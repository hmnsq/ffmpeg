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

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <float.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFFILE {
    size_t buf_ਮਾਪ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *rpos, *rend;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *shend;
    ptrdiff_t shlim, shcnt;
    ਖਾਲੀ *cookie;
    size_t (*ਪਠ)(ਬਣਤਰ FFFILE *, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *, size_t);
} FFFILE;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_hh -2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_h  -1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_def 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_l   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_L   2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_ll  3

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ਸਥਿਰ ਪੂਰਨ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_ਮਾਪ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ size_t ffstring_read(FFFILE *f, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf, size_t len)
{
    ਅੱਖਰ *src = f->cookie;
    size_t k = len+256;
    ਅੱਖਰ *ਸਿਰਾ = memchr(src, 0, k);

    ਜੇ (ਸਿਰਾ) k = ਸਿਰਾ-src;
    ਜੇ (k < len) len = k;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(buf, src, len);
    f->rpos = (ਖਾਲੀ *)(src+len);
    f->rend = (ਖਾਲੀ *)(src+k);
    f->cookie = src+k;

    ਵਾਪਸ len;
}

ਸਥਿਰ ਪੂਰਨ ffuflow(FFFILE *f)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ c;
    ਜੇ (!fftoread(f) && f->ਪਠ(f, &c, 1)==1) ਵਾਪਸ c;
    ਵਾਪਸ EOF;
}

ਸਥਿਰ ਖਾਲੀ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ਜੇ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ਨਹੀਂਤਾਂ
        f->shend = f->rend;
}

ਸਥਿਰ ਪੂਰਨ ffshgetc(FFFILE *f)
{
    ਪੂਰਨ c;
    ptrdiff_t cnt = shcnt(f);
    ਜੇ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ਵਾਪਸ EOF;
    }
    cnt++;
    ਜੇ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ਨਹੀਂਤਾਂ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ਜੇ (f->rpos[-1] != c) f->rpos[-1] = c;
    ਵਾਪਸ c;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ shlim(f, lim) ffshlim((f), (lim))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ shunget(f) ((f)->shend ? (ਖਾਲੀ)(f)->rpos-- : (ਖਾਲੀ)0)

ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਸਾਰਣੀ[] = { -1,
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

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ ffintscan(FFFILE *f, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅਧਾਰ_2, ਪੂਰਨ pok, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ lim)
{
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *val = ਸਾਰਣੀ+1;
    ਪੂਰਨ c, neg=0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ x;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ y;
    ਜੇ (ਅਧਾਰ_2 > 36 || ਅਧਾਰ_2 == 1) {
        errno = EINVAL;
        ਵਾਪਸ 0;
    }
    ਜਦੋਂ (av_isspace((c=shgetc(f))));
    ਜੇ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ਜੇ ((ਅਧਾਰ_2 == 0 || ਅਧਾਰ_2 == 16) && c=='0') {
        c = shgetc(f);
        ਜੇ ((c|32)=='x') {
            c = shgetc(f);
            ਜੇ (val[c]>=16) {
                shunget(f);
                ਜੇ (pok) shunget(f);
                ਨਹੀਂਤਾਂ shlim(f, 0);
                ਵਾਪਸ 0;
            }
            ਅਧਾਰ_2 = 16;
        } ਨਹੀਂਤਾਂ ਜੇ (ਅਧਾਰ_2 == 0) {
            ਅਧਾਰ_2 = 8;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਅਧਾਰ_2 == 0) ਅਧਾਰ_2 = 10;
        ਜੇ (val[c] >= ਅਧਾਰ_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ਵਾਪਸ 0;
        }
    }
    ਜੇ (ਅਧਾਰ_2 == 10) {
        ਲਈ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ਲਈ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ਜੇ (c-'0'>=10U) ਜਾਓ ਪੂਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (!(ਅਧਾਰ_2 & ਅਧਾਰ_2-1)) {
        ਪੂਰਨ bs = "\0\1\2\4\7\3\6\5"[(0x17*ਅਧਾਰ_2)>>5&7];
        ਲਈ (x=0; val[c]<ਅਧਾਰ_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ਲਈ (y=x; val[c]<ਅਧਾਰ_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ਨਹੀਂਤਾਂ {
        ਲਈ (x=0; val[c]<ਅਧਾਰ_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*ਅਧਾਰ_2 + val[c];
        ਲਈ (y=x; val[c]<ਅਧਾਰ_2 && y<=ULLONG_MAX/ਅਧਾਰ_2 && ਅਧਾਰ_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*ਅਧਾਰ_2 + val[c];
    }
    ਜੇ (val[c]<ਅਧਾਰ_2) {
        ਲਈ (; val[c]<ਅਧਾਰ_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ਜੇ (lim&1) neg = 0;
    }
ਪੂਰਾ:
    shunget(f);
    ਜੇ (y>=lim) {
        ਜੇ (!(lim&1) && !neg) {
            errno = ERANGE;
            ਵਾਪਸ lim-1;
        } ਨਹੀਂਤਾਂ ਜੇ (y>lim) {
            errno = ERANGE;
            ਵਾਪਸ lim;
        }
    }
    ਵਾਪਸ (y^neg)-neg;
}

ਸਥਿਰ ਲੰਮਾ ਲੰਮਾ scanexp(FFFILE *f, ਪੂਰਨ pok)
{
    ਪੂਰਨ c;
    ਪੂਰਨ x;
    ਲੰਮਾ ਲੰਮਾ y;
    ਪੂਰਨ neg = 0;

    c = shgetc(f);
    ਜੇ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ਜੇ (c-'0'>=10U && pok) shunget(f);
    }
    ਜੇ (c-'0'>=10U) {
        shunget(f);
        ਵਾਪਸ LLONG_MIN;
    }
    ਲਈ (x=0; c-'0'<10U && x<ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ਲਈ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ਲਈ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ਵਾਪਸ neg ? -y : y;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_B1B_DIG 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_B1B_MAX 9007199, 254740991
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KMAX 128
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਕਾਬ (KMAX-1)

ਸਥਿਰ ਦੁੱਗਣਾ decfloat(FFFILE *f, ਪੂਰਨ c, ਪੂਰਨ ਬਿੱਟ, ਪੂਰਨ emin, ਪੂਰਨ sign, ਪੂਰਨ pok)
{
    uint32_t x[KMAX];
    ਸਥਿਰ ਅਚਲ uint32_t th[] = { LD_B1B_MAX };
    ਪੂਰਨ i, j, k, a, z;
    ਲੰਮਾ ਲੰਮਾ lrp=0, dc=0;
    ਲੰਮਾ ਲੰਮਾ e10=0;
    ਪੂਰਨ lnz = 0;
    ਪੂਰਨ gotdig = 0, gotrad = 0;
    ਪੂਰਨ rp;
    ਪੂਰਨ e2;
    ਪੂਰਨ emax = -emin-ਬਿੱਟ+3;
    ਪੂਰਨ denormal = 0;
    ਦੁੱਗਣਾ y;
    ਦੁੱਗਣਾ frac=0;
    ਦੁੱਗਣਾ bias=0;
    ਸਥਿਰ ਅਚਲ ਪੂਰਨ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ਲਈ (; c=='0'; c = shgetc(f)) gotdig=1;
    ਜੇ (c=='.') {
        gotrad = 1;
        ਲਈ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ਲਈ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ਜੇ (c == '.') {
            ਜੇ (gotrad) ਰੋਕੋ;
            gotrad = 1;
            lrp = dc;
        } ਨਹੀਂਤਾਂ ਜੇ (k < KMAX-3) {
            dc++;
            ਜੇ (c!='0') lnz = dc;
            ਜੇ (j) x[k] = x[k]*10 + c-'0';
            ਨਹੀਂਤਾਂ x[k] = c-'0';
            ਜੇ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ਨਹੀਂਤਾਂ {
            dc++;
            ਜੇ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ਜੇ (!gotrad) lrp=dc;

    ਜੇ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ਜੇ (e10 == LLONG_MIN) {
            ਜੇ (pok) {
                shunget(f);
            } ਨਹੀਂਤਾਂ {
                shlim(f, 0);
                ਵਾਪਸ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ਨਹੀਂਤਾਂ ਜੇ (c>=0) {
        shunget(f);
    }
    ਜੇ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ਵਾਪਸ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ਜੇ (!x[0]) ਵਾਪਸ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ਜੇ (lrp==dc && dc<10 && (ਬਿੱਟ>30 || x[0]>>ਬਿੱਟ==0))
        ਵਾਪਸ sign * (ਦੁੱਗਣਾ)x[0];
    ਜੇ (lrp > -emin/2) {
        errno = ERANGE;
        ਵਾਪਸ sign * DBL_MAX * DBL_MAX;
    }
    ਜੇ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ਵਾਪਸ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ਜੇ (j) {
        ਲਈ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ਜੇ (lnz<9 && lnz<=rp && rp < 18) {
        ਪੂਰਨ bitlim;
        ਜੇ (rp == 9) ਵਾਪਸ sign * (ਦੁੱਗਣਾ)x[0];
        ਜੇ (rp < 9) ਵਾਪਸ sign * (ਦੁੱਗਣਾ)x[0] / p10s[8-rp];
        bitlim = ਬਿੱਟ-3*(ਪੂਰਨ)(rp-9);
        ਜੇ (bitlim>30 || x[0]>>bitlim==0)
            ਵਾਪਸ sign * (ਦੁੱਗਣਾ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ਲਈ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ਜੇ (rp % 9) {
        ਪੂਰਨ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ਪੂਰਨ p10 = p10s[8-rpm9];
        uint32_t ਹਾਸਲ = 0;
        ਲਈ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + ਹਾਸਲ;
            ਹਾਸਲ = 1000000000/p10 * tmp;
            ਜੇ (k==a && !x[k]) {
                a = (a+1 & ਨਕਾਬ);
                rp -= 9;
            }
        }
        ਜੇ (ਹਾਸਲ) x[z++] = ਹਾਸਲ;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ਜਦੋਂ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t ਹਾਸਲ = 0;
        e2 -= 29;
        ਲਈ (k=(z-1 & ਨਕਾਬ); ; k=(k-1 & ਨਕਾਬ)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + ਹਾਸਲ;
            ਜੇ (tmp > 1000000000) {
                ਹਾਸਲ = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ਨਹੀਂਤਾਂ {
                ਹਾਸਲ = 0;
                x[k] = tmp;
            }
            ਜੇ (k==(z-1 & ਨਕਾਬ) && k!=a && !x[k]) z = k;
            ਜੇ (k==a) ਰੋਕੋ;
        }
        ਜੇ (ਹਾਸਲ) {
            rp += 9;
            a = (a-1 & ਨਕਾਬ);
            ਜੇ (a == z) {
                z = (z-1 & ਨਕਾਬ);
                x[z-1 & ਨਕਾਬ] |= x[z];
            }
            x[a] = ਹਾਸਲ;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ਲਈ (;;) {
        uint32_t ਹਾਸਲ = 0;
        ਪੂਰਨ sh = 1;
        ਲਈ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & ਨਕਾਬ);
            ਜੇ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                ਰੋਕੋ;
            }
            ਜੇ (x[a+i & ਨਕਾਬ] > th[i]) ਰੋਕੋ;
        }
        ਜੇ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) ਰੋਕੋ;
        /* FIXME: find a way to compute optimal sh */
        ਜੇ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ਲਈ (k=a; k!=z; k=(k+1 & ਨਕਾਬ)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + ਹਾਸਲ;
            ਹਾਸਲ = (1000000000>>sh) * tmp;
            ਜੇ (k==a && !x[k]) {
                a = (a+1 & ਨਕਾਬ);
                i--;
                rp -= 9;
            }
        }
        ਜੇ (ਹਾਸਲ) {
            ਜੇ ((z+1 & ਨਕਾਬ) != a) {
                x[z] = ਹਾਸਲ;
                z = (z+1 & ਨਕਾਬ);
            } ਨਹੀਂਤਾਂ x[z-1 & ਨਕਾਬ] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ਲਈ (y=i=0; i<LD_B1B_DIG; i++) {
        ਜੇ ((a+i & ਨਕਾਬ)==z) x[(z=(z+1 & ਨਕਾਬ))-1 & ਨਕਾਬ] = 0;
        y = 1000000000.0L * y + x[a+i & ਨਕਾਬ];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ਜੇ (ਬਿੱਟ > DBL_MANT_DIG+e2-emin) {
        ਬਿੱਟ = DBL_MANT_DIG+e2-emin;
        ਜੇ (ਬਿੱਟ<0) ਬਿੱਟ=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ਜੇ (ਬਿੱਟ < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-ਬਿੱਟ-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-ਬਿੱਟ));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ਜੇ ((a+i & ਨਕਾਬ) != z) {
        uint32_t t = x[a+i & ਨਕਾਬ];
        ਜੇ (t < 500000000 && (t || (a+i+1 & ਨਕਾਬ) != z))
            frac += 0.25*sign;
        ਨਹੀਂਤਾਂ ਜੇ (t > 500000000)
            frac += 0.75*sign;
        ਨਹੀਂਤਾਂ ਜੇ (t == 500000000) {
            ਜੇ ((a+i+1 & ਨਕਾਬ) == z)
                frac += 0.5*sign;
            ਨਹੀਂਤਾਂ
                frac += 0.75*sign;
        }
        ਜੇ (DBL_MANT_DIG-ਬਿੱਟ >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ਜੇ ((e2+DBL_MANT_DIG & ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) > emax-5) {
        ਜੇ (fabs(y) >= ਘਾਤ(2, DBL_MANT_DIG)) {
            ਜੇ (denormal && ਬਿੱਟ==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ਜੇ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ਵਾਪਸ scalbn(y, e2);
}

ਸਥਿਰ ਦੁੱਗਣਾ hexfloat(FFFILE *f, ਪੂਰਨ ਬਿੱਟ, ਪੂਰਨ emin, ਪੂਰਨ sign, ਪੂਰਨ pok)
{
    uint32_t x = 0;
    ਦੁੱਗਣਾ y = 0;
    ਦੁੱਗਣਾ scale = 1;
    ਦੁੱਗਣਾ bias = 0;
    ਪੂਰਨ gottail = 0, gotrad = 0, gotdig = 0;
    ਲੰਮਾ ਲੰਮਾ rp = 0;
    ਲੰਮਾ ਲੰਮਾ dc = 0;
    ਲੰਮਾ ਲੰਮਾ e2 = 0;
    ਪੂਰਨ d;
    ਪੂਰਨ c;

    c = shgetc(f);

    /* Skip leading zeros */
    ਲਈ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ਜੇ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ਲਈ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ਲਈ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ਜੇ (c=='.') {
            ਜੇ (gotrad) ਰੋਕੋ;
            rp = dc;
            gotrad = 1;
        } ਨਹੀਂਤਾਂ {
            gotdig = 1;
            ਜੇ (c > '9') d = (c|32)+10-'a';
            ਨਹੀਂਤਾਂ d = c-'0';
            ਜੇ (dc<8) {
                x = x*16 + d;
            } ਨਹੀਂਤਾਂ ਜੇ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ਨਹੀਂਤਾਂ ਜੇ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ਜੇ (!gotdig) {
        shunget(f);
        ਜੇ (pok) {
            shunget(f);
            ਜੇ (gotrad) shunget(f);
        } ਨਹੀਂਤਾਂ {
            shlim(f, 0);
        }
        ਵਾਪਸ sign * 0.0;
    }
    ਜੇ (!gotrad) rp = dc;
    ਜਦੋਂ (dc<8) x *= 16, dc++;
    ਜੇ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ਜੇ (e2 == LLONG_MIN) {
            ਜੇ (pok) {
                shunget(f);
            } ਨਹੀਂਤਾਂ {
                shlim(f, 0);
                ਵਾਪਸ 0;
            }
            e2 = 0;
        }
    } ਨਹੀਂਤਾਂ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ਜੇ (!x) ਵਾਪਸ sign * 0.0;
    ਜੇ (e2 > -emin) {
        errno = ERANGE;
        ਵਾਪਸ sign * DBL_MAX * DBL_MAX;
    }
    ਜੇ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ਵਾਪਸ sign * DBL_MIN * DBL_MIN;
    }

    ਜਦੋਂ (x < 0x80000000) {
        ਜੇ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ਨਹੀਂਤਾਂ {
            x += x;
            y += y;
        }
        e2--;
    }

    ਜੇ (ਬਿੱਟ > 32+e2-emin) {
        ਬਿੱਟ = 32+e2-emin;
        ਜੇ (ਬਿੱਟ<0) ਬਿੱਟ=0;
    }

    ਜੇ (ਬਿੱਟ < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-ਬਿੱਟ-1), sign);

    ਜੇ (ਬਿੱਟ<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ਦੁੱਗਣਾ)x + sign*y;
    y -= bias;

    ਜੇ (!y) errno = ERANGE;

    ਵਾਪਸ scalbn(y, e2);
}

ਸਥਿਰ ਦੁੱਗਣਾ fffloatscan(FFFILE *f, ਪੂਰਨ prec, ਪੂਰਨ pok)
{
    ਪੂਰਨ sign = 1;
    size_t i;
    ਪੂਰਨ ਬਿੱਟ;
    ਪੂਰਨ emin;
    ਪੂਰਨ c;

    ਚੋਣ (prec) {
    ਹਾਲਤ 0:
        ਬਿੱਟ = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ 1:
        ਬਿੱਟ = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ 2:
        ਬਿੱਟ = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-ਬਿੱਟ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ 0;
    }

    ਜਦੋਂ (av_isspace((c = shgetc(f))));

    ਜੇ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ਲਈ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ਜੇ (i<7) c = shgetc(f);
    ਜੇ (i==3 || i==8 || (i>3 && pok)) {
        ਜੇ (i!=8) {
            shunget(f);
            ਜੇ (pok) ਲਈ (; i>3; i--) shunget(f);
        }
        ਵਾਪਸ sign * INFINITY;
    }
    ਜੇ (!i) ਲਈ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ਜੇ (i<2) c = shgetc(f);
    ਜੇ (i==3) {
        ਜੇ (shgetc(f) != '(') {
            shunget(f);
            ਵਾਪਸ NAN;
        }
        ਲਈ (i=1; ; i++) {
            c = shgetc(f);
            ਜੇ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ਜਾਰੀ;
            ਜੇ (c==')') ਵਾਪਸ NAN;
            shunget(f);
            ਜੇ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ਵਾਪਸ 0;
            }
            ਜਦੋਂ (i--) shunget(f);
            ਵਾਪਸ NAN;
        }
    }

    ਜੇ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ਵਾਪਸ 0;
    }

    ਜੇ (c=='0') {
        c = shgetc(f);
        ਜੇ ((c|32) == 'x')
            ਵਾਪਸ hexfloat(f, ਬਿੱਟ, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ਵਾਪਸ decfloat(f, c, ਬਿੱਟ, emin, sign, pok);
}

ਸਥਿਰ ਖਾਲੀ *arg_n(va_list ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n)
{
    ਖਾਲੀ *p;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
    va_list ap2;
    va_copy(ap2, ap);
    ਲਈ (i=n; i>1; i--) va_arg(ap2, ਖਾਲੀ *);
    p = va_arg(ap2, ਖਾਲੀ *);
    va_end(ap2);
    ਵਾਪਸ p;
}

ਸਥਿਰ ਖਾਲੀ store_int(ਖਾਲੀ *dest, ਪੂਰਨ ਮਾਪ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ i)
{
    ਜੇ (!dest) ਵਾਪਸ;
    ਚੋਣ (ਮਾਪ) {
    ਹਾਲਤ ਮਾਪ_hh:
        *(ਅੱਖਰ *)dest = i;
        ਰੋਕੋ;
    ਹਾਲਤ ਮਾਪ_h:
        *(ਛੋਟਾ *)dest = i;
        ਰੋਕੋ;
    ਹਾਲਤ ਮਾਪ_def:
        *(ਪੂਰਨ *)dest = i;
        ਰੋਕੋ;
    ਹਾਲਤ ਮਾਪ_l:
        *(ਲੰਮਾ *)dest = i;
        ਰੋਕੋ;
    ਹਾਲਤ ਮਾਪ_ll:
        *(ਲੰਮਾ ਲੰਮਾ *)dest = i;
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਪੂਰਨ ff_vfscanf(FFFILE *f, ਅਚਲ ਅੱਖਰ *fmt, va_list ap)
{
    ਪੂਰਨ ਚੌੜਾਈ;
    ਪੂਰਨ ਮਾਪ;
    ਪੂਰਨ ਅਧਾਰ_2;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p;
    ਪੂਰਨ c, t;
    ਅੱਖਰ *s;
    ਖਾਲੀ *dest=ਨਿਰਾ;
    ਪੂਰਨ invert;
    ਪੂਰਨ matches=0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ x;
    ਦੁੱਗਣਾ y;
    ptrdiff_t pos = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ scanset[257];
    size_t i;

    ਲਈ (p=(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)fmt; *p; p++) {

        ਜੇ (av_isspace(*p)) {
            ਜਦੋਂ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ਜਦੋਂ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ਜਾਰੀ;
        }
        ਜੇ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ਜੇ (*p == '%') {
                p++;
                ਜਦੋਂ (av_isspace((c=shgetc(f))));
            } ਨਹੀਂਤਾਂ {
                c = shgetc(f);
            }
            ਜੇ (c!=*p) {
                shunget(f);
                ਜੇ (c<0) ਜਾਓ ਨਿਵੇਸ਼_fail;
                ਜਾਓ ਮੇਲ_fail;
            }
            pos += shcnt(f);
            ਜਾਰੀ;
        }

        p++;
        ਜੇ (*p=='*') {
            dest = 0; p++;
        } ਨਹੀਂਤਾਂ ਜੇ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ਨਹੀਂਤਾਂ {
            dest = va_arg(ap, ਖਾਲੀ *);
        }

        ਲਈ (ਚੌੜਾਈ=0; av_isdigit(*p); p++) {
            ਚੌੜਾਈ = 10*ਚੌੜਾਈ + *p - '0';
        }

        ਜੇ (*p=='m') {
            s = 0;
            p++;
        }

        ਮਾਪ = ਮਾਪ_def;
        ਚੋਣ (*p++) {
        ਹਾਲਤ 'h':
            ਜੇ (*p == 'h') p++, ਮਾਪ = ਮਾਪ_hh;
            ਨਹੀਂਤਾਂ ਮਾਪ = ਮਾਪ_h;
            ਰੋਕੋ;
        ਹਾਲਤ 'l':
            ਜੇ (*p == 'l') p++, ਮਾਪ = ਮਾਪ_ll;
            ਨਹੀਂਤਾਂ ਮਾਪ = ਮਾਪ_l;
            ਰੋਕੋ;
        ਹਾਲਤ 'j':
            ਮਾਪ = ਮਾਪ_ll;
            ਰੋਕੋ;
        ਹਾਲਤ 'z':
        ਹਾਲਤ 't':
            ਮਾਪ = ਮਾਪ_l;
            ਰੋਕੋ;
        ਹਾਲਤ 'L':
            ਮਾਪ = ਮਾਪ_L;
            ਰੋਕੋ;
        ਹਾਲਤ 'd': ਹਾਲਤ 'i': ਹਾਲਤ 'o': ਹਾਲਤ 'u': ਹਾਲਤ 'x':
        ਹਾਲਤ 'a': ਹਾਲਤ 'e': ਹਾਲਤ 'f': ਹਾਲਤ 'g':
        ਹਾਲਤ 'A': ਹਾਲਤ 'E': ਹਾਲਤ 'F': ਹਾਲਤ 'G': ਹਾਲਤ 'X':
        ਹਾਲਤ 's': ਹਾਲਤ 'c': ਹਾਲਤ '[':
        ਹਾਲਤ 'S': ਹਾਲਤ 'C':
        ਹਾਲਤ 'p': ਹਾਲਤ 'n':
            p--;
            ਰੋਕੋ;
        ਮੂਲ:
            ਜਾਓ fmt_fail;
        }

        t = *p;

        /* C or S */
        ਜੇ ((t&0x2f) == 3) {
            t |= 32;
            ਮਾਪ = ਮਾਪ_l;
        }

        ਚੋਣ (t) {
            ਹਾਲਤ 'c':
                ਜੇ (ਚੌੜਾਈ < 1) ਚੌੜਾਈ = 1;
                ਰੋਕੋ;
            ਹਾਲਤ '[':
                ਰੋਕੋ;
            ਹਾਲਤ 'n':
                store_int(dest, ਮਾਪ, pos);
                /* do not increment match count, etc! */
                ਜਾਰੀ;
            ਮੂਲ:
                shlim(f, 0);
                ਜਦੋਂ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, ਚੌੜਾਈ);
        ਜੇ (shgetc(f) < 0) ਜਾਓ ਨਿਵੇਸ਼_fail;
        shunget(f);

        ਚੋਣ (t) {
            ਹਾਲਤ 's':
            ਹਾਲਤ 'c':
            ਹਾਲਤ '[':
                ਜੇ (t == 'c' || t == 's') {
                    memset(scanset, -1, ਆਕਾਰ scanset);
                    scanset[0] = 0;
                    ਜੇ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ਨਹੀਂਤਾਂ {
                    ਜੇ (*++p == '^') p++, invert = 1;
                    ਨਹੀਂਤਾਂ invert = 0;
                    memset(scanset, invert, ਆਕਾਰ scanset);
                    scanset[0] = 0;
                    ਜੇ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ਨਹੀਂਤਾਂ ਜੇ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ਲਈ (; *p != ']'; p++) {
                        ਜੇ (!*p) ਜਾਓ fmt_fail;
                        ਜੇ (*p=='-' && p[1] && p[1] != ']')
                            ਲਈ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ਜੇ ((s = dest)) {
                    ਜਦੋਂ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ਨਹੀਂਤਾਂ {
                    ਜਦੋਂ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ਜੇ (!shcnt(f)) ਜਾਓ ਮੇਲ_fail;
                ਜੇ (t == 'c' && shcnt(f) != ਚੌੜਾਈ) ਜਾਓ ਮੇਲ_fail;
                ਜੇ (t != 'c') {
                    ਜੇ (s) s[i] = 0;
                }
                ਰੋਕੋ;
            ਹਾਲਤ 'p':
            ਹਾਲਤ 'X':
            ਹਾਲਤ 'x':
                ਅਧਾਰ_2 = 16;
                ਜਾਓ int_common;
            ਹਾਲਤ 'o':
                ਅਧਾਰ_2 = 8;
                ਜਾਓ int_common;
            ਹਾਲਤ 'd':
            ਹਾਲਤ 'u':
                ਅਧਾਰ_2 = 10;
                ਜਾਓ int_common;
            ਹਾਲਤ 'i':
                ਅਧਾਰ_2 = 0;
int_common:
                x = ffintscan(f, ਅਧਾਰ_2, 0, ULLONG_MAX);
                ਜੇ (!shcnt(f))
                    ਜਾਓ ਮੇਲ_fail;
                ਜੇ (t=='p' && dest)
                    *(ਖਾਲੀ **)dest = (ਖਾਲੀ *)(uintptr_t)x;
                ਨਹੀਂਤਾਂ
                    store_int(dest, ਮਾਪ, x);
                ਰੋਕੋ;
            ਹਾਲਤ 'a': ਹਾਲਤ 'A':
            ਹਾਲਤ 'e': ਹਾਲਤ 'E':
            ਹਾਲਤ 'f': ਹਾਲਤ 'F':
            ਹਾਲਤ 'g': ਹਾਲਤ 'G':
                y = fffloatscan(f, ਮਾਪ, 0);
                ਜੇ (!shcnt(f))
                    ਜਾਓ ਮੇਲ_fail;
                ਜੇ (dest) {
                    ਚੋਣ (ਮਾਪ) {
                    ਹਾਲਤ ਮਾਪ_def:
                        *(ਦਸ਼ਮਲਵ *)dest = y;
                        ਰੋਕੋ;
                    ਹਾਲਤ ਮਾਪ_l:
                        *(ਦੁੱਗਣਾ *)dest = y;
                        ਰੋਕੋ;
                    ਹਾਲਤ ਮਾਪ_L:
                        *(ਦੁੱਗਣਾ *)dest = y;
                        ਰੋਕੋ;
                    }
                }
                ਰੋਕੋ;
        }

        pos += shcnt(f);
        ਜੇ (dest) matches++;
    }
    ਜੇ (0) {
fmt_fail:
ਨਿਵੇਸ਼_fail:
        ਜੇ (!matches) matches--;
    }
ਮੇਲ_fail:
    ਵਾਪਸ matches;
}

ਸਥਿਰ ਪੂਰਨ ff_vsscanf(ਅਚਲ ਅੱਖਰ *s, ਅਚਲ ਅੱਖਰ *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (ਖਾਲੀ *)s, .cookie = (ਖਾਲੀ *)s,
        .ਪਠ = ffstring_read,
    };

    ਵਾਪਸ ff_vfscanf(&f, fmt, ap);
}

ਪੂਰਨ av_sscanf(ਅਚਲ ਅੱਖਰ *string, ਅਚਲ ਅੱਖਰ *format, ...)
{
    ਪੂਰਨ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ਵਾਪਸ ret;
}
