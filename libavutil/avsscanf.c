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

static ཧྲིལ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ཕྱིར 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    གལ་ཏེ (end) k = end-src;
    གལ་ཏེ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ཕྱིར len;
}

static ཧྲིལ ffuflow(FFFILE *f)
{
    unsigned var_na c;
    གལ་ཏེ (!fftoread(f) && f->read(f, &c, 1)==1) ཕྱིར c;
    ཕྱིར EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    གལ་ཏེ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    དེ་མིན
        f->shend = f->rend;
}

static ཧྲིལ ffshgetc(FFFILE *f)
{
    ཧྲིལ c;
    ptrdiff_t cnt = shcnt(f);
    གལ་ཏེ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ཕྱིར EOF;
    }
    cnt++;
    གལ་ཏེ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    དེ་མིན
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    གལ་ཏེ (f->rpos[-1] != c) f->rpos[-1] = c;
    ཕྱིར c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, ཧྲིལ pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    ཧྲིལ c, neg=0;
    unsigned x;
    unsigned long long y;
    གལ་ཏེ (base > 36 || base == 1) {
        errno = EINVAL;
        ཕྱིར 0;
    }
    སྐབས (av_isspace((c=shgetc(f))));
    གལ་ཏེ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    གལ་ཏེ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        གལ་ཏེ ((c|32)=='x') {
            c = shgetc(f);
            གལ་ཏེ (val[c]>=16) {
                shunget(f);
                གལ་ཏེ (pok) shunget(f);
                དེ་མིན shlim(f, 0);
                ཕྱིར 0;
            }
            base = 16;
        } དེ་མིན གལ་ཏེ (base == 0) {
            base = 8;
        }
    } དེ་མིན {
        གལ་ཏེ (base == 0) base = 10;
        གལ་ཏེ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ཕྱིར 0;
        }
    }
    གལ་ཏེ (base == 10) {
        ཆེད་དུ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ཆེད་དུ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        གལ་ཏེ (c-'0'>=10U) goto done;
    } དེ་མིན གལ་ཏེ (!(base & base-1)) {
        ཧྲིལ bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        ཆེད་དུ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ཆེད་དུ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } དེ་མིན {
        ཆེད་དུ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        ཆེད་དུ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    གལ་ཏེ (val[c]<base) {
        ཆེད་དུ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        གལ་ཏེ (lim&1) neg = 0;
    }
done:
    shunget(f);
    གལ་ཏེ (y>=lim) {
        གལ་ཏེ (!(lim&1) && !neg) {
            errno = ERANGE;
            ཕྱིར lim-1;
        } དེ་མིན གལ་ཏེ (y>lim) {
            errno = ERANGE;
            ཕྱིར lim;
        }
    }
    ཕྱིར (y^neg)-neg;
}

static long long scanexp(FFFILE *f, ཧྲིལ pok)
{
    ཧྲིལ c;
    ཧྲིལ x;
    long long y;
    ཧྲིལ neg = 0;

    c = shgetc(f);
    གལ་ཏེ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        གལ་ཏེ (c-'0'>=10U && pok) shunget(f);
    }
    གལ་ཏེ (c-'0'>=10U) {
        shunget(f);
        ཕྱིར LLONG_MIN;
    }
    ཆེད་དུ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ཆེད་དུ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ཆེད་དུ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ཕྱིར neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, ཧྲིལ c, ཧྲིལ bits, ཧྲིལ emin, ཧྲིལ sign, ཧྲིལ pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    ཧྲིལ i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    ཧྲིལ lnz = 0;
    ཧྲིལ gotdig = 0, gotrad = 0;
    ཧྲིལ rp;
    ཧྲིལ e2;
    ཧྲིལ emax = -emin-bits+3;
    ཧྲིལ denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const ཧྲིལ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ཆེད་དུ (; c=='0'; c = shgetc(f)) gotdig=1;
    གལ་ཏེ (c=='.') {
        gotrad = 1;
        ཆེད་དུ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ཆེད་དུ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        གལ་ཏེ (c == '.') {
            གལ་ཏེ (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } དེ་མིན གལ་ཏེ (k < KMAX-3) {
            dc++;
            གལ་ཏེ (c!='0') lnz = dc;
            གལ་ཏེ (j) x[k] = x[k]*10 + c-'0';
            དེ་མིན x[k] = c-'0';
            གལ་ཏེ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } དེ་མིན {
            dc++;
            གལ་ཏེ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    གལ་ཏེ (!gotrad) lrp=dc;

    གལ་ཏེ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        གལ་ཏེ (e10 == LLONG_MIN) {
            གལ་ཏེ (pok) {
                shunget(f);
            } དེ་མིན {
                shlim(f, 0);
                ཕྱིར 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } དེ་མིན གལ་ཏེ (c>=0) {
        shunget(f);
    }
    གལ་ཏེ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ཕྱིར 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    གལ་ཏེ (!x[0]) ཕྱིར sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    གལ་ཏེ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ཕྱིར sign * (dviguu_na)x[0];
    གལ་ཏེ (lrp > -emin/2) {
        errno = ERANGE;
        ཕྱིར sign * DBL_MAX * DBL_MAX;
    }
    གལ་ཏེ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ཕྱིར sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    གལ་ཏེ (j) {
        ཆེད་དུ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    གལ་ཏེ (lnz<9 && lnz<=rp && rp < 18) {
        ཧྲིལ bitlim;
        གལ་ཏེ (rp == 9) ཕྱིར sign * (dviguu_na)x[0];
        གལ་ཏེ (rp < 9) ཕྱིར sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(ཧྲིལ)(rp-9);
        གལ་ཏེ (bitlim>30 || x[0]>>bitlim==0)
            ཕྱིར sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ཆེད་དུ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    གལ་ཏེ (rp % 9) {
        ཧྲིལ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ཧྲིལ p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        ཆེད་དུ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            གལ་ཏེ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        གལ་ཏེ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    སྐབས (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        ཆེད་དུ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            གལ་ཏེ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } དེ་མིན {
                carry = 0;
                x[k] = tmp;
            }
            གལ་ཏེ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            གལ་ཏེ (k==a) bha_nga;
        }
        གལ་ཏེ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            གལ་ཏེ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ཆེད་དུ (;;) {
        uint32_t carry = 0;
        ཧྲིལ sh = 1;
        ཆེད་དུ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            གལ་ཏེ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            གལ་ཏེ (x[a+i & MASK] > th[i]) bha_nga;
        }
        གལ་ཏེ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        གལ་ཏེ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ཆེད་དུ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            གལ་ཏེ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        གལ་ཏེ (carry) {
            གལ་ཏེ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } དེ་མིན x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ཆེད་དུ (y=i=0; i<LD_B1B_DIG; i++) {
        གལ་ཏེ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    གལ་ཏེ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        གལ་ཏེ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    གལ་ཏེ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    གལ་ཏེ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        གལ་ཏེ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        དེ་མིན གལ་ཏེ (t > 500000000)
            frac += 0.75*sign;
        དེ་མིན གལ་ཏེ (t == 500000000) {
            གལ་ཏེ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            དེ་མིན
                frac += 0.75*sign;
        }
        གལ་ཏེ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    གལ་ཏེ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        གལ་ཏེ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            གལ་ཏེ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        གལ་ཏེ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ཕྱིར scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, ཧྲིལ bits, ཧྲིལ emin, ཧྲིལ sign, ཧྲིལ pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    ཧྲིལ gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    ཧྲིལ d;
    ཧྲིལ c;

    c = shgetc(f);

    /* Skip leading zeros */
    ཆེད་དུ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    གལ་ཏེ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ཆེད་དུ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ཆེད་དུ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        གལ་ཏེ (c=='.') {
            གལ་ཏེ (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } དེ་མིན {
            gotdig = 1;
            གལ་ཏེ (c > '9') d = (c|32)+10-'a';
            དེ་མིན d = c-'0';
            གལ་ཏེ (dc<8) {
                x = x*16 + d;
            } དེ་མིན གལ་ཏེ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } དེ་མིན གལ་ཏེ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    གལ་ཏེ (!gotdig) {
        shunget(f);
        གལ་ཏེ (pok) {
            shunget(f);
            གལ་ཏེ (gotrad) shunget(f);
        } དེ་མིན {
            shlim(f, 0);
        }
        ཕྱིར sign * 0.0;
    }
    གལ་ཏེ (!gotrad) rp = dc;
    སྐབས (dc<8) x *= 16, dc++;
    གལ་ཏེ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        གལ་ཏེ (e2 == LLONG_MIN) {
            གལ་ཏེ (pok) {
                shunget(f);
            } དེ་མིན {
                shlim(f, 0);
                ཕྱིར 0;
            }
            e2 = 0;
        }
    } དེ་མིན {
        shunget(f);
    }
    e2 += 4*rp - 32;

    གལ་ཏེ (!x) ཕྱིར sign * 0.0;
    གལ་ཏེ (e2 > -emin) {
        errno = ERANGE;
        ཕྱིར sign * DBL_MAX * DBL_MAX;
    }
    གལ་ཏེ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ཕྱིར sign * DBL_MIN * DBL_MIN;
    }

    སྐབས (x < 0x80000000) {
        གལ་ཏེ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } དེ་མིན {
            x += x;
            y += y;
        }
        e2--;
    }

    གལ་ཏེ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        གལ་ཏེ (bits<0) bits=0;
    }

    གལ་ཏེ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    གལ་ཏེ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    གལ་ཏེ (!y) errno = ERANGE;

    ཕྱིར scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, ཧྲིལ prec, ཧྲིལ pok)
{
    ཧྲིལ sign = 1;
    size_t i;
    ཧྲིལ bits;
    ཧྲིལ emin;
    ཧྲིལ c;

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
        ཕྱིར 0;
    }

    སྐབས (av_isspace((c = shgetc(f))));

    གལ་ཏེ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ཆེད་དུ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        གལ་ཏེ (i<7) c = shgetc(f);
    གལ་ཏེ (i==3 || i==8 || (i>3 && pok)) {
        གལ་ཏེ (i!=8) {
            shunget(f);
            གལ་ཏེ (pok) ཆེད་དུ (; i>3; i--) shunget(f);
        }
        ཕྱིར sign * INFINITY;
    }
    གལ་ཏེ (!i) ཆེད་དུ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        གལ་ཏེ (i<2) c = shgetc(f);
    གལ་ཏེ (i==3) {
        གལ་ཏེ (shgetc(f) != '(') {
            shunget(f);
            ཕྱིར NAN;
        }
        ཆེད་དུ (i=1; ; i++) {
            c = shgetc(f);
            གལ་ཏེ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            གལ་ཏེ (c==')') ཕྱིར NAN;
            shunget(f);
            གལ་ཏེ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ཕྱིར 0;
            }
            སྐབས (i--) shunget(f);
            ཕྱིར NAN;
        }
    }

    གལ་ཏེ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ཕྱིར 0;
    }

    གལ་ཏེ (c=='0') {
        c = shgetc(f);
        གལ་ཏེ ((c|32) == 'x')
            ཕྱིར hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ཕྱིར decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned ཧྲིལ n)
{
    void *p;
    unsigned ཧྲིལ i;
    va_list ap2;
    va_copy(ap2, ap);
    ཆེད་དུ (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ཕྱིར p;
}

static void store_int(void *dest, ཧྲིལ size, unsigned long long i)
{
    གལ་ཏེ (!dest) ཕྱིར;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(ཧྲིལ *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static ཧྲིལ ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    ཧྲིལ width;
    ཧྲིལ size;
    ཧྲིལ base;
    const unsigned var_na *p;
    ཧྲིལ c, t;
    var_na *s;
    void *dest=NULL;
    ཧྲིལ invert;
    ཧྲིལ matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    ཆེད་དུ (p=(const unsigned var_na *)fmt; *p; p++) {

        གལ་ཏེ (av_isspace(*p)) {
            སྐབས (av_isspace(p[1])) p++;
            shlim(f, 0);
            སྐབས (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        གལ་ཏེ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            གལ་ཏེ (*p == '%') {
                p++;
                སྐབས (av_isspace((c=shgetc(f))));
            } དེ་མིན {
                c = shgetc(f);
            }
            གལ་ཏེ (c!=*p) {
                shunget(f);
                གལ་ཏེ (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        གལ་ཏེ (*p=='*') {
            dest = 0; p++;
        } དེ་མིན གལ་ཏེ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } དེ་མིན {
            dest = va_arg(ap, void *);
        }

        ཆེད་དུ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        གལ་ཏེ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            གལ་ཏེ (*p == 'h') p++, size = SIZE_hh;
            དེ་མིན size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            གལ་ཏེ (*p == 'l') p++, size = SIZE_ll;
            དེ་མིན size = SIZE_l;
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
        གལ་ཏེ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                གལ་ཏེ (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                སྐབས (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        གལ་ཏེ (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                གལ་ཏེ (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    གལ་ཏེ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } དེ་མིན {
                    གལ་ཏེ (*++p == '^') p++, invert = 1;
                    དེ་མིན invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    གལ་ཏེ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    དེ་མིན གལ་ཏེ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ཆེད་དུ (; *p != ']'; p++) {
                        གལ་ཏེ (!*p) goto fmt_fail;
                        གལ་ཏེ (*p=='-' && p[1] && p[1] != ']')
                            ཆེད་དུ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                གལ་ཏེ ((s = dest)) {
                    སྐབས (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } དེ་མིན {
                    སྐབས (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                གལ་ཏེ (!shcnt(f)) goto match_fail;
                གལ་ཏེ (t == 'c' && shcnt(f) != width) goto match_fail;
                གལ་ཏེ (t != 'c') {
                    གལ་ཏེ (s) s[i] = 0;
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
                གལ་ཏེ (!shcnt(f))
                    goto match_fail;
                གལ་ཏེ (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                དེ་མིན
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                གལ་ཏེ (!shcnt(f))
                    goto match_fail;
                གལ་ཏེ (dest) {
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
        གལ་ཏེ (dest) matches++;
    }
    གལ་ཏེ (0) {
fmt_fail:
input_fail:
        གལ་ཏེ (!matches) matches--;
    }
match_fail:
    ཕྱིར matches;
}

static ཧྲིལ ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ཕྱིར ff_vfscanf(&f, fmt, ap);
}

ཧྲིལ av_sscanf(const var_na *string, const var_na *format, ...)
{
    ཧྲིལ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ཕྱིར ret;
}
