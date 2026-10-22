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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_derivation(AVBufferRef *src_ref, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src_name)
{
    ಎಣಿಕೆ AVHWDeviceType derived_type;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *derived_name;
    AVBufferRef *derived_ref = ಖಾಲಿ, *ಹಿಂಭಾಗ_ref = ಖಾಲಿ;
    AVHWDeviceContext *src_dev, *derived_dev;
    ಪೂರ್ಣಾಂಕ err;

    src_dev = (AVHWDeviceContext*)src_ref->ದತ್ತಾಂಶ;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ಆಗ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ಆದರೆ (derived_type == AV_HWDEVICE_TYPE_NONE)
            ನಿಲ್ಲಿಸು;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ಆದರೆ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            ಮುಂದುವರಿ;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->ದತ್ತಾಂಶ;
        ಆದರೆ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            ಹೋಗು fail;
        }

        ಆದರೆ (derived_type == src_dev->type) {
            ಆದರೆ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                ಹೋಗು fail;
            }
            av_ಬಫರ್_unref(&derived_ref);
            ಮುಂದುವರಿ;
        }

        err = av_hwdevice_ctx_create_derived(&ಹಿಂಭಾಗ_ref, src_dev->type,
                                             derived_ref, 0);
        ಆದರೆ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            ಹೋಗು fail;
        }

        ಆದರೆ (ಹಿಂಭಾಗ_ref->ದತ್ತಾಂಶ != src_ref->ದತ್ತಾಂಶ) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            ಹೋಗು fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_ಬಫರ್_unref(&derived_ref);
        av_ಬಫರ್_unref(&ಹಿಂಭಾಗ_ref);
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    av_ಬಫರ್_unref(&derived_ref);
    av_ಬಫರ್_unref(&ಹಿಂಭಾಗ_ref);
    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_device(ಎಣಿಕೆ AVHWDeviceType type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name,
                       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device, AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    ಪೂರ್ಣಾಂಕ err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ಆದರೆ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ಹಿಂತಿರುಗಿ 1;
    }

    dev = (AVHWDeviceContext*)ref->ದತ್ತಾಂಶ;
    ಆದರೆ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_ಬಫರ್_unref(&ref);
        ಹಿಂತಿರುಗಿ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_ಬಫರ್_unref(&ref);

    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಎಣಿಕೆ AVHWDeviceType type;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *possible_devices[5];
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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_device_type(ಎಣಿಕೆ AVHWDeviceType type)
{
    ಎಣಿಕೆ AVHWDeviceType check;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    ಪೂರ್ಣಾಂಕ i, j, ಸಿಕ್ಕಿತು, err;

    name = av_hwdevice_get_type_name(type);
    ಆದರೆ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ಹಿಂತಿರುಗಿ -1;
    }

    check = av_hwdevice_ಕಂಡುಹಿಡಿ_type_by_name(name);
    ಆದರೆ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ಹಿಂತಿರುಗಿ -1;
    }

    ಸಿಕ್ಕಿತು = 0;

    err = test_device(type, name, ಖಾಲಿ, ಖಾಲಿ, 0);
    ಆದರೆ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ಹಿಂತಿರುಗಿ -1;
    }
    ಆದರೆ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++ಸಿಕ್ಕಿತು;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ಆದರೆ (test_devices[i].type != type)
            ಮುಂದುವರಿ;

        ಗಾಗಿ (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ಖಾಲಿ, 0);
            ಆದರೆ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ಹಿಂತಿರುಗಿ -1;
            }
            ಆದರೆ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++ಸಿಕ್ಕಿತು;
            }
        }
    }

    ಹಿಂತಿರುಗಿ !ಸಿಕ್ಕಿತು;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಎಣಿಕೆ AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    ಪೂರ್ಣಾಂಕ pass, fail, skip, err;

    pass = fail = skip = 0;
    ಆಗ (1) {
        type = av_hwdevice_iterate_types(type);
        ಆದರೆ (type == AV_HWDEVICE_TYPE_NONE)
            ನಿಲ್ಲಿಸು;

        err = test_device_type(type);
        ಆದರೆ (err == 0)
            ++pass;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (err < 0)
            ++fail;
        ಇಲ್ಲದಿದ್ದರೆ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ಹಿಂತಿರುಗಿ fail > 0;
}
