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

#ಅನ್ತರ್ಭಾವ "mem.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೋಷ್ಟಕ_DEF(name, ಗಾತ್ರ_2) \
    DECLARE_ALIGNED(32, TXSample, TX_TAB(ff_tx_tab_ ##name))[ಗಾತ್ರ_2]

#ವ್ಯಾಖ್ಯಾನಿಸು SR_POW2_TABLES \
    SR_ಕೋಷ್ಟಕ(8)        \
    SR_ಕೋಷ್ಟಕ(16)       \
    SR_ಕೋಷ್ಟಕ(32)       \
    SR_ಕೋಷ್ಟಕ(64)       \
    SR_ಕೋಷ್ಟಕ(128)      \
    SR_ಕೋಷ್ಟಕ(256)      \
    SR_ಕೋಷ್ಟಕ(512)      \
    SR_ಕೋಷ್ಟಕ(1024)     \
    SR_ಕೋಷ್ಟಕ(2048)     \
    SR_ಕೋಷ್ಟಕ(4096)     \
    SR_ಕೋಷ್ಟಕ(8192)     \
    SR_ಕೋಷ್ಟಕ(16384)    \
    SR_ಕೋಷ್ಟಕ(32768)    \
    SR_ಕೋಷ್ಟಕ(65536)    \
    SR_ಕೋಷ್ಟಕ(131072)   \

#ವ್ಯಾಖ್ಯಾನಿಸು SR_ಕೋಷ್ಟಕ(len) \
    ಕೋಷ್ಟಕ_DEF(len, len/4 + 1);
/* Power of two tables */
SR_POW2_TABLES
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SR_ಕೋಷ್ಟಕ

/* Other factors' tables */
ಕೋಷ್ಟಕ_DEF(53, 12);
ಕೋಷ್ಟಕ_DEF( 7,  6);
ಕೋಷ್ಟಕ_DEF( 9,  8);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFTab_Init_ದತ್ತಾಂಶ {
    ಶೂನ್ಯ (*func)(ಶೂನ್ಯ);
    ಪೂರ್ಣಾಂಕ factors[TX_MAX_SUB]; /* Must be sorted high -> low */
} FFTab_Init_ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿಸು SR_ಕೋಷ್ಟಕ(len)                                              \
ಸ್ಥಿರ av_cold ಶೂನ್ಯ TX_TAB(ff_tx_init_tab_ ##len)(ಶೂನ್ಯ)            \
{                                                                  \
    ದ್ವಿಗುಣ freq = 2*M_PI/len;                                      \
    TXSample *tab = TX_TAB(ff_tx_tab_ ##len);                      \
                                                                   \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len/4; i++)                                \
        *tab++ = RESCALE(ಕೋಜ್ಯಾ(i*freq));                             \
                                                                   \
    *tab = 0;                                                      \
}
SR_POW2_TABLES
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SR_ಕೋಷ್ಟಕ

ಸ್ಥಿರ ಶೂನ್ಯ (*ಸ್ಥಿರಾಂಕ sr_tabs_init_funcs[])(ಶೂನ್ಯ) = {
#ವ್ಯಾಖ್ಯಾನಿಸು SR_ಕೋಷ್ಟಕ(len) TX_TAB(ff_tx_init_tab_ ##len),
    SR_POW2_TABLES
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SR_ಕೋಷ್ಟಕ
};

ಸ್ಥಿರ AVOnce sr_tabs_init_once[] = {
#ವ್ಯಾಖ್ಯಾನಿಸು SR_ಕೋಷ್ಟಕ(len) AV_ONCE_INIT,
    SR_POW2_TABLES
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SR_ಕೋಷ್ಟಕ
};

ಸ್ಥಿರ av_cold ಶೂನ್ಯ TX_TAB(ff_tx_init_tab_53)(ಶೂನ್ಯ)
{
    /* 5pt, doubled to eliminate AVX lane shuffles */
    TX_TAB(ff_tx_tab_53)[0] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[1] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[2] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[3] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[4] = RESCALE(ಜ್ಯಾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[5] = RESCALE(ಜ್ಯಾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[6] = RESCALE(ಜ್ಯಾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[7] = RESCALE(ಜ್ಯಾ(2 * M_PI / 10));

    /* 3pt */
    TX_TAB(ff_tx_tab_53)[ 8] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[ 9] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[10] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  6));
    TX_TAB(ff_tx_tab_53)[11] = RESCALE(ಕೋಜ್ಯಾ(8 * M_PI /  6));
}

ಸ್ಥಿರ av_cold ಶೂನ್ಯ TX_TAB(ff_tx_init_tab_7)(ಶೂನ್ಯ)
{
    TX_TAB(ff_tx_tab_7)[0] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[1] = RESCALE(ಜ್ಯಾ(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[2] = RESCALE(ಜ್ಯಾ(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[3] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[4] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 14));
    TX_TAB(ff_tx_tab_7)[5] = RESCALE(ಜ್ಯಾ(2 * M_PI / 14));
}

ಸ್ಥಿರ av_cold ಶೂನ್ಯ TX_TAB(ff_tx_init_tab_9)(ಶೂನ್ಯ)
{
    TX_TAB(ff_tx_tab_9)[0] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[1] = RESCALE(ಜ್ಯಾ(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[2] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[3] = RESCALE(ಜ್ಯಾ(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[4] = RESCALE(ಕೋಜ್ಯಾ(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[5] = RESCALE(ಜ್ಯಾ(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[6] = TX_TAB(ff_tx_tab_9)[2] + TX_TAB(ff_tx_tab_9)[5];
    TX_TAB(ff_tx_tab_9)[7] = TX_TAB(ff_tx_tab_9)[3] - TX_TAB(ff_tx_tab_9)[4];
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTab_Init_ದತ್ತಾಂಶ nptwo_tabs_init_ದತ್ತಾಂಶ[] = {
    { TX_TAB(ff_tx_init_tab_53),      { 15, 5, 3 } },
    { TX_TAB(ff_tx_init_tab_9),       {  9 }       },
    { TX_TAB(ff_tx_init_tab_7),       {  7 }       },
};

ಸ್ಥಿರ AVOnce nptwo_tabs_init_once[] = {
    AV_ONCE_INIT,
    AV_ONCE_INIT,
    AV_ONCE_INIT,
};

av_cold ಶೂನ್ಯ TX_TAB(ff_tx_init_tabs)(ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ ಗುಣಕ_2 = ff_ctz(len);
    ಆದರೆ (ಗುಣಕ_2) {
        ಪೂರ್ಣಾಂಕ idx = ಗುಣಕ_2 - 3;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= idx; i++)
            ff_thread_once(&sr_tabs_init_once[i],
                            sr_tabs_init_funcs[i]);
        len >>= ಗುಣಕ_2;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(nptwo_tabs_init_ದತ್ತಾಂಶ); i++) {
        ಪೂರ್ಣಾಂಕ f, f_idx = 0;

        ಆದರೆ (len <= 1)
            ಹಿಂತಿರುಗಿ;

        ಆಗ ((f = nptwo_tabs_init_ದತ್ತಾಂಶ[i].factors[f_idx++])) {
            ಆದರೆ (f % len)
                ಮುಂದುವರಿ;

            ff_thread_once(&nptwo_tabs_init_once[i],
                            nptwo_tabs_init_ದತ್ತಾಂಶ[i].func);
            len /= f;
            ನಿಲ್ಲಿಸು;
        }
    }
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ fft3(TXComplex *ಹೊರಹೋಗು, TXComplex *ಒಳ,
                                  ptrdiff_t stride)
{
    TXComplex tmp[3];
    ಸ್ಥಿರಾಂಕ TXSample *tab = TX_TAB(ff_tx_tab_53);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    int64_t mtmp[4];
#ಆದರೆ_ಅಂತ್ಯ

    tmp[0] = ಒಳ[0];
    BF(tmp[1].re, tmp[2].im, ಒಳ[1].im, ಒಳ[2].im);
    BF(tmp[1].im, tmp[2].re, ಒಳ[1].re, ಒಳ[2].re);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    ಹೊರಹೋಗು[0*stride].re = (int64_t)tmp[0].re + tmp[2].re;
    ಹೊರಹೋಗು[0*stride].im = (int64_t)tmp[0].im + tmp[2].im;
    mtmp[0] = (int64_t)tab[ 8] * tmp[1].re;
    mtmp[1] = (int64_t)tab[ 9] * tmp[1].im;
    mtmp[2] = (int64_t)tab[10] * tmp[2].re;
    mtmp[3] = (int64_t)tab[10] * tmp[2].im;
    ಹೊರಹೋಗು[1*stride].re = tmp[0].re - (mtmp[2] + mtmp[0] + 0x40000000 >> 31);
    ಹೊರಹೋಗು[1*stride].im = tmp[0].im - (mtmp[3] - mtmp[1] + 0x40000000 >> 31);
    ಹೊರಹೋಗು[2*stride].re = tmp[0].re - (mtmp[2] - mtmp[0] + 0x40000000 >> 31);
    ಹೊರಹೋಗು[2*stride].im = tmp[0].im - (mtmp[3] + mtmp[1] + 0x40000000 >> 31);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹೊರಹೋಗು[0*stride].re = tmp[0].re + tmp[2].re;
    ಹೊರಹೋಗು[0*stride].im = tmp[0].im + tmp[2].im;
    tmp[1].re = tab[ 8] * tmp[1].re;
    tmp[1].im = tab[ 9] * tmp[1].im;
    tmp[2].re = tab[10] * tmp[2].re;
    tmp[2].im = tab[10] * tmp[2].im;
    ಹೊರಹೋಗು[1*stride].re = tmp[0].re - tmp[2].re + tmp[1].re;
    ಹೊರಹೋಗು[1*stride].im = tmp[0].im - tmp[2].im - tmp[1].im;
    ಹೊರಹೋಗು[2*stride].re = tmp[0].re - tmp[2].re - tmp[1].re;
    ಹೊರಹೋಗು[2*stride].im = tmp[0].im - tmp[2].im + tmp[1].im;
#ಆದರೆ_ಅಂತ್ಯ
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_FFT5(NAME, D0, D1, D2, D3, D4)                         \
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ NAME(TXComplex *ಹೊರಹೋಗು, TXComplex *ಒಳ,    \
                                  ptrdiff_t stride)                 \
{                                                                   \
    TXComplex dc, z0[4], t[6];                                      \
    ಸ್ಥಿರಾಂಕ TXSample *tab = TX_TAB(ff_tx_tab_53);                     \
                                                                    \
    dc = ಒಳ[0];                                                     \
    BF(t[1].im, t[0].re, ಒಳ[1].re, ಒಳ[4].re);                       \
    BF(t[1].re, t[0].im, ಒಳ[1].im, ಒಳ[4].im);                       \
    BF(t[3].im, t[2].re, ಒಳ[2].re, ಒಳ[3].re);                       \
    BF(t[3].re, t[2].im, ಒಳ[2].im, ಒಳ[3].im);                       \
                                                                    \
    ಹೊರಹೋಗು[D0*stride].re = dc.re + (TXUSample)t[0].re + t[2].re;        \
    ಹೊರಹೋಗು[D0*stride].im = dc.im + (TXUSample)t[0].im + t[2].im;        \
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
    ಹೊರಹೋಗು[D1*stride].re = dc.re + (TXUSample)z0[3].re;                 \
    ಹೊರಹೋಗು[D1*stride].im = dc.im + (TXUSample)z0[0].im;                 \
    ಹೊರಹೋಗು[D2*stride].re = dc.re + (TXUSample)z0[2].re;                 \
    ಹೊರಹೋಗು[D2*stride].im = dc.im + (TXUSample)z0[1].im;                 \
    ಹೊರಹೋಗು[D3*stride].re = dc.re + (TXUSample)z0[1].re;                 \
    ಹೊರಹೋಗು[D3*stride].im = dc.im + (TXUSample)z0[2].im;                 \
    ಹೊರಹೋಗು[D4*stride].re = dc.re + (TXUSample)z0[0].re;                 \
    ಹೊರಹೋಗು[D4*stride].im = dc.im + (TXUSample)z0[3].im;                 \
}

DECL_FFT5(fft5,     0,  1,  2,  3,  4)
DECL_FFT5(fft5_m1,  0,  6, 12,  3,  9)
DECL_FFT5(fft5_m2, 10,  1,  7, 13,  4)
DECL_FFT5(fft5_m3,  5, 11,  2,  8, 14)

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ fft7(TXComplex *ಹೊರಹೋಗು, TXComplex *ಒಳ,
                                  ptrdiff_t stride)
{
    TXComplex dc, t[6], z[3];
    ಸ್ಥಿರಾಂಕ TXComplex *tab = (ಸ್ಥಿರಾಂಕ TXComplex *)TX_TAB(ff_tx_tab_7);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    int64_t mtmp[12];
#ಆದರೆ_ಅಂತ್ಯ

    dc = ಒಳ[0];
    BF(t[1].re, t[0].re, ಒಳ[1].re, ಒಳ[6].re);
    BF(t[1].im, t[0].im, ಒಳ[1].im, ಒಳ[6].im);
    BF(t[3].re, t[2].re, ಒಳ[2].re, ಒಳ[5].re);
    BF(t[3].im, t[2].im, ಒಳ[2].im, ಒಳ[5].im);
    BF(t[5].re, t[4].re, ಒಳ[3].re, ಒಳ[4].re);
    BF(t[5].im, t[4].im, ಒಳ[3].im, ಒಳ[4].im);

    ಹೊರಹೋಗು[0*stride].re = dc.re + t[0].re + t[2].re + t[4].re;
    ಹೊರಹೋಗು[0*stride].im = dc.im + t[0].im + t[2].im + t[4].im;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32 /* NOTE: it's possible to do this with 16 mults but 72 adds */
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
#ಇಲ್ಲದಿದ್ದರೆ
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
#ಆದರೆ_ಅಂತ್ಯ

    BF(t[1].re, z[0].re, z[0].re, t[4].re);
    BF(t[3].re, z[1].re, z[1].re, t[2].re);
    BF(t[5].re, z[2].re, z[2].re, t[0].re);
    BF(t[1].im, z[0].im, z[0].im, t[0].im);
    BF(t[3].im, z[1].im, z[1].im, t[2].im);
    BF(t[5].im, z[2].im, z[2].im, t[4].im);

    ಹೊರಹೋಗು[1*stride].re = dc.re + z[0].re;
    ಹೊರಹೋಗು[1*stride].im = dc.im + t[1].im;
    ಹೊರಹೋಗು[2*stride].re = dc.re + t[3].re;
    ಹೊರಹೋಗು[2*stride].im = dc.im + z[1].im;
    ಹೊರಹೋಗು[3*stride].re = dc.re + z[2].re;
    ಹೊರಹೋಗು[3*stride].im = dc.im + t[5].im;
    ಹೊರಹೋಗು[4*stride].re = dc.re + t[5].re;
    ಹೊರಹೋಗು[4*stride].im = dc.im + z[2].im;
    ಹೊರಹೋಗು[5*stride].re = dc.re + z[1].re;
    ಹೊರಹೋಗು[5*stride].im = dc.im + t[3].im;
    ಹೊರಹೋಗು[6*stride].re = dc.re + t[1].re;
    ಹೊರಹೋಗು[6*stride].im = dc.im + z[0].im;
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ fft9(TXComplex *ಹೊರಹೋಗು, TXComplex *ಒಳ,
                                  ptrdiff_t stride)
{
    ಸ್ಥಿರಾಂಕ TXComplex *tab = (ಸ್ಥಿರಾಂಕ TXComplex *)TX_TAB(ff_tx_tab_9);
    TXComplex dc, t[16], w[4], x[5], y[5], z[2];
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    int64_t mtmp[12];
#ಆದರೆ_ಅಂತ್ಯ

    dc = ಒಳ[0];
    BF(t[1].re, t[0].re, ಒಳ[1].re, ಒಳ[8].re);
    BF(t[1].im, t[0].im, ಒಳ[1].im, ಒಳ[8].im);
    BF(t[3].re, t[2].re, ಒಳ[2].re, ಒಳ[7].re);
    BF(t[3].im, t[2].im, ಒಳ[2].im, ಒಳ[7].im);
    BF(t[5].re, t[4].re, ಒಳ[3].re, ಒಳ[6].re);
    BF(t[5].im, t[4].im, ಒಳ[3].im, ಒಳ[6].im);
    BF(t[7].re, t[6].re, ಒಳ[4].re, ಒಳ[5].re);
    BF(t[7].im, t[6].im, ಒಳ[4].im, ಒಳ[5].im);

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

    ಹೊರಹೋಗು[0*stride].re = z[0].re + z[1].re;
    ಹೊರಹೋಗು[0*stride].im = z[0].im + z[1].im;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
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
    z[0].re = ಒಳ[0].re + (int32_t)mtmp[2];
    z[0].im = ಒಳ[0].im + (int32_t)mtmp[3];

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

#ಇಲ್ಲದಿದ್ದರೆ
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
#ಆದರೆ_ಅಂತ್ಯ

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

    ಹೊರಹೋಗು[1*stride] = (TXComplex){ x[1].re + y[1].im, x[1].im - y[1].re };
    ಹೊರಹೋಗು[2*stride] = (TXComplex){ x[2].re + y[2].im, x[2].im - y[2].re };
    ಹೊರಹೋಗು[3*stride] = (TXComplex){ x[3].re + y[3].im, x[3].im - y[3].re };
    ಹೊರಹೋಗು[4*stride] = (TXComplex){ x[4].re + y[4].im, x[4].im - y[4].re };
    ಹೊರಹೋಗು[5*stride] = (TXComplex){ x[4].re - y[4].im, x[4].im + y[4].re };
    ಹೊರಹೋಗು[6*stride] = (TXComplex){ x[3].re - y[3].im, x[3].im + y[3].re };
    ಹೊರಹೋಗು[7*stride] = (TXComplex){ x[2].re - y[2].im, x[2].im + y[2].re };
    ಹೊರಹೋಗು[8*stride] = (TXComplex){ x[1].re - y[1].im, x[1].im + y[1].re };
}

ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ fft15(TXComplex *ಹೊರಹೋಗು, TXComplex *ಒಳ,
                                   ptrdiff_t stride)
{
    TXComplex tmp[15];

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 5; i++)
        fft3(tmp + i, ಒಳ + i*3, 5);

    fft5_m1(ಹೊರಹೋಗು, tmp +  0, stride);
    fft5_m2(ಹೊರಹೋಗು, tmp +  5, stride);
    fft5_m3(ಹೊರಹೋಗು, tmp + 10, stride);
}

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_ಗುಣಕ_init)(AVTXContext *s,
                                                  ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret = 0;
    TX_TAB(ff_tx_init_tabs)(len);

    ಆದರೆ (len == 15)
        ret = ff_tx_gen_pfa_ಒಳಹರಿವು_map(s, opts, 3, 5);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flags & FF_TX_PRESHUFFLE)
        ret = ff_tx_gen_default_map(s, opts);

    ಹಿಂತಿರುಗಿ ret;
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_ಗುಣಕ_S(n)                                                       \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft##n)(AVTXContext *s, ಶೂನ್ಯ *dst,                   \
                                  ಶೂನ್ಯ *src, ptrdiff_t stride)                 \
{                                                                              \
    fft##n((TXComplex *)dst, (TXComplex *)src, stride / ಗಾತ್ರ(TXComplex));    \
}                                                                              \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = {                    \
    .name       = TX_NAME_STR("fft" #n "_ns"),                                 \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು |                         \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,                          \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_ಗುಣಕ_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_ಗುಣಕ_F(n)                                                       \
DECL_ಗುಣಕ_S(n)                                                               \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft##n##_fwd_def) = {                   \
    .name       = TX_NAME_STR("fft" #n "_fwd"),                                \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು |                         \
                  AV_TX_UNALIGNED | FF_TX_FORWARD_ONLY,                        \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_ಗುಣಕ_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

DECL_ಗುಣಕ_F(3)
DECL_ಗುಣಕ_F(5)
DECL_ಗುಣಕ_F(7)
DECL_ಗುಣಕ_F(9)
DECL_ಗುಣಕ_S(15)

#ವ್ಯಾಖ್ಯಾನಿಸು BUTTERFLIES(a0, a1, a2, a3)            \
    ಮಾಡು {                                       \
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
    } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು TRANSFORM(a0, a1, a2, a3, wre, wim)    \
    ಮಾಡು {                                       \
        CMUL(t1, t2, a2.re, a2.im, wre, -wim); \
        CMUL(t5, t6, a3.re, a3.im, wre,  wim); \
        BUTTERFLIES(a0, a1, a2, a3);           \
    } ಆಗ (0)

/* z[0...8n-1], w[1...2n-1] */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ TX_NAME(ff_tx_fft_sr_combine)(TXComplex *z,
                                                 ಸ್ಥಿರಾಂಕ TXSample *ಕೋಜ್ಯಾ, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ o1 = 2*len;
    ಪೂರ್ಣಾಂಕ o2 = 4*len;
    ಪೂರ್ಣಾಂಕ o3 = 6*len;
    ಸ್ಥಿರಾಂಕ TXSample *wim = ಕೋಜ್ಯಾ + o1 - 7;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i += 4) {
        TRANSFORM(z[0], z[o1 + 0], z[o2 + 0], z[o3 + 0], ಕೋಜ್ಯಾ[0], wim[7]);
        TRANSFORM(z[2], z[o1 + 2], z[o2 + 2], z[o3 + 2], ಕೋಜ್ಯಾ[2], wim[5]);
        TRANSFORM(z[4], z[o1 + 4], z[o2 + 4], z[o3 + 4], ಕೋಜ್ಯಾ[4], wim[3]);
        TRANSFORM(z[6], z[o1 + 6], z[o2 + 6], z[o3 + 6], ಕೋಜ್ಯಾ[6], wim[1]);

        TRANSFORM(z[1], z[o1 + 1], z[o2 + 1], z[o3 + 1], ಕೋಜ್ಯಾ[1], wim[6]);
        TRANSFORM(z[3], z[o1 + 3], z[o2 + 3], z[o3 + 3], ಕೋಜ್ಯಾ[3], wim[4]);
        TRANSFORM(z[5], z[o1 + 5], z[o2 + 5], z[o3 + 5], ಕೋಜ್ಯಾ[5], wim[2]);
        TRANSFORM(z[7], z[o1 + 7], z[o2 + 7], z[o3 + 7], ಕೋಜ್ಯಾ[7], wim[0]);

        z   += 2*4;
        ಕೋಜ್ಯಾ += 2*4;
        wim -= 2*4;
    }
}

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_sr_codelet_init)(AVTXContext *s,
                                                      ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                      uint64_t flags,
                                                      FFTXCodeletOptions *opts,
                                                      ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    TX_TAB(ff_tx_init_tabs)(len);
    ಹಿಂತಿರುಗಿ ff_tx_gen_ptwo_revtab(s, opts);
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_SR_CODELET_DEF(n)                              \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = { \
    .name       = TX_NAME_STR("fft" #n "_ns"),              \
    .function   = TX_NAME(ff_tx_fft##n##_ns),               \
    .type       = TX_TYPE(FFT),                             \
    .flags      = FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | AV_TX_INPLACE |      \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,       \
    .factors[0] = 2,                                        \
    .nb_factors = 1,                                        \
    .min_len    = n,                                        \
    .max_len    = n,                                        \
    .init       = TX_NAME(ff_tx_fft_sr_codelet_init),       \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                      \
    .prio       = FF_TX_PRIO_ತಳ,                          \
};

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_SR_CODELET(n, n2, n4)                                    \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft##n##_ns)(AVTXContext *s, ಶೂನ್ಯ *_dst,    \
                                        ಶೂನ್ಯ *_src, ptrdiff_t stride) \
{                                                                     \
    TXComplex *src = _src;                                            \
    TXComplex *dst = _dst;                                            \
    ಸ್ಥಿರಾಂಕ TXSample *ಕೋಜ್ಯಾ = TX_TAB(ff_tx_tab_##n);                      \
                                                                      \
    TX_NAME(ff_tx_fft##n2##_ns)(s, dst,        src,        stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*2, src + n4*2, stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*3, src + n4*3, stride);   \
    TX_NAME(ff_tx_fft_sr_combine)(dst, ಕೋಜ್ಯಾ, n4 >> 1);                 \
}                                                                     \
                                                                      \
DECL_SR_CODELET_DEF(n)

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft2_ns)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                   ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;

    BF(tmp.re, dst[0].re, src[0].re, src[1].re);
    BF(tmp.im, dst[0].im, src[0].im, src[1].im);
    dst[1] = tmp;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft4_ns)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                   ಶೂನ್ಯ *_src, ptrdiff_t stride)
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

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft8_ns)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                   ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    ಸ್ಥಿರಾಂಕ TXSample ಕೋಜ್ಯಾ = TX_TAB(ff_tx_tab_8)[1];

    TX_NAME(ff_tx_fft4_ns)(s, dst, src, stride);

    BF(t1, dst[5].re, src[4].re, -src[5].re);
    BF(t2, dst[5].im, src[4].im, -src[5].im);
    BF(t5, dst[7].re, src[6].re, -src[7].re);
    BF(t6, dst[7].im, src[6].im, -src[7].im);

    BUTTERFLIES(dst[0], dst[2], dst[4], dst[6]);
    TRANSFORM(dst[1], dst[3], dst[5], dst[7], ಕೋಜ್ಯಾ, ಕೋಜ್ಯಾ);
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft16_ns)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                    ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ಸ್ಥಿರಾಂಕ TXSample *ಕೋಜ್ಯಾ = TX_TAB(ff_tx_tab_16);

    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    TXSample cos_16_1 = ಕೋಜ್ಯಾ[1];
    TXSample cos_16_2 = ಕೋಜ್ಯಾ[2];
    TXSample cos_16_3 = ಕೋಜ್ಯಾ[3];

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

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_init)(AVTXContext *s,
                                           ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                           ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ is_inplace = !!(flags & AV_TX_INPLACE);
    FFTXCodeletOptions sub_opts = {
        .map_dir = is_inplace ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    flags &= ~FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len, inv, scale)))
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (is_inplace && (ret = ff_tx_gen_inplace_map(s, len)))
        ಹಿಂತಿರುಗಿ ret;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_inplace_small_init)(AVTXContext *s,
                                                         ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                         uint64_t flags,
                                                         FFTXCodeletOptions *opts,
                                                         ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಆದರೆ (!(s->tmp = av_malloc(len*ಗಾತ್ರ(*s->tmp))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    flags &= ~AV_TX_INPLACE;
    ಹಿಂತಿರುಗಿ TX_NAME(ff_tx_fft_init)(s, cd, flags, opts, len, inv, scale);
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                               ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst1 = s->flags & AV_TX_INPLACE ? s->tmp : _dst;
    TXComplex *dst2 = _dst;
    ಪೂರ್ಣಾಂಕ *map = s->sub[0].map;
    ಪೂರ್ಣಾಂಕ len = s->len;

    /* Compilers can't vectorize this anyway without assuming AVX2, which they
     * generally don't, at least without -march=native -mtune=native */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
        dst1[i] = src[map[i]];

    s->fn[0](&s->sub[0], dst2, dst1, stride);
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft_inplace)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                       ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *map = s->sub->map;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *inplace_idx = s->map;
    ಪೂರ್ಣಾಂಕ src_idx, dst_idx;

    src_idx = *inplace_idx++;
    ಮಾಡು {
        tmp = src[src_idx];
        dst_idx = map[src_idx];
        ಮಾಡು {
            FFSWAP(TXComplex, tmp, src[dst_idx]);
            dst_idx = map[dst_idx];
        } ಆಗ (dst_idx != src_idx); /* Can be > as well, but was less predictable */
        src[dst_idx] = tmp;
    } ಆಗ ((src_idx = *inplace_idx++));

    s->fn[0](&s->sub[0], dst, src, stride);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_def) = {
    .name       = TX_NAME_STR("fft"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_inplace_small_def) = {
    .name       = TX_NAME_STR("fft_inplace_small"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | AV_TX_INPLACE,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 65536,
    .init       = TX_NAME(ff_tx_fft_inplace_small_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ - 256,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_inplace_def) = {
    .name       = TX_NAME_STR("fft_inplace"),
    .function   = TX_NAME(ff_tx_fft_inplace),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | AV_TX_INPLACE,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ - 512,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_init_naive_small)(AVTXContext *s,
                                                       ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                       uint64_t flags,
                                                       FFTXCodeletOptions *opts,
                                                       ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                       ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ phase = s->inv ? 2.0*M_PI/len : -2.0*M_PI/len;

    ಆದರೆ (!(s->ಘಾತಾಂಕ = av_malloc(len*len*ಗಾತ್ರ(*s->ಘಾತಾಂಕ))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < len; j++) {
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ ಗುಣಕ = phase*i*j;
            s->ಘಾತಾಂಕ[i*j] = (TXComplex){
                RESCALE(ಕೋಜ್ಯಾ(ಗುಣಕ)),
                RESCALE(ಜ್ಯಾ(ಗುಣಕ)),
            };
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft_naive)(AVTXContext *s, ಶೂನ್ಯ *_dst, ಶೂನ್ಯ *_src,
                                     ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n = s->len;
    ದ್ವಿಗುಣ phase = s->inv ? 2.0*M_PI/n : -2.0*M_PI/n;

    stride /= ಗಾತ್ರ(*dst);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < n; j++) {
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ ಗುಣಕ = phase*i*j;
            ಸ್ಥಿರಾಂಕ TXComplex mult = {
                RESCALE(ಕೋಜ್ಯಾ(ಗುಣಕ)),
                RESCALE(ಜ್ಯಾ(ಗುಣಕ)),
            };
            TXComplex res;
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft_naive_small)(AVTXContext *s, ಶೂನ್ಯ *_dst, ಶೂನ್ಯ *_src,
                                           ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n = s->len;

    stride /= ಗಾತ್ರ(*dst);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < n; j++) {
            TXComplex res;
            ಸ್ಥಿರಾಂಕ TXComplex mult = s->ಘಾತಾಂಕ[i*j];
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_naive_small_def) = {
    .name       = TX_NAME_STR("fft_naive_small"),
    .function   = TX_NAME(ff_tx_fft_naive_small),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 1024,
    .init       = TX_NAME(ff_tx_fft_init_naive_small),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN/2,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_naive_def) = {
    .name       = TX_NAME_STR("fft_naive"),
    .function   = TX_NAME(ff_tx_fft_naive),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = ಖಾಲಿ,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_fft_pfa_init)(AVTXContext *s,
                                               ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                               uint64_t flags,
                                               FFTXCodeletOptions *opts,
                                               ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                               ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret, *tmp, ps = flags & FF_TX_PRESHUFFLE;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };
    size_t extra_tmp_len = 0;
    ಪೂರ್ಣಾಂಕ len_list[TX_MAX_DECOMPOSITIONS];

    ಆದರೆ ((ret = ff_tx_decompose_ಉದ್ದಳತೆ(len_list, TX_TYPE(FFT), len, inv)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* Two iterations to test both orderings. */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ret; i++) {
        ಪೂರ್ಣಾಂಕ len1 = len_list[i];
        ಪೂರ್ಣಾಂಕ len2 = len / len1;

        /* Our ptwo transforms don't support striding the output. */
        ಆದರೆ (len2 & (len2 - 1))
            FFSWAP(ಪೂರ್ಣಾಂಕ, len1, len2);

        ff_tx_clear_ctx(s);

        /* First transform */
        sub_opts.map_dir = FF_TX_MAP_GATHER;
        flags &= ~AV_TX_INPLACE;
        flags |=  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು;
        flags |=  FF_TX_PRESHUFFLE; /* This function handles the permute step */
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len1, inv, scale);

        ಆದರೆ (ret == AVERROR(ENOMEM)) {
            ಹಿಂತಿರುಗಿ ret;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret < 0) { /* Try again without a preshuffle flag */
            flags &= ~FF_TX_PRESHUFFLE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len1, inv, scale);
            ಆದರೆ (ret == AVERROR(ENOMEM))
                ಹಿಂತಿರುಗಿ ret;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret < 0)
                ಮುಂದುವರಿ;
        }

        /* Second transform. */
        sub_opts.map_dir = FF_TX_MAP_SCATTER;
        flags |=  FF_TX_PRESHUFFLE;
retry:
        flags &= ~FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು;
        flags |=  AV_TX_INPLACE;
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len2, inv, scale);

        ಆದರೆ (ret == AVERROR(ENOMEM)) {
            ಹಿಂತಿರುಗಿ ret;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret < 0) { /* Try again with an out-of-place transform */
            flags |= FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು;
            flags &= ~AV_TX_INPLACE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len2, inv, scale);
            ಆದರೆ (ret == AVERROR(ENOMEM)) {
                ಹಿಂತಿರುಗಿ ret;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret < 0) {
                ಆದರೆ (flags & FF_TX_PRESHUFFLE) { /* Retry again without a preshuf flag */
                    flags &= ~FF_TX_PRESHUFFLE;
                    ಹೋಗು retry;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಮುಂದುವರಿ;
                }
            }
        }

        /* Success */
        ನಿಲ್ಲಿಸು;
    }

    /* If nothing was successful, error out */
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* Generate PFA map */
    ಆದರೆ ((ret = ff_tx_gen_compound_mapping(s, opts, 0,
                                          s->sub[0].len, s->sub[1].len)))
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (!(s->tmp = av_malloc(len*ಗಾತ್ರ(*s->tmp))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* Flatten input map */
    tmp = (ಪೂರ್ಣಾಂಕ *)s->tmp;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < len; k += s->sub[0].len) {
        ಸ್ಮರಣೆ_ನಕಲು(tmp, &s->map[k], s->sub[0].len*ಗಾತ್ರ(*tmp));
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->sub[0].len; i++)
            s->map[k + i] = tmp[s->sub[0].map[i]];
    }

    /* Only allocate extra temporary memory if we need it */
    ಆದರೆ (!(s->sub[1].flags & AV_TX_INPLACE))
        extra_tmp_len = len;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ps)
        extra_tmp_len = s->sub[0].len;

    ಆದರೆ (extra_tmp_len && !(s->ಘಾತಾಂಕ = av_malloc(extra_tmp_len*ಗಾತ್ರ(*s->ಘಾತಾಂಕ))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft_pfa)(AVTXContext *s, ಶೂನ್ಯ *ಹೊರಹೋಗು_3,
                                   ಶೂನ್ಯ *ಒಳ_3, ptrdiff_t stride)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಒಳ_map = s->map, *ಹೊರಹೋಗು_map = ಒಳ_map + l;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->ಘಾತಾಂಕ;
    TXComplex *ಒಳ = ಒಳ_3, *ಹೊರಹೋಗು = ಹೊರಹೋಗು_3;

    stride /= ಗಾತ್ರ(*ಹೊರಹೋಗು);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < m; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < n; j++)
            s->ಘಾತಾಂಕ[j] = ಒಳ[ಒಳ_map[i*n + j]];
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], s->ಘಾತಾಂಕ, m*ಗಾತ್ರ(TXComplex));
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], ಗಾತ್ರ(TXComplex));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < l; i++)
        ಹೊರಹೋಗು[i*stride] = tmp1[ಹೊರಹೋಗು_map[i]];
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_fft_pfa_ns)(AVTXContext *s, ಶೂನ್ಯ *ಹೊರಹೋಗು_3,
                                      ಶೂನ್ಯ *ಒಳ_3, ptrdiff_t stride)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಒಳ_map = s->map, *ಹೊರಹೋಗು_map = ಒಳ_map + l;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->ಘಾತಾಂಕ;
    TXComplex *ಒಳ = ಒಳ_3, *ಹೊರಹೋಗು = ಹೊರಹೋಗು_3;

    stride /= ಗಾತ್ರ(*ಹೊರಹೋಗು);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < m; i++)
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], &ಒಳ[i*n], m*ಗಾತ್ರ(TXComplex));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], ಗಾತ್ರ(TXComplex));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < l; i++)
        ಹೊರಹೋಗು[i*stride] = tmp1[ಹೊರಹೋಗು_map[i]];
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_pfa_def) = {
    .name       = TX_NAME_STR("fft_pfa"),
    .function   = TX_NAME(ff_tx_fft_pfa),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors    = { 7, 5, 3, 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_fft_pfa_ns_def) = {
    .name       = TX_NAME_STR("fft_pfa_ns"),
    .function   = TX_NAME(ff_tx_fft_pfa_ns),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು |
                  FF_TX_PRESHUFFLE,
    .factors    = { 7, 5, 3, 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_mdct_naive_init)(AVTXContext *s,
                                                  ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_naive_fwd)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                          ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    ದ್ವಿಗುಣ scale = s->scale_d;
    ಪೂರ್ಣಾಂಕ len = s->len;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ phase = M_PI/(4.0*len);

    stride /= ಗಾತ್ರ(*dst);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++) {
        ದ್ವಿಗುಣ ಮೊತ್ತ = 0.0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < len*2; j++) {
            ಪೂರ್ಣಾಂಕ a = (2*j + 1 + len) * (2*i + 1);
            ಮೊತ್ತ += UNSCALE(src[j]) * ಕೋಜ್ಯಾ(a * phase);
        }
        dst[i*stride] = RESCALE(ಮೊತ್ತ*scale);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_naive_inv)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                          ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    ದ್ವಿಗುಣ scale = s->scale_d;
    ಪೂರ್ಣಾಂಕ len = s->len >> 1;
    ಪೂರ್ಣಾಂಕ len2 = len*2;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ phase = M_PI/(4.0*len2);

    stride /= ಗಾತ್ರ(*src);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++) {
        ದ್ವಿಗುಣ ಮೊತ್ತ_d = 0.0;
        ದ್ವಿಗುಣ ಮೊತ್ತ_u = 0.0;
        ದ್ವಿಗುಣ i_d = phase * (4*len  - 2*i - 1);
        ದ್ವಿಗುಣ i_u = phase * (3*len2 + 2*i + 1);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < len2; j++) {
            ದ್ವಿಗುಣ a = (2 * j + 1);
            ದ್ವಿಗುಣ a_d = ಕೋಜ್ಯಾ(a * i_d);
            ದ್ವಿಗುಣ a_u = ಕೋಜ್ಯಾ(a * i_u);
            ದ್ವಿಗುಣ val = UNSCALE(src[j*stride]);
            ಮೊತ್ತ_d += a_d * val;
            ಮೊತ್ತ_u += a_u * val;
        }
        dst[i +   0] = RESCALE( ಮೊತ್ತ_d*scale);
        dst[i + len] = RESCALE(-ಮೊತ್ತ_u*scale);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_naive_fwd_def) = {
    .name       = TX_NAME_STR("mdct_naive_fwd"),
    .function   = TX_NAME(ff_tx_mdct_naive_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY }, /* MDCTs need an even length */
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_naive_inv_def) = {
    .name       = TX_NAME_STR("mdct_naive_inv"),
    .function   = TX_NAME(ff_tx_mdct_naive_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_mdct_init)(AVTXContext *s,
                                            ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                            ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;
    FFTXCodeletOptions sub_opts = {
        .map_dir = !inv ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* First try with an in-place transform */

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale))) {
        flags &= ~FF_TX_PRESHUFFLE; /* Now try with a generic FFT */
        ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                    inv, scale)))
            ಹಿಂತಿರುಗಿ ret;
    }

    s->map = av_malloc((len >> 1)*ಗಾತ್ರ(*s->map));
    ಆದರೆ (!s->map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* If we need to preshuffle copy the map from the subcontext */
    ಆದರೆ (s->sub[0].flags & FF_TX_PRESHUFFLE) {
        ಸ್ಮರಣೆ_ನಕಲು(s->map, s->sub->map, (len >> 1)*ಗಾತ್ರ(*s->map));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len >> 1; i++)
            s->map[i] = i;
    }

    ಆದರೆ ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : ಖಾಲಿ)))
        ಹಿಂತಿರುಗಿ ret;

    /* Saves a multiply in a hot path. */
    ಆದರೆ (inv)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < (s->len >> 1); i++)
            s->map[i] <<= 1;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_fwd)(AVTXContext *s, ಶೂನ್ಯ *_dst, ಶೂನ್ಯ *_src,
                                    ptrdiff_t stride)
{
    TXSample *src = _src, *dst = _dst;
    TXComplex *ಘಾತಾಂಕ = s->ಘಾತಾಂಕ, tmp, *z = _dst;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = s->len >> 1;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = s->len >> 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len3 = len2 * 3;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->map;

    stride /= ಗಾತ್ರ(*dst);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len2; i++) { /* Folding and pre-reindexing */
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k = 2*i;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ idx = sub_map[i];
        ಆದರೆ (k < len2) {
            tmp.re = FOLD(-src[ len2 + k],  src[1*len2 - 1 - k]);
            tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);
        } ಇಲ್ಲದಿದ್ದರೆ {
            tmp.re = FOLD(-src[ len2 + k], -src[5*len2 - 1 - k]);
            tmp.im = FOLD( src[-len2 + k], -src[1*len3 - 1 - k]);
        }
        CMUL(z[idx].im, z[idx].re, tmp.re, tmp.im, ಘಾತಾಂಕ[i].re, ಘಾತಾಂಕ[i].im);
    }

    s->fn[0](&s->sub[0], z, z, ಗಾತ್ರ(TXComplex));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].re, z[i1].im };
        TXComplex src0 = { z[i0].re, z[i0].im };

        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,
             ಘಾತಾಂಕ[i0].im, ಘಾತಾಂಕ[i0].re);
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,
             ಘಾತಾಂಕ[i1].im, ಘಾತಾಂಕ[i1].re);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_inv)(AVTXContext *s, ಶೂನ್ಯ *_dst, ಶೂನ್ಯ *_src,
                                    ptrdiff_t stride)
{
    TXComplex *z = _dst, *ಘಾತಾಂಕ = s->ಘಾತಾಂಕ;
    ಸ್ಥಿರಾಂಕ TXSample *src = _src, *in1, *in2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = s->len >> 1;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = s->len >> 2;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->map;

    stride /= ಗಾತ್ರ(*src);
    in1 = src;
    in2 = src + ((len2*2) - 1) * stride;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len2; i++) {
        ಪೂರ್ಣಾಂಕ k = sub_map[i];
        TXComplex tmp = { in2[-k*stride], in1[k*stride] };
        CMUL3(z[i], tmp, ಘಾತಾಂಕ[i]);
    }

    s->fn[0](&s->sub[0], z, z, ಗಾತ್ರ(TXComplex));

    ಘಾತಾಂಕ += len2;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].im, z[i1].re };
        TXComplex src0 = { z[i0].im, z[i0].re };

        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, ಘಾತಾಂಕ[i1].im, ಘಾತಾಂಕ[i1].re);
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, ಘಾತಾಂಕ[i0].im, ಘಾತಾಂಕ[i0].re);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_fwd_def) = {
    .name       = TX_NAME_STR("mdct_fwd"),
    .function   = TX_NAME(ff_tx_mdct_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_inv_def) = {
    .name       = TX_NAME_STR("mdct_inv"),
    .function   = TX_NAME(ff_tx_mdct_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ_init)(AVTXContext *s,
                                                     ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                     uint64_t flags,
                                                     FFTXCodeletOptions *opts,
                                                     ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                     ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~AV_TX_ತುಂಬಿದ_IMDCT;

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(MDCT), flags, ಖಾಲಿ, len, 1, scale)))
        ಹಿಂತಿರುಗಿ ret;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                         ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    ಪೂರ್ಣಾಂಕ len  = s->len << 1;
    ಪೂರ್ಣಾಂಕ len2 = len >> 1;
    ಪೂರ್ಣಾಂಕ len4 = len >> 2;
    TXSample *dst = _dst;

    s->fn[0](&s->sub[0], dst + len4, _src, stride);

    stride /= ಗಾತ್ರ(*dst);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++) {
        dst[            i*stride] = -dst[(len2 - i - 1)*stride];
        dst[(len - i - 1)*stride] =  dst[(len2 + i + 0)*stride];
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ_def) = {
    .name       = TX_NAME_STR("mdct_inv_full"),
    .function   = TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | AV_TX_ತುಂಬಿದ_IMDCT,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_mdct_pfa_init)(AVTXContext *s,
                                                ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                                uint64_t flags,
                                                FFTXCodeletOptions *opts,
                                                ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                                ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret, sub_len;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    len >>= 1;
    sub_len = len / cd->factors[0];

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        ಹಿಂತಿರುಗಿ ret;

    /* Our 15-point transform is also a compound one, so embed its input map */
    ಆದರೆ (cd->factors[0] == 15)
        TX_EMBED_ಒಳಹರಿವು_PFA_MAP(s->map, len, 3, 5);

    ಆದರೆ ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : ಖಾಲಿ)))
        ಹಿಂತಿರುಗಿ ret;

    /* Saves multiplies in loops. */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
        s->map[i] <<= 1;

    ಆದರೆ (!(s->tmp = av_malloc(len*ಗಾತ್ರ(*s->tmp))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    ಹಿಂತಿರುಗಿ 0;
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_COMP_IMDCT(N)                                                     \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_pfa_##N##xM_inv)(AVTXContext *s, ಶೂನ್ಯ *_dst,    \
                                                ಶೂನ್ಯ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXComplex *z = _dst, *ಘಾತಾಂಕ = s->ಘಾತಾಂಕ;                                        \
    ಸ್ಥಿರಾಂಕ TXSample *src = _src, *in1, *in2;                                    \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = s->len >> 2;                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = s->len >> 1;                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ m = s->sub->len;                                                 \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಒಳ_map = s->map, *ಹೊರಹೋಗು_map = ಒಳ_map + N*m;                       \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= ಗಾತ್ರ(*src); /* To convert it from bytes */                     \
    in1 = src;                                                                 \
    in2 = src + ((N*m*2) - 1) * stride;                                        \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len2; i += N) {                                        \
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < N; j++) {                                          \
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k = ಒಳ_map[j];                                           \
            TXComplex tmp = { in2[-k*stride], in1[k*stride] };                 \
            CMUL3(fft##N##in[j], tmp, ಘಾತಾಂಕ[j]);                                 \
        }                                                                      \
        fft##N(s->tmp + *(sub_map++), fft##N##in, m);                          \
        ಘಾತಾಂಕ += N;                                                              \
        ಒಳ_map += N;                                                           \
    }                                                                          \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, ಗಾತ್ರ(TXComplex));   \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++) {                                           \
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ i0 = len4 + i, i1 = len4 - i - 1;                            \
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s0 = ಹೊರಹೋಗು_map[i0], s1 = ಹೊರಹೋಗು_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].im, s->tmp[s1].re };                     \
        TXComplex src0 = { s->tmp[s0].im, s->tmp[s0].re };                     \
                                                                               \
        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, ಘಾತಾಂಕ[i1].im, ಘಾತಾಂಕ[i1].re);    \
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, ಘಾತಾಂಕ[i0].im, ಘಾತಾಂಕ[i0].re);    \
    }                                                                          \
}                                                                              \
                                                                               \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_inv_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_inv"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_inv),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_INVERSE_ONLY,   \
    .factors    = { N, TX_ಗುಣಕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

DECL_COMP_IMDCT(3)
DECL_COMP_IMDCT(5)
DECL_COMP_IMDCT(7)
DECL_COMP_IMDCT(9)
DECL_COMP_IMDCT(15)

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_COMP_MDCT(N)                                                      \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd)(AVTXContext *s, ಶೂನ್ಯ *_dst,    \
                                                ಶೂನ್ಯ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXSample *src = _src, *dst = _dst;                                         \
    TXComplex *ಘಾತಾಂಕ = s->ಘಾತಾಂಕ, tmp;                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ m = s->sub->len;                                                 \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = N*m;                                                      \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len3 = len4 * 3;                                                 \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len8 = s->len >> 2;                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಒಳ_map = s->map, *ಹೊರಹೋಗು_map = ಒಳ_map + N*m;                       \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= ಗಾತ್ರ(*dst);                                                    \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < m; i++) { /* Folding and pre-reindexing */             \
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < N; j++) {                                          \
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ k = ಒಳ_map[i*N + j];                                     \
            ಆದರೆ (k < len4) {                                                    \
                tmp.re = FOLD(-src[ len4 + k],  src[1*len4 - 1 - k]);          \
                tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);          \
            } ಇಲ್ಲದಿದ್ದರೆ {                                                           \
                tmp.re = FOLD(-src[ len4 + k], -src[5*len4 - 1 - k]);          \
                tmp.im = FOLD( src[-len4 + k], -src[1*len3 - 1 - k]);          \
            }                                                                  \
            CMUL(fft##N##in[j].im, fft##N##in[j].re, tmp.re, tmp.im,           \
                 ಘಾತಾಂಕ[k >> 1].re, ಘಾತಾಂಕ[k >> 1].im);                              \
        }                                                                      \
        fft##N(s->tmp + sub_map[i], fft##N##in, m);                            \
    }                                                                          \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, ಗಾತ್ರ(TXComplex));   \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len8; i++) {                                           \
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ i0 = len8 + i, i1 = len8 - i - 1;                            \
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s0 = ಹೊರಹೋಗು_map[i0], s1 = ಹೊರಹೋಗು_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].re, s->tmp[s1].im };                     \
        TXComplex src0 = { s->tmp[s0].re, s->tmp[s0].im };                     \
                                                                               \
        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,    \
             ಘಾತಾಂಕ[i0].im, ಘಾತಾಂಕ[i0].re);                                          \
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,    \
             ಘಾತಾಂಕ[i1].im, ಘಾತಾಂಕ[i1].re);                                          \
    }                                                                          \
}                                                                              \
                                                                               \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_fwd"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_FORWARD_ONLY,   \
    .factors    = { N, TX_ಗುಣಕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

DECL_COMP_MDCT(3)
DECL_COMP_MDCT(5)
DECL_COMP_MDCT(7)
DECL_COMP_MDCT(9)
DECL_COMP_MDCT(15)

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_rdft_init)(AVTXContext *s,
                                            ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                            ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;
    ದ್ವಿಗುಣ f, m;
    TXSample *tab;
    uint64_t r2r = flags & AV_TX_REAL_ಗಮ್ಯ_REAL;
    ಪೂರ್ಣಾಂಕ len4 = FFALIGN(len, 4) / 4;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~(AV_TX_REAL_ಗಮ್ಯ_REAL | AV_TX_REAL_ಗಮ್ಯ_IMAGINARY);

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, ಖಾಲಿ, len >> 1, inv, scale)))
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (!(s->ಘಾತಾಂಕ = av_mallocz((8 + 2*len4)*ಗಾತ್ರ(*s->ಘಾತಾಂಕ))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    tab = (TXSample *)s->ಘಾತಾಂಕ;

    f = 2*M_PI/len;

    m = (inv ? 2*s->scale_d : s->scale_d);

    *tab++ = RESCALE((inv ? 0.5 : 1.0) * m);
    *tab++ = RESCALE(inv ? 0.5*m : 1.0*m);
    *tab++ = RESCALE( m);
    *tab++ = RESCALE(-m);

    *tab++ = RESCALE( (0.5 - 0.0) * m);
    ಆದರೆ (r2r)
        *tab++ = 1 / s->scale_f;
    ಇಲ್ಲದಿದ್ದರೆ
        *tab++ = RESCALE( (0.0 - 0.5) * m);
    *tab++ = RESCALE( (0.5 - inv) * m);
    *tab++ = RESCALE(-(0.5 - inv) * m);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++)
        *tab++ = RESCALE(ಕೋಜ್ಯಾ(i*f));

    tab = ((TXSample *)s->ಘಾತಾಂಕ) + len4 + 8;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++)
        *tab++ = RESCALE(ಕೋಜ್ಯಾ(((len - i*4)/4.0)*f)) * (inv ? 1 : -1);

    ಹಿಂತಿರುಗಿ 0;
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_RDFT(n, inv)                                                      \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, ಶೂನ್ಯ *_dst,               \
                                     ಶೂನ್ಯ *_src, ptrdiff_t stride)             \
{                                                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = s->len >> 1;                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = s->len >> 2;                                              \
    ಸ್ಥಿರಾಂಕ TXSample *fact = (ಶೂನ್ಯ *)s->ಘಾತಾಂಕ;                                     \
    ಸ್ಥಿರಾಂಕ TXSample *tcos = fact + 8;                                           \
    ಸ್ಥಿರಾಂಕ TXSample *tsin = tcos + len4;                                        \
    TXComplex *ದತ್ತಾಂಶ = inv ? _src : _dst;                                       \
    TXComplex t[3];                                                            \
                                                                               \
    ಆದರೆ (!inv)                                                                  \
        s->fn[0](&s->sub[0], ದತ್ತಾಂಶ, _src, ಗಾತ್ರ(TXComplex));                   \
    ಇಲ್ಲದಿದ್ದರೆ                                                                       \
        ದತ್ತಾಂಶ[0].im = ದತ್ತಾಂಶ[len2].re;                                            \
                                                                               \
    /* The DC value's both components are real, but we need to change them     \
     * into complex values. Also, the middle of the array is special-cased.    \
     * These operations can be done before or after the loop. */               \
    t[0].re = ದತ್ತಾಂಶ[0].re;                                                      \
    ದತ್ತಾಂಶ[0].re = t[0].re + ದತ್ತಾಂಶ[0].im;                                         \
    ದತ್ತಾಂಶ[0].im = t[0].re - ದತ್ತಾಂಶ[0].im;                                         \
    ದತ್ತಾಂಶ[   0].re = MULT(fact[0], ದತ್ತಾಂಶ[   0].re);                              \
    ದತ್ತಾಂಶ[   0].im = MULT(fact[1], ದತ್ತಾಂಶ[   0].im);                              \
    ದತ್ತಾಂಶ[len4].re = MULT(fact[2], ದತ್ತಾಂಶ[len4].re);                              \
    ದತ್ತಾಂಶ[len4].im = MULT(fact[3], ದತ್ತಾಂಶ[len4].im);                              \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < len4; i++) {                                           \
        /* Separate even and odd FFTs */                                       \
        t[0].re = MULT(fact[4], (ದತ್ತಾಂಶ[i].re + ದತ್ತಾಂಶ[len2 - i].re));             \
        t[0].im = MULT(fact[5], (ದತ್ತಾಂಶ[i].im - ದತ್ತಾಂಶ[len2 - i].im));             \
        t[1].re = MULT(fact[6], (ದತ್ತಾಂಶ[i].im + ದತ್ತಾಂಶ[len2 - i].im));             \
        t[1].im = MULT(fact[7], (ದತ್ತಾಂಶ[i].re - ದತ್ತಾಂಶ[len2 - i].re));             \
                                                                               \
        /* Apply twiddle factors to the odd FFT and add to the even FFT */     \
        CMUL(t[2].re, t[2].im, t[1].re, t[1].im, tcos[i], tsin[i]);            \
                                                                               \
        ದತ್ತಾಂಶ[       i].re = t[0].re + t[2].re;                                 \
        ದತ್ತಾಂಶ[       i].im = t[2].im - t[0].im;                                 \
        ದತ್ತಾಂಶ[len2 - i].re = t[0].re - t[2].re;                                 \
        ದತ್ತಾಂಶ[len2 - i].im = t[2].im + t[0].im;                                 \
    }                                                                          \
                                                                               \
    ಆದರೆ (inv) {                                                                 \
        s->fn[0](&s->sub[0], _dst, ದತ್ತಾಂಶ, ಗಾತ್ರ(TXComplex));                   \
    } ಇಲ್ಲದಿದ್ದರೆ {                                                                   \
        /* Move [0].im to the last position, as convention requires */         \
        ದತ್ತಾಂಶ[len2].re = ದತ್ತಾಂಶ[0].im;                                            \
        ದತ್ತಾಂಶ[   0].im = ದತ್ತಾಂಶ[len2].im = 0;                                     \
    }                                                                          \
}                                                                              \
                                                                               \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು |       \
                  (inv ? FF_TX_INVERSE_ONLY : FF_TX_FORWARD_ONLY),             \
    .factors    = { 4, TX_ಗುಣಕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = 4,                                                           \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

DECL_RDFT(r2c,  0)
DECL_RDFT(c2r,  1)

#ವ್ಯಾಖ್ಯಾನಿಸು DECL_RDFT_HALF(n, ಬಹುಲಕ, mod2)                                          \
ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, ಶೂನ್ಯ *_dst,               \
                                        ಶೂನ್ಯ *_src, ptrdiff_t stride)          \
{                                                                              \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = s->len;                                                    \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = len >> 1;                                                 \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len4 = len >> 2;                                                 \
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ aligned_len4 = FFALIGN(len, 4)/4;                                \
    ಸ್ಥಿರಾಂಕ TXSample *fact = (ಶೂನ್ಯ *)s->ಘಾತಾಂಕ;                                     \
    ಸ್ಥಿರಾಂಕ TXSample *tcos = fact + 8;                                           \
    ಸ್ಥಿರಾಂಕ TXSample *tsin = tcos + aligned_len4;                                \
    TXComplex *ದತ್ತಾಂಶ = _dst;                                                    \
    TXSample *ಹೊರಹೋಗು = _dst; /* Half-complex is forward-only */                   \
    TXSample tmp_dc;                                                           \
    av_ಬಳಸದ TXSample tmp_mid;                                                \
    TXSample tmp[4];                                                           \
    TXComplex sf, sl;                                                          \
                                                                               \
    s->fn[0](&s->sub[0], _dst, _src, ಗಾತ್ರ(TXComplex));                       \
                                                                               \
    tmp_dc = ದತ್ತಾಂಶ[0].re;                                                       \
    ದತ್ತಾಂಶ[   0].re = tmp_dc + ದತ್ತಾಂಶ[0].im;                                       \
    tmp_dc        = tmp_dc - ದತ್ತಾಂಶ[0].im;                                       \
                                                                               \
    ದತ್ತಾಂಶ[   0].re = MULT(fact[0], ದತ್ತಾಂಶ[   0].re);                              \
    tmp_dc        = MULT(fact[1],        tmp_dc);                              \
    ದತ್ತಾಂಶ[len4].re = MULT(fact[2], ದತ್ತಾಂಶ[len4].re);                              \
                                                                               \
    ಆದರೆ (!mod2) {                                                               \
        ದತ್ತಾಂಶ[len4].im = MULT(fact[3], ದತ್ತಾಂಶ[len4].im);                          \
    } ಇಲ್ಲದಿದ್ದರೆ {                                                                   \
        sf = ದತ್ತಾಂಶ[len4];                                                       \
        sl = ದತ್ತಾಂಶ[len4 + 1];                                                   \
        ಆದರೆ (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        ಇಲ್ಲದಿದ್ದರೆ                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        ಆದರೆ (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_REAL) {                                      \
            tmp[3]  = tmp[1]*tcos[len4] - tmp[2]*tsin[len4];                   \
            tmp_mid = (tmp[0] - tmp[3]);                                       \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                               \
            tmp[3]  = tmp[1]*tsin[len4] + tmp[2]*tcos[len4];                   \
            tmp_mid = (tmp[0] + tmp[3]);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* NOTE: unrolling this breaks non-mod8 lengths */                         \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i <= len4; i++) {                                          \
        TXSample tmp[4];                                                       \
        TXComplex sf = ದತ್ತಾಂಶ[i];                                                \
        TXComplex sl = ದತ್ತಾಂಶ[len2 - i];                                         \
                                                                               \
        ಆದರೆ (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        ಇಲ್ಲದಿದ್ದರೆ                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
                                                                               \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        ಆದರೆ (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_REAL) {                                      \
            tmp[3]           = tmp[1]*tcos[i] - tmp[2]*tsin[i];                \
            ಹೊರಹೋಗು[i]           = (tmp[0] + tmp[3]);                              \
            ಹೊರಹೋಗು[len - i]     = (tmp[0] - tmp[3]);                              \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                               \
            tmp[3]           = tmp[1]*tsin[i] + tmp[2]*tcos[i];                \
            ಹೊರಹೋಗು[i - 1]       = (tmp[3] - tmp[0]);                              \
            ಹೊರಹೋಗು[len - i - 1] = (tmp[0] + tmp[3]);                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < (len4 + (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_IMAGINARY)); i++)       \
        ಹೊರಹೋಗು[len2 - i] = ಹೊರಹೋಗು[len - i];                                          \
                                                                               \
    ಆದರೆ (ಬಹುಲಕ == AV_TX_REAL_ಗಮ್ಯ_REAL) {                                          \
        ಹೊರಹೋಗು[len2] = tmp_dc;                                                    \
        ಆದರೆ (mod2)                                                              \
            ಹೊರಹೋಗು[len4 + 1] = tmp_mid * fact[5];                                 \
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (mod2) {                                                         \
        ಹೊರಹೋಗು[len4] = tmp_mid;                                                   \
    }                                                                          \
}                                                                              \
                                                                               \
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | ಬಹುಲಕ |                     \
                  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_FORWARD_ONLY,                     \
    .factors    = { 2 + 2*(!mod2), TX_ಗುಣಕ_ANY },                            \
    .nb_factors = 2,                                                           \
    .min_len    = 2 + 2*(!mod2),                                               \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ತಳ,                                             \
};

DECL_RDFT_HALF(r2r,      AV_TX_REAL_ಗಮ್ಯ_REAL,      0)
DECL_RDFT_HALF(r2r_mod2, AV_TX_REAL_ಗಮ್ಯ_REAL,      1)
DECL_RDFT_HALF(r2i,      AV_TX_REAL_ಗಮ್ಯ_IMAGINARY, 0)
DECL_RDFT_HALF(r2i_mod2, AV_TX_REAL_ಗಮ್ಯ_IMAGINARY, 1)

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_dct_init)(AVTXContext *s,
                                           ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                           ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;
    ದ್ವಿಗುಣ freq;
    TXSample *tab;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    ಆದರೆ (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, ಖಾಲಿ, len, inv, &rsc)))
        ಹಿಂತಿರುಗಿ ret;

    s->ಘಾತಾಂಕ = av_malloc((len/2)*3*ಗಾತ್ರ(TXSample));
    ಆದರೆ (!s->ಘಾತಾಂಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    tab = (TXSample *)s->ಘಾತಾಂಕ;

    freq = M_PI/(len*2);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
        tab[i] = RESCALE(ಕೋಜ್ಯಾ(i*freq)*(!inv + 1));

    ಆದರೆ (inv) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(0.5 / ಜ್ಯಾ((2*i + 1)*freq));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(ಕೋಜ್ಯಾ((len - 2*i - 1)*freq));
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_dctII)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                 ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = s->len;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = len >> 1;
    ಸ್ಥಿರಾಂಕ TXSample *ಘಾತಾಂಕ = (ಶೂನ್ಯ *)s->ಘಾತಾಂಕ;
    TXSample ಮುಂದಿನ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    int64_t tmp1, tmp2;
#ಇಲ್ಲದಿದ್ದರೆ
    TXSample tmp1, tmp2;
#ಆದರೆ_ಅಂತ್ಯ

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len2; i++) {
        TXSample in1 = src[i];
        TXSample in2 = src[len - i - 1];
        TXSample s    = ಘಾತಾಂಕ[len + i];

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
        tmp1 = in1 + in2;
        tmp2 = in1 - in2;

        tmp1 >>= 1;
        tmp2 *= s;

        tmp2 = (tmp2 + 0x40000000) >> 31;
#ಇಲ್ಲದಿದ್ದರೆ
        tmp1 = (in1 + in2)*0.5;
        tmp2 = (in1 - in2)*s;
#ಆದರೆ_ಅಂತ್ಯ

        src[i]           = tmp1 + tmp2;
        src[len - i - 1] = tmp1 - tmp2;
    }

    s->fn[0](&s->sub[0], dst, src, ಗಾತ್ರ(TXComplex));

    ಮುಂದಿನ = dst[len];

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = len - 2; i > 0; i -= 2) {
        TXSample tmp;

        CMUL(tmp, dst[i], ಘಾತಾಂಕ[len - i], ಘಾತಾಂಕ[i], dst[i + 0], dst[i + 1]);

        dst[i + 1] = ಮುಂದಿನ;

        ಮುಂದಿನ += tmp;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    tmp1 = ((int64_t)ಘಾತಾಂಕ[0]) * ((int64_t)dst[0]);
    dst[0] = (tmp1 + 0x40000000) >> 31;
#ಇಲ್ಲದಿದ್ದರೆ
    dst[0] = ಘಾತಾಂಕ[0] * dst[0];
#ಆದರೆ_ಅಂತ್ಯ
    dst[1] = ಮುಂದಿನ;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_dctIII)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                  ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = s->len;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len2 = len >> 1;
    ಸ್ಥಿರಾಂಕ TXSample *ಘಾತಾಂಕ = (ಶೂನ್ಯ *)s->ಘಾತಾಂಕ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
    int64_t  tmp1, tmp2 = src[len - 1];
    tmp2 = (2*tmp2 + 0x40000000) >> 31;
#ಇಲ್ಲದಿದ್ದರೆ
    TXSample tmp1, tmp2 = 2*src[len - 1];
#ಆದರೆ_ಅಂತ್ಯ

    src[len] = tmp2;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = len - 2; i >= 2; i -= 2) {
        TXSample val1 = src[i - 0];
        TXSample val2 = src[i - 1] - src[i + 1];

        CMUL(src[i + 1], src[i], ಘಾತಾಂಕ[len - i], ಘಾತಾಂಕ[i], val1, val2);
    }

    s->fn[0](&s->sub[0], dst, src, ಗಾತ್ರ(ದಶಮಾಂಶ));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len2; i++) {
        TXSample in1 = dst[i];
        TXSample in2 = dst[len - i - 1];
        TXSample c   = ಘಾತಾಂಕ[len + i];

        tmp1 = in1 + in2;
        tmp2 = in1 - in2;
        tmp2 *= c;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TX_INT32
        tmp2 = (tmp2 + 0x40000000) >> 31;
#ಆದರೆ_ಅಂತ್ಯ

        dst[i]            = tmp1 + tmp2;
        dst[len - i - 1]  = tmp1 - tmp2;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_dctII_def) = {
    .name       = TX_NAME_STR("dctII"),
    .function   = TX_NAME(ff_tx_dctII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_dctIII_def) = {
    .name       = TX_NAME_STR("dctIII"),
    .function   = TX_NAME(ff_tx_dctIII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ TX_NAME(ff_tx_dcstI_init)(AVTXContext *s,
                                             ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                             uint64_t flags,
                                             FFTXCodeletOptions *opts,
                                             ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                             ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    ಆದರೆ (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    /* We want a half-complex RDFT */
    flags |= cd->type == TX_TYPE(DCT_I) ? AV_TX_REAL_ಗಮ್ಯ_REAL :
                                          AV_TX_REAL_ಗಮ್ಯ_IMAGINARY;

    ಆದರೆ ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, ಖಾಲಿ,
                                (len - 1 + 2*(cd->type == TX_TYPE(DST_I)))*2,
                                0, &rsc)))
        ಹಿಂತಿರುಗಿ ret;

    s->tmp = av_mallocz((len + 1)*2*ಗಾತ್ರ(TXSample));
    ಆದರೆ (!s->tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_dctI)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = s->len - 1;
    TXSample *tmp = (TXSample *)s->tmp;

    stride /= ಗಾತ್ರ(TXSample);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
        tmp[i] = tmp[2*len - i] = src[i * stride];

    tmp[len] = src[len * stride]; /*ಮಧ್ಯ*/

    s->fn[0](&s->sub[0], dst, tmp, ಗಾತ್ರ(TXSample));
}

ಸ್ಥಿರ ಶೂನ್ಯ TX_NAME(ff_tx_dstI)(AVTXContext *s, ಶೂನ್ಯ *_dst,
                                ಶೂನ್ಯ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = s->len + 1;
    TXSample *tmp = (ಶೂನ್ಯ *)s->tmp;

    stride /= ಗಾತ್ರ(TXSample);

    tmp[0] = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < len; i++) {
        TXSample a = src[(i - 1) * stride];
        tmp[i] = -a;
        tmp[2*len - i] = a;
    }

    tmp[len] = 0; /* i == n, Nyquist */

    s->fn[0](&s->sub[0], dst, tmp, ಗಾತ್ರ(ದಶಮಾಂಶ));
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_dctI_def) = {
    .name       = TX_NAME_STR("dctI"),
    .function   = TX_NAME(ff_tx_dctI),
    .type       = TX_TYPE(DCT_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet TX_NAME(ff_tx_dstI_def) = {
    .name       = TX_NAME_STR("dstI"),
    .function   = TX_NAME(ff_tx_dstI),
    .type       = TX_TYPE(DST_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು,
    .factors    = { 2, TX_ಗುಣಕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ತಳ,
};

ಪೂರ್ಣಾಂಕ TX_TAB(ff_tx_mdct_gen_exp)(AVTXContext *s, ಪೂರ್ಣಾಂಕ *pre_tab)
{
    ಪೂರ್ಣಾಂಕ off = 0;
    ಪೂರ್ಣಾಂಕ len4 = s->len >> 1;
    ದ್ವಿಗುಣ scale = s->scale_d;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ theta = (scale < 0 ? len4 : 0) + 1.0/8.0;
    size_t alloc = pre_tab ? 2*len4 : len4;

    ಆದರೆ (!(s->ಘಾತಾಂಕ = av_malloc_array(alloc, ಗಾತ್ರ(*s->ಘಾತಾಂಕ))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    scale = ವರ್ಗಮೂಲ(fabs(scale));

    ಆದರೆ (pre_tab)
        off = len4;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++) {
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ alpha = M_PI_2 * (i + theta) / len4;
        s->ಘಾತಾಂಕ[off + i] = (TXComplex){ RESCALE(ಕೋಜ್ಯಾ(alpha) * scale),
                                       RESCALE(ಜ್ಯಾ(alpha) * scale) };
    }

    ಆದರೆ (pre_tab)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len4; i++)
            s->ಘಾತಾಂಕ[i] = s->ಘಾತಾಂಕ[len4 + pre_tab[i]];

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ FFTXCodelet * ಸ್ಥಿರಾಂಕ TX_NAME(ff_tx_codelet_list)[] = {
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
    &TX_NAME(ff_tx_mdct_inv_ತುಂಬಿದ_def),
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

    ಖಾಲಿ,
};
