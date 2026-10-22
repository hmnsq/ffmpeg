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

تعریفنوع ساختار FFFILE {
    size_t buf_size;
    unsigned نویسه *buf;
    unsigned نویسه *rpos, *rend;
    unsigned نویسه *shend;
    ptrdiff_t shlim, shcnt;
    تهی *cookie;
    size_t (*اقرأ)(ساختار FFFILE *, unsigned نویسه *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ایستا صحیح fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    بازگشت 0;
}

ایستا size_t ffstring_read(FFFILE *f, unsigned نویسه *buf, size_t len)
{
    نویسه *src = f->cookie;
    size_t k = len+256;
    نویسه *end = memchr(src, 0, k);

    اگر (end) k = end-src;
    اگر (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (تهی *)(src+len);
    f->rend = (تهی *)(src+k);
    f->cookie = src+k;

    بازگشت len;
}

ایستا صحیح ffuflow(FFFILE *f)
{
    unsigned نویسه c;
    اگر (!fftoread(f) && f->اقرأ(f, &c, 1)==1) بازگشت c;
    بازگشت EOF;
}

ایستا تهی ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    اگر (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    وگرنه
        f->shend = f->rend;
}

ایستا صحیح ffshgetc(FFFILE *f)
{
    صحیح c;
    ptrdiff_t cnt = shcnt(f);
    اگر (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        بازگشت EOF;
    }
    cnt++;
    اگر (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    وگرنه
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    اگر (f->rpos[-1] != c) f->rpos[-1] = c;
    بازگشت c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (تهی)(f)->rpos-- : (تهی)0)

ایستا ثابت unsigned نویسه table[] = { -1,
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

ایستا unsigned long long ffintscan(FFFILE *f, unsigned base, صحیح pok, unsigned long long lim)
{
    ثابت unsigned نویسه *val = table+1;
    صحیح c, neg=0;
    unsigned x;
    unsigned long long y;
    اگر (base > 36 || base == 1) {
        errno = EINVAL;
        بازگشت 0;
    }
    وقتی (av_isspace((c=shgetc(f))));
    اگر (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    اگر ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        اگر ((c|32)=='x') {
            c = shgetc(f);
            اگر (val[c]>=16) {
                shunget(f);
                اگر (pok) shunget(f);
                وگرنه shlim(f, 0);
                بازگشت 0;
            }
            base = 16;
        } وگرنه اگر (base == 0) {
            base = 8;
        }
    } وگرنه {
        اگر (base == 0) base = 10;
        اگر (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            بازگشت 0;
        }
    }
    اگر (base == 10) {
        برای (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        برای (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        اگر (c-'0'>=10U) برو done;
    } وگرنه اگر (!(base & base-1)) {
        صحیح bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        برای (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        برای (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } وگرنه {
        برای (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        برای (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    اگر (val[c]<base) {
        برای (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        اگر (lim&1) neg = 0;
    }
done:
    shunget(f);
    اگر (y>=lim) {
        اگر (!(lim&1) && !neg) {
            errno = ERANGE;
            بازگشت lim-1;
        } وگرنه اگر (y>lim) {
            errno = ERANGE;
            بازگشت lim;
        }
    }
    بازگشت (y^neg)-neg;
}

ایستا long long scanexp(FFFILE *f, صحیح pok)
{
    صحیح c;
    صحیح x;
    long long y;
    صحیح neg = 0;

    c = shgetc(f);
    اگر (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        اگر (c-'0'>=10U && pok) shunget(f);
    }
    اگر (c-'0'>=10U) {
        shunget(f);
        بازگشت LLONG_MIN;
    }
    برای (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    برای (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    برای (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    بازگشت neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

ایستا دوگانه decfloat(FFFILE *f, صحیح c, صحیح bits, صحیح emin, صحیح sign, صحیح pok)
{
    uint32_t x[KMAX];
    ایستا ثابت uint32_t th[] = { LD_B1B_MAX };
    صحیح i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    صحیح lnz = 0;
    صحیح gotdig = 0, gotrad = 0;
    صحیح rp;
    صحیح e2;
    صحیح emax = -emin-bits+3;
    صحیح denormal = 0;
    دوگانه y;
    دوگانه frac=0;
    دوگانه bias=0;
    ایستا ثابت صحیح p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    برای (; c=='0'; c = shgetc(f)) gotdig=1;
    اگر (c=='.') {
        gotrad = 1;
        برای (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    برای (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        اگر (c == '.') {
            اگر (gotrad) بشکن;
            gotrad = 1;
            lrp = dc;
        } وگرنه اگر (k < KMAX-3) {
            dc++;
            اگر (c!='0') lnz = dc;
            اگر (j) x[k] = x[k]*10 + c-'0';
            وگرنه x[k] = c-'0';
            اگر (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } وگرنه {
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
            } وگرنه {
                shlim(f, 0);
                بازگشت 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } وگرنه اگر (c>=0) {
        shunget(f);
    }
    اگر (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        بازگشت 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    اگر (!x[0]) بازگشت sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    اگر (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        بازگشت sign * (دوگانه)x[0];
    اگر (lrp > -emin/2) {
        errno = ERANGE;
        بازگشت sign * DBL_MAX * DBL_MAX;
    }
    اگر (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        بازگشت sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    اگر (j) {
        برای (; j<9; j++) x[k]*=10;
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
        اگر (rp == 9) بازگشت sign * (دوگانه)x[0];
        اگر (rp < 9) بازگشت sign * (دوگانه)x[0] / p10s[8-rp];
        bitlim = bits-3*(صحیح)(rp-9);
        اگر (bitlim>30 || x[0]>>bitlim==0)
            بازگشت sign * (دوگانه)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    برای (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    اگر (rp % 9) {
        صحیح rpm9 = rp>=0 ? rp%9 : rp%9+9;
        صحیح p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        برای (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            اگر (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        اگر (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    وقتی (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        برای (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            اگر (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } وگرنه {
                carry = 0;
                x[k] = tmp;
            }
            اگر (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            اگر (k==a) بشکن;
        }
        اگر (carry) {
            rp += 9;
            a = (a-1 & MASK);
            اگر (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    برای (;;) {
        uint32_t carry = 0;
        صحیح sh = 1;
        برای (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            اگر (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                بشکن;
            }
            اگر (x[a+i & MASK] > th[i]) بشکن;
        }
        اگر (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) بشکن;
        /* FIXME: find a way to compute optimal sh */
        اگر (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        برای (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            اگر (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        اگر (carry) {
            اگر ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } وگرنه x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    برای (y=i=0; i<LD_B1B_DIG; i++) {
        اگر ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    اگر (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        اگر (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    اگر (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    اگر ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        اگر (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        وگرنه اگر (t > 500000000)
            frac += 0.75*sign;
        وگرنه اگر (t == 500000000) {
            اگر ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            وگرنه
                frac += 0.75*sign;
        }
        اگر (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    اگر ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        اگر (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            اگر (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        اگر (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    بازگشت scalbn(y, e2);
}

ایستا دوگانه hexfloat(FFFILE *f, صحیح bits, صحیح emin, صحیح sign, صحیح pok)
{
    uint32_t x = 0;
    دوگانه y = 0;
    دوگانه scale = 1;
    دوگانه bias = 0;
    صحیح gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    صحیح d;
    صحیح c;

    c = shgetc(f);

    /* Skip leading zeros */
    برای (; c=='0'; c = shgetc(f))
        gotdig = 1;

    اگر (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        برای (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    برای (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        اگر (c=='.') {
            اگر (gotrad) بشکن;
            rp = dc;
            gotrad = 1;
        } وگرنه {
            gotdig = 1;
            اگر (c > '9') d = (c|32)+10-'a';
            وگرنه d = c-'0';
            اگر (dc<8) {
                x = x*16 + d;
            } وگرنه اگر (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } وگرنه اگر (d && !gottail) {
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
        } وگرنه {
            shlim(f, 0);
        }
        بازگشت sign * 0.0;
    }
    اگر (!gotrad) rp = dc;
    وقتی (dc<8) x *= 16, dc++;
    اگر ((c|32)=='p') {
        e2 = scanexp(f, pok);
        اگر (e2 == LLONG_MIN) {
            اگر (pok) {
                shunget(f);
            } وگرنه {
                shlim(f, 0);
                بازگشت 0;
            }
            e2 = 0;
        }
    } وگرنه {
        shunget(f);
    }
    e2 += 4*rp - 32;

    اگر (!x) بازگشت sign * 0.0;
    اگر (e2 > -emin) {
        errno = ERANGE;
        بازگشت sign * DBL_MAX * DBL_MAX;
    }
    اگر (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        بازگشت sign * DBL_MIN * DBL_MIN;
    }

    وقتی (x < 0x80000000) {
        اگر (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } وگرنه {
            x += x;
            y += y;
        }
        e2--;
    }

    اگر (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        اگر (bits<0) bits=0;
    }

    اگر (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    اگر (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(دوگانه)x + sign*y;
    y -= bias;

    اگر (!y) errno = ERANGE;

    بازگشت scalbn(y, e2);
}

ایستا دوگانه fffloatscan(FFFILE *f, صحیح prec, صحیح pok)
{
    صحیح sign = 1;
    size_t i;
    صحیح bits;
    صحیح emin;
    صحیح c;

    انتخاب (prec) {
    حالت 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        بشکن;
    حالت 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        بشکن;
    حالت 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        بشکن;
    پیشفرض:
        بازگشت 0;
    }

    وقتی (av_isspace((c = shgetc(f))));

    اگر (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    برای (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        اگر (i<7) c = shgetc(f);
    اگر (i==3 || i==8 || (i>3 && pok)) {
        اگر (i!=8) {
            shunget(f);
            اگر (pok) برای (; i>3; i--) shunget(f);
        }
        بازگشت sign * INFINITY;
    }
    اگر (!i) برای (i=0; i<3 && (c|32)=="nan"[i]; i++)
        اگر (i<2) c = shgetc(f);
    اگر (i==3) {
        اگر (shgetc(f) != '(') {
            shunget(f);
            بازگشت NAN;
        }
        برای (i=1; ; i++) {
            c = shgetc(f);
            اگر (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ادامه;
            اگر (c==')') بازگشت NAN;
            shunget(f);
            اگر (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                بازگشت 0;
            }
            وقتی (i--) shunget(f);
            بازگشت NAN;
        }
    }

    اگر (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        بازگشت 0;
    }

    اگر (c=='0') {
        c = shgetc(f);
        اگر ((c|32) == 'x')
            بازگشت hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    بازگشت decfloat(f, c, bits, emin, sign, pok);
}

ایستا تهی *arg_n(va_list ap, unsigned صحیح n)
{
    تهی *p;
    unsigned صحیح i;
    va_list ap2;
    va_copy(ap2, ap);
    برای (i=n; i>1; i--) va_arg(ap2, تهی *);
    p = va_arg(ap2, تهی *);
    va_end(ap2);
    بازگشت p;
}

ایستا تهی store_int(تهی *dest, صحیح size, unsigned long long i)
{
    اگر (!dest) بازگشت;
    انتخاب (size) {
    حالت SIZE_hh:
        *(نویسه *)dest = i;
        بشکن;
    حالت SIZE_h:
        *(short *)dest = i;
        بشکن;
    حالت SIZE_def:
        *(صحیح *)dest = i;
        بشکن;
    حالت SIZE_l:
        *(long *)dest = i;
        بشکن;
    حالت SIZE_ll:
        *(long long *)dest = i;
        بشکن;
    }
}

ایستا صحیح ff_vfscanf(FFFILE *f, ثابت نویسه *fmt, va_list ap)
{
    صحیح width;
    صحیح size;
    صحیح base;
    ثابت unsigned نویسه *p;
    صحیح c, t;
    نویسه *s;
    تهی *dest=پوچ;
    صحیح invert;
    صحیح matches=0;
    unsigned long long x;
    دوگانه y;
    ptrdiff_t pos = 0;
    unsigned نویسه scanset[257];
    size_t i;

    برای (p=(ثابت unsigned نویسه *)fmt; *p; p++) {

        اگر (av_isspace(*p)) {
            وقتی (av_isspace(p[1])) p++;
            shlim(f, 0);
            وقتی (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ادامه;
        }
        اگر (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            اگر (*p == '%') {
                p++;
                وقتی (av_isspace((c=shgetc(f))));
            } وگرنه {
                c = shgetc(f);
            }
            اگر (c!=*p) {
                shunget(f);
                اگر (c<0) برو درون_داد_fail;
                برو match_fail;
            }
            pos += shcnt(f);
            ادامه;
        }

        p++;
        اگر (*p=='*') {
            dest = 0; p++;
        } وگرنه اگر (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } وگرنه {
            dest = va_arg(ap, تهی *);
        }

        برای (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        اگر (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        انتخاب (*p++) {
        حالت 'h':
            اگر (*p == 'h') p++, size = SIZE_hh;
            وگرنه size = SIZE_h;
            بشکن;
        حالت 'l':
            اگر (*p == 'l') p++, size = SIZE_ll;
            وگرنه size = SIZE_l;
            بشکن;
        حالت 'j':
            size = SIZE_ll;
            بشکن;
        حالت 'z':
        حالت 't':
            size = SIZE_l;
            بشکن;
        حالت 'L':
            size = SIZE_L;
            بشکن;
        حالت 'd': حالت 'i': حالت 'o': حالت 'u': حالت 'x':
        حالت 'a': حالت 'e': حالت 'f': حالت 'g':
        حالت 'A': حالت 'E': حالت 'F': حالت 'G': حالت 'X':
        حالت 's': حالت 'c': حالت '[':
        حالت 'S': حالت 'C':
        حالت 'p': حالت 'n':
            p--;
            بشکن;
        پیشفرض:
            برو fmt_fail;
        }

        t = *p;

        /* C or S */
        اگر ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        انتخاب (t) {
            حالت 'c':
                اگر (width < 1) width = 1;
                بشکن;
            حالت '[':
                بشکن;
            حالت 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                ادامه;
            پیشفرض:
                shlim(f, 0);
                وقتی (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        اگر (shgetc(f) < 0) برو درون_داد_fail;
        shunget(f);

        انتخاب (t) {
            حالت 's':
            حالت 'c':
            حالت '[':
                اگر (t == 'c' || t == 's') {
                    memset(scanset, -1, اندازه scanset);
                    scanset[0] = 0;
                    اگر (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } وگرنه {
                    اگر (*++p == '^') p++, invert = 1;
                    وگرنه invert = 0;
                    memset(scanset, invert, اندازه scanset);
                    scanset[0] = 0;
                    اگر (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    وگرنه اگر (*p == ']') p++, scanset[1+']'] = 1-invert;
                    برای (; *p != ']'; p++) {
                        اگر (!*p) برو fmt_fail;
                        اگر (*p=='-' && p[1] && p[1] != ']')
                            برای (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                اگر ((s = dest)) {
                    وقتی (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } وگرنه {
                    وقتی (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                اگر (!shcnt(f)) برو match_fail;
                اگر (t == 'c' && shcnt(f) != width) برو match_fail;
                اگر (t != 'c') {
                    اگر (s) s[i] = 0;
                }
                بشکن;
            حالت 'p':
            حالت 'X':
            حالت 'x':
                base = 16;
                برو int_common;
            حالت 'o':
                base = 8;
                برو int_common;
            حالت 'd':
            حالت 'u':
                base = 10;
                برو int_common;
            حالت 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                اگر (!shcnt(f))
                    برو match_fail;
                اگر (t=='p' && dest)
                    *(تهی **)dest = (تهی *)(uintptr_t)x;
                وگرنه
                    store_int(dest, size, x);
                بشکن;
            حالت 'a': حالت 'A':
            حالت 'e': حالت 'E':
            حالت 'f': حالت 'F':
            حالت 'g': حالت 'G':
                y = fffloatscan(f, size, 0);
                اگر (!shcnt(f))
                    برو match_fail;
                اگر (dest) {
                    انتخاب (size) {
                    حالت SIZE_def:
                        *(اعشاری *)dest = y;
                        بشکن;
                    حالت SIZE_l:
                        *(دوگانه *)dest = y;
                        بشکن;
                    حالت SIZE_L:
                        *(دوگانه *)dest = y;
                        بشکن;
                    }
                }
                بشکن;
        }

        pos += shcnt(f);
        اگر (dest) matches++;
    }
    اگر (0) {
fmt_fail:
درون_داد_fail:
        اگر (!matches) matches--;
    }
match_fail:
    بازگشت matches;
}

ایستا صحیح ff_vsscanf(ثابت نویسه *s, ثابت نویسه *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (تهی *)s, .cookie = (تهی *)s,
        .اقرأ = ffstring_read,
    };

    بازگشت ff_vfscanf(&f, fmt, ap);
}

صحیح av_sscanf(ثابت نویسه *string, ثابت نویسه *format, ...)
{
    صحیح ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    بازگشت ret;
}
