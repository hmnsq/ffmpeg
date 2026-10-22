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

#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "internal.h"
#அந்தர்பாவ "slicethread.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "thread.h"
#அந்தர்பாவ "avassert.h"

#define MAX_AUTO_THREADS 16

#எனில் HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

வகைவரை கட்டமைப்பு WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    முழு             done;
} WorkerContext;

கட்டமைப்பு AVSliceThread {
    WorkerContext   *workers;
    முழு             nb_threads;
    முழு             nb_active_threads;
    முழு             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    முழு             done;
    முழு             finished;
    atomic_int      error;

    வெறுமை            *priv;
    முழு            (*worker_func)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads);
    முழு            (*main_func)(வெறுமை *priv);

#எனில் LIBAVUTIL_VERSION_MAJOR < 62
    வெறுமை           (*worker_func_v1)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads);
    வெறுமை           (*main_func_v1)(வெறுமை *priv);
    வெறுமை            *priv_v1;
#endif
};

நிலையான முழு run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    செய் {
        முழு ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        எனில் (ret)
            தொடர்;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        எனில் (ret) {
            முழு prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } போது ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    திரும்பு current_job == nb_jobs + nb_active_threads - 1;
}

நிலையான வெறுமை *attribute_align_arg thread_worker(வெறுமை *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    போது (1) {
        w->done = 1;
        போது (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        எனில் (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            திரும்பு வெற்று;
        }

        எனில் (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
முழு avpriv_slicethread_create2(AVSliceThread **pctx, வெறுமை *priv,
                               முழு (*worker_func)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads),
                               முழு (*main_func)(வெறுமை *priv),
                               முழு nb_threads)
{
    AVSliceThread *ctx;
    முழு nb_workers, i;
    முழு ret;

    av_assert0(nb_threads >= 0);
    எனில் (!nb_threads) {
        முழு nb_cpus = av_cpu_மொத்தம்();
        எனில் (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        இல்லையெனில்
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    எனில் (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(அளவு(*ctx));
    எனில் (!ctx)
        திரும்பு AVERROR(ENOMEM);

    எனில் (nb_workers && !(ctx->workers = av_calloc(nb_workers, அளவு(*ctx->workers)))) {
        av_freep(pctx);
        திரும்பு AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, வெற்று);
    எனில் (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        திரும்பு AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, வெற்று);
    எனில் (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        திரும்பு AVERROR(ret);
    }
    ctx->done        = 0;

    க்கு (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, வெற்று);
        எனில் (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            திரும்பு AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, வெற்று);
        எனில் (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            திரும்பு AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        எனில் (ret = pthread_create(&w->thread, வெற்று, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            திரும்பு AVERROR(ret);
        }

        போது (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    திரும்பு nb_threads;
}

முழு avpriv_slicethread_execute2(AVSliceThread *ctx, முழு nb_jobs, முழு execute_main)
{
    முழு nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    எனில் (!ctx->main_func || !execute_main)
        nb_workers--;

    க்கு (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    எனில் (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } இல்லையெனில்
        is_last = run_jobs(ctx);

    எனில் (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        போது (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    எனில் (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    திரும்பு ret;
}

av_cold வெறுமை avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    முழு nb_workers, i;

    எனில் (!ctx)
        திரும்பு;

    nb_workers = ctx->nb_threads;
    எனில் (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    க்கு (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    க்கு (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, வெற்று);
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

#எனில் LIBAVUTIL_VERSION_MAJOR < 62

நிலையான முழு wrapper_worker(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    திரும்பு 0;
}

நிலையான முழு wrapper_main(வெறுமை *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    திரும்பு 0;
}

முழு avpriv_slicethread_create(AVSliceThread **pctx, வெறுமை *priv,
                              வெறுமை (*worker_func)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads),
                              வெறுமை (*main_func)(வெறுமை *priv),
                              முழு nb_threads)
{
    முழு ret = avpriv_slicethread_create2(pctx, வெற்று, wrapper_worker,
                                         main_func ? wrapper_main : வெற்று,
                                         nb_threads);
    எனில் (ret < 0)
        திரும்பு ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    திரும்பு ret;
}

வெறுமை avpriv_slicethread_execute(AVSliceThread *ctx, முழு nb_jobs, முழு execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#இல்லையெனில் /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

முழு avpriv_slicethread_create2(AVSliceThread **pctx, வெறுமை *priv,
                               முழு (*worker_func)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads),
                               முழு (*main_func)(வெறுமை *priv),
                               முழு nb_threads)
{
    *pctx = வெற்று;
    திரும்பு AVERROR(ENOSYS);
}

முழு avpriv_slicethread_execute2(AVSliceThread *ctx, முழு nb_jobs, முழு execute_main)
{
    av_assert0(0);
}

வெறுமை avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#எனில் LIBAVUTIL_VERSION_MAJOR < 62

முழு avpriv_slicethread_create(AVSliceThread **pctx, வெறுமை *priv,
                              வெறுமை (*worker_func)(வெறுமை *priv, முழு jobnr, முழு threadnr, முழு nb_jobs, முழு nb_threads),
                              வெறுமை (*main_func)(வெறுமை *priv),
                              முழு nb_threads)
{
    *pctx = வெற்று;
    திரும்பு AVERROR(ENOSYS);
}

வெறுமை avpriv_slicethread_execute(AVSliceThread *ctx, முழு nb_jobs, முழு execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
