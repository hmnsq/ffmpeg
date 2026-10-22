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

#অন্তর্ভাব "config.h"

#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif
#যদি HAVE_IO_H
#অন্তর্ভাব <io.h>
#endif
#অন্তর্ভাব <inttypes.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব "bprint.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "internal.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "time.h"
#অন্তর্ভাব "time_internal.h"

স্থির AVMutex mutex = AV_MUTEX_INITIALIZER;

#define সারি_SZ 1024

#যদি HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#অন্তর্ভাব <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

স্থির atomic_int av_log_level = AV_LOG_INFO;
স্থির atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#যদি defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#অন্তর্ভাব <windows.h>
স্থির ধ্রুব uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_প্রবেশ           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_প্রবেশ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_প্রবেশ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_প্রবেশ        ] = 5,
};

স্থির int16_t background, attr_orig;
স্থির HANDLE con;
#endif

স্থির ধ্রুব uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_প্রবেশ           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_প্রবেশ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_প্রবেশ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_প্রবেশ        ] = 207 << 8 | 0x05,
};

স্থির পূর্ণাঙ্ক use_color = -1;

#যদি defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
স্থির শূন্য win_console_puts(ধ্রুব বর্ণ *str)
{
    ধ্রুব uint8_t *q = str;
    uint16_t সারি[সারি_SZ];

    যাবত্ (*q) {
        uint16_t *buf = সারি;
        DWORD nb_chars = 0;
        DWORD written;

        যাবত্ (*q && nb_chars < সারি_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; গচ্ছ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, সারি, nb_chars, &written, রিক্ত);
    }
}
#endif

স্থির শূন্য check_color_terminal(শূন্য)
{
    বর্ণ *term = getenv("TERM");

#যদি defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    যদি (con != INVALID_HANDLE_মান && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_মান;
    যদি (con != INVALID_HANDLE_মান) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    যদি (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } অন্যথা যদি (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } অন্যথা {
#যদি defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_মান);
#নোচেদ্যদি HAVE_ISATTY
        use_color = (term && isatty(2));
#অন্যথা
        use_color = 0;
#endif
    }

    যদি (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

স্থির শূন্য ansi_fputs(পূর্ণাঙ্ক level, পূর্ণাঙ্ক tint, ধ্রুব বর্ণ *str, পূর্ণাঙ্ক local_use_color)
{
    যদি (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#যদি defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        যদি (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } অন্যথা যদি (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } অন্যথা যদি (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } অন্যথা
        fputs(str, stderr);
}

স্থির শূন্য colored_fputs(পূর্ণাঙ্ক level, পূর্ণাঙ্ক tint, ধ্রুব বর্ণ *str)
{
    পূর্ণাঙ্ক local_use_color;
    যদি (!*str)
        প্রত্যাগম;

    যদি (use_color < 0)
        check_color_terminal();

    যদি (level == AV_LOG_INFO/8) local_use_color = 0;
    অন্যথা                        local_use_color = use_color;

#যদি defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    যদি (con != INVALID_HANDLE_মান) {
        যদি (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        যদি (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } অন্যথা {
        ansi_fputs(level, tint, str, local_use_color);
    }
#অন্যথা
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ধ্রুব বর্ণ *av_default_item_name(শূন্য *ptr)
{
    প্রত্যাগম (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(শূন্য *ptr)
{
    প্রত্যাগম (*(AVClass **) ptr)->category;
}

স্থির শূন্য sanitize(uint8_t *সারি){
    যাবত্(*সারি){
        যদি(*সারি < 0x08 || (*সারি > 0x0D && *সারি < 0x20))
            *সারি='?';
        সারি++;
    }
}

স্থির পূর্ণাঙ্ক get_category(শূন্য *ptr){
    AVClass *avc = *(AVClass **) ptr;
    যদি(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) প্রত্যাগম AV_CLASS_CATEGORY_NA + 16;

    যদি(avc->get_category)
        প্রত্যাগম avc->get_category(ptr) + 16;

    প্রত্যাগম avc->category + 16;
}

স্থির ধ্রুব বর্ণ *get_level_str(পূর্ণাঙ্ক level)
{
    বিকল্প (level) {
    পক্ষ AV_LOG_QUIET:
        প্রত্যাগম "quiet";
    পক্ষ AV_LOG_DEBUG:
        প্রত্যাগম "debug";
    পক্ষ AV_LOG_TRACE:
        প্রত্যাগম "trace";
    পক্ষ AV_LOG_VERBOSE:
        প্রত্যাগম "verbose";
    পক্ষ AV_LOG_INFO:
        প্রত্যাগম "info";
    পক্ষ AV_LOG_WARNING:
        প্রত্যাগম "warning";
    পক্ষ AV_LOG_ERROR:
        প্রত্যাগম "error";
    পক্ষ AV_LOG_FATAL:
        প্রত্যাগম "fatal";
    পক্ষ AV_LOG_PANIC:
        প্রত্যাগম "panic";
    স্বভাব:
        প্রত্যাগম "";
    }
}

স্থির ধ্রুব বর্ণ *item_name(শূন্য *obj, ধ্রুব AVClass *cls)
{
    প্রত্যাগম (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

স্থির শূন্য format_date_now(AVBPrint* bp_time, পূর্ণাঙ্ক include_date)
{
    সংরচনা tm *ptm, tmbuf;
    ধ্রুব int64_t time_us = av_gettime();
    ধ্রুব int64_t time_ms = time_us / 1000;
    ধ্রুব time_t time_s   = time_ms / 1000;
    ধ্রুব পূর্ণাঙ্ক millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    যদি (ptm) {
        যদি (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

স্থির শূন্য format_সারি(শূন্য *avcl, পূর্ণাঙ্ক level, ধ্রুব বর্ণ *fmt, va_list vl,
                        AVBPrint part[5], পূর্ণাঙ্ক *print_prefix, পূর্ণাঙ্ক type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : রিক্ত;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    পূর্ণাঙ্ক flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    যদি(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    যদি (*print_prefix && avc) {
        যদি (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            যদি (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                যদি(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        যদি(type) type[1] = get_category(avcl);
    }

    যদি (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    যদি (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    যদি(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        বর্ণ lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

শূন্য av_log_format_সারি(শূন্য *ptr, পূর্ণাঙ্ক level, ধ্রুব বর্ণ *fmt, va_list vl,
                        বর্ণ *সারি, পূর্ণাঙ্ক সারি_size, পূর্ণাঙ্ক *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, সারি, সারি_size, print_prefix);
}

পূর্ণাঙ্ক av_log_format_line2(শূন্য *ptr, পূর্ণাঙ্ক level, ধ্রুব বর্ণ *fmt, va_list vl,
                        বর্ণ *সারি, পূর্ণাঙ্ক সারি_size, পূর্ণাঙ্ক *print_prefix)
{
    AVBPrint part[5];
    পূর্ণাঙ্ক ret;

    format_সারি(ptr, level, fmt, vl, part, print_prefix, রিক্ত);
    ret = snprintf(সারি, সারি_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, রিক্ত);
    প্রত্যাগম ret;
}

শূন্য av_log_default_callback(শূন্য* ptr, পূর্ণাঙ্ক level, ধ্রুব বর্ণ* fmt, va_list vl)
{
    স্থির পূর্ণাঙ্ক print_prefix = 1;
    স্থির পূর্ণাঙ্ক গুনতি;
    স্থির বর্ণ prev[সারি_SZ];
    AVBPrint part[5];
    বর্ণ সারি[সারি_SZ];
    স্থির পূর্ণাঙ্ক is_atty;
    পূর্ণাঙ্ক type[2];
    unsigned tint = 0;

    যদি (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    যদি (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        প্রত্যাগম;
    ff_mutex_lock(&mutex);

    format_সারি(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(সারি, পরিমাণ(সারি), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#যদি HAVE_ISATTY
    যদি (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    যদি (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(সারি, prev) &&
        *সারি && সারি[strlen(সারি) - 1] != '\r'){
        গুনতি++;
        যদি (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", গুনতি);
        গচ্ছ end;
    }
    যদি (গুনতি > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", গুনতি);
        গুনতি = 0;
    }
    strcpy(prev, সারি);

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

#যদি CONFIG_VALGRIND_BACKTRACE
    যদি (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, রিক্ত);
    ff_mutex_unlock(&mutex);
}

স্থির শূন্য (*_Atomic av_log_callback)(শূন্য*, পূর্ণাঙ্ক, ধ্রুব বর্ণ*, va_list) = av_log_default_callback;

শূন্য av_log(শূন্য* avcl, পূর্ণাঙ্ক level, ধ্রুব বর্ণ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

শূন্য av_log_once(শূন্য* avcl, পূর্ণাঙ্ক initial_level, পূর্ণাঙ্ক subsequent_level, পূর্ণাঙ্ক *state, ধ্রুব বর্ণ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

শূন্য av_vlog(শূন্য* avcl, পূর্ণাঙ্ক level, ধ্রুব বর্ণ *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : রিক্ত;
    শূন্য (*log_callback)(শূন্য*, পূর্ণাঙ্ক, ধ্রুব বর্ণ*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    যদি (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(পূর্ণাঙ্ক *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    যদি (log_callback)
        log_callback(avcl, level, fmt, vl);
}

পূর্ণাঙ্ক av_log_get_level(শূন্য)
{
    প্রত্যাগম atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

শূন্য av_log_set_level(পূর্ণাঙ্ক level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

শূন্য av_log_set_flags(পূর্ণাঙ্ক arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

পূর্ণাঙ্ক av_log_get_flags(শূন্য)
{
    প্রত্যাগম atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

শূন্য av_log_set_callback(শূন্য (*callback)(শূন্য*, পূর্ণাঙ্ক, ধ্রুব বর্ণ*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

স্থির শূন্য missing_feature_sample(পূর্ণাঙ্ক sample, শূন্য *avc, ধ্রুব বর্ণ *বার্তা,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, বার্তা, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    যদি (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

শূন্য avpriv_request_sample(শূন্য *avc, ধ্রুব বর্ণ *বার্তা, ...)
{
    va_list argument_list;

    va_start(argument_list, বার্তা);
    missing_feature_sample(1, avc, বার্তা, argument_list);
    va_end(argument_list);
}

শূন্য avpriv_report_missing_feature(শূন্য *avc, ধ্রুব বর্ণ *বার্তা, ...)
{
    va_list argument_list;

    va_start(argument_list, বার্তা);
    missing_feature_sample(0, avc, বার্তা, argument_list);
    va_end(argument_list);
}
