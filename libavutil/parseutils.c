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

#ಅನ್ತರ್ಭಾವ <time.h>

#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "eval.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "random_seed.h"
#ಅನ್ತರ್ಭಾವ "time_internal.h"
#ಅನ್ತರ್ಭಾವ "parseutils.h"
#ಅನ್ತರ್ಭಾವ "time.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST

#ವ್ಯಾಖ್ಯಾನಿಸು av_get_random_ಬೀಜ av_get_random_ಬೀಜ_deterministic
ಸ್ಥಿರ uint32_t av_get_random_ಬೀಜ_deterministic(ಶೂನ್ಯ);

#ವ್ಯಾಖ್ಯಾನಿಸು av_gettime() 1331972053200000

#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ av_parse_ಅನುಪಾತ(AVRational *q, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ max,
                   ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    ಅಕ್ಷರ c;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಓದು(str, "%d:%d%c", &q->ಅಂಕೆ, &q->den, &c) != 2) {
        ದ್ವಿಗುಣ d;
        ret = av_ಅಭಿವ್ಯಕ್ತಿ_parse_and_eval(&d, str, ಖಾಲಿ, ಖಾಲಿ,
                                     ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ,
                                     ಖಾಲಿ, log_ಸ್ಥಾನಾಂತರ, log_ctx);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        *q = av_d2q(d, max);
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_reduce(&q->ಅಂಕೆ, &q->den, q->ಅಂಕೆ, q->den, max);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Video_ಗಾತ್ರ_Abbr {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *abbr;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;
} Video_ಗಾತ್ರ_Abbr;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Video_ದರ_Abbr {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *abbr;
    AVRational ದರ;
} Video_ದರ_Abbr;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Video_ಗಾತ್ರ_Abbr video_ಗಾತ್ರ_abbrs[] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Video_ದರ_Abbr video_ದರ_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

ಪೂರ್ಣಾಂಕ av_parse_video_ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ *ಅಗಲ_ptr, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ_ptr, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ n = FF_ARRAY_ELEMS(video_ಗಾತ್ರ_abbrs);
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p;
    ಪೂರ್ಣಾಂಕ ಅಗಲ = 0, ಎತ್ತರ = 0;

    ಗಾಗಿ (i = 0; i < n; i++) {
        ಆದರೆ (!strcmp(video_ಗಾತ್ರ_abbrs[i].abbr, str)) {
            ಅಗಲ  = video_ಗಾತ್ರ_abbrs[i].ಅಗಲ;
            ಎತ್ತರ = video_ಗಾತ್ರ_abbrs[i].ಎತ್ತರ;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (i == n) {
        ಅಗಲ = strtol(str, (ಶೂನ್ಯ*)&p, 10);
        ಆದರೆ (*p)
            p++;
        ಎತ್ತರ = strtol(p, (ಶೂನ್ಯ*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        ಆದರೆ (*p)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಆದರೆ (ಅಗಲ <= 0 || ಎತ್ತರ <= 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    *ಅಗಲ_ptr  = ಅಗಲ;
    *ಎತ್ತರ_ptr = ಎತ್ತರ;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_parse_video_ದರ(AVRational *ದರ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *arg)
{
    ಪೂರ್ಣಾಂಕ i, ret;
    ಪೂರ್ಣಾಂಕ n = FF_ARRAY_ELEMS(video_ದರ_abbrs);

    /* First, we check our abbreviation table */
    ಗಾಗಿ (i = 0; i < n; ++i)
        ಆದರೆ (!strcmp(video_ದರ_abbrs[i].abbr, arg)) {
            *ದರ = video_ದರ_abbrs[i].ದರ;
            ಹಿಂತಿರುಗಿ 0;
        }

    /* Then, we try to parse it as fraction */
    ಆದರೆ ((ret = av_parse_ಅನುಪಾತ_quiet(ದರ, arg, 1001000)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (!ದರ->ಅಂಕೆ || !ದರ->den)
        ಆದರೆ ((ret = av_parse_ಅನುಪಾತ_quiet(ದರ, arg, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)) < 0)
            ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (ದರ->ಅಂಕೆ <= 0 || ದರ->den <= 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಹಿಂತಿರುಗಿ 0;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Color_ನಮೂದು {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} Color_ನಮೂದು;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Color_ನಮೂದು color_ಕೋಷ್ಟಕ[] = {
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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ color_ಕೋಷ್ಟಕ_compare(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *lhs, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *rhs)
{
    ಹಿಂತಿರುಗಿ av_strcasecmp(lhs, ((ಸ್ಥಿರಾಂಕ Color_ನಮೂದು *)rhs)->name);
}

#ವ್ಯಾಖ್ಯಾನಿಸು ALPHA_SEP '@'

ಪೂರ್ಣಾಂಕ av_parse_color(uint8_t *rgba_color, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *color_string, ಪೂರ್ಣಾಂಕ slen,
                   ಶೂನ್ಯ *log_ctx)
{
    ಅಕ್ಷರ *ಬಾಲ, color_string2[128];
    ಸ್ಥಿರಾಂಕ Color_ನಮೂದು *ನಮೂದು;
    ಪೂರ್ಣಾಂಕ len, hex_ಸ್ಥಾನಾಂತರ = 0;

    ಆದರೆ (color_string[0] == '#') {
        hex_ಸ್ಥಾನಾಂತರ = 1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(color_string, "0x", 2))
        hex_ಸ್ಥಾನಾಂತರ = 2;

    ಆದರೆ (slen < 0)
        slen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(color_string);
    av_strlcpy(color_string2, color_string + hex_ಸ್ಥಾನಾಂತರ,
               FFMIN(slen-hex_ಸ್ಥಾನಾಂತರ+1, ಗಾತ್ರ(color_string2)));
    ಆದರೆ ((ಬಾಲ = strchr(color_string2, ALPHA_SEP)))
        *ಬಾಲ++ = 0;
    len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(color_string2);
    rgba_color[3] = 255;

    ಆದರೆ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        ಪೂರ್ಣಾಂಕ rgba = av_get_random_ಬೀಜ();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hex_ಸ್ಥಾನಾಂತರ ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        ಅಕ್ಷರ *ಬಾಲ;
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ rgba = strtoul(color_string2, &ಬಾಲ, 16);

        ಆದರೆ (*ಬಾಲ || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        ಆದರೆ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ನಮೂದು = bsearch(color_string2,
                        color_ಕೋಷ್ಟಕ,
                        FF_ARRAY_ELEMS(color_ಕೋಷ್ಟಕ),
                        ಗಾತ್ರ(Color_ನಮೂದು),
                        color_ಕೋಷ್ಟಕ_compare);
        ಆದರೆ (!ನಮೂದು) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        ಸ್ಮರಣೆ_ನಕಲು(rgba_color, ನಮೂದು->rgb_color, 3);
    }

    ಆದರೆ (ಬಾಲ) {
        ದ್ವಿಗುಣ alpha;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *alpha_string = ಬಾಲ;
        ಆದರೆ (!ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &ಬಾಲ, 16);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದ್ವಿಗುಣ norm_alpha = strtod(alpha_string, &ಬಾಲ);
            ಆದರೆ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            ಇಲ್ಲದಿದ್ದರೆ
                alpha = 255 * norm_alpha;
        }

        ಆದರೆ (ಬಾಲ == alpha_string || *ಬಾಲ || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_get_ತಿಳಿದ_color_name(ಪೂರ್ಣಾಂಕ color_idx, ಸ್ಥಿರಾಂಕ uint8_t **rgbp)
{
    ಸ್ಥಿರಾಂಕ Color_ನಮೂದು *color;

    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)color_idx >= FF_ARRAY_ELEMS(color_ಕೋಷ್ಟಕ))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    color = &color_ಕೋಷ್ಟಕ[color_idx];
    ಆದರೆ (rgbp)
        *rgbp = color->rgb_color;

    ಹಿಂತಿರುಗಿ color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ date_get_ಅಂಕೆ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **pp,
                        ಪೂರ್ಣಾಂಕ n_min, ಪೂರ್ಣಾಂಕ n_max, ಪೂರ್ಣಾಂಕ len_max)
{
    ಪೂರ್ಣಾಂಕ i, val, c;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p;

    p = *pp;
    val = 0;
    ಗಾಗಿ(i = 0; i < len_max; i++) {
        c = *p;
        ಆದರೆ (!av_isdigit(c))
            ನಿಲ್ಲಿಸು;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    ಆದರೆ (p == *pp)
        ಹಿಂತಿರುಗಿ -1;
    ಆದರೆ (val < n_min || val > n_max)
        ಹಿಂತಿರುಗಿ -1;
    *pp = p;
    ಹಿಂತಿರುಗಿ val;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ date_get_month(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **pp) {
    ಪೂರ್ಣಾಂಕ i = 0;
    ಗಾಗಿ (; i < 12; i++) {
        ಆದರೆ (!av_strncasecmp(*pp, months[i], 3)) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mo_ತುಂಬಿದ = months[i] + 3;
            ಪೂರ್ಣಾಂಕ len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(mo_ತುಂಬಿದ);
            *pp += 3;
            ಆದರೆ (len > 0 && !av_strncasecmp(*pp, mo_ತುಂಬಿದ, len))
                *pp += len;
            ಹಿಂತಿರುಗಿ i;
        }
    }
    ಹಿಂತಿರುಗಿ -1;
}

ಅಕ್ಷರ *av_small_strptime(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ರಚನೆ tm *dt)
{
    ಪೂರ್ಣಾಂಕ c, val;

    ಆಗ((c = *fmt++)) {
        ಆದರೆ (c != '%') {
            ಆದರೆ (av_isspace(c))
                ಗಾಗಿ (; *p && av_isspace(*p); p++);
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*p != c)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            ಇಲ್ಲದಿದ್ದರೆ p++;
            ಮುಂದುವರಿ;
        }

        c = *fmt++;
        ಆಯ್ಕೆ(c) {
        ಸ್ಥಿತಿ 'H':
        ಸ್ಥಿತಿ 'J':
            val = date_get_ಅಂಕೆ(&p, 0, c == 'H' ? 23 : ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, c == 'H' ? 2 : 4);

            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_hour = val;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'M':
            val = date_get_ಅಂಕೆ(&p, 0, 59, 2);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_min = val;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'S':
            val = date_get_ಅಂಕೆ(&p, 0, 59, 2);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_sec = val;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'Y':
            val = date_get_ಅಂಕೆ(&p, 0, 9999, 4);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_year = val - 1900;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'm':
            val = date_get_ಅಂಕೆ(&p, 1, 12, 2);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_mon = val - 1;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'd':
            val = date_get_ಅಂಕೆ(&p, 1, 31, 2);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_mday = val;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            ಆದರೆ (!p)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 'b':
        ಸ್ಥಿತಿ 'B':
        ಸ್ಥಿತಿ 'h':
            val = date_get_month(&p);
            ಆದರೆ (val == -1)
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            dt->tm_mon = val;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ '%':
            ಆದರೆ (*p++ != '%')
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)p;
}

time_t av_timegm(ರಚನೆ tm *tm)
{
    time_t t;

    ಪೂರ್ಣಾಂಕ y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    ಆದರೆ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    ಹಿಂತಿರುಗಿ t;
}

ಪೂರ್ಣಾಂಕ av_parse_ಸಮಯ(int64_t *timeval, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *timestr, ಪೂರ್ಣಾಂಕ duration)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p, *q;
    int64_t t, now64;
    time_t now;
    ರಚನೆ tm dt = { 0 }, tmbuf;
    ಪೂರ್ಣಾಂಕ today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ ಸಮಯ_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = ಖಾಲಿ;
    *timeval = INT64_MIN;
    ಆದರೆ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        ಆದರೆ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            ಹಿಂತಿರುಗಿ 0;
        }

        /* parse the year-month-day part */
        ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            ಆದರೆ (q)
                ನಿಲ್ಲಿಸು;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        ಆದರೆ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        ಆದರೆ (*p == 'T' || *p == 't')
            p++;
        ಇಲ್ಲದಿದ್ದರೆ
            ಆಗ (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(ಸಮಯ_fmt); i++) {
            q = av_small_strptime(p, ಸಮಯ_fmt[i], &dt);
            ಆದರೆ (q)
                ನಿಲ್ಲಿಸು;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* parse timestr as a duration */
        ಆದರೆ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        ಆದರೆ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        ಆದರೆ (!q) {
            ಅಕ್ಷರ *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            ಆದರೆ (o == p) /* the parsing didn't succeed */
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            ಆದರೆ (errno == ERANGE)
                ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
            q = o;
        } ಇಲ್ಲದಿದ್ದರೆ {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    ಆದರೆ (!q)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    /* parse the .m... part */
    ಆದರೆ (*q == '.') {
        ಪೂರ್ಣಾಂಕ n;
        q++;
        ಗಾಗಿ (n = 100000; n >= 1; n /= 10, q++) {
            ಆದರೆ (!av_isdigit(*q))
                ನಿಲ್ಲಿಸು;
            microseconds += n * (*q - '0');
        }
        ಆಗ (av_isdigit(*q))
            q++;
    }

    ಆದರೆ (duration) {
        ಆದರೆ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*q == 's')
            q++;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ is_utc = *q == 'Z' || *q == 'z';
        ಪೂರ್ಣಾಂಕ tzoffset = 0;
        q += is_utc;
        ಆದರೆ (!today && !is_utc && (*q == '+' || *q == '-')) {
            ರಚನೆ tm tz = { 0 };
            ಪೂರ್ಣಾಂಕ sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                ಆದರೆ (q)
                    ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ (!q)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        ಆದರೆ (today) { /* fill in today's date */
            ರಚನೆ tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    ಆದರೆ (*q)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    t *= suffix;
    ಆದರೆ (INT64_MAX - microseconds < t)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    t += microseconds;
    ಆದರೆ (t == INT64_MIN && negative)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಕಂಡುಹಿಡಿ_info_ಟ್ಯಾಗ್(ಅಕ್ಷರ *arg, ಪೂರ್ಣಾಂಕ arg_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *tag1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *info)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p;
    ಅಕ್ಷರ ಟ್ಯಾಗ್[128], *q;

    p = info;
    ಆದರೆ (*p == '?')
        p++;
    ಗಾಗಿ(;;) {
        q = ಟ್ಯಾಗ್;
        ಆಗ (*p != '\0' && *p != '=' && *p != '&') {
            ಆದರೆ ((q - ಟ್ಯಾಗ್) < ಗಾತ್ರ(ಟ್ಯಾಗ್) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        ಆದರೆ (*p == '=') {
            p++;
            ಆಗ (*p != '&' && *p != '\0') {
                ಆದರೆ ((q - arg) < arg_ಗಾತ್ರ - 1) {
                    ಆದರೆ (*p == '+')
                        *q++ = ' ';
                    ಇಲ್ಲದಿದ್ದರೆ
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        ಆದರೆ (!strcmp(ಟ್ಯಾಗ್, tag1))
            ಹಿಂತಿರುಗಿ 1;
        ಆದರೆ (*p != '&')
            ನಿಲ್ಲಿಸು;
        p++;
    }
    ಹಿಂತಿರುಗಿ 0;
}
