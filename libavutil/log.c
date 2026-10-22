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

#شامل "config.h"

#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif
#اگر HAVE_IO_H
#شامل <io.h>
#endif
#شامل <inttypes.h>
#شامل <stdarg.h>
#شامل <stdatomic.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل "bprint.h"
#شامل "common.h"
#شامل "internal.h"
#شامل "log.h"
#شامل "thread.h"
#شامل "time.h"
#شامل "time_internal.h"

ایستا AVMutex mutex = AV_MUTEX_INITIALIZER;

#define سطر_SZ 1024

#اگر HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#شامل <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

ایستا atomic_int av_log_level = AV_LOG_INFO;
ایستا atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#شامل <windows.h>
ایستا ثابت uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_درون_داد           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_درون_داد  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_درون_داد  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_درون_داد        ] = 5,
};

ایستا int16_t background, attr_orig;
ایستا HANDLE con;
#endif

ایستا ثابت uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_درون_داد           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_درون_داد  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_درون_داد  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_درون_داد        ] = 207 << 8 | 0x05,
};

ایستا صحیح use_color = -1;

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ایستا تهی win_console_puts(ثابت نویسه *str)
{
    ثابت uint8_t *q = str;
    uint16_t سطر[سطر_SZ];

    وقتی (*q) {
        uint16_t *buf = سطر;
        DWORD nb_chars = 0;
        DWORD written;

        وقتی (*q && nb_chars < سطر_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; برو continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, سطر, nb_chars, &written, پوچ);
    }
}
#endif

ایستا تهی check_color_terminal(تهی)
{
    نویسه *term = getenv("TERM");

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    اگر (con != INVALID_HANDLE_مقدار && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_مقدار;
    اگر (con != INVALID_HANDLE_مقدار) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    اگر (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } وگرنه اگر (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } وگرنه {
#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_مقدار);
#وگرنهاگر HAVE_ISATTY
        use_color = (term && isatty(2));
#وگرنه
        use_color = 0;
#endif
    }

    اگر (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

ایستا تهی ansi_fputs(صحیح level, صحیح tint, ثابت نویسه *str, صحیح local_use_color)
{
    اگر (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#اگر defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        اگر (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } وگرنه اگر (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } وگرنه اگر (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } وگرنه
        fputs(str, stderr);
}

ایستا تهی colored_fputs(صحیح level, صحیح tint, ثابت نویسه *str)
{
    صحیح local_use_color;
    اگر (!*str)
        بازگشت;

    اگر (use_color < 0)
        check_color_terminal();

    اگر (level == AV_LOG_INFO/8) local_use_color = 0;
    وگرنه                        local_use_color = use_color;

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    اگر (con != INVALID_HANDLE_مقدار) {
        اگر (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        اگر (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } وگرنه {
        ansi_fputs(level, tint, str, local_use_color);
    }
#وگرنه
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ثابت نویسه *av_default_item_name(تهی *ptr)
{
    بازگشت (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(تهی *ptr)
{
    بازگشت (*(AVClass **) ptr)->category;
}

ایستا تهی sanitize(uint8_t *سطر){
    وقتی(*سطر){
        اگر(*سطر < 0x08 || (*سطر > 0x0D && *سطر < 0x20))
            *سطر='?';
        سطر++;
    }
}

ایستا صحیح get_category(تهی *ptr){
    AVClass *avc = *(AVClass **) ptr;
    اگر(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) بازگشت AV_CLASS_CATEGORY_NA + 16;

    اگر(avc->get_category)
        بازگشت avc->get_category(ptr) + 16;

    بازگشت avc->category + 16;
}

ایستا ثابت نویسه *get_level_str(صحیح level)
{
    انتخاب (level) {
    حالت AV_LOG_QUIET:
        بازگشت "quiet";
    حالت AV_LOG_DEBUG:
        بازگشت "debug";
    حالت AV_LOG_TRACE:
        بازگشت "trace";
    حالت AV_LOG_VERBOSE:
        بازگشت "verbose";
    حالت AV_LOG_INFO:
        بازگشت "info";
    حالت AV_LOG_WARNING:
        بازگشت "warning";
    حالت AV_LOG_ERROR:
        بازگشت "error";
    حالت AV_LOG_FATAL:
        بازگشت "fatal";
    حالت AV_LOG_PANIC:
        بازگشت "panic";
    پیشفرض:
        بازگشت "";
    }
}

ایستا ثابت نویسه *item_name(تهی *obj, ثابت AVClass *cls)
{
    بازگشت (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

ایستا تهی format_date_now(AVBPrint* bp_time, صحیح include_date)
{
    ساختار tm *ptm, tmbuf;
    ثابت int64_t time_us = av_gettime();
    ثابت int64_t time_ms = time_us / 1000;
    ثابت time_t time_s   = time_ms / 1000;
    ثابت صحیح millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    اگر (ptm) {
        اگر (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

ایستا تهی format_سطر(تهی *avcl, صحیح level, ثابت نویسه *fmt, va_list vl,
                        AVBPrint part[5], صحیح *print_prefix, صحیح type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : پوچ;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    صحیح flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    اگر(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    اگر (*print_prefix && avc) {
        اگر (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            اگر (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                اگر(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        اگر(type) type[1] = get_category(avcl);
    }

    اگر (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    اگر (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    اگر(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        نویسه lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

تهی av_log_format_سطر(تهی *ptr, صحیح level, ثابت نویسه *fmt, va_list vl,
                        نویسه *سطر, صحیح سطر_size, صحیح *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, سطر, سطر_size, print_prefix);
}

صحیح av_log_format_line2(تهی *ptr, صحیح level, ثابت نویسه *fmt, va_list vl,
                        نویسه *سطر, صحیح سطر_size, صحیح *print_prefix)
{
    AVBPrint part[5];
    صحیح ret;

    format_سطر(ptr, level, fmt, vl, part, print_prefix, پوچ);
    ret = snprintf(سطر, سطر_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, پوچ);
    بازگشت ret;
}

تهی av_log_default_callback(تهی* ptr, صحیح level, ثابت نویسه* fmt, va_list vl)
{
    ایستا صحیح print_prefix = 1;
    ایستا صحیح شمار;
    ایستا نویسه prev[سطر_SZ];
    AVBPrint part[5];
    نویسه سطر[سطر_SZ];
    ایستا صحیح is_atty;
    صحیح type[2];
    unsigned tint = 0;

    اگر (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    اگر (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        بازگشت;
    ff_mutex_lock(&mutex);

    format_سطر(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(سطر, اندازه(سطر), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#اگر HAVE_ISATTY
    اگر (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    اگر (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(سطر, prev) &&
        *سطر && سطر[strlen(سطر) - 1] != '\r'){
        شمار++;
        اگر (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", شمار);
        برو end;
    }
    اگر (شمار > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", شمار);
        شمار = 0;
    }
    strcpy(prev, سطر);

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

#اگر CONFIG_VALGRIND_BACKTRACE
    اگر (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, پوچ);
    ff_mutex_unlock(&mutex);
}

ایستا تهی (*_Atomic av_log_callback)(تهی*, صحیح, ثابت نویسه*, va_list) = av_log_default_callback;

تهی av_log(تهی* avcl, صحیح level, ثابت نویسه *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

تهی av_log_once(تهی* avcl, صحیح initial_level, صحیح subsequent_level, صحیح *state, ثابت نویسه *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

تهی av_vlog(تهی* avcl, صحیح level, ثابت نویسه *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : پوچ;
    تهی (*log_callback)(تهی*, صحیح, ثابت نویسه*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    اگر (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(صحیح *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    اگر (log_callback)
        log_callback(avcl, level, fmt, vl);
}

صحیح av_log_get_level(تهی)
{
    بازگشت atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

تهی av_log_set_level(صحیح level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

تهی av_log_set_flags(صحیح arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

صحیح av_log_get_flags(تهی)
{
    بازگشت atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

تهی av_log_set_callback(تهی (*callback)(تهی*, صحیح, ثابت نویسه*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ایستا تهی missing_feature_sample(صحیح sample, تهی *avc, ثابت نویسه *پیام,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, پیام, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    اگر (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

تهی avpriv_request_sample(تهی *avc, ثابت نویسه *پیام, ...)
{
    va_list argument_list;

    va_start(argument_list, پیام);
    missing_feature_sample(1, avc, پیام, argument_list);
    va_end(argument_list);
}

تهی avpriv_report_missing_feature(تهی *avc, ثابت نویسه *پیام, ...)
{
    va_list argument_list;

    va_start(argument_list, پیام);
    missing_feature_sample(0, avc, پیام, argument_list);
    va_end(argument_list);
}
