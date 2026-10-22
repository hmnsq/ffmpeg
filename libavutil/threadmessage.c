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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stddef.h>

#अन्तर्भाव "error.h"
#अन्तर्भाव "fifo.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "threadmessage.h"
#अन्तर्भाव "thread.h"

संरचना AVThreadMessageQueue {
#सचे HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    पूर्णाङ्क err_send;
    पूर्णाङ्क err_recv;
    unsigned elsize;
    शून्य (*free_func)(शून्य *सन्देशः);
#अञ्ञथा
    पूर्णाङ्क dummy;
#endif
};

पूर्णाङ्क av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#सचे HAVE_THREADS
    AVThreadMessageQueue *rmq;
    पूर्णाङ्क ret = 0;

    सचे (nelem > INT_MAX / elsize)
        पटिनिवत्त AVERROR(EINVAL);
    सचे (!(rmq = av_mallocz(परिमाण(*rmq))))
        पटिनिवत्त AVERROR(ENOMEM);
    सचे ((ret = pthread_mutex_init(&rmq->lock, रिक्त))) {
        av_free(rmq);
        पटिनिवत्त AVERROR(ret);
    }
    सचे ((ret = pthread_cond_init(&rmq->cond_recv, रिक्त))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        पटिनिवत्त AVERROR(ret);
    }
    सचे ((ret = pthread_cond_init(&rmq->cond_send, रिक्त))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        पटिनिवत्त AVERROR(ret);
    }
    सचे (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        पटिनिवत्त AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    पटिनिवत्त 0;
#अञ्ञथा
    *mq = रिक्त;
    पटिनिवत्त AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           शून्य (*free_func)(शून्य *सन्देशः))
{
#सचे HAVE_THREADS
    mq->free_func = free_func;
#endif
}

शून्य av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#सचे HAVE_THREADS
    सचे (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

पूर्णाङ्क av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#सचे HAVE_THREADS
    पूर्णाङ्क ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    पटिनिवत्त ret;
#अञ्ञथा
    पटिनिवत्त AVERROR(ENOSYS);
#endif
}

#सचे HAVE_THREADS

स्थिर पूर्णाङ्क av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               शून्य *सन्देशः,
                                               unsigned flags)
{
    याव (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        सचे ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            पटिनिवत्त AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    सचे (mq->err_send)
        पटिनिवत्त mq->err_send;
    av_fifo_write(mq->fifo, सन्देशः, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               शून्य *सन्देशः,
                                               unsigned flags)
{
    याव (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        सचे ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            पटिनिवत्त AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    सचे (!av_fifo_can_read(mq->fifo))
        पटिनिवत्त mq->err_recv;
    av_fifo_read(mq->fifo, सन्देशः, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    पटिनिवत्त 0;
}

#endif /* HAVE_THREADS */

पूर्णाङ्क av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 शून्य *सन्देशः,
                                 unsigned flags)
{
#सचे HAVE_THREADS
    पूर्णाङ्क ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, सन्देशः, flags);
    pthread_mutex_unlock(&mq->lock);
    पटिनिवत्त ret;
#अञ्ञथा
    पटिनिवत्त AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

पूर्णाङ्क av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 शून्य *सन्देशः,
                                 unsigned flags)
{
#सचे HAVE_THREADS
    पूर्णाङ्क ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, सन्देशः, flags);
    pthread_mutex_unlock(&mq->lock);
    पटिनिवत्त ret;
#अञ्ञथा
    पटिनिवत्त AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          पूर्णाङ्क err)
{
#सचे HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          पूर्णाङ्क err)
{
#सचे HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#सचे HAVE_THREADS
स्थिर पूर्णाङ्क free_func_wrap(शून्य *arg, शून्य *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *सन्देशः = buf;
    अत्थाय (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(सन्देशः + i * mq->elsize);
    पटिनिवत्त 0;
}
#endif

शून्य av_thread_message_flush(AVThreadMessageQueue *mq)
{
#सचे HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    सचे (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
