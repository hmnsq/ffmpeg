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
বাহ্যিক পূর্ণসংখ্যা ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          গণনা AVHWDeviceType base_dev_typ,
                                          শূন্য **base_handle);
#endif


প্রকারলেখ কাঠামো OpenCLDeviceContext {
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
    পূর্ণসংখ্যা beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    পূর্ণসংখ্যা qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#যদি HAVE_OPENCL_DXVA2
    পূর্ণসংখ্যা dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#যদি HAVE_OPENCL_D3D11
    পূর্ণসংখ্যা d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#যদি HAVE_OPENCL_DRM_ARM
    পূর্ণসংখ্যা drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

প্রকারলেখ কাঠামো OpenCLFramesContext {
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
    পূর্ণসংখ্যা                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


স্থির শূন্য CL_CALLBACK opencl_error_callback(ধ্রুবক অক্ষর *errinfo,
                                              ধ্রুবক শূন্য *private_info,
                                              size_t cb,
                                              শূন্য *user_তথ্য)
{
    AVHWDeviceContext *ctx = user_তথ্য;
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

স্থির কাঠামো {
    ধ্রুবক অক্ষর *চাবি;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

স্থির কাঠামো {
    ধ্রুবক অক্ষর *চাবি;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

স্থির কাঠামো {
    ধ্রুবক অক্ষর *চাবি;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

স্থির অক্ষর *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info চাবি)
{
    অক্ষর *str;
    size_t আকার_2;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, চাবি, 0, ফাঁকা, &আকার_2);
    যদি (cle != CL_SUCCESS)
        ফেরত ফাঁকা;
    str = av_malloc(আকার_2);
    যদি (!str)
        ফেরত ফাঁকা;
    cle = clGetPlatformInfo(platform_id, চাবি, আকার_2, str, &আকার_2);
    যদি (cle != CL_SUCCESS) {
        av_free(str);
        ফেরত ফাঁকা;
    }
    av_assert0(strlen(str) + 1 == আকার_2);
    ফেরত str;
}

স্থির অক্ষর *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info চাবি)
{
    অক্ষর *str;
    size_t আকার_2;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, চাবি, 0, ফাঁকা, &আকার_2);
    যদি (cle != CL_SUCCESS)
        ফেরত ফাঁকা;
    str = av_malloc(আকার_2);
    যদি (!str)
        ফেরত ফাঁকা;
    cle = clGetDeviceInfo(device_id, চাবি, আকার_2, str, &আকার_2);
    যদি (cle != CL_SUCCESS) {
        av_free(str);
        ফেরত ফাঁকা;
    }
    av_assert0(strlen(str) + 1== আকার_2);
    ফেরত str;
}

স্থির পূর্ণসংখ্যা opencl_check_platform_extension(cl_platform_id platform_id,
                                           ধ্রুবক অক্ষর *name)
{
    অক্ষর *str;
    পূর্ণসংখ্যা found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    যদি (str && strstr(str, name))
        found = 1;
    av_free(str);
    ফেরত found;
}

স্থির পূর্ণসংখ্যা opencl_check_device_extension(cl_device_id device_id,
                                         ধ্রুবক অক্ষর *name)
{
    অক্ষর *str;
    পূর্ণসংখ্যা found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    যদি (str && strstr(str, name))
        found = 1;
    av_free(str);
    ফেরত found;
}

av_unused স্থির পূর্ণসংখ্যা opencl_check_extension(AVHWDeviceContext *hwdev,
                                            ধ্রুবক অক্ষর *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    যদি (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ফেরত 1;
    }

    যদি (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ফেরত 1;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      শূন্য *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ফাঁকা, nb_platforms);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ফেরত AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, আকার(**platforms));
    যদি (!*platforms)
        ফেরত AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ফেরত AVERROR(ENODEV);
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  ধ্রুবক অক্ষর *platform_name,
                                  শূন্য *context)
{
    AVDictionary *opts = context;
    ধ্রুবক AVDictionaryEntry *param;
    অক্ষর *str;
    পূর্ণসংখ্যা i, ret = 0;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].চাবি,
                            ফাঁকা, 0);
        যদি (!param)
            চালু;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        যদি (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].চাবি, platform_name);
            ফেরত AVERROR_UNKNOWN;
        }
        যদি (!av_stristr(str, param->মান)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->চাবি, str);
            ret = 1;
        }
        av_free(str);
    }

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    ধ্রুবক অক্ষর *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    শূন্য *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ফাঁকা, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ফেরত 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ফেরত AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, আকার(**devices));
    যদি (!*devices)
        ফেরত AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ফেরত AVERROR(ENODEV);
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                ধ্রুবক অক্ষর *device_name,
                                শূন্য *context)
{
    AVDictionary *opts = context;
    ধ্রুবক AVDictionaryEntry *param;
    অক্ষর *str;
    পূর্ণসংখ্যা i, ret = 0;

    param = av_dict_get(opts, "device_type", ফাঁকা, 0);
    যদি (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        জন্য (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            যদি (!strcmp(opencl_device_types[i].চাবি, param->মান)) {
                match_type = opencl_device_types[i].type;
                বিরতি;
            }
        }
        যদি (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->মান);
            ফেরত AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              আকার(device_type), &device_type, ফাঁকা);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ফেরত AVERROR_UNKNOWN;
        }

        যদি (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ফেরত 1;
        }
    }

    জন্য (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].চাবি,
                            ফাঁকা, 0);
        যদি (!param)
            চালু;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        যদি (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].চাবি, device_name);
            ফেরত AVERROR_UNKNOWN;
        }
        যদি (!av_stristr(str, param->মান)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->চাবি, str);
            ret = 1;
        }
        av_free(str);
    }

    ফেরত ret;
}

প্রকারলেখ কাঠামো OpenCLDeviceSelector {
    পূর্ণসংখ্যা platform_সূচক;
    পূর্ণসংখ্যা device_সূচক;
    শূন্য *context;
    পূর্ণসংখ্যা (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               শূন্য *context);
    পূর্ণসংখ্যা (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ধ্রুবক অক্ষর *platform_name,
                               শূন্য *context);
    পূর্ণসংখ্যা (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               ধ্রুবক অক্ষর *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               শূন্য *context);
    পূর্ণসংখ্যা (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               ধ্রুবক অক্ষর *device_name,
                               শূন্য *context);
} OpenCLDeviceSelector;

স্থির পূর্ণসংখ্যা opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         ধ্রুবক OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ফাঁকা;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ফাঁকা;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    অক্ষর *platform_name_src = ফাঁকা,
         *device_name_src   = ফাঁকা;
    পূর্ণসংখ্যা err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    যদি (err)
        ফেরত err;

    found = 0;
    জন্য (p = 0; p < nb_platforms; p++) {
        ধ্রুবক অক্ষর *platform_name;

        যদি (selector->platform_সূচক >= 0 &&
            selector->platform_সূচক != p)
            চালু;

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
                যাও fail;
            যদি (err > 0)
                চালু;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        যদি (err < 0)
            চালু;

        জন্য (d = 0; d < nb_devices; d++) {
            ধ্রুবক অক্ষর *device_name;

            যদি (selector->device_সূচক >= 0 &&
                selector->device_সূচক != d)
                চালু;

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
                    যাও fail;
                যদি (err > 0)
                    চালু;
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
        যাও fail;
    }
    যদি (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        যাও fail;
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
        যাও fail;
    }

    hwdev->মুক্ত = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা opencl_device_create(AVHWDeviceContext *hwdev, ধ্রুবক অক্ষর *device,
                                AVDictionary *opts, পূর্ণসংখ্যা flags)
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
        পূর্ণসংখ্যা d = -1, p = -1, ret;
        যদি (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        অন্যথা
            ret = sscanf(device, "%d.%d", &p, &d);
        যদি (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ফেরত AVERROR(EINVAL);
        }
        selector.platform_সূচক = p;
        selector.device_সূচক   = d;
    } অন্যথা {
        selector.platform_সূচক = -1;
        selector.device_সূচক   = -1;
    }

    ফেরত opencl_device_create_internal(hwdev, &selector, ফাঁকা);
}

স্থির পূর্ণসংখ্যা opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    যদি (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ফেরত AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } অন্যথা {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        যদি (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ফেরত AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          আকার(priv->platform_id), &priv->platform_id,
                          ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ফেরত AVERROR(EIO);
    }

#define CL_FUNC(name, desc) করো {                                \
        যদি (fail)                                               \
            বিরতি;                                              \
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
    } যখন (0)

#যদি HAVE_OPENCL_DRM_BEIGNET
    {
        পূর্ণসংখ্যা fail = 0;

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
        size_t props_আকার;
        cl_context_properties *props = ফাঁকা;
        VADisplay va_display;
        ধ্রুবক অক্ষর *va_ext = "cl_intel_va_api_media_sharing";
        পূর্ণসংখ্যা i, fail = 0;

        যদি (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            যাও no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ফাঁকা, &props_আকার);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            যাও no_qsv;
        }
        যদি (props_আকার == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            যাও no_qsv;
        }

        props = av_malloc(props_আকার);
        যদি (!props)
            ফেরত AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_আকার, props, ফাঁকা);
        যদি (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            যাও no_qsv;
        }

        va_display = ফাঁকা;
        জন্য (i = 0; i < (props_আকার / আকার(*props) - 1); i++) {
            যদি (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                বিরতি;
            }
        }
        যদি (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            যাও no_qsv;
        }
        যদি (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            যাও no_qsv;
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
        পূর্ণসংখ্যা fail = 0;

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
        ধ্রুবক অক্ষর *d3d11_ext = "cl_khr_d3d11_sharing";
        ধ্রুবক অক্ষর *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        পূর্ণসংখ্যা fail = 0;

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
        ধ্রুবক অক্ষর *drm_arm_ext = "cl_arm_import_memory";
        ধ্রুবক অক্ষর *image_ext   = "cl_khr_image2d_from_buffer";
        পূর্ণসংখ্যা fail = 0;

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

    ফেরত 0;
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
        priv->command_queue = ফাঁকা;
    }
}

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
স্থির পূর্ণসংখ্যা opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    ধ্রুবক অক্ষর *platform_name,
                                                    শূন্য *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    যদি (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ফেরত 1;
    } অন্যথা {
        ফেরত 0;
    }
}

স্থির পূর্ণসংখ্যা opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      ধ্রুবক অক্ষর *platform_name,
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
        ফেরত AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ফাঁকা, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ফেরত 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ফেরত AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, আকার(**devices));
    যদি (!*devices)
        ফেরত AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  ধ্রুবক অক্ষর *device_name,
                                                  শূন্য *context)
{
    ধ্রুবক অক্ষর *va_ext = "cl_intel_va_api_media_sharing";

    যদি (opencl_check_device_extension(device_id, va_ext)) {
        ফেরত 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ফেরত 1;
    }
}
#endif

#যদি HAVE_OPENCL_DXVA2
স্থির পূর্ণসংখ্যা opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ধ্রুবক অক্ষর *platform_name,
                                        শূন্য *context)
{
    ধ্রুবক অক্ষর *dx9_ext = "cl_khr_dx9_media_sharing";

    যদি (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ফেরত 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ফেরত 1;
    }
}

স্থির পূর্ণসংখ্যা opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুবক অক্ষর *platform_name,
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
        ফেরত AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (শূন্য**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ফাঁকা, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ফেরত 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ফেরত AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, আকার(**devices));
    যদি (!*devices)
        ফেরত AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (শূন্য**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}
#endif

#যদি HAVE_OPENCL_D3D11
স্থির পূর্ণসংখ্যা opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        ধ্রুবক অক্ষর *platform_name,
                                        শূন্য *context)
{
    ধ্রুবক অক্ষর *d3d11_ext = "cl_khr_d3d11_sharing";

    যদি (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ফেরত 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ফেরত 1;
    }
}

স্থির পূর্ণসংখ্যা opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুবক অক্ষর *platform_name,
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
        ফেরত AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ফাঁকা, nb_devices);
    যদি (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ফেরত 0;
    } অন্যথা যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ফেরত AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, আকার(**devices));
    যদি (!*devices)
        ফেরত AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}
#endif

#যদি HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
স্থির পূর্ণসংখ্যা opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    ধ্রুবক অক্ষর *device_name,
                                    শূন্য *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          আকার(device_type), &device_type, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ফেরত AVERROR_UNKNOWN;
    }
    যদি (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ফেরত 1;
    }

    ফেরত 0;
}
#endif

#যদি HAVE_OPENCL_DRM_ARM
স্থির পূর্ণসংখ্যা opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          ধ্রুবক অক্ষর *platform_name,
                                          শূন্য *context)
{
    ধ্রুবক অক্ষর *drm_arm_ext = "cl_arm_import_memory";

    যদি (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ফেরত 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ফেরত 1;
    }
}

স্থির পূর্ণসংখ্যা opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        ধ্রুবক অক্ষর *device_name,
                                        শূন্য *context)
{
    ধ্রুবক অক্ষর *drm_arm_ext = "cl_arm_import_memory";

    যদি (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ফেরত 0;
    } অন্যথা {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ফেরত 1;
    }
}
#endif

স্থির পূর্ণসংখ্যা opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা err;
    নির্বাচন (src_ctx->type) {

#যদি HAVE_OPENCL_DRM_BEIGNET
    ক্ষেত্র AV_HWDEVICE_TYPE_DRM:
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ফাঁকা;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            যদি (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            যদি (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_সূচক      = -1,
                    .device_সূচক        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ফাঁকা,
                };
                err = opencl_device_create_internal(hwdev, &selector, ফাঁকা);
            }
            av_dict_free(&selector_opts);
        }
        বিরতি;
#endif

#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
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
                .platform_সূচক      = -1,
                .device_সূচক        = -1,
                .context             = src_hwctx->display,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_intel_media_vaapi_platform,
                .enumerate_devices   = &opencl_enumerate_intel_media_vaapi_devices,
                .filter_device       = &opencl_filter_intel_media_vaapi_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        বিরতি;
#endif

#যদি HAVE_OPENCL_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
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
                বিরতি;
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
                    .platform_সূচক      = -1,
                    .device_সূচক        = -1,
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
        বিরতি;
#endif

#যদি HAVE_OPENCL_D3D11
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
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
                .platform_সূচক      = -1,
                .device_সূচক        = -1,
                .context             = src_hwctx->device,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_d3d11_platform,
                .enumerate_devices   = &opencl_enumerate_d3d11_devices,
                .filter_device       = &opencl_filter_gpu_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, props);
        }
        বিরতি;
#endif

#যদি HAVE_OPENCL_DRM_ARM
    ক্ষেত্র AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_সূচক      = -1,
                .device_সূচক        = -1,
                .context             = ফাঁকা,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, ফাঁকা);
        }
        বিরতি;
#endif

#যদি HAVE_OPENCL_VIDEOTOOLBOX
    ক্ষেত্র AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ফাঁকা, ফাঁকা, 0);
        বিরতি;
#endif

    পূর্বনির্ধারিত:
        err = AVERROR(ENOSYS);
        বিরতি;
    }

    ফেরত err;
}

স্থির পূর্ণসংখ্যা opencl_get_plane_format(গণনা AVPixelFormat pixfmt,
                                   পূর্ণসংখ্যা plane, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    ধ্রুবক AVPixFmtDescriptor *desc;
    ধ্রুবক AVComponentDescriptor *comp;
    পূর্ণসংখ্যা channels = 0, order = 0, depth = 0, step = 0;
    পূর্ণসংখ্যা wsub, hsub, alpha;
    পূর্ণসংখ্যা c;

    যদি (plane >= AV_অঙ্ক_তথ্য_POINTERS)
        ফেরত AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    যদি (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ফেরত AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    যদি (width & wsub - 1 || height & hsub - 1)
        ফেরত AVERROR(EINVAL);

    জন্য (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        যদি (comp->plane != plane)
            চালু;
        // The step size must be a power of two.
        যদি (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            ফেরত AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        যদি (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            ফেরত AVERROR(EINVAL);
        // The depth must not vary between components.
        যদি (depth && comp->depth != depth)
            ফেরত AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        যদি (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ফেরত AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        যদি (step && comp->step != step)
            ফেরত AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    যদি (channels == 0)
        ফেরত AVERROR(ENOENT);

    memset(image_format, 0, আকার(*image_format));
    memset(image_desc,   0, আকার(*image_desc));
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
        image_format->image_channel_তথ্য_type = CL_UNORM_INT8;
    } অন্যথা {
        যদি (depth <= 16)
            image_format->image_channel_তথ্য_type = CL_UNORM_INT16;
        অন্যথা যদি (depth == 32)
            image_format->image_channel_তথ্য_type = CL_FLOAT;
        অন্যথা
            ফেরত AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    ক্ষেত্র order: image_format->image_channel_order = type; বিরতি;
    নির্বাচন (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         ধ্রুবক শূন্য *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ফাঁকা;
    cl_int cle;
    গণনা AVPixelFormat pix_fmt;
    পূর্ণসংখ্যা err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          আকার(max_width), &max_width, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } অন্যথা {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          আকার(max_height), &max_height, ফাঁকা);
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
                                     0, ফাঁকা, &nb_image_formats);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        যাও fail;
    }
    যদি (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        যাও fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, আকার(*image_formats));
    যদি (!image_formats) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ফাঁকা);
    যদি (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        যাও fail;
    }

    pix_fmts_found = 0;
    জন্য (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        পূর্ণসংখ্যা plane, i;

        জন্য (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            যদি (err < 0)
                বিরতি;

            জন্য (i = 0; i < nb_image_formats; i++) {
                যদি (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_তথ্য_type ==
                    image_format.image_channel_তথ্য_type)
                    বিরতি;
            }
            যদি (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                বিরতি;
            }
        }
        যদি (err != AVERROR(ENOENT))
            চালু;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                আকার(*constraints->valid_sw_formats));
        যদি (err < 0)
            যাও fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, আকার(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ফেরত 0;

fail:
    av_freep(&image_formats);
    ফেরত err;
}

স্থির শূন্য opencl_pool_free(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)তথ্য;
    cl_int cle;
    পূর্ণসংখ্যা p;

    জন্য (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

স্থির AVBufferRef *opencl_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    পূর্ণসংখ্যা err, p;
    AVBufferRef *ref;

    desc = av_mallocz(আকার(*desc));
    যদি (!desc)
        ফেরত ফাঁকা;

    জন্য (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        যদি (err == AVERROR(ENOENT))
            বিরতি;
        যদি (err < 0)
            যাও fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ফাঁকা, &cle);
        যদি (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            যাও fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_বাফার_create((uint8_t*)desc, আকার(*desc),
                           &opencl_pool_free, hwfc, 0);
    যদি (!ref)
        যাও fail;

    ফেরত ref;

fail:
    জন্য (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ফেরত ফাঁকা;
}

স্থির পূর্ণসংখ্যা opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
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
        ফেরত AVERROR(EIO);
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_frames_init(AVHWFramesContext *hwfc)
{
    যদি (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_বাফার_pool_init2(আকার(cl_mem), hwfc,
                                 &opencl_pool_alloc, ফাঁকা);
        যদি (!ffhwframesctx(hwfc)->pool_internal)
            ফেরত AVERROR(ENOMEM);
    }

    ফেরত opencl_frames_init_command_queue(hwfc);
}

স্থির শূন্য opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#যদি HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    পূর্ণসংখ্যা i, p;
    জন্য (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        জন্য (p = 0; p < desc->nb_planes; p++) {
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
        priv->command_queue = ফাঁকা;
    }
}

স্থির পূর্ণসংখ্যা opencl_get_বাফার(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    পূর্ণসংখ্যা p;

    frame->buf[0] = av_বাফার_pool_get(hwfc->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->তথ্য;

    জন্য (p = 0; p < desc->nb_planes; p++)
        frame->তথ্য[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       গণনা AVHWFrameTransferDirection dir,
                                       গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, পূর্ণসংখ্যা nb_events)
{
    cl_int cle;
    পূর্ণসংখ্যা i;

    cle = clWaitForEvents(nb_events, events);
    যদি (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ফেরত AVERROR(EIO);
    }

    জন্য (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা opencl_transfer_তথ্য_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, ধ্রুবক AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_অঙ্ক_তথ্য_POINTERS];
    পূর্ণসংখ্যা err, p;

    যদি (dst->format != hwfc->sw_format)
        ফেরত AVERROR(EINVAL);

    জন্য (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err < 0) {
            যদি (err == AVERROR(ENOENT))
                err = 0;
            বিরতি;
        }

        যদি (!dst->তথ্য[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            বিরতি;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->তথ্য[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->তথ্য[p],
                                 0, ফাঁকা, &events[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            বিরতি;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ফেরত err;
}

স্থির পূর্ণসংখ্যা opencl_transfer_তথ্য_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, ধ্রুবক AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_অঙ্ক_তথ্য_POINTERS];
    পূর্ণসংখ্যা err, p;

    যদি (src->format != hwfc->sw_format)
        ফেরত AVERROR(EINVAL);

    জন্য (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err < 0) {
            যদি (err == AVERROR(ENOENT))
                err = 0;
            বিরতি;
        }

        যদি (!src->তথ্য[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            বিরতি;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->তথ্য[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->তথ্য[p],
                                  0, ফাঁকা, &events[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            বিরতি;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ফেরত err;
}

প্রকারলেখ কাঠামো OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    শূন্য *address[AV_অঙ্ক_তথ্য_POINTERS];
} OpenCLMapping;

স্থির শূন্য opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_অঙ্ক_তথ্য_POINTERS];
    পূর্ণসংখ্যা p, e;
    cl_int cle;

    জন্য (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        যদি (!map->address[p])
            বিরতি;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->তথ্য[p],
                                      map->address[p],
                                      0, ফাঁকা, &events[e]);
        যদি (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

স্থির পূর্ণসংখ্যা opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
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
    cl_event events[AV_অঙ্ক_তথ্য_POINTERS];
    পূর্ণসংখ্যা err, p;

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

    map = av_mallocz(আকার(*map));
    যদি (!map)
        ফেরত AVERROR(ENOMEM);

    জন্য (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        যদি (err == AVERROR(ENOENT))
            বিরতি;
        যদি (err < 0)
            যাও fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->তথ্য[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, ফাঁকা, 0, ফাঁকা,
                              &events[p], &cle);
        যদি (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            যাও fail;
        }

        dst->তথ্য[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->তথ্য[p], dst->তথ্য[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    যদি (err < 0)
        যাও fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    জন্য (p = 0; p < AV_অঙ্ক_তথ্য_POINTERS; p++) {
        যদি (!map->address[p])
            বিরতি;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->তথ্য[p],
                                map->address[p],
                                0, ফাঁকা, &events[p]);
    }
    যদি (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ফেরত err;
}

#যদি HAVE_OPENCL_DRM_BEIGNET

প্রকারলেখ কাঠামো DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

স্থির শূন্য opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        যদি (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

স্থির পূর্ণসংখ্যা opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, ধ্রুবক AVFrame *src,
                                       পূর্ণসংখ্যা flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    ধ্রুবক AVDRMFrameDescriptor *desc;
    cl_int cle;
    পূর্ণসংখ্যা err, i, j, p;

    desc = (ধ্রুবক AVDRMFrameDescriptor*)src->তথ্য[0];

    mapping = av_mallocz(আকার(*mapping));
    যদি (!mapping)
        ফেরত AVERROR(ENOMEM);

    p = 0;
    জন্য (i = 0; i < desc->nb_layers; i++) {
        ধ্রুবক AVDRMLayerDescriptor *layer = &desc->layers[i];
        জন্য (j = 0; j < layer->nb_planes; j++) {
            ধ্রুবক AVDRMPlaneDescriptor *plane = &layer->planes[j];
            ধ্রুবক AVDRMObjectDescriptor *object =
                &desc->objects[plane->object_সূচক];

            cl_import_image_info_intel image_info = {
                .fd        = object->fd,
                .আকার_2      = object->আকার_2,
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
                যাও fail;
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
                যাও fail;
            }

            dst->তথ্য[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    জন্য (p = 0; p < mapping->frame.nb_planes; p++) {
        যদি (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->তথ্য, 0, আকার(dst->তথ্য));
    ফেরত err;
}

#যদি HAVE_OPENCL_VAAPI_BEIGNET

স্থির পূর্ণসংখ্যা opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ধ্রুবক AVFrame *src,
                                 পূর্ণসংখ্যা flags)
{
    AVFrame *tmp;
    পূর্ণসংখ্যা err;

    tmp = av_frame_alloc();
    যদি (!tmp)
        ফেরত AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_মৌলিক;

    err = av_hwframe_map(tmp, src, flags);
    যদি (err < 0)
        যাও fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    যদি (err < 0)
        যাও fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ফেরত err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

স্থির অন্তঃরেখ cl_mem_flags opencl_mem_flags_for_mapping(পূর্ণসংখ্যা map_flags)
{
    যদি ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ফেরত CL_MEM_READ_WRITE;
    অন্যথা যদি (map_flags & AV_HWFRAME_MAP_READ)
        ফেরত CL_MEM_READ_ONLY;
    অন্যথা যদি (map_flags & AV_HWFRAME_MAP_WRITE)
        ফেরত CL_MEM_WRITE_ONLY;
    অন্যথা
        ফেরত 0;
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
    পূর্ণসংখ্যা p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    জন্য (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        যদি (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

স্থির পূর্ণসংখ্যা opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->তথ্য;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    VASurfaceID va_surface;
    cl_mem_flags cl_flags;
    cl_event event;
    cl_int cle;
    পূর্ণসংখ্যা err, p;

#যদি CONFIG_LIBMFX
    যদি (src->format == AV_PIX_FMT_QSV) {
        শূন্য *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->তথ্য[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        যদি (err < 0)
            ফেরত err;
        va_surface = *(VASurfaceID *)base_handle;
    } অন্যথা
#endif
        যদি (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->তথ্য[3];
    } অন্যথা {
        ফেরত AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        ফেরত AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(আকার(*desc));
    যদি (!desc)
        ফেরত AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    জন্য (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        যদি (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            যাও fail;
        }

        dst->তথ্য[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        যাও fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        যাও fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    জন্য (p = 0; p < desc->nb_planes; p++)
        যদি (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->তথ্য, 0, আকার(dst->তথ্য));
    ফেরত err;
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
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ফেরত;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

স্থির পূর্ণসংখ্যা opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->তথ্য;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    পূর্ণসংখ্যা err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->তথ্য[3]);

    জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
        যদি (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->তথ্য[3])
            বিরতি;
    }
    যদি (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ফেরত AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ফেরত AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        যাও fail;

    জন্য (i = 0; i < desc->nb_planes; i++)
        dst->তথ্য[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->তথ্য, 0, আকার(dst->তথ্য));
    ফেরত err;
}

স্থির পূর্ণসংখ্যা opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, পূর্ণসংখ্যা flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    পূর্ণসংখ্যা err, i, p, nb_planes;

    যদি (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ফেরত AVERROR(EINVAL);
    }
    nb_planes = 2;

    যদি (src_fc->initial_pool_আকার == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ফেরত AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        ফেরত AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  আকার(*frames_priv->mapped_frames));
    যদি (!frames_priv->mapped_frames)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ফাঁকা,
        };
        desc->nb_planes = nb_planes;
        জন্য (p = 0; p < nb_planes; p++) {
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
                যাও fail;
            }
        }
    }

    ফেরত 0;

fail:
    জন্য (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        জন্য (p = 0; p < desc->nb_planes; p++) {
            যদি (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ফেরত err;
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
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

স্থির পূর্ণসংখ্যা opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    পূর্ণসংখ্যা err, সূচক, i;

    সূচক = (intptr_t)src->তথ্য[1];
    যদি (সূচক >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", সূচক, frames_priv->nb_mapped_frames);
        ফেরত AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           সূচক);

    desc = &frames_priv->mapped_frames[সূচক];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ফেরত AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    যদি (err < 0)
        যাও fail;

    জন্য (i = 0; i < desc->nb_planes; i++)
        dst->তথ্য[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ফাঁকা, &event);
    যদি (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->তথ্য, 0, আকার(dst->তথ্য));
    ফেরত err;
}

স্থির পূর্ণসংখ্যা opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, পূর্ণসংখ্যা flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    পূর্ণসংখ্যা err, i, p, nb_planes;

    যদি (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ফেরত AVERROR(EINVAL);
    }
    nb_planes = 2;

    যদি (src_fc->initial_pool_আকার == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ফেরত AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        ফেরত AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_আকার;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  আকার(*frames_priv->mapped_frames));
    যদি (!frames_priv->mapped_frames)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        জন্য (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            যদি (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned পূর্ণসংখ্যা)subresource, cle);
                err = AVERROR(EIO);
                যাও fail;
            }
        }
    }

    ফেরত 0;

fail:
    জন্য (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        জন্য (p = 0; p < desc->nb_planes; p++) {
            যদি (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ফেরত err;
}

#endif

#যদি HAVE_OPENCL_DRM_ARM

প্রকারলেখ কাঠামো DRMARMtoOpenCLMapping {
    পূর্ণসংখ্যা nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    পূর্ণসংখ্যা nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

স্থির শূন্য opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    জন্য (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

স্থির পূর্ণসংখ্যা opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->তথ্য;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    ধ্রুবক AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ফাঁকা;
    cl_mem_flags cl_flags;
    ধ্রুবক cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    পূর্ণসংখ্যা err, i, j;

    desc = (ধ্রুবক AVDRMFrameDescriptor*)src->তথ্য[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    যদি (!cl_flags)
        ফেরত AVERROR(EINVAL);

    mapping = av_mallocz(আকার(*mapping));
    যদি (!mapping)
        ফেরত AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    জন্য (i = 0; i < desc->nb_objects; i++) {
        পূর্ণসংখ্যা fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        যদি (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].আকার_2, &cle);
        যদি (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].আকার_2, cle);
            err = AVERROR(EIO);
            যাও fail;
        }
    }

    mapping->nb_planes = 0;
    জন্য (i = 0; i < desc->nb_layers; i++) {
        ধ্রুবক AVDRMLayerDescriptor *layer = &desc->layers[i];

        জন্য (j = 0; j < layer->nb_planes; j++) {
            ধ্রুবক AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_বাফার;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_বাফার_region region;
            পূর্ণসংখ্যা p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            যদি (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                যাও fail;
            }

            region.origin = plane->offset;
            region.আকার_2   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_বাফার =
                cl_Create_Sub_বাফার(mapping->object_buffers[plane->object_সূচক],
                                  cl_flags,
                                  CL_বাফার_CREATE_TYPE_REGION,
                                  &region, &cle);
            যদি (!plane_বাফার) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                যাও fail;
            }

            image_desc.বাফার = plane_বাফার;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ফাঁকা, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_বাফার);

            যদি (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                যাও fail;
            }

            ++mapping->nb_planes;
        }
    }

    জন্য (i = 0; i < mapping->nb_planes; i++)
        dst->তথ্য[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    যদি (err < 0)
        যাও fail;

    dst->width  = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    জন্য (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    জন্য (i = 0; i < mapping->nb_objects; i++) {
        যদি (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->তথ্য, 0, আকার(dst->তথ্য));
    ফেরত err;
}

#endif

#যদি HAVE_OPENCL_VIDEOTOOLBOX

স্থির শূন্য opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

স্থির পূর্ণসংখ্যা opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    CVPixel_বাফার_Ref pixbuf = (CVPixel_বাফার_Ref) src->তথ্য[3];
    IOSurfaceRef io_surface_ref = CVPixel_বাফার_Get_IOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ফাঁকা;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    যদি (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ফেরত AVERROR_EXTERNAL;
    }

    desc = av_mallocz(আকার(*desc));
    যদি (!desc)
        ফেরত AVERROR(ENOMEM);

    জন্য (পূর্ণসংখ্যা p = 0;; p++) {
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
            বিরতি;
        যদি (err < 0)
            যাও fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        যদি (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            যাও fail;
        }
        desc->nb_planes++;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < desc->nb_planes; i++)
        dst->তথ্য[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    যদি (err < 0)
        যাও fail;

    dst->width = src->width;
    dst->height = src->height;

    ফেরত 0;

fail:
    জন্য (পূর্ণসংখ্যা i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ফেরত err;
}

#endif

স্থির পূর্ণসংখ্যা opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    যদি (hwfc->sw_format != dst->format)
        ফেরত AVERROR(ENOSYS);
    ফেরত opencl_map_frame(hwfc, dst, src, flags);
}

স্থির পূর্ণসংখ্যা opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    নির্বাচন (src->format) {
#যদি HAVE_OPENCL_DRM_BEIGNET
    ক্ষেত্র AV_PIX_FMT_DRM_মৌলিক:
        যদি (priv->beignet_drm_mapping_usable)
            ফেরত opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VAAPI_BEIGNET
    ক্ষেত্র AV_PIX_FMT_VAAPI:
        যদি (priv->beignet_drm_mapping_usable)
            ফেরত opencl_map_from_vaapi(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ক্ষেত্র AV_PIX_FMT_QSV:
    ক্ষেত্র AV_PIX_FMT_VAAPI:
        যদি (priv->qsv_mapping_usable)
            ফেরত opencl_map_from_qsv(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_DXVA2
    ক্ষেত্র AV_PIX_FMT_DXVA2_VLD:
        যদি (priv->dxva2_mapping_usable)
            ফেরত opencl_map_from_dxva2(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_D3D11
    ক্ষেত্র AV_PIX_FMT_D3D11:
        যদি (priv->d3d11_mapping_usable)
            ফেরত opencl_map_from_d3d11(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_DRM_ARM
    ক্ষেত্র AV_PIX_FMT_DRM_মৌলিক:
        যদি (priv->drm_arm_mapping_usable)
            ফেরত opencl_map_from_drm_arm(hwfc, dst, src, flags);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VIDEOTOOLBOX
    ক্ষেত্র AV_PIX_FMT_VIDEOTOOLBOX:
        ফেরত opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    ফেরত AVERROR(ENOSYS);
}

স্থির পূর্ণসংখ্যা opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, পূর্ণসংখ্যা flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    নির্বাচন (src_fc->device_ctx->type) {
#যদি HAVE_OPENCL_DRM_BEIGNET
    ক্ষেত্র AV_HWDEVICE_TYPE_DRM:
        যদি (!priv->beignet_drm_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VAAPI_BEIGNET
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        যদি (!priv->beignet_drm_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ক্ষেত্র AV_HWDEVICE_TYPE_QSV:
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        যদি (!priv->qsv_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        বিরতি;
#endif
#যদি HAVE_OPENCL_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
        যদি (!priv->dxva2_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        {
            পূর্ণসংখ্যা err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            যদি (err < 0)
                ফেরত err;
        }
        বিরতি;
#endif
#যদি HAVE_OPENCL_D3D11
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        যদি (!priv->d3d11_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        {
            পূর্ণসংখ্যা err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            যদি (err < 0)
                ফেরত err;
        }
        বিরতি;
#endif
#যদি HAVE_OPENCL_DRM_ARM
    ক্ষেত্র AV_HWDEVICE_TYPE_DRM:
        যদি (!priv->drm_arm_mapping_usable)
            ফেরত AVERROR(ENOSYS);
        বিরতি;
#endif
#যদি HAVE_OPENCL_VIDEOTOOLBOX
    ক্ষেত্র AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }
    ফেরত opencl_frames_init_command_queue(dst_fc);
}

ধ্রুবক HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_আকার      = আকার(OpenCLDeviceContext),
    .frames_hwctx_আকার      = আকার(OpenCLFramesContext),

    .device_create          = &opencl_device_create,
    .device_derive          = &opencl_device_derive,
    .device_init            = &opencl_device_init,
    .device_uninit          = &opencl_device_uninit,

    .frames_get_constraints = &opencl_frames_get_constraints,
    .frames_init            = &opencl_frames_init,
    .frames_uninit          = &opencl_frames_uninit,
    .frames_get_বাফার      = &opencl_get_বাফার,

    .transfer_get_formats   = &opencl_transfer_get_formats,
    .transfer_তথ্য_to       = &opencl_transfer_তথ্য_to,
    .transfer_তথ্য_from     = &opencl_transfer_তথ্য_from,

    .map_from               = &opencl_map_from,
    .map_to                 = &opencl_map_to,
    .frames_derive_to       = &opencl_frames_derive_to,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
