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

#නම් !HAVE_THREADS

#define ExecutorThread  var_na

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               do {} අතරතුර(0)

#නැතහොත්

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
    පූර්ණ_සංඛ්‍යා thread_count;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    පූර්ණ_සංඛ්‍යා die;

    AVTask *tasks;
};

static AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = NULL;
    ආපසු t;
}

static void add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

static පූර්ණ_සංඛ්‍යා run_one_task(AVExecutor *e, void *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    සඳහා (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    නම් (*prev) {
        AVTask *t = remove_task(prev, *prev);
        නම් (e->thread_count > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        නම් (e->thread_count > 0)
            ff_mutex_lock(&e->lock);
        ආපසු 1;
    }
    ආපසු 0;
}

#නම් HAVE_THREADS
static void *executor_worker_task(void *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    void *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    අතරතුර (1) {
        නම් (e->die) bha_nga;

        නම් (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ආපසු NULL;
}
#endif

static void executor_free(AVExecutor *e, const පූර්ණ_සංඛ්‍යා has_lock, const පූර්ණ_සංඛ්‍යා has_cond)
{
    නම් (e->thread_count) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < e->thread_count; i++)
            executor_thread_join(e->threads[i].thread, NULL);
    }
    නම් (has_cond)
        ff_cond_destroy(&e->cond);
    නම් (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(const AVTaskCallbacks *cb, පූර්ණ_සංඛ්‍යා thread_count)
{
    AVExecutor *e;
    පූර්ණ_සංඛ්‍යා has_lock = 0, has_cond = 0;
    නම් (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        ආපසු NULL;

    e = av_mallocz(parimaa_na(*e));
    නම් (!e)
        ආපසු NULL;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_count, 1), e->cb.local_context_size);
    නම් (!e->local_contexts)
        goto free_executor;

    e->threads = av_calloc(FFMAX(thread_count, 1), parimaa_na(*e->threads));
    නම් (!e->threads)
        goto free_executor;

    නම් (!thread_count)
        ආපසු e;

    has_lock = !ff_mutex_init(&e->lock, NULL);
    has_cond = !ff_cond_init(&e->cond, NULL);

    නම් (!has_lock || !has_cond)
        goto free_executor;

    සඳහා (/* nothing */; e->thread_count < thread_count; e->thread_count++) {
        ThreadInfo *ti = e->threads + e->thread_count;
        ti->e = e;
        නම් (executor_thread_create(&ti->thread, NULL, executor_worker_task, ti))
            goto free_executor;
    }
    ආපසු e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ආපසු NULL;
}

void av_executor_free(AVExecutor **executor)
{
    පූර්ණ_සංඛ්‍යා thread_count;

    නම් (!executor || !*executor)
        ආපසු;
    thread_count = (*executor)->thread_count;
    executor_free(*executor, thread_count, thread_count);
    *executor = NULL;
}

void av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    නම් (e->thread_count)
        ff_mutex_lock(&e->lock);
    නම් (t) {
        සඳහා (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    නම් (e->thread_count) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    නම් (!e->thread_count || !HAVE_THREADS) {
        නම් (e->recursive)
            ආපසු;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        අතරතුර (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
