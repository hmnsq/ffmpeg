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

#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif
#ಯದಿ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#endif
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

#define ಸಾಲು_SZ 1024

#ಯದಿ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#ಅನ್ತರ್ಭಾವ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

ಸ್ಥಿರ atomic_int av_log_level = AV_LOG_INFO;
ಸ್ಥಿರ atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#ಯದಿ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#ಅನ್ತರ್ಭಾವ <windows.h>
ಸ್ಥಿರ ಧ್ರುವ uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
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
#endif

ಸ್ಥಿರ ಧ್ರುವ uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ use_color = -1;

#ಯದಿ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ಸ್ಥಿರ ಶೂನ್ಯ win_console_puts(ಧ್ರುವ ವರ್ಣ *str)
{
    ಧ್ರುವ uint8_t *q = str;
    uint16_t ಸಾಲು[ಸಾಲು_SZ];

    ಯಾವತ್ (*q) {
        uint16_t *buf = ಸಾಲು;
        DWORD nb_chars = 0;
        DWORD written;

        ಯಾವತ್ (*q && nb_chars < ಸಾಲು_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; ಗಚ್ಛ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ಸಾಲು, nb_chars, &written, ರಿಕ್ತ);
    }
}
#endif

ಸ್ಥಿರ ಶೂನ್ಯ check_color_terminal(ಶೂನ್ಯ)
{
    ವರ್ಣ *term = getenv("TERM");

#ಯದಿ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    ಯದಿ (con != INVALID_HANDLE_ಮೌಲ್ಯ && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_ಮೌಲ್ಯ;
    ಯದಿ (con != INVALID_HANDLE_ಮೌಲ್ಯ) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    ಯದಿ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } ಅನ್ಯಥಾ ಯದಿ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } ಅನ್ಯಥಾ {
#ಯದಿ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_ಮೌಲ್ಯ);
#ನೋಚೇದ್ಯದಿ HAVE_ISATTY
        use_color = (term && isatty(2));
#ಅನ್ಯಥಾ
        use_color = 0;
#endif
    }

    ಯದಿ (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

ಸ್ಥಿರ ಶೂನ್ಯ ansi_fputs(ಪೂರ್ಣಾಙ್ಕ level, ಪೂರ್ಣಾಙ್ಕ tint, ಧ್ರುವ ವರ್ಣ *str, ಪೂರ್ಣಾಙ್ಕ local_use_color)
{
    ಯದಿ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#ಯದಿ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        ಯದಿ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } ಅನ್ಯಥಾ ಯದಿ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } ಅನ್ಯಥಾ ಯದಿ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } ಅನ್ಯಥಾ
        fputs(str, stderr);
}

ಸ್ಥಿರ ಶೂನ್ಯ colored_fputs(ಪೂರ್ಣಾಙ್ಕ level, ಪೂರ್ಣಾಙ್ಕ tint, ಧ್ರುವ ವರ್ಣ *str)
{
    ಪೂರ್ಣಾಙ್ಕ local_use_color;
    ಯದಿ (!*str)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (use_color < 0)
        check_color_terminal();

    ಯದಿ (level == AV_LOG_INFO/8) local_use_color = 0;
    ಅನ್ಯಥಾ                        local_use_color = use_color;

#ಯದಿ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    ಯದಿ (con != INVALID_HANDLE_ಮೌಲ್ಯ) {
        ಯದಿ (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        ಯದಿ (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } ಅನ್ಯಥಾ {
        ansi_fputs(level, tint, str, local_use_color);
    }
#ಅನ್ಯಥಾ
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ಧ್ರುವ ವರ್ಣ *av_default_item_name(ಶೂನ್ಯ *ptr)
{
    ಪ್ರತ್ಯಾಗಮ (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(ಶೂನ್ಯ *ptr)
{
    ಪ್ರತ್ಯಾಗಮ (*(AVClass **) ptr)->category;
}

ಸ್ಥಿರ ಶೂನ್ಯ sanitize(uint8_t *ಸಾಲು){
    ಯಾವತ್(*ಸಾಲು){
        ಯದಿ(*ಸಾಲು < 0x08 || (*ಸಾಲು > 0x0D && *ಸಾಲು < 0x20))
            *ಸಾಲು='?';
        ಸಾಲು++;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_category(ಶೂನ್ಯ *ptr){
    AVClass *avc = *(AVClass **) ptr;
    ಯದಿ(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) ಪ್ರತ್ಯಾಗಮ AV_CLASS_CATEGORY_NA + 16;

    ಯದಿ(avc->get_category)
        ಪ್ರತ್ಯಾಗಮ avc->get_category(ptr) + 16;

    ಪ್ರತ್ಯಾಗಮ avc->category + 16;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *get_level_str(ಪೂರ್ಣಾಙ್ಕ level)
{
    ವಿಕಲ್ಪ (level) {
    ಪಕ್ಷ AV_LOG_QUIET:
        ಪ್ರತ್ಯಾಗಮ "quiet";
    ಪಕ್ಷ AV_LOG_DEBUG:
        ಪ್ರತ್ಯಾಗಮ "debug";
    ಪಕ್ಷ AV_LOG_TRACE:
        ಪ್ರತ್ಯಾಗಮ "trace";
    ಪಕ್ಷ AV_LOG_VERBOSE:
        ಪ್ರತ್ಯಾಗಮ "verbose";
    ಪಕ್ಷ AV_LOG_INFO:
        ಪ್ರತ್ಯಾಗಮ "info";
    ಪಕ್ಷ AV_LOG_WARNING:
        ಪ್ರತ್ಯಾಗಮ "warning";
    ಪಕ್ಷ AV_LOG_ERROR:
        ಪ್ರತ್ಯಾಗಮ "error";
    ಪಕ್ಷ AV_LOG_FATAL:
        ಪ್ರತ್ಯಾಗಮ "fatal";
    ಪಕ್ಷ AV_LOG_PANIC:
        ಪ್ರತ್ಯಾಗಮ "panic";
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ "";
    }
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *item_name(ಶೂನ್ಯ *obj, ಧ್ರುವ AVClass *cls)
{
    ಪ್ರತ್ಯಾಗಮ (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

ಸ್ಥಿರ ಶೂನ್ಯ format_date_now(AVBPrint* bp_time, ಪೂರ್ಣಾಙ್ಕ include_date)
{
    ಸಂರಚನಾ tm *ptm, tmbuf;
    ಧ್ರುವ int64_t time_us = av_gettime();
    ಧ್ರುವ int64_t time_ms = time_us / 1000;
    ಧ್ರುವ time_t time_s   = time_ms / 1000;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    ಯದಿ (ptm) {
        ಯದಿ (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ format_ಸಾಲು(ಶೂನ್ಯ *avcl, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, va_list vl,
                        AVBPrint part[5], ಪೂರ್ಣಾಙ್ಕ *print_prefix, ಪೂರ್ಣಾಙ್ಕ type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ರಿಕ್ತ;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    ಪೂರ್ಣಾಙ್ಕ flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    ಯದಿ(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    ಯದಿ (*print_prefix && avc) {
        ಯದಿ (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            ಯದಿ (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                ಯದಿ(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        ಯದಿ(type) type[1] = get_category(avcl);
    }

    ಯದಿ (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    ಯದಿ (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    ಯದಿ(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        ವರ್ಣ lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

ಶೂನ್ಯ av_log_format_ಸಾಲು(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, va_list vl,
                        ವರ್ಣ *ಸಾಲು, ಪೂರ್ಣಾಙ್ಕ ಸಾಲು_size, ಪೂರ್ಣಾಙ್ಕ *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, ಸಾಲು, ಸಾಲು_size, print_prefix);
}

ಪೂರ್ಣಾಙ್ಕ av_log_format_line2(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, va_list vl,
                        ವರ್ಣ *ಸಾಲು, ಪೂರ್ಣಾಙ್ಕ ಸಾಲು_size, ಪೂರ್ಣಾಙ್ಕ *print_prefix)
{
    AVBPrint part[5];
    ಪೂರ್ಣಾಙ್ಕ ret;

    format_ಸಾಲು(ptr, level, fmt, vl, part, print_prefix, ರಿಕ್ತ);
    ret = snprintf(ಸಾಲು, ಸಾಲು_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ರಿಕ್ತ);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ av_log_default_callback(ಶೂನ್ಯ* ptr, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ* fmt, va_list vl)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ print_prefix = 1;
    ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;
    ಸ್ಥಿರ ವರ್ಣ prev[ಸಾಲು_SZ];
    AVBPrint part[5];
    ವರ್ಣ ಸಾಲು[ಸಾಲು_SZ];
    ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ is_atty;
    ಪೂರ್ಣಾಙ್ಕ type[2];
    unsigned tint = 0;

    ಯದಿ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    ಯದಿ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        ಪ್ರತ್ಯಾಗಮ;
    ff_mutex_lock(&mutex);

    format_ಸಾಲು(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(ಸಾಲು, ಪರಿಮಾಣ(ಸಾಲು), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#ಯದಿ HAVE_ISATTY
    ಯದಿ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    ಯದಿ (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(ಸಾಲು, prev) &&
        *ಸಾಲು && ಸಾಲು[strlen(ಸಾಲು) - 1] != '\r'){
        ಎಣಿಕೆ++;
        ಯದಿ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", ಎಣಿಕೆ);
        ಗಚ್ಛ end;
    }
    ಯದಿ (ಎಣಿಕೆ > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", ಎಣಿಕೆ);
        ಎಣಿಕೆ = 0;
    }
    strcpy(prev, ಸಾಲು);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_LEVELS - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_LEVELS - 1), tint >> 8, part[3].str);

#ಯದಿ CONFIG_VALGRIND_BACKTRACE
    ಯದಿ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, ರಿಕ್ತ);
    ff_mutex_unlock(&mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ (*_Atomic av_log_callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಙ್ಕ, ಧ್ರುವ ವರ್ಣ*, va_list) = av_log_default_callback;

ಶೂನ್ಯ av_log(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

ಶೂನ್ಯ av_log_once(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಙ್ಕ initial_level, ಪೂರ್ಣಾಙ್ಕ subsequent_level, ಪೂರ್ಣಾಙ್ಕ *state, ಧ್ರುವ ವರ್ಣ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

ಶೂನ್ಯ av_vlog(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ರಿಕ್ತ;
    ಶೂನ್ಯ (*log_callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಙ್ಕ, ಧ್ರುವ ವರ್ಣ*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    ಯದಿ (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(ಪೂರ್ಣಾಙ್ಕ *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    ಯದಿ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

ಪೂರ್ಣಾಙ್ಕ av_log_get_level(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_set_level(ಪೂರ್ಣಾಙ್ಕ level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_set_flags(ಪೂರ್ಣಾಙ್ಕ arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

ಪೂರ್ಣಾಙ್ಕ av_log_get_flags(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

ಶೂನ್ಯ av_log_set_callback(ಶೂನ್ಯ (*callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಙ್ಕ, ಧ್ರುವ ವರ್ಣ*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ಸ್ಥಿರ ಶೂನ್ಯ missing_feature_sample(ಪೂರ್ಣಾಙ್ಕ sample, ಶೂನ್ಯ *avc, ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, ಸಂದೇಶ, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    ಯದಿ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

ಶೂನ್ಯ avpriv_request_sample(ಶೂನ್ಯ *avc, ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ, ...)
{
    va_list argument_list;

    va_start(argument_list, ಸಂದೇಶ);
    missing_feature_sample(1, avc, ಸಂದೇಶ, argument_list);
    va_end(argument_list);
}

ಶೂನ್ಯ avpriv_report_missing_feature(ಶೂನ್ಯ *avc, ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ, ...)
{
    va_list argument_list;

    va_start(argument_list, ಸಂದೇಶ);
    missing_feature_sample(0, avc, ಸಂದೇಶ, argument_list);
    va_end(argument_list);
}
