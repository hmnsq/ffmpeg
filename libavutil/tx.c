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

#include "avassert.h"
#include "intmath.h"
#include "cpu.h"
#include "mem.h"
#include "qsort.h"
#include "bprint.h"

#include "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
static av_always_inline 整数 mulinv(整数 n, 整数 m)
{
    n = n % m;
    ために (整数 x = 1; x < m; x++)
        もし (((n * x) % m) == 1)
            戻る x;
    av_assert0(0); /* Never reached */
    戻る 0;
}

整数 ff_tx_gen_pfa_input_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            整数 d1, 整数 d2)
{
    const 整数 sl = d1*d2;

    s->map = av_malloc(s->len*sizeof(*s->map));
    もし (!s->map)
        戻る AVERROR(ENOMEM);

    ために (整数 k = 0; k < s->len; k += sl) {
        もし (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ために (整数 m = 0; m < d2; m++)
                ために (整数 n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } 否则 {
            ために (整数 m = 0; m < d2; m++)
                ために (整数 n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        もし (s->inv)
            ために (整数 w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(整数, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    戻る 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
整数 ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               整数 inv, 整数 n, 整数 m)
{
    整数 *in_map, *out_map;
    const 整数 len = n*m;    /* Will not be equal to s->len for MDCTs */
    整数 m_inv, n_inv;

    /* Make sure the numbers are coprime */
    もし (av_gcd(n, m) != 1)
        戻る AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    もし (!(s->map = av_malloc(2*len*sizeof(*s->map))))
        戻る AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    もし (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ために (整数 j = 0; j < m; j++) {
            ために (整数 i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } 否则 {
        ために (整数 j = 0; j < m; j++) {
            ために (整数 i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    もし (inv) {
        ために (整数 i = 0; i < m; i++) {
            整数 *in = &in_map[i*n + 1]; /* Skip the DC */
            ために (整数 j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(整数, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    戻る 0;
}

static inline 整数 split_radix_permutation(整数 i, 整数 len, 整数 inv)
{
    len >>= 1;
    もし (len <= 1)
        戻る i & 1;
    もし (!(i & len))
        戻る split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    戻る split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

整数 ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    整数 len = s->len;

    もし (!(s->map = av_malloc(len*sizeof(*s->map))))
        戻る AVERROR(ENOMEM);

    もし (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ために (整数 i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } 否则 {
        ために (整数 i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    戻る 0;
}

整数 ff_tx_gen_inplace_map(AVTXContext *s, 整数 len)
{
    整数 *src_map, out_map_idx = 0;

    もし (!s->sub || !s->sub->map)
        戻る AVERROR(EINVAL);

    もし (!(s->map = av_mallocz(len*sizeof(*s->map))))
        戻る AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ために (整数 src = 1; src < s->len; src++) {
        整数 dst = src_map[src];
        整数 found = 0;

        もし (dst <= src)
            continue;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        do {
            ために (整数 j = 0; j < out_map_idx; j++) {
                もし (dst == s->map[j]) {
                    found = 1;
                    break;
                }
            }
            dst = src_map[dst];
        } ながら (dst != src && !found);

        もし (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    戻る 0;
}

static void parity_revtab_generator(整数 *revtab, 整数 n, 整数 inv, 整数 offset,
                                    整数 is_dual, 整数 dual_high, 整数 len,
                                    整数 basis, 整数 dual_stride, 整数 inv_lookup)
{
    len >>= 1;

    もし (len <= basis) {
        整数 k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_high = is_dual & dual_high;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_high*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_high)*len + dual_high*len;

        ために (整数 i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            もし (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } 否则 {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            もし (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        戻る;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

整数 ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, 整数 len, 整数 inv,
                                        FFTXCodeletOptions *opts,
                                        整数 basis, 整数 dual_stride)
{
    basis >>= 1;
    もし (len < basis)
        戻る AVERROR(EINVAL);

    もし (!(s->map = av_mallocz(len*sizeof(*s->map))))
        戻る AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    戻る 0;
}

static void reset_ctx(AVTXContext *s, 整数 free_sub)
{
    もし (!s)
        戻る;

    もし (s->sub)
        ために (整数 i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    もし (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    もし (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = NULL;
    memset(s->fn, 0, sizeof(s->fn));
}

void ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold void av_tx_uninit(AVTXContext **ctx)
{
    もし (!(*ctx))
        戻る;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

static av_cold 整数 ff_tx_null_init(AVTXContext *s, const FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   整数 len, 整数 inv, const void *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    もし (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        戻る AVERROR(EINVAL);
    戻る 0;
}

/* Null transform when the length is 1 */
static void ff_tx_null(AVTXContext *s, void *_out, void *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

static const FFTXCodelet ff_tx_null_def = {
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

static const FFTXCodelet * const ff_tx_null_list[] = {
    &ff_tx_null_def,
    NULL,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
static const FFTXCodelet * const * const codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#もし HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#もし ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
static const 整数 codelet_list_num = FF_ARRAY_ELEMS(codelet_list);

static const 整数 cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

static const 整数 cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

static 整数 get_codelet_prio(const FFTXCodelet *cd, 整数 cpu_flags, 整数 len)
{
    整数 prio = cd->prio;
    整数 max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ために (整数 i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        もし ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    もし ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    もし ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    もし ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ために (整数 i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    もし (max_factor)
        prio += 16*max_factor;

    戻る prio;
}

typedef struct FFTXLenDecomp {
    整数 len;
    整数 len2;
    整数 prio;
    const FFTXCodelet *cd;
} FFTXLenDecomp;

static 整数 cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    戻る FFDIFFSIGN(b->prio, a->prio);
}

整数 ff_tx_decompose_length(整数 dst[TX_MAX_DECOMPOSITIONS], enum AVTXType type,
                           整数 len, 整数 inv)
{
    整数 nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    整数 codelet_list_idx = codelet_list_num;

    const 整数 cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ながら (codelet_list_idx--) {
        const FFTXCodelet * const * list = codelet_list[codelet_list_idx];
        const FFTXCodelet *cd = NULL;

        ながら ((cd = *list++)) {
            整数 fl = len;
            整数 skip = 0, prio;
            整数 factors_product = 1, factors_mod = 0;

            もし (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                goto sort;

            /* Check if the type matches */
            もし (cd->type != TX_TYPE_ANY && type != cd->type)
                continue;

            /* Check direction for non-orthogonal codelets */
            もし (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                continue;

            /* Check if the CPU supports the required ISA */
            もし (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                continue;

            ために (整数 i = 0; i < TX_MAX_FACTORS; i++) {
                もし (!cd->factors[i] || (fl == 1))
                    break;

                もし (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } 否则 もし (!(fl % cd->factors[i])) {
                    factors_mod++;
                    もし (cd->factors[i] == 2) {
                        整数 b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } 否则 {
                        do {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } ながら (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            もし ((factors_mod < cd->nb_factors) || (len == factors_product))
                continue;

            もし (av_gcd(factors_product, fl) != 1)
                continue;

            /* Check if length is supported and factorization was successful */
            もし ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                continue;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            ために (整数 i = 0; i < nb_decomp; i++) {
                もし (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    もし (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    break;
                }
            }

            /* Add decomposition if unique */
            もし (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    もし (!nb_decomp)
        戻る AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ために (整数 i = 0; i < nb_decomp; i++) {
        もし (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        否则
            dst[i] = ld[i].len;
    }

    戻る nb_decomp;
}

整数 ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*sizeof(*s->map));
    もし (!s->map)
        戻る AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    もし (s->inv) /* Reversing the ACs flips the transform direction */
        ために (整数 i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    否则
        ために (整数 i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    戻る 0;
}

#もし !CONFIG_SMALL
static void print_flags(AVBPrint *bp, uint64_t f)
{
    整数 prev = 0;
    const char *sep = ", ";
    av_bprintf(bp, "flags: [");
    もし ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    もし ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    もし ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    もし ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    もし ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    もし ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    もし ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    もし ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    もし ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    もし ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    もし ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

static void print_type(AVBPrint *bp, enum AVTXType type)
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

static void print_cd_info(const FFTXCodelet *cd, 整数 prio, 整数 len, 整数 print_prio,
                          整数 log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    もし (!len) {
        もし (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        もし (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        否则
            av_bprintf(&bp, "%i", cd->max_len);
    } 否则 {
        av_bprintf(&bp, "%i", len);
    }

    もし (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        もし (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        否则
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ために (整数 i = 0; i < TX_MAX_FACTORS; i++) {
            もし (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            もし (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            否则 もし (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            否则
                break;
        }

        av_bprintf(&bp, "], ");
    } 否则 {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    もし (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(NULL, log_level, "%s\n", bp.str);
}

static void print_tx_structure(AVTXContext *s, 整数 depth)
{
    const FFTXCodelet *cd = s->cd_self;

    ために (整数 i = 0; i <= depth; i++)
        av_log(NULL, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ために (整数 i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

typedef struct TXCodeletMatch {
    const FFTXCodelet *cd;
    整数 prio;
} TXCodeletMatch;

static 整数 cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    戻る FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
static inline 整数 check_cd_factors(const FFTXCodelet *cd, 整数 len)
{
    整数 matches = 0, any_flag = 0;

    ために (整数 i = 0; i < TX_MAX_FACTORS; i++) {
        整数 factor = cd->factors[i];

        もし (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            continue;
        } 否则 もし (len <= 1 || !factor) {
            break;
        } 否则 もし (factor == 2) { /* Fast path */
            整数 bits_2 = ff_ctz(len);
            もし (!bits_2)
                continue; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } 否则 {
            整数 res = len % factor;
            もし (res)
                continue; /* Factor not supported */

            ながら (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    戻る (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold 整数 ff_tx_init_subtx(AVTXContext *s, enum AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             整数 len, 整数 inv, const void *scale)
{
    整数 ret = 0;
    AVTXContext *sub = NULL;
    TXCodeletMatch *cd_tmp, *cd_matches = NULL;
    unsigned 整数 cd_matches_size = 0;
    整数 codelet_list_idx = codelet_list_num;
    整数 nb_cd_matches = 0;
#もし !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    const 整数 cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    もし (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    もし ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    もし ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ながら (codelet_list_idx--) {
        const FFTXCodelet * const * list = codelet_list[codelet_list_idx];
        const FFTXCodelet *cd = NULL;

        ながら ((cd = *list++)) {
            /* Check if the type matches */
            もし (cd->type != TX_TYPE_ANY && type != cd->type)
                continue;

            /* Check direction for non-orthogonal codelets */
            もし (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                continue;

            /* Check if the requested flags match from both sides */
            もし (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                continue;

            /* Check if length is supported */
            もし ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                continue;

            /* Check if the CPU supports the required ISA */
            もし (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                continue;

            /* Check for factors */
            もし (!check_cd_factors(cd, len))
                continue;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     sizeof(*cd_tmp) * (nb_cd_matches + 1));
            もし (!cd_tmp) {
                av_free(cd_matches);
                戻る AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#もし !CONFIG_SMALL
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
    もし (!nb_cd_matches)
        戻る AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#もし !CONFIG_SMALL
    av_log(NULL, AV_LOG_TRACE, "%s\n", bp.str);

    ために (整数 i = 0; i < nb_cd_matches; i++) {
        av_log(NULL, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    もし (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*sizeof(*sub));
        もし (!sub) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
    }

    /* Attempt to initialize each */
    ために (整数 i = 0; i < nb_cd_matches; i++) {
        const FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        もし (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        もし (ret >= 0) {
            もし (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*sizeof(*sctx->map));
                もし (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    goto end;
                }

                ために (整数 i = 0; i < len; i++)
                    sctx->map[i] = i;
            } 否则 もし (opts && (opts->map_dir != sctx->map_dir)) {
                整数 *tmp = av_malloc(len*sizeof(*sctx->map));
                もし (!tmp) {
                    ret = AVERROR(ENOMEM);
                    goto end;
                }

                memcpy(tmp, sctx->map, len*sizeof(*sctx->map));

                ために (整数 i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            goto end;
        }

        s->fn[s->nb_sub] = NULL;
        s->cd[s->nb_sub] = NULL;

        reset_ctx(sctx, 0);
        もし (ret == AVERROR(ENOMEM))
            break;
    }

    もし (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    戻る ret;
}

av_cold 整数 av_tx_init(AVTXContext **ctx, av_tx_fn *tx, enum AVTXType type,
                       整数 inv, 整数 len, const void *scale, uint64_t flags)
{
    整数 ret;
    AVTXContext tmp = { 0 };
    const double default_scale_d = 1.0;
    const float  default_scale_f = 1.0f;

    もし (!len || type >= AV_TX_NB || !ctx || !tx)
        戻る AVERROR(EINVAL);

    もし (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    もし (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    もし (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    否则 もし (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, NULL, len, inv, scale);
    もし (ret < 0)
        戻る ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#もし !CONFIG_SMALL
    av_log(NULL, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    戻る ret;
}
