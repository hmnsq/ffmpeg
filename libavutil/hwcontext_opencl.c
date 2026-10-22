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

#ضمن <string.h>

#ضمن "config.h"

#ضمن "avassert.h"
#ضمن "avstring.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_opencl.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"

#إذا HAVE_OPENCL_VAAPI_BEIGNET
#ضمن <unistd.h>
#ضمن <va/va.h>
#ضمن <va/va_drmcommon.h>
#ضمن <CL/cl_intel.h>
#ضمن "hwcontext_vaapi.h"
#endif

#إذا HAVE_OPENCL_DRM_BEIGNET
#ضمن <unistd.h>
#ضمن <CL/cl_intel.h>
#ضمن "hwcontext_drm.h"
#endif

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
#إذا CONFIG_LIBMFX
#ضمن <mfxstructures.h>
#endif
#ضمن <va/va.h>
#ضمن <CL/cl_va_api_media_sharing_intel.h>
#ضمن "hwcontext_vaapi.h"
#endif

#إذا HAVE_OPENCL_DXVA2
#define COBJMACROS
#ضمن <CL/cl_dx9_media_sharing.h>
#ضمن <dxva2api.h>
#ضمن "hwcontext_dxva2.h"
#endif

#إذا HAVE_OPENCL_D3D11
#ضمن <CL/cl_d3d11.h>
#ضمن "hwcontext_d3d11va.h"
#endif

#إذا HAVE_OPENCL_DRM_ARM
#ضمن <CL/cl_ext.h>
#ضمن <drm_fourcc.h>
#ضمن "hwcontext_drm.h"
#endif

#إذا HAVE_OPENCL_VIDEOTOOLBOX
#ضمن <OpenCL/cl_gl_ext.h>
#ضمن <VideoToolbox/VideoToolbox.h>
#endif

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
خارجي صحيح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          تعداد AVHWDeviceType base_dev_typ,
                                          فراغ **base_handle);
#endif


تعريفنوع بنية OpenCLDeviceContext {
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
#إذا HAVE_OPENCL_DRM_BEIGNET
    صحيح beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    صحيح qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#إذا HAVE_OPENCL_DXVA2
    صحيح dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#إذا HAVE_OPENCL_D3D11
    صحيح d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#إذا HAVE_OPENCL_DRM_ARM
    صحيح drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

تعريفنوع بنية OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    صحيح                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


ساكن فراغ CL_CALLBACK opencl_error_callback(ثابت حرف *errinfo,
                                              ثابت فراغ *private_info,
                                              size_t cb,
                                              فراغ *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

ساكن فراغ opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

ساكن بنية {
    ثابت حرف *کونچي;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

ساكن بنية {
    ثابت حرف *کونچي;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

ساكن بنية {
    ثابت حرف *کونچي;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

ساكن حرف *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info کونچي)
{
    حرف *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, کونچي, 0, عدم, &size);
    إذا (cle != CL_SUCCESS)
        أرجع عدم;
    str = av_malloc(size);
    إذا (!str)
        أرجع عدم;
    cle = clGetPlatformInfo(platform_id, کونچي, size, str, &size);
    إذا (cle != CL_SUCCESS) {
        av_free(str);
        أرجع عدم;
    }
    av_assert0(strlen(str) + 1 == size);
    أرجع str;
}

ساكن حرف *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info کونچي)
{
    حرف *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, کونچي, 0, عدم, &size);
    إذا (cle != CL_SUCCESS)
        أرجع عدم;
    str = av_malloc(size);
    إذا (!str)
        أرجع عدم;
    cle = clGetDeviceInfo(device_id, کونچي, size, str, &size);
    إذا (cle != CL_SUCCESS) {
        av_free(str);
        أرجع عدم;
    }
    av_assert0(strlen(str) + 1== size);
    أرجع str;
}

ساكن صحيح opencl_check_platform_extension(cl_platform_id platform_id,
                                           ثابت حرف *name)
{
    حرف *str;
    صحيح found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    إذا (str && strstr(str, name))
        found = 1;
    av_free(str);
    أرجع found;
}

ساكن صحيح opencl_check_device_extension(cl_device_id device_id,
                                         ثابت حرف *name)
{
    حرف *str;
    صحيح found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    إذا (str && strstr(str, name))
        found = 1;
    av_free(str);
    أرجع found;
}

av_unused ساكن صحيح opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ثابت حرف *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    إذا (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        أرجع 1;
    }

    إذا (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        أرجع 1;
    }

    أرجع 0;
}

ساكن صحيح opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      فراغ *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, عدم, nb_platforms);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        أرجع AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, حجم(**platforms));
    إذا (!*platforms)
        أرجع AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        أرجع AVERROR(ENODEV);
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ثابت حرف *platform_name,
                                  فراغ *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionaryEntry *param;
    حرف *str;
    صحيح i, ret = 0;

    لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].کونچي,
                            عدم, 0);
        إذا (!param)
            استمر;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        إذا (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].کونچي, platform_name);
            أرجع AVERROR_UNKNOWN;
        }
        إذا (!av_stristr(str, param->نيلاي)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کونچي, str);
            ret = 1;
        }
        av_free(str);
    }

    أرجع ret;
}

ساكن صحيح opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ثابت حرف *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    فراغ *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR(ENODEV);
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ثابت حرف *device_name,
                                فراغ *context)
{
    AVDictionary *opts = context;
    ثابت AVDictionaryEntry *param;
    حرف *str;
    صحيح i, ret = 0;

    param = av_dict_get(opts, "device_type", عدم, 0);
    إذا (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            إذا (!strcmp(opencl_device_types[i].کونچي, param->نيلاي)) {
                match_type = opencl_device_types[i].type;
                اكسر;
            }
        }
        إذا (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->نيلاي);
            أرجع AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              حجم(device_type), &device_type, عدم);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            أرجع AVERROR_UNKNOWN;
        }

        إذا (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            أرجع 1;
        }
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].کونچي,
                            عدم, 0);
        إذا (!param)
            استمر;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        إذا (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].کونچي, device_name);
            أرجع AVERROR_UNKNOWN;
        }
        إذا (!av_stristr(str, param->نيلاي)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->کونچي, str);
            ret = 1;
        }
        av_free(str);
    }

    أرجع ret;
}

تعريفنوع بنية OpenCLDeviceSelector {
    صحيح platform_index;
    صحيح device_index;
    فراغ *context;
    صحيح (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               فراغ *context);
    صحيح (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               فراغ *context);
    صحيح (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ثابت حرف *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               فراغ *context);
    صحيح (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ثابت حرف *device_name,
                               فراغ *context);
} OpenCLDeviceSelector;

ساكن صحيح opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ثابت OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = عدم;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = عدم;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    حرف *platform_name_src = عدم,
         *device_name_src   = عدم;
    صحيح err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    إذا (err)
        أرجع err;

    found = 0;
    لكل (p = 0; p < nb_platforms; p++) {
        ثابت حرف *platform_name;

        إذا (selector->platform_index >= 0 &&
            selector->platform_index != p)
            استمر;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        إذا (platform_name_src)
            platform_name = platform_name_src;
        وإلا
            platform_name = "Unknown Platform";

        إذا (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            إذا (err < 0)
                اذهب fail;
            إذا (err > 0)
                استمر;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        إذا (err < 0)
            استمر;

        لكل (d = 0; d < nb_devices; d++) {
            ثابت حرف *device_name;

            إذا (selector->device_index >= 0 &&
                selector->device_index != d)
                استمر;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            إذا (device_name_src)
                device_name = device_name_src;
            وإلا
                device_name = "Unknown Device";

            إذا (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                إذا (err < 0)
                    اذهب fail;
                إذا (err > 0)
                    استمر;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    إذا (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        اذهب fail;
    }
    إذا (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        اذهب fail;
    }

    إذا (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } وإلا {
        إذا (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    إذا (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        اذهب fail;
    }

    hwdev->حرر = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    أرجع err;
}

ساكن صحيح opencl_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                                AVDictionary *opts, صحيح flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    إذا (device && device[0]) {
        // Match one or both indices for platform and device.
        صحيح d = -1, p = -1, ret;
        إذا (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        وإلا
            ret = sscanf(device, "%d.%d", &p, &d);
        إذا (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            أرجع AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } وإلا {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    أرجع opencl_device_create_internal(hwdev, &selector, عدم);
}

ساكن صحيح opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    إذا (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            أرجع AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } وإلا {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        إذا (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            أرجع AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          حجم(priv->platform_id), &priv->platform_id,
                          عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        أرجع AVERROR(EIO);
    }

#define CL_FUNC(name, desc) افعل {                                \
        إذا (fail)                                               \
            اكسر;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        إذا (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } وإلا {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } طالما (0)

#إذا HAVE_OPENCL_DRM_BEIGNET
    {
        صحيح fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } وإلا {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = عدم;
        VADisplay va_display;
        ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";
        صحيح i, fail = 0;

        إذا (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            اذهب no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, عدم, &props_size);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            اذهب no_qsv;
        }
        إذا (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }

        props = av_malloc(props_size);
        إذا (!props)
            أرجع AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, عدم);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            اذهب no_qsv;
        }

        va_display = عدم;
        لكل (i = 0; i < (props_size / حجم(*props) - 1); i++) {
            إذا (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                اكسر;
            }
        }
        إذا (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }
        إذا (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            اذهب no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        إذا (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } وإلا {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#إذا HAVE_OPENCL_DXVA2
    {
        صحيح fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } وإلا {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#إذا HAVE_OPENCL_D3D11
    {
        ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";
        ثابت حرف *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        صحيح fail = 0;

        إذا (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } وإلا إذا (!opencl_check_extension(hwdev, nv12_ext)) {
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

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } وإلا {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#إذا HAVE_OPENCL_DRM_ARM
    {
        ثابت حرف *drm_arm_ext = "cl_arm_import_memory";
        ثابت حرف *image_ext   = "cl_khr_image2d_from_buffer";
        صحيح fail = 0;

        إذا (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        إذا (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        إذا (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } وإلا {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    أرجع 0;
}

ساكن فراغ opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    إذا (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        إذا (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = عدم;
    }
}

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
ساكن صحيح opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ثابت حرف *platform_name,
                                                    فراغ *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    إذا (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        أرجع 1;
    } وإلا {
        أرجع 0;
    }
}

ساكن صحيح opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ثابت حرف *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      فراغ *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    إذا (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن صحيح opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ثابت حرف *device_name,
                                                  فراغ *context)
{
    ثابت حرف *va_ext = "cl_intel_va_api_media_sharing";

    إذا (opencl_check_device_extension(device_id, va_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        أرجع 1;
    }
}
#endif

#إذا HAVE_OPENCL_DXVA2
ساكن صحيح opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        فراغ *context)
{
    ثابت حرف *dx9_ext = "cl_khr_dx9_media_sharing";

    إذا (opencl_check_platform_extension(platform_id, dx9_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          فراغ *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    إذا (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (فراغ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (فراغ**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}
#endif

#إذا HAVE_OPENCL_D3D11
ساكن صحيح opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ثابت حرف *platform_name,
                                        فراغ *context)
{
    ثابت حرف *d3d11_ext = "cl_khr_d3d11_sharing";

    إذا (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          فراغ *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    إذا (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        أرجع AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, عدم, nb_devices);
    إذا (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        أرجع 0;
    } وإلا إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        أرجع AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, حجم(**devices));
    إذا (!*devices)
        أرجع AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}
#endif

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
ساكن صحيح opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ثابت حرف *device_name,
                                    فراغ *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          حجم(device_type), &device_type, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        أرجع AVERROR_UNKNOWN;
    }
    إذا (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        أرجع 1;
    }

    أرجع 0;
}
#endif

#إذا HAVE_OPENCL_DRM_ARM
ساكن صحيح opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ثابت حرف *platform_name,
                                          فراغ *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    إذا (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        أرجع 1;
    }
}

ساكن صحيح opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ثابت حرف *device_name,
                                        فراغ *context)
{
    ثابت حرف *drm_arm_ext = "cl_arm_import_memory";

    إذا (opencl_check_device_extension(device_id, drm_arm_ext)) {
        أرجع 0;
    } وإلا {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        أرجع 1;
    }
}
#endif

ساكن صحيح opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                صحيح flags)
{
    صحيح err;
    بدل (src_ctx->type) {

#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_HWDEVICE_TYPE_DRM:
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = عدم;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            إذا (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            إذا (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = عدم,
                };
                err = opencl_device_create_internal(hwdev, &selector, عدم);
            }
            av_dict_free(&selector_opts);
        }
        اكسر;
#endif

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    حالة AV_HWDEVICE_TYPE_VAAPI:
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
        اكسر;
#endif

#إذا HAVE_OPENCL_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            إذا (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                اكسر;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            إذا (SUCCEEDED(hr)) {
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
            } وإلا {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        اكسر;
#endif

#إذا HAVE_OPENCL_D3D11
    حالة AV_HWDEVICE_TYPE_D3D11VA:
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
        اكسر;
#endif

#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = عدم,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, عدم);
        }
        اكسر;
#endif

#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, عدم, عدم, 0);
        اكسر;
#endif

    افتراضي:
        err = AVERROR(ENOSYS);
        اكسر;
    }

    أرجع err;
}

ساكن صحيح opencl_get_plane_format(تعداد AVPixelFormat pixfmt,
                                   صحيح plane, صحيح width, صحيح height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ثابت AVPixFmtDescriptor *desc;
    ثابت AVComponentDescriptor *comp;
    صحيح channels = 0, order = 0, depth = 0, step = 0;
    صحيح wsub, hsub, alpha;
    صحيح c;

    إذا (plane >= AV_اڠک_DATA_POINTERS)
        أرجع AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        أرجع AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    إذا (width & wsub - 1 || height & hsub - 1)
        أرجع AVERROR(EINVAL);

    لكل (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        إذا (comp->plane != plane)
            استمر;
        // The step size must be a power of two.
        إذا (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            أرجع AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        إذا (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            أرجع AVERROR(EINVAL);
        // The depth must not vary between components.
        إذا (depth && comp->depth != depth)
            أرجع AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        إذا (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            أرجع AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        إذا (step && comp->step != step)
            أرجع AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    إذا (channels == 0)
        أرجع AVERROR(ENOENT);

    memset(image_format, 0, حجم(*image_format));
    memset(image_desc,   0, حجم(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    إذا (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } وإلا {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    إذا (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } وإلا {
        إذا (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        وإلا إذا (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        وإلا
            أرجع AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    حالة order: image_format->image_channel_order = type; اكسر;
    بدل (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    أرجع 0;
}

ساكن صحيح opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ثابت فراغ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = عدم;
    cl_int cle;
    تعداد AVPixelFormat pix_fmt;
    صحيح err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          حجم(max_width), &max_width, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } وإلا {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          حجم(max_height), &max_height, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } وإلا {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, عدم, &nb_image_formats);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        اذهب fail;
    }
    إذا (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        اذهب fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, حجم(*image_formats));
    إذا (!image_formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, عدم);
    إذا (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        اذهب fail;
    }

    pix_fmts_found = 0;
    لكل (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        صحيح plane, i;

        لكل (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            إذا (err < 0)
                اكسر;

            لكل (i = 0; i < nb_image_formats; i++) {
                إذا (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    اكسر;
            }
            إذا (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                اكسر;
            }
        }
        إذا (err != AVERROR(ENOENT))
            استمر;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                حجم(*constraints->valid_sw_formats));
        إذا (err < 0)
            اذهب fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;

fail:
    av_freep(&image_formats);
    أرجع err;
}

ساكن فراغ opencl_pool_free(فراغ *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    صحيح p;

    لكل (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

ساكن AVBufferRef *opencl_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    صحيح err, p;
    AVBufferRef *ref;

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع عدم;

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, عدم, &cle);
        إذا (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            اذهب fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, حجم(*desc),
                           &opencl_pool_free, hwfc, 0);
    إذا (!ref)
        اذهب fail;

    أرجع ref;

fail:
    لكل (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    أرجع عدم;
}

ساكن صحيح opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    إذا (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    أرجع 0;
}

ساكن صحيح opencl_frames_init(AVHWFramesContext *hwfc)
{
    إذا (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(حجم(cl_mem), hwfc,
                                 &opencl_pool_alloc, عدم);
        إذا (!ffhwframesctx(hwfc)->pool_internal)
            أرجع AVERROR(ENOMEM);
    }

    أرجع opencl_frames_init_command_queue(hwfc);
}

ساكن فراغ opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#إذا HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    صحيح i, p;
    لكل (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            إذا (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    إذا (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = عدم;
    }
}

ساكن صحيح opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    صحيح p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    إذا (!frame->buf[0])
        أرجع AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    لكل (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    أرجع 0;
}

ساكن صحيح opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       تعداد AVHWFrameTransferDirection dir,
                                       تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    أرجع 0;
}

ساكن صحيح opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, صحيح nb_events)
{
    cl_int cle;
    صحيح i;

    cle = clWaitForEvents(nb_events, events);
    إذا (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    لكل (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    أرجع 0;
}

ساكن صحيح opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_اڠک_DATA_POINTERS];
    صحيح err, p;

    إذا (dst->format != hwfc->sw_format)
        أرجع AVERROR(EINVAL);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        إذا (err < 0) {
            إذا (err == AVERROR(ENOENT))
                err = 0;
            اكسر;
        }

        إذا (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            اكسر;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, عدم, &events[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اكسر;
        }
    }

    opencl_wait_events(hwfc, events, p);

    أرجع err;
}

ساكن صحيح opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ثابت AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_اڠک_DATA_POINTERS];
    صحيح err, p;

    إذا (src->format != hwfc->sw_format)
        أرجع AVERROR(EINVAL);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        إذا (err < 0) {
            إذا (err == AVERROR(ENOENT))
                err = 0;
            اكسر;
        }

        إذا (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            اكسر;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, عدم, &events[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اكسر;
        }
    }

    opencl_wait_events(hwfc, events, p);

    أرجع err;
}

تعريفنوع بنية OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    فراغ *address[AV_اڠک_DATA_POINTERS];
} OpenCLMapping;

ساكن فراغ opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_اڠک_DATA_POINTERS];
    صحيح p, e;
    cl_int cle;

    لكل (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        إذا (!map->address[p])
            اكسر;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, عدم, &events[e]);
        إذا (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

ساكن صحيح opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ثابت AVFrame *src, صحيح flags)
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
    cl_event events[AV_اڠک_DATA_POINTERS];
    صحيح err, p;

    av_assert0(hwfc->sw_format == dst->format);

    إذا (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } وإلا {
        map_flags = 0;
        إذا (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        إذا (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(حجم(*map));
    إذا (!map)
        أرجع AVERROR(ENOMEM);

    لكل (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, عدم, 0, عدم,
                              &events[p], &cle);
        إذا (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    لكل (p = 0; p < AV_اڠک_DATA_POINTERS; p++) {
        إذا (!map->address[p])
            اكسر;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, عدم, &events[p]);
    }
    إذا (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    أرجع err;
}

#إذا HAVE_OPENCL_DRM_BEIGNET

تعريفنوع بنية DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

ساكن فراغ opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    صحيح i;

    لكل (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        إذا (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

ساكن صحيح opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ثابت AVFrame *src,
                                       صحيح flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ثابت AVDRMFrameDescriptor *desc;
    cl_int cle;
    صحيح err, i, j, p;

    desc = (ثابت AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(حجم(*mapping));
    إذا (!mapping)
        أرجع AVERROR(ENOMEM);

    p = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];
        لكل (j = 0; j < layer->nb_planes; j++) {
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
            إذا (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                اذهب fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            إذا (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    لكل (p = 0; p < mapping->frame.nb_planes; p++) {
        إذا (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, حجم(dst->data));
    أرجع err;
}

#إذا HAVE_OPENCL_VAAPI_BEIGNET

ساكن صحيح opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ثابت AVFrame *src,
                                 صحيح flags)
{
    AVFrame *tmp;
    صحيح err;

    tmp = av_frame_alloc();
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ڤردان;

    err = av_hwframe_map(tmp, src, flags);
    إذا (err < 0)
        اذهب fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    أرجع err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

ساكن مضمن cl_mem_flags opencl_mem_flags_for_mapping(صحيح map_flags)
{
    إذا ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        أرجع CL_MEM_READ_WRITE;
    وإلا إذا (map_flags & AV_HWFRAME_MAP_READ)
        أرجع CL_MEM_READ_ONLY;
    وإلا إذا (map_flags & AV_HWFRAME_MAP_WRITE)
        أرجع CL_MEM_WRITE_ONLY;
    وإلا
        أرجع 0;
}

#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA

ساكن فراغ opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    صحيح p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    لكل (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        إذا (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

ساكن صحيح opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags)
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
    صحيح err, p;

#إذا CONFIG_LIBMFX
    إذا (src->format == AV_PIX_FMT_QSV) {
        فراغ *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        إذا (err < 0)
            أرجع err;
        va_surface = *(VASurfaceID *)base_handle;
    } وإلا
#endif
        إذا (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } وإلا {
        أرجع AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    لكل (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        إذا (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        اذهب fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    لكل (p = 0; p < desc->nb_planes; p++)
        إذا (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, حجم(dst->data));
    أرجع err;
}

#endif

#إذا HAVE_OPENCL_DXVA2

ساكن فراغ opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        أرجع;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساكن صحيح opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحيح err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
        إذا (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            اكسر;
    }
    إذا (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        أرجع AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    لكل (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, حجم(dst->data));
    أرجع err;
}

ساكن صحيح opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحيح flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحيح err, i, p, nb_planes;

    إذا (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }
    nb_planes = 2;

    إذا (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  حجم(*frames_priv->mapped_frames));
    إذا (!frames_priv->mapped_frames)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = عدم,
        };
        desc->nb_planes = nb_planes;
        لكل (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            إذا (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }
        }
    }

    أرجع 0;

fail:
    لكل (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            إذا (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    أرجع err;
}

#endif

#إذا HAVE_OPENCL_D3D11

ساكن فراغ opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

ساكن صحيح opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ثابت AVFrame *src, صحيح flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    صحيح err, index, i;

    index = (intptr_t)src->data[1];
    إذا (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        أرجع AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        أرجع AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    إذا (err < 0)
        اذهب fail;

    لكل (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, عدم, &event);
    إذا (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, حجم(dst->data));
    أرجع err;
}

ساكن صحيح opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, صحيح flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    صحيح err, i, p, nb_planes;

    إذا (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }
    nb_planes = 2;

    إذا (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        أرجع AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  حجم(*frames_priv->mapped_frames));
    إذا (!frames_priv->mapped_frames)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        لكل (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            إذا (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned صحيح)subresource, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }
        }
    }

    أرجع 0;

fail:
    لكل (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        لكل (p = 0; p < desc->nb_planes; p++) {
            إذا (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    أرجع err;
}

#endif

#إذا HAVE_OPENCL_DRM_ARM

تعريفنوع بنية DRMARMtoOpenCLMapping {
    صحيح nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    صحيح nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

ساكن فراغ opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    صحيح i;

    لكل (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    لكل (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

ساكن صحيح opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ثابت AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = عدم;
    cl_mem_flags cl_flags;
    ثابت cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    صحيح err, i, j;

    desc = (ثابت AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    إذا (!cl_flags)
        أرجع AVERROR(EINVAL);

    mapping = av_mallocz(حجم(*mapping));
    إذا (!mapping)
        أرجع AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    لكل (i = 0; i < desc->nb_objects; i++) {
        صحيح fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        إذا (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        إذا (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            اذهب fail;
        }
    }

    mapping->nb_planes = 0;
    لكل (i = 0; i < desc->nb_layers; i++) {
        ثابت AVDRMLayerDescriptor *layer = &desc->layers[i];

        لكل (j = 0; j < layer->nb_planes; j++) {
            ثابت AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            صحيح p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            إذا (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                اذهب fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            إذا (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, عدم, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            إذا (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                اذهب fail;
            }

            ++mapping->nb_planes;
        }
    }

    لكل (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    إذا (err < 0)
        اذهب fail;

    dst->width  = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    لكل (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    لكل (i = 0; i < mapping->nb_objects; i++) {
        إذا (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, حجم(dst->data));
    أرجع err;
}

#endif

#إذا HAVE_OPENCL_VIDEOTOOLBOX

ساكن فراغ opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

ساكن صحيح opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ثابت AVFrame *src, صحيح flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = عدم;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    إذا (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        أرجع AVERROR_EXTERNAL;
    }

    desc = av_mallocz(حجم(*desc));
    إذا (!desc)
        أرجع AVERROR(ENOMEM);

    لكل (صحيح p = 0;; p++) {
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
        إذا (err == AVERROR(ENOENT))
            اكسر;
        إذا (err < 0)
            اذهب fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        إذا (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            اذهب fail;
        }
        desc->nb_planes++;
    }

    لكل (صحيح i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    إذا (err < 0)
        اذهب fail;

    dst->width = src->width;
    dst->height = src->height;

    أرجع 0;

fail:
    لكل (صحيح i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    أرجع err;
}

#endif

ساكن صحيح opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ثابت AVFrame *src, صحيح flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    إذا (hwfc->sw_format != dst->format)
        أرجع AVERROR(ENOSYS);
    أرجع opencl_map_frame(hwfc, dst, src, flags);
}

ساكن صحيح opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ثابت AVFrame *src, صحيح flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    بدل (src->format) {
#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_PIX_FMT_DRM_ڤردان:
        إذا (priv->beignet_drm_mapping_usable)
            أرجع opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_VAAPI_BEIGNET
    حالة AV_PIX_FMT_VAAPI:
        إذا (priv->beignet_drm_mapping_usable)
            أرجع opencl_map_from_vaapi(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالة AV_PIX_FMT_QSV:
    حالة AV_PIX_FMT_VAAPI:
        إذا (priv->qsv_mapping_usable)
            أرجع opencl_map_from_qsv(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_DXVA2
    حالة AV_PIX_FMT_DXVA2_VLD:
        إذا (priv->dxva2_mapping_usable)
            أرجع opencl_map_from_dxva2(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_D3D11
    حالة AV_PIX_FMT_D3D11:
        إذا (priv->d3d11_mapping_usable)
            أرجع opencl_map_from_d3d11(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_PIX_FMT_DRM_ڤردان:
        إذا (priv->drm_arm_mapping_usable)
            أرجع opencl_map_from_drm_arm(hwfc, dst, src, flags);
        اكسر;
#endif
#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_PIX_FMT_VIDEOTOOLBOX:
        أرجع opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    أرجع AVERROR(ENOSYS);
}

ساكن صحيح opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, صحيح flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    بدل (src_fc->device_ctx->type) {
#إذا HAVE_OPENCL_DRM_BEIGNET
    حالة AV_HWDEVICE_TYPE_DRM:
        إذا (!priv->beignet_drm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#endif
#إذا HAVE_OPENCL_VAAPI_BEIGNET
    حالة AV_HWDEVICE_TYPE_VAAPI:
        إذا (!priv->beignet_drm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#endif
#إذا HAVE_OPENCL_VAAPI_INTEL_MEDIA
    حالة AV_HWDEVICE_TYPE_QSV:
    حالة AV_HWDEVICE_TYPE_VAAPI:
        إذا (!priv->qsv_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#endif
#إذا HAVE_OPENCL_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        إذا (!priv->dxva2_mapping_usable)
            أرجع AVERROR(ENOSYS);
        {
            صحيح err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            إذا (err < 0)
                أرجع err;
        }
        اكسر;
#endif
#إذا HAVE_OPENCL_D3D11
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        إذا (!priv->d3d11_mapping_usable)
            أرجع AVERROR(ENOSYS);
        {
            صحيح err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            إذا (err < 0)
                أرجع err;
        }
        اكسر;
#endif
#إذا HAVE_OPENCL_DRM_ARM
    حالة AV_HWDEVICE_TYPE_DRM:
        إذا (!priv->drm_arm_mapping_usable)
            أرجع AVERROR(ENOSYS);
        اكسر;
#endif
#إذا HAVE_OPENCL_VIDEOTOOLBOX
    حالة AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        اكسر;
#endif
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }
    أرجع opencl_frames_init_command_queue(dst_fc);
}

ثابت HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = حجم(OpenCLDeviceContext),
    .frames_hwctx_size      = حجم(OpenCLFramesContext),

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

    .pix_fmts = (ثابت تعداد AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
