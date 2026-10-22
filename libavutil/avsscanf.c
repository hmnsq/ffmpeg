/*
 * Copyright (c) 2005-2014 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#అన్తర్భావ <errno.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <float.h>

#అన్తర్భావ "avstring.h"

రకనిర్వచనం నిర్మాణం FFFILE {
    size_t buf_కొలత;
    గుర్తులేని అక్షరం *buf;
    గుర్తులేని అక్షరం *rpos, *rend;
    గుర్తులేని అక్షరం *shend;
    ptrdiff_t shlim, shcnt;
    శూన్య *cookie;
    size_t (*పఠ)(నిర్మాణం FFFILE *, గుర్తులేని అక్షరం *, size_t);
} FFFILE;

#నిర్వచించు కొలత_hh -2
#నిర్వచించు కొలత_h  -1
#నిర్వచించు కొలత_def 0
#నిర్వచించు కొలత_l   1
#నిర్వచించు కొలత_L   2
#నిర్వచించు కొలత_ll  3

#నిర్వచించు shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

స్థిర పూర్ణాంకం fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_కొలత;
    తిరిగి 0;
}

స్థిర size_t ffstring_read(FFFILE *f, గుర్తులేని అక్షరం *buf, size_t len)
{
    అక్షరం *src = f->cookie;
    size_t k = len+256;
    అక్షరం *చివర = memchr(src, 0, k);

    ఒకవేళ (చివర) k = చివర-src;
    ఒకవేళ (k < len) len = k;
    జ్ఞాపకం_నకలు(buf, src, len);
    f->rpos = (శూన్య *)(src+len);
    f->rend = (శూన్య *)(src+k);
    f->cookie = src+k;

    తిరిగి len;
}

స్థిర పూర్ణాంకం ffuflow(FFFILE *f)
{
    గుర్తులేని అక్షరం c;
    ఒకవేళ (!fftoread(f) && f->పఠ(f, &c, 1)==1) తిరిగి c;
    తిరిగి EOF;
}

స్థిర శూన్య ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ఒకవేళ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    లేకపోతే
        f->shend = f->rend;
}

స్థిర పూర్ణాంకం ffshgetc(FFFILE *f)
{
    పూర్ణాంకం c;
    ptrdiff_t cnt = shcnt(f);
    ఒకవేళ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        తిరిగి EOF;
    }
    cnt++;
    ఒకవేళ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    లేకపోతే
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ఒకవేళ (f->rpos[-1] != c) f->rpos[-1] = c;
    తిరిగి c;
}

#నిర్వచించు shlim(f, lim) ffshlim((f), (lim))
#నిర్వచించు shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#నిర్వచించు shunget(f) ((f)->shend ? (శూన్య)(f)->rpos-- : (శూన్య)0)

స్థిర స్థిరరాశి గుర్తులేని అక్షరం పట్టిక[] = { -1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,
    -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
    25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,
    -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
    25,26,27,28,29,30,31,32,33,34,35,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

స్థిర గుర్తులేని దీర్ఘ దీర్ఘ ffintscan(FFFILE *f, గుర్తులేని పునాది_2, పూర్ణాంకం pok, గుర్తులేని దీర్ఘ దీర్ఘ lim)
{
    స్థిరరాశి గుర్తులేని అక్షరం *val = పట్టిక+1;
    పూర్ణాంకం c, neg=0;
    గుర్తులేని x;
    గుర్తులేని దీర్ఘ దీర్ఘ y;
    ఒకవేళ (పునాది_2 > 36 || పునాది_2 == 1) {
        errno = EINVAL;
        తిరిగి 0;
    }
    అయితే (av_isspace((c=shgetc(f))));
    ఒకవేళ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ఒకవేళ ((పునాది_2 == 0 || పునాది_2 == 16) && c=='0') {
        c = shgetc(f);
        ఒకవేళ ((c|32)=='x') {
            c = shgetc(f);
            ఒకవేళ (val[c]>=16) {
                shunget(f);
                ఒకవేళ (pok) shunget(f);
                లేకపోతే shlim(f, 0);
                తిరిగి 0;
            }
            పునాది_2 = 16;
        } లేకపోతే ఒకవేళ (పునాది_2 == 0) {
            పునాది_2 = 8;
        }
    } లేకపోతే {
        ఒకవేళ (పునాది_2 == 0) పునాది_2 = 10;
        ఒకవేళ (val[c] >= పునాది_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            తిరిగి 0;
        }
    }
    ఒకవేళ (పునాది_2 == 10) {
        కొరకు (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        కొరకు (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ఒకవేళ (c-'0'>=10U) వెళ్ళు పూర్తి;
    } లేకపోతే ఒకవేళ (!(పునాది_2 & పునాది_2-1)) {
        పూర్ణాంకం bs = "\0\1\2\4\7\3\6\5"[(0x17*పునాది_2)>>5&7];
        కొరకు (x=0; val[c]<పునాది_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        కొరకు (y=x; val[c]<పునాది_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } లేకపోతే {
        కొరకు (x=0; val[c]<పునాది_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*పునాది_2 + val[c];
        కొరకు (y=x; val[c]<పునాది_2 && y<=ULLONG_MAX/పునాది_2 && పునాది_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*పునాది_2 + val[c];
    }
    ఒకవేళ (val[c]<పునాది_2) {
        కొరకు (; val[c]<పునాది_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ఒకవేళ (lim&1) neg = 0;
    }
పూర్తి:
    shunget(f);
    ఒకవేళ (y>=lim) {
        ఒకవేళ (!(lim&1) && !neg) {
            errno = ERANGE;
            తిరిగి lim-1;
        } లేకపోతే ఒకవేళ (y>lim) {
            errno = ERANGE;
            తిరిగి lim;
        }
    }
    తిరిగి (y^neg)-neg;
}

స్థిర దీర్ఘ దీర్ఘ scanexp(FFFILE *f, పూర్ణాంకం pok)
{
    పూర్ణాంకం c;
    పూర్ణాంకం x;
    దీర్ఘ దీర్ఘ y;
    పూర్ణాంకం neg = 0;

    c = shgetc(f);
    ఒకవేళ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ఒకవేళ (c-'0'>=10U && pok) shunget(f);
    }
    ఒకవేళ (c-'0'>=10U) {
        shunget(f);
        తిరిగి LLONG_MIN;
    }
    కొరకు (x=0; c-'0'<10U && x<గరిష్ఠ_పూర్ణాంకం/10; c = shgetc(f))
        x = 10*x + (c-'0');
    కొరకు (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    కొరకు (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    తిరిగి neg ? -y : y;
}

#నిర్వచించు LD_B1B_DIG 2
#నిర్వచించు LD_B1B_MAX 9007199, 254740991
#నిర్వచించు KMAX 128
#నిర్వచించు ముసుగు (KMAX-1)

స్థిర ద్విగుణ decfloat(FFFILE *f, పూర్ణాంకం c, పూర్ణాంకం బిట్లు, పూర్ణాంకం emin, పూర్ణాంకం sign, పూర్ణాంకం pok)
{
    uint32_t x[KMAX];
    స్థిర స్థిరరాశి uint32_t th[] = { LD_B1B_MAX };
    పూర్ణాంకం i, j, k, a, z;
    దీర్ఘ దీర్ఘ lrp=0, dc=0;
    దీర్ఘ దీర్ఘ e10=0;
    పూర్ణాంకం lnz = 0;
    పూర్ణాంకం gotdig = 0, gotrad = 0;
    పూర్ణాంకం rp;
    పూర్ణాంకం e2;
    పూర్ణాంకం emax = -emin-బిట్లు+3;
    పూర్ణాంకం denormal = 0;
    ద్విగుణ y;
    ద్విగుణ frac=0;
    ద్విగుణ bias=0;
    స్థిర స్థిరరాశి పూర్ణాంకం p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    కొరకు (; c=='0'; c = shgetc(f)) gotdig=1;
    ఒకవేళ (c=='.') {
        gotrad = 1;
        కొరకు (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    కొరకు (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ఒకవేళ (c == '.') {
            ఒకవేళ (gotrad) ఆపు;
            gotrad = 1;
            lrp = dc;
        } లేకపోతే ఒకవేళ (k < KMAX-3) {
            dc++;
            ఒకవేళ (c!='0') lnz = dc;
            ఒకవేళ (j) x[k] = x[k]*10 + c-'0';
            లేకపోతే x[k] = c-'0';
            ఒకవేళ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } లేకపోతే {
            dc++;
            ఒకవేళ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ఒకవేళ (!gotrad) lrp=dc;

    ఒకవేళ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ఒకవేళ (e10 == LLONG_MIN) {
            ఒకవేళ (pok) {
                shunget(f);
            } లేకపోతే {
                shlim(f, 0);
                తిరిగి 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } లేకపోతే ఒకవేళ (c>=0) {
        shunget(f);
    }
    ఒకవేళ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        తిరిగి 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ఒకవేళ (!x[0]) తిరిగి sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ఒకవేళ (lrp==dc && dc<10 && (బిట్లు>30 || x[0]>>బిట్లు==0))
        తిరిగి sign * (ద్విగుణ)x[0];
    ఒకవేళ (lrp > -emin/2) {
        errno = ERANGE;
        తిరిగి sign * DBL_MAX * DBL_MAX;
    }
    ఒకవేళ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        తిరిగి sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ఒకవేళ (j) {
        కొరకు (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ఒకవేళ (lnz<9 && lnz<=rp && rp < 18) {
        పూర్ణాంకం bitlim;
        ఒకవేళ (rp == 9) తిరిగి sign * (ద్విగుణ)x[0];
        ఒకవేళ (rp < 9) తిరిగి sign * (ద్విగుణ)x[0] / p10s[8-rp];
        bitlim = బిట్లు-3*(పూర్ణాంకం)(rp-9);
        ఒకవేళ (bitlim>30 || x[0]>>bitlim==0)
            తిరిగి sign * (ద్విగుణ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    కొరకు (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ఒకవేళ (rp % 9) {
        పూర్ణాంకం rpm9 = rp>=0 ? rp%9 : rp%9+9;
        పూర్ణాంకం p10 = p10s[8-rpm9];
        uint32_t వాహకం = 0;
        కొరకు (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + వాహకం;
            వాహకం = 1000000000/p10 * tmp;
            ఒకవేళ (k==a && !x[k]) {
                a = (a+1 & ముసుగు);
                rp -= 9;
            }
        }
        ఒకవేళ (వాహకం) x[z++] = వాహకం;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    అయితే (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t వాహకం = 0;
        e2 -= 29;
        కొరకు (k=(z-1 & ముసుగు); ; k=(k-1 & ముసుగు)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + వాహకం;
            ఒకవేళ (tmp > 1000000000) {
                వాహకం = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } లేకపోతే {
                వాహకం = 0;
                x[k] = tmp;
            }
            ఒకవేళ (k==(z-1 & ముసుగు) && k!=a && !x[k]) z = k;
            ఒకవేళ (k==a) ఆపు;
        }
        ఒకవేళ (వాహకం) {
            rp += 9;
            a = (a-1 & ముసుగు);
            ఒకవేళ (a == z) {
                z = (z-1 & ముసుగు);
                x[z-1 & ముసుగు] |= x[z];
            }
            x[a] = వాహకం;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    కొరకు (;;) {
        uint32_t వాహకం = 0;
        పూర్ణాంకం sh = 1;
        కొరకు (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & ముసుగు);
            ఒకవేళ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                ఆపు;
            }
            ఒకవేళ (x[a+i & ముసుగు] > th[i]) ఆపు;
        }
        ఒకవేళ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) ఆపు;
        /* FIXME: find a way to compute optimal sh */
        ఒకవేళ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        కొరకు (k=a; k!=z; k=(k+1 & ముసుగు)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + వాహకం;
            వాహకం = (1000000000>>sh) * tmp;
            ఒకవేళ (k==a && !x[k]) {
                a = (a+1 & ముసుగు);
                i--;
                rp -= 9;
            }
        }
        ఒకవేళ (వాహకం) {
            ఒకవేళ ((z+1 & ముసుగు) != a) {
                x[z] = వాహకం;
                z = (z+1 & ముసుగు);
            } లేకపోతే x[z-1 & ముసుగు] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    కొరకు (y=i=0; i<LD_B1B_DIG; i++) {
        ఒకవేళ ((a+i & ముసుగు)==z) x[(z=(z+1 & ముసుగు))-1 & ముసుగు] = 0;
        y = 1000000000.0L * y + x[a+i & ముసుగు];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ఒకవేళ (బిట్లు > DBL_MANT_DIG+e2-emin) {
        బిట్లు = DBL_MANT_DIG+e2-emin;
        ఒకవేళ (బిట్లు<0) బిట్లు=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ఒకవేళ (బిట్లు < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-బిట్లు-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-బిట్లు));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ఒకవేళ ((a+i & ముసుగు) != z) {
        uint32_t t = x[a+i & ముసుగు];
        ఒకవేళ (t < 500000000 && (t || (a+i+1 & ముసుగు) != z))
            frac += 0.25*sign;
        లేకపోతే ఒకవేళ (t > 500000000)
            frac += 0.75*sign;
        లేకపోతే ఒకవేళ (t == 500000000) {
            ఒకవేళ ((a+i+1 & ముసుగు) == z)
                frac += 0.5*sign;
            లేకపోతే
                frac += 0.75*sign;
        }
        ఒకవేళ (DBL_MANT_DIG-బిట్లు >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ఒకవేళ ((e2+DBL_MANT_DIG & గరిష్ఠ_పూర్ణాంకం) > emax-5) {
        ఒకవేళ (fabs(y) >= ఘాతం(2, DBL_MANT_DIG)) {
            ఒకవేళ (denormal && బిట్లు==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ఒకవేళ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    తిరిగి scalbn(y, e2);
}

స్థిర ద్విగుణ hexfloat(FFFILE *f, పూర్ణాంకం బిట్లు, పూర్ణాంకం emin, పూర్ణాంకం sign, పూర్ణాంకం pok)
{
    uint32_t x = 0;
    ద్విగుణ y = 0;
    ద్విగుణ scale = 1;
    ద్విగుణ bias = 0;
    పూర్ణాంకం gottail = 0, gotrad = 0, gotdig = 0;
    దీర్ఘ దీర్ఘ rp = 0;
    దీర్ఘ దీర్ఘ dc = 0;
    దీర్ఘ దీర్ఘ e2 = 0;
    పూర్ణాంకం d;
    పూర్ణాంకం c;

    c = shgetc(f);

    /* Skip leading zeros */
    కొరకు (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ఒకవేళ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        కొరకు (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    కొరకు (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ఒకవేళ (c=='.') {
            ఒకవేళ (gotrad) ఆపు;
            rp = dc;
            gotrad = 1;
        } లేకపోతే {
            gotdig = 1;
            ఒకవేళ (c > '9') d = (c|32)+10-'a';
            లేకపోతే d = c-'0';
            ఒకవేళ (dc<8) {
                x = x*16 + d;
            } లేకపోతే ఒకవేళ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } లేకపోతే ఒకవేళ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ఒకవేళ (!gotdig) {
        shunget(f);
        ఒకవేళ (pok) {
            shunget(f);
            ఒకవేళ (gotrad) shunget(f);
        } లేకపోతే {
            shlim(f, 0);
        }
        తిరిగి sign * 0.0;
    }
    ఒకవేళ (!gotrad) rp = dc;
    అయితే (dc<8) x *= 16, dc++;
    ఒకవేళ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ఒకవేళ (e2 == LLONG_MIN) {
            ఒకవేళ (pok) {
                shunget(f);
            } లేకపోతే {
                shlim(f, 0);
                తిరిగి 0;
            }
            e2 = 0;
        }
    } లేకపోతే {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ఒకవేళ (!x) తిరిగి sign * 0.0;
    ఒకవేళ (e2 > -emin) {
        errno = ERANGE;
        తిరిగి sign * DBL_MAX * DBL_MAX;
    }
    ఒకవేళ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        తిరిగి sign * DBL_MIN * DBL_MIN;
    }

    అయితే (x < 0x80000000) {
        ఒకవేళ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } లేకపోతే {
            x += x;
            y += y;
        }
        e2--;
    }

    ఒకవేళ (బిట్లు > 32+e2-emin) {
        బిట్లు = 32+e2-emin;
        ఒకవేళ (బిట్లు<0) బిట్లు=0;
    }

    ఒకవేళ (బిట్లు < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-బిట్లు-1), sign);

    ఒకవేళ (బిట్లు<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ద్విగుణ)x + sign*y;
    y -= bias;

    ఒకవేళ (!y) errno = ERANGE;

    తిరిగి scalbn(y, e2);
}

స్థిర ద్విగుణ fffloatscan(FFFILE *f, పూర్ణాంకం prec, పూర్ణాంకం pok)
{
    పూర్ణాంకం sign = 1;
    size_t i;
    పూర్ణాంకం బిట్లు;
    పూర్ణాంకం emin;
    పూర్ణాంకం c;

    ఎంపిక (prec) {
    స్థితి 0:
        బిట్లు = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-బిట్లు;
        ఆపు;
    స్థితి 1:
        బిట్లు = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-బిట్లు;
        ఆపు;
    స్థితి 2:
        బిట్లు = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-బిట్లు;
        ఆపు;
    అప్రమేయ:
        తిరిగి 0;
    }

    అయితే (av_isspace((c = shgetc(f))));

    ఒకవేళ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    కొరకు (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ఒకవేళ (i<7) c = shgetc(f);
    ఒకవేళ (i==3 || i==8 || (i>3 && pok)) {
        ఒకవేళ (i!=8) {
            shunget(f);
            ఒకవేళ (pok) కొరకు (; i>3; i--) shunget(f);
        }
        తిరిగి sign * INFINITY;
    }
    ఒకవేళ (!i) కొరకు (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ఒకవేళ (i<2) c = shgetc(f);
    ఒకవేళ (i==3) {
        ఒకవేళ (shgetc(f) != '(') {
            shunget(f);
            తిరిగి NAN;
        }
        కొరకు (i=1; ; i++) {
            c = shgetc(f);
            ఒకవేళ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                కొనసాగు;
            ఒకవేళ (c==')') తిరిగి NAN;
            shunget(f);
            ఒకవేళ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                తిరిగి 0;
            }
            అయితే (i--) shunget(f);
            తిరిగి NAN;
        }
    }

    ఒకవేళ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        తిరిగి 0;
    }

    ఒకవేళ (c=='0') {
        c = shgetc(f);
        ఒకవేళ ((c|32) == 'x')
            తిరిగి hexfloat(f, బిట్లు, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    తిరిగి decfloat(f, c, బిట్లు, emin, sign, pok);
}

స్థిర శూన్య *arg_n(va_list ap, గుర్తులేని పూర్ణాంకం n)
{
    శూన్య *p;
    గుర్తులేని పూర్ణాంకం i;
    va_list ap2;
    va_copy(ap2, ap);
    కొరకు (i=n; i>1; i--) va_arg(ap2, శూన్య *);
    p = va_arg(ap2, శూన్య *);
    va_end(ap2);
    తిరిగి p;
}

స్థిర శూన్య store_int(శూన్య *dest, పూర్ణాంకం కొలత, గుర్తులేని దీర్ఘ దీర్ఘ i)
{
    ఒకవేళ (!dest) తిరిగి;
    ఎంపిక (కొలత) {
    స్థితి కొలత_hh:
        *(అక్షరం *)dest = i;
        ఆపు;
    స్థితి కొలత_h:
        *(పొట్టి *)dest = i;
        ఆపు;
    స్థితి కొలత_def:
        *(పూర్ణాంకం *)dest = i;
        ఆపు;
    స్థితి కొలత_l:
        *(దీర్ఘ *)dest = i;
        ఆపు;
    స్థితి కొలత_ll:
        *(దీర్ఘ దీర్ఘ *)dest = i;
        ఆపు;
    }
}

స్థిర పూర్ణాంకం ff_vfscanf(FFFILE *f, స్థిరరాశి అక్షరం *fmt, va_list ap)
{
    పూర్ణాంకం వెడల్పు;
    పూర్ణాంకం కొలత;
    పూర్ణాంకం పునాది_2;
    స్థిరరాశి గుర్తులేని అక్షరం *p;
    పూర్ణాంకం c, t;
    అక్షరం *s;
    శూన్య *dest=ఖాళీ;
    పూర్ణాంకం invert;
    పూర్ణాంకం matches=0;
    గుర్తులేని దీర్ఘ దీర్ఘ x;
    ద్విగుణ y;
    ptrdiff_t pos = 0;
    గుర్తులేని అక్షరం scanset[257];
    size_t i;

    కొరకు (p=(స్థిరరాశి గుర్తులేని అక్షరం *)fmt; *p; p++) {

        ఒకవేళ (av_isspace(*p)) {
            అయితే (av_isspace(p[1])) p++;
            shlim(f, 0);
            అయితే (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            కొనసాగు;
        }
        ఒకవేళ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ఒకవేళ (*p == '%') {
                p++;
                అయితే (av_isspace((c=shgetc(f))));
            } లేకపోతే {
                c = shgetc(f);
            }
            ఒకవేళ (c!=*p) {
                shunget(f);
                ఒకవేళ (c<0) వెళ్ళు ఆదానం_fail;
                వెళ్ళు సరిపోలిక_fail;
            }
            pos += shcnt(f);
            కొనసాగు;
        }

        p++;
        ఒకవేళ (*p=='*') {
            dest = 0; p++;
        } లేకపోతే ఒకవేళ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } లేకపోతే {
            dest = va_arg(ap, శూన్య *);
        }

        కొరకు (వెడల్పు=0; av_isdigit(*p); p++) {
            వెడల్పు = 10*వెడల్పు + *p - '0';
        }

        ఒకవేళ (*p=='m') {
            s = 0;
            p++;
        }

        కొలత = కొలత_def;
        ఎంపిక (*p++) {
        స్థితి 'h':
            ఒకవేళ (*p == 'h') p++, కొలత = కొలత_hh;
            లేకపోతే కొలత = కొలత_h;
            ఆపు;
        స్థితి 'l':
            ఒకవేళ (*p == 'l') p++, కొలత = కొలత_ll;
            లేకపోతే కొలత = కొలత_l;
            ఆపు;
        స్థితి 'j':
            కొలత = కొలత_ll;
            ఆపు;
        స్థితి 'z':
        స్థితి 't':
            కొలత = కొలత_l;
            ఆపు;
        స్థితి 'L':
            కొలత = కొలత_L;
            ఆపు;
        స్థితి 'd': స్థితి 'i': స్థితి 'o': స్థితి 'u': స్థితి 'x':
        స్థితి 'a': స్థితి 'e': స్థితి 'f': స్థితి 'g':
        స్థితి 'A': స్థితి 'E': స్థితి 'F': స్థితి 'G': స్థితి 'X':
        స్థితి 's': స్థితి 'c': స్థితి '[':
        స్థితి 'S': స్థితి 'C':
        స్థితి 'p': స్థితి 'n':
            p--;
            ఆపు;
        అప్రమేయ:
            వెళ్ళు fmt_fail;
        }

        t = *p;

        /* C or S */
        ఒకవేళ ((t&0x2f) == 3) {
            t |= 32;
            కొలత = కొలత_l;
        }

        ఎంపిక (t) {
            స్థితి 'c':
                ఒకవేళ (వెడల్పు < 1) వెడల్పు = 1;
                ఆపు;
            స్థితి '[':
                ఆపు;
            స్థితి 'n':
                store_int(dest, కొలత, pos);
                /* do not increment match count, etc! */
                కొనసాగు;
            అప్రమేయ:
                shlim(f, 0);
                అయితే (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, వెడల్పు);
        ఒకవేళ (shgetc(f) < 0) వెళ్ళు ఆదానం_fail;
        shunget(f);

        ఎంపిక (t) {
            స్థితి 's':
            స్థితి 'c':
            స్థితి '[':
                ఒకవేళ (t == 'c' || t == 's') {
                    memset(scanset, -1, పరిమాణం scanset);
                    scanset[0] = 0;
                    ఒకవేళ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } లేకపోతే {
                    ఒకవేళ (*++p == '^') p++, invert = 1;
                    లేకపోతే invert = 0;
                    memset(scanset, invert, పరిమాణం scanset);
                    scanset[0] = 0;
                    ఒకవేళ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    లేకపోతే ఒకవేళ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    కొరకు (; *p != ']'; p++) {
                        ఒకవేళ (!*p) వెళ్ళు fmt_fail;
                        ఒకవేళ (*p=='-' && p[1] && p[1] != ']')
                            కొరకు (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ఒకవేళ ((s = dest)) {
                    అయితే (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } లేకపోతే {
                    అయితే (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ఒకవేళ (!shcnt(f)) వెళ్ళు సరిపోలిక_fail;
                ఒకవేళ (t == 'c' && shcnt(f) != వెడల్పు) వెళ్ళు సరిపోలిక_fail;
                ఒకవేళ (t != 'c') {
                    ఒకవేళ (s) s[i] = 0;
                }
                ఆపు;
            స్థితి 'p':
            స్థితి 'X':
            స్థితి 'x':
                పునాది_2 = 16;
                వెళ్ళు int_common;
            స్థితి 'o':
                పునాది_2 = 8;
                వెళ్ళు int_common;
            స్థితి 'd':
            స్థితి 'u':
                పునాది_2 = 10;
                వెళ్ళు int_common;
            స్థితి 'i':
                పునాది_2 = 0;
int_common:
                x = ffintscan(f, పునాది_2, 0, ULLONG_MAX);
                ఒకవేళ (!shcnt(f))
                    వెళ్ళు సరిపోలిక_fail;
                ఒకవేళ (t=='p' && dest)
                    *(శూన్య **)dest = (శూన్య *)(uintptr_t)x;
                లేకపోతే
                    store_int(dest, కొలత, x);
                ఆపు;
            స్థితి 'a': స్థితి 'A':
            స్థితి 'e': స్థితి 'E':
            స్థితి 'f': స్థితి 'F':
            స్థితి 'g': స్థితి 'G':
                y = fffloatscan(f, కొలత, 0);
                ఒకవేళ (!shcnt(f))
                    వెళ్ళు సరిపోలిక_fail;
                ఒకవేళ (dest) {
                    ఎంపిక (కొలత) {
                    స్థితి కొలత_def:
                        *(దశాంశం *)dest = y;
                        ఆపు;
                    స్థితి కొలత_l:
                        *(ద్విగుణ *)dest = y;
                        ఆపు;
                    స్థితి కొలత_L:
                        *(ద్విగుణ *)dest = y;
                        ఆపు;
                    }
                }
                ఆపు;
        }

        pos += shcnt(f);
        ఒకవేళ (dest) matches++;
    }
    ఒకవేళ (0) {
fmt_fail:
ఆదానం_fail:
        ఒకవేళ (!matches) matches--;
    }
సరిపోలిక_fail:
    తిరిగి matches;
}

స్థిర పూర్ణాంకం ff_vsscanf(స్థిరరాశి అక్షరం *s, స్థిరరాశి అక్షరం *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (శూన్య *)s, .cookie = (శూన్య *)s,
        .పఠ = ffstring_read,
    };

    తిరిగి ff_vfscanf(&f, fmt, ap);
}

పూర్ణాంకం av_sscanf(స్థిరరాశి అక్షరం *string, స్థిరరాశి అక్షరం *format, ...)
{
    పూర్ణాంకం ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    తిరిగి ret;
}
