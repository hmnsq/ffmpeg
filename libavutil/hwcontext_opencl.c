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

#ವ್ಯಾಖ್ಯಾನಿಸು CL_USE_DEPRECATED_OPENCL_1_2_APIS

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_opencl.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"

#ಆದರೆ HAVE_OPENCL_VAAPI_BEIGNET
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <va/va.h>
#ಅನ್ತರ್ಭಾವ <va/va_drmcommon.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ಆದರೆ CONFIG_LIBMFX
#ಅನ್ತರ್ಭಾವ <mfxstructures.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <va/va.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_va_api_media_sharing_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಅನ್ತರ್ಭಾವ <CL/cl_dx9_media_sharing.h>
#ಅನ್ತರ್ಭಾವ <dxva2api.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_dxva2.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11
#ಅನ್ತರ್ಭಾವ <CL/cl_d3d11.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d11va.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM
#ಅನ್ತರ್ಭಾವ <CL/cl_ext.h>
#ಅನ್ತರ್ಭಾವ <drm_fourcc.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VIDEOTOOLBOX
#ಅನ್ತರ್ಭಾವ <OpenCL/cl_gl_ext.h>
#ಅನ್ತರ್ಭಾವ <VideoToolbox/VideoToolbox.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ff_qsv_get_surface_ತಳ_handle(mfx_ಚೌಕಟ್ಟು_Surface1 *surf,
                                          ಎಣಿಕೆ AVHWDeviceType ತಳ_dev_typ,
                                          ಶೂನ್ಯ **ತಳ_handle);
#ಆದರೆ_ಅಂತ್ಯ


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ OpenCLDeviceContext {
    /**
     * The public AVOpenCLDeviceContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLDeviceContext p;

    // Default command queue to use for transfer/mapping operations on
    // the device.  If the user supplies one, this is a reference to it.
    // Otherwise, it is newly-created.
    cl_command_ಸರತಿ command_ಸರತಿ;

    // The platform the context exists on.  This is needed to query and
    // retrieve extension functions.
    cl_platform_id platform_id;

    // Platform/device-specific functions.
#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
    ಪೂರ್ಣಾಂಕ beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಪೂರ್ಣಾಂಕ qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_VA_APIMedia_Surfaces_INTEL;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2
    ಪೂರ್ಣಾಂಕ dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_DX9_Media_Surfaces_KHR;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_DX9_Media_Surfaces_KHR_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_DX9_Media_Surfaces_KHR;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11
    ಪೂರ್ಣಾಂಕ d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_D3_D11_Objects_KHR_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_D3_D11_Objects_KHR;
    cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_D3_D11_Objects_KHR_fn
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_D3_D11_Objects_KHR;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM
    ಪೂರ್ಣಾಂಕ drm_arm_mapping_usable;
#ಆದರೆ_ಅಂತ್ಯ
} OpenCLDeviceContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_ಸರತಿ command_ಸರತಿ;

#ಆದರೆ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    ಪೂರ್ಣಾಂಕ                   nb_mapped_ಚೌಕಟ್ಟುಗಳು;
    AVOpenCLFrameDescriptor *mapped_ಚೌಕಟ್ಟುಗಳು;
#ಆದರೆ_ಅಂತ್ಯ
} OpenCLFramesContext;


ಸ್ಥಿರ ಶೂನ್ಯ CL_CALLBACK opencl_error_callback(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *errinfo,
                                              ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಖಾಸಗಿ_info,
                                              size_t cb,
                                              ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    AVHWDeviceContext *ctx = user_ದತ್ತಾಂಶ;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ಸ್ಥಿರ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_ಆವೃತ್ತಿ    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ಸ್ಥಿರ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_ಆವೃತ್ತಿ      },
    { "device_version",      CL_DEVICE_ಆವೃತ್ತಿ      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ಸ್ಥಿರ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ಸ್ಥಿರ ಅಕ್ಷರ *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info ಕೀಲಿ)
{
    ಅಕ್ಷರ *str;
    size_t ಗಾತ್ರ_2;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, ಕೀಲಿ, 0, ಖಾಲಿ, &ಗಾತ್ರ_2);
    ಆದರೆ (cle != CL_SUCCESS)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    str = av_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!str)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    cle = clGetPlatformInfo(platform_id, ಕೀಲಿ, ಗಾತ್ರ_2, str, &ಗಾತ್ರ_2);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_free(str);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    av_assert0(ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(str) + 1 == ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ str;
}

ಸ್ಥಿರ ಅಕ್ಷರ *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info ಕೀಲಿ)
{
    ಅಕ್ಷರ *str;
    size_t ಗಾತ್ರ_2;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, ಕೀಲಿ, 0, ಖಾಲಿ, &ಗಾತ್ರ_2);
    ಆದರೆ (cle != CL_SUCCESS)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    str = av_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!str)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    cle = clGetDeviceInfo(device_id, ಕೀಲಿ, ಗಾತ್ರ_2, str, &ಗಾತ್ರ_2);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_free(str);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    av_assert0(ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(str) + 1== ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ str;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_check_platform_extension(cl_platform_id platform_id,
                                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಅಕ್ಷರ *str;
    ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ಆದರೆ (str && ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(str, name))
        ಸಿಕ್ಕಿತು = 1;
    av_free(str);
    ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_check_device_extension(cl_device_id device_id,
                                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಅಕ್ಷರ *str;
    ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ಆದರೆ (str && ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(str, name))
        ಸಿಕ್ಕಿತು = 1;
    av_free(str);
    ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

av_ಬಳಸದ ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ಆದರೆ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ಹಿಂತಿರುಗಿ 1;
    }

    ಆದರೆ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ಹಿಂತಿರುಗಿ 1;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      ಶೂನ್ಯ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ಖಾಲಿ, nb_platforms);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, ಗಾತ್ರ(**platforms));
    ಆದರೆ (!*platforms)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                  ಶೂನ್ಯ *context)
{
    AVDictionary *opts = context;
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *param;
    ಅಕ್ಷರ *str;
    ಪೂರ್ಣಾಂಕ i, ret = 0;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].ಕೀಲಿ,
                            ಖಾಲಿ, 0);
        ಆದರೆ (!param)
            ಮುಂದುವರಿ;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ಆದರೆ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].ಕೀಲಿ, platform_name);
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }
        ಆದರೆ (!av_stristr(str, param->ಮೌಲ್ಯ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ಕೀಲಿ, str);
            ret = 1;
        }
        av_free(str);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    ಶೂನ್ಯ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ಖಾಲಿ, nb_devices);
    ಆದರೆ (cle == CL_DEVICE_NOT_ಸಿಕ್ಕಿತು) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, ಗಾತ್ರ(**devices));
    ಆದರೆ (!*devices)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name,
                                ಶೂನ್ಯ *context)
{
    AVDictionary *opts = context;
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *param;
    ಅಕ್ಷರ *str;
    ಪೂರ್ಣಾಂಕ i, ret = 0;

    param = av_dict_get(opts, "device_type", ಖಾಲಿ, 0);
    ಆದರೆ (param) {
        cl_device_type ಹೊಂದಿಕೆ_type = 0, device_type;
        cl_int cle;

        ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ಆದರೆ (!strcmp(opencl_device_types[i].ಕೀಲಿ, param->ಮೌಲ್ಯ)) {
                ಹೊಂದಿಕೆ_type = opencl_device_types[i].type;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!ಹೊಂದಿಕೆ_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->ಮೌಲ್ಯ);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              ಗಾತ್ರ(device_type), &device_type, ಖಾಲಿ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }

        ಆದರೆ (!(device_type & ಹೊಂದಿಕೆ_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ಹಿಂತಿರುಗಿ 1;
        }
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].ಕೀಲಿ,
                            ಖಾಲಿ, 0);
        ಆದರೆ (!param)
            ಮುಂದುವರಿ;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ಆದರೆ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].ಕೀಲಿ, device_name);
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }
        ಆದರೆ (!av_stristr(str, param->ಮೌಲ್ಯ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ಕೀಲಿ, str);
            ret = 1;
        }
        av_free(str);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ OpenCLDeviceSelector {
    ಪೂರ್ಣಾಂಕ platform_ಸೂಚ್ಯಂಕ;
    ಪೂರ್ಣಾಂಕ device_ಸೂಚ್ಯಂಕ;
    ಶೂನ್ಯ *context;
    ಪೂರ್ಣಾಂಕ (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಂಕ (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಂಕ (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಂಕ (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name,
                               ಶೂನ್ಯ *context);
} OpenCLDeviceSelector;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_device_create_ಆಂತರಿಕ(AVHWDeviceContext *hwdev,
                                         ಸ್ಥಿರಾಂಕ OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ಖಾಲಿ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ಖಾಲಿ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    ಅಕ್ಷರ *platform_name_src = ಖಾಲಿ,
         *device_name_src   = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ err, ಸಿಕ್ಕಿತು, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    ಸಿಕ್ಕಿತು = 0;
    ಗಾಗಿ (p = 0; p < nb_platforms; p++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name;

        ಆದರೆ (selector->platform_ಸೂಚ್ಯಂಕ >= 0 &&
            selector->platform_ಸೂಚ್ಯಂಕ != p)
            ಮುಂದುವರಿ;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ಆದರೆ (platform_name_src)
            platform_name = platform_name_src;
        ಇಲ್ಲದಿದ್ದರೆ
            platform_name = "Unknown Platform";

        ಆದರೆ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ಆದರೆ (err < 0)
                ಹೋಗು fail;
            ಆದರೆ (err > 0)
                ಮುಂದುವರಿ;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ಆದರೆ (err < 0)
            ಮುಂದುವರಿ;

        ಗಾಗಿ (d = 0; d < nb_devices; d++) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name;

            ಆದರೆ (selector->device_ಸೂಚ್ಯಂಕ >= 0 &&
                selector->device_ಸೂಚ್ಯಂಕ != d)
                ಮುಂದುವರಿ;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ಆದರೆ (device_name_src)
                device_name = device_name_src;
            ಇಲ್ಲದಿದ್ದರೆ
                device_name = "Unknown Device";

            ಆದರೆ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ಆದರೆ (err < 0)
                    ಹೋಗು fail;
                ಆದರೆ (err > 0)
                    ಮುಂದುವರಿ;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++ಸಿಕ್ಕಿತು;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ಆದರೆ (ಸಿಕ್ಕಿತು == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        ಹೋಗು fail;
    }
    ಆದರೆ (ಸಿಕ್ಕಿತು > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        ಹೋಗು fail;
    }

    ಆದರೆ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ಆದರೆ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        ಹೋಗು fail;
    }

    hwdev->ಬಿಡುಗಡೆ = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_device_create(AVHWDeviceContext *hwdev, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                                AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ಆದರೆ (device && device[0]) {
        // Match one or both indices for platform and device.
        ಪೂರ್ಣಾಂಕ d = -1, p = -1, ret;
        ಆದರೆ (device[0] == '.')
            ret = ಅಕ್ಷರಸರಣಿ_ಓದು(device, ".%d", &d);
        ಇಲ್ಲದಿದ್ದರೆ
            ret = ಅಕ್ಷರಸರಣಿ_ಓದು(device, "%d.%d", &p, &d);
        ಆದರೆ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        selector.platform_ಸೂಚ್ಯಂಕ = p;
        selector.device_ಸೂಚ್ಯಂಕ   = d;
    } ಇಲ್ಲದಿದ್ದರೆ {
        selector.platform_ಸೂಚ್ಯಂಕ = -1;
        selector.device_ಸೂಚ್ಯಂಕ   = -1;
    }

    ಹಿಂತಿರುಗಿ opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, ಖಾಲಿ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ಆದರೆ (hwctx->command_ಸರತಿ) {
        cle = cl_Retain_Command_ಸರತಿ(hwctx->command_ಸರತಿ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ಹಿಂತಿರುಗಿ AVERROR(EIO);
        }
        priv->command_ಸರತಿ = hwctx->command_ಸರತಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        priv->command_ಸರತಿ = cl_Create_Command_ಸರತಿ(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ಆದರೆ (!priv->command_ಸರತಿ) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ಹಿಂತಿರುಗಿ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          ಗಾತ್ರ(priv->platform_id), &priv->platform_id,
                          ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

#ವ್ಯಾಖ್ಯಾನಿಸು CL_FUNC(name, desc) ಮಾಡು {                                \
        ಆದರೆ (fail)                                               \
            ನಿಲ್ಲಿಸು;                                              \
        priv->name = cl_Get_Extension_Function_ವಿಳಾಸ_For_Platform(  \
            priv->platform_id, #name);                          \
        ಆದರೆ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ಆಗ (0)

#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
    {
        ಪೂರ್ಣಾಂಕ fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ಆದರೆ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_ಗಾತ್ರ;
        cl_context_properties *props = ಖಾಲಿ;
        VADisplay va_display;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *va_ext = "cl_intel_va_api_media_sharing";
        ಪೂರ್ಣಾಂಕ i, fail = 0;

        ಆದರೆ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            ಹೋಗು no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ಖಾಲಿ, &props_ಗಾತ್ರ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ಹೋಗು no_qsv;
        }
        ಆದರೆ (props_ಗಾತ್ರ == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಹೋಗು no_qsv;
        }

        props = av_malloc(props_ಗಾತ್ರ);
        ಆದರೆ (!props)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_ಗಾತ್ರ, props, ಖಾಲಿ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ಹೋಗು no_qsv;
        }

        va_display = ಖಾಲಿ;
        ಗಾಗಿ (i = 0; i < (props_ಗಾತ್ರ / ಗಾತ್ರ(*props) - 1); i++) {
            ಆದರೆ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಹೋಗು no_qsv;
        }
        ಆದರೆ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಹೋಗು no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        ಆದರೆ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2
    {
        ಪೂರ್ಣಾಂಕ fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        ಆದರೆ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *d3d11_ext = "cl_khr_d3d11_sharing";
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        ಪೂರ್ಣಾಂಕ fail = 0;

        ಆದರೆ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        ಆದರೆ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *drm_arm_ext = "cl_arm_import_memory";
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *image_ext   = "cl_khr_image2d_from_buffer";
        ಪೂರ್ಣಾಂಕ fail = 0;

        ಆದರೆ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ಆದರೆ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ಆದರೆ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CL_FUNC

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ಆದರೆ (priv->command_ಸರತಿ) {
        cle = cl_Release_Command_ಸರತಿ(priv->command_ಸರತಿ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_ಸರತಿ = ಖಾಲಿ;
    }
}

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                                    ಶೂನ್ಯ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ಆದರೆ (!cl_Get_Extension_Function_ವಿಳಾಸ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ಹಿಂತಿರುಗಿ 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ 0;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      ಶೂನ್ಯ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        cl_Get_Extension_Function_ವಿಳಾಸ_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ಆದರೆ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ಖಾಲಿ, nb_devices);
    ಆದರೆ (cle == CL_DEVICE_NOT_ಸಿಕ್ಕಿತು) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಗಾತ್ರ(**devices));
    ಆದರೆ (!*devices)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name,
                                                  ಶೂನ್ಯ *context)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *va_ext = "cl_intel_va_api_media_sharing";

    ಆದರೆ (opencl_check_device_extension(device_id, va_ext)) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ಹಿಂತಿರುಗಿ 1;
    }
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                        ಶೂನ್ಯ *context)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *dx9_ext = "cl_khr_dx9_media_sharing";

    ಆದರೆ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ಹಿಂತಿರುಗಿ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ಶೂನ್ಯ *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        cl_Get_Extension_Function_ವಿಳಾಸ_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ಆದರೆ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ಶೂನ್ಯ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ಖಾಲಿ, nb_devices);
    ಆದರೆ (cle == CL_DEVICE_NOT_ಸಿಕ್ಕಿತು) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಗಾತ್ರ(**devices));
    ಆದರೆ (!*devices)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ಶೂನ್ಯ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                        ಶೂನ್ಯ *context)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *d3d11_ext = "cl_khr_d3d11_sharing";

    ಆದರೆ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ಹಿಂತಿರುಗಿ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ಶೂನ್ಯ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        cl_Get_Extension_Function_ವಿಳಾಸ_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ಆದರೆ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ಖಾಲಿ, nb_devices);
    ಆದರೆ (cle == CL_DEVICE_NOT_ಸಿಕ್ಕಿತು) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಗಾತ್ರ(**devices));
    ಆದರೆ (!*devices)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name,
                                    ಶೂನ್ಯ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          ಗಾತ್ರ(device_type), &device_type, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }
    ಆದರೆ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ಹಿಂತಿರುಗಿ 1;
    }

    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *platform_name,
                                          ಶೂನ್ಯ *context)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *drm_arm_ext = "cl_arm_import_memory";

    ಆದರೆ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ಹಿಂತಿರುಗಿ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device_name,
                                        ಶೂನ್ಯ *context)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *drm_arm_ext = "cl_arm_import_memory";

    ಆದರೆ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ಹಿಂತಿರುಗಿ 1;
    }
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;
    ಆಯ್ಕೆ (src_ctx->type) {

#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DRM:
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ಖಾಲಿ;

            err = av_dict_ಗಣ(&selector_opts, "platform_vendor", "Intel", 0);
            ಆದರೆ (err >= 0)
                err = av_dict_ಗಣ(&selector_opts, "platform_version", "beignet", 0);
            ಆದರೆ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_ಸೂಚ್ಯಂಕ      = -1,
                    .device_ಸೂಚ್ಯಂಕ        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ಖಾಲಿ,
                };
                err = opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, ಖಾಲಿ);
            }
            av_dict_free(&selector_opts);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
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
                .platform_ಸೂಚ್ಯಂಕ      = -1,
                .device_ಸೂಚ್ಯಂಕ        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, props);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ಆದರೆ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)hr);
                err = AVERROR_UNKNOWN;
                ನಿಲ್ಲಿಸು;
            }

            hr = IDirect3_DDevice_Manager9_ಬೀಗ_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ಆದರೆ (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_ಸೂಚ್ಯಂಕ      = -1,
                    .device_ಸೂಚ್ಯಂಕ        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
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
                .platform_ಸೂಚ್ಯಂಕ      = -1,
                .device_ಸೂಚ್ಯಂಕ        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, props);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_ಸೂಚ್ಯಂಕ      = -1,
                .device_ಸೂಚ್ಯಂಕ        = -1,
                .context             = ಖಾಲಿ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_ಆಂತರಿಕ(hwdev, &selector, ಖಾಲಿ);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VIDEOTOOLBOX
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ಖಾಲಿ, ಖಾಲಿ, 0);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

    ಪೂರ್ವನಿಯೋಜಿತ:
        err = AVERROR(ENOSYS);
        ನಿಲ್ಲಿಸು;
    }

    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_get_plane_format(ಎಣಿಕೆ AVPixelFormat pixfmt,
                                   ಪೂರ್ಣಾಂಕ plane, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    ಸ್ಥಿರಾಂಕ AVComponentDescriptor *comp;
    ಪೂರ್ಣಾಂಕ channels = 0, ಕ್ರಮ = 0, ಆಳ = 0, ಹೆಜ್ಜೆ = 0;
    ಪೂರ್ಣಾಂಕ wsub, hsub, alpha;
    ಪೂರ್ಣಾಂಕ c;

    ಆದರೆ (plane >= AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು)
        ಹಿಂತಿರುಗಿ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ಆದರೆ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ಆದರೆ (ಅಗಲ & wsub - 1 || ಎತ್ತರ & hsub - 1)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ಆದರೆ (comp->plane != plane)
            ಮುಂದುವರಿ;
        // The step size must be a power of two.
        ಆದರೆ (comp->ಹೆಜ್ಜೆ != 1 && comp->ಹೆಜ್ಜೆ != 2 &&
            comp->ಹೆಜ್ಜೆ != 4 && comp->ಹೆಜ್ಜೆ != 8)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ಆದರೆ (comp->ಸರಿಸು + comp->ಆಳ != 8 &&
            comp->ಸರಿಸು + comp->ಆಳ != 16 &&
            comp->ಸರಿಸು + comp->ಆಳ != 32)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        // The depth must not vary between components.
        ಆದರೆ (ಆಳ && comp->ಆಳ != ಆಳ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ಆದರೆ (comp->ಆಳ > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ಆದರೆ (ಹೆಜ್ಜೆ && comp->ಹೆಜ್ಜೆ != ಹೆಜ್ಜೆ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        ಆಳ = comp->ಆಳ;
        ಕ್ರಮ = ಕ್ರಮ * 10 + comp->ಸ್ಥಾನಾಂತರ / ((ಆಳ + 7) / 8) + 1;
        ಹೆಜ್ಜೆ  = comp->ಹೆಜ್ಜೆ;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ಆದರೆ (channels == 0)
        ಹಿಂತಿರುಗಿ AVERROR(ENOENT);

    memset(image_format, 0, ಗಾತ್ರ(*image_format));
    memset(image_desc,   0, ಗಾತ್ರ(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ಆದರೆ (plane == 0 || alpha) {
        image_desc->image_ಅಗಲ     = ಅಗಲ;
        image_desc->image_ಎತ್ತರ    = ಎತ್ತರ;
        image_desc->image_ಅಡ್ಡಸಾಲು_pitch = ಹೆಜ್ಜೆ * ಅಗಲ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        image_desc->image_ಅಗಲ     = ಅಗಲ  / wsub;
        image_desc->image_ಎತ್ತರ    = ಎತ್ತರ / hsub;
        image_desc->image_ಅಡ್ಡಸಾಲು_pitch = ಹೆಜ್ಜೆ * ಅಗಲ / wsub;
    }

    ಆದರೆ (ಆಳ <= 8) {
        image_format->image_channel_ದತ್ತಾಂಶ_type = CL_UNORM_INT8;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಆಳ <= 16)
            image_format->image_channel_ದತ್ತಾಂಶ_type = CL_UNORM_INT16;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಆಳ == 32)
            image_format->image_channel_ದತ್ತಾಂಶ_type = CL_FLOAT;
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_ಕ್ರಮ(ಕ್ರಮ, type) \
    ಸ್ಥಿತಿ ಕ್ರಮ: image_format->image_channel_ಕ್ರಮ = type; ನಿಲ್ಲಿಸು;
    ಆಯ್ಕೆ (ಕ್ರಮ) {
        CHANNEL_ಕ್ರಮ(1,    CL_R);
        CHANNEL_ಕ್ರಮ(12,   CL_RG);
        CHANNEL_ಕ್ರಮ(1234, CL_RGBA);
        CHANNEL_ಕ್ರಮ(2341, CL_ARGB);
        CHANNEL_ಕ್ರಮ(3214, CL_BGRA);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CL_ABGR
        CHANNEL_ಕ್ರಮ(4321, CL_ABGR);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHANNEL_ಕ್ರಮ

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *hwdev,
                                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ಖಾಲಿ;
    cl_int cle;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    ಪೂರ್ಣಾಂಕ err, pix_fmts_ಸಿಕ್ಕಿತು;
    size_t max_ಅಗಲ, max_ಎತ್ತರ;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_ಅಗಲ,
                          ಗಾತ್ರ(max_ಅಗಲ), &max_ಅಗಲ, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } ಇಲ್ಲದಿದ್ದರೆ {
        constraints->max_ಅಗಲ = max_ಅಗಲ;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_ಎತ್ತರ,
                          ಗಾತ್ರ(max_ಎತ್ತರ), &max_ಎತ್ತರ, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } ಇಲ್ಲದಿದ್ದರೆ {
        constraints->max_ಎತ್ತರ = max_ಎತ್ತರ;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_ಅಗಲ, constraints->max_ಎತ್ತರ);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ಖಾಲಿ, &nb_image_formats);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }
    ಆದರೆ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, ಗಾತ್ರ(*image_formats));
    ಆದರೆ (!image_formats) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ಖಾಲಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    pix_fmts_ಸಿಕ್ಕಿತು = 0;
    ಗಾಗಿ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        ಪೂರ್ಣಾಂಕ plane, i;

        ಗಾಗಿ (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ಆದರೆ (err < 0)
                ನಿಲ್ಲಿಸು;

            ಗಾಗಿ (i = 0; i < nb_image_formats; i++) {
                ಆದರೆ (image_formats[i].image_channel_ಕ್ರಮ ==
                    image_format.image_channel_ಕ್ರಮ &&
                    image_formats[i].image_channel_ದತ್ತಾಂಶ_type ==
                    image_format.image_channel_ದತ್ತಾಂಶ_type)
                    ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (err != AVERROR(ENOENT))
            ಮುಂದುವರಿ;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_ಸಿಕ್ಕಿತು + 2,
                                ಗಾತ್ರ(*constraints->valid_sw_formats));
        ಆದರೆ (err < 0)
            ಹೋಗು fail;
        constraints->valid_sw_formats[pix_fmts_ಸಿಕ್ಕಿತು] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_ಸಿಕ್ಕಿತು + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_ಸಿಕ್ಕಿತು;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;

fail:
    av_freep(&image_formats);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_pool_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)ದತ್ತಾಂಶ;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ p;

    ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ಸ್ಥಿರ AVBufferRef *opencl_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    ಪೂರ್ಣಾಂಕ err, p;
    AVBufferRef *ref;

    desc = av_mallocz(ಗಾತ್ರ(*desc));
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಗಾಗಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->ಅಗಲ, hwfc->ಎತ್ತರ,
                                      &image_format, &image_desc);
        ಆದರೆ (err == AVERROR(ENOENT))
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (err < 0)
            ಹೋಗು fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_ಅಡ್ಡಸಾಲು_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ಖಾಲಿ, &cle);
        ಆದರೆ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            ಹೋಗು fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_ಬಫರ್_create((uint8_t*)desc, ಗಾತ್ರ(*desc),
                           &opencl_pool_free, hwfc, 0);
    ಆದರೆ (!ref)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ ref;

fail:
    ಗಾಗಿ (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_init_command_ಸರತಿ(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_ಸರತಿ = hwctx->command_ಸರತಿ ? hwctx->command_ಸರತಿ
                                               : devpriv->command_ಸರತಿ;
    cle = cl_Retain_Command_ಸರತಿ(priv->command_ಸರತಿ);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *hwfc)
{
    ಆದರೆ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ =
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ(cl_mem), hwfc,
                                 &opencl_pool_alloc, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಹಿಂತಿರುಗಿ opencl_ಚೌಕಟ್ಟುಗಳು_init_command_ಸರತಿ(hwfc);
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ಆದರೆ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    ಪೂರ್ಣಾಂಕ i, p;
    ಗಾಗಿ (i = 0; i < priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];
        ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ಆದರೆ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_ಚೌಕಟ್ಟುಗಳು);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (priv->command_ಸರತಿ) {
        cle = cl_Release_Command_ಸರತಿ(priv->command_ಸರತಿ);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_ಸರತಿ = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_get_ಬಫರ್(AVHWFramesContext *hwfc, AVFrame *ಚೌಕಟ್ಟು)
{
    AVOpenCLFrameDescriptor *desc;
    ಪೂರ್ಣಾಂಕ p;

    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(hwfc->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;

    ಗಾಗಿ (p = 0; p < desc->nb_planes; p++)
        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[p] = (uint8_t*)desc->planes[p];

    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_OPENCL;
    ಚೌಕಟ್ಟು->ಅಗಲ   = hwfc->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = hwfc->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                       ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, ಪೂರ್ಣಾಂಕ nb_events)
{
    cl_int cle;
    ಪೂರ್ಣಾಂಕ i;

    cle = clWaitForEvents(nb_events, events);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

    ಗಾಗಿ (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ err, p;

    ಆದರೆ (dst->format != hwfc->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ಅಗಲ, src->ಎತ್ತರ,
                                      &image_format, &image_desc);
        ಆದರೆ (err < 0) {
            ಆದರೆ (err == AVERROR(ENOENT))
                err = 0;
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!dst->ದತ್ತಾಂಶ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ನಿಲ್ಲಿಸು;
        }

        region[0] = image_desc.image_ಅಗಲ;
        region[1] = image_desc.image_ಎತ್ತರ;
        region[2] = 1;

        cle = cl_ಸರತಿಗೆ_ಸೇರಿಸು_Read_Image(priv->command_ಸರತಿ,
                                 (cl_mem)src->ದತ್ತಾಂಶ[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->ದತ್ತಾಂಶ[p],
                                 0, ಖಾಲಿ, &events[p]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ನಿಲ್ಲಿಸು;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ err, p;

    ಆದರೆ (src->format != hwfc->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ಅಗಲ, src->ಎತ್ತರ,
                                      &image_format, &image_desc);
        ಆದರೆ (err < 0) {
            ಆದರೆ (err == AVERROR(ENOENT))
                err = 0;
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!src->ದತ್ತಾಂಶ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ನಿಲ್ಲಿಸು;
        }

        region[0] = image_desc.image_ಅಗಲ;
        region[1] = image_desc.image_ಎತ್ತರ;
        region[2] = 1;

        cle = cl_ಸರತಿಗೆ_ಸೇರಿಸು_Write_Image(priv->command_ಸರತಿ,
                                  (cl_mem)dst->ದತ್ತಾಂಶ[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->ದತ್ತಾಂಶ[p],
                                  0, ಖಾಲಿ, &events[p]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ನಿಲ್ಲಿಸು;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ಹಿಂತಿರುಗಿ err;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    ಶೂನ್ಯ *ವಿಳಾಸ[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
} OpenCLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ p, e;
    cl_int cle;

    ಗಾಗಿ (p = e = 0; p < FF_ARRAY_ELEMS(map->ವಿಳಾಸ); p++) {
        ಆದರೆ (!map->ವಿಳಾಸ[p])
            ನಿಲ್ಲಿಸು;

        cle = cl_ಸರತಿಗೆ_ಸೇರಿಸು_Unmap_Mem_Object(priv->command_ಸರತಿ,
                                      (cl_mem)hwmap->ಮೂಲ->ದತ್ತಾಂಶ[p],
                                      map->ವಿಳಾಸ[p],
                                      0, ಖಾಲಿ, &events[e]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc, AVFrame *dst,
                            ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t ಅಡ್ಡಸಾಲು_pitch;
    cl_event events[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ಆದರೆ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } ಇಲ್ಲದಿದ್ದರೆ {
        map_flags = 0;
        ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(ಗಾತ್ರ(*map));
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->ಅಗಲ, src->ಎತ್ತರ,
                                      &image_format, &image_desc);
        ಆದರೆ (err == AVERROR(ENOENT))
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (err < 0)
            ಹೋಗು fail;

        region[0] = image_desc.image_ಅಗಲ;
        region[1] = image_desc.image_ಎತ್ತರ;
        region[2] = 1;

        map->ವಿಳಾಸ[p] =
            cl_ಸರತಿಗೆ_ಸೇರಿಸು_Map_Image(priv->command_ಸರತಿ,
                              (cl_mem)src->ದತ್ತಾಂಶ[p],
                              CL_FALSE, map_flags, origin, region,
                              &ಅಡ್ಡಸಾಲು_pitch, ಖಾಲಿ, 0, ಖಾಲಿ,
                              &events[p], &cle);
        ಆದರೆ (!map->ವಿಳಾಸ[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }

        dst->ದತ್ತಾಂಶ[p] = map->ವಿಳಾಸ[p];
        dst->linesize[p] = ಅಡ್ಡಸಾಲು_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->ದತ್ತಾಂಶ[p], dst->ದತ್ತಾಂಶ[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_ಚೌಕಟ್ಟು, map);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (p = 0; p < AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು; p++) {
        ಆದರೆ (!map->ವಿಳಾಸ[p])
            ನಿಲ್ಲಿಸು;
        cl_ಸರತಿಗೆ_ಸೇರಿಸು_Unmap_Mem_Object(priv->command_ಸರತಿ,
                                (cl_mem)src->ದತ್ತಾಂಶ[p],
                                map->ವಿಳಾಸ[p],
                                0, ಖಾಲಿ, &events[p]);
    }
    ಆದರೆ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DRMBeignet_ಗಮ್ಯ_Open_CLMapping {
    AVFrame              *drm_ಚೌಕಟ್ಟು;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor ಚೌಕಟ್ಟು;
} DRMBeignet_ಗಮ್ಯ_Open_CLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_ಗಮ್ಯ_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < mapping->ಚೌಕಟ್ಟು.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->ಚೌಕಟ್ಟು.planes[i]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                                       ಪೂರ್ಣಾಂಕ flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignet_ಗಮ್ಯ_Open_CLMapping *mapping;
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, i, j, p;

    desc = (ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor*)src->ದತ್ತಾಂಶ[0];

    mapping = av_mallocz(ಗಾತ್ರ(*mapping));
    ಆದರೆ (!mapping)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    p = 0;
    ಗಾಗಿ (i = 0; i < desc->nb_layers; i++) {
        ಸ್ಥಿರಾಂಕ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ಗಾಗಿ (j = 0; j < layer->nb_planes; j++) {
            ಸ್ಥಿರಾಂಕ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ಸ್ಥಿರಾಂಕ AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_ಸೂಚ್ಯಂಕ];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .ಗಾತ್ರ_2      = object->ಗಾತ್ರ_2,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .ಸ್ಥಾನಾಂತರ    = plane->ಸ್ಥಾನಾಂತರ,
                .ಅಡ್ಡಸಾಲು_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->ಅಗಲ, src->ಎತ್ತರ,
                                          &image_info.fmt,
                                          &image_desc);
            ಆದರೆ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                ಹೋಗು fail;
            }
            image_info.ಅಗಲ  = image_desc.image_ಅಗಲ;
            image_info.ಎತ್ತರ = image_desc.image_ಎತ್ತರ;

            mapping->ಚೌಕಟ್ಟು.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ಆದರೆ (!mapping->ಚೌಕಟ್ಟು.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }

            dst->ದತ್ತಾಂಶ[p] = (uint8_t*)mapping->ಚೌಕಟ್ಟು.planes[p];
            mapping->ಚೌಕಟ್ಟು.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (p = 0; p < mapping->ಚೌಕಟ್ಟು.nb_planes; p++) {
        ಆದರೆ (mapping->ಚೌಕಟ್ಟು.planes[p])
            clReleaseMemObject(mapping->ಚೌಕಟ್ಟು.planes[p]);
    }
    av_free(mapping);
    memset(dst->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(dst->ದತ್ತಾಂಶ));
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ HAVE_OPENCL_VAAPI_BEIGNET

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                                 ಪೂರ್ಣಾಂಕ flags)
{
    AVFrame *tmp;
    ಪೂರ್ಣಾಂಕ err;

    tmp = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = av_hwframe_map(tmp, src, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ಚೌಕಟ್ಟು_free(&tmp);
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_OPENCL_VAAPI_BEIGNET */
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_OPENCL_DRM_BEIGNET */

ಸ್ಥಿರ ಸಾಲೊಳಗೆ cl_mem_flags opencl_mem_flags_for_mapping(ಪೂರ್ಣಾಂಕ map_flags)
{
    ಆದರೆ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ಹಿಂತಿರುಗಿ CL_MEM_READ_WRITE;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (map_flags & AV_HWFRAME_MAP_READ)
        ಹಿಂತಿರುಗಿ CL_MEM_READ_ONLY;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (map_flags & AV_HWFRAME_MAP_WRITE)
        ಹಿಂತಿರುಗಿ CL_MEM_WRITE_ONLY;
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_VA_APIMedia_Surfaces_INTEL(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ಆದರೆ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, p;

#ಆದರೆ CONFIG_LIBMFX
    ಆದರೆ (src->format == AV_PIX_FMT_QSV) {
        ಶೂನ್ಯ *ತಳ_handle;
        mfx_ಚೌಕಟ್ಟು_Surface1 *mfx_surface = (mfx_ಚೌಕಟ್ಟು_Surface1*)src->ದತ್ತಾಂಶ[3];
        err = ff_qsv_get_surface_ತಳ_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &ತಳ_handle);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
        va_surface = *(VASurfaceID *)ತಳ_handle;
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಆದರೆ (!cl_flags)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(ಗಾತ್ರ(*desc));
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ಆದರೆ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }

        dst->ದತ್ತಾಂಶ[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_VA_APIMedia_Surfaces_INTEL(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        ಹೋಗು fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (p = 0; p < desc->nb_planes; p++)
        ಆದರೆ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(dst->ದತ್ತಾಂಶ));
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DXVA2

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_DX9_Media_Surfaces_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ಹಿಂತಿರುಗಿ;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->ದತ್ತಾಂಶ[3]);

    ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ಆದರೆ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->ದತ್ತಾಂಶ[3])
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_DX9_Media_Surfaces_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (i = 0; i < desc->nb_planes; i++)
        dst->ದತ್ತಾಂಶ[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_DX9_Media_Surfaces_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(dst->ದತ್ತಾಂಶ));
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ಪೂರ್ಣಾಂಕ flags)
{
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, i, p, nb_planes;

    ಆದರೆ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ಆದರೆ (src_fc->initial_pool_ಗಾತ್ರ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಆದರೆ (!cl_flags)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು = src_hwctx->nb_surfaces;

    ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು =
        av_calloc(ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು,
                  ಗಾತ್ರ(*ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು));
    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು; i++) {
        AVOpenCLFrameDescriptor *desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ಖಾಲಿ,
        };
        desc->nb_planes = nb_planes;
        ಗಾಗಿ (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ಆದರೆ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }
        }
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು; i++) {
        AVOpenCLFrameDescriptor *desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];
        ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
            ಆದರೆ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು);
    ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು = 0;
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_D3D11

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_D3_D11_Objects_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, ಸೂಚ್ಯಂಕ, i;

    ಸೂಚ್ಯಂಕ = (intptr_t)src->ದತ್ತಾಂಶ[1];
    ಆದರೆ (ಸೂಚ್ಯಂಕ >= ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", ಸೂಚ್ಯಂಕ, ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           ಸೂಚ್ಯಂಕ);

    desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[ಸೂಚ್ಯಂಕ];

    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Acquire_D3_D11_Objects_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (i = 0; i < desc->nb_planes; i++)
        dst->ದತ್ತಾಂಶ[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    cle = device_priv->cl_ಸರತಿಗೆ_ಸೇರಿಸು_Release_D3_D11_Objects_KHR(
        ಚೌಕಟ್ಟುಗಳು_priv->command_ಸರತಿ, desc->nb_planes, desc->planes,
        0, ಖಾಲಿ, &event);
    ಆದರೆ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(dst->ದತ್ತಾಂಶ));
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ಪೂರ್ಣಾಂಕ flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *ಚೌಕಟ್ಟುಗಳು_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, i, p, nb_planes;

    ಆದರೆ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ಆದರೆ (src_fc->initial_pool_ಗಾತ್ರ == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಆದರೆ (!cl_flags)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು = src_fc->initial_pool_ಗಾತ್ರ;

    ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು =
        av_calloc(ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು,
                  ಗಾತ್ರ(*ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು));
    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು; i++) {
        AVOpenCLFrameDescriptor *desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];
        desc->nb_planes = nb_planes;
        ಗಾಗಿ (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ಆದರೆ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)subresource, cle);
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }
        }
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು; i++) {
        AVOpenCLFrameDescriptor *desc = &ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು[i];
        ಗಾಗಿ (p = 0; p < desc->nb_planes; p++) {
            ಆದರೆ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&ಚೌಕಟ್ಟುಗಳು_priv->mapped_ಚೌಕಟ್ಟುಗಳು);
    ಚೌಕಟ್ಟುಗಳು_priv->nb_mapped_ಚೌಕಟ್ಟುಗಳು = 0;
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_DRM_ARM

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DRMARMtoOpenCLMapping {
    ಪೂರ್ಣಾಂಕ nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    ಪೂರ್ಣಾಂಕ nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    ಗಾಗಿ (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ಖಾಲಿ;
    cl_mem_flags cl_flags;
    ಸ್ಥಿರಾಂಕ cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    ಪೂರ್ಣಾಂಕ err, i, j;

    desc = (ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor*)src->ದತ್ತಾಂಶ[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಆದರೆ (!cl_flags)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    mapping = av_mallocz(ಗಾತ್ರ(*mapping));
    ಆದರೆ (!mapping)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    ಗಾಗಿ (i = 0; i < desc->nb_objects; i++) {
        ಪೂರ್ಣಾಂಕ fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ಆದರೆ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_ಸ್ಮರಣೆ_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].ಗಾತ್ರ_2, &cle);
        ಆದರೆ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].ಗಾತ್ರ_2, cle);
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }
    }

    mapping->nb_planes = 0;
    ಗಾಗಿ (i = 0; i < desc->nb_layers; i++) {
        ಸ್ಥಿರಾಂಕ AVDRMLayerDescriptor *layer = &desc->layers[i];

        ಗಾಗಿ (j = 0; j < layer->nb_planes; j++) {
            ಸ್ಥಿರಾಂಕ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_ಬಫರ್;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_ಬಫರ್_region region;
            ಪೂರ್ಣಾಂಕ p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->ಅಗಲ, src_fc->ಎತ್ತರ,
                                          &image_format, &image_desc);
            ಆದರೆ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                ಹೋಗು fail;
            }

            region.origin = plane->ಸ್ಥಾನಾಂತರ;
            region.ಗಾತ್ರ_2   = image_desc.image_ಅಡ್ಡಸಾಲು_pitch *
                            image_desc.image_ಎತ್ತರ;

            plane_ಬಫರ್ =
                cl_Create_Sub_ಬಫರ್(mapping->object_buffers[plane->object_ಸೂಚ್ಯಂಕ],
                                  cl_flags,
                                  CL_ಬಫರ್_CREATE_TYPE_REGION,
                                  &region, &cle);
            ಆದರೆ (!plane_ಬಫರ್) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }

            image_desc.ಬಫರ್ = plane_ಬಫರ್;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ಖಾಲಿ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_ಬಫರ್);

            ಆದರೆ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ಹೋಗು fail;
            }

            ++mapping->nb_planes;
        }
    }

    ಗಾಗಿ (i = 0; i < mapping->nb_planes; i++)
        dst->ದತ್ತಾಂಶ[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    ಗಾಗಿ (i = 0; i < mapping->nb_objects; i++) {
        ಆದರೆ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(dst->ದತ್ತಾಂಶ));
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_OPENCL_VIDEOTOOLBOX

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    CVPixel_ಬಫರ್_Ref pixbuf = (CVPixel_ಬಫರ್_Ref) src->ದತ್ತಾಂಶ[3];
    IOSurfaceRef io_surface_ref = CVPixel_ಬಫರ್_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ಖಾಲಿ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ಆದರೆ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(ಗಾತ್ರ(*desc));
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->ಅಗಲ, src->ಎತ್ತರ,
                                      &image_format, &image_desc);
        ಆದರೆ (err == AVERROR(ENOENT))
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (err < 0)
            ಹೋಗು fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ಆದರೆ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            ಹೋಗು fail;
        }
        desc->nb_planes++;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_planes; i++)
        dst->ದತ್ತಾಂಶ[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    dst->ಅಗಲ = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ಆದರೆ (hwfc->sw_format != dst->format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    ಹಿಂತಿರುಗಿ opencl_map_ಚೌಕಟ್ಟು(hwfc, dst, src, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_map_ಗಮ್ಯ(AVHWFramesContext *hwfc, AVFrame *dst,
                         ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    av_ಬಳಸದ OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    ಆಯ್ಕೆ (src->format) {
#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಆದರೆ (priv->beignet_drm_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VAAPI_BEIGNET
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
        ಆದರೆ (priv->beignet_drm_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_vaapi(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಸ್ಥಿತಿ AV_PIX_FMT_QSV:
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
        ಆದರೆ (priv->qsv_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_qsv(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_DXVA2
    ಸ್ಥಿತಿ AV_PIX_FMT_DXVA2_VLD:
        ಆದರೆ (priv->dxva2_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_dxva2(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_D3D11
    ಸ್ಥಿತಿ AV_PIX_FMT_D3D11:
        ಆದರೆ (priv->d3d11_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_d3d11(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_DRM_ARM
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಆದರೆ (priv->drm_arm_mapping_usable)
            ಹಿಂತಿರುಗಿ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VIDEOTOOLBOX
    ಸ್ಥಿತಿ AV_PIX_FMT_VIDEOTOOLBOX:
        ಹಿಂತಿರುಗಿ opencl_map_from_vt(hwfc, dst, src, flags);
#ಆದರೆ_ಅಂತ್ಯ
    }
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opencl_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ಪೂರ್ಣಾಂಕ flags)
{
    av_ಬಳಸದ OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    ಆಯ್ಕೆ (src_fc->device_ctx->type) {
#ಆದರೆ HAVE_OPENCL_DRM_BEIGNET
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DRM:
        ಆದರೆ (!priv->beignet_drm_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VAAPI_BEIGNET
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        ಆದರೆ (!priv->beignet_drm_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_QSV:
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        ಆದರೆ (!priv->qsv_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        ಆದರೆ (!priv->dxva2_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        {
            ಪೂರ್ಣಾಂಕ err;
            err = opencl_ಚೌಕಟ್ಟುಗಳು_derive_from_dxva2(dst_fc, src_fc, flags);
            ಆದರೆ (err < 0)
                ಹಿಂತಿರುಗಿ err;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_D3D11
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        ಆದರೆ (!priv->d3d11_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        {
            ಪೂರ್ಣಾಂಕ err;
            err = opencl_ಚೌಕಟ್ಟುಗಳು_derive_from_d3d11(dst_fc, src_fc, flags);
            ಆದರೆ (err < 0)
                ಹಿಂತಿರುಗಿ err;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_DRM_ARM
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DRM:
        ಆದರೆ (!priv->drm_arm_mapping_usable)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_OPENCL_VIDEOTOOLBOX
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
    ಹಿಂತಿರುಗಿ opencl_ಚೌಕಟ್ಟುಗಳು_init_command_ಸರತಿ(dst_fc);
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(OpenCLDeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .ಚೌಕಟ್ಟುಗಳು_get_constraints = &opencl_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init            = &opencl_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit          = &opencl_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = &opencl_get_ಬಫರ್,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = &opencl_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from     = &opencl_transfer_ದತ್ತಾಂಶ_from,

    .map_from               = &opencl_map_from,
    .map_ಗಮ್ಯ                 = &opencl_map_ಗಮ್ಯ,
    .ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ       = &opencl_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
