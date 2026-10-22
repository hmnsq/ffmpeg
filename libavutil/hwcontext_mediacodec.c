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

#समावेश "config.h"

#समावेश <android/native_window.h>
#समावेश <dlfcn.h>
#समावेश <media/NdkMediaCodec.h>

#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_mediacodec.h"

प्रकार काष्ठा MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    व्योम *libmedia;
    media_status_t (*create_surface)(ANativeWindow **surface);
} MediaCodecDeviceContext;


अटल पूर्णांक mc_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                            AVDictionary *opts, पूर्णांक flags)
{
    स्थिर AVDictionaryEntry *entry = शून्य;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    अगर (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        वापस AVERROR_UNKNOWN;
    }

    जबतक ((entry = av_dict_iterate(opts, entry))) {
        अगर (!म_भेद(entry->कुंजी, "create_window"))
            dev->create_window = म_से_प(entry->मूल्य);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_window ? "Enable" : "Disable");

    वापस 0;
}

अटल पूर्णांक mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANativeWindow *native_window = शून्य;

    अगर (dev->surface)
        वापस 0;

    अगर (dev->native_window)
        वापस 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    अगर (!dev->create_window)
        वापस 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    अगर (!s->libmedia)
        वापस AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    अगर (!s->create_surface)
        वापस AVERROR_UNKNOWN;

    s->create_surface(&native_window);
    dev->native_window = native_window;
    वापस 0;
}

अटल व्योम mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    अगर (!s->libmedia)
        वापस;

    अगर (dev->native_window) {
        ANativeWindow_release(dev->native_window);
        dev->native_window = शून्य;
    }
    dlclose(s->libmedia);
    s->libmedia = शून्य;
}

स्थिर HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_आकार    = माप(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
