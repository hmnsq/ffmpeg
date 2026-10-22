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

#समावेश "config.h"

#समावेश <stdbool.h>

#समावेश "mem.h"
#समावेश "thread.h"

#समावेश "executor.h"

#अगर !HAVE_THREADS

#घोषणा ExecutorThread  अक्षर

#घोषणा executor_thread_create(t, a, s, ar)      0
#घोषणा executor_thread_join(t, r)               करो {} जबतक(0)

#अन्यथा

#घोषणा ExecutorThread  pthread_t

#घोषणा executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#घोषणा executor_thread_join(t, r)               pthread_join(t, r)

#पूर्ण_अगर //!HAVE_THREADS

प्रकार काष्ठा ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

काष्ठा AVExecutor {
    AVTaskCallbacks cb;
    पूर्णांक thread_गिनती;
    bool recursive;

    ThreadInfo *threads;
    uint8_t *local_contexts;

    AVMutex lock;
    AVCond cond;
    पूर्णांक die;

    AVTask *tasks;
};

अटल AVTask* remove_task(AVTask **पूर्व, AVTask *t)
{
    *पूर्व  = t->अग्र;
    t->अग्र = शून्य;
    वापस t;
}

अटल व्योम add_task(AVTask **पूर्व, AVTask *t)
{
    t->अग्र = *पूर्व;
    *पूर्व   = t;
}

अटल पूर्णांक run_one_task(AVExecutor *e, व्योम *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **पूर्व;

    क्रम (पूर्व = &e->tasks; *पूर्व && !cb->ready(*पूर्व, cb->user_तथ्य); पूर्व = &(*पूर्व)->अग्र)
        /* nothing */;
    अगर (*पूर्व) {
        AVTask *t = remove_task(पूर्व, *पूर्व);
        अगर (e->thread_गिनती > 0)
            ff_mutex_unlock(&e->lock);
        cb->run(t, lc, cb->user_तथ्य);
        अगर (e->thread_गिनती > 0)
            ff_mutex_lock(&e->lock);
        वापस 1;
    }
    वापस 0;
}

#अगर HAVE_THREADS
अटल व्योम *executor_worker_task(व्योम *तथ्य)
{
    ThreadInfo *ti = (ThreadInfo*)तथ्य;
    AVExecutor *e  = ti->e;
    व्योम *lc       = e->local_contexts + (ti - e->threads) * e->cb.local_context_आकार;

    ff_mutex_lock(&e->lock);
    जबतक (1) {
        अगर (e->die) अवरोध;

        अगर (!run_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->lock);
        }
    }
    ff_mutex_unlock(&e->lock);
    वापस शून्य;
}
#पूर्ण_अगर

अटल व्योम executor_free(AVExecutor *e, स्थिर पूर्णांक has_lock, स्थिर पूर्णांक has_cond)
{
    अगर (e->thread_गिनती) {
        //signal die
        ff_mutex_lock(&e->lock);
        e->die = 1;
        ff_cond_broadcast(&e->cond);
        ff_mutex_unlock(&e->lock);

        क्रम (पूर्णांक i = 0; i < e->thread_गिनती; i++)
            executor_thread_join(e->threads[i].thread, शून्य);
    }
    अगर (has_cond)
        ff_cond_destroy(&e->cond);
    अगर (has_lock)
        ff_mutex_destroy(&e->lock);

    av_free(e->threads);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(स्थिर AVTaskCallbacks *cb, पूर्णांक thread_गिनती)
{
    AVExecutor *e;
    पूर्णांक has_lock = 0, has_cond = 0;
    अगर (!cb || !cb->user_तथ्य || !cb->ready || !cb->run || !cb->priority_higher)
        वापस शून्य;

    e = av_mallocz(माप(*e));
    अगर (!e)
        वापस शून्य;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_गिनती, 1), e->cb.local_context_आकार);
    अगर (!e->local_contexts)
        जाओ free_executor;

    e->threads = av_calloc(FFMAX(thread_गिनती, 1), माप(*e->threads));
    अगर (!e->threads)
        जाओ free_executor;

    अगर (!thread_गिनती)
        वापस e;

    has_lock = !ff_mutex_init(&e->lock, शून्य);
    has_cond = !ff_cond_init(&e->cond, शून्य);

    अगर (!has_lock || !has_cond)
        जाओ free_executor;

    क्रम (/* nothing */; e->thread_गिनती < thread_गिनती; e->thread_गिनती++) {
        ThreadInfo *ti = e->threads + e->thread_गिनती;
        ti->e = e;
        अगर (executor_thread_create(&ti->thread, शून्य, executor_worker_task, ti))
            जाओ free_executor;
    }
    वापस e;

free_executor:
    executor_free(e, has_lock, has_cond);
    वापस शून्य;
}

व्योम av_executor_free(AVExecutor **executor)
{
    पूर्णांक thread_गिनती;

    अगर (!executor || !*executor)
        वापस;
    thread_गिनती = (*executor)->thread_गिनती;
    executor_free(*executor, thread_गिनती, thread_गिनती);
    *executor = शून्य;
}

व्योम av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **पूर्व;

    अगर (e->thread_गिनती)
        ff_mutex_lock(&e->lock);
    अगर (t) {
        क्रम (पूर्व = &e->tasks; *पूर्व && cb->priority_higher(*पूर्व, t); पूर्व = &(*पूर्व)->अग्र)
            /* nothing */;
        add_task(पूर्व, t);
    }
    अगर (e->thread_गिनती) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->lock);
    }

    अगर (!e->thread_गिनती || !HAVE_THREADS) {
        अगर (e->recursive)
            वापस;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        जबतक (run_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
