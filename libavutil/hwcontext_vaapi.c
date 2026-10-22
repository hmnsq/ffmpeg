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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
ପ୍ରକାରବ୍ୟାଖ୍ୟା HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ଶୂନ୍ୟ **ppFactory);
#endif
#ଯଦି HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#ଯଦି HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#ଯଦି CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଯଦି HAVE_UNISTD_H
#   include <unistd.h>
#endif


#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_drm.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_vaapi.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"


ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIDevicePriv {
#ଯଦି HAVE_VAAPI_X11
    Display *x11_display;
#endif

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_fd;
} VAAPIDevicePriv;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPISurfaceFormat {
    ଗଣନା AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc;
} VAAPISurfaceFormat;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              nb_formats;
} VAAPIDeviceContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା rt_format;
    // Whether vaDeriveImage works.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୌଳିକ_2_import_unsupported;
} VAAPIFramesContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags;
} VAAPIMapping;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIFormat {
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା rt_format;
    ଗଣନା AVPixelFormat pix_fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ସ୍ଥିର ଅଚଳ VAAPIFormatDescriptor vaapi_format_map[] = {
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

ସ୍ଥିର ଅଚଳ VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        ଯଦି (vaapi_format_map[i].fourcc == fourcc)
            ଫେରନ୍ତୁ &vaapi_format_map[i];
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଅଚଳ VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(ଗଣନା AVPixelFormat pix_fmt, ଅଚଳ VAAPIFormatDescriptor *prev)
{
    ଅଚଳ VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    ଯଦି (!prev)
        prev = vaapi_format_map;
    ଅନ୍ୟଥା
        prev++;

    ପାଇଁ (; prev < end; prev++)
        ଯଦି (prev->pix_fmt == pix_fmt)
            ଫେରନ୍ତୁ prev;
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଗଣନା AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc)
{
    ଅଚଳ VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    ଯଦି (desc)
        ଫେରନ୍ତୁ desc->pix_fmt;
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ AV_PIX_FMT_NONE;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  ଗଣନା AVPixelFormat pix_fmt,
                                  ଅଚଳ VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ଅଚଳ VAAPIFormatDescriptor *desc = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯେତେବେଳେ ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        ପାଇଁ (i = 0; i < ctx->nb_formats; i++) {
            ଯଦି (ctx->formats[i].fourcc == desc->fourcc) {
                ଯଦି (_desc)
                    *_desc = desc;
                ଯଦି (image_format)
                    *image_format = &ctx->formats[i].image_format;
                ଫେରନ୍ତୁ 0;
            }
        }
    }

    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  ଗଣନା AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    ଯଦି (!image_format)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଫେରନ୍ତୁ vaapi_get_img_desc_and_format(hwdev, pix_fmt, ଖାଲି, image_format);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ଅଚଳ AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ଖାଲି;
    VAStatus vas;
    ଗଣନା AVPixelFormat pix_fmt;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, j, attr_ଗଣନା, pix_fmt_ଗଣନା;

    ଯଦି (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_ଗଣନା = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_ଗଣନା);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ଯାଅ fail;
        }

        attr_list = av_malloc(attr_ଗଣନା * ଆକାର(*attr_list));
        ଯଦି (!attr_list) {
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_ଗଣନା);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            ଯାଅ fail;
        }

        pix_fmt_ଗଣନା = 0;
        ପାଇଁ (i = 0; i < attr_ଗଣନା; i++) {
            ବାଛ (attr_list[i].type) {
            ସ୍ଥିତି VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                ଯଦି (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_ଗଣନା;
                } ଅନ୍ୟଥା {
                    // Something unsupported - ignore.
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (pix_fmt_ଗଣନା == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ଖାଲି;
        } ଅନ୍ୟଥା {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_ଗଣନା + 1,
                                                            ଆକାର(pix_fmt));
            ଯଦି (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                ଯାଅ fail;
            }

            ପାଇଁ (i = j = 0; i < attr_ଗଣନା; i++) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;

                ଯଦି (attr_list[i].type != VASurfaceAttribPixelFormat)
                    ଜାରି;
                fourcc = attr_list[i].ମୂଲ୍ୟ.ମୂଲ୍ୟ.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                ଯଦି (pix_fmt == AV_PIX_FMT_NONE)
                    ଜାରି;

                ପାଇଁ (k = 0; k < j; k++) {
                    ଯଦି (constraints->valid_sw_formats[k] == pix_fmt)
                        ଭାଙ୍ଗ;
                }

                ଯଦି (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } ଅନ୍ୟଥା {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        ଆକାର(pix_fmt));
        ଯଦି (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
        ପାଇଁ (i = j = 0; i < ctx->nb_formats; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;

            ପାଇଁ (k = 0; k < j; k++) {
                ଯଦି (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    ଭାଙ୍ଗ;
            }

            ଯଦି (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(pix_fmt));
    ଯଦି (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *friendly_name;
    ଅଚଳ ଅକ୍ଷର *match_string;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା quirks;
} vaapi_driver_quirks_table[] = {
#ଯଦି !VA_CHECK_VERSION(1, 0, 0)
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

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ଖାଲି;
    VAStatus vas;
    ଅଚଳ ଅକ୍ଷର *vendor_string;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, image_ଗଣନା;
    ଗଣନା AVPixelFormat pix_fmt;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା fourcc;

    image_ଗଣନା = va_Max_ଅଙ୍କ_Image_Formats(hwctx->display);
    ଯଦି (image_ଗଣନା <= 0) {
        err = AVERROR(EIO);
        ଯାଅ fail;
    }
    image_list = av_malloc(image_ଗଣନା * ଆକାର(*image_list));
    ଯଦି (!image_list) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_ଗଣନା);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        ଯାଅ fail;
    }

    ctx->formats  = av_malloc(image_ଗଣନା * ଆକାର(*ctx->formats));
    ଯଦି (!ctx->formats) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    ctx->nb_formats = 0;
    ପାଇଁ (i = 0; i < image_ଗଣନା; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        ଯଦି (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } ଅନ୍ୟଥା {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    ଯଦି (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    ଯଦି (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } ଅନ୍ୟଥା {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        ଯଦି (vendor_string) {
            ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                ଯଦି (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    ଭାଙ୍ଗ;
                }
            }
            ଯଦି (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } ଅନ୍ୟଥା {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    ଫେରନ୍ତୁ 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_buffer_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ସ୍ଥିର AVBufferRef *vaapi_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    ଯଦି (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        ଫେରନ୍ତୁ ଖାଲି;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        ଫେରନ୍ତୁ ଖାଲି;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           ଆକାର(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    ଯଦି (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    ଫେରନ୍ତୁ ref;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ଅଚଳ VAAPIFormatDescriptor *desc = ଖାଲି;
    VAImageFormat *expected_format = ଖାଲି;
    AVBufferRef *test_surface = ଖାଲି;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    ଯଦି (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        ଯଦି (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ଖାଲି)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଯଦି (!hwfc->pool) {
        ଯଦି (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା need_pixel_format = 1;
            ପାଇଁ (i = 0; i < avfc->nb_attributes; i++) {
                ଯଦି (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                ଯଦି (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        ଆକାର(*ctx->attributes));
            ଯଦି (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                ଯାଅ fail;
            }

            ପାଇଁ (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            ଯଦି (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Integer,
                    .ମୂଲ୍ୟ.ମୂଲ୍ୟ.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            ଯଦି (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Integer,
                    .ମୂଲ୍ୟ.ମୂଲ୍ୟ.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } ଅନ୍ୟଥା {
            ctx->attributes = ଖାଲି;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        ଯଦି (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          ଆକାର(*avfc->surface_ids));
            ଯଦି (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
        } ଅନ୍ୟଥା {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ଖାଲି;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(ଆକାର(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ଖାଲି);
        ଯଦି (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    ଯଦି (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        ଯଦି (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        ଯଦି (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    ଯଦି (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        ଯଦି (vas == VA_STATUS_SUCCESS) {
            ଯଦି (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } ଅନ୍ୟଥା {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } ଅନ୍ୟଥା {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } ଅନ୍ୟଥା {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    ଫେରନ୍ତୁ 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      ଗଣନା AVHWFrameTransferDirection dir,
                                      ଗଣନା AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    ଗଣନା AVPixelFormat *pix_fmts;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, k, sw_format_available;

    sw_format_available = 0;
    ପାଇଁ (i = 0; i < ctx->nb_formats; i++) {
        ଯଦି (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * ଆକାର(*pix_fmts));
    ଯଦି (!pix_fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } ଅନ୍ୟଥା {
        k = 0;
    }
    ପାଇଁ (i = 0; i < ctx->nb_formats; i++) {
        ଯଦି (ctx->formats[i].pix_fmt == hwfc->sw_format)
            ଜାରି;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    ଯଦି ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ଅଚଳ VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    ଶୂନ୍ୟ *address = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i;
#ଯଦି VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    ଯଦି (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    ଯଦି (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ଯଦି (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    ଯଦି (err < 0) {
        // Requested format is not a valid output format.
        ଫେରନ୍ତୁ err;
    }

    map = av_malloc(ଆକାର(*map));
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ଯାଅ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    ଯଦି (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ଯାଅ fail;
        }
        ଯଦି (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            ଯାଅ fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } ଅନ୍ୟଥା {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            ଯାଅ fail;
        }
        ଯଦି (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            ଯଦି (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                ଯାଅ fail;
            }
        }
    }

#ଯଦି VA_CHECK_VERSION(1, 21, 0)
    ଯଦି (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#ଅନ୍ୟଥା
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ଯାଅ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ପାଇଁ (i = 0; i < map->image.ଅଙ୍କ_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    ଯଦି (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (map) {
        ଯଦି (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        ଯଦି (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (dst->width > hwfc->width || dst->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (src->width > hwfc->width || src->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    err = av_frame_copy_props(dst, src);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    ଫେରନ୍ତୁ 0;
}

#ଯଦି CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    uint32_t va_fourcc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#ଯଦି defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#ଯଦି defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#ଯଦି defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#ଯଦି defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#ଯଦି defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#ଯଦି defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

ସ୍ଥିର ଶୂନ୍ୟ vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
#ଯଦି VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_prime2;
#ଅନ୍ୟଥା
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ଅଚଳ AVDRMFrameDescriptor *desc;
    ଅଚଳ VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, j;

#ଯଦି !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Integer,
            .ମୂଲ୍ୟ.ମୂଲ୍ୟ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ମୌଳିକ,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Pointer,
            .ମୂଲ୍ୟ.ମୂଲ୍ୟ.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    ଯଦି (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    va_fourcc = 0;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ଯଦି (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            ଜାରି;
        ପାଇଁ (j = 0; j < desc->nb_layers; j++) {
            ଯଦି (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                ଭାଙ୍ଗ;
        }
        ଯଦି (j != desc->nb_layers)
            ଜାରି;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        ଭାଙ୍ଗ;
    }
    ଯଦି (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#ଯଦି VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->ମୌଳିକ_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    ଯଦି (use_prime2) {
        VADRMPRIMESurfaceDescriptor ମୌଳିକ_desc;
        VASurfaceAttrib ମୌଳିକ_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Integer,
                .ମୂଲ୍ୟ.ମୂଲ୍ୟ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ମୌଳିକ_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Pointer,
                .ମୂଲ୍ୟ.ମୂଲ୍ୟ.p = &ମୌଳିକ_desc,
            }
        };
        ମୌଳିକ_desc.fourcc = va_fourcc;
        ମୌଳିକ_desc.width = src_fc->width;
        ମୌଳିକ_desc.height = src_fc->height;
        ମୌଳିକ_desc.ଅଙ୍କ_objects = desc->nb_objects;
        ପାଇଁ (i = 0; i < desc->nb_objects; ++i) {
            ମୌଳିକ_desc.objects[i].fd = desc->objects[i].fd;
            ମୌଳିକ_desc.objects[i].size = desc->objects[i].size;
            ମୌଳିକ_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        ମୌଳିକ_desc.ଅଙ୍କ_layers = desc->nb_layers;
        ପାଇଁ (i = 0; i < desc->nb_layers; ++i) {
            ମୌଳିକ_desc.layers[i].drm_format = desc->layers[i].format;
            ମୌଳିକ_desc.layers[i].ଅଙ୍କ_planes = desc->layers[i].nb_planes;
            ପାଇଁ (j = 0; j < desc->layers[i].nb_planes; ++j) {
                ମୌଳିକ_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                ମୌଳିକ_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                ମୌଳିକ_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            ଯଦି (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, ମୌଳିକ_desc.layers[i].pitch[1],
                    ମୌଳିକ_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, ମୌଳିକ_desc.layers[i].offset[1],
                    ମୌଳିକ_desc.layers[i].offset[2]);
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
                               ମୌଳିକ_attrs, FF_ARRAY_ELEMS(ମୌଳିକ_attrs));
        ଯଦି (vas != VA_STATUS_SUCCESS)
            src_vafc->ମୌଳିକ_2_import_unsupported = 1;
    }

    ଯଦି (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Integer,
                .ମୂଲ୍ୟ.ମୂଲ୍ୟ.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ମୌଳିକ,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .ମୂଲ୍ୟ.type    = VAGeneric_ମୂଲ୍ୟ_Type_Pointer,
                .ମୂଲ୍ୟ.ମୂଲ୍ୟ.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.ଅଙ୍କ_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        ପାଇଁ (i = 0; i < desc->nb_layers; i++) {
            ପାଇଁ (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.ଅଙ୍କ_planes = k;

        ଯଦି (format_desc->chroma_planes_swapped &&
            buffer_desc.ଅଙ୍କ_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#ଅନ୍ୟଥା
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.ଅଙ୍କ_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    ପାଇଁ (i = 0; i < desc->nb_layers; i++) {
        ପାଇଁ (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.ଅଙ୍କ_planes = k;

    ଯଦି (format_desc->chroma_planes_swapped &&
        buffer_desc.ଅଙ୍କ_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        ଫେରନ୍ତୁ AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (ଶୂନ୍ୟ*)(uintptr_t)surface_id);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    ଫେରନ୍ତୁ 0;
}

#ଯଦି VA_CHECK_VERSION(1, 1, 0)
ସ୍ଥିର ଶୂନ୍ୟ vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ଖାଲି;
    uint32_t export_flags;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    ଯଦି (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            ଫେରନ୍ତୁ AVERROR(EIO);
        }
    }

    ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ମୌଳିକ_2,
                                export_flags, &va_desc);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        ଯଦି (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

    drm_desc = av_mallocz(ଆକାର(*drm_desc));
    ଯଦି (!drm_desc) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.ଅଙ୍କ_objects;
    ପାଇଁ (i = 0; i < va_desc.ଅଙ୍କ_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.ଅଙ୍କ_layers;
    ପାଇଁ (i = 0; i < va_desc.ଅଙ୍କ_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].ଅଙ୍କ_planes;
        ପାଇଁ (j = 0; j < va_desc.layers[i].ଅଙ୍କ_planes; j++) {
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
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (i = 0; i < va_desc.ଅଙ୍କ_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    ଫେରନ୍ତୁ err;
}
#endif

#ଯଦି VA_CHECK_VERSION(0, 36, 0)
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

ସ୍ଥିର ଶୂନ୍ୟ vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = ଖାଲି;
    VASurfaceID surface_id;
    VAStatus vas;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(ଆକାର(*mapping));
    ଯଦି (!mapping)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ଯାଅ fail;
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ଯଦି (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            ଭାଙ୍ଗ;
    }
    ଯଦି (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        ଯାଅ fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_ମୌଳିକ;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    ଯଦି (mapping->drm_desc.nb_layers > 1) {
        ଯଦି (mapping->drm_desc.nb_layers != mapping->image.ଅଙ୍କ_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.ଅଙ୍କ_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            ଯାଅ fail_derived;
        }

        ପାଇଁ(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } ଅନ୍ୟଥା {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.ଅଙ୍କ_planes;
        ପାଇଁ (p = 0; p < mapping->image.ଅଙ୍କ_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        ଯାଅ fail_derived;
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
    ଯଦି (err < 0)
        ଯାଅ fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    ଫେରନ୍ତୁ 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    ଫେରନ୍ତୁ err;
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
#ଯଦି VA_CHECK_VERSION(1, 1, 0)
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    ଯଦି (err != AVERROR(ENOSYS))
        ଫେରନ୍ତୁ err;
#endif
#ଯଦି VA_CHECK_VERSION(0, 36, 0)
    ଫେରନ୍ତୁ vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ବାଛ (src->format) {
#ଯଦି CONFIG_LIBDRM
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଫେରନ୍ତୁ vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ବାଛ (dst->format) {
#ଯଦି CONFIG_LIBDRM
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଫେରନ୍ତୁ vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    ଯଦି (hwctx->display)
        vaTerminate(hwctx->display);

#ଯଦି HAVE_VAAPI_X11
    ଯଦି (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#ଯଦି HAVE_VAAPI_DRM
    ଯଦି (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#ଯଦି CONFIG_VAAPI_1
ସ୍ଥିର ଶୂନ୍ୟ vaapi_device_log_error(ଶୂନ୍ୟ *context, ଅଚଳ ଅକ୍ଷର *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

ସ୍ଥିର ଶୂନ୍ୟ vaapi_device_log_info(ଶୂନ୍ୟ *context, ଅଚଳ ଅକ୍ଷର *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା major, minor;
    VAStatus vas;

#ଯଦି CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    ଯଦି (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        ଫେରନ୍ତୁ AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                               AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ଖାଲି;
    ଅଚଳ AVDictionaryEntry *ent;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(ଆକାର(*priv));
    ଯଦି (!priv)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->ମୁକ୍ତ        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ଖାଲି, 0);
    ଯଦି (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        ଯଦି (!strcmp(ent->ମୂଲ୍ୟ, "drm")) {
            try_drm = 1;
        } ଅନ୍ୟଥା ଯଦି (!strcmp(ent->ମୂଲ୍ୟ, "x11")) {
            try_x11 = 1;
        } ଅନ୍ୟଥା ଯଦି (!strcmp(ent->ମୂଲ୍ୟ, "win32")) {
            try_win32 = 1;
        } ଅନ୍ୟଥା {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->ମୂଲ୍ୟ);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    } ଅନ୍ୟଥା {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#ଯଦି HAVE_VAAPI_DRM
    ଯେତେବେଳେ (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        ଯଦି (device) {
            priv->drm_fd = open(device, O_RDWR);
            ଯଦି (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                ଭାଙ୍ଗ;
            }
        } ଅନ୍ୟଥା {
            ଅକ୍ଷର path[64];
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା n, max_devices = 8;
#ଯଦି CONFIG_LIBDRM
            drmVersion *info;
            ଅଚଳ AVDictionaryEntry *kernel_driver;
            ଅଚଳ AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ଖାଲି, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ଖାଲି, 0);
#endif
            ପାଇଁ (n = 0; n < max_devices; n++) {
                snprintf(path, ଆକାର(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                ଯଦି (priv->drm_fd < 0) {
                    ଯଦି (errno == ENOENT) {
                        ଯଦି (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            ଜାରି;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } ଅନ୍ୟଥା
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    ଭାଙ୍ଗ;
                }
#ଯଦି CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                ଯଦି (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ଜାରି;
                }
                ଯଦି (kernel_driver) {
                    ଯଦି (strcmp(kernel_driver->ମୂଲ୍ୟ, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        ଜାରି;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    ଭାଙ୍ଗ;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } ଅନ୍ୟଥା ଯଦି (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ଜାରି;
                } ଅନ୍ୟଥା ଯଦି (vendor_id) {
                    drmDevicePtr device;
                    ଅକ୍ଷର drm_vendor[8];
                    ଯଦି (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ଜାରି;
                    }

                    snprintf(drm_vendor, ଆକାର(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    ଯଦି (strcmp(vendor_id->ମୂଲ୍ୟ, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->ମୂଲ୍ୟ);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ଜାରି;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->ମୂଲ୍ୟ);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    ଭାଙ୍ଗ;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                ଭାଙ୍ଗ;
            }
            ଯଦି (n >= max_devices)
                ଭାଙ୍ଗ;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        ଯଦି (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
        ଭାଙ୍ଗ;
    }
#endif

#ଯଦି HAVE_VAAPI_X11
    ଯଦି (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        ଯଦି (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } ଅନ୍ୟଥା {
            display = vaGetDisplay(priv->x11_display);
            ଯଦି (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                ଫେରନ୍ତୁ AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#ଯଦି HAVE_VAAPI_WIN32
    ଯଦି (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        ଯଦି (!device) {
            display = vaGetDisplayWin32(ଖାଲି);
        } ଅନ୍ୟଥା {
            IDXGIFactory2 *pDXGIFactory = ଖାଲି;
            IDXGIAdapter *pAdapter = ଖାଲି;
#ଯଦି !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            ଯଦି (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                ଫେରନ୍ତୁ AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            ଯଦି (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                ଫେରନ୍ତୁ AVERROR_UNKNOWN;
            }
#ଅନ୍ୟଥା
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            ଯଦି (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (ଶୂନ୍ୟ **)&pDXGIFactory))) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା adapter = atoi(device);
                ଯଦି (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    ଯଦି (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.ତଳ_Part,
                              desc.AdapterLuid.ଉପର_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#ଯଦି !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        ଯଦି (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    ଯଦି (!display) {
        ଯଦି (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        ଅନ୍ୟଥା
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ଖାଲି, 0);
    ଯଦି (ent) {
#ଯଦି VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->ମୂଲ୍ୟ);
        ଯଦି (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->ମୂଲ୍ୟ, vas, vaErrorStr(vas));
            vaTerminate(display);
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
#ଅନ୍ୟଥା
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    ଫେରନ୍ତୁ vaapi_device_connect(ctx, display);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
#ଯଦି HAVE_VAAPI_DRM
    ଯଦି (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd;

        ଯଦି (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

#ଯଦି CONFIG_LIBDRM
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣ୍ଠି_type = drm_Get_ଗଣ୍ଠି_Type_From_Fd(src_hwctx->fd);
            ଅକ୍ଷର *render_ଗଣ୍ଠି;
            ଯଦି (ଗଣ୍ଠି_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            }
            ଯଦି (ଗଣ୍ଠି_type == DRM_ଗଣ୍ଠି_RENDER) {
                fd = src_hwctx->fd;
            } ଅନ୍ୟଥା {
                render_ଗଣ୍ଠି = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                ଯଦି (!render_ଗଣ୍ଠି) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } ଅନ୍ୟଥା {
                    fd = open(render_ଗଣ୍ଠି, O_RDWR);
                    ଯଦି (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } ଅନ୍ୟଥା {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_ଗଣ୍ଠି);
                    }
                    ମୁକ୍ତ(render_ଗଣ୍ଠି);
                }
            }
        }
#ଅନ୍ୟଥା
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(ଆକାର(*priv));
        ଯଦି (!priv) {
            ଯଦି (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }

        ଯଦି (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } ଅନ୍ୟଥା {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->ମୁକ୍ତ        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        ଯଦି (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            ଫେରନ୍ତୁ AVERROR(EIO);
        }

        ଫେରନ୍ତୁ vaapi_device_connect(ctx, display);
    }
#endif
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ଅଚଳ HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = ଆକାର(VAAPIDeviceContext),
    .device_hwconfig_size   = ଆକାର(AVVAAPIHWConfig),
    .frames_hwctx_size      = ଆକାର(VAAPIFramesContext),

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

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
