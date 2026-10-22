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

#अन्तर्भाव "config.h"

#अन्तर्भाव <stdbool.h>

#अन्तर्भाव "mem.h"
#अन्तर्भाव "thread.h"

#अन्तर्भाव "executor.h"

#जर !HAVE_THREADS

#define ExecutorThread  अक्षर

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               करा {} पर्यंत(0)

#अन्यथा

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

प्रकारव्याख्या संरचना ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

संरचना AVExecutor {
    AVTaskCallbacks cb;
    पूर्णांक thread_मोजणी;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    पूर्णांक die;

    AVTask *tasks;
};

स्थिर AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = रिक्त;
    परत t;
}

स्थिर शून्य add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

स्थिर पूर्णांक run_one_task(AVExecutor *e, शून्य *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    साठी (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    जर (*prev) {
        AVTask *t = remove_task(prev, *prev);
        जर (e->thread_मोजणी > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        जर (e->thread_मोजणी > 0)
            ff_mutex_lock(&e->lock);
        परत 1;
    }
    परत 0;
}

#जर HAVE_THREADS
स्थिर शून्य *executor_worker_task(शून्य *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    शून्य *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    पर्यंत (1) {
        जर (e->die) थांबा;

        जर (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    परत रिक्त;
}
#endif

स्थिर शून्य executor_free(AVExecutor *e, स्थिरांक पूर्णांक has_lock, स्थिरांक पूर्णांक has_cond)
{
    जर (e->thread_मोजणी) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        साठी (पूर्णांक i = 0; i < e->thread_मोजणी; i++)
            executor_thread_join(e->threads[i].thread, रिक्त);
    }
    जर (has_cond)
        ff_cond_destroy(&e->cond);
    जर (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(स्थिरांक AVTaskCallbacks *cb, पूर्णांक thread_मोजणी)
{
    AVExecutor *e;
    पूर्णांक has_lock = 0, has_cond = 0;
    जर (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        परत रिक्त;

    e = av_mallocz(आकार(*e));
    जर (!e)
        परत रिक्त;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_मोजणी, 1), e->cb.local_context_size);
    जर (!e->local_contexts)
        जा free_executor;

    e->threads = av_calloc(FFMAX(thread_मोजणी, 1), आकार(*e->threads));
    जर (!e->threads)
        जा free_executor;

    जर (!thread_मोजणी)
        परत e;

    has_lock = !ff_mutex_init(&e->lock, रिक्त);
    has_cond = !ff_cond_init(&e->cond, रिक्त);

    जर (!has_lock || !has_cond)
        जा free_executor;

    साठी (/* nothing */; e->thread_मोजणी < thread_मोजणी; e->thread_मोजणी++) {
        ThreadInfo *ti = e->threads + e->thread_मोजणी;
        ti->e = e;
        जर (executor_thread_create(&ti->thread, रिक्त, executor_worker_task, ti))
            जा free_executor;
    }
    परत e;

free_executor:
    executor_free(e, has_lock, has_cond);
    परत रिक्त;
}

शून्य av_executor_free(AVExecutor **executor)
{
    पूर्णांक thread_मोजणी;

    जर (!executor || !*executor)
        परत;
    thread_मोजणी = (*executor)->thread_मोजणी;
    executor_free(*executor, thread_मोजणी, thread_मोजणी);
    *executor = रिक्त;
}

शून्य av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    जर (e->thread_मोजणी)
        ff_mutex_lock(&e->lock);
    जर (t) {
        साठी (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    जर (e->thread_मोजणी) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    जर (!e->thread_मोजणी || !HAVE_THREADS) {
        जर (e->recursive)
            परत;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        पर्यंत (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
