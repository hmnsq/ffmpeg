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

#अन्तर्भाव "config.h"

#यदि HAVE_PRCTL
#अन्तर्भाव <sys/prctl.h>
#अथवायदि (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#अन्तर्भाव <pthread_np.h>
#endif

#अन्तर्भाव "error.h"

#यदि HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#यदि HAVE_PTHREADS
#अन्तर्भाव <pthread.h>

#यदि defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#अन्तर्भाव <stdlib.h>

#अन्तर्भाव "log.h"
#अन्तर्भाव "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) गर {                            \
    वर्ण errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(रिक्त, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    पात();                                                            \
} जबसम्म (0)

#define ASSERT_PTHREAD_NORET(func, ...) गर {                            \
    पूर्णाङ्क ret = func(__VA_ARGS__);                                        \
    यदि (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} जबसम्म (0)

#define ASSERT_PTHREAD(func, ...) गर {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    फर्काऊ 0;                                                           \
} जबसम्म (0)

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_join(pthread_t thread, शून्य **मान_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, मान_ptr);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_init(pthread_mutex_t *mutex, अचर pthread_mutexattr_t *attr)
{
    यदि (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } अन्यथा {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    फर्काऊ 0;
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_init(pthread_cond_t *cond, अचर pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                अचर संरचना timespec *abstime)
{
    पूर्णाङ्क ret = pthread_cond_timedwait(cond, mutex, abstime);
    यदि (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    फर्काऊ ret;
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_once(pthread_once_t *once_control, शून्य (*init_routine)(शून्य))
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

#अथवायदि HAVE_OS2THREADS
#अन्तर्भाव "compat/os2threads.h"
#अन्यथा
#अन्तर्भाव "compat/w32pthreads.h"
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

#अन्यथा

#define AVMutex वर्ण
#define AV_MUTEX_INITIALIZER 0

स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_init(AVMutex *mutex, अचर शून्य *attr){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_lock(AVMutex *mutex){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_unlock(AVMutex *mutex){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_destroy(AVMutex *mutex){ फर्काऊ 0; }

#define AVCond वर्ण

स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_init(AVCond *cond, अचर शून्य *attr){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_destroy(AVCond *cond){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_signal(AVCond *cond){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_broadcast(AVCond *cond){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_wait(AVCond *cond, AVMutex *mutex){ फर्काऊ 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    अचर शून्य *abstime){ फर्काऊ 0; }

#define AVOnce वर्ण
#define AV_ONCE_INIT 0

स्थिर अन्तःस्थ पूर्णाङ्क ff_thread_once(वर्ण *control, शून्य (*routine)(शून्य))
{
    यदि (!*control) {
        routine();
        *control = 1;
    }
    फर्काऊ 0;
}

#endif

स्थिर अन्तःस्थ पूर्णाङ्क ff_thread_setname(अचर वर्ण *name)
{
    पूर्णाङ्क ret = 0;

#यदि HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#अथवायदि HAVE_PTHREAD_SETNAME_NP
#यदि defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#अथवायदि defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#अन्यथा
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#अथवायदि HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#अथवायदि HAVE_W32THREADS
    ret = win32_thread_setname(name);
#अन्यथा
    ret = AVERROR(ENOSYS);
#endif

    फर्काऊ ret;
}

#endif /* AVUTIL_THREAD_H */
