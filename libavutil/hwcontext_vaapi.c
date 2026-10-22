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
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
تعریفنوع HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, تهی **ppFactory);
#endif
#اگر HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#اگر HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#اگر CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#شامل <fcntl.h>
#اگر HAVE_UNISTD_H
#   include <unistd.h>
#endif


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


تعریفنوع ساختار VAAPIDevicePriv {
#اگر HAVE_VAAPI_X11
    Display *x11_display;
#endif

    صحیح drm_fd;
} VAAPIDevicePriv;

تعریفنوع ساختار VAAPISurfaceFormat {
    شمارش AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned صحیح fourcc;
} VAAPISurfaceFormat;

تعریفنوع ساختار VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    صحیح              nb_formats;
} VAAPIDeviceContext;

تعریفنوع ساختار VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    صحیح           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned صحیح rt_format;
    // Whether vaDeriveImage works.
    صحیح derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    صحیح اول_2_import_unsupported;
} VAAPIFramesContext;

تعریفنوع ساختار VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    صحیح flags;
} VAAPIMapping;

تعریفنوع ساختار VAAPIFormat {
    unsigned صحیح fourcc;
    unsigned صحیح rt_format;
    شمارش AVPixelFormat pix_fmt;
    صحیح chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
ایستا ثابت VAAPIFormatDescriptor vaapi_format_map[] = {
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

ایستا ثابت VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned صحیح fourcc)
{
    صحیح i;
    برای (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        اگر (vaapi_format_map[i].fourcc == fourcc)
            بازگشت &vaapi_format_map[i];
    بازگشت پوچ;
}

ایستا ثابت VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(شمارش AVPixelFormat pix_fmt, ثابت VAAPIFormatDescriptor *prev)
{
    ثابت VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    اگر (!prev)
        prev = vaapi_format_map;
    وگرنه
        prev++;

    برای (; prev < end; prev++)
        اگر (prev->pix_fmt == pix_fmt)
            بازگشت prev;
    بازگشت پوچ;
}

ایستا شمارش AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned صحیح fourcc)
{
    ثابت VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    اگر (desc)
        بازگشت desc->pix_fmt;
    وگرنه
        بازگشت AV_PIX_FMT_NONE;
}

ایستا صحیح vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  شمارش AVPixelFormat pix_fmt,
                                  ثابت VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ثابت VAAPIFormatDescriptor *desc = پوچ;
    صحیح i;

    وقتی ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        برای (i = 0; i < ctx->nb_formats; i++) {
            اگر (ctx->formats[i].fourcc == desc->fourcc) {
                اگر (_desc)
                    *_desc = desc;
                اگر (image_format)
                    *image_format = &ctx->formats[i].image_format;
                بازگشت 0;
            }
        }
    }

    بازگشت AVERROR(ENOSYS);
}

ایستا صحیح vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  شمارش AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    اگر (!image_format)
        بازگشت AVERROR(EINVAL);
    بازگشت vaapi_get_img_desc_and_format(hwdev, pix_fmt, پوچ, image_format);
}

ایستا صحیح vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        ثابت تهی *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ثابت AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = پوچ;
    VAStatus vas;
    شمارش AVPixelFormat pix_fmt;
    unsigned صحیح fourcc;
    صحیح err, i, j, attr_شمار, pix_fmt_شمار;

    اگر (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_شمار = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_شمار);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            برو fail;
        }

        attr_list = av_malloc(attr_شمار * اندازه(*attr_list));
        اگر (!attr_list) {
            err = AVERROR(ENOMEM);
            برو fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_شمار);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            برو fail;
        }

        pix_fmt_شمار = 0;
        برای (i = 0; i < attr_شمار; i++) {
            انتخاب (attr_list[i].type) {
            حالت VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].مقدار.مقدار.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                اگر (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_شمار;
                } وگرنه {
                    // Something unsupported - ignore.
                }
                بشکن;
            حالت VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].مقدار.مقدار.i;
                بشکن;
            حالت VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].مقدار.مقدار.i;
                بشکن;
            حالت VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].مقدار.مقدار.i;
                بشکن;
            حالت VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].مقدار.مقدار.i;
                بشکن;
            }
        }
        اگر (pix_fmt_شمار == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = پوچ;
        } وگرنه {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_شمار + 1,
                                                            اندازه(pix_fmt));
            اگر (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                برو fail;
            }

            برای (i = j = 0; i < attr_شمار; i++) {
                صحیح k;

                اگر (attr_list[i].type != VASurfaceAttribPixelFormat)
                    ادامه;
                fourcc = attr_list[i].مقدار.مقدار.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                اگر (pix_fmt == AV_PIX_FMT_NONE)
                    ادامه;

                برای (k = 0; k < j; k++) {
                    اگر (constraints->valid_sw_formats[k] == pix_fmt)
                        بشکن;
                }

                اگر (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } وگرنه {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        اندازه(pix_fmt));
        اگر (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            برو fail;
        }
        برای (i = j = 0; i < ctx->nb_formats; i++) {
            صحیح k;

            برای (k = 0; k < j; k++) {
                اگر (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    بشکن;
            }

            اگر (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(pix_fmt));
    اگر (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        برو fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    بازگشت err;
}

ایستا ثابت ساختار {
    ثابت نویسه *friendly_name;
    ثابت نویسه *match_string;
    unsigned صحیح quirks;
} vaapi_driver_quirks_table[] = {
#اگر !VA_CHECK_VERSION(1, 0, 0)
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

ایستا صحیح vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = پوچ;
    VAStatus vas;
    ثابت نویسه *vendor_string;
    صحیح err, i, image_شمار;
    شمارش AVPixelFormat pix_fmt;
    unsigned صحیح fourcc;

    image_شمار = va_Max_رقم_Image_Formats(hwctx->display);
    اگر (image_شمار <= 0) {
        err = AVERROR(EIO);
        برو fail;
    }
    image_list = av_malloc(image_شمار * اندازه(*image_list));
    اگر (!image_list) {
        err = AVERROR(ENOMEM);
        برو fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_شمار);
    اگر (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        برو fail;
    }

    ctx->formats  = av_malloc(image_شمار * اندازه(*ctx->formats));
    اگر (!ctx->formats) {
        err = AVERROR(ENOMEM);
        برو fail;
    }
    ctx->nb_formats = 0;
    برای (i = 0; i < image_شمار; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        اگر (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } وگرنه {
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

    اگر (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } وگرنه {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        اگر (vendor_string) {
            برای (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                اگر (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    بشکن;
                }
            }
            اگر (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } وگرنه {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    بازگشت 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    بازگشت err;
}

ایستا تهی vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

ایستا تهی vaapi_buffer_free(تهی *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

ایستا AVBufferRef *vaapi_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    اگر (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        بازگشت پوچ;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        بازگشت پوچ;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           اندازه(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    اگر (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        بازگشت پوچ;
    }

    اگر (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    بازگشت ref;
}

ایستا صحیح vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ثابت VAAPIFormatDescriptor *desc = پوچ;
    VAImageFormat *expected_format = پوچ;
    AVBufferRef *test_surface = پوچ;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    صحیح err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    اگر (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        اگر (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, پوچ)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            بازگشت AVERROR(EINVAL);
        }
    }

    اگر (!hwfc->pool) {
        اگر (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            صحیح need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            صحیح need_pixel_format = 1;
            برای (i = 0; i < avfc->nb_attributes; i++) {
                اگر (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                اگر (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        اندازه(*ctx->attributes));
            اگر (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                برو fail;
            }

            برای (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            اگر (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .مقدار.type    = VAGeneric_مقدار_Type_Integer,
                    .مقدار.مقدار.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            اگر (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .مقدار.type    = VAGeneric_مقدار_Type_Integer,
                    .مقدار.مقدار.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } وگرنه {
            ctx->attributes = پوچ;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        اگر (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          اندازه(*avfc->surface_ids));
            اگر (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                برو fail;
            }
        } وگرنه {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = پوچ;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(اندازه(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, پوچ);
        اگر (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            برو fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    اگر (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        اگر (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            برو fail;
        }
    } وگرنه {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        اگر (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            برو fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    اگر (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        اگر (vas == VA_STATUS_SUCCESS) {
            اگر (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } وگرنه {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } وگرنه {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } وگرنه {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    بازگشت 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    بازگشت err;
}

ایستا تهی vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

ایستا صحیح vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    بازگشت 0;
}

ایستا صحیح vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      شمارش AVHWFrameTransferDirection dir,
                                      شمارش AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    شمارش AVPixelFormat *pix_fmts;
    صحیح i, k, sw_format_available;

    sw_format_available = 0;
    برای (i = 0; i < ctx->nb_formats; i++) {
        اگر (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * اندازه(*pix_fmts));
    اگر (!pix_fmts)
        بازگشت AVERROR(ENOMEM);

    اگر (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } وگرنه {
        k = 0;
    }
    برای (i = 0; i < ctx->nb_formats; i++) {
        اگر (ctx->formats[i].pix_fmt == hwfc->sw_format)
            ادامه;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    بازگشت 0;
}

ایستا تهی vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    اگر ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

ایستا صحیح vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ثابت VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    تهی *address = پوچ;
    صحیح err, i;
#اگر VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    اگر (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        بازگشت AVERROR(EINVAL);
    }
    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    اگر (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        بازگشت AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    اگر (err < 0) {
        // Requested format is not a valid output format.
        بازگشت err;
    }

    map = av_malloc(اندازه(*map));
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        برو fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    اگر (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            برو fail;
        }
        اگر (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            برو fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } وگرنه {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            برو fail;
        }
        اگر (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            اگر (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                برو fail;
            }
        }
    }

#اگر VA_CHECK_VERSION(1, 21, 0)
    اگر (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    اگر (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#وگرنه
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        برو fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    برای (i = 0; i < map->image.رقم_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    اگر (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    بازگشت 0;

fail:
    اگر (map) {
        اگر (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        اگر (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    بازگشت err;
}

ایستا صحیح vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->width > hwfc->width || dst->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        برو fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->width > hwfc->width || src->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        برو fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    اگر (err)
        بازگشت err;

    err = av_frame_copy_props(dst, src);
    اگر (err)
        بازگشت err;

    بازگشت 0;
}

#اگر CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
ایستا ثابت ساختار {
    uint32_t va_fourcc;
    صحیح   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#اگر defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#اگر defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#اگر defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#اگر defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#اگر defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#اگر defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

ایستا تهی vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

ایستا صحیح vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحیح flags)
{
#اگر VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    صحیح use_prime2;
#وگرنه
    صحیح k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    ثابت VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    صحیح err, i, j;

#اگر !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .مقدار.type    = VAGeneric_مقدار_Type_Integer,
            .مقدار.مقدار.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_اول,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .مقدار.type    = VAGeneric_مقدار_Type_Pointer,
            .مقدار.مقدار.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    اگر (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        بازگشت AVERROR(EINVAL);
    }

    va_fourcc = 0;
    برای (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        اگر (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            ادامه;
        برای (j = 0; j < desc->nb_layers; j++) {
            اگر (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                بشکن;
        }
        اگر (j != desc->nb_layers)
            ادامه;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        بشکن;
    }
    اگر (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        بازگشت AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#اگر VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->اول_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    اگر (use_prime2) {
        VADRMPRIMESurfaceDescriptor اول_desc;
        VASurfaceAttrib اول_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .مقدار.type    = VAGeneric_مقدار_Type_Integer,
                .مقدار.مقدار.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_اول_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .مقدار.type    = VAGeneric_مقدار_Type_Pointer,
                .مقدار.مقدار.p = &اول_desc,
            }
        };
        اول_desc.fourcc = va_fourcc;
        اول_desc.width = src_fc->width;
        اول_desc.height = src_fc->height;
        اول_desc.رقم_objects = desc->nb_objects;
        برای (i = 0; i < desc->nb_objects; ++i) {
            اول_desc.objects[i].fd = desc->objects[i].fd;
            اول_desc.objects[i].size = desc->objects[i].size;
            اول_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        اول_desc.رقم_layers = desc->nb_layers;
        برای (i = 0; i < desc->nb_layers; ++i) {
            اول_desc.layers[i].drm_format = desc->layers[i].format;
            اول_desc.layers[i].رقم_planes = desc->layers[i].nb_planes;
            برای (j = 0; j < desc->layers[i].nb_planes; ++j) {
                اول_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                اول_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                اول_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            اگر (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, اول_desc.layers[i].pitch[1],
                    اول_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, اول_desc.layers[i].offset[1],
                    اول_desc.layers[i].offset[2]);
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
                               اول_attrs, FF_ARRAY_ELEMS(اول_attrs));
        اگر (vas != VA_STATUS_SUCCESS)
            src_vafc->اول_2_import_unsupported = 1;
    }

    اگر (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        صحیح k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .مقدار.type    = VAGeneric_مقدار_Type_Integer,
                .مقدار.مقدار.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_اول,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .مقدار.type    = VAGeneric_مقدار_Type_Pointer,
                .مقدار.مقدار.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.رقم_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        برای (i = 0; i < desc->nb_layers; i++) {
            برای (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.رقم_planes = k;

        اگر (format_desc->chroma_planes_swapped &&
            buffer_desc.رقم_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#وگرنه
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.رقم_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    برای (i = 0; i < desc->nb_layers; i++) {
        برای (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.رقم_planes = k;

    اگر (format_desc->chroma_planes_swapped &&
        buffer_desc.رقم_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        بازگشت AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (تهی*)(uintptr_t)surface_id);
    اگر (err < 0)
        بازگشت err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    بازگشت 0;
}

#اگر VA_CHECK_VERSION(1, 1, 0)
ایستا تهی vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    صحیح i;

    برای (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

ایستا صحیح vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = پوچ;
    uint32_t export_flags;
    صحیح err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    اگر (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            بازگشت AVERROR(EIO);
        }
    }

    اگر (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_اول_2,
                                export_flags, &va_desc);
    اگر (vas != VA_STATUS_SUCCESS) {
        اگر (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            بازگشت AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        بازگشت AVERROR(EIO);
    }

    drm_desc = av_mallocz(اندازه(*drm_desc));
    اگر (!drm_desc) {
        err = AVERROR(ENOMEM);
        برو fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.رقم_objects;
    برای (i = 0; i < va_desc.رقم_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.رقم_layers;
    برای (i = 0; i < va_desc.رقم_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].رقم_planes;
        برای (j = 0; j < va_desc.layers[i].رقم_planes; j++) {
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
    اگر (err < 0)
        برو fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    بازگشت 0;

fail:
    برای (i = 0; i < va_desc.رقم_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    بازگشت err;
}
#endif

#اگر VA_CHECK_VERSION(0, 36, 0)
تعریفنوع ساختار VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

ایستا تهی vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

ایستا صحیح vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ثابت AVFrame *src, صحیح flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = پوچ;
    VASurfaceID surface_id;
    VAStatus vas;
    صحیح err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(اندازه(*mapping));
    اگر (!mapping)
        بازگشت AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        برو fail;
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        اگر (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            بشکن;
    }
    اگر (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        برو fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_اول;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    اگر (mapping->drm_desc.nb_layers > 1) {
        اگر (mapping->drm_desc.nb_layers != mapping->image.رقم_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.رقم_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            برو fail_derived;
        }

        برای(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } وگرنه {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.رقم_planes;
        برای (p = 0; p < mapping->image.رقم_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        برو fail_derived;
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
    اگر (err < 0)
        برو fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    بازگشت 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    بازگشت err;
}
#endif

ایستا صحیح vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحیح flags)
{
#اگر VA_CHECK_VERSION(1, 1, 0)
    صحیح err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    اگر (err != AVERROR(ENOSYS))
        بازگشت err;
#endif
#اگر VA_CHECK_VERSION(0, 36, 0)
    بازگشت vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    بازگشت AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

ایستا صحیح vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        ثابت AVFrame *src, صحیح flags)
{
    انتخاب (src->format) {
#اگر CONFIG_LIBDRM
    حالت AV_PIX_FMT_DRM_اول:
        بازگشت vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }
}

ایستا صحیح vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ثابت AVFrame *src, صحیح flags)
{
    انتخاب (dst->format) {
#اگر CONFIG_LIBDRM
    حالت AV_PIX_FMT_DRM_اول:
        بازگشت vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    پیشفرض:
        بازگشت vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

ایستا تهی vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    اگر (hwctx->display)
        vaTerminate(hwctx->display);

#اگر HAVE_VAAPI_X11
    اگر (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#اگر HAVE_VAAPI_DRM
    اگر (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#اگر CONFIG_VAAPI_1
ایستا تهی vaapi_device_log_error(تهی *context, ثابت نویسه *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

ایستا تهی vaapi_device_log_info(تهی *context, ثابت نویسه *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

ایستا صحیح vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    صحیح major, minor;
    VAStatus vas;

#اگر CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    اگر (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        بازگشت AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    بازگشت 0;
}

ایستا صحیح vaapi_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                               AVDictionary *opts, صحیح flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = پوچ;
    ثابت AVDictionaryEntry *ent;
    صحیح try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(اندازه(*priv));
    اگر (!priv)
        بازگشت AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->آزاد        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", پوچ, 0);
    اگر (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        اگر (!strcmp(ent->مقدار, "drm")) {
            try_drm = 1;
        } وگرنه اگر (!strcmp(ent->مقدار, "x11")) {
            try_x11 = 1;
        } وگرنه اگر (!strcmp(ent->مقدار, "win32")) {
            try_win32 = 1;
        } وگرنه {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->مقدار);
            بازگشت AVERROR(EINVAL);
        }
    } وگرنه {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#اگر HAVE_VAAPI_DRM
    وقتی (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        صحیح loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        اگر (device) {
            priv->drm_fd = open(device, O_RDWR);
            اگر (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                بشکن;
            }
        } وگرنه {
            نویسه path[64];
            صحیح n, max_devices = 8;
#اگر CONFIG_LIBDRM
            drmVersion *info;
            ثابت AVDictionaryEntry *kernel_driver;
            ثابت AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", پوچ, 0);
            vendor_id = av_dict_get(opts, "vendor_id", پوچ, 0);
#endif
            برای (n = 0; n < max_devices; n++) {
                snprintf(path, اندازه(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                اگر (priv->drm_fd < 0) {
                    اگر (errno == ENOENT) {
                        اگر (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            ادامه;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } وگرنه
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    بشکن;
                }
#اگر CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                اگر (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ادامه;
                }
                اگر (kernel_driver) {
                    اگر (strcmp(kernel_driver->مقدار, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        ادامه;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    بشکن;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } وگرنه اگر (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ادامه;
                } وگرنه اگر (vendor_id) {
                    drmDevicePtr device;
                    نویسه drm_vendor[8];
                    اگر (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ادامه;
                    }

                    snprintf(drm_vendor, اندازه(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    اگر (strcmp(vendor_id->مقدار, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->مقدار);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ادامه;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->مقدار);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    بشکن;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                بشکن;
            }
            اگر (n >= max_devices)
                بشکن;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        اگر (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            بازگشت AVERROR_EXTERNAL;
        }
        بشکن;
    }
#endif

#اگر HAVE_VAAPI_X11
    اگر (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        اگر (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } وگرنه {
            display = vaGetDisplay(priv->x11_display);
            اگر (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                بازگشت AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#اگر HAVE_VAAPI_WIN32
    اگر (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        اگر (!device) {
            display = vaGetDisplayWin32(پوچ);
        } وگرنه {
            IDXGIFactory2 *pDXGIFactory = پوچ;
            IDXGIAdapter *pAdapter = پوچ;
#اگر !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            اگر (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                بازگشت AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            اگر (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                بازگشت AVERROR_UNKNOWN;
            }
#وگرنه
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            اگر (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (تهی **)&pDXGIFactory))) {
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
                              desc.AdapterLuid.بالا_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#اگر !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        اگر (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            بازگشت AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    اگر (!display) {
        اگر (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        وگرنه
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        بازگشت AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", پوچ, 0);
    اگر (ent) {
#اگر VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->مقدار);
        اگر (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->مقدار, vas, vaErrorStr(vas));
            vaTerminate(display);
            بازگشت AVERROR_EXTERNAL;
        }
#وگرنه
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    بازگشت vaapi_device_connect(ctx, display);
}

ایستا صحیح vaapi_device_derive(AVHWDeviceContext *ctx,
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
            بازگشت AVERROR(EINVAL);
        }

#اگر CONFIG_LIBDRM
        {
            صحیح گره_type = drm_Get_گره_Type_From_Fd(src_hwctx->fd);
            نویسه *render_گره;
            اگر (گره_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                بازگشت AVERROR(EINVAL);
            }
            اگر (گره_type == DRM_گره_RENDER) {
                fd = src_hwctx->fd;
            } وگرنه {
                render_گره = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                اگر (!render_گره) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } وگرنه {
                    fd = open(render_گره, O_RDWR);
                    اگر (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } وگرنه {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_گره);
                    }
                    آزاد(render_گره);
                }
            }
        }
#وگرنه
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(اندازه(*priv));
        اگر (!priv) {
            اگر (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            بازگشت AVERROR(ENOMEM);
        }

        اگر (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } وگرنه {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->آزاد        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        اگر (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            بازگشت AVERROR(EIO);
        }

        بازگشت vaapi_device_connect(ctx, display);
    }
#endif
    بازگشت AVERROR(ENOSYS);
}

ثابت HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = اندازه(VAAPIDeviceContext),
    .device_hwconfig_size   = اندازه(AVVAAPIHWConfig),
    .frames_hwctx_size      = اندازه(VAAPIFramesContext),

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

    .pix_fmts = (ثابت شمارش AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
