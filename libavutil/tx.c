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

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "intmath.h"
#অন্তর্ভাৱ "cpu.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "qsort.h"
#অন্তর্ভাৱ "bprint.h"

#অন্তর্ভাৱ "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
স্থির av_always_inline পূর্ণাঙ্ক mulinv(পূর্ণাঙ্ক n, পূর্ণাঙ্ক m)
{
    n = n % m;
    বাবে (পূর্ণাঙ্ক x = 1; x < m; x++)
        যদি (((n * x) % m) == 1)
            ঘূৰাই x;
    av_assert0(0); /* Never reached */
    ঘূৰাই 0;
}

পূর্ণাঙ্ক ff_tx_gen_pfa_প্ৰবেশ_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            পূর্ণাঙ্ক d1, পূর্ণাঙ্ক d2)
{
    ধ্রুৱ পূর্ণাঙ্ক sl = d1*d2;

    s->map = av_malloc(s->len*পরিমাণ(*s->map));
    যদি (!s->map)
        ঘূৰাই AVERROR(ENOMEM);

    বাবে (পূর্ণাঙ্ক k = 0; k < s->len; k += sl) {
        যদি (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            বাবে (পূর্ণাঙ্ক m = 0; m < d2; m++)
                বাবে (পূর্ণাঙ্ক n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } অন্যথা {
            বাবে (পূর্ণাঙ্ক m = 0; m < d2; m++)
                বাবে (পূর্ণাঙ্ক n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        যদি (s->inv)
            বাবে (পূর্ণাঙ্ক w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(পূর্ণাঙ্ক, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ঘূৰাই 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
পূর্ণাঙ্ক ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               পূর্ণাঙ্ক inv, পূর্ণাঙ্ক n, পূর্ণাঙ্ক m)
{
    পূর্ণাঙ্ক *in_map, *out_map;
    ধ্রুৱ পূর্ণাঙ্ক len = n*m;    /* Will not be equal to s->len for MDCTs */
    পূর্ণাঙ্ক m_inv, n_inv;

    /* Make sure the numbers are coprime */
    যদি (av_gcd(n, m) != 1)
        ঘূৰাই AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    যদি (!(s->map = av_malloc(2*len*পরিমাণ(*s->map))))
        ঘূৰাই AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    যদি (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        বাবে (পূর্ণাঙ্ক j = 0; j < m; j++) {
            বাবে (পূর্ণাঙ্ক i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } অন্যথা {
        বাবে (পূর্ণাঙ্ক j = 0; j < m; j++) {
            বাবে (পূর্ণাঙ্ক i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    যদি (inv) {
        বাবে (পূর্ণাঙ্ক i = 0; i < m; i++) {
            পূর্ণাঙ্ক *in = &in_map[i*n + 1]; /* Skip the DC */
            বাবে (পূর্ণাঙ্ক j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(পূর্ণাঙ্ক, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ঘূৰাই 0;
}

স্থির অন্তঃস্থ পূর্ণাঙ্ক split_radix_permutation(পূর্ণাঙ্ক i, পূর্ণাঙ্ক len, পূর্ণাঙ্ক inv)
{
    len >>= 1;
    যদি (len <= 1)
        ঘূৰাই i & 1;
    যদি (!(i & len))
        ঘূৰাই split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ঘূৰাই split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

পূর্ণাঙ্ক ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    পূর্ণাঙ্ক len = s->len;

    যদি (!(s->map = av_malloc(len*পরিমাণ(*s->map))))
        ঘূৰাই AVERROR(ENOMEM);

    যদি (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        বাবে (পূর্ণাঙ্ক i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } অন্যথা {
        বাবে (পূর্ণাঙ্ক i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ঘূৰাই 0;
}

পূর্ণাঙ্ক ff_tx_gen_inplace_map(AVTXContext *s, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক *src_map, out_map_idx = 0;

    যদি (!s->sub || !s->sub->map)
        ঘূৰাই AVERROR(EINVAL);

    যদি (!(s->map = av_mallocz(len*পরিমাণ(*s->map))))
        ঘূৰাই AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    বাবে (পূর্ণাঙ্ক src = 1; src < s->len; src++) {
        পূর্ণাঙ্ক dst = src_map[src];
        পূর্ণাঙ্ক found = 0;

        যদি (dst <= src)
            অনুৱর্ত;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        কৰা {
            বাবে (পূর্ণাঙ্ক j = 0; j < out_map_idx; j++) {
                যদি (dst == s->map[j]) {
                    found = 1;
                    ভঙ্গ;
                }
            }
            dst = src_map[dst];
        } যেতিয়ালৈ (dst != src && !found);

        যদি (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    ঘূৰাই 0;
}

স্থির শূন্য parity_revtab_generator(পূর্ণাঙ্ক *revtab, পূর্ণাঙ্ক n, পূর্ণাঙ্ক inv, পূর্ণাঙ্ক offset,
                                    পূর্ণাঙ্ক is_dual, পূর্ণাঙ্ক dual_উপৰেৰ, পূর্ণাঙ্ক len,
                                    পূর্ণাঙ্ক basis, পূর্ণাঙ্ক dual_stride, পূর্ণাঙ্ক inv_lookup)
{
    len >>= 1;

    যদি (len <= basis) {
        পূর্ণাঙ্ক k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_উপৰেৰ = is_dual & dual_উপৰেৰ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_উপৰেৰ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_উপৰেৰ)*len + dual_উপৰেৰ*len;

        বাবে (পূর্ণাঙ্ক i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            যদি (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } অন্যথা {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            যদি (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ঘূৰাই;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

পূর্ণাঙ্ক ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, পূর্ণাঙ্ক len, পূর্ণাঙ্ক inv,
                                        FFTXCodeletOptions *opts,
                                        পূর্ণাঙ্ক basis, পূর্ণাঙ্ক dual_stride)
{
    basis >>= 1;
    যদি (len < basis)
        ঘূৰাই AVERROR(EINVAL);

    যদি (!(s->map = av_mallocz(len*পরিমাণ(*s->map))))
        ঘূৰাই AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ঘূৰাই 0;
}

স্থির শূন্য reset_ctx(AVTXContext *s, পূর্ণাঙ্ক free_sub)
{
    যদি (!s)
        ঘূৰাই;

    যদি (s->sub)
        বাবে (পূর্ণাঙ্ক i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    যদি (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    যদি (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = রিক্ত;
    memset(s->fn, 0, পরিমাণ(s->fn));
}

শূন্য ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold শূন্য av_tx_uninit(AVTXContext **ctx)
{
    যদি (!(*ctx))
        ঘূৰাই;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

স্থির av_cold পূর্ণাঙ্ক ff_tx_null_init(AVTXContext *s, ধ্রুৱ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   পূর্ণাঙ্ক len, পূর্ণাঙ্ক inv, ধ্রুৱ শূন্য *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    যদি (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ঘূৰাই AVERROR(EINVAL);
    ঘূৰাই 0;
}

/* Null transform when the length is 1 */
স্থির শূন্য ff_tx_null(AVTXContext *s, শূন্য *_out, শূন্য *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

স্থির ধ্রুৱ FFTXCodelet ff_tx_null_def = {
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

স্থির ধ্রুৱ FFTXCodelet * ধ্রুৱ ff_tx_null_list[] = {
    &ff_tx_null_def,
    রিক্ত,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
স্থির ধ্রুৱ FFTXCodelet * ধ্রুৱ * ধ্রুৱ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#যদি HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#যদি ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
স্থির ধ্রুৱ পূর্ণাঙ্ক codelet_list_অঙ্ক = FF_ARRAY_ELEMS(codelet_list);

স্থির ধ্রুৱ পূর্ণাঙ্ক cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

স্থির ধ্রুৱ পূর্ণাঙ্ক cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

স্থির পূর্ণাঙ্ক get_codelet_prio(ধ্রুৱ FFTXCodelet *cd, পূর্ণাঙ্ক cpu_flags, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক prio = cd->prio;
    পূর্ণাঙ্ক max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        যদি ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    যদি ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    যদি ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    যদি ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    বাবে (পূর্ণাঙ্ক i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    যদি (max_factor)
        prio += 16*max_factor;

    ঘূৰাই prio;
}

প্রকারনির্দেশ সংরচনা FFTXLenDecomp {
    পূর্ণাঙ্ক len;
    পূর্ণাঙ্ক len2;
    পূর্ণাঙ্ক prio;
    ধ্রুৱ FFTXCodelet *cd;
} FFTXLenDecomp;

স্থির পূর্ণাঙ্ক cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ঘূৰাই FFDIFFSIGN(b->prio, a->prio);
}

পূর্ণাঙ্ক ff_tx_decompose_length(পূর্ণাঙ্ক dst[TX_MAX_DECOMPOSITIONS], গণনা AVTXType type,
                           পূর্ণাঙ্ক len, পূর্ণাঙ্ক inv)
{
    পূর্ণাঙ্ক nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    পূর্ণাঙ্ক codelet_list_idx = codelet_list_অঙ্ক;

    ধ্রুৱ পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    যেতিয়ালৈ (codelet_list_idx--) {
        ধ্রুৱ FFTXCodelet * ধ্রুৱ * list = codelet_list[codelet_list_idx];
        ধ্রুৱ FFTXCodelet *cd = রিক্ত;

        যেতিয়ালৈ ((cd = *list++)) {
            পূর্ণাঙ্ক fl = len;
            পূর্ণাঙ্ক skip = 0, prio;
            পূর্ণাঙ্ক factors_product = 1, factors_mod = 0;

            যদি (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                গচ্ছ sort;

            /* Check if the type matches */
            যদি (cd->type != TX_TYPE_ANY && type != cd->type)
                অনুৱর্ত;

            /* Check direction for non-orthogonal codelets */
            যদি (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                অনুৱর্ত;

            /* Check if the CPU supports the required ISA */
            যদি (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                অনুৱর্ত;

            বাবে (পূর্ণাঙ্ক i = 0; i < TX_MAX_FACTORS; i++) {
                যদি (!cd->factors[i] || (fl == 1))
                    ভঙ্গ;

                যদি (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } অন্যথা যদি (!(fl % cd->factors[i])) {
                    factors_mod++;
                    যদি (cd->factors[i] == 2) {
                        পূর্ণাঙ্ক b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } অন্যথা {
                        কৰা {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } যেতিয়ালৈ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            যদি ((factors_mod < cd->nb_factors) || (len == factors_product))
                অনুৱর্ত;

            যদি (av_gcd(factors_product, fl) != 1)
                অনুৱর্ত;

            /* Check if length is supported and factorization was successful */
            যদি ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                অনুৱর্ত;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            বাবে (পূর্ণাঙ্ক i = 0; i < nb_decomp; i++) {
                যদি (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    যদি (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ভঙ্গ;
                }
            }

            /* Add decomposition if unique */
            যদি (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    যদি (!nb_decomp)
        ঘূৰাই AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    বাবে (পূর্ণাঙ্ক i = 0; i < nb_decomp; i++) {
        যদি (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        অন্যথা
            dst[i] = ld[i].len;
    }

    ঘূৰাই nb_decomp;
}

পূর্ণাঙ্ক ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*পরিমাণ(*s->map));
    যদি (!s->map)
        ঘূৰাই AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    যদি (s->inv) /* Reversing the ACs flips the transform direction */
        বাবে (পূর্ণাঙ্ক i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    অন্যথা
        বাবে (পূর্ণাঙ্ক i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ঘূৰাই 0;
}

#যদি !CONFIG_SMALL
স্থির শূন্য print_flags(AVBPrint *bp, uint64_t f)
{
    পূর্ণাঙ্ক prev = 0;
    ধ্রুৱ ৱর্ণ *sep = ", ";
    av_bprintf(bp, "flags: [");
    যদি ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    যদি ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    যদি ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    যদি ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    যদি ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    যদি ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    যদি ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    যদি ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    যদি ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    যদি ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    যদি ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

স্থির শূন্য print_type(AVBPrint *bp, গণনা AVTXType type)
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

স্থির শূন্য print_cd_info(ধ্রুৱ FFTXCodelet *cd, পূর্ণাঙ্ক prio, পূর্ণাঙ্ক len, পূর্ণাঙ্ক print_prio,
                          পূর্ণাঙ্ক log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    যদি (!len) {
        যদি (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        যদি (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        অন্যথা
            av_bprintf(&bp, "%i", cd->max_len);
    } অন্যথা {
        av_bprintf(&bp, "%i", len);
    }

    যদি (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        যদি (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        অন্যথা
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        বাবে (পূর্ণাঙ্ক i = 0; i < TX_MAX_FACTORS; i++) {
            যদি (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            যদি (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            অন্যথা যদি (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            অন্যথা
                ভঙ্গ;
        }

        av_bprintf(&bp, "], ");
    } অন্যথা {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    যদি (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(রিক্ত, log_level, "%s\n", bp.str);
}

স্থির শূন্য print_tx_structure(AVTXContext *s, পূর্ণাঙ্ক depth)
{
    ধ্রুৱ FFTXCodelet *cd = s->cd_self;

    বাবে (পূর্ণাঙ্ক i = 0; i <= depth; i++)
        av_log(রিক্ত, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    বাবে (পূর্ণাঙ্ক i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

প্রকারনির্দেশ সংরচনা TXCodeletMatch {
    ধ্রুৱ FFTXCodelet *cd;
    পূর্ণাঙ্ক prio;
} TXCodeletMatch;

স্থির পূর্ণাঙ্ক cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    ঘূৰাই FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
স্থির অন্তঃস্থ পূর্ণাঙ্ক check_cd_factors(ধ্রুৱ FFTXCodelet *cd, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক matches = 0, any_flag = 0;

    বাবে (পূর্ণাঙ্ক i = 0; i < TX_MAX_FACTORS; i++) {
        পূর্ণাঙ্ক factor = cd->factors[i];

        যদি (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            অনুৱর্ত;
        } অন্যথা যদি (len <= 1 || !factor) {
            ভঙ্গ;
        } অন্যথা যদি (factor == 2) { /* Fast path */
            পূর্ণাঙ্ক bits_2 = ff_ctz(len);
            যদি (!bits_2)
                অনুৱর্ত; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } অন্যথা {
            পূর্ণাঙ্ক res = len % factor;
            যদি (res)
                অনুৱর্ত; /* Factor not supported */

            যেতিয়ালৈ (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    ঘূৰাই (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold পূর্ণাঙ্ক ff_tx_init_subtx(AVTXContext *s, গণনা AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             পূর্ণাঙ্ক len, পূর্ণাঙ্ক inv, ধ্রুৱ শূন্য *scale)
{
    পূর্ণাঙ্ক ret = 0;
    AVTXContext *sub = রিক্ত;
    TXCodeletMatch *cd_tmp, *cd_matches = রিক্ত;
    unsigned পূর্ণাঙ্ক cd_matches_size = 0;
    পূর্ণাঙ্ক codelet_list_idx = codelet_list_অঙ্ক;
    পূর্ণাঙ্ক nb_cd_matches = 0;
#যদি !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ধ্রুৱ পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    যদি (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    যদি ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    যদি ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    যেতিয়ালৈ (codelet_list_idx--) {
        ধ্রুৱ FFTXCodelet * ধ্রুৱ * list = codelet_list[codelet_list_idx];
        ধ্রুৱ FFTXCodelet *cd = রিক্ত;

        যেতিয়ালৈ ((cd = *list++)) {
            /* Check if the type matches */
            যদি (cd->type != TX_TYPE_ANY && type != cd->type)
                অনুৱর্ত;

            /* Check direction for non-orthogonal codelets */
            যদি (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                অনুৱর্ত;

            /* Check if the requested flags match from both sides */
            যদি (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                অনুৱর্ত;

            /* Check if length is supported */
            যদি ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                অনুৱর্ত;

            /* Check if the CPU supports the required ISA */
            যদি (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                অনুৱর্ত;

            /* Check for factors */
            যদি (!check_cd_factors(cd, len))
                অনুৱর্ত;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     পরিমাণ(*cd_tmp) * (nb_cd_matches + 1));
            যদি (!cd_tmp) {
                av_free(cd_matches);
                ঘূৰাই AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#যদি !CONFIG_SMALL
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
    যদি (!nb_cd_matches)
        ঘূৰাই AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#যদি !CONFIG_SMALL
    av_log(রিক্ত, AV_LOG_TRACE, "%s\n", bp.str);

    বাবে (পূর্ণাঙ্ক i = 0; i < nb_cd_matches; i++) {
        av_log(রিক্ত, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    যদি (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*পরিমাণ(*sub));
        যদি (!sub) {
            ret = AVERROR(ENOMEM);
            গচ্ছ end;
        }
    }

    /* Attempt to initialize each */
    বাবে (পূর্ণাঙ্ক i = 0; i < nb_cd_matches; i++) {
        ধ্রুৱ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        যদি (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        যদি (ret >= 0) {
            যদি (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*পরিমাণ(*sctx->map));
                যদি (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    গচ্ছ end;
                }

                বাবে (পূর্ণাঙ্ক i = 0; i < len; i++)
                    sctx->map[i] = i;
            } অন্যথা যদি (opts && (opts->map_dir != sctx->map_dir)) {
                পূর্ণাঙ্ক *tmp = av_malloc(len*পরিমাণ(*sctx->map));
                যদি (!tmp) {
                    ret = AVERROR(ENOMEM);
                    গচ্ছ end;
                }

                memcpy(tmp, sctx->map, len*পরিমাণ(*sctx->map));

                বাবে (পূর্ণাঙ্ক i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            গচ্ছ end;
        }

        s->fn[s->nb_sub] = রিক্ত;
        s->cd[s->nb_sub] = রিক্ত;

        reset_ctx(sctx, 0);
        যদি (ret == AVERROR(ENOMEM))
            ভঙ্গ;
    }

    যদি (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    ঘূৰাই ret;
}

av_cold পূর্ণাঙ্ক av_tx_init(AVTXContext **ctx, av_tx_fn *tx, গণনা AVTXType type,
                       পূর্ণাঙ্ক inv, পূর্ণাঙ্ক len, ধ্রুৱ শূন্য *scale, uint64_t flags)
{
    পূর্ণাঙ্ক ret;
    AVTXContext tmp = { 0 };
    ধ্রুৱ দ্ৱিগুণ default_scale_d = 1.0;
    ধ্রুৱ ভিন্ন  default_scale_f = 1.0f;

    যদি (!len || type >= AV_TX_NB || !ctx || !tx)
        ঘূৰাই AVERROR(EINVAL);

    যদি (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    যদি (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    যদি (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    অন্যথা যদি (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, রিক্ত, len, inv, scale);
    যদি (ret < 0)
        ঘূৰাই ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#যদি !CONFIG_SMALL
    av_log(রিক্ত, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    ঘূৰাই ret;
}
