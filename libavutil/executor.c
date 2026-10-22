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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "executor.h"

#ਜੇ !HAVE_ਧਾਗੇ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ExecutorThread  ਅੱਖਰ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ executor_thread_create(t, a, s, ar)      0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ executor_thread_join(t, r)               ਕਰੋ {} ਜਦੋਂ(0)

#ਨਹੀਂਤਾਂ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ExecutorThread  pthread_t

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ executor_thread_join(t, r)               pthread_join(t, r)

#ਜੇ_ਅੰਤ //!HAVE_THREADS

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ਬਣਤਰ AVExecutor {
    AVTaskCallbacks cb;
    ਪੂਰਨ thread_ਗਿਣਤੀ;
    bool recursive;

    ThreadInfo *ਧਾਗੇ;
    uint8_t *local_contexts;

    AVMutex ਤਾਲਾ;
    AVCond cond;
    ਪੂਰਨ die;

    AVTask *tasks;
};

ਸਥਿਰ AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->ਅਗਲਾ;
    t->ਅਗਲਾ = ਨਿਰਾ;
    ਵਾਪਸ t;
}

ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_task(AVTask **prev, AVTask *t)
{
    t->ਅਗਲਾ = *prev;
    *prev   = t;
}

ਸਥਿਰ ਪੂਰਨ ਲੜੀਵਾਰ_one_task(AVExecutor *e, ਖਾਲੀ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ਲਈ (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_ਅੰਕੜੇ); prev = &(*prev)->ਅਗਲਾ)
        /* nothing */;
    ਜੇ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ਜੇ (e->thread_ਗਿਣਤੀ > 0)
            ff_mutex_unlock(&e->ਤਾਲਾ);
        cb->ਲੜੀਵਾਰ(t, lc, cb->user_ਅੰਕੜੇ);
        ਜੇ (e->thread_ਗਿਣਤੀ > 0)
            ff_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);
        ਵਾਪਸ 1;
    }
    ਵਾਪਸ 0;
}

#ਜੇ HAVE_ਧਾਗੇ
ਸਥਿਰ ਖਾਲੀ *executor_ਕਾਮਾ_task(ਖਾਲੀ *ਅੰਕੜੇ)
{
    ThreadInfo *ti = (ThreadInfo*)ਅੰਕੜੇ;
    AVExecutor *e  = ti->e;
    ਖਾਲੀ *lc       = e->local_contexts + (ti - e->ਧਾਗੇ) * e->cb.local_context_ਮਾਪ;

    ff_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);
    ਜਦੋਂ (1) {
        ਜੇ (e->die) ਰੋਕੋ;

        ਜੇ (!ਲੜੀਵਾਰ_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->ਤਾਲਾ);
        }
    }
    ff_mutex_unlock(&e->ਤਾਲਾ);
    ਵਾਪਸ ਨਿਰਾ;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ executor_free(AVExecutor *e, ਅਚਲ ਪੂਰਨ has_ਤਾਲਾ, ਅਚਲ ਪੂਰਨ has_cond)
{
    ਜੇ (e->thread_ਗਿਣਤੀ) {
        //signal die
        ff_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);
        e->die = 1;
        ff_cond_ਪ੍ਰਸਾਰਣ(&e->cond);
        ff_mutex_unlock(&e->ਤਾਲਾ);

        ਲਈ (ਪੂਰਨ i = 0; i < e->thread_ਗਿਣਤੀ; i++)
            executor_thread_join(e->ਧਾਗੇ[i].thread, ਨਿਰਾ);
    }
    ਜੇ (has_cond)
        ff_cond_destroy(&e->cond);
    ਜੇ (has_ਤਾਲਾ)
        ff_mutex_destroy(&e->ਤਾਲਾ);

    av_free(e->ਧਾਗੇ);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ਅਚਲ AVTaskCallbacks *cb, ਪੂਰਨ thread_ਗਿਣਤੀ)
{
    AVExecutor *e;
    ਪੂਰਨ has_ਤਾਲਾ = 0, has_cond = 0;
    ਜੇ (!cb || !cb->user_ਅੰਕੜੇ || !cb->ready || !cb->ਲੜੀਵਾਰ || !cb->ਤਰਜੀਹ_higher)
        ਵਾਪਸ ਨਿਰਾ;

    e = av_mallocz(ਆਕਾਰ(*e));
    ਜੇ (!e)
        ਵਾਪਸ ਨਿਰਾ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ਗਿਣਤੀ, 1), e->cb.local_context_ਮਾਪ);
    ਜੇ (!e->local_contexts)
        ਜਾਓ free_executor;

    e->ਧਾਗੇ = av_calloc(FFMAX(thread_ਗਿਣਤੀ, 1), ਆਕਾਰ(*e->ਧਾਗੇ));
    ਜੇ (!e->ਧਾਗੇ)
        ਜਾਓ free_executor;

    ਜੇ (!thread_ਗਿਣਤੀ)
        ਵਾਪਸ e;

    has_ਤਾਲਾ = !ff_mutex_init(&e->ਤਾਲਾ, ਨਿਰਾ);
    has_cond = !ff_cond_init(&e->cond, ਨਿਰਾ);

    ਜੇ (!has_ਤਾਲਾ || !has_cond)
        ਜਾਓ free_executor;

    ਲਈ (/* nothing */; e->thread_ਗਿਣਤੀ < thread_ਗਿਣਤੀ; e->thread_ਗਿਣਤੀ++) {
        ThreadInfo *ti = e->ਧਾਗੇ + e->thread_ਗਿਣਤੀ;
        ti->e = e;
        ਜੇ (executor_thread_create(&ti->thread, ਨਿਰਾ, executor_ਕਾਮਾ_task, ti))
            ਜਾਓ free_executor;
    }
    ਵਾਪਸ e;

free_executor:
    executor_free(e, has_ਤਾਲਾ, has_cond);
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ av_executor_free(AVExecutor **executor)
{
    ਪੂਰਨ thread_ਗਿਣਤੀ;

    ਜੇ (!executor || !*executor)
        ਵਾਪਸ;
    thread_ਗਿਣਤੀ = (*executor)->thread_ਗਿਣਤੀ;
    executor_free(*executor, thread_ਗਿਣਤੀ, thread_ਗਿਣਤੀ);
    *executor = ਨਿਰਾ;
}

ਖਾਲੀ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ਜੇ (e->thread_ਗਿਣਤੀ)
        ff_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);
    ਜੇ (t) {
        ਲਈ (prev = &e->tasks; *prev && cb->ਤਰਜੀਹ_higher(*prev, t); prev = &(*prev)->ਅਗਲਾ)
            /* nothing */;
        ਜੋੜੋ_task(prev, t);
    }
    ਜੇ (e->thread_ਗਿਣਤੀ) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->ਤਾਲਾ);
    }

    ਜੇ (!e->thread_ਗਿਣਤੀ || !HAVE_ਧਾਗੇ) {
        ਜੇ (e->recursive)
            ਵਾਪਸ;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ਜਦੋਂ (ਲੜੀਵਾਰ_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
