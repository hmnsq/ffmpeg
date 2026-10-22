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

#شامل "avassert.h"
#شامل "intmath.h"
#شامل "cpu.h"
#شامل "mem.h"
#شامل "qsort.h"
#شامل "bprint.h"

#شامل "tx_priv.h"

#تعریف_کرو TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ساکن av_always_inline صحیح mulinv(صحیح n, صحیح m)
{
    n = n % m;
    برائے (صحیح x = 1; x < m; x++)
        اگر (((n * x) % m) == 1)
            واپس x;
    av_assert0(0); /* Never reached */
    واپس 0;
}

صحیح ff_tx_gen_pfa_داخلہ_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            صحیح d1, صحیح d2)
{
    ثابت صحیح sl = d1*d2;

    s->map = av_malloc(s->len*حجم(*s->map));
    اگر (!s->map)
        واپس AVERROR(ENOMEM);

    برائے (صحیح k = 0; k < s->len; k += sl) {
        اگر (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            برائے (صحیح m = 0; m < d2; m++)
                برائے (صحیح n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ورنہ {
            برائے (صحیح m = 0; m < d2; m++)
                برائے (صحیح n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        اگر (s->inv)
            برائے (صحیح w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(صحیح, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    واپس 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
صحیح ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               صحیح inv, صحیح n, صحیح m)
{
    صحیح *اندر_map, *برآمد_map;
    ثابت صحیح len = n*m;    /* Will not be equal to s->len for MDCTs */
    صحیح m_inv, n_inv;

    /* Make sure the numbers are coprime */
    اگر (av_عاد_اعظم(n, m) != 1)
        واپس AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    اگر (!(s->map = av_malloc(2*len*حجم(*s->map))))
        واپس AVERROR(ENOMEM);

    اندر_map  = s->map;
    برآمد_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    اگر (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        برائے (صحیح j = 0; j < m; j++) {
            برائے (صحیح i = 0; i < n; i++) {
                اندر_map[(i*m + j*n) % len] = j*n + i;
                برآمد_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ورنہ {
        برائے (صحیح j = 0; j < m; j++) {
            برائے (صحیح i = 0; i < n; i++) {
                اندر_map[j*n + i] = (i*m + j*n) % len;
                برآمد_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    اگر (inv) {
        برائے (صحیح i = 0; i < m; i++) {
            صحیح *اندر = &اندر_map[i*n + 1]; /* Skip the DC */
            برائے (صحیح j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(صحیح, اندر[j], اندر[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    واپس 0;
}

ساکن اندرونی صحیح بانٹو_radix_permutation(صحیح i, صحیح len, صحیح inv)
{
    len >>= 1;
    اگر (len <= 1)
        واپس i & 1;
    اگر (!(i & len))
        واپس بانٹو_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    واپس بانٹو_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

صحیح ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    صحیح len = s->len;

    اگر (!(s->map = av_malloc(len*حجم(*s->map))))
        واپس AVERROR(ENOMEM);

    اگر (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        برائے (صحیح i = 0; i < s->len; i++)
            s->map[-بانٹو_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ورنہ {
        برائے (صحیح i = 0; i < s->len; i++)
            s->map[i] = -بانٹو_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    واپس 0;
}

صحیح ff_tx_gen_inplace_map(AVTXContext *s, صحیح len)
{
    صحیح *src_map, برآمد_map_idx = 0;

    اگر (!s->sub || !s->sub->map)
        واپس AVERROR(EINVAL);

    اگر (!(s->map = av_mallocz(len*حجم(*s->map))))
        واپس AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    برائے (صحیح src = 1; src < s->len; src++) {
        صحیح dst = src_map[src];
        صحیح ملا = 0;

        اگر (dst <= src)
            جاری;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        کرو {
            برائے (صحیح j = 0; j < برآمد_map_idx; j++) {
                اگر (dst == s->map[j]) {
                    ملا = 1;
                    توڑو;
                }
            }
            dst = src_map[dst];
        } جب (dst != src && !ملا);

        اگر (!ملا)
            s->map[برآمد_map_idx++] = src;
    }

    s->map[برآمد_map_idx++] = 0;

    واپس 0;
}

ساکن خالی parity_revtab_generator(صحیح *revtab, صحیح n, صحیح inv, صحیح انحراف,
                                    صحیح is_dual, صحیح dual_بلند, صحیح len,
                                    صحیح basis, صحیح dual_stride, صحیح inv_lookup)
{
    len >>= 1;

    اگر (len <= basis) {
        صحیح k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_بلند = is_dual & dual_بلند;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = انحراف + dual_بلند*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_بلند)*len + dual_بلند*len;

        برائے (صحیح i = 0; i < len; i++) {
            k1 = -بانٹو_radix_permutation(انحراف + i*2 + 0, n, inv) & (n - 1);
            k2 = -بانٹو_radix_permutation(انحراف + i*2 + 1, n, inv) & (n - 1);
            اگر (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ورنہ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            اگر (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        واپس;
    }

    parity_revtab_generator(revtab, n, inv, انحراف,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, انحراف + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, انحراف + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

صحیح ff_tx_gen_بانٹو_radix_parity_revtab(AVTXContext *s, صحیح len, صحیح inv,
                                        FFTXCodeletOptions *opts,
                                        صحیح basis, صحیح dual_stride)
{
    basis >>= 1;
    اگر (len < basis)
        واپس AVERROR(EINVAL);

    اگر (!(s->map = av_mallocz(len*حجم(*s->map))))
        واپس AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    واپس 0;
}

ساکن خالی reset_ctx(AVTXContext *s, صحیح free_sub)
{
    اگر (!s)
        واپس;

    اگر (s->sub)
        برائے (صحیح i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    اگر (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    اگر (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->قوت_نما);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = تہی;
    memset(s->fn, 0, حجم(s->fn));
}

خالی ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold خالی av_tx_uninit(AVTXContext **ctx)
{
    اگر (!(*ctx))
        واپس;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ساکن av_cold صحیح ff_tx_null_init(AVTXContext *s, ثابت FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   صحیح len, صحیح inv, ثابت خالی *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    اگر (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        واپس AVERROR(EINVAL);
    واپس 0;
}

/* Null transform when the length is 1 */
ساکن خالی ff_tx_null(AVTXContext *s, خالی *برآمد_3, خالی *اندر_3, ptrdiff_t stride)
{
    حافظہ_نقل(برآمد_3, اندر_3, stride);
}

ساکن ثابت FFTXCodelet ff_tx_null_def = {
    .name       = NULL_IF_CONFIG_SMALL("null"),
    .function   = ff_tx_null,
    .type       = TX_TYPE_ANY,
    .flags      = AV_TX_UNALIGNED | FF_TX_ALIGNED |
                  FF_TX_برآمد_کا_رکھو | AV_TX_INPLACE,
    .factors[0] = TX_ضربی_عدد_ANY,
    .min_len    = 1,
    .max_len    = 1,
    .init       = ff_tx_null_init,
    .cpu_flags  = FF_TX_CPU_FLAGS_ALL,
    .prio       = FF_TX_PRIO_MAX,
};

ساکن ثابت FFTXCodelet * ثابت ff_tx_null_list[] = {
    &ff_tx_null_def,
    تہی,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ساکن ثابت FFTXCodelet * ثابت * ثابت codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#اگر HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#اگر_ختم
#اگر ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#اگر_ختم
};
ساکن ثابت صحیح codelet_list_عدد = FF_ARRAY_ELEMS(codelet_list);

ساکن ثابت صحیح cpu_slow_نقاب = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ساکن ثابت صحیح cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ساکن صحیح get_codelet_prio(ثابت FFTXCodelet *cd, صحیح cpu_flags, صحیح len)
{
    صحیح prio = cd->prio;
    صحیح max_ضربی_عدد = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        اگر ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    اگر ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    اگر ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    اگر ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    برائے (صحیح i = 0; i < TX_MAX_SUB; i++)
        max_ضربی_عدد = FFMAX(cd->factors[i], max_ضربی_عدد);
    اگر (max_ضربی_عدد)
        prio += 16*max_ضربی_عدد;

    واپس prio;
}

قسمتعریف ساخت FFTXLenDecomp {
    صحیح len;
    صحیح len2;
    صحیح prio;
    ثابت FFTXCodelet *cd;
} FFTXLenDecomp;

ساکن صحیح cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    واپس FFDIFFSIGN(b->prio, a->prio);
}

صحیح ff_tx_decompose_لمبائی(صحیح dst[TX_MAX_DECOMPOSITIONS], شمار AVTXType type,
                           صحیح len, صحیح inv)
{
    صحیح nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    صحیح codelet_list_idx = codelet_list_عدد;

    ثابت صحیح cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    جب (codelet_list_idx--) {
        ثابت FFTXCodelet * ثابت * list = codelet_list[codelet_list_idx];
        ثابت FFTXCodelet *cd = تہی;

        جب ((cd = *list++)) {
            صحیح fl = len;
            صحیح skip = 0, prio;
            صحیح factors_حاصل_ضرب = 1, factors_mod = 0;

            اگر (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                جاؤ ترتیب_دو;

            /* Check if the type matches */
            اگر (cd->type != TX_TYPE_ANY && type != cd->type)
                جاری;

            /* Check direction for non-orthogonal codelets */
            اگر (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_بھرا_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_مقصد_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_مقصد_IMAGINARY)) && inv))
                جاری;

            /* Check if the CPU supports the required ISA */
            اگر (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_نقاب)))
                جاری;

            برائے (صحیح i = 0; i < TX_MAX_FACTORS; i++) {
                اگر (!cd->factors[i] || (fl == 1))
                    توڑو;

                اگر (cd->factors[i] == TX_ضربی_عدد_ANY) {
                    factors_mod++;
                    factors_حاصل_ضرب *= fl;
                } ورنہ اگر (!(fl % cd->factors[i])) {
                    factors_mod++;
                    اگر (cd->factors[i] == 2) {
                        صحیح b = ff_ctz(fl);
                        fl >>= b;
                        factors_حاصل_ضرب <<= b;
                    } ورنہ {
                        کرو {
                            fl /= cd->factors[i];
                            factors_حاصل_ضرب *= cd->factors[i];
                        } جب (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            اگر ((factors_mod < cd->nb_factors) || (len == factors_حاصل_ضرب))
                جاری;

            اگر (av_عاد_اعظم(factors_حاصل_ضرب, fl) != 1)
                جاری;

            /* Check if length is supported and factorization was successful */
            اگر ((factors_حاصل_ضرب < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_حاصل_ضرب > cd->max_len)))
                جاری;

            prio = get_codelet_prio(cd, cpu_flags, factors_حاصل_ضرب) * factors_حاصل_ضرب;

            /* Check for duplicates */
            برائے (صحیح i = 0; i < nb_decomp; i++) {
                اگر (factors_حاصل_ضرب == ld[i].len) {
                    /* Update priority if new one is higher */
                    اگر (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    توڑو;
                }
            }

            /* Add decomposition if unique */
            اگر (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_حاصل_ضرب;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    اگر (!nb_decomp)
        واپس AVERROR(EINVAL);

ترتیب_دو:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    برائے (صحیح i = 0; i < nb_decomp; i++) {
        اگر (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ورنہ
            dst[i] = ld[i].len;
    }

    واپس nb_decomp;
}

صحیح ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*حجم(*s->map));
    اگر (!s->map)
        واپس AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    اگر (s->inv) /* Reversing the ACs flips the transform direction */
        برائے (صحیح i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ورنہ
        برائے (صحیح i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    واپس 0;
}

#اگر !CONFIG_SMALL
ساکن خالی print_flags(AVBPrint *bp, uint64_t f)
{
    صحیح پچھلا = 0;
    ثابت حرف *sep = ", ";
    av_bprintf(bp, "flags: [");
    اگر ((f & FF_TX_ALIGNED) && ++پچھلا)
        av_bprintf(bp, "aligned");
    اگر ((f & AV_TX_UNALIGNED) && ++پچھلا)
        av_bprintf(bp, "%sunaligned", پچھلا > 1 ? sep : "");
    اگر ((f & AV_TX_INPLACE) && ++پچھلا)
        av_bprintf(bp, "%sinplace", پچھلا > 1 ? sep : "");
    اگر ((f & FF_TX_برآمد_کا_رکھو) && ++پچھلا)
        av_bprintf(bp, "%sout_of_place", پچھلا > 1 ? sep : "");
    اگر ((f & FF_TX_FORWARD_ONLY) && ++پچھلا)
        av_bprintf(bp, "%sfwd_only", پچھلا > 1 ? sep : "");
    اگر ((f & FF_TX_INVERSE_ONLY) && ++پچھلا)
        av_bprintf(bp, "%sinv_only", پچھلا > 1 ? sep : "");
    اگر ((f & FF_TX_PRESHUFFLE) && ++پچھلا)
        av_bprintf(bp, "%spreshuf", پچھلا > 1 ? sep : "");
    اگر ((f & AV_TX_بھرا_IMDCT) && ++پچھلا)
        av_bprintf(bp, "%simdct_full", پچھلا > 1 ? sep : "");
    اگر ((f & AV_TX_REAL_مقصد_REAL) && ++پچھلا)
        av_bprintf(bp, "%sreal_to_real", پچھلا > 1 ? sep : "");
    اگر ((f & AV_TX_REAL_مقصد_IMAGINARY) && ++پچھلا)
        av_bprintf(bp, "%sreal_to_imaginary", پچھلا > 1 ? sep : "");
    اگر ((f & FF_TX_ASM_CALL) && ++پچھلا)
        av_bprintf(bp, "%sasm_call", پچھلا > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ساکن خالی print_type(AVBPrint *bp, شمار AVTXType type)
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

ساکن خالی print_cd_info(ثابت FFTXCodelet *cd, صحیح prio, صحیح len, صحیح print_prio,
                          صحیح log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_سائز_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    اگر (!len) {
        اگر (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        اگر (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ورنہ
            av_bprintf(&bp, "%i", cd->max_len);
    } ورنہ {
        av_bprintf(&bp, "%i", len);
    }

    اگر (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        اگر (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ورنہ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        برائے (صحیح i = 0; i < TX_MAX_FACTORS; i++) {
            اگر (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            اگر (cd->factors[i] == TX_ضربی_عدد_ANY)
                av_bprintf(&bp, "any");
            ورنہ اگر (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ورنہ
                توڑو;
        }

        av_bprintf(&bp, "], ");
    } ورنہ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    اگر (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(تہی, log_level, "%s\n", bp.str);
}

ساکن خالی print_tx_structure(AVTXContext *s, صحیح گہرائی)
{
    ثابت FFTXCodelet *cd = s->cd_self;

    برائے (صحیح i = 0; i <= گہرائی; i++)
        av_log(تہی, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    برائے (صحیح i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], گہرائی + 1);
}
#اگر_ختم /* CONFIG_SMALL */

قسمتعریف ساخت TXCodelet_مطابقت {
    ثابت FFTXCodelet *cd;
    صحیح prio;
} TXCodelet_مطابقت;

ساکن صحیح cmp_matches(TXCodelet_مطابقت *a, TXCodelet_مطابقت *b)
{
    واپس FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ساکن اندرونی صحیح check_cd_factors(ثابت FFTXCodelet *cd, صحیح len)
{
    صحیح matches = 0, any_flag = 0;

    برائے (صحیح i = 0; i < TX_MAX_FACTORS; i++) {
        صحیح ضربی_عدد = cd->factors[i];

        اگر (ضربی_عدد == TX_ضربی_عدد_ANY) {
            any_flag = 1;
            matches++;
            جاری;
        } ورنہ اگر (len <= 1 || !ضربی_عدد) {
            توڑو;
        } ورنہ اگر (ضربی_عدد == 2) { /* Fast path */
            صحیح بٹ_2 = ff_ctz(len);
            اگر (!بٹ_2)
                جاری; /* Factor not supported */

            len >>= بٹ_2;
            matches++;
        } ورنہ {
            صحیح res = len % ضربی_عدد;
            اگر (res)
                جاری; /* Factor not supported */

            جب (!res) {
                len /= ضربی_عدد;
                res = len % ضربی_عدد;
            }
            matches++;
        }
    }

    واپس (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold صحیح ff_tx_init_subtx(AVTXContext *s, شمار AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             صحیح len, صحیح inv, ثابت خالی *scale)
{
    صحیح ret = 0;
    AVTXContext *sub = تہی;
    TXCodelet_مطابقت *cd_tmp, *cd_matches = تہی;
    غیرعلامتی صحیح cd_matches_سائز = 0;
    صحیح codelet_list_idx = codelet_list_عدد;
    صحیح nb_cd_matches = 0;
#اگر !CONFIG_SMALL
    AVBPrint bp;
#اگر_ختم

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ثابت صحیح cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_نقاب = AV_TX_بھرا_IMDCT |
                            AV_TX_REAL_مقصد_REAL |
                            AV_TX_REAL_مقصد_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    اگر (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    اگر ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_برآمد_کا_رکھو))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_برآمد_کا_رکھو);
    اگر ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    جب (codelet_list_idx--) {
        ثابت FFTXCodelet * ثابت * list = codelet_list[codelet_list_idx];
        ثابت FFTXCodelet *cd = تہی;

        جب ((cd = *list++)) {
            /* Check if the type matches */
            اگر (cd->type != TX_TYPE_ANY && type != cd->type)
                جاری;

            /* Check direction for non-orthogonal codelets */
            اگر (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_بھرا_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_مقصد_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_مقصد_IMAGINARY)) && inv))
                جاری;

            /* Check if the requested flags match from both sides */
            اگر (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_نقاب & cd->flags) != (req_flags & inv_req_نقاب)))
                جاری;

            /* Check if length is supported */
            اگر ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                جاری;

            /* Check if the CPU supports the required ISA */
            اگر (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_نقاب)))
                جاری;

            /* Check for factors */
            اگر (!check_cd_factors(cd, len))
                جاری;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_سائز,
                                     حجم(*cd_tmp) * (nb_cd_matches + 1));
            اگر (!cd_tmp) {
                av_free(cd_matches);
                واپس AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#اگر !CONFIG_SMALL
    /* Print debugging info */
    av_bprint_init(&bp, 0, AV_BPRINT_سائز_AUTOMATIC);
    av_bprintf(&bp, "For transform of length %i, %s, ", len,
               inv ? "inverse" : "forward");
    print_type(&bp, type);
    av_bprintf(&bp, ", ");
    print_flags(&bp, flags);
    av_bprintf(&bp, ", found %i matches%s", nb_cd_matches,
               nb_cd_matches ? ":" : ".");
#اگر_ختم

    /* No matches found */
    اگر (!nb_cd_matches)
        واپس AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodelet_مطابقت, cmp_matches);

#اگر !CONFIG_SMALL
    av_log(تہی, AV_LOG_TRACE, "%s\n", bp.str);

    برائے (صحیح i = 0; i < nb_cd_matches; i++) {
        av_log(تہی, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#اگر_ختم

    اگر (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*حجم(*sub));
        اگر (!sub) {
            ret = AVERROR(ENOMEM);
            جاؤ انتہا;
        }
    }

    /* Attempt to initialize each */
    برائے (صحیح i = 0; i < nb_cd_matches; i++) {
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
        اگر (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        اگر (ret >= 0) {
            اگر (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*حجم(*sctx->map));
                اگر (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    جاؤ انتہا;
                }

                برائے (صحیح i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ورنہ اگر (opts && (opts->map_dir != sctx->map_dir)) {
                صحیح *tmp = av_malloc(len*حجم(*sctx->map));
                اگر (!tmp) {
                    ret = AVERROR(ENOMEM);
                    جاؤ انتہا;
                }

                حافظہ_نقل(tmp, sctx->map, len*حجم(*sctx->map));

                برائے (صحیح i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            جاؤ انتہا;
        }

        s->fn[s->nb_sub] = تہی;
        s->cd[s->nb_sub] = تہی;

        reset_ctx(sctx, 0);
        اگر (ret == AVERROR(ENOMEM))
            توڑو;
    }

    اگر (!s->nb_sub)
        av_freep(&s->sub);

انتہا:
    av_free(cd_matches);
    واپس ret;
}

av_cold صحیح av_tx_init(AVTXContext **ctx, av_tx_fn *tx, شمار AVTXType type,
                       صحیح inv, صحیح len, ثابت خالی *scale, uint64_t flags)
{
    صحیح ret;
    AVTXContext tmp = { 0 };
    ثابت دوہرا default_scale_d = 1.0;
    ثابت اعشاری  default_scale_f = 1.0f;

    اگر (!len || type >= AV_TX_NB || !ctx || !tx)
        واپس AVERROR(EINVAL);

    اگر (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    اگر (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_برآمد_کا_رکھو;

    اگر (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ورنہ اگر (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, تہی, len, inv, scale);
    اگر (ret < 0)
        واپس ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#اگر !CONFIG_SMALL
    av_log(تہی, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#اگر_ختم

    واپس ret;
}
