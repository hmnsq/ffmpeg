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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "intmath.h"
#अन्तर्भाव "cpu.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "qsort.h"
#अन्तर्भाव "bprint.h"

#अन्तर्भाव "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
स्थिर av_always_inline पूर्णाङ्क mulinv(पूर्णाङ्क n, पूर्णाङ्क m)
{
    n = n % m;
    प्रति (पूर्णाङ्क x = 1; x < m; x++)
        यदि (((n * x) % m) == 1)
            प्रत्यागम x;
    av_assert0(0); /* Never reached */
    प्रत्यागम 0;
}

पूर्णाङ्क ff_tx_gen_pfa_निवेश_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            पूर्णाङ्क d1, पूर्णाङ्क d2)
{
    ध्रुव पूर्णाङ्क sl = d1*d2;

    s->map = av_malloc(s->len*परिमाण(*s->map));
    यदि (!s->map)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (पूर्णाङ्क k = 0; k < s->len; k += sl) {
        यदि (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            प्रति (पूर्णाङ्क m = 0; m < d2; m++)
                प्रति (पूर्णाङ्क n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } अन्यथा {
            प्रति (पूर्णाङ्क m = 0; m < d2; m++)
                प्रति (पूर्णाङ्क n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        यदि (s->inv)
            प्रति (पूर्णाङ्क w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(पूर्णाङ्क, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    प्रत्यागम 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
पूर्णाङ्क ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               पूर्णाङ्क inv, पूर्णाङ्क n, पूर्णाङ्क m)
{
    पूर्णाङ्क *in_map, *out_map;
    ध्रुव पूर्णाङ्क len = n*m;    /* Will not be equal to s->len for MDCTs */
    पूर्णाङ्क m_inv, n_inv;

    /* Make sure the numbers are coprime */
    यदि (av_gcd(n, m) != 1)
        प्रत्यागम AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    यदि (!(s->map = av_malloc(2*len*परिमाण(*s->map))))
        प्रत्यागम AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    यदि (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        प्रति (पूर्णाङ्क j = 0; j < m; j++) {
            प्रति (पूर्णाङ्क i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } अन्यथा {
        प्रति (पूर्णाङ्क j = 0; j < m; j++) {
            प्रति (पूर्णाङ्क i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    यदि (inv) {
        प्रति (पूर्णाङ्क i = 0; i < m; i++) {
            पूर्णाङ्क *in = &in_map[i*n + 1]; /* Skip the DC */
            प्रति (पूर्णाङ्क j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(पूर्णाङ्क, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    प्रत्यागम 0;
}

स्थिर अन्तःस्थ पूर्णाङ्क split_radix_permutation(पूर्णाङ्क i, पूर्णाङ्क len, पूर्णाङ्क inv)
{
    len >>= 1;
    यदि (len <= 1)
        प्रत्यागम i & 1;
    यदि (!(i & len))
        प्रत्यागम split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    प्रत्यागम split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

पूर्णाङ्क ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    पूर्णाङ्क len = s->len;

    यदि (!(s->map = av_malloc(len*परिमाण(*s->map))))
        प्रत्यागम AVERROR(ENOMEM);

    यदि (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        प्रति (पूर्णाङ्क i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_tx_gen_inplace_map(AVTXContext *s, पूर्णाङ्क len)
{
    पूर्णाङ्क *src_map, out_map_idx = 0;

    यदि (!s->sub || !s->sub->map)
        प्रत्यागम AVERROR(EINVAL);

    यदि (!(s->map = av_mallocz(len*परिमाण(*s->map))))
        प्रत्यागम AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    प्रति (पूर्णाङ्क src = 1; src < s->len; src++) {
        पूर्णाङ्क dst = src_map[src];
        पूर्णाङ्क found = 0;

        यदि (dst <= src)
            अनुवर्त;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        कुरु {
            प्रति (पूर्णाङ्क j = 0; j < out_map_idx; j++) {
                यदि (dst == s->map[j]) {
                    found = 1;
                    भङ्ग;
                }
            }
            dst = src_map[dst];
        } यावत् (dst != src && !found);

        यदि (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    प्रत्यागम 0;
}

स्थिर शून्य parity_revtab_generator(पूर्णाङ्क *revtab, पूर्णाङ्क n, पूर्णाङ्क inv, पूर्णाङ्क offset,
                                    पूर्णाङ्क is_dual, पूर्णाङ्क dual_ऊपरी, पूर्णाङ्क len,
                                    पूर्णाङ्क basis, पूर्णाङ्क dual_stride, पूर्णाङ्क inv_lookup)
{
    len >>= 1;

    यदि (len <= basis) {
        पूर्णाङ्क k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ऊपरी = is_dual & dual_ऊपरी;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_ऊपरी*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ऊपरी)*len + dual_ऊपरी*len;

        प्रति (पूर्णाङ्क i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            यदि (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } अन्यथा {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            यदि (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        प्रत्यागम;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

पूर्णाङ्क ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, पूर्णाङ्क len, पूर्णाङ्क inv,
                                        FFTXCodeletOptions *opts,
                                        पूर्णाङ्क basis, पूर्णाङ्क dual_stride)
{
    basis >>= 1;
    यदि (len < basis)
        प्रत्यागम AVERROR(EINVAL);

    यदि (!(s->map = av_mallocz(len*परिमाण(*s->map))))
        प्रत्यागम AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    प्रत्यागम 0;
}

स्थिर शून्य reset_ctx(AVTXContext *s, पूर्णाङ्क free_sub)
{
    यदि (!s)
        प्रत्यागम;

    यदि (s->sub)
        प्रति (पूर्णाङ्क i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    यदि (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    यदि (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = रिक्त;
    memset(s->fn, 0, परिमाण(s->fn));
}

शून्य ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold शून्य av_tx_uninit(AVTXContext **ctx)
{
    यदि (!(*ctx))
        प्रत्यागम;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

स्थिर av_cold पूर्णाङ्क ff_tx_null_init(AVTXContext *s, ध्रुव FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   पूर्णाङ्क len, पूर्णाङ्क inv, ध्रुव शून्य *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    यदि (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        प्रत्यागम AVERROR(EINVAL);
    प्रत्यागम 0;
}

/* Null transform when the length is 1 */
स्थिर शून्य ff_tx_null(AVTXContext *s, शून्य *_out, शून्य *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

स्थिर ध्रुव FFTXCodelet ff_tx_null_def = {
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

स्थिर ध्रुव FFTXCodelet * ध्रुव ff_tx_null_list[] = {
    &ff_tx_null_def,
    रिक्त,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
स्थिर ध्रुव FFTXCodelet * ध्रुव * ध्रुव codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#यदि HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#यदि ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
स्थिर ध्रुव पूर्णाङ्क codelet_list_अंक = FF_ARRAY_ELEMS(codelet_list);

स्थिर ध्रुव पूर्णाङ्क cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

स्थिर ध्रुव पूर्णाङ्क cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

स्थिर पूर्णाङ्क get_codelet_prio(ध्रुव FFTXCodelet *cd, पूर्णाङ्क cpu_flags, पूर्णाङ्क len)
{
    पूर्णाङ्क prio = cd->prio;
    पूर्णाङ्क max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        यदि ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    यदि ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    यदि ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    यदि ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    प्रति (पूर्णाङ्क i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    यदि (max_factor)
        prio += 16*max_factor;

    प्रत्यागम prio;
}

प्रकारनिर्देश संरचना FFTXLenDecomp {
    पूर्णाङ्क len;
    पूर्णाङ्क len2;
    पूर्णाङ्क prio;
    ध्रुव FFTXCodelet *cd;
} FFTXLenDecomp;

स्थिर पूर्णाङ्क cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    प्रत्यागम FFDIFFSIGN(b->prio, a->prio);
}

पूर्णाङ्क ff_tx_decompose_length(पूर्णाङ्क dst[TX_MAX_DECOMPOSITIONS], गणना AVTXType type,
                           पूर्णाङ्क len, पूर्णाङ्क inv)
{
    पूर्णाङ्क nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    पूर्णाङ्क codelet_list_idx = codelet_list_अंक;

    ध्रुव पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    यावत् (codelet_list_idx--) {
        ध्रुव FFTXCodelet * ध्रुव * list = codelet_list[codelet_list_idx];
        ध्रुव FFTXCodelet *cd = रिक्त;

        यावत् ((cd = *list++)) {
            पूर्णाङ्क fl = len;
            पूर्णाङ्क skip = 0, prio;
            पूर्णाङ्क factors_product = 1, factors_mod = 0;

            यदि (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                गच्छ sort;

            /* Check if the type matches */
            यदि (cd->type != TX_TYPE_ANY && type != cd->type)
                अनुवर्त;

            /* Check direction for non-orthogonal codelets */
            यदि (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                अनुवर्त;

            /* Check if the CPU supports the required ISA */
            यदि (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                अनुवर्त;

            प्रति (पूर्णाङ्क i = 0; i < TX_MAX_FACTORS; i++) {
                यदि (!cd->factors[i] || (fl == 1))
                    भङ्ग;

                यदि (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } अन्यथा यदि (!(fl % cd->factors[i])) {
                    factors_mod++;
                    यदि (cd->factors[i] == 2) {
                        पूर्णाङ्क b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } अन्यथा {
                        कुरु {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } यावत् (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            यदि ((factors_mod < cd->nb_factors) || (len == factors_product))
                अनुवर्त;

            यदि (av_gcd(factors_product, fl) != 1)
                अनुवर्त;

            /* Check if length is supported and factorization was successful */
            यदि ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                अनुवर्त;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            प्रति (पूर्णाङ्क i = 0; i < nb_decomp; i++) {
                यदि (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    यदि (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    भङ्ग;
                }
            }

            /* Add decomposition if unique */
            यदि (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    यदि (!nb_decomp)
        प्रत्यागम AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    प्रति (पूर्णाङ्क i = 0; i < nb_decomp; i++) {
        यदि (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        अन्यथा
            dst[i] = ld[i].len;
    }

    प्रत्यागम nb_decomp;
}

पूर्णाङ्क ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*परिमाण(*s->map));
    यदि (!s->map)
        प्रत्यागम AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    यदि (s->inv) /* Reversing the ACs flips the transform direction */
        प्रति (पूर्णाङ्क i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    अन्यथा
        प्रति (पूर्णाङ्क i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    प्रत्यागम 0;
}

#यदि !CONFIG_SMALL
स्थिर शून्य print_flags(AVBPrint *bp, uint64_t f)
{
    पूर्णाङ्क prev = 0;
    ध्रुव वर्ण *sep = ", ";
    av_bprintf(bp, "flags: [");
    यदि ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    यदि ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    यदि ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    यदि ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    यदि ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    यदि ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    यदि ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    यदि ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    यदि ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    यदि ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    यदि ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

स्थिर शून्य print_type(AVBPrint *bp, गणना AVTXType type)
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

स्थिर शून्य print_cd_info(ध्रुव FFTXCodelet *cd, पूर्णाङ्क prio, पूर्णाङ्क len, पूर्णाङ्क print_prio,
                          पूर्णाङ्क log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    यदि (!len) {
        यदि (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        यदि (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        अन्यथा
            av_bprintf(&bp, "%i", cd->max_len);
    } अन्यथा {
        av_bprintf(&bp, "%i", len);
    }

    यदि (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        यदि (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        अन्यथा
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        प्रति (पूर्णाङ्क i = 0; i < TX_MAX_FACTORS; i++) {
            यदि (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            यदि (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            अन्यथा यदि (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            अन्यथा
                भङ्ग;
        }

        av_bprintf(&bp, "], ");
    } अन्यथा {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    यदि (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(रिक्त, log_level, "%s\n", bp.str);
}

स्थिर शून्य print_tx_structure(AVTXContext *s, पूर्णाङ्क depth)
{
    ध्रुव FFTXCodelet *cd = s->cd_self;

    प्रति (पूर्णाङ्क i = 0; i <= depth; i++)
        av_log(रिक्त, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    प्रति (पूर्णाङ्क i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

प्रकारनिर्देश संरचना TXCodeletMatch {
    ध्रुव FFTXCodelet *cd;
    पूर्णाङ्क prio;
} TXCodeletMatch;

स्थिर पूर्णाङ्क cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    प्रत्यागम FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
स्थिर अन्तःस्थ पूर्णाङ्क check_cd_factors(ध्रुव FFTXCodelet *cd, पूर्णाङ्क len)
{
    पूर्णाङ्क matches = 0, any_flag = 0;

    प्रति (पूर्णाङ्क i = 0; i < TX_MAX_FACTORS; i++) {
        पूर्णाङ्क factor = cd->factors[i];

        यदि (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            अनुवर्त;
        } अन्यथा यदि (len <= 1 || !factor) {
            भङ्ग;
        } अन्यथा यदि (factor == 2) { /* Fast path */
            पूर्णाङ्क bits_2 = ff_ctz(len);
            यदि (!bits_2)
                अनुवर्त; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } अन्यथा {
            पूर्णाङ्क res = len % factor;
            यदि (res)
                अनुवर्त; /* Factor not supported */

            यावत् (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    प्रत्यागम (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold पूर्णाङ्क ff_tx_init_subtx(AVTXContext *s, गणना AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             पूर्णाङ्क len, पूर्णाङ्क inv, ध्रुव शून्य *scale)
{
    पूर्णाङ्क ret = 0;
    AVTXContext *sub = रिक्त;
    TXCodeletMatch *cd_tmp, *cd_matches = रिक्त;
    unsigned पूर्णाङ्क cd_matches_size = 0;
    पूर्णाङ्क codelet_list_idx = codelet_list_अंक;
    पूर्णाङ्क nb_cd_matches = 0;
#यदि !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ध्रुव पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    यदि (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    यदि ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    यदि ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    यावत् (codelet_list_idx--) {
        ध्रुव FFTXCodelet * ध्रुव * list = codelet_list[codelet_list_idx];
        ध्रुव FFTXCodelet *cd = रिक्त;

        यावत् ((cd = *list++)) {
            /* Check if the type matches */
            यदि (cd->type != TX_TYPE_ANY && type != cd->type)
                अनुवर्त;

            /* Check direction for non-orthogonal codelets */
            यदि (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                अनुवर्त;

            /* Check if the requested flags match from both sides */
            यदि (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                अनुवर्त;

            /* Check if length is supported */
            यदि ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                अनुवर्त;

            /* Check if the CPU supports the required ISA */
            यदि (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                अनुवर्त;

            /* Check for factors */
            यदि (!check_cd_factors(cd, len))
                अनुवर्त;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     परिमाण(*cd_tmp) * (nb_cd_matches + 1));
            यदि (!cd_tmp) {
                av_free(cd_matches);
                प्रत्यागम AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#यदि !CONFIG_SMALL
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
    यदि (!nb_cd_matches)
        प्रत्यागम AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#यदि !CONFIG_SMALL
    av_log(रिक्त, AV_LOG_TRACE, "%s\n", bp.str);

    प्रति (पूर्णाङ्क i = 0; i < nb_cd_matches; i++) {
        av_log(रिक्त, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    यदि (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*परिमाण(*sub));
        यदि (!sub) {
            ret = AVERROR(ENOMEM);
            गच्छ end;
        }
    }

    /* Attempt to initialize each */
    प्रति (पूर्णाङ्क i = 0; i < nb_cd_matches; i++) {
        ध्रुव FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        यदि (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        यदि (ret >= 0) {
            यदि (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*परिमाण(*sctx->map));
                यदि (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    गच्छ end;
                }

                प्रति (पूर्णाङ्क i = 0; i < len; i++)
                    sctx->map[i] = i;
            } अन्यथा यदि (opts && (opts->map_dir != sctx->map_dir)) {
                पूर्णाङ्क *tmp = av_malloc(len*परिमाण(*sctx->map));
                यदि (!tmp) {
                    ret = AVERROR(ENOMEM);
                    गच्छ end;
                }

                memcpy(tmp, sctx->map, len*परिमाण(*sctx->map));

                प्रति (पूर्णाङ्क i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            गच्छ end;
        }

        s->fn[s->nb_sub] = रिक्त;
        s->cd[s->nb_sub] = रिक्त;

        reset_ctx(sctx, 0);
        यदि (ret == AVERROR(ENOMEM))
            भङ्ग;
    }

    यदि (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    प्रत्यागम ret;
}

av_cold पूर्णाङ्क av_tx_init(AVTXContext **ctx, av_tx_fn *tx, गणना AVTXType type,
                       पूर्णाङ्क inv, पूर्णाङ्क len, ध्रुव शून्य *scale, uint64_t flags)
{
    पूर्णाङ्क ret;
    AVTXContext tmp = { 0 };
    ध्रुव द्विगुण default_scale_d = 1.0;
    ध्रुव भिन्न  default_scale_f = 1.0f;

    यदि (!len || type >= AV_TX_NB || !ctx || !tx)
        प्रत्यागम AVERROR(EINVAL);

    यदि (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    यदि (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    यदि (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    अन्यथा यदि (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, रिक्त, len, inv, scale);
    यदि (ret < 0)
        प्रत्यागम ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#यदि !CONFIG_SMALL
    av_log(रिक्त, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    प्रत्यागम ret;
}
