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

#অন্তর্ভাব "compat/cuda/dynlink_loader.h"
#অন্তর্ভাব "error.h"

প্রকারনির্দেশ CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, ধ্রুব বর্ণ** pstr);
প্রকারনির্দেশ CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, ধ্রুব বর্ণ** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
স্থির অন্তঃস্থ পূর্ণাঙ্ক ff_cuda_check(শূন্য *avctx,
                                শূন্য *cuGetErrorName_fn, শূন্য *cuGetErrorString_fn,
                                CUresult err, ধ্রুব বর্ণ *func)
{
    ধ্রুব বর্ণ *err_name;
    ধ্রুব বর্ণ *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    যদি (err == CUDA_SUCCESS)
        প্রত্যাগম 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    যদি (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    প্রত্যাগম AVERROR_EXTERNAL;
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
