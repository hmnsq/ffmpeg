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


#अगर_अघोषित AVUTIL_HWCONTEXT_CUDA_INTERNAL_H
#घोषणा AVUTIL_HWCONTEXT_CUDA_INTERNAL_H

#समावेश "compat/cuda/dynlink_loader.h"
#समावेश "hwcontext_cuda.h"

/**
 * @file
 * FFmpeg internal API for CUDA.
 */

काष्ठा AVCUDADeviceContextInternal {
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
अटल अंतरभूत पूर्णांक ff_cuda_cuarray_elem_आकार(CUarray_format fmt)
{
    चयन (fmt) {
    हाल CU_AD_FORMAT_UNSIGNED_INT8:
    हाल CU_AD_FORMAT_SIGNED_INT8:   वापस 1;
    हाल CU_AD_FORMAT_UNSIGNED_INT16:
    हाल CU_AD_FORMAT_SIGNED_INT16:
    हाल CU_AD_FORMAT_HALF:          वापस 2;
    हाल CU_AD_FORMAT_UNSIGNED_INT32:
    हाल CU_AD_FORMAT_SIGNED_INT32:
    हाल CU_AD_FORMAT_FLOAT:         वापस 4;
    शेष:                         वापस 0;
    }
}

#पूर्ण_अगर /* AVUTIL_HWCONTEXT_CUDA_INTERNAL_H */
