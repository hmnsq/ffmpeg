/*
 * log functions
 * Copyright (c) 2003 Michel Bardiaux
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

/**
 * @file
 * logging functions
 */

#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "bprint.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "internal.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "time.h"
#ಅನ್ತರ್ಭಾವ "time_internal.h"

ಸ್ಥಿರ AVMutex mutex = AV_MUTEX_INITIALIZER;

#ವ್ಯಾಖ್ಯಾನಿಸು ಸಾಲು_SZ 1024

#ಆದರೆ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#ಅನ್ತರ್ಭಾವ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#ವ್ಯಾಖ್ಯಾನಿಸು BACKTRACE_LOGLEVEL AV_LOG_ERROR
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ atomic_int av_log_level = AV_LOG_INFO;
ಸ್ಥಿರ atomic_int av_log_flags = 0;

#ವ್ಯಾಖ್ಯಾನಿಸು NB_ಮಟ್ಟಗಳು 8
#ಆದರೆ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#ಅನ್ತರ್ಭಾವ <windows.h>
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_ಒಳಹರಿವು           ] = 13,
    [16+AV_CLASS_CATEGORY_OUTPUT          ] =  5,
    [16+AV_CLASS_CATEGORY_MUXER           ] = 13,
    [16+AV_CLASS_CATEGORY_DEMUXER         ] =  5,
    [16+AV_CLASS_CATEGORY_ENCODER         ] = 11,
    [16+AV_CLASS_CATEGORY_DECODER         ] =  3,
    [16+AV_CLASS_CATEGORY_FILTER          ] = 10,
    [16+AV_CLASS_CATEGORY_BITSTREAM_FILTER] =  9,
    [16+AV_CLASS_CATEGORY_SWSCALER        ] =  7,
    [16+AV_CLASS_CATEGORY_SWRESAMPLER     ] =  7,
    [16+AV_CLASS_CATEGORY_HWDEVICE        ] =  6,
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ಒಳಹರಿವು  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ಒಳಹರಿವು  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_ಒಳಹರಿವು        ] = 5,
};

ಸ್ಥಿರ int16_t background, attr_orig;
ಸ್ಥಿರ HANDLE con;
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_ಒಳಹರಿವು           ] = 219 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_OUTPUT          ] = 201 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_MUXER           ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEMUXER         ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_ENCODER         ] =  51 << 8 | 0x16,
    [16+AV_CLASS_CATEGORY_DECODER         ] =  39 << 8 | 0x06,
    [16+AV_CLASS_CATEGORY_FILTER          ] = 155 << 8 | 0x12,
    [16+AV_CLASS_CATEGORY_BITSTREAM_FILTER] = 192 << 8 | 0x14,
    [16+AV_CLASS_CATEGORY_SWSCALER        ] = 153 << 8 | 0x14,
    [16+AV_CLASS_CATEGORY_SWRESAMPLER     ] = 147 << 8 | 0x14,
    [16+AV_CLASS_CATEGORY_HWDEVICE        ] = 214 << 8 | 0x13,
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ಒಳಹರಿವು  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ಒಳಹರಿವು  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_ಒಳಹರಿವು        ] = 207 << 8 | 0x05,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ use_color = -1;

#ಆದರೆ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ಸ್ಥಿರ ಶೂನ್ಯ win_console_puts(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಸ್ಥಿರಾಂಕ uint8_t *q = str;
    uint16_t ಸಾಲು[ಸಾಲು_SZ];

    ಆಗ (*q) {
        uint16_t *buf = ಸಾಲು;
        DWORD nb_chars = 0;
        DWORD written;

        ಆಗ (*q && nb_chars < ಸಾಲು_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; ಹೋಗು continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ಸಾಲು, nb_chars, &written, ಖಾಲಿ);
    }
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ check_color_terminal(ಶೂನ್ಯ)
{
    ಅಕ್ಷರ *ಪದ = getenv("TERM");

#ಆದರೆ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_ಬಫರ್_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    ಆದರೆ (con != INVALID_HANDLE_ಮೌಲ್ಯ && !Get_Console_ಬಹುಲಕ(con, &dummy))
        con = INVALID_HANDLE_ಮೌಲ್ಯ;
    ಆದರೆ (con != INVALID_HANDLE_ಮೌಲ್ಯ) {
        Get_Console_Screen_ಬಫರ್_Info(con, &con_info);
        attr_orig  = con_info.w_ಗುಣಲಕ್ಷಣಗಳು;
        background = attr_orig & 0xF0;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
#ಆದರೆ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_ಮೌಲ್ಯ);
#ಅಥವಾಆದರೆ HAVE_ISATTY
        use_color = (ಪದ && isatty(2));
#ಇಲ್ಲದಿದ್ದರೆ
        use_color = 0;
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಆದರೆ (getenv("AV_LOG_FORCE_256COLOR") || ಪದ && ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(ಪದ, "256color"))
        use_color *= 256;
}

ಸ್ಥಿರ ಶೂನ್ಯ ansi_fputs(ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ tint, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ local_use_color)
{
    ಆದರೆ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#ಆದರೆ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        ಆದರೆ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#ಆದರೆ_ಅಂತ್ಯ
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } ಇಲ್ಲದಿದ್ದರೆ
        fputs(str, stderr);
}

ಸ್ಥಿರ ಶೂನ್ಯ colored_fputs(ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ tint, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ local_use_color;
    ಆದರೆ (!*str)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (use_color < 0)
        check_color_terminal();

    ಆದರೆ (level == AV_LOG_INFO/8) local_use_color = 0;
    ಇಲ್ಲದಿದ್ದರೆ                        local_use_color = use_color;

#ಆದರೆ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    ಆದರೆ (con != INVALID_HANDLE_ಮೌಲ್ಯ) {
        ಆದರೆ (local_use_color)
            ಗಣ_Console_ಪಠ್ಯ_Attribute(con, background | win_color[level]);
        win_console_puts(str);
        ಆದರೆ (local_use_color)
            ಗಣ_Console_ಪಠ್ಯ_Attribute(con, attr_orig);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ansi_fputs(level, tint, str, local_use_color);
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ansi_fputs(level, tint, str, local_use_color);
#ಆದರೆ_ಅಂತ್ಯ

}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_default_ಅಂಶ_name(ಶೂನ್ಯ *ptr)
{
    ಹಿಂತಿರುಗಿ (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(ಶೂನ್ಯ *ptr)
{
    ಹಿಂತಿರುಗಿ (*(AVClass **) ptr)->category;
}

ಸ್ಥಿರ ಶೂನ್ಯ sanitize(uint8_t *ಸಾಲು){
    ಆಗ(*ಸಾಲು){
        ಆದರೆ(*ಸಾಲು < 0x08 || (*ಸಾಲು > 0x0D && *ಸಾಲು < 0x20))
            *ಸಾಲು='?';
        ಸಾಲು++;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_category(ಶೂನ್ಯ *ptr){
    AVClass *avc = *(AVClass **) ptr;
    ಆದರೆ(    !avc
        || (avc->ಆವೃತ್ತಿ&0xFF)<100
        ||  avc->ಆವೃತ್ತಿ < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) ಹಿಂತಿರುಗಿ AV_CLASS_CATEGORY_NA + 16;

    ಆದರೆ(avc->get_category)
        ಹಿಂತಿರುಗಿ avc->get_category(ptr) + 16;

    ಹಿಂತಿರುಗಿ avc->category + 16;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *get_level_str(ಪೂರ್ಣಾಂಕ level)
{
    ಆಯ್ಕೆ (level) {
    ಸ್ಥಿತಿ AV_LOG_QUIET:
        ಹಿಂತಿರುಗಿ "quiet";
    ಸ್ಥಿತಿ AV_LOG_DEBUG:
        ಹಿಂತಿರುಗಿ "debug";
    ಸ್ಥಿತಿ AV_LOG_TRACE:
        ಹಿಂತಿರುಗಿ "trace";
    ಸ್ಥಿತಿ AV_LOG_VERBOSE:
        ಹಿಂತಿರುಗಿ "verbose";
    ಸ್ಥಿತಿ AV_LOG_INFO:
        ಹಿಂತಿರುಗಿ "info";
    ಸ್ಥಿತಿ AV_LOG_WARNING:
        ಹಿಂತಿರುಗಿ "warning";
    ಸ್ಥಿತಿ AV_LOG_ERROR:
        ಹಿಂತಿರುಗಿ "error";
    ಸ್ಥಿತಿ AV_LOG_FATAL:
        ಹಿಂತಿರುಗಿ "fatal";
    ಸ್ಥಿತಿ AV_LOG_PANIC:
        ಹಿಂತಿರುಗಿ "panic";
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ "";
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಅಂಶ_name(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVClass *cls)
{
    ಹಿಂತಿರುಗಿ (cls->ಅಂಶ_name ? cls->ಅಂಶ_name : av_default_ಅಂಶ_name)(obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ format_date_now(AVBPrint* bp_ಸಮಯ, ಪೂರ್ಣಾಂಕ include_date)
{
    ರಚನೆ tm *ptm, tmbuf;
    ಸ್ಥಿರಾಂಕ int64_t ಸಮಯ_us = av_gettime();
    ಸ್ಥಿರಾಂಕ int64_t ಸಮಯ_ms = ಸಮಯ_us / 1000;
    ಸ್ಥಿರಾಂಕ time_t ಸಮಯ_s   = ಸಮಯ_ms / 1000;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ millisec    = ಸಮಯ_ms - (ಸಮಯ_s * 1000);
    ptm                   = localtime_r(&ಸಮಯ_s, &tmbuf);
    ಆದರೆ (ptm) {
        ಆದರೆ (include_date)
            av_bprint_strftime(bp_ಸಮಯ, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_ಸಮಯ, "%H:%M:%S", ptm);
        av_bprintf(bp_ಸಮಯ, ".%03d ", millisec);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ format_ಸಾಲು(ಶೂನ್ಯ *avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl,
                        AVBPrint part[5], ಪೂರ್ಣಾಂಕ *print_ಪೂರ್ವಪ್ರತ್ಯಯ, ಪೂರ್ಣಾಂಕ type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ಖಾಲಿ;
    av_bprint_init(part+0, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    ಪೂರ್ಣಾಂಕ flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    ಆದರೆ(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    ಆದರೆ (*print_ಪೂರ್ವಪ್ರತ್ಯಯ && avc) {
        ಆದರೆ (avc->ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ) {
            AVClass** ಪೋಷಕ = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ);
            ಆದರೆ (ಪೋಷಕ && *ಪೋಷಕ) {
                av_bprintf(part+0, "[%s @ %p] ",
                           ಅಂಶ_name(ಪೋಷಕ, *ಪೋಷಕ), ಪೋಷಕ);
                ಆದರೆ(type) type[0] = get_category(ಪೋಷಕ);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   ಅಂಶ_name(avcl, avc), avcl);
        ಆದರೆ(type) type[1] = get_category(avcl);
    }

    ಆದರೆ (*print_ಪೂರ್ವಪ್ರತ್ಯಯ && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_ಸಮಯ | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    ಆದರೆ (*print_ಪೂರ್ವಪ್ರತ್ಯಯ && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    ಆದರೆ(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        ಅಕ್ಷರ lastc = part[3].len && part[3].len <= part[3].ಗಾತ್ರ_2 ? part[3].str[part[3].len - 1] : 0;
        *print_ಪೂರ್ವಪ್ರತ್ಯಯ = lastc == '\n' || lastc == '\r';
    }
}

ಶೂನ್ಯ av_log_format_ಸಾಲು(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl,
                        ಅಕ್ಷರ *ಸಾಲು, ಪೂರ್ಣಾಂಕ ಸಾಲು_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ *print_ಪೂರ್ವಪ್ರತ್ಯಯ)
{
    av_log_format_line2(ptr, level, fmt, vl, ಸಾಲು, ಸಾಲು_ಗಾತ್ರ, print_ಪೂರ್ವಪ್ರತ್ಯಯ);
}

ಪೂರ್ಣಾಂಕ av_log_format_line2(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl,
                        ಅಕ್ಷರ *ಸಾಲು, ಪೂರ್ಣಾಂಕ ಸಾಲು_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ *print_ಪೂರ್ವಪ್ರತ್ಯಯ)
{
    AVBPrint part[5];
    ಪೂರ್ಣಾಂಕ ret;

    format_ಸಾಲು(ptr, level, fmt, vl, part, print_ಪೂರ್ವಪ್ರತ್ಯಯ, ಖಾಲಿ);
    ret = snprintf(ಸಾಲು, ಸಾಲು_ಗಾತ್ರ, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ av_log_default_callback(ಶೂನ್ಯ* ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* fmt, va_list vl)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ print_ಪೂರ್ವಪ್ರತ್ಯಯ = 1;
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2;
    ಸ್ಥಿರ ಅಕ್ಷರ prev[ಸಾಲು_SZ];
    AVBPrint part[5];
    ಅಕ್ಷರ ಸಾಲು[ಸಾಲು_SZ];
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ is_atty;
    ಪೂರ್ಣಾಂಕ type[2];
    ಚಿಹ್ನೆರಹಿತ tint = 0;

    ಆದರೆ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    ಆದರೆ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        ಹಿಂತಿರುಗಿ;
    ff_mutex_ಬೀಗ(&mutex);

    format_ಸಾಲು(ptr, level, fmt, vl, part, &print_ಪೂರ್ವಪ್ರತ್ಯಯ, type);
    snprintf(ಸಾಲು, ಗಾತ್ರ(ಸಾಲು), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#ಆದರೆ HAVE_ISATTY
    ಆದರೆ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (print_ಪೂರ್ವಪ್ರತ್ಯಯ && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(ಸಾಲು, prev) &&
        *ಸಾಲು && ಸಾಲು[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಸಾಲು) - 1] != '\r'){
        ಎಣಿಕೆ_2++;
        ಆದರೆ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", ಎಣಿಕೆ_2);
        ಹೋಗು ಕೊನೆ;
    }
    ಆದರೆ (ಎಣಿಕೆ_2 > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", ಎಣಿಕೆ_2);
        ಎಣಿಕೆ_2 = 0;
    }
    strcpy(prev, ಸಾಲು);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_ಮಟ್ಟಗಳು - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_ಮಟ್ಟಗಳು - 1), tint >> 8, part[3].str);

#ಆದರೆ CONFIG_VALGRIND_BACKTRACE
    ಆದರೆ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#ಆದರೆ_ಅಂತ್ಯ
ಕೊನೆ:
    av_bprint_finalize(part+3, ಖಾಲಿ);
    ff_mutex_unlock(&mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ (*_Atomic av_log_callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*, va_list) = av_log_default_callback;

ಶೂನ್ಯ av_log(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

ಶೂನ್ಯ av_log_once(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಂಕ initial_level, ಪೂರ್ಣಾಂಕ subsequent_level, ಪೂರ್ಣಾಂಕ *state, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

ಶೂನ್ಯ av_vlog(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ಖಾಲಿ;
    ಶೂನ್ಯ (*log_callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    ಆದರೆ (avc && avc->ಆವೃತ್ತಿ >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ && level >= AV_LOG_FATAL)
        level += *(ಪೂರ್ಣಾಂಕ *) (((uint8_t *) avcl) + avc->log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ);
    ಆದರೆ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

ಪೂರ್ಣಾಂಕ av_log_get_level(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_ಗಣ_level(ಪೂರ್ಣಾಂಕ level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_ಗಣ_flags(ಪೂರ್ಣಾಂಕ arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

ಪೂರ್ಣಾಂಕ av_log_get_flags(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_ಗಣ_callback(ಶೂನ್ಯ (*callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ಸ್ಥಿರ ಶೂನ್ಯ missing_feature_sample(ಪೂರ್ಣಾಂಕ sample, ಶೂನ್ಯ *avc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ,
                                   va_list ವಾದ_list)
{
    av_vlog(avc, AV_LOG_WARNING, ಸಂದೇಶ, ವಾದ_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    ಆದರೆ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

ಶೂನ್ಯ avpriv_request_sample(ಶೂನ್ಯ *avc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...)
{
    va_list ವಾದ_list;

    va_start(ವಾದ_list, ಸಂದೇಶ);
    missing_feature_sample(1, avc, ಸಂದೇಶ, ವಾದ_list);
    va_end(ವಾದ_list);
}

ಶೂನ್ಯ avpriv_report_missing_feature(ಶೂನ್ಯ *avc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...)
{
    va_list ವಾದ_list;

    va_start(ವಾದ_list, ಸಂದೇಶ);
    missing_feature_sample(0, avc, ಸಂದೇಶ, ವಾದ_list);
    va_end(ವಾದ_list);
}
