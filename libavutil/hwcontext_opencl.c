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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_opencl.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"

#ଯଦି HAVE_OPENCL_VAAPI_BEIGNET
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <va/va.h>
#ଅନ୍ତର୍ଭାଵ <va/va_drmcommon.h>
#ଅନ୍ତର୍ଭାଵ <CL/cl_intel.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_vaapi.h"
#endif

#ଯଦି HAVE_OPENCL_DRM_BEIGNET
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <CL/cl_intel.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_drm.h"
#endif

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ଯଦି CONFIG_LIBMFX
#ଅନ୍ତର୍ଭାଵ <mfxstructures.h>
#endif
#ଅନ୍ତର୍ଭାଵ <va/va.h>
#ଅନ୍ତର୍ଭାଵ <CL/cl_va_api_media_sharing_intel.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_vaapi.h"
#endif

#ଯଦି HAVE_OPENCL_DXVA2
#define COBJMACROS
#ଅନ୍ତର୍ଭାଵ <CL/cl_dx9_media_sharing.h>
#ଅନ୍ତର୍ଭାଵ <dxva2api.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_dxva2.h"
#endif

#ଯଦି HAVE_OPENCL_D3D11
#ଅନ୍ତର୍ଭାଵ <CL/cl_d3d11.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_d3d11va.h"
#endif

#ଯଦି HAVE_OPENCL_DRM_ARM
#ଅନ୍ତର୍ଭାଵ <CL/cl_ext.h>
#ଅନ୍ତର୍ଭାଵ <drm_fourcc.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_drm.h"
#endif

#ଯଦି HAVE_OPENCL_VIDEOTOOLBOX
#ଅନ୍ତର୍ଭାଵ <OpenCL/cl_gl_ext.h>
#ଅନ୍ତର୍ଭାଵ <VideoToolbox/VideoToolbox.h>
#endif

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ଗଣନା AVHWDeviceType base_dev_typ,
                                          ଶୂନ୍ୟ **base_handle);
#endif


ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା OpenCLDeviceContext {
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
#ଯଦି HAVE_OPENCL_DRM_BEIGNET
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#ଯଦି HAVE_OPENCL_DXVA2
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#ଯଦି HAVE_OPENCL_D3D11
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#ଯଦି HAVE_OPENCL_DRM_ARM
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#ଯଦି HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


ସ୍ଥିର ଶୂନ୍ୟ CL_CALLBACK opencl_error_callback(ଅଚଳ ଅକ୍ଷର *errinfo,
                                              ଅଚଳ ଶୂନ୍ୟ *private_info,
                                              size_t cb,
                                              ଶୂନ୍ୟ *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ସ୍ଥିର ଶୂନ୍ୟ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ସ୍ଥିର ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *ଚାବି;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ସ୍ଥିର ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *ଚାବି;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ସ୍ଥିର ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *ଚାବି;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ସ୍ଥିର ଅକ୍ଷର *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info ଚାବି)
{
    ଅକ୍ଷର *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, ଚାବି, 0, ଖାଲି, &size);
    ଯଦି (cle != CL_SUCCESS)
        ଫେରନ୍ତୁ ଖାଲି;
    str = av_malloc(size);
    ଯଦି (!str)
        ଫେରନ୍ତୁ ଖାଲି;
    cle = clGetPlatformInfo(platform_id, ଚାବି, size, str, &size);
    ଯଦି (cle != CL_SUCCESS) {
        av_free(str);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    av_assert0(strlen(str) + 1 == size);
    ଫେରନ୍ତୁ str;
}

ସ୍ଥିର ଅକ୍ଷର *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info ଚାବି)
{
    ଅକ୍ଷର *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, ଚାବି, 0, ଖାଲି, &size);
    ଯଦି (cle != CL_SUCCESS)
        ଫେରନ୍ତୁ ଖାଲି;
    str = av_malloc(size);
    ଯଦି (!str)
        ଫେରନ୍ତୁ ଖାଲି;
    cle = clGetDeviceInfo(device_id, ଚାବି, size, str, &size);
    ଯଦି (cle != CL_SUCCESS) {
        av_free(str);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    av_assert0(strlen(str) + 1== size);
    ଫେରନ୍ତୁ str;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_check_platform_extension(cl_platform_id platform_id,
                                           ଅଚଳ ଅକ୍ଷର *name)
{
    ଅକ୍ଷର *str;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ଯଦି (str && strstr(str, name))
        found = 1;
    av_free(str);
    ଫେରନ୍ତୁ found;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_check_device_extension(cl_device_id device_id,
                                         ଅଚଳ ଅକ୍ଷର *name)
{
    ଅକ୍ଷର *str;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ଯଦି (str && strstr(str, name))
        found = 1;
    av_free(str);
    ଫେରନ୍ତୁ found;
}

av_unused ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ଅଚଳ ଅକ୍ଷର *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ଯଦି (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ଫେରନ୍ତୁ 1;
    }

    ଯଦି (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ଫେରନ୍ତୁ 1;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      ଶୂନ୍ୟ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ଖାଲି, nb_platforms);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ଫେରନ୍ତୁ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, ଆକାର(**platforms));
    ଯଦି (!*platforms)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ଫେରନ୍ତୁ AVERROR(ENODEV);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ଅଚଳ ଅକ୍ଷର *platform_name,
                                  ଶୂନ୍ୟ *context)
{
    AVDictionary *opts = context;
    ଅଚଳ AVDictionaryEntry *param;
    ଅକ୍ଷର *str;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].ଚାବି,
                            ଖାଲି, 0);
        ଯଦି (!param)
            ଜାରି;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ଯଦି (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].ଚାବି, platform_name);
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
        }
        ଯଦି (!av_stristr(str, param->ମୂଲ୍ୟ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ଚାବି, str);
            ret = 1;
        }
        av_free(str);
    }

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ଅଚଳ ଅକ୍ଷର *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    ଶୂନ୍ୟ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ଖାଲି, nb_devices);
    ଯଦି (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ଫେରନ୍ତୁ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, ଆକାର(**devices));
    ଯଦି (!*devices)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ଫେରନ୍ତୁ AVERROR(ENODEV);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ଅଚଳ ଅକ୍ଷର *device_name,
                                ଶୂନ୍ୟ *context)
{
    AVDictionary *opts = context;
    ଅଚଳ AVDictionaryEntry *param;
    ଅକ୍ଷର *str;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;

    param = av_dict_get(opts, "device_type", ଖାଲି, 0);
    ଯଦି (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ଯଦି (!strcmp(opencl_device_types[i].ଚାବି, param->ମୂଲ୍ୟ)) {
                match_type = opencl_device_types[i].type;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->ମୂଲ୍ୟ);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              ଆକାର(device_type), &device_type, ଖାଲି);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
        }

        ଯଦି (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ଫେରନ୍ତୁ 1;
        }
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].ଚାବି,
                            ଖାଲି, 0);
        ଯଦି (!param)
            ଜାରି;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ଯଦି (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].ଚାବି, device_name);
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
        }
        ଯଦି (!av_stristr(str, param->ମୂଲ୍ୟ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ଚାବି, str);
            ret = 1;
        }
        av_free(str);
    }

    ଫେରନ୍ତୁ ret;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା OpenCLDeviceSelector {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା platform_index;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_index;
    ଶୂନ୍ୟ *context;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               ଶୂନ୍ୟ *context);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ଅଚଳ ଅକ୍ଷର *platform_name,
                               ଶୂନ୍ୟ *context);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ଅଚଳ ଅକ୍ଷର *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               ଶୂନ୍ୟ *context);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ଅଚଳ ଅକ୍ଷର *device_name,
                               ଶୂନ୍ୟ *context);
} OpenCLDeviceSelector;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ଅଚଳ OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ଖାଲି;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ଖାଲି;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    ଅକ୍ଷର *platform_name_src = ଖାଲି,
         *device_name_src   = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    found = 0;
    ପାଇଁ (p = 0; p < nb_platforms; p++) {
        ଅଚଳ ଅକ୍ଷର *platform_name;

        ଯଦି (selector->platform_index >= 0 &&
            selector->platform_index != p)
            ଜାରି;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ଯଦି (platform_name_src)
            platform_name = platform_name_src;
        ଅନ୍ୟଥା
            platform_name = "Unknown Platform";

        ଯଦି (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ଯଦି (err < 0)
                ଯାଅ fail;
            ଯଦି (err > 0)
                ଜାରି;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ଯଦି (err < 0)
            ଜାରି;

        ପାଇଁ (d = 0; d < nb_devices; d++) {
            ଅଚଳ ଅକ୍ଷର *device_name;

            ଯଦି (selector->device_index >= 0 &&
                selector->device_index != d)
                ଜାରି;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ଯଦି (device_name_src)
                device_name = device_name_src;
            ଅନ୍ୟଥା
                device_name = "Unknown Device";

            ଯଦି (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ଯଦି (err < 0)
                    ଯାଅ fail;
                ଯଦି (err > 0)
                    ଜାରି;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ଯଦି (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        ଯାଅ fail;
    }
    ଯଦି (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        ଯାଅ fail;
    }

    ଯଦି (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } ଅନ୍ୟଥା {
        ଯଦି (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ଯଦି (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        ଯାଅ fail;
    }

    hwdev->ମୁକ୍ତ = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_device_create(AVHWDeviceContext *hwdev, ଅଚଳ ଅକ୍ଷର *device,
                                AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ଯଦି (device && device[0]) {
        // Match one or both indices for platform and device.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା d = -1, p = -1, ret;
        ଯଦି (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        ଅନ୍ୟଥା
            ret = sscanf(device, "%d.%d", &p, &d);
        ଯଦି (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } ଅନ୍ୟଥା {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    ଫେରନ୍ତୁ opencl_device_create_internal(hwdev, &selector, ଖାଲି);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ଯଦି (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ଫେରନ୍ତୁ AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } ଅନ୍ୟଥା {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ଯଦି (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ଫେରନ୍ତୁ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          ଆକାର(priv->platform_id), &priv->platform_id,
                          ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

#define CL_FUNC(name, desc) କର {                                \
        ଯଦି (fail)                                               \
            ଭାଙ୍ଗ;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        ଯଦି (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } ଅନ୍ୟଥା {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ଯେତେବେଳେ (0)

#ଯଦି HAVE_OPENCL_DRM_BEIGNET
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ଯଦି (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } ଅନ୍ୟଥା {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = ଖାଲି;
        VADisplay va_display;
        ଅଚଳ ଅକ୍ଷର *va_ext = "cl_intel_va_api_media_sharing";
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, fail = 0;

        ଯଦି (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            ଯାଅ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ଖାଲି, &props_size);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ଯାଅ no_qsv;
        }
        ଯଦି (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ଯାଅ no_qsv;
        }

        props = av_malloc(props_size);
        ଯଦି (!props)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, ଖାଲି);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            ଯାଅ no_qsv;
        }

        va_display = ଖାଲି;
        ପାଇଁ (i = 0; i < (props_size / ଆକାର(*props) - 1); i++) {
            ଯଦି (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ଯାଅ no_qsv;
        }
        ଯଦି (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            ଯାଅ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        ଯଦି (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } ଅନ୍ୟଥା {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#ଯଦି HAVE_OPENCL_DXVA2
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        ଯଦି (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } ଅନ୍ୟଥା {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#ଯଦି HAVE_OPENCL_D3D11
    {
        ଅଚଳ ଅକ୍ଷର *d3d11_ext = "cl_khr_d3d11_sharing";
        ଅଚଳ ଅକ୍ଷର *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail = 0;

        ଯଦି (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } ଅନ୍ୟଥା ଯଦି (!opencl_check_extension(hwdev, nv12_ext)) {
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

        ଯଦି (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } ଅନ୍ୟଥା {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#ଯଦି HAVE_OPENCL_DRM_ARM
    {
        ଅଚଳ ଅକ୍ଷର *drm_arm_ext = "cl_arm_import_memory";
        ଅଚଳ ଅକ୍ଷର *image_ext   = "cl_khr_image2d_from_buffer";
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail = 0;

        ଯଦି (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ଯଦି (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ଯଦି (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } ଅନ୍ୟଥା {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ଯଦି (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = ଖାଲି;
    }
}

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ଅଚଳ ଅକ୍ଷର *platform_name,
                                                    ଶୂନ୍ୟ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ଯଦି (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ଫେରନ୍ତୁ 1;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ 0;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ଅଚଳ ଅକ୍ଷର *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      ଶୂନ୍ୟ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ଯଦି (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ଖାଲି, nb_devices);
    ଯଦି (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ଆକାର(**devices));
    ଯଦି (!*devices)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ଅଚଳ ଅକ୍ଷର *device_name,
                                                  ଶୂନ୍ୟ *context)
{
    ଅଚଳ ଅକ୍ଷର *va_ext = "cl_intel_va_api_media_sharing";

    ଯଦି (opencl_check_device_extension(device_id, va_ext)) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ଫେରନ୍ତୁ 1;
    }
}
#endif

#ଯଦି HAVE_OPENCL_DXVA2
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ଅଚଳ ଅକ୍ଷର *platform_name,
                                        ଶୂନ୍ୟ *context)
{
    ଅଚଳ ଅକ୍ଷର *dx9_ext = "cl_khr_dx9_media_sharing";

    ଯଦି (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ଫେରନ୍ତୁ 1;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ଅଚଳ ଅକ୍ଷର *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ଶୂନ୍ୟ *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ଯଦି (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ଶୂନ୍ୟ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ଖାଲି, nb_devices);
    ଯଦି (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ଆକାର(**devices));
    ଯଦି (!*devices)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ଶୂନ୍ୟ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}
#endif

#ଯଦି HAVE_OPENCL_D3D11
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ଅଚଳ ଅକ୍ଷର *platform_name,
                                        ଶୂନ୍ୟ *context)
{
    ଅଚଳ ଅକ୍ଷର *d3d11_ext = "cl_khr_d3d11_sharing";

    ଯଦି (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ଫେରନ୍ତୁ 1;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ଅଚଳ ଅକ୍ଷର *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ଶୂନ୍ୟ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ଯଦି (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ଖାଲି, nb_devices);
    ଯଦି (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, ଆକାର(**devices));
    ଯଦି (!*devices)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}
#endif

#ଯଦି HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ଅଚଳ ଅକ୍ଷର *device_name,
                                    ଶୂନ୍ୟ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          ଆକାର(device_type), &device_type, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }
    ଯଦି (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ଫେରନ୍ତୁ 1;
    }

    ଫେରନ୍ତୁ 0;
}
#endif

#ଯଦି HAVE_OPENCL_DRM_ARM
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ଅଚଳ ଅକ୍ଷର *platform_name,
                                          ଶୂନ୍ୟ *context)
{
    ଅଚଳ ଅକ୍ଷର *drm_arm_ext = "cl_arm_import_memory";

    ଯଦି (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ଫେରନ୍ତୁ 1;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ଅଚଳ ଅକ୍ଷର *device_name,
                                        ଶୂନ୍ୟ *context)
{
    ଅଚଳ ଅକ୍ଷର *drm_arm_ext = "cl_arm_import_memory";

    ଯଦି (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ଫେରନ୍ତୁ 1;
    }
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    ବାଛ (src_ctx->type) {

#ଯଦି HAVE_OPENCL_DRM_BEIGNET
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DRM:
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ଖାଲି;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            ଯଦି (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            ଯଦି (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ଖାଲି,
                };
                err = opencl_device_create_internal(hwdev, &selector, ଖାଲି);
            }
            av_dict_free(&selector_opts);
        }
        ଭାଙ୍ଗ;
#endif

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
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
        ଭାଙ୍ଗ;
#endif

#ଯଦି HAVE_OPENCL_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ଯଦି (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                ଭାଙ୍ଗ;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ଯଦି (SUCCEEDED(hr)) {
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
            } ଅନ୍ୟଥା {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ଭାଙ୍ଗ;
#endif

#ଯଦି HAVE_OPENCL_D3D11
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
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
        ଭାଙ୍ଗ;
#endif

#ଯଦି HAVE_OPENCL_DRM_ARM
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = ଖାଲି,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, ଖାଲି);
        }
        ଭାଙ୍ଗ;
#endif

#ଯଦି HAVE_OPENCL_VIDEOTOOLBOX
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ଖାଲି, ଖାଲି, 0);
        ଭାଙ୍ଗ;
#endif

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        err = AVERROR(ENOSYS);
        ଭାଙ୍ଗ;
    }

    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_get_plane_format(ଗଣନା AVPixelFormat pixfmt,
                                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ଅଚଳ AVPixFmtDescriptor *desc;
    ଅଚଳ AVComponentDescriptor *comp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels = 0, order = 0, depth = 0, step = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା wsub, hsub, alpha;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    ଯଦି (plane >= AV_ଅଙ୍କ_DATA_POINTERS)
        ଫେରନ୍ତୁ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ଯଦି (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ଯଦି (width & wsub - 1 || height & hsub - 1)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ଯଦି (comp->plane != plane)
            ଜାରି;
        // The step size must be a power of two.
        ଯଦି (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ଯଦି (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        // The depth must not vary between components.
        ଯଦି (depth && comp->depth != depth)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ଯଦି (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ଯଦି (step && comp->step != step)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ଯଦି (channels == 0)
        ଫେରନ୍ତୁ AVERROR(ENOENT);

    memset(image_format, 0, ଆକାର(*image_format));
    memset(image_desc,   0, ଆକାର(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ଯଦି (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } ଅନ୍ୟଥା {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    ଯଦି (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } ଅନ୍ୟଥା {
        ଯଦି (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        ଅନ୍ୟଥା ଯଦି (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    ସ୍ଥିତି order: image_format->image_channel_order = type; ଭାଙ୍ଗ;
    ବାଛ (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ଖାଲି;
    cl_int cle;
    ଗଣନା AVPixelFormat pix_fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          ଆକାର(max_width), &max_width, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } ଅନ୍ୟଥା {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          ଆକାର(max_height), &max_height, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } ଅନ୍ୟଥା {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ଖାଲି, &nb_image_formats);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ଯାଅ fail;
    }
    ଯଦି (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, ଆକାର(*image_formats));
    ଯଦି (!image_formats) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ଖାଲି);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    pix_fmts_found = 0;
    ପାଇଁ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane, i;

        ପାଇଁ (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ଯଦି (err < 0)
                ଭାଙ୍ଗ;

            ପାଇଁ (i = 0; i < nb_image_formats; i++) {
                ଯଦି (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    ଭାଙ୍ଗ;
            }
            ଯଦି (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (err != AVERROR(ENOENT))
            ଜାରି;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                ଆକାର(*constraints->valid_sw_formats));
        ଯଦି (err < 0)
            ଯାଅ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
    ଯଦି (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;

fail:
    av_freep(&image_formats);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଶୂନ୍ୟ opencl_pool_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା p;

    ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ସ୍ଥିର AVBufferRef *opencl_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, p;
    AVBufferRef *ref;

    desc = av_mallocz(ଆକାର(*desc));
    ଯଦି (!desc)
        ଫେରନ୍ତୁ ଖାଲି;

    ପାଇଁ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        ଯଦି (err == AVERROR(ENOENT))
            ଭାଙ୍ଗ;
        ଯଦି (err < 0)
            ଯାଅ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ଖାଲି, &cle);
        ଯଦି (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            ଯାଅ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, ଆକାର(*desc),
                           &opencl_pool_free, hwfc, 0);
    ଯଦି (!ref)
        ଯାଅ fail;

    ଫେରନ୍ତୁ ref;

fail:
    ପାଇଁ (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_init(AVHWFramesContext *hwfc)
{
    ଯଦି (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(ଆକାର(cl_mem), hwfc,
                                 &opencl_pool_alloc, ଖାଲି);
        ଯଦି (!ffhwframesctx(hwfc)->pool_internal)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ଫେରନ୍ତୁ opencl_frames_init_command_queue(hwfc);
}

ସ୍ଥିର ଶୂନ୍ୟ opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ଯଦି HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, p;
    ପାଇଁ (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ଯଦି (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    ଯଦି (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = ଖାଲି;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    ପାଇଁ (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ଗଣନା AVHWFrameTransferDirection dir,
                                       ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_events)
{
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    cle = clWaitForEvents(nb_events, events);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

    ପାଇଁ (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ଅଚଳ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, p;

    ଯଦି (dst->format != hwfc->sw_format)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ଯଦି (err < 0) {
            ଯଦି (err == AVERROR(ENOENT))
                err = 0;
            ଭାଙ୍ଗ;
        }

        ଯଦି (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ଭାଙ୍ଗ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, ଖାଲି, &events[p]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ଭାଙ୍ଗ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ଅଚଳ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, p;

    ଯଦି (src->format != hwfc->sw_format)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ଯଦି (err < 0) {
            ଯଦି (err == AVERROR(ENOENT))
                err = 0;
            ଭାଙ୍ଗ;
        }

        ଯଦି (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ଭାଙ୍ଗ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, ଖାଲି, &events[p]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ଭାଙ୍ଗ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ଫେରନ୍ତୁ err;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    ଶୂନ୍ୟ *address[AV_ଅଙ୍କ_DATA_POINTERS];
} OpenCLMapping;

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା p, e;
    cl_int cle;

    ପାଇଁ (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        ଯଦି (!map->address[p])
            ଭାଙ୍ଗ;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, ଖାଲି, &events[e]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
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
    cl_event events[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ଯଦି (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } ଅନ୍ୟଥା {
        map_flags = 0;
        ଯଦି (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(ଆକାର(*map));
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ଯଦି (err == AVERROR(ENOENT))
            ଭାଙ୍ଗ;
        ଯଦି (err < 0)
            ଯାଅ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, ଖାଲି, 0, ଖାଲି,
                              &events[p], &cle);
        ଯଦି (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ଯାଅ fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (p = 0; p < AV_ଅଙ୍କ_DATA_POINTERS; p++) {
        ଯଦି (!map->address[p])
            ଭାଙ୍ଗ;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, ଖାଲି, &events[p]);
    }
    ଯଦି (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ଫେରନ୍ତୁ err;
}

#ଯଦି HAVE_OPENCL_DRM_BEIGNET

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ଅଚଳ AVFrame *src,
                                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ଅଚଳ AVDRMFrameDescriptor *desc;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, j, p;

    desc = (ଅଚଳ AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(ଆକାର(*mapping));
    ଯଦି (!mapping)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    p = 0;
    ପାଇଁ (i = 0; i < desc->nb_layers; i++) {
        ଅଚଳ AVDRMLayerDescriptor *layer = &desc->layers[i];
        ପାଇଁ (j = 0; j < layer->nb_planes; j++) {
            ଅଚଳ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ଅଚଳ AVDRMObjectDescriptor *object =
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
            ଯଦି (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                ଯାଅ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ଯଦି (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                ଯାଅ fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (p = 0; p < mapping->frame.nb_planes; p++) {
        ଯଦି (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, ଆକାର(dst->data));
    ଫେରନ୍ତୁ err;
}

#ଯଦି HAVE_OPENCL_VAAPI_BEIGNET

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ଅଚଳ AVFrame *src,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVFrame *tmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    tmp = av_frame_alloc();
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ମୌଳିକ;

    err = av_hwframe_map(tmp, src, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ଫେରନ୍ତୁ err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ cl_mem_flags opencl_mem_flags_for_mapping(ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_flags)
{
    ଯଦି ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ଫେରନ୍ତୁ CL_MEM_READ_WRITE;
    ଅନ୍ୟଥା ଯଦି (map_flags & AV_HWFRAME_MAP_READ)
        ଫେରନ୍ତୁ CL_MEM_READ_ONLY;
    ଅନ୍ୟଥା ଯଦି (map_flags & AV_HWFRAME_MAP_WRITE)
        ଫେରନ୍ତୁ CL_MEM_WRITE_ONLY;
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ 0;
}

#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ଯଦି (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, p;

#ଯଦି CONFIG_LIBMFX
    ଯଦି (src->format == AV_PIX_FMT_QSV) {
        ଶୂନ୍ୟ *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        ଯଦି (err < 0)
            ଫେରନ୍ତୁ err;
        va_surface = *(VASurfaceID *)base_handle;
    } ଅନ୍ୟଥା
#endif
        ଯଦି (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ଯଦି (!cl_flags)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(ଆକାର(*desc));
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ଯଦି (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            ଯାଅ fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        ଯାଅ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (p = 0; p < desc->nb_planes; p++)
        ଯଦି (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, ଆକାର(dst->data));
    ଫେରନ୍ତୁ err;
}

#endif

#ଯଦି HAVE_OPENCL_DXVA2

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ଫେରନ୍ତୁ;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ଯଦି (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            ଭାଙ୍ଗ;
    }
    ଯଦି (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, ଆକାର(dst->data));
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, p, nb_planes;

    ଯଦି (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ଯଦି (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ଯଦି (!cl_flags)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  ଆକାର(*frames_priv->mapped_frames));
    ଯଦି (!frames_priv->mapped_frames)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ଖାଲି,
        };
        desc->nb_planes = nb_planes;
        ପାଇଁ (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ଯଦି (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                ଯାଅ fail;
            }
        }
    }

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
            ଯଦି (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ଫେରନ୍ତୁ err;
}

#endif

#ଯଦି HAVE_OPENCL_D3D11

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, index, i;

    index = (intptr_t)src->data[1];
    ଯଦି (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ଫେରନ୍ତୁ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ଖାଲି, &event);
    ଯଦି (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, ଆକାର(dst->data));
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, p, nb_planes;

    ଯଦି (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ଯଦି (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ଯଦି (!cl_flags)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  ଆକାର(*frames_priv->mapped_frames));
    ଯଦି (!frames_priv->mapped_frames)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        ପାଇଁ (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ଯଦି (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)subresource, cle);
                err = AVERROR(EIO);
                ଯାଅ fail;
            }
        }
    }

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        ପାଇଁ (p = 0; p < desc->nb_planes; p++) {
            ଯଦି (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ଫେରନ୍ତୁ err;
}

#endif

#ଯଦି HAVE_OPENCL_DRM_ARM

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା DRMARMtoOpenCLMapping {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    ପାଇଁ (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ଅଚଳ AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ଖାଲି;
    cl_mem_flags cl_flags;
    ଅଚଳ cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, i, j;

    desc = (ଅଚଳ AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ଯଦି (!cl_flags)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    mapping = av_mallocz(ଆକାର(*mapping));
    ଯଦି (!mapping)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    ପାଇଁ (i = 0; i < desc->nb_objects; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ଯଦି (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        ଯଦି (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            ଯାଅ fail;
        }
    }

    mapping->nb_planes = 0;
    ପାଇଁ (i = 0; i < desc->nb_layers; i++) {
        ଅଚଳ AVDRMLayerDescriptor *layer = &desc->layers[i];

        ପାଇଁ (j = 0; j < layer->nb_planes; j++) {
            ଅଚଳ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            ଯଦି (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                ଯାଅ fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            ଯଦି (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ଯାଅ fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ଖାଲି, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            ଯଦି (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                ଯାଅ fail;
            }

            ++mapping->nb_planes;
        }
    }

    ପାଇଁ (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width  = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    ପାଇଁ (i = 0; i < mapping->nb_objects; i++) {
        ଯଦି (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, ଆକାର(dst->data));
    ଫେରନ୍ତୁ err;
}

#endif

#ଯଦି HAVE_OPENCL_VIDEOTOOLBOX

ସ୍ଥିର ଶୂନ୍ୟ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ଖାଲି;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ଯଦି (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(ଆକାର(*desc));
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା p = 0;; p++) {
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
        ଯଦି (err == AVERROR(ENOENT))
            ଭାଙ୍ଗ;
        ଯଦି (err < 0)
            ଯାଅ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ଯଦି (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            ଯାଅ fail;
        }
        desc->nb_planes++;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ଯଦି (err < 0)
        ଯାଅ fail;

    dst->width = src->width;
    dst->height = src->height;

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ଫେରନ୍ତୁ err;
}

#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ଯଦି (hwfc->sw_format != dst->format)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    ଫେରନ୍ତୁ opencl_map_frame(hwfc, dst, src, flags);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    ବାଛ (src->format) {
#ଯଦି HAVE_OPENCL_DRM_BEIGNET
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଯଦି (priv->beignet_drm_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VAAPI_BEIGNET
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
        ଯଦି (priv->beignet_drm_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_vaapi(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ସ୍ଥିତି AV_PIX_FMT_QSV:
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
        ଯଦି (priv->qsv_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_qsv(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_DXVA2
    ସ୍ଥିତି AV_PIX_FMT_DXVA2_VLD:
        ଯଦି (priv->dxva2_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_dxva2(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_D3D11
    ସ୍ଥିତି AV_PIX_FMT_D3D11:
        ଯଦି (priv->d3d11_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_d3d11(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_DRM_ARM
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଯଦି (priv->drm_arm_mapping_usable)
            ଫେରନ୍ତୁ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VIDEOTOOLBOX
    ସ୍ଥିତି AV_PIX_FMT_VIDEOTOOLBOX:
        ଫେରନ୍ତୁ opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    ବାଛ (src_fc->device_ctx->type) {
#ଯଦି HAVE_OPENCL_DRM_BEIGNET
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DRM:
        ଯଦି (!priv->beignet_drm_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VAAPI_BEIGNET
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        ଯଦି (!priv->beignet_drm_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_QSV:
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        ଯଦି (!priv->qsv_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        ଯଦି (!priv->dxva2_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            ଯଦି (err < 0)
                ଫେରନ୍ତୁ err;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_D3D11
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        ଯଦି (!priv->d3d11_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            ଯଦି (err < 0)
                ଫେରନ୍ତୁ err;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_DRM_ARM
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DRM:
        ଯଦି (!priv->drm_arm_mapping_usable)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଭାଙ୍ଗ;
#endif
#ଯଦି HAVE_OPENCL_VIDEOTOOLBOX
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
    ଫେରନ୍ତୁ opencl_frames_init_command_queue(dst_fc);
}

ଅଚଳ HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = ଆକାର(OpenCLDeviceContext),
    .frames_hwctx_size      = ଆକାର(OpenCLFramesContext),

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

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
