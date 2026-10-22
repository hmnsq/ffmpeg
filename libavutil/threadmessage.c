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
#ຖ້າ HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ຈຳນວນເຕັມ err_send;
    ຈຳນວນເຕັມ err_recv;
    unsigned elsize;
    void (*free_func)(void *msg);
#ບໍ່ດັ່ງນັ້ນ
    ຈຳນວນເຕັມ dummy;
#endif
};

ຈຳນວນເຕັມ av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#ຖ້າ HAVE_THREADS
    AVThreadMessageQueue *rmq;
    ຈຳນວນເຕັມ ret = 0;

    ຖ້າ (nelem > INT_MAX / elsize)
        ສົ່ງຄືນ AVERROR(EINVAL);
    ຖ້າ (!(rmq = av_mallocz(parimaa_na(*rmq))))
        ສົ່ງຄືນ AVERROR(ENOMEM);
    ຖ້າ ((ret = pthread_mutex_init(&rmq->lock, NULL))) {
        av_free(rmq);
        ສົ່ງຄືນ AVERROR(ret);
    }
    ຖ້າ ((ret = pthread_cond_init(&rmq->cond_recv, NULL))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ສົ່ງຄືນ AVERROR(ret);
    }
    ຖ້າ ((ret = pthread_cond_init(&rmq->cond_send, NULL))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ສົ່ງຄືນ AVERROR(ret);
    }
    ຖ້າ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ສົ່ງຄືນ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ສົ່ງຄືນ 0;
#ບໍ່ດັ່ງນັ້ນ
    *mq = NULL;
    ສົ່ງຄືນ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           void (*free_func)(void *msg))
{
#ຖ້າ HAVE_THREADS
    mq->free_func = free_func;
#endif
}

void av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#ຖ້າ HAVE_THREADS
    ຖ້າ (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

ຈຳນວນເຕັມ av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#ຖ້າ HAVE_THREADS
    ຈຳນວນເຕັມ ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ສົ່ງຄືນ ret;
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ AVERROR(ENOSYS);
#endif
}

#ຖ້າ HAVE_THREADS

static ຈຳນວນເຕັມ av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    ໃນຂະນະທີ່ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ຖ້າ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ສົ່ງຄືນ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    ຖ້າ (mq->err_send)
        ສົ່ງຄືນ mq->err_send;
    av_fifo_write(mq->fifo, msg, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    ໃນຂະນະທີ່ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ຖ້າ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ສົ່ງຄືນ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    ຖ້າ (!av_fifo_can_read(mq->fifo))
        ສົ່ງຄືນ mq->err_recv;
    av_fifo_read(mq->fifo, msg, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ສົ່ງຄືນ 0;
}

#endif /* HAVE_THREADS */

ຈຳນວນເຕັມ av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#ຖ້າ HAVE_THREADS
    ຈຳນວນເຕັມ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ສົ່ງຄືນ ret;
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ຈຳນວນເຕັມ av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#ຖ້າ HAVE_THREADS
    ຈຳນວນເຕັມ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ສົ່ງຄືນ ret;
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          ຈຳນວນເຕັມ err)
{
#ຖ້າ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          ຈຳນວນເຕັມ err)
{
#ຖ້າ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#ຖ້າ HAVE_THREADS
static ຈຳນວນເຕັມ free_func_wrap(void *arg, void *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *msg = buf;
    ສຳລັບ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(msg + i * mq->elsize);
    ສົ່ງຄືນ 0;
}
#endif

void av_thread_message_flush(AVThreadMessageQueue *mq)
{
#ຖ້າ HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    ຖ້າ (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
