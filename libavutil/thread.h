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

#அந்தர்பாவ "config.h"

#எனில் HAVE_PRCTL
#அந்தர்பாவ <sys/prctl.h>
#அல்லதெனில் (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#அந்தர்பாவ <pthread_np.h>
#endif

#அந்தர்பாவ "error.h"

#எனில் HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#எனில் HAVE_PTHREADS
#அந்தர்பாவ <pthread.h>

#எனில் defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#அந்தர்பாவ <stdlib.h>

#அந்தர்பாவ "log.h"
#அந்தர்பாவ "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) செய் {                            \
    எழுத்து errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(வெற்று, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} போது (0)

#define ASSERT_PTHREAD_NORET(func, ...) செய் {                            \
    முழு ret = func(__VA_ARGS__);                                        \
    எனில் (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} போது (0)

#define ASSERT_PTHREAD(func, ...) செய் {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    திரும்பு 0;                                                           \
} போது (0)

நிலையான உள்வரி முழு strict_pthread_join(pthread_t thread, வெறுமை **மதிப்பு_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, மதிப்பு_ptr);
}

நிலையான உள்வரி முழு strict_pthread_mutex_init(pthread_mutex_t *mutex, மாறிலி pthread_mutexattr_t *attr)
{
    எனில் (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } இல்லையெனில் {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    திரும்பு 0;
}

நிலையான உள்வரி முழு strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

நிலையான உள்வரி முழு strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

நிலையான உள்வரி முழு strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

நிலையான உள்வரி முழு strict_pthread_cond_init(pthread_cond_t *cond, மாறிலி pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

நிலையான உள்வரி முழு strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

நிலையான உள்வரி முழு strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

நிலையான உள்வரி முழு strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

நிலையான உள்வரி முழு strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

நிலையான உள்வரி முழு strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                மாறிலி கட்டமைப்பு timespec *abstime)
{
    முழு ret = pthread_cond_timedwait(cond, mutex, abstime);
    எனில் (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    திரும்பு ret;
}

நிலையான உள்வரி முழு strict_pthread_once(pthread_once_t *once_control, வெறுமை (*init_routine)(வெறுமை))
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

#அல்லதெனில் HAVE_OS2THREADS
#அந்தர்பாவ "compat/os2threads.h"
#இல்லையெனில்
#அந்தர்பாவ "compat/w32pthreads.h"
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

#இல்லையெனில்

#define AVMutex எழுத்து
#define AV_MUTEX_INITIALIZER 0

நிலையான உள்வரி முழு ff_mutex_init(AVMutex *mutex, மாறிலி வெறுமை *attr){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_mutex_lock(AVMutex *mutex){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_mutex_unlock(AVMutex *mutex){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_mutex_destroy(AVMutex *mutex){ திரும்பு 0; }

#define AVCond எழுத்து

நிலையான உள்வரி முழு ff_cond_init(AVCond *cond, மாறிலி வெறுமை *attr){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_cond_destroy(AVCond *cond){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_cond_signal(AVCond *cond){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_cond_broadcast(AVCond *cond){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_cond_wait(AVCond *cond, AVMutex *mutex){ திரும்பு 0; }
நிலையான உள்வரி முழு ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    மாறிலி வெறுமை *abstime){ திரும்பு 0; }

#define AVOnce எழுத்து
#define AV_ONCE_INIT 0

நிலையான உள்வரி முழு ff_thread_once(எழுத்து *control, வெறுமை (*routine)(வெறுமை))
{
    எனில் (!*control) {
        routine();
        *control = 1;
    }
    திரும்பு 0;
}

#endif

நிலையான உள்வரி முழு ff_thread_setname(மாறிலி எழுத்து *name)
{
    முழு ret = 0;

#எனில் HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#அல்லதெனில் HAVE_PTHREAD_SETNAME_NP
#எனில் defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#அல்லதெனில் defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#இல்லையெனில்
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#அல்லதெனில் HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#அல்லதெனில் HAVE_W32THREADS
    ret = win32_thread_setname(name);
#இல்லையெனில்
    ret = AVERROR(ENOSYS);
#endif

    திரும்பு ret;
}

#endif /* AVUTIL_THREAD_H */
