/*
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

#ifndef AVUTIL_SLICETHREAD_H
#define AVUTIL_SLICETHREAD_H

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "version.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVSliceThread AVSliceThread;

/**
 * Create slice threading context.
 * @param pctx slice threading context returned here
 * @param priv private pointer to be passed to callback function
 * @param worker_func callback function to be executed
 * @param main_func special callback function, called from main thread, may be NULL
 * @param nb_threads number of threads, 0 for automatic, must be >= 0
 * @return return number of threads or negative AVERROR on failure
 */
ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create2(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                               ಪೂರ್ಣಾಙ್ಕ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                               ಪೂರ್ಣಾಙ್ಕ (*main_func)(ಶೂನ್ಯ *priv),
                               ಪೂರ್ಣಾಙ್ಕ nb_threads);

/**
 * Execute slice threading. If any job returns a nonzero value,
 * all remaining jobs will be aborted and that value returned.
 *
 * If `main_func` itself returns a nonzero value, that value is guaranteed
 * to be returned, even if a worker thread returns a nonzero value first.
 *
 * @param ctx slice threading context
 * @param nb_jobs number of jobs, must be > 0
 * @param execute_main also execute main_func
 * @return 0 on success, else first seen return value
 */
ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_execute2(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main);

/**
 * Destroy slice threading context.
 * @param pctx pointer to context
 */
ಶೂನ್ಯ avpriv_slicethread_free(AVSliceThread **pctx);

#ಯದಿ LIBAVUTIL_VERSION_MAJOR < 62
/**
 * @deprecated
 * Wrapper around avpriv_slicethread_create2() for ABI backwards compatibility.
 */
attribute_deprecated
ಪೂರ್ಣಾಙ್ಕ avpriv_slicethread_create(AVSliceThread **pctx, ಶೂನ್ಯ *priv,
                              ಶೂನ್ಯ (*worker_func)(ಶೂನ್ಯ *priv, ಪೂರ್ಣಾಙ್ಕ jobnr, ಪೂರ್ಣಾಙ್ಕ threadnr, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ nb_threads),
                              ಶೂನ್ಯ (*main_func)(ಶೂನ್ಯ *priv),
                              ಪೂರ್ಣಾಙ್ಕ nb_threads);

/**
 * @deprecated
 * Wrapper around avpriv_slicethread_execute2() for ABI backwards compatibility.
 */
attribute_deprecated
ಶೂನ್ಯ avpriv_slicethread_execute(AVSliceThread *ctx, ಪೂರ್ಣಾಙ್ಕ nb_jobs, ಪೂರ್ಣಾಙ್ಕ execute_main);
#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif
