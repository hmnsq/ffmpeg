/*
 * Colorspace conversion defines
 * Copyright (c) 2001, 2002, 2003 Fabrice Bellard
 *
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

/**
 * @file
 * Various defines for YUV<->RGB conversion
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_COLORSPACE_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_COLORSPACE_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCALEBITS 10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ONE_HALF  (1 << (SCALEBITS - 1))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FIX(x)    ((ਪੂਰਨ) ((x) * (1<<SCALEBITS) + 0.5))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_ਮੰਜ਼ਿਲ_RGB1_CCIR(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_ਜੋੜੋ = FIX(1.40200*255.0/224.0) * cr + ONE_HALF;\
    g_ਜੋੜੋ = - FIX(0.34414*255.0/224.0) * cb - FIX(0.71414*255.0/224.0) * cr + \
            ONE_HALF;\
    b_ਜੋੜੋ = FIX(1.77200*255.0/224.0) * cb + ONE_HALF;\
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_ਮੰਜ਼ਿਲ_RGB1_CCIR_BT709(cb1, cr1)                      \
    {                                                         \
        cb    = (cb1) - 128;                                  \
        cr    = (cr1) - 128;                                  \
        r_ਜੋੜੋ = ONE_HALF + FIX(1.5747 * 255.0 / 224.0) * cr;  \
        g_ਜੋੜੋ = ONE_HALF - FIX(0.1873 * 255.0 / 224.0) * cb - \
                           FIX(0.4682 * 255.0 / 224.0) * cr;  \
        b_ਜੋੜੋ = ONE_HALF + FIX(1.8556 * 255.0 / 224.0) * cb;  \
    }

// To be used for the BT709 variant as well
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_ਮੰਜ਼ਿਲ_RGB2_CCIR(r, g, b, y1)\
{\
    y = ((y1) - 16) * FIX(255.0/219.0);\
    r = cm[(y + r_ਜੋੜੋ) >> SCALEBITS];\
    g = cm[(y + g_ਜੋੜੋ) >> SCALEBITS];\
    b = cm[(y + b_ਜੋੜੋ) >> SCALEBITS];\
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_ਮੰਜ਼ਿਲ_RGB1(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_ਜੋੜੋ = FIX(1.40200) * cr + ONE_HALF;\
    g_ਜੋੜੋ = - FIX(0.34414) * cb - FIX(0.71414) * cr + ONE_HALF;\
    b_ਜੋੜੋ = FIX(1.77200) * cb + ONE_HALF;\
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_ਮੰਜ਼ਿਲ_RGB2(r, g, b, y1)\
{\
    y = (y1) << SCALEBITS;\
    r = cm[(y + r_ਜੋੜੋ) >> SCALEBITS];\
    g = cm[(y + g_ਜੋੜੋ) >> SCALEBITS];\
    b = cm[(y + b_ਜੋੜੋ) >> SCALEBITS];\
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Y_CCIR_ਮੰਜ਼ਿਲ_JPEG(y)\
 cm[((y) * FIX(255.0/219.0) + (ONE_HALF - 16 * FIX(255.0/219.0))) >> SCALEBITS]

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Y_JPEG_ਮੰਜ਼ਿਲ_CCIR(y)\
 (((y) * FIX(219.0/255.0) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_CCIR_ਮੰਜ਼ਿਲ_JPEG(y)\
 cm[(((y) - 128) * FIX(127.0/112.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS]

/* NOTE: the clamp is really necessary! */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ C_JPEG_ਮੰਜ਼ਿਲ_CCIR(ਪੂਰਨ y) {
    y = (((y - 128) * FIX(112.0/127.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS);
    ਜੇ (y < 16)
        y = 16;
    ਵਾਪਸ y;
}


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_Y_CCIR(r, g, b) \
((FIX(0.29900*219.0/255.0) * (r) + FIX(0.58700*219.0/255.0) * (g) + \
  FIX(0.11400*219.0/255.0) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_U_CCIR(r1, g1, b1, ਖਿਸਕਾਓ)\
(((- FIX(0.16874*224.0/255.0) * r1 - FIX(0.33126*224.0/255.0) * g1 +         \
     FIX(0.50000*224.0/255.0) * b1 + (ONE_HALF << ਖਿਸਕਾਓ) - 1) >> (SCALEBITS + ਖਿਸਕਾਓ)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_V_CCIR(r1, g1, b1, ਖਿਸਕਾਓ)\
(((FIX(0.50000*224.0/255.0) * r1 - FIX(0.41869*224.0/255.0) * g1 -           \
   FIX(0.08131*224.0/255.0) * b1 + (ONE_HALF << ਖਿਸਕਾਓ) - 1) >> (SCALEBITS + ਖਿਸਕਾਓ)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_Y_JPEG(r, g, b) \
(FFMIN((FIX(0.29900) * (r) + FIX(0.58700) * (g) + \
  FIX(0.11400) * (b) + (ONE_HALF)) >> SCALEBITS, 255))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_U_JPEG(r1, g1, b1)\
(((- FIX(0.16874) * r1 - FIX(0.33126) * g1 + \
     FIX(0.50000) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_V_JPEG(r1, g1, b1)\
(((FIX(0.50000) * r1 - FIX(0.41869) * g1 - \
   FIX(0.08131) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

// Conversion macros for 8-bit RGB to YUV
// Derived from ITU-R BT.709-6 (06/2015) Item 3.5
// https://www.itu.int/rec/R-REC-BT.709-6-201506-I/en

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_Y_BT709(r, g, b) \
((FIX(0.21260*219.0/255.0) * (r) + FIX(0.71520*219.0/255.0) * (g) + \
  FIX(0.07220*219.0/255.0) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_U_BT709(r1, g1, b1, ਖਿਸਕਾਓ)\
(((- FIX(0.11457*224.0/255.0) * r1 - FIX(0.38543*224.0/255.0) * g1 +         \
     FIX(0.50000*224.0/255.0) * b1 + (ONE_HALF << ਖਿਸਕਾਓ) - 1) >> (SCALEBITS + ਖਿਸਕਾਓ)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_V_BT709(r1, g1, b1, ਖਿਸਕਾਓ)\
(((FIX(0.50000*224.0/255.0) * r1 - FIX(0.45415*224.0/255.0) * g1 -           \
   FIX(0.04585*224.0/255.0) * b1 + (ONE_HALF << ਖਿਸਕਾਓ) - 1) >> (SCALEBITS + ਖਿਸਕਾਓ)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_Y_BT709_ਭਰਿਆ(r, g, b) \
(FFMIN((FIX(0.21260) * (r) + FIX(0.71520) * (g) + \
  FIX(0.07220) * (b) + (ONE_HALF)) >> SCALEBITS, 255))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_U_BT709_ਭਰਿਆ(r1, g1, b1)\
(((- FIX(0.11457) * r1 - FIX(0.38543) * g1 + \
     FIX(0.50000) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_ਮੰਜ਼ਿਲ_V_BT709_ਭਰਿਆ(r1, g1, b1)\
(((FIX(0.50000) * r1 - FIX(0.45415) * g1 - \
   FIX(0.04585) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#ਜੇ_ਅੰਤ /* AVUTIL_COLORSPACE_H */
