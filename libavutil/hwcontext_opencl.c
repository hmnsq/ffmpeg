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
#endif

#اگر HAVE_OPENCL_DRM_BEIGNET
#شامل <unistd.h>
#شامل <CL/cl_intel.h>
#شامل "hwcontext_drm.h"
#endif

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
#اگر CONFIG_LIBMFX
#شامل <mfxstructures.h>
#endif
#شامل <va/va.h>
#شامل <CL/cl_va_api_media_sharing_intel.h>
#شامل "hwcontext_vaapi.h"
#endif

#اگر HAVE_OPENCL_DXVA2
#define COBJMACROS
#شامل <CL/cl_dx9_media_sharing.h>
#شامل <dxva2api.h>
#شامل "hwcontext_dxva2.h"
#endif

#اگر HAVE_OPENCL_D3D11
#شامل <CL/cl_d3d11.h>
#شامل "hwcontext_d3d11va.h"
#endif

#اگر HAVE_OPENCL_DRM_ARM
#شامل <CL/cl_ext.h>
#شامل <drm_fourcc.h>
#شامل "hwcontext_drm.h"
#endif

#اگر HAVE_OPENCL_VIDEOTOOLBOX
#شامل <OpenCL/cl_gl_ext.h>
#شامل <VideoToolbox/VideoToolbox.h>
#endif

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
بیرونی صحیح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          شمارش AVHWDeviceType base_dev_typ,
                                          تهی **base_handle);
#endif


تعریفنوع ساختار OpenCLDeviceContext {
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
#اگر HAVE_OPENCL_DRM_BEIGNET
    صحیح beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    صحیح qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#اگر HAVE_OPENCL_DXVA2
    صحیح dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#اگر HAVE_OPENCL_D3D11
    صحیح d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#اگر HAVE_OPENCL_DRM_ARM
    صحیح drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

تعریفنوع ساختار OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    صحیح                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


ایستا تهی CL_CALLBACK opencl_error_callback(ثابت نویسه *errinfo,
                                              ثابت تهی *private_info,
                                              size_t cb,
                                              تهی *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ایستا تهی opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ایستا ساختار {
    ثابت نویسه *کلید;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ایستا ساختار {
    ثابت نویسه *کلید;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ایستا ساختار {
    ثابت نویسه *کلید;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ایستا نویسه *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info کلید)
{
    نویسه *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, کلید, 0, پوچ, &size);
    اگر (cle != CL_SUCCESS)
        بازگشت پوچ;
    str = av_malloc(size);
    اگر (!str)
        بازگشت پوچ;
    cle = clGetPlatformInfo(platform_id, کلید, size, str, &size);
    اگر (cle != CL_SUCCESS) {
        av_free(str);
        بازگشت پوچ;
    }
    av_assert0(strlen(str) + 1 == size);
    بازگشت str;
}

ایستا نویسه *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info کلید)
{
    نویسه *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, کلید, 0, پوچ, &size);
    اگر (cle != CL_SUCCESS)
        بازگشت پوچ;
    str = av_malloc(size);
    اگر (!str)
        بازگشت پوچ;
    cle = clGetDeviceInfo(device_id, کلید, size, str, &size);
    اگر (cle != CL_SUCCESS) {
        av_free(str);
        بازگشت پوچ;
    }
    av_assert0(strlen(str) + 1== size);
    بازگشت str;
}

ایستا صحیح opencl_check_platform_extension(cl_platform_id platform_id,
                                           ثابت نویسه *name)
{
    نویسه *str;
    صحیح found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    اگر (str && strstr(str, name))
        found = 1;
    av_free(str);
    بازگشت found;
}

ایستا صحیح opencl_check_device_extension(cl_device_id device_id,
                                         ثابت نویسه *name)
{
    نویسه *str;
    صحیح found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    اگر (str && strstr(str, name))
        found = 1;
    av_free(str);
    بازگشت found;
}

av_unused ایستا صحیح opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ثابت نویسه *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    اگر (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        بازگشت 1;
    }

    اگر (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        بازگشت 1;
    }

    بازگشت 0;
}

ایستا صحیح opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      تهی *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, پوچ, nb_platforms);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        بازگشت AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, اندازه(**platforms));
    اگر (!*platforms)
        بازگشت AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        بازگشت AVERROR(ENODEV);
    }

    بازگشت 0;
}

ایستا صحیح opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ثابت نویسه *platform_name,
                                  تهی *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionaryEntry *param;
    نویسه *str;
    صحیح i, ret = 0;

    برای (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].کلید,
                            پوچ, 0);
        اگر (!param)
            ادامه;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        اگر (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].کلید, platform_name);
            بازگشت AVERROR_UNKNOWN;
        }
        اگر (!av_stristr(str, param->مقدار)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    بازگشت ret;
}

ایستا صحیح opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ثابت نویسه *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    تهی *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, پوچ, nb_devices);
    اگر (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        بازگشت 0;
    } وگرنه اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        بازگشت AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, اندازه(**devices));
    اگر (!*devices)
        بازگشت AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        بازگشت AVERROR(ENODEV);
    }

    بازگشت 0;
}

ایستا صحیح opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ثابت نویسه *device_name,
                                تهی *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionaryEntry *param;
    نویسه *str;
    صحیح i, ret = 0;

    param = av_dict_get(opts, "device_type", پوچ, 0);
    اگر (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        برای (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            اگر (!strcmp(opencl_device_types[i].کلید, param->مقدار)) {
                match_type = opencl_device_types[i].type;
                بشکن;
            }
        }
        اگر (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->مقدار);
            بازگشت AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              اندازه(device_type), &device_type, پوچ);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            بازگشت AVERROR_UNKNOWN;
        }

        اگر (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            بازگشت 1;
        }
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].کلید,
                            پوچ, 0);
        اگر (!param)
            ادامه;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        اگر (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].کلید, device_name);
            بازگشت AVERROR_UNKNOWN;
        }
        اگر (!av_stristr(str, param->مقدار)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کلید, str);
            ret = 1;
        }
        av_free(str);
    }

    بازگشت ret;
}

تعریفنوع ساختار OpenCLDeviceSelector {
    صحیح platform_index;
    صحیح device_index;
    تهی *context;
    صحیح (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               تهی *context);
    صحیح (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت نویسه *platform_name,
                               تهی *context);
    صحیح (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت نویسه *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               تهی *context);
    صحیح (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ثابت نویسه *device_name,
                               تهی *context);
} OpenCLDeviceSelector;

ایستا صحیح opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ثابت OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = پوچ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = پوچ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    نویسه *platform_name_src = پوچ,
         *device_name_src   = پوچ;
    صحیح err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    اگر (err)
        بازگشت err;

    found = 0;
    برای (p = 0; p < nb_platforms; p++) {
        ثابت نویسه *platform_name;

        اگر (selector->platform_index >= 0 &&
            selector->platform_index != p)
            ادامه;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        اگر (platform_name_src)
            platform_name = platform_name_src;
        وگرنه
            platform_name = "Unknown Platform";

        اگر (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            اگر (err < 0)
                برو fail;
            اگر (err > 0)
                ادامه;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        اگر (err < 0)
            ادامه;

        برای (d = 0; d < nb_devices; d++) {
            ثابت نویسه *device_name;

            اگر (selector->device_index >= 0 &&
                selector->device_index != d)
                ادامه;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            اگر (device_name_src)
                device_name = device_name_src;
            وگرنه
                device_name = "Unknown Device";

            اگر (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                اگر (err < 0)
                    برو fail;
                اگر (err > 0)
                    ادامه;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    اگر (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        برو fail;
    }
    اگر (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        برو fail;
    }

    اگر (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } وگرنه {
        اگر (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    اگر (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        برو fail;
    }

    hwdev->آزاد = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    بازگشت err;
}

ایستا صحیح opencl_device_create(AVHWDeviceContext *hwdev, ثابت نویسه *device,
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
            ret = sscanf(device, ".%d", &d);
        وگرنه
            ret = sscanf(device, "%d.%d", &p, &d);
        اگر (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            بازگشت AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } وگرنه {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    بازگشت opencl_device_create_internal(hwdev, &selector, پوچ);
}

ایستا صحیح opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    اگر (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            بازگشت AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } وگرنه {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        اگر (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            بازگشت AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          اندازه(priv->platform_id), &priv->platform_id,
                          پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        بازگشت AVERROR(EIO);
    }

#define CL_FUNC(name, desc) انجامبده {                                \
        اگر (fail)                                               \
            بشکن;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        اگر (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } وگرنه {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } وقتی (0)

#اگر HAVE_OPENCL_DRM_BEIGNET
    {
        صحیح fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } وگرنه {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = پوچ;
        VADisplay va_display;
        ثابت نویسه *va_ext = "cl_intel_va_api_media_sharing";
        صحیح i, fail = 0;

        اگر (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            برو no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, پوچ, &props_size);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            برو no_qsv;
        }
        اگر (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            برو no_qsv;
        }

        props = av_malloc(props_size);
        اگر (!props)
            بازگشت AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, پوچ);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            برو no_qsv;
        }

        va_display = پوچ;
        برای (i = 0; i < (props_size / اندازه(*props) - 1); i++) {
            اگر (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                بشکن;
            }
        }
        اگر (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            برو no_qsv;
        }
        اگر (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            برو no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        اگر (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } وگرنه {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#اگر HAVE_OPENCL_DXVA2
    {
        صحیح fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } وگرنه {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#اگر HAVE_OPENCL_D3D11
    {
        ثابت نویسه *d3d11_ext = "cl_khr_d3d11_sharing";
        ثابت نویسه *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        صحیح fail = 0;

        اگر (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } وگرنه اگر (!opencl_check_extension(hwdev, nv12_ext)) {
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

        اگر (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } وگرنه {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#اگر HAVE_OPENCL_DRM_ARM
    {
        ثابت نویسه *drm_arm_ext = "cl_arm_import_memory";
        ثابت نویسه *image_ext   = "cl_khr_image2d_from_buffer";
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
        } وگرنه {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    بازگشت 0;
}

ایستا تهی opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    اگر (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        اگر (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = پوچ;
    }
}

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
ایستا صحیح opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ثابت نویسه *platform_name,
                                                    تهی *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    اگر (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        بازگشت 1;
    } وگرنه {
        بازگشت 0;
    }
}

ایستا صحیح opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ثابت نویسه *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      تهی *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    اگر (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        بازگشت AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, پوچ, nb_devices);
    اگر (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        بازگشت 0;
    } وگرنه اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        بازگشت AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, اندازه(**devices));
    اگر (!*devices)
        بازگشت AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا صحیح opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ثابت نویسه *device_name,
                                                  تهی *context)
{
    ثابت نویسه *va_ext = "cl_intel_va_api_media_sharing";

    اگر (opencl_check_device_extension(device_id, va_ext)) {
        بازگشت 0;
    } وگرنه {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        بازگشت 1;
    }
}
#endif

#اگر HAVE_OPENCL_DXVA2
ایستا صحیح opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت نویسه *platform_name,
                                        تهی *context)
{
    ثابت نویسه *dx9_ext = "cl_khr_dx9_media_sharing";

    اگر (opencl_check_platform_extension(platform_id, dx9_ext)) {
        بازگشت 0;
    } وگرنه {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        بازگشت 1;
    }
}

ایستا صحیح opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت نویسه *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          تهی *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    اگر (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        بازگشت AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (تهی**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, پوچ, nb_devices);
    اگر (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        بازگشت 0;
    } وگرنه اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        بازگشت AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, اندازه(**devices));
    اگر (!*devices)
        بازگشت AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (تهی**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}
#endif

#اگر HAVE_OPENCL_D3D11
ایستا صحیح opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت نویسه *platform_name,
                                        تهی *context)
{
    ثابت نویسه *d3d11_ext = "cl_khr_d3d11_sharing";

    اگر (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        بازگشت 0;
    } وگرنه {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        بازگشت 1;
    }
}

ایستا صحیح opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت نویسه *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          تهی *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    اگر (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        بازگشت AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, پوچ, nb_devices);
    اگر (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        بازگشت 0;
    } وگرنه اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        بازگشت AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, اندازه(**devices));
    اگر (!*devices)
        بازگشت AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}
#endif

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ایستا صحیح opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ثابت نویسه *device_name,
                                    تهی *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          اندازه(device_type), &device_type, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        بازگشت AVERROR_UNKNOWN;
    }
    اگر (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        بازگشت 1;
    }

    بازگشت 0;
}
#endif

#اگر HAVE_OPENCL_DRM_ARM
ایستا صحیح opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت نویسه *platform_name,
                                          تهی *context)
{
    ثابت نویسه *drm_arm_ext = "cl_arm_import_memory";

    اگر (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        بازگشت 0;
    } وگرنه {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        بازگشت 1;
    }
}

ایستا صحیح opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ثابت نویسه *device_name,
                                        تهی *context)
{
    ثابت نویسه *drm_arm_ext = "cl_arm_import_memory";

    اگر (opencl_check_device_extension(device_id, drm_arm_ext)) {
        بازگشت 0;
    } وگرنه {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        بازگشت 1;
    }
}
#endif

ایستا صحیح opencl_device_derive(AVHWDeviceContext *hwdev,
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
            AVDictionary *selector_opts = پوچ;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            اگر (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            اگر (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = پوچ,
                };
                err = opencl_device_create_internal(hwdev, &selector, پوچ);
            }
            av_dict_free(&selector_opts);
        }
        بشکن;
#endif

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
        بشکن;
#endif

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
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                بشکن;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
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
            } وگرنه {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        بشکن;
#endif

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
        بشکن;
#endif

#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = پوچ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, پوچ);
        }
        بشکن;
#endif

#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, پوچ, پوچ, 0);
        بشکن;
#endif

    پیشفرض:
        err = AVERROR(ENOSYS);
        بشکن;
    }

    بازگشت err;
}

ایستا صحیح opencl_get_plane_format(شمارش AVPixelFormat pixfmt,
                                   صحیح plane, صحیح width, صحیح height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ثابت AVPixFmtDescriptor *desc;
    ثابت AVComponentDescriptor *comp;
    صحیح channels = 0, order = 0, depth = 0, step = 0;
    صحیح wsub, hsub, alpha;
    صحیح c;

    اگر (plane >= AV_رقم_DATA_POINTERS)
        بازگشت AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    اگر (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        بازگشت AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    اگر (width & wsub - 1 || height & hsub - 1)
        بازگشت AVERROR(EINVAL);

    برای (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        اگر (comp->plane != plane)
            ادامه;
        // The step size must be a power of two.
        اگر (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            بازگشت AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        اگر (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            بازگشت AVERROR(EINVAL);
        // The depth must not vary between components.
        اگر (depth && comp->depth != depth)
            بازگشت AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        اگر (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            بازگشت AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        اگر (step && comp->step != step)
            بازگشت AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    اگر (channels == 0)
        بازگشت AVERROR(ENOENT);

    memset(image_format, 0, اندازه(*image_format));
    memset(image_desc,   0, اندازه(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    اگر (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } وگرنه {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    اگر (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } وگرنه {
        اگر (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        وگرنه اگر (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        وگرنه
            بازگشت AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    حالت order: image_format->image_channel_order = type; بشکن;
    انتخاب (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    بازگشت 0;
}

ایستا صحیح opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ثابت تهی *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = پوچ;
    cl_int cle;
    شمارش AVPixelFormat pix_fmt;
    صحیح err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          اندازه(max_width), &max_width, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } وگرنه {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          اندازه(max_height), &max_height, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } وگرنه {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, پوچ, &nb_image_formats);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        برو fail;
    }
    اگر (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        برو fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, اندازه(*image_formats));
    اگر (!image_formats) {
        err = AVERROR(ENOMEM);
        برو fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, پوچ);
    اگر (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        برو fail;
    }

    pix_fmts_found = 0;
    برای (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        صحیح plane, i;

        برای (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            اگر (err < 0)
                بشکن;

            برای (i = 0; i < nb_image_formats; i++) {
                اگر (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    بشکن;
            }
            اگر (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                بشکن;
            }
        }
        اگر (err != AVERROR(ENOENT))
            ادامه;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                اندازه(*constraints->valid_sw_formats));
        اگر (err < 0)
            برو fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        برو fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;

fail:
    av_freep(&image_formats);
    بازگشت err;
}

ایستا تهی opencl_pool_free(تهی *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    صحیح p;

    برای (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ایستا AVBufferRef *opencl_pool_alloc(تهی *opaque, size_t size)
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

    desc = av_mallocz(اندازه(*desc));
    اگر (!desc)
        بازگشت پوچ;

    برای (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        اگر (err == AVERROR(ENOENT))
            بشکن;
        اگر (err < 0)
            برو fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, پوچ, &cle);
        اگر (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            برو fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, اندازه(*desc),
                           &opencl_pool_free, hwfc, 0);
    اگر (!ref)
        برو fail;

    بازگشت ref;

fail:
    برای (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    بازگشت پوچ;
}

ایستا صحیح opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    اگر (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        بازگشت AVERROR(EIO);
    }

    بازگشت 0;
}

ایستا صحیح opencl_frames_init(AVHWFramesContext *hwfc)
{
    اگر (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(اندازه(cl_mem), hwfc,
                                 &opencl_pool_alloc, پوچ);
        اگر (!ffhwframesctx(hwfc)->pool_internal)
            بازگشت AVERROR(ENOMEM);
    }

    بازگشت opencl_frames_init_command_queue(hwfc);
}

ایستا تهی opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#اگر HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    صحیح i, p;
    برای (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        برای (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            اگر (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    اگر (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = پوچ;
    }
}

ایستا صحیح opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    صحیح p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    برای (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    بازگشت 0;
}

ایستا صحیح opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       شمارش AVHWFrameTransferDirection dir,
                                       شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *fmts;

    fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    بازگشت 0;
}

ایستا صحیح opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, صحیح nb_events)
{
    cl_int cle;
    صحیح i;

    cle = clWaitForEvents(nb_events, events);
    اگر (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        بازگشت AVERROR(EIO);
    }

    برای (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    بازگشت 0;
}

ایستا صحیح opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_رقم_DATA_POINTERS];
    صحیح err, p;

    اگر (dst->format != hwfc->sw_format)
        بازگشت AVERROR(EINVAL);

    برای (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        اگر (err < 0) {
            اگر (err == AVERROR(ENOENT))
                err = 0;
            بشکن;
        }

        اگر (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            بشکن;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, پوچ, &events[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            بشکن;
        }
    }

    opencl_wait_events(hwfc, events, p);

    بازگشت err;
}

ایستا صحیح opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_رقم_DATA_POINTERS];
    صحیح err, p;

    اگر (src->format != hwfc->sw_format)
        بازگشت AVERROR(EINVAL);

    برای (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        اگر (err < 0) {
            اگر (err == AVERROR(ENOENT))
                err = 0;
            بشکن;
        }

        اگر (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            بشکن;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, پوچ, &events[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            بشکن;
        }
    }

    opencl_wait_events(hwfc, events, p);

    بازگشت err;
}

تعریفنوع ساختار OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    تهی *address[AV_رقم_DATA_POINTERS];
} OpenCLMapping;

ایستا تهی opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_رقم_DATA_POINTERS];
    صحیح p, e;
    cl_int cle;

    برای (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        اگر (!map->address[p])
            بشکن;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, پوچ, &events[e]);
        اگر (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ایستا صحیح opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
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
    size_t row_pitch;
    cl_event events[AV_رقم_DATA_POINTERS];
    صحیح err, p;

    av_assert0(hwfc->sw_format == dst->format);

    اگر (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } وگرنه {
        map_flags = 0;
        اگر (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        اگر (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(اندازه(*map));
    اگر (!map)
        بازگشت AVERROR(ENOMEM);

    برای (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        اگر (err == AVERROR(ENOENT))
            بشکن;
        اگر (err < 0)
            برو fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, پوچ, 0, پوچ,
                              &events[p], &cle);
        اگر (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            برو fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    اگر (err < 0)
        برو fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    برای (p = 0; p < AV_رقم_DATA_POINTERS; p++) {
        اگر (!map->address[p])
            بشکن;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, پوچ, &events[p]);
    }
    اگر (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    بازگشت err;
}

#اگر HAVE_OPENCL_DRM_BEIGNET

تعریفنوع ساختار DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

ایستا تهی opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    صحیح i;

    برای (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        اگر (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ایستا صحیح opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ثابت AVFrame *src,
                                       صحیح flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ثابت AVDRMFrameDescriptor *desc;
    cl_int cle;
    صحیح err, i, j, p;

    desc = (ثابت AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(اندازه(*mapping));
    اگر (!mapping)
        بازگشت AVERROR(ENOMEM);

    p = 0;
    برای (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        برای (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ثابت AVDRMObjectDescriptor *object =
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
            اگر (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                برو fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            اگر (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                برو fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    برای (p = 0; p < mapping->frame.nb_planes; p++) {
        اگر (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, اندازه(dst->data));
    بازگشت err;
}

#اگر HAVE_OPENCL_VAAPI_BEIGNET

ایستا صحیح opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ثابت AVFrame *src,
                                 صحیح flags)
{
    AVFrame *tmp;
    صحیح err;

    tmp = av_frame_alloc();
    اگر (!tmp)
        بازگشت AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_اول;

    err = av_hwframe_map(tmp, src, flags);
    اگر (err < 0)
        برو fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    اگر (err < 0)
        برو fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    بازگشت err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

ایستا درونخطی cl_mem_flags opencl_mem_flags_for_mapping(صحیح map_flags)
{
    اگر ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        بازگشت CL_MEM_READ_WRITE;
    وگرنه اگر (map_flags & AV_HWFRAME_MAP_READ)
        بازگشت CL_MEM_READ_ONLY;
    وگرنه اگر (map_flags & AV_HWFRAME_MAP_WRITE)
        بازگشت CL_MEM_WRITE_ONLY;
    وگرنه
        بازگشت 0;
}

#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA

ایستا تهی opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    صحیح p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    برای (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        اگر (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ایستا صحیح opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ثابت AVFrame *src, صحیح flags)
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
    صحیح err, p;

#اگر CONFIG_LIBMFX
    اگر (src->format == AV_PIX_FMT_QSV) {
        تهی *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        اگر (err < 0)
            بازگشت err;
        va_surface = *(VASurfaceID *)base_handle;
    } وگرنه
#endif
        اگر (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } وگرنه {
        بازگشت AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        بازگشت AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(اندازه(*desc));
    اگر (!desc)
        بازگشت AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    برای (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        اگر (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            برو fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        برو fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        برو fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    برای (p = 0; p < desc->nb_planes; p++)
        اگر (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, اندازه(dst->data));
    بازگشت err;
}

#endif

#اگر HAVE_OPENCL_DXVA2

ایستا تهی opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        بازگشت;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ایستا صحیح opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحیح err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
        اگر (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            بشکن;
    }
    اگر (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        بازگشت AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        بازگشت AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        برو fail;

    برای (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, اندازه(dst->data));
    بازگشت err;
}

ایستا صحیح opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحیح flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحیح err, i, p, nb_planes;

    اگر (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        بازگشت AVERROR(EINVAL);
    }
    nb_planes = 2;

    اگر (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        بازگشت AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        بازگشت AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  اندازه(*frames_priv->mapped_frames));
    اگر (!frames_priv->mapped_frames)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = پوچ,
        };
        desc->nb_planes = nb_planes;
        برای (p = 0; p < nb_planes; p++) {
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
                برو fail;
            }
        }
    }

    بازگشت 0;

fail:
    برای (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        برای (p = 0; p < desc->nb_planes; p++) {
            اگر (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    بازگشت err;
}

#endif

#اگر HAVE_OPENCL_D3D11

ایستا تهی opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ایستا صحیح opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحیح flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحیح err, index, i;

    index = (intptr_t)src->data[1];
    اگر (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        بازگشت AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        بازگشت AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    اگر (err < 0)
        برو fail;

    برای (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, پوچ, &event);
    اگر (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, اندازه(dst->data));
    بازگشت err;
}

ایستا صحیح opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحیح flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحیح err, i, p, nb_planes;

    اگر (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        بازگشت AVERROR(EINVAL);
    }
    nb_planes = 2;

    اگر (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        بازگشت AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        بازگشت AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  اندازه(*frames_priv->mapped_frames));
    اگر (!frames_priv->mapped_frames)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        برای (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            اگر (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned صحیح)subresource, cle);
                err = AVERROR(EIO);
                برو fail;
            }
        }
    }

    بازگشت 0;

fail:
    برای (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        برای (p = 0; p < desc->nb_planes; p++) {
            اگر (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    بازگشت err;
}

#endif

#اگر HAVE_OPENCL_DRM_ARM

تعریفنوع ساختار DRMARMtoOpenCLMapping {
    صحیح nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    صحیح nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ایستا تهی opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    صحیح i;

    برای (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    برای (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ایستا صحیح opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = پوچ;
    cl_mem_flags cl_flags;
    ثابت cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    صحیح err, i, j;

    desc = (ثابت AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    اگر (!cl_flags)
        بازگشت AVERROR(EINVAL);

    mapping = av_mallocz(اندازه(*mapping));
    اگر (!mapping)
        بازگشت AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    برای (i = 0; i < desc->nb_objects; i++) {
        صحیح fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        اگر (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        اگر (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            برو fail;
        }
    }

    mapping->nb_planes = 0;
    برای (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];

        برای (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            صحیح p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            اگر (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                برو fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            اگر (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                برو fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, پوچ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            اگر (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                برو fail;
            }

            ++mapping->nb_planes;
        }
    }

    برای (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    اگر (err < 0)
        برو fail;

    dst->width  = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    برای (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    برای (i = 0; i < mapping->nb_objects; i++) {
        اگر (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, اندازه(dst->data));
    بازگشت err;
}

#endif

#اگر HAVE_OPENCL_VIDEOTOOLBOX

ایستا تهی opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ایستا صحیح opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحیح flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = پوچ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    اگر (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        بازگشت AVERROR_EXTERNAL;
    }

    desc = av_mallocz(اندازه(*desc));
    اگر (!desc)
        بازگشت AVERROR(ENOMEM);

    برای (صحیح p = 0;; p++) {
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
        اگر (err == AVERROR(ENOENT))
            بشکن;
        اگر (err < 0)
            برو fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        اگر (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            برو fail;
        }
        desc->nb_planes++;
    }

    برای (صحیح i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    اگر (err < 0)
        برو fail;

    dst->width = src->width;
    dst->height = src->height;

    بازگشت 0;

fail:
    برای (صحیح i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    بازگشت err;
}

#endif

ایستا صحیح opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ثابت AVFrame *src, صحیح flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    اگر (hwfc->sw_format != dst->format)
        بازگشت AVERROR(ENOSYS);
    بازگشت opencl_map_frame(hwfc, dst, src, flags);
}

ایستا صحیح opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ثابت AVFrame *src, صحیح flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    انتخاب (src->format) {
#اگر HAVE_OPENCL_DRM_BEIGNET
    حالت AV_PIX_FMT_DRM_اول:
        اگر (priv->beignet_drm_mapping_usable)
            بازگشت opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_VAAPI_BEIGNET
    حالت AV_PIX_FMT_VAAPI:
        اگر (priv->beignet_drm_mapping_usable)
            بازگشت opencl_map_from_vaapi(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالت AV_PIX_FMT_QSV:
    حالت AV_PIX_FMT_VAAPI:
        اگر (priv->qsv_mapping_usable)
            بازگشت opencl_map_from_qsv(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_DXVA2
    حالت AV_PIX_FMT_DXVA2_VLD:
        اگر (priv->dxva2_mapping_usable)
            بازگشت opencl_map_from_dxva2(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_D3D11
    حالت AV_PIX_FMT_D3D11:
        اگر (priv->d3d11_mapping_usable)
            بازگشت opencl_map_from_d3d11(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_PIX_FMT_DRM_اول:
        اگر (priv->drm_arm_mapping_usable)
            بازگشت opencl_map_from_drm_arm(hwfc, dst, src, flags);
        بشکن;
#endif
#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_PIX_FMT_VIDEOTOOLBOX:
        بازگشت opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    بازگشت AVERROR(ENOSYS);
}

ایستا صحیح opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, صحیح flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    انتخاب (src_fc->device_ctx->type) {
#اگر HAVE_OPENCL_DRM_BEIGNET
    حالت AV_HWDEVICE_TYPE_DRM:
        اگر (!priv->beignet_drm_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        بشکن;
#endif
#اگر HAVE_OPENCL_VAAPI_BEIGNET
    حالت AV_HWDEVICE_TYPE_VAAPI:
        اگر (!priv->beignet_drm_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        بشکن;
#endif
#اگر HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالت AV_HWDEVICE_TYPE_QSV:
    حالت AV_HWDEVICE_TYPE_VAAPI:
        اگر (!priv->qsv_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        بشکن;
#endif
#اگر HAVE_OPENCL_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        اگر (!priv->dxva2_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        {
            صحیح err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            اگر (err < 0)
                بازگشت err;
        }
        بشکن;
#endif
#اگر HAVE_OPENCL_D3D11
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        اگر (!priv->d3d11_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        {
            صحیح err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            اگر (err < 0)
                بازگشت err;
        }
        بشکن;
#endif
#اگر HAVE_OPENCL_DRM_ARM
    حالت AV_HWDEVICE_TYPE_DRM:
        اگر (!priv->drm_arm_mapping_usable)
            بازگشت AVERROR(ENOSYS);
        بشکن;
#endif
#اگر HAVE_OPENCL_VIDEOTOOLBOX
    حالت AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        بشکن;
#endif
    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }
    بازگشت opencl_frames_init_command_queue(dst_fc);
}

ثابت HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = اندازه(OpenCLDeviceContext),
    .frames_hwctx_size      = اندازه(OpenCLFramesContext),

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

    .pix_fmts = (ثابت شمارش AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
