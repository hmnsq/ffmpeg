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

#अन्तर्भाव "config.h"

#यदि HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
प्रकारनिर्देश HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, शून्य **ppFactory);
#endif
#यदि HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#यदि HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#यदि CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#अन्तर्भाव <fcntl.h>
#यदि HAVE_UNISTD_H
#   include <unistd.h>
#endif


#अन्तर्भाव "avassert.h"
#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_drm.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_vaapi.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"


प्रकारनिर्देश संरचना VAAPIDevicePriv {
#यदि HAVE_VAAPI_X11
    Display *x11_display;
#endif

    पूर्णाङ्क drm_fd;
} VAAPIDevicePriv;

प्रकारनिर्देश संरचना VAAPISurfaceFormat {
    गणना AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned पूर्णाङ्क fourcc;
} VAAPISurfaceFormat;

प्रकारनिर्देश संरचना VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    पूर्णाङ्क              nb_formats;
} VAAPIDeviceContext;

प्रकारनिर्देश संरचना VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    पूर्णाङ्क           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned पूर्णाङ्क rt_format;
    // Whether vaDeriveImage works.
    पूर्णाङ्क derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    पूर्णाङ्क मूळसंख्या_2_import_unsupported;
} VAAPIFramesContext;

प्रकारनिर्देश संरचना VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    पूर्णाङ्क flags;
} VAAPIMapping;

प्रकारनिर्देश संरचना VAAPIFormat {
    unsigned पूर्णाङ्क fourcc;
    unsigned पूर्णाङ्क rt_format;
    गणना AVPixelFormat pix_fmt;
    पूर्णाङ्क chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
स्थिर ध्रुव VAAPIFormatDescriptor vaapi_format_map[] = {
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

स्थिर ध्रुव VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned पूर्णाङ्क fourcc)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        यदि (vaapi_format_map[i].fourcc == fourcc)
            प्रत्यागम &vaapi_format_map[i];
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(गणना AVPixelFormat pix_fmt, ध्रुव VAAPIFormatDescriptor *prev)
{
    ध्रुव VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    यदि (!prev)
        prev = vaapi_format_map;
    अन्यथा
        prev++;

    प्रति (; prev < end; prev++)
        यदि (prev->pix_fmt == pix_fmt)
            प्रत्यागम prev;
    प्रत्यागम रिक्त;
}

स्थिर गणना AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned पूर्णाङ्क fourcc)
{
    ध्रुव VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    यदि (desc)
        प्रत्यागम desc->pix_fmt;
    अन्यथा
        प्रत्यागम AV_PIX_FMT_NONE;
}

स्थिर पूर्णाङ्क vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  गणना AVPixelFormat pix_fmt,
                                  ध्रुव VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    ध्रुव VAAPIFormatDescriptor *desc = रिक्त;
    पूर्णाङ्क i;

    यावत् ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        प्रति (i = 0; i < ctx->nb_formats; i++) {
            यदि (ctx->formats[i].fourcc == desc->fourcc) {
                यदि (_desc)
                    *_desc = desc;
                यदि (image_format)
                    *image_format = &ctx->formats[i].image_format;
                प्रत्यागम 0;
            }
        }
    }

    प्रत्यागम AVERROR(ENOSYS);
}

स्थिर पूर्णाङ्क vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  गणना AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    यदि (!image_format)
        प्रत्यागम AVERROR(EINVAL);
    प्रत्यागम vaapi_get_img_desc_and_format(hwdev, pix_fmt, रिक्त, image_format);
}

स्थिर पूर्णाङ्क vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        ध्रुव शून्य *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    ध्रुव AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = रिक्त;
    VAStatus vas;
    गणना AVPixelFormat pix_fmt;
    unsigned पूर्णाङ्क fourcc;
    पूर्णाङ्क err, i, j, attr_मोजणी, pix_fmt_मोजणी;

    यदि (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_मोजणी = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_मोजणी);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            गच्छ fail;
        }

        attr_list = av_malloc(attr_मोजणी * परिमाण(*attr_list));
        यदि (!attr_list) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_मोजणी);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            गच्छ fail;
        }

        pix_fmt_मोजणी = 0;
        प्रति (i = 0; i < attr_मोजणी; i++) {
            विकल्प (attr_list[i].type) {
            पक्ष VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                यदि (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_मोजणी;
                } अन्यथा {
                    // Something unsupported - ignore.
                }
                भङ्ग;
            पक्ष VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].मूल्य.मूल्य.i;
                भङ्ग;
            पक्ष VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].मूल्य.मूल्य.i;
                भङ्ग;
            पक्ष VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].मूल्य.मूल्य.i;
                भङ्ग;
            पक्ष VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].मूल्य.मूल्य.i;
                भङ्ग;
            }
        }
        यदि (pix_fmt_मोजणी == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = रिक्त;
        } अन्यथा {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_मोजणी + 1,
                                                            परिमाण(pix_fmt));
            यदि (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                गच्छ fail;
            }

            प्रति (i = j = 0; i < attr_मोजणी; i++) {
                पूर्णाङ्क k;

                यदि (attr_list[i].type != VASurfaceAttribPixelFormat)
                    अनुवर्त;
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                यदि (pix_fmt == AV_PIX_FMT_NONE)
                    अनुवर्त;

                प्रति (k = 0; k < j; k++) {
                    यदि (constraints->valid_sw_formats[k] == pix_fmt)
                        भङ्ग;
                }

                यदि (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } अन्यथा {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        परिमाण(pix_fmt));
        यदि (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
        प्रति (i = j = 0; i < ctx->nb_formats; i++) {
            पूर्णाङ्क k;

            प्रति (k = 0; k < j; k++) {
                यदि (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    भङ्ग;
            }

            यदि (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(pix_fmt));
    यदि (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    प्रत्यागम err;
}

स्थिर ध्रुव संरचना {
    ध्रुव वर्ण *friendly_name;
    ध्रुव वर्ण *match_string;
    unsigned पूर्णाङ्क quirks;
} vaapi_driver_quirks_table[] = {
#यदि !VA_CHECK_VERSION(1, 0, 0)
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

स्थिर पूर्णाङ्क vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = रिक्त;
    VAStatus vas;
    ध्रुव वर्ण *vendor_string;
    पूर्णाङ्क err, i, image_मोजणी;
    गणना AVPixelFormat pix_fmt;
    unsigned पूर्णाङ्क fourcc;

    image_मोजणी = va_Max_अंक_Image_Formats(hwctx->display);
    यदि (image_मोजणी <= 0) {
        err = AVERROR(EIO);
        गच्छ fail;
    }
    image_list = av_malloc(image_मोजणी * परिमाण(*image_list));
    यदि (!image_list) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_मोजणी);
    यदि (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        गच्छ fail;
    }

    ctx->formats  = av_malloc(image_मोजणी * परिमाण(*ctx->formats));
    यदि (!ctx->formats) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }
    ctx->nb_formats = 0;
    प्रति (i = 0; i < image_मोजणी; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        यदि (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } अन्यथा {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    यदि (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    यदि (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } अन्यथा {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        यदि (vendor_string) {
            प्रति (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                यदि (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    भङ्ग;
                }
            }
            यदि (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } अन्यथा {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    प्रत्यागम 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    प्रत्यागम err;
}

स्थिर शून्य vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

स्थिर शून्य vaapi_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

स्थिर AVBufferRef *vaapi_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    यदि (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        प्रत्यागम रिक्त;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        प्रत्यागम रिक्त;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           परिमाण(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    यदि (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        प्रत्यागम रिक्त;
    }

    यदि (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    प्रत्यागम ref;
}

स्थिर पूर्णाङ्क vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    ध्रुव VAAPIFormatDescriptor *desc = रिक्त;
    VAImageFormat *expected_format = रिक्त;
    AVBufferRef *test_surface = रिक्त;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    पूर्णाङ्क err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    यदि (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        यदि (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, रिक्त)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            प्रत्यागम AVERROR(EINVAL);
        }
    }

    यदि (!hwfc->pool) {
        यदि (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            पूर्णाङ्क need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            पूर्णाङ्क need_pixel_format = 1;
            प्रति (i = 0; i < avfc->nb_attributes; i++) {
                यदि (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                यदि (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        परिमाण(*ctx->attributes));
            यदि (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                गच्छ fail;
            }

            प्रति (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            यदि (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                    .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            यदि (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                    .मूल्य.मूल्य.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } अन्यथा {
            ctx->attributes = रिक्त;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        यदि (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          परिमाण(*avfc->surface_ids));
            यदि (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                गच्छ fail;
            }
        } अन्यथा {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = रिक्त;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(परिमाण(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, रिक्त);
        यदि (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    यदि (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        यदि (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    } अन्यथा {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        यदि (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    यदि (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        यदि (vas == VA_STATUS_SUCCESS) {
            यदि (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } अन्यथा {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } अन्यथा {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } अन्यथा {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    प्रत्यागम 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    प्रत्यागम err;
}

स्थिर शून्य vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

स्थिर पूर्णाङ्क vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      गणना AVHWFrameTransferDirection dir,
                                      गणना AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    गणना AVPixelFormat *pix_fmts;
    पूर्णाङ्क i, k, sw_format_available;

    sw_format_available = 0;
    प्रति (i = 0; i < ctx->nb_formats; i++) {
        यदि (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * परिमाण(*pix_fmts));
    यदि (!pix_fmts)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } अन्यथा {
        k = 0;
    }
    प्रति (i = 0; i < ctx->nb_formats; i++) {
        यदि (ctx->formats[i].pix_fmt == hwfc->sw_format)
            अनुवर्त;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    प्रत्यागम 0;
}

स्थिर शून्य vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    यदि ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

स्थिर पूर्णाङ्क vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    ध्रुव VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    शून्य *address = रिक्त;
    पूर्णाङ्क err, i;
#यदि VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    यदि (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        प्रत्यागम AVERROR(EINVAL);
    }
    यदि (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    यदि (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        प्रत्यागम AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    यदि (err < 0) {
        // Requested format is not a valid output format.
        प्रत्यागम err;
    }

    map = av_malloc(परिमाण(*map));
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        गच्छ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    यदि (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            गच्छ fail;
        }
        यदि (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            गच्छ fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } अन्यथा {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            गच्छ fail;
        }
        यदि (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            यदि (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                गच्छ fail;
            }
        }
    }

#यदि VA_CHECK_VERSION(1, 21, 0)
    यदि (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    यदि (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#अन्यथा
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        गच्छ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    यदि (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रति (i = 0; i < map->image.अंक_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    यदि (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    प्रत्यागम 0;

fail:
    यदि (map) {
        यदि (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        यदि (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (dst->width > hwfc->width || dst->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    यदि (err)
        गच्छ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (src->width > hwfc->width || src->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    यदि (err)
        गच्छ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    यदि (err)
        प्रत्यागम err;

    err = av_frame_copy_props(dst, src);
    यदि (err)
        प्रत्यागम err;

    प्रत्यागम 0;
}

#यदि CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
स्थिर ध्रुव संरचना {
    uint32_t va_fourcc;
    पूर्णाङ्क   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#यदि defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#यदि defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#यदि defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#यदि defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#यदि defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#यदि defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

स्थिर शून्य vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

स्थिर पूर्णाङ्क vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
#यदि VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    पूर्णाङ्क use_prime2;
#अन्यथा
    पूर्णाङ्क k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    ध्रुव AVDRMFrameDescriptor *desc;
    ध्रुव VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    पूर्णाङ्क err, i, j;

#यदि !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
            .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
            .मूल्य.मूल्य.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    यदि (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    va_fourcc = 0;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        यदि (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            अनुवर्त;
        प्रति (j = 0; j < desc->nb_layers; j++) {
            यदि (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                भङ्ग;
        }
        यदि (j != desc->nb_layers)
            अनुवर्त;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        भङ्ग;
    }
    यदि (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#यदि VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->मूळसंख्या_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    यदि (use_prime2) {
        VADRMPRIMESurfaceDescriptor मूळसंख्या_desc;
        VASurfaceAttrib मूळसंख्या_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
                .मूल्य.मूल्य.p = &मूळसंख्या_desc,
            }
        };
        मूळसंख्या_desc.fourcc = va_fourcc;
        मूळसंख्या_desc.width = src_fc->width;
        मूळसंख्या_desc.height = src_fc->height;
        मूळसंख्या_desc.अंक_objects = desc->nb_objects;
        प्रति (i = 0; i < desc->nb_objects; ++i) {
            मूळसंख्या_desc.objects[i].fd = desc->objects[i].fd;
            मूळसंख्या_desc.objects[i].size = desc->objects[i].size;
            मूळसंख्या_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        मूळसंख्या_desc.अंक_layers = desc->nb_layers;
        प्रति (i = 0; i < desc->nb_layers; ++i) {
            मूळसंख्या_desc.layers[i].drm_format = desc->layers[i].format;
            मूळसंख्या_desc.layers[i].अंक_planes = desc->layers[i].nb_planes;
            प्रति (j = 0; j < desc->layers[i].nb_planes; ++j) {
                मूळसंख्या_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                मूळसंख्या_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                मूळसंख्या_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            यदि (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, मूळसंख्या_desc.layers[i].pitch[1],
                    मूळसंख्या_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, मूळसंख्या_desc.layers[i].offset[1],
                    मूळसंख्या_desc.layers[i].offset[2]);
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
                               मूळसंख्या_attrs, FF_ARRAY_ELEMS(मूळसंख्या_attrs));
        यदि (vas != VA_STATUS_SUCCESS)
            src_vafc->मूळसंख्या_2_import_unsupported = 1;
    }

    यदि (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        पूर्णाङ्क k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
                .मूल्य.मूल्य.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.अंक_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        प्रति (i = 0; i < desc->nb_layers; i++) {
            प्रति (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.अंक_planes = k;

        यदि (format_desc->chroma_planes_swapped &&
            buffer_desc.अंक_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#अन्यथा
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.अंक_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        प्रति (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.अंक_planes = k;

    यदि (format_desc->chroma_planes_swapped &&
        buffer_desc.अंक_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        प्रत्यागम AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (शून्य*)(uintptr_t)surface_id);
    यदि (err < 0)
        प्रत्यागम err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    प्रत्यागम 0;
}

#यदि VA_CHECK_VERSION(1, 1, 0)
स्थिर शून्य vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    पूर्णाङ्क i;

    प्रति (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

स्थिर पूर्णाङ्क vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = रिक्त;
    uint32_t export_flags;
    पूर्णाङ्क err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    यदि (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            प्रत्यागम AVERROR(EIO);
        }
    }

    यदि (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या_2,
                                export_flags, &va_desc);
    यदि (vas != VA_STATUS_SUCCESS) {
        यदि (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            प्रत्यागम AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        प्रत्यागम AVERROR(EIO);
    }

    drm_desc = av_mallocz(परिमाण(*drm_desc));
    यदि (!drm_desc) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.अंक_objects;
    प्रति (i = 0; i < va_desc.अंक_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.अंक_layers;
    प्रति (i = 0; i < va_desc.अंक_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].अंक_planes;
        प्रति (j = 0; j < va_desc.layers[i].अंक_planes; j++) {
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
    यदि (err < 0)
        गच्छ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < va_desc.अंक_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    प्रत्यागम err;
}
#endif

#यदि VA_CHECK_VERSION(0, 36, 0)
प्रकारनिर्देश संरचना VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

स्थिर शून्य vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

स्थिर पूर्णाङ्क vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = रिक्त;
    VASurfaceID surface_id;
    VAStatus vas;
    पूर्णाङ्क err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(परिमाण(*mapping));
    यदि (!mapping)
        प्रत्यागम AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        गच्छ fail;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        यदि (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            भङ्ग;
    }
    यदि (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        गच्छ fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    यदि (mapping->drm_desc.nb_layers > 1) {
        यदि (mapping->drm_desc.nb_layers != mapping->image.अंक_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.अंक_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            गच्छ fail_derived;
        }

        प्रति(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } अन्यथा {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.अंक_planes;
        प्रति (p = 0; p < mapping->image.अंक_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        गच्छ fail_derived;
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
    यदि (err < 0)
        गच्छ fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    प्रत्यागम 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    प्रत्यागम err;
}
#endif

स्थिर पूर्णाङ्क vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
#यदि VA_CHECK_VERSION(1, 1, 0)
    पूर्णाङ्क err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    यदि (err != AVERROR(ENOSYS))
        प्रत्यागम err;
#endif
#यदि VA_CHECK_VERSION(0, 36, 0)
    प्रत्यागम vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    प्रत्यागम AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

स्थिर पूर्णाङ्क vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    विकल्प (src->format) {
#यदि CONFIG_LIBDRM
    पक्ष AV_PIX_FMT_DRM_मूळसंख्या:
        प्रत्यागम vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }
}

स्थिर पूर्णाङ्क vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    विकल्प (dst->format) {
#यदि CONFIG_LIBDRM
    पक्ष AV_PIX_FMT_DRM_मूळसंख्या:
        प्रत्यागम vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    स्वभाव:
        प्रत्यागम vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

स्थिर शून्य vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    यदि (hwctx->display)
        vaTerminate(hwctx->display);

#यदि HAVE_VAAPI_X11
    यदि (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#यदि HAVE_VAAPI_DRM
    यदि (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#यदि CONFIG_VAAPI_1
स्थिर शून्य vaapi_device_log_error(शून्य *context, ध्रुव वर्ण *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

स्थिर शून्य vaapi_device_log_info(शून्य *context, ध्रुव वर्ण *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

स्थिर पूर्णाङ्क vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    पूर्णाङ्क major, minor;
    VAStatus vas;

#यदि CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    यदि (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        प्रत्यागम AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vaapi_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                               AVDictionary *opts, पूर्णाङ्क flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = रिक्त;
    ध्रुव AVDictionaryEntry *ent;
    पूर्णाङ्क try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(परिमाण(*priv));
    यदि (!priv)
        प्रत्यागम AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->मुक्त        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", रिक्त, 0);
    यदि (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        यदि (!strcmp(ent->मूल्य, "drm")) {
            try_drm = 1;
        } अन्यथा यदि (!strcmp(ent->मूल्य, "x11")) {
            try_x11 = 1;
        } अन्यथा यदि (!strcmp(ent->मूल्य, "win32")) {
            try_win32 = 1;
        } अन्यथा {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->मूल्य);
            प्रत्यागम AVERROR(EINVAL);
        }
    } अन्यथा {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#यदि HAVE_VAAPI_DRM
    यावत् (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        पूर्णाङ्क loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        यदि (device) {
            priv->drm_fd = open(device, O_RDWR);
            यदि (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                भङ्ग;
            }
        } अन्यथा {
            वर्ण path[64];
            पूर्णाङ्क n, max_devices = 8;
#यदि CONFIG_LIBDRM
            drmVersion *info;
            ध्रुव AVDictionaryEntry *kernel_driver;
            ध्रुव AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", रिक्त, 0);
            vendor_id = av_dict_get(opts, "vendor_id", रिक्त, 0);
#endif
            प्रति (n = 0; n < max_devices; n++) {
                snprintf(path, परिमाण(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                यदि (priv->drm_fd < 0) {
                    यदि (errno == ENOENT) {
                        यदि (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            अनुवर्त;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } अन्यथा
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    भङ्ग;
                }
#यदि CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                यदि (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    अनुवर्त;
                }
                यदि (kernel_driver) {
                    यदि (strcmp(kernel_driver->मूल्य, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        अनुवर्त;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    भङ्ग;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } अन्यथा यदि (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    अनुवर्त;
                } अन्यथा यदि (vendor_id) {
                    drmDevicePtr device;
                    वर्ण drm_vendor[8];
                    यदि (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        अनुवर्त;
                    }

                    snprintf(drm_vendor, परिमाण(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    यदि (strcmp(vendor_id->मूल्य, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->मूल्य);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        अनुवर्त;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->मूल्य);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    भङ्ग;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                भङ्ग;
            }
            यदि (n >= max_devices)
                भङ्ग;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        यदि (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            प्रत्यागम AVERROR_EXTERNAL;
        }
        भङ्ग;
    }
#endif

#यदि HAVE_VAAPI_X11
    यदि (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        यदि (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } अन्यथा {
            display = vaGetDisplay(priv->x11_display);
            यदि (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                प्रत्यागम AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#यदि HAVE_VAAPI_WIN32
    यदि (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        यदि (!device) {
            display = vaGetDisplayWin32(रिक्त);
        } अन्यथा {
            IDXGIFactory2 *pDXGIFactory = रिक्त;
            IDXGIAdapter *pAdapter = रिक्त;
#यदि !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            यदि (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                प्रत्यागम AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            यदि (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                प्रत्यागम AVERROR_UNKNOWN;
            }
#अन्यथा
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            यदि (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (शून्य **)&pDXGIFactory))) {
                पूर्णाङ्क adapter = atoi(device);
                यदि (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    यदि (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.खालचा_Part,
                              desc.AdapterLuid.वरचा_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#यदि !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        यदि (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            प्रत्यागम AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    यदि (!display) {
        यदि (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        अन्यथा
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", रिक्त, 0);
    यदि (ent) {
#यदि VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->मूल्य);
        यदि (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->मूल्य, vas, vaErrorStr(vas));
            vaTerminate(display);
            प्रत्यागम AVERROR_EXTERNAL;
        }
#अन्यथा
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    प्रत्यागम vaapi_device_connect(ctx, display);
}

स्थिर पूर्णाङ्क vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, पूर्णाङ्क flags)
{
#यदि HAVE_VAAPI_DRM
    यदि (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        पूर्णाङ्क fd;

        यदि (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            प्रत्यागम AVERROR(EINVAL);
        }

#यदि CONFIG_LIBDRM
        {
            पूर्णाङ्क गाठ_type = drm_Get_गाठ_Type_From_Fd(src_hwctx->fd);
            वर्ण *render_गाठ;
            यदि (गाठ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                प्रत्यागम AVERROR(EINVAL);
            }
            यदि (गाठ_type == DRM_गाठ_RENDER) {
                fd = src_hwctx->fd;
            } अन्यथा {
                render_गाठ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                यदि (!render_गाठ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } अन्यथा {
                    fd = open(render_गाठ, O_RDWR);
                    यदि (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } अन्यथा {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_गाठ);
                    }
                    मुक्त(render_गाठ);
                }
            }
        }
#अन्यथा
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(परिमाण(*priv));
        यदि (!priv) {
            यदि (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            प्रत्यागम AVERROR(ENOMEM);
        }

        यदि (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } अन्यथा {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->मुक्त        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        यदि (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            प्रत्यागम AVERROR(EIO);
        }

        प्रत्यागम vaapi_device_connect(ctx, display);
    }
#endif
    प्रत्यागम AVERROR(ENOSYS);
}

ध्रुव HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = परिमाण(VAAPIDeviceContext),
    .device_hwconfig_size   = परिमाण(AVVAAPIHWConfig),
    .frames_hwctx_size      = परिमाण(VAAPIFramesContext),

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

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
