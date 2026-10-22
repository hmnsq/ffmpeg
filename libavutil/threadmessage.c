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

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stddef.h>

#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "fifo.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "threadmessage.h"
#અન્તર્ભાવ "thread.h"

સંરચના AVThreadMessageQueue {
#જો HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    પૂર્ણાંક err_send;
    પૂર્ણાંક err_recv;
    unsigned elsize;
    શૂન્ય (*free_func)(શૂન્ય *સંદેશ);
#નહીંતર
    પૂર્ણાંક dummy;
#endif
};

પૂર્ણાંક av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#જો HAVE_THREADS
    AVThreadMessageQueue *rmq;
    પૂર્ણાંક ret = 0;

    જો (nelem > INT_MAX / elsize)
        પાછા AVERROR(EINVAL);
    જો (!(rmq = av_mallocz(કદ(*rmq))))
        પાછા AVERROR(ENOMEM);
    જો ((ret = pthread_mutex_init(&rmq->lock, ખાલી))) {
        av_free(rmq);
        પાછા AVERROR(ret);
    }
    જો ((ret = pthread_cond_init(&rmq->cond_recv, ખાલી))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        પાછા AVERROR(ret);
    }
    જો ((ret = pthread_cond_init(&rmq->cond_send, ખાલી))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        પાછા AVERROR(ret);
    }
    જો (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        પાછા AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    પાછા 0;
#નહીંતર
    *mq = ખાલી;
    પાછા AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

શૂન્ય av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           શૂન્ય (*free_func)(શૂન્ય *સંદેશ))
{
#જો HAVE_THREADS
    mq->free_func = free_func;
#endif
}

શૂન્ય av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#જો HAVE_THREADS
    જો (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

પૂર્ણાંક av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#જો HAVE_THREADS
    પૂર્ણાંક ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    પાછા ret;
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif
}

#જો HAVE_THREADS

સ્થિર પૂર્ણાંક av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               શૂન્ય *સંદેશ,
                                               unsigned flags)
{
    જ્યારે (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        જો ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            પાછા AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    જો (mq->err_send)
        પાછા mq->err_send;
    av_fifo_write(mq->fifo, સંદેશ, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    પાછા 0;
}

સ્થિર પૂર્ણાંક av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               શૂન્ય *સંદેશ,
                                               unsigned flags)
{
    જ્યારે (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        જો ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            પાછા AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    જો (!av_fifo_can_read(mq->fifo))
        પાછા mq->err_recv;
    av_fifo_read(mq->fifo, સંદેશ, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    પાછા 0;
}

#endif /* HAVE_THREADS */

પૂર્ણાંક av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 શૂન્ય *સંદેશ,
                                 unsigned flags)
{
#જો HAVE_THREADS
    પૂર્ણાંક ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, સંદેશ, flags);
    pthread_mutex_unlock(&mq->lock);
    પાછા ret;
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

પૂર્ણાંક av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 શૂન્ય *સંદેશ,
                                 unsigned flags)
{
#જો HAVE_THREADS
    પૂર્ણાંક ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, સંદેશ, flags);
    pthread_mutex_unlock(&mq->lock);
    પાછા ret;
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

શૂન્ય av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          પૂર્ણાંક err)
{
#જો HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

શૂન્ય av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          પૂર્ણાંક err)
{
#જો HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#જો HAVE_THREADS
સ્થિર પૂર્ણાંક free_func_wrap(શૂન્ય *arg, શૂન્ય *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *સંદેશ = buf;
    માટે (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(સંદેશ + i * mq->elsize);
    પાછા 0;
}
#endif

શૂન્ય av_thread_message_flush(AVThreadMessageQueue *mq)
{
#જો HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    જો (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
