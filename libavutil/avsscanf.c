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

#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <math.h>
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <float.h>

#ଅନ୍ତର୍ଭାଵ "avstring.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FFFILE {
    size_t buf_size;
    unsigned ଅକ୍ଷର *buf;
    unsigned ଅକ୍ଷର *rpos, *rend;
    unsigned ଅକ୍ଷର *shend;
    ptrdiff_t shlim, shcnt;
    ଶୂନ୍ୟ *cookie;
    size_t (*ପଠ)(ସଂରଚନା FFFILE *, unsigned ଅକ୍ଷର *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର size_t ffstring_read(FFFILE *f, unsigned ଅକ୍ଷର *buf, size_t len)
{
    ଅକ୍ଷର *src = f->cookie;
    size_t k = len+256;
    ଅକ୍ଷର *end = memchr(src, 0, k);

    ଯଦି (end) k = end-src;
    ଯଦି (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (ଶୂନ୍ୟ *)(src+len);
    f->rend = (ଶୂନ୍ୟ *)(src+k);
    f->cookie = src+k;

    ଫେରନ୍ତୁ len;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ffuflow(FFFILE *f)
{
    unsigned ଅକ୍ଷର c;
    ଯଦି (!fftoread(f) && f->ପଠ(f, &c, 1)==1) ଫେରନ୍ତୁ c;
    ଫେରନ୍ତୁ EOF;
}

ସ୍ଥିର ଶୂନ୍ୟ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ଯଦି (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ଅନ୍ୟଥା
        f->shend = f->rend;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ffshgetc(FFFILE *f)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    ptrdiff_t cnt = shcnt(f);
    ଯଦି (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ଫେରନ୍ତୁ EOF;
    }
    cnt++;
    ଯଦି (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ଅନ୍ୟଥା
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ଯଦି (f->rpos[-1] != c) f->rpos[-1] = c;
    ଫେରନ୍ତୁ c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (ଶୂନ୍ୟ)(f)->rpos-- : (ଶୂନ୍ୟ)0)

ସ୍ଥିର ଅଚଳ unsigned ଅକ୍ଷର table[] = { -1,
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

ସ୍ଥିର unsigned long long ffintscan(FFFILE *f, unsigned base, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pok, unsigned long long lim)
{
    ଅଚଳ unsigned ଅକ୍ଷର *val = table+1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, neg=0;
    unsigned x;
    unsigned long long y;
    ଯଦି (base > 36 || base == 1) {
        errno = EINVAL;
        ଫେରନ୍ତୁ 0;
    }
    ଯେତେବେଳେ (av_isspace((c=shgetc(f))));
    ଯଦି (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ଯଦି ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ଯଦି ((c|32)=='x') {
            c = shgetc(f);
            ଯଦି (val[c]>=16) {
                shunget(f);
                ଯଦି (pok) shunget(f);
                ଅନ୍ୟଥା shlim(f, 0);
                ଫେରନ୍ତୁ 0;
            }
            base = 16;
        } ଅନ୍ୟଥା ଯଦି (base == 0) {
            base = 8;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (base == 0) base = 10;
        ଯଦି (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ଫେରନ୍ତୁ 0;
        }
    }
    ଯଦି (base == 10) {
        ପାଇଁ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ପାଇଁ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ଯଦି (c-'0'>=10U) ଯାଅ done;
    } ଅନ୍ୟଥା ଯଦି (!(base & base-1)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        ପାଇଁ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ପାଇଁ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ଅନ୍ୟଥା {
        ପାଇଁ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        ପାଇଁ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ଯଦି (val[c]<base) {
        ପାଇଁ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ଯଦି (lim&1) neg = 0;
    }
done:
    shunget(f);
    ଯଦି (y>=lim) {
        ଯଦି (!(lim&1) && !neg) {
            errno = ERANGE;
            ଫେରନ୍ତୁ lim-1;
        } ଅନ୍ୟଥା ଯଦି (y>lim) {
            errno = ERANGE;
            ଫେରନ୍ତୁ lim;
        }
    }
    ଫେରନ୍ତୁ (y^neg)-neg;
}

ସ୍ଥିର long long scanexp(FFFILE *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pok)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x;
    long long y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା neg = 0;

    c = shgetc(f);
    ଯଦି (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ଯଦି (c-'0'>=10U && pok) shunget(f);
    }
    ଯଦି (c-'0'>=10U) {
        shunget(f);
        ଫେରନ୍ତୁ LLONG_MIN;
    }
    ପାଇଁ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ପାଇଁ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ପାଇଁ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ଫେରନ୍ତୁ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

ସ୍ଥିର ଦ୍ୱିଗୁଣ decfloat(FFFILE *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା emin, ପୂର୍ଣ୍ଣସଂଖ୍ୟା sign, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pok)
{
    uint32_t x[KMAX];
    ସ୍ଥିର ଅଚଳ uint32_t th[] = { LD_B1B_MAX };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା lnz = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା gotdig = 0, gotrad = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା e2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା emax = -emin-bits+3;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା denormal = 0;
    ଦ୍ୱିଗୁଣ y;
    ଦ୍ୱିଗୁଣ frac=0;
    ଦ୍ୱିଗୁଣ bias=0;
    ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ପାଇଁ (; c=='0'; c = shgetc(f)) gotdig=1;
    ଯଦି (c=='.') {
        gotrad = 1;
        ପାଇଁ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ପାଇଁ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ଯଦି (c == '.') {
            ଯଦି (gotrad) ଭାଙ୍ଗ;
            gotrad = 1;
            lrp = dc;
        } ଅନ୍ୟଥା ଯଦି (k < KMAX-3) {
            dc++;
            ଯଦି (c!='0') lnz = dc;
            ଯଦି (j) x[k] = x[k]*10 + c-'0';
            ଅନ୍ୟଥା x[k] = c-'0';
            ଯଦି (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ଅନ୍ୟଥା {
            dc++;
            ଯଦି (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ଯଦି (!gotrad) lrp=dc;

    ଯଦି (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ଯଦି (e10 == LLONG_MIN) {
            ଯଦି (pok) {
                shunget(f);
            } ଅନ୍ୟଥା {
                shlim(f, 0);
                ଫେରନ୍ତୁ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ଅନ୍ୟଥା ଯଦି (c>=0) {
        shunget(f);
    }
    ଯଦି (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ଫେରନ୍ତୁ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ଯଦି (!x[0]) ଫେରନ୍ତୁ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ଯଦି (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ଫେରନ୍ତୁ sign * (ଦ୍ୱିଗୁଣ)x[0];
    ଯଦି (lrp > -emin/2) {
        errno = ERANGE;
        ଫେରନ୍ତୁ sign * DBL_MAX * DBL_MAX;
    }
    ଯଦି (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ଫେରନ୍ତୁ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ଯଦି (j) {
        ପାଇଁ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ଯଦି (lnz<9 && lnz<=rp && rp < 18) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା bitlim;
        ଯଦି (rp == 9) ଫେରନ୍ତୁ sign * (ଦ୍ୱିଗୁଣ)x[0];
        ଯଦି (rp < 9) ଫେରନ୍ତୁ sign * (ଦ୍ୱିଗୁଣ)x[0] / p10s[8-rp];
        bitlim = bits-3*(ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(rp-9);
        ଯଦି (bitlim>30 || x[0]>>bitlim==0)
            ଫେରନ୍ତୁ sign * (ଦ୍ୱିଗୁଣ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ପାଇଁ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ଯଦି (rp % 9) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        ପାଇଁ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ଯଦି (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ଯଦି (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ଯେତେବେଳେ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        ପାଇଁ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ଯଦି (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ଅନ୍ୟଥା {
                carry = 0;
                x[k] = tmp;
            }
            ଯଦି (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ଯଦି (k==a) ଭାଙ୍ଗ;
        }
        ଯଦି (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ଯଦି (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ପାଇଁ (;;) {
        uint32_t carry = 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା sh = 1;
        ପାଇଁ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ଯଦି (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                ଭାଙ୍ଗ;
            }
            ଯଦି (x[a+i & MASK] > th[i]) ଭାଙ୍ଗ;
        }
        ଯଦି (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) ଭାଙ୍ଗ;
        /* FIXME: find a way to compute optimal sh */
        ଯଦି (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ପାଇଁ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ଯଦି (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ଯଦି (carry) {
            ଯଦି ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ଅନ୍ୟଥା x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ପାଇଁ (y=i=0; i<LD_B1B_DIG; i++) {
        ଯଦି ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ଯଦି (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ଯଦି (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ଯଦି (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ଯଦି ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ଯଦି (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ଅନ୍ୟଥା ଯଦି (t > 500000000)
            frac += 0.75*sign;
        ଅନ୍ୟଥା ଯଦି (t == 500000000) {
            ଯଦି ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ଅନ୍ୟଥା
                frac += 0.75*sign;
        }
        ଯଦି (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ଯଦି ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ଯଦି (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ଯଦି (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ଯଦି (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ଫେରନ୍ତୁ scalbn(y, e2);
}

ସ୍ଥିର ଦ୍ୱିଗୁଣ hexfloat(FFFILE *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା emin, ପୂର୍ଣ୍ଣସଂଖ୍ୟା sign, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pok)
{
    uint32_t x = 0;
    ଦ୍ୱିଗୁଣ y = 0;
    ଦ୍ୱିଗୁଣ scale = 1;
    ଦ୍ୱିଗୁଣ bias = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା d;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    c = shgetc(f);

    /* Skip leading zeros */
    ପାଇଁ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ଯଦି (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ପାଇଁ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ପାଇଁ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ଯଦି (c=='.') {
            ଯଦି (gotrad) ଭାଙ୍ଗ;
            rp = dc;
            gotrad = 1;
        } ଅନ୍ୟଥା {
            gotdig = 1;
            ଯଦି (c > '9') d = (c|32)+10-'a';
            ଅନ୍ୟଥା d = c-'0';
            ଯଦି (dc<8) {
                x = x*16 + d;
            } ଅନ୍ୟଥା ଯଦି (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ଅନ୍ୟଥା ଯଦି (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ଯଦି (!gotdig) {
        shunget(f);
        ଯଦି (pok) {
            shunget(f);
            ଯଦି (gotrad) shunget(f);
        } ଅନ୍ୟଥା {
            shlim(f, 0);
        }
        ଫେରନ୍ତୁ sign * 0.0;
    }
    ଯଦି (!gotrad) rp = dc;
    ଯେତେବେଳେ (dc<8) x *= 16, dc++;
    ଯଦି ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ଯଦି (e2 == LLONG_MIN) {
            ଯଦି (pok) {
                shunget(f);
            } ଅନ୍ୟଥା {
                shlim(f, 0);
                ଫେରନ୍ତୁ 0;
            }
            e2 = 0;
        }
    } ଅନ୍ୟଥା {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ଯଦି (!x) ଫେରନ୍ତୁ sign * 0.0;
    ଯଦି (e2 > -emin) {
        errno = ERANGE;
        ଫେରନ୍ତୁ sign * DBL_MAX * DBL_MAX;
    }
    ଯଦି (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ଫେରନ୍ତୁ sign * DBL_MIN * DBL_MIN;
    }

    ଯେତେବେଳେ (x < 0x80000000) {
        ଯଦି (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ଅନ୍ୟଥା {
            x += x;
            y += y;
        }
        e2--;
    }

    ଯଦି (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ଯଦି (bits<0) bits=0;
    }

    ଯଦି (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ଯଦି (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ଦ୍ୱିଗୁଣ)x + sign*y;
    y -= bias;

    ଯଦି (!y) errno = ERANGE;

    ଫେରନ୍ତୁ scalbn(y, e2);
}

ସ୍ଥିର ଦ୍ୱିଗୁଣ fffloatscan(FFFILE *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା prec, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pok)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sign = 1;
    size_t i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା emin;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;

    ବାଛ (prec) {
    ସ୍ଥିତି 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ 0;
    }

    ଯେତେବେଳେ (av_isspace((c = shgetc(f))));

    ଯଦି (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ପାଇଁ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ଯଦି (i<7) c = shgetc(f);
    ଯଦି (i==3 || i==8 || (i>3 && pok)) {
        ଯଦି (i!=8) {
            shunget(f);
            ଯଦି (pok) ପାଇଁ (; i>3; i--) shunget(f);
        }
        ଫେରନ୍ତୁ sign * INFINITY;
    }
    ଯଦି (!i) ପାଇଁ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ଯଦି (i<2) c = shgetc(f);
    ଯଦି (i==3) {
        ଯଦି (shgetc(f) != '(') {
            shunget(f);
            ଫେରନ୍ତୁ NAN;
        }
        ପାଇଁ (i=1; ; i++) {
            c = shgetc(f);
            ଯଦି (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ଜାରି;
            ଯଦି (c==')') ଫେରନ୍ତୁ NAN;
            shunget(f);
            ଯଦି (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ଫେରନ୍ତୁ 0;
            }
            ଯେତେବେଳେ (i--) shunget(f);
            ଫେରନ୍ତୁ NAN;
        }
    }

    ଯଦି (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (c=='0') {
        c = shgetc(f);
        ଯଦି ((c|32) == 'x')
            ଫେରନ୍ତୁ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ଫେରନ୍ତୁ decfloat(f, c, bits, emin, sign, pok);
}

ସ୍ଥିର ଶୂନ୍ୟ *arg_n(va_list ap, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
    ଶୂନ୍ୟ *p;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    va_list ap2;
    va_copy(ap2, ap);
    ପାଇଁ (i=n; i>1; i--) va_arg(ap2, ଶୂନ୍ୟ *);
    p = va_arg(ap2, ଶୂନ୍ୟ *);
    va_end(ap2);
    ଫେରନ୍ତୁ p;
}

ସ୍ଥିର ଶୂନ୍ୟ store_int(ଶୂନ୍ୟ *dest, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, unsigned long long i)
{
    ଯଦି (!dest) ଫେରନ୍ତୁ;
    ବାଛ (size) {
    ସ୍ଥିତି SIZE_hh:
        *(ଅକ୍ଷର *)dest = i;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SIZE_h:
        *(short *)dest = i;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SIZE_def:
        *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dest = i;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SIZE_l:
        *(long *)dest = i;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SIZE_ll:
        *(long long *)dest = i;
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vfscanf(FFFILE *f, ଅଚଳ ଅକ୍ଷର *fmt, va_list ap)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା base;
    ଅଚଳ unsigned ଅକ୍ଷର *p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, t;
    ଅକ୍ଷର *s;
    ଶୂନ୍ୟ *dest=ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା invert;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା matches=0;
    unsigned long long x;
    ଦ୍ୱିଗୁଣ y;
    ptrdiff_t pos = 0;
    unsigned ଅକ୍ଷର scanset[257];
    size_t i;

    ପାଇଁ (p=(ଅଚଳ unsigned ଅକ୍ଷର *)fmt; *p; p++) {

        ଯଦି (av_isspace(*p)) {
            ଯେତେବେଳେ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ଯେତେବେଳେ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ଜାରି;
        }
        ଯଦି (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ଯଦି (*p == '%') {
                p++;
                ଯେତେବେଳେ (av_isspace((c=shgetc(f))));
            } ଅନ୍ୟଥା {
                c = shgetc(f);
            }
            ଯଦି (c!=*p) {
                shunget(f);
                ଯଦି (c<0) ଯାଅ ନିବେଶ_fail;
                ଯାଅ match_fail;
            }
            pos += shcnt(f);
            ଜାରି;
        }

        p++;
        ଯଦି (*p=='*') {
            dest = 0; p++;
        } ଅନ୍ୟଥା ଯଦି (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ଅନ୍ୟଥା {
            dest = va_arg(ap, ଶୂନ୍ୟ *);
        }

        ପାଇଁ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ଯଦି (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        ବାଛ (*p++) {
        ସ୍ଥିତି 'h':
            ଯଦି (*p == 'h') p++, size = SIZE_hh;
            ଅନ୍ୟଥା size = SIZE_h;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 'l':
            ଯଦି (*p == 'l') p++, size = SIZE_ll;
            ଅନ୍ୟଥା size = SIZE_l;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 'j':
            size = SIZE_ll;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 'z':
        ସ୍ଥିତି 't':
            size = SIZE_l;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 'L':
            size = SIZE_L;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 'd': ସ୍ଥିତି 'i': ସ୍ଥିତି 'o': ସ୍ଥିତି 'u': ସ୍ଥିତି 'x':
        ସ୍ଥିତି 'a': ସ୍ଥିତି 'e': ସ୍ଥିତି 'f': ସ୍ଥିତି 'g':
        ସ୍ଥିତି 'A': ସ୍ଥିତି 'E': ସ୍ଥିତି 'F': ସ୍ଥିତି 'G': ସ୍ଥିତି 'X':
        ସ୍ଥିତି 's': ସ୍ଥିତି 'c': ସ୍ଥିତି '[':
        ସ୍ଥିତି 'S': ସ୍ଥିତି 'C':
        ସ୍ଥିତି 'p': ସ୍ଥିତି 'n':
            p--;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଯାଅ fmt_fail;
        }

        t = *p;

        /* C or S */
        ଯଦି ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        ବାଛ (t) {
            ସ୍ଥିତି 'c':
                ଯଦି (width < 1) width = 1;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି '[':
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                ଜାରି;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                shlim(f, 0);
                ଯେତେବେଳେ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ଯଦି (shgetc(f) < 0) ଯାଅ ନିବେଶ_fail;
        shunget(f);

        ବାଛ (t) {
            ସ୍ଥିତି 's':
            ସ୍ଥିତି 'c':
            ସ୍ଥିତି '[':
                ଯଦି (t == 'c' || t == 's') {
                    memset(scanset, -1, ଆକାର scanset);
                    scanset[0] = 0;
                    ଯଦି (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ଅନ୍ୟଥା {
                    ଯଦି (*++p == '^') p++, invert = 1;
                    ଅନ୍ୟଥା invert = 0;
                    memset(scanset, invert, ଆକାର scanset);
                    scanset[0] = 0;
                    ଯଦି (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ଅନ୍ୟଥା ଯଦି (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ପାଇଁ (; *p != ']'; p++) {
                        ଯଦି (!*p) ଯାଅ fmt_fail;
                        ଯଦି (*p=='-' && p[1] && p[1] != ']')
                            ପାଇଁ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ଯଦି ((s = dest)) {
                    ଯେତେବେଳେ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ଅନ୍ୟଥା {
                    ଯେତେବେଳେ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ଯଦି (!shcnt(f)) ଯାଅ match_fail;
                ଯଦି (t == 'c' && shcnt(f) != width) ଯାଅ match_fail;
                ଯଦି (t != 'c') {
                    ଯଦି (s) s[i] = 0;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 'p':
            ସ୍ଥିତି 'X':
            ସ୍ଥିତି 'x':
                base = 16;
                ଯାଅ int_common;
            ସ୍ଥିତି 'o':
                base = 8;
                ଯାଅ int_common;
            ସ୍ଥିତି 'd':
            ସ୍ଥିତି 'u':
                base = 10;
                ଯାଅ int_common;
            ସ୍ଥିତି 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                ଯଦି (!shcnt(f))
                    ଯାଅ match_fail;
                ଯଦି (t=='p' && dest)
                    *(ଶୂନ୍ୟ **)dest = (ଶୂନ୍ୟ *)(uintptr_t)x;
                ଅନ୍ୟଥା
                    store_int(dest, size, x);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 'a': ସ୍ଥିତି 'A':
            ସ୍ଥିତି 'e': ସ୍ଥିତି 'E':
            ସ୍ଥିତି 'f': ସ୍ଥିତି 'F':
            ସ୍ଥିତି 'g': ସ୍ଥିତି 'G':
                y = fffloatscan(f, size, 0);
                ଯଦି (!shcnt(f))
                    ଯାଅ match_fail;
                ଯଦି (dest) {
                    ବାଛ (size) {
                    ସ୍ଥିତି SIZE_def:
                        *(ଦଶମିକ *)dest = y;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି SIZE_l:
                        *(ଦ୍ୱିଗୁଣ *)dest = y;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି SIZE_L:
                        *(ଦ୍ୱିଗୁଣ *)dest = y;
                        ଭାଙ୍ଗ;
                    }
                }
                ଭାଙ୍ଗ;
        }

        pos += shcnt(f);
        ଯଦି (dest) matches++;
    }
    ଯଦି (0) {
fmt_fail:
ନିବେଶ_fail:
        ଯଦି (!matches) matches--;
    }
match_fail:
    ଫେରନ୍ତୁ matches;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vsscanf(ଅଚଳ ଅକ୍ଷର *s, ଅଚଳ ଅକ୍ଷର *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (ଶୂନ୍ୟ *)s, .cookie = (ଶୂନ୍ୟ *)s,
        .ପଠ = ffstring_read,
    };

    ଫେରନ୍ତୁ ff_vfscanf(&f, fmt, ap);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_sscanf(ଅଚଳ ଅକ୍ଷର *string, ଅଚଳ ଅକ୍ଷର *format, ...)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ଫେରନ୍ତୁ ret;
}
