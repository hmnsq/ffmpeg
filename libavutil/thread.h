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

#यदि_अपरिभाषितम् AVUTIL_THREAD_H
#परिभाषय AVUTIL_THREAD_H

#अन्तर्भाव "config.h"

#यदि HAVE_PRCTL
#अन्तर्भाव <sys/prctl.h>
#नोचेद्यदि (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_समुच्चयः_NAME_NP) && HAVE_PTHREAD_NP_H
#अन्तर्भाव <pthread_np.h>
#यदि_अन्तः

#अन्तर्भाव "error.h"

#यदि HAVE_PTHREADS || HAVE_W32_तन्तवः || HAVE_OS2_तन्तवः

#यदि HAVE_PTHREADS
#अन्तर्भाव <pthread.h>

#यदि defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#अन्तर्भाव <stdlib.h>

#अन्तर्भाव "log.h"
#अन्तर्भाव "macros.h"

#परिभाषय ASSERT_PTHREAD_ABORT(func, ret) कुरु {                            \
    वर्ण errbuf[AV_ERROR_MAX_STRING_आकार] = "";                         \
    av_log(रिक्त, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_आकार,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} यावत् (0)

#परिभाषय ASSERT_PTHREAD_NORET(func, ...) कुरु {                            \
    पूर्णाङ्क ret = func(__VA_ARGS__);                                        \
    यदि (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} यावत् (0)

#परिभाषय ASSERT_PTHREAD(func, ...) कुरु {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    प्रत्यागम 0;                                                           \
} यावत् (0)

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_join(pthread_t thread, शून्य **मानम्_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, मानम्_ptr);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_init(pthread_mutex_t *mutex, ध्रुव pthread_mutexattr_t *attr)
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
    प्रत्यागम 0;
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_तालकम्(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_तालकम्, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_init(pthread_cond_t *cond, ध्रुव pthread_condattr_t *attr)
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

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_प्रसारणम्(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_प्रसारणम्, cond);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ध्रुव संरचना timespec *abstime)
{
    पूर्णाङ्क ret = pthread_cond_timedwait(cond, mutex, abstime);
    यदि (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    प्रत्यागम ret;
}

स्थिर अन्तःस्थ पूर्णाङ्क strict_pthread_once(pthread_once_t *once_control, शून्य (*init_routine)(शून्य))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#परिभाषय pthread_join           strict_pthread_join
#परिभाषय pthread_mutex_init     strict_pthread_mutex_init
#परिभाषय pthread_mutex_destroy  strict_pthread_mutex_destroy
#परिभाषय pthread_mutex_तालकम्     strict_pthread_mutex_तालकम्
#परिभाषय pthread_mutex_unlock   strict_pthread_mutex_unlock
#परिभाषय pthread_cond_init      strict_pthread_cond_init
#परिभाषय pthread_cond_destroy   strict_pthread_cond_destroy
#परिभाषय pthread_cond_signal    strict_pthread_cond_signal
#परिभाषय pthread_cond_प्रसारणम् strict_pthread_cond_प्रसारणम्
#परिभाषय pthread_cond_wait      strict_pthread_cond_wait
#परिभाषय pthread_cond_timedwait strict_pthread_cond_timedwait
#परिभाषय pthread_once           strict_pthread_once
#यदि_अन्तः

#नोचेद्यदि HAVE_OS2_तन्तवः
#अन्तर्भाव "compat/os2threads.h"
#अन्यथा
#अन्तर्भाव "compat/w32pthreads.h"
#यदि_अन्तः

#परिभाषय AVMutex pthread_mutex_t
#परिभाषय AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#परिभाषय ff_mutex_init    pthread_mutex_init
#परिभाषय ff_mutex_तालकम्    pthread_mutex_तालकम्
#परिभाषय ff_mutex_unlock  pthread_mutex_unlock
#परिभाषय ff_mutex_destroy pthread_mutex_destroy

#परिभाषय AVCond pthread_cond_t

#परिभाषय ff_cond_init      pthread_cond_init
#परिभाषय ff_cond_destroy   pthread_cond_destroy
#परिभाषय ff_cond_signal    pthread_cond_signal
#परिभाषय ff_cond_प्रसारणम् pthread_cond_प्रसारणम्
#परिभाषय ff_cond_wait      pthread_cond_wait
#परिभाषय ff_cond_timedwait pthread_cond_timedwait

#परिभाषय AVOnce pthread_once_t
#परिभाषय AV_ONCE_INIT PTHREAD_ONCE_INIT

#परिभाषय ff_thread_once(control, routine) pthread_once(control, routine)

#अन्यथा

#परिभाषय AVMutex वर्ण
#परिभाषय AV_MUTEX_INITIALIZER 0

स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_init(AVMutex *mutex, ध्रुव शून्य *attr){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_तालकम्(AVMutex *mutex){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_unlock(AVMutex *mutex){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_mutex_destroy(AVMutex *mutex){ प्रत्यागम 0; }

#परिभाषय AVCond वर्ण

स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_init(AVCond *cond, ध्रुव शून्य *attr){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_destroy(AVCond *cond){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_signal(AVCond *cond){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_प्रसारणम्(AVCond *cond){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_wait(AVCond *cond, AVMutex *mutex){ प्रत्यागम 0; }
स्थिर अन्तःस्थ पूर्णाङ्क ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ध्रुव शून्य *abstime){ प्रत्यागम 0; }

#परिभाषय AVOnce वर्ण
#परिभाषय AV_ONCE_INIT 0

स्थिर अन्तःस्थ पूर्णाङ्क ff_thread_once(वर्ण *control, शून्य (*routine)(शून्य))
{
    यदि (!*control) {
        routine();
        *control = 1;
    }
    प्रत्यागम 0;
}

#यदि_अन्तः

स्थिर अन्तःस्थ पूर्णाङ्क ff_thread_setname(ध्रुव वर्ण *name)
{
    पूर्णाङ्क ret = 0;

#यदि HAVE_PRCTL
    ret = AVERROR(prctl(PR_समुच्चयः_NAME, name));
#नोचेद्यदि HAVE_PTHREAD_SETNAME_NP
#यदि defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#नोचेद्यदि defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#अन्यथा
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#यदि_अन्तः
#नोचेद्यदि HAVE_PTHREAD_समुच्चयः_NAME_NP
    pthread_समुच्चयः_name_np(pthread_self(), name);
#नोचेद्यदि HAVE_W32_तन्तवः
    ret = win32_thread_setname(name);
#अन्यथा
    ret = AVERROR(ENOSYS);
#यदि_अन्तः

    प्रत्यागम ret;
}

#यदि_अन्तः /* AVUTIL_THREAD_H */
