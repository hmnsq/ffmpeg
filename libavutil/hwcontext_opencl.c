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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CL_USE_DEPRECATED_OPENCL_1_2_APIS

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_opencl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"

#ਜੇ HAVE_OPENCL_VAAPI_BEIGNET
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <va/va.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <va/va_drmcommon.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_intel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vaapi.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_BEIGNET
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_intel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_drm.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ਜੇ CONFIG_LIBMFX
#ਅਨ੍ਤਰ੍ਭਾਵ <mfxstructures.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <va/va.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_va_api_media_sharing_intel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vaapi.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_dx9_media_sharing.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dxva2api.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_dxva2.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_d3d11.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_d3d11va.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM
#ਅਨ੍ਤਰ੍ਭਾਵ <CL/cl_ext.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <drm_fourcc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_drm.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VIDEOTOOLBOX
#ਅਨ੍ਤਰ੍ਭਾਵ <OpenCL/cl_gl_ext.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <VideoToolbox/VideoToolbox.h>
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
ਬਾਹਰੀ ਪੂਰਨ ff_qsv_get_surface_ਅਧਾਰ_handle(mfx_ਚੌਖਟਾ_Surface1 *surf,
                                          ਗਿਣਤੀ AVHWDeviceType ਅਧਾਰ_dev_typ,
                                          ਖਾਲੀ **ਅਧਾਰ_handle);
#ਜੇ_ਅੰਤ


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ OpenCLDeviceContext {
    /**
     * The public AVOpenCLDeviceContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLDeviceContext p;

    // Default command queue to use for transfer/mapping operations on
    // the device.  If the user supplies one, this is a reference to it.
    // Otherwise, it is newly-created.
    cl_command_ਕਤਾਰ command_ਕਤਾਰ;

    // The platform the context exists on.  This is needed to query and
    // retrieve extension functions.
    cl_platform_id platform_id;

    // Platform/device-specific functions.
#ਜੇ HAVE_OPENCL_DRM_BEIGNET
    ਪੂਰਨ beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ਪੂਰਨ qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_VA_APIMedia_Surfaces_INTEL;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2
    ਪੂਰਨ dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_DX9_Media_Surfaces_KHR;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_DX9_Media_Surfaces_KHR_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_DX9_Media_Surfaces_KHR;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11
    ਪੂਰਨ d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_D3_D11_Objects_KHR_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_D3_D11_Objects_KHR;
    cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_D3_D11_Objects_KHR_fn
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_D3_D11_Objects_KHR;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM
    ਪੂਰਨ drm_arm_mapping_usable;
#ਜੇ_ਅੰਤ
} OpenCLDeviceContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_ਕਤਾਰ command_ਕਤਾਰ;

#ਜੇ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    ਪੂਰਨ                   nb_mapped_ਚੌਖਟੇ;
    AVOpenCLFrameDescriptor *mapped_ਚੌਖਟੇ;
#ਜੇ_ਅੰਤ
} OpenCLFramesContext;


ਸਥਿਰ ਖਾਲੀ CL_CALLBACK opencl_error_callback(ਅਚਲ ਅੱਖਰ *errinfo,
                                              ਅਚਲ ਖਾਲੀ *ਨਿੱਜੀ_info,
                                              size_t cb,
                                              ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    AVHWDeviceContext *ctx = user_ਅੰਕੜੇ;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ਸਥਿਰ ਖਾਲੀ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ਸਥਿਰ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_ਸੰਸਕਰਣ    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ਸਥਿਰ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_ਸੰਸਕਰਣ      },
    { "device_version",      CL_DEVICE_ਸੰਸਕਰਣ      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ਸਥਿਰ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ਸਥਿਰ ਅੱਖਰ *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info ਕੁੰਜੀ)
{
    ਅੱਖਰ *str;
    size_t ਮਾਪ;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, ਕੁੰਜੀ, 0, ਨਿਰਾ, &ਮਾਪ);
    ਜੇ (cle != CL_SUCCESS)
        ਵਾਪਸ ਨਿਰਾ;
    str = av_malloc(ਮਾਪ);
    ਜੇ (!str)
        ਵਾਪਸ ਨਿਰਾ;
    cle = clGetPlatformInfo(platform_id, ਕੁੰਜੀ, ਮਾਪ, str, &ਮਾਪ);
    ਜੇ (cle != CL_SUCCESS) {
        av_free(str);
        ਵਾਪਸ ਨਿਰਾ;
    }
    av_assert0(ਲੜੀ_ਲੰਬਾਈ(str) + 1 == ਮਾਪ);
    ਵਾਪਸ str;
}

ਸਥਿਰ ਅੱਖਰ *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info ਕੁੰਜੀ)
{
    ਅੱਖਰ *str;
    size_t ਮਾਪ;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, ਕੁੰਜੀ, 0, ਨਿਰਾ, &ਮਾਪ);
    ਜੇ (cle != CL_SUCCESS)
        ਵਾਪਸ ਨਿਰਾ;
    str = av_malloc(ਮਾਪ);
    ਜੇ (!str)
        ਵਾਪਸ ਨਿਰਾ;
    cle = clGetDeviceInfo(device_id, ਕੁੰਜੀ, ਮਾਪ, str, &ਮਾਪ);
    ਜੇ (cle != CL_SUCCESS) {
        av_free(str);
        ਵਾਪਸ ਨਿਰਾ;
    }
    av_assert0(ਲੜੀ_ਲੰਬਾਈ(str) + 1== ਮਾਪ);
    ਵਾਪਸ str;
}

ਸਥਿਰ ਪੂਰਨ opencl_check_platform_extension(cl_platform_id platform_id,
                                           ਅਚਲ ਅੱਖਰ *name)
{
    ਅੱਖਰ *str;
    ਪੂਰਨ ਮਿਲਿਆ = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ਜੇ (str && ਲੜੀ_ਖੋਜ(str, name))
        ਮਿਲਿਆ = 1;
    av_free(str);
    ਵਾਪਸ ਮਿਲਿਆ;
}

ਸਥਿਰ ਪੂਰਨ opencl_check_device_extension(cl_device_id device_id,
                                         ਅਚਲ ਅੱਖਰ *name)
{
    ਅੱਖਰ *str;
    ਪੂਰਨ ਮਿਲਿਆ = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ਜੇ (str && ਲੜੀ_ਖੋਜ(str, name))
        ਮਿਲਿਆ = 1;
    av_free(str);
    ਵਾਪਸ ਮਿਲਿਆ;
}

av_ਅਣਵਰਤਿਆ ਸਥਿਰ ਪੂਰਨ opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ਅਚਲ ਅੱਖਰ *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ਜੇ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ਵਾਪਸ 1;
    }

    ਜੇ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ਵਾਪਸ 1;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      ਖਾਲੀ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ਨਿਰਾ, nb_platforms);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ਵਾਪਸ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, ਆਕਾਰ(**platforms));
    ਜੇ (!*platforms)
        ਵਾਪਸ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ਵਾਪਸ AVERROR(ENODEV);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ਅਚਲ ਅੱਖਰ *platform_name,
                                  ਖਾਲੀ *context)
{
    AVDictionary *opts = context;
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *param;
    ਅੱਖਰ *str;
    ਪੂਰਨ i, ret = 0;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].ਕੁੰਜੀ,
                            ਨਿਰਾ, 0);
        ਜੇ (!param)
            ਜਾਰੀ;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ਜੇ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].ਕੁੰਜੀ, platform_name);
            ਵਾਪਸ AVERROR_UNKNOWN;
        }
        ਜੇ (!av_stristr(str, param->ਮੁੱਲ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ਕੁੰਜੀ, str);
            ret = 1;
        }
        av_free(str);
    }

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ਅਚਲ ਅੱਖਰ *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    ਖਾਲੀ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ਨਿਰਾ, nb_devices);
    ਜੇ (cle == CL_DEVICE_NOT_ਮਿਲਿਆ) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ਵਾਪਸ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, ਆਕਾਰ(**devices));
    ਜੇ (!*devices)
        ਵਾਪਸ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ਵਾਪਸ AVERROR(ENODEV);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ਅਚਲ ਅੱਖਰ *device_name,
                                ਖਾਲੀ *context)
{
    AVDictionary *opts = context;
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *param;
    ਅੱਖਰ *str;
    ਪੂਰਨ i, ret = 0;

    param = av_dict_get(opts, "device_type", ਨਿਰਾ, 0);
    ਜੇ (param) {
        cl_device_type ਮੇਲ_type = 0, device_type;
        cl_int cle;

        ਲਈ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ਜੇ (!strcmp(opencl_device_types[i].ਕੁੰਜੀ, param->ਮੁੱਲ)) {
                ਮੇਲ_type = opencl_device_types[i].type;
                ਰੋਕੋ;
            }
        }
        ਜੇ (!ਮੇਲ_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->ਮੁੱਲ);
            ਵਾਪਸ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              ਆਕਾਰ(device_type), &device_type, ਨਿਰਾ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ਵਾਪਸ AVERROR_UNKNOWN;
        }

        ਜੇ (!(device_type & ਮੇਲ_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ਵਾਪਸ 1;
        }
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].ਕੁੰਜੀ,
                            ਨਿਰਾ, 0);
        ਜੇ (!param)
            ਜਾਰੀ;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ਜੇ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].ਕੁੰਜੀ, device_name);
            ਵਾਪਸ AVERROR_UNKNOWN;
        }
        ਜੇ (!av_stristr(str, param->ਮੁੱਲ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ਕੁੰਜੀ, str);
            ret = 1;
        }
        av_free(str);
    }

    ਵਾਪਸ ret;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ OpenCLDeviceSelector {
    ਪੂਰਨ platform_ਸੂਚਕਾਂਕ;
    ਪੂਰਨ device_ਸੂਚਕਾਂਕ;
    ਖਾਲੀ *context;
    ਪੂਰਨ (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               ਖਾਲੀ *context);
    ਪੂਰਨ (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ਅਚਲ ਅੱਖਰ *platform_name,
                               ਖਾਲੀ *context);
    ਪੂਰਨ (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ਅਚਲ ਅੱਖਰ *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               ਖਾਲੀ *context);
    ਪੂਰਨ (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ਅਚਲ ਅੱਖਰ *device_name,
                               ਖਾਲੀ *context);
} OpenCLDeviceSelector;

ਸਥਿਰ ਪੂਰਨ opencl_device_create_ਅੰਦਰੂਨੀ(AVHWDeviceContext *hwdev,
                                         ਅਚਲ OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ਨਿਰਾ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ਨਿਰਾ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    ਅੱਖਰ *platform_name_src = ਨਿਰਾ,
         *device_name_src   = ਨਿਰਾ;
    ਪੂਰਨ err, ਮਿਲਿਆ, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ਜੇ (err)
        ਵਾਪਸ err;

    ਮਿਲਿਆ = 0;
    ਲਈ (p = 0; p < nb_platforms; p++) {
        ਅਚਲ ਅੱਖਰ *platform_name;

        ਜੇ (selector->platform_ਸੂਚਕਾਂਕ >= 0 &&
            selector->platform_ਸੂਚਕਾਂਕ != p)
            ਜਾਰੀ;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ਜੇ (platform_name_src)
            platform_name = platform_name_src;
        ਨਹੀਂਤਾਂ
            platform_name = "Unknown Platform";

        ਜੇ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ਜੇ (err < 0)
                ਜਾਓ fail;
            ਜੇ (err > 0)
                ਜਾਰੀ;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ਜੇ (err < 0)
            ਜਾਰੀ;

        ਲਈ (d = 0; d < nb_devices; d++) {
            ਅਚਲ ਅੱਖਰ *device_name;

            ਜੇ (selector->device_ਸੂਚਕਾਂਕ >= 0 &&
                selector->device_ਸੂਚਕਾਂਕ != d)
                ਜਾਰੀ;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ਜੇ (device_name_src)
                device_name = device_name_src;
            ਨਹੀਂਤਾਂ
                device_name = "Unknown Device";

            ਜੇ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ਜੇ (err < 0)
                    ਜਾਓ fail;
                ਜੇ (err > 0)
                    ਜਾਰੀ;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++ਮਿਲਿਆ;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ਜੇ (ਮਿਲਿਆ == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        ਜਾਓ fail;
    }
    ਜੇ (ਮਿਲਿਆ > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        ਜਾਓ fail;
    }

    ਜੇ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ਜੇ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        ਜਾਓ fail;
    }

    hwdev->ਮੁਕਤ = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ opencl_device_create(AVHWDeviceContext *hwdev, ਅਚਲ ਅੱਖਰ *device,
                                AVDictionary *opts, ਪੂਰਨ flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ਜੇ (device && device[0]) {
        // Match one or both indices for platform and device.
        ਪੂਰਨ d = -1, p = -1, ret;
        ਜੇ (device[0] == '.')
            ret = ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ(device, ".%d", &d);
        ਨਹੀਂਤਾਂ
            ret = ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ(device, "%d.%d", &p, &d);
        ਜੇ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        selector.platform_ਸੂਚਕਾਂਕ = p;
        selector.device_ਸੂਚਕਾਂਕ   = d;
    } ਨਹੀਂਤਾਂ {
        selector.platform_ਸੂਚਕਾਂਕ = -1;
        selector.device_ਸੂਚਕਾਂਕ   = -1;
    }

    ਵਾਪਸ opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, ਨਿਰਾ);
}

ਸਥਿਰ ਪੂਰਨ opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ਜੇ (hwctx->command_ਕਤਾਰ) {
        cle = cl_Retain_Command_ਕਤਾਰ(hwctx->command_ਕਤਾਰ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ਵਾਪਸ AVERROR(EIO);
        }
        priv->command_ਕਤਾਰ = hwctx->command_ਕਤਾਰ;
    } ਨਹੀਂਤਾਂ {
        priv->command_ਕਤਾਰ = cl_Create_Command_ਕਤਾਰ(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ਜੇ (!priv->command_ਕਤਾਰ) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ਵਾਪਸ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          ਆਕਾਰ(priv->platform_id), &priv->platform_id,
                          ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ਵਾਪਸ AVERROR(EIO);
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CL_FUNC(name, desc) ਕਰੋ {                                \
        ਜੇ (fail)                                               \
            ਰੋਕੋ;                                              \
        priv->name = cl_Get_Extension_Function_ਪਤਾ_For_Platform(  \
            priv->platform_id, #name);                          \
        ਜੇ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } ਨਹੀਂਤਾਂ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ਜਦੋਂ (0)

#ਜੇ HAVE_OPENCL_DRM_BEIGNET
    {
        ਪੂਰਨ fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ਜੇ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } ਨਹੀਂਤਾਂ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_ਮਾਪ;
        cl_context_properties *props = ਨਿਰਾ;
        VADisplay va_display;
        ਅਚਲ ਅੱਖਰ *va_ext = "cl_intel_va_api_media_sharing";
        ਪੂਰਨ i, fail = 0;

        ਜੇ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            ਜਾਓ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ਨਿਰਾ, &props_ਮਾਪ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ਜਾਓ no_qsv;
        }
        ਜੇ (props_ਮਾਪ == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ਜਾਓ no_qsv;
        }

        props = av_malloc(props_ਮਾਪ);
        ਜੇ (!props)
            ਵਾਪਸ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_ਮਾਪ, props, ਨਿਰਾ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ਜਾਓ no_qsv;
        }

        va_display = ਨਿਰਾ;
        ਲਈ (i = 0; i < (props_ਮਾਪ / ਆਕਾਰ(*props) - 1); i++) {
            ਜੇ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ਰੋਕੋ;
            }
        }
        ਜੇ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ਜਾਓ no_qsv;
        }
        ਜੇ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ਜਾਓ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        ਜੇ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } ਨਹੀਂਤਾਂ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2
    {
        ਪੂਰਨ fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        ਜੇ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } ਨਹੀਂਤਾਂ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11
    {
        ਅਚਲ ਅੱਖਰ *d3d11_ext = "cl_khr_d3d11_sharing";
        ਅਚਲ ਅੱਖਰ *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        ਪੂਰਨ fail = 0;

        ਜੇ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } ਨਹੀਂਤਾਂ ਜੇ (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        ਜੇ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } ਨਹੀਂਤਾਂ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM
    {
        ਅਚਲ ਅੱਖਰ *drm_arm_ext = "cl_arm_import_memory";
        ਅਚਲ ਅੱਖਰ *image_ext   = "cl_khr_image2d_from_buffer";
        ਪੂਰਨ fail = 0;

        ਜੇ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ਜੇ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ਜੇ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } ਨਹੀਂਤਾਂ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CL_FUNC

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ਜੇ (priv->command_ਕਤਾਰ) {
        cle = cl_Release_Command_ਕਤਾਰ(priv->command_ਕਤਾਰ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_ਕਤਾਰ = ਨਿਰਾ;
    }
}

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
ਸਥਿਰ ਪੂਰਨ opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ਅਚਲ ਅੱਖਰ *platform_name,
                                                    ਖਾਲੀ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ਜੇ (!cl_Get_Extension_Function_ਪਤਾ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ਵਾਪਸ 1;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ 0;
    }
}

ਸਥਿਰ ਪੂਰਨ opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ਅਚਲ ਅੱਖਰ *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      ਖਾਲੀ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        cl_Get_Extension_Function_ਪਤਾ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ਜੇ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ਨਿਰਾ, nb_devices);
    ਜੇ (cle == CL_DEVICE_NOT_ਮਿਲਿਆ) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ਆਕਾਰ(**devices));
    ਜੇ (!*devices)
        ਵਾਪਸ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ਅਚਲ ਅੱਖਰ *device_name,
                                                  ਖਾਲੀ *context)
{
    ਅਚਲ ਅੱਖਰ *va_ext = "cl_intel_va_api_media_sharing";

    ਜੇ (opencl_check_device_extension(device_id, va_ext)) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ਵਾਪਸ 1;
    }
}
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2
ਸਥਿਰ ਪੂਰਨ opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ਅਚਲ ਅੱਖਰ *platform_name,
                                        ਖਾਲੀ *context)
{
    ਅਚਲ ਅੱਖਰ *dx9_ext = "cl_khr_dx9_media_sharing";

    ਜੇ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ਵਾਪਸ 1;
    }
}

ਸਥਿਰ ਪੂਰਨ opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ਅਚਲ ਅੱਖਰ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ਖਾਲੀ *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        cl_Get_Extension_Function_ਪਤਾ_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ਜੇ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ਖਾਲੀ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ਨਿਰਾ, nb_devices);
    ਜੇ (cle == CL_DEVICE_NOT_ਮਿਲਿਆ) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ਆਕਾਰ(**devices));
    ਜੇ (!*devices)
        ਵਾਪਸ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ਖਾਲੀ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11
ਸਥਿਰ ਪੂਰਨ opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ਅਚਲ ਅੱਖਰ *platform_name,
                                        ਖਾਲੀ *context)
{
    ਅਚਲ ਅੱਖਰ *d3d11_ext = "cl_khr_d3d11_sharing";

    ਜੇ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ਵਾਪਸ 1;
    }
}

ਸਥਿਰ ਪੂਰਨ opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ਅਚਲ ਅੱਖਰ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ਖਾਲੀ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        cl_Get_Extension_Function_ਪਤਾ_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ਜੇ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ਨਿਰਾ, nb_devices);
    ਜੇ (cle == CL_DEVICE_NOT_ਮਿਲਿਆ) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ਆਕਾਰ(**devices));
    ਜੇ (!*devices)
        ਵਾਪਸ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ਸਥਿਰ ਪੂਰਨ opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ਅਚਲ ਅੱਖਰ *device_name,
                                    ਖਾਲੀ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          ਆਕਾਰ(device_type), &device_type, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }
    ਜੇ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ਵਾਪਸ 1;
    }

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM
ਸਥਿਰ ਪੂਰਨ opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ਅਚਲ ਅੱਖਰ *platform_name,
                                          ਖਾਲੀ *context)
{
    ਅਚਲ ਅੱਖਰ *drm_arm_ext = "cl_arm_import_memory";

    ਜੇ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ਵਾਪਸ 1;
    }
}

ਸਥਿਰ ਪੂਰਨ opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ਅਚਲ ਅੱਖਰ *device_name,
                                        ਖਾਲੀ *context)
{
    ਅਚਲ ਅੱਖਰ *drm_arm_ext = "cl_arm_import_memory";

    ਜੇ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ਵਾਪਸ 1;
    }
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                ਪੂਰਨ flags)
{
    ਪੂਰਨ err;
    ਚੋਣ (src_ctx->type) {

#ਜੇ HAVE_OPENCL_DRM_BEIGNET
    ਹਾਲਤ AV_HWDEVICE_TYPE_DRM:
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ਨਿਰਾ;

            err = av_dict_ਸੈੱਟ(&selector_opts, "platform_vendor", "Intel", 0);
            ਜੇ (err >= 0)
                err = av_dict_ਸੈੱਟ(&selector_opts, "platform_version", "beignet", 0);
            ਜੇ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_ਸੂਚਕਾਂਕ      = -1,
                    .device_ਸੂਚਕਾਂਕ        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ਨਿਰਾ,
                };
                err = opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, ਨਿਰਾ);
            }
            av_dict_free(&selector_opts);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
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
                .platform_ਸੂਚਕਾਂਕ      = -1,
                .device_ਸੂਚਕਾਂਕ        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, props);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ਜੇ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)hr);
                err = AVERROR_UNKNOWN;
                ਰੋਕੋ;
            }

            hr = IDirect3_DDevice_Manager9_ਤਾਲਾ_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ਜੇ (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_ਸੂਚਕਾਂਕ      = -1,
                    .device_ਸੂਚਕਾਂਕ        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } ਨਹੀਂਤਾਂ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
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
                .platform_ਸੂਚਕਾਂਕ      = -1,
                .device_ਸੂਚਕਾਂਕ        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, props);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM
    ਹਾਲਤ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_ਸੂਚਕਾਂਕ      = -1,
                .device_ਸੂਚਕਾਂਕ        = -1,
                .context             = ਨਿਰਾ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_ਅੰਦਰੂਨੀ(hwdev, &selector, ਨਿਰਾ);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VIDEOTOOLBOX
    ਹਾਲਤ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ਨਿਰਾ, ਨਿਰਾ, 0);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

    ਮੂਲ:
        err = AVERROR(ENOSYS);
        ਰੋਕੋ;
    }

    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ opencl_get_plane_format(ਗਿਣਤੀ AVPixelFormat pixfmt,
                                   ਪੂਰਨ plane, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ਅਚਲ AVPixFmtDescriptor *desc;
    ਅਚਲ AVComponentDescriptor *comp;
    ਪੂਰਨ channels = 0, ਕ੍ਰਮ = 0, ਡੂੰਘਾਈ = 0, ਕਦਮ = 0;
    ਪੂਰਨ wsub, hsub, alpha;
    ਪੂਰਨ c;

    ਜੇ (plane >= AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ)
        ਵਾਪਸ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ਜੇ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ਵਾਪਸ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ਜੇ (ਚੌੜਾਈ & wsub - 1 || ਉਚਾਈ & hsub - 1)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ਜੇ (comp->plane != plane)
            ਜਾਰੀ;
        // The step size must be a power of two.
        ਜੇ (comp->ਕਦਮ != 1 && comp->ਕਦਮ != 2 &&
            comp->ਕਦਮ != 4 && comp->ਕਦਮ != 8)
            ਵਾਪਸ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ਜੇ (comp->ਖਿਸਕਾਓ + comp->ਡੂੰਘਾਈ != 8 &&
            comp->ਖਿਸਕਾਓ + comp->ਡੂੰਘਾਈ != 16 &&
            comp->ਖਿਸਕਾਓ + comp->ਡੂੰਘਾਈ != 32)
            ਵਾਪਸ AVERROR(EINVAL);
        // The depth must not vary between components.
        ਜੇ (ਡੂੰਘਾਈ && comp->ਡੂੰਘਾਈ != ਡੂੰਘਾਈ)
            ਵਾਪਸ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ਜੇ (comp->ਡੂੰਘਾਈ > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ਵਾਪਸ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ਜੇ (ਕਦਮ && comp->ਕਦਮ != ਕਦਮ)
            ਵਾਪਸ AVERROR(EINVAL);

        ਡੂੰਘਾਈ = comp->ਡੂੰਘਾਈ;
        ਕ੍ਰਮ = ਕ੍ਰਮ * 10 + comp->ਵਿੱਥ / ((ਡੂੰਘਾਈ + 7) / 8) + 1;
        ਕਦਮ  = comp->ਕਦਮ;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ਜੇ (channels == 0)
        ਵਾਪਸ AVERROR(ENOENT);

    memset(image_format, 0, ਆਕਾਰ(*image_format));
    memset(image_desc,   0, ਆਕਾਰ(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ਜੇ (plane == 0 || alpha) {
        image_desc->image_ਚੌੜਾਈ     = ਚੌੜਾਈ;
        image_desc->image_ਉਚਾਈ    = ਉਚਾਈ;
        image_desc->image_ਪੰਕਤੀ_pitch = ਕਦਮ * ਚੌੜਾਈ;
    } ਨਹੀਂਤਾਂ {
        image_desc->image_ਚੌੜਾਈ     = ਚੌੜਾਈ  / wsub;
        image_desc->image_ਉਚਾਈ    = ਉਚਾਈ / hsub;
        image_desc->image_ਪੰਕਤੀ_pitch = ਕਦਮ * ਚੌੜਾਈ / wsub;
    }

    ਜੇ (ਡੂੰਘਾਈ <= 8) {
        image_format->image_channel_ਅੰਕੜੇ_type = CL_UNORM_INT8;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਡੂੰਘਾਈ <= 16)
            image_format->image_channel_ਅੰਕੜੇ_type = CL_UNORM_INT16;
        ਨਹੀਂਤਾਂ ਜੇ (ਡੂੰਘਾਈ == 32)
            image_format->image_channel_ਅੰਕੜੇ_type = CL_FLOAT;
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(EINVAL);
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_ਕ੍ਰਮ(ਕ੍ਰਮ, type) \
    ਹਾਲਤ ਕ੍ਰਮ: image_format->image_channel_ਕ੍ਰਮ = type; ਰੋਕੋ;
    ਚੋਣ (ਕ੍ਰਮ) {
        CHANNEL_ਕ੍ਰਮ(1,    CL_R);
        CHANNEL_ਕ੍ਰਮ(12,   CL_RG);
        CHANNEL_ਕ੍ਰਮ(1234, CL_RGBA);
        CHANNEL_ਕ੍ਰਮ(2341, CL_ARGB);
        CHANNEL_ਕ੍ਰਮ(3214, CL_BGRA);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CL_ABGR
        CHANNEL_ਕ੍ਰਮ(4321, CL_ABGR);
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHANNEL_ਕ੍ਰਮ

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *hwdev,
                                         ਅਚਲ ਖਾਲੀ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ਨਿਰਾ;
    cl_int cle;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
    ਪੂਰਨ err, pix_fmts_ਮਿਲਿਆ;
    size_t max_ਚੌੜਾਈ, max_ਉਚਾਈ;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_ਚੌੜਾਈ,
                          ਆਕਾਰ(max_ਚੌੜਾਈ), &max_ਚੌੜਾਈ, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } ਨਹੀਂਤਾਂ {
        constraints->max_ਚੌੜਾਈ = max_ਚੌੜਾਈ;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_ਉਚਾਈ,
                          ਆਕਾਰ(max_ਉਚਾਈ), &max_ਉਚਾਈ, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } ਨਹੀਂਤਾਂ {
        constraints->max_ਉਚਾਈ = max_ਉਚਾਈ;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_ਚੌੜਾਈ, constraints->max_ਉਚਾਈ);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ਨਿਰਾ, &nb_image_formats);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }
    ਜੇ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, ਆਕਾਰ(*image_formats));
    ਜੇ (!image_formats) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ਨਿਰਾ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    pix_fmts_ਮਿਲਿਆ = 0;
    ਲਈ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        ਪੂਰਨ plane, i;

        ਲਈ (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ਜੇ (err < 0)
                ਰੋਕੋ;

            ਲਈ (i = 0; i < nb_image_formats; i++) {
                ਜੇ (image_formats[i].image_channel_ਕ੍ਰਮ ==
                    image_format.image_channel_ਕ੍ਰਮ &&
                    image_formats[i].image_channel_ਅੰਕੜੇ_type ==
                    image_format.image_channel_ਅੰਕੜੇ_type)
                    ਰੋਕੋ;
            }
            ਜੇ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ਰੋਕੋ;
            }
        }
        ਜੇ (err != AVERROR(ENOENT))
            ਜਾਰੀ;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_ਮਿਲਿਆ + 2,
                                ਆਕਾਰ(*constraints->valid_sw_formats));
        ਜੇ (err < 0)
            ਜਾਓ fail;
        constraints->valid_sw_formats[pix_fmts_ਮਿਲਿਆ] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_ਮਿਲਿਆ + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_ਮਿਲਿਆ;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;

fail:
    av_freep(&image_formats);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਖਾਲੀ opencl_pool_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)ਅੰਕੜੇ;
    cl_int cle;
    ਪੂਰਨ p;

    ਲਈ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ਸਥਿਰ AVBufferRef *opencl_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    ਪੂਰਨ err, p;
    AVBufferRef *ref;

    desc = av_mallocz(ਆਕਾਰ(*desc));
    ਜੇ (!desc)
        ਵਾਪਸ ਨਿਰਾ;

    ਲਈ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ,
                                      &image_format, &image_desc);
        ਜੇ (err == AVERROR(ENOENT))
            ਰੋਕੋ;
        ਜੇ (err < 0)
            ਜਾਓ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_ਪੰਕਤੀ_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ਨਿਰਾ, &cle);
        ਜੇ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            ਜਾਓ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_ਬਫਰ_create((uint8_t*)desc, ਆਕਾਰ(*desc),
                           &opencl_pool_free, hwfc, 0);
    ਜੇ (!ref)
        ਜਾਓ fail;

    ਵਾਪਸ ref;

fail:
    ਲਈ (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_init_command_ਕਤਾਰ(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_ਕਤਾਰ = hwctx->command_ਕਤਾਰ ? hwctx->command_ਕਤਾਰ
                                               : devpriv->command_ਕਤਾਰ;
    cle = cl_Retain_Command_ਕਤਾਰ(priv->command_ਕਤਾਰ);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        ਵਾਪਸ AVERROR(EIO);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_init(AVHWFramesContext *hwfc)
{
    ਜੇ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_ਅੰਦਰੂਨੀ =
            av_ਬਫਰ_pool_init2(ਆਕਾਰ(cl_mem), hwfc,
                                 &opencl_pool_alloc, ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(hwfc)->pool_ਅੰਦਰੂਨੀ)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਵਾਪਸ opencl_ਚੌਖਟੇ_init_command_ਕਤਾਰ(hwfc);
}

ਸਥਿਰ ਖਾਲੀ opencl_ਚੌਖਟੇ_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ਜੇ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    ਪੂਰਨ i, p;
    ਲਈ (i = 0; i < priv->nb_mapped_ਚੌਖਟੇ; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_ਚੌਖਟੇ[i];
        ਲਈ (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ਜੇ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_ਚੌਖਟੇ);
#ਜੇ_ਅੰਤ

    ਜੇ (priv->command_ਕਤਾਰ) {
        cle = cl_Release_Command_ਕਤਾਰ(priv->command_ਕਤਾਰ);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_ਕਤਾਰ = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ opencl_get_ਬਫਰ(AVHWFramesContext *hwfc, AVFrame *ਚੌਖਟਾ)
{
    AVOpenCLFrameDescriptor *desc;
    ਪੂਰਨ p;

    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(hwfc->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;

    ਲਈ (p = 0; p < desc->nb_planes; p++)
        ਚੌਖਟਾ->ਅੰਕੜੇ[p] = (uint8_t*)desc->planes[p];

    ਚੌਖਟਾ->format  = AV_PIX_FMT_OPENCL;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = hwfc->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = hwfc->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                       ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, ਪੂਰਨ nb_events)
{
    cl_int cle;
    ਪੂਰਨ i;

    cle = clWaitForEvents(nb_events, events);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ਵਾਪਸ AVERROR(EIO);
    }

    ਲਈ (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opencl_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ਅਚਲ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ err, p;

    ਜੇ (dst->format != hwfc->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ਚੌੜਾਈ, src->ਉਚਾਈ,
                                      &image_format, &image_desc);
        ਜੇ (err < 0) {
            ਜੇ (err == AVERROR(ENOENT))
                err = 0;
            ਰੋਕੋ;
        }

        ਜੇ (!dst->ਅੰਕੜੇ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ਰੋਕੋ;
        }

        region[0] = image_desc.image_ਚੌੜਾਈ;
        region[1] = image_desc.image_ਉਚਾਈ;
        region[2] = 1;

        cle = cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Read_Image(priv->command_ਕਤਾਰ,
                                 (cl_mem)src->ਅੰਕੜੇ[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->ਅੰਕੜੇ[p],
                                 0, ਨਿਰਾ, &events[p]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ਰੋਕੋ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ opencl_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ਅਚਲ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ err, p;

    ਜੇ (src->format != hwfc->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ਚੌੜਾਈ, src->ਉਚਾਈ,
                                      &image_format, &image_desc);
        ਜੇ (err < 0) {
            ਜੇ (err == AVERROR(ENOENT))
                err = 0;
            ਰੋਕੋ;
        }

        ਜੇ (!src->ਅੰਕੜੇ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ਰੋਕੋ;
        }

        region[0] = image_desc.image_ਚੌੜਾਈ;
        region[1] = image_desc.image_ਉਚਾਈ;
        region[2] = 1;

        cle = cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Write_Image(priv->command_ਕਤਾਰ,
                                  (cl_mem)dst->ਅੰਕੜੇ[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->ਅੰਕੜੇ[p],
                                  0, ਨਿਰਾ, &events[p]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ਰੋਕੋ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ਵਾਪਸ err;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    ਖਾਲੀ *ਪਤਾ[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
} OpenCLMapping;

ਸਥਿਰ ਖਾਲੀ opencl_unmap_ਚੌਖਟਾ(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ p, e;
    cl_int cle;

    ਲਈ (p = e = 0; p < FF_ARRAY_ELEMS(map->ਪਤਾ); p++) {
        ਜੇ (!map->ਪਤਾ[p])
            ਰੋਕੋ;

        cle = cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Unmap_Mem_Object(priv->command_ਕਤਾਰ,
                                      (cl_mem)hwmap->ਸਰੋਤ->ਅੰਕੜੇ[p],
                                      map->ਪਤਾ[p],
                                      0, ਨਿਰਾ, &events[e]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_ਚੌਖਟਾ(AVHWFramesContext *hwfc, AVFrame *dst,
                            ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t ਪੰਕਤੀ_pitch;
    cl_event events[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ਜੇ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } ਨਹੀਂਤਾਂ {
        map_flags = 0;
        ਜੇ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ਜੇ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(ਆਕਾਰ(*map));
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ਚੌੜਾਈ, src->ਉਚਾਈ,
                                      &image_format, &image_desc);
        ਜੇ (err == AVERROR(ENOENT))
            ਰੋਕੋ;
        ਜੇ (err < 0)
            ਜਾਓ fail;

        region[0] = image_desc.image_ਚੌੜਾਈ;
        region[1] = image_desc.image_ਉਚਾਈ;
        region[2] = 1;

        map->ਪਤਾ[p] =
            cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Map_Image(priv->command_ਕਤਾਰ,
                              (cl_mem)src->ਅੰਕੜੇ[p],
                              CL_FALSE, map_flags, origin, region,
                              &ਪੰਕਤੀ_pitch, ਨਿਰਾ, 0, ਨਿਰਾ,
                              &events[p], &cle);
        ਜੇ (!map->ਪਤਾ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ਜਾਓ fail;
        }

        dst->ਅੰਕੜੇ[p] = map->ਪਤਾ[p];
        dst->linesize[p] = ਪੰਕਤੀ_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->ਅੰਕੜੇ[p], dst->ਅੰਕੜੇ[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_ਚੌਖਟਾ, map);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    ਲਈ (p = 0; p < AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ; p++) {
        ਜੇ (!map->ਪਤਾ[p])
            ਰੋਕੋ;
        cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Unmap_Mem_Object(priv->command_ਕਤਾਰ,
                                (cl_mem)src->ਅੰਕੜੇ[p],
                                map->ਪਤਾ[p],
                                0, ਨਿਰਾ, &events[p]);
    }
    ਜੇ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ਵਾਪਸ err;
}

#ਜੇ HAVE_OPENCL_DRM_BEIGNET

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DRMBeignet_ਮੰਜ਼ਿਲ_Open_CLMapping {
    AVFrame              *drm_ਚੌਖਟਾ;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor ਚੌਖਟਾ;
} DRMBeignet_ਮੰਜ਼ਿਲ_Open_CLMapping;

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_ਮੰਜ਼ਿਲ_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < mapping->ਚੌਖਟਾ.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->ਚੌਖਟਾ.planes[i]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ਅਚਲ AVFrame *src,
                                       ਪੂਰਨ flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignet_ਮੰਜ਼ਿਲ_Open_CLMapping *mapping;
    ਅਚਲ AVDRMFrameDescriptor *desc;
    cl_int cle;
    ਪੂਰਨ err, i, j, p;

    desc = (ਅਚਲ AVDRMFrameDescriptor*)src->ਅੰਕੜੇ[0];

    mapping = av_mallocz(ਆਕਾਰ(*mapping));
    ਜੇ (!mapping)
        ਵਾਪਸ AVERROR(ENOMEM);

    p = 0;
    ਲਈ (i = 0; i < desc->nb_layers; i++) {
        ਅਚਲ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ਲਈ (j = 0; j < layer->nb_planes; j++) {
            ਅਚਲ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ਅਚਲ AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_ਸੂਚਕਾਂਕ];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .ਮਾਪ      = object->ਮਾਪ,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .ਵਿੱਥ    = plane->ਵਿੱਥ,
                .ਪੰਕਤੀ_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->ਚੌੜਾਈ, src->ਉਚਾਈ,
                                          &image_info.fmt,
                                          &image_desc);
            ਜੇ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                ਜਾਓ fail;
            }
            image_info.ਚੌੜਾਈ  = image_desc.image_ਚੌੜਾਈ;
            image_info.ਉਚਾਈ = image_desc.image_ਉਚਾਈ;

            mapping->ਚੌਖਟਾ.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ਜੇ (!mapping->ਚੌਖਟਾ.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                ਜਾਓ fail;
            }

            dst->ਅੰਕੜੇ[p] = (uint8_t*)mapping->ਚੌਖਟਾ.planes[p];
            mapping->ਚੌਖਟਾ.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    ਲਈ (p = 0; p < mapping->ਚੌਖਟਾ.nb_planes; p++) {
        ਜੇ (mapping->ਚੌਖਟਾ.planes[p])
            clReleaseMemObject(mapping->ਚੌਖਟਾ.planes[p]);
    }
    av_free(mapping);
    memset(dst->ਅੰਕੜੇ, 0, ਆਕਾਰ(dst->ਅੰਕੜੇ));
    ਵਾਪਸ err;
}

#ਜੇ HAVE_OPENCL_VAAPI_BEIGNET

ਸਥਿਰ ਪੂਰਨ opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ਅਚਲ AVFrame *src,
                                 ਪੂਰਨ flags)
{
    AVFrame *tmp;
    ਪੂਰਨ err;

    tmp = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ਅਭਾਜ;

    err = av_hwframe_map(tmp, src, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ਚੌਖਟਾ_free(&tmp);
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ /* HAVE_OPENCL_VAAPI_BEIGNET */
#ਜੇ_ਅੰਤ /* HAVE_OPENCL_DRM_BEIGNET */

ਸਥਿਰ ਸਤਰਅੰਦਰ cl_mem_flags opencl_mem_flags_for_mapping(ਪੂਰਨ map_flags)
{
    ਜੇ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ਵਾਪਸ CL_MEM_READ_WRITE;
    ਨਹੀਂਤਾਂ ਜੇ (map_flags & AV_HWFRAME_MAP_READ)
        ਵਾਪਸ CL_MEM_READ_ONLY;
    ਨਹੀਂਤਾਂ ਜੇ (map_flags & AV_HWFRAME_MAP_WRITE)
        ਵਾਪਸ CL_MEM_WRITE_ONLY;
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ 0;
}

#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    ਪੂਰਨ p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_VA_APIMedia_Surfaces_INTEL(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    ਲਈ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ਜੇ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    ਪੂਰਨ err, p;

#ਜੇ CONFIG_LIBMFX
    ਜੇ (src->format == AV_PIX_FMT_QSV) {
        ਖਾਲੀ *ਅਧਾਰ_handle;
        mfx_ਚੌਖਟਾ_Surface1 *mfx_surface = (mfx_ਚੌਖਟਾ_Surface1*)src->ਅੰਕੜੇ[3];
        err = ff_qsv_get_surface_ਅਧਾਰ_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &ਅਧਾਰ_handle);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
        va_surface = *(VASurfaceID *)ਅਧਾਰ_handle;
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->ਅੰਕੜੇ[3];
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ਜੇ (!cl_flags)
        ਵਾਪਸ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(ਆਕਾਰ(*desc));
    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    ਲਈ (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ਜੇ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            ਜਾਓ fail;
        }

        dst->ਅੰਕੜੇ[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_VA_APIMedia_Surfaces_INTEL(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        ਜਾਓ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    ਲਈ (p = 0; p < desc->nb_planes; p++)
        ਜੇ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->ਅੰਕੜੇ, 0, ਆਕਾਰ(dst->ਅੰਕੜੇ));
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DXVA2

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_DX9_Media_Surfaces_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ਵਾਪਸ;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVDXVA2_ਚੌਖਟੇ_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ਪੂਰਨ err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->ਅੰਕੜੇ[3]);

    ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ਜੇ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->ਅੰਕੜੇ[3])
            ਰੋਕੋ;
    }
    ਜੇ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[i];

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_DX9_Media_Surfaces_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ਵਾਪਸ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (i = 0; i < desc->nb_planes; i++)
        dst->ਅੰਕੜੇ[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_DX9_Media_Surfaces_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ਅੰਕੜੇ, 0, ਆਕਾਰ(dst->ਅੰਕੜੇ));
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ਪੂਰਨ flags)
{
    AVDXVA2_ਚੌਖਟੇ_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ਪੂਰਨ err, i, p, nb_planes;

    ਜੇ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ਜੇ (src_fc->initial_pool_ਮਾਪ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ਜੇ (!cl_flags)
        ਵਾਪਸ AVERROR(EINVAL);

    ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ = src_hwctx->nb_surfaces;

    ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ =
        av_calloc(ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ,
                  ਆਕਾਰ(*ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ));
    ਜੇ (!ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ; i++) {
        AVOpenCLFrameDescriptor *desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ਨਿਰਾ,
        };
        desc->nb_planes = nb_planes;
        ਲਈ (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ਜੇ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                ਜਾਓ fail;
            }
        }
    }

    ਵਾਪਸ 0;

fail:
    ਲਈ (i = 0; i < ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ; i++) {
        AVOpenCLFrameDescriptor *desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[i];
        ਲਈ (p = 0; p < desc->nb_planes; p++) {
            ਜੇ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ);
    ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ = 0;
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_D3D11

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_D3_D11_Objects_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ਪੂਰਨ err, ਸੂਚਕਾਂਕ, i;

    ਸੂਚਕਾਂਕ = (intptr_t)src->ਅੰਕੜੇ[1];
    ਜੇ (ਸੂਚਕਾਂਕ >= ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", ਸੂਚਕਾਂਕ, ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           ਸੂਚਕਾਂਕ);

    desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[ਸੂਚਕਾਂਕ];

    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Acquire_D3_D11_Objects_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ਵਾਪਸ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (i = 0; i < desc->nb_planes; i++)
        dst->ਅੰਕੜੇ[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    cle = device_priv->cl_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Release_D3_D11_Objects_KHR(
        ਚੌਖਟੇ_priv->command_ਕਤਾਰ, desc->nb_planes, desc->planes,
        0, ਨਿਰਾ, &event);
    ਜੇ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ਅੰਕੜੇ, 0, ਆਕਾਰ(dst->ਅੰਕੜੇ));
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ਪੂਰਨ flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *ਚੌਖਟੇ_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ਪੂਰਨ err, i, p, nb_planes;

    ਜੇ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ਜੇ (src_fc->initial_pool_ਮਾਪ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ਜੇ (!cl_flags)
        ਵਾਪਸ AVERROR(EINVAL);

    ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ = src_fc->initial_pool_ਮਾਪ;

    ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ =
        av_calloc(ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ,
                  ਆਕਾਰ(*ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ));
    ਜੇ (!ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ; i++) {
        AVOpenCLFrameDescriptor *desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[i];
        desc->nb_planes = nb_planes;
        ਲਈ (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ਜੇ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)subresource, cle);
                err = AVERROR(EIO);
                ਜਾਓ fail;
            }
        }
    }

    ਵਾਪਸ 0;

fail:
    ਲਈ (i = 0; i < ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ; i++) {
        AVOpenCLFrameDescriptor *desc = &ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ[i];
        ਲਈ (p = 0; p < desc->nb_planes; p++) {
            ਜੇ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&ਚੌਖਟੇ_priv->mapped_ਚੌਖਟੇ);
    ਚੌਖਟੇ_priv->nb_mapped_ਚੌਖਟੇ = 0;
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_DRM_ARM

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DRMARMtoOpenCLMapping {
    ਪੂਰਨ nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    ਪੂਰਨ nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    ਲਈ (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ਅਚਲ AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ਨਿਰਾ;
    cl_mem_flags cl_flags;
    ਅਚਲ cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    ਪੂਰਨ err, i, j;

    desc = (ਅਚਲ AVDRMFrameDescriptor*)src->ਅੰਕੜੇ[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ਜੇ (!cl_flags)
        ਵਾਪਸ AVERROR(EINVAL);

    mapping = av_mallocz(ਆਕਾਰ(*mapping));
    ਜੇ (!mapping)
        ਵਾਪਸ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    ਲਈ (i = 0; i < desc->nb_objects; i++) {
        ਪੂਰਨ fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ਜੇ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_ਸਮ੍ਰਿਤੀ_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].ਮਾਪ, &cle);
        ਜੇ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].ਮਾਪ, cle);
            err = AVERROR(EIO);
            ਜਾਓ fail;
        }
    }

    mapping->nb_planes = 0;
    ਲਈ (i = 0; i < desc->nb_layers; i++) {
        ਅਚਲ AVDRMLayerDescriptor *layer = &desc->layers[i];

        ਲਈ (j = 0; j < layer->nb_planes; j++) {
            ਅਚਲ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_ਬਫਰ;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_ਬਫਰ_region region;
            ਪੂਰਨ p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->ਚੌੜਾਈ, src_fc->ਉਚਾਈ,
                                          &image_format, &image_desc);
            ਜੇ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                ਜਾਓ fail;
            }

            region.origin = plane->ਵਿੱਥ;
            region.ਮਾਪ   = image_desc.image_ਪੰਕਤੀ_pitch *
                            image_desc.image_ਉਚਾਈ;

            plane_ਬਫਰ =
                cl_Create_Sub_ਬਫਰ(mapping->object_buffers[plane->object_ਸੂਚਕਾਂਕ],
                                  cl_flags,
                                  CL_ਬਫਰ_CREATE_TYPE_REGION,
                                  &region, &cle);
            ਜੇ (!plane_ਬਫਰ) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ਜਾਓ fail;
            }

            image_desc.ਬਫਰ = plane_ਬਫਰ;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ਨਿਰਾ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_ਬਫਰ);

            ਜੇ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ਜਾਓ fail;
            }

            ++mapping->nb_planes;
        }
    }

    ਲਈ (i = 0; i < mapping->nb_planes; i++)
        dst->ਅੰਕੜੇ[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    ਲਈ (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    ਲਈ (i = 0; i < mapping->nb_objects; i++) {
        ਜੇ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->ਅੰਕੜੇ, 0, ਆਕਾਰ(dst->ਅੰਕੜੇ));
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ

#ਜੇ HAVE_OPENCL_VIDEOTOOLBOX

ਸਥਿਰ ਖਾਲੀ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    CVPixel_ਬਫਰ_Ref pixbuf = (CVPixel_ਬਫਰ_Ref) src->ਅੰਕੜੇ[3];
    IOSurfaceRef io_surface_ref = CVPixel_ਬਫਰ_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ਨਿਰਾ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ਜੇ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(ਆਕਾਰ(*desc));
    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (ਪੂਰਨ p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->ਚੌੜਾਈ, src->ਉਚਾਈ,
                                      &image_format, &image_desc);
        ਜੇ (err == AVERROR(ENOENT))
            ਰੋਕੋ;
        ਜੇ (err < 0)
            ਜਾਓ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ਜੇ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            ਜਾਓ fail;
        }
        desc->nb_planes++;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_planes; i++)
        dst->ਅੰਕੜੇ[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    ਵਾਪਸ 0;

fail:
    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ਵਾਪਸ err;
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ਜੇ (hwfc->sw_format != dst->format)
        ਵਾਪਸ AVERROR(ENOSYS);
    ਵਾਪਸ opencl_map_ਚੌਖਟਾ(hwfc, dst, src, flags);
}

ਸਥਿਰ ਪੂਰਨ opencl_map_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc, AVFrame *dst,
                         ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    av_ਅਣਵਰਤਿਆ OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    ਚੋਣ (src->format) {
#ਜੇ HAVE_OPENCL_DRM_BEIGNET
    ਹਾਲਤ AV_PIX_FMT_DRM_ਅਭਾਜ:
        ਜੇ (priv->beignet_drm_mapping_usable)
            ਵਾਪਸ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VAAPI_BEIGNET
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
        ਜੇ (priv->beignet_drm_mapping_usable)
            ਵਾਪਸ opencl_map_from_vaapi(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ਹਾਲਤ AV_PIX_FMT_QSV:
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
        ਜੇ (priv->qsv_mapping_usable)
            ਵਾਪਸ opencl_map_from_qsv(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_DXVA2
    ਹਾਲਤ AV_PIX_FMT_DXVA2_VLD:
        ਜੇ (priv->dxva2_mapping_usable)
            ਵਾਪਸ opencl_map_from_dxva2(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_D3D11
    ਹਾਲਤ AV_PIX_FMT_D3D11:
        ਜੇ (priv->d3d11_mapping_usable)
            ਵਾਪਸ opencl_map_from_d3d11(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_DRM_ARM
    ਹਾਲਤ AV_PIX_FMT_DRM_ਅਭਾਜ:
        ਜੇ (priv->drm_arm_mapping_usable)
            ਵਾਪਸ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VIDEOTOOLBOX
    ਹਾਲਤ AV_PIX_FMT_VIDEOTOOLBOX:
        ਵਾਪਸ opencl_map_from_vt(hwfc, dst, src, flags);
#ਜੇ_ਅੰਤ
    }
    ਵਾਪਸ AVERROR(ENOSYS);
}

ਸਥਿਰ ਪੂਰਨ opencl_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ਪੂਰਨ flags)
{
    av_ਅਣਵਰਤਿਆ OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    ਚੋਣ (src_fc->device_ctx->type) {
#ਜੇ HAVE_OPENCL_DRM_BEIGNET
    ਹਾਲਤ AV_HWDEVICE_TYPE_DRM:
        ਜੇ (!priv->beignet_drm_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VAAPI_BEIGNET
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        ਜੇ (!priv->beignet_drm_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ਹਾਲਤ AV_HWDEVICE_TYPE_QSV:
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        ਜੇ (!priv->qsv_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        ਜੇ (!priv->dxva2_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        {
            ਪੂਰਨ err;
            err = opencl_ਚੌਖਟੇ_derive_from_dxva2(dst_fc, src_fc, flags);
            ਜੇ (err < 0)
                ਵਾਪਸ err;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_D3D11
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        ਜੇ (!priv->d3d11_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        {
            ਪੂਰਨ err;
            err = opencl_ਚੌਖਟੇ_derive_from_d3d11(dst_fc, src_fc, flags);
            ਜੇ (err < 0)
                ਵਾਪਸ err;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_DRM_ARM
    ਹਾਲਤ AV_HWDEVICE_TYPE_DRM:
        ਜੇ (!priv->drm_arm_mapping_usable)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_OPENCL_VIDEOTOOLBOX
    ਹਾਲਤ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }
    ਵਾਪਸ opencl_ਚੌਖਟੇ_init_command_ਕਤਾਰ(dst_fc);
}

ਅਚਲ HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_ਮਾਪ      = ਆਕਾਰ(OpenCLDeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ      = ਆਕਾਰ(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .ਚੌਖਟੇ_get_constraints = &opencl_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init            = &opencl_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit          = &opencl_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ      = &opencl_get_ਬਫਰ,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ       = &opencl_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from     = &opencl_transfer_ਅੰਕੜੇ_from,

    .map_from               = &opencl_map_from,
    .map_ਮੰਜ਼ਿਲ                 = &opencl_map_ਮੰਜ਼ਿਲ,
    .ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ       = &opencl_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
