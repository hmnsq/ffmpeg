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

#شامل <multimedia/player_framework/native_avcodec_base.h>

#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_oh.h"

ایستا صحیح oh_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                            AVDictionary *opts, صحیح flags)
{
    اگر (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_oh = {
    .type = AV_HWDEVICE_TYPE_OHCODEC,
    .name = "ohcodec",
    .device_hwctx_size = اندازه(AVOHCodecDeviceContext),
    .device_create = oh_device_create,
    .pix_fmts = (ثابت شمارش AVPixelFormat[]) {
        AV_PIX_FMT_OHCODEC,
        AV_PIX_FMT_NONE
    },
};
