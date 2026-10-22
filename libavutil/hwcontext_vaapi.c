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

#ఒకవేళ HAVE_VAAPI_WIN32
#   include <windows.h>
#నిర్వచించు COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
రకనిర్వచనం HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, శూన్య **ppFactory);
#అయితే_ముగింపు
#ఒకవేళ HAVE_VAAPI_X11
#   include <va/va_x11.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#అయితే_ముగింపు

#ఒకవేళ CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#అయితే_ముగింపు

#అన్తర్భావ <fcntl.h>
#ఒకవేళ HAVE_UNISTD_H
#   include <unistd.h>
#అయితే_ముగింపు


#అన్తర్భావ "avassert.h"
#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_drm.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_vaapi.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"


రకనిర్వచనం నిర్మాణం VAAPIDevicePriv {
#ఒకవేళ HAVE_VAAPI_X11
    Display *x11_display;
#అయితే_ముగింపు

    పూర్ణాంకం drm_fd;
} VAAPIDevicePriv;

రకనిర్వచనం నిర్మాణం VAAPISurfaceFormat {
    గణన AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    గుర్తులేని పూర్ణాంకం fourcc;
} VAAPISurfaceFormat;

రకనిర్వచనం నిర్మాణం VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    పూర్ణాంకం              nb_formats;
} VAAPIDeviceContext;

రకనిర్వచనం నిర్మాణం VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *లక్షణాలు;
    పూర్ణాంకం           nb_లక్షణాలు;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    గుర్తులేని పూర్ణాంకం rt_format;
    // Whether vaDeriveImage works.
    పూర్ణాంకం derive_పనిచేస్తుంది;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    పూర్ణాంకం ప్రధానసంఖ్య_2_import_unsupported;
} VAAPIFramesContext;

రకనిర్వచనం నిర్మాణం VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    పూర్ణాంకం flags;
} VAAPIMapping;

రకనిర్వచనం నిర్మాణం VAAPIFormat {
    గుర్తులేని పూర్ణాంకం fourcc;
    గుర్తులేని పూర్ణాంకం rt_format;
    గణన AVPixelFormat pix_fmt;
    పూర్ణాంకం chroma_planes_swapped;
} VAAPIFormatDescriptor;

#నిర్వచించు MAP(va, rt, av, మార్పిడి_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        మార్పిడి_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
స్థిర స్థిరరాశి VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#నిర్వచితమైతే VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#అయితే_ముగింపు
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#నిర్వచితమైతే VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#అయితే_ముగింపు
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#నిర్వచితమైతే VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#అయితే_ముగింపు
#నిర్వచితమైతే VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#అయితే_ముగింపు
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#నిర్వచితమైతే VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#అయితే_ముగింపు
    MAP(Y800, YUV400,  GRAY8,   0),
#నిర్వచితమైతే VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#అయితే_ముగింపు
#నిర్వచితమైతే VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#అయితే_ముగింపు
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#నిర్వచితమైతే VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#అయితే_ముగింపు
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#నిర్వచితమైతే VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#అయితే_ముగింపు
#నిర్వచితమైతే VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#అయితే_ముగింపు
#నిర్వచితమైతే VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#అయితే_ముగింపు
};
#నిర్వచనం_రద్దు MAP

స్థిర స్థిరరాశి VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(గుర్తులేని పూర్ణాంకం fourcc)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        ఒకవేళ (vaapi_format_map[i].fourcc == fourcc)
            తిరిగి &vaapi_format_map[i];
    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(గణన AVPixelFormat pix_fmt, స్థిరరాశి VAAPIFormatDescriptor *prev)
{
    స్థిరరాశి VAAPIFormatDescriptor *చివర = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    ఒకవేళ (!prev)
        prev = vaapi_format_map;
    లేకపోతే
        prev++;

    కొరకు (; prev < చివర; prev++)
        ఒకవేళ (prev->pix_fmt == pix_fmt)
            తిరిగి prev;
    తిరిగి ఖాళీ;
}

స్థిర గణన AVPixelFormat vaapi_pix_fmt_from_fourcc(గుర్తులేని పూర్ణాంకం fourcc)
{
    స్థిరరాశి VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    ఒకవేళ (desc)
        తిరిగి desc->pix_fmt;
    లేకపోతే
        తిరిగి AV_PIX_FMT_NONE;
}

స్థిర పూర్ణాంకం vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  గణన AVPixelFormat pix_fmt,
                                  స్థిరరాశి VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    స్థిరరాశి VAAPIFormatDescriptor *desc = ఖాళీ;
    పూర్ణాంకం i;

    అయితే ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        కొరకు (i = 0; i < ctx->nb_formats; i++) {
            ఒకవేళ (ctx->formats[i].fourcc == desc->fourcc) {
                ఒకవేళ (_desc)
                    *_desc = desc;
                ఒకవేళ (image_format)
                    *image_format = &ctx->formats[i].image_format;
                తిరిగి 0;
            }
        }
    }

    తిరిగి AVERROR(ENOSYS);
}

స్థిర పూర్ణాంకం vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  గణన AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    ఒకవేళ (!image_format)
        తిరిగి AVERROR(EINVAL);
    తిరిగి vaapi_get_img_desc_and_format(hwdev, pix_fmt, ఖాళీ, image_format);
}

స్థిర పూర్ణాంకం vaapi_చట్రాలు_get_constraints(AVHWDeviceContext *hwdev,
                                        స్థిరరాశి శూన్య *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    స్థిరరాశి AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ఖాళీ;
    VAStatus vas;
    గణన AVPixelFormat pix_fmt;
    గుర్తులేని పూర్ణాంకం fourcc;
    పూర్ణాంకం err, i, j, attr_లెక్క, pix_fmt_లెక్క;

    ఒకవేళ (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_లక్షణాలు)) {
        attr_లెక్క = 0;
        vas = va_Query_Surface_లక్షణాలు(hwctx->display, config->config_id,
                                       0, &attr_లెక్క);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            వెళ్ళు fail;
        }

        attr_list = av_malloc(attr_లెక్క * పరిమాణం(*attr_list));
        ఒకవేళ (!attr_list) {
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }

        vas = va_Query_Surface_లక్షణాలు(hwctx->display, config->config_id,
                                       attr_list, &attr_లెక్క);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            వెళ్ళు fail;
        }

        pix_fmt_లెక్క = 0;
        కొరకు (i = 0; i < attr_లెక్క; i++) {
            ఎంపిక (attr_list[i].type) {
            స్థితి VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].విలువ.విలువ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                ఒకవేళ (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_లెక్క;
                } లేకపోతే {
                    // Something unsupported - ignore.
                }
                ఆపు;
            స్థితి VASurface_Attrib_Min_వెడల్పు:
                constraints->min_వెడల్పు  = attr_list[i].విలువ.విలువ.i;
                ఆపు;
            స్థితి VASurface_Attrib_Min_ఎత్తు:
                constraints->min_ఎత్తు = attr_list[i].విలువ.విలువ.i;
                ఆపు;
            స్థితి VASurface_Attrib_Max_వెడల్పు:
                constraints->max_వెడల్పు  = attr_list[i].విలువ.విలువ.i;
                ఆపు;
            స్థితి VASurface_Attrib_Max_ఎత్తు:
                constraints->max_ఎత్తు = attr_list[i].విలువ.విలువ.i;
                ఆపు;
            }
        }
        ఒకవేళ (pix_fmt_లెక్క == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ఖాళీ;
        } లేకపోతే {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_లెక్క + 1,
                                                            పరిమాణం(pix_fmt));
            ఒకవేళ (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }

            కొరకు (i = j = 0; i < attr_లెక్క; i++) {
                పూర్ణాంకం k;

                ఒకవేళ (attr_list[i].type != VASurfaceAttribPixelFormat)
                    కొనసాగు;
                fourcc = attr_list[i].విలువ.విలువ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                ఒకవేళ (pix_fmt == AV_PIX_FMT_NONE)
                    కొనసాగు;

                కొరకు (k = 0; k < j; k++) {
                    ఒకవేళ (constraints->valid_sw_formats[k] == pix_fmt)
                        ఆపు;
                }

                ఒకవేళ (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } లేకపోతే {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        పరిమాణం(pix_fmt));
        ఒకవేళ (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
        కొరకు (i = j = 0; i < ctx->nb_formats; i++) {
            పూర్ణాంకం k;

            కొరకు (k = 0; k < j; k++) {
                ఒకవేళ (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    ఆపు;
            }

            ఒకవేళ (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(pix_fmt));
    ఒకవేళ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    తిరిగి err;
}

స్థిర స్థిరరాశి నిర్మాణం {
    స్థిరరాశి అక్షరం *friendly_name;
    స్థిరరాశి అక్షరం *సరిపోలిక_string;
    గుర్తులేని పూర్ణాంకం quirks;
} vaapi_driver_quirks_పట్టిక[] = {
#ఒకవేళ !VA_CHECK_సంస్కరణ(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#అయితే_ముగింపు
    {
        "Intel iHD",
        "ubit",
        AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE,
    },
    {
        "VDPAU wrapper",
        "Splitted-Desktop Systems VDPAU backend for VA-API",
        AV_VAAPI_DRIVER_QUIRK_SURFACE_లక్షణాలు,
    },
};

స్థిర పూర్ణాంకం vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ఖాళీ;
    VAStatus vas;
    స్థిరరాశి అక్షరం *vendor_string;
    పూర్ణాంకం err, i, image_లెక్క;
    గణన AVPixelFormat pix_fmt;
    గుర్తులేని పూర్ణాంకం fourcc;

    image_లెక్క = va_Max_అంకె_Image_Formats(hwctx->display);
    ఒకవేళ (image_లెక్క <= 0) {
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }
    image_list = av_malloc(image_లెక్క * పరిమాణం(*image_list));
    ఒకవేళ (!image_list) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_లెక్క);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }

    ctx->formats  = av_malloc(image_లెక్క * పరిమాణం(*ctx->formats));
    ఒకవేళ (!ctx->formats) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    ctx->nb_formats = 0;
    కొరకు (i = 0; i < image_లెక్క; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        ఒకవేళ (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } లేకపోతే {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    ఒకవేళ (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    ఒకవేళ (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_సమితి) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } లేకపోతే {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        ఒకవేళ (vendor_string) {
            కొరకు (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_పట్టిక); i++) {
                ఒకవేళ (అక్షరశ్రేణి_శోధన(vendor_string,
                           vaapi_driver_quirks_పట్టిక[i].సరిపోలిక_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_పట్టిక[i].friendly_name,
                           vaapi_driver_quirks_పట్టిక[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_పట్టిక[i].quirks;
                    ఆపు;
                }
            }
            ఒకవేళ (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_పట్టిక))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } లేకపోతే {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    తిరిగి 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    తిరిగి err;
}

స్థిర శూన్య vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

స్థిర శూన్య vaapi_బఫరు_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)దత్తాంశం;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

స్థిర AVBufferRef *vaapi_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    ఒకవేళ (hwfc->initial_pool_కొలత > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_కొలత)
        తిరిగి ఖాళీ;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->వెడల్పు, hwfc->ఎత్తు,
                           &surface_id, 1,
                           ctx->లక్షణాలు, ctx->nb_లక్షణాలు);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        తిరిగి ఖాళీ;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_బఫరు_create((uint8_t*)(uintptr_t)surface_id,
                           పరిమాణం(surface_id), &vaapi_బఫరు_free,
                           hwfc, AV_బఫరు_FLAG_READONLY);
    ఒకవేళ (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (hwfc->initial_pool_కొలత > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_కొలత);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    తిరిగి ref;
}

స్థిర పూర్ణాంకం vaapi_చట్రాలు_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    స్థిరరాశి VAAPIFormatDescriptor *desc = ఖాళీ;
    VAImageFormat *expected_format = ఖాళీ;
    AVBufferRef *test_surface = ఖాళీ;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    పూర్ణాంకం err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    ఒకవేళ (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        ఒకవేళ (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ఖాళీ)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            తిరిగి AVERROR(EINVAL);
        }
    }

    ఒకవేళ (!hwfc->pool) {
        ఒకవేళ (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_లక్షణాలు)) {
            పూర్ణాంకం need_జ్ఞాపకం_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            పూర్ణాంకం need_pixel_format = 1;
            కొరకు (i = 0; i < avfc->nb_లక్షణాలు; i++) {
                ఒకవేళ (avfc->లక్షణాలు[i].type == VASurface_Attrib_జ్ఞాపకం_Type)
                    need_జ్ఞాపకం_type  = 0;
                ఒకవేళ (avfc->లక్షణాలు[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_లక్షణాలు =
                avfc->nb_లక్షణాలు + need_జ్ఞాపకం_type + need_pixel_format;

            ctx->లక్షణాలు = av_malloc(ctx->nb_లక్షణాలు *
                                        పరిమాణం(*ctx->లక్షణాలు));
            ఒకవేళ (!ctx->లక్షణాలు) {
                err = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }

            కొరకు (i = 0; i < avfc->nb_లక్షణాలు; i++)
                ctx->లక్షణాలు[i] = avfc->లక్షణాలు[i];
            ఒకవేళ (need_జ్ఞాపకం_type) {
                ctx->లక్షణాలు[i++] = (VASurfaceAttrib) {
                    .type          = VASurface_Attrib_జ్ఞాపకం_Type,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .విలువ.type    = VAGeneric_విలువ_Type_Integer,
                    .విలువ.విలువ.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            ఒకవేళ (need_pixel_format) {
                ctx->లక్షణాలు[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .విలువ.type    = VAGeneric_విలువ_Type_Integer,
                    .విలువ.విలువ.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_లక్షణాలు);
        } లేకపోతే {
            ctx->లక్షణాలు = ఖాళీ;
            ctx->nb_లక్షణాలు = 0;
        }

        ctx->rt_format = desc->rt_format;

        ఒకవేళ (hwfc->initial_pool_కొలత > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_కొలత *
                                          పరిమాణం(*avfc->surface_ids));
            ఒకవేళ (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
        } లేకపోతే {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ఖాళీ;
        }

        ffhwframesctx(hwfc)->pool_అంతర్గత =
            av_బఫరు_pool_init2(పరిమాణం(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(hwfc)->pool_అంతర్గత) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    ఒకవేళ (hwfc->pool) {
        test_surface = av_బఫరు_pool_get(hwfc->pool);
        ఒకవేళ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    } లేకపోతే {
        test_surface = av_బఫరు_pool_get(ffhwframesctx(hwfc)->pool_అంతర్గత);
        ఒకవేళ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->దత్తాంశం;

    ctx->derive_పనిచేస్తుంది = 0;
    ఒకవేళ (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        ఒకవేళ (vas == VA_స్థితి_SUCCESS) {
            ఒకవేళ (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_పనిచేస్తుంది = 1;
            } లేకపోతే {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } లేకపోతే {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } లేకపోతే {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_బఫరు_unref(&test_surface);
    తిరిగి 0;

fail:
    av_బఫరు_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->లక్షణాలు);
    తిరిగి err;
}

స్థిర శూన్య vaapi_చట్రాలు_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->లక్షణాలు);
}

స్థిర పూర్ణాంకం vaapi_get_బఫరు(AVHWFramesContext *hwfc, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(hwfc->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[3] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_VAAPI;
    చట్రం->వెడల్పు   = hwfc->వెడల్పు;
    చట్రం->ఎత్తు  = hwfc->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      గణన AVHWFrameTransferDirection dir,
                                      గణన AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    గణన AVPixelFormat *pix_fmts;
    పూర్ణాంకం i, k, sw_format_అందుబాటు;

    sw_format_అందుబాటు = 0;
    కొరకు (i = 0; i < ctx->nb_formats; i++) {
        ఒకవేళ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_అందుబాటు = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * పరిమాణం(*pix_fmts));
    ఒకవేళ (!pix_fmts)
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (sw_format_అందుబాటు) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } లేకపోతే {
        k = 0;
    }
    కొరకు (i = 0; i < ctx->nb_formats; i++) {
        ఒకవేళ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            కొనసాగు;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    తిరిగి 0;
}

స్థిర శూన్య vaapi_unmap_చట్రం(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ఆధారం->దత్తాంశం[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_బఫరు(hwctx->display, map->image.buf);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    ఒకవేళ ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_ప్రత్యక్ష)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->వెడల్పు, hwfc->ఎత్తు,
                         0, 0, hwfc->వెడల్పు, hwfc->ఎత్తు);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

స్థిర పూర్ణాంకం vaapi_map_చట్రం(AVHWFramesContext *hwfc,
                           AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    స్థిరరాశి VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    శూన్య *చిరునామా = ఖాళీ;
    పూర్ణాంకం err, i;
#ఒకవేళ VA_CHECK_సంస్కరణ(1, 21, 0)
    uint32_t vaflags = 0;
#అయితే_ముగింపు

    surface_id = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    ఒకవేళ (!ctx->derive_పనిచేస్తుంది && (flags & AV_HWFRAME_MAP_ప్రత్యక్ష)) {
        // Requested direct mapping but it is not possible.
        తిరిగి AVERROR(EINVAL);
    }
    ఒకవేళ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ఒకవేళ (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_ప్రత్యక్ష)) {
        // Requested direct mapping but the formats do not match.
        తిరిగి AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    ఒకవేళ (err < 0) {
        // Requested format is not a valid output format.
        తిరిగి err;
    }

    map = av_malloc(పరిమాణం(*map));
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    ఒకవేళ (ctx->derive_పనిచేస్తుంది && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_ప్రత్యక్ష) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }
        ఒకవేళ (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }
        map->flags |= AV_HWFRAME_MAP_ప్రత్యక్ష;
    } లేకపోతే {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->వెడల్పు, hwfc->ఎత్తు, &map->image);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }
        ఒకవేళ (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->వెడల్పు, hwfc->ఎత్తు, map->image.image_id);
            ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }
        }
    }

#ఒకవేళ VA_CHECK_సంస్కరణ(1, 21, 0)
    ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &చిరునామా, vaflags);
#లేకపోతే
    vas = va_Map_బఫరు(hwctx->display, map->image.buf, &చిరునామా);
#అయితే_ముగింపు
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx,
                                dst, src, &vaapi_unmap_చట్రం, map);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    కొరకు (i = 0; i < map->image.అంకె_planes; i++) {
        dst->దత్తాంశం[i] = (uint8_t*)చిరునామా + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    ఒకవేళ (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->దత్తాంశం[1], dst->దత్తాంశం[2]);
    }

    తిరిగి 0;

fail:
    ఒకవేళ (map) {
        ఒకవేళ (చిరునామా)
            va_Unmap_బఫరు(hwctx->display, map->image.buf);
        ఒకవేళ (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    తిరిగి err;
}

స్థిర పూర్ణాంకం vaapi_transfer_దత్తాంశం_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (dst->వెడల్పు > hwfc->వెడల్పు || dst->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_చట్రం(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = dst->వెడల్పు;
    map->ఎత్తు = dst->ఎత్తు;

    err = av_చట్రం_copy(dst, map);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vaapi_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *hwfc,
                                  AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (src->వెడల్పు > hwfc->వెడల్పు || src->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_చట్రం(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = src->వెడల్పు;
    map->ఎత్తు = src->ఎత్తు;

    err = av_చట్రం_copy(map, src);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vaapi_map_గమ్యం_జ్ఞాపకం(AVHWFramesContext *hwfc, AVFrame *dst,
                               స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;

    err = vaapi_map_చట్రం(hwfc, dst, src, flags);
    ఒకవేళ (err)
        తిరిగి err;

    err = av_చట్రం_copy_props(dst, src);
    ఒకవేళ (err)
        తిరిగి err;

    తిరిగి 0;
}

#ఒకవేళ CONFIG_LIBDRM

#నిర్వచించు DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
స్థిర స్థిరరాశి నిర్మాణం {
    uint32_t va_fourcc;
    పూర్ణాంకం   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#నిర్వచితమైతే DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#అయితే_ముగింపు
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#ఒకవేళ defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#అయితే_ముగింపు
#ఒకవేళ defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#అయితే_ముగింపు
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#నిర్వచితమైతే VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#అయితే_ముగింపు
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#ఒకవేళ defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#అయితే_ముగింపు
#ఒకవేళ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#అయితే_ముగింపు
#ఒకవేళ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#అయితే_ముగింపు
#ఒకవేళ defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#అయితే_ముగింపు
};
#నిర్వచనం_రద్దు DRM_MAP

స్థిర శూన్య vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

స్థిర పూర్ణాంకం vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
#ఒకవేళ VA_CHECK_సంస్కరణ(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    పూర్ణాంకం use_prime2;
#లేకపోతే
    పూర్ణాంకం k;
#అయితే_ముగింపు
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    స్థిరరాశి AVDRMFrameDescriptor *desc;
    స్థిరరాశి VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_స్థితి_SUCCESS;
    uint32_t va_fourcc;
    పూర్ణాంకం err, i, j;

#ఒకవేళ !VA_CHECK_సంస్కరణ(1, 1, 0)
    గుర్తులేని దీర్ఘ బఫరు_handle;
    VASurfaceAttribExternalBuffers బఫరు_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurface_Attrib_జ్ఞాపకం_Type,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .విలువ.type    = VAGeneric_విలువ_Type_Integer,
            .విలువ.విలువ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ప్రధానసంఖ్య,
        },
        {
            .type  = VASurface_Attrib_External_బఫరు_Descriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .విలువ.type    = VAGeneric_విలువ_Type_సూచిక,
            .విలువ.విలువ.p = &బఫరు_desc,
        }
    };
#అయితే_ముగింపు

    desc = (AVDRMFrameDescriptor*)src->దత్తాంశం[0];

    ఒకవేళ (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        తిరిగి AVERROR(EINVAL);
    }

    va_fourcc = 0;
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ఒకవేళ (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            కొనసాగు;
        కొరకు (j = 0; j < desc->nb_layers; j++) {
            ఒకవేళ (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                ఆపు;
        }
        ఒకవేళ (j != desc->nb_layers)
            కొనసాగు;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        ఆపు;
    }
    ఒకవేళ (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        తిరిగి AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#ఒకవేళ VA_CHECK_సంస్కరణ(1, 1, 0)
    use_prime2 = !src_vafc->ప్రధానసంఖ్య_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    ఒకవేళ (use_prime2) {
        VADRMPRIMESurfaceDescriptor ప్రధానసంఖ్య_desc;
        VASurfaceAttrib ప్రధానసంఖ్య_attrs[2] = {
            {
                .type  = VASurface_Attrib_జ్ఞాపకం_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .విలువ.type    = VAGeneric_విలువ_Type_Integer,
                .విలువ.విలువ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ప్రధానసంఖ్య_2,
            },
            {
                .type  = VASurface_Attrib_External_బఫరు_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .విలువ.type    = VAGeneric_విలువ_Type_సూచిక,
                .విలువ.విలువ.p = &ప్రధానసంఖ్య_desc,
            }
        };
        ప్రధానసంఖ్య_desc.fourcc = va_fourcc;
        ప్రధానసంఖ్య_desc.వెడల్పు = src_fc->వెడల్పు;
        ప్రధానసంఖ్య_desc.ఎత్తు = src_fc->ఎత్తు;
        ప్రధానసంఖ్య_desc.అంకె_objects = desc->nb_objects;
        కొరకు (i = 0; i < desc->nb_objects; ++i) {
            ప్రధానసంఖ్య_desc.objects[i].fd = desc->objects[i].fd;
            ప్రధానసంఖ్య_desc.objects[i].కొలత = desc->objects[i].కొలత;
            ప్రధానసంఖ్య_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        ప్రధానసంఖ్య_desc.అంకె_layers = desc->nb_layers;
        కొరకు (i = 0; i < desc->nb_layers; ++i) {
            ప్రధానసంఖ్య_desc.layers[i].drm_format = desc->layers[i].format;
            ప్రధానసంఖ్య_desc.layers[i].అంకె_planes = desc->layers[i].nb_planes;
            కొరకు (j = 0; j < desc->layers[i].nb_planes; ++j) {
                ప్రధానసంఖ్య_desc.layers[i].object_సూచీ[j] =
                        desc->layers[i].planes[j].object_సూచీ;
                ప్రధానసంఖ్య_desc.layers[i].స్థానభ్రంశం[j] = desc->layers[i].planes[j].స్థానభ్రంశం;
                ప్రధానసంఖ్య_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            ఒకవేళ (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, ప్రధానసంఖ్య_desc.layers[i].pitch[1],
                    ప్రధానసంఖ్య_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, ప్రధానసంఖ్య_desc.layers[i].స్థానభ్రంశం[1],
                    ప్రధానసంఖ్య_desc.layers[i].స్థానభ్రంశం[2]);
            }
        }

        /*
         * We can query for PRIME_2 support with vaQuerySurfaceAttributes, but that
         * that needs the config_id which we don't have here . Both Intel and
         * Gallium seem to do the correct error checks, so lets just try the
         * PRIME_2 import first.
         */
        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->వెడల్పు, src->ఎత్తు, &surface_id, 1,
                               ప్రధానసంఖ్య_attrs, FF_ARRAY_ELEMS(ప్రధానసంఖ్య_attrs));
        ఒకవేళ (vas != VA_స్థితి_SUCCESS)
            src_vafc->ప్రధానసంఖ్య_2_import_unsupported = 1;
    }

    ఒకవేళ (!use_prime2 || vas != VA_స్థితి_SUCCESS) {
        పూర్ణాంకం k;
        uintptr_t బఫరు_handle;
        VASurfaceAttribExternalBuffers బఫరు_desc;
        VASurfaceAttrib బఫరు_attrs[2] = {
            {
                .type  = VASurface_Attrib_జ్ఞాపకం_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .విలువ.type    = VAGeneric_విలువ_Type_Integer,
                .విలువ.విలువ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ప్రధానసంఖ్య,
            },
            {
                .type  = VASurface_Attrib_External_బఫరు_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .విలువ.type    = VAGeneric_విలువ_Type_సూచిక,
                .విలువ.విలువ.p = &బఫరు_desc,
            }
        };

        బఫరు_handle = desc->objects[0].fd;
        బఫరు_desc.pixel_format = va_fourcc;
        బఫరు_desc.వెడల్పు        = src_fc->వెడల్పు;
        బఫరు_desc.ఎత్తు       = src_fc->ఎత్తు;
        బఫరు_desc.దత్తాంశం_కొలత    = desc->objects[0].కొలత;
        బఫరు_desc.buffers      = &బఫరు_handle;
        బఫరు_desc.అంకె_buffers  = 1;
        బఫరు_desc.flags        = 0;

        k = 0;
        కొరకు (i = 0; i < desc->nb_layers; i++) {
            కొరకు (j = 0; j < desc->layers[i].nb_planes; j++) {
                బఫరు_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                బఫరు_desc.offsets[k] = desc->layers[i].planes[j].స్థానభ్రంశం;
                ++k;
            }
        }
        బఫరు_desc.అంకె_planes = k;

        ఒకవేళ (format_desc->chroma_planes_swapped &&
            బఫరు_desc.అంకె_planes == 3) {
            FFSWAP(uint32_t, బఫరు_desc.pitches[1], బఫరు_desc.pitches[2]);
            FFSWAP(uint32_t, బఫరు_desc.offsets[1], బఫరు_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->వెడల్పు, src->ఎత్తు,
                               &surface_id, 1,
                               బఫరు_attrs, FF_ARRAY_ELEMS(బఫరు_attrs));
    }
#లేకపోతే
    బఫరు_handle = desc->objects[0].fd;
    బఫరు_desc.pixel_format = va_fourcc;
    బఫరు_desc.వెడల్పు        = src_fc->వెడల్పు;
    బఫరు_desc.ఎత్తు       = src_fc->ఎత్తు;
    బఫరు_desc.దత్తాంశం_కొలత    = desc->objects[0].కొలత;
    బఫరు_desc.buffers      = &బఫరు_handle;
    బఫరు_desc.అంకె_buffers  = 1;
    బఫరు_desc.flags        = 0;

    k = 0;
    కొరకు (i = 0; i < desc->nb_layers; i++) {
        కొరకు (j = 0; j < desc->layers[i].nb_planes; j++) {
            బఫరు_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            బఫరు_desc.offsets[k] = desc->layers[i].planes[j].స్థానభ్రంశం;
            ++k;
        }
    }
    బఫరు_desc.అంకె_planes = k;

    ఒకవేళ (format_desc->chroma_planes_swapped &&
        బఫరు_desc.అంకె_planes == 3) {
        FFSWAP(uint32_t, బఫరు_desc.pitches[1], బఫరు_desc.pitches[2]);
        FFSWAP(uint32_t, బఫరు_desc.offsets[1], బఫరు_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->వెడల్పు, src->ఎత్తు,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#అయితే_ముగింపు
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        తిరిగి AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (శూన్య*)(uintptr_t)surface_id);
    ఒకవేళ (err < 0)
        తిరిగి err;

    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;
    dst->దత్తాంశం[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    తిరిగి 0;
}

#ఒకవేళ VA_CHECK_సంస్కరణ(1, 1, 0)
స్థిర శూన్య vaapi_unmap_గమ్యం_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

స్థిర పూర్ణాంకం vaapi_map_గమ్యం_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ఖాళీ;
    uint32_t export_flags;
    పూర్ణాంకం err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    ఒకవేళ (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            తిరిగి AVERROR(EIO);
        }
    }

    ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ప్రధానసంఖ్య_2,
                                export_flags, &va_desc);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        ఒకవేళ (vas == VA_స్థితి_ERROR_UNIMPLEMENTED)
            తిరిగి AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        తిరిగి AVERROR(EIO);
    }

    drm_desc = av_mallocz(పరిమాణం(*drm_desc));
    ఒకవేళ (!drm_desc) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.అంకె_objects;
    కొరకు (i = 0; i < va_desc.అంకె_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].కొలత = va_desc.objects[i].కొలత;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.అంకె_layers;
    కొరకు (i = 0; i < va_desc.అంకె_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].అంకె_planes;
        కొరకు (j = 0; j < va_desc.layers[i].అంకె_planes; j++) {
            drm_desc->layers[i].planes[j].object_సూచీ =
                va_desc.layers[i].object_సూచీ[j];
            drm_desc->layers[i].planes[j].స్థానభ్రంశం =
                va_desc.layers[i].స్థానభ్రంశం[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src,
                                &vaapi_unmap_గమ్యం_drm_esh, drm_desc);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;
    dst->దత్తాంశం[0] = (uint8_t*)drm_desc;

    తిరిగి 0;

fail:
    కొరకు (i = 0; i < va_desc.అంకె_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    తిరిగి err;
}
#అయితే_ముగింపు

#ఒకవేళ VA_CHECK_సంస్కరణ(0, 36, 0)
రకనిర్వచనం నిర్మాణం VAAPIDRMImage_బఫరు_Mapping {
    VAImage      image;
    VABufferInfo బఫరు_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_బఫరు_Mapping;

స్థిర శూన్య vaapi_unmap_గమ్యం_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_బఫరు_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ఆధారం->దత్తాంశం[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_బఫరు_Handle(hwctx->display, mapping->image.buf);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

స్థిర పూర్ణాంకం vaapi_map_గమ్యం_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_బఫరు_Mapping *mapping = ఖాళీ;
    VASurfaceID surface_id;
    VAStatus vas;
    పూర్ణాంకం err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(పరిమాణం(*mapping));
    ఒకవేళ (!mapping)
        తిరిగి AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ఒకవేళ (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            ఆపు;
    }
    ఒకవేళ (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        వెళ్ళు fail_derived;
    }

    mapping->బఫరు_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ప్రధానసంఖ్య;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    ఒకవేళ (mapping->drm_desc.nb_layers > 1) {
        ఒకవేళ (mapping->drm_desc.nb_layers != mapping->image.అంకె_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.అంకె_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            వెళ్ళు fail_derived;
        }

        కొరకు(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_సూచీ = 0,
                    .స్థానభ్రంశం       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } లేకపోతే {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.అంకె_planes;
        కొరకు (p = 0; p < mapping->image.అంకె_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_సూచీ = 0,
                .స్థానభ్రంశం       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_బఫరు_Handle(hwctx->display, mapping->image.buf,
                                &mapping->బఫరు_info);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        వెళ్ళు fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->బఫరు_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->బఫరు_info.handle,
        .కొలత = mapping->image.దత్తాంశం_కొలత,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx,
                                dst, src, &vaapi_unmap_గమ్యం_drm_abh,
                                mapping);
    ఒకవేళ (err < 0)
        వెళ్ళు fail_mapped;

    dst->దత్తాంశం[0] = (uint8_t*)&mapping->drm_desc;
    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;

    తిరిగి 0;

fail_mapped:
    va_Release_బఫరు_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    తిరిగి err;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vaapi_map_గమ్యం_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
#ఒకవేళ VA_CHECK_సంస్కరణ(1, 1, 0)
    పూర్ణాంకం err;
    err = vaapi_map_గమ్యం_drm_esh(hwfc, dst, src, flags);
    ఒకవేళ (err != AVERROR(ENOSYS))
        తిరిగి err;
#అయితే_ముగింపు
#ఒకవేళ VA_CHECK_సంస్కరణ(0, 36, 0)
    తిరిగి vaapi_map_గమ్యం_drm_abh(hwfc, dst, src, flags);
#అయితే_ముగింపు
    తిరిగి AVERROR(ENOSYS);
}

#అయితే_ముగింపు /* CONFIG_LIBDRM */

స్థిర పూర్ణాంకం vaapi_map_గమ్యం(AVHWFramesContext *hwfc, AVFrame *dst,
                        స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    ఎంపిక (src->format) {
#ఒకవేళ CONFIG_LIBDRM
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        తిరిగి vaapi_map_from_drm(hwfc, dst, src, flags);
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }
}

స్థిర పూర్ణాంకం vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    ఎంపిక (dst->format) {
#ఒకవేళ CONFIG_LIBDRM
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        తిరిగి vaapi_map_గమ్యం_drm(hwfc, dst, src, flags);
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి vaapi_map_గమ్యం_జ్ఞాపకం(hwfc, dst, src, flags);
    }
}

స్థిర శూన్య vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    ఒకవేళ (hwctx->display)
        vaTerminate(hwctx->display);

#ఒకవేళ HAVE_VAAPI_X11
    ఒకవేళ (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#అయితే_ముగింపు

#ఒకవేళ HAVE_VAAPI_DRM
    ఒకవేళ (priv->drm_fd >= 0)
        close(priv->drm_fd);
#అయితే_ముగింపు

    av_freep(&priv);
}

#ఒకవేళ CONFIG_VAAPI_1
స్థిర శూన్య vaapi_device_log_error(శూన్య *context, స్థిరరాశి అక్షరం *సందేశం_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", సందేశం_2);
}

స్థిర శూన్య vaapi_device_log_info(శూన్య *context, స్థిరరాశి అక్షరం *సందేశం_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", సందేశం_2);
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    పూర్ణాంకం major, minor;
    VAStatus vas;

#ఒకవేళ CONFIG_VAAPI_1
    va_సమితి_Error_Callback(display, &vaapi_device_log_error, ctx);
    va_సమితి_Info_Callback (display, &vaapi_device_log_info,  ctx);
#అయితే_ముగింపు

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        తిరిగి AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vaapi_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                               AVDictionary *opts, పూర్ణాంకం flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ఖాళీ;
    స్థిరరాశి AVDictionary_నమోదు *ent;
    పూర్ణాంకం try_drm, try_x11, try_win32, try_all av_వాడని;

    priv = av_mallocz(పరిమాణం(*priv));
    ఒకవేళ (!priv)
        తిరిగి AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->విడుదల        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ఖాళీ, 0);
    ఒకవేళ (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        ఒకవేళ (!strcmp(ent->విలువ, "drm")) {
            try_drm = 1;
        } లేకపోతే ఒకవేళ (!strcmp(ent->విలువ, "x11")) {
            try_x11 = 1;
        } లేకపోతే ఒకవేళ (!strcmp(ent->విలువ, "win32")) {
            try_win32 = 1;
        } లేకపోతే {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->విలువ);
            తిరిగి AVERROR(EINVAL);
        }
    } లేకపోతే {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#ఒకవేళ HAVE_VAAPI_DRM
    అయితే (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        పూర్ణాంకం loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        ఒకవేళ (device) {
            priv->drm_fd = open(device, O_RDWR);
            ఒకవేళ (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                ఆపు;
            }
        } లేకపోతే {
            అక్షరం మార్గం[64];
            పూర్ణాంకం n, max_devices = 8;
#ఒకవేళ CONFIG_LIBDRM
            drm_సంస్కరణ *info;
            స్థిరరాశి AVDictionary_నమోదు *kernel_driver;
            స్థిరరాశి AVDictionary_నమోదు *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ఖాళీ, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ఖాళీ, 0);
#అయితే_ముగింపు
            కొరకు (n = 0; n < max_devices; n++) {
                snprintf(మార్గం, పరిమాణం(మార్గం),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(మార్గం, O_RDWR);
                ఒకవేళ (priv->drm_fd < 0) {
                    ఒకవేళ (errno == ENOENT) {
                        ఒకవేళ (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", మార్గం);
                            కొనసాగు;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } లేకపోతే
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    ఆపు;
                }
#ఒకవేళ CONFIG_LIBDRM
                info = drm_Get_సంస్కరణ(priv->drm_fd);
                ఒకవేళ (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    కొనసాగు;
                }
                ఒకవేళ (kernel_driver) {
                    ఒకవేళ (strcmp(kernel_driver->విలువ, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drm_Free_సంస్కరణ(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        కొనసాగు;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drm_Free_సంస్కరణ(info);
                    ఆపు;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } లేకపోతే ఒకవేళ (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drm_Free_సంస్కరణ(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    కొనసాగు;
                } లేకపోతే ఒకవేళ (vendor_id) {
                    drmDevicePtr device;
                    అక్షరం drm_vendor[8];
                    ఒకవేళ (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_సంస్కరణ(info);
                        కొనసాగు;
                    }

                    snprintf(drm_vendor, పరిమాణం(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    ఒకవేళ (strcmp(vendor_id->విలువ, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->విలువ);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_సంస్కరణ(info);
                        కొనసాగు;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->విలువ);
                    drmFreeDevice(&device);
                    drm_Free_సంస్కరణ(info);
                    ఆపు;
                }
                drm_Free_సంస్కరణ(info);
#అయితే_ముగింపు
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                ఆపు;
            }
            ఒకవేళ (n >= max_devices)
                ఆపు;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        ఒకవేళ (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            తిరిగి AVERROR_EXTERNAL;
        }
        ఆపు;
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_VAAPI_X11
    ఒకవేళ (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        ఒకవేళ (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } లేకపోతే {
            display = vaGetDisplay(priv->x11_display);
            ఒకవేళ (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                తిరిగి AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_VAAPI_WIN32
    ఒకవేళ (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        ఒకవేళ (!device) {
            display = vaGetDisplayWin32(ఖాళీ);
        } లేకపోతే {
            IDXGIFactory2 *pDXGIFactory = ఖాళీ;
            IDXGIAdapter *pAdapter = ఖాళీ;
#ఒకవేళ !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            ఒకవేళ (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                తిరిగి AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            ఒకవేళ (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                తిరిగి AVERROR_UNKNOWN;
            }
#లేకపోతే
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#అయితే_ముగింపు
            ఒకవేళ (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (శూన్య **)&pDXGIFactory))) {
                పూర్ణాంకం adapter = atoi(device);
                ఒకవేళ (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    ఒకవేళ (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.దిగువ_Part,
                              desc.AdapterLuid.ఎగువ_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#ఒకవేళ !HAVE_UWP
            dlclose(dxgi);
#అయితే_ముగింపు
        }

        ఒకవేళ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            తిరిగి AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#అయితే_ముగింపు

    ఒకవేళ (!display) {
        ఒకవేళ (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        లేకపోతే
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        తిరిగి AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ఖాళీ, 0);
    ఒకవేళ (ent) {
#ఒకవేళ VA_CHECK_సంస్కరణ(0, 38, 0)
        VAStatus vas;
        vas = va_సమితి_Driver_Name(display, ent->విలువ);
        ఒకవేళ (vas != VA_స్థితి_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->విలువ, vas, vaErrorStr(vas));
            vaTerminate(display);
            తిరిగి AVERROR_EXTERNAL;
        }
#లేకపోతే
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#అయితే_ముగింపు
    }

    తిరిగి vaapi_device_connect(ctx, display);
}

స్థిర పూర్ణాంకం vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, పూర్ణాంకం flags)
{
#ఒకవేళ HAVE_VAAPI_DRM
    ఒకవేళ (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        పూర్ణాంకం fd;

        ఒకవేళ (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            తిరిగి AVERROR(EINVAL);
        }

#ఒకవేళ CONFIG_LIBDRM
        {
            పూర్ణాంకం కణుపు_type = drm_Get_కణుపు_Type_From_Fd(src_hwctx->fd);
            అక్షరం *render_కణుపు;
            ఒకవేళ (కణుపు_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                తిరిగి AVERROR(EINVAL);
            }
            ఒకవేళ (కణుపు_type == DRM_కణుపు_RENDER) {
                fd = src_hwctx->fd;
            } లేకపోతే {
                render_కణుపు = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                ఒకవేళ (!render_కణుపు) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } లేకపోతే {
                    fd = open(render_కణుపు, O_RDWR);
                    ఒకవేళ (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } లేకపోతే {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_కణుపు);
                    }
                    విడుదల(render_కణుపు);
                }
            }
        }
#లేకపోతే
        fd = src_hwctx->fd;
#అయితే_ముగింపు

        priv = av_mallocz(పరిమాణం(*priv));
        ఒకవేళ (!priv) {
            ఒకవేళ (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            తిరిగి AVERROR(ENOMEM);
        }

        ఒకవేళ (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } లేకపోతే {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->విడుదల        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        ఒకవేళ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            తిరిగి AVERROR(EIO);
        }

        తిరిగి vaapi_device_connect(ctx, display);
    }
#అయితే_ముగింపు
    తిరిగి AVERROR(ENOSYS);
}

స్థిరరాశి HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_కొలత      = పరిమాణం(VAAPIDeviceContext),
    .device_hwconfig_కొలత   = పరిమాణం(AVVAAPIHWConfig),
    .చట్రాలు_hwctx_కొలత      = పరిమాణం(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .చట్రాలు_get_constraints = &vaapi_చట్రాలు_get_constraints,
    .చట్రాలు_init            = &vaapi_చట్రాలు_init,
    .చట్రాలు_uninit          = &vaapi_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు      = &vaapi_get_బఫరు,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = &vaapi_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from     = &vaapi_transfer_దత్తాంశం_from,
    .map_గమ్యం                 = &vaapi_map_గమ్యం,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
