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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_EXECUTOR_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_EXECUTOR_H

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVExecutor AVExecutor;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVTask AVTask;

ರಚನೆ AVTask {
    AVTask *ಮುಂದಿನ;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVTaskCallbacks {
    ಶೂನ್ಯ *user_ದತ್ತಾಂಶ;

    ಪೂರ್ಣಾಂಕ local_context_ಗಾತ್ರ;

    // return 1 if a's priority > b's priority
    ಪೂರ್ಣಾಂಕ (*ಆದ್ಯತೆ_higher)(ಸ್ಥಿರಾಂಕ AVTask *a, ಸ್ಥಿರಾಂಕ AVTask *b);

    // task is ready for run
    ಪೂರ್ಣಾಂಕ (*ready)(ಸ್ಥಿರಾಂಕ AVTask *t, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ);

    // run the task
    ಪೂರ್ಣಾಂಕ (*ಸತತ)(AVTask *t, ಶೂನ್ಯ *local_context, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ);
} AVTaskCallbacks;

/**
 * Alloc executor
 * @param callbacks callback structure for executor
 * @param thread_count worker thread number, 0 for run on caller's thread directly
 * @return return the executor
 */
AVExecutor* av_executor_alloc(ಸ್ಥಿರಾಂಕ AVTaskCallbacks *callbacks, ಪೂರ್ಣಾಂಕ thread_ಎಣಿಕೆ);

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

#ಆದರೆ_ಅಂತ್ಯ //AVUTIL_EXECUTOR_H
