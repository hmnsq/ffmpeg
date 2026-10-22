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

#اگر_غیر_تعریف_شدہ AVUTIL_EXECUTOR_H
#تعریف_کرو AVUTIL_EXECUTOR_H

قسمتعریف ساخت AVExecutor AVExecutor;
قسمتعریف ساخت AVTask AVTask;

ساخت AVTask {
    AVTask *اگلا;
};

قسمتعریف ساخت AVTaskCallbacks {
    خالی *user_ڈیٹا;

    صحیح local_context_سائز;

    // return 1 if a's priority > b's priority
    صحیح (*ترجیح_higher)(ثابت AVTask *a, ثابت AVTask *b);

    // task is ready for run
    صحیح (*ready)(ثابت AVTask *t, خالی *user_ڈیٹا);

    // run the task
    صحیح (*تسلسل)(AVTask *t, خالی *local_context, خالی *user_ڈیٹا);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ثابت AVTaskCallbacks *callbacks, صحیح thread_گنتی);

/**
 * Free executor
 * @param e  pointer to executor
 */
خالی av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
خالی av_executor_execute(AVExecutor *e, AVTask *t);

#اگر_ختم //AVUTIL_EXECUTOR_H
