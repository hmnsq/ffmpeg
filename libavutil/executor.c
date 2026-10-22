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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <stdbool.h>

#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "thread.h"

#અન્તર્ભાવ "executor.h"

#જો !HAVE_THREADS

#define ExecutorThread  અક્ષર

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               કરો {} જ્યારે(0)

#નહીંતર

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

પ્રકારવ્યાખ્યા સંરચના ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

સંરચના AVExecutor {
    AVTaskCallbacks cb;
    પૂર્ણાંક thread_ગણતરી;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    પૂર્ણાંક die;

    AVTask *tasks;
};

સ્થિર AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = ખાલી;
    પાછા t;
}

સ્થિર શૂન્ય add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

સ્થિર પૂર્ણાંક run_one_task(AVExecutor *e, શૂન્ય *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    માટે (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    જો (*prev) {
        AVTask *t = remove_task(prev, *prev);
        જો (e->thread_ગણતરી > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        જો (e->thread_ગણતરી > 0)
            ff_mutex_lock(&e->lock);
        પાછા 1;
    }
    પાછા 0;
}

#જો HAVE_THREADS
સ્થિર શૂન્ય *executor_worker_task(શૂન્ય *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    શૂન્ય *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    જ્યારે (1) {
        જો (e->die) તોડો;

        જો (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    પાછા ખાલી;
}
#endif

સ્થિર શૂન્ય executor_free(AVExecutor *e, અચલ પૂર્ણાંક has_lock, અચલ પૂર્ણાંક has_cond)
{
    જો (e->thread_ગણતરી) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        માટે (પૂર્ણાંક i = 0; i < e->thread_ગણતરી; i++)
            executor_thread_join(e->threads[i].thread, ખાલી);
    }
    જો (has_cond)
        ff_cond_destroy(&e->cond);
    જો (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(અચલ AVTaskCallbacks *cb, પૂર્ણાંક thread_ગણતરી)
{
    AVExecutor *e;
    પૂર્ણાંક has_lock = 0, has_cond = 0;
    જો (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        પાછા ખાલી;

    e = av_mallocz(કદ(*e));
    જો (!e)
        પાછા ખાલી;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ગણતરી, 1), e->cb.local_context_size);
    જો (!e->local_contexts)
        જાઓ free_executor;

    e->threads = av_calloc(FFMAX(thread_ગણતરી, 1), કદ(*e->threads));
    જો (!e->threads)
        જાઓ free_executor;

    જો (!thread_ગણતરી)
        પાછા e;

    has_lock = !ff_mutex_init(&e->lock, ખાલી);
    has_cond = !ff_cond_init(&e->cond, ખાલી);

    જો (!has_lock || !has_cond)
        જાઓ free_executor;

    માટે (/* nothing */; e->thread_ગણતરી < thread_ગણતરી; e->thread_ગણતરી++) {
        ThreadInfo *ti = e->threads + e->thread_ગણતરી;
        ti->e = e;
        જો (executor_thread_create(&ti->thread, ખાલી, executor_worker_task, ti))
            જાઓ free_executor;
    }
    પાછા e;

free_executor:
    executor_free(e, has_lock, has_cond);
    પાછા ખાલી;
}

શૂન્ય av_executor_free(AVExecutor **executor)
{
    પૂર્ણાંક thread_ગણતરી;

    જો (!executor || !*executor)
        પાછા;
    thread_ગણતરી = (*executor)->thread_ગણતરી;
    executor_free(*executor, thread_ગણતરી, thread_ગણતરી);
    *executor = ખાલી;
}

શૂન્ય av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    જો (e->thread_ગણતરી)
        ff_mutex_lock(&e->lock);
    જો (t) {
        માટે (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    જો (e->thread_ગણતરી) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    જો (!e->thread_ગણતરી || !HAVE_THREADS) {
        જો (e->recursive)
            પાછા;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        જ્યારે (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
