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
    size_t buf_size;
    unsigned حرف *buf;
    unsigned حرف *rpos, *rend;
    unsigned حرف *shend;
    ptrdiff_t shlim, shcnt;
    فراغ *cookie;
    size_t (*اقرأ)(بنية FFFILE *, unsigned حرف *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ساكن صحيح fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    החזר 0;
}

ساكن size_t ffstring_read(FFFILE *f, unsigned حرف *buf, size_t len)
{
    حرف *src = f->cookie;
    size_t k = len+256;
    حرف *end = memchr(src, 0, k);

    אם (end) k = end-src;
    אם (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (فراغ *)(src+len);
    f->rend = (فراغ *)(src+k);
    f->cookie = src+k;

    החזר len;
}

ساكن صحيح ffuflow(FFFILE *f)
{
    unsigned حرف c;
    אם (!fftoread(f) && f->اقرأ(f, &c, 1)==1) החזר c;
    החזר EOF;
}

ساكن فراغ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    אם (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    אחרת
        f->shend = f->rend;
}

ساكن صحيح ffshgetc(FFFILE *f)
{
    صحيح c;
    ptrdiff_t cnt = shcnt(f);
    אם (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        החזר EOF;
    }
    cnt++;
    אם (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    אחרת
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    אם (f->rpos[-1] != c) f->rpos[-1] = c;
    החזר c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (فراغ)(f)->rpos-- : (فراغ)0)

ساكن ثابت unsigned حرف table[] = { -1,
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

ساكن unsigned long long ffintscan(FFFILE *f, unsigned base, صحيح pok, unsigned long long lim)
{
    ثابت unsigned حرف *val = table+1;
    صحيح c, neg=0;
    unsigned x;
    unsigned long long y;
    אם (base > 36 || base == 1) {
        errno = EINVAL;
        החזר 0;
    }
    כלעוד (av_isspace((c=shgetc(f))));
    אם (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    אם ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        אם ((c|32)=='x') {
            c = shgetc(f);
            אם (val[c]>=16) {
                shunget(f);
                אם (pok) shunget(f);
                אחרת shlim(f, 0);
                החזר 0;
            }
            base = 16;
        } אחרת אם (base == 0) {
            base = 8;
        }
    } אחרת {
        אם (base == 0) base = 10;
        אם (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            החזר 0;
        }
    }
    אם (base == 10) {
        עבור (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        עבור (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        אם (c-'0'>=10U) اذهب done;
    } אחרת אם (!(base & base-1)) {
        صحيح bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        עבור (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        עבור (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } אחרת {
        עבור (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        עבור (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    אם (val[c]<base) {
        עבור (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        אם (lim&1) neg = 0;
    }
done:
    shunget(f);
    אם (y>=lim) {
        אם (!(lim&1) && !neg) {
            errno = ERANGE;
            החזר lim-1;
        } אחרת אם (y>lim) {
            errno = ERANGE;
            החזר lim;
        }
    }
    החזר (y^neg)-neg;
}

ساكن long long scanexp(FFFILE *f, صحيح pok)
{
    صحيح c;
    صحيح x;
    long long y;
    صحيح neg = 0;

    c = shgetc(f);
    אם (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        אם (c-'0'>=10U && pok) shunget(f);
    }
    אם (c-'0'>=10U) {
        shunget(f);
        החזר LLONG_MIN;
    }
    עבור (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    עבור (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    עבור (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    החזר neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

ساكن مزدوج decfloat(FFFILE *f, صحيح c, صحيح bits, صحيح emin, صحيح sign, صحيح pok)
{
    uint32_t x[KMAX];
    ساكن ثابت uint32_t th[] = { LD_B1B_MAX };
    صحيح i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    صحيح lnz = 0;
    صحيح gotdig = 0, gotrad = 0;
    صحيح rp;
    صحيح e2;
    صحيح emax = -emin-bits+3;
    صحيح denormal = 0;
    مزدوج y;
    مزدوج frac=0;
    مزدوج bias=0;
    ساكن ثابت صحيح p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    עבור (; c=='0'; c = shgetc(f)) gotdig=1;
    אם (c=='.') {
        gotrad = 1;
        עבור (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    עבור (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        אם (c == '.') {
            אם (gotrad) اكسر;
            gotrad = 1;
            lrp = dc;
        } אחרת אם (k < KMAX-3) {
            dc++;
            אם (c!='0') lnz = dc;
            אם (j) x[k] = x[k]*10 + c-'0';
            אחרת x[k] = c-'0';
            אם (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } אחרת {
            dc++;
            אם (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    אם (!gotrad) lrp=dc;

    אם (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        אם (e10 == LLONG_MIN) {
            אם (pok) {
                shunget(f);
            } אחרת {
                shlim(f, 0);
                החזר 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } אחרת אם (c>=0) {
        shunget(f);
    }
    אם (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        החזר 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    אם (!x[0]) החזר sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    אם (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        החזר sign * (مزدوج)x[0];
    אם (lrp > -emin/2) {
        errno = ERANGE;
        החזר sign * DBL_MAX * DBL_MAX;
    }
    אם (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        החזר sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    אם (j) {
        עבור (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    אם (lnz<9 && lnz<=rp && rp < 18) {
        صحيح bitlim;
        אם (rp == 9) החזר sign * (مزدوج)x[0];
        אם (rp < 9) החזר sign * (مزدوج)x[0] / p10s[8-rp];
        bitlim = bits-3*(صحيح)(rp-9);
        אם (bitlim>30 || x[0]>>bitlim==0)
            החזר sign * (مزدوج)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    עבור (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    אם (rp % 9) {
        صحيح rpm9 = rp>=0 ? rp%9 : rp%9+9;
        صحيح p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        עבור (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            אם (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        אם (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    כלעוד (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        עבור (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            אם (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } אחרת {
                carry = 0;
                x[k] = tmp;
            }
            אם (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            אם (k==a) اكسر;
        }
        אם (carry) {
            rp += 9;
            a = (a-1 & MASK);
            אם (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    עבור (;;) {
        uint32_t carry = 0;
        صحيح sh = 1;
        עבור (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            אם (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                اكسر;
            }
            אם (x[a+i & MASK] > th[i]) اكسر;
        }
        אם (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) اكسر;
        /* FIXME: find a way to compute optimal sh */
        אם (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        עבור (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            אם (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        אם (carry) {
            אם ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } אחרת x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    עבור (y=i=0; i<LD_B1B_DIG; i++) {
        אם ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    אם (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        אם (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    אם (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    אם ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        אם (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        אחרת אם (t > 500000000)
            frac += 0.75*sign;
        אחרת אם (t == 500000000) {
            אם ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            אחרת
                frac += 0.75*sign;
        }
        אם (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    אם ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        אם (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            אם (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        אם (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    החזר scalbn(y, e2);
}

ساكن مزدوج hexfloat(FFFILE *f, صحيح bits, صحيح emin, صحيح sign, صحيح pok)
{
    uint32_t x = 0;
    مزدوج y = 0;
    مزدوج scale = 1;
    مزدوج bias = 0;
    صحيح gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    صحيح d;
    صحيح c;

    c = shgetc(f);

    /* Skip leading zeros */
    עבור (; c=='0'; c = shgetc(f))
        gotdig = 1;

    אם (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        עבור (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    עבור (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        אם (c=='.') {
            אם (gotrad) اكسر;
            rp = dc;
            gotrad = 1;
        } אחרת {
            gotdig = 1;
            אם (c > '9') d = (c|32)+10-'a';
            אחרת d = c-'0';
            אם (dc<8) {
                x = x*16 + d;
            } אחרת אם (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } אחרת אם (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    אם (!gotdig) {
        shunget(f);
        אם (pok) {
            shunget(f);
            אם (gotrad) shunget(f);
        } אחרת {
            shlim(f, 0);
        }
        החזר sign * 0.0;
    }
    אם (!gotrad) rp = dc;
    כלעוד (dc<8) x *= 16, dc++;
    אם ((c|32)=='p') {
        e2 = scanexp(f, pok);
        אם (e2 == LLONG_MIN) {
            אם (pok) {
                shunget(f);
            } אחרת {
                shlim(f, 0);
                החזר 0;
            }
            e2 = 0;
        }
    } אחרת {
        shunget(f);
    }
    e2 += 4*rp - 32;

    אם (!x) החזר sign * 0.0;
    אם (e2 > -emin) {
        errno = ERANGE;
        החזר sign * DBL_MAX * DBL_MAX;
    }
    אם (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        החזר sign * DBL_MIN * DBL_MIN;
    }

    כלעוד (x < 0x80000000) {
        אם (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } אחרת {
            x += x;
            y += y;
        }
        e2--;
    }

    אם (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        אם (bits<0) bits=0;
    }

    אם (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    אם (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(مزدوج)x + sign*y;
    y -= bias;

    אם (!y) errno = ERANGE;

    החזר scalbn(y, e2);
}

ساكن مزدوج fffloatscan(FFFILE *f, صحيح prec, صحيح pok)
{
    صحيح sign = 1;
    size_t i;
    صحيح bits;
    صحيح emin;
    صحيح c;

    بدل (prec) {
    حالة 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        اكسر;
    حالة 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        اكسر;
    حالة 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        اكسر;
    افتراضي:
        החזר 0;
    }

    כלעוד (av_isspace((c = shgetc(f))));

    אם (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    עבור (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        אם (i<7) c = shgetc(f);
    אם (i==3 || i==8 || (i>3 && pok)) {
        אם (i!=8) {
            shunget(f);
            אם (pok) עבור (; i>3; i--) shunget(f);
        }
        החזר sign * INFINITY;
    }
    אם (!i) עבור (i=0; i<3 && (c|32)=="nan"[i]; i++)
        אם (i<2) c = shgetc(f);
    אם (i==3) {
        אם (shgetc(f) != '(') {
            shunget(f);
            החזר NAN;
        }
        עבור (i=1; ; i++) {
            c = shgetc(f);
            אם (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                استمر;
            אם (c==')') החזר NAN;
            shunget(f);
            אם (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                החזר 0;
            }
            כלעוד (i--) shunget(f);
            החזר NAN;
        }
    }

    אם (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        החזר 0;
    }

    אם (c=='0') {
        c = shgetc(f);
        אם ((c|32) == 'x')
            החזר hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    החזר decfloat(f, c, bits, emin, sign, pok);
}

ساكن فراغ *arg_n(va_list ap, unsigned صحيح n)
{
    فراغ *p;
    unsigned صحيح i;
    va_list ap2;
    va_copy(ap2, ap);
    עבור (i=n; i>1; i--) va_arg(ap2, فراغ *);
    p = va_arg(ap2, فراغ *);
    va_end(ap2);
    החזר p;
}

ساكن فراغ store_int(فراغ *dest, صحيح size, unsigned long long i)
{
    אם (!dest) החזר;
    بدل (size) {
    حالة SIZE_hh:
        *(حرف *)dest = i;
        اكسر;
    حالة SIZE_h:
        *(short *)dest = i;
        اكسر;
    حالة SIZE_def:
        *(صحيح *)dest = i;
        اكسر;
    حالة SIZE_l:
        *(long *)dest = i;
        اكسر;
    حالة SIZE_ll:
        *(long long *)dest = i;
        اكسر;
    }
}

ساكن صحيح ff_vfscanf(FFFILE *f, ثابت حرف *fmt, va_list ap)
{
    صحيح width;
    صحيح size;
    صحيح base;
    ثابت unsigned حرف *p;
    صحيح c, t;
    حرف *s;
    فراغ *dest=عدم;
    صحيح invert;
    صحيح matches=0;
    unsigned long long x;
    مزدوج y;
    ptrdiff_t pos = 0;
    unsigned حرف scanset[257];
    size_t i;

    עבור (p=(ثابت unsigned حرف *)fmt; *p; p++) {

        אם (av_isspace(*p)) {
            כלעוד (av_isspace(p[1])) p++;
            shlim(f, 0);
            כלעוד (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            استمر;
        }
        אם (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            אם (*p == '%') {
                p++;
                כלעוד (av_isspace((c=shgetc(f))));
            } אחרת {
                c = shgetc(f);
            }
            אם (c!=*p) {
                shunget(f);
                אם (c<0) اذهب input_fail;
                اذهب match_fail;
            }
            pos += shcnt(f);
            استمر;
        }

        p++;
        אם (*p=='*') {
            dest = 0; p++;
        } אחרת אם (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } אחרת {
            dest = va_arg(ap, فراغ *);
        }

        עבור (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        אם (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        بدل (*p++) {
        حالة 'h':
            אם (*p == 'h') p++, size = SIZE_hh;
            אחרת size = SIZE_h;
            اكسر;
        حالة 'l':
            אם (*p == 'l') p++, size = SIZE_ll;
            אחרת size = SIZE_l;
            اكسر;
        حالة 'j':
            size = SIZE_ll;
            اكسر;
        حالة 'z':
        حالة 't':
            size = SIZE_l;
            اكسر;
        حالة 'L':
            size = SIZE_L;
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
        אם ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        بدل (t) {
            حالة 'c':
                אם (width < 1) width = 1;
                اكسر;
            حالة '[':
                اكسر;
            حالة 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                استمر;
            افتراضي:
                shlim(f, 0);
                כלעוד (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        אם (shgetc(f) < 0) اذهب input_fail;
        shunget(f);

        بدل (t) {
            حالة 's':
            حالة 'c':
            حالة '[':
                אם (t == 'c' || t == 's') {
                    memset(scanset, -1, حجم scanset);
                    scanset[0] = 0;
                    אם (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } אחרת {
                    אם (*++p == '^') p++, invert = 1;
                    אחרת invert = 0;
                    memset(scanset, invert, حجم scanset);
                    scanset[0] = 0;
                    אם (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    אחרת אם (*p == ']') p++, scanset[1+']'] = 1-invert;
                    עבור (; *p != ']'; p++) {
                        אם (!*p) اذهب fmt_fail;
                        אם (*p=='-' && p[1] && p[1] != ']')
                            עבור (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                אם ((s = dest)) {
                    כלעוד (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } אחרת {
                    כלעוד (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                אם (!shcnt(f)) اذهب match_fail;
                אם (t == 'c' && shcnt(f) != width) اذهب match_fail;
                אם (t != 'c') {
                    אם (s) s[i] = 0;
                }
                اكسر;
            حالة 'p':
            حالة 'X':
            حالة 'x':
                base = 16;
                اذهب int_common;
            حالة 'o':
                base = 8;
                اذهب int_common;
            حالة 'd':
            حالة 'u':
                base = 10;
                اذهب int_common;
            حالة 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                אם (!shcnt(f))
                    اذهب match_fail;
                אם (t=='p' && dest)
                    *(فراغ **)dest = (فراغ *)(uintptr_t)x;
                אחרת
                    store_int(dest, size, x);
                اكسر;
            حالة 'a': حالة 'A':
            حالة 'e': حالة 'E':
            حالة 'f': حالة 'F':
            حالة 'g': حالة 'G':
                y = fffloatscan(f, size, 0);
                אם (!shcnt(f))
                    اذهب match_fail;
                אם (dest) {
                    بدل (size) {
                    حالة SIZE_def:
                        *(عائم *)dest = y;
                        اكسر;
                    حالة SIZE_l:
                        *(مزدوج *)dest = y;
                        اكسر;
                    حالة SIZE_L:
                        *(مزدوج *)dest = y;
                        اكسر;
                    }
                }
                اكسر;
        }

        pos += shcnt(f);
        אם (dest) matches++;
    }
    אם (0) {
fmt_fail:
input_fail:
        אם (!matches) matches--;
    }
match_fail:
    החזר matches;
}

ساكن صحيح ff_vsscanf(ثابت حرف *s, ثابت حرف *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (فراغ *)s, .cookie = (فراغ *)s,
        .اقرأ = ffstring_read,
    };

    החזר ff_vfscanf(&f, fmt, ap);
}

صحيح av_sscanf(ثابت حرف *string, ثابت حرف *format, ...)
{
    صحيح ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    החזר ret;
}
