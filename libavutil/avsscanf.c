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

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <float.h>

#ಅನ್ತರ್ಭಾವ "avstring.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFFILE {
    size_t buf_size;
    unsigned ವರ್ಣ *buf;
    unsigned ವರ್ಣ *rpos, *rend;
    unsigned ವರ್ಣ *shend;
    ptrdiff_t shlim, shcnt;
    ಶೂನ್ಯ *cookie;
    size_t (*ಪಠ)(ಸಂರಚನಾ FFFILE *, unsigned ವರ್ಣ *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ size_t ffstring_read(FFFILE *f, unsigned ವರ್ಣ *buf, size_t len)
{
    ವರ್ಣ *src = f->cookie;
    size_t k = len+256;
    ವರ್ಣ *end = memchr(src, 0, k);

    ಯದಿ (end) k = end-src;
    ಯದಿ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (ಶೂನ್ಯ *)(src+len);
    f->rend = (ಶೂನ್ಯ *)(src+k);
    f->cookie = src+k;

    ಪ್ರತ್ಯಾಗಮ len;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ffuflow(FFFILE *f)
{
    unsigned ವರ್ಣ c;
    ಯದಿ (!fftoread(f) && f->ಪಠ(f, &c, 1)==1) ಪ್ರತ್ಯಾಗಮ c;
    ಪ್ರತ್ಯಾಗಮ EOF;
}

ಸ್ಥಿರ ಶೂನ್ಯ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ಯದಿ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ಅನ್ಯಥಾ
        f->shend = f->rend;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ffshgetc(FFFILE *f)
{
    ಪೂರ್ಣಾಙ್ಕ c;
    ptrdiff_t cnt = shcnt(f);
    ಯದಿ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ಪ್ರತ್ಯಾಗಮ EOF;
    }
    cnt++;
    ಯದಿ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ಅನ್ಯಥಾ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ಯದಿ (f->rpos[-1] != c) f->rpos[-1] = c;
    ಪ್ರತ್ಯಾಗಮ c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (ಶೂನ್ಯ)(f)->rpos-- : (ಶೂನ್ಯ)0)

ಸ್ಥಿರ ಧ್ರುವ unsigned ವರ್ಣ table[] = { -1,
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

ಸ್ಥಿರ unsigned long long ffintscan(FFFILE *f, unsigned base, ಪೂರ್ಣಾಙ್ಕ pok, unsigned long long lim)
{
    ಧ್ರುವ unsigned ವರ್ಣ *val = table+1;
    ಪೂರ್ಣಾಙ್ಕ c, neg=0;
    unsigned x;
    unsigned long long y;
    ಯದಿ (base > 36 || base == 1) {
        errno = EINVAL;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಯಾವತ್ (av_isspace((c=shgetc(f))));
    ಯದಿ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ಯದಿ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ಯದಿ ((c|32)=='x') {
            c = shgetc(f);
            ಯದಿ (val[c]>=16) {
                shunget(f);
                ಯದಿ (pok) shunget(f);
                ಅನ್ಯಥಾ shlim(f, 0);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
            base = 16;
        } ಅನ್ಯಥಾ ಯದಿ (base == 0) {
            base = 8;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (base == 0) base = 10;
        ಯದಿ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }
    ಯದಿ (base == 10) {
        ಪ್ರತಿ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ಪ್ರತಿ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ಯದಿ (c-'0'>=10U) ಗಚ್ಛ done;
    } ಅನ್ಯಥಾ ಯದಿ (!(base & base-1)) {
        ಪೂರ್ಣಾಙ್ಕ bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        ಪ್ರತಿ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ಪ್ರತಿ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        ಪ್ರತಿ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ಯದಿ (val[c]<base) {
        ಪ್ರತಿ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ಯದಿ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ಯದಿ (y>=lim) {
        ಯದಿ (!(lim&1) && !neg) {
            errno = ERANGE;
            ಪ್ರತ್ಯಾಗಮ lim-1;
        } ಅನ್ಯಥಾ ಯದಿ (y>lim) {
            errno = ERANGE;
            ಪ್ರತ್ಯಾಗಮ lim;
        }
    }
    ಪ್ರತ್ಯಾಗಮ (y^neg)-neg;
}

ಸ್ಥಿರ long long scanexp(FFFILE *f, ಪೂರ್ಣಾಙ್ಕ pok)
{
    ಪೂರ್ಣಾಙ್ಕ c;
    ಪೂರ್ಣಾಙ್ಕ x;
    long long y;
    ಪೂರ್ಣಾಙ್ಕ neg = 0;

    c = shgetc(f);
    ಯದಿ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ಯದಿ (c-'0'>=10U && pok) shunget(f);
    }
    ಯದಿ (c-'0'>=10U) {
        shunget(f);
        ಪ್ರತ್ಯಾಗಮ LLONG_MIN;
    }
    ಪ್ರತಿ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ಪ್ರತಿ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ಪ್ರತಿ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ಪ್ರತ್ಯಾಗಮ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

ಸ್ಥಿರ ದ್ವಿಗುಣ decfloat(FFFILE *f, ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ bits, ಪೂರ್ಣಾಙ್ಕ emin, ಪೂರ್ಣಾಙ್ಕ sign, ಪೂರ್ಣಾಙ್ಕ pok)
{
    uint32_t x[KMAX];
    ಸ್ಥಿರ ಧ್ರುವ uint32_t th[] = { LD_B1B_MAX };
    ಪೂರ್ಣಾಙ್ಕ i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ಪೂರ್ಣಾಙ್ಕ lnz = 0;
    ಪೂರ್ಣಾಙ್ಕ gotdig = 0, gotrad = 0;
    ಪೂರ್ಣಾಙ್ಕ rp;
    ಪೂರ್ಣಾಙ್ಕ e2;
    ಪೂರ್ಣಾಙ್ಕ emax = -emin-bits+3;
    ಪೂರ್ಣಾಙ್ಕ denormal = 0;
    ದ್ವಿಗುಣ y;
    ದ್ವಿಗುಣ frac=0;
    ದ್ವಿಗುಣ bias=0;
    ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ಪ್ರತಿ (; c=='0'; c = shgetc(f)) gotdig=1;
    ಯದಿ (c=='.') {
        gotrad = 1;
        ಪ್ರತಿ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ಪ್ರತಿ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ಯದಿ (c == '.') {
            ಯದಿ (gotrad) ಭಙ್ಗ;
            gotrad = 1;
            lrp = dc;
        } ಅನ್ಯಥಾ ಯದಿ (k < KMAX-3) {
            dc++;
            ಯದಿ (c!='0') lnz = dc;
            ಯದಿ (j) x[k] = x[k]*10 + c-'0';
            ಅನ್ಯಥಾ x[k] = c-'0';
            ಯದಿ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ಅನ್ಯಥಾ {
            dc++;
            ಯದಿ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ಯದಿ (!gotrad) lrp=dc;

    ಯದಿ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ಯದಿ (e10 == LLONG_MIN) {
            ಯದಿ (pok) {
                shunget(f);
            } ಅನ್ಯಥಾ {
                shlim(f, 0);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ಅನ್ಯಥಾ ಯದಿ (c>=0) {
        shunget(f);
    }
    ಯದಿ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ಯದಿ (!x[0]) ಪ್ರತ್ಯಾಗಮ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ಯದಿ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ಪ್ರತ್ಯಾಗಮ sign * (ದ್ವಿಗುಣ)x[0];
    ಯದಿ (lrp > -emin/2) {
        errno = ERANGE;
        ಪ್ರತ್ಯಾಗಮ sign * DBL_MAX * DBL_MAX;
    }
    ಯದಿ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ಪ್ರತ್ಯಾಗಮ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ಯದಿ (j) {
        ಪ್ರತಿ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ಯದಿ (lnz<9 && lnz<=rp && rp < 18) {
        ಪೂರ್ಣಾಙ್ಕ bitlim;
        ಯದಿ (rp == 9) ಪ್ರತ್ಯಾಗಮ sign * (ದ್ವಿಗುಣ)x[0];
        ಯದಿ (rp < 9) ಪ್ರತ್ಯಾಗಮ sign * (ದ್ವಿಗುಣ)x[0] / p10s[8-rp];
        bitlim = bits-3*(ಪೂರ್ಣಾಙ್ಕ)(rp-9);
        ಯದಿ (bitlim>30 || x[0]>>bitlim==0)
            ಪ್ರತ್ಯಾಗಮ sign * (ದ್ವಿಗುಣ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ಪ್ರತಿ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ಯದಿ (rp % 9) {
        ಪೂರ್ಣಾಙ್ಕ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ಪೂರ್ಣಾಙ್ಕ p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        ಪ್ರತಿ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ಯದಿ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ಯದಿ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ಯಾವತ್ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        ಪ್ರತಿ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ಯದಿ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ಅನ್ಯಥಾ {
                carry = 0;
                x[k] = tmp;
            }
            ಯದಿ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ಯದಿ (k==a) ಭಙ್ಗ;
        }
        ಯದಿ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ಯದಿ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ಪ್ರತಿ (;;) {
        uint32_t carry = 0;
        ಪೂರ್ಣಾಙ್ಕ sh = 1;
        ಪ್ರತಿ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ಯದಿ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                ಭಙ್ಗ;
            }
            ಯದಿ (x[a+i & MASK] > th[i]) ಭಙ್ಗ;
        }
        ಯದಿ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) ಭಙ್ಗ;
        /* FIXME: find a way to compute optimal sh */
        ಯದಿ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ಪ್ರತಿ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ಯದಿ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ಯದಿ (carry) {
            ಯದಿ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ಅನ್ಯಥಾ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ಪ್ರತಿ (y=i=0; i<LD_B1B_DIG; i++) {
        ಯದಿ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ಯದಿ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ಯದಿ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ಯದಿ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ಯದಿ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ಯದಿ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ಅನ್ಯಥಾ ಯದಿ (t > 500000000)
            frac += 0.75*sign;
        ಅನ್ಯಥಾ ಯದಿ (t == 500000000) {
            ಯದಿ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ಅನ್ಯಥಾ
                frac += 0.75*sign;
        }
        ಯದಿ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ಯದಿ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ಯದಿ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ಯದಿ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ಯದಿ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ಪ್ರತ್ಯಾಗಮ scalbn(y, e2);
}

ಸ್ಥಿರ ದ್ವಿಗುಣ hexfloat(FFFILE *f, ಪೂರ್ಣಾಙ್ಕ bits, ಪೂರ್ಣಾಙ್ಕ emin, ಪೂರ್ಣಾಙ್ಕ sign, ಪೂರ್ಣಾಙ್ಕ pok)
{
    uint32_t x = 0;
    ದ್ವಿಗುಣ y = 0;
    ದ್ವಿಗುಣ scale = 1;
    ದ್ವಿಗುಣ bias = 0;
    ಪೂರ್ಣಾಙ್ಕ gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ಪೂರ್ಣಾಙ್ಕ d;
    ಪೂರ್ಣಾಙ್ಕ c;

    c = shgetc(f);

    /* Skip leading zeros */
    ಪ್ರತಿ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ಯದಿ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ಪ್ರತಿ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ಪ್ರತಿ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ಯದಿ (c=='.') {
            ಯದಿ (gotrad) ಭಙ್ಗ;
            rp = dc;
            gotrad = 1;
        } ಅನ್ಯಥಾ {
            gotdig = 1;
            ಯದಿ (c > '9') d = (c|32)+10-'a';
            ಅನ್ಯಥಾ d = c-'0';
            ಯದಿ (dc<8) {
                x = x*16 + d;
            } ಅನ್ಯಥಾ ಯದಿ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ಅನ್ಯಥಾ ಯದಿ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ಯದಿ (!gotdig) {
        shunget(f);
        ಯದಿ (pok) {
            shunget(f);
            ಯದಿ (gotrad) shunget(f);
        } ಅನ್ಯಥಾ {
            shlim(f, 0);
        }
        ಪ್ರತ್ಯಾಗಮ sign * 0.0;
    }
    ಯದಿ (!gotrad) rp = dc;
    ಯಾವತ್ (dc<8) x *= 16, dc++;
    ಯದಿ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ಯದಿ (e2 == LLONG_MIN) {
            ಯದಿ (pok) {
                shunget(f);
            } ಅನ್ಯಥಾ {
                shlim(f, 0);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
            e2 = 0;
        }
    } ಅನ್ಯಥಾ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ಯದಿ (!x) ಪ್ರತ್ಯಾಗಮ sign * 0.0;
    ಯದಿ (e2 > -emin) {
        errno = ERANGE;
        ಪ್ರತ್ಯಾಗಮ sign * DBL_MAX * DBL_MAX;
    }
    ಯದಿ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ಪ್ರತ್ಯಾಗಮ sign * DBL_MIN * DBL_MIN;
    }

    ಯಾವತ್ (x < 0x80000000) {
        ಯದಿ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ಅನ್ಯಥಾ {
            x += x;
            y += y;
        }
        e2--;
    }

    ಯದಿ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ಯದಿ (bits<0) bits=0;
    }

    ಯದಿ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ಯದಿ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ದ್ವಿಗುಣ)x + sign*y;
    y -= bias;

    ಯದಿ (!y) errno = ERANGE;

    ಪ್ರತ್ಯಾಗಮ scalbn(y, e2);
}

ಸ್ಥಿರ ದ್ವಿಗುಣ fffloatscan(FFFILE *f, ಪೂರ್ಣಾಙ್ಕ prec, ಪೂರ್ಣಾಙ್ಕ pok)
{
    ಪೂರ್ಣಾಙ್ಕ sign = 1;
    size_t i;
    ಪೂರ್ಣಾಙ್ಕ bits;
    ಪೂರ್ಣಾಙ್ಕ emin;
    ಪೂರ್ಣಾಙ್ಕ c;

    ವಿಕಲ್ಪ (prec) {
    ಪಕ್ಷ 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        ಭಙ್ಗ;
    ಪಕ್ಷ 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        ಭಙ್ಗ;
    ಪಕ್ಷ 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯಾವತ್ (av_isspace((c = shgetc(f))));

    ಯದಿ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ಪ್ರತಿ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ಯದಿ (i<7) c = shgetc(f);
    ಯದಿ (i==3 || i==8 || (i>3 && pok)) {
        ಯದಿ (i!=8) {
            shunget(f);
            ಯದಿ (pok) ಪ್ರತಿ (; i>3; i--) shunget(f);
        }
        ಪ್ರತ್ಯಾಗಮ sign * INFINITY;
    }
    ಯದಿ (!i) ಪ್ರತಿ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ಯದಿ (i<2) c = shgetc(f);
    ಯದಿ (i==3) {
        ಯದಿ (shgetc(f) != '(') {
            shunget(f);
            ಪ್ರತ್ಯಾಗಮ NAN;
        }
        ಪ್ರತಿ (i=1; ; i++) {
            c = shgetc(f);
            ಯದಿ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ಅನುವರ್ತ;
            ಯದಿ (c==')') ಪ್ರತ್ಯಾಗಮ NAN;
            shunget(f);
            ಯದಿ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
            ಯಾವತ್ (i--) shunget(f);
            ಪ್ರತ್ಯಾಗಮ NAN;
        }
    }

    ಯದಿ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (c=='0') {
        c = shgetc(f);
        ಯದಿ ((c|32) == 'x')
            ಪ್ರತ್ಯಾಗಮ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ಪ್ರತ್ಯಾಗಮ decfloat(f, c, bits, emin, sign, pok);
}

ಸ್ಥಿರ ಶೂನ್ಯ *arg_n(va_list ap, unsigned ಪೂರ್ಣಾಙ್ಕ n)
{
    ಶೂನ್ಯ *p;
    unsigned ಪೂರ್ಣಾಙ್ಕ i;
    va_list ap2;
    va_copy(ap2, ap);
    ಪ್ರತಿ (i=n; i>1; i--) va_arg(ap2, ಶೂನ್ಯ *);
    p = va_arg(ap2, ಶೂನ್ಯ *);
    va_end(ap2);
    ಪ್ರತ್ಯಾಗಮ p;
}

ಸ್ಥಿರ ಶೂನ್ಯ store_int(ಶೂನ್ಯ *dest, ಪೂರ್ಣಾಙ್ಕ size, unsigned long long i)
{
    ಯದಿ (!dest) ಪ್ರತ್ಯಾಗಮ;
    ವಿಕಲ್ಪ (size) {
    ಪಕ್ಷ SIZE_hh:
        *(ವರ್ಣ *)dest = i;
        ಭಙ್ಗ;
    ಪಕ್ಷ SIZE_h:
        *(short *)dest = i;
        ಭಙ್ಗ;
    ಪಕ್ಷ SIZE_def:
        *(ಪೂರ್ಣಾಙ್ಕ *)dest = i;
        ಭಙ್ಗ;
    ಪಕ್ಷ SIZE_l:
        *(long *)dest = i;
        ಭಙ್ಗ;
    ಪಕ್ಷ SIZE_ll:
        *(long long *)dest = i;
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ff_vfscanf(FFFILE *f, ಧ್ರುವ ವರ್ಣ *fmt, va_list ap)
{
    ಪೂರ್ಣಾಙ್ಕ width;
    ಪೂರ್ಣಾಙ್ಕ size;
    ಪೂರ್ಣಾಙ್ಕ base;
    ಧ್ರುವ unsigned ವರ್ಣ *p;
    ಪೂರ್ಣಾಙ್ಕ c, t;
    ವರ್ಣ *s;
    ಶೂನ್ಯ *dest=ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ invert;
    ಪೂರ್ಣಾಙ್ಕ matches=0;
    unsigned long long x;
    ದ್ವಿಗುಣ y;
    ptrdiff_t pos = 0;
    unsigned ವರ್ಣ scanset[257];
    size_t i;

    ಪ್ರತಿ (p=(ಧ್ರುವ unsigned ವರ್ಣ *)fmt; *p; p++) {

        ಯದಿ (av_isspace(*p)) {
            ಯಾವತ್ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ಯಾವತ್ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ಅನುವರ್ತ;
        }
        ಯದಿ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ಯದಿ (*p == '%') {
                p++;
                ಯಾವತ್ (av_isspace((c=shgetc(f))));
            } ಅನ್ಯಥಾ {
                c = shgetc(f);
            }
            ಯದಿ (c!=*p) {
                shunget(f);
                ಯದಿ (c<0) ಗಚ್ಛ ಒಳಹರಿವು_fail;
                ಗಚ್ಛ match_fail;
            }
            pos += shcnt(f);
            ಅನುವರ್ತ;
        }

        p++;
        ಯದಿ (*p=='*') {
            dest = 0; p++;
        } ಅನ್ಯಥಾ ಯದಿ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ಅನ್ಯಥಾ {
            dest = va_arg(ap, ಶೂನ್ಯ *);
        }

        ಪ್ರತಿ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ಯದಿ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        ವಿಕಲ್ಪ (*p++) {
        ಪಕ್ಷ 'h':
            ಯದಿ (*p == 'h') p++, size = SIZE_hh;
            ಅನ್ಯಥಾ size = SIZE_h;
            ಭಙ್ಗ;
        ಪಕ್ಷ 'l':
            ಯದಿ (*p == 'l') p++, size = SIZE_ll;
            ಅನ್ಯಥಾ size = SIZE_l;
            ಭಙ್ಗ;
        ಪಕ್ಷ 'j':
            size = SIZE_ll;
            ಭಙ್ಗ;
        ಪಕ್ಷ 'z':
        ಪಕ್ಷ 't':
            size = SIZE_l;
            ಭಙ್ಗ;
        ಪಕ್ಷ 'L':
            size = SIZE_L;
            ಭಙ್ಗ;
        ಪಕ್ಷ 'd': ಪಕ್ಷ 'i': ಪಕ್ಷ 'o': ಪಕ್ಷ 'u': ಪಕ್ಷ 'x':
        ಪಕ್ಷ 'a': ಪಕ್ಷ 'e': ಪಕ್ಷ 'f': ಪಕ್ಷ 'g':
        ಪಕ್ಷ 'A': ಪಕ್ಷ 'E': ಪಕ್ಷ 'F': ಪಕ್ಷ 'G': ಪಕ್ಷ 'X':
        ಪಕ್ಷ 's': ಪಕ್ಷ 'c': ಪಕ್ಷ '[':
        ಪಕ್ಷ 'S': ಪಕ್ಷ 'C':
        ಪಕ್ಷ 'p': ಪಕ್ಷ 'n':
            p--;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಗಚ್ಛ fmt_fail;
        }

        t = *p;

        /* C or S */
        ಯದಿ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        ವಿಕಲ್ಪ (t) {
            ಪಕ್ಷ 'c':
                ಯದಿ (width < 1) width = 1;
                ಭಙ್ಗ;
            ಪಕ್ಷ '[':
                ಭಙ್ಗ;
            ಪಕ್ಷ 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                ಅನುವರ್ತ;
            ಸ್ವಭಾವ:
                shlim(f, 0);
                ಯಾವತ್ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ಯದಿ (shgetc(f) < 0) ಗಚ್ಛ ಒಳಹರಿವು_fail;
        shunget(f);

        ವಿಕಲ್ಪ (t) {
            ಪಕ್ಷ 's':
            ಪಕ್ಷ 'c':
            ಪಕ್ಷ '[':
                ಯದಿ (t == 'c' || t == 's') {
                    memset(scanset, -1, ಪರಿಮಾಣ scanset);
                    scanset[0] = 0;
                    ಯದಿ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ಅನ್ಯಥಾ {
                    ಯದಿ (*++p == '^') p++, invert = 1;
                    ಅನ್ಯಥಾ invert = 0;
                    memset(scanset, invert, ಪರಿಮಾಣ scanset);
                    scanset[0] = 0;
                    ಯದಿ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ಅನ್ಯಥಾ ಯದಿ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ಪ್ರತಿ (; *p != ']'; p++) {
                        ಯದಿ (!*p) ಗಚ್ಛ fmt_fail;
                        ಯದಿ (*p=='-' && p[1] && p[1] != ']')
                            ಪ್ರತಿ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ಯದಿ ((s = dest)) {
                    ಯಾವತ್ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ಅನ್ಯಥಾ {
                    ಯಾವತ್ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ಯದಿ (!shcnt(f)) ಗಚ್ಛ match_fail;
                ಯದಿ (t == 'c' && shcnt(f) != width) ಗಚ್ಛ match_fail;
                ಯದಿ (t != 'c') {
                    ಯದಿ (s) s[i] = 0;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ 'p':
            ಪಕ್ಷ 'X':
            ಪಕ್ಷ 'x':
                base = 16;
                ಗಚ್ಛ int_common;
            ಪಕ್ಷ 'o':
                base = 8;
                ಗಚ್ಛ int_common;
            ಪಕ್ಷ 'd':
            ಪಕ್ಷ 'u':
                base = 10;
                ಗಚ್ಛ int_common;
            ಪಕ್ಷ 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                ಯದಿ (!shcnt(f))
                    ಗಚ್ಛ match_fail;
                ಯದಿ (t=='p' && dest)
                    *(ಶೂನ್ಯ **)dest = (ಶೂನ್ಯ *)(uintptr_t)x;
                ಅನ್ಯಥಾ
                    store_int(dest, size, x);
                ಭಙ್ಗ;
            ಪಕ್ಷ 'a': ಪಕ್ಷ 'A':
            ಪಕ್ಷ 'e': ಪಕ್ಷ 'E':
            ಪಕ್ಷ 'f': ಪಕ್ಷ 'F':
            ಪಕ್ಷ 'g': ಪಕ್ಷ 'G':
                y = fffloatscan(f, size, 0);
                ಯದಿ (!shcnt(f))
                    ಗಚ್ಛ match_fail;
                ಯದಿ (dest) {
                    ವಿಕಲ್ಪ (size) {
                    ಪಕ್ಷ SIZE_def:
                        *(ಭಿನ್ನ *)dest = y;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ SIZE_l:
                        *(ದ್ವಿಗುಣ *)dest = y;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ SIZE_L:
                        *(ದ್ವಿಗುಣ *)dest = y;
                        ಭಙ್ಗ;
                    }
                }
                ಭಙ್ಗ;
        }

        pos += shcnt(f);
        ಯದಿ (dest) matches++;
    }
    ಯದಿ (0) {
fmt_fail:
ಒಳಹರಿವು_fail:
        ಯದಿ (!matches) matches--;
    }
match_fail:
    ಪ್ರತ್ಯಾಗಮ matches;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ff_vsscanf(ಧ್ರುವ ವರ್ಣ *s, ಧ್ರುವ ವರ್ಣ *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (ಶೂನ್ಯ *)s, .cookie = (ಶೂನ್ಯ *)s,
        .ಪಠ = ffstring_read,
    };

    ಪ್ರತ್ಯಾಗಮ ff_vfscanf(&f, fmt, ap);
}

ಪೂರ್ಣಾಙ್ಕ av_sscanf(ಧ್ರುವ ವರ್ಣ *string, ಧ್ರುವ ವರ್ಣ *format, ...)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ಪ್ರತ್ಯಾಗಮ ret;
}
