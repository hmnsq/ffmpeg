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

#అన్తర్భావ <multimedia/player_framework/native_avcodec_base.h>

#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_oh.h"

స్థిర పూర్ణాంకం oh_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                            AVDictionary *opts, పూర్ణాంకం flags)
{
    ఒకవేళ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_oh = {
    .type = AV_HWDEVICE_TYPE_OHCODEC,
    .name = "ohcodec",
    .device_hwctx_కొలత = పరిమాణం(AVOHCodecDeviceContext),
    .device_create = oh_device_create,
    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]) {
        AV_PIX_FMT_OHCODEC,
        AV_PIX_FMT_NONE
    },
};
