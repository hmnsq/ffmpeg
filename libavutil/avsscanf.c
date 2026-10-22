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

static ကိန်းပြည့် fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ပြန်ပေး 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    အကယ်၍ (end) k = end-src;
    အကယ်၍ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ပြန်ပေး len;
}

static ကိန်းပြည့် ffuflow(FFFILE *f)
{
    unsigned var_na c;
    အကယ်၍ (!fftoread(f) && f->read(f, &c, 1)==1) ပြန်ပေး c;
    ပြန်ပေး EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    အကယ်၍ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    မဟုတ်ပါက
        f->shend = f->rend;
}

static ကိန်းပြည့် ffshgetc(FFFILE *f)
{
    ကိန်းပြည့် c;
    ptrdiff_t cnt = shcnt(f);
    အကယ်၍ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ပြန်ပေး EOF;
    }
    cnt++;
    အကယ်၍ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    မဟုတ်ပါက
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    အကယ်၍ (f->rpos[-1] != c) f->rpos[-1] = c;
    ပြန်ပေး c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, ကိန်းပြည့် pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    ကိန်းပြည့် c, neg=0;
    unsigned x;
    unsigned long long y;
    အကယ်၍ (base > 36 || base == 1) {
        errno = EINVAL;
        ပြန်ပေး 0;
    }
    နေစဉ် (av_isspace((c=shgetc(f))));
    အကယ်၍ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    အကယ်၍ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        အကယ်၍ ((c|32)=='x') {
            c = shgetc(f);
            အကယ်၍ (val[c]>=16) {
                shunget(f);
                အကယ်၍ (pok) shunget(f);
                မဟုတ်ပါက shlim(f, 0);
                ပြန်ပေး 0;
            }
            base = 16;
        } မဟုတ်ပါက အကယ်၍ (base == 0) {
            base = 8;
        }
    } မဟုတ်ပါက {
        အကယ်၍ (base == 0) base = 10;
        အကယ်၍ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ပြန်ပေး 0;
        }
    }
    အကယ်၍ (base == 10) {
        အတွက် (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        အတွက် (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        အကယ်၍ (c-'0'>=10U) goto done;
    } မဟုတ်ပါက အကယ်၍ (!(base & base-1)) {
        ကိန်းပြည့် bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        အတွက် (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        အတွက် (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } မဟုတ်ပါက {
        အတွက် (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        အတွက် (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    အကယ်၍ (val[c]<base) {
        အတွက် (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        အကယ်၍ (lim&1) neg = 0;
    }
done:
    shunget(f);
    အကယ်၍ (y>=lim) {
        အကယ်၍ (!(lim&1) && !neg) {
            errno = ERANGE;
            ပြန်ပေး lim-1;
        } မဟုတ်ပါက အကယ်၍ (y>lim) {
            errno = ERANGE;
            ပြန်ပေး lim;
        }
    }
    ပြန်ပေး (y^neg)-neg;
}

static long long scanexp(FFFILE *f, ကိန်းပြည့် pok)
{
    ကိန်းပြည့် c;
    ကိန်းပြည့် x;
    long long y;
    ကိန်းပြည့် neg = 0;

    c = shgetc(f);
    အကယ်၍ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        အကယ်၍ (c-'0'>=10U && pok) shunget(f);
    }
    အကယ်၍ (c-'0'>=10U) {
        shunget(f);
        ပြန်ပေး LLONG_MIN;
    }
    အတွက် (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    အတွက် (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    အတွက် (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ပြန်ပေး neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, ကိန်းပြည့် c, ကိန်းပြည့် bits, ကိန်းပြည့် emin, ကိန်းပြည့် sign, ကိန်းပြည့် pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    ကိန်းပြည့် i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ကိန်းပြည့် lnz = 0;
    ကိန်းပြည့် gotdig = 0, gotrad = 0;
    ကိန်းပြည့် rp;
    ကိန်းပြည့် e2;
    ကိန်းပြည့် emax = -emin-bits+3;
    ကိန်းပြည့် denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const ကိန်းပြည့် p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    အတွက် (; c=='0'; c = shgetc(f)) gotdig=1;
    အကယ်၍ (c=='.') {
        gotrad = 1;
        အတွက် (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    အတွက် (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        အကယ်၍ (c == '.') {
            အကယ်၍ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } မဟုတ်ပါက အကယ်၍ (k < KMAX-3) {
            dc++;
            အကယ်၍ (c!='0') lnz = dc;
            အကယ်၍ (j) x[k] = x[k]*10 + c-'0';
            မဟုတ်ပါက x[k] = c-'0';
            အကယ်၍ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } မဟုတ်ပါက {
            dc++;
            အကယ်၍ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    အကယ်၍ (!gotrad) lrp=dc;

    အကယ်၍ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        အကယ်၍ (e10 == LLONG_MIN) {
            အကယ်၍ (pok) {
                shunget(f);
            } မဟုတ်ပါက {
                shlim(f, 0);
                ပြန်ပေး 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } မဟုတ်ပါက အကယ်၍ (c>=0) {
        shunget(f);
    }
    အကယ်၍ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ပြန်ပေး 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    အကယ်၍ (!x[0]) ပြန်ပေး sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    အကယ်၍ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ပြန်ပေး sign * (dviguu_na)x[0];
    အကယ်၍ (lrp > -emin/2) {
        errno = ERANGE;
        ပြန်ပေး sign * DBL_MAX * DBL_MAX;
    }
    အကယ်၍ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ပြန်ပေး sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    အကယ်၍ (j) {
        အတွက် (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    အကယ်၍ (lnz<9 && lnz<=rp && rp < 18) {
        ကိန်းပြည့် bitlim;
        အကယ်၍ (rp == 9) ပြန်ပေး sign * (dviguu_na)x[0];
        အကယ်၍ (rp < 9) ပြန်ပေး sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(ကိန်းပြည့်)(rp-9);
        အကယ်၍ (bitlim>30 || x[0]>>bitlim==0)
            ပြန်ပေး sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    အတွက် (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    အကယ်၍ (rp % 9) {
        ကိန်းပြည့် rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ကိန်းပြည့် p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        အတွက် (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            အကယ်၍ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        အကယ်၍ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    နေစဉ် (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        အတွက် (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            အကယ်၍ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } မဟုတ်ပါက {
                carry = 0;
                x[k] = tmp;
            }
            အကယ်၍ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            အကယ်၍ (k==a) bha_nga;
        }
        အကယ်၍ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            အကယ်၍ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    အတွက် (;;) {
        uint32_t carry = 0;
        ကိန်းပြည့် sh = 1;
        အတွက် (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            အကယ်၍ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            အကယ်၍ (x[a+i & MASK] > th[i]) bha_nga;
        }
        အကယ်၍ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        အကယ်၍ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        အတွက် (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            အကယ်၍ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        အကယ်၍ (carry) {
            အကယ်၍ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } မဟုတ်ပါက x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    အတွက် (y=i=0; i<LD_B1B_DIG; i++) {
        အကယ်၍ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    အကယ်၍ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        အကယ်၍ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    အကယ်၍ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    အကယ်၍ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        အကယ်၍ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        မဟုတ်ပါက အကယ်၍ (t > 500000000)
            frac += 0.75*sign;
        မဟုတ်ပါက အကယ်၍ (t == 500000000) {
            အကယ်၍ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            မဟုတ်ပါက
                frac += 0.75*sign;
        }
        အကယ်၍ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    အကယ်၍ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        အကယ်၍ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            အကယ်၍ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        အကယ်၍ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ပြန်ပေး scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, ကိန်းပြည့် bits, ကိန်းပြည့် emin, ကိန်းပြည့် sign, ကိန်းပြည့် pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    ကိန်းပြည့် gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ကိန်းပြည့် d;
    ကိန်းပြည့် c;

    c = shgetc(f);

    /* Skip leading zeros */
    အတွက် (; c=='0'; c = shgetc(f))
        gotdig = 1;

    အကယ်၍ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        အတွက် (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    အတွက် (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        အကယ်၍ (c=='.') {
            အကယ်၍ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } မဟုတ်ပါက {
            gotdig = 1;
            အကယ်၍ (c > '9') d = (c|32)+10-'a';
            မဟုတ်ပါက d = c-'0';
            အကယ်၍ (dc<8) {
                x = x*16 + d;
            } မဟုတ်ပါက အကယ်၍ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } မဟုတ်ပါက အကယ်၍ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    အကယ်၍ (!gotdig) {
        shunget(f);
        အကယ်၍ (pok) {
            shunget(f);
            အကယ်၍ (gotrad) shunget(f);
        } မဟုတ်ပါက {
            shlim(f, 0);
        }
        ပြန်ပေး sign * 0.0;
    }
    အကယ်၍ (!gotrad) rp = dc;
    နေစဉ် (dc<8) x *= 16, dc++;
    အကယ်၍ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        အကယ်၍ (e2 == LLONG_MIN) {
            အကယ်၍ (pok) {
                shunget(f);
            } မဟုတ်ပါက {
                shlim(f, 0);
                ပြန်ပေး 0;
            }
            e2 = 0;
        }
    } မဟုတ်ပါက {
        shunget(f);
    }
    e2 += 4*rp - 32;

    အကယ်၍ (!x) ပြန်ပေး sign * 0.0;
    အကယ်၍ (e2 > -emin) {
        errno = ERANGE;
        ပြန်ပေး sign * DBL_MAX * DBL_MAX;
    }
    အကယ်၍ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ပြန်ပေး sign * DBL_MIN * DBL_MIN;
    }

    နေစဉ် (x < 0x80000000) {
        အကယ်၍ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } မဟုတ်ပါက {
            x += x;
            y += y;
        }
        e2--;
    }

    အကယ်၍ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        အကယ်၍ (bits<0) bits=0;
    }

    အကယ်၍ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    အကယ်၍ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    အကယ်၍ (!y) errno = ERANGE;

    ပြန်ပေး scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, ကိန်းပြည့် prec, ကိန်းပြည့် pok)
{
    ကိန်းပြည့် sign = 1;
    size_t i;
    ကိန်းပြည့် bits;
    ကိန်းပြည့် emin;
    ကိန်းပြည့် c;

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
        ပြန်ပေး 0;
    }

    နေစဉ် (av_isspace((c = shgetc(f))));

    အကယ်၍ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    အတွက် (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        အကယ်၍ (i<7) c = shgetc(f);
    အကယ်၍ (i==3 || i==8 || (i>3 && pok)) {
        အကယ်၍ (i!=8) {
            shunget(f);
            အကယ်၍ (pok) အတွက် (; i>3; i--) shunget(f);
        }
        ပြန်ပေး sign * INFINITY;
    }
    အကယ်၍ (!i) အတွက် (i=0; i<3 && (c|32)=="nan"[i]; i++)
        အကယ်၍ (i<2) c = shgetc(f);
    အကယ်၍ (i==3) {
        အကယ်၍ (shgetc(f) != '(') {
            shunget(f);
            ပြန်ပေး NAN;
        }
        အတွက် (i=1; ; i++) {
            c = shgetc(f);
            အကယ်၍ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            အကယ်၍ (c==')') ပြန်ပေး NAN;
            shunget(f);
            အကယ်၍ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ပြန်ပေး 0;
            }
            နေစဉ် (i--) shunget(f);
            ပြန်ပေး NAN;
        }
    }

    အကယ်၍ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ပြန်ပေး 0;
    }

    အကယ်၍ (c=='0') {
        c = shgetc(f);
        အကယ်၍ ((c|32) == 'x')
            ပြန်ပေး hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ပြန်ပေး decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned ကိန်းပြည့် n)
{
    void *p;
    unsigned ကိန်းပြည့် i;
    va_list ap2;
    va_copy(ap2, ap);
    အတွက် (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ပြန်ပေး p;
}

static void store_int(void *dest, ကိန်းပြည့် size, unsigned long long i)
{
    အကယ်၍ (!dest) ပြန်ပေး;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(ကိန်းပြည့် *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static ကိန်းပြည့် ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    ကိန်းပြည့် width;
    ကိန်းပြည့် size;
    ကိန်းပြည့် base;
    const unsigned var_na *p;
    ကိန်းပြည့် c, t;
    var_na *s;
    void *dest=NULL;
    ကိန်းပြည့် invert;
    ကိန်းပြည့် matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    အတွက် (p=(const unsigned var_na *)fmt; *p; p++) {

        အကယ်၍ (av_isspace(*p)) {
            နေစဉ် (av_isspace(p[1])) p++;
            shlim(f, 0);
            နေစဉ် (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        အကယ်၍ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            အကယ်၍ (*p == '%') {
                p++;
                နေစဉ် (av_isspace((c=shgetc(f))));
            } မဟုတ်ပါက {
                c = shgetc(f);
            }
            အကယ်၍ (c!=*p) {
                shunget(f);
                အကယ်၍ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        အကယ်၍ (*p=='*') {
            dest = 0; p++;
        } မဟုတ်ပါက အကယ်၍ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } မဟုတ်ပါက {
            dest = va_arg(ap, void *);
        }

        အတွက် (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        အကယ်၍ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            အကယ်၍ (*p == 'h') p++, size = SIZE_hh;
            မဟုတ်ပါက size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            အကယ်၍ (*p == 'l') p++, size = SIZE_ll;
            မဟုတ်ပါက size = SIZE_l;
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
        အကယ်၍ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                အကယ်၍ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                နေစဉ် (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        အကယ်၍ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                အကယ်၍ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    အကယ်၍ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } မဟုတ်ပါက {
                    အကယ်၍ (*++p == '^') p++, invert = 1;
                    မဟုတ်ပါက invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    အကယ်၍ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    မဟုတ်ပါက အကယ်၍ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    အတွက် (; *p != ']'; p++) {
                        အကယ်၍ (!*p) goto fmt_fail;
                        အကယ်၍ (*p=='-' && p[1] && p[1] != ']')
                            အတွက် (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                အကယ်၍ ((s = dest)) {
                    နေစဉ် (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } မဟုတ်ပါက {
                    နေစဉ် (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                အကယ်၍ (!shcnt(f)) goto match_fail;
                အကယ်၍ (t == 'c' && shcnt(f) != width) goto match_fail;
                အကယ်၍ (t != 'c') {
                    အကယ်၍ (s) s[i] = 0;
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
                အကယ်၍ (!shcnt(f))
                    goto match_fail;
                အကယ်၍ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                မဟုတ်ပါက
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                အကယ်၍ (!shcnt(f))
                    goto match_fail;
                အကယ်၍ (dest) {
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
        အကယ်၍ (dest) matches++;
    }
    အကယ်၍ (0) {
fmt_fail:
input_fail:
        အကယ်၍ (!matches) matches--;
    }
match_fail:
    ပြန်ပေး matches;
}

static ကိန်းပြည့် ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ပြန်ပေး ff_vfscanf(&f, fmt, ap);
}

ကိန်းပြည့် av_sscanf(const var_na *string, const var_na *format, ...)
{
    ကိန်းပြည့် ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ပြန်ပေး ret;
}
