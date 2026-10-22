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

#ضمن "config.h"

#ضمن <android/native_window.h>
#ضمن <dlfcn.h>
#ضمن <media/NdkMediaCodec.h>

#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_mediacodec.h"

تعريفنوع بنية MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    فراغ *libmedia;
    media_حالت_t (*create_surface)(ANative_کھڑکی **surface);
} MediaCodecDeviceContext;


ساكن صحيح mc_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحيح flags)
{
    ثابت AVDictionary_اندراج *اندراج = عدم;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    إذا (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        أرجع AVERROR_UNKNOWN;
    }

    طالما ((اندراج = av_dict_iterate(opts, اندراج))) {
        إذا (!strcmp(اندراج->کلید, "create_window"))
            dev->create_کھڑکی = atoi(اندراج->قدر);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_کھڑکی ? "Enable" : "Disable");

    أرجع 0;
}

ساكن صحيح mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_کھڑکی *native_کھڑکی = عدم;

    إذا (dev->surface)
        أرجع 0;

    إذا (dev->native_کھڑکی)
        أرجع 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    إذا (!dev->create_کھڑکی)
        أرجع 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    إذا (!s->libmedia)
        أرجع AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    إذا (!s->create_surface)
        أرجع AVERROR_UNKNOWN;

    s->create_surface(&native_کھڑکی);
    dev->native_کھڑکی = native_کھڑکی;
    أرجع 0;
}

ساكن فراغ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    إذا (!s->libmedia)
        أرجع;

    إذا (dev->native_کھڑکی) {
        ANative_کھڑکی_release(dev->native_کھڑکی);
        dev->native_کھڑکی = عدم;
    }
    dlclose(s->libmedia);
    s->libmedia = عدم;
}

ثابت HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_ناپ    = حجم(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
