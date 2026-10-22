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

#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ "internal.h"
#ଅନ୍ତର୍ଭାଵ "slicethread.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"

#define MAX_AUTO_THREADS 16

#ଯଦି HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             done;
} WorkerContext;

ସଂରଚନା AVSliceThread {
    WorkerContext   *workers;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             nb_threads;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             nb_active_threads;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             done;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             finished;
    atomic_int      error;

    ଶୂନ୍ୟ            *priv;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା            (*worker_func)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା            (*main_func)(ଶୂନ୍ୟ *priv);

#ଯଦି LIBAVUTIL_VERSION_MAJOR < 62
    ଶୂନ୍ୟ           (*worker_func_v1)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads);
    ଶୂନ୍ୟ           (*main_func_v1)(ଶୂନ୍ୟ *priv);
    ଶୂନ୍ୟ            *priv_v1;
#endif
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    କର {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ଯଦି (ret)
            ଜାରି;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        ଯଦି (ret) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } ଯେତେବେଳେ ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    ଫେରନ୍ତୁ current_job == nb_jobs + nb_active_threads - 1;
}

ସ୍ଥିର ଶୂନ୍ୟ *attribute_align_arg thread_worker(ଶୂନ୍ୟ *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    ଯେତେବେଳେ (1) {
        w->done = 1;
        ଯେତେବେଳେ (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        ଯଦି (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        ଯଦି (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_create2(AVSliceThread **pctx, ଶୂନ୍ୟ *priv,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*worker_func)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads),
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*main_func)(ଶୂନ୍ୟ *priv),
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads)
{
    AVSliceThread *ctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_workers, i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    av_assert0(nb_threads >= 0);
    ଯଦି (!nb_threads) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_cpus = av_cpu_ଗଣନା();
        ଯଦି (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        ଅନ୍ୟଥା
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    ଯଦି (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(ଆକାର(*ctx));
    ଯଦି (!ctx)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (nb_workers && !(ctx->workers = av_calloc(nb_workers, ଆକାର(*ctx->workers)))) {
        av_freep(pctx);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, ଖାଲି);
    ଯଦି (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        ଫେରନ୍ତୁ AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, ଖାଲି);
    ଯଦି (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        ଫେରନ୍ତୁ AVERROR(ret);
    }
    ctx->done        = 0;

    ପାଇଁ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ଖାଲି);
        ଯଦି (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ଫେରନ୍ତୁ AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ଖାଲି);
        ଯଦି (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            ଫେରନ୍ତୁ AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        ଯଦି (ret = pthread_create(&w->thread, ଖାଲି, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            ଫେରନ୍ତୁ AVERROR(ret);
        }

        ଯେତେବେଳେ (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    ଫେରନ୍ତୁ nb_threads;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_execute2(AVSliceThread *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା execute_main)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    ଯଦି (!ctx->main_func || !execute_main)
        nb_workers--;

    ପାଇଁ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ଯଦି (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ଅନ୍ୟଥା
        is_last = run_jobs(ctx);

    ଯଦି (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        ଯେତେବେଳେ (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    ଯଦି (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    ଫେରନ୍ତୁ ret;
}

av_cold ଶୂନ୍ୟ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_workers, i;

    ଯଦି (!ctx)
        ଫେରନ୍ତୁ;

    nb_workers = ctx->nb_threads;
    ଯଦି (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    ପାଇଁ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ପାଇଁ (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, ଖାଲି);
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

#ଯଦି LIBAVUTIL_VERSION_MAJOR < 62

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା wrapper_worker(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା wrapper_main(ଶୂନ୍ୟ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_create(AVSliceThread **pctx, ଶୂନ୍ୟ *priv,
                              ଶୂନ୍ୟ (*worker_func)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads),
                              ଶୂନ୍ୟ (*main_func)(ଶୂନ୍ୟ *priv),
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = avpriv_slicethread_create2(pctx, ଖାଲି, wrapper_worker,
                                         main_func ? wrapper_main : ଖାଲି,
                                         nb_threads);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ avpriv_slicethread_execute(AVSliceThread *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ଅନ୍ୟଥା /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_create2(AVSliceThread **pctx, ଶୂନ୍ୟ *priv,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*worker_func)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads),
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*main_func)(ଶୂନ୍ୟ *priv),
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads)
{
    *pctx = ଖାଲି;
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_execute2(AVSliceThread *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା execute_main)
{
    av_assert0(0);
}

ଶୂନ୍ୟ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ଯଦି LIBAVUTIL_VERSION_MAJOR < 62

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_slicethread_create(AVSliceThread **pctx, ଶୂନ୍ୟ *priv,
                              ଶୂନ୍ୟ (*worker_func)(ଶୂନ୍ୟ *priv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା jobnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା threadnr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads),
                              ଶୂନ୍ୟ (*main_func)(ଶୂନ୍ୟ *priv),
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_threads)
{
    *pctx = ଖାଲି;
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ଶୂନ୍ୟ avpriv_slicethread_execute(AVSliceThread *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_jobs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
