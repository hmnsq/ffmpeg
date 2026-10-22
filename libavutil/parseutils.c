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

#include <time.h>

#include "avstring.h"
#include "avutil.h"
#include "common.h"
#include "eval.h"
#include "log.h"
#include "random_seed.h"
#include "time_internal.h"
#include "parseutils.h"
#include "time.h"

#ifdef TEST

#define av_get_random_seed av_get_random_seed_deterministic
static uint32_t av_get_random_seed_deterministic(void);

#define av_gettime() 1331972053200000

#endif

ཧྲིལ av_parse_ratio(AVRational *q, const var_na *str, ཧྲིལ max,
                   ཧྲིལ log_offset, void *log_ctx)
{
    var_na c;
    ཧྲིལ ret;

    གལ་ཏེ (sscanf(str, "%d:%d%c", &q->num, &q->den, &c) != 2) {
        dviguu_na d;
        ret = av_expr_parse_and_eval(&d, str, NULL, NULL,
                                     NULL, NULL, NULL, NULL,
                                     NULL, log_offset, log_ctx);
        གལ་ཏེ (ret < 0)
            ཕྱིར ret;
        *q = av_d2q(d, max);
    } དེ་མིན {
        av_reduce(&q->num, &q->den, q->num, q->den, max);
    }

    ཕྱིར 0;
}

typedef sa_nracanaa VideoSizeAbbr {
    const var_na *abbr;
    ཧྲིལ width, height;
} VideoSizeAbbr;

typedef sa_nracanaa VideoRateAbbr {
    const var_na *abbr;
    AVRational rate;
} VideoRateAbbr;

static const VideoSizeAbbr video_size_abbrs[] = {
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

static const VideoRateAbbr video_rate_abbrs[]= {
    { "ntsc",      { 30000, 1001 } },
    { "pal",       {    25,    1 } },
    { "qntsc",     { 30000, 1001 } }, /* VCD compliant NTSC */
    { "qpal",      {    25,    1 } }, /* VCD compliant PAL */
    { "sntsc",     { 30000, 1001 } }, /* square pixel NTSC */
    { "spal",      {    25,    1 } }, /* square pixel PAL */
    { "film",      {    24,    1 } },
    { "ntsc-film", { 24000, 1001 } },
};

static const var_na *months[12] = {
    "january", "february", "march", "april", "may", "june", "july", "august",
    "september", "october", "november", "december"
};

ཧྲིལ av_parse_video_size(ཧྲིལ *width_ptr, ཧྲིལ *height_ptr, const var_na *str)
{
    ཧྲིལ i;
    ཧྲིལ n = FF_ARRAY_ELEMS(video_size_abbrs);
    const var_na *p;
    ཧྲིལ width = 0, height = 0;

    ཆེད་དུ (i = 0; i < n; i++) {
        གལ་ཏེ (!strcmp(video_size_abbrs[i].abbr, str)) {
            width  = video_size_abbrs[i].width;
            height = video_size_abbrs[i].height;
            bha_nga;
        }
    }
    གལ་ཏེ (i == n) {
        width = strtol(str, (void*)&p, 10);
        གལ་ཏེ (*p)
            p++;
        height = strtol(p, (void*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        གལ་ཏེ (*p)
            ཕྱིར AVERROR(EINVAL);
    }
    གལ་ཏེ (width <= 0 || height <= 0)
        ཕྱིར AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    ཕྱིར 0;
}

ཧྲིལ av_parse_video_rate(AVRational *rate, const var_na *arg)
{
    ཧྲིལ i, ret;
    ཧྲིལ n = FF_ARRAY_ELEMS(video_rate_abbrs);

    /* First, we check our abbreviation table */
    ཆེད་དུ (i = 0; i < n; ++i)
        གལ་ཏེ (!strcmp(video_rate_abbrs[i].abbr, arg)) {
            *rate = video_rate_abbrs[i].rate;
            ཕྱིར 0;
        }

    /* Then, we try to parse it as fraction */
    གལ་ཏེ ((ret = av_parse_ratio_quiet(rate, arg, 1001000)) < 0)
        ཕྱིར ret;
    གལ་ཏེ (!rate->num || !rate->den)
        གལ་ཏེ ((ret = av_parse_ratio_quiet(rate, arg, INT_MAX)) < 0)
            ཕྱིར ret;
    གལ་ཏེ (rate->num <= 0 || rate->den <= 0)
        ཕྱིར AVERROR(EINVAL);
    ཕྱིར 0;
}

typedef sa_nracanaa ColorEntry {
    const var_na *name;            ///< a string representing the name of the color
    uint8_t     rgb_color[3];    ///< RGB values for the color
} ColorEntry;

static const ColorEntry color_table[] = {
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

static ཧྲིལ color_table_compare(const void *lhs, const void *rhs)
{
    ཕྱིར av_strcasecmp(lhs, ((const ColorEntry *)rhs)->name);
}

#define ALPHA_SEP '@'

ཧྲིལ av_parse_color(uint8_t *rgba_color, const var_na *color_string, ཧྲིལ slen,
                   void *log_ctx)
{
    var_na *tail, color_string2[128];
    const ColorEntry *entry;
    ཧྲིལ len, hex_offset = 0;

    གལ་ཏེ (color_string[0] == '#') {
        hex_offset = 1;
    } དེ་མིན གལ་ཏེ (!strncmp(color_string, "0x", 2))
        hex_offset = 2;

    གལ་ཏེ (slen < 0)
        slen = strlen(color_string);
    av_strlcpy(color_string2, color_string + hex_offset,
               FFMIN(slen-hex_offset+1, parimaa_na(color_string2)));
    གལ་ཏེ ((tail = strchr(color_string2, ALPHA_SEP)))
        *tail++ = 0;
    len = strlen(color_string2);
    rgba_color[3] = 255;

    གལ་ཏེ (!av_strcasecmp(color_string2, "random") || !av_strcasecmp(color_string2, "bikeshed")) {
        ཧྲིལ rgba = av_get_random_seed();
        rgba_color[0] = rgba >> 24;
        rgba_color[1] = rgba >> 16;
        rgba_color[2] = rgba >> 8;
        rgba_color[3] = rgba;
    } དེ་མིན གལ་ཏེ (hex_offset ||
               strspn(color_string2, "0123456789ABCDEFabcdef") == len) {
        var_na *tail;
        unsigned ཧྲིལ rgba = strtoul(color_string2, &tail, 16);

        གལ་ཏེ (*tail || (len != 6 && len != 8)) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid 0xRRGGBB[AA] color string: '%s'\n", color_string2);
            ཕྱིར AVERROR(EINVAL);
        }
        གལ་ཏེ (len == 8) {
            rgba_color[3] = rgba;
            rgba >>= 8;
        }
        rgba_color[0] = rgba >> 16;
        rgba_color[1] = rgba >> 8;
        rgba_color[2] = rgba;
    } དེ་མིན {
        entry = bsearch(color_string2,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        parimaa_na(ColorEntry),
                        color_table_compare);
        གལ་ཏེ (!entry) {
            av_log(log_ctx, AV_LOG_ERROR, "Cannot find color '%s'\n", color_string2);
            ཕྱིར AVERROR(EINVAL);
        }
        memcpy(rgba_color, entry->rgb_color, 3);
    }

    གལ་ཏེ (tail) {
        dviguu_na alpha;
        const var_na *alpha_string = tail;
        གལ་ཏེ (!strncmp(alpha_string, "0x", 2)) {
            alpha = strtoul(alpha_string, &tail, 16);
        } དེ་མིན {
            dviguu_na norm_alpha = strtod(alpha_string, &tail);
            གལ་ཏེ (norm_alpha < 0.0 || norm_alpha > 1.0)
                alpha = 256;
            དེ་མིན
                alpha = 255 * norm_alpha;
        }

        གལ་ཏེ (tail == alpha_string || *tail || alpha > 255 || alpha < 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid alpha value specifier '%s' in '%s'\n",
                   alpha_string, color_string);
            ཕྱིར AVERROR(EINVAL);
        }
        rgba_color[3] = alpha;
    }

    ཕྱིར 0;
}

const var_na *av_get_known_color_name(ཧྲིལ color_idx, const uint8_t **rgbp)
{
    const ColorEntry *color;

    གལ་ཏེ ((unsigned)color_idx >= FF_ARRAY_ELEMS(color_table))
        ཕྱིར NULL;

    color = &color_table[color_idx];
    གལ་ཏེ (rgbp)
        *rgbp = color->rgb_color;

    ཕྱིར color->name;
}

/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
static ཧྲིལ date_get_num(const var_na **pp,
                        ཧྲིལ n_min, ཧྲིལ n_max, ཧྲིལ len_max)
{
    ཧྲིལ i, val, c;
    const var_na *p;

    p = *pp;
    val = 0;
    ཆེད་དུ(i = 0; i < len_max; i++) {
        c = *p;
        གལ་ཏེ (!av_isdigit(c))
            bha_nga;
        val = (val * 10) + c - '0';
        p++;
    }
    /* no number read ? */
    གལ་ཏེ (p == *pp)
        ཕྱིར -1;
    གལ་ཏེ (val < n_min || val > n_max)
        ཕྱིར -1;
    *pp = p;
    ཕྱིར val;
}

static ཧྲིལ date_get_month(const var_na **pp) {
    ཧྲིལ i = 0;
    ཆེད་དུ (; i < 12; i++) {
        གལ་ཏེ (!av_strncasecmp(*pp, months[i], 3)) {
            const var_na *mo_full = months[i] + 3;
            ཧྲིལ len = strlen(mo_full);
            *pp += 3;
            གལ་ཏེ (len > 0 && !av_strncasecmp(*pp, mo_full, len))
                *pp += len;
            ཕྱིར i;
        }
    }
    ཕྱིར -1;
}

var_na *av_small_strptime(const var_na *p, const var_na *fmt, sa_nracanaa tm *dt)
{
    ཧྲིལ c, val;

    སྐབས((c = *fmt++)) {
        གལ་ཏེ (c != '%') {
            གལ་ཏེ (av_isspace(c))
                ཆེད་དུ (; *p && av_isspace(*p); p++);
            དེ་མིན གལ་ཏེ (*p != c)
                ཕྱིར NULL;
            དེ་མིན p++;
            continue;
        }

        c = *fmt++;
        switch(c) {
        pak_sa 'H':
        pak_sa 'J':
            val = date_get_num(&p, 0, c == 'H' ? 23 : INT_MAX, c == 'H' ? 2 : 4);

            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_hour = val;
            bha_nga;
        pak_sa 'M':
            val = date_get_num(&p, 0, 59, 2);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_min = val;
            bha_nga;
        pak_sa 'S':
            val = date_get_num(&p, 0, 59, 2);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_sec = val;
            bha_nga;
        pak_sa 'Y':
            val = date_get_num(&p, 0, 9999, 4);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_year = val - 1900;
            bha_nga;
        pak_sa 'm':
            val = date_get_num(&p, 1, 12, 2);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_mon = val - 1;
            bha_nga;
        pak_sa 'd':
            val = date_get_num(&p, 1, 31, 2);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_mday = val;
            bha_nga;
        pak_sa 'T':
            p = av_small_strptime(p, "%H:%M:%S", dt);
            གལ་ཏེ (!p)
                ཕྱིར NULL;
            bha_nga;
        pak_sa 'b':
        pak_sa 'B':
        pak_sa 'h':
            val = date_get_month(&p);
            གལ་ཏེ (val == -1)
                ཕྱིར NULL;
            dt->tm_mon = val;
            bha_nga;
        pak_sa '%':
            གལ་ཏེ (*p++ != '%')
                ཕྱིར NULL;
            bha_nga;
        default:
            ཕྱིར NULL;
        }
    }

    ཕྱིར (var_na*)p;
}

time_t av_timegm(sa_nracanaa tm *tm)
{
    time_t t;

    ཧྲིལ y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    གལ་ཏེ (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    ཕྱིར t;
}

ཧྲིལ av_parse_time(int64_t *timeval, const var_na *timestr, ཧྲིལ duration)
{
    const var_na *p, *q;
    int64_t t, now64;
    time_t now;
    sa_nracanaa tm dt = { 0 }, tmbuf;
    ཧྲིལ today = 0, negative = 0, microseconds = 0, suffix = 1000000;
    ཧྲིལ i;
    static const var_na * const date_fmt[] = {
        "%Y - %m - %d",
        "%Y%m%d",
    };
    static const var_na * const time_fmt[] = {
        "%H:%M:%S",
        "%H%M%S",
    };
    static const var_na * const tz_fmt[] = {
        "%H:%M",
        "%H%M",
        "%H",
    };

    p = timestr;
    q = NULL;
    *timeval = INT64_MIN;
    གལ་ཏེ (!duration) {
        now64 = av_gettime();
        now = now64 / 1000000;

        གལ་ཏེ (!av_strcasecmp(timestr, "now")) {
            *timeval = now64;
            ཕྱིར 0;
        }

        /* parse the year-month-day part */
        ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(date_fmt); i++) {
            q = av_small_strptime(p, date_fmt[i], &dt);
            གལ་ཏེ (q)
                bha_nga;
        }

        /* if the year-month-day part is missing, then take the
         * current year-month-day time */
        གལ་ཏེ (!q) {
            today = 1;
            q = p;
        }
        p = q;

        གལ་ཏེ (*p == 'T' || *p == 't')
            p++;
        དེ་མིན
            སྐབས (av_isspace(*p))
                p++;

        /* parse the hour-minute-second part */
        ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(time_fmt); i++) {
            q = av_small_strptime(p, time_fmt[i], &dt);
            གལ་ཏེ (q)
                bha_nga;
        }
    } དེ་མིན {
        /* parse timestr as a duration */
        གལ་ཏེ (p[0] == '-') {
            negative = 1;
            ++p;
        }
        /* parse timestr as HH:MM:SS */
        q = av_small_strptime(p, "%J:%M:%S", &dt);
        གལ་ཏེ (!q) {
            /* parse timestr as MM:SS */
            q = av_small_strptime(p, "%M:%S", &dt);
            dt.tm_hour = 0;
        }
        གལ་ཏེ (!q) {
            var_na *o;
            /* parse timestr as S+ */
            errno = 0;
            t = strtoll(p, &o, 10);
            གལ་ཏེ (o == p) /* the parsing didn't succeed */
                ཕྱིར AVERROR(EINVAL);
            གལ་ཏེ (errno == ERANGE)
                ཕྱིར AVERROR(ERANGE);
            q = o;
        } དེ་མིན {
            t = dt.tm_hour * 3600 + dt.tm_min * 60 + dt.tm_sec;
        }
    }

    /* Now we have all the fields that we can get */
    གལ་ཏེ (!q)
        ཕྱིར AVERROR(EINVAL);

    /* parse the .m... part */
    གལ་ཏེ (*q == '.') {
        ཧྲིལ n;
        q++;
        ཆེད་དུ (n = 100000; n >= 1; n /= 10, q++) {
            གལ་ཏེ (!av_isdigit(*q))
                bha_nga;
            microseconds += n * (*q - '0');
        }
        སྐབས (av_isdigit(*q))
            q++;
    }

    གལ་ཏེ (duration) {
        གལ་ཏེ (q[0] == 'm' && q[1] == 's') {
            suffix = 1000;
            microseconds /= 1000;
            q += 2;
        } དེ་མིན གལ་ཏེ (q[0] == 'u' && q[1] == 's') {
            suffix = 1;
            microseconds = 0;
            q += 2;
        } དེ་མིན གལ་ཏེ (*q == 's')
            q++;
    } དེ་མིན {
        ཧྲིལ is_utc = *q == 'Z' || *q == 'z';
        ཧྲིལ tzoffset = 0;
        q += is_utc;
        གལ་ཏེ (!today && !is_utc && (*q == '+' || *q == '-')) {
            sa_nracanaa tm tz = { 0 };
            ཧྲིལ sign = (*q == '+' ? -1 : 1);
            q++;
            p = q;
            ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(tz_fmt); i++) {
                q = av_small_strptime(p, tz_fmt[i], &tz);
                གལ་ཏེ (q)
                    bha_nga;
            }
            གལ་ཏེ (!q)
                ཕྱིར AVERROR(EINVAL);
            tzoffset = sign * (tz.tm_hour * 60 + tz.tm_min) * 60;
            is_utc = 1;
        }
        གལ་ཏེ (today) { /* fill in today's date */
            sa_nracanaa tm dt2 = is_utc ? *gmtime_r(&now, &tmbuf) : *localtime_r(&now, &tmbuf);
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
    གལ་ཏེ (*q)
        ཕྱིར AVERROR(EINVAL);

    གལ་ཏེ (INT64_MAX / suffix < t || t < INT64_MIN / suffix)
        ཕྱིར AVERROR(ERANGE);
    t *= suffix;
    གལ་ཏེ (INT64_MAX - microseconds < t)
        ཕྱིར AVERROR(ERANGE);
    t += microseconds;
    གལ་ཏེ (t == INT64_MIN && negative)
        ཕྱིར AVERROR(ERANGE);
    *timeval = negative ? -t : t;
    ཕྱིར 0;
}

ཧྲིལ av_find_info_tag(var_na *arg, ཧྲིལ arg_size, const var_na *tag1, const var_na *info)
{
    const var_na *p;
    var_na tag[128], *q;

    p = info;
    གལ་ཏེ (*p == '?')
        p++;
    ཆེད་དུ(;;) {
        q = tag;
        སྐབས (*p != '\0' && *p != '=' && *p != '&') {
            གལ་ཏེ ((q - tag) < parimaa_na(tag) - 1)
                *q++ = *p;
            p++;
        }
        *q = '\0';
        q = arg;
        གལ་ཏེ (*p == '=') {
            p++;
            སྐབས (*p != '&' && *p != '\0') {
                གལ་ཏེ ((q - arg) < arg_size - 1) {
                    གལ་ཏེ (*p == '+')
                        *q++ = ' ';
                    དེ་མིན
                        *q++ = *p;
                }
                p++;
            }
        }
        *q = '\0';
        གལ་ཏེ (!strcmp(tag, tag1))
            ཕྱིར 1;
        གལ་ཏེ (*p != '&')
            bha_nga;
        p++;
    }
    ཕྱིར 0;
}
