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

#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/hwcontext.h"

স্থির পূর্ণসংখ্যা test_derivation(AVBufferRef *src_ref, ধ্রুবক অক্ষর *src_name)
{
    গণনা AVHWDeviceType derived_type;
    ধ্রুবক অক্ষর *derived_name;
    AVBufferRef *derived_ref = ফাঁকা, *back_ref = ফাঁকা;
    AVHWDeviceContext *src_dev, *derived_dev;
    পূর্ণসংখ্যা err;

    src_dev = (AVHWDeviceContext*)src_ref->তথ্য;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    যখন (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        যদি (derived_type == AV_HWDEVICE_TYPE_NONE)
            বিরতি;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        যদি (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            চালু;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->তথ্য;
        যদি (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            যাও fail;
        }

        যদি (derived_type == src_dev->type) {
            যদি (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                যাও fail;
            }
            av_বাফার_unref(&derived_ref);
            চালু;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        যদি (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            যাও fail;
        }

        যদি (back_ref->তথ্য != src_ref->তথ্য) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            যাও fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_বাফার_unref(&derived_ref);
        av_বাফার_unref(&back_ref);
    }

    ফেরত 0;

fail:
    av_বাফার_unref(&derived_ref);
    av_বাফার_unref(&back_ref);
    ফেরত -1;
}

স্থির পূর্ণসংখ্যা test_device(গণনা AVHWDeviceType type, ধ্রুবক অক্ষর *name,
                       ধ্রুবক অক্ষর *device, AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    পূর্ণসংখ্যা err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    যদি (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ফেরত 1;
    }

    dev = (AVHWDeviceContext*)ref->তথ্য;
    যদি (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_বাফার_unref(&ref);
        ফেরত -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_বাফার_unref(&ref);

    ফেরত err;
}

স্থির ধ্রুবক কাঠামো {
    গণনা AVHWDeviceType type;
    ধ্রুবক অক্ষর *possible_devices[5];
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

স্থির পূর্ণসংখ্যা test_device_type(গণনা AVHWDeviceType type)
{
    গণনা AVHWDeviceType check;
    ধ্রুবক অক্ষর *name;
    পূর্ণসংখ্যা i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    যদি (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ফেরত -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    যদি (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ফেরত -1;
    }

    found = 0;

    err = test_device(type, name, ফাঁকা, ফাঁকা, 0);
    যদি (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ফেরত -1;
    }
    যদি (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    জন্য (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        যদি (test_devices[i].type != type)
            চালু;

        জন্য (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ফাঁকা, 0);
            যদি (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ফেরত -1;
            }
            যদি (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    ফেরত !found;
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    গণনা AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    পূর্ণসংখ্যা pass, fail, skip, err;

    pass = fail = skip = 0;
    যখন (1) {
        type = av_hwdevice_iterate_types(type);
        যদি (type == AV_HWDEVICE_TYPE_NONE)
            বিরতি;

        err = test_device_type(type);
        যদি (err == 0)
            ++pass;
        অন্যথা যদি (err < 0)
            ++fail;
        অন্যথা
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ফেরত fail > 0;
}
