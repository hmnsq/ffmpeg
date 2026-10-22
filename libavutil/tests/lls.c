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

#شامل <limits.h>
#شامل <stdio.h>

#شامل "libavutil/internal.h"
#شامل "libavutil/lfg.h"
#شامل "libavutil/lls.h"
#شامل "libavutil/mem_internal.h"

/* Values below the printed precision are rounding noise whose sign varies
 * between platforms, so print them as zero. */
ساکن دوہرا clean(دوہرا v)
{
    واپس fabs(v) < 1e-9 ? 0.0 : v;
}

صحیح مین(خالی)
{
    LLSModel m;
    صحیح i, ترتیب;
    AVLFG lfg;

    av_lfg_init(&lfg, 1);
    avpriv_init_lls(&m, 3);

    برائے (i = 0; i < 100; i++) {
        LOCAL_ALIGNED(32, دوہرا, var, [4]);
        دوہرا eval;

        var[0] =         (av_lfg_get(&lfg) / (دوہرا) UINT_MAX - 0.5) * 2;
        var[1] = var[0] + av_lfg_get(&lfg) / (دوہرا) UINT_MAX - 0.5;
        var[2] = var[1] + av_lfg_get(&lfg) / (دوہرا) UINT_MAX - 0.5;
        var[3] = var[2] + av_lfg_get(&lfg) / (دوہرا) UINT_MAX - 0.5;
        m.update_lls(&m, var);
        avpriv_solve_lls(&m, 0.001, 0);
        برائے (ترتیب = 0; ترتیب < 3; ترتیب++) {
            eval = m.evaluate_lls(&m, var + 1, ترتیب);
            لکھو("real:%9f order:%d pred:%9f var:%f coeffs:%f %9f %9f\n",
                   var[0], ترتیب, eval,
                   جذر(FFMAX(m.variance[ترتیب], 0) / (i + 1)),
                   clean(m.coeff[ترتیب][0]), clean(m.coeff[ترتیب][1]),
                   clean(m.coeff[ترتیب][2]));
        }
    }
    واپس 0;
}
