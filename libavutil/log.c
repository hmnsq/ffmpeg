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
#اگر_ختم
#اگر HAVE_IO_H
#شامل <io.h>
#اگر_ختم
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

ساکن AVMutex mutex = AV_MUTEX_INITIALIZER;

#تعریف_کرو سطر_SZ 1024

#اگر HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#شامل <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#تعریف_کرو BACKTRACE_LOGLEVEL AV_LOG_ERROR
#اگر_ختم

ساکن atomic_int av_log_level = AV_LOG_INFO;
ساکن atomic_int av_log_flags = 0;

#تعریف_کرو NB_سطحیں 8
#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#شامل <windows.h>
ساکن ثابت uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_داخلہ           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_داخلہ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_داخلہ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_داخلہ        ] = 5,
};

ساکن int16_t background, attr_orig;
ساکن HANDLE con;
#اگر_ختم

ساکن ثابت uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_داخلہ           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_داخلہ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_داخلہ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_داخلہ        ] = 207 << 8 | 0x05,
};

ساکن صحیح use_color = -1;

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ساکن خالی win_console_puts(ثابت حرف *str)
{
    ثابت uint8_t *q = str;
    uint16_t سطر[سطر_SZ];

    جب (*q) {
        uint16_t *buf = سطر;
        DWORD nb_chars = 0;
        DWORD written;

        جب (*q && nb_chars < سطر_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; جاؤ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, سطر, nb_chars, &written, تہی);
    }
}
#اگر_ختم

ساکن خالی check_color_terminal(خالی)
{
    حرف *رکن = getenv("TERM");

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_بفر_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    اگر (con != INVALID_HANDLE_قدر && !Get_Console_منوال(con, &dummy))
        con = INVALID_HANDLE_قدر;
    اگر (con != INVALID_HANDLE_قدر) {
        Get_Console_Screen_بفر_Info(con, &con_info);
        attr_orig  = con_info.w_اوصاف;
        background = attr_orig & 0xF0;
    }
#اگر_ختم

    اگر (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } ورنہ اگر (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } ورنہ {
#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_قدر);
#وگرنہ_اگر HAVE_ISATTY
        use_color = (رکن && isatty(2));
#ورنہ
        use_color = 0;
#اگر_ختم
    }

    اگر (getenv("AV_LOG_FORCE_256COLOR") || رکن && لڑی_تلاش(رکن, "256color"))
        use_color *= 256;
}

ساکن خالی ansi_fputs(صحیح level, صحیح tint, ثابت حرف *str, صحیح local_use_color)
{
    اگر (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#اگر defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        اگر (level == AV_LOG_WARNING / 8)
            intensity = 1;
#اگر_ختم
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } ورنہ اگر (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } ورنہ اگر (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } ورنہ
        fputs(str, stderr);
}

ساکن خالی colored_fputs(صحیح level, صحیح tint, ثابت حرف *str)
{
    صحیح local_use_color;
    اگر (!*str)
        واپس;

    اگر (use_color < 0)
        check_color_terminal();

    اگر (level == AV_LOG_INFO/8) local_use_color = 0;
    ورنہ                        local_use_color = use_color;

#اگر defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    اگر (con != INVALID_HANDLE_قدر) {
        اگر (local_use_color)
            سیٹ_Console_متن_Attribute(con, background | win_color[level]);
        win_console_puts(str);
        اگر (local_use_color)
            سیٹ_Console_متن_Attribute(con, attr_orig);
    } ورنہ {
        ansi_fputs(level, tint, str, local_use_color);
    }
#ورنہ
    ansi_fputs(level, tint, str, local_use_color);
#اگر_ختم

}

ثابت حرف *av_default_شے_name(خالی *ptr)
{
    واپس (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(خالی *ptr)
{
    واپس (*(AVClass **) ptr)->category;
}

ساکن خالی sanitize(uint8_t *سطر){
    جب(*سطر){
        اگر(*سطر < 0x08 || (*سطر > 0x0D && *سطر < 0x20))
            *سطر='?';
        سطر++;
    }
}

ساکن صحیح get_category(خالی *ptr){
    AVClass *avc = *(AVClass **) ptr;
    اگر(    !avc
        || (avc->نسخہ&0xFF)<100
        ||  avc->نسخہ < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) واپس AV_CLASS_CATEGORY_NA + 16;

    اگر(avc->get_category)
        واپس avc->get_category(ptr) + 16;

    واپس avc->category + 16;
}

ساکن ثابت حرف *get_level_str(صحیح level)
{
    انتخاب (level) {
    حالت AV_LOG_QUIET:
        واپس "quiet";
    حالت AV_LOG_DEBUG:
        واپس "debug";
    حالت AV_LOG_TRACE:
        واپس "trace";
    حالت AV_LOG_VERBOSE:
        واپس "verbose";
    حالت AV_LOG_INFO:
        واپس "info";
    حالت AV_LOG_WARNING:
        واپس "warning";
    حالت AV_LOG_ERROR:
        واپس "error";
    حالت AV_LOG_FATAL:
        واپس "fatal";
    حالت AV_LOG_PANIC:
        واپس "panic";
    طےشدہ:
        واپس "";
    }
}

ساکن ثابت حرف *شے_name(خالی *obj, ثابت AVClass *cls)
{
    واپس (cls->شے_name ? cls->شے_name : av_default_شے_name)(obj);
}

ساکن خالی format_date_now(AVBPrint* bp_وقت, صحیح include_date)
{
    ساخت tm *ptm, tmbuf;
    ثابت int64_t وقت_us = av_gettime();
    ثابت int64_t وقت_ms = وقت_us / 1000;
    ثابت time_t وقت_s   = وقت_ms / 1000;
    ثابت صحیح millisec    = وقت_ms - (وقت_s * 1000);
    ptm                   = localtime_r(&وقت_s, &tmbuf);
    اگر (ptm) {
        اگر (include_date)
            av_bprint_strftime(bp_وقت, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_وقت, "%H:%M:%S", ptm);
        av_bprintf(bp_وقت, ".%03d ", millisec);
    }
}

ساکن خالی format_سطر(خالی *avcl, صحیح level, ثابت حرف *fmt, va_list vl,
                        AVBPrint part[5], صحیح *print_سابقہ, صحیح type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : تہی;
    av_bprint_init(part+0, 0, AV_BPRINT_سائز_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_سائز_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_سائز_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_سائز_AUTOMATIC);
    صحیح flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    اگر(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    اگر (*print_سابقہ && avc) {
        اگر (avc->والد_log_context_انحراف) {
            AVClass** والد = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->والد_log_context_انحراف);
            اگر (والد && *والد) {
                av_bprintf(part+0, "[%s @ %p] ",
                           شے_name(والد, *والد), والد);
                اگر(type) type[0] = get_category(والد);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   شے_name(avcl, avc), avcl);
        اگر(type) type[1] = get_category(avcl);
    }

    اگر (*print_سابقہ && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_وقت | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    اگر (*print_سابقہ && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    اگر(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        حرف lastc = part[3].len && part[3].len <= part[3].سائز ? part[3].str[part[3].len - 1] : 0;
        *print_سابقہ = lastc == '\n' || lastc == '\r';
    }
}

خالی av_log_format_سطر(خالی *ptr, صحیح level, ثابت حرف *fmt, va_list vl,
                        حرف *سطر, صحیح سطر_سائز, صحیح *print_سابقہ)
{
    av_log_format_line2(ptr, level, fmt, vl, سطر, سطر_سائز, print_سابقہ);
}

صحیح av_log_format_line2(خالی *ptr, صحیح level, ثابت حرف *fmt, va_list vl,
                        حرف *سطر, صحیح سطر_سائز, صحیح *print_سابقہ)
{
    AVBPrint part[5];
    صحیح ret;

    format_سطر(ptr, level, fmt, vl, part, print_سابقہ, تہی);
    ret = snprintf(سطر, سطر_سائز, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, تہی);
    واپس ret;
}

خالی av_log_default_callback(خالی* ptr, صحیح level, ثابت حرف* fmt, va_list vl)
{
    ساکن صحیح print_سابقہ = 1;
    ساکن صحیح گنتی;
    ساکن حرف پچھلا[سطر_SZ];
    AVBPrint part[5];
    حرف سطر[سطر_SZ];
    ساکن صحیح is_atty;
    صحیح type[2];
    غیرعلامتی tint = 0;

    اگر (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    اگر (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        واپس;
    ff_mutex_تالا(&mutex);

    format_سطر(ptr, level, fmt, vl, part, &print_سابقہ, type);
    snprintf(سطر, حجم(سطر), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#اگر HAVE_ISATTY
    اگر (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#اگر_ختم

    اگر (print_سابقہ && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(سطر, پچھلا) &&
        *سطر && سطر[لڑی_لمبائی(سطر) - 1] != '\r'){
        گنتی++;
        اگر (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", گنتی);
        جاؤ انتہا;
    }
    اگر (گنتی > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", گنتی);
        گنتی = 0;
    }
    strcpy(پچھلا, سطر);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_سطحیں - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_سطحیں - 1), tint >> 8, part[3].str);

#اگر CONFIG_VALGRIND_BACKTRACE
    اگر (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#اگر_ختم
انتہا:
    av_bprint_finalize(part+3, تہی);
    ff_mutex_unlock(&mutex);
}

ساکن خالی (*_Atomic av_log_callback)(خالی*, صحیح, ثابت حرف*, va_list) = av_log_default_callback;

خالی av_log(خالی* avcl, صحیح level, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

خالی av_log_once(خالی* avcl, صحیح initial_level, صحیح subsequent_level, صحیح *state, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

خالی av_vlog(خالی* avcl, صحیح level, ثابت حرف *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : تہی;
    خالی (*log_callback)(خالی*, صحیح, ثابت حرف*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    اگر (avc && avc->نسخہ >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_انحراف_انحراف && level >= AV_LOG_FATAL)
        level += *(صحیح *) (((uint8_t *) avcl) + avc->log_level_انحراف_انحراف);
    اگر (log_callback)
        log_callback(avcl, level, fmt, vl);
}

صحیح av_log_get_level(خالی)
{
    واپس atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

خالی av_log_سیٹ_level(صحیح level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

خالی av_log_سیٹ_flags(صحیح arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

صحیح av_log_get_flags(خالی)
{
    واپس atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

خالی av_log_سیٹ_callback(خالی (*callback)(خالی*, صحیح, ثابت حرف*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ساکن خالی missing_feature_sample(صحیح sample, خالی *avc, ثابت حرف *پیغام,
                                   va_list دلیل_list)
{
    av_vlog(avc, AV_LOG_WARNING, پیغام, دلیل_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    اگر (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

خالی avpriv_request_sample(خالی *avc, ثابت حرف *پیغام, ...)
{
    va_list دلیل_list;

    va_start(دلیل_list, پیغام);
    missing_feature_sample(1, avc, پیغام, دلیل_list);
    va_end(دلیل_list);
}

خالی avpriv_report_missing_feature(خالی *avc, ثابت حرف *پیغام, ...)
{
    va_list دلیل_list;

    va_start(دلیل_list, پیغام);
    missing_feature_sample(0, avc, پیغام, دلیل_list);
    va_end(دلیل_list);
}
