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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_DRM_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_DRM_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

/**
 * @file
 * API-specific header for AV_HWDEVICE_TYPE_DRM.
 *
 * Internal frame allocation is not currently supported - all frames
 * must be allocated by the user.  Thus AVHWFramesContext is always
 * NULL, though this may change if support for frame allocation is
 * added in future.
 */

ಎಣಿಕೆ {
    /**
     * The maximum number of layers/planes in a DRM frame.
     */
    AV_DRM_MAX_PLANES = 4
};

/**
 * DRM object descriptor.
 *
 * Describes a single DRM object, addressing it as a PRIME file
 * descriptor.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDRMObjectDescriptor {
    /**
     * DRM PRIME fd for the object.
     */
    ಪೂರ್ಣಾಂಕ fd;
    /**
     * Total size of the object.
     *
     * (This includes any parts not which do not contain image data.)
     */
    size_t ಗಾತ್ರ_2;
    /**
     * Format modifier applied to the object (DRM_FORMAT_MOD_*).
     *
     * If the format modifier is unknown then this should be set to
     * DRM_FORMAT_MOD_INVALID.
     */
    uint64_t format_modifier;
} AVDRMObjectDescriptor;

/**
 * DRM plane descriptor.
 *
 * Describes a single plane of a layer, which is contained within
 * a single object.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDRMPlaneDescriptor {
    /**
     * Index of the object containing this plane in the objects
     * array of the enclosing frame descriptor.
     */
    ಪೂರ್ಣಾಂಕ object_ಸೂಚ್ಯಂಕ;
    /**
     * Offset within that object of this plane.
     */
    ptrdiff_t ಸ್ಥಾನಾಂತರ;
    /**
     * Pitch (linesize) of this plane.
     */
    ptrdiff_t pitch;
} AVDRMPlaneDescriptor;

/**
 * DRM layer descriptor.
 *
 * Describes a single layer within a frame.  This has the structure
 * defined by its format, and will contain one or more planes.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDRMLayerDescriptor {
    /**
     * Format of the layer (DRM_FORMAT_*).
     */
    uint32_t format;
    /**
     * Number of planes in the layer.
     *
     * This must match the number of planes required by format.
     */
    ಪೂರ್ಣಾಂಕ nb_planes;
    /**
     * Array of planes in this layer.
     */
    AVDRMPlaneDescriptor planes[AV_DRM_MAX_PLANES];
} AVDRMLayerDescriptor;

/**
 * DRM frame descriptor.
 *
 * This is used as the data pointer for AV_PIX_FMT_DRM_PRIME frames.
 * It is also used by user-allocated frame pools - allocating in
 * AVHWFramesContext.pool must return AVBufferRefs which contain
 * an object of this type.
 *
 * The fields of this structure should be set such it can be
 * imported directly by EGL using the EGL_EXT_image_dma_buf_import
 * and EGL_EXT_image_dma_buf_import_modifiers extensions.
 * (Note that the exact layout of a particular format may vary between
 * platforms - we only specify that the same platform should be able
 * to import it.)
 *
 * The total number of planes must not exceed AV_DRM_MAX_PLANES, and
 * the order of the planes by increasing layer index followed by
 * increasing plane index must be the same as the order which would
 * be used for the data pointers in the equivalent software format.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDRMFrameDescriptor {
    /**
     * Number of DRM objects making up this frame.
     */
    ಪೂರ್ಣಾಂಕ nb_objects;
    /**
     * Array of objects making up the frame.
     */
    AVDRMObjectDescriptor objects[AV_DRM_MAX_PLANES];
    /**
     * Number of layers in the frame.
     */
    ಪೂರ್ಣಾಂಕ nb_layers;
    /**
     * Array of layers in the frame.
     */
    AVDRMLayerDescriptor layers[AV_DRM_MAX_PLANES];
} AVDRMFrameDescriptor;

/**
 * DRM device.
 *
 * Allocated as AVHWDeviceContext.hwctx.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDRMDeviceContext {
    /**
     * File descriptor of DRM device.
     *
     * This is used as the device to create frames on, and may also be
     * used in some derivation and mapping operations.
     *
     * If no device is required, set to -1.
     */
    ಪೂರ್ಣಾಂಕ fd;
} AVDRMDeviceContext;

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_DRM_H */
