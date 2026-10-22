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


#ifndef AVUTIL_HWCONTEXT_CUDA_INTERNAL_H
#define AVUTIL_HWCONTEXT_CUDA_INTERNAL_H

#ضمن "compat/cuda/dynlink_loader.h"
#ضمن "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

بنية AVCUDADeviceContextInternal {
    CudaFunctions *cuda_dl;
    صحيح is_allocated;
    CUdevice cuda_device;
    صحيح flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
ساكن مضمن صحيح ff_cuda_cuarray_elem_size(CUarray_format fmt)
{
    بدل (fmt) {
    حالة CU_AD_FORMAT_UNSIGNED_INT8:
    حالة CU_AD_FORMAT_SIGNED_INT8:   ܦܢܐ 1;
    حالة CU_AD_FORMAT_UNSIGNED_INT16:
    حالة CU_AD_FORMAT_SIGNED_INT16:
    حالة CU_AD_FORMAT_HALF:          ܦܢܐ 2;
    حالة CU_AD_FORMAT_UNSIGNED_INT32:
    حالة CU_AD_FORMAT_SIGNED_INT32:
    حالة CU_AD_FORMAT_FLOAT:         ܦܢܐ 4;
    افتراضي:                         ܦܢܐ 0;
    }
}

#endif /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
