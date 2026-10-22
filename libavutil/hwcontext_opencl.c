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

#include <string.h>

#include "config.h"

#include "avassert.h"
#include "avstring.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_opencl.h"
#include "mem.h"
#include "pixdesc.h"

#ប្រសិនបើ HAVE_OPENCL_VAAPI_BEIGNET
#include <unistd.h>
#include <va/va.h>
#include <va/va_drmcommon.h>
#include <CL/cl_intel.h>
#include "hwcontext_vaapi.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
#include <unistd.h>
#include <CL/cl_intel.h>
#include "hwcontext_drm.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
#ប្រសិនបើ CONFIG_LIBMFX
#include <mfxstructures.h>
#endif
#include <va/va.h>
#include <CL/cl_va_api_media_sharing_intel.h>
#include "hwcontext_vaapi.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2
#define COBJMACROS
#include <CL/cl_dx9_media_sharing.h>
#include <dxva2api.h>
#include "hwcontext_dxva2.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11
#include <CL/cl_d3d11.h>
#include "hwcontext_d3d11va.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
#include <CL/cl_ext.h>
#include <drm_fourcc.h>
#include "hwcontext_drm.h"
#endif

#ប្រសិនបើ HAVE_OPENCL_VIDEOTOOLBOX
#include <OpenCL/cl_gl_ext.h>
#include <VideoToolbox/VideoToolbox.h>
#endif

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA && CONFIG_LIBMFX
extern ចំនួនគត់ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ga_nanaa AVHWDeviceType base_dev_typ,
                                          void **base_handle);
#endif


typedef sa_nracanaa OpenCLDeviceContext {
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
#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
    ចំនួនគត់ beignet_drm_mapping_usable;
    clCreateImageFromFdINTEL_fn clCreateImageFromFdINTEL;
#endif

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    ចំនួនគត់ qsv_mapping_usable;
    clCreateFromVA_APIMediaSurfaceINTEL_fn
        clCreateFromVA_APIMediaSurfaceINTEL;
    clEnqueueAcquireVA_APIMediaSurfacesINTEL_fn
        clEnqueueAcquireVA_APIMediaSurfacesINTEL;
    clEnqueueReleaseVA_APIMediaSurfacesINTEL_fn
        clEnqueueReleaseVA_APIMediaSurfacesINTEL;
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2
    ចំនួនគត់ dxva2_mapping_usable;
    cl_dx9_media_adapter_type_khr dx9_media_adapter_type;

    clCreateFromDX9MediaSurfaceKHR_fn
        clCreateFromDX9MediaSurfaceKHR;
    clEnqueueAcquireDX9MediaSurfacesKHR_fn
        clEnqueueAcquireDX9MediaSurfacesKHR;
    clEnqueueReleaseDX9MediaSurfacesKHR_fn
        clEnqueueReleaseDX9MediaSurfacesKHR;
#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11
    ចំនួនគត់ d3d11_mapping_usable;
    clCreateFromD3D11Texture2DKHR_fn
        clCreateFromD3D11Texture2DKHR;
    clEnqueueAcquireD3D11ObjectsKHR_fn
        clEnqueueAcquireD3D11ObjectsKHR;
    clEnqueueReleaseD3D11ObjectsKHR_fn
        clEnqueueReleaseD3D11ObjectsKHR;
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
    ចំនួនគត់ drm_arm_mapping_usable;
#endif
} OpenCLDeviceContext;

typedef sa_nracanaa OpenCLFramesContext {
    /**
     * The public AVOpenCLFramesContext. See hwcontext_opencl.h for it.
     */
    AVOpenCLFramesContext p;

    // Command queue used for transfer/mapping operations on this frames
    // context.  If the user supplies one, this is a reference to it.
    // Otherwise, it is a reference to the default command queue for the
    // device.
    cl_command_queue command_queue;

#ប្រសិនបើ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    // For mapping APIs which have separate creation and acquire/release
    // steps, this stores the OpenCL memory objects corresponding to each
    // frame.
    ចំនួនគត់                   nb_mapped_frames;
    AVOpenCLFrameDescriptor *mapped_frames;
#endif
} OpenCLFramesContext;


static void CL_CALLBACK opencl_error_callback(const var_na *errinfo,
                                              const void *private_info,
                                              size_t cb,
                                              void *user_data)
{
    AVHWDeviceContext *ctx = user_data;
    av_log(ctx, AV_LOG_ERROR, "OpenCL error: %s\n", errinfo);
}

static void opencl_device_free(AVHWDeviceContext *hwdev)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;

    cle = clReleaseContext(hwctx->context);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to release OpenCL "
               "context: %d.\n", cle);
    }
}

static sa_nracanaa {
    const var_na *key;
    cl_platform_info name;
} opencl_platform_params[] = {
    { "platform_profile",    CL_PLATFORM_PROFILE    },
    { "platform_version",    CL_PLATFORM_VERSION    },
    { "platform_name",       CL_PLATFORM_NAME       },
    { "platform_vendor",     CL_PLATFORM_VENDOR     },
    { "platform_extensions", CL_PLATFORM_EXTENSIONS },
};

static sa_nracanaa {
    const var_na *key;
    cl_device_info name;
} opencl_device_params[] = {
    { "device_name",         CL_DEVICE_NAME         },
    { "device_vendor",       CL_DEVICE_VENDOR       },
    { "driver_version",      CL_DRIVER_VERSION      },
    { "device_version",      CL_DEVICE_VERSION      },
    { "device_profile",      CL_DEVICE_PROFILE      },
    { "device_extensions",   CL_DEVICE_EXTENSIONS   },
};

static sa_nracanaa {
    const var_na *key;
    cl_device_type type;
} opencl_device_types[] = {
    { "cpu",         CL_DEVICE_TYPE_CPU         },
    { "gpu",         CL_DEVICE_TYPE_GPU         },
    { "accelerator", CL_DEVICE_TYPE_ACCELERATOR },
    { "custom",      CL_DEVICE_TYPE_CUSTOM      },
    { "default",     CL_DEVICE_TYPE_DEFAULT     },
    { "all",         CL_DEVICE_TYPE_ALL         },
};

static var_na *opencl_get_platform_string(cl_platform_id platform_id,
                                        cl_platform_info key)
{
    var_na *str;
    size_t size;
    cl_int cle;
    cle = clGetPlatformInfo(platform_id, key, 0, NULL, &size);
    ប្រសិនបើ (cle != CL_SUCCESS)
        ត្រឡប់ NULL;
    str = av_malloc(size);
    ប្រសិនបើ (!str)
        ត្រឡប់ NULL;
    cle = clGetPlatformInfo(platform_id, key, size, str, &size);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_free(str);
        ត្រឡប់ NULL;
    }
    av_assert0(strlen(str) + 1 == size);
    ត្រឡប់ str;
}

static var_na *opencl_get_device_string(cl_device_id device_id,
                                      cl_device_info key)
{
    var_na *str;
    size_t size;
    cl_int cle;
    cle = clGetDeviceInfo(device_id, key, 0, NULL, &size);
    ប្រសិនបើ (cle != CL_SUCCESS)
        ត្រឡប់ NULL;
    str = av_malloc(size);
    ប្រសិនបើ (!str)
        ត្រឡប់ NULL;
    cle = clGetDeviceInfo(device_id, key, size, str, &size);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_free(str);
        ត្រឡប់ NULL;
    }
    av_assert0(strlen(str) + 1== size);
    ត្រឡប់ str;
}

static ចំនួនគត់ opencl_check_platform_extension(cl_platform_id platform_id,
                                           const var_na *name)
{
    var_na *str;
    ចំនួនគត់ found = 0;
    str = opencl_get_platform_string(platform_id,
                                     CL_PLATFORM_EXTENSIONS);
    ប្រសិនបើ (str && strstr(str, name))
        found = 1;
    av_free(str);
    ត្រឡប់ found;
}

static ចំនួនគត់ opencl_check_device_extension(cl_device_id device_id,
                                         const var_na *name)
{
    var_na *str;
    ចំនួនគត់ found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    ប្រសិនបើ (str && strstr(str, name))
        found = 1;
    av_free(str);
    ត្រឡប់ found;
}

av_unused static ចំនួនគត់ opencl_check_extension(AVHWDeviceContext *hwdev,
                                            const var_na *name)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;

    ប្រសិនបើ (opencl_check_platform_extension(priv->platform_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as platform extension.\n", name);
        ត្រឡប់ 1;
    }

    ប្រសិនបើ (opencl_check_device_extension(hwctx->device_id, name)) {
        av_log(hwdev, AV_LOG_DEBUG,
               "%s found as device extension.\n", name);
        ត្រឡប់ 1;
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_enumerate_platforms(AVHWDeviceContext *hwdev,
                                      cl_uint *nb_platforms,
                                      cl_platform_id **platforms,
                                      void *context)
{
    cl_int cle;

    cle = clGetPlatformIDs(0, NULL, nb_platforms);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of "
               "OpenCL platforms: %d.\n", cle);
        ត្រឡប់ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL platforms found.\n",
           *nb_platforms);

    *platforms = av_malloc_array(*nb_platforms, parimaa_na(**platforms));
    ប្រសិនបើ (!*platforms)
        ត្រឡប់ AVERROR(ENOMEM);

    cle = clGetPlatformIDs(*nb_platforms, *platforms, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of OpenCL "
               "platforms: %d.\n", cle);
        av_freep(platforms);
        ត្រឡប់ AVERROR(ENODEV);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_filter_platform(AVHWDeviceContext *hwdev,
                                  cl_platform_id platform_id,
                                  const var_na *platform_name,
                                  void *context)
{
    AVDictionary *opts = context;
    const AVDictionaryEntry *param;
    var_na *str;
    ចំនួនគត់ i, ret = 0;

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(opencl_platform_params); i++) {
        param = av_dict_get(opts, opencl_platform_params[i].key,
                            NULL, 0);
        ប្រសិនបើ (!param)
            continue;

        str = opencl_get_platform_string(platform_id,
                                         opencl_platform_params[i].name);
        ប្រសិនបើ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of platform \"%s\".\n",
                   opencl_platform_params[i].key, platform_name);
            ត្រឡប់ AVERROR_UNKNOWN;
        }
        ប្រសិនបើ (!av_stristr(str, param->value)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->key, str);
            ret = 1;
        }
        av_free(str);
    }

    ត្រឡប់ ret;
}

static ចំនួនគត់ opencl_enumerate_devices(AVHWDeviceContext *hwdev,
                                    cl_platform_id platform_id,
                                    const var_na *platform_name,
                                    cl_uint *nb_devices,
                                    cl_device_id **devices,
                                    void *context)
{
    cl_int cle;

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         0, NULL, nb_devices);
    ប្រសិនបើ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ត្រឡប់ AVERROR(ENODEV);
    }
    av_log(hwdev, AV_LOG_DEBUG, "%u OpenCL devices found on "
           "platform \"%s\".\n", *nb_devices, platform_name);

    *devices = av_malloc_array(*nb_devices, parimaa_na(**devices));
    ប្រសិនបើ (!*devices)
        ត្រឡប់ AVERROR(ENOMEM);

    cle = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL,
                         *nb_devices, *devices, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ត្រឡប់ AVERROR(ENODEV);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_filter_device(AVHWDeviceContext *hwdev,
                                cl_device_id device_id,
                                const var_na *device_name,
                                void *context)
{
    AVDictionary *opts = context;
    const AVDictionaryEntry *param;
    var_na *str;
    ចំនួនគត់ i, ret = 0;

    param = av_dict_get(opts, "device_type", NULL, 0);
    ប្រសិនបើ (param) {
        cl_device_type match_type = 0, device_type;
        cl_int cle;

        សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_types); i++) {
            ប្រសិនបើ (!strcmp(opencl_device_types[i].key, param->value)) {
                match_type = opencl_device_types[i].type;
                bha_nga;
            }
        }
        ប្រសិនបើ (!match_type) {
            av_log(hwdev, AV_LOG_ERROR, "Unknown device type %s.\n",
                   param->value);
            ត្រឡប់ AVERROR(EINVAL);
        }

        cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                              parimaa_na(device_type), &device_type, NULL);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
                   "of device \"%s\".\n", device_name);
            ត្រឡប់ AVERROR_UNKNOWN;
        }

        ប្រសិនបើ (!(device_type & match_type)) {
            av_log(hwdev, AV_LOG_DEBUG, "device_type does not match.\n");
            ត្រឡប់ 1;
        }
    }

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(opencl_device_params); i++) {
        param = av_dict_get(opts, opencl_device_params[i].key,
                            NULL, 0);
        ប្រសិនបើ (!param)
            continue;

        str = opencl_get_device_string(device_id,
                                       opencl_device_params[i].name);
        ប្រសិនបើ (!str) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to query %s "
                   "of device \"%s\".\n",
                   opencl_device_params[i].key, device_name);
            ត្រឡប់ AVERROR_UNKNOWN;
        }
        ប្រសិនបើ (!av_stristr(str, param->value)) {
            av_log(hwdev, AV_LOG_DEBUG, "%s does not match (\"%s\").\n",
                   param->key, str);
            ret = 1;
        }
        av_free(str);
    }

    ត្រឡប់ ret;
}

typedef sa_nracanaa OpenCLDeviceSelector {
    ចំនួនគត់ platform_index;
    ចំនួនគត់ device_index;
    void *context;
    ចំនួនគត់ (*enumerate_platforms)(AVHWDeviceContext *hwdev,
                               cl_uint *nb_platforms,
                               cl_platform_id **platforms,
                               void *context);
    ចំនួនគត់ (*filter_platform)    (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               const var_na *platform_name,
                               void *context);
    ចំនួនគត់ (*enumerate_devices)  (AVHWDeviceContext *hwdev,
                               cl_platform_id platform_id,
                               const var_na *platform_name,
                               cl_uint *nb_devices,
                               cl_device_id **devices,
                               void *context);
    ចំនួនគត់ (*filter_device)      (AVHWDeviceContext *hwdev,
                               cl_device_id device_id,
                               const var_na *device_name,
                               void *context);
} OpenCLDeviceSelector;

static ចំនួនគត់ opencl_device_create_internal(AVHWDeviceContext *hwdev,
                                         const OpenCLDeviceSelector *selector,
                                         cl_context_properties *props)
{
    cl_uint      nb_platforms;
    cl_platform_id *platforms = NULL;
    cl_platform_id  platform_id;
    cl_uint      nb_devices;
    cl_device_id   *devices = NULL;
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_int cle;
    cl_context_properties default_props[3];
    var_na *platform_name_src = NULL,
         *device_name_src   = NULL;
    ចំនួនគត់ err, found, p, d;

    av_assert0(selector->enumerate_platforms &&
               selector->enumerate_devices);

    err = selector->enumerate_platforms(hwdev, &nb_platforms, &platforms,
                                        selector->context);
    ប្រសិនបើ (err)
        ត្រឡប់ err;

    found = 0;
    សម្រាប់ (p = 0; p < nb_platforms; p++) {
        const var_na *platform_name;

        ប្រសិនបើ (selector->platform_index >= 0 &&
            selector->platform_index != p)
            continue;

        av_freep(&platform_name_src);
        platform_name_src = opencl_get_platform_string(platforms[p],
                                                           CL_PLATFORM_NAME);
        ប្រសិនបើ (platform_name_src)
            platform_name = platform_name_src;
        បើមិនដូច្នេះ
            platform_name = "Unknown Platform";

        ប្រសិនបើ (selector->filter_platform) {
            err = selector->filter_platform(hwdev, platforms[p],
                                            platform_name,
                                            selector->context);
            ប្រសិនបើ (err < 0)
                goto fail;
            ប្រសិនបើ (err > 0)
                continue;
        }

        err = selector->enumerate_devices(hwdev, platforms[p], platform_name,
                                          &nb_devices, &devices,
                                          selector->context);
        ប្រសិនបើ (err < 0)
            continue;

        សម្រាប់ (d = 0; d < nb_devices; d++) {
            const var_na *device_name;

            ប្រសិនបើ (selector->device_index >= 0 &&
                selector->device_index != d)
                continue;

            av_freep(&device_name_src);
            device_name_src = opencl_get_device_string(devices[d],
                                                           CL_DEVICE_NAME);
            ប្រសិនបើ (device_name_src)
                device_name = device_name_src;
            បើមិនដូច្នេះ
                device_name = "Unknown Device";

            ប្រសិនបើ (selector->filter_device) {
                err = selector->filter_device(hwdev, devices[d],
                                              device_name,
                                              selector->context);
                ប្រសិនបើ (err < 0)
                    goto fail;
                ប្រសិនបើ (err > 0)
                    continue;
            }

            av_log(hwdev, AV_LOG_VERBOSE, "%d.%d: %s / %s\n", p, d,
                   platform_name, device_name);

            ++found;
            platform_id      = platforms[p];
            hwctx->device_id = devices[d];
        }

        av_freep(&devices);
    }

    ប្រសិនបើ (found == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No matching devices found.\n");
        err = AVERROR(ENODEV);
        goto fail;
    }
    ប្រសិនបើ (found > 1) {
        av_log(hwdev, AV_LOG_ERROR, "More than one matching device found.\n");
        err = AVERROR(ENODEV);
        goto fail;
    }

    ប្រសិនបើ (!props) {
        props = default_props;
        default_props[0] = CL_CONTEXT_PLATFORM;
        default_props[1] = (intptr_t)platform_id;
        default_props[2] = 0;
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (props[0] == CL_CONTEXT_PLATFORM && props[1] == 0)
            props[1] = (intptr_t)platform_id;
    }

    hwctx->context = clCreateContext(props, 1, &hwctx->device_id,
                                     &opencl_error_callback, hwdev, &cle);
    ប្រសិនបើ (!hwctx->context) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to create OpenCL context: "
               "%d.\n", cle);
        err = AVERROR(ENODEV);
        goto fail;
    }

    hwdev->free = &opencl_device_free;

    err = 0;
fail:
    av_freep(&platform_name_src);
    av_freep(&device_name_src);
    av_freep(&platforms);
    av_freep(&devices);
    ត្រឡប់ err;
}

static ចំនួនគត់ opencl_device_create(AVHWDeviceContext *hwdev, const var_na *device,
                                AVDictionary *opts, ចំនួនគត់ flags)
{
    OpenCLDeviceSelector selector = {
        .context = opts,
        .enumerate_platforms = &opencl_enumerate_platforms,
        .filter_platform     = &opencl_filter_platform,
        .enumerate_devices   = &opencl_enumerate_devices,
        .filter_device       = &opencl_filter_device,
    };

    ប្រសិនបើ (device && device[0]) {
        // Match one or both indices for platform and device.
        ចំនួនគត់ d = -1, p = -1, ret;
        ប្រសិនបើ (device[0] == '.')
            ret = sscanf(device, ".%d", &d);
        បើមិនដូច្នេះ
            ret = sscanf(device, "%d.%d", &p, &d);
        ប្រសិនបើ (ret < 1) {
            av_log(hwdev, AV_LOG_ERROR, "Invalid OpenCL platform/device "
                   "index specification \"%s\".\n", device);
            ត្រឡប់ AVERROR(EINVAL);
        }
        selector.platform_index = p;
        selector.device_index   = d;
    } បើមិនដូច្នេះ {
        selector.platform_index = -1;
        selector.device_index   = -1;
    }

    ត្រឡប់ opencl_device_create_internal(hwdev, &selector, NULL);
}

static ចំនួនគត់ opencl_device_init(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext    *priv = hwdev->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    cl_int cle;

    ប្រសិនបើ (hwctx->command_queue) {
        cle = clRetainCommandQueue(hwctx->command_queue);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to retain external "
                   "command queue: %d.\n", cle);
            ត្រឡប់ AVERROR(EIO);
        }
        priv->command_queue = hwctx->command_queue;
    } បើមិនដូច្នេះ {
        priv->command_queue = clCreateCommandQueue(hwctx->context,
                                                   hwctx->device_id,
                                                   0, &cle);
        ប្រសិនបើ (!priv->command_queue) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create internal "
                   "command queue: %d.\n", cle);
            ត្រឡប់ AVERROR(EIO);
        }
    }

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_PLATFORM,
                          parimaa_na(priv->platform_id), &priv->platform_id,
                          NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to determine the OpenCL "
               "platform containing the device.\n");
        ត្រឡប់ AVERROR(EIO);
    }

#define CL_FUNC(name, desc) do {                                \
        ប្រសិនបើ (fail)                                               \
            bha_nga;                                              \
        priv->name = clGetExtensionFunctionAddressForPlatform(  \
            priv->platform_id, #name);                          \
        ប្រសិនបើ (!priv->name) {                                      \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function not found (%s).\n", #name);  \
            fail = 1;                                           \
        } បើមិនដូច្នេះ {                                                \
            av_log(hwdev, AV_LOG_VERBOSE,                       \
                   desc " function found (%s).\n", #name);      \
        }                                                       \
    } ខណៈពេល (0)

#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
    {
        ចំនួនគត់ fail = 0;

        CL_FUNC(clCreateImageFromFdINTEL,
                "Beignet DRM to OpenCL image mapping");

        ប្រសិនបើ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "Beignet DRM to OpenCL "
                   "mapping not usable.\n");
            priv->beignet_drm_mapping_usable = 0;
        } បើមិនដូច្នេះ {
            priv->beignet_drm_mapping_usable = 1;
        }
    }
#endif

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    {
        size_t props_size;
        cl_context_properties *props = NULL;
        VADisplay va_display;
        const var_na *va_ext = "cl_intel_va_api_media_sharing";
        ចំនួនគត់ i, fail = 0;

        ប្រសិនបើ (!opencl_check_extension(hwdev, va_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for QSV to OpenCL mapping.\n", va_ext);
            goto no_qsv;
        }

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               0, NULL, &props_size);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            goto no_qsv;
        }
        ប្រសិនបើ (props_size == 0) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }

        props = av_malloc(props_size);
        ប្រសិនបើ (!props)
            ត្រឡប់ AVERROR(ENOMEM);

        cle = clGetContextInfo(hwctx->context, CL_CONTEXT_PROPERTIES,
                               props_size, props, NULL);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_VERBOSE, "Failed to get context "
                   "properties: %d.\n", cle);
            goto no_qsv;
        }

        va_display = NULL;
        សម្រាប់ (i = 0; i < (props_size / parimaa_na(*props) - 1); i++) {
            ប្រសិនបើ (props[i] == CL_CONTEXT_VA_API_DISPLAY_INTEL) {
                va_display = (VADisplay)(intptr_t)props[i+1];
                bha_nga;
            }
        }
        ប្រសិនបើ (!va_display) {
            av_log(hwdev, AV_LOG_VERBOSE, "Media sharing must be "
                   "enabled on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }
        ប្រសិនបើ (!vaDisplayIsValid(va_display)) {
            av_log(hwdev, AV_LOG_VERBOSE, "A valid VADisplay is "
                   "required on context creation to use QSV to "
                   "OpenCL mapping.\n");
            goto no_qsv;
        }

        CL_FUNC(clCreateFromVA_APIMediaSurfaceINTEL,
                "Intel QSV to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseVA_APIMediaSurfacesINTEL,
                "Intel QSV in OpenCL release");

        ប្រសិនបើ (fail) {
        no_qsv:
            av_log(hwdev, AV_LOG_WARNING, "QSV to OpenCL mapping "
                   "not usable.\n");
            priv->qsv_mapping_usable = 0;
        } បើមិនដូច្នេះ {
            priv->qsv_mapping_usable = 1;
        }
        av_free(props);
    }
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2
    {
        ចំនួនគត់ fail = 0;

        CL_FUNC(clCreateFromDX9MediaSurfaceKHR,
                "DXVA2 to OpenCL mapping");
        CL_FUNC(clEnqueueAcquireDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL acquire");
        CL_FUNC(clEnqueueReleaseDX9MediaSurfacesKHR,
                "DXVA2 in OpenCL release");

        ប្រសិនបើ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DXVA2 to OpenCL mapping "
                   "not usable.\n");
            priv->dxva2_mapping_usable = 0;
        } បើមិនដូច្នេះ {
            priv->dx9_media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
            priv->dxva2_mapping_usable = 1;
        }
    }
#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11
    {
        const var_na *d3d11_ext = "cl_khr_d3d11_sharing";
        const var_na *nv12_ext  = "cl_intel_d3d11_nv12_media_sharing";
        ចំនួនគត់ fail = 0;

        ប្រសិនបើ (!opencl_check_extension(hwdev, d3d11_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for D3D11 to OpenCL mapping.\n", d3d11_ext);
            fail = 1;
        } បើមិនដូច្នេះ ប្រសិនបើ (!opencl_check_extension(hwdev, nv12_ext)) {
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

        ប្រសិនបើ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "D3D11 to OpenCL mapping "
                   "not usable.\n");
            priv->d3d11_mapping_usable = 0;
        } បើមិនដូច្នេះ {
            priv->d3d11_mapping_usable = 1;
        }
    }
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
    {
        const var_na *drm_arm_ext = "cl_arm_import_memory";
        const var_na *image_ext   = "cl_khr_image2d_from_buffer";
        ចំនួនគត់ fail = 0;

        ប្រសិនបើ (!opencl_check_extension(hwdev, drm_arm_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   drm_arm_ext);
            fail = 1;
        }
        ប្រសិនបើ (!opencl_check_extension(hwdev, image_ext)) {
            av_log(hwdev, AV_LOG_VERBOSE, "The %s extension is "
                   "required for DRM to OpenCL mapping on ARM.\n",
                   image_ext);
            fail = 1;
        }

        // clImportMemoryARM() is linked statically.

        ប្រសិនបើ (fail) {
            av_log(hwdev, AV_LOG_WARNING, "DRM to OpenCL mapping on ARM "
                   "not usable.\n");
            priv->drm_arm_mapping_usable = 0;
        } បើមិនដូច្នេះ {
            priv->drm_arm_mapping_usable = 1;
        }
    }
#endif

#undef CL_FUNC

    ត្រឡប់ 0;
}

static void opencl_device_uninit(AVHWDeviceContext *hwdev)
{
    OpenCLDeviceContext *priv = hwdev->hwctx;
    cl_int cle;

    ប្រសិនបើ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to release internal "
                   "command queue reference: %d.\n", cle);
        }
        priv->command_queue = NULL;
    }
}

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
static ចំនួនគត់ opencl_filter_intel_media_vaapi_platform(AVHWDeviceContext *hwdev,
                                                    cl_platform_id platform_id,
                                                    const var_na *platform_name,
                                                    void *context)
{
    // This doesn't exist as a platform extension, so just test whether
    // the function we will use for device enumeration exists.

    ប្រសិនបើ (!clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL")) {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not export the "
               "VAAPI device enumeration function.\n", platform_name);
        ត្រឡប់ 1;
    } បើមិនដូច្នេះ {
        ត្រឡប់ 0;
    }
}

static ចំនួនគត់ opencl_enumerate_intel_media_vaapi_devices(AVHWDeviceContext *hwdev,
                                                      cl_platform_id platform_id,
                                                      const var_na *platform_name,
                                                      cl_uint *nb_devices,
                                                      cl_device_id **devices,
                                                      void *context)
{
    VADisplay va_display = context;
    clGetDeviceIDsFromVA_APIMediaAdapterINTEL_fn
        clGetDeviceIDsFromVA_APIMediaAdapterINTEL;
    cl_int cle;

    clGetDeviceIDsFromVA_APIMediaAdapterINTEL =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromVA_APIMediaAdapterINTEL");
    ប្រសិនបើ (!clGetDeviceIDsFromVA_APIMediaAdapterINTEL) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromVA_APIMediaAdapterINTEL().\n");
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, 0, NULL, nb_devices);
    ប្រសិនបើ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No VAAPI-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, parimaa_na(**devices));
    ប្រសិនបើ (!*devices)
        ត្រឡប់ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
        platform_id, CL_VA_API_DISPLAY_INTEL, va_display,
        CL_PREFERRED_DEVICES_FOR_VA_API_INTEL, *nb_devices, *devices, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of VAAPI-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_filter_intel_media_vaapi_device(AVHWDeviceContext *hwdev,
                                                  cl_device_id device_id,
                                                  const var_na *device_name,
                                                  void *context)
{
    const var_na *va_ext = "cl_intel_va_api_media_sharing";

    ប្រសិនបើ (opencl_check_device_extension(device_id, va_ext)) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, va_ext);
        ត្រឡប់ 1;
    }
}
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2
static ចំនួនគត់ opencl_filter_dxva2_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        const var_na *platform_name,
                                        void *context)
{
    const var_na *dx9_ext = "cl_khr_dx9_media_sharing";

    ប្រសិនបើ (opencl_check_platform_extension(platform_id, dx9_ext)) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, dx9_ext);
        ត្រឡប់ 1;
    }
}

static ចំនួនគត់ opencl_enumerate_dxva2_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          const var_na *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          void *context)
{
    IDirect3DDevice9 *device = context;
    clGetDeviceIDsFromDX9MediaAdapterKHR_fn
        clGetDeviceIDsFromDX9MediaAdapterKHR;
    cl_dx9_media_adapter_type_khr media_adapter_type = CL_ADAPTER_D3D9EX_KHR;
    cl_int cle;

    clGetDeviceIDsFromDX9MediaAdapterKHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromDX9MediaAdapterKHR");
    ប្រសិនបើ (!clGetDeviceIDsFromDX9MediaAdapterKHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromDX9MediaAdapterKHR().\n");
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (void**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        0, NULL, nb_devices);
    ប្រសិនបើ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No DXVA2-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, parimaa_na(**devices));
    ប្រសិនបើ (!*devices)
        ត្រឡប់ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform_id, 1, &media_adapter_type, (void**)&device,
        CL_PREFERRED_DEVICES_FOR_DX9_MEDIA_ADAPTER_KHR,
        *nb_devices, *devices, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of DXVA2-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    ត្រឡប់ 0;
}
#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11
static ចំនួនគត់ opencl_filter_d3d11_platform(AVHWDeviceContext *hwdev,
                                        cl_platform_id platform_id,
                                        const var_na *platform_name,
                                        void *context)
{
    const var_na *d3d11_ext = "cl_khr_d3d11_sharing";

    ប្រសិនបើ (opencl_check_platform_extension(platform_id, d3d11_ext)) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, d3d11_ext);
        ត្រឡប់ 1;
    }
}

static ចំនួនគត់ opencl_enumerate_d3d11_devices(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          const var_na *platform_name,
                                          cl_uint *nb_devices,
                                          cl_device_id **devices,
                                          void *context)
{
    ID3D11Device *device = context;
    clGetDeviceIDsFromD3D11KHR_fn clGetDeviceIDsFromD3D11KHR;
    cl_int cle;

    clGetDeviceIDsFromD3D11KHR =
        clGetExtensionFunctionAddressForPlatform(platform_id,
            "clGetDeviceIDsFromD3D11KHR");
    ប្រសិនបើ (!clGetDeviceIDsFromD3D11KHR) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get address of "
               "clGetDeviceIDsFromD3D11KHR().\n");
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     0, NULL, nb_devices);
    ប្រសិនបើ (cle == CL_DEVICE_NOT_FOUND) {
        av_log(hwdev, AV_LOG_DEBUG, "No D3D11-supporting devices found "
               "on platform \"%s\".\n", platform_name);
        *nb_devices = 0;
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get number of devices "
               "on platform \"%s\": %d.\n", platform_name, cle);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    *devices = av_malloc_array(*nb_devices, parimaa_na(**devices));
    ប្រសិនបើ (!*devices)
        ត្រឡប់ AVERROR(ENOMEM);

    cle = clGetDeviceIDsFromD3D11KHR(platform_id,
                                     CL_D3D11_DEVICE_KHR, device,
                                     CL_PREFERRED_DEVICES_FOR_D3D11_KHR,
                                     *nb_devices, *devices, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to get list of D3D11-supporting "
               "devices on platform \"%s\": %d.\n", platform_name, cle);
        av_freep(devices);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    ត្រឡប់ 0;
}
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
static ចំនួនគត់ opencl_filter_gpu_device(AVHWDeviceContext *hwdev,
                                    cl_device_id device_id,
                                    const var_na *device_name,
                                    void *context)
{
    cl_device_type device_type;
    cl_int cle;

    cle = clGetDeviceInfo(device_id, CL_DEVICE_TYPE,
                          parimaa_na(device_type), &device_type, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query device type "
               "of device \"%s\".\n", device_name);
        ត្រឡប់ AVERROR_UNKNOWN;
    }
    ប្រសិនបើ (!(device_type & CL_DEVICE_TYPE_GPU)) {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s skipped (not GPU).\n",
               device_name);
        ត្រឡប់ 1;
    }

    ត្រឡប់ 0;
}
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
static ចំនួនគត់ opencl_filter_drm_arm_platform(AVHWDeviceContext *hwdev,
                                          cl_platform_id platform_id,
                                          const var_na *platform_name,
                                          void *context)
{
    const var_na *drm_arm_ext = "cl_arm_import_memory";

    ប្រសិនបើ (opencl_check_platform_extension(platform_id, drm_arm_ext)) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        av_log(hwdev, AV_LOG_DEBUG, "Platform %s does not support the "
               "%s extension.\n", platform_name, drm_arm_ext);
        ត្រឡប់ 1;
    }
}

static ចំនួនគត់ opencl_filter_drm_arm_device(AVHWDeviceContext *hwdev,
                                        cl_device_id device_id,
                                        const var_na *device_name,
                                        void *context)
{
    const var_na *drm_arm_ext = "cl_arm_import_memory";

    ប្រសិនបើ (opencl_check_device_extension(device_id, drm_arm_ext)) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        av_log(hwdev, AV_LOG_DEBUG, "Device %s does not support the "
               "%s extension.\n", device_name, drm_arm_ext);
        ត្រឡប់ 1;
    }
}
#endif

static ចំនួនគត់ opencl_device_derive(AVHWDeviceContext *hwdev,
                                AVHWDeviceContext *src_ctx, AVDictionary *opts,
                                ចំនួនគត់ flags)
{
    ចំនួនគត់ err;
    switch (src_ctx->type) {

#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
    pak_sa AV_HWDEVICE_TYPE_DRM:
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        {
            // Surface mapping works via DRM PRIME fds with no special
            // initialisation required in advance.  This just finds the
            // Beignet ICD by name.
            AVDictionary *selector_opts = NULL;

            err = av_dict_set(&selector_opts, "platform_vendor", "Intel", 0);
            ប្រសិនបើ (err >= 0)
                err = av_dict_set(&selector_opts, "platform_version", "beignet", 0);
            ប្រសិនបើ (err >= 0) {
                OpenCLDeviceSelector selector = {
                    .platform_index      = -1,
                    .device_index        = 0,
                    .context             = selector_opts,
                    .enumerate_platforms = &opencl_enumerate_platforms,
                    .filter_platform     = &opencl_filter_platform,
                    .enumerate_devices   = &opencl_enumerate_devices,
                    .filter_device       = NULL,
                };
                err = opencl_device_create_internal(hwdev, &selector, NULL);
            }
            av_dict_free(&selector_opts);
        }
        bha_nga;
#endif

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
        // The generic code automatically attempts to derive from all
        // ancestors of the given device, so we can ignore QSV devices here
        // and just consider the inner VAAPI device it was derived from.
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
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
        bha_nga;
#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *src_hwctx = src_ctx->hwctx;
            IDirect3DDevice9 *device;
            HANDLE device_handle;
            HRESULT hr;

            hr = IDirect3DDeviceManager9_OpenDeviceHandle(src_hwctx->devmgr,
                                                          &device_handle);
            ប្រសិនបើ (FAILED(hr)) {
                av_log(hwdev, AV_LOG_ERROR, "Failed to open device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
                bha_nga;
            }

            hr = IDirect3DDeviceManager9_LockDevice(src_hwctx->devmgr,
                                                    device_handle,
                                                    &device, FALSE);
            ប្រសិនបើ (SUCCEEDED(hr)) {
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
            } បើមិនដូច្នេះ {
                av_log(hwdev, AV_LOG_ERROR, "Failed to lock device handle "
                       "for Direct3D9 device: %lx.\n", (unsigned long)hr);
                err = AVERROR_UNKNOWN;
            }

            IDirect3DDeviceManager9_CloseDeviceHandle(src_hwctx->devmgr,
                                                      device_handle);
        }
        bha_nga;
#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
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
        bha_nga;
#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
    pak_sa AV_HWDEVICE_TYPE_DRM:
        {
            OpenCLDeviceSelector selector = {
                .platform_index      = -1,
                .device_index        = -1,
                .context             = NULL,
                .enumerate_platforms = &opencl_enumerate_platforms,
                .filter_platform     = &opencl_filter_drm_arm_platform,
                .enumerate_devices   = &opencl_enumerate_devices,
                .filter_device       = &opencl_filter_drm_arm_device,
            };

            err = opencl_device_create_internal(hwdev, &selector, NULL);
        }
        bha_nga;
#endif

#ប្រសិនបើ HAVE_OPENCL_VIDEOTOOLBOX
    pak_sa AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        err = opencl_device_create(hwdev, NULL, NULL, 0);
        bha_nga;
#endif

    default:
        err = AVERROR(ENOSYS);
        bha_nga;
    }

    ត្រឡប់ err;
}

static ចំនួនគត់ opencl_get_plane_format(ga_nanaa AVPixelFormat pixfmt,
                                   ចំនួនគត់ plane, ចំនួនគត់ width, ចំនួនគត់ height,
                                   cl_image_format *image_format,
                                   cl_image_desc *image_desc)
{
    const AVPixFmtDescriptor *desc;
    const AVComponentDescriptor *comp;
    ចំនួនគត់ channels = 0, order = 0, depth = 0, step = 0;
    ចំនួនគត់ wsub, hsub, alpha;
    ចំនួនគត់ c;

    ប្រសិនបើ (plane >= AV_NUM_DATA_POINTERS)
        ត្រឡប់ AVERROR(ENOENT);

    desc = av_pix_fmt_desc_get(pixfmt);

    // Only normal images are allowed.
    ប្រសិនបើ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM |
                       AV_PIX_FMT_FLAG_HWACCEL   |
                       AV_PIX_FMT_FLAG_PAL))
        ត្រឡប់ AVERROR(EINVAL);

    wsub = 1 << desc->log2_chroma_w;
    hsub = 1 << desc->log2_chroma_h;
    // Subsampled components must be exact.
    ប្រសិនបើ (width & wsub - 1 || height & hsub - 1)
        ត្រឡប់ AVERROR(EINVAL);

    សម្រាប់ (c = 0; c < desc->nb_components; c++) {
        comp = &desc->comp[c];
        ប្រសិនបើ (comp->plane != plane)
            continue;
        // The step size must be a power of two.
        ប្រសិនបើ (comp->step != 1 && comp->step != 2 &&
            comp->step != 4 && comp->step != 8)
            ត្រឡប់ AVERROR(EINVAL);
        // The bits in each component must be packed in the
        // most-significant-bits of the relevant bytes.
        ប្រសិនបើ (comp->shift + comp->depth != 8 &&
            comp->shift + comp->depth != 16 &&
            comp->shift + comp->depth != 32)
            ត្រឡប់ AVERROR(EINVAL);
        // The depth must not vary between components.
        ប្រសិនបើ (depth && comp->depth != depth)
            ត្រឡប់ AVERROR(EINVAL);
        // If a single data element crosses multiple bytes then
        // it must match the native endianness.
        ប្រសិនបើ (comp->depth > 8 &&
            HAVE_BIGENDIAN == !(desc->flags & AV_PIX_FMT_FLAG_BE))
            ត្រឡប់ AVERROR(EINVAL);
        // A single data element must not contain multiple samples
        // from the same component.
        ប្រសិនបើ (step && comp->step != step)
            ត្រឡប់ AVERROR(EINVAL);

        depth = comp->depth;
        order = order * 10 + comp->offset / ((depth + 7) / 8) + 1;
        step  = comp->step;
        alpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA &&
                 c == desc->nb_components - 1);
        ++channels;
    }
    ប្រសិនបើ (channels == 0)
        ត្រឡប់ AVERROR(ENOENT);

    memset(image_format, 0, parimaa_na(*image_format));
    memset(image_desc,   0, parimaa_na(*image_desc));
    image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;

    ប្រសិនបើ (plane == 0 || alpha) {
        image_desc->image_width     = width;
        image_desc->image_height    = height;
        image_desc->image_row_pitch = step * width;
    } បើមិនដូច្នេះ {
        image_desc->image_width     = width  / wsub;
        image_desc->image_height    = height / hsub;
        image_desc->image_row_pitch = step * width / wsub;
    }

    ប្រសិនបើ (depth <= 8) {
        image_format->image_channel_data_type = CL_UNORM_INT8;
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (depth <= 16)
            image_format->image_channel_data_type = CL_UNORM_INT16;
        បើមិនដូច្នេះ ប្រសិនបើ (depth == 32)
            image_format->image_channel_data_type = CL_FLOAT;
        បើមិនដូច្នេះ
            ត្រឡប់ AVERROR(EINVAL);
    }

#define CHANNEL_ORDER(order, type) \
    pak_sa order: image_format->image_channel_order = type; bha_nga;
    switch (order) {
        CHANNEL_ORDER(1,    CL_R);
        CHANNEL_ORDER(12,   CL_RG);
        CHANNEL_ORDER(1234, CL_RGBA);
        CHANNEL_ORDER(2341, CL_ARGB);
        CHANNEL_ORDER(3214, CL_BGRA);
#ifdef CL_ABGR
        CHANNEL_ORDER(4321, CL_ABGR);
#endif
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }
#undef CHANNEL_ORDER

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_frames_get_constraints(AVHWDeviceContext *hwdev,
                                         const void *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    AVOpenCLDeviceContext *hwctx = hwdev->hwctx;
    cl_uint nb_image_formats;
    cl_image_format *image_formats = NULL;
    cl_int cle;
    ga_nanaa AVPixelFormat pix_fmt;
    ចំនួនគត់ err, pix_fmts_found;
    size_t max_width, max_height;

    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_WIDTH,
                          parimaa_na(max_width), &max_width, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image width: %d.\n", cle);
    } បើមិនដូច្នេះ {
        constraints->max_width = max_width;
    }
    cle = clGetDeviceInfo(hwctx->device_id, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                          parimaa_na(max_height), &max_height, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query maximum "
               "supported image height: %d.\n", cle);
    } បើមិនដូច្នេះ {
        constraints->max_height = max_height;
    }
    av_log(hwdev, AV_LOG_DEBUG, "Maximum supported image size %dx%d.\n",
           constraints->max_width, constraints->max_height);

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     0, NULL, &nb_image_formats);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        goto fail;
    }
    ប្រសិនបើ (nb_image_formats == 0) {
        av_log(hwdev, AV_LOG_ERROR, "No image support in OpenCL "
               "driver (zero supported image formats).\n");
        err = AVERROR(ENOSYS);
        goto fail;
    }

    image_formats =
        av_malloc_array(nb_image_formats, parimaa_na(*image_formats));
    ប្រសិនបើ (!image_formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }

    cle = clGetSupportedImageFormats(hwctx->context,
                                     CL_MEM_READ_WRITE,
                                     CL_MEM_OBJECT_IMAGE2D,
                                     nb_image_formats,
                                     image_formats, NULL);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwdev, AV_LOG_ERROR, "Failed to query supported "
               "image formats: %d.\n", cle);
        err = AVERROR(ENOSYS);
        goto fail;
    }

    pix_fmts_found = 0;
    សម្រាប់ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++) {
        cl_image_format image_format;
        cl_image_desc   image_desc;
        ចំនួនគត់ plane, i;

        សម្រាប់ (plane = 0;; plane++) {
            err = opencl_get_plane_format(pix_fmt, plane, 0, 0,
                                          &image_format,
                                          &image_desc);
            ប្រសិនបើ (err < 0)
                bha_nga;

            សម្រាប់ (i = 0; i < nb_image_formats; i++) {
                ប្រសិនបើ (image_formats[i].image_channel_order ==
                    image_format.image_channel_order &&
                    image_formats[i].image_channel_data_type ==
                    image_format.image_channel_data_type)
                    bha_nga;
            }
            ប្រសិនបើ (i == nb_image_formats) {
                err = AVERROR(EINVAL);
                bha_nga;
            }
        }
        ប្រសិនបើ (err != AVERROR(ENOENT))
            continue;

        av_log(hwdev, AV_LOG_DEBUG, "Format %s supported.\n",
               av_get_pix_fmt_name(pix_fmt));

        err = av_reallocp_array(&constraints->valid_sw_formats,
                                pix_fmts_found + 2,
                                parimaa_na(*constraints->valid_sw_formats));
        ប្រសិនបើ (err < 0)
            goto fail;
        constraints->valid_sw_formats[pix_fmts_found] = pix_fmt;
        constraints->valid_sw_formats[pix_fmts_found + 1] =
            AV_PIX_FMT_NONE;
        ++pix_fmts_found;
    }

    av_freep(&image_formats);

    constraints->valid_hw_formats =
        av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    ប្រសិនបើ (!constraints->valid_hw_formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    constraints->valid_hw_formats[0] = AV_PIX_FMT_OPENCL;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ត្រឡប់ 0;

fail:
    av_freep(&image_formats);
    ត្រឡប់ err;
}

static void opencl_pool_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext       *hwfc = opaque;
    AVOpenCLFrameDescriptor *desc = (AVOpenCLFrameDescriptor*)data;
    cl_int cle;
    ចំនួនគត់ p;

    សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release plane %d: "
                   "%d.\n", p, cle);
        }
    }

    av_free(desc);
}

static AVBufferRef *opencl_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext      *hwfc = opaque;
    AVOpenCLDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_int cle;
    cl_mem image;
    cl_image_format image_format;
    cl_image_desc   image_desc;
    ចំនួនគត់ err, p;
    AVBufferRef *ref;

    desc = av_mallocz(parimaa_na(*desc));
    ប្រសិនបើ (!desc)
        ត្រឡប់ NULL;

    សម្រាប់ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      hwfc->width, hwfc->height,
                                      &image_format, &image_desc);
        ប្រសិនបើ (err == AVERROR(ENOENT))
            bha_nga;
        ប្រសិនបើ (err < 0)
            goto fail;

        // For generic image objects, the pitch is determined by the
        // implementation.
        image_desc.image_row_pitch = 0;

        image = clCreateImage(hwctx->context, CL_MEM_READ_WRITE,
                              &image_format, &image_desc, NULL, &cle);
        ប្រសិនបើ (!image) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to create image for "
                   "plane %d: %d.\n", p, cle);
            goto fail;
        }

        desc->planes[p] = image;
    }

    desc->nb_planes = p;

    ref = av_buffer_create((uint8_t*)desc, parimaa_na(*desc),
                           &opencl_pool_free, hwfc, 0);
    ប្រសិនបើ (!ref)
        goto fail;

    ត្រឡប់ ref;

fail:
    សម្រាប់ (p = 0; desc->planes[p]; p++)
        clReleaseMemObject(desc->planes[p]);
    av_free(desc);
    ត្រឡប់ NULL;
}

static ចំនួនគត់ opencl_frames_init_command_queue(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext    *priv = hwfc->hwctx;
    AVOpenCLFramesContext *hwctx = &priv->p;
    OpenCLDeviceContext *devpriv = hwfc->device_ctx->hwctx;
    cl_int cle;

    priv->command_queue = hwctx->command_queue ? hwctx->command_queue
                                               : devpriv->command_queue;
    cle = clRetainCommandQueue(priv->command_queue);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retain frame "
               "command queue: %d.\n", cle);
        ត្រឡប់ AVERROR(EIO);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_frames_init(AVHWFramesContext *hwfc)
{
    ប្រសិនបើ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal =
            av_buffer_pool_init2(parimaa_na(cl_mem), hwfc,
                                 &opencl_pool_alloc, NULL);
        ប្រសិនបើ (!ffhwframesctx(hwfc)->pool_internal)
            ត្រឡប់ AVERROR(ENOMEM);
    }

    ត្រឡប់ opencl_frames_init_command_queue(hwfc);
}

static void opencl_frames_uninit(AVHWFramesContext *hwfc)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_int cle;

#ប្រសិនបើ HAVE_OPENCL_DXVA2 || HAVE_OPENCL_D3D11
    ចំនួនគត់ i, p;
    សម្រាប់ (i = 0; i < priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &priv->mapped_frames[i];
        សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
            cle = clReleaseMemObject(desc->planes[p]);
            ប្រសិនបើ (cle != CL_SUCCESS) {
                av_log(hwfc, AV_LOG_ERROR, "Failed to release mapped "
                       "frame object (frame %d plane %d): %d.\n",
                       i, p, cle);
            }
        }
    }
    av_freep(&priv->mapped_frames);
#endif

    ប្រសិនបើ (priv->command_queue) {
        cle = clReleaseCommandQueue(priv->command_queue);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release frame "
                   "command queue: %d.\n", cle);
        }
        priv->command_queue = NULL;
    }
}

static ចំនួនគត់ opencl_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    AVOpenCLFrameDescriptor *desc;
    ចំនួនគត់ p;

    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ប្រសិនបើ (!frame->buf[0])
        ត្រឡប់ AVERROR(ENOMEM);

    desc = (AVOpenCLFrameDescriptor*)frame->buf[0]->data;

    សម្រាប់ (p = 0; p < desc->nb_planes; p++)
        frame->data[p] = (uint8_t*)desc->planes[p];

    frame->format  = AV_PIX_FMT_OPENCL;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ga_nanaa AVHWFrameTransferDirection dir,
                                       ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts;

    fmts = av_malloc_array(2, parimaa_na(*fmts));
    ប្រសិនបើ (!fmts)
        ត្រឡប់ AVERROR(ENOMEM);

    fmts[0] = hwfc->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, ចំនួនគត់ nb_events)
{
    cl_int cle;
    ចំនួនគត់ i;

    cle = clWaitForEvents(nb_events, events);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        ត្រឡប់ AVERROR(EIO);
    }

    សម្រាប់ (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opencl_transfer_data_from(AVHWFramesContext *hwfc,
                                     AVFrame *dst, const AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_NUM_DATA_POINTERS];
    ចំនួនគត់ err, p;

    ប្រសិនបើ (dst->format != hwfc->sw_format)
        ត្រឡប់ AVERROR(EINVAL);

    សម្រាប់ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ប្រសិនបើ (err < 0) {
            ប្រសិនបើ (err == AVERROR(ENOENT))
                err = 0;
            bha_nga;
        }

        ប្រសិនបើ (!dst->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "destination frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            bha_nga;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueReadImage(priv->command_queue,
                                 (cl_mem)src->data[p],
                                 CL_FALSE, origin, region,
                                 dst->linesize[p], 0,
                                 dst->data[p],
                                 0, NULL, &events[p]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue read of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            bha_nga;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ត្រឡប់ err;
}

static ចំនួនគត់ opencl_transfer_data_to(AVHWFramesContext *hwfc,
                                   AVFrame *dst, const AVFrame *src)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    cl_image_format image_format;
    cl_image_desc image_desc;
    cl_int cle;
    size_t origin[3] = { 0, 0, 0 };
    size_t region[3];
    cl_event events[AV_NUM_DATA_POINTERS];
    ចំនួនគត់ err, p;

    ប្រសិនបើ (src->format != hwfc->sw_format)
        ត្រឡប់ AVERROR(EINVAL);

    សម្រាប់ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ប្រសិនបើ (err < 0) {
            ប្រសិនបើ (err == AVERROR(ENOENT))
                err = 0;
            bha_nga;
        }

        ប្រសិនបើ (!src->data[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Plane %d missing on "
                   "source frame for transfer.\n", p);
            err = AVERROR(EINVAL);
            bha_nga;
        }

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        cle = clEnqueueWriteImage(priv->command_queue,
                                  (cl_mem)dst->data[p],
                                  CL_FALSE, origin, region,
                                  src->linesize[p], 0,
                                  src->data[p],
                                  0, NULL, &events[p]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to enqueue write of "
                   "OpenCL image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            bha_nga;
        }
    }

    opencl_wait_events(hwfc, events, p);

    ត្រឡប់ err;
}

typedef sa_nracanaa OpenCLMapping {
    // The mapped addresses for each plane.
    // The destination frame is not available when we unmap, so these
    // need to be stored separately.
    void *address[AV_NUM_DATA_POINTERS];
} OpenCLMapping;

static void opencl_unmap_frame(AVHWFramesContext *hwfc,
                               HWMapDescriptor *hwmap)
{
    OpenCLFramesContext *priv = hwfc->hwctx;
    OpenCLMapping *map = hwmap->priv;
    cl_event events[AV_NUM_DATA_POINTERS];
    ចំនួនគត់ p, e;
    cl_int cle;

    សម្រាប់ (p = e = 0; p < FF_ARRAY_ELEMS(map->address); p++) {
        ប្រសិនបើ (!map->address[p])
            bha_nga;

        cle = clEnqueueUnmapMemObject(priv->command_queue,
                                      (cl_mem)hwmap->source->data[p],
                                      map->address[p],
                                      0, NULL, &events[e]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to unmap OpenCL "
                   "image plane %d: %d.\n", p, cle);
        }
        ++e;
    }

    opencl_wait_events(hwfc, events, e);

    av_free(map);
}

static ចំនួនគត់ opencl_map_frame(AVHWFramesContext *hwfc, AVFrame *dst,
                            const AVFrame *src, ចំនួនគត់ flags)
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
    cl_event events[AV_NUM_DATA_POINTERS];
    ចំនួនគត់ err, p;

    av_assert0(hwfc->sw_format == dst->format);

    ប្រសិនបើ (flags & AV_HWFRAME_MAP_OVERWRITE &&
        !(flags & AV_HWFRAME_MAP_READ)) {
        // This is mutually exclusive with the read/write flags, so
        // there is no way to map with read here.
        map_flags = CL_MAP_WRITE_INVALIDATE_REGION;
    } បើមិនដូច្នេះ {
        map_flags = 0;
        ប្រសិនបើ (flags & AV_HWFRAME_MAP_READ)
            map_flags |= CL_MAP_READ;
        ប្រសិនបើ (flags & AV_HWFRAME_MAP_WRITE)
            map_flags |= CL_MAP_WRITE;
    }

    map = av_mallocz(parimaa_na(*map));
    ប្រសិនបើ (!map)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (p = 0;; p++) {
        err = opencl_get_plane_format(hwfc->sw_format, p,
                                      src->width, src->height,
                                      &image_format, &image_desc);
        ប្រសិនបើ (err == AVERROR(ENOENT))
            bha_nga;
        ប្រសិនបើ (err < 0)
            goto fail;

        region[0] = image_desc.image_width;
        region[1] = image_desc.image_height;
        region[2] = 1;

        map->address[p] =
            clEnqueueMapImage(priv->command_queue,
                              (cl_mem)src->data[p],
                              CL_FALSE, map_flags, origin, region,
                              &row_pitch, NULL, 0, NULL,
                              &events[p], &cle);
        ប្រសិនបើ (!map->address[p]) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to map OpenCL "
                   "image plane %d: %d.\n", p, cle);
            err = AVERROR(EIO);
            goto fail;
        }

        dst->data[p] = map->address[p];
        dst->linesize[p] = row_pitch;

        av_log(hwfc, AV_LOG_DEBUG, "Map plane %d (%p -> %p).\n",
               p, src->data[p], dst->data[p]);
    }

    err = opencl_wait_events(hwfc, events, p);
    ប្រសិនបើ (err < 0)
        goto fail;

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                &opencl_unmap_frame, map);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    សម្រាប់ (p = 0; p < AV_NUM_DATA_POINTERS; p++) {
        ប្រសិនបើ (!map->address[p])
            bha_nga;
        clEnqueueUnmapMemObject(priv->command_queue,
                                (cl_mem)src->data[p],
                                map->address[p],
                                0, NULL, &events[p]);
    }
    ប្រសិនបើ (p > 0)
        opencl_wait_events(hwfc, events, p);
    av_freep(&map);
    ត្រឡប់ err;
}

#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET

typedef sa_nracanaa DRMBeignetToOpenCLMapping {
    AVFrame              *drm_frame;
    AVDRMFrameDescriptor *drm_desc;

    AVOpenCLFrameDescriptor frame;
} DRMBeignetToOpenCLMapping;

static void opencl_unmap_from_drm_beignet(AVHWFramesContext *dst_fc,
                                          HWMapDescriptor *hwmap)
{
    DRMBeignetToOpenCLMapping *mapping = hwmap->priv;
    cl_int cle;
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < mapping->frame.nb_planes; i++) {
        cle = clReleaseMemObject(mapping->frame.planes[i]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL image "
                   "of plane %d of DRM frame: %d.\n", i, cle);
        }
    }

    av_free(mapping);
}

static ចំនួនគត់ opencl_map_from_drm_beignet(AVHWFramesContext *dst_fc,
                                       AVFrame *dst, const AVFrame *src,
                                       ចំនួនគត់ flags)
{
    OpenCLDeviceContext    *priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext *hwctx = &priv->p;
    DRMBeignetToOpenCLMapping *mapping;
    const AVDRMFrameDescriptor *desc;
    cl_int cle;
    ចំនួនគត់ err, i, j, p;

    desc = (const AVDRMFrameDescriptor*)src->data[0];

    mapping = av_mallocz(parimaa_na(*mapping));
    ប្រសិនបើ (!mapping)
        ត្រឡប់ AVERROR(ENOMEM);

    p = 0;
    សម្រាប់ (i = 0; i < desc->nb_layers; i++) {
        const AVDRMLayerDescriptor *layer = &desc->layers[i];
        សម្រាប់ (j = 0; j < layer->nb_planes; j++) {
            const AVDRMPlaneDescriptor *plane = &layer->planes[j];
            const AVDRMObjectDescriptor *object =
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
            ប្រសិនបើ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "DRM frame layer %d "
                       "plane %d is not representable in OpenCL: %d.\n",
                       i, j, err);
                goto fail;
            }
            image_info.width  = image_desc.image_width;
            image_info.height = image_desc.image_height;

            mapping->frame.planes[p] =
                priv->clCreateImageFromFdINTEL(hwctx->context,
                                               &image_info, &cle);
            ប្រសិនបើ (!mapping->frame.planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL image "
                       "from layer %d plane %d of DRM frame: %d.\n",
                       i, j, cle);
                err = AVERROR(EIO);
                goto fail;
            }

            dst->data[p] = (uint8_t*)mapping->frame.planes[p];
            mapping->frame.nb_planes = ++p;
        }
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_beignet,
                                mapping);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    សម្រាប់ (p = 0; p < mapping->frame.nb_planes; p++) {
        ប្រសិនបើ (mapping->frame.planes[p])
            clReleaseMemObject(mapping->frame.planes[p]);
    }
    av_free(mapping);
    memset(dst->data, 0, parimaa_na(dst->data));
    ត្រឡប់ err;
}

#ប្រសិនបើ HAVE_OPENCL_VAAPI_BEIGNET

static ចំនួនគត់ opencl_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, const AVFrame *src,
                                 ចំនួនគត់ flags)
{
    AVFrame *tmp;
    ចំនួនគត់ err;

    tmp = av_frame_alloc();
    ប្រសិនបើ (!tmp)
        ត្រឡប់ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_PRIME;

    err = av_hwframe_map(tmp, src, flags);
    ប្រសិនបើ (err < 0)
        goto fail;

    err = opencl_map_from_drm_beignet(dst_fc, dst, tmp, flags);
    ប្រសិនបើ (err < 0)
        goto fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ត្រឡប់ err;
}

#endif /* HAVE_OPENCL_VAAPI_BEIGNET */
#endif /* HAVE_OPENCL_DRM_BEIGNET */

static anta_hstha cl_mem_flags opencl_mem_flags_for_mapping(ចំនួនគត់ map_flags)
{
    ប្រសិនបើ ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        ត្រឡប់ CL_MEM_READ_WRITE;
    បើមិនដូច្នេះ ប្រសិនបើ (map_flags & AV_HWFRAME_MAP_READ)
        ត្រឡប់ CL_MEM_READ_ONLY;
    បើមិនដូច្នេះ ប្រសិនបើ (map_flags & AV_HWFRAME_MAP_WRITE)
        ត្រឡប់ CL_MEM_WRITE_ONLY;
    បើមិនដូច្នេះ
        ត្រឡប់ 0;
}

#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA

static void opencl_unmap_from_qsv(AVHWFramesContext *dst_fc,
                                  HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;
    ចំនួនគត់ p;

    av_log(dst_fc, AV_LOG_DEBUG, "Unmap QSV/VAAPI surface from OpenCL.\n");

    cle = device_priv->clEnqueueReleaseVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handles: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);

    សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
        cle = clReleaseMemObject(desc->planes[p]);
        ប្រសិនបើ (cle != CL_SUCCESS) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to release CL "
                   "image of plane %d of QSV/VAAPI surface: %d\n",
                   p, cle);
        }
    }

    av_free(desc);
}

static ចំនួនគត់ opencl_map_from_qsv(AVHWFramesContext *dst_fc, AVFrame *dst,
                               const AVFrame *src, ចំនួនគត់ flags)
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
    ចំនួនគត់ err, p;

#ប្រសិនបើ CONFIG_LIBMFX
    ប្រសិនបើ (src->format == AV_PIX_FMT_QSV) {
        void *base_handle;
        mfxFrameSurface1 *mfx_surface = (mfxFrameSurface1*)src->data[3];
        err = ff_qsv_get_surface_base_handle(mfx_surface,
                                             AV_HWDEVICE_TYPE_VAAPI,
                                             &base_handle);
        ប្រសិនបើ (err < 0)
            ត្រឡប់ err;
        va_surface = *(VASurfaceID *)base_handle;
    } បើមិនដូច្នេះ
#endif
        ប្រសិនបើ (src->format == AV_PIX_FMT_VAAPI) {
        va_surface = (VASurfaceID)(uintptr_t)src->data[3];
    } បើមិនដូច្នេះ {
        ត្រឡប់ AVERROR(ENOSYS);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ប្រសិនបើ (!cl_flags)
        ត្រឡប់ AVERROR(EINVAL);

    av_log(src_fc, AV_LOG_DEBUG, "Map QSV/VAAPI surface %#x to "
           "OpenCL.\n", va_surface);

    desc = av_mallocz(parimaa_na(*desc));
    ប្រសិនបើ (!desc)
        ត្រឡប់ AVERROR(ENOMEM);

    // The cl_intel_va_api_media_sharing extension only supports NV12
    // surfaces, so for now there are always exactly two planes.
    desc->nb_planes = 2;

    សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
        desc->planes[p] =
            device_priv->clCreateFromVA_APIMediaSurfaceINTEL(
                dst_dev->context, cl_flags, &va_surface, p, &cle);
        ប្រសិនបើ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                   "image from plane %d of QSV/VAAPI surface "
                   "%#x: %d.\n", p, va_surface, cle);
            err = AVERROR(EIO);
            goto fail;
        }

        dst->data[p] = (uint8_t*)desc->planes[p];
    }

    cle = device_priv->clEnqueueAcquireVA_APIMediaSurfacesINTEL(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handles: %d.\n", cle);
        err = AVERROR(EIO);
        goto fail;
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ប្រសិនបើ (err < 0)
        goto fail;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_qsv, desc);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    សម្រាប់ (p = 0; p < desc->nb_planes; p++)
        ប្រសិនបើ (desc->planes[p])
            clReleaseMemObject(desc->planes[p]);
    av_freep(&desc);
    memset(dst->data, 0, parimaa_na(dst->data));
    ត្រឡប់ err;
}

#endif

#ប្រសិនបើ HAVE_OPENCL_DXVA2

static void opencl_unmap_from_dxva2(AVHWFramesContext *dst_fc,
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
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
        ត្រឡប់;
    }

    opencl_wait_events(dst_fc, &event, 1);
}

static ចំនួនគត់ opencl_map_from_dxva2(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 const AVFrame *src, ចំនួនគត់ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ចំនួនគត់ err, i;

    av_log(dst_fc, AV_LOG_DEBUG, "Map DXVA2 surface %p to "
           "OpenCL.\n", src->data[3]);

    សម្រាប់ (i = 0; i < src_hwctx->nb_surfaces; i++) {
        ប្រសិនបើ (src_hwctx->surfaces[i] == (IDirect3DSurface9*)src->data[3])
            bha_nga;
    }
    ប្រសិនបើ (i >= src_hwctx->nb_surfaces) {
        av_log(dst_fc, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ត្រឡប់ AVERROR(EINVAL);
    }

    desc = &frames_priv->mapped_frames[i];

    cle = device_priv->clEnqueueAcquireDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ត្រឡប់ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ប្រសិនបើ (err < 0)
        goto fail;

    សម្រាប់ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_dxva2, desc);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    cle = device_priv->clEnqueueReleaseDX9MediaSurfacesKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, parimaa_na(dst->data));
    ត្រឡប់ err;
}

static ចំនួនគត់ opencl_frames_derive_from_dxva2(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ចំនួនគត់ flags)
{
    AVDXVA2FramesContext  *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext   *dst_dev = &device_priv->p;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ចំនួនគត់ err, i, p, nb_planes;

    ប្រសិនបើ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ត្រឡប់ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ប្រសិនបើ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for DXVA2 to OpenCL mapping.\n");
        ត្រឡប់ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ប្រសិនបើ (!cl_flags)
        ត្រឡប់ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_hwctx->nb_surfaces;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  parimaa_na(*frames_priv->mapped_frames));
    ប្រសិនបើ (!frames_priv->mapped_frames)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        cl_dx9_surface_info_khr surface_info = {
            .resource      = src_hwctx->surfaces[i],
            .shared_handle = NULL,
        };
        desc->nb_planes = nb_planes;
        សម្រាប់ (p = 0; p < nb_planes; p++) {
            desc->planes[p] =
                device_priv->clCreateFromDX9MediaSurfaceKHR(
                    dst_dev->context, cl_flags,
                    device_priv->dx9_media_adapter_type,
                    &surface_info, p, &cle);
            ប្រសិនបើ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of DXVA2 surface %d: %d.\n",
                       p, i, cle);
                err = AVERROR(EIO);
                goto fail;
            }
        }
    }

    ត្រឡប់ 0;

fail:
    សម្រាប់ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
            ប្រសិនបើ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ត្រឡប់ err;
}

#endif

#ប្រសិនបើ HAVE_OPENCL_D3D11

static void opencl_unmap_from_d3d11(AVHWFramesContext *dst_fc,
                                    HWMapDescriptor *hwmap)
{
    AVOpenCLFrameDescriptor    *desc = hwmap->priv;
    OpenCLDeviceContext *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext *frames_priv = dst_fc->hwctx;
    cl_event event;
    cl_int cle;

    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to release surface "
               "handle: %d.\n", cle);
    }

    opencl_wait_events(dst_fc, &event, 1);
}

static ចំនួនគត់ opencl_map_from_d3d11(AVHWFramesContext *dst_fc, AVFrame *dst,
                                 const AVFrame *src, ចំនួនគត់ flags)
{
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    AVOpenCLFrameDescriptor *desc;
    cl_event event;
    cl_int cle;
    ចំនួនគត់ err, index, i;

    index = (intptr_t)src->data[1];
    ប្រសិនបើ (index >= frames_priv->nb_mapped_frames) {
        av_log(dst_fc, AV_LOG_ERROR, "Texture array index out of range for "
               "mapping: %d >= %d.\n", index, frames_priv->nb_mapped_frames);
        ត្រឡប់ AVERROR(EINVAL);
    }

    av_log(dst_fc, AV_LOG_DEBUG, "Map D3D11 texture %d to OpenCL.\n",
           index);

    desc = &frames_priv->mapped_frames[index];

    cle = device_priv->clEnqueueAcquireD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle != CL_SUCCESS) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to acquire surface "
               "handle: %d.\n", cle);
        ត្រឡប់ AVERROR(EIO);
    }

    err = opencl_wait_events(dst_fc, &event, 1);
    ប្រសិនបើ (err < 0)
        goto fail;

    សម្រាប់ (i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t*)desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_d3d11, desc);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    cle = device_priv->clEnqueueReleaseD3D11ObjectsKHR(
        frames_priv->command_queue, desc->nb_planes, desc->planes,
        0, NULL, &event);
    ប្រសិនបើ (cle == CL_SUCCESS)
        opencl_wait_events(dst_fc, &event, 1);
    memset(dst->data, 0, parimaa_na(dst->data));
    ត្រឡប់ err;
}

static ចំនួនគត់ opencl_frames_derive_from_d3d11(AVHWFramesContext *dst_fc,
                                           AVHWFramesContext *src_fc, ចំនួនគត់ flags)
{
    AVD3D11VAFramesContext *src_hwctx = src_fc->hwctx;
    OpenCLDeviceContext  *device_priv = dst_fc->device_ctx->hwctx;
    AVOpenCLDeviceContext    *dst_dev = &device_priv->p;
    OpenCLFramesContext  *frames_priv = dst_fc->hwctx;
    cl_mem_flags cl_flags;
    cl_int cle;
    ចំនួនគត់ err, i, p, nb_planes;

    ប្រសិនបើ (src_fc->sw_format != AV_PIX_FMT_NV12) {
        av_log(dst_fc, AV_LOG_ERROR, "Only NV12 textures are supported "
               "for D3D11 to OpenCL mapping.\n");
        ត្រឡប់ AVERROR(EINVAL);
    }
    nb_planes = 2;

    ប្រសិនបើ (src_fc->initial_pool_size == 0) {
        av_log(dst_fc, AV_LOG_ERROR, "Only fixed-size pools are supported "
               "for D3D11 to OpenCL mapping.\n");
        ត្រឡប់ AVERROR(EINVAL);
    }

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ប្រសិនបើ (!cl_flags)
        ត្រឡប់ AVERROR(EINVAL);

    frames_priv->nb_mapped_frames = src_fc->initial_pool_size;

    frames_priv->mapped_frames =
        av_calloc(frames_priv->nb_mapped_frames,
                  parimaa_na(*frames_priv->mapped_frames));
    ប្រសិនបើ (!frames_priv->mapped_frames)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        desc->nb_planes = nb_planes;
        សម្រាប់ (p = 0; p < nb_planes; p++) {
            UINT subresource = 2 * i + p;

            desc->planes[p] =
                device_priv->clCreateFromD3D11Texture2DKHR(
                    dst_dev->context, cl_flags, src_hwctx->texture,
                    subresource, &cle);
            ប្រសិនបើ (!desc->planes[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL "
                       "image from plane %d of D3D texture "
                       "index %d (subresource %u): %d.\n",
                       p, i, (unsigned ចំនួនគត់)subresource, cle);
                err = AVERROR(EIO);
                goto fail;
            }
        }
    }

    ត្រឡប់ 0;

fail:
    សម្រាប់ (i = 0; i < frames_priv->nb_mapped_frames; i++) {
        AVOpenCLFrameDescriptor *desc = &frames_priv->mapped_frames[i];
        សម្រាប់ (p = 0; p < desc->nb_planes; p++) {
            ប្រសិនបើ (desc->planes[p])
                clReleaseMemObject(desc->planes[p]);
        }
    }
    av_freep(&frames_priv->mapped_frames);
    frames_priv->nb_mapped_frames = 0;
    ត្រឡប់ err;
}

#endif

#ប្រសិនបើ HAVE_OPENCL_DRM_ARM

typedef sa_nracanaa DRMARMtoOpenCLMapping {
    ចំនួនគត់ nb_objects;
    cl_mem object_buffers[AV_DRM_MAX_PLANES];
    ចំនួនគត់ nb_planes;
    cl_mem plane_images[AV_DRM_MAX_PLANES];
} DRMARMtoOpenCLMapping;

static void opencl_unmap_from_drm_arm(AVHWFramesContext *dst_fc,
                                      HWMapDescriptor *hwmap)
{
    DRMARMtoOpenCLMapping *mapping = hwmap->priv;
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < mapping->nb_planes; i++)
        clReleaseMemObject(mapping->plane_images[i]);

    សម្រាប់ (i = 0; i < mapping->nb_objects; i++)
        clReleaseMemObject(mapping->object_buffers[i]);

    av_free(mapping);
}

static ចំនួនគត់ opencl_map_from_drm_arm(AVHWFramesContext *dst_fc, AVFrame *dst,
                                   const AVFrame *src, ចំនួនគត់ flags)
{
    AVHWFramesContext *src_fc =
        (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;
    const AVDRMFrameDescriptor *desc;
    DRMARMtoOpenCLMapping *mapping = NULL;
    cl_mem_flags cl_flags;
    const cl_import_properties_arm props[3] = {
        CL_IMPORT_TYPE_ARM, CL_IMPORT_TYPE_DMA_BUF_ARM, 0,
    };
    cl_int cle;
    ចំនួនគត់ err, i, j;

    desc = (const AVDRMFrameDescriptor*)src->data[0];

    cl_flags = opencl_mem_flags_for_mapping(flags);
    ប្រសិនបើ (!cl_flags)
        ត្រឡប់ AVERROR(EINVAL);

    mapping = av_mallocz(parimaa_na(*mapping));
    ប្រសិនបើ (!mapping)
        ត្រឡប់ AVERROR(ENOMEM);

    mapping->nb_objects = desc->nb_objects;
    សម្រាប់ (i = 0; i < desc->nb_objects; i++) {
        ចំនួនគត់ fd = desc->objects[i].fd;

        av_log(dst_fc, AV_LOG_DEBUG, "Map DRM PRIME fd %d to OpenCL.\n", fd);

        ប្រសិនបើ (desc->objects[i].format_modifier) {
            av_log(dst_fc, AV_LOG_DEBUG, "Warning: object %d fd %d has "
                   "nonzero format modifier %"PRId64", result may not "
                   "be as expected.\n", i, fd,
                   desc->objects[i].format_modifier);
        }

        mapping->object_buffers[i] =
            clImportMemoryARM(dst_dev->context, cl_flags, props,
                              &fd, desc->objects[i].size, &cle);
        ប្រសិនបើ (!mapping->object_buffers[i]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create CL buffer "
                   "from object %d (fd %d, size %zu) of DRM frame: %d.\n",
                   i, fd, desc->objects[i].size, cle);
            err = AVERROR(EIO);
            goto fail;
        }
    }

    mapping->nb_planes = 0;
    សម្រាប់ (i = 0; i < desc->nb_layers; i++) {
        const AVDRMLayerDescriptor *layer = &desc->layers[i];

        សម្រាប់ (j = 0; j < layer->nb_planes; j++) {
            const AVDRMPlaneDescriptor *plane = &layer->planes[j];
            cl_mem plane_buffer;
            cl_image_format image_format;
            cl_image_desc   image_desc;
            cl_buffer_region region;
            ចំនួនគត់ p = mapping->nb_planes;

            err = opencl_get_plane_format(src_fc->sw_format, p,
                                          src_fc->width, src_fc->height,
                                          &image_format, &image_desc);
            ប្រសិនបើ (err < 0) {
                av_log(dst_fc, AV_LOG_ERROR, "Invalid plane %d (DRM "
                       "layer %d plane %d): %d.\n", p, i, j, err);
                goto fail;
            }

            region.origin = plane->offset;
            region.size   = image_desc.image_row_pitch *
                            image_desc.image_height;

            plane_buffer =
                clCreateSubBuffer(mapping->object_buffers[plane->object_index],
                                  cl_flags,
                                  CL_BUFFER_CREATE_TYPE_REGION,
                                  &region, &cle);
            ប្រសិនបើ (!plane_buffer) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create sub-buffer "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                goto fail;
            }

            image_desc.buffer = plane_buffer;

            mapping->plane_images[p] =
                clCreateImage(dst_dev->context, cl_flags,
                              &image_format, &image_desc, NULL, &cle);

            // Unreference the sub-buffer immediately - we don't need it
            // directly and a reference is held by the image.
            clReleaseMemObject(plane_buffer);

            ប្រសិនបើ (!mapping->plane_images[p]) {
                av_log(dst_fc, AV_LOG_ERROR, "Failed to create image "
                       "for plane %d: %d.\n", p, cle);
                err = AVERROR(EIO);
                goto fail;
            }

            ++mapping->nb_planes;
        }
    }

    សម្រាប់ (i = 0; i < mapping->nb_planes; i++)
        dst->data[i] = (uint8_t*)mapping->plane_images[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &opencl_unmap_from_drm_arm, mapping);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width  = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    សម្រាប់ (i = 0; i < mapping->nb_planes; i++) {
        clReleaseMemObject(mapping->plane_images[i]);
    }
    សម្រាប់ (i = 0; i < mapping->nb_objects; i++) {
        ប្រសិនបើ (mapping->object_buffers[i])
            clReleaseMemObject(mapping->object_buffers[i]);
    }
    av_free(mapping);
    memset(dst->data, 0, parimaa_na(dst->data));
    ត្រឡប់ err;
}

#endif

#ប្រសិនបើ HAVE_OPENCL_VIDEOTOOLBOX

static void opencl_unmap_from_vt(AVHWFramesContext *hwfc,
                                 HWMapDescriptor *hwmap)
{
    uint8_t *desc = hwmap->priv;
    opencl_pool_free(hwfc, desc);
}

static ចំនួនគត់ opencl_map_from_vt(AVHWFramesContext *dst_fc, AVFrame *dst,
                              const AVFrame *src, ចំនួនគត់ flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef) src->data[3];
    IOSurfaceRef io_surface_ref = CVPixelBufferGetIOSurface(pixbuf);
    cl_int err = 0;
    AVOpenCLFrameDescriptor *desc = NULL;
    AVOpenCLDeviceContext *dst_dev = dst_fc->device_ctx->hwctx;

    ប្រសិនបើ (!io_surface_ref) {
        av_log(dst_fc, AV_LOG_ERROR, "Failed to get IOSurfaceRef\n");
        ត្រឡប់ AVERROR_EXTERNAL;
    }

    desc = av_mallocz(parimaa_na(*desc));
    ប្រសិនបើ (!desc)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (ចំនួនគត់ p = 0;; p++) {
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
        ប្រសិនបើ (err == AVERROR(ENOENT))
            bha_nga;
        ប្រសិនបើ (err < 0)
            goto fail;

        desc->planes[p] = clCreateImageFromIOSurfaceWithPropertiesAPPLE(dst_dev->context,
                                                    opencl_mem_flags_for_mapping(flags),
                                                    &image_format, &image_desc,
                                                    props, &err);
        ប្រសិនបើ (!desc->planes[p]) {
            av_log(dst_fc, AV_LOG_ERROR, "Failed to create image from IOSurfaceRef\n");
            err = AVERROR(EIO);
            goto fail;
        }
        desc->nb_planes++;
    }

    សម្រាប់ (ចំនួនគត់ i = 0; i < desc->nb_planes; i++)
        dst->data[i] = (uint8_t *) desc->planes[i];

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                opencl_unmap_from_vt, desc);
    ប្រសិនបើ (err < 0)
        goto fail;

    dst->width = src->width;
    dst->height = src->height;

    ត្រឡប់ 0;

fail:
    សម្រាប់ (ចំនួនគត់ i = 0; i < desc->nb_planes; i++)
        clReleaseMemObject(desc->planes[i]);
    av_freep(&desc);
    ត្រឡប់ err;
}

#endif

static ចំនួនគត់ opencl_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           const AVFrame *src, ចំនួនគត់ flags)
{
    av_assert0(src->format == AV_PIX_FMT_OPENCL);
    ប្រសិនបើ (hwfc->sw_format != dst->format)
        ត្រឡប់ AVERROR(ENOSYS);
    ត្រឡប់ opencl_map_frame(hwfc, dst, src, flags);
}

static ចំនួនគត់ opencl_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         const AVFrame *src, ចំនួនគត់ flags)
{
    av_unused OpenCLDeviceContext *priv = hwfc->device_ctx->hwctx;
    av_assert0(dst->format == AV_PIX_FMT_OPENCL);
    switch (src->format) {
#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
    pak_sa AV_PIX_FMT_DRM_PRIME:
        ប្រសិនបើ (priv->beignet_drm_mapping_usable)
            ត្រឡប់ opencl_map_from_drm_beignet(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VAAPI_BEIGNET
    pak_sa AV_PIX_FMT_VAAPI:
        ប្រសិនបើ (priv->beignet_drm_mapping_usable)
            ត្រឡប់ opencl_map_from_vaapi(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    pak_sa AV_PIX_FMT_QSV:
    pak_sa AV_PIX_FMT_VAAPI:
        ប្រសិនបើ (priv->qsv_mapping_usable)
            ត្រឡប់ opencl_map_from_qsv(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_DXVA2
    pak_sa AV_PIX_FMT_DXVA2_VLD:
        ប្រសិនបើ (priv->dxva2_mapping_usable)
            ត្រឡប់ opencl_map_from_dxva2(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_D3D11
    pak_sa AV_PIX_FMT_D3D11:
        ប្រសិនបើ (priv->d3d11_mapping_usable)
            ត្រឡប់ opencl_map_from_d3d11(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
    pak_sa AV_PIX_FMT_DRM_PRIME:
        ប្រសិនបើ (priv->drm_arm_mapping_usable)
            ត្រឡប់ opencl_map_from_drm_arm(hwfc, dst, src, flags);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VIDEOTOOLBOX
    pak_sa AV_PIX_FMT_VIDEOTOOLBOX:
        ត្រឡប់ opencl_map_from_vt(hwfc, dst, src, flags);
#endif
    }
    ត្រឡប់ AVERROR(ENOSYS);
}

static ចំនួនគត់ opencl_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ចំនួនគត់ flags)
{
    av_unused OpenCLDeviceContext *priv = dst_fc->device_ctx->hwctx;
    switch (src_fc->device_ctx->type) {
#ប្រសិនបើ HAVE_OPENCL_DRM_BEIGNET
    pak_sa AV_HWDEVICE_TYPE_DRM:
        ប្រសិនបើ (!priv->beignet_drm_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VAAPI_BEIGNET
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        ប្រសិនបើ (!priv->beignet_drm_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VAAPI_INTEL_MEDIA
    pak_sa AV_HWDEVICE_TYPE_QSV:
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        ប្រសិនបើ (!priv->qsv_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        ប្រសិនបើ (!priv->dxva2_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        {
            ចំនួនគត់ err;
            err = opencl_frames_derive_from_dxva2(dst_fc, src_fc, flags);
            ប្រសិនបើ (err < 0)
                ត្រឡប់ err;
        }
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_D3D11
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        ប្រសិនបើ (!priv->d3d11_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        {
            ចំនួនគត់ err;
            err = opencl_frames_derive_from_d3d11(dst_fc, src_fc, flags);
            ប្រសិនបើ (err < 0)
                ត្រឡប់ err;
        }
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_DRM_ARM
    pak_sa AV_HWDEVICE_TYPE_DRM:
        ប្រសិនបើ (!priv->drm_arm_mapping_usable)
            ត្រឡប់ AVERROR(ENOSYS);
        bha_nga;
#endif
#ប្រសិនបើ HAVE_OPENCL_VIDEOTOOLBOX
    pak_sa AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
        bha_nga;
#endif
    default:
        ត្រឡប់ AVERROR(ENOSYS);
    }
    ត្រឡប់ opencl_frames_init_command_queue(dst_fc);
}

const HWContextType ff_hwcontext_type_opencl = {
    .type                   = AV_HWDEVICE_TYPE_OPENCL,
    .name                   = "OpenCL",

    .device_hwctx_size      = parimaa_na(OpenCLDeviceContext),
    .frames_hwctx_size      = parimaa_na(OpenCLFramesContext),

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

    .pix_fmts = (const ga_nanaa AVPixelFormat[]) {
        AV_PIX_FMT_OPENCL,
        AV_PIX_FMT_NONE
    },
};
