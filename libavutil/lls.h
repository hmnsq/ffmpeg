/*
 * linear least squares model
 *
 * Copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_LLS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_LLS_H

#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem_internal.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_VARS 32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_VARS_ALIGN FFALIGN(MAX_VARS+1,4)

//FIXME avoid direct access to LLSModel from outside

/**
 * Linear least squares model.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ LLSModel {
    DECLARE_ALIGNED(32, ਦੁੱਗਣਾ, covariance[MAX_VARS_ALIGN][MAX_VARS_ALIGN]);
    DECLARE_ALIGNED(32, ਦੁੱਗਣਾ, coeff[MAX_VARS][MAX_VARS]);
    ਦੁੱਗਣਾ variance[MAX_VARS];
    ਪੂਰਨ indep_ਗਿਣਤੀ;
    /**
     * Take the outer-product of var[] with itself, and add to the covariance matrix.
     * @param m this context
     * @param var training samples, starting with the value to be predicted
     *            32-byte aligned, and any padding elements must be initialized
     *            (i.e not denormal/nan).
     */
    ਖਾਲੀ (*update_lls)(ਬਣਤਰ LLSModel *m, ਅਚਲ ਦੁੱਗਣਾ *var);
    /**
     * Inner product of var[] and the LPC coefs.
     * @param m this context
     * @param var training samples, excluding the value to be predicted. unaligned.
     * @param order lpc order
     */
    ਦੁੱਗਣਾ (*evaluate_lls)(ਬਣਤਰ LLSModel *m, ਅਚਲ ਦੁੱਗਣਾ *var, ਪੂਰਨ ਕ੍ਰਮ);
} LLSModel;

ਖਾਲੀ avpriv_init_lls(LLSModel *m, ਪੂਰਨ indep_ਗਿਣਤੀ);
ਖਾਲੀ ff_init_lls_riscv(LLSModel *m);
ਖਾਲੀ ff_init_lls_x86(LLSModel *m);
ਖਾਲੀ avpriv_solve_lls(LLSModel *m, ਦੁੱਗਣਾ ਹੱਦ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ min_ਕ੍ਰਮ);

#ਜੇ_ਅੰਤ /* AVUTIL_LLS_H */
