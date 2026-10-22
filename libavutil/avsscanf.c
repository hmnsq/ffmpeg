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

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <math.h>
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <float.h>

#அந்தர்பாவ "avstring.h"

வகைவரை கட்டமைப்பு FFFILE {
    size_t buf_size;
    unsigned எழுத்து *buf;
    unsigned எழுத்து *rpos, *rend;
    unsigned எழுத்து *shend;
    ptrdiff_t shlim, shcnt;
    வெறுமை *cookie;
    size_t (*பட)(கட்டமைப்பு FFFILE *, unsigned எழுத்து *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

நிலையான முழு fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    திரும்பு 0;
}

நிலையான size_t ffstring_read(FFFILE *f, unsigned எழுத்து *buf, size_t len)
{
    எழுத்து *src = f->cookie;
    size_t k = len+256;
    எழுத்து *end = memchr(src, 0, k);

    எனில் (end) k = end-src;
    எனில் (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (வெறுமை *)(src+len);
    f->rend = (வெறுமை *)(src+k);
    f->cookie = src+k;

    திரும்பு len;
}

நிலையான முழு ffuflow(FFFILE *f)
{
    unsigned எழுத்து c;
    எனில் (!fftoread(f) && f->பட(f, &c, 1)==1) திரும்பு c;
    திரும்பு EOF;
}

நிலையான வெறுமை ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    எனில் (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    இல்லையெனில்
        f->shend = f->rend;
}

நிலையான முழு ffshgetc(FFFILE *f)
{
    முழு c;
    ptrdiff_t cnt = shcnt(f);
    எனில் (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        திரும்பு EOF;
    }
    cnt++;
    எனில் (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    இல்லையெனில்
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    எனில் (f->rpos[-1] != c) f->rpos[-1] = c;
    திரும்பு c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (வெறுமை)(f)->rpos-- : (வெறுமை)0)

நிலையான மாறிலி unsigned எழுத்து table[] = { -1,
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

நிலையான unsigned long long ffintscan(FFFILE *f, unsigned base, முழு pok, unsigned long long lim)
{
    மாறிலி unsigned எழுத்து *val = table+1;
    முழு c, neg=0;
    unsigned x;
    unsigned long long y;
    எனில் (base > 36 || base == 1) {
        errno = EINVAL;
        திரும்பு 0;
    }
    போது (av_isspace((c=shgetc(f))));
    எனில் (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    எனில் ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        எனில் ((c|32)=='x') {
            c = shgetc(f);
            எனில் (val[c]>=16) {
                shunget(f);
                எனில் (pok) shunget(f);
                இல்லையெனில் shlim(f, 0);
                திரும்பு 0;
            }
            base = 16;
        } இல்லையெனில் எனில் (base == 0) {
            base = 8;
        }
    } இல்லையெனில் {
        எனில் (base == 0) base = 10;
        எனில் (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            திரும்பு 0;
        }
    }
    எனில் (base == 10) {
        க்கு (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        க்கு (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        எனில் (c-'0'>=10U) செல் done;
    } இல்லையெனில் எனில் (!(base & base-1)) {
        முழு bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        க்கு (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        க்கு (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } இல்லையெனில் {
        க்கு (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        க்கு (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    எனில் (val[c]<base) {
        க்கு (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        எனில் (lim&1) neg = 0;
    }
done:
    shunget(f);
    எனில் (y>=lim) {
        எனில் (!(lim&1) && !neg) {
            errno = ERANGE;
            திரும்பு lim-1;
        } இல்லையெனில் எனில் (y>lim) {
            errno = ERANGE;
            திரும்பு lim;
        }
    }
    திரும்பு (y^neg)-neg;
}

நிலையான long long scanexp(FFFILE *f, முழு pok)
{
    முழு c;
    முழு x;
    long long y;
    முழு neg = 0;

    c = shgetc(f);
    எனில் (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        எனில் (c-'0'>=10U && pok) shunget(f);
    }
    எனில் (c-'0'>=10U) {
        shunget(f);
        திரும்பு LLONG_MIN;
    }
    க்கு (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    க்கு (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    க்கு (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    திரும்பு neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

நிலையான இரட்டை decfloat(FFFILE *f, முழு c, முழு bits, முழு emin, முழு sign, முழு pok)
{
    uint32_t x[KMAX];
    நிலையான மாறிலி uint32_t th[] = { LD_B1B_MAX };
    முழு i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    முழு lnz = 0;
    முழு gotdig = 0, gotrad = 0;
    முழு rp;
    முழு e2;
    முழு emax = -emin-bits+3;
    முழு denormal = 0;
    இரட்டை y;
    இரட்டை frac=0;
    இரட்டை bias=0;
    நிலையான மாறிலி முழு p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    க்கு (; c=='0'; c = shgetc(f)) gotdig=1;
    எனில் (c=='.') {
        gotrad = 1;
        க்கு (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    க்கு (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        எனில் (c == '.') {
            எனில் (gotrad) நிறுத்து;
            gotrad = 1;
            lrp = dc;
        } இல்லையெனில் எனில் (k < KMAX-3) {
            dc++;
            எனில் (c!='0') lnz = dc;
            எனில் (j) x[k] = x[k]*10 + c-'0';
            இல்லையெனில் x[k] = c-'0';
            எனில் (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } இல்லையெனில் {
            dc++;
            எனில் (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    எனில் (!gotrad) lrp=dc;

    எனில் (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        எனில் (e10 == LLONG_MIN) {
            எனில் (pok) {
                shunget(f);
            } இல்லையெனில் {
                shlim(f, 0);
                திரும்பு 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } இல்லையெனில் எனில் (c>=0) {
        shunget(f);
    }
    எனில் (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        திரும்பு 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    எனில் (!x[0]) திரும்பு sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    எனில் (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        திரும்பு sign * (இரட்டை)x[0];
    எனில் (lrp > -emin/2) {
        errno = ERANGE;
        திரும்பு sign * DBL_MAX * DBL_MAX;
    }
    எனில் (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        திரும்பு sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    எனில் (j) {
        க்கு (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    எனில் (lnz<9 && lnz<=rp && rp < 18) {
        முழு bitlim;
        எனில் (rp == 9) திரும்பு sign * (இரட்டை)x[0];
        எனில் (rp < 9) திரும்பு sign * (இரட்டை)x[0] / p10s[8-rp];
        bitlim = bits-3*(முழு)(rp-9);
        எனில் (bitlim>30 || x[0]>>bitlim==0)
            திரும்பு sign * (இரட்டை)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    க்கு (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    எனில் (rp % 9) {
        முழு rpm9 = rp>=0 ? rp%9 : rp%9+9;
        முழு p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        க்கு (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            எனில் (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        எனில் (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    போது (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        க்கு (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            எனில் (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } இல்லையெனில் {
                carry = 0;
                x[k] = tmp;
            }
            எனில் (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            எனில் (k==a) நிறுத்து;
        }
        எனில் (carry) {
            rp += 9;
            a = (a-1 & MASK);
            எனில் (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    க்கு (;;) {
        uint32_t carry = 0;
        முழு sh = 1;
        க்கு (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            எனில் (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                நிறுத்து;
            }
            எனில் (x[a+i & MASK] > th[i]) நிறுத்து;
        }
        எனில் (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) நிறுத்து;
        /* FIXME: find a way to compute optimal sh */
        எனில் (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        க்கு (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            எனில் (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        எனில் (carry) {
            எனில் ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } இல்லையெனில் x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    க்கு (y=i=0; i<LD_B1B_DIG; i++) {
        எனில் ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    எனில் (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        எனில் (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    எனில் (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    எனில் ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        எனில் (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        இல்லையெனில் எனில் (t > 500000000)
            frac += 0.75*sign;
        இல்லையெனில் எனில் (t == 500000000) {
            எனில் ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            இல்லையெனில்
                frac += 0.75*sign;
        }
        எனில் (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    எனில் ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        எனில் (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            எனில் (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        எனில் (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    திரும்பு scalbn(y, e2);
}

நிலையான இரட்டை hexfloat(FFFILE *f, முழு bits, முழு emin, முழு sign, முழு pok)
{
    uint32_t x = 0;
    இரட்டை y = 0;
    இரட்டை scale = 1;
    இரட்டை bias = 0;
    முழு gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    முழு d;
    முழு c;

    c = shgetc(f);

    /* Skip leading zeros */
    க்கு (; c=='0'; c = shgetc(f))
        gotdig = 1;

    எனில் (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        க்கு (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    க்கு (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        எனில் (c=='.') {
            எனில் (gotrad) நிறுத்து;
            rp = dc;
            gotrad = 1;
        } இல்லையெனில் {
            gotdig = 1;
            எனில் (c > '9') d = (c|32)+10-'a';
            இல்லையெனில் d = c-'0';
            எனில் (dc<8) {
                x = x*16 + d;
            } இல்லையெனில் எனில் (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } இல்லையெனில் எனில் (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    எனில் (!gotdig) {
        shunget(f);
        எனில் (pok) {
            shunget(f);
            எனில் (gotrad) shunget(f);
        } இல்லையெனில் {
            shlim(f, 0);
        }
        திரும்பு sign * 0.0;
    }
    எனில் (!gotrad) rp = dc;
    போது (dc<8) x *= 16, dc++;
    எனில் ((c|32)=='p') {
        e2 = scanexp(f, pok);
        எனில் (e2 == LLONG_MIN) {
            எனில் (pok) {
                shunget(f);
            } இல்லையெனில் {
                shlim(f, 0);
                திரும்பு 0;
            }
            e2 = 0;
        }
    } இல்லையெனில் {
        shunget(f);
    }
    e2 += 4*rp - 32;

    எனில் (!x) திரும்பு sign * 0.0;
    எனில் (e2 > -emin) {
        errno = ERANGE;
        திரும்பு sign * DBL_MAX * DBL_MAX;
    }
    எனில் (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        திரும்பு sign * DBL_MIN * DBL_MIN;
    }

    போது (x < 0x80000000) {
        எனில் (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } இல்லையெனில் {
            x += x;
            y += y;
        }
        e2--;
    }

    எனில் (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        எனில் (bits<0) bits=0;
    }

    எனில் (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    எனில் (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(இரட்டை)x + sign*y;
    y -= bias;

    எனில் (!y) errno = ERANGE;

    திரும்பு scalbn(y, e2);
}

நிலையான இரட்டை fffloatscan(FFFILE *f, முழு prec, முழு pok)
{
    முழு sign = 1;
    size_t i;
    முழு bits;
    முழு emin;
    முழு c;

    தேர்வு (prec) {
    நிலை 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        நிறுத்து;
    நிலை 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        நிறுத்து;
    நிலை 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        நிறுத்து;
    இயல்பு:
        திரும்பு 0;
    }

    போது (av_isspace((c = shgetc(f))));

    எனில் (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    க்கு (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        எனில் (i<7) c = shgetc(f);
    எனில் (i==3 || i==8 || (i>3 && pok)) {
        எனில் (i!=8) {
            shunget(f);
            எனில் (pok) க்கு (; i>3; i--) shunget(f);
        }
        திரும்பு sign * INFINITY;
    }
    எனில் (!i) க்கு (i=0; i<3 && (c|32)=="nan"[i]; i++)
        எனில் (i<2) c = shgetc(f);
    எனில் (i==3) {
        எனில் (shgetc(f) != '(') {
            shunget(f);
            திரும்பு NAN;
        }
        க்கு (i=1; ; i++) {
            c = shgetc(f);
            எனில் (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                தொடர்;
            எனில் (c==')') திரும்பு NAN;
            shunget(f);
            எனில் (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                திரும்பு 0;
            }
            போது (i--) shunget(f);
            திரும்பு NAN;
        }
    }

    எனில் (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        திரும்பு 0;
    }

    எனில் (c=='0') {
        c = shgetc(f);
        எனில் ((c|32) == 'x')
            திரும்பு hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    திரும்பு decfloat(f, c, bits, emin, sign, pok);
}

நிலையான வெறுமை *arg_n(va_list ap, unsigned முழு n)
{
    வெறுமை *p;
    unsigned முழு i;
    va_list ap2;
    va_copy(ap2, ap);
    க்கு (i=n; i>1; i--) va_arg(ap2, வெறுமை *);
    p = va_arg(ap2, வெறுமை *);
    va_end(ap2);
    திரும்பு p;
}

நிலையான வெறுமை store_int(வெறுமை *dest, முழு size, unsigned long long i)
{
    எனில் (!dest) திரும்பு;
    தேர்வு (size) {
    நிலை SIZE_hh:
        *(எழுத்து *)dest = i;
        நிறுத்து;
    நிலை SIZE_h:
        *(short *)dest = i;
        நிறுத்து;
    நிலை SIZE_def:
        *(முழு *)dest = i;
        நிறுத்து;
    நிலை SIZE_l:
        *(long *)dest = i;
        நிறுத்து;
    நிலை SIZE_ll:
        *(long long *)dest = i;
        நிறுத்து;
    }
}

நிலையான முழு ff_vfscanf(FFFILE *f, மாறிலி எழுத்து *fmt, va_list ap)
{
    முழு width;
    முழு size;
    முழு base;
    மாறிலி unsigned எழுத்து *p;
    முழு c, t;
    எழுத்து *s;
    வெறுமை *dest=வெற்று;
    முழு invert;
    முழு matches=0;
    unsigned long long x;
    இரட்டை y;
    ptrdiff_t pos = 0;
    unsigned எழுத்து scanset[257];
    size_t i;

    க்கு (p=(மாறிலி unsigned எழுத்து *)fmt; *p; p++) {

        எனில் (av_isspace(*p)) {
            போது (av_isspace(p[1])) p++;
            shlim(f, 0);
            போது (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            தொடர்;
        }
        எனில் (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            எனில் (*p == '%') {
                p++;
                போது (av_isspace((c=shgetc(f))));
            } இல்லையெனில் {
                c = shgetc(f);
            }
            எனில் (c!=*p) {
                shunget(f);
                எனில் (c<0) செல் உள்ளீடு_fail;
                செல் match_fail;
            }
            pos += shcnt(f);
            தொடர்;
        }

        p++;
        எனில் (*p=='*') {
            dest = 0; p++;
        } இல்லையெனில் எனில் (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } இல்லையெனில் {
            dest = va_arg(ap, வெறுமை *);
        }

        க்கு (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        எனில் (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        தேர்வு (*p++) {
        நிலை 'h':
            எனில் (*p == 'h') p++, size = SIZE_hh;
            இல்லையெனில் size = SIZE_h;
            நிறுத்து;
        நிலை 'l':
            எனில் (*p == 'l') p++, size = SIZE_ll;
            இல்லையெனில் size = SIZE_l;
            நிறுத்து;
        நிலை 'j':
            size = SIZE_ll;
            நிறுத்து;
        நிலை 'z':
        நிலை 't':
            size = SIZE_l;
            நிறுத்து;
        நிலை 'L':
            size = SIZE_L;
            நிறுத்து;
        நிலை 'd': நிலை 'i': நிலை 'o': நிலை 'u': நிலை 'x':
        நிலை 'a': நிலை 'e': நிலை 'f': நிலை 'g':
        நிலை 'A': நிலை 'E': நிலை 'F': நிலை 'G': நிலை 'X':
        நிலை 's': நிலை 'c': நிலை '[':
        நிலை 'S': நிலை 'C':
        நிலை 'p': நிலை 'n':
            p--;
            நிறுத்து;
        இயல்பு:
            செல் fmt_fail;
        }

        t = *p;

        /* C or S */
        எனில் ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        தேர்வு (t) {
            நிலை 'c':
                எனில் (width < 1) width = 1;
                நிறுத்து;
            நிலை '[':
                நிறுத்து;
            நிலை 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                தொடர்;
            இயல்பு:
                shlim(f, 0);
                போது (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        எனில் (shgetc(f) < 0) செல் உள்ளீடு_fail;
        shunget(f);

        தேர்வு (t) {
            நிலை 's':
            நிலை 'c':
            நிலை '[':
                எனில் (t == 'c' || t == 's') {
                    memset(scanset, -1, அளவு scanset);
                    scanset[0] = 0;
                    எனில் (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } இல்லையெனில் {
                    எனில் (*++p == '^') p++, invert = 1;
                    இல்லையெனில் invert = 0;
                    memset(scanset, invert, அளவு scanset);
                    scanset[0] = 0;
                    எனில் (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    இல்லையெனில் எனில் (*p == ']') p++, scanset[1+']'] = 1-invert;
                    க்கு (; *p != ']'; p++) {
                        எனில் (!*p) செல் fmt_fail;
                        எனில் (*p=='-' && p[1] && p[1] != ']')
                            க்கு (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                எனில் ((s = dest)) {
                    போது (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } இல்லையெனில் {
                    போது (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                எனில் (!shcnt(f)) செல் match_fail;
                எனில் (t == 'c' && shcnt(f) != width) செல் match_fail;
                எனில் (t != 'c') {
                    எனில் (s) s[i] = 0;
                }
                நிறுத்து;
            நிலை 'p':
            நிலை 'X':
            நிலை 'x':
                base = 16;
                செல் int_common;
            நிலை 'o':
                base = 8;
                செல் int_common;
            நிலை 'd':
            நிலை 'u':
                base = 10;
                செல் int_common;
            நிலை 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                எனில் (!shcnt(f))
                    செல் match_fail;
                எனில் (t=='p' && dest)
                    *(வெறுமை **)dest = (வெறுமை *)(uintptr_t)x;
                இல்லையெனில்
                    store_int(dest, size, x);
                நிறுத்து;
            நிலை 'a': நிலை 'A':
            நிலை 'e': நிலை 'E':
            நிலை 'f': நிலை 'F':
            நிலை 'g': நிலை 'G':
                y = fffloatscan(f, size, 0);
                எனில் (!shcnt(f))
                    செல் match_fail;
                எனில் (dest) {
                    தேர்வு (size) {
                    நிலை SIZE_def:
                        *(தசம *)dest = y;
                        நிறுத்து;
                    நிலை SIZE_l:
                        *(இரட்டை *)dest = y;
                        நிறுத்து;
                    நிலை SIZE_L:
                        *(இரட்டை *)dest = y;
                        நிறுத்து;
                    }
                }
                நிறுத்து;
        }

        pos += shcnt(f);
        எனில் (dest) matches++;
    }
    எனில் (0) {
fmt_fail:
உள்ளீடு_fail:
        எனில் (!matches) matches--;
    }
match_fail:
    திரும்பு matches;
}

நிலையான முழு ff_vsscanf(மாறிலி எழுத்து *s, மாறிலி எழுத்து *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (வெறுமை *)s, .cookie = (வெறுமை *)s,
        .பட = ffstring_read,
    };

    திரும்பு ff_vfscanf(&f, fmt, ap);
}

முழு av_sscanf(மாறிலி எழுத்து *string, மாறிலி எழுத்து *format, ...)
{
    முழு ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    திரும்பு ret;
}
