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

#إذا !HAVE_دھاگے

#تعریف_کرو ExecutorThread  حرف

#تعریف_کرو executor_thread_create(t, a, s, ar)      0
#تعریف_کرو executor_thread_join(t, r)               افعل {} طالما(0)

#وإلا

#تعریف_کرو ExecutorThread  pthread_t

#تعریف_کرو executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#تعریف_کرو executor_thread_join(t, r)               pthread_join(t, r)

#جے_انت //!HAVE_THREADS

تعريفنوع بنية ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

بنية AVExecutor {
    AVTaskCallbacks cb;
    صحيح thread_گنتی;
    bool recursive;

    ThreadInfo *دھاگے;
    uint8_t *local_contexts;

    AVMutex جندرا;
    AVCond cond;
    صحيح die;

    AVTask *tasks;
};

ساكن AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->اگلا;
    t->اگلا = عدم;
    أرجع t;
}

ساكن فراغ جوڑو_task(AVTask **prev, AVTask *t)
{
    t->اگلا = *prev;
    *prev   = t;
}

ساكن صحيح لگاتار_one_task(AVExecutor *e, فراغ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    لكل (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_انکڑے); prev = &(*prev)->اگلا)
        /* nothing */;
    إذا (*prev) {
        AVTask *t = remove_task(prev, *prev);
        إذا (e->thread_گنتی > 0)
            ff_mutex_unlock(&e->جندرا);
        cb->لگاتار(t, lc, cb->user_انکڑے);
        إذا (e->thread_گنتی > 0)
            ff_mutex_جندرا(&e->جندرا);
        أرجع 1;
    }
    أرجع 0;
}

#إذا HAVE_دھاگے
ساكن فراغ *executor_کامہ_task(فراغ *انکڑے)
{
    ThreadInfo *ti = (ThreadInfo*)انکڑے;
    AVExecutor *e  = ti->e;
    فراغ *lc       = e->local_contexts + (ti - e->دھاگے) * e->cb.local_context_ناپ;

    ff_mutex_جندرا(&e->جندرا);
    طالما (1) {
        إذا (e->die) اكسر;

        إذا (!لگاتار_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->جندرا);
        }
    }
    ff_mutex_unlock(&e->جندرا);
    أرجع عدم;
}
#جے_انت

ساكن فراغ executor_free(AVExecutor *e, ثابت صحيح has_جندرا, ثابت صحيح has_cond)
{
    إذا (e->thread_گنتی) {
        //signal die
        ff_mutex_جندرا(&e->جندرا);
        e->die = 1;
        ff_cond_نشر(&e->cond);
        ff_mutex_unlock(&e->جندرا);

        لكل (صحيح i = 0; i < e->thread_گنتی; i++)
            executor_thread_join(e->دھاگے[i].thread, عدم);
    }
    إذا (has_cond)
        ff_cond_destroy(&e->cond);
    إذا (has_جندرا)
        ff_mutex_destroy(&e->جندرا);

    av_free(e->دھاگے);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحيح thread_گنتی)
{
    AVExecutor *e;
    صحيح has_جندرا = 0, has_cond = 0;
    إذا (!cb || !cb->user_انکڑے || !cb->ready || !cb->لگاتار || !cb->ترجیح_higher)
        أرجع عدم;

    e = av_mallocz(حجم(*e));
    إذا (!e)
        أرجع عدم;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_گنتی, 1), e->cb.local_context_ناپ);
    إذا (!e->local_contexts)
        اذهب free_executor;

    e->دھاگے = av_calloc(FFMAX(thread_گنتی, 1), حجم(*e->دھاگے));
    إذا (!e->دھاگے)
        اذهب free_executor;

    إذا (!thread_گنتی)
        أرجع e;

    has_جندرا = !ff_mutex_init(&e->جندرا, عدم);
    has_cond = !ff_cond_init(&e->cond, عدم);

    إذا (!has_جندرا || !has_cond)
        اذهب free_executor;

    لكل (/* nothing */; e->thread_گنتی < thread_گنتی; e->thread_گنتی++) {
        ThreadInfo *ti = e->دھاگے + e->thread_گنتی;
        ti->e = e;
        إذا (executor_thread_create(&ti->thread, عدم, executor_کامہ_task, ti))
            اذهب free_executor;
    }
    أرجع e;

free_executor:
    executor_free(e, has_جندرا, has_cond);
    أرجع عدم;
}

فراغ av_executor_free(AVExecutor **executor)
{
    صحيح thread_گنتی;

    إذا (!executor || !*executor)
        أرجع;
    thread_گنتی = (*executor)->thread_گنتی;
    executor_free(*executor, thread_گنتی, thread_گنتی);
    *executor = عدم;
}

فراغ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    إذا (e->thread_گنتی)
        ff_mutex_جندرا(&e->جندرا);
    إذا (t) {
        لكل (prev = &e->tasks; *prev && cb->ترجیح_higher(*prev, t); prev = &(*prev)->اگلا)
            /* nothing */;
        جوڑو_task(prev, t);
    }
    إذا (e->thread_گنتی) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->جندرا);
    }

    إذا (!e->thread_گنتی || !HAVE_دھاگے) {
        إذا (e->recursive)
            أرجع;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        طالما (لگاتار_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
