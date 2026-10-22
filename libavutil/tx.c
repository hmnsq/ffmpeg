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

#ضمن "avassert.h"
#ضمن "intmath.h"
#ضمن "cpu.h"
#ضمن "mem.h"
#ضمن "qsort.h"
#ضمن "bprint.h"

#ضمن "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ساكن av_always_inline صحيح mulinv(صحيح n, صحيح m)
{
    n = n % m;
    لكل (صحيح x = 1; x < m; x++)
        إذا (((n * x) % m) == 1)
            أرجع x;
    av_assert0(0); /* Never reached */
    أرجع 0;
}

صحيح ff_tx_gen_pfa_تێخستن_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            صحيح d1, صحيح d2)
{
    ثابت صحيح sl = d1*d2;

    s->map = av_malloc(s->len*حجم(*s->map));
    إذا (!s->map)
        أرجع AVERROR(ENOMEM);

    لكل (صحيح k = 0; k < s->len; k += sl) {
        إذا (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            لكل (صحيح m = 0; m < d2; m++)
                لكل (صحيح n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } وإلا {
            لكل (صحيح m = 0; m < d2; m++)
                لكل (صحيح n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        إذا (s->inv)
            لكل (صحيح w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(صحيح, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    أرجع 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
صحيح ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               صحيح inv, صحيح n, صحيح m)
{
    صحيح *in_map, *out_map;
    ثابت صحيح len = n*m;    /* Will not be equal to s->len for MDCTs */
    صحيح m_inv, n_inv;

    /* Make sure the numbers are coprime */
    إذا (av_gcd(n, m) != 1)
        أرجع AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    إذا (!(s->map = av_malloc(2*len*حجم(*s->map))))
        أرجع AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    إذا (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        لكل (صحيح j = 0; j < m; j++) {
            لكل (صحيح i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } وإلا {
        لكل (صحيح j = 0; j < m; j++) {
            لكل (صحيح i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    إذا (inv) {
        لكل (صحيح i = 0; i < m; i++) {
            صحيح *in = &in_map[i*n + 1]; /* Skip the DC */
            لكل (صحيح j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(صحيح, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    أرجع 0;
}

ساكن مضمن صحيح split_radix_permutation(صحيح i, صحيح len, صحيح inv)
{
    len >>= 1;
    إذا (len <= 1)
        أرجع i & 1;
    إذا (!(i & len))
        أرجع split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    أرجع split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

صحيح ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    صحيح len = s->len;

    إذا (!(s->map = av_malloc(len*حجم(*s->map))))
        أرجع AVERROR(ENOMEM);

    إذا (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        لكل (صحيح i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } وإلا {
        لكل (صحيح i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    أرجع 0;
}

صحيح ff_tx_gen_inplace_map(AVTXContext *s, صحيح len)
{
    صحيح *src_map, out_map_idx = 0;

    إذا (!s->sub || !s->sub->map)
        أرجع AVERROR(EINVAL);

    إذا (!(s->map = av_mallocz(len*حجم(*s->map))))
        أرجع AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    لكل (صحيح src = 1; src < s->len; src++) {
        صحيح dst = src_map[src];
        صحيح found = 0;

        إذا (dst <= src)
            استمر;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        افعل {
            لكل (صحيح j = 0; j < out_map_idx; j++) {
                إذا (dst == s->map[j]) {
                    found = 1;
                    اكسر;
                }
            }
            dst = src_map[dst];
        } طالما (dst != src && !found);

        إذا (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    أرجع 0;
}

ساكن فراغ parity_revtab_generator(صحيح *revtab, صحيح n, صحيح inv, صحيح offset,
                                    صحيح is_dual, صحيح dual_بەرز, صحيح len,
                                    صحيح basis, صحيح dual_stride, صحيح inv_lookup)
{
    len >>= 1;

    إذا (len <= basis) {
        صحيح k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_بەرز = is_dual & dual_بەرز;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_بەرز*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_بەرز)*len + dual_بەرز*len;

        لكل (صحيح i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            إذا (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } وإلا {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            إذا (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        أرجع;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

صحيح ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, صحيح len, صحيح inv,
                                        FFTXCodeletOptions *opts,
                                        صحيح basis, صحيح dual_stride)
{
    basis >>= 1;
    إذا (len < basis)
        أرجع AVERROR(EINVAL);

    إذا (!(s->map = av_mallocz(len*حجم(*s->map))))
        أرجع AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    أرجع 0;
}

ساكن فراغ reset_ctx(AVTXContext *s, صحيح free_sub)
{
    إذا (!s)
        أرجع;

    إذا (s->sub)
        لكل (صحيح i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    إذا (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    إذا (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = عدم;
    memset(s->fn, 0, حجم(s->fn));
}

فراغ ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold فراغ av_tx_uninit(AVTXContext **ctx)
{
    إذا (!(*ctx))
        أرجع;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ساكن av_cold صحيح ff_tx_null_init(AVTXContext *s, ثابت FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   صحيح len, صحيح inv, ثابت فراغ *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    إذا (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        أرجع AVERROR(EINVAL);
    أرجع 0;
}

/* Null transform when the length is 1 */
ساكن فراغ ff_tx_null(AVTXContext *s, فراغ *_out, فراغ *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

ساكن ثابت FFTXCodelet ff_tx_null_def = {
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

ساكن ثابت FFTXCodelet * ثابت ff_tx_null_list[] = {
    &ff_tx_null_def,
    عدم,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ساكن ثابت FFTXCodelet * ثابت * ثابت codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#إذا HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#إذا ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
ساكن ثابت صحيح codelet_list_ژمارە = FF_ARRAY_ELEMS(codelet_list);

ساكن ثابت صحيح cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ساكن ثابت صحيح cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ساكن صحيح get_codelet_prio(ثابت FFTXCodelet *cd, صحيح cpu_flags, صحيح len)
{
    صحيح prio = cd->prio;
    صحيح max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        إذا ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    إذا ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    إذا ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    إذا ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    لكل (صحيح i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    إذا (max_factor)
        prio += 16*max_factor;

    أرجع prio;
}

تعريفنوع بنية FFTXLenDecomp {
    صحيح len;
    صحيح len2;
    صحيح prio;
    ثابت FFTXCodelet *cd;
} FFTXLenDecomp;

ساكن صحيح cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    أرجع FFDIFFSIGN(b->prio, a->prio);
}

صحيح ff_tx_decompose_length(صحيح dst[TX_MAX_DECOMPOSITIONS], تعداد AVTXType type,
                           صحيح len, صحيح inv)
{
    صحيح nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    صحيح codelet_list_idx = codelet_list_ژمارە;

    ثابت صحيح cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    طالما (codelet_list_idx--) {
        ثابت FFTXCodelet * ثابت * list = codelet_list[codelet_list_idx];
        ثابت FFTXCodelet *cd = عدم;

        طالما ((cd = *list++)) {
            صحيح fl = len;
            صحيح skip = 0, prio;
            صحيح factors_product = 1, factors_mod = 0;

            إذا (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                اذهب sort;

            /* Check if the type matches */
            إذا (cd->type != TX_TYPE_ANY && type != cd->type)
                استمر;

            /* Check direction for non-orthogonal codelets */
            إذا (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                استمر;

            /* Check if the CPU supports the required ISA */
            إذا (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                استمر;

            لكل (صحيح i = 0; i < TX_MAX_FACTORS; i++) {
                إذا (!cd->factors[i] || (fl == 1))
                    اكسر;

                إذا (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } وإلا إذا (!(fl % cd->factors[i])) {
                    factors_mod++;
                    إذا (cd->factors[i] == 2) {
                        صحيح b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } وإلا {
                        افعل {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } طالما (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            إذا ((factors_mod < cd->nb_factors) || (len == factors_product))
                استمر;

            إذا (av_gcd(factors_product, fl) != 1)
                استمر;

            /* Check if length is supported and factorization was successful */
            إذا ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                استمر;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            لكل (صحيح i = 0; i < nb_decomp; i++) {
                إذا (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    إذا (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    اكسر;
                }
            }

            /* Add decomposition if unique */
            إذا (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    إذا (!nb_decomp)
        أرجع AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    لكل (صحيح i = 0; i < nb_decomp; i++) {
        إذا (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        وإلا
            dst[i] = ld[i].len;
    }

    أرجع nb_decomp;
}

صحيح ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*حجم(*s->map));
    إذا (!s->map)
        أرجع AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    إذا (s->inv) /* Reversing the ACs flips the transform direction */
        لكل (صحيح i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    وإلا
        لكل (صحيح i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    أرجع 0;
}

#إذا !CONFIG_SMALL
ساكن فراغ print_flags(AVBPrint *bp, uint64_t f)
{
    صحيح prev = 0;
    ثابت حرف *sep = ", ";
    av_bprintf(bp, "flags: [");
    إذا ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    إذا ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    إذا ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    إذا ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    إذا ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    إذا ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    إذا ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    إذا ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    إذا ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    إذا ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    إذا ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ساكن فراغ print_type(AVBPrint *bp, تعداد AVTXType type)
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

ساكن فراغ print_cd_info(ثابت FFTXCodelet *cd, صحيح prio, صحيح len, صحيح print_prio,
                          صحيح log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    إذا (!len) {
        إذا (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        إذا (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        وإلا
            av_bprintf(&bp, "%i", cd->max_len);
    } وإلا {
        av_bprintf(&bp, "%i", len);
    }

    إذا (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        إذا (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        وإلا
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        لكل (صحيح i = 0; i < TX_MAX_FACTORS; i++) {
            إذا (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            إذا (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            وإلا إذا (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            وإلا
                اكسر;
        }

        av_bprintf(&bp, "], ");
    } وإلا {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    إذا (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(عدم, log_level, "%s\n", bp.str);
}

ساكن فراغ print_tx_structure(AVTXContext *s, صحيح depth)
{
    ثابت FFTXCodelet *cd = s->cd_self;

    لكل (صحيح i = 0; i <= depth; i++)
        av_log(عدم, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    لكل (صحيح i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

تعريفنوع بنية TXCodeletMatch {
    ثابت FFTXCodelet *cd;
    صحيح prio;
} TXCodeletMatch;

ساكن صحيح cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    أرجع FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ساكن مضمن صحيح check_cd_factors(ثابت FFTXCodelet *cd, صحيح len)
{
    صحيح matches = 0, any_flag = 0;

    لكل (صحيح i = 0; i < TX_MAX_FACTORS; i++) {
        صحيح factor = cd->factors[i];

        إذا (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            استمر;
        } وإلا إذا (len <= 1 || !factor) {
            اكسر;
        } وإلا إذا (factor == 2) { /* Fast path */
            صحيح bits_2 = ff_ctz(len);
            إذا (!bits_2)
                استمر; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } وإلا {
            صحيح res = len % factor;
            إذا (res)
                استمر; /* Factor not supported */

            طالما (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    أرجع (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold صحيح ff_tx_init_subtx(AVTXContext *s, تعداد AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             صحيح len, صحيح inv, ثابت فراغ *scale)
{
    صحيح ret = 0;
    AVTXContext *sub = عدم;
    TXCodeletMatch *cd_tmp, *cd_matches = عدم;
    unsigned صحيح cd_matches_size = 0;
    صحيح codelet_list_idx = codelet_list_ژمارە;
    صحيح nb_cd_matches = 0;
#إذا !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ثابت صحيح cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    إذا (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    إذا ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    إذا ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    طالما (codelet_list_idx--) {
        ثابت FFTXCodelet * ثابت * list = codelet_list[codelet_list_idx];
        ثابت FFTXCodelet *cd = عدم;

        طالما ((cd = *list++)) {
            /* Check if the type matches */
            إذا (cd->type != TX_TYPE_ANY && type != cd->type)
                استمر;

            /* Check direction for non-orthogonal codelets */
            إذا (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                استمر;

            /* Check if the requested flags match from both sides */
            إذا (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                استمر;

            /* Check if length is supported */
            إذا ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                استمر;

            /* Check if the CPU supports the required ISA */
            إذا (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                استمر;

            /* Check for factors */
            إذا (!check_cd_factors(cd, len))
                استمر;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     حجم(*cd_tmp) * (nb_cd_matches + 1));
            إذا (!cd_tmp) {
                av_free(cd_matches);
                أرجع AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#إذا !CONFIG_SMALL
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
    إذا (!nb_cd_matches)
        أرجع AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#إذا !CONFIG_SMALL
    av_log(عدم, AV_LOG_TRACE, "%s\n", bp.str);

    لكل (صحيح i = 0; i < nb_cd_matches; i++) {
        av_log(عدم, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    إذا (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*حجم(*sub));
        إذا (!sub) {
            ret = AVERROR(ENOMEM);
            اذهب end;
        }
    }

    /* Attempt to initialize each */
    لكل (صحيح i = 0; i < nb_cd_matches; i++) {
        ثابت FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        إذا (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        إذا (ret >= 0) {
            إذا (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*حجم(*sctx->map));
                إذا (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    اذهب end;
                }

                لكل (صحيح i = 0; i < len; i++)
                    sctx->map[i] = i;
            } وإلا إذا (opts && (opts->map_dir != sctx->map_dir)) {
                صحيح *tmp = av_malloc(len*حجم(*sctx->map));
                إذا (!tmp) {
                    ret = AVERROR(ENOMEM);
                    اذهب end;
                }

                memcpy(tmp, sctx->map, len*حجم(*sctx->map));

                لكل (صحيح i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            اذهب end;
        }

        s->fn[s->nb_sub] = عدم;
        s->cd[s->nb_sub] = عدم;

        reset_ctx(sctx, 0);
        إذا (ret == AVERROR(ENOMEM))
            اكسر;
    }

    إذا (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    أرجع ret;
}

av_cold صحيح av_tx_init(AVTXContext **ctx, av_tx_fn *tx, تعداد AVTXType type,
                       صحيح inv, صحيح len, ثابت فراغ *scale, uint64_t flags)
{
    صحيح ret;
    AVTXContext tmp = { 0 };
    ثابت مزدوج default_scale_d = 1.0;
    ثابت عائم  default_scale_f = 1.0f;

    إذا (!len || type >= AV_TX_NB || !ctx || !tx)
        أرجع AVERROR(EINVAL);

    إذا (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    إذا (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    إذا (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    وإلا إذا (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, عدم, len, inv, scale);
    إذا (ret < 0)
        أرجع ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#إذا !CONFIG_SMALL
    av_log(عدم, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    أرجع ret;
}
