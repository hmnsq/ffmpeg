/*
 * Copyright (c) 2014 Nicolas George
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FFmpeg; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ضمن <limits.h>
#ضمن <stddef.h>

#ضمن "error.h"
#ضمن "fifo.h"
#ضمن "mem.h"
#ضمن "threadmessage.h"
#ضمن "thread.h"

بنية AVThread_پیغام_کتار {
#إذا HAVE_تارونه
    AVFifo *fifo;
    pthread_mutex_t قلف;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    بینښه elsize;
    فراغ (*free_func)(فراغ *پیغام);
#وإلا
    صحيح dummy;
#د_که_پای
};

صحيح av_thread_پیغام_کتار_alloc(AVThread_پیغام_کتار **mq,
                                  بینښه nelem,
                                  بینښه elsize)
{
#إذا HAVE_تارونه
    AVThread_پیغام_کتار *rmq;
    صحيح ret = 0;

    إذا (nelem > لوی_عدد / elsize)
        أرجع AVERROR(EINVAL);
    إذا (!(rmq = av_mallocz(حجم(*rmq))))
        أرجع AVERROR(ENOMEM);
    إذا ((ret = pthread_mutex_init(&rmq->قلف, عدم))) {
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->قلف);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->قلف);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->قلف);
        av_free(rmq);
        أرجع AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    أرجع 0;
#وإلا
    *mq = عدم;
    أرجع AVERROR(ENOSYS);
#د_که_پای /* HAVE_THREADS */
}

فراغ av_thread_پیغام_کتار_سېټ_free_func(AVThread_پیغام_کتار *mq,
                                           فراغ (*free_func)(فراغ *پیغام))
{
#إذا HAVE_تارونه
    mq->free_func = free_func;
#د_که_پای
}

فراغ av_thread_پیغام_کتار_free(AVThread_پیغام_کتار **mq)
{
#إذا HAVE_تارونه
    إذا (*mq) {
        av_thread_پیغام_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->قلف);
        av_freep(mq);
    }
#د_که_پای
}

صحيح av_thread_پیغام_کتار_nb_elems(AVThread_پیغام_کتار *mq)
{
#إذا HAVE_تارونه
    صحيح ret;
    pthread_mutex_قلف(&mq->قلف);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->قلف);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#د_که_پای
}

#إذا HAVE_تارونه

ساكن صحيح av_thread_پیغام_کتار_send_locked(AVThread_پیغام_کتار *mq,
                                               فراغ *پیغام,
                                               بینښه flags)
{
    طالما (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        إذا ((flags & AV_THREAD_پیغام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->قلف);
    }
    إذا (mq->err_send)
        أرجع mq->err_send;
    av_fifo_write(mq->fifo, پیغام, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    أرجع 0;
}

ساكن صحيح av_thread_پیغام_کتار_recv_locked(AVThread_پیغام_کتار *mq,
                                               فراغ *پیغام,
                                               بینښه flags)
{
    طالما (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        إذا ((flags & AV_THREAD_پیغام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->قلف);
    }
    إذا (!av_fifo_can_read(mq->fifo))
        أرجع mq->err_recv;
    av_fifo_read(mq->fifo, پیغام, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    أرجع 0;
}

#د_که_پای /* HAVE_THREADS */

صحيح av_thread_پیغام_کتار_send(AVThread_پیغام_کتار *mq,
                                 فراغ *پیغام,
                                 بینښه flags)
{
#إذا HAVE_تارونه
    صحيح ret;

    pthread_mutex_قلف(&mq->قلف);
    ret = av_thread_پیغام_کتار_send_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->قلف);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#د_که_پای /* HAVE_THREADS */
}

صحيح av_thread_پیغام_کتار_recv(AVThread_پیغام_کتار *mq,
                                 فراغ *پیغام,
                                 بینښه flags)
{
#إذا HAVE_تارونه
    صحيح ret;

    pthread_mutex_قلف(&mq->قلف);
    ret = av_thread_پیغام_کتار_recv_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->قلف);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#د_که_پای /* HAVE_THREADS */
}

فراغ av_thread_پیغام_کتار_سېټ_err_send(AVThread_پیغام_کتار *mq,
                                          صحيح err)
{
#إذا HAVE_تارونه
    pthread_mutex_قلف(&mq->قلف);
    mq->err_send = err;
    pthread_cond_خپرونه(&mq->cond_send);
    pthread_mutex_unlock(&mq->قلف);
#د_که_پای /* HAVE_THREADS */
}

فراغ av_thread_پیغام_کتار_سېټ_err_recv(AVThread_پیغام_کتار *mq,
                                          صحيح err)
{
#إذا HAVE_تارونه
    pthread_mutex_قلف(&mq->قلف);
    mq->err_recv = err;
    pthread_cond_خپرونه(&mq->cond_recv);
    pthread_mutex_unlock(&mq->قلف);
#د_که_پای /* HAVE_THREADS */
}

#إذا HAVE_تارونه
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThread_پیغام_کتار *mq = arg;
    uint8_t *پیغام = buf;
    لكل (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(پیغام + i * mq->elsize);
    أرجع 0;
}
#د_که_پای

فراغ av_thread_پیغام_flush(AVThread_پیغام_کتار *mq)
{
#إذا HAVE_تارونه
    size_t کارول_شوی;

    pthread_mutex_قلف(&mq->قلف);
    کارول_شوی = av_fifo_can_read(mq->fifo);
    إذا (mq->free_func)
        av_fifo_read_منزل_cb(mq->fifo, free_func_wrap, mq, &کارول_شوی);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_خپرونه(&mq->cond_send);
    pthread_mutex_unlock(&mq->قلف);
#د_که_پای /* HAVE_THREADS */
}
