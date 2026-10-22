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

#অন্তর্ভাৱ "config.h"

#অন্তর্ভাৱ <stdbool.h>

#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "thread.h"

#অন্তর্ভাৱ "executor.h"

#যদি !HAVE_THREADS

#define ExecutorThread  ৱর্ণ

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               কৰা {} যেতিয়ালৈ(0)

#অন্যথা

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

প্রকারনির্দেশ সংরচনা ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

সংরচনা AVExecutor {
    AVTaskCallbacks cb;
    পূর্ণাঙ্ক thread_গুনতি;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    পূর্ণাঙ্ক die;

    AVTask *tasks;
};

স্থির AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = রিক্ত;
    ঘূৰাই t;
}

স্থির শূন্য add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

স্থির পূর্ণাঙ্ক run_one_task(AVExecutor *e, শূন্য *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    বাবে (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    যদি (*prev) {
        AVTask *t = remove_task(prev, *prev);
        যদি (e->thread_গুনতি > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        যদি (e->thread_গুনতি > 0)
            ff_mutex_lock(&e->lock);
        ঘূৰাই 1;
    }
    ঘূৰাই 0;
}

#যদি HAVE_THREADS
স্থির শূন্য *executor_worker_task(শূন্য *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    শূন্য *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    যেতিয়ালৈ (1) {
        যদি (e->die) ভঙ্গ;

        যদি (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ঘূৰাই রিক্ত;
}
#endif

স্থির শূন্য executor_free(AVExecutor *e, ধ্রুৱ পূর্ণাঙ্ক has_lock, ধ্রুৱ পূর্ণাঙ্ক has_cond)
{
    যদি (e->thread_গুনতি) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        বাবে (পূর্ণাঙ্ক i = 0; i < e->thread_গুনতি; i++)
            executor_thread_join(e->threads[i].thread, রিক্ত);
    }
    যদি (has_cond)
        ff_cond_destroy(&e->cond);
    যদি (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ধ্রুৱ AVTaskCallbacks *cb, পূর্ণাঙ্ক thread_গুনতি)
{
    AVExecutor *e;
    পূর্ণাঙ্ক has_lock = 0, has_cond = 0;
    যদি (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        ঘূৰাই রিক্ত;

    e = av_mallocz(পরিমাণ(*e));
    যদি (!e)
        ঘূৰাই রিক্ত;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_গুনতি, 1), e->cb.local_context_size);
    যদি (!e->local_contexts)
        গচ্ছ free_executor;

    e->threads = av_calloc(FFMAX(thread_গুনতি, 1), পরিমাণ(*e->threads));
    যদি (!e->threads)
        গচ্ছ free_executor;

    যদি (!thread_গুনতি)
        ঘূৰাই e;

    has_lock = !ff_mutex_init(&e->lock, রিক্ত);
    has_cond = !ff_cond_init(&e->cond, রিক্ত);

    যদি (!has_lock || !has_cond)
        গচ্ছ free_executor;

    বাবে (/* nothing */; e->thread_গুনতি < thread_গুনতি; e->thread_গুনতি++) {
        ThreadInfo *ti = e->threads + e->thread_গুনতি;
        ti->e = e;
        যদি (executor_thread_create(&ti->thread, রিক্ত, executor_worker_task, ti))
            গচ্ছ free_executor;
    }
    ঘূৰাই e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ঘূৰাই রিক্ত;
}

শূন্য av_executor_free(AVExecutor **executor)
{
    পূর্ণাঙ্ক thread_গুনতি;

    যদি (!executor || !*executor)
        ঘূৰাই;
    thread_গুনতি = (*executor)->thread_গুনতি;
    executor_free(*executor, thread_গুনতি, thread_গুনতি);
    *executor = রিক্ত;
}

শূন্য av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    যদি (e->thread_গুনতি)
        ff_mutex_lock(&e->lock);
    যদি (t) {
        বাবে (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    যদি (e->thread_গুনতি) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    যদি (!e->thread_গুনতি || !HAVE_THREADS) {
        যদি (e->recursive)
            ঘূৰাই;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        যেতিয়ালৈ (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
