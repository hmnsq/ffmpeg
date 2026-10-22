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

#അന്തര്ഭാവ "config.h"

#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif
#എങ്കിൽ HAVE_IO_H
#അന്തര്ഭാവ <io.h>
#endif
#അന്തര്ഭാവ <inttypes.h>
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ "bprint.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "internal.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "thread.h"
#അന്തര്ഭാവ "time.h"
#അന്തര്ഭാവ "time_internal.h"

സ്ഥിതം AVMutex mutex = AV_MUTEX_INITIALIZER;

#define വരി_SZ 1024

#എങ്കിൽ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#അന്തര്ഭാവ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

സ്ഥിതം atomic_int av_log_level = AV_LOG_INFO;
സ്ഥിതം atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#എങ്കിൽ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#അന്തര്ഭാവ <windows.h>
സ്ഥിതം സ്ഥിരം uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_നിവേശം           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_നിവേശം  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_നിവേശം  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_നിവേശം        ] = 5,
};

സ്ഥിതം int16_t background, attr_orig;
സ്ഥിതം HANDLE con;
#endif

സ്ഥിതം സ്ഥിരം uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_നിവേശം           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_നിവേശം  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_നിവേശം  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_നിവേശം        ] = 207 << 8 | 0x05,
};

സ്ഥിതം പൂർണ്ണസംഖ്യ use_color = -1;

#എങ്കിൽ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
സ്ഥിതം ശൂന്യം win_console_puts(സ്ഥിരം അക്ഷരം *str)
{
    സ്ഥിരം uint8_t *q = str;
    uint16_t വരി[വരി_SZ];

    ആകുമ്പോൾ (*q) {
        uint16_t *buf = വരി;
        DWORD nb_chars = 0;
        DWORD written;

        ആകുമ്പോൾ (*q && nb_chars < വരി_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; പോകുക continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, വരി, nb_chars, &written, ശൂന്യ);
    }
}
#endif

സ്ഥിതം ശൂന്യം check_color_terminal(ശൂന്യം)
{
    അക്ഷരം *term = getenv("TERM");

#എങ്കിൽ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    എങ്കിൽ (con != INVALID_HANDLE_മൂല്യം && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_മൂല്യം;
    എങ്കിൽ (con != INVALID_HANDLE_മൂല്യം) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    എങ്കിൽ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } അല്ലെങ്കിൽ {
#എങ്കിൽ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_മൂല്യം);
#അല്ലെങ്കിലെങ്കിൽ HAVE_ISATTY
        use_color = (term && isatty(2));
#അല്ലെങ്കിൽ
        use_color = 0;
#endif
    }

    എങ്കിൽ (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

സ്ഥിതം ശൂന്യം ansi_fputs(പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ tint, സ്ഥിരം അക്ഷരം *str, പൂർണ്ണസംഖ്യ local_use_color)
{
    എങ്കിൽ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#എങ്കിൽ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        എങ്കിൽ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } അല്ലെങ്കിൽ എങ്കിൽ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } അല്ലെങ്കിൽ എങ്കിൽ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } അല്ലെങ്കിൽ
        fputs(str, stderr);
}

സ്ഥിതം ശൂന്യം colored_fputs(പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ tint, സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ local_use_color;
    എങ്കിൽ (!*str)
        തിരികെ;

    എങ്കിൽ (use_color < 0)
        check_color_terminal();

    എങ്കിൽ (level == AV_LOG_INFO/8) local_use_color = 0;
    അല്ലെങ്കിൽ                        local_use_color = use_color;

#എങ്കിൽ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    എങ്കിൽ (con != INVALID_HANDLE_മൂല്യം) {
        എങ്കിൽ (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        എങ്കിൽ (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } അല്ലെങ്കിൽ {
        ansi_fputs(level, tint, str, local_use_color);
    }
#അല്ലെങ്കിൽ
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

സ്ഥിരം അക്ഷരം *av_default_item_name(ശൂന്യം *ptr)
{
    തിരികെ (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(ശൂന്യം *ptr)
{
    തിരികെ (*(AVClass **) ptr)->category;
}

സ്ഥിതം ശൂന്യം sanitize(uint8_t *വരി){
    ആകുമ്പോൾ(*വരി){
        എങ്കിൽ(*വരി < 0x08 || (*വരി > 0x0D && *വരി < 0x20))
            *വരി='?';
        വരി++;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_category(ശൂന്യം *ptr){
    AVClass *avc = *(AVClass **) ptr;
    എങ്കിൽ(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) തിരികെ AV_CLASS_CATEGORY_NA + 16;

    എങ്കിൽ(avc->get_category)
        തിരികെ avc->get_category(ptr) + 16;

    തിരികെ avc->category + 16;
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *get_level_str(പൂർണ്ണസംഖ്യ level)
{
    തിരഞ്ഞെടുപ്പ് (level) {
    അവസ്ഥ AV_LOG_QUIET:
        തിരികെ "quiet";
    അവസ്ഥ AV_LOG_DEBUG:
        തിരികെ "debug";
    അവസ്ഥ AV_LOG_TRACE:
        തിരികെ "trace";
    അവസ്ഥ AV_LOG_VERBOSE:
        തിരികെ "verbose";
    അവസ്ഥ AV_LOG_INFO:
        തിരികെ "info";
    അവസ്ഥ AV_LOG_WARNING:
        തിരികെ "warning";
    അവസ്ഥ AV_LOG_ERROR:
        തിരികെ "error";
    അവസ്ഥ AV_LOG_FATAL:
        തിരികെ "fatal";
    അവസ്ഥ AV_LOG_PANIC:
        തിരികെ "panic";
    സ്ഥിരസ്ഥിതി:
        തിരികെ "";
    }
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *item_name(ശൂന്യം *obj, സ്ഥിരം AVClass *cls)
{
    തിരികെ (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

സ്ഥിതം ശൂന്യം format_date_now(AVBPrint* bp_time, പൂർണ്ണസംഖ്യ include_date)
{
    ഘടന tm *ptm, tmbuf;
    സ്ഥിരം int64_t time_us = av_gettime();
    സ്ഥിരം int64_t time_ms = time_us / 1000;
    സ്ഥിരം time_t time_s   = time_ms / 1000;
    സ്ഥിരം പൂർണ്ണസംഖ്യ millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    എങ്കിൽ (ptm) {
        എങ്കിൽ (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

സ്ഥിതം ശൂന്യം format_വരി(ശൂന്യം *avcl, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, va_list vl,
                        AVBPrint part[5], പൂർണ്ണസംഖ്യ *print_prefix, പൂർണ്ണസംഖ്യ type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ശൂന്യ;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    പൂർണ്ണസംഖ്യ flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    എങ്കിൽ(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    എങ്കിൽ (*print_prefix && avc) {
        എങ്കിൽ (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            എങ്കിൽ (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                എങ്കിൽ(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        എങ്കിൽ(type) type[1] = get_category(avcl);
    }

    എങ്കിൽ (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    എങ്കിൽ (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    എങ്കിൽ(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        അക്ഷരം lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

ശൂന്യം av_log_format_വരി(ശൂന്യം *ptr, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, va_list vl,
                        അക്ഷരം *വരി, പൂർണ്ണസംഖ്യ വരി_size, പൂർണ്ണസംഖ്യ *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, വരി, വരി_size, print_prefix);
}

പൂർണ്ണസംഖ്യ av_log_format_line2(ശൂന്യം *ptr, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, va_list vl,
                        അക്ഷരം *വരി, പൂർണ്ണസംഖ്യ വരി_size, പൂർണ്ണസംഖ്യ *print_prefix)
{
    AVBPrint part[5];
    പൂർണ്ണസംഖ്യ ret;

    format_വരി(ptr, level, fmt, vl, part, print_prefix, ശൂന്യ);
    ret = snprintf(വരി, വരി_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ശൂന്യ);
    തിരികെ ret;
}

ശൂന്യം av_log_default_callback(ശൂന്യം* ptr, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം* fmt, va_list vl)
{
    സ്ഥിതം പൂർണ്ണസംഖ്യ print_prefix = 1;
    സ്ഥിതം പൂർണ്ണസംഖ്യ എണ്ണം;
    സ്ഥിതം അക്ഷരം prev[വരി_SZ];
    AVBPrint part[5];
    അക്ഷരം വരി[വരി_SZ];
    സ്ഥിതം പൂർണ്ണസംഖ്യ is_atty;
    പൂർണ്ണസംഖ്യ type[2];
    unsigned tint = 0;

    എങ്കിൽ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    എങ്കിൽ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        തിരികെ;
    ff_mutex_lock(&mutex);

    format_വരി(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(വരി, വലുപ്പം(വരി), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#എങ്കിൽ HAVE_ISATTY
    എങ്കിൽ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    എങ്കിൽ (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(വരി, prev) &&
        *വരി && വരി[strlen(വരി) - 1] != '\r'){
        എണ്ണം++;
        എങ്കിൽ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", എണ്ണം);
        പോകുക end;
    }
    എങ്കിൽ (എണ്ണം > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", എണ്ണം);
        എണ്ണം = 0;
    }
    strcpy(prev, വരി);

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

#എങ്കിൽ CONFIG_VALGRIND_BACKTRACE
    എങ്കിൽ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, ശൂന്യ);
    ff_mutex_unlock(&mutex);
}

സ്ഥിതം ശൂന്യം (*_Atomic av_log_callback)(ശൂന്യം*, പൂർണ്ണസംഖ്യ, സ്ഥിരം അക്ഷരം*, va_list) = av_log_default_callback;

ശൂന്യം av_log(ശൂന്യം* avcl, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

ശൂന്യം av_log_once(ശൂന്യം* avcl, പൂർണ്ണസംഖ്യ initial_level, പൂർണ്ണസംഖ്യ subsequent_level, പൂർണ്ണസംഖ്യ *state, സ്ഥിരം അക്ഷരം *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

ശൂന്യം av_vlog(ശൂന്യം* avcl, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ശൂന്യ;
    ശൂന്യം (*log_callback)(ശൂന്യം*, പൂർണ്ണസംഖ്യ, സ്ഥിരം അക്ഷരം*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    എങ്കിൽ (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(പൂർണ്ണസംഖ്യ *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    എങ്കിൽ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

പൂർണ്ണസംഖ്യ av_log_get_level(ശൂന്യം)
{
    തിരികെ atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

ശൂന്യം av_log_set_level(പൂർണ്ണസംഖ്യ level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

ശൂന്യം av_log_set_flags(പൂർണ്ണസംഖ്യ arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

പൂർണ്ണസംഖ്യ av_log_get_flags(ശൂന്യം)
{
    തിരികെ atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

ശൂന്യം av_log_set_callback(ശൂന്യം (*callback)(ശൂന്യം*, പൂർണ്ണസംഖ്യ, സ്ഥിരം അക്ഷരം*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

സ്ഥിതം ശൂന്യം missing_feature_sample(പൂർണ്ണസംഖ്യ sample, ശൂന്യം *avc, സ്ഥിരം അക്ഷരം *സന്ദേശം,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, സന്ദേശം, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    എങ്കിൽ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

ശൂന്യം avpriv_request_sample(ശൂന്യം *avc, സ്ഥിരം അക്ഷരം *സന്ദേശം, ...)
{
    va_list argument_list;

    va_start(argument_list, സന്ദേശം);
    missing_feature_sample(1, avc, സന്ദേശം, argument_list);
    va_end(argument_list);
}

ശൂന്യം avpriv_report_missing_feature(ശൂന്യം *avc, സ്ഥിരം അക്ഷരം *സന്ദേശം, ...)
{
    va_list argument_list;

    va_start(argument_list, സന്ദേശം);
    missing_feature_sample(0, avc, സന്ദേശം, argument_list);
    va_end(argument_list);
}
