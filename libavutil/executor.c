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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <stdbool.h>

#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"

#ଅନ୍ତର୍ଭାଵ "executor.h"

#ଯଦି !HAVE_THREADS

#define ExecutorThread  ଅକ୍ଷର

#define executor_thread_create(t, a, s, ar)      0
#define executor_thread_join(t, r)               କର {} ଯେତେବେଳେ(0)

#ଅନ୍ୟଥା

#define ExecutorThread  pthread_t

#define executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#define executor_thread_join(t, r)               pthread_join(t, r)

#endif //!HAVE_THREADS

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ସଂରଚନା AVExecutor {
    AVTaskCallbacks cb;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା thread_ଗଣନା;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା die;

    AVTask *tasks;
};

ସ୍ଥିର AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->next;
    t->next = ଖାଲି;
    ଫେରନ୍ତୁ t;
}

ସ୍ଥିର ଶୂନ୍ୟ add_task(AVTask **prev, AVTask *t)
{
    t->next = *prev;
    *prev   = t;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା run_one_task(AVExecutor *e, ଶୂନ୍ୟ *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ପାଇଁ (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_data); prev = &(*prev)->next)
        /* nothing */;
    ଯଦି (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ଯଦି (e->thread_ଗଣନା > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_data);
        ଯଦି (e->thread_ଗଣନା > 0)
            ff_mutex_lock(&e->lock);
        ଫେରନ୍ତୁ 1;
    }
    ଫେରନ୍ତୁ 0;
}

#ଯଦି HAVE_THREADS
ସ୍ଥିର ଶୂନ୍ୟ *executor_worker_task(ଶୂନ୍ୟ *data)
{
    ThreadInfo *ti = (ThreadInfo*)data;
    AVExecutor *e  = ti->e;
    ଶୂନ୍ୟ *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_size;

    ff_mutex_lock(&e->lock);
    ଯେତେବେଳେ (1) {
        ଯଦି (e->die) ଭାଙ୍ଗ;

        ଯଦି (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    ଫେରନ୍ତୁ ଖାଲି;
}
#endif

ସ୍ଥିର ଶୂନ୍ୟ executor_free(AVExecutor *e, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_lock, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_cond)
{
    ଯଦି (e->thread_ଗଣନା) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->thread_ଗଣନା; i++)
            executor_thread_join(e->threads[i].thread, ଖାଲି);
    }
    ଯଦି (has_cond)
        ff_cond_destroy(&e->cond);
    ଯଦି (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ଅଚଳ AVTaskCallbacks *cb, ପୂର୍ଣ୍ଣସଂଖ୍ୟା thread_ଗଣନା)
{
    AVExecutor *e;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_lock = 0, has_cond = 0;
    ଯଦି (!cb || !cb->user_data || !cb->ready || !cb->run || !cb->priority_higher)
        ଫେରନ୍ତୁ ଖାଲି;

    e = av_mallocz(ଆକାର(*e));
    ଯଦି (!e)
        ଫେରନ୍ତୁ ଖାଲି;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_ଗଣନା, 1), e->cb.local_context_size);
    ଯଦି (!e->local_contexts)
        ଯାଅ free_executor;

    e->threads = av_calloc(FFMAX(thread_ଗଣନା, 1), ଆକାର(*e->threads));
    ଯଦି (!e->threads)
        ଯାଅ free_executor;

    ଯଦି (!thread_ଗଣନା)
        ଫେରନ୍ତୁ e;

    has_lock = !ff_mutex_init(&e->lock, ଖାଲି);
    has_cond = !ff_cond_init(&e->cond, ଖାଲି);

    ଯଦି (!has_lock || !has_cond)
        ଯାଅ free_executor;

    ପାଇଁ (/* nothing */; e->thread_ଗଣନା < thread_ଗଣନା; e->thread_ଗଣନା++) {
        ThreadInfo *ti = e->threads + e->thread_ଗଣନା;
        ti->e = e;
        ଯଦି (executor_thread_create(&ti->thread, ଖାଲି, executor_worker_task, ti))
            ଯାଅ free_executor;
    }
    ଫେରନ୍ତୁ e;

free_executor:
    executor_free(e, has_lock, has_cond);
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ av_executor_free(AVExecutor **executor)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା thread_ଗଣନା;

    ଯଦି (!executor || !*executor)
        ଫେରନ୍ତୁ;
    thread_ଗଣନା = (*executor)->thread_ଗଣନା;
    executor_free(*executor, thread_ଗଣନା, thread_ଗଣନା);
    *executor = ଖାଲି;
}

ଶୂନ୍ୟ av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ଯଦି (e->thread_ଗଣନା)
        ff_mutex_lock(&e->lock);
    ଯଦି (t) {
        ପାଇଁ (prev = &e->tasks; *prev && cb->priority_higher(*prev, t); prev = &(*prev)->next)
            /* nothing */;
        add_task(prev, t);
    }
    ଯଦି (e->thread_ଗଣନା) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    ଯଦି (!e->thread_ଗଣନା || !HAVE_THREADS) {
        ଯଦି (e->recursive)
            ଫେରନ୍ତୁ;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        ଯେତେବେଳେ (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
