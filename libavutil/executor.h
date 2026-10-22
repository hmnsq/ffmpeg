/*
 * Copyright (C) 2023 Nuo Mi
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_EXECUTOR_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_EXECUTOR_H

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVExecutor AVExecutor;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVTask AVTask;

ਬਣਤਰ AVTask {
    AVTask *ਅਗਲਾ;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVTaskCallbacks {
    ਖਾਲੀ *user_ਅੰਕੜੇ;

    ਪੂਰਨ local_context_ਮਾਪ;

    // return 1 if a's priority > b's priority
    ਪੂਰਨ (*ਤਰਜੀਹ_higher)(ਅਚਲ AVTask *a, ਅਚਲ AVTask *b);

    // task is ready for run
    ਪੂਰਨ (*ready)(ਅਚਲ AVTask *t, ਖਾਲੀ *user_ਅੰਕੜੇ);

    // run the task
    ਪੂਰਨ (*ਲੜੀਵਾਰ)(AVTask *t, ਖਾਲੀ *local_context, ਖਾਲੀ *user_ਅੰਕੜੇ);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ਅਚਲ AVTaskCallbacks *callbacks, ਪੂਰਨ thread_ਗਿਣਤੀ);

/**
 * Free executor
 * @param e  pointer to executor
 */
ਖਾਲੀ av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
ਖਾਲੀ av_executor_execute(AVExecutor *e, AVTask *t);

#ਜੇ_ਅੰਤ //AVUTIL_EXECUTOR_H
