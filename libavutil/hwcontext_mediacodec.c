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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <android/native_window.h>
#ଅନ୍ତର୍ଭାଵ <dlfcn.h>
#ଅନ୍ତର୍ଭାଵ <media/NdkMediaCodec.h>

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_mediacodec.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    ଶୂନ୍ୟ *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା mc_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                            AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVDictionaryEntry *entry = ଖାଲି;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    ଯଦି (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯେତେବେଳେ ((entry = av_dict_iterate(opts, entry))) {
        ଯଦି (!strcmp(entry->ଚାବି, "create_window"))
            dev->create_window = atoi(entry->ମୂଲ୍ୟ);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = ଖାଲି;

    ଯଦି (dev->surface)
        ଫେରନ୍ତୁ 0;

    ଯଦି (dev->native_window)
        ଫେରନ୍ତୁ 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    ଯଦି (!dev->create_window)
        ଫେରନ୍ତୁ 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    ଯଦି (!s->libmedia)
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    ଯଦି (!s->create_surface)
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    ଯଦି (!s->libmedia)
        ଫେରନ୍ତୁ;

    ଯଦି (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = ଖାଲି;
    }
    dlclose(s->libmedia);
    s->libmedia = ଖାଲି;
}

ଅଚଳ HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = ଆକାର(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
