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

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <float.h>

#ಅನ್ತರ್ಭಾವ "avstring.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFFILE {
    size_t buf_ಗಾತ್ರ;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *rpos, *rend;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *shend;
    ptrdiff_t shlim, shcnt;
    ಶೂನ್ಯ *cookie;
    size_t (*ಪಠ)(ರಚನೆ FFFILE *, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *, size_t);
} FFFILE;

#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_hh -2
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_h  -1
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_def 0
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_l   1
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_L   2
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_ll  3

#ವ್ಯಾಖ್ಯಾನಿಸು shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_ಗಾತ್ರ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ size_t ffstring_read(FFFILE *f, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf, size_t len)
{
    ಅಕ್ಷರ *src = f->cookie;
    size_t k = len+256;
    ಅಕ್ಷರ *ಕೊನೆ = memchr(src, 0, k);

    ಆದರೆ (ಕೊನೆ) k = ಕೊನೆ-src;
    ಆದರೆ (k < len) len = k;
    ಸ್ಮರಣೆ_ನಕಲು(buf, src, len);
    f->rpos = (ಶೂನ್ಯ *)(src+len);
    f->rend = (ಶೂನ್ಯ *)(src+k);
    f->cookie = src+k;

    ಹಿಂತಿರುಗಿ len;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ffuflow(FFFILE *f)
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ c;
    ಆದರೆ (!fftoread(f) && f->ಪಠ(f, &c, 1)==1) ಹಿಂತಿರುಗಿ c;
    ಹಿಂತಿರುಗಿ EOF;
}

ಸ್ಥಿರ ಶೂನ್ಯ ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    ಆದರೆ (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    ಇಲ್ಲದಿದ್ದರೆ
        f->shend = f->rend;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ffshgetc(FFFILE *f)
{
    ಪೂರ್ಣಾಂಕ c;
    ptrdiff_t cnt = shcnt(f);
    ಆದರೆ (f->shlim && cnt >= f->shlim || (c=ffuflow(f)) < 0) {
        f->shcnt = f->buf - f->rpos + cnt;
        f->shend = 0;
        ಹಿಂತಿರುಗಿ EOF;
    }
    cnt++;
    ಆದರೆ (f->shlim && f->rend - f->rpos > f->shlim - cnt)
        f->shend = f->rpos + (f->shlim - cnt);
    ಇಲ್ಲದಿದ್ದರೆ
        f->shend = f->rend;
    f->shcnt = f->buf - f->rpos + cnt;
    ಆದರೆ (f->rpos[-1] != c) f->rpos[-1] = c;
    ಹಿಂತಿರುಗಿ c;
}

#ವ್ಯಾಖ್ಯಾನಿಸು shlim(f, lim) ffshlim((f), (lim))
#ವ್ಯಾಖ್ಯಾನಿಸು shgetc(f) (((f)->rpos < (f)->shend) ? *(f)->rpos++ : ffshgetc(f))
#ವ್ಯಾಖ್ಯಾನಿಸು shunget(f) ((f)->shend ? (ಶೂನ್ಯ)(f)->rpos-- : (ಶೂನ್ಯ)0)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೋಷ್ಟಕ[] = { -1,
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

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ffintscan(FFFILE *f, ಚಿಹ್ನೆರಹಿತ ತಳ_2, ಪೂರ್ಣಾಂಕ pok, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ lim)
{
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *val = ಕೋಷ್ಟಕ+1;
    ಪೂರ್ಣಾಂಕ c, neg=0;
    ಚಿಹ್ನೆರಹಿತ x;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ y;
    ಆದರೆ (ತಳ_2 > 36 || ತಳ_2 == 1) {
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ 0;
    }
    ಆಗ (av_isspace((c=shgetc(f))));
    ಆದರೆ (c=='+' || c=='-') {
        neg = -(c=='-');
        c = shgetc(f);
    }
    ಆದರೆ ((ತಳ_2 == 0 || ತಳ_2 == 16) && c=='0') {
        c = shgetc(f);
        ಆದರೆ ((c|32)=='x') {
            c = shgetc(f);
            ಆದರೆ (val[c]>=16) {
                shunget(f);
                ಆದರೆ (pok) shunget(f);
                ಇಲ್ಲದಿದ್ದರೆ shlim(f, 0);
                ಹಿಂತಿರುಗಿ 0;
            }
            ತಳ_2 = 16;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ತಳ_2 == 0) {
            ತಳ_2 = 8;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ತಳ_2 == 0) ತಳ_2 = 10;
        ಆದರೆ (val[c] >= ತಳ_2) {
            shunget(f);
            shlim(f, 0);
            errno = EINVAL;
            ಹಿಂತಿರುಗಿ 0;
        }
    }
    ಆದರೆ (ತಳ_2 == 10) {
        ಗಾಗಿ (x=0; c-'0'<10U && x<=UINT_MAX/10-1; c=shgetc(f))
            x = x*10 + (c-'0');
        ಗಾಗಿ (y=x; c-'0'<10U && y<=ULLONG_MAX/10 && 10*y<=ULLONG_MAX-(c-'0'); c=shgetc(f))
            y = y*10 + (c-'0');
        ಆದರೆ (c-'0'>=10U) ಹೋಗು ಮುಗಿದ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(ತಳ_2 & ತಳ_2-1)) {
        ಪೂರ್ಣಾಂಕ bs = "\0\1\2\4\7\3\6\5"[(0x17*ತಳ_2)>>5&7];
        ಗಾಗಿ (x=0; val[c]<ತಳ_2 && x<=UINT_MAX/32; c=shgetc(f))
            x = x<<bs | val[c];
        ಗಾಗಿ (y=x; val[c]<ತಳ_2 && y<=ULLONG_MAX>>bs; c=shgetc(f))
            y = y<<bs | val[c];
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (x=0; val[c]<ತಳ_2 && x<=UINT_MAX/36-1; c=shgetc(f))
            x = x*ತಳ_2 + val[c];
        ಗಾಗಿ (y=x; val[c]<ತಳ_2 && y<=ULLONG_MAX/ತಳ_2 && ತಳ_2*y<=ULLONG_MAX-val[c]; c=shgetc(f))
            y = y*ತಳ_2 + val[c];
    }
    ಆದರೆ (val[c]<ತಳ_2) {
        ಗಾಗಿ (; val[c]<ತಳ_2; c=shgetc(f));
        errno = ERANGE;
        y = lim;
        ಆದರೆ (lim&1) neg = 0;
    }
ಮುಗಿದ:
    shunget(f);
    ಆದರೆ (y>=lim) {
        ಆದರೆ (!(lim&1) && !neg) {
            errno = ERANGE;
            ಹಿಂತಿರುಗಿ lim-1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y>lim) {
            errno = ERANGE;
            ಹಿಂತಿರುಗಿ lim;
        }
    }
    ಹಿಂತಿರುಗಿ (y^neg)-neg;
}

ಸ್ಥಿರ ದೀರ್ಘ ದೀರ್ಘ scanexp(FFFILE *f, ಪೂರ್ಣಾಂಕ pok)
{
    ಪೂರ್ಣಾಂಕ c;
    ಪೂರ್ಣಾಂಕ x;
    ದೀರ್ಘ ದೀರ್ಘ y;
    ಪೂರ್ಣಾಂಕ neg = 0;

    c = shgetc(f);
    ಆದರೆ (c=='+' || c=='-') {
        neg = (c=='-');
        c = shgetc(f);
        ಆದರೆ (c-'0'>=10U && pok) shunget(f);
    }
    ಆದರೆ (c-'0'>=10U) {
        shunget(f);
        ಹಿಂತಿರುಗಿ LLONG_MIN;
    }
    ಗಾಗಿ (x=0; c-'0'<10U && x<ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ/10; c = shgetc(f))
        x = 10*x + (c-'0');
    ಗಾಗಿ (y=x; c-'0'<10U && y<LLONG_MAX/100; c = shgetc(f))
        y = 10*y + (c-'0');
    ಗಾಗಿ (; c-'0'<10U; c = shgetc(f));
    shunget(f);
    ಹಿಂತಿರುಗಿ neg ? -y : y;
}

#ವ್ಯಾಖ್ಯಾನಿಸು LD_B1B_DIG 2
#ವ್ಯಾಖ್ಯಾನಿಸು LD_B1B_MAX 9007199, 254740991
#ವ್ಯಾಖ್ಯಾನಿಸು KMAX 128
#ವ್ಯಾಖ್ಯಾನಿಸು ಮುಖವಾಡ (KMAX-1)

ಸ್ಥಿರ ದ್ವಿಗುಣ decfloat(FFFILE *f, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ emin, ಪೂರ್ಣಾಂಕ sign, ಪೂರ್ಣಾಂಕ pok)
{
    uint32_t x[KMAX];
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t th[] = { LD_B1B_MAX };
    ಪೂರ್ಣಾಂಕ i, j, k, a, z;
    ದೀರ್ಘ ದೀರ್ಘ lrp=0, dc=0;
    ದೀರ್ಘ ದೀರ್ಘ e10=0;
    ಪೂರ್ಣಾಂಕ lnz = 0;
    ಪೂರ್ಣಾಂಕ gotdig = 0, gotrad = 0;
    ಪೂರ್ಣಾಂಕ rp;
    ಪೂರ್ಣಾಂಕ e2;
    ಪೂರ್ಣಾಂಕ emax = -emin-ಬಿಟ್ಟುಗಳು+3;
    ಪೂರ್ಣಾಂಕ denormal = 0;
    ದ್ವಿಗುಣ y;
    ದ್ವಿಗುಣ frac=0;
    ದ್ವಿಗುಣ bias=0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ p10s[] = { 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000 };

    j=0;
    k=0;

    /* Don't let leading zeros consume buffer space */
    ಗಾಗಿ (; c=='0'; c = shgetc(f)) gotdig=1;
    ಆದರೆ (c=='.') {
        gotrad = 1;
        ಗಾಗಿ (c = shgetc(f); c=='0'; c = shgetc(f)) gotdig=1, lrp--;
    }

    x[0] = 0;
    ಗಾಗಿ (; c-'0'<10U || c=='.'; c = shgetc(f)) {
        ಆದರೆ (c == '.') {
            ಆದರೆ (gotrad) ನಿಲ್ಲಿಸು;
            gotrad = 1;
            lrp = dc;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (k < KMAX-3) {
            dc++;
            ಆದರೆ (c!='0') lnz = dc;
            ಆದರೆ (j) x[k] = x[k]*10 + c-'0';
            ಇಲ್ಲದಿದ್ದರೆ x[k] = c-'0';
            ಆದರೆ (++j==9) {
                k++;
                j=0;
            }
            gotdig=1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dc++;
            ಆದರೆ (c!='0') {
                lnz = (KMAX-4)*9;
                x[KMAX-4] |= 1;
            }
        }
    }
    ಆದರೆ (!gotrad) lrp=dc;

    ಆದರೆ (gotdig && (c|32)=='e') {
        e10 = scanexp(f, pok);
        ಆದರೆ (e10 == LLONG_MIN) {
            ಆದರೆ (pok) {
                shunget(f);
            } ಇಲ್ಲದಿದ್ದರೆ {
                shlim(f, 0);
                ಹಿಂತಿರುಗಿ 0;
            }
            e10 = 0;
        }
        lrp += e10;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c>=0) {
        shunget(f);
    }
    ಆದರೆ (!gotdig) {
        errno = EINVAL;
        shlim(f, 0);
        ಹಿಂತಿರುಗಿ 0;
    }

    /* Handle zero specially to avoid nasty special cases later */
    ಆದರೆ (!x[0]) ಹಿಂತಿರುಗಿ sign * 0.0;

    /* Optimize small integers (w/no exponent) and over/under-flow */
    ಆದರೆ (lrp==dc && dc<10 && (ಬಿಟ್ಟುಗಳು>30 || x[0]>>ಬಿಟ್ಟುಗಳು==0))
        ಹಿಂತಿರುಗಿ sign * (ದ್ವಿಗುಣ)x[0];
    ಆದರೆ (lrp > -emin/2) {
        errno = ERANGE;
        ಹಿಂತಿರುಗಿ sign * DBL_MAX * DBL_MAX;
    }
    ಆದರೆ (lrp < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ಹಿಂತಿರುಗಿ sign * DBL_MIN * DBL_MIN;
    }

    /* Align incomplete final B1B digit */
    ಆದರೆ (j) {
        ಗಾಗಿ (; j<9; j++) x[k]*=10;
        k++;
        j=0;
    }

    a = 0;
    z = k;
    e2 = 0;
    rp = lrp;

    /* Optimize small to mid-size integers (even in exp. notation) */
    ಆದರೆ (lnz<9 && lnz<=rp && rp < 18) {
        ಪೂರ್ಣಾಂಕ bitlim;
        ಆದರೆ (rp == 9) ಹಿಂತಿರುಗಿ sign * (ದ್ವಿಗುಣ)x[0];
        ಆದರೆ (rp < 9) ಹಿಂತಿರುಗಿ sign * (ದ್ವಿಗುಣ)x[0] / p10s[8-rp];
        bitlim = ಬಿಟ್ಟುಗಳು-3*(ಪೂರ್ಣಾಂಕ)(rp-9);
        ಆದರೆ (bitlim>30 || x[0]>>bitlim==0)
            ಹಿಂತಿರುಗಿ sign * (ದ್ವಿಗುಣ)x[0] * p10s[rp-10];
    }

    /* Drop trailing zeros */
    ಗಾಗಿ (; !x[z-1]; z--);

    /* Align radix point to B1B digit boundary */
    ಆದರೆ (rp % 9) {
        ಪೂರ್ಣಾಂಕ rpm9 = rp>=0 ? rp%9 : rp%9+9;
        ಪೂರ್ಣಾಂಕ p10 = p10s[8-rpm9];
        uint32_t ವಾಹಕ = 0;
        ಗಾಗಿ (k=a; k!=z; k++) {
            uint32_t tmp = x[k] % p10;
            x[k] = x[k]/p10 + ವಾಹಕ;
            ವಾಹಕ = 1000000000/p10 * tmp;
            ಆದರೆ (k==a && !x[k]) {
                a = (a+1 & ಮುಖವಾಡ);
                rp -= 9;
            }
        }
        ಆದರೆ (ವಾಹಕ) x[z++] = ವಾಹಕ;
        rp += 9-rpm9;
    }

    /* Upscale until desired number of bits are left of radix point */
    ಆಗ (rp < 9*LD_B1B_DIG || (rp == 9*LD_B1B_DIG && x[a]<th[0])) {
        uint32_t ವಾಹಕ = 0;
        e2 -= 29;
        ಗಾಗಿ (k=(z-1 & ಮುಖವಾಡ); ; k=(k-1 & ಮುಖವಾಡ)) {
            uint64_t tmp = ((uint64_t)x[k] << 29) + ವಾಹಕ;
            ಆದರೆ (tmp > 1000000000) {
                ವಾಹಕ = tmp / 1000000000;
                x[k] = tmp % 1000000000;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ವಾಹಕ = 0;
                x[k] = tmp;
            }
            ಆದರೆ (k==(z-1 & ಮುಖವಾಡ) && k!=a && !x[k]) z = k;
            ಆದರೆ (k==a) ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (ವಾಹಕ) {
            rp += 9;
            a = (a-1 & ಮುಖವಾಡ);
            ಆದರೆ (a == z) {
                z = (z-1 & ಮುಖವಾಡ);
                x[z-1 & ಮುಖವಾಡ] |= x[z];
            }
            x[a] = ವಾಹಕ;
        }
    }

    /* Downscale until exactly number of bits are left of radix point */
    ಗಾಗಿ (;;) {
        uint32_t ವಾಹಕ = 0;
        ಪೂರ್ಣಾಂಕ sh = 1;
        ಗಾಗಿ (i=0; i<LD_B1B_DIG; i++) {
            k = (a+i & ಮುಖವಾಡ);
            ಆದರೆ (k == z || x[k] < th[i]) {
                i=LD_B1B_DIG;
                ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ (x[a+i & ಮುಖವಾಡ] > th[i]) ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (i==LD_B1B_DIG && rp==9*LD_B1B_DIG) ನಿಲ್ಲಿಸು;
        /* FIXME: find a way to compute optimal sh */
        ಆದರೆ (rp > 9+9*LD_B1B_DIG) sh = 9;
        e2 += sh;
        ಗಾಗಿ (k=a; k!=z; k=(k+1 & ಮುಖವಾಡ)) {
            uint32_t tmp = x[k] & (1<<sh)-1;
            x[k] = (x[k]>>sh) + ವಾಹಕ;
            ವಾಹಕ = (1000000000>>sh) * tmp;
            ಆದರೆ (k==a && !x[k]) {
                a = (a+1 & ಮುಖವಾಡ);
                i--;
                rp -= 9;
            }
        }
        ಆದರೆ (ವಾಹಕ) {
            ಆದರೆ ((z+1 & ಮುಖವಾಡ) != a) {
                x[z] = ವಾಹಕ;
                z = (z+1 & ಮುಖವಾಡ);
            } ಇಲ್ಲದಿದ್ದರೆ x[z-1 & ಮುಖವಾಡ] |= 1;
        }
    }

    /* Assemble desired bits into floating point variable */
    ಗಾಗಿ (y=i=0; i<LD_B1B_DIG; i++) {
        ಆದರೆ ((a+i & ಮುಖವಾಡ)==z) x[(z=(z+1 & ಮುಖವಾಡ))-1 & ಮುಖವಾಡ] = 0;
        y = 1000000000.0L * y + x[a+i & ಮುಖವಾಡ];
    }

    y *= sign;

    /* Limit precision for denormal results */
    ಆದರೆ (ಬಿಟ್ಟುಗಳು > DBL_MANT_DIG+e2-emin) {
        ಬಿಟ್ಟುಗಳು = DBL_MANT_DIG+e2-emin;
        ಆದರೆ (ಬಿಟ್ಟುಗಳು<0) ಬಿಟ್ಟುಗಳು=0;
        denormal = 1;
    }

    /* Calculate bias term to force rounding, move out lower bits */
    ಆದರೆ (ಬಿಟ್ಟುಗಳು < DBL_MANT_DIG) {
        bias = copysign(scalbn(1, 2*DBL_MANT_DIG-ಬಿಟ್ಟುಗಳು-1), y);
        frac = fmod(y, scalbn(1, DBL_MANT_DIG-ಬಿಟ್ಟುಗಳು));
        y -= frac;
        y += bias;
    }

    /* Process tail of decimal input so it can affect rounding */
    ಆದರೆ ((a+i & ಮುಖವಾಡ) != z) {
        uint32_t t = x[a+i & ಮುಖವಾಡ];
        ಆದರೆ (t < 500000000 && (t || (a+i+1 & ಮುಖವಾಡ) != z))
            frac += 0.25*sign;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t > 500000000)
            frac += 0.75*sign;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t == 500000000) {
            ಆದರೆ ((a+i+1 & ಮುಖವಾಡ) == z)
                frac += 0.5*sign;
            ಇಲ್ಲದಿದ್ದರೆ
                frac += 0.75*sign;
        }
        ಆದರೆ (DBL_MANT_DIG-ಬಿಟ್ಟುಗಳು >= 2 && !fmod(frac, 1))
            frac++;
    }

    y += frac;
    y -= bias;

    ಆದರೆ ((e2+DBL_MANT_DIG & ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) > emax-5) {
        ಆದರೆ (fabs(y) >= ಘಾತ(2, DBL_MANT_DIG)) {
            ಆದರೆ (denormal && ಬಿಟ್ಟುಗಳು==DBL_MANT_DIG+e2-emin)
                denormal = 0;
            y *= 0.5;
            e2++;
        }
        ಆದರೆ (e2+DBL_MANT_DIG>emax || (denormal && frac))
            errno = ERANGE;
    }

    ಹಿಂತಿರುಗಿ scalbn(y, e2);
}

ಸ್ಥಿರ ದ್ವಿಗುಣ hexfloat(FFFILE *f, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ emin, ಪೂರ್ಣಾಂಕ sign, ಪೂರ್ಣಾಂಕ pok)
{
    uint32_t x = 0;
    ದ್ವಿಗುಣ y = 0;
    ದ್ವಿಗುಣ scale = 1;
    ದ್ವಿಗುಣ bias = 0;
    ಪೂರ್ಣಾಂಕ gottail = 0, gotrad = 0, gotdig = 0;
    ದೀರ್ಘ ದೀರ್ಘ rp = 0;
    ದೀರ್ಘ ದೀರ್ಘ dc = 0;
    ದೀರ್ಘ ದೀರ್ಘ e2 = 0;
    ಪೂರ್ಣಾಂಕ d;
    ಪೂರ್ಣಾಂಕ c;

    c = shgetc(f);

    /* Skip leading zeros */
    ಗಾಗಿ (; c=='0'; c = shgetc(f))
        gotdig = 1;

    ಆದರೆ (c=='.') {
        gotrad = 1;
        c = shgetc(f);
        /* Count zeros after the radix point before significand */
        ಗಾಗಿ (rp=0; c=='0'; c = shgetc(f), rp--) gotdig = 1;
    }

    ಗಾಗಿ (; c-'0'<10U || (c|32)-'a'<6U || c=='.'; c = shgetc(f)) {
        ಆದರೆ (c=='.') {
            ಆದರೆ (gotrad) ನಿಲ್ಲಿಸು;
            rp = dc;
            gotrad = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            gotdig = 1;
            ಆದರೆ (c > '9') d = (c|32)+10-'a';
            ಇಲ್ಲದಿದ್ದರೆ d = c-'0';
            ಆದರೆ (dc<8) {
                x = x*16 + d;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dc < DBL_MANT_DIG/4+1) {
                y += d*(scale/=16);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d && !gottail) {
                y += 0.5*scale;
                gottail = 1;
            }
            dc++;
        }
    }
    ಆದರೆ (!gotdig) {
        shunget(f);
        ಆದರೆ (pok) {
            shunget(f);
            ಆದರೆ (gotrad) shunget(f);
        } ಇಲ್ಲದಿದ್ದರೆ {
            shlim(f, 0);
        }
        ಹಿಂತಿರುಗಿ sign * 0.0;
    }
    ಆದರೆ (!gotrad) rp = dc;
    ಆಗ (dc<8) x *= 16, dc++;
    ಆದರೆ ((c|32)=='p') {
        e2 = scanexp(f, pok);
        ಆದರೆ (e2 == LLONG_MIN) {
            ಆದರೆ (pok) {
                shunget(f);
            } ಇಲ್ಲದಿದ್ದರೆ {
                shlim(f, 0);
                ಹಿಂತಿರುಗಿ 0;
            }
            e2 = 0;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        shunget(f);
    }
    e2 += 4*rp - 32;

    ಆದರೆ (!x) ಹಿಂತಿರುಗಿ sign * 0.0;
    ಆದರೆ (e2 > -emin) {
        errno = ERANGE;
        ಹಿಂತಿರುಗಿ sign * DBL_MAX * DBL_MAX;
    }
    ಆದರೆ (e2 < emin-2*DBL_MANT_DIG) {
        errno = ERANGE;
        ಹಿಂತಿರುಗಿ sign * DBL_MIN * DBL_MIN;
    }

    ಆಗ (x < 0x80000000) {
        ಆದರೆ (y>=0.5) {
            x += x + 1;
            y += y - 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            x += x;
            y += y;
        }
        e2--;
    }

    ಆದರೆ (ಬಿಟ್ಟುಗಳು > 32+e2-emin) {
        ಬಿಟ್ಟುಗಳು = 32+e2-emin;
        ಆದರೆ (ಬಿಟ್ಟುಗಳು<0) ಬಿಟ್ಟುಗಳು=0;
    }

    ಆದರೆ (ಬಿಟ್ಟುಗಳು < DBL_MANT_DIG)
        bias = copysign(scalbn(1, 32+DBL_MANT_DIG-ಬಿಟ್ಟುಗಳು-1), sign);

    ಆದರೆ (ಬಿಟ್ಟುಗಳು<32 && y && !(x&1)) x++, y=0;

    y = bias + sign*(ದ್ವಿಗುಣ)x + sign*y;
    y -= bias;

    ಆದರೆ (!y) errno = ERANGE;

    ಹಿಂತಿರುಗಿ scalbn(y, e2);
}

ಸ್ಥಿರ ದ್ವಿಗುಣ fffloatscan(FFFILE *f, ಪೂರ್ಣಾಂಕ prec, ಪೂರ್ಣಾಂಕ pok)
{
    ಪೂರ್ಣಾಂಕ sign = 1;
    size_t i;
    ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು;
    ಪೂರ್ಣಾಂಕ emin;
    ಪೂರ್ಣಾಂಕ c;

    ಆಯ್ಕೆ (prec) {
    ಸ್ಥಿತಿ 0:
        ಬಿಟ್ಟುಗಳು = FLT_MANT_DIG;
        emin = FLT_MIN_EXP-ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 1:
        ಬಿಟ್ಟುಗಳು = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
        ಬಿಟ್ಟುಗಳು = DBL_MANT_DIG;
        emin = DBL_MIN_EXP-ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆಗ (av_isspace((c = shgetc(f))));

    ಆದರೆ (c=='+' || c=='-') {
        sign -= 2*(c=='-');
        c = shgetc(f);
    }

    ಗಾಗಿ (i=0; i<8 && (c|32)=="infinity"[i]; i++)
        ಆದರೆ (i<7) c = shgetc(f);
    ಆದರೆ (i==3 || i==8 || (i>3 && pok)) {
        ಆದರೆ (i!=8) {
            shunget(f);
            ಆದರೆ (pok) ಗಾಗಿ (; i>3; i--) shunget(f);
        }
        ಹಿಂತಿರುಗಿ sign * INFINITY;
    }
    ಆದರೆ (!i) ಗಾಗಿ (i=0; i<3 && (c|32)=="nan"[i]; i++)
        ಆದರೆ (i<2) c = shgetc(f);
    ಆದರೆ (i==3) {
        ಆದರೆ (shgetc(f) != '(') {
            shunget(f);
            ಹಿಂತಿರುಗಿ NAN;
        }
        ಗಾಗಿ (i=1; ; i++) {
            c = shgetc(f);
            ಆದರೆ (c-'0'<10U || c-'A'<26U || c-'a'<26U || c=='_')
                ಮುಂದುವರಿ;
            ಆದರೆ (c==')') ಹಿಂತಿರುಗಿ NAN;
            shunget(f);
            ಆದರೆ (!pok) {
                errno = EINVAL;
                shlim(f, 0);
                ಹಿಂತಿರುಗಿ 0;
            }
            ಆಗ (i--) shunget(f);
            ಹಿಂತಿರುಗಿ NAN;
        }
    }

    ಆದರೆ (i) {
        shunget(f);
        errno = EINVAL;
        shlim(f, 0);
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (c=='0') {
        c = shgetc(f);
        ಆದರೆ ((c|32) == 'x')
            ಹಿಂತಿರುಗಿ hexfloat(f, ಬಿಟ್ಟುಗಳು, emin, sign, pok);
        shunget(f);
        c = '0';
    }

    ಹಿಂತಿರುಗಿ decfloat(f, c, ಬಿಟ್ಟುಗಳು, emin, sign, pok);
}

ಸ್ಥಿರ ಶೂನ್ಯ *arg_n(va_list ap, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ n)
{
    ಶೂನ್ಯ *p;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
    va_list ap2;
    va_copy(ap2, ap);
    ಗಾಗಿ (i=n; i>1; i--) va_arg(ap2, ಶೂನ್ಯ *);
    p = va_arg(ap2, ಶೂನ್ಯ *);
    va_end(ap2);
    ಹಿಂತಿರುಗಿ p;
}

ಸ್ಥಿರ ಶೂನ್ಯ store_int(ಶೂನ್ಯ *dest, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ i)
{
    ಆದರೆ (!dest) ಹಿಂತಿರುಗಿ;
    ಆಯ್ಕೆ (ಗಾತ್ರ_2) {
    ಸ್ಥಿತಿ ಗಾತ್ರ_hh:
        *(ಅಕ್ಷರ *)dest = i;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಗಾತ್ರ_h:
        *(ಗಿಡ್ಡ *)dest = i;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಗಾತ್ರ_def:
        *(ಪೂರ್ಣಾಂಕ *)dest = i;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಗಾತ್ರ_l:
        *(ದೀರ್ಘ *)dest = i;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಗಾತ್ರ_ll:
        *(ದೀರ್ಘ ದೀರ್ಘ *)dest = i;
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ff_vfscanf(FFFILE *f, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ap)
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
    ಪೂರ್ಣಾಂಕ ತಳ_2;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p;
    ಪೂರ್ಣಾಂಕ c, t;
    ಅಕ್ಷರ *s;
    ಶೂನ್ಯ *dest=ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ invert;
    ಪೂರ್ಣಾಂಕ matches=0;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ x;
    ದ್ವಿಗುಣ y;
    ptrdiff_t pos = 0;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ scanset[257];
    size_t i;

    ಗಾಗಿ (p=(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)fmt; *p; p++) {

        ಆದರೆ (av_isspace(*p)) {
            ಆಗ (av_isspace(p[1])) p++;
            shlim(f, 0);
            ಆಗ (av_isspace(shgetc(f)));
            shunget(f);
            pos += shcnt(f);
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (*p != '%' || p[1] == '%') {
            shlim(f, 0);
            ಆದರೆ (*p == '%') {
                p++;
                ಆಗ (av_isspace((c=shgetc(f))));
            } ಇಲ್ಲದಿದ್ದರೆ {
                c = shgetc(f);
            }
            ಆದರೆ (c!=*p) {
                shunget(f);
                ಆದರೆ (c<0) ಹೋಗು ಒಳಹರಿವು_fail;
                ಹೋಗು ಹೊಂದಿಕೆ_fail;
            }
            pos += shcnt(f);
            ಮುಂದುವರಿ;
        }

        p++;
        ಆದರೆ (*p=='*') {
            dest = 0; p++;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (av_isdigit(*p) && p[1]=='$') {
            dest = arg_n(ap, *p-'0'); p+=2;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dest = va_arg(ap, ಶೂನ್ಯ *);
        }

        ಗಾಗಿ (ಅಗಲ=0; av_isdigit(*p); p++) {
            ಅಗಲ = 10*ಅಗಲ + *p - '0';
        }

        ಆದರೆ (*p=='m') {
            s = 0;
            p++;
        }

        ಗಾತ್ರ_2 = ಗಾತ್ರ_def;
        ಆಯ್ಕೆ (*p++) {
        ಸ್ಥಿತಿ 'h':
            ಆದರೆ (*p == 'h') p++, ಗಾತ್ರ_2 = ಗಾತ್ರ_hh;
            ಇಲ್ಲದಿದ್ದರೆ ಗಾತ್ರ_2 = ಗಾತ್ರ_h;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'l':
            ಆದರೆ (*p == 'l') p++, ಗಾತ್ರ_2 = ಗಾತ್ರ_ll;
            ಇಲ್ಲದಿದ್ದರೆ ಗಾತ್ರ_2 = ಗಾತ್ರ_l;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'j':
            ಗಾತ್ರ_2 = ಗಾತ್ರ_ll;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'z':
        ಸ್ಥಿತಿ 't':
            ಗಾತ್ರ_2 = ಗಾತ್ರ_l;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'L':
            ಗಾತ್ರ_2 = ಗಾತ್ರ_L;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'd': ಸ್ಥಿತಿ 'i': ಸ್ಥಿತಿ 'o': ಸ್ಥಿತಿ 'u': ಸ್ಥಿತಿ 'x':
        ಸ್ಥಿತಿ 'a': ಸ್ಥಿತಿ 'e': ಸ್ಥಿತಿ 'f': ಸ್ಥಿತಿ 'g':
        ಸ್ಥಿತಿ 'A': ಸ್ಥಿತಿ 'E': ಸ್ಥಿತಿ 'F': ಸ್ಥಿತಿ 'G': ಸ್ಥಿತಿ 'X':
        ಸ್ಥಿತಿ 's': ಸ್ಥಿತಿ 'c': ಸ್ಥಿತಿ '[':
        ಸ್ಥಿತಿ 'S': ಸ್ಥಿತಿ 'C':
        ಸ್ಥಿತಿ 'p': ಸ್ಥಿತಿ 'n':
            p--;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹೋಗು fmt_fail;
        }

        t = *p;

        /* C or S */
        ಆದರೆ ((t&0x2f) == 3) {
            t |= 32;
            ಗಾತ್ರ_2 = ಗಾತ್ರ_l;
        }

        ಆಯ್ಕೆ (t) {
            ಸ್ಥಿತಿ 'c':
                ಆದರೆ (ಅಗಲ < 1) ಅಗಲ = 1;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ '[':
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 'n':
                store_int(dest, ಗಾತ್ರ_2, pos);
                /* do not increment match count, etc! */
                ಮುಂದುವರಿ;
            ಪೂರ್ವನಿಯೋಜಿತ:
                shlim(f, 0);
                ಆಗ (av_isspace(shgetc(f)));
                shunget(f);
                pos += shcnt(f);
        }

        shlim(f, ಅಗಲ);
        ಆದರೆ (shgetc(f) < 0) ಹೋಗು ಒಳಹರಿವು_fail;
        shunget(f);

        ಆಯ್ಕೆ (t) {
            ಸ್ಥಿತಿ 's':
            ಸ್ಥಿತಿ 'c':
            ಸ್ಥಿತಿ '[':
                ಆದರೆ (t == 'c' || t == 's') {
                    memset(scanset, -1, ಗಾತ್ರ scanset);
                    scanset[0] = 0;
                    ಆದರೆ (t == 's') {
                        scanset[1 + '\t'] = 0;
                        scanset[1 + '\n'] = 0;
                        scanset[1 + '\v'] = 0;
                        scanset[1 + '\f'] = 0;
                        scanset[1 + '\r'] = 0;
                        scanset[1 + ' ' ] = 0;
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಆದರೆ (*++p == '^') p++, invert = 1;
                    ಇಲ್ಲದಿದ್ದರೆ invert = 0;
                    memset(scanset, invert, ಗಾತ್ರ scanset);
                    scanset[0] = 0;
                    ಆದರೆ (*p == '-') p++, scanset[1+'-'] = 1-invert;
                    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*p == ']') p++, scanset[1+']'] = 1-invert;
                    ಗಾಗಿ (; *p != ']'; p++) {
                        ಆದರೆ (!*p) ಹೋಗು fmt_fail;
                        ಆದರೆ (*p=='-' && p[1] && p[1] != ']')
                            ಗಾಗಿ (c=p++[-1]; c<*p; c++)
                                scanset[1+c] = 1-invert;
                        scanset[1+*p] = 1-invert;
                    }
                }
                s = 0;
                i = 0;
                ಆದರೆ ((s = dest)) {
                    ಆಗ (scanset[(c=shgetc(f))+1])
                        s[i++] = c;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಆಗ (scanset[(c=shgetc(f))+1]);
                }
                shunget(f);
                ಆದರೆ (!shcnt(f)) ಹೋಗು ಹೊಂದಿಕೆ_fail;
                ಆದರೆ (t == 'c' && shcnt(f) != ಅಗಲ) ಹೋಗು ಹೊಂದಿಕೆ_fail;
                ಆದರೆ (t != 'c') {
                    ಆದರೆ (s) s[i] = 0;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 'p':
            ಸ್ಥಿತಿ 'X':
            ಸ್ಥಿತಿ 'x':
                ತಳ_2 = 16;
                ಹೋಗು int_common;
            ಸ್ಥಿತಿ 'o':
                ತಳ_2 = 8;
                ಹೋಗು int_common;
            ಸ್ಥಿತಿ 'd':
            ಸ್ಥಿತಿ 'u':
                ತಳ_2 = 10;
                ಹೋಗು int_common;
            ಸ್ಥಿತಿ 'i':
                ತಳ_2 = 0;
int_common:
                x = ffintscan(f, ತಳ_2, 0, ULLONG_MAX);
                ಆದರೆ (!shcnt(f))
                    ಹೋಗು ಹೊಂದಿಕೆ_fail;
                ಆದರೆ (t=='p' && dest)
                    *(ಶೂನ್ಯ **)dest = (ಶೂನ್ಯ *)(uintptr_t)x;
                ಇಲ್ಲದಿದ್ದರೆ
                    store_int(dest, ಗಾತ್ರ_2, x);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 'a': ಸ್ಥಿತಿ 'A':
            ಸ್ಥಿತಿ 'e': ಸ್ಥಿತಿ 'E':
            ಸ್ಥಿತಿ 'f': ಸ್ಥಿತಿ 'F':
            ಸ್ಥಿತಿ 'g': ಸ್ಥಿತಿ 'G':
                y = fffloatscan(f, ಗಾತ್ರ_2, 0);
                ಆದರೆ (!shcnt(f))
                    ಹೋಗು ಹೊಂದಿಕೆ_fail;
                ಆದರೆ (dest) {
                    ಆಯ್ಕೆ (ಗಾತ್ರ_2) {
                    ಸ್ಥಿತಿ ಗಾತ್ರ_def:
                        *(ದಶಮಾಂಶ *)dest = y;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ ಗಾತ್ರ_l:
                        *(ದ್ವಿಗುಣ *)dest = y;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ ಗಾತ್ರ_L:
                        *(ದ್ವಿಗುಣ *)dest = y;
                        ನಿಲ್ಲಿಸು;
                    }
                }
                ನಿಲ್ಲಿಸು;
        }

        pos += shcnt(f);
        ಆದರೆ (dest) matches++;
    }
    ಆದರೆ (0) {
fmt_fail:
ಒಳಹರಿವು_fail:
        ಆದರೆ (!matches) matches--;
    }
ಹೊಂದಿಕೆ_fail:
    ಹಿಂತಿರುಗಿ matches;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ff_vsscanf(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ap)
{
    FFFILE f = {
        .buf = (ಶೂನ್ಯ *)s, .cookie = (ಶೂನ್ಯ *)s,
        .ಪಠ = ffstring_read,
    };

    ಹಿಂತಿರುಗಿ ff_vfscanf(&f, fmt, ap);
}

ಪೂರ್ಣಾಂಕ av_sscanf(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *string, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *format, ...)
{
    ಪೂರ್ಣಾಂಕ ret;
    va_list ap;
    va_start(ap, format);
    ret = ff_vsscanf(string, format, ap);
    va_end(ap);
    ಹಿಂತಿರುಗಿ ret;
}
