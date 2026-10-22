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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_HWCONTEXT_CUDA_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_HWCONTEXT_CUDA_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "compat/cuda/dynlink_loader.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

ਬਣਤਰ AVCUDADevice_Context_ਅੰਦਰੂਨੀ {
    CudaFunctions *cuda_dl;
    ਪੂਰਨ is_allocated;
    CUdevice cuda_device;
    ਪੂਰਨ flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_cuda_cuarray_elem_ਮਾਪ(CUarray_format fmt)
{
    ਚੋਣ (fmt) {
    ਹਾਲਤ CU_AD_FORMAT_UNSIGNED_INT8:
    ਹਾਲਤ CU_AD_FORMAT_SIGNED_INT8:   ਵਾਪਸ 1;
    ਹਾਲਤ CU_AD_FORMAT_UNSIGNED_INT16:
    ਹਾਲਤ CU_AD_FORMAT_SIGNED_INT16:
    ਹਾਲਤ CU_AD_FORMAT_HALF:          ਵਾਪਸ 2;
    ਹਾਲਤ CU_AD_FORMAT_UNSIGNED_INT32:
    ਹਾਲਤ CU_AD_FORMAT_SIGNED_INT32:
    ਹਾਲਤ CU_AD_FORMAT_FLOAT:         ਵਾਪਸ 4;
    ਮੂਲ:                         ਵਾਪਸ 0;
    }
}

#ਜੇ_ਅੰਤ /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
