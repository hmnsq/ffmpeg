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

#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "internal.h"
#ಅನ್ತರ್ಭಾವ "slicethread.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_AUTO_ಎಳೆಗಳು 16

#ಆದರೆ HAVE_PTHREADS || HAVE_W32_ಎಳೆಗಳು || HAVE_OS2_ಎಳೆಗಳು

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಕೆಲಸಗಾರ_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    ಪೂರ್ಣಾಂಕ             ಮುಗಿದ;
} ಕೆಲಸಗಾರ_Context;

ರಚನೆ AVSliceThread {
    ಕೆಲಸಗಾರ_Context   *workers;
    ಪೂರ್ಣಾಂಕ             nb_ಎಳೆಗಳು;
    ಪೂರ್ಣಾಂಕ             nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು;
    ಪೂರ್ಣಾಂಕ             nb_jobs;

    atomic_uint     ಮೊದಲ_ಕೆಲಸ;
    atomic_uint     current_ಕೆಲಸ;
    pthread_mutex_t ಮುಗಿದ_mutex;
    pthread_cond_t  ಮುಗಿದ_cond;
    ಪೂರ್ಣಾಂಕ             ಮುಗಿದ;
    ಪೂರ್ಣಾಂಕ             ಪೂರ್ಣಗೊಂಡ;
    atomic_int      error;

    ಶೂನ್ಯ            *priv;
    ಪೂರ್ಣಾಂಕ            (*ಕೆಲಸಗಾರ_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು);
    ಪೂರ್ಣಾಂಕ            (*main_func)(ಶೂನ್ಯ *priv);

#ಆದರೆ LIBAVUTIL_ಆವೃತ್ತಿ_MAJOR < 62
    ಶೂನ್ಯ           (*ಕೆಲಸಗಾರ_func_v1)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು);
    ಶೂನ್ಯ           (*main_func_v1)(ಶೂನ್ಯ *priv);
    ಶೂನ್ಯ            *priv_v1;
#ಆದರೆ_ಅಂತ್ಯ
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಸತತ_jobs(AVSliceThread *ctx)
{
    ಚಿಹ್ನೆರಹಿತ nb_jobs    = ctx->nb_jobs;
    ಚಿಹ್ನೆರಹಿತ nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು = ctx->nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು;
    ಚಿಹ್ನೆರಹಿತ ಮೊದಲ_ಕೆಲಸ    = atomic_fetch_add_explicit(&ctx->ಮೊದಲ_ಕೆಲಸ, 1, memory_order_acq_rel);
    ಚಿಹ್ನೆರಹಿತ current_ಕೆಲಸ  = ಮೊದಲ_ಕೆಲಸ;

    ಮಾಡು {
        ಪೂರ್ಣಾಂಕ ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ಆದರೆ (ret)
            ಮುಂದುವರಿ;
        ret = ctx->ಕೆಲಸಗಾರ_func(ctx->priv, current_ಕೆಲಸ, ಮೊದಲ_ಕೆಲಸ, nb_jobs, nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು);
        ಆದರೆ (ret) {
            ಪೂರ್ಣಾಂಕ prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ಆಗ ((current_ಕೆಲಸ = atomic_fetch_add_explicit(&ctx->current_ಕೆಲಸ, 1, memory_order_acq_rel)) < nb_jobs);

    ಹಿಂತಿರುಗಿ current_ಕೆಲಸ == nb_jobs + nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು - 1;
}

ಸ್ಥಿರ ಶೂನ್ಯ *attribute_align_arg thread_ಕೆಲಸಗಾರ(ಶೂನ್ಯ *v)
{
    ಕೆಲಸಗಾರ_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_ಬೀಗ(&w->mutex);
    pthread_cond_signal(&w->cond);

    ಆಗ (1) {
        w->ಮುಗಿದ = 1;
        ಆಗ (w->ಮುಗಿದ)
            pthread_cond_wait(&w->cond, &w->mutex);

        ಆದರೆ (ctx->ಪೂರ್ಣಗೊಂಡ) {
            pthread_mutex_unlock(&w->mutex);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಆದರೆ (ಸತತ_jobs(ctx)) {
            pthread_mutex_ಬೀಗ(&ctx->ಮುಗಿದ_mutex);
            ctx->ಮುಗಿದ = 1;
            pthread_cond_signal(&ctx->ಮುಗಿದ_cond);
            pthread_mutex_unlock(&ctx->ಮುಗಿದ_mutex);
        }
    }
}

av_cold
ಪೂರ್ಣಾಂಕ avpriv_slicethread_create2(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                               ಪೂರ್ಣಾಂಕ (*ಕೆಲಸಗಾರ_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು),
                               ಪೂರ್ಣಾಂಕ (*main_func)(ಶೂನ್ಯ *priv),
                               ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು)
{
    AVSliceThread *ctx;
    ಪೂರ್ಣಾಂಕ nb_workers, i;
    ಪೂರ್ಣಾಂಕ ret;

    av_assert0(nb_ಎಳೆಗಳು >= 0);
    ಆದರೆ (!nb_ಎಳೆಗಳು) {
        ಪೂರ್ಣಾಂಕ nb_cpus = av_cpu_ಎಣಿಕೆ();
        ಆದರೆ (nb_cpus > 1)
            nb_ಎಳೆಗಳು = FFMIN(nb_cpus + 1, MAX_AUTO_ಎಳೆಗಳು);
        ಇಲ್ಲದಿದ್ದರೆ
            nb_ಎಳೆಗಳು = 1;
    }

    nb_workers = nb_ಎಳೆಗಳು;
    ಆದರೆ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(ಗಾತ್ರ(*ctx));
    ಆದರೆ (!ctx)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (nb_workers && !(ctx->workers = av_calloc(nb_workers, ಗಾತ್ರ(*ctx->workers)))) {
        av_freep(pctx);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->ಕೆಲಸಗಾರ_func = ಕೆಲಸಗಾರ_func;
    ctx->main_func   = main_func;
    ctx->nb_ಎಳೆಗಳು  = nb_ಎಳೆಗಳು;
    ctx->nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು = 0;
    ctx->nb_jobs     = 0;
    ctx->ಪೂರ್ಣಗೊಂಡ    = 0;

    atomic_init(&ctx->ಮೊದಲ_ಕೆಲಸ, 0);
    atomic_init(&ctx->current_ಕೆಲಸ, 0);
    ret = pthread_mutex_init(&ctx->ಮುಗಿದ_mutex, ಖಾಲಿ);
    ಆದರೆ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ಹಿಂತಿರುಗಿ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->ಮುಗಿದ_cond, ಖಾಲಿ);
    ಆದರೆ (ret) {
        ctx->nb_ಎಳೆಗಳು = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ಹಿಂತಿರುಗಿ AVERROR(ret);
    }
    ctx->ಮುಗಿದ        = 0;

    ಗಾಗಿ (i = 0; i < nb_workers; i++) {
        ಕೆಲಸಗಾರ_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ಖಾಲಿ);
        ಆದರೆ (ret) {
            ctx->nb_ಎಳೆಗಳು = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ಹಿಂತಿರುಗಿ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ಖಾಲಿ);
        ಆದರೆ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_ಎಳೆಗಳು = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ಹಿಂತಿರುಗಿ AVERROR(ret);
        }
        pthread_mutex_ಬೀಗ(&w->mutex);
        w->ಮುಗಿದ = 0;

        ಆದರೆ (ret = pthread_create(&w->thread, ಖಾಲಿ, thread_ಕೆಲಸಗಾರ, w)) {
            ctx->nb_ಎಳೆಗಳು = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ಹಿಂತಿರುಗಿ AVERROR(ret);
        }

        ಆಗ (!w->ಮುಗಿದ)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ಹಿಂತಿರುಗಿ nb_ಎಳೆಗಳು;
}

ಪೂರ್ಣಾಂಕ avpriv_slicethread_execute2(AVSliceThread *ctx, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ execute_main)
{
    ಪೂರ್ಣಾಂಕ nb_workers, i, is_ಕೊನೆಯ = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು = FFMIN(nb_jobs, ctx->nb_ಎಳೆಗಳು);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->ಮೊದಲ_ಕೆಲಸ, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_ಕೆಲಸ, ctx->nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು, memory_order_relaxed);
    nb_workers             = ctx->nb_ಸಕ್ರಿಯ_ಎಳೆಗಳು;
    ಆದರೆ (!ctx->main_func || !execute_main)
        nb_workers--;

    ಗಾಗಿ (i = 0; i < nb_workers; i++) {
        ಕೆಲಸಗಾರ_Context *w = &ctx->workers[i];
        pthread_mutex_ಬೀಗ(&w->mutex);
        w->ಮುಗಿದ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ಆದರೆ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ಇಲ್ಲದಿದ್ದರೆ
        is_ಕೊನೆಯ = ಸತತ_jobs(ctx);

    ಆದರೆ (!is_ಕೊನೆಯ) {
        pthread_mutex_ಬೀಗ(&ctx->ಮುಗಿದ_mutex);
        ಆಗ (!ctx->ಮುಗಿದ)
            pthread_cond_wait(&ctx->ಮುಗಿದ_cond, &ctx->ಮುಗಿದ_mutex);
        ctx->ಮುಗಿದ = 0;
        pthread_mutex_unlock(&ctx->ಮುಗಿದ_mutex);
    }

    ಆದರೆ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ಹಿಂತಿರುಗಿ ret;
}

av_cold ಶೂನ್ಯ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    ಪೂರ್ಣಾಂಕ nb_workers, i;

    ಆದರೆ (!ctx)
        ಹಿಂತಿರುಗಿ;

    nb_workers = ctx->nb_ಎಳೆಗಳು;
    ಆದರೆ (!ctx->main_func)
        nb_workers--;

    ctx->ಪೂರ್ಣಗೊಂಡ = 1;
    ಗಾಗಿ (i = 0; i < nb_workers; i++) {
        ಕೆಲಸಗಾರ_Context *w = &ctx->workers[i];
        pthread_mutex_ಬೀಗ(&w->mutex);
        w->ಮುಗಿದ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ಗಾಗಿ (i = 0; i < nb_workers; i++) {
        ಕೆಲಸಗಾರ_Context *w = &ctx->workers[i];
        pthread_join(w->thread, ಖಾಲಿ);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->ಮುಗಿದ_cond);
    pthread_mutex_destroy(&ctx->ಮುಗಿದ_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#ಆದರೆ LIBAVUTIL_ಆವೃತ್ತಿ_MAJOR < 62

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ wrapper_ಕೆಲಸಗಾರ(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು)
{
    AVSliceThread *ctx = priv;
    ctx->ಕೆಲಸಗಾರ_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_ಎಳೆಗಳು);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ wrapper_main(ಶೂನ್ಯ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ avpriv_slicethread_create(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                              ಶೂನ್ಯ (*ಕೆಲಸಗಾರ_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು),
                              ಶೂನ್ಯ (*main_func)(ಶೂನ್ಯ *priv),
                              ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು)
{
    ಪೂರ್ಣಾಂಕ ret = avpriv_slicethread_create2(pctx, ಖಾಲಿ, wrapper_ಕೆಲಸಗಾರ,
                                         main_func ? wrapper_main : ಖಾಲಿ,
                                         nb_ಎಳೆಗಳು);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->ಕೆಲಸಗಾರ_func_v1 = ಕೆಲಸಗಾರ_func;
    (*pctx)->main_func_v1   = main_func;
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ avpriv_slicethread_execute(AVSliceThread *ctx, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#ಆದರೆ_ಅಂತ್ಯ /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ಇಲ್ಲದಿದ್ದರೆ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

ಪೂರ್ಣಾಂಕ avpriv_slicethread_create2(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                               ಪೂರ್ಣಾಂಕ (*ಕೆಲಸಗಾರ_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು),
                               ಪೂರ್ಣಾಂಕ (*main_func)(ಶೂನ್ಯ *priv),
                               ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು)
{
    *pctx = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಪೂರ್ಣಾಂಕ avpriv_slicethread_execute2(AVSliceThread *ctx, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ execute_main)
{
    av_assert0(0);
}

ಶೂನ್ಯ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ಆದರೆ LIBAVUTIL_ಆವೃತ್ತಿ_MAJOR < 62

ಪೂರ್ಣಾಂಕ avpriv_slicethread_create(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                              ಶೂನ್ಯ (*ಕೆಲಸಗಾರ_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಂಕ jobnr, ಪೂರ್ಣಾಂಕ threadnr, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು),
                              ಶೂನ್ಯ (*main_func)(ಶೂನ್ಯ *priv),
                              ಪೂರ್ಣಾಂಕ nb_ಎಳೆಗಳು)
{
    *pctx = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಶೂನ್ಯ avpriv_slicethread_execute(AVSliceThread *ctx, ಪೂರ್ಣಾಂಕ nb_jobs, ಪೂರ್ಣಾಂಕ execute_main)
{
    av_assert0(0);
}

#ಆದರೆ_ಅಂತ್ಯ /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
