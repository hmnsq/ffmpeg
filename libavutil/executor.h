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

تعريفنوع بنية AVExecutor AVExecutor;
تعريفنوع بنية AVTask AVTask;

بنية AVTask {
    AVTask *next;
};

تعريفنوع بنية AVTaskCallbacks {
    فراغ *user_data;

    صحيح local_context_size;

    // return 1 if a's priority > b's priority
    صحيح (*priority_higher)(ثابت AVTask *a, ثابت AVTask *b);

    // task is ready for run
    صحيح (*ready)(ثابت AVTask *t, فراغ *user_data);

    // run the task
    صحيح (*run)(AVTask *t, فراغ *local_context, فراغ *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *callbacks, صحيح thread_عدد);

/**
 * Free executor
 * @param e  pointer to executor
 */
فراغ av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
فراغ av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
