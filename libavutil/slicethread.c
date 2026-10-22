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

#만약 HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

typedef struct WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    정수             done;
} WorkerContext;

struct AVSliceThread {
    WorkerContext   *workers;
    정수             nb_threads;
    정수             nb_active_threads;
    정수             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    정수             done;
    정수             finished;
    atomic_int      error;

    void            *priv;
    정수            (*worker_func)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads);
    정수            (*main_func)(void *priv);

#만약 LIBAVUTIL_VERSION_MAJOR < 62
    void           (*worker_func_v1)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads);
    void           (*main_func_v1)(void *priv);
    void            *priv_v1;
#endif
};

static 정수 run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    do {
        정수 ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        만약 (ret)
            continue;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        만약 (ret) {
            정수 prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } 동안 ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    반환 current_job == nb_jobs + nb_active_threads - 1;
}

static void *attribute_align_arg thread_worker(void *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    동안 (1) {
        w->done = 1;
        동안 (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        만약 (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            반환 NULL;
        }

        만약 (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
정수 avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               정수 (*worker_func)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads),
                               정수 (*main_func)(void *priv),
                               정수 nb_threads)
{
    AVSliceThread *ctx;
    정수 nb_workers, i;
    정수 ret;

    av_assert0(nb_threads >= 0);
    만약 (!nb_threads) {
        정수 nb_cpus = av_cpu_count();
        만약 (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        아니면
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    만약 (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(sizeof(*ctx));
    만약 (!ctx)
        반환 AVERROR(ENOMEM);

    만약 (nb_workers && !(ctx->workers = av_calloc(nb_workers, sizeof(*ctx->workers)))) {
        av_freep(pctx);
        반환 AVERROR(ENOMEM);
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
    만약 (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        반환 AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, NULL);
    만약 (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        반환 AVERROR(ret);
    }
    ctx->done        = 0;

    위해 (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, NULL);
        만약 (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            반환 AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, NULL);
        만약 (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            반환 AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        만약 (ret = pthread_create(&w->thread, NULL, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            반환 AVERROR(ret);
        }

        동안 (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    반환 nb_threads;
}

정수 avpriv_slicethread_execute2(AVSliceThread *ctx, 정수 nb_jobs, 정수 execute_main)
{
    정수 nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    만약 (!ctx->main_func || !execute_main)
        nb_workers--;

    위해 (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    만약 (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } 아니면
        is_last = run_jobs(ctx);

    만약 (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        동안 (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    만약 (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    반환 ret;
}

av_cold void avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    정수 nb_workers, i;

    만약 (!ctx)
        반환;

    nb_workers = ctx->nb_threads;
    만약 (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    위해 (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    위해 (i = 0; i < nb_workers; i++) {
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

#만약 LIBAVUTIL_VERSION_MAJOR < 62

static 정수 wrapper_worker(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    반환 0;
}

static 정수 wrapper_main(void *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    반환 0;
}

정수 avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads),
                              void (*main_func)(void *priv),
                              정수 nb_threads)
{
    정수 ret = avpriv_slicethread_create2(pctx, NULL, wrapper_worker,
                                         main_func ? wrapper_main : NULL,
                                         nb_threads);
    만약 (ret < 0)
        반환 ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    반환 ret;
}

void avpriv_slicethread_execute(AVSliceThread *ctx, 정수 nb_jobs, 정수 execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#아니면 /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

정수 avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               정수 (*worker_func)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads),
                               정수 (*main_func)(void *priv),
                               정수 nb_threads)
{
    *pctx = NULL;
    반환 AVERROR(ENOSYS);
}

정수 avpriv_slicethread_execute2(AVSliceThread *ctx, 정수 nb_jobs, 정수 execute_main)
{
    av_assert0(0);
}

void avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#만약 LIBAVUTIL_VERSION_MAJOR < 62

정수 avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, 정수 jobnr, 정수 threadnr, 정수 nb_jobs, 정수 nb_threads),
                              void (*main_func)(void *priv),
                              정수 nb_threads)
{
    *pctx = NULL;
    반환 AVERROR(ENOSYS);
}

void avpriv_slicethread_execute(AVSliceThread *ctx, 정수 nb_jobs, 정수 execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
