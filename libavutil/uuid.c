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

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uuid.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"

ਪੂਰਨ av_uuid_parse(ਅਚਲ ਅੱਖਰ *ਵਿੱਚ_2, AVUUID uu)
{
    ਜੇ (ਲੜੀ_ਲੰਬਾਈ(ਵਿੱਚ_2) != 36)
        ਵਾਪਸ AVERROR(EINVAL);

    ਵਾਪਸ av_uuid_parse_range(ਵਿੱਚ_2, ਵਿੱਚ_2 + 36, uu);
}

ਸਥਿਰ ਪੂਰਨ xdigit_ਮੰਜ਼ਿਲ_int(ਅੱਖਰ c)
{
    c = av_tolower(c);

    ਜੇ (c >= 'a' && c <= 'f')
        ਵਾਪਸ c - 'a' + 10;

    ਜੇ (c >= '0' && c <= '9')
        ਵਾਪਸ c - '0';

    ਵਾਪਸ -1;
}

ਪੂਰਨ av_uuid_parse_range(ਅਚਲ ਅੱਖਰ *ਵਿੱਚ_ਸ਼ੁਰੂ, ਅਚਲ ਅੱਖਰ *ਵਿੱਚ_ਸਿਰਾ, AVUUID uu)
{
    ਪੂਰਨ i;
    ਅਚਲ ਅੱਖਰ *cp;

    ਜੇ ((ਵਿੱਚ_ਸਿਰਾ - ਵਿੱਚ_ਸ਼ੁਰੂ) != 36)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (i = 0, cp = ਵਿੱਚ_ਸ਼ੁਰੂ; i < 16; i++) {
        ਪੂਰਨ hi;
        ਪੂਰਨ lo;

        ਜੇ (i == 4 || i == 6 || i == 8 || i == 10)
            cp++;

        hi = xdigit_ਮੰਜ਼ਿਲ_int(*cp++);
        lo = xdigit_ਮੰਜ਼ਿਲ_int(*cp++);

        ਜੇ (hi == -1 || lo == -1)
            ਵਾਪਸ AVERROR(EINVAL);

        uu[i] = (hi << 4) + lo;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ attribute_nonstring ਅਚਲ ਅੱਖਰ hexdigits_ਹੇਠਲਾ[16] = "0123456789abcdef";

ਖਾਲੀ av_uuid_unparse(ਅਚਲ AVUUID uuid, ਅੱਖਰ *ਬਾਹਰਲਾ)
{
    ਅੱਖਰ *p = ਬਾਹਰਲਾ;

    ਲਈ (ਪੂਰਨ i = 0; i < 16; i++) {
        uint8_t tmp;

        ਜੇ (i == 4 || i == 6 || i == 8 || i == 10)
            *p++ = '-';

        tmp = uuid[i];
        *p++ = hexdigits_ਹੇਠਲਾ[tmp >> 4];
        *p++ = hexdigits_ਹੇਠਲਾ[tmp & 15];
    }

    *p = '\0';
}

ਪੂਰਨ av_uuid_urn_parse(ਅਚਲ ਅੱਖਰ *ਵਿੱਚ_2, AVUUID uu)
{
    ਜੇ (av_stristr(ਵਿੱਚ_2, "urn:uuid:") != ਵਿੱਚ_2)
        ਵਾਪਸ AVERROR(EINVAL);

    ਵਾਪਸ av_uuid_parse(ਵਿੱਚ_2 + 9, uu);
}
