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

typedef sa_nracanaa AVExecutor AVExecutor;
typedef sa_nracanaa AVTask AVTask;

sa_nracanaa AVTask {
    AVTask *next;
};

typedef sa_nracanaa AVTaskCallbacks {
    void *user_data;

    ចំនួនគត់ local_context_size;

    // return 1 if a's priority > b's priority
    ចំនួនគត់ (*priority_higher)(const AVTask *a, const AVTask *b);

    // task is ready for run
    ចំនួនគត់ (*ready)(const AVTask *t, void *user_data);

    // run the task
    ចំនួនគត់ (*run)(AVTask *t, void *local_context, void *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(const AVTaskCallbacks *callbacks, ចំនួនគត់ thread_count);

/**
 * Free executor
 * @param e  pointer to executor
 */
void av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
void av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
