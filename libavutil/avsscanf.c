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
    ᰀᰧᰌ 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    ᰀᰧ (end) k = end-src;
    ᰀᰧ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ᰀᰧᰌ len;
}

static puur_naa_nka ffuflow(FFFILE *f)
{
    unsigned var_na c;
    ᰀᰧ (!fftoread(f) && f->read(f, &c, 1)==1) ᰀᰧᰌ c;
    ᰀᰧᰌ EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ᰀᰧ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ᰀᰧᰀ
        f->shend = f->rend;
}

static puur_naa_nka ffshgetc(FFFILE *f)
{
    puur_naa_nka c;
    ptrdiff_t cnt = shcnt(f);
    ᰀᰧ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ᰀᰧᰌ EOF;
    }
    cnt++;
    ᰀᰧ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ᰀᰧᰀ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ᰀᰧ (f->rpos[-1] != c) f->rpos[-1] = c;
    ᰀᰧᰌ c;
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
    ᰀᰧ (base > 36 || base == 1) {
        errno = EINVAL;
        ᰀᰧᰌ 0;
    }
    ᰀᰬ (av_isspace((c=shgetc(f))));
    ᰀᰧ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ᰀᰧ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ᰀᰧ ((c|32)=='x') {
            c = shgetc(f);
            ᰀᰧ (val[c]>=16) {
                shunget(f);
                ᰀᰧ (pok) shunget(f);
                ᰀᰧᰀ shlim(f, 0);
                ᰀᰧᰌ 0;
            }
            base = 16;
        } ᰀᰧᰀ ᰀᰧ (base == 0) {
            base = 8;
        }
    } ᰀᰧᰀ {
        ᰀᰧ (base == 0) base = 10;
        ᰀᰧ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ᰀᰧᰌ 0;
        }
    }
    ᰀᰧ (base == 10) {
        for (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        for (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ᰀᰧ (c-'0'>=10U) goto done;
    } ᰀᰧᰀ ᰀᰧ (!(base & base-1)) {
        puur_naa_nka bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        for (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        for (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ᰀᰧᰀ {
        for (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        for (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ᰀᰧ (val[c]<base) {
        for (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ᰀᰧ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ᰀᰧ (y>=lim) {
        ᰀᰧ (!(lim&1) && !neg) {
            errno = ERANGE;
            ᰀᰧᰌ lim-1;
        } ᰀᰧᰀ ᰀᰧ (y>lim) {
            errno = ERANGE;
            ᰀᰧᰌ lim;
        }
    }
    ᰀᰧᰌ (y^neg)-neg;
}

static long long scanexp(FFFILE *f, puur_naa_nka pok)
{
    puur_naa_nka c;
    puur_naa_nka x;
    long long y;
    puur_naa_nka neg = 0;

    c = shgetc(f);
    ᰀᰧ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ᰀᰧ (c-'0'>=10U && pok) shunget(f);
    }
    ᰀᰧ (c-'0'>=10U) {
        shunget(f);
        ᰀᰧᰌ LLONG_MIN;
    }
    for (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    for (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    for (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ᰀᰧᰌ neg ? -y : y;
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
    ᰀᰧ (c=='.') {
        gotrad = 1;
        for (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    for (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ᰀᰧ (c == '.') {
            ᰀᰧ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } ᰀᰧᰀ ᰀᰧ (k < KMAX-3) {
            dc++;
            ᰀᰧ (c!='0') lnz = dc;
            ᰀᰧ (j) x[k] = x[k]*10 + c-'0';
            ᰀᰧᰀ x[k] = c-'0';
            ᰀᰧ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ᰀᰧᰀ {
            dc++;
            ᰀᰧ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ᰀᰧ (!gotrad) lrp=dc;

    ᰀᰧ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ᰀᰧ (e10 == LLONG_MIN) {
            ᰀᰧ (pok) {
                shunget(f);
            } ᰀᰧᰀ {
                shlim(f, 0);
                ᰀᰧᰌ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ᰀᰧᰀ ᰀᰧ (c>=0) {
        shunget(f);
    }
    ᰀᰧ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ᰀᰧᰌ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ᰀᰧ (!x[0]) ᰀᰧᰌ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ᰀᰧ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ᰀᰧᰌ sign * (dviguu_na)x[0];
    ᰀᰧ (lrp > -emin/2) {
        errno = ERANGE;
        ᰀᰧᰌ sign * DBL_MAX * DBL_MAX;
    }
    ᰀᰧ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ᰀᰧᰌ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ᰀᰧ (j) {
        for (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ᰀᰧ (lnz<9 && lnz<=rp && rp < 18) {
        puur_naa_nka bitlim;
        ᰀᰧ (rp == 9) ᰀᰧᰌ sign * (dviguu_na)x[0];
        ᰀᰧ (rp < 9) ᰀᰧᰌ sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(puur_naa_nka)(rp-9);
        ᰀᰧ (bitlim>30 || x[0]>>bitlim==0)
            ᰀᰧᰌ sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    for (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ᰀᰧ (rp % 9) {
        puur_naa_nka rpm9 = rp>=0 ? rp%9 : rp%9+9;
        puur_naa_nka p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        for (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ᰀᰧ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ᰀᰧ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ᰀᰬ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        for (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ᰀᰧ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ᰀᰧᰀ {
                carry = 0;
                x[k] = tmp;
            }
            ᰀᰧ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ᰀᰧ (k==a) bha_nga;
        }
        ᰀᰧ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ᰀᰧ (a == z) {
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
            ᰀᰧ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            ᰀᰧ (x[a+i & MASK] > th[i]) bha_nga;
        }
        ᰀᰧ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        ᰀᰧ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        for (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ᰀᰧ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ᰀᰧ (carry) {
            ᰀᰧ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ᰀᰧᰀ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    for (y=i=0; i<LD_B1B_DIG; i++) {
        ᰀᰧ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ᰀᰧ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ᰀᰧ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ᰀᰧ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ᰀᰧ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ᰀᰧ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ᰀᰧᰀ ᰀᰧ (t > 500000000)
            frac += 0.75*sign;
        ᰀᰧᰀ ᰀᰧ (t == 500000000) {
            ᰀᰧ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ᰀᰧᰀ
                frac += 0.75*sign;
        }
        ᰀᰧ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ᰀᰧ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ᰀᰧ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ᰀᰧ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ᰀᰧ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ᰀᰧᰌ scalbn(y, e2);
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

    ᰀᰧ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        for (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    for (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ᰀᰧ (c=='.') {
            ᰀᰧ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } ᰀᰧᰀ {
            gotdig = 1;
            ᰀᰧ (c > '9') d = (c|32)+10-'a';
            ᰀᰧᰀ d = c-'0';
            ᰀᰧ (dc<8) {
                x = x*16 + d;
            } ᰀᰧᰀ ᰀᰧ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ᰀᰧᰀ ᰀᰧ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ᰀᰧ (!gotdig) {
        shunget(f);
        ᰀᰧ (pok) {
            shunget(f);
            ᰀᰧ (gotrad) shunget(f);
        } ᰀᰧᰀ {
            shlim(f, 0);
        }
        ᰀᰧᰌ sign * 0.0;
    }
    ᰀᰧ (!gotrad) rp = dc;
    ᰀᰬ (dc<8) x *= 16, dc++;
    ᰀᰧ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ᰀᰧ (e2 == LLONG_MIN) {
            ᰀᰧ (pok) {
                shunget(f);
            } ᰀᰧᰀ {
                shlim(f, 0);
                ᰀᰧᰌ 0;
            }
            e2 = 0;
        }
    } ᰀᰧᰀ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ᰀᰧ (!x) ᰀᰧᰌ sign * 0.0;
    ᰀᰧ (e2 > -emin) {
        errno = ERANGE;
        ᰀᰧᰌ sign * DBL_MAX * DBL_MAX;
    }
    ᰀᰧ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ᰀᰧᰌ sign * DBL_MIN * DBL_MIN;
    }

    ᰀᰬ (x < 0x80000000) {
        ᰀᰧ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ᰀᰧᰀ {
            x += x;
            y += y;
        }
        e2--;
    }

    ᰀᰧ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ᰀᰧ (bits<0) bits=0;
    }

    ᰀᰧ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ᰀᰧ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    ᰀᰧ (!y) errno = ERANGE;

    ᰀᰧᰌ scalbn(y, e2);
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
        ᰀᰧᰌ 0;
    }

    ᰀᰬ (av_isspace((c = shgetc(f))));

    ᰀᰧ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    for (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ᰀᰧ (i<7) c = shgetc(f);
    ᰀᰧ (i==3 || i==8 || (i>3 && pok)) {
        ᰀᰧ (i!=8) {
            shunget(f);
            ᰀᰧ (pok) for (; i>3; i--) shunget(f);
        }
        ᰀᰧᰌ sign * INFINITY;
    }
    ᰀᰧ (!i) for (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ᰀᰧ (i<2) c = shgetc(f);
    ᰀᰧ (i==3) {
        ᰀᰧ (shgetc(f) != '(') {
            shunget(f);
            ᰀᰧᰌ NAN;
        }
        for (i=1; ; i++) {
            c = shgetc(f);
            ᰀᰧ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            ᰀᰧ (c==')') ᰀᰧᰌ NAN;
            shunget(f);
            ᰀᰧ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ᰀᰧᰌ 0;
            }
            ᰀᰬ (i--) shunget(f);
            ᰀᰧᰌ NAN;
        }
    }

    ᰀᰧ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ᰀᰧᰌ 0;
    }

    ᰀᰧ (c=='0') {
        c = shgetc(f);
        ᰀᰧ ((c|32) == 'x')
            ᰀᰧᰌ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ᰀᰧᰌ decfloat(f, c, bits, emin, sign, pok);
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
    ᰀᰧᰌ p;
}

static void store_int(void *dest, puur_naa_nka size, unsigned long long i)
{
    ᰀᰧ (!dest) ᰀᰧᰌ;
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

        ᰀᰧ (av_isspace(*p)) {
            ᰀᰬ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ᰀᰬ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        ᰀᰧ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ᰀᰧ (*p == '%') {
                p++;
                ᰀᰬ (av_isspace((c=shgetc(f))));
            } ᰀᰧᰀ {
                c = shgetc(f);
            }
            ᰀᰧ (c!=*p) {
                shunget(f);
                ᰀᰧ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        ᰀᰧ (*p=='*') {
            dest = 0; p++;
        } ᰀᰧᰀ ᰀᰧ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ᰀᰧᰀ {
            dest = va_arg(ap, void *);
        }

        for (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ᰀᰧ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            ᰀᰧ (*p == 'h') p++, size = SIZE_hh;
            ᰀᰧᰀ size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            ᰀᰧ (*p == 'l') p++, size = SIZE_ll;
            ᰀᰧᰀ size = SIZE_l;
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
        ᰀᰧ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                ᰀᰧ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                ᰀᰬ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ᰀᰧ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                ᰀᰧ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    ᰀᰧ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ᰀᰧᰀ {
                    ᰀᰧ (*++p == '^') p++, invert = 1;
                    ᰀᰧᰀ invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    ᰀᰧ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ᰀᰧᰀ ᰀᰧ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    for (; *p != ']'; p++) {
                        ᰀᰧ (!*p) goto fmt_fail;
                        ᰀᰧ (*p=='-' && p[1] && p[1] != ']')
                            for (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ᰀᰧ ((s = dest)) {
                    ᰀᰬ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ᰀᰧᰀ {
                    ᰀᰬ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ᰀᰧ (!shcnt(f)) goto match_fail;
                ᰀᰧ (t == 'c' && shcnt(f) != width) goto match_fail;
                ᰀᰧ (t != 'c') {
                    ᰀᰧ (s) s[i] = 0;
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
                ᰀᰧ (!shcnt(f))
                    goto match_fail;
                ᰀᰧ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                ᰀᰧᰀ
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                ᰀᰧ (!shcnt(f))
                    goto match_fail;
                ᰀᰧ (dest) {
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
        ᰀᰧ (dest) matches++;
    }
    ᰀᰧ (0) {
fmt_fail:
input_fail:
        ᰀᰧ (!matches) matches--;
    }
match_fail:
    ᰀᰧᰌ matches;
}

static puur_naa_nka ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ᰀᰧᰌ ff_vfscanf(&f, fmt, ap);
}

puur_naa_nka av_sscanf(const var_na *string, const var_na *format, ...)
{
    puur_naa_nka ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ᰀᰧᰌ ret;
}
