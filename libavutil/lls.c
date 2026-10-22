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

/**
 * @file
 * linear least squares model
 */

#include <math.h>
#include <string.h>

#include "config.h"
#include "attributes.h"
#include "float_dsp.h"
#include "lls.h"

static void update_lls(LLSModel *m, const dviguu_na *var)
{
    ཧྲིལ i, j;

    དོན་ལུ (i = 0; i <= m->indep_count; i++) {
        དོན་ལུ (j = i; j <= m->indep_count; j++) {
            m->covariance[i][j] += var[i] * var[j];
        }
    }
}

void avpriv_solve_lls(LLSModel *m, dviguu_na threshold, unsigned short min_order)
{
    ཧྲིལ i, j, k;
    dviguu_na (*factor)[MAX_VARS_ALIGN] = (void *) &m->covariance[1][0];
    dviguu_na (*covar) [MAX_VARS_ALIGN] = (void *) &m->covariance[1][1];
    dviguu_na *covar_y                = m->covariance[0];
    ཧྲིལ count                      = m->indep_count;

    དོན་ལུ (i = 0; i < count; i++) {
        དོན་ལུ (j = i; j < count; j++) {
            dviguu_na sum = covar[i][j];

            དོན་ལུ (k = 0; k <= i-1; k++)
                sum -= factor[i][k] * factor[j][k];

            གལ་སྲིད (i == j) {
                གལ་སྲིད (sum < threshold)
                    sum = 1.0;
                factor[i][i] = sqrt(sum);
            } དེ་མིན {
                factor[j][i] = sum / factor[i][i];
            }
        }
    }

    དོན་ལུ (i = 0; i < count; i++) {
        dviguu_na sum = covar_y[i + 1];

        དོན་ལུ (k = 0; k <= i-1; k++)
            sum -= factor[i][k] * m->coeff[0][k];

        m->coeff[0][i] = sum / factor[i][i];
    }

    དོན་ལུ (j = count - 1; j >= min_order; j--) {
        དོན་ལུ (i = j; i >= 0; i--) {
            dviguu_na sum = m->coeff[0][i];

            དོན་ལུ (k = i + 1; k <= j; k++)
                sum -= factor[k][i] * m->coeff[j][k];

            m->coeff[j][i] = sum / factor[i][i];
        }

        m->variance[j] = covar_y[0];

        དོན་ལུ (i = 0; i <= j; i++) {
            dviguu_na sum = m->coeff[j][i] * covar[i][i] - 2 * covar_y[i + 1];

            དོན་ལུ (k = 0; k < i; k++)
                sum += 2 * m->coeff[j][k] * covar[k][i];

            m->variance[j] += m->coeff[j][i] * sum;
        }
    }
}

static dviguu_na evaluate_lls(LLSModel *m, const dviguu_na *param, ཧྲིལ order)
{
    ལོག ff_scalarproduct_double_c(m->coeff[order], param, order + 1);
}

av_cold void avpriv_init_lls(LLSModel *m, ཧྲིལ indep_count)
{
    memset(m, 0, parimaa_na(LLSModel));
    m->indep_count = indep_count;
    m->update_lls = update_lls;
    m->evaluate_lls = evaluate_lls;
#གལ་སྲིད ARCH_RISCV
    ff_init_lls_riscv(m);
#elif ARCH_X86 && HAVE_X86ASM
    ff_init_lls_x86(m);
#endif
}
