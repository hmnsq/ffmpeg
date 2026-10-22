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

static ចំនួនគត់ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ត្រឡប់ 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    ប្រសិនបើ (end) k = end-src;
    ប្រសិនបើ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ត្រឡប់ len;
}

static ចំនួនគត់ ffuflow(FFFILE *f)
{
    unsigned var_na c;
    ប្រសិនបើ (!fftoread(f) && f->read(f, &c, 1)==1) ត្រឡប់ c;
    ត្រឡប់ EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ប្រសិនបើ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    បើមិនដូច្នេះ
        f->shend = f->rend;
}

static ចំនួនគត់ ffshgetc(FFFILE *f)
{
    ចំនួនគត់ c;
    ptrdiff_t cnt = shcnt(f);
    ប្រសិនបើ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ត្រឡប់ EOF;
    }
    cnt++;
    ប្រសិនបើ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    បើមិនដូច្នេះ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ប្រសិនបើ (f->rpos[-1] != c) f->rpos[-1] = c;
    ត្រឡប់ c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, ចំនួនគត់ pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    ចំនួនគត់ c, neg=0;
    unsigned x;
    unsigned long long y;
    ប្រសិនបើ (base > 36 || base == 1) {
        errno = EINVAL;
        ត្រឡប់ 0;
    }
    ខណៈពេល (av_isspace((c=shgetc(f))));
    ប្រសិនបើ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ប្រសិនបើ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ប្រសិនបើ ((c|32)=='x') {
            c = shgetc(f);
            ប្រសិនបើ (val[c]>=16) {
                shunget(f);
                ប្រសិនបើ (pok) shunget(f);
                បើមិនដូច្នេះ shlim(f, 0);
                ត្រឡប់ 0;
            }
            base = 16;
        } បើមិនដូច្នេះ ប្រសិនបើ (base == 0) {
            base = 8;
        }
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (base == 0) base = 10;
        ប្រសិនបើ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ត្រឡប់ 0;
        }
    }
    ប្រសិនបើ (base == 10) {
        សម្រាប់ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        សម្រាប់ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ប្រសិនបើ (c-'0'>=10U) goto done;
    } បើមិនដូច្នេះ ប្រសិនបើ (!(base & base-1)) {
        ចំនួនគត់ bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        សម្រាប់ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        សម្រាប់ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } បើមិនដូច្នេះ {
        សម្រាប់ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        សម្រាប់ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ប្រសិនបើ (val[c]<base) {
        សម្រាប់ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ប្រសិនបើ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ប្រសិនបើ (y>=lim) {
        ប្រសិនបើ (!(lim&1) && !neg) {
            errno = ERANGE;
            ត្រឡប់ lim-1;
        } បើមិនដូច្នេះ ប្រសិនបើ (y>lim) {
            errno = ERANGE;
            ត្រឡប់ lim;
        }
    }
    ត្រឡប់ (y^neg)-neg;
}

static long long scanexp(FFFILE *f, ចំនួនគត់ pok)
{
    ចំនួនគត់ c;
    ចំនួនគត់ x;
    long long y;
    ចំនួនគត់ neg = 0;

    c = shgetc(f);
    ប្រសិនបើ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ប្រសិនបើ (c-'0'>=10U && pok) shunget(f);
    }
    ប្រសិនបើ (c-'0'>=10U) {
        shunget(f);
        ត្រឡប់ LLONG_MIN;
    }
    សម្រាប់ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    សម្រាប់ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    សម្រាប់ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ត្រឡប់ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, ចំនួនគត់ c, ចំនួនគត់ bits, ចំនួនគត់ emin, ចំនួនគត់ sign, ចំនួនគត់ pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    ចំនួនគត់ i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ចំនួនគត់ lnz = 0;
    ចំនួនគត់ gotdig = 0, gotrad = 0;
    ចំនួនគត់ rp;
    ចំនួនគត់ e2;
    ចំនួនគត់ emax = -emin-bits+3;
    ចំនួនគត់ denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const ចំនួនគត់ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    សម្រាប់ (; c=='0'; c = shgetc(f)) gotdig=1;
    ប្រសិនបើ (c=='.') {
        gotrad = 1;
        សម្រាប់ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    សម្រាប់ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ប្រសិនបើ (c == '.') {
            ប្រសិនបើ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } បើមិនដូច្នេះ ប្រសិនបើ (k < KMAX-3) {
            dc++;
            ប្រសិនបើ (c!='0') lnz = dc;
            ប្រសិនបើ (j) x[k] = x[k]*10 + c-'0';
            បើមិនដូច្នេះ x[k] = c-'0';
            ប្រសិនបើ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } បើមិនដូច្នេះ {
            dc++;
            ប្រសិនបើ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ប្រសិនបើ (!gotrad) lrp=dc;

    ប្រសិនបើ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ប្រសិនបើ (e10 == LLONG_MIN) {
            ប្រសិនបើ (pok) {
                shunget(f);
            } បើមិនដូច្នេះ {
                shlim(f, 0);
                ត្រឡប់ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } បើមិនដូច្នេះ ប្រសិនបើ (c>=0) {
        shunget(f);
    }
    ប្រសិនបើ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ត្រឡប់ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ប្រសិនបើ (!x[0]) ត្រឡប់ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ប្រសិនបើ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ត្រឡប់ sign * (dviguu_na)x[0];
    ប្រសិនបើ (lrp > -emin/2) {
        errno = ERANGE;
        ត្រឡប់ sign * DBL_MAX * DBL_MAX;
    }
    ប្រសិនបើ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ត្រឡប់ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ប្រសិនបើ (j) {
        សម្រាប់ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ប្រសិនបើ (lnz<9 && lnz<=rp && rp < 18) {
        ចំនួនគត់ bitlim;
        ប្រសិនបើ (rp == 9) ត្រឡប់ sign * (dviguu_na)x[0];
        ប្រសិនបើ (rp < 9) ត្រឡប់ sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(ចំនួនគត់)(rp-9);
        ប្រសិនបើ (bitlim>30 || x[0]>>bitlim==0)
            ត្រឡប់ sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    សម្រាប់ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ប្រសិនបើ (rp % 9) {
        ចំនួនគត់ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ចំនួនគត់ p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        សម្រាប់ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ប្រសិនបើ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ប្រសិនបើ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ខណៈពេល (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        សម្រាប់ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ប្រសិនបើ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } បើមិនដូច្នេះ {
                carry = 0;
                x[k] = tmp;
            }
            ប្រសិនបើ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ប្រសិនបើ (k==a) bha_nga;
        }
        ប្រសិនបើ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ប្រសិនបើ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    សម្រាប់ (;;) {
        uint32_t carry = 0;
        ចំនួនគត់ sh = 1;
        សម្រាប់ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ប្រសិនបើ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            ប្រសិនបើ (x[a+i & MASK] > th[i]) bha_nga;
        }
        ប្រសិនបើ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        ប្រសិនបើ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        សម្រាប់ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ប្រសិនបើ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ប្រសិនបើ (carry) {
            ប្រសិនបើ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } បើមិនដូច្នេះ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    សម្រាប់ (y=i=0; i<LD_B1B_DIG; i++) {
        ប្រសិនបើ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ប្រសិនបើ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ប្រសិនបើ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ប្រសិនបើ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ប្រសិនបើ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ប្រសិនបើ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        បើមិនដូច្នេះ ប្រសិនបើ (t > 500000000)
            frac += 0.75*sign;
        បើមិនដូច្នេះ ប្រសិនបើ (t == 500000000) {
            ប្រសិនបើ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            បើមិនដូច្នេះ
                frac += 0.75*sign;
        }
        ប្រសិនបើ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ប្រសិនបើ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ប្រសិនបើ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ប្រសិនបើ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ប្រសិនបើ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ត្រឡប់ scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, ចំនួនគត់ bits, ចំនួនគត់ emin, ចំនួនគត់ sign, ចំនួនគត់ pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    ចំនួនគត់ gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ចំនួនគត់ d;
    ចំនួនគត់ c;

    c = shgetc(f);

    /* Skip leading zeros */
    សម្រាប់ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ប្រសិនបើ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        សម្រាប់ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    សម្រាប់ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ប្រសិនបើ (c=='.') {
            ប្រសិនបើ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } បើមិនដូច្នេះ {
            gotdig = 1;
            ប្រសិនបើ (c > '9') d = (c|32)+10-'a';
            បើមិនដូច្នេះ d = c-'0';
            ប្រសិនបើ (dc<8) {
                x = x*16 + d;
            } បើមិនដូច្នេះ ប្រសិនបើ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } បើមិនដូច្នេះ ប្រសិនបើ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ប្រសិនបើ (!gotdig) {
        shunget(f);
        ប្រសិនបើ (pok) {
            shunget(f);
            ប្រសិនបើ (gotrad) shunget(f);
        } បើមិនដូច្នេះ {
            shlim(f, 0);
        }
        ត្រឡប់ sign * 0.0;
    }
    ប្រសិនបើ (!gotrad) rp = dc;
    ខណៈពេល (dc<8) x *= 16, dc++;
    ប្រសិនបើ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ប្រសិនបើ (e2 == LLONG_MIN) {
            ប្រសិនបើ (pok) {
                shunget(f);
            } បើមិនដូច្នេះ {
                shlim(f, 0);
                ត្រឡប់ 0;
            }
            e2 = 0;
        }
    } បើមិនដូច្នេះ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ប្រសិនបើ (!x) ត្រឡប់ sign * 0.0;
    ប្រសិនបើ (e2 > -emin) {
        errno = ERANGE;
        ត្រឡប់ sign * DBL_MAX * DBL_MAX;
    }
    ប្រសិនបើ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ត្រឡប់ sign * DBL_MIN * DBL_MIN;
    }

    ខណៈពេល (x < 0x80000000) {
        ប្រសិនបើ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } បើមិនដូច្នេះ {
            x += x;
            y += y;
        }
        e2--;
    }

    ប្រសិនបើ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ប្រសិនបើ (bits<0) bits=0;
    }

    ប្រសិនបើ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ប្រសិនបើ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    ប្រសិនបើ (!y) errno = ERANGE;

    ត្រឡប់ scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, ចំនួនគត់ prec, ចំនួនគត់ pok)
{
    ចំនួនគត់ sign = 1;
    size_t i;
    ចំនួនគត់ bits;
    ចំនួនគត់ emin;
    ចំនួនគត់ c;

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
        ត្រឡប់ 0;
    }

    ខណៈពេល (av_isspace((c = shgetc(f))));

    ប្រសិនបើ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    សម្រាប់ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ប្រសិនបើ (i<7) c = shgetc(f);
    ប្រសិនបើ (i==3 || i==8 || (i>3 && pok)) {
        ប្រសិនបើ (i!=8) {
            shunget(f);
            ប្រសិនបើ (pok) សម្រាប់ (; i>3; i--) shunget(f);
        }
        ត្រឡប់ sign * INFINITY;
    }
    ប្រសិនបើ (!i) សម្រាប់ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ប្រសិនបើ (i<2) c = shgetc(f);
    ប្រសិនបើ (i==3) {
        ប្រសិនបើ (shgetc(f) != '(') {
            shunget(f);
            ត្រឡប់ NAN;
        }
        សម្រាប់ (i=1; ; i++) {
            c = shgetc(f);
            ប្រសិនបើ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            ប្រសិនបើ (c==')') ត្រឡប់ NAN;
            shunget(f);
            ប្រសិនបើ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ត្រឡប់ 0;
            }
            ខណៈពេល (i--) shunget(f);
            ត្រឡប់ NAN;
        }
    }

    ប្រសិនបើ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ត្រឡប់ 0;
    }

    ប្រសិនបើ (c=='0') {
        c = shgetc(f);
        ប្រសិនបើ ((c|32) == 'x')
            ត្រឡប់ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ត្រឡប់ decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned ចំនួនគត់ n)
{
    void *p;
    unsigned ចំនួនគត់ i;
    va_list ap2;
    va_copy(ap2, ap);
    សម្រាប់ (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ត្រឡប់ p;
}

static void store_int(void *dest, ចំនួនគត់ size, unsigned long long i)
{
    ប្រសិនបើ (!dest) ត្រឡប់;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(ចំនួនគត់ *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static ចំនួនគត់ ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    ចំនួនគត់ width;
    ចំនួនគត់ size;
    ចំនួនគត់ base;
    const unsigned var_na *p;
    ចំនួនគត់ c, t;
    var_na *s;
    void *dest=NULL;
    ចំនួនគត់ invert;
    ចំនួនគត់ matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    សម្រាប់ (p=(const unsigned var_na *)fmt; *p; p++) {

        ប្រសិនបើ (av_isspace(*p)) {
            ខណៈពេល (av_isspace(p[1])) p++;
            shlim(f, 0);
            ខណៈពេល (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        ប្រសិនបើ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ប្រសិនបើ (*p == '%') {
                p++;
                ខណៈពេល (av_isspace((c=shgetc(f))));
            } បើមិនដូច្នេះ {
                c = shgetc(f);
            }
            ប្រសិនបើ (c!=*p) {
                shunget(f);
                ប្រសិនបើ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        ប្រសិនបើ (*p=='*') {
            dest = 0; p++;
        } បើមិនដូច្នេះ ប្រសិនបើ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } បើមិនដូច្នេះ {
            dest = va_arg(ap, void *);
        }

        សម្រាប់ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ប្រសិនបើ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            ប្រសិនបើ (*p == 'h') p++, size = SIZE_hh;
            បើមិនដូច្នេះ size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            ប្រសិនបើ (*p == 'l') p++, size = SIZE_ll;
            បើមិនដូច្នេះ size = SIZE_l;
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
        ប្រសិនបើ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                ប្រសិនបើ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                ខណៈពេល (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ប្រសិនបើ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                ប្រសិនបើ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    ប្រសិនបើ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } បើមិនដូច្នេះ {
                    ប្រសិនបើ (*++p == '^') p++, invert = 1;
                    បើមិនដូច្នេះ invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    ប្រសិនបើ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    បើមិនដូច្នេះ ប្រសិនបើ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    សម្រាប់ (; *p != ']'; p++) {
                        ប្រសិនបើ (!*p) goto fmt_fail;
                        ប្រសិនបើ (*p=='-' && p[1] && p[1] != ']')
                            សម្រាប់ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ប្រសិនបើ ((s = dest)) {
                    ខណៈពេល (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } បើមិនដូច្នេះ {
                    ខណៈពេល (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ប្រសិនបើ (!shcnt(f)) goto match_fail;
                ប្រសិនបើ (t == 'c' && shcnt(f) != width) goto match_fail;
                ប្រសិនបើ (t != 'c') {
                    ប្រសិនបើ (s) s[i] = 0;
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
                ប្រសិនបើ (!shcnt(f))
                    goto match_fail;
                ប្រសិនបើ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                បើមិនដូច្នេះ
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                ប្រសិនបើ (!shcnt(f))
                    goto match_fail;
                ប្រសិនបើ (dest) {
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
        ប្រសិនបើ (dest) matches++;
    }
    ប្រសិនបើ (0) {
fmt_fail:
input_fail:
        ប្រសិនបើ (!matches) matches--;
    }
match_fail:
    ត្រឡប់ matches;
}

static ចំនួនគត់ ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ត្រឡប់ ff_vfscanf(&f, fmt, ap);
}

ចំនួនគត់ av_sscanf(const var_na *string, const var_na *format, ...)
{
    ចំនួនគត់ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ត្រឡប់ ret;
}
