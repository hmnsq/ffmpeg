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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <stdbool.h>

#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "thread.h"

#অন্তর্ভাব "executor.h"

#যদি !HAVE_THREADS

#define ExecutorThread  অক্ষর

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               করো {} যখন(0)

#অন্যথা

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

প্রকারলেখ কাঠামো ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

কাঠামো AVExecutor {
    AVTaskCallbacks cb;
    পূর্ণসংখ্যা thread_গুনতি;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    পূর্ণসংখ্যা die;

    AVTask *tasks;
};

স্থির AVTask* remove_task(AVTask **পূর্ব, AVTask *t)
{
    *পূর্ব  = t->পরবর্তী;
    t->পরবর্তী = ফাঁকা;
    ফেরত t;
}

স্থির শূন্য add_task(AVTask **পূর্ব, AVTask *t)
{
    t->পরবর্তী = *পূর্ব;
    *পূর্ব   = t;
}

স্থির পূর্ণসংখ্যা run_one_task(AVExecutor *e, শূন্য *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **পূর্ব;

    জন্য (পূর্ব = &e->tasks; *পূর্ব && !cb->ready(*পূর্ব, cb->user_তথ্য); পূর্ব = &(*পূর্ব)->পরবর্তী)
        /* nothing */;
    যদি (*পূর্ব) {
        AVTask *t = remove_task(পূর্ব, *পূর্ব);
        যদি (e->thread_গুনতি > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_তথ্য);
        যদি (e->thread_গুনতি > 0)
            ff_mutex_lock(&e->lock);
        ফেরত 1;
    }
    ফেরত 0;
}

#যদি HAVE_THREADS
স্থির শূন্য *executor_worker_task(শূন্য *তথ্য)
{
    ThreadInfo *ti = (ThreadInfo*)তথ্য;
    AVExecutor *e  = ti->e;
    শূন্য *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_আকার;

    ff_mutex_lock(&e->lock);
    যখন (1) {
        যদি (e->die) বিরতি;

        যদি (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ফেরত ফাঁকা;
}
#endif

স্থির শূন্য executor_free(AVExecutor *e, ধ্রুবক পূর্ণসংখ্যা has_lock, ধ্রুবক পূর্ণসংখ্যা has_cond)
{
    যদি (e->thread_গুনতি) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        জন্য (পূর্ণসংখ্যা i = 0; i < e->thread_গুনতি; i++)
            executor_thread_join(e->threads[i].thread, ফাঁকা);
    }
    যদি (has_cond)
        ff_cond_destroy(&e->cond);
    যদি (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ধ্রুবক AVTaskCallbacks *cb, পূর্ণসংখ্যা thread_গুনতি)
{
    AVExecutor *e;
    পূর্ণসংখ্যা has_lock = 0, has_cond = 0;
    যদি (!cb || !cb->user_তথ্য || !cb->ready || !cb->run || !cb->priority_higher)
        ফেরত ফাঁকা;

    e = av_mallocz(আকার(*e));
    যদি (!e)
        ফেরত ফাঁকা;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_গুনতি, 1), e->cb.local_context_আকার);
    যদি (!e->local_contexts)
        যাও free_executor;

    e->threads = av_calloc(FFMAX(thread_গুনতি, 1), আকার(*e->threads));
    যদি (!e->threads)
        যাও free_executor;

    যদি (!thread_গুনতি)
        ফেরত e;

    has_lock = !ff_mutex_init(&e->lock, ফাঁকা);
    has_cond = !ff_cond_init(&e->cond, ফাঁকা);

    যদি (!has_lock || !has_cond)
        যাও free_executor;

    জন্য (/* nothing */; e->thread_গুনতি < thread_গুনতি; e->thread_গুনতি++) {
        ThreadInfo *ti = e->threads + e->thread_গুনতি;
        ti->e = e;
        যদি (executor_thread_create(&ti->thread, ফাঁকা, executor_worker_task, ti))
            যাও free_executor;
    }
    ফেরত e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ফেরত ফাঁকা;
}

শূন্য av_executor_free(AVExecutor **executor)
{
    পূর্ণসংখ্যা thread_গুনতি;

    যদি (!executor || !*executor)
        ফেরত;
    thread_গুনতি = (*executor)->thread_গুনতি;
    executor_free(*executor, thread_গুনতি, thread_গুনতি);
    *executor = ফাঁকা;
}

শূন্য av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **পূর্ব;

    যদি (e->thread_গুনতি)
        ff_mutex_lock(&e->lock);
    যদি (t) {
        জন্য (পূর্ব = &e->tasks; *পূর্ব && cb->priority_higher(*পূর্ব, t); পূর্ব = &(*পূর্ব)->পরবর্তী)
            /* nothing */;
        add_task(পূর্ব, t);
    }
    যদি (e->thread_গুনতি) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    যদি (!e->thread_গুনতি || !HAVE_THREADS) {
        যদি (e->recursive)
            ফেরত;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        যখন (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
