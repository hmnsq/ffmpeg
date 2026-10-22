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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext.h"

ਸਥਿਰ ਪੂਰਨ test_derivation(AVBufferRef *src_ref, ਅਚਲ ਅੱਖਰ *src_name)
{
    ਗਿਣਤੀ AVHWDeviceType derived_type;
    ਅਚਲ ਅੱਖਰ *derived_name;
    AVBufferRef *derived_ref = ਨਿਰਾ, *ਪਿੱਠ_ref = ਨਿਰਾ;
    AVHWDeviceContext *src_dev, *derived_dev;
    ਪੂਰਨ err;

    src_dev = (AVHWDeviceContext*)src_ref->ਅੰਕੜੇ;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ਜਦੋਂ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ਜੇ (derived_type == AV_HWDEVICE_TYPE_NONE)
            ਰੋਕੋ;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ਜੇ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            ਜਾਰੀ;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->ਅੰਕੜੇ;
        ਜੇ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            ਜਾਓ fail;
        }

        ਜੇ (derived_type == src_dev->type) {
            ਜੇ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                ਜਾਓ fail;
            }
            av_ਬਫਰ_unref(&derived_ref);
            ਜਾਰੀ;
        }

        err = av_hwdevice_ctx_create_derived(&ਪਿੱਠ_ref, src_dev->type,
                                             derived_ref, 0);
        ਜੇ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            ਜਾਓ fail;
        }

        ਜੇ (ਪਿੱਠ_ref->ਅੰਕੜੇ != src_ref->ਅੰਕੜੇ) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            ਜਾਓ fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_ਬਫਰ_unref(&derived_ref);
        av_ਬਫਰ_unref(&ਪਿੱਠ_ref);
    }

    ਵਾਪਸ 0;

fail:
    av_ਬਫਰ_unref(&derived_ref);
    av_ਬਫਰ_unref(&ਪਿੱਠ_ref);
    ਵਾਪਸ -1;
}

ਸਥਿਰ ਪੂਰਨ test_device(ਗਿਣਤੀ AVHWDeviceType type, ਅਚਲ ਅੱਖਰ *name,
                       ਅਚਲ ਅੱਖਰ *device, AVDictionary *opts, ਪੂਰਨ flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    ਪੂਰਨ err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ਜੇ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ਵਾਪਸ 1;
    }

    dev = (AVHWDeviceContext*)ref->ਅੰਕੜੇ;
    ਜੇ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_ਬਫਰ_unref(&ref);
        ਵਾਪਸ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_ਬਫਰ_unref(&ref);

    ਵਾਪਸ err;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਗਿਣਤੀ AVHWDeviceType type;
    ਅਚਲ ਅੱਖਰ *possible_devices[5];
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

ਸਥਿਰ ਪੂਰਨ test_device_type(ਗਿਣਤੀ AVHWDeviceType type)
{
    ਗਿਣਤੀ AVHWDeviceType check;
    ਅਚਲ ਅੱਖਰ *name;
    ਪੂਰਨ i, j, ਮਿਲਿਆ, err;

    name = av_hwdevice_get_type_name(type);
    ਜੇ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ਵਾਪਸ -1;
    }

    check = av_hwdevice_ਲੱਭੋ_type_by_name(name);
    ਜੇ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ਵਾਪਸ -1;
    }

    ਮਿਲਿਆ = 0;

    err = test_device(type, name, ਨਿਰਾ, ਨਿਰਾ, 0);
    ਜੇ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ਵਾਪਸ -1;
    }
    ਜੇ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++ਮਿਲਿਆ;
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ਜੇ (test_devices[i].type != type)
            ਜਾਰੀ;

        ਲਈ (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ਨਿਰਾ, 0);
            ਜੇ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ਵਾਪਸ -1;
            }
            ਜੇ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++ਮਿਲਿਆ;
            }
        }
    }

    ਵਾਪਸ !ਮਿਲਿਆ;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਗਿਣਤੀ AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    ਪੂਰਨ pass, fail, skip, err;

    pass = fail = skip = 0;
    ਜਦੋਂ (1) {
        type = av_hwdevice_iterate_types(type);
        ਜੇ (type == AV_HWDEVICE_TYPE_NONE)
            ਰੋਕੋ;

        err = test_device_type(type);
        ਜੇ (err == 0)
            ++pass;
        ਨਹੀਂਤਾਂ ਜੇ (err < 0)
            ++fail;
        ਨਹੀਂਤਾਂ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ਵਾਪਸ fail > 0;
}
