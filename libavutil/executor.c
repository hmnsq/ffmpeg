/*
 * Copyright (C) 2023 Nuo Mi
 *
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

#ضمن "config.h"

#ضمن <stdbool.h>

#ضمن "mem.h"
#ضمن "thread.h"

#ضمن "executor.h"

#إذا !HAVE_ڌاڳا

#وصف_ڪريو ExecutorThread  حرف

#وصف_ڪريو executor_thread_create(t, a, s, ar)      0
#وصف_ڪريو executor_thread_join(t, r)               افعل {} طالما(0)

#وإلا

#وصف_ڪريو ExecutorThread  pthread_t

#وصف_ڪريو executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#وصف_ڪريو executor_thread_join(t, r)               pthread_join(t, r)

#جيڪڏهن_پورو //!HAVE_THREADS

تعريفنوع بنية ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

بنية AVExecutor {
    AVTaskCallbacks cb;
    صحيح thread_ڳڻپ;
    bool recursive;

    ThreadInfo *ڌاڳا;
    uint8_t *local_contexts;

    AVMutex تالو;
    AVCond cond;
    صحيح die;

    AVTask *tasks;
};

ساكن AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->ايندڙ;
    t->ايندڙ = عدم;
    أرجع t;
}

ساكن فراغ جوڙيو_task(AVTask **prev, AVTask *t)
{
    t->ايندڙ = *prev;
    *prev   = t;
}

ساكن صحيح لاڳيتو_one_task(AVExecutor *e, فراغ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    لكل (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_معلومات); prev = &(*prev)->ايندڙ)
        /* nothing */;
    إذا (*prev) {
        AVTask *t = remove_task(prev, *prev);
        إذا (e->thread_ڳڻپ > 0)
            ff_mutex_unlock(&e->تالو);
        cb->لاڳيتو(t, lc, cb->user_معلومات);
        إذا (e->thread_ڳڻپ > 0)
            ff_mutex_تالو(&e->تالو);
        أرجع 1;
    }
    أرجع 0;
}

#إذا HAVE_ڌاڳا
ساكن فراغ *executor_ڪم_ڪندڙ_task(فراغ *معلومات)
{
    ThreadInfo *ti = (ThreadInfo*)معلومات;
    AVExecutor *e  = ti->e;
    فراغ *lc       = e->local_contexts + (ti - e->ڌاڳا) * e->cb.local_context_سائيز;

    ff_mutex_تالو(&e->تالو);
    طالما (1) {
        إذا (e->die) اكسر;

        إذا (!لاڳيتو_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->تالو);
        }
    }
    ff_mutex_unlock(&e->تالو);
    أرجع عدم;
}
#جيڪڏهن_پورو

ساكن فراغ executor_free(AVExecutor *e, ثابت صحيح has_تالو, ثابت صحيح has_cond)
{
    إذا (e->thread_ڳڻپ) {
        //signal die
        ff_mutex_تالو(&e->تالو);
        e->die = 1;
        ff_cond_نشر(&e->cond);
        ff_mutex_unlock(&e->تالو);

        لكل (صحيح i = 0; i < e->thread_ڳڻپ; i++)
            executor_thread_join(e->ڌاڳا[i].thread, عدم);
    }
    إذا (has_cond)
        ff_cond_destroy(&e->cond);
    إذا (has_تالو)
        ff_mutex_destroy(&e->تالو);

    av_free(e->ڌاڳا);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحيح thread_ڳڻپ)
{
    AVExecutor *e;
    صحيح has_تالو = 0, has_cond = 0;
    إذا (!cb || !cb->user_معلومات || !cb->ready || !cb->لاڳيتو || !cb->ترجيح_higher)
        أرجع عدم;

    e = av_mallocz(حجم(*e));
    إذا (!e)
        أرجع عدم;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ڳڻپ, 1), e->cb.local_context_سائيز);
    إذا (!e->local_contexts)
        اذهب free_executor;

    e->ڌاڳا = av_calloc(FFMAX(thread_ڳڻپ, 1), حجم(*e->ڌاڳا));
    إذا (!e->ڌاڳا)
        اذهب free_executor;

    إذا (!thread_ڳڻپ)
        أرجع e;

    has_تالو = !ff_mutex_init(&e->تالو, عدم);
    has_cond = !ff_cond_init(&e->cond, عدم);

    إذا (!has_تالو || !has_cond)
        اذهب free_executor;

    لكل (/* nothing */; e->thread_ڳڻپ < thread_ڳڻپ; e->thread_ڳڻپ++) {
        ThreadInfo *ti = e->ڌاڳا + e->thread_ڳڻپ;
        ti->e = e;
        إذا (executor_thread_create(&ti->thread, عدم, executor_ڪم_ڪندڙ_task, ti))
            اذهب free_executor;
    }
    أرجع e;

free_executor:
    executor_free(e, has_تالو, has_cond);
    أرجع عدم;
}

فراغ av_executor_free(AVExecutor **executor)
{
    صحيح thread_ڳڻپ;

    إذا (!executor || !*executor)
        أرجع;
    thread_ڳڻپ = (*executor)->thread_ڳڻپ;
    executor_free(*executor, thread_ڳڻپ, thread_ڳڻپ);
    *executor = عدم;
}

فراغ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    إذا (e->thread_ڳڻپ)
        ff_mutex_تالو(&e->تالو);
    إذا (t) {
        لكل (prev = &e->tasks; *prev && cb->ترجيح_higher(*prev, t); prev = &(*prev)->ايندڙ)
            /* nothing */;
        جوڙيو_task(prev, t);
    }
    إذا (e->thread_ڳڻپ) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->تالو);
    }

    إذا (!e->thread_ڳڻپ || !HAVE_ڌاڳا) {
        إذا (e->recursive)
            أرجع;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        طالما (لاڳيتو_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
