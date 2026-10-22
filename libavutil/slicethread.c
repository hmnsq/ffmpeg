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

#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "internal.h"
#അന്തര്ഭാവ "slicethread.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "thread.h"
#അന്തര്ഭാവ "avassert.h"

#define MAX_AUTO_THREADS 16

#എങ്കിൽ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

തരനിർവചനം ഘടന WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    പൂർണ്ണസംഖ്യ             done;
} WorkerContext;

ഘടന AVSliceThread {
    WorkerContext   *workers;
    പൂർണ്ണസംഖ്യ             nb_threads;
    പൂർണ്ണസംഖ്യ             nb_active_threads;
    പൂർണ്ണസംഖ്യ             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    പൂർണ്ണസംഖ്യ             done;
    പൂർണ്ണസംഖ്യ             finished;
    atomic_int      error;

    ശൂന്യം            *priv;
    പൂർണ്ണസംഖ്യ            (*worker_func)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads);
    പൂർണ്ണസംഖ്യ            (*main_func)(ശൂന്യം *priv);

#എങ്കിൽ LIBAVUTIL_VERSION_MAJOR < 62
    ശൂന്യം           (*worker_func_v1)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads);
    ശൂന്യം           (*main_func_v1)(ശൂന്യം *priv);
    ശൂന്യം            *priv_v1;
#endif
};

സ്ഥിതം പൂർണ്ണസംഖ്യ run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    ചെയ്യുക {
        പൂർണ്ണസംഖ്യ ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        എങ്കിൽ (ret)
            തുടരുക;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        എങ്കിൽ (ret) {
            പൂർണ്ണസംഖ്യ prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ആകുമ്പോൾ ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    തിരികെ current_job == nb_jobs + nb_active_threads - 1;
}

സ്ഥിതം ശൂന്യം *attribute_align_arg thread_worker(ശൂന്യം *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    ആകുമ്പോൾ (1) {
        w->done = 1;
        ആകുമ്പോൾ (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        എങ്കിൽ (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            തിരികെ ശൂന്യ;
        }

        എങ്കിൽ (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
പൂർണ്ണസംഖ്യ avpriv_slicethread_create2(AVSliceThread **pctx, ശൂന്യം *priv,
                               പൂർണ്ണസംഖ്യ (*worker_func)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads),
                               പൂർണ്ണസംഖ്യ (*main_func)(ശൂന്യം *priv),
                               പൂർണ്ണസംഖ്യ nb_threads)
{
    AVSliceThread *ctx;
    പൂർണ്ണസംഖ്യ nb_workers, i;
    പൂർണ്ണസംഖ്യ ret;

    av_assert0(nb_threads >= 0);
    എങ്കിൽ (!nb_threads) {
        പൂർണ്ണസംഖ്യ nb_cpus = av_cpu_എണ്ണം();
        എങ്കിൽ (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        അല്ലെങ്കിൽ
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    എങ്കിൽ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(വലുപ്പം(*ctx));
    എങ്കിൽ (!ctx)
        തിരികെ AVERROR(ENOMEM);

    എങ്കിൽ (nb_workers && !(ctx->workers = av_calloc(nb_workers, വലുപ്പം(*ctx->workers)))) {
        av_freep(pctx);
        തിരികെ AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, ശൂന്യ);
    എങ്കിൽ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        തിരികെ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, ശൂന്യ);
    എങ്കിൽ (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        തിരികെ AVERROR(ret);
    }
    ctx->done        = 0;

    വേണ്ടി (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ശൂന്യ);
        എങ്കിൽ (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            തിരികെ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ശൂന്യ);
        എങ്കിൽ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            തിരികെ AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        എങ്കിൽ (ret = pthread_create(&w->thread, ശൂന്യ, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            തിരികെ AVERROR(ret);
        }

        ആകുമ്പോൾ (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    തിരികെ nb_threads;
}

പൂർണ്ണസംഖ്യ avpriv_slicethread_execute2(AVSliceThread *ctx, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ execute_main)
{
    പൂർണ്ണസംഖ്യ nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    എങ്കിൽ (!ctx->main_func || !execute_main)
        nb_workers--;

    വേണ്ടി (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    എങ്കിൽ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } അല്ലെങ്കിൽ
        is_last = run_jobs(ctx);

    എങ്കിൽ (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        ആകുമ്പോൾ (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    എങ്കിൽ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    തിരികെ ret;
}

av_cold ശൂന്യം avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    പൂർണ്ണസംഖ്യ nb_workers, i;

    എങ്കിൽ (!ctx)
        തിരികെ;

    nb_workers = ctx->nb_threads;
    എങ്കിൽ (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    വേണ്ടി (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    വേണ്ടി (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, ശൂന്യ);
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

#എങ്കിൽ LIBAVUTIL_VERSION_MAJOR < 62

സ്ഥിതം പൂർണ്ണസംഖ്യ wrapper_worker(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ wrapper_main(ശൂന്യം *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ avpriv_slicethread_create(AVSliceThread **pctx, ശൂന്യം *priv,
                              ശൂന്യം (*worker_func)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads),
                              ശൂന്യം (*main_func)(ശൂന്യം *priv),
                              പൂർണ്ണസംഖ്യ nb_threads)
{
    പൂർണ്ണസംഖ്യ ret = avpriv_slicethread_create2(pctx, ശൂന്യ, wrapper_worker,
                                         main_func ? wrapper_main : ശൂന്യ,
                                         nb_threads);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    തിരികെ ret;
}

ശൂന്യം avpriv_slicethread_execute(AVSliceThread *ctx, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#അല്ലെങ്കിൽ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

പൂർണ്ണസംഖ്യ avpriv_slicethread_create2(AVSliceThread **pctx, ശൂന്യം *priv,
                               പൂർണ്ണസംഖ്യ (*worker_func)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads),
                               പൂർണ്ണസംഖ്യ (*main_func)(ശൂന്യം *priv),
                               പൂർണ്ണസംഖ്യ nb_threads)
{
    *pctx = ശൂന്യ;
    തിരികെ AVERROR(ENOSYS);
}

പൂർണ്ണസംഖ്യ avpriv_slicethread_execute2(AVSliceThread *ctx, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ execute_main)
{
    av_assert0(0);
}

ശൂന്യം avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#എങ്കിൽ LIBAVUTIL_VERSION_MAJOR < 62

പൂർണ്ണസംഖ്യ avpriv_slicethread_create(AVSliceThread **pctx, ശൂന്യം *priv,
                              ശൂന്യം (*worker_func)(ശൂന്യം *priv, പൂർണ്ണസംഖ്യ jobnr, പൂർണ്ണസംഖ്യ threadnr, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ nb_threads),
                              ശൂന്യം (*main_func)(ശൂന്യം *priv),
                              പൂർണ്ണസംഖ്യ nb_threads)
{
    *pctx = ശൂന്യ;
    തിരികെ AVERROR(ENOSYS);
}

ശൂന്യം avpriv_slicethread_execute(AVSliceThread *ctx, പൂർണ്ണസംഖ്യ nb_jobs, പൂർണ്ണസംഖ്യ execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
