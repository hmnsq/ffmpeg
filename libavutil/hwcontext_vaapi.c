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

#অন্তর্ভাব "config.h"

#যদি HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
প্রকারলেখ HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, শূন্য **ppFactory);
#endif
#যদি HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#যদি HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#যদি CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#অন্তর্ভাব <fcntl.h>
#যদি HAVE_UNISTD_H
#   include <unistd.h>
#endif


#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_drm.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_vaapi.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "pixfmt.h"


প্রকারলেখ কাঠামো VAAPIDevicePriv {
#যদি HAVE_VAAPI_X11
    Display *x11_display;
#endif

    পূর্ণসংখ্যা drm_fd;
} VAAPIDevicePriv;

প্রকারলেখ কাঠামো VAAPISurfaceFormat {
    গণনা AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned পূর্ণসংখ্যা fourcc;
} VAAPISurfaceFormat;

প্রকারলেখ কাঠামো VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    পূর্ণসংখ্যা              nb_formats;
} VAAPIDeviceContext;

প্রকারলেখ কাঠামো VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    পূর্ণসংখ্যা           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned পূর্ণসংখ্যা rt_format;
    // Whether vaDeriveImage works.
    পূর্ণসংখ্যা derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    পূর্ণসংখ্যা মৌলিক_2_import_unsupported;
} VAAPIFramesContext;

প্রকারলেখ কাঠামো VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    পূর্ণসংখ্যা flags;
} VAAPIMapping;

প্রকারলেখ কাঠামো VAAPIFormat {
    unsigned পূর্ণসংখ্যা fourcc;
    unsigned পূর্ণসংখ্যা rt_format;
    গণনা AVPixelFormat pix_fmt;
    পূর্ণসংখ্যা chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
স্থির ধ্রুবক VAAPIFormatDescriptor vaapi_format_map[] = {
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

স্থির ধ্রুবক VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned পূর্ণসংখ্যা fourcc)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        যদি (vaapi_format_map[i].fourcc == fourcc)
            ফেরত &vaapi_format_map[i];
    ফেরত ফাঁকা;
}

স্থির ধ্রুবক VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(গণনা AVPixelFormat pix_fmt, ধ্রুবক VAAPIFormatDescriptor *পূর্ব)
{
    ধ্রুবক VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    যদি (!পূর্ব)
        পূর্ব = vaapi_format_map;
    অন্যথা
        পূর্ব++;

    জন্য (; পূর্ব < end; পূর্ব++)
        যদি (পূর্ব->pix_fmt == pix_fmt)
            ফেরত পূর্ব;
    ফেরত ফাঁকা;
}

স্থির গণনা AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned পূর্ণসংখ্যা fourcc)
{
    ধ্রুবক VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    যদি (desc)
        ফেরত desc->pix_fmt;
    অন্যথা
        ফেরত AV_PIX_FMT_NONE;
}

স্থির পূর্ণসংখ্যা vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  গণনা AVPixelFormat pix_fmt,
                                  ধ্রুবক VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ধ্রুবক VAAPIFormatDescriptor *desc = ফাঁকা;
    পূর্ণসংখ্যা i;

    যখন ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        জন্য (i = 0; i < ctx->nb_formats; i++) {
            যদি (ctx->formats[i].fourcc == desc->fourcc) {
                যদি (_desc)
                    *_desc = desc;
                যদি (image_format)
                    *image_format = &ctx->formats[i].image_format;
                ফেরত 0;
            }
        }
    }

    ফেরত AVERROR(ENOSYS);
}

স্থির পূর্ণসংখ্যা vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  গণনা AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    যদি (!image_format)
        ফেরত AVERROR(EINVAL);
    ফেরত vaapi_get_img_desc_and_format(hwdev, pix_fmt, ফাঁকা, image_format);
}

স্থির পূর্ণসংখ্যা vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        ধ্রুবক শূন্য *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ধ্রুবক AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ফাঁকা;
    VAStatus vas;
    গণনা AVPixelFormat pix_fmt;
    unsigned পূর্ণসংখ্যা fourcc;
    পূর্ণসংখ্যা err, i, j, attr_গুনতি, pix_fmt_গুনতি;

    যদি (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_গুনতি = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_গুনতি);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            যাও fail;
        }

        attr_list = av_malloc(attr_গুনতি * আকার(*attr_list));
        যদি (!attr_list) {
            err = AVERROR(ENOMEM);
            যাও fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_গুনতি);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            যাও fail;
        }

        pix_fmt_গুনতি = 0;
        জন্য (i = 0; i < attr_গুনতি; i++) {
            নির্বাচন (attr_list[i].type) {
            ক্ষেত্র VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].মান.মান.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                যদি (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_গুনতি;
                } অন্যথা {
                    // Something unsupported - ignore.
                }
                বিরতি;
            ক্ষেত্র VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].মান.মান.i;
                বিরতি;
            ক্ষেত্র VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].মান.মান.i;
                বিরতি;
            ক্ষেত্র VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].মান.মান.i;
                বিরতি;
            ক্ষেত্র VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].মান.মান.i;
                বিরতি;
            }
        }
        যদি (pix_fmt_গুনতি == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ফাঁকা;
        } অন্যথা {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_গুনতি + 1,
                                                            আকার(pix_fmt));
            যদি (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                যাও fail;
            }

            জন্য (i = j = 0; i < attr_গুনতি; i++) {
                পূর্ণসংখ্যা k;

                যদি (attr_list[i].type != VASurfaceAttribPixelFormat)
                    চালু;
                fourcc = attr_list[i].মান.মান.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                যদি (pix_fmt == AV_PIX_FMT_NONE)
                    চালু;

                জন্য (k = 0; k < j; k++) {
                    যদি (constraints->valid_sw_formats[k] == pix_fmt)
                        বিরতি;
                }

                যদি (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } অন্যথা {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        আকার(pix_fmt));
        যদি (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            যাও fail;
        }
        জন্য (i = j = 0; i < ctx->nb_formats; i++) {
            পূর্ণসংখ্যা k;

            জন্য (k = 0; k < j; k++) {
                যদি (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    বিরতি;
            }

            যদি (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, আকার(pix_fmt));
    যদি (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    ফেরত err;
}

স্থির ধ্রুবক কাঠামো {
    ধ্রুবক অক্ষর *friendly_name;
    ধ্রুবক অক্ষর *match_string;
    unsigned পূর্ণসংখ্যা quirks;
} vaapi_driver_quirks_table[] = {
#যদি !VA_CHECK_VERSION(1, 0, 0)
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

স্থির পূর্ণসংখ্যা vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ফাঁকা;
    VAStatus vas;
    ধ্রুবক অক্ষর *vendor_string;
    পূর্ণসংখ্যা err, i, image_গুনতি;
    গণনা AVPixelFormat pix_fmt;
    unsigned পূর্ণসংখ্যা fourcc;

    image_গুনতি = va_Max_অঙ্ক_Image_Formats(hwctx->display);
    যদি (image_গুনতি <= 0) {
        err = AVERROR(EIO);
        যাও fail;
    }
    image_list = av_malloc(image_গুনতি * আকার(*image_list));
    যদি (!image_list) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_গুনতি);
    যদি (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        যাও fail;
    }

    ctx->formats  = av_malloc(image_গুনতি * আকার(*ctx->formats));
    যদি (!ctx->formats) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }
    ctx->nb_formats = 0;
    জন্য (i = 0; i < image_গুনতি; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        যদি (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } অন্যথা {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    যদি (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    যদি (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } অন্যথা {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        যদি (vendor_string) {
            জন্য (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                যদি (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    বিরতি;
                }
            }
            যদি (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } অন্যথা {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    ফেরত 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    ফেরত err;
}

স্থির শূন্য vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

স্থির শূন্য vaapi_বাফার_free(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)তথ্য;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

স্থির AVBufferRef *vaapi_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    যদি (hwfc->initial_pool_আকার > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_আকার)
        ফেরত ফাঁকা;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        ফেরত ফাঁকা;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_বাফার_create((uint8_t*)(uintptr_t)surface_id,
                           আকার(surface_id), &vaapi_বাফার_free,
                           hwfc, AV_বাফার_FLAG_READONLY);
    যদি (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        ফেরত ফাঁকা;
    }

    যদি (hwfc->initial_pool_আকার > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_আকার);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    ফেরত ref;
}

স্থির পূর্ণসংখ্যা vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ধ্রুবক VAAPIFormatDescriptor *desc = ফাঁকা;
    VAImageFormat *expected_format = ফাঁকা;
    AVBufferRef *test_surface = ফাঁকা;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    পূর্ণসংখ্যা err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    যদি (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        যদি (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ফাঁকা)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ফেরত AVERROR(EINVAL);
        }
    }

    যদি (!hwfc->pool) {
        যদি (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            পূর্ণসংখ্যা need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            পূর্ণসংখ্যা need_pixel_format = 1;
            জন্য (i = 0; i < avfc->nb_attributes; i++) {
                যদি (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                যদি (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        আকার(*ctx->attributes));
            যদি (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                যাও fail;
            }

            জন্য (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            যদি (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .মান.type    = VAGeneric_মান_Type_Integer,
                    .মান.মান.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            যদি (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .মান.type    = VAGeneric_মান_Type_Integer,
                    .মান.মান.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } অন্যথা {
            ctx->attributes = ফাঁকা;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        যদি (hwfc->initial_pool_আকার > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_আকার *
                                          আকার(*avfc->surface_ids));
            যদি (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                যাও fail;
            }
        } অন্যথা {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ফাঁকা;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_বাফার_pool_init2(আকার(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ফাঁকা);
        যদি (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            যাও fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    যদি (hwfc->pool) {
        test_surface = av_বাফার_pool_get(hwfc->pool);
        যদি (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            যাও fail;
        }
    } অন্যথা {
        test_surface = av_বাফার_pool_get(ffhwframesctx(hwfc)->pool_internal);
        যদি (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            যাও fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->তথ্য;

    ctx->derive_works = 0;
    যদি (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        যদি (vas == VA_STATUS_SUCCESS) {
            যদি (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } অন্যথা {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } অন্যথা {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } অন্যথা {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_বাফার_unref(&test_surface);
    ফেরত 0;

fail:
    av_বাফার_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    ফেরত err;
}

স্থির শূন্য vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

স্থির পূর্ণসংখ্যা vaapi_get_বাফার(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_বাফার_pool_get(hwfc->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    frame->তথ্য[3] = frame->buf[0]->তথ্য;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      গণনা AVHWFrameTransferDirection dir,
                                      গণনা AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    গণনা AVPixelFormat *pix_fmts;
    পূর্ণসংখ্যা i, k, sw_format_available;

    sw_format_available = 0;
    জন্য (i = 0; i < ctx->nb_formats; i++) {
        যদি (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * আকার(*pix_fmts));
    যদি (!pix_fmts)
        ফেরত AVERROR(ENOMEM);

    যদি (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } অন্যথা {
        k = 0;
    }
    জন্য (i = 0; i < ctx->nb_formats; i++) {
        যদি (ctx->formats[i].pix_fmt == hwfc->sw_format)
            চালু;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ফেরত 0;
}

স্থির শূন্য vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->তথ্য[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_বাফার(hwctx->display, map->image.buf);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    যদি ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

স্থির পূর্ণসংখ্যা vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ধ্রুবক VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    শূন্য *address = ফাঁকা;
    পূর্ণসংখ্যা err, i;
#যদি VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->তথ্য[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    যদি (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        ফেরত AVERROR(EINVAL);
    }
    যদি (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    যদি (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        ফেরত AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    যদি (err < 0) {
        // Requested format is not a valid output format.
        ফেরত err;
    }

    map = av_malloc(আকার(*map));
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        যাও fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    যদি (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            যাও fail;
        }
        যদি (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            যাও fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } অন্যথা {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            যাও fail;
        }
        যদি (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            যদি (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                যাও fail;
            }
        }
    }

#যদি VA_CHECK_VERSION(1, 21, 0)
    যদি (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    যদি (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#অন্যথা
    vas = va_Map_বাফার(hwctx->display, map->image.buf, &address);
#endif
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        যাও fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    জন্য (i = 0; i < map->image.অঙ্ক_planes; i++) {
        dst->তথ্য[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    যদি (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->তথ্য[1], dst->তথ্য[2]);
    }

    ফেরত 0;

fail:
    যদি (map) {
        যদি (address)
            va_Unmap_বাফার(hwctx->display, map->image.buf);
        যদি (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    ফেরত err;
}

স্থির পূর্ণসংখ্যা vaapi_transfer_তথ্য_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (dst->width > hwfc->width || dst->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    যদি (err)
        যাও fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা vaapi_transfer_তথ্য_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (src->width > hwfc->width || src->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    যদি (err)
        যাও fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    যদি (err)
        ফেরত err;

    err = av_frame_copy_props(dst, src);
    যদি (err)
        ফেরত err;

    ফেরত 0;
}

#যদি CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
স্থির ধ্রুবক কাঠামো {
    uint32_t va_fourcc;
    পূর্ণসংখ্যা   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#যদি defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#যদি defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#যদি defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#যদি defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#যদি defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#যদি defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

স্থির শূন্য vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

স্থির পূর্ণসংখ্যা vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
#যদি VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    পূর্ণসংখ্যা use_prime2;
#অন্যথা
    পূর্ণসংখ্যা k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->তথ্য;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ধ্রুবক AVDRMFrameDescriptor *desc;
    ধ্রুবক VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    পূর্ণসংখ্যা err, i, j;

#যদি !VA_CHECK_VERSION(1, 1, 0)
    unsigned long বাফার_handle;
    VASurfaceAttribExternalBuffers বাফার_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .মান.type    = VAGeneric_মান_Type_Integer,
            .মান.মান.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_মৌলিক,
        },
        {
            .type  = VASurface_Attrib_External_বাফার_Descriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .মান.type    = VAGeneric_মান_Type_Pointer,
            .মান.মান.p = &বাফার_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->তথ্য[0];

    যদি (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        ফেরত AVERROR(EINVAL);
    }

    va_fourcc = 0;
    জন্য (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        যদি (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            চালু;
        জন্য (j = 0; j < desc->nb_layers; j++) {
            যদি (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                বিরতি;
        }
        যদি (j != desc->nb_layers)
            চালু;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        বিরতি;
    }
    যদি (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        ফেরত AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#যদি VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->মৌলিক_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    যদি (use_prime2) {
        VADRMPRIMESurfaceDescriptor মৌলিক_desc;
        VASurfaceAttrib মৌলিক_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .মান.type    = VAGeneric_মান_Type_Integer,
                .মান.মান.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_মৌলিক_2,
            },
            {
                .type  = VASurface_Attrib_External_বাফার_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .মান.type    = VAGeneric_মান_Type_Pointer,
                .মান.মান.p = &মৌলিক_desc,
            }
        };
        মৌলিক_desc.fourcc = va_fourcc;
        মৌলিক_desc.width = src_fc->width;
        মৌলিক_desc.height = src_fc->height;
        মৌলিক_desc.অঙ্ক_objects = desc->nb_objects;
        জন্য (i = 0; i < desc->nb_objects; ++i) {
            মৌলিক_desc.objects[i].fd = desc->objects[i].fd;
            মৌলিক_desc.objects[i].আকার_2 = desc->objects[i].আকার_2;
            মৌলিক_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        মৌলিক_desc.অঙ্ক_layers = desc->nb_layers;
        জন্য (i = 0; i < desc->nb_layers; ++i) {
            মৌলিক_desc.layers[i].drm_format = desc->layers[i].format;
            মৌলিক_desc.layers[i].অঙ্ক_planes = desc->layers[i].nb_planes;
            জন্য (j = 0; j < desc->layers[i].nb_planes; ++j) {
                মৌলিক_desc.layers[i].object_সূচক[j] =
                        desc->layers[i].planes[j].object_সূচক;
                মৌলিক_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                মৌলিক_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            যদি (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, মৌলিক_desc.layers[i].pitch[1],
                    মৌলিক_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, মৌলিক_desc.layers[i].offset[1],
                    মৌলিক_desc.layers[i].offset[2]);
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
                               মৌলিক_attrs, FF_ARRAY_ELEMS(মৌলিক_attrs));
        যদি (vas != VA_STATUS_SUCCESS)
            src_vafc->মৌলিক_2_import_unsupported = 1;
    }

    যদি (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        পূর্ণসংখ্যা k;
        uintptr_t বাফার_handle;
        VASurfaceAttribExternalBuffers বাফার_desc;
        VASurfaceAttrib বাফার_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .মান.type    = VAGeneric_মান_Type_Integer,
                .মান.মান.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_মৌলিক,
            },
            {
                .type  = VASurface_Attrib_External_বাফার_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .মান.type    = VAGeneric_মান_Type_Pointer,
                .মান.মান.p = &বাফার_desc,
            }
        };

        বাফার_handle = desc->objects[0].fd;
        বাফার_desc.pixel_format = va_fourcc;
        বাফার_desc.width        = src_fc->width;
        বাফার_desc.height       = src_fc->height;
        বাফার_desc.তথ্য_আকার    = desc->objects[0].আকার_2;
        বাফার_desc.buffers      = &বাফার_handle;
        বাফার_desc.অঙ্ক_buffers  = 1;
        বাফার_desc.flags        = 0;

        k = 0;
        জন্য (i = 0; i < desc->nb_layers; i++) {
            জন্য (j = 0; j < desc->layers[i].nb_planes; j++) {
                বাফার_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                বাফার_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        বাফার_desc.অঙ্ক_planes = k;

        যদি (format_desc->chroma_planes_swapped &&
            বাফার_desc.অঙ্ক_planes == 3) {
            FFSWAP(uint32_t, বাফার_desc.pitches[1], বাফার_desc.pitches[2]);
            FFSWAP(uint32_t, বাফার_desc.offsets[1], বাফার_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               বাফার_attrs, FF_ARRAY_ELEMS(বাফার_attrs));
    }
#অন্যথা
    বাফার_handle = desc->objects[0].fd;
    বাফার_desc.pixel_format = va_fourcc;
    বাফার_desc.width        = src_fc->width;
    বাফার_desc.height       = src_fc->height;
    বাফার_desc.তথ্য_আকার    = desc->objects[0].আকার_2;
    বাফার_desc.buffers      = &বাফার_handle;
    বাফার_desc.অঙ্ক_buffers  = 1;
    বাফার_desc.flags        = 0;

    k = 0;
    জন্য (i = 0; i < desc->nb_layers; i++) {
        জন্য (j = 0; j < desc->layers[i].nb_planes; j++) {
            বাফার_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            বাফার_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    বাফার_desc.অঙ্ক_planes = k;

    যদি (format_desc->chroma_planes_swapped &&
        বাফার_desc.অঙ্ক_planes == 3) {
        FFSWAP(uint32_t, বাফার_desc.pitches[1], বাফার_desc.pitches[2]);
        FFSWAP(uint32_t, বাফার_desc.offsets[1], বাফার_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        ফেরত AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (শূন্য*)(uintptr_t)surface_id);
    যদি (err < 0)
        ফেরত err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->তথ্য[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    ফেরত 0;
}

#যদি VA_CHECK_VERSION(1, 1, 0)
স্থির শূন্য vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

স্থির পূর্ণসংখ্যা vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ফাঁকা;
    uint32_t export_flags;
    পূর্ণসংখ্যা err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->তথ্য[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    যদি (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            ফেরত AVERROR(EIO);
        }
    }

    যদি (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_মৌলিক_2,
                                export_flags, &va_desc);
    যদি (vas != VA_STATUS_SUCCESS) {
        যদি (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            ফেরত AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        ফেরত AVERROR(EIO);
    }

    drm_desc = av_mallocz(আকার(*drm_desc));
    যদি (!drm_desc) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.অঙ্ক_objects;
    জন্য (i = 0; i < va_desc.অঙ্ক_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].আকার_2 = va_desc.objects[i].আকার_2;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.অঙ্ক_layers;
    জন্য (i = 0; i < va_desc.অঙ্ক_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].অঙ্ক_planes;
        জন্য (j = 0; j < va_desc.layers[i].অঙ্ক_planes; j++) {
            drm_desc->layers[i].planes[j].object_সূচক =
                va_desc.layers[i].object_সূচক[j];
            drm_desc->layers[i].planes[j].offset =
                va_desc.layers[i].offset[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &vaapi_unmap_to_drm_esh, drm_desc);
    যদি (err < 0)
        যাও fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->তথ্য[0] = (uint8_t*)drm_desc;

    ফেরত 0;

fail:
    জন্য (i = 0; i < va_desc.অঙ্ক_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    ফেরত err;
}
#endif

#যদি VA_CHECK_VERSION(0, 36, 0)
প্রকারলেখ কাঠামো VAAPIDRMImage_বাফার_Mapping {
    VAImage      image;
    VABufferInfo বাফার_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_বাফার_Mapping;

স্থির শূন্য vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_বাফার_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->তথ্য[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_বাফার_Handle(hwctx->display, mapping->image.buf);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

স্থির পূর্ণসংখ্যা vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_বাফার_Mapping *mapping = ফাঁকা;
    VASurfaceID surface_id;
    VAStatus vas;
    পূর্ণসংখ্যা err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->তথ্য[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(আকার(*mapping));
    যদি (!mapping)
        ফেরত AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        যাও fail;
    }

    জন্য (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        যদি (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            বিরতি;
    }
    যদি (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        যাও fail_derived;
    }

    mapping->বাফার_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_মৌলিক;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    যদি (mapping->drm_desc.nb_layers > 1) {
        যদি (mapping->drm_desc.nb_layers != mapping->image.অঙ্ক_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.অঙ্ক_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            যাও fail_derived;
        }

        জন্য(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_সূচক = 0,
                    .offset       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } অন্যথা {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.অঙ্ক_planes;
        জন্য (p = 0; p < mapping->image.অঙ্ক_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_সূচক = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_বাফার_Handle(hwctx->display, mapping->image.buf,
                                &mapping->বাফার_info);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        যাও fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->বাফার_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->বাফার_info.handle,
        .আকার_2 = mapping->image.তথ্য_আকার,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_to_drm_abh,
                                mapping);
    যদি (err < 0)
        যাও fail_mapped;

    dst->তথ্য[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    ফেরত 0;

fail_mapped:
    va_Release_বাফার_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    ফেরত err;
}
#endif

স্থির পূর্ণসংখ্যা vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
#যদি VA_CHECK_VERSION(1, 1, 0)
    পূর্ণসংখ্যা err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    যদি (err != AVERROR(ENOSYS))
        ফেরত err;
#endif
#যদি VA_CHECK_VERSION(0, 36, 0)
    ফেরত vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    ফেরত AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

স্থির পূর্ণসংখ্যা vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    নির্বাচন (src->format) {
#যদি CONFIG_LIBDRM
    ক্ষেত্র AV_PIX_FMT_DRM_মৌলিক:
        ফেরত vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }
}

স্থির পূর্ণসংখ্যা vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    নির্বাচন (dst->format) {
#যদি CONFIG_LIBDRM
    ক্ষেত্র AV_PIX_FMT_DRM_মৌলিক:
        ফেরত vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    পূর্বনির্ধারিত:
        ফেরত vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

স্থির শূন্য vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    যদি (hwctx->display)
        vaTerminate(hwctx->display);

#যদি HAVE_VAAPI_X11
    যদি (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#যদি HAVE_VAAPI_DRM
    যদি (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#যদি CONFIG_VAAPI_1
স্থির শূন্য vaapi_device_log_error(শূন্য *context, ধ্রুবক অক্ষর *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

স্থির শূন্য vaapi_device_log_info(শূন্য *context, ধ্রুবক অক্ষর *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

স্থির পূর্ণসংখ্যা vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    পূর্ণসংখ্যা major, minor;
    VAStatus vas;

#যদি CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    যদি (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        ফেরত AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vaapi_device_create(AVHWDeviceContext *ctx, ধ্রুবক অক্ষর *device,
                               AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ফাঁকা;
    ধ্রুবক AVDictionaryEntry *ent;
    পূর্ণসংখ্যা try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(আকার(*priv));
    যদি (!priv)
        ফেরত AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->মুক্ত        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ফাঁকা, 0);
    যদি (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        যদি (!strcmp(ent->মান, "drm")) {
            try_drm = 1;
        } অন্যথা যদি (!strcmp(ent->মান, "x11")) {
            try_x11 = 1;
        } অন্যথা যদি (!strcmp(ent->মান, "win32")) {
            try_win32 = 1;
        } অন্যথা {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->মান);
            ফেরত AVERROR(EINVAL);
        }
    } অন্যথা {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#যদি HAVE_VAAPI_DRM
    যখন (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        পূর্ণসংখ্যা loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        যদি (device) {
            priv->drm_fd = open(device, O_RDWR);
            যদি (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                বিরতি;
            }
        } অন্যথা {
            অক্ষর path[64];
            পূর্ণসংখ্যা n, max_devices = 8;
#যদি CONFIG_LIBDRM
            drmVersion *info;
            ধ্রুবক AVDictionaryEntry *kernel_driver;
            ধ্রুবক AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ফাঁকা, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ফাঁকা, 0);
#endif
            জন্য (n = 0; n < max_devices; n++) {
                snprintf(path, আকার(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                যদি (priv->drm_fd < 0) {
                    যদি (errno == ENOENT) {
                        যদি (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            চালু;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } অন্যথা
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    বিরতি;
                }
#যদি CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                যদি (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    চালু;
                }
                যদি (kernel_driver) {
                    যদি (strcmp(kernel_driver->মান, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        চালু;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    বিরতি;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } অন্যথা যদি (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    চালু;
                } অন্যথা যদি (vendor_id) {
                    drmDevicePtr device;
                    অক্ষর drm_vendor[8];
                    যদি (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        চালু;
                    }

                    snprintf(drm_vendor, আকার(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    যদি (strcmp(vendor_id->মান, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->মান);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        চালু;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->মান);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    বিরতি;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                বিরতি;
            }
            যদি (n >= max_devices)
                বিরতি;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        যদি (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            ফেরত AVERROR_EXTERNAL;
        }
        বিরতি;
    }
#endif

#যদি HAVE_VAAPI_X11
    যদি (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        যদি (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } অন্যথা {
            display = vaGetDisplay(priv->x11_display);
            যদি (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                ফেরত AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#যদি HAVE_VAAPI_WIN32
    যদি (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        যদি (!device) {
            display = vaGetDisplayWin32(ফাঁকা);
        } অন্যথা {
            IDXGIFactory2 *pDXGIFactory = ফাঁকা;
            IDXGIAdapter *pAdapter = ফাঁকা;
#যদি !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            যদি (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                ফেরত AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            যদি (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                ফেরত AVERROR_UNKNOWN;
            }
#অন্যথা
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            যদি (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (শূন্য **)&pDXGIFactory))) {
                পূর্ণসংখ্যা adapter = atoi(device);
                যদি (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    যদি (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.নিচের_Part,
                              desc.AdapterLuid.উপরের_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#যদি !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        যদি (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            ফেরত AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    যদি (!display) {
        যদি (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        অন্যথা
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        ফেরত AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ফাঁকা, 0);
    যদি (ent) {
#যদি VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->মান);
        যদি (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->মান, vas, vaErrorStr(vas));
            vaTerminate(display);
            ফেরত AVERROR_EXTERNAL;
        }
#অন্যথা
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    ফেরত vaapi_device_connect(ctx, display);
}

স্থির পূর্ণসংখ্যা vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, পূর্ণসংখ্যা flags)
{
#যদি HAVE_VAAPI_DRM
    যদি (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        পূর্ণসংখ্যা fd;

        যদি (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            ফেরত AVERROR(EINVAL);
        }

#যদি CONFIG_LIBDRM
        {
            পূর্ণসংখ্যা গ্রন্থি_type = drm_Get_গ্রন্থি_Type_From_Fd(src_hwctx->fd);
            অক্ষর *render_গ্রন্থি;
            যদি (গ্রন্থি_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                ফেরত AVERROR(EINVAL);
            }
            যদি (গ্রন্থি_type == DRM_গ্রন্থি_RENDER) {
                fd = src_hwctx->fd;
            } অন্যথা {
                render_গ্রন্থি = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                যদি (!render_গ্রন্থি) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } অন্যথা {
                    fd = open(render_গ্রন্থি, O_RDWR);
                    যদি (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } অন্যথা {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_গ্রন্থি);
                    }
                    মুক্ত(render_গ্রন্থি);
                }
            }
        }
#অন্যথা
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(আকার(*priv));
        যদি (!priv) {
            যদি (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            ফেরত AVERROR(ENOMEM);
        }

        যদি (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } অন্যথা {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->মুক্ত        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        যদি (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            ফেরত AVERROR(EIO);
        }

        ফেরত vaapi_device_connect(ctx, display);
    }
#endif
    ফেরত AVERROR(ENOSYS);
}

ধ্রুবক HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_আকার      = আকার(VAAPIDeviceContext),
    .device_hwconfig_আকার   = আকার(AVVAAPIHWConfig),
    .frames_hwctx_আকার      = আকার(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .frames_get_constraints = &vaapi_frames_get_constraints,
    .frames_init            = &vaapi_frames_init,
    .frames_uninit          = &vaapi_frames_uninit,
    .frames_get_বাফার      = &vaapi_get_বাফার,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_তথ্য_to       = &vaapi_transfer_তথ্য_to,
    .transfer_তথ্য_from     = &vaapi_transfer_তথ্য_from,
    .map_to                 = &vaapi_map_to,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
