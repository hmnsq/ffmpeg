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

#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব "cpu.h"
#অন্তর্ভাব "internal.h"
#অন্তর্ভাব "slicethread.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "avassert.h"

#define MAX_AUTO_THREADS 16

#যদি HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

প্রকারলেখ কাঠামো WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    পূর্ণসংখ্যা             done;
} WorkerContext;

কাঠামো AVSliceThread {
    WorkerContext   *workers;
    পূর্ণসংখ্যা             nb_threads;
    পূর্ণসংখ্যা             nb_active_threads;
    পূর্ণসংখ্যা             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    পূর্ণসংখ্যা             done;
    পূর্ণসংখ্যা             finished;
    atomic_int      error;

    শূন্য            *priv;
    পূর্ণসংখ্যা            (*worker_func)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads);
    পূর্ণসংখ্যা            (*main_func)(শূন্য *priv);

#যদি LIBAVUTIL_VERSION_MAJOR < 62
    শূন্য           (*worker_func_v1)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads);
    শূন্য           (*main_func_v1)(শূন্য *priv);
    শূন্য            *priv_v1;
#endif
};

স্থির পূর্ণসংখ্যা run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    করো {
        পূর্ণসংখ্যা ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        যদি (ret)
            চালু;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        যদি (ret) {
            পূর্ণসংখ্যা পূর্ব = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &পূর্ব, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } যখন ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ফেরত current_job == nb_jobs + nb_active_threads - 1;
}

স্থির শূন্য *attribute_align_arg thread_worker(শূন্য *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    যখন (1) {
        w->done = 1;
        যখন (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        যদি (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ফেরত ফাঁকা;
        }

        যদি (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
পূর্ণসংখ্যা avpriv_slicethread_create2(AVSliceThread **pctx, শূন্য *priv,
                               পূর্ণসংখ্যা (*worker_func)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads),
                               পূর্ণসংখ্যা (*main_func)(শূন্য *priv),
                               পূর্ণসংখ্যা nb_threads)
{
    AVSliceThread *ctx;
    পূর্ণসংখ্যা nb_workers, i;
    পূর্ণসংখ্যা ret;

    av_assert0(nb_threads >= 0);
    যদি (!nb_threads) {
        পূর্ণসংখ্যা nb_cpus = av_cpu_গুনতি();
        যদি (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        অন্যথা
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    যদি (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(আকার(*ctx));
    যদি (!ctx)
        ফেরত AVERROR(ENOMEM);

    যদি (nb_workers && !(ctx->workers = av_calloc(nb_workers, আকার(*ctx->workers)))) {
        av_freep(pctx);
        ফেরত AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, ফাঁকা);
    যদি (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ফেরত AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, ফাঁকা);
    যদি (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ফেরত AVERROR(ret);
    }
    ctx->done        = 0;

    জন্য (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ফাঁকা);
        যদি (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ফেরত AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ফাঁকা);
        যদি (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ফেরত AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        যদি (ret = pthread_create(&w->thread, ফাঁকা, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ফেরত AVERROR(ret);
        }

        যখন (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ফেরত nb_threads;
}

পূর্ণসংখ্যা avpriv_slicethread_execute2(AVSliceThread *ctx, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা execute_main)
{
    পূর্ণসংখ্যা nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    যদি (!ctx->main_func || !execute_main)
        nb_workers--;

    জন্য (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    যদি (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } অন্যথা
        is_last = run_jobs(ctx);

    যদি (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        যখন (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    যদি (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ফেরত ret;
}

av_cold শূন্য avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    পূর্ণসংখ্যা nb_workers, i;

    যদি (!ctx)
        ফেরত;

    nb_workers = ctx->nb_threads;
    যদি (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    জন্য (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    জন্য (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, ফাঁকা);
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

#যদি LIBAVUTIL_VERSION_MAJOR < 62

স্থির পূর্ণসংখ্যা wrapper_worker(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা wrapper_main(শূন্য *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ফেরত 0;
}

পূর্ণসংখ্যা avpriv_slicethread_create(AVSliceThread **pctx, শূন্য *priv,
                              শূন্য (*worker_func)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads),
                              শূন্য (*main_func)(শূন্য *priv),
                              পূর্ণসংখ্যা nb_threads)
{
    পূর্ণসংখ্যা ret = avpriv_slicethread_create2(pctx, ফাঁকা, wrapper_worker,
                                         main_func ? wrapper_main : ফাঁকা,
                                         nb_threads);
    যদি (ret < 0)
        ফেরত ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ফেরত ret;
}

শূন্য avpriv_slicethread_execute(AVSliceThread *ctx, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#অন্যথা /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

পূর্ণসংখ্যা avpriv_slicethread_create2(AVSliceThread **pctx, শূন্য *priv,
                               পূর্ণসংখ্যা (*worker_func)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads),
                               পূর্ণসংখ্যা (*main_func)(শূন্য *priv),
                               পূর্ণসংখ্যা nb_threads)
{
    *pctx = ফাঁকা;
    ফেরত AVERROR(ENOSYS);
}

পূর্ণসংখ্যা avpriv_slicethread_execute2(AVSliceThread *ctx, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা execute_main)
{
    av_assert0(0);
}

শূন্য avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#যদি LIBAVUTIL_VERSION_MAJOR < 62

পূর্ণসংখ্যা avpriv_slicethread_create(AVSliceThread **pctx, শূন্য *priv,
                              শূন্য (*worker_func)(শূন্য *priv, পূর্ণসংখ্যা jobnr, পূর্ণসংখ্যা threadnr, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা nb_threads),
                              শূন্য (*main_func)(শূন্য *priv),
                              পূর্ণসংখ্যা nb_threads)
{
    *pctx = ফাঁকা;
    ফেরত AVERROR(ENOSYS);
}

শূন্য avpriv_slicethread_execute(AVSliceThread *ctx, পূর্ণসংখ্যা nb_jobs, পূর্ণসংখ্যা execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
