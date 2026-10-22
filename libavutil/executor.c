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

#అన్తర్భావ "config.h"

#అన్తర్భావ <stdbool.h>

#అన్తర్భావ "mem.h"
#అన్తర్భావ "thread.h"

#అన్తర్భావ "executor.h"

#ఒకవేళ !HAVE_దారాలు

#నిర్వచించు ExecutorThread  అక్షరం

#నిర్వచించు executor_thread_create(t, a, s, ar)      0
#నిర్వచించు executor_thread_join(t, r)               చేయి {} అయితే(0)

#లేకపోతే

#నిర్వచించు ExecutorThread  pthread_t

#నిర్వచించు executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#నిర్వచించు executor_thread_join(t, r)               pthread_join(t, r)

#అయితే_ముగింపు //!HAVE_THREADS

రకనిర్వచనం నిర్మాణం ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

నిర్మాణం AVExecutor {
    AVTaskCallbacks cb;
    పూర్ణాంకం thread_లెక్క;
    bool recursive;

    ThreadInfo *దారాలు;
    uint8_t *local_contexts;

    AVMutex తాళం_2;
    AVCond cond;
    పూర్ణాంకం die;

    AVTask *tasks;
};

స్థిర AVTask* remove_task(AVTask **prev, AVTask *t)
{
    *prev  = t->తదుపరి;
    t->తదుపరి = ఖాళీ;
    తిరిగి t;
}

స్థిర శూన్య కూడు_task(AVTask **prev, AVTask *t)
{
    t->తదుపరి = *prev;
    *prev   = t;
}

స్థిర పూర్ణాంకం నిరంతరం_one_task(AVExecutor *e, శూన్య *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    కొరకు (prev = &e->tasks; *prev && !cb->ready(*prev, cb->user_దత్తాంశం); prev = &(*prev)->తదుపరి)
        /* nothing */;
    ఒకవేళ (*prev) {
        AVTask *t = remove_task(prev, *prev);
        ఒకవేళ (e->thread_లెక్క > 0)
            ff_mutex_unlock(&e->తాళం_2);
        cb->నిరంతరం(t, lc, cb->user_దత్తాంశం);
        ఒకవేళ (e->thread_లెక్క > 0)
            ff_mutex_తాళం(&e->తాళం_2);
        తిరిగి 1;
    }
    తిరిగి 0;
}

#ఒకవేళ HAVE_దారాలు
స్థిర శూన్య *executor_కార్మికుడు_task(శూన్య *దత్తాంశం)
{
    ThreadInfo *ti = (ThreadInfo*)దత్తాంశం;
    AVExecutor *e  = ti->e;
    శూన్య *lc       = e->local_contexts + (ti - e->దారాలు) * e->cb.local_context_కొలత;

    ff_mutex_తాళం(&e->తాళం_2);
    అయితే (1) {
        ఒకవేళ (e->die) ఆపు;

        ఒకవేళ (!నిరంతరం_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->తాళం_2);
        }
    }
    ff_mutex_unlock(&e->తాళం_2);
    తిరిగి ఖాళీ;
}
#అయితే_ముగింపు

స్థిర శూన్య executor_free(AVExecutor *e, స్థిరరాశి పూర్ణాంకం has_తాళం, స్థిరరాశి పూర్ణాంకం has_cond)
{
    ఒకవేళ (e->thread_లెక్క) {
        //signal die
        ff_mutex_తాళం(&e->తాళం_2);
        e->die = 1;
        ff_cond_ప్రసారం(&e->cond);
        ff_mutex_unlock(&e->తాళం_2);

        కొరకు (పూర్ణాంకం i = 0; i < e->thread_లెక్క; i++)
            executor_thread_join(e->దారాలు[i].thread, ఖాళీ);
    }
    ఒకవేళ (has_cond)
        ff_cond_destroy(&e->cond);
    ఒకవేళ (has_తాళం)
        ff_mutex_destroy(&e->తాళం_2);

    av_free(e->దారాలు);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(స్థిరరాశి AVTaskCallbacks *cb, పూర్ణాంకం thread_లెక్క)
{
    AVExecutor *e;
    పూర్ణాంకం has_తాళం = 0, has_cond = 0;
    ఒకవేళ (!cb || !cb->user_దత్తాంశం || !cb->ready || !cb->నిరంతరం || !cb->ప్రాధాన్యత_higher)
        తిరిగి ఖాళీ;

    e = av_mallocz(పరిమాణం(*e));
    ఒకవేళ (!e)
        తిరిగి ఖాళీ;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_లెక్క, 1), e->cb.local_context_కొలత);
    ఒకవేళ (!e->local_contexts)
        వెళ్ళు free_executor;

    e->దారాలు = av_calloc(FFMAX(thread_లెక్క, 1), పరిమాణం(*e->దారాలు));
    ఒకవేళ (!e->దారాలు)
        వెళ్ళు free_executor;

    ఒకవేళ (!thread_లెక్క)
        తిరిగి e;

    has_తాళం = !ff_mutex_init(&e->తాళం_2, ఖాళీ);
    has_cond = !ff_cond_init(&e->cond, ఖాళీ);

    ఒకవేళ (!has_తాళం || !has_cond)
        వెళ్ళు free_executor;

    కొరకు (/* nothing */; e->thread_లెక్క < thread_లెక్క; e->thread_లెక్క++) {
        ThreadInfo *ti = e->దారాలు + e->thread_లెక్క;
        ti->e = e;
        ఒకవేళ (executor_thread_create(&ti->thread, ఖాళీ, executor_కార్మికుడు_task, ti))
            వెళ్ళు free_executor;
    }
    తిరిగి e;

free_executor:
    executor_free(e, has_తాళం, has_cond);
    తిరిగి ఖాళీ;
}

శూన్య av_executor_free(AVExecutor **executor)
{
    పూర్ణాంకం thread_లెక్క;

    ఒకవేళ (!executor || !*executor)
        తిరిగి;
    thread_లెక్క = (*executor)->thread_లెక్క;
    executor_free(*executor, thread_లెక్క, thread_లెక్క);
    *executor = ఖాళీ;
}

శూన్య av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **prev;

    ఒకవేళ (e->thread_లెక్క)
        ff_mutex_తాళం(&e->తాళం_2);
    ఒకవేళ (t) {
        కొరకు (prev = &e->tasks; *prev && cb->ప్రాధాన్యత_higher(*prev, t); prev = &(*prev)->తదుపరి)
            /* nothing */;
        కూడు_task(prev, t);
    }
    ఒకవేళ (e->thread_లెక్క) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->తాళం_2);
    }

    ఒకవేళ (!e->thread_లెక్క || !HAVE_దారాలు) {
        ఒకవేళ (e->recursive)
            తిరిగి;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        అయితే (నిరంతరం_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
