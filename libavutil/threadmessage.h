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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_THREADMESSAGE_H
#وصف_ڪريو AVUTIL_THREADMESSAGE_H

تعريفنوع بنية AVThread_پيغام_قطار AVThread_پيغام_قطار;

تعريفنوع تعداد AVThread_پيغام_Flags {

    /**
     * Perform non-blocking operation.
     * If this flag is set, send and recv operations are non-blocking and
     * return AVERROR(EAGAIN) immediately if they can not proceed.
     */
    AV_THREAD_پيغام_NONBLOCK = 1,

} AVThread_پيغام_Flags;

/**
 * Allocate a new message queue.
 *
 * @param mq      pointer to the message queue
 * @param nelem   maximum number of elements in the queue
 * @param elsize  size of each element in the queue
 * @return  >=0 for success; <0 for error, in particular AVERROR(ENOSYS) if
 *          lavu was built without thread support
 */
صحيح av_thread_پيغام_قطار_alloc(AVThread_پيغام_قطار **mq,
                                  بنانشان nelem,
                                  بنانشان elsize);

/**
 * Free a message queue.
 *
 * The message queue must no longer be in use by another thread.
 */
فراغ av_thread_پيغام_قطار_free(AVThread_پيغام_قطار **mq);

/**
 * Send a message on the queue.
 */
صحيح av_thread_پيغام_قطار_send(AVThread_پيغام_قطار *mq,
                                 فراغ *نياپو,
                                 بنانشان flags);

/**
 * Receive a message from the queue.
 */
صحيح av_thread_پيغام_قطار_recv(AVThread_پيغام_قطار *mq,
                                 فراغ *نياپو,
                                 بنانشان flags);

/**
 * Set the sending error code.
 *
 * If the error code is set to non-zero, av_thread_message_queue_send() will
 * return it immediately. Conventional values, such as AVERROR_EOF or
 * AVERROR(EAGAIN), can be used to cause the sending thread to stop or
 * suspend its operation.
 */
فراغ av_thread_پيغام_قطار_سيٽ_err_send(AVThread_پيغام_قطار *mq,
                                          صحيح err);

/**
 * Set the receiving error code.
 *
 * If the error code is set to non-zero, av_thread_message_queue_recv() will
 * return it immediately when there are no longer available messages.
 * Conventional values, such as AVERROR_EOF or AVERROR(EAGAIN), can be used
 * to cause the receiving thread to stop or suspend its operation.
 */
فراغ av_thread_پيغام_قطار_سيٽ_err_recv(AVThread_پيغام_قطار *mq,
                                          صحيح err);

/**
 * Set the optional free message callback function which will be called if an
 * operation is removing messages from the queue.
 */
فراغ av_thread_پيغام_قطار_سيٽ_free_func(AVThread_پيغام_قطار *mq,
                                           فراغ (*free_func)(فراغ *نياپو));

/**
 * Return the current number of messages in the queue.
 *
 * @return the current number of messages or AVERROR(ENOSYS) if lavu was built
 *         without thread support
 */
صحيح av_thread_پيغام_قطار_nb_elems(AVThread_پيغام_قطار *mq);

/**
 * Flush the message queue
 *
 * This function is mostly equivalent to reading and free-ing every message
 * except that it will be done in a single operation (no lock/unlock between
 * reads).
 */
فراغ av_thread_پيغام_flush(AVThread_پيغام_قطار *mq);

#جيڪڏهن_پورو /* AVUTIL_THREADMESSAGE_H */
