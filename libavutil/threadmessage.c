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

بنية AVThreadMessageQueue {
#ܐܢ HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    unsigned elsize;
    فراغ (*free_func)(فراغ *msg);
#ܐܚܪܢܐ
    صحيح dummy;
#endif
};

صحيح av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#ܐܢ HAVE_THREADS
    AVThreadMessageQueue *rmq;
    صحيح ret = 0;

    ܐܢ (nelem > INT_MAX / elsize)
        ܦܢܐ AVERROR(EINVAL);
    ܐܢ (!(rmq = av_mallocz(حجم(*rmq))))
        ܦܢܐ AVERROR(ENOMEM);
    ܐܢ ((ret = pthread_mutex_init(&rmq->lock, عدم))) {
        av_free(rmq);
        ܦܢܐ AVERROR(ret);
    }
    ܐܢ ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ܦܢܐ AVERROR(ret);
    }
    ܐܢ ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ܦܢܐ AVERROR(ret);
    }
    ܐܢ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ܦܢܐ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ܦܢܐ 0;
#ܐܚܪܢܐ
    *mq = عدم;
    ܦܢܐ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           فراغ (*free_func)(فراغ *msg))
{
#ܐܢ HAVE_THREADS
    mq->free_func = free_func;
#endif
}

فراغ av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#ܐܢ HAVE_THREADS
    ܐܢ (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

صحيح av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#ܐܢ HAVE_THREADS
    صحيح ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ܦܢܐ ret;
#ܐܚܪܢܐ
    ܦܢܐ AVERROR(ENOSYS);
#endif
}

#ܐܢ HAVE_THREADS

ساكن صحيح av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               فراغ *msg,
                                               unsigned flags)
{
    ܟܡܐ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ܐܢ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ܦܢܐ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    ܐܢ (mq->err_send)
        ܦܢܐ mq->err_send;
    av_fifo_write(mq->fifo, msg, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ܦܢܐ 0;
}

ساكن صحيح av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               فراغ *msg,
                                               unsigned flags)
{
    ܟܡܐ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ܐܢ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ܦܢܐ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    ܐܢ (!av_fifo_can_read(mq->fifo))
        ܦܢܐ mq->err_recv;
    av_fifo_read(mq->fifo, msg, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ܦܢܐ 0;
}

#endif /* HAVE_THREADS */

صحيح av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 فراغ *msg,
                                 unsigned flags)
{
#ܐܢ HAVE_THREADS
    صحيح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ܦܢܐ ret;
#ܐܚܪܢܐ
    ܦܢܐ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

صحيح av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 فراغ *msg,
                                 unsigned flags)
{
#ܐܢ HAVE_THREADS
    صحيح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ܦܢܐ ret;
#ܐܚܪܢܐ
    ܦܢܐ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          صحيح err)
{
#ܐܢ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          صحيح err)
{
#ܐܢ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#ܐܢ HAVE_THREADS
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *msg = buf;
    لكل (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(msg + i * mq->elsize);
    ܦܢܐ 0;
}
#endif

فراغ av_thread_message_flush(AVThreadMessageQueue *mq)
{
#ܐܢ HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    ܐܢ (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
