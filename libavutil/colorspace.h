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

#यदि_अपरिभाषितम् AVUTIL_COLORSPACE_H
#परिभाषय AVUTIL_COLORSPACE_H

#परिभाषय SCALEBITS 10
#परिभाषय ONE_HALF  (1 << (SCALEBITS - 1))
#परिभाषय FIX(x)    ((पूर्णाङ्क) ((x) * (1<<SCALEBITS) + 0.5))

#परिभाषय YUV_गन्तव्यम्_RGB1_CCIR(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_सङ्कलय = FIX(1.40200*255.0/224.0) * cr + ONE_HALF;\
    g_सङ्कलय = - FIX(0.34414*255.0/224.0) * cb - FIX(0.71414*255.0/224.0) * cr + \
            ONE_HALF;\
    b_सङ्कलय = FIX(1.77200*255.0/224.0) * cb + ONE_HALF;\
}

#परिभाषय YUV_गन्तव्यम्_RGB1_CCIR_BT709(cb1, cr1)                      \
    {                                                         \
        cb    = (cb1) - 128;                                  \
        cr    = (cr1) - 128;                                  \
        r_सङ्कलय = ONE_HALF + FIX(1.5747 * 255.0 / 224.0) * cr;  \
        g_सङ्कलय = ONE_HALF - FIX(0.1873 * 255.0 / 224.0) * cb - \
                           FIX(0.4682 * 255.0 / 224.0) * cr;  \
        b_सङ्कलय = ONE_HALF + FIX(1.8556 * 255.0 / 224.0) * cb;  \
    }

// To be used for the BT709 variant as well
#परिभाषय YUV_गन्तव्यम्_RGB2_CCIR(r, g, b, y1)\
{\
    y = ((y1) - 16) * FIX(255.0/219.0);\
    r = cm[(y + r_सङ्कलय) >> SCALEBITS];\
    g = cm[(y + g_सङ्कलय) >> SCALEBITS];\
    b = cm[(y + b_सङ्कलय) >> SCALEBITS];\
}

#परिभाषय YUV_गन्तव्यम्_RGB1(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_सङ्कलय = FIX(1.40200) * cr + ONE_HALF;\
    g_सङ्कलय = - FIX(0.34414) * cb - FIX(0.71414) * cr + ONE_HALF;\
    b_सङ्कलय = FIX(1.77200) * cb + ONE_HALF;\
}

#परिभाषय YUV_गन्तव्यम्_RGB2(r, g, b, y1)\
{\
    y = (y1) << SCALEBITS;\
    r = cm[(y + r_सङ्कलय) >> SCALEBITS];\
    g = cm[(y + g_सङ्कलय) >> SCALEBITS];\
    b = cm[(y + b_सङ्कलय) >> SCALEBITS];\
}

#परिभाषय Y_CCIR_गन्तव्यम्_JPEG(y)\
 cm[((y) * FIX(255.0/219.0) + (ONE_HALF - 16 * FIX(255.0/219.0))) >> SCALEBITS]

#परिभाषय Y_JPEG_गन्तव्यम्_CCIR(y)\
 (((y) * FIX(219.0/255.0) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#परिभाषय C_CCIR_गन्तव्यम्_JPEG(y)\
 cm[(((y) - 128) * FIX(127.0/112.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS]

/* NOTE: the clamp is really necessary! */
स्थिर अन्तःस्थ पूर्णाङ्क C_JPEG_गन्तव्यम्_CCIR(पूर्णाङ्क y) {
    y = (((y - 128) * FIX(112.0/127.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS);
    यदि (y < 16)
        y = 16;
    प्रत्यागम y;
}


#परिभाषय RGB_गन्तव्यम्_Y_CCIR(r, g, b) \
((FIX(0.29900*219.0/255.0) * (r) + FIX(0.58700*219.0/255.0) * (g) + \
  FIX(0.11400*219.0/255.0) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#परिभाषय RGB_गन्तव्यम्_U_CCIR(r1, g1, b1, सरणम्)\
(((- FIX(0.16874*224.0/255.0) * r1 - FIX(0.33126*224.0/255.0) * g1 +         \
     FIX(0.50000*224.0/255.0) * b1 + (ONE_HALF << सरणम्) - 1) >> (SCALEBITS + सरणम्)) + 128)

#परिभाषय RGB_गन्तव्यम्_V_CCIR(r1, g1, b1, सरणम्)\
(((FIX(0.50000*224.0/255.0) * r1 - FIX(0.41869*224.0/255.0) * g1 -           \
   FIX(0.08131*224.0/255.0) * b1 + (ONE_HALF << सरणम्) - 1) >> (SCALEBITS + सरणम्)) + 128)

#परिभाषय RGB_गन्तव्यम्_Y_JPEG(r, g, b) \
(FFMIN((FIX(0.29900) * (r) + FIX(0.58700) * (g) + \
  FIX(0.11400) * (b) + (ONE_HALF)) >> SCALEBITS, 255))

#परिभाषय RGB_गन्तव्यम्_U_JPEG(r1, g1, b1)\
(((- FIX(0.16874) * r1 - FIX(0.33126) * g1 + \
     FIX(0.50000) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#परिभाषय RGB_गन्तव्यम्_V_JPEG(r1, g1, b1)\
(((FIX(0.50000) * r1 - FIX(0.41869) * g1 - \
   FIX(0.08131) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

// Conversion macros for 8-bit RGB to YUV
// Derived from ITU-R BT.709-6 (06/2015) Item 3.5
// https://www.itu.int/rec/R-REC-BT.709-6-201506-I/en

#परिभाषय RGB_गन्तव्यम्_Y_BT709(r, g, b) \
((FIX(0.21260*219.0/255.0) * (r) + FIX(0.71520*219.0/255.0) * (g) + \
  FIX(0.07220*219.0/255.0) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#परिभाषय RGB_गन्तव्यम्_U_BT709(r1, g1, b1, सरणम्)\
(((- FIX(0.11457*224.0/255.0) * r1 - FIX(0.38543*224.0/255.0) * g1 +         \
     FIX(0.50000*224.0/255.0) * b1 + (ONE_HALF << सरणम्) - 1) >> (SCALEBITS + सरणम्)) + 128)

#परिभाषय RGB_गन्तव्यम्_V_BT709(r1, g1, b1, सरणम्)\
(((FIX(0.50000*224.0/255.0) * r1 - FIX(0.45415*224.0/255.0) * g1 -           \
   FIX(0.04585*224.0/255.0) * b1 + (ONE_HALF << सरणम्) - 1) >> (SCALEBITS + सरणम्)) + 128)

#परिभाषय RGB_गन्तव्यम्_Y_BT709_पूर्णम्(r, g, b) \
(FFMIN((FIX(0.21260) * (r) + FIX(0.71520) * (g) + \
  FIX(0.07220) * (b) + (ONE_HALF)) >> SCALEBITS, 255))

#परिभाषय RGB_गन्तव्यम्_U_BT709_पूर्णम्(r1, g1, b1)\
(((- FIX(0.11457) * r1 - FIX(0.38543) * g1 + \
     FIX(0.50000) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#परिभाषय RGB_गन्तव्यम्_V_BT709_पूर्णम्(r1, g1, b1)\
(((FIX(0.50000) * r1 - FIX(0.45415) * g1 - \
   FIX(0.04585) * b1 + (ONE_HALF) - 1) >> (SCALEBITS)) + 128)

#यदि_अन्तः /* AVUTIL_COLORSPACE_H */
