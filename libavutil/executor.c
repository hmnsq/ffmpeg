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

#ಆದರೆ !HAVE_ಎಳೆಗಳು

#ವ್ಯಾಖ್ಯಾನಿಸು ExecutorThread  ಅಕ್ಷರ

#ವ್ಯಾಖ್ಯಾನಿಸು executor_thread_create(t, a, s, ar)      0
#ವ್ಯಾಖ್ಯಾನಿಸು executor_thread_join(t, r)               ಮಾಡು {} ಆಗ(0)

#ಇಲ್ಲದಿದ್ದರೆ

#ವ್ಯಾಖ್ಯಾನಿಸು ExecutorThread  pthread_t

#ವ್ಯಾಖ್ಯಾನಿಸು executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#ವ್ಯಾಖ್ಯಾನಿಸು executor_thread_join(t, r)               pthread_join(t, r)

#ಆದರೆ_ಅಂತ್ಯ //!HAVE_THREADS

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ರಚನೆ AVExecutor {
    AVTaskCallbacks cb;
    ಪೂರ್ಣಾಂಕ thread_ಎಣಿಕೆ;
    bool recursive;

    ThreadInfo *ಎಳೆಗಳು;
    uint8_t *local_contexts;

    AVMutex ಬೀಗ_2;
    AVCond cond;
    ಪೂರ್ಣಾಂಕ die;

    AVTask *tasks;
};

ಸ್ಥಿರ AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->ಮುಂದಿನ;
    t->ಮುಂದಿನ = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ t;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_task(AVTask **prev, AVTask *t)
{
    t->ಮುಂದಿನ = *prev;
    *prev   = t;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಸತತ_one_task(AVExecutor *e, ಶೂನ್ಯ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ಗಾಗಿ (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_ದತ್ತಾಂಶ); prev = &(*prev)->ಮುಂದಿನ)
        /* nothing */;
    ಆದರೆ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ಆದರೆ (e->thread_ಎಣಿಕೆ > 0)
            ff_mutex_unlock(&e->ಬೀಗ_2);
        cb->ಸತತ(t, lc, cb->user_ದತ್ತಾಂಶ);
        ಆದರೆ (e->thread_ಎಣಿಕೆ > 0)
            ff_mutex_ಬೀಗ(&e->ಬೀಗ_2);
        ಹಿಂತಿರುಗಿ 1;
    }
    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ HAVE_ಎಳೆಗಳು
ಸ್ಥಿರ ಶೂನ್ಯ *executor_ಕೆಲಸಗಾರ_task(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    ThreadInfo *ti = (ThreadInfo*)ದತ್ತಾಂಶ;
    AVExecutor *e  = ti->e;
    ಶೂನ್ಯ *lc       = e->local_contexts + (ti - e->ಎಳೆಗಳು) * e->cb.local_context_ಗಾತ್ರ;

    ff_mutex_ಬೀಗ(&e->ಬೀಗ_2);
    ಆಗ (1) {
        ಆದರೆ (e->die) ನಿಲ್ಲಿಸು;

        ಆದರೆ (!ಸತತ_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->ಬೀಗ_2);
        }
    }
    ff_mutex_unlock(&e->ಬೀಗ_2);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ executor_free(AVExecutor *e, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ has_ಬೀಗ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ has_cond)
{
    ಆದರೆ (e->thread_ಎಣಿಕೆ) {
        //signal die
        ff_mutex_ಬೀಗ(&e->ಬೀಗ_2);
        e->die = 1;
        ff_cond_ಪ್ರಸಾರ(&e->cond);
        ff_mutex_unlock(&e->ಬೀಗ_2);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->thread_ಎಣಿಕೆ; i++)
            executor_thread_join(e->ಎಳೆಗಳು[i].thread, ಖಾಲಿ);
    }
    ಆದರೆ (has_cond)
        ff_cond_destroy(&e->cond);
    ಆದರೆ (has_ಬೀಗ)
        ff_mutex_destroy(&e->ಬೀಗ_2);

    av_free(e->ಎಳೆಗಳು);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ಸ್ಥಿರಾಂಕ AVTaskCallbacks *cb, ಪೂರ್ಣಾಂಕ thread_ಎಣಿಕೆ)
{
    AVExecutor *e;
    ಪೂರ್ಣಾಂಕ has_ಬೀಗ = 0, has_cond = 0;
    ಆದರೆ (!cb || !cb->user_ದತ್ತಾಂಶ || !cb->ready || !cb->ಸತತ || !cb->ಆದ್ಯತೆ_higher)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    e = av_mallocz(ಗಾತ್ರ(*e));
    ಆದರೆ (!e)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ಎಣಿಕೆ, 1), e->cb.local_context_ಗಾತ್ರ);
    ಆದರೆ (!e->local_contexts)
        ಹೋಗು free_executor;

    e->ಎಳೆಗಳು = av_calloc(FFMAX(thread_ಎಣಿಕೆ, 1), ಗಾತ್ರ(*e->ಎಳೆಗಳು));
    ಆದರೆ (!e->ಎಳೆಗಳು)
        ಹೋಗು free_executor;

    ಆದರೆ (!thread_ಎಣಿಕೆ)
        ಹಿಂತಿರುಗಿ e;

    has_ಬೀಗ = !ff_mutex_init(&e->ಬೀಗ_2, ಖಾಲಿ);
    has_cond = !ff_cond_init(&e->cond, ಖಾಲಿ);

    ಆದರೆ (!has_ಬೀಗ || !has_cond)
        ಹೋಗು free_executor;

    ಗಾಗಿ (/* nothing */; e->thread_ಎಣಿಕೆ < thread_ಎಣಿಕೆ; e->thread_ಎಣಿಕೆ++) {
        ThreadInfo *ti = e->ಎಳೆಗಳು + e->thread_ಎಣಿಕೆ;
        ti->e = e;
        ಆದರೆ (executor_thread_create(&ti->thread, ಖಾಲಿ, executor_ಕೆಲಸಗಾರ_task, ti))
            ಹೋಗು free_executor;
    }
    ಹಿಂತಿರುಗಿ e;

free_executor:
    executor_free(e, has_ಬೀಗ, has_cond);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ av_executor_free(AVExecutor **executor)
{
    ಪೂರ್ಣಾಂಕ thread_ಎಣಿಕೆ;

    ಆದರೆ (!executor || !*executor)
        ಹಿಂತಿರುಗಿ;
    thread_ಎಣಿಕೆ = (*executor)->thread_ಎಣಿಕೆ;
    executor_free(*executor, thread_ಎಣಿಕೆ, thread_ಎಣಿಕೆ);
    *executor = ಖಾಲಿ;
}

ಶೂನ್ಯ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ಆದರೆ (e->thread_ಎಣಿಕೆ)
        ff_mutex_ಬೀಗ(&e->ಬೀಗ_2);
    ಆದರೆ (t) {
        ಗಾಗಿ (prev = &e->tasks; *prev && cb->ಆದ್ಯತೆ_higher(*prev, t); prev = &(*prev)->ಮುಂದಿನ)
            /* nothing */;
        ಕೂಡಿಸು_task(prev, t);
    }
    ಆದರೆ (e->thread_ಎಣಿಕೆ) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->ಬೀಗ_2);
    }

    ಆದರೆ (!e->thread_ಎಣಿಕೆ || !HAVE_ಎಳೆಗಳು) {
        ಆದರೆ (e->recursive)
            ಹಿಂತಿರುಗಿ;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ಆಗ (ಸತತ_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
