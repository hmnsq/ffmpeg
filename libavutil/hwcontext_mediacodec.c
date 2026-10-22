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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <android/native_window.h>
#அந்தர்பாவ <dlfcn.h>
#அந்தர்பாவ <media/NdkMediaCodec.h>

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_mediacodec.h"

வகைவரை கட்டமைப்பு MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    வெறுமை *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


நிலையான முழு mc_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                            AVDictionary *opts, முழு flags)
{
    மாறிலி AVDictionaryEntry *entry = வெற்று;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    எனில் (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    போது ((entry = av_dict_iterate(opts, entry))) {
        எனில் (!strcmp(entry->சாவி, "create_window"))
            dev->create_window = atoi(entry->மதிப்பு);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    திரும்பு 0;
}

நிலையான முழு mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = வெற்று;

    எனில் (dev->surface)
        திரும்பு 0;

    எனில் (dev->native_window)
        திரும்பு 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    எனில் (!dev->create_window)
        திரும்பு 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    எனில் (!s->libmedia)
        திரும்பு AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    எனில் (!s->create_surface)
        திரும்பு AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    திரும்பு 0;
}

நிலையான வெறுமை mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    எனில் (!s->libmedia)
        திரும்பு;

    எனில் (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = வெற்று;
    }
    dlclose(s->libmedia);
    s->libmedia = வெற்று;
}

மாறிலி HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = அளவு(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
