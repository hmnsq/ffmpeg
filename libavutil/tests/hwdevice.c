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

ایستا صحیح test_derivation(AVBufferRef *src_ref, ثابت نویسه *src_name)
{
    شمارش AVHWDeviceType derived_type;
    ثابت نویسه *derived_name;
    AVBufferRef *derived_ref = پوچ, *back_ref = پوچ;
    AVHWDeviceContext *src_dev, *derived_dev;
    صحیح err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    وقتی (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        اگر (derived_type == AV_HWDEVICE_TYPE_NONE)
            بشکن;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        اگر (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            ادامه;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        اگر (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            برو fail;
        }

        اگر (derived_type == src_dev->type) {
            اگر (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                برو fail;
            }
            av_buffer_unref(&derived_ref);
            ادامه;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        اگر (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            برو fail;
        }

        اگر (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            برو fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    بازگشت 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    بازگشت -1;
}

ایستا صحیح test_device(شمارش AVHWDeviceType type, ثابت نویسه *name,
                       ثابت نویسه *device, AVDictionary *opts, صحیح flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    صحیح err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    اگر (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        بازگشت 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    اگر (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        بازگشت -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    بازگشت err;
}

ایستا ثابت ساختار {
    شمارش AVHWDeviceType type;
    ثابت نویسه *possible_devices[5];
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

ایستا صحیح test_device_type(شمارش AVHWDeviceType type)
{
    شمارش AVHWDeviceType check;
    ثابت نویسه *name;
    صحیح i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    اگر (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        بازگشت -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    اگر (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        بازگشت -1;
    }

    found = 0;

    err = test_device(type, name, پوچ, پوچ, 0);
    اگر (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        بازگشت -1;
    }
    اگر (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        اگر (test_devices[i].type != type)
            ادامه;

        برای (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              پوچ, 0);
            اگر (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                بازگشت -1;
            }
            اگر (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    بازگشت !found;
}

صحیح اصلی(تهی)
{
    شمارش AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    صحیح pass, fail, skip, err;

    pass = fail = skip = 0;
    وقتی (1) {
        type = av_hwdevice_iterate_types(type);
        اگر (type == AV_HWDEVICE_TYPE_NONE)
            بشکن;

        err = test_device_type(type);
        اگر (err == 0)
            ++pass;
        وگرنه اگر (err < 0)
            ++fail;
        وگرنه
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    بازگشت fail > 0;
}
