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

#അന്തര്ഭാവ "config.h"

#എങ്കിൽ HAVE_PRCTL
#അന്തര്ഭാവ <sys/prctl.h>
#അല്ലെങ്കിലെങ്കിൽ (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_SET_NAME_NP) && HAVE_PTHREAD_NP_H
#അന്തര്ഭാവ <pthread_np.h>
#endif

#അന്തര്ഭാവ "error.h"

#എങ്കിൽ HAVE_PTHREADS || HAVE_W32THREADS || HAVE_OS2THREADS

#എങ്കിൽ HAVE_PTHREADS
#അന്തര്ഭാവ <pthread.h>

#എങ്കിൽ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#അന്തര്ഭാവ <stdlib.h>

#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "macros.h"

#define ASSERT_PTHREAD_ABORT(func, ret) ചെയ്യുക {                            \
    അക്ഷരം errbuf[AV_ERROR_MAX_STRING_SIZE] = "";                         \
    av_log(ശൂന്യ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} ആകുമ്പോൾ (0)

#define ASSERT_PTHREAD_NORET(func, ...) ചെയ്യുക {                            \
    പൂർണ്ണസംഖ്യ ret = func(__VA_ARGS__);                                        \
    എങ്കിൽ (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} ആകുമ്പോൾ (0)

#define ASSERT_PTHREAD(func, ...) ചെയ്യുക {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    തിരികെ 0;                                                           \
} ആകുമ്പോൾ (0)

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_join(pthread_t thread, ശൂന്യം **മൂല്യം_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, മൂല്യം_ptr);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_mutex_init(pthread_mutex_t *mutex, സ്ഥിരം pthread_mutexattr_t *attr)
{
    എങ്കിൽ (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } അല്ലെങ്കിൽ {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    തിരികെ 0;
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_lock, mutex);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_init(pthread_cond_t *cond, സ്ഥിരം pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_broadcast(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_broadcast, cond);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                സ്ഥിരം ഘടന timespec *abstime)
{
    പൂർണ്ണസംഖ്യ ret = pthread_cond_timedwait(cond, mutex, abstime);
    എങ്കിൽ (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    തിരികെ ret;
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ strict_pthread_once(pthread_once_t *once_control, ശൂന്യം (*init_routine)(ശൂന്യം))
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

#അല്ലെങ്കിലെങ്കിൽ HAVE_OS2THREADS
#അന്തര്ഭാവ "compat/os2threads.h"
#അല്ലെങ്കിൽ
#അന്തര്ഭാവ "compat/w32pthreads.h"
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

#അല്ലെങ്കിൽ

#define AVMutex അക്ഷരം
#define AV_MUTEX_INITIALIZER 0

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_mutex_init(AVMutex *mutex, സ്ഥിരം ശൂന്യം *attr){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_mutex_lock(AVMutex *mutex){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_mutex_unlock(AVMutex *mutex){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_mutex_destroy(AVMutex *mutex){ തിരികെ 0; }

#define AVCond അക്ഷരം

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_init(AVCond *cond, സ്ഥിരം ശൂന്യം *attr){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_destroy(AVCond *cond){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_signal(AVCond *cond){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_broadcast(AVCond *cond){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_wait(AVCond *cond, AVMutex *mutex){ തിരികെ 0; }
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    സ്ഥിരം ശൂന്യം *abstime){ തിരികെ 0; }

#define AVOnce അക്ഷരം
#define AV_ONCE_INIT 0

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_thread_once(അക്ഷരം *control, ശൂന്യം (*routine)(ശൂന്യം))
{
    എങ്കിൽ (!*control) {
        routine();
        *control = 1;
    }
    തിരികെ 0;
}

#endif

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ ff_thread_setname(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ ret = 0;

#എങ്കിൽ HAVE_PRCTL
    ret = AVERROR(prctl(PR_SET_NAME, name));
#അല്ലെങ്കിലെങ്കിൽ HAVE_PTHREAD_SETNAME_NP
#എങ്കിൽ defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#അല്ലെങ്കിലെങ്കിൽ defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#അല്ലെങ്കിൽ
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#endif
#അല്ലെങ്കിലെങ്കിൽ HAVE_PTHREAD_SET_NAME_NP
    pthread_set_name_np(pthread_self(), name);
#അല്ലെങ്കിലെങ്കിൽ HAVE_W32THREADS
    ret = win32_thread_setname(name);
#അല്ലെങ്കിൽ
    ret = AVERROR(ENOSYS);
#endif

    തിരികെ ret;
}

#endif /* AVUTIL_THREAD_H */
