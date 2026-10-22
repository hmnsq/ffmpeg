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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stddef.h>

#అన్తర్భావ "error.h"
#అన్తర్భావ "fifo.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "threadmessage.h"
#అన్తర్భావ "thread.h"

నిర్మాణం AVThread_సందేశం_వరుస {
#ఒకవేళ HAVE_దారాలు
    AVFifo *fifo;
    pthread_mutex_t తాళం_2;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    పూర్ణాంకం err_send;
    పూర్ణాంకం err_recv;
    గుర్తులేని elsize;
    శూన్య (*free_func)(శూన్య *సందేశం);
#లేకపోతే
    పూర్ణాంకం dummy;
#అయితే_ముగింపు
};

పూర్ణాంకం av_thread_సందేశం_వరుస_alloc(AVThread_సందేశం_వరుస **mq,
                                  గుర్తులేని nelem,
                                  గుర్తులేని elsize)
{
#ఒకవేళ HAVE_దారాలు
    AVThread_సందేశం_వరుస *rmq;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (nelem > గరిష్ఠ_పూర్ణాంకం / elsize)
        తిరిగి AVERROR(EINVAL);
    ఒకవేళ (!(rmq = av_mallocz(పరిమాణం(*rmq))))
        తిరిగి AVERROR(ENOMEM);
    ఒకవేళ ((ret = pthread_mutex_init(&rmq->తాళం_2, ఖాళీ))) {
        av_free(rmq);
        తిరిగి AVERROR(ret);
    }
    ఒకవేళ ((ret = pthread_cond_init(&rmq->cond_recv, ఖాళీ))) {
        pthread_mutex_destroy(&rmq->తాళం_2);
        av_free(rmq);
        తిరిగి AVERROR(ret);
    }
    ఒకవేళ ((ret = pthread_cond_init(&rmq->cond_send, ఖాళీ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->తాళం_2);
        av_free(rmq);
        తిరిగి AVERROR(ret);
    }
    ఒకవేళ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->తాళం_2);
        av_free(rmq);
        తిరిగి AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    తిరిగి 0;
#లేకపోతే
    *mq = ఖాళీ;
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు /* HAVE_THREADS */
}

శూన్య av_thread_సందేశం_వరుస_సమితి_free_func(AVThread_సందేశం_వరుస *mq,
                                           శూన్య (*free_func)(శూన్య *సందేశం))
{
#ఒకవేళ HAVE_దారాలు
    mq->free_func = free_func;
#అయితే_ముగింపు
}

శూన్య av_thread_సందేశం_వరుస_free(AVThread_సందేశం_వరుస **mq)
{
#ఒకవేళ HAVE_దారాలు
    ఒకవేళ (*mq) {
        av_thread_సందేశం_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->తాళం_2);
        av_freep(mq);
    }
#అయితే_ముగింపు
}

పూర్ణాంకం av_thread_సందేశం_వరుస_nb_elems(AVThread_సందేశం_వరుస *mq)
{
#ఒకవేళ HAVE_దారాలు
    పూర్ణాంకం ret;
    pthread_mutex_తాళం(&mq->తాళం_2);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->తాళం_2);
    తిరిగి ret;
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
}

#ఒకవేళ HAVE_దారాలు

స్థిర పూర్ణాంకం av_thread_సందేశం_వరుస_send_locked(AVThread_సందేశం_వరుస *mq,
                                               శూన్య *సందేశం,
                                               గుర్తులేని flags)
{
    అయితే (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        ఒకవేళ ((flags & AV_THREAD_సందేశం_NONBLOCK))
            తిరిగి AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->తాళం_2);
    }
    ఒకవేళ (mq->err_send)
        తిరిగి mq->err_send;
    av_fifo_write(mq->fifo, సందేశం, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    తిరిగి 0;
}

స్థిర పూర్ణాంకం av_thread_సందేశం_వరుస_recv_locked(AVThread_సందేశం_వరుస *mq,
                                               శూన్య *సందేశం,
                                               గుర్తులేని flags)
{
    అయితే (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        ఒకవేళ ((flags & AV_THREAD_సందేశం_NONBLOCK))
            తిరిగి AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->తాళం_2);
    }
    ఒకవేళ (!av_fifo_can_read(mq->fifo))
        తిరిగి mq->err_recv;
    av_fifo_read(mq->fifo, సందేశం, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    తిరిగి 0;
}

#అయితే_ముగింపు /* HAVE_THREADS */

పూర్ణాంకం av_thread_సందేశం_వరుస_send(AVThread_సందేశం_వరుస *mq,
                                 శూన్య *సందేశం,
                                 గుర్తులేని flags)
{
#ఒకవేళ HAVE_దారాలు
    పూర్ణాంకం ret;

    pthread_mutex_తాళం(&mq->తాళం_2);
    ret = av_thread_సందేశం_వరుస_send_locked(mq, సందేశం, flags);
    pthread_mutex_unlock(&mq->తాళం_2);
    తిరిగి ret;
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు /* HAVE_THREADS */
}

పూర్ణాంకం av_thread_సందేశం_వరుస_recv(AVThread_సందేశం_వరుస *mq,
                                 శూన్య *సందేశం,
                                 గుర్తులేని flags)
{
#ఒకవేళ HAVE_దారాలు
    పూర్ణాంకం ret;

    pthread_mutex_తాళం(&mq->తాళం_2);
    ret = av_thread_సందేశం_వరుస_recv_locked(mq, సందేశం, flags);
    pthread_mutex_unlock(&mq->తాళం_2);
    తిరిగి ret;
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు /* HAVE_THREADS */
}

శూన్య av_thread_సందేశం_వరుస_సమితి_err_send(AVThread_సందేశం_వరుస *mq,
                                          పూర్ణాంకం err)
{
#ఒకవేళ HAVE_దారాలు
    pthread_mutex_తాళం(&mq->తాళం_2);
    mq->err_send = err;
    pthread_cond_ప్రసారం(&mq->cond_send);
    pthread_mutex_unlock(&mq->తాళం_2);
#అయితే_ముగింపు /* HAVE_THREADS */
}

శూన్య av_thread_సందేశం_వరుస_సమితి_err_recv(AVThread_సందేశం_వరుస *mq,
                                          పూర్ణాంకం err)
{
#ఒకవేళ HAVE_దారాలు
    pthread_mutex_తాళం(&mq->తాళం_2);
    mq->err_recv = err;
    pthread_cond_ప్రసారం(&mq->cond_recv);
    pthread_mutex_unlock(&mq->తాళం_2);
#అయితే_ముగింపు /* HAVE_THREADS */
}

#ఒకవేళ HAVE_దారాలు
స్థిర పూర్ణాంకం free_func_wrap(శూన్య *arg, శూన్య *buf, size_t *nb_elems)
{
    AVThread_సందేశం_వరుస *mq = arg;
    uint8_t *సందేశం = buf;
    కొరకు (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(సందేశం + i * mq->elsize);
    తిరిగి 0;
}
#అయితే_ముగింపు

శూన్య av_thread_సందేశం_flush(AVThread_సందేశం_వరుస *mq)
{
#ఒకవేళ HAVE_దారాలు
    size_t వాడిన;

    pthread_mutex_తాళం(&mq->తాళం_2);
    వాడిన = av_fifo_can_read(mq->fifo);
    ఒకవేళ (mq->free_func)
        av_fifo_read_గమ్యం_cb(mq->fifo, free_func_wrap, mq, &వాడిన);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_ప్రసారం(&mq->cond_send);
    pthread_mutex_unlock(&mq->తాళం_2);
#అయితే_ముగింపు /* HAVE_THREADS */
}
