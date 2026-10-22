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

#include <stdatomic.h>
#include "cpu.h"
#include "internal.h"
#include "slicethread.h"
#include "mem.h"
#include "thread.h"
#include "avassert.h"

#define MAX_AUTO_THREADS 16

#ꦪꦼꦤ꧀ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

typedef sa_nracanaa WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    puur_naa_nka             done;
} WorkerContext;

sa_nracanaa AVSliceThread {
    WorkerContext   *workers;
    puur_naa_nka             nb_threads;
    puur_naa_nka             nb_active_threads;
    puur_naa_nka             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    puur_naa_nka             done;
    puur_naa_nka             finished;
    atomic_int      error;

    void            *priv;
    puur_naa_nka            (*worker_func)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads);
    puur_naa_nka            (*main_func)(void *priv);

#ꦪꦼꦤ꧀ LIBAVUTIL_VERSION_MAJOR < 62
    void           (*worker_func_v1)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads);
    void           (*main_func_v1)(void *priv);
    void            *priv_v1;
#endif
};

static puur_naa_nka run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    do {
        puur_naa_nka ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ꦪꦼꦤ꧀ (ret)
            continue;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        ꦪꦼꦤ꧀ (ret) {
            puur_naa_nka prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ꦱꦼꦢꦼꦭ ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ꦮꦭꦶ current_job == nb_jobs + nb_active_threads - 1;
}

static void *attribute_align_arg thread_worker(void *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    ꦱꦼꦢꦼꦭ (1) {
        w->done = 1;
        ꦱꦼꦢꦼꦭ (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        ꦪꦼꦤ꧀ (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ꦮꦭꦶ NULL;
        }

        ꦪꦼꦤ꧀ (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
puur_naa_nka avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               puur_naa_nka (*worker_func)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads),
                               puur_naa_nka (*main_func)(void *priv),
                               puur_naa_nka nb_threads)
{
    AVSliceThread *ctx;
    puur_naa_nka nb_workers, i;
    puur_naa_nka ret;

    av_assert0(nb_threads >= 0);
    ꦪꦼꦤ꧀ (!nb_threads) {
        puur_naa_nka nb_cpus = av_cpu_count();
        ꦪꦼꦤ꧀ (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        ꦭꦶꦪ
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    ꦪꦼꦤ꧀ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(parimaa_na(*ctx));
    ꦪꦼꦤ꧀ (!ctx)
        ꦮꦭꦶ AVERROR(ENOMEM);

    ꦪꦼꦤ꧀ (nb_workers && !(ctx->workers = av_calloc(nb_workers, parimaa_na(*ctx->workers)))) {
        av_freep(pctx);
        ꦮꦭꦶ AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, NULL);
    ꦪꦼꦤ꧀ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ꦮꦭꦶ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, NULL);
    ꦪꦼꦤ꧀ (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ꦮꦭꦶ AVERROR(ret);
    }
    ctx->done        = 0;

    ꦏꦁꦒꦺꦴ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, NULL);
        ꦪꦼꦤ꧀ (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ꦮꦭꦶ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, NULL);
        ꦪꦼꦤ꧀ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ꦮꦭꦶ AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        ꦪꦼꦤ꧀ (ret = pthread_create(&w->thread, NULL, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ꦮꦭꦶ AVERROR(ret);
        }

        ꦱꦼꦢꦼꦭ (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ꦮꦭꦶ nb_threads;
}

puur_naa_nka avpriv_slicethread_execute2(AVSliceThread *ctx, puur_naa_nka nb_jobs, puur_naa_nka execute_main)
{
    puur_naa_nka nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    ꦪꦼꦤ꧀ (!ctx->main_func || !execute_main)
        nb_workers--;

    ꦏꦁꦒꦺꦴ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ꦪꦼꦤ꧀ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ꦭꦶꦪ
        is_last = run_jobs(ctx);

    ꦪꦼꦤ꧀ (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        ꦱꦼꦢꦼꦭ (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    ꦪꦼꦤ꧀ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ꦮꦭꦶ ret;
}

av_cold void avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    puur_naa_nka nb_workers, i;

    ꦪꦼꦤ꧀ (!ctx)
        ꦮꦭꦶ;

    nb_workers = ctx->nb_threads;
    ꦪꦼꦤ꧀ (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    ꦏꦁꦒꦺꦴ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ꦏꦁꦒꦺꦴ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, NULL);
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

#ꦪꦼꦤ꧀ LIBAVUTIL_VERSION_MAJOR < 62

static puur_naa_nka wrapper_worker(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ꦮꦭꦶ 0;
}

static puur_naa_nka wrapper_main(void *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ꦮꦭꦶ 0;
}

puur_naa_nka avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads),
                              void (*main_func)(void *priv),
                              puur_naa_nka nb_threads)
{
    puur_naa_nka ret = avpriv_slicethread_create2(pctx, NULL, wrapper_worker,
                                         main_func ? wrapper_main : NULL,
                                         nb_threads);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ꦮꦭꦶ ret;
}

void avpriv_slicethread_execute(AVSliceThread *ctx, puur_naa_nka nb_jobs, puur_naa_nka execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ꦭꦶꦪ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

puur_naa_nka avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               puur_naa_nka (*worker_func)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads),
                               puur_naa_nka (*main_func)(void *priv),
                               puur_naa_nka nb_threads)
{
    *pctx = NULL;
    ꦮꦭꦶ AVERROR(ENOSYS);
}

puur_naa_nka avpriv_slicethread_execute2(AVSliceThread *ctx, puur_naa_nka nb_jobs, puur_naa_nka execute_main)
{
    av_assert0(0);
}

void avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ꦪꦼꦤ꧀ LIBAVUTIL_VERSION_MAJOR < 62

puur_naa_nka avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, puur_naa_nka jobnr, puur_naa_nka threadnr, puur_naa_nka nb_jobs, puur_naa_nka nb_threads),
                              void (*main_func)(void *priv),
                              puur_naa_nka nb_threads)
{
    *pctx = NULL;
    ꦮꦭꦶ AVERROR(ENOSYS);
}

void avpriv_slicethread_execute(AVSliceThread *ctx, puur_naa_nka nb_jobs, puur_naa_nka execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
