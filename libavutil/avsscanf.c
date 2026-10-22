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

    जइ (end) k = end-src;
    जइ (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (शून्य *)(src+len);
    f->rend = (शून्य *)(src+k);
    f->cookie = src+k;

    प्रत्यागम len;
}

स्थिर पूर्णाङ्क ffuflow(FFFILE *f)
{
    unsigned वर्ण c;
    जइ (!fftoread(f) && f->पठ(f, &c, 1)==1) प्रत्यागम c;
    प्रत्यागम EOF;
}

स्थिर शून्य ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    जइ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    अण्णहा
        f->shend = f->rend;
}

स्थिर पूर्णाङ्क ffshgetc(FFFILE *f)
{
    पूर्णाङ्क c;
    ptrdiff_t cnt = shcnt(f);
    जइ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        प्रत्यागम EOF;
    }
    cnt++;
    जइ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    अण्णहा
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    जइ (f->rpos[-1] != c) f->rpos[-1] = c;
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
    जइ (base > 36 || base == 1) {
        errno = EINVAL;
        प्रत्यागम 0;
    }
    जाव (av_isspace((c=shgetc(f))));
    जइ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    जइ ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        जइ ((c|32)=='x') {
            c = shgetc(f);
            जइ (val[c]>=16) {
                shunget(f);
                जइ (pok) shunget(f);
                अण्णहा shlim(f, 0);
                प्रत्यागम 0;
            }
            base = 16;
        } अण्णहा जइ (base == 0) {
            base = 8;
        }
    } अण्णहा {
        जइ (base == 0) base = 10;
        जइ (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            प्रत्यागम 0;
        }
    }
    जइ (base == 10) {
        प्रति (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        प्रति (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        जइ (c-'0'>=10U) गच्छ done;
    } अण्णहा जइ (!(base & base-1)) {
        पूर्णाङ्क bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        प्रति (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        प्रति (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अण्णहा {
        प्रति (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        प्रति (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    जइ (val[c]<base) {
        प्रति (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        जइ (lim&1) neg = 0;
    }
done:
    shunget(f);
    जइ (y>=lim) {
        जइ (!(lim&1) && !neg) {
            errno = ERANGE;
            प्रत्यागम lim-1;
        } अण्णहा जइ (y>lim) {
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
    जइ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        जइ (c-'0'>=10U && pok) shunget(f);
    }
    जइ (c-'0'>=10U) {
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
    जइ (c=='.') {
        gotrad = 1;
        प्रति (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    प्रति (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        जइ (c == '.') {
            जइ (gotrad) भङ्ग;
            gotrad = 1;
            lrp = dc;
        } अण्णहा जइ (k < KMAX-3) {
            dc++;
            जइ (c!='0') lnz = dc;
            जइ (j) x[k] = x[k]*10 + c-'0';
            अण्णहा x[k] = c-'0';
            जइ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } अण्णहा {
            dc++;
            जइ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    जइ (!gotrad) lrp=dc;

    जइ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        जइ (e10 == LLONG_MIN) {
            जइ (pok) {
                shunget(f);
            } अण्णहा {
                shlim(f, 0);
                प्रत्यागम 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } अण्णहा जइ (c>=0) {
        shunget(f);
    }
    जइ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        प्रत्यागम 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    जइ (!x[0]) प्रत्यागम sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    जइ (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        प्रत्यागम sign * (द्विगुण)x[0];
    जइ (lrp > -emin/2) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MAX * DBL_MAX;
    }
    जइ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    जइ (j) {
        प्रति (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    जइ (lnz<9 && lnz<=rp && rp < 18) {
        पूर्णाङ्क bitlim;
        जइ (rp == 9) प्रत्यागम sign * (द्विगुण)x[0];
        जइ (rp < 9) प्रत्यागम sign * (द्विगुण)x[0] / p10s[8-rp];
        bitlim = bits-3*(पूर्णाङ्क)(rp-9);
        जइ (bitlim>30 || x[0]>>bitlim==0)
            प्रत्यागम sign * (द्विगुण)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    प्रति (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    जइ (rp % 9) {
        पूर्णाङ्क rpm9 = rp>=0 ? rp%9 : rp%9+9;
        पूर्णाङ्क p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        प्रति (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            जइ (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        जइ (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    जाव (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        प्रति (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            जइ (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अण्णहा {
                carry = 0;
                x[k] = tmp;
            }
            जइ (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            जइ (k==a) भङ्ग;
        }
        जइ (carry) {
            rp += 9;
            a = (a-1 & MASK);
            जइ (a == z) {
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
            जइ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                भङ्ग;
            }
            जइ (x[a+i & MASK] > th[i]) भङ्ग;
        }
        जइ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) भङ्ग;
        /* FIXME: find a way to compute optimal sh */
        जइ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        प्रति (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            जइ (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        जइ (carry) {
            जइ ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } अण्णहा x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    प्रति (y=i=0; i<LD_B1B_DIG; i++) {
        जइ ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    जइ (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        जइ (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    जइ (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    जइ ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        जइ (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        अण्णहा जइ (t > 500000000)
            frac += 0.75*sign;
        अण्णहा जइ (t == 500000000) {
            जइ ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            अण्णहा
                frac += 0.75*sign;
        }
        जइ (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    जइ ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        जइ (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            जइ (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        जइ (e2+DBL_MANT_DIG>emax || (denormal && frac))
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

    जइ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        प्रति (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    प्रति (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        जइ (c=='.') {
            जइ (gotrad) भङ्ग;
            rp = dc;
            gotrad = 1;
        } अण्णहा {
            gotdig = 1;
            जइ (c > '9') d = (c|32)+10-'a';
            अण्णहा d = c-'0';
            जइ (dc<8) {
                x = x*16 + d;
            } अण्णहा जइ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } अण्णहा जइ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    जइ (!gotdig) {
        shunget(f);
        जइ (pok) {
            shunget(f);
            जइ (gotrad) shunget(f);
        } अण्णहा {
            shlim(f, 0);
        }
        प्रत्यागम sign * 0.0;
    }
    जइ (!gotrad) rp = dc;
    जाव (dc<8) x *= 16, dc++;
    जइ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        जइ (e2 == LLONG_MIN) {
            जइ (pok) {
                shunget(f);
            } अण्णहा {
                shlim(f, 0);
                प्रत्यागम 0;
            }
            e2 = 0;
        }
    } अण्णहा {
        shunget(f);
    }
    e2 += 4*rp - 32;

    जइ (!x) प्रत्यागम sign * 0.0;
    जइ (e2 > -emin) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MAX * DBL_MAX;
    }
    जइ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        प्रत्यागम sign * DBL_MIN * DBL_MIN;
    }

    जाव (x < 0x80000000) {
        जइ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } अण्णहा {
            x += x;
            y += y;
        }
        e2--;
    }

    जइ (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        जइ (bits<0) bits=0;
    }

    जइ (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    जइ (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुण)x + sign*y;
    y -= bias;

    जइ (!y) errno = ERANGE;

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

    जाव (av_isspace((c = shgetc(f))));

    जइ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    प्रति (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        जइ (i<7) c = shgetc(f);
    जइ (i==3 || i==8 || (i>3 && pok)) {
        जइ (i!=8) {
            shunget(f);
            जइ (pok) प्रति (; i>3; i--) shunget(f);
        }
        प्रत्यागम sign * INFINITY;
    }
    जइ (!i) प्रति (i=0; i<3 && (c|32)=="nan"[i]; i++)
        जइ (i<2) c = shgetc(f);
    जइ (i==3) {
        जइ (shgetc(f) != '(') {
            shunget(f);
            प्रत्यागम NAN;
        }
        प्रति (i=1; ; i++) {
            c = shgetc(f);
            जइ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                अनुवर्त;
            जइ (c==')') प्रत्यागम NAN;
            shunget(f);
            जइ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                प्रत्यागम 0;
            }
            जाव (i--) shunget(f);
            प्रत्यागम NAN;
        }
    }

    जइ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        प्रत्यागम 0;
    }

    जइ (c=='0') {
        c = shgetc(f);
        जइ ((c|32) == 'x')
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
    जइ (!dest) प्रत्यागम;
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

        जइ (av_isspace(*p)) {
            जाव (av_isspace(p[1])) p++;
            shlim(f, 0);
            जाव (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            अनुवर्त;
        }
        जइ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            जइ (*p == '%') {
                p++;
                जाव (av_isspace((c=shgetc(f))));
            } अण्णहा {
                c = shgetc(f);
            }
            जइ (c!=*p) {
                shunget(f);
                जइ (c<0) गच्छ निवेशः_fail;
                गच्छ match_fail;
            }
            pos += shcnt(f);
            अनुवर्त;
        }

        p++;
        जइ (*p=='*') {
            dest = 0; p++;
        } अण्णहा जइ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } अण्णहा {
            dest = va_arg(ap, शून्य *);
        }

        प्रति (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        जइ (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        विकल्प (*p++) {
        पक्ष 'h':
            जइ (*p == 'h') p++, size = SIZE_hh;
            अण्णहा size = SIZE_h;
            भङ्ग;
        पक्ष 'l':
            जइ (*p == 'l') p++, size = SIZE_ll;
            अण्णहा size = SIZE_l;
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
        जइ ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        विकल्प (t) {
            पक्ष 'c':
                जइ (width < 1) width = 1;
                भङ्ग;
            पक्ष '[':
                भङ्ग;
            पक्ष 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                अनुवर्त;
            स्वभाव:
                shlim(f, 0);
                जाव (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        जइ (shgetc(f) < 0) गच्छ निवेशः_fail;
        shunget(f);

        विकल्प (t) {
            पक्ष 's':
            पक्ष 'c':
            पक्ष '[':
                जइ (t == 'c' || t == 's') {
                    memset(scanset, -1, परिमाण scanset);
                    scanset[0] = 0;
                    जइ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } अण्णहा {
                    जइ (*++p == '^') p++, invert = 1;
                    अण्णहा invert = 0;
                    memset(scanset, invert, परिमाण scanset);
                    scanset[0] = 0;
                    जइ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    अण्णहा जइ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    प्रति (; *p != ']'; p++) {
                        जइ (!*p) गच्छ fmt_fail;
                        जइ (*p=='-' && p[1] && p[1] != ']')
                            प्रति (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                जइ ((s = dest)) {
                    जाव (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } अण्णहा {
                    जाव (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                जइ (!shcnt(f)) गच्छ match_fail;
                जइ (t == 'c' && shcnt(f) != width) गच्छ match_fail;
                जइ (t != 'c') {
                    जइ (s) s[i] = 0;
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
                जइ (!shcnt(f))
                    गच्छ match_fail;
                जइ (t=='p' && dest)
                    *(शून्य **)dest = (शून्य *)(uintptr_t)x;
                अण्णहा
                    store_int(dest, size, x);
                भङ्ग;
            पक्ष 'a': पक्ष 'A':
            पक्ष 'e': पक्ष 'E':
            पक्ष 'f': पक्ष 'F':
            पक्ष 'g': पक्ष 'G':
                y = fffloatscan(f, size, 0);
                जइ (!shcnt(f))
                    गच्छ match_fail;
                जइ (dest) {
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
        जइ (dest) matches++;
    }
    जइ (0) {
fmt_fail:
निवेशः_fail:
        जइ (!matches) matches--;
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
