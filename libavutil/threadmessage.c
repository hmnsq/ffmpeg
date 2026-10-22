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

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>

#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "fifo.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "threadmessage.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"

ସଂରଚନା AVThreadMessageQueue {
#ଯଦି HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err_send;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err_recv;
    unsigned elsize;
    ଶୂନ୍ୟ (*free_func)(ଶୂନ୍ୟ *ସନ୍ଦେଶ);
#ଅନ୍ୟଥା
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy;
#endif
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#ଯଦି HAVE_THREADS
    AVThreadMessageQueue *rmq;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (nelem > INT_MAX / elsize)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଯଦି (!(rmq = av_mallocz(ଆକାର(*rmq))))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    ଯଦି ((ret = pthread_mutex_init(&rmq->lock, ଖାଲି))) {
        av_free(rmq);
        ଫେରନ୍ତୁ AVERROR(ret);
    }
    ଯଦି ((ret = pthread_cond_init(&rmq->cond_recv, ଖାଲି))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ଫେରନ୍ତୁ AVERROR(ret);
    }
    ଯଦି ((ret = pthread_cond_init(&rmq->cond_send, ଖାଲି))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ଫେରନ୍ତୁ AVERROR(ret);
    }
    ଯଦି (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ଫେରନ୍ତୁ 0;
#ଅନ୍ୟଥା
    *mq = ଖାଲି;
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ଶୂନ୍ୟ av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           ଶୂନ୍ୟ (*free_func)(ଶୂନ୍ୟ *ସନ୍ଦେଶ))
{
#ଯଦି HAVE_THREADS
    mq->free_func = free_func;
#endif
}

ଶୂନ୍ୟ av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#ଯଦି HAVE_THREADS
    ଯଦି (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#ଯଦି HAVE_THREADS
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ଫେରନ୍ତୁ ret;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
}

#ଯଦି HAVE_THREADS

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               ଶୂନ୍ୟ *ସନ୍ଦେଶ,
                                               unsigned flags)
{
    ଯେତେବେଳେ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ଯଦି ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ଫେରନ୍ତୁ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    ଯଦି (mq->err_send)
        ଫେରନ୍ତୁ mq->err_send;
    av_fifo_write(mq->fifo, ସନ୍ଦେଶ, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               ଶୂନ୍ୟ *ସନ୍ଦେଶ,
                                               unsigned flags)
{
    ଯେତେବେଳେ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ଯଦି ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ଫେରନ୍ତୁ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    ଯଦି (!av_fifo_can_read(mq->fifo))
        ଫେରନ୍ତୁ mq->err_recv;
    av_fifo_read(mq->fifo, ସନ୍ଦେଶ, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ଫେରନ୍ତୁ 0;
}

#endif /* HAVE_THREADS */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 ଶୂନ୍ୟ *ସନ୍ଦେଶ,
                                 unsigned flags)
{
#ଯଦି HAVE_THREADS
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, ସନ୍ଦେଶ, flags);
    pthread_mutex_unlock(&mq->lock);
    ଫେରନ୍ତୁ ret;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 ଶୂନ୍ୟ *ସନ୍ଦେଶ,
                                 unsigned flags)
{
#ଯଦି HAVE_THREADS
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, ସନ୍ଦେଶ, flags);
    pthread_mutex_unlock(&mq->lock);
    ଫେରନ୍ତୁ ret;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ଶୂନ୍ୟ av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା err)
{
#ଯଦି HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

ଶୂନ୍ୟ av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା err)
{
#ଯଦି HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#ଯଦି HAVE_THREADS
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା free_func_wrap(ଶୂନ୍ୟ *arg, ଶୂନ୍ୟ *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *ସନ୍ଦେଶ = buf;
    ପାଇଁ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(ସନ୍ଦେଶ + i * mq->elsize);
    ଫେରନ୍ତୁ 0;
}
#endif

ଶୂନ୍ୟ av_thread_message_flush(AVThreadMessageQueue *mq)
{
#ଯଦି HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    ଯଦି (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
