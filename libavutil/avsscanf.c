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

static 整数 fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    返回 0;
}

static size_t ffstring_read(FFFILE *f, unsigned char *buf, size_t len)
{
    char *src = f->cookie;
    size_t k = len+256;
    char *end = memchr(src, 0, k);

    如果 (end) k = end-src;
    如果 (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    返回 len;
}

static 整数 ffuflow(FFFILE *f)
{
    unsigned char c;
    如果 (!fftoread(f) && f->read(f, &c, 1)==1) 返回 c;
    返回 EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    如果 (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    否则
        f->shend = f->rend;
}

static 整数 ffshgetc(FFFILE *f)
{
    整数 c;
    ptrdiff_t cnt = shcnt(f);
    如果 (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        返回 EOF;
    }
    cnt++;
    如果 (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    否则
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    如果 (f->rpos[-1] != c) f->rpos[-1] = c;
    返回 c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, 整数 pok, unsigned long long lim)
{
    const unsigned char *val = table+1;
    整数 c, neg=0;
    unsigned x;
    unsigned long long y;
    如果 (base > 36 || base == 1) {
        errno = EINVAL;
        返回 0;
    }
    当 (av_isspace((c=shgetc(f))));
    如果 (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    如果 ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        如果 ((c|32)=='x') {
            c = shgetc(f);
            如果 (val[c]>=16) {
                shunget(f);
                如果 (pok) shunget(f);
                否则 shlim(f, 0);
                返回 0;
            }
            base = 16;
        } 否则 如果 (base == 0) {
            base = 8;
        }
    } 否则 {
        如果 (base == 0) base = 10;
        如果 (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            返回 0;
        }
    }
    如果 (base == 10) {
        为 (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        为 (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        如果 (c-'0'>=10U) goto done;
    } 否则 如果 (!(base & base-1)) {
        整数 bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        为 (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        为 (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } 否则 {
        为 (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        为 (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    如果 (val[c]<base) {
        为 (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        如果 (lim&1) neg = 0;
    }
done:
    shunget(f);
    如果 (y>=lim) {
        如果 (!(lim&1) && !neg) {
            errno = ERANGE;
            返回 lim-1;
        } 否则 如果 (y>lim) {
            errno = ERANGE;
            返回 lim;
        }
    }
    返回 (y^neg)-neg;
}

static long long scanexp(FFFILE *f, 整数 pok)
{
    整数 c;
    整数 x;
    long long y;
    整数 neg = 0;

    c = shgetc(f);
    如果 (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        如果 (c-'0'>=10U && pok) shunget(f);
    }
    如果 (c-'0'>=10U) {
        shunget(f);
        返回 LLONG_MIN;
    }
    为 (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    为 (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    为 (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    返回 neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static double decfloat(FFFILE *f, 整数 c, 整数 bits, 整数 emin, 整数 sign, 整数 pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    整数 i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    整数 lnz = 0;
    整数 gotdig = 0, gotrad = 0;
    整数 rp;
    整数 e2;
    整数 emax = -emin-bits+3;
    整数 denormal = 0;
    double y;
    double frac=0;
    double bias=0;
    static const 整数 p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    为 (; c=='0'; c = shgetc(f)) gotdig=1;
    如果 (c=='.') {
        gotrad = 1;
        为 (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    为 (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        如果 (c == '.') {
            如果 (gotrad) break;
            gotrad = 1;
            lrp = dc;
        } 否则 如果 (k < KMAX-3) {
            dc++;
            如果 (c!='0') lnz = dc;
            如果 (j) x[k] = x[k]*10 + c-'0';
            否则 x[k] = c-'0';
            如果 (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } 否则 {
            dc++;
            如果 (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    如果 (!gotrad) lrp=dc;

    如果 (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        如果 (e10 == LLONG_MIN) {
            如果 (pok) {
                shunget(f);
            } 否则 {
                shlim(f, 0);
                返回 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } 否则 如果 (c>=0) {
        shunget(f);
    }
    如果 (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        返回 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    如果 (!x[0]) 返回 sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    如果 (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        返回 sign * (double)x[0];
    如果 (lrp > -emin/2) {
        errno = ERANGE;
        返回 sign * DBL_MAX * DBL_MAX;
    }
    如果 (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        返回 sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    如果 (j) {
        为 (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    如果 (lnz<9 && lnz<=rp && rp < 18) {
        整数 bitlim;
        如果 (rp == 9) 返回 sign * (double)x[0];
        如果 (rp < 9) 返回 sign * (double)x[0] / p10s[8-rp];
        bitlim = bits-3*(整数)(rp-9);
        如果 (bitlim>30 || x[0]>>bitlim==0)
            返回 sign * (double)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    为 (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    如果 (rp % 9) {
        整数 rpm9 = rp>=0 ? rp%9 : rp%9+9;
        整数 p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        为 (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            如果 (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        如果 (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    当 (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        为 (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            如果 (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } 否则 {
                carry = 0;
                x[k] = tmp;
            }
            如果 (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            如果 (k==a) break;
        }
        如果 (carry) {
            rp += 9;
            a = (a-1 & MASK);
            如果 (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    为 (;;) {
        uint32_t carry = 0;
        整数 sh = 1;
        为 (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            如果 (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                break;
            }
            如果 (x[a+i & MASK] > th[i]) break;
        }
        如果 (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) break;
        /* FIXME: find a way to compute optimal sh */
        如果 (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        为 (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            如果 (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        如果 (carry) {
            如果 ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } 否则 x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    为 (y=i=0; i<LD_B1B_DIG; i++) {
        如果 ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    如果 (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        如果 (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    如果 (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    如果 ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        如果 (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        否则 如果 (t > 500000000)
            frac += 0.75*sign;
        否则 如果 (t == 500000000) {
            如果 ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            否则
                frac += 0.75*sign;
        }
        如果 (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    如果 ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        如果 (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            如果 (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        如果 (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    返回 scalbn(y, e2);
}

static double hexfloat(FFFILE *f, 整数 bits, 整数 emin, 整数 sign, 整数 pok)
{
    uint32_t x = 0;
    double y = 0;
    double scale = 1;
    double bias = 0;
    整数 gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    整数 d;
    整数 c;

    c = shgetc(f);

    /* Skip leading zeros */
    为 (; c=='0'; c = shgetc(f))
        gotdig = 1;

    如果 (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        为 (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    为 (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        如果 (c=='.') {
            如果 (gotrad) break;
            rp = dc;
            gotrad = 1;
        } 否则 {
            gotdig = 1;
            如果 (c > '9') d = (c|32)+10-'a';
            否则 d = c-'0';
            如果 (dc<8) {
                x = x*16 + d;
            } 否则 如果 (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } 否则 如果 (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    如果 (!gotdig) {
        shunget(f);
        如果 (pok) {
            shunget(f);
            如果 (gotrad) shunget(f);
        } 否则 {
            shlim(f, 0);
        }
        返回 sign * 0.0;
    }
    如果 (!gotrad) rp = dc;
    当 (dc<8) x *= 16, dc++;
    如果 ((c|32)=='p') {
        e2 = scanexp(f, pok);
        如果 (e2 == LLONG_MIN) {
            如果 (pok) {
                shunget(f);
            } 否则 {
                shlim(f, 0);
                返回 0;
            }
            e2 = 0;
        }
    } 否则 {
        shunget(f);
    }
    e2 += 4*rp - 32;

    如果 (!x) 返回 sign * 0.0;
    如果 (e2 > -emin) {
        errno = ERANGE;
        返回 sign * DBL_MAX * DBL_MAX;
    }
    如果 (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        返回 sign * DBL_MIN * DBL_MIN;
    }

    当 (x < 0x80000000) {
        如果 (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } 否则 {
            x += x;
            y += y;
        }
        e2--;
    }

    如果 (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        如果 (bits<0) bits=0;
    }

    如果 (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    如果 (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(double)x + sign*y;
    y -= bias;

    如果 (!y) errno = ERANGE;

    返回 scalbn(y, e2);
}

static double fffloatscan(FFFILE *f, 整数 prec, 整数 pok)
{
    整数 sign = 1;
    size_t i;
    整数 bits;
    整数 emin;
    整数 c;

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
        返回 0;
    }

    当 (av_isspace((c = shgetc(f))));

    如果 (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    为 (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        如果 (i<7) c = shgetc(f);
    如果 (i==3 || i==8 || (i>3 && pok)) {
        如果 (i!=8) {
            shunget(f);
            如果 (pok) 为 (; i>3; i--) shunget(f);
        }
        返回 sign * INFINITY;
    }
    如果 (!i) 为 (i=0; i<3 && (c|32)=="nan"[i]; i++)
        如果 (i<2) c = shgetc(f);
    如果 (i==3) {
        如果 (shgetc(f) != '(') {
            shunget(f);
            返回 NAN;
        }
        为 (i=1; ; i++) {
            c = shgetc(f);
            如果 (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            如果 (c==')') 返回 NAN;
            shunget(f);
            如果 (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                返回 0;
            }
            当 (i--) shunget(f);
            返回 NAN;
        }
    }

    如果 (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        返回 0;
    }

    如果 (c=='0') {
        c = shgetc(f);
        如果 ((c|32) == 'x')
            返回 hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    返回 decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned 整数 n)
{
    void *p;
    unsigned 整数 i;
    va_list ap2;
    va_copy(ap2, ap);
    为 (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    返回 p;
}

static void store_int(void *dest, 整数 size, unsigned long long i)
{
    如果 (!dest) 返回;
    switch (size) {
    case SIZE_hh:
        *(char *)dest = i;
        break;
    case SIZE_h:
        *(short *)dest = i;
        break;
    case SIZE_def:
        *(整数 *)dest = i;
        break;
    case SIZE_l:
        *(long *)dest = i;
        break;
    case SIZE_ll:
        *(long long *)dest = i;
        break;
    }
}

static 整数 ff_vfscanf(FFFILE *f, const char *fmt, va_list ap)
{
    整数 width;
    整数 size;
    整数 base;
    const unsigned char *p;
    整数 c, t;
    char *s;
    void *dest=NULL;
    整数 invert;
    整数 matches=0;
    unsigned long long x;
    double y;
    ptrdiff_t pos = 0;
    unsigned char scanset[257];
    size_t i;

    为 (p=(const unsigned char *)fmt; *p; p++) {

        如果 (av_isspace(*p)) {
            当 (av_isspace(p[1])) p++;
            shlim(f, 0);
            当 (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        如果 (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            如果 (*p == '%') {
                p++;
                当 (av_isspace((c=shgetc(f))));
            } 否则 {
                c = shgetc(f);
            }
            如果 (c!=*p) {
                shunget(f);
                如果 (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        如果 (*p=='*') {
            dest = 0; p++;
        } 否则 如果 (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } 否则 {
            dest = va_arg(ap, void *);
        }

        为 (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        如果 (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        case 'h':
            如果 (*p == 'h') p++, size = SIZE_hh;
            否则 size = SIZE_h;
            break;
        case 'l':
            如果 (*p == 'l') p++, size = SIZE_ll;
            否则 size = SIZE_l;
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
        如果 ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            case 'c':
                如果 (width < 1) width = 1;
                break;
            case '[':
                break;
            case 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                当 (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        如果 (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            case 's':
            case 'c':
            case '[':
                如果 (t == 'c' || t == 's') {
                    memset(scanset, -1, sizeof scanset);
                    scanset[0] = 0;
                    如果 (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } 否则 {
                    如果 (*++p == '^') p++, invert = 1;
                    否则 invert = 0;
                    memset(scanset, invert, sizeof scanset);
                    scanset[0] = 0;
                    如果 (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    否则 如果 (*p == ']') p++, scanset[1+']'] = 1-invert;
                    为 (; *p != ']'; p++) {
                        如果 (!*p) goto fmt_fail;
                        如果 (*p=='-' && p[1] && p[1] != ']')
                            为 (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                如果 ((s = dest)) {
                    当 (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } 否则 {
                    当 (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                如果 (!shcnt(f)) goto match_fail;
                如果 (t == 'c' && shcnt(f) != width) goto match_fail;
                如果 (t != 'c') {
                    如果 (s) s[i] = 0;
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
                如果 (!shcnt(f))
                    goto match_fail;
                如果 (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                否则
                    store_int(dest, size, x);
                break;
            case 'a': case 'A':
            case 'e': case 'E':
            case 'f': case 'F':
            case 'g': case 'G':
                y = fffloatscan(f, size, 0);
                如果 (!shcnt(f))
                    goto match_fail;
                如果 (dest) {
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
        如果 (dest) matches++;
    }
    如果 (0) {
fmt_fail:
input_fail:
        如果 (!matches) matches--;
    }
match_fail:
    返回 matches;
}

static 整数 ff_vsscanf(const char *s, const char *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    返回 ff_vfscanf(&f, fmt, ap);
}

整数 av_sscanf(const char *string, const char *format, ...)
{
    整数 ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    返回 ret;
}
