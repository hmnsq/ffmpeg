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

#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/hwcontext.h"

நிலையான முழு test_derivation(AVBufferRef *src_ref, மாறிலி எழுத்து *src_name)
{
    எண்ணிக்கை AVHWDeviceType derived_type;
    மாறிலி எழுத்து *derived_name;
    AVBufferRef *derived_ref = வெற்று, *back_ref = வெற்று;
    AVHWDeviceContext *src_dev, *derived_dev;
    முழு err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    போது (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        எனில் (derived_type == AV_HWDEVICE_TYPE_NONE)
            நிறுத்து;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        எனில் (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            தொடர்;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        எனில் (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            செல் fail;
        }

        எனில் (derived_type == src_dev->type) {
            எனில் (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                செல் fail;
            }
            av_buffer_unref(&derived_ref);
            தொடர்;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        எனில் (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            செல் fail;
        }

        எனில் (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            செல் fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    திரும்பு 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    திரும்பு -1;
}

நிலையான முழு test_device(எண்ணிக்கை AVHWDeviceType type, மாறிலி எழுத்து *name,
                       மாறிலி எழுத்து *device, AVDictionary *opts, முழு flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    முழு err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    எனில் (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        திரும்பு 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    எனில் (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        திரும்பு -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    திரும்பு err;
}

நிலையான மாறிலி கட்டமைப்பு {
    எண்ணிக்கை AVHWDeviceType type;
    மாறிலி எழுத்து *possible_devices[5];
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

நிலையான முழு test_device_type(எண்ணிக்கை AVHWDeviceType type)
{
    எண்ணிக்கை AVHWDeviceType check;
    மாறிலி எழுத்து *name;
    முழு i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    எனில் (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        திரும்பு -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    எனில் (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        திரும்பு -1;
    }

    found = 0;

    err = test_device(type, name, வெற்று, வெற்று, 0);
    எனில் (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        திரும்பு -1;
    }
    எனில் (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        எனில் (test_devices[i].type != type)
            தொடர்;

        க்கு (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              வெற்று, 0);
            எனில் (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                திரும்பு -1;
            }
            எனில் (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    திரும்பு !found;
}

முழு முதன்மை(வெறுமை)
{
    எண்ணிக்கை AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    முழு pass, fail, skip, err;

    pass = fail = skip = 0;
    போது (1) {
        type = av_hwdevice_iterate_types(type);
        எனில் (type == AV_HWDEVICE_TYPE_NONE)
            நிறுத்து;

        err = test_device_type(type);
        எனில் (err == 0)
            ++pass;
        இல்லையெனில் எனில் (err < 0)
            ++fail;
        இல்லையெனில்
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    திரும்பு fail > 0;
}
