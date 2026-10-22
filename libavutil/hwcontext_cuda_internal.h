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


#اگر_غیر_تعریف_شدہ AVUTIL_HWCONTEXT_CUDA_اندرونی_H
#تعریف_کرو AVUTIL_HWCONTEXT_CUDA_اندرونی_H

#شامل "compat/cuda/dynlink_loader.h"
#شامل "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

ساخت AVCUDADevice_Context_اندرونی {
    CudaFunctions *cuda_dl;
    صحیح is_allocated;
    CUdevice cuda_device;
    صحیح flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
ساکن اندرونی صحیح ff_cuda_cuarray_elem_سائز(CUarray_format fmt)
{
    انتخاب (fmt) {
    حالت CU_AD_FORMAT_UNSIGNED_INT8:
    حالت CU_AD_FORMAT_SIGNED_INT8:   واپس 1;
    حالت CU_AD_FORMAT_UNSIGNED_INT16:
    حالت CU_AD_FORMAT_SIGNED_INT16:
    حالت CU_AD_FORMAT_HALF:          واپس 2;
    حالت CU_AD_FORMAT_UNSIGNED_INT32:
    حالت CU_AD_FORMAT_SIGNED_INT32:
    حالت CU_AD_FORMAT_FLOAT:         واپس 4;
    طےشدہ:                         واپس 0;
    }
}

#اگر_ختم /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
