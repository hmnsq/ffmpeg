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

#define MAX_AUTO_THREADS 16

#ಯದಿ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    ಪೂರ್ಣಾಙ್ಕ             done;
} WorkerContext;

ಸಂರಚನಾ AVSliceThread {
    WorkerContext   *workers;
    ಪೂರ್ಣಾಙ್ಕ             nb_threads;
    ಪೂರ್ಣಾಙ್ಕ             nb_active_threads;
    ಪೂರ್ಣಾಙ್ಕ             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    ಪೂರ್ಣಾಙ್ಕ             done;
    ಪೂರ್ಣಾಙ್ಕ             finished;
    atomic_int      error;

    ಶೂನ್ಯ            *priv;
    ಪೂರ್ಣಾಙ್ಕ            (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads);
    ಪೂರ್ಣಾಙ್ಕ            (*main_func)(ಶೂನ್ಯ *priv);

#ಯದಿ LIBAVUTIL_VERSION_MAJOR < 62
    ಶೂನ್ಯ           (*worker_func_v1)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads);
    ಶೂನ್ಯ           (*main_func_v1)(ಶೂನ್ಯ *priv);
    ಶೂನ್ಯ            *priv_v1;
#endif
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    ಕುರು {
        ಪೂರ್ಣಾಙ್ಕ ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ಯದಿ (ret)
            ಅನುವರ್ತ;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        ಯದಿ (ret) {
            ಪೂರ್ಣಾಙ್ಕ prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ಯಾವತ್ ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ಪ್ರತ್ಯಾಗಮ current_job == nb_jobs + nb_active_threads - 1;
}

ಸ್ಥಿರ ಶೂನ್ಯ *attribute_align_arg thread_worker(ಶೂನ್ಯ *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    ಯಾವತ್ (1) {
        w->done = 1;
        ಯಾವತ್ (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        ಯದಿ (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        ಯದಿ (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create2(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                               ಪೂರ್ಣಾಙ್ಕ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                               ಪೂರ್ಣಾಙ್ಕ (*main_func)(ಶೂನ್ಯ *priv),
                               ಪೂರ್ಣಾಙ್ಕ nb_threads)
{
    AVSliceThread *ctx;
    ಪೂರ್ಣಾಙ್ಕ nb_workers, i;
    ಪೂರ್ಣಾಙ್ಕ ret;

    av_assert0(nb_threads >= 0);
    ಯದಿ (!nb_threads) {
        ಪೂರ್ಣಾಙ್ಕ nb_cpus = av_cpu_ಎಣಿಕೆ();
        ಯದಿ (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        ಅನ್ಯಥಾ
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    ಯದಿ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(ಪರಿಮಾಣ(*ctx));
    ಯದಿ (!ctx)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (nb_workers && !(ctx->workers = av_calloc(nb_workers, ಪರಿಮಾಣ(*ctx->workers)))) {
        av_freep(pctx);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->worker_func = worker_func;
    ctx->main_func   = main_func;
    ctx->nb_threads  = nb_threads;
    ctx->nb_active_threads = 0;
    ctx->nb_jobs     = 0;
    ctx->finished    = 0;

    atomic_init(&ctx->first_job, 0);
    atomic_init(&ctx->current_job, 0);
    ret = pthread_mutex_init(&ctx->done_mutex, ರಿಕ್ತ);
    ಯದಿ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, ರಿಕ್ತ);
    ಯದಿ (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
    }
    ctx->done        = 0;

    ಪ್ರತಿ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ರಿಕ್ತ);
        ಯದಿ (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ರಿಕ್ತ);
        ಯದಿ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        ಯದಿ (ret = pthread_create(&w->thread, ರಿಕ್ತ, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
        }

        ಯಾವತ್ (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ಪ್ರತ್ಯಾಗಮ nb_threads;
}

ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_execute2(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main)
{
    ಪೂರ್ಣಾಙ್ಕ nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    ಯದಿ (!ctx->main_func || !execute_main)
        nb_workers--;

    ಪ್ರತಿ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ಯದಿ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ಅನ್ಯಥಾ
        is_last = run_jobs(ctx);

    ಯದಿ (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        ಯಾವತ್ (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    ಯದಿ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ಪ್ರತ್ಯಾಗಮ ret;
}

av_cold ಶೂನ್ಯ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    ಪೂರ್ಣಾಙ್ಕ nb_workers, i;

    ಯದಿ (!ctx)
        ಪ್ರತ್ಯಾಗಮ;

    nb_workers = ctx->nb_threads;
    ಯದಿ (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    ಪ್ರತಿ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ಪ್ರತಿ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, ರಿಕ್ತ);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->done_cond);
    pthread_mutex_destroy(&ctx->done_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#ಯದಿ LIBAVUTIL_VERSION_MAJOR < 62

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ wrapper_worker(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ wrapper_main(ಶೂನ್ಯ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                              ಶೂನ್ಯ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                              ಶೂನ್ಯ (*main_func)(ಶೂನ್ಯ *priv),
                              ಪೂರ್ಣಾಙ್ಕ nb_threads)
{
    ಪೂರ್ಣಾಙ್ಕ ret = avpriv_slicethread_create2(pctx, ರಿಕ್ತ, wrapper_worker,
                                         main_func ? wrapper_main : ರಿಕ್ತ,
                                         nb_threads);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ avpriv_slicethread_execute(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ಅನ್ಯಥಾ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create2(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                               ಪೂರ್ಣಾಙ್ಕ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                               ಪೂರ್ಣಾಙ್ಕ (*main_func)(ಶೂನ್ಯ *priv),
                               ಪೂರ್ಣಾಙ್ಕ nb_threads)
{
    *pctx = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_execute2(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main)
{
    av_assert0(0);
}

ಶೂನ್ಯ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ಯದಿ LIBAVUTIL_VERSION_MAJOR < 62

ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                              ಶೂನ್ಯ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                              ಶೂನ್ಯ (*main_func)(ಶೂನ್ಯ *priv),
                              ಪೂರ್ಣಾಙ್ಕ nb_threads)
{
    *pctx = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಶೂನ್ಯ avpriv_slicethread_execute(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
