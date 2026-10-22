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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "threadmessage.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

ਬਣਤਰ AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ {
#ਜੇ HAVE_ਧਾਗੇ
    AVFifo *fifo;
    pthread_mutex_t ਤਾਲਾ;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    ਪੂਰਨ err_send;
    ਪੂਰਨ err_recv;
    ਬਿਨਾਨਿਸ਼ਾਨੀ elsize;
    ਖਾਲੀ (*free_func)(ਖਾਲੀ *ਸੁਨੇਹਾ);
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ dummy;
#ਜੇ_ਅੰਤ
};

ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_alloc(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ **mq,
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ nelem,
                                  ਬਿਨਾਨਿਸ਼ਾਨੀ elsize)
{
#ਜੇ HAVE_ਧਾਗੇ
    AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *rmq;
    ਪੂਰਨ ret = 0;

    ਜੇ (nelem > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / elsize)
        ਵਾਪਸ AVERROR(EINVAL);
    ਜੇ (!(rmq = av_mallocz(ਆਕਾਰ(*rmq))))
        ਵਾਪਸ AVERROR(ENOMEM);
    ਜੇ ((ret = pthread_mutex_init(&rmq->ਤਾਲਾ, ਨਿਰਾ))) {
        av_free(rmq);
        ਵਾਪਸ AVERROR(ret);
    }
    ਜੇ ((ret = pthread_cond_init(&rmq->cond_recv, ਨਿਰਾ))) {
        pthread_mutex_destroy(&rmq->ਤਾਲਾ);
        av_free(rmq);
        ਵਾਪਸ AVERROR(ret);
    }
    ਜੇ ((ret = pthread_cond_init(&rmq->cond_send, ਨਿਰਾ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->ਤਾਲਾ);
        av_free(rmq);
        ਵਾਪਸ AVERROR(ret);
    }
    ਜੇ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->ਤਾਲਾ);
        av_free(rmq);
        ਵਾਪਸ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    ਵਾਪਸ 0;
#ਨਹੀਂਤਾਂ
    *mq = ਨਿਰਾ;
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}

ਖਾਲੀ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_ਸੈੱਟ_free_func(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                           ਖਾਲੀ (*free_func)(ਖਾਲੀ *ਸੁਨੇਹਾ))
{
#ਜੇ HAVE_ਧਾਗੇ
    mq->free_func = free_func;
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_free(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ **mq)
{
#ਜੇ HAVE_ਧਾਗੇ
    ਜੇ (*mq) {
        av_thread_ਸੁਨੇਹਾ_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->ਤਾਲਾ);
        av_freep(mq);
    }
#ਜੇ_ਅੰਤ
}

ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_nb_elems(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq)
{
#ਜੇ HAVE_ਧਾਗੇ
    ਪੂਰਨ ret;
    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
    ਵਾਪਸ ret;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
}

#ਜੇ HAVE_ਧਾਗੇ

ਸਥਿਰ ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_send_locked(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                               ਖਾਲੀ *ਸੁਨੇਹਾ,
                                               ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਜਦੋਂ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ਜੇ ((flags & AV_THREAD_ਸੁਨੇਹਾ_NONBLOCK))
            ਵਾਪਸ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->ਤਾਲਾ);
    }
    ਜੇ (mq->err_send)
        ਵਾਪਸ mq->err_send;
    av_fifo_write(mq->fifo, ਸੁਨੇਹਾ, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_recv_locked(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                               ਖਾਲੀ *ਸੁਨੇਹਾ,
                                               ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਜਦੋਂ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ਜੇ ((flags & AV_THREAD_ਸੁਨੇਹਾ_NONBLOCK))
            ਵਾਪਸ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->ਤਾਲਾ);
    }
    ਜੇ (!av_fifo_can_read(mq->fifo))
        ਵਾਪਸ mq->err_recv;
    av_fifo_read(mq->fifo, ਸੁਨੇਹਾ, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ /* HAVE_THREADS */

ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_send(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                 ਖਾਲੀ *ਸੁਨੇਹਾ,
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
#ਜੇ HAVE_ਧਾਗੇ
    ਪੂਰਨ ret;

    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    ret = av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_send_locked(mq, ਸੁਨੇਹਾ, flags);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
    ਵਾਪਸ ret;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}

ਪੂਰਨ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_recv(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                 ਖਾਲੀ *ਸੁਨੇਹਾ,
                                 ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
#ਜੇ HAVE_ਧਾਗੇ
    ਪੂਰਨ ret;

    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    ret = av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_recv_locked(mq, ਸੁਨੇਹਾ, flags);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
    ਵਾਪਸ ret;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}

ਖਾਲੀ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_ਸੈੱਟ_err_send(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                          ਪੂਰਨ err)
{
#ਜੇ HAVE_ਧਾਗੇ
    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    mq->err_send = err;
    pthread_cond_ਪ੍ਰਸਾਰਣ(&mq->cond_send);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}

ਖਾਲੀ av_thread_ਸੁਨੇਹਾ_ਕਤਾਰ_ਸੈੱਟ_err_recv(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq,
                                          ਪੂਰਨ err)
{
#ਜੇ HAVE_ਧਾਗੇ
    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    mq->err_recv = err;
    pthread_cond_ਪ੍ਰਸਾਰਣ(&mq->cond_recv);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}

#ਜੇ HAVE_ਧਾਗੇ
ਸਥਿਰ ਪੂਰਨ free_func_wrap(ਖਾਲੀ *arg, ਖਾਲੀ *buf, size_t *nb_elems)
{
    AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq = arg;
    uint8_t *ਸੁਨੇਹਾ = buf;
    ਲਈ (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(ਸੁਨੇਹਾ + i * mq->elsize);
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

ਖਾਲੀ av_thread_ਸੁਨੇਹਾ_flush(AVThread_ਸੁਨੇਹਾ_ਕਤਾਰ *mq)
{
#ਜੇ HAVE_ਧਾਗੇ
    size_t ਵਰਤਿਆ;

    pthread_mutex_ਤਾਲਾ(&mq->ਤਾਲਾ);
    ਵਰਤਿਆ = av_fifo_can_read(mq->fifo);
    ਜੇ (mq->free_func)
        av_fifo_read_ਮੰਜ਼ਿਲ_cb(mq->fifo, free_func_wrap, mq, &ਵਰਤਿਆ);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_ਪ੍ਰਸਾਰਣ(&mq->cond_send);
    pthread_mutex_unlock(&mq->ਤਾਲਾ);
#ਜੇ_ਅੰਤ /* HAVE_THREADS */
}
