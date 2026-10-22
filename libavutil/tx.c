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
स्थिर av_always_inline पूर्णांक mulinv(पूर्णांक n, पूर्णांक m)
{
    n = n % m;
    साठी (पूर्णांक x = 1; x < m; x++)
        जर (((n * x) % m) == 1)
            परत x;
    av_assert0(0); /* Never reached */
    परत 0;
}

पूर्णांक ff_tx_gen_pfa_आदान_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            पूर्णांक d1, पूर्णांक d2)
{
    स्थिरांक पूर्णांक sl = d1*d2;

    s->map = av_malloc(s->len*आकार(*s->map));
    जर (!s->map)
        परत AVERROR(ENOMEM);

    साठी (पूर्णांक k = 0; k < s->len; k += sl) {
        जर (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            साठी (पूर्णांक m = 0; m < d2; m++)
                साठी (पूर्णांक n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } अन्यथा {
            साठी (पूर्णांक m = 0; m < d2; m++)
                साठी (पूर्णांक n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        जर (s->inv)
            साठी (पूर्णांक w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(पूर्णांक, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    परत 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
पूर्णांक ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               पूर्णांक inv, पूर्णांक n, पूर्णांक m)
{
    पूर्णांक *in_map, *out_map;
    स्थिरांक पूर्णांक len = n*m;    /* Will not be equal to s->len for MDCTs */
    पूर्णांक m_inv, n_inv;

    /* Make sure the numbers are coprime */
    जर (av_gcd(n, m) != 1)
        परत AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    जर (!(s->map = av_malloc(2*len*आकार(*s->map))))
        परत AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    जर (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        साठी (पूर्णांक j = 0; j < m; j++) {
            साठी (पूर्णांक i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } अन्यथा {
        साठी (पूर्णांक j = 0; j < m; j++) {
            साठी (पूर्णांक i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    जर (inv) {
        साठी (पूर्णांक i = 0; i < m; i++) {
            पूर्णांक *in = &in_map[i*n + 1]; /* Skip the DC */
            साठी (पूर्णांक j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(पूर्णांक, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    परत 0;
}

स्थिर ओळीत पूर्णांक split_radix_permutation(पूर्णांक i, पूर्णांक len, पूर्णांक inv)
{
    len >>= 1;
    जर (len <= 1)
        परत i & 1;
    जर (!(i & len))
        परत split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    परत split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

पूर्णांक ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    पूर्णांक len = s->len;

    जर (!(s->map = av_malloc(len*आकार(*s->map))))
        परत AVERROR(ENOMEM);

    जर (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        साठी (पूर्णांक i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } अन्यथा {
        साठी (पूर्णांक i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    परत 0;
}

पूर्णांक ff_tx_gen_inplace_map(AVTXContext *s, पूर्णांक len)
{
    पूर्णांक *src_map, out_map_idx = 0;

    जर (!s->sub || !s->sub->map)
        परत AVERROR(EINVAL);

    जर (!(s->map = av_mallocz(len*आकार(*s->map))))
        परत AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    साठी (पूर्णांक src = 1; src < s->len; src++) {
        पूर्णांक dst = src_map[src];
        पूर्णांक found = 0;

        जर (dst <= src)
            सुरूठेवा;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        करा {
            साठी (पूर्णांक j = 0; j < out_map_idx; j++) {
                जर (dst == s->map[j]) {
                    found = 1;
                    थांबा;
                }
            }
            dst = src_map[dst];
        } पर्यंत (dst != src && !found);

        जर (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    परत 0;
}

स्थिर शून्य parity_revtab_generator(पूर्णांक *revtab, पूर्णांक n, पूर्णांक inv, पूर्णांक offset,
                                    पूर्णांक is_dual, पूर्णांक dual_वरचा, पूर्णांक len,
                                    पूर्णांक basis, पूर्णांक dual_stride, पूर्णांक inv_lookup)
{
    len >>= 1;

    जर (len <= basis) {
        पूर्णांक k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_वरचा = is_dual & dual_वरचा;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_वरचा*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_वरचा)*len + dual_वरचा*len;

        साठी (पूर्णांक i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            जर (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } अन्यथा {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            जर (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        परत;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

पूर्णांक ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, पूर्णांक len, पूर्णांक inv,
                                        FFTXCodeletOptions *opts,
                                        पूर्णांक basis, पूर्णांक dual_stride)
{
    basis >>= 1;
    जर (len < basis)
        परत AVERROR(EINVAL);

    जर (!(s->map = av_mallocz(len*आकार(*s->map))))
        परत AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    परत 0;
}

स्थिर शून्य reset_ctx(AVTXContext *s, पूर्णांक free_sub)
{
    जर (!s)
        परत;

    जर (s->sub)
        साठी (पूर्णांक i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    जर (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    जर (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = रिक्त;
    स_रखो(s->fn, 0, आकार(s->fn));
}

शून्य ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold शून्य av_tx_uninit(AVTXContext **ctx)
{
    जर (!(*ctx))
        परत;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

स्थिर av_cold पूर्णांक ff_tx_null_init(AVTXContext *s, स्थिरांक FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   पूर्णांक len, पूर्णांक inv, स्थिरांक शून्य *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    जर (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        परत AVERROR(EINVAL);
    परत 0;
}

/* Null transform when the length is 1 */
स्थिर शून्य ff_tx_null(AVTXContext *s, शून्य *_out, शून्य *_in, सूचक_भेद_प्रकार stride)
{
    स_नकल(_out, _in, stride);
}

स्थिर स्थिरांक FFTXCodelet ff_tx_null_def = {
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

स्थिर स्थिरांक FFTXCodelet * स्थिरांक ff_tx_null_list[] = {
    &ff_tx_null_def,
    रिक्त,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
स्थिर स्थिरांक FFTXCodelet * स्थिरांक * स्थिरांक codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#जर HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#जर ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
स्थिर स्थिरांक पूर्णांक codelet_list_अंक = FF_ARRAY_ELEMS(codelet_list);

स्थिर स्थिरांक पूर्णांक cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

स्थिर स्थिरांक पूर्णांक cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

स्थिर पूर्णांक get_codelet_prio(स्थिरांक FFTXCodelet *cd, पूर्णांक cpu_flags, पूर्णांक len)
{
    पूर्णांक prio = cd->prio;
    पूर्णांक max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        जर ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    जर ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    जर ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    जर ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    साठी (पूर्णांक i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    जर (max_factor)
        prio += 16*max_factor;

    परत prio;
}

प्रकारव्याख्या संरचना FFTXLenDecomp {
    पूर्णांक len;
    पूर्णांक len2;
    पूर्णांक prio;
    स्थिरांक FFTXCodelet *cd;
} FFTXLenDecomp;

स्थिर पूर्णांक cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    परत FFDIFFSIGN(b->prio, a->prio);
}

पूर्णांक ff_tx_decompose_length(पूर्णांक dst[TX_MAX_DECOMPOSITIONS], गणना AVTXType type,
                           पूर्णांक len, पूर्णांक inv)
{
    पूर्णांक nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    पूर्णांक codelet_list_idx = codelet_list_अंक;

    स्थिरांक पूर्णांक cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    पर्यंत (codelet_list_idx--) {
        स्थिरांक FFTXCodelet * स्थिरांक * list = codelet_list[codelet_list_idx];
        स्थिरांक FFTXCodelet *cd = रिक्त;

        पर्यंत ((cd = *list++)) {
            पूर्णांक fl = len;
            पूर्णांक skip = 0, prio;
            पूर्णांक factors_product = 1, factors_mod = 0;

            जर (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                जा sort;

            /* Check if the type matches */
            जर (cd->type != TX_TYPE_ANY && type != cd->type)
                सुरूठेवा;

            /* Check direction for non-orthogonal codelets */
            जर (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                सुरूठेवा;

            /* Check if the CPU supports the required ISA */
            जर (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                सुरूठेवा;

            साठी (पूर्णांक i = 0; i < TX_MAX_FACTORS; i++) {
                जर (!cd->factors[i] || (fl == 1))
                    थांबा;

                जर (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } अन्यथा जर (!(fl % cd->factors[i])) {
                    factors_mod++;
                    जर (cd->factors[i] == 2) {
                        पूर्णांक b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } अन्यथा {
                        करा {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } पर्यंत (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            जर ((factors_mod < cd->nb_factors) || (len == factors_product))
                सुरूठेवा;

            जर (av_gcd(factors_product, fl) != 1)
                सुरूठेवा;

            /* Check if length is supported and factorization was successful */
            जर ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                सुरूठेवा;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            साठी (पूर्णांक i = 0; i < nb_decomp; i++) {
                जर (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    जर (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    थांबा;
                }
            }

            /* Add decomposition if unique */
            जर (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    जर (!nb_decomp)
        परत AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    साठी (पूर्णांक i = 0; i < nb_decomp; i++) {
        जर (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        अन्यथा
            dst[i] = ld[i].len;
    }

    परत nb_decomp;
}

पूर्णांक ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*आकार(*s->map));
    जर (!s->map)
        परत AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    जर (s->inv) /* Reversing the ACs flips the transform direction */
        साठी (पूर्णांक i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    अन्यथा
        साठी (पूर्णांक i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    परत 0;
}

#जर !CONFIG_SMALL
स्थिर शून्य print_flags(AVBPrint *bp, uint64_t f)
{
    पूर्णांक prev = 0;
    स्थिरांक अक्षर *sep = ", ";
    av_bprintf(bp, "flags: [");
    जर ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    जर ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    जर ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    जर ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    जर ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    जर ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    जर ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    जर ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    जर ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    जर ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    जर ((f & FF_TX_ASM_CALL) && ++prev)
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

स्थिर शून्य print_cd_info(स्थिरांक FFTXCodelet *cd, पूर्णांक prio, पूर्णांक len, पूर्णांक print_prio,
                          पूर्णांक log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    जर (!len) {
        जर (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        जर (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        अन्यथा
            av_bprintf(&bp, "%i", cd->max_len);
    } अन्यथा {
        av_bprintf(&bp, "%i", len);
    }

    जर (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        जर (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        अन्यथा
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        साठी (पूर्णांक i = 0; i < TX_MAX_FACTORS; i++) {
            जर (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            जर (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            अन्यथा जर (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            अन्यथा
                थांबा;
        }

        av_bprintf(&bp, "], ");
    } अन्यथा {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    जर (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(रिक्त, log_level, "%s\n", bp.str);
}

स्थिर शून्य print_tx_structure(AVTXContext *s, पूर्णांक depth)
{
    स्थिरांक FFTXCodelet *cd = s->cd_self;

    साठी (पूर्णांक i = 0; i <= depth; i++)
        av_log(रिक्त, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    साठी (पूर्णांक i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

प्रकारव्याख्या संरचना TXCodeletMatch {
    स्थिरांक FFTXCodelet *cd;
    पूर्णांक prio;
} TXCodeletMatch;

स्थिर पूर्णांक cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    परत FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
स्थिर ओळीत पूर्णांक check_cd_factors(स्थिरांक FFTXCodelet *cd, पूर्णांक len)
{
    पूर्णांक matches = 0, any_flag = 0;

    साठी (पूर्णांक i = 0; i < TX_MAX_FACTORS; i++) {
        पूर्णांक factor = cd->factors[i];

        जर (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            सुरूठेवा;
        } अन्यथा जर (len <= 1 || !factor) {
            थांबा;
        } अन्यथा जर (factor == 2) { /* Fast path */
            पूर्णांक bits_2 = ff_ctz(len);
            जर (!bits_2)
                सुरूठेवा; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } अन्यथा {
            पूर्णांक res = len % factor;
            जर (res)
                सुरूठेवा; /* Factor not supported */

            पर्यंत (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    परत (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold पूर्णांक ff_tx_init_subtx(AVTXContext *s, गणना AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             पूर्णांक len, पूर्णांक inv, स्थिरांक शून्य *scale)
{
    पूर्णांक ret = 0;
    AVTXContext *sub = रिक्त;
    TXCodeletMatch *cd_tmp, *cd_matches = रिक्त;
    अचिन्हित पूर्णांक cd_matches_size = 0;
    पूर्णांक codelet_list_idx = codelet_list_अंक;
    पूर्णांक nb_cd_matches = 0;
#जर !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    स्थिरांक पूर्णांक cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    जर (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    जर ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    जर ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    पर्यंत (codelet_list_idx--) {
        स्थिरांक FFTXCodelet * स्थिरांक * list = codelet_list[codelet_list_idx];
        स्थिरांक FFTXCodelet *cd = रिक्त;

        पर्यंत ((cd = *list++)) {
            /* Check if the type matches */
            जर (cd->type != TX_TYPE_ANY && type != cd->type)
                सुरूठेवा;

            /* Check direction for non-orthogonal codelets */
            जर (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                सुरूठेवा;

            /* Check if the requested flags match from both sides */
            जर (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                सुरूठेवा;

            /* Check if length is supported */
            जर ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                सुरूठेवा;

            /* Check if the CPU supports the required ISA */
            जर (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                सुरूठेवा;

            /* Check for factors */
            जर (!check_cd_factors(cd, len))
                सुरूठेवा;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     आकार(*cd_tmp) * (nb_cd_matches + 1));
            जर (!cd_tmp) {
                av_free(cd_matches);
                परत AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#जर !CONFIG_SMALL
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
    जर (!nb_cd_matches)
        परत AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#जर !CONFIG_SMALL
    av_log(रिक्त, AV_LOG_TRACE, "%s\n", bp.str);

    साठी (पूर्णांक i = 0; i < nb_cd_matches; i++) {
        av_log(रिक्त, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    जर (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*आकार(*sub));
        जर (!sub) {
            ret = AVERROR(ENOMEM);
            जा end;
        }
    }

    /* Attempt to initialize each */
    साठी (पूर्णांक i = 0; i < nb_cd_matches; i++) {
        स्थिरांक FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        जर (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        जर (ret >= 0) {
            जर (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*आकार(*sctx->map));
                जर (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    जा end;
                }

                साठी (पूर्णांक i = 0; i < len; i++)
                    sctx->map[i] = i;
            } अन्यथा जर (opts && (opts->map_dir != sctx->map_dir)) {
                पूर्णांक *tmp = av_malloc(len*आकार(*sctx->map));
                जर (!tmp) {
                    ret = AVERROR(ENOMEM);
                    जा end;
                }

                स_नकल(tmp, sctx->map, len*आकार(*sctx->map));

                साठी (पूर्णांक i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            जा end;
        }

        s->fn[s->nb_sub] = रिक्त;
        s->cd[s->nb_sub] = रिक्त;

        reset_ctx(sctx, 0);
        जर (ret == AVERROR(ENOMEM))
            थांबा;
    }

    जर (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    परत ret;
}

av_cold पूर्णांक av_tx_init(AVTXContext **ctx, av_tx_fn *tx, गणना AVTXType type,
                       पूर्णांक inv, पूर्णांक len, स्थिरांक शून्य *scale, uint64_t flags)
{
    पूर्णांक ret;
    AVTXContext tmp = { 0 };
    स्थिरांक द्विगुण default_scale_d = 1.0;
    स्थिरांक दशांश  default_scale_f = 1.0f;

    जर (!len || type >= AV_TX_NB || !ctx || !tx)
        परत AVERROR(EINVAL);

    जर (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    जर (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    जर (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    अन्यथा जर (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, रिक्त, len, inv, scale);
    जर (ret < 0)
        परत ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#जर !CONFIG_SMALL
    av_log(रिक्त, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    परत ret;
}
