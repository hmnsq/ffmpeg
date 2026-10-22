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

#जइ !HAVE_THREADS

#define ExecutorThread  वर्ण

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               करेहि {} जाव(0)

#अण्णहा

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

प्रकारनिर्देश संरचना ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

संरचना AVExecutor {
    AVTaskCallbacks cb;
    पूर्णाङ्क thread_गणनम्;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    पूर्णाङ्क die;

    AVTask *tasks;
};

स्थिर AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = रिक्त;
    प्रत्यागम t;
}

स्थिर शून्य add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

स्थिर पूर्णाङ्क run_one_task(AVExecutor *e, शून्य *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    प्रति (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    जइ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        जइ (e->thread_गणनम् > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        जइ (e->thread_गणनम् > 0)
            ff_mutex_lock(&e->lock);
        प्रत्यागम 1;
    }
    प्रत्यागम 0;
}

#जइ HAVE_THREADS
स्थिर शून्य *executor_worker_task(शून्य *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    शून्य *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    जाव (1) {
        जइ (e->die) भङ्ग;

        जइ (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    प्रत्यागम रिक्त;
}
#endif

स्थिर शून्य executor_free(AVExecutor *e, ध्रुव पूर्णाङ्क has_lock, ध्रुव पूर्णाङ्क has_cond)
{
    जइ (e->thread_गणनम्) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        प्रति (पूर्णाङ्क i = 0; i < e->thread_गणनम्; i++)
            executor_thread_join(e->threads[i].thread, रिक्त);
    }
    जइ (has_cond)
        ff_cond_destroy(&e->cond);
    जइ (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ध्रुव AVTaskCallbacks *cb, पूर्णाङ्क thread_गणनम्)
{
    AVExecutor *e;
    पूर्णाङ्क has_lock = 0, has_cond = 0;
    जइ (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        प्रत्यागम रिक्त;

    e = av_mallocz(परिमाण(*e));
    जइ (!e)
        प्रत्यागम रिक्त;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_गणनम्, 1), e->cb.local_context_size);
    जइ (!e->local_contexts)
        गच्छ free_executor;

    e->threads = av_calloc(FFMAX(thread_गणनम्, 1), परिमाण(*e->threads));
    जइ (!e->threads)
        गच्छ free_executor;

    जइ (!thread_गणनम्)
        प्रत्यागम e;

    has_lock = !ff_mutex_init(&e->lock, रिक्त);
    has_cond = !ff_cond_init(&e->cond, रिक्त);

    जइ (!has_lock || !has_cond)
        गच्छ free_executor;

    प्रति (/* nothing */; e->thread_गणनम् < thread_गणनम्; e->thread_गणनम्++) {
        ThreadInfo *ti = e->threads + e->thread_गणनम्;
        ti->e = e;
        जइ (executor_thread_create(&ti->thread, रिक्त, executor_worker_task, ti))
            गच्छ free_executor;
    }
    प्रत्यागम e;

free_executor:
    executor_free(e, has_lock, has_cond);
    प्रत्यागम रिक्त;
}

शून्य av_executor_free(AVExecutor **executor)
{
    पूर्णाङ्क thread_गणनम्;

    जइ (!executor || !*executor)
        प्रत्यागम;
    thread_गणनम् = (*executor)->thread_गणनम्;
    executor_free(*executor, thread_गणनम्, thread_गणनम्);
    *executor = रिक्त;
}

शून्य av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    जइ (e->thread_गणनम्)
        ff_mutex_lock(&e->lock);
    जइ (t) {
        प्रति (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    जइ (e->thread_गणनम्) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    जइ (!e->thread_गणनम् || !HAVE_THREADS) {
        जइ (e->recursive)
            प्रत्यागम;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        जाव (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
