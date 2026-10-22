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


#अगर_अघोषित AVUTIL_CUDA_CHECK_H
#घोषणा AVUTIL_CUDA_CHECK_H

#समावेश "compat/cuda/dynlink_loader.h"
#समावेश "error.h"

प्रकार CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, स्थिर अक्षर** pstr);
प्रकार CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, स्थिर अक्षर** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
अटल अंतरभूत पूर्णांक ff_cuda_check(व्योम *avctx,
                                व्योम *cuGetErrorName_fn, व्योम *cuGetErrorString_fn,
                                CUresult err, स्थिर अक्षर *func)
{
    स्थिर अक्षर *err_name;
    स्थिर अक्षर *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    अगर (err == CUDA_SUCCESS)
        वापस 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    अगर (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    वापस AVERROR_EXTERNAL;
}

/**
 * Convenience wrapper for ff_cuda_check when directly linking libcuda.
 */

#घोषणा FF_CUDA_CHECK(avclass, x) ff_cuda_check(avclass, cuGetErrorName, cuGetErrorString, (x), #x)

/**
 * Convenience wrapper for ff_cuda_check when dynamically loading cuda symbols.
 */

#घोषणा FF_CUDA_CHECK_DL(avclass, cudl, x) ff_cuda_check(avclass, cudl->cuGetErrorName, cudl->cuGetErrorString, (x), #x)

#पूर्ण_अगर /* AVUTIL_CUDA_CHECK_H */
