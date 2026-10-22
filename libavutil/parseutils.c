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

#অন্তর্ভাব <time.h>

#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "avutil.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "eval.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "random_seed.h"
#অন্তর্ভাব "time_internal.h"
#অন্তর্ভাব "parseutils.h"
#অন্তর্ভাব "time.h"

#ifdef TEST

#define av_get_random_seed av_get_random_seed_deterministic
স্থির uint32_t av_get_random_seed_deterministic(শূন্য);

#define av_gettime() 1331972053200000

#endif

পূর্ণসংখ্যা av_parse_ratio(AVRational *q, ধ্রুবক অক্ষর *str, পূর্ণসংখ্যা max,
                   পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    অক্ষর c;
    পূর্ণসংখ্যা ret;

    যদি (sscanf(str, "%d:%d%c", &q->অঙ্ক, &q->den, &c) != 2) {
        দ্বিগুণ d;
        ret = av_রাশিমালা_parse_and_eval(&d, str, ফাঁকা, ফাঁকা,
                                     ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা,
                                     ফাঁকা, log_offset, log_ctx);
        যদি (ret < 0)
            ফেরত ret;
        *q = av_d2q(d, max);
    } অন্যথা {
        av_reduce(&q->অঙ্ক, &q->den, q->অঙ্ক, q->den, max);
    }

    ফেরত 0;
}

প্রকারলেখ কাঠামো Video_আকার_Abbr {
    ধ্রুবক অক্ষর *abbr;
    পূর্ণসংখ্যা width, height;
} Video_আকার_Abbr;

প্রকারলেখ কাঠামো VideoRateAbbr {
    ধ্রুবক অক্ষর *abbr;
    AVRational rate;
} VideoRateAbbr;

স্থির ধ্রুবক Video_আকার_Abbr video_আকার_abbrs[] = {
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

স্থির ধ্রুবক VideoRateAbbr video_rate_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

স্থির ধ্রুবক অক্ষর *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

পূর্ণসংখ্যা av_parse_video_আকার(পূর্ণসংখ্যা *width_ptr, পূর্ণসংখ্যা *height_ptr, ধ্রুবক অক্ষর *str)
{
    পূর্ণসংখ্যা i;
    পূর্ণসংখ্যা n = FF_ARRAY_ELEMS(video_আকার_abbrs);
    ধ্রুবক অক্ষর *p;
    পূর্ণসংখ্যা width = 0, height = 0;

    জন্য (i = 0; i < n; i++) {
        যদি (!strcmp(video_আকার_abbrs[i].abbr, str)) {
            width  = video_আকার_abbrs[i].width;
            height = video_আকার_abbrs[i].height;
            বিরতি;
        }
    }
    যদি (i == n) {
        width = strtol(str, (শূন্য*)&p, 10);
        যদি (*p)
            p++;
        height = strtol(p, (শূন্য*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        যদি (*p)
            ফেরত AVERROR(EINVAL);
    }
    যদি (width <= 0 || height <= 0)
        ফেরত AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    ফেরত 0;
}

পূর্ণসংখ্যা av_parse_video_rate(AVRational *rate, ধ্রুবক অক্ষর *arg)
{
    পূর্ণসংখ্যা i, ret;
    পূর্ণসংখ্যা n = FF_ARRAY_ELEMS(video_rate_abbrs);

    /* First, we check our abbreviation table */
    জন্য (i = 0; i < n; ++i)
        যদি (!strcmp(video_rate_abbrs[i].abbr, arg)) {
            *rate = video_rate_abbrs[i].rate;
            ফেরত 0;
        }

    /* Then, we try to parse it as fraction */
    যদি ((ret = av_parse_ratio_quiet(rate, arg, 1001000)) < 0)
        ফেরত ret;
    যদি (!rate->অঙ্ক || !rate->den)
        যদি ((ret = av_parse_ratio_quiet(rate, arg, INT_MAX)) < 0)
            ফেরত ret;
    যদি (rate->অঙ্ক <= 0 || rate->den <= 0)
        ফেরত AVERROR(EINVAL);
    ফেরত 0;
}

প্রকারলেখ কাঠামো ColorEntry {
    ধ্রুবক অক্ষর *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} ColorEntry;

স্থির ধ্রুবক ColorEntry color_table[] = {
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

স্থির পূর্ণসংখ্যা color_table_compare(ধ্রুবক শূন্য *lhs, ধ্রুবক শূন্য *rhs)
{
    ফেরত av_strcasecmp(lhs, ((ধ্রুবক ColorEntry *)rhs)->name);
}

#define ALPHA_SEP '@'

পূর্ণসংখ্যা av_parse_color(uint8_t *rgba_color, ধ্রুবক অক্ষর *color_string, পূর্ণসংখ্যা slen,
                   শূন্য *log_ctx)
{
    অক্ষর *লেজ, color_string2[128];
    ধ্রুবক ColorEntry *entry;
    পূর্ণসংখ্যা len, hex_offset = 0;

    যদি (color_string[0] == '#') {
        hex_offset = 1;
    } অন্যথা যদি (!strncmp(color_string, "0x", 2))
        hex_offset = 2;

    যদি (slen < 0)
        slen = strlen(color_string);
    av_strlcpy(color_string2, color_string + hex_offset,
               FFMIN(slen-hex_offset+1, আকার(color_string2)));
    যদি ((লেজ = strchr(color_string2, ALPHA_SEP)))
        *লেজ++ = 0;
    len = strlen(color_string2);
    rgba_color[3] = 255;

    যদি (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        পূর্ণসংখ্যা rgba = av_get_random_seed();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } অন্যথা যদি (hex_offset ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        অক্ষর *লেজ;
        unsigned পূর্ণসংখ্যা rgba = strtoul(color_string2, &লেজ, 16);

        যদি (*লেজ || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            ফেরত AVERROR(EINVAL);
        }
        যদি (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } অন্যথা {
        entry = bsearch(color_string2,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        আকার(ColorEntry),
                        color_table_compare);
        যদি (!entry) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            ফেরত AVERROR(EINVAL);
        }
        memcpy(rgba_color, entry->rgb_color, 3);
    }

    যদি (লেজ) {
        দ্বিগুণ alpha;
        ধ্রুবক অক্ষর *alpha_string = লেজ;
        যদি (!strncmp(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &লেজ, 16);
        } অন্যথা {
            দ্বিগুণ norm_alpha = strtod(alpha_string, &লেজ);
            যদি (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            অন্যথা
                alpha = 255 * norm_alpha;
        }

        যদি (লেজ == alpha_string || *লেজ || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            ফেরত AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    ফেরত 0;
}

ধ্রুবক অক্ষর *av_get_known_color_name(পূর্ণসংখ্যা color_idx, ধ্রুবক uint8_t **rgbp)
{
    ধ্রুবক ColorEntry *color;

    যদি ((unsigned)color_idx >= FF_ARRAY_ELEMS(color_table))
        ফেরত ফাঁকা;

    color = &color_table[color_idx];
    যদি (rgbp)
        *rgbp = color->rgb_color;

    ফেরত color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
স্থির পূর্ণসংখ্যা date_get_অঙ্ক(ধ্রুবক অক্ষর **pp,
                        পূর্ণসংখ্যা n_min, পূর্ণসংখ্যা n_max, পূর্ণসংখ্যা len_max)
{
    পূর্ণসংখ্যা i, val, c;
    ধ্রুবক অক্ষর *p;

    p = *pp;
    val = 0;
    জন্য(i = 0; i < len_max; i++) {
        c = *p;
        যদি (!av_isdigit(c))
            বিরতি;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    যদি (p == *pp)
        ফেরত -1;
    যদি (val < n_min || val > n_max)
        ফেরত -1;
    *pp = p;
    ফেরত val;
}

স্থির পূর্ণসংখ্যা date_get_month(ধ্রুবক অক্ষর **pp) {
    পূর্ণসংখ্যা i = 0;
    জন্য (; i < 12; i++) {
        যদি (!av_strncasecmp(*pp, months[i], 3)) {
            ধ্রুবক অক্ষর *mo_full = months[i] + 3;
            পূর্ণসংখ্যা len = strlen(mo_full);
            *pp += 3;
            যদি (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            ফেরত i;
        }
    }
    ফেরত -1;
}

অক্ষর *av_small_strptime(ধ্রুবক অক্ষর *p, ধ্রুবক অক্ষর *fmt, কাঠামো tm *dt)
{
    পূর্ণসংখ্যা c, val;

    যখন((c = *fmt++)) {
        যদি (c != '%') {
            যদি (av_isspace(c))
                জন্য (; *p && av_isspace(*p); p++);
            অন্যথা যদি (*p != c)
                ফেরত ফাঁকা;
            অন্যথা p++;
            চালু;
        }

        c = *fmt++;
        নির্বাচন(c) {
        ক্ষেত্র 'H':
        ক্ষেত্র 'J':
            val = date_get_অঙ্ক(&p, 0, c == 'H' ? 23 : INT_MAX, c == 'H' ? 2 : 4);

            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_hour = val;
            বিরতি;
        ক্ষেত্র 'M':
            val = date_get_অঙ্ক(&p, 0, 59, 2);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_min = val;
            বিরতি;
        ক্ষেত্র 'S':
            val = date_get_অঙ্ক(&p, 0, 59, 2);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_sec = val;
            বিরতি;
        ক্ষেত্র 'Y':
            val = date_get_অঙ্ক(&p, 0, 9999, 4);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_year = val - 1900;
            বিরতি;
        ক্ষেত্র 'm':
            val = date_get_অঙ্ক(&p, 1, 12, 2);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_mon = val - 1;
            বিরতি;
        ক্ষেত্র 'd':
            val = date_get_অঙ্ক(&p, 1, 31, 2);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_mday = val;
            বিরতি;
        ক্ষেত্র 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            যদি (!p)
                ফেরত ফাঁকা;
            বিরতি;
        ক্ষেত্র 'b':
        ক্ষেত্র 'B':
        ক্ষেত্র 'h':
            val = date_get_month(&p);
            যদি (val == -1)
                ফেরত ফাঁকা;
            dt->tm_mon = val;
            বিরতি;
        ক্ষেত্র '%':
            যদি (*p++ != '%')
                ফেরত ফাঁকা;
            বিরতি;
        পূর্বনির্ধারিত:
            ফেরত ফাঁকা;
        }
    }

    ফেরত (অক্ষর*)p;
}

time_t av_timegm(কাঠামো tm *tm)
{
    time_t t;

    পূর্ণসংখ্যা y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    যদি (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    ফেরত t;
}

পূর্ণসংখ্যা av_parse_time(int64_t *timeval, ধ্রুবক অক্ষর *timestr, পূর্ণসংখ্যা duration)
{
    ধ্রুবক অক্ষর *p, *q;
    int64_t t, now64;
    time_t now;
    কাঠামো tm dt = { 0 }, tmbuf;
    পূর্ণসংখ্যা today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    পূর্ণসংখ্যা i;
    স্থির ধ্রুবক অক্ষর * ধ্রুবক date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    স্থির ধ্রুবক অক্ষর * ধ্রুবক time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    স্থির ধ্রুবক অক্ষর * ধ্রুবক tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = ফাঁকা;
    *timeval = INT64_MIN;
    যদি (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        যদি (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            ফেরত 0;
        }

        /* parse the year-month-day part */
        জন্য (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            যদি (q)
                বিরতি;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        যদি (!q) {
            today = 1;
            q = p;
        }
        p = q;

        যদি (*p == 'T' || *p == 't')
            p++;
        অন্যথা
            যখন (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        জন্য (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            যদি (q)
                বিরতি;
        }
    } অন্যথা {
        /* parse timestr as a duration */
        যদি (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        যদি (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        যদি (!q) {
            অক্ষর *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            যদি (o == p) /* the parsing didn't succeed */
                ফেরত AVERROR(EINVAL);
            যদি (errno == ERANGE)
                ফেরত AVERROR(ERANGE);
            q = o;
        } অন্যথা {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    যদি (!q)
        ফেরত AVERROR(EINVAL);

    /* parse the .m... part */
    যদি (*q == '.') {
        পূর্ণসংখ্যা n;
        q++;
        জন্য (n = 100000; n >= 1; n /= 10, q++) {
            যদি (!av_isdigit(*q))
                বিরতি;
            microseconds += n * (*q - '0');
        }
        যখন (av_isdigit(*q))
            q++;
    }

    যদি (duration) {
        যদি (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } অন্যথা যদি (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } অন্যথা যদি (*q == 's')
            q++;
    } অন্যথা {
        পূর্ণসংখ্যা is_utc = *q == 'Z' || *q == 'z';
        পূর্ণসংখ্যা tzoffset = 0;
        q += is_utc;
        যদি (!today && !is_utc && (*q == '+' || *q == '-')) {
            কাঠামো tm tz = { 0 };
            পূর্ণসংখ্যা sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            জন্য (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                যদি (q)
                    বিরতি;
            }
            যদি (!q)
                ফেরত AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        যদি (today) { /* fill in today's date */
            কাঠামো tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    যদি (*q)
        ফেরত AVERROR(EINVAL);

    যদি (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        ফেরত AVERROR(ERANGE);
    t *= suffix;
    যদি (INT64_MAX - microseconds < t)
        ফেরত AVERROR(ERANGE);
    t += microseconds;
    যদি (t == INT64_MIN && negative)
        ফেরত AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    ফেরত 0;
}

পূর্ণসংখ্যা av_find_info_tag(অক্ষর *arg, পূর্ণসংখ্যা arg_আকার, ধ্রুবক অক্ষর *tag1, ধ্রুবক অক্ষর *info)
{
    ধ্রুবক অক্ষর *p;
    অক্ষর tag[128], *q;

    p = info;
    যদি (*p == '?')
        p++;
    জন্য(;;) {
        q = tag;
        যখন (*p != '\0' && *p != '=' && *p != '&') {
            যদি ((q - tag) < আকার(tag) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        যদি (*p == '=') {
            p++;
            যখন (*p != '&' && *p != '\0') {
                যদি ((q - arg) < arg_আকার - 1) {
                    যদি (*p == '+')
                        *q++ = ' ';
                    অন্যথা
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        যদি (!strcmp(tag, tag1))
            ফেরত 1;
        যদি (*p != '&')
            বিরতি;
        p++;
    }
    ফেরত 0;
}
