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
    ܦܢܐ 0;
}

ساكن size_t ffstring_read(FFFILE *f, unsigned حرف *buf, size_t len)
{
    حرف *src = f->cookie;
    size_t k = len+256;
    حرف *end = memchr(src, 0, k);

    ܐܢ (end) k = end-src;
    ܐܢ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (فراغ *)(src+len);
    f->rend = (فراغ *)(src+k);
    f->cookie = src+k;

    ܦܢܐ len;
}

ساكن صحيح ffuflow(FFFILE *f)
{
    unsigned حرف c;
    ܐܢ (!fftoread(f) && f->اقرأ(f, &c, 1)==1) ܦܢܐ c;
    ܦܢܐ EOF;
}

ساكن فراغ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ܐܢ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ܐܚܪܢܐ
        f->shend = f->rend;
}

ساكن صحيح ffshgetc(FFFILE *f)
{
    صحيح c;
    ptrdiff_t cnt = shcnt(f);
    ܐܢ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ܦܢܐ EOF;
    }
    cnt++;
    ܐܢ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ܐܚܪܢܐ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ܐܢ (f->rpos[-1] != c) f->rpos[-1] = c;
    ܦܢܐ c;
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
    ܐܢ (base > 36 || base == 1) {
        errno = EINVAL;
        ܦܢܐ 0;
    }
    ܟܡܐ (av_isspace((c=shgetc(f))));
    ܐܢ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ܐܢ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ܐܢ ((c|32)=='x') {
            c = shgetc(f);
            ܐܢ (val[c]>=16) {
                shunget(f);
                ܐܢ (pok) shunget(f);
                ܐܚܪܢܐ shlim(f, 0);
                ܦܢܐ 0;
            }
            base = 16;
        } ܐܚܪܢܐ ܐܢ (base == 0) {
            base = 8;
        }
    } ܐܚܪܢܐ {
        ܐܢ (base == 0) base = 10;
        ܐܢ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ܦܢܐ 0;
        }
    }
    ܐܢ (base == 10) {
        لكل (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        لكل (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ܐܢ (c-'0'>=10U) اذهب done;
    } ܐܚܪܢܐ ܐܢ (!(base & base-1)) {
        صحيح bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        لكل (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        لكل (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ܐܚܪܢܐ {
        لكل (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        لكل (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ܐܢ (val[c]<base) {
        لكل (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ܐܢ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ܐܢ (y>=lim) {
        ܐܢ (!(lim&1) && !neg) {
            errno = ERANGE;
            ܦܢܐ lim-1;
        } ܐܚܪܢܐ ܐܢ (y>lim) {
            errno = ERANGE;
            ܦܢܐ lim;
        }
    }
    ܦܢܐ (y^neg)-neg;
}

ساكن long long scanexp(FFFILE *f, صحيح pok)
{
    صحيح c;
    صحيح x;
    long long y;
    صحيح neg = 0;

    c = shgetc(f);
    ܐܢ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ܐܢ (c-'0'>=10U && pok) shunget(f);
    }
    ܐܢ (c-'0'>=10U) {
        shunget(f);
        ܦܢܐ LLONG_MIN;
    }
    لكل (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    لكل (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    لكل (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ܦܢܐ neg ? -y : y;
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
    لكل (; c=='0'; c = shgetc(f)) gotdig=1;
    ܐܢ (c=='.') {
        gotrad = 1;
        لكل (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    لكل (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ܐܢ (c == '.') {
            ܐܢ (gotrad) اكسر;
            gotrad = 1;
            lrp = dc;
        } ܐܚܪܢܐ ܐܢ (k < KMAX-3) {
            dc++;
            ܐܢ (c!='0') lnz = dc;
            ܐܢ (j) x[k] = x[k]*10 + c-'0';
            ܐܚܪܢܐ x[k] = c-'0';
            ܐܢ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ܐܚܪܢܐ {
            dc++;
            ܐܢ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ܐܢ (!gotrad) lrp=dc;

    ܐܢ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ܐܢ (e10 == LLONG_MIN) {
            ܐܢ (pok) {
                shunget(f);
            } ܐܚܪܢܐ {
                shlim(f, 0);
                ܦܢܐ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ܐܚܪܢܐ ܐܢ (c>=0) {
        shunget(f);
    }
    ܐܢ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ܦܢܐ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ܐܢ (!x[0]) ܦܢܐ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ܐܢ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ܦܢܐ sign * (مزدوج)x[0];
    ܐܢ (lrp > -emin/2) {
        errno = ERANGE;
        ܦܢܐ sign * DBL_MAX * DBL_MAX;
    }
    ܐܢ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ܦܢܐ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ܐܢ (j) {
        لكل (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ܐܢ (lnz<9 && lnz<=rp && rp < 18) {
        صحيح bitlim;
        ܐܢ (rp == 9) ܦܢܐ sign * (مزدوج)x[0];
        ܐܢ (rp < 9) ܦܢܐ sign * (مزدوج)x[0] / p10s[8-rp];
        bitlim = bits-3*(صحيح)(rp-9);
        ܐܢ (bitlim>30 || x[0]>>bitlim==0)
            ܦܢܐ sign * (مزدوج)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    لكل (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ܐܢ (rp % 9) {
        صحيح rpm9 = rp>=0 ? rp%9 : rp%9+9;
        صحيح p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        لكل (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ܐܢ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ܐܢ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ܟܡܐ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        لكل (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ܐܢ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ܐܚܪܢܐ {
                carry = 0;
                x[k] = tmp;
            }
            ܐܢ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ܐܢ (k==a) اكسر;
        }
        ܐܢ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ܐܢ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    لكل (;;) {
        uint32_t carry = 0;
        صحيح sh = 1;
        لكل (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ܐܢ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                اكسر;
            }
            ܐܢ (x[a+i & MASK] > th[i]) اكسر;
        }
        ܐܢ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) اكسر;
        /* FIXME: find a way to compute optimal sh */
        ܐܢ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        لكل (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ܐܢ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ܐܢ (carry) {
            ܐܢ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ܐܚܪܢܐ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    لكل (y=i=0; i<LD_B1B_DIG; i++) {
        ܐܢ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ܐܢ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ܐܢ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ܐܢ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ܐܢ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ܐܢ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ܐܚܪܢܐ ܐܢ (t > 500000000)
            frac += 0.75*sign;
        ܐܚܪܢܐ ܐܢ (t == 500000000) {
            ܐܢ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ܐܚܪܢܐ
                frac += 0.75*sign;
        }
        ܐܢ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ܐܢ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ܐܢ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ܐܢ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ܐܢ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ܦܢܐ scalbn(y, e2);
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
    لكل (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ܐܢ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        لكل (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    لكل (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ܐܢ (c=='.') {
            ܐܢ (gotrad) اكسر;
            rp = dc;
            gotrad = 1;
        } ܐܚܪܢܐ {
            gotdig = 1;
            ܐܢ (c > '9') d = (c|32)+10-'a';
            ܐܚܪܢܐ d = c-'0';
            ܐܢ (dc<8) {
                x = x*16 + d;
            } ܐܚܪܢܐ ܐܢ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ܐܚܪܢܐ ܐܢ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ܐܢ (!gotdig) {
        shunget(f);
        ܐܢ (pok) {
            shunget(f);
            ܐܢ (gotrad) shunget(f);
        } ܐܚܪܢܐ {
            shlim(f, 0);
        }
        ܦܢܐ sign * 0.0;
    }
    ܐܢ (!gotrad) rp = dc;
    ܟܡܐ (dc<8) x *= 16, dc++;
    ܐܢ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ܐܢ (e2 == LLONG_MIN) {
            ܐܢ (pok) {
                shunget(f);
            } ܐܚܪܢܐ {
                shlim(f, 0);
                ܦܢܐ 0;
            }
            e2 = 0;
        }
    } ܐܚܪܢܐ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ܐܢ (!x) ܦܢܐ sign * 0.0;
    ܐܢ (e2 > -emin) {
        errno = ERANGE;
        ܦܢܐ sign * DBL_MAX * DBL_MAX;
    }
    ܐܢ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ܦܢܐ sign * DBL_MIN * DBL_MIN;
    }

    ܟܡܐ (x < 0x80000000) {
        ܐܢ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ܐܚܪܢܐ {
            x += x;
            y += y;
        }
        e2--;
    }

    ܐܢ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ܐܢ (bits<0) bits=0;
    }

    ܐܢ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ܐܢ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(مزدوج)x + sign*y;
    y -= bias;

    ܐܢ (!y) errno = ERANGE;

    ܦܢܐ scalbn(y, e2);
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
        ܦܢܐ 0;
    }

    ܟܡܐ (av_isspace((c = shgetc(f))));

    ܐܢ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    لكل (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ܐܢ (i<7) c = shgetc(f);
    ܐܢ (i==3 || i==8 || (i>3 && pok)) {
        ܐܢ (i!=8) {
            shunget(f);
            ܐܢ (pok) لكل (; i>3; i--) shunget(f);
        }
        ܦܢܐ sign * INFINITY;
    }
    ܐܢ (!i) لكل (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ܐܢ (i<2) c = shgetc(f);
    ܐܢ (i==3) {
        ܐܢ (shgetc(f) != '(') {
            shunget(f);
            ܦܢܐ NAN;
        }
        لكل (i=1; ; i++) {
            c = shgetc(f);
            ܐܢ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                استمر;
            ܐܢ (c==')') ܦܢܐ NAN;
            shunget(f);
            ܐܢ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ܦܢܐ 0;
            }
            ܟܡܐ (i--) shunget(f);
            ܦܢܐ NAN;
        }
    }

    ܐܢ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ܦܢܐ 0;
    }

    ܐܢ (c=='0') {
        c = shgetc(f);
        ܐܢ ((c|32) == 'x')
            ܦܢܐ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ܦܢܐ decfloat(f, c, bits, emin, sign, pok);
}

ساكن فراغ *arg_n(va_list ap, unsigned صحيح n)
{
    فراغ *p;
    unsigned صحيح i;
    va_list ap2;
    va_copy(ap2, ap);
    لكل (i=n; i>1; i--) va_arg(ap2, فراغ *);
    p = va_arg(ap2, فراغ *);
    va_end(ap2);
    ܦܢܐ p;
}

ساكن فراغ store_int(فراغ *dest, صحيح size, unsigned long long i)
{
    ܐܢ (!dest) ܦܢܐ;
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

    لكل (p=(ثابت unsigned حرف *)fmt; *p; p++) {

        ܐܢ (av_isspace(*p)) {
            ܟܡܐ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ܟܡܐ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            استمر;
        }
        ܐܢ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ܐܢ (*p == '%') {
                p++;
                ܟܡܐ (av_isspace((c=shgetc(f))));
            } ܐܚܪܢܐ {
                c = shgetc(f);
            }
            ܐܢ (c!=*p) {
                shunget(f);
                ܐܢ (c<0) اذهب input_fail;
                اذهب match_fail;
            }
            pos += shcnt(f);
            استمر;
        }

        p++;
        ܐܢ (*p=='*') {
            dest = 0; p++;
        } ܐܚܪܢܐ ܐܢ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ܐܚܪܢܐ {
            dest = va_arg(ap, فراغ *);
        }

        لكل (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ܐܢ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        بدل (*p++) {
        حالة 'h':
            ܐܢ (*p == 'h') p++, size = SIZE_hh;
            ܐܚܪܢܐ size = SIZE_h;
            اكسر;
        حالة 'l':
            ܐܢ (*p == 'l') p++, size = SIZE_ll;
            ܐܚܪܢܐ size = SIZE_l;
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
        ܐܢ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        بدل (t) {
            حالة 'c':
                ܐܢ (width < 1) width = 1;
                اكسر;
            حالة '[':
                اكسر;
            حالة 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                استمر;
            افتراضي:
                shlim(f, 0);
                ܟܡܐ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ܐܢ (shgetc(f) < 0) اذهب input_fail;
        shunget(f);

        بدل (t) {
            حالة 's':
            حالة 'c':
            حالة '[':
                ܐܢ (t == 'c' || t == 's') {
                    memset(scanset, -1, حجم scanset);
                    scanset[0] = 0;
                    ܐܢ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ܐܚܪܢܐ {
                    ܐܢ (*++p == '^') p++, invert = 1;
                    ܐܚܪܢܐ invert = 0;
                    memset(scanset, invert, حجم scanset);
                    scanset[0] = 0;
                    ܐܢ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ܐܚܪܢܐ ܐܢ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    لكل (; *p != ']'; p++) {
                        ܐܢ (!*p) اذهب fmt_fail;
                        ܐܢ (*p=='-' && p[1] && p[1] != ']')
                            لكل (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ܐܢ ((s = dest)) {
                    ܟܡܐ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ܐܚܪܢܐ {
                    ܟܡܐ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ܐܢ (!shcnt(f)) اذهب match_fail;
                ܐܢ (t == 'c' && shcnt(f) != width) اذهب match_fail;
                ܐܢ (t != 'c') {
                    ܐܢ (s) s[i] = 0;
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
                ܐܢ (!shcnt(f))
                    اذهب match_fail;
                ܐܢ (t=='p' && dest)
                    *(فراغ **)dest = (فراغ *)(uintptr_t)x;
                ܐܚܪܢܐ
                    store_int(dest, size, x);
                اكسر;
            حالة 'a': حالة 'A':
            حالة 'e': حالة 'E':
            حالة 'f': حالة 'F':
            حالة 'g': حالة 'G':
                y = fffloatscan(f, size, 0);
                ܐܢ (!shcnt(f))
                    اذهب match_fail;
                ܐܢ (dest) {
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
        ܐܢ (dest) matches++;
    }
    ܐܢ (0) {
fmt_fail:
input_fail:
        ܐܢ (!matches) matches--;
    }
match_fail:
    ܦܢܐ matches;
}

ساكن صحيح ff_vsscanf(ثابت حرف *s, ثابت حرف *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (فراغ *)s, .cookie = (فراغ *)s,
        .اقرأ = ffstring_read,
    };

    ܦܢܐ ff_vfscanf(&f, fmt, ap);
}

صحيح av_sscanf(ثابت حرف *string, ثابت حرف *format, ...)
{
    صحيح ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ܦܢܐ ret;
}
