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

بنية AVThread_پیام_صف {
#إذا HAVE_نخها
    AVFifo *fifo;
    pthread_mutex_t قفل_2;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    بیعلامت elsize;
    فراغ (*free_func)(فراغ *پیام);
#وإلا
    صحيح dummy;
#پایان_اگر
};

صحيح av_thread_پیام_صف_alloc(AVThread_پیام_صف **mq,
                                  بیعلامت nelem,
                                  بیعلامت elsize)
{
#إذا HAVE_نخها
    AVThread_پیام_صف *rmq;
    صحيح ret = 0;

    إذا (nelem > بیشترین_صحیح / elsize)
        أرجع AVERROR(EINVAL);
    إذا (!(rmq = av_mallocz(حجم(*rmq))))
        أرجع AVERROR(ENOMEM);
    إذا ((ret = pthread_mutex_init(&rmq->قفل_2, عدم))) {
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->قفل_2);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->قفل_2);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->قفل_2);
        av_free(rmq);
        أرجع AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    أرجع 0;
#وإلا
    *mq = عدم;
    أرجع AVERROR(ENOSYS);
#پایان_اگر /* HAVE_THREADS */
}

فراغ av_thread_پیام_صف_مجموعه_free_func(AVThread_پیام_صف *mq,
                                           فراغ (*free_func)(فراغ *پیام))
{
#إذا HAVE_نخها
    mq->free_func = free_func;
#پایان_اگر
}

فراغ av_thread_پیام_صف_free(AVThread_پیام_صف **mq)
{
#إذا HAVE_نخها
    إذا (*mq) {
        av_thread_پیام_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->قفل_2);
        av_freep(mq);
    }
#پایان_اگر
}

صحيح av_thread_پیام_صف_nb_elems(AVThread_پیام_صف *mq)
{
#إذا HAVE_نخها
    صحيح ret;
    pthread_mutex_قفل(&mq->قفل_2);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->قفل_2);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#پایان_اگر
}

#إذا HAVE_نخها

ساكن صحيح av_thread_پیام_صف_send_locked(AVThread_پیام_صف *mq,
                                               فراغ *پیام,
                                               بیعلامت flags)
{
    طالما (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        إذا ((flags & AV_THREAD_پیام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->قفل_2);
    }
    إذا (mq->err_send)
        أرجع mq->err_send;
    av_fifo_write(mq->fifo, پیام, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    أرجع 0;
}

ساكن صحيح av_thread_پیام_صف_recv_locked(AVThread_پیام_صف *mq,
                                               فراغ *پیام,
                                               بیعلامت flags)
{
    طالما (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        إذا ((flags & AV_THREAD_پیام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->قفل_2);
    }
    إذا (!av_fifo_can_read(mq->fifo))
        أرجع mq->err_recv;
    av_fifo_read(mq->fifo, پیام, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    أرجع 0;
}

#پایان_اگر /* HAVE_THREADS */

صحيح av_thread_پیام_صف_send(AVThread_پیام_صف *mq,
                                 فراغ *پیام,
                                 بیعلامت flags)
{
#إذا HAVE_نخها
    صحيح ret;

    pthread_mutex_قفل(&mq->قفل_2);
    ret = av_thread_پیام_صف_send_locked(mq, پیام, flags);
    pthread_mutex_unlock(&mq->قفل_2);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#پایان_اگر /* HAVE_THREADS */
}

صحيح av_thread_پیام_صف_recv(AVThread_پیام_صف *mq,
                                 فراغ *پیام,
                                 بیعلامت flags)
{
#إذا HAVE_نخها
    صحيح ret;

    pthread_mutex_قفل(&mq->قفل_2);
    ret = av_thread_پیام_صف_recv_locked(mq, پیام, flags);
    pthread_mutex_unlock(&mq->قفل_2);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#پایان_اگر /* HAVE_THREADS */
}

فراغ av_thread_پیام_صف_مجموعه_err_send(AVThread_پیام_صف *mq,
                                          صحيح err)
{
#إذا HAVE_نخها
    pthread_mutex_قفل(&mq->قفل_2);
    mq->err_send = err;
    pthread_cond_پخش(&mq->cond_send);
    pthread_mutex_unlock(&mq->قفل_2);
#پایان_اگر /* HAVE_THREADS */
}

فراغ av_thread_پیام_صف_مجموعه_err_recv(AVThread_پیام_صف *mq,
                                          صحيح err)
{
#إذا HAVE_نخها
    pthread_mutex_قفل(&mq->قفل_2);
    mq->err_recv = err;
    pthread_cond_پخش(&mq->cond_recv);
    pthread_mutex_unlock(&mq->قفل_2);
#پایان_اگر /* HAVE_THREADS */
}

#إذا HAVE_نخها
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThread_پیام_صف *mq = arg;
    uint8_t *پیام = buf;
    لكل (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(پیام + i * mq->elsize);
    أرجع 0;
}
#پایان_اگر

فراغ av_thread_پیام_flush(AVThread_پیام_صف *mq)
{
#إذا HAVE_نخها
    size_t استفاده_شده;

    pthread_mutex_قفل(&mq->قفل_2);
    استفاده_شده = av_fifo_can_read(mq->fifo);
    إذا (mq->free_func)
        av_fifo_read_مقصد_cb(mq->fifo, free_func_wrap, mq, &استفاده_شده);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_پخش(&mq->cond_send);
    pthread_mutex_unlock(&mq->قفل_2);
#پایان_اگر /* HAVE_THREADS */
}
