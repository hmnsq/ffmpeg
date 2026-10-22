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

#অন্তর্ভাব "attributes_internal.h"
#অন্তর্ভাব "uuid.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "avstring.h"

পূর্ণাঙ্ক av_uuid_parse(ধ্রুব বর্ণ *in, AVUUID uu)
{
    যদি (strlen(in) != 36)
        প্রত্যাগম AVERROR(EINVAL);

    প্রত্যাগম av_uuid_parse_range(in, in + 36, uu);
}

স্থির পূর্ণাঙ্ক xdigit_to_int(বর্ণ c)
{
    c = av_tolower(c);

    যদি (c >= 'a' && c <= 'f')
        প্রত্যাগম c - 'a' + 10;

    যদি (c >= '0' && c <= '9')
        প্রত্যাগম c - '0';

    প্রত্যাগম -1;
}

পূর্ণাঙ্ক av_uuid_parse_range(ধ্রুব বর্ণ *in_start, ধ্রুব বর্ণ *in_end, AVUUID uu)
{
    পূর্ণাঙ্ক i;
    ধ্রুব বর্ণ *cp;

    যদি ((in_end - in_start) != 36)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (i = 0, cp = in_start; i < 16; i++) {
        পূর্ণাঙ্ক hi;
        পূর্ণাঙ্ক lo;

        যদি (i == 4 || i == 6 || i == 8 || i == 10)
            cp++;

        hi = xdigit_to_int(*cp++);
        lo = xdigit_to_int(*cp++);

        যদি (hi == -1 || lo == -1)
            প্রত্যাগম AVERROR(EINVAL);

        uu[i] = (hi << 4) + lo;
    }

    প্রত্যাগম 0;
}

স্থির attribute_nonstring ধ্রুব বর্ণ hexdigits_lower[16] = "0123456789abcdef";

শূন্য av_uuid_unparse(ধ্রুব AVUUID uuid, বর্ণ *out)
{
    বর্ণ *p = out;

    প্রতি (পূর্ণাঙ্ক i = 0; i < 16; i++) {
        uint8_t tmp;

        যদি (i == 4 || i == 6 || i == 8 || i == 10)
            *p++ = '-';

        tmp = uuid[i];
        *p++ = hexdigits_lower[tmp >> 4];
        *p++ = hexdigits_lower[tmp & 15];
    }

    *p = '\0';
}

পূর্ণাঙ্ক av_uuid_urn_parse(ধ্রুব বর্ণ *in, AVUUID uu)
{
    যদি (av_stristr(in, "urn:uuid:") != in)
        প্রত্যাগম AVERROR(EINVAL);

    প্রত্যাগম av_uuid_parse(in + 9, uu);
}
