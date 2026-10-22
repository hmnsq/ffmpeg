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

#ضمن <stdio.h>

#ضمن "libavutil/hwcontext.h"

ساكن صحيح test_derivation(AVBufferRef *src_ref, ثابت حرف *src_name)
{
    تعداد AVHWDeviceType derived_type;
    ثابت حرف *derived_name;
    AVBufferRef *derived_ref = عدم, *back_ref = عدم;
    AVHWDeviceContext *src_dev, *derived_dev;
    صحيح err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    כלעוד (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        אם (derived_type == AV_HWDEVICE_TYPE_NONE)
            اكسر;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        אם (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            استمر;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        אם (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            اذهب fail;
        }

        אם (derived_type == src_dev->type) {
            אם (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                اذهب fail;
            }
            av_buffer_unref(&derived_ref);
            استمر;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        אם (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            اذهب fail;
        }

        אם (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            اذهب fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    החזר 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    החזר -1;
}

ساكن صحيح test_device(تعداد AVHWDeviceType type, ثابت حرف *name,
                       ثابت حرف *device, AVDictionary *opts, صحيح flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    صحيح err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    אם (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        החזר 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    אם (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        החזר -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    החזר err;
}

ساكن ثابت بنية {
    تعداد AVHWDeviceType type;
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

ساكن صحيح test_device_type(تعداد AVHWDeviceType type)
{
    تعداد AVHWDeviceType check;
    ثابت حرف *name;
    صحيح i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    אם (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        החזר -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    אם (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        החזר -1;
    }

    found = 0;

    err = test_device(type, name, عدم, عدم, 0);
    אם (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        החזר -1;
    }
    אם (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    עבור (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        אם (test_devices[i].type != type)
            استمر;

        עבור (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              عدم, 0);
            אם (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                החזר -1;
            }
            אם (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    החזר !found;
}

صحيح main(فراغ)
{
    تعداد AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    صحيح pass, fail, skip, err;

    pass = fail = skip = 0;
    כלעוד (1) {
        type = av_hwdevice_iterate_types(type);
        אם (type == AV_HWDEVICE_TYPE_NONE)
            اكسر;

        err = test_device_type(type);
        אם (err == 0)
            ++pass;
        אחרת אם (err < 0)
            ++fail;
        אחרת
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    החזר fail > 0;
}
