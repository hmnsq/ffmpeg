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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <android/native_window.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <media/NdkMediaCodec.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_mediacodec.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    ਖਾਲੀ *libmedia;
    media_ਸਥਿਤੀ_t (*create_surface)(ANative_ਖਿੜਕੀ **surface);
} MediaCodecDeviceContext;


ਸਥਿਰ ਪੂਰਨ mc_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                            AVDictionary *opts, ਪੂਰਨ flags)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *ਇੰਦਰਾਜ = ਨਿਰਾ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    ਜੇ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜਦੋਂ ((ਇੰਦਰਾਜ = av_dict_iterate(opts, ਇੰਦਰਾਜ))) {
        ਜੇ (!strcmp(ਇੰਦਰਾਜ->ਕੁੰਜੀ, "create_window"))
            dev->create_ਖਿੜਕੀ = atoi(ਇੰਦਰਾਜ->ਮੁੱਲ);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_ਖਿੜਕੀ ? "Enable" : "Disable");

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_ਖਿੜਕੀ *native_ਖਿੜਕੀ = ਨਿਰਾ;

    ਜੇ (dev->surface)
        ਵਾਪਸ 0;

    ਜੇ (dev->native_ਖਿੜਕੀ)
        ਵਾਪਸ 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    ਜੇ (!dev->create_ਖਿੜਕੀ)
        ਵਾਪਸ 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    ਜੇ (!s->libmedia)
        ਵਾਪਸ AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    ਜੇ (!s->create_surface)
        ਵਾਪਸ AVERROR_UNKNOWN;

    s->create_surface(&native_ਖਿੜਕੀ);
    dev->native_ਖਿੜਕੀ = native_ਖਿੜਕੀ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    ਜੇ (!s->libmedia)
        ਵਾਪਸ;

    ਜੇ (dev->native_ਖਿੜਕੀ) {
        ANative_ਖਿੜਕੀ_release(dev->native_ਖਿੜਕੀ);
        dev->native_ਖਿੜਕੀ = ਨਿਰਾ;
    }
    dlclose(s->libmedia);
    s->libmedia = ਨਿਰਾ;
}

ਅਚਲ HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
