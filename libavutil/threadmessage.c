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

بنية AVThread_پيغام_قطار {
#إذا HAVE_ڌاڳا
    AVFifo *fifo;
    pthread_mutex_t تالو;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    بنانشان elsize;
    فراغ (*free_func)(فراغ *نياپو);
#وإلا
    صحيح dummy;
#جيڪڏهن_پورو
};

صحيح av_thread_پيغام_قطار_alloc(AVThread_پيغام_قطار **mq,
                                  بنانشان nelem,
                                  بنانشان elsize)
{
#إذا HAVE_ڌاڳا
    AVThread_پيغام_قطار *rmq;
    صحيح ret = 0;

    إذا (nelem > وڌ_کان_وڌ_عدد / elsize)
        أرجع AVERROR(EINVAL);
    إذا (!(rmq = av_mallocz(حجم(*rmq))))
        أرجع AVERROR(ENOMEM);
    إذا ((ret = pthread_mutex_init(&rmq->تالو, عدم))) {
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->تالو);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->تالو);
        av_free(rmq);
        أرجع AVERROR(ret);
    }
    إذا (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->تالو);
        av_free(rmq);
        أرجع AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    أرجع 0;
#وإلا
    *mq = عدم;
    أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو /* HAVE_THREADS */
}

فراغ av_thread_پيغام_قطار_سيٽ_free_func(AVThread_پيغام_قطار *mq,
                                           فراغ (*free_func)(فراغ *نياپو))
{
#إذا HAVE_ڌاڳا
    mq->free_func = free_func;
#جيڪڏهن_پورو
}

فراغ av_thread_پيغام_قطار_free(AVThread_پيغام_قطار **mq)
{
#إذا HAVE_ڌاڳا
    إذا (*mq) {
        av_thread_پيغام_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->تالو);
        av_freep(mq);
    }
#جيڪڏهن_پورو
}

صحيح av_thread_پيغام_قطار_nb_elems(AVThread_پيغام_قطار *mq)
{
#إذا HAVE_ڌاڳا
    صحيح ret;
    pthread_mutex_تالو(&mq->تالو);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->تالو);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
}

#إذا HAVE_ڌاڳا

ساكن صحيح av_thread_پيغام_قطار_send_locked(AVThread_پيغام_قطار *mq,
                                               فراغ *نياپو,
                                               بنانشان flags)
{
    طالما (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        إذا ((flags & AV_THREAD_پيغام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->تالو);
    }
    إذا (mq->err_send)
        أرجع mq->err_send;
    av_fifo_write(mq->fifo, نياپو, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    أرجع 0;
}

ساكن صحيح av_thread_پيغام_قطار_recv_locked(AVThread_پيغام_قطار *mq,
                                               فراغ *نياپو,
                                               بنانشان flags)
{
    طالما (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        إذا ((flags & AV_THREAD_پيغام_NONBLOCK))
            أرجع AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->تالو);
    }
    إذا (!av_fifo_can_read(mq->fifo))
        أرجع mq->err_recv;
    av_fifo_read(mq->fifo, نياپو, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    أرجع 0;
}

#جيڪڏهن_پورو /* HAVE_THREADS */

صحيح av_thread_پيغام_قطار_send(AVThread_پيغام_قطار *mq,
                                 فراغ *نياپو,
                                 بنانشان flags)
{
#إذا HAVE_ڌاڳا
    صحيح ret;

    pthread_mutex_تالو(&mq->تالو);
    ret = av_thread_پيغام_قطار_send_locked(mq, نياپو, flags);
    pthread_mutex_unlock(&mq->تالو);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو /* HAVE_THREADS */
}

صحيح av_thread_پيغام_قطار_recv(AVThread_پيغام_قطار *mq,
                                 فراغ *نياپو,
                                 بنانشان flags)
{
#إذا HAVE_ڌاڳا
    صحيح ret;

    pthread_mutex_تالو(&mq->تالو);
    ret = av_thread_پيغام_قطار_recv_locked(mq, نياپو, flags);
    pthread_mutex_unlock(&mq->تالو);
    أرجع ret;
#وإلا
    أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو /* HAVE_THREADS */
}

فراغ av_thread_پيغام_قطار_سيٽ_err_send(AVThread_پيغام_قطار *mq,
                                          صحيح err)
{
#إذا HAVE_ڌاڳا
    pthread_mutex_تالو(&mq->تالو);
    mq->err_send = err;
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->تالو);
#جيڪڏهن_پورو /* HAVE_THREADS */
}

فراغ av_thread_پيغام_قطار_سيٽ_err_recv(AVThread_پيغام_قطار *mq,
                                          صحيح err)
{
#إذا HAVE_ڌاڳا
    pthread_mutex_تالو(&mq->تالو);
    mq->err_recv = err;
    pthread_cond_نشر(&mq->cond_recv);
    pthread_mutex_unlock(&mq->تالو);
#جيڪڏهن_پورو /* HAVE_THREADS */
}

#إذا HAVE_ڌاڳا
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThread_پيغام_قطار *mq = arg;
    uint8_t *نياپو = buf;
    لكل (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(نياپو + i * mq->elsize);
    أرجع 0;
}
#جيڪڏهن_پورو

فراغ av_thread_پيغام_flush(AVThread_پيغام_قطار *mq)
{
#إذا HAVE_ڌاڳا
    size_t استعمال_ٿيل;

    pthread_mutex_تالو(&mq->تالو);
    استعمال_ٿيل = av_fifo_can_read(mq->fifo);
    إذا (mq->free_func)
        av_fifo_read_منزل_cb(mq->fifo, free_func_wrap, mq, &استعمال_ٿيل);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->تالو);
#جيڪڏهن_پورو /* HAVE_THREADS */
}
