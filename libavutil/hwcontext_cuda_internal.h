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


#నిర్వచితం_కాకపోతే AVUTIL_HWCONTEXT_CUDA_అంతర్గత_H
#నిర్వచించు AVUTIL_HWCONTEXT_CUDA_అంతర్గత_H

#అన్తర్భావ "compat/cuda/dynlink_loader.h"
#అన్తర్భావ "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

నిర్మాణం AVCUDADevice_Context_అంతర్గత {
    CudaFunctions *cuda_dl;
    పూర్ణాంకం is_allocated;
    CUdevice cuda_device;
    పూర్ణాంకం flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
స్థిర అంతఃవరుస పూర్ణాంకం ff_cuda_cuarray_elem_కొలత(CUarray_format fmt)
{
    ఎంపిక (fmt) {
    స్థితి CU_AD_FORMAT_UNSIGNED_INT8:
    స్థితి CU_AD_FORMAT_SIGNED_INT8:   తిరిగి 1;
    స్థితి CU_AD_FORMAT_UNSIGNED_INT16:
    స్థితి CU_AD_FORMAT_SIGNED_INT16:
    స్థితి CU_AD_FORMAT_HALF:          తిరిగి 2;
    స్థితి CU_AD_FORMAT_UNSIGNED_INT32:
    స్థితి CU_AD_FORMAT_SIGNED_INT32:
    స్థితి CU_AD_FORMAT_FLOAT:         తిరిగి 4;
    అప్రమేయ:                         తిరిగి 0;
    }
}

#అయితే_ముగింపు /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
