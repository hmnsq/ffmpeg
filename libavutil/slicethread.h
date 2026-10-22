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

#अगर_अघोषित AVUTIL_SLICETHREAD_H
#घोषणा AVUTIL_SLICETHREAD_H

#समावेश "attributes.h"
#समावेश "version.h"

प्रकार काष्ठा AVSliceThread AVSliceThread;

/**
 * Create slice threading context.
 * @param pctx slice threading context returned here
 * @param priv private pointer to be passed to callback function
 * @param worker_func callback function to be executed
 * @param main_func special callback function, called from main thread, may be NULL
 * @param nb_threads number of threads, 0 for automatic, must be >= 0
 * @return return number of threads or negative AVERROR on failure
 */
पूर्णांक avpriv_slicethread_create2(AVSliceThread **pctx, व्योम *priv,
                               पूर्णांक (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                               पूर्णांक (*main_func)(व्योम *priv),
                               पूर्णांक nb_threads);

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
पूर्णांक avpriv_slicethread_execute2(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main);

/**
 * Destroy slice threading context.
 * @param pctx pointer to context
 */
व्योम avpriv_slicethread_free(AVSliceThread **pctx);

#अगर LIBAVUTIL_VERSION_MAJOR < 62
/**
 * @deprecated
 * Wrapper around avpriv_slicethread_create2() for ABI backwards compatibility.
 */
attribute_deprecated
पूर्णांक avpriv_slicethread_create(AVSliceThread **pctx, व्योम *priv,
                              व्योम (*worker_func)(व्योम *priv, पूर्णांक jobnr, पूर्णांक threadnr, पूर्णांक nb_jobs, पूर्णांक nb_threads),
                              व्योम (*main_func)(व्योम *priv),
                              पूर्णांक nb_threads);

/**
 * @deprecated
 * Wrapper around avpriv_slicethread_execute2() for ABI backwards compatibility.
 */
attribute_deprecated
व्योम avpriv_slicethread_execute(AVSliceThread *ctx, पूर्णांक nb_jobs, पूर्णांक execute_main);
#पूर्ण_अगर /* LIBAVUTIL_VERSION_MAJOR < 62 */

#पूर्ण_अगर
