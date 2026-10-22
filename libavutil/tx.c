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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "intmath.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "qsort.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"

#ಅನ್ತರ್ಭಾವ "tx_priv.h"

#ವ್ಯಾಖ್ಯಾನಿಸು TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ಸ್ಥಿರ av_always_inline ಪೂರ್ಣಾಂಕ mulinv(ಪೂರ್ಣಾಂಕ n, ಪೂರ್ಣಾಂಕ m)
{
    n = n % m;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 1; x < m; x++)
        ಆದರೆ (((n * x) % m) == 1)
            ಹಿಂತಿರುಗಿ x;
    av_assert0(0); /* Never reached */
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_tx_gen_pfa_ಒಳಹರಿವು_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            ಪೂರ್ಣಾಂಕ d1, ಪೂರ್ಣಾಂಕ d2)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ sl = d1*d2;

    s->map = av_malloc(s->len*ಗಾತ್ರ(*s->map));
    ಆದರೆ (!s->map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < s->len; k += sl) {
        ಆದರೆ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ m = 0; m < d2; m++)
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ m = 0; m < d2; m++)
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ಆದರೆ (s->inv)
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(ಪೂರ್ಣಾಂಕ, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಹಿಂತಿರುಗಿ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
ಪೂರ್ಣಾಂಕ ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               ಪೂರ್ಣಾಂಕ inv, ಪೂರ್ಣಾಂಕ n, ಪೂರ್ಣಾಂಕ m)
{
    ಪೂರ್ಣಾಂಕ *ಒಳ_map, *ಹೊರಹೋಗು_map;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = n*m;    /* Will not be equal to s->len for MDCTs */
    ಪೂರ್ಣಾಂಕ m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ಆದರೆ (av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(n, m) != 1)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ಆದರೆ (!(s->map = av_malloc(2*len*ಗಾತ್ರ(*s->map))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಒಳ_map  = s->map;
    ಹೊರಹೋಗು_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ಆದರೆ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < m; j++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++) {
                ಒಳ_map[(i*m + j*n) % len] = j*n + i;
                ಹೊರಹೋಗು_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < m; j++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < n; i++) {
                ಒಳ_map[j*n + i] = (i*m + j*n) % len;
                ಹೊರಹೋಗು_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ಆದರೆ (inv) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < m; i++) {
            ಪೂರ್ಣಾಂಕ *ಒಳ = &ಒಳ_map[i*n + 1]; /* Skip the DC */
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(ಪೂರ್ಣಾಂಕ, ಒಳ[j], ಒಳ[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ವಿಭಜಿಸು_radix_permutation(ಪೂರ್ಣಾಂಕ i, ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv)
{
    len >>= 1;
    ಆದರೆ (len <= 1)
        ಹಿಂತಿರುಗಿ i & 1;
    ಆದರೆ (!(i & len))
        ಹಿಂತಿರುಗಿ ವಿಭಜಿಸು_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ಹಿಂತಿರುಗಿ ವಿಭಜಿಸು_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

ಪೂರ್ಣಾಂಕ ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    ಪೂರ್ಣಾಂಕ len = s->len;

    ಆದರೆ (!(s->map = av_malloc(len*ಗಾತ್ರ(*s->map))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->len; i++)
            s->map[-ವಿಭಜಿಸು_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->len; i++)
            s->map[i] = -ವಿಭಜಿಸು_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_tx_gen_inplace_map(AVTXContext *s, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ *src_map, ಹೊರಹೋಗು_map_idx = 0;

    ಆದರೆ (!s->sub || !s->sub->map)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!(s->map = av_mallocz(len*ಗಾತ್ರ(*s->map))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ src = 1; src < s->len; src++) {
        ಪೂರ್ಣಾಂಕ dst = src_map[src];
        ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು = 0;

        ಆದರೆ (dst <= src)
            ಮುಂದುವರಿ;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        ಮಾಡು {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < ಹೊರಹೋಗು_map_idx; j++) {
                ಆದರೆ (dst == s->map[j]) {
                    ಸಿಕ್ಕಿತು = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }
            dst = src_map[dst];
        } ಆಗ (dst != src && !ಸಿಕ್ಕಿತು);

        ಆದರೆ (!ಸಿಕ್ಕಿತು)
            s->map[ಹೊರಹೋಗು_map_idx++] = src;
    }

    s->map[ಹೊರಹೋಗು_map_idx++] = 0;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ parity_revtab_generator(ಪೂರ್ಣಾಂಕ *revtab, ಪೂರ್ಣಾಂಕ n, ಪೂರ್ಣಾಂಕ inv, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ,
                                    ಪೂರ್ಣಾಂಕ is_dual, ಪೂರ್ಣಾಂಕ dual_ಮೇಲಿನ, ಪೂರ್ಣಾಂಕ len,
                                    ಪೂರ್ಣಾಂಕ basis, ಪೂರ್ಣಾಂಕ dual_stride, ಪೂರ್ಣಾಂಕ inv_lookup)
{
    len >>= 1;

    ಆದರೆ (len <= basis) {
        ಪೂರ್ಣಾಂಕ k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ಮೇಲಿನ = is_dual & dual_ಮೇಲಿನ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = ಸ್ಥಾನಾಂತರ + dual_ಮೇಲಿನ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ಮೇಲಿನ)*len + dual_ಮೇಲಿನ*len;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++) {
            k1 = -ವಿಭಜಿಸು_radix_permutation(ಸ್ಥಾನಾಂತರ + i*2 + 0, n, inv) & (n - 1);
            k2 = -ವಿಭಜಿಸು_radix_permutation(ಸ್ಥಾನಾಂತರ + i*2 + 1, n, inv) & (n - 1);
            ಆದರೆ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ಇಲ್ಲದಿದ್ದರೆ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ಆದರೆ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ಹಿಂತಿರುಗಿ;
    }

    parity_revtab_generator(revtab, n, inv, ಸ್ಥಾನಾಂತರ,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, ಸ್ಥಾನಾಂತರ + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, ಸ್ಥಾನಾಂತರ + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

ಪೂರ್ಣಾಂಕ ff_tx_gen_ವಿಭಜಿಸು_radix_parity_revtab(AVTXContext *s, ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv,
                                        FFTXCodeletOptions *opts,
                                        ಪೂರ್ಣಾಂಕ basis, ಪೂರ್ಣಾಂಕ dual_stride)
{
    basis >>= 1;
    ಆದರೆ (len < basis)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!(s->map = av_mallocz(len*ಗಾತ್ರ(*s->map))))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_ctx(AVTXContext *s, ಪೂರ್ಣಾಂಕ free_sub)
{
    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (s->sub)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ಆದರೆ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ಆದರೆ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->ಘಾತಾಂಕ);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ಖಾಲಿ;
    memset(s->fn, 0, ಗಾತ್ರ(s->fn));
}

ಶೂನ್ಯ ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold ಶೂನ್ಯ av_tx_uninit(AVTXContext **ctx)
{
    ಆದರೆ (!(*ctx))
        ಹಿಂತಿರುಗಿ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಂಕ ff_tx_null_init(AVTXContext *s, ಸ್ಥಿರಾಂಕ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ಆದರೆ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಹಿಂತಿರುಗಿ 0;
}

/* Null transform when the length is 1 */
ಸ್ಥಿರ ಶೂನ್ಯ ff_tx_null(AVTXContext *s, ಶೂನ್ಯ *ಹೊರಹೋಗು_3, ಶೂನ್ಯ *ಒಳ_3, ptrdiff_t stride)
{
    ಸ್ಮರಣೆ_ನಕಲು(ಹೊರಹೋಗು_3, ಒಳ_3, stride);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet ff_tx_null_def = {
    .name       = NULL_IF_CONFIG_SMALL("null"),
    .function   = ff_tx_null,
    .type       = TX_TYPE_ANY,
    .flags      = AV_TX_UNALIGNED | FF_TX_ALIGNED |
                  FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು | AV_TX_INPLACE,
    .factors[0] = TX_ಗುಣಕ_ANY,
    .min_len    = 1,
    .max_len    = 1,
    .init       = ff_tx_null_init,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MAX,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet * ಸ್ಥಿರಾಂಕ ff_tx_null_list[] = {
    &ff_tx_null_def,
    ಖಾಲಿ,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FFTXCodelet * ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#ಆದರೆ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#ಆದರೆ_ಅಂತ್ಯ
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ codelet_list_ಅಂಕೆ = FF_ARRAY_ELEMS(codelet_list);

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ cpu_slow_ಮುಖವಾಡ = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_codelet_prio(ಸ್ಥಿರಾಂಕ FFTXCodelet *cd, ಪೂರ್ಣಾಂಕ cpu_flags, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ prio = cd->prio;
    ಪೂರ್ಣಾಂಕ max_ಗುಣಕ = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ಆದರೆ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ಆದರೆ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ಆದರೆ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ಆದರೆ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < TX_MAX_SUB; i++)
        max_ಗುಣಕ = FFMAX(cd->factors[i], max_ಗುಣಕ);
    ಆದರೆ (max_ಗುಣಕ)
        prio += 16*max_ಗುಣಕ;

    ಹಿಂತಿರುಗಿ prio;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFTXLenDecomp {
    ಪೂರ್ಣಾಂಕ len;
    ಪೂರ್ಣಾಂಕ len2;
    ಪೂರ್ಣಾಂಕ prio;
    ಸ್ಥಿರಾಂಕ FFTXCodelet *cd;
} FFTXLenDecomp;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ಹಿಂತಿರುಗಿ FFDIFFSIGN(b->prio, a->prio);
}

ಪೂರ್ಣಾಂಕ ff_tx_decompose_ಉದ್ದಳತೆ(ಪೂರ್ಣಾಂಕ dst[TX_MAX_DECOMPOSITIONS], ಎಣಿಕೆ AVTXType type,
                           ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv)
{
    ಪೂರ್ಣಾಂಕ nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    ಪೂರ್ಣಾಂಕ codelet_list_idx = codelet_list_ಅಂಕೆ;

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ಆಗ (codelet_list_idx--) {
        ಸ್ಥಿರಾಂಕ FFTXCodelet * ಸ್ಥಿರಾಂಕ * list = codelet_list[codelet_list_idx];
        ಸ್ಥಿರಾಂಕ FFTXCodelet *cd = ಖಾಲಿ;

        ಆಗ ((cd = *list++)) {
            ಪೂರ್ಣಾಂಕ fl = len;
            ಪೂರ್ಣಾಂಕ skip = 0, prio;
            ಪೂರ್ಣಾಂಕ factors_ಗುಣಲಬ್ಧ = 1, factors_mod = 0;

            ಆದರೆ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                ಹೋಗು ವಿಂಗಡಿಸು;

            /* Check if the type matches */
            ಆದರೆ (cd->type != TX_TYPE_ANY && type != cd->type)
                ಮುಂದುವರಿ;

            /* Check direction for non-orthogonal codelets */
            ಆದರೆ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_ತುಂಬಿದ_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ಗಮ್ಯ_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ಗಮ್ಯ_IMAGINARY)) && inv))
                ಮುಂದುವರಿ;

            /* Check if the CPU supports the required ISA */
            ಆದರೆ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ಮುಖವಾಡ)))
                ಮುಂದುವರಿ;

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < TX_MAX_FACTORS; i++) {
                ಆದರೆ (!cd->factors[i] || (fl == 1))
                    ನಿಲ್ಲಿಸು;

                ಆದರೆ (cd->factors[i] == TX_ಗುಣಕ_ANY) {
                    factors_mod++;
                    factors_ಗುಣಲಬ್ಧ *= fl;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ಆದರೆ (cd->factors[i] == 2) {
                        ಪೂರ್ಣಾಂಕ b = ff_ctz(fl);
                        fl >>= b;
                        factors_ಗುಣಲಬ್ಧ <<= b;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಮಾಡು {
                            fl /= cd->factors[i];
                            factors_ಗುಣಲಬ್ಧ *= cd->factors[i];
                        } ಆಗ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ಆದರೆ ((factors_mod < cd->nb_factors) || (len == factors_ಗುಣಲಬ್ಧ))
                ಮುಂದುವರಿ;

            ಆದರೆ (av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(factors_ಗುಣಲಬ್ಧ, fl) != 1)
                ಮುಂದುವರಿ;

            /* Check if length is supported and factorization was successful */
            ಆದರೆ ((factors_ಗುಣಲಬ್ಧ < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_ಗುಣಲಬ್ಧ > cd->max_len)))
                ಮುಂದುವರಿ;

            prio = get_codelet_prio(cd, cpu_flags, factors_ಗುಣಲಬ್ಧ) * factors_ಗುಣಲಬ್ಧ;

            /* Check for duplicates */
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_decomp; i++) {
                ಆದರೆ (factors_ಗುಣಲಬ್ಧ == ld[i].len) {
                    /* Update priority if new one is higher */
                    ಆದರೆ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }

            /* Add decomposition if unique */
            ಆದರೆ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_ಗುಣಲಬ್ಧ;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ಆದರೆ (!nb_decomp)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

ವಿಂಗಡಿಸು:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_decomp; i++) {
        ಆದರೆ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ಇಲ್ಲದಿದ್ದರೆ
            dst[i] = ld[i].len;
    }

    ಹಿಂತಿರುಗಿ nb_decomp;
}

ಪೂರ್ಣಾಂಕ ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*ಗಾತ್ರ(*s->map));
    ಆದರೆ (!s->map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ಆದರೆ (s->inv) /* Reversing the ACs flips the transform direction */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ಇಲ್ಲದಿದ್ದರೆ
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ !CONFIG_SMALL
ಸ್ಥಿರ ಶೂನ್ಯ print_flags(AVBPrint *bp, uint64_t f)
{
    ಪೂರ್ಣಾಂಕ prev = 0;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sep = ", ";
    av_bprintf(bp, "flags: [");
    ಆದರೆ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ಆದರೆ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ಆದರೆ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ಆದರೆ ((f & FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ಆದರೆ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ಆದರೆ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ಆದರೆ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ಆದರೆ ((f & AV_TX_ತುಂಬಿದ_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ಆದರೆ ((f & AV_TX_REAL_ಗಮ್ಯ_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ಆದರೆ ((f & AV_TX_REAL_ಗಮ್ಯ_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ಆದರೆ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ಸ್ಥಿರ ಶೂನ್ಯ print_type(AVBPrint *bp, ಎಣಿಕೆ AVTXType type)
{
    av_bprintf(bp, "%s",
               type == TX_TYPE_ANY       ? "any"         :
               type == AV_TX_FLOAT_FFT   ? "fft_float"   :
               type == AV_TX_FLOAT_MDCT  ? "mdct_float"  :
               type == AV_TX_FLOAT_RDFT  ? "rdft_float"  :
               type == AV_TX_FLOAT_DCT_I ? "dctI_float"  :
               type == AV_TX_FLOAT_DST_I ? "dstI_float"  :
               type == AV_TX_DOUBLE_FFT  ? "fft_double"  :
               type == AV_TX_DOUBLE_MDCT ? "mdct_double" :
               type == AV_TX_DOUBLE_RDFT ? "rdft_double" :
               type == AV_TX_DOUBLE_DCT_I ? "dctI_double" :
               type == AV_TX_DOUBLE_DST_I ? "dstI_double" :
               type == AV_TX_INT32_FFT   ? "fft_int32"   :
               type == AV_TX_INT32_MDCT  ? "mdct_int32"  :
               type == AV_TX_INT32_RDFT  ? "rdft_int32"  :
               type == AV_TX_INT32_DCT_I ? "dctI_int32" :
               type == AV_TX_INT32_DST_I ? "dstI_int32" :
               "unknown");
}

ಸ್ಥಿರ ಶೂನ್ಯ print_cd_info(ಸ್ಥಿರಾಂಕ FFTXCodelet *cd, ಪೂರ್ಣಾಂಕ prio, ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ print_prio,
                          ಪೂರ್ಣಾಂಕ log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ಆದರೆ (!len) {
        ಆದರೆ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ಆದರೆ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ಇಲ್ಲದಿದ್ದರೆ
            av_bprintf(&bp, "%i", cd->max_len);
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_bprintf(&bp, "%i", len);
    }

    ಆದರೆ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ಆದರೆ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ಇಲ್ಲದಿದ್ದರೆ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < TX_MAX_FACTORS; i++) {
            ಆದರೆ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ಆದರೆ (cd->factors[i] == TX_ಗುಣಕ_ANY)
                av_bprintf(&bp, "any");
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ಇಲ್ಲದಿದ್ದರೆ
                ನಿಲ್ಲಿಸು;
        }

        av_bprintf(&bp, "], ");
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ಆದರೆ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ಖಾಲಿ, log_level, "%s\n", bp.str);
}

ಸ್ಥಿರ ಶೂನ್ಯ print_tx_structure(AVTXContext *s, ಪೂರ್ಣಾಂಕ ಆಳ)
{
    ಸ್ಥಿರಾಂಕ FFTXCodelet *cd = s->cd_self;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= ಆಳ; i++)
        av_log(ಖಾಲಿ, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], ಆಳ + 1);
}
#ಆದರೆ_ಅಂತ್ಯ /* CONFIG_SMALL */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ TXCodelet_ಹೊಂದಿಕೆ {
    ಸ್ಥಿರಾಂಕ FFTXCodelet *cd;
    ಪೂರ್ಣಾಂಕ prio;
} TXCodelet_ಹೊಂದಿಕೆ;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cmp_matches(TXCodelet_ಹೊಂದಿಕೆ *a, TXCodelet_ಹೊಂದಿಕೆ *b)
{
    ಹಿಂತಿರುಗಿ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ check_cd_factors(ಸ್ಥಿರಾಂಕ FFTXCodelet *cd, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ matches = 0, any_flag = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < TX_MAX_FACTORS; i++) {
        ಪೂರ್ಣಾಂಕ ಗುಣಕ = cd->factors[i];

        ಆದರೆ (ಗುಣಕ == TX_ಗುಣಕ_ANY) {
            any_flag = 1;
            matches++;
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (len <= 1 || !ಗುಣಕ) {
            ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಗುಣಕ == 2) { /* Fast path */
            ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು_2 = ff_ctz(len);
            ಆದರೆ (!ಬಿಟ್ಟುಗಳು_2)
                ಮುಂದುವರಿ; /* Factor not supported */

            len >>= ಬಿಟ್ಟುಗಳು_2;
            matches++;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ res = len % ಗುಣಕ;
            ಆದರೆ (res)
                ಮುಂದುವರಿ; /* Factor not supported */

            ಆಗ (!res) {
                len /= ಗುಣಕ;
                res = len % ಗುಣಕ;
            }
            matches++;
        }
    }

    ಹಿಂತಿರುಗಿ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold ಪೂರ್ಣಾಂಕ ff_tx_init_subtx(AVTXContext *s, ಎಣಿಕೆ AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ inv, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಂಕ ret = 0;
    AVTXContext *sub = ಖಾಲಿ;
    TXCodelet_ಹೊಂದಿಕೆ *cd_tmp, *cd_matches = ಖಾಲಿ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cd_matches_ಗಾತ್ರ = 0;
    ಪೂರ್ಣಾಂಕ codelet_list_idx = codelet_list_ಅಂಕೆ;
    ಪೂರ್ಣಾಂಕ nb_cd_matches = 0;
#ಆದರೆ !CONFIG_SMALL
    AVBPrint bp;
#ಆದರೆ_ಅಂತ್ಯ

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_ಮುಖವಾಡ = AV_TX_ತುಂಬಿದ_IMDCT |
                            AV_TX_REAL_ಗಮ್ಯ_REAL |
                            AV_TX_REAL_ಗಮ್ಯ_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ಆದರೆ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ಆದರೆ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು);
    ಆದರೆ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ಆಗ (codelet_list_idx--) {
        ಸ್ಥಿರಾಂಕ FFTXCodelet * ಸ್ಥಿರಾಂಕ * list = codelet_list[codelet_list_idx];
        ಸ್ಥಿರಾಂಕ FFTXCodelet *cd = ಖಾಲಿ;

        ಆಗ ((cd = *list++)) {
            /* Check if the type matches */
            ಆದರೆ (cd->type != TX_TYPE_ANY && type != cd->type)
                ಮುಂದುವರಿ;

            /* Check direction for non-orthogonal codelets */
            ಆದರೆ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_ತುಂಬಿದ_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ಗಮ್ಯ_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ಗಮ್ಯ_IMAGINARY)) && inv))
                ಮುಂದುವರಿ;

            /* Check if the requested flags match from both sides */
            ಆದರೆ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_ಮುಖವಾಡ & cd->flags) != (req_flags & inv_req_ಮುಖವಾಡ)))
                ಮುಂದುವರಿ;

            /* Check if length is supported */
            ಆದರೆ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                ಮುಂದುವರಿ;

            /* Check if the CPU supports the required ISA */
            ಆದರೆ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ಮುಖವಾಡ)))
                ಮುಂದುವರಿ;

            /* Check for factors */
            ಆದರೆ (!check_cd_factors(cd, len))
                ಮುಂದುವರಿ;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_ಗಾತ್ರ,
                                     ಗಾತ್ರ(*cd_tmp) * (nb_cd_matches + 1));
            ಆದರೆ (!cd_tmp) {
                av_free(cd_matches);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ಆದರೆ !CONFIG_SMALL
    /* Print debugging info */
    av_bprint_init(&bp, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    av_bprintf(&bp, "For transform of length %i, %s, ", len,
               inv ? "inverse" : "forward");
    print_type(&bp, type);
    av_bprintf(&bp, ", ");
    print_flags(&bp, flags);
    av_bprintf(&bp, ", found %i matches%s", nb_cd_matches,
               nb_cd_matches ? ":" : ".");
#ಆದರೆ_ಅಂತ್ಯ

    /* No matches found */
    ಆದರೆ (!nb_cd_matches)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodelet_ಹೊಂದಿಕೆ, cmp_matches);

#ಆದರೆ !CONFIG_SMALL
    av_log(ಖಾಲಿ, AV_LOG_TRACE, "%s\n", bp.str);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_cd_matches; i++) {
        av_log(ಖಾಲಿ, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*ಗಾತ್ರ(*sub));
        ಆದರೆ (!sub) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು ಕೊನೆ;
        }
    }

    /* Attempt to initialize each */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_cd_matches; i++) {
        ಸ್ಥಿರಾಂಕ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        ಆದರೆ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ಆದರೆ (ret >= 0) {
            ಆದರೆ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*ಗಾತ್ರ(*sctx->map));
                ಆದರೆ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    ಹೋಗು ಕೊನೆ;
                }

                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (opts && (opts->map_dir != sctx->map_dir)) {
                ಪೂರ್ಣಾಂಕ *tmp = av_malloc(len*ಗಾತ್ರ(*sctx->map));
                ಆದರೆ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    ಹೋಗು ಕೊನೆ;
                }

                ಸ್ಮರಣೆ_ನಕಲು(tmp, sctx->map, len*ಗಾತ್ರ(*sctx->map));

                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            ಹೋಗು ಕೊನೆ;
        }

        s->fn[s->nb_sub] = ಖಾಲಿ;
        s->cd[s->nb_sub] = ಖಾಲಿ;

        reset_ctx(sctx, 0);
        ಆದರೆ (ret == AVERROR(ENOMEM))
            ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (!s->nb_sub)
        av_freep(&s->sub);

ಕೊನೆ:
    av_free(cd_matches);
    ಹಿಂತಿರುಗಿ ret;
}

av_cold ಪೂರ್ಣಾಂಕ av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ಎಣಿಕೆ AVTXType type,
                       ಪೂರ್ಣಾಂಕ inv, ಪೂರ್ಣಾಂಕ len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *scale, uint64_t flags)
{
    ಪೂರ್ಣಾಂಕ ret;
    AVTXContext tmp = { 0 };
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ default_scale_d = 1.0;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ  default_scale_f = 1.0f;

    ಆದರೆ (!len || type >= AV_TX_NB || !ctx || !tx)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ಆದರೆ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_ಹೊರಹೋಗು_ದ_ಇರಿಸು;

    ಆದರೆ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ಖಾಲಿ, len, inv, scale);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ಆದರೆ !CONFIG_SMALL
    av_log(ಖಾಲಿ, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ret;
}
