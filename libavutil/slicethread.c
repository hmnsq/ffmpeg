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

#অন্তর্ভাৱ <stdatomic.h>
#অন্তর্ভাৱ "cpu.h"
#অন্তর্ভাৱ "internal.h"
#অন্তর্ভাৱ "slicethread.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "thread.h"
#অন্তর্ভাৱ "avassert.h"

#define MAX_AUTO_THREADS 16

#যদি HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

প্রকারনির্দেশ সংরচনা WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    পূর্ণাঙ্ক             done;
} WorkerContext;

সংরচনা AVSliceThread {
    WorkerContext   *workers;
    পূর্ণাঙ্ক             nb_threads;
    পূর্ণাঙ্ক             nb_active_threads;
    পূর্ণাঙ্ক             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    পূর্ণাঙ্ক             done;
    পূর্ণাঙ্ক             finished;
    atomic_int      error;

    শূন্য            *priv;
    পূর্ণাঙ্ক            (*worker_func)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads);
    পূর্ণাঙ্ক            (*main_func)(শূন্য *priv);

#যদি LIBAVUTIL_VERSION_MAJOR < 62
    শূন্য           (*worker_func_v1)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads);
    শূন্য           (*main_func_v1)(শূন্য *priv);
    শূন্য            *priv_v1;
#endif
};

স্থির পূর্ণাঙ্ক run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    কৰা {
        পূর্ণাঙ্ক ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        যদি (ret)
            অনুৱর্ত;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        যদি (ret) {
            পূর্ণাঙ্ক prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } যেতিয়ালৈ ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ঘূৰাই current_job == nb_jobs + nb_active_threads - 1;
}

স্থির শূন্য *attribute_align_arg thread_worker(শূন্য *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    যেতিয়ালৈ (1) {
        w->done = 1;
        যেতিয়ালৈ (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        যদি (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ঘূৰাই রিক্ত;
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
পূর্ণাঙ্ক avpriv_slicethread_create2(AVSliceThread **pctx, শূন্য *priv,
                               পূর্ণাঙ্ক (*worker_func)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads),
                               পূর্ণাঙ্ক (*main_func)(শূন্য *priv),
                               পূর্ণাঙ্ক nb_threads)
{
    AVSliceThread *ctx;
    পূর্ণাঙ্ক nb_workers, i;
    পূর্ণাঙ্ক ret;

    av_assert0(nb_threads >= 0);
    যদি (!nb_threads) {
        পূর্ণাঙ্ক nb_cpus = av_cpu_গুনতি();
        যদি (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        অন্যথা
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    যদি (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(পরিমাণ(*ctx));
    যদি (!ctx)
        ঘূৰাই AVERROR(ENOMEM);

    যদি (nb_workers && !(ctx->workers = av_calloc(nb_workers, পরিমাণ(*ctx->workers)))) {
        av_freep(pctx);
        ঘূৰাই AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, রিক্ত);
    যদি (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ঘূৰাই AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, রিক্ত);
    যদি (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ঘূৰাই AVERROR(ret);
    }
    ctx->done        = 0;

    বাবে (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, রিক্ত);
        যদি (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ঘূৰাই AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, রিক্ত);
        যদি (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ঘূৰাই AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        যদি (ret = pthread_create(&w->thread, রিক্ত, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ঘূৰাই AVERROR(ret);
        }

        যেতিয়ালৈ (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ঘূৰাই nb_threads;
}

পূর্ণাঙ্ক avpriv_slicethread_execute2(AVSliceThread *ctx, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক execute_main)
{
    পূর্ণাঙ্ক nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    যদি (!ctx->main_func || !execute_main)
        nb_workers--;

    বাবে (i = 0; i < nb_workers; i++) {
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
        যেতিয়ালৈ (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    যদি (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ঘূৰাই ret;
}

av_cold শূন্য avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    পূর্ণাঙ্ক nb_workers, i;

    যদি (!ctx)
        ঘূৰাই;

    nb_workers = ctx->nb_threads;
    যদি (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    বাবে (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    বাবে (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, রিক্ত);
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

স্থির পূর্ণাঙ্ক wrapper_worker(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক wrapper_main(শূন্য *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ঘূৰাই 0;
}

পূর্ণাঙ্ক avpriv_slicethread_create(AVSliceThread **pctx, শূন্য *priv,
                              শূন্য (*worker_func)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads),
                              শূন্য (*main_func)(শূন্য *priv),
                              পূর্ণাঙ্ক nb_threads)
{
    পূর্ণাঙ্ক ret = avpriv_slicethread_create2(pctx, রিক্ত, wrapper_worker,
                                         main_func ? wrapper_main : রিক্ত,
                                         nb_threads);
    যদি (ret < 0)
        ঘূৰাই ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ঘূৰাই ret;
}

শূন্য avpriv_slicethread_execute(AVSliceThread *ctx, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#অন্যথা /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

পূর্ণাঙ্ক avpriv_slicethread_create2(AVSliceThread **pctx, শূন্য *priv,
                               পূর্ণাঙ্ক (*worker_func)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads),
                               পূর্ণাঙ্ক (*main_func)(শূন্য *priv),
                               পূর্ণাঙ্ক nb_threads)
{
    *pctx = রিক্ত;
    ঘূৰাই AVERROR(ENOSYS);
}

পূর্ণাঙ্ক avpriv_slicethread_execute2(AVSliceThread *ctx, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক execute_main)
{
    av_assert0(0);
}

শূন্য avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#যদি LIBAVUTIL_VERSION_MAJOR < 62

পূর্ণাঙ্ক avpriv_slicethread_create(AVSliceThread **pctx, শূন্য *priv,
                              শূন্য (*worker_func)(শূন্য *priv, পূর্ণাঙ্ক jobnr, পূর্ণাঙ্ক threadnr, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক nb_threads),
                              শূন্য (*main_func)(শূন্য *priv),
                              পূর্ণাঙ্ক nb_threads)
{
    *pctx = রিক্ত;
    ঘূৰাই AVERROR(ENOSYS);
}

শূন্য avpriv_slicethread_execute(AVSliceThread *ctx, পূর্ণাঙ্ক nb_jobs, পূর্ণাঙ্ক execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
