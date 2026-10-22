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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_IO_H
#ਅਨ੍ਤਰ੍ਭਾਵ <io.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time_internal.h"

ਸਥਿਰ AVMutex mutex = AV_MUTEX_INITIALIZER;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਤਰ_SZ 1024

#ਜੇ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#ਅਨ੍ਤਰ੍ਭਾਵ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BACKTRACE_LOGLEVEL AV_LOG_ERROR
#ਜੇ_ਅੰਤ

ਸਥਿਰ atomic_int av_log_level = AV_LOG_INFO;
ਸਥਿਰ atomic_int av_log_flags = 0;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NB_ਪੱਧਰ 8
#ਜੇ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
ਸਥਿਰ ਅਚਲ uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_ਨਿਵੇਸ਼           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ਨਿਵੇਸ਼  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ਨਿਵੇਸ਼  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_ਨਿਵੇਸ਼        ] = 5,
};

ਸਥਿਰ int16_t background, attr_orig;
ਸਥਿਰ HANDLE con;
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਅਚਲ uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_ਨਿਵੇਸ਼           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ਨਿਵੇਸ਼  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ਨਿਵੇਸ਼  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_ਨਿਵੇਸ਼        ] = 207 << 8 | 0x05,
};

ਸਥਿਰ ਪੂਰਨ use_color = -1;

#ਜੇ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ਸਥਿਰ ਖਾਲੀ win_console_puts(ਅਚਲ ਅੱਖਰ *str)
{
    ਅਚਲ uint8_t *q = str;
    uint16_t ਸਤਰ[ਸਤਰ_SZ];

    ਜਦੋਂ (*q) {
        uint16_t *buf = ਸਤਰ;
        DWORD nb_chars = 0;
        DWORD written;

        ਜਦੋਂ (*q && nb_chars < ਸਤਰ_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; ਜਾਓ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ਸਤਰ, nb_chars, &written, ਨਿਰਾ);
    }
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ check_color_terminal(ਖਾਲੀ)
{
    ਅੱਖਰ *ਪਦ = getenv("TERM");

#ਜੇ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_ਬਫਰ_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    ਜੇ (con != INVALID_HANDLE_ਮੁੱਲ && !Get_Console_ਬਹੁਲਕ(con, &dummy))
        con = INVALID_HANDLE_ਮੁੱਲ;
    ਜੇ (con != INVALID_HANDLE_ਮੁੱਲ) {
        Get_Console_Screen_ਬਫਰ_Info(con, &con_info);
        attr_orig  = con_info.w_ਗੁਣ;
        background = attr_orig & 0xF0;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } ਨਹੀਂਤਾਂ ਜੇ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } ਨਹੀਂਤਾਂ {
#ਜੇ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_ਮੁੱਲ);
#ਜਾਂਜੇ HAVE_ISATTY
        use_color = (ਪਦ && isatty(2));
#ਨਹੀਂਤਾਂ
        use_color = 0;
#ਜੇ_ਅੰਤ
    }

    ਜੇ (getenv("AV_LOG_FORCE_256COLOR") || ਪਦ && ਲੜੀ_ਖੋਜ(ਪਦ, "256color"))
        use_color *= 256;
}

ਸਥਿਰ ਖਾਲੀ ansi_fputs(ਪੂਰਨ level, ਪੂਰਨ tint, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ local_use_color)
{
    ਜੇ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#ਜੇ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        ਜੇ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#ਜੇ_ਅੰਤ
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } ਨਹੀਂਤਾਂ ਜੇ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } ਨਹੀਂਤਾਂ ਜੇ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } ਨਹੀਂਤਾਂ
        fputs(str, stderr);
}

ਸਥਿਰ ਖਾਲੀ colored_fputs(ਪੂਰਨ level, ਪੂਰਨ tint, ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ local_use_color;
    ਜੇ (!*str)
        ਵਾਪਸ;

    ਜੇ (use_color < 0)
        check_color_terminal();

    ਜੇ (level == AV_LOG_INFO/8) local_use_color = 0;
    ਨਹੀਂਤਾਂ                        local_use_color = use_color;

#ਜੇ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    ਜੇ (con != INVALID_HANDLE_ਮੁੱਲ) {
        ਜੇ (local_use_color)
            ਸੈੱਟ_Console_ਪਾਠ_Attribute(con, background | win_color[level]);
        win_console_puts(str);
        ਜੇ (local_use_color)
            ਸੈੱਟ_Console_ਪਾਠ_Attribute(con, attr_orig);
    } ਨਹੀਂਤਾਂ {
        ansi_fputs(level, tint, str, local_use_color);
    }
#ਨਹੀਂਤਾਂ
    ansi_fputs(level, tint, str, local_use_color);
#ਜੇ_ਅੰਤ

}

ਅਚਲ ਅੱਖਰ *av_default_ਵਸਤੂ_name(ਖਾਲੀ *ptr)
{
    ਵਾਪਸ (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(ਖਾਲੀ *ptr)
{
    ਵਾਪਸ (*(AVClass **) ptr)->category;
}

ਸਥਿਰ ਖਾਲੀ sanitize(uint8_t *ਸਤਰ){
    ਜਦੋਂ(*ਸਤਰ){
        ਜੇ(*ਸਤਰ < 0x08 || (*ਸਤਰ > 0x0D && *ਸਤਰ < 0x20))
            *ਸਤਰ='?';
        ਸਤਰ++;
    }
}

ਸਥਿਰ ਪੂਰਨ get_category(ਖਾਲੀ *ptr){
    AVClass *avc = *(AVClass **) ptr;
    ਜੇ(    !avc
        || (avc->ਸੰਸਕਰਣ&0xFF)<100
        ||  avc->ਸੰਸਕਰਣ < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) ਵਾਪਸ AV_CLASS_CATEGORY_NA + 16;

    ਜੇ(avc->get_category)
        ਵਾਪਸ avc->get_category(ptr) + 16;

    ਵਾਪਸ avc->category + 16;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *get_level_str(ਪੂਰਨ level)
{
    ਚੋਣ (level) {
    ਹਾਲਤ AV_LOG_QUIET:
        ਵਾਪਸ "quiet";
    ਹਾਲਤ AV_LOG_DEBUG:
        ਵਾਪਸ "debug";
    ਹਾਲਤ AV_LOG_TRACE:
        ਵਾਪਸ "trace";
    ਹਾਲਤ AV_LOG_VERBOSE:
        ਵਾਪਸ "verbose";
    ਹਾਲਤ AV_LOG_INFO:
        ਵਾਪਸ "info";
    ਹਾਲਤ AV_LOG_WARNING:
        ਵਾਪਸ "warning";
    ਹਾਲਤ AV_LOG_ERROR:
        ਵਾਪਸ "error";
    ਹਾਲਤ AV_LOG_FATAL:
        ਵਾਪਸ "fatal";
    ਹਾਲਤ AV_LOG_PANIC:
        ਵਾਪਸ "panic";
    ਮੂਲ:
        ਵਾਪਸ "";
    }
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਵਸਤੂ_name(ਖਾਲੀ *obj, ਅਚਲ AVClass *cls)
{
    ਵਾਪਸ (cls->ਵਸਤੂ_name ? cls->ਵਸਤੂ_name : av_default_ਵਸਤੂ_name)(obj);
}

ਸਥਿਰ ਖਾਲੀ format_date_now(AVBPrint* bp_ਸਮਾਂ, ਪੂਰਨ include_date)
{
    ਬਣਤਰ tm *ptm, tmbuf;
    ਅਚਲ int64_t ਸਮਾਂ_us = av_gettime();
    ਅਚਲ int64_t ਸਮਾਂ_ms = ਸਮਾਂ_us / 1000;
    ਅਚਲ time_t ਸਮਾਂ_s   = ਸਮਾਂ_ms / 1000;
    ਅਚਲ ਪੂਰਨ millisec    = ਸਮਾਂ_ms - (ਸਮਾਂ_s * 1000);
    ptm                   = localtime_r(&ਸਮਾਂ_s, &tmbuf);
    ਜੇ (ptm) {
        ਜੇ (include_date)
            av_bprint_strftime(bp_ਸਮਾਂ, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_ਸਮਾਂ, "%H:%M:%S", ptm);
        av_bprintf(bp_ਸਮਾਂ, ".%03d ", millisec);
    }
}

ਸਥਿਰ ਖਾਲੀ format_ਸਤਰ(ਖਾਲੀ *avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl,
                        AVBPrint part[5], ਪੂਰਨ *print_ਅਗੇਤਰ, ਪੂਰਨ type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ਨਿਰਾ;
    av_bprint_init(part+0, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_ਮਾਪ_AUTOMATIC);
    ਪੂਰਨ flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    ਜੇ(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    ਜੇ (*print_ਅਗੇਤਰ && avc) {
        ਜੇ (avc->ਮਾਪਾ_log_context_ਵਿੱਥ) {
            AVClass** ਮਾਪਾ = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->ਮਾਪਾ_log_context_ਵਿੱਥ);
            ਜੇ (ਮਾਪਾ && *ਮਾਪਾ) {
                av_bprintf(part+0, "[%s @ %p] ",
                           ਵਸਤੂ_name(ਮਾਪਾ, *ਮਾਪਾ), ਮਾਪਾ);
                ਜੇ(type) type[0] = get_category(ਮਾਪਾ);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   ਵਸਤੂ_name(avcl, avc), avcl);
        ਜੇ(type) type[1] = get_category(avcl);
    }

    ਜੇ (*print_ਅਗੇਤਰ && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_ਸਮਾਂ | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    ਜੇ (*print_ਅਗੇਤਰ && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    ਜੇ(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        ਅੱਖਰ lastc = part[3].len && part[3].len <= part[3].ਮਾਪ ? part[3].str[part[3].len - 1] : 0;
        *print_ਅਗੇਤਰ = lastc == '\n' || lastc == '\r';
    }
}

ਖਾਲੀ av_log_format_ਸਤਰ(ਖਾਲੀ *ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl,
                        ਅੱਖਰ *ਸਤਰ, ਪੂਰਨ ਸਤਰ_ਮਾਪ, ਪੂਰਨ *print_ਅਗੇਤਰ)
{
    av_log_format_line2(ptr, level, fmt, vl, ਸਤਰ, ਸਤਰ_ਮਾਪ, print_ਅਗੇਤਰ);
}

ਪੂਰਨ av_log_format_line2(ਖਾਲੀ *ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl,
                        ਅੱਖਰ *ਸਤਰ, ਪੂਰਨ ਸਤਰ_ਮਾਪ, ਪੂਰਨ *print_ਅਗੇਤਰ)
{
    AVBPrint part[5];
    ਪੂਰਨ ret;

    format_ਸਤਰ(ptr, level, fmt, vl, part, print_ਅਗੇਤਰ, ਨਿਰਾ);
    ret = snprintf(ਸਤਰ, ਸਤਰ_ਮਾਪ, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ਨਿਰਾ);
    ਵਾਪਸ ret;
}

ਖਾਲੀ av_log_default_callback(ਖਾਲੀ* ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ* fmt, va_list vl)
{
    ਸਥਿਰ ਪੂਰਨ print_ਅਗੇਤਰ = 1;
    ਸਥਿਰ ਪੂਰਨ ਗਿਣਤੀ_2;
    ਸਥਿਰ ਅੱਖਰ prev[ਸਤਰ_SZ];
    AVBPrint part[5];
    ਅੱਖਰ ਸਤਰ[ਸਤਰ_SZ];
    ਸਥਿਰ ਪੂਰਨ is_atty;
    ਪੂਰਨ type[2];
    ਬਿਨਾਨਿਸ਼ਾਨੀ tint = 0;

    ਜੇ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    ਜੇ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        ਵਾਪਸ;
    ff_mutex_ਤਾਲਾ(&mutex);

    format_ਸਤਰ(ptr, level, fmt, vl, part, &print_ਅਗੇਤਰ, type);
    snprintf(ਸਤਰ, ਆਕਾਰ(ਸਤਰ), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#ਜੇ HAVE_ISATTY
    ਜੇ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#ਜੇ_ਅੰਤ

    ਜੇ (print_ਅਗੇਤਰ && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(ਸਤਰ, prev) &&
        *ਸਤਰ && ਸਤਰ[ਲੜੀ_ਲੰਬਾਈ(ਸਤਰ) - 1] != '\r'){
        ਗਿਣਤੀ_2++;
        ਜੇ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", ਗਿਣਤੀ_2);
        ਜਾਓ ਸਿਰਾ;
    }
    ਜੇ (ਗਿਣਤੀ_2 > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", ਗਿਣਤੀ_2);
        ਗਿਣਤੀ_2 = 0;
    }
    strcpy(prev, ਸਤਰ);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_ਪੱਧਰ - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_ਪੱਧਰ - 1), tint >> 8, part[3].str);

#ਜੇ CONFIG_VALGRIND_BACKTRACE
    ਜੇ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#ਜੇ_ਅੰਤ
ਸਿਰਾ:
    av_bprint_finalize(part+3, ਨਿਰਾ);
    ff_mutex_unlock(&mutex);
}

ਸਥਿਰ ਖਾਲੀ (*_Atomic av_log_callback)(ਖਾਲੀ*, ਪੂਰਨ, ਅਚਲ ਅੱਖਰ*, va_list) = av_log_default_callback;

ਖਾਲੀ av_log(ਖਾਲੀ* avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

ਖਾਲੀ av_log_once(ਖਾਲੀ* avcl, ਪੂਰਨ initial_level, ਪੂਰਨ subsequent_level, ਪੂਰਨ *state, ਅਚਲ ਅੱਖਰ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

ਖਾਲੀ av_vlog(ਖਾਲੀ* avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ਨਿਰਾ;
    ਖਾਲੀ (*log_callback)(ਖਾਲੀ*, ਪੂਰਨ, ਅਚਲ ਅੱਖਰ*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    ਜੇ (avc && avc->ਸੰਸਕਰਣ >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_ਵਿੱਥ_ਵਿੱਥ && level >= AV_LOG_FATAL)
        level += *(ਪੂਰਨ *) (((uint8_t *) avcl) + avc->log_level_ਵਿੱਥ_ਵਿੱਥ);
    ਜੇ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

ਪੂਰਨ av_log_get_level(ਖਾਲੀ)
{
    ਵਾਪਸ atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

ਖਾਲੀ av_log_ਸੈੱਟ_level(ਪੂਰਨ level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

ਖਾਲੀ av_log_ਸੈੱਟ_flags(ਪੂਰਨ arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

ਪੂਰਨ av_log_get_flags(ਖਾਲੀ)
{
    ਵਾਪਸ atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

ਖਾਲੀ av_log_ਸੈੱਟ_callback(ਖਾਲੀ (*callback)(ਖਾਲੀ*, ਪੂਰਨ, ਅਚਲ ਅੱਖਰ*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ਸਥਿਰ ਖਾਲੀ missing_feature_sample(ਪੂਰਨ sample, ਖਾਲੀ *avc, ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ,
                                   va_list ਦਲੀਲ_list)
{
    av_vlog(avc, AV_LOG_WARNING, ਸੁਨੇਹਾ, ਦਲੀਲ_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    ਜੇ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

ਖਾਲੀ avpriv_request_sample(ਖਾਲੀ *avc, ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...)
{
    va_list ਦਲੀਲ_list;

    va_start(ਦਲੀਲ_list, ਸੁਨੇਹਾ);
    missing_feature_sample(1, avc, ਸੁਨੇਹਾ, ਦਲੀਲ_list);
    va_end(ਦਲੀਲ_list);
}

ਖਾਲੀ avpriv_report_missing_feature(ਖਾਲੀ *avc, ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...)
{
    va_list ਦਲੀਲ_list;

    va_start(ਦਲੀਲ_list, ਸੁਨੇਹਾ);
    missing_feature_sample(0, avc, ਸੁਨੇਹਾ, ਦਲੀਲ_list);
    va_end(ਦਲੀਲ_list);
}
