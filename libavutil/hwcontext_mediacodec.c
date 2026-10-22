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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <android/native_window.h>
#അന്തര്ഭാവ <dlfcn.h>
#അന്തര്ഭാവ <media/NdkMediaCodec.h>

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_mediacodec.h"

തരനിർവചനം ഘടന MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    ശൂന്യം *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


സ്ഥിതം പൂർണ്ണസംഖ്യ mc_device_create(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                            AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVDictionaryEntry *entry = ശൂന്യ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    എങ്കിൽ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    ആകുമ്പോൾ ((entry = av_dict_iterate(opts, entry))) {
        എങ്കിൽ (!strcmp(entry->താക്കോൽ, "create_window"))
            dev->create_window = atoi(entry->മൂല്യം);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = ശൂന്യ;

    എങ്കിൽ (dev->surface)
        തിരികെ 0;

    എങ്കിൽ (dev->native_window)
        തിരികെ 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    എങ്കിൽ (!dev->create_window)
        തിരികെ 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    എങ്കിൽ (!s->libmedia)
        തിരികെ AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    എങ്കിൽ (!s->create_surface)
        തിരികെ AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    എങ്കിൽ (!s->libmedia)
        തിരികെ;

    എങ്കിൽ (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = ശൂന്യ;
    }
    dlclose(s->libmedia);
    s->libmedia = ശൂന്യ;
}

സ്ഥിരം HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = വലുപ്പം(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
