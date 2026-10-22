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
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


ساكن صحيح mc_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = عدم;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    אם (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        החזר AVERROR_UNKNOWN;
    }

    כלעוד ((entry = av_dict_iterate(opts, entry))) {
        אם (!strcmp(entry->key, "create_window"))
            dev->create_window = atoi(entry->value);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    החזר 0;
}

ساكن صحيح mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = عدم;

    אם (dev->surface)
        החזר 0;

    אם (dev->native_window)
        החזר 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    אם (!dev->create_window)
        החזר 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    אם (!s->libmedia)
        החזר AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    אם (!s->create_surface)
        החזר AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    החזר 0;
}

ساكن فراغ mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    אם (!s->libmedia)
        החזר;

    אם (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = عدم;
    }
    dlclose(s->libmedia);
    s->libmedia = عدم;
}

ثابت HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = حجم(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
