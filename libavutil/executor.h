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

#ifndef AVUTIL_EXECUTOR_H
#define AVUTIL_EXECUTOR_H

প্রকারনির্দেশ সংরচনা AVExecutor AVExecutor;
প্রকারনির্দেশ সংরচনা AVTask AVTask;

সংরচনা AVTask {
    AVTask *next;
};

প্রকারনির্দেশ সংরচনা AVTaskCallbacks {
    শূন্য *user_data;

    পূর্ণাঙ্ক local_context_size;

    // return 1 if a's priority > b's priority
    পূর্ণাঙ্ক (*priority_higher)(ধ্রুব AVTask *a, ধ্রুব AVTask *b);

    // task is ready for run
    পূর্ণাঙ্ক (*ready)(ধ্রুব AVTask *t, শূন্য *user_data);

    // run the task
    পূর্ণাঙ্ক (*run)(AVTask *t, শূন্য *local_context, শূন্য *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ধ্রুব AVTaskCallbacks *callbacks, পূর্ণাঙ্ক thread_গুনতি);

/**
 * Free executor
 * @param e  pointer to executor
 */
শূন্য av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
শূন্য av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
