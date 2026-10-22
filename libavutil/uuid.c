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

#அந்தர்பாவ "attributes_internal.h"
#அந்தர்பாவ "uuid.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "avstring.h"

முழு av_uuid_parse(மாறிலி எழுத்து *in, AVUUID uu)
{
    எனில் (strlen(in) != 36)
        திரும்பு AVERROR(EINVAL);

    திரும்பு av_uuid_parse_range(in, in + 36, uu);
}

நிலையான முழு xdigit_to_int(எழுத்து c)
{
    c = av_tolower(c);

    எனில் (c >= 'a' && c <= 'f')
        திரும்பு c - 'a' + 10;

    எனில் (c >= '0' && c <= '9')
        திரும்பு c - '0';

    திரும்பு -1;
}

முழு av_uuid_parse_range(மாறிலி எழுத்து *in_start, மாறிலி எழுத்து *in_end, AVUUID uu)
{
    முழு i;
    மாறிலி எழுத்து *cp;

    எனில் ((in_end - in_start) != 36)
        திரும்பு AVERROR(EINVAL);

    க்கு (i = 0, cp = in_start; i < 16; i++) {
        முழு hi;
        முழு lo;

        எனில் (i == 4 || i == 6 || i == 8 || i == 10)
            cp++;

        hi = xdigit_to_int(*cp++);
        lo = xdigit_to_int(*cp++);

        எனில் (hi == -1 || lo == -1)
            திரும்பு AVERROR(EINVAL);

        uu[i] = (hi << 4) + lo;
    }

    திரும்பு 0;
}

நிலையான attribute_nonstring மாறிலி எழுத்து hexdigits_lower[16] = "0123456789abcdef";

வெறுமை av_uuid_unparse(மாறிலி AVUUID uuid, எழுத்து *out)
{
    எழுத்து *p = out;

    க்கு (முழு i = 0; i < 16; i++) {
        uint8_t tmp;

        எனில் (i == 4 || i == 6 || i == 8 || i == 10)
            *p++ = '-';

        tmp = uuid[i];
        *p++ = hexdigits_lower[tmp >> 4];
        *p++ = hexdigits_lower[tmp & 15];
    }

    *p = '\0';
}

முழு av_uuid_urn_parse(மாறிலி எழுத்து *in, AVUUID uu)
{
    எனில் (av_stristr(in, "urn:uuid:") != in)
        திரும்பு AVERROR(EINVAL);

    திரும்பு av_uuid_parse(in + 9, uu);
}
