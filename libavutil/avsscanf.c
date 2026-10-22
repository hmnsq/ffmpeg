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

#ضمن <errno.h>
#ضمن <limits.h>
#ضمن <math.h>
#ضمن <stdarg.h>
#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <float.h>

#ضمن "avstring.h"

تعريفنوع بنية FFFILE {
    size_t buf_اندازه;
    بیعلامت حرف *buf;
    بیعلامت حرف *rpos, *rend;
    بیعلامت حرف *shend;
    ptrdiff_t shlim, shcnt;
    فراغ *cookie;
    size_t (*اقرأ)(بنية FFFILE *, بیعلامت حرف *, size_t);
} FFFILE;

#تعریف_کن اندازه_hh -2
#تعریف_کن اندازه_h  -1
#تعریف_کن اندازه_def 0
#تعریف_کن اندازه_l   1
#تعریف_کن اندازه_L   2
#تعریف_کن اندازه_ll  3

#تعریف_کن shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ساكن صحيح fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_اندازه;
    أرجع 0;
}

ساكن size_t ffstring_read(FFFILE *f, بیعلامت حرف *buf, size_t len)
{
    حرف *src = f->cookie;
    size_t k = len+256;
    حرف *انتها = memchr(src, 0, k);

    إذا (انتها) k = انتها-src;
    إذا (k < len) len = k;
    کپی_حافظه(buf, src, len);
    f->rpos = (فراغ *)(src+len);
    f->rend = (فراغ *)(src+k);
    f->cookie = src+k;

    أرجع len;
}

ساكن صحيح ffuflow(FFFILE *f)
{
    بیعلامت حرف c;
    إذا (!fftoread(f) && f->اقرأ(f, &c, 1)==1) أرجع c;
    أرجع EOF;
}

ساكن فراغ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    إذا (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    وإلا
        f->shend = f->rend;
}

ساكن صحيح ffshgetc(FFFILE *f)
{
    صحيح c;
    ptrdiff_t cnt = shcnt(f);
    إذا (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        أرجع EOF;
    }
    cnt++;
    إذا (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    وإلا
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    إذا (f->rpos[-1] != c) f->rpos[-1] = c;
    أرجع c;
}

#تعریف_کن shlim(f, lim) ffshlim((f), (lim))
#تعریف_کن shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#تعریف_کن shunget(f) ((f)->shend ? (فراغ)(f)->rpos-- : (فراغ)0)

ساكن ثابت بیعلامت حرف جدول[] = { -1,
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

ساكن بیعلامت دراز دراز ffintscan(FFFILE *f, بیعلامت پایه_2, صحيح pok, بیعلامت دراز دراز lim)
{
    ثابت بیعلامت حرف *val = جدول+1;
    صحيح c, neg=0;
    بیعلامت x;
    بیعلامت دراز دراز y;
    إذا (پایه_2 > 36 || پایه_2 == 1) {
        errno = EINVAL;
        أرجع 0;
    }
    طالما (av_isspace((c=shgetc(f))));
    إذا (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    إذا ((پایه_2 == 0 || پایه_2 == 16) && c=='0') {
        c = shgetc(f);
        إذا ((c|32)=='x') {
            c = shgetc(f);
            إذا (val[c]>=16) {
                shunget(f);
                إذا (pok) shunget(f);
                وإلا shlim(f, 0);
                أرجع 0;
            }
            پایه_2 = 16;
        } وإلا إذا (پایه_2 == 0) {
            پایه_2 = 8;
        }
    } وإلا {
        إذا (پایه_2 == 0) پایه_2 = 10;
        إذا (val[c] >= پایه_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            أرجع 0;
        }
    }
    إذا (پایه_2 == 10) {
        لكل (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        لكل (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        إذا (c-'0'>=10U) اذهب انجامشده;
    } وإلا إذا (!(پایه_2 & پایه_2-1)) {
        صحيح bs = "\0\1\2\4\7\3\6\5"[(0x17*پایه_2)>>5&7];
        لكل (x=0; val[c]<پایه_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        لكل (y=x; val[c]<پایه_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } وإلا {
        لكل (x=0; val[c]<پایه_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*پایه_2 + val[c];
        لكل (y=x; val[c]<پایه_2 && y<=ULLONG_MAX/پایه_2 && پایه_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*پایه_2 + val[c];
    }
    إذا (val[c]<پایه_2) {
        لكل (; val[c]<پایه_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        إذا (lim&1) neg = 0;
    }
انجامشده:
    shunget(f);
    إذا (y>=lim) {
        إذا (!(lim&1) && !neg) {
            errno = ERANGE;
            أرجع lim-1;
        } وإلا إذا (y>lim) {
            errno = ERANGE;
            أرجع lim;
        }
    }
    أرجع (y^neg)-neg;
}

ساكن دراز دراز scanexp(FFFILE *f, صحيح pok)
{
    صحيح c;
    صحيح x;
    دراز دراز y;
    صحيح neg = 0;

    c = shgetc(f);
    إذا (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        إذا (c-'0'>=10U && pok) shunget(f);
    }
    إذا (c-'0'>=10U) {
        shunget(f);
        أرجع LLONG_MIN;
    }
    لكل (x=0; c-'0'<10U && x<بیشترین_صحیح/10; c = shgetc(f))
        x = 10*x + (c-'0');
    لكل (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    لكل (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    أرجع neg ? -y : y;
}

#تعریف_کن LD_B1B_DIG 2
#تعریف_کن LD_B1B_MAX 9007199, 254740991
#تعریف_کن KMAX 128
#تعریف_کن ماسک (KMAX-1)

ساكن مزدوج decfloat(FFFILE *f, صحيح c, صحيح بیتها, صحيح emin, صحيح sign, صحيح pok)
{
    uint32_t x[KMAX];
    ساكن ثابت uint32_t th[] = { LD_B1B_MAX };
    صحيح i, j, k, a, z;
    دراز دراز lrp=0, dc=0;
    دراز دراز e10=0;
    صحيح lnz = 0;
    صحيح gotdig = 0, gotrad = 0;
    صحيح rp;
    صحيح e2;
    صحيح emax = -emin-بیتها+3;
    صحيح denormal = 0;
    مزدوج y;
    مزدوج frac=0;
    مزدوج bias=0;
    ساكن ثابت صحيح p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    لكل (; c=='0'; c = shgetc(f)) gotdig=1;
    إذا (c=='.') {
        gotrad = 1;
        لكل (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    لكل (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        إذا (c == '.') {
            إذا (gotrad) اكسر;
            gotrad = 1;
            lrp = dc;
        } وإلا إذا (k < KMAX-3) {
            dc++;
            إذا (c!='0') lnz = dc;
            إذا (j) x[k] = x[k]*10 + c-'0';
            وإلا x[k] = c-'0';
            إذا (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } وإلا {
            dc++;
            إذا (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    إذا (!gotrad) lrp=dc;

    إذا (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        إذا (e10 == LLONG_MIN) {
            إذا (pok) {
                shunget(f);
            } وإلا {
                shlim(f, 0);
                أرجع 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } وإلا إذا (c>=0) {
        shunget(f);
    }
    إذا (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        أرجع 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    إذا (!x[0]) أرجع sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    إذا (lrp==dc && dc<10 && (بیتها>30 || x[0]>>بیتها==0))
        أرجع sign * (مزدوج)x[0];
    إذا (lrp > -emin/2) {
        errno = ERANGE;
        أرجع sign * DBL_MAX * DBL_MAX;
    }
    إذا (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        أرجع sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    إذا (j) {
        لكل (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    إذا (lnz<9 && lnz<=rp && rp < 18) {
        صحيح bitlim;
        إذا (rp == 9) أرجع sign * (مزدوج)x[0];
        إذا (rp < 9) أرجع sign * (مزدوج)x[0] / p10s[8-rp];
        bitlim = بیتها-3*(صحيح)(rp-9);
        إذا (bitlim>30 || x[0]>>bitlim==0)
            أرجع sign * (مزدوج)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    لكل (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    إذا (rp % 9) {
        صحيح rpm9 = rp>=0 ? rp%9 : rp%9+9;
        صحيح p10 = p10s[8-rpm9];
        uint32_t انتقال = 0;
        لكل (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + انتقال;
            انتقال = 1000000000/p10 * tmp;
            إذا (k==a && !x[k]) {
                a = (a+1 & ماسک);
                rp -= 9;
            }
        }
        إذا (انتقال) x[z++] = انتقال;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    طالما (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t انتقال = 0;
        e2 -= 29;
        لكل (k=(z-1 & ماسک); ; k=(k-1 & ماسک)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + انتقال;
            إذا (tmp > 1000000000) {
                انتقال = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } وإلا {
                انتقال = 0;
                x[k] = tmp;
            }
            إذا (k==(z-1 & ماسک) && k!=a && !x[k]) z = k;
            إذا (k==a) اكسر;
        }
        إذا (انتقال) {
            rp += 9;
            a = (a-1 & ماسک);
            إذا (a == z) {
                z = (z-1 & ماسک);
                x[z-1 & ماسک] |= x[z];
            }
            x[a] = انتقال;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    لكل (;;) {
        uint32_t انتقال = 0;
        صحيح sh = 1;
        لكل (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & ماسک);
            إذا (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                اكسر;
            }
            إذا (x[a+i & ماسک] > th[i]) اكسر;
        }
        إذا (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) اكسر;
        /* FIXME: find a way to compute optimal sh */
        إذا (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        لكل (k=a; k!=z; k=(k+1 & ماسک)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + انتقال;
            انتقال = (1000000000>>sh) * tmp;
            إذا (k==a && !x[k]) {
                a = (a+1 & ماسک);
                i--;
                rp -= 9;
            }
        }
        إذا (انتقال) {
            إذا ((z+1 & ماسک) != a) {
                x[z] = انتقال;
                z = (z+1 & ماسک);
            } وإلا x[z-1 & ماسک] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    لكل (y=i=0; i<LD_B1B_DIG; i++) {
        إذا ((a+i & ماسک)==z) x[(z=(z+1 & ماسک))-1 & ماسک] = 0;
        y = 1000000000.0L * y + x[a+i & ماسک];
    }

    y *= sign;

    /* Limit precision for denormal results */
    إذا (بیتها > DBL_MANT_DIG+e2-emin) {
        بیتها = DBL_MANT_DIG+e2-emin;
        إذا (بیتها<0) بیتها=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    إذا (بیتها < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-بیتها-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-بیتها));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    إذا ((a+i & ماسک) != z) {
        uint32_t t = x[a+i & ماسک];
        إذا (t < 500000000 && (t || (a+i+1 & ماسک) != z))
            frac += 0.25*sign;
        وإلا إذا (t > 500000000)
            frac += 0.75*sign;
        وإلا إذا (t == 500000000) {
            إذا ((a+i+1 & ماسک) == z)
                frac += 0.5*sign;
            وإلا
                frac += 0.75*sign;
        }
        إذا (DBL_MANT_DIG-بیتها >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    إذا ((e2+DBL_MANT_DIG & بیشترین_صحیح) > emax-5) {
        إذا (fabs(y) >= توان(2, DBL_MANT_DIG)) {
            إذا (denormal && بیتها==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        إذا (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    أرجع scalbn(y, e2);
}

ساكن مزدوج hexfloat(FFFILE *f, صحيح بیتها, صحيح emin, صحيح sign, صحيح pok)
{
    uint32_t x = 0;
    مزدوج y = 0;
    مزدوج scale = 1;
    مزدوج bias = 0;
    صحيح gottail = 0, gotrad = 0, gotdig = 0;
    دراز دراز rp = 0;
    دراز دراز dc = 0;
    دراز دراز e2 = 0;
    صحيح d;
    صحيح c;

    c = shgetc(f);

    /* Skip leading zeros */
    لكل (; c=='0'; c = shgetc(f))
        gotdig = 1;

    إذا (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        لكل (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    لكل (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        إذا (c=='.') {
            إذا (gotrad) اكسر;
            rp = dc;
            gotrad = 1;
        } وإلا {
            gotdig = 1;
            إذا (c > '9') d = (c|32)+10-'a';
            وإلا d = c-'0';
            إذا (dc<8) {
                x = x*16 + d;
            } وإلا إذا (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } وإلا إذا (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    إذا (!gotdig) {
        shunget(f);
        إذا (pok) {
            shunget(f);
            إذا (gotrad) shunget(f);
        } وإلا {
            shlim(f, 0);
        }
        أرجع sign * 0.0;
    }
    إذا (!gotrad) rp = dc;
    طالما (dc<8) x *= 16, dc++;
    إذا ((c|32)=='p') {
        e2 = scanexp(f, pok);
        إذا (e2 == LLONG_MIN) {
            إذا (pok) {
                shunget(f);
            } وإلا {
                shlim(f, 0);
                أرجع 0;
            }
            e2 = 0;
        }
    } وإلا {
        shunget(f);
    }
    e2 += 4*rp - 32;

    إذا (!x) أرجع sign * 0.0;
    إذا (e2 > -emin) {
        errno = ERANGE;
        أرجع sign * DBL_MAX * DBL_MAX;
    }
    إذا (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        أرجع sign * DBL_MIN * DBL_MIN;
    }

    طالما (x < 0x80000000) {
        إذا (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } وإلا {
            x += x;
            y += y;
        }
        e2--;
    }

    إذا (بیتها > 32+e2-emin) {
        بیتها = 32+e2-emin;
        إذا (بیتها<0) بیتها=0;
    }

    إذا (بیتها < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-بیتها-1), sign);

    إذا (بیتها<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(مزدوج)x + sign*y;
    y -= bias;

    إذا (!y) errno = ERANGE;

    أرجع scalbn(y, e2);
}

ساكن مزدوج fffloatscan(FFFILE *f, صحيح prec, صحيح pok)
{
    صحيح sign = 1;
    size_t i;
    صحيح بیتها;
    صحيح emin;
    صحيح c;

    بدل (prec) {
    حالة 0:
        بیتها = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-بیتها;
        اكسر;
    حالة 1:
        بیتها = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-بیتها;
        اكسر;
    حالة 2:
        بیتها = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-بیتها;
        اكسر;
    افتراضي:
        أرجع 0;
    }

    طالما (av_isspace((c = shgetc(f))));

    إذا (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    لكل (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        إذا (i<7) c = shgetc(f);
    إذا (i==3 || i==8 || (i>3 && pok)) {
        إذا (i!=8) {
            shunget(f);
            إذا (pok) لكل (; i>3; i--) shunget(f);
        }
        أرجع sign * INFINITY;
    }
    إذا (!i) لكل (i=0; i<3 && (c|32)=="nan"[i]; i++)
        إذا (i<2) c = shgetc(f);
    إذا (i==3) {
        إذا (shgetc(f) != '(') {
            shunget(f);
            أرجع NAN;
        }
        لكل (i=1; ; i++) {
            c = shgetc(f);
            إذا (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                استمر;
            إذا (c==')') أرجع NAN;
            shunget(f);
            إذا (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                أرجع 0;
            }
            طالما (i--) shunget(f);
            أرجع NAN;
        }
    }

    إذا (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        أرجع 0;
    }

    إذا (c=='0') {
        c = shgetc(f);
        إذا ((c|32) == 'x')
            أرجع hexfloat(f, بیتها, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    أرجع decfloat(f, c, بیتها, emin, sign, pok);
}

ساكن فراغ *arg_n(va_list ap, بیعلامت صحيح n)
{
    فراغ *p;
    بیعلامت صحيح i;
    va_list ap2;
    va_copy(ap2, ap);
    لكل (i=n; i>1; i--) va_arg(ap2, فراغ *);
    p = va_arg(ap2, فراغ *);
    va_end(ap2);
    أرجع p;
}

ساكن فراغ store_int(فراغ *dest, صحيح اندازه, بیعلامت دراز دراز i)
{
    إذا (!dest) أرجع;
    بدل (اندازه) {
    حالة اندازه_hh:
        *(حرف *)dest = i;
        اكسر;
    حالة اندازه_h:
        *(کوتاه *)dest = i;
        اكسر;
    حالة اندازه_def:
        *(صحيح *)dest = i;
        اكسر;
    حالة اندازه_l:
        *(دراز *)dest = i;
        اكسر;
    حالة اندازه_ll:
        *(دراز دراز *)dest = i;
        اكسر;
    }
}

ساكن صحيح ff_vfscanf(FFFILE *f, ثابت حرف *fmt, va_list ap)
{
    صحيح عرض;
    صحيح اندازه;
    صحيح پایه_2;
    ثابت بیعلامت حرف *p;
    صحيح c, t;
    حرف *s;
    فراغ *dest=عدم;
    صحيح invert;
    صحيح matches=0;
    بیعلامت دراز دراز x;
    مزدوج y;
    ptrdiff_t pos = 0;
    بیعلامت حرف scanset[257];
    size_t i;

    لكل (p=(ثابت بیعلامت حرف *)fmt; *p; p++) {

        إذا (av_isspace(*p)) {
            طالما (av_isspace(p[1])) p++;
            shlim(f, 0);
            طالما (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            استمر;
        }
        إذا (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            إذا (*p == '%') {
                p++;
                طالما (av_isspace((c=shgetc(f))));
            } وإلا {
                c = shgetc(f);
            }
            إذا (c!=*p) {
                shunget(f);
                إذا (c<0) اذهب درون_داد_fail;
                اذهب تطابق_fail;
            }
            pos += shcnt(f);
            استمر;
        }

        p++;
        إذا (*p=='*') {
            dest = 0; p++;
        } وإلا إذا (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } وإلا {
            dest = va_arg(ap, فراغ *);
        }

        لكل (عرض=0; av_isdigit(*p); p++) {
            عرض = 10*عرض + *p - '0';
        }

        إذا (*p=='m') {
            s = 0;
            p++;
        }

        اندازه = اندازه_def;
        بدل (*p++) {
        حالة 'h':
            إذا (*p == 'h') p++, اندازه = اندازه_hh;
            وإلا اندازه = اندازه_h;
            اكسر;
        حالة 'l':
            إذا (*p == 'l') p++, اندازه = اندازه_ll;
            وإلا اندازه = اندازه_l;
            اكسر;
        حالة 'j':
            اندازه = اندازه_ll;
            اكسر;
        حالة 'z':
        حالة 't':
            اندازه = اندازه_l;
            اكسر;
        حالة 'L':
            اندازه = اندازه_L;
            اكسر;
        حالة 'd': حالة 'i': حالة 'o': حالة 'u': حالة 'x':
        حالة 'a': حالة 'e': حالة 'f': حالة 'g':
        حالة 'A': حالة 'E': حالة 'F': حالة 'G': حالة 'X':
        حالة 's': حالة 'c': حالة '[':
        حالة 'S': حالة 'C':
        حالة 'p': حالة 'n':
            p--;
            اكسر;
        افتراضي:
            اذهب fmt_fail;
        }

        t = *p;

        /* C or S */
        إذا ((t&0x2f) == 3) {
            t |= 32;
            اندازه = اندازه_l;
        }

        بدل (t) {
            حالة 'c':
                إذا (عرض < 1) عرض = 1;
                اكسر;
            حالة '[':
                اكسر;
            حالة 'n':
                store_int(dest, اندازه, pos);
                /* do not increment match count, etc! */
                استمر;
            افتراضي:
                shlim(f, 0);
                طالما (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, عرض);
        إذا (shgetc(f) < 0) اذهب درون_داد_fail;
        shunget(f);

        بدل (t) {
            حالة 's':
            حالة 'c':
            حالة '[':
                إذا (t == 'c' || t == 's') {
                    memset(scanset, -1, حجم scanset);
                    scanset[0] = 0;
                    إذا (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } وإلا {
                    إذا (*++p == '^') p++, invert = 1;
                    وإلا invert = 0;
                    memset(scanset, invert, حجم scanset);
                    scanset[0] = 0;
                    إذا (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    وإلا إذا (*p == ']') p++, scanset[1+']'] = 1-invert;
                    لكل (; *p != ']'; p++) {
                        إذا (!*p) اذهب fmt_fail;
                        إذا (*p=='-' && p[1] && p[1] != ']')
                            لكل (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                إذا ((s = dest)) {
                    طالما (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } وإلا {
                    طالما (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                إذا (!shcnt(f)) اذهب تطابق_fail;
                إذا (t == 'c' && shcnt(f) != عرض) اذهب تطابق_fail;
                إذا (t != 'c') {
                    إذا (s) s[i] = 0;
                }
                اكسر;
            حالة 'p':
            حالة 'X':
            حالة 'x':
                پایه_2 = 16;
                اذهب int_common;
            حالة 'o':
                پایه_2 = 8;
                اذهب int_common;
            حالة 'd':
            حالة 'u':
                پایه_2 = 10;
                اذهب int_common;
            حالة 'i':
                پایه_2 = 0;
int_common:
                x = ffintscan(f, پایه_2, 0, ULLONG_MAX);
                إذا (!shcnt(f))
                    اذهب تطابق_fail;
                إذا (t=='p' && dest)
                    *(فراغ **)dest = (فراغ *)(uintptr_t)x;
                وإلا
                    store_int(dest, اندازه, x);
                اكسر;
            حالة 'a': حالة 'A':
            حالة 'e': حالة 'E':
            حالة 'f': حالة 'F':
            حالة 'g': حالة 'G':
                y = fffloatscan(f, اندازه, 0);
                إذا (!shcnt(f))
                    اذهب تطابق_fail;
                إذا (dest) {
                    بدل (اندازه) {
                    حالة اندازه_def:
                        *(عائم *)dest = y;
                        اكسر;
                    حالة اندازه_l:
                        *(مزدوج *)dest = y;
                        اكسر;
                    حالة اندازه_L:
                        *(مزدوج *)dest = y;
                        اكسر;
                    }
                }
                اكسر;
        }

        pos += shcnt(f);
        إذا (dest) matches++;
    }
    إذا (0) {
fmt_fail:
درون_داد_fail:
        إذا (!matches) matches--;
    }
تطابق_fail:
    أرجع matches;
}

ساكن صحيح ff_vsscanf(ثابت حرف *s, ثابت حرف *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (فراغ *)s, .cookie = (فراغ *)s,
        .اقرأ = ffstring_read,
    };

    أرجع ff_vfscanf(&f, fmt, ap);
}

صحيح av_sscanf(ثابت حرف *string, ثابت حرف *format, ...)
{
    صحيح ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    أرجع ret;
}
