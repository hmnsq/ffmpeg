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

#അന്തര്ഭാവ <stdio.h>

#അന്തര്ഭാവ "libavutil/hwcontext.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ test_derivation(AVBufferRef *src_ref, സ്ഥിരം അക്ഷരം *src_name)
{
    എണ്ണൽ AVHWDeviceType derived_type;
    സ്ഥിരം അക്ഷരം *derived_name;
    AVBufferRef *derived_ref = ശൂന്യ, *back_ref = ശൂന്യ;
    AVHWDeviceContext *src_dev, *derived_dev;
    പൂർണ്ണസംഖ്യ err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    ആകുമ്പോൾ (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        എങ്കിൽ (derived_type == AV_HWDEVICE_TYPE_NONE)
            നിർത്തുക;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        എങ്കിൽ (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            തുടരുക;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        എങ്കിൽ (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            പോകുക fail;
        }

        എങ്കിൽ (derived_type == src_dev->type) {
            എങ്കിൽ (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                പോകുക fail;
            }
            av_buffer_unref(&derived_ref);
            തുടരുക;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        എങ്കിൽ (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            പോകുക fail;
        }

        എങ്കിൽ (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            പോകുക fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    തിരികെ 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    തിരികെ -1;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ test_device(എണ്ണൽ AVHWDeviceType type, സ്ഥിരം അക്ഷരം *name,
                       സ്ഥിരം അക്ഷരം *device, AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    പൂർണ്ണസംഖ്യ err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    എങ്കിൽ (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        തിരികെ 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    എങ്കിൽ (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        തിരികെ -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    തിരികെ err;
}

സ്ഥിതം സ്ഥിരം ഘടന {
    എണ്ണൽ AVHWDeviceType type;
    സ്ഥിരം അക്ഷരം *possible_devices[5];
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

സ്ഥിതം പൂർണ്ണസംഖ്യ test_device_type(എണ്ണൽ AVHWDeviceType type)
{
    എണ്ണൽ AVHWDeviceType check;
    സ്ഥിരം അക്ഷരം *name;
    പൂർണ്ണസംഖ്യ i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    എങ്കിൽ (!name) {
        fprintf(stderr, "No name available for device type %d.\n", type);
        തിരികെ -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    എങ്കിൽ (check != type) {
        fprintf(stderr, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        തിരികെ -1;
    }

    found = 0;

    err = test_device(type, name, ശൂന്യ, ശൂന്യ, 0);
    എങ്കിൽ (err < 0) {
        fprintf(stderr, "Test failed for %s with default options.\n", name);
        തിരികെ -1;
    }
    എങ്കിൽ (err == 0) {
        fprintf(stderr, "Test passed for %s with default options.\n", name);
        ++found;
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        എങ്കിൽ (test_devices[i].type != type)
            തുടരുക;

        വേണ്ടി (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              ശൂന്യ, 0);
            എങ്കിൽ (err < 0) {
                fprintf(stderr, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                തിരികെ -1;
            }
            എങ്കിൽ (err == 0) {
                fprintf(stderr, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    തിരികെ !found;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    എണ്ണൽ AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    പൂർണ്ണസംഖ്യ pass, fail, skip, err;

    pass = fail = skip = 0;
    ആകുമ്പോൾ (1) {
        type = av_hwdevice_iterate_types(type);
        എങ്കിൽ (type == AV_HWDEVICE_TYPE_NONE)
            നിർത്തുക;

        err = test_device_type(type);
        എങ്കിൽ (err == 0)
            ++pass;
        അല്ലെങ്കിൽ എങ്കിൽ (err < 0)
            ++fail;
        അല്ലെങ്കിൽ
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    തിരികെ fail > 0;
}
