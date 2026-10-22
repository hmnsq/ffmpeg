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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "slicethread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_AUTO_ਧਾਗੇ 16

#ਜੇ HAVE_PTHREADS || HAVE_W32_ਧਾਗੇ || HAVE_OS2_ਧਾਗੇ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਕਾਮਾ_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    ਪੂਰਨ             ਪੂਰਾ;
} ਕਾਮਾ_Context;

ਬਣਤਰ AVSliceThread {
    ਕਾਮਾ_Context   *workers;
    ਪੂਰਨ             nb_ਧਾਗੇ;
    ਪੂਰਨ             nb_ਸਰਗਰਮ_ਧਾਗੇ;
    ਪੂਰਨ             nb_jobs;

    atomic_uint     ਪਹਿਲਾ_ਕੰਮ;
    atomic_uint     current_ਕੰਮ;
    pthread_mutex_t ਪੂਰਾ_mutex;
    pthread_cond_t  ਪੂਰਾ_cond;
    ਪੂਰਨ             ਪੂਰਾ;
    ਪੂਰਨ             ਮੁਕੰਮਲ;
    atomic_int      error;

    ਖਾਲੀ            *priv;
    ਪੂਰਨ            (*ਕਾਮਾ_func)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ);
    ਪੂਰਨ            (*main_func)(ਖਾਲੀ *priv);

#ਜੇ LIBAVUTIL_ਸੰਸਕਰਣ_MAJOR < 62
    ਖਾਲੀ           (*ਕਾਮਾ_func_v1)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ);
    ਖਾਲੀ           (*main_func_v1)(ਖਾਲੀ *priv);
    ਖਾਲੀ            *priv_v1;
#ਜੇ_ਅੰਤ
};

ਸਥਿਰ ਪੂਰਨ ਲੜੀਵਾਰ_jobs(AVSliceThread *ctx)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ nb_jobs    = ctx->nb_jobs;
    ਬਿਨਾਨਿਸ਼ਾਨੀ nb_ਸਰਗਰਮ_ਧਾਗੇ = ctx->nb_ਸਰਗਰਮ_ਧਾਗੇ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪਹਿਲਾ_ਕੰਮ    = atomic_fetch_add_explicit(&ctx->ਪਹਿਲਾ_ਕੰਮ, 1, memory_order_acq_rel);
    ਬਿਨਾਨਿਸ਼ਾਨੀ current_ਕੰਮ  = ਪਹਿਲਾ_ਕੰਮ;

    ਕਰੋ {
        ਪੂਰਨ ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ਜੇ (ret)
            ਜਾਰੀ;
        ret = ctx->ਕਾਮਾ_func(ctx->priv, current_ਕੰਮ, ਪਹਿਲਾ_ਕੰਮ, nb_jobs, nb_ਸਰਗਰਮ_ਧਾਗੇ);
        ਜੇ (ret) {
            ਪੂਰਨ prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ਜਦੋਂ ((current_ਕੰਮ = atomic_fetch_add_explicit(&ctx->current_ਕੰਮ, 1, memory_order_acq_rel)) < nb_jobs);

    ਵਾਪਸ current_ਕੰਮ == nb_jobs + nb_ਸਰਗਰਮ_ਧਾਗੇ - 1;
}

ਸਥਿਰ ਖਾਲੀ *attribute_align_arg thread_ਕਾਮਾ(ਖਾਲੀ *v)
{
    ਕਾਮਾ_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_ਤਾਲਾ(&w->mutex);
    pthread_cond_signal(&w->cond);

    ਜਦੋਂ (1) {
        w->ਪੂਰਾ = 1;
        ਜਦੋਂ (w->ਪੂਰਾ)
            pthread_cond_wait(&w->cond, &w->mutex);

        ਜੇ (ctx->ਮੁਕੰਮਲ) {
            pthread_mutex_unlock(&w->mutex);
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਜੇ (ਲੜੀਵਾਰ_jobs(ctx)) {
            pthread_mutex_ਤਾਲਾ(&ctx->ਪੂਰਾ_mutex);
            ctx->ਪੂਰਾ = 1;
            pthread_cond_signal(&ctx->ਪੂਰਾ_cond);
            pthread_mutex_unlock(&ctx->ਪੂਰਾ_mutex);
        }
    }
}

av_cold
ਪੂਰਨ avpriv_slicethread_create2(AVSliceThread **pctx, ਖਾਲੀ *priv,
                               ਪੂਰਨ (*ਕਾਮਾ_func)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ),
                               ਪੂਰਨ (*main_func)(ਖਾਲੀ *priv),
                               ਪੂਰਨ nb_ਧਾਗੇ)
{
    AVSliceThread *ctx;
    ਪੂਰਨ nb_workers, i;
    ਪੂਰਨ ret;

    av_assert0(nb_ਧਾਗੇ >= 0);
    ਜੇ (!nb_ਧਾਗੇ) {
        ਪੂਰਨ nb_cpus = av_cpu_ਗਿਣਤੀ();
        ਜੇ (nb_cpus > 1)
            nb_ਧਾਗੇ = FFMIN(nb_cpus + 1, MAX_AUTO_ਧਾਗੇ);
        ਨਹੀਂਤਾਂ
            nb_ਧਾਗੇ = 1;
    }

    nb_workers = nb_ਧਾਗੇ;
    ਜੇ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(ਆਕਾਰ(*ctx));
    ਜੇ (!ctx)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (nb_workers && !(ctx->workers = av_calloc(nb_workers, ਆਕਾਰ(*ctx->workers)))) {
        av_freep(pctx);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->ਕਾਮਾ_func = ਕਾਮਾ_func;
    ctx->main_func   = main_func;
    ctx->nb_ਧਾਗੇ  = nb_ਧਾਗੇ;
    ctx->nb_ਸਰਗਰਮ_ਧਾਗੇ = 0;
    ctx->nb_jobs     = 0;
    ctx->ਮੁਕੰਮਲ    = 0;

    atomic_init(&ctx->ਪਹਿਲਾ_ਕੰਮ, 0);
    atomic_init(&ctx->current_ਕੰਮ, 0);
    ret = pthread_mutex_init(&ctx->ਪੂਰਾ_mutex, ਨਿਰਾ);
    ਜੇ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ਵਾਪਸ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->ਪੂਰਾ_cond, ਨਿਰਾ);
    ਜੇ (ret) {
        ctx->nb_ਧਾਗੇ = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ਵਾਪਸ AVERROR(ret);
    }
    ctx->ਪੂਰਾ        = 0;

    ਲਈ (i = 0; i < nb_workers; i++) {
        ਕਾਮਾ_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ਨਿਰਾ);
        ਜੇ (ret) {
            ctx->nb_ਧਾਗੇ = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ਵਾਪਸ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ਨਿਰਾ);
        ਜੇ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_ਧਾਗੇ = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ਵਾਪਸ AVERROR(ret);
        }
        pthread_mutex_ਤਾਲਾ(&w->mutex);
        w->ਪੂਰਾ = 0;

        ਜੇ (ret = pthread_create(&w->thread, ਨਿਰਾ, thread_ਕਾਮਾ, w)) {
            ctx->nb_ਧਾਗੇ = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ਵਾਪਸ AVERROR(ret);
        }

        ਜਦੋਂ (!w->ਪੂਰਾ)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ਵਾਪਸ nb_ਧਾਗੇ;
}

ਪੂਰਨ avpriv_slicethread_execute2(AVSliceThread *ctx, ਪੂਰਨ nb_jobs, ਪੂਰਨ execute_main)
{
    ਪੂਰਨ nb_workers, i, is_ਆਖਰੀ = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_ਸਰਗਰਮ_ਧਾਗੇ = FFMIN(nb_jobs, ctx->nb_ਧਾਗੇ);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->ਪਹਿਲਾ_ਕੰਮ, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_ਕੰਮ, ctx->nb_ਸਰਗਰਮ_ਧਾਗੇ, memory_order_relaxed);
    nb_workers             = ctx->nb_ਸਰਗਰਮ_ਧਾਗੇ;
    ਜੇ (!ctx->main_func || !execute_main)
        nb_workers--;

    ਲਈ (i = 0; i < nb_workers; i++) {
        ਕਾਮਾ_Context *w = &ctx->workers[i];
        pthread_mutex_ਤਾਲਾ(&w->mutex);
        w->ਪੂਰਾ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ਜੇ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ਨਹੀਂਤਾਂ
        is_ਆਖਰੀ = ਲੜੀਵਾਰ_jobs(ctx);

    ਜੇ (!is_ਆਖਰੀ) {
        pthread_mutex_ਤਾਲਾ(&ctx->ਪੂਰਾ_mutex);
        ਜਦੋਂ (!ctx->ਪੂਰਾ)
            pthread_cond_wait(&ctx->ਪੂਰਾ_cond, &ctx->ਪੂਰਾ_mutex);
        ctx->ਪੂਰਾ = 0;
        pthread_mutex_unlock(&ctx->ਪੂਰਾ_mutex);
    }

    ਜੇ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ਵਾਪਸ ret;
}

av_cold ਖਾਲੀ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    ਪੂਰਨ nb_workers, i;

    ਜੇ (!ctx)
        ਵਾਪਸ;

    nb_workers = ctx->nb_ਧਾਗੇ;
    ਜੇ (!ctx->main_func)
        nb_workers--;

    ctx->ਮੁਕੰਮਲ = 1;
    ਲਈ (i = 0; i < nb_workers; i++) {
        ਕਾਮਾ_Context *w = &ctx->workers[i];
        pthread_mutex_ਤਾਲਾ(&w->mutex);
        w->ਪੂਰਾ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ਲਈ (i = 0; i < nb_workers; i++) {
        ਕਾਮਾ_Context *w = &ctx->workers[i];
        pthread_join(w->thread, ਨਿਰਾ);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->ਪੂਰਾ_cond);
    pthread_mutex_destroy(&ctx->ਪੂਰਾ_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#ਜੇ LIBAVUTIL_ਸੰਸਕਰਣ_MAJOR < 62

ਸਥਿਰ ਪੂਰਨ wrapper_ਕਾਮਾ(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ)
{
    AVSliceThread *ctx = priv;
    ctx->ਕਾਮਾ_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_ਧਾਗੇ);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ wrapper_main(ਖਾਲੀ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ਵਾਪਸ 0;
}

ਪੂਰਨ avpriv_slicethread_create(AVSliceThread **pctx, ਖਾਲੀ *priv,
                              ਖਾਲੀ (*ਕਾਮਾ_func)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ),
                              ਖਾਲੀ (*main_func)(ਖਾਲੀ *priv),
                              ਪੂਰਨ nb_ਧਾਗੇ)
{
    ਪੂਰਨ ret = avpriv_slicethread_create2(pctx, ਨਿਰਾ, wrapper_ਕਾਮਾ,
                                         main_func ? wrapper_main : ਨਿਰਾ,
                                         nb_ਧਾਗੇ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->ਕਾਮਾ_func_v1 = ਕਾਮਾ_func;
    (*pctx)->main_func_v1   = main_func;
    ਵਾਪਸ ret;
}

ਖਾਲੀ avpriv_slicethread_execute(AVSliceThread *ctx, ਪੂਰਨ nb_jobs, ਪੂਰਨ execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#ਜੇ_ਅੰਤ /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ਨਹੀਂਤਾਂ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

ਪੂਰਨ avpriv_slicethread_create2(AVSliceThread **pctx, ਖਾਲੀ *priv,
                               ਪੂਰਨ (*ਕਾਮਾ_func)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ),
                               ਪੂਰਨ (*main_func)(ਖਾਲੀ *priv),
                               ਪੂਰਨ nb_ਧਾਗੇ)
{
    *pctx = ਨਿਰਾ;
    ਵਾਪਸ AVERROR(ENOSYS);
}

ਪੂਰਨ avpriv_slicethread_execute2(AVSliceThread *ctx, ਪੂਰਨ nb_jobs, ਪੂਰਨ execute_main)
{
    av_assert0(0);
}

ਖਾਲੀ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ਜੇ LIBAVUTIL_ਸੰਸਕਰਣ_MAJOR < 62

ਪੂਰਨ avpriv_slicethread_create(AVSliceThread **pctx, ਖਾਲੀ *priv,
                              ਖਾਲੀ (*ਕਾਮਾ_func)(ਖਾਲੀ *priv, ਪੂਰਨ jobnr, ਪੂਰਨ threadnr, ਪੂਰਨ nb_jobs, ਪੂਰਨ nb_ਧਾਗੇ),
                              ਖਾਲੀ (*main_func)(ਖਾਲੀ *priv),
                              ਪੂਰਨ nb_ਧਾਗੇ)
{
    *pctx = ਨਿਰਾ;
    ਵਾਪਸ AVERROR(ENOSYS);
}

ਖਾਲੀ avpriv_slicethread_execute(AVSliceThread *ctx, ਪੂਰਨ nb_jobs, ਪੂਰਨ execute_main)
{
    av_assert0(0);
}

#ਜੇ_ਅੰਤ /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ਜੇ_ਅੰਤ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
