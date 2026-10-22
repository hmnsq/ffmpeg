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

#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <math.h>
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <float.h>

#અન્તર્ભાવ "avstring.h"

પ્રકારવ્યાખ્યા સંરચના FFFILE {
    size_t buf_size;
    unsigned અક્ષર *buf;
    unsigned અક્ષર *rpos, *rend;
    unsigned અક્ષર *shend;
    ptrdiff_t shlim, shcnt;
    શૂન્ય *cookie;
    size_t (*પઠ)(સંરચના FFFILE *, unsigned અક્ષર *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

સ્થિર પૂર્ણાંક fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    પાછા 0;
}

સ્થિર size_t ffstring_read(FFFILE *f, unsigned અક્ષર *buf, size_t len)
{
    અક્ષર *src = f->cookie;
    size_t k = len+256;
    અક્ષર *end = memchr(src, 0, k);

    જો (end) k = end-src;
    જો (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (શૂન્ય *)(src+len);
    f->rend = (શૂન્ય *)(src+k);
    f->cookie = src+k;

    પાછા len;
}

સ્થિર પૂર્ણાંક ffuflow(FFFILE *f)
{
    unsigned અક્ષર c;
    જો (!fftoread(f) && f->પઠ(f, &c, 1)==1) પાછા c;
    પાછા EOF;
}

સ્થિર શૂન્ય ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    જો (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    નહીંતર
        f->shend = f->rend;
}

સ્થિર પૂર્ણાંક ffshgetc(FFFILE *f)
{
    પૂર્ણાંક c;
    ptrdiff_t cnt = shcnt(f);
    જો (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        પાછા EOF;
    }
    cnt++;
    જો (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    નહીંતર
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    જો (f->rpos[-1] != c) f->rpos[-1] = c;
    પાછા c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (શૂન્ય)(f)->rpos-- : (શૂન્ય)0)

સ્થિર અચલ unsigned અક્ષર table[] = { -1,
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

સ્થિર unsigned long long ffintscan(FFFILE *f, unsigned base, પૂર્ણાંક pok, unsigned long long lim)
{
    અચલ unsigned અક્ષર *val = table+1;
    પૂર્ણાંક c, neg=0;
    unsigned x;
    unsigned long long y;
    જો (base > 36 || base == 1) {
        errno = EINVAL;
        પાછા 0;
    }
    જ્યારે (av_isspace((c=shgetc(f))));
    જો (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    જો ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        જો ((c|32)=='x') {
            c = shgetc(f);
            જો (val[c]>=16) {
                shunget(f);
                જો (pok) shunget(f);
                નહીંતર shlim(f, 0);
                પાછા 0;
            }
            base = 16;
        } નહીંતર જો (base == 0) {
            base = 8;
        }
    } નહીંતર {
        જો (base == 0) base = 10;
        જો (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            પાછા 0;
        }
    }
    જો (base == 10) {
        માટે (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        માટે (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        જો (c-'0'>=10U) જાઓ done;
    } નહીંતર જો (!(base & base-1)) {
        પૂર્ણાંક bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        માટે (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        માટે (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } નહીંતર {
        માટે (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        માટે (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    જો (val[c]<base) {
        માટે (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        જો (lim&1) neg = 0;
    }
done:
    shunget(f);
    જો (y>=lim) {
        જો (!(lim&1) && !neg) {
            errno = ERANGE;
            પાછા lim-1;
        } નહીંતર જો (y>lim) {
            errno = ERANGE;
            પાછા lim;
        }
    }
    પાછા (y^neg)-neg;
}

સ્થિર long long scanexp(FFFILE *f, પૂર્ણાંક pok)
{
    પૂર્ણાંક c;
    પૂર્ણાંક x;
    long long y;
    પૂર્ણાંક neg = 0;

    c = shgetc(f);
    જો (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        જો (c-'0'>=10U && pok) shunget(f);
    }
    જો (c-'0'>=10U) {
        shunget(f);
        પાછા LLONG_MIN;
    }
    માટે (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    માટે (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    માટે (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    પાછા neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

સ્થિર દ્વિગુણ decfloat(FFFILE *f, પૂર્ણાંક c, પૂર્ણાંક bits, પૂર્ણાંક emin, પૂર્ણાંક sign, પૂર્ણાંક pok)
{
    uint32_t x[KMAX];
    સ્થિર અચલ uint32_t th[] = { LD_B1B_MAX };
    પૂર્ણાંક i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    પૂર્ણાંક lnz = 0;
    પૂર્ણાંક gotdig = 0, gotrad = 0;
    પૂર્ણાંક rp;
    પૂર્ણાંક e2;
    પૂર્ણાંક emax = -emin-bits+3;
    પૂર્ણાંક denormal = 0;
    દ્વિગુણ y;
    દ્વિગુણ frac=0;
    દ્વિગુણ bias=0;
    સ્થિર અચલ પૂર્ણાંક p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    માટે (; c=='0'; c = shgetc(f)) gotdig=1;
    જો (c=='.') {
        gotrad = 1;
        માટે (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    માટે (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        જો (c == '.') {
            જો (gotrad) તોડો;
            gotrad = 1;
            lrp = dc;
        } નહીંતર જો (k < KMAX-3) {
            dc++;
            જો (c!='0') lnz = dc;
            જો (j) x[k] = x[k]*10 + c-'0';
            નહીંતર x[k] = c-'0';
            જો (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } નહીંતર {
            dc++;
            જો (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    જો (!gotrad) lrp=dc;

    જો (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        જો (e10 == LLONG_MIN) {
            જો (pok) {
                shunget(f);
            } નહીંતર {
                shlim(f, 0);
                પાછા 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } નહીંતર જો (c>=0) {
        shunget(f);
    }
    જો (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        પાછા 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    જો (!x[0]) પાછા sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    જો (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        પાછા sign * (દ્વિગુણ)x[0];
    જો (lrp > -emin/2) {
        errno = ERANGE;
        પાછા sign * DBL_MAX * DBL_MAX;
    }
    જો (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        પાછા sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    જો (j) {
        માટે (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    જો (lnz<9 && lnz<=rp && rp < 18) {
        પૂર્ણાંક bitlim;
        જો (rp == 9) પાછા sign * (દ્વિગુણ)x[0];
        જો (rp < 9) પાછા sign * (દ્વિગુણ)x[0] / p10s[8-rp];
        bitlim = bits-3*(પૂર્ણાંક)(rp-9);
        જો (bitlim>30 || x[0]>>bitlim==0)
            પાછા sign * (દ્વિગુણ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    માટે (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    જો (rp % 9) {
        પૂર્ણાંક rpm9 = rp>=0 ? rp%9 : rp%9+9;
        પૂર્ણાંક p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        માટે (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            જો (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        જો (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    જ્યારે (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        માટે (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            જો (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } નહીંતર {
                carry = 0;
                x[k] = tmp;
            }
            જો (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            જો (k==a) તોડો;
        }
        જો (carry) {
            rp += 9;
            a = (a-1 & MASK);
            જો (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    માટે (;;) {
        uint32_t carry = 0;
        પૂર્ણાંક sh = 1;
        માટે (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            જો (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                તોડો;
            }
            જો (x[a+i & MASK] > th[i]) તોડો;
        }
        જો (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) તોડો;
        /* FIXME: find a way to compute optimal sh */
        જો (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        માટે (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            જો (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        જો (carry) {
            જો ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } નહીંતર x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    માટે (y=i=0; i<LD_B1B_DIG; i++) {
        જો ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    જો (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        જો (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    જો (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    જો ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        જો (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        નહીંતર જો (t > 500000000)
            frac += 0.75*sign;
        નહીંતર જો (t == 500000000) {
            જો ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            નહીંતર
                frac += 0.75*sign;
        }
        જો (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    જો ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        જો (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            જો (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        જો (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    પાછા scalbn(y, e2);
}

સ્થિર દ્વિગુણ hexfloat(FFFILE *f, પૂર્ણાંક bits, પૂર્ણાંક emin, પૂર્ણાંક sign, પૂર્ણાંક pok)
{
    uint32_t x = 0;
    દ્વિગુણ y = 0;
    દ્વિગુણ scale = 1;
    દ્વિગુણ bias = 0;
    પૂર્ણાંક gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    પૂર્ણાંક d;
    પૂર્ણાંક c;

    c = shgetc(f);

    /* Skip leading zeros */
    માટે (; c=='0'; c = shgetc(f))
        gotdig = 1;

    જો (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        માટે (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    માટે (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        જો (c=='.') {
            જો (gotrad) તોડો;
            rp = dc;
            gotrad = 1;
        } નહીંતર {
            gotdig = 1;
            જો (c > '9') d = (c|32)+10-'a';
            નહીંતર d = c-'0';
            જો (dc<8) {
                x = x*16 + d;
            } નહીંતર જો (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } નહીંતર જો (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    જો (!gotdig) {
        shunget(f);
        જો (pok) {
            shunget(f);
            જો (gotrad) shunget(f);
        } નહીંતર {
            shlim(f, 0);
        }
        પાછા sign * 0.0;
    }
    જો (!gotrad) rp = dc;
    જ્યારે (dc<8) x *= 16, dc++;
    જો ((c|32)=='p') {
        e2 = scanexp(f, pok);
        જો (e2 == LLONG_MIN) {
            જો (pok) {
                shunget(f);
            } નહીંતર {
                shlim(f, 0);
                પાછા 0;
            }
            e2 = 0;
        }
    } નહીંતર {
        shunget(f);
    }
    e2 += 4*rp - 32;

    જો (!x) પાછા sign * 0.0;
    જો (e2 > -emin) {
        errno = ERANGE;
        પાછા sign * DBL_MAX * DBL_MAX;
    }
    જો (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        પાછા sign * DBL_MIN * DBL_MIN;
    }

    જ્યારે (x < 0x80000000) {
        જો (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } નહીંતર {
            x += x;
            y += y;
        }
        e2--;
    }

    જો (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        જો (bits<0) bits=0;
    }

    જો (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    જો (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(દ્વિગુણ)x + sign*y;
    y -= bias;

    જો (!y) errno = ERANGE;

    પાછા scalbn(y, e2);
}

સ્થિર દ્વિગુણ fffloatscan(FFFILE *f, પૂર્ણાંક prec, પૂર્ણાંક pok)
{
    પૂર્ણાંક sign = 1;
    size_t i;
    પૂર્ણાંક bits;
    પૂર્ણાંક emin;
    પૂર્ણાંક c;

    પસંદગી (prec) {
    સ્થિતિ 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        તોડો;
    સ્થિતિ 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        તોડો;
    સ્થિતિ 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        તોડો;
    મૂળભૂત:
        પાછા 0;
    }

    જ્યારે (av_isspace((c = shgetc(f))));

    જો (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    માટે (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        જો (i<7) c = shgetc(f);
    જો (i==3 || i==8 || (i>3 && pok)) {
        જો (i!=8) {
            shunget(f);
            જો (pok) માટે (; i>3; i--) shunget(f);
        }
        પાછા sign * INFINITY;
    }
    જો (!i) માટે (i=0; i<3 && (c|32)=="nan"[i]; i++)
        જો (i<2) c = shgetc(f);
    જો (i==3) {
        જો (shgetc(f) != '(') {
            shunget(f);
            પાછા NAN;
        }
        માટે (i=1; ; i++) {
            c = shgetc(f);
            જો (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ચાલુ;
            જો (c==')') પાછા NAN;
            shunget(f);
            જો (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                પાછા 0;
            }
            જ્યારે (i--) shunget(f);
            પાછા NAN;
        }
    }

    જો (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        પાછા 0;
    }

    જો (c=='0') {
        c = shgetc(f);
        જો ((c|32) == 'x')
            પાછા hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    પાછા decfloat(f, c, bits, emin, sign, pok);
}

સ્થિર શૂન્ય *arg_n(va_list ap, unsigned પૂર્ણાંક n)
{
    શૂન્ય *p;
    unsigned પૂર્ણાંક i;
    va_list ap2;
    va_copy(ap2, ap);
    માટે (i=n; i>1; i--) va_arg(ap2, શૂન્ય *);
    p = va_arg(ap2, શૂન્ય *);
    va_end(ap2);
    પાછા p;
}

સ્થિર શૂન્ય store_int(શૂન્ય *dest, પૂર્ણાંક size, unsigned long long i)
{
    જો (!dest) પાછા;
    પસંદગી (size) {
    સ્થિતિ SIZE_hh:
        *(અક્ષર *)dest = i;
        તોડો;
    સ્થિતિ SIZE_h:
        *(short *)dest = i;
        તોડો;
    સ્થિતિ SIZE_def:
        *(પૂર્ણાંક *)dest = i;
        તોડો;
    સ્થિતિ SIZE_l:
        *(long *)dest = i;
        તોડો;
    સ્થિતિ SIZE_ll:
        *(long long *)dest = i;
        તોડો;
    }
}

સ્થિર પૂર્ણાંક ff_vfscanf(FFFILE *f, અચલ અક્ષર *fmt, va_list ap)
{
    પૂર્ણાંક width;
    પૂર્ણાંક size;
    પૂર્ણાંક base;
    અચલ unsigned અક્ષર *p;
    પૂર્ણાંક c, t;
    અક્ષર *s;
    શૂન્ય *dest=ખાલી;
    પૂર્ણાંક invert;
    પૂર્ણાંક matches=0;
    unsigned long long x;
    દ્વિગુણ y;
    ptrdiff_t pos = 0;
    unsigned અક્ષર scanset[257];
    size_t i;

    માટે (p=(અચલ unsigned અક્ષર *)fmt; *p; p++) {

        જો (av_isspace(*p)) {
            જ્યારે (av_isspace(p[1])) p++;
            shlim(f, 0);
            જ્યારે (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ચાલુ;
        }
        જો (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            જો (*p == '%') {
                p++;
                જ્યારે (av_isspace((c=shgetc(f))));
            } નહીંતર {
                c = shgetc(f);
            }
            જો (c!=*p) {
                shunget(f);
                જો (c<0) જાઓ આગત_fail;
                જાઓ match_fail;
            }
            pos += shcnt(f);
            ચાલુ;
        }

        p++;
        જો (*p=='*') {
            dest = 0; p++;
        } નહીંતર જો (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } નહીંતર {
            dest = va_arg(ap, શૂન્ય *);
        }

        માટે (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        જો (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        પસંદગી (*p++) {
        સ્થિતિ 'h':
            જો (*p == 'h') p++, size = SIZE_hh;
            નહીંતર size = SIZE_h;
            તોડો;
        સ્થિતિ 'l':
            જો (*p == 'l') p++, size = SIZE_ll;
            નહીંતર size = SIZE_l;
            તોડો;
        સ્થિતિ 'j':
            size = SIZE_ll;
            તોડો;
        સ્થિતિ 'z':
        સ્થિતિ 't':
            size = SIZE_l;
            તોડો;
        સ્થિતિ 'L':
            size = SIZE_L;
            તોડો;
        સ્થિતિ 'd': સ્થિતિ 'i': સ્થિતિ 'o': સ્થિતિ 'u': સ્થિતિ 'x':
        સ્થિતિ 'a': સ્થિતિ 'e': સ્થિતિ 'f': સ્થિતિ 'g':
        સ્થિતિ 'A': સ્થિતિ 'E': સ્થિતિ 'F': સ્થિતિ 'G': સ્થિતિ 'X':
        સ્થિતિ 's': સ્થિતિ 'c': સ્થિતિ '[':
        સ્થિતિ 'S': સ્થિતિ 'C':
        સ્થિતિ 'p': સ્થિતિ 'n':
            p--;
            તોડો;
        મૂળભૂત:
            જાઓ fmt_fail;
        }

        t = *p;

        /* C or S */
        જો ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        પસંદગી (t) {
            સ્થિતિ 'c':
                જો (width < 1) width = 1;
                તોડો;
            સ્થિતિ '[':
                તોડો;
            સ્થિતિ 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                ચાલુ;
            મૂળભૂત:
                shlim(f, 0);
                જ્યારે (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        જો (shgetc(f) < 0) જાઓ આગત_fail;
        shunget(f);

        પસંદગી (t) {
            સ્થિતિ 's':
            સ્થિતિ 'c':
            સ્થિતિ '[':
                જો (t == 'c' || t == 's') {
                    memset(scanset, -1, કદ scanset);
                    scanset[0] = 0;
                    જો (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } નહીંતર {
                    જો (*++p == '^') p++, invert = 1;
                    નહીંતર invert = 0;
                    memset(scanset, invert, કદ scanset);
                    scanset[0] = 0;
                    જો (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    નહીંતર જો (*p == ']') p++, scanset[1+']'] = 1-invert;
                    માટે (; *p != ']'; p++) {
                        જો (!*p) જાઓ fmt_fail;
                        જો (*p=='-' && p[1] && p[1] != ']')
                            માટે (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                જો ((s = dest)) {
                    જ્યારે (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } નહીંતર {
                    જ્યારે (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                જો (!shcnt(f)) જાઓ match_fail;
                જો (t == 'c' && shcnt(f) != width) જાઓ match_fail;
                જો (t != 'c') {
                    જો (s) s[i] = 0;
                }
                તોડો;
            સ્થિતિ 'p':
            સ્થિતિ 'X':
            સ્થિતિ 'x':
                base = 16;
                જાઓ int_common;
            સ્થિતિ 'o':
                base = 8;
                જાઓ int_common;
            સ્થિતિ 'd':
            સ્થિતિ 'u':
                base = 10;
                જાઓ int_common;
            સ્થિતિ 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                જો (!shcnt(f))
                    જાઓ match_fail;
                જો (t=='p' && dest)
                    *(શૂન્ય **)dest = (શૂન્ય *)(uintptr_t)x;
                નહીંતર
                    store_int(dest, size, x);
                તોડો;
            સ્થિતિ 'a': સ્થિતિ 'A':
            સ્થિતિ 'e': સ્થિતિ 'E':
            સ્થિતિ 'f': સ્થિતિ 'F':
            સ્થિતિ 'g': સ્થિતિ 'G':
                y = fffloatscan(f, size, 0);
                જો (!shcnt(f))
                    જાઓ match_fail;
                જો (dest) {
                    પસંદગી (size) {
                    સ્થિતિ SIZE_def:
                        *(દશાંશ *)dest = y;
                        તોડો;
                    સ્થિતિ SIZE_l:
                        *(દ્વિગુણ *)dest = y;
                        તોડો;
                    સ્થિતિ SIZE_L:
                        *(દ્વિગુણ *)dest = y;
                        તોડો;
                    }
                }
                તોડો;
        }

        pos += shcnt(f);
        જો (dest) matches++;
    }
    જો (0) {
fmt_fail:
આગત_fail:
        જો (!matches) matches--;
    }
match_fail:
    પાછા matches;
}

સ્થિર પૂર્ણાંક ff_vsscanf(અચલ અક્ષર *s, અચલ અક્ષર *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (શૂન્ય *)s, .cookie = (શૂન્ય *)s,
        .પઠ = ffstring_read,
    };

    પાછા ff_vfscanf(&f, fmt, ap);
}

પૂર્ણાંક av_sscanf(અચલ અક્ષર *string, અચલ અક્ષર *format, ...)
{
    પૂર્ણાંક ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    પાછા ret;
}
