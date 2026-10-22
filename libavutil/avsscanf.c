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

static 정수 fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    반환 0;
}

static size_t ffstring_read(FFFILE *f, unsigned char *buf, size_t len)
{
    char *src = f->cookie;
    size_t k = len+256;
    char *end = memchr(src, 0, k);

    만약 (end) k = end-src;
    만약 (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    반환 len;
}

static 정수 ffuflow(FFFILE *f)
{
    unsigned char c;
    만약 (!fftoread(f) && f->read(f, &c, 1)==1) 반환 c;
    반환 EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    만약 (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    아니면
        f->shend = f->rend;
}

static 정수 ffshgetc(FFFILE *f)
{
    정수 c;
    ptrdiff_t cnt = shcnt(f);
    만약 (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        반환 EOF;
    }
    cnt++;
    만약 (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    아니면
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    만약 (f->rpos[-1] != c) f->rpos[-1] = c;
    반환 c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, 정수 pok, unsigned long long lim)
{
    const unsigned char *val = table+1;
    정수 c, neg=0;
    unsigned x;
    unsigned long long y;
    만약 (base > 36 || base == 1) {
        errno = EINVAL;
        반환 0;
    }
    동안 (av_isspace((c=shgetc(f))));
    만약 (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    만약 ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        만약 ((c|32)=='x') {
            c = shgetc(f);
            만약 (val[c]>=16) {
                shunget(f);
                만약 (pok) shunget(f);
                아니면 shlim(f, 0);
                반환 0;
            }
            base = 16;
        } 아니면 만약 (base == 0) {
            base = 8;
        }
    } 아니면 {
        만약 (base == 0) base = 10;
        만약 (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            반환 0;
        }
    }
    만약 (base == 10) {
        위해 (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        위해 (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        만약 (c-'0'>=10U) goto done;
    } 아니면 만약 (!(base & base-1)) {
        정수 bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        위해 (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        위해 (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } 아니면 {
        위해 (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        위해 (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    만약 (val[c]<base) {
        위해 (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        만약 (lim&1) neg = 0;
    }
done:
    shunget(f);
    만약 (y>=lim) {
        만약 (!(lim&1) && !neg) {
            errno = ERANGE;
            반환 lim-1;
        } 아니면 만약 (y>lim) {
            errno = ERANGE;
            반환 lim;
        }
    }
    반환 (y^neg)-neg;
}

static long long scanexp(FFFILE *f, 정수 pok)
{
    정수 c;
    정수 x;
    long long y;
    정수 neg = 0;

    c = shgetc(f);
    만약 (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        만약 (c-'0'>=10U && pok) shunget(f);
    }
    만약 (c-'0'>=10U) {
        shunget(f);
        반환 LLONG_MIN;
    }
    위해 (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    위해 (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    위해 (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    반환 neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static double decfloat(FFFILE *f, 정수 c, 정수 bits, 정수 emin, 정수 sign, 정수 pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    정수 i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    정수 lnz = 0;
    정수 gotdig = 0, gotrad = 0;
    정수 rp;
    정수 e2;
    정수 emax = -emin-bits+3;
    정수 denormal = 0;
    double y;
    double frac=0;
    double bias=0;
    static const 정수 p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    위해 (; c=='0'; c = shgetc(f)) gotdig=1;
    만약 (c=='.') {
        gotrad = 1;
        위해 (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    위해 (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        만약 (c == '.') {
            만약 (gotrad) break;
            gotrad = 1;
            lrp = dc;
        } 아니면 만약 (k < KMAX-3) {
            dc++;
            만약 (c!='0') lnz = dc;
            만약 (j) x[k] = x[k]*10 + c-'0';
            아니면 x[k] = c-'0';
            만약 (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } 아니면 {
            dc++;
            만약 (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    만약 (!gotrad) lrp=dc;

    만약 (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        만약 (e10 == LLONG_MIN) {
            만약 (pok) {
                shunget(f);
            } 아니면 {
                shlim(f, 0);
                반환 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } 아니면 만약 (c>=0) {
        shunget(f);
    }
    만약 (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        반환 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    만약 (!x[0]) 반환 sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    만약 (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        반환 sign * (double)x[0];
    만약 (lrp > -emin/2) {
        errno = ERANGE;
        반환 sign * DBL_MAX * DBL_MAX;
    }
    만약 (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        반환 sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    만약 (j) {
        위해 (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    만약 (lnz<9 && lnz<=rp && rp < 18) {
        정수 bitlim;
        만약 (rp == 9) 반환 sign * (double)x[0];
        만약 (rp < 9) 반환 sign * (double)x[0] / p10s[8-rp];
        bitlim = bits-3*(정수)(rp-9);
        만약 (bitlim>30 || x[0]>>bitlim==0)
            반환 sign * (double)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    위해 (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    만약 (rp % 9) {
        정수 rpm9 = rp>=0 ? rp%9 : rp%9+9;
        정수 p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        위해 (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            만약 (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        만약 (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    동안 (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        위해 (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            만약 (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } 아니면 {
                carry = 0;
                x[k] = tmp;
            }
            만약 (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            만약 (k==a) break;
        }
        만약 (carry) {
            rp += 9;
            a = (a-1 & MASK);
            만약 (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    위해 (;;) {
        uint32_t carry = 0;
        정수 sh = 1;
        위해 (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            만약 (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                break;
            }
            만약 (x[a+i & MASK] > th[i]) break;
        }
        만약 (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) break;
        /* FIXME: find a way to compute optimal sh */
        만약 (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        위해 (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            만약 (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        만약 (carry) {
            만약 ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } 아니면 x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    위해 (y=i=0; i<LD_B1B_DIG; i++) {
        만약 ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    만약 (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        만약 (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    만약 (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    만약 ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        만약 (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        아니면 만약 (t > 500000000)
            frac += 0.75*sign;
        아니면 만약 (t == 500000000) {
            만약 ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            아니면
                frac += 0.75*sign;
        }
        만약 (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    만약 ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        만약 (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            만약 (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        만약 (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    반환 scalbn(y, e2);
}

static double hexfloat(FFFILE *f, 정수 bits, 정수 emin, 정수 sign, 정수 pok)
{
    uint32_t x = 0;
    double y = 0;
    double scale = 1;
    double bias = 0;
    정수 gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    정수 d;
    정수 c;

    c = shgetc(f);

    /* Skip leading zeros */
    위해 (; c=='0'; c = shgetc(f))
        gotdig = 1;

    만약 (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        위해 (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    위해 (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        만약 (c=='.') {
            만약 (gotrad) break;
            rp = dc;
            gotrad = 1;
        } 아니면 {
            gotdig = 1;
            만약 (c > '9') d = (c|32)+10-'a';
            아니면 d = c-'0';
            만약 (dc<8) {
                x = x*16 + d;
            } 아니면 만약 (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } 아니면 만약 (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    만약 (!gotdig) {
        shunget(f);
        만약 (pok) {
            shunget(f);
            만약 (gotrad) shunget(f);
        } 아니면 {
            shlim(f, 0);
        }
        반환 sign * 0.0;
    }
    만약 (!gotrad) rp = dc;
    동안 (dc<8) x *= 16, dc++;
    만약 ((c|32)=='p') {
        e2 = scanexp(f, pok);
        만약 (e2 == LLONG_MIN) {
            만약 (pok) {
                shunget(f);
            } 아니면 {
                shlim(f, 0);
                반환 0;
            }
            e2 = 0;
        }
    } 아니면 {
        shunget(f);
    }
    e2 += 4*rp - 32;

    만약 (!x) 반환 sign * 0.0;
    만약 (e2 > -emin) {
        errno = ERANGE;
        반환 sign * DBL_MAX * DBL_MAX;
    }
    만약 (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        반환 sign * DBL_MIN * DBL_MIN;
    }

    동안 (x < 0x80000000) {
        만약 (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } 아니면 {
            x += x;
            y += y;
        }
        e2--;
    }

    만약 (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        만약 (bits<0) bits=0;
    }

    만약 (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    만약 (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(double)x + sign*y;
    y -= bias;

    만약 (!y) errno = ERANGE;

    반환 scalbn(y, e2);
}

static double fffloatscan(FFFILE *f, 정수 prec, 정수 pok)
{
    정수 sign = 1;
    size_t i;
    정수 bits;
    정수 emin;
    정수 c;

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
        반환 0;
    }

    동안 (av_isspace((c = shgetc(f))));

    만약 (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    위해 (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        만약 (i<7) c = shgetc(f);
    만약 (i==3 || i==8 || (i>3 && pok)) {
        만약 (i!=8) {
            shunget(f);
            만약 (pok) 위해 (; i>3; i--) shunget(f);
        }
        반환 sign * INFINITY;
    }
    만약 (!i) 위해 (i=0; i<3 && (c|32)=="nan"[i]; i++)
        만약 (i<2) c = shgetc(f);
    만약 (i==3) {
        만약 (shgetc(f) != '(') {
            shunget(f);
            반환 NAN;
        }
        위해 (i=1; ; i++) {
            c = shgetc(f);
            만약 (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            만약 (c==')') 반환 NAN;
            shunget(f);
            만약 (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                반환 0;
            }
            동안 (i--) shunget(f);
            반환 NAN;
        }
    }

    만약 (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        반환 0;
    }

    만약 (c=='0') {
        c = shgetc(f);
        만약 ((c|32) == 'x')
            반환 hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    반환 decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned 정수 n)
{
    void *p;
    unsigned 정수 i;
    va_list ap2;
    va_copy(ap2, ap);
    위해 (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    반환 p;
}

static void store_int(void *dest, 정수 size, unsigned long long i)
{
    만약 (!dest) 반환;
    switch (size) {
    case SIZE_hh:
        *(char *)dest = i;
        break;
    case SIZE_h:
        *(short *)dest = i;
        break;
    case SIZE_def:
        *(정수 *)dest = i;
        break;
    case SIZE_l:
        *(long *)dest = i;
        break;
    case SIZE_ll:
        *(long long *)dest = i;
        break;
    }
}

static 정수 ff_vfscanf(FFFILE *f, const char *fmt, va_list ap)
{
    정수 width;
    정수 size;
    정수 base;
    const unsigned char *p;
    정수 c, t;
    char *s;
    void *dest=NULL;
    정수 invert;
    정수 matches=0;
    unsigned long long x;
    double y;
    ptrdiff_t pos = 0;
    unsigned char scanset[257];
    size_t i;

    위해 (p=(const unsigned char *)fmt; *p; p++) {

        만약 (av_isspace(*p)) {
            동안 (av_isspace(p[1])) p++;
            shlim(f, 0);
            동안 (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        만약 (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            만약 (*p == '%') {
                p++;
                동안 (av_isspace((c=shgetc(f))));
            } 아니면 {
                c = shgetc(f);
            }
            만약 (c!=*p) {
                shunget(f);
                만약 (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        만약 (*p=='*') {
            dest = 0; p++;
        } 아니면 만약 (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } 아니면 {
            dest = va_arg(ap, void *);
        }

        위해 (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        만약 (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        case 'h':
            만약 (*p == 'h') p++, size = SIZE_hh;
            아니면 size = SIZE_h;
            break;
        case 'l':
            만약 (*p == 'l') p++, size = SIZE_ll;
            아니면 size = SIZE_l;
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
        만약 ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            case 'c':
                만약 (width < 1) width = 1;
                break;
            case '[':
                break;
            case 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                동안 (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        만약 (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            case 's':
            case 'c':
            case '[':
                만약 (t == 'c' || t == 's') {
                    memset(scanset, -1, sizeof scanset);
                    scanset[0] = 0;
                    만약 (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } 아니면 {
                    만약 (*++p == '^') p++, invert = 1;
                    아니면 invert = 0;
                    memset(scanset, invert, sizeof scanset);
                    scanset[0] = 0;
                    만약 (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    아니면 만약 (*p == ']') p++, scanset[1+']'] = 1-invert;
                    위해 (; *p != ']'; p++) {
                        만약 (!*p) goto fmt_fail;
                        만약 (*p=='-' && p[1] && p[1] != ']')
                            위해 (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                만약 ((s = dest)) {
                    동안 (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } 아니면 {
                    동안 (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                만약 (!shcnt(f)) goto match_fail;
                만약 (t == 'c' && shcnt(f) != width) goto match_fail;
                만약 (t != 'c') {
                    만약 (s) s[i] = 0;
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
                만약 (!shcnt(f))
                    goto match_fail;
                만약 (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                아니면
                    store_int(dest, size, x);
                break;
            case 'a': case 'A':
            case 'e': case 'E':
            case 'f': case 'F':
            case 'g': case 'G':
                y = fffloatscan(f, size, 0);
                만약 (!shcnt(f))
                    goto match_fail;
                만약 (dest) {
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
        만약 (dest) matches++;
    }
    만약 (0) {
fmt_fail:
input_fail:
        만약 (!matches) matches--;
    }
match_fail:
    반환 matches;
}

static 정수 ff_vsscanf(const char *s, const char *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    반환 ff_vfscanf(&f, fmt, ap);
}

정수 av_sscanf(const char *string, const char *format, ...)
{
    정수 ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    반환 ret;
}
