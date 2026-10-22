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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <stdbool.h>

#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "thread.h"

#அந்தர்பாவ "executor.h"

#எனில் !HAVE_THREADS

#define ExecutorThread  எழுத்து

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               செய் {} போது(0)

#இல்லையெனில்

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

வகைவரை கட்டமைப்பு ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

கட்டமைப்பு AVExecutor {
    AVTaskCallbacks cb;
    முழு thread_மொத்தம்;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    முழு die;

    AVTask *tasks;
};

நிலையான AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = வெற்று;
    திரும்பு t;
}

நிலையான வெறுமை add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

நிலையான முழு run_one_task(AVExecutor *e, வெறுமை *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    க்கு (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    எனில் (*prev) {
        AVTask *t = remove_task(prev, *prev);
        எனில் (e->thread_மொத்தம் > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        எனில் (e->thread_மொத்தம் > 0)
            ff_mutex_lock(&e->lock);
        திரும்பு 1;
    }
    திரும்பு 0;
}

#எனில் HAVE_THREADS
நிலையான வெறுமை *executor_worker_task(வெறுமை *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    வெறுமை *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    போது (1) {
        எனில் (e->die) நிறுத்து;

        எனில் (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    திரும்பு வெற்று;
}
#endif

நிலையான வெறுமை executor_free(AVExecutor *e, மாறிலி முழு has_lock, மாறிலி முழு has_cond)
{
    எனில் (e->thread_மொத்தம்) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        க்கு (முழு i = 0; i < e->thread_மொத்தம்; i++)
            executor_thread_join(e->threads[i].thread, வெற்று);
    }
    எனில் (has_cond)
        ff_cond_destroy(&e->cond);
    எனில் (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(மாறிலி AVTaskCallbacks *cb, முழு thread_மொத்தம்)
{
    AVExecutor *e;
    முழு has_lock = 0, has_cond = 0;
    எனில் (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        திரும்பு வெற்று;

    e = av_mallocz(அளவு(*e));
    எனில் (!e)
        திரும்பு வெற்று;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_மொத்தம், 1), e->cb.local_context_size);
    எனில் (!e->local_contexts)
        செல் free_executor;

    e->threads = av_calloc(FFMAX(thread_மொத்தம், 1), அளவு(*e->threads));
    எனில் (!e->threads)
        செல் free_executor;

    எனில் (!thread_மொத்தம்)
        திரும்பு e;

    has_lock = !ff_mutex_init(&e->lock, வெற்று);
    has_cond = !ff_cond_init(&e->cond, வெற்று);

    எனில் (!has_lock || !has_cond)
        செல் free_executor;

    க்கு (/* nothing */; e->thread_மொத்தம் < thread_மொத்தம்; e->thread_மொத்தம்++) {
        ThreadInfo *ti = e->threads + e->thread_மொத்தம்;
        ti->e = e;
        எனில் (executor_thread_create(&ti->thread, வெற்று, executor_worker_task, ti))
            செல் free_executor;
    }
    திரும்பு e;

free_executor:
    executor_free(e, has_lock, has_cond);
    திரும்பு வெற்று;
}

வெறுமை av_executor_free(AVExecutor **executor)
{
    முழு thread_மொத்தம்;

    எனில் (!executor || !*executor)
        திரும்பு;
    thread_மொத்தம் = (*executor)->thread_மொத்தம்;
    executor_free(*executor, thread_மொத்தம், thread_மொத்தம்);
    *executor = வெற்று;
}

வெறுமை av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    எனில் (e->thread_மொத்தம்)
        ff_mutex_lock(&e->lock);
    எனில் (t) {
        க்கு (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    எனில் (e->thread_மொத்தம்) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    எனில் (!e->thread_மொத்தம் || !HAVE_THREADS) {
        எனில் (e->recursive)
            திரும்பு;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        போது (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
