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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_opencl.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"

#എങ്കിൽ HAVE_OPENCL_VAAPI_BEIGNET
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <va/va.h>
#അന്തര്ഭാവ <va/va_drmcommon.h>
#അന്തര്ഭാവ <CL/cl_intel.h>
#അന്തര്ഭാവ "hwcontext_vaapi.h"
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <CL/cl_intel.h>
#അന്തര്ഭാവ "hwcontext_drm.h"
#endif

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#എങ്കിൽ CONFIG_LIBMFX
#അന്തര്ഭാവ <mfxstructures.h>
#endif
#അന്തര്ഭാവ <va/va.h>
#അന്തര്ഭാവ <CL/cl_va_api_media_sharing_intel.h>
#അന്തര്ഭാവ "hwcontext_vaapi.h"
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2
#define COBJMACROS
#അന്തര്ഭാവ <CL/cl_dx9_media_sharing.h>
#അന്തര്ഭാവ <dxva2api.h>
#അന്തര്ഭാവ "hwcontext_dxva2.h"
#endif

#എങ്കിൽ HAVE_OPENCL_D3D11
#അന്തര്ഭാവ <CL/cl_d3d11.h>
#അന്തര്ഭാവ "hwcontext_d3d11va.h"
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM
#അന്തര്ഭാവ <CL/cl_ext.h>
#അന്തര്ഭാവ <drm_fourcc.h>
#അന്തര്ഭാവ "hwcontext_drm.h"
#endif

#എങ്കിൽ HAVE_OPENCL_VIDEOTOOLBOX
#അന്തര്ഭാവ <OpenCL/cl_gl_ext.h>
#അന്തര്ഭാവ <VideoToolbox/VideoToolbox.h>
#endif

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
ബാഹ്യ പൂർണ്ണസംഖ്യ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          എണ്ണൽ AVHWDeviceType base_dev_typ,
                                          ശൂന്യം **base_handle);
#endif


തരനിർവചനം ഘടന OpenCLDeviceContext {
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
#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
    പൂർണ്ണസംഖ്യ beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    പൂർണ്ണസംഖ്യ qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2
    പൂർണ്ണസംഖ്യ dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#എങ്കിൽ HAVE_OPENCL_D3D11
    പൂർണ്ണസംഖ്യ d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM
    പൂർണ്ണസംഖ്യ drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

തരനിർവചനം ഘടന OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#എങ്കിൽ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    പൂർണ്ണസംഖ്യ                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


സ്ഥിതം ശൂന്യം CL_CALLBACK opencl_error_callback(സ്ഥിരം അക്ഷരം *errinfo,
                                              സ്ഥിരം ശൂന്യം *private_info,
                                              size_t cb,
                                              ശൂന്യം *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

സ്ഥിതം ശൂന്യം opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

സ്ഥിതം ഘടന {
    സ്ഥിരം അക്ഷരം *താക്കോൽ;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

സ്ഥിതം ഘടന {
    സ്ഥിരം അക്ഷരം *താക്കോൽ;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

സ്ഥിതം ഘടന {
    സ്ഥിരം അക്ഷരം *താക്കോൽ;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

സ്ഥിതം അക്ഷരം *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info താക്കോൽ)
{
    അക്ഷരം *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, താക്കോൽ, 0, ശൂന്യ, &size);
    എങ്കിൽ (cle != CL_SUCCESS)
        തിരികെ ശൂന്യ;
    str = av_malloc(size);
    എങ്കിൽ (!str)
        തിരികെ ശൂന്യ;
    cle = clGetPlatformInfo(platform_id, താക്കോൽ, size, str, &size);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_free(str);
        തിരികെ ശൂന്യ;
    }
    av_assert0(strlen(str) + 1 == size);
    തിരികെ str;
}

സ്ഥിതം അക്ഷരം *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info താക്കോൽ)
{
    അക്ഷരം *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, താക്കോൽ, 0, ശൂന്യ, &size);
    എങ്കിൽ (cle != CL_SUCCESS)
        തിരികെ ശൂന്യ;
    str = av_malloc(size);
    എങ്കിൽ (!str)
        തിരികെ ശൂന്യ;
    cle = clGetDeviceInfo(device_id, താക്കോൽ, size, str, &size);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_free(str);
        തിരികെ ശൂന്യ;
    }
    av_assert0(strlen(str) + 1== size);
    തിരികെ str;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_check_platform_extension(cl_platform_id platform_id,
                                           സ്ഥിരം അക്ഷരം *name)
{
    അക്ഷരം *str;
    പൂർണ്ണസംഖ്യ found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    എങ്കിൽ (str && strstr(str, name))
        found = 1;
    av_free(str);
    തിരികെ found;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_check_device_extension(cl_device_id device_id,
                                         സ്ഥിരം അക്ഷരം *name)
{
    അക്ഷരം *str;
    പൂർണ്ണസംഖ്യ found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    എങ്കിൽ (str && strstr(str, name))
        found = 1;
    av_free(str);
    തിരികെ found;
}

av_unused സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_check_extension(AVHWDeviceContext *hwdev,
                                            സ്ഥിരം അക്ഷരം *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    എങ്കിൽ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        തിരികെ 1;
    }

    എങ്കിൽ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        തിരികെ 1;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      ശൂന്യം *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ശൂന്യ, nb_platforms);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        തിരികെ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, വലുപ്പം(**platforms));
    എങ്കിൽ (!*platforms)
        തിരികെ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        തിരികെ AVERROR(ENODEV);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  സ്ഥിരം അക്ഷരം *platform_name,
                                  ശൂന്യം *context)
{
    AVDictionary *opts = context;
    സ്ഥിരം AVDictionaryEntry *param;
    അക്ഷരം *str;
    പൂർണ്ണസംഖ്യ i, ret = 0;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].താക്കോൽ,
                            ശൂന്യ, 0);
        എങ്കിൽ (!param)
            തുടരുക;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        എങ്കിൽ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].താക്കോൽ, platform_name);
            തിരികെ AVERROR_UNKNOWN;
        }
        എങ്കിൽ (!av_stristr(str, param->മൂല്യം)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->താക്കോൽ, str);
            ret = 1;
        }
        av_free(str);
    }

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    സ്ഥിരം അക്ഷരം *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    ശൂന്യം *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ശൂന്യ, nb_devices);
    എങ്കിൽ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        തിരികെ 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        തിരികെ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, വലുപ്പം(**devices));
    എങ്കിൽ (!*devices)
        തിരികെ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        തിരികെ AVERROR(ENODEV);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                സ്ഥിരം അക്ഷരം *device_name,
                                ശൂന്യം *context)
{
    AVDictionary *opts = context;
    സ്ഥിരം AVDictionaryEntry *param;
    അക്ഷരം *str;
    പൂർണ്ണസംഖ്യ i, ret = 0;

    param = av_dict_get(opts, "device_type", ശൂന്യ, 0);
    എങ്കിൽ (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            എങ്കിൽ (!strcmp(opencl_device_types[i].താക്കോൽ, param->മൂല്യം)) {
                match_type = opencl_device_types[i].type;
                നിർത്തുക;
            }
        }
        എങ്കിൽ (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->മൂല്യം);
            തിരികെ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              വലുപ്പം(device_type), &device_type, ശൂന്യ);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            തിരികെ AVERROR_UNKNOWN;
        }

        എങ്കിൽ (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            തിരികെ 1;
        }
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].താക്കോൽ,
                            ശൂന്യ, 0);
        എങ്കിൽ (!param)
            തുടരുക;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        എങ്കിൽ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].താക്കോൽ, device_name);
            തിരികെ AVERROR_UNKNOWN;
        }
        എങ്കിൽ (!av_stristr(str, param->മൂല്യം)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->താക്കോൽ, str);
            ret = 1;
        }
        av_free(str);
    }

    തിരികെ ret;
}

തരനിർവചനം ഘടന OpenCLDeviceSelector {
    പൂർണ്ണസംഖ്യ platform_index;
    പൂർണ്ണസംഖ്യ device_index;
    ശൂന്യം *context;
    പൂർണ്ണസംഖ്യ (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               ശൂന്യം *context);
    പൂർണ്ണസംഖ്യ (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               സ്ഥിരം അക്ഷരം *platform_name,
                               ശൂന്യം *context);
    പൂർണ്ണസംഖ്യ (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               സ്ഥിരം അക്ഷരം *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               ശൂന്യം *context);
    പൂർണ്ണസംഖ്യ (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               സ്ഥിരം അക്ഷരം *device_name,
                               ശൂന്യം *context);
} OpenCLDeviceSelector;

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         സ്ഥിരം OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ശൂന്യ;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ശൂന്യ;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    അക്ഷരം *platform_name_src = ശൂന്യ,
         *device_name_src   = ശൂന്യ;
    പൂർണ്ണസംഖ്യ err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    എങ്കിൽ (err)
        തിരികെ err;

    found = 0;
    വേണ്ടി (p = 0; p < nb_platforms; p++) {
        സ്ഥിരം അക്ഷരം *platform_name;

        എങ്കിൽ (selector->platform_index >= 0 &&
            selector->platform_index != p)
            തുടരുക;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        എങ്കിൽ (platform_name_src)
            platform_name = platform_name_src;
        അല്ലെങ്കിൽ
            platform_name = "Unknown Platform";

        എങ്കിൽ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            എങ്കിൽ (err < 0)
                പോകുക fail;
            എങ്കിൽ (err > 0)
                തുടരുക;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        എങ്കിൽ (err < 0)
            തുടരുക;

        വേണ്ടി (d = 0; d < nb_devices; d++) {
            സ്ഥിരം അക്ഷരം *device_name;

            എങ്കിൽ (selector->device_index >= 0 &&
                selector->device_index != d)
                തുടരുക;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            എങ്കിൽ (device_name_src)
                device_name = device_name_src;
            അല്ലെങ്കിൽ
                device_name = "Unknown Device";

            എങ്കിൽ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                എങ്കിൽ (err < 0)
                    പോകുക fail;
                എങ്കിൽ (err > 0)
                    തുടരുക;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    എങ്കിൽ (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        പോകുക fail;
    }
    എങ്കിൽ (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        പോകുക fail;
    }

    എങ്കിൽ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    എങ്കിൽ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        പോകുക fail;
    }

    hwdev->സ്വതന്ത്രം = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_device_create(AVHWDeviceContext *hwdev, സ്ഥിരം അക്ഷരം *device,
                                AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    എങ്കിൽ (device && device[0]) {
        // Match one or both indices for platform and device.
        പൂർണ്ണസംഖ്യ d = -1, p = -1, ret;
        എങ്കിൽ (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        അല്ലെങ്കിൽ
            ret = sscanf(device, "%d.%d", &p, &d);
        എങ്കിൽ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            തിരികെ AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } അല്ലെങ്കിൽ {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    തിരികെ opencl_device_create_internal(hwdev, &selector, ശൂന്യ);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    എങ്കിൽ (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            തിരികെ AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } അല്ലെങ്കിൽ {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        എങ്കിൽ (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            തിരികെ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          വലുപ്പം(priv->platform_id), &priv->platform_id,
                          ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        തിരികെ AVERROR(EIO);
    }

#define CL_FUNC(name, desc) ചെയ്യുക {                                \
        എങ്കിൽ (fail)                                               \
            നിർത്തുക;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        എങ്കിൽ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } അല്ലെങ്കിൽ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ആകുമ്പോൾ (0)

#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
    {
        പൂർണ്ണസംഖ്യ fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        എങ്കിൽ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } അല്ലെങ്കിൽ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = ശൂന്യ;
        VADisplay va_display;
        സ്ഥിരം അക്ഷരം *va_ext = "cl_intel_va_api_media_sharing";
        പൂർണ്ണസംഖ്യ i, fail = 0;

        എങ്കിൽ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            പോകുക no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ശൂന്യ, &props_size);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            പോകുക no_qsv;
        }
        എങ്കിൽ (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            പോകുക no_qsv;
        }

        props = av_malloc(props_size);
        എങ്കിൽ (!props)
            തിരികെ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, ശൂന്യ);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            പോകുക no_qsv;
        }

        va_display = ശൂന്യ;
        വേണ്ടി (i = 0; i < (props_size / വലുപ്പം(*props) - 1); i++) {
            എങ്കിൽ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                നിർത്തുക;
            }
        }
        എങ്കിൽ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            പോകുക no_qsv;
        }
        എങ്കിൽ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            പോകുക no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        എങ്കിൽ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } അല്ലെങ്കിൽ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2
    {
        പൂർണ്ണസംഖ്യ fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        എങ്കിൽ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } അല്ലെങ്കിൽ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#എങ്കിൽ HAVE_OPENCL_D3D11
    {
        സ്ഥിരം അക്ഷരം *d3d11_ext = "cl_khr_d3d11_sharing";
        സ്ഥിരം അക്ഷരം *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        പൂർണ്ണസംഖ്യ fail = 0;

        എങ്കിൽ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } അല്ലെങ്കിൽ എങ്കിൽ (!opencl_check_extension(hwdev, nv12_ext)) {
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

        എങ്കിൽ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } അല്ലെങ്കിൽ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM
    {
        സ്ഥിരം അക്ഷരം *drm_arm_ext = "cl_arm_import_memory";
        സ്ഥിരം അക്ഷരം *image_ext   = "cl_khr_image2d_from_buffer";
        പൂർണ്ണസംഖ്യ fail = 0;

        എങ്കിൽ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        എങ്കിൽ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        എങ്കിൽ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } അല്ലെങ്കിൽ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    എങ്കിൽ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = ശൂന്യ;
    }
}

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    സ്ഥിരം അക്ഷരം *platform_name,
                                                    ശൂന്യം *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    എങ്കിൽ (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        തിരികെ 1;
    } അല്ലെങ്കിൽ {
        തിരികെ 0;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      സ്ഥിരം അക്ഷരം *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      ശൂന്യം *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    എങ്കിൽ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ശൂന്യ, nb_devices);
    എങ്കിൽ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        തിരികെ 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        തിരികെ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, വലുപ്പം(**devices));
    എങ്കിൽ (!*devices)
        തിരികെ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  സ്ഥിരം അക്ഷരം *device_name,
                                                  ശൂന്യം *context)
{
    സ്ഥിരം അക്ഷരം *va_ext = "cl_intel_va_api_media_sharing";

    എങ്കിൽ (opencl_check_device_extension(device_id, va_ext)) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        തിരികെ 1;
    }
}
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2
സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        സ്ഥിരം അക്ഷരം *platform_name,
                                        ശൂന്യം *context)
{
    സ്ഥിരം അക്ഷരം *dx9_ext = "cl_khr_dx9_media_sharing";

    എങ്കിൽ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        തിരികെ 1;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          സ്ഥിരം അക്ഷരം *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ശൂന്യം *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    എങ്കിൽ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ശൂന്യം**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ശൂന്യ, nb_devices);
    എങ്കിൽ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        തിരികെ 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        തിരികെ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, വലുപ്പം(**devices));
    എങ്കിൽ (!*devices)
        തിരികെ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (ശൂന്യം**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}
#endif

#എങ്കിൽ HAVE_OPENCL_D3D11
സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        സ്ഥിരം അക്ഷരം *platform_name,
                                        ശൂന്യം *context)
{
    സ്ഥിരം അക്ഷരം *d3d11_ext = "cl_khr_d3d11_sharing";

    എങ്കിൽ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        തിരികെ 1;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          സ്ഥിരം അക്ഷരം *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          ശൂന്യം *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    എങ്കിൽ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ശൂന്യ, nb_devices);
    എങ്കിൽ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        തിരികെ 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        തിരികെ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, വലുപ്പം(**devices));
    എങ്കിൽ (!*devices)
        തിരികെ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    സ്ഥിരം അക്ഷരം *device_name,
                                    ശൂന്യം *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          വലുപ്പം(device_type), &device_type, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        തിരികെ AVERROR_UNKNOWN;
    }
    എങ്കിൽ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        തിരികെ 1;
    }

    തിരികെ 0;
}
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM
സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          സ്ഥിരം അക്ഷരം *platform_name,
                                          ശൂന്യം *context)
{
    സ്ഥിരം അക്ഷരം *drm_arm_ext = "cl_arm_import_memory";

    എങ്കിൽ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        തിരികെ 1;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        സ്ഥിരം അക്ഷരം *device_name,
                                        ശൂന്യം *context)
{
    സ്ഥിരം അക്ഷരം *drm_arm_ext = "cl_arm_import_memory";

    എങ്കിൽ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        തിരികെ 1;
    }
}
#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ err;
    തിരഞ്ഞെടുപ്പ് (src_ctx->type) {

#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
    അവസ്ഥ AV_HWDEVICE_TYPE_DRM:
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ശൂന്യ;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            എങ്കിൽ (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            എങ്കിൽ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ശൂന്യ,
                };
                err = opencl_device_create_internal(hwdev, &selector, ശൂന്യ);
            }
            av_dict_free(&selector_opts);
        }
        നിർത്തുക;
#endif

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
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
        നിർത്തുക;
#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            എങ്കിൽ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                നിർത്തുക;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            എങ്കിൽ (SUCCEEDED(hr)) {
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
            } അല്ലെങ്കിൽ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        നിർത്തുക;
#endif

#എങ്കിൽ HAVE_OPENCL_D3D11
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
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
        നിർത്തുക;
#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM
    അവസ്ഥ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = ശൂന്യ,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, ശൂന്യ);
        }
        നിർത്തുക;
#endif

#എങ്കിൽ HAVE_OPENCL_VIDEOTOOLBOX
    അവസ്ഥ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ശൂന്യ, ശൂന്യ, 0);
        നിർത്തുക;
#endif

    സ്ഥിരസ്ഥിതി:
        err = AVERROR(ENOSYS);
        നിർത്തുക;
    }

    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_get_plane_format(എണ്ണൽ AVPixelFormat pixfmt,
                                   പൂർണ്ണസംഖ്യ plane, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    സ്ഥിരം AVPixFmtDescriptor *desc;
    സ്ഥിരം AVComponentDescriptor *comp;
    പൂർണ്ണസംഖ്യ channels = 0, order = 0, depth = 0, step = 0;
    പൂർണ്ണസംഖ്യ wsub, hsub, alpha;
    പൂർണ്ണസംഖ്യ c;

    എങ്കിൽ (plane >= AV_അക്കം_DATA_POINTERS)
        തിരികെ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    എങ്കിൽ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        തിരികെ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    എങ്കിൽ (width & wsub - 1 || height & hsub - 1)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        എങ്കിൽ (comp->plane != plane)
            തുടരുക;
        // The step size must be a power of two.
        എങ്കിൽ (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            തിരികെ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        എങ്കിൽ (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            തിരികെ AVERROR(EINVAL);
        // The depth must not vary between components.
        എങ്കിൽ (depth && comp->depth != depth)
            തിരികെ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        എങ്കിൽ (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            തിരികെ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        എങ്കിൽ (step && comp->step != step)
            തിരികെ AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    എങ്കിൽ (channels == 0)
        തിരികെ AVERROR(ENOENT);

    memset(image_format, 0, വലുപ്പം(*image_format));
    memset(image_desc,   0, വലുപ്പം(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    എങ്കിൽ (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } അല്ലെങ്കിൽ {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    എങ്കിൽ (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        അല്ലെങ്കിൽ എങ്കിൽ (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        അല്ലെങ്കിൽ
            തിരികെ AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    അവസ്ഥ order: image_format->image_channel_order = type; നിർത്തുക;
    തിരഞ്ഞെടുപ്പ് (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         സ്ഥിരം ശൂന്യം *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ശൂന്യ;
    cl_int cle;
    എണ്ണൽ AVPixelFormat pix_fmt;
    പൂർണ്ണസംഖ്യ err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          വലുപ്പം(max_width), &max_width, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } അല്ലെങ്കിൽ {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          വലുപ്പം(max_height), &max_height, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } അല്ലെങ്കിൽ {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ശൂന്യ, &nb_image_formats);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        പോകുക fail;
    }
    എങ്കിൽ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        പോകുക fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, വലുപ്പം(*image_formats));
    എങ്കിൽ (!image_formats) {
        err = AVERROR(ENOMEM);
        പോകുക fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ശൂന്യ);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        പോകുക fail;
    }

    pix_fmts_found = 0;
    വേണ്ടി (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        പൂർണ്ണസംഖ്യ plane, i;

        വേണ്ടി (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            എങ്കിൽ (err < 0)
                നിർത്തുക;

            വേണ്ടി (i = 0; i < nb_image_formats; i++) {
                എങ്കിൽ (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    നിർത്തുക;
            }
            എങ്കിൽ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                നിർത്തുക;
            }
        }
        എങ്കിൽ (err != AVERROR(ENOENT))
            തുടരുക;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                വലുപ്പം(*constraints->valid_sw_formats));
        എങ്കിൽ (err < 0)
            പോകുക fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        പോകുക fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;

fail:
    av_freep(&image_formats);
    തിരികെ err;
}

സ്ഥിതം ശൂന്യം opencl_pool_free(ശൂന്യം *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    പൂർണ്ണസംഖ്യ p;

    വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

സ്ഥിതം AVBufferRef *opencl_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    പൂർണ്ണസംഖ്യ err, p;
    AVBufferRef *ref;

    desc = av_mallocz(വലുപ്പം(*desc));
    എങ്കിൽ (!desc)
        തിരികെ ശൂന്യ;

    വേണ്ടി (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        എങ്കിൽ (err == AVERROR(ENOENT))
            നിർത്തുക;
        എങ്കിൽ (err < 0)
            പോകുക fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ശൂന്യ, &cle);
        എങ്കിൽ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            പോകുക fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, വലുപ്പം(*desc),
                           &opencl_pool_free, hwfc, 0);
    എങ്കിൽ (!ref)
        പോകുക fail;

    തിരികെ ref;

fail:
    വേണ്ടി (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    തിരികെ ശൂന്യ;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        തിരികെ AVERROR(EIO);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_init(AVHWFramesContext *hwfc)
{
    എങ്കിൽ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(വലുപ്പം(cl_mem), hwfc,
                                 &opencl_pool_alloc, ശൂന്യ);
        എങ്കിൽ (!ffhwframesctx(hwfc)->pool_internal)
            തിരികെ AVERROR(ENOMEM);
    }

    തിരികെ opencl_frames_init_command_queue(hwfc);
}

സ്ഥിതം ശൂന്യം opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#എങ്കിൽ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    പൂർണ്ണസംഖ്യ i, p;
    വേണ്ടി (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            എങ്കിൽ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    എങ്കിൽ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    പൂർണ്ണസംഖ്യ p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    വേണ്ടി (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       എണ്ണൽ AVHWFrameTransferDirection dir,
                                       എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, പൂർണ്ണസംഖ്യ nb_events)
{
    cl_int cle;
    പൂർണ്ണസംഖ്യ i;

    cle = clWaitForEvents(nb_events, events);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        തിരികെ AVERROR(EIO);
    }

    വേണ്ടി (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_അക്കം_DATA_POINTERS];
    പൂർണ്ണസംഖ്യ err, p;

    എങ്കിൽ (dst->format != hwfc->sw_format)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        എങ്കിൽ (err < 0) {
            എങ്കിൽ (err == AVERROR(ENOENT))
                err = 0;
            നിർത്തുക;
        }

        എങ്കിൽ (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            നിർത്തുക;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, ശൂന്യ, &events[p]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            നിർത്തുക;
        }
    }

    opencl_wait_events(hwfc, events, p);

    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_അക്കം_DATA_POINTERS];
    പൂർണ്ണസംഖ്യ err, p;

    എങ്കിൽ (src->format != hwfc->sw_format)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        എങ്കിൽ (err < 0) {
            എങ്കിൽ (err == AVERROR(ENOENT))
                err = 0;
            നിർത്തുക;
        }

        എങ്കിൽ (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            നിർത്തുക;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, ശൂന്യ, &events[p]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            നിർത്തുക;
        }
    }

    opencl_wait_events(hwfc, events, p);

    തിരികെ err;
}

തരനിർവചനം ഘടന OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    ശൂന്യം *address[AV_അക്കം_DATA_POINTERS];
} OpenCLMapping;

സ്ഥിതം ശൂന്യം opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_അക്കം_DATA_POINTERS];
    പൂർണ്ണസംഖ്യ p, e;
    cl_int cle;

    വേണ്ടി (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        എങ്കിൽ (!map->address[p])
            നിർത്തുക;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, ശൂന്യ, &events[e]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
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
    cl_event events[AV_അക്കം_DATA_POINTERS];
    പൂർണ്ണസംഖ്യ err, p;

    av_assert0(hwfc->sw_format == dst->format);

    എങ്കിൽ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } അല്ലെങ്കിൽ {
        map_flags = 0;
        എങ്കിൽ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        എങ്കിൽ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(വലുപ്പം(*map));
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        എങ്കിൽ (err == AVERROR(ENOENT))
            നിർത്തുക;
        എങ്കിൽ (err < 0)
            പോകുക fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, ശൂന്യ, 0, ശൂന്യ,
                              &events[p], &cle);
        എങ്കിൽ (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            പോകുക fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    വേണ്ടി (p = 0; p < AV_അക്കം_DATA_POINTERS; p++) {
        എങ്കിൽ (!map->address[p])
            നിർത്തുക;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, ശൂന്യ, &events[p]);
    }
    എങ്കിൽ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    തിരികെ err;
}

#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET

തരനിർവചനം ഘടന DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

സ്ഥിതം ശൂന്യം opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, സ്ഥിരം AVFrame *src,
                                       പൂർണ്ണസംഖ്യ flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    സ്ഥിരം AVDRMFrameDescriptor *desc;
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, i, j, p;

    desc = (സ്ഥിരം AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(വലുപ്പം(*mapping));
    എങ്കിൽ (!mapping)
        തിരികെ AVERROR(ENOMEM);

    p = 0;
    വേണ്ടി (i = 0; i < desc->nb_layers; i++) {
        സ്ഥിരം AVDRMLayerDescriptor *layer = &desc->layers[i];
        വേണ്ടി (j = 0; j < layer->nb_planes; j++) {
            സ്ഥിരം AVDRMPlaneDescriptor *plane = &layer->planes[j];
            സ്ഥിരം AVDRMObjectDescriptor *object =
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
            എങ്കിൽ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                പോകുക fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            എങ്കിൽ (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                പോകുക fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    വേണ്ടി (p = 0; p < mapping->frame.nb_planes; p++) {
        എങ്കിൽ (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, വലുപ്പം(dst->data));
    തിരികെ err;
}

#എങ്കിൽ HAVE_OPENCL_VAAPI_BEIGNET

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, സ്ഥിരം AVFrame *src,
                                 പൂർണ്ണസംഖ്യ flags)
{
    AVFrame *tmp;
    പൂർണ്ണസംഖ്യ err;

    tmp = av_frame_alloc();
    എങ്കിൽ (!tmp)
        തിരികെ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_അഭാജ്യം;

    err = av_hwframe_map(tmp, src, flags);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    തിരികെ err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

സ്ഥിതം വരിയിൽ cl_mem_flags opencl_mem_flags_for_mapping(പൂർണ്ണസംഖ്യ map_flags)
{
    എങ്കിൽ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        തിരികെ CL_MEM_READ_WRITE;
    അല്ലെങ്കിൽ എങ്കിൽ (map_flags & AV_HWFRAME_MAP_READ)
        തിരികെ CL_MEM_READ_ONLY;
    അല്ലെങ്കിൽ എങ്കിൽ (map_flags & AV_HWFRAME_MAP_WRITE)
        തിരികെ CL_MEM_WRITE_ONLY;
    അല്ലെങ്കിൽ
        തിരികെ 0;
}

#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA

സ്ഥിതം ശൂന്യം opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    പൂർണ്ണസംഖ്യ p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        എങ്കിൽ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
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
    പൂർണ്ണസംഖ്യ err, p;

#എങ്കിൽ CONFIG_LIBMFX
    എങ്കിൽ (src->format == AV_PIX_FMT_QSV) {
        ശൂന്യം *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        എങ്കിൽ (err < 0)
            തിരികെ err;
        va_surface = *(VASurfaceID *)base_handle;
    } അല്ലെങ്കിൽ
#endif
        എങ്കിൽ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } അല്ലെങ്കിൽ {
        തിരികെ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    എങ്കിൽ (!cl_flags)
        തിരികെ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(വലുപ്പം(*desc));
    എങ്കിൽ (!desc)
        തിരികെ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        എങ്കിൽ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            പോകുക fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        പോകുക fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    വേണ്ടി (p = 0; p < desc->nb_planes; p++)
        എങ്കിൽ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, വലുപ്പം(dst->data));
    തിരികെ err;
}

#endif

#എങ്കിൽ HAVE_OPENCL_DXVA2

സ്ഥിതം ശൂന്യം opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        തിരികെ;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
        എങ്കിൽ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            നിർത്തുക;
    }
    എങ്കിൽ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        തിരികെ AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        തിരികെ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    വേണ്ടി (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, വലുപ്പം(dst->data));
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, പൂർണ്ണസംഖ്യ flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, i, p, nb_planes;

    എങ്കിൽ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        തിരികെ AVERROR(EINVAL);
    }
    nb_planes = 2;

    എങ്കിൽ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        തിരികെ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    എങ്കിൽ (!cl_flags)
        തിരികെ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  വലുപ്പം(*frames_priv->mapped_frames));
    എങ്കിൽ (!frames_priv->mapped_frames)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ശൂന്യ,
        };
        desc->nb_planes = nb_planes;
        വേണ്ടി (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            എങ്കിൽ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                പോകുക fail;
            }
        }
    }

    തിരികെ 0;

fail:
    വേണ്ടി (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
            എങ്കിൽ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    തിരികെ err;
}

#endif

#എങ്കിൽ HAVE_OPENCL_D3D11

സ്ഥിതം ശൂന്യം opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, index, i;

    index = (intptr_t)src->data[1];
    എങ്കിൽ (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        തിരികെ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        തിരികെ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    വേണ്ടി (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ശൂന്യ, &event);
    എങ്കിൽ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, വലുപ്പം(dst->data));
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, പൂർണ്ണസംഖ്യ flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, i, p, nb_planes;

    എങ്കിൽ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        തിരികെ AVERROR(EINVAL);
    }
    nb_planes = 2;

    എങ്കിൽ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        തിരികെ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    എങ്കിൽ (!cl_flags)
        തിരികെ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  വലുപ്പം(*frames_priv->mapped_frames));
    എങ്കിൽ (!frames_priv->mapped_frames)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        വേണ്ടി (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            എങ്കിൽ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned പൂർണ്ണസംഖ്യ)subresource, cle);
                err = AVERROR(EIO);
                പോകുക fail;
            }
        }
    }

    തിരികെ 0;

fail:
    വേണ്ടി (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        വേണ്ടി (p = 0; p < desc->nb_planes; p++) {
            എങ്കിൽ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    തിരികെ err;
}

#endif

#എങ്കിൽ HAVE_OPENCL_DRM_ARM

തരനിർവചനം ഘടന DRMARMtoOpenCLMapping {
    പൂർണ്ണസംഖ്യ nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    പൂർണ്ണസംഖ്യ nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

സ്ഥിതം ശൂന്യം opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    വേണ്ടി (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    സ്ഥിരം AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ശൂന്യ;
    cl_mem_flags cl_flags;
    സ്ഥിരം cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    പൂർണ്ണസംഖ്യ err, i, j;

    desc = (സ്ഥിരം AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    എങ്കിൽ (!cl_flags)
        തിരികെ AVERROR(EINVAL);

    mapping = av_mallocz(വലുപ്പം(*mapping));
    എങ്കിൽ (!mapping)
        തിരികെ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    വേണ്ടി (i = 0; i < desc->nb_objects; i++) {
        പൂർണ്ണസംഖ്യ fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        എങ്കിൽ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        എങ്കിൽ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            പോകുക fail;
        }
    }

    mapping->nb_planes = 0;
    വേണ്ടി (i = 0; i < desc->nb_layers; i++) {
        സ്ഥിരം AVDRMLayerDescriptor *layer = &desc->layers[i];

        വേണ്ടി (j = 0; j < layer->nb_planes; j++) {
            സ്ഥിരം AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            പൂർണ്ണസംഖ്യ p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            എങ്കിൽ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                പോകുക fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            എങ്കിൽ (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                പോകുക fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ശൂന്യ, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            എങ്കിൽ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                പോകുക fail;
            }

            ++mapping->nb_planes;
        }
    }

    വേണ്ടി (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width  = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    വേണ്ടി (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    വേണ്ടി (i = 0; i < mapping->nb_objects; i++) {
        എങ്കിൽ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, വലുപ്പം(dst->data));
    തിരികെ err;
}

#endif

#എങ്കിൽ HAVE_OPENCL_VIDEOTOOLBOX

സ്ഥിതം ശൂന്യം opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ശൂന്യ;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    എങ്കിൽ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        തിരികെ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(വലുപ്പം(*desc));
    എങ്കിൽ (!desc)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (പൂർണ്ണസംഖ്യ p = 0;; p++) {
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
        എങ്കിൽ (err == AVERROR(ENOENT))
            നിർത്തുക;
        എങ്കിൽ (err < 0)
            പോകുക fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        എങ്കിൽ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            പോകുക fail;
        }
        desc->nb_planes++;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    എങ്കിൽ (err < 0)
        പോകുക fail;

    dst->width = src->width;
    dst->height = src->height;

    തിരികെ 0;

fail:
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    തിരികെ err;
}

#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    എങ്കിൽ (hwfc->sw_format != dst->format)
        തിരികെ AVERROR(ENOSYS);
    തിരികെ opencl_map_frame(hwfc, dst, src, flags);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    തിരഞ്ഞെടുപ്പ് (src->format) {
#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
    അവസ്ഥ AV_PIX_FMT_DRM_അഭാജ്യം:
        എങ്കിൽ (priv->beignet_drm_mapping_usable)
            തിരികെ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VAAPI_BEIGNET
    അവസ്ഥ AV_PIX_FMT_VAAPI:
        എങ്കിൽ (priv->beignet_drm_mapping_usable)
            തിരികെ opencl_map_from_vaapi(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    അവസ്ഥ AV_PIX_FMT_QSV:
    അവസ്ഥ AV_PIX_FMT_VAAPI:
        എങ്കിൽ (priv->qsv_mapping_usable)
            തിരികെ opencl_map_from_qsv(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_DXVA2
    അവസ്ഥ AV_PIX_FMT_DXVA2_VLD:
        എങ്കിൽ (priv->dxva2_mapping_usable)
            തിരികെ opencl_map_from_dxva2(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_D3D11
    അവസ്ഥ AV_PIX_FMT_D3D11:
        എങ്കിൽ (priv->d3d11_mapping_usable)
            തിരികെ opencl_map_from_d3d11(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_DRM_ARM
    അവസ്ഥ AV_PIX_FMT_DRM_അഭാജ്യം:
        എങ്കിൽ (priv->drm_arm_mapping_usable)
            തിരികെ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VIDEOTOOLBOX
    അവസ്ഥ AV_PIX_FMT_VIDEOTOOLBOX:
        തിരികെ opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    തിരികെ AVERROR(ENOSYS);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, പൂർണ്ണസംഖ്യ flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    തിരഞ്ഞെടുപ്പ് (src_fc->device_ctx->type) {
#എങ്കിൽ HAVE_OPENCL_DRM_BEIGNET
    അവസ്ഥ AV_HWDEVICE_TYPE_DRM:
        എങ്കിൽ (!priv->beignet_drm_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VAAPI_BEIGNET
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        എങ്കിൽ (!priv->beignet_drm_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    അവസ്ഥ AV_HWDEVICE_TYPE_QSV:
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        എങ്കിൽ (!priv->qsv_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        എങ്കിൽ (!priv->dxva2_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        {
            പൂർണ്ണസംഖ്യ err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            എങ്കിൽ (err < 0)
                തിരികെ err;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_D3D11
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        എങ്കിൽ (!priv->d3d11_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        {
            പൂർണ്ണസംഖ്യ err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            എങ്കിൽ (err < 0)
                തിരികെ err;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_DRM_ARM
    അവസ്ഥ AV_HWDEVICE_TYPE_DRM:
        എങ്കിൽ (!priv->drm_arm_mapping_usable)
            തിരികെ AVERROR(ENOSYS);
        നിർത്തുക;
#endif
#എങ്കിൽ HAVE_OPENCL_VIDEOTOOLBOX
    അവസ്ഥ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(ENOSYS);
    }
    തിരികെ opencl_frames_init_command_queue(dst_fc);
}

സ്ഥിരം HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = വലുപ്പം(OpenCLDeviceContext),
    .frames_hwctx_size      = വലുപ്പം(OpenCLFramesContext),

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

    .pix_fmts = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
