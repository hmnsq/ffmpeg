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

#अगर_अघोषित AVUTIL_EXECUTOR_H
#घोषणा AVUTIL_EXECUTOR_H

प्रकार काष्ठा AVExecutor AVExecutor;
प्रकार काष्ठा AVTask AVTask;

काष्ठा AVTask {
    AVTask *अग्र;
};

प्रकार काष्ठा AVTaskCallbacks {
    व्योम *user_तथ्य;

    पूर्णांक local_context_आकार;

    // return 1 if a's priority > b's priority
    पूर्णांक (*priority_higher)(स्थिर AVTask *a, स्थिर AVTask *b);

    // task is ready for run
    पूर्णांक (*ready)(स्थिर AVTask *t, व्योम *user_तथ्य);

    // run the task
    पूर्णांक (*run)(AVTask *t, व्योम *local_context, व्योम *user_तथ्य);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(स्थिर AVTaskCallbacks *callbacks, पूर्णांक thread_गिनती);

/**
 * Free executor
 * @param e  pointer to executor
 */
व्योम av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
व्योम av_executor_execute(AVExecutor *e, AVTask *t);

#पूर्ण_अगर //AVUTIL_EXECUTOR_H
