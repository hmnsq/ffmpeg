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

#شامل <limits.h>
#شامل <stddef.h>

#شامل "error.h"
#شامل "fifo.h"
#شامل "mem.h"
#شامل "threadmessage.h"
#شامل "thread.h"

ساخت AVThread_پیغام_قطار {
#اگر HAVE_دھاگے
    AVFifo *fifo;
    pthread_mutex_t تالا_2;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    صحیح err_send;
    صحیح err_recv;
    غیرعلامتی elsize;
    خالی (*free_func)(خالی *پیغام);
#ورنہ
    صحیح dummy;
#اگر_ختم
};

صحیح av_thread_پیغام_قطار_alloc(AVThread_پیغام_قطار **mq,
                                  غیرعلامتی nelem,
                                  غیرعلامتی elsize)
{
#اگر HAVE_دھاگے
    AVThread_پیغام_قطار *rmq;
    صحیح ret = 0;

    اگر (nelem > زیادہ_سے_زیادہ_عدد / elsize)
        واپس AVERROR(EINVAL);
    اگر (!(rmq = av_mallocz(حجم(*rmq))))
        واپس AVERROR(ENOMEM);
    اگر ((ret = pthread_mutex_init(&rmq->تالا_2, تہی))) {
        av_free(rmq);
        واپس AVERROR(ret);
    }
    اگر ((ret = pthread_cond_init(&rmq->cond_recv, تہی))) {
        pthread_mutex_destroy(&rmq->تالا_2);
        av_free(rmq);
        واپس AVERROR(ret);
    }
    اگر ((ret = pthread_cond_init(&rmq->cond_send, تہی))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->تالا_2);
        av_free(rmq);
        واپس AVERROR(ret);
    }
    اگر (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->تالا_2);
        av_free(rmq);
        واپس AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    واپس 0;
#ورنہ
    *mq = تہی;
    واپس AVERROR(ENOSYS);
#اگر_ختم /* HAVE_THREADS */
}

خالی av_thread_پیغام_قطار_سیٹ_free_func(AVThread_پیغام_قطار *mq,
                                           خالی (*free_func)(خالی *پیغام))
{
#اگر HAVE_دھاگے
    mq->free_func = free_func;
#اگر_ختم
}

خالی av_thread_پیغام_قطار_free(AVThread_پیغام_قطار **mq)
{
#اگر HAVE_دھاگے
    اگر (*mq) {
        av_thread_پیغام_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->تالا_2);
        av_freep(mq);
    }
#اگر_ختم
}

صحیح av_thread_پیغام_قطار_nb_elems(AVThread_پیغام_قطار *mq)
{
#اگر HAVE_دھاگے
    صحیح ret;
    pthread_mutex_تالا(&mq->تالا_2);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->تالا_2);
    واپس ret;
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم
}

#اگر HAVE_دھاگے

ساکن صحیح av_thread_پیغام_قطار_send_locked(AVThread_پیغام_قطار *mq,
                                               خالی *پیغام,
                                               غیرعلامتی flags)
{
    جب (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        اگر ((flags & AV_THREAD_پیغام_NONBLOCK))
            واپس AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->تالا_2);
    }
    اگر (mq->err_send)
        واپس mq->err_send;
    av_fifo_write(mq->fifo, پیغام, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    واپس 0;
}

ساکن صحیح av_thread_پیغام_قطار_recv_locked(AVThread_پیغام_قطار *mq,
                                               خالی *پیغام,
                                               غیرعلامتی flags)
{
    جب (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        اگر ((flags & AV_THREAD_پیغام_NONBLOCK))
            واپس AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->تالا_2);
    }
    اگر (!av_fifo_can_read(mq->fifo))
        واپس mq->err_recv;
    av_fifo_read(mq->fifo, پیغام, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    واپس 0;
}

#اگر_ختم /* HAVE_THREADS */

صحیح av_thread_پیغام_قطار_send(AVThread_پیغام_قطار *mq,
                                 خالی *پیغام,
                                 غیرعلامتی flags)
{
#اگر HAVE_دھاگے
    صحیح ret;

    pthread_mutex_تالا(&mq->تالا_2);
    ret = av_thread_پیغام_قطار_send_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->تالا_2);
    واپس ret;
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم /* HAVE_THREADS */
}

صحیح av_thread_پیغام_قطار_recv(AVThread_پیغام_قطار *mq,
                                 خالی *پیغام,
                                 غیرعلامتی flags)
{
#اگر HAVE_دھاگے
    صحیح ret;

    pthread_mutex_تالا(&mq->تالا_2);
    ret = av_thread_پیغام_قطار_recv_locked(mq, پیغام, flags);
    pthread_mutex_unlock(&mq->تالا_2);
    واپس ret;
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم /* HAVE_THREADS */
}

خالی av_thread_پیغام_قطار_سیٹ_err_send(AVThread_پیغام_قطار *mq,
                                          صحیح err)
{
#اگر HAVE_دھاگے
    pthread_mutex_تالا(&mq->تالا_2);
    mq->err_send = err;
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->تالا_2);
#اگر_ختم /* HAVE_THREADS */
}

خالی av_thread_پیغام_قطار_سیٹ_err_recv(AVThread_پیغام_قطار *mq,
                                          صحیح err)
{
#اگر HAVE_دھاگے
    pthread_mutex_تالا(&mq->تالا_2);
    mq->err_recv = err;
    pthread_cond_نشر(&mq->cond_recv);
    pthread_mutex_unlock(&mq->تالا_2);
#اگر_ختم /* HAVE_THREADS */
}

#اگر HAVE_دھاگے
ساکن صحیح free_func_wrap(خالی *arg, خالی *buf, size_t *nb_elems)
{
    AVThread_پیغام_قطار *mq = arg;
    uint8_t *پیغام = buf;
    برائے (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(پیغام + i * mq->elsize);
    واپس 0;
}
#اگر_ختم

خالی av_thread_پیغام_flush(AVThread_پیغام_قطار *mq)
{
#اگر HAVE_دھاگے
    size_t مستعمل;

    pthread_mutex_تالا(&mq->تالا_2);
    مستعمل = av_fifo_can_read(mq->fifo);
    اگر (mq->free_func)
        av_fifo_read_مقصد_cb(mq->fifo, free_func_wrap, mq, &مستعمل);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_نشر(&mq->cond_send);
    pthread_mutex_unlock(&mq->تالا_2);
#اگر_ختم /* HAVE_THREADS */
}
