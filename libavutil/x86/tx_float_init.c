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

#घोषणा TX_FLOAT
#समावेश "libavutil/tx_priv.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/x86/cpu.h"

#समावेश "config.h"

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

#घोषणा DECL_INIT_FN(basis, interleave)                                        \
अटल av_cold पूर्णांक b ##basis## _i ##interleave(AVTXContext *s,                 \
                                               स्थिर FFTXCodelet *cd,          \
                                               uint64_t flags,                 \
                                               FFTXCodeletOptions *opts,       \
                                               पूर्णांक len, पूर्णांक inv,               \
                                               स्थिर व्योम *scale)              \
{                                                                              \
    ff_tx_init_tabs_float(len);                                                \
    अगर (cd->max_len == 2)                                                      \
        वापस ff_tx_gen_ptwo_revtab(s, opts);                                 \
    अन्यथा                                                                       \
        वापस ff_tx_gen_split_radix_parity_revtab(s, len, inv, opts,          \
                                                   basis, interleave);         \
}

DECL_INIT_FN(8, 0)
DECL_INIT_FN(8, 2)

#अगर ARCH_X86_64
अटल av_cold पूर्णांक factor_init(AVTXContext *s, स्थिर FFTXCodelet *cd,
                               uint64_t flags, FFTXCodeletOptions *opts,
                               पूर्णांक len, पूर्णांक inv, स्थिर व्योम *scale)
{
    पूर्णांक ret;

    /* The transformations below are performed in the gather domain,
     * so override the option and let the infrastructure convert the map
     * to SCATTER if needed. */
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    TX_TAB(ff_tx_init_tabs)(len);

    अगर (len == 15)
        ret = ff_tx_gen_pfa_निवेश_map(s, &sub_opts, 3, 5);
    अन्यथा
        ret = ff_tx_gen_default_map(s, &sub_opts);

    अगर (ret < 0)
        वापस ret;

    अगर (len == 15) {
        पूर्णांक cnt = 0, tmp[15];

        /* Special permutation to simplify loads in the pre-permuted version */
        स_नकल(tmp, s->map, 15*माप(*tmp));
        क्रम (पूर्णांक i = 1; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        क्रम (पूर्णांक i = 2; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        क्रम (पूर्णांक i = 0; i < 15; i += 3) {
            s->map[cnt] = tmp[i];
            cnt++;
        }
        स_हटाओ(&s->map[7], &s->map[6], 4*माप(पूर्णांक));
        स_हटाओ(&s->map[3], &s->map[1], 4*माप(पूर्णांक));
        s->map[1] = tmp[2];
        s->map[2] = tmp[0];
    }

    वापस 0;
}

अटल av_cold पूर्णांक m_inv_init(AVTXContext *s, स्थिर FFTXCodelet *cd,
                              uint64_t flags, FFTXCodeletOptions *opts,
                              पूर्णांक len, पूर्णांक inv, स्थिर व्योम *scale)
{
    पूर्णांक ret;
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_GATHER };

    s->scale_d = *((SCALE_TYPE *)scale);
    s->scale_f = s->scale_d;

    flags &= ~FF_TX_OUT_OF_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */
    flags |=  FF_TX_ASM_CALL;     /* We want an assembly function, not C */

    अगर ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts, len >> 1,
                                inv, scale)))
        वापस ret;

    s->map = av_malloc(len*माप(*s->map));
    अगर (!s->map)
        वापस AVERROR(ENOMEM);

    स_नकल(s->map, s->sub->map, (len >> 1)*माप(*s->map));
    /* Invert lookup table for unstrided path */
    क्रम (पूर्णांक i = 0; i < (len >> 1); i++)
       s->map[(len >> 1) + s->map[i]] = i;

    अगर ((ret = ff_tx_mdct_gen_exp_float(s, s->map)))
        वापस ret;

    वापस 0;
}

अटल av_cold पूर्णांक fft_pfa_init(AVTXContext *s,
                                स्थिर FFTXCodelet *cd,
                                uint64_t flags,
                                FFTXCodeletOptions *opts,
                                पूर्णांक len, पूर्णांक inv,
                                स्थिर व्योम *scale)
{
    पूर्णांक ret;
    पूर्णांक sub_len = len / cd->factors[0];
    FFTXCodeletOptions sub_opts = { .map_dir = FF_TX_MAP_SCATTER };

    flags &= ~FF_TX_OUT_OF_PLACE; /* We want the subtransform to be */
    flags |=  AV_TX_INPLACE;      /* in-place */
    flags |=  FF_TX_PRESHUFFLE;   /* This function handles the permute step */
    flags |=  FF_TX_ASM_CALL;     /* We want an assembly function, not C */

    अगर ((ret = ff_tx_init_subtx(s, TX_TYPE(FFT), flags, &sub_opts,
                                sub_len, inv, scale)))
        वापस ret;

    अगर ((ret = ff_tx_gen_compound_mapping(s, opts, s->inv, cd->factors[0], sub_len)))
        वापस ret;

    अगर (cd->factors[0] == 15) {
        पूर्णांक tmp[15];

        /* Our 15-point transform is also a compound one, so embed its input map */
        TX_EMBED_निवेश_PFA_MAP(s->map, len, 3, 5);

        /* Special permutation to simplify loads in the pre-permuted version */
        क्रम (पूर्णांक k = 0; k < s->sub[0].len; k++) {
            पूर्णांक cnt = 0;
            स_नकल(tmp, &s->map[k*15], 15*माप(*tmp));
            क्रम (पूर्णांक i = 1; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            क्रम (पूर्णांक i = 2; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            क्रम (पूर्णांक i = 0; i < 15; i += 3) {
                s->map[k*15 + cnt] = tmp[i];
                cnt++;
            }
            स_हटाओ(&s->map[k*15 + 7], &s->map[k*15 + 6], 4*माप(पूर्णांक));
            स_हटाओ(&s->map[k*15 + 3], &s->map[k*15 + 1], 4*माप(पूर्णांक));
            s->map[k*15 + 1] = tmp[2];
            s->map[k*15 + 2] = tmp[0];
        }
    }

    अगर (!(s->tmp = av_malloc(len*माप(*s->tmp))))
        वापस AVERROR(ENOMEM);

    TX_TAB(ff_tx_init_tabs)(len / sub_len);

    वापस 0;
}
#पूर्ण_अगर

स्थिर FFTXCodelet * स्थिर ff_tx_codelet_list_float_x86[] = {
    TX_DEF(fft2,     FFT,  2,  2, 2, 0, 128, शून्य,  sse3, SSE3, AV_TX_INPLACE, 0),
    TX_DEF(fft2_asm, FFT,  2,  2, 2, 0, 192, b8_i0, sse3, SSE3,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, 0),
    TX_DEF(fft2,     FFT,  2,  2, 2, 0, 192, b8_i0, sse3, SSE3, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_fwd, FFT,  4,  4, 2, 0, 128, शून्य,  sse2, SSE2, AV_TX_INPLACE | FF_TX_FORWARD_ONLY, 0),
    TX_DEF(fft4_fwd_asm, FFT,  4,  4, 2, 0, 192, b8_i0, sse2, SSE2,
           AV_TX_INPLACE | FF_TX_PRESHUFFLE | FF_TX_ASM_CALL, 0),
    TX_DEF(fft4_inv_asm, FFT,  4,  4, 2, 0, 128, शून्य,  sse2, SSE2,
           AV_TX_INPLACE | FF_TX_INVERSE_ONLY | FF_TX_ASM_CALL, 0),
    TX_DEF(fft4_fwd, FFT,  4,  4, 2, 0, 192, b8_i0, sse2, SSE2, AV_TX_INPLACE | FF_TX_PRESHUFFLE, 0),
    TX_DEF(fft4_inv, FFT,  4,  4, 2, 0, 128, शून्य,  sse2, SSE2, AV_TX_INPLACE | FF_TX_INVERSE_ONLY, 0),
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

#अगर ARCH_X86_64
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

    TX_DEF(fft15, FFT, 15, 15, 15, 0, 320, factor_init, avx2, AVX2,
           AV_TX_INPLACE, AV_CPU_FLAG_AVXSLOW),
    TX_DEF(fft15_ns, FFT, 15, 15, 15, 0, 384, factor_init, avx2, AVX2,
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

    TX_DEF(mdct_inv, MDCT, 16, TX_LEN_UNLIMITED, 2, TX_FACTOR_ANY, 384, m_inv_init, avx2, AVX2,
           FF_TX_INVERSE_ONLY, AV_CPU_FLAG_AVXSLOW | AV_CPU_FLAG_SLOW_GATHER),
#पूर्ण_अगर

    शून्य,
};
