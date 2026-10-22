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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_HWCONTEXT_VDPAU_H
#وصف_ڪريو AVUTIL_HWCONTEXT_VDPAU_H

#ضمن <vdpau/vdpau.h>

/**
 * @file
 * An API-specific header for AV_HWDEVICE_TYPE_VDPAU.
 *
 * This API supports dynamic frame pools. AVHWFramesContext.pool must return
 * AVBufferRefs whose data pointer is a VdpVideoSurface.
 */

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
تعريفنوع بنية AVVDPAUDeviceContext {
    VdpDevice          device;
    Vdp_Get_Proc_پتو *get_proc_پتو;
} AVVDPAUDeviceContext;

/**
 * AVHWFramesContext.hwctx is currently not used
 */

#جيڪڏهن_پورو /* AVUTIL_HWCONTEXT_VDPAU_H */
