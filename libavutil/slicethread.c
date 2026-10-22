/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ضمن <stdatomic.h>
#ضمن "cpu.h"
#ضمن "internal.h"
#ضمن "slicethread.h"
#ضمن "mem.h"
#ضمن "thread.h"
#ضمن "avassert.h"

#تعریف_کن MAX_AUTO_نخها 16

#إذا HAVE_PTHREADS || HAVE_W32_نخها || HAVE_OS2_نخها

تعريفنوع بنية کارگر_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحيح             انجامشده;
} کارگر_Context;

بنية AVSliceThread {
    کارگر_Context   *workers;
    صحيح             nb_نخها;
    صحيح             nb_فعال_نخها;
    صحيح             nb_jobs;

    atomic_uint     اولی_کار;
    atomic_uint     current_کار;
    pthread_mutex_t انجامشده_mutex;
    pthread_cond_t  انجامشده_cond;
    صحيح             انجامشده;
    صحيح             پایانیافته;
    atomic_int      error;

    فراغ            *priv;
    صحيح            (*کارگر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها);
    صحيح            (*main_func)(فراغ *priv);

#إذا LIBAVUTIL_نسخه_MAJOR < 62
    فراغ           (*کارگر_func_v1)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها);
    فراغ           (*main_func_v1)(فراغ *priv);
    فراغ            *priv_v1;
#پایان_اگر
};

ساكن صحيح پیاپی_jobs(AVSliceThread *ctx)
{
    بیعلامت nb_jobs    = ctx->nb_jobs;
    بیعلامت nb_فعال_نخها = ctx->nb_فعال_نخها;
    بیعلامت اولی_کار    = atomic_fetch_add_explicit(&ctx->اولی_کار, 1, memory_order_acq_rel);
    بیعلامت current_کار  = اولی_کار;

    افعل {
        صحيح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        إذا (ret)
            استمر;
        ret = ctx->کارگر_func(ctx->priv, current_کار, اولی_کار, nb_jobs, nb_فعال_نخها);
        إذا (ret) {
            صحيح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } طالما ((current_کار = atomic_fetch_add_explicit(&ctx->current_کار, 1, memory_order_acq_rel)) < nb_jobs);

    أرجع current_کار == nb_jobs + nb_فعال_نخها - 1;
}

ساكن فراغ *attribute_align_arg thread_کارگر(فراغ *v)
{
    کارگر_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_قفل(&w->mutex);
    pthread_cond_signal(&w->cond);

    طالما (1) {
        w->انجامشده = 1;
        طالما (w->انجامشده)
            pthread_cond_wait(&w->cond, &w->mutex);

        إذا (ctx->پایانیافته) {
            pthread_mutex_unlock(&w->mutex);
            أرجع عدم;
        }

        إذا (پیاپی_jobs(ctx)) {
            pthread_mutex_قفل(&ctx->انجامشده_mutex);
            ctx->انجامشده = 1;
            pthread_cond_signal(&ctx->انجامشده_cond);
            pthread_mutex_unlock(&ctx->انجامشده_mutex);
        }
    }
}

av_cold
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کارگر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_نخها)
{
    AVSliceThread *ctx;
    صحيح nb_workers, i;
    صحيح ret;

    av_assert0(nb_نخها >= 0);
    إذا (!nb_نخها) {
        صحيح nb_cpus = av_cpu_شمار();
        إذا (nb_cpus > 1)
            nb_نخها = FFMIN(nb_cpus + 1, MAX_AUTO_نخها);
        وإلا
            nb_نخها = 1;
    }

    nb_workers = nb_نخها;
    إذا (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(حجم(*ctx));
    إذا (!ctx)
        أرجع AVERROR(ENOMEM);

    إذا (nb_workers && !(ctx->workers = av_calloc(nb_workers, حجم(*ctx->workers)))) {
        av_freep(pctx);
        أرجع AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->کارگر_func = کارگر_func;
    ctx->main_func   = main_func;
    ctx->nb_نخها  = nb_نخها;
    ctx->nb_فعال_نخها = 0;
    ctx->nb_jobs     = 0;
    ctx->پایانیافته    = 0;

    atomic_init(&ctx->اولی_کار, 0);
    atomic_init(&ctx->current_کار, 0);
    ret = pthread_mutex_init(&ctx->انجامشده_mutex, عدم);
    إذا (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        أرجع AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->انجامشده_cond, عدم);
    إذا (ret) {
        ctx->nb_نخها = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        أرجع AVERROR(ret);
    }
    ctx->انجامشده        = 0;

    لكل (i = 0; i < nb_workers; i++) {
        کارگر_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, عدم);
        إذا (ret) {
            ctx->nb_نخها = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, عدم);
        إذا (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_نخها = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        pthread_mutex_قفل(&w->mutex);
        w->انجامشده = 0;

        إذا (ret = pthread_create(&w->thread, عدم, thread_کارگر, w)) {
            ctx->nb_نخها = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }

        طالما (!w->انجامشده)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    أرجع nb_نخها;
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    صحيح nb_workers, i, is_آخرین = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_فعال_نخها = FFMIN(nb_jobs, ctx->nb_نخها);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->اولی_کار, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_کار, ctx->nb_فعال_نخها, memory_order_relaxed);
    nb_workers             = ctx->nb_فعال_نخها;
    إذا (!ctx->main_func || !execute_main)
        nb_workers--;

    لكل (i = 0; i < nb_workers; i++) {
        کارگر_Context *w = &ctx->workers[i];
        pthread_mutex_قفل(&w->mutex);
        w->انجامشده = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    إذا (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وإلا
        is_آخرین = پیاپی_jobs(ctx);

    إذا (!is_آخرین) {
        pthread_mutex_قفل(&ctx->انجامشده_mutex);
        طالما (!ctx->انجامشده)
            pthread_cond_wait(&ctx->انجامشده_cond, &ctx->انجامشده_mutex);
        ctx->انجامشده = 0;
        pthread_mutex_unlock(&ctx->انجامشده_mutex);
    }

    إذا (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    أرجع ret;
}

av_cold فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    صحيح nb_workers, i;

    إذا (!ctx)
        أرجع;

    nb_workers = ctx->nb_نخها;
    إذا (!ctx->main_func)
        nb_workers--;

    ctx->پایانیافته = 1;
    لكل (i = 0; i < nb_workers; i++) {
        کارگر_Context *w = &ctx->workers[i];
        pthread_mutex_قفل(&w->mutex);
        w->انجامشده = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    لكل (i = 0; i < nb_workers; i++) {
        کارگر_Context *w = &ctx->workers[i];
        pthread_join(w->thread, عدم);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->انجامشده_cond);
    pthread_mutex_destroy(&ctx->انجامشده_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#إذا LIBAVUTIL_نسخه_MAJOR < 62

ساكن صحيح wrapper_کارگر(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها)
{
    AVSliceThread *ctx = priv;
    ctx->کارگر_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_نخها);
    أرجع 0;
}

ساكن صحيح wrapper_main(فراغ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    أرجع 0;
}

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کارگر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_نخها)
{
    صحيح ret = avpriv_slicethread_create2(pctx, عدم, wrapper_کارگر,
                                         main_func ? wrapper_main : عدم,
                                         nb_نخها);
    إذا (ret < 0)
        أرجع ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->کارگر_func_v1 = کارگر_func;
    (*pctx)->main_func_v1   = main_func;
    أرجع ret;
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#پایان_اگر /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وإلا /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کارگر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_نخها)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#إذا LIBAVUTIL_نسخه_MAJOR < 62

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کارگر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_نخها),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_نخها)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

#پایان_اگر /* LIBAVUTIL_VERSION_MAJOR < 62 */

#پایان_اگر /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
