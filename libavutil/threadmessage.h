/*
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

#यदि_अपरिभाषितम् AVUTIL_THREADMESSAGE_H
#परिभाषय AVUTIL_THREADMESSAGE_H

प्रकारनिर्देश संरचना AVThread_सन्देशः_Queue AVThread_सन्देशः_Queue;

प्रकारनिर्देश गणना AVThread_सन्देशः_Flags {

    /**
     * Perform non-blocking operation.
     * If this flag is set, send and recv operations are non-blocking and
     * return AVERROR(EAGAIN) immediately if they can not proceed.
     */
    AV_THREAD_सन्देशः_NONBLOCK = 1,

} AVThread_सन्देशः_Flags;

/**
 * Allocate a new message queue.
 *
 * @param mq      pointer to the message queue
 * @param nelem   maximum number of elements in the queue
 * @param elsize  size of each element in the queue
 * @return  >=0 for success; <0 for error, in particular AVERROR(ENOSYS) if
 *          lavu was built without thread support
 */
पूर्णाङ्क av_thread_सन्देशः_queue_alloc(AVThread_सन्देशः_Queue **mq,
                                  अचिह्नित nelem,
                                  अचिह्नित elsize);

/**
 * Free a message queue.
 *
 * The message queue must no longer be in use by another thread.
 */
शून्य av_thread_सन्देशः_queue_free(AVThread_सन्देशः_Queue **mq);

/**
 * Send a message on the queue.
 */
पूर्णाङ्क av_thread_सन्देशः_queue_send(AVThread_सन्देशः_Queue *mq,
                                 शून्य *सन्देशः,
                                 अचिह्नित flags);

/**
 * Receive a message from the queue.
 */
पूर्णाङ्क av_thread_सन्देशः_queue_recv(AVThread_सन्देशः_Queue *mq,
                                 शून्य *सन्देशः,
                                 अचिह्नित flags);

/**
 * Set the sending error code.
 *
 * If the error code is set to non-zero, av_thread_message_queue_send() will
 * return it immediately. Conventional values, such as AVERROR_EOF or
 * AVERROR(EAGAIN), can be used to cause the sending thread to stop or
 * suspend its operation.
 */
शून्य av_thread_सन्देशः_queue_समुच्चयः_err_send(AVThread_सन्देशः_Queue *mq,
                                          पूर्णाङ्क err);

/**
 * Set the receiving error code.
 *
 * If the error code is set to non-zero, av_thread_message_queue_recv() will
 * return it immediately when there are no longer available messages.
 * Conventional values, such as AVERROR_EOF or AVERROR(EAGAIN), can be used
 * to cause the receiving thread to stop or suspend its operation.
 */
शून्य av_thread_सन्देशः_queue_समुच्चयः_err_recv(AVThread_सन्देशः_Queue *mq,
                                          पूर्णाङ्क err);

/**
 * Set the optional free message callback function which will be called if an
 * operation is removing messages from the queue.
 */
शून्य av_thread_सन्देशः_queue_समुच्चयः_free_func(AVThread_सन्देशः_Queue *mq,
                                           शून्य (*free_func)(शून्य *सन्देशः));

/**
 * Return the current number of messages in the queue.
 *
 * @return the current number of messages or AVERROR(ENOSYS) if lavu was built
 *         without thread support
 */
पूर्णाङ्क av_thread_सन्देशः_queue_nb_elems(AVThread_सन्देशः_Queue *mq);

/**
 * Flush the message queue
 *
 * This function is mostly equivalent to reading and free-ing every message
 * except that it will be done in a single operation (no lock/unlock between
 * reads).
 */
शून्य av_thread_सन्देशः_flush(AVThread_सन्देशः_Queue *mq);

#यदि_अन्तः /* AVUTIL_THREADMESSAGE_H */
