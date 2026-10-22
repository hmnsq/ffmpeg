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

#إذا !HAVE_تارونه

#تعریف_کړه ExecutorThread  حرف

#تعریف_کړه executor_thread_create(t, a, s, ar)      0
#تعریف_کړه executor_thread_join(t, r)               افعل {} طالما(0)

#وإلا

#تعریف_کړه ExecutorThread  pthread_t

#تعریف_کړه executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#تعریف_کړه executor_thread_join(t, r)               pthread_join(t, r)

#د_که_پای //!HAVE_THREADS

تعريفنوع بنية ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

بنية AVExecutor {
    AVTaskCallbacks cb;
    صحيح thread_شمېر;
    bool recursive;

    ThreadInfo *تارونه;
    uint8_t *local_contexts;

    AVMutex قلف;
    AVCond cond;
    صحيح die;

    AVTask *tasks;
};

ساكن AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->بل;
    t->بل = عدم;
    أرجع t;
}

ساكن فراغ جمع_کړه_task(AVTask **prev, AVTask *t)
{
    t->بل = *prev;
    *prev   = t;
}

ساكن صحيح پرلپسې_one_task(AVExecutor *e, فراغ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    لكل (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_معلومات); prev = &(*prev)->بل)
        /* nothing */;
    إذا (*prev) {
        AVTask *t = remove_task(prev, *prev);
        إذا (e->thread_شمېر > 0)
            ff_mutex_unlock(&e->قلف);
        cb->پرلپسې(t, lc, cb->user_معلومات);
        إذا (e->thread_شمېر > 0)
            ff_mutex_قلف(&e->قلف);
        أرجع 1;
    }
    أرجع 0;
}

#إذا HAVE_تارونه
ساكن فراغ *executor_کارګر_task(فراغ *معلومات)
{
    ThreadInfo *ti = (ThreadInfo*)معلومات;
    AVExecutor *e  = ti->e;
    فراغ *lc       = e->local_contexts + (ti - e->تارونه) * e->cb.local_context_اندازه;

    ff_mutex_قلف(&e->قلف);
    طالما (1) {
        إذا (e->die) اكسر;

        إذا (!پرلپسې_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->قلف);
        }
    }
    ff_mutex_unlock(&e->قلف);
    أرجع عدم;
}
#د_که_پای

ساكن فراغ executor_free(AVExecutor *e, ثابت صحيح has_قلف, ثابت صحيح has_cond)
{
    إذا (e->thread_شمېر) {
        //signal die
        ff_mutex_قلف(&e->قلف);
        e->die = 1;
        ff_cond_خپرونه(&e->cond);
        ff_mutex_unlock(&e->قلف);

        لكل (صحيح i = 0; i < e->thread_شمېر; i++)
            executor_thread_join(e->تارونه[i].thread, عدم);
    }
    إذا (has_cond)
        ff_cond_destroy(&e->cond);
    إذا (has_قلف)
        ff_mutex_destroy(&e->قلف);

    av_free(e->تارونه);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحيح thread_شمېر)
{
    AVExecutor *e;
    صحيح has_قلف = 0, has_cond = 0;
    إذا (!cb || !cb->user_معلومات || !cb->ready || !cb->پرلپسې || !cb->لومړیتوب_higher)
        أرجع عدم;

    e = av_mallocz(حجم(*e));
    إذا (!e)
        أرجع عدم;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_شمېر, 1), e->cb.local_context_اندازه);
    إذا (!e->local_contexts)
        اذهب free_executor;

    e->تارونه = av_calloc(FFMAX(thread_شمېر, 1), حجم(*e->تارونه));
    إذا (!e->تارونه)
        اذهب free_executor;

    إذا (!thread_شمېر)
        أرجع e;

    has_قلف = !ff_mutex_init(&e->قلف, عدم);
    has_cond = !ff_cond_init(&e->cond, عدم);

    إذا (!has_قلف || !has_cond)
        اذهب free_executor;

    لكل (/* nothing */; e->thread_شمېر < thread_شمېر; e->thread_شمېر++) {
        ThreadInfo *ti = e->تارونه + e->thread_شمېر;
        ti->e = e;
        إذا (executor_thread_create(&ti->thread, عدم, executor_کارګر_task, ti))
            اذهب free_executor;
    }
    أرجع e;

free_executor:
    executor_free(e, has_قلف, has_cond);
    أرجع عدم;
}

فراغ av_executor_free(AVExecutor **executor)
{
    صحيح thread_شمېر;

    إذا (!executor || !*executor)
        أرجع;
    thread_شمېر = (*executor)->thread_شمېر;
    executor_free(*executor, thread_شمېر, thread_شمېر);
    *executor = عدم;
}

فراغ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    إذا (e->thread_شمېر)
        ff_mutex_قلف(&e->قلف);
    إذا (t) {
        لكل (prev = &e->tasks; *prev && cb->لومړیتوب_higher(*prev, t); prev = &(*prev)->بل)
            /* nothing */;
        جمع_کړه_task(prev, t);
    }
    إذا (e->thread_شمېر) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->قلف);
    }

    إذا (!e->thread_شمېر || !HAVE_تارونه) {
        إذا (e->recursive)
            أرجع;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        طالما (پرلپسې_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
