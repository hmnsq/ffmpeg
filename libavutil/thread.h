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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_THREAD_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_THREAD_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_PRCTL
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/prctl.h>
#ਜਾਂਜੇ (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_ਸੈੱਟ_NAME_NP) && HAVE_PTHREAD_NP_H
#ਅਨ੍ਤਰ੍ਭਾਵ <pthread_np.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"

#ਜੇ HAVE_PTHREADS || HAVE_W32_ਧਾਗੇ || HAVE_OS2_ਧਾਗੇ

#ਜੇ HAVE_PTHREADS
#ਅਨ੍ਤਰ੍ਭਾਵ <pthread.h>

#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSERT_PTHREAD_ABORT(func, ret) ਕਰੋ {                            \
    ਅੱਖਰ errbuf[AV_ERROR_MAX_STRING_ਮਾਪ] = "";                         \
    av_log(ਨਿਰਾ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_ਮਾਪ,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSERT_PTHREAD_NORET(func, ...) ਕਰੋ {                            \
    ਪੂਰਨ ret = func(__VA_ARGS__);                                        \
    ਜੇ (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSERT_PTHREAD(func, ...) ਕਰੋ {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    ਵਾਪਸ 0;                                                           \
} ਜਦੋਂ (0)

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_join(pthread_t thread, ਖਾਲੀ **ਮੁੱਲ_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, ਮੁੱਲ_ptr);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_mutex_init(pthread_mutex_t *mutex, ਅਚਲ pthread_mutexattr_t *attr)
{
    ਜੇ (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } ਨਹੀਂਤਾਂ {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_mutex_ਤਾਲਾ(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_ਤਾਲਾ, mutex);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_init(pthread_cond_t *cond, ਅਚਲ pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_ਪ੍ਰਸਾਰਣ(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_ਪ੍ਰਸਾਰਣ, cond);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ਅਚਲ ਬਣਤਰ timespec *abstime)
{
    ਪੂਰਨ ret = pthread_cond_timedwait(cond, mutex, abstime);
    ਜੇ (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ strict_pthread_once(pthread_once_t *once_control, ਖਾਲੀ (*init_routine)(ਖਾਲੀ))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_join           strict_pthread_join
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_mutex_init     strict_pthread_mutex_init
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_mutex_destroy  strict_pthread_mutex_destroy
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_mutex_ਤਾਲਾ     strict_pthread_mutex_ਤਾਲਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_mutex_unlock   strict_pthread_mutex_unlock
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_init      strict_pthread_cond_init
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_destroy   strict_pthread_cond_destroy
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_signal    strict_pthread_cond_signal
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_ਪ੍ਰਸਾਰਣ strict_pthread_cond_ਪ੍ਰਸਾਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_wait      strict_pthread_cond_wait
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_cond_timedwait strict_pthread_cond_timedwait
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pthread_once           strict_pthread_once
#ਜੇ_ਅੰਤ

#ਜਾਂਜੇ HAVE_OS2_ਧਾਗੇ
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/os2threads.h"
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32pthreads.h"
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVMutex pthread_mutex_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_mutex_init    pthread_mutex_init
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_mutex_ਤਾਲਾ    pthread_mutex_ਤਾਲਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_mutex_unlock  pthread_mutex_unlock
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_mutex_destroy pthread_mutex_destroy

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVCond pthread_cond_t

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_init      pthread_cond_init
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_destroy   pthread_cond_destroy
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_signal    pthread_cond_signal
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_ਪ੍ਰਸਾਰਣ pthread_cond_ਪ੍ਰਸਾਰਣ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_wait      pthread_cond_wait
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_cond_timedwait pthread_cond_timedwait

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVOnce pthread_once_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ONCE_INIT PTHREAD_ONCE_INIT

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_thread_once(control, routine) pthread_once(control, routine)

#ਨਹੀਂਤਾਂ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVMutex ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_MUTEX_INITIALIZER 0

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_mutex_init(AVMutex *mutex, ਅਚਲ ਖਾਲੀ *attr){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_mutex_ਤਾਲਾ(AVMutex *mutex){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_mutex_unlock(AVMutex *mutex){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_mutex_destroy(AVMutex *mutex){ ਵਾਪਸ 0; }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVCond ਅੱਖਰ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_init(AVCond *cond, ਅਚਲ ਖਾਲੀ *attr){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_destroy(AVCond *cond){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_signal(AVCond *cond){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_ਪ੍ਰਸਾਰਣ(AVCond *cond){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_wait(AVCond *cond, AVMutex *mutex){ ਵਾਪਸ 0; }
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ਅਚਲ ਖਾਲੀ *abstime){ ਵਾਪਸ 0; }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVOnce ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ONCE_INIT 0

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_thread_once(ਅੱਖਰ *control, ਖਾਲੀ (*routine)(ਖਾਲੀ))
{
    ਜੇ (!*control) {
        routine();
        *control = 1;
    }
    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_thread_setname(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ ret = 0;

#ਜੇ HAVE_PRCTL
    ret = AVERROR(prctl(PR_ਸੈੱਟ_NAME, name));
#ਜਾਂਜੇ HAVE_PTHREAD_SETNAME_NP
#ਜੇ defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#ਜਾਂਜੇ defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#ਨਹੀਂਤਾਂ
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#ਜੇ_ਅੰਤ
#ਜਾਂਜੇ HAVE_PTHREAD_ਸੈੱਟ_NAME_NP
    pthread_ਸੈੱਟ_name_np(pthread_self(), name);
#ਜਾਂਜੇ HAVE_W32_ਧਾਗੇ
    ret = win32_thread_setname(name);
#ਨਹੀਂਤਾਂ
    ret = AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ /* AVUTIL_THREAD_H */
