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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVExecutor AVExecutor;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVTask AVTask;

ସଂରଚନା AVTask {
    AVTask *next;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVTaskCallbacks {
    ଶୂନ୍ୟ *user_data;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା local_context_size;

    // return 1 if a's priority > b's priority
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*priority_higher)(ଅଚଳ AVTask *a, ଅଚଳ AVTask *b);

    // task is ready for run
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*ready)(ଅଚଳ AVTask *t, ଶୂନ୍ୟ *user_data);

    // run the task
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*run)(AVTask *t, ଶୂନ୍ୟ *local_context, ଶୂନ୍ୟ *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ଅଚଳ AVTaskCallbacks *callbacks, ପୂର୍ଣ୍ଣସଂଖ୍ୟା thread_ଗଣନା);

/**
 * Free executor
 * @param e  pointer to executor
 */
ଶୂନ୍ୟ av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
ଶୂନ୍ୟ av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
