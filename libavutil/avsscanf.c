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

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include "avstring.h"

typedef sa_nracanaa FFFILE {
    size_t buf_size;
    unsigned var_na *buf;
    unsigned var_na *rpos, *rend;
    unsigned var_na *shend;
    ptrdiff_t shlim, shcnt;
    void *cookie;
    size_t (*read)(sa_nracanaa FFFILE *, unsigned var_na *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

static puur_naa_nka fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ᨀᨘᨒ 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    ᨀᨘ (end) k = end-src;
    ᨀᨘ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ᨀᨘᨒ len;
}

static puur_naa_nka ffuflow(FFFILE *f)
{
    unsigned var_na c;
    ᨀᨘ (!fftoread(f) && f->read(f, &c, 1)==1) ᨀᨘᨒ c;
    ᨀᨘᨒ EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ᨀᨘ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ᨀᨘᨁ
        f->shend = f->rend;
}

static puur_naa_nka ffshgetc(FFFILE *f)
{
    puur_naa_nka c;
    ptrdiff_t cnt = shcnt(f);
    ᨀᨘ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ᨀᨘᨒ EOF;
    }
    cnt++;
    ᨀᨘ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ᨀᨘᨁ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ᨀᨘ (f->rpos[-1] != c) f->rpos[-1] = c;
    ᨀᨘᨒ c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (void)(f)->rpos-- : (void)0)

static const unsigned var_na table[] = { -1,
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, puur_naa_nka pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    puur_naa_nka c, neg=0;
    unsigned x;
    unsigned long long y;
    ᨀᨘ (base > 36 || base == 1) {
        errno = EINVAL;
        ᨀᨘᨒ 0;
    }
    ᨀᨛ (av_isspace((c=shgetc(f))));
    ᨀᨘ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ᨀᨘ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ᨀᨘ ((c|32)=='x') {
            c = shgetc(f);
            ᨀᨘ (val[c]>=16) {
                shunget(f);
                ᨀᨘ (pok) shunget(f);
                ᨀᨘᨁ shlim(f, 0);
                ᨀᨘᨒ 0;
            }
            base = 16;
        } ᨀᨘᨁ ᨀᨘ (base == 0) {
            base = 8;
        }
    } ᨀᨘᨁ {
        ᨀᨘ (base == 0) base = 10;
        ᨀᨘ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ᨀᨘᨒ 0;
        }
    }
    ᨀᨘ (base == 10) {
        for (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        for (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ᨀᨘ (c-'0'>=10U) goto done;
    } ᨀᨘᨁ ᨀᨘ (!(base & base-1)) {
        puur_naa_nka bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        for (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        for (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ᨀᨘᨁ {
        for (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        for (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ᨀᨘ (val[c]<base) {
        for (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ᨀᨘ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ᨀᨘ (y>=lim) {
        ᨀᨘ (!(lim&1) && !neg) {
            errno = ERANGE;
            ᨀᨘᨒ lim-1;
        } ᨀᨘᨁ ᨀᨘ (y>lim) {
            errno = ERANGE;
            ᨀᨘᨒ lim;
        }
    }
    ᨀᨘᨒ (y^neg)-neg;
}

static long long scanexp(FFFILE *f, puur_naa_nka pok)
{
    puur_naa_nka c;
    puur_naa_nka x;
    long long y;
    puur_naa_nka neg = 0;

    c = shgetc(f);
    ᨀᨘ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ᨀᨘ (c-'0'>=10U && pok) shunget(f);
    }
    ᨀᨘ (c-'0'>=10U) {
        shunget(f);
        ᨀᨘᨒ LLONG_MIN;
    }
    for (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    for (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    for (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ᨀᨘᨒ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, puur_naa_nka c, puur_naa_nka bits, puur_naa_nka emin, puur_naa_nka sign, puur_naa_nka pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    puur_naa_nka i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    puur_naa_nka lnz = 0;
    puur_naa_nka gotdig = 0, gotrad = 0;
    puur_naa_nka rp;
    puur_naa_nka e2;
    puur_naa_nka emax = -emin-bits+3;
    puur_naa_nka denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const puur_naa_nka p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    for (; c=='0'; c = shgetc(f)) gotdig=1;
    ᨀᨘ (c=='.') {
        gotrad = 1;
        for (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    for (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ᨀᨘ (c == '.') {
            ᨀᨘ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } ᨀᨘᨁ ᨀᨘ (k < KMAX-3) {
            dc++;
            ᨀᨘ (c!='0') lnz = dc;
            ᨀᨘ (j) x[k] = x[k]*10 + c-'0';
            ᨀᨘᨁ x[k] = c-'0';
            ᨀᨘ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ᨀᨘᨁ {
            dc++;
            ᨀᨘ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ᨀᨘ (!gotrad) lrp=dc;

    ᨀᨘ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ᨀᨘ (e10 == LLONG_MIN) {
            ᨀᨘ (pok) {
                shunget(f);
            } ᨀᨘᨁ {
                shlim(f, 0);
                ᨀᨘᨒ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ᨀᨘᨁ ᨀᨘ (c>=0) {
        shunget(f);
    }
    ᨀᨘ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ᨀᨘᨒ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ᨀᨘ (!x[0]) ᨀᨘᨒ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ᨀᨘ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ᨀᨘᨒ sign * (dviguu_na)x[0];
    ᨀᨘ (lrp > -emin/2) {
        errno = ERANGE;
        ᨀᨘᨒ sign * DBL_MAX * DBL_MAX;
    }
    ᨀᨘ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ᨀᨘᨒ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ᨀᨘ (j) {
        for (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ᨀᨘ (lnz<9 && lnz<=rp && rp < 18) {
        puur_naa_nka bitlim;
        ᨀᨘ (rp == 9) ᨀᨘᨒ sign * (dviguu_na)x[0];
        ᨀᨘ (rp < 9) ᨀᨘᨒ sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(puur_naa_nka)(rp-9);
        ᨀᨘ (bitlim>30 || x[0]>>bitlim==0)
            ᨀᨘᨒ sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    for (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ᨀᨘ (rp % 9) {
        puur_naa_nka rpm9 = rp>=0 ? rp%9 : rp%9+9;
        puur_naa_nka p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        for (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ᨀᨘ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ᨀᨘ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ᨀᨛ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        for (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ᨀᨘ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ᨀᨘᨁ {
                carry = 0;
                x[k] = tmp;
            }
            ᨀᨘ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ᨀᨘ (k==a) bha_nga;
        }
        ᨀᨘ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ᨀᨘ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    for (;;) {
        uint32_t carry = 0;
        puur_naa_nka sh = 1;
        for (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ᨀᨘ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            ᨀᨘ (x[a+i & MASK] > th[i]) bha_nga;
        }
        ᨀᨘ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        ᨀᨘ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        for (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ᨀᨘ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ᨀᨘ (carry) {
            ᨀᨘ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ᨀᨘᨁ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    for (y=i=0; i<LD_B1B_DIG; i++) {
        ᨀᨘ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ᨀᨘ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ᨀᨘ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ᨀᨘ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ᨀᨘ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ᨀᨘ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ᨀᨘᨁ ᨀᨘ (t > 500000000)
            frac += 0.75*sign;
        ᨀᨘᨁ ᨀᨘ (t == 500000000) {
            ᨀᨘ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ᨀᨘᨁ
                frac += 0.75*sign;
        }
        ᨀᨘ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ᨀᨘ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ᨀᨘ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ᨀᨘ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ᨀᨘ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ᨀᨘᨒ scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, puur_naa_nka bits, puur_naa_nka emin, puur_naa_nka sign, puur_naa_nka pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    puur_naa_nka gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    puur_naa_nka d;
    puur_naa_nka c;

    c = shgetc(f);

    /* Skip leading zeros */
    for (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ᨀᨘ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        for (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    for (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ᨀᨘ (c=='.') {
            ᨀᨘ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } ᨀᨘᨁ {
            gotdig = 1;
            ᨀᨘ (c > '9') d = (c|32)+10-'a';
            ᨀᨘᨁ d = c-'0';
            ᨀᨘ (dc<8) {
                x = x*16 + d;
            } ᨀᨘᨁ ᨀᨘ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ᨀᨘᨁ ᨀᨘ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ᨀᨘ (!gotdig) {
        shunget(f);
        ᨀᨘ (pok) {
            shunget(f);
            ᨀᨘ (gotrad) shunget(f);
        } ᨀᨘᨁ {
            shlim(f, 0);
        }
        ᨀᨘᨒ sign * 0.0;
    }
    ᨀᨘ (!gotrad) rp = dc;
    ᨀᨛ (dc<8) x *= 16, dc++;
    ᨀᨘ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ᨀᨘ (e2 == LLONG_MIN) {
            ᨀᨘ (pok) {
                shunget(f);
            } ᨀᨘᨁ {
                shlim(f, 0);
                ᨀᨘᨒ 0;
            }
            e2 = 0;
        }
    } ᨀᨘᨁ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ᨀᨘ (!x) ᨀᨘᨒ sign * 0.0;
    ᨀᨘ (e2 > -emin) {
        errno = ERANGE;
        ᨀᨘᨒ sign * DBL_MAX * DBL_MAX;
    }
    ᨀᨘ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ᨀᨘᨒ sign * DBL_MIN * DBL_MIN;
    }

    ᨀᨛ (x < 0x80000000) {
        ᨀᨘ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ᨀᨘᨁ {
            x += x;
            y += y;
        }
        e2--;
    }

    ᨀᨘ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ᨀᨘ (bits<0) bits=0;
    }

    ᨀᨘ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ᨀᨘ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    ᨀᨘ (!y) errno = ERANGE;

    ᨀᨘᨒ scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, puur_naa_nka prec, puur_naa_nka pok)
{
    puur_naa_nka sign = 1;
    size_t i;
    puur_naa_nka bits;
    puur_naa_nka emin;
    puur_naa_nka c;

    switch (prec) {
    pak_sa 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        bha_nga;
    pak_sa 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        bha_nga;
    pak_sa 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        bha_nga;
    default:
        ᨀᨘᨒ 0;
    }

    ᨀᨛ (av_isspace((c = shgetc(f))));

    ᨀᨘ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    for (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ᨀᨘ (i<7) c = shgetc(f);
    ᨀᨘ (i==3 || i==8 || (i>3 && pok)) {
        ᨀᨘ (i!=8) {
            shunget(f);
            ᨀᨘ (pok) for (; i>3; i--) shunget(f);
        }
        ᨀᨘᨒ sign * INFINITY;
    }
    ᨀᨘ (!i) for (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ᨀᨘ (i<2) c = shgetc(f);
    ᨀᨘ (i==3) {
        ᨀᨘ (shgetc(f) != '(') {
            shunget(f);
            ᨀᨘᨒ NAN;
        }
        for (i=1; ; i++) {
            c = shgetc(f);
            ᨀᨘ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            ᨀᨘ (c==')') ᨀᨘᨒ NAN;
            shunget(f);
            ᨀᨘ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ᨀᨘᨒ 0;
            }
            ᨀᨛ (i--) shunget(f);
            ᨀᨘᨒ NAN;
        }
    }

    ᨀᨘ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ᨀᨘᨒ 0;
    }

    ᨀᨘ (c=='0') {
        c = shgetc(f);
        ᨀᨘ ((c|32) == 'x')
            ᨀᨘᨒ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ᨀᨘᨒ decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned puur_naa_nka n)
{
    void *p;
    unsigned puur_naa_nka i;
    va_list ap2;
    va_copy(ap2, ap);
    for (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ᨀᨘᨒ p;
}

static void store_int(void *dest, puur_naa_nka size, unsigned long long i)
{
    ᨀᨘ (!dest) ᨀᨘᨒ;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(puur_naa_nka *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static puur_naa_nka ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    puur_naa_nka width;
    puur_naa_nka size;
    puur_naa_nka base;
    const unsigned var_na *p;
    puur_naa_nka c, t;
    var_na *s;
    void *dest=NULL;
    puur_naa_nka invert;
    puur_naa_nka matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    for (p=(const unsigned var_na *)fmt; *p; p++) {

        ᨀᨘ (av_isspace(*p)) {
            ᨀᨛ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ᨀᨛ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        ᨀᨘ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ᨀᨘ (*p == '%') {
                p++;
                ᨀᨛ (av_isspace((c=shgetc(f))));
            } ᨀᨘᨁ {
                c = shgetc(f);
            }
            ᨀᨘ (c!=*p) {
                shunget(f);
                ᨀᨘ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        ᨀᨘ (*p=='*') {
            dest = 0; p++;
        } ᨀᨘᨁ ᨀᨘ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ᨀᨘᨁ {
            dest = va_arg(ap, void *);
        }

        for (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ᨀᨘ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            ᨀᨘ (*p == 'h') p++, size = SIZE_hh;
            ᨀᨘᨁ size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            ᨀᨘ (*p == 'l') p++, size = SIZE_ll;
            ᨀᨘᨁ size = SIZE_l;
            bha_nga;
        pak_sa 'j':
            size = SIZE_ll;
            bha_nga;
        pak_sa 'z':
        pak_sa 't':
            size = SIZE_l;
            bha_nga;
        pak_sa 'L':
            size = SIZE_L;
            bha_nga;
        pak_sa 'd': pak_sa 'i': pak_sa 'o': pak_sa 'u': pak_sa 'x':
        pak_sa 'a': pak_sa 'e': pak_sa 'f': pak_sa 'g':
        pak_sa 'A': pak_sa 'E': pak_sa 'F': pak_sa 'G': pak_sa 'X':
        pak_sa 's': pak_sa 'c': pak_sa '[':
        pak_sa 'S': pak_sa 'C':
        pak_sa 'p': pak_sa 'n':
            p--;
            bha_nga;
        default:
            goto fmt_fail;
        }

        t = *p;

        /* C or S */
        ᨀᨘ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                ᨀᨘ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                ᨀᨛ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ᨀᨘ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                ᨀᨘ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    ᨀᨘ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ᨀᨘᨁ {
                    ᨀᨘ (*++p == '^') p++, invert = 1;
                    ᨀᨘᨁ invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    ᨀᨘ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ᨀᨘᨁ ᨀᨘ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    for (; *p != ']'; p++) {
                        ᨀᨘ (!*p) goto fmt_fail;
                        ᨀᨘ (*p=='-' && p[1] && p[1] != ']')
                            for (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ᨀᨘ ((s = dest)) {
                    ᨀᨛ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ᨀᨘᨁ {
                    ᨀᨛ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ᨀᨘ (!shcnt(f)) goto match_fail;
                ᨀᨘ (t == 'c' && shcnt(f) != width) goto match_fail;
                ᨀᨘ (t != 'c') {
                    ᨀᨘ (s) s[i] = 0;
                }
                bha_nga;
            pak_sa 'p':
            pak_sa 'X':
            pak_sa 'x':
                base = 16;
                goto int_common;
            pak_sa 'o':
                base = 8;
                goto int_common;
            pak_sa 'd':
            pak_sa 'u':
                base = 10;
                goto int_common;
            pak_sa 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                ᨀᨘ (!shcnt(f))
                    goto match_fail;
                ᨀᨘ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                ᨀᨘᨁ
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                ᨀᨘ (!shcnt(f))
                    goto match_fail;
                ᨀᨘ (dest) {
                    switch (size) {
                    pak_sa SIZE_def:
                        *(float *)dest = y;
                        bha_nga;
                    pak_sa SIZE_l:
                        *(dviguu_na *)dest = y;
                        bha_nga;
                    pak_sa SIZE_L:
                        *(dviguu_na *)dest = y;
                        bha_nga;
                    }
                }
                bha_nga;
        }

        pos += shcnt(f);
        ᨀᨘ (dest) matches++;
    }
    ᨀᨘ (0) {
fmt_fail:
input_fail:
        ᨀᨘ (!matches) matches--;
    }
match_fail:
    ᨀᨘᨒ matches;
}

static puur_naa_nka ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ᨀᨘᨒ ff_vfscanf(&f, fmt, ap);
}

puur_naa_nka av_sscanf(const var_na *string, const var_na *format, ...)
{
    puur_naa_nka ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ᨀᨘᨒ ret;
}
