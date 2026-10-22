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

#अन्तर्भाव <string.h>

#अन्तर्भाव "config.h"

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_opencl.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"

#जइ HAVE_OPENCL_VAAPI_BEIGNET
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <va/va.h>
#अन्तर्भाव <va/va_drmcommon.h>
#अन्तर्भाव <CL/cl_intel.h>
#अन्तर्भाव "hwcontext_vaapi.h"
#endif

#जइ HAVE_OPENCL_DRM_BEIGNET
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <CL/cl_intel.h>
#अन्तर्भाव "hwcontext_drm.h"
#endif

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#जइ CONFIG_LIBMFX
#अन्तर्भाव <mfxstructures.h>
#endif
#अन्तर्भाव <va/va.h>
#अन्तर्भाव <CL/cl_va_api_media_sharing_intel.h>
#अन्तर्भाव "hwcontext_vaapi.h"
#endif

#जइ HAVE_OPENCL_DXVA2
#define COBJMACROS
#अन्तर्भाव <CL/cl_dx9_media_sharing.h>
#अन्तर्भाव <dxva2api.h>
#अन्तर्भाव "hwcontext_dxva2.h"
#endif

#जइ HAVE_OPENCL_D3D11
#अन्तर्भाव <CL/cl_d3d11.h>
#अन्तर्भाव "hwcontext_d3d11va.h"
#endif

#जइ HAVE_OPENCL_DRM_ARM
#अन्तर्भाव <CL/cl_ext.h>
#अन्तर्भाव <drm_fourcc.h>
#अन्तर्भाव "hwcontext_drm.h"
#endif

#जइ HAVE_OPENCL_VIDEOTOOLBOX
#अन्तर्भाव <OpenCL/cl_gl_ext.h>
#अन्तर्भाव <VideoToolbox/VideoToolbox.h>
#endif

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
बाह्य पूर्णाङ्क ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          गणना AVHWDeviceType base_dev_typ,
                                          शून्य **base_handle);
#endif


प्रकारनिर्देश संरचना OpenCLDeviceContext {
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
#जइ HAVE_OPENCL_DRM_BEIGNET
    पूर्णाङ्क beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पूर्णाङ्क qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#जइ HAVE_OPENCL_DXVA2
    पूर्णाङ्क dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#जइ HAVE_OPENCL_D3D11
    पूर्णाङ्क d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#जइ HAVE_OPENCL_DRM_ARM
    पूर्णाङ्क drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

प्रकारनिर्देश संरचना OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#जइ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    पूर्णाङ्क                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


स्थिर शून्य CL_CALLBACK opencl_error_callback(ध्रुव वर्ण *errinfo,
                                              ध्रुव शून्य *private_info,
                                              size_t cb,
                                              शून्य *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

स्थिर शून्य opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

स्थिर संरचना {
    ध्रुव वर्ण *कुञ्चिका;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

स्थिर संरचना {
    ध्रुव वर्ण *कुञ्चिका;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

स्थिर संरचना {
    ध्रुव वर्ण *कुञ्चिका;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

स्थिर वर्ण *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info कुञ्चिका)
{
    वर्ण *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, कुञ्चिका, 0, रिक्त, &size);
    जइ (cle != CL_SUCCESS)
        प्रत्यागम रिक्त;
    str = av_malloc(size);
    जइ (!str)
        प्रत्यागम रिक्त;
    cle = clGetPlatformInfo(platform_id, कुञ्चिका, size, str, &size);
    जइ (cle != CL_SUCCESS) {
        av_free(str);
        प्रत्यागम रिक्त;
    }
    av_assert0(strlen(str) + 1 == size);
    प्रत्यागम str;
}

स्थिर वर्ण *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info कुञ्चिका)
{
    वर्ण *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, कुञ्चिका, 0, रिक्त, &size);
    जइ (cle != CL_SUCCESS)
        प्रत्यागम रिक्त;
    str = av_malloc(size);
    जइ (!str)
        प्रत्यागम रिक्त;
    cle = clGetDeviceInfo(device_id, कुञ्चिका, size, str, &size);
    जइ (cle != CL_SUCCESS) {
        av_free(str);
        प्रत्यागम रिक्त;
    }
    av_assert0(strlen(str) + 1== size);
    प्रत्यागम str;
}

स्थिर पूर्णाङ्क opencl_check_platform_extension(cl_platform_id platform_id,
                                           ध्रुव वर्ण *name)
{
    वर्ण *str;
    पूर्णाङ्क found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    जइ (str && strstr(str, name))
        found = 1;
    av_free(str);
    प्रत्यागम found;
}

स्थिर पूर्णाङ्क opencl_check_device_extension(cl_device_id device_id,
                                         ध्रुव वर्ण *name)
{
    वर्ण *str;
    पूर्णाङ्क found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    जइ (str && strstr(str, name))
        found = 1;
    av_free(str);
    प्रत्यागम found;
}

av_unused स्थिर पूर्णाङ्क opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ध्रुव वर्ण *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    जइ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        प्रत्यागम 1;
    }

    जइ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        प्रत्यागम 1;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      शून्य *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, रिक्त, nb_platforms);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        प्रत्यागम AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, परिमाण(**platforms));
    जइ (!*platforms)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        प्रत्यागम AVERROR(ENODEV);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ध्रुव वर्ण *platform_name,
                                  शून्य *context)
{
    AVDictionary *opts = context;
    ध्रुव AVDictionaryEntry *param;
    वर्ण *str;
    पूर्णाङ्क i, ret = 0;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].कुञ्चिका,
                            रिक्त, 0);
        जइ (!param)
            अनुवर्त;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        जइ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].कुञ्चिका, platform_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }
        जइ (!av_stristr(str, param->मानम्)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->कुञ्चिका, str);
            ret = 1;
        }
        av_free(str);
    }

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ध्रुव वर्ण *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    शून्य *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, रिक्त, nb_devices);
    जइ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अण्णहा जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    जइ (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR(ENODEV);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ध्रुव वर्ण *device_name,
                                शून्य *context)
{
    AVDictionary *opts = context;
    ध्रुव AVDictionaryEntry *param;
    वर्ण *str;
    पूर्णाङ्क i, ret = 0;

    param = av_dict_get(opts, "device_type", रिक्त, 0);
    जइ (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            जइ (!strcmp(opencl_device_types[i].कुञ्चिका, param->मानम्)) {
                match_type = opencl_device_types[i].type;
                भङ्ग;
            }
        }
        जइ (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->मानम्);
            प्रत्यागम AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              परिमाण(device_type), &device_type, रिक्त);
        जइ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }

        जइ (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            प्रत्यागम 1;
        }
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].कुञ्चिका,
                            रिक्त, 0);
        जइ (!param)
            अनुवर्त;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        जइ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].कुञ्चिका, device_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }
        जइ (!av_stristr(str, param->मानम्)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->कुञ्चिका, str);
            ret = 1;
        }
        av_free(str);
    }

    प्रत्यागम ret;
}

प्रकारनिर्देश संरचना OpenCLDeviceSelector {
    पूर्णाङ्क platform_index;
    पूर्णाङ्क device_index;
    शून्य *context;
    पूर्णाङ्क (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               शून्य *context);
    पूर्णाङ्क (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ध्रुव वर्ण *platform_name,
                               शून्य *context);
    पूर्णाङ्क (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ध्रुव वर्ण *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               शून्य *context);
    पूर्णाङ्क (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ध्रुव वर्ण *device_name,
                               शून्य *context);
} OpenCLDeviceSelector;

स्थिर पूर्णाङ्क opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ध्रुव OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = रिक्त;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = रिक्त;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    वर्ण *platform_name_src = रिक्त,
         *device_name_src   = रिक्त;
    पूर्णाङ्क err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    जइ (err)
        प्रत्यागम err;

    found = 0;
    प्रति (p = 0; p < nb_platforms; p++) {
        ध्रुव वर्ण *platform_name;

        जइ (selector->platform_index >= 0 &&
            selector->platform_index != p)
            अनुवर्त;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        जइ (platform_name_src)
            platform_name = platform_name_src;
        अण्णहा
            platform_name = "Unknown Platform";

        जइ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            जइ (err < 0)
                गच्छ fail;
            जइ (err > 0)
                अनुवर्त;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        जइ (err < 0)
            अनुवर्त;

        प्रति (d = 0; d < nb_devices; d++) {
            ध्रुव वर्ण *device_name;

            जइ (selector->device_index >= 0 &&
                selector->device_index != d)
                अनुवर्त;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            जइ (device_name_src)
                device_name = device_name_src;
            अण्णहा
                device_name = "Unknown Device";

            जइ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                जइ (err < 0)
                    गच्छ fail;
                जइ (err > 0)
                    अनुवर्त;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    जइ (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        गच्छ fail;
    }
    जइ (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        गच्छ fail;
    }

    जइ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } अण्णहा {
        जइ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    जइ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        गच्छ fail;
    }

    hwdev->मुक्त = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_device_create(AVHWDeviceContext *hwdev, ध्रुव वर्ण *device,
                                AVDictionary *opts, पूर्णाङ्क flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    जइ (device && device[0]) {
        // Match one or both indices for platform and device.
        पूर्णाङ्क d = -1, p = -1, ret;
        जइ (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        अण्णहा
            ret = sscanf(device, "%d.%d", &p, &d);
        जइ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            प्रत्यागम AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } अण्णहा {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    प्रत्यागम opencl_device_create_internal(hwdev, &selector, रिक्त);
}

स्थिर पूर्णाङ्क opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    जइ (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        जइ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            प्रत्यागम AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } अण्णहा {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        जइ (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            प्रत्यागम AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          परिमाण(priv->platform_id), &priv->platform_id,
                          रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        प्रत्यागम AVERROR(EIO);
    }

#define CL_FUNC(name, desc) करेहि {                                \
        जइ (fail)                                               \
            भङ्ग;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        जइ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } अण्णहा {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } जाव (0)

#जइ HAVE_OPENCL_DRM_BEIGNET
    {
        पूर्णाङ्क fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        जइ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } अण्णहा {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = रिक्त;
        VADisplay va_display;
        ध्रुव वर्ण *va_ext = "cl_intel_va_api_media_sharing";
        पूर्णाङ्क i, fail = 0;

        जइ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            गच्छ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, रिक्त, &props_size);
        जइ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            गच्छ no_qsv;
        }
        जइ (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }

        props = av_malloc(props_size);
        जइ (!props)
            प्रत्यागम AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, रिक्त);
        जइ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            गच्छ no_qsv;
        }

        va_display = रिक्त;
        प्रति (i = 0; i < (props_size / परिमाण(*props) - 1); i++) {
            जइ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                भङ्ग;
            }
        }
        जइ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }
        जइ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        जइ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } अण्णहा {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#जइ HAVE_OPENCL_DXVA2
    {
        पूर्णाङ्क fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        जइ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } अण्णहा {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#जइ HAVE_OPENCL_D3D11
    {
        ध्रुव वर्ण *d3d11_ext = "cl_khr_d3d11_sharing";
        ध्रुव वर्ण *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        पूर्णाङ्क fail = 0;

        जइ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } अण्णहा जइ (!opencl_check_extension(hwdev, nv12_ext)) {
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

        जइ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } अण्णहा {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#जइ HAVE_OPENCL_DRM_ARM
    {
        ध्रुव वर्ण *drm_arm_ext = "cl_arm_import_memory";
        ध्रुव वर्ण *image_ext   = "cl_khr_image2d_from_buffer";
        पूर्णाङ्क fail = 0;

        जइ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        जइ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        जइ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } अण्णहा {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    प्रत्यागम 0;
}

स्थिर शून्य opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    जइ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        जइ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = रिक्त;
    }
}

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
स्थिर पूर्णाङ्क opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ध्रुव वर्ण *platform_name,
                                                    शून्य *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    जइ (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        प्रत्यागम 1;
    } अण्णहा {
        प्रत्यागम 0;
    }
}

स्थिर पूर्णाङ्क opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ध्रुव वर्ण *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      शून्य *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    जइ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, रिक्त, nb_devices);
    जइ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अण्णहा जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    जइ (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ध्रुव वर्ण *device_name,
                                                  शून्य *context)
{
    ध्रुव वर्ण *va_ext = "cl_intel_va_api_media_sharing";

    जइ (opencl_check_device_extension(device_id, va_ext)) {
        प्रत्यागम 0;
    } अण्णहा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        प्रत्यागम 1;
    }
}
#endif

#जइ HAVE_OPENCL_DXVA2
स्थिर पूर्णाङ्क opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ध्रुव वर्ण *platform_name,
                                        शून्य *context)
{
    ध्रुव वर्ण *dx9_ext = "cl_khr_dx9_media_sharing";

    जइ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        प्रत्यागम 0;
    } अण्णहा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        प्रत्यागम 1;
    }
}

स्थिर पूर्णाङ्क opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ध्रुव वर्ण *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          शून्य *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    जइ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (शून्य**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, रिक्त, nb_devices);
    जइ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अण्णहा जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    जइ (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (शून्य**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}
#endif

#जइ HAVE_OPENCL_D3D11
स्थिर पूर्णाङ्क opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ध्रुव वर्ण *platform_name,
                                        शून्य *context)
{
    ध्रुव वर्ण *d3d11_ext = "cl_khr_d3d11_sharing";

    जइ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        प्रत्यागम 0;
    } अण्णहा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        प्रत्यागम 1;
    }
}

स्थिर पूर्णाङ्क opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ध्रुव वर्ण *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          शून्य *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    जइ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, रिक्त, nb_devices);
    जइ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अण्णहा जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    जइ (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}
#endif

#जइ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
स्थिर पूर्णाङ्क opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ध्रुव वर्ण *device_name,
                                    शून्य *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          परिमाण(device_type), &device_type, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        प्रत्यागम AVERROR_UNKNOWN;
    }
    जइ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        प्रत्यागम 1;
    }

    प्रत्यागम 0;
}
#endif

#जइ HAVE_OPENCL_DRM_ARM
स्थिर पूर्णाङ्क opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ध्रुव वर्ण *platform_name,
                                          शून्य *context)
{
    ध्रुव वर्ण *drm_arm_ext = "cl_arm_import_memory";

    जइ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        प्रत्यागम 0;
    } अण्णहा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        प्रत्यागम 1;
    }
}

स्थिर पूर्णाङ्क opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ध्रुव वर्ण *device_name,
                                        शून्य *context)
{
    ध्रुव वर्ण *drm_arm_ext = "cl_arm_import_memory";

    जइ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        प्रत्यागम 0;
    } अण्णहा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        प्रत्यागम 1;
    }
}
#endif

स्थिर पूर्णाङ्क opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                पूर्णाङ्क flags)
{
    पूर्णाङ्क err;
    विकल्प (src_ctx->type) {

#जइ HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_DRM:
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = रिक्त;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            जइ (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            जइ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = रिक्त,
                };
                err = opencl_device_create_internal(hwdev, &selector, रिक्त);
            }
            av_dict_free(&selector_opts);
        }
        भङ्ग;
#endif

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
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
        भङ्ग;
#endif

#जइ HAVE_OPENCL_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            जइ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                भङ्ग;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            जइ (SUCCEEDED(hr)) {
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
            } अण्णहा {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        भङ्ग;
#endif

#जइ HAVE_OPENCL_D3D11
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
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
        भङ्ग;
#endif

#जइ HAVE_OPENCL_DRM_ARM
    पक्ष AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = रिक्त,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, रिक्त);
        }
        भङ्ग;
#endif

#जइ HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, रिक्त, रिक्त, 0);
        भङ्ग;
#endif

    स्वभाव:
        err = AVERROR(ENOSYS);
        भङ्ग;
    }

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_get_plane_format(गणना AVPixelFormat pixfmt,
                                   पूर्णाङ्क plane, पूर्णाङ्क width, पूर्णाङ्क height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ध्रुव AVPixFmtDescriptor *desc;
    ध्रुव AVComponentDescriptor *comp;
    पूर्णाङ्क channels = 0, order = 0, depth = 0, step = 0;
    पूर्णाङ्क wsub, hsub, alpha;
    पूर्णाङ्क c;

    जइ (plane >= AV_अङ्कः_DATA_POINTERS)
        प्रत्यागम AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    जइ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        प्रत्यागम AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    जइ (width & wsub - 1 || height & hsub - 1)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        जइ (comp->plane != plane)
            अनुवर्त;
        // The step size must be a power of two.
        जइ (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            प्रत्यागम AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        जइ (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            प्रत्यागम AVERROR(EINVAL);
        // The depth must not vary between components.
        जइ (depth && comp->depth != depth)
            प्रत्यागम AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        जइ (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            प्रत्यागम AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        जइ (step && comp->step != step)
            प्रत्यागम AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    जइ (channels == 0)
        प्रत्यागम AVERROR(ENOENT);

    memset(image_format, 0, परिमाण(*image_format));
    memset(image_desc,   0, परिमाण(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    जइ (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } अण्णहा {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    जइ (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } अण्णहा {
        जइ (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        अण्णहा जइ (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        अण्णहा
            प्रत्यागम AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    पक्ष order: image_format->image_channel_order = type; भङ्ग;
    विकल्प (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ध्रुव शून्य *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = रिक्त;
    cl_int cle;
    गणना AVPixelFormat pix_fmt;
    पूर्णाङ्क err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          परिमाण(max_width), &max_width, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } अण्णहा {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          परिमाण(max_height), &max_height, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } अण्णहा {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, रिक्त, &nb_image_formats);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }
    जइ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, परिमाण(*image_formats));
    जइ (!image_formats) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, रिक्त);
    जइ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }

    pix_fmts_found = 0;
    प्रति (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        पूर्णाङ्क plane, i;

        प्रति (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            जइ (err < 0)
                भङ्ग;

            प्रति (i = 0; i < nb_image_formats; i++) {
                जइ (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    भङ्ग;
            }
            जइ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                भङ्ग;
            }
        }
        जइ (err != AVERROR(ENOENT))
            अनुवर्त;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                परिमाण(*constraints->valid_sw_formats));
        जइ (err < 0)
            गच्छ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    जइ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;

fail:
    av_freep(&image_formats);
    प्रत्यागम err;
}

स्थिर शून्य opencl_pool_free(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    पूर्णाङ्क p;

    प्रति (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

स्थिर AVBufferRef *opencl_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    पूर्णाङ्क err, p;
    AVBufferRef *ref;

    desc = av_mallocz(परिमाण(*desc));
    जइ (!desc)
        प्रत्यागम रिक्त;

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        जइ (err == AVERROR(ENOENT))
            भङ्ग;
        जइ (err < 0)
            गच्छ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, रिक्त, &cle);
        जइ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            गच्छ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, परिमाण(*desc),
                           &opencl_pool_free, hwfc, 0);
    जइ (!ref)
        गच्छ fail;

    प्रत्यागम ref;

fail:
    प्रति (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    जइ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_frames_init(AVHWFramesContext *hwfc)
{
    जइ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(परिमाण(cl_mem), hwfc,
                                 &opencl_pool_alloc, रिक्त);
        जइ (!ffhwframesctx(hwfc)->pool_internal)
            प्रत्यागम AVERROR(ENOMEM);
    }

    प्रत्यागम opencl_frames_init_command_queue(hwfc);
}

स्थिर शून्य opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#जइ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    पूर्णाङ्क i, p;
    प्रति (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            जइ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    जइ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = रिक्त;
    }
}

स्थिर पूर्णाङ्क opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    पूर्णाङ्क p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    जइ (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    प्रति (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       गणना AVHWFrameTransferDirection dir,
                                       गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    जइ (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, पूर्णाङ्क nb_events)
{
    cl_int cle;
    पूर्णाङ्क i;

    cle = clWaitForEvents(nb_events, events);
    जइ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    प्रति (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ध्रुव AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_अङ्कः_DATA_POINTERS];
    पूर्णाङ्क err, p;

    जइ (dst->format != hwfc->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        जइ (err < 0) {
            जइ (err == AVERROR(ENOENT))
                err = 0;
            भङ्ग;
        }

        जइ (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            भङ्ग;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, रिक्त, &events[p]);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            भङ्ग;
        }
    }

    opencl_wait_events(hwfc, events, p);

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ध्रुव AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_अङ्कः_DATA_POINTERS];
    पूर्णाङ्क err, p;

    जइ (src->format != hwfc->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        जइ (err < 0) {
            जइ (err == AVERROR(ENOENT))
                err = 0;
            भङ्ग;
        }

        जइ (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            भङ्ग;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, रिक्त, &events[p]);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            भङ्ग;
        }
    }

    opencl_wait_events(hwfc, events, p);

    प्रत्यागम err;
}

प्रकारनिर्देश संरचना OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    शून्य *address[AV_अङ्कः_DATA_POINTERS];
} OpenCLMapping;

स्थिर शून्य opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_अङ्कः_DATA_POINTERS];
    पूर्णाङ्क p, e;
    cl_int cle;

    प्रति (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        जइ (!map->address[p])
            भङ्ग;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, रिक्त, &events[e]);
        जइ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

स्थिर पूर्णाङ्क opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ध्रुव AVFrame *src, पूर्णाङ्क flags)
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
    cl_event events[AV_अङ्कः_DATA_POINTERS];
    पूर्णाङ्क err, p;

    av_assert0(hwfc->sw_format == dst->format);

    जइ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } अण्णहा {
        map_flags = 0;
        जइ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        जइ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(परिमाण(*map));
    जइ (!map)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        जइ (err == AVERROR(ENOENT))
            भङ्ग;
        जइ (err < 0)
            गच्छ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, रिक्त, 0, रिक्त,
                              &events[p], &cle);
        जइ (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    जइ (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < AV_अङ्कः_DATA_POINTERS; p++) {
        जइ (!map->address[p])
            भङ्ग;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, रिक्त, &events[p]);
    }
    जइ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    प्रत्यागम err;
}

#जइ HAVE_OPENCL_DRM_BEIGNET

प्रकारनिर्देश संरचना DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

स्थिर शून्य opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    पूर्णाङ्क i;

    प्रति (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        जइ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

स्थिर पूर्णाङ्क opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ध्रुव AVFrame *src,
                                       पूर्णाङ्क flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ध्रुव AVDRMFrameDescriptor *desc;
    cl_int cle;
    पूर्णाङ्क err, i, j, p;

    desc = (ध्रुव AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(परिमाण(*mapping));
    जइ (!mapping)
        प्रत्यागम AVERROR(ENOMEM);

    p = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        ध्रुव AVDRMLayerDescriptor *layer = &desc->layers[i];
        प्रति (j = 0; j < layer->nb_planes; j++) {
            ध्रुव AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ध्रुव AVDRMObjectDescriptor *object =
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
            जइ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                गच्छ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            जइ (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < mapping->frame.nb_planes; p++) {
        जइ (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, परिमाण(dst->data));
    प्रत्यागम err;
}

#जइ HAVE_OPENCL_VAAPI_BEIGNET

स्थिर पूर्णाङ्क opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ध्रुव AVFrame *src,
                                 पूर्णाङ्क flags)
{
    AVFrame *tmp;
    पूर्णाङ्क err;

    tmp = av_frame_alloc();
    जइ (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_अविभाज्यः;

    err = av_hwframe_map(tmp, src, flags);
    जइ (err < 0)
        गच्छ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    जइ (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    प्रत्यागम err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

स्थिर अन्तःस्थ cl_mem_flags opencl_mem_flags_for_mapping(पूर्णाङ्क map_flags)
{
    जइ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        प्रत्यागम CL_MEM_READ_WRITE;
    अण्णहा जइ (map_flags & AV_HWFRAME_MAP_READ)
        प्रत्यागम CL_MEM_READ_ONLY;
    अण्णहा जइ (map_flags & AV_HWFRAME_MAP_WRITE)
        प्रत्यागम CL_MEM_WRITE_ONLY;
    अण्णहा
        प्रत्यागम 0;
}

#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA

स्थिर शून्य opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    प्रति (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        जइ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

स्थिर पूर्णाङ्क opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ध्रुव AVFrame *src, पूर्णाङ्क flags)
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
    पूर्णाङ्क err, p;

#जइ CONFIG_LIBMFX
    जइ (src->format == AV_PIX_FMT_QSV) {
        शून्य *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        जइ (err < 0)
            प्रत्यागम err;
        va_surface = *(VASurfaceID *)base_handle;
    } अण्णहा
#endif
        जइ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } अण्णहा {
        प्रत्यागम AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    जइ (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(परिमाण(*desc));
    जइ (!desc)
        प्रत्यागम AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    प्रति (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        जइ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        गच्छ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    जइ (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < desc->nb_planes; p++)
        जइ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, परिमाण(dst->data));
    प्रत्यागम err;
}

#endif

#जइ HAVE_OPENCL_DXVA2

स्थिर शून्य opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        प्रत्यागम;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

स्थिर पूर्णाङ्क opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
        जइ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            भङ्ग;
    }
    जइ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    जइ (err < 0)
        गच्छ fail;

    प्रति (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, परिमाण(dst->data));
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णाङ्क err, i, p, nb_planes;

    जइ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    nb_planes = 2;

    जइ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    जइ (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  परिमाण(*frames_priv->mapped_frames));
    जइ (!frames_priv->mapped_frames)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = रिक्त,
        };
        desc->nb_planes = nb_planes;
        प्रति (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            जइ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }
        }
    }

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            जइ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    प्रत्यागम err;
}

#endif

#जइ HAVE_OPENCL_D3D11

स्थिर शून्य opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

स्थिर पूर्णाङ्क opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क err, index, i;

    index = (intptr_t)src->data[1];
    जइ (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    जइ (err < 0)
        गच्छ fail;

    प्रति (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    जइ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, परिमाण(dst->data));
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णाङ्क err, i, p, nb_planes;

    जइ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    nb_planes = 2;

    जइ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    जइ (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  परिमाण(*frames_priv->mapped_frames));
    जइ (!frames_priv->mapped_frames)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        प्रति (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            जइ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned पूर्णाङ्क)subresource, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }
        }
    }

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            जइ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    प्रत्यागम err;
}

#endif

#जइ HAVE_OPENCL_DRM_ARM

प्रकारनिर्देश संरचना DRMARMtoOpenCLMapping {
    पूर्णाङ्क nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    पूर्णाङ्क nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

स्थिर शून्य opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    पूर्णाङ्क i;

    प्रति (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    प्रति (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

स्थिर पूर्णाङ्क opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ध्रुव AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = रिक्त;
    cl_mem_flags cl_flags;
    ध्रुव cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    पूर्णाङ्क err, i, j;

    desc = (ध्रुव AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    जइ (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    mapping = av_mallocz(परिमाण(*mapping));
    जइ (!mapping)
        प्रत्यागम AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    प्रति (i = 0; i < desc->nb_objects; i++) {
        पूर्णाङ्क fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        जइ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        जइ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }
    }

    mapping->nb_planes = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        ध्रुव AVDRMLayerDescriptor *layer = &desc->layers[i];

        प्रति (j = 0; j < layer->nb_planes; j++) {
            ध्रुव AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            पूर्णाङ्क p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            जइ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                गच्छ fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            जइ (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, रिक्त, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            जइ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            ++mapping->nb_planes;
        }
    }

    प्रति (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    जइ (err < 0)
        गच्छ fail;

    dst->width  = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    प्रति (i = 0; i < mapping->nb_objects; i++) {
        जइ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, परिमाण(dst->data));
    प्रत्यागम err;
}

#endif

#जइ HAVE_OPENCL_VIDEOTOOLBOX

स्थिर शून्य opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

स्थिर पूर्णाङ्क opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = रिक्त;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    जइ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        प्रत्यागम AVERROR_EXTERNAL;
    }

    desc = av_mallocz(परिमाण(*desc));
    जइ (!desc)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (पूर्णाङ्क p = 0;; p++) {
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
        जइ (err == AVERROR(ENOENT))
            भङ्ग;
        जइ (err < 0)
            गच्छ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        जइ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            गच्छ fail;
        }
        desc->nb_planes++;
    }

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    जइ (err < 0)
        गच्छ fail;

    dst->width = src->width;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (पूर्णाङ्क i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    प्रत्यागम err;
}

#endif

स्थिर पूर्णाङ्क opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    जइ (hwfc->sw_format != dst->format)
        प्रत्यागम AVERROR(ENOSYS);
    प्रत्यागम opencl_map_frame(hwfc, dst, src, flags);
}

स्थिर पूर्णाङ्क opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    विकल्प (src->format) {
#जइ HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        जइ (priv->beignet_drm_mapping_usable)
            प्रत्यागम opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VAAPI_BEIGNET
    पक्ष AV_PIX_FMT_VAAPI:
        जइ (priv->beignet_drm_mapping_usable)
            प्रत्यागम opencl_map_from_vaapi(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पक्ष AV_PIX_FMT_QSV:
    पक्ष AV_PIX_FMT_VAAPI:
        जइ (priv->qsv_mapping_usable)
            प्रत्यागम opencl_map_from_qsv(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_DXVA2
    पक्ष AV_PIX_FMT_DXVA2_VLD:
        जइ (priv->dxva2_mapping_usable)
            प्रत्यागम opencl_map_from_dxva2(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_D3D11
    पक्ष AV_PIX_FMT_D3D11:
        जइ (priv->d3d11_mapping_usable)
            प्रत्यागम opencl_map_from_d3d11(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_DRM_ARM
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        जइ (priv->drm_arm_mapping_usable)
            प्रत्यागम opencl_map_from_drm_arm(hwfc, dst, src, flags);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_PIX_FMT_VIDEOTOOLBOX:
        प्रत्यागम opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    प्रत्यागम AVERROR(ENOSYS);
}

स्थिर पूर्णाङ्क opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    विकल्प (src_fc->device_ctx->type) {
#जइ HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_DRM:
        जइ (!priv->beignet_drm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VAAPI_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        जइ (!priv->beignet_drm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पक्ष AV_HWDEVICE_TYPE_QSV:
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        जइ (!priv->qsv_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        जइ (!priv->dxva2_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        {
            पूर्णाङ्क err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            जइ (err < 0)
                प्रत्यागम err;
        }
        भङ्ग;
#endif
#जइ HAVE_OPENCL_D3D11
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        जइ (!priv->d3d11_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        {
            पूर्णाङ्क err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            जइ (err < 0)
                प्रत्यागम err;
        }
        भङ्ग;
#endif
#जइ HAVE_OPENCL_DRM_ARM
    पक्ष AV_HWDEVICE_TYPE_DRM:
        जइ (!priv->drm_arm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#endif
#जइ HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        भङ्ग;
#endif
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }
    प्रत्यागम opencl_frames_init_command_queue(dst_fc);
}

ध्रुव HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = परिमाण(OpenCLDeviceContext),
    .frames_hwctx_size      = परिमाण(OpenCLFramesContext),

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

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
