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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <android/native_window.h>
#অন্তর্ভাব <dlfcn.h>
#অন্তর্ভাব <media/NdkMediaCodec.h>

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_mediacodec.h"

প্রকারনির্দেশ সংরচনা MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    শূন্য *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


স্থির পূর্ণাঙ্ক mc_device_create(AVHWDeviceContext *ctx, ধ্রুব বর্ণ *device,
                            AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    ধ্রুব AVDictionaryEntry *entry = রিক্ত;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    যদি (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    যাবত্ ((entry = av_dict_iterate(opts, entry))) {
        যদি (!strcmp(entry->চাবি, "create_window"))
            dev->create_window = atoi(entry->মান);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = রিক্ত;

    যদি (dev->surface)
        প্রত্যাগম 0;

    যদি (dev->native_window)
        প্রত্যাগম 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    যদি (!dev->create_window)
        প্রত্যাগম 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    যদি (!s->libmedia)
        প্রত্যাগম AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    যদি (!s->create_surface)
        প্রত্যাগম AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    প্রত্যাগম 0;
}

স্থির শূন্য mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    যদি (!s->libmedia)
        প্রত্যাগম;

    যদি (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = রিক্ত;
    }
    dlclose(s->libmedia);
    s->libmedia = রিক্ত;
}

ধ্রুব HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = পরিমাণ(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ধ্রুব গণনা AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
