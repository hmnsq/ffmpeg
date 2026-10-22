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

static ຈຳນວນເຕັມ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ສົ່ງຄືນ 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    ຖ້າ (end) k = end-src;
    ຖ້າ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ສົ່ງຄືນ len;
}

static ຈຳນວນເຕັມ ffuflow(FFFILE *f)
{
    unsigned var_na c;
    ຖ້າ (!fftoread(f) && f->read(f, &c, 1)==1) ສົ່ງຄືນ c;
    ສົ່ງຄືນ EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ຖ້າ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ບໍ່ດັ່ງນັ້ນ
        f->shend = f->rend;
}

static ຈຳນວນເຕັມ ffshgetc(FFFILE *f)
{
    ຈຳນວນເຕັມ c;
    ptrdiff_t cnt = shcnt(f);
    ຖ້າ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ສົ່ງຄືນ EOF;
    }
    cnt++;
    ຖ້າ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ບໍ່ດັ່ງນັ້ນ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ຖ້າ (f->rpos[-1] != c) f->rpos[-1] = c;
    ສົ່ງຄືນ c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, ຈຳນວນເຕັມ pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    ຈຳນວນເຕັມ c, neg=0;
    unsigned x;
    unsigned long long y;
    ຖ້າ (base > 36 || base == 1) {
        errno = EINVAL;
        ສົ່ງຄືນ 0;
    }
    ໃນຂະນະທີ່ (av_isspace((c=shgetc(f))));
    ຖ້າ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ຖ້າ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ຖ້າ ((c|32)=='x') {
            c = shgetc(f);
            ຖ້າ (val[c]>=16) {
                shunget(f);
                ຖ້າ (pok) shunget(f);
                ບໍ່ດັ່ງນັ້ນ shlim(f, 0);
                ສົ່ງຄືນ 0;
            }
            base = 16;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (base == 0) {
            base = 8;
        }
    } ບໍ່ດັ່ງນັ້ນ {
        ຖ້າ (base == 0) base = 10;
        ຖ້າ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ສົ່ງຄືນ 0;
        }
    }
    ຖ້າ (base == 10) {
        ສຳລັບ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ສຳລັບ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ຖ້າ (c-'0'>=10U) goto done;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (!(base & base-1)) {
        ຈຳນວນເຕັມ bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        ສຳລັບ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ສຳລັບ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ບໍ່ດັ່ງນັ້ນ {
        ສຳລັບ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        ສຳລັບ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ຖ້າ (val[c]<base) {
        ສຳລັບ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ຖ້າ (lim&1) neg = 0;
    }
done:
    shunget(f);
    ຖ້າ (y>=lim) {
        ຖ້າ (!(lim&1) && !neg) {
            errno = ERANGE;
            ສົ່ງຄືນ lim-1;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (y>lim) {
            errno = ERANGE;
            ສົ່ງຄືນ lim;
        }
    }
    ສົ່ງຄືນ (y^neg)-neg;
}

static long long scanexp(FFFILE *f, ຈຳນວນເຕັມ pok)
{
    ຈຳນວນເຕັມ c;
    ຈຳນວນເຕັມ x;
    long long y;
    ຈຳນວນເຕັມ neg = 0;

    c = shgetc(f);
    ຖ້າ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ຖ້າ (c-'0'>=10U && pok) shunget(f);
    }
    ຖ້າ (c-'0'>=10U) {
        shunget(f);
        ສົ່ງຄືນ LLONG_MIN;
    }
    ສຳລັບ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ສຳລັບ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ສຳລັບ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ສົ່ງຄືນ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, ຈຳນວນເຕັມ c, ຈຳນວນເຕັມ bits, ຈຳນວນເຕັມ emin, ຈຳນວນເຕັມ sign, ຈຳນວນເຕັມ pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    ຈຳນວນເຕັມ i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ຈຳນວນເຕັມ lnz = 0;
    ຈຳນວນເຕັມ gotdig = 0, gotrad = 0;
    ຈຳນວນເຕັມ rp;
    ຈຳນວນເຕັມ e2;
    ຈຳນວນເຕັມ emax = -emin-bits+3;
    ຈຳນວນເຕັມ denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const ຈຳນວນເຕັມ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ສຳລັບ (; c=='0'; c = shgetc(f)) gotdig=1;
    ຖ້າ (c=='.') {
        gotrad = 1;
        ສຳລັບ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ສຳລັບ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ຖ້າ (c == '.') {
            ຖ້າ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (k < KMAX-3) {
            dc++;
            ຖ້າ (c!='0') lnz = dc;
            ຖ້າ (j) x[k] = x[k]*10 + c-'0';
            ບໍ່ດັ່ງນັ້ນ x[k] = c-'0';
            ຖ້າ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ບໍ່ດັ່ງນັ້ນ {
            dc++;
            ຖ້າ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ຖ້າ (!gotrad) lrp=dc;

    ຖ້າ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ຖ້າ (e10 == LLONG_MIN) {
            ຖ້າ (pok) {
                shunget(f);
            } ບໍ່ດັ່ງນັ້ນ {
                shlim(f, 0);
                ສົ່ງຄືນ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (c>=0) {
        shunget(f);
    }
    ຖ້າ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ສົ່ງຄືນ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ຖ້າ (!x[0]) ສົ່ງຄືນ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ຖ້າ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ສົ່ງຄືນ sign * (dviguu_na)x[0];
    ຖ້າ (lrp > -emin/2) {
        errno = ERANGE;
        ສົ່ງຄືນ sign * DBL_MAX * DBL_MAX;
    }
    ຖ້າ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ສົ່ງຄືນ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ຖ້າ (j) {
        ສຳລັບ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ຖ້າ (lnz<9 && lnz<=rp && rp < 18) {
        ຈຳນວນເຕັມ bitlim;
        ຖ້າ (rp == 9) ສົ່ງຄືນ sign * (dviguu_na)x[0];
        ຖ້າ (rp < 9) ສົ່ງຄືນ sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(ຈຳນວນເຕັມ)(rp-9);
        ຖ້າ (bitlim>30 || x[0]>>bitlim==0)
            ສົ່ງຄືນ sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ສຳລັບ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ຖ້າ (rp % 9) {
        ຈຳນວນເຕັມ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ຈຳນວນເຕັມ p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        ສຳລັບ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ຖ້າ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ຖ້າ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ໃນຂະນະທີ່ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        ສຳລັບ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ຖ້າ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ບໍ່ດັ່ງນັ້ນ {
                carry = 0;
                x[k] = tmp;
            }
            ຖ້າ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ຖ້າ (k==a) bha_nga;
        }
        ຖ້າ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ຖ້າ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ສຳລັບ (;;) {
        uint32_t carry = 0;
        ຈຳນວນເຕັມ sh = 1;
        ສຳລັບ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ຖ້າ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            ຖ້າ (x[a+i & MASK] > th[i]) bha_nga;
        }
        ຖ້າ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        ຖ້າ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ສຳລັບ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ຖ້າ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ຖ້າ (carry) {
            ຖ້າ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } ບໍ່ດັ່ງນັ້ນ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ສຳລັບ (y=i=0; i<LD_B1B_DIG; i++) {
        ຖ້າ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ຖ້າ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ຖ້າ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ຖ້າ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ຖ້າ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ຖ້າ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        ບໍ່ດັ່ງນັ້ນ ຖ້າ (t > 500000000)
            frac += 0.75*sign;
        ບໍ່ດັ່ງນັ້ນ ຖ້າ (t == 500000000) {
            ຖ້າ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            ບໍ່ດັ່ງນັ້ນ
                frac += 0.75*sign;
        }
        ຖ້າ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ຖ້າ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ຖ້າ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ຖ້າ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ຖ້າ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ສົ່ງຄືນ scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, ຈຳນວນເຕັມ bits, ຈຳນວນເຕັມ emin, ຈຳນວນເຕັມ sign, ຈຳນວນເຕັມ pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    ຈຳນວນເຕັມ gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ຈຳນວນເຕັມ d;
    ຈຳນວນເຕັມ c;

    c = shgetc(f);

    /* Skip leading zeros */
    ສຳລັບ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ຖ້າ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ສຳລັບ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ສຳລັບ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ຖ້າ (c=='.') {
            ຖ້າ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } ບໍ່ດັ່ງນັ້ນ {
            gotdig = 1;
            ຖ້າ (c > '9') d = (c|32)+10-'a';
            ບໍ່ດັ່ງນັ້ນ d = c-'0';
            ຖ້າ (dc<8) {
                x = x*16 + d;
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ຖ້າ (!gotdig) {
        shunget(f);
        ຖ້າ (pok) {
            shunget(f);
            ຖ້າ (gotrad) shunget(f);
        } ບໍ່ດັ່ງນັ້ນ {
            shlim(f, 0);
        }
        ສົ່ງຄືນ sign * 0.0;
    }
    ຖ້າ (!gotrad) rp = dc;
    ໃນຂະນະທີ່ (dc<8) x *= 16, dc++;
    ຖ້າ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ຖ້າ (e2 == LLONG_MIN) {
            ຖ້າ (pok) {
                shunget(f);
            } ບໍ່ດັ່ງນັ້ນ {
                shlim(f, 0);
                ສົ່ງຄືນ 0;
            }
            e2 = 0;
        }
    } ບໍ່ດັ່ງນັ້ນ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ຖ້າ (!x) ສົ່ງຄືນ sign * 0.0;
    ຖ້າ (e2 > -emin) {
        errno = ERANGE;
        ສົ່ງຄືນ sign * DBL_MAX * DBL_MAX;
    }
    ຖ້າ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ສົ່ງຄືນ sign * DBL_MIN * DBL_MIN;
    }

    ໃນຂະນະທີ່ (x < 0x80000000) {
        ຖ້າ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ບໍ່ດັ່ງນັ້ນ {
            x += x;
            y += y;
        }
        e2--;
    }

    ຖ້າ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ຖ້າ (bits<0) bits=0;
    }

    ຖ້າ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ຖ້າ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    ຖ້າ (!y) errno = ERANGE;

    ສົ່ງຄືນ scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, ຈຳນວນເຕັມ prec, ຈຳນວນເຕັມ pok)
{
    ຈຳນວນເຕັມ sign = 1;
    size_t i;
    ຈຳນວນເຕັມ bits;
    ຈຳນວນເຕັມ emin;
    ຈຳນວນເຕັມ c;

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
        ສົ່ງຄືນ 0;
    }

    ໃນຂະນະທີ່ (av_isspace((c = shgetc(f))));

    ຖ້າ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ສຳລັບ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ຖ້າ (i<7) c = shgetc(f);
    ຖ້າ (i==3 || i==8 || (i>3 && pok)) {
        ຖ້າ (i!=8) {
            shunget(f);
            ຖ້າ (pok) ສຳລັບ (; i>3; i--) shunget(f);
        }
        ສົ່ງຄືນ sign * INFINITY;
    }
    ຖ້າ (!i) ສຳລັບ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ຖ້າ (i<2) c = shgetc(f);
    ຖ້າ (i==3) {
        ຖ້າ (shgetc(f) != '(') {
            shunget(f);
            ສົ່ງຄືນ NAN;
        }
        ສຳລັບ (i=1; ; i++) {
            c = shgetc(f);
            ຖ້າ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            ຖ້າ (c==')') ສົ່ງຄືນ NAN;
            shunget(f);
            ຖ້າ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ສົ່ງຄືນ 0;
            }
            ໃນຂະນະທີ່ (i--) shunget(f);
            ສົ່ງຄືນ NAN;
        }
    }

    ຖ້າ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ສົ່ງຄືນ 0;
    }

    ຖ້າ (c=='0') {
        c = shgetc(f);
        ຖ້າ ((c|32) == 'x')
            ສົ່ງຄືນ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ສົ່ງຄືນ decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned ຈຳນວນເຕັມ n)
{
    void *p;
    unsigned ຈຳນວນເຕັມ i;
    va_list ap2;
    va_copy(ap2, ap);
    ສຳລັບ (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ສົ່ງຄືນ p;
}

static void store_int(void *dest, ຈຳນວນເຕັມ size, unsigned long long i)
{
    ຖ້າ (!dest) ສົ່ງຄືນ;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(ຈຳນວນເຕັມ *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static ຈຳນວນເຕັມ ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    ຈຳນວນເຕັມ width;
    ຈຳນວນເຕັມ size;
    ຈຳນວນເຕັມ base;
    const unsigned var_na *p;
    ຈຳນວນເຕັມ c, t;
    var_na *s;
    void *dest=NULL;
    ຈຳນວນເຕັມ invert;
    ຈຳນວນເຕັມ matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    ສຳລັບ (p=(const unsigned var_na *)fmt; *p; p++) {

        ຖ້າ (av_isspace(*p)) {
            ໃນຂະນະທີ່ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ໃນຂະນະທີ່ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        ຖ້າ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ຖ້າ (*p == '%') {
                p++;
                ໃນຂະນະທີ່ (av_isspace((c=shgetc(f))));
            } ບໍ່ດັ່ງນັ້ນ {
                c = shgetc(f);
            }
            ຖ້າ (c!=*p) {
                shunget(f);
                ຖ້າ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        ຖ້າ (*p=='*') {
            dest = 0; p++;
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ບໍ່ດັ່ງນັ້ນ {
            dest = va_arg(ap, void *);
        }

        ສຳລັບ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ຖ້າ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            ຖ້າ (*p == 'h') p++, size = SIZE_hh;
            ບໍ່ດັ່ງນັ້ນ size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            ຖ້າ (*p == 'l') p++, size = SIZE_ll;
            ບໍ່ດັ່ງນັ້ນ size = SIZE_l;
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
        ຖ້າ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                ຖ້າ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                ໃນຂະນະທີ່ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ຖ້າ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                ຖ້າ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    ຖ້າ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ບໍ່ດັ່ງນັ້ນ {
                    ຖ້າ (*++p == '^') p++, invert = 1;
                    ບໍ່ດັ່ງນັ້ນ invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    ຖ້າ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ບໍ່ດັ່ງນັ້ນ ຖ້າ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ສຳລັບ (; *p != ']'; p++) {
                        ຖ້າ (!*p) goto fmt_fail;
                        ຖ້າ (*p=='-' && p[1] && p[1] != ']')
                            ສຳລັບ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ຖ້າ ((s = dest)) {
                    ໃນຂະນະທີ່ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ບໍ່ດັ່ງນັ້ນ {
                    ໃນຂະນະທີ່ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ຖ້າ (!shcnt(f)) goto match_fail;
                ຖ້າ (t == 'c' && shcnt(f) != width) goto match_fail;
                ຖ້າ (t != 'c') {
                    ຖ້າ (s) s[i] = 0;
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
                ຖ້າ (!shcnt(f))
                    goto match_fail;
                ຖ້າ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                ບໍ່ດັ່ງນັ້ນ
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                ຖ້າ (!shcnt(f))
                    goto match_fail;
                ຖ້າ (dest) {
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
        ຖ້າ (dest) matches++;
    }
    ຖ້າ (0) {
fmt_fail:
input_fail:
        ຖ້າ (!matches) matches--;
    }
match_fail:
    ສົ່ງຄືນ matches;
}

static ຈຳນວນເຕັມ ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ສົ່ງຄືນ ff_vfscanf(&f, fmt, ap);
}

ຈຳນວນເຕັມ av_sscanf(const var_na *string, const var_na *format, ...)
{
    ຈຳນວນເຕັມ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ສົ່ງຄືນ ret;
}
