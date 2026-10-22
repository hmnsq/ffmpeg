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

#अन्तर्भाव <multimedia/player_framework/native_avcodec_base.h>

#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_oh.h"

स्थिर पूर्णाङ्क oh_device_create(AVHWDeviceContext *ctx, अचर वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    यदि (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        फर्काऊ AVERROR_UNKNOWN;
    }

    फर्काऊ 0;
}

अचर HWContextType ff_hwcontext_type_oh = {
    .type = AV_HWDEVICE_TYPE_OHCODEC,
    .name = "ohcodec",
    .device_hwctx_size = परिमाण(AVOHCodecDeviceContext),
    .device_create = oh_device_create,
    .pix_fmts = (अचर गणना AVPixelFormat[]) {
        AV_PIX_FMT_OHCODEC,
        AV_PIX_FMT_NONE
    },
};
