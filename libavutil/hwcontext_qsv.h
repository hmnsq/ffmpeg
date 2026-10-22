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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_QSV_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_QSV_H

#ಅನ್ತರ್ಭಾವ <mfxvideo.h>

/**
 * @file
 * An API-specific header for AV_HWDEVICE_TYPE_QSV.
 *
 * AVHWFramesContext.pool must contain AVBufferRefs whose data pointer points
 * to a mfxFrameSurface1 struct.
 */

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVQSVDeviceContext {
    mfxSession session;
    /**
     * The mfxLoader handle used for mfxSession creation
     *
     * This field is only available for oneVPL user. For non-oneVPL user, this
     * field must be set to NULL.
     *
     * Filled by the user before calling av_hwdevice_ctx_init() and should be
     * cast to mfxLoader handle. Deallocating the AVHWDeviceContext will always
     * release this interface.
     */
    ಶೂನ್ಯ *loader;
} AVQSVDeviceContext;

/**
 * This struct is allocated as AVHWFramesContext.hwctx
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVQSVFramesContext {
    /**
     * A pointer to a mfxFrameSurface1 struct
     *
     * It is available when nb_surfaces is non-zero.
     */
    mfx_ಚೌಕಟ್ಟು_Surface1 *surfaces;

    /**
     * Number of frames in the pool
     *
     * It is 0 for dynamic frame pools or AVHWFramesContext.initial_pool_size
     * for fixed frame pools.
     *
     * Note only oneVPL GPU runtime 2.9+ can support dynamic frame pools
     * on d3d11va or vaapi
     */
    ಪೂರ್ಣಾಂಕ            nb_surfaces;

    /**
     * A combination of MFX_MEMTYPE_* describing the frame pool.
     */
    ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_type;

    /**
     * A pointer to a mfxFrameInfo struct
     *
     * It is available when nb_surfaces is 0, all buffers allocated from the
     * pool have the same mfxFrameInfo.
     */
    mfx_ಚೌಕಟ್ಟು_Info *info;
} AVQSVFramesContext;

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_QSV_H */
