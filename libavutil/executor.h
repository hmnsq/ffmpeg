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

തരനിർവചനം ഘടന AVExecutor AVExecutor;
തരനിർവചനം ഘടന AVTask AVTask;

ഘടന AVTask {
    AVTask *next;
};

തരനിർവചനം ഘടന AVTaskCallbacks {
    ശൂന്യം *user_data;

    പൂർണ്ണസംഖ്യ local_context_size;

    // return 1 if a's priority > b's priority
    പൂർണ്ണസംഖ്യ (*priority_higher)(സ്ഥിരം AVTask *a, സ്ഥിരം AVTask *b);

    // task is ready for run
    പൂർണ്ണസംഖ്യ (*ready)(സ്ഥിരം AVTask *t, ശൂന്യം *user_data);

    // run the task
    പൂർണ്ണസംഖ്യ (*run)(AVTask *t, ശൂന്യം *local_context, ശൂന്യം *user_data);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(സ്ഥിരം AVTaskCallbacks *callbacks, പൂർണ്ണസംഖ്യ thread_എണ്ണം);

/**
 * Free executor
 * @param e  pointer to executor
 */
ശൂന്യം av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
ശൂന്യം av_executor_execute(AVExecutor *e, AVTask *t);

#endif //AVUTIL_EXECUTOR_H
