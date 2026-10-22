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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TX_FLOAT
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/tx_priv.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/aarch64/cpu.h"

TX_DECL_FN(fft2,      neon)
TX_DECL_FN(fft4_fwd,  neon)
TX_DECL_FN(fft4_inv,  neon)
TX_DECL_FN(fft8,      neon)
TX_DECL_FN(fft8_ns,   neon)
TX_DECL_FN(fft15,     neon)
TX_DECL_FN(fft15_ns,  neon)
TX_DECL_FN(fft16,     neon)
TX_DECL_FN(fft16_ns,  neon)
TX_DECL_FN(fft32,     neon)
TX_DECL_FN(fft32_ns,  neon)
TX_DECL_FN(fft_sr,    neon)
TX_DECL_FN(fft_sr_ns, neon)
TX_DECL_FN(fft_pfa_15xM, neon)
TX_DECL_FN(fft_pfa_15xM_ns, neon)
TX_DECL_FN(mdct_inv, neon)

ਸਥਿਰ av_cold ਪੂਰਨ neon_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ff_tx_init_tabs_float(len);
    ਜੇ (cd->max_len == 2)
        ਵਾਪਸ ff_tx_gen_ptwo_revtab(s, opts);
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ ff_tx_gen_ਵੰਡੋ_radix_parity_revtab(s, len, inv, opts, 8, 0);
}

/* Reorder one 15-point map so the loads in the pre-permuted assembly path
 * become simple contiguous chunks. Mirrors the x86 FFT15 init. */
ਸਥਿਰ ਖਾਲੀ fft15_ਕ੍ਰਮ_ਬਦਲੋ_map(ਪੂਰਨ *map)
{
    ਪੂਰਨ cnt = 0, tmp[15];
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp, map, 15*ਆਕਾਰ(*tmp));
    ਲਈ (ਪੂਰਨ i = 1; i < 15; i += 3)
        map[cnt++] = tmp[i];
    ਲਈ (ਪੂਰਨ i = 2; i < 15; i += 3)
        map[cnt++] = tmp[i];
    ਲਈ (ਪੂਰਨ i = 0; i < 15; i += 3)
        map[cnt++] = tmp[i];
    memmove(&map[7], &map[6], 4*ਆਕਾਰ(ਪੂਰਨ));
    memmove(&map[3], &map[1], 4*ਆਕਾਰ(ਪੂਰਨ));
    map[1] = tmp[2];
    map[2] = tmp[0];
}

ਸਥਿਰ av_cold ਪੂਰਨ fft15_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                              uint64_t flags, FFTXCodeletOptions *opts,
                              ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    ff_tx_init_tabs_float(len);

    ਜੇ ((ret = ff_tx_gen_pfa_ਨਿਵੇਸ਼_map(s, &sub_opts, 3, 5)) < 0)
        ਵਾਪਸ ret;

    fft15_ਕ੍ਰਮ_ਬਦਲੋ_map(s->map);

    ਵਾਪਸ 0;
}

/* 15xM prime-factor FFT: M inlined 15-point transforms followed by 15 calls to
 * a power-of-two subtransform. Mirrors the x86 fft_pfa_15xM, but the aarch64
 * ABI lets us call the subtransform normally, so no FF_TX_ASM_CALL is needed. */
ਸਥਿਰ av_cold ਪੂਰਨ fft_pfa_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                                uint64_t flags, FFTXCodeletOptions *opts,
                                ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    ਪੂਰਨ sub_len = len / cd->factors[0];
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        ਵਾਪਸ ret;

    ਜੇ ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv,
                                          cd->factors[0], sub_len)))
        ਵਾਪਸ ret;

    /* The 15-point transform is itself a compound one, so embed its input map
     * and apply the same load-friendly reorder used by fft15_init. */
    TX_EMBED_ਨਿਵੇਸ਼_PFA_MAP(s->map, len, 3, 5);
    ਲਈ (ਪੂਰਨ k = 0; k < sub_len; k++)
        fft15_ਕ੍ਰਮ_ਬਦਲੋ_map(&s->map[k*15]);

    ਜੇ (!(s->tmp = av_malloc(len*ਆਕਾਰ(*s->tmp))))
        ਵਾਪਸ AVERROR(ENOMEM);

    ff_tx_init_tabs_float(len / sub_len);

    ਵਾਪਸ 0;
}

/* Inverse MDCT: a pre-rotation, an in-place len/2 complex FFT, and a
 * post-rotation. Mirrors the generic ff_tx_mdct_init / x86 m_inv_init, but the
 * subtransform is called with a normal blr (no FF_TX_ASM_CALL on aarch64). */
ਸਥਿਰ av_cold ਪੂਰਨ mdct_inv_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                                 uint64_t flags, FFTXCodeletOptions *opts,
                                 ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    /* The pre-rotation processes two output complex at a time, so len/2 must
     * be even.  Real codecs always satisfy this; bail out otherwise so the
     * generic C MDCT is used. */
    ਜੇ (len & 3)
        ਵਾਪਸ AVERROR(ENOSYS);

    s->scale_d = *((ਅਚਲ ਦਸ਼ਮਲਵ *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* The subtransform is in-place */
    flags |=  AV_TX_INPLACE;
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale)))
        ਵਾਪਸ ret;

    /* The map holds the gather map (first half, used by the strided
     * pre-rotation) followed by its inverse (second half): the contiguous
     * stride==4 path reads the input in order and scatters output complex i
     * to position s->map[len2 + j], where j is the contiguous input index. */
    s->map = av_malloc(len*ਆਕਾਰ(*s->map));
    ਜੇ (!s->map)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(s->map, s->sub->map, (len >> 1)*ਆਕਾਰ(*s->map));

    ਜੇ ((ret = ff_tx_mdct_gen_exp_float(s, s->map)))
        ਵਾਪਸ ret;

    /* Invert the gather map for the contiguous path (before doubling). */
    ਲਈ (ਪੂਰਨ i = 0; i < (len >> 1); i++)
        s->map[(len >> 1) + s->map[i]] = i;

    /* Pre-double the gather-map indices (saves a shift in the strided path). */
    ਲਈ (ਪੂਰਨ i = 0; i < (len >> 1); i++)
        s->map[i] <<= 1;

    ਵਾਪਸ 0;
}

ਅਚਲ FFTXCodelet * ਅਚਲ ff_tx_codelet_list_float_aarch64[] = {
    TX_DEF(fft2,      FFT,  2,  2, 2, 0, 128, ਨਿਰਾ,      neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft2,      FFT,  2,  2, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_fwd,  FFT,  4,  4, 2, 0, 128, ਨਿਰਾ,      neon, NEON, AV_TX_INPLACE | FF_TX_FORWARD_ONLY, 0),
    TX_DEF(fft4_fwd,  FFT,  4,  4, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_inv,  FFT,  4,  4, 2, 0, 128, ਨਿਰਾ,      neon, NEON, AV_TX_INPLACE | FF_TX_INVERSE_ONLY, 0),
    TX_DEF(fft8,      FFT,  8,  8, 2, 0, 128, neon_init, neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft8_ns,   FFT,  8,  8, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft15,     FFT, 15, 15, 15, 0, 128, fft15_init, neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft15_ns,  FFT, 15, 15, 15, 0, 192, fft15_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft16,     FFT, 16, 16, 2, 0, 128, neon_init, neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft16_ns,  FFT, 16, 16, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft32,     FFT, 32, 32, 2, 0, 128, neon_init, neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft32_ns,  FFT, 32, 32, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),

    TX_DEF(fft_sr,    FFT, 64, 131072, 2, 0, 128, neon_init, neon, NEON, 0, 0),
    TX_DEF(fft_sr_ns, FFT, 64, 131072, 2, 0, 192, neon_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),

    TX_DEF(fft_pfa_15xM,    FFT, 60, TX_LEN_UNLIMITED, 15, 2, 128, fft_pfa_init, neon, NEON, AV_TX_INPLACE, 0),
    TX_DEF(fft_pfa_15xM_ns, FFT, 60, TX_LEN_UNLIMITED, 15, 2, 192, fft_pfa_init, neon, NEON, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),

    TX_DEF(mdct_inv, MDCT, 16, TX_LEN_UNLIMITED, 2, TX_ਗੁਣਕ_ANY, 256, mdct_inv_init, neon, NEON, FF_TX_INVERSE_ONLY, 0),

    ਨਿਰਾ,
};
