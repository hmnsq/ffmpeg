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


#अगर_अघोषित AVUTIL_HWCONTEXT_CUDA_H
#घोषणा AVUTIL_HWCONTEXT_CUDA_H

#अगर_अघोषित CUDA_VERSION
#समावेश <cuda.h>
#पूर्ण_अगर

#समावेश <stdint.h>

#समावेश "pixfmt.h"

/**
 * @file
 * An API-specific header for AV_HWDEVICE_TYPE_CUDA.
 *
 * This API supports dynamic frame pools. AVHWFramesContext.pool must return
 * AVBufferRefs whose data pointer is a CUdeviceptr.
 */

प्रकार काष्ठा AVCUDADeviceContextInternal AVCUDADeviceContextInternal;

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
प्रकार काष्ठा AVCUDADeviceContext {
    CUcontext cuda_ctx;
    CUstream stream;
    AVCUDADeviceContextInternal *internal;
} AVCUDADeviceContext;

/**
 * CUDA frame descriptor for pool allocation of AV_PIX_FMT_CUARRAY frames.
 *
 * In user-allocated pools, AVHWFramesContext.pool must return AVBufferRefs
 * with the data pointer pointing at an object of this type describing the
 * planes of the frame.
 *
 * This has no use outside of custom allocation, and AVFrame AVBufferRef do not
 * necessarily point to an instance of this struct.
 */
प्रकार काष्ठा AVCUDAArrayFrameDescriptor {
    /**
     * The CUarray containing the frame data.
     *
     * Normally stored in AVFrame.data[0].
     */
    CUarray array;

    /**
     * The index into AVCUDAFramesContext.cuarray_surfaces, or 0 if not applicable.
     *
     * Normally stored in AVFrame.data[1] (cast from intptr_t).
     */
    intptr_t सूचकांक;
} AVCUDAArrayFrameDescriptor;

/**
 * This struct is allocated as AVHWFramesContext.hwctx
 */
प्रकार काष्ठा AVCUDAFramesContext {
    /**
     * CUDA_ARRAY3D_DESCRIPTOR CUarrays will be initialized with.
     * Mostly used to provide external Flags.
     *
     * Width, Height and Format only honored if != 0.
     * Filled with default parameters from the FramesContext otherwise.
     *
     * Only applicable for AV_PIX_FMT_CUARRAY.
     */
    CUDA_ARRAY3D_DESCRIPTOR cuarray_desc;

    /**
     * If >0, pre-allocate a fixed pool of surfaces.
     * The surfaces will be available via cuarray_surfaces after init.
     * Size of the pool cannot be changed afterwards.
     *
     * Only applicable for AV_PIX_FMT_CUARRAY.
     */
    पूर्णांक cuarray_अंक_surfaces;

    /**
     * If cuarray_num_surfaces is >0, this contains the array of pre-allocated surfaces.
     *
     * Only applicable for AV_PIX_FMT_CUARRAY.
     */
    CUarray *cuarray_surfaces;
} AVCUDAFramesContext;

/**
 * CUDA hardware pipeline configuration details.
 *
 * Passed to av_hwdevice_get_hwframe_constraints() to query
 * per-hw-format constraints. When provided, valid_sw_formats
 * will be filtered to only those compatible with the specified
 * hw_format.
 */
प्रकार काष्ठा AVCUDAHWConfig {
    /**
     * The hardware pixel format to query constraints for.
     * Must be AV_PIX_FMT_CUDA or AV_PIX_FMT_CUARRAY.
     */
    क्रमागत AVPixelFormat hw_format;
} AVCUDAHWConfig;

/**
 * @defgroup hwcontext_cuda Device context creation flags
 *
 * Flags for av_hwdevice_ctx_create.
 *
 * @{
 */

/**
 * Use primary device context instead of creating a new one.
 */
#घोषणा AV_CUDA_USE_PRIMARY_CONTEXT (1 << 0)

/**
 * Use current device context instead of creating a new one.
 */
#घोषणा AV_CUDA_USE_CURRENT_CONTEXT (1 << 1)

/**
 * @}
 */

#पूर्ण_अगर /* AVUTIL_HWCONTEXT_CUDA_H */
