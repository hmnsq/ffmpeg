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

#اگر !HAVE_دھاگے

#تعریف_کرو ExecutorThread  حرف

#تعریف_کرو executor_thread_create(t, a, s, ar)      0
#تعریف_کرو executor_thread_join(t, r)               کرو {} جب(0)

#ورنہ

#تعریف_کرو ExecutorThread  pthread_t

#تعریف_کرو executor_thread_create(t, a, s, ar)      pthread_create(t, a, s, ar)
#تعریف_کرو executor_thread_join(t, r)               pthread_join(t, r)

#اگر_ختم //!HAVE_THREADS

قسمتعریف ساخت ThreadInfo {
    AVExecutor *e;
    ExecutorThread thread;
} ThreadInfo;

ساخت AVExecutor {
    AVTaskCallbacks cb;
    صحیح thread_گنتی;
    bool recursive;

    ThreadInfo *دھاگے;
    uint8_t *local_contexts;

    AVMutex تالا_2;
    AVCond cond;
    صحیح die;

    AVTask *tasks;
};

ساکن AVTask* remove_task(AVTask **پچھلا, AVTask *t)
{
    *پچھلا  = t->اگلا;
    t->اگلا = تہی;
    واپس t;
}

ساکن خالی جوڑو_task(AVTask **پچھلا, AVTask *t)
{
    t->اگلا = *پچھلا;
    *پچھلا   = t;
}

ساکن صحیح تسلسل_one_task(AVExecutor *e, خالی *lc)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **پچھلا;

    برائے (پچھلا = &e->tasks; *پچھلا && !cb->ready(*پچھلا, cb->user_ڈیٹا); پچھلا = &(*پچھلا)->اگلا)
        /* nothing */;
    اگر (*پچھلا) {
        AVTask *t = remove_task(پچھلا, *پچھلا);
        اگر (e->thread_گنتی > 0)
            ff_mutex_unlock(&e->تالا_2);
        cb->تسلسل(t, lc, cb->user_ڈیٹا);
        اگر (e->thread_گنتی > 0)
            ff_mutex_تالا(&e->تالا_2);
        واپس 1;
    }
    واپس 0;
}

#اگر HAVE_دھاگے
ساکن خالی *executor_کارکن_task(خالی *ڈیٹا)
{
    ThreadInfo *ti = (ThreadInfo*)ڈیٹا;
    AVExecutor *e  = ti->e;
    خالی *lc       = e->local_contexts + (ti - e->دھاگے) * e->cb.local_context_سائز;

    ff_mutex_تالا(&e->تالا_2);
    جب (1) {
        اگر (e->die) توڑو;

        اگر (!تسلسل_one_task(e, lc)) {
            //no task in one loop
            ff_cond_wait(&e->cond, &e->تالا_2);
        }
    }
    ff_mutex_unlock(&e->تالا_2);
    واپس تہی;
}
#اگر_ختم

ساکن خالی executor_free(AVExecutor *e, ثابت صحیح has_تالا, ثابت صحیح has_cond)
{
    اگر (e->thread_گنتی) {
        //signal die
        ff_mutex_تالا(&e->تالا_2);
        e->die = 1;
        ff_cond_نشر(&e->cond);
        ff_mutex_unlock(&e->تالا_2);

        برائے (صحیح i = 0; i < e->thread_گنتی; i++)
            executor_thread_join(e->دھاگے[i].thread, تہی);
    }
    اگر (has_cond)
        ff_cond_destroy(&e->cond);
    اگر (has_تالا)
        ff_mutex_destroy(&e->تالا_2);

    av_free(e->دھاگے);
    av_free(e->local_contexts);

    av_free(e);
}

AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *cb, صحیح thread_گنتی)
{
    AVExecutor *e;
    صحیح has_تالا = 0, has_cond = 0;
    اگر (!cb || !cb->user_ڈیٹا || !cb->ready || !cb->تسلسل || !cb->ترجیح_higher)
        واپس تہی;

    e = av_mallocz(حجم(*e));
    اگر (!e)
        واپس تہی;
    e->cb = *cb;

    e->local_contexts = av_calloc(FFMAX(thread_گنتی, 1), e->cb.local_context_سائز);
    اگر (!e->local_contexts)
        جاؤ free_executor;

    e->دھاگے = av_calloc(FFMAX(thread_گنتی, 1), حجم(*e->دھاگے));
    اگر (!e->دھاگے)
        جاؤ free_executor;

    اگر (!thread_گنتی)
        واپس e;

    has_تالا = !ff_mutex_init(&e->تالا_2, تہی);
    has_cond = !ff_cond_init(&e->cond, تہی);

    اگر (!has_تالا || !has_cond)
        جاؤ free_executor;

    برائے (/* nothing */; e->thread_گنتی < thread_گنتی; e->thread_گنتی++) {
        ThreadInfo *ti = e->دھاگے + e->thread_گنتی;
        ti->e = e;
        اگر (executor_thread_create(&ti->thread, تہی, executor_کارکن_task, ti))
            جاؤ free_executor;
    }
    واپس e;

free_executor:
    executor_free(e, has_تالا, has_cond);
    واپس تہی;
}

خالی av_executor_free(AVExecutor **executor)
{
    صحیح thread_گنتی;

    اگر (!executor || !*executor)
        واپس;
    thread_گنتی = (*executor)->thread_گنتی;
    executor_free(*executor, thread_گنتی, thread_گنتی);
    *executor = تہی;
}

خالی av_executor_execute(AVExecutor *e, AVTask *t)
{
    AVTaskCallbacks *cb = &e->cb;
    AVTask **پچھلا;

    اگر (e->thread_گنتی)
        ff_mutex_تالا(&e->تالا_2);
    اگر (t) {
        برائے (پچھلا = &e->tasks; *پچھلا && cb->ترجیح_higher(*پچھلا, t); پچھلا = &(*پچھلا)->اگلا)
            /* nothing */;
        جوڑو_task(پچھلا, t);
    }
    اگر (e->thread_گنتی) {
        ff_cond_signal(&e->cond);
        ff_mutex_unlock(&e->تالا_2);
    }

    اگر (!e->thread_گنتی || !HAVE_دھاگے) {
        اگر (e->recursive)
            واپس;
        e->recursive = true;
        // We are running in a single-threaded environment, so we must handle all tasks ourselves
        جب (تسلسل_one_task(e, e->local_contexts))
            /* nothing */;
        e->recursive = false;
    }
}
