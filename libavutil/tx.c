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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intmath.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "qsort.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "tx_priv.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ਸਥਿਰ av_always_inline ਪੂਰਨ mulinv(ਪੂਰਨ n, ਪੂਰਨ m)
{
    n = n % m;
    ਲਈ (ਪੂਰਨ x = 1; x < m; x++)
        ਜੇ (((n * x) % m) == 1)
            ਵਾਪਸ x;
    av_assert0(0); /* Never reached */
    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_tx_gen_pfa_ਨਿਵੇਸ਼_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            ਪੂਰਨ d1, ਪੂਰਨ d2)
{
    ਅਚਲ ਪੂਰਨ sl = d1*d2;

    s->map = av_malloc(s->len*ਆਕਾਰ(*s->map));
    ਜੇ (!s->map)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (ਪੂਰਨ k = 0; k < s->len; k += sl) {
        ਜੇ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ਲਈ (ਪੂਰਨ m = 0; m < d2; m++)
                ਲਈ (ਪੂਰਨ n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ਨਹੀਂਤਾਂ {
            ਲਈ (ਪੂਰਨ m = 0; m < d2; m++)
                ਲਈ (ਪੂਰਨ n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ਜੇ (s->inv)
            ਲਈ (ਪੂਰਨ w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(ਪੂਰਨ, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ਵਾਪਸ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
ਪੂਰਨ ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               ਪੂਰਨ inv, ਪੂਰਨ n, ਪੂਰਨ m)
{
    ਪੂਰਨ *ਵਿੱਚ_map, *ਬਾਹਰਲਾ_map;
    ਅਚਲ ਪੂਰਨ len = n*m;    /* Will not be equal to s->len for MDCTs */
    ਪੂਰਨ m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ਜੇ (av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(n, m) != 1)
        ਵਾਪਸ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ਜੇ (!(s->map = av_malloc(2*len*ਆਕਾਰ(*s->map))))
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਿੱਚ_map  = s->map;
    ਬਾਹਰਲਾ_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ਜੇ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ਲਈ (ਪੂਰਨ j = 0; j < m; j++) {
            ਲਈ (ਪੂਰਨ i = 0; i < n; i++) {
                ਵਿੱਚ_map[(i*m + j*n) % len] = j*n + i;
                ਬਾਹਰਲਾ_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ j = 0; j < m; j++) {
            ਲਈ (ਪੂਰਨ i = 0; i < n; i++) {
                ਵਿੱਚ_map[j*n + i] = (i*m + j*n) % len;
                ਬਾਹਰਲਾ_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ਜੇ (inv) {
        ਲਈ (ਪੂਰਨ i = 0; i < m; i++) {
            ਪੂਰਨ *ਵਿੱਚ_2 = &ਵਿੱਚ_map[i*n + 1]; /* Skip the DC */
            ਲਈ (ਪੂਰਨ j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(ਪੂਰਨ, ਵਿੱਚ_2[j], ਵਿੱਚ_2[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ਵੰਡੋ_radix_permutation(ਪੂਰਨ i, ਪੂਰਨ len, ਪੂਰਨ inv)
{
    len >>= 1;
    ਜੇ (len <= 1)
        ਵਾਪਸ i & 1;
    ਜੇ (!(i & len))
        ਵਾਪਸ ਵੰਡੋ_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ਵਾਪਸ ਵੰਡੋ_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

ਪੂਰਨ ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    ਪੂਰਨ len = s->len;

    ਜੇ (!(s->map = av_malloc(len*ਆਕਾਰ(*s->map))))
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ਲਈ (ਪੂਰਨ i = 0; i < s->len; i++)
            s->map[-ਵੰਡੋ_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ i = 0; i < s->len; i++)
            s->map[i] = -ਵੰਡੋ_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_tx_gen_inplace_map(AVTXContext *s, ਪੂਰਨ len)
{
    ਪੂਰਨ *src_map, ਬਾਹਰਲਾ_map_idx = 0;

    ਜੇ (!s->sub || !s->sub->map)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!(s->map = av_mallocz(len*ਆਕਾਰ(*s->map))))
        ਵਾਪਸ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ਲਈ (ਪੂਰਨ src = 1; src < s->len; src++) {
        ਪੂਰਨ dst = src_map[src];
        ਪੂਰਨ ਮਿਲਿਆ = 0;

        ਜੇ (dst <= src)
            ਜਾਰੀ;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        ਕਰੋ {
            ਲਈ (ਪੂਰਨ j = 0; j < ਬਾਹਰਲਾ_map_idx; j++) {
                ਜੇ (dst == s->map[j]) {
                    ਮਿਲਿਆ = 1;
                    ਰੋਕੋ;
                }
            }
            dst = src_map[dst];
        } ਜਦੋਂ (dst != src && !ਮਿਲਿਆ);

        ਜੇ (!ਮਿਲਿਆ)
            s->map[ਬਾਹਰਲਾ_map_idx++] = src;
    }

    s->map[ਬਾਹਰਲਾ_map_idx++] = 0;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ parity_revtab_generator(ਪੂਰਨ *revtab, ਪੂਰਨ n, ਪੂਰਨ inv, ਪੂਰਨ ਵਿੱਥ,
                                    ਪੂਰਨ is_dual, ਪੂਰਨ dual_ਉੱਚਾ, ਪੂਰਨ len,
                                    ਪੂਰਨ basis, ਪੂਰਨ dual_stride, ਪੂਰਨ inv_lookup)
{
    len >>= 1;

    ਜੇ (len <= basis) {
        ਪੂਰਨ k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ਉੱਚਾ = is_dual & dual_ਉੱਚਾ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = ਵਿੱਥ + dual_ਉੱਚਾ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ਉੱਚਾ)*len + dual_ਉੱਚਾ*len;

        ਲਈ (ਪੂਰਨ i = 0; i < len; i++) {
            k1 = -ਵੰਡੋ_radix_permutation(ਵਿੱਥ + i*2 + 0, n, inv) & (n - 1);
            k2 = -ਵੰਡੋ_radix_permutation(ਵਿੱਥ + i*2 + 1, n, inv) & (n - 1);
            ਜੇ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ਨਹੀਂਤਾਂ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ਜੇ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ਵਾਪਸ;
    }

    parity_revtab_generator(revtab, n, inv, ਵਿੱਥ,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, ਵਿੱਥ + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, ਵਿੱਥ + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

ਪੂਰਨ ff_tx_gen_ਵੰਡੋ_radix_parity_revtab(AVTXContext *s, ਪੂਰਨ len, ਪੂਰਨ inv,
                                        FFTXCodeletOptions *opts,
                                        ਪੂਰਨ basis, ਪੂਰਨ dual_stride)
{
    basis >>= 1;
    ਜੇ (len < basis)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!(s->map = av_mallocz(len*ਆਕਾਰ(*s->map))))
        ਵਾਪਸ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ reset_ctx(AVTXContext *s, ਪੂਰਨ free_sub)
{
    ਜੇ (!s)
        ਵਾਪਸ;

    ਜੇ (s->sub)
        ਲਈ (ਪੂਰਨ i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ਜੇ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ਜੇ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->ਘਾਤਾਂਕ);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ਨਿਰਾ;
    memset(s->fn, 0, ਆਕਾਰ(s->fn));
}

ਖਾਲੀ ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold ਖਾਲੀ av_tx_uninit(AVTXContext **ctx)
{
    ਜੇ (!(*ctx))
        ਵਾਪਸ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ਸਥਿਰ av_cold ਪੂਰਨ ff_tx_null_init(AVTXContext *s, ਅਚਲ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ਜੇ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ਵਾਪਸ AVERROR(EINVAL);
    ਵਾਪਸ 0;
}

/* Null transform when the length is 1 */
ਸਥਿਰ ਖਾਲੀ ff_tx_null(AVTXContext *s, ਖਾਲੀ *ਬਾਹਰਲਾ_3, ਖਾਲੀ *ਵਿੱਚ_4, ptrdiff_t stride)
{
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ਬਾਹਰਲਾ_3, ਵਿੱਚ_4, stride);
}

ਸਥਿਰ ਅਚਲ FFTXCodelet ff_tx_null_def = {
    .name       = NULL_IF_CONFIG_SMALL("null"),
    .function   = ff_tx_null,
    .type       = TX_TYPE_ANY,
    .flags      = AV_TX_UNALIGNED | FF_TX_ALIGNED |
                  FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ | AV_TX_INPLACE,
    .factors[0] = TX_ਗੁਣਕ_ANY,
    .min_len    = 1,
    .max_len    = 1,
    .init       = ff_tx_null_init,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MAX,
};

ਸਥਿਰ ਅਚਲ FFTXCodelet * ਅਚਲ ff_tx_null_list[] = {
    &ff_tx_null_def,
    ਨਿਰਾ,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ਸਥਿਰ ਅਚਲ FFTXCodelet * ਅਚਲ * ਅਚਲ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#ਜੇ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#ਜੇ_ਅੰਤ
#ਜੇ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#ਜੇ_ਅੰਤ
};
ਸਥਿਰ ਅਚਲ ਪੂਰਨ codelet_list_ਅੰਕ = FF_ARRAY_ELEMS(codelet_list);

ਸਥਿਰ ਅਚਲ ਪੂਰਨ cpu_slow_ਨਕਾਬ = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ਸਥਿਰ ਅਚਲ ਪੂਰਨ cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ਸਥਿਰ ਪੂਰਨ get_codelet_prio(ਅਚਲ FFTXCodelet *cd, ਪੂਰਨ cpu_flags, ਪੂਰਨ len)
{
    ਪੂਰਨ prio = cd->prio;
    ਪੂਰਨ max_ਗੁਣਕ = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ਜੇ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ਜੇ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ਜੇ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ਜੇ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ਲਈ (ਪੂਰਨ i = 0; i < TX_MAX_SUB; i++)
        max_ਗੁਣਕ = FFMAX(cd->factors[i], max_ਗੁਣਕ);
    ਜੇ (max_ਗੁਣਕ)
        prio += 16*max_ਗੁਣਕ;

    ਵਾਪਸ prio;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFTXLenDecomp {
    ਪੂਰਨ len;
    ਪੂਰਨ len2;
    ਪੂਰਨ prio;
    ਅਚਲ FFTXCodelet *cd;
} FFTXLenDecomp;

ਸਥਿਰ ਪੂਰਨ cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ਵਾਪਸ FFDIFFSIGN(b->prio, a->prio);
}

ਪੂਰਨ ff_tx_decompose_ਲੰਮਾਈ(ਪੂਰਨ dst[TX_MAX_DECOMPOSITIONS], ਗਿਣਤੀ AVTXType type,
                           ਪੂਰਨ len, ਪੂਰਨ inv)
{
    ਪੂਰਨ nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    ਪੂਰਨ codelet_list_idx = codelet_list_ਅੰਕ;

    ਅਚਲ ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ਜਦੋਂ (codelet_list_idx--) {
        ਅਚਲ FFTXCodelet * ਅਚਲ * list = codelet_list[codelet_list_idx];
        ਅਚਲ FFTXCodelet *cd = ਨਿਰਾ;

        ਜਦੋਂ ((cd = *list++)) {
            ਪੂਰਨ fl = len;
            ਪੂਰਨ skip = 0, prio;
            ਪੂਰਨ factors_ਗੁਣਨਫਲ = 1, factors_mod = 0;

            ਜੇ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                ਜਾਓ ਛਾਂਟੋ;

            /* Check if the type matches */
            ਜੇ (cd->type != TX_TYPE_ANY && type != cd->type)
                ਜਾਰੀ;

            /* Check direction for non-orthogonal codelets */
            ਜੇ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_ਭਰਿਆ_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY)) && inv))
                ਜਾਰੀ;

            /* Check if the CPU supports the required ISA */
            ਜੇ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ਨਕਾਬ)))
                ਜਾਰੀ;

            ਲਈ (ਪੂਰਨ i = 0; i < TX_MAX_FACTORS; i++) {
                ਜੇ (!cd->factors[i] || (fl == 1))
                    ਰੋਕੋ;

                ਜੇ (cd->factors[i] == TX_ਗੁਣਕ_ANY) {
                    factors_mod++;
                    factors_ਗੁਣਨਫਲ *= fl;
                } ਨਹੀਂਤਾਂ ਜੇ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ਜੇ (cd->factors[i] == 2) {
                        ਪੂਰਨ b = ff_ctz(fl);
                        fl >>= b;
                        factors_ਗੁਣਨਫਲ <<= b;
                    } ਨਹੀਂਤਾਂ {
                        ਕਰੋ {
                            fl /= cd->factors[i];
                            factors_ਗੁਣਨਫਲ *= cd->factors[i];
                        } ਜਦੋਂ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ਜੇ ((factors_mod < cd->nb_factors) || (len == factors_ਗੁਣਨਫਲ))
                ਜਾਰੀ;

            ਜੇ (av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(factors_ਗੁਣਨਫਲ, fl) != 1)
                ਜਾਰੀ;

            /* Check if length is supported and factorization was successful */
            ਜੇ ((factors_ਗੁਣਨਫਲ < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_ਗੁਣਨਫਲ > cd->max_len)))
                ਜਾਰੀ;

            prio = get_codelet_prio(cd, cpu_flags, factors_ਗੁਣਨਫਲ) * factors_ਗੁਣਨਫਲ;

            /* Check for duplicates */
            ਲਈ (ਪੂਰਨ i = 0; i < nb_decomp; i++) {
                ਜੇ (factors_ਗੁਣਨਫਲ == ld[i].len) {
                    /* Update priority if new one is higher */
                    ਜੇ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ਰੋਕੋ;
                }
            }

            /* Add decomposition if unique */
            ਜੇ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_ਗੁਣਨਫਲ;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ਜੇ (!nb_decomp)
        ਵਾਪਸ AVERROR(EINVAL);

ਛਾਂਟੋ:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ਲਈ (ਪੂਰਨ i = 0; i < nb_decomp; i++) {
        ਜੇ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ਨਹੀਂਤਾਂ
            dst[i] = ld[i].len;
    }

    ਵਾਪਸ nb_decomp;
}

ਪੂਰਨ ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*ਆਕਾਰ(*s->map));
    ਜੇ (!s->map)
        ਵਾਪਸ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ਜੇ (s->inv) /* Reversing the ACs flips the transform direction */
        ਲਈ (ਪੂਰਨ i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ਨਹੀਂਤਾਂ
        ਲਈ (ਪੂਰਨ i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ਵਾਪਸ 0;
}

#ਜੇ !CONFIG_SMALL
ਸਥਿਰ ਖਾਲੀ print_flags(AVBPrint *bp, uint64_t f)
{
    ਪੂਰਨ prev = 0;
    ਅਚਲ ਅੱਖਰ *sep = ", ";
    av_bprintf(bp, "flags: [");
    ਜੇ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ਜੇ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ਜੇ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ਜੇ ((f & FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ਜੇ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ਜੇ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ਜੇ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ਜੇ ((f & AV_TX_ਭਰਿਆ_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ਜੇ ((f & AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ਜੇ ((f & AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ਜੇ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ਸਥਿਰ ਖਾਲੀ print_type(AVBPrint *bp, ਗਿਣਤੀ AVTXType type)
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

ਸਥਿਰ ਖਾਲੀ print_cd_info(ਅਚਲ FFTXCodelet *cd, ਪੂਰਨ prio, ਪੂਰਨ len, ਪੂਰਨ print_prio,
                          ਪੂਰਨ log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ਜੇ (!len) {
        ਜੇ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ਜੇ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ਨਹੀਂਤਾਂ
            av_bprintf(&bp, "%i", cd->max_len);
    } ਨਹੀਂਤਾਂ {
        av_bprintf(&bp, "%i", len);
    }

    ਜੇ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ਜੇ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ਨਹੀਂਤਾਂ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ਲਈ (ਪੂਰਨ i = 0; i < TX_MAX_FACTORS; i++) {
            ਜੇ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ਜੇ (cd->factors[i] == TX_ਗੁਣਕ_ANY)
                av_bprintf(&bp, "any");
            ਨਹੀਂਤਾਂ ਜੇ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ਨਹੀਂਤਾਂ
                ਰੋਕੋ;
        }

        av_bprintf(&bp, "], ");
    } ਨਹੀਂਤਾਂ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ਜੇ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ਨਿਰਾ, log_level, "%s\n", bp.str);
}

ਸਥਿਰ ਖਾਲੀ print_tx_structure(AVTXContext *s, ਪੂਰਨ ਡੂੰਘਾਈ)
{
    ਅਚਲ FFTXCodelet *cd = s->cd_self;

    ਲਈ (ਪੂਰਨ i = 0; i <= ਡੂੰਘਾਈ; i++)
        av_log(ਨਿਰਾ, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ਲਈ (ਪੂਰਨ i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], ਡੂੰਘਾਈ + 1);
}
#ਜੇ_ਅੰਤ /* CONFIG_SMALL */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ TXCodelet_ਮੇਲ {
    ਅਚਲ FFTXCodelet *cd;
    ਪੂਰਨ prio;
} TXCodelet_ਮੇਲ;

ਸਥਿਰ ਪੂਰਨ cmp_matches(TXCodelet_ਮੇਲ *a, TXCodelet_ਮੇਲ *b)
{
    ਵਾਪਸ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ check_cd_factors(ਅਚਲ FFTXCodelet *cd, ਪੂਰਨ len)
{
    ਪੂਰਨ matches = 0, any_flag = 0;

    ਲਈ (ਪੂਰਨ i = 0; i < TX_MAX_FACTORS; i++) {
        ਪੂਰਨ ਗੁਣਕ = cd->factors[i];

        ਜੇ (ਗੁਣਕ == TX_ਗੁਣਕ_ANY) {
            any_flag = 1;
            matches++;
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ ਜੇ (len <= 1 || !ਗੁਣਕ) {
            ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ ਜੇ (ਗੁਣਕ == 2) { /* Fast path */
            ਪੂਰਨ ਬਿੱਟ_2 = ff_ctz(len);
            ਜੇ (!ਬਿੱਟ_2)
                ਜਾਰੀ; /* Factor not supported */

            len >>= ਬਿੱਟ_2;
            matches++;
        } ਨਹੀਂਤਾਂ {
            ਪੂਰਨ res = len % ਗੁਣਕ;
            ਜੇ (res)
                ਜਾਰੀ; /* Factor not supported */

            ਜਦੋਂ (!res) {
                len /= ਗੁਣਕ;
                res = len % ਗੁਣਕ;
            }
            matches++;
        }
    }

    ਵਾਪਸ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold ਪੂਰਨ ff_tx_init_subtx(AVTXContext *s, ਗਿਣਤੀ AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ਪੂਰਨ len, ਪੂਰਨ inv, ਅਚਲ ਖਾਲੀ *scale)
{
    ਪੂਰਨ ret = 0;
    AVTXContext *sub = ਨਿਰਾ;
    TXCodelet_ਮੇਲ *cd_tmp, *cd_matches = ਨਿਰਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cd_matches_ਮਾਪ = 0;
    ਪੂਰਨ codelet_list_idx = codelet_list_ਅੰਕ;
    ਪੂਰਨ nb_cd_matches = 0;
#ਜੇ !CONFIG_SMALL
    AVBPrint bp;
#ਜੇ_ਅੰਤ

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ਅਚਲ ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_ਨਕਾਬ = AV_TX_ਭਰਿਆ_IMDCT |
                            AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL |
                            AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ਜੇ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ਜੇ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ);
    ਜੇ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ਜਦੋਂ (codelet_list_idx--) {
        ਅਚਲ FFTXCodelet * ਅਚਲ * list = codelet_list[codelet_list_idx];
        ਅਚਲ FFTXCodelet *cd = ਨਿਰਾ;

        ਜਦੋਂ ((cd = *list++)) {
            /* Check if the type matches */
            ਜੇ (cd->type != TX_TYPE_ANY && type != cd->type)
                ਜਾਰੀ;

            /* Check direction for non-orthogonal codelets */
            ਜੇ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_ਭਰਿਆ_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ਮੰਜ਼ਿਲ_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_ਮੰਜ਼ਿਲ_IMAGINARY)) && inv))
                ਜਾਰੀ;

            /* Check if the requested flags match from both sides */
            ਜੇ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_ਨਕਾਬ & cd->flags) != (req_flags & inv_req_ਨਕਾਬ)))
                ਜਾਰੀ;

            /* Check if length is supported */
            ਜੇ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                ਜਾਰੀ;

            /* Check if the CPU supports the required ISA */
            ਜੇ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ਨਕਾਬ)))
                ਜਾਰੀ;

            /* Check for factors */
            ਜੇ (!check_cd_factors(cd, len))
                ਜਾਰੀ;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_ਮਾਪ,
                                     ਆਕਾਰ(*cd_tmp) * (nb_cd_matches + 1));
            ਜੇ (!cd_tmp) {
                av_free(cd_matches);
                ਵਾਪਸ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ਜੇ !CONFIG_SMALL
    /* Print debugging info */
    av_bprint_init(&bp, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);
    av_bprintf(&bp, "For transform of length %i, %s, ", len,
               inv ? "inverse" : "forward");
    print_type(&bp, type);
    av_bprintf(&bp, ", ");
    print_flags(&bp, flags);
    av_bprintf(&bp, ", found %i matches%s", nb_cd_matches,
               nb_cd_matches ? ":" : ".");
#ਜੇ_ਅੰਤ

    /* No matches found */
    ਜੇ (!nb_cd_matches)
        ਵਾਪਸ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodelet_ਮੇਲ, cmp_matches);

#ਜੇ !CONFIG_SMALL
    av_log(ਨਿਰਾ, AV_LOG_TRACE, "%s\n", bp.str);

    ਲਈ (ਪੂਰਨ i = 0; i < nb_cd_matches; i++) {
        av_log(ਨਿਰਾ, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*ਆਕਾਰ(*sub));
        ਜੇ (!sub) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ ਸਿਰਾ;
        }
    }

    /* Attempt to initialize each */
    ਲਈ (ਪੂਰਨ i = 0; i < nb_cd_matches; i++) {
        ਅਚਲ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        ਜੇ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ਜੇ (ret >= 0) {
            ਜੇ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*ਆਕਾਰ(*sctx->map));
                ਜੇ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    ਜਾਓ ਸਿਰਾ;
                }

                ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ਨਹੀਂਤਾਂ ਜੇ (opts && (opts->map_dir != sctx->map_dir)) {
                ਪੂਰਨ *tmp = av_malloc(len*ਆਕਾਰ(*sctx->map));
                ਜੇ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    ਜਾਓ ਸਿਰਾ;
                }

                ਸਮ੍ਰਿਤੀ_ਨਕਲ(tmp, sctx->map, len*ਆਕਾਰ(*sctx->map));

                ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            ਜਾਓ ਸਿਰਾ;
        }

        s->fn[s->nb_sub] = ਨਿਰਾ;
        s->cd[s->nb_sub] = ਨਿਰਾ;

        reset_ctx(sctx, 0);
        ਜੇ (ret == AVERROR(ENOMEM))
            ਰੋਕੋ;
    }

    ਜੇ (!s->nb_sub)
        av_freep(&s->sub);

ਸਿਰਾ:
    av_free(cd_matches);
    ਵਾਪਸ ret;
}

av_cold ਪੂਰਨ av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ਗਿਣਤੀ AVTXType type,
                       ਪੂਰਨ inv, ਪੂਰਨ len, ਅਚਲ ਖਾਲੀ *scale, uint64_t flags)
{
    ਪੂਰਨ ret;
    AVTXContext tmp = { 0 };
    ਅਚਲ ਦੁੱਗਣਾ default_scale_d = 1.0;
    ਅਚਲ ਦਸ਼ਮਲਵ  default_scale_f = 1.0f;

    ਜੇ (!len || type >= AV_TX_NB || !ctx || !tx)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ਜੇ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_ਬਾਹਰਲਾ_ਦਾ_ਰੱਖੋ;

    ਜੇ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ਨਹੀਂਤਾਂ ਜੇ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ਨਿਰਾ, len, inv, scale);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ਜੇ !CONFIG_SMALL
    av_log(ਨਿਰਾ, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ret;
}
