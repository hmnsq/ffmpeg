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

#ضمن "config.h"

#אם HAVE_PRCTL
#ضمن <sys/prctl.h>
#وإلاإذا (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#ضمن <pthread_np.h>
#endif

#ضمن "error.h"

#אם HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#אם HAVE_PTHREADS
#ضمن <pthread.h>

#אם defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ضمن <stdlib.h>

#ضمن "log.h"
#ضمن "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) עשה {                            \
    حرف errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(عدم, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} כלעוד (0)

#define ASSERT_PTHREAD_NORET(func, ...) עשה {                            \
    صحيح ret = func(__VA_ARGS__);                                        \
    אם (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} כלעוד (0)

#define ASSERT_PTHREAD(func, ...) עשה {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    החזר 0;                                                           \
} כלעוד (0)

ساكن مضمن صحيح strict_pthread_join(pthread_t thread, فراغ **value_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, value_ptr);
}

ساكن مضمن صحيح strict_pthread_mutex_init(pthread_mutex_t *mutex, ثابت pthread_mutexattr_t *attr)
{
    אם (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } אחרת {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    החזר 0;
}

ساكن مضمن صحيح strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ساكن مضمن صحيح strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

ساكن مضمن صحيح strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ساكن مضمن صحيح strict_pthread_cond_init(pthread_cond_t *cond, ثابت pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ساكن مضمن صحيح strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ساكن مضمن صحيح strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ساكن مضمن صحيح strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

ساكن مضمن صحيح strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ساكن مضمن صحيح strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ثابت بنية timespec *abstime)
{
    صحيح ret = pthread_cond_timedwait(cond, mutex, abstime);
    אם (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    החזר ret;
}

ساكن مضمن صحيح strict_pthread_once(pthread_once_t *once_control, فراغ (*init_routine)(فراغ))
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

#وإلاإذا HAVE_OS2THREADS
#ضمن "compat/os2threads.h"
#אחרת
#ضمن "compat/w32pthreads.h"
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

#אחרת

#define AVMutex حرف
#define AV_MUTEX_INITIALIZER 0

ساكن مضمن صحيح ff_mutex_init(AVMutex *mutex, ثابت فراغ *attr){ החזר 0; }
ساكن مضمن صحيح ff_mutex_lock(AVMutex *mutex){ החזר 0; }
ساكن مضمن صحيح ff_mutex_unlock(AVMutex *mutex){ החזר 0; }
ساكن مضمن صحيح ff_mutex_destroy(AVMutex *mutex){ החזר 0; }

#define AVCond حرف

ساكن مضمن صحيح ff_cond_init(AVCond *cond, ثابت فراغ *attr){ החזר 0; }
ساكن مضمن صحيح ff_cond_destroy(AVCond *cond){ החזר 0; }
ساكن مضمن صحيح ff_cond_signal(AVCond *cond){ החזר 0; }
ساكن مضمن صحيح ff_cond_broadcast(AVCond *cond){ החזר 0; }
ساكن مضمن صحيح ff_cond_wait(AVCond *cond, AVMutex *mutex){ החזר 0; }
ساكن مضمن صحيح ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ثابت فراغ *abstime){ החזר 0; }

#define AVOnce حرف
#define AV_ONCE_INIT 0

ساكن مضمن صحيح ff_thread_once(حرف *control, فراغ (*routine)(فراغ))
{
    אם (!*control) {
        routine();
        *control = 1;
    }
    החזר 0;
}

#endif

ساكن مضمن صحيح ff_thread_setname(ثابت حرف *name)
{
    صحيح ret = 0;

#אם HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#وإلاإذا HAVE_PTHREAD_SETNAME_NP
#אם defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#وإلاإذا defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#אחרת
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#وإلاإذا HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#وإلاإذا HAVE_W32THREADS
    ret = win32_thread_setname(name);
#אחרת
    ret = AVERROR(ENOSYS);
#endif

    החזר ret;
}

#endif /* AVUTIL_THREAD_H */
