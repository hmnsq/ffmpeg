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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_CUDA_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_CUDA_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ "compat/cuda/dynlink_loader.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

ರಚನೆ AVCUDADevice_Context_ಆಂತರಿಕ {
    CudaFunctions *cuda_dl;
    ಪೂರ್ಣಾಂಕ is_allocated;
    CUdevice cuda_device;
    ಪೂರ್ಣಾಂಕ flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_cuda_cuarray_elem_ಗಾತ್ರ(CUarray_format fmt)
{
    ಆಯ್ಕೆ (fmt) {
    ಸ್ಥಿತಿ CU_AD_FORMAT_UNSIGNED_INT8:
    ಸ್ಥಿತಿ CU_AD_FORMAT_SIGNED_INT8:   ಹಿಂತಿರುಗಿ 1;
    ಸ್ಥಿತಿ CU_AD_FORMAT_UNSIGNED_INT16:
    ಸ್ಥಿತಿ CU_AD_FORMAT_SIGNED_INT16:
    ಸ್ಥಿತಿ CU_AD_FORMAT_HALF:          ಹಿಂತಿರುಗಿ 2;
    ಸ್ಥಿತಿ CU_AD_FORMAT_UNSIGNED_INT32:
    ಸ್ಥಿತಿ CU_AD_FORMAT_SIGNED_INT32:
    ಸ್ಥಿತಿ CU_AD_FORMAT_FLOAT:         ಹಿಂತಿರುಗಿ 4;
    ಪೂರ್ವನಿಯೋಜಿತ:                         ಹಿಂತಿರುಗಿ 0;
    }
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
