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

#ضمن <stdatomic.h>
#ضمن "cpu.h"
#ضمن "internal.h"
#ضمن "slicethread.h"
#ضمن "mem.h"
#ضمن "thread.h"
#ضمن "avassert.h"

#define MAX_AUTO_THREADS 16

#إذا HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

تعريفنوع بنية WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحيح             done;
} WorkerContext;

بنية AVSliceThread {
    WorkerContext   *workers;
    صحيح             nb_threads;
    صحيح             nb_active_threads;
    صحيح             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    صحيح             done;
    صحيح             finished;
    atomic_int      error;

    فراغ            *priv;
    صحيح            (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads);
    صحيح            (*main_func)(فراغ *priv);

#إذا LIBAVUTIL_VERSION_MAJOR < 62
    فراغ           (*worker_func_v1)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads);
    فراغ           (*main_func_v1)(فراغ *priv);
    فراغ            *priv_v1;
#endif
};

ساكن صحيح run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    افعل {
        صحيح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        إذا (ret)
            استمر;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        إذا (ret) {
            صحيح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } بينما ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    إرجاع current_job == nb_jobs + nb_active_threads - 1;
}

ساكن فراغ *attribute_align_arg thread_worker(فراغ *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    بينما (1) {
        w->done = 1;
        بينما (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        إذا (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            إرجاع عدم;
        }

        إذا (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_threads)
{
    AVSliceThread *ctx;
    صحيح nb_workers, i;
    صحيح ret;

    av_assert0(nb_threads >= 0);
    إذا (!nb_threads) {
        صحيح nb_cpus = av_cpu_تعداد();
        إذا (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        وإلا
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    إذا (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(حجم(*ctx));
    إذا (!ctx)
        إرجاع AVERROR(ENOMEM);

    إذا (nb_workers && !(ctx->workers = av_calloc(nb_workers, حجم(*ctx->workers)))) {
        av_freep(pctx);
        إرجاع AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, عدم);
    إذا (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        إرجاع AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, عدم);
    إذا (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        إرجاع AVERROR(ret);
    }
    ctx->done        = 0;

    لكل (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, عدم);
        إذا (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            إرجاع AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, عدم);
        إذا (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            إرجاع AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        إذا (ret = pthread_create(&w->thread, عدم, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            إرجاع AVERROR(ret);
        }

        بينما (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    إرجاع nb_threads;
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    صحيح nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    إذا (!ctx->main_func || !execute_main)
        nb_workers--;

    لكل (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    إذا (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وإلا
        is_last = run_jobs(ctx);

    إذا (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        بينما (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    إذا (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    إرجاع ret;
}

av_cold فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    صحيح nb_workers, i;

    إذا (!ctx)
        إرجاع;

    nb_workers = ctx->nb_threads;
    إذا (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    لكل (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    لكل (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, عدم);
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

#إذا LIBAVUTIL_VERSION_MAJOR < 62

ساكن صحيح wrapper_worker(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    إرجاع 0;
}

ساكن صحيح wrapper_main(فراغ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    إرجاع 0;
}

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_threads)
{
    صحيح ret = avpriv_slicethread_create2(pctx, عدم, wrapper_worker,
                                         main_func ? wrapper_main : عدم,
                                         nb_threads);
    إذا (ret < 0)
        إرجاع ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    إرجاع ret;
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وإلا /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_threads)
{
    *pctx = عدم;
    إرجاع AVERROR(ENOSYS);
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#إذا LIBAVUTIL_VERSION_MAJOR < 62

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_threads)
{
    *pctx = عدم;
    إرجاع AVERROR(ENOSYS);
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
