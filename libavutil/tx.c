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

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "intmath.h"
#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "qsort.h"
#அந்தர்பாவ "bprint.h"

#அந்தர்பாவ "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
நிலையான av_always_inline முழு mulinv(முழு n, முழு m)
{
    n = n % m;
    க்கு (முழு x = 1; x < m; x++)
        எனில் (((n * x) % m) == 1)
            திரும்பு x;
    av_assert0(0); /* Never reached */
    திரும்பு 0;
}

முழு ff_tx_gen_pfa_உள்ளீடு_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            முழு d1, முழு d2)
{
    மாறிலி முழு sl = d1*d2;

    s->map = av_malloc(s->len*அளவு(*s->map));
    எனில் (!s->map)
        திரும்பு AVERROR(ENOMEM);

    க்கு (முழு k = 0; k < s->len; k += sl) {
        எனில் (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            க்கு (முழு m = 0; m < d2; m++)
                க்கு (முழு n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } இல்லையெனில் {
            க்கு (முழு m = 0; m < d2; m++)
                க்கு (முழு n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        எனில் (s->inv)
            க்கு (முழு w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(முழு, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    திரும்பு 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
முழு ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               முழு inv, முழு n, முழு m)
{
    முழு *in_map, *out_map;
    மாறிலி முழு len = n*m;    /* Will not be equal to s->len for MDCTs */
    முழு m_inv, n_inv;

    /* Make sure the numbers are coprime */
    எனில் (av_gcd(n, m) != 1)
        திரும்பு AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    எனில் (!(s->map = av_malloc(2*len*அளவு(*s->map))))
        திரும்பு AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    எனில் (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        க்கு (முழு j = 0; j < m; j++) {
            க்கு (முழு i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } இல்லையெனில் {
        க்கு (முழு j = 0; j < m; j++) {
            க்கு (முழு i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    எனில் (inv) {
        க்கு (முழு i = 0; i < m; i++) {
            முழு *in = &in_map[i*n + 1]; /* Skip the DC */
            க்கு (முழு j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(முழு, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    திரும்பு 0;
}

நிலையான உள்வரி முழு split_radix_permutation(முழு i, முழு len, முழு inv)
{
    len >>= 1;
    எனில் (len <= 1)
        திரும்பு i & 1;
    எனில் (!(i & len))
        திரும்பு split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    திரும்பு split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

முழு ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    முழு len = s->len;

    எனில் (!(s->map = av_malloc(len*அளவு(*s->map))))
        திரும்பு AVERROR(ENOMEM);

    எனில் (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        க்கு (முழு i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } இல்லையெனில் {
        க்கு (முழு i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    திரும்பு 0;
}

முழு ff_tx_gen_inplace_map(AVTXContext *s, முழு len)
{
    முழு *src_map, out_map_idx = 0;

    எனில் (!s->sub || !s->sub->map)
        திரும்பு AVERROR(EINVAL);

    எனில் (!(s->map = av_mallocz(len*அளவு(*s->map))))
        திரும்பு AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    க்கு (முழு src = 1; src < s->len; src++) {
        முழு dst = src_map[src];
        முழு found = 0;

        எனில் (dst <= src)
            தொடர்;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        செய் {
            க்கு (முழு j = 0; j < out_map_idx; j++) {
                எனில் (dst == s->map[j]) {
                    found = 1;
                    நிறுத்து;
                }
            }
            dst = src_map[dst];
        } போது (dst != src && !found);

        எனில் (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    திரும்பு 0;
}

நிலையான வெறுமை parity_revtab_generator(முழு *revtab, முழு n, முழு inv, முழு offset,
                                    முழு is_dual, முழு dual_உயர்வு, முழு len,
                                    முழு basis, முழு dual_stride, முழு inv_lookup)
{
    len >>= 1;

    எனில் (len <= basis) {
        முழு k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_உயர்வு = is_dual & dual_உயர்வு;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_உயர்வு*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_உயர்வு)*len + dual_உயர்வு*len;

        க்கு (முழு i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            எனில் (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } இல்லையெனில் {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            எனில் (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        திரும்பு;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

முழு ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, முழு len, முழு inv,
                                        FFTXCodeletOptions *opts,
                                        முழு basis, முழு dual_stride)
{
    basis >>= 1;
    எனில் (len < basis)
        திரும்பு AVERROR(EINVAL);

    எனில் (!(s->map = av_mallocz(len*அளவு(*s->map))))
        திரும்பு AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    திரும்பு 0;
}

நிலையான வெறுமை reset_ctx(AVTXContext *s, முழு free_sub)
{
    எனில் (!s)
        திரும்பு;

    எனில் (s->sub)
        க்கு (முழு i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    எனில் (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    எனில் (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = வெற்று;
    memset(s->fn, 0, அளவு(s->fn));
}

வெறுமை ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold வெறுமை av_tx_uninit(AVTXContext **ctx)
{
    எனில் (!(*ctx))
        திரும்பு;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

நிலையான av_cold முழு ff_tx_null_init(AVTXContext *s, மாறிலி FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   முழு len, முழு inv, மாறிலி வெறுமை *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    எனில் (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        திரும்பு AVERROR(EINVAL);
    திரும்பு 0;
}

/* Null transform when the length is 1 */
நிலையான வெறுமை ff_tx_null(AVTXContext *s, வெறுமை *_out, வெறுமை *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

நிலையான மாறிலி FFTXCodelet ff_tx_null_def = {
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

நிலையான மாறிலி FFTXCodelet * மாறிலி ff_tx_null_list[] = {
    &ff_tx_null_def,
    வெற்று,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
நிலையான மாறிலி FFTXCodelet * மாறிலி * மாறிலி codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#எனில் HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#எனில் ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
நிலையான மாறிலி முழு codelet_list_இலக்கம் = FF_ARRAY_ELEMS(codelet_list);

நிலையான மாறிலி முழு cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

நிலையான மாறிலி முழு cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

நிலையான முழு get_codelet_prio(மாறிலி FFTXCodelet *cd, முழு cpu_flags, முழு len)
{
    முழு prio = cd->prio;
    முழு max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        எனில் ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    எனில் ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    எனில் ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    எனில் ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    க்கு (முழு i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    எனில் (max_factor)
        prio += 16*max_factor;

    திரும்பு prio;
}

வகைவரை கட்டமைப்பு FFTXLenDecomp {
    முழு len;
    முழு len2;
    முழு prio;
    மாறிலி FFTXCodelet *cd;
} FFTXLenDecomp;

நிலையான முழு cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    திரும்பு FFDIFFSIGN(b->prio, a->prio);
}

முழு ff_tx_decompose_length(முழு dst[TX_MAX_DECOMPOSITIONS], எண்ணிக்கை AVTXType type,
                           முழு len, முழு inv)
{
    முழு nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    முழு codelet_list_idx = codelet_list_இலக்கம்;

    மாறிலி முழு cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    போது (codelet_list_idx--) {
        மாறிலி FFTXCodelet * மாறிலி * list = codelet_list[codelet_list_idx];
        மாறிலி FFTXCodelet *cd = வெற்று;

        போது ((cd = *list++)) {
            முழு fl = len;
            முழு skip = 0, prio;
            முழு factors_product = 1, factors_mod = 0;

            எனில் (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                செல் sort;

            /* Check if the type matches */
            எனில் (cd->type != TX_TYPE_ANY && type != cd->type)
                தொடர்;

            /* Check direction for non-orthogonal codelets */
            எனில் (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                தொடர்;

            /* Check if the CPU supports the required ISA */
            எனில் (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                தொடர்;

            க்கு (முழு i = 0; i < TX_MAX_FACTORS; i++) {
                எனில் (!cd->factors[i] || (fl == 1))
                    நிறுத்து;

                எனில் (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } இல்லையெனில் எனில் (!(fl % cd->factors[i])) {
                    factors_mod++;
                    எனில் (cd->factors[i] == 2) {
                        முழு b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } இல்லையெனில் {
                        செய் {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } போது (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            எனில் ((factors_mod < cd->nb_factors) || (len == factors_product))
                தொடர்;

            எனில் (av_gcd(factors_product, fl) != 1)
                தொடர்;

            /* Check if length is supported and factorization was successful */
            எனில் ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                தொடர்;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            க்கு (முழு i = 0; i < nb_decomp; i++) {
                எனில் (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    எனில் (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    நிறுத்து;
                }
            }

            /* Add decomposition if unique */
            எனில் (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    எனில் (!nb_decomp)
        திரும்பு AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    க்கு (முழு i = 0; i < nb_decomp; i++) {
        எனில் (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        இல்லையெனில்
            dst[i] = ld[i].len;
    }

    திரும்பு nb_decomp;
}

முழு ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*அளவு(*s->map));
    எனில் (!s->map)
        திரும்பு AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    எனில் (s->inv) /* Reversing the ACs flips the transform direction */
        க்கு (முழு i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    இல்லையெனில்
        க்கு (முழு i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    திரும்பு 0;
}

#எனில் !CONFIG_SMALL
நிலையான வெறுமை print_flags(AVBPrint *bp, uint64_t f)
{
    முழு prev = 0;
    மாறிலி எழுத்து *sep = ", ";
    av_bprintf(bp, "flags: [");
    எனில் ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    எனில் ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    எனில் ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    எனில் ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    எனில் ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    எனில் ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    எனில் ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    எனில் ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    எனில் ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    எனில் ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    எனில் ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

நிலையான வெறுமை print_type(AVBPrint *bp, எண்ணிக்கை AVTXType type)
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

நிலையான வெறுமை print_cd_info(மாறிலி FFTXCodelet *cd, முழு prio, முழு len, முழு print_prio,
                          முழு log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    எனில் (!len) {
        எனில் (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        எனில் (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        இல்லையெனில்
            av_bprintf(&bp, "%i", cd->max_len);
    } இல்லையெனில் {
        av_bprintf(&bp, "%i", len);
    }

    எனில் (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        எனில் (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        இல்லையெனில்
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        க்கு (முழு i = 0; i < TX_MAX_FACTORS; i++) {
            எனில் (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            எனில் (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            இல்லையெனில் எனில் (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            இல்லையெனில்
                நிறுத்து;
        }

        av_bprintf(&bp, "], ");
    } இல்லையெனில் {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    எனில் (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(வெற்று, log_level, "%s\n", bp.str);
}

நிலையான வெறுமை print_tx_structure(AVTXContext *s, முழு depth)
{
    மாறிலி FFTXCodelet *cd = s->cd_self;

    க்கு (முழு i = 0; i <= depth; i++)
        av_log(வெற்று, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    க்கு (முழு i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

வகைவரை கட்டமைப்பு TXCodeletMatch {
    மாறிலி FFTXCodelet *cd;
    முழு prio;
} TXCodeletMatch;

நிலையான முழு cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    திரும்பு FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
நிலையான உள்வரி முழு check_cd_factors(மாறிலி FFTXCodelet *cd, முழு len)
{
    முழு matches = 0, any_flag = 0;

    க்கு (முழு i = 0; i < TX_MAX_FACTORS; i++) {
        முழு factor = cd->factors[i];

        எனில் (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            தொடர்;
        } இல்லையெனில் எனில் (len <= 1 || !factor) {
            நிறுத்து;
        } இல்லையெனில் எனில் (factor == 2) { /* Fast path */
            முழு bits_2 = ff_ctz(len);
            எனில் (!bits_2)
                தொடர்; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } இல்லையெனில் {
            முழு res = len % factor;
            எனில் (res)
                தொடர்; /* Factor not supported */

            போது (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    திரும்பு (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold முழு ff_tx_init_subtx(AVTXContext *s, எண்ணிக்கை AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             முழு len, முழு inv, மாறிலி வெறுமை *scale)
{
    முழு ret = 0;
    AVTXContext *sub = வெற்று;
    TXCodeletMatch *cd_tmp, *cd_matches = வெற்று;
    unsigned முழு cd_matches_size = 0;
    முழு codelet_list_idx = codelet_list_இலக்கம்;
    முழு nb_cd_matches = 0;
#எனில் !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    மாறிலி முழு cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    எனில் (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    எனில் ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    எனில் ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    போது (codelet_list_idx--) {
        மாறிலி FFTXCodelet * மாறிலி * list = codelet_list[codelet_list_idx];
        மாறிலி FFTXCodelet *cd = வெற்று;

        போது ((cd = *list++)) {
            /* Check if the type matches */
            எனில் (cd->type != TX_TYPE_ANY && type != cd->type)
                தொடர்;

            /* Check direction for non-orthogonal codelets */
            எனில் (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                தொடர்;

            /* Check if the requested flags match from both sides */
            எனில் (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                தொடர்;

            /* Check if length is supported */
            எனில் ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                தொடர்;

            /* Check if the CPU supports the required ISA */
            எனில் (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                தொடர்;

            /* Check for factors */
            எனில் (!check_cd_factors(cd, len))
                தொடர்;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     அளவு(*cd_tmp) * (nb_cd_matches + 1));
            எனில் (!cd_tmp) {
                av_free(cd_matches);
                திரும்பு AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#எனில் !CONFIG_SMALL
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
    எனில் (!nb_cd_matches)
        திரும்பு AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#எனில் !CONFIG_SMALL
    av_log(வெற்று, AV_LOG_TRACE, "%s\n", bp.str);

    க்கு (முழு i = 0; i < nb_cd_matches; i++) {
        av_log(வெற்று, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    எனில் (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*அளவு(*sub));
        எனில் (!sub) {
            ret = AVERROR(ENOMEM);
            செல் end;
        }
    }

    /* Attempt to initialize each */
    க்கு (முழு i = 0; i < nb_cd_matches; i++) {
        மாறிலி FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        எனில் (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        எனில் (ret >= 0) {
            எனில் (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*அளவு(*sctx->map));
                எனில் (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    செல் end;
                }

                க்கு (முழு i = 0; i < len; i++)
                    sctx->map[i] = i;
            } இல்லையெனில் எனில் (opts && (opts->map_dir != sctx->map_dir)) {
                முழு *tmp = av_malloc(len*அளவு(*sctx->map));
                எனில் (!tmp) {
                    ret = AVERROR(ENOMEM);
                    செல் end;
                }

                memcpy(tmp, sctx->map, len*அளவு(*sctx->map));

                க்கு (முழு i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            செல் end;
        }

        s->fn[s->nb_sub] = வெற்று;
        s->cd[s->nb_sub] = வெற்று;

        reset_ctx(sctx, 0);
        எனில் (ret == AVERROR(ENOMEM))
            நிறுத்து;
    }

    எனில் (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    திரும்பு ret;
}

av_cold முழு av_tx_init(AVTXContext **ctx, av_tx_fn *tx, எண்ணிக்கை AVTXType type,
                       முழு inv, முழு len, மாறிலி வெறுமை *scale, uint64_t flags)
{
    முழு ret;
    AVTXContext tmp = { 0 };
    மாறிலி இரட்டை default_scale_d = 1.0;
    மாறிலி தசம  default_scale_f = 1.0f;

    எனில் (!len || type >= AV_TX_NB || !ctx || !tx)
        திரும்பு AVERROR(EINVAL);

    எனில் (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    எனில் (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    எனில் (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    இல்லையெனில் எனில் (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, வெற்று, len, inv, scale);
    எனில் (ret < 0)
        திரும்பு ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#எனில் !CONFIG_SMALL
    av_log(வெற்று, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    திரும்பு ret;
}
