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

#شامل "config.h"

#شامل <android/native_window.h>
#شامل <dlfcn.h>
#شامل <media/NdkMediaCodec.h>

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_mediacodec.h"

قسمتعریف ساخت MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    خالی *libmedia;
    media_حالت_t (*create_surface)(ANative_کھڑکی **surface);
} MediaCodecDeviceContext;


ساکن صحیح mc_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحیح flags)
{
    ثابت AVDictionary_اندراج *اندراج_2 = تہی;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    اگر (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        واپس AVERROR_UNKNOWN;
    }

    جب ((اندراج_2 = av_dict_iterate(opts, اندراج_2))) {
        اگر (!strcmp(اندراج_2->کلید, "create_window"))
            dev->create_کھڑکی = atoi(اندراج_2->قدر);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_کھڑکی ? "Enable" : "Disable");

    واپس 0;
}

ساکن صحیح mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_کھڑکی *native_کھڑکی = تہی;

    اگر (dev->surface)
        واپس 0;

    اگر (dev->native_کھڑکی)
        واپس 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    اگر (!dev->create_کھڑکی)
        واپس 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    اگر (!s->libmedia)
        واپس AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    اگر (!s->create_surface)
        واپس AVERROR_UNKNOWN;

    s->create_surface(&native_کھڑکی);
    dev->native_کھڑکی = native_کھڑکی;
    واپس 0;
}

ساکن خالی mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    اگر (!s->libmedia)
        واپس;

    اگر (dev->native_کھڑکی) {
        ANative_کھڑکی_release(dev->native_کھڑکی);
        dev->native_کھڑکی = تہی;
    }
    dlclose(s->libmedia);
    s->libmedia = تہی;
}

ثابت HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_سائز    = حجم(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ثابت شمار AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
