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

#समावेश <time.h>

#समावेश "avstring.h"
#समावेश "avutil.h"
#समावेश "common.h"
#समावेश "eval.h"
#समावेश "log.h"
#समावेश "random_seed.h"
#समावेश "time_internal.h"
#समावेश "parseutils.h"
#समावेश "time.h"

#अगर_घोषित TEST

#घोषणा av_get_random_seed av_get_random_seed_deterministic
अटल uint32_t av_get_random_seed_deterministic(व्योम);

#घोषणा av_gettime() 1331972053200000

#पूर्ण_अगर

पूर्णांक av_parse_ratio(AVRational *q, स्थिर अक्षर *str, पूर्णांक max,
                   पूर्णांक log_offset, व्योम *log_ctx)
{
    अक्षर c;
    पूर्णांक ret;

    अगर (माला_पूछो(str, "%d:%d%c", &q->अंक, &q->den, &c) != 2) {
        द्विगुन d;
        ret = av_व्यंजक_parse_and_eval(&d, str, शून्य, शून्य,
                                     शून्य, शून्य, शून्य, शून्य,
                                     शून्य, log_offset, log_ctx);
        अगर (ret < 0)
            वापस ret;
        *q = av_d2q(d, max);
    } अन्यथा {
        av_reduce(&q->अंक, &q->den, q->अंक, q->den, max);
    }

    वापस 0;
}

प्रकार काष्ठा Video_आकार_Abbr {
    स्थिर अक्षर *abbr;
    पूर्णांक width, height;
} Video_आकार_Abbr;

प्रकार काष्ठा VideoRateAbbr {
    स्थिर अक्षर *abbr;
    AVRational rate;
} VideoRateAbbr;

अटल स्थिर Video_आकार_Abbr video_आकार_abbrs[] = {
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

अटल स्थिर VideoRateAbbr video_rate_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

अटल स्थिर अक्षर *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

पूर्णांक av_parse_video_आकार(पूर्णांक *width_ptr, पूर्णांक *height_ptr, स्थिर अक्षर *str)
{
    पूर्णांक i;
    पूर्णांक n = FF_ARRAY_ELEMS(video_आकार_abbrs);
    स्थिर अक्षर *p;
    पूर्णांक width = 0, height = 0;

    क्रम (i = 0; i < n; i++) {
        अगर (!म_भेद(video_आकार_abbrs[i].abbr, str)) {
            width  = video_आकार_abbrs[i].width;
            height = video_आकार_abbrs[i].height;
            अवरोध;
        }
    }
    अगर (i == n) {
        width = म_से_दीर्घ(str, (व्योम*)&p, 10);
        अगर (*p)
            p++;
        height = म_से_दीर्घ(p, (व्योम*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        अगर (*p)
            वापस AVERROR(EINVAL);
    }
    अगर (width <= 0 || height <= 0)
        वापस AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    वापस 0;
}

पूर्णांक av_parse_video_rate(AVRational *rate, स्थिर अक्षर *arg)
{
    पूर्णांक i, ret;
    पूर्णांक n = FF_ARRAY_ELEMS(video_rate_abbrs);

    /* First, we check our abbreviation table */
    क्रम (i = 0; i < n; ++i)
        अगर (!म_भेद(video_rate_abbrs[i].abbr, arg)) {
            *rate = video_rate_abbrs[i].rate;
            वापस 0;
        }

    /* Then, we try to parse it as fraction */
    अगर ((ret = av_parse_ratio_quiet(rate, arg, 1001000)) < 0)
        वापस ret;
    अगर (!rate->अंक || !rate->den)
        अगर ((ret = av_parse_ratio_quiet(rate, arg, पूर्णांक_उच्च)) < 0)
            वापस ret;
    अगर (rate->अंक <= 0 || rate->den <= 0)
        वापस AVERROR(EINVAL);
    वापस 0;
}

प्रकार काष्ठा ColorEntry {
    स्थिर अक्षर *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} ColorEntry;

अटल स्थिर ColorEntry color_table[] = {
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

अटल पूर्णांक color_table_compare(स्थिर व्योम *lhs, स्थिर व्योम *rhs)
{
    वापस av_strcasecmp(lhs, ((स्थिर ColorEntry *)rhs)->name);
}

#घोषणा ALPHA_SEP '@'

पूर्णांक av_parse_color(uint8_t *rgba_color, स्थिर अक्षर *color_string, पूर्णांक slen,
                   व्योम *log_ctx)
{
    अक्षर *पुच्छ, color_string2[128];
    स्थिर ColorEntry *entry;
    पूर्णांक len, hex_offset = 0;

    अगर (color_string[0] == '#') {
        hex_offset = 1;
    } अन्यथा अगर (!म_भेदन(color_string, "0x", 2))
        hex_offset = 2;

    अगर (slen < 0)
        slen = म_माप(color_string);
    av_strlcpy(color_string2, color_string + hex_offset,
               FFMIN(slen-hex_offset+1, माप(color_string2)));
    अगर ((पुच्छ = म_अक्षर(color_string2, ALPHA_SEP)))
        *पुच्छ++ = 0;
    len = म_माप(color_string2);
    rgba_color[3] = 255;

    अगर (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        पूर्णांक rgba = av_get_random_seed();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } अन्यथा अगर (hex_offset ||
               म_अखोज(color_string2, "0123456789ABCDEFabcdef") == len) {
        अक्षर *पुच्छ;
        अचिन्हित पूर्णांक rgba = म_से_अदीर्घ(color_string2, &पुच्छ, 16);

        अगर (*पुच्छ || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            वापस AVERROR(EINVAL);
        }
        अगर (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } अन्यथा {
        entry = द्वा_खोज(color_string2,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        माप(ColorEntry),
                        color_table_compare);
        अगर (!entry) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            वापस AVERROR(EINVAL);
        }
        स_नकल(rgba_color, entry->rgb_color, 3);
    }

    अगर (पुच्छ) {
        द्विगुन alpha;
        स्थिर अक्षर *alpha_string = पुच्छ;
        अगर (!म_भेदन(alpha_string, "0x", 2)) {
            alpha = म_से_अदीर्घ(alpha_string, &पुच्छ, 16);
        } अन्यथा {
            द्विगुन norm_alpha = म_से_भग्न(alpha_string, &पुच्छ);
            अगर (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            अन्यथा
                alpha = 255 * norm_alpha;
        }

        अगर (पुच्छ == alpha_string || *पुच्छ || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            वापस AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    वापस 0;
}

स्थिर अक्षर *av_get_known_color_name(पूर्णांक color_idx, स्थिर uint8_t **rgbp)
{
    स्थिर ColorEntry *color;

    अगर ((अचिन्हित)color_idx >= FF_ARRAY_ELEMS(color_table))
        वापस शून्य;

    color = &color_table[color_idx];
    अगर (rgbp)
        *rgbp = color->rgb_color;

    वापस color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
अटल पूर्णांक date_get_अंक(स्थिर अक्षर **pp,
                        पूर्णांक n_min, पूर्णांक n_max, पूर्णांक len_max)
{
    पूर्णांक i, val, c;
    स्थिर अक्षर *p;

    p = *pp;
    val = 0;
    क्रम(i = 0; i < len_max; i++) {
        c = *p;
        अगर (!av_isdigit(c))
            अवरोध;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    अगर (p == *pp)
        वापस -1;
    अगर (val < n_min || val > n_max)
        वापस -1;
    *pp = p;
    वापस val;
}

अटल पूर्णांक date_get_month(स्थिर अक्षर **pp) {
    पूर्णांक i = 0;
    क्रम (; i < 12; i++) {
        अगर (!av_strncasecmp(*pp, months[i], 3)) {
            स्थिर अक्षर *mo_full = months[i] + 3;
            पूर्णांक len = म_माप(mo_full);
            *pp += 3;
            अगर (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            वापस i;
        }
    }
    वापस -1;
}

अक्षर *av_small_strptime(स्थिर अक्षर *p, स्थिर अक्षर *fmt, काष्ठा पंचांग *dt)
{
    पूर्णांक c, val;

    जबतक((c = *fmt++)) {
        अगर (c != '%') {
            अगर (av_isspace(c))
                क्रम (; *p && av_isspace(*p); p++);
            अन्यथा अगर (*p != c)
                वापस शून्य;
            अन्यथा p++;
            जारी;
        }

        c = *fmt++;
        चयन(c) {
        हाल 'H':
        हाल 'J':
            val = date_get_अंक(&p, 0, c == 'H' ? 23 : पूर्णांक_उच्च, c == 'H' ? 2 : 4);

            अगर (val == -1)
                वापस शून्य;
            dt->tm_hour = val;
            अवरोध;
        हाल 'M':
            val = date_get_अंक(&p, 0, 59, 2);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_min = val;
            अवरोध;
        हाल 'S':
            val = date_get_अंक(&p, 0, 59, 2);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_sec = val;
            अवरोध;
        हाल 'Y':
            val = date_get_अंक(&p, 0, 9999, 4);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_year = val - 1900;
            अवरोध;
        हाल 'm':
            val = date_get_अंक(&p, 1, 12, 2);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_mon = val - 1;
            अवरोध;
        हाल 'd':
            val = date_get_अंक(&p, 1, 31, 2);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_mday = val;
            अवरोध;
        हाल 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            अगर (!p)
                वापस शून्य;
            अवरोध;
        हाल 'b':
        हाल 'B':
        हाल 'h':
            val = date_get_month(&p);
            अगर (val == -1)
                वापस शून्य;
            dt->tm_mon = val;
            अवरोध;
        हाल '%':
            अगर (*p++ != '%')
                वापस शून्य;
            अवरोध;
        शेष:
            वापस शून्य;
        }
    }

    वापस (अक्षर*)p;
}

समय_प्रकार av_timegm(काष्ठा पंचांग *पंचांग)
{
    समय_प्रकार t;

    पूर्णांक y = पंचांग->tm_year + 1900, m = पंचांग->tm_mon + 1, d = पंचांग->tm_mday;

    अगर (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * पंचांग->tm_hour + 60 * पंचांग->tm_min + पंचांग->tm_sec;

    वापस t;
}

पूर्णांक av_parse_time(int64_t *timeval, स्थिर अक्षर *timestr, पूर्णांक duration)
{
    स्थिर अक्षर *p, *q;
    int64_t t, now64;
    समय_प्रकार now;
    काष्ठा पंचांग dt = { 0 }, tmbuf;
    पूर्णांक today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    पूर्णांक i;
    अटल स्थिर अक्षर * स्थिर date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    अटल स्थिर अक्षर * स्थिर time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    अटल स्थिर अक्षर * स्थिर tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = शून्य;
    *timeval = INT64_MIN;
    अगर (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        अगर (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            वापस 0;
        }

        /* parse the year-month-day part */
        क्रम (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            अगर (q)
                अवरोध;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        अगर (!q) {
            today = 1;
            q = p;
        }
        p = q;

        अगर (*p == 'T' || *p == 't')
            p++;
        अन्यथा
            जबतक (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        क्रम (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            अगर (q)
                अवरोध;
        }
    } अन्यथा {
        /* parse timestr as a duration */
        अगर (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        अगर (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        अगर (!q) {
            अक्षर *o;
            /* parse timestr as S+ */
            त्रुटि_सं = 0;
            t = strtoll(p, &o, 10);
            अगर (o == p) /* the parsing didn't succeed */
                वापस AVERROR(EINVAL);
            अगर (त्रुटि_सं == दुस्फल)
                वापस AVERROR(दुस्फल);
            q = o;
        } अन्यथा {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    अगर (!q)
        वापस AVERROR(EINVAL);

    /* parse the .m... part */
    अगर (*q == '.') {
        पूर्णांक n;
        q++;
        क्रम (n = 100000; n >= 1; n /= 10, q++) {
            अगर (!av_isdigit(*q))
                अवरोध;
            microseconds += n * (*q - '0');
        }
        जबतक (av_isdigit(*q))
            q++;
    }

    अगर (duration) {
        अगर (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } अन्यथा अगर (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } अन्यथा अगर (*q == 's')
            q++;
    } अन्यथा {
        पूर्णांक is_utc = *q == 'Z' || *q == 'z';
        पूर्णांक tzoffset = 0;
        q += is_utc;
        अगर (!today && !is_utc && (*q == '+' || *q == '-')) {
            काष्ठा पंचांग tz = { 0 };
            पूर्णांक sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            क्रम (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                अगर (q)
                    अवरोध;
            }
            अगर (!q)
                वापस AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        अगर (today) { /* fill in today's date */
            काष्ठा पंचांग dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
            dt2.tm_hour = dt.tm_hour;
            dt2.tm_min  = dt.tm_min;
            dt2.tm_sec  = dt.tm_sec;
            dt = dt2;
        }
        dt.tm_isdst = is_utc ? 0 : -1;
        t = is_utc ? av_timegm(&dt) : स_गढ़ो(&dt);
        t += tzoffset;
    }

    /* Check that we are at the end of the string */
    अगर (*q)
        वापस AVERROR(EINVAL);

    अगर (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        वापस AVERROR(दुस्फल);
    t *= suffix;
    अगर (INT64_MAX - microseconds < t)
        वापस AVERROR(दुस्फल);
    t += microseconds;
    अगर (t == INT64_MIN && negative)
        वापस AVERROR(दुस्फल);
    *timeval = negative ? -t : t;
    वापस 0;
}

पूर्णांक av_find_info_tag(अक्षर *arg, पूर्णांक arg_आकार, स्थिर अक्षर *tag1, स्थिर अक्षर *info)
{
    स्थिर अक्षर *p;
    अक्षर tag[128], *q;

    p = info;
    अगर (*p == '?')
        p++;
    क्रम(;;) {
        q = tag;
        जबतक (*p != '\0' && *p != '=' && *p != '&') {
            अगर ((q - tag) < माप(tag) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        अगर (*p == '=') {
            p++;
            जबतक (*p != '&' && *p != '\0') {
                अगर ((q - arg) < arg_आकार - 1) {
                    अगर (*p == '+')
                        *q++ = ' ';
                    अन्यथा
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        अगर (!म_भेद(tag, tag1))
            वापस 1;
        अगर (*p != '&')
            अवरोध;
        p++;
    }
    वापस 0;
}
