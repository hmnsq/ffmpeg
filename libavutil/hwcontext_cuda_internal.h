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

#ଅନ୍ତର୍ଭାଵ "compat/cuda/dynlink_loader.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

ସଂରଚନା AVCUDADeviceContextInternal {
    CudaFunctions *cuda_dl;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_allocated;
    CUdevice cuda_device;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_cuda_cuarray_elem_size(CUarray_format fmt)
{
    ବାଛ (fmt) {
    ସ୍ଥିତି CU_AD_FORMAT_UNSIGNED_INT8:
    ସ୍ଥିତି CU_AD_FORMAT_SIGNED_INT8:   ଫେରନ୍ତୁ 1;
    ସ୍ଥିତି CU_AD_FORMAT_UNSIGNED_INT16:
    ସ୍ଥିତି CU_AD_FORMAT_SIGNED_INT16:
    ସ୍ଥିତି CU_AD_FORMAT_HALF:          ଫେରନ୍ତୁ 2;
    ସ୍ଥିତି CU_AD_FORMAT_UNSIGNED_INT32:
    ସ୍ଥିତି CU_AD_FORMAT_SIGNED_INT32:
    ସ୍ଥିତି CU_AD_FORMAT_FLOAT:         ଫେରନ୍ତୁ 4;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                         ଫେରନ୍ତୁ 0;
    }
}

#endif /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
