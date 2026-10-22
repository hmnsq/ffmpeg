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


#ifndef AVUTIL_CUDA_CHECK_H
#define AVUTIL_CUDA_CHECK_H

#அந்தர்பாவ "compat/cuda/dynlink_loader.h"
#அந்தர்பாவ "error.h"

வகைவரை CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, மாறிலி எழுத்து** pstr);
வகைவரை CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, மாறிலி எழுத்து** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
நிலையான உள்வரி முழு ff_cuda_check(வெறுமை *avctx,
                                வெறுமை *cuGetErrorName_fn, வெறுமை *cuGetErrorString_fn,
                                CUresult err, மாறிலி எழுத்து *func)
{
    மாறிலி எழுத்து *err_name;
    மாறிலி எழுத்து *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    எனில் (err == CUDA_SUCCESS)
        திரும்பு 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    எனில் (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    திரும்பு AVERROR_EXTERNAL;
}

/**
 * Convenience wrapper for ff_cuda_check when directly linking libcuda.
 */

#define FF_CUDA_CHECK(avclass, x) ff_cuda_check(avclass, cuGetErrorName, cuGetErrorString, (x), #x)

/**
 * Convenience wrapper for ff_cuda_check when dynamically loading cuda symbols.
 */

#define FF_CUDA_CHECK_DL(avclass, cudl, x) ff_cuda_check(avclass, cudl->cuGetErrorName, cudl->cuGetErrorString, (x), #x)

#endif /* AVUTIL_CUDA_CHECK_H */
