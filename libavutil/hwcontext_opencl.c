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

#تعریف_کرو CL_USE_DEPRECATED_OPENCL_1_2_APIS

#ضمن <string.h>

#ضمن "config.h"

#ضمن "avassert.h"
#ضمن "avstring.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_opencl.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"

#إذا HAVE_OPENCL_VAAPI_BEIGNET
#ضمن <unistd.h>
#ضمن <va/va.h>
#ضمن <va/va_drmcommon.h>
#ضمن <CL/cl_intel.h>
#ضمن "hwcontext_vaapi.h"
#جے_انت

#إذا HAVE_OPENCL_DRM_BEIGNET
#ضمن <unistd.h>
#ضمن <CL/cl_intel.h>
#ضمن "hwcontext_drm.h"
#جے_انت

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
#إذا CONFIG_LIBMFX
#ضمن <mfxstructures.h>
#جے_انت
#ضمن <va/va.h>
#ضمن <CL/cl_va_api_media_sharing_intel.h>
#ضمن "hwcontext_vaapi.h"
#جے_انت

#إذا HAVE_OPENCL_DXVA2
#تعریف_کرو COBJMACROS
#ضمن <CL/cl_dx9_media_sharing.h>
#ضمن <dxva2api.h>
#ضمن "hwcontext_dxva2.h"
#جے_انت

#إذا HAVE_OPENCL_D3D11
#ضمن <CL/cl_d3d11.h>
#ضمن "hwcontext_d3d11va.h"
#جے_انت

#إذا HAVE_OPENCL_DRM_ARM
#ضمن <CL/cl_ext.h>
#ضمن <drm_fourcc.h>
#ضمن "hwcontext_drm.h"
#جے_انت

#إذا HAVE_OPENCL_VIDEOTOOLBOX
#ضمن <OpenCL/cl_gl_ext.h>
#ضمن <VideoToolbox/VideoToolbox.h>
#جے_انت

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
خارجي صحيح ff_qsv_get_surface_ادھار_handle(mfx_چوکھٹا_Surface1 *surf,
                                          تعداد AVHWDeviceType ادھار_dev_typ,
                                          فراغ **ادھار_handle);
#جے_انت


تعريفنوع بنية OpenCLDeviceContext {
    /**
     * The public AVOpenCLDeviceContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLDeviceContext p;

    // Default command queue to use for transfer/mapping operations on
    // the device.  If the user supplies one, this is a reference to it.
    // Otherwise, it is newly-created.
    cl_command_قطار command_قطار;

    // The platform the context exists on.  This is needed to query and
    // retrieve extension functions.
    cl_platform_id platform_id;

    // Platform/device-specific functions.
#إذا HAVE_OPENCL_DRM_BEIGNET
    صحيح beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#جے_انت

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    صحيح qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_قطار_وچ_پاؤ_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_قطار_وچ_پاؤ_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_قطار_وچ_پاؤ_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_قطار_وچ_پاؤ_Release_VA_APIMedia_Surfaces_INTEL;
#جے_انت

#إذا HAVE_OPENCL_DXVA2
    صحيح dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_قطار_وچ_پاؤ_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_قطار_وچ_پاؤ_Acquire_DX9_Media_Surfaces_KHR;
    cl_قطار_وچ_پاؤ_Release_DX9_Media_Surfaces_KHR_fn
        cl_قطار_وچ_پاؤ_Release_DX9_Media_Surfaces_KHR;
#جے_انت

#إذا HAVE_OPENCL_D3D11
    صحيح d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_قطار_وچ_پاؤ_Acquire_D3_D11_Objects_KHR_fn
        cl_قطار_وچ_پاؤ_Acquire_D3_D11_Objects_KHR;
    cl_قطار_وچ_پاؤ_Release_D3_D11_Objects_KHR_fn
        cl_قطار_وچ_پاؤ_Release_D3_D11_Objects_KHR;
#جے_انت

#إذا HAVE_OPENCL_DRM_ARM
    صحيح drm_arm_mapping_usable;
#جے_انت
} OpenCLDeviceContext;

تعريفنوع بنية OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_قطار command_قطار;

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    صحيح                   nb_mapped_چوکھٹے;
    AVOpenCLFrameDescriptor *mapped_چوکھٹے;
#جے_انت
} OpenCLFramesContext;


ساكن فراغ CL_CALLBACK opencl_error_callback(ثابت حرف *errinfo,
                                              ثابت فراغ *نجی_info,
                                              size_t cb,
                                              فراغ *user_انکڑے)
{
    AVHWDeviceContext *ctx = user_انکڑے;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ساكن فراغ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ساكن بنية {
    ثابت حرف *کلید;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_نسخہ    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ساكن بنية {
    ثابت حرف *کلید;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_نسخہ      },
    { "device_version",      CL_DEVICE_نسخہ      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ساكن بنية {
    ثابت حرف *کلید;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ساكن حرف *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info کلید)
{
    حرف *str;
    size_t ناپ;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, کلید, 0, عدم, &ناپ);
    إذا (cle != CL_SUCCESS)
        أرجع عدم;
    str = av_malloc(ناپ);
    إذا (!str)
        أرجع عدم;
    cle = clGetPlatformInfo(platform_id, کلید, ناپ, str, &ناپ);
    إذا (cle != CL_SUCCESS) {
        av_free(str);
        أرجع عدم;
    }
    av_assert0(لڑی_لمبائی(str) + 1 == ناپ);
    أرجع str;
}

ساكن حرف *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info کلید)
{
    حرف *str;
    size_t ناپ;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, کلید, 0, عدم, &ناپ);
    إذا (cle != CL_SUCCESS)
        أرجع عدم;
    str = av_malloc(ناپ);
    إذا (!str)
        أرجع عدم;
    cle = clGetDeviceInfo(device_id, کلید, ناپ, str, &ناپ);
    إذا (cle != CL_SUCCESS) {
        av_free(str);
        أرجع عدم;
    }
    av_assert0(لڑی_لمبائی(str) + 1== ناپ);
    أرجع str;
}

ساكن صحيح opencl_check_platform_extension(cl_platform_id platform_id,
                                           ثابت حرف *name)
{
    حرف *str;
    صحيح لبھیا = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    إذا (str && لڑی_کھوج(str, name))
        لبھیا = 1;
    av_free(str);
    أرجع لبھیا;
}

ساكن صحيح opencl_check_device_extension(cl_device_id device_id,
                                         ثابت حرف *name)
{
    حرف *str;
    صحيح لبھیا = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    إذا (str && لڑی_کھوج(str, name))
        لبھیا = 1;
    av_free(str);
    أرجع لبھیا;
}

av_بن_ورتیا ساكن صحيح opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ثابت حرف *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    إذا (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        أرجع 1;
    }

    إذا (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        أرجع 1;
    }

    أرجع 0;
}

ساكن صحيح opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      فراغ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, عدم, nb_platforms);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        أرجع AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, حجم(**platforms));
    إذا (!*platforms)
        أرجع AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        أرجع AVERROR(ENODEV);
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ثابت حرف *platform_name,
                                  فراغ *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionary_اندراج *param;
    حرف *str;
    صحيح i, ret = 0;

    لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].کلید,
                            عدم, 0);
        إذا (!param)
            استمر;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        إذا (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].کلید, platform_name);
            أرجع AVERROR_UNKNOWN;
        }
        إذا (!av_stristr(str, param->قدر)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    أرجع ret;
}

ساكن صحيح opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ثابت حرف *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    فراغ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_لبھیا) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR(ENODEV);
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ثابت حرف *device_name,
                                فراغ *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionary_اندراج *param;
    حرف *str;
    صحيح i, ret = 0;

    param = av_dict_get(opts, "device_type", عدم, 0);
    إذا (param) {
        cl_device_type میل_type = 0, device_type;
        cl_int cle;

        لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            إذا (!strcmp(opencl_device_types[i].کلید, param->قدر)) {
                میل_type = opencl_device_types[i].type;
                اكسر;
            }
        }
        إذا (!میل_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->قدر);
            أرجع AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              حجم(device_type), &device_type, عدم);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            أرجع AVERROR_UNKNOWN;
        }

        إذا (!(device_type & میل_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            أرجع 1;
        }
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].کلید,
                            عدم, 0);
        إذا (!param)
            استمر;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        إذا (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].کلید, device_name);
            أرجع AVERROR_UNKNOWN;
        }
        إذا (!av_stristr(str, param->قدر)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    أرجع ret;
}

تعريفنوع بنية OpenCLDeviceSelector {
    صحيح platform_اشاریہ;
    صحيح device_اشاریہ;
    فراغ *context;
    صحيح (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               فراغ *context);
    صحيح (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               فراغ *context);
    صحيح (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               فراغ *context);
    صحيح (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ثابت حرف *device_name,
                               فراغ *context);
} OpenCLDeviceSelector;

ساكن صحيح opencl_device_create_اندرونی(AVHWDeviceContext *hwdev,
                                         ثابت OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = عدم;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = عدم;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    حرف *platform_name_src = عدم,
         *device_name_src   = عدم;
    صحيح err, لبھیا, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    إذا (err)
        أرجع err;

    لبھیا = 0;
    لكل (p = 0; p < nb_platforms; p++) {
        ثابت حرف *platform_name;

        إذا (selector->platform_اشاریہ >= 0 &&
            selector->platform_اشاریہ != p)
            استمر;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        إذا (platform_name_src)
            platform_name = platform_name_src;
        وإلا
            platform_name = "Unknown Platform";

        إذا (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            إذا (err < 0)
                اذهب fail;
            إذا (err > 0)
                استمر;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        إذا (err < 0)
            استمر;

        لكل (d = 0; d < nb_devices; d++) {
            ثابت حرف *device_name;

            إذا (selector->device_اشاریہ >= 0 &&
                selector->device_اشاریہ != d)
                استمر;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            إذا (device_name_src)
                device_name = device_name_src;
            وإلا
                device_name = "Unknown Device";

            إذا (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                إذا (err < 0)
                    اذهب fail;
                إذا (err > 0)
                    استمر;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++لبھیا;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    إذا (لبھیا == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        اذهب fail;
    }
    إذا (لبھیا > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        اذهب fail;
    }

    إذا (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } وإلا {
        إذا (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    إذا (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        اذهب fail;
    }

    hwdev->حرر = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    أرجع err;
}

ساكن صحيح opencl_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                                AVDictionary *opts, صحيح flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    إذا (device && device[0]) {
        // Match one or both indices for platform and device.
        صحيح d = -1, p = -1, ret;
        إذا (device[0] == '.')
            ret = لڑی_توں_پڑھو(device, ".%d", &d);
        وإلا
            ret = لڑی_توں_پڑھو(device, "%d.%d", &p, &d);
        إذا (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            أرجع AVERROR(EINVAL);
        }
        selector.platform_اشاریہ = p;
        selector.device_اشاریہ   = d;
    } وإلا {
        selector.platform_اشاریہ = -1;
        selector.device_اشاریہ   = -1;
    }

    أرجع opencl_device_create_اندرونی(hwdev, &selector, عدم);
}

ساكن صحيح opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    إذا (hwctx->command_قطار) {
        cle = cl_Retain_Command_قطار(hwctx->command_قطار);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            أرجع AVERROR(EIO);
        }
        priv->command_قطار = hwctx->command_قطار;
    } وإلا {
        priv->command_قطار = cl_Create_Command_قطار(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        إذا (!priv->command_قطار) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            أرجع AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          حجم(priv->platform_id), &priv->platform_id,
                          عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        أرجع AVERROR(EIO);
    }

#تعریف_کرو CL_FUNC(name, desc) افعل {                                \
        إذا (fail)                                               \
            اكسر;                                              \
        priv->name = cl_Get_Extension_Function_پتہ_For_Platform(  \
            priv->platform_id, #name);                          \
        إذا (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } وإلا {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } طالما (0)

#إذا HAVE_OPENCL_DRM_BEIGNET
    {
        صحيح fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } وإلا {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#جے_انت

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_ناپ;
        cl_context_properties *props = عدم;
        VADisplay va_display;
        ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";
        صحيح i, fail = 0;

        إذا (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            اذهب no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, عدم, &props_ناپ);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            اذهب no_qsv;
        }
        إذا (props_ناپ == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }

        props = av_malloc(props_ناپ);
        إذا (!props)
            أرجع AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_ناپ, props, عدم);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            اذهب no_qsv;
        }

        va_display = عدم;
        لكل (i = 0; i < (props_ناپ / حجم(*props) - 1); i++) {
            إذا (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                اكسر;
            }
        }
        إذا (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }
        إذا (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_قطار_وچ_پاؤ_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_قطار_وچ_پاؤ_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        إذا (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } وإلا {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#جے_انت

#إذا HAVE_OPENCL_DXVA2
    {
        صحيح fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_قطار_وچ_پاؤ_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_قطار_وچ_پاؤ_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } وإلا {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#جے_انت

#إذا HAVE_OPENCL_D3D11
    {
        ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";
        ثابت حرف *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        صحيح fail = 0;

        إذا (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } وإلا إذا (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_قطار_وچ_پاؤ_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_قطار_وچ_پاؤ_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } وإلا {
            priv->d3d11_mapping_usable = 1;
        }
    }
#جے_انت

#إذا HAVE_OPENCL_DRM_ARM
    {
        ثابت حرف *drm_arm_ext = "cl_arm_import_memory";
        ثابت حرف *image_ext   = "cl_khr_image2d_from_buffer";
        صحيح fail = 0;

        إذا (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        إذا (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } وإلا {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#جے_انت

#تعریف_رد CL_FUNC

    أرجع 0;
}

ساكن فراغ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    إذا (priv->command_قطار) {
        cle = cl_Release_Command_قطار(priv->command_قطار);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_قطار = عدم;
    }
}

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
ساكن صحيح opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ثابت حرف *platform_name,
                                                    فراغ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    إذا (!cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        أرجع 1;
    } وإلا {
        أرجع 0;
    }
}

ساكن صحيح opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ثابت حرف *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      فراغ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    إذا (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_لبھیا) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ثابت حرف *device_name,
                                                  فراغ *context)
{
    ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";

    إذا (opencl_check_device_extension(device_id, va_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        أرجع 1;
    }
}
#جے_انت

#إذا HAVE_OPENCL_DXVA2
ساكن صحيح opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        فراغ *context)
{
    ثابت حرف *dx9_ext = "cl_khr_dx9_media_sharing";

    إذا (opencl_check_platform_extension(platform_id, dx9_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          فراغ *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    إذا (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (فراغ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_لبھیا) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (فراغ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}
#جے_انت

#إذا HAVE_OPENCL_D3D11
ساكن صحيح opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        فراغ *context)
{
    ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";

    إذا (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          فراغ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    إذا (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_لبھیا) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}
#جے_انت

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ساكن صحيح opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ثابت حرف *device_name,
                                    فراغ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          حجم(device_type), &device_type, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        أرجع AVERROR_UNKNOWN;
    }
    إذا (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        أرجع 1;
    }

    أرجع 0;
}
#جے_انت

#إذا HAVE_OPENCL_DRM_ARM
ساكن صحيح opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          فراغ *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    إذا (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ثابت حرف *device_name,
                                        فراغ *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    إذا (opencl_check_device_extension(device_id, drm_arm_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        أرجع 1;
    }
}
#جے_انت

ساكن صحيح opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                صحيح flags)
{
    صحيح err;
    بدل (src_ctx->type) {

#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_HWDEVICE_TYPE_DRM:
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = عدم;

            err = av_dict_سیٹ(&selector_opts, "platform_vendor", "Intel", 0);
            إذا (err >= 0)
                err = av_dict_سیٹ(&selector_opts, "platform_version", "beignet", 0);
            إذا (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_اشاریہ      = -1,
                    .device_اشاریہ        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = عدم,
                };
                err = opencl_device_create_اندرونی(hwdev, &selector, عدم);
            }
            av_dict_free(&selector_opts);
        }
        اكسر;
#جے_انت

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
            cl_context_properties props[7] = {
                CL_CONTEXT_PLATFORM,
                0,
                CL_CONTEXT_VA_API_DISPLAY_INTEL,
                (intptr_t)src_hwctx->display,
                CL_CONTEXT_INTEROP_USER_SYNC,
                CL_FALSE,
                0,
            };
            OpenCLDeviceSelector selector = {
                .platform_اشاریہ      = -1,
                .device_اشاریہ        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_اندرونی(hwdev, &selector, props);
        }
        اكسر;
#جے_انت

#إذا HAVE_OPENCL_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            إذا (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (بنانشانی لما)hr);
                err = AVERROR_UNKNOWN;
                اكسر;
            }

            hr = IDirect3_DDevice_Manager9_جندرا_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            إذا (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_اشاریہ      = -1,
                    .device_اشاریہ        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_اندرونی(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } وإلا {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (بنانشانی لما)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        اكسر;
#جے_انت

#إذا HAVE_OPENCL_D3D11
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *src_hwctx = src_ctx->hwctx;
            cl_context_properties props[5] = {
                CL_CONTEXT_PLATFORM,
                0,
                CL_CONTEXT_D3D11_DEVICE_KHR,
                (intptr_t)src_hwctx->device,
                0,
            };
            OpenCLDeviceSelector selector = {
                .platform_اشاریہ      = -1,
                .device_اشاریہ        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_اندرونی(hwdev, &selector, props);
        }
        اكسر;
#جے_انت

#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_اشاریہ      = -1,
                .device_اشاریہ        = -1,
                .context             = عدم,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_اندرونی(hwdev, &selector, عدم);
        }
        اكسر;
#جے_انت

#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, عدم, عدم, 0);
        اكسر;
#جے_انت

    افتراضي:
        err = AVERROR(ENOSYS);
        اكسر;
    }

    أرجع err;
}

ساكن صحيح opencl_get_plane_format(تعداد AVPixelFormat pixfmt,
                                   صحيح plane, صحيح چوڑائی, صحيح اچائی,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ثابت AVPixFmtDescriptor *desc;
    ثابت AVComponentDescriptor *comp;
    صحيح channels = 0, ترتیب = 0, ڈونگھائی = 0, قدم = 0;
    صحيح wsub, hsub, alpha;
    صحيح c;

    إذا (plane >= AV_عدد_انکڑے_سوچکاں)
        أرجع AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        أرجع AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    إذا (چوڑائی & wsub - 1 || اچائی & hsub - 1)
        أرجع AVERROR(EINVAL);

    لكل (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        إذا (comp->plane != plane)
            استمر;
        // The step size must be a power of two.
        إذا (comp->قدم != 1 && comp->قدم != 2 &&
            comp->قدم != 4 && comp->قدم != 8)
            أرجع AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        إذا (comp->کھسکاؤ + comp->ڈونگھائی != 8 &&
            comp->کھسکاؤ + comp->ڈونگھائی != 16 &&
            comp->کھسکاؤ + comp->ڈونگھائی != 32)
            أرجع AVERROR(EINVAL);
        // The depth must not vary between components.
        إذا (ڈونگھائی && comp->ڈونگھائی != ڈونگھائی)
            أرجع AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        إذا (comp->ڈونگھائی > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            أرجع AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        إذا (قدم && comp->قدم != قدم)
            أرجع AVERROR(EINVAL);

        ڈونگھائی = comp->ڈونگھائی;
        ترتیب = ترتیب * 10 + comp->وتھ / ((ڈونگھائی + 7) / 8) + 1;
        قدم  = comp->قدم;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    إذا (channels == 0)
        أرجع AVERROR(ENOENT);

    memset(image_format, 0, حجم(*image_format));
    memset(image_desc,   0, حجم(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    إذا (plane == 0 || alpha) {
        image_desc->image_چوڑائی     = چوڑائی;
        image_desc->image_اچائی    = اچائی;
        image_desc->image_صف_pitch = قدم * چوڑائی;
    } وإلا {
        image_desc->image_چوڑائی     = چوڑائی  / wsub;
        image_desc->image_اچائی    = اچائی / hsub;
        image_desc->image_صف_pitch = قدم * چوڑائی / wsub;
    }

    إذا (ڈونگھائی <= 8) {
        image_format->image_channel_انکڑے_type = CL_UNORM_INT8;
    } وإلا {
        إذا (ڈونگھائی <= 16)
            image_format->image_channel_انکڑے_type = CL_UNORM_INT16;
        وإلا إذا (ڈونگھائی == 32)
            image_format->image_channel_انکڑے_type = CL_FLOAT;
        وإلا
            أرجع AVERROR(EINVAL);
    }

#تعریف_کرو CHANNEL_ترتیب(ترتیب, type) \
    حالة ترتیب: image_format->image_channel_ترتیب = type; اكسر;
    بدل (ترتیب) {
        CHANNEL_ترتیب(1,    CL_R);
        CHANNEL_ترتیب(12,   CL_RG);
        CHANNEL_ترتیب(1234, CL_RGBA);
        CHANNEL_ترتیب(2341, CL_ARGB);
        CHANNEL_ترتیب(3214, CL_BGRA);
#جے_تعریف_شدہ CL_ABGR
        CHANNEL_ترتیب(4321, CL_ABGR);
#جے_انت
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
#تعریف_رد CHANNEL_ترتیب

    أرجع 0;
}

ساكن صحيح opencl_چوکھٹے_get_constraints(AVHWDeviceContext *hwdev,
                                         ثابت فراغ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = عدم;
    cl_int cle;
    تعداد AVPixelFormat pix_fmt;
    صحيح err, pix_fmts_لبھیا;
    size_t max_چوڑائی, max_اچائی;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_چوڑائی,
                          حجم(max_چوڑائی), &max_چوڑائی, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } وإلا {
        constraints->max_چوڑائی = max_چوڑائی;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_اچائی,
                          حجم(max_اچائی), &max_اچائی, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } وإلا {
        constraints->max_اچائی = max_اچائی;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_چوڑائی, constraints->max_اچائی);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, عدم, &nb_image_formats);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        اذهب fail;
    }
    إذا (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        اذهب fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, حجم(*image_formats));
    إذا (!image_formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        اذهب fail;
    }

    pix_fmts_لبھیا = 0;
    لكل (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        صحيح plane, i;

        لكل (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            إذا (err < 0)
                اكسر;

            لكل (i = 0; i < nb_image_formats; i++) {
                إذا (image_formats[i].image_channel_ترتیب ==
                    image_format.image_channel_ترتیب &&
                    image_formats[i].image_channel_انکڑے_type ==
                    image_format.image_channel_انکڑے_type)
                    اكسر;
            }
            إذا (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                اكسر;
            }
        }
        إذا (err != AVERROR(ENOENT))
            استمر;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_لبھیا + 2,
                                حجم(*constraints->valid_sw_formats));
        إذا (err < 0)
            اذهب fail;
        constraints->valid_sw_formats[pix_fmts_لبھیا] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_لبھیا + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_لبھیا;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;

fail:
    av_freep(&image_formats);
    أرجع err;
}

ساكن فراغ opencl_pool_free(فراغ *opaque, uint8_t *انکڑے)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)انکڑے;
    cl_int cle;
    صحيح p;

    لكل (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ساكن AVBufferRef *opencl_pool_alloc(فراغ *opaque, size_t ناپ)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    صحيح err, p;
    AVBufferRef *ref;

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع عدم;

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->چوڑائی, hwfc->اچائی,
                                      &image_format, &image_desc);
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_صف_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, عدم, &cle);
        إذا (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            اذهب fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_بفر_create((uint8_t*)desc, حجم(*desc),
                           &opencl_pool_free, hwfc, 0);
    إذا (!ref)
        اذهب fail;

    أرجع ref;

fail:
    لكل (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    أرجع عدم;
}

ساكن صحيح opencl_چوکھٹے_init_command_قطار(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_قطار = hwctx->command_قطار ? hwctx->command_قطار
                                               : devpriv->command_قطار;
    cle = cl_Retain_Command_قطار(priv->command_قطار);
    إذا (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    أرجع 0;
}

ساكن صحيح opencl_چوکھٹے_init(AVHWFramesContext *hwfc)
{
    إذا (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_اندرونی =
            av_بفر_pool_init2(حجم(cl_mem), hwfc,
                                 &opencl_pool_alloc, عدم);
        إذا (!ffhwframesctx(hwfc)->pool_اندرونی)
            أرجع AVERROR(ENOMEM);
    }

    أرجع opencl_چوکھٹے_init_command_قطار(hwfc);
}

ساكن فراغ opencl_چوکھٹے_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    صحيح i, p;
    لكل (i = 0; i < priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_چوکھٹے[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            إذا (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_چوکھٹے);
#جے_انت

    إذا (priv->command_قطار) {
        cle = cl_Release_Command_قطار(priv->command_قطار);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_قطار = عدم;
    }
}

ساكن صحيح opencl_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکھٹا)
{
    AVOpenCLFrameDescriptor *desc;
    صحيح p;

    چوکھٹا->buf[0] = av_بفر_pool_get(hwfc->pool);
    إذا (!چوکھٹا->buf[0])
        أرجع AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)چوکھٹا->buf[0]->انکڑے;

    لكل (p = 0; p < desc->nb_planes; p++)
        چوکھٹا->انکڑے[p] = (uint8_t*)desc->planes[p];

    چوکھٹا->format  = AV_PIX_FMT_OPENCL;
    چوکھٹا->چوڑائی   = hwfc->چوڑائی;
    چوکھٹا->اچائی  = hwfc->اچائی;

    أرجع 0;
}

ساكن صحيح opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       تعداد AVHWFrameTransferDirection dir,
                                       تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    أرجع 0;
}

ساكن صحيح opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, صحيح nb_events)
{
    cl_int cle;
    صحيح i;

    cle = clWaitForEvents(nb_events, events);
    إذا (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    لكل (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    أرجع 0;
}

ساكن صحيح opencl_transfer_انکڑے_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_عدد_انکڑے_سوچکاں];
    صحيح err, p;

    إذا (dst->format != hwfc->sw_format)
        أرجع AVERROR(EINVAL);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اچائی,
                                      &image_format, &image_desc);
        إذا (err < 0) {
            إذا (err == AVERROR(ENOENT))
                err = 0;
            اكسر;
        }

        إذا (!dst->انکڑے[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            اكسر;
        }

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اچائی;
        region[2] = 1;

        cle = cl_قطار_وچ_پاؤ_Read_Image(priv->command_قطار,
                                 (cl_mem)src->انکڑے[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->انکڑے[p],
                                 0, عدم, &events[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اكسر;
        }
    }

    opencl_wait_events(hwfc, events, p);

    أرجع err;
}

ساكن صحيح opencl_transfer_انکڑے_منزل(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_عدد_انکڑے_سوچکاں];
    صحيح err, p;

    إذا (src->format != hwfc->sw_format)
        أرجع AVERROR(EINVAL);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اچائی,
                                      &image_format, &image_desc);
        إذا (err < 0) {
            إذا (err == AVERROR(ENOENT))
                err = 0;
            اكسر;
        }

        إذا (!src->انکڑے[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            اكسر;
        }

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اچائی;
        region[2] = 1;

        cle = cl_قطار_وچ_پاؤ_Write_Image(priv->command_قطار,
                                  (cl_mem)dst->انکڑے[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->انکڑے[p],
                                  0, عدم, &events[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اكسر;
        }
    }

    opencl_wait_events(hwfc, events, p);

    أرجع err;
}

تعريفنوع بنية OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    فراغ *پتہ[AV_عدد_انکڑے_سوچکاں];
} OpenCLMapping;

ساكن فراغ opencl_unmap_چوکھٹا(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_عدد_انکڑے_سوچکاں];
    صحيح p, e;
    cl_int cle;

    لكل (p = e = 0; p < FF_ARRAY_ELEMS(map->پتہ); p++) {
        إذا (!map->پتہ[p])
            اكسر;

        cle = cl_قطار_وچ_پاؤ_Unmap_Mem_Object(priv->command_قطار,
                                      (cl_mem)hwmap->سروت->انکڑے[p],
                                      map->پتہ[p],
                                      0, عدم, &events[e]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ساكن صحيح opencl_map_چوکھٹا(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحيح flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t صف_pitch;
    cl_event events[AV_عدد_انکڑے_سوچکاں];
    صحيح err, p;

    av_assert0(hwfc->sw_format == dst->format);

    إذا (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } وإلا {
        map_flags = 0;
        إذا (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        إذا (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(حجم(*map));
    إذا (!map)
        أرجع AVERROR(ENOMEM);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اچائی,
                                      &image_format, &image_desc);
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اچائی;
        region[2] = 1;

        map->پتہ[p] =
            cl_قطار_وچ_پاؤ_Map_Image(priv->command_قطار,
                              (cl_mem)src->انکڑے[p],
                              CL_FALSE, map_flags, origin, region,
                              &صف_pitch, عدم, 0, عدم,
                              &events[p], &cle);
        إذا (!map->پتہ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }

        dst->انکڑے[p] = map->پتہ[p];
        dst->linesize[p] = صف_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->انکڑے[p], dst->انکڑے[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_چوکھٹا, map);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    لكل (p = 0; p < AV_عدد_انکڑے_سوچکاں; p++) {
        إذا (!map->پتہ[p])
            اكسر;
        cl_قطار_وچ_پاؤ_Unmap_Mem_Object(priv->command_قطار,
                                (cl_mem)src->انکڑے[p],
                                map->پتہ[p],
                                0, عدم, &events[p]);
    }
    إذا (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    أرجع err;
}

#إذا HAVE_OPENCL_DRM_BEIGNET

تعريفنوع بنية DRMBeignet_منزل_Open_CLMapping {
    AVFrame              *drm_چوکھٹا;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor چوکھٹا;
} DRMBeignet_منزل_Open_CLMapping;

ساكن فراغ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_منزل_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    صحيح i;

    لكل (i = 0; i < mapping->چوکھٹا.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->چوکھٹا.planes[i]);
        إذا (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ساكن صحيح opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ثابت AVFrame *src,
                                       صحيح flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignet_منزل_Open_CLMapping *mapping;
    ثابت AVDRMFrameDescriptor *desc;
    cl_int cle;
    صحيح err, i, j, p;

    desc = (ثابت AVDRMFrameDescriptor*)src->انکڑے[0];

    mapping = av_mallocz(حجم(*mapping));
    إذا (!mapping)
        أرجع AVERROR(ENOMEM);

    p = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        لكل (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ثابت AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_اشاریہ];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .ناپ      = object->ناپ,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .وتھ    = plane->وتھ,
                .صف_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->چوڑائی, src->اچائی,
                                          &image_info.fmt,
                                          &image_desc);
            إذا (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                اذهب fail;
            }
            image_info.چوڑائی  = image_desc.image_چوڑائی;
            image_info.اچائی = image_desc.image_اچائی;

            mapping->چوکھٹا.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            إذا (!mapping->چوکھٹا.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            dst->انکڑے[p] = (uint8_t*)mapping->چوکھٹا.planes[p];
            mapping->چوکھٹا.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    لكل (p = 0; p < mapping->چوکھٹا.nb_planes; p++) {
        إذا (mapping->چوکھٹا.planes[p])
            clReleaseMemObject(mapping->چوکھٹا.planes[p]);
    }
    av_free(mapping);
    memset(dst->انکڑے, 0, حجم(dst->انکڑے));
    أرجع err;
}

#إذا HAVE_OPENCL_VAAPI_BEIGNET

ساكن صحيح opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ثابت AVFrame *src,
                                 صحيح flags)
{
    AVFrame *tmp;
    صحيح err;

    tmp = av_چوکھٹا_alloc();
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_مفرد;

    err = av_hwframe_map(tmp, src, flags);
    إذا (err < 0)
        اذهب fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_چوکھٹا_free(&tmp);
    أرجع err;
}

#جے_انت /* HAVE_OPENCL_VAAPI_BEIGNET */
#جے_انت /* HAVE_OPENCL_DRM_BEIGNET */

ساكن مضمن cl_mem_flags opencl_mem_flags_for_mapping(صحيح map_flags)
{
    إذا ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        أرجع CL_MEM_READ_WRITE;
    وإلا إذا (map_flags & AV_HWFRAME_MAP_READ)
        أرجع CL_MEM_READ_ONLY;
    وإلا إذا (map_flags & AV_HWFRAME_MAP_WRITE)
        أرجع CL_MEM_WRITE_ONLY;
    وإلا
        أرجع 0;
}

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA

ساكن فراغ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    صحيح p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_قطار_وچ_پاؤ_Release_VA_APIMedia_Surfaces_INTEL(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    لكل (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ساكن صحيح opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    صحيح err, p;

#إذا CONFIG_LIBMFX
    إذا (src->format == AV_PIX_FMT_QSV) {
        فراغ *ادھار_handle;
        mfx_چوکھٹا_Surface1 *mfx_surface = (mfx_چوکھٹا_Surface1*)src->انکڑے[3];
        err = ff_qsv_get_surface_ادھار_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &ادھار_handle);
        إذا (err < 0)
            أرجع err;
        va_surface = *(VASurfaceID *)ادھار_handle;
    } وإلا
#جے_انت
        إذا (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->انکڑے[3];
    } وإلا {
        أرجع AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    لكل (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        إذا (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }

        dst->انکڑے[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_قطار_وچ_پاؤ_Acquire_VA_APIMedia_Surfaces_INTEL(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        اذهب fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    لكل (p = 0; p < desc->nb_planes; p++)
        إذا (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->انکڑے, 0, حجم(dst->انکڑے));
    أرجع err;
}

#جے_انت

#إذا HAVE_OPENCL_DXVA2

ساكن فراغ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_قطار_وچ_پاؤ_Release_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        أرجع;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساكن صحيح opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;
    AVDXVA2_چوکھٹے_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحيح err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->انکڑے[3]);

    لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
        إذا (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->انکڑے[3])
            اكسر;
    }
    إذا (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        أرجع AVERROR(EINVAL);
    }

    desc = &چوکھٹے_priv->mapped_چوکھٹے[i];

    cle = device_priv->cl_قطار_وچ_پاؤ_Acquire_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    لكل (i = 0; i < desc->nb_planes; i++)
        dst->انکڑے[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    cle = device_priv->cl_قطار_وچ_پاؤ_Release_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->انکڑے, 0, حجم(dst->انکڑے));
    أرجع err;
}

ساكن صحيح opencl_چوکھٹے_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحيح flags)
{
    AVDXVA2_چوکھٹے_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحيح err, i, p, nb_planes;

    إذا (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }
    nb_planes = 2;

    إذا (src_fc->initial_pool_ناپ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    چوکھٹے_priv->nb_mapped_چوکھٹے = src_hwctx->nb_surfaces;

    چوکھٹے_priv->mapped_چوکھٹے =
        av_calloc(چوکھٹے_priv->nb_mapped_چوکھٹے,
                  حجم(*چوکھٹے_priv->mapped_چوکھٹے));
    إذا (!چوکھٹے_priv->mapped_چوکھٹے)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = عدم,
        };
        desc->nb_planes = nb_planes;
        لكل (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            إذا (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }
        }
    }

    أرجع 0;

fail:
    لكل (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            إذا (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&چوکھٹے_priv->mapped_چوکھٹے);
    چوکھٹے_priv->nb_mapped_چوکھٹے = 0;
    أرجع err;
}

#جے_انت

#إذا HAVE_OPENCL_D3D11

ساكن فراغ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_قطار_وچ_پاؤ_Release_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساكن صحيح opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحيح flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحيح err, اشاریہ, i;

    اشاریہ = (intptr_t)src->انکڑے[1];
    إذا (اشاریہ >= چوکھٹے_priv->nb_mapped_چوکھٹے) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", اشاریہ, چوکھٹے_priv->nb_mapped_چوکھٹے);
        أرجع AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           اشاریہ);

    desc = &چوکھٹے_priv->mapped_چوکھٹے[اشاریہ];

    cle = device_priv->cl_قطار_وچ_پاؤ_Acquire_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    لكل (i = 0; i < desc->nb_planes; i++)
        dst->انکڑے[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    cle = device_priv->cl_قطار_وچ_پاؤ_Release_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->انکڑے, 0, حجم(dst->انکڑے));
    أرجع err;
}

ساكن صحيح opencl_چوکھٹے_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحيح flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *چوکھٹے_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحيح err, i, p, nb_planes;

    إذا (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }
    nb_planes = 2;

    إذا (src_fc->initial_pool_ناپ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    چوکھٹے_priv->nb_mapped_چوکھٹے = src_fc->initial_pool_ناپ;

    چوکھٹے_priv->mapped_چوکھٹے =
        av_calloc(چوکھٹے_priv->nb_mapped_چوکھٹے,
                  حجم(*چوکھٹے_priv->mapped_چوکھٹے));
    إذا (!چوکھٹے_priv->mapped_چوکھٹے)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        desc->nb_planes = nb_planes;
        لكل (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            إذا (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (بنانشانی صحيح)subresource, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }
        }
    }

    أرجع 0;

fail:
    لكل (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            إذا (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&چوکھٹے_priv->mapped_چوکھٹے);
    چوکھٹے_priv->nb_mapped_چوکھٹے = 0;
    أرجع err;
}

#جے_انت

#إذا HAVE_OPENCL_DRM_ARM

تعريفنوع بنية DRMARMtoOpenCLMapping {
    صحيح nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    صحيح nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ساكن فراغ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    صحيح i;

    لكل (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    لكل (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ساكن صحيح opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = عدم;
    cl_mem_flags cl_flags;
    ثابت cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    صحيح err, i, j;

    desc = (ثابت AVDRMFrameDescriptor*)src->انکڑے[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    mapping = av_mallocz(حجم(*mapping));
    إذا (!mapping)
        أرجع AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    لكل (i = 0; i < desc->nb_objects; i++) {
        صحيح fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        إذا (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_حافظہ_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].ناپ, &cle);
        إذا (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].ناپ, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }
    }

    mapping->nb_planes = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];

        لكل (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_بفر;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_بفر_region region;
            صحيح p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->چوڑائی, src_fc->اچائی,
                                          &image_format, &image_desc);
            إذا (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                اذهب fail;
            }

            region.origin = plane->وتھ;
            region.ناپ   = image_desc.image_صف_pitch *
                            image_desc.image_اچائی;

            plane_بفر =
                cl_Create_Sub_بفر(mapping->object_buffers[plane->object_اشاریہ],
                                  cl_flags,
                                  CL_بفر_CREATE_TYPE_REGION,
                                  &region, &cle);
            إذا (!plane_بفر) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            image_desc.بفر = plane_بفر;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, عدم, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_بفر);

            إذا (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            ++mapping->nb_planes;
        }
    }

    لكل (i = 0; i < mapping->nb_planes; i++)
        dst->انکڑے[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    لكل (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    لكل (i = 0; i < mapping->nb_objects; i++) {
        إذا (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->انکڑے, 0, حجم(dst->انکڑے));
    أرجع err;
}

#جے_انت

#إذا HAVE_OPENCL_VIDEOTOOLBOX

ساكن فراغ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ساكن صحيح opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحيح flags)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref) src->انکڑے[3];
    IOSurfaceRef io_surface_ref = CVPixel_بفر_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = عدم;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    إذا (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        أرجع AVERROR_EXTERNAL;
    }

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع AVERROR(ENOMEM);

    لكل (صحيح p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->چوڑائی, src->اچائی,
                                      &image_format, &image_desc);
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        إذا (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            اذهب fail;
        }
        desc->nb_planes++;
    }

    لكل (صحيح i = 0; i < desc->nb_planes; i++)
        dst->انکڑے[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    إذا (err < 0)
        اذهب fail;

    dst->چوڑائی = src->چوڑائی;
    dst->اچائی = src->اچائی;

    أرجع 0;

fail:
    لكل (صحيح i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    أرجع err;
}

#جے_انت

ساكن صحيح opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ثابت AVFrame *src, صحيح flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    إذا (hwfc->sw_format != dst->format)
        أرجع AVERROR(ENOSYS);
    أرجع opencl_map_چوکھٹا(hwfc, dst, src, flags);
}

ساكن صحيح opencl_map_منزل(AVHWFramesContext *hwfc, AVFrame *dst,
                         ثابت AVFrame *src, صحيح flags)
{
    av_بن_ورتیا OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    بدل (src->format) {
#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_PIX_FMT_DRM_مفرد:
        إذا (priv->beignet_drm_mapping_usable)
            أرجع opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VAAPI_BEIGNET
    حالة AV_PIX_FMT_VAAPI:
        إذا (priv->beignet_drm_mapping_usable)
            أرجع opencl_map_from_vaapi(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالة AV_PIX_FMT_QSV:
    حالة AV_PIX_FMT_VAAPI:
        إذا (priv->qsv_mapping_usable)
            أرجع opencl_map_from_qsv(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_DXVA2
    حالة AV_PIX_FMT_DXVA2_VLD:
        إذا (priv->dxva2_mapping_usable)
            أرجع opencl_map_from_dxva2(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_D3D11
    حالة AV_PIX_FMT_D3D11:
        إذا (priv->d3d11_mapping_usable)
            أرجع opencl_map_from_d3d11(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_PIX_FMT_DRM_مفرد:
        إذا (priv->drm_arm_mapping_usable)
            أرجع opencl_map_from_drm_arm(hwfc, dst, src, flags);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_PIX_FMT_VIDEOTOOLBOX:
        أرجع opencl_map_from_vt(hwfc, dst, src, flags);
#جے_انت
    }
    أرجع AVERROR(ENOSYS);
}

ساكن صحيح opencl_چوکھٹے_derive_منزل(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, صحيح flags)
{
    av_بن_ورتیا OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    بدل (src_fc->device_ctx->type) {
#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_HWDEVICE_TYPE_DRM:
        إذا (!priv->beignet_drm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VAAPI_BEIGNET
    حالة AV_HWDEVICE_TYPE_VAAPI:
        إذا (!priv->beignet_drm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالة AV_HWDEVICE_TYPE_QSV:
    حالة AV_HWDEVICE_TYPE_VAAPI:
        إذا (!priv->qsv_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        إذا (!priv->dxva2_mapping_usable)
            أرجع AVERROR(ENOSYS);
        {
            صحيح err;
            err = opencl_چوکھٹے_derive_from_dxva2(dst_fc, src_fc, flags);
            إذا (err < 0)
                أرجع err;
        }
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_D3D11
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        إذا (!priv->d3d11_mapping_usable)
            أرجع AVERROR(ENOSYS);
        {
            صحيح err;
            err = opencl_چوکھٹے_derive_from_d3d11(dst_fc, src_fc, flags);
            إذا (err < 0)
                أرجع err;
        }
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_HWDEVICE_TYPE_DRM:
        إذا (!priv->drm_arm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#جے_انت
#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        اكسر;
#جے_انت
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }
    أرجع opencl_چوکھٹے_init_command_قطار(dst_fc);
}

ثابت HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_ناپ      = حجم(OpenCLDeviceContext),
    .چوکھٹے_hwctx_ناپ      = حجم(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .چوکھٹے_get_constraints = &opencl_چوکھٹے_get_constraints,
    .چوکھٹے_init            = &opencl_چوکھٹے_init,
    .چوکھٹے_uninit          = &opencl_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = &opencl_get_بفر,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_انکڑے_منزل       = &opencl_transfer_انکڑے_منزل,
    .transfer_انکڑے_from     = &opencl_transfer_انکڑے_from,

    .map_from               = &opencl_map_from,
    .map_منزل                 = &opencl_map_منزل,
    .چوکھٹے_derive_منزل       = &opencl_چوکھٹے_derive_منزل,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
