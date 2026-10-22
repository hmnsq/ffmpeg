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

static จำนวนเต็ม fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    คืน 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    ถ้า (end) k = end-src;
    ถ้า (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    คืน len;
}

static จำนวนเต็ม ffuflow(FFFILE *f)
{
    unsigned var_na c;
    ถ้า (!fftoread(f) && f->read(f, &c, 1)==1) คืน c;
    คืน EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ถ้า (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    มิฉะนั้น
        f->shend = f->rend;
}

static จำนวนเต็ม ffshgetc(FFFILE *f)
{
    จำนวนเต็ม c;
    ptrdiff_t cnt = shcnt(f);
    ถ้า (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        คืน EOF;
    }
    cnt++;
    ถ้า (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    มิฉะนั้น
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ถ้า (f->rpos[-1] != c) f->rpos[-1] = c;
    คืน c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, จำนวนเต็ม pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    จำนวนเต็ม c, neg=0;
    unsigned x;
    unsigned long long y;
    ถ้า (base > 36 || base == 1) {
        errno = EINVAL;
        คืน 0;
    }
    ขณะ (av_isspace((c=shgetc(f))));
    ถ้า (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ถ้า ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        ถ้า ((c|32)=='x') {
            c = shgetc(f);
            ถ้า (val[c]>=16) {
                shunget(f);
                ถ้า (pok) shunget(f);
                มิฉะนั้น shlim(f, 0);
                คืน 0;
            }
            base = 16;
        } มิฉะนั้น ถ้า (base == 0) {
            base = 8;
        }
    } มิฉะนั้น {
        ถ้า (base == 0) base = 10;
        ถ้า (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            คืน 0;
        }
    }
    ถ้า (base == 10) {
        สำหรับ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        สำหรับ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ถ้า (c-'0'>=10U) goto done;
    } มิฉะนั้น ถ้า (!(base & base-1)) {
        จำนวนเต็ม bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        สำหรับ (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        สำหรับ (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } มิฉะนั้น {
        สำหรับ (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        สำหรับ (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    ถ้า (val[c]<base) {
        สำหรับ (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ถ้า (lim&1) neg = 0;
    }
done:
    shunget(f);
    ถ้า (y>=lim) {
        ถ้า (!(lim&1) && !neg) {
            errno = ERANGE;
            คืน lim-1;
        } มิฉะนั้น ถ้า (y>lim) {
            errno = ERANGE;
            คืน lim;
        }
    }
    คืน (y^neg)-neg;
}

static long long scanexp(FFFILE *f, จำนวนเต็ม pok)
{
    จำนวนเต็ม c;
    จำนวนเต็ม x;
    long long y;
    จำนวนเต็ม neg = 0;

    c = shgetc(f);
    ถ้า (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ถ้า (c-'0'>=10U && pok) shunget(f);
    }
    ถ้า (c-'0'>=10U) {
        shunget(f);
        คืน LLONG_MIN;
    }
    สำหรับ (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    สำหรับ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    สำหรับ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    คืน neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, จำนวนเต็ม c, จำนวนเต็ม bits, จำนวนเต็ม emin, จำนวนเต็ม sign, จำนวนเต็ม pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    จำนวนเต็ม i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    จำนวนเต็ม lnz = 0;
    จำนวนเต็ม gotdig = 0, gotrad = 0;
    จำนวนเต็ม rp;
    จำนวนเต็ม e2;
    จำนวนเต็ม emax = -emin-bits+3;
    จำนวนเต็ม denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const จำนวนเต็ม p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    สำหรับ (; c=='0'; c = shgetc(f)) gotdig=1;
    ถ้า (c=='.') {
        gotrad = 1;
        สำหรับ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    สำหรับ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ถ้า (c == '.') {
            ถ้า (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } มิฉะนั้น ถ้า (k < KMAX-3) {
            dc++;
            ถ้า (c!='0') lnz = dc;
            ถ้า (j) x[k] = x[k]*10 + c-'0';
            มิฉะนั้น x[k] = c-'0';
            ถ้า (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } มิฉะนั้น {
            dc++;
            ถ้า (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ถ้า (!gotrad) lrp=dc;

    ถ้า (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ถ้า (e10 == LLONG_MIN) {
            ถ้า (pok) {
                shunget(f);
            } มิฉะนั้น {
                shlim(f, 0);
                คืน 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } มิฉะนั้น ถ้า (c>=0) {
        shunget(f);
    }
    ถ้า (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        คืน 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ถ้า (!x[0]) คืน sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ถ้า (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        คืน sign * (dviguu_na)x[0];
    ถ้า (lrp > -emin/2) {
        errno = ERANGE;
        คืน sign * DBL_MAX * DBL_MAX;
    }
    ถ้า (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        คืน sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ถ้า (j) {
        สำหรับ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ถ้า (lnz<9 && lnz<=rp && rp < 18) {
        จำนวนเต็ม bitlim;
        ถ้า (rp == 9) คืน sign * (dviguu_na)x[0];
        ถ้า (rp < 9) คืน sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(จำนวนเต็ม)(rp-9);
        ถ้า (bitlim>30 || x[0]>>bitlim==0)
            คืน sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    สำหรับ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ถ้า (rp % 9) {
        จำนวนเต็ม rpm9 = rp>=0 ? rp%9 : rp%9+9;
        จำนวนเต็ม p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        สำหรับ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            ถ้า (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        ถ้า (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ขณะ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        สำหรับ (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            ถ้า (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } มิฉะนั้น {
                carry = 0;
                x[k] = tmp;
            }
            ถ้า (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            ถ้า (k==a) bha_nga;
        }
        ถ้า (carry) {
            rp += 9;
            a = (a-1 & MASK);
            ถ้า (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    สำหรับ (;;) {
        uint32_t carry = 0;
        จำนวนเต็ม sh = 1;
        สำหรับ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            ถ้า (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            ถ้า (x[a+i & MASK] > th[i]) bha_nga;
        }
        ถ้า (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        ถ้า (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        สำหรับ (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            ถ้า (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        ถ้า (carry) {
            ถ้า ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } มิฉะนั้น x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    สำหรับ (y=i=0; i<LD_B1B_DIG; i++) {
        ถ้า ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ถ้า (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        ถ้า (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ถ้า (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ถ้า ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        ถ้า (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        มิฉะนั้น ถ้า (t > 500000000)
            frac += 0.75*sign;
        มิฉะนั้น ถ้า (t == 500000000) {
            ถ้า ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            มิฉะนั้น
                frac += 0.75*sign;
        }
        ถ้า (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ถ้า ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        ถ้า (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            ถ้า (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ถ้า (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    คืน scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, จำนวนเต็ม bits, จำนวนเต็ม emin, จำนวนเต็ม sign, จำนวนเต็ม pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    จำนวนเต็ม gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    จำนวนเต็ม d;
    จำนวนเต็ม c;

    c = shgetc(f);

    /* Skip leading zeros */
    สำหรับ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ถ้า (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        สำหรับ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    สำหรับ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ถ้า (c=='.') {
            ถ้า (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } มิฉะนั้น {
            gotdig = 1;
            ถ้า (c > '9') d = (c|32)+10-'a';
            มิฉะนั้น d = c-'0';
            ถ้า (dc<8) {
                x = x*16 + d;
            } มิฉะนั้น ถ้า (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } มิฉะนั้น ถ้า (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ถ้า (!gotdig) {
        shunget(f);
        ถ้า (pok) {
            shunget(f);
            ถ้า (gotrad) shunget(f);
        } มิฉะนั้น {
            shlim(f, 0);
        }
        คืน sign * 0.0;
    }
    ถ้า (!gotrad) rp = dc;
    ขณะ (dc<8) x *= 16, dc++;
    ถ้า ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ถ้า (e2 == LLONG_MIN) {
            ถ้า (pok) {
                shunget(f);
            } มิฉะนั้น {
                shlim(f, 0);
                คืน 0;
            }
            e2 = 0;
        }
    } มิฉะนั้น {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ถ้า (!x) คืน sign * 0.0;
    ถ้า (e2 > -emin) {
        errno = ERANGE;
        คืน sign * DBL_MAX * DBL_MAX;
    }
    ถ้า (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        คืน sign * DBL_MIN * DBL_MIN;
    }

    ขณะ (x < 0x80000000) {
        ถ้า (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } มิฉะนั้น {
            x += x;
            y += y;
        }
        e2--;
    }

    ถ้า (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        ถ้า (bits<0) bits=0;
    }

    ถ้า (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    ถ้า (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    ถ้า (!y) errno = ERANGE;

    คืน scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, จำนวนเต็ม prec, จำนวนเต็ม pok)
{
    จำนวนเต็ม sign = 1;
    size_t i;
    จำนวนเต็ม bits;
    จำนวนเต็ม emin;
    จำนวนเต็ม c;

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
        คืน 0;
    }

    ขณะ (av_isspace((c = shgetc(f))));

    ถ้า (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    สำหรับ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ถ้า (i<7) c = shgetc(f);
    ถ้า (i==3 || i==8 || (i>3 && pok)) {
        ถ้า (i!=8) {
            shunget(f);
            ถ้า (pok) สำหรับ (; i>3; i--) shunget(f);
        }
        คืน sign * INFINITY;
    }
    ถ้า (!i) สำหรับ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ถ้า (i<2) c = shgetc(f);
    ถ้า (i==3) {
        ถ้า (shgetc(f) != '(') {
            shunget(f);
            คืน NAN;
        }
        สำหรับ (i=1; ; i++) {
            c = shgetc(f);
            ถ้า (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            ถ้า (c==')') คืน NAN;
            shunget(f);
            ถ้า (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                คืน 0;
            }
            ขณะ (i--) shunget(f);
            คืน NAN;
        }
    }

    ถ้า (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        คืน 0;
    }

    ถ้า (c=='0') {
        c = shgetc(f);
        ถ้า ((c|32) == 'x')
            คืน hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    คืน decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned จำนวนเต็ม n)
{
    void *p;
    unsigned จำนวนเต็ม i;
    va_list ap2;
    va_copy(ap2, ap);
    สำหรับ (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    คืน p;
}

static void store_int(void *dest, จำนวนเต็ม size, unsigned long long i)
{
    ถ้า (!dest) คืน;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(จำนวนเต็ม *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static จำนวนเต็ม ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    จำนวนเต็ม width;
    จำนวนเต็ม size;
    จำนวนเต็ม base;
    const unsigned var_na *p;
    จำนวนเต็ม c, t;
    var_na *s;
    void *dest=NULL;
    จำนวนเต็ม invert;
    จำนวนเต็ม matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    สำหรับ (p=(const unsigned var_na *)fmt; *p; p++) {

        ถ้า (av_isspace(*p)) {
            ขณะ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ขณะ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        ถ้า (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ถ้า (*p == '%') {
                p++;
                ขณะ (av_isspace((c=shgetc(f))));
            } มิฉะนั้น {
                c = shgetc(f);
            }
            ถ้า (c!=*p) {
                shunget(f);
                ถ้า (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        ถ้า (*p=='*') {
            dest = 0; p++;
        } มิฉะนั้น ถ้า (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } มิฉะนั้น {
            dest = va_arg(ap, void *);
        }

        สำหรับ (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        ถ้า (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            ถ้า (*p == 'h') p++, size = SIZE_hh;
            มิฉะนั้น size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            ถ้า (*p == 'l') p++, size = SIZE_ll;
            มิฉะนั้น size = SIZE_l;
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
        ถ้า ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                ถ้า (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                ขณะ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        ถ้า (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                ถ้า (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    ถ้า (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } มิฉะนั้น {
                    ถ้า (*++p == '^') p++, invert = 1;
                    มิฉะนั้น invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    ถ้า (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    มิฉะนั้น ถ้า (*p == ']') p++, scanset[1+']'] = 1-invert;
                    สำหรับ (; *p != ']'; p++) {
                        ถ้า (!*p) goto fmt_fail;
                        ถ้า (*p=='-' && p[1] && p[1] != ']')
                            สำหรับ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ถ้า ((s = dest)) {
                    ขณะ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } มิฉะนั้น {
                    ขณะ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ถ้า (!shcnt(f)) goto match_fail;
                ถ้า (t == 'c' && shcnt(f) != width) goto match_fail;
                ถ้า (t != 'c') {
                    ถ้า (s) s[i] = 0;
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
                ถ้า (!shcnt(f))
                    goto match_fail;
                ถ้า (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                มิฉะนั้น
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                ถ้า (!shcnt(f))
                    goto match_fail;
                ถ้า (dest) {
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
        ถ้า (dest) matches++;
    }
    ถ้า (0) {
fmt_fail:
input_fail:
        ถ้า (!matches) matches--;
    }
match_fail:
    คืน matches;
}

static จำนวนเต็ม ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    คืน ff_vfscanf(&f, fmt, ap);
}

จำนวนเต็ม av_sscanf(const var_na *string, const var_na *format, ...)
{
    จำนวนเต็ม ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    คืน ret;
}
