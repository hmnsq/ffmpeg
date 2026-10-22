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

#समावेश <limits.h>
#समावेश <stddef.h>

#समावेश "error.h"
#समावेश "fifo.h"
#समावेश "mem.h"
#समावेश "threadmessage.h"
#समावेश "thread.h"

काष्ठा AVThreadMessageQueue {
#अगर HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    पूर्णांक err_send;
    पूर्णांक err_recv;
    अचिन्हित elsize;
    व्योम (*free_func)(व्योम *संदेश);
#अन्यथा
    पूर्णांक dummy;
#पूर्ण_अगर
};

पूर्णांक av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  अचिन्हित nelem,
                                  अचिन्हित elsize)
{
#अगर HAVE_THREADS
    AVThreadMessageQueue *rmq;
    पूर्णांक ret = 0;

    अगर (nelem > पूर्णांक_उच्च / elsize)
        वापस AVERROR(EINVAL);
    अगर (!(rmq = av_mallocz(माप(*rmq))))
        वापस AVERROR(ENOMEM);
    अगर ((ret = pthread_mutex_init(&rmq->lock, शून्य))) {
        av_free(rmq);
        वापस AVERROR(ret);
    }
    अगर ((ret = pthread_cond_init(&rmq->cond_recv, शून्य))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        वापस AVERROR(ret);
    }
    अगर ((ret = pthread_cond_init(&rmq->cond_send, शून्य))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        वापस AVERROR(ret);
    }
    अगर (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        वापस AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    वापस 0;
#अन्यथा
    *mq = शून्य;
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर /* HAVE_THREADS */
}

व्योम av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           व्योम (*free_func)(व्योम *संदेश))
{
#अगर HAVE_THREADS
    mq->free_func = free_func;
#पूर्ण_अगर
}

व्योम av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#अगर HAVE_THREADS
    अगर (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#पूर्ण_अगर
}

पूर्णांक av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#अगर HAVE_THREADS
    पूर्णांक ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    वापस ret;
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर
}

#अगर HAVE_THREADS

अटल पूर्णांक av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               व्योम *संदेश,
                                               अचिन्हित flags)
{
    जबतक (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        अगर ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            वापस AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    अगर (mq->err_send)
        वापस mq->err_send;
    av_fifo_write(mq->fifo, संदेश, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    वापस 0;
}

अटल पूर्णांक av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               व्योम *संदेश,
                                               अचिन्हित flags)
{
    जबतक (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        अगर ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            वापस AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    अगर (!av_fifo_can_read(mq->fifo))
        वापस mq->err_recv;
    av_fifo_read(mq->fifo, संदेश, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    वापस 0;
}

#पूर्ण_अगर /* HAVE_THREADS */

पूर्णांक av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 व्योम *संदेश,
                                 अचिन्हित flags)
{
#अगर HAVE_THREADS
    पूर्णांक ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, संदेश, flags);
    pthread_mutex_unlock(&mq->lock);
    वापस ret;
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर /* HAVE_THREADS */
}

पूर्णांक av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 व्योम *संदेश,
                                 अचिन्हित flags)
{
#अगर HAVE_THREADS
    पूर्णांक ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, संदेश, flags);
    pthread_mutex_unlock(&mq->lock);
    वापस ret;
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर /* HAVE_THREADS */
}

व्योम av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          पूर्णांक err)
{
#अगर HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#पूर्ण_अगर /* HAVE_THREADS */
}

व्योम av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          पूर्णांक err)
{
#अगर HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#पूर्ण_अगर /* HAVE_THREADS */
}

#अगर HAVE_THREADS
अटल पूर्णांक free_func_wrap(व्योम *arg, व्योम *buf, माप_प्रकार *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *संदेश = buf;
    क्रम (माप_प्रकार i = 0; i < *nb_elems; i++)
        mq->free_func(संदेश + i * mq->elsize);
    वापस 0;
}
#पूर्ण_अगर

व्योम av_thread_message_flush(AVThreadMessageQueue *mq)
{
#अगर HAVE_THREADS
    माप_प्रकार used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    अगर (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#पूर्ण_अगर /* HAVE_THREADS */
}
