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

#ប្រសិនបើ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

typedef sa_nracanaa WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    ចំនួនគត់             done;
} WorkerContext;

sa_nracanaa AVSliceThread {
    WorkerContext   *workers;
    ចំនួនគត់             nb_threads;
    ចំនួនគត់             nb_active_threads;
    ចំនួនគត់             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    ចំនួនគត់             done;
    ចំនួនគត់             finished;
    atomic_int      error;

    void            *priv;
    ចំនួនគត់            (*worker_func)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads);
    ចំនួនគត់            (*main_func)(void *priv);

#ប្រសិនបើ LIBAVUTIL_VERSION_MAJOR < 62
    void           (*worker_func_v1)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads);
    void           (*main_func_v1)(void *priv);
    void            *priv_v1;
#endif
};

static ចំនួនគត់ run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    do {
        ចំនួនគត់ ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ប្រសិនបើ (ret)
            continue;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        ប្រសិនបើ (ret) {
            ចំនួនគត់ prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ខណៈពេល ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ត្រឡប់ current_job == nb_jobs + nb_active_threads - 1;
}

static void *attribute_align_arg thread_worker(void *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    ខណៈពេល (1) {
        w->done = 1;
        ខណៈពេល (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        ប្រសិនបើ (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ត្រឡប់ NULL;
        }

        ប្រសិនបើ (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
ចំនួនគត់ avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               ចំនួនគត់ (*worker_func)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads),
                               ចំនួនគត់ (*main_func)(void *priv),
                               ចំនួនគត់ nb_threads)
{
    AVSliceThread *ctx;
    ចំនួនគត់ nb_workers, i;
    ចំនួនគត់ ret;

    av_assert0(nb_threads >= 0);
    ប្រសិនបើ (!nb_threads) {
        ចំនួនគត់ nb_cpus = av_cpu_count();
        ប្រសិនបើ (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        បើមិនដូច្នេះ
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    ប្រសិនបើ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(parimaa_na(*ctx));
    ប្រសិនបើ (!ctx)
        ត្រឡប់ AVERROR(ENOMEM);

    ប្រសិនបើ (nb_workers && !(ctx->workers = av_calloc(nb_workers, parimaa_na(*ctx->workers)))) {
        av_freep(pctx);
        ត្រឡប់ AVERROR(ENOMEM);
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
    ប្រសិនបើ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ត្រឡប់ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, NULL);
    ប្រសិនបើ (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ត្រឡប់ AVERROR(ret);
    }
    ctx->done        = 0;

    សម្រាប់ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, NULL);
        ប្រសិនបើ (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ត្រឡប់ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, NULL);
        ប្រសិនបើ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ត្រឡប់ AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        ប្រសិនបើ (ret = pthread_create(&w->thread, NULL, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ត្រឡប់ AVERROR(ret);
        }

        ខណៈពេល (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ត្រឡប់ nb_threads;
}

ចំនួនគត់ avpriv_slicethread_execute2(AVSliceThread *ctx, ចំនួនគត់ nb_jobs, ចំនួនគត់ execute_main)
{
    ចំនួនគត់ nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    ប្រសិនបើ (!ctx->main_func || !execute_main)
        nb_workers--;

    សម្រាប់ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ប្រសិនបើ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } បើមិនដូច្នេះ
        is_last = run_jobs(ctx);

    ប្រសិនបើ (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        ខណៈពេល (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    ប្រសិនបើ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ត្រឡប់ ret;
}

av_cold void avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    ចំនួនគត់ nb_workers, i;

    ប្រសិនបើ (!ctx)
        ត្រឡប់;

    nb_workers = ctx->nb_threads;
    ប្រសិនបើ (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    សម្រាប់ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    សម្រាប់ (i = 0; i < nb_workers; i++) {
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

#ប្រសិនបើ LIBAVUTIL_VERSION_MAJOR < 62

static ចំនួនគត់ wrapper_worker(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ត្រឡប់ 0;
}

static ចំនួនគត់ wrapper_main(void *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ត្រឡប់ 0;
}

ចំនួនគត់ avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads),
                              void (*main_func)(void *priv),
                              ចំនួនគត់ nb_threads)
{
    ចំនួនគត់ ret = avpriv_slicethread_create2(pctx, NULL, wrapper_worker,
                                         main_func ? wrapper_main : NULL,
                                         nb_threads);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ត្រឡប់ ret;
}

void avpriv_slicethread_execute(AVSliceThread *ctx, ចំនួនគត់ nb_jobs, ចំនួនគត់ execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#បើមិនដូច្នេះ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

ចំនួនគត់ avpriv_slicethread_create2(AVSliceThread **pctx, void *priv,
                               ចំនួនគត់ (*worker_func)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads),
                               ចំនួនគត់ (*main_func)(void *priv),
                               ចំនួនគត់ nb_threads)
{
    *pctx = NULL;
    ត្រឡប់ AVERROR(ENOSYS);
}

ចំនួនគត់ avpriv_slicethread_execute2(AVSliceThread *ctx, ចំនួនគត់ nb_jobs, ចំនួនគត់ execute_main)
{
    av_assert0(0);
}

void avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ប្រសិនបើ LIBAVUTIL_VERSION_MAJOR < 62

ចំនួនគត់ avpriv_slicethread_create(AVSliceThread **pctx, void *priv,
                              void (*worker_func)(void *priv, ចំនួនគត់ jobnr, ចំនួនគត់ threadnr, ចំនួនគត់ nb_jobs, ចំនួនគត់ nb_threads),
                              void (*main_func)(void *priv),
                              ចំនួនគត់ nb_threads)
{
    *pctx = NULL;
    ត្រឡប់ AVERROR(ENOSYS);
}

void avpriv_slicethread_execute(AVSliceThread *ctx, ចំនួនគត់ nb_jobs, ចំនួនគត់ execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
