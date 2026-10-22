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

#شامل "config.h"

#اگر HAVE_VAAPI_WIN32
#   include <windows.h>
#تعریف_کرو COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
قسمتعریف HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, خالی **ppFactory);
#اگر_ختم
#اگر HAVE_VAAPI_X11
#   include <va/va_x11.h>
#اگر_ختم
#اگر HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#اگر_ختم

#اگر CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#اگر_ختم

#شامل <fcntl.h>
#اگر HAVE_UNISTD_H
#   include <unistd.h>
#اگر_ختم


#شامل "avassert.h"
#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_drm.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_vaapi.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"


قسمتعریف ساخت VAAPIDevicePriv {
#اگر HAVE_VAAPI_X11
    Display *x11_display;
#اگر_ختم

    صحیح drm_fd;
} VAAPIDevicePriv;

قسمتعریف ساخت VAAPISurfaceFormat {
    شمار AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    غیرعلامتی صحیح fourcc;
} VAAPISurfaceFormat;

قسمتعریف ساخت VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    صحیح              nb_formats;
} VAAPIDeviceContext;

قسمتعریف ساخت VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *اوصاف;
    صحیح           nb_اوصاف;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    غیرعلامتی صحیح rt_format;
    // Whether vaDeriveImage works.
    صحیح derive_چلتا;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    صحیح مفرد_2_import_unsupported;
} VAAPIFramesContext;

قسمتعریف ساخت VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    صحیح flags;
} VAAPIMapping;

قسمتعریف ساخت VAAPIFormat {
    غیرعلامتی صحیح fourcc;
    غیرعلامتی صحیح rt_format;
    شمار AVPixelFormat pix_fmt;
    صحیح chroma_planes_swapped;
} VAAPIFormatDescriptor;

#تعریف_کرو MAP(va, rt, av, تبادلہ_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        تبادلہ_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ساکن ثابت VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#اگر_تعریف_شدہ VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#اگر_ختم
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#اگر_تعریف_شدہ VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#اگر_ختم
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#اگر_تعریف_شدہ VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#اگر_ختم
#اگر_تعریف_شدہ VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#اگر_ختم
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#اگر_تعریف_شدہ VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#اگر_ختم
    MAP(Y800, YUV400,  GRAY8,   0),
#اگر_تعریف_شدہ VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#اگر_ختم
#اگر_تعریف_شدہ VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#اگر_ختم
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#اگر_تعریف_شدہ VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#اگر_ختم
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#اگر_تعریف_شدہ VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#اگر_ختم
#اگر_تعریف_شدہ VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#اگر_ختم
#اگر_تعریف_شدہ VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#اگر_ختم
};
#تعریف_منسوخ MAP

ساکن ثابت VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(غیرعلامتی صحیح fourcc)
{
    صحیح i;
    برائے (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        اگر (vaapi_format_map[i].fourcc == fourcc)
            واپس &vaapi_format_map[i];
    واپس تہی;
}

ساکن ثابت VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(شمار AVPixelFormat pix_fmt, ثابت VAAPIFormatDescriptor *پچھلا)
{
    ثابت VAAPIFormatDescriptor *انتہا = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    اگر (!پچھلا)
        پچھلا = vaapi_format_map;
    ورنہ
        پچھلا++;

    برائے (; پچھلا < انتہا; پچھلا++)
        اگر (پچھلا->pix_fmt == pix_fmt)
            واپس پچھلا;
    واپس تہی;
}

ساکن شمار AVPixelFormat vaapi_pix_fmt_from_fourcc(غیرعلامتی صحیح fourcc)
{
    ثابت VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    اگر (desc)
        واپس desc->pix_fmt;
    ورنہ
        واپس AV_PIX_FMT_NONE;
}

ساکن صحیح vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  شمار AVPixelFormat pix_fmt,
                                  ثابت VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ثابت VAAPIFormatDescriptor *desc = تہی;
    صحیح i;

    جب ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        برائے (i = 0; i < ctx->nb_formats; i++) {
            اگر (ctx->formats[i].fourcc == desc->fourcc) {
                اگر (_desc)
                    *_desc = desc;
                اگر (image_format)
                    *image_format = &ctx->formats[i].image_format;
                واپس 0;
            }
        }
    }

    واپس AVERROR(ENOSYS);
}

ساکن صحیح vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  شمار AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    اگر (!image_format)
        واپس AVERROR(EINVAL);
    واپس vaapi_get_img_desc_and_format(hwdev, pix_fmt, تہی, image_format);
}

ساکن صحیح vaapi_چوکھٹے_get_constraints(AVHWDeviceContext *hwdev,
                                        ثابت خالی *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ثابت AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = تہی;
    VAStatus vas;
    شمار AVPixelFormat pix_fmt;
    غیرعلامتی صحیح fourcc;
    صحیح err, i, j, attr_گنتی, pix_fmt_گنتی;

    اگر (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_اوصاف)) {
        attr_گنتی = 0;
        vas = va_Query_Surface_اوصاف(hwctx->display, config->config_id,
                                       0, &attr_گنتی);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            جاؤ fail;
        }

        attr_list = av_malloc(attr_گنتی * حجم(*attr_list));
        اگر (!attr_list) {
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }

        vas = va_Query_Surface_اوصاف(hwctx->display, config->config_id,
                                       attr_list, &attr_گنتی);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            جاؤ fail;
        }

        pix_fmt_گنتی = 0;
        برائے (i = 0; i < attr_گنتی; i++) {
            انتخاب (attr_list[i].type) {
            حالت VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].قدر.قدر.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                اگر (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_گنتی;
                } ورنہ {
                    // Something unsupported - ignore.
                }
                توڑو;
            حالت VASurface_Attrib_Min_چوڑائی:
                constraints->min_چوڑائی  = attr_list[i].قدر.قدر.i;
                توڑو;
            حالت VASurface_Attrib_Min_اونچائی:
                constraints->min_اونچائی = attr_list[i].قدر.قدر.i;
                توڑو;
            حالت VASurface_Attrib_Max_چوڑائی:
                constraints->max_چوڑائی  = attr_list[i].قدر.قدر.i;
                توڑو;
            حالت VASurface_Attrib_Max_اونچائی:
                constraints->max_اونچائی = attr_list[i].قدر.قدر.i;
                توڑو;
            }
        }
        اگر (pix_fmt_گنتی == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = تہی;
        } ورنہ {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_گنتی + 1,
                                                            حجم(pix_fmt));
            اگر (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                جاؤ fail;
            }

            برائے (i = j = 0; i < attr_گنتی; i++) {
                صحیح k;

                اگر (attr_list[i].type != VASurfaceAttribPixelFormat)
                    جاری;
                fourcc = attr_list[i].قدر.قدر.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                اگر (pix_fmt == AV_PIX_FMT_NONE)
                    جاری;

                برائے (k = 0; k < j; k++) {
                    اگر (constraints->valid_sw_formats[k] == pix_fmt)
                        توڑو;
                }

                اگر (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } ورنہ {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        حجم(pix_fmt));
        اگر (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
        برائے (i = j = 0; i < ctx->nb_formats; i++) {
            صحیح k;

            برائے (k = 0; k < j; k++) {
                اگر (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    توڑو;
            }

            اگر (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, حجم(pix_fmt));
    اگر (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    واپس err;
}

ساکن ثابت ساخت {
    ثابت حرف *friendly_name;
    ثابت حرف *مطابقت_string;
    غیرعلامتی صحیح quirks;
} vaapi_driver_quirks_جدول[] = {
#اگر !VA_CHECK_نسخہ(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#اگر_ختم
    {
        "Intel iHD",
        "ubit",
        AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE,
    },
    {
        "VDPAU wrapper",
        "Splitted-Desktop Systems VDPAU backend for VA-API",
        AV_VAAPI_DRIVER_QUIRK_SURFACE_اوصاف,
    },
};

ساکن صحیح vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = تہی;
    VAStatus vas;
    ثابت حرف *vendor_string;
    صحیح err, i, image_گنتی;
    شمار AVPixelFormat pix_fmt;
    غیرعلامتی صحیح fourcc;

    image_گنتی = va_Max_عدد_Image_Formats(hwctx->display);
    اگر (image_گنتی <= 0) {
        err = AVERROR(EIO);
        جاؤ fail;
    }
    image_list = av_malloc(image_گنتی * حجم(*image_list));
    اگر (!image_list) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_گنتی);
    اگر (vas != VA_حالت_SUCCESS) {
        err = AVERROR(EIO);
        جاؤ fail;
    }

    ctx->formats  = av_malloc(image_گنتی * حجم(*ctx->formats));
    اگر (!ctx->formats) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }
    ctx->nb_formats = 0;
    برائے (i = 0; i < image_گنتی; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        اگر (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } ورنہ {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    اگر (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    اگر (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_سیٹ) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } ورنہ {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        اگر (vendor_string) {
            برائے (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_جدول); i++) {
                اگر (لڑی_تلاش(vendor_string,
                           vaapi_driver_quirks_جدول[i].مطابقت_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_جدول[i].friendly_name,
                           vaapi_driver_quirks_جدول[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_جدول[i].quirks;
                    توڑو;
                }
            }
            اگر (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_جدول))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } ورنہ {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    واپس 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    واپس err;
}

ساکن خالی vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ساکن خالی vaapi_بفر_free(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)ڈیٹا;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ساکن AVBufferRef *vaapi_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    اگر (hwfc->initial_pool_سائز > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_سائز)
        واپس تہی;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->چوڑائی, hwfc->اونچائی,
                           &surface_id, 1,
                           ctx->اوصاف, ctx->nb_اوصاف);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        واپس تہی;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_بفر_create((uint8_t*)(uintptr_t)surface_id,
                           حجم(surface_id), &vaapi_بفر_free,
                           hwfc, AV_بفر_FLAG_READONLY);
    اگر (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        واپس تہی;
    }

    اگر (hwfc->initial_pool_سائز > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_سائز);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    واپس ref;
}

ساکن صحیح vaapi_چوکھٹے_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ثابت VAAPIFormatDescriptor *desc = تہی;
    VAImageFormat *expected_format = تہی;
    AVBufferRef *test_surface = تہی;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    صحیح err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    اگر (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        اگر (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, تہی)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            واپس AVERROR(EINVAL);
        }
    }

    اگر (!hwfc->pool) {
        اگر (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_اوصاف)) {
            صحیح need_حافظہ_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            صحیح need_pixel_format = 1;
            برائے (i = 0; i < avfc->nb_اوصاف; i++) {
                اگر (avfc->اوصاف[i].type == VASurface_Attrib_حافظہ_Type)
                    need_حافظہ_type  = 0;
                اگر (avfc->اوصاف[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_اوصاف =
                avfc->nb_اوصاف + need_حافظہ_type + need_pixel_format;

            ctx->اوصاف = av_malloc(ctx->nb_اوصاف *
                                        حجم(*ctx->اوصاف));
            اگر (!ctx->اوصاف) {
                err = AVERROR(ENOMEM);
                جاؤ fail;
            }

            برائے (i = 0; i < avfc->nb_اوصاف; i++)
                ctx->اوصاف[i] = avfc->اوصاف[i];
            اگر (need_حافظہ_type) {
                ctx->اوصاف[i++] = (VASurfaceAttrib) {
                    .type          = VASurface_Attrib_حافظہ_Type,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .قدر.type    = VAGeneric_قدر_Type_Integer,
                    .قدر.قدر.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            اگر (need_pixel_format) {
                ctx->اوصاف[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .قدر.type    = VAGeneric_قدر_Type_Integer,
                    .قدر.قدر.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_اوصاف);
        } ورنہ {
            ctx->اوصاف = تہی;
            ctx->nb_اوصاف = 0;
        }

        ctx->rt_format = desc->rt_format;

        اگر (hwfc->initial_pool_سائز > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_سائز *
                                          حجم(*avfc->surface_ids));
            اگر (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                جاؤ fail;
            }
        } ورنہ {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = تہی;
        }

        ffhwframesctx(hwfc)->pool_اندرونی =
            av_بفر_pool_init2(حجم(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, تہی);
        اگر (!ffhwframesctx(hwfc)->pool_اندرونی) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    اگر (hwfc->pool) {
        test_surface = av_بفر_pool_get(hwfc->pool);
        اگر (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
    } ورنہ {
        test_surface = av_بفر_pool_get(ffhwframesctx(hwfc)->pool_اندرونی);
        اگر (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->ڈیٹا;

    ctx->derive_چلتا = 0;
    اگر (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        اگر (vas == VA_حالت_SUCCESS) {
            اگر (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_چلتا = 1;
            } ورنہ {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } ورنہ {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } ورنہ {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_بفر_unref(&test_surface);
    واپس 0;

fail:
    av_بفر_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->اوصاف);
    واپس err;
}

ساکن خالی vaapi_چوکھٹے_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->اوصاف);
}

ساکن صحیح vaapi_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(hwfc->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[3] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_VAAPI;
    چوکھٹا->چوڑائی   = hwfc->چوڑائی;
    چوکھٹا->اونچائی  = hwfc->اونچائی;

    واپس 0;
}

ساکن صحیح vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      شمار AVHWFrameTransferDirection dir,
                                      شمار AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    شمار AVPixelFormat *pix_fmts;
    صحیح i, k, sw_format_دستیاب;

    sw_format_دستیاب = 0;
    برائے (i = 0; i < ctx->nb_formats; i++) {
        اگر (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_دستیاب = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * حجم(*pix_fmts));
    اگر (!pix_fmts)
        واپس AVERROR(ENOMEM);

    اگر (sw_format_دستیاب) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } ورنہ {
        k = 0;
    }
    برائے (i = 0; i < ctx->nb_formats; i++) {
        اگر (ctx->formats[i].pix_fmt == hwfc->sw_format)
            جاری;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    واپس 0;
}

ساکن خالی vaapi_unmap_چوکھٹا(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ماخذ->ڈیٹا[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_بفر(hwctx->display, map->image.buf);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    اگر ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_براہ_راست)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->چوڑائی, hwfc->اونچائی,
                         0, 0, hwfc->چوڑائی, hwfc->اونچائی);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ساکن صحیح vaapi_map_چوکھٹا(AVHWFramesContext *hwfc,
                           AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ثابت VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    خالی *پتہ = تہی;
    صحیح err, i;
#اگر VA_CHECK_نسخہ(1, 21, 0)
    uint32_t vaflags = 0;
#اگر_ختم

    surface_id = (VASurfaceID)(uintptr_t)src->ڈیٹا[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    اگر (!ctx->derive_چلتا && (flags & AV_HWFRAME_MAP_براہ_راست)) {
        // Requested direct mapping but it is not possible.
        واپس AVERROR(EINVAL);
    }
    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    اگر (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_براہ_راست)) {
        // Requested direct mapping but the formats do not match.
        واپس AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    اگر (err < 0) {
        // Requested format is not a valid output format.
        واپس err;
    }

    map = av_malloc(حجم(*map));
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        جاؤ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    اگر (ctx->derive_چلتا && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_براہ_راست) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            جاؤ fail;
        }
        اگر (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            جاؤ fail;
        }
        map->flags |= AV_HWFRAME_MAP_براہ_راست;
    } ورنہ {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->چوڑائی, hwfc->اونچائی, &map->image);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            جاؤ fail;
        }
        اگر (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->چوڑائی, hwfc->اونچائی, map->image.image_id);
            اگر (vas != VA_حالت_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                جاؤ fail;
            }
        }
    }

#اگر VA_CHECK_نسخہ(1, 21, 0)
    اگر (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    اگر (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &پتہ, vaflags);
#ورنہ
    vas = va_Map_بفر(hwctx->display, map->image.buf, &پتہ);
#اگر_ختم
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        جاؤ fail;
    }

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx,
                                dst, src, &vaapi_unmap_چوکھٹا, map);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    برائے (i = 0; i < map->image.عدد_planes; i++) {
        dst->ڈیٹا[i] = (uint8_t*)پتہ + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    اگر (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->ڈیٹا[1], dst->ڈیٹا[2]);
    }

    واپس 0;

fail:
    اگر (map) {
        اگر (پتہ)
            va_Unmap_بفر(hwctx->display, map->image.buf);
        اگر (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    واپس err;
}

ساکن صحیح vaapi_transfer_ڈیٹا_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->چوڑائی > hwfc->چوڑائی || dst->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_چوکھٹا(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = dst->چوڑائی;
    map->اونچائی = dst->اونچائی;

    err = av_چوکھٹا_copy(dst, map);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح vaapi_transfer_ڈیٹا_مقصد(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->چوڑائی > hwfc->چوڑائی || src->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_چوکھٹا(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = src->چوڑائی;
    map->اونچائی = src->اونچائی;

    err = av_چوکھٹا_copy(map, src);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح vaapi_map_مقصد_حافظہ(AVHWFramesContext *hwfc, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    err = vaapi_map_چوکھٹا(hwfc, dst, src, flags);
    اگر (err)
        واپس err;

    err = av_چوکھٹا_copy_props(dst, src);
    اگر (err)
        واپس err;

    واپس 0;
}

#اگر CONFIG_LIBDRM

#تعریف_کرو DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ساکن ثابت ساخت {
    uint32_t va_fourcc;
    صحیح   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#اگر_تعریف_شدہ DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#اگر_ختم
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#اگر defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#اگر_ختم
#اگر defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#اگر_ختم
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#اگر_تعریف_شدہ VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#اگر_ختم
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#اگر defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#اگر_ختم
#اگر defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#اگر_ختم
#اگر defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#اگر_ختم
#اگر defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#اگر_ختم
};
#تعریف_منسوخ DRM_MAP

ساکن خالی vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ساکن صحیح vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحیح flags)
{
#اگر VA_CHECK_نسخہ(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    صحیح use_prime2;
#ورنہ
    صحیح k;
#اگر_ختم
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_چوکھٹے_ctx->ڈیٹا;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    ثابت VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_حالت_SUCCESS;
    uint32_t va_fourcc;
    صحیح err, i, j;

#اگر !VA_CHECK_نسخہ(1, 1, 0)
    غیرعلامتی طویل بفر_handle;
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
#اگر_ختم

    desc = (AVDRMFrameDescriptor*)src->ڈیٹا[0];

    اگر (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        واپس AVERROR(EINVAL);
    }

    va_fourcc = 0;
    برائے (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        اگر (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            جاری;
        برائے (j = 0; j < desc->nb_layers; j++) {
            اگر (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                توڑو;
        }
        اگر (j != desc->nb_layers)
            جاری;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        توڑو;
    }
    اگر (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        واپس AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#اگر VA_CHECK_نسخہ(1, 1, 0)
    use_prime2 = !src_vafc->مفرد_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    اگر (use_prime2) {
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
        مفرد_desc.اونچائی = src_fc->اونچائی;
        مفرد_desc.عدد_objects = desc->nb_objects;
        برائے (i = 0; i < desc->nb_objects; ++i) {
            مفرد_desc.objects[i].fd = desc->objects[i].fd;
            مفرد_desc.objects[i].سائز = desc->objects[i].سائز;
            مفرد_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        مفرد_desc.عدد_layers = desc->nb_layers;
        برائے (i = 0; i < desc->nb_layers; ++i) {
            مفرد_desc.layers[i].drm_format = desc->layers[i].format;
            مفرد_desc.layers[i].عدد_planes = desc->layers[i].nb_planes;
            برائے (j = 0; j < desc->layers[i].nb_planes; ++j) {
                مفرد_desc.layers[i].object_اشاریہ[j] =
                        desc->layers[i].planes[j].object_اشاریہ;
                مفرد_desc.layers[i].انحراف[j] = desc->layers[i].planes[j].انحراف;
                مفرد_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            اگر (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, مفرد_desc.layers[i].pitch[1],
                    مفرد_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, مفرد_desc.layers[i].انحراف[1],
                    مفرد_desc.layers[i].انحراف[2]);
            }
        }

        /*
         * We can query for PRIME_2 support with vaQuerySurfaceAttributes, but that
         * that needs the config_id which we don't have here . Both Intel and
         * Gallium seem to do the correct error checks, so lets just try the
         * PRIME_2 import first.
         */
        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->چوڑائی, src->اونچائی, &surface_id, 1,
                               مفرد_attrs, FF_ARRAY_ELEMS(مفرد_attrs));
        اگر (vas != VA_حالت_SUCCESS)
            src_vafc->مفرد_2_import_unsupported = 1;
    }

    اگر (!use_prime2 || vas != VA_حالت_SUCCESS) {
        صحیح k;
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
        بفر_desc.اونچائی       = src_fc->اونچائی;
        بفر_desc.ڈیٹا_سائز    = desc->objects[0].سائز;
        بفر_desc.buffers      = &بفر_handle;
        بفر_desc.عدد_buffers  = 1;
        بفر_desc.flags        = 0;

        k = 0;
        برائے (i = 0; i < desc->nb_layers; i++) {
            برائے (j = 0; j < desc->layers[i].nb_planes; j++) {
                بفر_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                بفر_desc.offsets[k] = desc->layers[i].planes[j].انحراف;
                ++k;
            }
        }
        بفر_desc.عدد_planes = k;

        اگر (format_desc->chroma_planes_swapped &&
            بفر_desc.عدد_planes == 3) {
            FFSWAP(uint32_t, بفر_desc.pitches[1], بفر_desc.pitches[2]);
            FFSWAP(uint32_t, بفر_desc.offsets[1], بفر_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->چوڑائی, src->اونچائی,
                               &surface_id, 1,
                               بفر_attrs, FF_ARRAY_ELEMS(بفر_attrs));
    }
#ورنہ
    بفر_handle = desc->objects[0].fd;
    بفر_desc.pixel_format = va_fourcc;
    بفر_desc.چوڑائی        = src_fc->چوڑائی;
    بفر_desc.اونچائی       = src_fc->اونچائی;
    بفر_desc.ڈیٹا_سائز    = desc->objects[0].سائز;
    بفر_desc.buffers      = &بفر_handle;
    بفر_desc.عدد_buffers  = 1;
    بفر_desc.flags        = 0;

    k = 0;
    برائے (i = 0; i < desc->nb_layers; i++) {
        برائے (j = 0; j < desc->layers[i].nb_planes; j++) {
            بفر_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            بفر_desc.offsets[k] = desc->layers[i].planes[j].انحراف;
            ++k;
        }
    }
    بفر_desc.عدد_planes = k;

    اگر (format_desc->chroma_planes_swapped &&
        بفر_desc.عدد_planes == 3) {
        FFSWAP(uint32_t, بفر_desc.pitches[1], بفر_desc.pitches[2]);
        FFSWAP(uint32_t, بفر_desc.offsets[1], بفر_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->چوڑائی, src->اونچائی,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#اگر_ختم
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        واپس AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (خالی*)(uintptr_t)surface_id);
    اگر (err < 0)
        واپس err;

    dst->چوڑائی   = src->چوڑائی;
    dst->اونچائی  = src->اونچائی;
    dst->ڈیٹا[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    واپس 0;
}

#اگر VA_CHECK_نسخہ(1, 1, 0)
ساکن خالی vaapi_unmap_مقصد_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    صحیح i;

    برائے (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ساکن صحیح vaapi_map_مقصد_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = تہی;
    uint32_t export_flags;
    صحیح err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->ڈیٹا[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    اگر (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            واپس AVERROR(EIO);
        }
    }

    اگر (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد_2,
                                export_flags, &va_desc);
    اگر (vas != VA_حالت_SUCCESS) {
        اگر (vas == VA_حالت_ERROR_UNIMPLEMENTED)
            واپس AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        واپس AVERROR(EIO);
    }

    drm_desc = av_mallocz(حجم(*drm_desc));
    اگر (!drm_desc) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.عدد_objects;
    برائے (i = 0; i < va_desc.عدد_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].سائز = va_desc.objects[i].سائز;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.عدد_layers;
    برائے (i = 0; i < va_desc.عدد_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].عدد_planes;
        برائے (j = 0; j < va_desc.layers[i].عدد_planes; j++) {
            drm_desc->layers[i].planes[j].object_اشاریہ =
                va_desc.layers[i].object_اشاریہ[j];
            drm_desc->layers[i].planes[j].انحراف =
                va_desc.layers[i].انحراف[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                &vaapi_unmap_مقصد_drm_esh, drm_desc);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی   = src->چوڑائی;
    dst->اونچائی  = src->اونچائی;
    dst->ڈیٹا[0] = (uint8_t*)drm_desc;

    واپس 0;

fail:
    برائے (i = 0; i < va_desc.عدد_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    واپس err;
}
#اگر_ختم

#اگر VA_CHECK_نسخہ(0, 36, 0)
قسمتعریف ساخت VAAPIDRMImage_بفر_Mapping {
    VAImage      image;
    VABufferInfo بفر_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_بفر_Mapping;

ساکن خالی vaapi_unmap_مقصد_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_بفر_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->ماخذ->ڈیٹا[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_بفر_Handle(hwctx->display, mapping->image.buf);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ساکن صحیح vaapi_map_مقصد_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_بفر_Mapping *mapping = تہی;
    VASurfaceID surface_id;
    VAStatus vas;
    صحیح err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->ڈیٹا[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(حجم(*mapping));
    اگر (!mapping)
        واپس AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        جاؤ fail;
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        اگر (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            توڑو;
    }
    اگر (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        جاؤ fail_derived;
    }

    mapping->بفر_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_مفرد;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    اگر (mapping->drm_desc.nb_layers > 1) {
        اگر (mapping->drm_desc.nb_layers != mapping->image.عدد_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.عدد_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            جاؤ fail_derived;
        }

        برائے(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_اشاریہ = 0,
                    .انحراف       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } ورنہ {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.عدد_planes;
        برائے (p = 0; p < mapping->image.عدد_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_اشاریہ = 0,
                .انحراف       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_بفر_Handle(hwctx->display, mapping->image.buf,
                                &mapping->بفر_info);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        جاؤ fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->بفر_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->بفر_info.handle,
        .سائز = mapping->image.ڈیٹا_سائز,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx,
                                dst, src, &vaapi_unmap_مقصد_drm_abh,
                                mapping);
    اگر (err < 0)
        جاؤ fail_mapped;

    dst->ڈیٹا[0] = (uint8_t*)&mapping->drm_desc;
    dst->چوڑائی   = src->چوڑائی;
    dst->اونچائی  = src->اونچائی;

    واپس 0;

fail_mapped:
    va_Release_بفر_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    واپس err;
}
#اگر_ختم

ساکن صحیح vaapi_map_مقصد_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحیح flags)
{
#اگر VA_CHECK_نسخہ(1, 1, 0)
    صحیح err;
    err = vaapi_map_مقصد_drm_esh(hwfc, dst, src, flags);
    اگر (err != AVERROR(ENOSYS))
        واپس err;
#اگر_ختم
#اگر VA_CHECK_نسخہ(0, 36, 0)
    واپس vaapi_map_مقصد_drm_abh(hwfc, dst, src, flags);
#اگر_ختم
    واپس AVERROR(ENOSYS);
}

#اگر_ختم /* CONFIG_LIBDRM */

ساکن صحیح vaapi_map_مقصد(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحیح flags)
{
    انتخاب (src->format) {
#اگر CONFIG_LIBDRM
    حالت AV_PIX_FMT_DRM_مفرد:
        واپس vaapi_map_from_drm(hwfc, dst, src, flags);
#اگر_ختم
    طےشدہ:
        واپس AVERROR(ENOSYS);
    }
}

ساکن صحیح vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ثابت AVFrame *src, صحیح flags)
{
    انتخاب (dst->format) {
#اگر CONFIG_LIBDRM
    حالت AV_PIX_FMT_DRM_مفرد:
        واپس vaapi_map_مقصد_drm(hwfc, dst, src, flags);
#اگر_ختم
    طےشدہ:
        واپس vaapi_map_مقصد_حافظہ(hwfc, dst, src, flags);
    }
}

ساکن خالی vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    اگر (hwctx->display)
        vaTerminate(hwctx->display);

#اگر HAVE_VAAPI_X11
    اگر (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#اگر_ختم

#اگر HAVE_VAAPI_DRM
    اگر (priv->drm_fd >= 0)
        close(priv->drm_fd);
#اگر_ختم

    av_freep(&priv);
}

#اگر CONFIG_VAAPI_1
ساکن خالی vaapi_device_log_error(خالی *context, ثابت حرف *پیغام_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", پیغام_2);
}

ساکن خالی vaapi_device_log_info(خالی *context, ثابت حرف *پیغام_2)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", پیغام_2);
}
#اگر_ختم

ساکن صحیح vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    صحیح major, minor;
    VAStatus vas;

#اگر CONFIG_VAAPI_1
    va_سیٹ_Error_Callback(display, &vaapi_device_log_error, ctx);
    va_سیٹ_Info_Callback (display, &vaapi_device_log_info,  ctx);
#اگر_ختم

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    اگر (vas != VA_حالت_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        واپس AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    واپس 0;
}

ساکن صحیح vaapi_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحیح flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = تہی;
    ثابت AVDictionary_اندراج *ent;
    صحیح try_drm, try_x11, try_win32, try_all av_غیر_مستعمل;

    priv = av_mallocz(حجم(*priv));
    اگر (!priv)
        واپس AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->آزاد        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", تہی, 0);
    اگر (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        اگر (!strcmp(ent->قدر, "drm")) {
            try_drm = 1;
        } ورنہ اگر (!strcmp(ent->قدر, "x11")) {
            try_x11 = 1;
        } ورنہ اگر (!strcmp(ent->قدر, "win32")) {
            try_win32 = 1;
        } ورنہ {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->قدر);
            واپس AVERROR(EINVAL);
        }
    } ورنہ {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#اگر HAVE_VAAPI_DRM
    جب (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        صحیح loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        اگر (device) {
            priv->drm_fd = open(device, O_RDWR);
            اگر (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                توڑو;
            }
        } ورنہ {
            حرف راستہ[64];
            صحیح n, max_devices = 8;
#اگر CONFIG_LIBDRM
            drm_نسخہ *info;
            ثابت AVDictionary_اندراج *kernel_driver;
            ثابت AVDictionary_اندراج *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", تہی, 0);
            vendor_id = av_dict_get(opts, "vendor_id", تہی, 0);
#اگر_ختم
            برائے (n = 0; n < max_devices; n++) {
                snprintf(راستہ, حجم(راستہ),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(راستہ, O_RDWR);
                اگر (priv->drm_fd < 0) {
                    اگر (errno == ENOENT) {
                        اگر (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", راستہ);
                            جاری;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } ورنہ
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    توڑو;
                }
#اگر CONFIG_LIBDRM
                info = drm_Get_نسخہ(priv->drm_fd);
                اگر (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    جاری;
                }
                اگر (kernel_driver) {
                    اگر (strcmp(kernel_driver->قدر, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drm_Free_نسخہ(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        جاری;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drm_Free_نسخہ(info);
                    توڑو;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } ورنہ اگر (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drm_Free_نسخہ(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    جاری;
                } ورنہ اگر (vendor_id) {
                    drmDevicePtr device;
                    حرف drm_vendor[8];
                    اگر (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_نسخہ(info);
                        جاری;
                    }

                    snprintf(drm_vendor, حجم(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    اگر (strcmp(vendor_id->قدر, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->قدر);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drm_Free_نسخہ(info);
                        جاری;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->قدر);
                    drmFreeDevice(&device);
                    drm_Free_نسخہ(info);
                    توڑو;
                }
                drm_Free_نسخہ(info);
#اگر_ختم
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                توڑو;
            }
            اگر (n >= max_devices)
                توڑو;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        اگر (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            واپس AVERROR_EXTERNAL;
        }
        توڑو;
    }
#اگر_ختم

#اگر HAVE_VAAPI_X11
    اگر (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        اگر (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } ورنہ {
            display = vaGetDisplay(priv->x11_display);
            اگر (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                واپس AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#اگر_ختم

#اگر HAVE_VAAPI_WIN32
    اگر (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        اگر (!device) {
            display = vaGetDisplayWin32(تہی);
        } ورنہ {
            IDXGIFactory2 *pDXGIFactory = تہی;
            IDXGIAdapter *pAdapter = تہی;
#اگر !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            اگر (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                واپس AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            اگر (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                واپس AVERROR_UNKNOWN;
            }
#ورنہ
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#اگر_ختم
            اگر (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (خالی **)&pDXGIFactory))) {
                صحیح adapter = atoi(device);
                اگر (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    اگر (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
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
#اگر !HAVE_UWP
            dlclose(dxgi);
#اگر_ختم
        }

        اگر (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            واپس AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#اگر_ختم

    اگر (!display) {
        اگر (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        ورنہ
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        واپس AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", تہی, 0);
    اگر (ent) {
#اگر VA_CHECK_نسخہ(0, 38, 0)
        VAStatus vas;
        vas = va_سیٹ_Driver_Name(display, ent->قدر);
        اگر (vas != VA_حالت_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->قدر, vas, vaErrorStr(vas));
            vaTerminate(display);
            واپس AVERROR_EXTERNAL;
        }
#ورنہ
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#اگر_ختم
    }

    واپس vaapi_device_connect(ctx, display);
}

ساکن صحیح vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, صحیح flags)
{
#اگر HAVE_VAAPI_DRM
    اگر (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        صحیح fd;

        اگر (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            واپس AVERROR(EINVAL);
        }

#اگر CONFIG_LIBDRM
        {
            صحیح گرہ_type = drm_Get_گرہ_Type_From_Fd(src_hwctx->fd);
            حرف *render_گرہ;
            اگر (گرہ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                واپس AVERROR(EINVAL);
            }
            اگر (گرہ_type == DRM_گرہ_RENDER) {
                fd = src_hwctx->fd;
            } ورنہ {
                render_گرہ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                اگر (!render_گرہ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } ورنہ {
                    fd = open(render_گرہ, O_RDWR);
                    اگر (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } ورنہ {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_گرہ);
                    }
                    آزاد(render_گرہ);
                }
            }
        }
#ورنہ
        fd = src_hwctx->fd;
#اگر_ختم

        priv = av_mallocz(حجم(*priv));
        اگر (!priv) {
            اگر (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            واپس AVERROR(ENOMEM);
        }

        اگر (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } ورنہ {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->آزاد        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        اگر (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            واپس AVERROR(EIO);
        }

        واپس vaapi_device_connect(ctx, display);
    }
#اگر_ختم
    واپس AVERROR(ENOSYS);
}

ثابت HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_سائز      = حجم(VAAPIDeviceContext),
    .device_hwconfig_سائز   = حجم(AVVAAPIHWConfig),
    .چوکھٹے_hwctx_سائز      = حجم(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .چوکھٹے_get_constraints = &vaapi_چوکھٹے_get_constraints,
    .چوکھٹے_init            = &vaapi_چوکھٹے_init,
    .چوکھٹے_uninit          = &vaapi_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = &vaapi_get_بفر,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_ڈیٹا_مقصد       = &vaapi_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from     = &vaapi_transfer_ڈیٹا_from,
    .map_مقصد                 = &vaapi_map_مقصد,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (ثابت شمار AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
