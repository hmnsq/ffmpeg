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

#include <limits.h>
#include <stddef.h>

#include "error.h"
#include "fifo.h"
#include "mem.h"
#include "threadmessage.h"
#include "thread.h"

sa_nracanaa AVThreadMessageQueue {
#නම් HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    පූර්ණ_සංඛ්‍යා err_send;
    පූර්ණ_සංඛ්‍යා err_recv;
    unsigned elsize;
    void (*free_func)(void *msg);
#නැතහොත්
    පූර්ණ_සංඛ්‍යා dummy;
#endif
};

පූර්ණ_සංඛ්‍යා av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#නම් HAVE_THREADS
    AVThreadMessageQueue *rmq;
    පූර්ණ_සංඛ්‍යා ret = 0;

    නම් (nelem > INT_MAX / elsize)
        ආපසු AVERROR(EINVAL);
    නම් (!(rmq = av_mallocz(parimaa_na(*rmq))))
        ආපසු AVERROR(ENOMEM);
    නම් ((ret = pthread_mutex_init(&rmq->lock, NULL))) {
        av_free(rmq);
        ආපසු AVERROR(ret);
    }
    නම් ((ret = pthread_cond_init(&rmq->cond_recv, NULL))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ආපසු AVERROR(ret);
    }
    නම් ((ret = pthread_cond_init(&rmq->cond_send, NULL))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ආපසු AVERROR(ret);
    }
    නම් (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ආපසු AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ආපසු 0;
#නැතහොත්
    *mq = NULL;
    ආපසු AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           void (*free_func)(void *msg))
{
#නම් HAVE_THREADS
    mq->free_func = free_func;
#endif
}

void av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#නම් HAVE_THREADS
    නම් (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

පූර්ණ_සංඛ්‍යා av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#නම් HAVE_THREADS
    පූර්ණ_සංඛ්‍යා ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ආපසු ret;
#නැතහොත්
    ආපසු AVERROR(ENOSYS);
#endif
}

#නම් HAVE_THREADS

static පූර්ණ_සංඛ්‍යා av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    අතරතුර (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        නම් ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ආපසු AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    නම් (mq->err_send)
        ආපසු mq->err_send;
    av_fifo_write(mq->fifo, msg, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    අතරතුර (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        නම් ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ආපසු AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    නම් (!av_fifo_can_read(mq->fifo))
        ආපසු mq->err_recv;
    av_fifo_read(mq->fifo, msg, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ආපසු 0;
}

#endif /* HAVE_THREADS */

පූර්ණ_සංඛ්‍යා av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#නම් HAVE_THREADS
    පූර්ණ_සංඛ්‍යා ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ආපසු ret;
#නැතහොත්
    ආපසු AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

පූර්ණ_සංඛ්‍යා av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#නම් HAVE_THREADS
    පූර්ණ_සංඛ්‍යා ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ආපසු ret;
#නැතහොත්
    ආපසු AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          පූර්ණ_සංඛ්‍යා err)
{
#නම් HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          පූර්ණ_සංඛ්‍යා err)
{
#නම් HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#නම් HAVE_THREADS
static පූර්ණ_සංඛ්‍යා free_func_wrap(void *arg, void *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *msg = buf;
    සඳහා (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(msg + i * mq->elsize);
    ආපසු 0;
}
#endif

void av_thread_message_flush(AVThreadMessageQueue *mq)
{
#නම් HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    නම් (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
