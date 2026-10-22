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

#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ "cpu.h"
#અન્તર્ભાવ "internal.h"
#અન્તર્ભાવ "slicethread.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "thread.h"
#અન્તર્ભાવ "avassert.h"

#define MAX_AUTO_THREADS 16

#જો HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

પ્રકારવ્યાખ્યા સંરચના WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    પૂર્ણાંક             done;
} WorkerContext;

સંરચના AVSliceThread {
    WorkerContext   *workers;
    પૂર્ણાંક             nb_threads;
    પૂર્ણાંક             nb_active_threads;
    પૂર્ણાંક             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    પૂર્ણાંક             done;
    પૂર્ણાંક             finished;
    atomic_int      error;

    શૂન્ય            *priv;
    પૂર્ણાંક            (*worker_func)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads);
    પૂર્ણાંક            (*main_func)(શૂન્ય *priv);

#જો LIBAVUTIL_VERSION_MAJOR < 62
    શૂન્ય           (*worker_func_v1)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads);
    શૂન્ય           (*main_func_v1)(શૂન્ય *priv);
    શૂન્ય            *priv_v1;
#endif
};

સ્થિર પૂર્ણાંક run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    કરો {
        પૂર્ણાંક ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        જો (ret)
            ચાલુ;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        જો (ret) {
            પૂર્ણાંક prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } જ્યારે ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    પાછા current_job == nb_jobs + nb_active_threads - 1;
}

સ્થિર શૂન્ય *attribute_align_arg thread_worker(શૂન્ય *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    જ્યારે (1) {
        w->done = 1;
        જ્યારે (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        જો (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            પાછા ખાલી;
        }

        જો (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
પૂર્ણાંક avpriv_slicethread_create2(AVSliceThread **pctx, શૂન્ય *priv,
                               પૂર્ણાંક (*worker_func)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads),
                               પૂર્ણાંક (*main_func)(શૂન્ય *priv),
                               પૂર્ણાંક nb_threads)
{
    AVSliceThread *ctx;
    પૂર્ણાંક nb_workers, i;
    પૂર્ણાંક ret;

    av_assert0(nb_threads >= 0);
    જો (!nb_threads) {
        પૂર્ણાંક nb_cpus = av_cpu_ગણતરી();
        જો (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        નહીંતર
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    જો (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(કદ(*ctx));
    જો (!ctx)
        પાછા AVERROR(ENOMEM);

    જો (nb_workers && !(ctx->workers = av_calloc(nb_workers, કદ(*ctx->workers)))) {
        av_freep(pctx);
        પાછા AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, ખાલી);
    જો (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        પાછા AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, ખાલી);
    જો (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        પાછા AVERROR(ret);
    }
    ctx->done        = 0;

    માટે (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ખાલી);
        જો (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            પાછા AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ખાલી);
        જો (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            પાછા AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        જો (ret = pthread_create(&w->thread, ખાલી, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            પાછા AVERROR(ret);
        }

        જ્યારે (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    પાછા nb_threads;
}

પૂર્ણાંક avpriv_slicethread_execute2(AVSliceThread *ctx, પૂર્ણાંક nb_jobs, પૂર્ણાંક execute_main)
{
    પૂર્ણાંક nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    જો (!ctx->main_func || !execute_main)
        nb_workers--;

    માટે (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    જો (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } નહીંતર
        is_last = run_jobs(ctx);

    જો (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        જ્યારે (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    જો (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    પાછા ret;
}

av_cold શૂન્ય avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    પૂર્ણાંક nb_workers, i;

    જો (!ctx)
        પાછા;

    nb_workers = ctx->nb_threads;
    જો (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    માટે (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    માટે (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, ખાલી);
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

#જો LIBAVUTIL_VERSION_MAJOR < 62

સ્થિર પૂર્ણાંક wrapper_worker(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    પાછા 0;
}

સ્થિર પૂર્ણાંક wrapper_main(શૂન્ય *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    પાછા 0;
}

પૂર્ણાંક avpriv_slicethread_create(AVSliceThread **pctx, શૂન્ય *priv,
                              શૂન્ય (*worker_func)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads),
                              શૂન્ય (*main_func)(શૂન્ય *priv),
                              પૂર્ણાંક nb_threads)
{
    પૂર્ણાંક ret = avpriv_slicethread_create2(pctx, ખાલી, wrapper_worker,
                                         main_func ? wrapper_main : ખાલી,
                                         nb_threads);
    જો (ret < 0)
        પાછા ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    પાછા ret;
}

શૂન્ય avpriv_slicethread_execute(AVSliceThread *ctx, પૂર્ણાંક nb_jobs, પૂર્ણાંક execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#નહીંતર /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

પૂર્ણાંક avpriv_slicethread_create2(AVSliceThread **pctx, શૂન્ય *priv,
                               પૂર્ણાંક (*worker_func)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads),
                               પૂર્ણાંક (*main_func)(શૂન્ય *priv),
                               પૂર્ણાંક nb_threads)
{
    *pctx = ખાલી;
    પાછા AVERROR(ENOSYS);
}

પૂર્ણાંક avpriv_slicethread_execute2(AVSliceThread *ctx, પૂર્ણાંક nb_jobs, પૂર્ણાંક execute_main)
{
    av_assert0(0);
}

શૂન્ય avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#જો LIBAVUTIL_VERSION_MAJOR < 62

પૂર્ણાંક avpriv_slicethread_create(AVSliceThread **pctx, શૂન્ય *priv,
                              શૂન્ય (*worker_func)(શૂન્ય *priv, પૂર્ણાંક jobnr, પૂર્ણાંક threadnr, પૂર્ણાંક nb_jobs, પૂર્ણાંક nb_threads),
                              શૂન્ય (*main_func)(શૂન્ય *priv),
                              પૂર્ણાંક nb_threads)
{
    *pctx = ખાલી;
    પાછા AVERROR(ENOSYS);
}

શૂન્ય avpriv_slicethread_execute(AVSliceThread *ctx, પૂર્ણાંક nb_jobs, પૂર્ણાંક execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
