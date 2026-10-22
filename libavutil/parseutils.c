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

#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eval.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "random_seed.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "parseutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_get_random_ਬੀਜ av_get_random_ਬੀਜ_deterministic
ਸਥਿਰ uint32_t av_get_random_ਬੀਜ_deterministic(ਖਾਲੀ);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_gettime() 1331972053200000

#ਜੇ_ਅੰਤ

ਪੂਰਨ av_parse_ਅਨੁਪਾਤ(AVRational *q, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ max,
                   ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    ਅੱਖਰ c;
    ਪੂਰਨ ret;

    ਜੇ (ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ(str, "%d:%d%c", &q->ਅੰਕ, &q->den, &c) != 2) {
        ਦੁੱਗਣਾ d;
        ret = av_ਵਿਅੰਜਕ_parse_and_eval(&d, str, ਨਿਰਾ, ਨਿਰਾ,
                                     ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ,
                                     ਨਿਰਾ, log_ਵਿੱਥ, log_ctx);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        *q = av_d2q(d, max);
    } ਨਹੀਂਤਾਂ {
        av_reduce(&q->ਅੰਕ, &q->den, q->ਅੰਕ, q->den, max);
    }

    ਵਾਪਸ 0;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Video_ਮਾਪ_Abbr {
    ਅਚਲ ਅੱਖਰ *abbr;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
} Video_ਮਾਪ_Abbr;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Video_ਦਰ_Abbr {
    ਅਚਲ ਅੱਖਰ *abbr;
    AVRational ਦਰ;
} Video_ਦਰ_Abbr;

ਸਥਿਰ ਅਚਲ Video_ਮਾਪ_Abbr video_ਮਾਪ_abbrs[] = {
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

ਸਥਿਰ ਅਚਲ Video_ਦਰ_Abbr video_ਦਰ_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

ਪੂਰਨ av_parse_video_ਮਾਪ(ਪੂਰਨ *ਚੌੜਾਈ_ptr, ਪੂਰਨ *ਉਚਾਈ_ptr, ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ i;
    ਪੂਰਨ n = FF_ARRAY_ELEMS(video_ਮਾਪ_abbrs);
    ਅਚਲ ਅੱਖਰ *p;
    ਪੂਰਨ ਚੌੜਾਈ = 0, ਉਚਾਈ = 0;

    ਲਈ (i = 0; i < n; i++) {
        ਜੇ (!strcmp(video_ਮਾਪ_abbrs[i].abbr, str)) {
            ਚੌੜਾਈ  = video_ਮਾਪ_abbrs[i].ਚੌੜਾਈ;
            ਉਚਾਈ = video_ਮਾਪ_abbrs[i].ਉਚਾਈ;
            ਰੋਕੋ;
        }
    }
    ਜੇ (i == n) {
        ਚੌੜਾਈ = strtol(str, (ਖਾਲੀ*)&p, 10);
        ਜੇ (*p)
            p++;
        ਉਚਾਈ = strtol(p, (ਖਾਲੀ*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        ਜੇ (*p)
            ਵਾਪਸ AVERROR(EINVAL);
    }
    ਜੇ (ਚੌੜਾਈ <= 0 || ਉਚਾਈ <= 0)
        ਵਾਪਸ AVERROR(EINVAL);
    *ਚੌੜਾਈ_ptr  = ਚੌੜਾਈ;
    *ਉਚਾਈ_ptr = ਉਚਾਈ;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_parse_video_ਦਰ(AVRational *ਦਰ, ਅਚਲ ਅੱਖਰ *arg)
{
    ਪੂਰਨ i, ret;
    ਪੂਰਨ n = FF_ARRAY_ELEMS(video_ਦਰ_abbrs);

    /* First, we check our abbreviation table */
    ਲਈ (i = 0; i < n; ++i)
        ਜੇ (!strcmp(video_ਦਰ_abbrs[i].abbr, arg)) {
            *ਦਰ = video_ਦਰ_abbrs[i].ਦਰ;
            ਵਾਪਸ 0;
        }

    /* Then, we try to parse it as fraction */
    ਜੇ ((ret = av_parse_ਅਨੁਪਾਤ_quiet(ਦਰ, arg, 1001000)) < 0)
        ਵਾਪਸ ret;
    ਜੇ (!ਦਰ->ਅੰਕ || !ਦਰ->den)
        ਜੇ ((ret = av_parse_ਅਨੁਪਾਤ_quiet(ਦਰ, arg, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)) < 0)
            ਵਾਪਸ ret;
    ਜੇ (ਦਰ->ਅੰਕ <= 0 || ਦਰ->den <= 0)
        ਵਾਪਸ AVERROR(EINVAL);
    ਵਾਪਸ 0;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Color_ਇੰਦਰਾਜ {
    ਅਚਲ ਅੱਖਰ *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} Color_ਇੰਦਰਾਜ;

ਸਥਿਰ ਅਚਲ Color_ਇੰਦਰਾਜ color_ਸਾਰਣੀ[] = {
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

ਸਥਿਰ ਪੂਰਨ color_ਸਾਰਣੀ_compare(ਅਚਲ ਖਾਲੀ *lhs, ਅਚਲ ਖਾਲੀ *rhs)
{
    ਵਾਪਸ av_strcasecmp(lhs, ((ਅਚਲ Color_ਇੰਦਰਾਜ *)rhs)->name);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALPHA_SEP '@'

ਪੂਰਨ av_parse_color(uint8_t *rgba_color, ਅਚਲ ਅੱਖਰ *color_string, ਪੂਰਨ slen,
                   ਖਾਲੀ *log_ctx)
{
    ਅੱਖਰ *ਪੂਛ, color_string2[128];
    ਅਚਲ Color_ਇੰਦਰਾਜ *ਇੰਦਰਾਜ;
    ਪੂਰਨ len, hex_ਵਿੱਥ = 0;

    ਜੇ (color_string[0] == '#') {
        hex_ਵਿੱਥ = 1;
    } ਨਹੀਂਤਾਂ ਜੇ (!ਲੜੀ_ਤੁਲਨਾ(color_string, "0x", 2))
        hex_ਵਿੱਥ = 2;

    ਜੇ (slen < 0)
        slen = ਲੜੀ_ਲੰਬਾਈ(color_string);
    av_strlcpy(color_string2, color_string + hex_ਵਿੱਥ,
               FFMIN(slen-hex_ਵਿੱਥ+1, ਆਕਾਰ(color_string2)));
    ਜੇ ((ਪੂਛ = strchr(color_string2, ALPHA_SEP)))
        *ਪੂਛ++ = 0;
    len = ਲੜੀ_ਲੰਬਾਈ(color_string2);
    rgba_color[3] = 255;

    ਜੇ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        ਪੂਰਨ rgba = av_get_random_ਬੀਜ();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } ਨਹੀਂਤਾਂ ਜੇ (hex_ਵਿੱਥ ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        ਅੱਖਰ *ਪੂਛ;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ rgba = strtoul(color_string2, &ਪੂਛ, 16);

        ਜੇ (*ਪੂਛ || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        ਜੇ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } ਨਹੀਂਤਾਂ {
        ਇੰਦਰਾਜ = bsearch(color_string2,
                        color_ਸਾਰਣੀ,
                        FF_ARRAY_ELEMS(color_ਸਾਰਣੀ),
                        ਆਕਾਰ(Color_ਇੰਦਰਾਜ),
                        color_ਸਾਰਣੀ_compare);
        ਜੇ (!ਇੰਦਰਾਜ) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(rgba_color, ਇੰਦਰਾਜ->rgb_color, 3);
    }

    ਜੇ (ਪੂਛ) {
        ਦੁੱਗਣਾ alpha;
        ਅਚਲ ਅੱਖਰ *alpha_string = ਪੂਛ;
        ਜੇ (!ਲੜੀ_ਤੁਲਨਾ(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &ਪੂਛ, 16);
        } ਨਹੀਂਤਾਂ {
            ਦੁੱਗਣਾ norm_alpha = strtod(alpha_string, &ਪੂਛ);
            ਜੇ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            ਨਹੀਂਤਾਂ
                alpha = 255 * norm_alpha;
        }

        ਜੇ (ਪੂਛ == alpha_string || *ਪੂਛ || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    ਵਾਪਸ 0;
}

ਅਚਲ ਅੱਖਰ *av_get_ਗਿਆਤ_color_name(ਪੂਰਨ color_idx, ਅਚਲ uint8_t **rgbp)
{
    ਅਚਲ Color_ਇੰਦਰਾਜ *color;

    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)color_idx >= FF_ARRAY_ELEMS(color_ਸਾਰਣੀ))
        ਵਾਪਸ ਨਿਰਾ;

    color = &color_ਸਾਰਣੀ[color_idx];
    ਜੇ (rgbp)
        *rgbp = color->rgb_color;

    ਵਾਪਸ color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
ਸਥਿਰ ਪੂਰਨ date_get_ਅੰਕ(ਅਚਲ ਅੱਖਰ **pp,
                        ਪੂਰਨ n_min, ਪੂਰਨ n_max, ਪੂਰਨ len_max)
{
    ਪੂਰਨ i, val, c;
    ਅਚਲ ਅੱਖਰ *p;

    p = *pp;
    val = 0;
    ਲਈ(i = 0; i < len_max; i++) {
        c = *p;
        ਜੇ (!av_isdigit(c))
            ਰੋਕੋ;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    ਜੇ (p == *pp)
        ਵਾਪਸ -1;
    ਜੇ (val < n_min || val > n_max)
        ਵਾਪਸ -1;
    *pp = p;
    ਵਾਪਸ val;
}

ਸਥਿਰ ਪੂਰਨ date_get_month(ਅਚਲ ਅੱਖਰ **pp) {
    ਪੂਰਨ i = 0;
    ਲਈ (; i < 12; i++) {
        ਜੇ (!av_strncasecmp(*pp, months[i], 3)) {
            ਅਚਲ ਅੱਖਰ *mo_ਭਰਿਆ = months[i] + 3;
            ਪੂਰਨ len = ਲੜੀ_ਲੰਬਾਈ(mo_ਭਰਿਆ);
            *pp += 3;
            ਜੇ (len > 0 && !av_strncasecmp(*pp, mo_ਭਰਿਆ, len))
                *pp += len;
            ਵਾਪਸ i;
        }
    }
    ਵਾਪਸ -1;
}

ਅੱਖਰ *av_small_strptime(ਅਚਲ ਅੱਖਰ *p, ਅਚਲ ਅੱਖਰ *fmt, ਬਣਤਰ tm *dt)
{
    ਪੂਰਨ c, val;

    ਜਦੋਂ((c = *fmt++)) {
        ਜੇ (c != '%') {
            ਜੇ (av_isspace(c))
                ਲਈ (; *p && av_isspace(*p); p++);
            ਨਹੀਂਤਾਂ ਜੇ (*p != c)
                ਵਾਪਸ ਨਿਰਾ;
            ਨਹੀਂਤਾਂ p++;
            ਜਾਰੀ;
        }

        c = *fmt++;
        ਚੋਣ(c) {
        ਹਾਲਤ 'H':
        ਹਾਲਤ 'J':
            val = date_get_ਅੰਕ(&p, 0, c == 'H' ? 23 : ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, c == 'H' ? 2 : 4);

            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_hour = val;
            ਰੋਕੋ;
        ਹਾਲਤ 'M':
            val = date_get_ਅੰਕ(&p, 0, 59, 2);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_min = val;
            ਰੋਕੋ;
        ਹਾਲਤ 'S':
            val = date_get_ਅੰਕ(&p, 0, 59, 2);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_sec = val;
            ਰੋਕੋ;
        ਹਾਲਤ 'Y':
            val = date_get_ਅੰਕ(&p, 0, 9999, 4);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_year = val - 1900;
            ਰੋਕੋ;
        ਹਾਲਤ 'm':
            val = date_get_ਅੰਕ(&p, 1, 12, 2);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_mon = val - 1;
            ਰੋਕੋ;
        ਹਾਲਤ 'd':
            val = date_get_ਅੰਕ(&p, 1, 31, 2);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_mday = val;
            ਰੋਕੋ;
        ਹਾਲਤ 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            ਜੇ (!p)
                ਵਾਪਸ ਨਿਰਾ;
            ਰੋਕੋ;
        ਹਾਲਤ 'b':
        ਹਾਲਤ 'B':
        ਹਾਲਤ 'h':
            val = date_get_month(&p);
            ਜੇ (val == -1)
                ਵਾਪਸ ਨਿਰਾ;
            dt->tm_mon = val;
            ਰੋਕੋ;
        ਹਾਲਤ '%':
            ਜੇ (*p++ != '%')
                ਵਾਪਸ ਨਿਰਾ;
            ਰੋਕੋ;
        ਮੂਲ:
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਵਾਪਸ (ਅੱਖਰ*)p;
}

time_t av_timegm(ਬਣਤਰ tm *tm)
{
    time_t t;

    ਪੂਰਨ y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    ਜੇ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    ਵਾਪਸ t;
}

ਪੂਰਨ av_parse_ਸਮਾਂ(int64_t *timeval, ਅਚਲ ਅੱਖਰ *timestr, ਪੂਰਨ duration)
{
    ਅਚਲ ਅੱਖਰ *p, *q;
    int64_t t, now64;
    time_t now;
    ਬਣਤਰ tm dt = { 0 }, tmbuf;
    ਪੂਰਨ today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    ਪੂਰਨ i;
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ ਸਮਾਂ_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = ਨਿਰਾ;
    *timeval = INT64_MIN;
    ਜੇ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        ਜੇ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            ਵਾਪਸ 0;
        }

        /* parse the year-month-day part */
        ਲਈ (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            ਜੇ (q)
                ਰੋਕੋ;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        ਜੇ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        ਜੇ (*p == 'T' || *p == 't')
            p++;
        ਨਹੀਂਤਾਂ
            ਜਦੋਂ (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        ਲਈ (i = 0; i < FF_ARRAY_ELEMS(ਸਮਾਂ_fmt); i++) {
            q = av_small_strptime(p, ਸਮਾਂ_fmt[i], &dt);
            ਜੇ (q)
                ਰੋਕੋ;
        }
    } ਨਹੀਂਤਾਂ {
        /* parse timestr as a duration */
        ਜੇ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        ਜੇ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        ਜੇ (!q) {
            ਅੱਖਰ *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            ਜੇ (o == p) /* the parsing didn't succeed */
                ਵਾਪਸ AVERROR(EINVAL);
            ਜੇ (errno == ERANGE)
                ਵਾਪਸ AVERROR(ERANGE);
            q = o;
        } ਨਹੀਂਤਾਂ {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    ਜੇ (!q)
        ਵਾਪਸ AVERROR(EINVAL);

    /* parse the .m... part */
    ਜੇ (*q == '.') {
        ਪੂਰਨ n;
        q++;
        ਲਈ (n = 100000; n >= 1; n /= 10, q++) {
            ਜੇ (!av_isdigit(*q))
                ਰੋਕੋ;
            microseconds += n * (*q - '0');
        }
        ਜਦੋਂ (av_isdigit(*q))
            q++;
    }

    ਜੇ (duration) {
        ਜੇ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } ਨਹੀਂਤਾਂ ਜੇ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } ਨਹੀਂਤਾਂ ਜੇ (*q == 's')
            q++;
    } ਨਹੀਂਤਾਂ {
        ਪੂਰਨ is_utc = *q == 'Z' || *q == 'z';
        ਪੂਰਨ tzoffset = 0;
        q += is_utc;
        ਜੇ (!today && !is_utc && (*q == '+' || *q == '-')) {
            ਬਣਤਰ tm tz = { 0 };
            ਪੂਰਨ sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            ਲਈ (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                ਜੇ (q)
                    ਰੋਕੋ;
            }
            ਜੇ (!q)
                ਵਾਪਸ AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        ਜੇ (today) { /* fill in today's date */
            ਬਣਤਰ tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    ਜੇ (*q)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        ਵਾਪਸ AVERROR(ERANGE);
    t *= suffix;
    ਜੇ (INT64_MAX - microseconds < t)
        ਵਾਪਸ AVERROR(ERANGE);
    t += microseconds;
    ਜੇ (t == INT64_MIN && negative)
        ਵਾਪਸ AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਲੱਭੋ_info_ਟੈਗ(ਅੱਖਰ *arg, ਪੂਰਨ arg_ਮਾਪ, ਅਚਲ ਅੱਖਰ *tag1, ਅਚਲ ਅੱਖਰ *info)
{
    ਅਚਲ ਅੱਖਰ *p;
    ਅੱਖਰ ਟੈਗ[128], *q;

    p = info;
    ਜੇ (*p == '?')
        p++;
    ਲਈ(;;) {
        q = ਟੈਗ;
        ਜਦੋਂ (*p != '\0' && *p != '=' && *p != '&') {
            ਜੇ ((q - ਟੈਗ) < ਆਕਾਰ(ਟੈਗ) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        ਜੇ (*p == '=') {
            p++;
            ਜਦੋਂ (*p != '&' && *p != '\0') {
                ਜੇ ((q - arg) < arg_ਮਾਪ - 1) {
                    ਜੇ (*p == '+')
                        *q++ = ' ';
                    ਨਹੀਂਤਾਂ
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        ਜੇ (!strcmp(ਟੈਗ, tag1))
            ਵਾਪਸ 1;
        ਜੇ (*p != '&')
            ਰੋਕੋ;
        p++;
    }
    ਵਾਪਸ 0;
}
