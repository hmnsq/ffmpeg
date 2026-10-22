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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/hwcontext.h"

స్థిర పూర్ణాంకం test_derivation(AVBufferRef *src_ref, స్థిరరాశి అక్షరం *src_name)
{
    గణన AVHWDeviceType derived_type;
    స్థిరరాశి అక్షరం *derived_name;
    AVBufferRef *derived_ref = ఖాళీ, *వెనుక_ref = ఖాళీ;
    AVHWDeviceContext *src_dev, *derived_dev;
    పూర్ణాంకం err;

    src_dev = (AVHWDeviceContext*)src_ref->దత్తాంశం;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    అయితే (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        ఒకవేళ (derived_type == AV_HWDEVICE_TYPE_NONE)
            ఆపు;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        ఒకవేళ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            కొనసాగు;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->దత్తాంశం;
        ఒకవేళ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            వెళ్ళు fail;
        }

        ఒకవేళ (derived_type == src_dev->type) {
            ఒకవేళ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                వెళ్ళు fail;
            }
            av_బఫరు_unref(&derived_ref);
            కొనసాగు;
        }

        err = av_hwdevice_ctx_create_derived(&వెనుక_ref, src_dev->type,
                                             derived_ref, 0);
        ఒకవేళ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            వెళ్ళు fail;
        }

        ఒకవేళ (వెనుక_ref->దత్తాంశం != src_ref->దత్తాంశం) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            వెళ్ళు fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_బఫరు_unref(&derived_ref);
        av_బఫరు_unref(&వెనుక_ref);
    }

    తిరిగి 0;

fail:
    av_బఫరు_unref(&derived_ref);
    av_బఫరు_unref(&వెనుక_ref);
    తిరిగి -1;
}

స్థిర పూర్ణాంకం test_device(గణన AVHWDeviceType type, స్థిరరాశి అక్షరం *name,
                       స్థిరరాశి అక్షరం *device, AVDictionary *opts, పూర్ణాంకం flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    పూర్ణాంకం err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    ఒకవేళ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        తిరిగి 1;
    }

    dev = (AVHWDeviceContext*)ref->దత్తాంశం;
    ఒకవేళ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_బఫరు_unref(&ref);
        తిరిగి -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_బఫరు_unref(&ref);

    తిరిగి err;
}

స్థిర స్థిరరాశి నిర్మాణం {
    గణన AVHWDeviceType type;
    స్థిరరాశి అక్షరం *possible_devices[5];
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

స్థిర పూర్ణాంకం test_device_type(గణన AVHWDeviceType type)
{
    గణన AVHWDeviceType check;
    స్థిరరాశి అక్షరం *name;
    పూర్ణాంకం i, j, దొరికింది, err;

    name = av_hwdevice_get_type_name(type);
    ఒకవేళ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        తిరిగి -1;
    }

    check = av_hwdevice_కనుగొను_type_by_name(name);
    ఒకవేళ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        తిరిగి -1;
    }

    దొరికింది = 0;

    err = test_device(type, name, ఖాళీ, ఖాళీ, 0);
    ఒకవేళ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        తిరిగి -1;
    }
    ఒకవేళ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++దొరికింది;
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        ఒకవేళ (test_devices[i].type != type)
            కొనసాగు;

        కొరకు (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ఖాళీ, 0);
            ఒకవేళ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                తిరిగి -1;
            }
            ఒకవేళ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++దొరికింది;
            }
        }
    }

    తిరిగి !దొరికింది;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    గణన AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    పూర్ణాంకం pass, fail, skip, err;

    pass = fail = skip = 0;
    అయితే (1) {
        type = av_hwdevice_iterate_types(type);
        ఒకవేళ (type == AV_HWDEVICE_TYPE_NONE)
            ఆపు;

        err = test_device_type(type);
        ఒకవేళ (err == 0)
            ++pass;
        లేకపోతే ఒకవేళ (err < 0)
            ++fail;
        లేకపోతే
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    తిరిగి fail > 0;
}
