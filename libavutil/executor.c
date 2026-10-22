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

#यदि !HAVE_तन्तवः

#परिभाषय ExecutorThread  वर्ण

#परिभाषय executor_thread_create(t, a, s, ar)      0
#परिभाषय executor_thread_join(t, r)               कुरु {} यावत्(0)

#अन्यथा

#परिभाषय ExecutorThread  pthread_t

#परिभाषय executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#परिभाषय executor_thread_join(t, r)               pthread_join(t, r)

#यदि_अन्तः //!HAVE_THREADS

प्रकारनिर्देश संरचना ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

संरचना AVExecutor {
    AVTaskCallbacks cb;
    पूर्णाङ्क thread_गणनम्;
    bool recursive;

    ThreadInfo *तन्तवः;
    uint8_t *local_contexts;

    AVMutex तालकम्;
    AVCond cond;
    पूर्णाङ्क die;

    AVTask *tasks;
};

स्थिर AVTask* remove_task(AVTask **पूर्व, AVTask *t)
{
    *पूर्व  = t->अग्र;
    t->अग्र = रिक्त;
    प्रत्यागम t;
}

स्थिर शून्य सङ्कलय_task(AVTask **पूर्व, AVTask *t)
{
    t->अग्र = *पूर्व;
    *पूर्व   = t;
}

स्थिर पूर्णाङ्क सततम्_one_task(AVExecutor *e, शून्य *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **पूर्व;

    प्रति (पूर्व = &e->tasks; *पूर्व && !cb->ready(*पूर्व, cb->user_दत्त); पूर्व = &(*पूर्व)->अग्र)
        /* nothing */;
    यदि (*पूर्व) {
        AVTask *t = remove_task(पूर्व, *पूर्व);
        यदि (e->thread_गणनम् > 0)
            ff_mutex_unlock(&e->तालकम्);
        cb->सततम्(t, lc, cb->user_दत्त);
        यदि (e->thread_गणनम् > 0)
            ff_mutex_तालकम्(&e->तालकम्);
        प्रत्यागम 1;
    }
    प्रत्यागम 0;
}

#यदि HAVE_तन्तवः
स्थिर शून्य *executor_कार्यकर्ता_task(शून्य *दत्त)
{
    ThreadInfo *ti = (ThreadInfo*)दत्त;
    AVExecutor *e  = ti->e;
    शून्य *lc       = e->local_contexts + (ti - e->तन्तवः) * e->cb.local_context_आकार;

    ff_mutex_तालकम्(&e->तालकम्);
    यावत् (1) {
        यदि (e->die) भङ्ग;

        यदि (!सततम्_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->तालकम्);
        }
    }
    ff_mutex_unlock(&e->तालकम्);
    प्रत्यागम रिक्त;
}
#यदि_अन्तः

स्थिर शून्य executor_free(AVExecutor *e, ध्रुव पूर्णाङ्क has_तालकम्, ध्रुव पूर्णाङ्क has_cond)
{
    यदि (e->thread_गणनम्) {
        //signal die
        ff_mutex_तालकम्(&e->तालकम्);
        e->die = 1;
        ff_cond_प्रसारणम्(&e->cond);
        ff_mutex_unlock(&e->तालकम्);

        प्रति (पूर्णाङ्क i = 0; i < e->thread_गणनम्; i++)
            executor_thread_join(e->तन्तवः[i].thread, रिक्त);
    }
    यदि (has_cond)
        ff_cond_destroy(&e->cond);
    यदि (has_तालकम्)
        ff_mutex_destroy(&e->तालकम्);

    av_free(e->तन्तवः);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ध्रुव AVTaskCallbacks *cb, पूर्णाङ्क thread_गणनम्)
{
    AVExecutor *e;
    पूर्णाङ्क has_तालकम् = 0, has_cond = 0;
    यदि (!cb || !cb->user_दत्त || !cb->ready || !cb->सततम् || !cb->प्राथमिकता_higher)
        प्रत्यागम रिक्त;

    e = av_mallocz(परिमाण(*e));
    यदि (!e)
        प्रत्यागम रिक्त;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_गणनम्, 1), e->cb.local_context_आकार);
    यदि (!e->local_contexts)
        गच्छ free_executor;

    e->तन्तवः = av_calloc(FFMAX(thread_गणनम्, 1), परिमाण(*e->तन्तवः));
    यदि (!e->तन्तवः)
        गच्छ free_executor;

    यदि (!thread_गणनम्)
        प्रत्यागम e;

    has_तालकम् = !ff_mutex_init(&e->तालकम्, रिक्त);
    has_cond = !ff_cond_init(&e->cond, रिक्त);

    यदि (!has_तालकम् || !has_cond)
        गच्छ free_executor;

    प्रति (/* nothing */; e->thread_गणनम् < thread_गणनम्; e->thread_गणनम्++) {
        ThreadInfo *ti = e->तन्तवः + e->thread_गणनम्;
        ti->e = e;
        यदि (executor_thread_create(&ti->thread, रिक्त, executor_कार्यकर्ता_task, ti))
            गच्छ free_executor;
    }
    प्रत्यागम e;

free_executor:
    executor_free(e, has_तालकम्, has_cond);
    प्रत्यागम रिक्त;
}

शून्य av_executor_free(AVExecutor **executor)
{
    पूर्णाङ्क thread_गणनम्;

    यदि (!executor || !*executor)
        प्रत्यागम;
    thread_गणनम् = (*executor)->thread_गणनम्;
    executor_free(*executor, thread_गणनम्, thread_गणनम्);
    *executor = रिक्त;
}

शून्य av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **पूर्व;

    यदि (e->thread_गणनम्)
        ff_mutex_तालकम्(&e->तालकम्);
    यदि (t) {
        प्रति (पूर्व = &e->tasks; *पूर्व && cb->प्राथमिकता_higher(*पूर्व, t); पूर्व = &(*पूर्व)->अग्र)
            /* nothing */;
        सङ्कलय_task(पूर्व, t);
    }
    यदि (e->thread_गणनम्) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->तालकम्);
    }

    यदि (!e->thread_गणनम् || !HAVE_तन्तवः) {
        यदि (e->recursive)
            प्रत्यागम;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        यावत् (सततम्_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
