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

#परिभाषय CL_USE_DEPRECATED_OPENCL_1_2_APIS

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

#यदि HAVE_OPENCL_VAAPI_BEIGNET
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <va/va.h>
#अन्तर्भाव <va/va_drmcommon.h>
#अन्तर्भाव <CL/cl_intel.h>
#अन्तर्भाव "hwcontext_vaapi.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_BEIGNET
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <CL/cl_intel.h>
#अन्तर्भाव "hwcontext_drm.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
#यदि CONFIG_LIBMFX
#अन्तर्भाव <mfxstructures.h>
#यदि_अन्तः
#अन्तर्भाव <va/va.h>
#अन्तर्भाव <CL/cl_va_api_media_sharing_intel.h>
#अन्तर्भाव "hwcontext_vaapi.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2
#परिभाषय COBJMACROS
#अन्तर्भाव <CL/cl_dx9_media_sharing.h>
#अन्तर्भाव <dxva2api.h>
#अन्तर्भाव "hwcontext_dxva2.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11
#अन्तर्भाव <CL/cl_d3d11.h>
#अन्तर्भाव "hwcontext_d3d11va.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM
#अन्तर्भाव <CL/cl_ext.h>
#अन्तर्भाव <drm_fourcc.h>
#अन्तर्भाव "hwcontext_drm.h"
#यदि_अन्तः

#यदि HAVE_OPENCL_VIDEOTOOLBOX
#अन्तर्भाव <OpenCL/cl_gl_ext.h>
#अन्तर्भाव <VideoToolbox/VideoToolbox.h>
#यदि_अन्तः

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
बाह्य पूर्णाङ्क ff_qsv_get_surface_आधारः_handle(mfxFrameSurface1 *surf,
                                          गणना AVHWDeviceType आधारः_dev_typ,
                                          शून्य **आधारः_handle);
#यदि_अन्तः


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
#यदि HAVE_OPENCL_DRM_BEIGNET
    पूर्णाङ्क beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#यदि_अन्तः

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पूर्णाङ्क qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    cl_पङ्क्तौ_निक्षिप_Acquire_VA_APIMedia_Surfaces_INTEL_fn
        cl_पङ्क्तौ_निक्षिप_Acquire_VA_APIMedia_Surfaces_INTEL;
    cl_पङ्क्तौ_निक्षिप_Release_VA_APIMedia_Surfaces_INTEL_fn
        cl_पङ्क्तौ_निक्षिप_Release_VA_APIMedia_Surfaces_INTEL;
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2
    पूर्णाङ्क dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    cl_पङ्क्तौ_निक्षिप_Acquire_DX9_Media_Surfaces_KHR_fn
        cl_पङ्क्तौ_निक्षिप_Acquire_DX9_Media_Surfaces_KHR;
    cl_पङ्क्तौ_निक्षिप_Release_DX9_Media_Surfaces_KHR_fn
        cl_पङ्क्तौ_निक्षिप_Release_DX9_Media_Surfaces_KHR;
#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11
    पूर्णाङ्क d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    cl_पङ्क्तौ_निक्षिप_Acquire_D3_D11_Objects_KHR_fn
        cl_पङ्क्तौ_निक्षिप_Acquire_D3_D11_Objects_KHR;
    cl_पङ्क्तौ_निक्षिप_Release_D3_D11_Objects_KHR_fn
        cl_पङ्क्तौ_निक्षिप_Release_D3_D11_Objects_KHR;
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM
    पूर्णाङ्क drm_arm_mapping_usable;
#यदि_अन्तः
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

#यदि HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    पूर्णाङ्क                   nb_mapped_चौकटाः;
    AVOpenCLFrameDescriptor *mapped_चौकटाः;
#यदि_अन्तः
} OpenCLFramesContext;


स्थिर शून्य CL_CALLBACK opencl_error_callback(ध्रुव वर्ण *errinfo,
                                              ध्रुव शून्य *वैयक्तिकम्_info,
                                              size_t cb,
                                              शून्य *user_दत्त)
{
    AVHWDeviceContext *ctx = user_दत्त;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

स्थिर शून्य opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

स्थिर संरचना {
    ध्रुव वर्ण *कुञ्चिका;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_संस्करणम्    },
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
    { "driver_version",      CL_DRIVER_संस्करणम्      },
    { "device_version",      CL_DEVICE_संस्करणम्      },
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
    size_t आकार;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, कुञ्चिका, 0, रिक्त, &आकार);
    यदि (cle != CL_SUCCESS)
        प्रत्यागम रिक्त;
    str = av_malloc(आकार);
    यदि (!str)
        प्रत्यागम रिक्त;
    cle = clGetPlatformInfo(platform_id, कुञ्चिका, आकार, str, &आकार);
    यदि (cle != CL_SUCCESS) {
        av_free(str);
        प्रत्यागम रिक्त;
    }
    av_assert0(वाक्यदैर्घ्यम्(str) + 1 == आकार);
    प्रत्यागम str;
}

स्थिर वर्ण *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info कुञ्चिका)
{
    वर्ण *str;
    size_t आकार;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, कुञ्चिका, 0, रिक्त, &आकार);
    यदि (cle != CL_SUCCESS)
        प्रत्यागम रिक्त;
    str = av_malloc(आकार);
    यदि (!str)
        प्रत्यागम रिक्त;
    cle = clGetDeviceInfo(device_id, कुञ्चिका, आकार, str, &आकार);
    यदि (cle != CL_SUCCESS) {
        av_free(str);
        प्रत्यागम रिक्त;
    }
    av_assert0(वाक्यदैर्घ्यम्(str) + 1== आकार);
    प्रत्यागम str;
}

स्थिर पूर्णाङ्क opencl_check_platform_extension(cl_platform_id platform_id,
                                           ध्रुव वर्ण *name)
{
    वर्ण *str;
    पूर्णाङ्क प्राप्तम् = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    यदि (str && वाक्ये_अन्विष(str, name))
        प्राप्तम् = 1;
    av_free(str);
    प्रत्यागम प्राप्तम्;
}

स्थिर पूर्णाङ्क opencl_check_device_extension(cl_device_id device_id,
                                         ध्रुव वर्ण *name)
{
    वर्ण *str;
    पूर्णाङ्क प्राप्तम् = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    यदि (str && वाक्ये_अन्विष(str, name))
        प्राप्तम् = 1;
    av_free(str);
    प्रत्यागम प्राप्तम्;
}

av_अप्रयुक्तम् स्थिर पूर्णाङ्क opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ध्रुव वर्ण *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    यदि (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        प्रत्यागम 1;
    }

    यदि (opencl_check_device_extension(hwctx->device_id, name)) {
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
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        प्रत्यागम AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, परिमाण(**platforms));
    यदि (!*platforms)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, रिक्त);
    यदि (cle != CL_SUCCESS) {
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
    ध्रुव AVDictionary_प्रविष्टिः *param;
    वर्ण *str;
    पूर्णाङ्क i, ret = 0;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].कुञ्चिका,
                            रिक्त, 0);
        यदि (!param)
            अनुवर्त;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        यदि (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].कुञ्चिका, platform_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }
        यदि (!av_stristr(str, param->मानम्)) {
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
    यदि (cle == CL_DEVICE_NOT_प्राप्तम्) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अन्यथा यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    यदि (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, रिक्त);
    यदि (cle != CL_SUCCESS) {
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
    ध्रुव AVDictionary_प्रविष्टिः *param;
    वर्ण *str;
    पूर्णाङ्क i, ret = 0;

    param = av_dict_get(opts, "device_type", रिक्त, 0);
    यदि (param) {
        cl_device_type मेलनम्_type = 0, device_type;
        cl_int cle;

        प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            यदि (!वाक्यं_तुलय(opencl_device_types[i].कुञ्चिका, param->मानम्)) {
                मेलनम्_type = opencl_device_types[i].type;
                भङ्ग;
            }
        }
        यदि (!मेलनम्_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->मानम्);
            प्रत्यागम AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              परिमाण(device_type), &device_type, रिक्त);
        यदि (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }

        यदि (!(device_type & मेलनम्_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            प्रत्यागम 1;
        }
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].कुञ्चिका,
                            रिक्त, 0);
        यदि (!param)
            अनुवर्त;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        यदि (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].कुञ्चिका, device_name);
            प्रत्यागम AVERROR_UNKNOWN;
        }
        यदि (!av_stristr(str, param->मानम्)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->कुञ्चिका, str);
            ret = 1;
        }
        av_free(str);
    }

    प्रत्यागम ret;
}

प्रकारनिर्देश संरचना OpenCLDeviceSelector {
    पूर्णाङ्क platform_सूचकांक;
    पूर्णाङ्क device_सूचकांक;
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

स्थिर पूर्णाङ्क opencl_device_create_आन्तरिकम्(AVHWDeviceContext *hwdev,
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
    पूर्णाङ्क err, प्राप्तम्, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    यदि (err)
        प्रत्यागम err;

    प्राप्तम् = 0;
    प्रति (p = 0; p < nb_platforms; p++) {
        ध्रुव वर्ण *platform_name;

        यदि (selector->platform_सूचकांक >= 0 &&
            selector->platform_सूचकांक != p)
            अनुवर्त;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        यदि (platform_name_src)
            platform_name = platform_name_src;
        अन्यथा
            platform_name = "Unknown Platform";

        यदि (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            यदि (err < 0)
                गच्छ fail;
            यदि (err > 0)
                अनुवर्त;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        यदि (err < 0)
            अनुवर्त;

        प्रति (d = 0; d < nb_devices; d++) {
            ध्रुव वर्ण *device_name;

            यदि (selector->device_सूचकांक >= 0 &&
                selector->device_सूचकांक != d)
                अनुवर्त;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            यदि (device_name_src)
                device_name = device_name_src;
            अन्यथा
                device_name = "Unknown Device";

            यदि (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                यदि (err < 0)
                    गच्छ fail;
                यदि (err > 0)
                    अनुवर्त;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++प्राप्तम्;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    यदि (प्राप्तम् == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        गच्छ fail;
    }
    यदि (प्राप्तम् > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        गच्छ fail;
    }

    यदि (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } अन्यथा {
        यदि (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    यदि (!hwctx->context) {
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

    यदि (device && device[0]) {
        // Match one or both indices for platform and device.
        पूर्णाङ्क d = -1, p = -1, ret;
        यदि (device[0] == '.')
            ret = वाक्यात्_पठ(device, ".%d", &d);
        अन्यथा
            ret = वाक्यात्_पठ(device, "%d.%d", &p, &d);
        यदि (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            प्रत्यागम AVERROR(EINVAL);
        }
        selector.platform_सूचकांक = p;
        selector.device_सूचकांक   = d;
    } अन्यथा {
        selector.platform_सूचकांक = -1;
        selector.device_सूचकांक   = -1;
    }

    प्रत्यागम opencl_device_create_आन्तरिकम्(hwdev, &selector, रिक्त);
}

स्थिर पूर्णाङ्क opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    यदि (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        यदि (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            प्रत्यागम AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } अन्यथा {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        यदि (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            प्रत्यागम AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          परिमाण(priv->platform_id), &priv->platform_id,
                          रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        प्रत्यागम AVERROR(EIO);
    }

#परिभाषय CL_FUNC(name, desc) कुरु {                                \
        यदि (fail)                                               \
            भङ्ग;                                              \
        priv->name = cl_Get_Extension_Function_स्थानाङ्कः_For_Platform(  \
            priv->platform_id, #name);                          \
        यदि (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } अन्यथा {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } यावत् (0)

#यदि HAVE_OPENCL_DRM_BEIGNET
    {
        पूर्णाङ्क fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        यदि (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } अन्यथा {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#यदि_अन्तः

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_आकार;
        cl_context_properties *props = रिक्त;
        VADisplay va_display;
        ध्रुव वर्ण *va_ext = "cl_intel_va_api_media_sharing";
        पूर्णाङ्क i, fail = 0;

        यदि (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            गच्छ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, रिक्त, &props_आकार);
        यदि (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            गच्छ no_qsv;
        }
        यदि (props_आकार == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }

        props = av_malloc(props_आकार);
        यदि (!props)
            प्रत्यागम AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_आकार, props, रिक्त);
        यदि (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            गच्छ no_qsv;
        }

        va_display = रिक्त;
        प्रति (i = 0; i < (props_आकार / परिमाण(*props) - 1); i++) {
            यदि (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                भङ्ग;
            }
        }
        यदि (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }
        यदि (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            गच्छ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Acquire_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Release_VA_APIMedia_Surfaces_INTEL,
                "Intel QSV in OpenCL release");

        यदि (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } अन्यथा {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2
    {
        पूर्णाङ्क fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Acquire_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Release_DX9_Media_Surfaces_KHR,
                "DXVA2 in OpenCL release");

        यदि (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } अन्यथा {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11
    {
        ध्रुव वर्ण *d3d11_ext = "cl_khr_d3d11_sharing";
        ध्रुव वर्ण *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        पूर्णाङ्क fail = 0;

        यदि (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } अन्यथा यदि (!opencl_check_extension(hwdev, nv12_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension may be "
                   "required for D3D11 to OpenCL mapping.\n", nv12_ext);
            // Not fatal.
        }

        CL_FUNC(clCreateFromD3D11Texture2DKHR,
                "D3D11 to OpenCL mapping");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Acquire_D3_D11_Objects_KHR,
                "D3D11 in OpenCL acquire");
        CL_FUNC(cl_पङ्क्तौ_निक्षिप_Release_D3_D11_Objects_KHR,
                "D3D11 in OpenCL release");

        यदि (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } अन्यथा {
            priv->d3d11_mapping_usable = 1;
        }
    }
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM
    {
        ध्रुव वर्ण *drm_arm_ext = "cl_arm_import_memory";
        ध्रुव वर्ण *image_ext   = "cl_khr_image2d_from_buffer";
        पूर्णाङ्क fail = 0;

        यदि (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        यदि (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        यदि (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } अन्यथा {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#यदि_अन्तः

#अपरिभाषय CL_FUNC

    प्रत्यागम 0;
}

स्थिर शून्य opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    यदि (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        यदि (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = रिक्त;
    }
}

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
स्थिर पूर्णाङ्क opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ध्रुव वर्ण *platform_name,
                                                    शून्य *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    यदि (!cl_Get_Extension_Function_स्थानाङ्कः_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        प्रत्यागम 1;
    } अन्यथा {
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
        cl_Get_Extension_Function_स्थानाङ्कः_For_Platform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    यदि (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, रिक्त, nb_devices);
    यदि (cle == CL_DEVICE_NOT_प्राप्तम्) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अन्यथा यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    यदि (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, रिक्त);
    यदि (cle != CL_SUCCESS) {
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

    यदि (opencl_check_device_extension(device_id, va_ext)) {
        प्रत्यागम 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        प्रत्यागम 1;
    }
}
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2
स्थिर पूर्णाङ्क opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ध्रुव वर्ण *platform_name,
                                        शून्य *context)
{
    ध्रुव वर्ण *dx9_ext = "cl_khr_dx9_media_sharing";

    यदि (opencl_check_platform_extension(platform_id, dx9_ext)) {
        प्रत्यागम 0;
    } अन्यथा {
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
        cl_Get_Extension_Function_स्थानाङ्कः_For_Platform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    यदि (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (शून्य**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, रिक्त, nb_devices);
    यदि (cle == CL_DEVICE_NOT_प्राप्तम्) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अन्यथा यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    यदि (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (शून्य**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}
#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11
स्थिर पूर्णाङ्क opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ध्रुव वर्ण *platform_name,
                                        शून्य *context)
{
    ध्रुव वर्ण *d3d11_ext = "cl_khr_d3d11_sharing";

    यदि (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        प्रत्यागम 0;
    } अन्यथा {
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
        cl_Get_Extension_Function_स्थानाङ्कः_For_Platform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    यदि (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, रिक्त, nb_devices);
    यदि (cle == CL_DEVICE_NOT_प्राप्तम्) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        प्रत्यागम 0;
    } अन्यथा यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, परिमाण(**devices));
    यदि (!*devices)
        प्रत्यागम AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
स्थिर पूर्णाङ्क opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ध्रुव वर्ण *device_name,
                                    शून्य *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          परिमाण(device_type), &device_type, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        प्रत्यागम AVERROR_UNKNOWN;
    }
    यदि (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        प्रत्यागम 1;
    }

    प्रत्यागम 0;
}
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM
स्थिर पूर्णाङ्क opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ध्रुव वर्ण *platform_name,
                                          शून्य *context)
{
    ध्रुव वर्ण *drm_arm_ext = "cl_arm_import_memory";

    यदि (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        प्रत्यागम 0;
    } अन्यथा {
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

    यदि (opencl_check_device_extension(device_id, drm_arm_ext)) {
        प्रत्यागम 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        प्रत्यागम 1;
    }
}
#यदि_अन्तः

स्थिर पूर्णाङ्क opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                पूर्णाङ्क flags)
{
    पूर्णाङ्क err;
    विकल्प (src_ctx->type) {

#यदि HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_DRM:
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = रिक्त;

            err = av_dict_समुच्चयः(&selector_opts, "platform_vendor", "Intel", 0);
            यदि (err >= 0)
                err = av_dict_समुच्चयः(&selector_opts, "platform_version", "beignet", 0);
            यदि (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_सूचकांक      = -1,
                    .device_सूचकांक        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = रिक्त,
                };
                err = opencl_device_create_आन्तरिकम्(hwdev, &selector, रिक्त);
            }
            av_dict_free(&selector_opts);
        }
        भङ्ग;
#यदि_अन्तः

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
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
                .platform_सूचकांक      = -1,
                .device_सूचकांक        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_आन्तरिकम्(hwdev, &selector, props);
        }
        भङ्ग;
#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            यदि (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (अचिह्नित दीर्घ)hr);
                err = AVERROR_UNKNOWN;
                भङ्ग;
            }

            hr = IDirect3_DDevice_Manager9_तालकम्_Device(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            यदि (SUCCEEDED(hr)) {
                cl_context_properties props[5] = {
                    CL_CONTEXT_PLATFORM,
                    0,
                    CL_CONTEXT_ADAPTER_D3D9EX_KHR,
                    (intptr_t)device,
                    0,
                };
                OpenCLDeviceSelector selector = {
                    .platform_सूचकांक      = -1,
                    .device_सूचकांक        = -1,
                    .context             = device,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_dxva2_platform,
                    .enumerate_devices   = &opencl_enumerate_dxva2_devices,
                    .filter_device       = &opencl_filter_gpu_device,
                };

                err = opencl_device_create_आन्तरिकम्(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } अन्यथा {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (अचिह्नित दीर्घ)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        भङ्ग;
#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11
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
                .platform_सूचकांक      = -1,
                .device_सूचकांक        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_आन्तरिकम्(hwdev, &selector, props);
        }
        भङ्ग;
#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM
    पक्ष AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_सूचकांक      = -1,
                .device_सूचकांक        = -1,
                .context             = रिक्त,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_आन्तरिकम्(hwdev, &selector, रिक्त);
        }
        भङ्ग;
#यदि_अन्तः

#यदि HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, रिक्त, रिक्त, 0);
        भङ्ग;
#यदि_अन्तः

    स्वभाव:
        err = AVERROR(ENOSYS);
        भङ्ग;
    }

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_get_plane_format(गणना AVPixelFormat pixfmt,
                                   पूर्णाङ्क plane, पूर्णाङ्क विस्तारः, पूर्णाङ्क height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ध्रुव AVPixFmtDescriptor *desc;
    ध्रुव AVComponentDescriptor *comp;
    पूर्णाङ्क channels = 0, क्रमः = 0, गभीरता = 0, चरणः = 0;
    पूर्णाङ्क wsub, hsub, alpha;
    पूर्णाङ्क c;

    यदि (plane >= AV_अङ्कः_दत्त_सूचकाः)
        प्रत्यागम AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    यदि (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        प्रत्यागम AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    यदि (विस्तारः & wsub - 1 || height & hsub - 1)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        यदि (comp->plane != plane)
            अनुवर्त;
        // The step size must be a power of two.
        यदि (comp->चरणः != 1 && comp->चरणः != 2 &&
            comp->चरणः != 4 && comp->चरणः != 8)
            प्रत्यागम AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        यदि (comp->सरणम् + comp->गभीरता != 8 &&
            comp->सरणम् + comp->गभीरता != 16 &&
            comp->सरणम् + comp->गभीरता != 32)
            प्रत्यागम AVERROR(EINVAL);
        // The depth must not vary between components.
        यदि (गभीरता && comp->गभीरता != गभीरता)
            प्रत्यागम AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        यदि (comp->गभीरता > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            प्रत्यागम AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        यदि (चरणः && comp->चरणः != चरणः)
            प्रत्यागम AVERROR(EINVAL);

        गभीरता = comp->गभीरता;
        क्रमः = क्रमः * 10 + comp->विस्थापनम् / ((गभीरता + 7) / 8) + 1;
        चरणः  = comp->चरणः;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    यदि (channels == 0)
        प्रत्यागम AVERROR(ENOENT);

    स्मृतिं_पूरय(image_format, 0, परिमाण(*image_format));
    स्मृतिं_पूरय(image_desc,   0, परिमाण(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    यदि (plane == 0 || alpha) {
        image_desc->image_विस्तारः     = विस्तारः;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = चरणः * विस्तारः;
    } अन्यथा {
        image_desc->image_विस्तारः     = विस्तारः  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = चरणः * विस्तारः / wsub;
    }

    यदि (गभीरता <= 8) {
        image_format->image_channel_दत्त_type = CL_UNORM_INT8;
    } अन्यथा {
        यदि (गभीरता <= 16)
            image_format->image_channel_दत्त_type = CL_UNORM_INT16;
        अन्यथा यदि (गभीरता == 32)
            image_format->image_channel_दत्त_type = CL_FLOAT;
        अन्यथा
            प्रत्यागम AVERROR(EINVAL);
    }

#परिभाषय CHANNEL_क्रमः(क्रमः, type) \
    पक्ष क्रमः: image_format->image_channel_क्रमः = type; भङ्ग;
    विकल्प (क्रमः) {
        CHANNEL_क्रमः(1,    CL_R);
        CHANNEL_क्रमः(12,   CL_RG);
        CHANNEL_क्रमः(1234, CL_RGBA);
        CHANNEL_क्रमः(2341, CL_ARGB);
        CHANNEL_क्रमः(3214, CL_BGRA);
#यदि_परिभाषितम् CL_ABGR
        CHANNEL_क्रमः(4321, CL_ABGR);
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
#अपरिभाषय CHANNEL_क्रमः

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_चौकटाः_get_constraints(AVHWDeviceContext *hwdev,
                                         ध्रुव शून्य *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = रिक्त;
    cl_int cle;
    गणना AVPixelFormat pix_fmt;
    पूर्णाङ्क err, pix_fmts_प्राप्तम्;
    size_t max_विस्तारः, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2_D_MAX_विस्तारः,
                          परिमाण(max_विस्तारः), &max_विस्तारः, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } अन्यथा {
        constraints->max_विस्तारः = max_विस्तारः;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          परिमाण(max_height), &max_height, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } अन्यथा {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_विस्तारः, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, रिक्त, &nb_image_formats);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }
    यदि (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, परिमाण(*image_formats));
    यदि (!image_formats) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, रिक्त);
    यदि (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        गच्छ fail;
    }

    pix_fmts_प्राप्तम् = 0;
    प्रति (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        पूर्णाङ्क plane, i;

        प्रति (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            यदि (err < 0)
                भङ्ग;

            प्रति (i = 0; i < nb_image_formats; i++) {
                यदि (image_formats[i].image_channel_क्रमः ==
                    image_format.image_channel_क्रमः &&
                    image_formats[i].image_channel_दत्त_type ==
                    image_format.image_channel_दत्त_type)
                    भङ्ग;
            }
            यदि (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                भङ्ग;
            }
        }
        यदि (err != AVERROR(ENOENT))
            अनुवर्त;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_प्राप्तम् + 2,
                                परिमाण(*constraints->valid_sw_formats));
        यदि (err < 0)
            गच्छ fail;
        constraints->valid_sw_formats[pix_fmts_प्राप्तम्] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_प्राप्तम् + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_प्राप्तम्;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats) {
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

स्थिर शून्य opencl_pool_free(शून्य *opaque, uint8_t *दत्त)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)दत्त;
    cl_int cle;
    पूर्णाङ्क p;

    प्रति (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        यदि (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

स्थिर AVBufferRef *opencl_pool_alloc(शून्य *opaque, size_t आकार)
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
    यदि (!desc)
        प्रत्यागम रिक्त;

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->विस्तारः, hwfc->height,
                                      &image_format, &image_desc);
        यदि (err == AVERROR(ENOENT))
            भङ्ग;
        यदि (err < 0)
            गच्छ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, रिक्त, &cle);
        यदि (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            गच्छ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_बफर_create((uint8_t*)desc, परिमाण(*desc),
                           &opencl_pool_free, hwfc, 0);
    यदि (!ref)
        गच्छ fail;

    प्रत्यागम ref;

fail:
    प्रति (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क opencl_चौकटाः_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    यदि (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_चौकटाः_init(AVHWFramesContext *hwfc)
{
    यदि (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_आन्तरिकम् =
            av_बफर_pool_init2(परिमाण(cl_mem), hwfc,
                                 &opencl_pool_alloc, रिक्त);
        यदि (!ffhwframesctx(hwfc)->pool_आन्तरिकम्)
            प्रत्यागम AVERROR(ENOMEM);
    }

    प्रत्यागम opencl_चौकटाः_init_command_queue(hwfc);
}

स्थिर शून्य opencl_चौकटाः_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#यदि HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    पूर्णाङ्क i, p;
    प्रति (i = 0; i < priv->nb_mapped_चौकटाः; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_चौकटाः[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            यदि (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_चौकटाः);
#यदि_अन्तः

    यदि (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        यदि (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = रिक्त;
    }
}

स्थिर पूर्णाङ्क opencl_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    पूर्णाङ्क p;

    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->दत्त;

    प्रति (p = 0; p < desc->nb_planes; p++)
        frame->दत्त[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->विस्तारः   = hwfc->विस्तारः;
    frame->height  = hwfc->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       गणना AVHWFrameTransferDirection dir,
                                       गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
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
    यदि (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    प्रति (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        यदि (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opencl_transfer_दत्त_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ध्रुव AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क err, p;

    यदि (dst->format != hwfc->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->विस्तारः, src->height,
                                      &image_format, &image_desc);
        यदि (err < 0) {
            यदि (err == AVERROR(ENOENT))
                err = 0;
            भङ्ग;
        }

        यदि (!dst->दत्त[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            भङ्ग;
        }

        region[0] = image_desc.image_विस्तारः;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = cl_पङ्क्तौ_निक्षिप_Read_Image(priv->command_queue,
                                 (cl_mem)src->दत्त[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->दत्त[p],
                                 0, रिक्त, &events[p]);
        यदि (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            भङ्ग;
        }
    }

    opencl_wait_events(hwfc, events, p);

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_transfer_दत्त_गन्तव्यम्(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ध्रुव AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क err, p;

    यदि (src->format != hwfc->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->विस्तारः, src->height,
                                      &image_format, &image_desc);
        यदि (err < 0) {
            यदि (err == AVERROR(ENOENT))
                err = 0;
            भङ्ग;
        }

        यदि (!src->दत्त[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            भङ्ग;
        }

        region[0] = image_desc.image_विस्तारः;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = cl_पङ्क्तौ_निक्षिप_Write_Image(priv->command_queue,
                                  (cl_mem)dst->दत्त[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->दत्त[p],
                                  0, रिक्त, &events[p]);
        यदि (cle != CL_SUCCESS) {
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
    शून्य *स्थानाङ्कः[AV_अङ्कः_दत्त_सूचकाः];
} OpenCLMapping;

स्थिर शून्य opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क p, e;
    cl_int cle;

    प्रति (p = e = 0; p < FF_ARRAY_ELEMS(map->स्थानाङ्कः); p++) {
        यदि (!map->स्थानाङ्कः[p])
            भङ्ग;

        cle = cl_पङ्क्तौ_निक्षिप_Unmap_Mem_Object(priv->command_queue,
                                      (cl_mem)hwmap->source->दत्त[p],
                                      map->स्थानाङ्कः[p],
                                      0, रिक्त, &events[e]);
        यदि (cle != CL_SUCCESS) {
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
    cl_event events[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क err, p;

    av_assert0(hwfc->sw_format == dst->format);

    यदि (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } अन्यथा {
        map_flags = 0;
        यदि (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        यदि (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(परिमाण(*map));
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->विस्तारः, src->height,
                                      &image_format, &image_desc);
        यदि (err == AVERROR(ENOENT))
            भङ्ग;
        यदि (err < 0)
            गच्छ fail;

        region[0] = image_desc.image_विस्तारः;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->स्थानाङ्कः[p] =
            cl_पङ्क्तौ_निक्षिप_Map_Image(priv->command_queue,
                              (cl_mem)src->दत्त[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, रिक्त, 0, रिक्त,
                              &events[p], &cle);
        यदि (!map->स्थानाङ्कः[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }

        dst->दत्त[p] = map->स्थानाङ्कः[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->दत्त[p], dst->दत्त[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    यदि (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_create(src->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_frame, map);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < AV_अङ्कः_दत्त_सूचकाः; p++) {
        यदि (!map->स्थानाङ्कः[p])
            भङ्ग;
        cl_पङ्क्तौ_निक्षिप_Unmap_Mem_Object(priv->command_queue,
                                (cl_mem)src->दत्त[p],
                                map->स्थानाङ्कः[p],
                                0, रिक्त, &events[p]);
    }
    यदि (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    प्रत्यागम err;
}

#यदि HAVE_OPENCL_DRM_BEIGNET

प्रकारनिर्देश संरचना DRMBeignet_गन्तव्यम्_Open_CLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignet_गन्तव्यम्_Open_CLMapping;

स्थिर शून्य opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignet_गन्तव्यम्_Open_CLMapping *mapping = hwmap->priv;
    cl_int cle;
    पूर्णाङ्क i;

    प्रति (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        यदि (cle != CL_SUCCESS) {
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
    DRMBeignet_गन्तव्यम्_Open_CLMapping *mapping;
    ध्रुव AVDRMFrameDescriptor *desc;
    cl_int cle;
    पूर्णाङ्क err, i, j, p;

    desc = (ध्रुव AVDRMFrameDescriptor*)src->दत्त[0];

    mapping = av_mallocz(परिमाण(*mapping));
    यदि (!mapping)
        प्रत्यागम AVERROR(ENOMEM);

    p = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        ध्रुव AVDRMLayerDescriptor *layer = &desc->layers[i];
        प्रति (j = 0; j < layer->nb_planes; j++) {
            ध्रुव AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ध्रुव AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_सूचकांक];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .आकार      = object->आकार,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .विस्थापनम्    = plane->विस्थापनम्,
                .row_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->विस्तारः, src->height,
                                          &image_info.fmt,
                                          &image_desc);
            यदि (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                गच्छ fail;
            }
            image_info.विस्तारः  = image_desc.image_विस्तारः;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            यदि (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            dst->दत्त[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < mapping->frame.nb_planes; p++) {
        यदि (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    स्मृतिं_पूरय(dst->दत्त, 0, परिमाण(dst->दत्त));
    प्रत्यागम err;
}

#यदि HAVE_OPENCL_VAAPI_BEIGNET

स्थिर पूर्णाङ्क opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ध्रुव AVFrame *src,
                                 पूर्णाङ्क flags)
{
    AVFrame *tmp;
    पूर्णाङ्क err;

    tmp = av_frame_alloc();
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_अविभाज्यः;

    err = av_hwframe_map(tmp, src, flags);
    यदि (err < 0)
        गच्छ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    यदि (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    प्रत्यागम err;
}

#यदि_अन्तः /* HAVE_OPENCL_VAAPI_BEIGNET */
#यदि_अन्तः /* HAVE_OPENCL_DRM_BEIGNET */

स्थिर अन्तःस्थ cl_mem_flags opencl_mem_flags_for_mapping(पूर्णाङ्क map_flags)
{
    यदि ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        प्रत्यागम CL_MEM_READ_WRITE;
    अन्यथा यदि (map_flags & AV_HWFRAME_MAP_READ)
        प्रत्यागम CL_MEM_READ_ONLY;
    अन्यथा यदि (map_flags & AV_HWFRAME_MAP_WRITE)
        प्रत्यागम CL_MEM_WRITE_ONLY;
    अन्यथा
        प्रत्यागम 0;
}

#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA

स्थिर शून्य opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Release_VA_APIMedia_Surfaces_INTEL(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    प्रति (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        यदि (cle != CL_SUCCESS) {
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
        (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क err, p;

#यदि CONFIG_LIBMFX
    यदि (src->format == AV_PIX_FMT_QSV) {
        शून्य *आधारः_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->दत्त[3];
        err = ff_qsv_get_surface_आधारः_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &आधारः_handle);
        यदि (err < 0)
            प्रत्यागम err;
        va_surface = *(VASurfaceID *)आधारः_handle;
    } अन्यथा
#यदि_अन्तः
        यदि (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->दत्त[3];
    } अन्यथा {
        प्रत्यागम AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    यदि (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(परिमाण(*desc));
    यदि (!desc)
        प्रत्यागम AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    प्रति (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        यदि (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }

        dst->दत्त[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Acquire_VA_APIMedia_Surfaces_INTEL(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        गच्छ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    यदि (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (p = 0; p < desc->nb_planes; p++)
        यदि (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    स्मृतिं_पूरय(dst->दत्त, 0, परिमाण(dst->दत्त));
    प्रत्यागम err;
}

#यदि_अन्तः

#यदि HAVE_OPENCL_DXVA2

स्थिर शून्य opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap DXVA2 surface from OpenCL.\n");

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Release_DX9_Media_Surfaces_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
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
        (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
    AVDXVA2_चौकटाः_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->दत्त[3]);

    प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
        यदि (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->दत्त[3])
            भङ्ग;
    }
    यदि (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    desc = &चौकटाः_priv->mapped_चौकटाः[i];

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Acquire_DX9_Media_Surfaces_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    यदि (err < 0)
        गच्छ fail;

    प्रति (i = 0; i < desc->nb_planes; i++)
        dst->दत्त[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Release_DX9_Media_Surfaces_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    स्मृतिं_पूरय(dst->दत्त, 0, परिमाण(dst->दत्त));
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_चौकटाः_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    AVDXVA2_चौकटाः_Context  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णाङ्क err, i, p, nb_planes;

    यदि (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    nb_planes = 2;

    यदि (src_fc->initial_pool_आकार == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    यदि (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    चौकटाः_priv->nb_mapped_चौकटाः = src_hwctx->nb_surfaces;

    चौकटाः_priv->mapped_चौकटाः =
        av_calloc(चौकटाः_priv->nb_mapped_चौकटाः,
                  परिमाण(*चौकटाः_priv->mapped_चौकटाः));
    यदि (!चौकटाः_priv->mapped_चौकटाः)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < चौकटाः_priv->nb_mapped_चौकटाः; i++) {
        AVOpenCLFrameDescriptor *desc = &चौकटाः_priv->mapped_चौकटाः[i];
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
            यदि (!desc->planes[p]) {
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
    प्रति (i = 0; i < चौकटाः_priv->nb_mapped_चौकटाः; i++) {
        AVOpenCLFrameDescriptor *desc = &चौकटाः_priv->mapped_चौकटाः[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            यदि (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&चौकटाः_priv->mapped_चौकटाः);
    चौकटाः_priv->nb_mapped_चौकटाः = 0;
    प्रत्यागम err;
}

#यदि_अन्तः

#यदि HAVE_OPENCL_D3D11

स्थिर शून्य opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *चौकटाः_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Release_D3_D11_Objects_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

स्थिर पूर्णाङ्क opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *चौकटाः_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णाङ्क err, सूचकांक, i;

    सूचकांक = (intptr_t)src->दत्त[1];
    यदि (सूचकांक >= चौकटाः_priv->nb_mapped_चौकटाः) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", सूचकांक, चौकटाः_priv->nb_mapped_चौकटाः);
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           सूचकांक);

    desc = &चौकटाः_priv->mapped_चौकटाः[सूचकांक];

    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Acquire_D3_D11_Objects_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        प्रत्यागम AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    यदि (err < 0)
        गच्छ fail;

    प्रति (i = 0; i < desc->nb_planes; i++)
        dst->दत्त[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    cle = device_priv->cl_पङ्क्तौ_निक्षिप_Release_D3_D11_Objects_KHR(
        चौकटाः_priv->command_queue, desc->nb_planes, desc->planes,
        0, रिक्त, &event);
    यदि (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    स्मृतिं_पूरय(dst->दत्त, 0, परिमाण(dst->दत्त));
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क opencl_चौकटाः_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *चौकटाः_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णाङ्क err, i, p, nb_planes;

    यदि (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    nb_planes = 2;

    यदि (src_fc->initial_pool_आकार == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    यदि (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    चौकटाः_priv->nb_mapped_चौकटाः = src_fc->initial_pool_आकार;

    चौकटाः_priv->mapped_चौकटाः =
        av_calloc(चौकटाः_priv->nb_mapped_चौकटाः,
                  परिमाण(*चौकटाः_priv->mapped_चौकटाः));
    यदि (!चौकटाः_priv->mapped_चौकटाः)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < चौकटाः_priv->nb_mapped_चौकटाः; i++) {
        AVOpenCLFrameDescriptor *desc = &चौकटाः_priv->mapped_चौकटाः[i];
        desc->nb_planes = nb_planes;
        प्रति (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            यदि (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (अचिह्नित पूर्णाङ्क)subresource, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }
        }
    }

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < चौकटाः_priv->nb_mapped_चौकटाः; i++) {
        AVOpenCLFrameDescriptor *desc = &चौकटाः_priv->mapped_चौकटाः[i];
        प्रति (p = 0; p < desc->nb_planes; p++) {
            यदि (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&चौकटाः_priv->mapped_चौकटाः);
    चौकटाः_priv->nb_mapped_चौकटाः = 0;
    प्रत्यागम err;
}

#यदि_अन्तः

#यदि HAVE_OPENCL_DRM_ARM

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
        (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ध्रुव AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = रिक्त;
    cl_mem_flags cl_flags;
    ध्रुव cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    पूर्णाङ्क err, i, j;

    desc = (ध्रुव AVDRMFrameDescriptor*)src->दत्त[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    यदि (!cl_flags)
        प्रत्यागम AVERROR(EINVAL);

    mapping = av_mallocz(परिमाण(*mapping));
    यदि (!mapping)
        प्रत्यागम AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    प्रति (i = 0; i < desc->nb_objects; i++) {
        पूर्णाङ्क fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        यदि (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            cl_Import_स्मृतिः_ARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].आकार, &cle);
        यदि (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].आकार, cle);
            err = AVERROR(EIO);
            गच्छ fail;
        }
    }

    mapping->nb_planes = 0;
    प्रति (i = 0; i < desc->nb_layers; i++) {
        ध्रुव AVDRMLayerDescriptor *layer = &desc->layers[i];

        प्रति (j = 0; j < layer->nb_planes; j++) {
            ध्रुव AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_बफर;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_बफर_region region;
            पूर्णाङ्क p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->विस्तारः, src_fc->height,
                                          &image_format, &image_desc);
            यदि (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                गच्छ fail;
            }

            region.origin = plane->विस्थापनम्;
            region.आकार   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_बफर =
                cl_Create_Sub_बफर(mapping->object_buffers[plane->object_सूचकांक],
                                  cl_flags,
                                  CL_बफर_CREATE_TYPE_REGION,
                                  &region, &cle);
            यदि (!plane_बफर) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            image_desc.बफर = plane_बफर;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, रिक्त, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_बफर);

            यदि (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                गच्छ fail;
            }

            ++mapping->nb_planes;
        }
    }

    प्रति (i = 0; i < mapping->nb_planes; i++)
        dst->दत्त[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    प्रति (i = 0; i < mapping->nb_objects; i++) {
        यदि (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    स्मृतिं_पूरय(dst->दत्त, 0, परिमाण(dst->दत्त));
    प्रत्यागम err;
}

#यदि_अन्तः

#यदि HAVE_OPENCL_VIDEOTOOLBOX

स्थिर शून्य opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

स्थिर पूर्णाङ्क opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref) src->दत्त[3];
    IOSurfaceRef io_surface_ref = CVPixel_बफर_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = रिक्त;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    यदि (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        प्रत्यागम AVERROR_EXTERNAL;
    }

    desc = av_mallocz(परिमाण(*desc));
    यदि (!desc)
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
                                      src->विस्तारः, src->height,
                                      &image_format, &image_desc);
        यदि (err == AVERROR(ENOENT))
            भङ्ग;
        यदि (err < 0)
            गच्छ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        यदि (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            गच्छ fail;
        }
        desc->nb_planes++;
    }

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_planes; i++)
        dst->दत्त[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    यदि (err < 0)
        गच्छ fail;

    dst->विस्तारः = src->विस्तारः;
    dst->height = src->height;

    प्रत्यागम 0;

fail:
    प्रति (पूर्णाङ्क i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    प्रत्यागम err;
}

#यदि_अन्तः

स्थिर पूर्णाङ्क opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    यदि (hwfc->sw_format != dst->format)
        प्रत्यागम AVERROR(ENOSYS);
    प्रत्यागम opencl_map_frame(hwfc, dst, src, flags);
}

स्थिर पूर्णाङ्क opencl_map_गन्तव्यम्(AVHWFramesContext *hwfc, AVFrame *dst,
                         ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_अप्रयुक्तम् OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    विकल्प (src->format) {
#यदि HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        यदि (priv->beignet_drm_mapping_usable)
            प्रत्यागम opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VAAPI_BEIGNET
    पक्ष AV_PIX_FMT_VAAPI:
        यदि (priv->beignet_drm_mapping_usable)
            प्रत्यागम opencl_map_from_vaapi(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पक्ष AV_PIX_FMT_QSV:
    पक्ष AV_PIX_FMT_VAAPI:
        यदि (priv->qsv_mapping_usable)
            प्रत्यागम opencl_map_from_qsv(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_DXVA2
    पक्ष AV_PIX_FMT_DXVA2_VLD:
        यदि (priv->dxva2_mapping_usable)
            प्रत्यागम opencl_map_from_dxva2(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_D3D11
    पक्ष AV_PIX_FMT_D3D11:
        यदि (priv->d3d11_mapping_usable)
            प्रत्यागम opencl_map_from_d3d11(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_DRM_ARM
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        यदि (priv->drm_arm_mapping_usable)
            प्रत्यागम opencl_map_from_drm_arm(hwfc, dst, src, flags);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_PIX_FMT_VIDEOTOOLBOX:
        प्रत्यागम opencl_map_from_vt(hwfc, dst, src, flags);
#यदि_अन्तः
    }
    प्रत्यागम AVERROR(ENOSYS);
}

स्थिर पूर्णाङ्क opencl_चौकटाः_derive_गन्तव्यम्(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    av_अप्रयुक्तम् OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    विकल्प (src_fc->device_ctx->type) {
#यदि HAVE_OPENCL_DRM_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_DRM:
        यदि (!priv->beignet_drm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VAAPI_BEIGNET
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        यदि (!priv->beignet_drm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पक्ष AV_HWDEVICE_TYPE_QSV:
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        यदि (!priv->qsv_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        यदि (!priv->dxva2_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        {
            पूर्णाङ्क err;
            err = opencl_चौकटाः_derive_from_dxva2(dst_fc, src_fc, flags);
            यदि (err < 0)
                प्रत्यागम err;
        }
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_D3D11
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        यदि (!priv->d3d11_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        {
            पूर्णाङ्क err;
            err = opencl_चौकटाः_derive_from_d3d11(dst_fc, src_fc, flags);
            यदि (err < 0)
                प्रत्यागम err;
        }
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_DRM_ARM
    पक्ष AV_HWDEVICE_TYPE_DRM:
        यदि (!priv->drm_arm_mapping_usable)
            प्रत्यागम AVERROR(ENOSYS);
        भङ्ग;
#यदि_अन्तः
#यदि HAVE_OPENCL_VIDEOTOOLBOX
    पक्ष AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }
    प्रत्यागम opencl_चौकटाः_init_command_queue(dst_fc);
}

ध्रुव HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_आकार      = परिमाण(OpenCLDeviceContext),
    .चौकटाः_hwctx_आकार      = परिमाण(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .चौकटाः_get_constraints = &opencl_चौकटाः_get_constraints,
    .चौकटाः_init            = &opencl_चौकटाः_init,
    .चौकटाः_uninit          = &opencl_चौकटाः_uninit,
    .चौकटाः_get_बफर      = &opencl_get_बफर,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्       = &opencl_transfer_दत्त_गन्तव्यम्,
    .transfer_दत्त_from     = &opencl_transfer_दत्त_from,

    .map_from               = &opencl_map_from,
    .map_गन्तव्यम्                 = &opencl_map_गन्तव्यम्,
    .चौकटाः_derive_गन्तव्यम्       = &opencl_चौकटाः_derive_गन्तव्यम्,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
