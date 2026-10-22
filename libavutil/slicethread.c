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

#وصف_ڪريو MAX_AUTO_ڌاڳا 16

#إذا HAVE_PTHREADS || HAVE_W32_ڌاڳا || HAVE_OS2_ڌاڳا

تعريفنوع بنية ڪم_ڪندڙ_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحيح             پورو;
} ڪم_ڪندڙ_Context;

بنية AVSliceThread {
    ڪم_ڪندڙ_Context   *workers;
    صحيح             nb_ڌاڳا;
    صحيح             nb_سرگرم_ڌاڳا;
    صحيح             nb_jobs;

    atomic_uint     پهريون_ڪم;
    atomic_uint     current_ڪم;
    pthread_mutex_t پورو_mutex;
    pthread_cond_t  پورو_cond;
    صحيح             پورو;
    صحيح             ختم;
    atomic_int      error;

    فراغ            *priv;
    صحيح            (*ڪم_ڪندڙ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا);
    صحيح            (*main_func)(فراغ *priv);

#إذا LIBAVUTIL_نسخو_MAJOR < 62
    فراغ           (*ڪم_ڪندڙ_func_v1)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا);
    فراغ           (*main_func_v1)(فراغ *priv);
    فراغ            *priv_v1;
#جيڪڏهن_پورو
};

ساكن صحيح لاڳيتو_jobs(AVSliceThread *ctx)
{
    بنانشان nb_jobs    = ctx->nb_jobs;
    بنانشان nb_سرگرم_ڌاڳا = ctx->nb_سرگرم_ڌاڳا;
    بنانشان پهريون_ڪم    = atomic_fetch_add_explicit(&ctx->پهريون_ڪم, 1, memory_order_acq_rel);
    بنانشان current_ڪم  = پهريون_ڪم;

    افعل {
        صحيح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        إذا (ret)
            استمر;
        ret = ctx->ڪم_ڪندڙ_func(ctx->priv, current_ڪم, پهريون_ڪم, nb_jobs, nb_سرگرم_ڌاڳا);
        إذا (ret) {
            صحيح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } طالما ((current_ڪم = atomic_fetch_add_explicit(&ctx->current_ڪم, 1, memory_order_acq_rel)) < nb_jobs);

    أرجع current_ڪم == nb_jobs + nb_سرگرم_ڌاڳا - 1;
}

ساكن فراغ *attribute_align_arg thread_ڪم_ڪندڙ(فراغ *v)
{
    ڪم_ڪندڙ_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_تالو(&w->mutex);
    pthread_cond_signal(&w->cond);

    طالما (1) {
        w->پورو = 1;
        طالما (w->پورو)
            pthread_cond_wait(&w->cond, &w->mutex);

        إذا (ctx->ختم) {
            pthread_mutex_unlock(&w->mutex);
            أرجع عدم;
        }

        إذا (لاڳيتو_jobs(ctx)) {
            pthread_mutex_تالو(&ctx->پورو_mutex);
            ctx->پورو = 1;
            pthread_cond_signal(&ctx->پورو_cond);
            pthread_mutex_unlock(&ctx->پورو_mutex);
        }
    }
}

av_cold
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*ڪم_ڪندڙ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_ڌاڳا)
{
    AVSliceThread *ctx;
    صحيح nb_workers, i;
    صحيح ret;

    av_assert0(nb_ڌاڳا >= 0);
    إذا (!nb_ڌاڳا) {
        صحيح nb_cpus = av_cpu_ڳڻپ();
        إذا (nb_cpus > 1)
            nb_ڌاڳا = FFMIN(nb_cpus + 1, MAX_AUTO_ڌاڳا);
        وإلا
            nb_ڌاڳا = 1;
    }

    nb_workers = nb_ڌاڳا;
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
    ctx->ڪم_ڪندڙ_func = ڪم_ڪندڙ_func;
    ctx->main_func   = main_func;
    ctx->nb_ڌاڳا  = nb_ڌاڳا;
    ctx->nb_سرگرم_ڌاڳا = 0;
    ctx->nb_jobs     = 0;
    ctx->ختم    = 0;

    atomic_init(&ctx->پهريون_ڪم, 0);
    atomic_init(&ctx->current_ڪم, 0);
    ret = pthread_mutex_init(&ctx->پورو_mutex, عدم);
    إذا (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        أرجع AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->پورو_cond, عدم);
    إذا (ret) {
        ctx->nb_ڌاڳا = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        أرجع AVERROR(ret);
    }
    ctx->پورو        = 0;

    لكل (i = 0; i < nb_workers; i++) {
        ڪم_ڪندڙ_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, عدم);
        إذا (ret) {
            ctx->nb_ڌاڳا = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, عدم);
        إذا (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_ڌاڳا = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        pthread_mutex_تالو(&w->mutex);
        w->پورو = 0;

        إذا (ret = pthread_create(&w->thread, عدم, thread_ڪم_ڪندڙ, w)) {
            ctx->nb_ڌاڳا = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }

        طالما (!w->پورو)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    أرجع nb_ڌاڳا;
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    صحيح nb_workers, i, is_آخري = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_سرگرم_ڌاڳا = FFMIN(nb_jobs, ctx->nb_ڌاڳا);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->پهريون_ڪم, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_ڪم, ctx->nb_سرگرم_ڌاڳا, memory_order_relaxed);
    nb_workers             = ctx->nb_سرگرم_ڌاڳا;
    إذا (!ctx->main_func || !execute_main)
        nb_workers--;

    لكل (i = 0; i < nb_workers; i++) {
        ڪم_ڪندڙ_Context *w = &ctx->workers[i];
        pthread_mutex_تالو(&w->mutex);
        w->پورو = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    إذا (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وإلا
        is_آخري = لاڳيتو_jobs(ctx);

    إذا (!is_آخري) {
        pthread_mutex_تالو(&ctx->پورو_mutex);
        طالما (!ctx->پورو)
            pthread_cond_wait(&ctx->پورو_cond, &ctx->پورو_mutex);
        ctx->پورو = 0;
        pthread_mutex_unlock(&ctx->پورو_mutex);
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

    nb_workers = ctx->nb_ڌاڳا;
    إذا (!ctx->main_func)
        nb_workers--;

    ctx->ختم = 1;
    لكل (i = 0; i < nb_workers; i++) {
        ڪم_ڪندڙ_Context *w = &ctx->workers[i];
        pthread_mutex_تالو(&w->mutex);
        w->پورو = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    لكل (i = 0; i < nb_workers; i++) {
        ڪم_ڪندڙ_Context *w = &ctx->workers[i];
        pthread_join(w->thread, عدم);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->پورو_cond);
    pthread_mutex_destroy(&ctx->پورو_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#إذا LIBAVUTIL_نسخو_MAJOR < 62

ساكن صحيح wrapper_ڪم_ڪندڙ(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا)
{
    AVSliceThread *ctx = priv;
    ctx->ڪم_ڪندڙ_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_ڌاڳا);
    أرجع 0;
}

ساكن صحيح wrapper_main(فراغ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    أرجع 0;
}

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*ڪم_ڪندڙ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_ڌاڳا)
{
    صحيح ret = avpriv_slicethread_create2(pctx, عدم, wrapper_ڪم_ڪندڙ,
                                         main_func ? wrapper_main : عدم,
                                         nb_ڌاڳا);
    إذا (ret < 0)
        أرجع ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->ڪم_ڪندڙ_func_v1 = ڪم_ڪندڙ_func;
    (*pctx)->main_func_v1   = main_func;
    أرجع ret;
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#جيڪڏهن_پورو /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وإلا /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*ڪم_ڪندڙ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_ڌاڳا)
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

#إذا LIBAVUTIL_نسخو_MAJOR < 62

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*ڪم_ڪندڙ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_ڌاڳا),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_ڌاڳا)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

#جيڪڏهن_پورو /* LIBAVUTIL_VERSION_MAJOR < 62 */

#جيڪڏهن_پورو /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
