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

#якщо !HAVE_THREADS

#define ExecutorThread  char

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               do {} поки(0)

#інакше

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
    ціле thread_count;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    ціле die;

    AVTask *tasks;
};

static AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = NULL;
    повернути t;
}

static void add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

static ціле run_one_task(AVExecutor *e, void *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    для (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    якщо (*prev) {
        AVTask *t = remove_task(prev, *prev);
        якщо (e->thread_count > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        якщо (e->thread_count > 0)
            ff_mutex_lock(&e->lock);
        повернути 1;
    }
    повернути 0;
}

#якщо HAVE_THREADS
static void *executor_worker_task(void *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    void *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    поки (1) {
        якщо (e->die) break;

        якщо (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    повернути NULL;
}
#endif

static void executor_free(AVExecutor *e, const ціле has_lock, const ціле has_cond)
{
    якщо (e->thread_count) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        для (ціле i = 0; i < e->thread_count; i++)
            executor_thread_join(e->threads[i].thread, NULL);
    }
    якщо (has_cond)
        ff_cond_destroy(&e->cond);
    якщо (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(const AVTaskCallbacks *cb, ціле thread_count)
{
    AVExecutor *e;
    ціле has_lock = 0, has_cond = 0;
    якщо (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        повернути NULL;

    e = av_mallocz(sizeof(*e));
    якщо (!e)
        повернути NULL;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_count, 1), e->cb.local_context_size);
    якщо (!e->local_contexts)
        goto free_executor;

    e->threads = av_calloc(FFMAX(thread_count, 1), sizeof(*e->threads));
    якщо (!e->threads)
        goto free_executor;

    якщо (!thread_count)
        повернути e;

    has_lock = !ff_mutex_init(&e->lock, NULL);
    has_cond = !ff_cond_init(&e->cond, NULL);

    якщо (!has_lock || !has_cond)
        goto free_executor;

    для (/* nothing */; e->thread_count < thread_count; e->thread_count++) {
        ThreadInfo *ti = e->threads + e->thread_count;
        ti->e = e;
        якщо (executor_thread_create(&ti->thread, NULL, executor_worker_task, ti))
            goto free_executor;
    }
    повернути e;

free_executor:
    executor_free(e, has_lock, has_cond);
    повернути NULL;
}

void av_executor_free(AVExecutor **executor)
{
    ціле thread_count;

    якщо (!executor || !*executor)
        повернути;
    thread_count = (*executor)->thread_count;
    executor_free(*executor, thread_count, thread_count);
    *executor = NULL;
}

void av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    якщо (e->thread_count)
        ff_mutex_lock(&e->lock);
    якщо (t) {
        для (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    якщо (e->thread_count) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    якщо (!e->thread_count || !HAVE_THREADS) {
        якщо (e->recursive)
            повернути;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        поки (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
