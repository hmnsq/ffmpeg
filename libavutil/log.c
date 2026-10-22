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

#અન્તર્ભાવ "config.h"

#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif
#જો HAVE_IO_H
#અન્તર્ભાવ <io.h>
#endif
#અન્તર્ભાવ <inttypes.h>
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ "bprint.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "internal.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "thread.h"
#અન્તર્ભાવ "time.h"
#અન્તર્ભાવ "time_internal.h"

સ્થિર AVMutex mutex = AV_MUTEX_INITIALIZER;

#define લીટી_SZ 1024

#જો HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#અન્તર્ભાવ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

સ્થિર atomic_int av_log_level = AV_LOG_INFO;
સ્થિર atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#જો defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#અન્તર્ભાવ <windows.h>
સ્થિર અચલ uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_આગત           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_આગત  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_આગત  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_આગત        ] = 5,
};

સ્થિર int16_t background, attr_orig;
સ્થિર HANDLE con;
#endif

સ્થિર અચલ uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_આગત           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_આગત  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_આગત  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_આગત        ] = 207 << 8 | 0x05,
};

સ્થિર પૂર્ણાંક use_color = -1;

#જો defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
સ્થિર શૂન્ય win_console_puts(અચલ અક્ષર *str)
{
    અચલ uint8_t *q = str;
    uint16_t લીટી[લીટી_SZ];

    જ્યારે (*q) {
        uint16_t *buf = લીટી;
        DWORD nb_chars = 0;
        DWORD written;

        જ્યારે (*q && nb_chars < લીટી_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; જાઓ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, લીટી, nb_chars, &written, ખાલી);
    }
}
#endif

સ્થિર શૂન્ય check_color_terminal(શૂન્ય)
{
    અક્ષર *term = getenv("TERM");

#જો defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    જો (con != INVALID_HANDLE_કિંમત && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_કિંમત;
    જો (con != INVALID_HANDLE_કિંમત) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    જો (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } નહીંતર જો (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } નહીંતર {
#જો defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_કિંમત);
#અથવાજો HAVE_ISATTY
        use_color = (term && isatty(2));
#નહીંતર
        use_color = 0;
#endif
    }

    જો (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

સ્થિર શૂન્ય ansi_fputs(પૂર્ણાંક level, પૂર્ણાંક tint, અચલ અક્ષર *str, પૂર્ણાંક local_use_color)
{
    જો (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#જો defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        જો (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } નહીંતર જો (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } નહીંતર જો (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } નહીંતર
        fputs(str, stderr);
}

સ્થિર શૂન્ય colored_fputs(પૂર્ણાંક level, પૂર્ણાંક tint, અચલ અક્ષર *str)
{
    પૂર્ણાંક local_use_color;
    જો (!*str)
        પાછા;

    જો (use_color < 0)
        check_color_terminal();

    જો (level == AV_LOG_INFO/8) local_use_color = 0;
    નહીંતર                        local_use_color = use_color;

#જો defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    જો (con != INVALID_HANDLE_કિંમત) {
        જો (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        જો (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } નહીંતર {
        ansi_fputs(level, tint, str, local_use_color);
    }
#નહીંતર
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

અચલ અક્ષર *av_default_item_name(શૂન્ય *ptr)
{
    પાછા (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(શૂન્ય *ptr)
{
    પાછા (*(AVClass **) ptr)->category;
}

સ્થિર શૂન્ય sanitize(uint8_t *લીટી){
    જ્યારે(*લીટી){
        જો(*લીટી < 0x08 || (*લીટી > 0x0D && *લીટી < 0x20))
            *લીટી='?';
        લીટી++;
    }
}

સ્થિર પૂર્ણાંક get_category(શૂન્ય *ptr){
    AVClass *avc = *(AVClass **) ptr;
    જો(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) પાછા AV_CLASS_CATEGORY_NA + 16;

    જો(avc->get_category)
        પાછા avc->get_category(ptr) + 16;

    પાછા avc->category + 16;
}

સ્થિર અચલ અક્ષર *get_level_str(પૂર્ણાંક level)
{
    પસંદગી (level) {
    સ્થિતિ AV_LOG_QUIET:
        પાછા "quiet";
    સ્થિતિ AV_LOG_DEBUG:
        પાછા "debug";
    સ્થિતિ AV_LOG_TRACE:
        પાછા "trace";
    સ્થિતિ AV_LOG_VERBOSE:
        પાછા "verbose";
    સ્થિતિ AV_LOG_INFO:
        પાછા "info";
    સ્થિતિ AV_LOG_WARNING:
        પાછા "warning";
    સ્થિતિ AV_LOG_ERROR:
        પાછા "error";
    સ્થિતિ AV_LOG_FATAL:
        પાછા "fatal";
    સ્થિતિ AV_LOG_PANIC:
        પાછા "panic";
    મૂળભૂત:
        પાછા "";
    }
}

સ્થિર અચલ અક્ષર *item_name(શૂન્ય *obj, અચલ AVClass *cls)
{
    પાછા (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

સ્થિર શૂન્ય format_date_now(AVBPrint* bp_time, પૂર્ણાંક include_date)
{
    સંરચના tm *ptm, tmbuf;
    અચલ int64_t time_us = av_gettime();
    અચલ int64_t time_ms = time_us / 1000;
    અચલ time_t time_s   = time_ms / 1000;
    અચલ પૂર્ણાંક millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    જો (ptm) {
        જો (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

સ્થિર શૂન્ય format_લીટી(શૂન્ય *avcl, પૂર્ણાંક level, અચલ અક્ષર *fmt, va_list vl,
                        AVBPrint part[5], પૂર્ણાંક *print_prefix, પૂર્ણાંક type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ખાલી;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    પૂર્ણાંક flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    જો(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    જો (*print_prefix && avc) {
        જો (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            જો (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                જો(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        જો(type) type[1] = get_category(avcl);
    }

    જો (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    જો (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    જો(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        અક્ષર lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

શૂન્ય av_log_format_લીટી(શૂન્ય *ptr, પૂર્ણાંક level, અચલ અક્ષર *fmt, va_list vl,
                        અક્ષર *લીટી, પૂર્ણાંક લીટી_size, પૂર્ણાંક *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, લીટી, લીટી_size, print_prefix);
}

પૂર્ણાંક av_log_format_line2(શૂન્ય *ptr, પૂર્ણાંક level, અચલ અક્ષર *fmt, va_list vl,
                        અક્ષર *લીટી, પૂર્ણાંક લીટી_size, પૂર્ણાંક *print_prefix)
{
    AVBPrint part[5];
    પૂર્ણાંક ret;

    format_લીટી(ptr, level, fmt, vl, part, print_prefix, ખાલી);
    ret = snprintf(લીટી, લીટી_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ખાલી);
    પાછા ret;
}

શૂન્ય av_log_default_callback(શૂન્ય* ptr, પૂર્ણાંક level, અચલ અક્ષર* fmt, va_list vl)
{
    સ્થિર પૂર્ણાંક print_prefix = 1;
    સ્થિર પૂર્ણાંક ગણતરી;
    સ્થિર અક્ષર prev[લીટી_SZ];
    AVBPrint part[5];
    અક્ષર લીટી[લીટી_SZ];
    સ્થિર પૂર્ણાંક is_atty;
    પૂર્ણાંક type[2];
    unsigned tint = 0;

    જો (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    જો (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        પાછા;
    ff_mutex_lock(&mutex);

    format_લીટી(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(લીટી, કદ(લીટી), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#જો HAVE_ISATTY
    જો (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    જો (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(લીટી, prev) &&
        *લીટી && લીટી[strlen(લીટી) - 1] != '\r'){
        ગણતરી++;
        જો (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", ગણતરી);
        જાઓ end;
    }
    જો (ગણતરી > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", ગણતરી);
        ગણતરી = 0;
    }
    strcpy(prev, લીટી);

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

#જો CONFIG_VALGRIND_BACKTRACE
    જો (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, ખાલી);
    ff_mutex_unlock(&mutex);
}

સ્થિર શૂન્ય (*_Atomic av_log_callback)(શૂન્ય*, પૂર્ણાંક, અચલ અક્ષર*, va_list) = av_log_default_callback;

શૂન્ય av_log(શૂન્ય* avcl, પૂર્ણાંક level, અચલ અક્ષર *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

શૂન્ય av_log_once(શૂન્ય* avcl, પૂર્ણાંક initial_level, પૂર્ણાંક subsequent_level, પૂર્ણાંક *state, અચલ અક્ષર *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

શૂન્ય av_vlog(શૂન્ય* avcl, પૂર્ણાંક level, અચલ અક્ષર *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ખાલી;
    શૂન્ય (*log_callback)(શૂન્ય*, પૂર્ણાંક, અચલ અક્ષર*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    જો (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(પૂર્ણાંક *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    જો (log_callback)
        log_callback(avcl, level, fmt, vl);
}

પૂર્ણાંક av_log_get_level(શૂન્ય)
{
    પાછા atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

શૂન્ય av_log_set_level(પૂર્ણાંક level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

શૂન્ય av_log_set_flags(પૂર્ણાંક arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

પૂર્ણાંક av_log_get_flags(શૂન્ય)
{
    પાછા atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

શૂન્ય av_log_set_callback(શૂન્ય (*callback)(શૂન્ય*, પૂર્ણાંક, અચલ અક્ષર*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

સ્થિર શૂન્ય missing_feature_sample(પૂર્ણાંક sample, શૂન્ય *avc, અચલ અક્ષર *સંદેશ,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, સંદેશ, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    જો (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

શૂન્ય avpriv_request_sample(શૂન્ય *avc, અચલ અક્ષર *સંદેશ, ...)
{
    va_list argument_list;

    va_start(argument_list, સંદેશ);
    missing_feature_sample(1, avc, સંદેશ, argument_list);
    va_end(argument_list);
}

શૂન્ય avpriv_report_missing_feature(શૂન્ય *avc, અચલ અક્ષર *સંદેશ, ...)
{
    va_list argument_list;

    va_start(argument_list, સંદેશ);
    missing_feature_sample(0, avc, સંદેશ, argument_list);
    va_end(argument_list);
}
