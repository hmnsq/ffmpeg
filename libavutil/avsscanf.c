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

#समावेश <errno.h>
#समावेश <limits.h>
#समावेश <math.h>
#समावेश <stdarg.h>
#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <float.h>

#समावेश "avstring.h"

प्रकार काष्ठा FFFILE {
    माप_प्रकार buf_आकार;
    अचिन्हित अक्षर *buf;
    अचिन्हित अक्षर *rpos, *rend;
    अचिन्हित अक्षर *shend;
    सूचक_भेद_प्रकार shlim, shcnt;
    व्योम *cookie;
    माप_प्रकार (*पढ़ो)(काष्ठा FFFILE *, अचिन्हित अक्षर *, माप_प्रकार);
} FFFILE;

#घोषणा आकार_hh -2
#घोषणा आकार_h  -1
#घोषणा आकार_def 0
#घोषणा आकार_l   1
#घोषणा आकार_L   2
#घोषणा आकार_ll  3

#घोषणा shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

अटल पूर्णांक fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_आकार;
    वापस 0;
}

अटल माप_प्रकार ffstring_read(FFFILE *f, अचिन्हित अक्षर *buf, माप_प्रकार len)
{
    अक्षर *src = f->cookie;
    माप_प्रकार k = len+256;
    अक्षर *end = स_प्रथम(src, 0, k);

    अगर (end) k = end-src;
    अगर (k < len) len = k;
    स_नकल(buf, src, len);
    f->rpos = (व्योम *)(src+len);
    f->rend = (व्योम *)(src+k);
    f->cookie = src+k;

    वापस len;
}

अटल पूर्णांक ffuflow(FFFILE *f)
{
    अचिन्हित अक्षर c;
    अगर (!fftoread(f) && f->पढ़ो(f, &c, 1)==1) वापस c;
    वापस खातापूर्ण;
}

अटल व्योम ffshlim(FFFILE *f, सूचक_भेद_प्रकार lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    अगर (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    अन्यथा
        f->shend = f->rend;
}

अटल पूर्णांक ffshgetc(FFFILE *f)
{
    पूर्णांक c;
    सूचक_भेद_प्रकार cnt = shcnt(f);
    अगर (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        वापस खातापूर्ण;
    }
    cnt++;
    अगर (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    अन्यथा
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    अगर (f->rpos[-1] != c) f->rpos[-1] = c;
    वापस c;
}

#घोषणा shlim(f, lim) ffshlim((f), (lim))
#घोषणा shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#घोषणा shunget(f) ((f)->shend ? (व्योम)(f)->rpos-- : (व्योम)0)

अटल स्थिर अचिन्हित अक्षर table[] = { -1,
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

अटल अचिन्हित दीर्घ दीर्घ ffintscan(FFFILE *f, अचिन्हित base, पूर्णांक pok, अचिन्हित दीर्घ दीर्घ lim)
{
    स्थिर अचिन्हित अक्षर *val = table+1;
    पूर्णांक c, neg=0;
    अचिन्हित x;
    अचिन्हित दीर्घ दीर्घ y;
    अगर (base > 36 || base == 1) {
        त्रुटि_सं = EINVAL;
        वापस 0;
    }
    जबतक (av_isspace((c=shgetc(f))));
    अगर (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    अगर ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        अगर ((c|32)=='x') {
            c = shgetc(f);
            अगर (val[c]>=16) {
                shunget(f);
                अगर (pok) shunget(f);
                अन्यथा shlim(f, 0);
                वापस 0;
            }
            base = 16;
        } अन्यथा अगर (base == 0) {
            base = 8;
        }
    } अन्यथा {
        अगर (base == 0) base = 10;
        अगर (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            त्रुटि_सं = EINVAL;
            वापस 0;
        }
    }
    अगर (base == 10) {
        क्रम (x=0; c-'0'<10U && x<=अच_पूर्णांक_उच्च/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        क्रम (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        अगर (c-'0'>=10U) जाओ done;
    } अन्यथा अगर (!(base & base-1)) {
        पूर्णांक bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        क्रम (x=0; val[c]<base && x<=अच_पूर्णांक_उच्च/32; c=shgetc(f))
            x = x<<bs | val[c];
        क्रम (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अन्यथा {
        क्रम (x=0; val[c]<base && x<=अच_पूर्णांक_उच्च/36-1; c=shgetc(f))
            x = x*base + val[c];
        क्रम (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    अगर (val[c]<base) {
        क्रम (; val[c]<base; c=shgetc(f));
        त्रुटि_सं = दुस्फल;
        y = lim;
        अगर (lim&1) neg = 0;
    }
done:
    shunget(f);
    अगर (y>=lim) {
        अगर (!(lim&1) && !neg) {
            त्रुटि_सं = दुस्फल;
            वापस lim-1;
        } अन्यथा अगर (y>lim) {
            त्रुटि_सं = दुस्फल;
            वापस lim;
        }
    }
    वापस (y^neg)-neg;
}

अटल दीर्घ दीर्घ scanexp(FFFILE *f, पूर्णांक pok)
{
    पूर्णांक c;
    पूर्णांक x;
    दीर्घ दीर्घ y;
    पूर्णांक neg = 0;

    c = shgetc(f);
    अगर (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        अगर (c-'0'>=10U && pok) shunget(f);
    }
    अगर (c-'0'>=10U) {
        shunget(f);
        वापस LLONG_MIN;
    }
    क्रम (x=0; c-'0'<10U && x<पूर्णांक_उच्च/10; c = shgetc(f))
        x = 10*x + (c-'0');
    क्रम (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    क्रम (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    वापस neg ? -y : y;
}

#घोषणा LD_B1B_DIG 2
#घोषणा LD_B1B_MAX 9007199, 254740991
#घोषणा KMAX 128
#घोषणा MASK (KMAX-1)

अटल द्विगुन decfloat(FFFILE *f, पूर्णांक c, पूर्णांक bits, पूर्णांक emin, पूर्णांक sign, पूर्णांक pok)
{
    uint32_t x[KMAX];
    अटल स्थिर uint32_t th[] = { LD_B1B_MAX };
    पूर्णांक i, j, k, a, z;
    दीर्घ दीर्घ lrp=0, dc=0;
    दीर्घ दीर्घ e10=0;
    पूर्णांक lnz = 0;
    पूर्णांक gotdig = 0, gotrad = 0;
    पूर्णांक rp;
    पूर्णांक e2;
    पूर्णांक emax = -emin-bits+3;
    पूर्णांक denormal = 0;
    द्विगुन y;
    द्विगुन frac=0;
    द्विगुन bias=0;
    अटल स्थिर पूर्णांक p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    क्रम (; c=='0'; c = shgetc(f)) gotdig=1;
    अगर (c=='.') {
        gotrad = 1;
        क्रम (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    क्रम (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        अगर (c == '.') {
            अगर (gotrad) अवरोध;
            gotrad = 1;
            lrp = dc;
        } अन्यथा अगर (k < KMAX-3) {
            dc++;
            अगर (c!='0') lnz = dc;
            अगर (j) x[k] = x[k]*10 + c-'0';
            अन्यथा x[k] = c-'0';
            अगर (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } अन्यथा {
            dc++;
            अगर (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    अगर (!gotrad) lrp=dc;

    अगर (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        अगर (e10 == LLONG_MIN) {
            अगर (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                वापस 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } अन्यथा अगर (c>=0) {
        shunget(f);
    }
    अगर (!gotdig) {
        त्रुटि_सं = EINVAL;
        shlim(f, 0);
        वापस 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    अगर (!x[0]) वापस sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    अगर (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        वापस sign * (द्विगुन)x[0];
    अगर (lrp > -emin/2) {
        त्रुटि_सं = दुस्फल;
        वापस sign * द्विग_उच्च * द्विग_उच्च;
    }
    अगर (lrp < emin-2*द्विग_पूर्ण) {
        त्रुटि_सं = दुस्फल;
        वापस sign * द्विग_न्यून * द्विग_न्यून;
    }

    /* Align incomplete final B1B digit */
    अगर (j) {
        क्रम (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    अगर (lnz<9 && lnz<=rp && rp < 18) {
        पूर्णांक bitlim;
        अगर (rp == 9) वापस sign * (द्विगुन)x[0];
        अगर (rp < 9) वापस sign * (द्विगुन)x[0] / p10s[8-rp];
        bitlim = bits-3*(पूर्णांक)(rp-9);
        अगर (bitlim>30 || x[0]>>bitlim==0)
            वापस sign * (द्विगुन)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    क्रम (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    अगर (rp % 9) {
        पूर्णांक rpm9 = rp>=0 ? rp%9 : rp%9+9;
        पूर्णांक p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        क्रम (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            अगर (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        अगर (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    जबतक (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        क्रम (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            अगर (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अन्यथा {
                carry = 0;
                x[k] = tmp;
            }
            अगर (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            अगर (k==a) अवरोध;
        }
        अगर (carry) {
            rp += 9;
            a = (a-1 & MASK);
            अगर (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    क्रम (;;) {
        uint32_t carry = 0;
        पूर्णांक sh = 1;
        क्रम (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            अगर (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                अवरोध;
            }
            अगर (x[a+i & MASK] > th[i]) अवरोध;
        }
        अगर (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) अवरोध;
        /* FIXME: find a way to compute optimal sh */
        अगर (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        क्रम (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            अगर (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        अगर (carry) {
            अगर ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } अन्यथा x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    क्रम (y=i=0; i<LD_B1B_DIG; i++) {
        अगर ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    अगर (bits > द्विग_पूर्ण+e2-emin) {
        bits = द्विग_पूर्ण+e2-emin;
        अगर (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    अगर (bits < द्विग_पूर्ण) {
        bias = copysign(scalbn(1, 2*द्विग_पूर्ण-bits-1), y);
        frac = भ_शेष(y, scalbn(1, द्विग_पूर्ण-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    अगर ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        अगर (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        अन्यथा अगर (t > 500000000)
            frac += 0.75*sign;
        अन्यथा अगर (t == 500000000) {
            अगर ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            अन्यथा
                frac += 0.75*sign;
        }
        अगर (द्विग_पूर्ण-bits >= 2 && !भ_शेष(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    अगर ((e2+द्विग_पूर्ण & पूर्णांक_उच्च) > emax-5) {
        अगर (भ_असल(y) >= घात(2, द्विग_पूर्ण)) {
            अगर (denormal && bits==द्विग_पूर्ण+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        अगर (e2+द्विग_पूर्ण>emax || (denormal && frac))
            त्रुटि_सं = दुस्फल;
    }

    वापस scalbn(y, e2);
}

अटल द्विगुन hexfloat(FFFILE *f, पूर्णांक bits, पूर्णांक emin, पूर्णांक sign, पूर्णांक pok)
{
    uint32_t x = 0;
    द्विगुन y = 0;
    द्विगुन scale = 1;
    द्विगुन bias = 0;
    पूर्णांक gottail = 0, gotrad = 0, gotdig = 0;
    दीर्घ दीर्घ rp = 0;
    दीर्घ दीर्घ dc = 0;
    दीर्घ दीर्घ e2 = 0;
    पूर्णांक d;
    पूर्णांक c;

    c = shgetc(f);

    /* Skip leading zeros */
    क्रम (; c=='0'; c = shgetc(f))
        gotdig = 1;

    अगर (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        क्रम (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    क्रम (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        अगर (c=='.') {
            अगर (gotrad) अवरोध;
            rp = dc;
            gotrad = 1;
        } अन्यथा {
            gotdig = 1;
            अगर (c > '9') d = (c|32)+10-'a';
            अन्यथा d = c-'0';
            अगर (dc<8) {
                x = x*16 + d;
            } अन्यथा अगर (dc < द्विग_पूर्ण/4+1) {
                y += d*(scale/=16);
            } अन्यथा अगर (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    अगर (!gotdig) {
        shunget(f);
        अगर (pok) {
            shunget(f);
            अगर (gotrad) shunget(f);
        } अन्यथा {
            shlim(f, 0);
        }
        वापस sign * 0.0;
    }
    अगर (!gotrad) rp = dc;
    जबतक (dc<8) x *= 16, dc++;
    अगर ((c|32)=='p') {
        e2 = scanexp(f, pok);
        अगर (e2 == LLONG_MIN) {
            अगर (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                वापस 0;
            }
            e2 = 0;
        }
    } अन्यथा {
        shunget(f);
    }
    e2 += 4*rp - 32;

    अगर (!x) वापस sign * 0.0;
    अगर (e2 > -emin) {
        त्रुटि_सं = दुस्फल;
        वापस sign * द्विग_उच्च * द्विग_उच्च;
    }
    अगर (e2 < emin-2*द्विग_पूर्ण) {
        त्रुटि_सं = दुस्फल;
        वापस sign * द्विग_न्यून * द्विग_न्यून;
    }

    जबतक (x < 0x80000000) {
        अगर (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } अन्यथा {
            x += x;
            y += y;
        }
        e2--;
    }

    अगर (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        अगर (bits<0) bits=0;
    }

    अगर (bits < द्विग_पूर्ण)
        bias = copysign(scalbn(1, 32+द्विग_पूर्ण-bits-1), sign);

    अगर (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुन)x + sign*y;
    y -= bias;

    अगर (!y) त्रुटि_सं = दुस्फल;

    वापस scalbn(y, e2);
}

अटल द्विगुन fffloatscan(FFFILE *f, पूर्णांक prec, पूर्णांक pok)
{
    पूर्णांक sign = 1;
    माप_प्रकार i;
    पूर्णांक bits;
    पूर्णांक emin;
    पूर्णांक c;

    चयन (prec) {
    हाल 0:
        bits = भग्न_पूर्ण;
        emin = FLT_MIN_EXP-bits;
        अवरोध;
    हाल 1:
        bits = द्विग_पूर्ण;
        emin = DBL_MIN_EXP-bits;
        अवरोध;
    हाल 2:
        bits = द्विग_पूर्ण;
        emin = DBL_MIN_EXP-bits;
        अवरोध;
    शेष:
        वापस 0;
    }

    जबतक (av_isspace((c = shgetc(f))));

    अगर (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    क्रम (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        अगर (i<7) c = shgetc(f);
    अगर (i==3 || i==8 || (i>3 && pok)) {
        अगर (i!=8) {
            shunget(f);
            अगर (pok) क्रम (; i>3; i--) shunget(f);
        }
        वापस sign * अनन्त;
    }
    अगर (!i) क्रम (i=0; i<3 && (c|32)=="nan"[i]; i++)
        अगर (i<2) c = shgetc(f);
    अगर (i==3) {
        अगर (shgetc(f) != '(') {
            shunget(f);
            वापस न_अंक;
        }
        क्रम (i=1; ; i++) {
            c = shgetc(f);
            अगर (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                जारी;
            अगर (c==')') वापस न_अंक;
            shunget(f);
            अगर (!pok) {
                त्रुटि_सं = EINVAL;
                shlim(f, 0);
                वापस 0;
            }
            जबतक (i--) shunget(f);
            वापस न_अंक;
        }
    }

    अगर (i) {
        shunget(f);
        त्रुटि_सं = EINVAL;
        shlim(f, 0);
        वापस 0;
    }

    अगर (c=='0') {
        c = shgetc(f);
        अगर ((c|32) == 'x')
            वापस hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    वापस decfloat(f, c, bits, emin, sign, pok);
}

अटल व्योम *arg_n(बहु_सूची ap, अचिन्हित पूर्णांक n)
{
    व्योम *p;
    अचिन्हित पूर्णांक i;
    बहु_सूची ap2;
    va_copy(ap2, ap);
    क्रम (i=n; i>1; i--) बहु_तर्क(ap2, व्योम *);
    p = बहु_तर्क(ap2, व्योम *);
    बहु_पूर्ण(ap2);
    वापस p;
}

अटल व्योम store_int(व्योम *dest, पूर्णांक आकार, अचिन्हित दीर्घ दीर्घ i)
{
    अगर (!dest) वापस;
    चयन (आकार) {
    हाल आकार_hh:
        *(अक्षर *)dest = i;
        अवरोध;
    हाल आकार_h:
        *(लघु *)dest = i;
        अवरोध;
    हाल आकार_def:
        *(पूर्णांक *)dest = i;
        अवरोध;
    हाल आकार_l:
        *(दीर्घ *)dest = i;
        अवरोध;
    हाल आकार_ll:
        *(दीर्घ दीर्घ *)dest = i;
        अवरोध;
    }
}

अटल पूर्णांक ff_vfscanf(FFFILE *f, स्थिर अक्षर *fmt, बहु_सूची ap)
{
    पूर्णांक width;
    पूर्णांक आकार;
    पूर्णांक base;
    स्थिर अचिन्हित अक्षर *p;
    पूर्णांक c, t;
    अक्षर *s;
    व्योम *dest=शून्य;
    पूर्णांक invert;
    पूर्णांक matches=0;
    अचिन्हित दीर्घ दीर्घ x;
    द्विगुन y;
    सूचक_भेद_प्रकार pos = 0;
    अचिन्हित अक्षर scanset[257];
    माप_प्रकार i;

    क्रम (p=(स्थिर अचिन्हित अक्षर *)fmt; *p; p++) {

        अगर (av_isspace(*p)) {
            जबतक (av_isspace(p[1])) p++;
            shlim(f, 0);
            जबतक (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            जारी;
        }
        अगर (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            अगर (*p == '%') {
                p++;
                जबतक (av_isspace((c=shgetc(f))));
            } अन्यथा {
                c = shgetc(f);
            }
            अगर (c!=*p) {
                shunget(f);
                अगर (c<0) जाओ निवेश_fail;
                जाओ match_fail;
            }
            pos += shcnt(f);
            जारी;
        }

        p++;
        अगर (*p=='*') {
            dest = 0; p++;
        } अन्यथा अगर (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } अन्यथा {
            dest = बहु_तर्क(ap, व्योम *);
        }

        क्रम (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        अगर (*p=='m') {
            s = 0;
            p++;
        }

        आकार = आकार_def;
        चयन (*p++) {
        हाल 'h':
            अगर (*p == 'h') p++, आकार = आकार_hh;
            अन्यथा आकार = आकार_h;
            अवरोध;
        हाल 'l':
            अगर (*p == 'l') p++, आकार = आकार_ll;
            अन्यथा आकार = आकार_l;
            अवरोध;
        हाल 'j':
            आकार = आकार_ll;
            अवरोध;
        हाल 'z':
        हाल 't':
            आकार = आकार_l;
            अवरोध;
        हाल 'L':
            आकार = आकार_L;
            अवरोध;
        हाल 'd': हाल 'i': हाल 'o': हाल 'u': हाल 'x':
        हाल 'a': हाल 'e': हाल 'f': हाल 'g':
        हाल 'A': हाल 'E': हाल 'F': हाल 'G': हाल 'X':
        हाल 's': हाल 'c': हाल '[':
        हाल 'S': हाल 'C':
        हाल 'p': हाल 'n':
            p--;
            अवरोध;
        शेष:
            जाओ fmt_fail;
        }

        t = *p;

        /* C or S */
        अगर ((t&0x2f) == 3) {
            t |= 32;
            आकार = आकार_l;
        }

        चयन (t) {
            हाल 'c':
                अगर (width < 1) width = 1;
                अवरोध;
            हाल '[':
                अवरोध;
            हाल 'n':
                store_int(dest, आकार, pos);
                /* do not increment match count, etc! */
                जारी;
            शेष:
                shlim(f, 0);
                जबतक (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        अगर (shgetc(f) < 0) जाओ निवेश_fail;
        shunget(f);

        चयन (t) {
            हाल 's':
            हाल 'c':
            हाल '[':
                अगर (t == 'c' || t == 's') {
                    स_रखो(scanset, -1, माप scanset);
                    scanset[0] = 0;
                    अगर (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } अन्यथा {
                    अगर (*++p == '^') p++, invert = 1;
                    अन्यथा invert = 0;
                    स_रखो(scanset, invert, माप scanset);
                    scanset[0] = 0;
                    अगर (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    अन्यथा अगर (*p == ']') p++, scanset[1+']'] = 1-invert;
                    क्रम (; *p != ']'; p++) {
                        अगर (!*p) जाओ fmt_fail;
                        अगर (*p=='-' && p[1] && p[1] != ']')
                            क्रम (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                अगर ((s = dest)) {
                    जबतक (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } अन्यथा {
                    जबतक (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                अगर (!shcnt(f)) जाओ match_fail;
                अगर (t == 'c' && shcnt(f) != width) जाओ match_fail;
                अगर (t != 'c') {
                    अगर (s) s[i] = 0;
                }
                अवरोध;
            हाल 'p':
            हाल 'X':
            हाल 'x':
                base = 16;
                जाओ int_common;
            हाल 'o':
                base = 8;
                जाओ int_common;
            हाल 'd':
            हाल 'u':
                base = 10;
                जाओ int_common;
            हाल 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                अगर (!shcnt(f))
                    जाओ match_fail;
                अगर (t=='p' && dest)
                    *(व्योम **)dest = (व्योम *)(uintptr_t)x;
                अन्यथा
                    store_int(dest, आकार, x);
                अवरोध;
            हाल 'a': हाल 'A':
            हाल 'e': हाल 'E':
            हाल 'f': हाल 'F':
            हाल 'g': हाल 'G':
                y = fffloatscan(f, आकार, 0);
                अगर (!shcnt(f))
                    जाओ match_fail;
                अगर (dest) {
                    चयन (आकार) {
                    हाल आकार_def:
                        *(भग्न *)dest = y;
                        अवरोध;
                    हाल आकार_l:
                        *(द्विगुन *)dest = y;
                        अवरोध;
                    हाल आकार_L:
                        *(द्विगुन *)dest = y;
                        अवरोध;
                    }
                }
                अवरोध;
        }

        pos += shcnt(f);
        अगर (dest) matches++;
    }
    अगर (0) {
fmt_fail:
निवेश_fail:
        अगर (!matches) matches--;
    }
match_fail:
    वापस matches;
}

अटल पूर्णांक ff_vsscanf(स्थिर अक्षर *s, स्थिर अक्षर *fmt, बहु_सूची ap)
{
    FFFILE f = {
        .buf = (व्योम *)s, .cookie = (व्योम *)s,
        .पढ़ो = ffstring_read,
    };

    वापस ff_vfscanf(&f, fmt, ap);
}

पूर्णांक av_sscanf(स्थिर अक्षर *string, स्थिर अक्षर *format, ...)
{
    पूर्णांक ret;
    बहु_सूची ap;
    बहु_शुरू(ap, format);
    ret = ff_vsscanf(string, format, ap);
    बहु_पूर्ण(ap);
    वापस ret;
}
