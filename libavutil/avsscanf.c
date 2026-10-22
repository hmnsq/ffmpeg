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

#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <math.h>
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <float.h>

#അന്തര്ഭാവ "avstring.h"

തരനിർവചനം ഘടന FFFILE {
    size_t buf_size;
    unsigned അക്ഷരം *buf;
    unsigned അക്ഷരം *rpos, *rend;
    unsigned അക്ഷരം *shend;
    ptrdiff_t shlim, shcnt;
    ശൂന്യം *cookie;
    size_t (*പഠ)(ഘടന FFFILE *, unsigned അക്ഷരം *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

സ്ഥിതം പൂർണ്ണസംഖ്യ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    തിരികെ 0;
}

സ്ഥിതം size_t ffstring_read(FFFILE *f, unsigned അക്ഷരം *buf, size_t len)
{
    അക്ഷരം *src = f->cookie;
    size_t k = len+256;
    അക്ഷരം *end = memchr(src, 0, k);

    എങ്കിൽ (end) k = end-src;
    എങ്കിൽ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (ശൂന്യം *)(src+len);
    f->rend = (ശൂന്യം *)(src+k);
    f->cookie = src+k;

    തിരികെ len;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ ffuflow(FFFILE *f)
{
    unsigned അക്ഷരം c;
    എങ്കിൽ (!fftoread(f) && f->പഠ(f, &c, 1)==1) തിരികെ c;
    തിരികെ EOF;
}

സ്ഥിതം ശൂന്യം ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    എങ്കിൽ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    അല്ലെങ്കിൽ
        f->shend = f->rend;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ ffshgetc(FFFILE *f)
{
    പൂർണ്ണസംഖ്യ c;
    ptrdiff_t cnt = shcnt(f);
    എങ്കിൽ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        തിരികെ EOF;
    }
    cnt++;
    എങ്കിൽ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    അല്ലെങ്കിൽ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    എങ്കിൽ (f->rpos[-1] != c) f->rpos[-1] = c;
    തിരികെ c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (ശൂന്യം)(f)->rpos-- : (ശൂന്യം)0)

സ്ഥിതം സ്ഥിരം unsigned അക്ഷരം table[] = { -1,
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

സ്ഥിതം unsigned long long ffintscan(FFFILE *f, unsigned base, പൂർണ്ണസംഖ്യ pok, unsigned long long lim)
{
    സ്ഥിരം unsigned അക്ഷരം *val = table+1;
    പൂർണ്ണസംഖ്യ c, neg=0;
    unsigned x;
    unsigned long long y;
    എങ്കിൽ (base > 36 || base == 1) {
        errno = EINVAL;
        തിരികെ 0;
    }
    ആകുമ്പോൾ (av_isspace((c=shgetc(f))));
    എങ്കിൽ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    എങ്കിൽ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        എങ്കിൽ ((c|32)=='x') {
            c = shgetc(f);
            എങ്കിൽ (val[c]>=16) {
                shunget(f);
                എങ്കിൽ (pok) shunget(f);
                അല്ലെങ്കിൽ shlim(f, 0);
                തിരികെ 0;
            }
            base = 16;
        } അല്ലെങ്കിൽ എങ്കിൽ (base == 0) {
            base = 8;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (base == 0) base = 10;
        എങ്കിൽ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            തിരികെ 0;
        }
    }
    എങ്കിൽ (base == 10) {
        വേണ്ടി (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        വേണ്ടി (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        എങ്കിൽ (c-'0'>=10U) പോകുക done;
    } അല്ലെങ്കിൽ എങ്കിൽ (!(base & base-1)) {
        പൂർണ്ണസംഖ്യ bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        വേണ്ടി (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        വേണ്ടി (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } അല്ലെങ്കിൽ {
        വേണ്ടി (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        വേണ്ടി (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    എങ്കിൽ (val[c]<base) {
        വേണ്ടി (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        എങ്കിൽ (lim&1) neg = 0;
    }
done:
    shunget(f);
    എങ്കിൽ (y>=lim) {
        എങ്കിൽ (!(lim&1) && !neg) {
            errno = ERANGE;
            തിരികെ lim-1;
        } അല്ലെങ്കിൽ എങ്കിൽ (y>lim) {
            errno = ERANGE;
            തിരികെ lim;
        }
    }
    തിരികെ (y^neg)-neg;
}

സ്ഥിതം long long scanexp(FFFILE *f, പൂർണ്ണസംഖ്യ pok)
{
    പൂർണ്ണസംഖ്യ c;
    പൂർണ്ണസംഖ്യ x;
    long long y;
    പൂർണ്ണസംഖ്യ neg = 0;

    c = shgetc(f);
    എങ്കിൽ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        എങ്കിൽ (c-'0'>=10U && pok) shunget(f);
    }
    എങ്കിൽ (c-'0'>=10U) {
        shunget(f);
        തിരികെ LLONG_MIN;
    }
    വേണ്ടി (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    വേണ്ടി (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    വേണ്ടി (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    തിരികെ neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

സ്ഥിതം ഇരട്ട decfloat(FFFILE *f, പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ bits, പൂർണ്ണസംഖ്യ emin, പൂർണ്ണസംഖ്യ sign, പൂർണ്ണസംഖ്യ pok)
{
    uint32_t x[KMAX];
    സ്ഥിതം സ്ഥിരം uint32_t th[] = { LD_B1B_MAX };
    പൂർണ്ണസംഖ്യ i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    പൂർണ്ണസംഖ്യ lnz = 0;
    പൂർണ്ണസംഖ്യ gotdig = 0, gotrad = 0;
    പൂർണ്ണസംഖ്യ rp;
    പൂർണ്ണസംഖ്യ e2;
    പൂർണ്ണസംഖ്യ emax = -emin-bits+3;
    പൂർണ്ണസംഖ്യ denormal = 0;
    ഇരട്ട y;
    ഇരട്ട frac=0;
    ഇരട്ട bias=0;
    സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    വേണ്ടി (; c=='0'; c = shgetc(f)) gotdig=1;
    എങ്കിൽ (c=='.') {
        gotrad = 1;
        വേണ്ടി (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    വേണ്ടി (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        എങ്കിൽ (c == '.') {
            എങ്കിൽ (gotrad) നിർത്തുക;
            gotrad = 1;
            lrp = dc;
        } അല്ലെങ്കിൽ എങ്കിൽ (k < KMAX-3) {
            dc++;
            എങ്കിൽ (c!='0') lnz = dc;
            എങ്കിൽ (j) x[k] = x[k]*10 + c-'0';
            അല്ലെങ്കിൽ x[k] = c-'0';
            എങ്കിൽ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } അല്ലെങ്കിൽ {
            dc++;
            എങ്കിൽ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    എങ്കിൽ (!gotrad) lrp=dc;

    എങ്കിൽ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        എങ്കിൽ (e10 == LLONG_MIN) {
            എങ്കിൽ (pok) {
                shunget(f);
            } അല്ലെങ്കിൽ {
                shlim(f, 0);
                തിരികെ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } അല്ലെങ്കിൽ എങ്കിൽ (c>=0) {
        shunget(f);
    }
    എങ്കിൽ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        തിരികെ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    എങ്കിൽ (!x[0]) തിരികെ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    എങ്കിൽ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        തിരികെ sign * (ഇരട്ട)x[0];
    എങ്കിൽ (lrp > -emin/2) {
        errno = ERANGE;
        തിരികെ sign * DBL_MAX * DBL_MAX;
    }
    എങ്കിൽ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        തിരികെ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    എങ്കിൽ (j) {
        വേണ്ടി (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    എങ്കിൽ (lnz<9 && lnz<=rp && rp < 18) {
        പൂർണ്ണസംഖ്യ bitlim;
        എങ്കിൽ (rp == 9) തിരികെ sign * (ഇരട്ട)x[0];
        എങ്കിൽ (rp < 9) തിരികെ sign * (ഇരട്ട)x[0] / p10s[8-rp];
        bitlim = bits-3*(പൂർണ്ണസംഖ്യ)(rp-9);
        എങ്കിൽ (bitlim>30 || x[0]>>bitlim==0)
            തിരികെ sign * (ഇരട്ട)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    വേണ്ടി (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    എങ്കിൽ (rp % 9) {
        പൂർണ്ണസംഖ്യ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        പൂർണ്ണസംഖ്യ p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        വേണ്ടി (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            എങ്കിൽ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        എങ്കിൽ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ആകുമ്പോൾ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        വേണ്ടി (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            എങ്കിൽ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } അല്ലെങ്കിൽ {
                carry = 0;
                x[k] = tmp;
            }
            എങ്കിൽ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            എങ്കിൽ (k==a) നിർത്തുക;
        }
        എങ്കിൽ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            എങ്കിൽ (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    വേണ്ടി (;;) {
        uint32_t carry = 0;
        പൂർണ്ണസംഖ്യ sh = 1;
        വേണ്ടി (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            എങ്കിൽ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                നിർത്തുക;
            }
            എങ്കിൽ (x[a+i & MASK] > th[i]) നിർത്തുക;
        }
        എങ്കിൽ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) നിർത്തുക;
        /* FIXME: find a way to compute optimal sh */
        എങ്കിൽ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        വേണ്ടി (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            എങ്കിൽ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        എങ്കിൽ (carry) {
            എങ്കിൽ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } അല്ലെങ്കിൽ x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    വേണ്ടി (y=i=0; i<LD_B1B_DIG; i++) {
        എങ്കിൽ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    എങ്കിൽ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        എങ്കിൽ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    എങ്കിൽ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    എങ്കിൽ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        എങ്കിൽ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        അല്ലെങ്കിൽ എങ്കിൽ (t > 500000000)
            frac += 0.75*sign;
        അല്ലെങ്കിൽ എങ്കിൽ (t == 500000000) {
            എങ്കിൽ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            അല്ലെങ്കിൽ
                frac += 0.75*sign;
        }
        എങ്കിൽ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    എങ്കിൽ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        എങ്കിൽ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            എങ്കിൽ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        എങ്കിൽ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    തിരികെ scalbn(y, e2);
}

സ്ഥിതം ഇരട്ട hexfloat(FFFILE *f, പൂർണ്ണസംഖ്യ bits, പൂർണ്ണസംഖ്യ emin, പൂർണ്ണസംഖ്യ sign, പൂർണ്ണസംഖ്യ pok)
{
    uint32_t x = 0;
    ഇരട്ട y = 0;
    ഇരട്ട scale = 1;
    ഇരട്ട bias = 0;
    പൂർണ്ണസംഖ്യ gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    പൂർണ്ണസംഖ്യ d;
    പൂർണ്ണസംഖ്യ c;

    c = shgetc(f);

    /* Skip leading zeros */
    വേണ്ടി (; c=='0'; c = shgetc(f))
        gotdig = 1;

    എങ്കിൽ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        വേണ്ടി (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    വേണ്ടി (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        എങ്കിൽ (c=='.') {
            എങ്കിൽ (gotrad) നിർത്തുക;
            rp = dc;
            gotrad = 1;
        } അല്ലെങ്കിൽ {
            gotdig = 1;
            എങ്കിൽ (c > '9') d = (c|32)+10-'a';
            അല്ലെങ്കിൽ d = c-'0';
            എങ്കിൽ (dc<8) {
                x = x*16 + d;
            } അല്ലെങ്കിൽ എങ്കിൽ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } അല്ലെങ്കിൽ എങ്കിൽ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    എങ്കിൽ (!gotdig) {
        shunget(f);
        എങ്കിൽ (pok) {
            shunget(f);
            എങ്കിൽ (gotrad) shunget(f);
        } അല്ലെങ്കിൽ {
            shlim(f, 0);
        }
        തിരികെ sign * 0.0;
    }
    എങ്കിൽ (!gotrad) rp = dc;
    ആകുമ്പോൾ (dc<8) x *= 16, dc++;
    എങ്കിൽ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        എങ്കിൽ (e2 == LLONG_MIN) {
            എങ്കിൽ (pok) {
                shunget(f);
            } അല്ലെങ്കിൽ {
                shlim(f, 0);
                തിരികെ 0;
            }
            e2 = 0;
        }
    } അല്ലെങ്കിൽ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    എങ്കിൽ (!x) തിരികെ sign * 0.0;
    എങ്കിൽ (e2 > -emin) {
        errno = ERANGE;
        തിരികെ sign * DBL_MAX * DBL_MAX;
    }
    എങ്കിൽ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        തിരികെ sign * DBL_MIN * DBL_MIN;
    }

    ആകുമ്പോൾ (x < 0x80000000) {
        എങ്കിൽ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } അല്ലെങ്കിൽ {
            x += x;
            y += y;
        }
        e2--;
    }

    എങ്കിൽ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        എങ്കിൽ (bits<0) bits=0;
    }

    എങ്കിൽ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    എങ്കിൽ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ഇരട്ട)x + sign*y;
    y -= bias;

    എങ്കിൽ (!y) errno = ERANGE;

    തിരികെ scalbn(y, e2);
}

സ്ഥിതം ഇരട്ട fffloatscan(FFFILE *f, പൂർണ്ണസംഖ്യ prec, പൂർണ്ണസംഖ്യ pok)
{
    പൂർണ്ണസംഖ്യ sign = 1;
    size_t i;
    പൂർണ്ണസംഖ്യ bits;
    പൂർണ്ണസംഖ്യ emin;
    പൂർണ്ണസംഖ്യ c;

    തിരഞ്ഞെടുപ്പ് (prec) {
    അവസ്ഥ 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        നിർത്തുക;
    അവസ്ഥ 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        നിർത്തുക;
    അവസ്ഥ 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ 0;
    }

    ആകുമ്പോൾ (av_isspace((c = shgetc(f))));

    എങ്കിൽ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    വേണ്ടി (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        എങ്കിൽ (i<7) c = shgetc(f);
    എങ്കിൽ (i==3 || i==8 || (i>3 && pok)) {
        എങ്കിൽ (i!=8) {
            shunget(f);
            എങ്കിൽ (pok) വേണ്ടി (; i>3; i--) shunget(f);
        }
        തിരികെ sign * INFINITY;
    }
    എങ്കിൽ (!i) വേണ്ടി (i=0; i<3 && (c|32)=="nan"[i]; i++)
        എങ്കിൽ (i<2) c = shgetc(f);
    എങ്കിൽ (i==3) {
        എങ്കിൽ (shgetc(f) != '(') {
            shunget(f);
            തിരികെ NAN;
        }
        വേണ്ടി (i=1; ; i++) {
            c = shgetc(f);
            എങ്കിൽ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                തുടരുക;
            എങ്കിൽ (c==')') തിരികെ NAN;
            shunget(f);
            എങ്കിൽ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                തിരികെ 0;
            }
            ആകുമ്പോൾ (i--) shunget(f);
            തിരികെ NAN;
        }
    }

    എങ്കിൽ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        തിരികെ 0;
    }

    എങ്കിൽ (c=='0') {
        c = shgetc(f);
        എങ്കിൽ ((c|32) == 'x')
            തിരികെ hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    തിരികെ decfloat(f, c, bits, emin, sign, pok);
}

സ്ഥിതം ശൂന്യം *arg_n(va_list ap, unsigned പൂർണ്ണസംഖ്യ n)
{
    ശൂന്യം *p;
    unsigned പൂർണ്ണസംഖ്യ i;
    va_list ap2;
    va_copy(ap2, ap);
    വേണ്ടി (i=n; i>1; i--) va_arg(ap2, ശൂന്യം *);
    p = va_arg(ap2, ശൂന്യം *);
    va_end(ap2);
    തിരികെ p;
}

സ്ഥിതം ശൂന്യം store_int(ശൂന്യം *dest, പൂർണ്ണസംഖ്യ size, unsigned long long i)
{
    എങ്കിൽ (!dest) തിരികെ;
    തിരഞ്ഞെടുപ്പ് (size) {
    അവസ്ഥ SIZE_hh:
        *(അക്ഷരം *)dest = i;
        നിർത്തുക;
    അവസ്ഥ SIZE_h:
        *(short *)dest = i;
        നിർത്തുക;
    അവസ്ഥ SIZE_def:
        *(പൂർണ്ണസംഖ്യ *)dest = i;
        നിർത്തുക;
    അവസ്ഥ SIZE_l:
        *(long *)dest = i;
        നിർത്തുക;
    അവസ്ഥ SIZE_ll:
        *(long long *)dest = i;
        നിർത്തുക;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ ff_vfscanf(FFFILE *f, സ്ഥിരം അക്ഷരം *fmt, va_list ap)
{
    പൂർണ്ണസംഖ്യ width;
    പൂർണ്ണസംഖ്യ size;
    പൂർണ്ണസംഖ്യ base;
    സ്ഥിരം unsigned അക്ഷരം *p;
    പൂർണ്ണസംഖ്യ c, t;
    അക്ഷരം *s;
    ശൂന്യം *dest=ശൂന്യ;
    പൂർണ്ണസംഖ്യ invert;
    പൂർണ്ണസംഖ്യ matches=0;
    unsigned long long x;
    ഇരട്ട y;
    ptrdiff_t pos = 0;
    unsigned അക്ഷരം scanset[257];
    size_t i;

    വേണ്ടി (p=(സ്ഥിരം unsigned അക്ഷരം *)fmt; *p; p++) {

        എങ്കിൽ (av_isspace(*p)) {
            ആകുമ്പോൾ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ആകുമ്പോൾ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            തുടരുക;
        }
        എങ്കിൽ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            എങ്കിൽ (*p == '%') {
                p++;
                ആകുമ്പോൾ (av_isspace((c=shgetc(f))));
            } അല്ലെങ്കിൽ {
                c = shgetc(f);
            }
            എങ്കിൽ (c!=*p) {
                shunget(f);
                എങ്കിൽ (c<0) പോകുക നിവേശം_fail;
                പോകുക match_fail;
            }
            pos += shcnt(f);
            തുടരുക;
        }

        p++;
        എങ്കിൽ (*p=='*') {
            dest = 0; p++;
        } അല്ലെങ്കിൽ എങ്കിൽ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } അല്ലെങ്കിൽ {
            dest = va_arg(ap, ശൂന്യം *);
        }

        വേണ്ടി (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        എങ്കിൽ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        തിരഞ്ഞെടുപ്പ് (*p++) {
        അവസ്ഥ 'h':
            എങ്കിൽ (*p == 'h') p++, size = SIZE_hh;
            അല്ലെങ്കിൽ size = SIZE_h;
            നിർത്തുക;
        അവസ്ഥ 'l':
            എങ്കിൽ (*p == 'l') p++, size = SIZE_ll;
            അല്ലെങ്കിൽ size = SIZE_l;
            നിർത്തുക;
        അവസ്ഥ 'j':
            size = SIZE_ll;
            നിർത്തുക;
        അവസ്ഥ 'z':
        അവസ്ഥ 't':
            size = SIZE_l;
            നിർത്തുക;
        അവസ്ഥ 'L':
            size = SIZE_L;
            നിർത്തുക;
        അവസ്ഥ 'd': അവസ്ഥ 'i': അവസ്ഥ 'o': അവസ്ഥ 'u': അവസ്ഥ 'x':
        അവസ്ഥ 'a': അവസ്ഥ 'e': അവസ്ഥ 'f': അവസ്ഥ 'g':
        അവസ്ഥ 'A': അവസ്ഥ 'E': അവസ്ഥ 'F': അവസ്ഥ 'G': അവസ്ഥ 'X':
        അവസ്ഥ 's': അവസ്ഥ 'c': അവസ്ഥ '[':
        അവസ്ഥ 'S': അവസ്ഥ 'C':
        അവസ്ഥ 'p': അവസ്ഥ 'n':
            p--;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            പോകുക fmt_fail;
        }

        t = *p;

        /* C or S */
        എങ്കിൽ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        തിരഞ്ഞെടുപ്പ് (t) {
            അവസ്ഥ 'c':
                എങ്കിൽ (width < 1) width = 1;
                നിർത്തുക;
            അവസ്ഥ '[':
                നിർത്തുക;
            അവസ്ഥ 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                തുടരുക;
            സ്ഥിരസ്ഥിതി:
                shlim(f, 0);
                ആകുമ്പോൾ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        എങ്കിൽ (shgetc(f) < 0) പോകുക നിവേശം_fail;
        shunget(f);

        തിരഞ്ഞെടുപ്പ് (t) {
            അവസ്ഥ 's':
            അവസ്ഥ 'c':
            അവസ്ഥ '[':
                എങ്കിൽ (t == 'c' || t == 's') {
                    memset(scanset, -1, വലുപ്പം scanset);
                    scanset[0] = 0;
                    എങ്കിൽ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } അല്ലെങ്കിൽ {
                    എങ്കിൽ (*++p == '^') p++, invert = 1;
                    അല്ലെങ്കിൽ invert = 0;
                    memset(scanset, invert, വലുപ്പം scanset);
                    scanset[0] = 0;
                    എങ്കിൽ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    അല്ലെങ്കിൽ എങ്കിൽ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    വേണ്ടി (; *p != ']'; p++) {
                        എങ്കിൽ (!*p) പോകുക fmt_fail;
                        എങ്കിൽ (*p=='-' && p[1] && p[1] != ']')
                            വേണ്ടി (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                എങ്കിൽ ((s = dest)) {
                    ആകുമ്പോൾ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } അല്ലെങ്കിൽ {
                    ആകുമ്പോൾ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                എങ്കിൽ (!shcnt(f)) പോകുക match_fail;
                എങ്കിൽ (t == 'c' && shcnt(f) != width) പോകുക match_fail;
                എങ്കിൽ (t != 'c') {
                    എങ്കിൽ (s) s[i] = 0;
                }
                നിർത്തുക;
            അവസ്ഥ 'p':
            അവസ്ഥ 'X':
            അവസ്ഥ 'x':
                base = 16;
                പോകുക int_common;
            അവസ്ഥ 'o':
                base = 8;
                പോകുക int_common;
            അവസ്ഥ 'd':
            അവസ്ഥ 'u':
                base = 10;
                പോകുക int_common;
            അവസ്ഥ 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                എങ്കിൽ (!shcnt(f))
                    പോകുക match_fail;
                എങ്കിൽ (t=='p' && dest)
                    *(ശൂന്യം **)dest = (ശൂന്യം *)(uintptr_t)x;
                അല്ലെങ്കിൽ
                    store_int(dest, size, x);
                നിർത്തുക;
            അവസ്ഥ 'a': അവസ്ഥ 'A':
            അവസ്ഥ 'e': അവസ്ഥ 'E':
            അവസ്ഥ 'f': അവസ്ഥ 'F':
            അവസ്ഥ 'g': അവസ്ഥ 'G':
                y = fffloatscan(f, size, 0);
                എങ്കിൽ (!shcnt(f))
                    പോകുക match_fail;
                എങ്കിൽ (dest) {
                    തിരഞ്ഞെടുപ്പ് (size) {
                    അവസ്ഥ SIZE_def:
                        *(ദശാംശം *)dest = y;
                        നിർത്തുക;
                    അവസ്ഥ SIZE_l:
                        *(ഇരട്ട *)dest = y;
                        നിർത്തുക;
                    അവസ്ഥ SIZE_L:
                        *(ഇരട്ട *)dest = y;
                        നിർത്തുക;
                    }
                }
                നിർത്തുക;
        }

        pos += shcnt(f);
        എങ്കിൽ (dest) matches++;
    }
    എങ്കിൽ (0) {
fmt_fail:
നിവേശം_fail:
        എങ്കിൽ (!matches) matches--;
    }
match_fail:
    തിരികെ matches;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ ff_vsscanf(സ്ഥിരം അക്ഷരം *s, സ്ഥിരം അക്ഷരം *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (ശൂന്യം *)s, .cookie = (ശൂന്യം *)s,
        .പഠ = ffstring_read,
    };

    തിരികെ ff_vfscanf(&f, fmt, ap);
}

പൂർണ്ണസംഖ്യ av_sscanf(സ്ഥിരം അക്ഷരം *string, സ്ഥിരം അക്ഷരം *format, ...)
{
    പൂർണ്ണസംഖ്യ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    തിരികെ ret;
}
