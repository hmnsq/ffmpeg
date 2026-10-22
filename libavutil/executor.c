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

#شامل "config.h"

#شامل <stdbool.h>

#شامل "mem.h"
#شامل "thread.h"

#شامل "executor.h"

#اگر !HAVE_THREADS

#define ExecutorThread  نویسه

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               انجامبده {} وقتی(0)

#وگرنه

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

تعریفنوع ساختار ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ساختار AVExecutor {
    AVTaskCallbacks cb;
    صحیح thread_شمار;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    صحیح die;

    AVTask *tasks;
};

ایستا AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = پوچ;
    بازگشت t;
}

ایستا تهی add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

ایستا صحیح run_one_task(AVExecutor *e, تهی *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    برای (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    اگر (*prev) {
        AVTask *t = remove_task(prev, *prev);
        اگر (e->thread_شمار > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        اگر (e->thread_شمار > 0)
            ff_mutex_lock(&e->lock);
        بازگشت 1;
    }
    بازگشت 0;
}

#اگر HAVE_THREADS
ایستا تهی *executor_worker_task(تهی *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    تهی *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    وقتی (1) {
        اگر (e->die) بشکن;

        اگر (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    بازگشت پوچ;
}
#endif

ایستا تهی executor_free(AVExecutor *e, ثابت صحیح has_lock, ثابت صحیح has_cond)
{
    اگر (e->thread_شمار) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        برای (صحیح i = 0; i < e->thread_شمار; i++)
            executor_thread_join(e->threads[i].thread, پوچ);
    }
    اگر (has_cond)
        ff_cond_destroy(&e->cond);
    اگر (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحیح thread_شمار)
{
    AVExecutor *e;
    صحیح has_lock = 0, has_cond = 0;
    اگر (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        بازگشت پوچ;

    e = av_mallocz(اندازه(*e));
    اگر (!e)
        بازگشت پوچ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_شمار, 1), e->cb.local_context_size);
    اگر (!e->local_contexts)
        برو free_executor;

    e->threads = av_calloc(FFMAX(thread_شمار, 1), اندازه(*e->threads));
    اگر (!e->threads)
        برو free_executor;

    اگر (!thread_شمار)
        بازگشت e;

    has_lock = !ff_mutex_init(&e->lock, پوچ);
    has_cond = !ff_cond_init(&e->cond, پوچ);

    اگر (!has_lock || !has_cond)
        برو free_executor;

    برای (/* nothing */; e->thread_شمار < thread_شمار; e->thread_شمار++) {
        ThreadInfo *ti = e->threads + e->thread_شمار;
        ti->e = e;
        اگر (executor_thread_create(&ti->thread, پوچ, executor_worker_task, ti))
            برو free_executor;
    }
    بازگشت e;

free_executor:
    executor_free(e, has_lock, has_cond);
    بازگشت پوچ;
}

تهی av_executor_free(AVExecutor **executor)
{
    صحیح thread_شمار;

    اگر (!executor || !*executor)
        بازگشت;
    thread_شمار = (*executor)->thread_شمار;
    executor_free(*executor, thread_شمار, thread_شمار);
    *executor = پوچ;
}

تهی av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    اگر (e->thread_شمار)
        ff_mutex_lock(&e->lock);
    اگر (t) {
        برای (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    اگر (e->thread_شمار) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    اگر (!e->thread_شمار || !HAVE_THREADS) {
        اگر (e->recursive)
            بازگشت;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        وقتی (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
