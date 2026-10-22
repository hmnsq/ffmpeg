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


#اگر_غیر_تعریف_شدہ AVUTIL_CUDA_CHECK_H
#تعریف_کرو AVUTIL_CUDA_CHECK_H

#شامل "compat/cuda/dynlink_loader.h"
#شامل "error.h"

قسمتعریف CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, ثابت حرف** pstr);
قسمتعریف CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, ثابت حرف** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
ساکن اندرونی صحیح ff_cuda_check(خالی *avctx,
                                خالی *cuGetErrorName_fn, خالی *cuGetErrorString_fn,
                                CUresult err, ثابت حرف *func)
{
    ثابت حرف *err_name;
    ثابت حرف *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    اگر (err == CUDA_SUCCESS)
        واپس 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    اگر (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    واپس AVERROR_EXTERNAL;
}

/**
 * Convenience wrapper for ff_cuda_check when directly linking libcuda.
 */

#تعریف_کرو FF_CUDA_CHECK(avclass, x) ff_cuda_check(avclass, cuGetErrorName, cuGetErrorString, (x), #x)

/**
 * Convenience wrapper for ff_cuda_check when dynamically loading cuda symbols.
 */

#تعریف_کرو FF_CUDA_CHECK_DL(avclass, cudl, x) ff_cuda_check(avclass, cudl->cuGetErrorName, cudl->cuGetErrorString, (x), #x)

#اگر_ختم /* AVUTIL_CUDA_CHECK_H */
