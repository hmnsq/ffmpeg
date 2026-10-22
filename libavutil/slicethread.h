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

#ضمن "attributes.h"
#ضمن "version.h"

تعريفنوع بنية AVSliceThread AVSliceThread;

/**
 * Create slice threading context.
 * @param pctx slice threading context returned here
 * @param priv private pointer to be passed to callback function
 * @param worker_func callback function to be executed
 * @param main_func special callback function, called from main thread, may be NULL
 * @param nb_threads number of threads, 0 for automatic, must be >= 0
 * @return return number of threads or negative AVERROR on failure
 */
صحيح avpriv_slicethread_create2(AVSliceThread **pctx, فراغ *priv,
                               صحيح (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                               صحيح (*main_func)(فراغ *priv),
                               صحيح nb_threads);

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
صحيح avpriv_slicethread_execute2(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main);

/**
 * Destroy slice threading context.
 * @param pctx pointer to context
 */
فراغ avpriv_slicethread_free(AVSliceThread **pctx);

#إذا LIBAVUTIL_VERSION_MAJOR < 62
/**
 * @deprecated
 * Wrapper around avpriv_slicethread_create2() for ABI backwards compatibility.
 */
attribute_deprecated
صحيح avpriv_slicethread_create(AVSliceThread **pctx, فراغ *priv,
                              فراغ (*worker_func)(فراغ *priv, صحيح jobnr, صحيح threadnr, صحيح nb_jobs, صحيح nb_threads),
                              فراغ (*main_func)(فراغ *priv),
                              صحيح nb_threads);

/**
 * @deprecated
 * Wrapper around avpriv_slicethread_execute2() for ABI backwards compatibility.
 */
attribute_deprecated
فراغ avpriv_slicethread_execute(AVSliceThread *ctx, صحيح nb_jobs, صحيح execute_main);
#endif /* LIBAVUTIL_VERSION_MAJOR < 62 */

#endif
