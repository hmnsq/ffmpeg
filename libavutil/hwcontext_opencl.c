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

#شامل <string.h>

#شامل "config.h"

#شامل "avassert.h"
#شامل "avstring.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_opencl.h"
#شامل "mem.h"
#شامل "pixdesc.h"

#اگر HAVE_OPENCL_VAAPI_BEIGNET
#شامل <unistd.h>
#شامل <va/va.h>
#شامل <va/va_drmcommon.h>
#شامل <CL/cl_intel.h>
#شامل "hwcontext_vaapi.h"
#اگر_ختم

#اگر HAVE_OPENCL_DRM_BEIGNET
#شامل <unistd.h>
#شامل <CL/cl_intel.h>
#شامل "hwcontext_drm.h"
#اگر_ختم

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
#اگر CONFIG_LIBMFX
#شامل <mfxstructures.h>
#اگر_ختم
#شامل <va/va.h>
#شامل <CL/cl_va_api_media_sharing_intel.h>
#شامل "hwcontext_vaapi.h"
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2
#تعریف_کرو COBJMACROS
#شامل <CL/cl_dx9_media_sharing.h>
#شامل <dxva2api.h>
#شامل "hwcontext_dxva2.h"
#اگر_ختم

#اگر HAVE_OPENCL_D3D11
#شامل <CL/cl_d3d11.h>
#شامل "hwcontext_d3d11va.h"
#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM
#شامل <CL/cl_ext.h>
#شامل <drm_fourcc.h>
#شامل "hwcontext_drm.h"
#اگر_ختم

#اگر HAVE_OPENCL_VIDEOTOOLBOX
#شامل <OpenCL/cl_gl_ext.h>
#شامل <VideoToolbox/VideoToolbox.h>
#اگر_ختم

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
خارجی صحیح ff_qsv_get_surface_بنیاد_handle(mfx_چوکھٹا_Surface1 *surf,
                                          شمار AVHWDeviceType بنیاد_dev_typ,
                                          خالی **بنیاد_handle);
#اگر_ختم


قسمتعریف ساخت OpenCLDeviceContext {
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
#اگر HAVE_OPENCL_DRM_BEIGNET
    صحیح beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#اگر_ختم

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    صحیح qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_قطار_میں_ڈالو_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_قطار_میں_ڈالو_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_قطار_میں_ڈالو_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_قطار_میں_ڈالو_Release_VA_APIMedia_Surfaces_INTEL;
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2
    صحیح dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_قطار_میں_ڈالو_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_قطار_میں_ڈالو_Acquire_DX9_Media_Surfaces_KHR;
    cl_قطار_میں_ڈالو_Release_DX9_Media_Surfaces_KHR_fn
        cl_قطار_میں_ڈالو_Release_DX9_Media_Surfaces_KHR;
#اگر_ختم

#اگر HAVE_OPENCL_D3D11
    صحیح d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_قطار_میں_ڈالو_Acquire_D3_D11_Objects_KHR_fn
        cl_قطار_میں_ڈالو_Acquire_D3_D11_Objects_KHR;
    cl_قطار_میں_ڈالو_Release_D3_D11_Objects_KHR_fn
        cl_قطار_میں_ڈالو_Release_D3_D11_Objects_KHR;
#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM
    صحیح drm_arm_mapping_usable;
#اگر_ختم
} OpenCLDeviceContext;

قسمتعریف ساخت OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_قطار command_قطار;

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    صحیح                   nb_mapped_چوکھٹے;
    AVOpenCLFrameDescriptor *mapped_چوکھٹے;
#اگر_ختم
} OpenCLFramesContext;


ساکن خالی CL_CALLBACK opencl_error_callback(ثابت حرف *errinfo,
                                              ثابت خالی *نجی_info,
                                              size_t cb,
                                              خالی *user_ڈیٹا)
{
    AVHWDeviceContext *ctx = user_ڈیٹا;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ساکن خالی opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ساکن ساخت {
    ثابت حرف *کلید;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_نسخہ    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ساکن ساخت {
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

ساکن ساخت {
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

ساکن حرف *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info کلید)
{
    حرف *str;
    size_t سائز;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, کلید, 0, تہی, &سائز);
    اگر (cle != CL_SUCCESS)
        واپس تہی;
    str = av_malloc(سائز);
    اگر (!str)
        واپس تہی;
    cle = clGetPlatformInfo(platform_id, کلید, سائز, str, &سائز);
    اگر (cle != CL_SUCCESS) {
        av_free(str);
        واپس تہی;
    }
    av_assert0(لڑی_لمبائی(str) + 1 == سائز);
    واپس str;
}

ساکن حرف *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info کلید)
{
    حرف *str;
    size_t سائز;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, کلید, 0, تہی, &سائز);
    اگر (cle != CL_SUCCESS)
        واپس تہی;
    str = av_malloc(سائز);
    اگر (!str)
        واپس تہی;
    cle = clGetDeviceInfo(device_id, کلید, سائز, str, &سائز);
    اگر (cle != CL_SUCCESS) {
        av_free(str);
        واپس تہی;
    }
    av_assert0(لڑی_لمبائی(str) + 1== سائز);
    واپس str;
}

ساکن صحیح opencl_check_platform_extension(cl_platform_id platform_id,
                                           ثابت حرف *name)
{
    حرف *str;
    صحیح ملا = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    اگر (str && لڑی_تلاش(str, name))
        ملا = 1;
    av_free(str);
    واپس ملا;
}

ساکن صحیح opencl_check_device_extension(cl_device_id device_id,
                                         ثابت حرف *name)
{
    حرف *str;
    صحیح ملا = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    اگر (str && لڑی_تلاش(str, name))
        ملا = 1;
    av_free(str);
    واپس ملا;
}

av_غیر_مستعمل ساکن صحیح opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ثابت حرف *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    اگر (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        واپس 1;
    }

    اگر (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        واپس 1;
    }

    واپس 0;
}

ساکن صحیح opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      خالی *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, تہی, nb_platforms);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        واپس AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, حجم(**platforms));
    اگر (!*platforms)
        واپس AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        واپس AVERROR(ENODEV);
    }

    واپس 0;
}

ساکن صحیح opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ثابت حرف *platform_name,
                                  خالی *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionary_اندراج *param;
    حرف *str;
    صحیح i, ret = 0;

    برائے (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].کلید,
                            تہی, 0);
        اگر (!param)
            جاری;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        اگر (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].کلید, platform_name);
            واپس AVERROR_UNKNOWN;
        }
        اگر (!av_stristr(str, param->قدر)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    واپس ret;
}

ساکن صحیح opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ثابت حرف *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    خالی *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, تہی, nb_devices);
    اگر (cle == CL_DEVICE_NOT_ملا) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        واپس 0;
    } ورنہ اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        واپس AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    اگر (!*devices)
        واپس AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        واپس AVERROR(ENODEV);
    }

    واپس 0;
}

ساکن صحیح opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ثابت حرف *device_name,
                                خالی *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionary_اندراج *param;
    حرف *str;
    صحیح i, ret = 0;

    param = av_dict_get(opts, "device_type", تہی, 0);
    اگر (param) {
        cl_device_type مطابقت_type = 0, device_type;
        cl_int cle;

        برائے (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            اگر (!strcmp(opencl_device_types[i].کلید, param->قدر)) {
                مطابقت_type = opencl_device_types[i].type;
                توڑو;
            }
        }
        اگر (!مطابقت_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->قدر);
            واپس AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              حجم(device_type), &device_type, تہی);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            واپس AVERROR_UNKNOWN;
        }

        اگر (!(device_type & مطابقت_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            واپس 1;
        }
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].کلید,
                            تہی, 0);
        اگر (!param)
            جاری;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        اگر (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].کلید, device_name);
            واپس AVERROR_UNKNOWN;
        }
        اگر (!av_stristr(str, param->قدر)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    واپس ret;
}

قسمتعریف ساخت OpenCLDeviceSelector {
    صحیح platform_اشاریہ;
    صحیح device_اشاریہ;
    خالی *context;
    صحیح (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               خالی *context);
    صحیح (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               خالی *context);
    صحیح (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               خالی *context);
    صحیح (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ثابت حرف *device_name,
                               خالی *context);
} OpenCLDeviceSelector;

ساکن صحیح opencl_device_create_اندرونی(AVHWDeviceContext *hwdev,
                                         ثابت OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = تہی;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = تہی;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    حرف *platform_name_src = تہی,
         *device_name_src   = تہی;
    صحیح err, ملا, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    اگر (err)
        واپس err;

    ملا = 0;
    برائے (p = 0; p < nb_platforms; p++) {
        ثابت حرف *platform_name;

        اگر (selector->platform_اشاریہ >= 0 &&
            selector->platform_اشاریہ != p)
            جاری;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        اگر (platform_name_src)
            platform_name = platform_name_src;
        ورنہ
            platform_name = "Unknown Platform";

        اگر (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            اگر (err < 0)
                جاؤ fail;
            اگر (err > 0)
                جاری;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        اگر (err < 0)
            جاری;

        برائے (d = 0; d < nb_devices; d++) {
            ثابت حرف *device_name;

            اگر (selector->device_اشاریہ >= 0 &&
                selector->device_اشاریہ != d)
                جاری;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            اگر (device_name_src)
                device_name = device_name_src;
            ورنہ
                device_name = "Unknown Device";

            اگر (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                اگر (err < 0)
                    جاؤ fail;
                اگر (err > 0)
                    جاری;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++ملا;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    اگر (ملا == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        جاؤ fail;
    }
    اگر (ملا > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        جاؤ fail;
    }

    اگر (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } ورنہ {
        اگر (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    اگر (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        جاؤ fail;
    }

    hwdev->آزاد = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    واپس err;
}

ساکن صحیح opencl_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                                AVDictionary *opts, صحیح flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    اگر (device && device[0]) {
        // Match one or both indices for platform and device.
        صحیح d = -1, p = -1, ret;
        اگر (device[0] == '.')
            ret = لڑی_سے_پڑھو(device, ".%d", &d);
        ورنہ
            ret = لڑی_سے_پڑھو(device, "%d.%d", &p, &d);
        اگر (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            واپس AVERROR(EINVAL);
        }
        selector.platform_اشاریہ = p;
        selector.device_اشاریہ   = d;
    } ورنہ {
        selector.platform_اشاریہ = -1;
        selector.device_اشاریہ   = -1;
    }

    واپس opencl_device_create_اندرونی(hwdev, &selector, تہی);
}

ساکن صحیح opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    اگر (hwctx->command_قطار) {
        cle = cl_Retain_Command_قطار(hwctx->command_قطار);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            واپس AVERROR(EIO);
        }
        priv->command_قطار = hwctx->command_قطار;
    } ورنہ {
        priv->command_قطار = cl_Create_Command_قطار(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        اگر (!priv->command_قطار) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            واپس AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          حجم(priv->platform_id), &priv->platform_id,
                          تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        واپس AVERROR(EIO);
    }

#تعریف_کرو CL_FUNC(name, desc) کرو {                                \
        اگر (fail)                                               \
            توڑو;                                              \
        priv->name = cl_Get_Extension_Function_پتہ_For_Platform(  \
            priv->platform_id, #name);                          \
        اگر (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } ورنہ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } جب (0)

#اگر HAVE_OPENCL_DRM_BEIGNET
    {
        صحیح fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } ورنہ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#اگر_ختم

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_سائز;
        cl_context_properties *props = تہی;
        VADisplay va_display;
        ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";
        صحیح i, fail = 0;

        اگر (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            جاؤ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, تہی, &props_سائز);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            جاؤ no_qsv;
        }
        اگر (props_سائز == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            جاؤ no_qsv;
        }

        props = av_malloc(props_سائز);
        اگر (!props)
            واپس AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_سائز, props, تہی);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            جاؤ no_qsv;
        }

        va_display = تہی;
        برائے (i = 0; i < (props_سائز / حجم(*props) - 1); i++) {
            اگر (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                توڑو;
            }
        }
        اگر (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            جاؤ no_qsv;
        }
        اگر (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            جاؤ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_قطار_میں_ڈالو_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_قطار_میں_ڈالو_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        اگر (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } ورنہ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2
    {
        صحیح fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_قطار_میں_ڈالو_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_قطار_میں_ڈالو_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } ورنہ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#اگر_ختم

#اگر HAVE_OPENCL_D3D11
    {
        ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";
        ثابت حرف *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        صحیح fail = 0;

        اگر (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } ورنہ اگر (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_قطار_میں_ڈالو_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_قطار_میں_ڈالو_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } ورنہ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM
    {
        ثابت حرف *drm_arm_ext = "cl_arm_import_memory";
        ثابت حرف *image_ext   = "cl_khr_image2d_from_buffer";
        صحیح fail = 0;

        اگر (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        اگر (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } ورنہ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#اگر_ختم

#تعریف_منسوخ CL_FUNC

    واپس 0;
}

ساکن خالی opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    اگر (priv->command_قطار) {
        cle = cl_Release_Command_قطار(priv->command_قطار);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_قطار = تہی;
    }
}

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
ساکن صحیح opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ثابت حرف *platform_name,
                                                    خالی *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    اگر (!cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        واپس 1;
    } ورنہ {
        واپس 0;
    }
}

ساکن صحیح opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ثابت حرف *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      خالی *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    اگر (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        واپس AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, تہی, nb_devices);
    اگر (cle == CL_DEVICE_NOT_ملا) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        واپس 0;
    } ورنہ اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        واپس AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    اگر (!*devices)
        واپس AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن صحیح opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ثابت حرف *device_name,
                                                  خالی *context)
{
    ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";

    اگر (opencl_check_device_extension(device_id, va_ext)) {
        واپس 0;
    } ورنہ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        واپس 1;
    }
}
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2
ساکن صحیح opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        خالی *context)
{
    ثابت حرف *dx9_ext = "cl_khr_dx9_media_sharing";

    اگر (opencl_check_platform_extension(platform_id, dx9_ext)) {
        واپس 0;
    } ورنہ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        واپس 1;
    }
}

ساکن صحیح opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          خالی *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    اگر (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        واپس AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (خالی**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, تہی, nb_devices);
    اگر (cle == CL_DEVICE_NOT_ملا) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        واپس 0;
    } ورنہ اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        واپس AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    اگر (!*devices)
        واپس AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (خالی**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}
#اگر_ختم

#اگر HAVE_OPENCL_D3D11
ساکن صحیح opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        خالی *context)
{
    ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";

    اگر (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        واپس 0;
    } ورنہ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        واپس 1;
    }
}

ساکن صحیح opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          خالی *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        cl_Get_Extension_Function_پتہ_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    اگر (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        واپس AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, تہی, nb_devices);
    اگر (cle == CL_DEVICE_NOT_ملا) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        واپس 0;
    } ورنہ اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        واپس AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    اگر (!*devices)
        واپس AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ساکن صحیح opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ثابت حرف *device_name,
                                    خالی *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          حجم(device_type), &device_type, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        واپس AVERROR_UNKNOWN;
    }
    اگر (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        واپس 1;
    }

    واپس 0;
}
#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM
ساکن صحیح opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          خالی *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    اگر (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        واپس 0;
    } ورنہ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        واپس 1;
    }
}

ساکن صحیح opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ثابت حرف *device_name,
                                        خالی *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    اگر (opencl_check_device_extension(device_id, drm_arm_ext)) {
        واپس 0;
    } ورنہ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        واپس 1;
    }
}
#اگر_ختم

ساکن صحیح opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                صحیح flags)
{
    صحیح err;
    انتخاب (src_ctx->type) {

#اگر HAVE_OPENCL_DRM_BEIGNET
    حالت AV_HWDEVICE_TYPE_DRM:
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = تہی;

            err = av_dict_سیٹ(&selector_opts, "platform_vendor", "Intel", 0);
            اگر (err >= 0)
                err = av_dict_سیٹ(&selector_opts, "platform_version", "beignet", 0);
            اگر (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_اشاریہ      = -1,
                    .device_اشاریہ        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = تہی,
                };
                err = opencl_device_create_اندرونی(hwdev, &selector, تہی);
            }
            av_dict_free(&selector_opts);
        }
        توڑو;
#اگر_ختم

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    حالت AV_HWDEVICE_TYPE_VAAPI:
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
        توڑو;
#اگر_ختم

#اگر HAVE_OPENCL_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            اگر (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (غیرعلامتی طویل)hr);
                err = AVERROR_UNKNOWN;
                توڑو;
            }

            hr = IDirect3_DDevice_Manager9_تالا_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            اگر (SUCCEEDED(hr)) {
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
            } ورنہ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (غیرعلامتی طویل)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        توڑو;
#اگر_ختم

#اگر HAVE_OPENCL_D3D11
    حالت AV_HWDEVICE_TYPE_D3D11VA:
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
        توڑو;
#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_اشاریہ      = -1,
                .device_اشاریہ        = -1,
                .context             = تہی,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_اندرونی(hwdev, &selector, تہی);
        }
        توڑو;
#اگر_ختم

#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, تہی, تہی, 0);
        توڑو;
#اگر_ختم

    طےشدہ:
        err = AVERROR(ENOSYS);
        توڑو;
    }

    واپس err;
}

ساکن صحیح opencl_get_plane_format(شمار AVPixelFormat pixfmt,
                                   صحیح plane, صحیح چوڑائی, صحیح اونچائی,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ثابت AVPixFmtDescriptor *desc;
    ثابت AVComponentDescriptor *comp;
    صحیح channels = 0, ترتیب = 0, گہرائی = 0, قدم = 0;
    صحیح wsub, hsub, alpha;
    صحیح c;

    اگر (plane >= AV_عدد_ڈیٹا_اشارے)
        واپس AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    اگر (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        واپس AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    اگر (چوڑائی & wsub - 1 || اونچائی & hsub - 1)
        واپس AVERROR(EINVAL);

    برائے (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        اگر (comp->plane != plane)
            جاری;
        // The step size must be a power of two.
        اگر (comp->قدم != 1 && comp->قدم != 2 &&
            comp->قدم != 4 && comp->قدم != 8)
            واپس AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        اگر (comp->سرکاؤ + comp->گہرائی != 8 &&
            comp->سرکاؤ + comp->گہرائی != 16 &&
            comp->سرکاؤ + comp->گہرائی != 32)
            واپس AVERROR(EINVAL);
        // The depth must not vary between components.
        اگر (گہرائی && comp->گہرائی != گہرائی)
            واپس AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        اگر (comp->گہرائی > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            واپس AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        اگر (قدم && comp->قدم != قدم)
            واپس AVERROR(EINVAL);

        گہرائی = comp->گہرائی;
        ترتیب = ترتیب * 10 + comp->انحراف / ((گہرائی + 7) / 8) + 1;
        قدم  = comp->قدم;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    اگر (channels == 0)
        واپس AVERROR(ENOENT);

    memset(image_format, 0, حجم(*image_format));
    memset(image_desc,   0, حجم(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    اگر (plane == 0 || alpha) {
        image_desc->image_چوڑائی     = چوڑائی;
        image_desc->image_اونچائی    = اونچائی;
        image_desc->image_صف_pitch = قدم * چوڑائی;
    } ورنہ {
        image_desc->image_چوڑائی     = چوڑائی  / wsub;
        image_desc->image_اونچائی    = اونچائی / hsub;
        image_desc->image_صف_pitch = قدم * چوڑائی / wsub;
    }

    اگر (گہرائی <= 8) {
        image_format->image_channel_ڈیٹا_type = CL_UNORM_INT8;
    } ورنہ {
        اگر (گہرائی <= 16)
            image_format->image_channel_ڈیٹا_type = CL_UNORM_INT16;
        ورنہ اگر (گہرائی == 32)
            image_format->image_channel_ڈیٹا_type = CL_FLOAT;
        ورنہ
            واپس AVERROR(EINVAL);
    }

#تعریف_کرو CHANNEL_ترتیب(ترتیب, type) \
    حالت ترتیب: image_format->image_channel_ترتیب = type; توڑو;
    انتخاب (ترتیب) {
        CHANNEL_ترتیب(1,    CL_R);
        CHANNEL_ترتیب(12,   CL_RG);
        CHANNEL_ترتیب(1234, CL_RGBA);
        CHANNEL_ترتیب(2341, CL_ARGB);
        CHANNEL_ترتیب(3214, CL_BGRA);
#اگر_تعریف_شدہ CL_ABGR
        CHANNEL_ترتیب(4321, CL_ABGR);
#اگر_ختم
    طےشدہ:
        واپس AVERROR(EINVAL);
    }
#تعریف_منسوخ CHANNEL_ترتیب

    واپس 0;
}

ساکن صحیح opencl_چوکھٹے_get_constraints(AVHWDeviceContext *hwdev,
                                         ثابت خالی *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = تہی;
    cl_int cle;
    شمار AVPixelFormat pix_fmt;
    صحیح err, pix_fmts_ملا;
    size_t max_چوڑائی, max_اونچائی;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_چوڑائی,
                          حجم(max_چوڑائی), &max_چوڑائی, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } ورنہ {
        constraints->max_چوڑائی = max_چوڑائی;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_اونچائی,
                          حجم(max_اونچائی), &max_اونچائی, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } ورنہ {
        constraints->max_اونچائی = max_اونچائی;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_چوڑائی, constraints->max_اونچائی);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, تہی, &nb_image_formats);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        جاؤ fail;
    }
    اگر (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        جاؤ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, حجم(*image_formats));
    اگر (!image_formats) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, تہی);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        جاؤ fail;
    }

    pix_fmts_ملا = 0;
    برائے (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        صحیح plane, i;

        برائے (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            اگر (err < 0)
                توڑو;

            برائے (i = 0; i < nb_image_formats; i++) {
                اگر (image_formats[i].image_channel_ترتیب ==
                    image_format.image_channel_ترتیب &&
                    image_formats[i].image_channel_ڈیٹا_type ==
                    image_format.image_channel_ڈیٹا_type)
                    توڑو;
            }
            اگر (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                توڑو;
            }
        }
        اگر (err != AVERROR(ENOENT))
            جاری;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_ملا + 2,
                                حجم(*constraints->valid_sw_formats));
        اگر (err < 0)
            جاؤ fail;
        constraints->valid_sw_formats[pix_fmts_ملا] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_ملا + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_ملا;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;

fail:
    av_freep(&image_formats);
    واپس err;
}

ساکن خالی opencl_pool_free(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)ڈیٹا;
    cl_int cle;
    صحیح p;

    برائے (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ساکن AVBufferRef *opencl_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    صحیح err, p;
    AVBufferRef *ref;

    desc = av_mallocz(حجم(*desc));
    اگر (!desc)
        واپس تہی;

    برائے (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->چوڑائی, hwfc->اونچائی,
                                      &image_format, &image_desc);
        اگر (err == AVERROR(ENOENT))
            توڑو;
        اگر (err < 0)
            جاؤ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_صف_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, تہی, &cle);
        اگر (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            جاؤ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_بفر_create((uint8_t*)desc, حجم(*desc),
                           &opencl_pool_free, hwfc, 0);
    اگر (!ref)
        جاؤ fail;

    واپس ref;

fail:
    برائے (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    واپس تہی;
}

ساکن صحیح opencl_چوکھٹے_init_command_قطار(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_قطار = hwctx->command_قطار ? hwctx->command_قطار
                                               : devpriv->command_قطار;
    cle = cl_Retain_Command_قطار(priv->command_قطار);
    اگر (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        واپس AVERROR(EIO);
    }

    واپس 0;
}

ساکن صحیح opencl_چوکھٹے_init(AVHWFramesContext *hwfc)
{
    اگر (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_اندرونی =
            av_بفر_pool_init2(حجم(cl_mem), hwfc,
                                 &opencl_pool_alloc, تہی);
        اگر (!ffhwframesctx(hwfc)->pool_اندرونی)
            واپس AVERROR(ENOMEM);
    }

    واپس opencl_چوکھٹے_init_command_قطار(hwfc);
}

ساکن خالی opencl_چوکھٹے_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    صحیح i, p;
    برائے (i = 0; i < priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_چوکھٹے[i];
        برائے (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            اگر (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_چوکھٹے);
#اگر_ختم

    اگر (priv->command_قطار) {
        cle = cl_Release_Command_قطار(priv->command_قطار);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_قطار = تہی;
    }
}

ساکن صحیح opencl_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکھٹا)
{
    AVOpenCLFrameDescriptor *desc;
    صحیح p;

    چوکھٹا->buf[0] = av_بفر_pool_get(hwfc->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)چوکھٹا->buf[0]->ڈیٹا;

    برائے (p = 0; p < desc->nb_planes; p++)
        چوکھٹا->ڈیٹا[p] = (uint8_t*)desc->planes[p];

    چوکھٹا->format  = AV_PIX_FMT_OPENCL;
    چوکھٹا->چوڑائی   = hwfc->چوڑائی;
    چوکھٹا->اونچائی  = hwfc->اونچائی;

    واپس 0;
}

ساکن صحیح opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       شمار AVHWFrameTransferDirection dir,
                                       شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    واپس 0;
}

ساکن صحیح opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, صحیح nb_events)
{
    cl_int cle;
    صحیح i;

    cle = clWaitForEvents(nb_events, events);
    اگر (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        واپس AVERROR(EIO);
    }

    برائے (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    واپس 0;
}

ساکن صحیح opencl_transfer_ڈیٹا_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_عدد_ڈیٹا_اشارے];
    صحیح err, p;

    اگر (dst->format != hwfc->sw_format)
        واپس AVERROR(EINVAL);

    برائے (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اونچائی,
                                      &image_format, &image_desc);
        اگر (err < 0) {
            اگر (err == AVERROR(ENOENT))
                err = 0;
            توڑو;
        }

        اگر (!dst->ڈیٹا[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            توڑو;
        }

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اونچائی;
        region[2] = 1;

        cle = cl_قطار_میں_ڈالو_Read_Image(priv->command_قطار,
                                 (cl_mem)src->ڈیٹا[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->ڈیٹا[p],
                                 0, تہی, &events[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            توڑو;
        }
    }

    opencl_wait_events(hwfc, events, p);

    واپس err;
}

ساکن صحیح opencl_transfer_ڈیٹا_مقصد(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_عدد_ڈیٹا_اشارے];
    صحیح err, p;

    اگر (src->format != hwfc->sw_format)
        واپس AVERROR(EINVAL);

    برائے (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اونچائی,
                                      &image_format, &image_desc);
        اگر (err < 0) {
            اگر (err == AVERROR(ENOENT))
                err = 0;
            توڑو;
        }

        اگر (!src->ڈیٹا[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            توڑو;
        }

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اونچائی;
        region[2] = 1;

        cle = cl_قطار_میں_ڈالو_Write_Image(priv->command_قطار,
                                  (cl_mem)dst->ڈیٹا[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->ڈیٹا[p],
                                  0, تہی, &events[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            توڑو;
        }
    }

    opencl_wait_events(hwfc, events, p);

    واپس err;
}

قسمتعریف ساخت OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    خالی *پتہ[AV_عدد_ڈیٹا_اشارے];
} OpenCLMapping;

ساکن خالی opencl_unmap_چوکھٹا(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_عدد_ڈیٹا_اشارے];
    صحیح p, e;
    cl_int cle;

    برائے (p = e = 0; p < FF_ARRAY_ELEMS(map->پتہ); p++) {
        اگر (!map->پتہ[p])
            توڑو;

        cle = cl_قطار_میں_ڈالو_Unmap_Mem_Object(priv->command_قطار,
                                      (cl_mem)hwmap->ماخذ->ڈیٹا[p],
                                      map->پتہ[p],
                                      0, تہی, &events[e]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ساکن صحیح opencl_map_چوکھٹا(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحیح flags)
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
    cl_event events[AV_عدد_ڈیٹا_اشارے];
    صحیح err, p;

    av_assert0(hwfc->sw_format == dst->format);

    اگر (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } ورنہ {
        map_flags = 0;
        اگر (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        اگر (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(حجم(*map));
    اگر (!map)
        واپس AVERROR(ENOMEM);

    برائے (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->چوڑائی, src->اونچائی,
                                      &image_format, &image_desc);
        اگر (err == AVERROR(ENOENT))
            توڑو;
        اگر (err < 0)
            جاؤ fail;

        region[0] = image_desc.image_چوڑائی;
        region[1] = image_desc.image_اونچائی;
        region[2] = 1;

        map->پتہ[p] =
            cl_قطار_میں_ڈالو_Map_Image(priv->command_قطار,
                              (cl_mem)src->ڈیٹا[p],
                              CL_FALSE, map_flags, origin, region,
                              &صف_pitch, تہی, 0, تہی,
                              &events[p], &cle);
        اگر (!map->پتہ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            جاؤ fail;
        }

        dst->ڈیٹا[p] = map->پتہ[p];
        dst->linesize[p] = صف_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->ڈیٹا[p], dst->ڈیٹا[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    اگر (err < 0)
        جاؤ fail;

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_چوکھٹا, map);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    برائے (p = 0; p < AV_عدد_ڈیٹا_اشارے; p++) {
        اگر (!map->پتہ[p])
            توڑو;
        cl_قطار_میں_ڈالو_Unmap_Mem_Object(priv->command_قطار,
                                (cl_mem)src->ڈیٹا[p],
                                map->پتہ[p],
                                0, تہی, &events[p]);
    }
    اگر (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    واپس err;
}

#اگر HAVE_OPENCL_DRM_BEIGNET

قسمتعریف ساخت DRMBeignet_مقصد_Open_CLMapping {
    AVFrame              *drm_چوکھٹا;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor چوکھٹا;
} DRMBeignet_مقصد_Open_CLMapping;

ساکن خالی opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_مقصد_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    صحیح i;

    برائے (i = 0; i < mapping->چوکھٹا.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->چوکھٹا.planes[i]);
        اگر (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ساکن صحیح opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ثابت AVFrame *src,
                                       صحیح flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignet_مقصد_Open_CLMapping *mapping;
    ثابت AVDRMFrameDescriptor *desc;
    cl_int cle;
    صحیح err, i, j, p;

    desc = (ثابت AVDRMFrameDescriptor*)src->ڈیٹا[0];

    mapping = av_mallocz(حجم(*mapping));
    اگر (!mapping)
        واپس AVERROR(ENOMEM);

    p = 0;
    برائے (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        برائے (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ثابت AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_اشاریہ];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .سائز      = object->سائز,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .انحراف    = plane->انحراف,
                .صف_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->چوڑائی, src->اونچائی,
                                          &image_info.fmt,
                                          &image_desc);
            اگر (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                جاؤ fail;
            }
            image_info.چوڑائی  = image_desc.image_چوڑائی;
            image_info.اونچائی = image_desc.image_اونچائی;

            mapping->چوکھٹا.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            اگر (!mapping->چوکھٹا.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                جاؤ fail;
            }

            dst->ڈیٹا[p] = (uint8_t*)mapping->چوکھٹا.planes[p];
            mapping->چوکھٹا.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    برائے (p = 0; p < mapping->چوکھٹا.nb_planes; p++) {
        اگر (mapping->چوکھٹا.planes[p])
            clReleaseMemObject(mapping->چوکھٹا.planes[p]);
    }
    av_free(mapping);
    memset(dst->ڈیٹا, 0, حجم(dst->ڈیٹا));
    واپس err;
}

#اگر HAVE_OPENCL_VAAPI_BEIGNET

ساکن صحیح opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ثابت AVFrame *src,
                                 صحیح flags)
{
    AVFrame *tmp;
    صحیح err;

    tmp = av_چوکھٹا_alloc();
    اگر (!tmp)
        واپس AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_مفرد;

    err = av_hwframe_map(tmp, src, flags);
    اگر (err < 0)
        جاؤ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    اگر (err < 0)
        جاؤ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_چوکھٹا_free(&tmp);
    واپس err;
}

#اگر_ختم /* HAVE_OPENCL_VAAPI_BEIGNET */
#اگر_ختم /* HAVE_OPENCL_DRM_BEIGNET */

ساکن اندرونی cl_mem_flags opencl_mem_flags_for_mapping(صحیح map_flags)
{
    اگر ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        واپس CL_MEM_READ_WRITE;
    ورنہ اگر (map_flags & AV_HWFRAME_MAP_READ)
        واپس CL_MEM_READ_ONLY;
    ورنہ اگر (map_flags & AV_HWFRAME_MAP_WRITE)
        واپس CL_MEM_WRITE_ONLY;
    ورنہ
        واپس 0;
}

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA

ساکن خالی opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    صحیح p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_قطار_میں_ڈالو_Release_VA_APIMedia_Surfaces_INTEL(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    برائے (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ساکن صحیح opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    صحیح err, p;

#اگر CONFIG_LIBMFX
    اگر (src->format == AV_PIX_FMT_QSV) {
        خالی *بنیاد_handle;
        mfx_چوکھٹا_Surface1 *mfx_surface = (mfx_چوکھٹا_Surface1*)src->ڈیٹا[3];
        err = ff_qsv_get_surface_بنیاد_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &بنیاد_handle);
        اگر (err < 0)
            واپس err;
        va_surface = *(VASurfaceID *)بنیاد_handle;
    } ورنہ
#اگر_ختم
        اگر (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->ڈیٹا[3];
    } ورنہ {
        واپس AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        واپس AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(حجم(*desc));
    اگر (!desc)
        واپس AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    برائے (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        اگر (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            جاؤ fail;
        }

        dst->ڈیٹا[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_قطار_میں_ڈالو_Acquire_VA_APIMedia_Surfaces_INTEL(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        جاؤ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        جاؤ fail;

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    برائے (p = 0; p < desc->nb_planes; p++)
        اگر (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->ڈیٹا, 0, حجم(dst->ڈیٹا));
    واپس err;
}

#اگر_ختم

#اگر HAVE_OPENCL_DXVA2

ساکن خالی opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_قطار_میں_ڈالو_Release_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        واپس;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساکن صحیح opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
    AVDXVA2_چوکھٹے_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحیح err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->ڈیٹا[3]);

    برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
        اگر (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->ڈیٹا[3])
            توڑو;
    }
    اگر (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        واپس AVERROR(EINVAL);
    }

    desc = &چوکھٹے_priv->mapped_چوکھٹے[i];

    cle = device_priv->cl_قطار_میں_ڈالو_Acquire_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        واپس AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        جاؤ fail;

    برائے (i = 0; i < desc->nb_planes; i++)
        dst->ڈیٹا[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    cle = device_priv->cl_قطار_میں_ڈالو_Release_DX9_Media_Surfaces_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ڈیٹا, 0, حجم(dst->ڈیٹا));
    واپس err;
}

ساکن صحیح opencl_چوکھٹے_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحیح flags)
{
    AVDXVA2_چوکھٹے_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحیح err, i, p, nb_planes;

    اگر (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        واپس AVERROR(EINVAL);
    }
    nb_planes = 2;

    اگر (src_fc->initial_pool_سائز == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        واپس AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        واپس AVERROR(EINVAL);

    چوکھٹے_priv->nb_mapped_چوکھٹے = src_hwctx->nb_surfaces;

    چوکھٹے_priv->mapped_چوکھٹے =
        av_calloc(چوکھٹے_priv->nb_mapped_چوکھٹے,
                  حجم(*چوکھٹے_priv->mapped_چوکھٹے));
    اگر (!چوکھٹے_priv->mapped_چوکھٹے)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = تہی,
        };
        desc->nb_planes = nb_planes;
        برائے (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            اگر (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                جاؤ fail;
            }
        }
    }

    واپس 0;

fail:
    برائے (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        برائے (p = 0; p < desc->nb_planes; p++) {
            اگر (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&چوکھٹے_priv->mapped_چوکھٹے);
    چوکھٹے_priv->nb_mapped_چوکھٹے = 0;
    واپس err;
}

#اگر_ختم

#اگر HAVE_OPENCL_D3D11

ساکن خالی opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *چوکھٹے_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_قطار_میں_ڈالو_Release_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساکن صحیح opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *چوکھٹے_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحیح err, اشاریہ, i;

    اشاریہ = (intptr_t)src->ڈیٹا[1];
    اگر (اشاریہ >= چوکھٹے_priv->nb_mapped_چوکھٹے) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", اشاریہ, چوکھٹے_priv->nb_mapped_چوکھٹے);
        واپس AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           اشاریہ);

    desc = &چوکھٹے_priv->mapped_چوکھٹے[اشاریہ];

    cle = device_priv->cl_قطار_میں_ڈالو_Acquire_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        واپس AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        جاؤ fail;

    برائے (i = 0; i < desc->nb_planes; i++)
        dst->ڈیٹا[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    cle = device_priv->cl_قطار_میں_ڈالو_Release_D3_D11_Objects_KHR(
        چوکھٹے_priv->command_قطار, desc->nb_planes, desc->planes,
        0, تہی, &event);
    اگر (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ڈیٹا, 0, حجم(dst->ڈیٹا));
    واپس err;
}

ساکن صحیح opencl_چوکھٹے_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحیح flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *چوکھٹے_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحیح err, i, p, nb_planes;

    اگر (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        واپس AVERROR(EINVAL);
    }
    nb_planes = 2;

    اگر (src_fc->initial_pool_سائز == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        واپس AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        واپس AVERROR(EINVAL);

    چوکھٹے_priv->nb_mapped_چوکھٹے = src_fc->initial_pool_سائز;

    چوکھٹے_priv->mapped_چوکھٹے =
        av_calloc(چوکھٹے_priv->nb_mapped_چوکھٹے,
                  حجم(*چوکھٹے_priv->mapped_چوکھٹے));
    اگر (!چوکھٹے_priv->mapped_چوکھٹے)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        desc->nb_planes = nb_planes;
        برائے (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            اگر (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (غیرعلامتی صحیح)subresource, cle);
                err = AVERROR(EIO);
                جاؤ fail;
            }
        }
    }

    واپس 0;

fail:
    برائے (i = 0; i < چوکھٹے_priv->nb_mapped_چوکھٹے; i++) {
        AVOpenCLFrameDescriptor *desc = &چوکھٹے_priv->mapped_چوکھٹے[i];
        برائے (p = 0; p < desc->nb_planes; p++) {
            اگر (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&چوکھٹے_priv->mapped_چوکھٹے);
    چوکھٹے_priv->nb_mapped_چوکھٹے = 0;
    واپس err;
}

#اگر_ختم

#اگر HAVE_OPENCL_DRM_ARM

قسمتعریف ساخت DRMARMtoOpenCLMapping {
    صحیح nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    صحیح nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ساکن خالی opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    صحیح i;

    برائے (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    برائے (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ساکن صحیح opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = تہی;
    cl_mem_flags cl_flags;
    ثابت cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    صحیح err, i, j;

    desc = (ثابت AVDRMFrameDescriptor*)src->ڈیٹا[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        واپس AVERROR(EINVAL);

    mapping = av_mallocz(حجم(*mapping));
    اگر (!mapping)
        واپس AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    برائے (i = 0; i < desc->nb_objects; i++) {
        صحیح fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        اگر (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_حافظہ_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].سائز, &cle);
        اگر (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].سائز, cle);
            err = AVERROR(EIO);
            جاؤ fail;
        }
    }

    mapping->nb_planes = 0;
    برائے (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];

        برائے (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_بفر;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_بفر_region region;
            صحیح p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->چوڑائی, src_fc->اونچائی,
                                          &image_format, &image_desc);
            اگر (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                جاؤ fail;
            }

            region.origin = plane->انحراف;
            region.سائز   = image_desc.image_صف_pitch *
                            image_desc.image_اونچائی;

            plane_بفر =
                cl_Create_Sub_بفر(mapping->object_buffers[plane->object_اشاریہ],
                                  cl_flags,
                                  CL_بفر_CREATE_TYPE_REGION,
                                  &region, &cle);
            اگر (!plane_بفر) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                جاؤ fail;
            }

            image_desc.بفر = plane_بفر;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, تہی, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_بفر);

            اگر (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                جاؤ fail;
            }

            ++mapping->nb_planes;
        }
    }

    برائے (i = 0; i < mapping->nb_planes; i++)
        dst->ڈیٹا[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    برائے (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    برائے (i = 0; i < mapping->nb_objects; i++) {
        اگر (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->ڈیٹا, 0, حجم(dst->ڈیٹا));
    واپس err;
}

#اگر_ختم

#اگر HAVE_OPENCL_VIDEOTOOLBOX

ساکن خالی opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ساکن صحیح opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحیح flags)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref) src->ڈیٹا[3];
    IOSurfaceRef io_surface_ref = CVPixel_بفر_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = تہی;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    اگر (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        واپس AVERROR_EXTERNAL;
    }

    desc = av_mallocz(حجم(*desc));
    اگر (!desc)
        واپس AVERROR(ENOMEM);

    برائے (صحیح p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->چوڑائی, src->اونچائی,
                                      &image_format, &image_desc);
        اگر (err == AVERROR(ENOENT))
            توڑو;
        اگر (err < 0)
            جاؤ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        اگر (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            جاؤ fail;
        }
        desc->nb_planes++;
    }

    برائے (صحیح i = 0; i < desc->nb_planes; i++)
        dst->ڈیٹا[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    اگر (err < 0)
        جاؤ fail;

    dst->چوڑائی = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    واپس 0;

fail:
    برائے (صحیح i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    واپس err;
}

#اگر_ختم

ساکن صحیح opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ثابت AVFrame *src, صحیح flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    اگر (hwfc->sw_format != dst->format)
        واپس AVERROR(ENOSYS);
    واپس opencl_map_چوکھٹا(hwfc, dst, src, flags);
}

ساکن صحیح opencl_map_مقصد(AVHWFramesContext *hwfc, AVFrame *dst,
                         ثابت AVFrame *src, صحیح flags)
{
    av_غیر_مستعمل OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    انتخاب (src->format) {
#اگر HAVE_OPENCL_DRM_BEIGNET
    حالت AV_PIX_FMT_DRM_مفرد:
        اگر (priv->beignet_drm_mapping_usable)
            واپس opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VAAPI_BEIGNET
    حالت AV_PIX_FMT_VAAPI:
        اگر (priv->beignet_drm_mapping_usable)
            واپس opencl_map_from_vaapi(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالت AV_PIX_FMT_QSV:
    حالت AV_PIX_FMT_VAAPI:
        اگر (priv->qsv_mapping_usable)
            واپس opencl_map_from_qsv(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_DXVA2
    حالت AV_PIX_FMT_DXVA2_VLD:
        اگر (priv->dxva2_mapping_usable)
            واپس opencl_map_from_dxva2(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_D3D11
    حالت AV_PIX_FMT_D3D11:
        اگر (priv->d3d11_mapping_usable)
            واپس opencl_map_from_d3d11(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_PIX_FMT_DRM_مفرد:
        اگر (priv->drm_arm_mapping_usable)
            واپس opencl_map_from_drm_arm(hwfc, dst, src, flags);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_PIX_FMT_VIDEOTOOLBOX:
        واپس opencl_map_from_vt(hwfc, dst, src, flags);
#اگر_ختم
    }
    واپس AVERROR(ENOSYS);
}

ساکن صحیح opencl_چوکھٹے_derive_مقصد(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, صحیح flags)
{
    av_غیر_مستعمل OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    انتخاب (src_fc->device_ctx->type) {
#اگر HAVE_OPENCL_DRM_BEIGNET
    حالت AV_HWDEVICE_TYPE_DRM:
        اگر (!priv->beignet_drm_mapping_usable)
            واپس AVERROR(ENOSYS);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VAAPI_BEIGNET
    حالت AV_HWDEVICE_TYPE_VAAPI:
        اگر (!priv->beignet_drm_mapping_usable)
            واپس AVERROR(ENOSYS);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالت AV_HWDEVICE_TYPE_QSV:
    حالت AV_HWDEVICE_TYPE_VAAPI:
        اگر (!priv->qsv_mapping_usable)
            واپس AVERROR(ENOSYS);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        اگر (!priv->dxva2_mapping_usable)
            واپس AVERROR(ENOSYS);
        {
            صحیح err;
            err = opencl_چوکھٹے_derive_from_dxva2(dst_fc, src_fc, flags);
            اگر (err < 0)
                واپس err;
        }
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_D3D11
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        اگر (!priv->d3d11_mapping_usable)
            واپس AVERROR(ENOSYS);
        {
            صحیح err;
            err = opencl_چوکھٹے_derive_from_d3d11(dst_fc, src_fc, flags);
            اگر (err < 0)
                واپس err;
        }
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_HWDEVICE_TYPE_DRM:
        اگر (!priv->drm_arm_mapping_usable)
            واپس AVERROR(ENOSYS);
        توڑو;
#اگر_ختم
#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        توڑو;
#اگر_ختم
    طےشدہ:
        واپس AVERROR(ENOSYS);
    }
    واپس opencl_چوکھٹے_init_command_قطار(dst_fc);
}

ثابت HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_سائز      = حجم(OpenCLDeviceContext),
    .چوکھٹے_hwctx_سائز      = حجم(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .چوکھٹے_get_constraints = &opencl_چوکھٹے_get_constraints,
    .چوکھٹے_init            = &opencl_چوکھٹے_init,
    .چوکھٹے_uninit          = &opencl_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = &opencl_get_بفر,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_ڈیٹا_مقصد       = &opencl_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from     = &opencl_transfer_ڈیٹا_from,

    .map_from               = &opencl_map_from,
    .map_مقصد                 = &opencl_map_مقصد,
    .چوکھٹے_derive_مقصد       = &opencl_چوکھٹے_derive_مقصد,

    .pix_fmts = (ثابت شمار AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
