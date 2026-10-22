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

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव "cpu.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "slicethread.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "thread.h"
#अन्तर्भाव "avassert.h"

#define MAX_AUTO_THREADS 16

#सचे HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

प्रकारनिर्देश संरचना WorkerContext {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    पूर्णाङ्क             done;
} WorkerContext;

संरचना AVSliceThread {
    WorkerContext   *workers;
    पूर्णाङ्क             nb_threads;
    पूर्णाङ्क             nb_active_threads;
    पूर्णाङ्क             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t done_mutex;
    pthread_cond_t  done_cond;
    पूर्णाङ्क             done;
    पूर्णाङ्क             finished;
    atomic_int      error;

    शून्य            *priv;
    पूर्णाङ्क            (*worker_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads);
    पूर्णाङ्क            (*main_func)(शून्य *priv);

#सचे LIBAVUTIL_VERSION_MAJOR < 62
    शून्य           (*worker_func_v1)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads);
    शून्य           (*main_func_v1)(शून्य *priv);
    शून्य            *priv_v1;
#endif
};

स्थिर पूर्णाङ्क run_jobs(AVSliceThread *ctx)
{
    unsigned nb_jobs    = ctx->nb_jobs;
    unsigned nb_active_threads = ctx->nb_active_threads;
    unsigned first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    unsigned current_job  = first_job;

    करोहि {
        पूर्णाङ्क ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        सचे (ret)
            अनुवर्त;
        ret = ctx->worker_func(ctx->priv, current_job, first_job, nb_jobs, nb_active_threads);
        सचे (ret) {
            पूर्णाङ्क prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } याव ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    पटिनिवत्त current_job == nb_jobs + nb_active_threads - 1;
}

स्थिर शून्य *attribute_align_arg thread_worker(शून्य *v)
{
    WorkerContext *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_lock(&w->mutex);
    pthread_cond_signal(&w->cond);

    याव (1) {
        w->done = 1;
        याव (w->done)
            pthread_cond_wait(&w->cond, &w->mutex);

        सचे (ctx->finished) {
            pthread_mutex_unlock(&w->mutex);
            पटिनिवत्त रिक्त;
        }

        सचे (run_jobs(ctx)) {
            pthread_mutex_lock(&ctx->done_mutex);
            ctx->done = 1;
            pthread_cond_signal(&ctx->done_cond);
            pthread_mutex_unlock(&ctx->done_mutex);
        }
    }
}

av_cold
पूर्णाङ्क avpriv_slicethread_create2(AVSliceThread **pctx, शून्य *priv,
                               पूर्णाङ्क (*worker_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads),
                               पूर्णाङ्क (*main_func)(शून्य *priv),
                               पूर्णाङ्क nb_threads)
{
    AVSliceThread *ctx;
    पूर्णाङ्क nb_workers, i;
    पूर्णाङ्क ret;

    av_assert0(nb_threads >= 0);
    सचे (!nb_threads) {
        पूर्णाङ्क nb_cpus = av_cpu_गणनम्();
        सचे (nb_cpus > 1)
            nb_threads = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        अञ्ञथा
            nb_threads = 1;
    }

    nb_workers = nb_threads;
    सचे (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(परिमाण(*ctx));
    सचे (!ctx)
        पटिनिवत्त AVERROR(ENOMEM);

    सचे (nb_workers && !(ctx->workers = av_calloc(nb_workers, परिमाण(*ctx->workers)))) {
        av_freep(pctx);
        पटिनिवत्त AVERROR(ENOMEM);
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
    ret = pthread_mutex_init(&ctx->done_mutex, रिक्त);
    सचे (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        पटिनिवत्त AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->done_cond, रिक्त);
    सचे (ret) {
        ctx->nb_threads = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        पटिनिवत्त AVERROR(ret);
    }
    ctx->done        = 0;

    अत्थाय (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, रिक्त);
        सचे (ret) {
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            पटिनिवत्त AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, रिक्त);
        सचे (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_threads = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            पटिनिवत्त AVERROR(ret);
        }
        pthread_mutex_lock(&w->mutex);
        w->done = 0;

        सचे (ret = pthread_create(&w->thread, रिक्त, thread_worker, w)) {
            ctx->nb_threads = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            पटिनिवत्त AVERROR(ret);
        }

        याव (!w->done)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    पटिनिवत्त nb_threads;
}

पूर्णाङ्क avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    पूर्णाङ्क nb_workers, i, is_last = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_active_threads = FFMIN(nb_jobs, ctx->nb_threads);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_active_threads, memory_order_relaxed);
    nb_workers             = ctx->nb_active_threads;
    सचे (!ctx->main_func || !execute_main)
        nb_workers--;

    अत्थाय (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    सचे (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } अञ्ञथा
        is_last = run_jobs(ctx);

    सचे (!is_last) {
        pthread_mutex_lock(&ctx->done_mutex);
        याव (!ctx->done)
            pthread_cond_wait(&ctx->done_cond, &ctx->done_mutex);
        ctx->done = 0;
        pthread_mutex_unlock(&ctx->done_mutex);
    }

    सचे (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    पटिनिवत्त ret;
}

av_cold शून्य avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    पूर्णाङ्क nb_workers, i;

    सचे (!ctx)
        पटिनिवत्त;

    nb_workers = ctx->nb_threads;
    सचे (!ctx->main_func)
        nb_workers--;

    ctx->finished = 1;
    अत्थाय (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_mutex_lock(&w->mutex);
        w->done = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    अत्थाय (i = 0; i < nb_workers; i++) {
        WorkerContext *w = &ctx->workers[i];
        pthread_join(w->thread, रिक्त);
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

#सचे LIBAVUTIL_VERSION_MAJOR < 62

स्थिर पूर्णाङ्क wrapper_worker(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads)
{
    AVSliceThread *ctx = priv;
    ctx->worker_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_threads);
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क wrapper_main(शून्य *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    पटिनिवत्त 0;
}

पूर्णाङ्क avpriv_slicethread_create(AVSliceThread **pctx, शून्य *priv,
                              शून्य (*worker_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads),
                              शून्य (*main_func)(शून्य *priv),
                              पूर्णाङ्क nb_threads)
{
    पूर्णाङ्क ret = avpriv_slicethread_create2(pctx, रिक्त, wrapper_worker,
                                         main_func ? wrapper_main : रिक्त,
                                         nb_threads);
    सचे (ret < 0)
        पटिनिवत्त ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->worker_func_v1 = worker_func;
    (*pctx)->main_func_v1   = main_func;
    पटिनिवत्त ret;
}

शून्य avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#अञ्ञथा /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

पूर्णाङ्क avpriv_slicethread_create2(AVSliceThread **pctx, शून्य *priv,
                               पूर्णाङ्क (*worker_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads),
                               पूर्णाङ्क (*main_func)(शून्य *priv),
                               पूर्णाङ्क nb_threads)
{
    *pctx = रिक्त;
    पटिनिवत्त AVERROR(ENOSYS);
}

पूर्णाङ्क avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    av_assert0(0);
}

शून्य avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#सचे LIBAVUTIL_VERSION_MAJOR < 62

पूर्णाङ्क avpriv_slicethread_create(AVSliceThread **pctx, शून्य *priv,
                              शून्य (*worker_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_threads),
                              शून्य (*main_func)(शून्य *priv),
                              पूर्णाङ्क nb_threads)
{
    *pctx = रिक्त;
    पटिनिवत्त AVERROR(ENOSYS);
}

शून्य avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    av_assert0(0);
}

#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
