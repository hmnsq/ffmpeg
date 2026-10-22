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

#समावेश <stdatomic.h>
#समावेश "cpu.h"
#समावेश "internal.h"
#समावेश "slicethread.h"
#समावेश "mem.h"
#समावेश "thread.h"
#समावेश "avassert.h"

#घोषणा MAX_AUTO_THREADS 16

#अगर HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

प्रकार काष्ठा WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    पूर्णांक             done;
} WorkerContext;

काष्ठा AVSliceThread {
    WorkerContext   *workers;
    पूर्णांक             nb_threads;
    पूर्णांक             nb_active_threads;
    पूर्णांक             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    पूर्णांक             done;
    पूर्णांक             finished;
    atomic_int      error;

    व्योम            *priv;
    पूर्णांक            (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads);
    पूर्णांक            (*main_func)(व्योम *priv);

#अगर LIBAVUTIL_VERSION_MAJOR < 62
    व्योम           (*worker_func_v1)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads);
    व्योम           (*main_func_v1)(व्योम *priv);
    व्योम            *priv_v1;
#पूर्ण_अगर
};

अटल पूर्णांक run_jobs(AVSliceThread *ctx)
{
    अचिन्हित nb_jobs    = ctx->nb_jobs;
    अचिन्हित nb_active_threads = ctx->nb_active_threads;
    अचिन्हित first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    अचिन्हित current_job  = first_job;

    करो {
        पूर्णांक ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        अगर (ret)
            जारी;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        अगर (ret) {
            पूर्णांक पूर्व = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &पूर्व, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } जबतक ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    वापस current_job == nb_jobs + nb_active_threads - 1;
}

अटल व्योम *attribute_align_arg thread_worker(व्योम *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    जबतक (1) {
        w->done = 1;
        जबतक (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        अगर (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            वापस शून्य;
        }

        अगर (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
पूर्णांक avpriv_slicethread_create2(AVSliceThread **pctx, व्योम *priv,
                               पूर्णांक (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                               पूर्णांक (*main_func)(व्योम *priv),
                               पूर्णांक nb_threads)
{
    AVSliceThread *ctx;
    पूर्णांक nb_workers, i;
    पूर्णांक ret;

    av_assert0(nb_threads >= 0);
    अगर (!nb_threads) {
        पूर्णांक nb_cpus = av_cpu_गिनती();
        अगर (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        अन्यथा
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    अगर (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(माप(*ctx));
    अगर (!ctx)
        वापस AVERROR(ENOMEM);

    अगर (nb_workers && !(ctx->workers = av_calloc(nb_workers, माप(*ctx->workers)))) {
        av_freep(pctx);
        वापस AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, शून्य);
    अगर (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        वापस AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, शून्य);
    अगर (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        वापस AVERROR(ret);
    }
    ctx->done        = 0;

    क्रम (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, शून्य);
        अगर (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            वापस AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, शून्य);
        अगर (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            वापस AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        अगर (ret = pthread_create(&w->thread, शून्य, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            वापस AVERROR(ret);
        }

        जबतक (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    वापस nb_threads;
}

पूर्णांक avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main)
{
    पूर्णांक nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    अगर (!ctx->main_func || !execute_main)
        nb_workers--;

    क्रम (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    अगर (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } अन्यथा
        is_last = run_jobs(ctx);

    अगर (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        जबतक (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    अगर (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    वापस ret;
}

av_cold व्योम avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    पूर्णांक nb_workers, i;

    अगर (!ctx)
        वापस;

    nb_workers = ctx->nb_threads;
    अगर (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    क्रम (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    क्रम (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, शून्य);
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

#अगर LIBAVUTIL_VERSION_MAJOR < 62

अटल पूर्णांक wrapper_worker(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    वापस 0;
}

अटल पूर्णांक wrapper_main(व्योम *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    वापस 0;
}

पूर्णांक avpriv_slicethread_create(AVSliceThread **pctx, व्योम *priv,
                              व्योम (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                              व्योम (*main_func)(व्योम *priv),
                              पूर्णांक nb_threads)
{
    पूर्णांक ret = avpriv_slicethread_create2(pctx, शून्य, wrapper_worker,
                                         main_func ? wrapper_main : शून्य,
                                         nb_threads);
    अगर (ret < 0)
        वापस ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    वापस ret;
}

व्योम avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#पूर्ण_अगर /* LIBAVUTIL_VERSION_MAJOR < 62 */

#अन्यथा /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

पूर्णांक avpriv_slicethread_create2(AVSliceThread **pctx, व्योम *priv,
                               पूर्णांक (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                               पूर्णांक (*main_func)(व्योम *priv),
                               पूर्णांक nb_threads)
{
    *pctx = शून्य;
    वापस AVERROR(ENOSYS);
}

पूर्णांक avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main)
{
    av_assert0(0);
}

व्योम avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#अगर LIBAVUTIL_VERSION_MAJOR < 62

पूर्णांक avpriv_slicethread_create(AVSliceThread **pctx, व्योम *priv,
                              व्योम (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                              व्योम (*main_func)(व्योम *priv),
                              पूर्णांक nb_threads)
{
    *pctx = शून्य;
    वापस AVERROR(ENOSYS);
}

व्योम avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main)
{
    av_assert0(0);
}

#पूर्ण_अगर /* LIBAVUTIL_VERSION_MAJOR < 62 */

#पूर्ण_अगर /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
