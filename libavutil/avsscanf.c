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

#अन्तर्भाव <errno.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <float.h>

#अन्तर्भाव "avstring.h"

प्रकारनिर्देश संरचना FFFILE {
    size_t buf_size;
    unsigned वर्ण *buf;
    unsigned वर्ण *rpos, *rend;
    unsigned वर्ण *shend;
    ptrdiff_t shlim, shcnt;
    शून्य *cookie;
    size_t (*पठ)(संरचना FFFILE *, unsigned वर्ण *, size_t);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

स्थिर पूर्णाङ्क fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    प्रत्यागम 0;
}

स्थिर size_t ffstring_read(FFFILE *f, unsigned वर्ण *buf, size_t len)
{
    वर्ण *src = f->cookie;
    size_t k = len+256;
    वर्ण *end = memchr(src, 0, k);

    यदि (end) k = end-src;
    यदि (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (शून्य *)(src+len);
    f->rend = (शून्य *)(src+k);
    f->cookie = src+k;

    प्रत्यागम len;
}

स्थिर पूर्णाङ्क ffuflow(FFFILE *f)
{
    unsigned वर्ण c;
    यदि (!fftoread(f) && f->पठ(f, &c, 1)==1) प्रत्यागम c;
    प्रत्यागम EOF;
}

स्थिर शून्य ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    यदि (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    अन्यथा
        f->shend = f->rend;
}

स्थिर पूर्णाङ्क ffshgetc(FFFILE *f)
{
    पूर्णाङ्क c;
    ptrdiff_t cnt = shcnt(f);
    यदि (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        प्रत्यागम EOF;
    }
    cnt++;
    यदि (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    अन्यथा
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    यदि (f->rpos[-1] != c) f->rpos[-1] = c;
    प्रत्यागम c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (शून्य)(f)->rpos-- : (शून्य)0)

स्थिर ध्रुव unsigned वर्ण table[] = { -1,
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

स्थिर unsigned long long ffintscan(FFFILE *f, unsigned base, पूर्णाङ्क pok, unsigned long long lim)
{
    ध्रुव unsigned वर्ण *val = table+1;
    पूर्णाङ्क c, neg=0;
    unsigned x;
    unsigned long long y;
    यदि (base > 36 || base == 1) {
        errno = EINVAL;
        प्रत्यागम 0;
    }
    यावत् (av_isspace((c=shgetc(f))));
    यदि (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    यदि ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        यदि ((c|32)=='x') {
            c = shgetc(f);
            यदि (val[c]>=16) {
                shunget(f);
                यदि (pok) shunget(f);
                अन्यथा shlim(f, 0);
                प्रत्यागम 0;
            }
            base = 16;
        } अन्यथा यदि (base == 0) {
            base = 8;
        }
    } अन्यथा {
        यदि (base == 0) base = 10;
        यदि (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            प्रत्यागम 0;
        }
    }
    यदि (base == 10) {
        प्रति (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        प्रति (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        यदि (c-'0'>=10U) गच्छ done;
    } अन्यथा यदि (!(base & base-1)) {
        पूर्णाङ्क bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        प्रति (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        प्रति (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अन्यथा {
        प्रति (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        प्रति (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    यदि (val[c]<base) {
        प्रति (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        यदि (lim&1) neg = 0;
    }
done:
    shunget(f);
    यदि (y>=lim) {
        यदि (!(lim&1) && !neg) {
            errno = ERANGE;
            प्रत्यागम lim-1;
        } अन्यथा यदि (y>lim) {
            errno = ERANGE;
            प्रत्यागम lim;
        }
    }
    प्रत्यागम (y^neg)-neg;
}

स्थिर long long scanexp(FFFILE *f, पूर्णाङ्क pok)
{
    पूर्णाङ्क c;
    पूर्णाङ्क x;
    long long y;
    पूर्णाङ्क neg = 0;

    c = shgetc(f);
    यदि (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        यदि (c-'0'>=10U && pok) shunget(f);
    }
    यदि (c-'0'>=10U) {
        shunget(f);
        प्रत्यागम LLONG_MIN;
    }
    प्रति (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    प्रति (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    प्रति (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    प्रत्यागम neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

स्थिर द्विगुण decfloat(FFFILE *f, पूर्णाङ्क c, पूर्णाङ्क bits, पूर्णाङ्क emin, पूर्णाङ्क sign, पूर्णाङ्क pok)
{
    uint32_t x[KMAX];
    स्थिर ध्रुव uint32_t th[] = { LD_B1B_MAX };
    पूर्णाङ्क i, j, k, a, z;
    long long lrp=0, dc=0;
    long long e10=0;
    पूर्णाङ्क lnz = 0;
    पूर्णाङ्क gotdig = 0, gotrad = 0;
    पूर्णाङ्क rp;
    पूर्णाङ्क e2;
    पूर्णाङ्क emax = -emin-bits+3;
    पूर्णाङ्क denormal = 0;
    द्विगुण y;
    द्विगुण frac=0;
    द्विगुण bias=0;
    स्थिर ध्रुव पूर्णाङ्क p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    प्रति (; c=='0'; c = shgetc(f)) gotdig=1;
    यदि (c=='.') {
        gotrad = 1;
        प्रति (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    प्रति (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        यदि (c == '.') {
            यदि (gotrad) भङ्ग;
            gotrad = 1;
            lrp = dc;
        } अन्यथा यदि (k < KMAX-3) {
            dc++;
            यदि (c!='0') lnz = dc;
            यदि (j) x[k] = x[k]*10 + c-'0';
            अन्यथा x[k] = c-'0';
            यदि (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } अन्यथा {
            dc++;
            यदि (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    यदि (!gotrad) lrp=dc;

    यदि (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        यदि (e10 == LLONG_MIN) {
            यदि (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                प्रत्यागम 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } अन्यथा यदि (c>=0) {
        shunget(f);
    }
    यदि (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        प्रत्यागम 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    यदि (!x[0]) प्रत्यागम sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    यदि (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        प्रत्यागम sign * (द्विगुण)x[0];
    यदि (lrp > -emin/2) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MAX * DBL_MAX;
    }
    यदि (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    यदि (j) {
        प्रति (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    यदि (lnz<9 && lnz<=rp && rp < 18) {
        पूर्णाङ्क bitlim;
        यदि (rp == 9) प्रत्यागम sign * (द्विगुण)x[0];
        यदि (rp < 9) प्रत्यागम sign * (द्विगुण)x[0] / p10s[8-rp];
        bitlim = bits-3*(पूर्णाङ्क)(rp-9);
        यदि (bitlim>30 || x[0]>>bitlim==0)
            प्रत्यागम sign * (द्विगुण)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    प्रति (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    यदि (rp % 9) {
        पूर्णाङ्क rpm9 = rp>=0 ? rp%9 : rp%9+9;
        पूर्णाङ्क p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        प्रति (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            यदि (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        यदि (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    यावत् (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        प्रति (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            यदि (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अन्यथा {
                carry = 0;
                x[k] = tmp;
            }
            यदि (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            यदि (k==a) भङ्ग;
        }
        यदि (carry) {
            rp += 9;
            a = (a-1 & MASK);
            यदि (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    प्रति (;;) {
        uint32_t carry = 0;
        पूर्णाङ्क sh = 1;
        प्रति (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            यदि (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                भङ्ग;
            }
            यदि (x[a+i & MASK] > th[i]) भङ्ग;
        }
        यदि (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) भङ्ग;
        /* FIXME: find a way to compute optimal sh */
        यदि (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        प्रति (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            यदि (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        यदि (carry) {
            यदि ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } अन्यथा x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    प्रति (y=i=0; i<LD_B1B_DIG; i++) {
        यदि ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    यदि (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        यदि (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    यदि (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    यदि ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        यदि (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        अन्यथा यदि (t > 500000000)
            frac += 0.75*sign;
        अन्यथा यदि (t == 500000000) {
            यदि ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            अन्यथा
                frac += 0.75*sign;
        }
        यदि (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    यदि ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        यदि (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            यदि (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        यदि (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    प्रत्यागम scalbn(y, e2);
}

स्थिर द्विगुण hexfloat(FFFILE *f, पूर्णाङ्क bits, पूर्णाङ्क emin, पूर्णाङ्क sign, पूर्णाङ्क pok)
{
    uint32_t x = 0;
    द्विगुण y = 0;
    द्विगुण scale = 1;
    द्विगुण bias = 0;
    पूर्णाङ्क gottail = 0, gotrad = 0, gotdig = 0;
    long long rp = 0;
    long long dc = 0;
    long long e2 = 0;
    पूर्णाङ्क d;
    पूर्णाङ्क c;

    c = shgetc(f);

    /* Skip leading zeros */
    प्रति (; c=='0'; c = shgetc(f))
        gotdig = 1;

    यदि (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        प्रति (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    प्रति (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        यदि (c=='.') {
            यदि (gotrad) भङ्ग;
            rp = dc;
            gotrad = 1;
        } अन्यथा {
            gotdig = 1;
            यदि (c > '9') d = (c|32)+10-'a';
            अन्यथा d = c-'0';
            यदि (dc<8) {
                x = x*16 + d;
            } अन्यथा यदि (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } अन्यथा यदि (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    यदि (!gotdig) {
        shunget(f);
        यदि (pok) {
            shunget(f);
            यदि (gotrad) shunget(f);
        } अन्यथा {
            shlim(f, 0);
        }
        प्रत्यागम sign * 0.0;
    }
    यदि (!gotrad) rp = dc;
    यावत् (dc<8) x *= 16, dc++;
    यदि ((c|32)=='p') {
        e2 = scanexp(f, pok);
        यदि (e2 == LLONG_MIN) {
            यदि (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                प्रत्यागम 0;
            }
            e2 = 0;
        }
    } अन्यथा {
        shunget(f);
    }
    e2 += 4*rp - 32;

    यदि (!x) प्रत्यागम sign * 0.0;
    यदि (e2 > -emin) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MAX * DBL_MAX;
    }
    यदि (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MIN * DBL_MIN;
    }

    यावत् (x < 0x80000000) {
        यदि (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } अन्यथा {
            x += x;
            y += y;
        }
        e2--;
    }

    यदि (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        यदि (bits<0) bits=0;
    }

    यदि (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    यदि (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुण)x + sign*y;
    y -= bias;

    यदि (!y) errno = ERANGE;

    प्रत्यागम scalbn(y, e2);
}

स्थिर द्विगुण fffloatscan(FFFILE *f, पूर्णाङ्क prec, पूर्णाङ्क pok)
{
    पूर्णाङ्क sign = 1;
    size_t i;
    पूर्णाङ्क bits;
    पूर्णाङ्क emin;
    पूर्णाङ्क c;

    विकल्प (prec) {
    पक्ष 0:
        bits = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-bits;
        भङ्ग;
    पक्ष 1:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        भङ्ग;
    पक्ष 2:
        bits = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-bits;
        भङ्ग;
    स्वभाव:
        प्रत्यागम 0;
    }

    यावत् (av_isspace((c = shgetc(f))));

    यदि (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    प्रति (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        यदि (i<7) c = shgetc(f);
    यदि (i==3 || i==8 || (i>3 && pok)) {
        यदि (i!=8) {
            shunget(f);
            यदि (pok) प्रति (; i>3; i--) shunget(f);
        }
        प्रत्यागम sign * INFINITY;
    }
    यदि (!i) प्रति (i=0; i<3 && (c|32)=="nan"[i]; i++)
        यदि (i<2) c = shgetc(f);
    यदि (i==3) {
        यदि (shgetc(f) != '(') {
            shunget(f);
            प्रत्यागम NAN;
        }
        प्रति (i=1; ; i++) {
            c = shgetc(f);
            यदि (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                अनुवर्त;
            यदि (c==')') प्रत्यागम NAN;
            shunget(f);
            यदि (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                प्रत्यागम 0;
            }
            यावत् (i--) shunget(f);
            प्रत्यागम NAN;
        }
    }

    यदि (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        प्रत्यागम 0;
    }

    यदि (c=='0') {
        c = shgetc(f);
        यदि ((c|32) == 'x')
            प्रत्यागम hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    प्रत्यागम decfloat(f, c, bits, emin, sign, pok);
}

स्थिर शून्य *arg_n(va_list ap, unsigned पूर्णाङ्क n)
{
    शून्य *p;
    unsigned पूर्णाङ्क i;
    va_list ap2;
    va_copy(ap2, ap);
    प्रति (i=n; i>1; i--) va_arg(ap2, शून्य *);
    p = va_arg(ap2, शून्य *);
    va_end(ap2);
    प्रत्यागम p;
}

स्थिर शून्य store_int(शून्य *dest, पूर्णाङ्क size, unsigned long long i)
{
    यदि (!dest) प्रत्यागम;
    विकल्प (size) {
    पक्ष SIZE_hh:
        *(वर्ण *)dest = i;
        भङ्ग;
    पक्ष SIZE_h:
        *(short *)dest = i;
        भङ्ग;
    पक्ष SIZE_def:
        *(पूर्णाङ्क *)dest = i;
        भङ्ग;
    पक्ष SIZE_l:
        *(long *)dest = i;
        भङ्ग;
    पक्ष SIZE_ll:
        *(long long *)dest = i;
        भङ्ग;
    }
}

स्थिर पूर्णाङ्क ff_vfscanf(FFFILE *f, ध्रुव वर्ण *fmt, va_list ap)
{
    पूर्णाङ्क width;
    पूर्णाङ्क size;
    पूर्णाङ्क base;
    ध्रुव unsigned वर्ण *p;
    पूर्णाङ्क c, t;
    वर्ण *s;
    शून्य *dest=रिक्त;
    पूर्णाङ्क invert;
    पूर्णाङ्क matches=0;
    unsigned long long x;
    द्विगुण y;
    ptrdiff_t pos = 0;
    unsigned वर्ण scanset[257];
    size_t i;

    प्रति (p=(ध्रुव unsigned वर्ण *)fmt; *p; p++) {

        यदि (av_isspace(*p)) {
            यावत् (av_isspace(p[1])) p++;
            shlim(f, 0);
            यावत् (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            अनुवर्त;
        }
        यदि (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            यदि (*p == '%') {
                p++;
                यावत् (av_isspace((c=shgetc(f))));
            } अन्यथा {
                c = shgetc(f);
            }
            यदि (c!=*p) {
                shunget(f);
                यदि (c<0) गच्छ निवेश_fail;
                गच्छ match_fail;
            }
            pos += shcnt(f);
            अनुवर्त;
        }

        p++;
        यदि (*p=='*') {
            dest = 0; p++;
        } अन्यथा यदि (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } अन्यथा {
            dest = va_arg(ap, शून्य *);
        }

        प्रति (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        यदि (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        विकल्प (*p++) {
        पक्ष 'h':
            यदि (*p == 'h') p++, size = SIZE_hh;
            अन्यथा size = SIZE_h;
            भङ्ग;
        पक्ष 'l':
            यदि (*p == 'l') p++, size = SIZE_ll;
            अन्यथा size = SIZE_l;
            भङ्ग;
        पक्ष 'j':
            size = SIZE_ll;
            भङ्ग;
        पक्ष 'z':
        पक्ष 't':
            size = SIZE_l;
            भङ्ग;
        पक्ष 'L':
            size = SIZE_L;
            भङ्ग;
        पक्ष 'd': पक्ष 'i': पक्ष 'o': पक्ष 'u': पक्ष 'x':
        पक्ष 'a': पक्ष 'e': पक्ष 'f': पक्ष 'g':
        पक्ष 'A': पक्ष 'E': पक्ष 'F': पक्ष 'G': पक्ष 'X':
        पक्ष 's': पक्ष 'c': पक्ष '[':
        पक्ष 'S': पक्ष 'C':
        पक्ष 'p': पक्ष 'n':
            p--;
            भङ्ग;
        स्वभाव:
            गच्छ fmt_fail;
        }

        t = *p;

        /* C or S */
        यदि ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        विकल्प (t) {
            पक्ष 'c':
                यदि (width < 1) width = 1;
                भङ्ग;
            पक्ष '[':
                भङ्ग;
            पक्ष 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                अनुवर्त;
            स्वभाव:
                shlim(f, 0);
                यावत् (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        यदि (shgetc(f) < 0) गच्छ निवेश_fail;
        shunget(f);

        विकल्प (t) {
            पक्ष 's':
            पक्ष 'c':
            पक्ष '[':
                यदि (t == 'c' || t == 's') {
                    memset(scanset, -1, परिमाण scanset);
                    scanset[0] = 0;
                    यदि (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } अन्यथा {
                    यदि (*++p == '^') p++, invert = 1;
                    अन्यथा invert = 0;
                    memset(scanset, invert, परिमाण scanset);
                    scanset[0] = 0;
                    यदि (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    अन्यथा यदि (*p == ']') p++, scanset[1+']'] = 1-invert;
                    प्रति (; *p != ']'; p++) {
                        यदि (!*p) गच्छ fmt_fail;
                        यदि (*p=='-' && p[1] && p[1] != ']')
                            प्रति (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                यदि ((s = dest)) {
                    यावत् (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } अन्यथा {
                    यावत् (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                यदि (!shcnt(f)) गच्छ match_fail;
                यदि (t == 'c' && shcnt(f) != width) गच्छ match_fail;
                यदि (t != 'c') {
                    यदि (s) s[i] = 0;
                }
                भङ्ग;
            पक्ष 'p':
            पक्ष 'X':
            पक्ष 'x':
                base = 16;
                गच्छ int_common;
            पक्ष 'o':
                base = 8;
                गच्छ int_common;
            पक्ष 'd':
            पक्ष 'u':
                base = 10;
                गच्छ int_common;
            पक्ष 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                यदि (!shcnt(f))
                    गच्छ match_fail;
                यदि (t=='p' && dest)
                    *(शून्य **)dest = (शून्य *)(uintptr_t)x;
                अन्यथा
                    store_int(dest, size, x);
                भङ्ग;
            पक्ष 'a': पक्ष 'A':
            पक्ष 'e': पक्ष 'E':
            पक्ष 'f': पक्ष 'F':
            पक्ष 'g': पक्ष 'G':
                y = fffloatscan(f, size, 0);
                यदि (!shcnt(f))
                    गच्छ match_fail;
                यदि (dest) {
                    विकल्प (size) {
                    पक्ष SIZE_def:
                        *(भिन्न *)dest = y;
                        भङ्ग;
                    पक्ष SIZE_l:
                        *(द्विगुण *)dest = y;
                        भङ्ग;
                    पक्ष SIZE_L:
                        *(द्विगुण *)dest = y;
                        भङ्ग;
                    }
                }
                भङ्ग;
        }

        pos += shcnt(f);
        यदि (dest) matches++;
    }
    यदि (0) {
fmt_fail:
निवेश_fail:
        यदि (!matches) matches--;
    }
match_fail:
    प्रत्यागम matches;
}

स्थिर पूर्णाङ्क ff_vsscanf(ध्रुव वर्ण *s, ध्रुव वर्ण *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (शून्य *)s, .cookie = (शून्य *)s,
        .पठ = ffstring_read,
    };

    प्रत्यागम ff_vfscanf(&f, fmt, ap);
}

पूर्णाङ्क av_sscanf(ध्रुव वर्ण *string, ध्रुव वर्ण *format, ...)
{
    पूर्णाङ्क ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    प्रत्यागम ret;
}
