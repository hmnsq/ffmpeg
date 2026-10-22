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

#समावेश "config.h"

#अगर HAVE_VAAPI_WIN32
#   include <windows.h>
#घोषणा COBJMACROS
#   include <initguid.h>
#   include <dxgi1_2.h>
#   include "compat/w32dlfcn.h"
#   include <va/va_win32.h>
प्रकार HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, व्योम **ppFactory);
#पूर्ण_अगर
#अगर HAVE_VAAPI_X11
#   include <va/va_x11.h>
#पूर्ण_अगर
#अगर HAVE_VAAPI_DRM
#   include <va/va_drm.h>
#पूर्ण_अगर

#अगर CONFIG_LIBDRM
#   include <va/va_drmcommon.h>
#   include <xf86drm.h>
#   include <drm_fourcc.h>
#   ifndef DRM_FORMAT_MOD_INVALID
#       define DRM_FORMAT_MOD_INVALID ((1ULL << 56) - 1)
#   endif
#पूर्ण_अगर

#समावेश <fcntl.h>
#अगर HAVE_UNISTD_H
#   include <unistd.h>
#पूर्ण_अगर


#समावेश "avassert.h"
#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_drm.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_vaapi.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "pixfmt.h"


प्रकार काष्ठा VAAPIDevicePriv {
#अगर HAVE_VAAPI_X11
    Display *x11_display;
#पूर्ण_अगर

    पूर्णांक drm_fd;
} VAAPIDevicePriv;

प्रकार काष्ठा VAAPISurfaceFormat {
    क्रमागत AVPixelFormat pix_fmt;
    VAImageFormat image_format;
    अचिन्हित पूर्णांक fourcc;
} VAAPISurfaceFormat;

प्रकार काष्ठा VAAPIDeviceContext {
    /**
     * The public AVVAAPIDeviceContext. See hwcontext_vaapi.h for it.
     */
    AVVAAPIDeviceContext p;

    // Surface formats which can be used with this device.
    VAAPISurfaceFormat *formats;
    पूर्णांक              nb_formats;
} VAAPIDeviceContext;

प्रकार काष्ठा VAAPIFramesContext {
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
    पूर्णांक अभाज्य_2_import_unsupported;
} VAAPIFramesContext;

प्रकार काष्ठा VAAPIMapping {
    // Handle to the derived or copied image which is mapped.
    VAImage image;
    // The mapping flags actually used.
    पूर्णांक flags;
} VAAPIMapping;

प्रकार काष्ठा VAAPIFormat {
    अचिन्हित पूर्णांक fourcc;
    अचिन्हित पूर्णांक rt_format;
    क्रमागत AVPixelFormat pix_fmt;
    पूर्णांक chroma_planes_swapped;
} VAAPIFormatDescriptor;

#घोषणा MAP(va, rt, av, swap_uv) { \
        VA_FOURCC_ ## va, \
        VA_RT_FORMAT_ ## rt, \
        AV_PIX_FMT_ ## av, \
        swap_uv, \
    }
// The map fourcc <-> pix_fmt isn't bijective because of the annoying U/V
// plane swap cases.  The frame handling below tries to hide these.
अटल स्थिर VAAPIFormatDescriptor vaapi_format_map[] = {
    MAP(NV12, YUV420,  NV12,    0),
#अगर_घोषित VA_FOURCC_I420
    MAP(I420, YUV420,  YUV420P, 0),
#पूर्ण_अगर
    MAP(YV12, YUV420,  YUV420P, 1),
    MAP(IYUV, YUV420,  YUV420P, 0),
    MAP(422H, YUV422,  YUV422P, 0),
#अगर_घोषित VA_FOURCC_YV16
    MAP(YV16, YUV422,  YUV422P, 1),
#पूर्ण_अगर
    MAP(UYVY, YUV422,  UYVY422, 0),
    MAP(YUY2, YUV422,  YUYV422, 0),
#अगर_घोषित VA_FOURCC_Y210
    MAP(Y210, YUV422_10,  Y210, 0),
#पूर्ण_अगर
#अगर_घोषित VA_FOURCC_Y212
    MAP(Y212, YUV422_12,  Y212, 0),
#पूर्ण_अगर
    MAP(411P, YUV411,  YUV411P, 0),
    MAP(422V, YUV422,  YUV440P, 0),
    MAP(444P, YUV444,  YUV444P, 0),
#अगर_घोषित VA_FOURCC_XYUV
    MAP(XYUV, YUV444,  VUYX,    0),
#पूर्ण_अगर
    MAP(Y800, YUV400,  GRAY8,   0),
#अगर_घोषित VA_FOURCC_P010
    MAP(P010, YUV420_10BPP, P010, 0),
#पूर्ण_अगर
#अगर_घोषित VA_FOURCC_P012
    MAP(P012, YUV420_12, P012, 0),
#पूर्ण_अगर
    MAP(BGRA, RGB32,   BGRA, 0),
    MAP(BGRX, RGB32,   BGR0, 0),
    MAP(RGBA, RGB32,   RGBA, 0),
    MAP(RGBX, RGB32,   RGB0, 0),
#अगर_घोषित VA_FOURCC_ABGR
    MAP(ABGR, RGB32,   ABGR, 0),
    MAP(XBGR, RGB32,   0BGR, 0),
#पूर्ण_अगर
    MAP(ARGB, RGB32,   ARGB, 0),
    MAP(XRGB, RGB32,   0RGB, 0),
#अगर_घोषित VA_FOURCC_X2R10G10B10
    MAP(X2R10G10B10, RGB32_10, X2RGB10, 0),
#पूर्ण_अगर
#अगर_घोषित VA_FOURCC_Y410
    // libva doesn't include a fourcc for XV30 and the driver only declares
    // support for Y410, so we must fudge the mapping here.
    MAP(Y410, YUV444_10,  XV30, 0),
#पूर्ण_अगर
#अगर_घोषित VA_FOURCC_Y412
    // libva doesn't include a fourcc for XV36 and the driver only declares
    // support for Y412, so we must fudge the mapping here.
    MAP(Y412, YUV444_12,  XV36, 0),
#पूर्ण_अगर
};
#अघोषित MAP

अटल स्थिर VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(अचिन्हित पूर्णांक fourcc)
{
    पूर्णांक i;
    क्रम (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        अगर (vaapi_format_map[i].fourcc == fourcc)
            वापस &vaapi_format_map[i];
    वापस शून्य;
}

अटल स्थिर VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(क्रमागत AVPixelFormat pix_fmt, स्थिर VAAPIFormatDescriptor *पूर्व)
{
    स्थिर VAAPIFormatDescriptor *end = &vaapi_format_map[FF_ARRAY_ELEMS(vaapi_format_map)];
    अगर (!पूर्व)
        पूर्व = vaapi_format_map;
    अन्यथा
        पूर्व++;

    क्रम (; पूर्व < end; पूर्व++)
        अगर (पूर्व->pix_fmt == pix_fmt)
            वापस पूर्व;
    वापस शून्य;
}

अटल क्रमागत AVPixelFormat vaapi_pix_fmt_from_fourcc(अचिन्हित पूर्णांक fourcc)
{
    स्थिर VAAPIFormatDescriptor *desc;
    desc = vaapi_format_from_fourcc(fourcc);
    अगर (desc)
        वापस desc->pix_fmt;
    अन्यथा
        वापस AV_PIX_FMT_NONE;
}

अटल पूर्णांक vaapi_get_img_desc_and_format(AVHWDeviceContext *hwdev,
                                  क्रमागत AVPixelFormat pix_fmt,
                                  स्थिर VAAPIFormatDescriptor **_desc,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    स्थिर VAAPIFormatDescriptor *desc = शून्य;
    पूर्णांक i;

    जबतक ((desc = vaapi_format_from_pix_fmt(pix_fmt, desc))) {
        क्रम (i = 0; i < ctx->nb_formats; i++) {
            अगर (ctx->formats[i].fourcc == desc->fourcc) {
                अगर (_desc)
                    *_desc = desc;
                अगर (image_format)
                    *image_format = &ctx->formats[i].image_format;
                वापस 0;
            }
        }
    }

    वापस AVERROR(ENOSYS);
}

अटल पूर्णांक vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  क्रमागत AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    अगर (!image_format)
        वापस AVERROR(EINVAL);
    वापस vaapi_get_img_desc_and_format(hwdev, pix_fmt, शून्य, image_format);
}

अटल पूर्णांक vaapi_frames_get_constraints(AVHWDeviceContext *hwdev,
                                        स्थिर व्योम *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    स्थिर AVVAAPIHWConfig *config = hwconfig;
    VASurfaceAttrib *attr_list = शून्य;
    VAStatus vas;
    क्रमागत AVPixelFormat pix_fmt;
    अचिन्हित पूर्णांक fourcc;
    पूर्णांक err, i, j, attr_गिनती, pix_fmt_गिनती;

    अगर (config &&
        !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
        attr_गिनती = 0;
        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       0, &attr_गिनती);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            जाओ fail;
        }

        attr_list = av_malloc(attr_गिनती * माप(*attr_list));
        अगर (!attr_list) {
            err = AVERROR(ENOMEM);
            जाओ fail;
        }

        vas = vaQuerySurfaceAttributes(hwctx->display, config->config_id,
                                       attr_list, &attr_गिनती);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query surface attributes: "
                   "%d (%s).\n", vas, vaErrorStr(vas));
            err = AVERROR(ENOSYS);
            जाओ fail;
        }

        pix_fmt_गिनती = 0;
        क्रम (i = 0; i < attr_गिनती; i++) {
            चयन (attr_list[i].type) {
            हाल VASurfaceAttribPixelFormat:
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
                अगर (pix_fmt != AV_PIX_FMT_NONE) {
                    ++pix_fmt_गिनती;
                } अन्यथा {
                    // Something unsupported - ignore.
                }
                अवरोध;
            हाल VASurfaceAttribMinWidth:
                constraints->min_width  = attr_list[i].मूल्य.मूल्य.i;
                अवरोध;
            हाल VASurfaceAttribMinHeight:
                constraints->min_height = attr_list[i].मूल्य.मूल्य.i;
                अवरोध;
            हाल VASurfaceAttribMaxWidth:
                constraints->max_width  = attr_list[i].मूल्य.मूल्य.i;
                अवरोध;
            हाल VASurfaceAttribMaxHeight:
                constraints->max_height = attr_list[i].मूल्य.मूल्य.i;
                अवरोध;
            }
        }
        अगर (pix_fmt_गिनती == 0) {
            // Nothing usable found.  Presumably there exists something which
            // works, so leave the set null to indicate unknown.
            constraints->valid_sw_formats = शून्य;
        } अन्यथा {
            constraints->valid_sw_formats = av_malloc_array(pix_fmt_गिनती + 1,
                                                            माप(pix_fmt));
            अगर (!constraints->valid_sw_formats) {
                err = AVERROR(ENOMEM);
                जाओ fail;
            }

            क्रम (i = j = 0; i < attr_गिनती; i++) {
                पूर्णांक k;

                अगर (attr_list[i].type != VASurfaceAttribPixelFormat)
                    जारी;
                fourcc = attr_list[i].मूल्य.मूल्य.i;
                pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);

                अगर (pix_fmt == AV_PIX_FMT_NONE)
                    जारी;

                क्रम (k = 0; k < j; k++) {
                    अगर (constraints->valid_sw_formats[k] == pix_fmt)
                        अवरोध;
                }

                अगर (k == j)
                    constraints->valid_sw_formats[j++] = pix_fmt;
            }
            constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
        }
    } अन्यथा {
        // No configuration supplied.
        // Return the full set of image formats known by the implementation.
        constraints->valid_sw_formats = av_malloc_array(ctx->nb_formats + 1,
                                                        माप(pix_fmt));
        अगर (!constraints->valid_sw_formats) {
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
        क्रम (i = j = 0; i < ctx->nb_formats; i++) {
            पूर्णांक k;

            क्रम (k = 0; k < j; k++) {
                अगर (constraints->valid_sw_formats[k] == ctx->formats[i].pix_fmt)
                    अवरोध;
            }

            अगर (k == j)
                constraints->valid_sw_formats[j++] = ctx->formats[i].pix_fmt;
        }

        constraints->valid_sw_formats[j] = AV_PIX_FMT_NONE;
    }

    constraints->valid_hw_formats = av_malloc_array(2, माप(pix_fmt));
    अगर (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_VAAPI;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    err = 0;
fail:
    av_freep(&attr_list);
    वापस err;
}

अटल स्थिर काष्ठा {
    स्थिर अक्षर *friendly_name;
    स्थिर अक्षर *match_string;
    अचिन्हित पूर्णांक quirks;
} vaapi_driver_quirks_table[] = {
#अगर !VA_CHECK_VERSION(1, 0, 0)
    // The i965 driver did not conform before version 2.0.
    {
        "Intel i965 (Quick Sync)",
        "i965",
        AV_VAAPI_DRIVER_QUIRK_RENDER_PARAM_BUFFERS,
    },
#पूर्ण_अगर
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

अटल पूर्णांक vaapi_device_init(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;
    AVVAAPIDeviceContext *hwctx = &ctx->p;
    VAImageFormat *image_list = शून्य;
    VAStatus vas;
    स्थिर अक्षर *vendor_string;
    पूर्णांक err, i, image_गिनती;
    क्रमागत AVPixelFormat pix_fmt;
    अचिन्हित पूर्णांक fourcc;

    image_गिनती = va_Max_अंक_Image_Formats(hwctx->display);
    अगर (image_गिनती <= 0) {
        err = AVERROR(EIO);
        जाओ fail;
    }
    image_list = av_malloc(image_गिनती * माप(*image_list));
    अगर (!image_list) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }
    vas = vaQueryImageFormats(hwctx->display, image_list, &image_गिनती);
    अगर (vas != VA_STATUS_SUCCESS) {
        err = AVERROR(EIO);
        जाओ fail;
    }

    ctx->formats  = av_malloc(image_गिनती * माप(*ctx->formats));
    अगर (!ctx->formats) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }
    ctx->nb_formats = 0;
    क्रम (i = 0; i < image_गिनती; i++) {
        fourcc  = image_list[i].fourcc;
        pix_fmt = vaapi_pix_fmt_from_fourcc(fourcc);
        अगर (pix_fmt == AV_PIX_FMT_NONE) {
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
    अगर (vendor_string)
        av_log(hwdev, AV_LOG_VERBOSE, "VAAPI driver: %s.\n", vendor_string);

    अगर (hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_USER_SET) {
        av_log(hwdev, AV_LOG_VERBOSE, "Using quirks set by user (%#x).\n",
               hwctx->driver_quirks);
    } अन्यथा {
        // Detect the driver in use and set quirk flags if necessary.
        hwctx->driver_quirks = 0;
        अगर (vendor_string) {
            क्रम (i = 0; i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table); i++) {
                अगर (म_माला(vendor_string,
                           vaapi_driver_quirks_table[i].match_string)) {
                    av_log(hwdev, AV_LOG_VERBOSE, "Matched driver string "
                           "as known nonstandard driver \"%s\", setting "
                           "quirks (%#x).\n",
                           vaapi_driver_quirks_table[i].friendly_name,
                           vaapi_driver_quirks_table[i].quirks);
                    hwctx->driver_quirks |=
                        vaapi_driver_quirks_table[i].quirks;
                    अवरोध;
                }
            }
            अगर (!(i < FF_ARRAY_ELEMS(vaapi_driver_quirks_table))) {
                av_log(hwdev, AV_LOG_VERBOSE, "Driver not found in known "
                       "nonstandard list, using standard behaviour.\n");
            }
        } अन्यथा {
            av_log(hwdev, AV_LOG_VERBOSE, "Driver has no vendor string, "
                   "assuming standard behaviour.\n");
        }
    }

    av_free(image_list);
    वापस 0;
fail:
    av_freep(&ctx->formats);
    av_free(image_list);
    वापस err;
}

अटल व्योम vaapi_device_uninit(AVHWDeviceContext *hwdev)
{
    VAAPIDeviceContext *ctx = hwdev->hwctx;

    av_freep(&ctx->formats);
}

अटल व्योम vaapi_बफर_free(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWFramesContext     *hwfc = opaque;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)तथ्य;

    vas = vaDestroySurfaces(hwctx->display, &surface_id, 1);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }
}

अटल AVBufferRef *vaapi_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    अगर (hwfc->initial_pool_आकार > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_आकार)
        वापस शून्य;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        वापस शून्य;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_बफर_create((uint8_t*)(uintptr_t)surface_id,
                           माप(surface_id), &vaapi_बफर_free,
                           hwfc, AV_बफर_FLAG_READONLY);
    अगर (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        वापस शून्य;
    }

    अगर (hwfc->initial_pool_आकार > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_आकार);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    वापस ref;
}

अटल पूर्णांक vaapi_frames_init(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext     *ctx = hwfc->hwctx;
    AVVAAPIFramesContext  *avfc = &ctx->p;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    स्थिर VAAPIFormatDescriptor *desc = शून्य;
    VAImageFormat *expected_format = शून्य;
    AVBufferRef *test_surface = शून्य;
    VASurfaceID test_surface_id;
    VAImage test_image;
    VAStatus vas;
    पूर्णांक err, i;

    err = vaapi_get_img_desc_and_format(hwfc->device_ctx, hwfc->sw_format,
                                        &desc, &expected_format);
    अगर (err < 0) {
        // Use a relaxed check when pool exist. It can be an external pool.
        अगर (!hwfc->pool || !vaapi_format_from_pix_fmt(hwfc->sw_format, शून्य)) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported format: %s.\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            वापस AVERROR(EINVAL);
        }
    }

    अगर (!hwfc->pool) {
        अगर (!(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_SURFACE_ATTRIBUTES)) {
            पूर्णांक need_memory_type = !(hwctx->driver_quirks & AV_VAAPI_DRIVER_QUIRK_ATTRIB_MEMTYPE);
            पूर्णांक need_pixel_format = 1;
            क्रम (i = 0; i < avfc->nb_attributes; i++) {
                अगर (avfc->attributes[i].type == VASurfaceAttribMemoryType)
                    need_memory_type  = 0;
                अगर (avfc->attributes[i].type == VASurfaceAttribPixelFormat)
                    need_pixel_format = 0;
            }
            ctx->nb_attributes =
                avfc->nb_attributes + need_memory_type + need_pixel_format;

            ctx->attributes = av_malloc(ctx->nb_attributes *
                                        माप(*ctx->attributes));
            अगर (!ctx->attributes) {
                err = AVERROR(ENOMEM);
                जाओ fail;
            }

            क्रम (i = 0; i < avfc->nb_attributes; i++)
                ctx->attributes[i] = avfc->attributes[i];
            अगर (need_memory_type) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribMemoryType,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                    .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_VA,
                };
            }
            अगर (need_pixel_format) {
                ctx->attributes[i++] = (VASurfaceAttrib) {
                    .type          = VASurfaceAttribPixelFormat,
                    .flags         = VA_SURFACE_ATTRIB_SETTABLE,
                    .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                    .मूल्य.मूल्य.i = desc->fourcc,
                };
            }
            av_assert0(i == ctx->nb_attributes);
        } अन्यथा {
            ctx->attributes = शून्य;
            ctx->nb_attributes = 0;
        }

        ctx->rt_format = desc->rt_format;

        अगर (hwfc->initial_pool_आकार > 0) {
            // This pool will be usable as a render target, so we need to store
            // all of the surface IDs somewhere that vaCreateContext() calls
            // will be able to access them.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = av_malloc(hwfc->initial_pool_आकार *
                                          माप(*avfc->surface_ids));
            अगर (!avfc->surface_ids) {
                err = AVERROR(ENOMEM);
                जाओ fail;
            }
        } अन्यथा {
            // This pool allows dynamic sizing, and will not be usable as a
            // render target.
            avfc->nb_surfaces = 0;
            avfc->surface_ids = शून्य;
        }

        ffhwframesctx(hwfc)->pool_internal =
            av_बफर_pool_init2(माप(VASurfaceID), hwfc,
                                 &vaapi_pool_alloc, शून्य);
        अगर (!ffhwframesctx(hwfc)->pool_internal) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create VAAPI surface pool.\n");
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
    }

    // Allocate a single surface to test whether vaDeriveImage() is going
    // to work for the specific configuration.
    अगर (hwfc->pool) {
        test_surface = av_बफर_pool_get(hwfc->pool);
        अगर (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "user-configured buffer pool.\n");
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
    } अन्यथा {
        test_surface = av_बफर_pool_get(ffhwframesctx(hwfc)->pool_internal);
        अगर (!test_surface) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to allocate a surface from "
                   "internal buffer pool.\n");
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
    }
    test_surface_id = (VASurfaceID)(uintptr_t)test_surface->तथ्य;

    ctx->derive_works = 0;
    अगर (expected_format) {
        vas = vaDeriveImage(hwctx->display, test_surface_id, &test_image);
        अगर (vas == VA_STATUS_SUCCESS) {
            अगर (expected_format->fourcc == test_image.format.fourcc) {
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

    av_बफर_unref(&test_surface);
    वापस 0;

fail:
    av_बफर_unref(&test_surface);
    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
    वापस err;
}

अटल व्योम vaapi_frames_uninit(AVHWFramesContext *hwfc)
{
    VAAPIFramesContext    *ctx = hwfc->hwctx;
    AVVAAPIFramesContext *avfc = &ctx->p;

    av_freep(&avfc->surface_ids);
    av_freep(&ctx->attributes);
}

अटल पूर्णांक vaapi_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[3] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_VAAPI;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    वापस 0;
}

अटल पूर्णांक vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      क्रमागत AVHWFrameTransferDirection dir,
                                      क्रमागत AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->hwctx;
    क्रमागत AVPixelFormat *pix_fmts;
    पूर्णांक i, k, sw_format_available;

    sw_format_available = 0;
    क्रम (i = 0; i < ctx->nb_formats; i++) {
        अगर (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * माप(*pix_fmts));
    अगर (!pix_fmts)
        वापस AVERROR(ENOMEM);

    अगर (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } अन्यथा {
        k = 0;
    }
    क्रम (i = 0; i < ctx->nb_formats; i++) {
        अगर (ctx->formats[i].pix_fmt == hwfc->sw_format)
            जारी;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    वापस 0;
}

अटल व्योम vaapi_unmap_frame(AVHWFramesContext *hwfc,
                              HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIMapping           *map = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->तथ्य[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap surface %#x.\n", surface_id);

    vas = va_Unmap_बफर(hwctx->display, map->image.buf);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to unmap image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    अगर ((map->flags & AV_HWFRAME_MAP_WRITE) &&
        !(map->flags & AV_HWFRAME_MAP_DIRECT)) {
        vas = vaPutImage(hwctx->display, surface_id, map->image.image_id,
                         0, 0, hwfc->width, hwfc->height,
                         0, 0, hwfc->width, hwfc->height);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to write image to surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        }
    }

    vas = vaDestroyImage(hwctx->display, map->image.image_id);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
    }

    av_free(map);
}

अटल पूर्णांक vaapi_map_frame(AVHWFramesContext *hwfc,
                           AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIFramesContext *ctx = hwfc->hwctx;
    VASurfaceID surface_id;
    स्थिर VAAPIFormatDescriptor *desc;
    VAImageFormat *image_format;
    VAAPIMapping *map;
    VAStatus vas;
    व्योम *address = शून्य;
    पूर्णांक err, i;
#अगर VA_CHECK_VERSION(1, 21, 0)
    uint32_t vaflags = 0;
#पूर्ण_अगर

    surface_id = (VASurfaceID)(uintptr_t)src->तथ्य[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map surface %#x.\n", surface_id);

    अगर (!ctx->derive_works && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but it is not possible.
        वापस AVERROR(EINVAL);
    }
    अगर (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अगर (dst->format != hwfc->sw_format && (flags & AV_HWFRAME_MAP_DIRECT)) {
        // Requested direct mapping but the formats do not match.
        वापस AVERROR(EINVAL);
    }

    err = vaapi_get_image_format(hwfc->device_ctx, dst->format, &image_format);
    अगर (err < 0) {
        // Requested format is not a valid output format.
        वापस err;
    }

    map = av_malloc(माप(*map));
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->flags = flags;
    map->image.image_id = VA_INVALID_ID;

    vas = vaSyncSurface(hwctx->display, surface_id);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जाओ fail;
    }

    // The memory which we map using derive need not be connected to the CPU
    // in a way conducive to fast access.  On Gen7-Gen9 Intel graphics, the
    // memory is mappable but not cached, so normal memcpy()-like access is
    // very slow to read it (but writing is ok).  It is possible to read much
    // faster with a copy routine which is aware of the limitation, but we
    // assume for now that the user is not aware of that and would therefore
    // prefer not to be given direct-mapped memory if they request read access.
    अगर (ctx->derive_works && dst->format == hwfc->sw_format &&
        ((flags & AV_HWFRAME_MAP_DIRECT) || !(flags & AV_HWFRAME_MAP_READ))) {
        vas = vaDeriveImage(hwctx->display, surface_id, &map->image);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            जाओ fail;
        }
        अगर (map->image.format.fourcc != image_format->fourcc) {
            av_log(hwfc, AV_LOG_ERROR, "Derive image of surface %#x "
                   "is in wrong format: expected %#08x, got %#08x.\n",
                   surface_id, image_format->fourcc, map->image.format.fourcc);
            err = AVERROR(EIO);
            जाओ fail;
        }
        map->flags |= AV_HWFRAME_MAP_DIRECT;
    } अन्यथा {
        vas = vaCreateImage(hwctx->display, image_format,
                            hwfc->width, hwfc->height, &map->image);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "surface %#x: %d (%s).\n",
                   surface_id, vas, vaErrorStr(vas));
            err = AVERROR(EIO);
            जाओ fail;
        }
        अगर (!(flags & AV_HWFRAME_MAP_OVERWRITE)) {
            vas = vaGetImage(hwctx->display, surface_id, 0, 0,
                             hwfc->width, hwfc->height, map->image.image_id);
            अगर (vas != VA_STATUS_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to read image from "
                       "surface %#x: %d (%s).\n",
                       surface_id, vas, vaErrorStr(vas));
                err = AVERROR(EIO);
                जाओ fail;
            }
        }
    }

#अगर VA_CHECK_VERSION(1, 21, 0)
    अगर (flags & AV_HWFRAME_MAP_READ)
        vaflags |= VA_MAPBUFFER_FLAG_READ;
    अगर (flags & AV_HWFRAME_MAP_WRITE)
        vaflags |= VA_MAPBUFFER_FLAG_WRITE;
    // On drivers not implementing vaMapBuffer2 libva calls vaMapBuffer instead.
    vas = vaMapBuffer2(hwctx->display, map->image.buf, &address, vaflags);
#अन्यथा
    vas = va_Map_बफर(hwctx->display, map->image.buf, &address);
#पूर्ण_अगर
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to map image from surface "
               "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जाओ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_frame, map);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    क्रम (i = 0; i < map->image.अंक_planes; i++) {
        dst->तथ्य[i] = (uint8_t*)address + map->image.offsets[i];
        dst->linesize[i] = map->image.pitches[i];
    }

    desc = vaapi_format_from_fourcc(map->image.format.fourcc);
    अगर (desc && desc->chroma_planes_swapped) {
        // Chroma planes are YVU rather than YUV, so swap them.
        FFSWAP(uint8_t*, dst->तथ्य[1], dst->तथ्य[2]);
    }

    वापस 0;

fail:
    अगर (map) {
        अगर (address)
            va_Unmap_बफर(hwctx->display, map->image.buf);
        अगर (map->image.image_id != VA_INVALID_ID)
            vaDestroyImage(hwctx->display, map->image.image_id);
        av_free(map);
    }
    वापस err;
}

अटल पूर्णांक vaapi_transfer_तथ्य_from(AVHWFramesContext *hwfc,
                                    AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (dst->width > hwfc->width || dst->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = dst->format;

    err = vaapi_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    अगर (err)
        जाओ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक vaapi_transfer_तथ्य_to(AVHWFramesContext *hwfc,
                                  AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (src->width > hwfc->width || src->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = src->format;

    err = vaapi_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    अगर (err)
        जाओ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक vaapi_map_to_memory(AVHWFramesContext *hwfc, AVFrame *dst,
                               स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    err = vaapi_map_frame(hwfc, dst, src, flags);
    अगर (err)
        वापस err;

    err = av_frame_copy_props(dst, src);
    अगर (err)
        वापस err;

    वापस 0;
}

#अगर CONFIG_LIBDRM

#घोषणा DRM_MAP(va, layers, ...) { \
        VA_FOURCC_ ## va, \
        layers, \
        { __VA_ARGS__ } \
    }
अटल स्थिर काष्ठा {
    uint32_t va_fourcc;
    पूर्णांक   nb_layer_formats;
    uint32_t layer_formats[AV_DRM_MAX_PLANES];
} vaapi_drm_format_map[] = {
#अगर_घोषित DRM_FORMAT_R8
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_RG88),
    DRM_MAP(NV12, 2, DRM_FORMAT_R8,  DRM_FORMAT_GR88),
#पूर्ण_अगर
    DRM_MAP(NV12, 1, DRM_FORMAT_NV12),
#अगर defined(VA_FOURCC_P010) && defined(DRM_FORMAT_R16)
    DRM_MAP(P010, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#पूर्ण_अगर
#अगर defined(VA_FOURCC_P012) && defined(DRM_FORMAT_R16)
    DRM_MAP(P012, 2, DRM_FORMAT_R16, DRM_FORMAT_RG1616),
#पूर्ण_अगर
    DRM_MAP(BGRA, 1, DRM_FORMAT_ARGB8888),
    DRM_MAP(BGRX, 1, DRM_FORMAT_XRGB8888),
    DRM_MAP(RGBA, 1, DRM_FORMAT_ABGR8888),
    DRM_MAP(RGBX, 1, DRM_FORMAT_XBGR8888),
#अगर_घोषित VA_FOURCC_ABGR
    DRM_MAP(ABGR, 1, DRM_FORMAT_RGBA8888),
    DRM_MAP(XBGR, 1, DRM_FORMAT_RGBX8888),
#पूर्ण_अगर
    DRM_MAP(ARGB, 1, DRM_FORMAT_BGRA8888),
    DRM_MAP(XRGB, 1, DRM_FORMAT_BGRX8888),
#अगर defined(VA_FOURCC_XYUV) && defined(DRM_FORMAT_XYUV8888)
    DRM_MAP(XYUV, 1, DRM_FORMAT_XYUV8888),
#पूर्ण_अगर
#अगर defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU2101010)
    DRM_MAP(Y410, 1, DRM_FORMAT_XVYU2101010),
#पूर्ण_अगर
#अगर defined(VA_FOURCC_Y412) && defined(DRM_FORMAT_XVYU12_16161616)
    DRM_MAP(Y412, 1, DRM_FORMAT_XVYU12_16161616),
#पूर्ण_अगर
#अगर defined(VA_FOURCC_X2R10G10B10) && defined(DRM_FORMAT_XRGB2101010)
    DRM_MAP(X2R10G10B10, 1, DRM_FORMAT_XRGB2101010),
#पूर्ण_अगर
};
#अघोषित DRM_MAP

अटल व्योम vaapi_unmap_from_drm(AVHWFramesContext *dst_fc,
                                 HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)hwmap->priv;

    av_log(dst_fc, AV_LOG_DEBUG, "Destroy surface %#x.\n", surface_id);

    vaDestroySurfaces(dst_dev->display, &surface_id, 1);
}

अटल पूर्णांक vaapi_map_from_drm(AVHWFramesContext *src_fc, AVFrame *dst,
                              स्थिर AVFrame *src, पूर्णांक flags)
{
#अगर VA_CHECK_VERSION(1, 1, 0)
    VAAPIFramesContext    *src_vafc = src_fc->hwctx;
    पूर्णांक use_prime2;
#अन्यथा
    पूर्णांक k;
#पूर्ण_अगर
    AVHWFramesContext      *dst_fc =
        (AVHWFramesContext*)dst->hw_frames_ctx->तथ्य;
    AVVAAPIDeviceContext  *dst_dev = dst_fc->device_ctx->hwctx;
    स्थिर AVDRMFrameDescriptor *desc;
    स्थिर VAAPIFormatDescriptor *format_desc;
    VASurfaceID surface_id;
    VAStatus vas = VA_STATUS_SUCCESS;
    uint32_t va_fourcc;
    पूर्णांक err, i, j;

#अगर !VA_CHECK_VERSION(1, 1, 0)
    अचिन्हित दीर्घ बफर_handle;
    VASurfaceAttribExternalBuffers बफर_desc;
    VASurfaceAttrib attrs[2] = {
        {
            .type  = VASurfaceAttribMemoryType,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
            .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_अभाज्य,
        },
        {
            .type  = VASurface_Attrib_External_बफर_Descriptor,
            .flags = VA_SURFACE_ATTRIB_SETTABLE,
            .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
            .मूल्य.मूल्य.p = &बफर_desc,
        }
    };
#पूर्ण_अगर

    desc = (AVDRMFrameDescriptor*)src->तथ्य[0];

    अगर (desc->nb_objects != 1) {
        av_log(dst_fc, AV_LOG_ERROR, "VAAPI can only map frames "
               "made from a single DRM object.\n");
        वापस AVERROR(EINVAL);
    }

    va_fourcc = 0;
    क्रम (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        अगर (desc->nb_layers != vaapi_drm_format_map[i].nb_layer_formats)
            जारी;
        क्रम (j = 0; j < desc->nb_layers; j++) {
            अगर (desc->layers[j].format !=
                vaapi_drm_format_map[i].layer_formats[j])
                अवरोध;
        }
        अगर (j != desc->nb_layers)
            जारी;
        va_fourcc = vaapi_drm_format_map[i].va_fourcc;
        अवरोध;
    }
    अगर (!va_fourcc) {
        av_log(dst_fc, AV_LOG_ERROR, "DRM format not supported "
               "by VAAPI.\n");
        वापस AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map DRM object %d to VAAPI as "
           "%08x.\n", desc->objects[0].fd, va_fourcc);

    format_desc = vaapi_format_from_fourcc(va_fourcc);
    av_assert0(format_desc);

#अगर VA_CHECK_VERSION(1, 1, 0)
    use_prime2 = !src_vafc->अभाज्य_2_import_unsupported &&
                 desc->objects[0].format_modifier != DRM_FORMAT_MOD_INVALID;
    अगर (use_prime2) {
        VADRMPRIMESurfaceDescriptor अभाज्य_desc;
        VASurfaceAttrib अभाज्य_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_अभाज्य_2,
            },
            {
                .type  = VASurface_Attrib_External_बफर_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
                .मूल्य.मूल्य.p = &अभाज्य_desc,
            }
        };
        अभाज्य_desc.fourcc = va_fourcc;
        अभाज्य_desc.width = src_fc->width;
        अभाज्य_desc.height = src_fc->height;
        अभाज्य_desc.अंक_objects = desc->nb_objects;
        क्रम (i = 0; i < desc->nb_objects; ++i) {
            अभाज्य_desc.objects[i].fd = desc->objects[i].fd;
            अभाज्य_desc.objects[i].आकार = desc->objects[i].आकार;
            अभाज्य_desc.objects[i].drm_format_modifier =
                    desc->objects[i].format_modifier;
        }

        अभाज्य_desc.अंक_layers = desc->nb_layers;
        क्रम (i = 0; i < desc->nb_layers; ++i) {
            अभाज्य_desc.layers[i].drm_format = desc->layers[i].format;
            अभाज्य_desc.layers[i].अंक_planes = desc->layers[i].nb_planes;
            क्रम (j = 0; j < desc->layers[i].nb_planes; ++j) {
                अभाज्य_desc.layers[i].object_सूचकांक[j] =
                        desc->layers[i].planes[j].object_सूचकांक;
                अभाज्य_desc.layers[i].offset[j] = desc->layers[i].planes[j].offset;
                अभाज्य_desc.layers[i].pitch[j] = desc->layers[i].planes[j].pitch;
            }

            अगर (format_desc->chroma_planes_swapped &&
                desc->layers[i].nb_planes == 3) {
                FFSWAP(uint32_t, अभाज्य_desc.layers[i].pitch[1],
                    अभाज्य_desc.layers[i].pitch[2]);
                FFSWAP(uint32_t, अभाज्य_desc.layers[i].offset[1],
                    अभाज्य_desc.layers[i].offset[2]);
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
                               अभाज्य_attrs, FF_ARRAY_ELEMS(अभाज्य_attrs));
        अगर (vas != VA_STATUS_SUCCESS)
            src_vafc->अभाज्य_2_import_unsupported = 1;
    }

    अगर (!use_prime2 || vas != VA_STATUS_SUCCESS) {
        पूर्णांक k;
        uintptr_t बफर_handle;
        VASurfaceAttribExternalBuffers बफर_desc;
        VASurfaceAttrib बफर_attrs[2] = {
            {
                .type  = VASurfaceAttribMemoryType,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Integer,
                .मूल्य.मूल्य.i = VA_SURFACE_ATTRIB_MEM_TYPE_DRM_अभाज्य,
            },
            {
                .type  = VASurface_Attrib_External_बफर_Descriptor,
                .flags = VA_SURFACE_ATTRIB_SETTABLE,
                .मूल्य.type    = VAGeneric_मूल्य_Type_Pointer,
                .मूल्य.मूल्य.p = &बफर_desc,
            }
        };

        बफर_handle = desc->objects[0].fd;
        बफर_desc.pixel_format = va_fourcc;
        बफर_desc.width        = src_fc->width;
        बफर_desc.height       = src_fc->height;
        बफर_desc.तथ्य_आकार    = desc->objects[0].आकार;
        बफर_desc.buffers      = &बफर_handle;
        बफर_desc.अंक_buffers  = 1;
        बफर_desc.flags        = 0;

        k = 0;
        क्रम (i = 0; i < desc->nb_layers; i++) {
            क्रम (j = 0; j < desc->layers[i].nb_planes; j++) {
                बफर_desc.pitches[k] = desc->layers[i].planes[j].pitch;
                बफर_desc.offsets[k] = desc->layers[i].planes[j].offset;
                ++k;
            }
        }
        बफर_desc.अंक_planes = k;

        अगर (format_desc->chroma_planes_swapped &&
            बफर_desc.अंक_planes == 3) {
            FFSWAP(uint32_t, बफर_desc.pitches[1], बफर_desc.pitches[2]);
            FFSWAP(uint32_t, बफर_desc.offsets[1], बफर_desc.offsets[2]);
        }

        vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                               src->width, src->height,
                               &surface_id, 1,
                               बफर_attrs, FF_ARRAY_ELEMS(बफर_attrs));
    }
#अन्यथा
    बफर_handle = desc->objects[0].fd;
    बफर_desc.pixel_format = va_fourcc;
    बफर_desc.width        = src_fc->width;
    बफर_desc.height       = src_fc->height;
    बफर_desc.तथ्य_आकार    = desc->objects[0].आकार;
    बफर_desc.buffers      = &बफर_handle;
    बफर_desc.अंक_buffers  = 1;
    बफर_desc.flags        = 0;

    k = 0;
    क्रम (i = 0; i < desc->nb_layers; i++) {
        क्रम (j = 0; j < desc->layers[i].nb_planes; j++) {
            बफर_desc.pitches[k] = desc->layers[i].planes[j].pitch;
            बफर_desc.offsets[k] = desc->layers[i].planes[j].offset;
            ++k;
        }
    }
    बफर_desc.अंक_planes = k;

    अगर (format_desc->chroma_planes_swapped &&
        बफर_desc.अंक_planes == 3) {
        FFSWAP(uint32_t, बफर_desc.pitches[1], बफर_desc.pitches[2]);
        FFSWAP(uint32_t, बफर_desc.offsets[1], बफर_desc.offsets[2]);
    }

    vas = vaCreateSurfaces(dst_dev->display, format_desc->rt_format,
                           src->width, src->height,
                           &surface_id, 1,
                           attrs, FF_ARRAY_ELEMS(attrs));
#पूर्ण_अगर
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to create surface from DRM "
               "object: %d (%s).\n", vas, vaErrorStr(vas));
        वापस AVERROR(EIO);
    }
    av_log(dst_fc, AV_LOG_DEBUG, "Create surface %#x.\n", surface_id);

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vaapi_unmap_from_drm,
                                (व्योम*)(uintptr_t)surface_id);
    अगर (err < 0)
        वापस err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->तथ्य[3] = (uint8_t*)(uintptr_t)surface_id;

    av_log(dst_fc, AV_LOG_DEBUG, "Mapped DRM object %d to "
           "surface %#x.\n", desc->objects[0].fd, surface_id);

    वापस 0;
}

#अगर VA_CHECK_VERSION(1, 1, 0)
अटल व्योम vaapi_unmap_to_drm_esh(AVHWFramesContext *hwfc,
                                   HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;
    पूर्णांक i;

    क्रम (i = 0; i < drm_desc->nb_objects; i++)
        बंद(drm_desc->objects[i].fd);

    av_freep(&drm_desc);
}

अटल पूर्णांक vaapi_map_to_drm_esh(AVHWFramesContext *hwfc, AVFrame *dst,
                                स्थिर AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    VADRMPRIMESurfaceDescriptor va_desc;
    AVDRMFrameDescriptor *drm_desc = शून्य;
    uint32_t export_flags;
    पूर्णांक err, i, j;

    surface_id = (VASurfaceID)(uintptr_t)src->तथ्य[3];

    export_flags = VA_EXPORT_SURFACE_SEPARATE_LAYERS;
    अगर (flags & AV_HWFRAME_MAP_READ) {
        export_flags |= VA_EXPORT_SURFACE_READ_ONLY;

        vas = vaSyncSurface(hwctx->display, surface_id);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to sync surface "
                   "%#x: %d (%s).\n", surface_id, vas, vaErrorStr(vas));
            वापस AVERROR(EIO);
        }
    }

    अगर (flags & AV_HWFRAME_MAP_WRITE)
        export_flags |= VA_EXPORT_SURFACE_WRITE_ONLY;

    vas = vaExportSurfaceHandle(hwctx->display, surface_id,
                                VA_SURFACE_ATTRIB_MEM_TYPE_DRM_अभाज्य_2,
                                export_flags, &va_desc);
    अगर (vas != VA_STATUS_SUCCESS) {
        अगर (vas == VA_STATUS_ERROR_UNIMPLEMENTED)
            वापस AVERROR(ENOSYS);
        av_log(hwfc, AV_LOG_ERROR, "Failed to export surface %#x: "
               "%d (%s).\n", surface_id, vas, vaErrorStr(vas));
        वापस AVERROR(EIO);
    }

    drm_desc = av_mallocz(माप(*drm_desc));
    अगर (!drm_desc) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    // By some bizarre coincidence, these structures are very similar...
    drm_desc->nb_objects = va_desc.अंक_objects;
    क्रम (i = 0; i < va_desc.अंक_objects; i++) {
        drm_desc->objects[i].fd   = va_desc.objects[i].fd;
        drm_desc->objects[i].आकार = va_desc.objects[i].आकार;
        drm_desc->objects[i].format_modifier =
            va_desc.objects[i].drm_format_modifier;
    }
    drm_desc->nb_layers = va_desc.अंक_layers;
    क्रम (i = 0; i < va_desc.अंक_layers; i++) {
        drm_desc->layers[i].format    = va_desc.layers[i].drm_format;
        drm_desc->layers[i].nb_planes = va_desc.layers[i].अंक_planes;
        क्रम (j = 0; j < va_desc.layers[i].अंक_planes; j++) {
            drm_desc->layers[i].planes[j].object_सूचकांक =
                va_desc.layers[i].object_सूचकांक[j];
            drm_desc->layers[i].planes[j].offset =
                va_desc.layers[i].offset[j];
            drm_desc->layers[i].planes[j].pitch =
                va_desc.layers[i].pitch[j];
        }
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &vaapi_unmap_to_drm_esh, drm_desc);
    अगर (err < 0)
        जाओ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->तथ्य[0] = (uint8_t*)drm_desc;

    वापस 0;

fail:
    क्रम (i = 0; i < va_desc.अंक_objects; i++)
        बंद(va_desc.objects[i].fd);
    av_freep(&drm_desc);
    वापस err;
}
#पूर्ण_अगर

#अगर VA_CHECK_VERSION(0, 36, 0)
प्रकार काष्ठा VAAPIDRMImage_बफर_Mapping {
    VAImage      image;
    VABufferInfo बफर_info;

    AVDRMFrameDescriptor drm_desc;
} VAAPIDRMImage_बफर_Mapping;

अटल व्योम vaapi_unmap_to_drm_abh(AVHWFramesContext *hwfc,
                                  HWMapDescriptor *hwmap)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_बफर_Mapping *mapping = hwmap->priv;
    VASurfaceID surface_id;
    VAStatus vas;

    surface_id = (VASurfaceID)(uintptr_t)hwmap->source->तथ्य[3];
    av_log(hwfc, AV_LOG_DEBUG, "Unmap VAAPI surface %#x from DRM.\n",
           surface_id);

    // DRM PRIME file descriptors are closed by vaReleaseBufferHandle(),
    // so we shouldn't close them separately.

    vas = va_Release_बफर_Handle(hwctx->display, mapping->image.buf);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to release buffer "
               "handle of image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
    }

    vas = vaDestroyImage(hwctx->display, mapping->image.image_id);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to destroy image "
               "derived from surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
    }

    av_free(mapping);
}

अटल पूर्णांक vaapi_map_to_drm_abh(AVHWFramesContext *hwfc, AVFrame *dst,
                                स्थिर AVFrame *src, पूर्णांक flags)
{
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    VAAPIDRMImage_बफर_Mapping *mapping = शून्य;
    VASurfaceID surface_id;
    VAStatus vas;
    पूर्णांक err, i, p;

    surface_id = (VASurfaceID)(uintptr_t)src->तथ्य[3];
    av_log(hwfc, AV_LOG_DEBUG, "Map VAAPI surface %#x to DRM.\n",
           surface_id);

    mapping = av_mallocz(माप(*mapping));
    अगर (!mapping)
        वापस AVERROR(ENOMEM);

    vas = vaDeriveImage(hwctx->display, surface_id,
                        &mapping->image);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to derive image from "
               "surface %#x: %d (%s).\n",
               surface_id, vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जाओ fail;
    }

    क्रम (i = 0; i < FF_ARRAY_ELEMS(vaapi_drm_format_map); i++) {
        अगर (vaapi_drm_format_map[i].va_fourcc ==
            mapping->image.format.fourcc)
            अवरोध;
    }
    अगर (i >= FF_ARRAY_ELEMS(vaapi_drm_format_map)) {
        av_log(hwfc, AV_LOG_ERROR, "No matching DRM format for "
               "VAAPI format %#x.\n", mapping->image.format.fourcc);
        err = AVERROR(EINVAL);
        जाओ fail_derived;
    }

    mapping->बफर_info.mem_type =
        VA_SURFACE_ATTRIB_MEM_TYPE_DRM_अभाज्य;

    mapping->drm_desc.nb_layers =
        vaapi_drm_format_map[i].nb_layer_formats;
    अगर (mapping->drm_desc.nb_layers > 1) {
        अगर (mapping->drm_desc.nb_layers != mapping->image.अंक_planes) {
            av_log(hwfc, AV_LOG_ERROR, "Image properties do not match "
                   "expected format: got %d planes, but expected %d.\n",
                   mapping->image.अंक_planes, mapping->drm_desc.nb_layers);
            err = AVERROR(EINVAL);
            जाओ fail_derived;
        }

        क्रम(p = 0; p < mapping->drm_desc.nb_layers; p++) {
            mapping->drm_desc.layers[p] = (AVDRMLayerDescriptor) {
                .format    = vaapi_drm_format_map[i].layer_formats[p],
                .nb_planes = 1,
                .planes[0] = {
                    .object_सूचकांक = 0,
                    .offset       = mapping->image.offsets[p],
                    .pitch        = mapping->image.pitches[p],
                },
            };
        }
    } अन्यथा {
        mapping->drm_desc.layers[0].format =
            vaapi_drm_format_map[i].layer_formats[0];
        mapping->drm_desc.layers[0].nb_planes = mapping->image.अंक_planes;
        क्रम (p = 0; p < mapping->image.अंक_planes; p++) {
            mapping->drm_desc.layers[0].planes[p] = (AVDRMPlaneDescriptor) {
                .object_सूचकांक = 0,
                .offset       = mapping->image.offsets[p],
                .pitch        = mapping->image.pitches[p],
            };
        }
    }

    vas = va_Acquire_बफर_Handle(hwctx->display, mapping->image.buf,
                                &mapping->बफर_info);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to get buffer "
               "handle from image %#x (derived from surface %#x): "
               "%d (%s).\n", mapping->image.buf, surface_id,
               vas, vaErrorStr(vas));
        err = AVERROR(EIO);
        जाओ fail_derived;
    }

    av_log(hwfc, AV_LOG_DEBUG, "DRM PRIME fd is %"PRIdPTR".\n",
           mapping->बफर_info.handle);

    mapping->drm_desc.nb_objects = 1;
    mapping->drm_desc.objects[0] = (AVDRMObjectDescriptor) {
        .fd   = mapping->बफर_info.handle,
        .आकार = mapping->image.तथ्य_आकार,
        // There is no way to get the format modifier with this API.
        .format_modifier = DRM_FORMAT_MOD_INVALID,
    };

    err = ff_hwframe_map_create(src->hw_frames_ctx,
                                dst, src, &vaapi_unmap_to_drm_abh,
                                mapping);
    अगर (err < 0)
        जाओ fail_mapped;

    dst->तथ्य[0] = (uint8_t*)&mapping->drm_desc;
    dst->width   = src->width;
    dst->height  = src->height;

    वापस 0;

fail_mapped:
    va_Release_बफर_Handle(hwctx->display, mapping->image.buf);
fail_derived:
    vaDestroyImage(hwctx->display, mapping->image.image_id);
fail:
    av_freep(&mapping);
    वापस err;
}
#पूर्ण_अगर

अटल पूर्णांक vaapi_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                            स्थिर AVFrame *src, पूर्णांक flags)
{
#अगर VA_CHECK_VERSION(1, 1, 0)
    पूर्णांक err;
    err = vaapi_map_to_drm_esh(hwfc, dst, src, flags);
    अगर (err != AVERROR(ENOSYS))
        वापस err;
#पूर्ण_अगर
#अगर VA_CHECK_VERSION(0, 36, 0)
    वापस vaapi_map_to_drm_abh(hwfc, dst, src, flags);
#पूर्ण_अगर
    वापस AVERROR(ENOSYS);
}

#पूर्ण_अगर /* CONFIG_LIBDRM */

अटल पूर्णांक vaapi_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                        स्थिर AVFrame *src, पूर्णांक flags)
{
    चयन (src->format) {
#अगर CONFIG_LIBDRM
    हाल AV_PIX_FMT_DRM_अभाज्य:
        वापस vaapi_map_from_drm(hwfc, dst, src, flags);
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }
}

अटल पूर्णांक vaapi_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                          स्थिर AVFrame *src, पूर्णांक flags)
{
    चयन (dst->format) {
#अगर CONFIG_LIBDRM
    हाल AV_PIX_FMT_DRM_अभाज्य:
        वापस vaapi_map_to_drm(hwfc, dst, src, flags);
#पूर्ण_अगर
    शेष:
        वापस vaapi_map_to_memory(hwfc, dst, src, flags);
    }
}

अटल व्योम vaapi_device_free(AVHWDeviceContext *ctx)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    VAAPIDevicePriv      *priv  = ctx->user_opaque;

    अगर (hwctx->display)
        vaTerminate(hwctx->display);

#अगर HAVE_VAAPI_X11
    अगर (priv->x11_display)
        XCloseDisplay(priv->x11_display);
#पूर्ण_अगर

#अगर HAVE_VAAPI_DRM
    अगर (priv->drm_fd >= 0)
        बंद(priv->drm_fd);
#पूर्ण_अगर

    av_freep(&priv);
}

#अगर CONFIG_VAAPI_1
अटल व्योम vaapi_device_log_error(व्योम *context, स्थिर अक्षर *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_ERROR, "libva: %s", message);
}

अटल व्योम vaapi_device_log_info(व्योम *context, स्थिर अक्षर *message)
{
    AVHWDeviceContext *ctx = context;

    av_log(ctx, AV_LOG_VERBOSE, "libva: %s", message);
}
#पूर्ण_अगर

अटल पूर्णांक vaapi_device_connect(AVHWDeviceContext *ctx,
                                VADisplay display)
{
    AVVAAPIDeviceContext *hwctx = ctx->hwctx;
    पूर्णांक major, minor;
    VAStatus vas;

#अगर CONFIG_VAAPI_1
    vaSetErrorCallback(display, &vaapi_device_log_error, ctx);
    vaSetInfoCallback (display, &vaapi_device_log_info,  ctx);
#पूर्ण_अगर

    hwctx->display = display;

    vas = vaInitialize(display, &major, &minor);
    अगर (vas != VA_STATUS_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to initialise VAAPI "
               "connection: %d (%s).\n", vas, vaErrorStr(vas));
        वापस AVERROR(EIO);
    }
    av_log(ctx, AV_LOG_VERBOSE, "Initialised VAAPI connection: "
           "version %d.%d\n", major, minor);

    वापस 0;
}

अटल पूर्णांक vaapi_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                               AVDictionary *opts, पूर्णांक flags)
{
    VAAPIDevicePriv *priv;
    VADisplay display = शून्य;
    स्थिर AVDictionaryEntry *ent;
    पूर्णांक try_drm, try_x11, try_win32, try_all av_unused;

    priv = av_mallocz(माप(*priv));
    अगर (!priv)
        वापस AVERROR(ENOMEM);

    priv->drm_fd = -1;

    ctx->user_opaque = priv;
    ctx->मुक्त        = vaapi_device_free;

    ent = av_dict_get(opts, "connection_type", शून्य, 0);
    अगर (ent) {
        try_all = try_drm = try_x11 = try_win32 = 0;
        अगर (!म_भेद(ent->मूल्य, "drm")) {
            try_drm = 1;
        } अन्यथा अगर (!म_भेद(ent->मूल्य, "x11")) {
            try_x11 = 1;
        } अन्यथा अगर (!म_भेद(ent->मूल्य, "win32")) {
            try_win32 = 1;
        } अन्यथा {
            av_log(ctx, AV_LOG_ERROR, "Invalid connection type %s.\n",
                   ent->मूल्य);
            वापस AVERROR(EINVAL);
        }
    } अन्यथा {
        try_all = 1;
        try_drm = HAVE_VAAPI_DRM;
        try_x11 = HAVE_VAAPI_X11;
        try_win32 = HAVE_VAAPI_WIN32;
    }

#अगर HAVE_VAAPI_DRM
    जबतक (!display && try_drm) {
        // If the device is specified, try to open it as a DRM device node.
        // If not, look for a usable render node, possibly restricted to those
        // using a specified kernel driver.
        पूर्णांक loglevel = try_all ? AV_LOG_VERBOSE : AV_LOG_ERROR;
        अगर (device) {
            priv->drm_fd = खोलो(device, O_RDWR);
            अगर (priv->drm_fd < 0) {
                av_log(ctx, loglevel, "Failed to open %s as "
                       "DRM device node.\n", device);
                अवरोध;
            }
        } अन्यथा {
            अक्षर path[64];
            पूर्णांक n, max_devices = 8;
#अगर CONFIG_LIBDRM
            drmVersion *info;
            स्थिर AVDictionaryEntry *kernel_driver;
            स्थिर AVDictionaryEntry *vendor_id;
            kernel_driver = av_dict_get(opts, "kernel_driver", शून्य, 0);
            vendor_id = av_dict_get(opts, "vendor_id", शून्य, 0);
#पूर्ण_अगर
            क्रम (n = 0; n < max_devices; n++) {
                snprintf(path, माप(path),
                         "/dev/dri/renderD%d", 128 + n);
                priv->drm_fd = खोलो(path, O_RDWR);
                अगर (priv->drm_fd < 0) {
                    अगर (त्रुटि_सं == ENOENT) {
                        अगर (n != max_devices - 1) {
                            av_log(ctx, AV_LOG_VERBOSE,
                                   "No render device %s, try next device for "
                                   "DRM render node.\n", path);
                            जारी;
                        }

                        av_log(ctx, AV_LOG_VERBOSE, "No available render device "
                               "for DRM render node.\n");
                    } अन्यथा
                        av_log(ctx, AV_LOG_VERBOSE, "Cannot open "
                               "DRM render node for device %d.\n", n);
                    अवरोध;
                }
#अगर CONFIG_LIBDRM
                info = drmGetVersion(priv->drm_fd);
                अगर (!info) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Failed to get DRM version for device %d.\n", n);
                    बंद(priv->drm_fd);
                    priv->drm_fd = -1;
                    जारी;
                }
                अगर (kernel_driver) {
                    अगर (म_भेद(kernel_driver->मूल्य, info->name)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching kernel driver (%s).\n",
                               n, info->name);
                        drmFreeVersion(info);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        जारी;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching kernel driver (%s).\n",
                           n, info->name);
                    drmFreeVersion(info);
                    अवरोध;
                // drmGetVersion() ensures |info->name| is 0-terminated.
                } अन्यथा अगर (!म_भेद(info->name, "vgem")) {
                    av_log(ctx, AV_LOG_VERBOSE,
                           "Skipping vgem node for device %d.\n", n);
                    drmFreeVersion(info);
                    बंद(priv->drm_fd);
                    priv->drm_fd = -1;
                    जारी;
                } अन्यथा अगर (vendor_id) {
                    drmDevicePtr device;
                    अक्षर drm_vendor[8];
                    अगर (drmGetDevice(priv->drm_fd, &device)) {
                        av_log(ctx, AV_LOG_VERBOSE,
                               "Failed to get DRM device info for device %d.\n", n);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        जारी;
                    }

                    snprintf(drm_vendor, माप(drm_vendor), "0x%x", device->deviceinfo.pci->vendor_id);
                    अगर (म_भेद(vendor_id->मूल्य, drm_vendor)) {
                        av_log(ctx, AV_LOG_VERBOSE, "Ignoring device %d "
                               "with non-matching vendor id (%s).\n",
                               n, vendor_id->मूल्य);
                        drmFreeDevice(&device);
                        बंद(priv->drm_fd);
                        priv->drm_fd = -1;
                        drmFreeVersion(info);
                        जारी;
                    }
                    av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                           "DRM render node for device %d, "
                           "with matching vendor id (%s).\n",
                           n, vendor_id->मूल्य);
                    drmFreeDevice(&device);
                    drmFreeVersion(info);
                    अवरोध;
                }
                drmFreeVersion(info);
#पूर्ण_अगर
                av_log(ctx, AV_LOG_VERBOSE, "Trying to use "
                       "DRM render node for device %d.\n", n);
                अवरोध;
            }
            अगर (n >= max_devices)
                अवरोध;
        }

        display = vaGetDisplayDRM(priv->drm_fd);
        अगर (!display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open a VA display "
                   "from DRM device %s.\n", device);
            वापस AVERROR_EXTERNAL;
        }
        अवरोध;
    }
#पूर्ण_अगर

#अगर HAVE_VAAPI_X11
    अगर (!display && try_x11) {
        // Try to open the device as an X11 display.
        priv->x11_display = XOpenDisplay(device);
        अगर (!priv->x11_display) {
            av_log(ctx, AV_LOG_VERBOSE, "Cannot open X11 display "
                   "%s.\n", XDisplayName(device));
        } अन्यथा {
            display = vaGetDisplay(priv->x11_display);
            अगर (!display) {
                av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                       "from X11 display %s.\n", XDisplayName(device));
                वापस AVERROR_UNKNOWN;
            }

            av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                   "X11 display %s.\n", XDisplayName(device));
        }
    }
#पूर्ण_अगर

#अगर HAVE_VAAPI_WIN32
    अगर (!display && try_win32) {
        // Try to create a display from the specified device, if any.
        अगर (!device) {
            display = vaGetDisplayWin32(शून्य);
        } अन्यथा {
            IDXGIFactory2 *pDXGIFactory = शून्य;
            IDXGIAdapter *pAdapter = शून्य;
#अगर !HAVE_UWP
            HANDLE dxgi = dlopen("dxgi.dll", 0);
            अगर (!dxgi) {
                av_log(ctx, AV_LOG_ERROR, "Failed to load dxgi.dll\n");
                वापस AVERROR_UNKNOWN;
            }
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)dlsym(dxgi, "CreateDXGIFactory");
            अगर (!pfnCreateDXGIFactory) {
                av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory load failed\n");
                dlclose(dxgi);
                वापस AVERROR_UNKNOWN;
            }
#अन्यथा
            // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't
            // available, only CreateDXGIFactory1
            PFN_CREATE_DXGI_FACTORY pfnCreateDXGIFactory =
                (PFN_CREATE_DXGI_FACTORY)CreateDXGIFactory1;
#पूर्ण_अगर
            अगर (SUCCEEDED(pfnCreateDXGIFactory(&IID_IDXGIFactory2,
                                              (व्योम **)&pDXGIFactory))) {
                पूर्णांक adapter = म_से_प(device);
                अगर (SUCCEEDED(IDXGIFactory2_EnumAdapters(pDXGIFactory,
                                                         adapter,
                                                         &pAdapter))) {
                    DXGI_ADAPTER_DESC desc;
                    अगर (SUCCEEDED(IDXGIAdapter2_GetDesc(pAdapter, &desc))) {
                        av_log(ctx, AV_LOG_INFO,
                              "Using device %04x:%04x (%ls) - LUID %lu %ld.\n",
                              desc.VendorId, desc.DeviceId, desc.Description,
                              desc.AdapterLuid.निचला_Part,
                              desc.AdapterLuid.ऊपरी_Part);
                        display = vaGetDisplayWin32(&desc.AdapterLuid);
                    }
                    IDXGIAdapter_Release(pAdapter);
                }
                IDXGIFactory2_Release(pDXGIFactory);
            }
#अगर !HAVE_UWP
            dlclose(dxgi);
#पूर्ण_अगर
        }

        अगर (!display) {
            av_log(ctx, AV_LOG_ERROR, "Cannot open a VA display "
                    "from Win32 display.\n");
            वापस AVERROR_UNKNOWN;
        }

        av_log(ctx, AV_LOG_VERBOSE, "Opened VA display via "
                "Win32 display.\n");
    }
#पूर्ण_अगर

    अगर (!display) {
        अगर (device)
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "device %s.\n", device);
        अन्यथा
            av_log(ctx, AV_LOG_ERROR, "No VA display found for "
                   "any default device.\n");
        वापस AVERROR(EINVAL);
    }

    ent = av_dict_get(opts, "driver", शून्य, 0);
    अगर (ent) {
#अगर VA_CHECK_VERSION(0, 38, 0)
        VAStatus vas;
        vas = vaSetDriverName(display, ent->मूल्य);
        अगर (vas != VA_STATUS_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Failed to set driver name to "
                   "%s: %d (%s).\n", ent->मूल्य, vas, vaErrorStr(vas));
            vaTerminate(display);
            वापस AVERROR_EXTERNAL;
        }
#अन्यथा
        av_log(ctx, AV_LOG_WARNING, "Driver name setting is not "
               "supported with this VAAPI version.\n");
#पूर्ण_अगर
    }

    वापस vaapi_device_connect(ctx, display);
}

अटल पूर्णांक vaapi_device_derive(AVHWDeviceContext *ctx,
                               AVHWDeviceContext *src_ctx,
                               AVDictionary *opts, पूर्णांक flags)
{
#अगर HAVE_VAAPI_DRM
    अगर (src_ctx->type == AV_HWDEVICE_TYPE_DRM) {
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay *display;
        VAAPIDevicePriv *priv;
        पूर्णांक fd;

        अगर (src_hwctx->fd < 0) {
            av_log(ctx, AV_LOG_ERROR, "DRM instance requires an associated "
                   "device to derive a VA display from.\n");
            वापस AVERROR(EINVAL);
        }

#अगर CONFIG_LIBDRM
        {
            पूर्णांक गाँठ_type = drm_Get_गाँठ_Type_From_Fd(src_hwctx->fd);
            अक्षर *render_गाँठ;
            अगर (गाँठ_type < 0) {
                av_log(ctx, AV_LOG_ERROR, "DRM instance fd does not appear "
                       "to refer to a DRM device.\n");
                वापस AVERROR(EINVAL);
            }
            अगर (गाँठ_type == DRM_गाँठ_RENDER) {
                fd = src_hwctx->fd;
            } अन्यथा {
                render_गाँठ = drmGetRenderDeviceNameFromFd(src_hwctx->fd);
                अगर (!render_गाँठ) {
                    av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                           "because the device does not have an "
                           "associated render node.\n");
                    fd = src_hwctx->fd;
                } अन्यथा {
                    fd = खोलो(render_गाँठ, O_RDWR);
                    अगर (fd < 0) {
                        av_log(ctx, AV_LOG_VERBOSE, "Using non-render node "
                               "because the associated render node "
                               "could not be opened.\n");
                        fd = src_hwctx->fd;
                    } अन्यथा {
                        av_log(ctx, AV_LOG_VERBOSE, "Using render node %s "
                               "in place of non-render DRM device.\n",
                               render_गाँठ);
                    }
                    मुक्त(render_गाँठ);
                }
            }
        }
#अन्यथा
        fd = src_hwctx->fd;
#पूर्ण_अगर

        priv = av_mallocz(माप(*priv));
        अगर (!priv) {
            अगर (fd != src_hwctx->fd) {
                // The fd was opened in this function.
                बंद(fd);
            }
            वापस AVERROR(ENOMEM);
        }

        अगर (fd == src_hwctx->fd) {
            // The fd is inherited from the source context and we are holding
            // a reference to that, we don't want to close it from here.
            priv->drm_fd = -1;
        } अन्यथा {
            priv->drm_fd = fd;
        }

        ctx->user_opaque = priv;
        ctx->मुक्त        = &vaapi_device_free;

        display = vaGetDisplayDRM(fd);
        अगर (!display) {
            av_log(ctx, AV_LOG_ERROR, "Failed to open a VA display from "
                   "DRM device.\n");
            वापस AVERROR(EIO);
        }

        वापस vaapi_device_connect(ctx, display);
    }
#पूर्ण_अगर
    वापस AVERROR(ENOSYS);
}

स्थिर HWContextType ff_hwcontext_type_vaapi = {
    .type                   = AV_HWDEVICE_TYPE_VAAPI,
    .name                   = "VAAPI",

    .device_hwctx_आकार      = माप(VAAPIDeviceContext),
    .device_hwconfig_आकार   = माप(AVVAAPIHWConfig),
    .frames_hwctx_आकार      = माप(VAAPIFramesContext),

    .device_create          = &vaapi_device_create,
    .device_derive          = &vaapi_device_derive,
    .device_init            = &vaapi_device_init,
    .device_uninit          = &vaapi_device_uninit,
    .frames_get_constraints = &vaapi_frames_get_constraints,
    .frames_init            = &vaapi_frames_init,
    .frames_uninit          = &vaapi_frames_uninit,
    .frames_get_बफर      = &vaapi_get_बफर,
    .transfer_get_formats   = &vaapi_transfer_get_formats,
    .transfer_तथ्य_to       = &vaapi_transfer_तथ्य_to,
    .transfer_तथ्य_from     = &vaapi_transfer_तथ्य_from,
    .map_to                 = &vaapi_map_to,
    .map_from               = &vaapi_map_from,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]) {
        AV_PIX_FMT_VAAPI,
        AV_PIX_FMT_NONE
    },
};
