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

#شامل "config.h"

#اگر HAVE_PRCTL
#شامل <sys/prctl.h>
#وگرنهاگر (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#شامل <pthread_np.h>
#endif

#شامل "error.h"

#اگر HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#اگر HAVE_PTHREADS
#شامل <pthread.h>

#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#شامل <stdlib.h>

#شامل "log.h"
#شامل "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) انجامبده {                            \
    نویسه errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(پوچ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} وقتی (0)

#define ASSERT_PTHREAD_NORET(func, ...) انجامبده {                            \
    صحیح ret = func(__VA_ARGS__);                                        \
    اگر (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} وقتی (0)

#define ASSERT_PTHREAD(func, ...) انجامبده {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    بازگشت 0;                                                           \
} وقتی (0)

ایستا درونخطی صحیح strict_pthread_join(pthread_t thread, تهی **مقدار_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, مقدار_ptr);
}

ایستا درونخطی صحیح strict_pthread_mutex_init(pthread_mutex_t *mutex, ثابت pthread_mutexattr_t *attr)
{
    اگر (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } وگرنه {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    بازگشت 0;
}

ایستا درونخطی صحیح strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ایستا درونخطی صحیح strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

ایستا درونخطی صحیح strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ایستا درونخطی صحیح strict_pthread_cond_init(pthread_cond_t *cond, ثابت pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ایستا درونخطی صحیح strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ایستا درونخطی صحیح strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ایستا درونخطی صحیح strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

ایستا درونخطی صحیح strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ایستا درونخطی صحیح strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ثابت ساختار timespec *abstime)
{
    صحیح ret = pthread_cond_timedwait(cond, mutex, abstime);
    اگر (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    بازگشت ret;
}

ایستا درونخطی صحیح strict_pthread_once(pthread_once_t *once_control, تهی (*init_routine)(تهی))
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

#وگرنهاگر HAVE_OS2THREADS
#شامل "compat/os2threads.h"
#وگرنه
#شامل "compat/w32pthreads.h"
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

#وگرنه

#define AVMutex نویسه
#define AV_MUTEX_INITIALIZER 0

ایستا درونخطی صحیح ff_mutex_init(AVMutex *mutex, ثابت تهی *attr){ بازگشت 0; }
ایستا درونخطی صحیح ff_mutex_lock(AVMutex *mutex){ بازگشت 0; }
ایستا درونخطی صحیح ff_mutex_unlock(AVMutex *mutex){ بازگشت 0; }
ایستا درونخطی صحیح ff_mutex_destroy(AVMutex *mutex){ بازگشت 0; }

#define AVCond نویسه

ایستا درونخطی صحیح ff_cond_init(AVCond *cond, ثابت تهی *attr){ بازگشت 0; }
ایستا درونخطی صحیح ff_cond_destroy(AVCond *cond){ بازگشت 0; }
ایستا درونخطی صحیح ff_cond_signal(AVCond *cond){ بازگشت 0; }
ایستا درونخطی صحیح ff_cond_broadcast(AVCond *cond){ بازگشت 0; }
ایستا درونخطی صحیح ff_cond_wait(AVCond *cond, AVMutex *mutex){ بازگشت 0; }
ایستا درونخطی صحیح ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ثابت تهی *abstime){ بازگشت 0; }

#define AVOnce نویسه
#define AV_ONCE_INIT 0

ایستا درونخطی صحیح ff_thread_once(نویسه *control, تهی (*routine)(تهی))
{
    اگر (!*control) {
        routine();
        *control = 1;
    }
    بازگشت 0;
}

#endif

ایستا درونخطی صحیح ff_thread_setname(ثابت نویسه *name)
{
    صحیح ret = 0;

#اگر HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#وگرنهاگر HAVE_PTHREAD_SETNAME_NP
#اگر defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#وگرنهاگر defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#وگرنه
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#وگرنهاگر HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#وگرنهاگر HAVE_W32THREADS
    ret = win32_thread_setname(name);
#وگرنه
    ret = AVERROR(ENOSYS);
#endif

    بازگشت ret;
}

#endif /* AVUTIL_THREAD_H */
