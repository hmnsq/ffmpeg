/*
 * Compute the Adler-32 checksum of a data stream.
 * This is a modified version based on adler32.c from the zlib library.
 *
 * Copyright (C) 1995 Mark Adler
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/**
 * @file
 * Computes the Adler-32 checksum of a data stream
 *
 * This is a modified version based on adler32.c from the zlib library.
 * @author Mark Adler
 * @ingroup lavu_adler32
 */

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "adler32.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ತಳ 65521L /* largest prime smaller than 65536 */

#ವ್ಯಾಖ್ಯಾನಿಸು DO1(buf)  { s1 += *buf++; s2 += s1; }
#ವ್ಯಾಖ್ಯಾನಿಸು DO4(buf)  DO1(buf); DO1(buf); DO1(buf); DO1(buf);
#ವ್ಯಾಖ್ಯಾನಿಸು DO16(buf) DO4(buf); DO4(buf); DO4(buf); DO4(buf);

AVAdler av_adler32_update(AVAdler adler, ಸ್ಥಿರಾಂಕ uint8_t *buf, size_t len)
{
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ s1 = adler & 0xffff;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ s2 = adler >> 16;

    ಆಗ (len > 0) {
#ಆದರೆ HAVE_FAST_64_ಬಿಟ್ && HAVE_FAST_UNALIGNED && !CONFIG_SMALL
        ಚಿಹ್ನೆರಹಿತ len2 = FFMIN((len-1) & ~7, 23*8);
        ಆದರೆ (len2) {
            uint64_t a1= 0;
            uint64_t a2= 0;
            uint64_t b1= 0;
            uint64_t b2= 0;
            len -= len2;
            s2 += s1*len2;
            ಆಗ (len2 >= 8) {
                uint64_t v = AV_RN64(buf);
                a2 += a1;
                b2 += b1;
                a1 +=  v    &0x00FF00FF00FF00FF;
                b1 += (v>>8)&0x00FF00FF00FF00FF;
                len2 -= 8;
                buf+=8;
            }

            //We combine the 8 interleaved adler32 checksums without overflows
            //Decreasing the number of iterations would allow below code to be
            //simplified but would likely be slower due to the fewer iterations
            //of the inner loop
            s1 += ((a1+b1)*0x1000100010001)>>48;
            s2 += ((((a2&0xFFFF0000FFFF)+(b2&0xFFFF0000FFFF)+((a2>>16)&0xFFFF0000FFFF)+((b2>>16)&0xFFFF0000FFFF))*0x800000008)>>32)
#ಆದರೆ HAVE_BIGENDIAN
                 + 2*((b1*0x1000200030004)>>48)
                 +   ((a1*0x1000100010001)>>48)
                 + 2*((a1*0x0000100020003)>>48);
#ಇಲ್ಲದಿದ್ದರೆ
                 + 2*((a1*0x4000300020001)>>48)
                 +   ((b1*0x1000100010001)>>48)
                 + 2*((b1*0x3000200010000)>>48);
#ಆದರೆ_ಅಂತ್ಯ
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ಆಗ (len > 4  && s2 < (1U << 31)) {
            DO4(buf);
            len -= 4;
        }
#ಆದರೆ_ಅಂತ್ಯ
        DO1(buf); len--;
        s1 %= ತಳ;
        s2 %= ತಳ;
    }
    ಹಿಂತಿರುಗಿ (s2 << 16) | s1;
}
