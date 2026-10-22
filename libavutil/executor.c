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

#إذا !HAVE_نخها

#تعریف_کن ExecutorThread  حرف

#تعریف_کن executor_thread_create(t, a, s, ar)      0
#تعریف_کن executor_thread_join(t, r)               افعل {} طالما(0)

#وإلا

#تعریف_کن ExecutorThread  pthread_t

#تعریف_کن executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#تعریف_کن executor_thread_join(t, r)               pthread_join(t, r)

#پایان_اگر //!HAVE_THREADS

تعريفنوع بنية ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

بنية AVExecutor {
    AVTaskCallbacks cb;
    صحيح thread_شمار;
    bool recursive;

    ThreadInfo *نخها;
    uint8_t *local_contexts;

    AVMutex قفل_2;
    AVCond cond;
    صحيح die;

    AVTask *tasks;
};

ساكن AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->بعدی;
    t->بعدی = عدم;
    أرجع t;
}

ساكن فراغ جمع_کن_task(AVTask **prev, AVTask *t)
{
    t->بعدی = *prev;
    *prev   = t;
}

ساكن صحيح پیاپی_one_task(AVExecutor *e, فراغ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    لكل (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_داده); prev = &(*prev)->بعدی)
        /* nothing */;
    إذا (*prev) {
        AVTask *t = remove_task(prev, *prev);
        إذا (e->thread_شمار > 0)
            ff_mutex_unlock(&e->قفل_2);
        cb->پیاپی(t, lc, cb->user_داده);
        إذا (e->thread_شمار > 0)
            ff_mutex_قفل(&e->قفل_2);
        أرجع 1;
    }
    أرجع 0;
}

#إذا HAVE_نخها
ساكن فراغ *executor_کارگر_task(فراغ *داده)
{
    ThreadInfo *ti = (ThreadInfo*)داده;
    AVExecutor *e  = ti->e;
    فراغ *lc       = e->local_contexts + (ti - e->نخها) * e->cb.local_context_اندازه;

    ff_mutex_قفل(&e->قفل_2);
    طالما (1) {
        إذا (e->die) اكسر;

        إذا (!پیاپی_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->قفل_2);
        }
    }
    ff_mutex_unlock(&e->قفل_2);
    أرجع عدم;
}
#پایان_اگر

ساكن فراغ executor_free(AVExecutor *e, ثابت صحيح has_قفل, ثابت صحيح has_cond)
{
    إذا (e->thread_شمار) {
        //signal die
        ff_mutex_قفل(&e->قفل_2);
        e->die = 1;
        ff_cond_پخش(&e->cond);
        ff_mutex_unlock(&e->قفل_2);

        لكل (صحيح i = 0; i < e->thread_شمار; i++)
            executor_thread_join(e->نخها[i].thread, عدم);
    }
    إذا (has_cond)
        ff_cond_destroy(&e->cond);
    إذا (has_قفل)
        ff_mutex_destroy(&e->قفل_2);

    av_free(e->نخها);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحيح thread_شمار)
{
    AVExecutor *e;
    صحيح has_قفل = 0, has_cond = 0;
    إذا (!cb || !cb->user_داده || !cb->ready || !cb->پیاپی || !cb->اولویت_higher)
        أرجع عدم;

    e = av_mallocz(حجم(*e));
    إذا (!e)
        أرجع عدم;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_شمار, 1), e->cb.local_context_اندازه);
    إذا (!e->local_contexts)
        اذهب free_executor;

    e->نخها = av_calloc(FFMAX(thread_شمار, 1), حجم(*e->نخها));
    إذا (!e->نخها)
        اذهب free_executor;

    إذا (!thread_شمار)
        أرجع e;

    has_قفل = !ff_mutex_init(&e->قفل_2, عدم);
    has_cond = !ff_cond_init(&e->cond, عدم);

    إذا (!has_قفل || !has_cond)
        اذهب free_executor;

    لكل (/* nothing */; e->thread_شمار < thread_شمار; e->thread_شمار++) {
        ThreadInfo *ti = e->نخها + e->thread_شمار;
        ti->e = e;
        إذا (executor_thread_create(&ti->thread, عدم, executor_کارگر_task, ti))
            اذهب free_executor;
    }
    أرجع e;

free_executor:
    executor_free(e, has_قفل, has_cond);
    أرجع عدم;
}

فراغ av_executor_free(AVExecutor **executor)
{
    صحيح thread_شمار;

    إذا (!executor || !*executor)
        أرجع;
    thread_شمار = (*executor)->thread_شمار;
    executor_free(*executor, thread_شمار, thread_شمار);
    *executor = عدم;
}

فراغ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    إذا (e->thread_شمار)
        ff_mutex_قفل(&e->قفل_2);
    إذا (t) {
        لكل (prev = &e->tasks; *prev && cb->اولویت_higher(*prev, t); prev = &(*prev)->بعدی)
            /* nothing */;
        جمع_کن_task(prev, t);
    }
    إذا (e->thread_شمار) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->قفل_2);
    }

    إذا (!e->thread_شمار || !HAVE_نخها) {
        إذا (e->recursive)
            أرجع;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        طالما (پیاپی_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
