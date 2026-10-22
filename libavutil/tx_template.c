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

#ضمن "mem.h"

#define TABLE_DEF(name, size) \
    DECLARE_ALIGNED(32, TXSample, TX_TAB(ff_tx_tab_ ##name))[size]

#define SR_POW2_TABLES \
    SR_TABLE(8)        \
    SR_TABLE(16)       \
    SR_TABLE(32)       \
    SR_TABLE(64)       \
    SR_TABLE(128)      \
    SR_TABLE(256)      \
    SR_TABLE(512)      \
    SR_TABLE(1024)     \
    SR_TABLE(2048)     \
    SR_TABLE(4096)     \
    SR_TABLE(8192)     \
    SR_TABLE(16384)    \
    SR_TABLE(32768)    \
    SR_TABLE(65536)    \
    SR_TABLE(131072)   \

#define SR_TABLE(len) \
    TABLE_DEF(len, len/4 + 1);
/* Power of two tables */
SR_POW2_TABLES
#undef SR_TABLE

/* Other factors' tables */
TABLE_DEF(53, 12);
TABLE_DEF( 7,  6);
TABLE_DEF( 9,  8);

تعريفنوع بنية FFTabInitData {
    فراغ (*func)(فراغ);
    صحيح factors[TX_MAX_SUB]; /* Must be sorted high -> low */
} FFTabInitData;

#define SR_TABLE(len)                                              \
ساكن av_cold فراغ TX_TAB(ff_tx_init_tab_ ##len)(فراغ)            \
{                                                                  \
    مزدوج freq = 2*M_PI/len;                                      \
    TXSample *tab = TX_TAB(ff_tx_tab_ ##len);                      \
                                                                   \
    لكل (صحيح i = 0; i < len/4; i++)                                \
        *tab++ = RESCALE(cos(i*freq));                             \
                                                                   \
    *tab = 0;                                                      \
}
SR_POW2_TABLES
#undef SR_TABLE

ساكن فراغ (*ثابت sr_tabs_init_funcs[])(فراغ) = {
#define SR_TABLE(len) TX_TAB(ff_tx_init_tab_ ##len),
    SR_POW2_TABLES
#undef SR_TABLE
};

ساكن AVOnce sr_tabs_init_once[] = {
#define SR_TABLE(len) AV_ONCE_INIT,
    SR_POW2_TABLES
#undef SR_TABLE
};

ساكن av_cold فراغ TX_TAB(ff_tx_init_tab_53)(فراغ)
{
    /* 5pt, doubled to eliminate AVX lane shuffles */
    TX_TAB(ff_tx_tab_53)[0] = RESCALE(cos(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[1] = RESCALE(cos(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[2] = RESCALE(cos(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[3] = RESCALE(cos(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[4] = RESCALE(sin(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[5] = RESCALE(sin(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[6] = RESCALE(sin(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[7] = RESCALE(sin(2 * M_PI / 10));

    /* 3pt */
    TX_TAB(ff_tx_tab_53)[ 8] = RESCALE(cos(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[ 9] = RESCALE(cos(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[10] = RESCALE(cos(2 * M_PI /  6));
    TX_TAB(ff_tx_tab_53)[11] = RESCALE(cos(8 * M_PI /  6));
}

ساكن av_cold فراغ TX_TAB(ff_tx_init_tab_7)(فراغ)
{
    TX_TAB(ff_tx_tab_7)[0] = RESCALE(cos(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[1] = RESCALE(sin(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[2] = RESCALE(sin(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[3] = RESCALE(cos(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[4] = RESCALE(cos(2 * M_PI / 14));
    TX_TAB(ff_tx_tab_7)[5] = RESCALE(sin(2 * M_PI / 14));
}

ساكن av_cold فراغ TX_TAB(ff_tx_init_tab_9)(فراغ)
{
    TX_TAB(ff_tx_tab_9)[0] = RESCALE(cos(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[1] = RESCALE(sin(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[2] = RESCALE(cos(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[3] = RESCALE(sin(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[4] = RESCALE(cos(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[5] = RESCALE(sin(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[6] = TX_TAB(ff_tx_tab_9)[2] + TX_TAB(ff_tx_tab_9)[5];
    TX_TAB(ff_tx_tab_9)[7] = TX_TAB(ff_tx_tab_9)[3] - TX_TAB(ff_tx_tab_9)[4];
}

ساكن ثابت FFTabInitData nptwo_tabs_init_data[] = {
    { TX_TAB(ff_tx_init_tab_53),      { 15, 5, 3 } },
    { TX_TAB(ff_tx_init_tab_9),       {  9 }       },
    { TX_TAB(ff_tx_init_tab_7),       {  7 }       },
};

ساكن AVOnce nptwo_tabs_init_once[] = {
    AV_ONCE_INIT,
    AV_ONCE_INIT,
    AV_ONCE_INIT,
};

av_cold فراغ TX_TAB(ff_tx_init_tabs)(صحيح len)
{
    صحيح factor_2 = ff_ctz(len);
    𐡄𐡍 (factor_2) {
        صحيح idx = factor_2 - 3;
        لكل (صحيح i = 0; i <= idx; i++)
            ff_thread_once(&sr_tabs_init_once[i],
                            sr_tabs_init_funcs[i]);
        len >>= factor_2;
    }

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(nptwo_tabs_init_data); i++) {
        صحيح f, f_idx = 0;

        𐡄𐡍 (len <= 1)
            أرجع;

        طالما ((f = nptwo_tabs_init_data[i].factors[f_idx++])) {
            𐡄𐡍 (f % len)
                استمر;

            ff_thread_once(&nptwo_tabs_init_once[i],
                            nptwo_tabs_init_data[i].func);
            len /= f;
            اكسر;
        }
    }
}

ساكن av_always_inline فراغ fft3(TXComplex *out, TXComplex *in,
                                  ptrdiff_t stride)
{
    TXComplex tmp[3];
    ثابت TXSample *tab = TX_TAB(ff_tx_tab_53);
#ifdef TX_INT32
    int64_t mtmp[4];
#endif

    tmp[0] = in[0];
    BF(tmp[1].re, tmp[2].im, in[1].im, in[2].im);
    BF(tmp[1].im, tmp[2].re, in[1].re, in[2].re);

#ifdef TX_INT32
    out[0*stride].re = (int64_t)tmp[0].re + tmp[2].re;
    out[0*stride].im = (int64_t)tmp[0].im + tmp[2].im;
    mtmp[0] = (int64_t)tab[ 8] * tmp[1].re;
    mtmp[1] = (int64_t)tab[ 9] * tmp[1].im;
    mtmp[2] = (int64_t)tab[10] * tmp[2].re;
    mtmp[3] = (int64_t)tab[10] * tmp[2].im;
    out[1*stride].re = tmp[0].re - (mtmp[2] + mtmp[0] + 0x40000000 >> 31);
    out[1*stride].im = tmp[0].im - (mtmp[3] - mtmp[1] + 0x40000000 >> 31);
    out[2*stride].re = tmp[0].re - (mtmp[2] - mtmp[0] + 0x40000000 >> 31);
    out[2*stride].im = tmp[0].im - (mtmp[3] + mtmp[1] + 0x40000000 >> 31);
#وإلا
    out[0*stride].re = tmp[0].re + tmp[2].re;
    out[0*stride].im = tmp[0].im + tmp[2].im;
    tmp[1].re = tab[ 8] * tmp[1].re;
    tmp[1].im = tab[ 9] * tmp[1].im;
    tmp[2].re = tab[10] * tmp[2].re;
    tmp[2].im = tab[10] * tmp[2].im;
    out[1*stride].re = tmp[0].re - tmp[2].re + tmp[1].re;
    out[1*stride].im = tmp[0].im - tmp[2].im - tmp[1].im;
    out[2*stride].re = tmp[0].re - tmp[2].re - tmp[1].re;
    out[2*stride].im = tmp[0].im - tmp[2].im + tmp[1].im;
#endif
}

#define DECL_FFT5(NAME, D0, D1, D2, D3, D4)                         \
ساكن av_always_inline فراغ NAME(TXComplex *out, TXComplex *in,    \
                                  ptrdiff_t stride)                 \
{                                                                   \
    TXComplex dc, z0[4], t[6];                                      \
    ثابت TXSample *tab = TX_TAB(ff_tx_tab_53);                     \
                                                                    \
    dc = in[0];                                                     \
    BF(t[1].im, t[0].re, in[1].re, in[4].re);                       \
    BF(t[1].re, t[0].im, in[1].im, in[4].im);                       \
    BF(t[3].im, t[2].re, in[2].re, in[3].re);                       \
    BF(t[3].re, t[2].im, in[2].im, in[3].im);                       \
                                                                    \
    out[D0*stride].re = dc.re + (TXUSample)t[0].re + t[2].re;        \
    out[D0*stride].im = dc.im + (TXUSample)t[0].im + t[2].im;        \
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
    out[D1*stride].re = dc.re + (TXUSample)z0[3].re;                 \
    out[D1*stride].im = dc.im + (TXUSample)z0[0].im;                 \
    out[D2*stride].re = dc.re + (TXUSample)z0[2].re;                 \
    out[D2*stride].im = dc.im + (TXUSample)z0[1].im;                 \
    out[D3*stride].re = dc.re + (TXUSample)z0[1].re;                 \
    out[D3*stride].im = dc.im + (TXUSample)z0[2].im;                 \
    out[D4*stride].re = dc.re + (TXUSample)z0[0].re;                 \
    out[D4*stride].im = dc.im + (TXUSample)z0[3].im;                 \
}

DECL_FFT5(fft5,     0,  1,  2,  3,  4)
DECL_FFT5(fft5_m1,  0,  6, 12,  3,  9)
DECL_FFT5(fft5_m2, 10,  1,  7, 13,  4)
DECL_FFT5(fft5_m3,  5, 11,  2,  8, 14)

ساكن av_always_inline فراغ fft7(TXComplex *out, TXComplex *in,
                                  ptrdiff_t stride)
{
    TXComplex dc, t[6], z[3];
    ثابت TXComplex *tab = (ثابت TXComplex *)TX_TAB(ff_tx_tab_7);
#ifdef TX_INT32
    int64_t mtmp[12];
#endif

    dc = in[0];
    BF(t[1].re, t[0].re, in[1].re, in[6].re);
    BF(t[1].im, t[0].im, in[1].im, in[6].im);
    BF(t[3].re, t[2].re, in[2].re, in[5].re);
    BF(t[3].im, t[2].im, in[2].im, in[5].im);
    BF(t[5].re, t[4].re, in[3].re, in[4].re);
    BF(t[5].im, t[4].im, in[3].im, in[4].im);

    out[0*stride].re = dc.re + t[0].re + t[2].re + t[4].re;
    out[0*stride].im = dc.im + t[0].im + t[2].im + t[4].im;

#ifdef TX_INT32 /* NOTE: it's possible to do this with 16 mults but 72 adds */
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
#وإلا
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
#endif

    BF(t[1].re, z[0].re, z[0].re, t[4].re);
    BF(t[3].re, z[1].re, z[1].re, t[2].re);
    BF(t[5].re, z[2].re, z[2].re, t[0].re);
    BF(t[1].im, z[0].im, z[0].im, t[0].im);
    BF(t[3].im, z[1].im, z[1].im, t[2].im);
    BF(t[5].im, z[2].im, z[2].im, t[4].im);

    out[1*stride].re = dc.re + z[0].re;
    out[1*stride].im = dc.im + t[1].im;
    out[2*stride].re = dc.re + t[3].re;
    out[2*stride].im = dc.im + z[1].im;
    out[3*stride].re = dc.re + z[2].re;
    out[3*stride].im = dc.im + t[5].im;
    out[4*stride].re = dc.re + t[5].re;
    out[4*stride].im = dc.im + z[2].im;
    out[5*stride].re = dc.re + z[1].re;
    out[5*stride].im = dc.im + t[3].im;
    out[6*stride].re = dc.re + t[1].re;
    out[6*stride].im = dc.im + z[0].im;
}

ساكن av_always_inline فراغ fft9(TXComplex *out, TXComplex *in,
                                  ptrdiff_t stride)
{
    ثابت TXComplex *tab = (ثابت TXComplex *)TX_TAB(ff_tx_tab_9);
    TXComplex dc, t[16], w[4], x[5], y[5], z[2];
#ifdef TX_INT32
    int64_t mtmp[12];
#endif

    dc = in[0];
    BF(t[1].re, t[0].re, in[1].re, in[8].re);
    BF(t[1].im, t[0].im, in[1].im, in[8].im);
    BF(t[3].re, t[2].re, in[2].re, in[7].re);
    BF(t[3].im, t[2].im, in[2].im, in[7].im);
    BF(t[5].re, t[4].re, in[3].re, in[6].re);
    BF(t[5].im, t[4].im, in[3].im, in[6].im);
    BF(t[7].re, t[6].re, in[4].re, in[5].re);
    BF(t[7].im, t[6].im, in[4].im, in[5].im);

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

    out[0*stride].re = z[0].re + z[1].re;
    out[0*stride].im = z[0].im + z[1].im;

#ifdef TX_INT32
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
    z[0].re = in[0].re + (int32_t)mtmp[2];
    z[0].im = in[0].im + (int32_t)mtmp[3];

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

#وإلا
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
#endif

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

    out[1*stride] = (TXComplex){ x[1].re + y[1].im, x[1].im - y[1].re };
    out[2*stride] = (TXComplex){ x[2].re + y[2].im, x[2].im - y[2].re };
    out[3*stride] = (TXComplex){ x[3].re + y[3].im, x[3].im - y[3].re };
    out[4*stride] = (TXComplex){ x[4].re + y[4].im, x[4].im - y[4].re };
    out[5*stride] = (TXComplex){ x[4].re - y[4].im, x[4].im + y[4].re };
    out[6*stride] = (TXComplex){ x[3].re - y[3].im, x[3].im + y[3].re };
    out[7*stride] = (TXComplex){ x[2].re - y[2].im, x[2].im + y[2].re };
    out[8*stride] = (TXComplex){ x[1].re - y[1].im, x[1].im + y[1].re };
}

ساكن av_always_inline فراغ fft15(TXComplex *out, TXComplex *in,
                                   ptrdiff_t stride)
{
    TXComplex tmp[15];

    لكل (صحيح i = 0; i < 5; i++)
        fft3(tmp + i, in + i*3, 5);

    fft5_m1(out, tmp +  0, stride);
    fft5_m2(out, tmp +  5, stride);
    fft5_m3(out, tmp + 10, stride);
}

ساكن av_cold صحيح TX_NAME(ff_tx_fft_factor_init)(AVTXContext *s,
                                                  ثابت FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  صحيح len, صحيح inv,
                                                  ثابت فراغ *scale)
{
    صحيح ret = 0;
    TX_TAB(ff_tx_init_tabs)(len);

    𐡄𐡍 (len == 15)
        ret = ff_tx_gen_pfa_input_map(s, opts, 3, 5);
    وإلا 𐡄𐡍 (flags & FF_TX_PRESHUFFLE)
        ret = ff_tx_gen_default_map(s, opts);

    أرجع ret;
}

#define DECL_FACTOR_S(n)                                                       \
ساكن فراغ TX_NAME(ff_tx_fft##n)(AVTXContext *s, فراغ *dst,                   \
                                  فراغ *src, ptrdiff_t stride)                 \
{                                                                              \
    fft##n((TXComplex *)dst, (TXComplex *)src, stride / حجم(TXComplex));    \
}                                                                              \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = {                    \
    .name       = TX_NAME_STR("fft" #n "_ns"),                                 \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_OUT_OF_PLACE |                         \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,                          \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_factor_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

#define DECL_FACTOR_F(n)                                                       \
DECL_FACTOR_S(n)                                                               \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft##n##_fwd_def) = {                   \
    .name       = TX_NAME_STR("fft" #n "_fwd"),                                \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_OUT_OF_PLACE |                         \
                  AV_TX_UNALIGNED | FF_TX_FORWARD_ONLY,                        \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_factor_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

DECL_FACTOR_F(3)
DECL_FACTOR_F(5)
DECL_FACTOR_F(7)
DECL_FACTOR_F(9)
DECL_FACTOR_S(15)

#define BUTTERFLIES(a0, a1, a2, a3)            \
    𐡏𐡁𐡃 {                                       \
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
    } طالما (0)

#define TRANSFORM(a0, a1, a2, a3, wre, wim)    \
    𐡏𐡁𐡃 {                                       \
        CMUL(t1, t2, a2.re, a2.im, wre, -wim); \
        CMUL(t5, t6, a3.re, a3.im, wre,  wim); \
        BUTTERFLIES(a0, a1, a2, a3);           \
    } طالما (0)

/* z[0...8n-1], w[1...2n-1] */
ساكن مضمن فراغ TX_NAME(ff_tx_fft_sr_combine)(TXComplex *z,
                                                 ثابت TXSample *cos, صحيح len)
{
    صحيح o1 = 2*len;
    صحيح o2 = 4*len;
    صحيح o3 = 6*len;
    ثابت TXSample *wim = cos + o1 - 7;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;

    لكل (صحيح i = 0; i < len; i += 4) {
        TRANSFORM(z[0], z[o1 + 0], z[o2 + 0], z[o3 + 0], cos[0], wim[7]);
        TRANSFORM(z[2], z[o1 + 2], z[o2 + 2], z[o3 + 2], cos[2], wim[5]);
        TRANSFORM(z[4], z[o1 + 4], z[o2 + 4], z[o3 + 4], cos[4], wim[3]);
        TRANSFORM(z[6], z[o1 + 6], z[o2 + 6], z[o3 + 6], cos[6], wim[1]);

        TRANSFORM(z[1], z[o1 + 1], z[o2 + 1], z[o3 + 1], cos[1], wim[6]);
        TRANSFORM(z[3], z[o1 + 3], z[o2 + 3], z[o3 + 3], cos[3], wim[4]);
        TRANSFORM(z[5], z[o1 + 5], z[o2 + 5], z[o3 + 5], cos[5], wim[2]);
        TRANSFORM(z[7], z[o1 + 7], z[o2 + 7], z[o3 + 7], cos[7], wim[0]);

        z   += 2*4;
        cos += 2*4;
        wim -= 2*4;
    }
}

ساكن av_cold صحيح TX_NAME(ff_tx_fft_sr_codelet_init)(AVTXContext *s,
                                                      ثابت FFTXCodelet *cd,
                                                      uint64_t flags,
                                                      FFTXCodeletOptions *opts,
                                                      صحيح len, صحيح inv,
                                                      ثابت فراغ *scale)
{
    TX_TAB(ff_tx_init_tabs)(len);
    أرجع ff_tx_gen_ptwo_revtab(s, opts);
}

#define DECL_SR_CODELET_DEF(n)                              \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = { \
    .name       = TX_NAME_STR("fft" #n "_ns"),              \
    .function   = TX_NAME(ff_tx_fft##n##_ns),               \
    .type       = TX_TYPE(FFT),                             \
    .flags      = FF_TX_OUT_OF_PLACE | AV_TX_INPLACE |      \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,       \
    .factors[0] = 2,                                        \
    .nb_factors = 1,                                        \
    .min_len    = n,                                        \
    .max_len    = n,                                        \
    .init       = TX_NAME(ff_tx_fft_sr_codelet_init),       \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                      \
    .prio       = FF_TX_PRIO_BASE,                          \
};

#define DECL_SR_CODELET(n, n2, n4)                                    \
ساكن فراغ TX_NAME(ff_tx_fft##n##_ns)(AVTXContext *s, فراغ *_dst,    \
                                        فراغ *_src, ptrdiff_t stride) \
{                                                                     \
    TXComplex *src = _src;                                            \
    TXComplex *dst = _dst;                                            \
    ثابت TXSample *cos = TX_TAB(ff_tx_tab_##n);                      \
                                                                      \
    TX_NAME(ff_tx_fft##n2##_ns)(s, dst,        src,        stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*2, src + n4*2, stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*3, src + n4*3, stride);   \
    TX_NAME(ff_tx_fft_sr_combine)(dst, cos, n4 >> 1);                 \
}                                                                     \
                                                                      \
DECL_SR_CODELET_DEF(n)

ساكن فراغ TX_NAME(ff_tx_fft2_ns)(AVTXContext *s, فراغ *_dst,
                                   فراغ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;

    BF(tmp.re, dst[0].re, src[0].re, src[1].re);
    BF(tmp.im, dst[0].im, src[0].im, src[1].im);
    dst[1] = tmp;
}

ساكن فراغ TX_NAME(ff_tx_fft4_ns)(AVTXContext *s, فراغ *_dst,
                                   فراغ *_src, ptrdiff_t stride)
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

ساكن فراغ TX_NAME(ff_tx_fft8_ns)(AVTXContext *s, فراغ *_dst,
                                   فراغ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    ثابت TXSample cos = TX_TAB(ff_tx_tab_8)[1];

    TX_NAME(ff_tx_fft4_ns)(s, dst, src, stride);

    BF(t1, dst[5].re, src[4].re, -src[5].re);
    BF(t2, dst[5].im, src[4].im, -src[5].im);
    BF(t5, dst[7].re, src[6].re, -src[7].re);
    BF(t6, dst[7].im, src[6].im, -src[7].im);

    BUTTERFLIES(dst[0], dst[2], dst[4], dst[6]);
    TRANSFORM(dst[1], dst[3], dst[5], dst[7], cos, cos);
}

ساكن فراغ TX_NAME(ff_tx_fft16_ns)(AVTXContext *s, فراغ *_dst,
                                    فراغ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ثابت TXSample *cos = TX_TAB(ff_tx_tab_16);

    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    TXSample cos_16_1 = cos[1];
    TXSample cos_16_2 = cos[2];
    TXSample cos_16_3 = cos[3];

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

ساكن av_cold صحيح TX_NAME(ff_tx_fft_init)(AVTXContext *s,
                                           ثابت FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           صحيح len, صحيح inv,
                                           ثابت فراغ *scale)
{
    صحيح ret;
    صحيح is_inplace = !!(flags & AV_TX_INPLACE);
    FFTXCodeletOptions sub_opts = {
        .map_dir = is_inplace ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    flags &= ~FF_TX_OUT_OF_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len, inv, scale)))
        أرجع ret;

    𐡄𐡍 (is_inplace && (ret = ff_tx_gen_inplace_map(s, len)))
        أرجع ret;

    أرجع 0;
}

ساكن av_cold صحيح TX_NAME(ff_tx_fft_inplace_small_init)(AVTXContext *s,
                                                         ثابت FFTXCodelet *cd,
                                                         uint64_t flags,
                                                         FFTXCodeletOptions *opts,
                                                         صحيح len, صحيح inv,
                                                         ثابت فراغ *scale)
{
    𐡄𐡍 (!(s->tmp = av_malloc(len*حجم(*s->tmp))))
        أرجع AVERROR(ENOMEM);
    flags &= ~AV_TX_INPLACE;
    أرجع TX_NAME(ff_tx_fft_init)(s, cd, flags, opts, len, inv, scale);
}

ساكن فراغ TX_NAME(ff_tx_fft)(AVTXContext *s, فراغ *_dst,
                               فراغ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst1 = s->flags & AV_TX_INPLACE ? s->tmp : _dst;
    TXComplex *dst2 = _dst;
    صحيح *map = s->sub[0].map;
    صحيح len = s->len;

    /* Compilers can't vectorize this anyway without assuming AVX2, which they
     * generally don't, at least without -march=native -mtune=native */
    لكل (صحيح i = 0; i < len; i++)
        dst1[i] = src[map[i]];

    s->fn[0](&s->sub[0], dst2, dst1, stride);
}

ساكن فراغ TX_NAME(ff_tx_fft_inplace)(AVTXContext *s, فراغ *_dst,
                                       فراغ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;
    ثابت صحيح *map = s->sub->map;
    ثابت صحيح *inplace_idx = s->map;
    صحيح src_idx, dst_idx;

    src_idx = *inplace_idx++;
    𐡏𐡁𐡃 {
        tmp = src[src_idx];
        dst_idx = map[src_idx];
        𐡏𐡁𐡃 {
            FFSWAP(TXComplex, tmp, src[dst_idx]);
            dst_idx = map[dst_idx];
        } طالما (dst_idx != src_idx); /* Can be > as well, but was less predictable */
        src[dst_idx] = tmp;
    } طالما ((src_idx = *inplace_idx++));

    s->fn[0](&s->sub[0], dst, src, stride);
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_def) = {
    .name       = TX_NAME_STR("fft"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE,
    .factors[0] = TX_FACTOR_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_inplace_small_def) = {
    .name       = TX_NAME_STR("fft_inplace_small"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | AV_TX_INPLACE,
    .factors[0] = TX_FACTOR_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 65536,
    .init       = TX_NAME(ff_tx_fft_inplace_small_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE - 256,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_inplace_def) = {
    .name       = TX_NAME_STR("fft_inplace"),
    .function   = TX_NAME(ff_tx_fft_inplace),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | AV_TX_INPLACE,
    .factors[0] = TX_FACTOR_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE - 512,
};

ساكن av_cold صحيح TX_NAME(ff_tx_fft_init_naive_small)(AVTXContext *s,
                                                       ثابت FFTXCodelet *cd,
                                                       uint64_t flags,
                                                       FFTXCodeletOptions *opts,
                                                       صحيح len, صحيح inv,
                                                       ثابت فراغ *scale)
{
    ثابت مزدوج phase = s->inv ? 2.0*M_PI/len : -2.0*M_PI/len;

    𐡄𐡍 (!(s->exp = av_malloc(len*len*حجم(*s->exp))))
        أرجع AVERROR(ENOMEM);

    لكل (صحيح i = 0; i < len; i++) {
        لكل (صحيح j = 0; j < len; j++) {
            ثابت مزدوج factor = phase*i*j;
            s->exp[i*j] = (TXComplex){
                RESCALE(cos(factor)),
                RESCALE(sin(factor)),
            };
        }
    }

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_fft_naive)(AVTXContext *s, فراغ *_dst, فراغ *_src,
                                     ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ثابت صحيح n = s->len;
    مزدوج phase = s->inv ? 2.0*M_PI/n : -2.0*M_PI/n;

    stride /= حجم(*dst);

    لكل (صحيح i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        لكل (صحيح j = 0; j < n; j++) {
            ثابت مزدوج factor = phase*i*j;
            ثابت TXComplex mult = {
                RESCALE(cos(factor)),
                RESCALE(sin(factor)),
            };
            TXComplex res;
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ساكن فراغ TX_NAME(ff_tx_fft_naive_small)(AVTXContext *s, فراغ *_dst, فراغ *_src,
                                           ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ثابت صحيح n = s->len;

    stride /= حجم(*dst);

    لكل (صحيح i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        لكل (صحيح j = 0; j < n; j++) {
            TXComplex res;
            ثابت TXComplex mult = s->exp[i*j];
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_naive_small_def) = {
    .name       = TX_NAME_STR("fft_naive_small"),
    .function   = TX_NAME(ff_tx_fft_naive_small),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE,
    .factors[0] = TX_FACTOR_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 1024,
    .init       = TX_NAME(ff_tx_fft_init_naive_small),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN/2,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_naive_def) = {
    .name       = TX_NAME_STR("fft_naive"),
    .function   = TX_NAME(ff_tx_fft_naive),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE,
    .factors[0] = TX_FACTOR_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = عدم,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ساكن av_cold صحيح TX_NAME(ff_tx_fft_pfa_init)(AVTXContext *s,
                                               ثابت FFTXCodelet *cd,
                                               uint64_t flags,
                                               FFTXCodeletOptions *opts,
                                               صحيح len, صحيح inv,
                                               ثابت فراغ *scale)
{
    صحيح ret, *tmp, ps = flags & FF_TX_PRESHUFFLE;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };
    size_t extra_tmp_len = 0;
    صحيح len_list[TX_MAX_DECOMPOSITIONS];

    𐡄𐡍 ((ret = ff_tx_decompose_length(len_list, TX_TYPE(FFT), len, inv)) < 0)
        أرجع ret;

    /* Two iterations to test both orderings. */
    لكل (صحيح i = 0; i < ret; i++) {
        صحيح len1 = len_list[i];
        صحيح len2 = len / len1;

        /* Our ptwo transforms don't support striding the output. */
        𐡄𐡍 (len2 & (len2 - 1))
            FFSWAP(صحيح, len1, len2);

        ff_tx_clear_ctx(s);

        /* First transform */
        sub_opts.map_dir = FF_TX_MAP_GATHER;
        flags &= ~AV_TX_INPLACE;
        flags |=  FF_TX_OUT_OF_PLACE;
        flags |=  FF_TX_PRESHUFFLE; /* This function handles the permute step */
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len1, inv, scale);

        𐡄𐡍 (ret == AVERROR(ENOMEM)) {
            أرجع ret;
        } وإلا 𐡄𐡍 (ret < 0) { /* Try again without a preshuffle flag */
            flags &= ~FF_TX_PRESHUFFLE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len1, inv, scale);
            𐡄𐡍 (ret == AVERROR(ENOMEM))
                أرجع ret;
            وإلا 𐡄𐡍 (ret < 0)
                استمر;
        }

        /* Second transform. */
        sub_opts.map_dir = FF_TX_MAP_SCATTER;
        flags |=  FF_TX_PRESHUFFLE;
retry:
        flags &= ~FF_TX_OUT_OF_PLACE;
        flags |=  AV_TX_INPLACE;
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len2, inv, scale);

        𐡄𐡍 (ret == AVERROR(ENOMEM)) {
            أرجع ret;
        } وإلا 𐡄𐡍 (ret < 0) { /* Try again with an out-of-place transform */
            flags |= FF_TX_OUT_OF_PLACE;
            flags &= ~AV_TX_INPLACE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len2, inv, scale);
            𐡄𐡍 (ret == AVERROR(ENOMEM)) {
                أرجع ret;
            } وإلا 𐡄𐡍 (ret < 0) {
                𐡄𐡍 (flags & FF_TX_PRESHUFFLE) { /* Retry again without a preshuf flag */
                    flags &= ~FF_TX_PRESHUFFLE;
                    اذهب retry;
                } وإلا {
                    استمر;
                }
            }
        }

        /* Success */
        اكسر;
    }

    /* If nothing was successful, error out */
    𐡄𐡍 (ret < 0)
        أرجع ret;

    /* Generate PFA map */
    𐡄𐡍 ((ret = ff_tx_gen_compound_mapping(s, opts, 0,
                                          s->sub[0].len, s->sub[1].len)))
        أرجع ret;

    𐡄𐡍 (!(s->tmp = av_malloc(len*حجم(*s->tmp))))
        أرجع AVERROR(ENOMEM);

    /* Flatten input map */
    tmp = (صحيح *)s->tmp;
    لكل (صحيح k = 0; k < len; k += s->sub[0].len) {
        memcpy(tmp, &s->map[k], s->sub[0].len*حجم(*tmp));
        لكل (صحيح i = 0; i < s->sub[0].len; i++)
            s->map[k + i] = tmp[s->sub[0].map[i]];
    }

    /* Only allocate extra temporary memory if we need it */
    𐡄𐡍 (!(s->sub[1].flags & AV_TX_INPLACE))
        extra_tmp_len = len;
    وإلا 𐡄𐡍 (!ps)
        extra_tmp_len = s->sub[0].len;

    𐡄𐡍 (extra_tmp_len && !(s->exp = av_malloc(extra_tmp_len*حجم(*s->exp))))
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_fft_pfa)(AVTXContext *s, فراغ *_out,
                                   فراغ *_in, ptrdiff_t stride)
{
    ثابت صحيح n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ثابت صحيح *in_map = s->map, *out_map = in_map + l;
    ثابت صحيح *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->exp;
    TXComplex *in = _in, *out = _out;

    stride /= حجم(*out);

    لكل (صحيح i = 0; i < m; i++) {
        لكل (صحيح j = 0; j < n; j++)
            s->exp[j] = in[in_map[i*n + j]];
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], s->exp, m*حجم(TXComplex));
    }

    لكل (صحيح i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], حجم(TXComplex));

    لكل (صحيح i = 0; i < l; i++)
        out[i*stride] = tmp1[out_map[i]];
}

ساكن فراغ TX_NAME(ff_tx_fft_pfa_ns)(AVTXContext *s, فراغ *_out,
                                      فراغ *_in, ptrdiff_t stride)
{
    ثابت صحيح n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ثابت صحيح *in_map = s->map, *out_map = in_map + l;
    ثابت صحيح *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->exp;
    TXComplex *in = _in, *out = _out;

    stride /= حجم(*out);

    لكل (صحيح i = 0; i < m; i++)
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], &in[i*n], m*حجم(TXComplex));

    لكل (صحيح i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], حجم(TXComplex));

    لكل (صحيح i = 0; i < l; i++)
        out[i*stride] = tmp1[out_map[i]];
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_pfa_def) = {
    .name       = TX_NAME_STR("fft_pfa"),
    .function   = TX_NAME(ff_tx_fft_pfa),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_OUT_OF_PLACE,
    .factors    = { 7, 5, 3, 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_fft_pfa_ns_def) = {
    .name       = TX_NAME_STR("fft_pfa_ns"),
    .function   = TX_NAME(ff_tx_fft_pfa_ns),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_OUT_OF_PLACE |
                  FF_TX_PRESHUFFLE,
    .factors    = { 7, 5, 3, 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن av_cold صحيح TX_NAME(ff_tx_mdct_naive_init)(AVTXContext *s,
                                                  ثابت FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  صحيح len, صحيح inv,
                                                  ثابت فراغ *scale)
{
    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;
    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_mdct_naive_fwd)(AVTXContext *s, فراغ *_dst,
                                          فراغ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    مزدوج scale = s->scale_d;
    صحيح len = s->len;
    ثابت مزدوج phase = M_PI/(4.0*len);

    stride /= حجم(*dst);

    لكل (صحيح i = 0; i < len; i++) {
        مزدوج sum = 0.0;
        لكل (صحيح j = 0; j < len*2; j++) {
            صحيح a = (2*j + 1 + len) * (2*i + 1);
            sum += UNSCALE(src[j]) * cos(a * phase);
        }
        dst[i*stride] = RESCALE(sum*scale);
    }
}

ساكن فراغ TX_NAME(ff_tx_mdct_naive_inv)(AVTXContext *s, فراغ *_dst,
                                          فراغ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    مزدوج scale = s->scale_d;
    صحيح len = s->len >> 1;
    صحيح len2 = len*2;
    ثابت مزدوج phase = M_PI/(4.0*len2);

    stride /= حجم(*src);

    لكل (صحيح i = 0; i < len; i++) {
        مزدوج sum_d = 0.0;
        مزدوج sum_u = 0.0;
        مزدوج i_d = phase * (4*len  - 2*i - 1);
        مزدوج i_u = phase * (3*len2 + 2*i + 1);
        لكل (صحيح j = 0; j < len2; j++) {
            مزدوج a = (2 * j + 1);
            مزدوج a_d = cos(a * i_d);
            مزدوج a_u = cos(a * i_u);
            مزدوج val = UNSCALE(src[j*stride]);
            sum_d += a_d * val;
            sum_u += a_u * val;
        }
        dst[i +   0] = RESCALE( sum_d*scale);
        dst[i + len] = RESCALE(-sum_u*scale);
    }
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_naive_fwd_def) = {
    .name       = TX_NAME_STR("mdct_naive_fwd"),
    .function   = TX_NAME(ff_tx_mdct_naive_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_FACTOR_ANY }, /* MDCTs need an even length */
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_naive_inv_def) = {
    .name       = TX_NAME_STR("mdct_naive_inv"),
    .function   = TX_NAME(ff_tx_mdct_naive_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ساكن av_cold صحيح TX_NAME(ff_tx_mdct_init)(AVTXContext *s,
                                            ثابت FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            صحيح len, صحيح inv,
                                            ثابت فراغ *scale)
{
    صحيح ret;
    FFTXCodeletOptions sub_opts = {
        .map_dir = !inv ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_OUT_OF_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* First try with an in-place transform */

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale))) {
        flags &= ~FF_TX_PRESHUFFLE; /* Now try with a generic FFT */
        𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                    inv, scale)))
            أرجع ret;
    }

    s->map = av_malloc((len >> 1)*حجم(*s->map));
    𐡄𐡍 (!s->map)
        أرجع AVERROR(ENOMEM);

    /* If we need to preshuffle copy the map from the subcontext */
    𐡄𐡍 (s->sub[0].flags & FF_TX_PRESHUFFLE) {
        memcpy(s->map, s->sub->map, (len >> 1)*حجم(*s->map));
    } وإلا {
        لكل (صحيح i = 0; i < len >> 1; i++)
            s->map[i] = i;
    }

    𐡄𐡍 ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : عدم)))
        أرجع ret;

    /* Saves a multiply in a hot path. */
    𐡄𐡍 (inv)
        لكل (صحيح i = 0; i < (s->len >> 1); i++)
            s->map[i] <<= 1;

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_mdct_fwd)(AVTXContext *s, فراغ *_dst, فراغ *_src,
                                    ptrdiff_t stride)
{
    TXSample *src = _src, *dst = _dst;
    TXComplex *exp = s->exp, tmp, *z = _dst;
    ثابت صحيح len2 = s->len >> 1;
    ثابت صحيح len4 = s->len >> 2;
    ثابت صحيح len3 = len2 * 3;
    ثابت صحيح *sub_map = s->map;

    stride /= حجم(*dst);

    لكل (صحيح i = 0; i < len2; i++) { /* Folding and pre-reindexing */
        ثابت صحيح k = 2*i;
        ثابت صحيح idx = sub_map[i];
        𐡄𐡍 (k < len2) {
            tmp.re = FOLD(-src[ len2 + k],  src[1*len2 - 1 - k]);
            tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);
        } وإلا {
            tmp.re = FOLD(-src[ len2 + k], -src[5*len2 - 1 - k]);
            tmp.im = FOLD( src[-len2 + k], -src[1*len3 - 1 - k]);
        }
        CMUL(z[idx].im, z[idx].re, tmp.re, tmp.im, exp[i].re, exp[i].im);
    }

    s->fn[0](&s->sub[0], z, z, حجم(TXComplex));

    لكل (صحيح i = 0; i < len4; i++) {
        ثابت صحيح i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].re, z[i1].im };
        TXComplex src0 = { z[i0].re, z[i0].im };

        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,
             exp[i0].im, exp[i0].re);
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,
             exp[i1].im, exp[i1].re);
    }
}

ساكن فراغ TX_NAME(ff_tx_mdct_inv)(AVTXContext *s, فراغ *_dst, فراغ *_src,
                                    ptrdiff_t stride)
{
    TXComplex *z = _dst, *exp = s->exp;
    ثابت TXSample *src = _src, *in1, *in2;
    ثابت صحيح len2 = s->len >> 1;
    ثابت صحيح len4 = s->len >> 2;
    ثابت صحيح *sub_map = s->map;

    stride /= حجم(*src);
    in1 = src;
    in2 = src + ((len2*2) - 1) * stride;

    لكل (صحيح i = 0; i < len2; i++) {
        صحيح k = sub_map[i];
        TXComplex tmp = { in2[-k*stride], in1[k*stride] };
        CMUL3(z[i], tmp, exp[i]);
    }

    s->fn[0](&s->sub[0], z, z, حجم(TXComplex));

    exp += len2;
    لكل (صحيح i = 0; i < len4; i++) {
        ثابت صحيح i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].im, z[i1].re };
        TXComplex src0 = { z[i0].im, z[i0].re };

        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, exp[i1].im, exp[i1].re);
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, exp[i0].im, exp[i0].re);
    }
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_fwd_def) = {
    .name       = TX_NAME_STR("mdct_fwd"),
    .function   = TX_NAME(ff_tx_mdct_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_inv_def) = {
    .name       = TX_NAME_STR("mdct_inv"),
    .function   = TX_NAME(ff_tx_mdct_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن av_cold صحيح TX_NAME(ff_tx_mdct_inv_full_init)(AVTXContext *s,
                                                     ثابت FFTXCodelet *cd,
                                                     uint64_t flags,
                                                     FFTXCodeletOptions *opts,
                                                     صحيح len, صحيح inv,
                                                     ثابت فراغ *scale)
{
    صحيح ret;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~AV_TX_FULL_IMDCT;

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(MDCT), flags, عدم, len, 1, scale)))
        أرجع ret;

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_mdct_inv_full)(AVTXContext *s, فراغ *_dst,
                                         فراغ *_src, ptrdiff_t stride)
{
    صحيح len  = s->len << 1;
    صحيح len2 = len >> 1;
    صحيح len4 = len >> 2;
    TXSample *dst = _dst;

    s->fn[0](&s->sub[0], dst + len4, _src, stride);

    stride /= حجم(*dst);

    لكل (صحيح i = 0; i < len4; i++) {
        dst[            i*stride] = -dst[(len2 - i - 1)*stride];
        dst[(len - i - 1)*stride] =  dst[(len2 + i + 0)*stride];
    }
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_inv_full_def) = {
    .name       = TX_NAME_STR("mdct_inv_full"),
    .function   = TX_NAME(ff_tx_mdct_inv_full),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_OUT_OF_PLACE | AV_TX_FULL_IMDCT,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_inv_full_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن av_cold صحيح TX_NAME(ff_tx_mdct_pfa_init)(AVTXContext *s,
                                                ثابت FFTXCodelet *cd,
                                                uint64_t flags,
                                                FFTXCodeletOptions *opts,
                                                صحيح len, صحيح inv,
                                                ثابت فراغ *scale)
{
    صحيح ret, sub_len;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    len >>= 1;
    sub_len = len / cd->factors[0];

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_OUT_OF_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        أرجع ret;

    𐡄𐡍 ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        أرجع ret;

    /* Our 15-point transform is also a compound one, so embed its input map */
    𐡄𐡍 (cd->factors[0] == 15)
        TX_EMBED_INPUT_PFA_MAP(s->map, len, 3, 5);

    𐡄𐡍 ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : عدم)))
        أرجع ret;

    /* Saves multiplies in loops. */
    لكل (صحيح i = 0; i < len; i++)
        s->map[i] <<= 1;

    𐡄𐡍 (!(s->tmp = av_malloc(len*حجم(*s->tmp))))
        أرجع AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    أرجع 0;
}

#define DECL_COMP_IMDCT(N)                                                     \
ساكن فراغ TX_NAME(ff_tx_mdct_pfa_##N##xM_inv)(AVTXContext *s, فراغ *_dst,    \
                                                فراغ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXComplex *z = _dst, *exp = s->exp;                                        \
    ثابت TXSample *src = _src, *in1, *in2;                                    \
    ثابت صحيح len4 = s->len >> 2;                                              \
    ثابت صحيح len2 = s->len >> 1;                                              \
    ثابت صحيح m = s->sub->len;                                                 \
    ثابت صحيح *in_map = s->map, *out_map = in_map + N*m;                       \
    ثابت صحيح *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= حجم(*src); /* To convert it from bytes */                     \
    in1 = src;                                                                 \
    in2 = src + ((N*m*2) - 1) * stride;                                        \
                                                                               \
    لكل (صحيح i = 0; i < len2; i += N) {                                        \
        لكل (صحيح j = 0; j < N; j++) {                                          \
            ثابت صحيح k = in_map[j];                                           \
            TXComplex tmp = { in2[-k*stride], in1[k*stride] };                 \
            CMUL3(fft##N##in[j], tmp, exp[j]);                                 \
        }                                                                      \
        fft##N(s->tmp + *(sub_map++), fft##N##in, m);                          \
        exp += N;                                                              \
        in_map += N;                                                           \
    }                                                                          \
                                                                               \
    لكل (صحيح i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, حجم(TXComplex));   \
                                                                               \
    لكل (صحيح i = 0; i < len4; i++) {                                           \
        ثابت صحيح i0 = len4 + i, i1 = len4 - i - 1;                            \
        ثابت صحيح s0 = out_map[i0], s1 = out_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].im, s->tmp[s1].re };                     \
        TXComplex src0 = { s->tmp[s0].im, s->tmp[s0].re };                     \
                                                                               \
        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, exp[i1].im, exp[i1].re);    \
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, exp[i0].im, exp[i0].re);    \
    }                                                                          \
}                                                                              \
                                                                               \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_inv_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_inv"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_inv),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_INVERSE_ONLY,   \
    .factors    = { N, TX_FACTOR_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

DECL_COMP_IMDCT(3)
DECL_COMP_IMDCT(5)
DECL_COMP_IMDCT(7)
DECL_COMP_IMDCT(9)
DECL_COMP_IMDCT(15)

#define DECL_COMP_MDCT(N)                                                      \
ساكن فراغ TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd)(AVTXContext *s, فراغ *_dst,    \
                                                فراغ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXSample *src = _src, *dst = _dst;                                         \
    TXComplex *exp = s->exp, tmp;                                              \
    ثابت صحيح m = s->sub->len;                                                 \
    ثابت صحيح len4 = N*m;                                                      \
    ثابت صحيح len3 = len4 * 3;                                                 \
    ثابت صحيح len8 = s->len >> 2;                                              \
    ثابت صحيح *in_map = s->map, *out_map = in_map + N*m;                       \
    ثابت صحيح *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= حجم(*dst);                                                    \
                                                                               \
    لكل (صحيح i = 0; i < m; i++) { /* Folding and pre-reindexing */             \
        لكل (صحيح j = 0; j < N; j++) {                                          \
            ثابت صحيح k = in_map[i*N + j];                                     \
            𐡄𐡍 (k < len4) {                                                    \
                tmp.re = FOLD(-src[ len4 + k],  src[1*len4 - 1 - k]);          \
                tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);          \
            } وإلا {                                                           \
                tmp.re = FOLD(-src[ len4 + k], -src[5*len4 - 1 - k]);          \
                tmp.im = FOLD( src[-len4 + k], -src[1*len3 - 1 - k]);          \
            }                                                                  \
            CMUL(fft##N##in[j].im, fft##N##in[j].re, tmp.re, tmp.im,           \
                 exp[k >> 1].re, exp[k >> 1].im);                              \
        }                                                                      \
        fft##N(s->tmp + sub_map[i], fft##N##in, m);                            \
    }                                                                          \
                                                                               \
    لكل (صحيح i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, حجم(TXComplex));   \
                                                                               \
    لكل (صحيح i = 0; i < len8; i++) {                                           \
        ثابت صحيح i0 = len8 + i, i1 = len8 - i - 1;                            \
        ثابت صحيح s0 = out_map[i0], s1 = out_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].re, s->tmp[s1].im };                     \
        TXComplex src0 = { s->tmp[s0].re, s->tmp[s0].im };                     \
                                                                               \
        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,    \
             exp[i0].im, exp[i0].re);                                          \
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,    \
             exp[i1].im, exp[i1].re);                                          \
    }                                                                          \
}                                                                              \
                                                                               \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_fwd"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_OUT_OF_PLACE | FF_TX_FORWARD_ONLY,   \
    .factors    = { N, TX_FACTOR_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

DECL_COMP_MDCT(3)
DECL_COMP_MDCT(5)
DECL_COMP_MDCT(7)
DECL_COMP_MDCT(9)
DECL_COMP_MDCT(15)

ساكن av_cold صحيح TX_NAME(ff_tx_rdft_init)(AVTXContext *s,
                                            ثابت FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            صحيح len, صحيح inv,
                                            ثابت فراغ *scale)
{
    صحيح ret;
    مزدوج f, m;
    TXSample *tab;
    uint64_t r2r = flags & AV_TX_REAL_TO_REAL;
    صحيح len4 = FFALIGN(len, 4) / 4;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~(AV_TX_REAL_TO_REAL | AV_TX_REAL_TO_IMAGINARY);

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, عدم, len >> 1, inv, scale)))
        أرجع ret;

    𐡄𐡍 (!(s->exp = av_mallocz((8 + 2*len4)*حجم(*s->exp))))
        أرجع AVERROR(ENOMEM);

    tab = (TXSample *)s->exp;

    f = 2*M_PI/len;

    m = (inv ? 2*s->scale_d : s->scale_d);

    *tab++ = RESCALE((inv ? 0.5 : 1.0) * m);
    *tab++ = RESCALE(inv ? 0.5*m : 1.0*m);
    *tab++ = RESCALE( m);
    *tab++ = RESCALE(-m);

    *tab++ = RESCALE( (0.5 - 0.0) * m);
    𐡄𐡍 (r2r)
        *tab++ = 1 / s->scale_f;
    وإلا
        *tab++ = RESCALE( (0.0 - 0.5) * m);
    *tab++ = RESCALE( (0.5 - inv) * m);
    *tab++ = RESCALE(-(0.5 - inv) * m);

    لكل (صحيح i = 0; i < len4; i++)
        *tab++ = RESCALE(cos(i*f));

    tab = ((TXSample *)s->exp) + len4 + 8;

    لكل (صحيح i = 0; i < len4; i++)
        *tab++ = RESCALE(cos(((len - i*4)/4.0)*f)) * (inv ? 1 : -1);

    أرجع 0;
}

#define DECL_RDFT(n, inv)                                                      \
ساكن فراغ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, فراغ *_dst,               \
                                     فراغ *_src, ptrdiff_t stride)             \
{                                                                              \
    ثابت صحيح len2 = s->len >> 1;                                              \
    ثابت صحيح len4 = s->len >> 2;                                              \
    ثابت TXSample *fact = (فراغ *)s->exp;                                     \
    ثابت TXSample *tcos = fact + 8;                                           \
    ثابت TXSample *tsin = tcos + len4;                                        \
    TXComplex *data = inv ? _src : _dst;                                       \
    TXComplex t[3];                                                            \
                                                                               \
    𐡄𐡍 (!inv)                                                                  \
        s->fn[0](&s->sub[0], data, _src, حجم(TXComplex));                   \
    وإلا                                                                       \
        data[0].im = data[len2].re;                                            \
                                                                               \
    /* The DC value's both components are real, but we need to change them     \
     * into complex values. Also, the middle of the array is special-cased.    \
     * These operations can be done before or after the loop. */               \
    t[0].re = data[0].re;                                                      \
    data[0].re = t[0].re + data[0].im;                                         \
    data[0].im = t[0].re - data[0].im;                                         \
    data[   0].re = MULT(fact[0], data[   0].re);                              \
    data[   0].im = MULT(fact[1], data[   0].im);                              \
    data[len4].re = MULT(fact[2], data[len4].re);                              \
    data[len4].im = MULT(fact[3], data[len4].im);                              \
                                                                               \
    لكل (صحيح i = 1; i < len4; i++) {                                           \
        /* Separate even and odd FFTs */                                       \
        t[0].re = MULT(fact[4], (data[i].re + data[len2 - i].re));             \
        t[0].im = MULT(fact[5], (data[i].im - data[len2 - i].im));             \
        t[1].re = MULT(fact[6], (data[i].im + data[len2 - i].im));             \
        t[1].im = MULT(fact[7], (data[i].re - data[len2 - i].re));             \
                                                                               \
        /* Apply twiddle factors to the odd FFT and add to the even FFT */     \
        CMUL(t[2].re, t[2].im, t[1].re, t[1].im, tcos[i], tsin[i]);            \
                                                                               \
        data[       i].re = t[0].re + t[2].re;                                 \
        data[       i].im = t[2].im - t[0].im;                                 \
        data[len2 - i].re = t[0].re - t[2].re;                                 \
        data[len2 - i].im = t[2].im + t[0].im;                                 \
    }                                                                          \
                                                                               \
    𐡄𐡍 (inv) {                                                                 \
        s->fn[0](&s->sub[0], _dst, data, حجم(TXComplex));                   \
    } وإلا {                                                                   \
        /* Move [0].im to the last position, as convention requires */         \
        data[len2].re = data[0].im;                                            \
        data[   0].im = data[len2].im = 0;                                     \
    }                                                                          \
}                                                                              \
                                                                               \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_OUT_OF_PLACE |       \
                  (inv ? FF_TX_INVERSE_ONLY : FF_TX_FORWARD_ONLY),             \
    .factors    = { 4, TX_FACTOR_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = 4,                                                           \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

DECL_RDFT(r2c,  0)
DECL_RDFT(c2r,  1)

#define DECL_RDFT_HALF(n, mode, mod2)                                          \
ساكن فراغ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, فراغ *_dst,               \
                                        فراغ *_src, ptrdiff_t stride)          \
{                                                                              \
    ثابت صحيح len = s->len;                                                    \
    ثابت صحيح len2 = len >> 1;                                                 \
    ثابت صحيح len4 = len >> 2;                                                 \
    ثابت صحيح aligned_len4 = FFALIGN(len, 4)/4;                                \
    ثابت TXSample *fact = (فراغ *)s->exp;                                     \
    ثابت TXSample *tcos = fact + 8;                                           \
    ثابت TXSample *tsin = tcos + aligned_len4;                                \
    TXComplex *data = _dst;                                                    \
    TXSample *out = _dst; /* Half-complex is forward-only */                   \
    TXSample tmp_dc;                                                           \
    av_unused TXSample tmp_mid;                                                \
    TXSample tmp[4];                                                           \
    TXComplex sf, sl;                                                          \
                                                                               \
    s->fn[0](&s->sub[0], _dst, _src, حجم(TXComplex));                       \
                                                                               \
    tmp_dc = data[0].re;                                                       \
    data[   0].re = tmp_dc + data[0].im;                                       \
    tmp_dc        = tmp_dc - data[0].im;                                       \
                                                                               \
    data[   0].re = MULT(fact[0], data[   0].re);                              \
    tmp_dc        = MULT(fact[1],        tmp_dc);                              \
    data[len4].re = MULT(fact[2], data[len4].re);                              \
                                                                               \
    𐡄𐡍 (!mod2) {                                                               \
        data[len4].im = MULT(fact[3], data[len4].im);                          \
    } وإلا {                                                                   \
        sf = data[len4];                                                       \
        sl = data[len4 + 1];                                                   \
        𐡄𐡍 (mode == AV_TX_REAL_TO_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        وإلا                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        𐡄𐡍 (mode == AV_TX_REAL_TO_REAL) {                                      \
            tmp[3]  = tmp[1]*tcos[len4] - tmp[2]*tsin[len4];                   \
            tmp_mid = (tmp[0] - tmp[3]);                                       \
        } وإلا {                                                               \
            tmp[3]  = tmp[1]*tsin[len4] + tmp[2]*tcos[len4];                   \
            tmp_mid = (tmp[0] + tmp[3]);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* NOTE: unrolling this breaks non-mod8 lengths */                         \
    لكل (صحيح i = 1; i <= len4; i++) {                                          \
        TXSample tmp[4];                                                       \
        TXComplex sf = data[i];                                                \
        TXComplex sl = data[len2 - i];                                         \
                                                                               \
        𐡄𐡍 (mode == AV_TX_REAL_TO_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        وإلا                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
                                                                               \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        𐡄𐡍 (mode == AV_TX_REAL_TO_REAL) {                                      \
            tmp[3]           = tmp[1]*tcos[i] - tmp[2]*tsin[i];                \
            out[i]           = (tmp[0] + tmp[3]);                              \
            out[len - i]     = (tmp[0] - tmp[3]);                              \
        } وإلا {                                                               \
            tmp[3]           = tmp[1]*tsin[i] + tmp[2]*tcos[i];                \
            out[i - 1]       = (tmp[3] - tmp[0]);                              \
            out[len - i - 1] = (tmp[0] + tmp[3]);                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    لكل (صحيح i = 1; i < (len4 + (mode == AV_TX_REAL_TO_IMAGINARY)); i++)       \
        out[len2 - i] = out[len - i];                                          \
                                                                               \
    𐡄𐡍 (mode == AV_TX_REAL_TO_REAL) {                                          \
        out[len2] = tmp_dc;                                                    \
        𐡄𐡍 (mod2)                                                              \
            out[len4 + 1] = tmp_mid * fact[5];                                 \
    } وإلا 𐡄𐡍 (mod2) {                                                         \
        out[len4] = tmp_mid;                                                   \
    }                                                                          \
}                                                                              \
                                                                               \
ساكن ثابت FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | mode |                     \
                  FF_TX_OUT_OF_PLACE | FF_TX_FORWARD_ONLY,                     \
    .factors    = { 2 + 2*(!mod2), TX_FACTOR_ANY },                            \
    .nb_factors = 2,                                                           \
    .min_len    = 2 + 2*(!mod2),                                               \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_BASE,                                             \
};

DECL_RDFT_HALF(r2r,      AV_TX_REAL_TO_REAL,      0)
DECL_RDFT_HALF(r2r_mod2, AV_TX_REAL_TO_REAL,      1)
DECL_RDFT_HALF(r2i,      AV_TX_REAL_TO_IMAGINARY, 0)
DECL_RDFT_HALF(r2i_mod2, AV_TX_REAL_TO_IMAGINARY, 1)

ساكن av_cold صحيح TX_NAME(ff_tx_dct_init)(AVTXContext *s,
                                           ثابت FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           صحيح len, صحيح inv,
                                           ثابت فراغ *scale)
{
    صحيح ret;
    مزدوج freq;
    TXSample *tab;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    𐡄𐡍 (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, عدم, len, inv, &rsc)))
        أرجع ret;

    s->exp = av_malloc((len/2)*3*حجم(TXSample));
    𐡄𐡍 (!s->exp)
        أرجع AVERROR(ENOMEM);

    tab = (TXSample *)s->exp;

    freq = M_PI/(len*2);

    لكل (صحيح i = 0; i < len; i++)
        tab[i] = RESCALE(cos(i*freq)*(!inv + 1));

    𐡄𐡍 (inv) {
        لكل (صحيح i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(0.5 / sin((2*i + 1)*freq));
    } وإلا {
        لكل (صحيح i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(cos((len - 2*i - 1)*freq));
    }

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_dctII)(AVTXContext *s, فراغ *_dst,
                                 فراغ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ثابت صحيح len = s->len;
    ثابت صحيح len2 = len >> 1;
    ثابت TXSample *exp = (فراغ *)s->exp;
    TXSample next;
#ifdef TX_INT32
    int64_t tmp1, tmp2;
#وإلا
    TXSample tmp1, tmp2;
#endif

    لكل (صحيح i = 0; i < len2; i++) {
        TXSample in1 = src[i];
        TXSample in2 = src[len - i - 1];
        TXSample s    = exp[len + i];

#ifdef TX_INT32
        tmp1 = in1 + in2;
        tmp2 = in1 - in2;

        tmp1 >>= 1;
        tmp2 *= s;

        tmp2 = (tmp2 + 0x40000000) >> 31;
#وإلا
        tmp1 = (in1 + in2)*0.5;
        tmp2 = (in1 - in2)*s;
#endif

        src[i]           = tmp1 + tmp2;
        src[len - i - 1] = tmp1 - tmp2;
    }

    s->fn[0](&s->sub[0], dst, src, حجم(TXComplex));

    next = dst[len];

    لكل (صحيح i = len - 2; i > 0; i -= 2) {
        TXSample tmp;

        CMUL(tmp, dst[i], exp[len - i], exp[i], dst[i + 0], dst[i + 1]);

        dst[i + 1] = next;

        next += tmp;
    }

#ifdef TX_INT32
    tmp1 = ((int64_t)exp[0]) * ((int64_t)dst[0]);
    dst[0] = (tmp1 + 0x40000000) >> 31;
#وإلا
    dst[0] = exp[0] * dst[0];
#endif
    dst[1] = next;
}

ساكن فراغ TX_NAME(ff_tx_dctIII)(AVTXContext *s, فراغ *_dst,
                                  فراغ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ثابت صحيح len = s->len;
    ثابت صحيح len2 = len >> 1;
    ثابت TXSample *exp = (فراغ *)s->exp;
#ifdef TX_INT32
    int64_t  tmp1, tmp2 = src[len - 1];
    tmp2 = (2*tmp2 + 0x40000000) >> 31;
#وإلا
    TXSample tmp1, tmp2 = 2*src[len - 1];
#endif

    src[len] = tmp2;

    لكل (صحيح i = len - 2; i >= 2; i -= 2) {
        TXSample val1 = src[i - 0];
        TXSample val2 = src[i - 1] - src[i + 1];

        CMUL(src[i + 1], src[i], exp[len - i], exp[i], val1, val2);
    }

    s->fn[0](&s->sub[0], dst, src, حجم(عائم));

    لكل (صحيح i = 0; i < len2; i++) {
        TXSample in1 = dst[i];
        TXSample in2 = dst[len - i - 1];
        TXSample c   = exp[len + i];

        tmp1 = in1 + in2;
        tmp2 = in1 - in2;
        tmp2 *= c;
#ifdef TX_INT32
        tmp2 = (tmp2 + 0x40000000) >> 31;
#endif

        dst[i]            = tmp1 + tmp2;
        dst[len - i - 1]  = tmp1 - tmp2;
    }
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_dctII_def) = {
    .name       = TX_NAME_STR("dctII"),
    .function   = TX_NAME(ff_tx_dctII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_OUT_OF_PLACE | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_FACTOR_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_dctIII_def) = {
    .name       = TX_NAME_STR("dctIII"),
    .function   = TX_NAME(ff_tx_dctIII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_OUT_OF_PLACE | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_FACTOR_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن av_cold صحيح TX_NAME(ff_tx_dcstI_init)(AVTXContext *s,
                                             ثابت FFTXCodelet *cd,
                                             uint64_t flags,
                                             FFTXCodeletOptions *opts,
                                             صحيح len, صحيح inv,
                                             ثابت فراغ *scale)
{
    صحيح ret;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    𐡄𐡍 (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    /* We want a half-complex RDFT */
    flags |= cd->type == TX_TYPE(DCT_I) ? AV_TX_REAL_TO_REAL :
                                          AV_TX_REAL_TO_IMAGINARY;

    𐡄𐡍 ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, عدم,
                                (len - 1 + 2*(cd->type == TX_TYPE(DST_I)))*2,
                                0, &rsc)))
        أرجع ret;

    s->tmp = av_mallocz((len + 1)*2*حجم(TXSample));
    𐡄𐡍 (!s->tmp)
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

ساكن فراغ TX_NAME(ff_tx_dctI)(AVTXContext *s, فراغ *_dst,
                                فراغ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ثابت صحيح len = s->len - 1;
    TXSample *tmp = (TXSample *)s->tmp;

    stride /= حجم(TXSample);

    لكل (صحيح i = 0; i < len; i++)
        tmp[i] = tmp[2*len - i] = src[i * stride];

    tmp[len] = src[len * stride]; /* Middle */

    s->fn[0](&s->sub[0], dst, tmp, حجم(TXSample));
}

ساكن فراغ TX_NAME(ff_tx_dstI)(AVTXContext *s, فراغ *_dst,
                                فراغ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ثابت صحيح len = s->len + 1;
    TXSample *tmp = (فراغ *)s->tmp;

    stride /= حجم(TXSample);

    tmp[0] = 0;

    لكل (صحيح i = 1; i < len; i++) {
        TXSample a = src[(i - 1) * stride];
        tmp[i] = -a;
        tmp[2*len - i] = a;
    }

    tmp[len] = 0; /* i == n, Nyquist */

    s->fn[0](&s->sub[0], dst, tmp, حجم(عائم));
}

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_dctI_def) = {
    .name       = TX_NAME_STR("dctI"),
    .function   = TX_NAME(ff_tx_dctI),
    .type       = TX_TYPE(DCT_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_OUT_OF_PLACE,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

ساكن ثابت FFTXCodelet TX_NAME(ff_tx_dstI_def) = {
    .name       = TX_NAME_STR("dstI"),
    .function   = TX_NAME(ff_tx_dstI),
    .type       = TX_TYPE(DST_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_OUT_OF_PLACE,
    .factors    = { 2, TX_FACTOR_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_BASE,
};

صحيح TX_TAB(ff_tx_mdct_gen_exp)(AVTXContext *s, صحيح *pre_tab)
{
    صحيح off = 0;
    صحيح len4 = s->len >> 1;
    مزدوج scale = s->scale_d;
    ثابت مزدوج theta = (scale < 0 ? len4 : 0) + 1.0/8.0;
    size_t alloc = pre_tab ? 2*len4 : len4;

    𐡄𐡍 (!(s->exp = av_malloc_array(alloc, حجم(*s->exp))))
        أرجع AVERROR(ENOMEM);

    scale = sqrt(fabs(scale));

    𐡄𐡍 (pre_tab)
        off = len4;

    لكل (صحيح i = 0; i < len4; i++) {
        ثابت مزدوج alpha = M_PI_2 * (i + theta) / len4;
        s->exp[off + i] = (TXComplex){ RESCALE(cos(alpha) * scale),
                                       RESCALE(sin(alpha) * scale) };
    }

    𐡄𐡍 (pre_tab)
        لكل (صحيح i = 0; i < len4; i++)
            s->exp[i] = s->exp[len4 + pre_tab[i]];

    أرجع 0;
}

ثابت FFTXCodelet * ثابت TX_NAME(ff_tx_codelet_list)[] = {
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
    &TX_NAME(ff_tx_mdct_inv_full_def),
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

    عدم,
};
