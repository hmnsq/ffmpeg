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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <stdbool.h>

#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

#ಅನ್ತರ್ಭಾವ "executor.h"

#ಯದಿ !HAVE_THREADS

#define ExecutorThread  ವರ್ಣ

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               ಕುರು {} ಯಾವತ್(0)

#ಅನ್ಯಥಾ

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ಸಂರಚನಾ AVExecutor {
    AVTaskCallbacks cb;
    ಪೂರ್ಣಾಙ್ಕ thread_ಎಣಿಕೆ;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    ಪೂರ್ಣಾಙ್ಕ die;

    AVTask *tasks;
};

ಸ್ಥಿರ AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ t;
}

ಸ್ಥಿರ ಶೂನ್ಯ add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ run_one_task(AVExecutor *e, ಶೂನ್ಯ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ಪ್ರತಿ (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    ಯದಿ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ಯದಿ (e->thread_ಎಣಿಕೆ > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        ಯದಿ (e->thread_ಎಣಿಕೆ > 0)
            ff_mutex_lock(&e->lock);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ HAVE_THREADS
ಸ್ಥಿರ ಶೂನ್ಯ *executor_worker_task(ಶೂನ್ಯ *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    ಶೂನ್ಯ *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    ಯಾವತ್ (1) {
        ಯದಿ (e->die) ಭಙ್ಗ;

        ಯದಿ (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
#endif

ಸ್ಥಿರ ಶೂನ್ಯ executor_free(AVExecutor *e, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ has_lock, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ has_cond)
{
    ಯದಿ (e->thread_ಎಣಿಕೆ) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->thread_ಎಣಿಕೆ; i++)
            executor_thread_join(e->threads[i].thread, ರಿಕ್ತ);
    }
    ಯದಿ (has_cond)
        ff_cond_destroy(&e->cond);
    ಯದಿ (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ಧ್ರುವ AVTaskCallbacks *cb, ಪೂರ್ಣಾಙ್ಕ thread_ಎಣಿಕೆ)
{
    AVExecutor *e;
    ಪೂರ್ಣಾಙ್ಕ has_lock = 0, has_cond = 0;
    ಯದಿ (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    e = av_mallocz(ಪರಿಮಾಣ(*e));
    ಯದಿ (!e)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ಎಣಿಕೆ, 1), e->cb.local_context_size);
    ಯದಿ (!e->local_contexts)
        ಗಚ್ಛ free_executor;

    e->threads = av_calloc(FFMAX(thread_ಎಣಿಕೆ, 1), ಪರಿಮಾಣ(*e->threads));
    ಯದಿ (!e->threads)
        ಗಚ್ಛ free_executor;

    ಯದಿ (!thread_ಎಣಿಕೆ)
        ಪ್ರತ್ಯಾಗಮ e;

    has_lock = !ff_mutex_init(&e->lock, ರಿಕ್ತ);
    has_cond = !ff_cond_init(&e->cond, ರಿಕ್ತ);

    ಯದಿ (!has_lock || !has_cond)
        ಗಚ್ಛ free_executor;

    ಪ್ರತಿ (/* nothing */; e->thread_ಎಣಿಕೆ < thread_ಎಣಿಕೆ; e->thread_ಎಣಿಕೆ++) {
        ThreadInfo *ti = e->threads + e->thread_ಎಣಿಕೆ;
        ti->e = e;
        ಯದಿ (executor_thread_create(&ti->thread, ರಿಕ್ತ, executor_worker_task, ti))
            ಗಚ್ಛ free_executor;
    }
    ಪ್ರತ್ಯಾಗಮ e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ av_executor_free(AVExecutor **executor)
{
    ಪೂರ್ಣಾಙ್ಕ thread_ಎಣಿಕೆ;

    ಯದಿ (!executor || !*executor)
        ಪ್ರತ್ಯಾಗಮ;
    thread_ಎಣಿಕೆ = (*executor)->thread_ಎಣಿಕೆ;
    executor_free(*executor, thread_ಎಣಿಕೆ, thread_ಎಣಿಕೆ);
    *executor = ರಿಕ್ತ;
}

ಶೂನ್ಯ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ಯದಿ (e->thread_ಎಣಿಕೆ)
        ff_mutex_lock(&e->lock);
    ಯದಿ (t) {
        ಪ್ರತಿ (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    ಯದಿ (e->thread_ಎಣಿಕೆ) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    ಯದಿ (!e->thread_ಎಣಿಕೆ || !HAVE_THREADS) {
        ಯದಿ (e->recursive)
            ಪ್ರತ್ಯಾಗಮ;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ಯಾವತ್ (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
