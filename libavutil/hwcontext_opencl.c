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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "config.h"

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_opencl.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"

#எனில் HAVE_OPENCL_VAAPI_BEIGNET
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <va/va.h>
#அந்தர்பாவ <va/va_drmcommon.h>
#அந்தர்பாவ <CL/cl_intel.h>
#அந்தர்பாவ "hwcontext_vaapi.h"
#endif

#எனில் HAVE_OPENCL_DRM_BEIGNET
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <CL/cl_intel.h>
#அந்தர்பாவ "hwcontext_drm.h"
#endif

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
#எனில் CONFIG_LIBMFX
#அந்தர்பாவ <mfxstructures.h>
#endif
#அந்தர்பாவ <va/va.h>
#அந்தர்பாவ <CL/cl_va_api_media_sharing_intel.h>
#அந்தர்பாவ "hwcontext_vaapi.h"
#endif

#எனில் HAVE_OPENCL_DXVA2
#define COBJMACROS
#அந்தர்பாவ <CL/cl_dx9_media_sharing.h>
#அந்தர்பாவ <dxva2api.h>
#அந்தர்பாவ "hwcontext_dxva2.h"
#endif

#எனில் HAVE_OPENCL_D3D11
#அந்தர்பாவ <CL/cl_d3d11.h>
#அந்தர்பாவ "hwcontext_d3d11va.h"
#endif

#எனில் HAVE_OPENCL_DRM_ARM
#அந்தர்பாவ <CL/cl_ext.h>
#அந்தர்பாவ <drm_fourcc.h>
#அந்தர்பாவ "hwcontext_drm.h"
#endif

#எனில் HAVE_OPENCL_VIDEOTOOLBOX
#அந்தர்பாவ <OpenCL/cl_gl_ext.h>
#அந்தர்பாவ <VideoToolbox/VideoToolbox.h>
#endif

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
வெளி முழு ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          எண்ணிக்கை AVHWDeviceType base_dev_typ,
                                          வெறுமை **base_handle);
#endif


வகைவரை கட்டமைப்பு OpenCLDeviceContext {
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
#எனில் HAVE_OPENCL_DRM_BEIGNET
    முழு beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
    முழு qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#எனில் HAVE_OPENCL_DXVA2
    முழு dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#எனில் HAVE_OPENCL_D3D11
    முழு d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#எனில் HAVE_OPENCL_DRM_ARM
    முழு drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

வகைவரை கட்டமைப்பு OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#எனில் HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    முழு                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


நிலையான வெறுமை CL_CALLBACK opencl_error_callback(மாறிலி எழுத்து *errinfo,
                                              மாறிலி வெறுமை *private_info,
                                              size_t cb,
                                              வெறுமை *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

நிலையான வெறுமை opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

நிலையான கட்டமைப்பு {
    மாறிலி எழுத்து *சாவி;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

நிலையான கட்டமைப்பு {
    மாறிலி எழுத்து *சாவி;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

நிலையான கட்டமைப்பு {
    மாறிலி எழுத்து *சாவி;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

நிலையான எழுத்து *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info சாவி)
{
    எழுத்து *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, சாவி, 0, வெற்று, &size);
    எனில் (cle != CL_SUCCESS)
        திரும்பு வெற்று;
    str = av_malloc(size);
    எனில் (!str)
        திரும்பு வெற்று;
    cle = clGetPlatformInfo(platform_id, சாவி, size, str, &size);
    எனில் (cle != CL_SUCCESS) {
        av_free(str);
        திரும்பு வெற்று;
    }
    av_assert0(strlen(str) + 1 == size);
    திரும்பு str;
}

நிலையான எழுத்து *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info சாவி)
{
    எழுத்து *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, சாவி, 0, வெற்று, &size);
    எனில் (cle != CL_SUCCESS)
        திரும்பு வெற்று;
    str = av_malloc(size);
    எனில் (!str)
        திரும்பு வெற்று;
    cle = clGetDeviceInfo(device_id, சாவி, size, str, &size);
    எனில் (cle != CL_SUCCESS) {
        av_free(str);
        திரும்பு வெற்று;
    }
    av_assert0(strlen(str) + 1== size);
    திரும்பு str;
}

நிலையான முழு opencl_check_platform_extension(cl_platform_id platform_id,
                                           மாறிலி எழுத்து *name)
{
    எழுத்து *str;
    முழு found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    எனில் (str && strstr(str, name))
        found = 1;
    av_free(str);
    திரும்பு found;
}

நிலையான முழு opencl_check_device_extension(cl_device_id device_id,
                                         மாறிலி எழுத்து *name)
{
    எழுத்து *str;
    முழு found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    எனில் (str && strstr(str, name))
        found = 1;
    av_free(str);
    திரும்பு found;
}

av_unused நிலையான முழு opencl_check_extension(AVHWDeviceContext *hwdev,
                                            மாறிலி எழுத்து *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    எனில் (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        திரும்பு 1;
    }

    எனில் (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        திரும்பு 1;
    }

    திரும்பு 0;
}

நிலையான முழு opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      வெறுமை *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, வெற்று, nb_platforms);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        திரும்பு AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, அளவு(**platforms));
    எனில் (!*platforms)
        திரும்பு AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        திரும்பு AVERROR(ENODEV);
    }

    திரும்பு 0;
}

நிலையான முழு opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  மாறிலி எழுத்து *platform_name,
                                  வெறுமை *context)
{
    AVDictionary *opts = context;
    மாறிலி AVDictionaryEntry *param;
    எழுத்து *str;
    முழு i, ret = 0;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].சாவி,
                            வெற்று, 0);
        எனில் (!param)
            தொடர்;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        எனில் (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].சாவி, platform_name);
            திரும்பு AVERROR_UNKNOWN;
        }
        எனில் (!av_stristr(str, param->மதிப்பு)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->சாவி, str);
            ret = 1;
        }
        av_free(str);
    }

    திரும்பு ret;
}

நிலையான முழு opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    மாறிலி எழுத்து *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    வெறுமை *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, வெற்று, nb_devices);
    எனில் (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        திரும்பு 0;
    } இல்லையெனில் எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        திரும்பு AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, அளவு(**devices));
    எனில் (!*devices)
        திரும்பு AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        திரும்பு AVERROR(ENODEV);
    }

    திரும்பு 0;
}

நிலையான முழு opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                மாறிலி எழுத்து *device_name,
                                வெறுமை *context)
{
    AVDictionary *opts = context;
    மாறிலி AVDictionaryEntry *param;
    எழுத்து *str;
    முழு i, ret = 0;

    param = av_dict_get(opts, "device_type", வெற்று, 0);
    எனில் (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        க்கு (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            எனில் (!strcmp(opencl_device_types[i].சாவி, param->மதிப்பு)) {
                match_type = opencl_device_types[i].type;
                நிறுத்து;
            }
        }
        எனில் (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->மதிப்பு);
            திரும்பு AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              அளவு(device_type), &device_type, வெற்று);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            திரும்பு AVERROR_UNKNOWN;
        }

        எனில் (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            திரும்பு 1;
        }
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].சாவி,
                            வெற்று, 0);
        எனில் (!param)
            தொடர்;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        எனில் (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].சாவி, device_name);
            திரும்பு AVERROR_UNKNOWN;
        }
        எனில் (!av_stristr(str, param->மதிப்பு)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->சாவி, str);
            ret = 1;
        }
        av_free(str);
    }

    திரும்பு ret;
}

வகைவரை கட்டமைப்பு OpenCLDeviceSelector {
    முழு platform_index;
    முழு device_index;
    வெறுமை *context;
    முழு (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               வெறுமை *context);
    முழு (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               மாறிலி எழுத்து *platform_name,
                               வெறுமை *context);
    முழு (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               மாறிலி எழுத்து *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               வெறுமை *context);
    முழு (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               மாறிலி எழுத்து *device_name,
                               வெறுமை *context);
} OpenCLDeviceSelector;

நிலையான முழு opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         மாறிலி OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = வெற்று;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = வெற்று;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    எழுத்து *platform_name_src = வெற்று,
         *device_name_src   = வெற்று;
    முழு err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    எனில் (err)
        திரும்பு err;

    found = 0;
    க்கு (p = 0; p < nb_platforms; p++) {
        மாறிலி எழுத்து *platform_name;

        எனில் (selector->platform_index >= 0 &&
            selector->platform_index != p)
            தொடர்;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        எனில் (platform_name_src)
            platform_name = platform_name_src;
        இல்லையெனில்
            platform_name = "Unknown Platform";

        எனில் (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            எனில் (err < 0)
                செல் fail;
            எனில் (err > 0)
                தொடர்;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        எனில் (err < 0)
            தொடர்;

        க்கு (d = 0; d < nb_devices; d++) {
            மாறிலி எழுத்து *device_name;

            எனில் (selector->device_index >= 0 &&
                selector->device_index != d)
                தொடர்;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            எனில் (device_name_src)
                device_name = device_name_src;
            இல்லையெனில்
                device_name = "Unknown Device";

            எனில் (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                எனில் (err < 0)
                    செல் fail;
                எனில் (err > 0)
                    தொடர்;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    எனில் (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        செல் fail;
    }
    எனில் (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        செல் fail;
    }

    எனில் (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } இல்லையெனில் {
        எனில் (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    எனில் (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        செல் fail;
    }

    hwdev->விடுவி = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    திரும்பு err;
}

நிலையான முழு opencl_device_create(AVHWDeviceContext *hwdev, மாறிலி எழுத்து *device,
                                AVDictionary *opts, முழு flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    எனில் (device && device[0]) {
        // Match one or both indices for platform and device.
        முழு d = -1, p = -1, ret;
        எனில் (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        இல்லையெனில்
            ret = sscanf(device, "%d.%d", &p, &d);
        எனில் (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            திரும்பு AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } இல்லையெனில் {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    திரும்பு opencl_device_create_internal(hwdev, &selector, வெற்று);
}

நிலையான முழு opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    எனில் (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            திரும்பு AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } இல்லையெனில் {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        எனில் (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            திரும்பு AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          அளவு(priv->platform_id), &priv->platform_id,
                          வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        திரும்பு AVERROR(EIO);
    }

#define CL_FUNC(name, desc) செய் {                                \
        எனில் (fail)                                               \
            நிறுத்து;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        எனில் (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } இல்லையெனில் {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } போது (0)

#எனில் HAVE_OPENCL_DRM_BEIGNET
    {
        முழு fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        எனில் (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } இல்லையெனில் {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = வெற்று;
        VADisplay va_display;
        மாறிலி எழுத்து *va_ext = "cl_intel_va_api_media_sharing";
        முழு i, fail = 0;

        எனில் (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            செல் no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, வெற்று, &props_size);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            செல் no_qsv;
        }
        எனில் (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            செல் no_qsv;
        }

        props = av_malloc(props_size);
        எனில் (!props)
            திரும்பு AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, வெற்று);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            செல் no_qsv;
        }

        va_display = வெற்று;
        க்கு (i = 0; i < (props_size / அளவு(*props) - 1); i++) {
            எனில் (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                நிறுத்து;
            }
        }
        எனில் (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            செல் no_qsv;
        }
        எனில் (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            செல் no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        எனில் (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } இல்லையெனில் {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#எனில் HAVE_OPENCL_DXVA2
    {
        முழு fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        எனில் (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } இல்லையெனில் {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#எனில் HAVE_OPENCL_D3D11
    {
        மாறிலி எழுத்து *d3d11_ext = "cl_khr_d3d11_sharing";
        மாறிலி எழுத்து *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        முழு fail = 0;

        எனில் (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } இல்லையெனில் எனில் (!opencl_check_extension(hwdev, nv12_ext)) {
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

        எனில் (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } இல்லையெனில் {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#எனில் HAVE_OPENCL_DRM_ARM
    {
        மாறிலி எழுத்து *drm_arm_ext = "cl_arm_import_memory";
        மாறிலி எழுத்து *image_ext   = "cl_khr_image2d_from_buffer";
        முழு fail = 0;

        எனில் (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        எனில் (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        எனில் (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } இல்லையெனில் {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    திரும்பு 0;
}

நிலையான வெறுமை opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    எனில் (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = வெற்று;
    }
}

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
நிலையான முழு opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    மாறிலி எழுத்து *platform_name,
                                                    வெறுமை *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    எனில் (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        திரும்பு 1;
    } இல்லையெனில் {
        திரும்பு 0;
    }
}

நிலையான முழு opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      மாறிலி எழுத்து *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      வெறுமை *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    எனில் (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, வெற்று, nb_devices);
    எனில் (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        திரும்பு 0;
    } இல்லையெனில் எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        திரும்பு AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, அளவு(**devices));
    எனில் (!*devices)
        திரும்பு AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

நிலையான முழு opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  மாறிலி எழுத்து *device_name,
                                                  வெறுமை *context)
{
    மாறிலி எழுத்து *va_ext = "cl_intel_va_api_media_sharing";

    எனில் (opencl_check_device_extension(device_id, va_ext)) {
        திரும்பு 0;
    } இல்லையெனில் {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        திரும்பு 1;
    }
}
#endif

#எனில் HAVE_OPENCL_DXVA2
நிலையான முழு opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        மாறிலி எழுத்து *platform_name,
                                        வெறுமை *context)
{
    மாறிலி எழுத்து *dx9_ext = "cl_khr_dx9_media_sharing";

    எனில் (opencl_check_platform_extension(platform_id, dx9_ext)) {
        திரும்பு 0;
    } இல்லையெனில் {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        திரும்பு 1;
    }
}

நிலையான முழு opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          மாறிலி எழுத்து *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          வெறுமை *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    எனில் (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (வெறுமை**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, வெற்று, nb_devices);
    எனில் (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        திரும்பு 0;
    } இல்லையெனில் எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        திரும்பு AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, அளவு(**devices));
    எனில் (!*devices)
        திரும்பு AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (வெறுமை**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}
#endif

#எனில் HAVE_OPENCL_D3D11
நிலையான முழு opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        மாறிலி எழுத்து *platform_name,
                                        வெறுமை *context)
{
    மாறிலி எழுத்து *d3d11_ext = "cl_khr_d3d11_sharing";

    எனில் (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        திரும்பு 0;
    } இல்லையெனில் {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        திரும்பு 1;
    }
}

நிலையான முழு opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          மாறிலி எழுத்து *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          வெறுமை *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    எனில் (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, வெற்று, nb_devices);
    எனில் (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        திரும்பு 0;
    } இல்லையெனில் எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        திரும்பு AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, அளவு(**devices));
    எனில் (!*devices)
        திரும்பு AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}
#endif

#எனில் HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
நிலையான முழு opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    மாறிலி எழுத்து *device_name,
                                    வெறுமை *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          அளவு(device_type), &device_type, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        திரும்பு AVERROR_UNKNOWN;
    }
    எனில் (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        திரும்பு 1;
    }

    திரும்பு 0;
}
#endif

#எனில் HAVE_OPENCL_DRM_ARM
நிலையான முழு opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          மாறிலி எழுத்து *platform_name,
                                          வெறுமை *context)
{
    மாறிலி எழுத்து *drm_arm_ext = "cl_arm_import_memory";

    எனில் (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        திரும்பு 0;
    } இல்லையெனில் {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        திரும்பு 1;
    }
}

நிலையான முழு opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        மாறிலி எழுத்து *device_name,
                                        வெறுமை *context)
{
    மாறிலி எழுத்து *drm_arm_ext = "cl_arm_import_memory";

    எனில் (opencl_check_device_extension(device_id, drm_arm_ext)) {
        திரும்பு 0;
    } இல்லையெனில் {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        திரும்பு 1;
    }
}
#endif

நிலையான முழு opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                முழு flags)
{
    முழு err;
    தேர்வு (src_ctx->type) {

#எனில் HAVE_OPENCL_DRM_BEIGNET
    நிலை AV_HWDEVICE_TYPE_DRM:
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = வெற்று;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            எனில் (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            எனில் (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = வெற்று,
                };
                err = opencl_device_create_internal(hwdev, &selector, வெற்று);
            }
            av_dict_free(&selector_opts);
        }
        நிறுத்து;
#endif

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    நிலை AV_HWDEVICE_TYPE_VAAPI:
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
        நிறுத்து;
#endif

#எனில் HAVE_OPENCL_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            எனில் (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                நிறுத்து;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            எனில் (SUCCEEDED(hr)) {
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
            } இல்லையெனில் {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        நிறுத்து;
#endif

#எனில் HAVE_OPENCL_D3D11
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
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
        நிறுத்து;
#endif

#எனில் HAVE_OPENCL_DRM_ARM
    நிலை AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = வெற்று,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, வெற்று);
        }
        நிறுத்து;
#endif

#எனில் HAVE_OPENCL_VIDEOTOOLBOX
    நிலை AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, வெற்று, வெற்று, 0);
        நிறுத்து;
#endif

    இயல்பு:
        err = AVERROR(ENOSYS);
        நிறுத்து;
    }

    திரும்பு err;
}

நிலையான முழு opencl_get_plane_format(எண்ணிக்கை AVPixelFormat pixfmt,
                                   முழு plane, முழு width, முழு height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    மாறிலி AVPixFmtDescriptor *desc;
    மாறிலி AVComponentDescriptor *comp;
    முழு channels = 0, order = 0, depth = 0, step = 0;
    முழு wsub, hsub, alpha;
    முழு c;

    எனில் (plane >= AV_இலக்கம்_DATA_POINTERS)
        திரும்பு AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    எனில் (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        திரும்பு AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    எனில் (width & wsub - 1 || height & hsub - 1)
        திரும்பு AVERROR(EINVAL);

    க்கு (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        எனில் (comp->plane != plane)
            தொடர்;
        // The step size must be a power of two.
        எனில் (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            திரும்பு AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        எனில் (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            திரும்பு AVERROR(EINVAL);
        // The depth must not vary between components.
        எனில் (depth && comp->depth != depth)
            திரும்பு AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        எனில் (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            திரும்பு AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        எனில் (step && comp->step != step)
            திரும்பு AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    எனில் (channels == 0)
        திரும்பு AVERROR(ENOENT);

    memset(image_format, 0, அளவு(*image_format));
    memset(image_desc,   0, அளவு(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    எனில் (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } இல்லையெனில் {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    எனில் (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } இல்லையெனில் {
        எனில் (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        இல்லையெனில் எனில் (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        இல்லையெனில்
            திரும்பு AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    நிலை order: image_format->image_channel_order = type; நிறுத்து;
    தேர்வு (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    திரும்பு 0;
}

நிலையான முழு opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         மாறிலி வெறுமை *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = வெற்று;
    cl_int cle;
    எண்ணிக்கை AVPixelFormat pix_fmt;
    முழு err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          அளவு(max_width), &max_width, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } இல்லையெனில் {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          அளவு(max_height), &max_height, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } இல்லையெனில் {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, வெற்று, &nb_image_formats);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        செல் fail;
    }
    எனில் (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        செல் fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, அளவு(*image_formats));
    எனில் (!image_formats) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, வெற்று);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        செல் fail;
    }

    pix_fmts_found = 0;
    க்கு (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        முழு plane, i;

        க்கு (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            எனில் (err < 0)
                நிறுத்து;

            க்கு (i = 0; i < nb_image_formats; i++) {
                எனில் (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    நிறுத்து;
            }
            எனில் (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                நிறுத்து;
            }
        }
        எனில் (err != AVERROR(ENOENT))
            தொடர்;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                அளவு(*constraints->valid_sw_formats));
        எனில் (err < 0)
            செல் fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
    எனில் (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        செல் fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    திரும்பு 0;

fail:
    av_freep(&image_formats);
    திரும்பு err;
}

நிலையான வெறுமை opencl_pool_free(வெறுமை *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    முழு p;

    க்கு (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

நிலையான AVBufferRef *opencl_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    முழு err, p;
    AVBufferRef *ref;

    desc = av_mallocz(அளவு(*desc));
    எனில் (!desc)
        திரும்பு வெற்று;

    க்கு (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        எனில் (err == AVERROR(ENOENT))
            நிறுத்து;
        எனில் (err < 0)
            செல் fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, வெற்று, &cle);
        எனில் (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            செல் fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, அளவு(*desc),
                           &opencl_pool_free, hwfc, 0);
    எனில் (!ref)
        செல் fail;

    திரும்பு ref;

fail:
    க்கு (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    திரும்பு வெற்று;
}

நிலையான முழு opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        திரும்பு AVERROR(EIO);
    }

    திரும்பு 0;
}

நிலையான முழு opencl_frames_init(AVHWFramesContext *hwfc)
{
    எனில் (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(அளவு(cl_mem), hwfc,
                                 &opencl_pool_alloc, வெற்று);
        எனில் (!ffhwframesctx(hwfc)->pool_internal)
            திரும்பு AVERROR(ENOMEM);
    }

    திரும்பு opencl_frames_init_command_queue(hwfc);
}

நிலையான வெறுமை opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#எனில் HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    முழு i, p;
    க்கு (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        க்கு (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            எனில் (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    எனில் (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = வெற்று;
    }
}

நிலையான முழு opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    முழு p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    க்கு (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    திரும்பு 0;
}

நிலையான முழு opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       எண்ணிக்கை AVHWFrameTransferDirection dir,
                                       எண்ணிக்கை AVPixelFormat **formats)
{
    எண்ணிக்கை AVPixelFormat *fmts;

    fmts = av_malloc_array(2, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    திரும்பு 0;
}

நிலையான முழு opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, முழு nb_events)
{
    cl_int cle;
    முழு i;

    cle = clWaitForEvents(nb_events, events);
    எனில் (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        திரும்பு AVERROR(EIO);
    }

    க்கு (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    திரும்பு 0;
}

நிலையான முழு opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, மாறிலி AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_இலக்கம்_DATA_POINTERS];
    முழு err, p;

    எனில் (dst->format != hwfc->sw_format)
        திரும்பு AVERROR(EINVAL);

    க்கு (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        எனில் (err < 0) {
            எனில் (err == AVERROR(ENOENT))
                err = 0;
            நிறுத்து;
        }

        எனில் (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            நிறுத்து;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, வெற்று, &events[p]);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            நிறுத்து;
        }
    }

    opencl_wait_events(hwfc, events, p);

    திரும்பு err;
}

நிலையான முழு opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, மாறிலி AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_இலக்கம்_DATA_POINTERS];
    முழு err, p;

    எனில் (src->format != hwfc->sw_format)
        திரும்பு AVERROR(EINVAL);

    க்கு (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        எனில் (err < 0) {
            எனில் (err == AVERROR(ENOENT))
                err = 0;
            நிறுத்து;
        }

        எனில் (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            நிறுத்து;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, வெற்று, &events[p]);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            நிறுத்து;
        }
    }

    opencl_wait_events(hwfc, events, p);

    திரும்பு err;
}

வகைவரை கட்டமைப்பு OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    வெறுமை *address[AV_இலக்கம்_DATA_POINTERS];
} OpenCLMapping;

நிலையான வெறுமை opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_இலக்கம்_DATA_POINTERS];
    முழு p, e;
    cl_int cle;

    க்கு (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        எனில் (!map->address[p])
            நிறுத்து;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, வெற்று, &events[e]);
        எனில் (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

நிலையான முழு opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            மாறிலி AVFrame *src, முழு flags)
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
    cl_event events[AV_இலக்கம்_DATA_POINTERS];
    முழு err, p;

    av_assert0(hwfc->sw_format == dst->format);

    எனில் (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } இல்லையெனில் {
        map_flags = 0;
        எனில் (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        எனில் (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(அளவு(*map));
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);

    க்கு (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        எனில் (err == AVERROR(ENOENT))
            நிறுத்து;
        எனில் (err < 0)
            செல் fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, வெற்று, 0, வெற்று,
                              &events[p], &cle);
        எனில் (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            செல் fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    எனில் (err < 0)
        செல் fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    க்கு (p = 0; p < AV_இலக்கம்_DATA_POINTERS; p++) {
        எனில் (!map->address[p])
            நிறுத்து;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, வெற்று, &events[p]);
    }
    எனில் (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    திரும்பு err;
}

#எனில் HAVE_OPENCL_DRM_BEIGNET

வகைவரை கட்டமைப்பு DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

நிலையான வெறுமை opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    முழு i;

    க்கு (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        எனில் (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

நிலையான முழு opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, மாறிலி AVFrame *src,
                                       முழு flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    மாறிலி AVDRMFrameDescriptor *desc;
    cl_int cle;
    முழு err, i, j, p;

    desc = (மாறிலி AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(அளவு(*mapping));
    எனில் (!mapping)
        திரும்பு AVERROR(ENOMEM);

    p = 0;
    க்கு (i = 0; i < desc->nb_layers; i++) {
        மாறிலி AVDRMLayerDescriptor *layer = &desc->layers[i];
        க்கு (j = 0; j < layer->nb_planes; j++) {
            மாறிலி AVDRMPlaneDescriptor *plane = &layer->planes[j];
            மாறிலி AVDRMObjectDescriptor *object =
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
            எனில் (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                செல் fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            எனில் (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                செல் fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    க்கு (p = 0; p < mapping->frame.nb_planes; p++) {
        எனில் (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, அளவு(dst->data));
    திரும்பு err;
}

#எனில் HAVE_OPENCL_VAAPI_BEIGNET

நிலையான முழு opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, மாறிலி AVFrame *src,
                                 முழு flags)
{
    AVFrame *tmp;
    முழு err;

    tmp = av_frame_alloc();
    எனில் (!tmp)
        திரும்பு AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_பகாஎண்;

    err = av_hwframe_map(tmp, src, flags);
    எனில் (err < 0)
        செல் fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    எனில் (err < 0)
        செல் fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    திரும்பு err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

நிலையான உள்வரி cl_mem_flags opencl_mem_flags_for_mapping(முழு map_flags)
{
    எனில் ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        திரும்பு CL_MEM_READ_WRITE;
    இல்லையெனில் எனில் (map_flags & AV_HWFRAME_MAP_READ)
        திரும்பு CL_MEM_READ_ONLY;
    இல்லையெனில் எனில் (map_flags & AV_HWFRAME_MAP_WRITE)
        திரும்பு CL_MEM_WRITE_ONLY;
    இல்லையெனில்
        திரும்பு 0;
}

#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA

நிலையான வெறுமை opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    முழு p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    க்கு (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        எனில் (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

நிலையான முழு opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               மாறிலி AVFrame *src, முழு flags)
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
    முழு err, p;

#எனில் CONFIG_LIBMFX
    எனில் (src->format == AV_PIX_FMT_QSV) {
        வெறுமை *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        எனில் (err < 0)
            திரும்பு err;
        va_surface = *(VASurfaceID *)base_handle;
    } இல்லையெனில்
#endif
        எனில் (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } இல்லையெனில் {
        திரும்பு AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    எனில் (!cl_flags)
        திரும்பு AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(அளவு(*desc));
    எனில் (!desc)
        திரும்பு AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    க்கு (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        எனில் (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            செல் fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        செல் fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    எனில் (err < 0)
        செல் fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    க்கு (p = 0; p < desc->nb_planes; p++)
        எனில் (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, அளவு(dst->data));
    திரும்பு err;
}

#endif

#எனில் HAVE_OPENCL_DXVA2

நிலையான வெறுமை opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        திரும்பு;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

நிலையான முழு opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 மாறிலி AVFrame *src, முழு flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    முழு err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
        எனில் (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            நிறுத்து;
    }
    எனில் (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        திரும்பு AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        திரும்பு AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    எனில் (err < 0)
        செல் fail;

    க்கு (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, அளவு(dst->data));
    திரும்பு err;
}

நிலையான முழு opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, முழு flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    முழு err, i, p, nb_planes;

    எனில் (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        திரும்பு AVERROR(EINVAL);
    }
    nb_planes = 2;

    எனில் (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        திரும்பு AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    எனில் (!cl_flags)
        திரும்பு AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  அளவு(*frames_priv->mapped_frames));
    எனில் (!frames_priv->mapped_frames)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = வெற்று,
        };
        desc->nb_planes = nb_planes;
        க்கு (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            எனில் (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                செல் fail;
            }
        }
    }

    திரும்பு 0;

fail:
    க்கு (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        க்கு (p = 0; p < desc->nb_planes; p++) {
            எனில் (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    திரும்பு err;
}

#endif

#எனில் HAVE_OPENCL_D3D11

நிலையான வெறுமை opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

நிலையான முழு opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 மாறிலி AVFrame *src, முழு flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    முழு err, index, i;

    index = (intptr_t)src->data[1];
    எனில் (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        திரும்பு AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        திரும்பு AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    எனில் (err < 0)
        செல் fail;

    க்கு (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, வெற்று, &event);
    எனில் (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, அளவு(dst->data));
    திரும்பு err;
}

நிலையான முழு opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, முழு flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    முழு err, i, p, nb_planes;

    எனில் (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        திரும்பு AVERROR(EINVAL);
    }
    nb_planes = 2;

    எனில் (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        திரும்பு AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    எனில் (!cl_flags)
        திரும்பு AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  அளவு(*frames_priv->mapped_frames));
    எனில் (!frames_priv->mapped_frames)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        க்கு (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            எனில் (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned முழு)subresource, cle);
                err = AVERROR(EIO);
                செல் fail;
            }
        }
    }

    திரும்பு 0;

fail:
    க்கு (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        க்கு (p = 0; p < desc->nb_planes; p++) {
            எனில் (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    திரும்பு err;
}

#endif

#எனில் HAVE_OPENCL_DRM_ARM

வகைவரை கட்டமைப்பு DRMARMtoOpenCLMapping {
    முழு nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    முழு nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

நிலையான வெறுமை opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    முழு i;

    க்கு (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    க்கு (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

நிலையான முழு opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   மாறிலி AVFrame *src, முழு flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    மாறிலி AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = வெற்று;
    cl_mem_flags cl_flags;
    மாறிலி cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    முழு err, i, j;

    desc = (மாறிலி AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    எனில் (!cl_flags)
        திரும்பு AVERROR(EINVAL);

    mapping = av_mallocz(அளவு(*mapping));
    எனில் (!mapping)
        திரும்பு AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    க்கு (i = 0; i < desc->nb_objects; i++) {
        முழு fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        எனில் (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        எனில் (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            செல் fail;
        }
    }

    mapping->nb_planes = 0;
    க்கு (i = 0; i < desc->nb_layers; i++) {
        மாறிலி AVDRMLayerDescriptor *layer = &desc->layers[i];

        க்கு (j = 0; j < layer->nb_planes; j++) {
            மாறிலி AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            முழு p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            எனில் (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                செல் fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            எனில் (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                செல் fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, வெற்று, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            எனில் (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                செல் fail;
            }

            ++mapping->nb_planes;
        }
    }

    க்கு (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    எனில் (err < 0)
        செல் fail;

    dst->width  = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    க்கு (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    க்கு (i = 0; i < mapping->nb_objects; i++) {
        எனில் (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, அளவு(dst->data));
    திரும்பு err;
}

#endif

#எனில் HAVE_OPENCL_VIDEOTOOLBOX

நிலையான வெறுமை opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

நிலையான முழு opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              மாறிலி AVFrame *src, முழு flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = வெற்று;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    எனில் (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        திரும்பு AVERROR_EXTERNAL;
    }

    desc = av_mallocz(அளவு(*desc));
    எனில் (!desc)
        திரும்பு AVERROR(ENOMEM);

    க்கு (முழு p = 0;; p++) {
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
        எனில் (err == AVERROR(ENOENT))
            நிறுத்து;
        எனில் (err < 0)
            செல் fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        எனில் (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            செல் fail;
        }
        desc->nb_planes++;
    }

    க்கு (முழு i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    எனில் (err < 0)
        செல் fail;

    dst->width = src->width;
    dst->height = src->height;

    திரும்பு 0;

fail:
    க்கு (முழு i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    திரும்பு err;
}

#endif

நிலையான முழு opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           மாறிலி AVFrame *src, முழு flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    எனில் (hwfc->sw_format != dst->format)
        திரும்பு AVERROR(ENOSYS);
    திரும்பு opencl_map_frame(hwfc, dst, src, flags);
}

நிலையான முழு opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         மாறிலி AVFrame *src, முழு flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    தேர்வு (src->format) {
#எனில் HAVE_OPENCL_DRM_BEIGNET
    நிலை AV_PIX_FMT_DRM_பகாஎண்:
        எனில் (priv->beignet_drm_mapping_usable)
            திரும்பு opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VAAPI_BEIGNET
    நிலை AV_PIX_FMT_VAAPI:
        எனில் (priv->beignet_drm_mapping_usable)
            திரும்பு opencl_map_from_vaapi(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
    நிலை AV_PIX_FMT_QSV:
    நிலை AV_PIX_FMT_VAAPI:
        எனில் (priv->qsv_mapping_usable)
            திரும்பு opencl_map_from_qsv(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_DXVA2
    நிலை AV_PIX_FMT_DXVA2_VLD:
        எனில் (priv->dxva2_mapping_usable)
            திரும்பு opencl_map_from_dxva2(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_D3D11
    நிலை AV_PIX_FMT_D3D11:
        எனில் (priv->d3d11_mapping_usable)
            திரும்பு opencl_map_from_d3d11(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_DRM_ARM
    நிலை AV_PIX_FMT_DRM_பகாஎண்:
        எனில் (priv->drm_arm_mapping_usable)
            திரும்பு opencl_map_from_drm_arm(hwfc, dst, src, flags);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VIDEOTOOLBOX
    நிலை AV_PIX_FMT_VIDEOTOOLBOX:
        திரும்பு opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    திரும்பு AVERROR(ENOSYS);
}

நிலையான முழு opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, முழு flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    தேர்வு (src_fc->device_ctx->type) {
#எனில் HAVE_OPENCL_DRM_BEIGNET
    நிலை AV_HWDEVICE_TYPE_DRM:
        எனில் (!priv->beignet_drm_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VAAPI_BEIGNET
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        எனில் (!priv->beignet_drm_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VAAPI_INTEL_MEDIA
    நிலை AV_HWDEVICE_TYPE_QSV:
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        எனில் (!priv->qsv_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        எனில் (!priv->dxva2_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        {
            முழு err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            எனில் (err < 0)
                திரும்பு err;
        }
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_D3D11
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        எனில் (!priv->d3d11_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        {
            முழு err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            எனில் (err < 0)
                திரும்பு err;
        }
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_DRM_ARM
    நிலை AV_HWDEVICE_TYPE_DRM:
        எனில் (!priv->drm_arm_mapping_usable)
            திரும்பு AVERROR(ENOSYS);
        நிறுத்து;
#endif
#எனில் HAVE_OPENCL_VIDEOTOOLBOX
    நிலை AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        நிறுத்து;
#endif
    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }
    திரும்பு opencl_frames_init_command_queue(dst_fc);
}

மாறிலி HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = அளவு(OpenCLDeviceContext),
    .frames_hwctx_size      = அளவு(OpenCLFramesContext),

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

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
