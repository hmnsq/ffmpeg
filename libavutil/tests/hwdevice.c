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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/hwcontext.h"

स्थिर पूर्णाङ्क test_derivation(AVBufferRef *src_ref, ध्रुव वर्ण *src_name)
{
    गणना AVHWDeviceType derived_type;
    ध्रुव वर्ण *derived_name;
    AVBufferRef *derived_ref = रिक्त, *back_ref = रिक्त;
    AVHWDeviceContext *src_dev, *derived_dev;
    पूर्णाङ्क err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    यावत् (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        यदि (derived_type == AV_HWDEVICE_TYPE_NONE)
            भङ्ग;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        यदि (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            अनुवर्त;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        यदि (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            गच्छ fail;
        }

        यदि (derived_type == src_dev->type) {
            यदि (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                गच्छ fail;
            }
            av_buffer_unref(&derived_ref);
            अनुवर्त;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        यदि (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            गच्छ fail;
        }

        यदि (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            गच्छ fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    प्रत्यागम 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    प्रत्यागम -1;
}

स्थिर पूर्णाङ्क test_device(गणना AVHWDeviceType type, ध्रुव वर्ण *name,
                       ध्रुव वर्ण *device, AVDictionary *opts, पूर्णाङ्क flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    पूर्णाङ्क err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    यदि (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        प्रत्यागम 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    यदि (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        प्रत्यागम -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    प्रत्यागम err;
}

स्थिर ध्रुव संरचना {
    गणना AVHWDeviceType type;
    ध्रुव वर्ण *possible_devices[5];
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

स्थिर पूर्णाङ्क test_device_type(गणना AVHWDeviceType type)
{
    गणना AVHWDeviceType check;
    ध्रुव वर्ण *name;
    पूर्णाङ्क i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    यदि (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        प्रत्यागम -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    यदि (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        प्रत्यागम -1;
    }

    found = 0;

    err = test_device(type, name, रिक्त, रिक्त, 0);
    यदि (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        प्रत्यागम -1;
    }
    यदि (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        यदि (test_devices[i].type != type)
            अनुवर्त;

        प्रति (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              रिक्त, 0);
            यदि (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                प्रत्यागम -1;
            }
            यदि (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    प्रत्यागम !found;
}

पूर्णाङ्क main(शून्य)
{
    गणना AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    पूर्णाङ्क pass, fail, skip, err;

    pass = fail = skip = 0;
    यावत् (1) {
        type = av_hwdevice_iterate_types(type);
        यदि (type == AV_HWDEVICE_TYPE_NONE)
            भङ्ग;

        err = test_device_type(type);
        यदि (err == 0)
            ++pass;
        अन्यथा यदि (err < 0)
            ++fail;
        अन्यथा
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    प्रत्यागम fail > 0;
}
