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

بنية AVThread_سنیہا_قطار {
#إذا HAVE_دھاگے
    AVFifo *fifo;
    pthread_mutex_t جندرا;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    بنانشانی elsize;
    فراغ (*free_func)(فراغ *پیغام);
#وإلا
    صحيح dummy;
#جے_انت
};

صحيح av_thread_سنیہا_قطار_alloc(AVThread_سنیہا_قطار **mq,
                                  بنانشانی nelem,
                                  بنانشانی elsize)
{
#إذا HAVE_دھاگے
    AVThread_سنیہا_قطار *rmq;
    صحيح ret = 0;

    إذا (nelem > ودھ_توں_ودھ_عدد / elsize)
        أرجع AVERROR(EINVAL);
    إذا (!(rmq = av_mallocz(حجم(*rmq))))
        أرجع AVERROR(ENOMEM);
    إذا ((ret = pthread_mutex_init(&rmq->جندرا, عدم))) {
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->جندرا);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->جندرا);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->جندرا);
        av_free(rmq);
        أرجع AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    أرجع 0;
#وإلا
    *mq = عدم;
    أرجع AVERROR(ENOSYS);
#جے_انت /* HAVE_THREADS */
}

فراغ av_thread_سنیہا_قطار_سیٹ_free_func(AVThread_سنیہا_قطار *mq,
                                           فراغ (*free_func)(فراغ *پیغام))
{
#إذا HAVE_دھاگے
    mq->free_func = free_func;
#جے_انت
}

فراغ av_thread_سنیہا_قطار_free(AVThread_سنیہا_قطار **mq)
{
#إذا HAVE_دھاگے
    إذا (*mq) {
        av_thread_سنیہا_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->جندرا);
        av_freep(mq);
    }
#جے_انت
}

صحيح av_thread_سنیہا_قطار_nb_elems(AVThread_سنیہا_قطار *mq)
{
#إذا HAVE_دھاگے
    صحيح ret;
    pthread_mutex_جندرا(&mq->جندرا);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->جندرا);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جے_انت
}

#إذا HAVE_دھاگے

ساكن صحيح av_thread_سنیہا_قطار_send_locked(AVThread_سنیہا_قطار *mq,
                                               فراغ *پیغام,
                                               بنانشانی flags)
{
    طالما (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        إذا ((flags & AV_THREAD_سنیہا_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->جندرا);
    }
    إذا (mq->err_send)
        أرجع mq->err_send;
    av_fifo_write(mq->fifo, پیغام, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    أرجع 0;
}

ساكن صحيح av_thread_سنیہا_قطار_recv_locked(AVThread_سنیہا_قطار *mq,
                                               فراغ *پیغام,
                                               بنانشانی flags)
{
    طالما (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        إذا ((flags & AV_THREAD_سنیہا_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->جندرا);
    }
    إذا (!av_fifo_can_read(mq->fifo))
        أرجع mq->err_recv;
    av_fifo_read(mq->fifo, پیغام, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    أرجع 0;
}

#جے_انت /* HAVE_THREADS */

صحيح av_thread_سنیہا_قطار_send(AVThread_سنیہا_قطار *mq,
                                 فراغ *پیغام,
                                 بنانشانی flags)
{
#إذا HAVE_دھاگے
    صحيح ret;

    pthread_mutex_جندرا(&mq->جندرا);
    ret = av_thread_سنیہا_قطار_send_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->جندرا);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جے_انت /* HAVE_THREADS */
}

صحيح av_thread_سنیہا_قطار_recv(AVThread_سنیہا_قطار *mq,
                                 فراغ *پیغام,
                                 بنانشانی flags)
{
#إذا HAVE_دھاگے
    صحيح ret;

    pthread_mutex_جندرا(&mq->جندرا);
    ret = av_thread_سنیہا_قطار_recv_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->جندرا);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جے_انت /* HAVE_THREADS */
}

فراغ av_thread_سنیہا_قطار_سیٹ_err_send(AVThread_سنیہا_قطار *mq,
                                          صحيح err)
{
#إذا HAVE_دھاگے
    pthread_mutex_جندرا(&mq->جندرا);
    mq->err_send = err;
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->جندرا);
#جے_انت /* HAVE_THREADS */
}

فراغ av_thread_سنیہا_قطار_سیٹ_err_recv(AVThread_سنیہا_قطار *mq,
                                          صحيح err)
{
#إذا HAVE_دھاگے
    pthread_mutex_جندرا(&mq->جندرا);
    mq->err_recv = err;
    pthread_cond_نشر(&mq->cond_recv);
    pthread_mutex_unlock(&mq->جندرا);
#جے_انت /* HAVE_THREADS */
}

#إذا HAVE_دھاگے
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThread_سنیہا_قطار *mq = arg;
    uint8_t *پیغام = buf;
    لكل (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(پیغام + i * mq->elsize);
    أرجع 0;
}
#جے_انت

فراغ av_thread_سنیہا_flush(AVThread_سنیہا_قطار *mq)
{
#إذا HAVE_دھاگے
    size_t ورتیا;

    pthread_mutex_جندرا(&mq->جندرا);
    ورتیا = av_fifo_can_read(mq->fifo);
    إذا (mq->free_func)
        av_fifo_read_منزل_cb(mq->fifo, free_func_wrap, mq, &ورتیا);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->جندرا);
#جے_انت /* HAVE_THREADS */
}
