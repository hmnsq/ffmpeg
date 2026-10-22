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

/**
 * @file
 * misc parsing utilities
 */

#अन्तर्भाव <time.h>

#अन्तर्भाव "avstring.h"
#अन्तर्भाव "avutil.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "eval.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "random_seed.h"
#अन्तर्भाव "time_internal.h"
#अन्तर्भाव "parseutils.h"
#अन्तर्भाव "time.h"

#ifdef TEST

#define av_get_random_seed av_get_random_seed_deterministic
स्थिर uint32_t av_get_random_seed_deterministic(शून्य);

#define av_gettime() 1331972053200000

#endif

पूर्णाङ्क av_parse_ratio(AVRational *q, ध्रुव वर्ण *str, पूर्णाङ्क max,
                   पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    वर्ण c;
    पूर्णाङ्क ret;

    जइ (sscanf(str, "%d:%d%c", &q->अङ्कः, &q->den, &c) != 2) {
        द्विगुण d;
        ret = av_व्यञ्जकम्_parse_and_eval(&d, str, रिक्त, रिक्त,
                                     रिक्त, रिक्त, रिक्त, रिक्त,
                                     रिक्त, log_offset, log_ctx);
        जइ (ret < 0)
            प्रत्यागम ret;
        *q = av_d2q(d, max);
    } अण्णहा {
        av_reduce(&q->अङ्कः, &q->den, q->अङ्कः, q->den, max);
    }

    प्रत्यागम 0;
}

प्रकारनिर्देश संरचना VideoSizeAbbr {
    ध्रुव वर्ण *abbr;
    पूर्णाङ्क width, height;
} VideoSizeAbbr;

प्रकारनिर्देश संरचना VideoRateAbbr {
    ध्रुव वर्ण *abbr;
    AVRational rate;
} VideoRateAbbr;

स्थिर ध्रुव VideoSizeAbbr video_size_abbrs[] = {
    { "ntsc",      720, 480 },
    { "pal",       720, 576 },
    { "qntsc",     352, 240 }, /* VCD compliant NTSC */
    { "qpal",      352, 288 }, /* VCD compliant PAL */
    { "sntsc",     640, 480 }, /* square pixel NTSC */
    { "spal",      768, 576 }, /* square pixel PAL */
    { "film",      352, 240 },
    { "ntsc-film", 352, 240 },
    { "sqcif",     128,  96 },
    { "qcif",      176, 144 },
    { "cif",       352, 288 },
    { "4cif",      704, 576 },
    { "16cif",    1408,1152 },
    { "qqvga",     160, 120 },
    { "qvga",      320, 240 },
    { "vga",       640, 480 },
    { "svga",      800, 600 },
    { "xga",      1024, 768 },
    { "uxga",     1600,1200 },
    { "qxga",     2048,1536 },
    { "sxga",     1280,1024 },
    { "qsxga",    2560,2048 },
    { "hsxga",    5120,4096 },
    { "wvga",      852, 480 },
    { "wxga",     1366, 768 },
    { "wsxga",    1600,1024 },
    { "wuxga",    1920,1200 },
    { "woxga",    2560,1600 },
    { "wqhd",     2560,1440 },
    { "wqsxga",   3200,2048 },
    { "wquxga",   3840,2400 },
    { "whsxga",   6400,4096 },
    { "whuxga",   7680,4800 },
    { "cga",       320, 200 },
    { "ega",       640, 350 },
    { "hd480",     852, 480 },
    { "hd720",    1280, 720 },
    { "hd1080",   1920,1080 },
    { "quadhd",   2560,1440 },
    { "2k",       2048,1080 }, /* Digital Cinema System Specification */
    { "2kdci",    2048,1080 },
    { "2kflat",   1998,1080 },
    { "2kscope",  2048, 858 },
    { "4k",       4096,2160 }, /* Digital Cinema System Specification */
    { "4kdci",    4096,2160 },
    { "4kflat",   3996,2160 },
    { "4kscope",  4096,1716 },
    { "nhd",       640,360  },
    { "hqvga",     240,160  },
    { "wqvga",     400,240  },
    { "fwqvga",    432,240  },
    { "hvga",      480,320  },
    { "qhd",       960,540  },
    { "uhd2160",  3840,2160 },
    { "uhd4320",  7680,4320 },
};

स्थिर ध्रुव VideoRateAbbr video_rate_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

स्थिर ध्रुव वर्ण *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

पूर्णाङ्क av_parse_video_size(पूर्णाङ्क *width_ptr, पूर्णाङ्क *height_ptr, ध्रुव वर्ण *str)
{
    पूर्णाङ्क i;
    पूर्णाङ्क n = FF_ARRAY_ELEMS(video_size_abbrs);
    ध्रुव वर्ण *p;
    पूर्णाङ्क width = 0, height = 0;

    प्रति (i = 0; i < n; i++) {
        जइ (!strcmp(video_size_abbrs[i].abbr, str)) {
            width  = video_size_abbrs[i].width;
            height = video_size_abbrs[i].height;
            भङ्ग;
        }
    }
    जइ (i == n) {
        width = strtol(str, (शून्य*)&p, 10);
        जइ (*p)
            p++;
        height = strtol(p, (शून्य*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        जइ (*p)
            प्रत्यागम AVERROR(EINVAL);
    }
    जइ (width <= 0 || height <= 0)
        प्रत्यागम AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    प्रत्यागम 0;
}

पूर्णाङ्क av_parse_video_rate(AVRational *rate, ध्रुव वर्ण *arg)
{
    पूर्णाङ्क i, ret;
    पूर्णाङ्क n = FF_ARRAY_ELEMS(video_rate_abbrs);

    /* First, we check our abbreviation table */
    प्रति (i = 0; i < n; ++i)
        जइ (!strcmp(video_rate_abbrs[i].abbr, arg)) {
            *rate = video_rate_abbrs[i].rate;
            प्रत्यागम 0;
        }

    /* Then, we try to parse it as fraction */
    जइ ((ret = av_parse_ratio_quiet(rate, arg, 1001000)) < 0)
        प्रत्यागम ret;
    जइ (!rate->अङ्कः || !rate->den)
        जइ ((ret = av_parse_ratio_quiet(rate, arg, INT_MAX)) < 0)
            प्रत्यागम ret;
    जइ (rate->अङ्कः <= 0 || rate->den <= 0)
        प्रत्यागम AVERROR(EINVAL);
    प्रत्यागम 0;
}

प्रकारनिर्देश संरचना ColorEntry {
    ध्रुव वर्ण *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} ColorEntry;

स्थिर ध्रुव ColorEntry color_table[] = {
    { "AliceBlue",            { 0xF0, 0xF8, 0xFF } },
    { "AntiqueWhite",         { 0xFA, 0xEB, 0xD7 } },
    { "Aqua",                 { 0x00, 0xFF, 0xFF } },
    { "Aquamarine",           { 0x7F, 0xFF, 0xD4 } },
    { "Azure",                { 0xF0, 0xFF, 0xFF } },
    { "Beige",                { 0xF5, 0xF5, 0xDC } },
    { "Bisque",               { 0xFF, 0xE4, 0xC4 } },
    { "Black",                { 0x00, 0x00, 0x00 } },
    { "BlanchedAlmond",       { 0xFF, 0xEB, 0xCD } },
    { "Blue",                 { 0x00, 0x00, 0xFF } },
    { "BlueViolet",           { 0x8A, 0x2B, 0xE2 } },
    { "Brown",                { 0xA5, 0x2A, 0x2A } },
    { "BurlyWood",            { 0xDE, 0xB8, 0x87 } },
    { "CadetBlue",            { 0x5F, 0x9E, 0xA0 } },
    { "Chartreuse",           { 0x7F, 0xFF, 0x00 } },
    { "Chocolate",            { 0xD2, 0x69, 0x1E } },
    { "Coral",                { 0xFF, 0x7F, 0x50 } },
    { "CornflowerBlue",       { 0x64, 0x95, 0xED } },
    { "Cornsilk",             { 0xFF, 0xF8, 0xDC } },
    { "Crimson",              { 0xDC, 0x14, 0x3C } },
    { "Cyan",                 { 0x00, 0xFF, 0xFF } },
    { "DarkBlue",             { 0x00, 0x00, 0x8B } },
    { "DarkCyan",             { 0x00, 0x8B, 0x8B } },
    { "DarkGoldenRod",        { 0xB8, 0x86, 0x0B } },
    { "DarkGray",             { 0xA9, 0xA9, 0xA9 } },
    { "DarkGreen",            { 0x00, 0x64, 0x00 } },
    { "DarkKhaki",            { 0xBD, 0xB7, 0x6B } },
    { "DarkMagenta",          { 0x8B, 0x00, 0x8B } },
    { "DarkOliveGreen",       { 0x55, 0x6B, 0x2F } },
    { "Darkorange",           { 0xFF, 0x8C, 0x00 } },
    { "DarkOrchid",           { 0x99, 0x32, 0xCC } },
    { "DarkRed",              { 0x8B, 0x00, 0x00 } },
    { "DarkSalmon",           { 0xE9, 0x96, 0x7A } },
    { "DarkSeaGreen",         { 0x8F, 0xBC, 0x8F } },
    { "DarkSlateBlue",        { 0x48, 0x3D, 0x8B } },
    { "DarkSlateGray",        { 0x2F, 0x4F, 0x4F } },
    { "DarkTurquoise",        { 0x00, 0xCE, 0xD1 } },
    { "DarkViolet",           { 0x94, 0x00, 0xD3 } },
    { "DeepPink",             { 0xFF, 0x14, 0x93 } },
    { "DeepSkyBlue",          { 0x00, 0xBF, 0xFF } },
    { "DimGray",              { 0x69, 0x69, 0x69 } },
    { "DodgerBlue",           { 0x1E, 0x90, 0xFF } },
    { "FireBrick",            { 0xB2, 0x22, 0x22 } },
    { "FloralWhite",          { 0xFF, 0xFA, 0xF0 } },
    { "ForestGreen",          { 0x22, 0x8B, 0x22 } },
    { "Fuchsia",              { 0xFF, 0x00, 0xFF } },
    { "Gainsboro",            { 0xDC, 0xDC, 0xDC } },
    { "GhostWhite",           { 0xF8, 0xF8, 0xFF } },
    { "Gold",                 { 0xFF, 0xD7, 0x00 } },
    { "GoldenRod",            { 0xDA, 0xA5, 0x20 } },
    { "Gray",                 { 0x80, 0x80, 0x80 } },
    { "Green",                { 0x00, 0x80, 0x00 } },
    { "GreenYellow",          { 0xAD, 0xFF, 0x2F } },
    { "HoneyDew",             { 0xF0, 0xFF, 0xF0 } },
    { "HotPink",              { 0xFF, 0x69, 0xB4 } },
    { "IndianRed",            { 0xCD, 0x5C, 0x5C } },
    { "Indigo",               { 0x4B, 0x00, 0x82 } },
    { "Ivory",                { 0xFF, 0xFF, 0xF0 } },
    { "Khaki",                { 0xF0, 0xE6, 0x8C } },
    { "Lavender",             { 0xE6, 0xE6, 0xFA } },
    { "LavenderBlush",        { 0xFF, 0xF0, 0xF5 } },
    { "LawnGreen",            { 0x7C, 0xFC, 0x00 } },
    { "LemonChiffon",         { 0xFF, 0xFA, 0xCD } },
    { "LightBlue",            { 0xAD, 0xD8, 0xE6 } },
    { "LightCoral",           { 0xF0, 0x80, 0x80 } },
    { "LightCyan",            { 0xE0, 0xFF, 0xFF } },
    { "LightGoldenRodYellow", { 0xFA, 0xFA, 0xD2 } },
    { "LightGreen",           { 0x90, 0xEE, 0x90 } },
    { "LightGrey",            { 0xD3, 0xD3, 0xD3 } },
    { "LightPink",            { 0xFF, 0xB6, 0xC1 } },
    { "LightSalmon",          { 0xFF, 0xA0, 0x7A } },
    { "LightSeaGreen",        { 0x20, 0xB2, 0xAA } },
    { "LightSkyBlue",         { 0x87, 0xCE, 0xFA } },
    { "LightSlateGray",       { 0x77, 0x88, 0x99 } },
    { "LightSteelBlue",       { 0xB0, 0xC4, 0xDE } },
    { "LightYellow",          { 0xFF, 0xFF, 0xE0 } },
    { "Lime",                 { 0x00, 0xFF, 0x00 } },
    { "LimeGreen",            { 0x32, 0xCD, 0x32 } },
    { "Linen",                { 0xFA, 0xF0, 0xE6 } },
    { "Magenta",              { 0xFF, 0x00, 0xFF } },
    { "Maroon",               { 0x80, 0x00, 0x00 } },
    { "MediumAquaMarine",     { 0x66, 0xCD, 0xAA } },
    { "MediumBlue",           { 0x00, 0x00, 0xCD } },
    { "MediumOrchid",         { 0xBA, 0x55, 0xD3 } },
    { "MediumPurple",         { 0x93, 0x70, 0xD8 } },
    { "MediumSeaGreen",       { 0x3C, 0xB3, 0x71 } },
    { "MediumSlateBlue",      { 0x7B, 0x68, 0xEE } },
    { "MediumSpringGreen",    { 0x00, 0xFA, 0x9A } },
    { "MediumTurquoise",      { 0x48, 0xD1, 0xCC } },
    { "MediumVioletRed",      { 0xC7, 0x15, 0x85 } },
    { "MidnightBlue",         { 0x19, 0x19, 0x70 } },
    { "MintCream",            { 0xF5, 0xFF, 0xFA } },
    { "MistyRose",            { 0xFF, 0xE4, 0xE1 } },
    { "Moccasin",             { 0xFF, 0xE4, 0xB5 } },
    { "NavajoWhite",          { 0xFF, 0xDE, 0xAD } },
    { "Navy",                 { 0x00, 0x00, 0x80 } },
    { "OldLace",              { 0xFD, 0xF5, 0xE6 } },
    { "Olive",                { 0x80, 0x80, 0x00 } },
    { "OliveDrab",            { 0x6B, 0x8E, 0x23 } },
    { "Orange",               { 0xFF, 0xA5, 0x00 } },
    { "OrangeRed",            { 0xFF, 0x45, 0x00 } },
    { "Orchid",               { 0xDA, 0x70, 0xD6 } },
    { "PaleGoldenRod",        { 0xEE, 0xE8, 0xAA } },
    { "PaleGreen",            { 0x98, 0xFB, 0x98 } },
    { "PaleTurquoise",        { 0xAF, 0xEE, 0xEE } },
    { "PaleVioletRed",        { 0xD8, 0x70, 0x93 } },
    { "PapayaWhip",           { 0xFF, 0xEF, 0xD5 } },
    { "PeachPuff",            { 0xFF, 0xDA, 0xB9 } },
    { "Peru",                 { 0xCD, 0x85, 0x3F } },
    { "Pink",                 { 0xFF, 0xC0, 0xCB } },
    { "Plum",                 { 0xDD, 0xA0, 0xDD } },
    { "PowderBlue",           { 0xB0, 0xE0, 0xE6 } },
    { "Purple",               { 0x80, 0x00, 0x80 } },
    { "Red",                  { 0xFF, 0x00, 0x00 } },
    { "RosyBrown",            { 0xBC, 0x8F, 0x8F } },
    { "RoyalBlue",            { 0x41, 0x69, 0xE1 } },
    { "SaddleBrown",          { 0x8B, 0x45, 0x13 } },
    { "Salmon",               { 0xFA, 0x80, 0x72 } },
    { "SandyBrown",           { 0xF4, 0xA4, 0x60 } },
    { "SeaGreen",             { 0x2E, 0x8B, 0x57 } },
    { "SeaShell",             { 0xFF, 0xF5, 0xEE } },
    { "Sienna",               { 0xA0, 0x52, 0x2D } },
    { "Silver",               { 0xC0, 0xC0, 0xC0 } },
    { "SkyBlue",              { 0x87, 0xCE, 0xEB } },
    { "SlateBlue",            { 0x6A, 0x5A, 0xCD } },
    { "SlateGray",            { 0x70, 0x80, 0x90 } },
    { "Snow",                 { 0xFF, 0xFA, 0xFA } },
    { "SpringGreen",          { 0x00, 0xFF, 0x7F } },
    { "SteelBlue",            { 0x46, 0x82, 0xB4 } },
    { "Tan",                  { 0xD2, 0xB4, 0x8C } },
    { "Teal",                 { 0x00, 0x80, 0x80 } },
    { "Thistle",              { 0xD8, 0xBF, 0xD8 } },
    { "Tomato",               { 0xFF, 0x63, 0x47 } },
    { "Turquoise",            { 0x40, 0xE0, 0xD0 } },
    { "Violet",               { 0xEE, 0x82, 0xEE } },
    { "Wheat",                { 0xF5, 0xDE, 0xB3 } },
    { "White",                { 0xFF, 0xFF, 0xFF } },
    { "WhiteSmoke",           { 0xF5, 0xF5, 0xF5 } },
    { "Yellow",               { 0xFF, 0xFF, 0x00 } },
    { "YellowGreen",          { 0x9A, 0xCD, 0x32 } },
};

स्थिर पूर्णाङ्क color_table_compare(ध्रुव शून्य *lhs, ध्रुव शून्य *rhs)
{
    प्रत्यागम av_strcasecmp(lhs, ((ध्रुव ColorEntry *)rhs)->name);
}

#define ALPHA_SEP '@'

पूर्णाङ्क av_parse_color(uint8_t *rgba_color, ध्रुव वर्ण *color_string, पूर्णाङ्क slen,
                   शून्य *log_ctx)
{
    वर्ण *tail, color_string2[128];
    ध्रुव ColorEntry *entry;
    पूर्णाङ्क len, hex_offset = 0;

    जइ (color_string[0] == '#') {
        hex_offset = 1;
    } अण्णहा जइ (!strncmp(color_string, "0x", 2))
        hex_offset = 2;

    जइ (slen < 0)
        slen = strlen(color_string);
    av_strlcpy(color_string2, color_string + hex_offset,
               FFMIN(slen-hex_offset+1, परिमाण(color_string2)));
    जइ ((tail = strchr(color_string2, ALPHA_SEP)))
        *tail++ = 0;
    len = strlen(color_string2);
    rgba_color[3] = 255;

    जइ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        पूर्णाङ्क rgba = av_get_random_seed();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } अण्णहा जइ (hex_offset ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        वर्ण *tail;
        unsigned पूर्णाङ्क rgba = strtoul(color_string2, &tail, 16);

        जइ (*tail || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            प्रत्यागम AVERROR(EINVAL);
        }
        जइ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } अण्णहा {
        entry = bsearch(color_string2,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        परिमाण(ColorEntry),
                        color_table_compare);
        जइ (!entry) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            प्रत्यागम AVERROR(EINVAL);
        }
        memcpy(rgba_color, entry->rgb_color, 3);
    }

    जइ (tail) {
        द्विगुण alpha;
        ध्रुव वर्ण *alpha_string = tail;
        जइ (!strncmp(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &tail, 16);
        } अण्णहा {
            द्विगुण norm_alpha = strtod(alpha_string, &tail);
            जइ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            अण्णहा
                alpha = 255 * norm_alpha;
        }

        जइ (tail == alpha_string || *tail || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            प्रत्यागम AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    प्रत्यागम 0;
}

ध्रुव वर्ण *av_get_known_color_name(पूर्णाङ्क color_idx, ध्रुव uint8_t **rgbp)
{
    ध्रुव ColorEntry *color;

    जइ ((unsigned)color_idx >= FF_ARRAY_ELEMS(color_table))
        प्रत्यागम रिक्त;

    color = &color_table[color_idx];
    जइ (rgbp)
        *rgbp = color->rgb_color;

    प्रत्यागम color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
स्थिर पूर्णाङ्क date_get_अङ्कः(ध्रुव वर्ण **pp,
                        पूर्णाङ्क n_min, पूर्णाङ्क n_max, पूर्णाङ्क len_max)
{
    पूर्णाङ्क i, val, c;
    ध्रुव वर्ण *p;

    p = *pp;
    val = 0;
    प्रति(i = 0; i < len_max; i++) {
        c = *p;
        जइ (!av_isdigit(c))
            भङ्ग;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    जइ (p == *pp)
        प्रत्यागम -1;
    जइ (val < n_min || val > n_max)
        प्रत्यागम -1;
    *pp = p;
    प्रत्यागम val;
}

स्थिर पूर्णाङ्क date_get_month(ध्रुव वर्ण **pp) {
    पूर्णाङ्क i = 0;
    प्रति (; i < 12; i++) {
        जइ (!av_strncasecmp(*pp, months[i], 3)) {
            ध्रुव वर्ण *mo_full = months[i] + 3;
            पूर्णाङ्क len = strlen(mo_full);
            *pp += 3;
            जइ (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            प्रत्यागम i;
        }
    }
    प्रत्यागम -1;
}

वर्ण *av_small_strptime(ध्रुव वर्ण *p, ध्रुव वर्ण *fmt, संरचना tm *dt)
{
    पूर्णाङ्क c, val;

    जाव((c = *fmt++)) {
        जइ (c != '%') {
            जइ (av_isspace(c))
                प्रति (; *p && av_isspace(*p); p++);
            अण्णहा जइ (*p != c)
                प्रत्यागम रिक्त;
            अण्णहा p++;
            अनुवर्त;
        }

        c = *fmt++;
        विकल्प(c) {
        पक्ष 'H':
        पक्ष 'J':
            val = date_get_अङ्कः(&p, 0, c == 'H' ? 23 : INT_MAX, c == 'H' ? 2 : 4);

            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_hour = val;
            भङ्ग;
        पक्ष 'M':
            val = date_get_अङ्कः(&p, 0, 59, 2);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_min = val;
            भङ्ग;
        पक्ष 'S':
            val = date_get_अङ्कः(&p, 0, 59, 2);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_sec = val;
            भङ्ग;
        पक्ष 'Y':
            val = date_get_अङ्कः(&p, 0, 9999, 4);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_year = val - 1900;
            भङ्ग;
        पक्ष 'm':
            val = date_get_अङ्कः(&p, 1, 12, 2);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_mon = val - 1;
            भङ्ग;
        पक्ष 'd':
            val = date_get_अङ्कः(&p, 1, 31, 2);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_mday = val;
            भङ्ग;
        पक्ष 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            जइ (!p)
                प्रत्यागम रिक्त;
            भङ्ग;
        पक्ष 'b':
        पक्ष 'B':
        पक्ष 'h':
            val = date_get_month(&p);
            जइ (val == -1)
                प्रत्यागम रिक्त;
            dt->tm_mon = val;
            भङ्ग;
        पक्ष '%':
            जइ (*p++ != '%')
                प्रत्यागम रिक्त;
            भङ्ग;
        स्वभाव:
            प्रत्यागम रिक्त;
        }
    }

    प्रत्यागम (वर्ण*)p;
}

time_t av_timegm(संरचना tm *tm)
{
    time_t t;

    पूर्णाङ्क y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    जइ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    प्रत्यागम t;
}

पूर्णाङ्क av_parse_time(int64_t *timeval, ध्रुव वर्ण *timestr, पूर्णाङ्क duration)
{
    ध्रुव वर्ण *p, *q;
    int64_t t, now64;
    time_t now;
    संरचना tm dt = { 0 }, tmbuf;
    पूर्णाङ्क today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    पूर्णाङ्क i;
    स्थिर ध्रुव वर्ण * ध्रुव date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    स्थिर ध्रुव वर्ण * ध्रुव time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    स्थिर ध्रुव वर्ण * ध्रुव tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = रिक्त;
    *timeval = INT64_MIN;
    जइ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        जइ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            प्रत्यागम 0;
        }

        /* parse the year-month-day part */
        प्रति (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            जइ (q)
                भङ्ग;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        जइ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        जइ (*p == 'T' || *p == 't')
            p++;
        अण्णहा
            जाव (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        प्रति (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            जइ (q)
                भङ्ग;
        }
    } अण्णहा {
        /* parse timestr as a duration */
        जइ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        जइ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        जइ (!q) {
            वर्ण *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            जइ (o == p) /* the parsing didn't succeed */
                प्रत्यागम AVERROR(EINVAL);
            जइ (errno == ERANGE)
                प्रत्यागम AVERROR(ERANGE);
            q = o;
        } अण्णहा {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    जइ (!q)
        प्रत्यागम AVERROR(EINVAL);

    /* parse the .m... part */
    जइ (*q == '.') {
        पूर्णाङ्क n;
        q++;
        प्रति (n = 100000; n >= 1; n /= 10, q++) {
            जइ (!av_isdigit(*q))
                भङ्ग;
            microseconds += n * (*q - '0');
        }
        जाव (av_isdigit(*q))
            q++;
    }

    जइ (duration) {
        जइ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } अण्णहा जइ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } अण्णहा जइ (*q == 's')
            q++;
    } अण्णहा {
        पूर्णाङ्क is_utc = *q == 'Z' || *q == 'z';
        पूर्णाङ्क tzoffset = 0;
        q += is_utc;
        जइ (!today && !is_utc && (*q == '+' || *q == '-')) {
            संरचना tm tz = { 0 };
            पूर्णाङ्क sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            प्रति (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                जइ (q)
                    भङ्ग;
            }
            जइ (!q)
                प्रत्यागम AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        जइ (today) { /* fill in today's date */
            संरचना tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
            dt2.tm_hour = dt.tm_hour;
            dt2.tm_min  = dt.tm_min;
            dt2.tm_sec  = dt.tm_sec;
            dt = dt2;
        }
        dt.tm_isdst = is_utc ? 0 : -1;
        t = is_utc ? av_timegm(&dt) : mktime(&dt);
        t += tzoffset;
    }

    /* Check that we are at the end of the string */
    जइ (*q)
        प्रत्यागम AVERROR(EINVAL);

    जइ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        प्रत्यागम AVERROR(ERANGE);
    t *= suffix;
    जइ (INT64_MAX - microseconds < t)
        प्रत्यागम AVERROR(ERANGE);
    t += microseconds;
    जइ (t == INT64_MIN && negative)
        प्रत्यागम AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    प्रत्यागम 0;
}

पूर्णाङ्क av_find_info_tag(वर्ण *arg, पूर्णाङ्क arg_size, ध्रुव वर्ण *tag1, ध्रुव वर्ण *info)
{
    ध्रुव वर्ण *p;
    वर्ण tag[128], *q;

    p = info;
    जइ (*p == '?')
        p++;
    प्रति(;;) {
        q = tag;
        जाव (*p != '\0' && *p != '=' && *p != '&') {
            जइ ((q - tag) < परिमाण(tag) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        जइ (*p == '=') {
            p++;
            जाव (*p != '&' && *p != '\0') {
                जइ ((q - arg) < arg_size - 1) {
                    जइ (*p == '+')
                        *q++ = ' ';
                    अण्णहा
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        जइ (!strcmp(tag, tag1))
            प्रत्यागम 1;
        जइ (*p != '&')
            भङ्ग;
        p++;
    }
    प्रत्यागम 0;
}
