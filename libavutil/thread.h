/*
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

// This header should only be used to simplify code where
// threading is optional, not as a generic threading abstraction.

#ifndef AVUTIL_THREAD_H
#define AVUTIL_THREAD_H

#અન્તર્ભાવ "config.h"

#જો HAVE_PRCTL
#અન્તર્ભાવ <sys/prctl.h>
#અથવાજો (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#અન્તર્ભાવ <pthread_np.h>
#endif

#અન્તર્ભાવ "error.h"

#જો HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#જો HAVE_PTHREADS
#અન્તર્ભાવ <pthread.h>

#જો defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#અન્તર્ભાવ <stdlib.h>

#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) કરો {                            \
    અક્ષર errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(ખાલી, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} જ્યારે (0)

#define ASSERT_PTHREAD_NORET(func, ...) કરો {                            \
    પૂર્ણાંક ret = func(__VA_ARGS__);                                        \
    જો (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} જ્યારે (0)

#define ASSERT_PTHREAD(func, ...) કરો {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    પાછા 0;                                                           \
} જ્યારે (0)

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_join(pthread_t thread, શૂન્ય **કિંમત_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, કિંમત_ptr);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_mutex_init(pthread_mutex_t *mutex, અચલ pthread_mutexattr_t *attr)
{
    જો (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } નહીંતર {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    પાછા 0;
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_init(pthread_cond_t *cond, અચલ pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                અચલ સંરચના timespec *abstime)
{
    પૂર્ણાંક ret = pthread_cond_timedwait(cond, mutex, abstime);
    જો (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    પાછા ret;
}

સ્થિર અંતઃરેખ પૂર્ણાંક strict_pthread_once(pthread_once_t *once_control, શૂન્ય (*init_routine)(શૂન્ય))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#define pthread_join           strict_pthread_join
#define pthread_mutex_init     strict_pthread_mutex_init
#define pthread_mutex_destroy  strict_pthread_mutex_destroy
#define pthread_mutex_lock     strict_pthread_mutex_lock
#define pthread_mutex_unlock   strict_pthread_mutex_unlock
#define pthread_cond_init      strict_pthread_cond_init
#define pthread_cond_destroy   strict_pthread_cond_destroy
#define pthread_cond_signal    strict_pthread_cond_signal
#define pthread_cond_broadcast strict_pthread_cond_broadcast
#define pthread_cond_wait      strict_pthread_cond_wait
#define pthread_cond_timedwait strict_pthread_cond_timedwait
#define pthread_once           strict_pthread_once
#endif

#અથવાજો HAVE_OS2THREADS
#અન્તર્ભાવ "compat/os2threads.h"
#નહીંતર
#અન્તર્ભાવ "compat/w32pthreads.h"
#endif

#define AVMutex pthread_mutex_t
#define AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define ff_mutex_init    pthread_mutex_init
#define ff_mutex_lock    pthread_mutex_lock
#define ff_mutex_unlock  pthread_mutex_unlock
#define ff_mutex_destroy pthread_mutex_destroy

#define AVCond pthread_cond_t

#define ff_cond_init      pthread_cond_init
#define ff_cond_destroy   pthread_cond_destroy
#define ff_cond_signal    pthread_cond_signal
#define ff_cond_broadcast pthread_cond_broadcast
#define ff_cond_wait      pthread_cond_wait
#define ff_cond_timedwait pthread_cond_timedwait

#define AVOnce pthread_once_t
#define AV_ONCE_INIT PTHREAD_ONCE_INIT

#define ff_thread_once(control, routine) pthread_once(control, routine)

#નહીંતર

#define AVMutex અક્ષર
#define AV_MUTEX_INITIALIZER 0

સ્થિર અંતઃરેખ પૂર્ણાંક ff_mutex_init(AVMutex *mutex, અચલ શૂન્ય *attr){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_mutex_lock(AVMutex *mutex){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_mutex_unlock(AVMutex *mutex){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_mutex_destroy(AVMutex *mutex){ પાછા 0; }

#define AVCond અક્ષર

સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_init(AVCond *cond, અચલ શૂન્ય *attr){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_destroy(AVCond *cond){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_signal(AVCond *cond){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_broadcast(AVCond *cond){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_wait(AVCond *cond, AVMutex *mutex){ પાછા 0; }
સ્થિર અંતઃરેખ પૂર્ણાંક ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    અચલ શૂન્ય *abstime){ પાછા 0; }

#define AVOnce અક્ષર
#define AV_ONCE_INIT 0

સ્થિર અંતઃરેખ પૂર્ણાંક ff_thread_once(અક્ષર *control, શૂન્ય (*routine)(શૂન્ય))
{
    જો (!*control) {
        routine();
        *control = 1;
    }
    પાછા 0;
}

#endif

સ્થિર અંતઃરેખ પૂર્ણાંક ff_thread_setname(અચલ અક્ષર *name)
{
    પૂર્ણાંક ret = 0;

#જો HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#અથવાજો HAVE_PTHREAD_SETNAME_NP
#જો defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#અથવાજો defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#નહીંતર
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#અથવાજો HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#અથવાજો HAVE_W32THREADS
    ret = win32_thread_setname(name);
#નહીંતર
    ret = AVERROR(ENOSYS);
#endif

    પાછા ret;
}

#endif /* AVUTIL_THREAD_H */
