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

#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <math.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <float.h>

#অন্তর্ভাব "avstring.h"

প্রকারলেখ কাঠামো FFFILE {
    size_t buf_আকার;
    unsigned অক্ষর *buf;
    unsigned অক্ষর *rpos, *rend;
    unsigned অক্ষর *shend;
    ptrdiff_t shlim, shcnt;
    শূন্য *cookie;
    size_t (*পঠ)(কাঠামো FFFILE *, unsigned অক্ষর *, size_t);
} FFFILE;

#define আকার_hh -2
#define আকার_h  -1
#define আকার_def 0
#define আকার_l   1
#define আকার_L   2
#define আকার_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

স্থির পূর্ণসংখ্যা fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_আকার;
    ফেরত 0;
}

স্থির size_t ffstring_read(FFFILE *f, unsigned অক্ষর *buf, size_t len)
{
    অক্ষর *src = f->cookie;
    size_t k = len+256;
    অক্ষর *end = memchr(src, 0, k);

    যদি (end) k = end-src;
    যদি (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (শূন্য *)(src+len);
    f->rend = (শূন্য *)(src+k);
    f->cookie = src+k;

    ফেরত len;
}

স্থির পূর্ণসংখ্যা ffuflow(FFFILE *f)
{
    unsigned অক্ষর c;
    যদি (!fftoread(f) && f->পঠ(f, &c, 1)==1) ফেরত c;
    ফেরত EOF;
}

স্থির শূন্য ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    যদি (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    অন্যথা
        f->shend = f->rend;
}

স্থির পূর্ণসংখ্যা ffshgetc(FFFILE *f)
{
    পূর্ণসংখ্যা c;
    ptrdiff_t cnt = shcnt(f);
    যদি (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ফেরত EOF;
    }
    cnt++;
    যদি (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    অন্যথা
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    যদি (f->rpos[-1] != c) f->rpos[-1] = c;
    ফেরত c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (শূন্য)(f)->rpos-- : (শূন্য)0)

স্থির ধ্রুবক unsigned অক্ষর table[] = { -1,
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

স্থির unsigned long long ffintscan(FFFILE *f, unsigned base, পূর্ণসংখ্যা pok, unsigned long long lim)
{
    ধ্রুবক unsigned অক্ষর *val = table+1;
    পূর্ণসংখ্যা c, neg=0;
    unsigned x;
    unsigned long long y;
    যদি (base > 36 || base == 1) {
        errno = EINVAL;
        ফেরত 0;
    }
    যখন (av_isspace((c=shgetc(f))));
    যদি (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    যদি ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        যদি ((c|32)=='x') {
            c = shgetc(f);
            যদি (val[c]>=16) {
                shunget(f);
                যদি (pok) shunget(f);
                অন্যথা shlim(f, 0);
                ফেরত 0;
            }
            base = 16;
        } অন্যথা যদি (base == 0) {
            base = 8;
        }
    } অন্যথা {
        যদি (base == 0) base = 10;
        যদি (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ফেরত 0;
        }
    }
    যদি (base == 10) {
        জন্য (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        জন্য (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        যদি (c-'0'>=10U) যাও done;
    } অন্যথা যদি (!(base & base-1)) {
        পূর্ণসংখ্যা bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        জন্য (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        জন্য (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } অন্যথা {
        জন্য (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        জন্য (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    যদি (val[c]<base) {
        জন্য (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        যদি (lim&1) neg = 0;
    }
done:
    shunget(f);
    যদি (y>=lim) {
        যদি (!(lim&1) && !neg) {
            errno = ERANGE;
            ফেরত lim-1;
        } অন্যথা যদি (y>lim) {
            errno = ERANGE;
            ফেরত lim;
        }
    }
    ফেরত (y^neg)-neg;
}

স্থির long long scanexp(FFFILE *f, পূর্ণসংখ্যা pok)
{
    পূর্ণসংখ্যা c;
    পূর্ণসংখ্যা x;
    long long y;
    পূর্ণসংখ্যা neg = 0;

    c = shgetc(f);
    যদি (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        যদি (c-'0'>=10U && pok) shunget(f);
    }
    যদি (c-'0'>=10U) {
        shunget(f);
        ফেরত LLONG_MIN;
    }
    জন্য (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    জন্য (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    জন্য (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ফেরত neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

স্থির দ্বিগুণ decfloat(FFFILE *f, পূর্ণসংখ্যা c, পূর্ণসংখ্যা bits, পূর্ণসংখ্যা emin, পূর্ণসংখ্যা sign, পূর্ণসংখ্যা pok)
{
    uint32_t x[KMAX];
    স্থির ধ্রুবক uint32_t th[] = { LD_B1B_MAX };
    পূর্ণসংখ্যা i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    পূর্ণসংখ্যা lnz = 0;
    পূর্ণসংখ্যা gotdig = 0, gotrad = 0;
    পূর্ণসংখ্যা rp;
    পূর্ণসংখ্যা e2;
    পূর্ণসংখ্যা emax = -emin-bits+3;
    পূর্ণসংখ্যা denormal = 0;
    দ্বিগুণ y;
    দ্বিগুণ frac=0;
    দ্বিগুণ bias=0;
    স্থির ধ্রুবক পূর্ণসংখ্যা p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    জন্য (; c=='0'; c = shgetc(f)) gotdig=1;
    যদি (c=='.') {
        gotrad = 1;
        জন্য (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    জন্য (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        যদি (c == '.') {
            যদি (gotrad) বিরতি;
            gotrad = 1;
            lrp = dc;
        } অন্যথা যদি (k < KMAX-3) {
            dc++;
            যদি (c!='0') lnz = dc;
            যদি (j) x[k] = x[k]*10 + c-'0';
            অন্যথা x[k] = c-'0';
            যদি (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } অন্যথা {
            dc++;
            যদি (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    যদি (!gotrad) lrp=dc;

    যদি (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        যদি (e10 == LLONG_MIN) {
            যদি (pok) {
                shunget(f);
            } অন্যথা {
                shlim(f, 0);
                ফেরত 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } অন্যথা যদি (c>=0) {
        shunget(f);
    }
    যদি (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ফেরত 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    যদি (!x[0]) ফেরত sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    যদি (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ফেরত sign * (দ্বিগুণ)x[0];
    যদি (lrp > -emin/2) {
        errno = ERANGE;
        ফেরত sign * DBL_MAX * DBL_MAX;
    }
    যদি (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ফেরত sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    যদি (j) {
        জন্য (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    যদি (lnz<9 && lnz<=rp && rp < 18) {
        পূর্ণসংখ্যা bitlim;
        যদি (rp == 9) ফেরত sign * (দ্বিগুণ)x[0];
        যদি (rp < 9) ফেরত sign * (দ্বিগুণ)x[0] / p10s[8-rp];
        bitlim = bits-3*(পূর্ণসংখ্যা)(rp-9);
        যদি (bitlim>30 || x[0]>>bitlim==0)
            ফেরত sign * (দ্বিগুণ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    জন্য (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    যদি (rp % 9) {
        পূর্ণসংখ্যা rpm9 = rp>=0 ? rp%9 : rp%9+9;
        পূর্ণসংখ্যা p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        জন্য (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            যদি (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        যদি (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    যখন (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        জন্য (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            যদি (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } অন্যথা {
                carry = 0;
                x[k] = tmp;
            }
            যদি (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            যদি (k==a) বিরতি;
        }
        যদি (carry) {
            rp += 9;
            a = (a-1 & MASK);
            যদি (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    জন্য (;;) {
        uint32_t carry = 0;
        পূর্ণসংখ্যা sh = 1;
        জন্য (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            যদি (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                বিরতি;
            }
            যদি (x[a+i & MASK] > th[i]) বিরতি;
        }
        যদি (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) বিরতি;
        /* FIXME: find a way to compute optimal sh */
        যদি (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        জন্য (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            যদি (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        যদি (carry) {
            যদি ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } অন্যথা x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    জন্য (y=i=0; i<LD_B1B_DIG; i++) {
        যদি ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    যদি (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        যদি (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    যদি (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    যদি ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        যদি (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        অন্যথা যদি (t > 500000000)
            frac += 0.75*sign;
        অন্যথা যদি (t == 500000000) {
            যদি ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            অন্যথা
                frac += 0.75*sign;
        }
        যদি (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    যদি ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        যদি (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            যদি (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        যদি (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ফেরত scalbn(y, e2);
}

স্থির দ্বিগুণ hexfloat(FFFILE *f, পূর্ণসংখ্যা bits, পূর্ণসংখ্যা emin, পূর্ণসংখ্যা sign, পূর্ণসংখ্যা pok)
{
    uint32_t x = 0;
    দ্বিগুণ y = 0;
    দ্বিগুণ scale = 1;
    দ্বিগুণ bias = 0;
    পূর্ণসংখ্যা gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    পূর্ণসংখ্যা d;
    পূর্ণসংখ্যা c;

    c = shgetc(f);

    /* Skip leading zeros */
    জন্য (; c=='0'; c = shgetc(f))
        gotdig = 1;

    যদি (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        জন্য (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    জন্য (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        যদি (c=='.') {
            যদি (gotrad) বিরতি;
            rp = dc;
            gotrad = 1;
        } অন্যথা {
            gotdig = 1;
            যদি (c > '9') d = (c|32)+10-'a';
            অন্যথা d = c-'0';
            যদি (dc<8) {
                x = x*16 + d;
            } অন্যথা যদি (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } অন্যথা যদি (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    যদি (!gotdig) {
        shunget(f);
        যদি (pok) {
            shunget(f);
            যদি (gotrad) shunget(f);
        } অন্যথা {
            shlim(f, 0);
        }
        ফেরত sign * 0.0;
    }
    যদি (!gotrad) rp = dc;
    যখন (dc<8) x *= 16, dc++;
    যদি ((c|32)=='p') {
        e2 = scanexp(f, pok);
        যদি (e2 == LLONG_MIN) {
            যদি (pok) {
                shunget(f);
            } অন্যথা {
                shlim(f, 0);
                ফেরত 0;
            }
            e2 = 0;
        }
    } অন্যথা {
        shunget(f);
    }
    e2 += 4*rp - 32;

    যদি (!x) ফেরত sign * 0.0;
    যদি (e2 > -emin) {
        errno = ERANGE;
        ফেরত sign * DBL_MAX * DBL_MAX;
    }
    যদি (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ফেরত sign * DBL_MIN * DBL_MIN;
    }

    যখন (x < 0x80000000) {
        যদি (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } অন্যথা {
            x += x;
            y += y;
        }
        e2--;
    }

    যদি (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        যদি (bits<0) bits=0;
    }

    যদি (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    যদি (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(দ্বিগুণ)x + sign*y;
    y -= bias;

    যদি (!y) errno = ERANGE;

    ফেরত scalbn(y, e2);
}

স্থির দ্বিগুণ fffloatscan(FFFILE *f, পূর্ণসংখ্যা prec, পূর্ণসংখ্যা pok)
{
    পূর্ণসংখ্যা sign = 1;
    size_t i;
    পূর্ণসংখ্যা bits;
    পূর্ণসংখ্যা emin;
    পূর্ণসংখ্যা c;

    নির্বাচন (prec) {
    ক্ষেত্র 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        বিরতি;
    ক্ষেত্র 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        বিরতি;
    ক্ষেত্র 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        বিরতি;
    পূর্বনির্ধারিত:
        ফেরত 0;
    }

    যখন (av_isspace((c = shgetc(f))));

    যদি (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    জন্য (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        যদি (i<7) c = shgetc(f);
    যদি (i==3 || i==8 || (i>3 && pok)) {
        যদি (i!=8) {
            shunget(f);
            যদি (pok) জন্য (; i>3; i--) shunget(f);
        }
        ফেরত sign * INFINITY;
    }
    যদি (!i) জন্য (i=0; i<3 && (c|32)=="nan"[i]; i++)
        যদি (i<2) c = shgetc(f);
    যদি (i==3) {
        যদি (shgetc(f) != '(') {
            shunget(f);
            ফেরত NAN;
        }
        জন্য (i=1; ; i++) {
            c = shgetc(f);
            যদি (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                চালু;
            যদি (c==')') ফেরত NAN;
            shunget(f);
            যদি (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ফেরত 0;
            }
            যখন (i--) shunget(f);
            ফেরত NAN;
        }
    }

    যদি (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ফেরত 0;
    }

    যদি (c=='0') {
        c = shgetc(f);
        যদি ((c|32) == 'x')
            ফেরত hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ফেরত decfloat(f, c, bits, emin, sign, pok);
}

স্থির শূন্য *arg_n(va_list ap, unsigned পূর্ণসংখ্যা n)
{
    শূন্য *p;
    unsigned পূর্ণসংখ্যা i;
    va_list ap2;
    va_copy(ap2, ap);
    জন্য (i=n; i>1; i--) va_arg(ap2, শূন্য *);
    p = va_arg(ap2, শূন্য *);
    va_end(ap2);
    ফেরত p;
}

স্থির শূন্য store_int(শূন্য *dest, পূর্ণসংখ্যা আকার_2, unsigned long long i)
{
    যদি (!dest) ফেরত;
    নির্বাচন (আকার_2) {
    ক্ষেত্র আকার_hh:
        *(অক্ষর *)dest = i;
        বিরতি;
    ক্ষেত্র আকার_h:
        *(short *)dest = i;
        বিরতি;
    ক্ষেত্র আকার_def:
        *(পূর্ণসংখ্যা *)dest = i;
        বিরতি;
    ক্ষেত্র আকার_l:
        *(long *)dest = i;
        বিরতি;
    ক্ষেত্র আকার_ll:
        *(long long *)dest = i;
        বিরতি;
    }
}

স্থির পূর্ণসংখ্যা ff_vfscanf(FFFILE *f, ধ্রুবক অক্ষর *fmt, va_list ap)
{
    পূর্ণসংখ্যা width;
    পূর্ণসংখ্যা আকার_2;
    পূর্ণসংখ্যা base;
    ধ্রুবক unsigned অক্ষর *p;
    পূর্ণসংখ্যা c, t;
    অক্ষর *s;
    শূন্য *dest=ফাঁকা;
    পূর্ণসংখ্যা invert;
    পূর্ণসংখ্যা matches=0;
    unsigned long long x;
    দ্বিগুণ y;
    ptrdiff_t pos = 0;
    unsigned অক্ষর scanset[257];
    size_t i;

    জন্য (p=(ধ্রুবক unsigned অক্ষর *)fmt; *p; p++) {

        যদি (av_isspace(*p)) {
            যখন (av_isspace(p[1])) p++;
            shlim(f, 0);
            যখন (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            চালু;
        }
        যদি (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            যদি (*p == '%') {
                p++;
                যখন (av_isspace((c=shgetc(f))));
            } অন্যথা {
                c = shgetc(f);
            }
            যদি (c!=*p) {
                shunget(f);
                যদি (c<0) যাও প্রবেশ_fail;
                যাও match_fail;
            }
            pos += shcnt(f);
            চালু;
        }

        p++;
        যদি (*p=='*') {
            dest = 0; p++;
        } অন্যথা যদি (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } অন্যথা {
            dest = va_arg(ap, শূন্য *);
        }

        জন্য (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        যদি (*p=='m') {
            s = 0;
            p++;
        }

        আকার_2 = আকার_def;
        নির্বাচন (*p++) {
        ক্ষেত্র 'h':
            যদি (*p == 'h') p++, আকার_2 = আকার_hh;
            অন্যথা আকার_2 = আকার_h;
            বিরতি;
        ক্ষেত্র 'l':
            যদি (*p == 'l') p++, আকার_2 = আকার_ll;
            অন্যথা আকার_2 = আকার_l;
            বিরতি;
        ক্ষেত্র 'j':
            আকার_2 = আকার_ll;
            বিরতি;
        ক্ষেত্র 'z':
        ক্ষেত্র 't':
            আকার_2 = আকার_l;
            বিরতি;
        ক্ষেত্র 'L':
            আকার_2 = আকার_L;
            বিরতি;
        ক্ষেত্র 'd': ক্ষেত্র 'i': ক্ষেত্র 'o': ক্ষেত্র 'u': ক্ষেত্র 'x':
        ক্ষেত্র 'a': ক্ষেত্র 'e': ক্ষেত্র 'f': ক্ষেত্র 'g':
        ক্ষেত্র 'A': ক্ষেত্র 'E': ক্ষেত্র 'F': ক্ষেত্র 'G': ক্ষেত্র 'X':
        ক্ষেত্র 's': ক্ষেত্র 'c': ক্ষেত্র '[':
        ক্ষেত্র 'S': ক্ষেত্র 'C':
        ক্ষেত্র 'p': ক্ষেত্র 'n':
            p--;
            বিরতি;
        পূর্বনির্ধারিত:
            যাও fmt_fail;
        }

        t = *p;

        /* C or S */
        যদি ((t&0x2f) == 3) {
            t |= 32;
            আকার_2 = আকার_l;
        }

        নির্বাচন (t) {
            ক্ষেত্র 'c':
                যদি (width < 1) width = 1;
                বিরতি;
            ক্ষেত্র '[':
                বিরতি;
            ক্ষেত্র 'n':
                store_int(dest, আকার_2, pos);
                /* do not increment match count, etc! */
                চালু;
            পূর্বনির্ধারিত:
                shlim(f, 0);
                যখন (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        যদি (shgetc(f) < 0) যাও প্রবেশ_fail;
        shunget(f);

        নির্বাচন (t) {
            ক্ষেত্র 's':
            ক্ষেত্র 'c':
            ক্ষেত্র '[':
                যদি (t == 'c' || t == 's') {
                    memset(scanset, -1, আকার scanset);
                    scanset[0] = 0;
                    যদি (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } অন্যথা {
                    যদি (*++p == '^') p++, invert = 1;
                    অন্যথা invert = 0;
                    memset(scanset, invert, আকার scanset);
                    scanset[0] = 0;
                    যদি (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    অন্যথা যদি (*p == ']') p++, scanset[1+']'] = 1-invert;
                    জন্য (; *p != ']'; p++) {
                        যদি (!*p) যাও fmt_fail;
                        যদি (*p=='-' && p[1] && p[1] != ']')
                            জন্য (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                যদি ((s = dest)) {
                    যখন (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } অন্যথা {
                    যখন (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                যদি (!shcnt(f)) যাও match_fail;
                যদি (t == 'c' && shcnt(f) != width) যাও match_fail;
                যদি (t != 'c') {
                    যদি (s) s[i] = 0;
                }
                বিরতি;
            ক্ষেত্র 'p':
            ক্ষেত্র 'X':
            ক্ষেত্র 'x':
                base = 16;
                যাও int_common;
            ক্ষেত্র 'o':
                base = 8;
                যাও int_common;
            ক্ষেত্র 'd':
            ক্ষেত্র 'u':
                base = 10;
                যাও int_common;
            ক্ষেত্র 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                যদি (!shcnt(f))
                    যাও match_fail;
                যদি (t=='p' && dest)
                    *(শূন্য **)dest = (শূন্য *)(uintptr_t)x;
                অন্যথা
                    store_int(dest, আকার_2, x);
                বিরতি;
            ক্ষেত্র 'a': ক্ষেত্র 'A':
            ক্ষেত্র 'e': ক্ষেত্র 'E':
            ক্ষেত্র 'f': ক্ষেত্র 'F':
            ক্ষেত্র 'g': ক্ষেত্র 'G':
                y = fffloatscan(f, আকার_2, 0);
                যদি (!shcnt(f))
                    যাও match_fail;
                যদি (dest) {
                    নির্বাচন (আকার_2) {
                    ক্ষেত্র আকার_def:
                        *(দশমিক *)dest = y;
                        বিরতি;
                    ক্ষেত্র আকার_l:
                        *(দ্বিগুণ *)dest = y;
                        বিরতি;
                    ক্ষেত্র আকার_L:
                        *(দ্বিগুণ *)dest = y;
                        বিরতি;
                    }
                }
                বিরতি;
        }

        pos += shcnt(f);
        যদি (dest) matches++;
    }
    যদি (0) {
fmt_fail:
প্রবেশ_fail:
        যদি (!matches) matches--;
    }
match_fail:
    ফেরত matches;
}

স্থির পূর্ণসংখ্যা ff_vsscanf(ধ্রুবক অক্ষর *s, ধ্রুবক অক্ষর *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (শূন্য *)s, .cookie = (শূন্য *)s,
        .পঠ = ffstring_read,
    };

    ফেরত ff_vfscanf(&f, fmt, ap);
}

পূর্ণসংখ্যা av_sscanf(ধ্রুবক অক্ষর *string, ধ্রুবক অক্ষর *format, ...)
{
    পূর্ণসংখ্যা ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ফেরত ret;
}
