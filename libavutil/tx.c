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
static av_always_inline ຈຳນວນເຕັມ mulinv(ຈຳນວນເຕັມ n, ຈຳນວນເຕັມ m)
{
    n = n % m;
    ສຳລັບ (ຈຳນວນເຕັມ x = 1; x < m; x++)
        ຖ້າ (((n * x) % m) == 1)
            ສົ່ງຄືນ x;
    av_assert0(0); /* Never reached */
    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ ff_tx_gen_pfa_input_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            ຈຳນວນເຕັມ d1, ຈຳນວນເຕັມ d2)
{
    const ຈຳນວນເຕັມ sl = d1*d2;

    s->map = av_malloc(s->len*parimaa_na(*s->map));
    ຖ້າ (!s->map)
        ສົ່ງຄືນ AVERROR(ENOMEM);

    ສຳລັບ (ຈຳນວນເຕັມ k = 0; k < s->len; k += sl) {
        ຖ້າ (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ສຳລັບ (ຈຳນວນເຕັມ m = 0; m < d2; m++)
                ສຳລັບ (ຈຳນວນເຕັມ n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ບໍ່ດັ່ງນັ້ນ {
            ສຳລັບ (ຈຳນວນເຕັມ m = 0; m < d2; m++)
                ສຳລັບ (ຈຳນວນເຕັມ n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ຖ້າ (s->inv)
            ສຳລັບ (ຈຳນວນເຕັມ w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(ຈຳນວນເຕັມ, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ສົ່ງຄືນ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
ຈຳນວນເຕັມ ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               ຈຳນວນເຕັມ inv, ຈຳນວນເຕັມ n, ຈຳນວນເຕັມ m)
{
    ຈຳນວນເຕັມ *in_map, *out_map;
    const ຈຳນວນເຕັມ len = n*m;    /* Will not be equal to s->len for MDCTs */
    ຈຳນວນເຕັມ m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ຖ້າ (av_gcd(n, m) != 1)
        ສົ່ງຄືນ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ຖ້າ (!(s->map = av_malloc(2*len*parimaa_na(*s->map))))
        ສົ່ງຄືນ AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ຖ້າ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ສຳລັບ (ຈຳນວນເຕັມ j = 0; j < m; j++) {
            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ບໍ່ດັ່ງນັ້ນ {
        ສຳລັບ (ຈຳນວນເຕັມ j = 0; j < m; j++) {
            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ຖ້າ (inv) {
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < m; i++) {
            ຈຳນວນເຕັມ *in = &in_map[i*n + 1]; /* Skip the DC */
            ສຳລັບ (ຈຳນວນເຕັມ j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(ຈຳນວນເຕັມ, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ສົ່ງຄືນ 0;
}

static anta_hstha ຈຳນວນເຕັມ split_radix_permutation(ຈຳນວນເຕັມ i, ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ inv)
{
    len >>= 1;
    ຖ້າ (len <= 1)
        ສົ່ງຄືນ i & 1;
    ຖ້າ (!(i & len))
        ສົ່ງຄືນ split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ສົ່ງຄືນ split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

ຈຳນວນເຕັມ ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    ຈຳນວນເຕັມ len = s->len;

    ຖ້າ (!(s->map = av_malloc(len*parimaa_na(*s->map))))
        ສົ່ງຄືນ AVERROR(ENOMEM);

    ຖ້າ (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ບໍ່ດັ່ງນັ້ນ {
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ ff_tx_gen_inplace_map(AVTXContext *s, ຈຳນວນເຕັມ len)
{
    ຈຳນວນເຕັມ *src_map, out_map_idx = 0;

    ຖ້າ (!s->sub || !s->sub->map)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (!(s->map = av_mallocz(len*parimaa_na(*s->map))))
        ສົ່ງຄືນ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ສຳລັບ (ຈຳນວນເຕັມ src = 1; src < s->len; src++) {
        ຈຳນວນເຕັມ dst = src_map[src];
        ຈຳນວນເຕັມ found = 0;

        ຖ້າ (dst <= src)
            continue;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        do {
            ສຳລັບ (ຈຳນວນເຕັມ j = 0; j < out_map_idx; j++) {
                ຖ້າ (dst == s->map[j]) {
                    found = 1;
                    bha_nga;
                }
            }
            dst = src_map[dst];
        } ໃນຂະນະທີ່ (dst != src && !found);

        ຖ້າ (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    ສົ່ງຄືນ 0;
}

static void parity_revtab_generator(ຈຳນວນເຕັມ *revtab, ຈຳນວນເຕັມ n, ຈຳນວນເຕັມ inv, ຈຳນວນເຕັມ offset,
                                    ຈຳນວນເຕັມ is_dual, ຈຳນວນເຕັມ dual_high, ຈຳນວນເຕັມ len,
                                    ຈຳນວນເຕັມ basis, ຈຳນວນເຕັມ dual_stride, ຈຳນວນເຕັມ inv_lookup)
{
    len >>= 1;

    ຖ້າ (len <= basis) {
        ຈຳນວນເຕັມ k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_high = is_dual & dual_high;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_high*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_high)*len + dual_high*len;

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            ຖ້າ (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ບໍ່ດັ່ງນັ້ນ {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ຖ້າ (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ສົ່ງຄືນ;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

ຈຳນວນເຕັມ ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ inv,
                                        FFTXCodeletOptions *opts,
                                        ຈຳນວນເຕັມ basis, ຈຳນວນເຕັມ dual_stride)
{
    basis >>= 1;
    ຖ້າ (len < basis)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (!(s->map = av_mallocz(len*parimaa_na(*s->map))))
        ສົ່ງຄືນ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ສົ່ງຄືນ 0;
}

static void reset_ctx(AVTXContext *s, ຈຳນວນເຕັມ free_sub)
{
    ຖ້າ (!s)
        ສົ່ງຄືນ;

    ຖ້າ (s->sub)
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ຖ້າ (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ຖ້າ (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = NULL;
    memset(s->fn, 0, parimaa_na(s->fn));
}

void ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold void av_tx_uninit(AVTXContext **ctx)
{
    ຖ້າ (!(*ctx))
        ສົ່ງຄືນ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

static av_cold ຈຳນວນເຕັມ ff_tx_null_init(AVTXContext *s, const FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ inv, const void *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ຖ້າ (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ສົ່ງຄືນ AVERROR(EINVAL);
    ສົ່ງຄືນ 0;
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
#ຖ້າ HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#ຖ້າ ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
static const ຈຳນວນເຕັມ codelet_list_num = FF_ARRAY_ELEMS(codelet_list);

static const ຈຳນວນເຕັມ cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

static const ຈຳນວນເຕັມ cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

static ຈຳນວນເຕັມ get_codelet_prio(const FFTXCodelet *cd, ຈຳນວນເຕັມ cpu_flags, ຈຳນວນເຕັມ len)
{
    ຈຳນວນເຕັມ prio = cd->prio;
    ຈຳນວນເຕັມ max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ຖ້າ ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ຖ້າ ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ຖ້າ ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ຖ້າ ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    ຖ້າ (max_factor)
        prio += 16*max_factor;

    ສົ່ງຄືນ prio;
}

typedef sa_nracanaa FFTXLenDecomp {
    ຈຳນວນເຕັມ len;
    ຈຳນວນເຕັມ len2;
    ຈຳນວນເຕັມ prio;
    const FFTXCodelet *cd;
} FFTXLenDecomp;

static ຈຳນວນເຕັມ cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ສົ່ງຄືນ FFDIFFSIGN(b->prio, a->prio);
}

ຈຳນວນເຕັມ ff_tx_decompose_length(ຈຳນວນເຕັມ dst[TX_MAX_DECOMPOSITIONS], ga_nanaa AVTXType type,
                           ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ inv)
{
    ຈຳນວນເຕັມ nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    ຈຳນວນເຕັມ codelet_list_idx = codelet_list_num;

    const ຈຳນວນເຕັມ cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ໃນຂະນະທີ່ (codelet_list_idx--) {
        const FFTXCodelet * const * list = codelet_list[codelet_list_idx];
        const FFTXCodelet *cd = NULL;

        ໃນຂະນະທີ່ ((cd = *list++)) {
            ຈຳນວນເຕັມ fl = len;
            ຈຳນວນເຕັມ skip = 0, prio;
            ຈຳນວນເຕັມ factors_product = 1, factors_mod = 0;

            ຖ້າ (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                goto sort;

            /* Check if the type matches */
            ຖ້າ (cd->type != TX_TYPE_ANY && type != cd->type)
                continue;

            /* Check direction for non-orthogonal codelets */
            ຖ້າ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                continue;

            /* Check if the CPU supports the required ISA */
            ຖ້າ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                continue;

            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < TX_MAX_FACTORS; i++) {
                ຖ້າ (!cd->factors[i] || (fl == 1))
                    bha_nga;

                ຖ້າ (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } ບໍ່ດັ່ງນັ້ນ ຖ້າ (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ຖ້າ (cd->factors[i] == 2) {
                        ຈຳນວນເຕັມ b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } ບໍ່ດັ່ງນັ້ນ {
                        do {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } ໃນຂະນະທີ່ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ຖ້າ ((factors_mod < cd->nb_factors) || (len == factors_product))
                continue;

            ຖ້າ (av_gcd(factors_product, fl) != 1)
                continue;

            /* Check if length is supported and factorization was successful */
            ຖ້າ ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                continue;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < nb_decomp; i++) {
                ຖ້າ (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    ຖ້າ (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    bha_nga;
                }
            }

            /* Add decomposition if unique */
            ຖ້າ (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ຖ້າ (!nb_decomp)
        ສົ່ງຄືນ AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < nb_decomp; i++) {
        ຖ້າ (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ບໍ່ດັ່ງນັ້ນ
            dst[i] = ld[i].len;
    }

    ສົ່ງຄືນ nb_decomp;
}

ຈຳນວນເຕັມ ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*parimaa_na(*s->map));
    ຖ້າ (!s->map)
        ສົ່ງຄືນ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ຖ້າ (s->inv) /* Reversing the ACs flips the transform direction */
        ສຳລັບ (ຈຳນວນເຕັມ i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ບໍ່ດັ່ງນັ້ນ
        ສຳລັບ (ຈຳນວນເຕັມ i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ສົ່ງຄືນ 0;
}

#ຖ້າ !CONFIG_SMALL
static void print_flags(AVBPrint *bp, uint64_t f)
{
    ຈຳນວນເຕັມ prev = 0;
    const var_na *sep = ", ";
    av_bprintf(bp, "flags: [");
    ຖ້າ ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ຖ້າ ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ຖ້າ ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ຖ້າ ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ຖ້າ ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ຖ້າ ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ຖ້າ ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ຖ້າ ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ຖ້າ ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ຖ້າ ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ຖ້າ ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

static void print_type(AVBPrint *bp, ga_nanaa AVTXType type)
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

static void print_cd_info(const FFTXCodelet *cd, ຈຳນວນເຕັມ prio, ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ print_prio,
                          ຈຳນວນເຕັມ log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ຖ້າ (!len) {
        ຖ້າ (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ຖ້າ (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ບໍ່ດັ່ງນັ້ນ
            av_bprintf(&bp, "%i", cd->max_len);
    } ບໍ່ດັ່ງນັ້ນ {
        av_bprintf(&bp, "%i", len);
    }

    ຖ້າ (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ຖ້າ (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ບໍ່ດັ່ງນັ້ນ
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < TX_MAX_FACTORS; i++) {
            ຖ້າ (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ຖ້າ (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            ບໍ່ດັ່ງນັ້ນ ຖ້າ (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ບໍ່ດັ່ງນັ້ນ
                bha_nga;
        }

        av_bprintf(&bp, "], ");
    } ບໍ່ດັ່ງນັ້ນ {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ຖ້າ (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(NULL, log_level, "%s\n", bp.str);
}

static void print_tx_structure(AVTXContext *s, ຈຳນວນເຕັມ depth)
{
    const FFTXCodelet *cd = s->cd_self;

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i <= depth; i++)
        av_log(NULL, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

typedef sa_nracanaa TXCodeletMatch {
    const FFTXCodelet *cd;
    ຈຳນວນເຕັມ prio;
} TXCodeletMatch;

static ຈຳນວນເຕັມ cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    ສົ່ງຄືນ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
static anta_hstha ຈຳນວນເຕັມ check_cd_factors(const FFTXCodelet *cd, ຈຳນວນເຕັມ len)
{
    ຈຳນວນເຕັມ matches = 0, any_flag = 0;

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < TX_MAX_FACTORS; i++) {
        ຈຳນວນເຕັມ factor = cd->factors[i];

        ຖ້າ (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            continue;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (len <= 1 || !factor) {
            bha_nga;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (factor == 2) { /* Fast path */
            ຈຳນວນເຕັມ bits_2 = ff_ctz(len);
            ຖ້າ (!bits_2)
                continue; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } ບໍ່ດັ່ງນັ້ນ {
            ຈຳນວນເຕັມ res = len % factor;
            ຖ້າ (res)
                continue; /* Factor not supported */

            ໃນຂະນະທີ່ (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    ສົ່ງຄືນ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold ຈຳນວນເຕັມ ff_tx_init_subtx(AVTXContext *s, ga_nanaa AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ຈຳນວນເຕັມ len, ຈຳນວນເຕັມ inv, const void *scale)
{
    ຈຳນວນເຕັມ ret = 0;
    AVTXContext *sub = NULL;
    TXCodeletMatch *cd_tmp, *cd_matches = NULL;
    unsigned ຈຳນວນເຕັມ cd_matches_size = 0;
    ຈຳນວນເຕັມ codelet_list_idx = codelet_list_num;
    ຈຳນວນເຕັມ nb_cd_matches = 0;
#ຖ້າ !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    const ຈຳນວນເຕັມ cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ຖ້າ (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ຖ້າ ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    ຖ້າ ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ໃນຂະນະທີ່ (codelet_list_idx--) {
        const FFTXCodelet * const * list = codelet_list[codelet_list_idx];
        const FFTXCodelet *cd = NULL;

        ໃນຂະນະທີ່ ((cd = *list++)) {
            /* Check if the type matches */
            ຖ້າ (cd->type != TX_TYPE_ANY && type != cd->type)
                continue;

            /* Check direction for non-orthogonal codelets */
            ຖ້າ (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                continue;

            /* Check if the requested flags match from both sides */
            ຖ້າ (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                continue;

            /* Check if length is supported */
            ຖ້າ ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                continue;

            /* Check if the CPU supports the required ISA */
            ຖ້າ (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                continue;

            /* Check for factors */
            ຖ້າ (!check_cd_factors(cd, len))
                continue;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     parimaa_na(*cd_tmp) * (nb_cd_matches + 1));
            ຖ້າ (!cd_tmp) {
                av_free(cd_matches);
                ສົ່ງຄືນ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ຖ້າ !CONFIG_SMALL
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
    ຖ້າ (!nb_cd_matches)
        ສົ່ງຄືນ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#ຖ້າ !CONFIG_SMALL
    av_log(NULL, AV_LOG_TRACE, "%s\n", bp.str);

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < nb_cd_matches; i++) {
        av_log(NULL, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    ຖ້າ (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*parimaa_na(*sub));
        ຖ້າ (!sub) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
    }

    /* Attempt to initialize each */
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < nb_cd_matches; i++) {
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
        ຖ້າ (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ຖ້າ (ret >= 0) {
            ຖ້າ (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*parimaa_na(*sctx->map));
                ຖ້າ (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    goto end;
                }

                ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (opts && (opts->map_dir != sctx->map_dir)) {
                ຈຳນວນເຕັມ *tmp = av_malloc(len*parimaa_na(*sctx->map));
                ຖ້າ (!tmp) {
                    ret = AVERROR(ENOMEM);
                    goto end;
                }

                memcpy(tmp, sctx->map, len*parimaa_na(*sctx->map));

                ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            goto end;
        }

        s->fn[s->nb_sub] = NULL;
        s->cd[s->nb_sub] = NULL;

        reset_ctx(sctx, 0);
        ຖ້າ (ret == AVERROR(ENOMEM))
            bha_nga;
    }

    ຖ້າ (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    ສົ່ງຄືນ ret;
}

av_cold ຈຳນວນເຕັມ av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ga_nanaa AVTXType type,
                       ຈຳນວນເຕັມ inv, ຈຳນວນເຕັມ len, const void *scale, uint64_t flags)
{
    ຈຳນວນເຕັມ ret;
    AVTXContext tmp = { 0 };
    const dviguu_na default_scale_d = 1.0;
    const float  default_scale_f = 1.0f;

    ຖ້າ (!len || type >= AV_TX_NB || !ctx || !tx)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ຖ້າ (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    ຖ້າ (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, NULL, len, inv, scale);
    ຖ້າ (ret < 0)
        ສົ່ງຄືນ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ຖ້າ !CONFIG_SMALL
    av_log(NULL, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    ສົ່ງຄືນ ret;
}
