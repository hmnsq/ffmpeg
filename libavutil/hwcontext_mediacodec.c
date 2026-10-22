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
    media_स्थितिः_t (*create_surface)(ANative_गवाक्षः **surface);
} MediaCodecDeviceContext;


स्थिर पूर्णाङ्क mc_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    ध्रुव AVDictionary_प्रविष्टिः *प्रविष्टिः = रिक्त;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    यदि (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यावत् ((प्रविष्टिः = av_dict_iterate(opts, प्रविष्टिः))) {
        यदि (!वाक्यं_तुलय(प्रविष्टिः->कुञ्चिका, "create_window"))
            dev->create_गवाक्षः = atoi(प्रविष्टिः->मानम्);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_गवाक्षः ? "Enable" : "Disable");

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_गवाक्षः *native_गवाक्षः = रिक्त;

    यदि (dev->surface)
        प्रत्यागम 0;

    यदि (dev->native_गवाक्षः)
        प्रत्यागम 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    यदि (!dev->create_गवाक्षः)
        प्रत्यागम 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    यदि (!s->libmedia)
        प्रत्यागम AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    यदि (!s->create_surface)
        प्रत्यागम AVERROR_UNKNOWN;

    s->create_surface(&native_गवाक्षः);
    dev->native_गवाक्षः = native_गवाक्षः;
    प्रत्यागम 0;
}

स्थिर शून्य mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    यदि (!s->libmedia)
        प्रत्यागम;

    यदि (dev->native_गवाक्षः) {
        ANative_गवाक्षः_release(dev->native_गवाक्षः);
        dev->native_गवाक्षः = रिक्त;
    }
    dlclose(s->libmedia);
    s->libmedia = रिक्त;
}

ध्रुव HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_आकार    = परिमाण(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
