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

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

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

#ಯದಿ HAVE_OPENCL_VAAPI_BEIGNET
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <va/va.h>
#ಅನ್ತರ್ಭಾವ <va/va_drmcommon.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#endif

#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#endif

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ಯದಿ CONFIG_LIBMFX
#ಅನ್ತರ್ಭಾವ <mfxstructures.h>
#endif
#ಅನ್ತರ್ಭಾವ <va/va.h>
#ಅನ್ತರ್ಭಾವ <CL/cl_va_api_media_sharing_intel.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#endif

#ಯದಿ HAVE_OPENCL_DXVA2
#define COBJMACROS
#ಅನ್ತರ್ಭಾವ <CL/cl_dx9_media_sharing.h>
#ಅನ್ತರ್ಭಾವ <dxva2api.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_dxva2.h"
#endif

#ಯದಿ HAVE_OPENCL_D3D11
#ಅನ್ತರ್ಭಾವ <CL/cl_d3d11.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d11va.h"
#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM
#ಅನ್ತರ್ಭಾವ <CL/cl_ext.h>
#ಅನ್ತರ್ಭಾವ <drm_fourcc.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#endif

#ಯದಿ HAVE_OPENCL_VIDEOTOOLBOX
#ಅನ್ತರ್ಭಾವ <OpenCL/cl_gl_ext.h>
#ಅನ್ತರ್ಭಾವ <VideoToolbox/VideoToolbox.h>
#endif

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ಗಣನಾ AVHWDeviceType base_dev_typ,
                                          ಶೂನ್ಯ **base_handle);
#endif


ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ OpenCLDeviceContext {
    /**
     * The public AVOpenCLDeviceContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLDeviceContext p;

    // Default command queue to use for transfer/mapping operations on
    // the device.  If the user supplies one, this is a reference to it.
    // Otherwise, it is newly-created.
    cl_command_queue command_queue;

    // The platform the context exists on.  This is needed to query and
    // retrieve extension functions.
    cl_platform_id platform_id;

    // Platform/device-specific functions.
#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
    ಪೂರ್ಣಾಙ್ಕ beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಪೂರ್ಣಾಙ್ಕ qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#ಯದಿ HAVE_OPENCL_DXVA2
    ಪೂರ್ಣಾಙ್ಕ dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#ಯದಿ HAVE_OPENCL_D3D11
    ಪೂರ್ಣಾಙ್ಕ d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM
    ಪೂರ್ಣಾಙ್ಕ drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#ಯದಿ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    ಪೂರ್ಣಾಙ್ಕ                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


ಸ್ಥಿರ ಶೂನ್ಯ CL_CALLBACK opencl_error_callback(ಧ್ರುವ ವರ್ಣ *errinfo,
                                              ಧ್ರುವ ಶೂನ್ಯ *private_info,
                                              size_t cb,
                                              ಶೂನ್ಯ *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ಸ್ಥಿರ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ಸ್ಥಿರ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ಸ್ಥಿರ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ಸ್ಥಿರ ವರ್ಣ *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info ಕೀಲಿ)
{
    ವರ್ಣ *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, ಕೀಲಿ, 0, ರಿಕ್ತ, &size);
    ಯದಿ (cle != CL_SUCCESS)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    str = av_malloc(size);
    ಯದಿ (!str)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    cle = clGetPlatformInfo(platform_id, ಕೀಲಿ, size, str, &size);
    ಯದಿ (cle != CL_SUCCESS) {
        av_free(str);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    av_assert0(strlen(str) + 1 == size);
    ಪ್ರತ್ಯಾಗಮ str;
}

ಸ್ಥಿರ ವರ್ಣ *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info ಕೀಲಿ)
{
    ವರ್ಣ *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, ಕೀಲಿ, 0, ರಿಕ್ತ, &size);
    ಯದಿ (cle != CL_SUCCESS)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    str = av_malloc(size);
    ಯದಿ (!str)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    cle = clGetDeviceInfo(device_id, ಕೀಲಿ, size, str, &size);
    ಯದಿ (cle != CL_SUCCESS) {
        av_free(str);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    av_assert0(strlen(str) + 1== size);
    ಪ್ರತ್ಯಾಗಮ str;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_check_platform_extension(cl_platform_id platform_id,
                                           ಧ್ರುವ ವರ್ಣ *name)
{
    ವರ್ಣ *str;
    ಪೂರ್ಣಾಙ್ಕ found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ಯದಿ (str && strstr(str, name))
        found = 1;
    av_free(str);
    ಪ್ರತ್ಯಾಗಮ found;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_check_device_extension(cl_device_id device_id,
                                         ಧ್ರುವ ವರ್ಣ *name)
{
    ವರ್ಣ *str;
    ಪೂರ್ಣಾಙ್ಕ found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ಯದಿ (str && strstr(str, name))
        found = 1;
    av_free(str);
    ಪ್ರತ್ಯಾಗಮ found;
}

av_unused ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ಧ್ರುವ ವರ್ಣ *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ಯದಿ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ಪ್ರತ್ಯಾಗಮ 1;
    }

    ಯದಿ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ಪ್ರತ್ಯಾಗಮ 1;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      ಶೂನ್ಯ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ರಿಕ್ತ, nb_platforms);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, ಪರಿಮಾಣ(**platforms));
    ಯದಿ (!*platforms)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENODEV);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ಧ್ರುವ ವರ್ಣ *platform_name,
                                  ಶೂನ್ಯ *context)
{
    AVDictionary *opts = context;
    ಧ್ರುವ AVDictionaryEntry *param;
    ವರ್ಣ *str;
    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].ಕೀಲಿ,
                            ರಿಕ್ತ, 0);
        ಯದಿ (!param)
            ಅನುವರ್ತ;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ಯದಿ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].ಕೀಲಿ, platform_name);
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
        }
        ಯದಿ (!av_stristr(str, param->ಮೌಲ್ಯ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ಕೀಲಿ, str);
            ret = 1;
        }
        av_free(str);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ಧ್ರುವ ವರ್ಣ *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    ಶೂನ್ಯ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ರಿಕ್ತ, nb_devices);
    ಯದಿ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, ಪರಿಮಾಣ(**devices));
    ಯದಿ (!*devices)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENODEV);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ಧ್ರುವ ವರ್ಣ *device_name,
                                ಶೂನ್ಯ *context)
{
    AVDictionary *opts = context;
    ಧ್ರುವ AVDictionaryEntry *param;
    ವರ್ಣ *str;
    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;

    param = av_dict_get(opts, "device_type", ರಿಕ್ತ, 0);
    ಯದಿ (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ಯದಿ (!strcmp(opencl_device_types[i].ಕೀಲಿ, param->ಮೌಲ್ಯ)) {
                match_type = opencl_device_types[i].type;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->ಮೌಲ್ಯ);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              ಪರಿಮಾಣ(device_type), &device_type, ರಿಕ್ತ);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
        }

        ಯದಿ (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].ಕೀಲಿ,
                            ರಿಕ್ತ, 0);
        ಯದಿ (!param)
            ಅನುವರ್ತ;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ಯದಿ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].ಕೀಲಿ, device_name);
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
        }
        ಯದಿ (!av_stristr(str, param->ಮೌಲ್ಯ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ಕೀಲಿ, str);
            ret = 1;
        }
        av_free(str);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ OpenCLDeviceSelector {
    ಪೂರ್ಣಾಙ್ಕ platform_index;
    ಪೂರ್ಣಾಙ್ಕ device_index;
    ಶೂನ್ಯ *context;
    ಪೂರ್ಣಾಙ್ಕ (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಙ್ಕ (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ಧ್ರುವ ವರ್ಣ *platform_name,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಙ್ಕ (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ಧ್ರುವ ವರ್ಣ *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               ಶೂನ್ಯ *context);
    ಪೂರ್ಣಾಙ್ಕ (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ಧ್ರುವ ವರ್ಣ *device_name,
                               ಶೂನ್ಯ *context);
} OpenCLDeviceSelector;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ಧ್ರುವ OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ರಿಕ್ತ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ರಿಕ್ತ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    ವರ್ಣ *platform_name_src = ರಿಕ್ತ,
         *device_name_src   = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    found = 0;
    ಪ್ರತಿ (p = 0; p < nb_platforms; p++) {
        ಧ್ರುವ ವರ್ಣ *platform_name;

        ಯದಿ (selector->platform_index >= 0 &&
            selector->platform_index != p)
            ಅನುವರ್ತ;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ಯದಿ (platform_name_src)
            platform_name = platform_name_src;
        ಅನ್ಯಥಾ
            platform_name = "Unknown Platform";

        ಯದಿ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ಯದಿ (err < 0)
                ಗಚ್ಛ fail;
            ಯದಿ (err > 0)
                ಅನುವರ್ತ;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ಯದಿ (err < 0)
            ಅನುವರ್ತ;

        ಪ್ರತಿ (d = 0; d < nb_devices; d++) {
            ಧ್ರುವ ವರ್ಣ *device_name;

            ಯದಿ (selector->device_index >= 0 &&
                selector->device_index != d)
                ಅನುವರ್ತ;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ಯದಿ (device_name_src)
                device_name = device_name_src;
            ಅನ್ಯಥಾ
                device_name = "Unknown Device";

            ಯದಿ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ಯದಿ (err < 0)
                    ಗಚ್ಛ fail;
                ಯದಿ (err > 0)
                    ಅನುವರ್ತ;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ಯದಿ (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        ಗಚ್ಛ fail;
    }
    ಯದಿ (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        ಗಚ್ಛ fail;
    }

    ಯದಿ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } ಅನ್ಯಥಾ {
        ಯದಿ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ಯದಿ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        ಗಚ್ಛ fail;
    }

    hwdev->ಮುಕ್ತ = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_device_create(AVHWDeviceContext *hwdev, ಧ್ರುವ ವರ್ಣ *device,
                                AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ಯದಿ (device && device[0]) {
        // Match one or both indices for platform and device.
        ಪೂರ್ಣಾಙ್ಕ d = -1, p = -1, ret;
        ಯದಿ (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        ಅನ್ಯಥಾ
            ret = sscanf(device, "%d.%d", &p, &d);
        ಯದಿ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } ಅನ್ಯಥಾ {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    ಪ್ರತ್ಯಾಗಮ opencl_device_create_internal(hwdev, &selector, ರಿಕ್ತ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ಯದಿ (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } ಅನ್ಯಥಾ {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ಯದಿ (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          ಪರಿಮಾಣ(priv->platform_id), &priv->platform_id,
                          ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

#define CL_FUNC(name, desc) ಕುರು {                                \
        ಯದಿ (fail)                                               \
            ಭಙ್ಗ;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        ಯದಿ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } ಅನ್ಯಥಾ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ಯಾವತ್ (0)

#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
    {
        ಪೂರ್ಣಾಙ್ಕ fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ಯದಿ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } ಅನ್ಯಥಾ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = ರಿಕ್ತ;
        VADisplay va_display;
        ಧ್ರುವ ವರ್ಣ *va_ext = "cl_intel_va_api_media_sharing";
        ಪೂರ್ಣಾಙ್ಕ i, fail = 0;

        ಯದಿ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            ಗಚ್ಛ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ರಿಕ್ತ, &props_size);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ಗಚ್ಛ no_qsv;
        }
        ಯದಿ (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಗಚ್ಛ no_qsv;
        }

        props = av_malloc(props_size);
        ಯದಿ (!props)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, ರಿಕ್ತ);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ಗಚ್ಛ no_qsv;
        }

        va_display = ರಿಕ್ತ;
        ಪ್ರತಿ (i = 0; i < (props_size / ಪರಿಮಾಣ(*props) - 1); i++) {
            ಯದಿ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಗಚ್ಛ no_qsv;
        }
        ಯದಿ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ಗಚ್ಛ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        ಯದಿ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } ಅನ್ಯಥಾ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#ಯದಿ HAVE_OPENCL_DXVA2
    {
        ಪೂರ್ಣಾಙ್ಕ fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        ಯದಿ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } ಅನ್ಯಥಾ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#ಯದಿ HAVE_OPENCL_D3D11
    {
        ಧ್ರುವ ವರ್ಣ *d3d11_ext = "cl_khr_d3d11_sharing";
        ಧ್ರುವ ವರ್ಣ *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        ಪೂರ್ಣಾಙ್ಕ fail = 0;

        ಯದಿ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } ಅನ್ಯಥಾ ಯದಿ (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireD3D11ObjectsKHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseD3D11ObjectsKHR,
                "D3D11 in OpenCL release");

        ಯದಿ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } ಅನ್ಯಥಾ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM
    {
        ಧ್ರುವ ವರ್ಣ *drm_arm_ext = "cl_arm_import_memory";
        ಧ್ರುವ ವರ್ಣ *image_ext   = "cl_khr_image2d_from_buffer";
        ಪೂರ್ಣಾಙ್ಕ fail = 0;

        ಯದಿ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ಯದಿ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ಯದಿ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } ಅನ್ಯಥಾ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ಯದಿ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = ರಿಕ್ತ;
    }
}

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ಧ್ರುವ ವರ್ಣ *platform_name,
                                                    ಶೂನ್ಯ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ಯದಿ (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ಪ್ರತ್ಯಾಗಮ 1;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ 0;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ಧ್ರುವ ವರ್ಣ *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      ಶೂನ್ಯ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ಯದಿ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ರಿಕ್ತ, nb_devices);
    ಯದಿ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಪರಿಮಾಣ(**devices));
    ಯದಿ (!*devices)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ಧ್ರುವ ವರ್ಣ *device_name,
                                                  ಶೂನ್ಯ *context)
{
    ಧ್ರುವ ವರ್ಣ *va_ext = "cl_intel_va_api_media_sharing";

    ಯದಿ (opencl_check_device_extension(device_id, va_ext)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
}
#endif

#ಯದಿ HAVE_OPENCL_DXVA2
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ಧ್ರುವ ವರ್ಣ *platform_name,
                                        ಶೂನ್ಯ *context)
{
    ಧ್ರುವ ವರ್ಣ *dx9_ext = "cl_khr_dx9_media_sharing";

    ಯದಿ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಧ್ರುವ ವರ್ಣ *platform_name,
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
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ಯದಿ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ಶೂನ್ಯ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ರಿಕ್ತ, nb_devices);
    ಯದಿ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಪರಿಮಾಣ(**devices));
    ಯದಿ (!*devices)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ಶೂನ್ಯ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
#endif

#ಯದಿ HAVE_OPENCL_D3D11
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ಧ್ರುವ ವರ್ಣ *platform_name,
                                        ಶೂನ್ಯ *context)
{
    ಧ್ರುವ ವರ್ಣ *d3d11_ext = "cl_khr_d3d11_sharing";

    ಯದಿ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಧ್ರುವ ವರ್ಣ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ಶೂನ್ಯ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ಯದಿ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ರಿಕ್ತ, nb_devices);
    ಯದಿ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ಪರಿಮಾಣ(**devices));
    ಯದಿ (!*devices)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
#endif

#ಯದಿ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ಧ್ರುವ ವರ್ಣ *device_name,
                                    ಶೂನ್ಯ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          ಪರಿಮಾಣ(device_type), &device_type, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }
    ಯದಿ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ಪ್ರತ್ಯಾಗಮ 1;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ಧ್ರುವ ವರ್ಣ *platform_name,
                                          ಶೂನ್ಯ *context)
{
    ಧ್ರುವ ವರ್ಣ *drm_arm_ext = "cl_arm_import_memory";

    ಯದಿ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ಧ್ರುವ ವರ್ಣ *device_name,
                                        ಶೂನ್ಯ *context)
{
    ಧ್ರುವ ವರ್ಣ *drm_arm_ext = "cl_arm_import_memory";

    ಯದಿ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    ವಿಕಲ್ಪ (src_ctx->type) {

#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DRM:
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ರಿಕ್ತ;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            ಯದಿ (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            ಯದಿ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ರಿಕ್ತ,
                };
                err = opencl_device_create_internal(hwdev, &selector, ರಿಕ್ತ);
            }
            av_dict_free(&selector_opts);
        }
        ಭಙ್ಗ;
#endif

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
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
                .platform_index      = -1,
                .device_index        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        ಭಙ್ಗ;
#endif

#ಯದಿ HAVE_OPENCL_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ಯದಿ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                ಭಙ್ಗ;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ಯದಿ (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_internal(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } ಅನ್ಯಥಾ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ಭಙ್ಗ;
#endif

#ಯದಿ HAVE_OPENCL_D3D11
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
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
                .platform_index      = -1,
                .device_index        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        ಭಙ್ಗ;
#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = ರಿಕ್ತ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, ರಿಕ್ತ);
        }
        ಭಙ್ಗ;
#endif

#ಯದಿ HAVE_OPENCL_VIDEOTOOLBOX
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ರಿಕ್ತ, ರಿಕ್ತ, 0);
        ಭಙ್ಗ;
#endif

    ಸ್ವಭಾವ:
        err = AVERROR(ENOSYS);
        ಭಙ್ಗ;
    }

    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_get_plane_format(ಗಣನಾ AVPixelFormat pixfmt,
                                   ಪೂರ್ಣಾಙ್ಕ plane, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    ಧ್ರುವ AVComponentDescriptor *comp;
    ಪೂರ್ಣಾಙ್ಕ channels = 0, order = 0, depth = 0, step = 0;
    ಪೂರ್ಣಾಙ್ಕ wsub, hsub, alpha;
    ಪೂರ್ಣಾಙ್ಕ c;

    ಯದಿ (plane >= AV_ಅಂಕೆ_DATA_POINTERS)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ಯದಿ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ಯದಿ (width & wsub - 1 || height & hsub - 1)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ಯದಿ (comp->plane != plane)
            ಅನುವರ್ತ;
        // The step size must be a power of two.
        ಯದಿ (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ಯದಿ (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        // The depth must not vary between components.
        ಯದಿ (depth && comp->depth != depth)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ಯದಿ (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ಯದಿ (step && comp->step != step)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ಯದಿ (channels == 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOENT);

    memset(image_format, 0, ಪರಿಮಾಣ(*image_format));
    memset(image_desc,   0, ಪರಿಮಾಣ(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ಯದಿ (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } ಅನ್ಯಥಾ {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    ಯದಿ (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } ಅನ್ಯಥಾ {
        ಯದಿ (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        ಅನ್ಯಥಾ ಯದಿ (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    ಪಕ್ಷ order: image_format->image_channel_order = type; ಭಙ್ಗ;
    ವಿಕಲ್ಪ (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ರಿಕ್ತ;
    cl_int cle;
    ಗಣನಾ AVPixelFormat pix_fmt;
    ಪೂರ್ಣಾಙ್ಕ err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          ಪರಿಮಾಣ(max_width), &max_width, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } ಅನ್ಯಥಾ {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          ಪರಿಮಾಣ(max_height), &max_height, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } ಅನ್ಯಥಾ {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ರಿಕ್ತ, &nb_image_formats);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }
    ಯದಿ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, ಪರಿಮಾಣ(*image_formats));
    ಯದಿ (!image_formats) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ರಿಕ್ತ);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    pix_fmts_found = 0;
    ಪ್ರತಿ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        ಪೂರ್ಣಾಙ್ಕ plane, i;

        ಪ್ರತಿ (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ಯದಿ (err < 0)
                ಭಙ್ಗ;

            ಪ್ರತಿ (i = 0; i < nb_image_formats; i++) {
                ಯದಿ (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    ಭಙ್ಗ;
            }
            ಯದಿ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (err != AVERROR(ENOENT))
            ಅನುವರ್ತ;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                ಪರಿಮಾಣ(*constraints->valid_sw_formats));
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
    ಯದಿ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_freep(&image_formats);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_pool_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ p;

    ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ಸ್ಥಿರ AVBufferRef *opencl_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    ಪೂರ್ಣಾಙ್ಕ err, p;
    AVBufferRef *ref;

    desc = av_mallocz(ಪರಿಮಾಣ(*desc));
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        ಯದಿ (err == AVERROR(ENOENT))
            ಭಙ್ಗ;
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ರಿಕ್ತ, &cle);
        ಯದಿ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            ಗಚ್ಛ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, ಪರಿಮಾಣ(*desc),
                           &opencl_pool_free, hwfc, 0);
    ಯದಿ (!ref)
        ಗಚ್ಛ fail;

    ಪ್ರತ್ಯಾಗಮ ref;

fail:
    ಪ್ರತಿ (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_init(AVHWFramesContext *hwfc)
{
    ಯದಿ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(ಪರಿಮಾಣ(cl_mem), hwfc,
                                 &opencl_pool_alloc, ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(hwfc)->pool_internal)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ಪ್ರತ್ಯಾಗಮ opencl_frames_init_command_queue(hwfc);
}

ಸ್ಥಿರ ಶೂನ್ಯ opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ಯದಿ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    ಪೂರ್ಣಾಙ್ಕ i, p;
    ಪ್ರತಿ (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ಯದಿ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    ಯದಿ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    ಪೂರ್ಣಾಙ್ಕ p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ಗಣನಾ AVHWFrameTransferDirection dir,
                                       ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, ಪೂರ್ಣಾಙ್ಕ nb_events)
{
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ i;

    cle = clWaitForEvents(nb_events, events);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

    ಪ್ರತಿ (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ err, p;

    ಯದಿ (dst->format != hwfc->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ಯದಿ (err < 0) {
            ಯದಿ (err == AVERROR(ENOENT))
                err = 0;
            ಭಙ್ಗ;
        }

        ಯದಿ (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ಭಙ್ಗ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, ರಿಕ್ತ, &events[p]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ಭಙ್ಗ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ err, p;

    ಯದಿ (src->format != hwfc->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ಯದಿ (err < 0) {
            ಯದಿ (err == AVERROR(ENOENT))
                err = 0;
            ಭಙ್ಗ;
        }

        ಯದಿ (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ಭಙ್ಗ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, ರಿಕ್ತ, &events[p]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ಭಙ್ಗ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ಪ್ರತ್ಯಾಗಮ err;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    ಶೂನ್ಯ *address[AV_ಅಂಕೆ_DATA_POINTERS];
} OpenCLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ p, e;
    cl_int cle;

    ಪ್ರತಿ (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        ಯದಿ (!map->address[p])
            ಭಙ್ಗ;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, ರಿಕ್ತ, &events[e]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t row_pitch;
    cl_event events[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ಯದಿ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } ಅನ್ಯಥಾ {
        map_flags = 0;
        ಯದಿ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(ಪರಿಮಾಣ(*map));
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ಯದಿ (err == AVERROR(ENOENT))
            ಭಙ್ಗ;
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, ರಿಕ್ತ, 0, ರಿಕ್ತ,
                              &events[p], &cle);
        ಯದಿ (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (p = 0; p < AV_ಅಂಕೆ_DATA_POINTERS; p++) {
        ಯದಿ (!map->address[p])
            ಭಙ್ಗ;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, ರಿಕ್ತ, &events[p]);
    }
    ಯದಿ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

#ಯದಿ HAVE_OPENCL_DRM_BEIGNET

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ಧ್ರುವ AVFrame *src,
                                       ಪೂರ್ಣಾಙ್ಕ flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ಧ್ರುವ AVDRMFrameDescriptor *desc;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, i, j, p;

    desc = (ಧ್ರುವ AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(ಪರಿಮಾಣ(*mapping));
    ಯದಿ (!mapping)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    p = 0;
    ಪ್ರತಿ (i = 0; i < desc->nb_layers; i++) {
        ಧ್ರುವ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ಪ್ರತಿ (j = 0; j < layer->nb_planes; j++) {
            ಧ್ರುವ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ಧ್ರುವ AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_index];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .size      = object->size,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .offset    = plane->offset,
                .row_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->width, src->height,
                                          &image_info.fmt,
                                          &image_desc);
            ಯದಿ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                ಗಚ್ಛ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ಯದಿ (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (p = 0; p < mapping->frame.nb_planes; p++) {
        ಯದಿ (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, ಪರಿಮಾಣ(dst->data));
    ಪ್ರತ್ಯಾಗಮ err;
}

#ಯದಿ HAVE_OPENCL_VAAPI_BEIGNET

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ಧ್ರುವ AVFrame *src,
                                 ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVFrame *tmp;
    ಪೂರ್ಣಾಙ್ಕ err;

    tmp = av_frame_alloc();
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = av_hwframe_map(tmp, src, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ cl_mem_flags opencl_mem_flags_for_mapping(ಪೂರ್ಣಾಙ್ಕ map_flags)
{
    ಯದಿ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ಪ್ರತ್ಯಾಗಮ CL_MEM_READ_WRITE;
    ಅನ್ಯಥಾ ಯದಿ (map_flags & AV_HWFRAME_MAP_READ)
        ಪ್ರತ್ಯಾಗಮ CL_MEM_READ_ONLY;
    ಅನ್ಯಥಾ ಯದಿ (map_flags & AV_HWFRAME_MAP_WRITE)
        ಪ್ರತ್ಯಾಗಮ CL_MEM_WRITE_ONLY;
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ಯದಿ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, p;

#ಯದಿ CONFIG_LIBMFX
    ಯದಿ (src->format == AV_PIX_FMT_QSV) {
        ಶೂನ್ಯ *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
        va_surface = *(VASurfaceID *)base_handle;
    } ಅನ್ಯಥಾ
#endif
        ಯದಿ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಯದಿ (!cl_flags)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(ಪರಿಮಾಣ(*desc));
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ಯದಿ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        ಗಚ್ಛ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++)
        ಯದಿ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, ಪರಿಮಾಣ(dst->data));
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif

#ಯದಿ HAVE_OPENCL_DXVA2

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ಯದಿ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            ಭಙ್ಗ;
    }
    ಯದಿ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, ಪರಿಮಾಣ(dst->data));
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, i, p, nb_planes;

    ಯದಿ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ಯದಿ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಯದಿ (!cl_flags)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  ಪರಿಮಾಣ(*frames_priv->mapped_frames));
    ಯದಿ (!frames_priv->mapped_frames)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ರಿಕ್ತ,
        };
        desc->nb_planes = nb_planes;
        ಪ್ರತಿ (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ಯದಿ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
            ಯದಿ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif

#ಯದಿ HAVE_OPENCL_D3D11

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, index, i;

    index = (intptr_t)src->data[1];
    ಯದಿ (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ರಿಕ್ತ, &event);
    ಯದಿ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, ಪರಿಮಾಣ(dst->data));
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, i, p, nb_planes;

    ಯದಿ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ಯದಿ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಯದಿ (!cl_flags)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  ಪರಿಮಾಣ(*frames_priv->mapped_frames));
    ಯದಿ (!frames_priv->mapped_frames)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        ಪ್ರತಿ (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ಯದಿ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned ಪೂರ್ಣಾಙ್ಕ)subresource, cle);
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        ಪ್ರತಿ (p = 0; p < desc->nb_planes; p++) {
            ಯದಿ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif

#ಯದಿ HAVE_OPENCL_DRM_ARM

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DRMARMtoOpenCLMapping {
    ಪೂರ್ಣಾಙ್ಕ nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    ಪೂರ್ಣಾಙ್ಕ nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    ಪ್ರತಿ (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ಧ್ರುವ AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ರಿಕ್ತ;
    cl_mem_flags cl_flags;
    ಧ್ರುವ cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    ಪೂರ್ಣಾಙ್ಕ err, i, j;

    desc = (ಧ್ರುವ AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ಯದಿ (!cl_flags)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    mapping = av_mallocz(ಪರಿಮಾಣ(*mapping));
    ಯದಿ (!mapping)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    ಪ್ರತಿ (i = 0; i < desc->nb_objects; i++) {
        ಪೂರ್ಣಾಙ್ಕ fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ಯದಿ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        ಯದಿ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }
    }

    mapping->nb_planes = 0;
    ಪ್ರತಿ (i = 0; i < desc->nb_layers; i++) {
        ಧ್ರುವ AVDRMLayerDescriptor *layer = &desc->layers[i];

        ಪ್ರತಿ (j = 0; j < layer->nb_planes; j++) {
            ಧ್ರುವ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            ಪೂರ್ಣಾಙ್ಕ p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            ಯದಿ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                ಗಚ್ಛ fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            ಯದಿ (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ರಿಕ್ತ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            ಯದಿ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ಗಚ್ಛ fail;
            }

            ++mapping->nb_planes;
        }
    }

    ಪ್ರತಿ (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    ಪ್ರತಿ (i = 0; i < mapping->nb_objects; i++) {
        ಯದಿ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, ಪರಿಮಾಣ(dst->data));
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif

#ಯದಿ HAVE_OPENCL_VIDEOTOOLBOX

ಸ್ಥಿರ ಶೂನ್ಯ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ರಿಕ್ತ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ಯದಿ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(ಪರಿಮಾಣ(*desc));
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ಯದಿ (err == AVERROR(ENOENT))
            ಭಙ್ಗ;
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ಯದಿ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            ಗಚ್ಛ fail;
        }
        desc->nb_planes++;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    dst->width = src->width;
    dst->height = src->height;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ಪ್ರತ್ಯಾಗಮ err;
}

#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ಯದಿ (hwfc->sw_format != dst->format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    ಪ್ರತ್ಯಾಗಮ opencl_map_frame(hwfc, dst, src, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    ವಿಕಲ್ಪ (src->format) {
#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಯದಿ (priv->beignet_drm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VAAPI_BEIGNET
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
        ಯದಿ (priv->beignet_drm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_vaapi(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಪಕ್ಷ AV_PIX_FMT_QSV:
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
        ಯದಿ (priv->qsv_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_qsv(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_DXVA2
    ಪಕ್ಷ AV_PIX_FMT_DXVA2_VLD:
        ಯದಿ (priv->dxva2_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_dxva2(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_D3D11
    ಪಕ್ಷ AV_PIX_FMT_D3D11:
        ಯದಿ (priv->d3d11_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_d3d11(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_DRM_ARM
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಯದಿ (priv->drm_arm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VIDEOTOOLBOX
    ಪಕ್ಷ AV_PIX_FMT_VIDEOTOOLBOX:
        ಪ್ರತ್ಯಾಗಮ opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    ವಿಕಲ್ಪ (src_fc->device_ctx->type) {
#ಯದಿ HAVE_OPENCL_DRM_BEIGNET
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DRM:
        ಯದಿ (!priv->beignet_drm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VAAPI_BEIGNET
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        ಯದಿ (!priv->beignet_drm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_QSV:
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        ಯದಿ (!priv->qsv_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        ಯದಿ (!priv->dxva2_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        {
            ಪೂರ್ಣಾಙ್ಕ err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            ಯದಿ (err < 0)
                ಪ್ರತ್ಯಾಗಮ err;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_D3D11
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        ಯದಿ (!priv->d3d11_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        {
            ಪೂರ್ಣಾಙ್ಕ err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            ಯದಿ (err < 0)
                ಪ್ರತ್ಯಾಗಮ err;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_DRM_ARM
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DRM:
        ಯದಿ (!priv->drm_arm_mapping_usable)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಭಙ್ಗ;
#endif
#ಯದಿ HAVE_OPENCL_VIDEOTOOLBOX
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
    ಪ್ರತ್ಯಾಗಮ opencl_frames_init_command_queue(dst_fc);
}

ಧ್ರುವ HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = ಪರಿಮಾಣ(OpenCLDeviceContext),
    .frames_hwctx_size      = ಪರಿಮಾಣ(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .frames_get_constraints = &opencl_frames_get_constraints,
    .frames_init            = &opencl_frames_init,
    .frames_uninit          = &opencl_frames_uninit,
    .frames_get_buffer      = &opencl_get_buffer,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_data_to       = &opencl_transfer_data_to,
    .transfer_data_from     = &opencl_transfer_data_from,

    .map_from               = &opencl_map_from,
    .map_to                 = &opencl_map_to,
    .frames_derive_to       = &opencl_frames_derive_to,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
