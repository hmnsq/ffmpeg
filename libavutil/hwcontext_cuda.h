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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_CUDA_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_CUDA_H

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ CUDA_ಆವೃತ್ತಿ
#ಅನ್ತರ್ಭಾವ <cuda.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "pixfmt.h"

/**
 * @file
 * An API-specific header for AV_HWDEVICE_TYPE_CUDA.
 *
 * This API supports dynamic frame pools. AVHWFramesContext.pool must return
 * AVBufferRefs whose data pointer is a CUdeviceptr.
 */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVCUDADevice_Context_ಆಂತರಿಕ AVCUDADevice_Context_ಆಂತರಿಕ;

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVCUDADeviceContext {
    CUcontext cuda_ctx;
    CUstream ಹರಿವು;
    AVCUDADevice_Context_ಆಂತರಿಕ *ಆಂತರಿಕ;
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
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor {
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
    intptr_t ಸೂಚ್ಯಂಕ;
} AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor;

/**
 * This struct is allocated as AVHWFramesContext.hwctx
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVCUDAFramesContext {
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
    ಪೂರ್ಣಾಂಕ cuarray_ಅಂಕೆ_surfaces;

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
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVCUDAHWConfig {
    /**
     * The hardware pixel format to query constraints for.
     * Must be AV_PIX_FMT_CUDA or AV_PIX_FMT_CUARRAY.
     */
    ಎಣಿಕೆ AVPixelFormat hw_format;
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
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CUDA_USE_PRIMARY_CONTEXT (1 << 0)

/**
 * Use current device context instead of creating a new one.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CUDA_USE_CURRENT_CONTEXT (1 << 1)

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_CUDA_H */
