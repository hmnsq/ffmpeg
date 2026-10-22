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
#ប្រសិនបើ HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ចំនួនគត់ err_send;
    ចំនួនគត់ err_recv;
    unsigned elsize;
    void (*free_func)(void *msg);
#បើមិនដូច្នេះ
    ចំនួនគត់ dummy;
#endif
};

ចំនួនគត់ av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#ប្រសិនបើ HAVE_THREADS
    AVThreadMessageQueue *rmq;
    ចំនួនគត់ ret = 0;

    ប្រសិនបើ (nelem > INT_MAX / elsize)
        ត្រឡប់ AVERROR(EINVAL);
    ប្រសិនបើ (!(rmq = av_mallocz(parimaa_na(*rmq))))
        ត្រឡប់ AVERROR(ENOMEM);
    ប្រសិនបើ ((ret = pthread_mutex_init(&rmq->lock, NULL))) {
        av_free(rmq);
        ត្រឡប់ AVERROR(ret);
    }
    ប្រសិនបើ ((ret = pthread_cond_init(&rmq->cond_recv, NULL))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ត្រឡប់ AVERROR(ret);
    }
    ប្រសិនបើ ((ret = pthread_cond_init(&rmq->cond_send, NULL))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ត្រឡប់ AVERROR(ret);
    }
    ប្រសិនបើ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ត្រឡប់ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ត្រឡប់ 0;
#បើមិនដូច្នេះ
    *mq = NULL;
    ត្រឡប់ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           void (*free_func)(void *msg))
{
#ប្រសិនបើ HAVE_THREADS
    mq->free_func = free_func;
#endif
}

void av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#ប្រសិនបើ HAVE_THREADS
    ប្រសិនបើ (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

ចំនួនគត់ av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#ប្រសិនបើ HAVE_THREADS
    ចំនួនគត់ ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ត្រឡប់ ret;
#បើមិនដូច្នេះ
    ត្រឡប់ AVERROR(ENOSYS);
#endif
}

#ប្រសិនបើ HAVE_THREADS

static ចំនួនគត់ av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    ខណៈពេល (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ប្រសិនបើ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ត្រឡប់ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    ប្រសិនបើ (mq->err_send)
        ត្រឡប់ mq->err_send;
    av_fifo_write(mq->fifo, msg, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ត្រឡប់ 0;
}

static ចំនួនគត់ av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               void *msg,
                                               unsigned flags)
{
    ខណៈពេល (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ប្រសិនបើ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ត្រឡប់ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    ប្រសិនបើ (!av_fifo_can_read(mq->fifo))
        ត្រឡប់ mq->err_recv;
    av_fifo_read(mq->fifo, msg, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ត្រឡប់ 0;
}

#endif /* HAVE_THREADS */

ចំនួនគត់ av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#ប្រសិនបើ HAVE_THREADS
    ចំនួនគត់ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ត្រឡប់ ret;
#បើមិនដូច្នេះ
    ត្រឡប់ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ចំនួនគត់ av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 void *msg,
                                 unsigned flags)
{
#ប្រសិនបើ HAVE_THREADS
    ចំនួនគត់ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    ត្រឡប់ ret;
#បើមិនដូច្នេះ
    ត្រឡប់ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          ចំនួនគត់ err)
{
#ប្រសិនបើ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

void av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          ចំនួនគត់ err)
{
#ប្រសិនបើ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#ប្រសិនបើ HAVE_THREADS
static ចំនួនគត់ free_func_wrap(void *arg, void *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *msg = buf;
    សម្រាប់ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(msg + i * mq->elsize);
    ត្រឡប់ 0;
}
#endif

void av_thread_message_flush(AVThreadMessageQueue *mq)
{
#ប្រសិនបើ HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    ប្រសិនបើ (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
