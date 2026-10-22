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

#که_نه_تعریف_شوی AVUTIL_THREAD_H
#تعریف_کړه AVUTIL_THREAD_H

#ضمن "config.h"

#إذا HAVE_PRCTL
#ضمن <sys/prctl.h>
#وإلاإذا (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_سېټ_NAME_NP) && HAVE_PTHREAD_NP_H
#ضمن <pthread_np.h>
#د_که_پای

#ضمن "error.h"

#إذا HAVE_PTHREADS || HAVE_W32_تارونه || HAVE_OS2_تارونه

#إذا HAVE_PTHREADS
#ضمن <pthread.h>

#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#ضمن <stdlib.h>

#ضمن "log.h"
#ضمن "macros.h"

#تعریف_کړه ASSERT_PTHREAD_ABORT(func, ret) افعل {                            \
    حرف errbuf[AV_ERROR_MAX_STRING_اندازه] = "";                         \
    av_log(عدم, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_اندازه,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} طالما (0)

#تعریف_کړه ASSERT_PTHREAD_NORET(func, ...) افعل {                            \
    صحيح ret = func(__VA_ARGS__);                                        \
    إذا (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} طالما (0)

#تعریف_کړه ASSERT_PTHREAD(func, ...) افعل {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    أرجع 0;                                                           \
} طالما (0)

ساكن مضمن صحيح strict_pthread_join(pthread_t thread, فراغ **ارزښت_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, ارزښت_ptr);
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

ساكن مضمن صحيح strict_pthread_mutex_قلف(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_قلف, mutex);
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

ساكن مضمن صحيح strict_pthread_cond_خپرونه(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_خپرونه, cond);
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

#تعریف_کړه pthread_join           strict_pthread_join
#تعریف_کړه pthread_mutex_init     strict_pthread_mutex_init
#تعریف_کړه pthread_mutex_destroy  strict_pthread_mutex_destroy
#تعریف_کړه pthread_mutex_قلف     strict_pthread_mutex_قلف
#تعریف_کړه pthread_mutex_unlock   strict_pthread_mutex_unlock
#تعریف_کړه pthread_cond_init      strict_pthread_cond_init
#تعریف_کړه pthread_cond_destroy   strict_pthread_cond_destroy
#تعریف_کړه pthread_cond_signal    strict_pthread_cond_signal
#تعریف_کړه pthread_cond_خپرونه strict_pthread_cond_خپرونه
#تعریف_کړه pthread_cond_wait      strict_pthread_cond_wait
#تعریف_کړه pthread_cond_timedwait strict_pthread_cond_timedwait
#تعریف_کړه pthread_once           strict_pthread_once
#د_که_پای

#وإلاإذا HAVE_OS2_تارونه
#ضمن "compat/os2threads.h"
#وإلا
#ضمن "compat/w32pthreads.h"
#د_که_پای

#تعریف_کړه AVMutex pthread_mutex_t
#تعریف_کړه AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#تعریف_کړه ff_mutex_init    pthread_mutex_init
#تعریف_کړه ff_mutex_قلف    pthread_mutex_قلف
#تعریف_کړه ff_mutex_unlock  pthread_mutex_unlock
#تعریف_کړه ff_mutex_destroy pthread_mutex_destroy

#تعریف_کړه AVCond pthread_cond_t

#تعریف_کړه ff_cond_init      pthread_cond_init
#تعریف_کړه ff_cond_destroy   pthread_cond_destroy
#تعریف_کړه ff_cond_signal    pthread_cond_signal
#تعریف_کړه ff_cond_خپرونه pthread_cond_خپرونه
#تعریف_کړه ff_cond_wait      pthread_cond_wait
#تعریف_کړه ff_cond_timedwait pthread_cond_timedwait

#تعریف_کړه AVOnce pthread_once_t
#تعریف_کړه AV_ONCE_INIT PTHREAD_ONCE_INIT

#تعریف_کړه ff_thread_once(control, routine) pthread_once(control, routine)

#وإلا

#تعریف_کړه AVMutex حرف
#تعریف_کړه AV_MUTEX_INITIALIZER 0

ساكن مضمن صحيح ff_mutex_init(AVMutex *mutex, ثابت فراغ *attr){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_قلف(AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_unlock(AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_mutex_destroy(AVMutex *mutex){ أرجع 0; }

#تعریف_کړه AVCond حرف

ساكن مضمن صحيح ff_cond_init(AVCond *cond, ثابت فراغ *attr){ أرجع 0; }
ساكن مضمن صحيح ff_cond_destroy(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_signal(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_خپرونه(AVCond *cond){ أرجع 0; }
ساكن مضمن صحيح ff_cond_wait(AVCond *cond, AVMutex *mutex){ أرجع 0; }
ساكن مضمن صحيح ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ثابت فراغ *abstime){ أرجع 0; }

#تعریف_کړه AVOnce حرف
#تعریف_کړه AV_ONCE_INIT 0

ساكن مضمن صحيح ff_thread_once(حرف *control, فراغ (*routine)(فراغ))
{
    إذا (!*control) {
        routine();
        *control = 1;
    }
    أرجع 0;
}

#د_که_پای

ساكن مضمن صحيح ff_thread_setname(ثابت حرف *name)
{
    صحيح ret = 0;

#إذا HAVE_PRCTL
    ret = AVERROR(prctl(PR_سېټ_NAME, name));
#وإلاإذا HAVE_PTHREAD_SETNAME_NP
#إذا defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#وإلاإذا defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#وإلا
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#د_که_پای
#وإلاإذا HAVE_PTHREAD_سېټ_NAME_NP
    pthread_سېټ_name_np(pthread_self(), name);
#وإلاإذا HAVE_W32_تارونه
    ret = win32_thread_setname(name);
#وإلا
    ret = AVERROR(ENOSYS);
#د_که_پای

    أرجع ret;
}

#د_که_پای /* AVUTIL_THREAD_H */
