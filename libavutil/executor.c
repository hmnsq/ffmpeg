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

#nếu !HAVE_THREADS

#define ExecutorThread  char

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               do {} trong_khi(0)

#không_thì

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

typedef struct ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

struct AVExecutor {
    AVTaskCallbacks cb;
    số_nguyên thread_count;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    số_nguyên die;

    AVTask *tasks;
};

static AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = NULL;
    trả_về t;
}

static void add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

static số_nguyên run_one_task(AVExecutor *e, void *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    cho (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    nếu (*prev) {
        AVTask *t = remove_task(prev, *prev);
        nếu (e->thread_count > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        nếu (e->thread_count > 0)
            ff_mutex_lock(&e->lock);
        trả_về 1;
    }
    trả_về 0;
}

#nếu HAVE_THREADS
static void *executor_worker_task(void *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    void *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    trong_khi (1) {
        nếu (e->die) break;

        nếu (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    trả_về NULL;
}
#endif

static void executor_free(AVExecutor *e, const số_nguyên has_lock, const số_nguyên has_cond)
{
    nếu (e->thread_count) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        cho (số_nguyên i = 0; i < e->thread_count; i++)
            executor_thread_join(e->threads[i].thread, NULL);
    }
    nếu (has_cond)
        ff_cond_destroy(&e->cond);
    nếu (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(const AVTaskCallbacks *cb, số_nguyên thread_count)
{
    AVExecutor *e;
    số_nguyên has_lock = 0, has_cond = 0;
    nếu (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        trả_về NULL;

    e = av_mallocz(sizeof(*e));
    nếu (!e)
        trả_về NULL;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_count, 1), e->cb.local_context_size);
    nếu (!e->local_contexts)
        goto free_executor;

    e->threads = av_calloc(FFMAX(thread_count, 1), sizeof(*e->threads));
    nếu (!e->threads)
        goto free_executor;

    nếu (!thread_count)
        trả_về e;

    has_lock = !ff_mutex_init(&e->lock, NULL);
    has_cond = !ff_cond_init(&e->cond, NULL);

    nếu (!has_lock || !has_cond)
        goto free_executor;

    cho (/* nothing */; e->thread_count < thread_count; e->thread_count++) {
        ThreadInfo *ti = e->threads + e->thread_count;
        ti->e = e;
        nếu (executor_thread_create(&ti->thread, NULL, executor_worker_task, ti))
            goto free_executor;
    }
    trả_về e;

free_executor:
    executor_free(e, has_lock, has_cond);
    trả_về NULL;
}

void av_executor_free(AVExecutor **executor)
{
    số_nguyên thread_count;

    nếu (!executor || !*executor)
        trả_về;
    thread_count = (*executor)->thread_count;
    executor_free(*executor, thread_count, thread_count);
    *executor = NULL;
}

void av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    nếu (e->thread_count)
        ff_mutex_lock(&e->lock);
    nếu (t) {
        cho (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    nếu (e->thread_count) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    nếu (!e->thread_count || !HAVE_THREADS) {
        nếu (e->recursive)
            trả_về;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        trong_khi (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
