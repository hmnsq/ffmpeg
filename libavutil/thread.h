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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_THREAD_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_THREAD_H

#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_PRCTL
#ಅನ್ತರ್ಭಾವ <sys/prctl.h>
#ಅಥವಾಆದರೆ (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_ಗಣ_NAME_NP) && HAVE_PTHREAD_NP_H
#ಅನ್ತರ್ಭಾವ <pthread_np.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "error.h"

#ಆದರೆ HAVE_PTHREADS || HAVE_W32_ಎಳೆಗಳು || HAVE_OS2_ಎಳೆಗಳು

#ಆದರೆ HAVE_PTHREADS
#ಅನ್ತರ್ಭಾವ <pthread.h>

#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ASSERT_PTHREAD_ABORT(func, ret) ಮಾಡು {                            \
    ಅಕ್ಷರ errbuf[AV_ERROR_MAX_STRING_ಗಾತ್ರ] = "";                         \
    av_log(ಖಾಲಿ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_ಗಾತ್ರ,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು ASSERT_PTHREAD_NORET(func, ...) ಮಾಡು {                            \
    ಪೂರ್ಣಾಂಕ ret = func(__VA_ARGS__);                                        \
    ಆದರೆ (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು ASSERT_PTHREAD(func, ...) ಮಾಡು {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ಹಿಂತಿರುಗಿ 0;                                                           \
} ಆಗ (0)

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_join(pthread_t thread, ಶೂನ್ಯ **ಮೌಲ್ಯ_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, ಮೌಲ್ಯ_ptr);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_mutex_init(pthread_mutex_t *mutex, ಸ್ಥಿರಾಂಕ pthread_mutexattr_t *attr)
{
    ಆದರೆ (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } ಇಲ್ಲದಿದ್ದರೆ {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_mutex_ಬೀಗ(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_ಬೀಗ, mutex);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_init(pthread_cond_t *cond, ಸ್ಥಿರಾಂಕ pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_ಪ್ರಸಾರ(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_ಪ್ರಸಾರ, cond);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ಸ್ಥಿರಾಂಕ ರಚನೆ timespec *abstime)
{
    ಪೂರ್ಣಾಂಕ ret = pthread_cond_timedwait(cond, mutex, abstime);
    ಆದರೆ (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ strict_pthread_once(pthread_once_t *once_control, ಶೂನ್ಯ (*init_routine)(ಶೂನ್ಯ))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#ವ್ಯಾಖ್ಯಾನಿಸು pthread_join           strict_pthread_join
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_mutex_init     strict_pthread_mutex_init
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_mutex_destroy  strict_pthread_mutex_destroy
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_mutex_ಬೀಗ     strict_pthread_mutex_ಬೀಗ
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_mutex_unlock   strict_pthread_mutex_unlock
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_init      strict_pthread_cond_init
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_destroy   strict_pthread_cond_destroy
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_signal    strict_pthread_cond_signal
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_ಪ್ರಸಾರ strict_pthread_cond_ಪ್ರಸಾರ
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_wait      strict_pthread_cond_wait
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_cond_timedwait strict_pthread_cond_timedwait
#ವ್ಯಾಖ್ಯಾನಿಸು pthread_once           strict_pthread_once
#ಆದರೆ_ಅಂತ್ಯ

#ಅಥವಾಆದರೆ HAVE_OS2_ಎಳೆಗಳು
#ಅನ್ತರ್ಭಾವ "compat/os2threads.h"
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ "compat/w32pthreads.h"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು AVMutex pthread_mutex_t
#ವ್ಯಾಖ್ಯಾನಿಸು AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#ವ್ಯಾಖ್ಯಾನಿಸು ff_mutex_init    pthread_mutex_init
#ವ್ಯಾಖ್ಯಾನಿಸು ff_mutex_ಬೀಗ    pthread_mutex_ಬೀಗ
#ವ್ಯಾಖ್ಯಾನಿಸು ff_mutex_unlock  pthread_mutex_unlock
#ವ್ಯಾಖ್ಯಾನಿಸು ff_mutex_destroy pthread_mutex_destroy

#ವ್ಯಾಖ್ಯಾನಿಸು AVCond pthread_cond_t

#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_init      pthread_cond_init
#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_destroy   pthread_cond_destroy
#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_signal    pthread_cond_signal
#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_ಪ್ರಸಾರ pthread_cond_ಪ್ರಸಾರ
#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_wait      pthread_cond_wait
#ವ್ಯಾಖ್ಯಾನಿಸು ff_cond_timedwait pthread_cond_timedwait

#ವ್ಯಾಖ್ಯಾನಿಸು AVOnce pthread_once_t
#ವ್ಯಾಖ್ಯಾನಿಸು AV_ONCE_INIT PTHREAD_ONCE_INIT

#ವ್ಯಾಖ್ಯಾನಿಸು ff_thread_once(control, routine) pthread_once(control, routine)

#ಇಲ್ಲದಿದ್ದರೆ

#ವ್ಯಾಖ್ಯಾನಿಸು AVMutex ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು AV_MUTEX_INITIALIZER 0

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_mutex_init(AVMutex *mutex, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *attr){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_mutex_ಬೀಗ(AVMutex *mutex){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_mutex_unlock(AVMutex *mutex){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_mutex_destroy(AVMutex *mutex){ ಹಿಂತಿರುಗಿ 0; }

#ವ್ಯಾಖ್ಯಾನಿಸು AVCond ಅಕ್ಷರ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_init(AVCond *cond, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *attr){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_destroy(AVCond *cond){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_signal(AVCond *cond){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_ಪ್ರಸಾರ(AVCond *cond){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_wait(AVCond *cond, AVMutex *mutex){ ಹಿಂತಿರುಗಿ 0; }
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *abstime){ ಹಿಂತಿರುಗಿ 0; }

#ವ್ಯಾಖ್ಯಾನಿಸು AVOnce ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು AV_ONCE_INIT 0

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_thread_once(ಅಕ್ಷರ *control, ಶೂನ್ಯ (*routine)(ಶೂನ್ಯ))
{
    ಆದರೆ (!*control) {
        routine();
        *control = 1;
    }
    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_thread_setname(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ ret = 0;

#ಆದರೆ HAVE_PRCTL
    ret = AVERROR(prctl(PR_ಗಣ_NAME, name));
#ಅಥವಾಆದರೆ HAVE_PTHREAD_SETNAME_NP
#ಆದರೆ defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#ಅಥವಾಆದರೆ defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#ಇಲ್ಲದಿದ್ದರೆ
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#ಆದರೆ_ಅಂತ್ಯ
#ಅಥವಾಆದರೆ HAVE_PTHREAD_ಗಣ_NAME_NP
    pthread_ಗಣ_name_np(pthread_self(), name);
#ಅಥವಾಆದರೆ HAVE_W32_ಎಳೆಗಳು
    ret = win32_thread_setname(name);
#ಇಲ್ಲದಿದ್ದರೆ
    ret = AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_THREAD_H */
