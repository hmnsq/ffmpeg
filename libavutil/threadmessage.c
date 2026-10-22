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
#जर HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    पूर्णांक err_send;
    पूर्णांक err_recv;
    अचिन्हित elsize;
    शून्य (*free_func)(शून्य *संदेश);
#अन्यथा
    पूर्णांक dummy;
#endif
};

पूर्णांक av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  अचिन्हित nelem,
                                  अचिन्हित elsize)
{
#जर HAVE_THREADS
    AVThreadMessageQueue *rmq;
    पूर्णांक ret = 0;

    जर (nelem > पूर्णांक_उच्च / elsize)
        परत AVERROR(EINVAL);
    जर (!(rmq = av_mallocz(आकार(*rmq))))
        परत AVERROR(ENOMEM);
    जर ((ret = pthread_mutex_init(&rmq->lock, रिक्त))) {
        av_free(rmq);
        परत AVERROR(ret);
    }
    जर ((ret = pthread_cond_init(&rmq->cond_recv, रिक्त))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        परत AVERROR(ret);
    }
    जर ((ret = pthread_cond_init(&rmq->cond_send, रिक्त))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        परत AVERROR(ret);
    }
    जर (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        परत AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    परत 0;
#अन्यथा
    *mq = रिक्त;
    परत AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           शून्य (*free_func)(शून्य *संदेश))
{
#जर HAVE_THREADS
    mq->free_func = free_func;
#endif
}

शून्य av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#जर HAVE_THREADS
    जर (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

पूर्णांक av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#जर HAVE_THREADS
    पूर्णांक ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    परत ret;
#अन्यथा
    परत AVERROR(ENOSYS);
#endif
}

#जर HAVE_THREADS

स्थिर पूर्णांक av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               शून्य *संदेश,
                                               अचिन्हित flags)
{
    पर्यंत (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        जर ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            परत AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    जर (mq->err_send)
        परत mq->err_send;
    av_fifo_write(mq->fifo, संदेश, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    परत 0;
}

स्थिर पूर्णांक av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               शून्य *संदेश,
                                               अचिन्हित flags)
{
    पर्यंत (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        जर ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            परत AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    जर (!av_fifo_can_read(mq->fifo))
        परत mq->err_recv;
    av_fifo_read(mq->fifo, संदेश, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    परत 0;
}

#endif /* HAVE_THREADS */

पूर्णांक av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 शून्य *संदेश,
                                 अचिन्हित flags)
{
#जर HAVE_THREADS
    पूर्णांक ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, संदेश, flags);
    pthread_mutex_unlock(&mq->lock);
    परत ret;
#अन्यथा
    परत AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

पूर्णांक av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 शून्य *संदेश,
                                 अचिन्हित flags)
{
#जर HAVE_THREADS
    पूर्णांक ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, संदेश, flags);
    pthread_mutex_unlock(&mq->lock);
    परत ret;
#अन्यथा
    परत AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          पूर्णांक err)
{
#जर HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

शून्य av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          पूर्णांक err)
{
#जर HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#जर HAVE_THREADS
स्थिर पूर्णांक free_func_wrap(शून्य *arg, शून्य *buf, माप_प्रकार *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *संदेश = buf;
    साठी (माप_प्रकार i = 0; i < *nb_elems; i++)
        mq->free_func(संदेश + i * mq->elsize);
    परत 0;
}
#endif

शून्य av_thread_message_flush(AVThreadMessageQueue *mq)
{
#जर HAVE_THREADS
    माप_प्रकार used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    जर (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
