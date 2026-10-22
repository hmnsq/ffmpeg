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

#إذا !HAVE_THREADS

#define ExecutorThread  حرف

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               افعل {} طالما(0)

#وإلا

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

تعريفنوع بنية ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

بنية AVExecutor {
    AVTaskCallbacks cb;
    صحيح thread_گنتی;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    صحيح die;

    AVTask *tasks;
};

ساكن AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = عدم;
    أرجع t;
}

ساكن فراغ add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

ساكن صحيح run_one_task(AVExecutor *e, فراغ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    لكل (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    إذا (*prev) {
        AVTask *t = remove_task(prev, *prev);
        إذا (e->thread_گنتی > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        إذا (e->thread_گنتی > 0)
            ff_mutex_lock(&e->lock);
        أرجع 1;
    }
    أرجع 0;
}

#إذا HAVE_THREADS
ساكن فراغ *executor_worker_task(فراغ *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    فراغ *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    طالما (1) {
        إذا (e->die) اكسر;

        إذا (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    أرجع عدم;
}
#endif

ساكن فراغ executor_free(AVExecutor *e, ثابت صحيح has_lock, ثابت صحيح has_cond)
{
    إذا (e->thread_گنتی) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        لكل (صحيح i = 0; i < e->thread_گنتی; i++)
            executor_thread_join(e->threads[i].thread, عدم);
    }
    إذا (has_cond)
        ff_cond_destroy(&e->cond);
    إذا (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحيح thread_گنتی)
{
    AVExecutor *e;
    صحيح has_lock = 0, has_cond = 0;
    إذا (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        أرجع عدم;

    e = av_mallocz(حجم(*e));
    إذا (!e)
        أرجع عدم;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_گنتی, 1), e->cb.local_context_size);
    إذا (!e->local_contexts)
        اذهب free_executor;

    e->threads = av_calloc(FFMAX(thread_گنتی, 1), حجم(*e->threads));
    إذا (!e->threads)
        اذهب free_executor;

    إذا (!thread_گنتی)
        أرجع e;

    has_lock = !ff_mutex_init(&e->lock, عدم);
    has_cond = !ff_cond_init(&e->cond, عدم);

    إذا (!has_lock || !has_cond)
        اذهب free_executor;

    لكل (/* nothing */; e->thread_گنتی < thread_گنتی; e->thread_گنتی++) {
        ThreadInfo *ti = e->threads + e->thread_گنتی;
        ti->e = e;
        إذا (executor_thread_create(&ti->thread, عدم, executor_worker_task, ti))
            اذهب free_executor;
    }
    أرجع e;

free_executor:
    executor_free(e, has_lock, has_cond);
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
        ff_mutex_lock(&e->lock);
    إذا (t) {
        لكل (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    إذا (e->thread_گنتی) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    إذا (!e->thread_گنتی || !HAVE_THREADS) {
        إذا (e->recursive)
            أرجع;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        طالما (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
