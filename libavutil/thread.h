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

#اگر_غیر_تعریف_شدہ AVUTIL_THREAD_H
#تعریف_کرو AVUTIL_THREAD_H

#شامل "config.h"

#اگر HAVE_PRCTL
#شامل <sys/prctl.h>
#وگرنہ_اگر (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_سیٹ_NAME_NP) && HAVE_PTHREAD_NP_H
#شامل <pthread_np.h>
#اگر_ختم

#شامل "error.h"

#اگر HAVE_PTHREADS || HAVE_W32_دھاگے || HAVE_OS2_دھاگے

#اگر HAVE_PTHREADS
#شامل <pthread.h>

#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#شامل <stdlib.h>

#شامل "log.h"
#شامل "macros.h"

#تعریف_کرو ASSERT_PTHREAD_ABORT(func, ret) کرو {                            \
    حرف errbuf[AV_ERROR_MAX_STRING_سائز] = "";                         \
    av_log(تہی, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_سائز,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} جب (0)

#تعریف_کرو ASSERT_PTHREAD_NORET(func, ...) کرو {                            \
    صحیح ret = func(__VA_ARGS__);                                        \
    اگر (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} جب (0)

#تعریف_کرو ASSERT_PTHREAD(func, ...) کرو {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    واپس 0;                                                           \
} جب (0)

ساکن اندرونی صحیح strict_pthread_join(pthread_t thread, خالی **قدر_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, قدر_ptr);
}

ساکن اندرونی صحیح strict_pthread_mutex_init(pthread_mutex_t *mutex, ثابت pthread_mutexattr_t *attr)
{
    اگر (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } ورنہ {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    واپس 0;
}

ساکن اندرونی صحیح strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

ساکن اندرونی صحیح strict_pthread_mutex_تالا(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_تالا, mutex);
}

ساکن اندرونی صحیح strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

ساکن اندرونی صحیح strict_pthread_cond_init(pthread_cond_t *cond, ثابت pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

ساکن اندرونی صحیح strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

ساکن اندرونی صحیح strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

ساکن اندرونی صحیح strict_pthread_cond_نشر(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_نشر, cond);
}

ساکن اندرونی صحیح strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

ساکن اندرونی صحیح strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                ثابت ساخت timespec *abstime)
{
    صحیح ret = pthread_cond_timedwait(cond, mutex, abstime);
    اگر (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    واپس ret;
}

ساکن اندرونی صحیح strict_pthread_once(pthread_once_t *once_control, خالی (*init_routine)(خالی))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#تعریف_کرو pthread_join           strict_pthread_join
#تعریف_کرو pthread_mutex_init     strict_pthread_mutex_init
#تعریف_کرو pthread_mutex_destroy  strict_pthread_mutex_destroy
#تعریف_کرو pthread_mutex_تالا     strict_pthread_mutex_تالا
#تعریف_کرو pthread_mutex_unlock   strict_pthread_mutex_unlock
#تعریف_کرو pthread_cond_init      strict_pthread_cond_init
#تعریف_کرو pthread_cond_destroy   strict_pthread_cond_destroy
#تعریف_کرو pthread_cond_signal    strict_pthread_cond_signal
#تعریف_کرو pthread_cond_نشر strict_pthread_cond_نشر
#تعریف_کرو pthread_cond_wait      strict_pthread_cond_wait
#تعریف_کرو pthread_cond_timedwait strict_pthread_cond_timedwait
#تعریف_کرو pthread_once           strict_pthread_once
#اگر_ختم

#وگرنہ_اگر HAVE_OS2_دھاگے
#شامل "compat/os2threads.h"
#ورنہ
#شامل "compat/w32pthreads.h"
#اگر_ختم

#تعریف_کرو AVMutex pthread_mutex_t
#تعریف_کرو AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#تعریف_کرو ff_mutex_init    pthread_mutex_init
#تعریف_کرو ff_mutex_تالا    pthread_mutex_تالا
#تعریف_کرو ff_mutex_unlock  pthread_mutex_unlock
#تعریف_کرو ff_mutex_destroy pthread_mutex_destroy

#تعریف_کرو AVCond pthread_cond_t

#تعریف_کرو ff_cond_init      pthread_cond_init
#تعریف_کرو ff_cond_destroy   pthread_cond_destroy
#تعریف_کرو ff_cond_signal    pthread_cond_signal
#تعریف_کرو ff_cond_نشر pthread_cond_نشر
#تعریف_کرو ff_cond_wait      pthread_cond_wait
#تعریف_کرو ff_cond_timedwait pthread_cond_timedwait

#تعریف_کرو AVOnce pthread_once_t
#تعریف_کرو AV_ONCE_INIT PTHREAD_ONCE_INIT

#تعریف_کرو ff_thread_once(control, routine) pthread_once(control, routine)

#ورنہ

#تعریف_کرو AVMutex حرف
#تعریف_کرو AV_MUTEX_INITIALIZER 0

ساکن اندرونی صحیح ff_mutex_init(AVMutex *mutex, ثابت خالی *attr){ واپس 0; }
ساکن اندرونی صحیح ff_mutex_تالا(AVMutex *mutex){ واپس 0; }
ساکن اندرونی صحیح ff_mutex_unlock(AVMutex *mutex){ واپس 0; }
ساکن اندرونی صحیح ff_mutex_destroy(AVMutex *mutex){ واپس 0; }

#تعریف_کرو AVCond حرف

ساکن اندرونی صحیح ff_cond_init(AVCond *cond, ثابت خالی *attr){ واپس 0; }
ساکن اندرونی صحیح ff_cond_destroy(AVCond *cond){ واپس 0; }
ساکن اندرونی صحیح ff_cond_signal(AVCond *cond){ واپس 0; }
ساکن اندرونی صحیح ff_cond_نشر(AVCond *cond){ واپس 0; }
ساکن اندرونی صحیح ff_cond_wait(AVCond *cond, AVMutex *mutex){ واپس 0; }
ساکن اندرونی صحیح ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    ثابت خالی *abstime){ واپس 0; }

#تعریف_کرو AVOnce حرف
#تعریف_کرو AV_ONCE_INIT 0

ساکن اندرونی صحیح ff_thread_once(حرف *control, خالی (*routine)(خالی))
{
    اگر (!*control) {
        routine();
        *control = 1;
    }
    واپس 0;
}

#اگر_ختم

ساکن اندرونی صحیح ff_thread_setname(ثابت حرف *name)
{
    صحیح ret = 0;

#اگر HAVE_PRCTL
    ret = AVERROR(prctl(PR_سیٹ_NAME, name));
#وگرنہ_اگر HAVE_PTHREAD_SETNAME_NP
#اگر defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#وگرنہ_اگر defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#ورنہ
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#اگر_ختم
#وگرنہ_اگر HAVE_PTHREAD_سیٹ_NAME_NP
    pthread_سیٹ_name_np(pthread_self(), name);
#وگرنہ_اگر HAVE_W32_دھاگے
    ret = win32_thread_setname(name);
#ورنہ
    ret = AVERROR(ENOSYS);
#اگر_ختم

    واپس ret;
}

#اگر_ختم /* AVUTIL_THREAD_H */
