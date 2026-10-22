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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "intmath.h"
#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "qsort.h"
#ଅନ୍ତର୍ଭାଵ "bprint.h"

#ଅନ୍ତର୍ଭାଵ "tx_priv.h"

#define TYPE_IS(type, x)               \
    (((x) == AV_TX_FLOAT_ ## type)  || \
     ((x) == AV_TX_DOUBLE_ ## type) || \
     ((x) == AV_TX_INT32_ ## type))

/* Calculates the modular multiplicative inverse */
ସ୍ଥିର av_always_inline ପୂର୍ଣ୍ଣସଂଖ୍ୟା mulinv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା n, ପୂର୍ଣ୍ଣସଂଖ୍ୟା m)
{
    n = n % m;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 1; x < m; x++)
        ଯଦି (((n * x) % m) == 1)
            ଫେରନ୍ତୁ x;
    av_assert0(0); /* Never reached */
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_pfa_ନିବେଶ_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା d1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d2)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା sl = d1*d2;

    s->map = av_malloc(s->len*ଆକାର(*s->map));
    ଯଦି (!s->map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < s->len; k += sl) {
        ଯଦି (s->inv || (opts && opts->map_dir == FF_TX_MAP_SCATTER)) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା m = 0; m < d2; m++)
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 0; n < d1; n++)
                    s->map[k + ((m*d1 + n*d2) % (sl))] = m*d1 + n;
        } ଅନ୍ୟଥା {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା m = 0; m < d2; m++)
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 0; n < d1; n++)
                    s->map[k + m*d1 + n] = (m*d1 + n*d2) % (sl);
        }

        ଯଦି (s->inv)
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 1; w <= ((sl) >> 1); w++)
                FFSWAP(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, s->map[k + w], s->map[k + sl - w]);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ଫେରନ୍ତୁ 0;
}

/* Guaranteed to work for any n, m where gcd(n, m) == 1 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n, ପୂର୍ଣ୍ଣସଂଖ୍ୟା m)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *in_map, *out_map;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = n*m;    /* Will not be equal to s->len for MDCTs */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା m_inv, n_inv;

    /* Make sure the numbers are coprime */
    ଯଦି (av_gcd(n, m) != 1)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    m_inv = mulinv(m, n);
    n_inv = mulinv(n, m);

    ଯଦି (!(s->map = av_malloc(2*len*ଆକାର(*s->map))))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    in_map  = s->map;
    out_map = s->map + len;

    /* Ruritanian map for input, CRT map for output, can be swapped */
    ଯଦି (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < m; j++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < n; i++) {
                in_map[(i*m + j*n) % len] = j*n + i;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    } ଅନ୍ୟଥା {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < m; j++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < n; i++) {
                in_map[j*n + i] = (i*m + j*n) % len;
                out_map[(i*m*m_inv + j*n*n_inv) % len] = i*m + j;
            }
        }
    }

    ଯଦି (inv) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < m; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା *in = &in_map[i*n + 1]; /* Skip the DC */
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ((n - 1) >> 1); j++)
                FFSWAP(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, in[j], in[n - j - 2]);
        }
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା split_radix_permutation(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv)
{
    len >>= 1;
    ଯଦି (len <= 1)
        ଫେରନ୍ତୁ i & 1;
    ଯଦି (!(i & len))
        ଫେରନ୍ତୁ split_radix_permutation(i, len, inv) * 2;
    len >>= 1;
    ଫେରନ୍ତୁ split_radix_permutation(i, len, inv) * 4 + 1 - 2*(!(i & len) ^ inv);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = s->len;

    ଯଦି (!(s->map = av_malloc(len*ଆକାର(*s->map))))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (opts && opts->map_dir == FF_TX_MAP_SCATTER) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->len; i++)
            s->map[-split_radix_permutation(i, len, s->inv) & (len - 1)] = i;
    } ଅନ୍ୟଥା {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->len; i++)
            s->map[i] = -split_radix_permutation(i, len, s->inv) & (len - 1);
    }

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_inplace_map(AVTXContext *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src_map, out_map_idx = 0;

    ଯଦି (!s->sub || !s->sub->map)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!(s->map = av_mallocz(len*ଆକାର(*s->map))))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    src_map = s->sub->map;

    /* The first coefficient is always already in-place */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା src = 1; src < s->len; src++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst = src_map[src];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା found = 0;

        ଯଦି (dst <= src)
            ଜାରି;

        /* This just checks if a closed loop has been encountered before,
         * and if so, skips it, since to fully permute a loop we must only
         * enter it once. */
        କର {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < out_map_idx; j++) {
                ଯଦି (dst == s->map[j]) {
                    found = 1;
                    ଭାଙ୍ଗ;
                }
            }
            dst = src_map[dst];
        } ଯେତେବେଳେ (dst != src && !found);

        ଯଦି (!found)
            s->map[out_map_idx++] = src;
    }

    s->map[out_map_idx++] = 0;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ parity_revtab_generator(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *revtab, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset,
                                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_dual, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dual_ଉପର, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len,
                                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା basis, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dual_stride, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv_lookup)
{
    len >>= 1;

    ଯଦି (len <= basis) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା k1, k2, stride, even_idx, odd_idx;

        is_dual = is_dual && dual_stride;
        dual_ଉପର = is_dual & dual_ଉପର;
        stride = is_dual ? FFMIN(dual_stride, len) : 0;

        even_idx = offset + dual_ଉପର*(stride - 2*len);
        odd_idx  = even_idx + len + (is_dual && !dual_ଉପର)*len + dual_ଉପର*len;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < len; i++) {
            k1 = -split_radix_permutation(offset + i*2 + 0, n, inv) & (n - 1);
            k2 = -split_radix_permutation(offset + i*2 + 1, n, inv) & (n - 1);
            ଯଦି (inv_lookup) {
                revtab[even_idx++] = k1;
                revtab[odd_idx++]  = k2;
            } ଅନ୍ୟଥା {
                revtab[k1] = even_idx++;
                revtab[k2] = odd_idx++;
            }
            ଯଦି (stride && !((i + 1) % stride)) {
                even_idx += stride;
                odd_idx  += stride;
            }
        }

        ଫେରନ୍ତୁ;
    }

    parity_revtab_generator(revtab, n, inv, offset,
                            0, 0, len >> 0, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0),
                            1, 0, len >> 1, basis, dual_stride, inv_lookup);
    parity_revtab_generator(revtab, n, inv, offset + (len >> 0) + (len >> 1),
                            1, 1, len >> 1, basis, dual_stride, inv_lookup);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv,
                                        FFTXCodeletOptions *opts,
                                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା basis, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dual_stride)
{
    basis >>= 1;
    ଯଦି (len < basis)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!(s->map = av_mallocz(len*ଆକାର(*s->map))))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    av_assert0(!dual_stride || !(dual_stride & (dual_stride - 1)));
    av_assert0(dual_stride <= basis);

    parity_revtab_generator(s->map, len, inv, 0, 0, 0, len,
                            basis, dual_stride,
                            opts ? opts->map_dir == FF_TX_MAP_GATHER : FF_TX_MAP_GATHER);

    s->map_dir = opts ? opts->map_dir : FF_TX_MAP_GATHER;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ reset_ctx(AVTXContext *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା free_sub)
{
    ଯଦି (!s)
        ଫେରନ୍ତୁ;

    ଯଦି (s->sub)
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < TX_MAX_SUB; i++)
            reset_ctx(&s->sub[i], free_sub + 1);

    ଯଦି (s->cd_self && s->cd_self->uninit)
        s->cd_self->uninit(s);

    ଯଦି (free_sub)
        av_freep(&s->sub);

    av_freep(&s->map);
    av_freep(&s->exp);
    av_freep(&s->tmp);

    /* Nothing else needs to be reset, it gets overwritten if another
     * ff_tx_init_subtx() call is made. */
    s->nb_sub = 0;
    s->opaque = ଖାଲି;
    memset(s->fn, 0, ଆକାର(s->fn));
}

ଶୂନ୍ୟ ff_tx_clear_ctx(AVTXContext *s)
{
    reset_ctx(s, 0);
}

av_cold ଶୂନ୍ୟ av_tx_uninit(AVTXContext **ctx)
{
    ଯଦି (!(*ctx))
        ଫେରନ୍ତୁ;

    reset_ctx(*ctx, 1);
    av_freep(ctx);
}

ସ୍ଥିର av_cold ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_null_init(AVTXContext *s, ଅଚଳ FFTXCodelet *cd,
                                   uint64_t flags, FFTXCodeletOptions *opts,
                                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv, ଅଚଳ ଶୂନ୍ୟ *scale)
{
    /* Can only handle one sample+type to one sample+type transforms */
    ଯଦି (TYPE_IS(MDCT, s->type) || TYPE_IS(RDFT, s->type))
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଫେରନ୍ତୁ 0;
}

/* Null transform when the length is 1 */
ସ୍ଥିର ଶୂନ୍ୟ ff_tx_null(AVTXContext *s, ଶୂନ୍ୟ *_out, ଶୂନ୍ୟ *_in, ptrdiff_t stride)
{
    memcpy(_out, _in, stride);
}

ସ୍ଥିର ଅଚଳ FFTXCodelet ff_tx_null_def = {
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

ସ୍ଥିର ଅଚଳ FFTXCodelet * ଅଚଳ ff_tx_null_list[] = {
    &ff_tx_null_def,
    ଖାଲି,
};

/* Array of all compiled codelet lists. Order is irrelevant. */
ସ୍ଥିର ଅଚଳ FFTXCodelet * ଅଚଳ * ଅଚଳ codelet_list[] = {
    ff_tx_codelet_list_float_c,
    ff_tx_codelet_list_double_c,
    ff_tx_codelet_list_int32_c,
    ff_tx_null_list,
#ଯଦି HAVE_X86ASM
    ff_tx_codelet_list_float_x86,
#endif
#ଯଦି ARCH_AARCH64
    ff_tx_codelet_list_float_aarch64,
#endif
};
ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା codelet_list_ଅଙ୍କ = FF_ARRAY_ELEMS(codelet_list);

ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_slow_mask = AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE3SLOW  |
                                 AV_CPU_FLAG_ATOM     | AV_CPU_FLAG_SSSE3SLOW |
                                 AV_CPU_FLAG_AVXSLOW  | AV_CPU_FLAG_SLOW_GATHER;

ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_slow_penalties[][2] = {
    { AV_CPU_FLAG_SSE2SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSE3SLOW,    1 + 64  },
    { AV_CPU_FLAG_SSSE3SLOW,   1 + 64  },
    { AV_CPU_FLAG_ATOM,        1 + 128 },
    { AV_CPU_FLAG_AVXSLOW,     1 + 128 },
    { AV_CPU_FLAG_SLOW_GATHER, 1 + 32  },
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_codelet_prio(ଅଚଳ FFTXCodelet *cd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା prio = cd->prio;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_factor = 0;

    /* If the CPU has a SLOW flag, and the instruction is also flagged
     * as being slow for such, reduce its priority */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(cpu_slow_penalties); i++) {
        ଯଦି ((cpu_flags & cd->cpu_flags) & cpu_slow_penalties[i][0])
            prio -= cpu_slow_penalties[i][1];
    }

    /* Prioritize aligned-only codelets */
    ଯଦି ((cd->flags & FF_TX_ALIGNED) && !(cd->flags & AV_TX_UNALIGNED))
        prio += 64;

    /* Codelets for specific lengths are generally faster */
    ଯଦି ((len == cd->min_len) && (len == cd->max_len))
        prio += 64;

    /* Forward-only or inverse-only transforms are generally better */
    ଯଦି ((cd->flags & (FF_TX_FORWARD_ONLY | FF_TX_INVERSE_ONLY)))
        prio += 64;

    /* Larger factors are generally better */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < TX_MAX_SUB; i++)
        max_factor = FFMAX(cd->factors[i], max_factor);
    ଯଦି (max_factor)
        prio += 16*max_factor;

    ଫେରନ୍ତୁ prio;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FFTXLenDecomp {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା prio;
    ଅଚଳ FFTXCodelet *cd;
} FFTXLenDecomp;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp_decomp(FFTXLenDecomp *a, FFTXLenDecomp *b)
{
    ଫେରନ୍ତୁ FFDIFFSIGN(b->prio, a->prio);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_decompose_length(ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst[TX_MAX_DECOMPOSITIONS], ଗଣନା AVTXType type,
                           ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_decomp = 0;
    FFTXLenDecomp ld[TX_MAX_DECOMPOSITIONS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା codelet_list_idx = codelet_list_ଅଙ୍କ;

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags = av_get_cpu_flags();

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ଯେତେବେଳେ (codelet_list_idx--) {
        ଅଚଳ FFTXCodelet * ଅଚଳ * list = codelet_list[codelet_list_idx];
        ଅଚଳ FFTXCodelet *cd = ଖାଲି;

        ଯେତେବେଳେ ((cd = *list++)) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା fl = len;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା skip = 0, prio;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା factors_product = 1, factors_mod = 0;

            ଯଦି (nb_decomp >= TX_MAX_DECOMPOSITIONS)
                ଯାଅ sort;

            /* Check if the type matches */
            ଯଦି (cd->type != TX_TYPE_ANY && type != cd->type)
                ଜାରି;

            /* Check direction for non-orthogonal codelets */
            ଯଦି (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ଜାରି;

            /* Check if the CPU supports the required ISA */
            ଯଦି (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ଜାରି;

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < TX_MAX_FACTORS; i++) {
                ଯଦି (!cd->factors[i] || (fl == 1))
                    ଭାଙ୍ଗ;

                ଯଦି (cd->factors[i] == TX_FACTOR_ANY) {
                    factors_mod++;
                    factors_product *= fl;
                } ଅନ୍ୟଥା ଯଦି (!(fl % cd->factors[i])) {
                    factors_mod++;
                    ଯଦି (cd->factors[i] == 2) {
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା b = ff_ctz(fl);
                        fl >>= b;
                        factors_product <<= b;
                    } ଅନ୍ୟଥା {
                        କର {
                            fl /= cd->factors[i];
                            factors_product *= cd->factors[i];
                        } ଯେତେବେଳେ (!(fl % cd->factors[i]));
                    }
                }
            }

            /* Disqualify if factor requirements are not satisfied or if trivial */
            ଯଦି ((factors_mod < cd->nb_factors) || (len == factors_product))
                ଜାରି;

            ଯଦି (av_gcd(factors_product, fl) != 1)
                ଜାରି;

            /* Check if length is supported and factorization was successful */
            ଯଦି ((factors_product < cd->min_len) ||
                (cd->max_len != TX_LEN_UNLIMITED && (factors_product > cd->max_len)))
                ଜାରି;

            prio = get_codelet_prio(cd, cpu_flags, factors_product) * factors_product;

            /* Check for duplicates */
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_decomp; i++) {
                ଯଦି (factors_product == ld[i].len) {
                    /* Update priority if new one is higher */
                    ଯଦି (prio > ld[i].prio)
                        ld[i].prio = prio;
                    skip = 1;
                    ଭାଙ୍ଗ;
                }
            }

            /* Add decomposition if unique */
            ଯଦି (!skip) {
                ld[nb_decomp].cd = cd;
                ld[nb_decomp].len = factors_product;
                ld[nb_decomp].len2 = fl;
                ld[nb_decomp].prio = prio;
                nb_decomp++;
            }
        }
    }

    ଯଦି (!nb_decomp)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

sort:
    AV_QSORT(ld, nb_decomp, FFTXLenDecomp, cmp_decomp);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_decomp; i++) {
        ଯଦି (ld[i].cd->nb_factors > 1)
            dst[i] = ld[i].len2;
        ଅନ୍ୟଥା
            dst[i] = ld[i].len;
    }

    ଫେରନ୍ତୁ nb_decomp;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts)
{
    s->map = av_malloc(s->len*ଆକାର(*s->map));
    ଯଦି (!s->map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    s->map[0] = 0; /* DC is always at the start */
    ଯଦି (s->inv) /* Reversing the ACs flips the transform direction */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; i < s->len; i++)
            s->map[i] = s->len - i;
    ଅନ୍ୟଥା
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; i < s->len; i++)
            s->map[i] = i;

    s->map_dir = FF_TX_MAP_GATHER;

    ଫେରନ୍ତୁ 0;
}

#ଯଦି !CONFIG_SMALL
ସ୍ଥିର ଶୂନ୍ୟ print_flags(AVBPrint *bp, uint64_t f)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା prev = 0;
    ଅଚଳ ଅକ୍ଷର *sep = ", ";
    av_bprintf(bp, "flags: [");
    ଯଦି ((f & FF_TX_ALIGNED) && ++prev)
        av_bprintf(bp, "aligned");
    ଯଦି ((f & AV_TX_UNALIGNED) && ++prev)
        av_bprintf(bp, "%sunaligned", prev > 1 ? sep : "");
    ଯଦି ((f & AV_TX_INPLACE) && ++prev)
        av_bprintf(bp, "%sinplace", prev > 1 ? sep : "");
    ଯଦି ((f & FF_TX_OUT_OF_PLACE) && ++prev)
        av_bprintf(bp, "%sout_of_place", prev > 1 ? sep : "");
    ଯଦି ((f & FF_TX_FORWARD_ONLY) && ++prev)
        av_bprintf(bp, "%sfwd_only", prev > 1 ? sep : "");
    ଯଦି ((f & FF_TX_INVERSE_ONLY) && ++prev)
        av_bprintf(bp, "%sinv_only", prev > 1 ? sep : "");
    ଯଦି ((f & FF_TX_PRESHUFFLE) && ++prev)
        av_bprintf(bp, "%spreshuf", prev > 1 ? sep : "");
    ଯଦି ((f & AV_TX_FULL_IMDCT) && ++prev)
        av_bprintf(bp, "%simdct_full", prev > 1 ? sep : "");
    ଯଦି ((f & AV_TX_REAL_TO_REAL) && ++prev)
        av_bprintf(bp, "%sreal_to_real", prev > 1 ? sep : "");
    ଯଦି ((f & AV_TX_REAL_TO_IMAGINARY) && ++prev)
        av_bprintf(bp, "%sreal_to_imaginary", prev > 1 ? sep : "");
    ଯଦି ((f & FF_TX_ASM_CALL) && ++prev)
        av_bprintf(bp, "%sasm_call", prev > 1 ? sep : "");
    av_bprintf(bp, "]");
}

ସ୍ଥିର ଶୂନ୍ୟ print_type(AVBPrint *bp, ଗଣନା AVTXType type)
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

ସ୍ଥିର ଶୂନ୍ୟ print_cd_info(ଅଚଳ FFTXCodelet *cd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା prio, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା print_prio,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_level)
{
    AVBPrint bp;
    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    av_bprintf(&bp, "%s - type: ", cd->name);

    print_type(&bp, cd->type);

    av_bprintf(&bp, ", len: ");
    ଯଦି (!len) {
        ଯଦି (cd->min_len != cd->max_len)
            av_bprintf(&bp, "[%i, ", cd->min_len);

        ଯଦି (cd->max_len == TX_LEN_UNLIMITED)
            av_bprintf(&bp, "∞");
        ଅନ୍ୟଥା
            av_bprintf(&bp, "%i", cd->max_len);
    } ଅନ୍ୟଥା {
        av_bprintf(&bp, "%i", len);
    }

    ଯଦି (cd->factors[1]) {
        av_bprintf(&bp, "%s, factors", !len && cd->min_len != cd->max_len ? "]" : "");
        ଯଦି (!cd->nb_factors)
            av_bprintf(&bp, ": [");
        ଅନ୍ୟଥା
            av_bprintf(&bp, "[%i]: [", cd->nb_factors);

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < TX_MAX_FACTORS; i++) {
            ଯଦି (i && cd->factors[i])
                av_bprintf(&bp, ", ");
            ଯଦି (cd->factors[i] == TX_FACTOR_ANY)
                av_bprintf(&bp, "any");
            ଅନ୍ୟଥା ଯଦି (cd->factors[i])
                av_bprintf(&bp, "%i", cd->factors[i]);
            ଅନ୍ୟଥା
                ଭାଙ୍ଗ;
        }

        av_bprintf(&bp, "], ");
    } ଅନ୍ୟଥା {
        av_bprintf(&bp, "%s, factor: %i, ",
                   !len && cd->min_len != cd->max_len ? "]" : "", cd->factors[0]);
    }
    print_flags(&bp, cd->flags);

    ଯଦି (print_prio)
        av_bprintf(&bp, ", prio: %i", prio);

    av_log(ଖାଲି, log_level, "%s\n", bp.str);
}

ସ୍ଥିର ଶୂନ୍ୟ print_tx_structure(AVTXContext *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth)
{
    ଅଚଳ FFTXCodelet *cd = s->cd_self;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i <= depth; i++)
        av_log(ଖାଲି, AV_LOG_DEBUG, "    ");

    print_cd_info(cd, cd->prio, s->len, 0, AV_LOG_DEBUG);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->nb_sub; i++)
        print_tx_structure(&s->sub[i], depth + 1);
}
#endif /* CONFIG_SMALL */

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା TXCodeletMatch {
    ଅଚଳ FFTXCodelet *cd;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା prio;
} TXCodeletMatch;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp_matches(TXCodeletMatch *a, TXCodeletMatch *b)
{
    ଫେରନ୍ତୁ FFDIFFSIGN(b->prio, a->prio);
}

/* We want all factors to completely cover the length */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_cd_factors(ଅଚଳ FFTXCodelet *cd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା matches = 0, any_flag = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < TX_MAX_FACTORS; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା factor = cd->factors[i];

        ଯଦି (factor == TX_FACTOR_ANY) {
            any_flag = 1;
            matches++;
            ଜାରି;
        } ଅନ୍ୟଥା ଯଦି (len <= 1 || !factor) {
            ଭାଙ୍ଗ;
        } ଅନ୍ୟଥା ଯଦି (factor == 2) { /* Fast path */
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits_2 = ff_ctz(len);
            ଯଦି (!bits_2)
                ଜାରି; /* Factor not supported */

            len >>= bits_2;
            matches++;
        } ଅନ୍ୟଥା {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = len % factor;
            ଯଦି (res)
                ଜାରି; /* Factor not supported */

            ଯେତେବେଳେ (!res) {
                len /= factor;
                res = len % factor;
            }
            matches++;
        }
    }

    ଫେରନ୍ତୁ (cd->nb_factors <= matches) && (any_flag || len == 1);
}

av_cold ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_tx_init_subtx(AVTXContext *s, ଗଣନା AVTXType type,
                             uint64_t flags, FFTXCodeletOptions *opts,
                             ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv, ଅଚଳ ଶୂନ୍ୟ *scale)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;
    AVTXContext *sub = ଖାଲି;
    TXCodeletMatch *cd_tmp, *cd_matches = ଖାଲି;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା cd_matches_size = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା codelet_list_idx = codelet_list_ଅଙ୍କ;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_cd_matches = 0;
#ଯଦି !CONFIG_SMALL
    AVBPrint bp;
#endif

    /* We still accept functions marked with SLOW, even if the CPU is
     * marked with the same flag, but we give them lower priority. */
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags = av_get_cpu_flags();

    /* Flags the transform wants */
    uint64_t req_flags = flags;

    /* Flags the codelet may require to be present */
    uint64_t inv_req_mask = AV_TX_FULL_IMDCT |
                            AV_TX_REAL_TO_REAL |
                            AV_TX_REAL_TO_IMAGINARY |
                            FF_TX_PRESHUFFLE |
                            FF_TX_ASM_CALL;

    /* Unaligned codelets are compatible with the aligned flag */
    ଯଦି (req_flags & FF_TX_ALIGNED)
        req_flags |= AV_TX_UNALIGNED;

    /* If either flag is set, both are okay, so don't check for an exact match */
    ଯଦି ((req_flags & AV_TX_INPLACE) && (req_flags & FF_TX_OUT_OF_PLACE))
        req_flags &= ~(AV_TX_INPLACE | FF_TX_OUT_OF_PLACE);
    ଯଦି ((req_flags & FF_TX_ALIGNED) && (req_flags & AV_TX_UNALIGNED))
        req_flags &= ~(FF_TX_ALIGNED | AV_TX_UNALIGNED);

    /* Loop through all codelets in all codelet lists to find matches
     * to the requirements */
    ଯେତେବେଳେ (codelet_list_idx--) {
        ଅଚଳ FFTXCodelet * ଅଚଳ * list = codelet_list[codelet_list_idx];
        ଅଚଳ FFTXCodelet *cd = ଖାଲି;

        ଯେତେବେଳେ ((cd = *list++)) {
            /* Check if the type matches */
            ଯଦି (cd->type != TX_TYPE_ANY && type != cd->type)
                ଜାରି;

            /* Check direction for non-orthogonal codelets */
            ଯଦି (((cd->flags & FF_TX_FORWARD_ONLY) && inv) ||
                ((cd->flags & (FF_TX_INVERSE_ONLY | AV_TX_FULL_IMDCT)) && !inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_REAL)) && inv) ||
                ((cd->flags & (FF_TX_FORWARD_ONLY | AV_TX_REAL_TO_IMAGINARY)) && inv))
                ଜାରି;

            /* Check if the requested flags match from both sides */
            ଯଦି (((req_flags    & cd->flags) != (req_flags)) ||
                ((inv_req_mask & cd->flags) != (req_flags & inv_req_mask)))
                ଜାରି;

            /* Check if length is supported */
            ଯଦି ((len < cd->min_len) || (cd->max_len != -1 && (len > cd->max_len)))
                ଜାରି;

            /* Check if the CPU supports the required ISA */
            ଯଦି (cd->cpu_flags != FF_TX_CPU_FLAGS_ALL &&
                !(cpu_flags & (cd->cpu_flags & ~cpu_slow_mask)))
                ଜାରି;

            /* Check for factors */
            ଯଦି (!check_cd_factors(cd, len))
                ଜାରି;

            /* Realloc array and append */
            cd_tmp = av_fast_realloc(cd_matches, &cd_matches_size,
                                     ଆକାର(*cd_tmp) * (nb_cd_matches + 1));
            ଯଦି (!cd_tmp) {
                av_free(cd_matches);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }

            cd_matches                     = cd_tmp;
            cd_matches[nb_cd_matches].cd   = cd;
            cd_matches[nb_cd_matches].prio = get_codelet_prio(cd, cpu_flags, len);
            nb_cd_matches++;
        }
    }

#ଯଦି !CONFIG_SMALL
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
    ଯଦି (!nb_cd_matches)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);

    /* Sort the list */
    AV_QSORT(cd_matches, nb_cd_matches, TXCodeletMatch, cmp_matches);

#ଯଦି !CONFIG_SMALL
    av_log(ଖାଲି, AV_LOG_TRACE, "%s\n", bp.str);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_cd_matches; i++) {
        av_log(ଖାଲି, AV_LOG_TRACE, "    %i: ", i + 1);
        print_cd_info(cd_matches[i].cd, cd_matches[i].prio, 0, 1, AV_LOG_TRACE);
    }
#endif

    ଯଦି (!s->sub) {
        s->sub = sub = av_mallocz(TX_MAX_SUB*ଆକାର(*sub));
        ଯଦି (!sub) {
            ret = AVERROR(ENOMEM);
            ଯାଅ end;
        }
    }

    /* Attempt to initialize each */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_cd_matches; i++) {
        ଅଚଳ FFTXCodelet *cd = cd_matches[i].cd;
        AVTXContext *sctx = &s->sub[s->nb_sub];

        sctx->len        = len;
        sctx->inv        = inv;
        sctx->type       = type;
        sctx->flags      = cd->flags | flags;
        sctx->cd_self    = cd;

        s->fn[s->nb_sub] = cd->function;
        s->cd[s->nb_sub] = cd;

        ret = 0;
        ଯଦି (cd->init)
            ret = cd->init(sctx, cd, flags, opts, len, inv, scale);

        ଯଦି (ret >= 0) {
            ଯଦି (opts && opts->map_dir != FF_TX_MAP_NONE &&
                sctx->map_dir == FF_TX_MAP_NONE) {
                /* If a specific map direction was requested, and it doesn't
                 * exist, create one.*/
                sctx->map = av_malloc(len*ଆକାର(*sctx->map));
                ଯଦି (!sctx->map) {
                    ret = AVERROR(ENOMEM);
                    ଯାଅ end;
                }

                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < len; i++)
                    sctx->map[i] = i;
            } ଅନ୍ୟଥା ଯଦି (opts && (opts->map_dir != sctx->map_dir)) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା *tmp = av_malloc(len*ଆକାର(*sctx->map));
                ଯଦି (!tmp) {
                    ret = AVERROR(ENOMEM);
                    ଯାଅ end;
                }

                memcpy(tmp, sctx->map, len*ଆକାର(*sctx->map));

                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < len; i++)
                    sctx->map[tmp[i]] = i;

                av_free(tmp);
            }

            s->nb_sub++;
            ଯାଅ end;
        }

        s->fn[s->nb_sub] = ଖାଲି;
        s->cd[s->nb_sub] = ଖାଲି;

        reset_ctx(sctx, 0);
        ଯଦି (ret == AVERROR(ENOMEM))
            ଭାଙ୍ଗ;
    }

    ଯଦି (!s->nb_sub)
        av_freep(&s->sub);

end:
    av_free(cd_matches);
    ଫେରନ୍ତୁ ret;
}

av_cold ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_tx_init(AVTXContext **ctx, av_tx_fn *tx, ଗଣନା AVTXType type,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ଅଚଳ ଶୂନ୍ୟ *scale, uint64_t flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    AVTXContext tmp = { 0 };
    ଅଚଳ ଦ୍ୱିଗୁଣ default_scale_d = 1.0;
    ଅଚଳ ଦଶମିକ  default_scale_f = 1.0f;

    ଯଦି (!len || type >= AV_TX_NB || !ctx || !tx)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!(flags & AV_TX_UNALIGNED))
        flags |= FF_TX_ALIGNED;
    ଯଦି (!(flags & AV_TX_INPLACE))
        flags |= FF_TX_OUT_OF_PLACE;

    ଯଦି (!scale && ((type == AV_TX_DOUBLE_MDCT) || (type == AV_TX_DOUBLE_DCT) ||
                   (type == AV_TX_DOUBLE_DCT_I) || (type == AV_TX_DOUBLE_DST_I) ||
                   (type == AV_TX_DOUBLE_RDFT)))
        scale = &default_scale_d;
    ଅନ୍ୟଥା ଯଦି (!scale && !TYPE_IS(FFT, type))
        scale = &default_scale_f;

    ret = ff_tx_init_subtx(&tmp, type, flags, ଖାଲି, len, inv, scale);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    *ctx = &tmp.sub[0];
    *tx  = tmp.fn[0];

#ଯଦି !CONFIG_SMALL
    av_log(ଖାଲି, AV_LOG_DEBUG, "Transform tree:\n");
    print_tx_structure(*ctx, 0);
#endif

    ଫେରନ୍ତୁ ret;
}
