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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "fifo.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "threadmessage.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

ಸಂರಚನಾ AVThreadMessageQueue {
#ಯದಿ HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ಪೂರ್ಣಾಙ್ಕ err_send;
    ಪೂರ್ಣಾಙ್ಕ err_recv;
    unsigned elsize;
    ಶೂನ್ಯ (*free_func)(ಶೂನ್ಯ *ಸಂದೇಶ);
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ dummy;
#endif
};

ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#ಯದಿ HAVE_THREADS
    AVThreadMessageQueue *rmq;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (nelem > INT_MAX / elsize)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಯದಿ (!(rmq = av_mallocz(ಪರಿಮಾಣ(*rmq))))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ಯದಿ ((ret = pthread_mutex_init(&rmq->lock, ರಿಕ್ತ))) {
        av_free(rmq);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
    }
    ಯದಿ ((ret = pthread_cond_init(&rmq->cond_recv, ರಿಕ್ತ))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
    }
    ಯದಿ ((ret = pthread_cond_init(&rmq->cond_send, ರಿಕ್ತ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ret);
    }
    ಯದಿ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ಪ್ರತ್ಯಾಗಮ 0;
#ಅನ್ಯಥಾ
    *mq = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           ಶೂನ್ಯ (*free_func)(ಶೂನ್ಯ *ಸಂದೇಶ))
{
#ಯದಿ HAVE_THREADS
    mq->free_func = free_func;
#endif
}

ಶೂನ್ಯ av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#ಯದಿ HAVE_THREADS
    ಯದಿ (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#ಯದಿ HAVE_THREADS
    ಪೂರ್ಣಾಙ್ಕ ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    ಪ್ರತ್ಯಾಗಮ ret;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
}

#ಯದಿ HAVE_THREADS

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               ಶೂನ್ಯ *ಸಂದೇಶ,
                                               unsigned flags)
{
    ಯಾವತ್ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ಯದಿ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    ಯದಿ (mq->err_send)
        ಪ್ರತ್ಯಾಗಮ mq->err_send;
    av_fifo_write(mq->fifo, ಸಂದೇಶ, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               ಶೂನ್ಯ *ಸಂದೇಶ,
                                               unsigned flags)
{
    ಯಾವತ್ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ಯದಿ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    ಯದಿ (!av_fifo_can_read(mq->fifo))
        ಪ್ರತ್ಯಾಗಮ mq->err_recv;
    av_fifo_read(mq->fifo, ಸಂದೇಶ, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ಪ್ರತ್ಯಾಗಮ 0;
}

#endif /* HAVE_THREADS */

ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 ಶೂನ್ಯ *ಸಂದೇಶ,
                                 unsigned flags)
{
#ಯದಿ HAVE_THREADS
    ಪೂರ್ಣಾಙ್ಕ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, ಸಂದೇಶ, flags);
    pthread_mutex_unlock(&mq->lock);
    ಪ್ರತ್ಯಾಗಮ ret;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ಪೂರ್ಣಾಙ್ಕ av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 ಶೂನ್ಯ *ಸಂದೇಶ,
                                 unsigned flags)
{
#ಯದಿ HAVE_THREADS
    ಪೂರ್ಣಾಙ್ಕ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, ಸಂದೇಶ, flags);
    pthread_mutex_unlock(&mq->lock);
    ಪ್ರತ್ಯಾಗಮ ret;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          ಪೂರ್ಣಾಙ್ಕ err)
{
#ಯದಿ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          ಪೂರ್ಣಾಙ್ಕ err)
{
#ಯದಿ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#ಯದಿ HAVE_THREADS
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ free_func_wrap(ಶೂನ್ಯ *arg, ಶೂನ್ಯ *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *ಸಂದೇಶ = buf;
    ಪ್ರತಿ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(ಸಂದೇಶ + i * mq->elsize);
    ಪ್ರತ್ಯಾಗಮ 0;
}
#endif

ಶೂನ್ಯ av_thread_message_flush(AVThreadMessageQueue *mq)
{
#ಯದಿ HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    ಯದಿ (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
