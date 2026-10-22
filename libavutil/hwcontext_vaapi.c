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

#அந்தர்பாவ "config.h"

#எனில் HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
வகைவரை HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, வெறுமை **ppFactory);
#endif
#எனில் HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#எனில் HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#எனில் CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#அந்தர்பாவ <fcntl.h>
#எனில் HAVE_UNISTD_H
#   include <unistd.h>
#endif


#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_drm.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_vaapi.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "pixfmt.h"


வகைவரை கட்டமைப்பு VAAPIDevicePriv {
#எனில் HAVE_VAAPI_X11
    Display *x11_display;
#endif

    முழு drm_fd;
} VAAPIDevicePriv;

வகைவரை கட்டமைப்பு VAAPISurfaceFormat {
    எண்ணிக்கை AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned முழு fourcc;
} VAAPISurfaceFormat;

வகைவரை கட்டமைப்பு VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    முழு              nb_formats;
} VAAPIDeviceContext;

வகைவரை கட்டமைப்பு VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    முழு           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned முழு rt_format;
    // Whether vaDeriveImage works.
    முழு derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    முழு பகாஎண்_2_import_unsupported;
} VAAPIFramesContext;

வகைவரை கட்டமைப்பு VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    முழு flags;
} VAAPIMapping;

வகைவரை கட்டமைப்பு VAAPIFormat {
    unsigned முழு fourcc;
    unsigned முழு rt_format;
    எண்ணிக்கை AVPixelFormat pix_fmt;
    முழு chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
நிலையான மாறிலி VAAPIFormatDescriptor vaapi_format_map[] = {
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

நிலையான மாறிலி VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned முழு fourcc)
{
    முழு i;
    க்கு (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        எனில் (vaapi_format_map[i].fourcc == fourcc)
            திரும்பு &vaapi_format_map[i];
    திரும்பு வெற்று;
}

நிலையான மாறிலி VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(எண்ணிக்கை AVPixelFormat pix_fmt, மாறிலி VAAPIFormatDescriptor *prev)
{
    மாறிலி VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    எனில் (!prev)
        prev = vaapi_format_map;
    இல்லையெனில்
        prev++;

    க்கு (; prev < end; prev++)
        எனில் (prev->pix_fmt == pix_fmt)
            திரும்பு prev;
    திரும்பு வெற்று;
}

நிலையான எண்ணிக்கை AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned முழு fourcc)
{
    மாறிலி VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    எனில் (desc)
        திரும்பு desc->pix_fmt;
    இல்லையெனில்
        திரும்பு AV_PIX_FMT_NONE;
}

நிலையான முழு vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  எண்ணிக்கை AVPixelFormat pix_fmt,
                                  மாறிலி VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    மாறிலி VAAPIFormatDescriptor *desc = வெற்று;
    முழு i;

    போது ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        க்கு (i = 0; i < ctx->nb_formats; i++) {
            எனில் (ctx->formats[i].fourcc == desc->fourcc) {
                எனில் (_desc)
                    *_desc = desc;
                எனில் (image_format)
                    *image_format = &ctx->formats[i].image_format;
                திரும்பு 0;
            }
        }
    }

    திரும்பு AVERROR(ENOSYS);
}

நிலையான முழு vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  எண்ணிக்கை AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    எனில் (!image_format)
        திரும்பு AVERROR(EINVAL);
    திரும்பு vaapi_get_img_desc_and_format(hwdev, pix_fmt, வெற்று, image_format);
}

நிலையான முழு vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        மாறிலி வெறுமை *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    மாறிலி AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = வெற்று;
    VAStatus vas;
    எண்ணிக்கை AVPixelFormat pix_fmt;
    unsigned முழு fourcc;
    முழு err, i, j, attr_மொத்தம், pix_fmt_மொத்தம்;

    எனில் (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_மொத்தம் = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_மொத்தம்);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            செல் fail;
        }

        attr_list = av_malloc(attr_மொத்தம் * அளவு(*attr_list));
        எனில் (!attr_list) {
            err = AVERROR(ENOMEM);
            செல் fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_மொத்தம்);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            செல் fail;
        }

        pix_fmt_மொத்தம் = 0;
        க்கு (i = 0; i < attr_மொத்தம்; i++) {
            தேர்வு (attr_list[i].type) {
            நிலை VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].மதிப்பு.மதிப்பு.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                எனில் (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_மொத்தம்;
                } இல்லையெனில் {
                    // Something unsupported - ignore.
                }
                நிறுத்து;
            நிலை VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].மதிப்பு.மதிப்பு.i;
                நிறுத்து;
            நிலை VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].மதிப்பு.மதிப்பு.i;
                நிறுத்து;
            நிலை VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].மதிப்பு.மதிப்பு.i;
                நிறுத்து;
            நிலை VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].மதிப்பு.மதிப்பு.i;
                நிறுத்து;
            }
        }
        எனில் (pix_fmt_மொத்தம் == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = வெற்று;
        } இல்லையெனில் {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_மொத்தம் + 1,
                                                            அளவு(pix_fmt));
            எனில் (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                செல் fail;
            }

            க்கு (i = j = 0; i < attr_மொத்தம்; i++) {
                முழு k;

                எனில் (attr_list[i].type != VASurfaceAttribPixelFormat)
                    தொடர்;
                fourcc = attr_list[i].மதிப்பு.மதிப்பு.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                எனில் (pix_fmt == AV_PIX_FMT_NONE)
                    தொடர்;

                க்கு (k = 0; k < j; k++) {
                    எனில் (constraints->valid_sw_formats[k] == pix_fmt)
                        நிறுத்து;
                }

                எனில் (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } இல்லையெனில் {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        அளவு(pix_fmt));
        எனில் (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            செல் fail;
        }
        க்கு (i = j = 0; i < ctx->nb_formats; i++) {
            முழு k;

            க்கு (k = 0; k < j; k++) {
                எனில் (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    நிறுத்து;
            }

            எனில் (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, அளவு(pix_fmt));
    எனில் (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    திரும்பு err;
}

நிலையான மாறிலி கட்டமைப்பு {
    மாறிலி எழுத்து *friendly_name;
    மாறிலி எழுத்து *match_string;
    unsigned முழு quirks;
} vaapi_driver_quirks_table[] = {
#எனில் !VA_CHECK_VERSION(1, 0, 0)
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

நிலையான முழு vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = வெற்று;
    VAStatus vas;
    மாறிலி எழுத்து *vendor_string;
    முழு err, i, image_மொத்தம்;
    எண்ணிக்கை AVPixelFormat pix_fmt;
    unsigned முழு fourcc;

    image_மொத்தம் = va_Max_இலக்கம்_Image_Formats(hwctx->display);
    எனில் (image_மொத்தம் <= 0) {
        err = AVERROR(EIO);
        செல் fail;
    }
    image_list = av_malloc(image_மொத்தம் * அளவு(*image_list));
    எனில் (!image_list) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_மொத்தம்);
    எனில் (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        செல் fail;
    }

    ctx->formats  = av_malloc(image_மொத்தம் * அளவு(*ctx->formats));
    எனில் (!ctx->formats) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }
    ctx->nb_formats = 0;
    க்கு (i = 0; i < image_மொத்தம்; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        எனில் (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } இல்லையெனில் {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    எனில் (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    எனில் (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } இல்லையெனில் {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        எனில் (vendor_string) {
            க்கு (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                எனில் (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    நிறுத்து;
                }
            }
            எனில் (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } இல்லையெனில் {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    திரும்பு 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    திரும்பு err;
}

நிலையான வெறுமை vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

நிலையான வெறுமை vaapi_buffer_free(வெறுமை *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

நிலையான AVBufferRef *vaapi_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    எனில் (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        திரும்பு வெற்று;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        திரும்பு வெற்று;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           அளவு(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    எனில் (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        திரும்பு வெற்று;
    }

    எனில் (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    திரும்பு ref;
}

நிலையான முழு vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    மாறிலி VAAPIFormatDescriptor *desc = வெற்று;
    VAImageFormat *expected_format = வெற்று;
    AVBufferRef *test_surface = வெற்று;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    முழு err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    எனில் (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        எனில் (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, வெற்று)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            திரும்பு AVERROR(EINVAL);
        }
    }

    எனில் (!hwfc->pool) {
        எனில் (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            முழு need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            முழு need_pixel_format = 1;
            க்கு (i = 0; i < avfc->nb_attributes; i++) {
                எனில் (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                எனில் (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        அளவு(*ctx->attributes));
            எனில் (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                செல் fail;
            }

            க்கு (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            எனில் (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Integer,
                    .மதிப்பு.மதிப்பு.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            எனில் (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Integer,
                    .மதிப்பு.மதிப்பு.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } இல்லையெனில் {
            ctx->attributes = வெற்று;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        எனில் (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          அளவு(*avfc->surface_ids));
            எனில் (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                செல் fail;
            }
        } இல்லையெனில் {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = வெற்று;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(அளவு(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, வெற்று);
        எனில் (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            செல் fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    எனில் (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        எனில் (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            செல் fail;
        }
    } இல்லையெனில் {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        எனில் (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            செல் fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    எனில் (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        எனில் (vas == VA_STATUS_SUCCESS) {
            எனில் (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } இல்லையெனில் {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } இல்லையெனில் {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } இல்லையெனில் {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    திரும்பு 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    திரும்பு err;
}

நிலையான வெறுமை vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

நிலையான முழு vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    திரும்பு 0;
}

நிலையான முழு vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      எண்ணிக்கை AVHWFrameTransferDirection dir,
                                      எண்ணிக்கை AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    எண்ணிக்கை AVPixelFormat *pix_fmts;
    முழு i, k, sw_format_available;

    sw_format_available = 0;
    க்கு (i = 0; i < ctx->nb_formats; i++) {
        எனில் (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * அளவு(*pix_fmts));
    எனில் (!pix_fmts)
        திரும்பு AVERROR(ENOMEM);

    எனில் (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } இல்லையெனில் {
        k = 0;
    }
    க்கு (i = 0; i < ctx->nb_formats; i++) {
        எனில் (ctx->formats[i].pix_fmt == hwfc->sw_format)
            தொடர்;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    திரும்பு 0;
}

நிலையான வெறுமை vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    எனில் ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

நிலையான முழு vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    மாறிலி VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    வெறுமை *address = வெற்று;
    முழு err, i;
#எனில் VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    எனில் (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        திரும்பு AVERROR(EINVAL);
    }
    எனில் (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    எனில் (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        திரும்பு AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    எனில் (err < 0) {
        // Requested format is not a valid output format.
        திரும்பு err;
    }

    map = av_malloc(அளவு(*map));
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        செல் fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    எனில் (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            செல் fail;
        }
        எனில் (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            செல் fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } இல்லையெனில் {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            செல் fail;
        }
        எனில் (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            எனில் (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                செல் fail;
            }
        }
    }

#எனில் VA_CHECK_VERSION(1, 21, 0)
    எனில் (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    எனில் (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#இல்லையெனில்
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        செல் fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    க்கு (i = 0; i < map->image.இலக்கம்_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    எனில் (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    திரும்பு 0;

fail:
    எனில் (map) {
        எனில் (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        எனில் (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    திரும்பு err;
}

நிலையான முழு vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (dst->width > hwfc->width || dst->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    எனில் (err)
        செல் fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (src->width > hwfc->width || src->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    எனில் (err)
        செல் fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               மாறிலி AVFrame *src, முழு flags)
{
    முழு err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    எனில் (err)
        திரும்பு err;

    err = av_frame_copy_props(dst, src);
    எனில் (err)
        திரும்பு err;

    திரும்பு 0;
}

#எனில் CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
நிலையான மாறிலி கட்டமைப்பு {
    uint32_t va_fourcc;
    முழு   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#எனில் defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#எனில் defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#எனில் defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#எனில் defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#எனில் defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#எனில் defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

நிலையான வெறுமை vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

நிலையான முழு vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              மாறிலி AVFrame *src, முழு flags)
{
#எனில் VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    முழு use_prime2;
#இல்லையெனில்
    முழு k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    மாறிலி AVDRMFrameDescriptor *desc;
    மாறிலி VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    முழு err, i, j;

#எனில் !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Integer,
            .மதிப்பு.மதிப்பு.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_பகாஎண்,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Pointer,
            .மதிப்பு.மதிப்பு.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    எனில் (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        திரும்பு AVERROR(EINVAL);
    }

    va_fourcc = 0;
    க்கு (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        எனில் (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            தொடர்;
        க்கு (j = 0; j < desc->nb_layers; j++) {
            எனில் (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                நிறுத்து;
        }
        எனில் (j != desc->nb_layers)
            தொடர்;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        நிறுத்து;
    }
    எனில் (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        திரும்பு AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#எனில் VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->பகாஎண்_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    எனில் (use_prime2) {
        VADRMPRIMESurfaceDescriptor பகாஎண்_desc;
        VASurfaceAttrib பகாஎண்_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Integer,
                .மதிப்பு.மதிப்பு.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_பகாஎண்_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Pointer,
                .மதிப்பு.மதிப்பு.p = &பகாஎண்_desc,
            }
        };
        பகாஎண்_desc.fourcc = va_fourcc;
        பகாஎண்_desc.width = src_fc->width;
        பகாஎண்_desc.height = src_fc->height;
        பகாஎண்_desc.இலக்கம்_objects = desc->nb_objects;
        க்கு (i = 0; i < desc->nb_objects; ++i) {
            பகாஎண்_desc.objects[i].fd = desc->objects[i].fd;
            பகாஎண்_desc.objects[i].size = desc->objects[i].size;
            பகாஎண்_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        பகாஎண்_desc.இலக்கம்_layers = desc->nb_layers;
        க்கு (i = 0; i < desc->nb_layers; ++i) {
            பகாஎண்_desc.layers[i].drm_format = desc->layers[i].format;
            பகாஎண்_desc.layers[i].இலக்கம்_planes = desc->layers[i].nb_planes;
            க்கு (j = 0; j < desc->layers[i].nb_planes; ++j) {
                பகாஎண்_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                பகாஎண்_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                பகாஎண்_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            எனில் (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, பகாஎண்_desc.layers[i].pitch[1],
                    பகாஎண்_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, பகாஎண்_desc.layers[i].offset[1],
                    பகாஎண்_desc.layers[i].offset[2]);
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
                               பகாஎண்_attrs, FF_ARRAY_ELEMS(பகாஎண்_attrs));
        எனில் (vas != VA_STATUS_SUCCESS)
            src_vafc->பகாஎண்_2_import_unsupported = 1;
    }

    எனில் (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        முழு k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Integer,
                .மதிப்பு.மதிப்பு.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_பகாஎண்,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .மதிப்பு.type    = VAGeneric_மதிப்பு_Type_Pointer,
                .மதிப்பு.மதிப்பு.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.இலக்கம்_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        க்கு (i = 0; i < desc->nb_layers; i++) {
            க்கு (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.இலக்கம்_planes = k;

        எனில் (format_desc->chroma_planes_swapped &&
            buffer_desc.இலக்கம்_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#இல்லையெனில்
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.இலக்கம்_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    க்கு (i = 0; i < desc->nb_layers; i++) {
        க்கு (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.இலக்கம்_planes = k;

    எனில் (format_desc->chroma_planes_swapped &&
        buffer_desc.இலக்கம்_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        திரும்பு AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (வெறுமை*)(uintptr_t)surface_id);
    எனில் (err < 0)
        திரும்பு err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    திரும்பு 0;
}

#எனில் VA_CHECK_VERSION(1, 1, 0)
நிலையான வெறுமை vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    முழு i;

    க்கு (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

நிலையான முழு vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                மாறிலி AVFrame *src, முழு flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = வெற்று;
    uint32_t export_flags;
    முழு err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    எனில் (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            திரும்பு AVERROR(EIO);
        }
    }

    எனில் (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_பகாஎண்_2,
                                export_flags, &va_desc);
    எனில் (vas != VA_STATUS_SUCCESS) {
        எனில் (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            திரும்பு AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        திரும்பு AVERROR(EIO);
    }

    drm_desc = av_mallocz(அளவு(*drm_desc));
    எனில் (!drm_desc) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.இலக்கம்_objects;
    க்கு (i = 0; i < va_desc.இலக்கம்_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.இலக்கம்_layers;
    க்கு (i = 0; i < va_desc.இலக்கம்_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].இலக்கம்_planes;
        க்கு (j = 0; j < va_desc.layers[i].இலக்கம்_planes; j++) {
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
    எனில் (err < 0)
        செல் fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    திரும்பு 0;

fail:
    க்கு (i = 0; i < va_desc.இலக்கம்_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    திரும்பு err;
}
#endif

#எனில் VA_CHECK_VERSION(0, 36, 0)
வகைவரை கட்டமைப்பு VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

நிலையான வெறுமை vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

நிலையான முழு vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                மாறிலி AVFrame *src, முழு flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = வெற்று;
    VASurfaceID surface_id;
    VAStatus vas;
    முழு err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(அளவு(*mapping));
    எனில் (!mapping)
        திரும்பு AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        செல் fail;
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        எனில் (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            நிறுத்து;
    }
    எனில் (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        செல் fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_பகாஎண்;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    எனில் (mapping->drm_desc.nb_layers > 1) {
        எனில் (mapping->drm_desc.nb_layers != mapping->image.இலக்கம்_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.இலக்கம்_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            செல் fail_derived;
        }

        க்கு(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } இல்லையெனில் {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.இலக்கம்_planes;
        க்கு (p = 0; p < mapping->image.இலக்கம்_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        செல் fail_derived;
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
    எனில் (err < 0)
        செல் fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    திரும்பு 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    திரும்பு err;
}
#endif

நிலையான முழு vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            மாறிலி AVFrame *src, முழு flags)
{
#எனில் VA_CHECK_VERSION(1, 1, 0)
    முழு err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    எனில் (err != AVERROR(ENOSYS))
        திரும்பு err;
#endif
#எனில் VA_CHECK_VERSION(0, 36, 0)
    திரும்பு vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    திரும்பு AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

நிலையான முழு vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        மாறிலி AVFrame *src, முழு flags)
{
    தேர்வு (src->format) {
#எனில் CONFIG_LIBDRM
    நிலை AV_PIX_FMT_DRM_பகாஎண்:
        திரும்பு vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }
}

நிலையான முழு vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          மாறிலி AVFrame *src, முழு flags)
{
    தேர்வு (dst->format) {
#எனில் CONFIG_LIBDRM
    நிலை AV_PIX_FMT_DRM_பகாஎண்:
        திரும்பு vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    இயல்பு:
        திரும்பு vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

நிலையான வெறுமை vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    எனில் (hwctx->display)
        vaTerminate(hwctx->display);

#எனில் HAVE_VAAPI_X11
    எனில் (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#எனில் HAVE_VAAPI_DRM
    எனில் (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#எனில் CONFIG_VAAPI_1
நிலையான வெறுமை vaapi_device_log_error(வெறுமை *context, மாறிலி எழுத்து *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

நிலையான வெறுமை vaapi_device_log_info(வெறுமை *context, மாறிலி எழுத்து *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

நிலையான முழு vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    முழு major, minor;
    VAStatus vas;

#எனில் CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    எனில் (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        திரும்பு AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    திரும்பு 0;
}

நிலையான முழு vaapi_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                               AVDictionary *opts, முழு flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = வெற்று;
    மாறிலி AVDictionaryEntry *ent;
    முழு try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(அளவு(*priv));
    எனில் (!priv)
        திரும்பு AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->விடுவி        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", வெற்று, 0);
    எனில் (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        எனில் (!strcmp(ent->மதிப்பு, "drm")) {
            try_drm = 1;
        } இல்லையெனில் எனில் (!strcmp(ent->மதிப்பு, "x11")) {
            try_x11 = 1;
        } இல்லையெனில் எனில் (!strcmp(ent->மதிப்பு, "win32")) {
            try_win32 = 1;
        } இல்லையெனில் {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->மதிப்பு);
            திரும்பு AVERROR(EINVAL);
        }
    } இல்லையெனில் {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#எனில் HAVE_VAAPI_DRM
    போது (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        முழு loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        எனில் (device) {
            priv->drm_fd = open(device, O_RDWR);
            எனில் (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                நிறுத்து;
            }
        } இல்லையெனில் {
            எழுத்து path[64];
            முழு n, max_devices = 8;
#எனில் CONFIG_LIBDRM
            drmVersion *info;
            மாறிலி AVDictionaryEntry *kernel_driver;
            மாறிலி AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", வெற்று, 0);
            vendor_id = av_dict_get(opts, "vendor_id", வெற்று, 0);
#endif
            க்கு (n = 0; n < max_devices; n++) {
                snprintf(path, அளவு(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                எனில் (priv->drm_fd < 0) {
                    எனில் (errno == ENOENT) {
                        எனில் (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            தொடர்;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } இல்லையெனில்
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    நிறுத்து;
                }
#எனில் CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                எனில் (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    தொடர்;
                }
                எனில் (kernel_driver) {
                    எனில் (strcmp(kernel_driver->மதிப்பு, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        தொடர்;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    நிறுத்து;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } இல்லையெனில் எனில் (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    தொடர்;
                } இல்லையெனில் எனில் (vendor_id) {
                    drmDevicePtr device;
                    எழுத்து drm_vendor[8];
                    எனில் (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        தொடர்;
                    }

                    snprintf(drm_vendor, அளவு(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    எனில் (strcmp(vendor_id->மதிப்பு, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->மதிப்பு);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        தொடர்;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->மதிப்பு);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    நிறுத்து;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                நிறுத்து;
            }
            எனில் (n >= max_devices)
                நிறுத்து;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        எனில் (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            திரும்பு AVERROR_EXTERNAL;
        }
        நிறுத்து;
    }
#endif

#எனில் HAVE_VAAPI_X11
    எனில் (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        எனில் (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } இல்லையெனில் {
            display = vaGetDisplay(priv->x11_display);
            எனில் (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                திரும்பு AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#எனில் HAVE_VAAPI_WIN32
    எனில் (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        எனில் (!device) {
            display = vaGetDisplayWin32(வெற்று);
        } இல்லையெனில் {
            IDXGIFactory2 *pDXGIFactory = வெற்று;
            IDXGIAdapter *pAdapter = வெற்று;
#எனில் !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            எனில் (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                திரும்பு AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            எனில் (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                திரும்பு AVERROR_UNKNOWN;
            }
#இல்லையெனில்
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            எனில் (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (வெறுமை **)&pDXGIFactory))) {
                முழு adapter = atoi(device);
                எனில் (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    எனில் (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.கீழ்_Part,
                              desc.AdapterLuid.உயர்வு_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#எனில் !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        எனில் (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            திரும்பு AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    எனில் (!display) {
        எனில் (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        இல்லையெனில்
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        திரும்பு AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", வெற்று, 0);
    எனில் (ent) {
#எனில் VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->மதிப்பு);
        எனில் (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->மதிப்பு, vas, vaErrorStr(vas));
            vaTerminate(display);
            திரும்பு AVERROR_EXTERNAL;
        }
#இல்லையெனில்
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    திரும்பு vaapi_device_connect(ctx, display);
}

நிலையான முழு vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, முழு flags)
{
#எனில் HAVE_VAAPI_DRM
    எனில் (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        முழு fd;

        எனில் (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            திரும்பு AVERROR(EINVAL);
        }

#எனில் CONFIG_LIBDRM
        {
            முழு முனை_type = drm_Get_முனை_Type_From_Fd(src_hwctx->fd);
            எழுத்து *render_முனை;
            எனில் (முனை_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                திரும்பு AVERROR(EINVAL);
            }
            எனில் (முனை_type == DRM_முனை_RENDER) {
                fd = src_hwctx->fd;
            } இல்லையெனில் {
                render_முனை = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                எனில் (!render_முனை) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } இல்லையெனில் {
                    fd = open(render_முனை, O_RDWR);
                    எனில் (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } இல்லையெனில் {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_முனை);
                    }
                    விடுவி(render_முனை);
                }
            }
        }
#இல்லையெனில்
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(அளவு(*priv));
        எனில் (!priv) {
            எனில் (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            திரும்பு AVERROR(ENOMEM);
        }

        எனில் (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } இல்லையெனில் {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->விடுவி        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        எனில் (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            திரும்பு AVERROR(EIO);
        }

        திரும்பு vaapi_device_connect(ctx, display);
    }
#endif
    திரும்பு AVERROR(ENOSYS);
}

மாறிலி HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = அளவு(VAAPIDeviceContext),
    .device_hwconfig_size   = அளவு(AVVAAPIHWConfig),
    .frames_hwctx_size      = அளவு(VAAPIFramesContext),

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

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
