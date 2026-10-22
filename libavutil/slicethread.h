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

#నిర్వచితం_కాకపోతే AVUTIL_SLICETHREAD_H
#నిర్వచించు AVUTIL_SLICETHREAD_H

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "version.h"

రకనిర్వచనం నిర్మాణం AVSliceThread AVSliceThread;

/**
 * Create slice threading context.
 * @param pctx slice threading context returned here
 * @param priv private pointer to be passed to callback function
 * @param worker_func callback function to be executed
 * @param main_func special callback function, called from main thread, may be NULL
 * @param nb_threads number of threads, 0 for automatic, must be >= 0
 * @return return number of threads or negative AVERROR on failure
 */
పూర్ణాంకం avpriv_slicethread_create2(AVSliceThread **pctx, శూన్య *priv,
                               పూర్ణాంకం (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                               పూర్ణాంకం (*main_func)(శూన్య *priv),
                               పూర్ణాంకం nb_దారాలు);

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
పూర్ణాంకం avpriv_slicethread_execute2(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main);

/**
 * Destroy slice threading context.
 * @param pctx pointer to context
 */
శూన్య avpriv_slicethread_free(AVSliceThread **pctx);

#ఒకవేళ LIBAVUTIL_సంస్కరణ_MAJOR < 62
/**
 * @deprecated
 * Wrapper around avpriv_slicethread_create2() for ABI backwards compatibility.
 */
attribute_deprecated
పూర్ణాంకం avpriv_slicethread_create(AVSliceThread **pctx, శూన్య *priv,
                              శూన్య (*కార్మికుడు_func)(శూన్య *priv, పూర్ణాంకం jobnr, పూర్ణాంకం threadnr, పూర్ణాంకం nb_jobs, పూర్ణాంకం nb_దారాలు),
                              శూన్య (*main_func)(శూన్య *priv),
                              పూర్ణాంకం nb_దారాలు);

/**
 * @deprecated
 * Wrapper around avpriv_slicethread_execute2() for ABI backwards compatibility.
 */
attribute_deprecated
శూన్య avpriv_slicethread_execute(AVSliceThread *ctx, పూర్ణాంకం nb_jobs, పూర్ణాంకం execute_main);
#అయితే_ముగింపు /* LIBAVUTIL_VERSION_MAJOR < 62 */

#అయితే_ముగింపు
