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

प्रकारव्याख्या संरचना AVExecutor AVExecutor;
प्रकारव्याख्या संरचना AVTask AVTask;

संरचना AVTask {
    AVTask *next;
};

प्रकारव्याख्या संरचना AVTaskCallbacks {
    शून्य *user_data;

    पूर्णांक local_context_size;

    // return 1 if a's priority > b's priority
    पूर्णांक (*priority_higher)(स्थिरांक AVTask *a, स्थिरांक AVTask *b);

    // task is ready for run
    पूर्णांक (*ready)(स्थिरांक AVTask *t, शून्य *user_data);

    // run the task
    पूर्णांक (*run)(AVTask *t, शून्य *local_context, शून्य *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(स्थिरांक AVTaskCallbacks *callbacks, पूर्णांक thread_मोजणी);

/**
 * Free executor
 * @param e  pointer to executor
 */
शून्य av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
शून्य av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
