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

#include <stdio.h>

#include "libavutil/hwcontext.h"

static 정수 test_derivation(AVBufferRef *src_ref, const char *src_name)
{
    enum AVHWDeviceType derived_type;
    const char *derived_name;
    AVBufferRef *derived_ref = NULL, *back_ref = NULL;
    AVHWDeviceContext *src_dev, *derived_dev;
    정수 err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    동안 (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        만약 (derived_type == AV_HWDEVICE_TYPE_NONE)
            break;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        만약 (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            continue;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        만약 (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            goto fail;
        }

        만약 (derived_type == src_dev->type) {
            만약 (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                goto fail;
            }
            av_buffer_unref(&derived_ref);
            continue;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        만약 (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            goto fail;
        }

        만약 (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            goto fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    반환 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    반환 -1;
}

static 정수 test_device(enum AVHWDeviceType type, const char *name,
                       const char *device, AVDictionary *opts, 정수 flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    정수 err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    만약 (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        반환 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    만약 (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        반환 -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    반환 err;
}

static const struct {
    enum AVHWDeviceType type;
    const char *possible_devices[5];
} test_devices[] = {
    { AV_HWDEVICE_TYPE_CUDA,
      { "0", "1", "2" } },
    { AV_HWDEVICE_TYPE_DRM,
      { "/dev/dri/card0", "/dev/dri/card1",
        "/dev/dri/renderD128", "/dev/dri/renderD129" } },
    { AV_HWDEVICE_TYPE_DXVA2,
      { "0", "1", "2" } },
    { AV_HWDEVICE_TYPE_D3D11VA,
      { "0", "1", "2" } },
    { AV_HWDEVICE_TYPE_D3D12VA,
      { "0", "1", "2" } },
    { AV_HWDEVICE_TYPE_OPENCL,
      { "0.0", "0.1", "1.0", "1.1" } },
    { AV_HWDEVICE_TYPE_VAAPI,
      { "/dev/dri/renderD128", "/dev/dri/renderD129", ":0", "0", "1" } },
};

static 정수 test_device_type(enum AVHWDeviceType type)
{
    enum AVHWDeviceType check;
    const char *name;
    정수 i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    만약 (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        반환 -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    만약 (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        반환 -1;
    }

    found = 0;

    err = test_device(type, name, NULL, NULL, 0);
    만약 (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        반환 -1;
    }
    만약 (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    위해 (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        만약 (test_devices[i].type != type)
            continue;

        위해 (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              NULL, 0);
            만약 (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                반환 -1;
            }
            만약 (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    반환 !found;
}

정수 main(void)
{
    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    정수 pass, fail, skip, err;

    pass = fail = skip = 0;
    동안 (1) {
        type = av_hwdevice_iterate_types(type);
        만약 (type == AV_HWDEVICE_TYPE_NONE)
            break;

        err = test_device_type(type);
        만약 (err == 0)
            ++pass;
        아니면 만약 (err < 0)
            ++fail;
        아니면
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    반환 fail > 0;
}
