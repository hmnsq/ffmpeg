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

#include "config.h"

#include <android/native_window.h>
#include <dlfcn.h>
#include <media/NdkMediaCodec.h>

#include "buffer.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_mediacodec.h"

typedef struct MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    void *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


static 整数 mc_device_create(AVHWDeviceContext *ctx, const char *device,
                            AVDictionary *opts, 整数 flags)
{
    const AVDictionaryEntry *entry = NULL;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    如果 (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        返回 AVERROR_UNKNOWN;
    }

    当 ((entry = av_dict_iterate(opts, entry))) {
        如果 (!strcmp(entry->key, "create_window"))
            dev->create_window = atoi(entry->value);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    返回 0;
}

static 整数 mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = NULL;

    如果 (dev->surface)
        返回 0;

    如果 (dev->native_window)
        返回 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    如果 (!dev->create_window)
        返回 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    如果 (!s->libmedia)
        返回 AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    如果 (!s->create_surface)
        返回 AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    返回 0;
}

static void mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    如果 (!s->libmedia)
        返回;

    如果 (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = NULL;
    }
    dlclose(s->libmedia);
    s->libmedia = NULL;
}

const HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = sizeof(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (const enum AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
