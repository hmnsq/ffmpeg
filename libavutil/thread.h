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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_PRCTL
#ଅନ୍ତର୍ଭାଵ <sys/prctl.h>
#ନଚେତଯଦି (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#ଅନ୍ତର୍ଭାଵ <pthread_np.h>
#endif

#ଅନ୍ତର୍ଭାଵ "error.h"

#ଯଦି HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#ଯଦି HAVE_PTHREADS
#ଅନ୍ତର୍ଭାଵ <pthread.h>

#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ଅନ୍ତର୍ଭାଵ <stdlib.h>

#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) କର {                            \
    ଅକ୍ଷର errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(ଖାଲି, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} ଯେତେବେଳେ (0)

#define ASSERT_PTHREAD_NORET(func, ...) କର {                            \
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = func(__VA_ARGS__);                                        \
    ଯଦି (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} ଯେତେବେଳେ (0)

#define ASSERT_PTHREAD(func, ...) କର {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ଫେରନ୍ତୁ 0;                                                           \
} ଯେତେବେଳେ (0)

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_join(pthread_t thread, ଶୂନ୍ୟ **ମୂଲ୍ୟ_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, ମୂଲ୍ୟ_ptr);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_mutex_init(pthread_mutex_t *mutex, ଅଚଳ pthread_mutexattr_t *attr)
{
    ଯଦି (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } ଅନ୍ୟଥା {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_init(pthread_cond_t *cond, ଅଚଳ pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ଅଚଳ ସଂରଚନା timespec *abstime)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = pthread_cond_timedwait(cond, mutex, abstime);
    ଯଦି (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strict_pthread_once(pthread_once_t *once_control, ଶୂନ୍ୟ (*init_routine)(ଶୂନ୍ୟ))
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

#ନଚେତଯଦି HAVE_OS2THREADS
#ଅନ୍ତର୍ଭାଵ "compat/os2threads.h"
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ "compat/w32pthreads.h"
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

#ଅନ୍ୟଥା

#define AVMutex ଅକ୍ଷର
#define AV_MUTEX_INITIALIZER 0

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_mutex_init(AVMutex *mutex, ଅଚଳ ଶୂନ୍ୟ *attr){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_mutex_lock(AVMutex *mutex){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_mutex_unlock(AVMutex *mutex){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_mutex_destroy(AVMutex *mutex){ ଫେରନ୍ତୁ 0; }

#define AVCond ଅକ୍ଷର

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_init(AVCond *cond, ଅଚଳ ଶୂନ୍ୟ *attr){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_destroy(AVCond *cond){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_signal(AVCond *cond){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_broadcast(AVCond *cond){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_wait(AVCond *cond, AVMutex *mutex){ ଫେରନ୍ତୁ 0; }
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ଅଚଳ ଶୂନ୍ୟ *abstime){ ଫେରନ୍ତୁ 0; }

#define AVOnce ଅକ୍ଷର
#define AV_ONCE_INIT 0

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_thread_once(ଅକ୍ଷର *control, ଶୂନ୍ୟ (*routine)(ଶୂନ୍ୟ))
{
    ଯଦି (!*control) {
        routine();
        *control = 1;
    }
    ଫେରନ୍ତୁ 0;
}

#endif

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_thread_setname(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

#ଯଦି HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#ନଚେତଯଦି HAVE_PTHREAD_SETNAME_NP
#ଯଦି defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#ନଚେତଯଦି defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#ଅନ୍ୟଥା
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#ନଚେତଯଦି HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#ନଚେତଯଦି HAVE_W32THREADS
    ret = win32_thread_setname(name);
#ଅନ୍ୟଥା
    ret = AVERROR(ENOSYS);
#endif

    ଫେରନ୍ତୁ ret;
}

#endif /* AVUTIL_THREAD_H */
