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

#تعریف_کړه MAX_AUTO_تارونه 16

#إذا HAVE_PTHREADS || HAVE_W32_تارونه || HAVE_OS2_تارونه

تعريفنوع بنية کارګر_Context {
    AVSliceThread   *ctx;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    pthread_t       thread;
    صحيح             بشپړ;
} کارګر_Context;

بنية AVSliceThread {
    کارګر_Context   *workers;
    صحيح             nb_تارونه;
    صحيح             nb_فعال_تارونه;
    صحيح             nb_jobs;

    atomic_uint     لومړی_دنده;
    atomic_uint     current_دنده;
    pthread_mutex_t بشپړ_mutex;
    pthread_cond_t  بشپړ_cond;
    صحيح             بشپړ;
    صحيح             پای_ته_رسېدلی;
    atomic_int      error;

    فراغ            *priv;
    صحيح            (*کارګر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه);
    صحيح            (*main_func)(فراغ *priv);

#إذا LIBAVUTIL_نسخه_MAJOR < 62
    فراغ           (*کارګر_func_v1)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه);
    فراغ           (*main_func_v1)(فراغ *priv);
    فراغ            *priv_v1;
#د_که_پای
};

ساكن صحيح پرلپسې_jobs(AVSliceThread *ctx)
{
    بینښه nb_jobs    = ctx->nb_jobs;
    بینښه nb_فعال_تارونه = ctx->nb_فعال_تارونه;
    بینښه لومړی_دنده    = atomic_fetch_add_explicit(&ctx->لومړی_دنده, 1, memory_order_acq_rel);
    بینښه current_دنده  = لومړی_دنده;

    افعل {
        صحيح ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);
        إذا (ret)
            استمر;
        ret = ctx->کارګر_func(ctx->priv, current_دنده, لومړی_دنده, nb_jobs, nb_فعال_تارونه);
        إذا (ret) {
            صحيح prev = 0;
            atomic_compare_exchange_strong_explicit(&ctx->error, &prev, ret,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed);
        }
    } طالما ((current_دنده = atomic_fetch_add_explicit(&ctx->current_دنده, 1, memory_order_acq_rel)) < nb_jobs);

    أرجع current_دنده == nb_jobs + nb_فعال_تارونه - 1;
}

ساكن فراغ *attribute_align_arg thread_کارګر(فراغ *v)
{
    کارګر_Context *w = v;
    AVSliceThread *ctx = w->ctx;

    pthread_mutex_قلف(&w->mutex);
    pthread_cond_signal(&w->cond);

    طالما (1) {
        w->بشپړ = 1;
        طالما (w->بشپړ)
            pthread_cond_wait(&w->cond, &w->mutex);

        إذا (ctx->پای_ته_رسېدلی) {
            pthread_mutex_unlock(&w->mutex);
            أرجع عدم;
        }

        إذا (پرلپسې_jobs(ctx)) {
            pthread_mutex_قلف(&ctx->بشپړ_mutex);
            ctx->بشپړ = 1;
            pthread_cond_signal(&ctx->بشپړ_cond);
            pthread_mutex_unlock(&ctx->بشپړ_mutex);
        }
    }
}

av_cold
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کارګر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_تارونه)
{
    AVSliceThread *ctx;
    صحيح nb_workers, i;
    صحيح ret;

    av_assert0(nb_تارونه >= 0);
    إذا (!nb_تارونه) {
        صحيح nb_cpus = av_cpu_شمېر();
        إذا (nb_cpus > 1)
            nb_تارونه = FFMIN(nb_cpus + 1, MAX_AUTO_تارونه);
        وإلا
            nb_تارونه = 1;
    }

    nb_workers = nb_تارونه;
    إذا (!main_func)
        nb_workers--;

    *pctx = ctx = av_mallocz(حجم(*ctx));
    إذا (!ctx)
        أرجع AVERROR(ENOMEM);

    إذا (nb_workers && !(ctx->workers = av_calloc(nb_workers, حجم(*ctx->workers)))) {
        av_freep(pctx);
        أرجع AVERROR(ENOMEM);
    }

    ctx->priv        = priv;
    ctx->کارګر_func = کارګر_func;
    ctx->main_func   = main_func;
    ctx->nb_تارونه  = nb_تارونه;
    ctx->nb_فعال_تارونه = 0;
    ctx->nb_jobs     = 0;
    ctx->پای_ته_رسېدلی    = 0;

    atomic_init(&ctx->لومړی_دنده, 0);
    atomic_init(&ctx->current_دنده, 0);
    ret = pthread_mutex_init(&ctx->بشپړ_mutex, عدم);
    إذا (ret) {
        av_freep(&ctx->workers);
        av_freep(pctx);
        أرجع AVERROR(ret);
    }
    ret = pthread_cond_init(&ctx->بشپړ_cond, عدم);
    إذا (ret) {
        ctx->nb_تارونه = main_func ? 0 : 1;
        avpriv_slicethread_free(pctx);
        أرجع AVERROR(ret);
    }
    ctx->بشپړ        = 0;

    لكل (i = 0; i < nb_workers; i++) {
        کارګر_Context *w = &ctx->workers[i];
        w->ctx = ctx;
        ret = pthread_mutex_init(&w->mutex, عدم);
        إذا (ret) {
            ctx->nb_تارونه = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        ret = pthread_cond_init(&w->cond, عدم);
        إذا (ret) {
            pthread_mutex_destroy(&w->mutex);
            ctx->nb_تارونه = main_func ? i : i + 1;
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }
        pthread_mutex_قلف(&w->mutex);
        w->بشپړ = 0;

        إذا (ret = pthread_create(&w->thread, عدم, thread_کارګر, w)) {
            ctx->nb_تارونه = main_func ? i : i + 1;
            pthread_mutex_unlock(&w->mutex);
            pthread_cond_destroy(&w->cond);
            pthread_mutex_destroy(&w->mutex);
            avpriv_slicethread_free(pctx);
            أرجع AVERROR(ret);
        }

        طالما (!w->بشپړ)
            pthread_cond_wait(&w->cond, &w->mutex);
        pthread_mutex_unlock(&w->mutex);
    }

    أرجع nb_تارونه;
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    صحيح nb_workers, i, is_وروستی = 0, ret = 0;

    av_assert0(nb_jobs > 0);
    ctx->nb_jobs           = nb_jobs;
    ctx->nb_فعال_تارونه = FFMIN(nb_jobs, ctx->nb_تارونه);
    atomic_store_explicit(&ctx->error, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->لومړی_دنده, 0, memory_order_relaxed);
    atomic_store_explicit(&ctx->current_دنده, ctx->nb_فعال_تارونه, memory_order_relaxed);
    nb_workers             = ctx->nb_فعال_تارونه;
    إذا (!ctx->main_func || !execute_main)
        nb_workers--;

    لكل (i = 0; i < nb_workers; i++) {
        کارګر_Context *w = &ctx->workers[i];
        pthread_mutex_قلف(&w->mutex);
        w->بشپړ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    إذا (ctx->main_func && execute_main) {
        ret = ctx->main_func(ctx->priv);
    } وإلا
        is_وروستی = پرلپسې_jobs(ctx);

    إذا (!is_وروستی) {
        pthread_mutex_قلف(&ctx->بشپړ_mutex);
        طالما (!ctx->بشپړ)
            pthread_cond_wait(&ctx->بشپړ_cond, &ctx->بشپړ_mutex);
        ctx->بشپړ = 0;
        pthread_mutex_unlock(&ctx->بشپړ_mutex);
    }

    إذا (!ret)
        ret = atomic_load_explicit(&ctx->error, memory_order_relaxed);

    أرجع ret;
}

av_cold فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    AVSliceThread *ctx = *pctx;
    صحيح nb_workers, i;

    إذا (!ctx)
        أرجع;

    nb_workers = ctx->nb_تارونه;
    إذا (!ctx->main_func)
        nb_workers--;

    ctx->پای_ته_رسېدلی = 1;
    لكل (i = 0; i < nb_workers; i++) {
        کارګر_Context *w = &ctx->workers[i];
        pthread_mutex_قلف(&w->mutex);
        w->بشپړ = 0;
        pthread_cond_signal(&w->cond);
        pthread_mutex_unlock(&w->mutex);
    }

    لكل (i = 0; i < nb_workers; i++) {
        کارګر_Context *w = &ctx->workers[i];
        pthread_join(w->thread, عدم);
        pthread_cond_destroy(&w->cond);
        pthread_mutex_destroy(&w->mutex);
    }

    pthread_cond_destroy(&ctx->بشپړ_cond);
    pthread_mutex_destroy(&ctx->بشپړ_mutex);
    av_freep(&ctx->workers);
    av_freep(pctx);
}

/**
 * Backwards compatibility wrapper for the deprecated avpriv_ slicethread API.
 */

#إذا LIBAVUTIL_نسخه_MAJOR < 62

ساكن صحيح wrapper_کارګر(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه)
{
    AVSliceThread *ctx = priv;
    ctx->کارګر_func_v1(ctx->priv_v1, jobnr, threadnr, nb_jobs, nb_تارونه);
    أرجع 0;
}

ساكن صحيح wrapper_main(فراغ *priv)
{
    AVSliceThread *ctx = priv;
    ctx->main_func_v1(ctx->priv_v1);
    أرجع 0;
}

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کارګر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_تارونه)
{
    صحيح ret = avpriv_slicethread_create2(pctx, عدم, wrapper_کارګر,
                                         main_func ? wrapper_main : عدم,
                                         nb_تارونه);
    إذا (ret < 0)
        أرجع ret;

    (*pctx)->priv           = *pctx;
    (*pctx)->priv_v1        = priv;
    (*pctx)->کارګر_func_v1 = کارګر_func;
    (*pctx)->main_func_v1   = main_func;
    أرجع ret;
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    avpriv_slicethread_execute2(ctx, nb_jobs, execute_main);
}

#د_که_پای /* LIBAVUTIL_VERSION_MAJOR < 62 */

#وإلا /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */

صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*کارګر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_تارونه)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

فراغ avpriv_slicethread_free(AVSliceThread **pctx)
{
    av_assert0(!pctx || !*pctx);
}

#إذا LIBAVUTIL_نسخه_MAJOR < 62

صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*کارګر_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_تارونه),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_تارونه)
{
    *pctx = عدم;
    أرجع AVERROR(ENOSYS);
}

فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main)
{
    av_assert0(0);
}

#د_که_پای /* LIBAVUTIL_VERSION_MAJOR < 62 */

#د_که_پای /* HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS32THREADS */
