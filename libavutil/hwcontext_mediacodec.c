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

#अन्तर्भाव "config.h"

#अन्तर्भाव <android/native_window.h>
#अन्तर्भाव <dlfcn.h>
#अन्तर्भाव <media/NdkMediaCodec.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_mediacodec.h"

प्रकारनिर्देश संरचना MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    शून्य *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


स्थिर पूर्णाङ्क mc_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    ध्रुव AVDictionaryEntry *entry = रिक्त;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    जइ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    जाव ((entry = av_dict_iterate(opts, entry))) {
        जइ (!strcmp(entry->कुञ्चिका, "create_window"))
            dev->create_window = atoi(entry->मानम्);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = रिक्त;

    जइ (dev->surface)
        प्रत्यागम 0;

    जइ (dev->native_window)
        प्रत्यागम 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    जइ (!dev->create_window)
        प्रत्यागम 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    जइ (!s->libmedia)
        प्रत्यागम AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    जइ (!s->create_surface)
        प्रत्यागम AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    प्रत्यागम 0;
}

स्थिर शून्य mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    जइ (!s->libmedia)
        प्रत्यागम;

    जइ (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = रिक्त;
    }
    dlclose(s->libmedia);
    s->libmedia = रिक्त;
}

ध्रुव HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = परिमाण(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
