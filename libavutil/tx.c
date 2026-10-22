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

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "intmath.h"
#અન્તર્ભાવ "cpu.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "qsort.h"
#અન્તર્ભાવ "bprint.h"

#અન્તર્ભાવ "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
સ્થિર av_always_inline પૂર્ણાંક mulinv(પૂર્ણાંક n, પૂર્ણાંક m)
{
    n = n % m;
    માટે (પૂર્ણાંક x = 1; x < m; x++)
        જો (((n * x) % m) == 1)
            પાછા x;
    av_assert0(0); /* Never reached */
    પાછા 0;
}

પૂર્ણાંક ff_tx_gen_pfa_આગત_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            પૂર્ણાંક d1, પૂર્ણાંક d2)
{
    અચલ પૂર્ણાંક sl = d1*d2;

    s->map = av_malloc(s->len*કદ(*s->map));
    જો (!s->map)
        પાછા AVERROR(ENOMEM);

    માટે (પૂર્ણાંક k = 0; k < s->len; k += sl) {
        જો (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            માટે (પૂર્ણાંક m = 0; m < d2; m++)
                માટે (પૂર્ણાંક n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } નહીંતર {
            માટે (પૂર્ણાંક m = 0; m < d2; m++)
                માટે (પૂર્ણાંક n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        જો (s->inv)
            માટે (પૂર્ણાંક w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(પૂર્ણાંક, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    પાછા 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
પૂર્ણાંક ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               પૂર્ણાંક inv, પૂર્ણાંક n, પૂર્ણાંક m)
{
    પૂર્ણાંક *in_map, *out_map;
    અચલ પૂર્ણાંક len = n*m;    /* Will not be equal to s->len for MDCTs */
    પૂર્ણાંક m_inv, n_inv;

    /* Make sure the numbers are coprime */
    જો (av_gcd(n, m) != 1)
        પાછા AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    જો (!(s->map = av_malloc(2*len*કદ(*s->map))))
        પાછા AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    જો (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        માટે (પૂર્ણાંક j = 0; j < m; j++) {
            માટે (પૂર્ણાંક i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } નહીંતર {
        માટે (પૂર્ણાંક j = 0; j < m; j++) {
            માટે (પૂર્ણાંક i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    જો (inv) {
        માટે (પૂર્ણાંક i = 0; i < m; i++) {
            પૂર્ણાંક *in = &in_map[i*n + 1]; /* Skip the DC */
            માટે (પૂર્ણાંક j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(પૂર્ણાંક, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    પાછા 0;
}

સ્થિર અંતઃરેખ પૂર્ણાંક split_radix_permutation(પૂર્ણાંક i, પૂર્ણાંક len, પૂર્ણાંક inv)
{
    len >>= 1;
    જો (len <= 1)
        પાછા i & 1;
    જો (!(i & len))
        પાછા split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    પાછા split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

પૂર્ણાંક ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    પૂર્ણાંક len = s->len;

    જો (!(s->map = av_malloc(len*કદ(*s->map))))
        પાછા AVERROR(ENOMEM);

    જો (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        માટે (પૂર્ણાંક i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } નહીંતર {
        માટે (પૂર્ણાંક i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    પાછા 0;
}

પૂર્ણાંક ff_tx_gen_inplace_map(AVTXContext *s, પૂર્ણાંક len)
{
    પૂર્ણાંક *src_map, out_map_idx = 0;

    જો (!s->sub || !s->sub->map)
        પાછા AVERROR(EINVAL);

    જો (!(s->map = av_mallocz(len*કદ(*s->map))))
        પાછા AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    માટે (પૂર્ણાંક src = 1; src < s->len; src++) {
        પૂર્ણાંક dst = src_map[src];
        પૂર્ણાંક found = 0;

        જો (dst <= src)
            ચાલુ;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        કરો {
            માટે (પૂર્ણાંક j = 0; j < out_map_idx; j++) {
                જો (dst == s->map[j]) {
                    found = 1;
                    તોડો;
                }
            }
            dst = src_map[dst];
        } જ્યારે (dst != src && !found);

        જો (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    પાછા 0;
}

સ્થિર શૂન્ય parity_revtab_generator(પૂર્ણાંક *revtab, પૂર્ણાંક n, પૂર્ણાંક inv, પૂર્ણાંક offset,
                                    પૂર્ણાંક is_dual, પૂર્ણાંક dual_ઉપલું, પૂર્ણાંક len,
                                    પૂર્ણાંક basis, પૂર્ણાંક dual_stride, પૂર્ણાંક inv_lookup)
{
    len >>= 1;

    જો (len <= basis) {
        પૂર્ણાંક k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ઉપલું = is_dual & dual_ઉપલું;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_ઉપલું*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ઉપલું)*len + dual_ઉપલું*len;

        માટે (પૂર્ણાંક i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            જો (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } નહીંતર {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            જો (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        પાછા;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

પૂર્ણાંક ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, પૂર્ણાંક len, પૂર્ણાંક inv,
                                        FFTXCodeletOptions *opts,
                                        પૂર્ણાંક basis, પૂર્ણાંક dual_stride)
{
    basis >>= 1;
    જો (len < basis)
        પાછા AVERROR(EINVAL);

    જો (!(s->map = av_mallocz(len*કદ(*s->map))))
        પાછા AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    પાછા 0;
}

સ્થિર શૂન્ય reset_ctx(AVTXContext *s, પૂર્ણાંક free_sub)
{
    જો (!s)
        પાછા;

    જો (s->sub)
        માટે (પૂર્ણાંક i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    જો (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    જો (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ખાલી;
    memset(s->fn, 0, કદ(s->fn));
}

શૂન્ય ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold શૂન્ય av_tx_uninit(AVTXContext **ctx)
{
    જો (!(*ctx))
        પાછા;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

સ્થિર av_cold પૂર્ણાંક ff_tx_null_init(AVTXContext *s, અચલ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   પૂર્ણાંક len, પૂર્ણાંક inv, અચલ શૂન્ય *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    જો (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        પાછા AVERROR(EINVAL);
    પાછા 0;
}

/* Null transform when the length is 1 */
સ્થિર શૂન્ય ff_tx_null(AVTXContext *s, શૂન્ય *_out, શૂન્ય *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

સ્થિર અચલ FFTXCodelet ff_tx_null_def = {
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

સ્થિર અચલ FFTXCodelet * અચલ ff_tx_null_list[] = {
    &ff_tx_null_def,
    ખાલી,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
સ્થિર અચલ FFTXCodelet * અચલ * અચલ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#જો HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#જો ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
સ્થિર અચલ પૂર્ણાંક codelet_list_અંક = FF_ARRAY_ELEMS(codelet_list);

સ્થિર અચલ પૂર્ણાંક cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

સ્થિર અચલ પૂર્ણાંક cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

સ્થિર પૂર્ણાંક get_codelet_prio(અચલ FFTXCodelet *cd, પૂર્ણાંક cpu_flags, પૂર્ણાંક len)
{
    પૂર્ણાંક prio = cd->prio;
    પૂર્ણાંક max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        જો ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    જો ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    જો ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    જો ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    માટે (પૂર્ણાંક i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    જો (max_factor)
        prio += 16*max_factor;

    પાછા prio;
}

પ્રકારવ્યાખ્યા સંરચના FFTXLenDecomp {
    પૂર્ણાંક len;
    પૂર્ણાંક len2;
    પૂર્ણાંક prio;
    અચલ FFTXCodelet *cd;
} FFTXLenDecomp;

સ્થિર પૂર્ણાંક cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    પાછા FFDIFFSIGN(b->prio, a->prio);
}

પૂર્ણાંક ff_tx_decompose_length(પૂર્ણાંક dst[TX_MAX_DECOMPOSITIONS], ગણના AVTXType type,
                           પૂર્ણાંક len, પૂર્ણાંક inv)
{
    પૂર્ણાંક nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    પૂર્ણાંક codelet_list_idx = codelet_list_અંક;

    અચલ પૂર્ણાંક cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    જ્યારે (codelet_list_idx--) {
        અચલ FFTXCodelet * અચલ * list = codelet_list[codelet_list_idx];
        અચલ FFTXCodelet *cd = ખાલી;

        જ્યારે ((cd = *list++)) {
            પૂર્ણાંક fl = len;
            પૂર્ણાંક skip = 0, prio;
            પૂર્ણાંક factors_product = 1, factors_mod = 0;

            જો (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                જાઓ sort;

            /* Check if the type matches */
            જો (cd->type != TX_TYPE_ANY && type != cd->type)
                ચાલુ;

            /* Check direction for non-orthogonal codelets */
            જો (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ચાલુ;

            /* Check if the CPU supports the required ISA */
            જો (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ચાલુ;

            માટે (પૂર્ણાંક i = 0; i < TX_MAX_FACTORS; i++) {
                જો (!cd->factors[i] || (fl == 1))
                    તોડો;

                જો (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } નહીંતર જો (!(fl % cd->factors[i])) {
                    factors_mod++;
                    જો (cd->factors[i] == 2) {
                        પૂર્ણાંક b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } નહીંતર {
                        કરો {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } જ્યારે (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            જો ((factors_mod < cd->nb_factors) || (len == factors_product))
                ચાલુ;

            જો (av_gcd(factors_product, fl) != 1)
                ચાલુ;

            /* Check if length is supported and factorization was successful */
            જો ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                ચાલુ;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            માટે (પૂર્ણાંક i = 0; i < nb_decomp; i++) {
                જો (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    જો (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    તોડો;
                }
            }

            /* Add decomposition if unique */
            જો (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    જો (!nb_decomp)
        પાછા AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    માટે (પૂર્ણાંક i = 0; i < nb_decomp; i++) {
        જો (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        નહીંતર
            dst[i] = ld[i].len;
    }

    પાછા nb_decomp;
}

પૂર્ણાંક ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*કદ(*s->map));
    જો (!s->map)
        પાછા AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    જો (s->inv) /* Reversing the ACs flips the transform direction */
        માટે (પૂર્ણાંક i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    નહીંતર
        માટે (પૂર્ણાંક i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    પાછા 0;
}

#જો !CONFIG_SMALL
સ્થિર શૂન્ય print_flags(AVBPrint *bp, uint64_t f)
{
    પૂર્ણાંક prev = 0;
    અચલ અક્ષર *sep = ", ";
    av_bprintf(bp, "flags: [");
    જો ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    જો ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    જો ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    જો ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    જો ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    જો ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    જો ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    જો ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    જો ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    જો ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    જો ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

સ્થિર શૂન્ય print_type(AVBPrint *bp, ગણના AVTXType type)
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

સ્થિર શૂન્ય print_cd_info(અચલ FFTXCodelet *cd, પૂર્ણાંક prio, પૂર્ણાંક len, પૂર્ણાંક print_prio,
                          પૂર્ણાંક log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    જો (!len) {
        જો (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        જો (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        નહીંતર
            av_bprintf(&bp, "%i", cd->max_len);
    } નહીંતર {
        av_bprintf(&bp, "%i", len);
    }

    જો (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        જો (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        નહીંતર
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        માટે (પૂર્ણાંક i = 0; i < TX_MAX_FACTORS; i++) {
            જો (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            જો (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            નહીંતર જો (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            નહીંતર
                તોડો;
        }

        av_bprintf(&bp, "], ");
    } નહીંતર {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    જો (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ખાલી, log_level, "%s\n", bp.str);
}

સ્થિર શૂન્ય print_tx_structure(AVTXContext *s, પૂર્ણાંક depth)
{
    અચલ FFTXCodelet *cd = s->cd_self;

    માટે (પૂર્ણાંક i = 0; i <= depth; i++)
        av_log(ખાલી, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    માટે (પૂર્ણાંક i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

પ્રકારવ્યાખ્યા સંરચના TXCodeletMatch {
    અચલ FFTXCodelet *cd;
    પૂર્ણાંક prio;
} TXCodeletMatch;

સ્થિર પૂર્ણાંક cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    પાછા FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
સ્થિર અંતઃરેખ પૂર્ણાંક check_cd_factors(અચલ FFTXCodelet *cd, પૂર્ણાંક len)
{
    પૂર્ણાંક matches = 0, any_flag = 0;

    માટે (પૂર્ણાંક i = 0; i < TX_MAX_FACTORS; i++) {
        પૂર્ણાંક factor = cd->factors[i];

        જો (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            ચાલુ;
        } નહીંતર જો (len <= 1 || !factor) {
            તોડો;
        } નહીંતર જો (factor == 2) { /* Fast path */
            પૂર્ણાંક bits_2 = ff_ctz(len);
            જો (!bits_2)
                ચાલુ; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } નહીંતર {
            પૂર્ણાંક res = len % factor;
            જો (res)
                ચાલુ; /* Factor not supported */

            જ્યારે (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    પાછા (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold પૂર્ણાંક ff_tx_init_subtx(AVTXContext *s, ગણના AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             પૂર્ણાંક len, પૂર્ણાંક inv, અચલ શૂન્ય *scale)
{
    પૂર્ણાંક ret = 0;
    AVTXContext *sub = ખાલી;
    TXCodeletMatch *cd_tmp, *cd_matches = ખાલી;
    unsigned પૂર્ણાંક cd_matches_size = 0;
    પૂર્ણાંક codelet_list_idx = codelet_list_અંક;
    પૂર્ણાંક nb_cd_matches = 0;
#જો !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    અચલ પૂર્ણાંક cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    જો (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    જો ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    જો ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    જ્યારે (codelet_list_idx--) {
        અચલ FFTXCodelet * અચલ * list = codelet_list[codelet_list_idx];
        અચલ FFTXCodelet *cd = ખાલી;

        જ્યારે ((cd = *list++)) {
            /* Check if the type matches */
            જો (cd->type != TX_TYPE_ANY && type != cd->type)
                ચાલુ;

            /* Check direction for non-orthogonal codelets */
            જો (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ચાલુ;

            /* Check if the requested flags match from both sides */
            જો (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                ચાલુ;

            /* Check if length is supported */
            જો ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                ચાલુ;

            /* Check if the CPU supports the required ISA */
            જો (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ચાલુ;

            /* Check for factors */
            જો (!check_cd_factors(cd, len))
                ચાલુ;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     કદ(*cd_tmp) * (nb_cd_matches + 1));
            જો (!cd_tmp) {
                av_free(cd_matches);
                પાછા AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#જો !CONFIG_SMALL
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
    જો (!nb_cd_matches)
        પાછા AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#જો !CONFIG_SMALL
    av_log(ખાલી, AV_LOG_TRACE, "%s\n", bp.str);

    માટે (પૂર્ણાંક i = 0; i < nb_cd_matches; i++) {
        av_log(ખાલી, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    જો (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*કદ(*sub));
        જો (!sub) {
            ret = AVERROR(ENOMEM);
            જાઓ end;
        }
    }

    /* Attempt to initialize each */
    માટે (પૂર્ણાંક i = 0; i < nb_cd_matches; i++) {
        અચલ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        જો (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        જો (ret >= 0) {
            જો (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*કદ(*sctx->map));
                જો (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    જાઓ end;
                }

                માટે (પૂર્ણાંક i = 0; i < len; i++)
                    sctx->map[i] = i;
            } નહીંતર જો (opts && (opts->map_dir != sctx->map_dir)) {
                પૂર્ણાંક *tmp = av_malloc(len*કદ(*sctx->map));
                જો (!tmp) {
                    ret = AVERROR(ENOMEM);
                    જાઓ end;
                }

                memcpy(tmp, sctx->map, len*કદ(*sctx->map));

                માટે (પૂર્ણાંક i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            જાઓ end;
        }

        s->fn[s->nb_sub] = ખાલી;
        s->cd[s->nb_sub] = ખાલી;

        reset_ctx(sctx, 0);
        જો (ret == AVERROR(ENOMEM))
            તોડો;
    }

    જો (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    પાછા ret;
}

av_cold પૂર્ણાંક av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ગણના AVTXType type,
                       પૂર્ણાંક inv, પૂર્ણાંક len, અચલ શૂન્ય *scale, uint64_t flags)
{
    પૂર્ણાંક ret;
    AVTXContext tmp = { 0 };
    અચલ દ્વિગુણ default_scale_d = 1.0;
    અચલ દશાંશ  default_scale_f = 1.0f;

    જો (!len || type >= AV_TX_NB || !ctx || !tx)
        પાછા AVERROR(EINVAL);

    જો (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    જો (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    જો (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    નહીંતર જો (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ખાલી, len, inv, scale);
    જો (ret < 0)
        પાછા ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#જો !CONFIG_SMALL
    av_log(ખાલી, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    પાછા ret;
}
