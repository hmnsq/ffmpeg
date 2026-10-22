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

#నిర్వచితం_కాకపోతే AVUTIL_THREAD_H
#నిర్వచించు AVUTIL_THREAD_H

#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_PRCTL
#అన్తర్భావ <sys/prctl.h>
#లేదావేళ (HAVE_PTHREAD_SETNAME_NP || HAVE_PTHREAD_సమితి_NAME_NP) && HAVE_PTHREAD_NP_H
#అన్తర్భావ <pthread_np.h>
#అయితే_ముగింపు

#అన్తర్భావ "error.h"

#ఒకవేళ HAVE_PTHREADS || HAVE_W32_దారాలు || HAVE_OS2_దారాలు

#ఒకవేళ HAVE_PTHREADS
#అన్తర్భావ <pthread.h>

#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL > 1

#అన్తర్భావ <stdlib.h>

#అన్తర్భావ "log.h"
#అన్తర్భావ "macros.h"

#నిర్వచించు ASSERT_PTHREAD_ABORT(func, ret) చేయి {                            \
    అక్షరం errbuf[AV_ERROR_MAX_STRING_కొలత] = "";                         \
    av_log(ఖాళీ, AV_LOG_FATAL, AV_STRINGIFY(func)                       \
           " failed with error: %s\n",                                  \
           av_make_error_string(errbuf, AV_ERROR_MAX_STRING_కొలత,       \
                                AVERROR(ret)));                         \
    abort();                                                            \
} అయితే (0)

#నిర్వచించు ASSERT_PTHREAD_NORET(func, ...) చేయి {                            \
    పూర్ణాంకం ret = func(__VA_ARGS__);                                        \
    ఒకవేళ (ret)                                                            \
        ASSERT_PTHREAD_ABORT(func, ret);                                \
} అయితే (0)

#నిర్వచించు ASSERT_PTHREAD(func, ...) చేయి {                                  \
    ASSERT_PTHREAD_NORET(func, __VA_ARGS__);                            \
    తిరిగి 0;                                                           \
} అయితే (0)

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_join(pthread_t thread, శూన్య **విలువ_ptr)
{
    ASSERT_PTHREAD(pthread_join, thread, విలువ_ptr);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_mutex_init(pthread_mutex_t *mutex, స్థిరరాశి pthread_mutexattr_t *attr)
{
    ఒకవేళ (attr) {
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, attr);
    } లేకపోతే {
        pthread_mutexattr_t local_attr;
        ASSERT_PTHREAD_NORET(pthread_mutexattr_init, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_settype, &local_attr, PTHREAD_MUTEX_ERRORCHECK);
        ASSERT_PTHREAD_NORET(pthread_mutex_init, mutex, &local_attr);
        ASSERT_PTHREAD_NORET(pthread_mutexattr_destroy, &local_attr);
    }
    తిరిగి 0;
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_destroy, mutex);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_mutex_తాళం(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_తాళం, mutex);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_mutex_unlock, mutex);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_init(pthread_cond_t *cond, స్థిరరాశి pthread_condattr_t *attr)
{
    ASSERT_PTHREAD(pthread_cond_init, cond, attr);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_destroy(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_destroy, cond);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_signal(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_signal, cond);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_ప్రసారం(pthread_cond_t *cond)
{
    ASSERT_PTHREAD(pthread_cond_ప్రసారం, cond);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    ASSERT_PTHREAD(pthread_cond_wait, cond, mutex);
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                                                స్థిరరాశి నిర్మాణం timespec *abstime)
{
    పూర్ణాంకం ret = pthread_cond_timedwait(cond, mutex, abstime);
    ఒకవేళ (ret && ret != ETIMEDOUT)
        ASSERT_PTHREAD_ABORT(pthread_cond_timedwait, ret);
    తిరిగి ret;
}

స్థిర అంతఃవరుస పూర్ణాంకం strict_pthread_once(pthread_once_t *once_control, శూన్య (*init_routine)(శూన్య))
{
    ASSERT_PTHREAD(pthread_once, once_control, init_routine);
}

#నిర్వచించు pthread_join           strict_pthread_join
#నిర్వచించు pthread_mutex_init     strict_pthread_mutex_init
#నిర్వచించు pthread_mutex_destroy  strict_pthread_mutex_destroy
#నిర్వచించు pthread_mutex_తాళం     strict_pthread_mutex_తాళం
#నిర్వచించు pthread_mutex_unlock   strict_pthread_mutex_unlock
#నిర్వచించు pthread_cond_init      strict_pthread_cond_init
#నిర్వచించు pthread_cond_destroy   strict_pthread_cond_destroy
#నిర్వచించు pthread_cond_signal    strict_pthread_cond_signal
#నిర్వచించు pthread_cond_ప్రసారం strict_pthread_cond_ప్రసారం
#నిర్వచించు pthread_cond_wait      strict_pthread_cond_wait
#నిర్వచించు pthread_cond_timedwait strict_pthread_cond_timedwait
#నిర్వచించు pthread_once           strict_pthread_once
#అయితే_ముగింపు

#లేదావేళ HAVE_OS2_దారాలు
#అన్తర్భావ "compat/os2threads.h"
#లేకపోతే
#అన్తర్భావ "compat/w32pthreads.h"
#అయితే_ముగింపు

#నిర్వచించు AVMutex pthread_mutex_t
#నిర్వచించు AV_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#నిర్వచించు ff_mutex_init    pthread_mutex_init
#నిర్వచించు ff_mutex_తాళం    pthread_mutex_తాళం
#నిర్వచించు ff_mutex_unlock  pthread_mutex_unlock
#నిర్వచించు ff_mutex_destroy pthread_mutex_destroy

#నిర్వచించు AVCond pthread_cond_t

#నిర్వచించు ff_cond_init      pthread_cond_init
#నిర్వచించు ff_cond_destroy   pthread_cond_destroy
#నిర్వచించు ff_cond_signal    pthread_cond_signal
#నిర్వచించు ff_cond_ప్రసారం pthread_cond_ప్రసారం
#నిర్వచించు ff_cond_wait      pthread_cond_wait
#నిర్వచించు ff_cond_timedwait pthread_cond_timedwait

#నిర్వచించు AVOnce pthread_once_t
#నిర్వచించు AV_ONCE_INIT PTHREAD_ONCE_INIT

#నిర్వచించు ff_thread_once(control, routine) pthread_once(control, routine)

#లేకపోతే

#నిర్వచించు AVMutex అక్షరం
#నిర్వచించు AV_MUTEX_INITIALIZER 0

స్థిర అంతఃవరుస పూర్ణాంకం ff_mutex_init(AVMutex *mutex, స్థిరరాశి శూన్య *attr){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_mutex_తాళం(AVMutex *mutex){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_mutex_unlock(AVMutex *mutex){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_mutex_destroy(AVMutex *mutex){ తిరిగి 0; }

#నిర్వచించు AVCond అక్షరం

స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_init(AVCond *cond, స్థిరరాశి శూన్య *attr){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_destroy(AVCond *cond){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_signal(AVCond *cond){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_ప్రసారం(AVCond *cond){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_wait(AVCond *cond, AVMutex *mutex){ తిరిగి 0; }
స్థిర అంతఃవరుస పూర్ణాంకం ff_cond_timedwait(AVCond *cond, AVMutex *mutex,
                                    స్థిరరాశి శూన్య *abstime){ తిరిగి 0; }

#నిర్వచించు AVOnce అక్షరం
#నిర్వచించు AV_ONCE_INIT 0

స్థిర అంతఃవరుస పూర్ణాంకం ff_thread_once(అక్షరం *control, శూన్య (*routine)(శూన్య))
{
    ఒకవేళ (!*control) {
        routine();
        *control = 1;
    }
    తిరిగి 0;
}

#అయితే_ముగింపు

స్థిర అంతఃవరుస పూర్ణాంకం ff_thread_setname(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం ret = 0;

#ఒకవేళ HAVE_PRCTL
    ret = AVERROR(prctl(PR_సమితి_NAME, name));
#లేదావేళ HAVE_PTHREAD_SETNAME_NP
#ఒకవేళ defined(__APPLE__)
    ret = AVERROR(pthread_setname_np(name));
#లేదావేళ defined(__NetBSD__)
    ret = AVERROR(pthread_setname_np(pthread_self(), "%s", name));
#లేకపోతే
    ret = AVERROR(pthread_setname_np(pthread_self(), name));
#అయితే_ముగింపు
#లేదావేళ HAVE_PTHREAD_సమితి_NAME_NP
    pthread_సమితి_name_np(pthread_self(), name);
#లేదావేళ HAVE_W32_దారాలు
    ret = win32_thread_setname(name);
#లేకపోతే
    ret = AVERROR(ENOSYS);
#అయితే_ముగింపు

    తిరిగి ret;
}

#అయితే_ముగింపు /* AVUTIL_THREAD_H */
