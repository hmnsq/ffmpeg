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

#અન્તર્ભાવ <multimedia/player_framework/native_avcodec_base.h>

#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_oh.h"

સ્થિર પૂર્ણાંક oh_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                            AVDictionary *opts, પૂર્ણાંક flags)
{
    જો (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

અચલ HWContextType ff_hwcontext_type_oh = {
    .type = AV_HWDEVICE_TYPE_OHCODEC,
    .name = "ohcodec",
    .device_hwctx_size = કદ(AVOHCodecDeviceContext),
    .device_create = oh_device_create,
    .pix_fmts = (અચલ ગણના AVPixelFormat[]) {
        AV_PIX_FMT_OHCODEC,
        AV_PIX_FMT_NONE
    },
};
