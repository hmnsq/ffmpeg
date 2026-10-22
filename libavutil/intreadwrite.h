/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#अगर_अघोषित AVUTIL_INTREADWRITE_H
#घोषणा AVUTIL_INTREADWRITE_H

#समावेश <stdint.h>
#समावेश "libavutil/avconfig.h"
#समावेश "attributes.h"
#समावेश "bswap.h"

प्रकार जोड़ {
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8 [8];
    द्विगुन   f64;
    भग्न    f32[2];
} av_alias av_alias64;

प्रकार जोड़ {
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8 [4];
    भग्न    f32;
} av_alias av_alias32;

प्रकार जोड़ {
    uint16_t u16;
    uint8_t  u8 [2];
} av_alias av_alias16;

/*
 * Arch-specific headers can provide any combination of
 * AV_[RW][BLN](16|24|32|48|64) and AV_(COPY|SWAP|ZERO)(64|128) macros.
 * Preprocessor symbols must be defined, even if these are implemented
 * as inline functions.
 *
 * R/W means read/write, B/L/N means big/little/native endianness.
 * The following macros require aligned access, compared to their
 * unaligned variants: AV_(COPY|SWAP|ZERO)(64|128), AV_[RW]N[8-64]A.
 * Incorrect usage may range from abysmal performance to crash
 * depending on the platform.
 *
 * The unaligned variants are AV_[RW][BLN][8-64] and AV_COPY*U.
 */

#अगर_घोषित HAVE_AV_CONFIG_H

#समावेश "config.h"

#अगर ARCH_AARCH64
#   include "aarch64/intreadwrite.h"
#या_अगर ARCH_MIPS
#   include "mips/intreadwrite.h"
#या_अगर ARCH_PPC
#   include "ppc/intreadwrite.h"
#या_अगर ARCH_X86
#   include "x86/intreadwrite.h"
#पूर्ण_अगर

#पूर्ण_अगर /* HAVE_AV_CONFIG_H */

/*
 * Map AV_RNXX <-> AV_R[BL]XX for all variants provided by per-arch headers.
 */

#अगर AV_HAVE_BIGENDIAN

#   अगर    defined(AV_RN16) && !defined(AV_RB16)
#       define AV_RB16(p) AV_RN16(p)
#   elif !defined(AV_RN16) &&  defined(AV_RB16)
#       define AV_RN16(p) AV_RB16(p)
#   endif

#   अगर    defined(AV_WN16) && !defined(AV_WB16)
#       define AV_WB16(p, v) AV_WN16(p, v)
#   elif !defined(AV_WN16) &&  defined(AV_WB16)
#       define AV_WN16(p, v) AV_WB16(p, v)
#   endif

#   अगर    defined(AV_RN24) && !defined(AV_RB24)
#       define AV_RB24(p) AV_RN24(p)
#   elif !defined(AV_RN24) &&  defined(AV_RB24)
#       define AV_RN24(p) AV_RB24(p)
#   endif

#   अगर    defined(AV_WN24) && !defined(AV_WB24)
#       define AV_WB24(p, v) AV_WN24(p, v)
#   elif !defined(AV_WN24) &&  defined(AV_WB24)
#       define AV_WN24(p, v) AV_WB24(p, v)
#   endif

#   अगर    defined(AV_RN32) && !defined(AV_RB32)
#       define AV_RB32(p) AV_RN32(p)
#   elif !defined(AV_RN32) &&  defined(AV_RB32)
#       define AV_RN32(p) AV_RB32(p)
#   endif

#   अगर    defined(AV_WN32) && !defined(AV_WB32)
#       define AV_WB32(p, v) AV_WN32(p, v)
#   elif !defined(AV_WN32) &&  defined(AV_WB32)
#       define AV_WN32(p, v) AV_WB32(p, v)
#   endif

#   अगर    defined(AV_RN48) && !defined(AV_RB48)
#       define AV_RB48(p) AV_RN48(p)
#   elif !defined(AV_RN48) &&  defined(AV_RB48)
#       define AV_RN48(p) AV_RB48(p)
#   endif

#   अगर    defined(AV_WN48) && !defined(AV_WB48)
#       define AV_WB48(p, v) AV_WN48(p, v)
#   elif !defined(AV_WN48) &&  defined(AV_WB48)
#       define AV_WN48(p, v) AV_WB48(p, v)
#   endif

#   अगर    defined(AV_RN64) && !defined(AV_RB64)
#       define AV_RB64(p) AV_RN64(p)
#   elif !defined(AV_RN64) &&  defined(AV_RB64)
#       define AV_RN64(p) AV_RB64(p)
#   endif

#   अगर    defined(AV_WN64) && !defined(AV_WB64)
#       define AV_WB64(p, v) AV_WN64(p, v)
#   elif !defined(AV_WN64) &&  defined(AV_WB64)
#       define AV_WN64(p, v) AV_WB64(p, v)
#   endif

#अन्यथा /* AV_HAVE_BIGENDIAN */

#   अगर    defined(AV_RN16) && !defined(AV_RL16)
#       define AV_RL16(p) AV_RN16(p)
#   elif !defined(AV_RN16) &&  defined(AV_RL16)
#       define AV_RN16(p) AV_RL16(p)
#   endif

#   अगर    defined(AV_WN16) && !defined(AV_WL16)
#       define AV_WL16(p, v) AV_WN16(p, v)
#   elif !defined(AV_WN16) &&  defined(AV_WL16)
#       define AV_WN16(p, v) AV_WL16(p, v)
#   endif

#   अगर    defined(AV_RN24) && !defined(AV_RL24)
#       define AV_RL24(p) AV_RN24(p)
#   elif !defined(AV_RN24) &&  defined(AV_RL24)
#       define AV_RN24(p) AV_RL24(p)
#   endif

#   अगर    defined(AV_WN24) && !defined(AV_WL24)
#       define AV_WL24(p, v) AV_WN24(p, v)
#   elif !defined(AV_WN24) &&  defined(AV_WL24)
#       define AV_WN24(p, v) AV_WL24(p, v)
#   endif

#   अगर    defined(AV_RN32) && !defined(AV_RL32)
#       define AV_RL32(p) AV_RN32(p)
#   elif !defined(AV_RN32) &&  defined(AV_RL32)
#       define AV_RN32(p) AV_RL32(p)
#   endif

#   अगर    defined(AV_WN32) && !defined(AV_WL32)
#       define AV_WL32(p, v) AV_WN32(p, v)
#   elif !defined(AV_WN32) &&  defined(AV_WL32)
#       define AV_WN32(p, v) AV_WL32(p, v)
#   endif

#   अगर    defined(AV_RN48) && !defined(AV_RL48)
#       define AV_RL48(p) AV_RN48(p)
#   elif !defined(AV_RN48) &&  defined(AV_RL48)
#       define AV_RN48(p) AV_RL48(p)
#   endif

#   अगर    defined(AV_WN48) && !defined(AV_WL48)
#       define AV_WL48(p, v) AV_WN48(p, v)
#   elif !defined(AV_WN48) &&  defined(AV_WL48)
#       define AV_WN48(p, v) AV_WL48(p, v)
#   endif

#   अगर    defined(AV_RN64) && !defined(AV_RL64)
#       define AV_RL64(p) AV_RN64(p)
#   elif !defined(AV_RN64) &&  defined(AV_RL64)
#       define AV_RN64(p) AV_RL64(p)
#   endif

#   अगर    defined(AV_WN64) && !defined(AV_WL64)
#       define AV_WL64(p, v) AV_WN64(p, v)
#   elif !defined(AV_WN64) &&  defined(AV_WL64)
#       define AV_WN64(p, v) AV_WL64(p, v)
#   endif

#पूर्ण_अगर /* !AV_HAVE_BIGENDIAN */

/*
 * Define AV_[RW]N helper macros to simplify definitions not provided
 * by per-arch headers.
 */

#अगर defined(__GNUC__) || defined(__clang__)

जोड़ unaligned_64 { uint64_t l; } __attribute__((packed)) av_alias;
जोड़ unaligned_32 { uint32_t l; } __attribute__((packed)) av_alias;
जोड़ unaligned_16 { uint16_t l; } __attribute__((packed)) av_alias;

#   define AV_RN(s, p) (((स्थिर जोड़ unaligned_##s *) (p))->l)
#   define AV_WN(s, p, v) ((((जोड़ unaligned_##s *) (p))->l) = (v))

#या_अगर defined(_MSC_VER) && (defined(_M_ARM) || defined(_M_X64) || defined(_M_ARM64)) && AV_HAVE_FAST_UNALIGNED

#   define AV_RN(s, p) (*((स्थिर __unaligned uint##s##_t*)(p)))
#   define AV_WN(s, p, v) (*((__unaligned uint##s##_t*)(p)) = (v))

#या_अगर AV_HAVE_FAST_UNALIGNED

#   define AV_RN(s, p) (((स्थिर av_alias##s*)(p))->u##s)
#   define AV_WN(s, p, v) (((av_alias##s*)(p))->u##s = (v))

#अन्यथा

#अगर_अघोषित AV_RB16
#   define AV_RB16(x)                           \
    ((((स्थिर uint8_t*)(x))[0] << 8) |          \
      ((स्थिर uint8_t*)(x))[1])
#पूर्ण_अगर
#अगर_अघोषित AV_WB16
#   define AV_WB16(p, val) करो {                 \
        uint16_t d = (val);                     \
        ((uint8_t*)(p))[1] = (d);               \
        ((uint8_t*)(p))[0] = (d)>>8;            \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RL16
#   define AV_RL16(x)                           \
    ((((स्थिर uint8_t*)(x))[1] << 8) |          \
      ((स्थिर uint8_t*)(x))[0])
#पूर्ण_अगर
#अगर_अघोषित AV_WL16
#   define AV_WL16(p, val) करो {                 \
        uint16_t d = (val);                     \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RB32
#   define AV_RB32(x)                                \
    (((uint32_t)((स्थिर uint8_t*)(x))[0] << 24) |    \
               (((स्थिर uint8_t*)(x))[1] << 16) |    \
               (((स्थिर uint8_t*)(x))[2] <<  8) |    \
                ((स्थिर uint8_t*)(x))[3])
#पूर्ण_अगर
#अगर_अघोषित AV_WB32
#   define AV_WB32(p, val) करो {                 \
        uint32_t d = (val);                     \
        ((uint8_t*)(p))[3] = (d);               \
        ((uint8_t*)(p))[2] = (d)>>8;            \
        ((uint8_t*)(p))[1] = (d)>>16;           \
        ((uint8_t*)(p))[0] = (d)>>24;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RL32
#   define AV_RL32(x)                                \
    (((uint32_t)((स्थिर uint8_t*)(x))[3] << 24) |    \
               (((स्थिर uint8_t*)(x))[2] << 16) |    \
               (((स्थिर uint8_t*)(x))[1] <<  8) |    \
                ((स्थिर uint8_t*)(x))[0])
#पूर्ण_अगर
#अगर_अघोषित AV_WL32
#   define AV_WL32(p, val) करो {                 \
        uint32_t d = (val);                     \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[2] = (d)>>16;           \
        ((uint8_t*)(p))[3] = (d)>>24;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RB64
#   define AV_RB64(x)                                   \
    (((uint64_t)((स्थिर uint8_t*)(x))[0] << 56) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[1] << 48) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[2] << 40) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[3] << 32) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[4] << 24) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[5] << 16) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[6] <<  8) |       \
      (uint64_t)((स्थिर uint8_t*)(x))[7])
#पूर्ण_अगर
#अगर_अघोषित AV_WB64
#   define AV_WB64(p, val) करो {                 \
        uint64_t d = (val);                     \
        ((uint8_t*)(p))[7] = (d);               \
        ((uint8_t*)(p))[6] = (d)>>8;            \
        ((uint8_t*)(p))[5] = (d)>>16;           \
        ((uint8_t*)(p))[4] = (d)>>24;           \
        ((uint8_t*)(p))[3] = (d)>>32;           \
        ((uint8_t*)(p))[2] = (d)>>40;           \
        ((uint8_t*)(p))[1] = (d)>>48;           \
        ((uint8_t*)(p))[0] = (d)>>56;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RL64
#   define AV_RL64(x)                                   \
    (((uint64_t)((स्थिर uint8_t*)(x))[7] << 56) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[6] << 48) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[5] << 40) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[4] << 32) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[3] << 24) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[2] << 16) |       \
     ((uint64_t)((स्थिर uint8_t*)(x))[1] <<  8) |       \
      (uint64_t)((स्थिर uint8_t*)(x))[0])
#पूर्ण_अगर
#अगर_अघोषित AV_WL64
#   define AV_WL64(p, val) करो {                 \
        uint64_t d = (val);                     \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[2] = (d)>>16;           \
        ((uint8_t*)(p))[3] = (d)>>24;           \
        ((uint8_t*)(p))[4] = (d)>>32;           \
        ((uint8_t*)(p))[5] = (d)>>40;           \
        ((uint8_t*)(p))[6] = (d)>>48;           \
        ((uint8_t*)(p))[7] = (d)>>56;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर AV_HAVE_BIGENDIAN
#   define AV_RN(s, p)    AV_RB##s(p)
#   define AV_WN(s, p, v) AV_WB##s(p, v)
#अन्यथा
#   define AV_RN(s, p)    AV_RL##s(p)
#   define AV_WN(s, p, v) AV_WL##s(p, v)
#पूर्ण_अगर

#पूर्ण_अगर /* HAVE_FAST_UNALIGNED */

#अगर_अघोषित AV_RN16
#   define AV_RN16(p) AV_RN(16, p)
#पूर्ण_अगर

#अगर_अघोषित AV_RN32
#   define AV_RN32(p) AV_RN(32, p)
#पूर्ण_अगर

#अगर_अघोषित AV_RN64
#   define AV_RN64(p) AV_RN(64, p)
#पूर्ण_अगर

#अगर_अघोषित AV_WN16
#   define AV_WN16(p, v) AV_WN(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_WN32
#   define AV_WN32(p, v) AV_WN(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_WN64
#   define AV_WN64(p, v) AV_WN(64, p, v)
#पूर्ण_अगर

#अगर AV_HAVE_BIGENDIAN
#   define AV_RB(s, p)    AV_RN##s(p)
#   define AV_WB(s, p, v) AV_WN##s(p, v)
#   define AV_RL(s, p)    av_bswap##s(AV_RN##s(p))
#   define AV_WL(s, p, v) AV_WN##s(p, av_bswap##s(v))
#अन्यथा
#   define AV_RB(s, p)    av_bswap##s(AV_RN##s(p))
#   define AV_WB(s, p, v) AV_WN##s(p, av_bswap##s(v))
#   define AV_RL(s, p)    AV_RN##s(p)
#   define AV_WL(s, p, v) AV_WN##s(p, v)
#पूर्ण_अगर

#घोषणा AV_RB8(x)     (((स्थिर uint8_t*)(x))[0])
#घोषणा AV_WB8(p, d)  करो { ((uint8_t*)(p))[0] = (d); } जबतक(0)

#घोषणा AV_RL8(x)     AV_RB8(x)
#घोषणा AV_WL8(p, d)  AV_WB8(p, d)

#अगर_अघोषित AV_RB16
#   define AV_RB16(p)    AV_RB(16, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB16
#   define AV_WB16(p, v) AV_WB(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RL16
#   define AV_RL16(p)    AV_RL(16, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL16
#   define AV_WL16(p, v) AV_WL(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB32
#   define AV_RB32(p)    AV_RB(32, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB32
#   define AV_WB32(p, v) AV_WB(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RL32
#   define AV_RL32(p)    AV_RL(32, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL32
#   define AV_WL32(p, v) AV_WL(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB64
#   define AV_RB64(p)    AV_RB(64, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB64
#   define AV_WB64(p, v) AV_WB(64, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RL64
#   define AV_RL64(p)    AV_RL(64, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL64
#   define AV_WL64(p, v) AV_WL(64, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB24
#   define AV_RB24(x)                           \
    ((((स्थिर uint8_t*)(x))[0] << 16) |         \
     (((स्थिर uint8_t*)(x))[1] <<  8) |         \
      ((स्थिर uint8_t*)(x))[2])
#पूर्ण_अगर
#अगर_अघोषित AV_WB24
#   define AV_WB24(p, d) करो {                   \
        ((uint8_t*)(p))[2] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[0] = (d)>>16;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RL24
#   define AV_RL24(x)                           \
    ((((स्थिर uint8_t*)(x))[2] << 16) |         \
     (((स्थिर uint8_t*)(x))[1] <<  8) |         \
      ((स्थिर uint8_t*)(x))[0])
#पूर्ण_अगर
#अगर_अघोषित AV_WL24
#   define AV_WL24(p, d) करो {                   \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[2] = (d)>>16;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RB48
#   define AV_RB48(x)                                     \
    (((uint64_t)((स्थिर uint8_t*)(x))[0] << 40) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[1] << 32) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[2] << 24) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[3] << 16) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[4] <<  8) |         \
      (uint64_t)((स्थिर uint8_t*)(x))[5])
#पूर्ण_अगर
#अगर_अघोषित AV_WB48
#   define AV_WB48(p, darg) करो {                \
        uint64_t d = (darg);                    \
        ((uint8_t*)(p))[5] = (d);               \
        ((uint8_t*)(p))[4] = (d)>>8;            \
        ((uint8_t*)(p))[3] = (d)>>16;           \
        ((uint8_t*)(p))[2] = (d)>>24;           \
        ((uint8_t*)(p))[1] = (d)>>32;           \
        ((uint8_t*)(p))[0] = (d)>>40;           \
    } जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित AV_RL48
#   define AV_RL48(x)                                     \
    (((uint64_t)((स्थिर uint8_t*)(x))[5] << 40) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[4] << 32) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[3] << 24) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[2] << 16) |         \
     ((uint64_t)((स्थिर uint8_t*)(x))[1] <<  8) |         \
      (uint64_t)((स्थिर uint8_t*)(x))[0])
#पूर्ण_अगर
#अगर_अघोषित AV_WL48
#   define AV_WL48(p, darg) करो {                \
        uint64_t d = (darg);                    \
        ((uint8_t*)(p))[0] = (d);               \
        ((uint8_t*)(p))[1] = (d)>>8;            \
        ((uint8_t*)(p))[2] = (d)>>16;           \
        ((uint8_t*)(p))[3] = (d)>>24;           \
        ((uint8_t*)(p))[4] = (d)>>32;           \
        ((uint8_t*)(p))[5] = (d)>>40;           \
    } जबतक(0)
#पूर्ण_अगर

/*
 * The AV_[RW]NA macros access naturally aligned data
 * in a type-safe way.
 */

#घोषणा AV_RNA(s, p)    (((स्थिर av_alias##s*)(p))->u##s)
#घोषणा AV_WNA(s, p, v) (((av_alias##s*)(p))->u##s = (v))

#अगर_अघोषित AV_RN16A
#   define AV_RN16A(p) AV_RNA(16, p)
#पूर्ण_अगर

#अगर_अघोषित AV_RN32A
#   define AV_RN32A(p) AV_RNA(32, p)
#पूर्ण_अगर

#अगर_अघोषित AV_RN64A
#   define AV_RN64A(p) AV_RNA(64, p)
#पूर्ण_अगर

#अगर_अघोषित AV_WN16A
#   define AV_WN16A(p, v) AV_WNA(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_WN32A
#   define AV_WN32A(p, v) AV_WNA(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_WN64A
#   define AV_WN64A(p, v) AV_WNA(64, p, v)
#पूर्ण_अगर

#अगर AV_HAVE_BIGENDIAN
#   define AV_RLA(s, p)    av_bswap##s(AV_RN##s##A(p))
#   define AV_WLA(s, p, v) AV_WN##s##A(p, av_bswap##s(v))
#   define AV_RBA(s, p)    AV_RN##s##A(p)
#   define AV_WBA(s, p, v) AV_WN##s##A(p, v)
#अन्यथा
#   define AV_RLA(s, p)    AV_RN##s##A(p)
#   define AV_WLA(s, p, v) AV_WN##s##A(p, v)
#   define AV_RBA(s, p)    av_bswap##s(AV_RN##s##A(p))
#   define AV_WBA(s, p, v) AV_WN##s##A(p, av_bswap##s(v))
#पूर्ण_अगर

#अगर_अघोषित AV_RL16A
#   define AV_RL16A(p) AV_RLA(16, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL16A
#   define AV_WL16A(p, v) AV_WLA(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB16A
#   define AV_RB16A(p) AV_RBA(16, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB16A
#   define AV_WB16A(p, v) AV_WBA(16, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RL32A
#   define AV_RL32A(p) AV_RLA(32, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL32A
#   define AV_WL32A(p, v) AV_WLA(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB32A
#   define AV_RB32A(p) AV_RBA(32, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB32A
#   define AV_WB32A(p, v) AV_WBA(32, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RL64A
#   define AV_RL64A(p) AV_RLA(64, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WL64A
#   define AV_WL64A(p, v) AV_WLA(64, p, v)
#पूर्ण_अगर

#अगर_अघोषित AV_RB64A
#   define AV_RB64A(p) AV_RBA(64, p)
#पूर्ण_अगर
#अगर_अघोषित AV_WB64A
#   define AV_WB64A(p, v) AV_WBA(64, p, v)
#पूर्ण_अगर

/*
 * The AV_COPYxxU macros are suitable for copying data to/from unaligned
 * memory locations.
 */

#घोषणा AV_COPYU(n, d, s) AV_WN##n(d, AV_RN##n(s));

#अगर_अघोषित AV_COPY16U
#   define AV_COPY16U(d, s) AV_COPYU(16, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY32U
#   define AV_COPY32U(d, s) AV_COPYU(32, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY64U
#   define AV_COPY64U(d, s) AV_COPYU(64, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY128U
#   define AV_COPY128U(d, s)                                    \
    करो {                                                        \
        AV_COPY64U(d, s);                                       \
        AV_COPY64U((अक्षर *)(d) + 8, (स्थिर अक्षर *)(s) + 8);     \
    } जबतक(0)
#पूर्ण_अगर

/* Parameters for AV_COPY*, AV_SWAP*, AV_ZERO* must be
 * naturally aligned.
 */

#घोषणा AV_COPY(n, d, s) \
    (((av_alias##n*)(d))->u##n = ((स्थिर av_alias##n*)(s))->u##n)

#अगर_अघोषित AV_COPY16
#   define AV_COPY16(d, s) AV_COPY(16, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY32
#   define AV_COPY32(d, s) AV_COPY(32, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY64
#   define AV_COPY64(d, s) AV_COPY(64, d, s)
#पूर्ण_अगर

#अगर_अघोषित AV_COPY128
#   define AV_COPY128(d, s)                    \
    करो {                                       \
        AV_COPY64(d, s);                       \
        AV_COPY64((अक्षर*)(d)+8, (अक्षर*)(s)+8); \
    } जबतक(0)
#पूर्ण_अगर

#घोषणा AV_SWAP(n, a, b) FFSWAP(av_alias##n, *(av_alias##n*)(a), *(av_alias##n*)(b))

#अगर_अघोषित AV_SWAP64
#   define AV_SWAP64(a, b) AV_SWAP(64, a, b)
#पूर्ण_अगर

#घोषणा AV_ZERO(n, d) (((av_alias##n*)(d))->u##n = 0)

#अगर_अघोषित AV_ZERO16
#   define AV_ZERO16(d) AV_ZERO(16, d)
#पूर्ण_अगर

#अगर_अघोषित AV_ZERO32
#   define AV_ZERO32(d) AV_ZERO(32, d)
#पूर्ण_अगर

#अगर_अघोषित AV_ZERO64
#   define AV_ZERO64(d) AV_ZERO(64, d)
#पूर्ण_अगर

#अगर_अघोषित AV_ZERO128
#   define AV_ZERO128(d)         \
    करो {                         \
        AV_ZERO64(d);            \
        AV_ZERO64((अक्षर*)(d)+8); \
    } जबतक(0)
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_INTREADWRITE_H */
