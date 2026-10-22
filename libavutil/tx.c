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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "intmath.h"
#అన్తర్భావ "cpu.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "qsort.h"
#అన్తర్భావ "bprint.h"

#అన్తర్భావ "tx_priv.h"

#నిర్వచించు TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
స్థిర av_always_inline పూర్ణాంకం mulinv(పూర్ణాంకం n, పూర్ణాంకం m)
{
    n = n % m;
    కొరకు (పూర్ణాంకం x = 1; x < m; x++)
        ఒకవేళ (((n * x) % m) == 1)
            తిరిగి x;
    av_assert0(0); /* Never reached */
    తిరిగి 0;
}

పూర్ణాంకం ff_tx_gen_pfa_ఆదానం_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            పూర్ణాంకం d1, పూర్ణాంకం d2)
{
    స్థిరరాశి పూర్ణాంకం sl = d1*d2;

    s->map = av_malloc(s->len*పరిమాణం(*s->map));
    ఒకవేళ (!s->map)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (పూర్ణాంకం k = 0; k < s->len; k += sl) {
        ఒకవేళ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            కొరకు (పూర్ణాంకం m = 0; m < d2; m++)
                కొరకు (పూర్ణాంకం n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } లేకపోతే {
            కొరకు (పూర్ణాంకం m = 0; m < d2; m++)
                కొరకు (పూర్ణాంకం n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ఒకవేళ (s->inv)
            కొరకు (పూర్ణాంకం w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(పూర్ణాంకం, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    తిరిగి 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
పూర్ణాంకం ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               పూర్ణాంకం inv, పూర్ణాంకం n, పూర్ణాంకం m)
{
    పూర్ణాంకం *లోపల_map, *బహిర్గతం_map;
    స్థిరరాశి పూర్ణాంకం len = n*m;    /* Will not be equal to s->len for MDCTs */
    పూర్ణాంకం m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ఒకవేళ (av_గరిష్ఠ_సామాన్య_భాజకం(n, m) != 1)
        తిరిగి AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ఒకవేళ (!(s->map = av_malloc(2*len*పరిమాణం(*s->map))))
        తిరిగి AVERROR(ENOMEM);

    లోపల_map  = s->map;
    బహిర్గతం_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ఒకవేళ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        కొరకు (పూర్ణాంకం j = 0; j < m; j++) {
            కొరకు (పూర్ణాంకం i = 0; i < n; i++) {
                లోపల_map[(i*m + j*n) % len] = j*n + i;
                బహిర్గతం_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } లేకపోతే {
        కొరకు (పూర్ణాంకం j = 0; j < m; j++) {
            కొరకు (పూర్ణాంకం i = 0; i < n; i++) {
                లోపల_map[j*n + i] = (i*m + j*n) % len;
                బహిర్గతం_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ఒకవేళ (inv) {
        కొరకు (పూర్ణాంకం i = 0; i < m; i++) {
            పూర్ణాంకం *లోపల = &లోపల_map[i*n + 1]; /* Skip the DC */
            కొరకు (పూర్ణాంకం j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(పూర్ణాంకం, లోపల[j], లోపల[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    తిరిగి 0;
}

స్థిర అంతఃవరుస పూర్ణాంకం విభజించు_radix_permutation(పూర్ణాంకం i, పూర్ణాంకం len, పూర్ణాంకం inv)
{
    len >>= 1;
    ఒకవేళ (len <= 1)
        తిరిగి i & 1;
    ఒకవేళ (!(i & len))
        తిరిగి విభజించు_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    తిరిగి విభజించు_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

పూర్ణాంకం ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    పూర్ణాంకం len = s->len;

    ఒకవేళ (!(s->map = av_malloc(len*పరిమాణం(*s->map))))
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        కొరకు (పూర్ణాంకం i = 0; i < s->len; i++)
            s->map[-విభజించు_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } లేకపోతే {
        కొరకు (పూర్ణాంకం i = 0; i < s->len; i++)
            s->map[i] = -విభజించు_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    తిరిగి 0;
}

పూర్ణాంకం ff_tx_gen_inplace_map(AVTXContext *s, పూర్ణాంకం len)
{
    పూర్ణాంకం *src_map, బహిర్గతం_map_idx = 0;

    ఒకవేళ (!s->sub || !s->sub->map)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!(s->map = av_mallocz(len*పరిమాణం(*s->map))))
        తిరిగి AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    కొరకు (పూర్ణాంకం src = 1; src < s->len; src++) {
        పూర్ణాంకం dst = src_map[src];
        పూర్ణాంకం దొరికింది = 0;

        ఒకవేళ (dst <= src)
            కొనసాగు;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        చేయి {
            కొరకు (పూర్ణాంకం j = 0; j < బహిర్గతం_map_idx; j++) {
                ఒకవేళ (dst == s->map[j]) {
                    దొరికింది = 1;
                    ఆపు;
                }
            }
            dst = src_map[dst];
        } అయితే (dst != src && !దొరికింది);

        ఒకవేళ (!దొరికింది)
            s->map[బహిర్గతం_map_idx++] = src;
    }

    s->map[బహిర్గతం_map_idx++] = 0;

    తిరిగి 0;
}

స్థిర శూన్య parity_revtab_generator(పూర్ణాంకం *revtab, పూర్ణాంకం n, పూర్ణాంకం inv, పూర్ణాంకం స్థానభ్రంశం,
                                    పూర్ణాంకం is_dual, పూర్ణాంకం dual_ఎగువ, పూర్ణాంకం len,
                                    పూర్ణాంకం basis, పూర్ణాంకం dual_stride, పూర్ణాంకం inv_lookup)
{
    len >>= 1;

    ఒకవేళ (len <= basis) {
        పూర్ణాంకం k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ఎగువ = is_dual & dual_ఎగువ;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = స్థానభ్రంశం + dual_ఎగువ*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ఎగువ)*len + dual_ఎగువ*len;

        కొరకు (పూర్ణాంకం i = 0; i < len; i++) {
            k1 = -విభజించు_radix_permutation(స్థానభ్రంశం + i*2 + 0, n, inv) & (n - 1);
            k2 = -విభజించు_radix_permutation(స్థానభ్రంశం + i*2 + 1, n, inv) & (n - 1);
            ఒకవేళ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } లేకపోతే {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ఒకవేళ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        తిరిగి;
    }

    parity_revtab_generator(revtab, n, inv, స్థానభ్రంశం,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, స్థానభ్రంశం + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, స్థానభ్రంశం + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

పూర్ణాంకం ff_tx_gen_విభజించు_radix_parity_revtab(AVTXContext *s, పూర్ణాంకం len, పూర్ణాంకం inv,
                                        FFTXCodeletOptions *opts,
                                        పూర్ణాంకం basis, పూర్ణాంకం dual_stride)
{
    basis >>= 1;
    ఒకవేళ (len < basis)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!(s->map = av_mallocz(len*పరిమాణం(*s->map))))
        తిరిగి AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    తిరిగి 0;
}

స్థిర శూన్య reset_ctx(AVTXContext *s, పూర్ణాంకం free_sub)
{
    ఒకవేళ (!s)
        తిరిగి;

    ఒకవేళ (s->sub)
        కొరకు (పూర్ణాంకం i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ఒకవేళ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ఒకవేళ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->ఘాతాంకం);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ఖాళీ;
    memset(s->fn, 0, పరిమాణం(s->fn));
}

శూన్య ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold శూన్య av_tx_uninit(AVTXContext **ctx)
{
    ఒకవేళ (!(*ctx))
        తిరిగి;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

స్థిర av_cold పూర్ణాంకం ff_tx_null_init(AVTXContext *s, స్థిరరాశి FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   పూర్ణాంకం len, పూర్ణాంకం inv, స్థిరరాశి శూన్య *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ఒకవేళ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        తిరిగి AVERROR(EINVAL);
    తిరిగి 0;
}

/* Null transform when the length is 1 */
స్థిర శూన్య ff_tx_null(AVTXContext *s, శూన్య *బహిర్గతం_3, శూన్య *లోపల_3, ptrdiff_t stride)
{
    జ్ఞాపకం_నకలు(బహిర్గతం_3, లోపల_3, stride);
}

స్థిర స్థిరరాశి FFTXCodelet ff_tx_null_def = {
    .name       = NULL_IF_CONFIG_SMALL("null"),
    .function   = ff_tx_null,
    .type       = TX_TYPE_ANY,
    .flags      = AV_TX_UNALIGNED | FF_TX_ALIGNED |
                  FF_TX_బహిర్గతం_యొక్క_ఉంచు | AV_TX_INPLACE,
    .factors[0] = TX_గుణకం_ANY,
    .min_len    = 1,
    .max_len    = 1,
    .init       = ff_tx_null_init,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MAX,
};

స్థిర స్థిరరాశి FFTXCodelet * స్థిరరాశి ff_tx_null_list[] = {
    &ff_tx_null_def,
    ఖాళీ,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
స్థిర స్థిరరాశి FFTXCodelet * స్థిరరాశి * స్థిరరాశి codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#ఒకవేళ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#అయితే_ముగింపు
#ఒకవేళ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#అయితే_ముగింపు
};
స్థిర స్థిరరాశి పూర్ణాంకం codelet_list_అంకె = FF_ARRAY_ELEMS(codelet_list);

స్థిర స్థిరరాశి పూర్ణాంకం cpu_slow_ముసుగు = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

స్థిర స్థిరరాశి పూర్ణాంకం cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

స్థిర పూర్ణాంకం get_codelet_prio(స్థిరరాశి FFTXCodelet *cd, పూర్ణాంకం cpu_flags, పూర్ణాంకం len)
{
    పూర్ణాంకం prio = cd->prio;
    పూర్ణాంకం max_గుణకం = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ఒకవేళ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ఒకవేళ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ఒకవేళ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ఒకవేళ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    కొరకు (పూర్ణాంకం i = 0; i < TX_MAX_SUB; i++)
        max_గుణకం = FFMAX(cd->factors[i], max_గుణకం);
    ఒకవేళ (max_గుణకం)
        prio += 16*max_గుణకం;

    తిరిగి prio;
}

రకనిర్వచనం నిర్మాణం FFTXLenDecomp {
    పూర్ణాంకం len;
    పూర్ణాంకం len2;
    పూర్ణాంకం prio;
    స్థిరరాశి FFTXCodelet *cd;
} FFTXLenDecomp;

స్థిర పూర్ణాంకం cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    తిరిగి FFDIFFSIGN(b->prio, a->prio);
}

పూర్ణాంకం ff_tx_decompose_నిడివి(పూర్ణాంకం dst[TX_MAX_DECOMPOSITIONS], గణన AVTXType type,
                           పూర్ణాంకం len, పూర్ణాంకం inv)
{
    పూర్ణాంకం nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    పూర్ణాంకం codelet_list_idx = codelet_list_అంకె;

    స్థిరరాశి పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    అయితే (codelet_list_idx--) {
        స్థిరరాశి FFTXCodelet * స్థిరరాశి * list = codelet_list[codelet_list_idx];
        స్థిరరాశి FFTXCodelet *cd = ఖాళీ;

        అయితే ((cd = *list++)) {
            పూర్ణాంకం fl = len;
            పూర్ణాంకం skip = 0, prio;
            పూర్ణాంకం factors_లబ్ధం = 1, factors_mod = 0;

            ఒకవేళ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                వెళ్ళు క్రమీకరించు;

            /* Check if the type matches */
            ఒకవేళ (cd->type != TX_TYPE_ANY && type != cd->type)
                కొనసాగు;

            /* Check direction for non-orthogonal codelets */
            ఒకవేళ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_నిండిన_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_గమ్యం_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_గమ్యం_IMAGINARY)) && inv))
                కొనసాగు;

            /* Check if the CPU supports the required ISA */
            ఒకవేళ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ముసుగు)))
                కొనసాగు;

            కొరకు (పూర్ణాంకం i = 0; i < TX_MAX_FACTORS; i++) {
                ఒకవేళ (!cd->factors[i] || (fl == 1))
                    ఆపు;

                ఒకవేళ (cd->factors[i] == TX_గుణకం_ANY) {
                    factors_mod++;
                    factors_లబ్ధం *= fl;
                } లేకపోతే ఒకవేళ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ఒకవేళ (cd->factors[i] == 2) {
                        పూర్ణాంకం b = ff_ctz(fl);
                        fl >>= b;
                        factors_లబ్ధం <<= b;
                    } లేకపోతే {
                        చేయి {
                            fl /= cd->factors[i];
                            factors_లబ్ధం *= cd->factors[i];
                        } అయితే (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ఒకవేళ ((factors_mod < cd->nb_factors) || (len == factors_లబ్ధం))
                కొనసాగు;

            ఒకవేళ (av_గరిష్ఠ_సామాన్య_భాజకం(factors_లబ్ధం, fl) != 1)
                కొనసాగు;

            /* Check if length is supported and factorization was successful */
            ఒకవేళ ((factors_లబ్ధం < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_లబ్ధం > cd->max_len)))
                కొనసాగు;

            prio = get_codelet_prio(cd, cpu_flags, factors_లబ్ధం) * factors_లబ్ధం;

            /* Check for duplicates */
            కొరకు (పూర్ణాంకం i = 0; i < nb_decomp; i++) {
                ఒకవేళ (factors_లబ్ధం == ld[i].len) {
                    /* Update priority if new one is higher */
                    ఒకవేళ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ఆపు;
                }
            }

            /* Add decomposition if unique */
            ఒకవేళ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_లబ్ధం;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ఒకవేళ (!nb_decomp)
        తిరిగి AVERROR(EINVAL);

క్రమీకరించు:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    కొరకు (పూర్ణాంకం i = 0; i < nb_decomp; i++) {
        ఒకవేళ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        లేకపోతే
            dst[i] = ld[i].len;
    }

    తిరిగి nb_decomp;
}

పూర్ణాంకం ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*పరిమాణం(*s->map));
    ఒకవేళ (!s->map)
        తిరిగి AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ఒకవేళ (s->inv) /* Reversing the ACs flips the transform direction */
        కొరకు (పూర్ణాంకం i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    లేకపోతే
        కొరకు (పూర్ణాంకం i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    తిరిగి 0;
}

#ఒకవేళ !CONFIG_SMALL
స్థిర శూన్య print_flags(AVBPrint *bp, uint64_t f)
{
    పూర్ణాంకం prev = 0;
    స్థిరరాశి అక్షరం *sep = ", ";
    av_bprintf(bp, "flags: [");
    ఒకవేళ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ఒకవేళ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ఒకవేళ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ఒకవేళ ((f & FF_TX_బహిర్గతం_యొక్క_ఉంచు) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ఒకవేళ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ఒకవేళ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ఒకవేళ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ఒకవేళ ((f & AV_TX_నిండిన_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ఒకవేళ ((f & AV_TX_REAL_గమ్యం_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ఒకవేళ ((f & AV_TX_REAL_గమ్యం_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ఒకవేళ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

స్థిర శూన్య print_type(AVBPrint *bp, గణన AVTXType type)
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

స్థిర శూన్య print_cd_info(స్థిరరాశి FFTXCodelet *cd, పూర్ణాంకం prio, పూర్ణాంకం len, పూర్ణాంకం print_prio,
                          పూర్ణాంకం log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_కొలత_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ఒకవేళ (!len) {
        ఒకవేళ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ఒకవేళ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        లేకపోతే
            av_bprintf(&bp, "%i", cd->max_len);
    } లేకపోతే {
        av_bprintf(&bp, "%i", len);
    }

    ఒకవేళ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ఒకవేళ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        లేకపోతే
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        కొరకు (పూర్ణాంకం i = 0; i < TX_MAX_FACTORS; i++) {
            ఒకవేళ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ఒకవేళ (cd->factors[i] == TX_గుణకం_ANY)
                av_bprintf(&bp, "any");
            లేకపోతే ఒకవేళ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            లేకపోతే
                ఆపు;
        }

        av_bprintf(&bp, "], ");
    } లేకపోతే {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ఒకవేళ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ఖాళీ, log_level, "%s\n", bp.str);
}

స్థిర శూన్య print_tx_structure(AVTXContext *s, పూర్ణాంకం లోతు)
{
    స్థిరరాశి FFTXCodelet *cd = s->cd_self;

    కొరకు (పూర్ణాంకం i = 0; i <= లోతు; i++)
        av_log(ఖాళీ, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    కొరకు (పూర్ణాంకం i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], లోతు + 1);
}
#అయితే_ముగింపు /* CONFIG_SMALL */

రకనిర్వచనం నిర్మాణం TXCodelet_సరిపోలిక {
    స్థిరరాశి FFTXCodelet *cd;
    పూర్ణాంకం prio;
} TXCodelet_సరిపోలిక;

స్థిర పూర్ణాంకం cmp_matches(TXCodelet_సరిపోలిక *a, TXCodelet_సరిపోలిక *b)
{
    తిరిగి FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
స్థిర అంతఃవరుస పూర్ణాంకం check_cd_factors(స్థిరరాశి FFTXCodelet *cd, పూర్ణాంకం len)
{
    పూర్ణాంకం matches = 0, any_flag = 0;

    కొరకు (పూర్ణాంకం i = 0; i < TX_MAX_FACTORS; i++) {
        పూర్ణాంకం గుణకం = cd->factors[i];

        ఒకవేళ (గుణకం == TX_గుణకం_ANY) {
            any_flag = 1;
            matches++;
            కొనసాగు;
        } లేకపోతే ఒకవేళ (len <= 1 || !గుణకం) {
            ఆపు;
        } లేకపోతే ఒకవేళ (గుణకం == 2) { /* Fast path */
            పూర్ణాంకం బిట్లు_2 = ff_ctz(len);
            ఒకవేళ (!బిట్లు_2)
                కొనసాగు; /* Factor not supported */

            len >>= బిట్లు_2;
            matches++;
        } లేకపోతే {
            పూర్ణాంకం res = len % గుణకం;
            ఒకవేళ (res)
                కొనసాగు; /* Factor not supported */

            అయితే (!res) {
                len /= గుణకం;
                res = len % గుణకం;
            }
            matches++;
        }
    }

    తిరిగి (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold పూర్ణాంకం ff_tx_init_subtx(AVTXContext *s, గణన AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             పూర్ణాంకం len, పూర్ణాంకం inv, స్థిరరాశి శూన్య *scale)
{
    పూర్ణాంకం ret = 0;
    AVTXContext *sub = ఖాళీ;
    TXCodelet_సరిపోలిక *cd_tmp, *cd_matches = ఖాళీ;
    గుర్తులేని పూర్ణాంకం cd_matches_కొలత = 0;
    పూర్ణాంకం codelet_list_idx = codelet_list_అంకె;
    పూర్ణాంకం nb_cd_matches = 0;
#ఒకవేళ !CONFIG_SMALL
    AVBPrint bp;
#అయితే_ముగింపు

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    స్థిరరాశి పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_ముసుగు = AV_TX_నిండిన_IMDCT |
                            AV_TX_REAL_గమ్యం_REAL |
                            AV_TX_REAL_గమ్యం_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ఒకవేళ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ఒకవేళ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_బహిర్గతం_యొక్క_ఉంచు))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_బహిర్గతం_యొక్క_ఉంచు);
    ఒకవేళ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    అయితే (codelet_list_idx--) {
        స్థిరరాశి FFTXCodelet * స్థిరరాశి * list = codelet_list[codelet_list_idx];
        స్థిరరాశి FFTXCodelet *cd = ఖాళీ;

        అయితే ((cd = *list++)) {
            /* Check if the type matches */
            ఒకవేళ (cd->type != TX_TYPE_ANY && type != cd->type)
                కొనసాగు;

            /* Check direction for non-orthogonal codelets */
            ఒకవేళ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_నిండిన_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_గమ్యం_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_గమ్యం_IMAGINARY)) && inv))
                కొనసాగు;

            /* Check if the requested flags match from both sides */
            ఒకవేళ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_ముసుగు & cd->flags) != (req_flags & inv_req_ముసుగు)))
                కొనసాగు;

            /* Check if length is supported */
            ఒకవేళ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                కొనసాగు;

            /* Check if the CPU supports the required ISA */
            ఒకవేళ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_ముసుగు)))
                కొనసాగు;

            /* Check for factors */
            ఒకవేళ (!check_cd_factors(cd, len))
                కొనసాగు;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_కొలత,
                                     పరిమాణం(*cd_tmp) * (nb_cd_matches + 1));
            ఒకవేళ (!cd_tmp) {
                av_free(cd_matches);
                తిరిగి AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ఒకవేళ !CONFIG_SMALL
    /* Print debugging info */
    av_bprint_init(&bp, 0, AV_BPRINT_కొలత_AUTOMATIC);
    av_bprintf(&bp, "For transform of length %i, %s, ", len,
               inv ? "inverse" : "forward");
    print_type(&bp, type);
    av_bprintf(&bp, ", ");
    print_flags(&bp, flags);
    av_bprintf(&bp, ", found %i matches%s", nb_cd_matches,
               nb_cd_matches ? ":" : ".");
#అయితే_ముగింపు

    /* No matches found */
    ఒకవేళ (!nb_cd_matches)
        తిరిగి AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodelet_సరిపోలిక, cmp_matches);

#ఒకవేళ !CONFIG_SMALL
    av_log(ఖాళీ, AV_LOG_TRACE, "%s\n", bp.str);

    కొరకు (పూర్ణాంకం i = 0; i < nb_cd_matches; i++) {
        av_log(ఖాళీ, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#అయితే_ముగింపు

    ఒకవేళ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*పరిమాణం(*sub));
        ఒకవేళ (!sub) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు చివర;
        }
    }

    /* Attempt to initialize each */
    కొరకు (పూర్ణాంకం i = 0; i < nb_cd_matches; i++) {
        స్థిరరాశి FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        ఒకవేళ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ఒకవేళ (ret >= 0) {
            ఒకవేళ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*పరిమాణం(*sctx->map));
                ఒకవేళ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    వెళ్ళు చివర;
                }

                కొరకు (పూర్ణాంకం i = 0; i < len; i++)
                    sctx->map[i] = i;
            } లేకపోతే ఒకవేళ (opts && (opts->map_dir != sctx->map_dir)) {
                పూర్ణాంకం *tmp = av_malloc(len*పరిమాణం(*sctx->map));
                ఒకవేళ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    వెళ్ళు చివర;
                }

                జ్ఞాపకం_నకలు(tmp, sctx->map, len*పరిమాణం(*sctx->map));

                కొరకు (పూర్ణాంకం i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            వెళ్ళు చివర;
        }

        s->fn[s->nb_sub] = ఖాళీ;
        s->cd[s->nb_sub] = ఖాళీ;

        reset_ctx(sctx, 0);
        ఒకవేళ (ret == AVERROR(ENOMEM))
            ఆపు;
    }

    ఒకవేళ (!s->nb_sub)
        av_freep(&s->sub);

చివర:
    av_free(cd_matches);
    తిరిగి ret;
}

av_cold పూర్ణాంకం av_tx_init(AVTXContext **ctx, av_tx_fn *tx, గణన AVTXType type,
                       పూర్ణాంకం inv, పూర్ణాంకం len, స్థిరరాశి శూన్య *scale, uint64_t flags)
{
    పూర్ణాంకం ret;
    AVTXContext tmp = { 0 };
    స్థిరరాశి ద్విగుణ default_scale_d = 1.0;
    స్థిరరాశి దశాంశం  default_scale_f = 1.0f;

    ఒకవేళ (!len || type >= AV_TX_NB || !ctx || !tx)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ఒకవేళ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_బహిర్గతం_యొక్క_ఉంచు;

    ఒకవేళ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    లేకపోతే ఒకవేళ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ఖాళీ, len, inv, scale);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ఒకవేళ !CONFIG_SMALL
    av_log(ఖాళీ, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#అయితే_ముగింపు

    తిరిగి ret;
}
