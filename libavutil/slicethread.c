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

#تعریف_کرو MAX_AUTO_دھاگے 16

#اگر HAVE_PTHREADS || HAVE_W32_دھاگے || HAVE_OS2_دھاگے

قسمتعریف ساخت کارکن_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحیح             مکمل;
} کارکن_Context;

ساخت AVSliceThread {
    کارکن_Context   *workers;
    صحیح             nb_دھاگے;
    صحیح             nb_فعال_دھاگے;
    صحیح             nb_jobs;

    atomic_uint     پہلا_کام;
    atomic_uint     current_کام;
    pthread_mutex_t مکمل_mutex;
    pthread_cond_t  مکمل_cond;
    صحیح             مکمل;
    صحیح             ختم_شدہ;
    atomic_int      error;

    خالی            *priv;
    صحیح            (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے);
    صحیح            (*main_func)(خالی *priv);

#اگر LIBAVUTIL_نسخہ_MAJOR < 62
    خالی           (*کارکن_func_v1)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے);
    خالی           (*main_func_v1)(خالی *priv);
    خالی            *priv_v1;
#اگر_ختم
};

ساکن صحیح تسلسل_jobs(AVSliceThread *ctx)
{
    غیرعلامتی nb_jobs    = ctx->nb_jobs;
    غیرعلامتی nb_فعال_دھاگے = ctx->nb_فعال_دھاگے;
    غیرعلامتی پہلا_کام    = atomic_fetch_add_explicit(&ctx->پہلا_کام, 1, memory_order_acq_rel);
    غیرعلامتی current_کام  = پہلا_کام;

    کرو {
        صحیح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        اگر (ret)
            جاری;
        ret = ctx->کارکن_func(ctx->priv, current_کام, پہلا_کام, nb_jobs, nb_فعال_دھاگے);
        اگر (ret) {
            صحیح پچھلا = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &پچھلا, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } جب ((current_کام = atomic_fetch_add_explicit(&ctx->current_کام, 1, memory_order_acq_rel)) < nb_jobs);

    واپس current_کام == nb_jobs + nb_فعال_دھاگے - 1;
}

ساکن خالی *attribute_align_arg thread_کارکن(خالی *v)
{
    کارکن_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_تالا(&w->mutex);
    pthread_cond_signal(&w->cond);

    جب (1) {
        w->مکمل = 1;
        جب (w->مکمل)
            pthread_cond_wait(&w->cond, &w->mutex);

        اگر (ctx->ختم_شدہ) {
            pthread_mutex_unlock(&w->mutex);
            واپس تہی;
        }

        اگر (تسلسل_jobs(ctx)) {
            pthread_mutex_تالا(&ctx->مکمل_mutex);
            ctx->مکمل = 1;
            pthread_cond_signal(&ctx->مکمل_cond);
            pthread_mutex_unlock(&ctx->مکمل_mutex);
        }
    }
}

av_cold
صحیح avpriv_slicethread_create2(AVSliceThread **pctx, خالی *priv,
                               صحیح (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                               صحیح (*main_func)(خالی *priv),
                               صحیح nb_دھاگے)
{
    AVSliceThread *ctx;
    صحیح nb_workers, i;
    صحیح ret;

    av_assert0(nb_دھاگے >= 0);
    اگر (!nb_دھاگے) {
        صحیح nb_cpus = av_cpu_گنتی();
        اگر (nb_cpus > 1)
            nb_دھاگے = FFMIN(nb_cpus + 1, MAX_AUTO_دھاگے);
        ورنہ
            nb_دھاگے = 1;
    }

    nb_workers = nb_دھاگے;
    اگر (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(حجم(*ctx));
    اگر (!ctx)
        واپس AVERROR(ENOMEM);

    اگر (nb_workers && !(ctx->workers = av_calloc(nb_workers, حجم(*ctx->workers)))) {
        av_freep(pctx);
        واپس AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->کارکن_func = کارکن_func;
    ctx->main_func   = main_func;
    ctx->nb_دھاگے  = nb_دھاگے;
    ctx->nb_فعال_دھاگے = 0;
    ctx->nb_jobs     = 0;
    ctx->ختم_شدہ    = 0;

    atomic_init(&ctx->پہلا_کام, 0);
    atomic_init(&ctx->current_کام, 0);
    ret = pthread_mutex_init(&ctx->مکمل_mutex, تہی);
    اگر (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        واپس AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->مکمل_cond, تہی);
    اگر (ret) {
        ctx->nb_دھاگے = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        واپس AVERROR(ret);
    }
    ctx->مکمل        = 0;

    برائے (i = 0; i < nb_workers; i++) {
        کارکن_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, تہی);
        اگر (ret) {
            ctx->nb_دھاگے = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            واپس AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, تہی);
        اگر (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_دھاگے = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            واپس AVERROR(ret);
        }
        pthread_mutex_تالا(&w->mutex);
        w->مکمل = 0;

        اگر (ret = pthread_create(&w->thread, تہی, thread_کارکن, w)) {
            ctx->nb_دھاگے = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            واپس AVERROR(ret);
        }

        جب (!w->مکمل)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    واپس nb_دھاگے;
}

صحیح avpriv_slicethread_execute2(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    صحیح nb_workers, i, is_آخری = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_فعال_دھاگے = FFMIN(nb_jobs, ctx->nb_دھاگے);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->پہلا_کام, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_کام, ctx->nb_فعال_دھاگے, memory_order_relaxed);
    nb_workers             = ctx->nb_فعال_دھاگے;
    اگر (!ctx->main_func || !execute_main)
        nb_workers--;

    برائے (i = 0; i < nb_workers; i++) {
        کارکن_Context *w = &ctx->workers[i];
        pthread_mutex_تالا(&w->mutex);
        w->مکمل = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    اگر (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } ورنہ
        is_آخری = تسلسل_jobs(ctx);

    اگر (!is_آخری) {
        pthread_mutex_تالا(&ctx->مکمل_mutex);
        جب (!ctx->مکمل)
            pthread_cond_wait(&ctx->مکمل_cond, &ctx->مکمل_mutex);
        ctx->مکمل = 0;
        pthread_mutex_unlock(&ctx->مکمل_mutex);
    }

    اگر (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    واپس ret;
}

av_cold خالی avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    صحیح nb_workers, i;

    اگر (!ctx)
        واپس;

    nb_workers = ctx->nb_دھاگے;
    اگر (!ctx->main_func)
        nb_workers--;

    ctx->ختم_شدہ = 1;
    برائے (i = 0; i < nb_workers; i++) {
        کارکن_Context *w = &ctx->workers[i];
        pthread_mutex_تالا(&w->mutex);
        w->مکمل = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    برائے (i = 0; i < nb_workers; i++) {
        کارکن_Context *w = &ctx->workers[i];
        pthread_join(w->thread, تہی);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->مکمل_cond);
    pthread_mutex_destroy(&ctx->مکمل_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#اگر LIBAVUTIL_نسخہ_MAJOR < 62

ساکن صحیح wrapper_کارکن(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے)
{
    AVSliceThread *ctx = priv;
    ctx->کارکن_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_دھاگے);
    واپس 0;
}

ساکن صحیح wrapper_main(خالی *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    واپس 0;
}

صحیح avpriv_slicethread_create(AVSliceThread **pctx, خالی *priv,
                              خالی (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                              خالی (*main_func)(خالی *priv),
                              صحیح nb_دھاگے)
{
    صحیح ret = avpriv_slicethread_create2(pctx, تہی, wrapper_کارکن,
                                         main_func ? wrapper_main : تہی,
                                         nb_دھاگے);
    اگر (ret < 0)
        واپس ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->کارکن_func_v1 = کارکن_func;
    (*pctx)->main_func_v1   = main_func;
    واپس ret;
}

خالی avpriv_slicethread_execute(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#اگر_ختم /* LIBAVUTIL_VERSION_MAJOR < 62 */

#ورنہ /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحیح avpriv_slicethread_create2(AVSliceThread **pctx, خالی *priv,
                               صحیح (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                               صحیح (*main_func)(خالی *priv),
                               صحیح nb_دھاگے)
{
    *pctx = تہی;
    واپس AVERROR(ENOSYS);
}

صحیح avpriv_slicethread_execute2(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    av_assert0(0);
}

خالی avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#اگر LIBAVUTIL_نسخہ_MAJOR < 62

صحیح avpriv_slicethread_create(AVSliceThread **pctx, خالی *priv,
                              خالی (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                              خالی (*main_func)(خالی *priv),
                              صحیح nb_دھاگے)
{
    *pctx = تہی;
    واپس AVERROR(ENOSYS);
}

خالی avpriv_slicethread_execute(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main)
{
    av_assert0(0);
}

#اگر_ختم /* LIBAVUTIL_VERSION_MAJOR < 62 */

#اگر_ختم /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
