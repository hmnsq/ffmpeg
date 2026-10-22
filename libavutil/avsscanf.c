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

#شامل <errno.h>
#شامل <limits.h>
#شامل <math.h>
#شامل <stdarg.h>
#شامل <stddef.h>
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <float.h>

#شامل "avstring.h"

قسمتعریف ساخت FFFILE {
    size_t buf_سائز;
    غیرعلامتی حرف *buf;
    غیرعلامتی حرف *rpos, *rend;
    غیرعلامتی حرف *shend;
    ptrdiff_t shlim, shcnt;
    خالی *cookie;
    size_t (*اقرأ)(ساخت FFFILE *, غیرعلامتی حرف *, size_t);
} FFFILE;

#تعریف_کرو سائز_hh -2
#تعریف_کرو سائز_h  -1
#تعریف_کرو سائز_def 0
#تعریف_کرو سائز_l   1
#تعریف_کرو سائز_L   2
#تعریف_کرو سائز_ll  3

#تعریف_کرو shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ساکن صحیح fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_سائز;
    واپس 0;
}

ساکن size_t ffstring_read(FFFILE *f, غیرعلامتی حرف *buf, size_t len)
{
    حرف *src = f->cookie;
    size_t k = len+256;
    حرف *انتہا = memchr(src, 0, k);

    اگر (انتہا) k = انتہا-src;
    اگر (k < len) len = k;
    حافظہ_نقل(buf, src, len);
    f->rpos = (خالی *)(src+len);
    f->rend = (خالی *)(src+k);
    f->cookie = src+k;

    واپس len;
}

ساکن صحیح ffuflow(FFFILE *f)
{
    غیرعلامتی حرف c;
    اگر (!fftoread(f) && f->اقرأ(f, &c, 1)==1) واپس c;
    واپس EOF;
}

ساکن خالی ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    اگر (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ورنہ
        f->shend = f->rend;
}

ساکن صحیح ffshgetc(FFFILE *f)
{
    صحیح c;
    ptrdiff_t cnt = shcnt(f);
    اگر (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        واپس EOF;
    }
    cnt++;
    اگر (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ورنہ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    اگر (f->rpos[-1] != c) f->rpos[-1] = c;
    واپس c;
}

#تعریف_کرو shlim(f, lim) ffshlim((f), (lim))
#تعریف_کرو shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#تعریف_کرو shunget(f) ((f)->shend ? (خالی)(f)->rpos-- : (خالی)0)

ساکن ثابت غیرعلامتی حرف جدول[] = { -1,
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

ساکن غیرعلامتی طویل طویل ffintscan(FFFILE *f, غیرعلامتی بنیاد_2, صحیح pok, غیرعلامتی طویل طویل lim)
{
    ثابت غیرعلامتی حرف *val = جدول+1;
    صحیح c, neg=0;
    غیرعلامتی x;
    غیرعلامتی طویل طویل y;
    اگر (بنیاد_2 > 36 || بنیاد_2 == 1) {
        errno = EINVAL;
        واپس 0;
    }
    جب (av_isspace((c=shgetc(f))));
    اگر (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    اگر ((بنیاد_2 == 0 || بنیاد_2 == 16) && c=='0') {
        c = shgetc(f);
        اگر ((c|32)=='x') {
            c = shgetc(f);
            اگر (val[c]>=16) {
                shunget(f);
                اگر (pok) shunget(f);
                ورنہ shlim(f, 0);
                واپس 0;
            }
            بنیاد_2 = 16;
        } ورنہ اگر (بنیاد_2 == 0) {
            بنیاد_2 = 8;
        }
    } ورنہ {
        اگر (بنیاد_2 == 0) بنیاد_2 = 10;
        اگر (val[c] >= بنیاد_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            واپس 0;
        }
    }
    اگر (بنیاد_2 == 10) {
        برائے (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        برائے (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        اگر (c-'0'>=10U) جاؤ مکمل;
    } ورنہ اگر (!(بنیاد_2 & بنیاد_2-1)) {
        صحیح bs = "\0\1\2\4\7\3\6\5"[(0x17*بنیاد_2)>>5&7];
        برائے (x=0; val[c]<بنیاد_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        برائے (y=x; val[c]<بنیاد_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ورنہ {
        برائے (x=0; val[c]<بنیاد_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*بنیاد_2 + val[c];
        برائے (y=x; val[c]<بنیاد_2 && y<=ULLONG_MAX/بنیاد_2 && بنیاد_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*بنیاد_2 + val[c];
    }
    اگر (val[c]<بنیاد_2) {
        برائے (; val[c]<بنیاد_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        اگر (lim&1) neg = 0;
    }
مکمل:
    shunget(f);
    اگر (y>=lim) {
        اگر (!(lim&1) && !neg) {
            errno = ERANGE;
            واپس lim-1;
        } ورنہ اگر (y>lim) {
            errno = ERANGE;
            واپس lim;
        }
    }
    واپس (y^neg)-neg;
}

ساکن طویل طویل scanexp(FFFILE *f, صحیح pok)
{
    صحیح c;
    صحیح x;
    طویل طویل y;
    صحیح neg = 0;

    c = shgetc(f);
    اگر (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        اگر (c-'0'>=10U && pok) shunget(f);
    }
    اگر (c-'0'>=10U) {
        shunget(f);
        واپس LLONG_MIN;
    }
    برائے (x=0; c-'0'<10U && x<زیادہ_سے_زیادہ_عدد/10; c = shgetc(f))
        x = 10*x + (c-'0');
    برائے (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    برائے (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    واپس neg ? -y : y;
}

#تعریف_کرو LD_B1B_DIG 2
#تعریف_کرو LD_B1B_MAX 9007199, 254740991
#تعریف_کرو KMAX 128
#تعریف_کرو نقاب (KMAX-1)

ساکن دوہرا decfloat(FFFILE *f, صحیح c, صحیح بٹ, صحیح emin, صحیح sign, صحیح pok)
{
    uint32_t x[KMAX];
    ساکن ثابت uint32_t th[] = { LD_B1B_MAX };
    صحیح i, j, k, a, z;
    طویل طویل lrp=0, dc=0;
    طویل طویل e10=0;
    صحیح lnz = 0;
    صحیح gotdig = 0, gotrad = 0;
    صحیح rp;
    صحیح e2;
    صحیح emax = -emin-بٹ+3;
    صحیح denormal = 0;
    دوہرا y;
    دوہرا frac=0;
    دوہرا bias=0;
    ساکن ثابت صحیح p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    برائے (; c=='0'; c = shgetc(f)) gotdig=1;
    اگر (c=='.') {
        gotrad = 1;
        برائے (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    برائے (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        اگر (c == '.') {
            اگر (gotrad) توڑو;
            gotrad = 1;
            lrp = dc;
        } ورنہ اگر (k < KMAX-3) {
            dc++;
            اگر (c!='0') lnz = dc;
            اگر (j) x[k] = x[k]*10 + c-'0';
            ورنہ x[k] = c-'0';
            اگر (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ورنہ {
            dc++;
            اگر (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    اگر (!gotrad) lrp=dc;

    اگر (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        اگر (e10 == LLONG_MIN) {
            اگر (pok) {
                shunget(f);
            } ورنہ {
                shlim(f, 0);
                واپس 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ورنہ اگر (c>=0) {
        shunget(f);
    }
    اگر (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        واپس 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    اگر (!x[0]) واپس sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    اگر (lrp==dc && dc<10 && (بٹ>30 || x[0]>>بٹ==0))
        واپس sign * (دوہرا)x[0];
    اگر (lrp > -emin/2) {
        errno = ERANGE;
        واپس sign * DBL_MAX * DBL_MAX;
    }
    اگر (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        واپس sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    اگر (j) {
        برائے (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    اگر (lnz<9 && lnz<=rp && rp < 18) {
        صحیح bitlim;
        اگر (rp == 9) واپس sign * (دوہرا)x[0];
        اگر (rp < 9) واپس sign * (دوہرا)x[0] / p10s[8-rp];
        bitlim = بٹ-3*(صحیح)(rp-9);
        اگر (bitlim>30 || x[0]>>bitlim==0)
            واپس sign * (دوہرا)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    برائے (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    اگر (rp % 9) {
        صحیح rpm9 = rp>=0 ? rp%9 : rp%9+9;
        صحیح p10 = p10s[8-rpm9];
        uint32_t حاصل = 0;
        برائے (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + حاصل;
            حاصل = 1000000000/p10 * tmp;
            اگر (k==a && !x[k]) {
                a = (a+1 & نقاب);
                rp -= 9;
            }
        }
        اگر (حاصل) x[z++] = حاصل;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    جب (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t حاصل = 0;
        e2 -= 29;
        برائے (k=(z-1 & نقاب); ; k=(k-1 & نقاب)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + حاصل;
            اگر (tmp > 1000000000) {
                حاصل = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ورنہ {
                حاصل = 0;
                x[k] = tmp;
            }
            اگر (k==(z-1 & نقاب) && k!=a && !x[k]) z = k;
            اگر (k==a) توڑو;
        }
        اگر (حاصل) {
            rp += 9;
            a = (a-1 & نقاب);
            اگر (a == z) {
                z = (z-1 & نقاب);
                x[z-1 & نقاب] |= x[z];
            }
            x[a] = حاصل;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    برائے (;;) {
        uint32_t حاصل = 0;
        صحیح sh = 1;
        برائے (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & نقاب);
            اگر (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                توڑو;
            }
            اگر (x[a+i & نقاب] > th[i]) توڑو;
        }
        اگر (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) توڑو;
        /* FIXME: find a way to compute optimal sh */
        اگر (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        برائے (k=a; k!=z; k=(k+1 & نقاب)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + حاصل;
            حاصل = (1000000000>>sh) * tmp;
            اگر (k==a && !x[k]) {
                a = (a+1 & نقاب);
                i--;
                rp -= 9;
            }
        }
        اگر (حاصل) {
            اگر ((z+1 & نقاب) != a) {
                x[z] = حاصل;
                z = (z+1 & نقاب);
            } ورنہ x[z-1 & نقاب] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    برائے (y=i=0; i<LD_B1B_DIG; i++) {
        اگر ((a+i & نقاب)==z) x[(z=(z+1 & نقاب))-1 & نقاب] = 0;
        y = 1000000000.0L * y + x[a+i & نقاب];
    }

    y *= sign;

    /* Limit precision for denormal results */
    اگر (بٹ > DBL_MANT_DIG+e2-emin) {
        بٹ = DBL_MANT_DIG+e2-emin;
        اگر (بٹ<0) بٹ=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    اگر (بٹ < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-بٹ-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-بٹ));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    اگر ((a+i & نقاب) != z) {
        uint32_t t = x[a+i & نقاب];
        اگر (t < 500000000 && (t || (a+i+1 & نقاب) != z))
            frac += 0.25*sign;
        ورنہ اگر (t > 500000000)
            frac += 0.75*sign;
        ورنہ اگر (t == 500000000) {
            اگر ((a+i+1 & نقاب) == z)
                frac += 0.5*sign;
            ورنہ
                frac += 0.75*sign;
        }
        اگر (DBL_MANT_DIG-بٹ >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    اگر ((e2+DBL_MANT_DIG & زیادہ_سے_زیادہ_عدد) > emax-5) {
        اگر (fabs(y) >= قوت(2, DBL_MANT_DIG)) {
            اگر (denormal && بٹ==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        اگر (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    واپس scalbn(y, e2);
}

ساکن دوہرا hexfloat(FFFILE *f, صحیح بٹ, صحیح emin, صحیح sign, صحیح pok)
{
    uint32_t x = 0;
    دوہرا y = 0;
    دوہرا scale = 1;
    دوہرا bias = 0;
    صحیح gottail = 0, gotrad = 0, gotdig = 0;
    طویل طویل rp = 0;
    طویل طویل dc = 0;
    طویل طویل e2 = 0;
    صحیح d;
    صحیح c;

    c = shgetc(f);

    /* Skip leading zeros */
    برائے (; c=='0'; c = shgetc(f))
        gotdig = 1;

    اگر (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        برائے (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    برائے (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        اگر (c=='.') {
            اگر (gotrad) توڑو;
            rp = dc;
            gotrad = 1;
        } ورنہ {
            gotdig = 1;
            اگر (c > '9') d = (c|32)+10-'a';
            ورنہ d = c-'0';
            اگر (dc<8) {
                x = x*16 + d;
            } ورنہ اگر (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ورنہ اگر (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    اگر (!gotdig) {
        shunget(f);
        اگر (pok) {
            shunget(f);
            اگر (gotrad) shunget(f);
        } ورنہ {
            shlim(f, 0);
        }
        واپس sign * 0.0;
    }
    اگر (!gotrad) rp = dc;
    جب (dc<8) x *= 16, dc++;
    اگر ((c|32)=='p') {
        e2 = scanexp(f, pok);
        اگر (e2 == LLONG_MIN) {
            اگر (pok) {
                shunget(f);
            } ورنہ {
                shlim(f, 0);
                واپس 0;
            }
            e2 = 0;
        }
    } ورنہ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    اگر (!x) واپس sign * 0.0;
    اگر (e2 > -emin) {
        errno = ERANGE;
        واپس sign * DBL_MAX * DBL_MAX;
    }
    اگر (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        واپس sign * DBL_MIN * DBL_MIN;
    }

    جب (x < 0x80000000) {
        اگر (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ورنہ {
            x += x;
            y += y;
        }
        e2--;
    }

    اگر (بٹ > 32+e2-emin) {
        بٹ = 32+e2-emin;
        اگر (بٹ<0) بٹ=0;
    }

    اگر (بٹ < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-بٹ-1), sign);

    اگر (بٹ<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(دوہرا)x + sign*y;
    y -= bias;

    اگر (!y) errno = ERANGE;

    واپس scalbn(y, e2);
}

ساکن دوہرا fffloatscan(FFFILE *f, صحیح prec, صحیح pok)
{
    صحیح sign = 1;
    size_t i;
    صحیح بٹ;
    صحیح emin;
    صحیح c;

    انتخاب (prec) {
    حالت 0:
        بٹ = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-بٹ;
        توڑو;
    حالت 1:
        بٹ = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-بٹ;
        توڑو;
    حالت 2:
        بٹ = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-بٹ;
        توڑو;
    طےشدہ:
        واپس 0;
    }

    جب (av_isspace((c = shgetc(f))));

    اگر (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    برائے (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        اگر (i<7) c = shgetc(f);
    اگر (i==3 || i==8 || (i>3 && pok)) {
        اگر (i!=8) {
            shunget(f);
            اگر (pok) برائے (; i>3; i--) shunget(f);
        }
        واپس sign * INFINITY;
    }
    اگر (!i) برائے (i=0; i<3 && (c|32)=="nan"[i]; i++)
        اگر (i<2) c = shgetc(f);
    اگر (i==3) {
        اگر (shgetc(f) != '(') {
            shunget(f);
            واپس NAN;
        }
        برائے (i=1; ; i++) {
            c = shgetc(f);
            اگر (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                جاری;
            اگر (c==')') واپس NAN;
            shunget(f);
            اگر (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                واپس 0;
            }
            جب (i--) shunget(f);
            واپس NAN;
        }
    }

    اگر (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        واپس 0;
    }

    اگر (c=='0') {
        c = shgetc(f);
        اگر ((c|32) == 'x')
            واپس hexfloat(f, بٹ, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    واپس decfloat(f, c, بٹ, emin, sign, pok);
}

ساکن خالی *arg_n(va_list ap, غیرعلامتی صحیح n)
{
    خالی *p;
    غیرعلامتی صحیح i;
    va_list ap2;
    va_copy(ap2, ap);
    برائے (i=n; i>1; i--) va_arg(ap2, خالی *);
    p = va_arg(ap2, خالی *);
    va_end(ap2);
    واپس p;
}

ساکن خالی store_int(خالی *dest, صحیح سائز, غیرعلامتی طویل طویل i)
{
    اگر (!dest) واپس;
    انتخاب (سائز) {
    حالت سائز_hh:
        *(حرف *)dest = i;
        توڑو;
    حالت سائز_h:
        *(مختصر *)dest = i;
        توڑو;
    حالت سائز_def:
        *(صحیح *)dest = i;
        توڑو;
    حالت سائز_l:
        *(طویل *)dest = i;
        توڑو;
    حالت سائز_ll:
        *(طویل طویل *)dest = i;
        توڑو;
    }
}

ساکن صحیح ff_vfscanf(FFFILE *f, ثابت حرف *fmt, va_list ap)
{
    صحیح چوڑائی;
    صحیح سائز;
    صحیح بنیاد_2;
    ثابت غیرعلامتی حرف *p;
    صحیح c, t;
    حرف *s;
    خالی *dest=تہی;
    صحیح invert;
    صحیح matches=0;
    غیرعلامتی طویل طویل x;
    دوہرا y;
    ptrdiff_t pos = 0;
    غیرعلامتی حرف scanset[257];
    size_t i;

    برائے (p=(ثابت غیرعلامتی حرف *)fmt; *p; p++) {

        اگر (av_isspace(*p)) {
            جب (av_isspace(p[1])) p++;
            shlim(f, 0);
            جب (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            جاری;
        }
        اگر (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            اگر (*p == '%') {
                p++;
                جب (av_isspace((c=shgetc(f))));
            } ورنہ {
                c = shgetc(f);
            }
            اگر (c!=*p) {
                shunget(f);
                اگر (c<0) جاؤ داخلہ_fail;
                جاؤ مطابقت_fail;
            }
            pos += shcnt(f);
            جاری;
        }

        p++;
        اگر (*p=='*') {
            dest = 0; p++;
        } ورنہ اگر (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ورنہ {
            dest = va_arg(ap, خالی *);
        }

        برائے (چوڑائی=0; av_isdigit(*p); p++) {
            چوڑائی = 10*چوڑائی + *p - '0';
        }

        اگر (*p=='m') {
            s = 0;
            p++;
        }

        سائز = سائز_def;
        انتخاب (*p++) {
        حالت 'h':
            اگر (*p == 'h') p++, سائز = سائز_hh;
            ورنہ سائز = سائز_h;
            توڑو;
        حالت 'l':
            اگر (*p == 'l') p++, سائز = سائز_ll;
            ورنہ سائز = سائز_l;
            توڑو;
        حالت 'j':
            سائز = سائز_ll;
            توڑو;
        حالت 'z':
        حالت 't':
            سائز = سائز_l;
            توڑو;
        حالت 'L':
            سائز = سائز_L;
            توڑو;
        حالت 'd': حالت 'i': حالت 'o': حالت 'u': حالت 'x':
        حالت 'a': حالت 'e': حالت 'f': حالت 'g':
        حالت 'A': حالت 'E': حالت 'F': حالت 'G': حالت 'X':
        حالت 's': حالت 'c': حالت '[':
        حالت 'S': حالت 'C':
        حالت 'p': حالت 'n':
            p--;
            توڑو;
        طےشدہ:
            جاؤ fmt_fail;
        }

        t = *p;

        /* C or S */
        اگر ((t&0x2f) == 3) {
            t |= 32;
            سائز = سائز_l;
        }

        انتخاب (t) {
            حالت 'c':
                اگر (چوڑائی < 1) چوڑائی = 1;
                توڑو;
            حالت '[':
                توڑو;
            حالت 'n':
                store_int(dest, سائز, pos);
                /* do not increment match count, etc! */
                جاری;
            طےشدہ:
                shlim(f, 0);
                جب (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, چوڑائی);
        اگر (shgetc(f) < 0) جاؤ داخلہ_fail;
        shunget(f);

        انتخاب (t) {
            حالت 's':
            حالت 'c':
            حالت '[':
                اگر (t == 'c' || t == 's') {
                    memset(scanset, -1, حجم scanset);
                    scanset[0] = 0;
                    اگر (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ورنہ {
                    اگر (*++p == '^') p++, invert = 1;
                    ورنہ invert = 0;
                    memset(scanset, invert, حجم scanset);
                    scanset[0] = 0;
                    اگر (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ورنہ اگر (*p == ']') p++, scanset[1+']'] = 1-invert;
                    برائے (; *p != ']'; p++) {
                        اگر (!*p) جاؤ fmt_fail;
                        اگر (*p=='-' && p[1] && p[1] != ']')
                            برائے (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                اگر ((s = dest)) {
                    جب (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ورنہ {
                    جب (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                اگر (!shcnt(f)) جاؤ مطابقت_fail;
                اگر (t == 'c' && shcnt(f) != چوڑائی) جاؤ مطابقت_fail;
                اگر (t != 'c') {
                    اگر (s) s[i] = 0;
                }
                توڑو;
            حالت 'p':
            حالت 'X':
            حالت 'x':
                بنیاد_2 = 16;
                جاؤ int_common;
            حالت 'o':
                بنیاد_2 = 8;
                جاؤ int_common;
            حالت 'd':
            حالت 'u':
                بنیاد_2 = 10;
                جاؤ int_common;
            حالت 'i':
                بنیاد_2 = 0;
int_common:
                x = ffintscan(f, بنیاد_2, 0, ULLONG_MAX);
                اگر (!shcnt(f))
                    جاؤ مطابقت_fail;
                اگر (t=='p' && dest)
                    *(خالی **)dest = (خالی *)(uintptr_t)x;
                ورنہ
                    store_int(dest, سائز, x);
                توڑو;
            حالت 'a': حالت 'A':
            حالت 'e': حالت 'E':
            حالت 'f': حالت 'F':
            حالت 'g': حالت 'G':
                y = fffloatscan(f, سائز, 0);
                اگر (!shcnt(f))
                    جاؤ مطابقت_fail;
                اگر (dest) {
                    انتخاب (سائز) {
                    حالت سائز_def:
                        *(اعشاری *)dest = y;
                        توڑو;
                    حالت سائز_l:
                        *(دوہرا *)dest = y;
                        توڑو;
                    حالت سائز_L:
                        *(دوہرا *)dest = y;
                        توڑو;
                    }
                }
                توڑو;
        }

        pos += shcnt(f);
        اگر (dest) matches++;
    }
    اگر (0) {
fmt_fail:
داخلہ_fail:
        اگر (!matches) matches--;
    }
مطابقت_fail:
    واپس matches;
}

ساکن صحیح ff_vsscanf(ثابت حرف *s, ثابت حرف *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (خالی *)s, .cookie = (خالی *)s,
        .اقرأ = ffstring_read,
    };

    واپس ff_vfscanf(&f, fmt, ap);
}

صحیح av_sscanf(ثابت حرف *string, ثابت حرف *format, ...)
{
    صحیح ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    واپس ret;
}
