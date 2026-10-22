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

#అన్తర్భావ "config.h"

#అన్తర్భావ <android/native_window.h>
#అన్తర్భావ <dlfcn.h>
#అన్తర్భావ <media/NdkMediaCodec.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_mediacodec.h"

రకనిర్వచనం నిర్మాణం MediaCodecDeviceContext {
    AVMediaCodecDeviceContext ctx;

    శూన్య *libmedia;
    media_స్థితి_t (*create_surface)(ANative_కిటికీ **surface);
} MediaCodecDeviceContext;


స్థిర పూర్ణాంకం mc_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                            AVDictionary *opts, పూర్ణాంకం flags)
{
    స్థిరరాశి AVDictionary_నమోదు *నమోదు_2 = ఖాళీ;
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = &s->ctx;

    ఒకవేళ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    అయితే ((నమోదు_2 = av_dict_iterate(opts, నమోదు_2))) {
        ఒకవేళ (!strcmp(నమోదు_2->కీలకం, "create_window"))
            dev->create_కిటికీ = atoi(నమోదు_2->విలువ);
    }

    av_log(ctx, AV_LOG_DEBUG, "%s createPersistentInputSurface\n",
            dev->create_కిటికీ ? "Enable" : "Disable");

    తిరిగి 0;
}

స్థిర పూర్ణాంకం mc_device_init(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = (AVMediaCodecDeviceContext *)s;
    ANative_కిటికీ *native_కిటికీ = ఖాళీ;

    ఒకవేళ (dev->surface)
        తిరిగి 0;

    ఒకవేళ (dev->native_కిటికీ)
        తిరిగి 0;

    // For backward compatibility, don't return error for a dummy
    // AVHWDeviceContext without surface or native_window.
    ఒకవేళ (!dev->create_కిటికీ)
        తిరిగి 0;

    s->libmedia = dlopen("libmediandk.so", RTLD_NOW);
    ఒకవేళ (!s->libmedia)
        తిరిగి AVERROR_UNKNOWN;

    s->create_surface = dlsym(s->libmedia, "AMediaCodec_createPersistentInputSurface");
    ఒకవేళ (!s->create_surface)
        తిరిగి AVERROR_UNKNOWN;

    s->create_surface(&native_కిటికీ);
    dev->native_కిటికీ = native_కిటికీ;
    తిరిగి 0;
}

స్థిర శూన్య mc_device_uninit(AVHWDeviceContext *ctx)
{
    MediaCodecDeviceContext *s = ctx->hwctx;
    AVMediaCodecDeviceContext *dev = ctx->hwctx;
    ఒకవేళ (!s->libmedia)
        తిరిగి;

    ఒకవేళ (dev->native_కిటికీ) {
        ANative_కిటికీ_release(dev->native_కిటికీ);
        dev->native_కిటికీ = ఖాళీ;
    }
    dlclose(s->libmedia);
    s->libmedia = ఖాళీ;
}

స్థిరరాశి HWContextType ff_hwcontext_type_mediacodec = {
    .type                 = AV_HWDEVICE_TYPE_MEDIACODEC,
    .name                 = "mediacodec",

    .device_hwctx_కొలత    = పరిమాణం(MediaCodecDeviceContext),

    .device_create        = mc_device_create,
    .device_init          = mc_device_init,
    .device_uninit        = mc_device_uninit,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]){
        AV_PIX_FMT_MEDIACODEC,
        AV_PIX_FMT_NONE
    },
};
