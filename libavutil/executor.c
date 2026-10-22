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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <stdbool.h>

#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "thread.h"

#അന്തര്ഭാവ "executor.h"

#എങ്കിൽ !HAVE_THREADS

#define ExecutorThread  അക്ഷരം

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               ചെയ്യുക {} ആകുമ്പോൾ(0)

#അല്ലെങ്കിൽ

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

തരനിർവചനം ഘടന ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ഘടന AVExecutor {
    AVTaskCallbacks cb;
    പൂർണ്ണസംഖ്യ thread_എണ്ണം;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    പൂർണ്ണസംഖ്യ die;

    AVTask *tasks;
};

സ്ഥിതം AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = ശൂന്യ;
    തിരികെ t;
}

സ്ഥിതം ശൂന്യം add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ run_one_task(AVExecutor *e, ശൂന്യം *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    വേണ്ടി (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    എങ്കിൽ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        എങ്കിൽ (e->thread_എണ്ണം > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        എങ്കിൽ (e->thread_എണ്ണം > 0)
            ff_mutex_lock(&e->lock);
        തിരികെ 1;
    }
    തിരികെ 0;
}

#എങ്കിൽ HAVE_THREADS
സ്ഥിതം ശൂന്യം *executor_worker_task(ശൂന്യം *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    ശൂന്യം *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    ആകുമ്പോൾ (1) {
        എങ്കിൽ (e->die) നിർത്തുക;

        എങ്കിൽ (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    തിരികെ ശൂന്യ;
}
#endif

സ്ഥിതം ശൂന്യം executor_free(AVExecutor *e, സ്ഥിരം പൂർണ്ണസംഖ്യ has_lock, സ്ഥിരം പൂർണ്ണസംഖ്യ has_cond)
{
    എങ്കിൽ (e->thread_എണ്ണം) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < e->thread_എണ്ണം; i++)
            executor_thread_join(e->threads[i].thread, ശൂന്യ);
    }
    എങ്കിൽ (has_cond)
        ff_cond_destroy(&e->cond);
    എങ്കിൽ (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(സ്ഥിരം AVTaskCallbacks *cb, പൂർണ്ണസംഖ്യ thread_എണ്ണം)
{
    AVExecutor *e;
    പൂർണ്ണസംഖ്യ has_lock = 0, has_cond = 0;
    എങ്കിൽ (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        തിരികെ ശൂന്യ;

    e = av_mallocz(വലുപ്പം(*e));
    എങ്കിൽ (!e)
        തിരികെ ശൂന്യ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_എണ്ണം, 1), e->cb.local_context_size);
    എങ്കിൽ (!e->local_contexts)
        പോകുക free_executor;

    e->threads = av_calloc(FFMAX(thread_എണ്ണം, 1), വലുപ്പം(*e->threads));
    എങ്കിൽ (!e->threads)
        പോകുക free_executor;

    എങ്കിൽ (!thread_എണ്ണം)
        തിരികെ e;

    has_lock = !ff_mutex_init(&e->lock, ശൂന്യ);
    has_cond = !ff_cond_init(&e->cond, ശൂന്യ);

    എങ്കിൽ (!has_lock || !has_cond)
        പോകുക free_executor;

    വേണ്ടി (/* nothing */; e->thread_എണ്ണം < thread_എണ്ണം; e->thread_എണ്ണം++) {
        ThreadInfo *ti = e->threads + e->thread_എണ്ണം;
        ti->e = e;
        എങ്കിൽ (executor_thread_create(&ti->thread, ശൂന്യ, executor_worker_task, ti))
            പോകുക free_executor;
    }
    തിരികെ e;

free_executor:
    executor_free(e, has_lock, has_cond);
    തിരികെ ശൂന്യ;
}

ശൂന്യം av_executor_free(AVExecutor **executor)
{
    പൂർണ്ണസംഖ്യ thread_എണ്ണം;

    എങ്കിൽ (!executor || !*executor)
        തിരികെ;
    thread_എണ്ണം = (*executor)->thread_എണ്ണം;
    executor_free(*executor, thread_എണ്ണം, thread_എണ്ണം);
    *executor = ശൂന്യ;
}

ശൂന്യം av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    എങ്കിൽ (e->thread_എണ്ണം)
        ff_mutex_lock(&e->lock);
    എങ്കിൽ (t) {
        വേണ്ടി (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    എങ്കിൽ (e->thread_എണ്ണം) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    എങ്കിൽ (!e->thread_എണ്ണം || !HAVE_THREADS) {
        എങ്കിൽ (e->recursive)
            തിരികെ;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ആകുമ്പോൾ (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
