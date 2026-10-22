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

#ಆದರೆ HAVE_VAAPI_WIN32
#   include <windows.h>
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ಶೂನ್ಯ **ppFactory);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_VAAPI_X11
#   include <va/va_x11.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಆದರೆ HAVE_UNISTD_H
#   include <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ


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


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIDevicePriv {
#ಆದರೆ HAVE_VAAPI_X11
    Display *x11_display;
#ಆದರೆ_ಅಂತ್ಯ

    ಪೂರ್ಣಾಂಕ drm_fd;
} VAAPIDevicePriv;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPISurfaceFormat {
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc;
} VAAPISurfaceFormat;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    ಪೂರ್ಣಾಂಕ              nb_formats;
} VAAPIDeviceContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *ಗುಣಲಕ್ಷಣಗಳು;
    ಪೂರ್ಣಾಂಕ           nb_ಗುಣಲಕ್ಷಣಗಳು;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ rt_format;
    // Whether vaDeriveImage works.
    ಪೂರ್ಣಾಂಕ derive_ಕೆಲಸಮಾಡುತ್ತದೆ;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    ಪೂರ್ಣಾಂಕ ಅವಿಭಾಜ್ಯ_2_import_unsupported;
} VAAPIFramesContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    ಪೂರ್ಣಾಂಕ flags;
} VAAPIMapping;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIFormat {
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ rt_format;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    ಪೂರ್ಣಾಂಕ chroma_planes_swapped;
} VAAPIFormatDescriptor;

#ವ್ಯಾಖ್ಯಾನಿಸು MAP(va, rt, av, ಅದಲುಬದಲು_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        ಅದಲುಬದಲು_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(Y800, YUV400,  GRAY8,   0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#ಆದರೆ_ಅಂತ್ಯ
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#ಆದರೆ_ಅಂತ್ಯ
};
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAP

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        ಆದರೆ (vaapi_format_map[i].fourcc == fourcc)
            ಹಿಂತಿರುಗಿ &vaapi_format_map[i];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(ಎಣಿಕೆ AVPixelFormat pix_fmt, ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *prev)
{
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *ಕೊನೆ = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    ಆದರೆ (!prev)
        prev = vaapi_format_map;
    ಇಲ್ಲದಿದ್ದರೆ
        prev++;

    ಗಾಗಿ (; prev < ಕೊನೆ; prev++)
        ಆದರೆ (prev->pix_fmt == pix_fmt)
            ಹಿಂತಿರುಗಿ prev;
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಎಣಿಕೆ AVPixelFormat vaapi_pix_fmt_from_fourcc(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc)
{
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    ಆದರೆ (desc)
        ಹಿಂತಿರುಗಿ desc->pix_fmt;
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                  ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *desc = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ i;

    ಆಗ ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        ಗಾಗಿ (i = 0; i < ctx->nb_formats; i++) {
            ಆದರೆ (ctx->formats[i].fourcc == desc->fourcc) {
                ಆದರೆ (_desc)
                    *_desc = desc;
                ಆದರೆ (image_format)
                    *image_format = &ctx->formats[i].image_format;
                ಹಿಂತಿರುಗಿ 0;
            }
        }
    }

    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    ಆದರೆ (!image_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಹಿಂತಿರುಗಿ vaapi_get_img_desc_and_format(hwdev, pix_fmt, ಖಾಲಿ, image_format);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *hwdev,
                                        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ಸ್ಥಿರಾಂಕ AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ಖಾಲಿ;
    VAStatus vas;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc;
    ಪೂರ್ಣಾಂಕ err, i, j, attr_ಎಣಿಕೆ, pix_fmt_ಎಣಿಕೆ;

    ಆದರೆ (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ಗುಣಲಕ್ಷಣಗಳು)) {
        attr_ಎಣಿಕೆ = 0;
        vas = va_Query_Surface_ಗುಣಲಕ್ಷಣಗಳು(hwctx->display, config->config_id,
                                       0, &attr_ಎಣಿಕೆ);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ಹೋಗು fail;
        }

        attr_list = av_malloc(attr_ಎಣಿಕೆ * ಗಾತ್ರ(*attr_list));
        ಆದರೆ (!attr_list) {
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }

        vas = va_Query_Surface_ಗುಣಲಕ್ಷಣಗಳು(hwctx->display, config->config_id,
                                       attr_list, &attr_ಎಣಿಕೆ);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ಹೋಗು fail;
        }

        pix_fmt_ಎಣಿಕೆ = 0;
        ಗಾಗಿ (i = 0; i < attr_ಎಣಿಕೆ; i++) {
            ಆಯ್ಕೆ (attr_list[i].type) {
            ಸ್ಥಿತಿ VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                ಆದರೆ (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_ಎಣಿಕೆ;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    // Something unsupported - ignore.
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ VASurface_Attrib_Min_ಅಗಲ:
                constraints->min_ಅಗಲ  = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ VASurface_Attrib_Min_ಎತ್ತರ:
                constraints->min_ಎತ್ತರ = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ VASurface_Attrib_Max_ಅಗಲ:
                constraints->max_ಅಗಲ  = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ VASurface_Attrib_Max_ಎತ್ತರ:
                constraints->max_ಎತ್ತರ = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (pix_fmt_ಎಣಿಕೆ == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ಖಾಲಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_ಎಣಿಕೆ + 1,
                                                            ಗಾತ್ರ(pix_fmt));
            ಆದರೆ (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }

            ಗಾಗಿ (i = j = 0; i < attr_ಎಣಿಕೆ; i++) {
                ಪೂರ್ಣಾಂಕ k;

                ಆದರೆ (attr_list[i].type != VASurfaceAttribPixelFormat)
                    ಮುಂದುವರಿ;
                fourcc = attr_list[i].ಮೌಲ್ಯ.ಮೌಲ್ಯ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                ಆದರೆ (pix_fmt == AV_PIX_FMT_NONE)
                    ಮುಂದುವರಿ;

                ಗಾಗಿ (k = 0; k < j; k++) {
                    ಆದರೆ (constraints->valid_sw_formats[k] == pix_fmt)
                        ನಿಲ್ಲಿಸು;
                }

                ಆದರೆ (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        ಗಾತ್ರ(pix_fmt));
        ಆದರೆ (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
        ಗಾಗಿ (i = j = 0; i < ctx->nb_formats; i++) {
            ಪೂರ್ಣಾಂಕ k;

            ಗಾಗಿ (k = 0; k < j; k++) {
                ಆದರೆ (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(pix_fmt));
    ಆದರೆ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *friendly_name;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಹೊಂದಿಕೆ_string;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ quirks;
} vaapi_driver_quirks_ಕೋಷ್ಟಕ[] = {
#ಆದರೆ !VA_CHECK_ಆವೃತ್ತಿ(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#ಆದರೆ_ಅಂತ್ಯ
    {
        "Intel iHD",
        "ubit",
        AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE,
    },
    {
        "VDPAU wrapper",
        "Splitted-Desktop Systems VDPAU backend for VA-API",
        AV_VAAPI_DRIVER_QUIRK_SURFACE_ಗುಣಲಕ್ಷಣಗಳು,
    },
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ಖಾಲಿ;
    VAStatus vas;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *vendor_string;
    ಪೂರ್ಣಾಂಕ err, i, image_ಎಣಿಕೆ;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ fourcc;

    image_ಎಣಿಕೆ = va_Max_ಅಂಕೆ_Image_Formats(hwctx->display);
    ಆದರೆ (image_ಎಣಿಕೆ <= 0) {
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }
    image_list = av_malloc(image_ಎಣಿಕೆ * ಗಾತ್ರ(*image_list));
    ಆದರೆ (!image_list) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_ಎಣಿಕೆ);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }

    ctx->formats  = av_malloc(image_ಎಣಿಕೆ * ಗಾತ್ರ(*ctx->formats));
    ಆದರೆ (!ctx->formats) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    ctx->nb_formats = 0;
    ಗಾಗಿ (i = 0; i < image_ಎಣಿಕೆ; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        ಆದರೆ (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    ಆದರೆ (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    ಆದರೆ (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_ಗಣ) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        ಆದರೆ (vendor_string) {
            ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_ಕೋಷ್ಟಕ); i++) {
                ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(vendor_string,
                           vaapi_driver_quirks_ಕೋಷ್ಟಕ[i].ಹೊಂದಿಕೆ_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_ಕೋಷ್ಟಕ[i].friendly_name,
                           vaapi_driver_quirks_ಕೋಷ್ಟಕ[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_ಕೋಷ್ಟಕ[i].quirks;
                    ನಿಲ್ಲಿಸು;
                }
            }
            ಆದರೆ (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_ಕೋಷ್ಟಕ))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    ಹಿಂತಿರುಗಿ 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_ಬಫರ್_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)ದತ್ತಾಂಶ;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ಸ್ಥಿರ AVBufferRef *vaapi_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    ಆದರೆ (hwfc->initial_pool_ಗಾತ್ರ > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->ಅಗಲ, hwfc->ಎತ್ತರ,
                           &surface_id, 1,
                           ctx->ಗುಣಲಕ್ಷಣಗಳು, ctx->nb_ಗುಣಲಕ್ಷಣಗಳು);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_ಬಫರ್_create((uint8_t*)(uintptr_t)surface_id,
                           ಗಾತ್ರ(surface_id), &vaapi_ಬಫರ್_free,
                           hwfc, AV_ಬಫರ್_FLAG_READONLY);
    ಆದರೆ (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (hwfc->initial_pool_ಗಾತ್ರ > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_ಗಾತ್ರ);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    ಹಿಂತಿರುಗಿ ref;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *desc = ಖಾಲಿ;
    VAImageFormat *expected_format = ಖಾಲಿ;
    AVBufferRef *test_surface = ಖಾಲಿ;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    ಪೂರ್ಣಾಂಕ err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    ಆದರೆ (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        ಆದರೆ (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ಖಾಲಿ)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಆದರೆ (!hwfc->pool) {
        ಆದರೆ (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ಗುಣಲಕ್ಷಣಗಳು)) {
            ಪೂರ್ಣಾಂಕ need_ಸ್ಮರಣೆ_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            ಪೂರ್ಣಾಂಕ need_pixel_format = 1;
            ಗಾಗಿ (i = 0; i < avfc->nb_ಗುಣಲಕ್ಷಣಗಳು; i++) {
                ಆದರೆ (avfc->ಗುಣಲಕ್ಷಣಗಳು[i].type == VASurface_Attrib_ಸ್ಮರಣೆ_Type)
                    need_ಸ್ಮರಣೆ_type  = 0;
                ಆದರೆ (avfc->ಗುಣಲಕ್ಷಣಗಳು[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_ಗುಣಲಕ್ಷಣಗಳು =
                avfc->nb_ಗುಣಲಕ್ಷಣಗಳು + need_ಸ್ಮರಣೆ_type + need_pixel_format;

            ctx->ಗುಣಲಕ್ಷಣಗಳು = av_malloc(ctx->nb_ಗುಣಲಕ್ಷಣಗಳು *
                                        ಗಾತ್ರ(*ctx->ಗುಣಲಕ್ಷಣಗಳು));
            ಆದರೆ (!ctx->ಗುಣಲಕ್ಷಣಗಳು) {
                err = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }

            ಗಾಗಿ (i = 0; i < avfc->nb_ಗುಣಲಕ್ಷಣಗಳು; i++)
                ctx->ಗುಣಲಕ್ಷಣಗಳು[i] = avfc->ಗುಣಲಕ್ಷಣಗಳು[i];
            ಆದರೆ (need_ಸ್ಮರಣೆ_type) {
                ctx->ಗುಣಲಕ್ಷಣಗಳು[i++] = (VASurfaceAttrib) {
                    .type          = VASurface_Attrib_ಸ್ಮರಣೆ_Type,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                    .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            ಆದರೆ (need_pixel_format) {
                ctx->ಗುಣಲಕ್ಷಣಗಳು[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                    .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_ಗುಣಲಕ್ಷಣಗಳು);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ctx->ಗುಣಲಕ್ಷಣಗಳು = ಖಾಲಿ;
            ctx->nb_ಗುಣಲಕ್ಷಣಗಳು = 0;
        }

        ctx->rt_format = desc->rt_format;

        ಆದರೆ (hwfc->initial_pool_ಗಾತ್ರ > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_ಗಾತ್ರ *
                                          ಗಾತ್ರ(*avfc->surface_ids));
            ಆದರೆ (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ಖಾಲಿ;
        }

        ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ =
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    ಆದರೆ (hwfc->pool) {
        test_surface = av_ಬಫರ್_pool_get(hwfc->pool);
        ಆದರೆ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        test_surface = av_ಬಫರ್_pool_get(ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ);
        ಆದರೆ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->ದತ್ತಾಂಶ;

    ctx->derive_ಕೆಲಸಮಾಡುತ್ತದೆ = 0;
    ಆದರೆ (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        ಆದರೆ (vas == VA_ಸ್ಥಿತಿ_SUCCESS) {
            ಆದರೆ (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_ಕೆಲಸಮಾಡುತ್ತದೆ = 1;
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_ಬಫರ್_unref(&test_surface);
    ಹಿಂತಿರುಗಿ 0;

fail:
    av_ಬಫರ್_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->ಗುಣಲಕ್ಷಣಗಳು);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->ಗುಣಲಕ್ಷಣಗಳು);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_get_ಬಫರ್(AVHWFramesContext *hwfc, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(hwfc->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_VAAPI;
    ಚೌಕಟ್ಟು->ಅಗಲ   = hwfc->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = hwfc->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                      ಎಣಿಕೆ AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    ಎಣಿಕೆ AVPixelFormat *pix_fmts;
    ಪೂರ್ಣಾಂಕ i, k, sw_format_ಲಭ್ಯ;

    sw_format_ಲಭ್ಯ = 0;
    ಗಾಗಿ (i = 0; i < ctx->nb_formats; i++) {
        ಆದರೆ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_ಲಭ್ಯ = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * ಗಾತ್ರ(*pix_fmts));
    ಆದರೆ (!pix_fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (sw_format_ಲಭ್ಯ) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        k = 0;
    }
    ಗಾಗಿ (i = 0; i < ctx->nb_formats; i++) {
        ಆದರೆ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            ಮುಂದುವರಿ;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ಮೂಲ->ದತ್ತಾಂಶ[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_ಬಫರ್(hwctx->display, map->image.buf);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    ಆದರೆ ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_ನೇರ)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ,
                         0, 0, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                           AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    ಶೂನ್ಯ *ವಿಳಾಸ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ err, i;
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 21, 0)
    uint32_t vaflags = 0;
#ಆದರೆ_ಅಂತ್ಯ

    surface_id = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    ಆದರೆ (!ctx->derive_ಕೆಲಸಮಾಡುತ್ತದೆ && (flags & AV_HWFRAME_MAP_ನೇರ)) {
        // Requested direct mapping but it is not possible.
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಆದರೆ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಆದರೆ (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_ನೇರ)) {
        // Requested direct mapping but the formats do not match.
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    ಆದರೆ (err < 0) {
        // Requested format is not a valid output format.
        ಹಿಂತಿರುಗಿ err;
    }

    map = av_malloc(ಗಾತ್ರ(*map));
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    ಆದರೆ (ctx->derive_ಕೆಲಸಮಾಡುತ್ತದೆ && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_ನೇರ) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }
        ಆದರೆ (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }
        map->flags |= AV_HWFRAME_MAP_ನೇರ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, &map->image);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }
        ಆದರೆ (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, map->image.image_id);
            ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }
        }
    }

#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 21, 0)
    ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &ವಿಳಾಸ, vaflags);
#ಇಲ್ಲದಿದ್ದರೆ
    vas = va_Map_ಬಫರ್(hwctx->display, map->image.buf, &ವಿಳಾಸ);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                dst, src, &vaapi_unmap_ಚೌಕಟ್ಟು, map);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಗಾಗಿ (i = 0; i < map->image.ಅಂಕೆ_planes; i++) {
        dst->ದತ್ತಾಂಶ[i] = (uint8_t*)ವಿಳಾಸ + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    ಆದರೆ (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->ದತ್ತಾಂಶ[1], dst->ದತ್ತಾಂಶ[2]);
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (map) {
        ಆದರೆ (ವಿಳಾಸ)
            va_Unmap_ಬಫರ್(hwctx->display, map->image.buf);
        ಆದರೆ (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->ಅಗಲ > hwfc->ಅಗಲ || dst->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_ಚೌಕಟ್ಟು(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = dst->ಅಗಲ;
    map->ಎತ್ತರ = dst->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(dst, map);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (src->ಅಗಲ > hwfc->ಅಗಲ || src->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_ಚೌಕಟ್ಟು(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = src->ಅಗಲ;
    map->ಎತ್ತರ = src->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(map, src);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಗಮ್ಯ_ಸ್ಮರಣೆ(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;

    err = vaapi_map_ಚೌಕಟ್ಟು(hwfc, dst, src, flags);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    err = av_ಚೌಕಟ್ಟು_copy_props(dst, src);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ CONFIG_LIBDRM

#ವ್ಯಾಖ್ಯಾನಿಸು DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    uint32_t va_fourcc;
    ಪೂರ್ಣಾಂಕ   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#ಆದರೆ_ಅಂತ್ಯ
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#ಆದರೆ defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#ಆದರೆ_ಅಂತ್ಯ
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#ಆದರೆ_ಅಂತ್ಯ
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#ಆದರೆ defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#ಆದರೆ_ಅಂತ್ಯ
};
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು DRM_MAP

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    ಪೂರ್ಣಾಂಕ use_prime2;
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ k;
#ಆದರೆ_ಅಂತ್ಯ
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc;
    ಸ್ಥಿರಾಂಕ VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_ಸ್ಥಿತಿ_SUCCESS;
    uint32_t va_fourcc;
    ಪೂರ್ಣಾಂಕ err, i, j;

#ಆದರೆ !VA_CHECK_ಆವೃತ್ತಿ(1, 1, 0)
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬಫರ್_handle;
    VASurfaceAttribExternalBuffers ಬಫರ್_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurface_Attrib_ಸ್ಮರಣೆ_Type,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
            .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ,
        },
        {
            .type  = VASurface_Attrib_External_ಬಫರ್_Descriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_ಸೂಚಕ,
            .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &ಬಫರ್_desc,
        }
    };
#ಆದರೆ_ಅಂತ್ಯ

    desc = (AVDRMFrameDescriptor*)src->ದತ್ತಾಂಶ[0];

    ಆದರೆ (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    va_fourcc = 0;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ಆದರೆ (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            ಮುಂದುವರಿ;
        ಗಾಗಿ (j = 0; j < desc->nb_layers; j++) {
            ಆದರೆ (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (j != desc->nb_layers)
            ಮುಂದುವರಿ;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 1, 0)
    use_prime2 = !src_vafc->ಅವಿಭಾಜ್ಯ_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    ಆದರೆ (use_prime2) {
        VADRMPRIMESurfaceDescriptor ಅವಿಭಾಜ್ಯ_desc;
        VASurfaceAttrib ಅವಿಭಾಜ್ಯ_attrs[2] = {
            {
                .type  = VASurface_Attrib_ಸ್ಮರಣೆ_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ_2,
            },
            {
                .type  = VASurface_Attrib_External_ಬಫರ್_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_ಸೂಚಕ,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &ಅವಿಭಾಜ್ಯ_desc,
            }
        };
        ಅವಿಭಾಜ್ಯ_desc.fourcc = va_fourcc;
        ಅವಿಭಾಜ್ಯ_desc.ಅಗಲ = src_fc->ಅಗಲ;
        ಅವಿಭಾಜ್ಯ_desc.ಎತ್ತರ = src_fc->ಎತ್ತರ;
        ಅವಿಭಾಜ್ಯ_desc.ಅಂಕೆ_objects = desc->nb_objects;
        ಗಾಗಿ (i = 0; i < desc->nb_objects; ++i) {
            ಅವಿಭಾಜ್ಯ_desc.objects[i].fd = desc->objects[i].fd;
            ಅವಿಭಾಜ್ಯ_desc.objects[i].ಗಾತ್ರ_2 = desc->objects[i].ಗಾತ್ರ_2;
            ಅವಿಭಾಜ್ಯ_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        ಅವಿಭಾಜ್ಯ_desc.ಅಂಕೆ_layers = desc->nb_layers;
        ಗಾಗಿ (i = 0; i < desc->nb_layers; ++i) {
            ಅವಿಭಾಜ್ಯ_desc.layers[i].drm_format = desc->layers[i].format;
            ಅವಿಭಾಜ್ಯ_desc.layers[i].ಅಂಕೆ_planes = desc->layers[i].nb_planes;
            ಗಾಗಿ (j = 0; j < desc->layers[i].nb_planes; ++j) {
                ಅವಿಭಾಜ್ಯ_desc.layers[i].object_ಸೂಚ್ಯಂಕ[j] =
                        desc->layers[i].planes[j].object_ಸೂಚ್ಯಂಕ;
                ಅವಿಭಾಜ್ಯ_desc.layers[i].ಸ್ಥಾನಾಂತರ[j] = desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ;
                ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            ಆದರೆ (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[1],
                    ಅವಿಭಾಜ್ಯ_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, ಅವಿಭಾಜ್ಯ_desc.layers[i].ಸ್ಥಾನಾಂತರ[1],
                    ಅವಿಭಾಜ್ಯ_desc.layers[i].ಸ್ಥಾನಾಂತರ[2]);
            }
        }

        /*
         * We can query for PRIME_2 support with vaQuerySurfaceAttributes, but that
         * that needs the config_id which we don't have here . Both Intel and
         * Gallium seem to do the correct error checks, so lets just try the
         * PRIME_2 import first.
         */
        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->ಅಗಲ, src->ಎತ್ತರ, &surface_id, 1,
                               ಅವಿಭಾಜ್ಯ_attrs, FF_ARRAY_ELEMS(ಅವಿಭಾಜ್ಯ_attrs));
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS)
            src_vafc->ಅವಿಭಾಜ್ಯ_2_import_unsupported = 1;
    }

    ಆದರೆ (!use_prime2 || vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        ಪೂರ್ಣಾಂಕ k;
        uintptr_t ಬಫರ್_handle;
        VASurfaceAttribExternalBuffers ಬಫರ್_desc;
        VASurfaceAttrib ಬಫರ್_attrs[2] = {
            {
                .type  = VASurface_Attrib_ಸ್ಮರಣೆ_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_Integer,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ,
            },
            {
                .type  = VASurface_Attrib_External_ಬಫರ್_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ಮೌಲ್ಯ.type    = VAGeneric_ಮೌಲ್ಯ_Type_ಸೂಚಕ,
                .ಮೌಲ್ಯ.ಮೌಲ್ಯ.p = &ಬಫರ್_desc,
            }
        };

        ಬಫರ್_handle = desc->objects[0].fd;
        ಬಫರ್_desc.pixel_format = va_fourcc;
        ಬಫರ್_desc.ಅಗಲ        = src_fc->ಅಗಲ;
        ಬಫರ್_desc.ಎತ್ತರ       = src_fc->ಎತ್ತರ;
        ಬಫರ್_desc.ದತ್ತಾಂಶ_ಗಾತ್ರ    = desc->objects[0].ಗಾತ್ರ_2;
        ಬಫರ್_desc.buffers      = &ಬಫರ್_handle;
        ಬಫರ್_desc.ಅಂಕೆ_buffers  = 1;
        ಬಫರ್_desc.flags        = 0;

        k = 0;
        ಗಾಗಿ (i = 0; i < desc->nb_layers; i++) {
            ಗಾಗಿ (j = 0; j < desc->layers[i].nb_planes; j++) {
                ಬಫರ್_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                ಬಫರ್_desc.offsets[k] = desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ;
                ++k;
            }
        }
        ಬಫರ್_desc.ಅಂಕೆ_planes = k;

        ಆದರೆ (format_desc->chroma_planes_swapped &&
            ಬಫರ್_desc.ಅಂಕೆ_planes == 3) {
            FFSWAP(uint32_t, ಬಫರ್_desc.pitches[1], ಬಫರ್_desc.pitches[2]);
            FFSWAP(uint32_t, ಬಫರ್_desc.offsets[1], ಬಫರ್_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->ಅಗಲ, src->ಎತ್ತರ,
                               &surface_id, 1,
                               ಬಫರ್_attrs, FF_ARRAY_ELEMS(ಬಫರ್_attrs));
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಬಫರ್_handle = desc->objects[0].fd;
    ಬಫರ್_desc.pixel_format = va_fourcc;
    ಬಫರ್_desc.ಅಗಲ        = src_fc->ಅಗಲ;
    ಬಫರ್_desc.ಎತ್ತರ       = src_fc->ಎತ್ತರ;
    ಬಫರ್_desc.ದತ್ತಾಂಶ_ಗಾತ್ರ    = desc->objects[0].ಗಾತ್ರ_2;
    ಬಫರ್_desc.buffers      = &ಬಫರ್_handle;
    ಬಫರ್_desc.ಅಂಕೆ_buffers  = 1;
    ಬಫರ್_desc.flags        = 0;

    k = 0;
    ಗಾಗಿ (i = 0; i < desc->nb_layers; i++) {
        ಗಾಗಿ (j = 0; j < desc->layers[i].nb_planes; j++) {
            ಬಫರ್_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            ಬಫರ್_desc.offsets[k] = desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ;
            ++k;
        }
    }
    ಬಫರ್_desc.ಅಂಕೆ_planes = k;

    ಆದರೆ (format_desc->chroma_planes_swapped &&
        ಬಫರ್_desc.ಅಂಕೆ_planes == 3) {
        FFSWAP(uint32_t, ಬಫರ್_desc.pitches[1], ಬಫರ್_desc.pitches[2]);
        FFSWAP(uint32_t, ಬಫರ್_desc.offsets[1], ಬಫರ್_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->ಅಗಲ, src->ಎತ್ತರ,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (ಶೂನ್ಯ*)(uintptr_t)surface_id);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;
    dst->ದತ್ತಾಂಶ[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 1, 0)
ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_ಗಮ್ಯ_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಗಮ್ಯ_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ಖಾಲಿ;
    uint32_t export_flags;
    ಪೂರ್ಣಾಂಕ err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    ಆದರೆ (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            ಹಿಂತಿರುಗಿ AVERROR(EIO);
        }
    }

    ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ_2,
                                export_flags, &va_desc);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        ಆದರೆ (vas == VA_ಸ್ಥಿತಿ_ERROR_UNIMPLEMENTED)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

    drm_desc = av_mallocz(ಗಾತ್ರ(*drm_desc));
    ಆದರೆ (!drm_desc) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.ಅಂಕೆ_objects;
    ಗಾಗಿ (i = 0; i < va_desc.ಅಂಕೆ_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].ಗಾತ್ರ_2 = va_desc.objects[i].ಗಾತ್ರ_2;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.ಅಂಕೆ_layers;
    ಗಾಗಿ (i = 0; i < va_desc.ಅಂಕೆ_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].ಅಂಕೆ_planes;
        ಗಾಗಿ (j = 0; j < va_desc.layers[i].ಅಂಕೆ_planes; j++) {
            drm_desc->layers[i].planes[j].object_ಸೂಚ್ಯಂಕ =
                va_desc.layers[i].object_ಸೂಚ್ಯಂಕ[j];
            drm_desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ =
                va_desc.layers[i].ಸ್ಥಾನಾಂತರ[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &vaapi_unmap_ಗಮ್ಯ_drm_esh, drm_desc);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;
    dst->ದತ್ತಾಂಶ[0] = (uint8_t*)drm_desc;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (i = 0; i < va_desc.ಅಂಕೆ_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(0, 36, 0)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VAAPIDRMImage_ಬಫರ್_Mapping {
    VAImage      image;
    VABufferInfo ಬಫರ್_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_ಬಫರ್_Mapping;

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_unmap_ಗಮ್ಯ_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_ಬಫರ್_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ಮೂಲ->ದತ್ತಾಂಶ[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_ಬಫರ್_Handle(hwctx->display, mapping->image.buf);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಗಮ್ಯ_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_ಬಫರ್_Mapping *mapping = ಖಾಲಿ;
    VASurfaceID surface_id;
    VAStatus vas;
    ಪೂರ್ಣಾಂಕ err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(ಗಾತ್ರ(*mapping));
    ಆದರೆ (!mapping)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ಆದರೆ (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        ಹೋಗು fail_derived;
    }

    mapping->ಬಫರ್_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ಅವಿಭಾಜ್ಯ;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    ಆದರೆ (mapping->drm_desc.nb_layers > 1) {
        ಆದರೆ (mapping->drm_desc.nb_layers != mapping->image.ಅಂಕೆ_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.ಅಂಕೆ_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            ಹೋಗು fail_derived;
        }

        ಗಾಗಿ(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_ಸೂಚ್ಯಂಕ = 0,
                    .ಸ್ಥಾನಾಂತರ       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.ಅಂಕೆ_planes;
        ಗಾಗಿ (p = 0; p < mapping->image.ಅಂಕೆ_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_ಸೂಚ್ಯಂಕ = 0,
                .ಸ್ಥಾನಾಂತರ       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_ಬಫರ್_Handle(hwctx->display, mapping->image.buf,
                                &mapping->ಬಫರ್_info);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ಹೋಗು fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->ಬಫರ್_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->ಬಫರ್_info.handle,
        .ಗಾತ್ರ_2 = mapping->image.ದತ್ತಾಂಶ_ಗಾತ್ರ,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                dst, src, &vaapi_unmap_ಗಮ್ಯ_drm_abh,
                                mapping);
    ಆದರೆ (err < 0)
        ಹೋಗು fail_mapped;

    dst->ದತ್ತಾಂಶ[0] = (uint8_t*)&mapping->drm_desc;
    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail_mapped:
    va_Release_ಬಫರ್_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಗಮ್ಯ_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 1, 0)
    ಪೂರ್ಣಾಂಕ err;
    err = vaapi_map_ಗಮ್ಯ_drm_esh(hwfc, dst, src, flags);
    ಆದರೆ (err != AVERROR(ENOSYS))
        ಹಿಂತಿರುಗಿ err;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(0, 36, 0)
    ಹಿಂತಿರುಗಿ vaapi_map_ಗಮ್ಯ_drm_abh(hwfc, dst, src, flags);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

#ಆದರೆ_ಅಂತ್ಯ /* CONFIG_LIBDRM */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_ಗಮ್ಯ(AVHWFramesContext *hwfc, AVFrame *dst,
                        ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಆಯ್ಕೆ (src->format) {
#ಆದರೆ CONFIG_LIBDRM
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಹಿಂತಿರುಗಿ vaapi_map_from_drm(hwfc, dst, src, flags);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಆಯ್ಕೆ (dst->format) {
#ಆದರೆ CONFIG_LIBDRM
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಹಿಂತಿರುಗಿ vaapi_map_ಗಮ್ಯ_drm(hwfc, dst, src, flags);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ vaapi_map_ಗಮ್ಯ_ಸ್ಮರಣೆ(hwfc, dst, src, flags);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    ಆದರೆ (hwctx->display)
        vaTerminate(hwctx->display);

#ಆದರೆ HAVE_VAAPI_X11
    ಆದರೆ (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_VAAPI_DRM
    ಆದರೆ (priv->drm_fd >= 0)
        close(priv->drm_fd);
#ಆದರೆ_ಅಂತ್ಯ

    av_freep(&priv);
}

#ಆದರೆ CONFIG_VAAPI_1
ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_log_error(ಶೂನ್ಯ *context, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", ಸಂದೇಶ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ vaapi_device_log_info(ಶೂನ್ಯ *context, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", ಸಂದೇಶ_2);
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ major, minor;
    VAStatus vas;

#ಆದರೆ CONFIG_VAAPI_1
    va_ಗಣ_Error_Callback(display, &vaapi_device_log_error, ctx);
    va_ಗಣ_Info_Callback (display, &vaapi_device_log_info,  ctx);
#ಆದರೆ_ಅಂತ್ಯ

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                               AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *ent;
    ಪೂರ್ಣಾಂಕ try_drm, try_x11, try_win32, try_all av_ಬಳಸದ;

    priv = av_mallocz(ಗಾತ್ರ(*priv));
    ಆದರೆ (!priv)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->ಬಿಡುಗಡೆ        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ಖಾಲಿ, 0);
    ಆದರೆ (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        ಆದರೆ (!strcmp(ent->ಮೌಲ್ಯ, "drm")) {
            try_drm = 1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(ent->ಮೌಲ್ಯ, "x11")) {
            try_x11 = 1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(ent->ಮೌಲ್ಯ, "win32")) {
            try_win32 = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->ಮೌಲ್ಯ);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#ಆದರೆ HAVE_VAAPI_DRM
    ಆಗ (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        ಪೂರ್ಣಾಂಕ loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        ಆದರೆ (device) {
            priv->drm_fd = open(device, O_RDWR);
            ಆದರೆ (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಅಕ್ಷರ ಮಾರ್ಗ[64];
            ಪೂರ್ಣಾಂಕ n, max_devices = 8;
#ಆದರೆ CONFIG_LIBDRM
            drm_ಆವೃತ್ತಿ *info;
            ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *kernel_driver;
            ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ಖಾಲಿ, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ಖಾಲಿ, 0);
#ಆದರೆ_ಅಂತ್ಯ
            ಗಾಗಿ (n = 0; n < max_devices; n++) {
                snprintf(ಮಾರ್ಗ, ಗಾತ್ರ(ಮಾರ್ಗ),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(ಮಾರ್ಗ, O_RDWR);
                ಆದರೆ (priv->drm_fd < 0) {
                    ಆದರೆ (errno == ENOENT) {
                        ಆದರೆ (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", ಮಾರ್ಗ);
                            ಮುಂದುವರಿ;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } ಇಲ್ಲದಿದ್ದರೆ
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    ನಿಲ್ಲಿಸು;
                }
#ಆದರೆ CONFIG_LIBDRM
                info = drm_Get_ಆವೃತ್ತಿ(priv->drm_fd);
                ಆದರೆ (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ಮುಂದುವರಿ;
                }
                ಆದರೆ (kernel_driver) {
                    ಆದರೆ (strcmp(kernel_driver->ಮೌಲ್ಯ, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drm_Free_ಆವೃತ್ತಿ(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        ಮುಂದುವರಿ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drm_Free_ಆವೃತ್ತಿ(info);
                    ನಿಲ್ಲಿಸು;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drm_Free_ಆವೃತ್ತಿ(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ಮುಂದುವರಿ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (vendor_id) {
                    drmDevicePtr device;
                    ಅಕ್ಷರ drm_vendor[8];
                    ಆದರೆ (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_ಆವೃತ್ತಿ(info);
                        ಮುಂದುವರಿ;
                    }

                    snprintf(drm_vendor, ಗಾತ್ರ(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    ಆದರೆ (strcmp(vendor_id->ಮೌಲ್ಯ, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->ಮೌಲ್ಯ);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_ಆವೃತ್ತಿ(info);
                        ಮುಂದುವರಿ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->ಮೌಲ್ಯ);
                    drmFreeDevice(&device);
                    drm_Free_ಆವೃತ್ತಿ(info);
                    ನಿಲ್ಲಿಸು;
                }
                drm_Free_ಆವೃತ್ತಿ(info);
#ಆದರೆ_ಅಂತ್ಯ
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ (n >= max_devices)
                ನಿಲ್ಲಿಸು;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        ಆದರೆ (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_VAAPI_X11
    ಆದರೆ (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        ಆದರೆ (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } ಇಲ್ಲದಿದ್ದರೆ {
            display = vaGetDisplay(priv->x11_display);
            ಆದರೆ (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_VAAPI_WIN32
    ಆದರೆ (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        ಆದರೆ (!device) {
            display = vaGetDisplayWin32(ಖಾಲಿ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            IDXGIFactory2 *pDXGIFactory = ಖಾಲಿ;
            IDXGIAdapter *pAdapter = ಖಾಲಿ;
#ಆದರೆ !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            ಆದರೆ (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            ಆದರೆ (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
            }
#ಇಲ್ಲದಿದ್ದರೆ
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (ಶೂನ್ಯ **)&pDXGIFactory))) {
                ಪೂರ್ಣಾಂಕ adapter = atoi(device);
                ಆದರೆ (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    ಆದರೆ (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
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
#ಆದರೆ !HAVE_UWP
            dlclose(dxgi);
#ಆದರೆ_ಅಂತ್ಯ
        }

        ಆದರೆ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!display) {
        ಆದರೆ (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ಖಾಲಿ, 0);
    ಆದರೆ (ent) {
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(0, 38, 0)
        VAStatus vas;
        vas = va_ಗಣ_Driver_Name(display, ent->ಮೌಲ್ಯ);
        ಆದರೆ (vas != VA_ಸ್ಥಿತಿ_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->ಮೌಲ್ಯ, vas, vaErrorStr(vas));
            vaTerminate(display);
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ vaapi_device_connect(ctx, display);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
#ಆದರೆ HAVE_VAAPI_DRM
    ಆದರೆ (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        ಪೂರ್ಣಾಂಕ fd;

        ಆದರೆ (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

#ಆದರೆ CONFIG_LIBDRM
        {
            ಪೂರ್ಣಾಂಕ ಗಂಟು_type = drm_Get_ಗಂಟು_Type_From_Fd(src_hwctx->fd);
            ಅಕ್ಷರ *render_ಗಂಟು;
            ಆದರೆ (ಗಂಟು_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            }
            ಆದರೆ (ಗಂಟು_type == DRM_ಗಂಟು_RENDER) {
                fd = src_hwctx->fd;
            } ಇಲ್ಲದಿದ್ದರೆ {
                render_ಗಂಟು = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                ಆದರೆ (!render_ಗಂಟು) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    fd = open(render_ಗಂಟು, O_RDWR);
                    ಆದರೆ (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_ಗಂಟು);
                    }
                    ಬಿಡುಗಡೆ(render_ಗಂಟು);
                }
            }
        }
#ಇಲ್ಲದಿದ್ದರೆ
        fd = src_hwctx->fd;
#ಆದರೆ_ಅಂತ್ಯ

        priv = av_mallocz(ಗಾತ್ರ(*priv));
        ಆದರೆ (!priv) {
            ಆದರೆ (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }

        ಆದರೆ (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->ಬಿಡುಗಡೆ        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        ಆದರೆ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            ಹಿಂತಿರುಗಿ AVERROR(EIO);
        }

        ಹಿಂತಿರುಗಿ vaapi_device_connect(ctx, display);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(VAAPIDeviceContext),
    .device_hwconfig_ಗಾತ್ರ   = ಗಾತ್ರ(AVVAAPIHWConfig),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = &vaapi_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init            = &vaapi_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit          = &vaapi_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = &vaapi_get_ಬಫರ್,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = &vaapi_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from     = &vaapi_transfer_ದತ್ತಾಂಶ_from,
    .map_ಗಮ್ಯ                 = &vaapi_map_ಗಮ್ಯ,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
