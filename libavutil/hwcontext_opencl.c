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

#నిర్వచించు CL_USE_DEPRECATED_OPENCL_1_2_APIS

#అన్తర్భావ <string.h>

#అన్తర్భావ "config.h"

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_opencl.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"

#ఒకవేళ HAVE_OPENCL_VAAPI_BEIGNET
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <va/va.h>
#అన్తర్భావ <va/va_drmcommon.h>
#అన్తర్భావ <CL/cl_intel.h>
#అన్తర్భావ "hwcontext_vaapi.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <CL/cl_intel.h>
#అన్తర్భావ "hwcontext_drm.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ఒకవేళ CONFIG_LIBMFX
#అన్తర్భావ <mfxstructures.h>
#అయితే_ముగింపు
#అన్తర్భావ <va/va.h>
#అన్తర్భావ <CL/cl_va_api_media_sharing_intel.h>
#అన్తర్భావ "hwcontext_vaapi.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2
#నిర్వచించు COBJMACROS
#అన్తర్భావ <CL/cl_dx9_media_sharing.h>
#అన్తర్భావ <dxva2api.h>
#అన్తర్భావ "hwcontext_dxva2.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11
#అన్తర్భావ <CL/cl_d3d11.h>
#అన్తర్భావ "hwcontext_d3d11va.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM
#అన్తర్భావ <CL/cl_ext.h>
#అన్తర్భావ <drm_fourcc.h>
#అన్తర్భావ "hwcontext_drm.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VIDEOTOOLBOX
#అన్తర్భావ <OpenCL/cl_gl_ext.h>
#అన్తర్భావ <VideoToolbox/VideoToolbox.h>
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
బాహ్య పూర్ణాంకం ff_qsv_get_surface_పునాది_handle(mfx_చట్రం_Surface1 *surf,
                                          గణన AVHWDeviceType పునాది_dev_typ,
                                          శూన్య **పునాది_handle);
#అయితే_ముగింపు


రకనిర్వచనం నిర్మాణం OpenCLDeviceContext {
    /**
     * The public AVOpenCLDeviceContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLDeviceContext p;

    // Default command queue to use for transfer/mapping operations on
    // the device.  If the user supplies one, this is a reference to it.
    // Otherwise, it is newly-created.
    cl_command_వరుస command_వరుస;

    // The platform the context exists on.  This is needed to query and
    // retrieve extension functions.
    cl_platform_id platform_id;

    // Platform/device-specific functions.
#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
    పూర్ణాంకం beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    పూర్ణాంకం qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_వరుసలో_చేర్చు_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_వరుసలో_చేర్చు_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_వరుసలో_చేర్చు_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_వరుసలో_చేర్చు_Release_VA_APIMedia_Surfaces_INTEL;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2
    పూర్ణాంకం dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_వరుసలో_చేర్చు_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_వరుసలో_చేర్చు_Acquire_DX9_Media_Surfaces_KHR;
    cl_వరుసలో_చేర్చు_Release_DX9_Media_Surfaces_KHR_fn
        cl_వరుసలో_చేర్చు_Release_DX9_Media_Surfaces_KHR;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11
    పూర్ణాంకం d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_వరుసలో_చేర్చు_Acquire_D3_D11_Objects_KHR_fn
        cl_వరుసలో_చేర్చు_Acquire_D3_D11_Objects_KHR;
    cl_వరుసలో_చేర్చు_Release_D3_D11_Objects_KHR_fn
        cl_వరుసలో_చేర్చు_Release_D3_D11_Objects_KHR;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM
    పూర్ణాంకం drm_arm_mapping_usable;
#అయితే_ముగింపు
} OpenCLDeviceContext;

రకనిర్వచనం నిర్మాణం OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_వరుస command_వరుస;

#ఒకవేళ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    పూర్ణాంకం                   nb_mapped_చట్రాలు;
    AVOpenCLFrameDescriptor *mapped_చట్రాలు;
#అయితే_ముగింపు
} OpenCLFramesContext;


స్థిర శూన్య CL_CALLBACK opencl_error_callback(స్థిరరాశి అక్షరం *errinfo,
                                              స్థిరరాశి శూన్య *వ్యక్తిగత_info,
                                              size_t cb,
                                              శూన్య *user_దత్తాంశం)
{
    AVHWDeviceContext *ctx = user_దత్తాంశం;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

స్థిర శూన్య opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

స్థిర నిర్మాణం {
    స్థిరరాశి అక్షరం *కీలకం;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_సంస్కరణ    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

స్థిర నిర్మాణం {
    స్థిరరాశి అక్షరం *కీలకం;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_సంస్కరణ      },
    { "device_version",      CL_DEVICE_సంస్కరణ      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

స్థిర నిర్మాణం {
    స్థిరరాశి అక్షరం *కీలకం;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

స్థిర అక్షరం *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info కీలకం)
{
    అక్షరం *str;
    size_t కొలత;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, కీలకం, 0, ఖాళీ, &కొలత);
    ఒకవేళ (cle != CL_SUCCESS)
        తిరిగి ఖాళీ;
    str = av_malloc(కొలత);
    ఒకవేళ (!str)
        తిరిగి ఖాళీ;
    cle = clGetPlatformInfo(platform_id, కీలకం, కొలత, str, &కొలత);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_free(str);
        తిరిగి ఖాళీ;
    }
    av_assert0(అక్షరశ్రేణి_పొడవు(str) + 1 == కొలత);
    తిరిగి str;
}

స్థిర అక్షరం *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info కీలకం)
{
    అక్షరం *str;
    size_t కొలత;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, కీలకం, 0, ఖాళీ, &కొలత);
    ఒకవేళ (cle != CL_SUCCESS)
        తిరిగి ఖాళీ;
    str = av_malloc(కొలత);
    ఒకవేళ (!str)
        తిరిగి ఖాళీ;
    cle = clGetDeviceInfo(device_id, కీలకం, కొలత, str, &కొలత);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_free(str);
        తిరిగి ఖాళీ;
    }
    av_assert0(అక్షరశ్రేణి_పొడవు(str) + 1== కొలత);
    తిరిగి str;
}

స్థిర పూర్ణాంకం opencl_check_platform_extension(cl_platform_id platform_id,
                                           స్థిరరాశి అక్షరం *name)
{
    అక్షరం *str;
    పూర్ణాంకం దొరికింది = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ఒకవేళ (str && అక్షరశ్రేణి_శోధన(str, name))
        దొరికింది = 1;
    av_free(str);
    తిరిగి దొరికింది;
}

స్థిర పూర్ణాంకం opencl_check_device_extension(cl_device_id device_id,
                                         స్థిరరాశి అక్షరం *name)
{
    అక్షరం *str;
    పూర్ణాంకం దొరికింది = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ఒకవేళ (str && అక్షరశ్రేణి_శోధన(str, name))
        దొరికింది = 1;
    av_free(str);
    తిరిగి దొరికింది;
}

av_వాడని స్థిర పూర్ణాంకం opencl_check_extension(AVHWDeviceContext *hwdev,
                                            స్థిరరాశి అక్షరం *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ఒకవేళ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        తిరిగి 1;
    }

    ఒకవేళ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        తిరిగి 1;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      శూన్య *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ఖాళీ, nb_platforms);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        తిరిగి AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, పరిమాణం(**platforms));
    ఒకవేళ (!*platforms)
        తిరిగి AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        తిరిగి AVERROR(ENODEV);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  స్థిరరాశి అక్షరం *platform_name,
                                  శూన్య *context)
{
    AVDictionary *opts = context;
    స్థిరరాశి AVDictionary_నమోదు *param;
    అక్షరం *str;
    పూర్ణాంకం i, ret = 0;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].కీలకం,
                            ఖాళీ, 0);
        ఒకవేళ (!param)
            కొనసాగు;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ఒకవేళ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].కీలకం, platform_name);
            తిరిగి AVERROR_UNKNOWN;
        }
        ఒకవేళ (!av_stristr(str, param->విలువ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->కీలకం, str);
            ret = 1;
        }
        av_free(str);
    }

    తిరిగి ret;
}

స్థిర పూర్ణాంకం opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    స్థిరరాశి అక్షరం *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    శూన్య *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ఖాళీ, nb_devices);
    ఒకవేళ (cle == CL_DEVICE_NOT_దొరికింది) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        తిరిగి AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, పరిమాణం(**devices));
    ఒకవేళ (!*devices)
        తిరిగి AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        తిరిగి AVERROR(ENODEV);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                స్థిరరాశి అక్షరం *device_name,
                                శూన్య *context)
{
    AVDictionary *opts = context;
    స్థిరరాశి AVDictionary_నమోదు *param;
    అక్షరం *str;
    పూర్ణాంకం i, ret = 0;

    param = av_dict_get(opts, "device_type", ఖాళీ, 0);
    ఒకవేళ (param) {
        cl_device_type సరిపోలిక_type = 0, device_type;
        cl_int cle;

        కొరకు (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ఒకవేళ (!strcmp(opencl_device_types[i].కీలకం, param->విలువ)) {
                సరిపోలిక_type = opencl_device_types[i].type;
                ఆపు;
            }
        }
        ఒకవేళ (!సరిపోలిక_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->విలువ);
            తిరిగి AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              పరిమాణం(device_type), &device_type, ఖాళీ);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            తిరిగి AVERROR_UNKNOWN;
        }

        ఒకవేళ (!(device_type & సరిపోలిక_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            తిరిగి 1;
        }
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].కీలకం,
                            ఖాళీ, 0);
        ఒకవేళ (!param)
            కొనసాగు;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ఒకవేళ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].కీలకం, device_name);
            తిరిగి AVERROR_UNKNOWN;
        }
        ఒకవేళ (!av_stristr(str, param->విలువ)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->కీలకం, str);
            ret = 1;
        }
        av_free(str);
    }

    తిరిగి ret;
}

రకనిర్వచనం నిర్మాణం OpenCLDeviceSelector {
    పూర్ణాంకం platform_సూచీ;
    పూర్ణాంకం device_సూచీ;
    శూన్య *context;
    పూర్ణాంకం (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               శూన్య *context);
    పూర్ణాంకం (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               స్థిరరాశి అక్షరం *platform_name,
                               శూన్య *context);
    పూర్ణాంకం (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               స్థిరరాశి అక్షరం *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               శూన్య *context);
    పూర్ణాంకం (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               స్థిరరాశి అక్షరం *device_name,
                               శూన్య *context);
} OpenCLDeviceSelector;

స్థిర పూర్ణాంకం opencl_device_create_అంతర్గత(AVHWDeviceContext *hwdev,
                                         స్థిరరాశి OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ఖాళీ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ఖాళీ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    అక్షరం *platform_name_src = ఖాళీ,
         *device_name_src   = ఖాళీ;
    పూర్ణాంకం err, దొరికింది, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ఒకవేళ (err)
        తిరిగి err;

    దొరికింది = 0;
    కొరకు (p = 0; p < nb_platforms; p++) {
        స్థిరరాశి అక్షరం *platform_name;

        ఒకవేళ (selector->platform_సూచీ >= 0 &&
            selector->platform_సూచీ != p)
            కొనసాగు;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ఒకవేళ (platform_name_src)
            platform_name = platform_name_src;
        లేకపోతే
            platform_name = "Unknown Platform";

        ఒకవేళ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ఒకవేళ (err < 0)
                వెళ్ళు fail;
            ఒకవేళ (err > 0)
                కొనసాగు;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ఒకవేళ (err < 0)
            కొనసాగు;

        కొరకు (d = 0; d < nb_devices; d++) {
            స్థిరరాశి అక్షరం *device_name;

            ఒకవేళ (selector->device_సూచీ >= 0 &&
                selector->device_సూచీ != d)
                కొనసాగు;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ఒకవేళ (device_name_src)
                device_name = device_name_src;
            లేకపోతే
                device_name = "Unknown Device";

            ఒకవేళ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ఒకవేళ (err < 0)
                    వెళ్ళు fail;
                ఒకవేళ (err > 0)
                    కొనసాగు;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++దొరికింది;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ఒకవేళ (దొరికింది == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        వెళ్ళు fail;
    }
    ఒకవేళ (దొరికింది > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        వెళ్ళు fail;
    }

    ఒకవేళ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } లేకపోతే {
        ఒకవేళ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ఒకవేళ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        వెళ్ళు fail;
    }

    hwdev->విడుదల = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    తిరిగి err;
}

స్థిర పూర్ణాంకం opencl_device_create(AVHWDeviceContext *hwdev, స్థిరరాశి అక్షరం *device,
                                AVDictionary *opts, పూర్ణాంకం flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ఒకవేళ (device && device[0]) {
        // Match one or both indices for platform and device.
        పూర్ణాంకం d = -1, p = -1, ret;
        ఒకవేళ (device[0] == '.')
            ret = అక్షరశ్రేణి_చదువు(device, ".%d", &d);
        లేకపోతే
            ret = అక్షరశ్రేణి_చదువు(device, "%d.%d", &p, &d);
        ఒకవేళ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            తిరిగి AVERROR(EINVAL);
        }
        selector.platform_సూచీ = p;
        selector.device_సూచీ   = d;
    } లేకపోతే {
        selector.platform_సూచీ = -1;
        selector.device_సూచీ   = -1;
    }

    తిరిగి opencl_device_create_అంతర్గత(hwdev, &selector, ఖాళీ);
}

స్థిర పూర్ణాంకం opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ఒకవేళ (hwctx->command_వరుస) {
        cle = cl_Retain_Command_వరుస(hwctx->command_వరుస);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            తిరిగి AVERROR(EIO);
        }
        priv->command_వరుస = hwctx->command_వరుస;
    } లేకపోతే {
        priv->command_వరుస = cl_Create_Command_వరుస(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ఒకవేళ (!priv->command_వరుస) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            తిరిగి AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          పరిమాణం(priv->platform_id), &priv->platform_id,
                          ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        తిరిగి AVERROR(EIO);
    }

#నిర్వచించు CL_FUNC(name, desc) చేయి {                                \
        ఒకవేళ (fail)                                               \
            ఆపు;                                              \
        priv->name = cl_Get_Extension_Function_చిరునామా_For_Platform(  \
            priv->platform_id, #name);                          \
        ఒకవేళ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } లేకపోతే {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } అయితే (0)

#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
    {
        పూర్ణాంకం fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ఒకవేళ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } లేకపోతే {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_కొలత;
        cl_context_properties *props = ఖాళీ;
        VADisplay va_display;
        స్థిరరాశి అక్షరం *va_ext = "cl_intel_va_api_media_sharing";
        పూర్ణాంకం i, fail = 0;

        ఒకవేళ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            వెళ్ళు no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ఖాళీ, &props_కొలత);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            వెళ్ళు no_qsv;
        }
        ఒకవేళ (props_కొలత == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            వెళ్ళు no_qsv;
        }

        props = av_malloc(props_కొలత);
        ఒకవేళ (!props)
            తిరిగి AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_కొలత, props, ఖాళీ);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            వెళ్ళు no_qsv;
        }

        va_display = ఖాళీ;
        కొరకు (i = 0; i < (props_కొలత / పరిమాణం(*props) - 1); i++) {
            ఒకవేళ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ఆపు;
            }
        }
        ఒకవేళ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            వెళ్ళు no_qsv;
        }
        ఒకవేళ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            వెళ్ళు no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_వరుసలో_చేర్చు_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_వరుసలో_చేర్చు_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        ఒకవేళ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } లేకపోతే {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2
    {
        పూర్ణాంకం fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_వరుసలో_చేర్చు_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_వరుసలో_చేర్చు_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        ఒకవేళ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } లేకపోతే {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11
    {
        స్థిరరాశి అక్షరం *d3d11_ext = "cl_khr_d3d11_sharing";
        స్థిరరాశి అక్షరం *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        పూర్ణాంకం fail = 0;

        ఒకవేళ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } లేకపోతే ఒకవేళ (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_వరుసలో_చేర్చు_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_వరుసలో_చేర్చు_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        ఒకవేళ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } లేకపోతే {
            priv->d3d11_mapping_usable = 1;
        }
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM
    {
        స్థిరరాశి అక్షరం *drm_arm_ext = "cl_arm_import_memory";
        స్థిరరాశి అక్షరం *image_ext   = "cl_khr_image2d_from_buffer";
        పూర్ణాంకం fail = 0;

        ఒకవేళ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ఒకవేళ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ఒకవేళ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } లేకపోతే {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#అయితే_ముగింపు

#నిర్వచనం_రద్దు CL_FUNC

    తిరిగి 0;
}

స్థిర శూన్య opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ఒకవేళ (priv->command_వరుస) {
        cle = cl_Release_Command_వరుస(priv->command_వరుస);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_వరుస = ఖాళీ;
    }
}

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
స్థిర పూర్ణాంకం opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    స్థిరరాశి అక్షరం *platform_name,
                                                    శూన్య *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ఒకవేళ (!cl_Get_Extension_Function_చిరునామా_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        తిరిగి 1;
    } లేకపోతే {
        తిరిగి 0;
    }
}

స్థిర పూర్ణాంకం opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      స్థిరరాశి అక్షరం *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      శూన్య *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        cl_Get_Extension_Function_చిరునామా_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ఒకవేళ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ఖాళీ, nb_devices);
    ఒకవేళ (cle == CL_DEVICE_NOT_దొరికింది) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        తిరిగి AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, పరిమాణం(**devices));
    ఒకవేళ (!*devices)
        తిరిగి AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  స్థిరరాశి అక్షరం *device_name,
                                                  శూన్య *context)
{
    స్థిరరాశి అక్షరం *va_ext = "cl_intel_va_api_media_sharing";

    ఒకవేళ (opencl_check_device_extension(device_id, va_ext)) {
        తిరిగి 0;
    } లేకపోతే {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        తిరిగి 1;
    }
}
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2
స్థిర పూర్ణాంకం opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        స్థిరరాశి అక్షరం *platform_name,
                                        శూన్య *context)
{
    స్థిరరాశి అక్షరం *dx9_ext = "cl_khr_dx9_media_sharing";

    ఒకవేళ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        తిరిగి 0;
    } లేకపోతే {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        తిరిగి 1;
    }
}

స్థిర పూర్ణాంకం opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          స్థిరరాశి అక్షరం *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          శూన్య *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        cl_Get_Extension_Function_చిరునామా_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ఒకవేళ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (శూన్య**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ఖాళీ, nb_devices);
    ఒకవేళ (cle == CL_DEVICE_NOT_దొరికింది) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        తిరిగి AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, పరిమాణం(**devices));
    ఒకవేళ (!*devices)
        తిరిగి AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (శూన్య**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11
స్థిర పూర్ణాంకం opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        స్థిరరాశి అక్షరం *platform_name,
                                        శూన్య *context)
{
    స్థిరరాశి అక్షరం *d3d11_ext = "cl_khr_d3d11_sharing";

    ఒకవేళ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        తిరిగి 0;
    } లేకపోతే {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        తిరిగి 1;
    }
}

స్థిర పూర్ణాంకం opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          స్థిరరాశి అక్షరం *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          శూన్య *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        cl_Get_Extension_Function_చిరునామా_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ఒకవేళ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ఖాళీ, nb_devices);
    ఒకవేళ (cle == CL_DEVICE_NOT_దొరికింది) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        తిరిగి AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, పరిమాణం(**devices));
    ఒకవేళ (!*devices)
        తిరిగి AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
స్థిర పూర్ణాంకం opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    స్థిరరాశి అక్షరం *device_name,
                                    శూన్య *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          పరిమాణం(device_type), &device_type, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        తిరిగి AVERROR_UNKNOWN;
    }
    ఒకవేళ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        తిరిగి 1;
    }

    తిరిగి 0;
}
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM
స్థిర పూర్ణాంకం opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          స్థిరరాశి అక్షరం *platform_name,
                                          శూన్య *context)
{
    స్థిరరాశి అక్షరం *drm_arm_ext = "cl_arm_import_memory";

    ఒకవేళ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        తిరిగి 0;
    } లేకపోతే {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        తిరిగి 1;
    }
}

స్థిర పూర్ణాంకం opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        స్థిరరాశి అక్షరం *device_name,
                                        శూన్య *context)
{
    స్థిరరాశి అక్షరం *drm_arm_ext = "cl_arm_import_memory";

    ఒకవేళ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        తిరిగి 0;
    } లేకపోతే {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        తిరిగి 1;
    }
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                పూర్ణాంకం flags)
{
    పూర్ణాంకం err;
    ఎంపిక (src_ctx->type) {

#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
    స్థితి AV_HWDEVICE_TYPE_DRM:
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ఖాళీ;

            err = av_dict_సమితి(&selector_opts, "platform_vendor", "Intel", 0);
            ఒకవేళ (err >= 0)
                err = av_dict_సమితి(&selector_opts, "platform_version", "beignet", 0);
            ఒకవేళ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_సూచీ      = -1,
                    .device_సూచీ        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ఖాళీ,
                };
                err = opencl_device_create_అంతర్గత(hwdev, &selector, ఖాళీ);
            }
            av_dict_free(&selector_opts);
        }
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
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
                .platform_సూచీ      = -1,
                .device_సూచీ        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_అంతర్గత(hwdev, &selector, props);
        }
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ఒకవేళ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (గుర్తులేని దీర్ఘ)hr);
                err = AVERROR_UNKNOWN;
                ఆపు;
            }

            hr = IDirect3_DDevice_Manager9_తాళం_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ఒకవేళ (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_సూచీ      = -1,
                    .device_సూచీ        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_అంతర్గత(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } లేకపోతే {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (గుర్తులేని దీర్ఘ)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
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
                .platform_సూచీ      = -1,
                .device_సూచీ        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_అంతర్గత(hwdev, &selector, props);
        }
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM
    స్థితి AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_సూచీ      = -1,
                .device_సూచీ        = -1,
                .context             = ఖాళీ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_అంతర్గత(hwdev, &selector, ఖాళీ);
        }
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VIDEOTOOLBOX
    స్థితి AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ఖాళీ, ఖాళీ, 0);
        ఆపు;
#అయితే_ముగింపు

    అప్రమేయ:
        err = AVERROR(ENOSYS);
        ఆపు;
    }

    తిరిగి err;
}

స్థిర పూర్ణాంకం opencl_get_plane_format(గణన AVPixelFormat pixfmt,
                                   పూర్ణాంకం plane, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    స్థిరరాశి AVPixFmtDescriptor *desc;
    స్థిరరాశి AVComponentDescriptor *comp;
    పూర్ణాంకం channels = 0, క్రమం = 0, లోతు = 0, అడుగు = 0;
    పూర్ణాంకం wsub, hsub, alpha;
    పూర్ణాంకం c;

    ఒకవేళ (plane >= AV_అంకె_దత్తాంశం_సూచికలు)
        తిరిగి AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ఒకవేళ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        తిరిగి AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ఒకవేళ (వెడల్పు & wsub - 1 || ఎత్తు & hsub - 1)
        తిరిగి AVERROR(EINVAL);

    కొరకు (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ఒకవేళ (comp->plane != plane)
            కొనసాగు;
        // The step size must be a power of two.
        ఒకవేళ (comp->అడుగు != 1 && comp->అడుగు != 2 &&
            comp->అడుగు != 4 && comp->అడుగు != 8)
            తిరిగి AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ఒకవేళ (comp->జరుపు + comp->లోతు != 8 &&
            comp->జరుపు + comp->లోతు != 16 &&
            comp->జరుపు + comp->లోతు != 32)
            తిరిగి AVERROR(EINVAL);
        // The depth must not vary between components.
        ఒకవేళ (లోతు && comp->లోతు != లోతు)
            తిరిగి AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ఒకవేళ (comp->లోతు > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            తిరిగి AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ఒకవేళ (అడుగు && comp->అడుగు != అడుగు)
            తిరిగి AVERROR(EINVAL);

        లోతు = comp->లోతు;
        క్రమం = క్రమం * 10 + comp->స్థానభ్రంశం / ((లోతు + 7) / 8) + 1;
        అడుగు  = comp->అడుగు;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ఒకవేళ (channels == 0)
        తిరిగి AVERROR(ENOENT);

    memset(image_format, 0, పరిమాణం(*image_format));
    memset(image_desc,   0, పరిమాణం(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ఒకవేళ (plane == 0 || alpha) {
        image_desc->image_వెడల్పు     = వెడల్పు;
        image_desc->image_ఎత్తు    = ఎత్తు;
        image_desc->image_అడ్డువరుస_pitch = అడుగు * వెడల్పు;
    } లేకపోతే {
        image_desc->image_వెడల్పు     = వెడల్పు  / wsub;
        image_desc->image_ఎత్తు    = ఎత్తు / hsub;
        image_desc->image_అడ్డువరుస_pitch = అడుగు * వెడల్పు / wsub;
    }

    ఒకవేళ (లోతు <= 8) {
        image_format->image_channel_దత్తాంశం_type = CL_UNORM_INT8;
    } లేకపోతే {
        ఒకవేళ (లోతు <= 16)
            image_format->image_channel_దత్తాంశం_type = CL_UNORM_INT16;
        లేకపోతే ఒకవేళ (లోతు == 32)
            image_format->image_channel_దత్తాంశం_type = CL_FLOAT;
        లేకపోతే
            తిరిగి AVERROR(EINVAL);
    }

#నిర్వచించు CHANNEL_క్రమం(క్రమం, type) \
    స్థితి క్రమం: image_format->image_channel_క్రమం = type; ఆపు;
    ఎంపిక (క్రమం) {
        CHANNEL_క్రమం(1,    CL_R);
        CHANNEL_క్రమం(12,   CL_RG);
        CHANNEL_క్రమం(1234, CL_RGBA);
        CHANNEL_క్రమం(2341, CL_ARGB);
        CHANNEL_క్రమం(3214, CL_BGRA);
#నిర్వచితమైతే CL_ABGR
        CHANNEL_క్రమం(4321, CL_ABGR);
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
#నిర్వచనం_రద్దు CHANNEL_క్రమం

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_get_constraints(AVHWDeviceContext *hwdev,
                                         స్థిరరాశి శూన్య *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ఖాళీ;
    cl_int cle;
    గణన AVPixelFormat pix_fmt;
    పూర్ణాంకం err, pix_fmts_దొరికింది;
    size_t max_వెడల్పు, max_ఎత్తు;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_వెడల్పు,
                          పరిమాణం(max_వెడల్పు), &max_వెడల్పు, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } లేకపోతే {
        constraints->max_వెడల్పు = max_వెడల్పు;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_ఎత్తు,
                          పరిమాణం(max_ఎత్తు), &max_ఎత్తు, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } లేకపోతే {
        constraints->max_ఎత్తు = max_ఎత్తు;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_వెడల్పు, constraints->max_ఎత్తు);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ఖాళీ, &nb_image_formats);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }
    ఒకవేళ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, పరిమాణం(*image_formats));
    ఒకవేళ (!image_formats) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ఖాళీ);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    pix_fmts_దొరికింది = 0;
    కొరకు (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        పూర్ణాంకం plane, i;

        కొరకు (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ఒకవేళ (err < 0)
                ఆపు;

            కొరకు (i = 0; i < nb_image_formats; i++) {
                ఒకవేళ (image_formats[i].image_channel_క్రమం ==
                    image_format.image_channel_క్రమం &&
                    image_formats[i].image_channel_దత్తాంశం_type ==
                    image_format.image_channel_దత్తాంశం_type)
                    ఆపు;
            }
            ఒకవేళ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ఆపు;
            }
        }
        ఒకవేళ (err != AVERROR(ENOENT))
            కొనసాగు;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_దొరికింది + 2,
                                పరిమాణం(*constraints->valid_sw_formats));
        ఒకవేళ (err < 0)
            వెళ్ళు fail;
        constraints->valid_sw_formats[pix_fmts_దొరికింది] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_దొరికింది + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_దొరికింది;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;

fail:
    av_freep(&image_formats);
    తిరిగి err;
}

స్థిర శూన్య opencl_pool_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)దత్తాంశం;
    cl_int cle;
    పూర్ణాంకం p;

    కొరకు (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

స్థిర AVBufferRef *opencl_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    పూర్ణాంకం err, p;
    AVBufferRef *ref;

    desc = av_mallocz(పరిమాణం(*desc));
    ఒకవేళ (!desc)
        తిరిగి ఖాళీ;

    కొరకు (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->వెడల్పు, hwfc->ఎత్తు,
                                      &image_format, &image_desc);
        ఒకవేళ (err == AVERROR(ENOENT))
            ఆపు;
        ఒకవేళ (err < 0)
            వెళ్ళు fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_అడ్డువరుస_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ఖాళీ, &cle);
        ఒకవేళ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            వెళ్ళు fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_బఫరు_create((uint8_t*)desc, పరిమాణం(*desc),
                           &opencl_pool_free, hwfc, 0);
    ఒకవేళ (!ref)
        వెళ్ళు fail;

    తిరిగి ref;

fail:
    కొరకు (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_init_command_వరుస(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_వరుస = hwctx->command_వరుస ? hwctx->command_వరుస
                                               : devpriv->command_వరుస;
    cle = cl_Retain_Command_వరుస(priv->command_వరుస);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        తిరిగి AVERROR(EIO);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_init(AVHWFramesContext *hwfc)
{
    ఒకవేళ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_అంతర్గత =
            av_బఫరు_pool_init2(పరిమాణం(cl_mem), hwfc,
                                 &opencl_pool_alloc, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(hwfc)->pool_అంతర్గత)
            తిరిగి AVERROR(ENOMEM);
    }

    తిరిగి opencl_చట్రాలు_init_command_వరుస(hwfc);
}

స్థిర శూన్య opencl_చట్రాలు_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ఒకవేళ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    పూర్ణాంకం i, p;
    కొరకు (i = 0; i < priv->nb_mapped_చట్రాలు; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_చట్రాలు[i];
        కొరకు (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ఒకవేళ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_చట్రాలు);
#అయితే_ముగింపు

    ఒకవేళ (priv->command_వరుస) {
        cle = cl_Release_Command_వరుస(priv->command_వరుస);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_వరుస = ఖాళీ;
    }
}

స్థిర పూర్ణాంకం opencl_get_బఫరు(AVHWFramesContext *hwfc, AVFrame *చట్రం)
{
    AVOpenCLFrameDescriptor *desc;
    పూర్ణాంకం p;

    చట్రం->buf[0] = av_బఫరు_pool_get(hwfc->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)చట్రం->buf[0]->దత్తాంశం;

    కొరకు (p = 0; p < desc->nb_planes; p++)
        చట్రం->దత్తాంశం[p] = (uint8_t*)desc->planes[p];

    చట్రం->format  = AV_PIX_FMT_OPENCL;
    చట్రం->వెడల్పు   = hwfc->వెడల్పు;
    చట్రం->ఎత్తు  = hwfc->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       గణన AVHWFrameTransferDirection dir,
                                       గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts;

    fmts = av_malloc_array(2, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, పూర్ణాంకం nb_events)
{
    cl_int cle;
    పూర్ణాంకం i;

    cle = clWaitForEvents(nb_events, events);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        తిరిగి AVERROR(EIO);
    }

    కొరకు (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opencl_transfer_దత్తాంశం_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం err, p;

    ఒకవేళ (dst->format != hwfc->sw_format)
        తిరిగి AVERROR(EINVAL);

    కొరకు (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->వెడల్పు, src->ఎత్తు,
                                      &image_format, &image_desc);
        ఒకవేళ (err < 0) {
            ఒకవేళ (err == AVERROR(ENOENT))
                err = 0;
            ఆపు;
        }

        ఒకవేళ (!dst->దత్తాంశం[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ఆపు;
        }

        region[0] = image_desc.image_వెడల్పు;
        region[1] = image_desc.image_ఎత్తు;
        region[2] = 1;

        cle = cl_వరుసలో_చేర్చు_Read_Image(priv->command_వరుస,
                                 (cl_mem)src->దత్తాంశం[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->దత్తాంశం[p],
                                 0, ఖాళీ, &events[p]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ఆపు;
        }
    }

    opencl_wait_events(hwfc, events, p);

    తిరిగి err;
}

స్థిర పూర్ణాంకం opencl_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *hwfc,
                                   AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం err, p;

    ఒకవేళ (src->format != hwfc->sw_format)
        తిరిగి AVERROR(EINVAL);

    కొరకు (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->వెడల్పు, src->ఎత్తు,
                                      &image_format, &image_desc);
        ఒకవేళ (err < 0) {
            ఒకవేళ (err == AVERROR(ENOENT))
                err = 0;
            ఆపు;
        }

        ఒకవేళ (!src->దత్తాంశం[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ఆపు;
        }

        region[0] = image_desc.image_వెడల్పు;
        region[1] = image_desc.image_ఎత్తు;
        region[2] = 1;

        cle = cl_వరుసలో_చేర్చు_Write_Image(priv->command_వరుస,
                                  (cl_mem)dst->దత్తాంశం[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->దత్తాంశం[p],
                                  0, ఖాళీ, &events[p]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ఆపు;
        }
    }

    opencl_wait_events(hwfc, events, p);

    తిరిగి err;
}

రకనిర్వచనం నిర్మాణం OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    శూన్య *చిరునామా[AV_అంకె_దత్తాంశం_సూచికలు];
} OpenCLMapping;

స్థిర శూన్య opencl_unmap_చట్రం(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం p, e;
    cl_int cle;

    కొరకు (p = e = 0; p < FF_ARRAY_ELEMS(map->చిరునామా); p++) {
        ఒకవేళ (!map->చిరునామా[p])
            ఆపు;

        cle = cl_వరుసలో_చేర్చు_Unmap_Mem_Object(priv->command_వరుస,
                                      (cl_mem)hwmap->ఆధారం->దత్తాంశం[p],
                                      map->చిరునామా[p],
                                      0, ఖాళీ, &events[e]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

స్థిర పూర్ణాంకం opencl_map_చట్రం(AVHWFramesContext *hwfc, AVFrame *dst,
                            స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    size_t అడ్డువరుస_pitch;
    cl_event events[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ఒకవేళ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } లేకపోతే {
        map_flags = 0;
        ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(పరిమాణం(*map));
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->వెడల్పు, src->ఎత్తు,
                                      &image_format, &image_desc);
        ఒకవేళ (err == AVERROR(ENOENT))
            ఆపు;
        ఒకవేళ (err < 0)
            వెళ్ళు fail;

        region[0] = image_desc.image_వెడల్పు;
        region[1] = image_desc.image_ఎత్తు;
        region[2] = 1;

        map->చిరునామా[p] =
            cl_వరుసలో_చేర్చు_Map_Image(priv->command_వరుస,
                              (cl_mem)src->దత్తాంశం[p],
                              CL_FALSE, map_flags, origin, region,
                              &అడ్డువరుస_pitch, ఖాళీ, 0, ఖాళీ,
                              &events[p], &cle);
        ఒకవేళ (!map->చిరునామా[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }

        dst->దత్తాంశం[p] = map->చిరునామా[p];
        dst->linesize[p] = అడ్డువరుస_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->దత్తాంశం[p], dst->దత్తాంశం[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_చట్రం, map);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    కొరకు (p = 0; p < AV_అంకె_దత్తాంశం_సూచికలు; p++) {
        ఒకవేళ (!map->చిరునామా[p])
            ఆపు;
        cl_వరుసలో_చేర్చు_Unmap_Mem_Object(priv->command_వరుస,
                                (cl_mem)src->దత్తాంశం[p],
                                map->చిరునామా[p],
                                0, ఖాళీ, &events[p]);
    }
    ఒకవేళ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    తిరిగి err;
}

#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET

రకనిర్వచనం నిర్మాణం DRMBeignet_గమ్యం_Open_CLMapping {
    AVFrame              *drm_చట్రం;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor చట్రం;
} DRMBeignet_గమ్యం_Open_CLMapping;

స్థిర శూన్య opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_గమ్యం_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < mapping->చట్రం.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->చట్రం.planes[i]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

స్థిర పూర్ణాంకం opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, స్థిరరాశి AVFrame *src,
                                       పూర్ణాంకం flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignet_గమ్యం_Open_CLMapping *mapping;
    స్థిరరాశి AVDRMFrameDescriptor *desc;
    cl_int cle;
    పూర్ణాంకం err, i, j, p;

    desc = (స్థిరరాశి AVDRMFrameDescriptor*)src->దత్తాంశం[0];

    mapping = av_mallocz(పరిమాణం(*mapping));
    ఒకవేళ (!mapping)
        తిరిగి AVERROR(ENOMEM);

    p = 0;
    కొరకు (i = 0; i < desc->nb_layers; i++) {
        స్థిరరాశి AVDRMLayerDescriptor *layer = &desc->layers[i];
        కొరకు (j = 0; j < layer->nb_planes; j++) {
            స్థిరరాశి AVDRMPlaneDescriptor *plane = &layer->planes[j];
            స్థిరరాశి AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_సూచీ];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .కొలత      = object->కొలత,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .స్థానభ్రంశం    = plane->స్థానభ్రంశం,
                .అడ్డువరుస_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->వెడల్పు, src->ఎత్తు,
                                          &image_info.fmt,
                                          &image_desc);
            ఒకవేళ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                వెళ్ళు fail;
            }
            image_info.వెడల్పు  = image_desc.image_వెడల్పు;
            image_info.ఎత్తు = image_desc.image_ఎత్తు;

            mapping->చట్రం.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ఒకవేళ (!mapping->చట్రం.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }

            dst->దత్తాంశం[p] = (uint8_t*)mapping->చట్రం.planes[p];
            mapping->చట్రం.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    కొరకు (p = 0; p < mapping->చట్రం.nb_planes; p++) {
        ఒకవేళ (mapping->చట్రం.planes[p])
            clReleaseMemObject(mapping->చట్రం.planes[p]);
    }
    av_free(mapping);
    memset(dst->దత్తాంశం, 0, పరిమాణం(dst->దత్తాంశం));
    తిరిగి err;
}

#ఒకవేళ HAVE_OPENCL_VAAPI_BEIGNET

స్థిర పూర్ణాంకం opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, స్థిరరాశి AVFrame *src,
                                 పూర్ణాంకం flags)
{
    AVFrame *tmp;
    పూర్ణాంకం err;

    tmp = av_చట్రం_alloc();
    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ప్రధానసంఖ్య;

    err = av_hwframe_map(tmp, src, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_చట్రం_free(&tmp);
    తిరిగి err;
}

#అయితే_ముగింపు /* HAVE_OPENCL_VAAPI_BEIGNET */
#అయితే_ముగింపు /* HAVE_OPENCL_DRM_BEIGNET */

స్థిర అంతఃవరుస cl_mem_flags opencl_mem_flags_for_mapping(పూర్ణాంకం map_flags)
{
    ఒకవేళ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        తిరిగి CL_MEM_READ_WRITE;
    లేకపోతే ఒకవేళ (map_flags & AV_HWFRAME_MAP_READ)
        తిరిగి CL_MEM_READ_ONLY;
    లేకపోతే ఒకవేళ (map_flags & AV_HWFRAME_MAP_WRITE)
        తిరిగి CL_MEM_WRITE_ONLY;
    లేకపోతే
        తిరిగి 0;
}

#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA

స్థిర శూన్య opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    పూర్ణాంకం p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_వరుసలో_చేర్చు_Release_VA_APIMedia_Surfaces_INTEL(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    కొరకు (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ఒకవేళ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

స్థిర పూర్ణాంకం opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    పూర్ణాంకం err, p;

#ఒకవేళ CONFIG_LIBMFX
    ఒకవేళ (src->format == AV_PIX_FMT_QSV) {
        శూన్య *పునాది_handle;
        mfx_చట్రం_Surface1 *mfx_surface = (mfx_చట్రం_Surface1*)src->దత్తాంశం[3];
        err = ff_qsv_get_surface_పునాది_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &పునాది_handle);
        ఒకవేళ (err < 0)
            తిరిగి err;
        va_surface = *(VASurfaceID *)పునాది_handle;
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];
    } లేకపోతే {
        తిరిగి AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ఒకవేళ (!cl_flags)
        తిరిగి AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(పరిమాణం(*desc));
    ఒకవేళ (!desc)
        తిరిగి AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    కొరకు (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ఒకవేళ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }

        dst->దత్తాంశం[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_వరుసలో_చేర్చు_Acquire_VA_APIMedia_Surfaces_INTEL(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        వెళ్ళు fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    కొరకు (p = 0; p < desc->nb_planes; p++)
        ఒకవేళ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->దత్తాంశం, 0, పరిమాణం(dst->దత్తాంశం));
    తిరిగి err;
}

#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DXVA2

స్థిర శూన్య opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_వరుసలో_చేర్చు_Release_DX9_Media_Surfaces_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        తిరిగి;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

స్థిర పూర్ణాంకం opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
    AVDXVA2_చట్రాలు_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    పూర్ణాంకం err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->దత్తాంశం[3]);

    కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ఒకవేళ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->దత్తాంశం[3])
            ఆపు;
    }
    ఒకవేళ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        తిరిగి AVERROR(EINVAL);
    }

    desc = &చట్రాలు_priv->mapped_చట్రాలు[i];

    cle = device_priv->cl_వరుసలో_చేర్చు_Acquire_DX9_Media_Surfaces_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        తిరిగి AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (i = 0; i < desc->nb_planes; i++)
        dst->దత్తాంశం[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    cle = device_priv->cl_వరుసలో_చేర్చు_Release_DX9_Media_Surfaces_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->దత్తాంశం, 0, పరిమాణం(dst->దత్తాంశం));
    తిరిగి err;
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, పూర్ణాంకం flags)
{
    AVDXVA2_చట్రాలు_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    పూర్ణాంకం err, i, p, nb_planes;

    ఒకవేళ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        తిరిగి AVERROR(EINVAL);
    }
    nb_planes = 2;

    ఒకవేళ (src_fc->initial_pool_కొలత == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        తిరిగి AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ఒకవేళ (!cl_flags)
        తిరిగి AVERROR(EINVAL);

    చట్రాలు_priv->nb_mapped_చట్రాలు = src_hwctx->nb_surfaces;

    చట్రాలు_priv->mapped_చట్రాలు =
        av_calloc(చట్రాలు_priv->nb_mapped_చట్రాలు,
                  పరిమాణం(*చట్రాలు_priv->mapped_చట్రాలు));
    ఒకవేళ (!చట్రాలు_priv->mapped_చట్రాలు)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < చట్రాలు_priv->nb_mapped_చట్రాలు; i++) {
        AVOpenCLFrameDescriptor *desc = &చట్రాలు_priv->mapped_చట్రాలు[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ఖాళీ,
        };
        desc->nb_planes = nb_planes;
        కొరకు (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ఒకవేళ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }
        }
    }

    తిరిగి 0;

fail:
    కొరకు (i = 0; i < చట్రాలు_priv->nb_mapped_చట్రాలు; i++) {
        AVOpenCLFrameDescriptor *desc = &చట్రాలు_priv->mapped_చట్రాలు[i];
        కొరకు (p = 0; p < desc->nb_planes; p++) {
            ఒకవేళ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&చట్రాలు_priv->mapped_చట్రాలు);
    చట్రాలు_priv->nb_mapped_చట్రాలు = 0;
    తిరిగి err;
}

#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_D3D11

స్థిర శూన్య opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *చట్రాలు_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_వరుసలో_చేర్చు_Release_D3_D11_Objects_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

స్థిర పూర్ణాంకం opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *చట్రాలు_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    పూర్ణాంకం err, సూచీ, i;

    సూచీ = (intptr_t)src->దత్తాంశం[1];
    ఒకవేళ (సూచీ >= చట్రాలు_priv->nb_mapped_చట్రాలు) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", సూచీ, చట్రాలు_priv->nb_mapped_చట్రాలు);
        తిరిగి AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           సూచీ);

    desc = &చట్రాలు_priv->mapped_చట్రాలు[సూచీ];

    cle = device_priv->cl_వరుసలో_చేర్చు_Acquire_D3_D11_Objects_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        తిరిగి AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (i = 0; i < desc->nb_planes; i++)
        dst->దత్తాంశం[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    cle = device_priv->cl_వరుసలో_చేర్చు_Release_D3_D11_Objects_KHR(
        చట్రాలు_priv->command_వరుస, desc->nb_planes, desc->planes,
        0, ఖాళీ, &event);
    ఒకవేళ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->దత్తాంశం, 0, పరిమాణం(dst->దత్తాంశం));
    తిరిగి err;
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, పూర్ణాంకం flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *చట్రాలు_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    పూర్ణాంకం err, i, p, nb_planes;

    ఒకవేళ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        తిరిగి AVERROR(EINVAL);
    }
    nb_planes = 2;

    ఒకవేళ (src_fc->initial_pool_కొలత == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        తిరిగి AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ఒకవేళ (!cl_flags)
        తిరిగి AVERROR(EINVAL);

    చట్రాలు_priv->nb_mapped_చట్రాలు = src_fc->initial_pool_కొలత;

    చట్రాలు_priv->mapped_చట్రాలు =
        av_calloc(చట్రాలు_priv->nb_mapped_చట్రాలు,
                  పరిమాణం(*చట్రాలు_priv->mapped_చట్రాలు));
    ఒకవేళ (!చట్రాలు_priv->mapped_చట్రాలు)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < చట్రాలు_priv->nb_mapped_చట్రాలు; i++) {
        AVOpenCLFrameDescriptor *desc = &చట్రాలు_priv->mapped_చట్రాలు[i];
        desc->nb_planes = nb_planes;
        కొరకు (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ఒకవేళ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (గుర్తులేని పూర్ణాంకం)subresource, cle);
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }
        }
    }

    తిరిగి 0;

fail:
    కొరకు (i = 0; i < చట్రాలు_priv->nb_mapped_చట్రాలు; i++) {
        AVOpenCLFrameDescriptor *desc = &చట్రాలు_priv->mapped_చట్రాలు[i];
        కొరకు (p = 0; p < desc->nb_planes; p++) {
            ఒకవేళ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&చట్రాలు_priv->mapped_చట్రాలు);
    చట్రాలు_priv->nb_mapped_చట్రాలు = 0;
    తిరిగి err;
}

#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_DRM_ARM

రకనిర్వచనం నిర్మాణం DRMARMtoOpenCLMapping {
    పూర్ణాంకం nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    పూర్ణాంకం nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

స్థిర శూన్య opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    కొరకు (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

స్థిర పూర్ణాంకం opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    స్థిరరాశి AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ఖాళీ;
    cl_mem_flags cl_flags;
    స్థిరరాశి cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    పూర్ణాంకం err, i, j;

    desc = (స్థిరరాశి AVDRMFrameDescriptor*)src->దత్తాంశం[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ఒకవేళ (!cl_flags)
        తిరిగి AVERROR(EINVAL);

    mapping = av_mallocz(పరిమాణం(*mapping));
    ఒకవేళ (!mapping)
        తిరిగి AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    కొరకు (i = 0; i < desc->nb_objects; i++) {
        పూర్ణాంకం fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ఒకవేళ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_జ్ఞాపకం_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].కొలత, &cle);
        ఒకవేళ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].కొలత, cle);
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }
    }

    mapping->nb_planes = 0;
    కొరకు (i = 0; i < desc->nb_layers; i++) {
        స్థిరరాశి AVDRMLayerDescriptor *layer = &desc->layers[i];

        కొరకు (j = 0; j < layer->nb_planes; j++) {
            స్థిరరాశి AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_బఫరు;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_బఫరు_region region;
            పూర్ణాంకం p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->వెడల్పు, src_fc->ఎత్తు,
                                          &image_format, &image_desc);
            ఒకవేళ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                వెళ్ళు fail;
            }

            region.origin = plane->స్థానభ్రంశం;
            region.కొలత   = image_desc.image_అడ్డువరుస_pitch *
                            image_desc.image_ఎత్తు;

            plane_బఫరు =
                cl_Create_Sub_బఫరు(mapping->object_buffers[plane->object_సూచీ],
                                  cl_flags,
                                  CL_బఫరు_CREATE_TYPE_REGION,
                                  &region, &cle);
            ఒకవేళ (!plane_బఫరు) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }

            image_desc.బఫరు = plane_బఫరు;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ఖాళీ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_బఫరు);

            ఒకవేళ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                వెళ్ళు fail;
            }

            ++mapping->nb_planes;
        }
    }

    కొరకు (i = 0; i < mapping->nb_planes; i++)
        dst->దత్తాంశం[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    కొరకు (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    కొరకు (i = 0; i < mapping->nb_objects; i++) {
        ఒకవేళ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->దత్తాంశం, 0, పరిమాణం(dst->దత్తాంశం));
    తిరిగి err;
}

#అయితే_ముగింపు

#ఒకవేళ HAVE_OPENCL_VIDEOTOOLBOX

స్థిర శూన్య opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

స్థిర పూర్ణాంకం opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    CVPixel_బఫరు_Ref pixbuf = (CVPixel_బఫరు_Ref) src->దత్తాంశం[3];
    IOSurfaceRef io_surface_ref = CVPixel_బఫరు_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ఖాళీ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ఒకవేళ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        తిరిగి AVERROR_EXTERNAL;
    }

    desc = av_mallocz(పరిమాణం(*desc));
    ఒకవేళ (!desc)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (పూర్ణాంకం p = 0;; p++) {
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_iosurface_properties_APPLE props[] = {
                CL_IOSURFACE_REF_APPLE, (cl_iosurface_properties_APPLE) io_surface_ref,
                CL_IOSURFACE_PLANE_APPLE, p,
                0
        };

        err = opencl_get_plane_format(dst_fc->sw_format, p,
                                      src->వెడల్పు, src->ఎత్తు,
                                      &image_format, &image_desc);
        ఒకవేళ (err == AVERROR(ENOENT))
            ఆపు;
        ఒకవేళ (err < 0)
            వెళ్ళు fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ఒకవేళ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            వెళ్ళు fail;
        }
        desc->nb_planes++;
    }

    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_planes; i++)
        dst->దత్తాంశం[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    dst->వెడల్పు = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    తిరిగి 0;

fail:
    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    తిరిగి err;
}

#అయితే_ముగింపు

స్థిర పూర్ణాంకం opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ఒకవేళ (hwfc->sw_format != dst->format)
        తిరిగి AVERROR(ENOSYS);
    తిరిగి opencl_map_చట్రం(hwfc, dst, src, flags);
}

స్థిర పూర్ణాంకం opencl_map_గమ్యం(AVHWFramesContext *hwfc, AVFrame *dst,
                         స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    av_వాడని OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    ఎంపిక (src->format) {
#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        ఒకవేళ (priv->beignet_drm_mapping_usable)
            తిరిగి opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VAAPI_BEIGNET
    స్థితి AV_PIX_FMT_VAAPI:
        ఒకవేళ (priv->beignet_drm_mapping_usable)
            తిరిగి opencl_map_from_vaapi(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    స్థితి AV_PIX_FMT_QSV:
    స్థితి AV_PIX_FMT_VAAPI:
        ఒకవేళ (priv->qsv_mapping_usable)
            తిరిగి opencl_map_from_qsv(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_DXVA2
    స్థితి AV_PIX_FMT_DXVA2_VLD:
        ఒకవేళ (priv->dxva2_mapping_usable)
            తిరిగి opencl_map_from_dxva2(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_D3D11
    స్థితి AV_PIX_FMT_D3D11:
        ఒకవేళ (priv->d3d11_mapping_usable)
            తిరిగి opencl_map_from_d3d11(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_DRM_ARM
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        ఒకవేళ (priv->drm_arm_mapping_usable)
            తిరిగి opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VIDEOTOOLBOX
    స్థితి AV_PIX_FMT_VIDEOTOOLBOX:
        తిరిగి opencl_map_from_vt(hwfc, dst, src, flags);
#అయితే_ముగింపు
    }
    తిరిగి AVERROR(ENOSYS);
}

స్థిర పూర్ణాంకం opencl_చట్రాలు_derive_గమ్యం(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, పూర్ణాంకం flags)
{
    av_వాడని OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    ఎంపిక (src_fc->device_ctx->type) {
#ఒకవేళ HAVE_OPENCL_DRM_BEIGNET
    స్థితి AV_HWDEVICE_TYPE_DRM:
        ఒకవేళ (!priv->beignet_drm_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VAAPI_BEIGNET
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        ఒకవేళ (!priv->beignet_drm_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    స్థితి AV_HWDEVICE_TYPE_QSV:
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        ఒకవేళ (!priv->qsv_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        ఒకవేళ (!priv->dxva2_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        {
            పూర్ణాంకం err;
            err = opencl_చట్రాలు_derive_from_dxva2(dst_fc, src_fc, flags);
            ఒకవేళ (err < 0)
                తిరిగి err;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_D3D11
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        ఒకవేళ (!priv->d3d11_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        {
            పూర్ణాంకం err;
            err = opencl_చట్రాలు_derive_from_d3d11(dst_fc, src_fc, flags);
            ఒకవేళ (err < 0)
                తిరిగి err;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_DRM_ARM
    స్థితి AV_HWDEVICE_TYPE_DRM:
        ఒకవేళ (!priv->drm_arm_mapping_usable)
            తిరిగి AVERROR(ENOSYS);
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ HAVE_OPENCL_VIDEOTOOLBOX
    స్థితి AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }
    తిరిగి opencl_చట్రాలు_init_command_వరుస(dst_fc);
}

స్థిరరాశి HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_కొలత      = పరిమాణం(OpenCLDeviceContext),
    .చట్రాలు_hwctx_కొలత      = పరిమాణం(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .చట్రాలు_get_constraints = &opencl_చట్రాలు_get_constraints,
    .చట్రాలు_init            = &opencl_చట్రాలు_init,
    .చట్రాలు_uninit          = &opencl_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు      = &opencl_get_బఫరు,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = &opencl_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from     = &opencl_transfer_దత్తాంశం_from,

    .map_from               = &opencl_map_from,
    .map_గమ్యం                 = &opencl_map_గమ్యం,
    .చట్రాలు_derive_గమ్యం       = &opencl_చట్రాలు_derive_గమ్యం,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
