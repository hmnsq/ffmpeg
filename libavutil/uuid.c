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

/*
 * Copyright (C) 1996, 1997 Theodore Ts'o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/**
 * @file
 * UUID parsing and serialization utilities.
 * The library treat the UUID as an opaque sequence of 16 unsigned bytes,
 * i.e. ignoring the internal layout of the UUID, which depends on the type
 * of the UUID.
 *
 * @author Pierre-Anthony Lemieux <pal@palemieux.com>
 * @author Zane van Iperen <zane@zanevaniperen.com>
 */

#अन्तर्भाव "attributes_internal.h"
#अन्तर्भाव "uuid.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "avstring.h"

पूर्णाङ्क av_uuid_parse(ध्रुव वर्ण *in, AVUUID uu)
{
    यदि (strlen(in) != 36)
        प्रत्यागम AVERROR(EINVAL);

    प्रत्यागम av_uuid_parse_range(in, in + 36, uu);
}

स्थिर पूर्णाङ्क xdigit_to_int(वर्ण c)
{
    c = av_tolower(c);

    यदि (c >= 'a' && c <= 'f')
        प्रत्यागम c - 'a' + 10;

    यदि (c >= '0' && c <= '9')
        प्रत्यागम c - '0';

    प्रत्यागम -1;
}

पूर्णाङ्क av_uuid_parse_range(ध्रुव वर्ण *in_start, ध्रुव वर्ण *in_end, AVUUID uu)
{
    पूर्णाङ्क i;
    ध्रुव वर्ण *cp;

    यदि ((in_end - in_start) != 36)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (i = 0, cp = in_start; i < 16; i++) {
        पूर्णाङ्क hi;
        पूर्णाङ्क lo;

        यदि (i == 4 || i == 6 || i == 8 || i == 10)
            cp++;

        hi = xdigit_to_int(*cp++);
        lo = xdigit_to_int(*cp++);

        यदि (hi == -1 || lo == -1)
            प्रत्यागम AVERROR(EINVAL);

        uu[i] = (hi << 4) + lo;
    }

    प्रत्यागम 0;
}

स्थिर attribute_nonstring ध्रुव वर्ण hexdigits_lower[16] = "0123456789abcdef";

शून्य av_uuid_unparse(ध्रुव AVUUID uuid, वर्ण *out)
{
    वर्ण *p = out;

    प्रति (पूर्णाङ्क i = 0; i < 16; i++) {
        uint8_t tmp;

        यदि (i == 4 || i == 6 || i == 8 || i == 10)
            *p++ = '-';

        tmp = uuid[i];
        *p++ = hexdigits_lower[tmp >> 4];
        *p++ = hexdigits_lower[tmp & 15];
    }

    *p = '\0';
}

पूर्णाङ्क av_uuid_urn_parse(ध्रुव वर्ण *in, AVUUID uu)
{
    यदि (av_stristr(in, "urn:uuid:") != in)
        प्रत्यागम AVERROR(EINVAL);

    प्रत्यागम av_uuid_parse(in + 9, uu);
}
