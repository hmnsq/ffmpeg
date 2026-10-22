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

#অন্তর্ভাব "compat/cuda/dynlink_loader.h"
#অন্তর্ভাব "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

কাঠামো AVCUDADeviceContextInternal {
    CudaFunctions *cuda_dl;
    পূর্ণসংখ্যা is_allocated;
    CUdevice cuda_device;
    পূর্ণসংখ্যা flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_cuda_cuarray_elem_আকার(CUarray_format fmt)
{
    নির্বাচন (fmt) {
    ক্ষেত্র CU_AD_FORMAT_UNSIGNED_INT8:
    ক্ষেত্র CU_AD_FORMAT_SIGNED_INT8:   ফেরত 1;
    ক্ষেত্র CU_AD_FORMAT_UNSIGNED_INT16:
    ক্ষেত্র CU_AD_FORMAT_SIGNED_INT16:
    ক্ষেত্র CU_AD_FORMAT_HALF:          ফেরত 2;
    ক্ষেত্র CU_AD_FORMAT_UNSIGNED_INT32:
    ক্ষেত্র CU_AD_FORMAT_SIGNED_INT32:
    ক্ষেত্র CU_AD_FORMAT_FLOAT:         ফেরত 4;
    পূর্বনির্ধারিত:                         ফেরত 0;
    }
}

#endif /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
