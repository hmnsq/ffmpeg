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

#ଅନ୍ତର୍ଭାଵ <stdio.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/hwcontext.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_derivation(AVBufferRef *src_ref, ଅଚଳ ଅକ୍ଷର *src_name)
{
    ଗଣନା AVHWDeviceType derived_type;
    ଅଚଳ ଅକ୍ଷର *derived_name;
    AVBufferRef *derived_ref = ଖାଲି, *back_ref = ଖାଲି;
    AVHWDeviceContext *src_dev, *derived_dev;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ଯେତେବେଳେ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ଯଦି (derived_type == AV_HWDEVICE_TYPE_NONE)
            ଭାଙ୍ଗ;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ଯଦି (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            ଜାରି;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        ଯଦି (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            ଯାଅ fail;
        }

        ଯଦି (derived_type == src_dev->type) {
            ଯଦି (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                ଯାଅ fail;
            }
            av_buffer_unref(&derived_ref);
            ଜାରି;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        ଯଦି (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            ଯାଅ fail;
        }

        ଯଦି (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            ଯାଅ fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    ଫେରନ୍ତୁ 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    ଫେରନ୍ତୁ -1;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_device(ଗଣନା AVHWDeviceType type, ଅଚଳ ଅକ୍ଷର *name,
                       ଅଚଳ ଅକ୍ଷର *device, AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ଯଦି (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        ଫେରନ୍ତୁ 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    ଯଦି (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        ଫେରନ୍ତୁ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଗଣନା AVHWDeviceType type;
    ଅଚଳ ଅକ୍ଷର *possible_devices[5];
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

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_device_type(ଗଣନା AVHWDeviceType type)
{
    ଗଣନା AVHWDeviceType check;
    ଅଚଳ ଅକ୍ଷର *name;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    ଯଦି (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        ଫେରନ୍ତୁ -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    ଯଦି (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        ଫେରନ୍ତୁ -1;
    }

    found = 0;

    err = test_device(type, name, ଖାଲି, ଖାଲି, 0);
    ଯଦି (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        ଫେରନ୍ତୁ -1;
    }
    ଯଦି (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ଯଦି (test_devices[i].type != type)
            ଜାରି;

        ପାଇଁ (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ଖାଲି, 0);
            ଯଦି (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                ଫେରନ୍ତୁ -1;
            }
            ଯଦି (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    ଫେରନ୍ତୁ !found;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ଗଣନା AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pass, fail, skip, err;

    pass = fail = skip = 0;
    ଯେତେବେଳେ (1) {
        type = av_hwdevice_iterate_types(type);
        ଯଦି (type == AV_HWDEVICE_TYPE_NONE)
            ଭାଙ୍ଗ;

        err = test_device_type(type);
        ଯଦି (err == 0)
            ++pass;
        ଅନ୍ୟଥା ଯଦି (err < 0)
            ++fail;
        ଅନ୍ୟଥା
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    ଫେରନ୍ତୁ fail > 0;
}
