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
    size_t buf_आकार;
    अचिह्नित वर्ण *buf;
    अचिह्नित वर्ण *rpos, *rend;
    अचिह्नित वर्ण *shend;
    ptrdiff_t shlim, shcnt;
    शून्य *cookie;
    size_t (*पठ)(संरचना FFFILE *, अचिह्नित वर्ण *, size_t);
} FFFILE;

#परिभाषय आकार_hh -2
#परिभाषय आकार_h  -1
#परिभाषय आकार_def 0
#परिभाषय आकार_l   1
#परिभाषय आकार_L   2
#परिभाषय आकार_ll  3

#परिभाषय shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

स्थिर पूर्णाङ्क fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_आकार;
    प्रत्यागम 0;
}

स्थिर size_t ffstring_read(FFFILE *f, अचिह्नित वर्ण *buf, size_t len)
{
    वर्ण *src = f->cookie;
    size_t k = len+256;
    वर्ण *अन्तः_2 = memchr(src, 0, k);

    यदि (अन्तः_2) k = अन्तः_2-src;
    यदि (k < len) len = k;
    स्मृतिं_प्रतिलिख(buf, src, len);
    f->rpos = (शून्य *)(src+len);
    f->rend = (शून्य *)(src+k);
    f->cookie = src+k;

    प्रत्यागम len;
}

स्थिर पूर्णाङ्क ffuflow(FFFILE *f)
{
    अचिह्नित वर्ण c;
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

#परिभाषय shlim(f, lim) ffshlim((f), (lim))
#परिभाषय shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#परिभाषय shunget(f) ((f)->shend ? (शून्य)(f)->rpos-- : (शून्य)0)

स्थिर ध्रुव अचिह्नित वर्ण सारणी[] = { -1,
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

स्थिर अचिह्नित दीर्घ दीर्घ ffintscan(FFFILE *f, अचिह्नित आधारः_2, पूर्णाङ्क pok, अचिह्नित दीर्घ दीर्घ lim)
{
    ध्रुव अचिह्नित वर्ण *val = सारणी+1;
    पूर्णाङ्क c, neg=0;
    अचिह्नित x;
    अचिह्नित दीर्घ दीर्घ y;
    यदि (आधारः_2 > 36 || आधारः_2 == 1) {
        errno = EINVAL;
        प्रत्यागम 0;
    }
    यावत् (av_isspace((c=shgetc(f))));
    यदि (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    यदि ((आधारः_2 == 0 || आधारः_2 == 16) && c=='0') {
        c = shgetc(f);
        यदि ((c|32)=='x') {
            c = shgetc(f);
            यदि (val[c]>=16) {
                shunget(f);
                यदि (pok) shunget(f);
                अन्यथा shlim(f, 0);
                प्रत्यागम 0;
            }
            आधारः_2 = 16;
        } अन्यथा यदि (आधारः_2 == 0) {
            आधारः_2 = 8;
        }
    } अन्यथा {
        यदि (आधारः_2 == 0) आधारः_2 = 10;
        यदि (val[c] >= आधारः_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            प्रत्यागम 0;
        }
    }
    यदि (आधारः_2 == 10) {
        प्रति (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        प्रति (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        यदि (c-'0'>=10U) गच्छ समाप्तम्;
    } अन्यथा यदि (!(आधारः_2 & आधारः_2-1)) {
        पूर्णाङ्क bs = "\0\1\2\4\7\3\6\5"[(0x17*आधारः_2)>>5&7];
        प्रति (x=0; val[c]<आधारः_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        प्रति (y=x; val[c]<आधारः_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अन्यथा {
        प्रति (x=0; val[c]<आधारः_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*आधारः_2 + val[c];
        प्रति (y=x; val[c]<आधारः_2 && y<=ULLONG_MAX/आधारः_2 && आधारः_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*आधारः_2 + val[c];
    }
    यदि (val[c]<आधारः_2) {
        प्रति (; val[c]<आधारः_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        यदि (lim&1) neg = 0;
    }
समाप्तम्:
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

स्थिर दीर्घ दीर्घ scanexp(FFFILE *f, पूर्णाङ्क pok)
{
    पूर्णाङ्क c;
    पूर्णाङ्क x;
    दीर्घ दीर्घ y;
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
    प्रति (x=0; c-'0'<10U && x<अधिकतम_पूर्णाङ्कः/10; c = shgetc(f))
        x = 10*x + (c-'0');
    प्रति (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    प्रति (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    प्रत्यागम neg ? -y : y;
}

#परिभाषय LD_B1B_DIG 2
#परिभाषय LD_B1B_MAX 9007199, 254740991
#परिभाषय KMAX 128
#परिभाषय आवरणम् (KMAX-1)

स्थिर द्विगुण decfloat(FFFILE *f, पूर्णाङ्क c, पूर्णाङ्क द्वयङ्काः, पूर्णाङ्क emin, पूर्णाङ्क sign, पूर्णाङ्क pok)
{
    uint32_t x[KMAX];
    स्थिर ध्रुव uint32_t th[] = { LD_B1B_MAX };
    पूर्णाङ्क i, j, k, a, z;
    दीर्घ दीर्घ lrp=0, dc=0;
    दीर्घ दीर्घ e10=0;
    पूर्णाङ्क lnz = 0;
    पूर्णाङ्क gotdig = 0, gotrad = 0;
    पूर्णाङ्क rp;
    पूर्णाङ्क e2;
    पूर्णाङ्क emax = -emin-द्वयङ्काः+3;
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
    यदि (lrp==dc && dc<10 && (द्वयङ्काः>30 || x[0]>>द्वयङ्काः==0))
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
        bitlim = द्वयङ्काः-3*(पूर्णाङ्क)(rp-9);
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
                a = (a+1 & आवरणम्);
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
        प्रति (k=(z-1 & आवरणम्); ; k=(k-1 & आवरणम्)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            यदि (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अन्यथा {
                carry = 0;
                x[k] = tmp;
            }
            यदि (k==(z-1 & आवरणम्) && k!=a && !x[k]) z = k;
            यदि (k==a) भङ्ग;
        }
        यदि (carry) {
            rp += 9;
            a = (a-1 & आवरणम्);
            यदि (a == z) {
                z = (z-1 & आवरणम्);
                x[z-1 & आवरणम्] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    प्रति (;;) {
        uint32_t carry = 0;
        पूर्णाङ्क sh = 1;
        प्रति (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & आवरणम्);
            यदि (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                भङ्ग;
            }
            यदि (x[a+i & आवरणम्] > th[i]) भङ्ग;
        }
        यदि (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) भङ्ग;
        /* FIXME: find a way to compute optimal sh */
        यदि (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        प्रति (k=a; k!=z; k=(k+1 & आवरणम्)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            यदि (k==a && !x[k]) {
                a = (a+1 & आवरणम्);
                i--;
                rp -= 9;
            }
        }
        यदि (carry) {
            यदि ((z+1 & आवरणम्) != a) {
                x[z] = carry;
                z = (z+1 & आवरणम्);
            } अन्यथा x[z-1 & आवरणम्] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    प्रति (y=i=0; i<LD_B1B_DIG; i++) {
        यदि ((a+i & आवरणम्)==z) x[(z=(z+1 & आवरणम्))-1 & आवरणम्] = 0;
        y = 1000000000.0L * y + x[a+i & आवरणम्];
    }

    y *= sign;

    /* Limit precision for denormal results */
    यदि (द्वयङ्काः > DBL_MANT_DIG+e2-emin) {
        द्वयङ्काः = DBL_MANT_DIG+e2-emin;
        यदि (द्वयङ्काः<0) द्वयङ्काः=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    यदि (द्वयङ्काः < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-द्वयङ्काः-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-द्वयङ्काः));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    यदि ((a+i & आवरणम्) != z) {
        uint32_t t = x[a+i & आवरणम्];
        यदि (t < 500000000 && (t || (a+i+1 & आवरणम्) != z))
            frac += 0.25*sign;
        अन्यथा यदि (t > 500000000)
            frac += 0.75*sign;
        अन्यथा यदि (t == 500000000) {
            यदि ((a+i+1 & आवरणम्) == z)
                frac += 0.5*sign;
            अन्यथा
                frac += 0.75*sign;
        }
        यदि (DBL_MANT_DIG-द्वयङ्काः >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    यदि ((e2+DBL_MANT_DIG & अधिकतम_पूर्णाङ्कः) > emax-5) {
        यदि (fabs(y) >= घातः(2, DBL_MANT_DIG)) {
            यदि (denormal && द्वयङ्काः==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        यदि (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    प्रत्यागम scalbn(y, e2);
}

स्थिर द्विगुण hexfloat(FFFILE *f, पूर्णाङ्क द्वयङ्काः, पूर्णाङ्क emin, पूर्णाङ्क sign, पूर्णाङ्क pok)
{
    uint32_t x = 0;
    द्विगुण y = 0;
    द्विगुण scale = 1;
    द्विगुण bias = 0;
    पूर्णाङ्क gottail = 0, gotrad = 0, gotdig = 0;
    दीर्घ दीर्घ rp = 0;
    दीर्घ दीर्घ dc = 0;
    दीर्घ दीर्घ e2 = 0;
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

    यदि (द्वयङ्काः > 32+e2-emin) {
        द्वयङ्काः = 32+e2-emin;
        यदि (द्वयङ्काः<0) द्वयङ्काः=0;
    }

    यदि (द्वयङ्काः < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-द्वयङ्काः-1), sign);

    यदि (द्वयङ्काः<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुण)x + sign*y;
    y -= bias;

    यदि (!y) errno = ERANGE;

    प्रत्यागम scalbn(y, e2);
}

स्थिर द्विगुण fffloatscan(FFFILE *f, पूर्णाङ्क prec, पूर्णाङ्क pok)
{
    पूर्णाङ्क sign = 1;
    size_t i;
    पूर्णाङ्क द्वयङ्काः;
    पूर्णाङ्क emin;
    पूर्णाङ्क c;

    विकल्प (prec) {
    पक्ष 0:
        द्वयङ्काः = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-द्वयङ्काः;
        भङ्ग;
    पक्ष 1:
        द्वयङ्काः = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-द्वयङ्काः;
        भङ्ग;
    पक्ष 2:
        द्वयङ्काः = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-द्वयङ्काः;
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
            प्रत्यागम hexfloat(f, द्वयङ्काः, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    प्रत्यागम decfloat(f, c, द्वयङ्काः, emin, sign, pok);
}

स्थिर शून्य *arg_n(va_list ap, अचिह्नित पूर्णाङ्क n)
{
    शून्य *p;
    अचिह्नित पूर्णाङ्क i;
    va_list ap2;
    va_copy(ap2, ap);
    प्रति (i=n; i>1; i--) va_arg(ap2, शून्य *);
    p = va_arg(ap2, शून्य *);
    va_end(ap2);
    प्रत्यागम p;
}

स्थिर शून्य store_int(शून्य *dest, पूर्णाङ्क आकार, अचिह्नित दीर्घ दीर्घ i)
{
    यदि (!dest) प्रत्यागम;
    विकल्प (आकार) {
    पक्ष आकार_hh:
        *(वर्ण *)dest = i;
        भङ्ग;
    पक्ष आकार_h:
        *(ह्रस्व *)dest = i;
        भङ्ग;
    पक्ष आकार_def:
        *(पूर्णाङ्क *)dest = i;
        भङ्ग;
    पक्ष आकार_l:
        *(दीर्घ *)dest = i;
        भङ्ग;
    पक्ष आकार_ll:
        *(दीर्घ दीर्घ *)dest = i;
        भङ्ग;
    }
}

स्थिर पूर्णाङ्क ff_vfscanf(FFFILE *f, ध्रुव वर्ण *fmt, va_list ap)
{
    पूर्णाङ्क विस्तारः;
    पूर्णाङ्क आकार;
    पूर्णाङ्क आधारः_2;
    ध्रुव अचिह्नित वर्ण *p;
    पूर्णाङ्क c, t;
    वर्ण *s;
    शून्य *dest=रिक्त;
    पूर्णाङ्क invert;
    पूर्णाङ्क matches=0;
    अचिह्नित दीर्घ दीर्घ x;
    द्विगुण y;
    ptrdiff_t pos = 0;
    अचिह्नित वर्ण scanset[257];
    size_t i;

    प्रति (p=(ध्रुव अचिह्नित वर्ण *)fmt; *p; p++) {

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
                यदि (c<0) गच्छ निवेशः_fail;
                गच्छ मेलनम्_fail;
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

        प्रति (विस्तारः=0; av_isdigit(*p); p++) {
            विस्तारः = 10*विस्तारः + *p - '0';
        }

        यदि (*p=='m') {
            s = 0;
            p++;
        }

        आकार = आकार_def;
        विकल्प (*p++) {
        पक्ष 'h':
            यदि (*p == 'h') p++, आकार = आकार_hh;
            अन्यथा आकार = आकार_h;
            भङ्ग;
        पक्ष 'l':
            यदि (*p == 'l') p++, आकार = आकार_ll;
            अन्यथा आकार = आकार_l;
            भङ्ग;
        पक्ष 'j':
            आकार = आकार_ll;
            भङ्ग;
        पक्ष 'z':
        पक्ष 't':
            आकार = आकार_l;
            भङ्ग;
        पक्ष 'L':
            आकार = आकार_L;
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
            आकार = आकार_l;
        }

        विकल्प (t) {
            पक्ष 'c':
                यदि (विस्तारः < 1) विस्तारः = 1;
                भङ्ग;
            पक्ष '[':
                भङ्ग;
            पक्ष 'n':
                store_int(dest, आकार, pos);
                /* do not increment match count, etc! */
                अनुवर्त;
            स्वभाव:
                shlim(f, 0);
                यावत् (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, विस्तारः);
        यदि (shgetc(f) < 0) गच्छ निवेशः_fail;
        shunget(f);

        विकल्प (t) {
            पक्ष 's':
            पक्ष 'c':
            पक्ष '[':
                यदि (t == 'c' || t == 's') {
                    स्मृतिं_पूरय(scanset, -1, परिमाण scanset);
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
                    स्मृतिं_पूरय(scanset, invert, परिमाण scanset);
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
                यदि (!shcnt(f)) गच्छ मेलनम्_fail;
                यदि (t == 'c' && shcnt(f) != विस्तारः) गच्छ मेलनम्_fail;
                यदि (t != 'c') {
                    यदि (s) s[i] = 0;
                }
                भङ्ग;
            पक्ष 'p':
            पक्ष 'X':
            पक्ष 'x':
                आधारः_2 = 16;
                गच्छ int_common;
            पक्ष 'o':
                आधारः_2 = 8;
                गच्छ int_common;
            पक्ष 'd':
            पक्ष 'u':
                आधारः_2 = 10;
                गच्छ int_common;
            पक्ष 'i':
                आधारः_2 = 0;
int_common:
                x = ffintscan(f, आधारः_2, 0, ULLONG_MAX);
                यदि (!shcnt(f))
                    गच्छ मेलनम्_fail;
                यदि (t=='p' && dest)
                    *(शून्य **)dest = (शून्य *)(uintptr_t)x;
                अन्यथा
                    store_int(dest, आकार, x);
                भङ्ग;
            पक्ष 'a': पक्ष 'A':
            पक्ष 'e': पक्ष 'E':
            पक्ष 'f': पक्ष 'F':
            पक्ष 'g': पक्ष 'G':
                y = fffloatscan(f, आकार, 0);
                यदि (!shcnt(f))
                    गच्छ मेलनम्_fail;
                यदि (dest) {
                    विकल्प (आकार) {
                    पक्ष आकार_def:
                        *(भिन्न *)dest = y;
                        भङ्ग;
                    पक्ष आकार_l:
                        *(द्विगुण *)dest = y;
                        भङ्ग;
                    पक्ष आकार_L:
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
निवेशः_fail:
        यदि (!matches) matches--;
    }
मेलनम्_fail:
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
