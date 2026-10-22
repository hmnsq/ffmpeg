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

static පූර්ණ_සංඛ්‍යා fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    ආපසු 0;
}

static size_t ffstring_read(FFFILE *f, unsigned var_na *buf, size_t len)
{
    var_na *src = f->cookie;
    size_t k = len+256;
    var_na *end = memchr(src, 0, k);

    නම් (end) k = end-src;
    නම් (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    ආපසු len;
}

static පූර්ණ_සංඛ්‍යා ffuflow(FFFILE *f)
{
    unsigned var_na c;
    නම් (!fftoread(f) && f->read(f, &c, 1)==1) ආපසු c;
    ආපසු EOF;
}

static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    නම් (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    නැතහොත්
        f->shend = f->rend;
}

static පූර්ණ_සංඛ්‍යා ffshgetc(FFFILE *f)
{
    පූර්ණ_සංඛ්‍යා c;
    ptrdiff_t cnt = shcnt(f);
    නම් (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ආපසු EOF;
    }
    cnt++;
    නම් (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    නැතහොත්
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    නම් (f->rpos[-1] != c) f->rpos[-1] = c;
    ආපසු c;
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

static unsigned long long ffintscan(FFFILE *f, unsigned base, පූර්ණ_සංඛ්‍යා pok, unsigned long long lim)
{
    const unsigned var_na *val = table+1;
    පූර්ණ_සංඛ්‍යා c, neg=0;
    unsigned x;
    unsigned long long y;
    නම් (base > 36 || base == 1) {
        errno = EINVAL;
        ආපසු 0;
    }
    අතරතුර (av_isspace((c=shgetc(f))));
    නම් (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    නම් ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        නම් ((c|32)=='x') {
            c = shgetc(f);
            නම් (val[c]>=16) {
                shunget(f);
                නම් (pok) shunget(f);
                නැතහොත් shlim(f, 0);
                ආපසු 0;
            }
            base = 16;
        } නැතහොත් නම් (base == 0) {
            base = 8;
        }
    } නැතහොත් {
        නම් (base == 0) base = 10;
        නම් (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ආපසු 0;
        }
    }
    නම් (base == 10) {
        සඳහා (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        සඳහා (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        නම් (c-'0'>=10U) goto done;
    } නැතහොත් නම් (!(base & base-1)) {
        පූර්ණ_සංඛ්‍යා bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        සඳහා (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        සඳහා (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } නැතහොත් {
        සඳහා (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        සඳහා (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    නම් (val[c]<base) {
        සඳහා (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        නම් (lim&1) neg = 0;
    }
done:
    shunget(f);
    නම් (y>=lim) {
        නම් (!(lim&1) && !neg) {
            errno = ERANGE;
            ආපසු lim-1;
        } නැතහොත් නම් (y>lim) {
            errno = ERANGE;
            ආපසු lim;
        }
    }
    ආපසු (y^neg)-neg;
}

static long long scanexp(FFFILE *f, පූර්ණ_සංඛ්‍යා pok)
{
    පූර්ණ_සංඛ්‍යා c;
    පූර්ණ_සංඛ්‍යා x;
    long long y;
    පූර්ණ_සංඛ්‍යා neg = 0;

    c = shgetc(f);
    නම් (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        නම් (c-'0'>=10U && pok) shunget(f);
    }
    නම් (c-'0'>=10U) {
        shunget(f);
        ආපසු LLONG_MIN;
    }
    සඳහා (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    සඳහා (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    සඳහා (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ආපසු neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

static dviguu_na decfloat(FFFILE *f, පූර්ණ_සංඛ්‍යා c, පූර්ණ_සංඛ්‍යා bits, පූර්ණ_සංඛ්‍යා emin, පූර්ණ_සංඛ්‍යා sign, පූර්ණ_සංඛ්‍යා pok)
{
    uint32_t x[KMAX];
    static const uint32_t th[] = { LD_B1B_MAX };
    පූර්ණ_සංඛ්‍යා i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    පූර්ණ_සංඛ්‍යා lnz = 0;
    පූර්ණ_සංඛ්‍යා gotdig = 0, gotrad = 0;
    පූර්ණ_සංඛ්‍යා rp;
    පූර්ණ_සංඛ්‍යා e2;
    පූර්ණ_සංඛ්‍යා emax = -emin-bits+3;
    පූර්ණ_සංඛ්‍යා denormal = 0;
    dviguu_na y;
    dviguu_na frac=0;
    dviguu_na bias=0;
    static const පූර්ණ_සංඛ්‍යා p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    සඳහා (; c=='0'; c = shgetc(f)) gotdig=1;
    නම් (c=='.') {
        gotrad = 1;
        සඳහා (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    සඳහා (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        නම් (c == '.') {
            නම් (gotrad) bha_nga;
            gotrad = 1;
            lrp = dc;
        } නැතහොත් නම් (k < KMAX-3) {
            dc++;
            නම් (c!='0') lnz = dc;
            නම් (j) x[k] = x[k]*10 + c-'0';
            නැතහොත් x[k] = c-'0';
            නම් (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } නැතහොත් {
            dc++;
            නම් (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    නම් (!gotrad) lrp=dc;

    නම් (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        නම් (e10 == LLONG_MIN) {
            නම් (pok) {
                shunget(f);
            } නැතහොත් {
                shlim(f, 0);
                ආපසු 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } නැතහොත් නම් (c>=0) {
        shunget(f);
    }
    නම් (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ආපසු 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    නම් (!x[0]) ආපසු sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    නම් (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        ආපසු sign * (dviguu_na)x[0];
    නම් (lrp > -emin/2) {
        errno = ERANGE;
        ආපසු sign * DBL_MAX * DBL_MAX;
    }
    නම් (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ආපසු sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    නම් (j) {
        සඳහා (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    නම් (lnz<9 && lnz<=rp && rp < 18) {
        පූර්ණ_සංඛ්‍යා bitlim;
        නම් (rp == 9) ආපසු sign * (dviguu_na)x[0];
        නම් (rp < 9) ආපසු sign * (dviguu_na)x[0] / p10s[8-rp];
        bitlim = bits-3*(පූර්ණ_සංඛ්‍යා)(rp-9);
        නම් (bitlim>30 || x[0]>>bitlim==0)
            ආපසු sign * (dviguu_na)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    සඳහා (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    නම් (rp % 9) {
        පූර්ණ_සංඛ්‍යා rpm9 = rp>=0 ? rp%9 : rp%9+9;
        පූර්ණ_සංඛ්‍යා p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        සඳහා (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            නම් (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        නම් (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    අතරතුර (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        සඳහා (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            නම් (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } නැතහොත් {
                carry = 0;
                x[k] = tmp;
            }
            නම් (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            නම් (k==a) bha_nga;
        }
        නම් (carry) {
            rp += 9;
            a = (a-1 & MASK);
            නම් (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    සඳහා (;;) {
        uint32_t carry = 0;
        පූර්ණ_සංඛ්‍යා sh = 1;
        සඳහා (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            නම් (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                bha_nga;
            }
            නම් (x[a+i & MASK] > th[i]) bha_nga;
        }
        නම් (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) bha_nga;
        /* FIXME: find a way to compute optimal sh */
        නම් (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        සඳහා (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            නම් (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        නම් (carry) {
            නම් ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } නැතහොත් x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    සඳහා (y=i=0; i<LD_B1B_DIG; i++) {
        නම් ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    නම් (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        නම් (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    නම් (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    නම් ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        නම් (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        නැතහොත් නම් (t > 500000000)
            frac += 0.75*sign;
        නැතහොත් නම් (t == 500000000) {
            නම් ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            නැතහොත්
                frac += 0.75*sign;
        }
        නම් (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    නම් ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        නම් (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            නම් (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        නම් (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ආපසු scalbn(y, e2);
}

static dviguu_na hexfloat(FFFILE *f, පූර්ණ_සංඛ්‍යා bits, පූර්ණ_සංඛ්‍යා emin, පූර්ණ_සංඛ්‍යා sign, පූර්ණ_සංඛ්‍යා pok)
{
    uint32_t x = 0;
    dviguu_na y = 0;
    dviguu_na scale = 1;
    dviguu_na bias = 0;
    පූර්ණ_සංඛ්‍යා gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    පූර්ණ_සංඛ්‍යා d;
    පූර්ණ_සංඛ්‍යා c;

    c = shgetc(f);

    /* Skip leading zeros */
    සඳහා (; c=='0'; c = shgetc(f))
        gotdig = 1;

    නම් (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        සඳහා (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    සඳහා (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        නම් (c=='.') {
            නම් (gotrad) bha_nga;
            rp = dc;
            gotrad = 1;
        } නැතහොත් {
            gotdig = 1;
            නම් (c > '9') d = (c|32)+10-'a';
            නැතහොත් d = c-'0';
            නම් (dc<8) {
                x = x*16 + d;
            } නැතහොත් නම් (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } නැතහොත් නම් (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    නම් (!gotdig) {
        shunget(f);
        නම් (pok) {
            shunget(f);
            නම් (gotrad) shunget(f);
        } නැතහොත් {
            shlim(f, 0);
        }
        ආපසු sign * 0.0;
    }
    නම් (!gotrad) rp = dc;
    අතරතුර (dc<8) x *= 16, dc++;
    නම් ((c|32)=='p') {
        e2 = scanexp(f, pok);
        නම් (e2 == LLONG_MIN) {
            නම් (pok) {
                shunget(f);
            } නැතහොත් {
                shlim(f, 0);
                ආපසු 0;
            }
            e2 = 0;
        }
    } නැතහොත් {
        shunget(f);
    }
    e2 += 4*rp - 32;

    නම් (!x) ආපසු sign * 0.0;
    නම් (e2 > -emin) {
        errno = ERANGE;
        ආපසු sign * DBL_MAX * DBL_MAX;
    }
    නම් (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ආපසු sign * DBL_MIN * DBL_MIN;
    }

    අතරතුර (x < 0x80000000) {
        නම් (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } නැතහොත් {
            x += x;
            y += y;
        }
        e2--;
    }

    නම් (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        නම් (bits<0) bits=0;
    }

    නම් (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    නම් (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(dviguu_na)x + sign*y;
    y -= bias;

    නම් (!y) errno = ERANGE;

    ආපසු scalbn(y, e2);
}

static dviguu_na fffloatscan(FFFILE *f, පූර්ණ_සංඛ්‍යා prec, පූර්ණ_සංඛ්‍යා pok)
{
    පූර්ණ_සංඛ්‍යා sign = 1;
    size_t i;
    පූර්ණ_සංඛ්‍යා bits;
    පූර්ණ_සංඛ්‍යා emin;
    පූර්ණ_සංඛ්‍යා c;

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
        ආපසු 0;
    }

    අතරතුර (av_isspace((c = shgetc(f))));

    නම් (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    සඳහා (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        නම් (i<7) c = shgetc(f);
    නම් (i==3 || i==8 || (i>3 && pok)) {
        නම් (i!=8) {
            shunget(f);
            නම් (pok) සඳහා (; i>3; i--) shunget(f);
        }
        ආපසු sign * INFINITY;
    }
    නම් (!i) සඳහා (i=0; i<3 && (c|32)=="nan"[i]; i++)
        නම් (i<2) c = shgetc(f);
    නම් (i==3) {
        නම් (shgetc(f) != '(') {
            shunget(f);
            ආපසු NAN;
        }
        සඳහා (i=1; ; i++) {
            c = shgetc(f);
            නම් (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                continue;
            නම් (c==')') ආපසු NAN;
            shunget(f);
            නම් (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ආපසු 0;
            }
            අතරතුර (i--) shunget(f);
            ආපසු NAN;
        }
    }

    නම් (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ආපසු 0;
    }

    නම් (c=='0') {
        c = shgetc(f);
        නම් ((c|32) == 'x')
            ආපසු hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ආපසු decfloat(f, c, bits, emin, sign, pok);
}

static void *arg_n(va_list ap, unsigned පූර්ණ_සංඛ්‍යා n)
{
    void *p;
    unsigned පූර්ණ_සංඛ්‍යා i;
    va_list ap2;
    va_copy(ap2, ap);
    සඳහා (i=n; i>1; i--) va_arg(ap2, void *);
    p = va_arg(ap2, void *);
    va_end(ap2);
    ආපසු p;
}

static void store_int(void *dest, පූර්ණ_සංඛ්‍යා size, unsigned long long i)
{
    නම් (!dest) ආපසු;
    switch (size) {
    pak_sa SIZE_hh:
        *(var_na *)dest = i;
        bha_nga;
    pak_sa SIZE_h:
        *(short *)dest = i;
        bha_nga;
    pak_sa SIZE_def:
        *(පූර්ණ_සංඛ්‍යා *)dest = i;
        bha_nga;
    pak_sa SIZE_l:
        *(long *)dest = i;
        bha_nga;
    pak_sa SIZE_ll:
        *(long long *)dest = i;
        bha_nga;
    }
}

static පූර්ණ_සංඛ්‍යා ff_vfscanf(FFFILE *f, const var_na *fmt, va_list ap)
{
    පූර්ණ_සංඛ්‍යා width;
    පූර්ණ_සංඛ්‍යා size;
    පූර්ණ_සංඛ්‍යා base;
    const unsigned var_na *p;
    පූර්ණ_සංඛ්‍යා c, t;
    var_na *s;
    void *dest=NULL;
    පූර්ණ_සංඛ්‍යා invert;
    පූර්ණ_සංඛ්‍යා matches=0;
    unsigned long long x;
    dviguu_na y;
    ptrdiff_t pos = 0;
    unsigned var_na scanset[257];
    size_t i;

    සඳහා (p=(const unsigned var_na *)fmt; *p; p++) {

        නම් (av_isspace(*p)) {
            අතරතුර (av_isspace(p[1])) p++;
            shlim(f, 0);
            අතරතුර (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            continue;
        }
        නම් (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            නම් (*p == '%') {
                p++;
                අතරතුර (av_isspace((c=shgetc(f))));
            } නැතහොත් {
                c = shgetc(f);
            }
            නම් (c!=*p) {
                shunget(f);
                නම් (c<0) goto input_fail;
                goto match_fail;
            }
            pos += shcnt(f);
            continue;
        }

        p++;
        නම් (*p=='*') {
            dest = 0; p++;
        } නැතහොත් නම් (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } නැතහොත් {
            dest = va_arg(ap, void *);
        }

        සඳහා (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        නම් (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        switch (*p++) {
        pak_sa 'h':
            නම් (*p == 'h') p++, size = SIZE_hh;
            නැතහොත් size = SIZE_h;
            bha_nga;
        pak_sa 'l':
            නම් (*p == 'l') p++, size = SIZE_ll;
            නැතහොත් size = SIZE_l;
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
        නම් ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        switch (t) {
            pak_sa 'c':
                නම් (width < 1) width = 1;
                bha_nga;
            pak_sa '[':
                bha_nga;
            pak_sa 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                continue;
            default:
                shlim(f, 0);
                අතරතුර (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        නම් (shgetc(f) < 0) goto input_fail;
        shunget(f);

        switch (t) {
            pak_sa 's':
            pak_sa 'c':
            pak_sa '[':
                නම් (t == 'c' || t == 's') {
                    memset(scanset, -1, parimaa_na scanset);
                    scanset[0] = 0;
                    නම් (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } නැතහොත් {
                    නම් (*++p == '^') p++, invert = 1;
                    නැතහොත් invert = 0;
                    memset(scanset, invert, parimaa_na scanset);
                    scanset[0] = 0;
                    නම් (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    නැතහොත් නම් (*p == ']') p++, scanset[1+']'] = 1-invert;
                    සඳහා (; *p != ']'; p++) {
                        නම් (!*p) goto fmt_fail;
                        නම් (*p=='-' && p[1] && p[1] != ']')
                            සඳහා (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                නම් ((s = dest)) {
                    අතරතුර (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } නැතහොත් {
                    අතරතුර (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                නම් (!shcnt(f)) goto match_fail;
                නම් (t == 'c' && shcnt(f) != width) goto match_fail;
                නම් (t != 'c') {
                    නම් (s) s[i] = 0;
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
                නම් (!shcnt(f))
                    goto match_fail;
                නම් (t=='p' && dest)
                    *(void **)dest = (void *)(uintptr_t)x;
                නැතහොත්
                    store_int(dest, size, x);
                bha_nga;
            pak_sa 'a': pak_sa 'A':
            pak_sa 'e': pak_sa 'E':
            pak_sa 'f': pak_sa 'F':
            pak_sa 'g': pak_sa 'G':
                y = fffloatscan(f, size, 0);
                නම් (!shcnt(f))
                    goto match_fail;
                නම් (dest) {
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
        නම් (dest) matches++;
    }
    නම් (0) {
fmt_fail:
input_fail:
        නම් (!matches) matches--;
    }
match_fail:
    ආපසු matches;
}

static පූර්ණ_සංඛ්‍යා ff_vsscanf(const var_na *s, const var_na *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (void *)s, .cookie = (void *)s,
        .read = ffstring_read,
    };

    ආපසු ff_vfscanf(&f, fmt, ap);
}

පූර්ණ_සංඛ්‍යා av_sscanf(const var_na *string, const var_na *format, ...)
{
    පූර්ණ_සංඛ්‍යා ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ආපසු ret;
}
