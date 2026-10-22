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

#घोषणा CL_USE_DEPRECATED_OPENCL_1_2_APIS

#समावेश <string.h>

#समावेश "config.h"

#समावेश "avassert.h"
#समावेश "avstring.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_opencl.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"

#अगर HAVE_OPENCL_VAAPI_BEIGNET
#समावेश <unistd.h>
#समावेश <va/va.h>
#समावेश <va/va_drmcommon.h>
#समावेश <CL/cl_intel.h>
#समावेश "hwcontext_vaapi.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_BEIGNET
#समावेश <unistd.h>
#समावेश <CL/cl_intel.h>
#समावेश "hwcontext_drm.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
#अगर CONFIG_LIBMFX
#समावेश <mfxstructures.h>
#पूर्ण_अगर
#समावेश <va/va.h>
#समावेश <CL/cl_va_api_media_sharing_intel.h>
#समावेश "hwcontext_vaapi.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2
#घोषणा COBJMACROS
#समावेश <CL/cl_dx9_media_sharing.h>
#समावेश <dxva2api.h>
#समावेश "hwcontext_dxva2.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11
#समावेश <CL/cl_d3d11.h>
#समावेश "hwcontext_d3d11va.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM
#समावेश <CL/cl_ext.h>
#समावेश <drm_fourcc.h>
#समावेश "hwcontext_drm.h"
#पूर्ण_अगर

#अगर HAVE_OPENCL_VIDEOTOOLBOX
#समावेश <OpenCL/cl_gl_ext.h>
#समावेश <VideoToolbox/VideoToolbox.h>
#पूर्ण_अगर

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
बाह्य पूर्णांक ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          क्रमागत AVHWDeviceType base_dev_typ,
                                          व्योम **base_handle);
#पूर्ण_अगर


प्रकार काष्ठा OpenCLDeviceContext {
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
#अगर HAVE_OPENCL_DRM_BEIGNET
    पूर्णांक beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#पूर्ण_अगर

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
    पूर्णांक qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2
    पूर्णांक dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11
    पूर्णांक d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM
    पूर्णांक drm_arm_mapping_usable;
#पूर्ण_अगर
} OpenCLDeviceContext;

प्रकार काष्ठा OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#अगर HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    पूर्णांक                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#पूर्ण_अगर
} OpenCLFramesContext;


अटल व्योम CL_CALLBACK opencl_error_callback(स्थिर अक्षर *errinfo,
                                              स्थिर व्योम *private_info,
                                              माप_प्रकार cb,
                                              व्योम *user_तथ्य)
{
    AVHWDeviceContext *ctx = user_तथ्य;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

अटल व्योम opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

अटल काष्ठा {
    स्थिर अक्षर *कुंजी;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

अटल काष्ठा {
    स्थिर अक्षर *कुंजी;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

अटल काष्ठा {
    स्थिर अक्षर *कुंजी;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

अटल अक्षर *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info कुंजी)
{
    अक्षर *str;
    माप_प्रकार आकार;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, कुंजी, 0, शून्य, &आकार);
    अगर (cle != CL_SUCCESS)
        वापस शून्य;
    str = av_malloc(आकार);
    अगर (!str)
        वापस शून्य;
    cle = clGetPlatformInfo(platform_id, कुंजी, आकार, str, &आकार);
    अगर (cle != CL_SUCCESS) {
        av_free(str);
        वापस शून्य;
    }
    av_assert0(म_माप(str) + 1 == आकार);
    वापस str;
}

अटल अक्षर *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info कुंजी)
{
    अक्षर *str;
    माप_प्रकार आकार;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, कुंजी, 0, शून्य, &आकार);
    अगर (cle != CL_SUCCESS)
        वापस शून्य;
    str = av_malloc(आकार);
    अगर (!str)
        वापस शून्य;
    cle = clGetDeviceInfo(device_id, कुंजी, आकार, str, &आकार);
    अगर (cle != CL_SUCCESS) {
        av_free(str);
        वापस शून्य;
    }
    av_assert0(म_माप(str) + 1== आकार);
    वापस str;
}

अटल पूर्णांक opencl_check_platform_extension(cl_platform_id platform_id,
                                           स्थिर अक्षर *name)
{
    अक्षर *str;
    पूर्णांक found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    अगर (str && म_माला(str, name))
        found = 1;
    av_free(str);
    वापस found;
}

अटल पूर्णांक opencl_check_device_extension(cl_device_id device_id,
                                         स्थिर अक्षर *name)
{
    अक्षर *str;
    पूर्णांक found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    अगर (str && म_माला(str, name))
        found = 1;
    av_free(str);
    वापस found;
}

av_unused अटल पूर्णांक opencl_check_extension(AVHWDeviceContext *hwdev,
                                            स्थिर अक्षर *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    अगर (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        वापस 1;
    }

    अगर (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        वापस 1;
    }

    वापस 0;
}

अटल पूर्णांक opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      व्योम *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, शून्य, nb_platforms);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        वापस AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, माप(**platforms));
    अगर (!*platforms)
        वापस AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        वापस AVERROR(ENODEV);
    }

    वापस 0;
}

अटल पूर्णांक opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  स्थिर अक्षर *platform_name,
                                  व्योम *context)
{
    AVDictionary *opts = context;
    स्थिर AVDictionaryEntry *param;
    अक्षर *str;
    पूर्णांक i, ret = 0;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].कुंजी,
                            शून्य, 0);
        अगर (!param)
            जारी;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        अगर (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].कुंजी, platform_name);
            वापस AVERROR_UNKNOWN;
        }
        अगर (!av_stristr(str, param->मूल्य)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->कुंजी, str);
            ret = 1;
        }
        av_free(str);
    }

    वापस ret;
}

अटल पूर्णांक opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    स्थिर अक्षर *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    व्योम *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, शून्य, nb_devices);
    अगर (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        वापस 0;
    } अन्यथा अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        वापस AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, माप(**devices));
    अगर (!*devices)
        वापस AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        वापस AVERROR(ENODEV);
    }

    वापस 0;
}

अटल पूर्णांक opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                स्थिर अक्षर *device_name,
                                व्योम *context)
{
    AVDictionary *opts = context;
    स्थिर AVDictionaryEntry *param;
    अक्षर *str;
    पूर्णांक i, ret = 0;

    param = av_dict_get(opts, "device_type", शून्य, 0);
    अगर (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        क्रम (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            अगर (!म_भेद(opencl_device_types[i].कुंजी, param->मूल्य)) {
                match_type = opencl_device_types[i].type;
                अवरोध;
            }
        }
        अगर (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->मूल्य);
            वापस AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              माप(device_type), &device_type, शून्य);
        अगर (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            वापस AVERROR_UNKNOWN;
        }

        अगर (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            वापस 1;
        }
    }

    क्रम (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].कुंजी,
                            शून्य, 0);
        अगर (!param)
            जारी;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        अगर (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].कुंजी, device_name);
            वापस AVERROR_UNKNOWN;
        }
        अगर (!av_stristr(str, param->मूल्य)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->कुंजी, str);
            ret = 1;
        }
        av_free(str);
    }

    वापस ret;
}

प्रकार काष्ठा OpenCLDeviceSelector {
    पूर्णांक platform_सूचकांक;
    पूर्णांक device_सूचकांक;
    व्योम *context;
    पूर्णांक (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               व्योम *context);
    पूर्णांक (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               स्थिर अक्षर *platform_name,
                               व्योम *context);
    पूर्णांक (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               स्थिर अक्षर *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               व्योम *context);
    पूर्णांक (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               स्थिर अक्षर *device_name,
                               व्योम *context);
} OpenCLDeviceSelector;

अटल पूर्णांक opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         स्थिर OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = शून्य;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = शून्य;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    अक्षर *platform_name_src = शून्य,
         *device_name_src   = शून्य;
    पूर्णांक err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    अगर (err)
        वापस err;

    found = 0;
    क्रम (p = 0; p < nb_platforms; p++) {
        स्थिर अक्षर *platform_name;

        अगर (selector->platform_सूचकांक >= 0 &&
            selector->platform_सूचकांक != p)
            जारी;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        अगर (platform_name_src)
            platform_name = platform_name_src;
        अन्यथा
            platform_name = "Unknown Platform";

        अगर (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            अगर (err < 0)
                जाओ fail;
            अगर (err > 0)
                जारी;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        अगर (err < 0)
            जारी;

        क्रम (d = 0; d < nb_devices; d++) {
            स्थिर अक्षर *device_name;

            अगर (selector->device_सूचकांक >= 0 &&
                selector->device_सूचकांक != d)
                जारी;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            अगर (device_name_src)
                device_name = device_name_src;
            अन्यथा
                device_name = "Unknown Device";

            अगर (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                अगर (err < 0)
                    जाओ fail;
                अगर (err > 0)
                    जारी;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    अगर (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        जाओ fail;
    }
    अगर (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        जाओ fail;
    }

    अगर (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } अन्यथा {
        अगर (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    अगर (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        जाओ fail;
    }

    hwdev->मुक्त = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    वापस err;
}

अटल पूर्णांक opencl_device_create(AVHWDeviceContext *hwdev, स्थिर अक्षर *device,
                                AVDictionary *opts, पूर्णांक flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    अगर (device && device[0]) {
        // Match one or both indices for platform and device.
        पूर्णांक d = -1, p = -1, ret;
        अगर (device[0] == '.')
            ret = माला_पूछो(device, ".%d", &d);
        अन्यथा
            ret = माला_पूछो(device, "%d.%d", &p, &d);
        अगर (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            वापस AVERROR(EINVAL);
        }
        selector.platform_सूचकांक = p;
        selector.device_सूचकांक   = d;
    } अन्यथा {
        selector.platform_सूचकांक = -1;
        selector.device_सूचकांक   = -1;
    }

    वापस opencl_device_create_internal(hwdev, &selector, शून्य);
}

अटल पूर्णांक opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    अगर (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        अगर (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            वापस AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } अन्यथा {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        अगर (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            वापस AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          माप(priv->platform_id), &priv->platform_id,
                          शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        वापस AVERROR(EIO);
    }

#घोषणा CL_FUNC(name, desc) करो {                                \
        अगर (fail)                                               \
            अवरोध;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        अगर (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } अन्यथा {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } जबतक (0)

#अगर HAVE_OPENCL_DRM_BEIGNET
    {
        पूर्णांक fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        अगर (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } अन्यथा {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#पूर्ण_अगर

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        माप_प्रकार props_आकार;
        cl_context_properties *props = शून्य;
        VADisplay va_display;
        स्थिर अक्षर *va_ext = "cl_intel_va_api_media_sharing";
        पूर्णांक i, fail = 0;

        अगर (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            जाओ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, शून्य, &props_आकार);
        अगर (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            जाओ no_qsv;
        }
        अगर (props_आकार == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            जाओ no_qsv;
        }

        props = av_malloc(props_आकार);
        अगर (!props)
            वापस AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_आकार, props, शून्य);
        अगर (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            जाओ no_qsv;
        }

        va_display = शून्य;
        क्रम (i = 0; i < (props_आकार / माप(*props) - 1); i++) {
            अगर (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                अवरोध;
            }
        }
        अगर (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            जाओ no_qsv;
        }
        अगर (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            जाओ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        अगर (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } अन्यथा {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2
    {
        पूर्णांक fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        अगर (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } अन्यथा {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11
    {
        स्थिर अक्षर *d3d11_ext = "cl_khr_d3d11_sharing";
        स्थिर अक्षर *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        पूर्णांक fail = 0;

        अगर (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } अन्यथा अगर (!opencl_check_extension(hwdev, nv12_ext)) {
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

        अगर (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } अन्यथा {
            priv->d3d11_mapping_usable = 1;
        }
    }
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM
    {
        स्थिर अक्षर *drm_arm_ext = "cl_arm_import_memory";
        स्थिर अक्षर *image_ext   = "cl_khr_image2d_from_buffer";
        पूर्णांक fail = 0;

        अगर (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        अगर (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        अगर (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } अन्यथा {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#पूर्ण_अगर

#अघोषित CL_FUNC

    वापस 0;
}

अटल व्योम opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    अगर (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        अगर (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = शून्य;
    }
}

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
अटल पूर्णांक opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    स्थिर अक्षर *platform_name,
                                                    व्योम *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    अगर (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        वापस 1;
    } अन्यथा {
        वापस 0;
    }
}

अटल पूर्णांक opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      स्थिर अक्षर *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      व्योम *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    अगर (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        वापस AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, शून्य, nb_devices);
    अगर (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        वापस 0;
    } अन्यथा अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        वापस AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, माप(**devices));
    अगर (!*devices)
        वापस AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

अटल पूर्णांक opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  स्थिर अक्षर *device_name,
                                                  व्योम *context)
{
    स्थिर अक्षर *va_ext = "cl_intel_va_api_media_sharing";

    अगर (opencl_check_device_extension(device_id, va_ext)) {
        वापस 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        वापस 1;
    }
}
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2
अटल पूर्णांक opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        स्थिर अक्षर *platform_name,
                                        व्योम *context)
{
    स्थिर अक्षर *dx9_ext = "cl_khr_dx9_media_sharing";

    अगर (opencl_check_platform_extension(platform_id, dx9_ext)) {
        वापस 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        वापस 1;
    }
}

अटल पूर्णांक opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          स्थिर अक्षर *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          व्योम *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    अगर (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        वापस AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (व्योम**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, शून्य, nb_devices);
    अगर (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        वापस 0;
    } अन्यथा अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        वापस AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, माप(**devices));
    अगर (!*devices)
        वापस AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (व्योम**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}
#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11
अटल पूर्णांक opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        स्थिर अक्षर *platform_name,
                                        व्योम *context)
{
    स्थिर अक्षर *d3d11_ext = "cl_khr_d3d11_sharing";

    अगर (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        वापस 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        वापस 1;
    }
}

अटल पूर्णांक opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          स्थिर अक्षर *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          व्योम *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    अगर (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        वापस AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, शून्य, nb_devices);
    अगर (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        वापस 0;
    } अन्यथा अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        वापस AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, माप(**devices));
    अगर (!*devices)
        वापस AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
अटल पूर्णांक opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    स्थिर अक्षर *device_name,
                                    व्योम *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          माप(device_type), &device_type, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        वापस AVERROR_UNKNOWN;
    }
    अगर (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        वापस 1;
    }

    वापस 0;
}
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM
अटल पूर्णांक opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          स्थिर अक्षर *platform_name,
                                          व्योम *context)
{
    स्थिर अक्षर *drm_arm_ext = "cl_arm_import_memory";

    अगर (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        वापस 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        वापस 1;
    }
}

अटल पूर्णांक opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        स्थिर अक्षर *device_name,
                                        व्योम *context)
{
    स्थिर अक्षर *drm_arm_ext = "cl_arm_import_memory";

    अगर (opencl_check_device_extension(device_id, drm_arm_ext)) {
        वापस 0;
    } अन्यथा {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        वापस 1;
    }
}
#पूर्ण_अगर

अटल पूर्णांक opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                पूर्णांक flags)
{
    पूर्णांक err;
    चयन (src_ctx->type) {

#अगर HAVE_OPENCL_DRM_BEIGNET
    हाल AV_HWDEVICE_TYPE_DRM:
    हाल AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = शून्य;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            अगर (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            अगर (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_सूचकांक      = -1,
                    .device_सूचकांक        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = शून्य,
                };
                err = opencl_device_create_internal(hwdev, &selector, शून्य);
            }
            av_dict_free(&selector_opts);
        }
        अवरोध;
#पूर्ण_अगर

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    हाल AV_HWDEVICE_TYPE_VAAPI:
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

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        अवरोध;
#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            अगर (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (अचिन्हित दीर्घ)hr);
                err = AVERROR_UNKNOWN;
                अवरोध;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            अगर (SUCCEEDED(hr)) {
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

                err = opencl_device_create_internal(hwdev, &selector, props);

                IDirect3DDeviceManager9_UnlockDevice(src_hwctx->devmgr,
                                                     device_handle, FALSE);
            } अन्यथा {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (अचिन्हित दीर्घ)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        अवरोध;
#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11
    हाल AV_HWDEVICE_TYPE_D3D11VA:
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

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        अवरोध;
#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM
    हाल AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_सूचकांक      = -1,
                .device_सूचकांक        = -1,
                .context             = शून्य,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, शून्य);
        }
        अवरोध;
#पूर्ण_अगर

#अगर HAVE_OPENCL_VIDEOTOOLBOX
    हाल AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, शून्य, शून्य, 0);
        अवरोध;
#पूर्ण_अगर

    शेष:
        err = AVERROR(ENOSYS);
        अवरोध;
    }

    वापस err;
}

अटल पूर्णांक opencl_get_plane_format(क्रमागत AVPixelFormat pixfmt,
                                   पूर्णांक plane, पूर्णांक width, पूर्णांक height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    स्थिर AVPixFmtDescriptor *desc;
    स्थिर AVComponentDescriptor *comp;
    पूर्णांक channels = 0, order = 0, depth = 0, step = 0;
    पूर्णांक wsub, hsub, alpha;
    पूर्णांक c;

    अगर (plane >= AV_अंक_तथ्य_POINTERS)
        वापस AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    अगर (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        वापस AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    अगर (width & wsub - 1 || height & hsub - 1)
        वापस AVERROR(EINVAL);

    क्रम (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        अगर (comp->plane != plane)
            जारी;
        // The step size must be a power of two.
        अगर (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            वापस AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        अगर (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            वापस AVERROR(EINVAL);
        // The depth must not vary between components.
        अगर (depth && comp->depth != depth)
            वापस AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        अगर (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            वापस AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        अगर (step && comp->step != step)
            वापस AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    अगर (channels == 0)
        वापस AVERROR(ENOENT);

    स_रखो(image_format, 0, माप(*image_format));
    स_रखो(image_desc,   0, माप(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    अगर (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } अन्यथा {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    अगर (depth <= 8) {
        image_format->image_channel_तथ्य_type = CL_UNORM_INT8;
    } अन्यथा {
        अगर (depth <= 16)
            image_format->image_channel_तथ्य_type = CL_UNORM_INT16;
        अन्यथा अगर (depth == 32)
            image_format->image_channel_तथ्य_type = CL_FLOAT;
        अन्यथा
            वापस AVERROR(EINVAL);
    }

#घोषणा CHANNEL_ORDER(order, type) \
    हाल order: image_format->image_channel_order = type; अवरोध;
    चयन (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#अगर_घोषित CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#पूर्ण_अगर
    शेष:
        वापस AVERROR(EINVAL);
    }
#अघोषित CHANNEL_ORDER

    वापस 0;
}

अटल पूर्णांक opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         स्थिर व्योम *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = शून्य;
    cl_int cle;
    क्रमागत AVPixelFormat pix_fmt;
    पूर्णांक err, pix_fmts_found;
    माप_प्रकार max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          माप(max_width), &max_width, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } अन्यथा {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          माप(max_height), &max_height, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } अन्यथा {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, शून्य, &nb_image_formats);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        जाओ fail;
    }
    अगर (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        जाओ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, माप(*image_formats));
    अगर (!image_formats) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, शून्य);
    अगर (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        जाओ fail;
    }

    pix_fmts_found = 0;
    क्रम (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        पूर्णांक plane, i;

        क्रम (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            अगर (err < 0)
                अवरोध;

            क्रम (i = 0; i < nb_image_formats; i++) {
                अगर (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_तथ्य_type ==
                    image_format.image_channel_तथ्य_type)
                    अवरोध;
            }
            अगर (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                अवरोध;
            }
        }
        अगर (err != AVERROR(ENOENT))
            जारी;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                माप(*constraints->valid_sw_formats));
        अगर (err < 0)
            जाओ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;

fail:
    av_freep(&image_formats);
    वापस err;
}

अटल व्योम opencl_pool_free(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)तथ्य;
    cl_int cle;
    पूर्णांक p;

    क्रम (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

अटल AVBufferRef *opencl_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    पूर्णांक err, p;
    AVBufferRef *ref;

    desc = av_mallocz(माप(*desc));
    अगर (!desc)
        वापस शून्य;

    क्रम (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        अगर (err == AVERROR(ENOENT))
            अवरोध;
        अगर (err < 0)
            जाओ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, शून्य, &cle);
        अगर (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            जाओ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_बफर_create((uint8_t*)desc, माप(*desc),
                           &opencl_pool_free, hwfc, 0);
    अगर (!ref)
        जाओ fail;

    वापस ref;

fail:
    क्रम (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    वापस शून्य;
}

अटल पूर्णांक opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    अगर (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        वापस AVERROR(EIO);
    }

    वापस 0;
}

अटल पूर्णांक opencl_frames_init(AVHWFramesContext *hwfc)
{
    अगर (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_बफर_pool_init2(माप(cl_mem), hwfc,
                                 &opencl_pool_alloc, शून्य);
        अगर (!ffhwframesctx(hwfc)->pool_internal)
            वापस AVERROR(ENOMEM);
    }

    वापस opencl_frames_init_command_queue(hwfc);
}

अटल व्योम opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#अगर HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    पूर्णांक i, p;
    क्रम (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        क्रम (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            अगर (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#पूर्ण_अगर

    अगर (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = शून्य;
    }
}

अटल पूर्णांक opencl_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    पूर्णांक p;

    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->तथ्य;

    क्रम (p = 0; p < desc->nb_planes; p++)
        frame->तथ्य[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    वापस 0;
}

अटल पूर्णांक opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       क्रमागत AVHWFrameTransferDirection dir,
                                       क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;

    fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    वापस 0;
}

अटल पूर्णांक opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, पूर्णांक nb_events)
{
    cl_int cle;
    पूर्णांक i;

    cle = clWaitForEvents(nb_events, events);
    अगर (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        वापस AVERROR(EIO);
    }

    क्रम (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    वापस 0;
}

अटल पूर्णांक opencl_transfer_तथ्य_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, स्थिर AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    माप_प्रकार origin[3] = { 0, 0, 0 };
    माप_प्रकार region[3];
    cl_event events[AV_अंक_तथ्य_POINTERS];
    पूर्णांक err, p;

    अगर (dst->format != hwfc->sw_format)
        वापस AVERROR(EINVAL);

    क्रम (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        अगर (err < 0) {
            अगर (err == AVERROR(ENOENT))
                err = 0;
            अवरोध;
        }

        अगर (!dst->तथ्य[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            अवरोध;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->तथ्य[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->तथ्य[p],
                                 0, शून्य, &events[p]);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            अवरोध;
        }
    }

    opencl_wait_events(hwfc, events, p);

    वापस err;
}

अटल पूर्णांक opencl_transfer_तथ्य_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, स्थिर AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    माप_प्रकार origin[3] = { 0, 0, 0 };
    माप_प्रकार region[3];
    cl_event events[AV_अंक_तथ्य_POINTERS];
    पूर्णांक err, p;

    अगर (src->format != hwfc->sw_format)
        वापस AVERROR(EINVAL);

    क्रम (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        अगर (err < 0) {
            अगर (err == AVERROR(ENOENT))
                err = 0;
            अवरोध;
        }

        अगर (!src->तथ्य[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            अवरोध;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->तथ्य[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->तथ्य[p],
                                  0, शून्य, &events[p]);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            अवरोध;
        }
    }

    opencl_wait_events(hwfc, events, p);

    वापस err;
}

प्रकार काष्ठा OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    व्योम *address[AV_अंक_तथ्य_POINTERS];
} OpenCLMapping;

अटल व्योम opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_अंक_तथ्य_POINTERS];
    पूर्णांक p, e;
    cl_int cle;

    क्रम (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        अगर (!map->address[p])
            अवरोध;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->तथ्य[p],
                                      map->address[p],
                                      0, शून्य, &events[e]);
        अगर (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

अटल पूर्णांक opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            स्थिर AVFrame *src, पूर्णांक flags)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_map_flags map_flags;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    OpenCLMapping *map;
    माप_प्रकार origin[3] = { 0, 0, 0 };
    माप_प्रकार region[3];
    माप_प्रकार row_pitch;
    cl_event events[AV_अंक_तथ्य_POINTERS];
    पूर्णांक err, p;

    av_assert0(hwfc->sw_format == dst->format);

    अगर (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } अन्यथा {
        map_flags = 0;
        अगर (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        अगर (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(माप(*map));
    अगर (!map)
        वापस AVERROR(ENOMEM);

    क्रम (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        अगर (err == AVERROR(ENOENT))
            अवरोध;
        अगर (err < 0)
            जाओ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->तथ्य[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, शून्य, 0, शून्य,
                              &events[p], &cle);
        अगर (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            जाओ fail;
        }

        dst->तथ्य[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->तथ्य[p], dst->तथ्य[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    अगर (err < 0)
        जाओ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    क्रम (p = 0; p < AV_अंक_तथ्य_POINTERS; p++) {
        अगर (!map->address[p])
            अवरोध;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->तथ्य[p],
                                map->address[p],
                                0, शून्य, &events[p]);
    }
    अगर (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    वापस err;
}

#अगर HAVE_OPENCL_DRM_BEIGNET

प्रकार काष्ठा DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

अटल व्योम opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    पूर्णांक i;

    क्रम (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        अगर (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

अटल पूर्णांक opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, स्थिर AVFrame *src,
                                       पूर्णांक flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    स्थिर AVDRMFrameDescriptor *desc;
    cl_int cle;
    पूर्णांक err, i, j, p;

    desc = (स्थिर AVDRMFrameDescriptor*)src->तथ्य[0];

    mapping = av_mallocz(माप(*mapping));
    अगर (!mapping)
        वापस AVERROR(ENOMEM);

    p = 0;
    क्रम (i = 0; i < desc->nb_layers; i++) {
        स्थिर AVDRMLayerDescriptor *layer = &desc->layers[i];
        क्रम (j = 0; j < layer->nb_planes; j++) {
            स्थिर AVDRMPlaneDescriptor *plane = &layer->planes[j];
            स्थिर AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_सूचकांक];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .आकार      = object->आकार,
                .type      = CL_MEM_OBJECT_IMAGE2D,
                .offset    = plane->offset,
                .row_pitch = plane->pitch,
            };
            cl_image_desc image_desc;

            err = opencl_get_plane_format(dst_fc->sw_format, p,
                                          src->width, src->height,
                                          &image_info.fmt,
                                          &image_desc);
            अगर (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                जाओ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            अगर (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                जाओ fail;
            }

            dst->तथ्य[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    क्रम (p = 0; p < mapping->frame.nb_planes; p++) {
        अगर (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    स_रखो(dst->तथ्य, 0, माप(dst->तथ्य));
    वापस err;
}

#अगर HAVE_OPENCL_VAAPI_BEIGNET

अटल पूर्णांक opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, स्थिर AVFrame *src,
                                 पूर्णांक flags)
{
    AVFrame *tmp;
    पूर्णांक err;

    tmp = av_frame_alloc();
    अगर (!tmp)
        वापस AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_अभाज्य;

    err = av_hwframe_map(tmp, src, flags);
    अगर (err < 0)
        जाओ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    अगर (err < 0)
        जाओ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    वापस err;
}

#पूर्ण_अगर /* HAVE_OPENCL_VAAPI_BEIGNET */
#पूर्ण_अगर /* HAVE_OPENCL_DRM_BEIGNET */

अटल अंतरभूत cl_mem_flags opencl_mem_flags_for_mapping(पूर्णांक map_flags)
{
    अगर ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        वापस CL_MEM_READ_WRITE;
    अन्यथा अगर (map_flags & AV_HWFRAME_MAP_READ)
        वापस CL_MEM_READ_ONLY;
    अन्यथा अगर (map_flags & AV_HWFRAME_MAP_WRITE)
        वापस CL_MEM_WRITE_ONLY;
    अन्यथा
        वापस 0;
}

#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA

अटल व्योम opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    पूर्णांक p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    क्रम (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        अगर (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

अटल पूर्णांक opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               स्थिर AVFrame *src, पूर्णांक flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    पूर्णांक err, p;

#अगर CONFIG_LIBMFX
    अगर (src->format == AV_PIX_FMT_QSV) {
        व्योम *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->तथ्य[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        अगर (err < 0)
            वापस err;
        va_surface = *(VASurfaceID *)base_handle;
    } अन्यथा
#पूर्ण_अगर
        अगर (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->तथ्य[3];
    } अन्यथा {
        वापस AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    अगर (!cl_flags)
        वापस AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(माप(*desc));
    अगर (!desc)
        वापस AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    क्रम (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        अगर (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            जाओ fail;
        }

        dst->तथ्य[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        जाओ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    अगर (err < 0)
        जाओ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    क्रम (p = 0; p < desc->nb_planes; p++)
        अगर (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    स_रखो(dst->तथ्य, 0, माप(dst->तथ्य));
    वापस err;
}

#पूर्ण_अगर

#अगर HAVE_OPENCL_DXVA2

अटल व्योम opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        वापस;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

अटल पूर्णांक opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 स्थिर AVFrame *src, पूर्णांक flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णांक err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->तथ्य[3]);

    क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
        अगर (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->तथ्य[3])
            अवरोध;
    }
    अगर (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        वापस AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        वापस AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    अगर (err < 0)
        जाओ fail;

    क्रम (i = 0; i < desc->nb_planes; i++)
        dst->तथ्य[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    स_रखो(dst->तथ्य, 0, माप(dst->तथ्य));
    वापस err;
}

अटल पूर्णांक opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णांक flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णांक err, i, p, nb_planes;

    अगर (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        वापस AVERROR(EINVAL);
    }
    nb_planes = 2;

    अगर (src_fc->initial_pool_आकार == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        वापस AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    अगर (!cl_flags)
        वापस AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  माप(*frames_priv->mapped_frames));
    अगर (!frames_priv->mapped_frames)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = शून्य,
        };
        desc->nb_planes = nb_planes;
        क्रम (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            अगर (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                जाओ fail;
            }
        }
    }

    वापस 0;

fail:
    क्रम (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        क्रम (p = 0; p < desc->nb_planes; p++) {
            अगर (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    वापस err;
}

#पूर्ण_अगर

#अगर HAVE_OPENCL_D3D11

अटल व्योम opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

अटल पूर्णांक opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 स्थिर AVFrame *src, पूर्णांक flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    पूर्णांक err, सूचकांक, i;

    सूचकांक = (intptr_t)src->तथ्य[1];
    अगर (सूचकांक >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", सूचकांक, frames_priv->nb_mapped_frames);
        वापस AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           सूचकांक);

    desc = &frames_priv->mapped_frames[सूचकांक];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        वापस AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    अगर (err < 0)
        जाओ fail;

    क्रम (i = 0; i < desc->nb_planes; i++)
        dst->तथ्य[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, शून्य, &event);
    अगर (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    स_रखो(dst->तथ्य, 0, माप(dst->तथ्य));
    वापस err;
}

अटल पूर्णांक opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, पूर्णांक flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    पूर्णांक err, i, p, nb_planes;

    अगर (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        वापस AVERROR(EINVAL);
    }
    nb_planes = 2;

    अगर (src_fc->initial_pool_आकार == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        वापस AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    अगर (!cl_flags)
        वापस AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_आकार;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  माप(*frames_priv->mapped_frames));
    अगर (!frames_priv->mapped_frames)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        क्रम (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            अगर (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (अचिन्हित पूर्णांक)subresource, cle);
                err = AVERROR(EIO);
                जाओ fail;
            }
        }
    }

    वापस 0;

fail:
    क्रम (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        क्रम (p = 0; p < desc->nb_planes; p++) {
            अगर (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    वापस err;
}

#पूर्ण_अगर

#अगर HAVE_OPENCL_DRM_ARM

प्रकार काष्ठा DRMARMtoOpenCLMapping {
    पूर्णांक nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    पूर्णांक nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

अटल व्योम opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    पूर्णांक i;

    क्रम (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    क्रम (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

अटल पूर्णांक opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   स्थिर AVFrame *src, पूर्णांक flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    स्थिर AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = शून्य;
    cl_mem_flags cl_flags;
    स्थिर cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    पूर्णांक err, i, j;

    desc = (स्थिर AVDRMFrameDescriptor*)src->तथ्य[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    अगर (!cl_flags)
        वापस AVERROR(EINVAL);

    mapping = av_mallocz(माप(*mapping));
    अगर (!mapping)
        वापस AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    क्रम (i = 0; i < desc->nb_objects; i++) {
        पूर्णांक fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        अगर (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].आकार, &cle);
        अगर (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].आकार, cle);
            err = AVERROR(EIO);
            जाओ fail;
        }
    }

    mapping->nb_planes = 0;
    क्रम (i = 0; i < desc->nb_layers; i++) {
        स्थिर AVDRMLayerDescriptor *layer = &desc->layers[i];

        क्रम (j = 0; j < layer->nb_planes; j++) {
            स्थिर AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_बफर;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_बफर_region region;
            पूर्णांक p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            अगर (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                जाओ fail;
            }

            region.origin = plane->offset;
            region.आकार   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_बफर =
                cl_Create_Sub_बफर(mapping->object_buffers[plane->object_सूचकांक],
                                  cl_flags,
                                  CL_बफर_CREATE_TYPE_REGION,
                                  &region, &cle);
            अगर (!plane_बफर) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                जाओ fail;
            }

            image_desc.बफर = plane_बफर;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, शून्य, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_बफर);

            अगर (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                जाओ fail;
            }

            ++mapping->nb_planes;
        }
    }

    क्रम (i = 0; i < mapping->nb_planes; i++)
        dst->तथ्य[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    अगर (err < 0)
        जाओ fail;

    dst->width  = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    क्रम (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    क्रम (i = 0; i < mapping->nb_objects; i++) {
        अगर (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    स_रखो(dst->तथ्य, 0, माप(dst->तथ्य));
    वापस err;
}

#पूर्ण_अगर

#अगर HAVE_OPENCL_VIDEOTOOLBOX

अटल व्योम opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

अटल पूर्णांक opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              स्थिर AVFrame *src, पूर्णांक flags)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref) src->तथ्य[3];
    IOSurfaceRef io_surface_ref = CVPixel_बफर_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = शून्य;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    अगर (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        वापस AVERROR_EXTERNAL;
    }

    desc = av_mallocz(माप(*desc));
    अगर (!desc)
        वापस AVERROR(ENOMEM);

    क्रम (पूर्णांक p = 0;; p++) {
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
        अगर (err == AVERROR(ENOENT))
            अवरोध;
        अगर (err < 0)
            जाओ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        अगर (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            जाओ fail;
        }
        desc->nb_planes++;
    }

    क्रम (पूर्णांक i = 0; i < desc->nb_planes; i++)
        dst->तथ्य[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    अगर (err < 0)
        जाओ fail;

    dst->width = src->width;
    dst->height = src->height;

    वापस 0;

fail:
    क्रम (पूर्णांक i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    वापस err;
}

#पूर्ण_अगर

अटल पूर्णांक opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           स्थिर AVFrame *src, पूर्णांक flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    अगर (hwfc->sw_format != dst->format)
        वापस AVERROR(ENOSYS);
    वापस opencl_map_frame(hwfc, dst, src, flags);
}

अटल पूर्णांक opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         स्थिर AVFrame *src, पूर्णांक flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    चयन (src->format) {
#अगर HAVE_OPENCL_DRM_BEIGNET
    हाल AV_PIX_FMT_DRM_अभाज्य:
        अगर (priv->beignet_drm_mapping_usable)
            वापस opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VAAPI_BEIGNET
    हाल AV_PIX_FMT_VAAPI:
        अगर (priv->beignet_drm_mapping_usable)
            वापस opencl_map_from_vaapi(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
    हाल AV_PIX_FMT_QSV:
    हाल AV_PIX_FMT_VAAPI:
        अगर (priv->qsv_mapping_usable)
            वापस opencl_map_from_qsv(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_DXVA2
    हाल AV_PIX_FMT_DXVA2_VLD:
        अगर (priv->dxva2_mapping_usable)
            वापस opencl_map_from_dxva2(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_D3D11
    हाल AV_PIX_FMT_D3D11:
        अगर (priv->d3d11_mapping_usable)
            वापस opencl_map_from_d3d11(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_DRM_ARM
    हाल AV_PIX_FMT_DRM_अभाज्य:
        अगर (priv->drm_arm_mapping_usable)
            वापस opencl_map_from_drm_arm(hwfc, dst, src, flags);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VIDEOTOOLBOX
    हाल AV_PIX_FMT_VIDEOTOOLBOX:
        वापस opencl_map_from_vt(hwfc, dst, src, flags);
#पूर्ण_अगर
    }
    वापस AVERROR(ENOSYS);
}

अटल पूर्णांक opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, पूर्णांक flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    चयन (src_fc->device_ctx->type) {
#अगर HAVE_OPENCL_DRM_BEIGNET
    हाल AV_HWDEVICE_TYPE_DRM:
        अगर (!priv->beignet_drm_mapping_usable)
            वापस AVERROR(ENOSYS);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VAAPI_BEIGNET
    हाल AV_HWDEVICE_TYPE_VAAPI:
        अगर (!priv->beignet_drm_mapping_usable)
            वापस AVERROR(ENOSYS);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VAAPI_INTEL_MEDIA
    हाल AV_HWDEVICE_TYPE_QSV:
    हाल AV_HWDEVICE_TYPE_VAAPI:
        अगर (!priv->qsv_mapping_usable)
            वापस AVERROR(ENOSYS);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        अगर (!priv->dxva2_mapping_usable)
            वापस AVERROR(ENOSYS);
        {
            पूर्णांक err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            अगर (err < 0)
                वापस err;
        }
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_D3D11
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        अगर (!priv->d3d11_mapping_usable)
            वापस AVERROR(ENOSYS);
        {
            पूर्णांक err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            अगर (err < 0)
                वापस err;
        }
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_DRM_ARM
    हाल AV_HWDEVICE_TYPE_DRM:
        अगर (!priv->drm_arm_mapping_usable)
            वापस AVERROR(ENOSYS);
        अवरोध;
#पूर्ण_अगर
#अगर HAVE_OPENCL_VIDEOTOOLBOX
    हाल AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        अवरोध;
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }
    वापस opencl_frames_init_command_queue(dst_fc);
}

स्थिर HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_आकार      = माप(OpenCLDeviceContext),
    .frames_hwctx_आकार      = माप(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .frames_get_constraints = &opencl_frames_get_constraints,
    .frames_init            = &opencl_frames_init,
    .frames_uninit          = &opencl_frames_uninit,
    .frames_get_बफर      = &opencl_get_बफर,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_तथ्य_to       = &opencl_transfer_तथ्य_to,
    .transfer_तथ्य_from     = &opencl_transfer_तथ्य_from,

    .map_from               = &opencl_map_from,
    .map_to                 = &opencl_map_to,
    .frames_derive_to       = &opencl_frames_derive_to,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
