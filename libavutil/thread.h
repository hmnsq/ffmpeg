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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_THREAD_H
#وصف_ڪريو AVUTIL_THREAD_H

#ضمن "config.h"

#إذا HAVE_PRCTL
#ضمن <sys/prctl.h>
#وإلاإذا (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_سيٽ_NAME_NP) && HAVE_PTHREAD_NP_H
#ضمن <pthread_np.h>
#جيڪڏهن_پورو

#ضمن "error.h"

#إذا HAVE_PTHREADS || HAVE_W32_ڌاڳا || HAVE_OS2_ڌاڳا

#إذا HAVE_PTHREADS
#ضمن <pthread.h>

#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ضمن <stdlib.h>

#ضمن "log.h"
#ضمن "macros.h"

#وصف_ڪريو ASSERT_PTHREAD_ABORT(func, ret) افعل {                            \
    حرف errbuf[AV_ERROR_MAX_STRING_سائيز] = "";                         \
    av_log(عدم, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_سائيز,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} طالما (0)

#وصف_ڪريو ASSERT_PTHREAD_NORET(func, ...) افعل {                            \
    صحيح ret = func(__VA_ARGS__);                                        \
    إذا (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} طالما (0)

#وصف_ڪريو ASSERT_PTHREAD(func, ...) افعل {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    أرجع 0;                                                           \
} طالما (0)

ساكن مضمن صحيح strict_pthread_join(pthread_t thread, فراغ **قدر_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, قدر_ptr);
}

ساكن مضمن صحيح strict_pthread_mutex_init(pthread_mutex_t *mutex, ثابت pthread_mutexattr_t *attr)
{
    إذا (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } وإلا {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    أرجع 0;
}

ساكن مضمن صحيح strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ساكن مضمن صحيح strict_pthread_mutex_تالو(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_تالو, mutex);
}

ساكن مضمن صحيح strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ساكن مضمن صحيح strict_pthread_cond_init(pthread_cond_t *cond, ثابت pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ساكن مضمن صحيح strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ساكن مضمن صحيح strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ساكن مضمن صحيح strict_pthread_cond_نشر(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_نشر, cond);
}

ساكن مضمن صحيح strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ساكن مضمن صحيح strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ثابت بنية timespec *abstime)
{
    صحيح ret = pthread_cond_timedwait(cond, mutex, abstime);
    إذا (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    أرجع ret;
}

ساكن مضمن صحيح strict_pthread_once(pthread_once_t *once_control, فراغ (*init_routine)(فراغ))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#وصف_ڪريو pthread_join           strict_pthread_join
#وصف_ڪريو pthread_mutex_init     strict_pthread_mutex_init
#وصف_ڪريو pthread_mutex_destroy  strict_pthread_mutex_destroy
#وصف_ڪريو pthread_mutex_تالو     strict_pthread_mutex_تالو
#وصف_ڪريو pthread_mutex_unlock   strict_pthread_mutex_unlock
#وصف_ڪريو pthread_cond_init      strict_pthread_cond_init
#وصف_ڪريو pthread_cond_destroy   strict_pthread_cond_destroy
#وصف_ڪريو pthread_cond_signal    strict_pthread_cond_signal
#وصف_ڪريو pthread_cond_نشر strict_pthread_cond_نشر
#وصف_ڪريو pthread_cond_wait      strict_pthread_cond_wait
#وصف_ڪريو pthread_cond_timedwait strict_pthread_cond_timedwait
#وصف_ڪريو pthread_once           strict_pthread_once
#جيڪڏهن_پورو

#وإلاإذا HAVE_OS2_ڌاڳا
#ضمن "compat/os2threads.h"
#وإلا
#ضمن "compat/w32pthreads.h"
#جيڪڏهن_پورو

#وصف_ڪريو AVMutex pthread_mutex_t
#وصف_ڪريو AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#وصف_ڪريو ff_mutex_init    pthread_mutex_init
#وصف_ڪريو ff_mutex_تالو    pthread_mutex_تالو
#وصف_ڪريو ff_mutex_unlock  pthread_mutex_unlock
#وصف_ڪريو ff_mutex_destroy pthread_mutex_destroy

#وصف_ڪريو AVCond pthread_cond_t

#وصف_ڪريو ff_cond_init      pthread_cond_init
#وصف_ڪريو ff_cond_destroy   pthread_cond_destroy
#وصف_ڪريو ff_cond_signal    pthread_cond_signal
#وصف_ڪريو ff_cond_نشر pthread_cond_نشر
#وصف_ڪريو ff_cond_wait      pthread_cond_wait
#وصف_ڪريو ff_cond_timedwait pthread_cond_timedwait

#وصف_ڪريو AVOnce pthread_once_t
#وصف_ڪريو AV_ONCE_INIT PTHREAD_ONCE_INIT

#وصف_ڪريو ff_thread_once(control, routine) pthread_once(control, routine)

#وإلا

#وصف_ڪريو AVMutex حرف
#وصف_ڪريو AV_MUTEX_INITIALIZER 0

ساكن مضمن صحيح ff_mutex_init(AVMutex *mutex, ثابت فراغ *attr){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_تالو(AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_unlock(AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_destroy(AVMutex *mutex){ أرجع 0; }

#وصف_ڪريو AVCond حرف

ساكن مضمن صحيح ff_cond_init(AVCond *cond, ثابت فراغ *attr){ أرجع 0; }
ساكن مضمن صحيح ff_cond_destroy(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_signal(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_نشر(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_wait(AVCond *cond, AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ثابت فراغ *abstime){ أرجع 0; }

#وصف_ڪريو AVOnce حرف
#وصف_ڪريو AV_ONCE_INIT 0

ساكن مضمن صحيح ff_thread_once(حرف *control, فراغ (*routine)(فراغ))
{
    إذا (!*control) {
        routine();
        *control = 1;
    }
    أرجع 0;
}

#جيڪڏهن_پورو

ساكن مضمن صحيح ff_thread_setname(ثابت حرف *name)
{
    صحيح ret = 0;

#إذا HAVE_PRCTL
    ret = AVERROR(prctl(PR_سيٽ_NAME, name));
#وإلاإذا HAVE_PTHREAD_SETNAME_NP
#إذا defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#وإلاإذا defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#وإلا
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#جيڪڏهن_پورو
#وإلاإذا HAVE_PTHREAD_سيٽ_NAME_NP
    pthread_سيٽ_name_np(pthread_self(), name);
#وإلاإذا HAVE_W32_ڌاڳا
    ret = win32_thread_setname(name);
#وإلا
    ret = AVERROR(ENOSYS);
#جيڪڏهن_پورو

    أرجع ret;
}

#جيڪڏهن_پورو /* AVUTIL_THREAD_H */
