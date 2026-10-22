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

#تعریف_کرو MAX_AUTO_دھاگے 16

#إذا HAVE_PTHREADS || HAVE_W32_دھاگے || HAVE_OS2_دھاگے

تعريفنوع بنية کامہ_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحيح             پورا;
} کامہ_Context;

بنية AVSliceThread {
    کامہ_Context   *workers;
    صحيح             nb_دھاگے;
    صحيح             nb_سرگرم_دھاگے;
    صحيح             nb_jobs;

    atomic_uint     پہلا_کم;
    atomic_uint     current_کم;
    pthread_mutex_t پورا_mutex;
    pthread_cond_t  پورا_cond;
    صحيح             پورا;
    صحيح             مکمل;
    atomic_int      error;

    فراغ            *priv;
    صحيح            (*کامہ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے);
    صحيح            (*main_func)(فراغ *priv);

#إذا LIBAVUTIL_نسخہ_MAJOR < 62
    فراغ           (*کامہ_func_v1)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے);
    فراغ           (*main_func_v1)(فراغ *priv);
    فراغ            *priv_v1;
#جے_انت
};

ساكن صحيح لگاتار_jobs(AVSliceThread *ctx)
{
    بنانشانی nb_jobs    = ctx->nb_jobs;
    بنانشانی nb_سرگرم_دھاگے = ctx->nb_سرگرم_دھاگے;
    بنانشانی پہلا_کم    = atomic_fetch_add_explicit(&ctx->پہلا_کم, 1, memory_order_acq_rel);
    بنانشانی current_کم  = پہلا_کم;

    افعل {
        صحيح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        إذا (ret)
            استمر;
        ret = ctx->کامہ_func(ctx->priv, current_کم, پہلا_کم, nb_jobs, nb_سرگرم_دھاگے);
        إذا (ret) {
            صحيح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } طالما ((current_کم = atomic_fetch_add_explicit(&ctx->current_کم, 1, memory_order_acq_rel)) < nb_jobs);

    أرجع current_کم == nb_jobs + nb_سرگرم_دھاگے - 1;
}

ساكن فراغ *attribute_align_arg thread_کامہ(فراغ *v)
{
    کامہ_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_جندرا(&w->mutex);
    pthread_cond_signal(&w->cond);

    طالما (1) {
        w->پورا = 1;
        طالما (w->پورا)
            pthread_cond_wait(&w->cond, &w->mutex);

        إذا (ctx->مکمل) {
            pthread_mutex_unlock(&w->mutex);
            أرجع عدم;
        }

        إذا (لگاتار_jobs(ctx)) {
            pthread_mutex_جندرا(&ctx->پورا_mutex);
            ctx->پورا = 1;
            pthread_cond_signal(&ctx->پورا_cond);
            pthread_mutex_unlock(&ctx->پورا_mutex);
        }
    }
}

av_cold
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کامہ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_دھاگے)
{
    AVSliceThread *ctx;
    صحيح nb_workers, i;
    صحيح ret;

    av_assert0(nb_دھاگے >= 0);
    إذا (!nb_دھاگے) {
        صحيح nb_cpus = av_cpu_گنتی();
        إذا (nb_cpus > 1)
            nb_دھاگے = FFMIN(nb_cpus + 1, MAX_AUTO_دھاگے);
        وإلا
            nb_دھاگے = 1;
    }

    nb_workers = nb_دھاگے;
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
    ctx->کامہ_func = کامہ_func;
    ctx->main_func   = main_func;
    ctx->nb_دھاگے  = nb_دھاگے;
    ctx->nb_سرگرم_دھاگے = 0;
    ctx->nb_jobs     = 0;
    ctx->مکمل    = 0;

    atomic_init(&ctx->پہلا_کم, 0);
    atomic_init(&ctx->current_کم, 0);
    ret = pthread_mutex_init(&ctx->پورا_mutex, عدم);
    إذا (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        أرجع AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->پورا_cond, عدم);
    إذا (ret) {
        ctx->nb_دھاگے = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        أرجع AVERROR(ret);
    }
    ctx->پورا        = 0;

    لكل (i = 0; i < nb_workers; i++) {
        کامہ_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, عدم);
        إذا (ret) {
            ctx->nb_دھاگے = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, عدم);
        إذا (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_دھاگے = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        pthread_mutex_جندرا(&w->mutex);
        w->پورا = 0;

        إذا (ret = pthread_create(&w->thread, عدم, thread_کامہ, w)) {
            ctx->nb_دھاگے = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }

        طالما (!w->پورا)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    أرجع nb_دھاگے;
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    صحيح nb_workers, i, is_آخری = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_سرگرم_دھاگے = FFMIN(nb_jobs, ctx->nb_دھاگے);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->پہلا_کم, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_کم, ctx->nb_سرگرم_دھاگے, memory_order_relaxed);
    nb_workers             = ctx->nb_سرگرم_دھاگے;
    إذا (!ctx->main_func || !execute_main)
        nb_workers--;

    لكل (i = 0; i < nb_workers; i++) {
        کامہ_Context *w = &ctx->workers[i];
        pthread_mutex_جندرا(&w->mutex);
        w->پورا = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    إذا (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وإلا
        is_آخری = لگاتار_jobs(ctx);

    إذا (!is_آخری) {
        pthread_mutex_جندرا(&ctx->پورا_mutex);
        طالما (!ctx->پورا)
            pthread_cond_wait(&ctx->پورا_cond, &ctx->پورا_mutex);
        ctx->پورا = 0;
        pthread_mutex_unlock(&ctx->پورا_mutex);
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

    nb_workers = ctx->nb_دھاگے;
    إذا (!ctx->main_func)
        nb_workers--;

    ctx->مکمل = 1;
    لكل (i = 0; i < nb_workers; i++) {
        کامہ_Context *w = &ctx->workers[i];
        pthread_mutex_جندرا(&w->mutex);
        w->پورا = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    لكل (i = 0; i < nb_workers; i++) {
        کامہ_Context *w = &ctx->workers[i];
        pthread_join(w->thread, عدم);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->پورا_cond);
    pthread_mutex_destroy(&ctx->پورا_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#إذا LIBAVUTIL_نسخہ_MAJOR < 62

ساكن صحيح wrapper_کامہ(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے)
{
    AVSliceThread *ctx = priv;
    ctx->کامہ_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_دھاگے);
    أرجع 0;
}

ساكن صحيح wrapper_main(فراغ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    أرجع 0;
}

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کامہ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_دھاگے)
{
    صحيح ret = avpriv_slicethread_create2(pctx, عدم, wrapper_کامہ,
                                         main_func ? wrapper_main : عدم,
                                         nb_دھاگے);
    إذا (ret < 0)
        أرجع ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->کامہ_func_v1 = کامہ_func;
    (*pctx)->main_func_v1   = main_func;
    أرجع ret;
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#جے_انت /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وإلا /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کامہ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_دھاگے)
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

#إذا LIBAVUTIL_نسخہ_MAJOR < 62

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کامہ_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_دھاگے),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_دھاگے)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

#جے_انت /* LIBAVUTIL_VERSION_MAJOR < 62 */

#جے_انت /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
