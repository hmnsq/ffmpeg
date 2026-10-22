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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ HAVE_PRCTL
#ಅನ್ತರ್ಭಾವ <sys/prctl.h>
#ನೋಚೇದ್ಯದಿ (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#ಅನ್ತರ್ಭಾವ <pthread_np.h>
#endif

#ಅನ್ತರ್ಭಾವ "error.h"

#ಯದಿ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#ಯದಿ HAVE_PTHREADS
#ಅನ್ತರ್ಭಾವ <pthread.h>

#ಯದಿ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) ಕುರು {                            \
    ವರ್ಣ errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(ರಿಕ್ತ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} ಯಾವತ್ (0)

#define ASSERT_PTHREAD_NORET(func, ...) ಕುರು {                            \
    ಪೂರ್ಣಾಙ್ಕ ret = func(__VA_ARGS__);                                        \
    ಯದಿ (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} ಯಾವತ್ (0)

#define ASSERT_PTHREAD(func, ...) ಕುರು {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ಪ್ರತ್ಯಾಗಮ 0;                                                           \
} ಯಾವತ್ (0)

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_join(pthread_t thread, ಶೂನ್ಯ **ಮೌಲ್ಯ_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, ಮೌಲ್ಯ_ptr);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_mutex_init(pthread_mutex_t *mutex, ಧ್ರುವ pthread_mutexattr_t *attr)
{
    ಯದಿ (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } ಅನ್ಯಥಾ {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_init(pthread_cond_t *cond, ಧ್ರುವ pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ಧ್ರುವ ಸಂರಚನಾ timespec *abstime)
{
    ಪೂರ್ಣಾಙ್ಕ ret = pthread_cond_timedwait(cond, mutex, abstime);
    ಯದಿ (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ strict_pthread_once(pthread_once_t *once_control, ಶೂನ್ಯ (*init_routine)(ಶೂನ್ಯ))
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

#ನೋಚೇದ್ಯದಿ HAVE_OS2THREADS
#ಅನ್ತರ್ಭಾವ "compat/os2threads.h"
#ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ "compat/w32pthreads.h"
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

#ಅನ್ಯಥಾ

#define AVMutex ವರ್ಣ
#define AV_MUTEX_INITIALIZER 0

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_mutex_init(AVMutex *mutex, ಧ್ರುವ ಶೂನ್ಯ *attr){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_mutex_lock(AVMutex *mutex){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_mutex_unlock(AVMutex *mutex){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_mutex_destroy(AVMutex *mutex){ ಪ್ರತ್ಯಾಗಮ 0; }

#define AVCond ವರ್ಣ

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_init(AVCond *cond, ಧ್ರುವ ಶೂನ್ಯ *attr){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_destroy(AVCond *cond){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_signal(AVCond *cond){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_broadcast(AVCond *cond){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_wait(AVCond *cond, AVMutex *mutex){ ಪ್ರತ್ಯಾಗಮ 0; }
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ಧ್ರುವ ಶೂನ್ಯ *abstime){ ಪ್ರತ್ಯಾಗಮ 0; }

#define AVOnce ವರ್ಣ
#define AV_ONCE_INIT 0

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_thread_once(ವರ್ಣ *control, ಶೂನ್ಯ (*routine)(ಶೂನ್ಯ))
{
    ಯದಿ (!*control) {
        routine();
        *control = 1;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

#endif

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_thread_setname(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

#ಯದಿ HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#ನೋಚೇದ್ಯದಿ HAVE_PTHREAD_SETNAME_NP
#ಯದಿ defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#ನೋಚೇದ್ಯದಿ defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#ಅನ್ಯಥಾ
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#ನೋಚೇದ್ಯದಿ HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#ನೋಚೇದ್ಯದಿ HAVE_W32THREADS
    ret = win32_thread_setname(name);
#ಅನ್ಯಥಾ
    ret = AVERROR(ENOSYS);
#endif

    ಪ್ರತ್ಯಾಗಮ ret;
}

#endif /* AVUTIL_THREAD_H */
