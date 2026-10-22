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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stddef.h>

#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "fifo.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "threadmessage.h"
#അന്തര്ഭാവ "thread.h"

ഘടന AVThreadMessageQueue {
#എങ്കിൽ HAVE_THREADS
    AVFifo *fifo;
    pthread_mutex_t lock;
    pthread_cond_t cond_recv;
    pthread_cond_t cond_send;
    പൂർണ്ണസംഖ്യ err_send;
    പൂർണ്ണസംഖ്യ err_recv;
    unsigned elsize;
    ശൂന്യം (*free_func)(ശൂന്യം *സന്ദേശം);
#അല്ലെങ്കിൽ
    പൂർണ്ണസംഖ്യ dummy;
#endif
};

പൂർണ്ണസംഖ്യ av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#എങ്കിൽ HAVE_THREADS
    AVThreadMessageQueue *rmq;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (nelem > INT_MAX / elsize)
        തിരികെ AVERROR(EINVAL);
    എങ്കിൽ (!(rmq = av_mallocz(വലുപ്പം(*rmq))))
        തിരികെ AVERROR(ENOMEM);
    എങ്കിൽ ((ret = pthread_mutex_init(&rmq->lock, ശൂന്യ))) {
        av_free(rmq);
        തിരികെ AVERROR(ret);
    }
    എങ്കിൽ ((ret = pthread_cond_init(&rmq->cond_recv, ശൂന്യ))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        തിരികെ AVERROR(ret);
    }
    എങ്കിൽ ((ret = pthread_cond_init(&rmq->cond_send, ശൂന്യ))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        തിരികെ AVERROR(ret);
    }
    എങ്കിൽ (!(rmq->fifo = av_fifo_alloc2(nelem, elsize, 0))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        തിരികെ AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    തിരികെ 0;
#അല്ലെങ്കിൽ
    *mq = ശൂന്യ;
    തിരികെ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ശൂന്യം av_thread_message_queue_set_free_func(AVThreadMessageQueue *mq,
                                           ശൂന്യം (*free_func)(ശൂന്യം *സന്ദേശം))
{
#എങ്കിൽ HAVE_THREADS
    mq->free_func = free_func;
#endif
}

ശൂന്യം av_thread_message_queue_free(AVThreadMessageQueue **mq)
{
#എങ്കിൽ HAVE_THREADS
    എങ്കിൽ (*mq) {
        av_thread_message_flush(*mq);
        av_fifo_freep2(&(*mq)->fifo);
        pthread_cond_destroy(&(*mq)->cond_send);
        pthread_cond_destroy(&(*mq)->cond_recv);
        pthread_mutex_destroy(&(*mq)->lock);
        av_freep(mq);
    }
#endif
}

പൂർണ്ണസംഖ്യ av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#എങ്കിൽ HAVE_THREADS
    പൂർണ്ണസംഖ്യ ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_can_read(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    തിരികെ ret;
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif
}

#എങ്കിൽ HAVE_THREADS

സ്ഥിതം പൂർണ്ണസംഖ്യ av_thread_message_queue_send_locked(AVThreadMessageQueue *mq,
                                               ശൂന്യം *സന്ദേശം,
                                               unsigned flags)
{
    ആകുമ്പോൾ (!mq->err_send && !av_fifo_can_write(mq->fifo)) {
        എങ്കിൽ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            തിരികെ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_send, &mq->lock);
    }
    എങ്കിൽ (mq->err_send)
        തിരികെ mq->err_send;
    av_fifo_write(mq->fifo, സന്ദേശം, 1);
    /* one message is sent, signal one receiver */
    pthread_cond_signal(&mq->cond_recv);
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ av_thread_message_queue_recv_locked(AVThreadMessageQueue *mq,
                                               ശൂന്യം *സന്ദേശം,
                                               unsigned flags)
{
    ആകുമ്പോൾ (!mq->err_recv && !av_fifo_can_read(mq->fifo)) {
        എങ്കിൽ ((flags & AV_THREAD_MESSAGE_NONBLOCK))
            തിരികെ AVERROR(EAGAIN);
        pthread_cond_wait(&mq->cond_recv, &mq->lock);
    }
    എങ്കിൽ (!av_fifo_can_read(mq->fifo))
        തിരികെ mq->err_recv;
    av_fifo_read(mq->fifo, സന്ദേശം, 1);
    /* one message space appeared, signal one sender */
    pthread_cond_signal(&mq->cond_send);
    തിരികെ 0;
}

#endif /* HAVE_THREADS */

പൂർണ്ണസംഖ്യ av_thread_message_queue_send(AVThreadMessageQueue *mq,
                                 ശൂന്യം *സന്ദേശം,
                                 unsigned flags)
{
#എങ്കിൽ HAVE_THREADS
    പൂർണ്ണസംഖ്യ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_send_locked(mq, സന്ദേശം, flags);
    pthread_mutex_unlock(&mq->lock);
    തിരികെ ret;
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

പൂർണ്ണസംഖ്യ av_thread_message_queue_recv(AVThreadMessageQueue *mq,
                                 ശൂന്യം *സന്ദേശം,
                                 unsigned flags)
{
#എങ്കിൽ HAVE_THREADS
    പൂർണ്ണസംഖ്യ ret;

    pthread_mutex_lock(&mq->lock);
    ret = av_thread_message_queue_recv_locked(mq, സന്ദേശം, flags);
    pthread_mutex_unlock(&mq->lock);
    തിരികെ ret;
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}

ശൂന്യം av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq,
                                          പൂർണ്ണസംഖ്യ err)
{
#എങ്കിൽ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_send = err;
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

ശൂന്യം av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq,
                                          പൂർണ്ണസംഖ്യ err)
{
#എങ്കിൽ HAVE_THREADS
    pthread_mutex_lock(&mq->lock);
    mq->err_recv = err;
    pthread_cond_broadcast(&mq->cond_recv);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}

#എങ്കിൽ HAVE_THREADS
സ്ഥിതം പൂർണ്ണസംഖ്യ free_func_wrap(ശൂന്യം *arg, ശൂന്യം *buf, size_t *nb_elems)
{
    AVThreadMessageQueue *mq = arg;
    uint8_t *സന്ദേശം = buf;
    വേണ്ടി (size_t i = 0; i < *nb_elems; i++)
        mq->free_func(സന്ദേശം + i * mq->elsize);
    തിരികെ 0;
}
#endif

ശൂന്യം av_thread_message_flush(AVThreadMessageQueue *mq)
{
#എങ്കിൽ HAVE_THREADS
    size_t used;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_can_read(mq->fifo);
    എങ്കിൽ (mq->free_func)
        av_fifo_read_to_cb(mq->fifo, free_func_wrap, mq, &used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}
