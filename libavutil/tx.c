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

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ಸ್ಥಿರ av_always_inline ಪೂರ್ಣಾಙ್ಕ mulinv(ಪೂರ್ಣಾಙ್ಕ n, ಪೂರ್ಣಾಙ್ಕ m)
{
    n = n % m;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 1; x < m; x++)
        ಯದಿ (((n * x) % m) == 1)
            ಪ್ರತ್ಯಾಗಮ x;
    av_assert0(0); /* Never reached */
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_pfa_ಒಳಹರಿವು_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            ಪೂರ್ಣಾಙ್ಕ d1, ಪೂರ್ಣಾಙ್ಕ d2)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ sl = d1*d2;

    s->map = av_malloc(s->len*ಪರಿಮಾಣ(*s->map));
    ಯದಿ (!s->map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ k = 0; k < s->len; k += sl) {
        ಯದಿ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ m = 0; m < d2; m++)
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ಅನ್ಯಥಾ {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ m = 0; m < d2; m++)
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ಯದಿ (s->inv)
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(ಪೂರ್ಣಾಙ್ಕ, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಪ್ರತ್ಯಾಗಮ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               ಪೂರ್ಣಾಙ್ಕ inv, ಪೂರ್ಣಾಙ್ಕ n, ಪೂರ್ಣಾಙ್ಕ m)
{
    ಪೂರ್ಣಾಙ್ಕ *in_map, *out_map;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ len = n*m;    /* Will not be equal to s->len for MDCTs */
    ಪೂರ್ಣಾಙ್ಕ m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ಯದಿ (av_gcd(n, m) != 1)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ಯದಿ (!(s->map = av_malloc(2*len*ಪರಿಮಾಣ(*s->map))))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ಯದಿ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < m; j++) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < m; j++) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ಯದಿ (inv) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < m; i++) {
            ಪೂರ್ಣಾಙ್ಕ *in = &in_map[i*n + 1]; /* Skip the DC */
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(ಪೂರ್ಣಾಙ್ಕ, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ split_radix_permutation(ಪೂರ್ಣಾಙ್ಕ i, ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ inv)
{
    len >>= 1;
    ಯದಿ (len <= 1)
        ಪ್ರತ್ಯಾಗಮ i & 1;
    ಯದಿ (!(i & len))
        ಪ್ರತ್ಯಾಗಮ split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ಪ್ರತ್ಯಾಗಮ split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    ಪೂರ್ಣಾಙ್ಕ len = s->len;

    ಯದಿ (!(s->map = av_malloc(len*ಪರಿಮಾಣ(*s->map))))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_inplace_map(AVTXContext *s, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ *src_map, out_map_idx = 0;

    ಯದಿ (!s->sub || !s->sub->map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!(s->map = av_mallocz(len*ಪರಿಮಾಣ(*s->map))))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ src = 1; src < s->len; src++) {
        ಪೂರ್ಣಾಙ್ಕ dst = src_map[src];
        ಪೂರ್ಣಾಙ್ಕ found = 0;

        ಯದಿ (dst <= src)
            ಅನುವರ್ತ;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        ಕುರು {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < out_map_idx; j++) {
                ಯದಿ (dst == s->map[j]) {
                    found = 1;
                    ಭಙ್ಗ;
                }
            }
            dst = src_map[dst];
        } ಯಾವತ್ (dst != src && !found);

        ಯದಿ (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ parity_revtab_generator(ಪೂರ್ಣಾಙ್ಕ *revtab, ಪೂರ್ಣಾಙ್ಕ n, ಪೂರ್ಣಾಙ್ಕ inv, ಪೂರ್ಣಾಙ್ಕ offset,
                                    ಪೂರ್ಣಾಙ್ಕ is_dual, ಪೂರ್ಣಾಙ್ಕ dual_ಮೇಲಿನ, ಪೂರ್ಣಾಙ್ಕ len,
                                    ಪೂರ್ಣಾಙ್ಕ basis, ಪೂರ್ಣಾಙ್ಕ dual_stride, ಪೂರ್ಣಾಙ್ಕ inv_lookup)
{
    len >>= 1;

    ಯದಿ (len <= basis) {
        ಪೂರ್ಣಾಙ್ಕ k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ಮೇಲಿನ = is_dual & dual_ಮೇಲಿನ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_ಮೇಲಿನ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ಮೇಲಿನ)*len + dual_ಮೇಲಿನ*len;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            ಯದಿ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ಅನ್ಯಥಾ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ಯದಿ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ಪ್ರತ್ಯಾಗಮ;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ inv,
                                        FFTXCodeletOptions *opts,
                                        ಪೂರ್ಣಾಙ್ಕ basis, ಪೂರ್ಣಾಙ್ಕ dual_stride)
{
    basis >>= 1;
    ಯದಿ (len < basis)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!(s->map = av_mallocz(len*ಪರಿಮಾಣ(*s->map))))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_ctx(AVTXContext *s, ಪೂರ್ಣಾಙ್ಕ free_sub)
{
    ಯದಿ (!s)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (s->sub)
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ಯದಿ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ಯದಿ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ರಿಕ್ತ;
    memset(s->fn, 0, ಪರಿಮಾಣ(s->fn));
}

ಶೂನ್ಯ ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold ಶೂನ್ಯ av_tx_uninit(AVTXContext **ctx)
{
    ಯದಿ (!(*ctx))
        ಪ್ರತ್ಯಾಗಮ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ಸ್ಥಿರ av_cold ಪೂರ್ಣಾಙ್ಕ ff_tx_null_init(AVTXContext *s, ಧ್ರುವ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ inv, ಧ್ರುವ ಶೂನ್ಯ *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ಯದಿ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಪ್ರತ್ಯಾಗಮ 0;
}

/* Null transform when the length is 1 */
ಸ್ಥಿರ ಶೂನ್ಯ ff_tx_null(AVTXContext *s, ಶೂನ್ಯ *_out, ಶೂನ್ಯ *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

ಸ್ಥಿರ ಧ್ರುವ FFTXCodelet ff_tx_null_def = {
    .name       = NULL_IF_CONFIG_SMALL("null"),
    .function   = ff_tx_null,
    .type       = TX_TYPE_ANY,
    .flags      = AV_TX_UNALIGNED | FF_TX_ALIGNED |
                  FF_TX_OUT_OF_PLACE | AV_TX_INPLACE,
    .factors[0] = TX_FACTOR_ANY,
    .min_len    = 1,
    .max_len    = 1,
    .init       = ff_tx_null_init,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MAX,
};

ಸ್ಥಿರ ಧ್ರುವ FFTXCodelet * ಧ್ರುವ ff_tx_null_list[] = {
    &ff_tx_null_def,
    ರಿಕ್ತ,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ಸ್ಥಿರ ಧ್ರುವ FFTXCodelet * ಧ್ರುವ * ಧ್ರುವ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#ಯದಿ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#ಯದಿ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ codelet_list_ಅಂಕೆ = FF_ARRAY_ELEMS(codelet_list);

ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_codelet_prio(ಧ್ರುವ FFTXCodelet *cd, ಪೂರ್ಣಾಙ್ಕ cpu_flags, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ prio = cd->prio;
    ಪೂರ್ಣಾಙ್ಕ max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ಯದಿ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ಯದಿ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ಯದಿ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ಯದಿ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    ಯದಿ (max_factor)
        prio += 16*max_factor;

    ಪ್ರತ್ಯಾಗಮ prio;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFTXLenDecomp {
    ಪೂರ್ಣಾಙ್ಕ len;
    ಪೂರ್ಣಾಙ್ಕ len2;
    ಪೂರ್ಣಾಙ್ಕ prio;
    ಧ್ರುವ FFTXCodelet *cd;
} FFTXLenDecomp;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ಪ್ರತ್ಯಾಗಮ FFDIFFSIGN(b->prio, a->prio);
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_decompose_length(ಪೂರ್ಣಾಙ್ಕ dst[TX_MAX_DECOMPOSITIONS], ಗಣನಾ AVTXType type,
                           ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ inv)
{
    ಪೂರ್ಣಾಙ್ಕ nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    ಪೂರ್ಣಾಙ್ಕ codelet_list_idx = codelet_list_ಅಂಕೆ;

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ಯಾವತ್ (codelet_list_idx--) {
        ಧ್ರುವ FFTXCodelet * ಧ್ರುವ * list = codelet_list[codelet_list_idx];
        ಧ್ರುವ FFTXCodelet *cd = ರಿಕ್ತ;

        ಯಾವತ್ ((cd = *list++)) {
            ಪೂರ್ಣಾಙ್ಕ fl = len;
            ಪೂರ್ಣಾಙ್ಕ skip = 0, prio;
            ಪೂರ್ಣಾಙ್ಕ factors_product = 1, factors_mod = 0;

            ಯದಿ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                ಗಚ್ಛ sort;

            /* Check if the type matches */
            ಯದಿ (cd->type != TX_TYPE_ANY && type != cd->type)
                ಅನುವರ್ತ;

            /* Check direction for non-orthogonal codelets */
            ಯದಿ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ಅನುವರ್ತ;

            /* Check if the CPU supports the required ISA */
            ಯದಿ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ಅನುವರ್ತ;

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < TX_MAX_FACTORS; i++) {
                ಯದಿ (!cd->factors[i] || (fl == 1))
                    ಭಙ್ಗ;

                ಯದಿ (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } ಅನ್ಯಥಾ ಯದಿ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ಯದಿ (cd->factors[i] == 2) {
                        ಪೂರ್ಣಾಙ್ಕ b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } ಅನ್ಯಥಾ {
                        ಕುರು {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } ಯಾವತ್ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ಯದಿ ((factors_mod < cd->nb_factors) || (len == factors_product))
                ಅನುವರ್ತ;

            ಯದಿ (av_gcd(factors_product, fl) != 1)
                ಅನುವರ್ತ;

            /* Check if length is supported and factorization was successful */
            ಯದಿ ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                ಅನುವರ್ತ;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_decomp; i++) {
                ಯದಿ (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    ಯದಿ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ಭಙ್ಗ;
                }
            }

            /* Add decomposition if unique */
            ಯದಿ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ಯದಿ (!nb_decomp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_decomp; i++) {
        ಯದಿ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ಅನ್ಯಥಾ
            dst[i] = ld[i].len;
    }

    ಪ್ರತ್ಯಾಗಮ nb_decomp;
}

ಪೂರ್ಣಾಙ್ಕ ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*ಪರಿಮಾಣ(*s->map));
    ಯದಿ (!s->map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ಯದಿ (s->inv) /* Reversing the ACs flips the transform direction */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ಅನ್ಯಥಾ
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ !CONFIG_SMALL
ಸ್ಥಿರ ಶೂನ್ಯ print_flags(AVBPrint *bp, uint64_t f)
{
    ಪೂರ್ಣಾಙ್ಕ prev = 0;
    ಧ್ರುವ ವರ್ಣ *sep = ", ";
    av_bprintf(bp, "flags: [");
    ಯದಿ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ಯದಿ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ಯದಿ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ಯದಿ ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ಯದಿ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ಯದಿ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ಯದಿ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ಯದಿ ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ಯದಿ ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ಯದಿ ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ಯದಿ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ಸ್ಥಿರ ಶೂನ್ಯ print_type(AVBPrint *bp, ಗಣನಾ AVTXType type)
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

ಸ್ಥಿರ ಶೂನ್ಯ print_cd_info(ಧ್ರುವ FFTXCodelet *cd, ಪೂರ್ಣಾಙ್ಕ prio, ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ print_prio,
                          ಪೂರ್ಣಾಙ್ಕ log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ಯದಿ (!len) {
        ಯದಿ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ಯದಿ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ಅನ್ಯಥಾ
            av_bprintf(&bp, "%i", cd->max_len);
    } ಅನ್ಯಥಾ {
        av_bprintf(&bp, "%i", len);
    }

    ಯದಿ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ಯದಿ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ಅನ್ಯಥಾ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < TX_MAX_FACTORS; i++) {
            ಯದಿ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ಯದಿ (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            ಅನ್ಯಥಾ ಯದಿ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ಅನ್ಯಥಾ
                ಭಙ್ಗ;
        }

        av_bprintf(&bp, "], ");
    } ಅನ್ಯಥಾ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ಯದಿ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ರಿಕ್ತ, log_level, "%s\n", bp.str);
}

ಸ್ಥಿರ ಶೂನ್ಯ print_tx_structure(AVTXContext *s, ಪೂರ್ಣಾಙ್ಕ depth)
{
    ಧ್ರುವ FFTXCodelet *cd = s->cd_self;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i <= depth; i++)
        av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ TXCodeletMatch {
    ಧ್ರುವ FFTXCodelet *cd;
    ಪೂರ್ಣಾಙ್ಕ prio;
} TXCodeletMatch;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    ಪ್ರತ್ಯಾಗಮ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ check_cd_factors(ಧ್ರುವ FFTXCodelet *cd, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ matches = 0, any_flag = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < TX_MAX_FACTORS; i++) {
        ಪೂರ್ಣಾಙ್ಕ factor = cd->factors[i];

        ಯದಿ (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            ಅನುವರ್ತ;
        } ಅನ್ಯಥಾ ಯದಿ (len <= 1 || !factor) {
            ಭಙ್ಗ;
        } ಅನ್ಯಥಾ ಯದಿ (factor == 2) { /* Fast path */
            ಪೂರ್ಣಾಙ್ಕ bits_2 = ff_ctz(len);
            ಯದಿ (!bits_2)
                ಅನುವರ್ತ; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } ಅನ್ಯಥಾ {
            ಪೂರ್ಣಾಙ್ಕ res = len % factor;
            ಯದಿ (res)
                ಅನುವರ್ತ; /* Factor not supported */

            ಯಾವತ್ (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    ಪ್ರತ್ಯಾಗಮ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold ಪೂರ್ಣಾಙ್ಕ ff_tx_init_subtx(AVTXContext *s, ಗಣನಾ AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ inv, ಧ್ರುವ ಶೂನ್ಯ *scale)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 0;
    AVTXContext *sub = ರಿಕ್ತ;
    TXCodeletMatch *cd_tmp, *cd_matches = ರಿಕ್ತ;
    unsigned ಪೂರ್ಣಾಙ್ಕ cd_matches_size = 0;
    ಪೂರ್ಣಾಙ್ಕ codelet_list_idx = codelet_list_ಅಂಕೆ;
    ಪೂರ್ಣಾಙ್ಕ nb_cd_matches = 0;
#ಯದಿ !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ಯದಿ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ಯದಿ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    ಯದಿ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ಯಾವತ್ (codelet_list_idx--) {
        ಧ್ರುವ FFTXCodelet * ಧ್ರುವ * list = codelet_list[codelet_list_idx];
        ಧ್ರುವ FFTXCodelet *cd = ರಿಕ್ತ;

        ಯಾವತ್ ((cd = *list++)) {
            /* Check if the type matches */
            ಯದಿ (cd->type != TX_TYPE_ANY && type != cd->type)
                ಅನುವರ್ತ;

            /* Check direction for non-orthogonal codelets */
            ಯದಿ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ಅನುವರ್ತ;

            /* Check if the requested flags match from both sides */
            ಯದಿ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                ಅನುವರ್ತ;

            /* Check if length is supported */
            ಯದಿ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                ಅನುವರ್ತ;

            /* Check if the CPU supports the required ISA */
            ಯದಿ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ಅನುವರ್ತ;

            /* Check for factors */
            ಯದಿ (!check_cd_factors(cd, len))
                ಅನುವರ್ತ;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     ಪರಿಮಾಣ(*cd_tmp) * (nb_cd_matches + 1));
            ಯದಿ (!cd_tmp) {
                av_free(cd_matches);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ಯದಿ !CONFIG_SMALL
    /* Print debugging info */
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprintf(&bp, "For transform of length %i, %s, ", len,
               inv ? "inverse" : "forward");
    print_type(&bp, type);
    av_bprintf(&bp, ", ");
    print_flags(&bp, flags);
    av_bprintf(&bp, ", found %i matches%s", nb_cd_matches,
               nb_cd_matches ? ":" : ".");
#endif

    /* No matches found */
    ಯದಿ (!nb_cd_matches)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#ಯದಿ !CONFIG_SMALL
    av_log(ರಿಕ್ತ, AV_LOG_TRACE, "%s\n", bp.str);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_cd_matches; i++) {
        av_log(ರಿಕ್ತ, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    ಯದಿ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*ಪರಿಮಾಣ(*sub));
        ಯದಿ (!sub) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ end;
        }
    }

    /* Attempt to initialize each */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_cd_matches; i++) {
        ಧ್ರುವ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        ಯದಿ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ಯದಿ (ret >= 0) {
            ಯದಿ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*ಪರಿಮಾಣ(*sctx->map));
                ಯದಿ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    ಗಚ್ಛ end;
                }

                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ಅನ್ಯಥಾ ಯದಿ (opts && (opts->map_dir != sctx->map_dir)) {
                ಪೂರ್ಣಾಙ್ಕ *tmp = av_malloc(len*ಪರಿಮಾಣ(*sctx->map));
                ಯದಿ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    ಗಚ್ಛ end;
                }

                memcpy(tmp, sctx->map, len*ಪರಿಮಾಣ(*sctx->map));

                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            ಗಚ್ಛ end;
        }

        s->fn[s->nb_sub] = ರಿಕ್ತ;
        s->cd[s->nb_sub] = ರಿಕ್ತ;

        reset_ctx(sctx, 0);
        ಯದಿ (ret == AVERROR(ENOMEM))
            ಭಙ್ಗ;
    }

    ಯದಿ (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    ಪ್ರತ್ಯಾಗಮ ret;
}

av_cold ಪೂರ್ಣಾಙ್ಕ av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ಗಣನಾ AVTXType type,
                       ಪೂರ್ಣಾಙ್ಕ inv, ಪೂರ್ಣಾಙ್ಕ len, ಧ್ರುವ ಶೂನ್ಯ *scale, uint64_t flags)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    AVTXContext tmp = { 0 };
    ಧ್ರುವ ದ್ವಿಗುಣ default_scale_d = 1.0;
    ಧ್ರುವ ಭಿನ್ನ  default_scale_f = 1.0f;

    ಯದಿ (!len || type >= AV_TX_NB || !ctx || !tx)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ಯದಿ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    ಯದಿ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ಅನ್ಯಥಾ ಯದಿ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ರಿಕ್ತ, len, inv, scale);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ಯದಿ !CONFIG_SMALL
    av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    ಪ್ರತ್ಯಾಗಮ ret;
}
