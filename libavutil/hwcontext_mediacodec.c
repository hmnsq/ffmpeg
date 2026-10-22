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

تعریفنوع ساختار MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    تهی *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


ایستا صحیح mc_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                            AVDictionary *opts, صحیح flags)
{
    ثابت AVDictionaryEntry *entry = پوچ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    اگر (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        بازگشت AVERROR_UNKNOWN;
    }

    وقتی ((entry = av_dict_iterate(opts, entry))) {
        اگر (!strcmp(entry->کلید, "create_window"))
            dev->create_window = atoi(entry->مقدار);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    بازگشت 0;
}

ایستا صحیح mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = پوچ;

    اگر (dev->surface)
        بازگشت 0;

    اگر (dev->native_window)
        بازگشت 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    اگر (!dev->create_window)
        بازگشت 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    اگر (!s->libmedia)
        بازگشت AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    اگر (!s->create_surface)
        بازگشت AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    بازگشت 0;
}

ایستا تهی mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    اگر (!s->libmedia)
        بازگشت;

    اگر (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = پوچ;
    }
    dlclose(s->libmedia);
    s->libmedia = پوچ;
}

ثابت HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = اندازه(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ثابت شمارش AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
