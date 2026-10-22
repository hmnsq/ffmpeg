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

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "intmath.h"
#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "qsort.h"
#അന്തര്ഭാവ "bprint.h"

#അന്തര്ഭാവ "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
സ്ഥിതം av_always_inline പൂർണ്ണസംഖ്യ mulinv(പൂർണ്ണസംഖ്യ n, പൂർണ്ണസംഖ്യ m)
{
    n = n % m;
    വേണ്ടി (പൂർണ്ണസംഖ്യ x = 1; x < m; x++)
        എങ്കിൽ (((n * x) % m) == 1)
            തിരികെ x;
    av_assert0(0); /* Never reached */
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ ff_tx_gen_pfa_നിവേശം_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            പൂർണ്ണസംഖ്യ d1, പൂർണ്ണസംഖ്യ d2)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ sl = d1*d2;

    s->map = av_malloc(s->len*വലുപ്പം(*s->map));
    എങ്കിൽ (!s->map)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (പൂർണ്ണസംഖ്യ k = 0; k < s->len; k += sl) {
        എങ്കിൽ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ m = 0; m < d2; m++)
                വേണ്ടി (പൂർണ്ണസംഖ്യ n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } അല്ലെങ്കിൽ {
            വേണ്ടി (പൂർണ്ണസംഖ്യ m = 0; m < d2; m++)
                വേണ്ടി (പൂർണ്ണസംഖ്യ n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        എങ്കിൽ (s->inv)
            വേണ്ടി (പൂർണ്ണസംഖ്യ w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(പൂർണ്ണസംഖ്യ, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    തിരികെ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
പൂർണ്ണസംഖ്യ ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               പൂർണ്ണസംഖ്യ inv, പൂർണ്ണസംഖ്യ n, പൂർണ്ണസംഖ്യ m)
{
    പൂർണ്ണസംഖ്യ *in_map, *out_map;
    സ്ഥിരം പൂർണ്ണസംഖ്യ len = n*m;    /* Will not be equal to s->len for MDCTs */
    പൂർണ്ണസംഖ്യ m_inv, n_inv;

    /* Make sure the numbers are coprime */
    എങ്കിൽ (av_gcd(n, m) != 1)
        തിരികെ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    എങ്കിൽ (!(s->map = av_malloc(2*len*വലുപ്പം(*s->map))))
        തിരികെ AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    എങ്കിൽ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < m; j++) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } അല്ലെങ്കിൽ {
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < m; j++) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    എങ്കിൽ (inv) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < m; i++) {
            പൂർണ്ണസംഖ്യ *in = &in_map[i*n + 1]; /* Skip the DC */
            വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(പൂർണ്ണസംഖ്യ, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    തിരികെ 0;
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ split_radix_permutation(പൂർണ്ണസംഖ്യ i, പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ inv)
{
    len >>= 1;
    എങ്കിൽ (len <= 1)
        തിരികെ i & 1;
    എങ്കിൽ (!(i & len))
        തിരികെ split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    തിരികെ split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

പൂർണ്ണസംഖ്യ ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    പൂർണ്ണസംഖ്യ len = s->len;

    എങ്കിൽ (!(s->map = av_malloc(len*വലുപ്പം(*s->map))))
        തിരികെ AVERROR(ENOMEM);

    എങ്കിൽ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } അല്ലെങ്കിൽ {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ ff_tx_gen_inplace_map(AVTXContext *s, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ *src_map, out_map_idx = 0;

    എങ്കിൽ (!s->sub || !s->sub->map)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!(s->map = av_mallocz(len*വലുപ്പം(*s->map))))
        തിരികെ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    വേണ്ടി (പൂർണ്ണസംഖ്യ src = 1; src < s->len; src++) {
        പൂർണ്ണസംഖ്യ dst = src_map[src];
        പൂർണ്ണസംഖ്യ found = 0;

        എങ്കിൽ (dst <= src)
            തുടരുക;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        ചെയ്യുക {
            വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < out_map_idx; j++) {
                എങ്കിൽ (dst == s->map[j]) {
                    found = 1;
                    നിർത്തുക;
                }
            }
            dst = src_map[dst];
        } ആകുമ്പോൾ (dst != src && !found);

        എങ്കിൽ (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം parity_revtab_generator(പൂർണ്ണസംഖ്യ *revtab, പൂർണ്ണസംഖ്യ n, പൂർണ്ണസംഖ്യ inv, പൂർണ്ണസംഖ്യ offset,
                                    പൂർണ്ണസംഖ്യ is_dual, പൂർണ്ണസംഖ്യ dual_മുകളിലെ, പൂർണ്ണസംഖ്യ len,
                                    പൂർണ്ണസംഖ്യ basis, പൂർണ്ണസംഖ്യ dual_stride, പൂർണ്ണസംഖ്യ inv_lookup)
{
    len >>= 1;

    എങ്കിൽ (len <= basis) {
        പൂർണ്ണസംഖ്യ k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_മുകളിലെ = is_dual & dual_മുകളിലെ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_മുകളിലെ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_മുകളിലെ)*len + dual_മുകളിലെ*len;

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            എങ്കിൽ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } അല്ലെങ്കിൽ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            എങ്കിൽ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        തിരികെ;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

പൂർണ്ണസംഖ്യ ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ inv,
                                        FFTXCodeletOptions *opts,
                                        പൂർണ്ണസംഖ്യ basis, പൂർണ്ണസംഖ്യ dual_stride)
{
    basis >>= 1;
    എങ്കിൽ (len < basis)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!(s->map = av_mallocz(len*വലുപ്പം(*s->map))))
        തിരികെ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം reset_ctx(AVTXContext *s, പൂർണ്ണസംഖ്യ free_sub)
{
    എങ്കിൽ (!s)
        തിരികെ;

    എങ്കിൽ (s->sub)
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    എങ്കിൽ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    എങ്കിൽ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ശൂന്യ;
    memset(s->fn, 0, വലുപ്പം(s->fn));
}

ശൂന്യം ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold ശൂന്യം av_tx_uninit(AVTXContext **ctx)
{
    എങ്കിൽ (!(*ctx))
        തിരികെ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

സ്ഥിതം av_cold പൂർണ്ണസംഖ്യ ff_tx_null_init(AVTXContext *s, സ്ഥിരം FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ inv, സ്ഥിരം ശൂന്യം *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    എങ്കിൽ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        തിരികെ AVERROR(EINVAL);
    തിരികെ 0;
}

/* Null transform when the length is 1 */
സ്ഥിതം ശൂന്യം ff_tx_null(AVTXContext *s, ശൂന്യം *_out, ശൂന്യം *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

സ്ഥിതം സ്ഥിരം FFTXCodelet ff_tx_null_def = {
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

സ്ഥിതം സ്ഥിരം FFTXCodelet * സ്ഥിരം ff_tx_null_list[] = {
    &ff_tx_null_def,
    ശൂന്യ,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
സ്ഥിതം സ്ഥിരം FFTXCodelet * സ്ഥിരം * സ്ഥിരം codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#എങ്കിൽ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#എങ്കിൽ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ codelet_list_അക്കം = FF_ARRAY_ELEMS(codelet_list);

സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

സ്ഥിതം പൂർണ്ണസംഖ്യ get_codelet_prio(സ്ഥിരം FFTXCodelet *cd, പൂർണ്ണസംഖ്യ cpu_flags, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ prio = cd->prio;
    പൂർണ്ണസംഖ്യ max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        എങ്കിൽ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    എങ്കിൽ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    എങ്കിൽ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    എങ്കിൽ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    എങ്കിൽ (max_factor)
        prio += 16*max_factor;

    തിരികെ prio;
}

തരനിർവചനം ഘടന FFTXLenDecomp {
    പൂർണ്ണസംഖ്യ len;
    പൂർണ്ണസംഖ്യ len2;
    പൂർണ്ണസംഖ്യ prio;
    സ്ഥിരം FFTXCodelet *cd;
} FFTXLenDecomp;

സ്ഥിതം പൂർണ്ണസംഖ്യ cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    തിരികെ FFDIFFSIGN(b->prio, a->prio);
}

പൂർണ്ണസംഖ്യ ff_tx_decompose_length(പൂർണ്ണസംഖ്യ dst[TX_MAX_DECOMPOSITIONS], എണ്ണൽ AVTXType type,
                           പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ inv)
{
    പൂർണ്ണസംഖ്യ nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    പൂർണ്ണസംഖ്യ codelet_list_idx = codelet_list_അക്കം;

    സ്ഥിരം പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ആകുമ്പോൾ (codelet_list_idx--) {
        സ്ഥിരം FFTXCodelet * സ്ഥിരം * list = codelet_list[codelet_list_idx];
        സ്ഥിരം FFTXCodelet *cd = ശൂന്യ;

        ആകുമ്പോൾ ((cd = *list++)) {
            പൂർണ്ണസംഖ്യ fl = len;
            പൂർണ്ണസംഖ്യ skip = 0, prio;
            പൂർണ്ണസംഖ്യ factors_product = 1, factors_mod = 0;

            എങ്കിൽ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                പോകുക sort;

            /* Check if the type matches */
            എങ്കിൽ (cd->type != TX_TYPE_ANY && type != cd->type)
                തുടരുക;

            /* Check direction for non-orthogonal codelets */
            എങ്കിൽ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                തുടരുക;

            /* Check if the CPU supports the required ISA */
            എങ്കിൽ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                തുടരുക;

            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < TX_MAX_FACTORS; i++) {
                എങ്കിൽ (!cd->factors[i] || (fl == 1))
                    നിർത്തുക;

                എങ്കിൽ (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } അല്ലെങ്കിൽ എങ്കിൽ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    എങ്കിൽ (cd->factors[i] == 2) {
                        പൂർണ്ണസംഖ്യ b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } അല്ലെങ്കിൽ {
                        ചെയ്യുക {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } ആകുമ്പോൾ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            എങ്കിൽ ((factors_mod < cd->nb_factors) || (len == factors_product))
                തുടരുക;

            എങ്കിൽ (av_gcd(factors_product, fl) != 1)
                തുടരുക;

            /* Check if length is supported and factorization was successful */
            എങ്കിൽ ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                തുടരുക;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_decomp; i++) {
                എങ്കിൽ (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    എങ്കിൽ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    നിർത്തുക;
                }
            }

            /* Add decomposition if unique */
            എങ്കിൽ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    എങ്കിൽ (!nb_decomp)
        തിരികെ AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_decomp; i++) {
        എങ്കിൽ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        അല്ലെങ്കിൽ
            dst[i] = ld[i].len;
    }

    തിരികെ nb_decomp;
}

പൂർണ്ണസംഖ്യ ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*വലുപ്പം(*s->map));
    എങ്കിൽ (!s->map)
        തിരികെ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    എങ്കിൽ (s->inv) /* Reversing the ACs flips the transform direction */
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    അല്ലെങ്കിൽ
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    തിരികെ 0;
}

#എങ്കിൽ !CONFIG_SMALL
സ്ഥിതം ശൂന്യം print_flags(AVBPrint *bp, uint64_t f)
{
    പൂർണ്ണസംഖ്യ prev = 0;
    സ്ഥിരം അക്ഷരം *sep = ", ";
    av_bprintf(bp, "flags: [");
    എങ്കിൽ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    എങ്കിൽ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    എങ്കിൽ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    എങ്കിൽ ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    എങ്കിൽ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    എങ്കിൽ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    എങ്കിൽ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    എങ്കിൽ ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    എങ്കിൽ ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    എങ്കിൽ ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    എങ്കിൽ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

സ്ഥിതം ശൂന്യം print_type(AVBPrint *bp, എണ്ണൽ AVTXType type)
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

സ്ഥിതം ശൂന്യം print_cd_info(സ്ഥിരം FFTXCodelet *cd, പൂർണ്ണസംഖ്യ prio, പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ print_prio,
                          പൂർണ്ണസംഖ്യ log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    എങ്കിൽ (!len) {
        എങ്കിൽ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        എങ്കിൽ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        അല്ലെങ്കിൽ
            av_bprintf(&bp, "%i", cd->max_len);
    } അല്ലെങ്കിൽ {
        av_bprintf(&bp, "%i", len);
    }

    എങ്കിൽ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        എങ്കിൽ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        അല്ലെങ്കിൽ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < TX_MAX_FACTORS; i++) {
            എങ്കിൽ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            എങ്കിൽ (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            അല്ലെങ്കിൽ എങ്കിൽ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            അല്ലെങ്കിൽ
                നിർത്തുക;
        }

        av_bprintf(&bp, "], ");
    } അല്ലെങ്കിൽ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    എങ്കിൽ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ശൂന്യ, log_level, "%s\n", bp.str);
}

സ്ഥിതം ശൂന്യം print_tx_structure(AVTXContext *s, പൂർണ്ണസംഖ്യ depth)
{
    സ്ഥിരം FFTXCodelet *cd = s->cd_self;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i <= depth; i++)
        av_log(ശൂന്യ, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

തരനിർവചനം ഘടന TXCodeletMatch {
    സ്ഥിരം FFTXCodelet *cd;
    പൂർണ്ണസംഖ്യ prio;
} TXCodeletMatch;

സ്ഥിതം പൂർണ്ണസംഖ്യ cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    തിരികെ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ check_cd_factors(സ്ഥിരം FFTXCodelet *cd, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ matches = 0, any_flag = 0;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < TX_MAX_FACTORS; i++) {
        പൂർണ്ണസംഖ്യ factor = cd->factors[i];

        എങ്കിൽ (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            തുടരുക;
        } അല്ലെങ്കിൽ എങ്കിൽ (len <= 1 || !factor) {
            നിർത്തുക;
        } അല്ലെങ്കിൽ എങ്കിൽ (factor == 2) { /* Fast path */
            പൂർണ്ണസംഖ്യ bits_2 = ff_ctz(len);
            എങ്കിൽ (!bits_2)
                തുടരുക; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } അല്ലെങ്കിൽ {
            പൂർണ്ണസംഖ്യ res = len % factor;
            എങ്കിൽ (res)
                തുടരുക; /* Factor not supported */

            ആകുമ്പോൾ (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    തിരികെ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold പൂർണ്ണസംഖ്യ ff_tx_init_subtx(AVTXContext *s, എണ്ണൽ AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ inv, സ്ഥിരം ശൂന്യം *scale)
{
    പൂർണ്ണസംഖ്യ ret = 0;
    AVTXContext *sub = ശൂന്യ;
    TXCodeletMatch *cd_tmp, *cd_matches = ശൂന്യ;
    unsigned പൂർണ്ണസംഖ്യ cd_matches_size = 0;
    പൂർണ്ണസംഖ്യ codelet_list_idx = codelet_list_അക്കം;
    പൂർണ്ണസംഖ്യ nb_cd_matches = 0;
#എങ്കിൽ !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    സ്ഥിരം പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    എങ്കിൽ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    എങ്കിൽ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    എങ്കിൽ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ആകുമ്പോൾ (codelet_list_idx--) {
        സ്ഥിരം FFTXCodelet * സ്ഥിരം * list = codelet_list[codelet_list_idx];
        സ്ഥിരം FFTXCodelet *cd = ശൂന്യ;

        ആകുമ്പോൾ ((cd = *list++)) {
            /* Check if the type matches */
            എങ്കിൽ (cd->type != TX_TYPE_ANY && type != cd->type)
                തുടരുക;

            /* Check direction for non-orthogonal codelets */
            എങ്കിൽ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                തുടരുക;

            /* Check if the requested flags match from both sides */
            എങ്കിൽ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                തുടരുക;

            /* Check if length is supported */
            എങ്കിൽ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                തുടരുക;

            /* Check if the CPU supports the required ISA */
            എങ്കിൽ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                തുടരുക;

            /* Check for factors */
            എങ്കിൽ (!check_cd_factors(cd, len))
                തുടരുക;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     വലുപ്പം(*cd_tmp) * (nb_cd_matches + 1));
            എങ്കിൽ (!cd_tmp) {
                av_free(cd_matches);
                തിരികെ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#എങ്കിൽ !CONFIG_SMALL
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
    എങ്കിൽ (!nb_cd_matches)
        തിരികെ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#എങ്കിൽ !CONFIG_SMALL
    av_log(ശൂന്യ, AV_LOG_TRACE, "%s\n", bp.str);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_cd_matches; i++) {
        av_log(ശൂന്യ, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    എങ്കിൽ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*വലുപ്പം(*sub));
        എങ്കിൽ (!sub) {
            ret = AVERROR(ENOMEM);
            പോകുക end;
        }
    }

    /* Attempt to initialize each */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_cd_matches; i++) {
        സ്ഥിരം FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        എങ്കിൽ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        എങ്കിൽ (ret >= 0) {
            എങ്കിൽ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*വലുപ്പം(*sctx->map));
                എങ്കിൽ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    പോകുക end;
                }

                വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < len; i++)
                    sctx->map[i] = i;
            } അല്ലെങ്കിൽ എങ്കിൽ (opts && (opts->map_dir != sctx->map_dir)) {
                പൂർണ്ണസംഖ്യ *tmp = av_malloc(len*വലുപ്പം(*sctx->map));
                എങ്കിൽ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    പോകുക end;
                }

                memcpy(tmp, sctx->map, len*വലുപ്പം(*sctx->map));

                വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            പോകുക end;
        }

        s->fn[s->nb_sub] = ശൂന്യ;
        s->cd[s->nb_sub] = ശൂന്യ;

        reset_ctx(sctx, 0);
        എങ്കിൽ (ret == AVERROR(ENOMEM))
            നിർത്തുക;
    }

    എങ്കിൽ (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    തിരികെ ret;
}

av_cold പൂർണ്ണസംഖ്യ av_tx_init(AVTXContext **ctx, av_tx_fn *tx, എണ്ണൽ AVTXType type,
                       പൂർണ്ണസംഖ്യ inv, പൂർണ്ണസംഖ്യ len, സ്ഥിരം ശൂന്യം *scale, uint64_t flags)
{
    പൂർണ്ണസംഖ്യ ret;
    AVTXContext tmp = { 0 };
    സ്ഥിരം ഇരട്ട default_scale_d = 1.0;
    സ്ഥിരം ദശാംശം  default_scale_f = 1.0f;

    എങ്കിൽ (!len || type >= AV_TX_NB || !ctx || !tx)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    എങ്കിൽ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    എങ്കിൽ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    അല്ലെങ്കിൽ എങ്കിൽ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ശൂന്യ, len, inv, scale);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#എങ്കിൽ !CONFIG_SMALL
    av_log(ശൂന്യ, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    തിരികെ ret;
}
