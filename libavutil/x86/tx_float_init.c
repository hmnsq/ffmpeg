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
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/x86/cpu.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

TX_DECL_FN(fft2,      sse3)
TX_DECL_FN(fft4_fwd,  sse2)
TX_DECL_FN(fft4_inv,  sse2)
TX_DECL_FN(fft8,      sse3)
TX_DECL_FN(fft8_ns,   sse3)
TX_DECL_FN(fft8,      avx)
TX_DECL_FN(fft8_ns,   avx)
TX_DECL_FN(fft15,     avx2)
TX_DECL_FN(fft15_ns,  avx2)
TX_DECL_FN(fft16,     avx)
TX_DECL_FN(fft16_ns,  avx)
TX_DECL_FN(fft16,     fma3)
TX_DECL_FN(fft16_ns,  fma3)
TX_DECL_FN(fft32,     avx)
TX_DECL_FN(fft32_ns,  avx)
TX_DECL_FN(fft32,     fma3)
TX_DECL_FN(fft32_ns,  fma3)
TX_DECL_FN(fft_sr,    avx)
TX_DECL_FN(fft_sr_ns, avx)
TX_DECL_FN(fft_sr,    fma3)
TX_DECL_FN(fft_sr_ns, fma3)
TX_DECL_FN(fft_sr,    avx2)
TX_DECL_FN(fft_sr_ns, avx2)

TX_DECL_FN(fft_pfa_15xM, avx2)
TX_DECL_FN(fft_pfa_15xM_ns, avx2)

TX_DECL_FN(mdct_inv, avx2)

TX_DECL_FN(fft2_asm, sse3)
TX_DECL_FN(fft4_fwd_asm, sse2)
TX_DECL_FN(fft4_inv_asm, sse2)
TX_DECL_FN(fft8_asm, sse3)
TX_DECL_FN(fft8_asm, avx)
TX_DECL_FN(fft16_asm, avx)
TX_DECL_FN(fft16_asm, fma3)
TX_DECL_FN(fft32_asm, avx)
TX_DECL_FN(fft32_asm, fma3)
TX_DECL_FN(fft_sr_asm, avx)
TX_DECL_FN(fft_sr_asm, fma3)
TX_DECL_FN(fft_sr_asm, avx2)

TX_DECL_FN(fft_pfa_15xM_asm, avx2)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECL_INIT_FN(basis, interleave)                                        \
ਸਥਿਰ av_cold ਪੂਰਨ b ##basis## _i ##interleave(AVTXContext *s,                 \
                                               ਅਚਲ FFTXCodelet *cd,          \
                                               uint64_t flags,                 \
                                               FFTXCodeletOptions *opts,       \
                                               ਪੂਰਨ len, ਪੂਰਨ inv,               \
                                               ਅਚਲ ਖਾਲੀ *scale)              \
{                                                                              \
    ff_tx_init_tabs_float(len);                                                \
    ਜੇ (cd->max_len == 2)                                                      \
        ਵਾਪਸ ff_tx_gen_ptwo_revtab(s, opts);                                 \
    ਨਹੀਂਤਾਂ                                                                       \
        ਵਾਪਸ ff_tx_gen_ਵੰਡੋ_radix_parity_revtab(s, len, inv, opts,          \
                                                   basis, interleave);         \
}

DECL_INIT_FN(8, 0)
DECL_INIT_FN(8, 2)

#ਜੇ ARCH_X86_64
ਸਥਿਰ av_cold ਪੂਰਨ ਗੁਣਕ_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                               uint64_t flags, FFTXCodeletOptions *opts,
                               ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;

    /* The transformations below are performed in the gather domain,
     * so override the option and let the infrastructure convert the map
     * to SCATTER if needed. */
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    TX_TAB(ff_tx_init_tabs)(len);

    ਜੇ (len == 15)
        ret = ff_tx_gen_pfa_ਨਿਵੇਸ਼_map(s, &sub_opts, 3, 5);
    ਨਹੀਂਤਾਂ
        ret = ff_tx_gen_default_map(s, &sub_opts);

    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (len == 15) {
        ਪੂਰਨ cnt = 0, tmp[15];

        /* Special permutation to simplify loads in the pre-permuted version */
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp, s->map, 15*ਆਕਾਰ(*tmp));
        ਲਈ (ਪੂਰਨ i = 1; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        ਲਈ (ਪੂਰਨ i = 2; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        ਲਈ (ਪੂਰਨ i = 0; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        memmove(&s->map[7], &s->map[6], 4*ਆਕਾਰ(ਪੂਰਨ));
        memmove(&s->map[3], &s->map[1], 4*ਆਕਾਰ(ਪੂਰਨ));
        s->map[1] = tmp[2];
        s->map[2] = tmp[0];
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ av_cold ਪੂਰਨ m_inv_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                              uint64_t flags, FFTXCodeletOptions *opts,
                              ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */
    flags |=  FF_TX_ASM_CALL;     /* We want an assembly function, not C */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale)))
        ਵਾਪਸ ret;

    s->map = av_malloc(len*ਆਕਾਰ(*s->map));
    ਜੇ (!s->map)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(s->map, s->sub->map, (len >> 1)*ਆਕਾਰ(*s->map));
    /* Invert lookup table for unstrided path */
    ਲਈ (ਪੂਰਨ i = 0; i < (len >> 1); i++)
       s->map[(len >> 1) + s->map[i]] = i;

    ਜੇ ((ret = ff_tx_mdct_gen_exp_float(s, s->map)))
        ਵਾਪਸ ret;

    ਵਾਪਸ 0;
}

ਸਥਿਰ av_cold ਪੂਰਨ fft_pfa_init(AVTXContext *s,
                                ਅਚਲ FFTXCodelet *cd,
                                uint64_t flags,
                                FFTXCodeletOptions *opts,
                                ਪੂਰਨ len, ਪੂਰਨ inv,
                                ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret;
    ਪੂਰਨ sub_len = len / cd->factors[0];
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    flags &= ~FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */
    flags |=  FF_TX_ASM_CALL;     /* We want an assembly function, not C */

    ਜੇ ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        ਵਾਪਸ ret;

    ਜੇ ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        ਵਾਪਸ ret;

    ਜੇ (cd->factors[0] == 15) {
        ਪੂਰਨ tmp[15];

        /* Our 15-point transform is also a compound one, so embed its input map */
        TX_EMBED_ਨਿਵੇਸ਼_PFA_MAP(s->map, len, 3, 5);

        /* Special permutation to simplify loads in the pre-permuted version */
        ਲਈ (ਪੂਰਨ k = 0; k < s->sub[0].len; k++) {
            ਪੂਰਨ cnt = 0;
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp, &s->map[k*15], 15*ਆਕਾਰ(*tmp));
            ਲਈ (ਪੂਰਨ i = 1; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            ਲਈ (ਪੂਰਨ i = 2; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            ਲਈ (ਪੂਰਨ i = 0; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            memmove(&s->map[k*15 + 7], &s->map[k*15 + 6], 4*ਆਕਾਰ(ਪੂਰਨ));
            memmove(&s->map[k*15 + 3], &s->map[k*15 + 1], 4*ਆਕਾਰ(ਪੂਰਨ));
            s->map[k*15 + 1] = tmp[2];
            s->map[k*15 + 2] = tmp[0];
        }
    }

    ਜੇ (!(s->tmp = av_malloc(len*ਆਕਾਰ(*s->tmp))))
        ਵਾਪਸ AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

ਅਚਲ FFTXCodelet * ਅਚਲ ff_tx_codelet_list_float_x86[] = {
    TX_DEF(fft2,     FFT,  2,  2, 2, 0, 128, ਨਿਰਾ,  sse3, SSE3, AV_TX_INPLACE, 0),
    TX_DEF(fft2_asm, FFT,  2,  2, 2, 0, 192, b8_i0, sse3, SSE3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, 0),
    TX_DEF(fft2,     FFT,  2,  2, 2, 0, 192, b8_i0, sse3, SSE3, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_fwd, FFT,  4,  4, 2, 0, 128, ਨਿਰਾ,  sse2, SSE2, AV_TX_INPLACE | FF_TX_FORWARD_ONLY, 0),
    TX_DEF(fft4_fwd_asm, FFT,  4,  4, 2, 0, 192, b8_i0, sse2, SSE2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, 0),
    TX_DEF(fft4_inv_asm, FFT,  4,  4, 2, 0, 128, ਨਿਰਾ,  sse2, SSE2,
           AV_TX_INPLACE | FF_TX_INVERSE_ONLY | FF_TX_ASM_CALL, 0),
    TX_DEF(fft4_fwd, FFT,  4,  4, 2, 0, 192, b8_i0, sse2, SSE2, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_inv, FFT,  4,  4, 2, 0, 128, ਨਿਰਾ,  sse2, SSE2, AV_TX_INPLACE | FF_TX_INVERSE_ONLY, 0),
    TX_DEF(fft8,     FFT,  8,  8, 2, 0, 128, b8_i0, sse3, SSE3, AV_TX_INPLACE, 0),
    TX_DEF(fft8_asm, FFT,  8,  8, 2, 0, 192, b8_i0, sse3, SSE3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, 0),
    TX_DEF(fft8_ns,  FFT,  8,  8, 2, 0, 192, b8_i0, sse3, SSE3, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft8,     FFT,  8,  8, 2, 0, 256, b8_i0, avx,  AVX,  AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft8_asm, FFT,  8,  8, 2, 0, 320, b8_i0, avx,  AVX,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft8_ns,  FFT,  8,  8, 2, 0, 320, b8_i0, avx,  AVX,  AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16,    FFT, 16, 16, 2, 0, 256, b8_i2, avx,  AVX,  AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16_asm, FFT, 16, 16, 2, 0, 320, b8_i2, avx,  AVX,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16_ns, FFT, 16, 16, 2, 0, 320, b8_i2, avx,  AVX,  AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16,    FFT, 16, 16, 2, 0, 288, b8_i2, fma3, FMA3, AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16_asm, FFT, 16, 16, 2, 0, 352, b8_i2, fma3, FMA3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft16_ns, FFT, 16, 16, 2, 0, 352, b8_i2, fma3, FMA3, AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),

#ਜੇ ARCH_X86_64
    TX_DEF(fft32,    FFT, 32, 32, 2, 0, 256, b8_i2, avx,  AVX,  AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft32_asm, FFT, 32, 32, 2, 0, 320, b8_i2, avx,  AVX,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft32_ns, FFT, 32, 32, 2, 0, 320, b8_i2, avx,  AVX,  AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft32,    FFT, 32, 32, 2, 0, 288, b8_i2, fma3, FMA3, AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft32_asm, FFT, 32, 32, 2, 0, 352, b8_i2, fma3, FMA3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft32_ns, FFT, 32, 32, 2, 0, 352, b8_i2, fma3, FMA3, AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr,    FFT, 64, 131072, 2, 0, 256, b8_i2, avx, AVX,  0, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr_asm, FFT, 64, 131072, 2, 0, 320, b8_i2, avx, AVX,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr_ns, FFT, 64, 131072, 2, 0, 320, b8_i2, avx, AVX,  AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr,    FFT, 64, 131072, 2, 0, 288, b8_i2, fma3,  FMA3,  0, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr_asm, FFT, 64, 131072, 2, 0, 352, b8_i2, fma3,  FMA3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft_sr_ns, FFT, 64, 131072, 2, 0, 352, b8_i2, fma3,  FMA3,  AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW),

    TX_DEF(fft15, FFT, 15, 15, 15, 0, 320, ਗੁਣਕ_init, avx2, AVX2,
           AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft15_ns, FFT, 15, 15, 15, 0, 384, ਗੁਣਕ_init, avx2, AVX2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE, AV_CPU_FLAG_AVXSLOW),

    TX_DEF(fft_sr,    FFT, 64, 131072, 2, 0, 320, b8_i2, avx2, AVX2, 0,
           AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
    TX_DEF(fft_sr_asm, FFT, 64, 131072, 2, 0, 384, b8_i2, avx2, AVX2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
    TX_DEF(fft_sr_ns, FFT, 64, 131072, 2, 0, 384, b8_i2, avx2, AVX2, AV_TX_INPLACE | FF_TX_PRESHUFFLE,
           AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),

    TX_DEF(fft_pfa_15xM, FFT, 60, TX_LEN_UNLIMITED, 15, 2, 320, fft_pfa_init, avx2, AVX2,
           AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
    TX_DEF(fft_pfa_15xM_asm, FFT, 60, TX_LEN_UNLIMITED, 15, 2, 384, fft_pfa_init, avx2, AVX2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
    TX_DEF(fft_pfa_15xM_ns, FFT, 60, TX_LEN_UNLIMITED, 15, 2, 384, fft_pfa_init, avx2, AVX2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),

    TX_DEF(mdct_inv, MDCT, 16, TX_LEN_UNLIMITED, 2, TX_ਗੁਣਕ_ANY, 384, m_inv_init, avx2, AVX2,
           FF_TX_INVERSE_ONLY, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
#ਜੇ_ਅੰਤ

    ਨਿਰਾ,
};
