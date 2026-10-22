/*
 * This file is part of FFmpeg.
 *
 * Copyright (c) 2025 Zhao Zhili <quinkblack@foxmail.com>
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

#ಅನ್ತರ್ಭಾವ <multimedia/player_framework/native_avcodec_base.h>

#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_oh.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ oh_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                            AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಯದಿ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_oh = {
    .type = AV_HWDEVICE_TYPE_OHCODEC,
    .name = "ohcodec",
    .device_hwctx_size = ಪರಿಮಾಣ(AVOHCodecDeviceContext),
    .device_create = oh_device_create,
    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]) {
        AV_PIX_FMT_OHCODEC,
        AV_PIX_FMT_NONE
    },
};
