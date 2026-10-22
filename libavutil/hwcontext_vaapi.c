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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ಶೂನ್ಯ **ppFactory);
#endif
#ಯದಿ HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#ಯದಿ HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#ಯದಿ CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಯದಿ HAVE_UNISTD_H
#   include <unistd.h>
#endif


#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"


ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIDevicePriv {
#ಯದಿ HAVE_VAAPI_X11
    Display *x11_display;
#endif

    ಪೂರ್ಣಾಙ್ಕ drm_fd;
} VAAPIDevicePriv;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPISurfaceFormat {
    ಗಣನಾ AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned ಪೂರ್ಣಾಙ್ಕ fourcc;
} VAAPISurfaceFormat;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    ಪೂರ್ಣಾಙ್ಕ              nb_formats;
} VAAPIDeviceContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    ಪೂರ್ಣಾಙ್ಕ           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned ಪೂರ್ಣಾಙ್ಕ rt_format;
    // Whether vaDeriveImage works.
    ಪೂರ್ಣಾಙ್ಕ derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    ಪೂರ್ಣಾಙ್ಕ ಅವಿಭಾಜ್ಯ_2_import_unsupported;
} VAAPIFramesContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    ಪೂರ್ಣಾಙ್ಕ flags;
} VAAPIMapping;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIFormat {
    unsigned ಪೂರ್ಣಾಙ್ಕ fourcc;
    unsigned ಪೂರ್ಣಾಙ್ಕ rt_format;
    ಗಣನಾ AVPixelFormat pix_fmt;
    ಪೂರ್ಣಾಙ್ಕ chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ಸ್ಥಿರ ಧ್ರುವ VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#ifdef VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#endif
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#ifdef VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#endif
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#ifdef VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#endif
#ifdef VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#endif
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#ifdef VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#endif
    MAP(Y800, YUV400,  GRAY8,   0),
#ifdef VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#endif
#ifdef VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#endif
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#ifdef VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#endif
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#ifdef VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#endif
#ifdef VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#endif
#ifdef VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#endif
};
#undef MAP

ಸ್ಥಿರ ಧ್ರುವ VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned ಪೂರ್ಣಾಙ್ಕ fourcc)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        ಯದಿ (vaapi_format_map[i].fourcc == fourcc)
            ಪ್ರತ್ಯಾಗಮ &vaapi_format_map[i];
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಧ್ರುವ VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(ಗಣನಾ AVPixelFormat pix_fmt, ಧ್ರುವ VAAPIFormatDescriptor *prev)
{
    ಧ್ರುವ VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    ಯದಿ (!prev)
        prev = vaapi_format_map;
    ಅನ್ಯಥಾ
        prev++;

    ಪ್ರತಿ (; prev < end; prev++)
        ಯದಿ (prev->pix_fmt == pix_fmt)
            ಪ್ರತ್ಯಾಗಮ prev;
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಗಣನಾ AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned ಪೂರ್ಣಾಙ್ಕ fourcc)
{
    ಧ್ರುವ VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    ಯದಿ (desc)
        ಪ್ರತ್ಯಾಗಮ desc->pix_fmt;
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ AV_PIX_FMT_NONE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  ಗಣನಾ AVPixelFormat pix_fmt,
                                  ಧ್ರುವ VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ಧ್ರುವ VAAPIFormatDescriptor *desc = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯಾವತ್ ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        ಪ್ರತಿ (i = 0; i < ctx->nb_formats; i++) {
            ಯದಿ (ctx->formats[i].fourcc == desc->fourcc) {
                ಯದಿ (_desc)
                    *_desc = desc;
                ಯದಿ (image_format)
                    *image_format = &ctx->formats[i].image_format;
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  ಗಣನಾ AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    ಯದಿ (!image_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಪ್ರತ್ಯಾಗಮ vaapi_get_img_desc_and_format(hwdev, pix_fmt, ರಿಕ್ತ, image_format);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ಧ್ರುವ AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ರಿಕ್ತ;
    VAStatus vas;
    ಗಣನಾ AVPixelFormat pix_fmt;
    unsigned ಪೂರ್ಣಾಙ್ಕ fourcc;
    ಪೂರ್ಣಾಙ್ಕ err, i, j, attr_ಎಣಿಕೆ, pix_fmt_ಎಣಿಕೆ;

    ಯದಿ (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_ಎಣಿಕೆ = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_ಎಣಿಕೆ);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ಗಚ್ಛ fail;
        }

        attr_list = av_malloc(attr_ಎಣಿಕೆ * ಪರಿಮಾಣ(*attr_list));
        ಯದಿ (!attr_list) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_ಎಣಿಕೆ);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ಗಚ್ಛ fail;
        }

        pix_fmt_ಎಣಿಕೆ = 0;
        ಪ್ರತಿ (i = 0; i < attr_ಎಣಿಕೆ; i++) {
            ವಿಕಲ್ಪ (attr_list[i].type) {
            ಪಕ್ಷ VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                ಯದಿ (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_ಎಣಿಕೆ;
                } ಅನ್ಯಥಾ {
                    // Something unsupported - ignore.
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ಭಙ್ಗ;
            ಪಕ್ಷ VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ಭಙ್ಗ;
            ಪಕ್ಷ VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ಭಙ್ಗ;
            ಪಕ್ಷ VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (pix_fmt_ಎಣಿಕೆ == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ರಿಕ್ತ;
        } ಅನ್ಯಥಾ {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_ಎಣಿಕೆ + 1,
                                                            ಪರಿಮಾಣ(pix_fmt));
            ಯದಿ (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }

            ಪ್ರತಿ (i = j = 0; i < attr_ಎಣಿಕೆ; i++) {
                ಪೂರ್ಣಾಙ್ಕ k;

                ಯದಿ (attr_list[i].type != VASurfaceAttribPixelFormat)
                    ಅನುವರ್ತ;
                fourcc = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                ಯದಿ (pix_fmt == AV_PIX_FMT_NONE)
                    ಅನುವರ್ತ;

                ಪ್ರತಿ (k = 0; k < j; k++) {
                    ಯದಿ (constraints->valid_sw_formats[k] == pix_fmt)
                        ಭಙ್ಗ;
                }

                ಯದಿ (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } ಅನ್ಯಥಾ {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        ಪರಿಮಾಣ(pix_fmt));
        ಯದಿ (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
        ಪ್ರತಿ (i = j = 0; i < ctx->nb_formats; i++) {
            ಪೂರ್ಣಾಙ್ಕ k;

            ಪ್ರತಿ (k = 0; k < j; k++) {
                ಯದಿ (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    ಭಙ್ಗ;
            }

            ಯದಿ (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(pix_fmt));
    ಯದಿ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *friendly_name;
    ಧ್ರುವ ವರ್ಣ *match_string;
    unsigned ಪೂರ್ಣಾಙ್ಕ quirks;
} vaapi_driver_quirks_table[] = {
#ಯದಿ !VA_CHECK_VERSION(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#endif
    {
        "Intel iHD",
        "ubit",
        AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE,
    },
    {
        "VDPAU wrapper",
        "Splitted-Desktop Systems VDPAU backend for VA-API",
        AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES,
    },
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ರಿಕ್ತ;
    VAStatus vas;
    ಧ್ರುವ ವರ್ಣ *vendor_string;
    ಪೂರ್ಣಾಙ್ಕ err, i, image_ಎಣಿಕೆ;
    ಗಣನಾ AVPixelFormat pix_fmt;
    unsigned ಪೂರ್ಣಾಙ್ಕ fourcc;

    image_ಎಣಿಕೆ = va_Max_ಅಂಕೆ_Image_Formats(hwctx->display);
    ಯದಿ (image_ಎಣಿಕೆ <= 0) {
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }
    image_list = av_malloc(image_ಎಣಿಕೆ * ಪರಿಮಾಣ(*image_list));
    ಯದಿ (!image_list) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_ಎಣಿಕೆ);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }

    ctx->formats  = av_malloc(image_ಎಣಿಕೆ * ಪರಿಮಾಣ(*ctx->formats));
    ಯದಿ (!ctx->formats) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    ctx->nb_formats = 0;
    ಪ್ರತಿ (i = 0; i < image_ಎಣಿಕೆ; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        ಯದಿ (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } ಅನ್ಯಥಾ {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    ಯದಿ (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    ಯದಿ (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } ಅನ್ಯಥಾ {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        ಯದಿ (vendor_string) {
            ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                ಯದಿ (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    ಭಙ್ಗ;
                }
            }
            ಯದಿ (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } ಅನ್ಯಥಾ {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_buffer_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ಸ್ಥಿರ AVBufferRef *vaapi_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    ಯದಿ (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           ಪರಿಮಾಣ(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    ಯದಿ (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    ಪ್ರತ್ಯಾಗಮ ref;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ಧ್ರುವ VAAPIFormatDescriptor *desc = ರಿಕ್ತ;
    VAImageFormat *expected_format = ರಿಕ್ತ;
    AVBufferRef *test_surface = ರಿಕ್ತ;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    ಪೂರ್ಣಾಙ್ಕ err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    ಯದಿ (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        ಯದಿ (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ರಿಕ್ತ)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಯದಿ (!hwfc->pool) {
        ಯದಿ (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            ಪೂರ್ಣಾಙ್ಕ need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            ಪೂರ್ಣಾಙ್ಕ need_pixel_format = 1;
            ಪ್ರತಿ (i = 0; i < avfc->nb_attributes; i++) {
                ಯದಿ (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                ಯದಿ (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        ಪರಿಮಾಣ(*ctx->attributes));
            ಯದಿ (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }

            ಪ್ರತಿ (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            ಯದಿ (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                    .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            ಯದಿ (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                    .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } ಅನ್ಯಥಾ {
            ctx->attributes = ರಿಕ್ತ;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        ಯದಿ (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          ಪರಿಮಾಣ(*avfc->surface_ids));
            ಯದಿ (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
        } ಅನ್ಯಥಾ {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ರಿಕ್ತ;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(ಪರಿಮಾಣ(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    ಯದಿ (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        ಯದಿ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        ಯದಿ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    ಯದಿ (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        ಯದಿ (vas == VA_STATUS_SUCCESS) {
            ಯದಿ (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } ಅನ್ಯಥಾ {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } ಅನ್ಯಥಾ {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } ಅನ್ಯಥಾ {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      ಗಣನಾ AVHWFrameTransferDirection dir,
                                      ಗಣನಾ AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    ಗಣನಾ AVPixelFormat *pix_fmts;
    ಪೂರ್ಣಾಙ್ಕ i, k, sw_format_available;

    sw_format_available = 0;
    ಪ್ರತಿ (i = 0; i < ctx->nb_formats; i++) {
        ಯದಿ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * ಪರಿಮಾಣ(*pix_fmts));
    ಯದಿ (!pix_fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } ಅನ್ಯಥಾ {
        k = 0;
    }
    ಪ್ರತಿ (i = 0; i < ctx->nb_formats; i++) {
        ಯದಿ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            ಅನುವರ್ತ;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    ಯದಿ ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ಧ್ರುವ VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    ಶೂನ್ಯ *address = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ err, i;
#ಯದಿ VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    ಯದಿ (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    ಯದಿ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಯದಿ (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    ಯದಿ (err < 0) {
        // Requested format is not a valid output format.
        ಪ್ರತ್ಯಾಗಮ err;
    }

    map = av_malloc(ಪರಿಮಾಣ(*map));
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    ಯದಿ (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }
        ಯದಿ (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } ಅನ್ಯಥಾ {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }
        ಯದಿ (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            ಯದಿ (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }
        }
    }

#ಯದಿ VA_CHECK_VERSION(1, 21, 0)
    ಯದಿ (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#ಅನ್ಯಥಾ
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತಿ (i = 0; i < map->image.ಅಂಕೆ_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    ಯದಿ (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (map) {
        ಯದಿ (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        ಯದಿ (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->width > hwfc->width || dst->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (src->width > hwfc->width || src->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    err = av_frame_copy_props(dst, src);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    uint32_t va_fourcc;
    ಪೂರ್ಣಾಙ್ಕ   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#ಯದಿ defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#ಯದಿ defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#ifdef VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#endif
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#ಯದಿ defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#ಯದಿ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#ಯದಿ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#ಯದಿ defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
#ಯದಿ VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    ಪೂರ್ಣಾಙ್ಕ use_prime2;
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ಧ್ರುವ AVDRMFrameDescriptor *desc;
    ಧ್ರುವ VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    ಪೂರ್ಣಾಙ್ಕ err, i, j;

#ಯದಿ !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
            .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Pointer,
            .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    ಯದಿ (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    va_fourcc = 0;
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ಯದಿ (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            ಅನುವರ್ತ;
        ಪ್ರತಿ (j = 0; j < desc->nb_layers; j++) {
            ಯದಿ (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                ಭಙ್ಗ;
        }
        ಯದಿ (j != desc->nb_layers)
            ಅನುವರ್ತ;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        ಭಙ್ಗ;
    }
    ಯದಿ (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#ಯದಿ VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->ಅವಿಭಾಜ್ಯ_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    ಯದಿ (use_prime2) {
        VADRMPRIMESurfaceDescriptor ಅವಿಭಾಜ್ಯ_desc;
        VASurfaceAttrib ಅವಿಭಾಜ್ಯ_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Pointer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &ಅವಿಭಾಜ್ಯ_desc,
            }
        };
        ಅವಿಭಾಜ್ಯ_desc.fourcc = va_fourcc;
        ಅವಿಭಾಜ್ಯ_desc.width = src_fc->width;
        ಅವಿಭಾಜ್ಯ_desc.height = src_fc->height;
        ಅವಿಭಾಜ್ಯ_desc.ಅಂಕೆ_objects = desc->nb_objects;
        ಪ್ರತಿ (i = 0; i < desc->nb_objects; ++i) {
            ಅವಿಭಾಜ್ಯ_desc.objects[i].fd = desc->objects[i].fd;
            ಅವಿಭಾಜ್ಯ_desc.objects[i].size = desc->objects[i].size;
            ಅವಿಭಾಜ್ಯ_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        ಅವಿಭಾಜ್ಯ_desc.ಅಂಕೆ_layers = desc->nb_layers;
        ಪ್ರತಿ (i = 0; i < desc->nb_layers; ++i) {
            ಅವಿಭಾಜ್ಯ_desc.layers[i].drm_format = desc->layers[i].format;
            ಅವಿಭಾಜ್ಯ_desc.layers[i].ಅಂಕೆ_planes = desc->layers[i].nb_planes;
            ಪ್ರತಿ (j = 0; j < desc->layers[i].nb_planes; ++j) {
                ಅವಿಭಾಜ್ಯ_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                ಅವಿಭಾಜ್ಯ_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            ಯದಿ (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[1],
                    ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, ಅವಿಭಾಜ್ಯ_desc.layers[i].offset[1],
                    ಅವಿಭಾಜ್ಯ_desc.layers[i].offset[2]);
            }
        }

        /*
         * We can query for PRIME_2 support with vaQuerySurfaceAttributes, but that
         * that needs the config_id which we don't have here . Both Intel and
         * Gallium seem to do the correct error checks, so lets just try the
         * PRIME_2 import first.
         */
        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height, &surface_id, 1,
                               ಅವಿಭಾಜ್ಯ_attrs, FF_ARRAY_ELEMS(ಅವಿಭಾಜ್ಯ_attrs));
        ಯದಿ (vas != VA_STATUS_SUCCESS)
            src_vafc->ಅವಿಭಾಜ್ಯ_2_import_unsupported = 1;
    }

    ಯದಿ (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        ಪೂರ್ಣಾಙ್ಕ k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Pointer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.ಅಂಕೆ_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        ಪ್ರತಿ (i = 0; i < desc->nb_layers; i++) {
            ಪ್ರತಿ (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.ಅಂಕೆ_planes = k;

        ಯದಿ (format_desc->chroma_planes_swapped &&
            buffer_desc.ಅಂಕೆ_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#ಅನ್ಯಥಾ
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.ಅಂಕೆ_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    ಪ್ರತಿ (i = 0; i < desc->nb_layers; i++) {
        ಪ್ರತಿ (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.ಅಂಕೆ_planes = k;

    ಯದಿ (format_desc->chroma_planes_swapped &&
        buffer_desc.ಅಂಕೆ_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (ಶೂನ್ಯ*)(uintptr_t)surface_id);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ VA_CHECK_VERSION(1, 1, 0)
ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ರಿಕ್ತ;
    uint32_t export_flags;
    ಪೂರ್ಣಾಙ್ಕ err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    ಯದಿ (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
        }
    }

    ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ_2,
                                export_flags, &va_desc);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        ಯದಿ (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

    drm_desc = av_mallocz(ಪರಿಮಾಣ(*drm_desc));
    ಯದಿ (!drm_desc) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.ಅಂಕೆ_objects;
    ಪ್ರತಿ (i = 0; i < va_desc.ಅಂಕೆ_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.ಅಂಕೆ_layers;
    ಪ್ರತಿ (i = 0; i < va_desc.ಅಂಕೆ_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].ಅಂಕೆ_planes;
        ಪ್ರತಿ (j = 0; j < va_desc.layers[i].ಅಂಕೆ_planes; j++) {
            drm_desc->layers[i].planes[j].object_index =
                va_desc.layers[i].object_index[j];
            drm_desc->layers[i].planes[j].offset =
                va_desc.layers[i].offset[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &vaapi_unmap_to_drm_esh, drm_desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (i = 0; i < va_desc.ಅಂಕೆ_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif

#ಯದಿ VA_CHECK_VERSION(0, 36, 0)
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = ರಿಕ್ತ;
    VASurfaceID surface_id;
    VAStatus vas;
    ಪೂರ್ಣಾಙ್ಕ err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(ಪರಿಮಾಣ(*mapping));
    ಯದಿ (!mapping)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ಯದಿ (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            ಭಙ್ಗ;
    }
    ಯದಿ (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        ಗಚ್ಛ fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    ಯದಿ (mapping->drm_desc.nb_layers > 1) {
        ಯದಿ (mapping->drm_desc.nb_layers != mapping->image.ಅಂಕೆ_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.ಅಂಕೆ_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail_derived;
        }

        ಪ್ರತಿ(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_index = 0,
                    .offset       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } ಅನ್ಯಥಾ {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.ಅಂಕೆ_planes;
        ಪ್ರತಿ (p = 0; p < mapping->image.ಅಂಕೆ_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಗಚ್ಛ fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->buffer_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->buffer_info.handle,
        .size = mapping->image.data_size,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_to_drm_abh,
                                mapping);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
#ಯದಿ VA_CHECK_VERSION(1, 1, 0)
    ಪೂರ್ಣಾಙ್ಕ err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    ಯದಿ (err != AVERROR(ENOSYS))
        ಪ್ರತ್ಯಾಗಮ err;
#endif
#ಯದಿ VA_CHECK_VERSION(0, 36, 0)
    ಪ್ರತ್ಯಾಗಮ vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ವಿಕಲ್ಪ (src->format) {
#ಯದಿ CONFIG_LIBDRM
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಪ್ರತ್ಯಾಗಮ vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ವಿಕಲ್ಪ (dst->format) {
#ಯದಿ CONFIG_LIBDRM
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಪ್ರತ್ಯಾಗಮ vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    ಯದಿ (hwctx->display)
        vaTerminate(hwctx->display);

#ಯದಿ HAVE_VAAPI_X11
    ಯದಿ (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#ಯದಿ HAVE_VAAPI_DRM
    ಯದಿ (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#ಯದಿ CONFIG_VAAPI_1
ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_log_error(ಶೂನ್ಯ *context, ಧ್ರುವ ವರ್ಣ *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_log_info(ಶೂನ್ಯ *context, ಧ್ರುವ ವರ್ಣ *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ major, minor;
    VAStatus vas;

#ಯದಿ CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    ಯದಿ (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                               AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ರಿಕ್ತ;
    ಧ್ರುವ AVDictionaryEntry *ent;
    ಪೂರ್ಣಾಙ್ಕ try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(ಪರಿಮಾಣ(*priv));
    ಯದಿ (!priv)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->ಮುಕ್ತ        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ರಿಕ್ತ, 0);
    ಯದಿ (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        ಯದಿ (!strcmp(ent->ಮೌಲ್ಯ, "drm")) {
            try_drm = 1;
        } ಅನ್ಯಥಾ ಯದಿ (!strcmp(ent->ಮೌಲ್ಯ, "x11")) {
            try_x11 = 1;
        } ಅನ್ಯಥಾ ಯದಿ (!strcmp(ent->ಮೌಲ್ಯ, "win32")) {
            try_win32 = 1;
        } ಅನ್ಯಥಾ {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->ಮೌಲ್ಯ);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    } ಅನ್ಯಥಾ {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#ಯದಿ HAVE_VAAPI_DRM
    ಯಾವತ್ (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        ಪೂರ್ಣಾಙ್ಕ loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        ಯದಿ (device) {
            priv->drm_fd = open(device, O_RDWR);
            ಯದಿ (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                ಭಙ್ಗ;
            }
        } ಅನ್ಯಥಾ {
            ವರ್ಣ path[64];
            ಪೂರ್ಣಾಙ್ಕ n, max_devices = 8;
#ಯದಿ CONFIG_LIBDRM
            drmVersion *info;
            ಧ್ರುವ AVDictionaryEntry *kernel_driver;
            ಧ್ರುವ AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ರಿಕ್ತ, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ರಿಕ್ತ, 0);
#endif
            ಪ್ರತಿ (n = 0; n < max_devices; n++) {
                snprintf(path, ಪರಿಮಾಣ(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                ಯದಿ (priv->drm_fd < 0) {
                    ಯದಿ (errno == ENOENT) {
                        ಯದಿ (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            ಅನುವರ್ತ;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } ಅನ್ಯಥಾ
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    ಭಙ್ಗ;
                }
#ಯದಿ CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                ಯದಿ (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ಅನುವರ್ತ;
                }
                ಯದಿ (kernel_driver) {
                    ಯದಿ (strcmp(kernel_driver->ಮೌಲ್ಯ, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        ಅನುವರ್ತ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    ಭಙ್ಗ;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } ಅನ್ಯಥಾ ಯದಿ (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ಅನುವರ್ತ;
                } ಅನ್ಯಥಾ ಯದಿ (vendor_id) {
                    drmDevicePtr device;
                    ವರ್ಣ drm_vendor[8];
                    ಯದಿ (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ಅನುವರ್ತ;
                    }

                    snprintf(drm_vendor, ಪರಿಮಾಣ(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    ಯದಿ (strcmp(vendor_id->ಮೌಲ್ಯ, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->ಮೌಲ್ಯ);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ಅನುವರ್ತ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->ಮೌಲ್ಯ);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    ಭಙ್ಗ;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                ಭಙ್ಗ;
            }
            ಯದಿ (n >= max_devices)
                ಭಙ್ಗ;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        ಯದಿ (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
        ಭಙ್ಗ;
    }
#endif

#ಯದಿ HAVE_VAAPI_X11
    ಯದಿ (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        ಯದಿ (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } ಅನ್ಯಥಾ {
            display = vaGetDisplay(priv->x11_display);
            ಯದಿ (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#ಯದಿ HAVE_VAAPI_WIN32
    ಯದಿ (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        ಯದಿ (!device) {
            display = vaGetDisplayWin32(ರಿಕ್ತ);
        } ಅನ್ಯಥಾ {
            IDXGIFactory2 *pDXGIFactory = ರಿಕ್ತ;
            IDXGIAdapter *pAdapter = ರಿಕ್ತ;
#ಯದಿ !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            ಯದಿ (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            ಯದಿ (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
            }
#ಅನ್ಯಥಾ
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            ಯದಿ (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (ಶೂನ್ಯ **)&pDXGIFactory))) {
                ಪೂರ್ಣಾಙ್ಕ adapter = atoi(device);
                ಯದಿ (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    ಯದಿ (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.ಕೆಳಗಿನ_Part,
                              desc.AdapterLuid.ಮೇಲಿನ_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#ಯದಿ !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        ಯದಿ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    ಯದಿ (!display) {
        ಯದಿ (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        ಅನ್ಯಥಾ
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ರಿಕ್ತ, 0);
    ಯದಿ (ent) {
#ಯದಿ VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->ಮೌಲ್ಯ);
        ಯದಿ (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->ಮೌಲ್ಯ, vas, vaErrorStr(vas));
            vaTerminate(display);
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
#ಅನ್ಯಥಾ
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    ಪ್ರತ್ಯಾಗಮ vaapi_device_connect(ctx, display);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
#ಯದಿ HAVE_VAAPI_DRM
    ಯದಿ (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        ಪೂರ್ಣಾಙ್ಕ fd;

        ಯದಿ (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }

#ಯದಿ CONFIG_LIBDRM
        {
            ಪೂರ್ಣಾಙ್ಕ ಗಂಟು_type = drm_Get_ಗಂಟು_Type_From_Fd(src_hwctx->fd);
            ವರ್ಣ *render_ಗಂಟು;
            ಯದಿ (ಗಂಟು_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            }
            ಯದಿ (ಗಂಟು_type == DRM_ಗಂಟು_RENDER) {
                fd = src_hwctx->fd;
            } ಅನ್ಯಥಾ {
                render_ಗಂಟು = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                ಯದಿ (!render_ಗಂಟು) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } ಅನ್ಯಥಾ {
                    fd = open(render_ಗಂಟು, O_RDWR);
                    ಯದಿ (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } ಅನ್ಯಥಾ {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_ಗಂಟು);
                    }
                    ಮುಕ್ತ(render_ಗಂಟು);
                }
            }
        }
#ಅನ್ಯಥಾ
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(ಪರಿಮಾಣ(*priv));
        ಯದಿ (!priv) {
            ಯದಿ (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }

        ಯದಿ (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } ಅನ್ಯಥಾ {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->ಮುಕ್ತ        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        ಯದಿ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
        }

        ಪ್ರತ್ಯಾಗಮ vaapi_device_connect(ctx, display);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಧ್ರುವ HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = ಪರಿಮಾಣ(VAAPIDeviceContext),
    .device_hwconfig_size   = ಪರಿಮಾಣ(AVVAAPIHWConfig),
    .frames_hwctx_size      = ಪರಿಮಾಣ(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .frames_get_constraints = &vaapi_frames_get_constraints,
    .frames_init            = &vaapi_frames_init,
    .frames_uninit          = &vaapi_frames_uninit,
    .frames_get_buffer      = &vaapi_get_buffer,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_data_to       = &vaapi_transfer_data_to,
    .transfer_data_from     = &vaapi_transfer_data_from,
    .map_to                 = &vaapi_map_to,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
