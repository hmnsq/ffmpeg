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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_CUDA_CHECK_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_CUDA_CHECK_H

#ਅਨ੍ਤਰ੍ਭਾਵ "compat/cuda/dynlink_loader.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, ਅਚਲ ਅੱਖਰ** pstr);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, ਅਚਲ ਅੱਖਰ** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cuda_check(ਖਾਲੀ *avctx,
                                ਖਾਲੀ *cuGetErrorName_fn, ਖਾਲੀ *cuGetErrorString_fn,
                                CUresult err, ਅਚਲ ਅੱਖਰ *func)
{
    ਅਚਲ ਅੱਖਰ *err_name;
    ਅਚਲ ਅੱਖਰ *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    ਜੇ (err == CUDA_SUCCESS)
        ਵਾਪਸ 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    ਜੇ (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    ਵਾਪਸ AVERROR_EXTERNAL;
}

/**
 * Convenience wrapper for ff_cuda_check when directly linking libcuda.
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_CUDA_CHECK(avclass, x) ff_cuda_check(avclass, cuGetErrorName, cuGetErrorString, (x), #x)

/**
 * Convenience wrapper for ff_cuda_check when dynamically loading cuda symbols.
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_CUDA_CHECK_DL(avclass, cudl, x) ff_cuda_check(avclass, cudl->cuGetErrorName, cudl->cuGetErrorString, (x), #x)

#ਜੇ_ਅੰਤ /* AVUTIL_CUDA_CHECK_H */
