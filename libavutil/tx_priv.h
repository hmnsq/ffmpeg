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

#ifndef AVUTIL_TX_PRIV_H
#define AVUTIL_TX_PRIV_H

#அந்தர்பாவ "tx.h"
#அந்தர்பாவ "thread.h"
#அந்தர்பாவ "mem_internal.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "attributes.h"

#ifdef TX_FLOAT
#define TX_TAB(x) x ## _float
#define TX_NAME(x) x ## _float_c
#define TX_NAME_STR(x) NULL_IF_CONFIG_SMALL(x "_float_c")
#define TX_TYPE(x) AV_TX_FLOAT_ ## x
#define TX_FN_NAME(fn, suffix) ff_tx_ ## fn ## _float_ ## suffix
#define TX_FN_NAME_STR(fn, suffix) NULL_IF_CONFIG_SMALL(#fn "_float_" #suffix)
#define MULT(x, m) ((x) * (m))
#define SCALE_TYPE தசம
வகைவரை தசம TXSample;
வகைவரை தசம TXUSample;
வகைவரை AVComplexFloat TXComplex;
#அல்லதெனில் defined(TX_DOUBLE)
#define TX_TAB(x) x ## _double
#define TX_NAME(x) x ## _double_c
#define TX_NAME_STR(x) NULL_IF_CONFIG_SMALL(x "_double_c")
#define TX_TYPE(x) AV_TX_DOUBLE_ ## x
#define TX_FN_NAME(fn, suffix) ff_tx_ ## fn ## _double_ ## suffix
#define TX_FN_NAME_STR(fn, suffix) NULL_IF_CONFIG_SMALL(#fn "_double_" #suffix)
#define MULT(x, m) ((x) * (m))
#define SCALE_TYPE இரட்டை
வகைவரை இரட்டை TXSample;
வகைவரை இரட்டை TXUSample;
வகைவரை AVComplexDouble TXComplex;
#அல்லதெனில் defined(TX_INT32)
#define TX_TAB(x) x ## _int32
#define TX_NAME(x) x ## _int32_c
#define TX_NAME_STR(x) NULL_IF_CONFIG_SMALL(x "_int32_c")
#define TX_TYPE(x) AV_TX_INT32_ ## x
#define TX_FN_NAME(fn, suffix) ff_tx_ ## fn ## _int32_ ## suffix
#define TX_FN_NAME_STR(fn, suffix) NULL_IF_CONFIG_SMALL(#fn "_int32_" #suffix)
#define MULT(x, m) (((((int64_t)(x)) * (int64_t)(m)) + 0x40000000) >> 31)
#define SCALE_TYPE தசம
வகைவரை int32_t TXSample;
வகைவரை uint32_t TXUSample;
வகைவரை AVComplexInt32 TXComplex;
#இல்லையெனில்
வகைவரை வெறுமை TXComplex;
#endif

#define TX_DECL_FN(fn, suffix) \
    வெறுமை TX_FN_NAME(fn, suffix)(AVTXContext *s, வெறுமை *o, வெறுமை *i, ptrdiff_t st);

#define TX_DEF(fn, tx_type, len_min, len_max, f1, f2,                          \
               p, init_fn, suffix, cf, cd_flags, cf2)                          \
    &(மாறிலி FFTXCodelet){                                                      \
        .name       = TX_FN_NAME_STR(fn, suffix),                              \
        .function   = TX_FN_NAME(fn, suffix),                                  \
        .type       = TX_TYPE(tx_type),                                        \
        .flags      = FF_TX_ALIGNED | FF_TX_OUT_OF_PLACE | cd_flags,           \
        .factors    = { (f1), (f2) },                                          \
        .nb_factors = !!(f1) + !!(f2),                                         \
        .min_len    = len_min,                                                 \
        .max_len    = len_max,                                                 \
        .init       = init_fn,                                                 \
        .cpu_flags  = cf2 | AV_CPU_FLAG_ ## cf,                                \
        .prio       = p,                                                       \
    }

#எனில் defined(TX_FLOAT) || defined(TX_DOUBLE)

#define CMUL(dre, dim, are, aim, bre, bim)      \
    செய் {                                        \
        (dre) = (are) * (bre) - (aim) * (bim);  \
        (dim) = (are) * (bim) + (aim) * (bre);  \
    } போது (0)

#define SMUL(dre, dim, are, aim, bre, bim)      \
    செய் {                                        \
        (dre) = (are) * (bre) - (aim) * (bim);  \
        (dim) = (are) * (bim) - (aim) * (bre);  \
    } போது (0)

#define UNSCALE(x) (x)
#define RESCALE(x) (x)

#define FOLD(a, b) ((a) + (b))

#define BF(x, y, a, b)  \
    செய் {                \
        x = (a) - (b);  \
        y = (a) + (b);  \
    } போது (0)

#அல்லதெனில் defined(TX_INT32)

/* Properly rounds the result */
#define CMUL(dre, dim, are, aim, bre, bim)             \
    செய் {                                               \
        int64_t accu;                                  \
        (accu)  = (int64_t)(bre) * (are);              \
        (accu) -= (int64_t)(bim) * (aim);              \
        (dre)   = (முழு)(((accu) + 0x40000000) >> 31);  \
        (accu)  = (int64_t)(bim) * (are);              \
        (accu) += (int64_t)(bre) * (aim);              \
        (dim)   = (முழு)(((accu) + 0x40000000) >> 31);  \
    } போது (0)

#define SMUL(dre, dim, are, aim, bre, bim)             \
    செய் {                                               \
        int64_t accu;                                  \
        (accu)  = (int64_t)(bre) * (are);              \
        (accu) -= (int64_t)(bim) * (aim);              \
        (dre)   = (முழு)(((accu) + 0x40000000) >> 31);  \
        (accu)  = (int64_t)(bim) * (are);              \
        (accu) -= (int64_t)(bre) * (aim);              \
        (dim)   = (முழு)(((accu) + 0x40000000) >> 31);  \
    } போது (0)

#define UNSCALE(x) ((இரட்டை)(x)/2147483648.0)
#define RESCALE(x) (av_clip64(llrintf((x) * 2147483648.0), INT32_MIN, INT32_MAX))

#define FOLD(x, y) ((int32_t)((x) + (unsigned)(y) + 32) >> 6)

#define BF(x, y, a, b)  \
    செய் {                \
        x = (a) - (unsigned)(b);  \
        y = (a) + (unsigned)(b);  \
    } போது (0)

#endif /* TX_INT32 */

#define CMUL3(c, a, b) CMUL((c).re, (c).im, (a).re, (a).im, (b).re, (b).im)

/* Codelet flags, used to pick codelets. Must be a superset of enum AVTXFlags,
 * but if it runs out of bits, it can be made separate. */
#define FF_TX_OUT_OF_PLACE (1ULL << 63) /* Can be OR'd with AV_TX_INPLACE             */
#define FF_TX_ALIGNED      (1ULL << 62) /* Cannot be OR'd with AV_TX_UNALIGNED        */
#define FF_TX_PRESHUFFLE   (1ULL << 61) /* Codelet expects permuted coeffs            */
#define FF_TX_INVERSE_ONLY (1ULL << 60) /* For non-orthogonal inverse-only transforms */
#define FF_TX_FORWARD_ONLY (1ULL << 59) /* For non-orthogonal forward-only transforms */
#define FF_TX_ASM_CALL     (1ULL << 58) /* For asm->asm functions only                */

வகைவரை எண்ணிக்கை FFTXCodeletPriority {
    FF_TX_PRIO_BASE = 0,               /* Baseline priority */

    /* For SIMD, set base prio to the register size in bits and increment in
     * steps of 64 depending on faster/slower features, like FMA. */

    FF_TX_PRIO_MIN          = -131072, /* For naive implementations */
    FF_TX_PRIO_MAX          =  32768,  /* For custom implementations/ASICs */
} FFTXCodeletPriority;

வகைவரை எண்ணிக்கை FFTXMapDirection {
    /* No map. Make a map up. */
    FF_TX_MAP_NONE = 0,

    /* Lookup table must be applied via dst[i] = src[lut[i]]; */
    FF_TX_MAP_GATHER,

    /* Lookup table must be applied via dst[lut[i]] = src[i]; */
    FF_TX_MAP_SCATTER,
} FFTXMapDirection;

/* Codelet options */
வகைவரை கட்டமைப்பு FFTXCodeletOptions {
    /* Request a specific lookup table direction. Codelets MUST put the
     * direction in AVTXContext. If the codelet does not respect this, a
     * conversion will be performed. */
    FFTXMapDirection map_dir;
} FFTXCodeletOptions;

/* Maximum number of factors a codelet may have. Arbitrary. */
#define TX_MAX_FACTORS 16

/* Maximum amount of subtransform functions, subtransforms and factors. Arbitrary. */
#define TX_MAX_SUB 4

/* Maximum number of returned results for ff_tx_decompose_length. Arbitrary. */
#define TX_MAX_DECOMPOSITIONS 512

வகைவரை கட்டமைப்பு FFTXCodelet {
    மாறிலி எழுத்து    *name;          /* Codelet name, for debugging */
    av_tx_fn       function;      /* Codelet function, != NULL */
    எண்ணிக்கை AVTXType  type;          /* Type of codelet transform */
#define TX_TYPE_ANY INT32_MAX     /* Special type to allow all types */

    uint64_t flags;               /* A combination of AVTXFlags and codelet
                                   * flags that describe its properties. */

    முழு factors[TX_MAX_FACTORS];  /* Length factors. MUST be coprime. */
#define TX_FACTOR_ANY -1          /* When used alone, signals that the codelet
                                   * supports all factors. Otherwise, if other
                                   * factors are present, it signals that whatever
                                   * remains will be supported, as long as the
                                   * other factors are a component of the length */

    முழு nb_factors;               /* Minimum number of factors that have to
                                   * be a modulo of the length. Must not be 0. */

    முழு min_len;                  /* Minimum length of transform, must be >= 1 */
    முழு max_len;                  /* Maximum length of transform */
#define TX_LEN_UNLIMITED -1       /* Special length value to permit all lengths */

    முழு (*init)(AVTXContext *s,   /* Optional callback for current context initialization. */
                மாறிலி கட்டமைப்பு FFTXCodelet *cd,
                uint64_t flags,
                FFTXCodeletOptions *opts,
                முழு len, முழு inv,
                மாறிலி வெறுமை *scale);

    முழு (*uninit)(AVTXContext *s); /* Optional callback for uninitialization. */

    முழு cpu_flags;                 /* CPU flags. If any negative flags like
                                    * SLOW are present, will avoid picking.
                                    * 0x0 to signal it's a C codelet */
#define FF_TX_CPU_FLAGS_ALL 0x0    /* Special CPU flag for C */

    முழு prio;                      /* < 0 = least, 0 = no pref, > 0 = prefer */
} FFTXCodelet;

கட்டமைப்பு AVTXContext {
    /* Fields the root transform and subtransforms use or may use.
     * NOTE: This section is used by assembly, do not reorder or change */
    முழு                len;             /* Length of the transform */
    முழு                inv;             /* If transform is inverse */
    முழு               *map;             /* Lookup table(s) */
    TXComplex         *exp;             /* Any non-pre-baked multiplication factors,
                                         * or extra temporary buffer */
    TXComplex         *tmp;             /* Temporary buffer, if needed */

    AVTXContext       *sub;             /* Subtransform context(s), if needed */
    av_tx_fn           fn[TX_MAX_SUB];  /* Function(s) for the subtransforms */
    முழு                nb_sub;          /* Number of subtransforms.
                                         * The reason all of these are set here
                                         * rather than in each separate context
                                         * is to eliminate extra pointer
                                         * dereferences. */

    /* Fields mainly useul/applicable for the root transform or initialization.
     * Fields below are not used by assembly code. */
    மாறிலி FFTXCodelet *cd[TX_MAX_SUB];  /* Subtransform codelets */
    மாறிலி FFTXCodelet *cd_self;         /* Codelet for the current context */
    எண்ணிக்கை AVTXType      type;            /* Type of transform */
    uint64_t           flags;           /* A combination of AVTXFlags and
                                         * codelet flags used when creating */
    FFTXMapDirection   map_dir;         /* Direction of AVTXContext->map */
    தசம              scale_f;
    இரட்டை             scale_d;
    வெறுமை              *opaque;          /* Free to use by implementations */
};

/* This function embeds a Ruritanian PFA input map into an existing lookup table
 * to avoid double permutation. This allows for compound factors to be
 * synthesized as fast PFA FFTs and embedded into either other or standalone
 * transforms.
 * The output CRT map must still be pre-baked into the transform. */
#define TX_EMBED_உள்ளீடு_PFA_MAP(map, tot_len, d1, d2)                             \
    செய் {                                                                         \
        முழு mtmp[(d1)*(d2)];                                                     \
        க்கு (முழு k = 0; k < tot_len; k += (d1)*(d2)) {                           \
            memcpy(mtmp, &map[k], (d1)*(d2)*அளவு(*mtmp));                      \
            க்கு (முழு m = 0; m < (d2); m++)                                       \
                க்கு (முழு n = 0; n < (d1); n++)                                   \
                    map[k + m*(d1) + n] = mtmp[(m*(d1) + n*(d2)) % ((d1)*(d2))]; \
        }                                                                        \
    } போது (0)

/* This function generates a Ruritanian PFA input map into s->map. */
முழு ff_tx_gen_pfa_உள்ளீடு_map(AVTXContext *s, FFTXCodeletOptions *opts,
                            முழு d1, முழு d2);

/* Create a subtransform in the current context with the given parameters.
 * The flags parameter from FFTXCodelet.init() should be preserved as much
 * as that's possible.
 * MUST be called during the sub() callback of each codelet. */
முழு ff_tx_init_subtx(AVTXContext *s, எண்ணிக்கை AVTXType type,
                     uint64_t flags, FFTXCodeletOptions *opts,
                     முழு len, முழு inv, மாறிலி வெறுமை *scale);

/* Clear the context by freeing all tables, maps and subtransforms. */
வெறுமை ff_tx_clear_ctx(AVTXContext *s);

/* Attempt to factorize a length into 2 integers such that
 * len / dst1 == dst2, where dst1 and dst2 are coprime. */
முழு ff_tx_decompose_length(முழு dst[TX_MAX_DECOMPOSITIONS], எண்ணிக்கை AVTXType type,
                           முழு len, முழு inv);

/* Generate a default map (0->len or 0, (len-1)->1 for inverse transforms)
 * for a context. */
முழு ff_tx_gen_default_map(AVTXContext *s, FFTXCodeletOptions *opts);

/*
 * Generates the PFA permutation table into AVTXContext->pfatab. The end table
 * is appended to the start table.
 * The `inv` flag should only be enabled if the lookup tables of subtransforms
 * won't get flattened.
 */
முழு ff_tx_gen_compound_mapping(AVTXContext *s, FFTXCodeletOptions *opts,
                               முழு inv, முழு n, முழு m);

/*
 * Generates a standard-ish (slightly modified) Split-Radix revtab into
 * AVTXContext->map. Invert lookup changes how the mapping needs to be applied.
 * If it's set to 0, it has to be applied like out[map[i]] = in[i], otherwise
 * if it's set to 1, has to be applied as out[i] = in[map[i]]
 */
முழு ff_tx_gen_ptwo_revtab(AVTXContext *s, FFTXCodeletOptions *opts);

/*
 * Generates an index into AVTXContext->inplace_idx that if followed in the
 * specific order, allows the revtab to be done in-place. The sub-transform
 * and its map should already be initialized.
 */
முழு ff_tx_gen_inplace_map(AVTXContext *s, முழு len);

/*
 * This generates a parity-based revtab of length len and direction inv.
 *
 * Parity means even and odd complex numbers will be split, e.g. the even
 * coefficients will come first, after which the odd coefficients will be
 * placed. For example, a 4-point transform's coefficients after reordering:
 * z[0].re, z[0].im, z[2].re, z[2].im, z[1].re, z[1].im, z[3].re, z[3].im
 *
 * The basis argument is the length of the largest non-composite transform
 * supported, and also implies that the basis/2 transform is supported as well,
 * as the split-radix algorithm requires it to be.
 *
 * The dual_stride argument indicates that both the basis, as well as the
 * basis/2 transforms support doing two transforms at once, and the coefficients
 * will be interleaved between each pair in a split-radix like so (stride == 2):
 * tx1[0], tx1[2], tx2[0], tx2[2], tx1[1], tx1[3], tx2[1], tx2[3]
 * A non-zero number switches this on, with the value indicating the stride
 * (how many values of 1 transform to put first before switching to the other).
 * Must be a power of two or 0. Must be less than the basis.
 * Value will be clipped to the transform size, so for a basis of 16 and a
 * dual_stride of 8, dual 8-point transforms will be laid out as if dual_stride
 * was set to 4.
 * Usually you'll set this to half the complex numbers that fit in a single
 * register or 0. This allows to reuse SSE functions as dual-transform
 * functions in AVX mode.
 *
 * If length is smaller than basis/2 this function will not do anything.
 *
 * If inv_lookup is set to 1, it will flip the lookup from out[map[i]] = src[i]
 * to out[i] = src[map[i]].
 */
முழு ff_tx_gen_split_radix_parity_revtab(AVTXContext *s, முழு len, முழு inv,
                                        FFTXCodeletOptions *opts,
                                        முழு basis, முழு dual_stride);

/* Typed init function to initialize shared tables. Will initialize all tables
 * for all factors of a length. */
வெறுமை ff_tx_init_tabs_float (முழு len);
வெறுமை ff_tx_init_tabs_double(முழு len);
வெறுமை ff_tx_init_tabs_int32 (முழு len);

/* Typed init function to initialize an MDCT exptab in a context.
 * If pre_tab is set, duplicates the entire table, with the first
 * copy being shuffled according to pre_tab, and the second copy
 * being the original. */
முழு ff_tx_mdct_gen_exp_float (AVTXContext *s, முழு *pre_tab);
முழு ff_tx_mdct_gen_exp_double(AVTXContext *s, முழு *pre_tab);
முழு ff_tx_mdct_gen_exp_int32 (AVTXContext *s, முழு *pre_tab);

/* Lists of codelets */
வெளி மாறிலி FFTXCodelet * மாறிலி ff_tx_codelet_list_float_c       [];
வெளி மாறிலி FFTXCodelet * மாறிலி ff_tx_codelet_list_float_x86     [];
வெளி மாறிலி FFTXCodelet * மாறிலி ff_tx_codelet_list_float_aarch64 [];

வெளி மாறிலி FFTXCodelet * மாறிலி ff_tx_codelet_list_double_c      [];

வெளி மாறிலி FFTXCodelet * மாறிலி ff_tx_codelet_list_int32_c       [];

#endif /* AVUTIL_TX_PRIV_H */
