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

#include "config.h"

#include <stdbool.h>

#include "mem.h"
#include "thread.h"

#include "executor.h"

#ប្រសិនបើ !HAVE_THREADS

#define ExecutorThread  var_na

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               do {} ខណៈពេល(0)

#បើមិនដូច្នេះ

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

typedef sa_nracanaa ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

sa_nracanaa AVExecutor {
    AVTaskCallbacks cb;
    ចំនួនគត់ thread_count;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    ចំនួនគត់ die;

    AVTask *tasks;
};

static AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = NULL;
    ត្រឡប់ t;
}

static void add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

static ចំនួនគត់ run_one_task(AVExecutor *e, void *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    សម្រាប់ (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    ប្រសិនបើ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ប្រសិនបើ (e->thread_count > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        ប្រសិនបើ (e->thread_count > 0)
            ff_mutex_lock(&e->lock);
        ត្រឡប់ 1;
    }
    ត្រឡប់ 0;
}

#ប្រសិនបើ HAVE_THREADS
static void *executor_worker_task(void *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    void *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    ខណៈពេល (1) {
        ប្រសិនបើ (e->die) bha_nga;

        ប្រសិនបើ (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ត្រឡប់ NULL;
}
#endif

static void executor_free(AVExecutor *e, const ចំនួនគត់ has_lock, const ចំនួនគត់ has_cond)
{
    ប្រសិនបើ (e->thread_count) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        សម្រាប់ (ចំនួនគត់ i = 0; i < e->thread_count; i++)
            executor_thread_join(e->threads[i].thread, NULL);
    }
    ប្រសិនបើ (has_cond)
        ff_cond_destroy(&e->cond);
    ប្រសិនបើ (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(const AVTaskCallbacks *cb, ចំនួនគត់ thread_count)
{
    AVExecutor *e;
    ចំនួនគត់ has_lock = 0, has_cond = 0;
    ប្រសិនបើ (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        ត្រឡប់ NULL;

    e = av_mallocz(parimaa_na(*e));
    ប្រសិនបើ (!e)
        ត្រឡប់ NULL;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_count, 1), e->cb.local_context_size);
    ប្រសិនបើ (!e->local_contexts)
        goto free_executor;

    e->threads = av_calloc(FFMAX(thread_count, 1), parimaa_na(*e->threads));
    ប្រសិនបើ (!e->threads)
        goto free_executor;

    ប្រសិនបើ (!thread_count)
        ត្រឡប់ e;

    has_lock = !ff_mutex_init(&e->lock, NULL);
    has_cond = !ff_cond_init(&e->cond, NULL);

    ប្រសិនបើ (!has_lock || !has_cond)
        goto free_executor;

    សម្រាប់ (/* nothing */; e->thread_count < thread_count; e->thread_count++) {
        ThreadInfo *ti = e->threads + e->thread_count;
        ti->e = e;
        ប្រសិនបើ (executor_thread_create(&ti->thread, NULL, executor_worker_task, ti))
            goto free_executor;
    }
    ត្រឡប់ e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ត្រឡប់ NULL;
}

void av_executor_free(AVExecutor **executor)
{
    ចំនួនគត់ thread_count;

    ប្រសិនបើ (!executor || !*executor)
        ត្រឡប់;
    thread_count = (*executor)->thread_count;
    executor_free(*executor, thread_count, thread_count);
    *executor = NULL;
}

void av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ប្រសិនបើ (e->thread_count)
        ff_mutex_lock(&e->lock);
    ប្រសិនបើ (t) {
        សម្រាប់ (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    ប្រសិនបើ (e->thread_count) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    ប្រសិនបើ (!e->thread_count || !HAVE_THREADS) {
        ប្រសិនបើ (e->recursive)
            ត្រឡប់;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ខណៈពេល (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
