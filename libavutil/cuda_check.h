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

#अन्तर्भाव "compat/cuda/dynlink_loader.h"
#अन्तर्भाव "error.h"

प्रकारनिर्देश CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, ध्रुव वर्ण** pstr);
प्रकारनिर्देश CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, ध्रुव वर्ण** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
स्थिर अन्तःस्थ पूर्णाङ्क ff_cuda_check(शून्य *avctx,
                                शून्य *cuGetErrorName_fn, शून्य *cuGetErrorString_fn,
                                CUresult err, ध्रुव वर्ण *func)
{
    ध्रुव वर्ण *err_name;
    ध्रुव वर्ण *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    यदि (err == CUDA_SUCCESS)
        प्रत्यागम 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    यदि (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    प्रत्यागम AVERROR_EXTERNAL;
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
