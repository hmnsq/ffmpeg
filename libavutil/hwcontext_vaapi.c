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

#અન્તર્ભાવ "config.h"

#જો HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
પ્રકારવ્યાખ્યા HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, શૂન્ય **ppFactory);
#endif
#જો HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#જો HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#જો CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#અન્તર્ભાવ <fcntl.h>
#જો HAVE_UNISTD_H
#   include <unistd.h>
#endif


#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_drm.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_vaapi.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "pixfmt.h"


પ્રકારવ્યાખ્યા સંરચના VAAPIDevicePriv {
#જો HAVE_VAAPI_X11
    Display *x11_display;
#endif

    પૂર્ણાંક drm_fd;
} VAAPIDevicePriv;

પ્રકારવ્યાખ્યા સંરચના VAAPISurfaceFormat {
    ગણના AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned પૂર્ણાંક fourcc;
} VAAPISurfaceFormat;

પ્રકારવ્યાખ્યા સંરચના VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    પૂર્ણાંક              nb_formats;
} VAAPIDeviceContext;

પ્રકારવ્યાખ્યા સંરચના VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    પૂર્ણાંક           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned પૂર્ણાંક rt_format;
    // Whether vaDeriveImage works.
    પૂર્ણાંક derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    પૂર્ણાંક અવિભાજ્ય_2_import_unsupported;
} VAAPIFramesContext;

પ્રકારવ્યાખ્યા સંરચના VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    પૂર્ણાંક flags;
} VAAPIMapping;

પ્રકારવ્યાખ્યા સંરચના VAAPIFormat {
    unsigned પૂર્ણાંક fourcc;
    unsigned પૂર્ણાંક rt_format;
    ગણના AVPixelFormat pix_fmt;
    પૂર્ણાંક chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
સ્થિર અચલ VAAPIFormatDescriptor vaapi_format_map[] = {
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

સ્થિર અચલ VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned પૂર્ણાંક fourcc)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        જો (vaapi_format_map[i].fourcc == fourcc)
            પાછા &vaapi_format_map[i];
    પાછા ખાલી;
}

સ્થિર અચલ VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(ગણના AVPixelFormat pix_fmt, અચલ VAAPIFormatDescriptor *prev)
{
    અચલ VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    જો (!prev)
        prev = vaapi_format_map;
    નહીંતર
        prev++;

    માટે (; prev < end; prev++)
        જો (prev->pix_fmt == pix_fmt)
            પાછા prev;
    પાછા ખાલી;
}

સ્થિર ગણના AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned પૂર્ણાંક fourcc)
{
    અચલ VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    જો (desc)
        પાછા desc->pix_fmt;
    નહીંતર
        પાછા AV_PIX_FMT_NONE;
}

સ્થિર પૂર્ણાંક vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  ગણના AVPixelFormat pix_fmt,
                                  અચલ VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    અચલ VAAPIFormatDescriptor *desc = ખાલી;
    પૂર્ણાંક i;

    જ્યારે ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        માટે (i = 0; i < ctx->nb_formats; i++) {
            જો (ctx->formats[i].fourcc == desc->fourcc) {
                જો (_desc)
                    *_desc = desc;
                જો (image_format)
                    *image_format = &ctx->formats[i].image_format;
                પાછા 0;
            }
        }
    }

    પાછા AVERROR(ENOSYS);
}

સ્થિર પૂર્ણાંક vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  ગણના AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    જો (!image_format)
        પાછા AVERROR(EINVAL);
    પાછા vaapi_get_img_desc_and_format(hwdev, pix_fmt, ખાલી, image_format);
}

સ્થિર પૂર્ણાંક vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        અચલ શૂન્ય *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    અચલ AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = ખાલી;
    VAStatus vas;
    ગણના AVPixelFormat pix_fmt;
    unsigned પૂર્ણાંક fourcc;
    પૂર્ણાંક err, i, j, attr_ગણતરી, pix_fmt_ગણતરી;

    જો (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_ગણતરી = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_ગણતરી);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            જાઓ fail;
        }

        attr_list = av_malloc(attr_ગણતરી * કદ(*attr_list));
        જો (!attr_list) {
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_ગણતરી);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            જાઓ fail;
        }

        pix_fmt_ગણતરી = 0;
        માટે (i = 0; i < attr_ગણતરી; i++) {
            પસંદગી (attr_list[i].type) {
            સ્થિતિ VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].કિંમત.કિંમત.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                જો (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_ગણતરી;
                } નહીંતર {
                    // Something unsupported - ignore.
                }
                તોડો;
            સ્થિતિ VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].કિંમત.કિંમત.i;
                તોડો;
            સ્થિતિ VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].કિંમત.કિંમત.i;
                તોડો;
            સ્થિતિ VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].કિંમત.કિંમત.i;
                તોડો;
            સ્થિતિ VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].કિંમત.કિંમત.i;
                તોડો;
            }
        }
        જો (pix_fmt_ગણતરી == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = ખાલી;
        } નહીંતર {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_ગણતરી + 1,
                                                            કદ(pix_fmt));
            જો (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                જાઓ fail;
            }

            માટે (i = j = 0; i < attr_ગણતરી; i++) {
                પૂર્ણાંક k;

                જો (attr_list[i].type != VASurfaceAttribPixelFormat)
                    ચાલુ;
                fourcc = attr_list[i].કિંમત.કિંમત.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                જો (pix_fmt == AV_PIX_FMT_NONE)
                    ચાલુ;

                માટે (k = 0; k < j; k++) {
                    જો (constraints->valid_sw_formats[k] == pix_fmt)
                        તોડો;
                }

                જો (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } નહીંતર {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        કદ(pix_fmt));
        જો (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }
        માટે (i = j = 0; i < ctx->nb_formats; i++) {
            પૂર્ણાંક k;

            માટે (k = 0; k < j; k++) {
                જો (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    તોડો;
            }

            જો (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, કદ(pix_fmt));
    જો (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    પાછા err;
}

સ્થિર અચલ સંરચના {
    અચલ અક્ષર *friendly_name;
    અચલ અક્ષર *match_string;
    unsigned પૂર્ણાંક quirks;
} vaapi_driver_quirks_table[] = {
#જો !VA_CHECK_VERSION(1, 0, 0)
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

સ્થિર પૂર્ણાંક vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = ખાલી;
    VAStatus vas;
    અચલ અક્ષર *vendor_string;
    પૂર્ણાંક err, i, image_ગણતરી;
    ગણના AVPixelFormat pix_fmt;
    unsigned પૂર્ણાંક fourcc;

    image_ગણતરી = va_Max_અંક_Image_Formats(hwctx->display);
    જો (image_ગણતરી <= 0) {
        err = AVERROR(EIO);
        જાઓ fail;
    }
    image_list = av_malloc(image_ગણતરી * કદ(*image_list));
    જો (!image_list) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_ગણતરી);
    જો (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        જાઓ fail;
    }

    ctx->formats  = av_malloc(image_ગણતરી * કદ(*ctx->formats));
    જો (!ctx->formats) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }
    ctx->nb_formats = 0;
    માટે (i = 0; i < image_ગણતરી; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        જો (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } નહીંતર {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    જો (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    જો (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } નહીંતર {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        જો (vendor_string) {
            માટે (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                જો (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    તોડો;
                }
            }
            જો (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } નહીંતર {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    પાછા 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    પાછા err;
}

સ્થિર શૂન્ય vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

સ્થિર શૂન્ય vaapi_buffer_free(શૂન્ય *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

સ્થિર AVBufferRef *vaapi_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    જો (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        પાછા ખાલી;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        પાછા ખાલી;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           કદ(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    જો (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        પાછા ખાલી;
    }

    જો (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    પાછા ref;
}

સ્થિર પૂર્ણાંક vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    અચલ VAAPIFormatDescriptor *desc = ખાલી;
    VAImageFormat *expected_format = ખાલી;
    AVBufferRef *test_surface = ખાલી;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    પૂર્ણાંક err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    જો (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        જો (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, ખાલી)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            પાછા AVERROR(EINVAL);
        }
    }

    જો (!hwfc->pool) {
        જો (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            પૂર્ણાંક need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            પૂર્ણાંક need_pixel_format = 1;
            માટે (i = 0; i < avfc->nb_attributes; i++) {
                જો (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                જો (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        કદ(*ctx->attributes));
            જો (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                જાઓ fail;
            }

            માટે (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            જો (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .કિંમત.type    = VAGeneric_કિંમત_Type_Integer,
                    .કિંમત.કિંમત.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            જો (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .કિંમત.type    = VAGeneric_કિંમત_Type_Integer,
                    .કિંમત.કિંમત.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } નહીંતર {
            ctx->attributes = ખાલી;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        જો (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          કદ(*avfc->surface_ids));
            જો (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                જાઓ fail;
            }
        } નહીંતર {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = ખાલી;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(કદ(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, ખાલી);
        જો (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    જો (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        જો (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }
    } નહીંતર {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        જો (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    જો (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        જો (vas == VA_STATUS_SUCCESS) {
            જો (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } નહીંતર {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } નહીંતર {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } નહીંતર {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    પાછા 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    પાછા err;
}

સ્થિર શૂન્ય vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

સ્થિર પૂર્ણાંક vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    પાછા 0;
}

સ્થિર પૂર્ણાંક vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      ગણના AVHWFrameTransferDirection dir,
                                      ગણના AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    ગણના AVPixelFormat *pix_fmts;
    પૂર્ણાંક i, k, sw_format_available;

    sw_format_available = 0;
    માટે (i = 0; i < ctx->nb_formats; i++) {
        જો (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * કદ(*pix_fmts));
    જો (!pix_fmts)
        પાછા AVERROR(ENOMEM);

    જો (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } નહીંતર {
        k = 0;
    }
    માટે (i = 0; i < ctx->nb_formats; i++) {
        જો (ctx->formats[i].pix_fmt == hwfc->sw_format)
            ચાલુ;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    પાછા 0;
}

સ્થિર શૂન્ય vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    જો ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

સ્થિર પૂર્ણાંક vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    અચલ VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    શૂન્ય *address = ખાલી;
    પૂર્ણાંક err, i;
#જો VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    જો (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        પાછા AVERROR(EINVAL);
    }
    જો (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    જો (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        પાછા AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    જો (err < 0) {
        // Requested format is not a valid output format.
        પાછા err;
    }

    map = av_malloc(કદ(*map));
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        જાઓ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    જો (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            જાઓ fail;
        }
        જો (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            જાઓ fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } નહીંતર {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            જાઓ fail;
        }
        જો (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            જો (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                જાઓ fail;
            }
        }
    }

#જો VA_CHECK_VERSION(1, 21, 0)
    જો (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    જો (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#નહીંતર
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        જાઓ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    માટે (i = 0; i < map->image.અંક_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    જો (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    પાછા 0;

fail:
    જો (map) {
        જો (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        જો (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    પાછા err;
}

સ્થિર પૂર્ણાંક vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (dst->width > hwfc->width || dst->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    જો (err)
        જાઓ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (src->width > hwfc->width || src->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    જો (err)
        જાઓ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પૂર્ણાંક err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    જો (err)
        પાછા err;

    err = av_frame_copy_props(dst, src);
    જો (err)
        પાછા err;

    પાછા 0;
}

#જો CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
સ્થિર અચલ સંરચના {
    uint32_t va_fourcc;
    પૂર્ણાંક   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#જો defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#જો defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#જો defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#જો defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#જો defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#જો defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

સ્થિર શૂન્ય vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

સ્થિર પૂર્ણાંક vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              અચલ AVFrame *src, પૂર્ણાંક flags)
{
#જો VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    પૂર્ણાંક use_prime2;
#નહીંતર
    પૂર્ણાંક k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    અચલ AVDRMFrameDescriptor *desc;
    અચલ VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    પૂર્ણાંક err, i, j;

#જો !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .કિંમત.type    = VAGeneric_કિંમત_Type_Integer,
            .કિંમત.કિંમત.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_અવિભાજ્ય,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .કિંમત.type    = VAGeneric_કિંમત_Type_Pointer,
            .કિંમત.કિંમત.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    જો (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        પાછા AVERROR(EINVAL);
    }

    va_fourcc = 0;
    માટે (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        જો (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            ચાલુ;
        માટે (j = 0; j < desc->nb_layers; j++) {
            જો (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                તોડો;
        }
        જો (j != desc->nb_layers)
            ચાલુ;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        તોડો;
    }
    જો (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        પાછા AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#જો VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->અવિભાજ્ય_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    જો (use_prime2) {
        VADRMPRIMESurfaceDescriptor અવિભાજ્ય_desc;
        VASurfaceAttrib અવિભાજ્ય_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .કિંમત.type    = VAGeneric_કિંમત_Type_Integer,
                .કિંમત.કિંમત.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_અવિભાજ્ય_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .કિંમત.type    = VAGeneric_કિંમત_Type_Pointer,
                .કિંમત.કિંમત.p = &અવિભાજ્ય_desc,
            }
        };
        અવિભાજ્ય_desc.fourcc = va_fourcc;
        અવિભાજ્ય_desc.width = src_fc->width;
        અવિભાજ્ય_desc.height = src_fc->height;
        અવિભાજ્ય_desc.અંક_objects = desc->nb_objects;
        માટે (i = 0; i < desc->nb_objects; ++i) {
            અવિભાજ્ય_desc.objects[i].fd = desc->objects[i].fd;
            અવિભાજ્ય_desc.objects[i].size = desc->objects[i].size;
            અવિભાજ્ય_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        અવિભાજ્ય_desc.અંક_layers = desc->nb_layers;
        માટે (i = 0; i < desc->nb_layers; ++i) {
            અવિભાજ્ય_desc.layers[i].drm_format = desc->layers[i].format;
            અવિભાજ્ય_desc.layers[i].અંક_planes = desc->layers[i].nb_planes;
            માટે (j = 0; j < desc->layers[i].nb_planes; ++j) {
                અવિભાજ્ય_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                અવિભાજ્ય_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                અવિભાજ્ય_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            જો (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, અવિભાજ્ય_desc.layers[i].pitch[1],
                    અવિભાજ્ય_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, અવિભાજ્ય_desc.layers[i].offset[1],
                    અવિભાજ્ય_desc.layers[i].offset[2]);
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
                               અવિભાજ્ય_attrs, FF_ARRAY_ELEMS(અવિભાજ્ય_attrs));
        જો (vas != VA_STATUS_SUCCESS)
            src_vafc->અવિભાજ્ય_2_import_unsupported = 1;
    }

    જો (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        પૂર્ણાંક k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .કિંમત.type    = VAGeneric_કિંમત_Type_Integer,
                .કિંમત.કિંમત.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_અવિભાજ્ય,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .કિંમત.type    = VAGeneric_કિંમત_Type_Pointer,
                .કિંમત.કિંમત.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.અંક_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        માટે (i = 0; i < desc->nb_layers; i++) {
            માટે (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.અંક_planes = k;

        જો (format_desc->chroma_planes_swapped &&
            buffer_desc.અંક_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#નહીંતર
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.અંક_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    માટે (i = 0; i < desc->nb_layers; i++) {
        માટે (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.અંક_planes = k;

    જો (format_desc->chroma_planes_swapped &&
        buffer_desc.અંક_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        પાછા AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (શૂન્ય*)(uintptr_t)surface_id);
    જો (err < 0)
        પાછા err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    પાછા 0;
}

#જો VA_CHECK_VERSION(1, 1, 0)
સ્થિર શૂન્ય vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    પૂર્ણાંક i;

    માટે (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

સ્થિર પૂર્ણાંક vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = ખાલી;
    uint32_t export_flags;
    પૂર્ણાંક err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    જો (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            પાછા AVERROR(EIO);
        }
    }

    જો (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_અવિભાજ્ય_2,
                                export_flags, &va_desc);
    જો (vas != VA_STATUS_SUCCESS) {
        જો (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            પાછા AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        પાછા AVERROR(EIO);
    }

    drm_desc = av_mallocz(કદ(*drm_desc));
    જો (!drm_desc) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.અંક_objects;
    માટે (i = 0; i < va_desc.અંક_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.અંક_layers;
    માટે (i = 0; i < va_desc.અંક_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].અંક_planes;
        માટે (j = 0; j < va_desc.layers[i].અંક_planes; j++) {
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
    જો (err < 0)
        જાઓ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    પાછા 0;

fail:
    માટે (i = 0; i < va_desc.અંક_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    પાછા err;
}
#endif

#જો VA_CHECK_VERSION(0, 36, 0)
પ્રકારવ્યાખ્યા સંરચના VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

સ્થિર શૂન્ય vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

સ્થિર પૂર્ણાંક vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = ખાલી;
    VASurfaceID surface_id;
    VAStatus vas;
    પૂર્ણાંક err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(કદ(*mapping));
    જો (!mapping)
        પાછા AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        જાઓ fail;
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        જો (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            તોડો;
    }
    જો (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        જાઓ fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_અવિભાજ્ય;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    જો (mapping->drm_desc.nb_layers > 1) {
        જો (mapping->drm_desc.nb_layers != mapping->image.અંક_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.અંક_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            જાઓ fail_derived;
        }

        માટે(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } નહીંતર {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.અંક_planes;
        માટે (p = 0; p < mapping->image.અંક_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        જાઓ fail_derived;
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
    જો (err < 0)
        જાઓ fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    પાછા 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    પાછા err;
}
#endif

સ્થિર પૂર્ણાંક vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            અચલ AVFrame *src, પૂર્ણાંક flags)
{
#જો VA_CHECK_VERSION(1, 1, 0)
    પૂર્ણાંક err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    જો (err != AVERROR(ENOSYS))
        પાછા err;
#endif
#જો VA_CHECK_VERSION(0, 36, 0)
    પાછા vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    પાછા AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

સ્થિર પૂર્ણાંક vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પસંદગી (src->format) {
#જો CONFIG_LIBDRM
    સ્થિતિ AV_PIX_FMT_DRM_અવિભાજ્ય:
        પાછા vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    મૂળભૂત:
        પાછા AVERROR(ENOSYS);
    }
}

સ્થિર પૂર્ણાંક vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પસંદગી (dst->format) {
#જો CONFIG_LIBDRM
    સ્થિતિ AV_PIX_FMT_DRM_અવિભાજ્ય:
        પાછા vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    મૂળભૂત:
        પાછા vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

સ્થિર શૂન્ય vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    જો (hwctx->display)
        vaTerminate(hwctx->display);

#જો HAVE_VAAPI_X11
    જો (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#જો HAVE_VAAPI_DRM
    જો (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#જો CONFIG_VAAPI_1
સ્થિર શૂન્ય vaapi_device_log_error(શૂન્ય *context, અચલ અક્ષર *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

સ્થિર શૂન્ય vaapi_device_log_info(શૂન્ય *context, અચલ અક્ષર *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

સ્થિર પૂર્ણાંક vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    પૂર્ણાંક major, minor;
    VAStatus vas;

#જો CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    જો (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        પાછા AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    પાછા 0;
}

સ્થિર પૂર્ણાંક vaapi_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                               AVDictionary *opts, પૂર્ણાંક flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = ખાલી;
    અચલ AVDictionaryEntry *ent;
    પૂર્ણાંક try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(કદ(*priv));
    જો (!priv)
        પાછા AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->મુક્ત        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", ખાલી, 0);
    જો (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        જો (!strcmp(ent->કિંમત, "drm")) {
            try_drm = 1;
        } નહીંતર જો (!strcmp(ent->કિંમત, "x11")) {
            try_x11 = 1;
        } નહીંતર જો (!strcmp(ent->કિંમત, "win32")) {
            try_win32 = 1;
        } નહીંતર {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->કિંમત);
            પાછા AVERROR(EINVAL);
        }
    } નહીંતર {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#જો HAVE_VAAPI_DRM
    જ્યારે (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        પૂર્ણાંક loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        જો (device) {
            priv->drm_fd = open(device, O_RDWR);
            જો (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                તોડો;
            }
        } નહીંતર {
            અક્ષર path[64];
            પૂર્ણાંક n, max_devices = 8;
#જો CONFIG_LIBDRM
            drmVersion *info;
            અચલ AVDictionaryEntry *kernel_driver;
            અચલ AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", ખાલી, 0);
            vendor_id = av_dict_get(opts, "vendor_id", ખાલી, 0);
#endif
            માટે (n = 0; n < max_devices; n++) {
                snprintf(path, કદ(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                જો (priv->drm_fd < 0) {
                    જો (errno == ENOENT) {
                        જો (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            ચાલુ;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } નહીંતર
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    તોડો;
                }
#જો CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                જો (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ચાલુ;
                }
                જો (kernel_driver) {
                    જો (strcmp(kernel_driver->કિંમત, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        ચાલુ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    તોડો;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } નહીંતર જો (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    ચાલુ;
                } નહીંતર જો (vendor_id) {
                    drmDevicePtr device;
                    અક્ષર drm_vendor[8];
                    જો (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ચાલુ;
                    }

                    snprintf(drm_vendor, કદ(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    જો (strcmp(vendor_id->કિંમત, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->કિંમત);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        ચાલુ;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->કિંમત);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    તોડો;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                તોડો;
            }
            જો (n >= max_devices)
                તોડો;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        જો (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            પાછા AVERROR_EXTERNAL;
        }
        તોડો;
    }
#endif

#જો HAVE_VAAPI_X11
    જો (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        જો (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } નહીંતર {
            display = vaGetDisplay(priv->x11_display);
            જો (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                પાછા AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#જો HAVE_VAAPI_WIN32
    જો (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        જો (!device) {
            display = vaGetDisplayWin32(ખાલી);
        } નહીંતર {
            IDXGIFactory2 *pDXGIFactory = ખાલી;
            IDXGIAdapter *pAdapter = ખાલી;
#જો !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            જો (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                પાછા AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            જો (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                પાછા AVERROR_UNKNOWN;
            }
#નહીંતર
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            જો (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (શૂન્ય **)&pDXGIFactory))) {
                પૂર્ણાંક adapter = atoi(device);
                જો (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    જો (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.નીચલું_Part,
                              desc.AdapterLuid.ઉપલું_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#જો !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        જો (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            પાછા AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    જો (!display) {
        જો (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        નહીંતર
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        પાછા AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", ખાલી, 0);
    જો (ent) {
#જો VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->કિંમત);
        જો (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->કિંમત, vas, vaErrorStr(vas));
            vaTerminate(display);
            પાછા AVERROR_EXTERNAL;
        }
#નહીંતર
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    પાછા vaapi_device_connect(ctx, display);
}

સ્થિર પૂર્ણાંક vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, પૂર્ણાંક flags)
{
#જો HAVE_VAAPI_DRM
    જો (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        પૂર્ણાંક fd;

        જો (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            પાછા AVERROR(EINVAL);
        }

#જો CONFIG_LIBDRM
        {
            પૂર્ણાંક ગાંઠ_type = drm_Get_ગાંઠ_Type_From_Fd(src_hwctx->fd);
            અક્ષર *render_ગાંઠ;
            જો (ગાંઠ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                પાછા AVERROR(EINVAL);
            }
            જો (ગાંઠ_type == DRM_ગાંઠ_RENDER) {
                fd = src_hwctx->fd;
            } નહીંતર {
                render_ગાંઠ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                જો (!render_ગાંઠ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } નહીંતર {
                    fd = open(render_ગાંઠ, O_RDWR);
                    જો (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } નહીંતર {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_ગાંઠ);
                    }
                    મુક્ત(render_ગાંઠ);
                }
            }
        }
#નહીંતર
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(કદ(*priv));
        જો (!priv) {
            જો (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            પાછા AVERROR(ENOMEM);
        }

        જો (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } નહીંતર {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->મુક્ત        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        જો (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            પાછા AVERROR(EIO);
        }

        પાછા vaapi_device_connect(ctx, display);
    }
#endif
    પાછા AVERROR(ENOSYS);
}

અચલ HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = કદ(VAAPIDeviceContext),
    .device_hwconfig_size   = કદ(AVVAAPIHWConfig),
    .frames_hwctx_size      = કદ(VAAPIFramesContext),

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

    .pix_fmts = (અચલ ગણના AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
