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

#شامل <limits.h>
#شامل <stddef.h>

#شامل "error.h"
#شامل "fifo.h"
#شامل "mem.h"
#شامل "threadmessage.h"
#شامل "thread.h"

ساختار AVThreadMessageQueue {
#اگر HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحیح err_send;
    صحیح err_recv;
    unsigned elsize;
    تهی (*free_func)(تهی *پیام);
#وگرنه
    صحیح dummy;
#endif
};

صحیح av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#اگر HAVE_THREADS
    AVThreadMessageQueue *rmq;
    صحیح ret = 0;

    اگر (nelem > INT_MAX / elsize)
        بازگشت AVERROR(EINVAL);
    اگر (!(rmq = av_mallocz(اندازه(*rmq))))
        بازگشت AVERROR(ENOMEM);
    اگر ((ret = pthread_mutex_init(&rmq->lock, پوچ))) {
        av_free(rmq);
        بازگشت AVERROR(ret);
    }
    اگر ((ret = pthread_cond_init(&rmq->cond_recv, پوچ))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        بازگشت AVERROR(ret);
    }
    اگر ((ret = pthread_cond_init(&rmq->cond_send, پوچ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        بازگشت AVERROR(ret);
    }
    اگر (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        بازگشت AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    بازگشت 0;
#وگرنه
    *mq = پوچ;
    بازگشت AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

تهی av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           تهی (*free_func)(تهی *پیام))
{
#اگر HAVE_THREADS
    mq->free_func = free_func;
#endif
}

تهی av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#اگر HAVE_THREADS
    اگر (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

صحیح av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#اگر HAVE_THREADS
    صحیح ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    بازگشت ret;
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif
}

#اگر HAVE_THREADS

ایستا صحیح av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               تهی *پیام,
                                               unsigned flags)
{
    وقتی (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        اگر ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            بازگشت AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    اگر (mq->err_send)
        بازگشت mq->err_send;
    av_fifo_write(mq->fifo, پیام, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    بازگشت 0;
}

ایستا صحیح av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               تهی *پیام,
                                               unsigned flags)
{
    وقتی (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        اگر ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            بازگشت AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    اگر (!av_fifo_can_read(mq->fifo))
        بازگشت mq->err_recv;
    av_fifo_read(mq->fifo, پیام, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    بازگشت 0;
}

#endif /* HAVE_THREADS */

صحیح av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 تهی *پیام,
                                 unsigned flags)
{
#اگر HAVE_THREADS
    صحیح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, پیام, flags);
    pthread_mutex_unlock(&mq->lock);
    بازگشت ret;
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

صحیح av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 تهی *پیام,
                                 unsigned flags)
{
#اگر HAVE_THREADS
    صحیح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, پیام, flags);
    pthread_mutex_unlock(&mq->lock);
    بازگشت ret;
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

تهی av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          صحیح err)
{
#اگر HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

تهی av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          صحیح err)
{
#اگر HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#اگر HAVE_THREADS
ایستا صحیح free_func_wrap(تهی *arg, تهی *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *پیام = buf;
    برای (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(پیام + i * mq->elsize);
    بازگشت 0;
}
#endif

تهی av_thread_message_flush(AVThreadMessageQueue *mq)
{
#اگر HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    اگر (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
