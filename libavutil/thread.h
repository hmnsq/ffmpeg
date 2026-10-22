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

#अगर_अघोषित AVUTIL_THREAD_H
#घोषणा AVUTIL_THREAD_H

#समावेश "config.h"

#अगर HAVE_PRCTL
#समावेश <sys/prctl.h>
#या_अगर (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#समावेश <pthread_np.h>
#पूर्ण_अगर

#समावेश "error.h"

#अगर HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#अगर HAVE_PTHREADS
#समावेश <pthread.h>

#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#समावेश <stdlib.h>

#समावेश "log.h"
#समावेश "macros.h"

#घोषणा ASSERT_PTHREAD_ABORT(func, ret) करो {                            \
    अक्षर errbuf[AV_ERROR_MAX_STRING_आकार] = "";                         \
    av_log(शून्य, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_आकार,       \
                                AVERROR(ret)));                         \
    पात();                                                            \
} जबतक (0)

#घोषणा ASSERT_PTHREAD_NORET(func, ...) करो {                            \
    पूर्णांक ret = func(__VA_ARGS__);                                        \
    अगर (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} जबतक (0)

#घोषणा ASSERT_PTHREAD(func, ...) करो {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    वापस 0;                                                           \
} जबतक (0)

अटल अंतरभूत पूर्णांक strict_pthread_join(pthread_t thread, व्योम **मूल्य_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, मूल्य_ptr);
}

अटल अंतरभूत पूर्णांक strict_pthread_mutex_init(pthread_mutex_t *mutex, स्थिर pthread_mutexattr_t *attr)
{
    अगर (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } अन्यथा {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    वापस 0;
}

अटल अंतरभूत पूर्णांक strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

अटल अंतरभूत पूर्णांक strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

अटल अंतरभूत पूर्णांक strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_init(pthread_cond_t *cond, स्थिर pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

अटल अंतरभूत पूर्णांक strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                स्थिर काष्ठा timespec *abstime)
{
    पूर्णांक ret = pthread_cond_timedwait(cond, mutex, abstime);
    अगर (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    वापस ret;
}

अटल अंतरभूत पूर्णांक strict_pthread_once(pthread_once_t *once_control, व्योम (*init_routine)(व्योम))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#घोषणा pthread_join           strict_pthread_join
#घोषणा pthread_mutex_init     strict_pthread_mutex_init
#घोषणा pthread_mutex_destroy  strict_pthread_mutex_destroy
#घोषणा pthread_mutex_lock     strict_pthread_mutex_lock
#घोषणा pthread_mutex_unlock   strict_pthread_mutex_unlock
#घोषणा pthread_cond_init      strict_pthread_cond_init
#घोषणा pthread_cond_destroy   strict_pthread_cond_destroy
#घोषणा pthread_cond_signal    strict_pthread_cond_signal
#घोषणा pthread_cond_broadcast strict_pthread_cond_broadcast
#घोषणा pthread_cond_wait      strict_pthread_cond_wait
#घोषणा pthread_cond_timedwait strict_pthread_cond_timedwait
#घोषणा pthread_once           strict_pthread_once
#पूर्ण_अगर

#या_अगर HAVE_OS2THREADS
#समावेश "compat/os2threads.h"
#अन्यथा
#समावेश "compat/w32pthreads.h"
#पूर्ण_अगर

#घोषणा AVMutex pthread_mutex_t
#घोषणा AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#घोषणा ff_mutex_init    pthread_mutex_init
#घोषणा ff_mutex_lock    pthread_mutex_lock
#घोषणा ff_mutex_unlock  pthread_mutex_unlock
#घोषणा ff_mutex_destroy pthread_mutex_destroy

#घोषणा AVCond pthread_cond_t

#घोषणा ff_cond_init      pthread_cond_init
#घोषणा ff_cond_destroy   pthread_cond_destroy
#घोषणा ff_cond_signal    pthread_cond_signal
#घोषणा ff_cond_broadcast pthread_cond_broadcast
#घोषणा ff_cond_wait      pthread_cond_wait
#घोषणा ff_cond_timedwait pthread_cond_timedwait

#घोषणा AVOnce pthread_once_t
#घोषणा AV_ONCE_INIT PTHREAD_ONCE_INIT

#घोषणा ff_thread_once(control, routine) pthread_once(control, routine)

#अन्यथा

#घोषणा AVMutex अक्षर
#घोषणा AV_MUTEX_INITIALIZER 0

अटल अंतरभूत पूर्णांक ff_mutex_init(AVMutex *mutex, स्थिर व्योम *attr){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_mutex_lock(AVMutex *mutex){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_mutex_unlock(AVMutex *mutex){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_mutex_destroy(AVMutex *mutex){ वापस 0; }

#घोषणा AVCond अक्षर

अटल अंतरभूत पूर्णांक ff_cond_init(AVCond *cond, स्थिर व्योम *attr){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_cond_destroy(AVCond *cond){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_cond_signal(AVCond *cond){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_cond_broadcast(AVCond *cond){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_cond_wait(AVCond *cond, AVMutex *mutex){ वापस 0; }
अटल अंतरभूत पूर्णांक ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    स्थिर व्योम *abstime){ वापस 0; }

#घोषणा AVOnce अक्षर
#घोषणा AV_ONCE_INIT 0

अटल अंतरभूत पूर्णांक ff_thread_once(अक्षर *control, व्योम (*routine)(व्योम))
{
    अगर (!*control) {
        routine();
        *control = 1;
    }
    वापस 0;
}

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक ff_thread_setname(स्थिर अक्षर *name)
{
    पूर्णांक ret = 0;

#अगर HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#या_अगर HAVE_PTHREAD_SETNAME_NP
#अगर defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#या_अगर defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#अन्यथा
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#पूर्ण_अगर
#या_अगर HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#या_अगर HAVE_W32THREADS
    ret = win32_thread_setname(name);
#अन्यथा
    ret = AVERROR(ENOSYS);
#पूर्ण_अगर

    वापस ret;
}

#पूर्ण_अगर /* AVUTIL_THREAD_H */
