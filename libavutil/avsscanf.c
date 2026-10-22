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

typedef struct FFFILE {
    size_t buf_size;
    unsigned char *buf;
    unsigned char *rpos, *rend;
    unsigned char *shend;
    ptrdiff_t shlim, shcnt;
    void *cookie;
    size_t (*read)(struct FFFILE *, unsigned char *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

static số_nguyên fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    trả_về 0;
}

static size_t ffstring_read(FFFILE *f, unsigned char *buf, size_t len)
{
    char *src = f->cookie;
    size_t k = len+256;
    char *end = memchr(src, 0, k);

    nếu (end) k = end-src;
    nếu (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    trả_về len;
}

static số_nguyên ffuflow(FFFILE *f)
{
    unsigned char c;
    nếu (!fftoread(f) && f->read(f, &c, 1)==1) trả_về c;
    trả_về EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    nếu (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    không_thì
        f->shend = f->rend;
}

static số_nguyên ffshgetc(FFFILE *f)
{
    số_nguyên c;
    ptrdiff_t cnt = shcnt(f);
    nếu (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        trả_về EOF;
    }
    cnt++;
    nếu (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    không_thì
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    nếu (f->rpos[-1] != c) f->rpos[-1] = c;
    trả_về c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (void)(f)->rpos-- : (void)0)

static const unsigned char table[] = { -1,
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, số_nguyên pok, unsigned long long lim)
{
    const unsigned char *val = table+1;
    số_nguyên c, neg=0;
    unsigned x;
    unsigned long long y;
    nếu (base > 36 || base == 1) {
        errno = EINVAL;
        trả_về 0;
    }
    trong_khi (av_isspace((c=shgetc(f))));
    nếu (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    nếu ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        nếu ((c|32)=='x') {
            c = shgetc(f);
            nếu (val[c]>=16) {
                shunget(f);
                nếu (pok) shunget(f);
                không_thì shlim(f, 0);
                trả_về 0;
            }
            base = 16;
        } không_thì nếu (base == 0) {
            base = 8;
        }
    } không_thì {
        nếu (base == 0) base = 10;
        nếu (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            trả_về 0;
        }
    }
    nếu (base == 10) {
        cho (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        cho (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        nếu (c-'0'>=10U) goto done;
    } không_thì nếu (!(base & base-1)) {
        số_nguyên bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        cho (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        cho (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } không_thì {
        cho (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        cho (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    nếu (val[c]<base) {
        cho (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        nếu (lim&1) neg = 0;
    }
done:
    shunget(f);
    nếu (y>=lim) {
        nếu (!(lim&1) && !neg) {
            errno = ERANGE;
            trả_về lim-1;
        } không_thì nếu (y>lim) {
            errno = ERANGE;
            trả_về lim;
        }
    }
    trả_về (y^neg)-neg;
}

static long long scanexp(FFFILE *f, số_nguyên pok)
{
    số_nguyên c;
    số_nguyên x;
    long long y;
    số_nguyên neg = 0;

    c = shgetc(f);
    nếu (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        nếu (c-'0'>=10U && pok) shunget(f);
    }
    nếu (c-'0'>=10U) {
        shunget(f);
        trả_về LLONG_MIN;
    }
    cho (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    cho (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    cho (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    trả_về neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static double decfloat(FFFILE *f, số_nguyên c, số_nguyên bits, số_nguyên emin, số_nguyên sign, số_nguyên pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    số_nguyên i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    số_nguyên lnz = 0;
    số_nguyên gotdig = 0, gotrad = 0;
    số_nguyên rp;
    số_nguyên e2;
    số_nguyên emax = -emin-bits+3;
    số_nguyên denormal = 0;
    double y;
    double frac=0;
    double bias=0;
    static const số_nguyên p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    cho (; c=='0'; c = shgetc(f)) gotdig=1;
    nếu (c=='.') {
        gotrad = 1;
        cho (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    cho (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        nếu (c == '.') {
            nếu (gotrad) break;
            gotrad = 1;
            lrp = dc;
        } không_thì nếu (k < KMAX-3) {
            dc++;
            nếu (c!='0') lnz = dc;
            nếu (j) x[k] = x[k]*10 + c-'0';
            không_thì x[k] = c-'0';
            nếu (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } không_thì {
            dc++;
            nếu (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    nếu (!gotrad) lrp=dc;

    nếu (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        nếu (e10 == LLONG_MIN) {
            nếu (pok) {
                shunget(f);
            } không_thì {
                shlim(f, 0);
                trả_về 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } không_thì nếu (c>=0) {
        shunget(f);
    }
    nếu (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        trả_về 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    nếu (!x[0]) trả_về sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    nếu (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        trả_về sign * (double)x[0];
    nếu (lrp > -emin/2) {
        errno = ERANGE;
        trả_về sign * DBL_MAX * DBL_MAX;
    }
    nếu (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        trả_về sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    nếu (j) {
        cho (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    nếu (lnz<9 && lnz<=rp && rp < 18) {
        số_nguyên bitlim;
        nếu (rp == 9) trả_về sign * (double)x[0];
        nếu (rp < 9) trả_về sign * (double)x[0] / p10s[8-rp];
        bitlim = bits-3*(số_nguyên)(rp-9);
        nếu (bitlim>30 || x[0]>>bitlim==0)
            trả_về sign * (double)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    cho (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    nếu (rp % 9) {
        số_nguyên rpm9 = rp>=0 ? rp%9 : rp%9+9;
        số_nguyên p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        cho (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            nếu (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        nếu (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    trong_khi (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        cho (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            nếu (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } không_thì {
                carry = 0;
                x[k] = tmp;
            }
            nếu (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            nếu (k==a) break;
        }
        nếu (carry) {
            rp += 9;
            a = (a-1 & MASK);
            nếu (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    cho (;;) {
        uint32_t carry = 0;
        số_nguyên sh = 1;
        cho (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            nếu (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                break;
            }
            nếu (x[a+i & MASK] > th[i]) break;
        }
        nếu (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) break;
        /* FIXME: find a way to compute optimal sh */
        nếu (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        cho (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            nếu (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        nếu (carry) {
            nếu ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } không_thì x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    cho (y=i=0; i<LD_B1B_DIG; i++) {
        nếu ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    nếu (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        nếu (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    nếu (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    nếu ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        nếu (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        không_thì nếu (t > 500000000)
            frac += 0.75*sign;
        không_thì nếu (t == 500000000) {
            nếu ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            không_thì
                frac += 0.75*sign;
        }
        nếu (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    nếu ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        nếu (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            nếu (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        nếu (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    trả_về scalbn(y, e2);
}

static double hexfloat(FFFILE *f, số_nguyên bits, số_nguyên emin, số_nguyên sign, số_nguyên pok)
{
    uint32_t x = 0;
    double y = 0;
    double scale = 1;
    double bias = 0;
    số_nguyên gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    số_nguyên d;
    số_nguyên c;

    c = shgetc(f);

    /* Skip leading zeros */
    cho (; c=='0'; c = shgetc(f))
        gotdig = 1;

    nếu (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        cho (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    cho (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        nếu (c=='.') {
            nếu (gotrad) break;
            rp = dc;
            gotrad = 1;
        } không_thì {
            gotdig = 1;
            nếu (c > '9') d = (c|32)+10-'a';
            không_thì d = c-'0';
            nếu (dc<8) {
                x = x*16 + d;
            } không_thì nếu (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } không_thì nếu (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    nếu (!gotdig) {
        shunget(f);
        nếu (pok) {
            shunget(f);
            nếu (gotrad) shunget(f);
        } không_thì {
            shlim(f, 0);
        }
        trả_về sign * 0.0;
    }
    nếu (!gotrad) rp = dc;
    trong_khi (dc<8) x *= 16, dc++;
    nếu ((c|32)=='p') {
        e2 = scanexp(f, pok);
        nếu (e2 == LLONG_MIN) {
            nếu (pok) {
                shunget(f);
            } không_thì {
                shlim(f, 0);
                trả_về 0;
            }
            e2 = 0;
        }
    } không_thì {
        shunget(f);
    }
    e2 += 4*rp - 32;

    nếu (!x) trả_về sign * 0.0;
    nếu (e2 > -emin) {
        errno = ERANGE;
        trả_về sign * DBL_MAX * DBL_MAX;
    }
    nếu (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        trả_về sign * DBL_MIN * DBL_MIN;
    }

    trong_khi (x < 0x80000000) {
        nếu (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } không_thì {
            x += x;
            y += y;
        }
        e2--;
    }

    nếu (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        nếu (bits<0) bits=0;
    }

    nếu (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    nếu (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(double)x + sign*y;
    y -= bias;

    nếu (!y) errno = ERANGE;

    trả_về scalbn(y, e2);
}

static double fffloatscan(FFFILE *f, số_nguyên prec, số_nguyên pok)
{
    số_nguyên sign = 1;
    size_t i;
    số_nguyên bits;
    số_nguyên emin;
    số_nguyên c;

    switch (prec) {
    case 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        break;
    case 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        break;
    case 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        break;
    default:
        trả_về 0;
    }

    trong_khi (av_isspace((c = shgetc(f))));

    nếu (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    cho (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        nếu (i<7) c = shgetc(f);
    nếu (i==3 || i==8 || (i>3 && pok)) {
        nếu (i!=8) {
            shunget(f);
            nếu (pok) cho (; i>3; i--) shunget(f);
        }
        trả_về sign * INFINITY;
    }
    nếu (!i) cho (i=0; i<3 && (c|32)=="nan"[i]; i++)
        nếu (i<2) c = shgetc(f);
    nếu (i==3) {
        nếu (shgetc(f) != '(') {
            shunget(f);
            trả_về NAN;
        }
        cho (i=1; ; i++) {
            c = shgetc(f);
            nếu (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            nếu (c==')') trả_về NAN;
            shunget(f);
            nếu (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                trả_về 0;
            }
            trong_khi (i--) shunget(f);
            trả_về NAN;
        }
    }

    nếu (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        trả_về 0;
    }

    nếu (c=='0') {
        c = shgetc(f);
        nếu ((c|32) == 'x')
            trả_về hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    trả_về decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned số_nguyên n)
{
    void *p;
    unsigned số_nguyên i;
    va_list ap2;
    va_copy(ap2, ap);
    cho (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    trả_về p;
}

static void store_int(void *dest, số_nguyên size, unsigned long long i)
{
    nếu (!dest) trả_về;
    switch (size) {
    case SIZE_hh:
        *(char *)dest = i;
        break;
    case SIZE_h:
        *(short *)dest = i;
        break;
    case SIZE_def:
        *(số_nguyên *)dest = i;
        break;
    case SIZE_l:
        *(long *)dest = i;
        break;
    case SIZE_ll:
        *(long long *)dest = i;
        break;
    }
}

static số_nguyên ff_vfscanf(FFFILE *f, const char *fmt, va_list ap)
{
    số_nguyên width;
    số_nguyên size;
    số_nguyên base;
    const unsigned char *p;
    số_nguyên c, t;
    char *s;
    void *dest=NULL;
    số_nguyên invert;
    số_nguyên matches=0;
    unsigned long long x;
    double y;
    ptrdiff_t pos = 0;
    unsigned char scanset[257];
    size_t i;

    cho (p=(const unsigned char *)fmt; *p; p++) {

        nếu (av_isspace(*p)) {
            trong_khi (av_isspace(p[1])) p++;
            shlim(f, 0);
            trong_khi (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        nếu (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            nếu (*p == '%') {
                p++;
                trong_khi (av_isspace((c=shgetc(f))));
            } không_thì {
                c = shgetc(f);
            }
            nếu (c!=*p) {
                shunget(f);
                nếu (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        nếu (*p=='*') {
            dest = 0; p++;
        } không_thì nếu (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } không_thì {
            dest = va_arg(ap, void *);
        }

        cho (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        nếu (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        case 'h':
            nếu (*p == 'h') p++, size = SIZE_hh;
            không_thì size = SIZE_h;
            break;
        case 'l':
            nếu (*p == 'l') p++, size = SIZE_ll;
            không_thì size = SIZE_l;
            break;
        case 'j':
            size = SIZE_ll;
            break;
        case 'z':
        case 't':
            size = SIZE_l;
            break;
        case 'L':
            size = SIZE_L;
            break;
        case 'd': case 'i': case 'o': case 'u': case 'x':
        case 'a': case 'e': case 'f': case 'g':
        case 'A': case 'E': case 'F': case 'G': case 'X':
        case 's': case 'c': case '[':
        case 'S': case 'C':
        case 'p': case 'n':
            p--;
            break;
        default:
            goto fmt_fail;
        }

        t = *p;

        /* C or S */
        nếu ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            case 'c':
                nếu (width < 1) width = 1;
                break;
            case '[':
                break;
            case 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                trong_khi (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        nếu (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            case 's':
            case 'c':
            case '[':
                nếu (t == 'c' || t == 's') {
                    memset(scanset, -1, sizeof scanset);
                    scanset[0] = 0;
                    nếu (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } không_thì {
                    nếu (*++p == '^') p++, invert = 1;
                    không_thì invert = 0;
                    memset(scanset, invert, sizeof scanset);
                    scanset[0] = 0;
                    nếu (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    không_thì nếu (*p == ']') p++, scanset[1+']'] = 1-invert;
                    cho (; *p != ']'; p++) {
                        nếu (!*p) goto fmt_fail;
                        nếu (*p=='-' && p[1] && p[1] != ']')
                            cho (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                nếu ((s = dest)) {
                    trong_khi (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } không_thì {
                    trong_khi (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                nếu (!shcnt(f)) goto match_fail;
                nếu (t == 'c' && shcnt(f) != width) goto match_fail;
                nếu (t != 'c') {
                    nếu (s) s[i] = 0;
                }
                break;
            case 'p':
            case 'X':
            case 'x':
                base = 16;
                goto int_common;
            case 'o':
                base = 8;
                goto int_common;
            case 'd':
            case 'u':
                base = 10;
                goto int_common;
            case 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                nếu (!shcnt(f))
                    goto match_fail;
                nếu (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                không_thì
                    store_int(dest, size, x);
                break;
            case 'a': case 'A':
            case 'e': case 'E':
            case 'f': case 'F':
            case 'g': case 'G':
                y = fffloatscan(f, size, 0);
                nếu (!shcnt(f))
                    goto match_fail;
                nếu (dest) {
                    switch (size) {
                    case SIZE_def:
                        *(float *)dest = y;
                        break;
                    case SIZE_l:
                        *(double *)dest = y;
                        break;
                    case SIZE_L:
                        *(double *)dest = y;
                        break;
                    }
                }
                break;
        }

        pos += shcnt(f);
        nếu (dest) matches++;
    }
    nếu (0) {
fmt_fail:
input_fail:
        nếu (!matches) matches--;
    }
match_fail:
    trả_về matches;
}

static số_nguyên ff_vsscanf(const char *s, const char *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    trả_về ff_vfscanf(&f, fmt, ap);
}

số_nguyên av_sscanf(const char *string, const char *format, ...)
{
    số_nguyên ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    trả_về ret;
}
