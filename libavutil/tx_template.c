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

#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਾਰਣੀ_DEF(name, ਮਾਪ) \
    DECLARE_ALIGNED(32, TXSample, TX_TAB(ff_tx_tab_ ##name))[ਮਾਪ]

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_POW2_TABLES \
    SR_ਸਾਰਣੀ(8)        \
    SR_ਸਾਰਣੀ(16)       \
    SR_ਸਾਰਣੀ(32)       \
    SR_ਸਾਰਣੀ(64)       \
    SR_ਸਾਰਣੀ(128)      \
    SR_ਸਾਰਣੀ(256)      \
    SR_ਸਾਰਣੀ(512)      \
    SR_ਸਾਰਣੀ(1024)     \
    SR_ਸਾਰਣੀ(2048)     \
    SR_ਸਾਰਣੀ(4096)     \
    SR_ਸਾਰਣੀ(8192)     \
    SR_ਸਾਰਣੀ(16384)    \
    SR_ਸਾਰਣੀ(32768)    \
    SR_ਸਾਰਣੀ(65536)    \
    SR_ਸਾਰਣੀ(131072)   \

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_ਸਾਰਣੀ(len) \
    ਸਾਰਣੀ_DEF(len, len/4 + 1);
/* Power of two tables */
SR_POW2_TABLES
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SR_ਸਾਰਣੀ

/* Other factors' tables */
ਸਾਰਣੀ_DEF(53, 12);
ਸਾਰਣੀ_DEF( 7,  6);
ਸਾਰਣੀ_DEF( 9,  8);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFTab_Init_ਅੰਕੜੇ {
    ਖਾਲੀ (*func)(ਖਾਲੀ);
    ਪੂਰਨ factors[TX_MAX_SUB]; /* Must be sorted high -> low */
} FFTab_Init_ਅੰਕੜੇ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_ਸਾਰਣੀ(len)                                              \
ਸਥਿਰ av_cold ਖਾਲੀ TX_TAB(ff_tx_init_tab_ ##len)(ਖਾਲੀ)            \
{                                                                  \
    ਦੁੱਗਣਾ freq = 2*M_PI/len;                                      \
    TXSample *tab = TX_TAB(ff_tx_tab_ ##len);                      \
                                                                   \
    ਲਈ (ਪੂਰਨ i = 0; i < len/4; i++)                                \
        *tab++ = RESCALE(ਕੋਜੀਵਾ(i*freq));                             \
                                                                   \
    *tab = 0;                                                      \
}
SR_POW2_TABLES
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SR_ਸਾਰਣੀ

ਸਥਿਰ ਖਾਲੀ (*ਅਚਲ sr_tabs_init_funcs[])(ਖਾਲੀ) = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_ਸਾਰਣੀ(len) TX_TAB(ff_tx_init_tab_ ##len),
    SR_POW2_TABLES
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SR_ਸਾਰਣੀ
};

ਸਥਿਰ AVOnce sr_tabs_init_once[] = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_ਸਾਰਣੀ(len) AV_ONCE_INIT,
    SR_POW2_TABLES
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SR_ਸਾਰਣੀ
};

ਸਥਿਰ av_cold ਖਾਲੀ TX_TAB(ff_tx_init_tab_53)(ਖਾਲੀ)
{
    /* 5pt, doubled to eliminate AVX lane shuffles */
    TX_TAB(ff_tx_tab_53)[0] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[1] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[2] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[3] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[4] = RESCALE(ਜੀਵਾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[5] = RESCALE(ਜੀਵਾ(2 * M_PI /  5));
    TX_TAB(ff_tx_tab_53)[6] = RESCALE(ਜੀਵਾ(2 * M_PI / 10));
    TX_TAB(ff_tx_tab_53)[7] = RESCALE(ਜੀਵਾ(2 * M_PI / 10));

    /* 3pt */
    TX_TAB(ff_tx_tab_53)[ 8] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[ 9] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 12));
    TX_TAB(ff_tx_tab_53)[10] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  6));
    TX_TAB(ff_tx_tab_53)[11] = RESCALE(ਕੋਜੀਵਾ(8 * M_PI /  6));
}

ਸਥਿਰ av_cold ਖਾਲੀ TX_TAB(ff_tx_init_tab_7)(ਖਾਲੀ)
{
    TX_TAB(ff_tx_tab_7)[0] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[1] = RESCALE(ਜੀਵਾ(2 * M_PI /  7));
    TX_TAB(ff_tx_tab_7)[2] = RESCALE(ਜੀਵਾ(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[3] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 28));
    TX_TAB(ff_tx_tab_7)[4] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 14));
    TX_TAB(ff_tx_tab_7)[5] = RESCALE(ਜੀਵਾ(2 * M_PI / 14));
}

ਸਥਿਰ av_cold ਖਾਲੀ TX_TAB(ff_tx_init_tab_9)(ਖਾਲੀ)
{
    TX_TAB(ff_tx_tab_9)[0] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[1] = RESCALE(ਜੀਵਾ(2 * M_PI /  3));
    TX_TAB(ff_tx_tab_9)[2] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[3] = RESCALE(ਜੀਵਾ(2 * M_PI /  9));
    TX_TAB(ff_tx_tab_9)[4] = RESCALE(ਕੋਜੀਵਾ(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[5] = RESCALE(ਜੀਵਾ(2 * M_PI / 36));
    TX_TAB(ff_tx_tab_9)[6] = TX_TAB(ff_tx_tab_9)[2] + TX_TAB(ff_tx_tab_9)[5];
    TX_TAB(ff_tx_tab_9)[7] = TX_TAB(ff_tx_tab_9)[3] - TX_TAB(ff_tx_tab_9)[4];
}

ਸਥਿਰ ਅਚਲ FFTab_Init_ਅੰਕੜੇ nptwo_tabs_init_ਅੰਕੜੇ[] = {
    { TX_TAB(ff_tx_init_tab_53),      { 15, 5, 3 } },
    { TX_TAB(ff_tx_init_tab_9),       {  9 }       },
    { TX_TAB(ff_tx_init_tab_7),       {  7 }       },
};

ਸਥਿਰ AVOnce nptwo_tabs_init_once[] = {
    AV_ONCE_INIT,
    AV_ONCE_INIT,
    AV_ONCE_INIT,
};

av_cold ਖਾਲੀ TX_TAB(ff_tx_init_tabs)(ਪੂਰਨ len)
{
    ਪੂਰਨ ਗੁਣਕ_2 = ff_ctz(len);
    ਜੇ (ਗੁਣਕ_2) {
        ਪੂਰਨ idx = ਗੁਣਕ_2 - 3;
        ਲਈ (ਪੂਰਨ i = 0; i <= idx; i++)
            ff_thread_once(&sr_tabs_init_once[i],
                            sr_tabs_init_funcs[i]);
        len >>= ਗੁਣਕ_2;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(nptwo_tabs_init_ਅੰਕੜੇ); i++) {
        ਪੂਰਨ f, f_idx = 0;

        ਜੇ (len <= 1)
            ਵਾਪਸ;

        ਜਦੋਂ ((f = nptwo_tabs_init_ਅੰਕੜੇ[i].factors[f_idx++])) {
            ਜੇ (f % len)
                ਜਾਰੀ;

            ff_thread_once(&nptwo_tabs_init_once[i],
                            nptwo_tabs_init_ਅੰਕੜੇ[i].func);
            len /= f;
            ਰੋਕੋ;
        }
    }
}

ਸਥਿਰ av_always_inline ਖਾਲੀ fft3(TXComplex *ਬਾਹਰਲਾ, TXComplex *ਵਿੱਚ_2,
                                  ptrdiff_t stride)
{
    TXComplex tmp[3];
    ਅਚਲ TXSample *tab = TX_TAB(ff_tx_tab_53);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    int64_t mtmp[4];
#ਜੇ_ਅੰਤ

    tmp[0] = ਵਿੱਚ_2[0];
    BF(tmp[1].re, tmp[2].im, ਵਿੱਚ_2[1].im, ਵਿੱਚ_2[2].im);
    BF(tmp[1].im, tmp[2].re, ਵਿੱਚ_2[1].re, ਵਿੱਚ_2[2].re);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    ਬਾਹਰਲਾ[0*stride].re = (int64_t)tmp[0].re + tmp[2].re;
    ਬਾਹਰਲਾ[0*stride].im = (int64_t)tmp[0].im + tmp[2].im;
    mtmp[0] = (int64_t)tab[ 8] * tmp[1].re;
    mtmp[1] = (int64_t)tab[ 9] * tmp[1].im;
    mtmp[2] = (int64_t)tab[10] * tmp[2].re;
    mtmp[3] = (int64_t)tab[10] * tmp[2].im;
    ਬਾਹਰਲਾ[1*stride].re = tmp[0].re - (mtmp[2] + mtmp[0] + 0x40000000 >> 31);
    ਬਾਹਰਲਾ[1*stride].im = tmp[0].im - (mtmp[3] - mtmp[1] + 0x40000000 >> 31);
    ਬਾਹਰਲਾ[2*stride].re = tmp[0].re - (mtmp[2] - mtmp[0] + 0x40000000 >> 31);
    ਬਾਹਰਲਾ[2*stride].im = tmp[0].im - (mtmp[3] + mtmp[1] + 0x40000000 >> 31);
#ਨਹੀਂਤਾਂ
    ਬਾਹਰਲਾ[0*stride].re = tmp[0].re + tmp[2].re;
    ਬਾਹਰਲਾ[0*stride].im = tmp[0].im + tmp[2].im;
    tmp[1].re = tab[ 8] * tmp[1].re;
    tmp[1].im = tab[ 9] * tmp[1].im;
    tmp[2].re = tab[10] * tmp[2].re;
    tmp[2].im = tab[10] * tmp[2].im;
    ਬਾਹਰਲਾ[1*stride].re = tmp[0].re - tmp[2].re + tmp[1].re;
    ਬਾਹਰਲਾ[1*stride].im = tmp[0].im - tmp[2].im - tmp[1].im;
    ਬਾਹਰਲਾ[2*stride].re = tmp[0].re - tmp[2].re - tmp[1].re;
    ਬਾਹਰਲਾ[2*stride].im = tmp[0].im - tmp[2].im + tmp[1].im;
#ਜੇ_ਅੰਤ
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_FFT5(NAME, D0, D1, D2, D3, D4)                         \
ਸਥਿਰ av_always_inline ਖਾਲੀ NAME(TXComplex *ਬਾਹਰਲਾ, TXComplex *ਵਿੱਚ_2,    \
                                  ptrdiff_t stride)                 \
{                                                                   \
    TXComplex dc, z0[4], t[6];                                      \
    ਅਚਲ TXSample *tab = TX_TAB(ff_tx_tab_53);                     \
                                                                    \
    dc = ਵਿੱਚ_2[0];                                                     \
    BF(t[1].im, t[0].re, ਵਿੱਚ_2[1].re, ਵਿੱਚ_2[4].re);                       \
    BF(t[1].re, t[0].im, ਵਿੱਚ_2[1].im, ਵਿੱਚ_2[4].im);                       \
    BF(t[3].im, t[2].re, ਵਿੱਚ_2[2].re, ਵਿੱਚ_2[3].re);                       \
    BF(t[3].re, t[2].im, ਵਿੱਚ_2[2].im, ਵਿੱਚ_2[3].im);                       \
                                                                    \
    ਬਾਹਰਲਾ[D0*stride].re = dc.re + (TXUSample)t[0].re + t[2].re;        \
    ਬਾਹਰਲਾ[D0*stride].im = dc.im + (TXUSample)t[0].im + t[2].im;        \
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
    ਬਾਹਰਲਾ[D1*stride].re = dc.re + (TXUSample)z0[3].re;                 \
    ਬਾਹਰਲਾ[D1*stride].im = dc.im + (TXUSample)z0[0].im;                 \
    ਬਾਹਰਲਾ[D2*stride].re = dc.re + (TXUSample)z0[2].re;                 \
    ਬਾਹਰਲਾ[D2*stride].im = dc.im + (TXUSample)z0[1].im;                 \
    ਬਾਹਰਲਾ[D3*stride].re = dc.re + (TXUSample)z0[1].re;                 \
    ਬਾਹਰਲਾ[D3*stride].im = dc.im + (TXUSample)z0[2].im;                 \
    ਬਾਹਰਲਾ[D4*stride].re = dc.re + (TXUSample)z0[0].re;                 \
    ਬਾਹਰਲਾ[D4*stride].im = dc.im + (TXUSample)z0[3].im;                 \
}

DECL_FFT5(fft5,     0,  1,  2,  3,  4)
DECL_FFT5(fft5_m1,  0,  6, 12,  3,  9)
DECL_FFT5(fft5_m2, 10,  1,  7, 13,  4)
DECL_FFT5(fft5_m3,  5, 11,  2,  8, 14)

ਸਥਿਰ av_always_inline ਖਾਲੀ fft7(TXComplex *ਬਾਹਰਲਾ, TXComplex *ਵਿੱਚ_2,
                                  ptrdiff_t stride)
{
    TXComplex dc, t[6], z[3];
    ਅਚਲ TXComplex *tab = (ਅਚਲ TXComplex *)TX_TAB(ff_tx_tab_7);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    int64_t mtmp[12];
#ਜੇ_ਅੰਤ

    dc = ਵਿੱਚ_2[0];
    BF(t[1].re, t[0].re, ਵਿੱਚ_2[1].re, ਵਿੱਚ_2[6].re);
    BF(t[1].im, t[0].im, ਵਿੱਚ_2[1].im, ਵਿੱਚ_2[6].im);
    BF(t[3].re, t[2].re, ਵਿੱਚ_2[2].re, ਵਿੱਚ_2[5].re);
    BF(t[3].im, t[2].im, ਵਿੱਚ_2[2].im, ਵਿੱਚ_2[5].im);
    BF(t[5].re, t[4].re, ਵਿੱਚ_2[3].re, ਵਿੱਚ_2[4].re);
    BF(t[5].im, t[4].im, ਵਿੱਚ_2[3].im, ਵਿੱਚ_2[4].im);

    ਬਾਹਰਲਾ[0*stride].re = dc.re + t[0].re + t[2].re + t[4].re;
    ਬਾਹਰਲਾ[0*stride].im = dc.im + t[0].im + t[2].im + t[4].im;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32 /* NOTE: it's possible to do this with 16 mults but 72 adds */
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
#ਨਹੀਂਤਾਂ
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
#ਜੇ_ਅੰਤ

    BF(t[1].re, z[0].re, z[0].re, t[4].re);
    BF(t[3].re, z[1].re, z[1].re, t[2].re);
    BF(t[5].re, z[2].re, z[2].re, t[0].re);
    BF(t[1].im, z[0].im, z[0].im, t[0].im);
    BF(t[3].im, z[1].im, z[1].im, t[2].im);
    BF(t[5].im, z[2].im, z[2].im, t[4].im);

    ਬਾਹਰਲਾ[1*stride].re = dc.re + z[0].re;
    ਬਾਹਰਲਾ[1*stride].im = dc.im + t[1].im;
    ਬਾਹਰਲਾ[2*stride].re = dc.re + t[3].re;
    ਬਾਹਰਲਾ[2*stride].im = dc.im + z[1].im;
    ਬਾਹਰਲਾ[3*stride].re = dc.re + z[2].re;
    ਬਾਹਰਲਾ[3*stride].im = dc.im + t[5].im;
    ਬਾਹਰਲਾ[4*stride].re = dc.re + t[5].re;
    ਬਾਹਰਲਾ[4*stride].im = dc.im + z[2].im;
    ਬਾਹਰਲਾ[5*stride].re = dc.re + z[1].re;
    ਬਾਹਰਲਾ[5*stride].im = dc.im + t[3].im;
    ਬਾਹਰਲਾ[6*stride].re = dc.re + t[1].re;
    ਬਾਹਰਲਾ[6*stride].im = dc.im + z[0].im;
}

ਸਥਿਰ av_always_inline ਖਾਲੀ fft9(TXComplex *ਬਾਹਰਲਾ, TXComplex *ਵਿੱਚ_2,
                                  ptrdiff_t stride)
{
    ਅਚਲ TXComplex *tab = (ਅਚਲ TXComplex *)TX_TAB(ff_tx_tab_9);
    TXComplex dc, t[16], w[4], x[5], y[5], z[2];
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    int64_t mtmp[12];
#ਜੇ_ਅੰਤ

    dc = ਵਿੱਚ_2[0];
    BF(t[1].re, t[0].re, ਵਿੱਚ_2[1].re, ਵਿੱਚ_2[8].re);
    BF(t[1].im, t[0].im, ਵਿੱਚ_2[1].im, ਵਿੱਚ_2[8].im);
    BF(t[3].re, t[2].re, ਵਿੱਚ_2[2].re, ਵਿੱਚ_2[7].re);
    BF(t[3].im, t[2].im, ਵਿੱਚ_2[2].im, ਵਿੱਚ_2[7].im);
    BF(t[5].re, t[4].re, ਵਿੱਚ_2[3].re, ਵਿੱਚ_2[6].re);
    BF(t[5].im, t[4].im, ਵਿੱਚ_2[3].im, ਵਿੱਚ_2[6].im);
    BF(t[7].re, t[6].re, ਵਿੱਚ_2[4].re, ਵਿੱਚ_2[5].re);
    BF(t[7].im, t[6].im, ਵਿੱਚ_2[4].im, ਵਿੱਚ_2[5].im);

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

    ਬਾਹਰਲਾ[0*stride].re = z[0].re + z[1].re;
    ਬਾਹਰਲਾ[0*stride].im = z[0].im + z[1].im;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
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
    z[0].re = ਵਿੱਚ_2[0].re + (int32_t)mtmp[2];
    z[0].im = ਵਿੱਚ_2[0].im + (int32_t)mtmp[3];

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

#ਨਹੀਂਤਾਂ
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
#ਜੇ_ਅੰਤ

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

    ਬਾਹਰਲਾ[1*stride] = (TXComplex){ x[1].re + y[1].im, x[1].im - y[1].re };
    ਬਾਹਰਲਾ[2*stride] = (TXComplex){ x[2].re + y[2].im, x[2].im - y[2].re };
    ਬਾਹਰਲਾ[3*stride] = (TXComplex){ x[3].re + y[3].im, x[3].im - y[3].re };
    ਬਾਹਰਲਾ[4*stride] = (TXComplex){ x[4].re + y[4].im, x[4].im - y[4].re };
    ਬਾਹਰਲਾ[5*stride] = (TXComplex){ x[4].re - y[4].im, x[4].im + y[4].re };
    ਬਾਹਰਲਾ[6*stride] = (TXComplex){ x[3].re - y[3].im, x[3].im + y[3].re };
    ਬਾਹਰਲਾ[7*stride] = (TXComplex){ x[2].re - y[2].im, x[2].im + y[2].re };
    ਬਾਹਰਲਾ[8*stride] = (TXComplex){ x[1].re - y[1].im, x[1].im + y[1].re };
}

ਸਥਿਰ av_always_inline ਖਾਲੀ fft15(TXComplex *ਬਾਹਰਲਾ, TXComplex *ਵਿੱਚ_2,
                                   ptrdiff_t stride)
{
    TXComplex tmp[15];

    ਲਈ (ਪੂਰਨ i = 0; i < 5; i++)
        fft3(tmp + i, ਵਿੱਚ_2 + i*3, 5);

    fft5_m1(ਬਾਹਰਲਾ, tmp +  0, stride);
    fft5_m2(ਬਾਹਰਲਾ, tmp +  5, stride);
    fft5_m3(ਬਾਹਰਲਾ, tmp + 10, stride);
}

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_ਗੁਣਕ_init)(AVTXContext *s,
                                                  ਅਚਲ FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  ਪੂਰਨ len, ਪੂਰਨ inv,
                                                  ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret = 0;
    TX_TAB(ff_tx_init_tabs)(len);

    ਜੇ (len == 15)
        ret = ff_tx_gen_pfa_ਨਿਵੇਸ਼_map(s, opts, 3, 5);
    ਨਹੀਂਤਾਂ ਜੇ (flags & FF_TX_PRESHUFFLE)
        ret = ff_tx_gen_default_map(s, opts);

    ਵਾਪਸ ret;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_ਗੁਣਕ_S(n)                                                       \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft##n)(AVTXContext *s, ਖਾਲੀ *dst,                   \
                                  ਖਾਲੀ *src, ptrdiff_t stride)                 \
{                                                                              \
    fft##n((TXComplex *)dst, (TXComplex *)src, stride / ਆਕਾਰ(TXComplex));    \
}                                                                              \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = {                    \
    .name       = TX_NAME_STR("fft" #n "_ns"),                                 \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ |                         \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,                          \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_ਗੁਣਕ_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_ਗੁਣਕ_F(n)                                                       \
DECL_ਗੁਣਕ_S(n)                                                               \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft##n##_fwd_def) = {                   \
    .name       = TX_NAME_STR("fft" #n "_fwd"),                                \
    .function   = TX_NAME(ff_tx_fft##n),                                       \
    .type       = TX_TYPE(FFT),                                                \
    .flags      = AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ |                         \
                  AV_TX_UNALIGNED | FF_TX_FORWARD_ONLY,                        \
    .factors[0] = n,                                                           \
    .nb_factors = 1,                                                           \
    .min_len    = n,                                                           \
    .max_len    = n,                                                           \
    .init       = TX_NAME(ff_tx_fft_ਗੁਣਕ_init),                              \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

DECL_ਗੁਣਕ_F(3)
DECL_ਗੁਣਕ_F(5)
DECL_ਗੁਣਕ_F(7)
DECL_ਗੁਣਕ_F(9)
DECL_ਗੁਣਕ_S(15)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTERFLIES(a0, a1, a2, a3)            \
    ਕਰੋ {                                       \
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
    } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSFORM(a0, a1, a2, a3, wre, wim)    \
    ਕਰੋ {                                       \
        CMUL(t1, t2, a2.re, a2.im, wre, -wim); \
        CMUL(t5, t6, a3.re, a3.im, wre,  wim); \
        BUTTERFLIES(a0, a1, a2, a3);           \
    } ਜਦੋਂ (0)

/* z[0...8n-1], w[1...2n-1] */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ TX_NAME(ff_tx_fft_sr_combine)(TXComplex *z,
                                                 ਅਚਲ TXSample *ਕੋਜੀਵਾ, ਪੂਰਨ len)
{
    ਪੂਰਨ o1 = 2*len;
    ਪੂਰਨ o2 = 4*len;
    ਪੂਰਨ o3 = 6*len;
    ਅਚਲ TXSample *wim = ਕੋਜੀਵਾ + o1 - 7;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;

    ਲਈ (ਪੂਰਨ i = 0; i < len; i += 4) {
        TRANSFORM(z[0], z[o1 + 0], z[o2 + 0], z[o3 + 0], ਕੋਜੀਵਾ[0], wim[7]);
        TRANSFORM(z[2], z[o1 + 2], z[o2 + 2], z[o3 + 2], ਕੋਜੀਵਾ[2], wim[5]);
        TRANSFORM(z[4], z[o1 + 4], z[o2 + 4], z[o3 + 4], ਕੋਜੀਵਾ[4], wim[3]);
        TRANSFORM(z[6], z[o1 + 6], z[o2 + 6], z[o3 + 6], ਕੋਜੀਵਾ[6], wim[1]);

        TRANSFORM(z[1], z[o1 + 1], z[o2 + 1], z[o3 + 1], ਕੋਜੀਵਾ[1], wim[6]);
        TRANSFORM(z[3], z[o1 + 3], z[o2 + 3], z[o3 + 3], ਕੋਜੀਵਾ[3], wim[4]);
        TRANSFORM(z[5], z[o1 + 5], z[o2 + 5], z[o3 + 5], ਕੋਜੀਵਾ[5], wim[2]);
        TRANSFORM(z[7], z[o1 + 7], z[o2 + 7], z[o3 + 7], ਕੋਜੀਵਾ[7], wim[0]);

        z   += 2*4;
        ਕੋਜੀਵਾ += 2*4;
        wim -= 2*4;
    }
}

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_sr_codelet_init)(AVTXContext *s,
                                                      ਅਚਲ FFTXCodelet *cd,
                                                      uint64_t flags,
                                                      FFTXCodeletOptions *opts,
                                                      ਪੂਰਨ len, ਪੂਰਨ inv,
                                                      ਅਚਲ ਖਾਲੀ *scale)
{
    TX_TAB(ff_tx_init_tabs)(len);
    ਵਾਪਸ ff_tx_gen_ptwo_revtab(s, opts);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_SR_CODELET_DEF(n)                              \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft##n##_ns_def) = { \
    .name       = TX_NAME_STR("fft" #n "_ns"),              \
    .function   = TX_NAME(ff_tx_fft##n##_ns),               \
    .type       = TX_TYPE(FFT),                             \
    .flags      = FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | AV_TX_INPLACE |      \
                  AV_TX_UNALIGNED | FF_TX_PRESHUFFLE,       \
    .factors[0] = 2,                                        \
    .nb_factors = 1,                                        \
    .min_len    = n,                                        \
    .max_len    = n,                                        \
    .init       = TX_NAME(ff_tx_fft_sr_codelet_init),       \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                      \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                          \
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_SR_CODELET(n, n2, n4)                                    \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft##n##_ns)(AVTXContext *s, ਖਾਲੀ *_dst,    \
                                        ਖਾਲੀ *_src, ptrdiff_t stride) \
{                                                                     \
    TXComplex *src = _src;                                            \
    TXComplex *dst = _dst;                                            \
    ਅਚਲ TXSample *ਕੋਜੀਵਾ = TX_TAB(ff_tx_tab_##n);                      \
                                                                      \
    TX_NAME(ff_tx_fft##n2##_ns)(s, dst,        src,        stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*2, src + n4*2, stride);   \
    TX_NAME(ff_tx_fft##n4##_ns)(s, dst + n4*3, src + n4*3, stride);   \
    TX_NAME(ff_tx_fft_sr_combine)(dst, ਕੋਜੀਵਾ, n4 >> 1);                 \
}                                                                     \
                                                                      \
DECL_SR_CODELET_DEF(n)

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft2_ns)(AVTXContext *s, ਖਾਲੀ *_dst,
                                   ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;

    BF(tmp.re, dst[0].re, src[0].re, src[1].re);
    BF(tmp.im, dst[0].im, src[0].im, src[1].im);
    dst[1] = tmp;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft4_ns)(AVTXContext *s, ਖਾਲੀ *_dst,
                                   ਖਾਲੀ *_src, ptrdiff_t stride)
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

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft8_ns)(AVTXContext *s, ਖਾਲੀ *_dst,
                                   ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    ਅਚਲ TXSample ਕੋਜੀਵਾ = TX_TAB(ff_tx_tab_8)[1];

    TX_NAME(ff_tx_fft4_ns)(s, dst, src, stride);

    BF(t1, dst[5].re, src[4].re, -src[5].re);
    BF(t2, dst[5].im, src[4].im, -src[5].im);
    BF(t5, dst[7].re, src[6].re, -src[7].re);
    BF(t6, dst[7].im, src[6].im, -src[7].im);

    BUTTERFLIES(dst[0], dst[2], dst[4], dst[6]);
    TRANSFORM(dst[1], dst[3], dst[5], dst[7], ਕੋਜੀਵਾ, ਕੋਜੀਵਾ);
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft16_ns)(AVTXContext *s, ਖਾਲੀ *_dst,
                                    ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ਅਚਲ TXSample *ਕੋਜੀਵਾ = TX_TAB(ff_tx_tab_16);

    TXUSample t1, t2, t3, t4, t5, t6, r0, i0, r1, i1;
    TXSample cos_16_1 = ਕੋਜੀਵਾ[1];
    TXSample cos_16_2 = ਕੋਜੀਵਾ[2];
    TXSample cos_16_3 = ਕੋਜੀਵਾ[3];

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

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_init)(AVTXContext *s,
                                           ਅਚਲ FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           ਪੂਰਨ len, ਪੂਰਨ inv,
                                           ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    ਪੂਰਨ is_inplace = !!(flags & AV_TX_INPLACE);
    FFTXCodeletOptions sub_opts = {
        .map_dir = is_inplace ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len, inv, scale)))
        ਵਾਪਸ ret;

    ਜੇ (is_inplace && (ret = ff_tx_gen_inplace_map(s, len)))
        ਵਾਪਸ ret;

    ਵਾਪਸ 0;
}

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_inplace_small_init)(AVTXContext *s,
                                                         ਅਚਲ FFTXCodelet *cd,
                                                         uint64_t flags,
                                                         FFTXCodeletOptions *opts,
                                                         ਪੂਰਨ len, ਪੂਰਨ inv,
                                                         ਅਚਲ ਖਾਲੀ *scale)
{
    ਜੇ (!(s->tmp = av_malloc(len*ਆਕਾਰ(*s->tmp))))
        ਵਾਪਸ AVERROR(ENOMEM);
    flags &= ~AV_TX_INPLACE;
    ਵਾਪਸ TX_NAME(ff_tx_fft_init)(s, cd, flags, opts, len, inv, scale);
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft)(AVTXContext *s, ਖਾਲੀ *_dst,
                               ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst1 = s->flags & AV_TX_INPLACE ? s->tmp : _dst;
    TXComplex *dst2 = _dst;
    ਪੂਰਨ *map = s->sub[0].map;
    ਪੂਰਨ len = s->len;

    /* Compilers can't vectorize this anyway without assuming AVX2, which they
     * generally don't, at least without -march=native -mtune=native */
    ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
        dst1[i] = src[map[i]];

    s->fn[0](&s->sub[0], dst2, dst1, stride);
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft_inplace)(AVTXContext *s, ਖਾਲੀ *_dst,
                                       ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    TXComplex tmp;
    ਅਚਲ ਪੂਰਨ *map = s->sub->map;
    ਅਚਲ ਪੂਰਨ *inplace_idx = s->map;
    ਪੂਰਨ src_idx, dst_idx;

    src_idx = *inplace_idx++;
    ਕਰੋ {
        tmp = src[src_idx];
        dst_idx = map[src_idx];
        ਕਰੋ {
            FFSWAP(TXComplex, tmp, src[dst_idx]);
            dst_idx = map[dst_idx];
        } ਜਦੋਂ (dst_idx != src_idx); /* Can be > as well, but was less predictable */
        src[dst_idx] = tmp;
    } ਜਦੋਂ ((src_idx = *inplace_idx++));

    s->fn[0](&s->sub[0], dst, src, stride);
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_def) = {
    .name       = TX_NAME_STR("fft"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_inplace_small_def) = {
    .name       = TX_NAME_STR("fft_inplace_small"),
    .function   = TX_NAME(ff_tx_fft),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | AV_TX_INPLACE,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 65536,
    .init       = TX_NAME(ff_tx_fft_inplace_small_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ - 256,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_inplace_def) = {
    .name       = TX_NAME_STR("fft_inplace"),
    .function   = TX_NAME(ff_tx_fft_inplace),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | AV_TX_INPLACE,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ - 512,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_init_naive_small)(AVTXContext *s,
                                                       ਅਚਲ FFTXCodelet *cd,
                                                       uint64_t flags,
                                                       FFTXCodeletOptions *opts,
                                                       ਪੂਰਨ len, ਪੂਰਨ inv,
                                                       ਅਚਲ ਖਾਲੀ *scale)
{
    ਅਚਲ ਦੁੱਗਣਾ phase = s->inv ? 2.0*M_PI/len : -2.0*M_PI/len;

    ਜੇ (!(s->ਘਾਤਾਂਕ = av_malloc(len*len*ਆਕਾਰ(*s->ਘਾਤਾਂਕ))))
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (ਪੂਰਨ i = 0; i < len; i++) {
        ਲਈ (ਪੂਰਨ j = 0; j < len; j++) {
            ਅਚਲ ਦੁੱਗਣਾ ਗੁਣਕ = phase*i*j;
            s->ਘਾਤਾਂਕ[i*j] = (TXComplex){
                RESCALE(ਕੋਜੀਵਾ(ਗੁਣਕ)),
                RESCALE(ਜੀਵਾ(ਗੁਣਕ)),
            };
        }
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft_naive)(AVTXContext *s, ਖਾਲੀ *_dst, ਖਾਲੀ *_src,
                                     ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ਅਚਲ ਪੂਰਨ n = s->len;
    ਦੁੱਗਣਾ phase = s->inv ? 2.0*M_PI/n : -2.0*M_PI/n;

    stride /= ਆਕਾਰ(*dst);

    ਲਈ (ਪੂਰਨ i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        ਲਈ (ਪੂਰਨ j = 0; j < n; j++) {
            ਅਚਲ ਦੁੱਗਣਾ ਗੁਣਕ = phase*i*j;
            ਅਚਲ TXComplex mult = {
                RESCALE(ਕੋਜੀਵਾ(ਗੁਣਕ)),
                RESCALE(ਜੀਵਾ(ਗੁਣਕ)),
            };
            TXComplex res;
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft_naive_small)(AVTXContext *s, ਖਾਲੀ *_dst, ਖਾਲੀ *_src,
                                           ptrdiff_t stride)
{
    TXComplex *src = _src;
    TXComplex *dst = _dst;
    ਅਚਲ ਪੂਰਨ n = s->len;

    stride /= ਆਕਾਰ(*dst);

    ਲਈ (ਪੂਰਨ i = 0; i < n; i++) {
        TXComplex tmp = { 0 };
        ਲਈ (ਪੂਰਨ j = 0; j < n; j++) {
            TXComplex res;
            ਅਚਲ TXComplex mult = s->ਘਾਤਾਂਕ[i*j];
            CMUL3(res, src[j], mult);
            tmp.re += res.re;
            tmp.im += res.im;
        }
        dst[i*stride] = tmp;
    }
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_naive_small_def) = {
    .name       = TX_NAME_STR("fft_naive_small"),
    .function   = TX_NAME(ff_tx_fft_naive_small),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = 1024,
    .init       = TX_NAME(ff_tx_fft_init_naive_small),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN/2,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_naive_def) = {
    .name       = TX_NAME_STR("fft_naive"),
    .function   = TX_NAME(ff_tx_fft_naive),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .nb_factors = 1,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = ਨਿਰਾ,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_fft_pfa_init)(AVTXContext *s,
                                               ਅਚਲ FFTXCodelet *cd,
                                               uint64_t flags,
                                               FFTXCodeletOptions *opts,
                                               ਪੂਰਨ len, ਪੂਰਨ inv,
                                               ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret, *tmp, ps = flags & FF_TX_PRESHUFFLE;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };
    size_t extra_tmp_len = 0;
    ਪੂਰਨ len_list[TX_MAX_DECOMPOSITIONS];

    ਜੇ ((ret = ff_tx_decompose_ਲੰਮਾਈ(len_list, TX_TYPE(FFT), len, inv)) < 0)
        ਵਾਪਸ ret;

    /* Two iterations to test both orderings. */
    ਲਈ (ਪੂਰਨ i = 0; i < ret; i++) {
        ਪੂਰਨ len1 = len_list[i];
        ਪੂਰਨ len2 = len / len1;

        /* Our ptwo transforms don't support striding the output. */
        ਜੇ (len2 & (len2 - 1))
            FFSWAP(ਪੂਰਨ, len1, len2);

        ff_tx_clear_ctx(s);

        /* First transform */
        sub_opts.map_dir = FF_TX_MAP_GATHER;
        flags &= ~AV_TX_INPLACE;
        flags |=  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ;
        flags |=  FF_TX_PRESHUFFLE; /* This function handles the permute step */
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len1, inv, scale);

        ਜੇ (ret == AVERROR(ENOMEM)) {
            ਵਾਪਸ ret;
        } ਨਹੀਂਤਾਂ ਜੇ (ret < 0) { /* Try again without a preshuffle flag */
            flags &= ~FF_TX_PRESHUFFLE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len1, inv, scale);
            ਜੇ (ret == AVERROR(ENOMEM))
                ਵਾਪਸ ret;
            ਨਹੀਂਤਾਂ ਜੇ (ret < 0)
                ਜਾਰੀ;
        }

        /* Second transform. */
        sub_opts.map_dir = FF_TX_MAP_SCATTER;
        flags |=  FF_TX_PRESHUFFLE;
retry:
        flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ;
        flags |=  AV_TX_INPLACE;
        ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                               len2, inv, scale);

        ਜੇ (ret == AVERROR(ENOMEM)) {
            ਵਾਪਸ ret;
        } ਨਹੀਂਤਾਂ ਜੇ (ret < 0) { /* Try again with an out-of-place transform */
            flags |= FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ;
            flags &= ~AV_TX_INPLACE;
            ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                   len2, inv, scale);
            ਜੇ (ret == AVERROR(ENOMEM)) {
                ਵਾਪਸ ret;
            } ਨਹੀਂਤਾਂ ਜੇ (ret < 0) {
                ਜੇ (flags & FF_TX_PRESHUFFLE) { /* Retry again without a preshuf flag */
                    flags &= ~FF_TX_PRESHUFFLE;
                    ਜਾਓ retry;
                } ਨਹੀਂਤਾਂ {
                    ਜਾਰੀ;
                }
            }
        }

        /* Success */
        ਰੋਕੋ;
    }

    /* If nothing was successful, error out */
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    /* Generate PFA map */
    ਜੇ ((ret = ff_tx_gen_compound_mapping(s, opts, 0,
                                          s->sub[0].len, s->sub[1].len)))
        ਵਾਪਸ ret;

    ਜੇ (!(s->tmp = av_malloc(len*ਆਕਾਰ(*s->tmp))))
        ਵਾਪਸ AVERROR(ENOMEM);

    /* Flatten input map */
    tmp = (ਪੂਰਨ *)s->tmp;
    ਲਈ (ਪੂਰਨ k = 0; k < len; k += s->sub[0].len) {
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp, &s->map[k], s->sub[0].len*ਆਕਾਰ(*tmp));
        ਲਈ (ਪੂਰਨ i = 0; i < s->sub[0].len; i++)
            s->map[k + i] = tmp[s->sub[0].map[i]];
    }

    /* Only allocate extra temporary memory if we need it */
    ਜੇ (!(s->sub[1].flags & AV_TX_INPLACE))
        extra_tmp_len = len;
    ਨਹੀਂਤਾਂ ਜੇ (!ps)
        extra_tmp_len = s->sub[0].len;

    ਜੇ (extra_tmp_len && !(s->ਘਾਤਾਂਕ = av_malloc(extra_tmp_len*ਆਕਾਰ(*s->ਘਾਤਾਂਕ))))
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft_pfa)(AVTXContext *s, ਖਾਲੀ *ਬਾਹਰਲਾ_3,
                                   ਖਾਲੀ *ਵਿੱਚ_4, ptrdiff_t stride)
{
    ਅਚਲ ਪੂਰਨ n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ਅਚਲ ਪੂਰਨ *ਵਿੱਚ_map = s->map, *ਬਾਹਰਲਾ_map = ਵਿੱਚ_map + l;
    ਅਚਲ ਪੂਰਨ *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->ਘਾਤਾਂਕ;
    TXComplex *ਵਿੱਚ_2 = ਵਿੱਚ_4, *ਬਾਹਰਲਾ = ਬਾਹਰਲਾ_3;

    stride /= ਆਕਾਰ(*ਬਾਹਰਲਾ);

    ਲਈ (ਪੂਰਨ i = 0; i < m; i++) {
        ਲਈ (ਪੂਰਨ j = 0; j < n; j++)
            s->ਘਾਤਾਂਕ[j] = ਵਿੱਚ_2[ਵਿੱਚ_map[i*n + j]];
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], s->ਘਾਤਾਂਕ, m*ਆਕਾਰ(TXComplex));
    }

    ਲਈ (ਪੂਰਨ i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], ਆਕਾਰ(TXComplex));

    ਲਈ (ਪੂਰਨ i = 0; i < l; i++)
        ਬਾਹਰਲਾ[i*stride] = tmp1[ਬਾਹਰਲਾ_map[i]];
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_fft_pfa_ns)(AVTXContext *s, ਖਾਲੀ *ਬਾਹਰਲਾ_3,
                                      ਖਾਲੀ *ਵਿੱਚ_4, ptrdiff_t stride)
{
    ਅਚਲ ਪੂਰਨ n = s->sub[0].len, m = s->sub[1].len, l = s->len;
    ਅਚਲ ਪੂਰਨ *ਵਿੱਚ_map = s->map, *ਬਾਹਰਲਾ_map = ਵਿੱਚ_map + l;
    ਅਚਲ ਪੂਰਨ *sub_map = s->sub[1].map;
    TXComplex *tmp1 = s->sub[1].flags & AV_TX_INPLACE ? s->tmp : s->ਘਾਤਾਂਕ;
    TXComplex *ਵਿੱਚ_2 = ਵਿੱਚ_4, *ਬਾਹਰਲਾ = ਬਾਹਰਲਾ_3;

    stride /= ਆਕਾਰ(*ਬਾਹਰਲਾ);

    ਲਈ (ਪੂਰਨ i = 0; i < m; i++)
        s->fn[0](&s->sub[0], &s->tmp[sub_map[i]], &ਵਿੱਚ_2[i*n], m*ਆਕਾਰ(TXComplex));

    ਲਈ (ਪੂਰਨ i = 0; i < n; i++)
        s->fn[1](&s->sub[1], &tmp1[m*i], &s->tmp[m*i], ਆਕਾਰ(TXComplex));

    ਲਈ (ਪੂਰਨ i = 0; i < l; i++)
        ਬਾਹਰਲਾ[i*stride] = tmp1[ਬਾਹਰਲਾ_map[i]];
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_pfa_def) = {
    .name       = TX_NAME_STR("fft_pfa"),
    .function   = TX_NAME(ff_tx_fft_pfa),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors    = { 7, 5, 3, 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_fft_pfa_ns_def) = {
    .name       = TX_NAME_STR("fft_pfa_ns"),
    .function   = TX_NAME(ff_tx_fft_pfa_ns),
    .type       = TX_TYPE(FFT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ |
                  FF_TX_PRESHUFFLE,
    .factors    = { 7, 5, 3, 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2*3,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_fft_pfa_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_mdct_naive_init)(AVTXContext *s,
                                                  ਅਚਲ FFTXCodelet *cd,
                                                  uint64_t flags,
                                                  FFTXCodeletOptions *opts,
                                                  ਪੂਰਨ len, ਪੂਰਨ inv,
                                                  ਅਚਲ ਖਾਲੀ *scale)
{
    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_naive_fwd)(AVTXContext *s, ਖਾਲੀ *_dst,
                                          ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    ਦੁੱਗਣਾ scale = s->scale_d;
    ਪੂਰਨ len = s->len;
    ਅਚਲ ਦੁੱਗਣਾ phase = M_PI/(4.0*len);

    stride /= ਆਕਾਰ(*dst);

    ਲਈ (ਪੂਰਨ i = 0; i < len; i++) {
        ਦੁੱਗਣਾ ਜੋੜ = 0.0;
        ਲਈ (ਪੂਰਨ j = 0; j < len*2; j++) {
            ਪੂਰਨ a = (2*j + 1 + len) * (2*i + 1);
            ਜੋੜ += UNSCALE(src[j]) * ਕੋਜੀਵਾ(a * phase);
        }
        dst[i*stride] = RESCALE(ਜੋੜ*scale);
    }
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_naive_inv)(AVTXContext *s, ਖਾਲੀ *_dst,
                                          ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *src = _src;
    TXSample *dst = _dst;
    ਦੁੱਗਣਾ scale = s->scale_d;
    ਪੂਰਨ len = s->len >> 1;
    ਪੂਰਨ len2 = len*2;
    ਅਚਲ ਦੁੱਗਣਾ phase = M_PI/(4.0*len2);

    stride /= ਆਕਾਰ(*src);

    ਲਈ (ਪੂਰਨ i = 0; i < len; i++) {
        ਦੁੱਗਣਾ ਜੋੜ_d = 0.0;
        ਦੁੱਗਣਾ ਜੋੜ_u = 0.0;
        ਦੁੱਗਣਾ i_d = phase * (4*len  - 2*i - 1);
        ਦੁੱਗਣਾ i_u = phase * (3*len2 + 2*i + 1);
        ਲਈ (ਪੂਰਨ j = 0; j < len2; j++) {
            ਦੁੱਗਣਾ a = (2 * j + 1);
            ਦੁੱਗਣਾ a_d = ਕੋਜੀਵਾ(a * i_d);
            ਦੁੱਗਣਾ a_u = ਕੋਜੀਵਾ(a * i_u);
            ਦੁੱਗਣਾ val = UNSCALE(src[j*stride]);
            ਜੋੜ_d += a_d * val;
            ਜੋੜ_u += a_u * val;
        }
        dst[i +   0] = RESCALE( ਜੋੜ_d*scale);
        dst[i + len] = RESCALE(-ਜੋੜ_u*scale);
    }
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_naive_fwd_def) = {
    .name       = TX_NAME_STR("mdct_naive_fwd"),
    .function   = TX_NAME(ff_tx_mdct_naive_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY }, /* MDCTs need an even length */
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_naive_inv_def) = {
    .name       = TX_NAME_STR("mdct_naive_inv"),
    .function   = TX_NAME(ff_tx_mdct_naive_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_naive_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MIN,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_mdct_init)(AVTXContext *s,
                                            ਅਚਲ FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            ਪੂਰਨ len, ਪੂਰਨ inv,
                                            ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    FFTXCodeletOptions sub_opts = {
        .map_dir = !inv ? FF_TX_MAP_SCATTER : FF_TX_MAP_GATHER,
    };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* First try with an in-place transform */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale))) {
        flags &= ~FF_TX_PRESHUFFLE; /* Now try with a generic FFT */
        ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                    inv, scale)))
            ਵਾਪਸ ret;
    }

    s->map = av_malloc((len >> 1)*ਆਕਾਰ(*s->map));
    ਜੇ (!s->map)
        ਵਾਪਸ AVERROR(ENOMEM);

    /* If we need to preshuffle copy the map from the subcontext */
    ਜੇ (s->sub[0].flags & FF_TX_PRESHUFFLE) {
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(s->map, s->sub->map, (len >> 1)*ਆਕਾਰ(*s->map));
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ i = 0; i < len >> 1; i++)
            s->map[i] = i;
    }

    ਜੇ ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : ਨਿਰਾ)))
        ਵਾਪਸ ret;

    /* Saves a multiply in a hot path. */
    ਜੇ (inv)
        ਲਈ (ਪੂਰਨ i = 0; i < (s->len >> 1); i++)
            s->map[i] <<= 1;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_fwd)(AVTXContext *s, ਖਾਲੀ *_dst, ਖਾਲੀ *_src,
                                    ptrdiff_t stride)
{
    TXSample *src = _src, *dst = _dst;
    TXComplex *ਘਾਤਾਂਕ = s->ਘਾਤਾਂਕ, tmp, *z = _dst;
    ਅਚਲ ਪੂਰਨ len2 = s->len >> 1;
    ਅਚਲ ਪੂਰਨ len4 = s->len >> 2;
    ਅਚਲ ਪੂਰਨ len3 = len2 * 3;
    ਅਚਲ ਪੂਰਨ *sub_map = s->map;

    stride /= ਆਕਾਰ(*dst);

    ਲਈ (ਪੂਰਨ i = 0; i < len2; i++) { /* Folding and pre-reindexing */
        ਅਚਲ ਪੂਰਨ k = 2*i;
        ਅਚਲ ਪੂਰਨ idx = sub_map[i];
        ਜੇ (k < len2) {
            tmp.re = FOLD(-src[ len2 + k],  src[1*len2 - 1 - k]);
            tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);
        } ਨਹੀਂਤਾਂ {
            tmp.re = FOLD(-src[ len2 + k], -src[5*len2 - 1 - k]);
            tmp.im = FOLD( src[-len2 + k], -src[1*len3 - 1 - k]);
        }
        CMUL(z[idx].im, z[idx].re, tmp.re, tmp.im, ਘਾਤਾਂਕ[i].re, ਘਾਤਾਂਕ[i].im);
    }

    s->fn[0](&s->sub[0], z, z, ਆਕਾਰ(TXComplex));

    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++) {
        ਅਚਲ ਪੂਰਨ i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].re, z[i1].im };
        TXComplex src0 = { z[i0].re, z[i0].im };

        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,
             ਘਾਤਾਂਕ[i0].im, ਘਾਤਾਂਕ[i0].re);
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,
             ਘਾਤਾਂਕ[i1].im, ਘਾਤਾਂਕ[i1].re);
    }
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_inv)(AVTXContext *s, ਖਾਲੀ *_dst, ਖਾਲੀ *_src,
                                    ptrdiff_t stride)
{
    TXComplex *z = _dst, *ਘਾਤਾਂਕ = s->ਘਾਤਾਂਕ;
    ਅਚਲ TXSample *src = _src, *in1, *in2;
    ਅਚਲ ਪੂਰਨ len2 = s->len >> 1;
    ਅਚਲ ਪੂਰਨ len4 = s->len >> 2;
    ਅਚਲ ਪੂਰਨ *sub_map = s->map;

    stride /= ਆਕਾਰ(*src);
    in1 = src;
    in2 = src + ((len2*2) - 1) * stride;

    ਲਈ (ਪੂਰਨ i = 0; i < len2; i++) {
        ਪੂਰਨ k = sub_map[i];
        TXComplex tmp = { in2[-k*stride], in1[k*stride] };
        CMUL3(z[i], tmp, ਘਾਤਾਂਕ[i]);
    }

    s->fn[0](&s->sub[0], z, z, ਆਕਾਰ(TXComplex));

    ਘਾਤਾਂਕ += len2;
    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++) {
        ਅਚਲ ਪੂਰਨ i0 = len4 + i, i1 = len4 - i - 1;
        TXComplex src1 = { z[i1].im, z[i1].re };
        TXComplex src0 = { z[i0].im, z[i0].re };

        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, ਘਾਤਾਂਕ[i1].im, ਘਾਤਾਂਕ[i1].re);
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, ਘਾਤਾਂਕ[i0].im, ਘਾਤਾਂਕ[i0].re);
    }
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_fwd_def) = {
    .name       = TX_NAME_STR("mdct_fwd"),
    .function   = TX_NAME(ff_tx_mdct_fwd),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_inv_def) = {
    .name       = TX_NAME_STR("mdct_inv"),
    .function   = TX_NAME(ff_tx_mdct_inv),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ_init)(AVTXContext *s,
                                                     ਅਚਲ FFTXCodelet *cd,
                                                     uint64_t flags,
                                                     FFTXCodeletOptions *opts,
                                                     ਪੂਰਨ len, ਪੂਰਨ inv,
                                                     ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~AV_TX_ਭਰਿਆ_IMDCT;

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(MDCT), flags, ਨਿਰਾ, len, 1, scale)))
        ਵਾਪਸ ret;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ)(AVTXContext *s, ਖਾਲੀ *_dst,
                                         ਖਾਲੀ *_src, ptrdiff_t stride)
{
    ਪੂਰਨ len  = s->len << 1;
    ਪੂਰਨ len2 = len >> 1;
    ਪੂਰਨ len4 = len >> 2;
    TXSample *dst = _dst;

    s->fn[0](&s->sub[0], dst + len4, _src, stride);

    stride /= ਆਕਾਰ(*dst);

    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++) {
        dst[            i*stride] = -dst[(len2 - i - 1)*stride];
        dst[(len - i - 1)*stride] =  dst[(len2 + i + 0)*stride];
    }
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ_def) = {
    .name       = TX_NAME_STR("mdct_inv_full"),
    .function   = TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ),
    .type       = TX_TYPE(MDCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | AV_TX_ਭਰਿਆ_IMDCT,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_mdct_pfa_init)(AVTXContext *s,
                                                ਅਚਲ FFTXCodelet *cd,
                                                uint64_t flags,
                                                FFTXCodeletOptions *opts,
                                                ਪੂਰਨ len, ਪੂਰਨ inv,
                                                ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret, sub_len;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    len >>= 1;
    sub_len = len / cd->factors[0];

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        ਵਾਪਸ ret;

    ਜੇ ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        ਵਾਪਸ ret;

    /* Our 15-point transform is also a compound one, so embed its input map */
    ਜੇ (cd->factors[0] == 15)
        TX_EMBED_ਨਿਵੇਸ਼_PFA_MAP(s->map, len, 3, 5);

    ਜੇ ((ret = TX_TAB(ff_tx_mdct_gen_exp)(s, inv ? s->map : ਨਿਰਾ)))
        ਵਾਪਸ ret;

    /* Saves multiplies in loops. */
    ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
        s->map[i] <<= 1;

    ਜੇ (!(s->tmp = av_malloc(len*ਆਕਾਰ(*s->tmp))))
        ਵਾਪਸ AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    ਵਾਪਸ 0;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_COMP_IMDCT(N)                                                     \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_pfa_##N##xM_inv)(AVTXContext *s, ਖਾਲੀ *_dst,    \
                                                ਖਾਲੀ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXComplex *z = _dst, *ਘਾਤਾਂਕ = s->ਘਾਤਾਂਕ;                                        \
    ਅਚਲ TXSample *src = _src, *in1, *in2;                                    \
    ਅਚਲ ਪੂਰਨ len4 = s->len >> 2;                                              \
    ਅਚਲ ਪੂਰਨ len2 = s->len >> 1;                                              \
    ਅਚਲ ਪੂਰਨ m = s->sub->len;                                                 \
    ਅਚਲ ਪੂਰਨ *ਵਿੱਚ_map = s->map, *ਬਾਹਰਲਾ_map = ਵਿੱਚ_map + N*m;                       \
    ਅਚਲ ਪੂਰਨ *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= ਆਕਾਰ(*src); /* To convert it from bytes */                     \
    in1 = src;                                                                 \
    in2 = src + ((N*m*2) - 1) * stride;                                        \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < len2; i += N) {                                        \
        ਲਈ (ਪੂਰਨ j = 0; j < N; j++) {                                          \
            ਅਚਲ ਪੂਰਨ k = ਵਿੱਚ_map[j];                                           \
            TXComplex tmp = { in2[-k*stride], in1[k*stride] };                 \
            CMUL3(fft##N##in[j], tmp, ਘਾਤਾਂਕ[j]);                                 \
        }                                                                      \
        fft##N(s->tmp + *(sub_map++), fft##N##in, m);                          \
        ਘਾਤਾਂਕ += N;                                                              \
        ਵਿੱਚ_map += N;                                                           \
    }                                                                          \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, ਆਕਾਰ(TXComplex));   \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++) {                                           \
        ਅਚਲ ਪੂਰਨ i0 = len4 + i, i1 = len4 - i - 1;                            \
        ਅਚਲ ਪੂਰਨ s0 = ਬਾਹਰਲਾ_map[i0], s1 = ਬਾਹਰਲਾ_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].im, s->tmp[s1].re };                     \
        TXComplex src0 = { s->tmp[s0].im, s->tmp[s0].re };                     \
                                                                               \
        CMUL(z[i1].re, z[i0].im, src1.re, src1.im, ਘਾਤਾਂਕ[i1].im, ਘਾਤਾਂਕ[i1].re);    \
        CMUL(z[i0].re, z[i1].im, src0.re, src0.im, ਘਾਤਾਂਕ[i0].im, ਘਾਤਾਂਕ[i0].re);    \
    }                                                                          \
}                                                                              \
                                                                               \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_inv_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_inv"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_inv),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_INVERSE_ONLY,   \
    .factors    = { N, TX_ਗੁਣਕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

DECL_COMP_IMDCT(3)
DECL_COMP_IMDCT(5)
DECL_COMP_IMDCT(7)
DECL_COMP_IMDCT(9)
DECL_COMP_IMDCT(15)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_COMP_MDCT(N)                                                      \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd)(AVTXContext *s, ਖਾਲੀ *_dst,    \
                                                ਖਾਲੀ *_src, ptrdiff_t stride)  \
{                                                                              \
    TXComplex fft##N##in[N];                                                   \
    TXSample *src = _src, *dst = _dst;                                         \
    TXComplex *ਘਾਤਾਂਕ = s->ਘਾਤਾਂਕ, tmp;                                              \
    ਅਚਲ ਪੂਰਨ m = s->sub->len;                                                 \
    ਅਚਲ ਪੂਰਨ len4 = N*m;                                                      \
    ਅਚਲ ਪੂਰਨ len3 = len4 * 3;                                                 \
    ਅਚਲ ਪੂਰਨ len8 = s->len >> 2;                                              \
    ਅਚਲ ਪੂਰਨ *ਵਿੱਚ_map = s->map, *ਬਾਹਰਲਾ_map = ਵਿੱਚ_map + N*m;                       \
    ਅਚਲ ਪੂਰਨ *sub_map = s->sub->map;                                          \
                                                                               \
    stride /= ਆਕਾਰ(*dst);                                                    \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < m; i++) { /* Folding and pre-reindexing */             \
        ਲਈ (ਪੂਰਨ j = 0; j < N; j++) {                                          \
            ਅਚਲ ਪੂਰਨ k = ਵਿੱਚ_map[i*N + j];                                     \
            ਜੇ (k < len4) {                                                    \
                tmp.re = FOLD(-src[ len4 + k],  src[1*len4 - 1 - k]);          \
                tmp.im = FOLD(-src[ len3 + k], -src[1*len3 - 1 - k]);          \
            } ਨਹੀਂਤਾਂ {                                                           \
                tmp.re = FOLD(-src[ len4 + k], -src[5*len4 - 1 - k]);          \
                tmp.im = FOLD( src[-len4 + k], -src[1*len3 - 1 - k]);          \
            }                                                                  \
            CMUL(fft##N##in[j].im, fft##N##in[j].re, tmp.re, tmp.im,           \
                 ਘਾਤਾਂਕ[k >> 1].re, ਘਾਤਾਂਕ[k >> 1].im);                              \
        }                                                                      \
        fft##N(s->tmp + sub_map[i], fft##N##in, m);                            \
    }                                                                          \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < N; i++)                                                \
        s->fn[0](&s->sub[0], s->tmp + m*i, s->tmp + m*i, ਆਕਾਰ(TXComplex));   \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 0; i < len8; i++) {                                           \
        ਅਚਲ ਪੂਰਨ i0 = len8 + i, i1 = len8 - i - 1;                            \
        ਅਚਲ ਪੂਰਨ s0 = ਬਾਹਰਲਾ_map[i0], s1 = ਬਾਹਰਲਾ_map[i1];                          \
        TXComplex src1 = { s->tmp[s1].re, s->tmp[s1].im };                     \
        TXComplex src0 = { s->tmp[s0].re, s->tmp[s0].im };                     \
                                                                               \
        CMUL(dst[2*i1*stride + stride], dst[2*i0*stride], src0.re, src0.im,    \
             ਘਾਤਾਂਕ[i0].im, ਘਾਤਾਂਕ[i0].re);                                          \
        CMUL(dst[2*i0*stride + stride], dst[2*i1*stride], src1.re, src1.im,    \
             ਘਾਤਾਂਕ[i1].im, ਘਾਤਾਂਕ[i1].re);                                          \
    }                                                                          \
}                                                                              \
                                                                               \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd_def) = {           \
    .name       = TX_NAME_STR("mdct_pfa_" #N "xM_fwd"),                        \
    .function   = TX_NAME(ff_tx_mdct_pfa_##N##xM_fwd),                         \
    .type       = TX_TYPE(MDCT),                                               \
    .flags      = AV_TX_UNALIGNED | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_FORWARD_ONLY,   \
    .factors    = { N, TX_ਗੁਣਕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = N*2,                                                         \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_mdct_pfa_init),                                \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

DECL_COMP_MDCT(3)
DECL_COMP_MDCT(5)
DECL_COMP_MDCT(7)
DECL_COMP_MDCT(9)
DECL_COMP_MDCT(15)

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_rdft_init)(AVTXContext *s,
                                            ਅਚਲ FFTXCodelet *cd,
                                            uint64_t flags,
                                            FFTXCodeletOptions *opts,
                                            ਪੂਰਨ len, ਪੂਰਨ inv,
                                            ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    ਦੁੱਗਣਾ f, m;
    TXSample *tab;
    uint64_t r2r = flags & AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL;
    ਪੂਰਨ len4 = FFALIGN(len, 4) / 4;

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~(AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL | AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY);

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, ਨਿਰਾ, len >> 1, inv, scale)))
        ਵਾਪਸ ret;

    ਜੇ (!(s->ਘਾਤਾਂਕ = av_mallocz((8 + 2*len4)*ਆਕਾਰ(*s->ਘਾਤਾਂਕ))))
        ਵਾਪਸ AVERROR(ENOMEM);

    tab = (TXSample *)s->ਘਾਤਾਂਕ;

    f = 2*M_PI/len;

    m = (inv ? 2*s->scale_d : s->scale_d);

    *tab++ = RESCALE((inv ? 0.5 : 1.0) * m);
    *tab++ = RESCALE(inv ? 0.5*m : 1.0*m);
    *tab++ = RESCALE( m);
    *tab++ = RESCALE(-m);

    *tab++ = RESCALE( (0.5 - 0.0) * m);
    ਜੇ (r2r)
        *tab++ = 1 / s->scale_f;
    ਨਹੀਂਤਾਂ
        *tab++ = RESCALE( (0.0 - 0.5) * m);
    *tab++ = RESCALE( (0.5 - inv) * m);
    *tab++ = RESCALE(-(0.5 - inv) * m);

    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++)
        *tab++ = RESCALE(ਕੋਜੀਵਾ(i*f));

    tab = ((TXSample *)s->ਘਾਤਾਂਕ) + len4 + 8;

    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++)
        *tab++ = RESCALE(ਕੋਜੀਵਾ(((len - i*4)/4.0)*f)) * (inv ? 1 : -1);

    ਵਾਪਸ 0;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_RDFT(n, inv)                                                      \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, ਖਾਲੀ *_dst,               \
                                     ਖਾਲੀ *_src, ptrdiff_t stride)             \
{                                                                              \
    ਅਚਲ ਪੂਰਨ len2 = s->len >> 1;                                              \
    ਅਚਲ ਪੂਰਨ len4 = s->len >> 2;                                              \
    ਅਚਲ TXSample *fact = (ਖਾਲੀ *)s->ਘਾਤਾਂਕ;                                     \
    ਅਚਲ TXSample *tcos = fact + 8;                                           \
    ਅਚਲ TXSample *tsin = tcos + len4;                                        \
    TXComplex *ਅੰਕੜੇ = inv ? _src : _dst;                                       \
    TXComplex t[3];                                                            \
                                                                               \
    ਜੇ (!inv)                                                                  \
        s->fn[0](&s->sub[0], ਅੰਕੜੇ, _src, ਆਕਾਰ(TXComplex));                   \
    ਨਹੀਂਤਾਂ                                                                       \
        ਅੰਕੜੇ[0].im = ਅੰਕੜੇ[len2].re;                                            \
                                                                               \
    /* The DC value's both components are real, but we need to change them     \
     * into complex values. Also, the middle of the array is special-cased.    \
     * These operations can be done before or after the loop. */               \
    t[0].re = ਅੰਕੜੇ[0].re;                                                      \
    ਅੰਕੜੇ[0].re = t[0].re + ਅੰਕੜੇ[0].im;                                         \
    ਅੰਕੜੇ[0].im = t[0].re - ਅੰਕੜੇ[0].im;                                         \
    ਅੰਕੜੇ[   0].re = MULT(fact[0], ਅੰਕੜੇ[   0].re);                              \
    ਅੰਕੜੇ[   0].im = MULT(fact[1], ਅੰਕੜੇ[   0].im);                              \
    ਅੰਕੜੇ[len4].re = MULT(fact[2], ਅੰਕੜੇ[len4].re);                              \
    ਅੰਕੜੇ[len4].im = MULT(fact[3], ਅੰਕੜੇ[len4].im);                              \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 1; i < len4; i++) {                                           \
        /* Separate even and odd FFTs */                                       \
        t[0].re = MULT(fact[4], (ਅੰਕੜੇ[i].re + ਅੰਕੜੇ[len2 - i].re));             \
        t[0].im = MULT(fact[5], (ਅੰਕੜੇ[i].im - ਅੰਕੜੇ[len2 - i].im));             \
        t[1].re = MULT(fact[6], (ਅੰਕੜੇ[i].im + ਅੰਕੜੇ[len2 - i].im));             \
        t[1].im = MULT(fact[7], (ਅੰਕੜੇ[i].re - ਅੰਕੜੇ[len2 - i].re));             \
                                                                               \
        /* Apply twiddle factors to the odd FFT and add to the even FFT */     \
        CMUL(t[2].re, t[2].im, t[1].re, t[1].im, tcos[i], tsin[i]);            \
                                                                               \
        ਅੰਕੜੇ[       i].re = t[0].re + t[2].re;                                 \
        ਅੰਕੜੇ[       i].im = t[2].im - t[0].im;                                 \
        ਅੰਕੜੇ[len2 - i].re = t[0].re - t[2].re;                                 \
        ਅੰਕੜੇ[len2 - i].im = t[2].im + t[0].im;                                 \
    }                                                                          \
                                                                               \
    ਜੇ (inv) {                                                                 \
        s->fn[0](&s->sub[0], _dst, ਅੰਕੜੇ, ਆਕਾਰ(TXComplex));                   \
    } ਨਹੀਂਤਾਂ {                                                                   \
        /* Move [0].im to the last position, as convention requires */         \
        ਅੰਕੜੇ[len2].re = ਅੰਕੜੇ[0].im;                                            \
        ਅੰਕੜੇ[   0].im = ਅੰਕੜੇ[len2].im = 0;                                     \
    }                                                                          \
}                                                                              \
                                                                               \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ |       \
                  (inv ? FF_TX_INVERSE_ONLY : FF_TX_FORWARD_ONLY),             \
    .factors    = { 4, TX_ਗੁਣਕ_ANY },                                        \
    .nb_factors = 2,                                                           \
    .min_len    = 4,                                                           \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

DECL_RDFT(r2c,  0)
DECL_RDFT(c2r,  1)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_RDFT_HALF(n, ਬਹੁਲਕ, mod2)                                          \
ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_rdft_ ##n)(AVTXContext *s, ਖਾਲੀ *_dst,               \
                                        ਖਾਲੀ *_src, ptrdiff_t stride)          \
{                                                                              \
    ਅਚਲ ਪੂਰਨ len = s->len;                                                    \
    ਅਚਲ ਪੂਰਨ len2 = len >> 1;                                                 \
    ਅਚਲ ਪੂਰਨ len4 = len >> 2;                                                 \
    ਅਚਲ ਪੂਰਨ aligned_len4 = FFALIGN(len, 4)/4;                                \
    ਅਚਲ TXSample *fact = (ਖਾਲੀ *)s->ਘਾਤਾਂਕ;                                     \
    ਅਚਲ TXSample *tcos = fact + 8;                                           \
    ਅਚਲ TXSample *tsin = tcos + aligned_len4;                                \
    TXComplex *ਅੰਕੜੇ = _dst;                                                    \
    TXSample *ਬਾਹਰਲਾ = _dst; /* Half-complex is forward-only */                   \
    TXSample tmp_dc;                                                           \
    av_ਅਣਵਰਤਿਆ TXSample tmp_mid;                                                \
    TXSample tmp[4];                                                           \
    TXComplex sf, sl;                                                          \
                                                                               \
    s->fn[0](&s->sub[0], _dst, _src, ਆਕਾਰ(TXComplex));                       \
                                                                               \
    tmp_dc = ਅੰਕੜੇ[0].re;                                                       \
    ਅੰਕੜੇ[   0].re = tmp_dc + ਅੰਕੜੇ[0].im;                                       \
    tmp_dc        = tmp_dc - ਅੰਕੜੇ[0].im;                                       \
                                                                               \
    ਅੰਕੜੇ[   0].re = MULT(fact[0], ਅੰਕੜੇ[   0].re);                              \
    tmp_dc        = MULT(fact[1],        tmp_dc);                              \
    ਅੰਕੜੇ[len4].re = MULT(fact[2], ਅੰਕੜੇ[len4].re);                              \
                                                                               \
    ਜੇ (!mod2) {                                                               \
        ਅੰਕੜੇ[len4].im = MULT(fact[3], ਅੰਕੜੇ[len4].im);                          \
    } ਨਹੀਂਤਾਂ {                                                                   \
        sf = ਅੰਕੜੇ[len4];                                                       \
        sl = ਅੰਕੜੇ[len4 + 1];                                                   \
        ਜੇ (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        ਨਹੀਂਤਾਂ                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        ਜੇ (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL) {                                      \
            tmp[3]  = tmp[1]*tcos[len4] - tmp[2]*tsin[len4];                   \
            tmp_mid = (tmp[0] - tmp[3]);                                       \
        } ਨਹੀਂਤਾਂ {                                                               \
            tmp[3]  = tmp[1]*tsin[len4] + tmp[2]*tcos[len4];                   \
            tmp_mid = (tmp[0] + tmp[3]);                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* NOTE: unrolling this breaks non-mod8 lengths */                         \
    ਲਈ (ਪੂਰਨ i = 1; i <= len4; i++) {                                          \
        TXSample tmp[4];                                                       \
        TXComplex sf = ਅੰਕੜੇ[i];                                                \
        TXComplex sl = ਅੰਕੜੇ[len2 - i];                                         \
                                                                               \
        ਜੇ (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL)                                        \
            tmp[0] = MULT(fact[4], (sf.re + sl.re));                           \
        ਨਹੀਂਤਾਂ                                                                   \
            tmp[0] = MULT(fact[5], (sf.im - sl.im));                           \
                                                                               \
        tmp[1] = MULT(fact[6], (sf.im + sl.im));                               \
        tmp[2] = MULT(fact[7], (sf.re - sl.re));                               \
                                                                               \
        ਜੇ (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL) {                                      \
            tmp[3]           = tmp[1]*tcos[i] - tmp[2]*tsin[i];                \
            ਬਾਹਰਲਾ[i]           = (tmp[0] + tmp[3]);                              \
            ਬਾਹਰਲਾ[len - i]     = (tmp[0] - tmp[3]);                              \
        } ਨਹੀਂਤਾਂ {                                                               \
            tmp[3]           = tmp[1]*tsin[i] + tmp[2]*tcos[i];                \
            ਬਾਹਰਲਾ[i - 1]       = (tmp[3] - tmp[0]);                              \
            ਬਾਹਰਲਾ[len - i - 1] = (tmp[0] + tmp[3]);                              \
        }                                                                      \
    }                                                                          \
                                                                               \
    ਲਈ (ਪੂਰਨ i = 1; i < (len4 + (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY)); i++)       \
        ਬਾਹਰਲਾ[len2 - i] = ਬਾਹਰਲਾ[len - i];                                          \
                                                                               \
    ਜੇ (ਬਹੁਲਕ == AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL) {                                          \
        ਬਾਹਰਲਾ[len2] = tmp_dc;                                                    \
        ਜੇ (mod2)                                                              \
            ਬਾਹਰਲਾ[len4 + 1] = tmp_mid * fact[5];                                 \
    } ਨਹੀਂਤਾਂ ਜੇ (mod2) {                                                         \
        ਬਾਹਰਲਾ[len4] = tmp_mid;                                                   \
    }                                                                          \
}                                                                              \
                                                                               \
ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_rdft_ ##n## _def) = {                   \
    .name       = TX_NAME_STR("rdft_" #n),                                     \
    .function   = TX_NAME(ff_tx_rdft_ ##n),                                    \
    .type       = TX_TYPE(RDFT),                                               \
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | ਬਹੁਲਕ |                     \
                  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_FORWARD_ONLY,                     \
    .factors    = { 2 + 2*(!mod2), TX_ਗੁਣਕ_ANY },                            \
    .nb_factors = 2,                                                           \
    .min_len    = 2 + 2*(!mod2),                                               \
    .max_len    = TX_LEN_UNLIMITED,                                            \
    .init       = TX_NAME(ff_tx_rdft_init),                                    \
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,                                         \
    .prio       = FF_TX_PRIO_ਅਧਾਰ,                                             \
};

DECL_RDFT_HALF(r2r,      AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL,      0)
DECL_RDFT_HALF(r2r_mod2, AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL,      1)
DECL_RDFT_HALF(r2i,      AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY, 0)
DECL_RDFT_HALF(r2i_mod2, AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY, 1)

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_dct_init)(AVTXContext *s,
                                           ਅਚਲ FFTXCodelet *cd,
                                           uint64_t flags,
                                           FFTXCodeletOptions *opts,
                                           ਪੂਰਨ len, ਪੂਰਨ inv,
                                           ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    ਦੁੱਗਣਾ freq;
    TXSample *tab;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    ਜੇ (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, ਨਿਰਾ, len, inv, &rsc)))
        ਵਾਪਸ ret;

    s->ਘਾਤਾਂਕ = av_malloc((len/2)*3*ਆਕਾਰ(TXSample));
    ਜੇ (!s->ਘਾਤਾਂਕ)
        ਵਾਪਸ AVERROR(ENOMEM);

    tab = (TXSample *)s->ਘਾਤਾਂਕ;

    freq = M_PI/(len*2);

    ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
        tab[i] = RESCALE(ਕੋਜੀਵਾ(i*freq)*(!inv + 1));

    ਜੇ (inv) {
        ਲਈ (ਪੂਰਨ i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(0.5 / ਜੀਵਾ((2*i + 1)*freq));
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ i = 0; i < len/2; i++)
            tab[len + i] = RESCALE(ਕੋਜੀਵਾ((len - 2*i - 1)*freq));
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_dctII)(AVTXContext *s, ਖਾਲੀ *_dst,
                                 ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ਅਚਲ ਪੂਰਨ len = s->len;
    ਅਚਲ ਪੂਰਨ len2 = len >> 1;
    ਅਚਲ TXSample *ਘਾਤਾਂਕ = (ਖਾਲੀ *)s->ਘਾਤਾਂਕ;
    TXSample ਅਗਲਾ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    int64_t tmp1, tmp2;
#ਨਹੀਂਤਾਂ
    TXSample tmp1, tmp2;
#ਜੇ_ਅੰਤ

    ਲਈ (ਪੂਰਨ i = 0; i < len2; i++) {
        TXSample in1 = src[i];
        TXSample in2 = src[len - i - 1];
        TXSample s    = ਘਾਤਾਂਕ[len + i];

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
        tmp1 = in1 + in2;
        tmp2 = in1 - in2;

        tmp1 >>= 1;
        tmp2 *= s;

        tmp2 = (tmp2 + 0x40000000) >> 31;
#ਨਹੀਂਤਾਂ
        tmp1 = (in1 + in2)*0.5;
        tmp2 = (in1 - in2)*s;
#ਜੇ_ਅੰਤ

        src[i]           = tmp1 + tmp2;
        src[len - i - 1] = tmp1 - tmp2;
    }

    s->fn[0](&s->sub[0], dst, src, ਆਕਾਰ(TXComplex));

    ਅਗਲਾ = dst[len];

    ਲਈ (ਪੂਰਨ i = len - 2; i > 0; i -= 2) {
        TXSample tmp;

        CMUL(tmp, dst[i], ਘਾਤਾਂਕ[len - i], ਘਾਤਾਂਕ[i], dst[i + 0], dst[i + 1]);

        dst[i + 1] = ਅਗਲਾ;

        ਅਗਲਾ += tmp;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    tmp1 = ((int64_t)ਘਾਤਾਂਕ[0]) * ((int64_t)dst[0]);
    dst[0] = (tmp1 + 0x40000000) >> 31;
#ਨਹੀਂਤਾਂ
    dst[0] = ਘਾਤਾਂਕ[0] * dst[0];
#ਜੇ_ਅੰਤ
    dst[1] = ਅਗਲਾ;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_dctIII)(AVTXContext *s, ਖਾਲੀ *_dst,
                                  ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ਅਚਲ ਪੂਰਨ len = s->len;
    ਅਚਲ ਪੂਰਨ len2 = len >> 1;
    ਅਚਲ TXSample *ਘਾਤਾਂਕ = (ਖਾਲੀ *)s->ਘਾਤਾਂਕ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
    int64_t  tmp1, tmp2 = src[len - 1];
    tmp2 = (2*tmp2 + 0x40000000) >> 31;
#ਨਹੀਂਤਾਂ
    TXSample tmp1, tmp2 = 2*src[len - 1];
#ਜੇ_ਅੰਤ

    src[len] = tmp2;

    ਲਈ (ਪੂਰਨ i = len - 2; i >= 2; i -= 2) {
        TXSample val1 = src[i - 0];
        TXSample val2 = src[i - 1] - src[i + 1];

        CMUL(src[i + 1], src[i], ਘਾਤਾਂਕ[len - i], ਘਾਤਾਂਕ[i], val1, val2);
    }

    s->fn[0](&s->sub[0], dst, src, ਆਕਾਰ(ਦਸ਼ਮਲਵ));

    ਲਈ (ਪੂਰਨ i = 0; i < len2; i++) {
        TXSample in1 = dst[i];
        TXSample in2 = dst[len - i - 1];
        TXSample c   = ਘਾਤਾਂਕ[len + i];

        tmp1 = in1 + in2;
        tmp2 = in1 - in2;
        tmp2 *= c;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TX_INT32
        tmp2 = (tmp2 + 0x40000000) >> 31;
#ਜੇ_ਅੰਤ

        dst[i]            = tmp1 + tmp2;
        dst[len - i - 1]  = tmp1 - tmp2;
    }
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_dctII_def) = {
    .name       = TX_NAME_STR("dctII"),
    .function   = TX_NAME(ff_tx_dctII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_FORWARD_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_dctIII_def) = {
    .name       = TX_NAME_STR("dctIII"),
    .function   = TX_NAME(ff_tx_dctIII),
    .type       = TX_TYPE(DCT),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE |
                  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | FF_TX_INVERSE_ONLY,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dct_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ av_cold ਪੂਰਨ TX_NAME(ff_tx_dcstI_init)(AVTXContext *s,
                                             ਅਚਲ FFTXCodelet *cd,
                                             uint64_t flags,
                                             FFTXCodeletOptions *opts,
                                             ਪੂਰਨ len, ਪੂਰਨ inv,
                                             ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    SCALE_TYPE rsc = *((SCALE_TYPE *)scale);

    ਜੇ (inv) {
        len *= 2;
        s->len *= 2;
        rsc *= 0.5;
    }

    /* We want a half-complex RDFT */
    flags |= cd->type == TX_TYPE(DCT_I) ? AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL :
                                          AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY;

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(RDFT), flags, ਨਿਰਾ,
                                (len - 1 + 2*(cd->type == TX_TYPE(DST_I)))*2,
                                0, &rsc)))
        ਵਾਪਸ ret;

    s->tmp = av_mallocz((len + 1)*2*ਆਕਾਰ(TXSample));
    ਜੇ (!s->tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_dctI)(AVTXContext *s, ਖਾਲੀ *_dst,
                                ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ਅਚਲ ਪੂਰਨ len = s->len - 1;
    TXSample *tmp = (TXSample *)s->tmp;

    stride /= ਆਕਾਰ(TXSample);

    ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
        tmp[i] = tmp[2*len - i] = src[i * stride];

    tmp[len] = src[len * stride]; /*ਵਿਚਕਾਰ*/

    s->fn[0](&s->sub[0], dst, tmp, ਆਕਾਰ(TXSample));
}

ਸਥਿਰ ਖਾਲੀ TX_NAME(ff_tx_dstI)(AVTXContext *s, ਖਾਲੀ *_dst,
                                ਖਾਲੀ *_src, ptrdiff_t stride)
{
    TXSample *dst = _dst;
    TXSample *src = _src;
    ਅਚਲ ਪੂਰਨ len = s->len + 1;
    TXSample *tmp = (ਖਾਲੀ *)s->tmp;

    stride /= ਆਕਾਰ(TXSample);

    tmp[0] = 0;

    ਲਈ (ਪੂਰਨ i = 1; i < len; i++) {
        TXSample a = src[(i - 1) * stride];
        tmp[i] = -a;
        tmp[2*len - i] = a;
    }

    tmp[len] = 0; /* i == n, Nyquist */

    s->fn[0](&s->sub[0], dst, tmp, ਆਕਾਰ(ਦਸ਼ਮਲਵ));
}

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_dctI_def) = {
    .name       = TX_NAME_STR("dctI"),
    .function   = TX_NAME(ff_tx_dctI),
    .type       = TX_TYPE(DCT_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet TX_NAME(ff_tx_dstI_def) = {
    .name       = TX_NAME_STR("dstI"),
    .function   = TX_NAME(ff_tx_dstI),
    .type       = TX_TYPE(DST_I),
    .flags      = AV_TX_UNALIGNED | AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ,
    .factors    = { 2, TX_ਗੁਣਕ_ANY },
    .nb_factors = 2,
    .min_len    = 2,
    .max_len    = TX_LEN_UNLIMITED,
    .init       = TX_NAME(ff_tx_dcstI_init),
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_ਅਧਾਰ,
};

ਪੂਰਨ TX_TAB(ff_tx_mdct_gen_exp)(AVTXContext *s, ਪੂਰਨ *pre_tab)
{
    ਪੂਰਨ off = 0;
    ਪੂਰਨ len4 = s->len >> 1;
    ਦੁੱਗਣਾ scale = s->scale_d;
    ਅਚਲ ਦੁੱਗਣਾ theta = (scale < 0 ? len4 : 0) + 1.0/8.0;
    size_t alloc = pre_tab ? 2*len4 : len4;

    ਜੇ (!(s->ਘਾਤਾਂਕ = av_malloc_array(alloc, ਆਕਾਰ(*s->ਘਾਤਾਂਕ))))
        ਵਾਪਸ AVERROR(ENOMEM);

    scale = ਵਰਗਮੂਲ(fabs(scale));

    ਜੇ (pre_tab)
        off = len4;

    ਲਈ (ਪੂਰਨ i = 0; i < len4; i++) {
        ਅਚਲ ਦੁੱਗਣਾ alpha = M_PI_2 * (i + theta) / len4;
        s->ਘਾਤਾਂਕ[off + i] = (TXComplex){ RESCALE(ਕੋਜੀਵਾ(alpha) * scale),
                                       RESCALE(ਜੀਵਾ(alpha) * scale) };
    }

    ਜੇ (pre_tab)
        ਲਈ (ਪੂਰਨ i = 0; i < len4; i++)
            s->ਘਾਤਾਂਕ[i] = s->ਘਾਤਾਂਕ[len4 + pre_tab[i]];

    ਵਾਪਸ 0;
}

ਅਚਲ FFTXCodelet * ਅਚਲ TX_NAME(ff_tx_codelet_list)[] = {
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
    &TX_NAME(ff_tx_mdct_inv_ਭਰਿਆ_def),
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

    ਨਿਰਾ,
};
