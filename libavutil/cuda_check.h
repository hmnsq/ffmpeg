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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_CUDA_CHECK_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_CUDA_CHECK_H

#ಅನ್ತರ್ಭಾವ "compat/cuda/dynlink_loader.h"
#ಅನ್ತರ್ಭಾವ "error.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CUresult CUDAAPI cuda_check_GetErrorName(CUresult error, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ** pstr);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CUresult CUDAAPI cuda_check_GetErrorString(CUresult error, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ** pstr);

/**
 * Wrap a CUDA function call and print error information if it fails.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cuda_check(ಶೂನ್ಯ *avctx,
                                ಶೂನ್ಯ *cuGetErrorName_fn, ಶೂನ್ಯ *cuGetErrorString_fn,
                                CUresult err, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *func)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *err_name;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *err_string;

    av_log(avctx, AV_LOG_TRACE, "Calling %s\n", func);

    ಆದರೆ (err == CUDA_SUCCESS)
        ಹಿಂತಿರುಗಿ 0;

    ((cuda_check_GetErrorName *)cuGetErrorName_fn)(err, &err_name);
    ((cuda_check_GetErrorString *)cuGetErrorString_fn)(err, &err_string);

    av_log(avctx, AV_LOG_ERROR, "%s failed", func);
    ಆದರೆ (err_name && err_string)
        av_log(avctx, AV_LOG_ERROR, " -> %s: %s", err_name, err_string);
    av_log(avctx, AV_LOG_ERROR, "\n");

    ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
}

/**
 * Convenience wrapper for ff_cuda_check when directly linking libcuda.
 */

#ವ್ಯಾಖ್ಯಾನಿಸು FF_CUDA_CHECK(avclass, x) ff_cuda_check(avclass, cuGetErrorName, cuGetErrorString, (x), #x)

/**
 * Convenience wrapper for ff_cuda_check when dynamically loading cuda symbols.
 */

#ವ್ಯಾಖ್ಯಾನಿಸು FF_CUDA_CHECK_DL(avclass, cudl, x) ff_cuda_check(avclass, cudl->cuGetErrorName, cudl->cuGetErrorString, (x), #x)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CUDA_CHECK_H */
