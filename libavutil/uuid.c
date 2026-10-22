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

#అన్తర్భావ "attributes_internal.h"
#అన్తర్భావ "uuid.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "avstring.h"

పూర్ణాంకం av_uuid_parse(స్థిరరాశి అక్షరం *లోపల, AVUUID uu)
{
    ఒకవేళ (అక్షరశ్రేణి_పొడవు(లోపల) != 36)
        తిరిగి AVERROR(EINVAL);

    తిరిగి av_uuid_parse_range(లోపల, లోపల + 36, uu);
}

స్థిర పూర్ణాంకం xdigit_గమ్యం_int(అక్షరం c)
{
    c = av_tolower(c);

    ఒకవేళ (c >= 'a' && c <= 'f')
        తిరిగి c - 'a' + 10;

    ఒకవేళ (c >= '0' && c <= '9')
        తిరిగి c - '0';

    తిరిగి -1;
}

పూర్ణాంకం av_uuid_parse_range(స్థిరరాశి అక్షరం *లోపల_ప్రారంభం, స్థిరరాశి అక్షరం *లోపల_చివర, AVUUID uu)
{
    పూర్ణాంకం i;
    స్థిరరాశి అక్షరం *cp;

    ఒకవేళ ((లోపల_చివర - లోపల_ప్రారంభం) != 36)
        తిరిగి AVERROR(EINVAL);

    కొరకు (i = 0, cp = లోపల_ప్రారంభం; i < 16; i++) {
        పూర్ణాంకం hi;
        పూర్ణాంకం lo;

        ఒకవేళ (i == 4 || i == 6 || i == 8 || i == 10)
            cp++;

        hi = xdigit_గమ్యం_int(*cp++);
        lo = xdigit_గమ్యం_int(*cp++);

        ఒకవేళ (hi == -1 || lo == -1)
            తిరిగి AVERROR(EINVAL);

        uu[i] = (hi << 4) + lo;
    }

    తిరిగి 0;
}

స్థిర attribute_nonstring స్థిరరాశి అక్షరం hexdigits_క్రింది[16] = "0123456789abcdef";

శూన్య av_uuid_unparse(స్థిరరాశి AVUUID uuid, అక్షరం *బహిర్గతం)
{
    అక్షరం *p = బహిర్గతం;

    కొరకు (పూర్ణాంకం i = 0; i < 16; i++) {
        uint8_t tmp;

        ఒకవేళ (i == 4 || i == 6 || i == 8 || i == 10)
            *p++ = '-';

        tmp = uuid[i];
        *p++ = hexdigits_క్రింది[tmp >> 4];
        *p++ = hexdigits_క్రింది[tmp & 15];
    }

    *p = '\0';
}

పూర్ణాంకం av_uuid_urn_parse(స్థిరరాశి అక్షరం *లోపల, AVUUID uu)
{
    ఒకవేళ (av_stristr(లోపల, "urn:uuid:") != లోపల)
        తిరిగి AVERROR(EINVAL);

    తిరిగి av_uuid_parse(లోపల + 9, uu);
}
