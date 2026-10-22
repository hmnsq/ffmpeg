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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_opencl.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"

#જો HAVE_OPENCL_VAAPI_BEIGNET
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <va/va.h>
#અન્તર્ભાવ <va/va_drmcommon.h>
#અન્તર્ભાવ <CL/cl_intel.h>
#અન્તર્ભાવ "hwcontext_vaapi.h"
#endif

#જો HAVE_OPENCL_DRM_BEIGNET
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <CL/cl_intel.h>
#અન્તર્ભાવ "hwcontext_drm.h"
#endif

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
#જો CONFIG_LIBMFX
#અન્તર્ભાવ <mfxstructures.h>
#endif
#અન્તર્ભાવ <va/va.h>
#અન્તર્ભાવ <CL/cl_va_api_media_sharing_intel.h>
#અન્તર્ભાવ "hwcontext_vaapi.h"
#endif

#જો HAVE_OPENCL_DXVA2
#define COBJMACROS
#અન્તર્ભાવ <CL/cl_dx9_media_sharing.h>
#અન્તર્ભાવ <dxva2api.h>
#અન્તર્ભાવ "hwcontext_dxva2.h"
#endif

#જો HAVE_OPENCL_D3D11
#અન્તર્ભાવ <CL/cl_d3d11.h>
#અન્તર્ભાવ "hwcontext_d3d11va.h"
#endif

#જો HAVE_OPENCL_DRM_ARM
#અન્તર્ભાવ <CL/cl_ext.h>
#અન્તર્ભાવ <drm_fourcc.h>
#અન્તર્ભાવ "hwcontext_drm.h"
#endif

#જો HAVE_OPENCL_VIDEOTOOLBOX
#અન્તર્ભાવ <OpenCL/cl_gl_ext.h>
#અન્તર્ભાવ <VideoToolbox/VideoToolbox.h>
#endif

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
બાહ્ય પૂર્ણાંક ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ગણના AVHWDeviceType base_dev_typ,
                                          શૂન્ય **base_handle);
#endif


પ્રકારવ્યાખ્યા સંરચના OpenCLDeviceContext {
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
#જો HAVE_OPENCL_DRM_BEIGNET
    પૂર્ણાંક beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
    પૂર્ણાંક qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#જો HAVE_OPENCL_DXVA2
    પૂર્ણાંક dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#જો HAVE_OPENCL_D3D11
    પૂર્ણાંક d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#જો HAVE_OPENCL_DRM_ARM
    પૂર્ણાંક drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

પ્રકારવ્યાખ્યા સંરચના OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#જો HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    પૂર્ણાંક                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


સ્થિર શૂન્ય CL_CALLBACK opencl_error_callback(અચલ અક્ષર *errinfo,
                                              અચલ શૂન્ય *private_info,
                                              size_t cb,
                                              શૂન્ય *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

સ્થિર શૂન્ય opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

સ્થિર સંરચના {
    અચલ અક્ષર *ચાવી;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

સ્થિર સંરચના {
    અચલ અક્ષર *ચાવી;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

સ્થિર સંરચના {
    અચલ અક્ષર *ચાવી;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

સ્થિર અક્ષર *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info ચાવી)
{
    અક્ષર *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, ચાવી, 0, ખાલી, &size);
    જો (cle != CL_SUCCESS)
        પાછા ખાલી;
    str = av_malloc(size);
    જો (!str)
        પાછા ખાલી;
    cle = clGetPlatformInfo(platform_id, ચાવી, size, str, &size);
    જો (cle != CL_SUCCESS) {
        av_free(str);
        પાછા ખાલી;
    }
    av_assert0(strlen(str) + 1 == size);
    પાછા str;
}

સ્થિર અક્ષર *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info ચાવી)
{
    અક્ષર *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, ચાવી, 0, ખાલી, &size);
    જો (cle != CL_SUCCESS)
        પાછા ખાલી;
    str = av_malloc(size);
    જો (!str)
        પાછા ખાલી;
    cle = clGetDeviceInfo(device_id, ચાવી, size, str, &size);
    જો (cle != CL_SUCCESS) {
        av_free(str);
        પાછા ખાલી;
    }
    av_assert0(strlen(str) + 1== size);
    પાછા str;
}

સ્થિર પૂર્ણાંક opencl_check_platform_extension(cl_platform_id platform_id,
                                           અચલ અક્ષર *name)
{
    અક્ષર *str;
    પૂર્ણાંક found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    જો (str && strstr(str, name))
        found = 1;
    av_free(str);
    પાછા found;
}

સ્થિર પૂર્ણાંક opencl_check_device_extension(cl_device_id device_id,
                                         અચલ અક્ષર *name)
{
    અક્ષર *str;
    પૂર્ણાંક found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    જો (str && strstr(str, name))
        found = 1;
    av_free(str);
    પાછા found;
}

av_unused સ્થિર પૂર્ણાંક opencl_check_extension(AVHWDeviceContext *hwdev,
                                            અચલ અક્ષર *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    જો (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        પાછા 1;
    }

    જો (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        પાછા 1;
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      શૂન્ય *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, ખાલી, nb_platforms);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        પાછા AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, કદ(**platforms));
    જો (!*platforms)
        પાછા AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        પાછા AVERROR(ENODEV);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  અચલ અક્ષર *platform_name,
                                  શૂન્ય *context)
{
    AVDictionary *opts = context;
    અચલ AVDictionaryEntry *param;
    અક્ષર *str;
    પૂર્ણાંક i, ret = 0;

    માટે (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].ચાવી,
                            ખાલી, 0);
        જો (!param)
            ચાલુ;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        જો (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].ચાવી, platform_name);
            પાછા AVERROR_UNKNOWN;
        }
        જો (!av_stristr(str, param->કિંમત)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ચાવી, str);
            ret = 1;
        }
        av_free(str);
    }

    પાછા ret;
}

સ્થિર પૂર્ણાંક opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    અચલ અક્ષર *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    શૂન્ય *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, ખાલી, nb_devices);
    જો (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        પાછા 0;
    } નહીંતર જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        પાછા AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, કદ(**devices));
    જો (!*devices)
        પાછા AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        પાછા AVERROR(ENODEV);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                અચલ અક્ષર *device_name,
                                શૂન્ય *context)
{
    AVDictionary *opts = context;
    અચલ AVDictionaryEntry *param;
    અક્ષર *str;
    પૂર્ણાંક i, ret = 0;

    param = av_dict_get(opts, "device_type", ખાલી, 0);
    જો (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        માટે (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            જો (!strcmp(opencl_device_types[i].ચાવી, param->કિંમત)) {
                match_type = opencl_device_types[i].type;
                તોડો;
            }
        }
        જો (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->કિંમત);
            પાછા AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              કદ(device_type), &device_type, ખાલી);
        જો (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            પાછા AVERROR_UNKNOWN;
        }

        જો (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            પાછા 1;
        }
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].ચાવી,
                            ખાલી, 0);
        જો (!param)
            ચાલુ;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        જો (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].ચાવી, device_name);
            પાછા AVERROR_UNKNOWN;
        }
        જો (!av_stristr(str, param->કિંમત)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->ચાવી, str);
            ret = 1;
        }
        av_free(str);
    }

    પાછા ret;
}

પ્રકારવ્યાખ્યા સંરચના OpenCLDeviceSelector {
    પૂર્ણાંક platform_index;
    પૂર્ણાંક device_index;
    શૂન્ય *context;
    પૂર્ણાંક (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               શૂન્ય *context);
    પૂર્ણાંક (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               અચલ અક્ષર *platform_name,
                               શૂન્ય *context);
    પૂર્ણાંક (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               અચલ અક્ષર *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               શૂન્ય *context);
    પૂર્ણાંક (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               અચલ અક્ષર *device_name,
                               શૂન્ય *context);
} OpenCLDeviceSelector;

સ્થિર પૂર્ણાંક opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         અચલ OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = ખાલી;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = ખાલી;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    અક્ષર *platform_name_src = ખાલી,
         *device_name_src   = ખાલી;
    પૂર્ણાંક err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    જો (err)
        પાછા err;

    found = 0;
    માટે (p = 0; p < nb_platforms; p++) {
        અચલ અક્ષર *platform_name;

        જો (selector->platform_index >= 0 &&
            selector->platform_index != p)
            ચાલુ;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        જો (platform_name_src)
            platform_name = platform_name_src;
        નહીંતર
            platform_name = "Unknown Platform";

        જો (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            જો (err < 0)
                જાઓ fail;
            જો (err > 0)
                ચાલુ;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        જો (err < 0)
            ચાલુ;

        માટે (d = 0; d < nb_devices; d++) {
            અચલ અક્ષર *device_name;

            જો (selector->device_index >= 0 &&
                selector->device_index != d)
                ચાલુ;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            જો (device_name_src)
                device_name = device_name_src;
            નહીંતર
                device_name = "Unknown Device";

            જો (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                જો (err < 0)
                    જાઓ fail;
                જો (err > 0)
                    ચાલુ;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    જો (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        જાઓ fail;
    }
    જો (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        જાઓ fail;
    }

    જો (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } નહીંતર {
        જો (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    જો (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        જાઓ fail;
    }

    hwdev->મુક્ત = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    પાછા err;
}

સ્થિર પૂર્ણાંક opencl_device_create(AVHWDeviceContext *hwdev, અચલ અક્ષર *device,
                                AVDictionary *opts, પૂર્ણાંક flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    જો (device && device[0]) {
        // Match one or both indices for platform and device.
        પૂર્ણાંક d = -1, p = -1, ret;
        જો (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        નહીંતર
            ret = sscanf(device, "%d.%d", &p, &d);
        જો (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            પાછા AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } નહીંતર {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    પાછા opencl_device_create_internal(hwdev, &selector, ખાલી);
}

સ્થિર પૂર્ણાંક opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    જો (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        જો (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            પાછા AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } નહીંતર {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        જો (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            પાછા AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          કદ(priv->platform_id), &priv->platform_id,
                          ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        પાછા AVERROR(EIO);
    }

#define CL_FUNC(name, desc) કરો {                                \
        જો (fail)                                               \
            તોડો;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        જો (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } નહીંતર {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } જ્યારે (0)

#જો HAVE_OPENCL_DRM_BEIGNET
    {
        પૂર્ણાંક fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        જો (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } નહીંતર {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = ખાલી;
        VADisplay va_display;
        અચલ અક્ષર *va_ext = "cl_intel_va_api_media_sharing";
        પૂર્ણાંક i, fail = 0;

        જો (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            જાઓ no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, ખાલી, &props_size);
        જો (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            જાઓ no_qsv;
        }
        જો (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            જાઓ no_qsv;
        }

        props = av_malloc(props_size);
        જો (!props)
            પાછા AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, ખાલી);
        જો (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            જાઓ no_qsv;
        }

        va_display = ખાલી;
        માટે (i = 0; i < (props_size / કદ(*props) - 1); i++) {
            જો (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                તોડો;
            }
        }
        જો (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            જાઓ no_qsv;
        }
        જો (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            જાઓ no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        જો (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } નહીંતર {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#જો HAVE_OPENCL_DXVA2
    {
        પૂર્ણાંક fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        જો (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } નહીંતર {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#જો HAVE_OPENCL_D3D11
    {
        અચલ અક્ષર *d3d11_ext = "cl_khr_d3d11_sharing";
        અચલ અક્ષર *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        પૂર્ણાંક fail = 0;

        જો (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } નહીંતર જો (!opencl_check_extension(hwdev, nv12_ext)) {
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

        જો (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } નહીંતર {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#જો HAVE_OPENCL_DRM_ARM
    {
        અચલ અક્ષર *drm_arm_ext = "cl_arm_import_memory";
        અચલ અક્ષર *image_ext   = "cl_khr_image2d_from_buffer";
        પૂર્ણાંક fail = 0;

        જો (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        જો (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        જો (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } નહીંતર {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    પાછા 0;
}

સ્થિર શૂન્ય opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    જો (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        જો (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = ખાલી;
    }
}

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
સ્થિર પૂર્ણાંક opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    અચલ અક્ષર *platform_name,
                                                    શૂન્ય *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    જો (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        પાછા 1;
    } નહીંતર {
        પાછા 0;
    }
}

સ્થિર પૂર્ણાંક opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      અચલ અક્ષર *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      શૂન્ય *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    જો (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        પાછા AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, ખાલી, nb_devices);
    જો (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        પાછા 0;
    } નહીંતર જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        પાછા AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, કદ(**devices));
    જો (!*devices)
        પાછા AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  અચલ અક્ષર *device_name,
                                                  શૂન્ય *context)
{
    અચલ અક્ષર *va_ext = "cl_intel_va_api_media_sharing";

    જો (opencl_check_device_extension(device_id, va_ext)) {
        પાછા 0;
    } નહીંતર {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        પાછા 1;
    }
}
#endif

#જો HAVE_OPENCL_DXVA2
સ્થિર પૂર્ણાંક opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        અચલ અક્ષર *platform_name,
                                        શૂન્ય *context)
{
    અચલ અક્ષર *dx9_ext = "cl_khr_dx9_media_sharing";

    જો (opencl_check_platform_extension(platform_id, dx9_ext)) {
        પાછા 0;
    } નહીંતર {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        પાછા 1;
    }
}

સ્થિર પૂર્ણાંક opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          અચલ અક્ષર *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          શૂન્ય *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    જો (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        પાછા AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (શૂન્ય**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, ખાલી, nb_devices);
    જો (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        પાછા 0;
    } નહીંતર જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        પાછા AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, કદ(**devices));
    જો (!*devices)
        પાછા AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (શૂન્ય**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}
#endif

#જો HAVE_OPENCL_D3D11
સ્થિર પૂર્ણાંક opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        અચલ અક્ષર *platform_name,
                                        શૂન્ય *context)
{
    અચલ અક્ષર *d3d11_ext = "cl_khr_d3d11_sharing";

    જો (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        પાછા 0;
    } નહીંતર {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        પાછા 1;
    }
}

સ્થિર પૂર્ણાંક opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          અચલ અક્ષર *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          શૂન્ય *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    જો (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        પાછા AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, ખાલી, nb_devices);
    જો (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        પાછા 0;
    } નહીંતર જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        પાછા AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, કદ(**devices));
    જો (!*devices)
        પાછા AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}
#endif

#જો HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
સ્થિર પૂર્ણાંક opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    અચલ અક્ષર *device_name,
                                    શૂન્ય *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          કદ(device_type), &device_type, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        પાછા AVERROR_UNKNOWN;
    }
    જો (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        પાછા 1;
    }

    પાછા 0;
}
#endif

#જો HAVE_OPENCL_DRM_ARM
સ્થિર પૂર્ણાંક opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          અચલ અક્ષર *platform_name,
                                          શૂન્ય *context)
{
    અચલ અક્ષર *drm_arm_ext = "cl_arm_import_memory";

    જો (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        પાછા 0;
    } નહીંતર {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        પાછા 1;
    }
}

સ્થિર પૂર્ણાંક opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        અચલ અક્ષર *device_name,
                                        શૂન્ય *context)
{
    અચલ અક્ષર *drm_arm_ext = "cl_arm_import_memory";

    જો (opencl_check_device_extension(device_id, drm_arm_ext)) {
        પાછા 0;
    } નહીંતર {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        પાછા 1;
    }
}
#endif

સ્થિર પૂર્ણાંક opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                પૂર્ણાંક flags)
{
    પૂર્ણાંક err;
    પસંદગી (src_ctx->type) {

#જો HAVE_OPENCL_DRM_BEIGNET
    સ્થિતિ AV_HWDEVICE_TYPE_DRM:
    સ્થિતિ AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = ખાલી;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            જો (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            જો (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = ખાલી,
                };
                err = opencl_device_create_internal(hwdev, &selector, ખાલી);
            }
            av_dict_free(&selector_opts);
        }
        તોડો;
#endif

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    સ્થિતિ AV_HWDEVICE_TYPE_VAAPI:
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
        તોડો;
#endif

#જો HAVE_OPENCL_DXVA2
    સ્થિતિ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            જો (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                તોડો;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            જો (SUCCEEDED(hr)) {
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
            } નહીંતર {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        તોડો;
#endif

#જો HAVE_OPENCL_D3D11
    સ્થિતિ AV_HWDEVICE_TYPE_D3D11VA:
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
        તોડો;
#endif

#જો HAVE_OPENCL_DRM_ARM
    સ્થિતિ AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = ખાલી,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, ખાલી);
        }
        તોડો;
#endif

#જો HAVE_OPENCL_VIDEOTOOLBOX
    સ્થિતિ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, ખાલી, ખાલી, 0);
        તોડો;
#endif

    મૂળભૂત:
        err = AVERROR(ENOSYS);
        તોડો;
    }

    પાછા err;
}

સ્થિર પૂર્ણાંક opencl_get_plane_format(ગણના AVPixelFormat pixfmt,
                                   પૂર્ણાંક plane, પૂર્ણાંક width, પૂર્ણાંક height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    અચલ AVPixFmtDescriptor *desc;
    અચલ AVComponentDescriptor *comp;
    પૂર્ણાંક channels = 0, order = 0, depth = 0, step = 0;
    પૂર્ણાંક wsub, hsub, alpha;
    પૂર્ણાંક c;

    જો (plane >= AV_અંક_DATA_POINTERS)
        પાછા AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    જો (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        પાછા AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    જો (width & wsub - 1 || height & hsub - 1)
        પાછા AVERROR(EINVAL);

    માટે (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        જો (comp->plane != plane)
            ચાલુ;
        // The step size must be a power of two.
        જો (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            પાછા AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        જો (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            પાછા AVERROR(EINVAL);
        // The depth must not vary between components.
        જો (depth && comp->depth != depth)
            પાછા AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        જો (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            પાછા AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        જો (step && comp->step != step)
            પાછા AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    જો (channels == 0)
        પાછા AVERROR(ENOENT);

    memset(image_format, 0, કદ(*image_format));
    memset(image_desc,   0, કદ(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    જો (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } નહીંતર {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    જો (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } નહીંતર {
        જો (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        નહીંતર જો (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        નહીંતર
            પાછા AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    સ્થિતિ order: image_format->image_channel_order = type; તોડો;
    પસંદગી (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         અચલ શૂન્ય *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = ખાલી;
    cl_int cle;
    ગણના AVPixelFormat pix_fmt;
    પૂર્ણાંક err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          કદ(max_width), &max_width, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } નહીંતર {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          કદ(max_height), &max_height, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } નહીંતર {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, ખાલી, &nb_image_formats);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        જાઓ fail;
    }
    જો (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        જાઓ fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, કદ(*image_formats));
    જો (!image_formats) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, ખાલી);
    જો (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        જાઓ fail;
    }

    pix_fmts_found = 0;
    માટે (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        પૂર્ણાંક plane, i;

        માટે (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            જો (err < 0)
                તોડો;

            માટે (i = 0; i < nb_image_formats; i++) {
                જો (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    તોડો;
            }
            જો (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                તોડો;
            }
        }
        જો (err != AVERROR(ENOENT))
            ચાલુ;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                કદ(*constraints->valid_sw_formats));
        જો (err < 0)
            જાઓ fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, કદ(*constraints->valid_hw_formats));
    જો (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    પાછા 0;

fail:
    av_freep(&image_formats);
    પાછા err;
}

સ્થિર શૂન્ય opencl_pool_free(શૂન્ય *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    પૂર્ણાંક p;

    માટે (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

સ્થિર AVBufferRef *opencl_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    પૂર્ણાંક err, p;
    AVBufferRef *ref;

    desc = av_mallocz(કદ(*desc));
    જો (!desc)
        પાછા ખાલી;

    માટે (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        જો (err == AVERROR(ENOENT))
            તોડો;
        જો (err < 0)
            જાઓ fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, ખાલી, &cle);
        જો (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            જાઓ fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, કદ(*desc),
                           &opencl_pool_free, hwfc, 0);
    જો (!ref)
        જાઓ fail;

    પાછા ref;

fail:
    માટે (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    પાછા ખાલી;
}

સ્થિર પૂર્ણાંક opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    જો (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        પાછા AVERROR(EIO);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_frames_init(AVHWFramesContext *hwfc)
{
    જો (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(કદ(cl_mem), hwfc,
                                 &opencl_pool_alloc, ખાલી);
        જો (!ffhwframesctx(hwfc)->pool_internal)
            પાછા AVERROR(ENOMEM);
    }

    પાછા opencl_frames_init_command_queue(hwfc);
}

સ્થિર શૂન્ય opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#જો HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    પૂર્ણાંક i, p;
    માટે (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        માટે (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            જો (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    જો (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = ખાલી;
    }
}

સ્થિર પૂર્ણાંક opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    પૂર્ણાંક p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    માટે (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ગણના AVHWFrameTransferDirection dir,
                                       ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *fmts;

    fmts = av_malloc_array(2, કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, પૂર્ણાંક nb_events)
{
    cl_int cle;
    પૂર્ણાંક i;

    cle = clWaitForEvents(nb_events, events);
    જો (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        પાછા AVERROR(EIO);
    }

    માટે (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, અચલ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_અંક_DATA_POINTERS];
    પૂર્ણાંક err, p;

    જો (dst->format != hwfc->sw_format)
        પાછા AVERROR(EINVAL);

    માટે (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        જો (err < 0) {
            જો (err == AVERROR(ENOENT))
                err = 0;
            તોડો;
        }

        જો (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            તોડો;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, ખાલી, &events[p]);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            તોડો;
        }
    }

    opencl_wait_events(hwfc, events, p);

    પાછા err;
}

સ્થિર પૂર્ણાંક opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, અચલ AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_અંક_DATA_POINTERS];
    પૂર્ણાંક err, p;

    જો (src->format != hwfc->sw_format)
        પાછા AVERROR(EINVAL);

    માટે (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        જો (err < 0) {
            જો (err == AVERROR(ENOENT))
                err = 0;
            તોડો;
        }

        જો (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            તોડો;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, ખાલી, &events[p]);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            તોડો;
        }
    }

    opencl_wait_events(hwfc, events, p);

    પાછા err;
}

પ્રકારવ્યાખ્યા સંરચના OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    શૂન્ય *address[AV_અંક_DATA_POINTERS];
} OpenCLMapping;

સ્થિર શૂન્ય opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_અંક_DATA_POINTERS];
    પૂર્ણાંક p, e;
    cl_int cle;

    માટે (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        જો (!map->address[p])
            તોડો;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, ખાલી, &events[e]);
        જો (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

સ્થિર પૂર્ણાંક opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            અચલ AVFrame *src, પૂર્ણાંક flags)
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
    cl_event events[AV_અંક_DATA_POINTERS];
    પૂર્ણાંક err, p;

    av_assert0(hwfc->sw_format == dst->format);

    જો (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } નહીંતર {
        map_flags = 0;
        જો (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        જો (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(કદ(*map));
    જો (!map)
        પાછા AVERROR(ENOMEM);

    માટે (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        જો (err == AVERROR(ENOENT))
            તોડો;
        જો (err < 0)
            જાઓ fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, ખાલી, 0, ખાલી,
                              &events[p], &cle);
        જો (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            જાઓ fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    જો (err < 0)
        જાઓ fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    માટે (p = 0; p < AV_અંક_DATA_POINTERS; p++) {
        જો (!map->address[p])
            તોડો;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, ખાલી, &events[p]);
    }
    જો (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    પાછા err;
}

#જો HAVE_OPENCL_DRM_BEIGNET

પ્રકારવ્યાખ્યા સંરચના DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

સ્થિર શૂન્ય opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    પૂર્ણાંક i;

    માટે (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        જો (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

સ્થિર પૂર્ણાંક opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, અચલ AVFrame *src,
                                       પૂર્ણાંક flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    અચલ AVDRMFrameDescriptor *desc;
    cl_int cle;
    પૂર્ણાંક err, i, j, p;

    desc = (અચલ AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(કદ(*mapping));
    જો (!mapping)
        પાછા AVERROR(ENOMEM);

    p = 0;
    માટે (i = 0; i < desc->nb_layers; i++) {
        અચલ AVDRMLayerDescriptor *layer = &desc->layers[i];
        માટે (j = 0; j < layer->nb_planes; j++) {
            અચલ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            અચલ AVDRMObjectDescriptor *object =
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
            જો (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                જાઓ fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            જો (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                જાઓ fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    માટે (p = 0; p < mapping->frame.nb_planes; p++) {
        જો (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, કદ(dst->data));
    પાછા err;
}

#જો HAVE_OPENCL_VAAPI_BEIGNET

સ્થિર પૂર્ણાંક opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, અચલ AVFrame *src,
                                 પૂર્ણાંક flags)
{
    AVFrame *tmp;
    પૂર્ણાંક err;

    tmp = av_frame_alloc();
    જો (!tmp)
        પાછા AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_અવિભાજ્ય;

    err = av_hwframe_map(tmp, src, flags);
    જો (err < 0)
        જાઓ fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    જો (err < 0)
        જાઓ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    પાછા err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

સ્થિર અંતઃરેખ cl_mem_flags opencl_mem_flags_for_mapping(પૂર્ણાંક map_flags)
{
    જો ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        પાછા CL_MEM_READ_WRITE;
    નહીંતર જો (map_flags & AV_HWFRAME_MAP_READ)
        પાછા CL_MEM_READ_ONLY;
    નહીંતર જો (map_flags & AV_HWFRAME_MAP_WRITE)
        પાછા CL_MEM_WRITE_ONLY;
    નહીંતર
        પાછા 0;
}

#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA

સ્થિર શૂન્ય opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    પૂર્ણાંક p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    માટે (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        જો (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

સ્થિર પૂર્ણાંક opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               અચલ AVFrame *src, પૂર્ણાંક flags)
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
    પૂર્ણાંક err, p;

#જો CONFIG_LIBMFX
    જો (src->format == AV_PIX_FMT_QSV) {
        શૂન્ય *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        જો (err < 0)
            પાછા err;
        va_surface = *(VASurfaceID *)base_handle;
    } નહીંતર
#endif
        જો (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } નહીંતર {
        પાછા AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    જો (!cl_flags)
        પાછા AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(કદ(*desc));
    જો (!desc)
        પાછા AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    માટે (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        જો (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            જાઓ fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        જાઓ fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    જો (err < 0)
        જાઓ fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    માટે (p = 0; p < desc->nb_planes; p++)
        જો (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, કદ(dst->data));
    પાછા err;
}

#endif

#જો HAVE_OPENCL_DXVA2

સ્થિર શૂન્ય opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        પાછા;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

સ્થિર પૂર્ણાંક opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    પૂર્ણાંક err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    માટે (i = 0; i < src_hwctx->nb_surfaces; i++) {
        જો (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            તોડો;
    }
    જો (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        પાછા AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        પાછા AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    જો (err < 0)
        જાઓ fail;

    માટે (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, કદ(dst->data));
    પાછા err;
}

સ્થિર પૂર્ણાંક opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, પૂર્ણાંક flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    પૂર્ણાંક err, i, p, nb_planes;

    જો (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        પાછા AVERROR(EINVAL);
    }
    nb_planes = 2;

    જો (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        પાછા AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    જો (!cl_flags)
        પાછા AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  કદ(*frames_priv->mapped_frames));
    જો (!frames_priv->mapped_frames)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = ખાલી,
        };
        desc->nb_planes = nb_planes;
        માટે (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            જો (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                જાઓ fail;
            }
        }
    }

    પાછા 0;

fail:
    માટે (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        માટે (p = 0; p < desc->nb_planes; p++) {
            જો (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    પાછા err;
}

#endif

#જો HAVE_OPENCL_D3D11

સ્થિર શૂન્ય opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

સ્થિર પૂર્ણાંક opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 અચલ AVFrame *src, પૂર્ણાંક flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    પૂર્ણાંક err, index, i;

    index = (intptr_t)src->data[1];
    જો (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        પાછા AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        પાછા AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    જો (err < 0)
        જાઓ fail;

    માટે (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, ખાલી, &event);
    જો (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, કદ(dst->data));
    પાછા err;
}

સ્થિર પૂર્ણાંક opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, પૂર્ણાંક flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    પૂર્ણાંક err, i, p, nb_planes;

    જો (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        પાછા AVERROR(EINVAL);
    }
    nb_planes = 2;

    જો (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        પાછા AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    જો (!cl_flags)
        પાછા AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  કદ(*frames_priv->mapped_frames));
    જો (!frames_priv->mapped_frames)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        માટે (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            જો (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned પૂર્ણાંક)subresource, cle);
                err = AVERROR(EIO);
                જાઓ fail;
            }
        }
    }

    પાછા 0;

fail:
    માટે (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        માટે (p = 0; p < desc->nb_planes; p++) {
            જો (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    પાછા err;
}

#endif

#જો HAVE_OPENCL_DRM_ARM

પ્રકારવ્યાખ્યા સંરચના DRMARMtoOpenCLMapping {
    પૂર્ણાંક nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    પૂર્ણાંક nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

સ્થિર શૂન્ય opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    પૂર્ણાંક i;

    માટે (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    માટે (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

સ્થિર પૂર્ણાંક opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    અચલ AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = ખાલી;
    cl_mem_flags cl_flags;
    અચલ cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    પૂર્ણાંક err, i, j;

    desc = (અચલ AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    જો (!cl_flags)
        પાછા AVERROR(EINVAL);

    mapping = av_mallocz(કદ(*mapping));
    જો (!mapping)
        પાછા AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    માટે (i = 0; i < desc->nb_objects; i++) {
        પૂર્ણાંક fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        જો (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        જો (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            જાઓ fail;
        }
    }

    mapping->nb_planes = 0;
    માટે (i = 0; i < desc->nb_layers; i++) {
        અચલ AVDRMLayerDescriptor *layer = &desc->layers[i];

        માટે (j = 0; j < layer->nb_planes; j++) {
            અચલ AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            પૂર્ણાંક p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            જો (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                જાઓ fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            જો (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                જાઓ fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, ખાલી, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            જો (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                જાઓ fail;
            }

            ++mapping->nb_planes;
        }
    }

    માટે (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    જો (err < 0)
        જાઓ fail;

    dst->width  = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    માટે (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    માટે (i = 0; i < mapping->nb_objects; i++) {
        જો (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, કદ(dst->data));
    પાછા err;
}

#endif

#જો HAVE_OPENCL_VIDEOTOOLBOX

સ્થિર શૂન્ય opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

સ્થિર પૂર્ણાંક opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              અચલ AVFrame *src, પૂર્ણાંક flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = ખાલી;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    જો (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        પાછા AVERROR_EXTERNAL;
    }

    desc = av_mallocz(કદ(*desc));
    જો (!desc)
        પાછા AVERROR(ENOMEM);

    માટે (પૂર્ણાંક p = 0;; p++) {
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
        જો (err == AVERROR(ENOENT))
            તોડો;
        જો (err < 0)
            જાઓ fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        જો (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            જાઓ fail;
        }
        desc->nb_planes++;
    }

    માટે (પૂર્ણાંક i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    જો (err < 0)
        જાઓ fail;

    dst->width = src->width;
    dst->height = src->height;

    પાછા 0;

fail:
    માટે (પૂર્ણાંક i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    પાછા err;
}

#endif

સ્થિર પૂર્ણાંક opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           અચલ AVFrame *src, પૂર્ણાંક flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    જો (hwfc->sw_format != dst->format)
        પાછા AVERROR(ENOSYS);
    પાછા opencl_map_frame(hwfc, dst, src, flags);
}

સ્થિર પૂર્ણાંક opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         અચલ AVFrame *src, પૂર્ણાંક flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    પસંદગી (src->format) {
#જો HAVE_OPENCL_DRM_BEIGNET
    સ્થિતિ AV_PIX_FMT_DRM_અવિભાજ્ય:
        જો (priv->beignet_drm_mapping_usable)
            પાછા opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_VAAPI_BEIGNET
    સ્થિતિ AV_PIX_FMT_VAAPI:
        જો (priv->beignet_drm_mapping_usable)
            પાછા opencl_map_from_vaapi(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
    સ્થિતિ AV_PIX_FMT_QSV:
    સ્થિતિ AV_PIX_FMT_VAAPI:
        જો (priv->qsv_mapping_usable)
            પાછા opencl_map_from_qsv(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_DXVA2
    સ્થિતિ AV_PIX_FMT_DXVA2_VLD:
        જો (priv->dxva2_mapping_usable)
            પાછા opencl_map_from_dxva2(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_D3D11
    સ્થિતિ AV_PIX_FMT_D3D11:
        જો (priv->d3d11_mapping_usable)
            પાછા opencl_map_from_d3d11(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_DRM_ARM
    સ્થિતિ AV_PIX_FMT_DRM_અવિભાજ્ય:
        જો (priv->drm_arm_mapping_usable)
            પાછા opencl_map_from_drm_arm(hwfc, dst, src, flags);
        તોડો;
#endif
#જો HAVE_OPENCL_VIDEOTOOLBOX
    સ્થિતિ AV_PIX_FMT_VIDEOTOOLBOX:
        પાછા opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    પાછા AVERROR(ENOSYS);
}

સ્થિર પૂર્ણાંક opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, પૂર્ણાંક flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    પસંદગી (src_fc->device_ctx->type) {
#જો HAVE_OPENCL_DRM_BEIGNET
    સ્થિતિ AV_HWDEVICE_TYPE_DRM:
        જો (!priv->beignet_drm_mapping_usable)
            પાછા AVERROR(ENOSYS);
        તોડો;
#endif
#જો HAVE_OPENCL_VAAPI_BEIGNET
    સ્થિતિ AV_HWDEVICE_TYPE_VAAPI:
        જો (!priv->beignet_drm_mapping_usable)
            પાછા AVERROR(ENOSYS);
        તોડો;
#endif
#જો HAVE_OPENCL_VAAPI_INTEL_MEDIA
    સ્થિતિ AV_HWDEVICE_TYPE_QSV:
    સ્થિતિ AV_HWDEVICE_TYPE_VAAPI:
        જો (!priv->qsv_mapping_usable)
            પાછા AVERROR(ENOSYS);
        તોડો;
#endif
#જો HAVE_OPENCL_DXVA2
    સ્થિતિ AV_HWDEVICE_TYPE_DXVA2:
        જો (!priv->dxva2_mapping_usable)
            પાછા AVERROR(ENOSYS);
        {
            પૂર્ણાંક err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            જો (err < 0)
                પાછા err;
        }
        તોડો;
#endif
#જો HAVE_OPENCL_D3D11
    સ્થિતિ AV_HWDEVICE_TYPE_D3D11VA:
        જો (!priv->d3d11_mapping_usable)
            પાછા AVERROR(ENOSYS);
        {
            પૂર્ણાંક err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            જો (err < 0)
                પાછા err;
        }
        તોડો;
#endif
#જો HAVE_OPENCL_DRM_ARM
    સ્થિતિ AV_HWDEVICE_TYPE_DRM:
        જો (!priv->drm_arm_mapping_usable)
            પાછા AVERROR(ENOSYS);
        તોડો;
#endif
#જો HAVE_OPENCL_VIDEOTOOLBOX
    સ્થિતિ AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        તોડો;
#endif
    મૂળભૂત:
        પાછા AVERROR(ENOSYS);
    }
    પાછા opencl_frames_init_command_queue(dst_fc);
}

અચલ HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = કદ(OpenCLDeviceContext),
    .frames_hwctx_size      = કદ(OpenCLFramesContext),

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

    .pix_fmts = (અચલ ગણના AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
