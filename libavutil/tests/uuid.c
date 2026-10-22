/*
 * Copyright (c) 2022 Pierre-Anthony Lemieux <pal@palemieux.com>
 *                    Zane van Iperen <zane@zanevaniperen.com>
 *
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

#അന്തര്ഭാവ "libavutil/uuid.h"
#അന്തര്ഭാവ "libavutil/log.h"

സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_1        = "6021b21e-894e-43ff-8317-1ca891c1c49b";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_1_UC     = "6021B21E-894E-43FF-8317-1CA891C1C49B";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_1_MIXED  = "6021b21e-894E-43fF-8317-1CA891C1c49b";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_1_URN    = "urn:uuid:6021b21e-894e-43ff-8317-1ca891c1c49b";
സ്ഥിതം സ്ഥിരം AVUUID UUID_1_BYTES = {0x60, 0x21, 0xb2, 0x1e, 0x89, 0x4e, 0x43, 0xff,
                                    0x83, 0x17, 0x1c, 0xa8, 0x91, 0xc1, 0xc4, 0x9b};

സ്ഥിതം സ്ഥിരം AVUUID UUID_NIL = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_BAD_1 = "16a2c9f8-afbc-4767-8621-8cb2b27599";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_BAD_2 = "75df62c2999b4bd38c9d8058fcde9123";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_BAD_3 = "a1b9a05e-f1d1-464g-a951-1ba0a374f02";
സ്ഥിതം സ്ഥിരം അക്ഷരം *UUID_BAD_4 = "279c66d432-7b39-41d5-966f-5e8138265c20";

പൂർണ്ണസംഖ്യ പ്രധാന(പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
    AVUUID uuid;
    AVUUID uuid2 = {0x32, 0xc7, 0x00, 0xc4, 0xd5, 0xd7, 0x42, 0x0,
                    0x93, 0xc0, 0x3b, 0x6d, 0xea, 0x1b, 0x20, 0x5b};

    /* test parsing */

    എങ്കിൽ (av_uuid_parse(UUID_1, uuid))
        തിരികെ 1;

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_1_BYTES))
        തിരികെ 1;

    /* test nil */

    av_uuid_nil(uuid);

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_NIL))
        തിരികെ 1;

    /* test equality */

    എങ്കിൽ (av_uuid_equal(UUID_1_BYTES, uuid2))
        തിരികെ 1;

    /* test copy */

    av_uuid_copy(uuid2, UUID_1_BYTES);

    എങ്കിൽ (!av_uuid_equal(uuid2, UUID_1_BYTES))
        തിരികെ 1;

    /* test uppercase parsing */

    എങ്കിൽ (av_uuid_parse(UUID_1_UC, uuid))
        തിരികെ 1;

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_1_BYTES))
        തിരികെ 1;

    /* test mixed-case parsing */

    എങ്കിൽ (av_uuid_parse(UUID_1_MIXED, uuid))
        തിരികെ 1;

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_1_BYTES))
        തിരികെ 1;

    /* test URN uuid parse */

    എങ്കിൽ (av_uuid_urn_parse(UUID_1_URN, uuid))
        തിരികെ 1;

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_1_BYTES))
        തിരികെ 1;

    /* test parse range */

    എങ്കിൽ (av_uuid_parse_range(UUID_1_URN + 9, UUID_1_URN + 45, uuid))
        തിരികെ 1;

    എങ്കിൽ (!av_uuid_equal(uuid, UUID_1_BYTES))
        തിരികെ 1;

    /* test bad parse range */

    എങ്കിൽ (!av_uuid_parse_range(UUID_1_URN + 9, UUID_1_URN + 44, uuid))
        തിരികെ 1;

    /* test bad parse range 2 */

    എങ്കിൽ (!av_uuid_parse_range(UUID_1_URN + 8, UUID_1_URN + 44, uuid))
        തിരികെ 1;

    /* test bad parse range 2 */

    എങ്കിൽ (!av_uuid_parse_range(UUID_1_URN + 8, UUID_1_URN + 45, uuid))
        തിരികെ 1;

    /* test bad uuid 1 */

    എങ്കിൽ (!av_uuid_parse(UUID_BAD_1, uuid))
        തിരികെ 1;

    /* test bad uuid 2 */

    എങ്കിൽ (!av_uuid_parse(UUID_BAD_2, uuid))
        തിരികെ 1;

    /* test bad uuid 3 */

    എങ്കിൽ (!av_uuid_parse(UUID_BAD_3, uuid))
        തിരികെ 1;

    /* test bad uuid 4 */

    എങ്കിൽ (!av_uuid_parse(UUID_BAD_4, uuid))
        തിരികെ 1;

    തിരികെ 0;
}
