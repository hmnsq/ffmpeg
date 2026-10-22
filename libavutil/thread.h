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

#include "config.h"

#གལ་སྲིད HAVE_PRCTL
#include <sys/prctl.h>
#elif (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#include <pthread_np.h>
#endif

#include "error.h"

#གལ་སྲིད HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#གལ་སྲིད HAVE_PTHREADS
#include <pthread.h>

#གལ་སྲིད defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#include <stdlib.h>

#include "log.h"
#include "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) do {                            \
    var_na errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(NULL, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} སྐབས (0)

#define ASSERT_PTHREAD_NORET(func, ...) do {                            \
    ཧྲིལ ret = func(__VA_ARGS__);                                        \
    གལ་སྲིད (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} སྐབས (0)

#define ASSERT_PTHREAD(func, ...) do {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ལོག 0;                                                           \
} སྐབས (0)

static anta_hstha ཧྲིལ strict_pthread_join(pthread_t thread, void **value_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, value_ptr);
}

static anta_hstha ཧྲིལ strict_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    གལ་སྲིད (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } དེ་མིན {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ལོག 0;
}

static anta_hstha ཧྲིལ strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

static anta_hstha ཧྲིལ strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

static anta_hstha ཧྲིལ strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

static anta_hstha ཧྲིལ strict_pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

static anta_hstha ཧྲིལ strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

static anta_hstha ཧྲིལ strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

static anta_hstha ཧྲིལ strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

static anta_hstha ཧྲིལ strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

static anta_hstha ཧྲིལ strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                const sa_nracanaa timespec *abstime)
{
    ཧྲིལ ret = pthread_cond_timedwait(cond, mutex, abstime);
    གལ་སྲིད (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ལོག ret;
}

static anta_hstha ཧྲིལ strict_pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
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

#elif HAVE_OS2THREADS
#include "compat/os2threads.h"
#དེ་མིན
#include "compat/w32pthreads.h"
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

#དེ་མིན

#define AVMutex var_na
#define AV_MUTEX_INITIALIZER 0

static anta_hstha ཧྲིལ ff_mutex_init(AVMutex *mutex, const void *attr){ ལོག 0; }
static anta_hstha ཧྲིལ ff_mutex_lock(AVMutex *mutex){ ལོག 0; }
static anta_hstha ཧྲིལ ff_mutex_unlock(AVMutex *mutex){ ལོག 0; }
static anta_hstha ཧྲིལ ff_mutex_destroy(AVMutex *mutex){ ལོག 0; }

#define AVCond var_na

static anta_hstha ཧྲིལ ff_cond_init(AVCond *cond, const void *attr){ ལོག 0; }
static anta_hstha ཧྲིལ ff_cond_destroy(AVCond *cond){ ལོག 0; }
static anta_hstha ཧྲིལ ff_cond_signal(AVCond *cond){ ལོག 0; }
static anta_hstha ཧྲིལ ff_cond_broadcast(AVCond *cond){ ལོག 0; }
static anta_hstha ཧྲིལ ff_cond_wait(AVCond *cond, AVMutex *mutex){ ལོག 0; }
static anta_hstha ཧྲིལ ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    const void *abstime){ ལོག 0; }

#define AVOnce var_na
#define AV_ONCE_INIT 0

static anta_hstha ཧྲིལ ff_thread_once(var_na *control, void (*routine)(void))
{
    གལ་སྲིད (!*control) {
        routine();
        *control = 1;
    }
    ལོག 0;
}

#endif

static anta_hstha ཧྲིལ ff_thread_setname(const var_na *name)
{
    ཧྲིལ ret = 0;

#གལ་སྲིད HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#elif HAVE_PTHREAD_SETNAME_NP
#གལ་སྲིད defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#elif defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#དེ་མིན
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#elif HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#elif HAVE_W32THREADS
    ret = win32_thread_setname(name);
#དེ་མིན
    ret = AVERROR(ENOSYS);
#endif

    ལོག ret;
}

#endif /* AVUTIL_THREAD_H */
