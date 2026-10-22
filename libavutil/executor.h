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

#నిర్వచితం_కాకపోతే AVUTIL_EXECUTOR_H
#నిర్వచించు AVUTIL_EXECUTOR_H

రకనిర్వచనం నిర్మాణం AVExecutor AVExecutor;
రకనిర్వచనం నిర్మాణం AVTask AVTask;

నిర్మాణం AVTask {
    AVTask *తదుపరి;
};

రకనిర్వచనం నిర్మాణం AVTaskCallbacks {
    శూన్య *user_దత్తాంశం;

    పూర్ణాంకం local_context_కొలత;

    // return 1 if a's priority > b's priority
    పూర్ణాంకం (*ప్రాధాన్యత_higher)(స్థిరరాశి AVTask *a, స్థిరరాశి AVTask *b);

    // task is ready for run
    పూర్ణాంకం (*ready)(స్థిరరాశి AVTask *t, శూన్య *user_దత్తాంశం);

    // run the task
    పూర్ణాంకం (*నిరంతరం)(AVTask *t, శూన్య *local_context, శూన్య *user_దత్తాంశం);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(స్థిరరాశి AVTaskCallbacks *callbacks, పూర్ణాంకం thread_లెక్క);

/**
 * Free executor
 * @param e  pointer to executor
 */
శూన్య av_executor_free(AVExecutor **e);

/**
 * Add task to executor
 * @param e pointer to executor
 * @param t pointer to task. If NULL, it will wakeup one work thread
 */
శూన్య av_executor_execute(AVExecutor *e, AVTask *t);

#అయితే_ముగింపు //AVUTIL_EXECUTOR_H
