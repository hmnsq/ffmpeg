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

#അന്തര്ഭാവ <time.h>

#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "eval.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "random_seed.h"
#അന്തര്ഭാവ "time_internal.h"
#അന്തര്ഭാവ "parseutils.h"
#അന്തര്ഭാവ "time.h"

#ifdef TEST

#define av_get_random_seed av_get_random_seed_deterministic
സ്ഥിതം uint32_t av_get_random_seed_deterministic(ശൂന്യം);

#define av_gettime() 1331972053200000

#endif

പൂർണ്ണസംഖ്യ av_parse_ratio(AVRational *q, സ്ഥിരം അക്ഷരം *str, പൂർണ്ണസംഖ്യ max,
                   പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    അക്ഷരം c;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (sscanf(str, "%d:%d%c", &q->അക്കം, &q->den, &c) != 2) {
        ഇരട്ട d;
        ret = av_വ്യഞ്ജകം_parse_and_eval(&d, str, ശൂന്യ, ശൂന്യ,
                                     ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ,
                                     ശൂന്യ, log_offset, log_ctx);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
        *q = av_d2q(d, max);
    } അല്ലെങ്കിൽ {
        av_reduce(&q->അക്കം, &q->den, q->അക്കം, q->den, max);
    }

    തിരികെ 0;
}

തരനിർവചനം ഘടന VideoSizeAbbr {
    സ്ഥിരം അക്ഷരം *abbr;
    പൂർണ്ണസംഖ്യ width, height;
} VideoSizeAbbr;

തരനിർവചനം ഘടന VideoRateAbbr {
    സ്ഥിരം അക്ഷരം *abbr;
    AVRational rate;
} VideoRateAbbr;

സ്ഥിതം സ്ഥിരം VideoSizeAbbr video_size_abbrs[] = {
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

സ്ഥിതം സ്ഥിരം VideoRateAbbr video_rate_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

സ്ഥിതം സ്ഥിരം അക്ഷരം *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

പൂർണ്ണസംഖ്യ av_parse_video_size(പൂർണ്ണസംഖ്യ *width_ptr, പൂർണ്ണസംഖ്യ *height_ptr, സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ i;
    പൂർണ്ണസംഖ്യ n = FF_ARRAY_ELEMS(video_size_abbrs);
    സ്ഥിരം അക്ഷരം *p;
    പൂർണ്ണസംഖ്യ width = 0, height = 0;

    വേണ്ടി (i = 0; i < n; i++) {
        എങ്കിൽ (!strcmp(video_size_abbrs[i].abbr, str)) {
            width  = video_size_abbrs[i].width;
            height = video_size_abbrs[i].height;
            നിർത്തുക;
        }
    }
    എങ്കിൽ (i == n) {
        width = strtol(str, (ശൂന്യം*)&p, 10);
        എങ്കിൽ (*p)
            p++;
        height = strtol(p, (ശൂന്യം*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        എങ്കിൽ (*p)
            തിരികെ AVERROR(EINVAL);
    }
    എങ്കിൽ (width <= 0 || height <= 0)
        തിരികെ AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_parse_video_rate(AVRational *rate, സ്ഥിരം അക്ഷരം *arg)
{
    പൂർണ്ണസംഖ്യ i, ret;
    പൂർണ്ണസംഖ്യ n = FF_ARRAY_ELEMS(video_rate_abbrs);

    /* First, we check our abbreviation table */
    വേണ്ടി (i = 0; i < n; ++i)
        എങ്കിൽ (!strcmp(video_rate_abbrs[i].abbr, arg)) {
            *rate = video_rate_abbrs[i].rate;
            തിരികെ 0;
        }

    /* Then, we try to parse it as fraction */
    എങ്കിൽ ((ret = av_parse_ratio_quiet(rate, arg, 1001000)) < 0)
        തിരികെ ret;
    എങ്കിൽ (!rate->അക്കം || !rate->den)
        എങ്കിൽ ((ret = av_parse_ratio_quiet(rate, arg, INT_MAX)) < 0)
            തിരികെ ret;
    എങ്കിൽ (rate->അക്കം <= 0 || rate->den <= 0)
        തിരികെ AVERROR(EINVAL);
    തിരികെ 0;
}

തരനിർവചനം ഘടന ColorEntry {
    സ്ഥിരം അക്ഷരം *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} ColorEntry;

സ്ഥിതം സ്ഥിരം ColorEntry color_table[] = {
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

സ്ഥിതം പൂർണ്ണസംഖ്യ color_table_compare(സ്ഥിരം ശൂന്യം *lhs, സ്ഥിരം ശൂന്യം *rhs)
{
    തിരികെ av_strcasecmp(lhs, ((സ്ഥിരം ColorEntry *)rhs)->name);
}

#define ALPHA_SEP '@'

പൂർണ്ണസംഖ്യ av_parse_color(uint8_t *rgba_color, സ്ഥിരം അക്ഷരം *color_string, പൂർണ്ണസംഖ്യ slen,
                   ശൂന്യം *log_ctx)
{
    അക്ഷരം *tail, color_string2[128];
    സ്ഥിരം ColorEntry *entry;
    പൂർണ്ണസംഖ്യ len, hex_offset = 0;

    എങ്കിൽ (color_string[0] == '#') {
        hex_offset = 1;
    } അല്ലെങ്കിൽ എങ്കിൽ (!strncmp(color_string, "0x", 2))
        hex_offset = 2;

    എങ്കിൽ (slen < 0)
        slen = strlen(color_string);
    av_strlcpy(color_string2, color_string + hex_offset,
               FFMIN(slen-hex_offset+1, വലുപ്പം(color_string2)));
    എങ്കിൽ ((tail = strchr(color_string2, ALPHA_SEP)))
        *tail++ = 0;
    len = strlen(color_string2);
    rgba_color[3] = 255;

    എങ്കിൽ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        പൂർണ്ണസംഖ്യ rgba = av_get_random_seed();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } അല്ലെങ്കിൽ എങ്കിൽ (hex_offset ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        അക്ഷരം *tail;
        unsigned പൂർണ്ണസംഖ്യ rgba = strtoul(color_string2, &tail, 16);

        എങ്കിൽ (*tail || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            തിരികെ AVERROR(EINVAL);
        }
        എങ്കിൽ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } അല്ലെങ്കിൽ {
        entry = bsearch(color_string2,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        വലുപ്പം(ColorEntry),
                        color_table_compare);
        എങ്കിൽ (!entry) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            തിരികെ AVERROR(EINVAL);
        }
        memcpy(rgba_color, entry->rgb_color, 3);
    }

    എങ്കിൽ (tail) {
        ഇരട്ട alpha;
        സ്ഥിരം അക്ഷരം *alpha_string = tail;
        എങ്കിൽ (!strncmp(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &tail, 16);
        } അല്ലെങ്കിൽ {
            ഇരട്ട norm_alpha = strtod(alpha_string, &tail);
            എങ്കിൽ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            അല്ലെങ്കിൽ
                alpha = 255 * norm_alpha;
        }

        എങ്കിൽ (tail == alpha_string || *tail || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            തിരികെ AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    തിരികെ 0;
}

സ്ഥിരം അക്ഷരം *av_get_known_color_name(പൂർണ്ണസംഖ്യ color_idx, സ്ഥിരം uint8_t **rgbp)
{
    സ്ഥിരം ColorEntry *color;

    എങ്കിൽ ((unsigned)color_idx >= FF_ARRAY_ELEMS(color_table))
        തിരികെ ശൂന്യ;

    color = &color_table[color_idx];
    എങ്കിൽ (rgbp)
        *rgbp = color->rgb_color;

    തിരികെ color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
സ്ഥിതം പൂർണ്ണസംഖ്യ date_get_അക്കം(സ്ഥിരം അക്ഷരം **pp,
                        പൂർണ്ണസംഖ്യ n_min, പൂർണ്ണസംഖ്യ n_max, പൂർണ്ണസംഖ്യ len_max)
{
    പൂർണ്ണസംഖ്യ i, val, c;
    സ്ഥിരം അക്ഷരം *p;

    p = *pp;
    val = 0;
    വേണ്ടി(i = 0; i < len_max; i++) {
        c = *p;
        എങ്കിൽ (!av_isdigit(c))
            നിർത്തുക;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    എങ്കിൽ (p == *pp)
        തിരികെ -1;
    എങ്കിൽ (val < n_min || val > n_max)
        തിരികെ -1;
    *pp = p;
    തിരികെ val;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ date_get_month(സ്ഥിരം അക്ഷരം **pp) {
    പൂർണ്ണസംഖ്യ i = 0;
    വേണ്ടി (; i < 12; i++) {
        എങ്കിൽ (!av_strncasecmp(*pp, months[i], 3)) {
            സ്ഥിരം അക്ഷരം *mo_full = months[i] + 3;
            പൂർണ്ണസംഖ്യ len = strlen(mo_full);
            *pp += 3;
            എങ്കിൽ (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            തിരികെ i;
        }
    }
    തിരികെ -1;
}

അക്ഷരം *av_small_strptime(സ്ഥിരം അക്ഷരം *p, സ്ഥിരം അക്ഷരം *fmt, ഘടന tm *dt)
{
    പൂർണ്ണസംഖ്യ c, val;

    ആകുമ്പോൾ((c = *fmt++)) {
        എങ്കിൽ (c != '%') {
            എങ്കിൽ (av_isspace(c))
                വേണ്ടി (; *p && av_isspace(*p); p++);
            അല്ലെങ്കിൽ എങ്കിൽ (*p != c)
                തിരികെ ശൂന്യ;
            അല്ലെങ്കിൽ p++;
            തുടരുക;
        }

        c = *fmt++;
        തിരഞ്ഞെടുപ്പ്(c) {
        അവസ്ഥ 'H':
        അവസ്ഥ 'J':
            val = date_get_അക്കം(&p, 0, c == 'H' ? 23 : INT_MAX, c == 'H' ? 2 : 4);

            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_hour = val;
            നിർത്തുക;
        അവസ്ഥ 'M':
            val = date_get_അക്കം(&p, 0, 59, 2);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_min = val;
            നിർത്തുക;
        അവസ്ഥ 'S':
            val = date_get_അക്കം(&p, 0, 59, 2);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_sec = val;
            നിർത്തുക;
        അവസ്ഥ 'Y':
            val = date_get_അക്കം(&p, 0, 9999, 4);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_year = val - 1900;
            നിർത്തുക;
        അവസ്ഥ 'm':
            val = date_get_അക്കം(&p, 1, 12, 2);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_mon = val - 1;
            നിർത്തുക;
        അവസ്ഥ 'd':
            val = date_get_അക്കം(&p, 1, 31, 2);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_mday = val;
            നിർത്തുക;
        അവസ്ഥ 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            എങ്കിൽ (!p)
                തിരികെ ശൂന്യ;
            നിർത്തുക;
        അവസ്ഥ 'b':
        അവസ്ഥ 'B':
        അവസ്ഥ 'h':
            val = date_get_month(&p);
            എങ്കിൽ (val == -1)
                തിരികെ ശൂന്യ;
            dt->tm_mon = val;
            നിർത്തുക;
        അവസ്ഥ '%':
            എങ്കിൽ (*p++ != '%')
                തിരികെ ശൂന്യ;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            തിരികെ ശൂന്യ;
        }
    }

    തിരികെ (അക്ഷരം*)p;
}

time_t av_timegm(ഘടന tm *tm)
{
    time_t t;

    പൂർണ്ണസംഖ്യ y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    എങ്കിൽ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    തിരികെ t;
}

പൂർണ്ണസംഖ്യ av_parse_time(int64_t *timeval, സ്ഥിരം അക്ഷരം *timestr, പൂർണ്ണസംഖ്യ duration)
{
    സ്ഥിരം അക്ഷരം *p, *q;
    int64_t t, now64;
    time_t now;
    ഘടന tm dt = { 0 }, tmbuf;
    പൂർണ്ണസംഖ്യ today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    പൂർണ്ണസംഖ്യ i;
    സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = ശൂന്യ;
    *timeval = INT64_MIN;
    എങ്കിൽ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        എങ്കിൽ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            തിരികെ 0;
        }

        /* parse the year-month-day part */
        വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            എങ്കിൽ (q)
                നിർത്തുക;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        എങ്കിൽ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        എങ്കിൽ (*p == 'T' || *p == 't')
            p++;
        അല്ലെങ്കിൽ
            ആകുമ്പോൾ (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            എങ്കിൽ (q)
                നിർത്തുക;
        }
    } അല്ലെങ്കിൽ {
        /* parse timestr as a duration */
        എങ്കിൽ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        എങ്കിൽ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        എങ്കിൽ (!q) {
            അക്ഷരം *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            എങ്കിൽ (o == p) /* the parsing didn't succeed */
                തിരികെ AVERROR(EINVAL);
            എങ്കിൽ (errno == ERANGE)
                തിരികെ AVERROR(ERANGE);
            q = o;
        } അല്ലെങ്കിൽ {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    എങ്കിൽ (!q)
        തിരികെ AVERROR(EINVAL);

    /* parse the .m... part */
    എങ്കിൽ (*q == '.') {
        പൂർണ്ണസംഖ്യ n;
        q++;
        വേണ്ടി (n = 100000; n >= 1; n /= 10, q++) {
            എങ്കിൽ (!av_isdigit(*q))
                നിർത്തുക;
            microseconds += n * (*q - '0');
        }
        ആകുമ്പോൾ (av_isdigit(*q))
            q++;
    }

    എങ്കിൽ (duration) {
        എങ്കിൽ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } അല്ലെങ്കിൽ എങ്കിൽ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } അല്ലെങ്കിൽ എങ്കിൽ (*q == 's')
            q++;
    } അല്ലെങ്കിൽ {
        പൂർണ്ണസംഖ്യ is_utc = *q == 'Z' || *q == 'z';
        പൂർണ്ണസംഖ്യ tzoffset = 0;
        q += is_utc;
        എങ്കിൽ (!today && !is_utc && (*q == '+' || *q == '-')) {
            ഘടന tm tz = { 0 };
            പൂർണ്ണസംഖ്യ sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                എങ്കിൽ (q)
                    നിർത്തുക;
            }
            എങ്കിൽ (!q)
                തിരികെ AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        എങ്കിൽ (today) { /* fill in today's date */
            ഘടന tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    എങ്കിൽ (*q)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        തിരികെ AVERROR(ERANGE);
    t *= suffix;
    എങ്കിൽ (INT64_MAX - microseconds < t)
        തിരികെ AVERROR(ERANGE);
    t += microseconds;
    എങ്കിൽ (t == INT64_MIN && negative)
        തിരികെ AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_find_info_tag(അക്ഷരം *arg, പൂർണ്ണസംഖ്യ arg_size, സ്ഥിരം അക്ഷരം *tag1, സ്ഥിരം അക്ഷരം *info)
{
    സ്ഥിരം അക്ഷരം *p;
    അക്ഷരം tag[128], *q;

    p = info;
    എങ്കിൽ (*p == '?')
        p++;
    വേണ്ടി(;;) {
        q = tag;
        ആകുമ്പോൾ (*p != '\0' && *p != '=' && *p != '&') {
            എങ്കിൽ ((q - tag) < വലുപ്പം(tag) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        എങ്കിൽ (*p == '=') {
            p++;
            ആകുമ്പോൾ (*p != '&' && *p != '\0') {
                എങ്കിൽ ((q - arg) < arg_size - 1) {
                    എങ്കിൽ (*p == '+')
                        *q++ = ' ';
                    അല്ലെങ്കിൽ
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        എങ്കിൽ (!strcmp(tag, tag1))
            തിരികെ 1;
        എങ്കിൽ (*p != '&')
            നിർത്തുക;
        p++;
    }
    തിരികെ 0;
}
