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

પ્રકારવ્યાખ્યા સંરચના AVExecutor AVExecutor;
પ્રકારવ્યાખ્યા સંરચના AVTask AVTask;

સંરચના AVTask {
    AVTask *next;
};

પ્રકારવ્યાખ્યા સંરચના AVTaskCallbacks {
    શૂન્ય *user_data;

    પૂર્ણાંક local_context_size;

    // return 1 if a's priority > b's priority
    પૂર્ણાંક (*priority_higher)(અચલ AVTask *a, અચલ AVTask *b);

    // task is ready for run
    પૂર્ણાંક (*ready)(અચલ AVTask *t, શૂન્ય *user_data);

    // run the task
    પૂર્ણાંક (*run)(AVTask *t, શૂન્ય *local_context, શૂન્ય *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(અચલ AVTaskCallbacks *callbacks, પૂર્ણાંક thread_ગણતરી);

/**
 * Free executor
 * @param e  pointer to executor
 */
શૂન્ય av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
શૂન્ય av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
