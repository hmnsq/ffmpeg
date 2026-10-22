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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <android/native_window.h>
#અન્તર્ભાવ <dlfcn.h>
#અન્તર્ભાવ <media/NdkMediaCodec.h>

#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_mediacodec.h"

પ્રકારવ્યાખ્યા સંરચના MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    શૂન્ય *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


સ્થિર પૂર્ણાંક mc_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                            AVDictionary *opts, પૂર્ણાંક flags)
{
    અચલ AVDictionaryEntry *entry = ખાલી;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    જો (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        પાછા AVERROR_UNKNOWN;
    }

    જ્યારે ((entry = av_dict_iterate(opts, entry))) {
        જો (!strcmp(entry->ચાવી, "create_window"))
            dev->create_window = atoi(entry->કિંમત);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    પાછા 0;
}

સ્થિર પૂર્ણાંક mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = ખાલી;

    જો (dev->surface)
        પાછા 0;

    જો (dev->native_window)
        પાછા 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    જો (!dev->create_window)
        પાછા 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    જો (!s->libmedia)
        પાછા AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    જો (!s->create_surface)
        પાછા AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    પાછા 0;
}

સ્થિર શૂન્ય mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    જો (!s->libmedia)
        પાછા;

    જો (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = ખાલી;
    }
    dlclose(s->libmedia);
    s->libmedia = ખાલી;
}

અચલ HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = કદ(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (અચલ ગણના AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
