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

#परिभाषय MAX_AUTO_तन्तवः 16

#यदि HAVE_PTHREADS || HAVE_W32_तन्तवः || HAVE_OS2_तन्तवः

प्रकारनिर्देश संरचना कार्यकर्ता_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    पूर्णाङ्क             समाप्तम्;
} कार्यकर्ता_Context;

संरचना AVSliceThread {
    कार्यकर्ता_Context   *workers;
    पूर्णाङ्क             nb_तन्तवः;
    पूर्णाङ्क             nb_सक्रिय_तन्तवः;
    पूर्णाङ्क             nb_jobs;

    atomic_uint     first_job;
    atomic_uint     current_job;
    pthread_mutex_t समाप्तम्_mutex;
    pthread_cond_t  समाप्तम्_cond;
    पूर्णाङ्क             समाप्तम्;
    पूर्णाङ्क             परिसमाप्तम्;
    atomic_int      error;

    शून्य            *priv;
    पूर्णाङ्क            (*कार्यकर्ता_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः);
    पूर्णाङ्क            (*main_func)(शून्य *priv);

#यदि LIBAVUTIL_संस्करणम्_MAJOR < 62
    शून्य           (*कार्यकर्ता_func_v1)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः);
    शून्य           (*main_func_v1)(शून्य *priv);
    शून्य            *priv_v1;
#यदि_अन्तः
};

स्थिर पूर्णाङ्क सततम्_jobs(AVSliceThread *ctx)
{
    अचिह्नित nb_jobs    = ctx->nb_jobs;
    अचिह्नित nb_सक्रिय_तन्तवः = ctx->nb_सक्रिय_तन्तवः;
    अचिह्नित first_job    = atomic_fetch_add_explicit(&ctx->first_job, 1, memory_order_acq_rel);
    अचिह्नित current_job  = first_job;

    कुरु {
        पूर्णाङ्क ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        यदि (ret)
            अनुवर्त;
        ret = ctx->कार्यकर्ता_func(ctx->priv, current_job, first_job, nb_jobs, nb_सक्रिय_तन्तवः);
        यदि (ret) {
            पूर्णाङ्क पूर्व = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &पूर्व, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } यावत् ((current_job = atomic_fetch_add_explicit(&ctx->current_job, 1, memory_order_acq_rel)) < nb_jobs);

    प्रत्यागम current_job == nb_jobs + nb_सक्रिय_तन्तवः - 1;
}

स्थिर शून्य *attribute_align_arg thread_कार्यकर्ता(शून्य *v)
{
    कार्यकर्ता_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_तालकम्(&w->mutex);
    pthread_cond_signal(&w->cond);

    यावत् (1) {
        w->समाप्तम् = 1;
        यावत् (w->समाप्तम्)
            pthread_cond_wait(&w->cond, &w->mutex);

        यदि (ctx->परिसमाप्तम्) {
            pthread_mutex_unlock(&w->mutex);
            प्रत्यागम रिक्त;
        }

        यदि (सततम्_jobs(ctx)) {
            pthread_mutex_तालकम्(&ctx->समाप्तम्_mutex);
            ctx->समाप्तम् = 1;
            pthread_cond_signal(&ctx->समाप्तम्_cond);
            pthread_mutex_unlock(&ctx->समाप्तम्_mutex);
        }
    }
}

av_cold
पूर्णाङ्क avpriv_slicethread_create2(AVSliceThread **pctx, शून्य *priv,
                               पूर्णाङ्क (*कार्यकर्ता_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः),
                               पूर्णाङ्क (*main_func)(शून्य *priv),
                               पूर्णाङ्क nb_तन्तवः)
{
    AVSliceThread *ctx;
    पूर्णाङ्क nb_workers, i;
    पूर्णाङ्क ret;

    av_assert0(nb_तन्तवः >= 0);
    यदि (!nb_तन्तवः) {
        पूर्णाङ्क nb_cpus = av_cpu_गणनम्();
        यदि (nb_cpus > 1)
            nb_तन्तवः = FFMIN(nb_cpus + 1, MAX_AUTO_तन्तवः);
        अन्यथा
            nb_तन्तवः = 1;
    }

    nb_workers = nb_तन्तवः;
    यदि (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(परिमाण(*ctx));
    यदि (!ctx)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (nb_workers && !(ctx->workers = av_calloc(nb_workers, परिमाण(*ctx->workers)))) {
        av_freep(pctx);
        प्रत्यागम AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->कार्यकर्ता_func = कार्यकर्ता_func;
    ctx->main_func   = main_func;
    ctx->nb_तन्तवः  = nb_तन्तवः;
    ctx->nb_सक्रिय_तन्तवः = 0;
    ctx->nb_jobs     = 0;
    ctx->परिसमाप्तम्    = 0;

    atomic_init(&ctx->first_job, 0);
    atomic_init(&ctx->current_job, 0);
    ret = pthread_mutex_init(&ctx->समाप्तम्_mutex, रिक्त);
    यदि (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        प्रत्यागम AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->समाप्तम्_cond, रिक्त);
    यदि (ret) {
        ctx->nb_तन्तवः = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        प्रत्यागम AVERROR(ret);
    }
    ctx->समाप्तम्        = 0;

    प्रति (i = 0; i < nb_workers; i++) {
        कार्यकर्ता_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, रिक्त);
        यदि (ret) {
            ctx->nb_तन्तवः = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            प्रत्यागम AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, रिक्त);
        यदि (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_तन्तवः = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            प्रत्यागम AVERROR(ret);
        }
        pthread_mutex_तालकम्(&w->mutex);
        w->समाप्तम् = 0;

        यदि (ret = pthread_create(&w->thread, रिक्त, thread_कार्यकर्ता, w)) {
            ctx->nb_तन्तवः = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            प्रत्यागम AVERROR(ret);
        }

        यावत् (!w->समाप्तम्)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    प्रत्यागम nb_तन्तवः;
}

पूर्णाङ्क avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    पूर्णाङ्क nb_workers, i, is_चरमः = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_सक्रिय_तन्तवः = FFMIN(nb_jobs, ctx->nb_तन्तवः);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->first_job, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_job, ctx->nb_सक्रिय_तन्तवः, memory_order_relaxed);
    nb_workers             = ctx->nb_सक्रिय_तन्तवः;
    यदि (!ctx->main_func || !execute_main)
        nb_workers--;

    प्रति (i = 0; i < nb_workers; i++) {
        कार्यकर्ता_Context *w = &ctx->workers[i];
        pthread_mutex_तालकम्(&w->mutex);
        w->समाप्तम् = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    यदि (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } अन्यथा
        is_चरमः = सततम्_jobs(ctx);

    यदि (!is_चरमः) {
        pthread_mutex_तालकम्(&ctx->समाप्तम्_mutex);
        यावत् (!ctx->समाप्तम्)
            pthread_cond_wait(&ctx->समाप्तम्_cond, &ctx->समाप्तम्_mutex);
        ctx->समाप्तम् = 0;
        pthread_mutex_unlock(&ctx->समाप्तम्_mutex);
    }

    यदि (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    प्रत्यागम ret;
}

av_cold शून्य avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    पूर्णाङ्क nb_workers, i;

    यदि (!ctx)
        प्रत्यागम;

    nb_workers = ctx->nb_तन्तवः;
    यदि (!ctx->main_func)
        nb_workers--;

    ctx->परिसमाप्तम् = 1;
    प्रति (i = 0; i < nb_workers; i++) {
        कार्यकर्ता_Context *w = &ctx->workers[i];
        pthread_mutex_तालकम्(&w->mutex);
        w->समाप्तम् = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    प्रति (i = 0; i < nb_workers; i++) {
        कार्यकर्ता_Context *w = &ctx->workers[i];
        pthread_join(w->thread, रिक्त);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->समाप्तम्_cond);
    pthread_mutex_destroy(&ctx->समाप्तम्_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#यदि LIBAVUTIL_संस्करणम्_MAJOR < 62

स्थिर पूर्णाङ्क wrapper_कार्यकर्ता(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः)
{
    AVSliceThread *ctx = priv;
    ctx->कार्यकर्ता_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_तन्तवः);
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क wrapper_main(शून्य *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    प्रत्यागम 0;
}

पूर्णाङ्क avpriv_slicethread_create(AVSliceThread **pctx, शून्य *priv,
                              शून्य (*कार्यकर्ता_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः),
                              शून्य (*main_func)(शून्य *priv),
                              पूर्णाङ्क nb_तन्तवः)
{
    पूर्णाङ्क ret = avpriv_slicethread_create2(pctx, रिक्त, wrapper_कार्यकर्ता,
                                         main_func ? wrapper_main : रिक्त,
                                         nb_तन्तवः);
    यदि (ret < 0)
        प्रत्यागम ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->कार्यकर्ता_func_v1 = कार्यकर्ता_func;
    (*pctx)->main_func_v1   = main_func;
    प्रत्यागम ret;
}

शून्य avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#यदि_अन्तः /* LIBAVUTIL_VERSION_MAJOR < 62 */

#अन्यथा /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

पूर्णाङ्क avpriv_slicethread_create2(AVSliceThread **pctx, शून्य *priv,
                               पूर्णाङ्क (*कार्यकर्ता_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः),
                               पूर्णाङ्क (*main_func)(शून्य *priv),
                               पूर्णाङ्क nb_तन्तवः)
{
    *pctx = रिक्त;
    प्रत्यागम AVERROR(ENOSYS);
}

पूर्णाङ्क avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    av_assert0(0);
}

शून्य avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#यदि LIBAVUTIL_संस्करणम्_MAJOR < 62

पूर्णाङ्क avpriv_slicethread_create(AVSliceThread **pctx, शून्य *priv,
                              शून्य (*कार्यकर्ता_func)(शून्य *priv, पूर्णाङ्क jobnr, पूर्णाङ्क threadnr, पूर्णाङ्क nb_jobs, पूर्णाङ्क nb_तन्तवः),
                              शून्य (*main_func)(शून्य *priv),
                              पूर्णाङ्क nb_तन्तवः)
{
    *pctx = रिक्त;
    प्रत्यागम AVERROR(ENOSYS);
}

शून्य avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णाङ्क nb_jobs, पूर्णाङ्क execute_main)
{
    av_assert0(0);
}

#यदि_अन्तः /* LIBAVUTIL_VERSION_MAJOR < 62 */

#यदि_अन्तः /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
