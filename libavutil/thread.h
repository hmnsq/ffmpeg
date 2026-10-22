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

#অন্তর্ভাব "config.h"

#যদি HAVE_PRCTL
#অন্তর্ভাব <sys/prctl.h>
#নতুবা_যদি (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#অন্তর্ভাব <pthread_np.h>
#endif

#অন্তর্ভাব "error.h"

#যদি HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#যদি HAVE_PTHREADS
#অন্তর্ভাব <pthread.h>

#যদি defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#অন্তর্ভাব <stdlib.h>

#অন্তর্ভাব "log.h"
#অন্তর্ভাব "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) করো {                            \
    অক্ষর errbuf[AV_ERROR_MAX_STRING_আকার] = "";                         \
    av_log(ফাঁকা, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_আকার,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} যখন (0)

#define ASSERT_PTHREAD_NORET(func, ...) করো {                            \
    পূর্ণসংখ্যা ret = func(__VA_ARGS__);                                        \
    যদি (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} যখন (0)

#define ASSERT_PTHREAD(func, ...) করো {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ফেরত 0;                                                           \
} যখন (0)

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_join(pthread_t thread, শূন্য **মান_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, মান_ptr);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_mutex_init(pthread_mutex_t *mutex, ধ্রুবক pthread_mutexattr_t *attr)
{
    যদি (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } অন্যথা {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ফেরত 0;
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_init(pthread_cond_t *cond, ধ্রুবক pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ধ্রুবক কাঠামো timespec *abstime)
{
    পূর্ণসংখ্যা ret = pthread_cond_timedwait(cond, mutex, abstime);
    যদি (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ফেরত ret;
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা strict_pthread_once(pthread_once_t *once_control, শূন্য (*init_routine)(শূন্য))
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

#নতুবা_যদি HAVE_OS2THREADS
#অন্তর্ভাব "compat/os2threads.h"
#অন্যথা
#অন্তর্ভাব "compat/w32pthreads.h"
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

#অন্যথা

#define AVMutex অক্ষর
#define AV_MUTEX_INITIALIZER 0

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_mutex_init(AVMutex *mutex, ধ্রুবক শূন্য *attr){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_mutex_lock(AVMutex *mutex){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_mutex_unlock(AVMutex *mutex){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_mutex_destroy(AVMutex *mutex){ ফেরত 0; }

#define AVCond অক্ষর

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_init(AVCond *cond, ধ্রুবক শূন্য *attr){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_destroy(AVCond *cond){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_signal(AVCond *cond){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_broadcast(AVCond *cond){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_wait(AVCond *cond, AVMutex *mutex){ ফেরত 0; }
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ধ্রুবক শূন্য *abstime){ ফেরত 0; }

#define AVOnce অক্ষর
#define AV_ONCE_INIT 0

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_thread_once(অক্ষর *control, শূন্য (*routine)(শূন্য))
{
    যদি (!*control) {
        routine();
        *control = 1;
    }
    ফেরত 0;
}

#endif

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_thread_setname(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা ret = 0;

#যদি HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#নতুবা_যদি HAVE_PTHREAD_SETNAME_NP
#যদি defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#নতুবা_যদি defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#অন্যথা
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#নতুবা_যদি HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#নতুবা_যদি HAVE_W32THREADS
    ret = win32_thread_setname(name);
#অন্যথা
    ret = AVERROR(ENOSYS);
#endif

    ফেরত ret;
}

#endif /* AVUTIL_THREAD_H */
