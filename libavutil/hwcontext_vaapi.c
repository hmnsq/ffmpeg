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

#जर HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
प्रकारव्याख्या HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, शून्य **ppFactory);
#endif
#जर HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#जर HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#जर CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#अन्तर्भाव <fcntl.h>
#जर HAVE_UNISTD_H
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


प्रकारव्याख्या संरचना VAAPIDevicePriv {
#जर HAVE_VAAPI_X11
    Display *x11_display;
#endif

    पूर्णांक drm_fd;
} VAAPIDevicePriv;

प्रकारव्याख्या संरचना VAAPISurfaceFormat {
    गणना AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    अचिन्हित पूर्णांक fourcc;
} VAAPISurfaceFormat;

प्रकारव्याख्या संरचना VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    पूर्णांक              nb_formats;
} VAAPIDeviceContext;

प्रकारव्याख्या संरचना VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    पूर्णांक           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    अचिन्हित पूर्णांक rt_format;
    // Whether vaDeriveImage works.
    पूर्णांक derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    पूर्णांक मूळसंख्या_2_import_unsupported;
} VAAPIFramesContext;

प्रकारव्याख्या संरचना VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    पूर्णांक flags;
} VAAPIMapping;

प्रकारव्याख्या संरचना VAAPIFormat {
    अचिन्हित पूर्णांक fourcc;
    अचिन्हित पूर्णांक rt_format;
    गणना AVPixelFormat pix_fmt;
    पूर्णांक chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
स्थिर स्थिरांक VAAPIFormatDescriptor vaapi_format_map[] = {
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

स्थिर स्थिरांक VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(अचिन्हित पूर्णांक fourcc)
{
    पूर्णांक i;
    साठी (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        जर (vaapi_format_map[i].fourcc == fourcc)
            परत &vaapi_format_map[i];
    परत रिक्त;
}

स्थिर स्थिरांक VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(गणना AVPixelFormat pix_fmt, स्थिरांक VAAPIFormatDescriptor *prev)
{
    स्थिरांक VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    जर (!prev)
        prev = vaapi_format_map;
    अन्यथा
        prev++;

    साठी (; prev < end; prev++)
        जर (prev->pix_fmt == pix_fmt)
            परत prev;
    परत रिक्त;
}

स्थिर गणना AVPixelFormat vaapi_pix_fmt_from_fourcc(अचिन्हित पूर्णांक fourcc)
{
    स्थिरांक VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    जर (desc)
        परत desc->pix_fmt;
    अन्यथा
        परत AV_PIX_FMT_NONE;
}

स्थिर पूर्णांक vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  गणना AVPixelFormat pix_fmt,
                                  स्थिरांक VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    स्थिरांक VAAPIFormatDescriptor *desc = रिक्त;
    पूर्णांक i;

    पर्यंत ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        साठी (i = 0; i < ctx->nb_formats; i++) {
            जर (ctx->formats[i].fourcc == desc->fourcc) {
                जर (_desc)
                    *_desc = desc;
                जर (image_format)
                    *image_format = &ctx->formats[i].image_format;
                परत 0;
            }
        }
    }

    परत AVERROR(ENOSYS);
}

स्थिर पूर्णांक vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  गणना AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    जर (!image_format)
        परत AVERROR(EINVAL);
    परत vaapi_get_img_desc_and_format(hwdev, pix_fmt, रिक्त, image_format);
}

स्थिर पूर्णांक vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        स्थिरांक शून्य *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    स्थिरांक AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = रिक्त;
    VAStatus vas;
    गणना AVPixelFormat pix_fmt;
    अचिन्हित पूर्णांक fourcc;
    पूर्णांक err, i, j, attr_मोजणी, pix_fmt_मोजणी;

    जर (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_मोजणी = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_मोजणी);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            जा fail;
        }

        attr_list = av_malloc(attr_मोजणी * आकार(*attr_list));
        जर (!attr_list) {
            err = AVERROR(ENOMEM);
            जा fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_मोजणी);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            जा fail;
        }

        pix_fmt_मोजणी = 0;
        साठी (i = 0; i < attr_मोजणी; i++) {
            निवड (attr_list[i].type) {
            स्थिती VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                जर (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_मोजणी;
                } अन्यथा {
                    // Something unsupported - ignore.
                }
                थांबा;
            स्थिती VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].मूल्य.मूल्य.i;
                थांबा;
            स्थिती VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].मूल्य.मूल्य.i;
                थांबा;
            स्थिती VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].मूल्य.मूल्य.i;
                थांबा;
            स्थिती VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].मूल्य.मूल्य.i;
                थांबा;
            }
        }
        जर (pix_fmt_मोजणी == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = रिक्त;
        } अन्यथा {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_मोजणी + 1,
                                                            आकार(pix_fmt));
            जर (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                जा fail;
            }

            साठी (i = j = 0; i < attr_मोजणी; i++) {
                पूर्णांक k;

                जर (attr_list[i].type != VASurfaceAttribPixelFormat)
                    सुरूठेवा;
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                जर (pix_fmt == AV_PIX_FMT_NONE)
                    सुरूठेवा;

                साठी (k = 0; k < j; k++) {
                    जर (constraints->valid_sw_formats[k] == pix_fmt)
                        थांबा;
                }

                जर (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } अन्यथा {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        आकार(pix_fmt));
        जर (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            जा fail;
        }
        साठी (i = j = 0; i < ctx->nb_formats; i++) {
            पूर्णांक k;

            साठी (k = 0; k < j; k++) {
                जर (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    थांबा;
            }

            जर (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, आकार(pix_fmt));
    जर (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        जा fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    परत err;
}

स्थिर स्थिरांक संरचना {
    स्थिरांक अक्षर *friendly_name;
    स्थिरांक अक्षर *match_string;
    अचिन्हित पूर्णांक quirks;
} vaapi_driver_quirks_table[] = {
#जर !VA_CHECK_VERSION(1, 0, 0)
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

स्थिर पूर्णांक vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = रिक्त;
    VAStatus vas;
    स्थिरांक अक्षर *vendor_string;
    पूर्णांक err, i, image_मोजणी;
    गणना AVPixelFormat pix_fmt;
    अचिन्हित पूर्णांक fourcc;

    image_मोजणी = va_Max_अंक_Image_Formats(hwctx->display);
    जर (image_मोजणी <= 0) {
        err = AVERROR(EIO);
        जा fail;
    }
    image_list = av_malloc(image_मोजणी * आकार(*image_list));
    जर (!image_list) {
        err = AVERROR(ENOMEM);
        जा fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_मोजणी);
    जर (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        जा fail;
    }

    ctx->formats  = av_malloc(image_मोजणी * आकार(*ctx->formats));
    जर (!ctx->formats) {
        err = AVERROR(ENOMEM);
        जा fail;
    }
    ctx->nb_formats = 0;
    साठी (i = 0; i < image_मोजणी; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        जर (pix_fmt == AV_PIX_FMT_NONE) {
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
    जर (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    जर (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } अन्यथा {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        जर (vendor_string) {
            साठी (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                जर (म_माला(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    थांबा;
                }
            }
            जर (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } अन्यथा {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    परत 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    परत err;
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
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

स्थिर AVBufferRef *vaapi_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    जर (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        परत रिक्त;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        परत रिक्त;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           आकार(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    जर (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        परत रिक्त;
    }

    जर (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    परत ref;
}

स्थिर पूर्णांक vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    स्थिरांक VAAPIFormatDescriptor *desc = रिक्त;
    VAImageFormat *expected_format = रिक्त;
    AVBufferRef *test_surface = रिक्त;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    पूर्णांक err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    जर (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        जर (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, रिक्त)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            परत AVERROR(EINVAL);
        }
    }

    जर (!hwfc->pool) {
        जर (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            पूर्णांक need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            पूर्णांक need_pixel_format = 1;
            साठी (i = 0; i < avfc->nb_attributes; i++) {
                जर (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                जर (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        आकार(*ctx->attributes));
            जर (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                जा fail;
            }

            साठी (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            जर (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                    .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            जर (need_pixel_format) {
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

        जर (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          आकार(*avfc->surface_ids));
            जर (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                जा fail;
            }
        } अन्यथा {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = रिक्त;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(आकार(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, रिक्त);
        जर (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            जा fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    जर (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        जर (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            जा fail;
        }
    } अन्यथा {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        जर (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            जा fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    जर (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        जर (vas == VA_STATUS_SUCCESS) {
            जर (expected_format->fourcc == test_image.format.fourcc) {
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
    परत 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    परत err;
}

स्थिर शून्य vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

स्थिर पूर्णांक vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    परत 0;
}

स्थिर पूर्णांक vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      गणना AVHWFrameTransferDirection dir,
                                      गणना AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    गणना AVPixelFormat *pix_fmts;
    पूर्णांक i, k, sw_format_available;

    sw_format_available = 0;
    साठी (i = 0; i < ctx->nb_formats; i++) {
        जर (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * आकार(*pix_fmts));
    जर (!pix_fmts)
        परत AVERROR(ENOMEM);

    जर (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } अन्यथा {
        k = 0;
    }
    साठी (i = 0; i < ctx->nb_formats; i++) {
        जर (ctx->formats[i].pix_fmt == hwfc->sw_format)
            सुरूठेवा;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    परत 0;
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
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    जर ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

स्थिर पूर्णांक vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    स्थिरांक VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    शून्य *address = रिक्त;
    पूर्णांक err, i;
#जर VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    जर (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        परत AVERROR(EINVAL);
    }
    जर (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    जर (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        परत AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    जर (err < 0) {
        // Requested format is not a valid output format.
        परत err;
    }

    map = av_malloc(आकार(*map));
    जर (!map)
        परत AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जा fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    जर (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            जा fail;
        }
        जर (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            जा fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } अन्यथा {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            जा fail;
        }
        जर (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            जर (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                जा fail;
            }
        }
    }

#जर VA_CHECK_VERSION(1, 21, 0)
    जर (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    जर (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#अन्यथा
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जा fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    जर (err < 0)
        जा fail;

    dst->width  = src->width;
    dst->height = src->height;

    साठी (i = 0; i < map->image.अंक_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    जर (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    परत 0;

fail:
    जर (map) {
        जर (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        जर (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    परत err;
}

स्थिर पूर्णांक vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, स्थिरांक AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    जर (dst->width > hwfc->width || dst->height > hwfc->height)
        परत AVERROR(EINVAL);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    जर (err)
        जा fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    जर (err)
        जा fail;

    err = 0;
fail:
    av_frame_free(&map);
    परत err;
}

स्थिर पूर्णांक vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, स्थिरांक AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    जर (src->width > hwfc->width || src->height > hwfc->height)
        परत AVERROR(EINVAL);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    जर (err)
        जा fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    जर (err)
        जा fail;

    err = 0;
fail:
    av_frame_free(&map);
    परत err;
}

स्थिर पूर्णांक vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               स्थिरांक AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    जर (err)
        परत err;

    err = av_frame_copy_props(dst, src);
    जर (err)
        परत err;

    परत 0;
}

#जर CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
स्थिर स्थिरांक संरचना {
    uint32_t va_fourcc;
    पूर्णांक   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#जर defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#जर defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#जर defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#जर defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#जर defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#जर defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
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

स्थिर पूर्णांक vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              स्थिरांक AVFrame *src, पूर्णांक flags)
{
#जर VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    पूर्णांक use_prime2;
#अन्यथा
    पूर्णांक k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    स्थिरांक AVDRMFrameDescriptor *desc;
    स्थिरांक VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    पूर्णांक err, i, j;

#जर !VA_CHECK_VERSION(1, 1, 0)
    अचिन्हित दीर्घ buffer_handle;
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

    जर (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        परत AVERROR(EINVAL);
    }

    va_fourcc = 0;
    साठी (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        जर (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            सुरूठेवा;
        साठी (j = 0; j < desc->nb_layers; j++) {
            जर (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                थांबा;
        }
        जर (j != desc->nb_layers)
            सुरूठेवा;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        थांबा;
    }
    जर (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        परत AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#जर VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->मूळसंख्या_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    जर (use_prime2) {
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
        साठी (i = 0; i < desc->nb_objects; ++i) {
            मूळसंख्या_desc.objects[i].fd = desc->objects[i].fd;
            मूळसंख्या_desc.objects[i].size = desc->objects[i].size;
            मूळसंख्या_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        मूळसंख्या_desc.अंक_layers = desc->nb_layers;
        साठी (i = 0; i < desc->nb_layers; ++i) {
            मूळसंख्या_desc.layers[i].drm_format = desc->layers[i].format;
            मूळसंख्या_desc.layers[i].अंक_planes = desc->layers[i].nb_planes;
            साठी (j = 0; j < desc->layers[i].nb_planes; ++j) {
                मूळसंख्या_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                मूळसंख्या_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                मूळसंख्या_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            जर (format_desc->chroma_planes_swapped &&
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
        जर (vas != VA_STATUS_SUCCESS)
            src_vafc->मूळसंख्या_2_import_unsupported = 1;
    }

    जर (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        पूर्णांक k;
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
        साठी (i = 0; i < desc->nb_layers; i++) {
            साठी (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.अंक_planes = k;

        जर (format_desc->chroma_planes_swapped &&
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
    साठी (i = 0; i < desc->nb_layers; i++) {
        साठी (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.अंक_planes = k;

    जर (format_desc->chroma_planes_swapped &&
        buffer_desc.अंक_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        परत AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (शून्य*)(uintptr_t)surface_id);
    जर (err < 0)
        परत err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    परत 0;
}

#जर VA_CHECK_VERSION(1, 1, 0)
स्थिर शून्य vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    पूर्णांक i;

    साठी (i = 0; i < drm_desc->nb_objects; i++)
        बंद(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

स्थिर पूर्णांक vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                स्थिरांक AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = रिक्त;
    uint32_t export_flags;
    पूर्णांक err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    जर (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            परत AVERROR(EIO);
        }
    }

    जर (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या_2,
                                export_flags, &va_desc);
    जर (vas != VA_STATUS_SUCCESS) {
        जर (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            परत AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        परत AVERROR(EIO);
    }

    drm_desc = av_mallocz(आकार(*drm_desc));
    जर (!drm_desc) {
        err = AVERROR(ENOMEM);
        जा fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.अंक_objects;
    साठी (i = 0; i < va_desc.अंक_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.अंक_layers;
    साठी (i = 0; i < va_desc.अंक_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].अंक_planes;
        साठी (j = 0; j < va_desc.layers[i].अंक_planes; j++) {
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
    जर (err < 0)
        जा fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    परत 0;

fail:
    साठी (i = 0; i < va_desc.अंक_objects; i++)
        बंद(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    परत err;
}
#endif

#जर VA_CHECK_VERSION(0, 36, 0)
प्रकारव्याख्या संरचना VAAPIDRMImageBufferMapping {
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
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

स्थिर पूर्णांक vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                स्थिरांक AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = रिक्त;
    VASurfaceID surface_id;
    VAStatus vas;
    पूर्णांक err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(आकार(*mapping));
    जर (!mapping)
        परत AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जा fail;
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        जर (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            थांबा;
    }
    जर (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        जा fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_मूळसंख्या;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    जर (mapping->drm_desc.nb_layers > 1) {
        जर (mapping->drm_desc.nb_layers != mapping->image.अंक_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.अंक_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            जा fail_derived;
        }

        साठी(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
        साठी (p = 0; p < mapping->image.अंक_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जा fail_derived;
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
    जर (err < 0)
        जा fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    परत 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    परत err;
}
#endif

स्थिर पूर्णांक vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            स्थिरांक AVFrame *src, पूर्णांक flags)
{
#जर VA_CHECK_VERSION(1, 1, 0)
    पूर्णांक err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    जर (err != AVERROR(ENOSYS))
        परत err;
#endif
#जर VA_CHECK_VERSION(0, 36, 0)
    परत vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    परत AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

स्थिर पूर्णांक vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        स्थिरांक AVFrame *src, पूर्णांक flags)
{
    निवड (src->format) {
#जर CONFIG_LIBDRM
    स्थिती AV_PIX_FMT_DRM_मूळसंख्या:
        परत vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    पूर्वनिर्धारित:
        परत AVERROR(ENOSYS);
    }
}

स्थिर पूर्णांक vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          स्थिरांक AVFrame *src, पूर्णांक flags)
{
    निवड (dst->format) {
#जर CONFIG_LIBDRM
    स्थिती AV_PIX_FMT_DRM_मूळसंख्या:
        परत vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    पूर्वनिर्धारित:
        परत vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

स्थिर शून्य vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    जर (hwctx->display)
        vaTerminate(hwctx->display);

#जर HAVE_VAAPI_X11
    जर (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#जर HAVE_VAAPI_DRM
    जर (priv->drm_fd >= 0)
        बंद(priv->drm_fd);
#endif

    av_freep(&priv);
}

#जर CONFIG_VAAPI_1
स्थिर शून्य vaapi_device_log_error(शून्य *context, स्थिरांक अक्षर *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

स्थिर शून्य vaapi_device_log_info(शून्य *context, स्थिरांक अक्षर *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

स्थिर पूर्णांक vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    पूर्णांक major, minor;
    VAStatus vas;

#जर CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    जर (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        परत AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    परत 0;
}

स्थिर पूर्णांक vaapi_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                               AVDictionary *opts, पूर्णांक flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = रिक्त;
    स्थिरांक AVDictionaryEntry *ent;
    पूर्णांक try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(आकार(*priv));
    जर (!priv)
        परत AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->मुक्त        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", रिक्त, 0);
    जर (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        जर (!म_भेद(ent->मूल्य, "drm")) {
            try_drm = 1;
        } अन्यथा जर (!म_भेद(ent->मूल्य, "x11")) {
            try_x11 = 1;
        } अन्यथा जर (!म_भेद(ent->मूल्य, "win32")) {
            try_win32 = 1;
        } अन्यथा {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->मूल्य);
            परत AVERROR(EINVAL);
        }
    } अन्यथा {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#जर HAVE_VAAPI_DRM
    पर्यंत (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        पूर्णांक loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        जर (device) {
            priv->drm_fd = खोलो(device, O_RDWR);
            जर (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                थांबा;
            }
        } अन्यथा {
            अक्षर path[64];
            पूर्णांक n, max_devices = 8;
#जर CONFIG_LIBDRM
            drmVersion *info;
            स्थिरांक AVDictionaryEntry *kernel_driver;
            स्थिरांक AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", रिक्त, 0);
            vendor_id = av_dict_get(opts, "vendor_id", रिक्त, 0);
#endif
            साठी (n = 0; n < max_devices; n++) {
                snprintf(path, आकार(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = खोलो(path, O_RDWR);
                जर (priv->drm_fd < 0) {
                    जर (त्रुटि_सं == ENOENT) {
                        जर (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            सुरूठेवा;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } अन्यथा
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    थांबा;
                }
#जर CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                जर (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    बंद(priv->drm_fd);
                    priv->drm_fd = -1;
                    सुरूठेवा;
                }
                जर (kernel_driver) {
                    जर (म_भेद(kernel_driver->मूल्य, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        सुरूठेवा;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    थांबा;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } अन्यथा जर (!म_भेद(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    बंद(priv->drm_fd);
                    priv->drm_fd = -1;
                    सुरूठेवा;
                } अन्यथा जर (vendor_id) {
                    drmDevicePtr device;
                    अक्षर drm_vendor[8];
                    जर (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        सुरूठेवा;
                    }

                    snprintf(drm_vendor, आकार(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    जर (म_भेद(vendor_id->मूल्य, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->मूल्य);
                        drmFreeDevice(&device);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        सुरूठेवा;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->मूल्य);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    थांबा;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                थांबा;
            }
            जर (n >= max_devices)
                थांबा;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        जर (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            परत AVERROR_EXTERNAL;
        }
        थांबा;
    }
#endif

#जर HAVE_VAAPI_X11
    जर (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        जर (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } अन्यथा {
            display = vaGetDisplay(priv->x11_display);
            जर (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                परत AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#जर HAVE_VAAPI_WIN32
    जर (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        जर (!device) {
            display = vaGetDisplayWin32(रिक्त);
        } अन्यथा {
            IDXGIFactory2 *pDXGIFactory = रिक्त;
            IDXGIAdapter *pAdapter = रिक्त;
#जर !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            जर (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                परत AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            जर (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                परत AVERROR_UNKNOWN;
            }
#अन्यथा
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            जर (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (शून्य **)&pDXGIFactory))) {
                पूर्णांक adapter = म_से_प(device);
                जर (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    जर (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
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
#जर !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        जर (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            परत AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    जर (!display) {
        जर (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        अन्यथा
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        परत AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", रिक्त, 0);
    जर (ent) {
#जर VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->मूल्य);
        जर (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->मूल्य, vas, vaErrorStr(vas));
            vaTerminate(display);
            परत AVERROR_EXTERNAL;
        }
#अन्यथा
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    परत vaapi_device_connect(ctx, display);
}

स्थिर पूर्णांक vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, पूर्णांक flags)
{
#जर HAVE_VAAPI_DRM
    जर (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        पूर्णांक fd;

        जर (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            परत AVERROR(EINVAL);
        }

#जर CONFIG_LIBDRM
        {
            पूर्णांक गाठ_type = drm_Get_गाठ_Type_From_Fd(src_hwctx->fd);
            अक्षर *render_गाठ;
            जर (गाठ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                परत AVERROR(EINVAL);
            }
            जर (गाठ_type == DRM_गाठ_RENDER) {
                fd = src_hwctx->fd;
            } अन्यथा {
                render_गाठ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                जर (!render_गाठ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } अन्यथा {
                    fd = खोलो(render_गाठ, O_RDWR);
                    जर (fd < 0) {
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

        priv = av_mallocz(आकार(*priv));
        जर (!priv) {
            जर (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                बंद(fd);
            }
            परत AVERROR(ENOMEM);
        }

        जर (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } अन्यथा {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->मुक्त        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        जर (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            परत AVERROR(EIO);
        }

        परत vaapi_device_connect(ctx, display);
    }
#endif
    परत AVERROR(ENOSYS);
}

स्थिरांक HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = आकार(VAAPIDeviceContext),
    .device_hwconfig_size   = आकार(AVVAAPIHWConfig),
    .frames_hwctx_size      = आकार(VAAPIFramesContext),

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

    .pix_fmts = (स्थिरांक गणना AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
