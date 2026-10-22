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

प्रकारव्याख्या संरचना FFFILE {
    माप_प्रकार buf_size;
    अचिन्हित अक्षर *buf;
    अचिन्हित अक्षर *rpos, *rend;
    अचिन्हित अक्षर *shend;
    सूचक_भेद_प्रकार shlim, shcnt;
    शून्य *cookie;
    माप_प्रकार (*पठ)(संरचना FFFILE *, अचिन्हित अक्षर *, माप_प्रकार);
} FFFILE;

#define SIZE_hh -2
#define SIZE_h  -1
#define SIZE_def 0
#define SIZE_l   1
#define SIZE_L   2
#define SIZE_ll  3

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

स्थिर पूर्णांक fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    परत 0;
}

स्थिर माप_प्रकार ffstring_read(FFFILE *f, अचिन्हित अक्षर *buf, माप_प्रकार len)
{
    अक्षर *src = f->cookie;
    माप_प्रकार k = len+256;
    अक्षर *end = स_प्रथम(src, 0, k);

    जर (end) k = end-src;
    जर (k < len) len = k;
    स_नकल(buf, src, len);
    f->rpos = (शून्य *)(src+len);
    f->rend = (शून्य *)(src+k);
    f->cookie = src+k;

    परत len;
}

स्थिर पूर्णांक ffuflow(FFFILE *f)
{
    अचिन्हित अक्षर c;
    जर (!fftoread(f) && f->पठ(f, &c, 1)==1) परत c;
    परत खातापूर्ण;
}

स्थिर शून्य ffshlim(FFFILE *f, सूचक_भेद_प्रकार lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    जर (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    अन्यथा
        f->shend = f->rend;
}

स्थिर पूर्णांक ffshgetc(FFFILE *f)
{
    पूर्णांक c;
    सूचक_भेद_प्रकार cnt = shcnt(f);
    जर (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        परत खातापूर्ण;
    }
    cnt++;
    जर (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    अन्यथा
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    जर (f->rpos[-1] != c) f->rpos[-1] = c;
    परत c;
}

#define shlim(f, lim) ffshlim((f), (lim))
#define shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#define shunget(f) ((f)->shend ? (शून्य)(f)->rpos-- : (शून्य)0)

स्थिर स्थिरांक अचिन्हित अक्षर table[] = { -1,
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

स्थिर अचिन्हित दीर्घ दीर्घ ffintscan(FFFILE *f, अचिन्हित base, पूर्णांक pok, अचिन्हित दीर्घ दीर्घ lim)
{
    स्थिरांक अचिन्हित अक्षर *val = table+1;
    पूर्णांक c, neg=0;
    अचिन्हित x;
    अचिन्हित दीर्घ दीर्घ y;
    जर (base > 36 || base == 1) {
        त्रुटि_सं = EINVAL;
        परत 0;
    }
    पर्यंत (av_isspace((c=shgetc(f))));
    जर (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    जर ((base == 0 || base == 16) && c=='0') {
        c = shgetc(f);
        जर ((c|32)=='x') {
            c = shgetc(f);
            जर (val[c]>=16) {
                shunget(f);
                जर (pok) shunget(f);
                अन्यथा shlim(f, 0);
                परत 0;
            }
            base = 16;
        } अन्यथा जर (base == 0) {
            base = 8;
        }
    } अन्यथा {
        जर (base == 0) base = 10;
        जर (val[c] >= base) {
            shunget(f);
            shlim(f, 0);
            त्रुटि_सं = EINVAL;
            परत 0;
        }
    }
    जर (base == 10) {
        साठी (x=0; c-'0'<10U && x<=अच_पूर्णांक_उच्च/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        साठी (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        जर (c-'0'>=10U) जा done;
    } अन्यथा जर (!(base & base-1)) {
        पूर्णांक bs = "\0\1\2\4\7\3\6\5"[(0x17*base)>>5&7];
        साठी (x=0; val[c]<base && x<=अच_पूर्णांक_उच्च/32; c=shgetc(f))
            x = x<<bs | val[c];
        साठी (y=x; val[c]<base && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } अन्यथा {
        साठी (x=0; val[c]<base && x<=अच_पूर्णांक_उच्च/36-1; c=shgetc(f))
            x = x*base + val[c];
        साठी (y=x; val[c]<base && y<=ULLONG_MAX/base && base*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*base + val[c];
    }
    जर (val[c]<base) {
        साठी (; val[c]<base; c=shgetc(f));
        त्रुटि_सं = दुस्फल;
        y = lim;
        जर (lim&1) neg = 0;
    }
done:
    shunget(f);
    जर (y>=lim) {
        जर (!(lim&1) && !neg) {
            त्रुटि_सं = दुस्फल;
            परत lim-1;
        } अन्यथा जर (y>lim) {
            त्रुटि_सं = दुस्फल;
            परत lim;
        }
    }
    परत (y^neg)-neg;
}

स्थिर दीर्घ दीर्घ scanexp(FFFILE *f, पूर्णांक pok)
{
    पूर्णांक c;
    पूर्णांक x;
    दीर्घ दीर्घ y;
    पूर्णांक neg = 0;

    c = shgetc(f);
    जर (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        जर (c-'0'>=10U && pok) shunget(f);
    }
    जर (c-'0'>=10U) {
        shunget(f);
        परत LLONG_MIN;
    }
    साठी (x=0; c-'0'<10U && x<पूर्णांक_उच्च/10; c = shgetc(f))
        x = 10*x + (c-'0');
    साठी (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    साठी (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    परत neg ? -y : y;
}

#define LD_B1B_DIG 2
#define LD_B1B_MAX 9007199, 254740991
#define KMAX 128
#define MASK (KMAX-1)

स्थिर द्विगुण decfloat(FFFILE *f, पूर्णांक c, पूर्णांक bits, पूर्णांक emin, पूर्णांक sign, पूर्णांक pok)
{
    uint32_t x[KMAX];
    स्थिर स्थिरांक uint32_t th[] = { LD_B1B_MAX };
    पूर्णांक i, j, k, a, z;
    दीर्घ दीर्घ lrp=0, dc=0;
    दीर्घ दीर्घ e10=0;
    पूर्णांक lnz = 0;
    पूर्णांक gotdig = 0, gotrad = 0;
    पूर्णांक rp;
    पूर्णांक e2;
    पूर्णांक emax = -emin-bits+3;
    पूर्णांक denormal = 0;
    द्विगुण y;
    द्विगुण frac=0;
    द्विगुण bias=0;
    स्थिर स्थिरांक पूर्णांक p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    साठी (; c=='0'; c = shgetc(f)) gotdig=1;
    जर (c=='.') {
        gotrad = 1;
        साठी (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    साठी (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        जर (c == '.') {
            जर (gotrad) थांबा;
            gotrad = 1;
            lrp = dc;
        } अन्यथा जर (k < KMAX-3) {
            dc++;
            जर (c!='0') lnz = dc;
            जर (j) x[k] = x[k]*10 + c-'0';
            अन्यथा x[k] = c-'0';
            जर (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } अन्यथा {
            dc++;
            जर (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    जर (!gotrad) lrp=dc;

    जर (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        जर (e10 == LLONG_MIN) {
            जर (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                परत 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } अन्यथा जर (c>=0) {
        shunget(f);
    }
    जर (!gotdig) {
        त्रुटि_सं = EINVAL;
        shlim(f, 0);
        परत 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    जर (!x[0]) परत sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    जर (lrp==dc && dc<10 && (bits>30 || x[0]>>bits==0))
        परत sign * (द्विगुण)x[0];
    जर (lrp > -emin/2) {
        त्रुटि_सं = दुस्फल;
        परत sign * द्विग_उच्च * द्विग_उच्च;
    }
    जर (lrp < emin-2*द्विग_पूर्ण) {
        त्रुटि_सं = दुस्फल;
        परत sign * द्विग_न्यून * द्विग_न्यून;
    }

    /* Align incomplete final B1B digit */
    जर (j) {
        साठी (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    जर (lnz<9 && lnz<=rp && rp < 18) {
        पूर्णांक bitlim;
        जर (rp == 9) परत sign * (द्विगुण)x[0];
        जर (rp < 9) परत sign * (द्विगुण)x[0] / p10s[8-rp];
        bitlim = bits-3*(पूर्णांक)(rp-9);
        जर (bitlim>30 || x[0]>>bitlim==0)
            परत sign * (द्विगुण)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    साठी (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    जर (rp % 9) {
        पूर्णांक rpm9 = rp>=0 ? rp%9 : rp%9+9;
        पूर्णांक p10 = p10s[8-rpm9];
        uint32_t carry = 0;
        साठी (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + carry;
            carry = 1000000000/p10 * tmp;
            जर (k==a && !x[k]) {
                a = (a+1 & MASK);
                rp -= 9;
            }
        }
        जर (carry) x[z++] = carry;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    पर्यंत (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t carry = 0;
        e2 -= 29;
        साठी (k=(z-1 & MASK); ; k=(k-1 & MASK)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + carry;
            जर (tmp > 1000000000) {
                carry = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } अन्यथा {
                carry = 0;
                x[k] = tmp;
            }
            जर (k==(z-1 & MASK) && k!=a && !x[k]) z = k;
            जर (k==a) थांबा;
        }
        जर (carry) {
            rp += 9;
            a = (a-1 & MASK);
            जर (a == z) {
                z = (z-1 & MASK);
                x[z-1 & MASK] |= x[z];
            }
            x[a] = carry;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    साठी (;;) {
        uint32_t carry = 0;
        पूर्णांक sh = 1;
        साठी (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & MASK);
            जर (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                थांबा;
            }
            जर (x[a+i & MASK] > th[i]) थांबा;
        }
        जर (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) थांबा;
        /* FIXME: find a way to compute optimal sh */
        जर (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        साठी (k=a; k!=z; k=(k+1 & MASK)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + carry;
            carry = (1000000000>>sh) * tmp;
            जर (k==a && !x[k]) {
                a = (a+1 & MASK);
                i--;
                rp -= 9;
            }
        }
        जर (carry) {
            जर ((z+1 & MASK) != a) {
                x[z] = carry;
                z = (z+1 & MASK);
            } अन्यथा x[z-1 & MASK] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    साठी (y=i=0; i<LD_B1B_DIG; i++) {
        जर ((a+i & MASK)==z) x[(z=(z+1 & MASK))-1 & MASK] = 0;
        y = 1000000000.0L * y + x[a+i & MASK];
    }

    y *= sign;

    /* Limit precision for denormal results */
    जर (bits > द्विग_पूर्ण+e2-emin) {
        bits = द्विग_पूर्ण+e2-emin;
        जर (bits<0) bits=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    जर (bits < द्विग_पूर्ण) {
        bias = copysign(scalbn(1, 2*द्विग_पूर्ण-bits-1), y);
        frac = भ_शेष(y, scalbn(1, द्विग_पूर्ण-bits));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    जर ((a+i & MASK) != z) {
        uint32_t t = x[a+i & MASK];
        जर (t < 500000000 && (t || (a+i+1 & MASK) != z))
            frac += 0.25*sign;
        अन्यथा जर (t > 500000000)
            frac += 0.75*sign;
        अन्यथा जर (t == 500000000) {
            जर ((a+i+1 & MASK) == z)
                frac += 0.5*sign;
            अन्यथा
                frac += 0.75*sign;
        }
        जर (द्विग_पूर्ण-bits >= 2 && !भ_शेष(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    जर ((e2+द्विग_पूर्ण & पूर्णांक_उच्च) > emax-5) {
        जर (भ_असल(y) >= घात(2, द्विग_पूर्ण)) {
            जर (denormal && bits==द्विग_पूर्ण+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        जर (e2+द्विग_पूर्ण>emax || (denormal && frac))
            त्रुटि_सं = दुस्फल;
    }

    परत scalbn(y, e2);
}

स्थिर द्विगुण hexfloat(FFFILE *f, पूर्णांक bits, पूर्णांक emin, पूर्णांक sign, पूर्णांक pok)
{
    uint32_t x = 0;
    द्विगुण y = 0;
    द्विगुण scale = 1;
    द्विगुण bias = 0;
    पूर्णांक gottail = 0, gotrad = 0, gotdig = 0;
    दीर्घ दीर्घ rp = 0;
    दीर्घ दीर्घ dc = 0;
    दीर्घ दीर्घ e2 = 0;
    पूर्णांक d;
    पूर्णांक c;

    c = shgetc(f);

    /* Skip leading zeros */
    साठी (; c=='0'; c = shgetc(f))
        gotdig = 1;

    जर (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        साठी (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    साठी (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        जर (c=='.') {
            जर (gotrad) थांबा;
            rp = dc;
            gotrad = 1;
        } अन्यथा {
            gotdig = 1;
            जर (c > '9') d = (c|32)+10-'a';
            अन्यथा d = c-'0';
            जर (dc<8) {
                x = x*16 + d;
            } अन्यथा जर (dc < द्विग_पूर्ण/4+1) {
                y += d*(scale/=16);
            } अन्यथा जर (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    जर (!gotdig) {
        shunget(f);
        जर (pok) {
            shunget(f);
            जर (gotrad) shunget(f);
        } अन्यथा {
            shlim(f, 0);
        }
        परत sign * 0.0;
    }
    जर (!gotrad) rp = dc;
    पर्यंत (dc<8) x *= 16, dc++;
    जर ((c|32)=='p') {
        e2 = scanexp(f, pok);
        जर (e2 == LLONG_MIN) {
            जर (pok) {
                shunget(f);
            } अन्यथा {
                shlim(f, 0);
                परत 0;
            }
            e2 = 0;
        }
    } अन्यथा {
        shunget(f);
    }
    e2 += 4*rp - 32;

    जर (!x) परत sign * 0.0;
    जर (e2 > -emin) {
        त्रुटि_सं = दुस्फल;
        परत sign * द्विग_उच्च * द्विग_उच्च;
    }
    जर (e2 < emin-2*द्विग_पूर्ण) {
        त्रुटि_सं = दुस्फल;
        परत sign * द्विग_न्यून * द्विग_न्यून;
    }

    पर्यंत (x < 0x80000000) {
        जर (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } अन्यथा {
            x += x;
            y += y;
        }
        e2--;
    }

    जर (bits > 32+e2-emin) {
        bits = 32+e2-emin;
        जर (bits<0) bits=0;
    }

    जर (bits < द्विग_पूर्ण)
        bias = copysign(scalbn(1, 32+द्विग_पूर्ण-bits-1), sign);

    जर (bits<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(द्विगुण)x + sign*y;
    y -= bias;

    जर (!y) त्रुटि_सं = दुस्फल;

    परत scalbn(y, e2);
}

स्थिर द्विगुण fffloatscan(FFFILE *f, पूर्णांक prec, पूर्णांक pok)
{
    पूर्णांक sign = 1;
    माप_प्रकार i;
    पूर्णांक bits;
    पूर्णांक emin;
    पूर्णांक c;

    निवड (prec) {
    स्थिती 0:
        bits = भग्न_पूर्ण;
        emin = FLT_MIN_EXP-bits;
        थांबा;
    स्थिती 1:
        bits = द्विग_पूर्ण;
        emin = DBL_MIN_EXP-bits;
        थांबा;
    स्थिती 2:
        bits = द्विग_पूर्ण;
        emin = DBL_MIN_EXP-bits;
        थांबा;
    पूर्वनिर्धारित:
        परत 0;
    }

    पर्यंत (av_isspace((c = shgetc(f))));

    जर (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    साठी (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        जर (i<7) c = shgetc(f);
    जर (i==3 || i==8 || (i>3 && pok)) {
        जर (i!=8) {
            shunget(f);
            जर (pok) साठी (; i>3; i--) shunget(f);
        }
        परत sign * अनन्त;
    }
    जर (!i) साठी (i=0; i<3 && (c|32)=="nan"[i]; i++)
        जर (i<2) c = shgetc(f);
    जर (i==3) {
        जर (shgetc(f) != '(') {
            shunget(f);
            परत न_अंक;
        }
        साठी (i=1; ; i++) {
            c = shgetc(f);
            जर (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                सुरूठेवा;
            जर (c==')') परत न_अंक;
            shunget(f);
            जर (!pok) {
                त्रुटि_सं = EINVAL;
                shlim(f, 0);
                परत 0;
            }
            पर्यंत (i--) shunget(f);
            परत न_अंक;
        }
    }

    जर (i) {
        shunget(f);
        त्रुटि_सं = EINVAL;
        shlim(f, 0);
        परत 0;
    }

    जर (c=='0') {
        c = shgetc(f);
        जर ((c|32) == 'x')
            परत hexfloat(f, bits, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    परत decfloat(f, c, bits, emin, sign, pok);
}

स्थिर शून्य *arg_n(बहु_सूची ap, अचिन्हित पूर्णांक n)
{
    शून्य *p;
    अचिन्हित पूर्णांक i;
    बहु_सूची ap2;
    va_copy(ap2, ap);
    साठी (i=n; i>1; i--) बहु_तर्क(ap2, शून्य *);
    p = बहु_तर्क(ap2, शून्य *);
    बहु_पूर्ण(ap2);
    परत p;
}

स्थिर शून्य store_int(शून्य *dest, पूर्णांक size, अचिन्हित दीर्घ दीर्घ i)
{
    जर (!dest) परत;
    निवड (size) {
    स्थिती SIZE_hh:
        *(अक्षर *)dest = i;
        थांबा;
    स्थिती SIZE_h:
        *(लघु *)dest = i;
        थांबा;
    स्थिती SIZE_def:
        *(पूर्णांक *)dest = i;
        थांबा;
    स्थिती SIZE_l:
        *(दीर्घ *)dest = i;
        थांबा;
    स्थिती SIZE_ll:
        *(दीर्घ दीर्घ *)dest = i;
        थांबा;
    }
}

स्थिर पूर्णांक ff_vfscanf(FFFILE *f, स्थिरांक अक्षर *fmt, बहु_सूची ap)
{
    पूर्णांक width;
    पूर्णांक size;
    पूर्णांक base;
    स्थिरांक अचिन्हित अक्षर *p;
    पूर्णांक c, t;
    अक्षर *s;
    शून्य *dest=रिक्त;
    पूर्णांक invert;
    पूर्णांक matches=0;
    अचिन्हित दीर्घ दीर्घ x;
    द्विगुण y;
    सूचक_भेद_प्रकार pos = 0;
    अचिन्हित अक्षर scanset[257];
    माप_प्रकार i;

    साठी (p=(स्थिरांक अचिन्हित अक्षर *)fmt; *p; p++) {

        जर (av_isspace(*p)) {
            पर्यंत (av_isspace(p[1])) p++;
            shlim(f, 0);
            पर्यंत (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            सुरूठेवा;
        }
        जर (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            जर (*p == '%') {
                p++;
                पर्यंत (av_isspace((c=shgetc(f))));
            } अन्यथा {
                c = shgetc(f);
            }
            जर (c!=*p) {
                shunget(f);
                जर (c<0) जा आदान_fail;
                जा match_fail;
            }
            pos += shcnt(f);
            सुरूठेवा;
        }

        p++;
        जर (*p=='*') {
            dest = 0; p++;
        } अन्यथा जर (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } अन्यथा {
            dest = बहु_तर्क(ap, शून्य *);
        }

        साठी (width=0; av_isdigit(*p); p++) {
            width = 10*width + *p - '0';
        }

        जर (*p=='m') {
            s = 0;
            p++;
        }

        size = SIZE_def;
        निवड (*p++) {
        स्थिती 'h':
            जर (*p == 'h') p++, size = SIZE_hh;
            अन्यथा size = SIZE_h;
            थांबा;
        स्थिती 'l':
            जर (*p == 'l') p++, size = SIZE_ll;
            अन्यथा size = SIZE_l;
            थांबा;
        स्थिती 'j':
            size = SIZE_ll;
            थांबा;
        स्थिती 'z':
        स्थिती 't':
            size = SIZE_l;
            थांबा;
        स्थिती 'L':
            size = SIZE_L;
            थांबा;
        स्थिती 'd': स्थिती 'i': स्थिती 'o': स्थिती 'u': स्थिती 'x':
        स्थिती 'a': स्थिती 'e': स्थिती 'f': स्थिती 'g':
        स्थिती 'A': स्थिती 'E': स्थिती 'F': स्थिती 'G': स्थिती 'X':
        स्थिती 's': स्थिती 'c': स्थिती '[':
        स्थिती 'S': स्थिती 'C':
        स्थिती 'p': स्थिती 'n':
            p--;
            थांबा;
        पूर्वनिर्धारित:
            जा fmt_fail;
        }

        t = *p;

        /* C or S */
        जर ((t&0x2f) == 3) {
            t |= 32;
            size = SIZE_l;
        }

        निवड (t) {
            स्थिती 'c':
                जर (width < 1) width = 1;
                थांबा;
            स्थिती '[':
                थांबा;
            स्थिती 'n':
                store_int(dest, size, pos);
                /* do not increment match count, etc! */
                सुरूठेवा;
            पूर्वनिर्धारित:
                shlim(f, 0);
                पर्यंत (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, width);
        जर (shgetc(f) < 0) जा आदान_fail;
        shunget(f);

        निवड (t) {
            स्थिती 's':
            स्थिती 'c':
            स्थिती '[':
                जर (t == 'c' || t == 's') {
                    स_रखो(scanset, -1, आकार scanset);
                    scanset[0] = 0;
                    जर (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } अन्यथा {
                    जर (*++p == '^') p++, invert = 1;
                    अन्यथा invert = 0;
                    स_रखो(scanset, invert, आकार scanset);
                    scanset[0] = 0;
                    जर (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    अन्यथा जर (*p == ']') p++, scanset[1+']'] = 1-invert;
                    साठी (; *p != ']'; p++) {
                        जर (!*p) जा fmt_fail;
                        जर (*p=='-' && p[1] && p[1] != ']')
                            साठी (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                जर ((s = dest)) {
                    पर्यंत (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } अन्यथा {
                    पर्यंत (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                जर (!shcnt(f)) जा match_fail;
                जर (t == 'c' && shcnt(f) != width) जा match_fail;
                जर (t != 'c') {
                    जर (s) s[i] = 0;
                }
                थांबा;
            स्थिती 'p':
            स्थिती 'X':
            स्थिती 'x':
                base = 16;
                जा int_common;
            स्थिती 'o':
                base = 8;
                जा int_common;
            स्थिती 'd':
            स्थिती 'u':
                base = 10;
                जा int_common;
            स्थिती 'i':
                base = 0;
int_common:
                x = ffintscan(f, base, 0, ULLONG_MAX);
                जर (!shcnt(f))
                    जा match_fail;
                जर (t=='p' && dest)
                    *(शून्य **)dest = (शून्य *)(uintptr_t)x;
                अन्यथा
                    store_int(dest, size, x);
                थांबा;
            स्थिती 'a': स्थिती 'A':
            स्थिती 'e': स्थिती 'E':
            स्थिती 'f': स्थिती 'F':
            स्थिती 'g': स्थिती 'G':
                y = fffloatscan(f, size, 0);
                जर (!shcnt(f))
                    जा match_fail;
                जर (dest) {
                    निवड (size) {
                    स्थिती SIZE_def:
                        *(दशांश *)dest = y;
                        थांबा;
                    स्थिती SIZE_l:
                        *(द्विगुण *)dest = y;
                        थांबा;
                    स्थिती SIZE_L:
                        *(द्विगुण *)dest = y;
                        थांबा;
                    }
                }
                थांबा;
        }

        pos += shcnt(f);
        जर (dest) matches++;
    }
    जर (0) {
fmt_fail:
आदान_fail:
        जर (!matches) matches--;
    }
match_fail:
    परत matches;
}

स्थिर पूर्णांक ff_vsscanf(स्थिरांक अक्षर *s, स्थिरांक अक्षर *fmt, बहु_सूची ap)
{
    FFFILE f = {
        .buf = (शून्य *)s, .cookie = (शून्य *)s,
        .पठ = ffstring_read,
    };

    परत ff_vfscanf(&f, fmt, ap);
}

पूर्णांक av_sscanf(स्थिरांक अक्षर *string, स्थिरांक अक्षर *format, ...)
{
    पूर्णांक ret;
    बहु_सूची ap;
    बहु_शुरू(ap, format);
    ret = ff_vsscanf(string, format, ap);
    बहु_पूर्ण(ap);
    परत ret;
}
