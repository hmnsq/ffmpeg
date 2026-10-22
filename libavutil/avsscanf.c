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

static целое fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    вернуть 0;
}

static size_t ffstring_read(FFFILE *f, unsigned char *buf, size_t len)
{
    char *src = f->cookie;
    size_t k = len+256;
    char *end = memchr(src, 0, k);

    если (end) k = end-src;
    если (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    вернуть len;
}

static целое ffuflow(FFFILE *f)
{
    unsigned char c;
    если (!fftoread(f) && f->read(f, &c, 1)==1) вернуть c;
    вернуть EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    если (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    иначе
        f->shend = f->rend;
}

static целое ffshgetc(FFFILE *f)
{
    целое c;
    ptrdiff_t cnt = shcnt(f);
    если (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        вернуть EOF;
    }
    cnt++;
    если (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    иначе
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    если (f->rpos[-1] != c) f->rpos[-1] = c;
    вернуть c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, целое pok, unsigned long long lim)
{
    const unsigned char *val = table+1;
    целое c, neg=0;
    unsigned x;
    unsigned long long y;
    если (base > 36 || base == 1) {
        errno = EINVAL;
        вернуть 0;
    }
    пока (av_isspace((c=shgetc(f))));
    если (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    если ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        если ((c|32)=='x') {
            c = shgetc(f);
            если (val[c]>=16) {
                shunget(f);
                если (pok) shunget(f);
                иначе shlim(f, 0);
                вернуть 0;
            }
            base = 16;
        } иначе если (base == 0) {
            base = 8;
        }
    } иначе {
        если (base == 0) base = 10;
        если (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            вернуть 0;
        }
    }
    если (base == 10) {
        для (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        для (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        если (c-'0'>=10U) goto done;
    } иначе если (!(base & base-1)) {
        целое bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        для (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        для (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } иначе {
        для (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        для (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    если (val[c]<base) {
        для (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        если (lim&1) neg = 0;
    }
done:
    shunget(f);
    если (y>=lim) {
        если (!(lim&1) && !neg) {
            errno = ERANGE;
            вернуть lim-1;
        } иначе если (y>lim) {
            errno = ERANGE;
            вернуть lim;
        }
    }
    вернуть (y^neg)-neg;
}

static long long scanexp(FFFILE *f, целое pok)
{
    целое c;
    целое x;
    long long y;
    целое neg = 0;

    c = shgetc(f);
    если (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        если (c-'0'>=10U && pok) shunget(f);
    }
    если (c-'0'>=10U) {
        shunget(f);
        вернуть LLONG_MIN;
    }
    для (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    для (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    для (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    вернуть neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static double decfloat(FFFILE *f, целое c, целое bits, целое emin, целое sign, целое pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    целое i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    целое lnz = 0;
    целое gotdig = 0, gotrad = 0;
    целое rp;
    целое e2;
    целое emax = -emin-bits+3;
    целое denormal = 0;
    double y;
    double frac=0;
    double bias=0;
    static const целое p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    для (; c=='0'; c = shgetc(f)) gotdig=1;
    если (c=='.') {
        gotrad = 1;
        для (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    для (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        если (c == '.') {
            если (gotrad) break;
            gotrad = 1;
            lrp = dc;
        } иначе если (k < KMAX-3) {
            dc++;
            если (c!='0') lnz = dc;
            если (j) x[k] = x[k]*10 + c-'0';
            иначе x[k] = c-'0';
            если (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } иначе {
            dc++;
            если (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    если (!gotrad) lrp=dc;

    если (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        если (e10 == LLONG_MIN) {
            если (pok) {
                shunget(f);
            } иначе {
                shlim(f, 0);
                вернуть 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } иначе если (c>=0) {
        shunget(f);
    }
    если (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        вернуть 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    если (!x[0]) вернуть sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    если (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        вернуть sign * (double)x[0];
    если (lrp > -emin/2) {
        errno = ERANGE;
        вернуть sign * DBL_MAX * DBL_MAX;
    }
    если (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        вернуть sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    если (j) {
        для (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    если (lnz<9 && lnz<=rp && rp < 18) {
        целое bitlim;
        если (rp == 9) вернуть sign * (double)x[0];
        если (rp < 9) вернуть sign * (double)x[0] / p10s[8-rp];
        bitlim = bits-3*(целое)(rp-9);
        если (bitlim>30 || x[0]>>bitlim==0)
            вернуть sign * (double)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    для (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    если (rp % 9) {
        целое rpm9 = rp>=0 ? rp%9 : rp%9+9;
        целое p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        для (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            если (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        если (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    пока (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        для (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            если (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } иначе {
                carry = 0;
                x[k] = tmp;
            }
            если (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            если (k==a) break;
        }
        если (carry) {
            rp += 9;
            a = (a-1 & MASK);
            если (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    для (;;) {
        uint32_t carry = 0;
        целое sh = 1;
        для (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            если (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                break;
            }
            если (x[a+i & MASK] > th[i]) break;
        }
        если (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) break;
        /* FIXME: find a way to compute optimal sh */
        если (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        для (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            если (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        если (carry) {
            если ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } иначе x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    для (y=i=0; i<LD_B1B_DIG; i++) {
        если ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    если (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        если (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    если (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    если ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        если (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        иначе если (t > 500000000)
            frac += 0.75*sign;
        иначе если (t == 500000000) {
            если ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            иначе
                frac += 0.75*sign;
        }
        если (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    если ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        если (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            если (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        если (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    вернуть scalbn(y, e2);
}

static double hexfloat(FFFILE *f, целое bits, целое emin, целое sign, целое pok)
{
    uint32_t x = 0;
    double y = 0;
    double scale = 1;
    double bias = 0;
    целое gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    целое d;
    целое c;

    c = shgetc(f);

    /* Skip leading zeros */
    для (; c=='0'; c = shgetc(f))
        gotdig = 1;

    если (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        для (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    для (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        если (c=='.') {
            если (gotrad) break;
            rp = dc;
            gotrad = 1;
        } иначе {
            gotdig = 1;
            если (c > '9') d = (c|32)+10-'a';
            иначе d = c-'0';
            если (dc<8) {
                x = x*16 + d;
            } иначе если (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } иначе если (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    если (!gotdig) {
        shunget(f);
        если (pok) {
            shunget(f);
            если (gotrad) shunget(f);
        } иначе {
            shlim(f, 0);
        }
        вернуть sign * 0.0;
    }
    если (!gotrad) rp = dc;
    пока (dc<8) x *= 16, dc++;
    если ((c|32)=='p') {
        e2 = scanexp(f, pok);
        если (e2 == LLONG_MIN) {
            если (pok) {
                shunget(f);
            } иначе {
                shlim(f, 0);
                вернуть 0;
            }
            e2 = 0;
        }
    } иначе {
        shunget(f);
    }
    e2 += 4*rp - 32;

    если (!x) вернуть sign * 0.0;
    если (e2 > -emin) {
        errno = ERANGE;
        вернуть sign * DBL_MAX * DBL_MAX;
    }
    если (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        вернуть sign * DBL_MIN * DBL_MIN;
    }

    пока (x < 0x80000000) {
        если (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } иначе {
            x += x;
            y += y;
        }
        e2--;
    }

    если (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        если (bits<0) bits=0;
    }

    если (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    если (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(double)x + sign*y;
    y -= bias;

    если (!y) errno = ERANGE;

    вернуть scalbn(y, e2);
}

static double fffloatscan(FFFILE *f, целое prec, целое pok)
{
    целое sign = 1;
    size_t i;
    целое bits;
    целое emin;
    целое c;

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
        вернуть 0;
    }

    пока (av_isspace((c = shgetc(f))));

    если (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    для (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        если (i<7) c = shgetc(f);
    если (i==3 || i==8 || (i>3 && pok)) {
        если (i!=8) {
            shunget(f);
            если (pok) для (; i>3; i--) shunget(f);
        }
        вернуть sign * INFINITY;
    }
    если (!i) для (i=0; i<3 && (c|32)=="nan"[i]; i++)
        если (i<2) c = shgetc(f);
    если (i==3) {
        если (shgetc(f) != '(') {
            shunget(f);
            вернуть NAN;
        }
        для (i=1; ; i++) {
            c = shgetc(f);
            если (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            если (c==')') вернуть NAN;
            shunget(f);
            если (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                вернуть 0;
            }
            пока (i--) shunget(f);
            вернуть NAN;
        }
    }

    если (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        вернуть 0;
    }

    если (c=='0') {
        c = shgetc(f);
        если ((c|32) == 'x')
            вернуть hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    вернуть decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned целое n)
{
    void *p;
    unsigned целое i;
    va_list ap2;
    va_copy(ap2, ap);
    для (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    вернуть p;
}

static void store_int(void *dest, целое size, unsigned long long i)
{
    если (!dest) вернуть;
    switch (size) {
    case SIZE_hh:
        *(char *)dest = i;
        break;
    case SIZE_h:
        *(short *)dest = i;
        break;
    case SIZE_def:
        *(целое *)dest = i;
        break;
    case SIZE_l:
        *(long *)dest = i;
        break;
    case SIZE_ll:
        *(long long *)dest = i;
        break;
    }
}

static целое ff_vfscanf(FFFILE *f, const char *fmt, va_list ap)
{
    целое width;
    целое size;
    целое base;
    const unsigned char *p;
    целое c, t;
    char *s;
    void *dest=NULL;
    целое invert;
    целое matches=0;
    unsigned long long x;
    double y;
    ptrdiff_t pos = 0;
    unsigned char scanset[257];
    size_t i;

    для (p=(const unsigned char *)fmt; *p; p++) {

        если (av_isspace(*p)) {
            пока (av_isspace(p[1])) p++;
            shlim(f, 0);
            пока (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        если (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            если (*p == '%') {
                p++;
                пока (av_isspace((c=shgetc(f))));
            } иначе {
                c = shgetc(f);
            }
            если (c!=*p) {
                shunget(f);
                если (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        если (*p=='*') {
            dest = 0; p++;
        } иначе если (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } иначе {
            dest = va_arg(ap, void *);
        }

        для (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        если (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        case 'h':
            если (*p == 'h') p++, size = SIZE_hh;
            иначе size = SIZE_h;
            break;
        case 'l':
            если (*p == 'l') p++, size = SIZE_ll;
            иначе size = SIZE_l;
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
        если ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            case 'c':
                если (width < 1) width = 1;
                break;
            case '[':
                break;
            case 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                пока (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        если (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            case 's':
            case 'c':
            case '[':
                если (t == 'c' || t == 's') {
                    memset(scanset, -1, sizeof scanset);
                    scanset[0] = 0;
                    если (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } иначе {
                    если (*++p == '^') p++, invert = 1;
                    иначе invert = 0;
                    memset(scanset, invert, sizeof scanset);
                    scanset[0] = 0;
                    если (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    иначе если (*p == ']') p++, scanset[1+']'] = 1-invert;
                    для (; *p != ']'; p++) {
                        если (!*p) goto fmt_fail;
                        если (*p=='-' && p[1] && p[1] != ']')
                            для (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                если ((s = dest)) {
                    пока (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } иначе {
                    пока (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                если (!shcnt(f)) goto match_fail;
                если (t == 'c' && shcnt(f) != width) goto match_fail;
                если (t != 'c') {
                    если (s) s[i] = 0;
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
                если (!shcnt(f))
                    goto match_fail;
                если (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                иначе
                    store_int(dest, size, x);
                break;
            case 'a': case 'A':
            case 'e': case 'E':
            case 'f': case 'F':
            case 'g': case 'G':
                y = fffloatscan(f, size, 0);
                если (!shcnt(f))
                    goto match_fail;
                если (dest) {
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
        если (dest) matches++;
    }
    если (0) {
fmt_fail:
input_fail:
        если (!matches) matches--;
    }
match_fail:
    вернуть matches;
}

static целое ff_vsscanf(const char *s, const char *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    вернуть ff_vfscanf(&f, fmt, ap);
}

целое av_sscanf(const char *string, const char *format, ...)
{
    целое ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    вернуть ret;
}
