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

प्रकारव्याख्या संरचना MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    शून्य *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


स्थिर पूर्णांक mc_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                            AVDictionary *opts, पूर्णांक flags)
{
    स्थिरांक AVDictionaryEntry *entry = रिक्त;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    जर (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        परत AVERROR_UNKNOWN;
    }

    पर्यंत ((entry = av_dict_iterate(opts, entry))) {
        जर (!म_भेद(entry->किल्ली, "create_window"))
            dev->create_window = म_से_प(entry->मूल्य);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    परत 0;
}

स्थिर पूर्णांक mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = रिक्त;

    जर (dev->surface)
        परत 0;

    जर (dev->native_window)
        परत 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    जर (!dev->create_window)
        परत 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    जर (!s->libmedia)
        परत AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    जर (!s->create_surface)
        परत AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    परत 0;
}

स्थिर शून्य mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    जर (!s->libmedia)
        परत;

    जर (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = रिक्त;
    }
    dlclose(s->libmedia);
    s->libmedia = रिक्त;
}

स्थिरांक HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_size    = आकार(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (स्थिरांक गणना AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
