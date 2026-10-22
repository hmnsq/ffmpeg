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

static puur_naa_nka test_derivation(AVBufferRef *src_ref, const var_na *src_name)
{
    ga_nanaa AVHWDeviceType derived_type;
    const var_na *derived_name;
    AVBufferRef *derived_ref = NULL, *back_ref = NULL;
    AVHWDeviceContext *src_dev, *derived_dev;
    puur_naa_nka err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ᨀᨛ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ᨀᨘ (derived_type == AV_HWDEVICE_TYPE_NONE)
            bha_nga;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ᨀᨘ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            continue;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        ᨀᨘ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            goto fail;
        }

        ᨀᨘ (derived_type == src_dev->type) {
            ᨀᨘ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                goto fail;
            }
            av_buffer_unref(&derived_ref);
            continue;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        ᨀᨘ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            goto fail;
        }

        ᨀᨘ (back_ref->data != src_ref->data) {
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

    ᨀᨘᨒ 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    ᨀᨘᨒ -1;
}

static puur_naa_nka test_device(ga_nanaa AVHWDeviceType type, const var_na *name,
                       const var_na *device, AVDictionary *opts, puur_naa_nka flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    puur_naa_nka err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ᨀᨘ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ᨀᨘᨒ 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    ᨀᨘ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        ᨀᨘᨒ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    ᨀᨘᨒ err;
}

static const sa_nracanaa {
    ga_nanaa AVHWDeviceType type;
    const var_na *possible_devices[5];
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

static puur_naa_nka test_device_type(ga_nanaa AVHWDeviceType type)
{
    ga_nanaa AVHWDeviceType check;
    const var_na *name;
    puur_naa_nka i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    ᨀᨘ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ᨀᨘᨒ -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    ᨀᨘ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ᨀᨘᨒ -1;
    }

    found = 0;

    err = test_device(type, name, NULL, NULL, 0);
    ᨀᨘ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ᨀᨘᨒ -1;
    }
    ᨀᨘ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ᨀᨘ (test_devices[i].type != type)
            continue;

        for (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              NULL, 0);
            ᨀᨘ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ᨀᨘᨒ -1;
            }
            ᨀᨘ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    ᨀᨘᨒ !found;
}

puur_naa_nka main(void)
{
    ga_nanaa AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    puur_naa_nka pass, fail, skip, err;

    pass = fail = skip = 0;
    ᨀᨛ (1) {
        type = av_hwdevice_iterate_types(type);
        ᨀᨘ (type == AV_HWDEVICE_TYPE_NONE)
            bha_nga;

        err = test_device_type(type);
        ᨀᨘ (err == 0)
            ++pass;
        ᨀᨘᨁ ᨀᨘ (err < 0)
            ++fail;
        ᨀᨘᨁ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ᨀᨘᨒ fail > 0;
}
