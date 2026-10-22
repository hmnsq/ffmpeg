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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    ಶೂನ್ಯ *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ mc_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                            AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVDictionaryEntry *entry = ರಿಕ್ತ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    ಯದಿ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯಾವತ್ ((entry = av_dict_iterate(opts, entry))) {
        ಯದಿ (!strcmp(entry->ಕೀಲಿ, "create_window"))
            dev->create_window = atoi(entry->ಮೌಲ್ಯ);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = ರಿಕ್ತ;

    ಯದಿ (dev->surface)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯದಿ (dev->native_window)
        ಪ್ರತ್ಯಾಗಮ 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    ಯದಿ (!dev->create_window)
        ಪ್ರತ್ಯಾಗಮ 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    ಯದಿ (!s->libmedia)
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    ಯದಿ (!s->create_surface)
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    ಯದಿ (!s->libmedia)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = ರಿಕ್ತ;
    }
    dlclose(s->libmedia);
    s->libmedia = ರಿಕ್ತ;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = ಪರಿಮಾಣ(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
