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

#अन्तर्भाव "compat/cuda/dynlink_loader.h"
#अन्तर्भाव "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

संरचना AVCUDADeviceContextInternal {
    CudaFunctions *cuda_dl;
    पूर्णांक is_allocated;
    CUdevice cuda_device;
    पूर्णांक flags;
};

/**
 * Return the element size in bytes for a CUarray_format, or 0 for unknown.
 *
 * Used to compute frame->linesize[] for CUarray frames (block-linear).
 * Callers that need a fallback should treat a 0 return as an error.
 */
स्थिर ओळीत पूर्णांक ff_cuda_cuarray_elem_size(CUarray_format fmt)
{
    निवड (fmt) {
    स्थिती CU_AD_FORMAT_UNSIGNED_INT8:
    स्थिती CU_AD_FORMAT_SIGNED_INT8:   परत 1;
    स्थिती CU_AD_FORMAT_UNSIGNED_INT16:
    स्थिती CU_AD_FORMAT_SIGNED_INT16:
    स्थिती CU_AD_FORMAT_HALF:          परत 2;
    स्थिती CU_AD_FORMAT_UNSIGNED_INT32:
    स्थिती CU_AD_FORMAT_SIGNED_INT32:
    स्थिती CU_AD_FORMAT_FLOAT:         परत 4;
    पूर्वनिर्धारित:                         परत 0;
    }
}

#endif /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
