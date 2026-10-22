/*
 * Copyright (c) Lynne
 *
 * Power of two FFT:
 * Copyright (c) Lynne
 * Copyright (c) 2008 Loren Merritt
 * Copyright (c) 2002 Fabrice Bellard
 * Partly based on libdjbfft by D. J. Bernstein
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

#अन्तर्भाव "mem.h"

#परिभाषय सारणी_DEF(name, आकार) \
    DECLARE_ALIGNED(32, TXSample, TX_TAB(ff_tx_tab_ ##name))[आकार]

#परिभाषय SR_POW2_TABLES \
    SR_सारणी(8)        \
    SR_सारणी(16)       \
    SR_सारणी(32)       \
    SR_सारणी(64)       \
    SR_सारणी(128)      \
    SR_सारणी(256)      \
    SR_सारणी(512)      \
    SR_सारणी(1024)     \
    SR_सारणी(2048)     \
    SR_सारणी(4096)     \
    SR_सारणी(8192)     \
    SR_सारणी(16384)    \
    SR_सारणी(32768)    \
    SR_सारणी(65536)    \
    SR_सारणी(131072)   \

#परिभाषय SR_सारणी(len) \
    सारणी_DEF(len, len/4 + 1);
/* Power of two tables */
SR_POW2_TABLES
#अपरिभाषय SR_सारणी

/* Other factors' tables */
सारणी_DEF(53, 12);
सारणी_DEF( 7,  6);
सारणी_DEF( 9,  8);

प्रकारनिर्देश संरचना FFTab_Init_दत्त {
    शून्य (*func)(शून्य);
    पूर्णाङ्क factors[TX_MAX_SUB]; /* Must be sorted high -> low */
} FFTab_Init_दत्त;

#परिभाषय SR_सारणी(len)                                              \
स्थिर av_cold शून्य TX_TAB(ff_tx_init_tab_ ##len)(शून्य)            \
{                                                                  \
    द्विगुण freq = 2*M_PI/len;                                      \
    TXSample *tab = TX_TAB(ff_tx_tab_ ##len);                      \
                                                                   \
    प्रति (पूर्णाङ्क i = 0; i < len/4; i++)                                \
        *tab++ = RESCALE(कोटिज्या(i*freq));                             \
                                                                   \
    *tab = 0;                                                      \
}
SR_POW2_TABLES
#अपरिभाषय SR_सारणी

स्थिर शून्य (*ध्रुव sr_tabs_init_funcs[])(शून्य) = {
#परिभाषय SR_सारणी(len) TX_TAB(ff_tx_init_tab_ ##len),
    SR_POW2_TABLES
#अपरिभाषय SR_सारणी
};

स्थिर AVOnce sr_tabs_init_once[] = {
#परिभाषय SR_सारणी(len) AV_ONCE_INIT,
    SR_POW2_TABLES
#अपरिभाषय SR_सारणी
};

स्थिर av_cold शून्य TX_TAB(ff_tx_init_tab_53)(शून्य)
{
    /* 5pt, doubled to eliminate AVX lane shuffles */
    TX_TAB(ff_tx_tab_53)[0] = RESCALE(कोटिज्या(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[1] = RESCALE(कोटिज्या(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[2] = RESCALE(कोटिज्या(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[3] = RESCALE(कोटिज्या(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[4] = RESCALE(ज्या(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[5] = RESCALE(ज्या(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[6] = RESCALE(ज्या(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[7] = RESCALE(ज्या(2 * M_PI / 10));

    /* 3pt */
    TX_TAB(ff_tx_tab_53)[ 8] = RESCALE(कोटिज्या(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[ 9] = RESCALE(कोटिज्या(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[10] = RESCALE(कोटिज्या(2 * M_PI /  6));
    TX_TAB(ff_tx_tab_53)[11] = RESCALE(कोटिज्या(8 * M_PI /  6));
}

स्थिर av_cold शून्य TX_TAB(ff_tx_init_tab_7)(शून्य)
{
    TX_TAB(ff_tx_tab_7)[0] = RESCALE(कोटिज्या(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[1] = RESCALE(ज्या(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[2] = RESCALE(ज्या(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[3] = RESCALE(कोटिज्या(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[4] = RESCALE(कोटिज्या(2 * M_PI / 14));
    TX_TAB(ff_tx_tab_7)[5] = RESCALE(ज्या(2 * M_PI / 14));
}

स्थिर av_cold शून्य TX_TAB(ff_tx_init_tab_9)(शून्य)
{
    TX_TAB(ff_tx_tab_9)[0] = RESCALE(कोटिज्या(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[1] = RESCALE(ज्या(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[2] = RESCALE(कोटिज्या(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[3] = RESCALE(ज्या(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[4] = RESCALE(कोटिज्या(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[5] = RESCALE(ज्या(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[6] = TX_TAB(ff_tx_tab_9)[2] + TX_TAB(ff_tx_tab_9)[5];
    TX_TAB(ff_tx_tab_9)[7] = TX_TAB(ff_tx_tab_9)[3] - TX_TAB(ff_tx_tab_9)[4];
}

स्थिर ध्रुव FFTab_Init_दत्त nptwo_tabs_init_दत्त[] = {
    { TX_TAB(ff_tx_init_tab_53),      { 15, 5, 3 } },
    { TX_TAB(ff_tx_init_tab_9),       {  9 }       },
    { TX_TAB(ff_tx_init_tab_7),       {  7 }       },
};

स्थिर AVOnce nptwo_tabs_init_once[] = {
    AV_ONCE_INIT,
    AV_ONCE_INIT,
    AV_ONCE_INIT,
};

av_cold शून्य TX_TAB(ff_tx_init_tabs)(पूर्णाङ्क len)
{
    पूर्णाङ्क गुणकः_2 = ff_ctz(len);
    यदि (गुणकः_2) {
        पूर्णाङ्क idx = गुणकः_2 - 3;
        प्रति (पूर्णाङ्क i = 0; i <= idx; i++)
            ff_thread_once(&sr_tabs_init_once[i],
                            sr_tabs_init_funcs[i]);
        len >>= गुणकः_2;
    }

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(nptwo_tabs_init_दत्त); i++) {
        पूर्णाङ्क f, f_idx = 0;

        यदि (len <= 1)
            प्रत्यागम;

        यावत् ((f = nptwo_tabs_init_दत्त[i].factors[f_idx++])) {
            यदि (f % len)
                अनुवर्त;

            ff_thread_once(&nptwo_tabs_init_once[i],
                            nptwo_tabs_init_दत्त[i].func);
            len /= f;
            भङ्ग;
        }
    }
}

स्थिर av_always_inline शून्य fft3(TXComplex *बहिर्गमनम्, TXComplex *अन्तर्,
                                  ptrdiff_t stride)
{
    TXComplex tmp[3];
    ध्रुव TXSample *tab = TX_TAB(ff_tx_tab_53);
#यदि_परिभाषितम् TX_INT32
    int64_t mtmp[4];
#यदि_अन्तः

    tmp[0] = अन्तर्[0];
    BF(tmp[1].re, tmp[2].im, अन्तर्[1].im, अन्तर्[2].im);
    BF(tmp[1].im, tmp[2].re, अन्तर्[1].re, अन्तर्[2].re);

#यदि_परिभाषितम् TX_INT32
    बहिर्गमनम्[0*stride].re = (int64_t)tmp[0].re + tmp[2].re;
    बहिर्गमनम्[0*stride].im = (int64_t)tmp[0].im + tmp[2].im;
    mtmp[0] = (int64_t)tab[ 8] * tmp[1].re;
    mtmp[1] = (int64_t)tab[ 9] * tmp[1].im;
    mtmp[2] = (int64_t)tab[10] * tmp[2].re;
    mtmp[3] = (int64_t)tab[10] * tmp[2].im;
    बहिर्गमनम्[1*stride].re = tmp[0].re - (mtmp[2] + mtmp[0] + 0x40000000 >> 31);
    बहिर्गमनम्[1*stride].im = tmp[0].im - (mtmp[3] - mtmp[1] + 0x40000000 >> 31);
    बहिर्गमनम्[2*stride].re = tmp[0].re - (mtmp[2] - mtmp[0] + 0x40000000 >> 31);
    बहिर्गमनम्[2*stride].im = tmp[0].im - (mtmp[3] + mtmp[1] + 0x40000000 >> 31);
#अन्यथा
    बहिर्गमनम्[0*stride].re = tmp[0].re + tmp[2].re;
    बहिर्गमनम्[0*stride].im = tmp[0].im + tmp[2].im;
    tmp[1].re = tab[ 8] * tmp[1].re;
    tmp[1].im = tab[ 9] * tmp[1].im;
    tmp[2].re = tab[10] * tmp[2].re;
    tmp[2].im = tab[10] * tmp[2].im;
    बहिर्गमनम्[1*stride].re = tmp[0].re - tmp[2].re + tmp[1].re;
    बहिर्गमनम्[1*stride].im = tmp[0].im - tmp[2].im - tmp[1].im;
    बहिर्गमनम्[2*stride].re = tmp[0].re - tmp[2].re - tmp[1].re;
    बहिर्गमनम्[2*stride].im = tmp[0].im - tmp[2].im + tmp[1].im;
#यदि_अन्तः
}

#परिभाषय DECL_FFT5(NAME, D0, D1, D2, D3, D4)                         \
स्थिर av_always_inline शून्य NAME(TXComplex *बहिर्गमनम्, TXComplex *अन्तर्,    \
                                  ptrdiff_t stride)                 \
{                                                                   \
    TXComplex dc, z0[4], t[6];                                      \
    ध्रुव TXSample *tab = TX_TAB(ff_tx_tab_53);                     \
                                                                    \
    dc = अन्तर्[0];                                                     \
    BF(t[1].im, t[0].re, अन्तर्[1].re, अन्तर्[4].re);                       \
    BF(t[1].re, t[0].im, अन्तर्[1].im, अन्तर्[4].im);                       \
    BF(t[3].im, t[2].re, अन्तर्[2].re, अन्तर्[3].re);                       \
    BF(t[3].re, t[2].im, अन्तर्[2].im, अन्तर्[3].im);                       \
                                                                    \
    बहिर्गमनम्[D0*stride].re = dc.re + (TXUSample)t[0].re + t[2].re;        \
    बहिर्गमनम्[D0*stride].im = dc.im + (TXUSample)t[0].im + t[2].im;        \
                                                                    \
    SMUL(t[4].re, t[0].re, tab[0], tab[2], t[2].re, t[0].re);       \
    SMUL(t[4].im, t[0].im, tab[0], tab[2], t[2].im, t[0].im);       \
    CMUL(t[5].re, t[1].re, tab[4], tab[6], t[3].re, t[1].re);       \
    CMUL(t[5].im, t[1].im, tab[4], tab[6], t[3].im, t[1].im);       \
                                                                    \
    BF(z0[0].re, z0[3].re, t[0].re, t[1].re);                       \
    BF(z0[0].im, z0[3].im, t[0].im, t[1].im);                       \
    BF(z0[2].re, z0[1].re, t[4].re, t[5].re);                       \
    BF(z0[2].im, z0[1].im, t[4].im, t[5].im);                       \
                                                                    \
    बहिर्गमनम्[D1*stride].re = dc.re + (TXUSample)z0[3].re;                 \
    बहिर्गमनम्[D1*stride].im = dc.im + (TXUSample)z0[0].im;                 \
    बहिर्गमनम्[D2*stride].re = dc.re + (TXUSample)z0[2].re;                 \
    बहिर्गमनम्[D2*stride].im = dc.im + (TXUSample)z0[1].im;                 \
    बहिर्गमनम्[D3*stride].re = dc.re + (TXUSample)z0[1].re;                 \
    बहिर्गमनम्[D3*stride].im = dc.im + (TXUSample)z0[2].im;                 \
    बहिर्गमनम्[D4*stride].re = dc.re + (TXUSample)z0[0].re;                 \
    बहिर्गमनम्[D4*stride].im = dc.im + (TXUSample)z0[3].im;                 \
}

DECL_FFT5(fft5,     0,  1,  2,  3,  4)
DECL_FFT5(fft5_m1,  0,  6, 12,  3,  9)
DECL_FFT5(fft5_m2, 10,  1,  7, 13,  4)
DECL_FFT5(fft5_m3,  5, 11,  2,  8, 14)

स्थिर av_always_inline शून्य fft7(TXComplex *बहिर्गमनम्, TXComplex *अन्तर्,
                                  ptrdiff_t stride)
{
    TXComplex dc, t[6], z[3];
    ध्रुव TXComplex *tab = (ध्रुव TXComplex *)TX_TAB(ff_tx_tab_7);
#यदि_परिभाषितम् TX_INT32
    int64_t mtmp[12];
#यदि_अन्तः

    dc = अन्तर्[0];
    BF(t[1].re, t[0].re, अन्तर्[1].re, अन्तर्[6].re);
    BF(t[1].im, t[0].im, अन्तर्[1].im, अन्तर्[6].im);
    BF(t[3].re, t[2].re, अन्तर्[2].re, अन्तर्[5].re);
    BF(t[3].im, t[2].im, अन्तर्[2].im, अन्तर्[5].im);
    BF(t[5].re, t[4].re, अन्तर्[3].re, अन्तर्[4].re);
    BF(t[5].im, t[4].im, अन्तर्[3].im, अन्तर्[4].im);

    बहिर्गमनम्[0*stride].re = dc.re + t[0].re + t[2].re + t[4].re;
    बहिर्गमनम्[0*stride].im = dc.im + t[0].im + t[2].im + t[4].im;

#यदि_परिभाषितम् TX_INT32 /* NOTE: it's possible to do this with 16 mults but 72 adds */
    mtmp[ 0] = ((int64_t)tab[0].re)*t[0].re - ((int64_t)tab[2].re)*t[4].re;
    mtmp[ 1] = ((int64_t)tab[0].re)*t[4].re - ((int64_t)tab[1].re)*t[0].re;
    mtmp[ 2] = ((int64_t)tab[0].re)*t[2].re - ((int64_t)tab[2].re)*t[0].re;
    mtmp[ 3] = ((int64_t)tab[0].re)*t[0].im - ((int64_t)tab[1].re)*t[2].im;
    mtmp[ 4] = ((int64_t)tab[0].re)*t[4].im - ((int64_t)tab[1].re)*t[0].im;
    mtmp[ 5] = ((int64_t)tab[0].re)*t[2].im - ((int64_t)tab[2].re)*t[0].im;

    mtmp[ 6] = ((int64_t)tab[2].im)*t[1].im + ((int64_t)tab[1].im)*t[5].im;
    mtmp[ 7] = ((int64_t)tab[0].im)*t[5].im + ((int64_t)tab[2].im)*t[3].im;
    mtmp[ 8] = ((int64_t)tab[2].im)*t[5].im + ((int64_t)tab[1].im)*t[3].im;
    mtmp[ 9] = ((int64_t)tab[0].im)*t[1].re + ((int64_t)tab[1].im)*t[3].re;
    mtmp[10] = ((int64_t)tab[2].im)*t[3].re + ((int64_t)tab[0].im)*t[5].re;
    mtmp[11] = ((int64_t)tab[2].im)*t[1].re + ((int64_t)tab[1].im)*t[5].re;

    z[0].re = (int32_t)(mtmp[ 0] - ((int64_t)tab[1].re)*t[2].re + 0x40000000 >> 31);
    z[1].re = (int32_t)(mtmp[ 1] - ((int64_t)tab[2].re)*t[2].re + 0x40000000 >> 31);
    z[2].re = (int32_t)(mtmp[ 2] - ((int64_t)tab[1].re)*t[4].re + 0x40000000 >> 31);
    z[0].im = (int32_t)(mtmp[ 3] - ((int64_t)tab[2].re)*t[4].im + 0x40000000 >> 31);
    z[1].im = (int32_t)(mtmp[ 4] - ((int64_t)tab[2].re)*t[2].im + 0x40000000 >> 31);
    z[2].im = (int32_t)(mtmp[ 5] - ((int64_t)tab[1].re)*t[4].im + 0x40000000 >> 31);

    t[0].re = (int32_t)(mtmp[ 6] - ((int64_t)tab[0].im)*t[3].im + 0x40000000 >> 31);
    t[2].re = (int32_t)(mtmp[ 7] - ((int64_t)tab[1].im)*t[1].im + 0x40000000 >> 31);
    t[4].re = (int32_t)(mtmp[ 8] + ((int64_t)tab[0].im)*t[1].im + 0x40000000 >> 31);
    t[0].im = (int32_t)(mtmp[ 9] + ((int64_t)tab[2].im)*t[5].re + 0x40000000 >> 31);
    t[2].im = (int32_t)(mtmp[10] - ((int64_t)tab[1].im)*t[1].re + 0x40000000 >> 31);
    t[4].im = (int32_t)(mtmp[11] - ((int64_t)tab[0].im)*t[3].re + 0x40000000 >> 31);
#अन्यथा
    z[0].re = tab[0].re*t[0].re - tab[2].re*t[4].re - tab[1].re*t[2].re;
    z[1].re = tab[0].re*t[4].re - tab[1].re*t[0].re - tab[2].re*t[2].re;
    z[2].re = tab[0].re*t[2].re - tab[2].re*t[0].re - tab[1].re*t[4].re;
    z[0].im = tab[0].re*t[0].im - tab[1].re*t[2].im - tab[2].re*t[4].im;
    z[1].im = tab[0].re*t[4].im - tab[1].re*t[0].im - tab[2].re*t[2].im;
    z[2].im = tab[0].re*t[2].im - tab[2].re*t[0].im - tab[1].re*t[4].im;

    /* It's possible to do t[4].re and t[0].im with 2 multiplies only by
     * multiplying the sum of all with the average of the twiddles */

    t[0].re = tab[2].im*t[1].im + tab[1].im*t[5].im - tab[0].im*t[3].im;
    t[2].re = tab[0].im*t[5].im + tab[2].im*t[3].im - tab[1].im*t[1].im;
    t[4].re = tab[2].im*t[5].im + tab[1].im*t[3].im + tab[0].im*t[1].im;
    t[0].im = tab[0].im*t[1].re + tab[1].im*t[3].re + tab[2].im*t[5].re;
    t[2].im = tab[2].im*t[3].re + tab[0].im*t[5].re - tab[1].im*t[1].re;
    t[4].im = tab[2].im*t[1].re + tab[1].im*t[5].re - tab[0].im*t[3].re;
#यदि_अन्तः

    BF(t[1].re, z[0].re, z[0].re, t[4].re);
    BF(t[3].re, z[1].re, z[1].re, t[2].re);
    BF(t[5].re, z[2].re, z[2].re, t[0].re);
    BF(t[1].im, z[0].im, z[0].im, t[0].im);
    BF(t[3].im, z[1].im, z[1].im, t[2].im);
    BF(t[5].im, z[2].im, z[2].im, t[4].im);

    बहिर्गमनम्[1*stride].re = dc.re + z[0].re;
    बहिर्गमनम्[1*stride].im = dc.im + t[1].im;
    बहिर्गमनम्[2*stride].re = dc.re + t[3].re;
    बहिर्गमनम्[2*stride].im = dc.im + z[1].im;
    बहिर्गमनम्[3*stride].re = dc.re + z[2].re;
    बहिर्गमनम्[3*stride].im = dc.im + t[5].im;
    बहिर्गमनम्[4*stride].re = dc.re + t[5].re;
    बहिर्गमनम्[4*stride].im = dc.im + z[2].im;
    बहिर्गमनम्[5*stride].re = dc.re + z[1].re;
    बहिर्गमनम्[5*stride].im = dc.im + t[3].im;
    बहिर्गमनम्[6*stride].re = dc.re + t[1].re;
    बहिर्गमनम्[6*stride].im = dc.im + z[0].im;
}

स्थिर av_always_inline शून्य fft9(TXComplex *बहिर्गमनम्, TXComplex *अन्तर्,
                                  ptrdiff_t stride)
{
    ध्रुव TXComplex *tab = (ध्रुव TXComplex *)TX_TAB(ff_tx_tab_9);
    TXComplex dc, t[16], w[4], x[5], y[5], z[2];
#यदि_परिभाषितम् TX_INT32
    int64_t mtmp[12];
#यदि_अन्तः

    dc = अन्तर्[0];
    BF(t[1].re, t[0].re, अन्तर्[1].re, अन्तर्[8].re);
    BF(t[1].im, t[0].im, अन्तर्[1].im, अन्तर्[8].im);
    BF(t[3].re, t[2].re, अन्तर्[2].re, अन्तर्[7].re);
    BF(t[3].im, t[2].im, अन्तर्[2].im, अन्तर्[7].im);
    BF(t[5].re, t[4].re, अन्तर्[3].re, अन्तर्[6].re);
    BF(t[5].im, t[4].im, अन्तर्[3].im, अन्तर्[6].im);
    BF(t[7].re, t[6].re, अन्तर्[4].re, अन्तर्[5].re);
    BF(t[7].im, t[6].im, अन्तर्[4].im, अन्तर्[5].im);

    w[0].re = t[0].re - t[6].re;
    w[0].im = t[0].im - t[6].im;
    w[1].re = t[2].re - t[6].re;
    w[1].im = t[2].im - t[6].im;
    w[2].re = t[1].re - t[7].re;
    w[2].im = t[1].im - t[7].im;
    w[3].re = t[3].re + t[7].re;
    w[3].im = t[3].im + t[7].im;

    z[0].re = dc.re + t[4].re;
    z[0].im = dc.im + t[4].im;

    z[1].re = t[0].re + t[2].re + t[6].re;
    z[1].im = t[0].im + t[2].im + t[6].im;

    बहिर्गमनम्[0*stride].re = z[0].re + z[1].re;
    बहिर्गमनम्[0*stride].im = z[0].im + z[1].im;

#यदि_परिभाषितम् TX_INT32
    mtmp[0] = t[1].re - t[3].re + t[7].re;
    mtmp[1] = t[1].im - t[3].im + t[7].im;

    y[3].re = (int32_t)(((int64_t)tab[0].im)*mtmp[0] + 0x40000000 >> 31);
    y[3].im = (int32_t)(((int64_t)tab[0].im)*mtmp[1] + 0x40000000 >> 31);

    mtmp[0] = (int32_t)(((int64_t)tab[0].re)*z[1].re + 0x40000000 >> 31);
    mtmp[1] = (int32_t)(((int64_t)tab[0].re)*z[1].im + 0x40000000 >> 31);
    mtmp[2] = (int32_t)(((int64_t)tab[0].re)*t[4].re + 0x40000000 >> 31);
    mtmp[3] = (int32_t)(((int64_t)tab[0].re)*t[4].im + 0x40000000 >> 31);

    x[3].re = z[0].re  + (int32_t)mtmp[0];
    x[3].im = z[0].im  + (int32_t)mtmp[1];
    z[0].re = अन्तर्[0].re + (int32_t)mtmp[2];
    z[0].im = अन्तर्[0].im + (int32_t)mtmp[3];

    mtmp[0] = ((int64_t)tab[1].re)*w[0].re;
    mtmp[1] = ((int64_t)tab[1].re)*w[0].im;
    mtmp[2] = ((int64_t)tab[2].im)*w[0].re;
    mtmp[3] = ((int64_t)tab[2].im)*w[0].im;
    mtmp[4] = ((int64_t)tab[1].im)*w[2].re;
    mtmp[5] = ((int64_t)tab[1].im)*w[2].im;
    mtmp[6] = ((int64_t)tab[2].re)*w[2].re;
    mtmp[7] = ((int64_t)tab[2].re)*w[2].im;

    x[1].re = (int32_t)(mtmp[0] + ((int64_t)tab[2].im)*w[1].re + 0x40000000 >> 31);
    x[1].im = (int32_t)(mtmp[1] + ((int64_t)tab[2].im)*w[1].im + 0x40000000 >> 31);
    x[2].re = (int32_t)(mtmp[2] - ((int64_t)tab[3].re)*w[1].re + 0x40000000 >> 31);
    x[2].im = (int32_t)(mtmp[3] - ((int64_t)tab[3].re)*w[1].im + 0x40000000 >> 31);
    y[1].re = (int32_t)(mtmp[4] + ((int64_t)tab[2].re)*w[3].re + 0x40000000 >> 31);
    y[1].im = (int32_t)(mtmp[5] + ((int64_t)tab[2].re)*w[3].im + 0x40000000 >> 31);
    y[2].re = (int32_t)(mtmp[6] - ((int64_t)tab[3].im)*w[3].re + 0x40000000 >> 31);
    y[2].im = (int32_t)(mtmp[7] - ((int64_t)tab[3].im)*w[3].im + 0x40000000 >> 31);

    y[0].re = (int32_t)(((int64_t)tab[0].im)*t[5].re + 0x40000000 >> 31);
    y[0].im = (int32_t)(((int64_t)tab[0].im)*t[5].im + 0x40000000 >> 31);

#अन्यथा
    y[3].re = tab[0].im*(t[1].re - t[3].re + t[7].re);
    y[3].im = tab[0].im*(t[1].im - t[3].im + t[7].im);

    x[3].re = z[0].re  + tab[0].re*z[1].re;
    x[3].im = z[0].im  + tab[0].re*z[1].im;
    z[0].re = dc.re + tab[0].re*t[4].re;
    z[0].im = dc.im + tab[0].re*t[4].im;

    x[1].re = tab[1].re*w[0].re + tab[2].im*w[1].re;
    x[1].im = tab[1].re*w[0].im + tab[2].im*w[1].im;
    x[2].re = tab[2].im*w[0].re - tab[3].re*w[1].re;
    x[2].im = tab[2].im*w[0].im - tab[3].re*w[1].im;
    y[1].re = tab[1].im*w[2].re + tab[2].re*w[3].re;
    y[1].im = tab[1].im*w[2].im + tab[2].re*w[3].im;
    y[2].re = tab[2].re*w[2].re - tab[3].im*w[3].re;
    y[2].im = tab[2].re*w[2].im - tab[3].im*w[3].im;

    y[0].re = tab[0].im*t[5].re;
    y[0].im = tab[0].im*t[5].im;
#यदि_अन्तः

    x[4].re = x[1].re + x[2].re;
    x[4].im = x[1].im + x[2].im;

    y[4].re = y[1].re - y[2].re;
    y[4].im = y[1].im - y[2].im;
    x[1].re = z[0].re + x[1].re;
    x[1].im = z[0].im + x[1].im;
    y[1].re = y[0].re + y[1].re;
    y[1].im = y[0].im + y[1].im;
    x[2].re = z[0].re + x[2].re;
    x[2].im = z[0].im + x[2].im;
    y[2].re = y[2].re - y[0].re;
    y[2].im = y[2].im - y[0].im;
    x[4].re = z[0].re - x[4].re;
    x[4].im = z[0].im - x[4].im;
    y[4].re = y[0].re - y[4].re;
    y[4].im = y[0].im - y[4].im;

    बहिर्गमनम्[1*stride] = (TXComplex){ x[1].re + y[1].im, x[1].im - y[1].re };
    बहिर्गमनम्[2*stride] = (TXComplex){ x[2].re + y[2].im, x[2].im - y[2].re };
    बहिर्गमनम्[3*stride] = (TXComplex){ x[3].re + y[3].im, x[3].im - y[3].re };
    बहिर्गमनम्[4*stride] = (TXComplex){ x[4].re + y[4].im, x[4].im - y[4].re };
    बहिर्गमनम्[5*stride] = (TXComplex){ x[4].re - y[4].im, x[4].im + y[4].re };
    बहिर्गमनम्[6*stride] = (TXComplex){ x[3].re - y[3].im, x[3].im + y[3].re };
    बहिर्गमनम्[7*stride] = (TXComplex){ x[2].re - y[2].im, x[2].im + y[2].re };
    बहिर्गमनम्[8*stride] = (TXComplex){ x[1].re - y[1].im, x[1].im + y[1].re };
}

स्थिर av_always_inline शून्य fft15(TXComplex *बहिर्गमनम्, TXComplex *अन्तर्,
                                   ptrdiff_t stride)
{
    TXComplex tmp[15];

    प्रति (पूर्णाङ्क i = 0; i < 5; i++)
        fft3(tmp + i, अन्तर् + i*3, 5);

    fft5_m1(बहिर्गमनम्, tmp +  0, stride);
    fft5_m2(बहिर्गमनम्, tmp +  5, stride);
    fft5_m3(बहिर्गमनम्, tmp + 10, stride);
}

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_गुणकः_init)(AVTXContext *s,
                                                  ध्रुव FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  पूर्णाङ्क len, पूर्णाङ्क inv,
                                                  ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret = 0;
    TX_TAB(ff_tx_init_tabs)(len);

    यदि (len == 15)
        ret = ff_tx_gen_pfa_निवेशः_map(s, opts, 3, 5);
    अन्यथा यदि (flags & FF_TX_PRESHUFFLE)
        ret = ff_tx_gen_default_map(s, opts);

    प्रत्यागम ret;
}

#परिभाषय DECL_गुणकः_S(n)                                                       \
स्थिर शून्य TX_NAME(ff_tx_fft##n)(AVTXContext *s, शून्य *dst,                   \
                                  शून्य *src, ptrdiff_t stride)                 \
{                                                                              \
    fft##n((TXComplex *)dst, (TXComplex *)src, stride / परिमाण(TXComplex));    \
}                                                                              \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = {                    \
    .name       = TX_NAME_STR("fft" #n "_ns"),                                 \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE |                         \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,                          \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_गुणकः_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

#परिभाषय DECL_गुणकः_F(n)                                                       \
DECL_गुणकः_S(n)                                                               \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft##n##_fwd_def) = {                   \
    .name       = TX_NAME_STR("fft" #n "_fwd"),                                \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE |                         \
                  AV_TX_UNALIGNED | FF_TX_FORWARD_ONLY,                        \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_गुणकः_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

DECL_गुणकः_F(3)
DECL_गुणकः_F(5)
DECL_गुणकः_F(7)
DECL_गुणकः_F(9)
DECL_गुणकः_S(15)

#परिभाषय BUTTERFLIES(a0, a1, a2, a3)            \
    कुरु {                                       \
        r0=a0.re;                              \
        i0=a0.im;                              \
        r1=a1.re;                              \
        i1=a1.im;                              \
        BF(t3, t5, t5, t1);                    \
        BF(a2.re, a0.re, r0, t5);              \
        BF(a3.im, a1.im, i1, t3);              \
        BF(t4, t6, t2, t6);                    \
        BF(a3.re, a1.re, r1, t4);              \
        BF(a2.im, a0.im, i0, t6);              \
    } यावत् (0)

#परिभाषय TRANSFORM(a0, a1, a2, a3, wre, wim)    \
    कुरु {                                       \
        CMUL(t1, t2, a2.re, a2.im, wre, -wim); \
        CMUL(t5, t6, a3.re, a3.im, wre,  wim); \
        BUTTERFLIES(a0, a1, a2, a3);           \
    } यावत् (0)

/* z[0...8n-1], w[1...2n-1] */
स्थिर अन्तःस्थ शून्य TX_NAME(ff_tx_fft_sr_combine)(TXComplex *z,
                                                 ध्रुव TXSample *कोटिज्या, पूर्णाङ्क len)
{
    पूर्णाङ्क o1 = 2*len;
    पूर्णाङ्क o2 = 4*len;
    पूर्णाङ्क o3 = 6*len;
    ध्रुव TXSample *wim = कोटिज्या + o1 - 7;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;

    प्रति (पूर्णाङ्क i = 0; i < len; i += 4) {
        TRANSFORM(z[0], z[o1 + 0], z[o2 + 0], z[o3 + 0], कोटिज्या[0], wim[7]);
        TRANSFORM(z[2], z[o1 + 2], z[o2 + 2], z[o3 + 2], कोटिज्या[2], wim[5]);
        TRANSFORM(z[4], z[o1 + 4], z[o2 + 4], z[o3 + 4], कोटिज्या[4], wim[3]);
        TRANSFORM(z[6], z[o1 + 6], z[o2 + 6], z[o3 + 6], कोटिज्या[6], wim[1]);

        TRANSFORM(z[1], z[o1 + 1], z[o2 + 1], z[o3 + 1], कोटिज्या[1], wim[6]);
        TRANSFORM(z[3], z[o1 + 3], z[o2 + 3], z[o3 + 3], कोटिज्या[3], wim[4]);
        TRANSFORM(z[5], z[o1 + 5], z[o2 + 5], z[o3 + 5], कोटिज्या[5], wim[2]);
        TRANSFORM(z[7], z[o1 + 7], z[o2 + 7], z[o3 + 7], कोटिज्या[7], wim[0]);

        z   += 2*4;
        कोटिज्या += 2*4;
        wim -= 2*4;
    }
}

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_sr_codelet_init)(AVTXContext *s,
                                                      ध्रुव FFTXCodelet *cd,
                                                      uint64_t flags,
                                                      FFTXCodeletOptions *opts,
                                                      पूर्णाङ्क len, पूर्णाङ्क inv,
                                                      ध्रुव शून्य *scale)
{
    TX_TAB(ff_tx_init_tabs)(len);
    प्रत्यागम ff_tx_gen_ptwo_revtab(s, opts);
}

#परिभाषय DECL_SR_CODELET_DEF(n)                              \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = { \
    .name       = TX_NAME_STR("fft" #n "_ns"),              \
    .function   = TX_NAME(ff_tx_fft##n##_ns),               \
    .type       = TX_TYPE(FFT),                             \
    .flags      = FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | AV_TX_INPLACE |      \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,       \
    .factors[0] = 2,                                        \
    .nb_factors = 1,                                        \
    .min_len    = n,                                        \
    .max_len    = n,                                        \
    .init       = TX_NAME(ff_tx_fft_sr_codelet_init),       \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                      \
    .prio       = FF_TX_PRIO_आधारः,                          \
};

#परिभाषय DECL_SR_CODELET(n, n2, n4)                                    \
स्थिर शून्य TX_NAME(ff_tx_fft##n##_ns)(AVTXContext *s, शून्य *_dst,    \
                                        शून्य *_src, ptrdiff_t stride) \
{                                                                     \
    TXComplex *src = _src;                                            \
    TXComplex *dst = _dst;                                            \
    ध्रुव TXSample *कोटिज्या = TX_TAB(ff_tx_tab_##n);                      \
                                                                      \
    TX_NAME(ff_tx_fft##n2##_ns)(s, dst,        src,        stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*2, src + n4*2, stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*3, src + n4*3, stride);   \
    TX_NAME(ff_tx_fft_sr_combine)(dst, कोटिज्या, n4 >> 1);                 \
}                                                                     \
                                                                      \
DECL_SR_CODELET_DEF(n)

स्थिर शून्य TX_NAME(ff_tx_fft2_ns)(AVTXContext *s, शून्य *_dst,
                                   शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;

    BF(tmp.re, dst[0].re, src[0].re, src[1].re);
    BF(tmp.im, dst[0].im, src[0].im, src[1].im);
    dst[1] = tmp;
}

स्थिर शून्य TX_NAME(ff_tx_fft4_ns)(AVTXContext *s, शून्य *_dst,
                                   शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXSample t1, t2, t3, t4, t5, t6, t7, t8;

    BF(t3, t1, src[0].re, src[1].re);
    BF(t8, t6, src[3].re, src[2].re);
    BF(dst[2].re, dst[0].re, t1, t6);
    BF(t4, t2, src[0].im, src[1].im);
    BF(t7, t5, src[2].im, src[3].im);
    BF(dst[3].im, dst[1].im, t4, t8);
    BF(dst[3].re, dst[1].re, t3, t7);
    BF(dst[2].im, dst[0].im, t2, t5);
}

स्थिर शून्य TX_NAME(ff_tx_fft8_ns)(AVTXContext *s, शून्य *_dst,
                                   शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    ध्रुव TXSample कोटिज्या = TX_TAB(ff_tx_tab_8)[1];

    TX_NAME(ff_tx_fft4_ns)(s, dst, src, stride);

    BF(t1, dst[5].re, src[4].re, -src[5].re);
    BF(t2, dst[5].im, src[4].im, -src[5].im);
    BF(t5, dst[7].re, src[6].re, -src[7].re);
    BF(t6, dst[7].im, src[6].im, -src[7].im);

    BUTTERFLIES(dst[0], dst[2], dst[4], dst[6]);
    TRANSFORM(dst[1], dst[3], dst[5], dst[7], कोटिज्या, कोटिज्या);
}

स्थिर शून्य TX_NAME(ff_tx_fft16_ns)(AVTXContext *s, शून्य *_dst,
                                    शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ध्रुव TXSample *कोटिज्या = TX_TAB(ff_tx_tab_16);

    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    TXSample cos_16_1 = कोटिज्या[1];
    TXSample cos_16_2 = कोटिज्या[2];
    TXSample cos_16_3 = कोटिज्या[3];

    TX_NAME(ff_tx_fft8_ns)(s, dst +  0, src +  0, stride);
    TX_NAME(ff_tx_fft4_ns)(s, dst +  8, src +  8, stride);
    TX_NAME(ff_tx_fft4_ns)(s, dst + 12, src + 12, stride);

    t1 = dst[ 8].re;
    t2 = dst[ 8].im;
    t5 = dst[12].re;
    t6 = dst[12].im;
    BUTTERFLIES(dst[0], dst[4], dst[8], dst[12]);

    TRANSFORM(dst[ 2], dst[ 6], dst[10], dst[14], cos_16_2, cos_16_2);
    TRANSFORM(dst[ 1], dst[ 5], dst[ 9], dst[13], cos_16_1, cos_16_3);
    TRANSFORM(dst[ 3], dst[ 7], dst[11], dst[15], cos_16_3, cos_16_1);
}

DECL_SR_CODELET_DEF(2)
DECL_SR_CODELET_DEF(4)
DECL_SR_CODELET_DEF(8)
DECL_SR_CODELET_DEF(16)
DECL_SR_CODELET(32,16,8)
DECL_SR_CODELET(64,32,16)
DECL_SR_CODELET(128,64,32)
DECL_SR_CODELET(256,128,64)
DECL_SR_CODELET(512,256,128)
DECL_SR_CODELET(1024,512,256)
DECL_SR_CODELET(2048,1024,512)
DECL_SR_CODELET(4096,2048,1024)
DECL_SR_CODELET(8192,4096,2048)
DECL_SR_CODELET(16384,8192,4096)
DECL_SR_CODELET(32768,16384,8192)
DECL_SR_CODELET(65536,32768,16384)
DECL_SR_CODELET(131072,65536,32768)

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_init)(AVTXContext *s,
                                           ध्रुव FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           पूर्णाङ्क len, पूर्णाङ्क inv,
                                           ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;
    पूर्णाङ्क is_inplace = !!(flags & AV_TX_INPLACE);
    FFTXCodeletOptions sub_opts = {
        .map_dir = is_inplace ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    flags &= ~FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len, inv, scale)))
        प्रत्यागम ret;

    यदि (is_inplace && (ret = ff_tx_gen_inplace_map(s, len)))
        प्रत्यागम ret;

    प्रत्यागम 0;
}

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_inplace_small_init)(AVTXContext *s,
                                                         ध्रुव FFTXCodelet *cd,
                                                         uint64_t flags,
                                                         FFTXCodeletOptions *opts,
                                                         पूर्णाङ्क len, पूर्णाङ्क inv,
                                                         ध्रुव शून्य *scale)
{
    यदि (!(s->tmp = av_malloc(len*परिमाण(*s->tmp))))
        प्रत्यागम AVERROR(ENOMEM);
    flags &= ~AV_TX_INPLACE;
    प्रत्यागम TX_NAME(ff_tx_fft_init)(s, cd, flags, opts, len, inv, scale);
}

स्थिर शून्य TX_NAME(ff_tx_fft)(AVTXContext *s, शून्य *_dst,
                               शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst1 = s->flags & AV_TX_INPLACE ? s->tmp : _dst;
    TXComplex *dst2 = _dst;
    पूर्णाङ्क *map = s->sub[0].map;
    पूर्णाङ्क len = s->len;

    /* Compilers can't vectorize this anyway without assuming AVX2, which they
     * generally don't, at least without -march=native -mtune=native */
    प्रति (पूर्णाङ्क i = 0; i < len; i++)
        dst1[i] = src[map[i]];

    s->fn[0](&s->sub[0], dst2, dst1, stride);
}

स्थिर शून्य TX_NAME(ff_tx_fft_inplace)(AVTXContext *s, शून्य *_dst,
                                       शून्य *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;
    ध्रुव पूर्णाङ्क *map = s->sub->map;
    ध्रुव पूर्णाङ्क *inplace_idx = s->map;
    पूर्णाङ्क src_idx, dst_idx;

    src_idx = *inplace_idx++;
    कुरु {
        tmp = src[src_idx];
        dst_idx = map[src_idx];
        कुरु {
            FFSWAP(TXComplex, tmp, src[dst_idx]);
            dst_idx = map[dst_idx];
        } यावत् (dst_idx != src_idx); /* Can be > as well, but was less predictable */
        src[dst_idx] = tmp;
    } यावत् ((src_idx = *inplace_idx++));

    s->fn[0](&s->sub[0], dst, src, stride);
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_def) = {
    .name       = TX_NAME_STR("fft"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors[0] = TX_गुणकः_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_inplace_small_def) = {
    .name       = TX_NAME_STR("fft_inplace_small"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | AV_TX_INPLACE,
    .factors[0] = TX_गुणकः_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 65536,
    .init       = TX_NAME(ff_tx_fft_inplace_small_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः - 256,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_inplace_def) = {
    .name       = TX_NAME_STR("fft_inplace"),
    .function   = TX_NAME(ff_tx_fft_inplace),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | AV_TX_INPLACE,
    .factors[0] = TX_गुणकः_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः - 512,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_init_naive_small)(AVTXContext *s,
                                                       ध्रुव FFTXCodelet *cd,
                                                       uint64_t flags,
                                                       FFTXCodeletOptions *opts,
                                                       पूर्णाङ्क len, पूर्णाङ्क inv,
                                                       ध्रुव शून्य *scale)
{
    ध्रुव द्विगुण phase = s->inv ? 2.0*M_PI/len : -2.0*M_PI/len;

    यदि (!(s->घातांकः = av_malloc(len*len*परिमाण(*s->घातांकः))))
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (पूर्णाङ्क i = 0; i < len; i++) {
        प्रति (पूर्णाङ्क j = 0; j < len; j++) {
            ध्रुव द्विगुण गुणकः = phase*i*j;
            s->घातांकः[i*j] = (TXComplex){
                RESCALE(कोटिज्या(गुणकः)),
                RESCALE(ज्या(गुणकः)),
            };
        }
    }

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_fft_naive)(AVTXContext *s, शून्य *_dst, शून्य *_src,
                                     ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ध्रुव पूर्णाङ्क n = s->len;
    द्विगुण phase = s->inv ? 2.0*M_PI/n : -2.0*M_PI/n;

    stride /= परिमाण(*dst);

    प्रति (पूर्णाङ्क i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        प्रति (पूर्णाङ्क j = 0; j < n; j++) {
            ध्रुव द्विगुण गुणकः = phase*i*j;
            ध्रुव TXComplex mult = {
                RESCALE(कोटिज्या(गुणकः)),
                RESCALE(ज्या(गुणकः)),
            };
            TXComplex res;
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

स्थिर शून्य TX_NAME(ff_tx_fft_naive_small)(AVTXContext *s, शून्य *_dst, शून्य *_src,
                                           ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ध्रुव पूर्णाङ्क n = s->len;

    stride /= परिमाण(*dst);

    प्रति (पूर्णाङ्क i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        प्रति (पूर्णाङ्क j = 0; j < n; j++) {
            TXComplex res;
            ध्रुव TXComplex mult = s->घातांकः[i*j];
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_naive_small_def) = {
    .name       = TX_NAME_STR("fft_naive_small"),
    .function   = TX_NAME(ff_tx_fft_naive_small),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors[0] = TX_गुणकः_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 1024,
    .init       = TX_NAME(ff_tx_fft_init_naive_small),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN/2,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_naive_def) = {
    .name       = TX_NAME_STR("fft_naive"),
    .function   = TX_NAME(ff_tx_fft_naive),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors[0] = TX_गुणकः_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = रिक्त,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_fft_pfa_init)(AVTXContext *s,
                                               ध्रुव FFTXCodelet *cd,
                                               uint64_t flags,
                                               FFTXCodeletOptions *opts,
                                               पूर्णाङ्क len, पूर्णाङ्क inv,
                                               ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret, *tmp, ps = flags & FF_TX_PRESHUFFLE;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };
    size_t extra_tmp_len = 0;
    पूर्णाङ्क len_list[TX_MAX_DECOMPOSITIONS];

    यदि ((ret = ff_tx_decompose_दीर्घता(len_list, TX_TYPE(FFT), len, inv)) < 0)
        प्रत्यागम ret;

    /* Two iterations to test both orderings. */
    प्रति (पूर्णाङ्क i = 0; i < ret; i++) {
        पूर्णाङ्क len1 = len_list[i];
        पूर्णाङ्क len2 = len / len1;

        /* Our ptwo transforms don't support striding the output. */
        यदि (len2 & (len2 - 1))
            FFSWAP(पूर्णाङ्क, len1, len2);

        ff_tx_clear_ctx(s);

        /* First transform */
        sub_opts.map_dir = FF_TX_MAP_GATHER;
        flags &= ~AV_TX_INPLACE;
        flags |=  FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE;
        flags |=  FF_TX_PRESHUFFLE; /* This function handles the permute step */
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len1, inv, scale);

        यदि (ret == AVERROR(ENOMEM)) {
            प्रत्यागम ret;
        } अन्यथा यदि (ret < 0) { /* Try again without a preshuffle flag */
            flags &= ~FF_TX_PRESHUFFLE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len1, inv, scale);
            यदि (ret == AVERROR(ENOMEM))
                प्रत्यागम ret;
            अन्यथा यदि (ret < 0)
                अनुवर्त;
        }

        /* Second transform. */
        sub_opts.map_dir = FF_TX_MAP_SCATTER;
        flags |=  FF_TX_PRESHUFFLE;
retry:
        flags &= ~FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE;
        flags |=  AV_TX_INPLACE;
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len2, inv, scale);

        यदि (ret == AVERROR(ENOMEM)) {
            प्रत्यागम ret;
        } अन्यथा यदि (ret < 0) { /* Try again with an out-of-place transform */
            flags |= FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE;
            flags &= ~AV_TX_INPLACE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len2, inv, scale);
            यदि (ret == AVERROR(ENOMEM)) {
                प्रत्यागम ret;
            } अन्यथा यदि (ret < 0) {
                यदि (flags & FF_TX_PRESHUFFLE) { /* Retry again without a preshuf flag */
                    flags &= ~FF_TX_PRESHUFFLE;
                    गच्छ retry;
                } अन्यथा {
                    अनुवर्त;
                }
            }
        }

        /* Success */
        भङ्ग;
    }

    /* If nothing was successful, error out */
    यदि (ret < 0)
        प्रत्यागम ret;

    /* Generate PFA map */
    यदि ((ret = ff_tx_gen_compound_mapping(s, opts, 0,
                                          s->sub[0].len, s->sub[1].len)))
        प्रत्यागम ret;

    यदि (!(s->tmp = av_malloc(len*परिमाण(*s->tmp))))
        प्रत्यागम AVERROR(ENOMEM);

    /* Flatten input map */
    tmp = (पूर्णाङ्क *)s->tmp;
    प्रति (पूर्णाङ्क k = 0; k < len; k += s->sub[0].len) {
        स्मृतिं_प्रतिलिख(tmp, &s->map[k], s->sub[0].len*परिमाण(*tmp));
        प्रति (पूर्णाङ्क i = 0; i < s->sub[0].len; i++)
            s->map[k + i] = tmp[s->sub[0].map[i]];
    }

    /* Only allocate extra temporary memory if we need it */
    यदि (!(s->sub[1].flags & AV_TX_INPLACE))
        extra_tmp_len = len;
    अन्यथा यदि (!ps)
        extra_tmp_len = s->sub[0].len;

    यदि (extra_tmp_len && !(s->घातांकः = av_malloc(extra_tmp_len*परिमाण(*s->घातांकः))))
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_fft_pfa)(AVTXContext *s, शून्य *बहिर्गमनम्_3,
                                   शून्य *अन्तर्_3, ptrdiff_t stride)
{
    ध्रुव पूर्णाङ्क n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ध्रुव पूर्णाङ्क *अन्तर्_map = s->map, *बहिर्गमनम्_map = अन्तर्_map + l;
    ध्रुव पूर्णाङ्क *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->घातांकः;
    TXComplex *अन्तर् = अन्तर्_3, *बहिर्गमनम् = बहिर्गमनम्_3;

    stride /= परिमाण(*बहिर्गमनम्);

    प्रति (पूर्णाङ्क i = 0; i < m; i++) {
        प्रति (पूर्णाङ्क j = 0; j < n; j++)
            s->घातांकः[j] = अन्तर्[अन्तर्_map[i*n + j]];
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], s->घातांकः, m*परिमाण(TXComplex));
    }

    प्रति (पूर्णाङ्क i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], परिमाण(TXComplex));

    प्रति (पूर्णाङ्क i = 0; i < l; i++)
        बहिर्गमनम्[i*stride] = tmp1[बहिर्गमनम्_map[i]];
}

स्थिर शून्य TX_NAME(ff_tx_fft_pfa_ns)(AVTXContext *s, शून्य *बहिर्गमनम्_3,
                                      शून्य *अन्तर्_3, ptrdiff_t stride)
{
    ध्रुव पूर्णाङ्क n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ध्रुव पूर्णाङ्क *अन्तर्_map = s->map, *बहिर्गमनम्_map = अन्तर्_map + l;
    ध्रुव पूर्णाङ्क *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->घातांकः;
    TXComplex *अन्तर् = अन्तर्_3, *बहिर्गमनम् = बहिर्गमनम्_3;

    stride /= परिमाण(*बहिर्गमनम्);

    प्रति (पूर्णाङ्क i = 0; i < m; i++)
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], &अन्तर्[i*n], m*परिमाण(TXComplex));

    प्रति (पूर्णाङ्क i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], परिमाण(TXComplex));

    प्रति (पूर्णाङ्क i = 0; i < l; i++)
        बहिर्गमनम्[i*stride] = tmp1[बहिर्गमनम्_map[i]];
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_pfa_def) = {
    .name       = TX_NAME_STR("fft_pfa"),
    .function   = TX_NAME(ff_tx_fft_pfa),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors    = { 7, 5, 3, 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_fft_pfa_ns_def) = {
    .name       = TX_NAME_STR("fft_pfa_ns"),
    .function   = TX_NAME(ff_tx_fft_pfa_ns),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE |
                  FF_TX_PRESHUFFLE,
    .factors    = { 7, 5, 3, 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_mdct_naive_init)(AVTXContext *s,
                                                  ध्रुव FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  पूर्णाङ्क len, पूर्णाङ्क inv,
                                                  ध्रुव शून्य *scale)
{
    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;
    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_mdct_naive_fwd)(AVTXContext *s, शून्य *_dst,
                                          शून्य *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    द्विगुण scale = s->scale_d;
    पूर्णाङ्क len = s->len;
    ध्रुव द्विगुण phase = M_PI/(4.0*len);

    stride /= परिमाण(*dst);

    प्रति (पूर्णाङ्क i = 0; i < len; i++) {
        द्विगुण योग = 0.0;
        प्रति (पूर्णाङ्क j = 0; j < len*2; j++) {
            पूर्णाङ्क a = (2*j + 1 + len) * (2*i + 1);
            योग += UNSCALE(src[j]) * कोटिज्या(a * phase);
        }
        dst[i*stride] = RESCALE(योग*scale);
    }
}

स्थिर शून्य TX_NAME(ff_tx_mdct_naive_inv)(AVTXContext *s, शून्य *_dst,
                                          शून्य *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    द्विगुण scale = s->scale_d;
    पूर्णाङ्क len = s->len >> 1;
    पूर्णाङ्क len2 = len*2;
    ध्रुव द्विगुण phase = M_PI/(4.0*len2);

    stride /= परिमाण(*src);

    प्रति (पूर्णाङ्क i = 0; i < len; i++) {
        द्विगुण योग_d = 0.0;
        द्विगुण योग_u = 0.0;
        द्विगुण i_d = phase * (4*len  - 2*i - 1);
        द्विगुण i_u = phase * (3*len2 + 2*i + 1);
        प्रति (पूर्णाङ्क j = 0; j < len2; j++) {
            द्विगुण a = (2 * j + 1);
            द्विगुण a_d = कोटिज्या(a * i_d);
            द्विगुण a_u = कोटिज्या(a * i_u);
            द्विगुण val = UNSCALE(src[j*stride]);
            योग_d += a_d * val;
            योग_u += a_u * val;
        }
        dst[i +   0] = RESCALE( योग_d*scale);
        dst[i + len] = RESCALE(-योग_u*scale);
    }
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_naive_fwd_def) = {
    .name       = TX_NAME_STR("mdct_naive_fwd"),
    .function   = TX_NAME(ff_tx_mdct_naive_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_गुणकः_ANY }, /* MDCTs need an even length */
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_naive_inv_def) = {
    .name       = TX_NAME_STR("mdct_naive_inv"),
    .function   = TX_NAME(ff_tx_mdct_naive_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_mdct_init)(AVTXContext *s,
                                            ध्रुव FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            पूर्णाङ्क len, पूर्णाङ्क inv,
                                            ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;
    FFTXCodeletOptions sub_opts = {
        .map_dir = !inv ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* First try with an in-place transform */

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale))) {
        flags &= ~FF_TX_PRESHUFFLE; /* Now try with a generic FFT */
        यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                    inv, scale)))
            प्रत्यागम ret;
    }

    s->map = av_malloc((len >> 1)*परिमाण(*s->map));
    यदि (!s->map)
        प्रत्यागम AVERROR(ENOMEM);

    /* If we need to preshuffle copy the map from the subcontext */
    यदि (s->sub[0].flags & FF_TX_PRESHUFFLE) {
        स्मृतिं_प्रतिलिख(s->map, s->sub->map, (len >> 1)*परिमाण(*s->map));
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < len >> 1; i++)
            s->map[i] = i;
    }

    यदि ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : रिक्त)))
        प्रत्यागम ret;

    /* Saves a multiply in a hot path. */
    यदि (inv)
        प्रति (पूर्णाङ्क i = 0; i < (s->len >> 1); i++)
            s->map[i] <<= 1;

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_mdct_fwd)(AVTXContext *s, शून्य *_dst, शून्य *_src,
                                    ptrdiff_t stride)
{
    TXSample *src = _src, *dst = _dst;
    TXComplex *घातांकः = s->घातांकः, tmp, *z = _dst;
    ध्रुव पूर्णाङ्क len2 = s->len >> 1;
    ध्रुव पूर्णाङ्क len4 = s->len >> 2;
    ध्रुव पूर्णाङ्क len3 = len2 * 3;
    ध्रुव पूर्णाङ्क *sub_map = s->map;

    stride /= परिमाण(*dst);

    प्रति (पूर्णाङ्क i = 0; i < len2; i++) { /* Folding and pre-reindexing */
        ध्रुव पूर्णाङ्क k = 2*i;
        ध्रुव पूर्णाङ्क idx = sub_map[i];
        यदि (k < len2) {
            tmp.re = FOLD(-src[ len2 + k],  src[1*len2 - 1 - k]);
            tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);
        } अन्यथा {
            tmp.re = FOLD(-src[ len2 + k], -src[5*len2 - 1 - k]);
            tmp.im = FOLD( src[-len2 + k], -src[1*len3 - 1 - k]);
        }
        CMUL(z[idx].im, z[idx].re, tmp.re, tmp.im, घातांकः[i].re, घातांकः[i].im);
    }

    s->fn[0](&s->sub[0], z, z, परिमाण(TXComplex));

    प्रति (पूर्णाङ्क i = 0; i < len4; i++) {
        ध्रुव पूर्णाङ्क i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].re, z[i1].im };
        TXComplex src0 = { z[i0].re, z[i0].im };

        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,
             घातांकः[i0].im, घातांकः[i0].re);
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,
             घातांकः[i1].im, घातांकः[i1].re);
    }
}

स्थिर शून्य TX_NAME(ff_tx_mdct_inv)(AVTXContext *s, शून्य *_dst, शून्य *_src,
                                    ptrdiff_t stride)
{
    TXComplex *z = _dst, *घातांकः = s->घातांकः;
    ध्रुव TXSample *src = _src, *in1, *in2;
    ध्रुव पूर्णाङ्क len2 = s->len >> 1;
    ध्रुव पूर्णाङ्क len4 = s->len >> 2;
    ध्रुव पूर्णाङ्क *sub_map = s->map;

    stride /= परिमाण(*src);
    in1 = src;
    in2 = src + ((len2*2) - 1) * stride;

    प्रति (पूर्णाङ्क i = 0; i < len2; i++) {
        पूर्णाङ्क k = sub_map[i];
        TXComplex tmp = { in2[-k*stride], in1[k*stride] };
        CMUL3(z[i], tmp, घातांकः[i]);
    }

    s->fn[0](&s->sub[0], z, z, परिमाण(TXComplex));

    घातांकः += len2;
    प्रति (पूर्णाङ्क i = 0; i < len4; i++) {
        ध्रुव पूर्णाङ्क i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].im, z[i1].re };
        TXComplex src0 = { z[i0].im, z[i0].re };

        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, घातांकः[i1].im, घातांकः[i1].re);
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, घातांकः[i0].im, घातांकः[i0].re);
    }
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_fwd_def) = {
    .name       = TX_NAME_STR("mdct_fwd"),
    .function   = TX_NAME(ff_tx_mdct_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_inv_def) = {
    .name       = TX_NAME_STR("mdct_inv"),
    .function   = TX_NAME(ff_tx_mdct_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_mdct_inv_पूर्णम्_init)(AVTXContext *s,
                                                     ध्रुव FFTXCodelet *cd,
                                                     uint64_t flags,
                                                     FFTXCodeletOptions *opts,
                                                     पूर्णाङ्क len, पूर्णाङ्क inv,
                                                     ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~AV_TX_पूर्णम्_IMDCT;

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(MDCT), flags, रिक्त, len, 1, scale)))
        प्रत्यागम ret;

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_mdct_inv_पूर्णम्)(AVTXContext *s, शून्य *_dst,
                                         शून्य *_src, ptrdiff_t stride)
{
    पूर्णाङ्क len  = s->len << 1;
    पूर्णाङ्क len2 = len >> 1;
    पूर्णाङ्क len4 = len >> 2;
    TXSample *dst = _dst;

    s->fn[0](&s->sub[0], dst + len4, _src, stride);

    stride /= परिमाण(*dst);

    प्रति (पूर्णाङ्क i = 0; i < len4; i++) {
        dst[            i*stride] = -dst[(len2 - i - 1)*stride];
        dst[(len - i - 1)*stride] =  dst[(len2 + i + 0)*stride];
    }
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_inv_पूर्णम्_def) = {
    .name       = TX_NAME_STR("mdct_inv_full"),
    .function   = TX_NAME(ff_tx_mdct_inv_पूर्णम्),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | AV_TX_पूर्णम्_IMDCT,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_inv_पूर्णम्_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_mdct_pfa_init)(AVTXContext *s,
                                                ध्रुव FFTXCodelet *cd,
                                                uint64_t flags,
                                                FFTXCodeletOptions *opts,
                                                पूर्णाङ्क len, पूर्णाङ्क inv,
                                                ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret, sub_len;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    len >>= 1;
    sub_len = len / cd->factors[0];

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        प्रत्यागम ret;

    यदि ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        प्रत्यागम ret;

    /* Our 15-point transform is also a compound one, so embed its input map */
    यदि (cd->factors[0] == 15)
        TX_EMBED_निवेशः_PFA_MAP(s->map, len, 3, 5);

    यदि ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : रिक्त)))
        प्रत्यागम ret;

    /* Saves multiplies in loops. */
    प्रति (पूर्णाङ्क i = 0; i < len; i++)
        s->map[i] <<= 1;

    यदि (!(s->tmp = av_malloc(len*परिमाण(*s->tmp))))
        प्रत्यागम AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    प्रत्यागम 0;
}

#परिभाषय DECL_COMP_IMDCT(N)                                                     \
स्थिर शून्य TX_NAME(ff_tx_mdct_pfa_##N##xM_inv)(AVTXContext *s, शून्य *_dst,    \
                                                शून्य *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXComplex *z = _dst, *घातांकः = s->घातांकः;                                        \
    ध्रुव TXSample *src = _src, *in1, *in2;                                    \
    ध्रुव पूर्णाङ्क len4 = s->len >> 2;                                              \
    ध्रुव पूर्णाङ्क len2 = s->len >> 1;                                              \
    ध्रुव पूर्णाङ्क m = s->sub->len;                                                 \
    ध्रुव पूर्णाङ्क *अन्तर्_map = s->map, *बहिर्गमनम्_map = अन्तर्_map + N*m;                       \
    ध्रुव पूर्णाङ्क *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= परिमाण(*src); /* To convert it from bytes */                     \
    in1 = src;                                                                 \
    in2 = src + ((N*m*2) - 1) * stride;                                        \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < len2; i += N) {                                        \
        प्रति (पूर्णाङ्क j = 0; j < N; j++) {                                          \
            ध्रुव पूर्णाङ्क k = अन्तर्_map[j];                                           \
            TXComplex tmp = { in2[-k*stride], in1[k*stride] };                 \
            CMUL3(fft##N##in[j], tmp, घातांकः[j]);                                 \
        }                                                                      \
        fft##N(s->tmp + *(sub_map++), fft##N##in, m);                          \
        घातांकः += N;                                                              \
        अन्तर्_map += N;                                                           \
    }                                                                          \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, परिमाण(TXComplex));   \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < len4; i++) {                                           \
        ध्रुव पूर्णाङ्क i0 = len4 + i, i1 = len4 - i - 1;                            \
        ध्रुव पूर्णाङ्क s0 = बहिर्गमनम्_map[i0], s1 = बहिर्गमनम्_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].im, s->tmp[s1].re };                     \
        TXComplex src0 = { s->tmp[s0].im, s->tmp[s0].re };                     \
                                                                               \
        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, घातांकः[i1].im, घातांकः[i1].re);    \
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, घातांकः[i0].im, घातांकः[i0].re);    \
    }                                                                          \
}                                                                              \
                                                                               \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_inv_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_inv"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_inv),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_INVERSE_ONLY,   \
    .factors    = { N, TX_गुणकः_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

DECL_COMP_IMDCT(3)
DECL_COMP_IMDCT(5)
DECL_COMP_IMDCT(7)
DECL_COMP_IMDCT(9)
DECL_COMP_IMDCT(15)

#परिभाषय DECL_COMP_MDCT(N)                                                      \
स्थिर शून्य TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd)(AVTXContext *s, शून्य *_dst,    \
                                                शून्य *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXSample *src = _src, *dst = _dst;                                         \
    TXComplex *घातांकः = s->घातांकः, tmp;                                              \
    ध्रुव पूर्णाङ्क m = s->sub->len;                                                 \
    ध्रुव पूर्णाङ्क len4 = N*m;                                                      \
    ध्रुव पूर्णाङ्क len3 = len4 * 3;                                                 \
    ध्रुव पूर्णाङ्क len8 = s->len >> 2;                                              \
    ध्रुव पूर्णाङ्क *अन्तर्_map = s->map, *बहिर्गमनम्_map = अन्तर्_map + N*m;                       \
    ध्रुव पूर्णाङ्क *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= परिमाण(*dst);                                                    \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < m; i++) { /* Folding and pre-reindexing */             \
        प्रति (पूर्णाङ्क j = 0; j < N; j++) {                                          \
            ध्रुव पूर्णाङ्क k = अन्तर्_map[i*N + j];                                     \
            यदि (k < len4) {                                                    \
                tmp.re = FOLD(-src[ len4 + k],  src[1*len4 - 1 - k]);          \
                tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);          \
            } अन्यथा {                                                           \
                tmp.re = FOLD(-src[ len4 + k], -src[5*len4 - 1 - k]);          \
                tmp.im = FOLD( src[-len4 + k], -src[1*len3 - 1 - k]);          \
            }                                                                  \
            CMUL(fft##N##in[j].im, fft##N##in[j].re, tmp.re, tmp.im,           \
                 घातांकः[k >> 1].re, घातांकः[k >> 1].im);                              \
        }                                                                      \
        fft##N(s->tmp + sub_map[i], fft##N##in, m);                            \
    }                                                                          \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, परिमाण(TXComplex));   \
                                                                               \
    प्रति (पूर्णाङ्क i = 0; i < len8; i++) {                                           \
        ध्रुव पूर्णाङ्क i0 = len8 + i, i1 = len8 - i - 1;                            \
        ध्रुव पूर्णाङ्क s0 = बहिर्गमनम्_map[i0], s1 = बहिर्गमनम्_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].re, s->tmp[s1].im };                     \
        TXComplex src0 = { s->tmp[s0].re, s->tmp[s0].im };                     \
                                                                               \
        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,    \
             घातांकः[i0].im, घातांकः[i0].re);                                          \
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,    \
             घातांकः[i1].im, घातांकः[i1].re);                                          \
    }                                                                          \
}                                                                              \
                                                                               \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_fwd"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_FORWARD_ONLY,   \
    .factors    = { N, TX_गुणकः_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

DECL_COMP_MDCT(3)
DECL_COMP_MDCT(5)
DECL_COMP_MDCT(7)
DECL_COMP_MDCT(9)
DECL_COMP_MDCT(15)

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_rdft_init)(AVTXContext *s,
                                            ध्रुव FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            पूर्णाङ्क len, पूर्णाङ्क inv,
                                            ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;
    द्विगुण f, m;
    TXSample *tab;
    uint64_t r2r = flags & AV_TX_REAL_गन्तव्यम्_REAL;
    पूर्णाङ्क len4 = FFALIGN(len, 4) / 4;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~(AV_TX_REAL_गन्तव्यम्_REAL | AV_TX_REAL_गन्तव्यम्_IMAGINARY);

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, रिक्त, len >> 1, inv, scale)))
        प्रत्यागम ret;

    यदि (!(s->घातांकः = av_mallocz((8 + 2*len4)*परिमाण(*s->घातांकः))))
        प्रत्यागम AVERROR(ENOMEM);

    tab = (TXSample *)s->घातांकः;

    f = 2*M_PI/len;

    m = (inv ? 2*s->scale_d : s->scale_d);

    *tab++ = RESCALE((inv ? 0.5 : 1.0) * m);
    *tab++ = RESCALE(inv ? 0.5*m : 1.0*m);
    *tab++ = RESCALE( m);
    *tab++ = RESCALE(-m);

    *tab++ = RESCALE( (0.5 - 0.0) * m);
    यदि (r2r)
        *tab++ = 1 / s->scale_f;
    अन्यथा
        *tab++ = RESCALE( (0.0 - 0.5) * m);
    *tab++ = RESCALE( (0.5 - inv) * m);
    *tab++ = RESCALE(-(0.5 - inv) * m);

    प्रति (पूर्णाङ्क i = 0; i < len4; i++)
        *tab++ = RESCALE(कोटिज्या(i*f));

    tab = ((TXSample *)s->घातांकः) + len4 + 8;

    प्रति (पूर्णाङ्क i = 0; i < len4; i++)
        *tab++ = RESCALE(कोटिज्या(((len - i*4)/4.0)*f)) * (inv ? 1 : -1);

    प्रत्यागम 0;
}

#परिभाषय DECL_RDFT(n, inv)                                                      \
स्थिर शून्य TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, शून्य *_dst,               \
                                     शून्य *_src, ptrdiff_t stride)             \
{                                                                              \
    ध्रुव पूर्णाङ्क len2 = s->len >> 1;                                              \
    ध्रुव पूर्णाङ्क len4 = s->len >> 2;                                              \
    ध्रुव TXSample *fact = (शून्य *)s->घातांकः;                                     \
    ध्रुव TXSample *tcos = fact + 8;                                           \
    ध्रुव TXSample *tsin = tcos + len4;                                        \
    TXComplex *दत्त = inv ? _src : _dst;                                       \
    TXComplex t[3];                                                            \
                                                                               \
    यदि (!inv)                                                                  \
        s->fn[0](&s->sub[0], दत्त, _src, परिमाण(TXComplex));                   \
    अन्यथा                                                                       \
        दत्त[0].im = दत्त[len2].re;                                            \
                                                                               \
    /* The DC value's both components are real, but we need to change them     \
     * into complex values. Also, the middle of the array is special-cased.    \
     * These operations can be done before or after the loop. */               \
    t[0].re = दत्त[0].re;                                                      \
    दत्त[0].re = t[0].re + दत्त[0].im;                                         \
    दत्त[0].im = t[0].re - दत्त[0].im;                                         \
    दत्त[   0].re = MULT(fact[0], दत्त[   0].re);                              \
    दत्त[   0].im = MULT(fact[1], दत्त[   0].im);                              \
    दत्त[len4].re = MULT(fact[2], दत्त[len4].re);                              \
    दत्त[len4].im = MULT(fact[3], दत्त[len4].im);                              \
                                                                               \
    प्रति (पूर्णाङ्क i = 1; i < len4; i++) {                                           \
        /* Separate even and odd FFTs */                                       \
        t[0].re = MULT(fact[4], (दत्त[i].re + दत्त[len2 - i].re));             \
        t[0].im = MULT(fact[5], (दत्त[i].im - दत्त[len2 - i].im));             \
        t[1].re = MULT(fact[6], (दत्त[i].im + दत्त[len2 - i].im));             \
        t[1].im = MULT(fact[7], (दत्त[i].re - दत्त[len2 - i].re));             \
                                                                               \
        /* Apply twiddle factors to the odd FFT and add to the even FFT */     \
        CMUL(t[2].re, t[2].im, t[1].re, t[1].im, tcos[i], tsin[i]);            \
                                                                               \
        दत्त[       i].re = t[0].re + t[2].re;                                 \
        दत्त[       i].im = t[2].im - t[0].im;                                 \
        दत्त[len2 - i].re = t[0].re - t[2].re;                                 \
        दत्त[len2 - i].im = t[2].im + t[0].im;                                 \
    }                                                                          \
                                                                               \
    यदि (inv) {                                                                 \
        s->fn[0](&s->sub[0], _dst, दत्त, परिमाण(TXComplex));                   \
    } अन्यथा {                                                                   \
        /* Move [0].im to the last position, as convention requires */         \
        दत्त[len2].re = दत्त[0].im;                                            \
        दत्त[   0].im = दत्त[len2].im = 0;                                     \
    }                                                                          \
}                                                                              \
                                                                               \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE |       \
                  (inv ? FF_TX_INVERSE_ONLY : FF_TX_FORWARD_ONLY),             \
    .factors    = { 4, TX_गुणकः_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = 4,                                                           \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

DECL_RDFT(r2c,  0)
DECL_RDFT(c2r,  1)

#परिभाषय DECL_RDFT_HALF(n, बहुलकम्, mod2)                                          \
स्थिर शून्य TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, शून्य *_dst,               \
                                        शून्य *_src, ptrdiff_t stride)          \
{                                                                              \
    ध्रुव पूर्णाङ्क len = s->len;                                                    \
    ध्रुव पूर्णाङ्क len2 = len >> 1;                                                 \
    ध्रुव पूर्णाङ्क len4 = len >> 2;                                                 \
    ध्रुव पूर्णाङ्क aligned_len4 = FFALIGN(len, 4)/4;                                \
    ध्रुव TXSample *fact = (शून्य *)s->घातांकः;                                     \
    ध्रुव TXSample *tcos = fact + 8;                                           \
    ध्रुव TXSample *tsin = tcos + aligned_len4;                                \
    TXComplex *दत्त = _dst;                                                    \
    TXSample *बहिर्गमनम् = _dst; /* Half-complex is forward-only */                   \
    TXSample tmp_dc;                                                           \
    av_अप्रयुक्तम् TXSample tmp_mid;                                                \
    TXSample tmp[4];                                                           \
    TXComplex sf, sl;                                                          \
                                                                               \
    s->fn[0](&s->sub[0], _dst, _src, परिमाण(TXComplex));                       \
                                                                               \
    tmp_dc = दत्त[0].re;                                                       \
    दत्त[   0].re = tmp_dc + दत्त[0].im;                                       \
    tmp_dc        = tmp_dc - दत्त[0].im;                                       \
                                                                               \
    दत्त[   0].re = MULT(fact[0], दत्त[   0].re);                              \
    tmp_dc        = MULT(fact[1],        tmp_dc);                              \
    दत्त[len4].re = MULT(fact[2], दत्त[len4].re);                              \
                                                                               \
    यदि (!mod2) {                                                               \
        दत्त[len4].im = MULT(fact[3], दत्त[len4].im);                          \
    } अन्यथा {                                                                   \
        sf = दत्त[len4];                                                       \
        sl = दत्त[len4 + 1];                                                   \
        यदि (बहुलकम् == AV_TX_REAL_गन्तव्यम्_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        अन्यथा                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        यदि (बहुलकम् == AV_TX_REAL_गन्तव्यम्_REAL) {                                      \
            tmp[3]  = tmp[1]*tcos[len4] - tmp[2]*tsin[len4];                   \
            tmp_mid = (tmp[0] - tmp[3]);                                       \
        } अन्यथा {                                                               \
            tmp[3]  = tmp[1]*tsin[len4] + tmp[2]*tcos[len4];                   \
            tmp_mid = (tmp[0] + tmp[3]);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* NOTE: unrolling this breaks non-mod8 lengths */                         \
    प्रति (पूर्णाङ्क i = 1; i <= len4; i++) {                                          \
        TXSample tmp[4];                                                       \
        TXComplex sf = दत्त[i];                                                \
        TXComplex sl = दत्त[len2 - i];                                         \
                                                                               \
        यदि (बहुलकम् == AV_TX_REAL_गन्तव्यम्_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        अन्यथा                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
                                                                               \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        यदि (बहुलकम् == AV_TX_REAL_गन्तव्यम्_REAL) {                                      \
            tmp[3]           = tmp[1]*tcos[i] - tmp[2]*tsin[i];                \
            बहिर्गमनम्[i]           = (tmp[0] + tmp[3]);                              \
            बहिर्गमनम्[len - i]     = (tmp[0] - tmp[3]);                              \
        } अन्यथा {                                                               \
            tmp[3]           = tmp[1]*tsin[i] + tmp[2]*tcos[i];                \
            बहिर्गमनम्[i - 1]       = (tmp[3] - tmp[0]);                              \
            बहिर्गमनम्[len - i - 1] = (tmp[0] + tmp[3]);                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    प्रति (पूर्णाङ्क i = 1; i < (len4 + (बहुलकम् == AV_TX_REAL_गन्तव्यम्_IMAGINARY)); i++)       \
        बहिर्गमनम्[len2 - i] = बहिर्गमनम्[len - i];                                          \
                                                                               \
    यदि (बहुलकम् == AV_TX_REAL_गन्तव्यम्_REAL) {                                          \
        बहिर्गमनम्[len2] = tmp_dc;                                                    \
        यदि (mod2)                                                              \
            बहिर्गमनम्[len4 + 1] = tmp_mid * fact[5];                                 \
    } अन्यथा यदि (mod2) {                                                         \
        बहिर्गमनम्[len4] = tmp_mid;                                                   \
    }                                                                          \
}                                                                              \
                                                                               \
स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | बहुलकम् |                     \
                  FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_FORWARD_ONLY,                     \
    .factors    = { 2 + 2*(!mod2), TX_गुणकः_ANY },                            \
    .nb_factors = 2,                                                           \
    .min_len    = 2 + 2*(!mod2),                                               \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_आधारः,                                             \
};

DECL_RDFT_HALF(r2r,      AV_TX_REAL_गन्तव्यम्_REAL,      0)
DECL_RDFT_HALF(r2r_mod2, AV_TX_REAL_गन्तव्यम्_REAL,      1)
DECL_RDFT_HALF(r2i,      AV_TX_REAL_गन्तव्यम्_IMAGINARY, 0)
DECL_RDFT_HALF(r2i_mod2, AV_TX_REAL_गन्तव्यम्_IMAGINARY, 1)

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_dct_init)(AVTXContext *s,
                                           ध्रुव FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           पूर्णाङ्क len, पूर्णाङ्क inv,
                                           ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;
    द्विगुण freq;
    TXSample *tab;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    यदि (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, रिक्त, len, inv, &rsc)))
        प्रत्यागम ret;

    s->घातांकः = av_malloc((len/2)*3*परिमाण(TXSample));
    यदि (!s->घातांकः)
        प्रत्यागम AVERROR(ENOMEM);

    tab = (TXSample *)s->घातांकः;

    freq = M_PI/(len*2);

    प्रति (पूर्णाङ्क i = 0; i < len; i++)
        tab[i] = RESCALE(कोटिज्या(i*freq)*(!inv + 1));

    यदि (inv) {
        प्रति (पूर्णाङ्क i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(0.5 / ज्या((2*i + 1)*freq));
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(कोटिज्या((len - 2*i - 1)*freq));
    }

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_dctII)(AVTXContext *s, शून्य *_dst,
                                 शून्य *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ध्रुव पूर्णाङ्क len = s->len;
    ध्रुव पूर्णाङ्क len2 = len >> 1;
    ध्रुव TXSample *घातांकः = (शून्य *)s->घातांकः;
    TXSample अग्र;
#यदि_परिभाषितम् TX_INT32
    int64_t tmp1, tmp2;
#अन्यथा
    TXSample tmp1, tmp2;
#यदि_अन्तः

    प्रति (पूर्णाङ्क i = 0; i < len2; i++) {
        TXSample in1 = src[i];
        TXSample in2 = src[len - i - 1];
        TXSample s    = घातांकः[len + i];

#यदि_परिभाषितम् TX_INT32
        tmp1 = in1 + in2;
        tmp2 = in1 - in2;

        tmp1 >>= 1;
        tmp2 *= s;

        tmp2 = (tmp2 + 0x40000000) >> 31;
#अन्यथा
        tmp1 = (in1 + in2)*0.5;
        tmp2 = (in1 - in2)*s;
#यदि_अन्तः

        src[i]           = tmp1 + tmp2;
        src[len - i - 1] = tmp1 - tmp2;
    }

    s->fn[0](&s->sub[0], dst, src, परिमाण(TXComplex));

    अग्र = dst[len];

    प्रति (पूर्णाङ्क i = len - 2; i > 0; i -= 2) {
        TXSample tmp;

        CMUL(tmp, dst[i], घातांकः[len - i], घातांकः[i], dst[i + 0], dst[i + 1]);

        dst[i + 1] = अग्र;

        अग्र += tmp;
    }

#यदि_परिभाषितम् TX_INT32
    tmp1 = ((int64_t)घातांकः[0]) * ((int64_t)dst[0]);
    dst[0] = (tmp1 + 0x40000000) >> 31;
#अन्यथा
    dst[0] = घातांकः[0] * dst[0];
#यदि_अन्तः
    dst[1] = अग्र;
}

स्थिर शून्य TX_NAME(ff_tx_dctIII)(AVTXContext *s, शून्य *_dst,
                                  शून्य *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ध्रुव पूर्णाङ्क len = s->len;
    ध्रुव पूर्णाङ्क len2 = len >> 1;
    ध्रुव TXSample *घातांकः = (शून्य *)s->घातांकः;
#यदि_परिभाषितम् TX_INT32
    int64_t  tmp1, tmp2 = src[len - 1];
    tmp2 = (2*tmp2 + 0x40000000) >> 31;
#अन्यथा
    TXSample tmp1, tmp2 = 2*src[len - 1];
#यदि_अन्तः

    src[len] = tmp2;

    प्रति (पूर्णाङ्क i = len - 2; i >= 2; i -= 2) {
        TXSample val1 = src[i - 0];
        TXSample val2 = src[i - 1] - src[i + 1];

        CMUL(src[i + 1], src[i], घातांकः[len - i], घातांकः[i], val1, val2);
    }

    s->fn[0](&s->sub[0], dst, src, परिमाण(भिन्न));

    प्रति (पूर्णाङ्क i = 0; i < len2; i++) {
        TXSample in1 = dst[i];
        TXSample in2 = dst[len - i - 1];
        TXSample c   = घातांकः[len + i];

        tmp1 = in1 + in2;
        tmp2 = in1 - in2;
        tmp2 *= c;
#यदि_परिभाषितम् TX_INT32
        tmp2 = (tmp2 + 0x40000000) >> 31;
#यदि_अन्तः

        dst[i]            = tmp1 + tmp2;
        dst[len - i - 1]  = tmp1 - tmp2;
    }
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_dctII_def) = {
    .name       = TX_NAME_STR("dctII"),
    .function   = TX_NAME(ff_tx_dctII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_गुणकः_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_dctIII_def) = {
    .name       = TX_NAME_STR("dctIII"),
    .function   = TX_NAME(ff_tx_dctIII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_गुणकः_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर av_cold पूर्णाङ्क TX_NAME(ff_tx_dcstI_init)(AVTXContext *s,
                                             ध्रुव FFTXCodelet *cd,
                                             uint64_t flags,
                                             FFTXCodeletOptions *opts,
                                             पूर्णाङ्क len, पूर्णाङ्क inv,
                                             ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    यदि (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    /* We want a half-complex RDFT */
    flags |= cd->type == TX_TYPE(DCT_I) ? AV_TX_REAL_गन्तव्यम्_REAL :
                                          AV_TX_REAL_गन्तव्यम्_IMAGINARY;

    यदि ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, रिक्त,
                                (len - 1 + 2*(cd->type == TX_TYPE(DST_I)))*2,
                                0, &rsc)))
        प्रत्यागम ret;

    s->tmp = av_mallocz((len + 1)*2*परिमाण(TXSample));
    यदि (!s->tmp)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

स्थिर शून्य TX_NAME(ff_tx_dctI)(AVTXContext *s, शून्य *_dst,
                                शून्य *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ध्रुव पूर्णाङ्क len = s->len - 1;
    TXSample *tmp = (TXSample *)s->tmp;

    stride /= परिमाण(TXSample);

    प्रति (पूर्णाङ्क i = 0; i < len; i++)
        tmp[i] = tmp[2*len - i] = src[i * stride];

    tmp[len] = src[len * stride]; /*मध्यः*/

    s->fn[0](&s->sub[0], dst, tmp, परिमाण(TXSample));
}

स्थिर शून्य TX_NAME(ff_tx_dstI)(AVTXContext *s, शून्य *_dst,
                                शून्य *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ध्रुव पूर्णाङ्क len = s->len + 1;
    TXSample *tmp = (शून्य *)s->tmp;

    stride /= परिमाण(TXSample);

    tmp[0] = 0;

    प्रति (पूर्णाङ्क i = 1; i < len; i++) {
        TXSample a = src[(i - 1) * stride];
        tmp[i] = -a;
        tmp[2*len - i] = a;
    }

    tmp[len] = 0; /* i == n, Nyquist */

    s->fn[0](&s->sub[0], dst, tmp, परिमाण(भिन्न));
}

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_dctI_def) = {
    .name       = TX_NAME_STR("dctI"),
    .function   = TX_NAME(ff_tx_dctI),
    .type       = TX_TYPE(DCT_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

स्थिर ध्रुव FFTXCodelet TX_NAME(ff_tx_dstI_def) = {
    .name       = TX_NAME_STR("dstI"),
    .function   = TX_NAME(ff_tx_dstI),
    .type       = TX_TYPE(DST_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_बहिर्गमनम्_सम्बन्धि_PLACE,
    .factors    = { 2, TX_गुणकः_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_आधारः,
};

पूर्णाङ्क TX_TAB(ff_tx_mdct_gen_exp)(AVTXContext *s, पूर्णाङ्क *pre_tab)
{
    पूर्णाङ्क off = 0;
    पूर्णाङ्क len4 = s->len >> 1;
    द्विगुण scale = s->scale_d;
    ध्रुव द्विगुण theta = (scale < 0 ? len4 : 0) + 1.0/8.0;
    size_t alloc = pre_tab ? 2*len4 : len4;

    यदि (!(s->घातांकः = av_malloc_array(alloc, परिमाण(*s->घातांकः))))
        प्रत्यागम AVERROR(ENOMEM);

    scale = वर्गमूलम्(fabs(scale));

    यदि (pre_tab)
        off = len4;

    प्रति (पूर्णाङ्क i = 0; i < len4; i++) {
        ध्रुव द्विगुण alpha = M_PI_2 * (i + theta) / len4;
        s->घातांकः[off + i] = (TXComplex){ RESCALE(कोटिज्या(alpha) * scale),
                                       RESCALE(ज्या(alpha) * scale) };
    }

    यदि (pre_tab)
        प्रति (पूर्णाङ्क i = 0; i < len4; i++)
            s->घातांकः[i] = s->घातांकः[len4 + pre_tab[i]];

    प्रत्यागम 0;
}

ध्रुव FFTXCodelet * ध्रुव TX_NAME(ff_tx_codelet_list)[] = {
    /* Split-Radix codelets */
    &TX_NAME(ff_tx_fft2_ns_def),
    &TX_NAME(ff_tx_fft4_ns_def),
    &TX_NAME(ff_tx_fft8_ns_def),
    &TX_NAME(ff_tx_fft16_ns_def),
    &TX_NAME(ff_tx_fft32_ns_def),
    &TX_NAME(ff_tx_fft64_ns_def),
    &TX_NAME(ff_tx_fft128_ns_def),
    &TX_NAME(ff_tx_fft256_ns_def),
    &TX_NAME(ff_tx_fft512_ns_def),
    &TX_NAME(ff_tx_fft1024_ns_def),
    &TX_NAME(ff_tx_fft2048_ns_def),
    &TX_NAME(ff_tx_fft4096_ns_def),
    &TX_NAME(ff_tx_fft8192_ns_def),
    &TX_NAME(ff_tx_fft16384_ns_def),
    &TX_NAME(ff_tx_fft32768_ns_def),
    &TX_NAME(ff_tx_fft65536_ns_def),
    &TX_NAME(ff_tx_fft131072_ns_def),

    /* Prime factor codelets */
    &TX_NAME(ff_tx_fft3_ns_def),
    &TX_NAME(ff_tx_fft5_ns_def),
    &TX_NAME(ff_tx_fft7_ns_def),
    &TX_NAME(ff_tx_fft9_ns_def),
    &TX_NAME(ff_tx_fft15_ns_def),

    /* We get these for free */
    &TX_NAME(ff_tx_fft3_fwd_def),
    &TX_NAME(ff_tx_fft5_fwd_def),
    &TX_NAME(ff_tx_fft7_fwd_def),
    &TX_NAME(ff_tx_fft9_fwd_def),

    /* Standalone transforms */
    &TX_NAME(ff_tx_fft_def),
    &TX_NAME(ff_tx_fft_inplace_def),
    &TX_NAME(ff_tx_fft_inplace_small_def),
    &TX_NAME(ff_tx_fft_pfa_def),
    &TX_NAME(ff_tx_fft_pfa_ns_def),
    &TX_NAME(ff_tx_fft_naive_def),
    &TX_NAME(ff_tx_fft_naive_small_def),
    &TX_NAME(ff_tx_mdct_fwd_def),
    &TX_NAME(ff_tx_mdct_inv_def),
    &TX_NAME(ff_tx_mdct_pfa_3xM_fwd_def),
    &TX_NAME(ff_tx_mdct_pfa_5xM_fwd_def),
    &TX_NAME(ff_tx_mdct_pfa_7xM_fwd_def),
    &TX_NAME(ff_tx_mdct_pfa_9xM_fwd_def),
    &TX_NAME(ff_tx_mdct_pfa_15xM_fwd_def),
    &TX_NAME(ff_tx_mdct_pfa_3xM_inv_def),
    &TX_NAME(ff_tx_mdct_pfa_5xM_inv_def),
    &TX_NAME(ff_tx_mdct_pfa_7xM_inv_def),
    &TX_NAME(ff_tx_mdct_pfa_9xM_inv_def),
    &TX_NAME(ff_tx_mdct_pfa_15xM_inv_def),
    &TX_NAME(ff_tx_mdct_naive_fwd_def),
    &TX_NAME(ff_tx_mdct_naive_inv_def),
    &TX_NAME(ff_tx_mdct_inv_पूर्णम्_def),
    &TX_NAME(ff_tx_rdft_r2c_def),
    &TX_NAME(ff_tx_rdft_r2r_def),
    &TX_NAME(ff_tx_rdft_r2r_mod2_def),
    &TX_NAME(ff_tx_rdft_r2i_def),
    &TX_NAME(ff_tx_rdft_r2i_mod2_def),
    &TX_NAME(ff_tx_rdft_c2r_def),
    &TX_NAME(ff_tx_dctII_def),
    &TX_NAME(ff_tx_dctIII_def),
    &TX_NAME(ff_tx_dctI_def),
    &TX_NAME(ff_tx_dstI_def),

    रिक्त,
};
