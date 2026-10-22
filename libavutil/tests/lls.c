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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/internal.h"
#ضمن "libavutil/lfg.h"
#ضمن "libavutil/lls.h"
#ضمن "libavutil/mem_internal.h"

/* Values below the printed precision are rounding noise whose sign varies
 * between platforms, so print them as zero. */
ساكن مزدوج clean(مزدوج v)
{
    أرجع fabs(v) < 1e-9 ? 0.0 : v;
}

صحيح اصلی(فراغ)
{
    LLSModel m;
    صحيح i, ترتیب;
    AVLFG lfg;

    av_lfg_init(&lfg, 1);
    avpriv_init_lls(&m, 3);

    لكل (i = 0; i < 100; i++) {
        LOCAL_ALIGNED(32, مزدوج, var, [4]);
        مزدوج eval;

        var[0] =         (av_lfg_get(&lfg) / (مزدوج) UINT_MAX - 0.5) * 2;
        var[1] = var[0] + av_lfg_get(&lfg) / (مزدوج) UINT_MAX - 0.5;
        var[2] = var[1] + av_lfg_get(&lfg) / (مزدوج) UINT_MAX - 0.5;
        var[3] = var[2] + av_lfg_get(&lfg) / (مزدوج) UINT_MAX - 0.5;
        m.update_lls(&m, var);
        avpriv_solve_lls(&m, 0.001, 0);
        لكل (ترتیب = 0; ترتیب < 3; ترتیب++) {
            eval = m.evaluate_lls(&m, var + 1, ترتیب);
            چاپ_کن("real:%9f order:%d pred:%9f var:%f coeffs:%f %9f %9f\n",
                   var[0], ترتیب, eval,
                   جذر(FFMAX(m.variance[ترتیب], 0) / (i + 1)),
                   clean(m.coeff[ترتیب][0]), clean(m.coeff[ترتیب][1]),
                   clean(m.coeff[ترتیب][2]));
        }
    }
    أرجع 0;
}
