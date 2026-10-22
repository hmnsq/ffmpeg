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

#شامل <stdatomic.h>
#شامل "cpu.h"
#شامل "internal.h"
#شامل "slicethread.h"
#شامل "mem.h"
#شامل "thread.h"
#شامل "avassert.h"

#define MAX_AUTO_THREADS 16

#اگر HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

تعریفنوع ساختار WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحیح             done;
} WorkerContext;

ساختار AVSliceThread {
    WorkerContext   *workers;
    صحیح             nb_threads;
    صحیح             nb_active_threads;
    صحیح             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    صحیح             done;
    صحیح             finished;
    atomic_int      error;

    تهی            *priv;
    صحیح            (*worker_func)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads);
    صحیح            (*main_func)(تهی *priv);

#اگر LIBAVUTIL_VERSION_MAJOR < 62
    تهی           (*worker_func_v1)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads);
    تهی           (*main_func_v1)(تهی *priv);
    تهی            *priv_v1;
#endif
};

ایستا صحیح run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    انجامبده {
        صحیح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        اگر (ret)
            ادامه;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        اگر (ret) {
            صحیح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } وقتی ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    بازگشت current_job == nb_jobs + nb_active_threads - 1;
}

ایستا تهی *attribute_align_arg thread_worker(تهی *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    وقتی (1) {
        w->done = 1;
        وقتی (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        اگر (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            بازگشت پوچ;
        }

        اگر (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
صحیح avpriv_slicethread_create2(AVSliceThread **pctx, تهی *priv,
                               صحیح (*worker_func)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads),
                               صحیح (*main_func)(تهی *priv),
                               صحیح nb_threads)
{
    AVSliceThread *ctx;
    صحیح nb_workers, i;
    صحیح ret;

    av_assert0(nb_threads >= 0);
    اگر (!nb_threads) {
        صحیح nb_cpus = av_cpu_شمار();
        اگر (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        وگرنه
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    اگر (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(اندازه(*ctx));
    اگر (!ctx)
        بازگشت AVERROR(ENOMEM);

    اگر (nb_workers && !(ctx->workers = av_calloc(nb_workers, اندازه(*ctx->workers)))) {
        av_freep(pctx);
        بازگشت AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, پوچ);
    اگر (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        بازگشت AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, پوچ);
    اگر (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        بازگشت AVERROR(ret);
    }
    ctx->done        = 0;

    برای (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, پوچ);
        اگر (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            بازگشت AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, پوچ);
        اگر (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            بازگشت AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        اگر (ret = pthread_create(&w->thread, پوچ, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            بازگشت AVERROR(ret);
        }

        وقتی (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    بازگشت nb_threads;
}

صحیح avpriv_slicethread_execute2(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    صحیح nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    اگر (!ctx->main_func || !execute_main)
        nb_workers--;

    برای (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    اگر (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وگرنه
        is_last = run_jobs(ctx);

    اگر (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        وقتی (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    اگر (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    بازگشت ret;
}

av_cold تهی avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    صحیح nb_workers, i;

    اگر (!ctx)
        بازگشت;

    nb_workers = ctx->nb_threads;
    اگر (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    برای (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    برای (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, پوچ);
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

#اگر LIBAVUTIL_VERSION_MAJOR < 62

ایستا صحیح wrapper_worker(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    بازگشت 0;
}

ایستا صحیح wrapper_main(تهی *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    بازگشت 0;
}

صحیح avpriv_slicethread_create(AVSliceThread **pctx, تهی *priv,
                              تهی (*worker_func)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads),
                              تهی (*main_func)(تهی *priv),
                              صحیح nb_threads)
{
    صحیح ret = avpriv_slicethread_create2(pctx, پوچ, wrapper_worker,
                                         main_func ? wrapper_main : پوچ,
                                         nb_threads);
    اگر (ret < 0)
        بازگشت ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    بازگشت ret;
}

تهی avpriv_slicethread_execute(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وگرنه /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحیح avpriv_slicethread_create2(AVSliceThread **pctx, تهی *priv,
                               صحیح (*worker_func)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads),
                               صحیح (*main_func)(تهی *priv),
                               صحیح nb_threads)
{
    *pctx = پوچ;
    بازگشت AVERROR(ENOSYS);
}

صحیح avpriv_slicethread_execute2(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    av_assert0(0);
}

تهی avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#اگر LIBAVUTIL_VERSION_MAJOR < 62

صحیح avpriv_slicethread_create(AVSliceThread **pctx, تهی *priv,
                              تهی (*worker_func)(تهی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_threads),
                              تهی (*main_func)(تهی *priv),
                              صحیح nb_threads)
{
    *pctx = پوچ;
    بازگشت AVERROR(ENOSYS);
}

تهی avpriv_slicethread_execute(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
