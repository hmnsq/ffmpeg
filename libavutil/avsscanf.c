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
    पटिनिवत्त 0;
}

स्थिर size_t ffstring_read(FFFILE *f, unsigned वर्ण *buf, size_t len)
{
    वर्ण *src = f->cookie;
    size_t k = len+256;
    वर्ण *end = memchr(src, 0, k);

    सचे (end) k = end-src;
    सचे (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (शून्य *)(src+len);
    f->rend = (शून्य *)(src+k);
    f->cookie = src+k;

    पटिनिवत्त len;
}

स्थिर पूर्णाङ्क ffuflow(FFFILE *f)
{
    unsigned वर्ण c;
    सचे (!fftoread(f) && f->पठ(f, &c, 1)==1) पटिनिवत्त c;
    पटिनिवत्त EOF;
}

स्थिर शून्य ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    सचे (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    अञ्ञथा
        f->shend = f->rend;
}

स्थिर पूर्णाङ्क ffshgetc(FFFILE *f)
{
    पूर्णाङ्क c;
    ptrdiff_t cnt = shcnt(f);
    सचे (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        पटिनिवत्त EOF;
    }
    cnt++;
    सचे (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    अञ्ञथा
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    सचे (f->rpos[-1] != c) f->rpos[-1] = c;
    पटिनिवत्त c;
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
    सचे (base > 36 || base == 1) {
        errno = EINVAL;
        पटिनिवत्त 0;
    }
    याव (av_isspace((c=shgetc(f))));
    सचे (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    सचे ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        सचे ((c|32)=='x') {
            c = shgetc(f);
            सचे (val[c]>=16) {
                shunget(f);
                सचे (pok) shunget(f);
                अञ्ञथा shlim(f, 0);
                पटिनिवत्त 0;
            }
            base = 16;
        } अञ्ञथा सचे (base == 0) {
            base = 8;
        }
    } अञ्ञथा {
        सचे (base == 0) base = 10;
        सचे (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            पटिनिवत्त 0;
        }
    }
    सचे (base == 10) {
        अत्थाय (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        अत्थाय (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        सचे (c-'0'>=10U) गच्छ done;
    } अञ्ञथा सचे (!(base & base-1)) {
        पूर्णाङ्क bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        अत्थाय (x=0; val[c]<base && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        अत्थाय (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अञ्ञथा {
        अत्थाय (x=0; val[c]<base && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*base + val[c];
        अत्थाय (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    सचे (val[c]<base) {
        अत्थाय (; val[c]<base; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        सचे (lim&1) neg = 0;
    }
done:
    shunget(f);
    सचे (y>=lim) {
        सचे (!(lim&1) && !neg) {
            errno = ERANGE;
            पटिनिवत्त lim-1;
        } अञ्ञथा सचे (y>lim) {
            errno = ERANGE;
            पटिनिवत्त lim;
        }
    }
    पटिनिवत्त (y^neg)-neg;
}

स्थिर long long scanexp(FFFILE *f, पूर्णाङ्क pok)
{
    पूर्णाङ्क c;
    पूर्णाङ्क x;
    long long y;
    पूर्णाङ्क neg = 0;

    c = shgetc(f);
    सचे (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        सचे (c-'0'>=10U && pok) shunget(f);
    }
    सचे (c-'0'>=10U) {
        shunget(f);
        पटिनिवत्त LLONG_MIN;
    }
    अत्थाय (x=0; c-'0'<10U && x<INT_MAX/10; c = shgetc(f))
        x = 10*x + (c-'0');
    अत्थाय (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    अत्थाय (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    पटिनिवत्त neg ? -y : y;
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
    अत्थाय (; c=='0'; c = shgetc(f)) gotdig=1;
    सचे (c=='.') {
        gotrad = 1;
        अत्थाय (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    अत्थाय (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        सचे (c == '.') {
            सचे (gotrad) भङ्ग;
            gotrad = 1;
            lrp = dc;
        } अञ्ञथा सचे (k < KMAX-3) {
            dc++;
            सचे (c!='0') lnz = dc;
            सचे (j) x[k] = x[k]*10 + c-'0';
            अञ्ञथा x[k] = c-'0';
            सचे (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } अञ्ञथा {
            dc++;
            सचे (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    सचे (!gotrad) lrp=dc;

    सचे (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        सचे (e10 == LLONG_MIN) {
            सचे (pok) {
                shunget(f);
            } अञ्ञथा {
                shlim(f, 0);
                पटिनिवत्त 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } अञ्ञथा सचे (c>=0) {
        shunget(f);
    }
    सचे (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        पटिनिवत्त 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    सचे (!x[0]) पटिनिवत्त sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    सचे (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        पटिनिवत्त sign * (द्विगुण)x[0];
    सचे (lrp > -emin/2) {
        errno = ERANGE;
        पटिनिवत्त sign * DBL_MAX * DBL_MAX;
    }
    सचे (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        पटिनिवत्त sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    सचे (j) {
        अत्थाय (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    सचे (lnz<9 && lnz<=rp && rp < 18) {
        पूर्णाङ्क bitlim;
        सचे (rp == 9) पटिनिवत्त sign * (द्विगुण)x[0];
        सचे (rp < 9) पटिनिवत्त sign * (द्विगुण)x[0] / p10s[8-rp];
        bitlim = bits-3*(पूर्णाङ्क)(rp-9);
        सचे (bitlim>30 || x[0]>>bitlim==0)
            पटिनिवत्त sign * (द्विगुण)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    अत्थाय (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    सचे (rp % 9) {
        पूर्णाङ्क rpm9 = rp>=0 ? rp%9 : rp%9+9;
        पूर्णाङ्क p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        अत्थाय (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            सचे (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        सचे (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    याव (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        अत्थाय (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            सचे (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अञ्ञथा {
                carry = 0;
                x[k] = tmp;
            }
            सचे (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            सचे (k==a) भङ्ग;
        }
        सचे (carry) {
            rp += 9;
            a = (a-1 & MASK);
            सचे (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    अत्थाय (;;) {
        uint32_t carry = 0;
        पूर्णाङ्क sh = 1;
        अत्थाय (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            सचे (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                भङ्ग;
            }
            सचे (x[a+i & MASK] > th[i]) भङ्ग;
        }
        सचे (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) भङ्ग;
        /* FIXME: find a way to compute optimal sh */
        सचे (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        अत्थाय (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            सचे (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        सचे (carry) {
            सचे ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } अञ्ञथा x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    अत्थाय (y=i=0; i<LD_B1B_DIG; i++) {
        सचे ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    सचे (bits > DBL_MANT_DIG+e2-emin) {
        bits = DBL_MANT_DIG+e2-emin;
        सचे (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    सचे (bits < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-bits-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    सचे ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        सचे (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        अञ्ञथा सचे (t > 500000000)
            frac += 0.75*sign;
        अञ्ञथा सचे (t == 500000000) {
            सचे ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            अञ्ञथा
                frac += 0.75*sign;
        }
        सचे (DBL_MANT_DIG-bits >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    सचे ((e2+DBL_MANT_DIG & INT_MAX) > emax-5) {
        सचे (fabs(y) >= pow(2, DBL_MANT_DIG)) {
            सचे (denormal && bits==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        सचे (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    पटिनिवत्त scalbn(y, e2);
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
    अत्थाय (; c=='0'; c = shgetc(f))
        gotdig = 1;

    सचे (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        अत्थाय (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    अत्थाय (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        सचे (c=='.') {
            सचे (gotrad) भङ्ग;
            rp = dc;
            gotrad = 1;
        } अञ्ञथा {
            gotdig = 1;
            सचे (c > '9') d = (c|32)+10-'a';
            अञ्ञथा d = c-'0';
            सचे (dc<8) {
                x = x*16 + d;
            } अञ्ञथा सचे (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } अञ्ञथा सचे (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    सचे (!gotdig) {
        shunget(f);
        सचे (pok) {
            shunget(f);
            सचे (gotrad) shunget(f);
        } अञ्ञथा {
            shlim(f, 0);
        }
        पटिनिवत्त sign * 0.0;
    }
    सचे (!gotrad) rp = dc;
    याव (dc<8) x *= 16, dc++;
    सचे ((c|32)=='p') {
        e2 = scanexp(f, pok);
        सचे (e2 == LLONG_MIN) {
            सचे (pok) {
                shunget(f);
            } अञ्ञथा {
                shlim(f, 0);
                पटिनिवत्त 0;
            }
            e2 = 0;
        }
    } अञ्ञथा {
        shunget(f);
    }
    e2 += 4*rp - 32;

    सचे (!x) पटिनिवत्त sign * 0.0;
    सचे (e2 > -emin) {
        errno = ERANGE;
        पटिनिवत्त sign * DBL_MAX * DBL_MAX;
    }
    सचे (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        पटिनिवत्त sign * DBL_MIN * DBL_MIN;
    }

    याव (x < 0x80000000) {
        सचे (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } अञ्ञथा {
            x += x;
            y += y;
        }
        e2--;
    }

    सचे (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        सचे (bits<0) bits=0;
    }

    सचे (bits < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-bits-1), sign);

    सचे (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुण)x + sign*y;
    y -= bias;

    सचे (!y) errno = ERANGE;

    पटिनिवत्त scalbn(y, e2);
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
        पटिनिवत्त 0;
    }

    याव (av_isspace((c = shgetc(f))));

    सचे (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    अत्थाय (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        सचे (i<7) c = shgetc(f);
    सचे (i==3 || i==8 || (i>3 && pok)) {
        सचे (i!=8) {
            shunget(f);
            सचे (pok) अत्थाय (; i>3; i--) shunget(f);
        }
        पटिनिवत्त sign * INFINITY;
    }
    सचे (!i) अत्थाय (i=0; i<3 && (c|32)=="nan"[i]; i++)
        सचे (i<2) c = shgetc(f);
    सचे (i==3) {
        सचे (shgetc(f) != '(') {
            shunget(f);
            पटिनिवत्त NAN;
        }
        अत्थाय (i=1; ; i++) {
            c = shgetc(f);
            सचे (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                अनुवर्त;
            सचे (c==')') पटिनिवत्त NAN;
            shunget(f);
            सचे (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                पटिनिवत्त 0;
            }
            याव (i--) shunget(f);
            पटिनिवत्त NAN;
        }
    }

    सचे (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        पटिनिवत्त 0;
    }

    सचे (c=='0') {
        c = shgetc(f);
        सचे ((c|32) == 'x')
            पटिनिवत्त hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    पटिनिवत्त decfloat(f, c, bits, emin, sign, pok);
}

स्थिर शून्य *arg_n(va_list ap, unsigned पूर्णाङ्क n)
{
    शून्य *p;
    unsigned पूर्णाङ्क i;
    va_list ap2;
    va_copy(ap2, ap);
    अत्थाय (i=n; i>1; i--) va_arg(ap2, शून्य *);
    p = va_arg(ap2, शून्य *);
    va_end(ap2);
    पटिनिवत्त p;
}

स्थिर शून्य store_int(शून्य *dest, पूर्णाङ्क size, unsigned long long i)
{
    सचे (!dest) पटिनिवत्त;
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

    अत्थाय (p=(ध्रुव unsigned वर्ण *)fmt; *p; p++) {

        सचे (av_isspace(*p)) {
            याव (av_isspace(p[1])) p++;
            shlim(f, 0);
            याव (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            अनुवर्त;
        }
        सचे (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            सचे (*p == '%') {
                p++;
                याव (av_isspace((c=shgetc(f))));
            } अञ्ञथा {
                c = shgetc(f);
            }
            सचे (c!=*p) {
                shunget(f);
                सचे (c<0) गच्छ निवेशः_fail;
                गच्छ match_fail;
            }
            pos += shcnt(f);
            अनुवर्त;
        }

        p++;
        सचे (*p=='*') {
            dest = 0; p++;
        } अञ्ञथा सचे (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } अञ्ञथा {
            dest = va_arg(ap, शून्य *);
        }

        अत्थाय (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        सचे (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        विकल्प (*p++) {
        पक्ष 'h':
            सचे (*p == 'h') p++, size = SIZE_hh;
            अञ्ञथा size = SIZE_h;
            भङ्ग;
        पक्ष 'l':
            सचे (*p == 'l') p++, size = SIZE_ll;
            अञ्ञथा size = SIZE_l;
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
        सचे ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        विकल्प (t) {
            पक्ष 'c':
                सचे (width < 1) width = 1;
                भङ्ग;
            पक्ष '[':
                भङ्ग;
            पक्ष 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                अनुवर्त;
            स्वभाव:
                shlim(f, 0);
                याव (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        सचे (shgetc(f) < 0) गच्छ निवेशः_fail;
        shunget(f);

        विकल्प (t) {
            पक्ष 's':
            पक्ष 'c':
            पक्ष '[':
                सचे (t == 'c' || t == 's') {
                    memset(scanset, -1, परिमाण scanset);
                    scanset[0] = 0;
                    सचे (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } अञ्ञथा {
                    सचे (*++p == '^') p++, invert = 1;
                    अञ्ञथा invert = 0;
                    memset(scanset, invert, परिमाण scanset);
                    scanset[0] = 0;
                    सचे (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    अञ्ञथा सचे (*p == ']') p++, scanset[1+']'] = 1-invert;
                    अत्थाय (; *p != ']'; p++) {
                        सचे (!*p) गच्छ fmt_fail;
                        सचे (*p=='-' && p[1] && p[1] != ']')
                            अत्थाय (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                सचे ((s = dest)) {
                    याव (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } अञ्ञथा {
                    याव (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                सचे (!shcnt(f)) गच्छ match_fail;
                सचे (t == 'c' && shcnt(f) != width) गच्छ match_fail;
                सचे (t != 'c') {
                    सचे (s) s[i] = 0;
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
                सचे (!shcnt(f))
                    गच्छ match_fail;
                सचे (t=='p' && dest)
                    *(शून्य **)dest = (शून्य *)(uintptr_t)x;
                अञ्ञथा
                    store_int(dest, size, x);
                भङ्ग;
            पक्ष 'a': पक्ष 'A':
            पक्ष 'e': पक्ष 'E':
            पक्ष 'f': पक्ष 'F':
            पक्ष 'g': पक्ष 'G':
                y = fffloatscan(f, size, 0);
                सचे (!shcnt(f))
                    गच्छ match_fail;
                सचे (dest) {
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
        सचे (dest) matches++;
    }
    सचे (0) {
fmt_fail:
निवेशः_fail:
        सचे (!matches) matches--;
    }
match_fail:
    पटिनिवत्त matches;
}

स्थिर पूर्णाङ्क ff_vsscanf(ध्रुव वर्ण *s, ध्रुव वर्ण *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (शून्य *)s, .cookie = (शून्य *)s,
        .पठ = ffstring_read,
    };

    पटिनिवत्त ff_vfscanf(&f, fmt, ap);
}

पूर्णाङ्क av_sscanf(ध्रुव वर्ण *string, ध्रुव वर्ण *format, ...)
{
    पूर्णाङ्क ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    पटिनिवत्त ret;
}
