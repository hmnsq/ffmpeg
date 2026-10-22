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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stddef.h>

#அந்தர்பாவ "error.h"
#அந்தர்பாவ "fifo.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "threadmessage.h"
#அந்தர்பாவ "thread.h"

கட்டமைப்பு AVThreadMessageQueue {
#எனில் HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    முழு err_send;
    முழு err_recv;
    unsigned elsize;
    வெறுமை (*free_func)(வெறுமை *செய்தி);
#இல்லையெனில்
    முழு dummy;
#endif
};

முழு av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#எனில் HAVE_THREADS
    AVThreadMessageQueue *rmq;
    முழு ret = 0;

    எனில் (nelem > INT_MAX / elsize)
        திரும்பு AVERROR(EINVAL);
    எனில் (!(rmq = av_mallocz(அளவு(*rmq))))
        திரும்பு AVERROR(ENOMEM);
    எனில் ((ret = pthread_mutex_init(&rmq->lock, வெற்று))) {
        av_free(rmq);
        திரும்பு AVERROR(ret);
    }
    எனில் ((ret = pthread_cond_init(&rmq->cond_recv, வெற்று))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        திரும்பு AVERROR(ret);
    }
    எனில் ((ret = pthread_cond_init(&rmq->cond_send, வெற்று))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        திரும்பு AVERROR(ret);
    }
    எனில் (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        திரும்பு AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    திரும்பு 0;
#இல்லையெனில்
    *mq = வெற்று;
    திரும்பு AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

வெறுமை av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           வெறுமை (*free_func)(வெறுமை *செய்தி))
{
#எனில் HAVE_THREADS
    mq->free_func = free_func;
#endif
}

வெறுமை av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#எனில் HAVE_THREADS
    எனில் (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

முழு av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#எனில் HAVE_THREADS
    முழு ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    திரும்பு ret;
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif
}

#எனில் HAVE_THREADS

நிலையான முழு av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               வெறுமை *செய்தி,
                                               unsigned flags)
{
    போது (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        எனில் ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            திரும்பு AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    எனில் (mq->err_send)
        திரும்பு mq->err_send;
    av_fifo_write(mq->fifo, செய்தி, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    திரும்பு 0;
}

நிலையான முழு av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               வெறுமை *செய்தி,
                                               unsigned flags)
{
    போது (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        எனில் ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            திரும்பு AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    எனில் (!av_fifo_can_read(mq->fifo))
        திரும்பு mq->err_recv;
    av_fifo_read(mq->fifo, செய்தி, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    திரும்பு 0;
}

#endif /* HAVE_THREADS */

முழு av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 வெறுமை *செய்தி,
                                 unsigned flags)
{
#எனில் HAVE_THREADS
    முழு ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, செய்தி, flags);
    pthread_mutex_unlock(&mq->lock);
    திரும்பு ret;
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

முழு av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 வெறுமை *செய்தி,
                                 unsigned flags)
{
#எனில் HAVE_THREADS
    முழு ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, செய்தி, flags);
    pthread_mutex_unlock(&mq->lock);
    திரும்பு ret;
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

வெறுமை av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          முழு err)
{
#எனில் HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

வெறுமை av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          முழு err)
{
#எனில் HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#எனில் HAVE_THREADS
நிலையான முழு free_func_wrap(வெறுமை *arg, வெறுமை *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *செய்தி = buf;
    க்கு (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(செய்தி + i * mq->elsize);
    திரும்பு 0;
}
#endif

வெறுமை av_thread_message_flush(AVThreadMessageQueue *mq)
{
#எனில் HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    எனில் (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
