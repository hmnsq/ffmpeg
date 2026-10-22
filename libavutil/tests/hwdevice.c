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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_derivation(AVBufferRef *src_ref, ಧ್ರುವ ವರ್ಣ *src_name)
{
    ಗಣನಾ AVHWDeviceType derived_type;
    ಧ್ರುವ ವರ್ಣ *derived_name;
    AVBufferRef *derived_ref = ರಿಕ್ತ, *back_ref = ರಿಕ್ತ;
    AVHWDeviceContext *src_dev, *derived_dev;
    ಪೂರ್ಣಾಙ್ಕ err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ಯಾವತ್ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ಯದಿ (derived_type == AV_HWDEVICE_TYPE_NONE)
            ಭಙ್ಗ;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ಯದಿ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            ಅನುವರ್ತ;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        ಯದಿ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            ಗಚ್ಛ fail;
        }

        ಯದಿ (derived_type == src_dev->type) {
            ಯದಿ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                ಗಚ್ಛ fail;
            }
            av_buffer_unref(&derived_ref);
            ಅನುವರ್ತ;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        ಯದಿ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            ಗಚ್ಛ fail;
        }

        ಯದಿ (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            ಗಚ್ಛ fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    ಪ್ರತ್ಯಾಗಮ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_device(ಗಣನಾ AVHWDeviceType type, ಧ್ರುವ ವರ್ಣ *name,
                       ಧ್ರುವ ವರ್ಣ *device, AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    ಪೂರ್ಣಾಙ್ಕ err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ಯದಿ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ಪ್ರತ್ಯಾಗಮ 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    ಯದಿ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಗಣನಾ AVHWDeviceType type;
    ಧ್ರುವ ವರ್ಣ *possible_devices[5];
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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_device_type(ಗಣನಾ AVHWDeviceType type)
{
    ಗಣನಾ AVHWDeviceType check;
    ಧ್ರುವ ವರ್ಣ *name;
    ಪೂರ್ಣಾಙ್ಕ i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    ಯದಿ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    ಯದಿ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    found = 0;

    err = test_device(type, name, ರಿಕ್ತ, ರಿಕ್ತ, 0);
    ಯದಿ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ಪ್ರತ್ಯಾಗಮ -1;
    }
    ಯದಿ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ಯದಿ (test_devices[i].type != type)
            ಅನುವರ್ತ;

        ಪ್ರತಿ (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ರಿಕ್ತ, 0);
            ಯದಿ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ಪ್ರತ್ಯಾಗಮ -1;
            }
            ಯದಿ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ !found;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ಗಣನಾ AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    ಪೂರ್ಣಾಙ್ಕ pass, fail, skip, err;

    pass = fail = skip = 0;
    ಯಾವತ್ (1) {
        type = av_hwdevice_iterate_types(type);
        ಯದಿ (type == AV_HWDEVICE_TYPE_NONE)
            ಭಙ್ಗ;

        err = test_device_type(type);
        ಯದಿ (err == 0)
            ++pass;
        ಅನ್ಯಥಾ ಯದಿ (err < 0)
            ++fail;
        ಅನ್ಯಥಾ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ಪ್ರತ್ಯಾಗಮ fail > 0;
}
