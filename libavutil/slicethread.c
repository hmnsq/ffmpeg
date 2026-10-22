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

#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ "cpu.h"
#అన్తర్భావ "internal.h"
#అన్తర్భావ "slicethread.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "thread.h"
#అన్తర్భావ "avassert.h"

#నిర్వచించు MAX_AUTO_దారాలు 16

#ఒకవేళ HAVE_PTHREADS || HAVE_W32_దారాలు || HAVE_OS2_దారాలు

రకనిర్వచనం నిర్మాణం కార్మికుడు_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    పూర్ణాంకం             పూర్తి;
} కార్మికుడు_Context;

నిర్మాణం AVSliceThread {
    కార్మికుడు_Context   *workers;
    పూర్ణాంకం             nb_దారాలు;
    పూర్ణాంకం             nb_చురుకైన_దారాలు;
    పూర్ణాంకం             nb_jobs;

    atomic_uint     మొదటి_పని;
    atomic_uint     current_పని;
    pthread_mutex_t పూర్తి_mutex;
    pthread_cond_t  పూర్తి_cond;
    పూర్ణాంకం             పూర్తి;
    పూర్ణాంకం             ముగిసిన;
    atomic_int      error;

    శూన్య            *priv;
    పూర్ణాంకం            (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు);
    పూర్ణాంకం            (*main_func)(శూన్య *priv);

#ఒకవేళ LIBAVUTIL_సంస్కరణ_MAJOR < 62
    శూన్య           (*కార్మికుడు_func_v1)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు);
    శూన్య           (*main_func_v1)(శూన్య *priv);
    శూన్య            *priv_v1;
#అయితే_ముగింపు
};

స్థిర పూర్ణాంకం నిరంతరం_jobs(AVSliceThread *ctx)
{
    గుర్తులేని nb_jobs    = ctx->nb_jobs;
    గుర్తులేని nb_చురుకైన_దారాలు = ctx->nb_చురుకైన_దారాలు;
    గుర్తులేని మొదటి_పని    = atomic_fetch_add_explicit(&ctx->మొదటి_పని, 1, memory_order_acq_rel);
    గుర్తులేని current_పని  = మొదటి_పని;

    చేయి {
        పూర్ణాంకం ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        ఒకవేళ (ret)
            కొనసాగు;
        ret = ctx->కార్మికుడు_func(ctx->priv, current_పని, మొదటి_పని, nb_jobs, nb_చురుకైన_దారాలు);
        ఒకవేళ (ret) {
            పూర్ణాంకం prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } అయితే ((current_పని = atomic_fetch_add_explicit(&ctx->current_పని, 1, memory_order_acq_rel)) < nb_jobs);

    తిరిగి current_పని == nb_jobs + nb_చురుకైన_దారాలు - 1;
}

స్థిర శూన్య *attribute_align_arg thread_కార్మికుడు(శూన్య *v)
{
    కార్మికుడు_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_తాళం(&w->mutex);
    pthread_cond_signal(&w->cond);

    అయితే (1) {
        w->పూర్తి = 1;
        అయితే (w->పూర్తి)
            pthread_cond_wait(&w->cond, &w->mutex);

        ఒకవేళ (ctx->ముగిసిన) {
            pthread_mutex_unlock(&w->mutex);
            తిరిగి ఖాళీ;
        }

        ఒకవేళ (నిరంతరం_jobs(ctx)) {
            pthread_mutex_తాళం(&ctx->పూర్తి_mutex);
            ctx->పూర్తి = 1;
            pthread_cond_signal(&ctx->పూర్తి_cond);
            pthread_mutex_unlock(&ctx->పూర్తి_mutex);
        }
    }
}

av_cold
పూర్ణాంకం avpriv_slicethread_create2(AVSliceThread **pctx, శూన్య *priv,
                               పూర్ణాంకం (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                               పూర్ణాంకం (*main_func)(శూన్య *priv),
                               పూర్ణాంకం nb_దారాలు)
{
    AVSliceThread *ctx;
    పూర్ణాంకం nb_workers, i;
    పూర్ణాంకం ret;

    av_assert0(nb_దారాలు >= 0);
    ఒకవేళ (!nb_దారాలు) {
        పూర్ణాంకం nb_cpus = av_cpu_లెక్క();
        ఒకవేళ (nb_cpus > 1)
            nb_దారాలు = FFMIN(nb_cpus + 1, MAX_AUTO_దారాలు);
        లేకపోతే
            nb_దారాలు = 1;
    }

    nb_workers = nb_దారాలు;
    ఒకవేళ (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(పరిమాణం(*ctx));
    ఒకవేళ (!ctx)
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (nb_workers && !(ctx->workers = av_calloc(nb_workers, పరిమాణం(*ctx->workers)))) {
        av_freep(pctx);
        తిరిగి AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->కార్మికుడు_func = కార్మికుడు_func;
    ctx->main_func   = main_func;
    ctx->nb_దారాలు  = nb_దారాలు;
    ctx->nb_చురుకైన_దారాలు = 0;
    ctx->nb_jobs     = 0;
    ctx->ముగిసిన    = 0;

    atomic_init(&ctx->మొదటి_పని, 0);
    atomic_init(&ctx->current_పని, 0);
    ret = pthread_mutex_init(&ctx->పూర్తి_mutex, ఖాళీ);
    ఒకవేళ (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        తిరిగి AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->పూర్తి_cond, ఖాళీ);
    ఒకవేళ (ret) {
        ctx->nb_దారాలు = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        తిరిగి AVERROR(ret);
    }
    ctx->పూర్తి        = 0;

    కొరకు (i = 0; i < nb_workers; i++) {
        కార్మికుడు_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, ఖాళీ);
        ఒకవేళ (ret) {
            ctx->nb_దారాలు = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            తిరిగి AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, ఖాళీ);
        ఒకవేళ (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_దారాలు = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            తిరిగి AVERROR(ret);
        }
        pthread_mutex_తాళం(&w->mutex);
        w->పూర్తి = 0;

        ఒకవేళ (ret = pthread_create(&w->thread, ఖాళీ, thread_కార్మికుడు, w)) {
            ctx->nb_దారాలు = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            తిరిగి AVERROR(ret);
        }

        అయితే (!w->పూర్తి)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    తిరిగి nb_దారాలు;
}

పూర్ణాంకం avpriv_slicethread_execute2(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main)
{
    పూర్ణాంకం nb_workers, i, is_చివరి = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_చురుకైన_దారాలు = FFMIN(nb_jobs, ctx->nb_దారాలు);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->మొదటి_పని, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_పని, ctx->nb_చురుకైన_దారాలు, memory_order_relaxed);
    nb_workers             = ctx->nb_చురుకైన_దారాలు;
    ఒకవేళ (!ctx->main_func || !execute_main)
        nb_workers--;

    కొరకు (i = 0; i < nb_workers; i++) {
        కార్మికుడు_Context *w = &ctx->workers[i];
        pthread_mutex_తాళం(&w->mutex);
        w->పూర్తి = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    ఒకవేళ (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } లేకపోతే
        is_చివరి = నిరంతరం_jobs(ctx);

    ఒకవేళ (!is_చివరి) {
        pthread_mutex_తాళం(&ctx->పూర్తి_mutex);
        అయితే (!ctx->పూర్తి)
            pthread_cond_wait(&ctx->పూర్తి_cond, &ctx->పూర్తి_mutex);
        ctx->పూర్తి = 0;
        pthread_mutex_unlock(&ctx->పూర్తి_mutex);
    }

    ఒకవేళ (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    తిరిగి ret;
}

av_cold శూన్య avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    పూర్ణాంకం nb_workers, i;

    ఒకవేళ (!ctx)
        తిరిగి;

    nb_workers = ctx->nb_దారాలు;
    ఒకవేళ (!ctx->main_func)
        nb_workers--;

    ctx->ముగిసిన = 1;
    కొరకు (i = 0; i < nb_workers; i++) {
        కార్మికుడు_Context *w = &ctx->workers[i];
        pthread_mutex_తాళం(&w->mutex);
        w->పూర్తి = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    కొరకు (i = 0; i < nb_workers; i++) {
        కార్మికుడు_Context *w = &ctx->workers[i];
        pthread_join(w->thread, ఖాళీ);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->పూర్తి_cond);
    pthread_mutex_destroy(&ctx->పూర్తి_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#ఒకవేళ LIBAVUTIL_సంస్కరణ_MAJOR < 62

స్థిర పూర్ణాంకం wrapper_కార్మికుడు(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు)
{
    AVSliceThread *ctx = priv;
    ctx->కార్మికుడు_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_దారాలు);
    తిరిగి 0;
}

స్థిర పూర్ణాంకం wrapper_main(శూన్య *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    తిరిగి 0;
}

పూర్ణాంకం avpriv_slicethread_create(AVSliceThread **pctx, శూన్య *priv,
                              శూన్య (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                              శూన్య (*main_func)(శూన్య *priv),
                              పూర్ణాంకం nb_దారాలు)
{
    పూర్ణాంకం ret = avpriv_slicethread_create2(pctx, ఖాళీ, wrapper_కార్మికుడు,
                                         main_func ? wrapper_main : ఖాళీ,
                                         nb_దారాలు);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->కార్మికుడు_func_v1 = కార్మికుడు_func;
    (*pctx)->main_func_v1   = main_func;
    తిరిగి ret;
}

శూన్య avpriv_slicethread_execute(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#అయితే_ముగింపు /* LIBAVUTIL_VERSION_MAJOR < 62 */

#లేకపోతే /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

పూర్ణాంకం avpriv_slicethread_create2(AVSliceThread **pctx, శూన్య *priv,
                               పూర్ణాంకం (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                               పూర్ణాంకం (*main_func)(శూన్య *priv),
                               పూర్ణాంకం nb_దారాలు)
{
    *pctx = ఖాళీ;
    తిరిగి AVERROR(ENOSYS);
}

పూర్ణాంకం avpriv_slicethread_execute2(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main)
{
    av_assert0(0);
}

శూన్య avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#ఒకవేళ LIBAVUTIL_సంస్కరణ_MAJOR < 62

పూర్ణాంకం avpriv_slicethread_create(AVSliceThread **pctx, శూన్య *priv,
                              శూన్య (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                              శూన్య (*main_func)(శూన్య *priv),
                              పూర్ణాంకం nb_దారాలు)
{
    *pctx = ఖాళీ;
    తిరిగి AVERROR(ENOSYS);
}

శూన్య avpriv_slicethread_execute(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main)
{
    av_assert0(0);
}

#అయితే_ముగింపు /* LIBAVUTIL_VERSION_MAJOR < 62 */

#అయితే_ముగింపు /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
