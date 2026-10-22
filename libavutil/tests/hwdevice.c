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

#شامل <stdio.h>

#شامل "libavutil/hwcontext.h"

ساکن صحیح test_derivation(AVBufferRef *src_ref, ثابت حرف *src_name)
{
    شمار AVHWDeviceType derived_type;
    ثابت حرف *derived_name;
    AVBufferRef *derived_ref = تہی, *عقب_ref = تہی;
    AVHWDeviceContext *src_dev, *derived_dev;
    صحیح err;

    src_dev = (AVHWDeviceContext*)src_ref->ڈیٹا;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    جب (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        اگر (derived_type == AV_HWDEVICE_TYPE_NONE)
            توڑو;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        اگر (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            جاری;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->ڈیٹا;
        اگر (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            جاؤ fail;
        }

        اگر (derived_type == src_dev->type) {
            اگر (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                جاؤ fail;
            }
            av_بفر_unref(&derived_ref);
            جاری;
        }

        err = av_hwdevice_ctx_create_derived(&عقب_ref, src_dev->type,
                                             derived_ref, 0);
        اگر (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            جاؤ fail;
        }

        اگر (عقب_ref->ڈیٹا != src_ref->ڈیٹا) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            جاؤ fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_بفر_unref(&derived_ref);
        av_بفر_unref(&عقب_ref);
    }

    واپس 0;

fail:
    av_بفر_unref(&derived_ref);
    av_بفر_unref(&عقب_ref);
    واپس -1;
}

ساکن صحیح test_device(شمار AVHWDeviceType type, ثابت حرف *name,
                       ثابت حرف *device, AVDictionary *opts, صحیح flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    صحیح err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    اگر (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        واپس 1;
    }

    dev = (AVHWDeviceContext*)ref->ڈیٹا;
    اگر (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_بفر_unref(&ref);
        واپس -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_بفر_unref(&ref);

    واپس err;
}

ساکن ثابت ساخت {
    شمار AVHWDeviceType type;
    ثابت حرف *possible_devices[5];
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

ساکن صحیح test_device_type(شمار AVHWDeviceType type)
{
    شمار AVHWDeviceType check;
    ثابت حرف *name;
    صحیح i, j, ملا, err;

    name = av_hwdevice_get_type_name(type);
    اگر (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        واپس -1;
    }

    check = av_hwdevice_ڈھونڈو_type_by_name(name);
    اگر (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        واپس -1;
    }

    ملا = 0;

    err = test_device(type, name, تہی, تہی, 0);
    اگر (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        واپس -1;
    }
    اگر (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++ملا;
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        اگر (test_devices[i].type != type)
            جاری;

        برائے (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              تہی, 0);
            اگر (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                واپس -1;
            }
            اگر (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++ملا;
            }
        }
    }

    واپس !ملا;
}

صحیح مین(خالی)
{
    شمار AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    صحیح pass, fail, skip, err;

    pass = fail = skip = 0;
    جب (1) {
        type = av_hwdevice_iterate_types(type);
        اگر (type == AV_HWDEVICE_TYPE_NONE)
            توڑو;

        err = test_device_type(type);
        اگر (err == 0)
            ++pass;
        ورنہ اگر (err < 0)
            ++fail;
        ورنہ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    واپس fail > 0;
}
