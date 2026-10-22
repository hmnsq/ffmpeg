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

#ضمن "config.h"

#إذا HAVE_VAAPI_WIN32
#   include <windows.h>
#تعریف_کرو COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
تعريفنوع HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, فراغ **ppFactory);
#جے_انت
#إذا HAVE_VAAPI_X11
#   include <va/va_x11.h>
#جے_انت
#إذا HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#جے_انت

#إذا CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#جے_انت

#ضمن <fcntl.h>
#إذا HAVE_UNISTD_H
#   include <unistd.h>
#جے_انت


#ضمن "avassert.h"
#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_drm.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_vaapi.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"


تعريفنوع بنية VAAPIDevicePriv {
#إذا HAVE_VAAPI_X11
    Display *x11_display;
#جے_انت

    صحيح drm_fd;
} VAAPIDevicePriv;

تعريفنوع بنية VAAPISurfaceFormat {
    تعداد AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    بنانشانی صحيح fourcc;
} VAAPISurfaceFormat;

تعريفنوع بنية VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    صحيح              nb_formats;
} VAAPIDeviceContext;

تعريفنوع بنية VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *گن;
    صحيح           nb_گن;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    بنانشانی صحيح rt_format;
    // Whether vaDeriveImage works.
    صحيح derive_چلدا;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    صحيح مفرد_2_import_unsupported;
} VAAPIFramesContext;

تعريفنوع بنية VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    صحيح flags;
} VAAPIMapping;

تعريفنوع بنية VAAPIFormat {
    بنانشانی صحيح fourcc;
    بنانشانی صحيح rt_format;
    تعداد AVPixelFormat pix_fmt;
    صحيح chroma_planes_swapped;
} VAAPIFormatDescriptor;

#تعریف_کرو MAP(va, rt, av, وٹاندرا_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        وٹاندرا_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ساكن ثابت VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#جے_تعریف_شدہ VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#جے_انت
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#جے_تعریف_شدہ VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#جے_انت
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#جے_تعریف_شدہ VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#جے_انت
#جے_تعریف_شدہ VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#جے_انت
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#جے_تعریف_شدہ VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#جے_انت
    MAP(Y800, YUV400,  GRAY8,   0),
#جے_تعریف_شدہ VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#جے_انت
#جے_تعریف_شدہ VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#جے_انت
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#جے_تعریف_شدہ VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#جے_انت
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#جے_تعریف_شدہ VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#جے_انت
#جے_تعریف_شدہ VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#جے_انت
#جے_تعریف_شدہ VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#جے_انت
};
#تعریف_رد MAP

ساكن ثابت VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(بنانشانی صحيح fourcc)
{
    صحيح i;
    لكل (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        إذا (vaapi_format_map[i].fourcc == fourcc)
            أرجع &vaapi_format_map[i];
    أرجع عدم;
}

ساكن ثابت VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(تعداد AVPixelFormat pix_fmt, ثابت VAAPIFormatDescriptor *prev)
{
    ثابت VAAPIFormatDescriptor *سرا = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    إذا (!prev)
        prev = vaapi_format_map;
    وإلا
        prev++;

    لكل (; prev < سرا; prev++)
        إذا (prev->pix_fmt == pix_fmt)
            أرجع prev;
    أرجع عدم;
}

ساكن تعداد AVPixelFormat vaapi_pix_fmt_from_fourcc(بنانشانی صحيح fourcc)
{
    ثابت VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    إذا (desc)
        أرجع desc->pix_fmt;
    وإلا
        أرجع AV_PIX_FMT_NONE;
}

ساكن صحيح vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  تعداد AVPixelFormat pix_fmt,
                                  ثابت VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ثابت VAAPIFormatDescriptor *desc = عدم;
    صحيح i;

    طالما ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        لكل (i = 0; i < ctx->nb_formats; i++) {
            إذا (ctx->formats[i].fourcc == desc->fourcc) {
                إذا (_desc)
                    *_desc = desc;
                إذا (image_format)
                    *image_format = &ctx->formats[i].image_format;
                أرجع 0;
            }
        }
    }

    أرجع AVERROR(ENOSYS);
}

ساكن صحيح vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  تعداد AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    إذا (!image_format)
        أرجع AVERROR(EINVAL);
    أرجع vaapi_get_img_desc_and_format(hwdev, pix_fmt, عدم, image_format);
}

ساكن صحيح vaapi_چوکھٹے_get_constraints(AVHWDeviceContext *hwdev,
                                        ثابت فراغ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ثابت AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = عدم;
    VAStatus vas;
    تعداد AVPixelFormat pix_fmt;
    بنانشانی صحيح fourcc;
    صحيح err, i, j, attr_گنتی, pix_fmt_گنتی;

    إذا (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_گن)) {
        attr_گنتی = 0;
        vas = va_Query_Surface_گن(hwctx->display, config->config_id,
                                       0, &attr_گنتی);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            اذهب fail;
        }

        attr_list = av_malloc(attr_گنتی * حجم(*attr_list));
        إذا (!attr_list) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }

        vas = va_Query_Surface_گن(hwctx->display, config->config_id,
                                       attr_list, &attr_گنتی);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            اذهب fail;
        }

        pix_fmt_گنتی = 0;
        لكل (i = 0; i < attr_گنتی; i++) {
            بدل (attr_list[i].type) {
            حالة VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].قدر.قدر.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                إذا (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_گنتی;
                } وإلا {
                    // Something unsupported - ignore.
                }
                اكسر;
            حالة VASurface_Attrib_Min_چوڑائی:
                constraints->min_چوڑائی  = attr_list[i].قدر.قدر.i;
                اكسر;
            حالة VASurface_Attrib_Min_اچائی:
                constraints->min_اچائی = attr_list[i].قدر.قدر.i;
                اكسر;
            حالة VASurface_Attrib_Max_چوڑائی:
                constraints->max_چوڑائی  = attr_list[i].قدر.قدر.i;
                اكسر;
            حالة VASurface_Attrib_Max_اچائی:
                constraints->max_اچائی = attr_list[i].قدر.قدر.i;
                اكسر;
            }
        }
        إذا (pix_fmt_گنتی == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = عدم;
        } وإلا {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_گنتی + 1,
                                                            حجم(pix_fmt));
            إذا (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                اذهب fail;
            }

            لكل (i = j = 0; i < attr_گنتی; i++) {
                صحيح k;

                إذا (attr_list[i].type != VASurfaceAttribPixelFormat)
                    استمر;
                fourcc = attr_list[i].قدر.قدر.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                إذا (pix_fmt == AV_PIX_FMT_NONE)
                    استمر;

                لكل (k = 0; k < j; k++) {
                    إذا (constraints->valid_sw_formats[k] == pix_fmt)
                        اكسر;
                }

                إذا (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } وإلا {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        حجم(pix_fmt));
        إذا (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
        لكل (i = j = 0; i < ctx->nb_formats; i++) {
            صحيح k;

            لكل (k = 0; k < j; k++) {
                إذا (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    اكسر;
            }

            إذا (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, حجم(pix_fmt));
    إذا (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    أرجع err;
}

ساكن ثابت بنية {
    ثابت حرف *friendly_name;
    ثابت حرف *میل_string;
    بنانشانی صحيح quirks;
} vaapi_driver_quirks_جدول[] = {
#إذا !VA_CHECK_نسخہ(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#جے_انت
    {
        "Intel iHD",
        "ubit",
        AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE,
    },
    {
        "VDPAU wrapper",
        "Splitted-Desktop Systems VDPAU backend for VA-API",
        AV_VAAPI_DRIVER_QUIRK_SURFACE_گن,
    },
};

ساكن صحيح vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = عدم;
    VAStatus vas;
    ثابت حرف *vendor_string;
    صحيح err, i, image_گنتی;
    تعداد AVPixelFormat pix_fmt;
    بنانشانی صحيح fourcc;

    image_گنتی = va_Max_عدد_Image_Formats(hwctx->display);
    إذا (image_گنتی <= 0) {
        err = AVERROR(EIO);
        اذهب fail;
    }
    image_list = av_malloc(image_گنتی * حجم(*image_list));
    إذا (!image_list) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_گنتی);
    إذا (vas != VA_حالت_SUCCESS) {
        err = AVERROR(EIO);
        اذهب fail;
    }

    ctx->formats  = av_malloc(image_گنتی * حجم(*ctx->formats));
    إذا (!ctx->formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }
    ctx->nb_formats = 0;
    لكل (i = 0; i < image_گنتی; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        إذا (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } وإلا {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    إذا (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    إذا (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_سیٹ) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } وإلا {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        إذا (vendor_string) {
            لكل (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_جدول); i++) {
                إذا (لڑی_کھوج(vendor_string,
                           vaapi_driver_quirks_جدول[i].میل_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_جدول[i].friendly_name,
                           vaapi_driver_quirks_جدول[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_جدول[i].quirks;
                    اكسر;
                }
            }
            إذا (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_جدول))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } وإلا {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    أرجع 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    أرجع err;
}

ساكن فراغ vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ساكن فراغ vaapi_بفر_free(فراغ *opaque, uint8_t *انکڑے)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)انکڑے;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ساكن AVBufferRef *vaapi_pool_alloc(فراغ *opaque, size_t ناپ)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    إذا (hwfc->initial_pool_ناپ > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_ناپ)
        أرجع عدم;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->چوڑائی, hwfc->اچائی,
                           &surface_id, 1,
                           ctx->گن, ctx->nb_گن);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        أرجع عدم;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_بفر_create((uint8_t*)(uintptr_t)surface_id,
                           حجم(surface_id), &vaapi_بفر_free,
                           hwfc, AV_بفر_FLAG_READONLY);
    إذا (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        أرجع عدم;
    }

    إذا (hwfc->initial_pool_ناپ > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_ناپ);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    أرجع ref;
}

ساكن صحيح vaapi_چوکھٹے_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ثابت VAAPIFormatDescriptor *desc = عدم;
    VAImageFormat *expected_format = عدم;
    AVBufferRef *test_surface = عدم;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    صحيح err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    إذا (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        إذا (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, عدم)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            أرجع AVERROR(EINVAL);
        }
    }

    إذا (!hwfc->pool) {
        إذا (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_گن)) {
            صحيح need_حافظہ_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            صحيح need_pixel_format = 1;
            لكل (i = 0; i < avfc->nb_گن; i++) {
                إذا (avfc->گن[i].type == VASurface_Attrib_حافظہ_Type)
                    need_حافظہ_type  = 0;
                إذا (avfc->گن[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_گن =
                avfc->nb_گن + need_حافظہ_type + need_pixel_format;

            ctx->گن = av_malloc(ctx->nb_گن *
                                        حجم(*ctx->گن));
            إذا (!ctx->گن) {
                err = AVERROR(ENOMEM);
                اذهب fail;
            }

            لكل (i = 0; i < avfc->nb_گن; i++)
                ctx->گن[i] = avfc->گن[i];
            إذا (need_حافظہ_type) {
                ctx->گن[i++] = (VASurfaceAttrib) {
                    .type          = VASurface_Attrib_حافظہ_Type,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .قدر.type    = VAGeneric_قدر_Type_Integer,
                    .قدر.قدر.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            إذا (need_pixel_format) {
                ctx->گن[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .قدر.type    = VAGeneric_قدر_Type_Integer,
                    .قدر.قدر.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_گن);
        } وإلا {
            ctx->گن = عدم;
            ctx->nb_گن = 0;
        }

        ctx->rt_format = desc->rt_format;

        إذا (hwfc->initial_pool_ناپ > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_ناپ *
                                          حجم(*avfc->surface_ids));
            إذا (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                اذهب fail;
            }
        } وإلا {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = عدم;
        }

        ffhwframesctx(hwfc)->pool_اندرونی =
            av_بفر_pool_init2(حجم(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, عدم);
        إذا (!ffhwframesctx(hwfc)->pool_اندرونی) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    إذا (hwfc->pool) {
        test_surface = av_بفر_pool_get(hwfc->pool);
        إذا (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا {
        test_surface = av_بفر_pool_get(ffhwframesctx(hwfc)->pool_اندرونی);
        إذا (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->انکڑے;

    ctx->derive_چلدا = 0;
    إذا (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        إذا (vas == VA_حالت_SUCCESS) {
            إذا (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_چلدا = 1;
            } وإلا {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } وإلا {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } وإلا {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_بفر_unref(&test_surface);
    أرجع 0;

fail:
    av_بفر_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->گن);
    أرجع err;
}

ساكن فراغ vaapi_چوکھٹے_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->گن);
}

ساكن صحيح vaapi_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(hwfc->pool);
    إذا (!چوکھٹا->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکھٹا->انکڑے[3] = چوکھٹا->buf[0]->انکڑے;
    چوکھٹا->format  = AV_PIX_FMT_VAAPI;
    چوکھٹا->چوڑائی   = hwfc->چوڑائی;
    چوکھٹا->اچائی  = hwfc->اچائی;

    أرجع 0;
}

ساكن صحيح vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      تعداد AVHWFrameTransferDirection dir,
                                      تعداد AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    تعداد AVPixelFormat *pix_fmts;
    صحيح i, k, sw_format_دستیاب;

    sw_format_دستیاب = 0;
    لكل (i = 0; i < ctx->nb_formats; i++) {
        إذا (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_دستیاب = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * حجم(*pix_fmts));
    إذا (!pix_fmts)
        أرجع AVERROR(ENOMEM);

    إذا (sw_format_دستیاب) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } وإلا {
        k = 0;
    }
    لكل (i = 0; i < ctx->nb_formats; i++) {
        إذا (ctx->formats[i].pix_fmt == hwfc->sw_format)
            استمر;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    أرجع 0;
}

ساكن فراغ vaapi_unmap_چوکھٹا(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->سروت->انکڑے[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_بفر(hwctx->display, map->image.buf);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    إذا ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_سدھا)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->چوڑائی, hwfc->اچائی,
                         0, 0, hwfc->چوڑائی, hwfc->اچائی);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ساكن صحيح vaapi_map_چوکھٹا(AVHWFramesContext *hwfc,
                           AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ثابت VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    فراغ *پتہ = عدم;
    صحيح err, i;
#إذا VA_CHECK_نسخہ(1, 21, 0)
    uint32_t vaflags = 0;
#جے_انت

    surface_id = (VASurfaceID)(uintptr_t)src->انکڑے[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    إذا (!ctx->derive_چلدا && (flags & AV_HWFRAME_MAP_سدھا)) {
        // Requested direct mapping but it is not possible.
        أرجع AVERROR(EINVAL);
    }
    إذا (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    إذا (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_سدھا)) {
        // Requested direct mapping but the formats do not match.
        أرجع AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    إذا (err < 0) {
        // Requested format is not a valid output format.
        أرجع err;
    }

    map = av_malloc(حجم(*map));
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        اذهب fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    إذا (ctx->derive_چلدا && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_سدھا) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            اذهب fail;
        }
        إذا (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            اذهب fail;
        }
        map->flags |= AV_HWFRAME_MAP_سدھا;
    } وإلا {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->چوڑائی, hwfc->اچائی, &map->image);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            اذهب fail;
        }
        إذا (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->چوڑائی, hwfc->اچائی, map->image.image_id);
            إذا (vas != VA_حالت_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                اذهب fail;
            }
        }
    }

#إذا VA_CHECK_نسخہ(1, 21, 0)
    إذا (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    إذا (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &پتہ, vaflags);
#وإلا
    vas = va_Map_بفر(hwctx->display, map->image.buf, &پتہ);
#جے_انت
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        اذهب fail;
    }

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx,
                                dst, src, &vaapi_unmap_چوکھٹا, map);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    لكل (i = 0; i < map->image.عدد_planes; i++) {
        dst->انکڑے[i] = (uint8_t*)پتہ + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    إذا (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->انکڑے[1], dst->انکڑے[2]);
    }

    أرجع 0;

fail:
    إذا (map) {
        إذا (پتہ)
            va_Unmap_بفر(hwctx->display, map->image.buf);
        إذا (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    أرجع err;
}

ساكن صحيح vaapi_transfer_انکڑے_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (dst->چوڑائی > hwfc->چوڑائی || dst->اچائی > hwfc->اچائی)
        أرجع AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_چوکھٹا(hwfc, map, src, AV_HWFRAME_MAP_READ);
    إذا (err)
        اذهب fail;

    map->چوڑائی  = dst->چوڑائی;
    map->اچائی = dst->اچائی;

    err = av_چوکھٹا_copy(dst, map);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    أرجع err;
}

ساكن صحيح vaapi_transfer_انکڑے_منزل(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (src->چوڑائی > hwfc->چوڑائی || src->اچائی > hwfc->اچائی)
        أرجع AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_چوکھٹا(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    إذا (err)
        اذهب fail;

    map->چوڑائی  = src->چوڑائی;
    map->اچائی = src->اچائی;

    err = av_چوکھٹا_copy(map, src);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    أرجع err;
}

ساكن صحيح vaapi_map_منزل_حافظہ(AVHWFramesContext *hwfc, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    err = vaapi_map_چوکھٹا(hwfc, dst, src, flags);
    إذا (err)
        أرجع err;

    err = av_چوکھٹا_copy_props(dst, src);
    إذا (err)
        أرجع err;

    أرجع 0;
}

#إذا CONFIG_LIBDRM

#تعریف_کرو DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ساكن ثابت بنية {
    uint32_t va_fourcc;
    صحيح   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#جے_تعریف_شدہ DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#جے_انت
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#إذا defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#جے_انت
#إذا defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#جے_انت
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#جے_تعریف_شدہ VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#جے_انت
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#إذا defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#جے_انت
#إذا defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#جے_انت
#إذا defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#جے_انت
#إذا defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#جے_انت
};
#تعریف_رد DRM_MAP

ساكن فراغ vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ساكن صحيح vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحيح flags)
{
#إذا VA_CHECK_نسخہ(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    صحيح use_prime2;
#وإلا
    صحيح k;
#جے_انت
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_چوکھٹے_ctx->انکڑے;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    ثابت VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_حالت_SUCCESS;
    uint32_t va_fourcc;
    صحيح err, i, j;

#إذا !VA_CHECK_نسخہ(1, 1, 0)
    بنانشانی لما بفر_handle;
    VASurfaceAttribExternalBuffers بفر_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurface_Attrib_حافظہ_Type,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .قدر.type    = VAGeneric_قدر_Type_Integer,
            .قدر.قدر.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد,
        },
        {
            .type  = VASurface_Attrib_External_بفر_Descriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .قدر.type    = VAGeneric_قدر_Type_اشارہ_گر,
            .قدر.قدر.p = &بفر_desc,
        }
    };
#جے_انت

    desc = (AVDRMFrameDescriptor*)src->انکڑے[0];

    إذا (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        أرجع AVERROR(EINVAL);
    }

    va_fourcc = 0;
    لكل (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        إذا (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            استمر;
        لكل (j = 0; j < desc->nb_layers; j++) {
            إذا (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                اكسر;
        }
        إذا (j != desc->nb_layers)
            استمر;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        اكسر;
    }
    إذا (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        أرجع AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#إذا VA_CHECK_نسخہ(1, 1, 0)
    use_prime2 = !src_vafc->مفرد_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    إذا (use_prime2) {
        VADRMPRIMESurfaceDescriptor مفرد_desc;
        VASurfaceAttrib مفرد_attrs[2] = {
            {
                .type  = VASurface_Attrib_حافظہ_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .قدر.type    = VAGeneric_قدر_Type_Integer,
                .قدر.قدر.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد_2,
            },
            {
                .type  = VASurface_Attrib_External_بفر_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .قدر.type    = VAGeneric_قدر_Type_اشارہ_گر,
                .قدر.قدر.p = &مفرد_desc,
            }
        };
        مفرد_desc.fourcc = va_fourcc;
        مفرد_desc.چوڑائی = src_fc->چوڑائی;
        مفرد_desc.اچائی = src_fc->اچائی;
        مفرد_desc.عدد_objects = desc->nb_objects;
        لكل (i = 0; i < desc->nb_objects; ++i) {
            مفرد_desc.objects[i].fd = desc->objects[i].fd;
            مفرد_desc.objects[i].ناپ = desc->objects[i].ناپ;
            مفرد_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        مفرد_desc.عدد_layers = desc->nb_layers;
        لكل (i = 0; i < desc->nb_layers; ++i) {
            مفرد_desc.layers[i].drm_format = desc->layers[i].format;
            مفرد_desc.layers[i].عدد_planes = desc->layers[i].nb_planes;
            لكل (j = 0; j < desc->layers[i].nb_planes; ++j) {
                مفرد_desc.layers[i].object_اشاریہ[j] =
                        desc->layers[i].planes[j].object_اشاریہ;
                مفرد_desc.layers[i].وتھ[j] = desc->layers[i].planes[j].وتھ;
                مفرد_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            إذا (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, مفرد_desc.layers[i].pitch[1],
                    مفرد_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, مفرد_desc.layers[i].وتھ[1],
                    مفرد_desc.layers[i].وتھ[2]);
            }
        }

        /*
         * We can query for PRIME_2 support with vaQuerySurfaceAttributes, but that
         * that needs the config_id which we don't have here . Both Intel and
         * Gallium seem to do the correct error checks, so lets just try the
         * PRIME_2 import first.
         */
        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->چوڑائی, src->اچائی, &surface_id, 1,
                               مفرد_attrs, FF_ARRAY_ELEMS(مفرد_attrs));
        إذا (vas != VA_حالت_SUCCESS)
            src_vafc->مفرد_2_import_unsupported = 1;
    }

    إذا (!use_prime2 || vas != VA_حالت_SUCCESS) {
        صحيح k;
        uintptr_t بفر_handle;
        VASurfaceAttribExternalBuffers بفر_desc;
        VASurfaceAttrib بفر_attrs[2] = {
            {
                .type  = VASurface_Attrib_حافظہ_Type,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .قدر.type    = VAGeneric_قدر_Type_Integer,
                .قدر.قدر.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد,
            },
            {
                .type  = VASurface_Attrib_External_بفر_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .قدر.type    = VAGeneric_قدر_Type_اشارہ_گر,
                .قدر.قدر.p = &بفر_desc,
            }
        };

        بفر_handle = desc->objects[0].fd;
        بفر_desc.pixel_format = va_fourcc;
        بفر_desc.چوڑائی        = src_fc->چوڑائی;
        بفر_desc.اچائی       = src_fc->اچائی;
        بفر_desc.انکڑے_ناپ    = desc->objects[0].ناپ;
        بفر_desc.buffers      = &بفر_handle;
        بفر_desc.عدد_buffers  = 1;
        بفر_desc.flags        = 0;

        k = 0;
        لكل (i = 0; i < desc->nb_layers; i++) {
            لكل (j = 0; j < desc->layers[i].nb_planes; j++) {
                بفر_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                بفر_desc.offsets[k] = desc->layers[i].planes[j].وتھ;
                ++k;
            }
        }
        بفر_desc.عدد_planes = k;

        إذا (format_desc->chroma_planes_swapped &&
            بفر_desc.عدد_planes == 3) {
            FFSWAP(uint32_t, بفر_desc.pitches[1], بفر_desc.pitches[2]);
            FFSWAP(uint32_t, بفر_desc.offsets[1], بفر_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->چوڑائی, src->اچائی,
                               &surface_id, 1,
                               بفر_attrs, FF_ARRAY_ELEMS(بفر_attrs));
    }
#وإلا
    بفر_handle = desc->objects[0].fd;
    بفر_desc.pixel_format = va_fourcc;
    بفر_desc.چوڑائی        = src_fc->چوڑائی;
    بفر_desc.اچائی       = src_fc->اچائی;
    بفر_desc.انکڑے_ناپ    = desc->objects[0].ناپ;
    بفر_desc.buffers      = &بفر_handle;
    بفر_desc.عدد_buffers  = 1;
    بفر_desc.flags        = 0;

    k = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        لكل (j = 0; j < desc->layers[i].nb_planes; j++) {
            بفر_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            بفر_desc.offsets[k] = desc->layers[i].planes[j].وتھ;
            ++k;
        }
    }
    بفر_desc.عدد_planes = k;

    إذا (format_desc->chroma_planes_swapped &&
        بفر_desc.عدد_planes == 3) {
        FFSWAP(uint32_t, بفر_desc.pitches[1], بفر_desc.pitches[2]);
        FFSWAP(uint32_t, بفر_desc.offsets[1], بفر_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->چوڑائی, src->اچائی,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#جے_انت
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        أرجع AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (فراغ*)(uintptr_t)surface_id);
    إذا (err < 0)
        أرجع err;

    dst->چوڑائی   = src->چوڑائی;
    dst->اچائی  = src->اچائی;
    dst->انکڑے[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    أرجع 0;
}

#إذا VA_CHECK_نسخہ(1, 1, 0)
ساكن فراغ vaapi_unmap_منزل_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    صحيح i;

    لكل (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ساكن صحيح vaapi_map_منزل_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحيح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = عدم;
    uint32_t export_flags;
    صحيح err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->انکڑے[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    إذا (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            أرجع AVERROR(EIO);
        }
    }

    إذا (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد_2,
                                export_flags, &va_desc);
    إذا (vas != VA_حالت_SUCCESS) {
        إذا (vas == VA_حالت_ERROR_UNIMPLEMENTED)
            أرجع AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        أرجع AVERROR(EIO);
    }

    drm_desc = av_mallocz(حجم(*drm_desc));
    إذا (!drm_desc) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.عدد_objects;
    لكل (i = 0; i < va_desc.عدد_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].ناپ = va_desc.objects[i].ناپ;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.عدد_layers;
    لكل (i = 0; i < va_desc.عدد_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].عدد_planes;
        لكل (j = 0; j < va_desc.layers[i].عدد_planes; j++) {
            drm_desc->layers[i].planes[j].object_اشاریہ =
                va_desc.layers[i].object_اشاریہ[j];
            drm_desc->layers[i].planes[j].وتھ =
                va_desc.layers[i].وتھ[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                &vaapi_unmap_منزل_drm_esh, drm_desc);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی   = src->چوڑائی;
    dst->اچائی  = src->اچائی;
    dst->انکڑے[0] = (uint8_t*)drm_desc;

    أرجع 0;

fail:
    لكل (i = 0; i < va_desc.عدد_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    أرجع err;
}
#جے_انت

#إذا VA_CHECK_نسخہ(0, 36, 0)
تعريفنوع بنية VAAPIDRMImage_بفر_Mapping {
    VAImage      image;
    VABufferInfo بفر_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_بفر_Mapping;

ساكن فراغ vaapi_unmap_منزل_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_بفر_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->سروت->انکڑے[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_بفر_Handle(hwctx->display, mapping->image.buf);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ساكن صحيح vaapi_map_منزل_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحيح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_بفر_Mapping *mapping = عدم;
    VASurfaceID surface_id;
    VAStatus vas;
    صحيح err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->انکڑے[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(حجم(*mapping));
    إذا (!mapping)
        أرجع AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        اذهب fail;
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        إذا (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            اكسر;
    }
    إذا (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        اذهب fail_derived;
    }

    mapping->بفر_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    إذا (mapping->drm_desc.nb_layers > 1) {
        إذا (mapping->drm_desc.nb_layers != mapping->image.عدد_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.عدد_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            اذهب fail_derived;
        }

        لكل(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_اشاریہ = 0,
                    .وتھ       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } وإلا {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.عدد_planes;
        لكل (p = 0; p < mapping->image.عدد_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_اشاریہ = 0,
                .وتھ       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_بفر_Handle(hwctx->display, mapping->image.buf,
                                &mapping->بفر_info);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        اذهب fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->بفر_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->بفر_info.handle,
        .ناپ = mapping->image.انکڑے_ناپ,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx,
                                dst, src, &vaapi_unmap_منزل_drm_abh,
                                mapping);
    إذا (err < 0)
        اذهب fail_mapped;

    dst->انکڑے[0] = (uint8_t*)&mapping->drm_desc;
    dst->چوڑائی   = src->چوڑائی;
    dst->اچائی  = src->اچائی;

    أرجع 0;

fail_mapped:
    va_Release_بفر_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    أرجع err;
}
#جے_انت

ساكن صحيح vaapi_map_منزل_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحيح flags)
{
#إذا VA_CHECK_نسخہ(1, 1, 0)
    صحيح err;
    err = vaapi_map_منزل_drm_esh(hwfc, dst, src, flags);
    إذا (err != AVERROR(ENOSYS))
        أرجع err;
#جے_انت
#إذا VA_CHECK_نسخہ(0, 36, 0)
    أرجع vaapi_map_منزل_drm_abh(hwfc, dst, src, flags);
#جے_انت
    أرجع AVERROR(ENOSYS);
}

#جے_انت /* CONFIG_LIBDRM */

ساكن صحيح vaapi_map_منزل(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحيح flags)
{
    بدل (src->format) {
#إذا CONFIG_LIBDRM
    حالة AV_PIX_FMT_DRM_مفرد:
        أرجع vaapi_map_from_drm(hwfc, dst, src, flags);
#جے_انت
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }
}

ساكن صحيح vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ثابت AVFrame *src, صحيح flags)
{
    بدل (dst->format) {
#إذا CONFIG_LIBDRM
    حالة AV_PIX_FMT_DRM_مفرد:
        أرجع vaapi_map_منزل_drm(hwfc, dst, src, flags);
#جے_انت
    افتراضي:
        أرجع vaapi_map_منزل_حافظہ(hwfc, dst, src, flags);
    }
}

ساكن فراغ vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    إذا (hwctx->display)
        vaTerminate(hwctx->display);

#إذا HAVE_VAAPI_X11
    إذا (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#جے_انت

#إذا HAVE_VAAPI_DRM
    إذا (priv->drm_fd >= 0)
        close(priv->drm_fd);
#جے_انت

    av_freep(&priv);
}

#إذا CONFIG_VAAPI_1
ساكن فراغ vaapi_device_log_error(فراغ *context, ثابت حرف *سنیہا)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", سنیہا);
}

ساكن فراغ vaapi_device_log_info(فراغ *context, ثابت حرف *سنیہا)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", سنیہا);
}
#جے_انت

ساكن صحيح vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    صحيح major, minor;
    VAStatus vas;

#إذا CONFIG_VAAPI_1
    va_سیٹ_Error_Callback(display, &vaapi_device_log_error, ctx);
    va_سیٹ_Info_Callback (display, &vaapi_device_log_info,  ctx);
#جے_انت

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    إذا (vas != VA_حالت_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        أرجع AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    أرجع 0;
}

ساكن صحيح vaapi_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحيح flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = عدم;
    ثابت AVDictionary_اندراج *ent;
    صحيح try_drm, try_x11, try_win32, try_all av_بن_ورتیا;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->حرر        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", عدم, 0);
    إذا (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        إذا (!strcmp(ent->قدر, "drm")) {
            try_drm = 1;
        } وإلا إذا (!strcmp(ent->قدر, "x11")) {
            try_x11 = 1;
        } وإلا إذا (!strcmp(ent->قدر, "win32")) {
            try_win32 = 1;
        } وإلا {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->قدر);
            أرجع AVERROR(EINVAL);
        }
    } وإلا {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#إذا HAVE_VAAPI_DRM
    طالما (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        صحيح loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        إذا (device) {
            priv->drm_fd = open(device, O_RDWR);
            إذا (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                اكسر;
            }
        } وإلا {
            حرف رستہ[64];
            صحيح n, max_devices = 8;
#إذا CONFIG_LIBDRM
            drm_نسخہ *info;
            ثابت AVDictionary_اندراج *kernel_driver;
            ثابت AVDictionary_اندراج *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", عدم, 0);
            vendor_id = av_dict_get(opts, "vendor_id", عدم, 0);
#جے_انت
            لكل (n = 0; n < max_devices; n++) {
                snprintf(رستہ, حجم(رستہ),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(رستہ, O_RDWR);
                إذا (priv->drm_fd < 0) {
                    إذا (errno == ENOENT) {
                        إذا (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", رستہ);
                            استمر;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } وإلا
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    اكسر;
                }
#إذا CONFIG_LIBDRM
                info = drm_Get_نسخہ(priv->drm_fd);
                إذا (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    استمر;
                }
                إذا (kernel_driver) {
                    إذا (strcmp(kernel_driver->قدر, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drm_Free_نسخہ(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        استمر;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drm_Free_نسخہ(info);
                    اكسر;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } وإلا إذا (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drm_Free_نسخہ(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    استمر;
                } وإلا إذا (vendor_id) {
                    drmDevicePtr device;
                    حرف drm_vendor[8];
                    إذا (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_نسخہ(info);
                        استمر;
                    }

                    snprintf(drm_vendor, حجم(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    إذا (strcmp(vendor_id->قدر, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->قدر);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_نسخہ(info);
                        استمر;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->قدر);
                    drmFreeDevice(&device);
                    drm_Free_نسخہ(info);
                    اكسر;
                }
                drm_Free_نسخہ(info);
#جے_انت
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                اكسر;
            }
            إذا (n >= max_devices)
                اكسر;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        إذا (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            أرجع AVERROR_EXTERNAL;
        }
        اكسر;
    }
#جے_انت

#إذا HAVE_VAAPI_X11
    إذا (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        إذا (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } وإلا {
            display = vaGetDisplay(priv->x11_display);
            إذا (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                أرجع AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#جے_انت

#إذا HAVE_VAAPI_WIN32
    إذا (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        إذا (!device) {
            display = vaGetDisplayWin32(عدم);
        } وإلا {
            IDXGIFactory2 *pDXGIFactory = عدم;
            IDXGIAdapter *pAdapter = عدم;
#إذا !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            إذا (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                أرجع AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            إذا (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                أرجع AVERROR_UNKNOWN;
            }
#وإلا
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#جے_انت
            إذا (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (فراغ **)&pDXGIFactory))) {
                صحيح adapter = atoi(device);
                إذا (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    إذا (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.کم_Part,
                              desc.AdapterLuid.بلند_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#إذا !HAVE_UWP
            dlclose(dxgi);
#جے_انت
        }

        إذا (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            أرجع AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#جے_انت

    إذا (!display) {
        إذا (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        وإلا
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        أرجع AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", عدم, 0);
    إذا (ent) {
#إذا VA_CHECK_نسخہ(0, 38, 0)
        VAStatus vas;
        vas = va_سیٹ_Driver_Name(display, ent->قدر);
        إذا (vas != VA_حالت_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->قدر, vas, vaErrorStr(vas));
            vaTerminate(display);
            أرجع AVERROR_EXTERNAL;
        }
#وإلا
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#جے_انت
    }

    أرجع vaapi_device_connect(ctx, display);
}

ساكن صحيح vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, صحيح flags)
{
#إذا HAVE_VAAPI_DRM
    إذا (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        صحيح fd;

        إذا (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            أرجع AVERROR(EINVAL);
        }

#إذا CONFIG_LIBDRM
        {
            صحيح گرہ_type = drm_Get_گرہ_Type_From_Fd(src_hwctx->fd);
            حرف *render_گرہ;
            إذا (گرہ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                أرجع AVERROR(EINVAL);
            }
            إذا (گرہ_type == DRM_گرہ_RENDER) {
                fd = src_hwctx->fd;
            } وإلا {
                render_گرہ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                إذا (!render_گرہ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } وإلا {
                    fd = open(render_گرہ, O_RDWR);
                    إذا (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } وإلا {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_گرہ);
                    }
                    حرر(render_گرہ);
                }
            }
        }
#وإلا
        fd = src_hwctx->fd;
#جے_انت

        priv = av_mallocz(حجم(*priv));
        إذا (!priv) {
            إذا (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            أرجع AVERROR(ENOMEM);
        }

        إذا (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } وإلا {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->حرر        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        إذا (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            أرجع AVERROR(EIO);
        }

        أرجع vaapi_device_connect(ctx, display);
    }
#جے_انت
    أرجع AVERROR(ENOSYS);
}

ثابت HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_ناپ      = حجم(VAAPIDeviceContext),
    .device_hwconfig_ناپ   = حجم(AVVAAPIHWConfig),
    .چوکھٹے_hwctx_ناپ      = حجم(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .چوکھٹے_get_constraints = &vaapi_چوکھٹے_get_constraints,
    .چوکھٹے_init            = &vaapi_چوکھٹے_init,
    .چوکھٹے_uninit          = &vaapi_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = &vaapi_get_بفر,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_انکڑے_منزل       = &vaapi_transfer_انکڑے_منزل,
    .transfer_انکڑے_from     = &vaapi_transfer_انکڑے_from,
    .map_منزل                 = &vaapi_map_منزل,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
