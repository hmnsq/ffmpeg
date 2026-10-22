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

#اگر_غیر_تعریف_شدہ AVUTIL_SLICETHREAD_H
#تعریف_کرو AVUTIL_SLICETHREAD_H

#شامل "attributes.h"
#شامل "version.h"

قسمتعریف ساخت AVSliceThread AVSliceThread;

/**
 * Create slice threading context.
 * @param pctx slice threading context returned here
 * @param priv private pointer to be passed to callback function
 * @param worker_func callback function to be executed
 * @param main_func special callback function, called from main thread, may be NULL
 * @param nb_threads number of threads, 0 for automatic, must be >= 0
 * @return return number of threads or negative AVERROR on failure
 */
صحیح avpriv_slicethread_create2(AVSliceThread **pctx, خالی *priv,
                               صحیح (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                               صحیح (*main_func)(خالی *priv),
                               صحیح nb_دھاگے);

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
صحیح avpriv_slicethread_execute2(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main);

/**
 * Destroy slice threading context.
 * @param pctx pointer to context
 */
خالی avpriv_slicethread_free(AVSliceThread **pctx);

#اگر LIBAVUTIL_نسخہ_MAJOR < 62
/**
 * @deprecated
 * Wrapper around avpriv_slicethread_create2() for ABI backwards compatibility.
 */
attribute_deprecated
صحیح avpriv_slicethread_create(AVSliceThread **pctx, خالی *priv,
                              خالی (*کارکن_func)(خالی *priv, صحیح jobnr, صحیح threadnr, صحیح nb_jobs, صحیح nb_دھاگے),
                              خالی (*main_func)(خالی *priv),
                              صحیح nb_دھاگے);

/**
 * @deprecated
 * Wrapper around avpriv_slicethread_execute2() for ABI backwards compatibility.
 */
attribute_deprecated
خالی avpriv_slicethread_execute(AVSliceThread *ctx, صحیح nb_jobs, صحیح execute_main);
#اگر_ختم /* LIBAVUTIL_VERSION_MAJOR < 62 */

#اگر_ختم
