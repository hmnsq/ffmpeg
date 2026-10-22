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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVExecutor AVExecutor;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVTask AVTask;

ಸಂರಚನಾ AVTask {
    AVTask *next;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVTaskCallbacks {
    ಶೂನ್ಯ *user_data;

    ಪೂರ್ಣಾಙ್ಕ local_context_size;

    // return 1 if a's priority > b's priority
    ಪೂರ್ಣಾಙ್ಕ (*priority_higher)(ಧ್ರುವ AVTask *a, ಧ್ರುವ AVTask *b);

    // task is ready for run
    ಪೂರ್ಣಾಙ್ಕ (*ready)(ಧ್ರುವ AVTask *t, ಶೂನ್ಯ *user_data);

    // run the task
    ಪೂರ್ಣಾಙ್ಕ (*run)(AVTask *t, ಶೂನ್ಯ *local_context, ಶೂನ್ಯ *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ಧ್ರುವ AVTaskCallbacks *callbacks, ಪೂರ್ಣಾಙ್ಕ thread_ಎಣಿಕೆ);

/**
 * Free executor
 * @param e  pointer to executor
 */
ಶೂನ್ಯ av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
ಶೂನ್ಯ av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
