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

संरचना AVThread_सन्देशः_Queue {
#यदि HAVE_तन्तवः
    AVFifo *fifo;
    pthread_mutex_t तालकम्;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    पूर्णाङ्क err_send;
    पूर्णाङ्क err_recv;
    अचिह्नित elsize;
    शून्य (*free_func)(शून्य *सन्देशः);
#अन्यथा
    पूर्णाङ्क dummy;
#यदि_अन्तः
};

पूर्णाङ्क av_thread_सन्देशः_queue_alloc(AVThread_सन्देशः_Queue **mq,
                                  अचिह्नित nelem,
                                  अचिह्नित elsize)
{
#यदि HAVE_तन्तवः
    AVThread_सन्देशः_Queue *rmq;
    पूर्णाङ्क ret = 0;

    यदि (nelem > अधिकतम_पूर्णाङ्कः / elsize)
        प्रत्यागम AVERROR(EINVAL);
    यदि (!(rmq = av_mallocz(परिमाण(*rmq))))
        प्रत्यागम AVERROR(ENOMEM);
    यदि ((ret = pthread_mutex_init(&rmq->तालकम्, रिक्त))) {
        av_free(rmq);
        प्रत्यागम AVERROR(ret);
    }
    यदि ((ret = pthread_cond_init(&rmq->cond_recv, रिक्त))) {
        pthread_mutex_destroy(&rmq->तालकम्);
        av_free(rmq);
        प्रत्यागम AVERROR(ret);
    }
    यदि ((ret = pthread_cond_init(&rmq->cond_send, रिक्त))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->तालकम्);
        av_free(rmq);
        प्रत्यागम AVERROR(ret);
    }
    यदि (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->तालकम्);
        av_free(rmq);
        प्रत्यागम AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    प्रत्यागम 0;
#अन्यथा
    *mq = रिक्त;
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः /* HAVE_THREADS */
}

शून्य av_thread_सन्देशः_queue_समुच्चयः_free_func(AVThread_सन्देशः_Queue *mq,
                                           शून्य (*free_func)(शून्य *सन्देशः))
{
#यदि HAVE_तन्तवः
    mq->free_func = free_func;
#यदि_अन्तः
}

शून्य av_thread_सन्देशः_queue_free(AVThread_सन्देशः_Queue **mq)
{
#यदि HAVE_तन्तवः
    यदि (*mq) {
        av_thread_सन्देशः_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->तालकम्);
        av_freep(mq);
    }
#यदि_अन्तः
}

पूर्णाङ्क av_thread_सन्देशः_queue_nb_elems(AVThread_सन्देशः_Queue *mq)
{
#यदि HAVE_तन्तवः
    पूर्णाङ्क ret;
    pthread_mutex_तालकम्(&mq->तालकम्);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->तालकम्);
    प्रत्यागम ret;
#अन्यथा
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
}

#यदि HAVE_तन्तवः

स्थिर पूर्णाङ्क av_thread_सन्देशः_queue_send_locked(AVThread_सन्देशः_Queue *mq,
                                               शून्य *सन्देशः,
                                               अचिह्नित flags)
{
    यावत् (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        यदि ((flags & AV_THREAD_सन्देशः_NONBLOCK))
            प्रत्यागम AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->तालकम्);
    }
    यदि (mq->err_send)
        प्रत्यागम mq->err_send;
    av_fifo_write(mq->fifo, सन्देशः, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क av_thread_सन्देशः_queue_recv_locked(AVThread_सन्देशः_Queue *mq,
                                               शून्य *सन्देशः,
                                               अचिह्नित flags)
{
    यावत् (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        यदि ((flags & AV_THREAD_सन्देशः_NONBLOCK))
            प्रत्यागम AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->तालकम्);
    }
    यदि (!av_fifo_can_read(mq->fifo))
        प्रत्यागम mq->err_recv;
    av_fifo_read(mq->fifo, सन्देशः, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    प्रत्यागम 0;
}

#यदि_अन्तः /* HAVE_THREADS */

पूर्णाङ्क av_thread_सन्देशः_queue_send(AVThread_सन्देशः_Queue *mq,
                                 शून्य *सन्देशः,
                                 अचिह्नित flags)
{
#यदि HAVE_तन्तवः
    पूर्णाङ्क ret;

    pthread_mutex_तालकम्(&mq->तालकम्);
    ret = av_thread_सन्देशः_queue_send_locked(mq, सन्देशः, flags);
    pthread_mutex_unlock(&mq->तालकम्);
    प्रत्यागम ret;
#अन्यथा
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः /* HAVE_THREADS */
}

पूर्णाङ्क av_thread_सन्देशः_queue_recv(AVThread_सन्देशः_Queue *mq,
                                 शून्य *सन्देशः,
                                 अचिह्नित flags)
{
#यदि HAVE_तन्तवः
    पूर्णाङ्क ret;

    pthread_mutex_तालकम्(&mq->तालकम्);
    ret = av_thread_सन्देशः_queue_recv_locked(mq, सन्देशः, flags);
    pthread_mutex_unlock(&mq->तालकम्);
    प्रत्यागम ret;
#अन्यथा
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः /* HAVE_THREADS */
}

शून्य av_thread_सन्देशः_queue_समुच्चयः_err_send(AVThread_सन्देशः_Queue *mq,
                                          पूर्णाङ्क err)
{
#यदि HAVE_तन्तवः
    pthread_mutex_तालकम्(&mq->तालकम्);
    mq->err_send = err;
    pthread_cond_प्रसारणम्(&mq->cond_send);
    pthread_mutex_unlock(&mq->तालकम्);
#यदि_अन्तः /* HAVE_THREADS */
}

शून्य av_thread_सन्देशः_queue_समुच्चयः_err_recv(AVThread_सन्देशः_Queue *mq,
                                          पूर्णाङ्क err)
{
#यदि HAVE_तन्तवः
    pthread_mutex_तालकम्(&mq->तालकम्);
    mq->err_recv = err;
    pthread_cond_प्रसारणम्(&mq->cond_recv);
    pthread_mutex_unlock(&mq->तालकम्);
#यदि_अन्तः /* HAVE_THREADS */
}

#यदि HAVE_तन्तवः
स्थिर पूर्णाङ्क free_func_wrap(शून्य *arg, शून्य *buf, size_t *nb_elems)
{
    AVThread_सन्देशः_Queue *mq = arg;
    uint8_t *सन्देशः = buf;
    प्रति (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(सन्देशः + i * mq->elsize);
    प्रत्यागम 0;
}
#यदि_अन्तः

शून्य av_thread_सन्देशः_flush(AVThread_सन्देशः_Queue *mq)
{
#यदि HAVE_तन्तवः
    size_t प्रयुक्तम्;

    pthread_mutex_तालकम्(&mq->तालकम्);
    प्रयुक्तम् = av_fifo_can_read(mq->fifo);
    यदि (mq->free_func)
        av_fifo_read_गन्तव्यम्_cb(mq->fifo, free_func_wrap, mq, &प्रयुक्तम्);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_प्रसारणम्(&mq->cond_send);
    pthread_mutex_unlock(&mq->तालकम्);
#यदि_अन्तः /* HAVE_THREADS */
}
