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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "config.h"

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_opencl.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"

#যদি HAVE_OPENCL_VAAPI_BEIGNET
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <va/va.h>
#অন্তর্ভাব <va/va_drmcommon.h>
#অন্তর্ভাব <CL/cl_intel.h>
#অন্তর্ভাব "hwcontext_vaapi.h"
#endif

#যদি HAVE_OPENCL_DRM_BEIGNET
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <CL/cl_intel.h>
#অন্তর্ভাব "hwcontext_drm.h"
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
#যদি CONFIG_LIBMFX
#অন্তর্ভাব <mfxstructures.h>
#endif
#অন্তর্ভাব <va/va.h>
#অন্তর্ভাব <CL/cl_va_api_media_sharing_intel.h>
#অন্তর্ভাব "hwcontext_vaapi.h"
#endif

#যদি HAVE_OPENCL_DXVA2
#define COBJMACROS
#অন্তর্ভাব <CL/cl_dx9_media_sharing.h>
#অন্তর্ভাব <dxva2api.h>
#অন্তর্ভাব "hwcontext_dxva2.h"
#endif

#যদি HAVE_OPENCL_D3D11
#অন্তর্ভাব <CL/cl_d3d11.h>
#অন্তর্ভাব "hwcontext_d3d11va.h"
#endif

#যদি HAVE_OPENCL_DRM_ARM
#অন্তর্ভাব <CL/cl_ext.h>
#অন্তর্ভাব <drm_fourcc.h>
#অন্তর্ভাব "hwcontext_drm.h"
#endif

#যদি HAVE_OPENCL_VIDEOTOOLBOX
#অন্তর্ভাব <OpenCL/cl_gl_ext.h>
#অন্তর্ভাব <VideoToolbox/VideoToolbox.h>
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
বাহ্য পূর্ণাঙ্ক ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          গণনা AVHWDeviceType base_dev_typ,
                                          শূন্য **base_handle);
#endif


প্রকারনির্দেশ সংরচনা OpenCLDeviceContext {
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
#যদি HAVE_OPENCL_DRM_BEIGNET
    পূর্ণাঙ্ক beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    পূর্ণাঙ্ক qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#যদি HAVE_OPENCL_DXVA2
    পূর্ণাঙ্ক dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#যদি HAVE_OPENCL_D3D11
    পূর্ণাঙ্ক d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#যদি HAVE_OPENCL_DRM_ARM
    পূর্ণাঙ্ক drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

প্রকারনির্দেশ সংরচনা OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#যদি HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    পূর্ণাঙ্ক                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


স্থির শূন্য CL_CALLBACK opencl_error_callback(ধ্রুব বর্ণ *errinfo,
                                              ধ্রুব শূন্য *private_info,
                                              size_t cb,
                                              শূন্য *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

স্থির শূন্য opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

স্থির সংরচনা {
    ধ্রুব বর্ণ *চাবি;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

স্থির সংরচনা {
    ধ্রুব বর্ণ *চাবি;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

স্থির সংরচনা {
    ধ্রুব বর্ণ *চাবি;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

স্থির বর্ণ *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info চাবি)
{
    বর্ণ *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, চাবি, 0, রিক্ত, &size);
    যদি (cle != CL_SUCCESS)
        প্রত্যাগম রিক্ত;
    str = av_malloc(size);
    যদি (!str)
        প্রত্যাগম রিক্ত;
    cle = clGetPlatformInfo(platform_id, চাবি, size, str, &size);
    যদি (cle != CL_SUCCESS) {
        av_free(str);
        প্রত্যাগম রিক্ত;
    }
    av_assert0(strlen(str) + 1 == size);
    প্রত্যাগম str;
}

স্থির বর্ণ *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info চাবি)
{
    বর্ণ *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, চাবি, 0, রিক্ত, &size);
    যদি (cle != CL_SUCCESS)
        প্রত্যাগম রিক্ত;
    str = av_malloc(size);
    যদি (!str)
        প্রত্যাগম রিক্ত;
    cle = clGetDeviceInfo(device_id, চাবি, size, str, &size);
    যদি (cle != CL_SUCCESS) {
        av_free(str);
        প্রত্যাগম রিক্ত;
    }
    av_assert0(strlen(str) + 1== size);
    প্রত্যাগম str;
}

স্থির পূর্ণাঙ্ক opencl_check_platform_extension(cl_platform_id platform_id,
                                           ধ্রুব বর্ণ *name)
{
    বর্ণ *str;
    পূর্ণাঙ্ক found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    যদি (str && strstr(str, name))
        found = 1;
    av_free(str);
    প্রত্যাগম found;
}

স্থির পূর্ণাঙ্ক opencl_check_device_extension(cl_device_id device_id,
                                         ধ্রুব বর্ণ *name)
{
    বর্ণ *str;
    পূর্ণাঙ্ক found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    যদি (str && strstr(str, name))
        found = 1;
    av_free(str);
    প্রত্যাগম found;
}

av_unused স্থির পূর্ণাঙ্ক opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ধ্রুব বর্ণ *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    যদি (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        প্রত্যাগম 1;
    }

    যদি (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        প্রত্যাগম 1;
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      শূন্য *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, রিক্ত, nb_platforms);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        প্রত্যাগম AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, পরিমাণ(**platforms));
    যদি (!*platforms)
        প্রত্যাগম AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        প্রত্যাগম AVERROR(ENODEV);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ধ্রুব বর্ণ *platform_name,
                                  শূন্য *context)
{
    AVDictionary *opts = context;
    ধ্রুব AVDictionaryEntry *param;
    বর্ণ *str;
    পূর্ণাঙ্ক i, ret = 0;

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].চাবি,
                            রিক্ত, 0);
        যদি (!param)
            অনুবর্ত;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        যদি (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].চাবি, platform_name);
            প্রত্যাগম AVERROR_UNKNOWN;
        }
        যদি (!av_stristr(str, param->মান)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->চাবি, str);
            ret = 1;
        }
        av_free(str);
    }

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ধ্রুব বর্ণ *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    শূন্য *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, রিক্ত, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        প্রত্যাগম 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        প্রত্যাগম AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, পরিমাণ(**devices));
    যদি (!*devices)
        প্রত্যাগম AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        প্রত্যাগম AVERROR(ENODEV);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ধ্রুব বর্ণ *device_name,
                                শূন্য *context)
{
    AVDictionary *opts = context;
    ধ্রুব AVDictionaryEntry *param;
    বর্ণ *str;
    পূর্ণাঙ্ক i, ret = 0;

    param = av_dict_get(opts, "device_type", রিক্ত, 0);
    যদি (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        প্রতি (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            যদি (!strcmp(opencl_device_types[i].চাবি, param->মান)) {
                match_type = opencl_device_types[i].type;
                ভঙ্গ;
            }
        }
        যদি (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->মান);
            প্রত্যাগম AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              পরিমাণ(device_type), &device_type, রিক্ত);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            প্রত্যাগম AVERROR_UNKNOWN;
        }

        যদি (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            প্রত্যাগম 1;
        }
    }

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].চাবি,
                            রিক্ত, 0);
        যদি (!param)
            অনুবর্ত;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        যদি (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].চাবি, device_name);
            প্রত্যাগম AVERROR_UNKNOWN;
        }
        যদি (!av_stristr(str, param->মান)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->চাবি, str);
            ret = 1;
        }
        av_free(str);
    }

    প্রত্যাগম ret;
}

প্রকারনির্দেশ সংরচনা OpenCLDeviceSelector {
    পূর্ণাঙ্ক platform_index;
    পূর্ণাঙ্ক device_index;
    শূন্য *context;
    পূর্ণাঙ্ক (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               শূন্য *context);
    পূর্ণাঙ্ক (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ধ্রুব বর্ণ *platform_name,
                               শূন্য *context);
    পূর্ণাঙ্ক (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ধ্রুব বর্ণ *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               শূন্য *context);
    পূর্ণাঙ্ক (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ধ্রুব বর্ণ *device_name,
                               শূন্য *context);
} OpenCLDeviceSelector;

স্থির পূর্ণাঙ্ক opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ধ্রুব OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = রিক্ত;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = রিক্ত;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    বর্ণ *platform_name_src = রিক্ত,
         *device_name_src   = রিক্ত;
    পূর্ণাঙ্ক err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    যদি (err)
        প্রত্যাগম err;

    found = 0;
    প্রতি (p = 0; p < nb_platforms; p++) {
        ধ্রুব বর্ণ *platform_name;

        যদি (selector->platform_index >= 0 &&
            selector->platform_index != p)
            অনুবর্ত;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        যদি (platform_name_src)
            platform_name = platform_name_src;
        অন্যথা
            platform_name = "Unknown Platform";

        যদি (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            যদি (err < 0)
                গচ্ছ fail;
            যদি (err > 0)
                অনুবর্ত;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        যদি (err < 0)
            অনুবর্ত;

        প্রতি (d = 0; d < nb_devices; d++) {
            ধ্রুব বর্ণ *device_name;

            যদি (selector->device_index >= 0 &&
                selector->device_index != d)
                অনুবর্ত;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            যদি (device_name_src)
                device_name = device_name_src;
            অন্যথা
                device_name = "Unknown Device";

            যদি (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                যদি (err < 0)
                    গচ্ছ fail;
                যদি (err > 0)
                    অনুবর্ত;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    যদি (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        গচ্ছ fail;
    }
    যদি (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        গচ্ছ fail;
    }

    যদি (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } অন্যথা {
        যদি (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    যদি (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        গচ্ছ fail;
    }

    hwdev->মুক্ত = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    প্রত্যাগম err;
}

স্থির পূর্ণাঙ্ক opencl_device_create(AVHWDeviceContext *hwdev, ধ্রুব বর্ণ *device,
                                AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    যদি (device && device[0]) {
        // Match one or both indices for platform and device.
        পূর্ণাঙ্ক d = -1, p = -1, ret;
        যদি (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        অন্যথা
            ret = sscanf(device, "%d.%d", &p, &d);
        যদি (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            প্রত্যাগম AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } অন্যথা {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    প্রত্যাগম opencl_device_create_internal(hwdev, &selector, রিক্ত);
}

স্থির পূর্ণাঙ্ক opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    যদি (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            প্রত্যাগম AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } অন্যথা {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        যদি (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            প্রত্যাগম AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          পরিমাণ(priv->platform_id), &priv->platform_id,
                          রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        প্রত্যাগম AVERROR(EIO);
    }

#define CL_FUNC(name, desc) কুরু {                                \
        যদি (fail)                                               \
            ভঙ্গ;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        যদি (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } অন্যথা {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } যাবত্ (0)

#যদি HAVE_OPENCL_DRM_BEIGNET
    {
        পূর্ণাঙ্ক fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        যদি (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } অন্যথা {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = রিক্ত;
        VADisplay va_display;
        ধ্রুব বর্ণ *va_ext = "cl_intel_va_api_media_sharing";
        পূর্ণাঙ্ক i, fail = 0;

        যদি (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            গচ্ছ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, রিক্ত, &props_size);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            গচ্ছ no_qsv;
        }
        যদি (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            গচ্ছ no_qsv;
        }

        props = av_malloc(props_size);
        যদি (!props)
            প্রত্যাগম AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, রিক্ত);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            গচ্ছ no_qsv;
        }

        va_display = রিক্ত;
        প্রতি (i = 0; i < (props_size / পরিমাণ(*props) - 1); i++) {
            যদি (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                ভঙ্গ;
            }
        }
        যদি (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            গচ্ছ no_qsv;
        }
        যদি (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            গচ্ছ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        যদি (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } অন্যথা {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#যদি HAVE_OPENCL_DXVA2
    {
        পূর্ণাঙ্ক fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        যদি (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } অন্যথা {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#যদি HAVE_OPENCL_D3D11
    {
        ধ্রুব বর্ণ *d3d11_ext = "cl_khr_d3d11_sharing";
        ধ্রুব বর্ণ *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        পূর্ণাঙ্ক fail = 0;

        যদি (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } অন্যথা যদি (!opencl_check_extension(hwdev, nv12_ext)) {
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

        যদি (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } অন্যথা {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#যদি HAVE_OPENCL_DRM_ARM
    {
        ধ্রুব বর্ণ *drm_arm_ext = "cl_arm_import_memory";
        ধ্রুব বর্ণ *image_ext   = "cl_khr_image2d_from_buffer";
        পূর্ণাঙ্ক fail = 0;

        যদি (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        যদি (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        যদি (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } অন্যথা {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    প্রত্যাগম 0;
}

স্থির শূন্য opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    যদি (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = রিক্ত;
    }
}

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
স্থির পূর্ণাঙ্ক opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ধ্রুব বর্ণ *platform_name,
                                                    শূন্য *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    যদি (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        প্রত্যাগম 1;
    } অন্যথা {
        প্রত্যাগম 0;
    }
}

স্থির পূর্ণাঙ্ক opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ধ্রুব বর্ণ *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      শূন্য *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    যদি (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, রিক্ত, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        প্রত্যাগম 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, পরিমাণ(**devices));
    যদি (!*devices)
        প্রত্যাগম AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ধ্রুব বর্ণ *device_name,
                                                  শূন্য *context)
{
    ধ্রুব বর্ণ *va_ext = "cl_intel_va_api_media_sharing";

    যদি (opencl_check_device_extension(device_id, va_ext)) {
        প্রত্যাগম 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        প্রত্যাগম 1;
    }
}
#endif

#যদি HAVE_OPENCL_DXVA2
স্থির পূর্ণাঙ্ক opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ধ্রুব বর্ণ *platform_name,
                                        শূন্য *context)
{
    ধ্রুব বর্ণ *dx9_ext = "cl_khr_dx9_media_sharing";

    যদি (opencl_check_platform_extension(platform_id, dx9_ext)) {
        প্রত্যাগম 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        প্রত্যাগম 1;
    }
}

স্থির পূর্ণাঙ্ক opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুব বর্ণ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          শূন্য *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    যদি (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (শূন্য**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, রিক্ত, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        প্রত্যাগম 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, পরিমাণ(**devices));
    যদি (!*devices)
        প্রত্যাগম AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (শূন্য**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    প্রত্যাগম 0;
}
#endif

#যদি HAVE_OPENCL_D3D11
স্থির পূর্ণাঙ্ক opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ধ্রুব বর্ণ *platform_name,
                                        শূন্য *context)
{
    ধ্রুব বর্ণ *d3d11_ext = "cl_khr_d3d11_sharing";

    যদি (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        প্রত্যাগম 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        প্রত্যাগম 1;
    }
}

স্থির পূর্ণাঙ্ক opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুব বর্ণ *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          শূন্য *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    যদি (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, রিক্ত, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        প্রত্যাগম 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, পরিমাণ(**devices));
    যদি (!*devices)
        প্রত্যাগম AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    প্রত্যাগম 0;
}
#endif

#যদি HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
স্থির পূর্ণাঙ্ক opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ধ্রুব বর্ণ *device_name,
                                    শূন্য *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          পরিমাণ(device_type), &device_type, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        প্রত্যাগম AVERROR_UNKNOWN;
    }
    যদি (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        প্রত্যাগম 1;
    }

    প্রত্যাগম 0;
}
#endif

#যদি HAVE_OPENCL_DRM_ARM
স্থির পূর্ণাঙ্ক opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুব বর্ণ *platform_name,
                                          শূন্য *context)
{
    ধ্রুব বর্ণ *drm_arm_ext = "cl_arm_import_memory";

    যদি (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        প্রত্যাগম 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        প্রত্যাগম 1;
    }
}

স্থির পূর্ণাঙ্ক opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ধ্রুব বর্ণ *device_name,
                                        শূন্য *context)
{
    ধ্রুব বর্ণ *drm_arm_ext = "cl_arm_import_memory";

    যদি (opencl_check_device_extension(device_id, drm_arm_ext)) {
        প্রত্যাগম 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        প্রত্যাগম 1;
    }
}
#endif

স্থির পূর্ণাঙ্ক opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক err;
    বিকল্প (src_ctx->type) {

#যদি HAVE_OPENCL_DRM_BEIGNET
    পক্ষ AV_HWDEVICE_TYPE_DRM:
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = রিক্ত;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            যদি (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            যদি (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = রিক্ত,
                };
                err = opencl_device_create_internal(hwdev, &selector, রিক্ত);
            }
            av_dict_free(&selector_opts);
        }
        ভঙ্গ;
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
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
        ভঙ্গ;
#endif

#যদি HAVE_OPENCL_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            যদি (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                ভঙ্গ;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            যদি (SUCCEEDED(hr)) {
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
            } অন্যথা {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        ভঙ্গ;
#endif

#যদি HAVE_OPENCL_D3D11
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
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
        ভঙ্গ;
#endif

#যদি HAVE_OPENCL_DRM_ARM
    পক্ষ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = রিক্ত,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, রিক্ত);
        }
        ভঙ্গ;
#endif

#যদি HAVE_OPENCL_VIDEOTOOLBOX
    পক্ষ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, রিক্ত, রিক্ত, 0);
        ভঙ্গ;
#endif

    স্বভাব:
        err = AVERROR(ENOSYS);
        ভঙ্গ;
    }

    প্রত্যাগম err;
}

স্থির পূর্ণাঙ্ক opencl_get_plane_format(গণনা AVPixelFormat pixfmt,
                                   পূর্ণাঙ্ক plane, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ধ্রুব AVPixFmtDescriptor *desc;
    ধ্রুব AVComponentDescriptor *comp;
    পূর্ণাঙ্ক channels = 0, order = 0, depth = 0, step = 0;
    পূর্ণাঙ্ক wsub, hsub, alpha;
    পূর্ণাঙ্ক c;

    যদি (plane >= AV_অঙ্ক_DATA_POINTERS)
        প্রত্যাগম AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    যদি (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        প্রত্যাগম AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    যদি (width & wsub - 1 || height & hsub - 1)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        যদি (comp->plane != plane)
            অনুবর্ত;
        // The step size must be a power of two.
        যদি (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            প্রত্যাগম AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        যদি (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            প্রত্যাগম AVERROR(EINVAL);
        // The depth must not vary between components.
        যদি (depth && comp->depth != depth)
            প্রত্যাগম AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        যদি (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            প্রত্যাগম AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        যদি (step && comp->step != step)
            প্রত্যাগম AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    যদি (channels == 0)
        প্রত্যাগম AVERROR(ENOENT);

    memset(image_format, 0, পরিমাণ(*image_format));
    memset(image_desc,   0, পরিমাণ(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    যদি (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } অন্যথা {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    যদি (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } অন্যথা {
        যদি (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        অন্যথা যদি (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        অন্যথা
            প্রত্যাগম AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    পক্ষ order: image_format->image_channel_order = type; ভঙ্গ;
    বিকল্প (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ধ্রুব শূন্য *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = রিক্ত;
    cl_int cle;
    গণনা AVPixelFormat pix_fmt;
    পূর্ণাঙ্ক err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          পরিমাণ(max_width), &max_width, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } অন্যথা {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          পরিমাণ(max_height), &max_height, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } অন্যথা {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, রিক্ত, &nb_image_formats);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        গচ্ছ fail;
    }
    যদি (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, পরিমাণ(*image_formats));
    যদি (!image_formats) {
        err = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, রিক্ত);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    pix_fmts_found = 0;
    প্রতি (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        পূর্ণাঙ্ক plane, i;

        প্রতি (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            যদি (err < 0)
                ভঙ্গ;

            প্রতি (i = 0; i < nb_image_formats; i++) {
                যদি (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    ভঙ্গ;
            }
            যদি (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                ভঙ্গ;
            }
        }
        যদি (err != AVERROR(ENOENT))
            অনুবর্ত;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                পরিমাণ(*constraints->valid_sw_formats));
        যদি (err < 0)
            গচ্ছ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, পরিমাণ(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        গচ্ছ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    প্রত্যাগম 0;

fail:
    av_freep(&image_formats);
    প্রত্যাগম err;
}

স্থির শূন্য opencl_pool_free(শূন্য *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    পূর্ণাঙ্ক p;

    প্রতি (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

স্থির AVBufferRef *opencl_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    পূর্ণাঙ্ক err, p;
    AVBufferRef *ref;

    desc = av_mallocz(পরিমাণ(*desc));
    যদি (!desc)
        প্রত্যাগম রিক্ত;

    প্রতি (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        যদি (err == AVERROR(ENOENT))
            ভঙ্গ;
        যদি (err < 0)
            গচ্ছ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, রিক্ত, &cle);
        যদি (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            গচ্ছ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, পরিমাণ(*desc),
                           &opencl_pool_free, hwfc, 0);
    যদি (!ref)
        গচ্ছ fail;

    প্রত্যাগম ref;

fail:
    প্রতি (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    প্রত্যাগম রিক্ত;
}

স্থির পূর্ণাঙ্ক opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    যদি (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        প্রত্যাগম AVERROR(EIO);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_frames_init(AVHWFramesContext *hwfc)
{
    যদি (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(পরিমাণ(cl_mem), hwfc,
                                 &opencl_pool_alloc, রিক্ত);
        যদি (!ffhwframesctx(hwfc)->pool_internal)
            প্রত্যাগম AVERROR(ENOMEM);
    }

    প্রত্যাগম opencl_frames_init_command_queue(hwfc);
}

স্থির শূন্য opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#যদি HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    পূর্ণাঙ্ক i, p;
    প্রতি (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        প্রতি (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            যদি (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    যদি (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = রিক্ত;
    }
}

স্থির পূর্ণাঙ্ক opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    পূর্ণাঙ্ক p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    যদি (!frame->buf[0])
        প্রত্যাগম AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    প্রতি (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       গণনা AVHWFrameTransferDirection dir,
                                       গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, পরিমাণ(*fmts));
    যদি (!fmts)
        প্রত্যাগম AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, পূর্ণাঙ্ক nb_events)
{
    cl_int cle;
    পূর্ণাঙ্ক i;

    cle = clWaitForEvents(nb_events, events);
    যদি (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        প্রত্যাগম AVERROR(EIO);
    }

    প্রতি (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ধ্রুব AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_অঙ্ক_DATA_POINTERS];
    পূর্ণাঙ্ক err, p;

    যদি (dst->format != hwfc->sw_format)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err < 0) {
            যদি (err == AVERROR(ENOENT))
                err = 0;
            ভঙ্গ;
        }

        যদি (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ভঙ্গ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, রিক্ত, &events[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ভঙ্গ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    প্রত্যাগম err;
}

স্থির পূর্ণাঙ্ক opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ধ্রুব AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_অঙ্ক_DATA_POINTERS];
    পূর্ণাঙ্ক err, p;

    যদি (src->format != hwfc->sw_format)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err < 0) {
            যদি (err == AVERROR(ENOENT))
                err = 0;
            ভঙ্গ;
        }

        যদি (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            ভঙ্গ;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, রিক্ত, &events[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            ভঙ্গ;
        }
    }

    opencl_wait_events(hwfc, events, p);

    প্রত্যাগম err;
}

প্রকারনির্দেশ সংরচনা OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    শূন্য *address[AV_অঙ্ক_DATA_POINTERS];
} OpenCLMapping;

স্থির শূন্য opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_অঙ্ক_DATA_POINTERS];
    পূর্ণাঙ্ক p, e;
    cl_int cle;

    প্রতি (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        যদি (!map->address[p])
            ভঙ্গ;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, রিক্ত, &events[e]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

স্থির পূর্ণাঙ্ক opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
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
    cl_event events[AV_অঙ্ক_DATA_POINTERS];
    পূর্ণাঙ্ক err, p;

    av_assert0(hwfc->sw_format == dst->format);

    যদি (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } অন্যথা {
        map_flags = 0;
        যদি (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        যদি (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(পরিমাণ(*map));
    যদি (!map)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err == AVERROR(ENOENT))
            ভঙ্গ;
        যদি (err < 0)
            গচ্ছ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, রিক্ত, 0, রিক্ত,
                              &events[p], &cle);
        যদি (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            গচ্ছ fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    যদি (err < 0)
        গচ্ছ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    প্রতি (p = 0; p < AV_অঙ্ক_DATA_POINTERS; p++) {
        যদি (!map->address[p])
            ভঙ্গ;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, রিক্ত, &events[p]);
    }
    যদি (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    প্রত্যাগম err;
}

#যদি HAVE_OPENCL_DRM_BEIGNET

প্রকারনির্দেশ সংরচনা DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

স্থির শূন্য opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        যদি (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

স্থির পূর্ণাঙ্ক opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ধ্রুব AVFrame *src,
                                       পূর্ণাঙ্ক flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ধ্রুব AVDRMFrameDescriptor *desc;
    cl_int cle;
    পূর্ণাঙ্ক err, i, j, p;

    desc = (ধ্রুব AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(পরিমাণ(*mapping));
    যদি (!mapping)
        প্রত্যাগম AVERROR(ENOMEM);

    p = 0;
    প্রতি (i = 0; i < desc->nb_layers; i++) {
        ধ্রুব AVDRMLayerDescriptor *layer = &desc->layers[i];
        প্রতি (j = 0; j < layer->nb_planes; j++) {
            ধ্রুব AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ধ্রুব AVDRMObjectDescriptor *object =
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
            যদি (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                গচ্ছ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            যদি (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                গচ্ছ fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    প্রতি (p = 0; p < mapping->frame.nb_planes; p++) {
        যদি (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, পরিমাণ(dst->data));
    প্রত্যাগম err;
}

#যদি HAVE_OPENCL_VAAPI_BEIGNET

স্থির পূর্ণাঙ্ক opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ধ্রুব AVFrame *src,
                                 পূর্ণাঙ্ক flags)
{
    AVFrame *tmp;
    পূর্ণাঙ্ক err;

    tmp = av_frame_alloc();
    যদি (!tmp)
        প্রত্যাগম AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_মৌলিক;

    err = av_hwframe_map(tmp, src, flags);
    যদি (err < 0)
        গচ্ছ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    যদি (err < 0)
        গচ্ছ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    প্রত্যাগম err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

স্থির অন্তঃস্থ cl_mem_flags opencl_mem_flags_for_mapping(পূর্ণাঙ্ক map_flags)
{
    যদি ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        প্রত্যাগম CL_MEM_READ_WRITE;
    অন্যথা যদি (map_flags & AV_HWFRAME_MAP_READ)
        প্রত্যাগম CL_MEM_READ_ONLY;
    অন্যথা যদি (map_flags & AV_HWFRAME_MAP_WRITE)
        প্রত্যাগম CL_MEM_WRITE_ONLY;
    অন্যথা
        প্রত্যাগম 0;
}

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA

স্থির শূন্য opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    পূর্ণাঙ্ক p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    প্রতি (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

স্থির পূর্ণাঙ্ক opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
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
    পূর্ণাঙ্ক err, p;

#যদি CONFIG_LIBMFX
    যদি (src->format == AV_PIX_FMT_QSV) {
        শূন্য *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        যদি (err < 0)
            প্রত্যাগম err;
        va_surface = *(VASurfaceID *)base_handle;
    } অন্যথা
#endif
        যদি (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } অন্যথা {
        প্রত্যাগম AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        প্রত্যাগম AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(পরিমাণ(*desc));
    যদি (!desc)
        প্রত্যাগম AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    প্রতি (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        যদি (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            গচ্ছ fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        গচ্ছ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        গচ্ছ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    প্রতি (p = 0; p < desc->nb_planes; p++)
        যদি (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, পরিমাণ(dst->data));
    প্রত্যাগম err;
}

#endif

#যদি HAVE_OPENCL_DXVA2

স্থির শূন্য opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        প্রত্যাগম;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

স্থির পূর্ণাঙ্ক opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    পূর্ণাঙ্ক err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
        যদি (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            ভঙ্গ;
    }
    যদি (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        প্রত্যাগম AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        গচ্ছ fail;

    প্রতি (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, পরিমাণ(dst->data));
    প্রত্যাগম err;
}

স্থির পূর্ণাঙ্ক opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, পূর্ণাঙ্ক flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    পূর্ণাঙ্ক err, i, p, nb_planes;

    যদি (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }
    nb_planes = 2;

    যদি (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        প্রত্যাগম AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  পরিমাণ(*frames_priv->mapped_frames));
    যদি (!frames_priv->mapped_frames)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = রিক্ত,
        };
        desc->nb_planes = nb_planes;
        প্রতি (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            যদি (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                গচ্ছ fail;
            }
        }
    }

    প্রত্যাগম 0;

fail:
    প্রতি (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        প্রতি (p = 0; p < desc->nb_planes; p++) {
            যদি (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    প্রত্যাগম err;
}

#endif

#যদি HAVE_OPENCL_D3D11

স্থির শূন্য opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

স্থির পূর্ণাঙ্ক opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    পূর্ণাঙ্ক err, index, i;

    index = (intptr_t)src->data[1];
    যদি (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        প্রত্যাগম AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        প্রত্যাগম AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        গচ্ছ fail;

    প্রতি (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, রিক্ত, &event);
    যদি (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, পরিমাণ(dst->data));
    প্রত্যাগম err;
}

স্থির পূর্ণাঙ্ক opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, পূর্ণাঙ্ক flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    পূর্ণাঙ্ক err, i, p, nb_planes;

    যদি (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }
    nb_planes = 2;

    যদি (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        প্রত্যাগম AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  পরিমাণ(*frames_priv->mapped_frames));
    যদি (!frames_priv->mapped_frames)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        প্রতি (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            যদি (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned পূর্ণাঙ্ক)subresource, cle);
                err = AVERROR(EIO);
                গচ্ছ fail;
            }
        }
    }

    প্রত্যাগম 0;

fail:
    প্রতি (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        প্রতি (p = 0; p < desc->nb_planes; p++) {
            যদি (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    প্রত্যাগম err;
}

#endif

#যদি HAVE_OPENCL_DRM_ARM

প্রকারনির্দেশ সংরচনা DRMARMtoOpenCLMapping {
    পূর্ণাঙ্ক nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    পূর্ণাঙ্ক nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

স্থির শূন্য opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    প্রতি (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

স্থির পূর্ণাঙ্ক opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ধ্রুব AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = রিক্ত;
    cl_mem_flags cl_flags;
    ধ্রুব cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    পূর্ণাঙ্ক err, i, j;

    desc = (ধ্রুব AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        প্রত্যাগম AVERROR(EINVAL);

    mapping = av_mallocz(পরিমাণ(*mapping));
    যদি (!mapping)
        প্রত্যাগম AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    প্রতি (i = 0; i < desc->nb_objects; i++) {
        পূর্ণাঙ্ক fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        যদি (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        যদি (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            গচ্ছ fail;
        }
    }

    mapping->nb_planes = 0;
    প্রতি (i = 0; i < desc->nb_layers; i++) {
        ধ্রুব AVDRMLayerDescriptor *layer = &desc->layers[i];

        প্রতি (j = 0; j < layer->nb_planes; j++) {
            ধ্রুব AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            পূর্ণাঙ্ক p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            যদি (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                গচ্ছ fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            যদি (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                গচ্ছ fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, রিক্ত, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            যদি (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                গচ্ছ fail;
            }

            ++mapping->nb_planes;
        }
    }

    প্রতি (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width  = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    প্রতি (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    প্রতি (i = 0; i < mapping->nb_objects; i++) {
        যদি (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, পরিমাণ(dst->data));
    প্রত্যাগম err;
}

#endif

#যদি HAVE_OPENCL_VIDEOTOOLBOX

স্থির শূন্য opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

স্থির পূর্ণাঙ্ক opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = রিক্ত;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    যদি (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        প্রত্যাগম AVERROR_EXTERNAL;
    }

    desc = av_mallocz(পরিমাণ(*desc));
    যদি (!desc)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (পূর্ণাঙ্ক p = 0;; p++) {
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
        যদি (err == AVERROR(ENOENT))
            ভঙ্গ;
        যদি (err < 0)
            গচ্ছ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        যদি (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            গচ্ছ fail;
        }
        desc->nb_planes++;
    }

    প্রতি (পূর্ণাঙ্ক i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    যদি (err < 0)
        গচ্ছ fail;

    dst->width = src->width;
    dst->height = src->height;

    প্রত্যাগম 0;

fail:
    প্রতি (পূর্ণাঙ্ক i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    প্রত্যাগম err;
}

#endif

স্থির পূর্ণাঙ্ক opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    যদি (hwfc->sw_format != dst->format)
        প্রত্যাগম AVERROR(ENOSYS);
    প্রত্যাগম opencl_map_frame(hwfc, dst, src, flags);
}

স্থির পূর্ণাঙ্ক opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    বিকল্প (src->format) {
#যদি HAVE_OPENCL_DRM_BEIGNET
    পক্ষ AV_PIX_FMT_DRM_মৌলিক:
        যদি (priv->beignet_drm_mapping_usable)
            প্রত্যাগম opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VAAPI_BEIGNET
    পক্ষ AV_PIX_FMT_VAAPI:
        যদি (priv->beignet_drm_mapping_usable)
            প্রত্যাগম opencl_map_from_vaapi(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    পক্ষ AV_PIX_FMT_QSV:
    পক্ষ AV_PIX_FMT_VAAPI:
        যদি (priv->qsv_mapping_usable)
            প্রত্যাগম opencl_map_from_qsv(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_DXVA2
    পক্ষ AV_PIX_FMT_DXVA2_VLD:
        যদি (priv->dxva2_mapping_usable)
            প্রত্যাগম opencl_map_from_dxva2(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_D3D11
    পক্ষ AV_PIX_FMT_D3D11:
        যদি (priv->d3d11_mapping_usable)
            প্রত্যাগম opencl_map_from_d3d11(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_DRM_ARM
    পক্ষ AV_PIX_FMT_DRM_মৌলিক:
        যদি (priv->drm_arm_mapping_usable)
            প্রত্যাগম opencl_map_from_drm_arm(hwfc, dst, src, flags);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VIDEOTOOLBOX
    পক্ষ AV_PIX_FMT_VIDEOTOOLBOX:
        প্রত্যাগম opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    প্রত্যাগম AVERROR(ENOSYS);
}

স্থির পূর্ণাঙ্ক opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, পূর্ণাঙ্ক flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    বিকল্প (src_fc->device_ctx->type) {
#যদি HAVE_OPENCL_DRM_BEIGNET
    পক্ষ AV_HWDEVICE_TYPE_DRM:
        যদি (!priv->beignet_drm_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VAAPI_BEIGNET
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        যদি (!priv->beignet_drm_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    পক্ষ AV_HWDEVICE_TYPE_QSV:
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        যদি (!priv->qsv_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        যদি (!priv->dxva2_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        {
            পূর্ণাঙ্ক err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            যদি (err < 0)
                প্রত্যাগম err;
        }
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_D3D11
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        যদি (!priv->d3d11_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        {
            পূর্ণাঙ্ক err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            যদি (err < 0)
                প্রত্যাগম err;
        }
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_DRM_ARM
    পক্ষ AV_HWDEVICE_TYPE_DRM:
        যদি (!priv->drm_arm_mapping_usable)
            প্রত্যাগম AVERROR(ENOSYS);
        ভঙ্গ;
#endif
#যদি HAVE_OPENCL_VIDEOTOOLBOX
    পক্ষ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        ভঙ্গ;
#endif
    স্বভাব:
        প্রত্যাগম AVERROR(ENOSYS);
    }
    প্রত্যাগম opencl_frames_init_command_queue(dst_fc);
}

ধ্রুব HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = পরিমাণ(OpenCLDeviceContext),
    .frames_hwctx_size      = পরিমাণ(OpenCLFramesContext),

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

    .pix_fmts = (ধ্রুব গণনা AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
