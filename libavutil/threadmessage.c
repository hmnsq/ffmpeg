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

ರಚನೆ AVThread_ಸಂದೇಶ_ಸರತಿ {
#ಆದರೆ HAVE_ಎಳೆಗಳು
    AVFifo *fifo;
    pthread_mutex_t ಬೀಗ_2;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ಪೂರ್ಣಾಂಕ err_send;
    ಪೂರ್ಣಾಂಕ err_recv;
    ಚಿಹ್ನೆರಹಿತ elsize;
    ಶೂನ್ಯ (*free_func)(ಶೂನ್ಯ *ಸಂದೇಶ);
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ dummy;
#ಆದರೆ_ಅಂತ್ಯ
};

ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_alloc(AVThread_ಸಂದೇಶ_ಸರತಿ **mq,
                                  ಚಿಹ್ನೆರಹಿತ nelem,
                                  ಚಿಹ್ನೆರಹಿತ elsize)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    AVThread_ಸಂದೇಶ_ಸರತಿ *rmq;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (nelem > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / elsize)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಆದರೆ (!(rmq = av_mallocz(ಗಾತ್ರ(*rmq))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಆದರೆ ((ret = pthread_mutex_init(&rmq->ಬೀಗ_2, ಖಾಲಿ))) {
        av_free(rmq);
        ಹಿಂತಿರುಗಿ AVERROR(ret);
    }
    ಆದರೆ ((ret = pthread_cond_init(&rmq->cond_recv, ಖಾಲಿ))) {
        pthread_mutex_destroy(&rmq->ಬೀಗ_2);
        av_free(rmq);
        ಹಿಂತಿರುಗಿ AVERROR(ret);
    }
    ಆದರೆ ((ret = pthread_cond_init(&rmq->cond_send, ಖಾಲಿ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->ಬೀಗ_2);
        av_free(rmq);
        ಹಿಂತಿರುಗಿ AVERROR(ret);
    }
    ಆದರೆ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->ಬೀಗ_2);
        av_free(rmq);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ಹಿಂತಿರುಗಿ 0;
#ಇಲ್ಲದಿದ್ದರೆ
    *mq = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_ಸಂದೇಶ_ಸರತಿ_ಗಣ_free_func(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                           ಶೂನ್ಯ (*free_func)(ಶೂನ್ಯ *ಸಂದೇಶ))
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    mq->free_func = free_func;
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ av_thread_ಸಂದೇಶ_ಸರತಿ_free(AVThread_ಸಂದೇಶ_ಸರತಿ **mq)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    ಆದರೆ (*mq) {
        av_thread_ಸಂದೇಶ_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->ಬೀಗ_2);
        av_freep(mq);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_nb_elems(AVThread_ಸಂದೇಶ_ಸರತಿ *mq)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    ಪೂರ್ಣಾಂಕ ret;
    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
    ಹಿಂತಿರುಗಿ ret;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ HAVE_ಎಳೆಗಳು

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_send_locked(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                               ಶೂನ್ಯ *ಸಂದೇಶ,
                                               ಚಿಹ್ನೆರಹಿತ flags)
{
    ಆಗ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ಆದರೆ ((flags & AV_THREAD_ಸಂದೇಶ_NONBLOCK))
            ಹಿಂತಿರುಗಿ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->ಬೀಗ_2);
    }
    ಆದರೆ (mq->err_send)
        ಹಿಂತಿರುಗಿ mq->err_send;
    av_fifo_write(mq->fifo, ಸಂದೇಶ, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_recv_locked(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                               ಶೂನ್ಯ *ಸಂದೇಶ,
                                               ಚಿಹ್ನೆರಹಿತ flags)
{
    ಆಗ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ಆದರೆ ((flags & AV_THREAD_ಸಂದೇಶ_NONBLOCK))
            ಹಿಂತಿರುಗಿ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->ಬೀಗ_2);
    }
    ಆದರೆ (!av_fifo_can_read(mq->fifo))
        ಹಿಂತಿರುಗಿ mq->err_recv;
    av_fifo_read(mq->fifo, ಸಂದೇಶ, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */

ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_send(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                 ಶೂನ್ಯ *ಸಂದೇಶ,
                                 ಚಿಹ್ನೆರಹಿತ flags)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    ಪೂರ್ಣಾಂಕ ret;

    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    ret = av_thread_ಸಂದೇಶ_ಸರತಿ_send_locked(mq, ಸಂದೇಶ, flags);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
    ಹಿಂತಿರುಗಿ ret;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}

ಪೂರ್ಣಾಂಕ av_thread_ಸಂದೇಶ_ಸರತಿ_recv(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                 ಶೂನ್ಯ *ಸಂದೇಶ,
                                 ಚಿಹ್ನೆರಹಿತ flags)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    ಪೂರ್ಣಾಂಕ ret;

    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    ret = av_thread_ಸಂದೇಶ_ಸರತಿ_recv_locked(mq, ಸಂದೇಶ, flags);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
    ಹಿಂತಿರುಗಿ ret;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_ಸಂದೇಶ_ಸರತಿ_ಗಣ_err_send(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                          ಪೂರ್ಣಾಂಕ err)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    mq->err_send = err;
    pthread_cond_ಪ್ರಸಾರ(&mq->cond_send);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}

ಶೂನ್ಯ av_thread_ಸಂದೇಶ_ಸರತಿ_ಗಣ_err_recv(AVThread_ಸಂದೇಶ_ಸರತಿ *mq,
                                          ಪೂರ್ಣಾಂಕ err)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    mq->err_recv = err;
    pthread_cond_ಪ್ರಸಾರ(&mq->cond_recv);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}

#ಆದರೆ HAVE_ಎಳೆಗಳು
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ free_func_wrap(ಶೂನ್ಯ *arg, ಶೂನ್ಯ *buf, size_t *nb_elems)
{
    AVThread_ಸಂದೇಶ_ಸರತಿ *mq = arg;
    uint8_t *ಸಂದೇಶ = buf;
    ಗಾಗಿ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(ಸಂದೇಶ + i * mq->elsize);
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ av_thread_ಸಂದೇಶ_flush(AVThread_ಸಂದೇಶ_ಸರತಿ *mq)
{
#ಆದರೆ HAVE_ಎಳೆಗಳು
    size_t ಬಳಸಿದ;

    pthread_mutex_ಬೀಗ(&mq->ಬೀಗ_2);
    ಬಳಸಿದ = av_fifo_can_read(mq->fifo);
    ಆದರೆ (mq->free_func)
        av_fifo_read_ಗಮ್ಯ_cb(mq->fifo, free_func_wrap, mq, &ಬಳಸಿದ);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_ಪ್ರಸಾರ(&mq->cond_send);
    pthread_mutex_unlock(&mq->ಬೀಗ_2);
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_THREADS */
}
