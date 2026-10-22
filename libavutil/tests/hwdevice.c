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

स्थिर पूर्णांक test_derivation(AVBufferRef *src_ref, स्थिरांक अक्षर *src_name)
{
    गणना AVHWDeviceType derived_type;
    स्थिरांक अक्षर *derived_name;
    AVBufferRef *derived_ref = रिक्त, *back_ref = रिक्त;
    AVHWDeviceContext *src_dev, *derived_dev;
    पूर्णांक err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    पर्यंत (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        जर (derived_type == AV_HWDEVICE_TYPE_NONE)
            थांबा;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        जर (err < 0) {
            ख_लिखो(मानक_त्रुटि, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            सुरूठेवा;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        जर (derived_dev->type != derived_type) {
            ख_लिखो(मानक_त्रुटि, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            जा fail;
        }

        जर (derived_type == src_dev->type) {
            जर (derived_dev != src_dev) {
                ख_लिखो(मानक_त्रुटि, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                जा fail;
            }
            av_buffer_unref(&derived_ref);
            सुरूठेवा;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        जर (err < 0) {
            ख_लिखो(मानक_त्रुटि, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            जा fail;
        }

        जर (back_ref->data != src_ref->data) {
            ख_लिखो(मानक_त्रुटि, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            जा fail;
        }

        ख_लिखो(मानक_त्रुटि, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    परत 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    परत -1;
}

स्थिर पूर्णांक test_device(गणना AVHWDeviceType type, स्थिरांक अक्षर *name,
                       स्थिरांक अक्षर *device, AVDictionary *opts, पूर्णांक flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    पूर्णांक err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    जर (err < 0) {
        ख_लिखो(मानक_त्रुटि, "Failed to create %s device: %d.\n", name, err);
        परत 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    जर (dev->type != type) {
        ख_लिखो(मानक_त्रुटि, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        परत -1;
    }

    ख_लिखो(मानक_त्रुटि, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    परत err;
}

स्थिर स्थिरांक संरचना {
    गणना AVHWDeviceType type;
    स्थिरांक अक्षर *possible_devices[5];
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

स्थिर पूर्णांक test_device_type(गणना AVHWDeviceType type)
{
    गणना AVHWDeviceType check;
    स्थिरांक अक्षर *name;
    पूर्णांक i, j, found, err;

    name = av_hwdevice_get_type_name(type);
    जर (!name) {
        ख_लिखो(मानक_त्रुटि, "No name available for device type %d.\n", type);
        परत -1;
    }

    check = av_hwdevice_find_type_by_name(name);
    जर (check != type) {
        ख_लिखो(मानक_त्रुटि, "Type %d maps to name %s maps to type %d.\n",
               type, name, check);
        परत -1;
    }

    found = 0;

    err = test_device(type, name, रिक्त, रिक्त, 0);
    जर (err < 0) {
        ख_लिखो(मानक_त्रुटि, "Test failed for %s with default options.\n", name);
        परत -1;
    }
    जर (err == 0) {
        ख_लिखो(मानक_त्रुटि, "Test passed for %s with default options.\n", name);
        ++found;
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(test_devices); i++) {
        जर (test_devices[i].type != type)
            सुरूठेवा;

        साठी (j = 0; test_devices[i].possible_devices[j]; j++) {
            err = test_device(type, name,
                              test_devices[i].possible_devices[j],
                              रिक्त, 0);
            जर (err < 0) {
                ख_लिखो(मानक_त्रुटि, "Test failed for %s with device %s.\n",
                       name, test_devices[i].possible_devices[j]);
                परत -1;
            }
            जर (err == 0) {
                ख_लिखो(मानक_त्रुटि, "Test passed for %s with device %s.\n",
                        name, test_devices[i].possible_devices[j]);
                ++found;
            }
        }
    }

    परत !found;
}

पूर्णांक main(शून्य)
{
    गणना AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    पूर्णांक pass, fail, skip, err;

    pass = fail = skip = 0;
    पर्यंत (1) {
        type = av_hwdevice_iterate_types(type);
        जर (type == AV_HWDEVICE_TYPE_NONE)
            थांबा;

        err = test_device_type(type);
        जर (err == 0)
            ++pass;
        अन्यथा जर (err < 0)
            ++fail;
        अन्यथा
            ++skip;
    }

    ख_लिखो(मानक_त्रुटि, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    परत fail > 0;
}
