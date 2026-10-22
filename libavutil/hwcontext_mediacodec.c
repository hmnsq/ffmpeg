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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <android/native_window.h>
#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ಅನ್ತರ್ಭಾವ <media/NdkMediaCodec.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_mediacodec.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    ಶೂನ್ಯ *libmedia;
    media_ಸ್ಥಿತಿ_t (*create_surface)(ANative_ಕಿಟಕಿ **surface);
} MediaCodecDeviceContext;


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ mc_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                            AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *ನಮೂದು = ಖಾಲಿ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    ಆದರೆ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆಗ ((ನಮೂದು = av_dict_iterate(opts, ನಮೂದು))) {
        ಆದರೆ (!strcmp(ನಮೂದು->ಕೀಲಿ, "create_window"))
            dev->create_ಕಿಟಕಿ = atoi(ನಮೂದು->ಮೌಲ್ಯ);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_ಕಿಟಕಿ ? "Enable" : "Disable");

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_ಕಿಟಕಿ *native_ಕಿಟಕಿ = ಖಾಲಿ;

    ಆದರೆ (dev->surface)
        ಹಿಂತಿರುಗಿ 0;

    ಆದರೆ (dev->native_ಕಿಟಕಿ)
        ಹಿಂತಿರುಗಿ 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    ಆದರೆ (!dev->create_ಕಿಟಕಿ)
        ಹಿಂತಿರುಗಿ 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    ಆದರೆ (!s->libmedia)
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    ಆದರೆ (!s->create_surface)
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;

    s->create_surface(&native_ಕಿಟಕಿ);
    dev->native_ಕಿಟಕಿ = native_ಕಿಟಕಿ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    ಆದರೆ (!s->libmedia)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (dev->native_ಕಿಟಕಿ) {
        ANative_ಕಿಟಕಿ_release(dev->native_ಕಿಟಕಿ);
        dev->native_ಕಿಟಕಿ = ಖಾಲಿ;
    }
    dlclose(s->libmedia);
    s->libmedia = ಖಾಲಿ;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
