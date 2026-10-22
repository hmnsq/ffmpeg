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

#include "config.h"

#ꦪꦼꦤ꧀ HAVE_VAAPI_WIN32
#   include <windows.h>
#define COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
typedef HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, void **ppFactory);
#endif
#ꦪꦼꦤ꧀ HAVE_VAAPI_X11
#   include <va/va_x11.h>
#endif
#ꦪꦼꦤ꧀ HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#endif

#ꦪꦼꦤ꧀ CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#endif

#include <fcntl.h>
#ꦪꦼꦤ꧀ HAVE_UNISTD_H
#   include <unistd.h>
#endif


#include "avassert.h"
#include "buffer.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_drm.h"
#include "hwcontext_internal.h"
#include "hwcontext_vaapi.h"
#include "mem.h"
#include "pixdesc.h"
#include "pixfmt.h"


typedef sa_nracanaa VAAPIDevicePriv {
#ꦪꦼꦤ꧀ HAVE_VAAPI_X11
    Display *x11_display;
#endif

    puur_naa_nka drm_fd;
} VAAPIDevicePriv;

typedef sa_nracanaa VAAPISurfaceFormat {
    ga_nanaa AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    unsigned puur_naa_nka fourcc;
} VAAPISurfaceFormat;

typedef sa_nracanaa VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    puur_naa_nka              nb_formats;
} VAAPIDeviceContext;

typedef sa_nracanaa VAAPIFramesContext {
    /**
     * The public AVVAAPIFramesContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIFramesContext p;

    // Surface attributes set at create time.
    VASurfaceAttrib *attributes;
    puur_naa_nka           nb_attributes;
    // RT format of the underlying surface (Intel driver ignores this anyway).
    unsigned puur_naa_nka rt_format;
    // Whether vaDeriveImage works.
    puur_naa_nka derive_works;
    // Caches whether VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2 is unsupported for
    // surface imports.
    puur_naa_nka prime_2_import_unsupported;
} VAAPIFramesContext;

typedef sa_nracanaa VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    puur_naa_nka flags;
} VAAPIMapping;

typedef sa_nracanaa VAAPIFormat {
    unsigned puur_naa_nka fourcc;
    unsigned puur_naa_nka rt_format;
    ga_nanaa AVPixelFormat pix_fmt;
    puur_naa_nka chroma_planes_swapped;
} VAAPIFormatDescriptor;

#define MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
static const VAAPIFormatDescriptor vaapi_format_map[] = {
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

static const VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned puur_naa_nka fourcc)
{
    puur_naa_nka i;
    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        ꦪꦼꦤ꧀ (vaapi_format_map[i].fourcc == fourcc)
            ꦮꦭꦶ &vaapi_format_map[i];
    ꦮꦭꦶ NULL;
}

static const VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(ga_nanaa AVPixelFormat pix_fmt, const VAAPIFormatDescriptor *prev)
{
    const VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    ꦪꦼꦤ꧀ (!prev)
        prev = vaapi_format_map;
    ꦭꦶꦪ
        prev++;

    ꦏꦁꦒꦺꦴ (; prev < end; prev++)
        ꦪꦼꦤ꧀ (prev->pix_fmt == pix_fmt)
            ꦮꦭꦶ prev;
    ꦮꦭꦶ NULL;
}

static ga_nanaa AVPixelFormat vaapi_pix_fmt_from_fourcc(unsigned puur_naa_nka fourcc)
{
    const VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    ꦪꦼꦤ꧀ (desc)
        ꦮꦭꦶ desc->pix_fmt;
    ꦭꦶꦪ
        ꦮꦭꦶ AV_PIX_FMT_NONE;
}

static puur_naa_nka vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  ga_nanaa AVPixelFormat pix_fmt,
                                  const VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    const VAAPIFormatDescriptor *desc = NULL;
    puur_naa_nka i;

    ꦱꦼꦢꦼꦭ ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        ꦏꦁꦒꦺꦴ (i = 0; i < ctx->nb_formats; i++) {
            ꦪꦼꦤ꧀ (ctx->formats[i].fourcc == desc->fourcc) {
                ꦪꦼꦤ꧀ (_desc)
                    *_desc = desc;
                ꦪꦼꦤ꧀ (image_format)
                    *image_format = &ctx->formats[i].image_format;
                ꦮꦭꦶ 0;
            }
        }
    }

    ꦮꦭꦶ AVERROR(ENOSYS);
}

static puur_naa_nka vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  ga_nanaa AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    ꦪꦼꦤ꧀ (!image_format)
        ꦮꦭꦶ AVERROR(EINVAL);
    ꦮꦭꦶ vaapi_get_img_desc_and_format(hwdev, pix_fmt, NULL, image_format);
}

static puur_naa_nka vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        const void *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    const AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = NULL;
    VAStatus vas;
    ga_nanaa AVPixelFormat pix_fmt;
    unsigned puur_naa_nka fourcc;
    puur_naa_nka err, i, j, attr_count, pix_fmt_count;

    ꦪꦼꦤ꧀ (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_count = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_count);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            goto fail;
        }

        attr_list = av_malloc(attr_count * parimaa_na(*attr_list));
        ꦪꦼꦤ꧀ (!attr_list) {
            err = AVERROR(ENOMEM);
            goto fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_count);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            goto fail;
        }

        pix_fmt_count = 0;
        ꦏꦁꦒꦺꦴ (i = 0; i < attr_count; i++) {
            switch (attr_list[i].type) {
            pak_sa VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].value.value.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                ꦪꦼꦤ꧀ (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_count;
                } ꦭꦶꦪ {
                    // Something unsupported - ignore.
                }
                bha_nga;
            pak_sa VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].value.value.i;
                bha_nga;
            pak_sa VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].value.value.i;
                bha_nga;
            pak_sa VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].value.value.i;
                bha_nga;
            pak_sa VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].value.value.i;
                bha_nga;
            }
        }
        ꦪꦼꦤ꧀ (pix_fmt_count == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = NULL;
        } ꦭꦶꦪ {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_count + 1,
                                                            parimaa_na(pix_fmt));
            ꦪꦼꦤ꧀ (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                goto fail;
            }

            ꦏꦁꦒꦺꦴ (i = j = 0; i < attr_count; i++) {
                puur_naa_nka k;

                ꦪꦼꦤ꧀ (attr_list[i].type != VASurfaceAttribPixelFormat)
                    continue;
                fourcc = attr_list[i].value.value.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                ꦪꦼꦤ꧀ (pix_fmt == AV_PIX_FMT_NONE)
                    continue;

                ꦏꦁꦒꦺꦴ (k = 0; k < j; k++) {
                    ꦪꦼꦤ꧀ (constraints->valid_sw_formats[k] == pix_fmt)
                        bha_nga;
                }

                ꦪꦼꦤ꧀ (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } ꦭꦶꦪ {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        parimaa_na(pix_fmt));
        ꦪꦼꦤ꧀ (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            goto fail;
        }
        ꦏꦁꦒꦺꦴ (i = j = 0; i < ctx->nb_formats; i++) {
            puur_naa_nka k;

            ꦏꦁꦒꦺꦴ (k = 0; k < j; k++) {
                ꦪꦼꦤ꧀ (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    bha_nga;
            }

            ꦪꦼꦤ꧀ (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(pix_fmt));
    ꦪꦼꦤ꧀ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    ꦮꦭꦶ err;
}

static const sa_nracanaa {
    const var_na *friendly_name;
    const var_na *match_string;
    unsigned puur_naa_nka quirks;
} vaapi_driver_quirks_table[] = {
#ꦪꦼꦤ꧀ !VA_CHECK_VERSION(1, 0, 0)
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

static puur_naa_nka vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = NULL;
    VAStatus vas;
    const var_na *vendor_string;
    puur_naa_nka err, i, image_count;
    ga_nanaa AVPixelFormat pix_fmt;
    unsigned puur_naa_nka fourcc;

    image_count = vaMaxNumImageFormats(hwctx->display);
    ꦪꦼꦤ꧀ (image_count <= 0) {
        err = AVERROR(EIO);
        goto fail;
    }
    image_list = av_malloc(image_count * parimaa_na(*image_list));
    ꦪꦼꦤ꧀ (!image_list) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_count);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        goto fail;
    }

    ctx->formats  = av_malloc(image_count * parimaa_na(*ctx->formats));
    ꦪꦼꦤ꧀ (!ctx->formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    ctx->nb_formats = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < image_count; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        ꦪꦼꦤ꧀ (pix_fmt == AV_PIX_FMT_NONE) {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> unknown.\n",
                   fourcc);
        } ꦭꦶꦪ {
            av_log(hwdev, AV_LOG_DEBUG, "Format %#x -> %s.\n",
                   fourcc, av_get_pix_fmt_name(pix_fmt));
            ctx->formats[ctx->nb_formats].pix_fmt      = pix_fmt;
            ctx->formats[ctx->nb_formats].fourcc       = fourcc;
            ctx->formats[ctx->nb_formats].image_format = image_list[i];
            ++ctx->nb_formats;
        }
    }

    vendor_string = vaQueryVendorString(hwctx->display);
    ꦪꦼꦤ꧀ (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    ꦪꦼꦤ꧀ (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } ꦭꦶꦪ {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        ꦪꦼꦤ꧀ (vendor_string) {
            ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                ꦪꦼꦤ꧀ (strstr(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    bha_nga;
                }
            }
            ꦪꦼꦤ꧀ (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } ꦭꦶꦪ {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    ꦮꦭꦶ 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    ꦮꦭꦶ err;
}

static void vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

static void vaapi_buffer_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)data;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

static AVBufferRef *vaapi_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    ꦪꦼꦤ꧀ (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        ꦮꦭꦶ NULL;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        ꦮꦭꦶ NULL;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           parimaa_na(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    ꦪꦼꦤ꧀ (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        ꦮꦭꦶ NULL;
    }

    ꦪꦼꦤ꧀ (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    ꦮꦭꦶ ref;
}

static puur_naa_nka vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    const VAAPIFormatDescriptor *desc = NULL;
    VAImageFormat *expected_format = NULL;
    AVBufferRef *test_surface = NULL;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    puur_naa_nka err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    ꦪꦼꦤ꧀ (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        ꦪꦼꦤ꧀ (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, NULL)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ꦮꦭꦶ AVERROR(EINVAL);
        }
    }

    ꦪꦼꦤ꧀ (!hwfc->pool) {
        ꦪꦼꦤ꧀ (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            puur_naa_nka need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            puur_naa_nka need_pixel_format = 1;
            ꦏꦁꦒꦺꦴ (i = 0; i < avfc->nb_attributes; i++) {
                ꦪꦼꦤ꧀ (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                ꦪꦼꦤ꧀ (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        parimaa_na(*ctx->attributes));
            ꦪꦼꦤ꧀ (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                goto fail;
            }

            ꦏꦁꦒꦺꦴ (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            ꦪꦼꦤ꧀ (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .value.type    = VAGenericValueTypeInteger,
                    .value.value.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            ꦪꦼꦤ꧀ (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .value.type    = VAGenericValueTypeInteger,
                    .value.value.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } ꦭꦶꦪ {
            ctx->attributes = NULL;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        ꦪꦼꦤ꧀ (hwfc->initial_pool_size > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_size *
                                          parimaa_na(*avfc->surface_ids));
            ꦪꦼꦤ꧀ (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                goto fail;
            }
        } ꦭꦶꦪ {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = NULL;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(parimaa_na(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, NULL);
        ꦪꦼꦤ꧀ (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            goto fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    ꦪꦼꦤ꧀ (hwfc->pool) {
        test_surface = av_buffer_pool_get(hwfc->pool);
        ꦪꦼꦤ꧀ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            goto fail;
        }
    } ꦭꦶꦪ {
        test_surface = av_buffer_pool_get(ffhwframesctx(hwfc)->pool_internal);
        ꦪꦼꦤ꧀ (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            goto fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->data;

    ctx->derive_works = 0;
    ꦪꦼꦤ꧀ (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        ꦪꦼꦤ꧀ (vas == VA_STATUS_SUCCESS) {
            ꦪꦼꦤ꧀ (expected_format->fourcc == test_image.format.fourcc) {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping possible.\n");
                ctx->derive_works = 1;
            } ꦭꦶꦪ {
                av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                       "derived image format %08x does not match "
                       "expected format %08x.\n",
                       expected_format->fourcc, test_image.format.fourcc);
            }
            vaDestroyImage(hwctx->display, test_image.image_id);
        } ꦭꦶꦪ {
            av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
                   "deriving image does not work: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
        }
    } ꦭꦶꦪ {
        av_log(hwfc, AV_LOG_DEBUG, "Direct mapping disabled: "
               "image format is not supported.\n");
    }

    av_buffer_unref(&test_surface);
    ꦮꦭꦶ 0;

fail:
    av_buffer_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    ꦮꦭꦶ err;
}

static void vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

static puur_naa_nka vaapi_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ꦪꦼꦤ꧀ (!frame->buf[0])
        ꦮꦭꦶ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ꦮꦭꦶ 0;
}

static puur_naa_nka vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      ga_nanaa AVHWFrameTransferDirection dir,
                                      ga_nanaa AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    ga_nanaa AVPixelFormat *pix_fmts;
    puur_naa_nka i, k, sw_format_available;

    sw_format_available = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < ctx->nb_formats; i++) {
        ꦪꦼꦤ꧀ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * parimaa_na(*pix_fmts));
    ꦪꦼꦤ꧀ (!pix_fmts)
        ꦮꦭꦶ AVERROR(ENOMEM);

    ꦪꦼꦤ꧀ (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } ꦭꦶꦪ {
        k = 0;
    }
    ꦏꦁꦒꦺꦴ (i = 0; i < ctx->nb_formats; i++) {
        ꦪꦼꦤ꧀ (ctx->formats[i].pix_fmt == hwfc->sw_format)
            continue;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    ꦮꦭꦶ 0;
}

static void vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = vaUnmapBuffer(hwctx->display, map->image.buf);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    ꦪꦼꦤ꧀ ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

static puur_naa_nka vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, const AVFrame *src, puur_naa_nka flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    const VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    void *address = NULL;
    puur_naa_nka err, i;
#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#endif

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    ꦪꦼꦤ꧀ (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        ꦮꦭꦶ AVERROR(EINVAL);
    }
    ꦪꦼꦤ꧀ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ꦪꦼꦤ꧀ (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        ꦮꦭꦶ AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    ꦪꦼꦤ꧀ (err < 0) {
        // Requested format is not a valid output format.
        ꦮꦭꦶ err;
    }

    map = av_malloc(parimaa_na(*map));
    ꦪꦼꦤ꧀ (!map)
        ꦮꦭꦶ AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    ꦪꦼꦤ꧀ (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            goto fail;
        }
        ꦪꦼꦤ꧀ (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            goto fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } ꦭꦶꦪ {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            goto fail;
        }
        ꦪꦼꦤ꧀ (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                goto fail;
            }
        }
    }

#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 21, 0)
    ꦪꦼꦤ꧀ (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    ꦪꦼꦤ꧀ (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#ꦭꦶꦪ
    vas = vaMapBuffer(hwctx->display, map->image.buf, &address);
#endif
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    ꦪꦼꦤ꧀ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ꦏꦁꦒꦺꦴ (i = 0; i < map->image.num_planes; i++) {
        dst->data[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    ꦪꦼꦤ꧀ (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->data[1], dst->data[2]);
    }

    ꦮꦭꦶ 0;

fail:
    ꦪꦼꦤ꧀ (map) {
        ꦪꦼꦤ꧀ (address)
            vaUnmapBuffer(hwctx->display, map->image.buf);
        ꦪꦼꦤ꧀ (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    ꦮꦭꦶ err;
}

static puur_naa_nka vaapi_transfer_data_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    puur_naa_nka err;

    ꦪꦼꦤ꧀ (dst->width > hwfc->width || dst->height > hwfc->height)
        ꦮꦭꦶ AVERROR(EINVAL);

    map = av_frame_alloc();
    ꦪꦼꦤ꧀ (!map)
        ꦮꦭꦶ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ꦪꦼꦤ꧀ (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ꦪꦼꦤ꧀ (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ꦮꦭꦶ err;
}

static puur_naa_nka vaapi_transfer_data_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    puur_naa_nka err;

    ꦪꦼꦤ꧀ (src->width > hwfc->width || src->height > hwfc->height)
        ꦮꦭꦶ AVERROR(EINVAL);

    map = av_frame_alloc();
    ꦪꦼꦤ꧀ (!map)
        ꦮꦭꦶ AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ꦪꦼꦤ꧀ (err)
        goto fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ꦪꦼꦤ꧀ (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ꦮꦭꦶ err;
}

static puur_naa_nka vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               const AVFrame *src, puur_naa_nka flags)
{
    puur_naa_nka err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    ꦪꦼꦤ꧀ (err)
        ꦮꦭꦶ err;

    err = av_frame_copy_props(dst, src);
    ꦪꦼꦤ꧀ (err)
        ꦮꦭꦶ err;

    ꦮꦭꦶ 0;
}

#ꦪꦼꦤ꧀ CONFIG_LIBDRM

#define DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
static const sa_nracanaa {
    uint32_t va_fourcc;
    puur_naa_nka   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#ifdef DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#endif
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#ꦪꦼꦤ꧀ defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#endif
#ꦪꦼꦤ꧀ defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
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
#ꦪꦼꦤ꧀ defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#endif
#ꦪꦼꦤ꧀ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#endif
#ꦪꦼꦤ꧀ defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#endif
#ꦪꦼꦤ꧀ defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#endif
};
#undef DRM_MAP

static void vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

static puur_naa_nka vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              const AVFrame *src, puur_naa_nka flags)
{
#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    puur_naa_nka use_prime2;
#ꦭꦶꦪ
    puur_naa_nka k;
#endif
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    const AVDRMFrameDescriptor *desc;
    const VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    puur_naa_nka err, i, j;

#ꦪꦼꦤ꧀ !VA_CHECK_VERSION(1, 1, 0)
    unsigned long buffer_handle;
    VASurfaceAttribExternalBuffers buffer_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .value.type    = VAGenericValueTypeInteger,
            .value.value.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME,
        },
        {
            .type  = VASurfaceAttribExternalBufferDescriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .value.type    = VAGenericValueTypePointer,
            .value.value.p = &buffer_desc,
        }
    };
#endif

    desc = (AVDRMFrameDescriptor*)src->data[0];

    ꦪꦼꦤ꧀ (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        ꦮꦭꦶ AVERROR(EINVAL);
    }

    va_fourcc = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ꦪꦼꦤ꧀ (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            continue;
        ꦏꦁꦒꦺꦴ (j = 0; j < desc->nb_layers; j++) {
            ꦪꦼꦤ꧀ (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                bha_nga;
        }
        ꦪꦼꦤ꧀ (j != desc->nb_layers)
            continue;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        bha_nga;
    }
    ꦪꦼꦤ꧀ (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        ꦮꦭꦶ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->prime_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    ꦪꦼꦤ꧀ (use_prime2) {
        VADRMPRIMESurfaceDescriptor prime_desc;
        VASurfaceAttrib prime_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .value.type    = VAGenericValueTypeInteger,
                .value.value.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .value.type    = VAGenericValueTypePointer,
                .value.value.p = &prime_desc,
            }
        };
        prime_desc.fourcc = va_fourcc;
        prime_desc.width = src_fc->width;
        prime_desc.height = src_fc->height;
        prime_desc.num_objects = desc->nb_objects;
        ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_objects; ++i) {
            prime_desc.objects[i].fd = desc->objects[i].fd;
            prime_desc.objects[i].size = desc->objects[i].size;
            prime_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        prime_desc.num_layers = desc->nb_layers;
        ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_layers; ++i) {
            prime_desc.layers[i].drm_format = desc->layers[i].format;
            prime_desc.layers[i].num_planes = desc->layers[i].nb_planes;
            ꦏꦁꦒꦺꦴ (j = 0; j < desc->layers[i].nb_planes; ++j) {
                prime_desc.layers[i].object_index[j] =
                        desc->layers[i].planes[j].object_index;
                prime_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                prime_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            ꦪꦼꦤ꧀ (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, prime_desc.layers[i].pitch[1],
                    prime_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, prime_desc.layers[i].offset[1],
                    prime_desc.layers[i].offset[2]);
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
                               prime_attrs, FF_ARRAY_ELEMS(prime_attrs));
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS)
            src_vafc->prime_2_import_unsupported = 1;
    }

    ꦪꦼꦤ꧀ (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        puur_naa_nka k;
        uintptr_t buffer_handle;
        VASurfaceAttribExternalBuffers buffer_desc;
        VASurfaceAttrib buffer_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .value.type    = VAGenericValueTypeInteger,
                .value.value.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME,
            },
            {
                .type  = VASurfaceAttribExternalBufferDescriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .value.type    = VAGenericValueTypePointer,
                .value.value.p = &buffer_desc,
            }
        };

        buffer_handle = desc->objects[0].fd;
        buffer_desc.pixel_format = va_fourcc;
        buffer_desc.width        = src_fc->width;
        buffer_desc.height       = src_fc->height;
        buffer_desc.data_size    = desc->objects[0].size;
        buffer_desc.buffers      = &buffer_handle;
        buffer_desc.num_buffers  = 1;
        buffer_desc.flags        = 0;

        k = 0;
        ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_layers; i++) {
            ꦏꦁꦒꦺꦴ (j = 0; j < desc->layers[i].nb_planes; j++) {
                buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        buffer_desc.num_planes = k;

        ꦪꦼꦤ꧀ (format_desc->chroma_planes_swapped &&
            buffer_desc.num_planes == 3) {
            FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
            FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               buffer_attrs, FF_ARRAY_ELEMS(buffer_attrs));
    }
#ꦭꦶꦪ
    buffer_handle = desc->objects[0].fd;
    buffer_desc.pixel_format = va_fourcc;
    buffer_desc.width        = src_fc->width;
    buffer_desc.height       = src_fc->height;
    buffer_desc.data_size    = desc->objects[0].size;
    buffer_desc.buffers      = &buffer_handle;
    buffer_desc.num_buffers  = 1;
    buffer_desc.flags        = 0;

    k = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_layers; i++) {
        ꦏꦁꦒꦺꦴ (j = 0; j < desc->layers[i].nb_planes; j++) {
            buffer_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            buffer_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    buffer_desc.num_planes = k;

    ꦪꦼꦤ꧀ (format_desc->chroma_planes_swapped &&
        buffer_desc.num_planes == 3) {
        FFSWAP(uint32_t, buffer_desc.pitches[1], buffer_desc.pitches[2]);
        FFSWAP(uint32_t, buffer_desc.offsets[1], buffer_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#endif
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        ꦮꦭꦶ AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (void*)(uintptr_t)surface_id);
    ꦪꦼꦤ꧀ (err < 0)
        ꦮꦭꦶ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    ꦮꦭꦶ 0;
}

#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 1, 0)
static void vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    puur_naa_nka i;

    ꦏꦁꦒꦺꦴ (i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

static puur_naa_nka vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                const AVFrame *src, puur_naa_nka flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = NULL;
    uint32_t export_flags;
    puur_naa_nka err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    ꦪꦼꦤ꧀ (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            ꦮꦭꦶ AVERROR(EIO);
        }
    }

    ꦪꦼꦤ꧀ (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME_2,
                                export_flags, &va_desc);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        ꦪꦼꦤ꧀ (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            ꦮꦭꦶ AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        ꦮꦭꦶ AVERROR(EIO);
    }

    drm_desc = av_mallocz(parimaa_na(*drm_desc));
    ꦪꦼꦤ꧀ (!drm_desc) {
        err = AVERROR(ENOMEM);
        goto fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.num_objects;
    ꦏꦁꦒꦺꦴ (i = 0; i < va_desc.num_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].size = va_desc.objects[i].size;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.num_layers;
    ꦏꦁꦒꦺꦴ (i = 0; i < va_desc.num_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].num_planes;
        ꦏꦁꦒꦺꦴ (j = 0; j < va_desc.layers[i].num_planes; j++) {
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
    ꦪꦼꦤ꧀ (err < 0)
        goto fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t*)drm_desc;

    ꦮꦭꦶ 0;

fail:
    ꦏꦁꦒꦺꦴ (i = 0; i < va_desc.num_objects; i++)
        close(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    ꦮꦭꦶ err;
}
#endif

#ꦪꦼꦤ꧀ VA_CHECK_VERSION(0, 36, 0)
typedef sa_nracanaa VAAPIDRMImageBufferMapping {
    VAImage      image;
    VABufferInfo buffer_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImageBufferMapping;

static void vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
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
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

static puur_naa_nka vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                const AVFrame *src, puur_naa_nka flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImageBufferMapping *mapping = NULL;
    VASurfaceID surface_id;
    VAStatus vas;
    puur_naa_nka err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->data[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(parimaa_na(*mapping));
    ꦪꦼꦤ꧀ (!mapping)
        ꦮꦭꦶ AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail;
    }

    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        ꦪꦼꦤ꧀ (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            bha_nga;
    }
    ꦪꦼꦤ꧀ (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        goto fail_derived;
    }

    mapping->buffer_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_PRIME;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    ꦪꦼꦤ꧀ (mapping->drm_desc.nb_layers > 1) {
        ꦪꦼꦤ꧀ (mapping->drm_desc.nb_layers != mapping->image.num_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.num_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            goto fail_derived;
        }

        ꦏꦁꦒꦺꦴ(p = 0; p < mapping->drm_desc.nb_layers; p++) {
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
    } ꦭꦶꦪ {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.num_planes;
        ꦏꦁꦒꦺꦴ (p = 0; p < mapping->image.num_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_index = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = vaAcquireBufferHandle(hwctx->display, mapping->image.buf,
                                &mapping->buffer_info);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        goto fail_derived;
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
    ꦪꦼꦤ꧀ (err < 0)
        goto fail_mapped;

    dst->data[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    ꦮꦭꦶ 0;

fail_mapped:
    vaReleaseBufferHandle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    ꦮꦭꦶ err;
}
#endif

static puur_naa_nka vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            const AVFrame *src, puur_naa_nka flags)
{
#ꦪꦼꦤ꧀ VA_CHECK_VERSION(1, 1, 0)
    puur_naa_nka err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    ꦪꦼꦤ꧀ (err != AVERROR(ENOSYS))
        ꦮꦭꦶ err;
#endif
#ꦪꦼꦤ꧀ VA_CHECK_VERSION(0, 36, 0)
    ꦮꦭꦶ vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#endif
    ꦮꦭꦶ AVERROR(ENOSYS);
}

#endif /* CONFIG_LIBDRM */

static puur_naa_nka vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        const AVFrame *src, puur_naa_nka flags)
{
    switch (src->format) {
#ꦪꦼꦤ꧀ CONFIG_LIBDRM
    pak_sa AV_PIX_FMT_DRM_PRIME:
        ꦮꦭꦶ vaapi_map_from_drm(hwfc, dst, src, flags);
#endif
    default:
        ꦮꦭꦶ AVERROR(ENOSYS);
    }
}

static puur_naa_nka vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          const AVFrame *src, puur_naa_nka flags)
{
    switch (dst->format) {
#ꦪꦼꦤ꧀ CONFIG_LIBDRM
    pak_sa AV_PIX_FMT_DRM_PRIME:
        ꦮꦭꦶ vaapi_map_to_drm(hwfc, dst, src, flags);
#endif
    default:
        ꦮꦭꦶ vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

static void vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    ꦪꦼꦤ꧀ (hwctx->display)
        vaTerminate(hwctx->display);

#ꦪꦼꦤ꧀ HAVE_VAAPI_X11
    ꦪꦼꦤ꧀ (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#endif

#ꦪꦼꦤ꧀ HAVE_VAAPI_DRM
    ꦪꦼꦤ꧀ (priv->drm_fd >= 0)
        close(priv->drm_fd);
#endif

    av_freep(&priv);
}

#ꦪꦼꦤ꧀ CONFIG_VAAPI_1
static void vaapi_device_log_error(void *context, const var_na *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

static void vaapi_device_log_info(void *context, const var_na *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#endif

static puur_naa_nka vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    puur_naa_nka major, minor;
    VAStatus vas;

#ꦪꦼꦤ꧀ CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#endif

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        ꦮꦭꦶ AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    ꦮꦭꦶ 0;
}

static puur_naa_nka vaapi_device_create(AVHWDeviceContext *ctx, const var_na *device,
                               AVDictionary *opts, puur_naa_nka flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = NULL;
    const AVDictionaryEntry *ent;
    puur_naa_nka try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(parimaa_na(*priv));
    ꦪꦼꦤ꧀ (!priv)
        ꦮꦭꦶ AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->free        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", NULL, 0);
    ꦪꦼꦤ꧀ (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        ꦪꦼꦤ꧀ (!strcmp(ent->value, "drm")) {
            try_drm = 1;
        } ꦭꦶꦪ ꦪꦼꦤ꧀ (!strcmp(ent->value, "x11")) {
            try_x11 = 1;
        } ꦭꦶꦪ ꦪꦼꦤ꧀ (!strcmp(ent->value, "win32")) {
            try_win32 = 1;
        } ꦭꦶꦪ {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->value);
            ꦮꦭꦶ AVERROR(EINVAL);
        }
    } ꦭꦶꦪ {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#ꦪꦼꦤ꧀ HAVE_VAAPI_DRM
    ꦱꦼꦢꦼꦭ (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        puur_naa_nka loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        ꦪꦼꦤ꧀ (device) {
            priv->drm_fd = open(device, O_RDWR);
            ꦪꦼꦤ꧀ (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                bha_nga;
            }
        } ꦭꦶꦪ {
            var_na path[64];
            puur_naa_nka n, max_devices = 8;
#ꦪꦼꦤ꧀ CONFIG_LIBDRM
            drmVersion *info;
            const AVDictionaryEntry *kernel_driver;
            const AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", NULL, 0);
            vendor_id = av_dict_get(opts, "vendor_id", NULL, 0);
#endif
            ꦏꦁꦒꦺꦴ (n = 0; n < max_devices; n++) {
                snprintf(path, parimaa_na(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = open(path, O_RDWR);
                ꦪꦼꦤ꧀ (priv->drm_fd < 0) {
                    ꦪꦼꦤ꧀ (errno == ENOENT) {
                        ꦪꦼꦤ꧀ (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            continue;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } ꦭꦶꦪ
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    bha_nga;
                }
#ꦪꦼꦤ꧀ CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                ꦪꦼꦤ꧀ (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    continue;
                }
                ꦪꦼꦤ꧀ (kernel_driver) {
                    ꦪꦼꦤ꧀ (strcmp(kernel_driver->value, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        continue;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    bha_nga;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } ꦭꦶꦪ ꦪꦼꦤ꧀ (!strcmp(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    close(priv->drm_fd);
                    priv->drm_fd = -1;
                    continue;
                } ꦭꦶꦪ ꦪꦼꦤ꧀ (vendor_id) {
                    drmDevicePtr device;
                    var_na drm_vendor[8];
                    ꦪꦼꦤ꧀ (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        continue;
                    }

                    snprintf(drm_vendor, parimaa_na(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    ꦪꦼꦤ꧀ (strcmp(vendor_id->value, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->value);
                        drmFreeDevice(&device);
                        close(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        continue;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->value);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    bha_nga;
                }
                drmFreeVersion(info);
#endif
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                bha_nga;
            }
            ꦪꦼꦤ꧀ (n >= max_devices)
                bha_nga;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        ꦪꦼꦤ꧀ (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            ꦮꦭꦶ AVERROR_EXTERNAL;
        }
        bha_nga;
    }
#endif

#ꦪꦼꦤ꧀ HAVE_VAAPI_X11
    ꦪꦼꦤ꧀ (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        ꦪꦼꦤ꧀ (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } ꦭꦶꦪ {
            display = vaGetDisplay(priv->x11_display);
            ꦪꦼꦤ꧀ (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                ꦮꦭꦶ AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#endif

#ꦪꦼꦤ꧀ HAVE_VAAPI_WIN32
    ꦪꦼꦤ꧀ (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        ꦪꦼꦤ꧀ (!device) {
            display = vaGetDisplayWin32(NULL);
        } ꦭꦶꦪ {
            IDXGIFactory2 *pDXGIFactory = NULL;
            IDXGIAdapter *pAdapter = NULL;
#ꦪꦼꦤ꧀ !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            ꦪꦼꦤ꧀ (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                ꦮꦭꦶ AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            ꦪꦼꦤ꧀ (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                ꦮꦭꦶ AVERROR_UNKNOWN;
            }
#ꦭꦶꦪ
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#endif
            ꦪꦼꦤ꧀ (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (void **)&pDXGIFactory))) {
                puur_naa_nka adapter = atoi(device);
                ꦪꦼꦤ꧀ (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    ꦪꦼꦤ꧀ (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.LowPart,
                              desc.AdapterLuid.HighPart);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#ꦪꦼꦤ꧀ !HAVE_UWP
            dlclose(dxgi);
#endif
        }

        ꦪꦼꦤ꧀ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            ꦮꦭꦶ AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#endif

    ꦪꦼꦤ꧀ (!display) {
        ꦪꦼꦤ꧀ (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        ꦭꦶꦪ
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        ꦮꦭꦶ AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", NULL, 0);
    ꦪꦼꦤ꧀ (ent) {
#ꦪꦼꦤ꧀ VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->value);
        ꦪꦼꦤ꧀ (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->value, vas, vaErrorStr(vas));
            vaTerminate(display);
            ꦮꦭꦶ AVERROR_EXTERNAL;
        }
#ꦭꦶꦪ
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#endif
    }

    ꦮꦭꦶ vaapi_device_connect(ctx, display);
}

static puur_naa_nka vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, puur_naa_nka flags)
{
#ꦪꦼꦤ꧀ HAVE_VAAPI_DRM
    ꦪꦼꦤ꧀ (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        puur_naa_nka fd;

        ꦪꦼꦤ꧀ (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            ꦮꦭꦶ AVERROR(EINVAL);
        }

#ꦪꦼꦤ꧀ CONFIG_LIBDRM
        {
            puur_naa_nka node_type = drmGetNodeTypeFromFd(src_hwctx->fd);
            var_na *render_node;
            ꦪꦼꦤ꧀ (node_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                ꦮꦭꦶ AVERROR(EINVAL);
            }
            ꦪꦼꦤ꧀ (node_type == DRM_NODE_RENDER) {
                fd = src_hwctx->fd;
            } ꦭꦶꦪ {
                render_node = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                ꦪꦼꦤ꧀ (!render_node) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } ꦭꦶꦪ {
                    fd = open(render_node, O_RDWR);
                    ꦪꦼꦤ꧀ (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } ꦭꦶꦪ {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_node);
                    }
                    free(render_node);
                }
            }
        }
#ꦭꦶꦪ
        fd = src_hwctx->fd;
#endif

        priv = av_mallocz(parimaa_na(*priv));
        ꦪꦼꦤ꧀ (!priv) {
            ꦪꦼꦤ꧀ (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                close(fd);
            }
            ꦮꦭꦶ AVERROR(ENOMEM);
        }

        ꦪꦼꦤ꧀ (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } ꦭꦶꦪ {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->free        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        ꦪꦼꦤ꧀ (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            ꦮꦭꦶ AVERROR(EIO);
        }

        ꦮꦭꦶ vaapi_device_connect(ctx, display);
    }
#endif
    ꦮꦭꦶ AVERROR(ENOSYS);
}

const HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_size      = parimaa_na(VAAPIDeviceContext),
    .device_hwconfig_size   = parimaa_na(AVVAAPIHWConfig),
    .frames_hwctx_size      = parimaa_na(VAAPIFramesContext),

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

    .pix_fmts = (const ga_nanaa AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
