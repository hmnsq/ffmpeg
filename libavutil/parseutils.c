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

#అన్తర్భావ <time.h>

#అన్తర్భావ "avstring.h"
#అన్తర్భావ "avutil.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "eval.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "random_seed.h"
#అన్తర్భావ "time_internal.h"
#అన్తర్భావ "parseutils.h"
#అన్తర్భావ "time.h"

#నిర్వచితమైతే TEST

#నిర్వచించు av_get_random_విత్తనం av_get_random_విత్తనం_deterministic
స్థిర uint32_t av_get_random_విత్తనం_deterministic(శూన్య);

#నిర్వచించు av_gettime() 1331972053200000

#అయితే_ముగింపు

పూర్ణాంకం av_parse_నిష్పత్తి(AVRational *q, స్థిరరాశి అక్షరం *str, పూర్ణాంకం max,
                   పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    అక్షరం c;
    పూర్ణాంకం ret;

    ఒకవేళ (అక్షరశ్రేణి_చదువు(str, "%d:%d%c", &q->అంకె, &q->den, &c) != 2) {
        ద్విగుణ d;
        ret = av_సమాసం_parse_and_eval(&d, str, ఖాళీ, ఖాళీ,
                                     ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ,
                                     ఖాళీ, log_స్థానభ్రంశం, log_ctx);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        *q = av_d2q(d, max);
    } లేకపోతే {
        av_reduce(&q->అంకె, &q->den, q->అంకె, q->den, max);
    }

    తిరిగి 0;
}

రకనిర్వచనం నిర్మాణం Video_కొలత_Abbr {
    స్థిరరాశి అక్షరం *abbr;
    పూర్ణాంకం వెడల్పు, ఎత్తు;
} Video_కొలత_Abbr;

రకనిర్వచనం నిర్మాణం Video_రేటు_Abbr {
    స్థిరరాశి అక్షరం *abbr;
    AVRational రేటు;
} Video_రేటు_Abbr;

స్థిర స్థిరరాశి Video_కొలత_Abbr video_కొలత_abbrs[] = {
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

స్థిర స్థిరరాశి Video_రేటు_Abbr video_రేటు_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

స్థిర స్థిరరాశి అక్షరం *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

పూర్ణాంకం av_parse_video_కొలత(పూర్ణాంకం *వెడల్పు_ptr, పూర్ణాంకం *ఎత్తు_ptr, స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం i;
    పూర్ణాంకం n = FF_ARRAY_ELEMS(video_కొలత_abbrs);
    స్థిరరాశి అక్షరం *p;
    పూర్ణాంకం వెడల్పు = 0, ఎత్తు = 0;

    కొరకు (i = 0; i < n; i++) {
        ఒకవేళ (!strcmp(video_కొలత_abbrs[i].abbr, str)) {
            వెడల్పు  = video_కొలత_abbrs[i].వెడల్పు;
            ఎత్తు = video_కొలత_abbrs[i].ఎత్తు;
            ఆపు;
        }
    }
    ఒకవేళ (i == n) {
        వెడల్పు = strtol(str, (శూన్య*)&p, 10);
        ఒకవేళ (*p)
            p++;
        ఎత్తు = strtol(p, (శూన్య*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        ఒకవేళ (*p)
            తిరిగి AVERROR(EINVAL);
    }
    ఒకవేళ (వెడల్పు <= 0 || ఎత్తు <= 0)
        తిరిగి AVERROR(EINVAL);
    *వెడల్పు_ptr  = వెడల్పు;
    *ఎత్తు_ptr = ఎత్తు;
    తిరిగి 0;
}

పూర్ణాంకం av_parse_video_రేటు(AVRational *రేటు, స్థిరరాశి అక్షరం *arg)
{
    పూర్ణాంకం i, ret;
    పూర్ణాంకం n = FF_ARRAY_ELEMS(video_రేటు_abbrs);

    /* First, we check our abbreviation table */
    కొరకు (i = 0; i < n; ++i)
        ఒకవేళ (!strcmp(video_రేటు_abbrs[i].abbr, arg)) {
            *రేటు = video_రేటు_abbrs[i].రేటు;
            తిరిగి 0;
        }

    /* Then, we try to parse it as fraction */
    ఒకవేళ ((ret = av_parse_నిష్పత్తి_quiet(రేటు, arg, 1001000)) < 0)
        తిరిగి ret;
    ఒకవేళ (!రేటు->అంకె || !రేటు->den)
        ఒకవేళ ((ret = av_parse_నిష్పత్తి_quiet(రేటు, arg, గరిష్ఠ_పూర్ణాంకం)) < 0)
            తిరిగి ret;
    ఒకవేళ (రేటు->అంకె <= 0 || రేటు->den <= 0)
        తిరిగి AVERROR(EINVAL);
    తిరిగి 0;
}

రకనిర్వచనం నిర్మాణం Color_నమోదు {
    స్థిరరాశి అక్షరం *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} Color_నమోదు;

స్థిర స్థిరరాశి Color_నమోదు color_పట్టిక[] = {
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

స్థిర పూర్ణాంకం color_పట్టిక_compare(స్థిరరాశి శూన్య *lhs, స్థిరరాశి శూన్య *rhs)
{
    తిరిగి av_strcasecmp(lhs, ((స్థిరరాశి Color_నమోదు *)rhs)->name);
}

#నిర్వచించు ALPHA_SEP '@'

పూర్ణాంకం av_parse_color(uint8_t *rgba_color, స్థిరరాశి అక్షరం *color_string, పూర్ణాంకం slen,
                   శూన్య *log_ctx)
{
    అక్షరం *తోక, color_string2[128];
    స్థిరరాశి Color_నమోదు *నమోదు_2;
    పూర్ణాంకం len, hex_స్థానభ్రంశం = 0;

    ఒకవేళ (color_string[0] == '#') {
        hex_స్థానభ్రంశం = 1;
    } లేకపోతే ఒకవేళ (!అక్షరశ్రేణి_పోలిక(color_string, "0x", 2))
        hex_స్థానభ్రంశం = 2;

    ఒకవేళ (slen < 0)
        slen = అక్షరశ్రేణి_పొడవు(color_string);
    av_strlcpy(color_string2, color_string + hex_స్థానభ్రంశం,
               FFMIN(slen-hex_స్థానభ్రంశం+1, పరిమాణం(color_string2)));
    ఒకవేళ ((తోక = strchr(color_string2, ALPHA_SEP)))
        *తోక++ = 0;
    len = అక్షరశ్రేణి_పొడవు(color_string2);
    rgba_color[3] = 255;

    ఒకవేళ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        పూర్ణాంకం rgba = av_get_random_విత్తనం();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } లేకపోతే ఒకవేళ (hex_స్థానభ్రంశం ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        అక్షరం *తోక;
        గుర్తులేని పూర్ణాంకం rgba = strtoul(color_string2, &తోక, 16);

        ఒకవేళ (*తోక || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            తిరిగి AVERROR(EINVAL);
        }
        ఒకవేళ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } లేకపోతే {
        నమోదు_2 = bsearch(color_string2,
                        color_పట్టిక,
                        FF_ARRAY_ELEMS(color_పట్టిక),
                        పరిమాణం(Color_నమోదు),
                        color_పట్టిక_compare);
        ఒకవేళ (!నమోదు_2) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            తిరిగి AVERROR(EINVAL);
        }
        జ్ఞాపకం_నకలు(rgba_color, నమోదు_2->rgb_color, 3);
    }

    ఒకవేళ (తోక) {
        ద్విగుణ alpha;
        స్థిరరాశి అక్షరం *alpha_string = తోక;
        ఒకవేళ (!అక్షరశ్రేణి_పోలిక(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &తోక, 16);
        } లేకపోతే {
            ద్విగుణ norm_alpha = strtod(alpha_string, &తోక);
            ఒకవేళ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            లేకపోతే
                alpha = 255 * norm_alpha;
        }

        ఒకవేళ (తోక == alpha_string || *తోక || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            తిరిగి AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    తిరిగి 0;
}

స్థిరరాశి అక్షరం *av_get_తెలిసిన_color_name(పూర్ణాంకం color_idx, స్థిరరాశి uint8_t **rgbp)
{
    స్థిరరాశి Color_నమోదు *color;

    ఒకవేళ ((గుర్తులేని)color_idx >= FF_ARRAY_ELEMS(color_పట్టిక))
        తిరిగి ఖాళీ;

    color = &color_పట్టిక[color_idx];
    ఒకవేళ (rgbp)
        *rgbp = color->rgb_color;

    తిరిగి color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
స్థిర పూర్ణాంకం date_get_అంకె(స్థిరరాశి అక్షరం **pp,
                        పూర్ణాంకం n_min, పూర్ణాంకం n_max, పూర్ణాంకం len_max)
{
    పూర్ణాంకం i, val, c;
    స్థిరరాశి అక్షరం *p;

    p = *pp;
    val = 0;
    కొరకు(i = 0; i < len_max; i++) {
        c = *p;
        ఒకవేళ (!av_isdigit(c))
            ఆపు;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    ఒకవేళ (p == *pp)
        తిరిగి -1;
    ఒకవేళ (val < n_min || val > n_max)
        తిరిగి -1;
    *pp = p;
    తిరిగి val;
}

స్థిర పూర్ణాంకం date_get_month(స్థిరరాశి అక్షరం **pp) {
    పూర్ణాంకం i = 0;
    కొరకు (; i < 12; i++) {
        ఒకవేళ (!av_strncasecmp(*pp, months[i], 3)) {
            స్థిరరాశి అక్షరం *mo_నిండిన = months[i] + 3;
            పూర్ణాంకం len = అక్షరశ్రేణి_పొడవు(mo_నిండిన);
            *pp += 3;
            ఒకవేళ (len > 0 && !av_strncasecmp(*pp, mo_నిండిన, len))
                *pp += len;
            తిరిగి i;
        }
    }
    తిరిగి -1;
}

అక్షరం *av_small_strptime(స్థిరరాశి అక్షరం *p, స్థిరరాశి అక్షరం *fmt, నిర్మాణం tm *dt)
{
    పూర్ణాంకం c, val;

    అయితే((c = *fmt++)) {
        ఒకవేళ (c != '%') {
            ఒకవేళ (av_isspace(c))
                కొరకు (; *p && av_isspace(*p); p++);
            లేకపోతే ఒకవేళ (*p != c)
                తిరిగి ఖాళీ;
            లేకపోతే p++;
            కొనసాగు;
        }

        c = *fmt++;
        ఎంపిక(c) {
        స్థితి 'H':
        స్థితి 'J':
            val = date_get_అంకె(&p, 0, c == 'H' ? 23 : గరిష్ఠ_పూర్ణాంకం, c == 'H' ? 2 : 4);

            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_hour = val;
            ఆపు;
        స్థితి 'M':
            val = date_get_అంకె(&p, 0, 59, 2);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_min = val;
            ఆపు;
        స్థితి 'S':
            val = date_get_అంకె(&p, 0, 59, 2);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_sec = val;
            ఆపు;
        స్థితి 'Y':
            val = date_get_అంకె(&p, 0, 9999, 4);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_year = val - 1900;
            ఆపు;
        స్థితి 'm':
            val = date_get_అంకె(&p, 1, 12, 2);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_mon = val - 1;
            ఆపు;
        స్థితి 'd':
            val = date_get_అంకె(&p, 1, 31, 2);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_mday = val;
            ఆపు;
        స్థితి 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            ఒకవేళ (!p)
                తిరిగి ఖాళీ;
            ఆపు;
        స్థితి 'b':
        స్థితి 'B':
        స్థితి 'h':
            val = date_get_month(&p);
            ఒకవేళ (val == -1)
                తిరిగి ఖాళీ;
            dt->tm_mon = val;
            ఆపు;
        స్థితి '%':
            ఒకవేళ (*p++ != '%')
                తిరిగి ఖాళీ;
            ఆపు;
        అప్రమేయ:
            తిరిగి ఖాళీ;
        }
    }

    తిరిగి (అక్షరం*)p;
}

time_t av_timegm(నిర్మాణం tm *tm)
{
    time_t t;

    పూర్ణాంకం y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    ఒకవేళ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    తిరిగి t;
}

పూర్ణాంకం av_parse_సమయం(int64_t *timeval, స్థిరరాశి అక్షరం *timestr, పూర్ణాంకం duration)
{
    స్థిరరాశి అక్షరం *p, *q;
    int64_t t, now64;
    time_t now;
    నిర్మాణం tm dt = { 0 }, tmbuf;
    పూర్ణాంకం today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    పూర్ణాంకం i;
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి సమయం_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = ఖాళీ;
    *timeval = INT64_MIN;
    ఒకవేళ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        ఒకవేళ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            తిరిగి 0;
        }

        /* parse the year-month-day part */
        కొరకు (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            ఒకవేళ (q)
                ఆపు;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        ఒకవేళ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        ఒకవేళ (*p == 'T' || *p == 't')
            p++;
        లేకపోతే
            అయితే (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        కొరకు (i = 0; i < FF_ARRAY_ELEMS(సమయం_fmt); i++) {
            q = av_small_strptime(p, సమయం_fmt[i], &dt);
            ఒకవేళ (q)
                ఆపు;
        }
    } లేకపోతే {
        /* parse timestr as a duration */
        ఒకవేళ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        ఒకవేళ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        ఒకవేళ (!q) {
            అక్షరం *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            ఒకవేళ (o == p) /* the parsing didn't succeed */
                తిరిగి AVERROR(EINVAL);
            ఒకవేళ (errno == ERANGE)
                తిరిగి AVERROR(ERANGE);
            q = o;
        } లేకపోతే {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    ఒకవేళ (!q)
        తిరిగి AVERROR(EINVAL);

    /* parse the .m... part */
    ఒకవేళ (*q == '.') {
        పూర్ణాంకం n;
        q++;
        కొరకు (n = 100000; n >= 1; n /= 10, q++) {
            ఒకవేళ (!av_isdigit(*q))
                ఆపు;
            microseconds += n * (*q - '0');
        }
        అయితే (av_isdigit(*q))
            q++;
    }

    ఒకవేళ (duration) {
        ఒకవేళ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } లేకపోతే ఒకవేళ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } లేకపోతే ఒకవేళ (*q == 's')
            q++;
    } లేకపోతే {
        పూర్ణాంకం is_utc = *q == 'Z' || *q == 'z';
        పూర్ణాంకం tzoffset = 0;
        q += is_utc;
        ఒకవేళ (!today && !is_utc && (*q == '+' || *q == '-')) {
            నిర్మాణం tm tz = { 0 };
            పూర్ణాంకం sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            కొరకు (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                ఒకవేళ (q)
                    ఆపు;
            }
            ఒకవేళ (!q)
                తిరిగి AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        ఒకవేళ (today) { /* fill in today's date */
            నిర్మాణం tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    ఒకవేళ (*q)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        తిరిగి AVERROR(ERANGE);
    t *= suffix;
    ఒకవేళ (INT64_MAX - microseconds < t)
        తిరిగి AVERROR(ERANGE);
    t += microseconds;
    ఒకవేళ (t == INT64_MIN && negative)
        తిరిగి AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    తిరిగి 0;
}

పూర్ణాంకం av_కనుగొను_info_ట్యాగ్(అక్షరం *arg, పూర్ణాంకం arg_కొలత, స్థిరరాశి అక్షరం *tag1, స్థిరరాశి అక్షరం *info)
{
    స్థిరరాశి అక్షరం *p;
    అక్షరం ట్యాగ్[128], *q;

    p = info;
    ఒకవేళ (*p == '?')
        p++;
    కొరకు(;;) {
        q = ట్యాగ్;
        అయితే (*p != '\0' && *p != '=' && *p != '&') {
            ఒకవేళ ((q - ట్యాగ్) < పరిమాణం(ట్యాగ్) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        ఒకవేళ (*p == '=') {
            p++;
            అయితే (*p != '&' && *p != '\0') {
                ఒకవేళ ((q - arg) < arg_కొలత - 1) {
                    ఒకవేళ (*p == '+')
                        *q++ = ' ';
                    లేకపోతే
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        ఒకవేళ (!strcmp(ట్యాగ్, tag1))
            తిరిగి 1;
        ఒకవేళ (*p != '&')
            ఆపు;
        p++;
    }
    తిరిగి 0;
}
