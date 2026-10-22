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

#ضمن "config.h"

#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#جے_انت
#إذا HAVE_IO_H
#ضمن <io.h>
#جے_انت
#ضمن <inttypes.h>
#ضمن <stdarg.h>
#ضمن <stdatomic.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن "bprint.h"
#ضمن "common.h"
#ضمن "internal.h"
#ضمن "log.h"
#ضمن "thread.h"
#ضمن "time.h"
#ضمن "time_internal.h"

ساكن AVMutex mutex = AV_MUTEX_INITIALIZER;

#تعریف_کرو سطر_SZ 1024

#إذا HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#ضمن <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#تعریف_کرو BACKTRACE_LOGLEVEL AV_LOG_ERROR
#جے_انت

ساكن atomic_int av_log_level = AV_LOG_INFO;
ساكن atomic_int av_log_flags = 0;

#تعریف_کرو NB_پدھراں 8
#إذا defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#ضمن <windows.h>
ساكن ثابت uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
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

ساكن int16_t background, attr_orig;
ساكن HANDLE con;
#جے_انت

ساكن ثابت uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
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

ساكن صحيح use_color = -1;

#إذا defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ساكن فراغ win_console_puts(ثابت حرف *str)
{
    ثابت uint8_t *q = str;
    uint16_t سطر[سطر_SZ];

    طالما (*q) {
        uint16_t *buf = سطر;
        DWORD nb_chars = 0;
        DWORD written;

        طالما (*q && nb_chars < سطر_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; اذهب continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, سطر, nb_chars, &written, عدم);
    }
}
#جے_انت

ساكن فراغ check_color_terminal(فراغ)
{
    حرف *رکن = getenv("TERM");

#إذا defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_بفر_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    إذا (con != INVALID_HANDLE_قدر && !Get_Console_منوال(con, &dummy))
        con = INVALID_HANDLE_قدر;
    إذا (con != INVALID_HANDLE_قدر) {
        Get_Console_Screen_بفر_Info(con, &con_info);
        attr_orig  = con_info.w_گن;
        background = attr_orig & 0xF0;
    }
#جے_انت

    إذا (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } وإلا إذا (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } وإلا {
#إذا defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_قدر);
#وإلاإذا HAVE_ISATTY
        use_color = (رکن && isatty(2));
#وإلا
        use_color = 0;
#جے_انت
    }

    إذا (getenv("AV_LOG_FORCE_256COLOR") || رکن && لڑی_کھوج(رکن, "256color"))
        use_color *= 256;
}

ساكن فراغ ansi_fputs(صحيح level, صحيح tint, ثابت حرف *str, صحيح local_use_color)
{
    إذا (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#إذا defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        إذا (level == AV_LOG_WARNING / 8)
            intensity = 1;
#جے_انت
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } وإلا إذا (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } وإلا إذا (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } وإلا
        fputs(str, stderr);
}

ساكن فراغ colored_fputs(صحيح level, صحيح tint, ثابت حرف *str)
{
    صحيح local_use_color;
    إذا (!*str)
        أرجع;

    إذا (use_color < 0)
        check_color_terminal();

    إذا (level == AV_LOG_INFO/8) local_use_color = 0;
    وإلا                        local_use_color = use_color;

#إذا defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    إذا (con != INVALID_HANDLE_قدر) {
        إذا (local_use_color)
            سیٹ_Console_متن_Attribute(con, background | win_color[level]);
        win_console_puts(str);
        إذا (local_use_color)
            سیٹ_Console_متن_Attribute(con, attr_orig);
    } وإلا {
        ansi_fputs(level, tint, str, local_use_color);
    }
#وإلا
    ansi_fputs(level, tint, str, local_use_color);
#جے_انت

}

ثابت حرف *av_default_شے_name(فراغ *ptr)
{
    أرجع (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(فراغ *ptr)
{
    أرجع (*(AVClass **) ptr)->category;
}

ساكن فراغ sanitize(uint8_t *سطر){
    طالما(*سطر){
        إذا(*سطر < 0x08 || (*سطر > 0x0D && *سطر < 0x20))
            *سطر='?';
        سطر++;
    }
}

ساكن صحيح get_category(فراغ *ptr){
    AVClass *avc = *(AVClass **) ptr;
    إذا(    !avc
        || (avc->نسخہ&0xFF)<100
        ||  avc->نسخہ < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) أرجع AV_CLASS_CATEGORY_NA + 16;

    إذا(avc->get_category)
        أرجع avc->get_category(ptr) + 16;

    أرجع avc->category + 16;
}

ساكن ثابت حرف *get_level_str(صحيح level)
{
    بدل (level) {
    حالة AV_LOG_QUIET:
        أرجع "quiet";
    حالة AV_LOG_DEBUG:
        أرجع "debug";
    حالة AV_LOG_TRACE:
        أرجع "trace";
    حالة AV_LOG_VERBOSE:
        أرجع "verbose";
    حالة AV_LOG_INFO:
        أرجع "info";
    حالة AV_LOG_WARNING:
        أرجع "warning";
    حالة AV_LOG_ERROR:
        أرجع "error";
    حالة AV_LOG_FATAL:
        أرجع "fatal";
    حالة AV_LOG_PANIC:
        أرجع "panic";
    افتراضي:
        أرجع "";
    }
}

ساكن ثابت حرف *شے_name(فراغ *obj, ثابت AVClass *cls)
{
    أرجع (cls->شے_name ? cls->شے_name : av_default_شے_name)(obj);
}

ساكن فراغ format_date_now(AVBPrint* bp_ویلا, صحيح include_date)
{
    بنية tm *ptm, tmbuf;
    ثابت int64_t ویلا_us = av_gettime();
    ثابت int64_t ویلا_ms = ویلا_us / 1000;
    ثابت time_t ویلا_s   = ویلا_ms / 1000;
    ثابت صحيح millisec    = ویلا_ms - (ویلا_s * 1000);
    ptm                   = localtime_r(&ویلا_s, &tmbuf);
    إذا (ptm) {
        إذا (include_date)
            av_bprint_strftime(bp_ویلا, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_ویلا, "%H:%M:%S", ptm);
        av_bprintf(bp_ویلا, ".%03d ", millisec);
    }
}

ساكن فراغ format_سطر(فراغ *avcl, صحيح level, ثابت حرف *fmt, va_list vl,
                        AVBPrint part[5], صحيح *print_اگیتر, صحيح type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : عدم;
    av_bprint_init(part+0, 0, AV_BPRINT_ناپ_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_ناپ_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_ناپ_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_ناپ_AUTOMATIC);
    صحيح flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    إذا(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    إذا (*print_اگیتر && avc) {
        إذا (avc->ماپا_log_context_وتھ) {
            AVClass** ماپا = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->ماپا_log_context_وتھ);
            إذا (ماپا && *ماپا) {
                av_bprintf(part+0, "[%s @ %p] ",
                           شے_name(ماپا, *ماپا), ماپا);
                إذا(type) type[0] = get_category(ماپا);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   شے_name(avcl, avc), avcl);
        إذا(type) type[1] = get_category(avcl);
    }

    إذا (*print_اگیتر && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_ویلا | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    إذا (*print_اگیتر && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    إذا(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        حرف lastc = part[3].len && part[3].len <= part[3].ناپ ? part[3].str[part[3].len - 1] : 0;
        *print_اگیتر = lastc == '\n' || lastc == '\r';
    }
}

فراغ av_log_format_سطر(فراغ *ptr, صحيح level, ثابت حرف *fmt, va_list vl,
                        حرف *سطر, صحيح سطر_ناپ, صحيح *print_اگیتر)
{
    av_log_format_line2(ptr, level, fmt, vl, سطر, سطر_ناپ, print_اگیتر);
}

صحيح av_log_format_line2(فراغ *ptr, صحيح level, ثابت حرف *fmt, va_list vl,
                        حرف *سطر, صحيح سطر_ناپ, صحيح *print_اگیتر)
{
    AVBPrint part[5];
    صحيح ret;

    format_سطر(ptr, level, fmt, vl, part, print_اگیتر, عدم);
    ret = snprintf(سطر, سطر_ناپ, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, عدم);
    أرجع ret;
}

فراغ av_log_default_callback(فراغ* ptr, صحيح level, ثابت حرف* fmt, va_list vl)
{
    ساكن صحيح print_اگیتر = 1;
    ساكن صحيح گنتی;
    ساكن حرف prev[سطر_SZ];
    AVBPrint part[5];
    حرف سطر[سطر_SZ];
    ساكن صحيح is_atty;
    صحيح type[2];
    بنانشانی tint = 0;

    إذا (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    إذا (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        أرجع;
    ff_mutex_جندرا(&mutex);

    format_سطر(ptr, level, fmt, vl, part, &print_اگیتر, type);
    snprintf(سطر, حجم(سطر), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#إذا HAVE_ISATTY
    إذا (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#جے_انت

    إذا (print_اگیتر && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(سطر, prev) &&
        *سطر && سطر[لڑی_لمبائی(سطر) - 1] != '\r'){
        گنتی++;
        إذا (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", گنتی);
        اذهب سرا;
    }
    إذا (گنتی > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", گنتی);
        گنتی = 0;
    }
    strcpy(prev, سطر);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_پدھراں - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_پدھراں - 1), tint >> 8, part[3].str);

#إذا CONFIG_VALGRIND_BACKTRACE
    إذا (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#جے_انت
سرا:
    av_bprint_finalize(part+3, عدم);
    ff_mutex_unlock(&mutex);
}

ساكن فراغ (*_Atomic av_log_callback)(فراغ*, صحيح, ثابت حرف*, va_list) = av_log_default_callback;

فراغ av_log(فراغ* avcl, صحيح level, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

فراغ av_log_once(فراغ* avcl, صحيح initial_level, صحيح subsequent_level, صحيح *state, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

فراغ av_vlog(فراغ* avcl, صحيح level, ثابت حرف *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : عدم;
    فراغ (*log_callback)(فراغ*, صحيح, ثابت حرف*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    إذا (avc && avc->نسخہ >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_وتھ_وتھ && level >= AV_LOG_FATAL)
        level += *(صحيح *) (((uint8_t *) avcl) + avc->log_level_وتھ_وتھ);
    إذا (log_callback)
        log_callback(avcl, level, fmt, vl);
}

صحيح av_log_get_level(فراغ)
{
    أرجع atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

فراغ av_log_سیٹ_level(صحيح level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

فراغ av_log_سیٹ_flags(صحيح arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

صحيح av_log_get_flags(فراغ)
{
    أرجع atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

فراغ av_log_سیٹ_callback(فراغ (*callback)(فراغ*, صحيح, ثابت حرف*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ساكن فراغ missing_feature_sample(صحيح sample, فراغ *avc, ثابت حرف *پیغام,
                                   va_list دلیل_list)
{
    av_vlog(avc, AV_LOG_WARNING, پیغام, دلیل_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    إذا (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

فراغ avpriv_request_sample(فراغ *avc, ثابت حرف *پیغام, ...)
{
    va_list دلیل_list;

    va_start(دلیل_list, پیغام);
    missing_feature_sample(1, avc, پیغام, دلیل_list);
    va_end(دلیل_list);
}

فراغ avpriv_report_missing_feature(فراغ *avc, ثابت حرف *پیغام, ...)
{
    va_list دلیل_list;

    va_start(دلیل_list, پیغام);
    missing_feature_sample(0, avc, پیغام, دلیل_list);
    va_end(دلیل_list);
}
