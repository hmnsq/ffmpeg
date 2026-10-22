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
#אם HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحيح err_send;
    صحيح err_recv;
    unsigned elsize;
    فراغ (*free_func)(فراغ *msg);
#אחרת
    صحيح dummy;
#endif
};

صحيح av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#אם HAVE_THREADS
    AVThreadMessageQueue *rmq;
    صحيح ret = 0;

    אם (nelem > INT_MAX / elsize)
        החזר AVERROR(EINVAL);
    אם (!(rmq = av_mallocz(حجم(*rmq))))
        החזר AVERROR(ENOMEM);
    אם ((ret = pthread_mutex_init(&rmq->lock, عدم))) {
        av_free(rmq);
        החזר AVERROR(ret);
    }
    אם ((ret = pthread_cond_init(&rmq->cond_recv, عدم))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        החזר AVERROR(ret);
    }
    אם ((ret = pthread_cond_init(&rmq->cond_send, عدم))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        החזר AVERROR(ret);
    }
    אם (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        החזר AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    החזר 0;
#אחרת
    *mq = عدم;
    החזר AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           فراغ (*free_func)(فراغ *msg))
{
#אם HAVE_THREADS
    mq->free_func = free_func;
#endif
}

فراغ av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#אם HAVE_THREADS
    אם (*mq) {
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
#אם HAVE_THREADS
    صحيح ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    החזר ret;
#אחרת
    החזר AVERROR(ENOSYS);
#endif
}

#אם HAVE_THREADS

ساكن صحيح av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               فراغ *msg,
                                               unsigned flags)
{
    כלעוד (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        אם ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            החזר AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    אם (mq->err_send)
        החזר mq->err_send;
    av_fifo_write(mq->fifo, msg, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    החזר 0;
}

ساكن صحيح av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               فراغ *msg,
                                               unsigned flags)
{
    כלעוד (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        אם ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            החזר AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    אם (!av_fifo_can_read(mq->fifo))
        החזר mq->err_recv;
    av_fifo_read(mq->fifo, msg, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    החזר 0;
}

#endif /* HAVE_THREADS */

صحيح av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 فراغ *msg,
                                 unsigned flags)
{
#אם HAVE_THREADS
    صحيح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    החזר ret;
#אחרת
    החזר AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

صحيح av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 فراغ *msg,
                                 unsigned flags)
{
#אם HAVE_THREADS
    صحيح ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, msg, flags);
    pthread_mutex_unlock(&mq->lock);
    החזר ret;
#אחרת
    החזר AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          صحيح err)
{
#אם HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

فراغ av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          صحيح err)
{
#אם HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#אם HAVE_THREADS
ساكن صحيح free_func_wrap(فراغ *arg, فراغ *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *msg = buf;
    עבור (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(msg + i * mq->elsize);
    החזר 0;
}
#endif

فراغ av_thread_message_flush(AVThreadMessageQueue *mq)
{
#אם HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    אם (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
