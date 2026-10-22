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

#অন্তর্ভাৱ <limits.h>
#অন্তর্ভাৱ <stddef.h>

#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "fifo.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "threadmessage.h"
#অন্তর্ভাৱ "thread.h"

সংরচনা AVThreadMessageQueue {
#যদি HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    পূর্ণাঙ্ক err_send;
    পূর্ণাঙ্ক err_recv;
    unsigned elsize;
    শূন্য (*free_func)(শূন্য *বাৰ্তা);
#অন্যথা
    পূর্ণাঙ্ক dummy;
#endif
};

পূর্ণাঙ্ক av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#যদি HAVE_THREADS
    AVThreadMessageQueue *rmq;
    পূর্ণাঙ্ক ret = 0;

    যদি (nelem > INT_MAX / elsize)
        ঘূৰাই AVERROR(EINVAL);
    যদি (!(rmq = av_mallocz(পরিমাণ(*rmq))))
        ঘূৰাই AVERROR(ENOMEM);
    যদি ((ret = pthread_mutex_init(&rmq->lock, রিক্ত))) {
        av_free(rmq);
        ঘূৰাই AVERROR(ret);
    }
    যদি ((ret = pthread_cond_init(&rmq->cond_recv, রিক্ত))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ঘূৰাই AVERROR(ret);
    }
    যদি ((ret = pthread_cond_init(&rmq->cond_send, রিক্ত))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ঘূৰাই AVERROR(ret);
    }
    যদি (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ঘূৰাই AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ঘূৰাই 0;
#অন্যথা
    *mq = রিক্ত;
    ঘূৰাই AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

শূন্য av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           শূন্য (*free_func)(শূন্য *বাৰ্তা))
{
#যদি HAVE_THREADS
    mq->free_func = free_func;
#endif
}

শূন্য av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#যদি HAVE_THREADS
    যদি (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

পূর্ণাঙ্ক av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#যদি HAVE_THREADS
    পূর্ণাঙ্ক ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ঘূৰাই ret;
#অন্যথা
    ঘূৰাই AVERROR(ENOSYS);
#endif
}

#যদি HAVE_THREADS

স্থির পূর্ণাঙ্ক av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               শূন্য *বাৰ্তা,
                                               unsigned flags)
{
    যেতিয়ালৈ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        যদি ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ঘূৰাই AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    যদি (mq->err_send)
        ঘূৰাই mq->err_send;
    av_fifo_write(mq->fifo, বাৰ্তা, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               শূন্য *বাৰ্তা,
                                               unsigned flags)
{
    যেতিয়ালৈ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        যদি ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ঘূৰাই AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    যদি (!av_fifo_can_read(mq->fifo))
        ঘূৰাই mq->err_recv;
    av_fifo_read(mq->fifo, বাৰ্তা, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ঘূৰাই 0;
}

#endif /* HAVE_THREADS */

পূর্ণাঙ্ক av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 শূন্য *বাৰ্তা,
                                 unsigned flags)
{
#যদি HAVE_THREADS
    পূর্ণাঙ্ক ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, বাৰ্তা, flags);
    pthread_mutex_unlock(&mq->lock);
    ঘূৰাই ret;
#অন্যথা
    ঘূৰাই AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

পূর্ণাঙ্ক av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 শূন্য *বাৰ্তা,
                                 unsigned flags)
{
#যদি HAVE_THREADS
    পূর্ণাঙ্ক ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, বাৰ্তা, flags);
    pthread_mutex_unlock(&mq->lock);
    ঘূৰাই ret;
#অন্যথা
    ঘূৰাই AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

শূন্য av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          পূর্ণাঙ্ক err)
{
#যদি HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

শূন্য av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          পূর্ণাঙ্ক err)
{
#যদি HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#যদি HAVE_THREADS
স্থির পূর্ণাঙ্ক free_func_wrap(শূন্য *arg, শূন্য *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *বাৰ্তা = buf;
    বাবে (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(বাৰ্তা + i * mq->elsize);
    ঘূৰাই 0;
}
#endif

শূন্য av_thread_message_flush(AVThreadMessageQueue *mq)
{
#যদি HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    যদি (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
