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

#include "config.h"

#အကယ်၍ HAVE_UNISTD_H
#include <unistd.h>
#endif
#အကယ်၍ HAVE_IO_H
#include <io.h>
#endif
#include <inttypes.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bprint.h"
#include "common.h"
#include "internal.h"
#include "log.h"
#include "thread.h"
#include "time.h"
#include "time_internal.h"

static AVMutex mutex = AV_MUTEX_INITIALIZER;

#define LINE_SZ 1024

#အကယ်၍ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#include <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

static atomic_int av_log_level = AV_LOG_INFO;
static atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#အကယ်၍ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#include <windows.h>
static const uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_INPUT           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_INPUT        ] = 5,
};

static int16_t background, attr_orig;
static HANDLE con;
#endif

static const uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_INPUT           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_INPUT        ] = 207 << 8 | 0x05,
};

static ကိန်းပြည့် use_color = -1;

#အကယ်၍ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
static void win_console_puts(const var_na *str)
{
    const uint8_t *q = str;
    uint16_t line[LINE_SZ];

    နေစဉ် (*q) {
        uint16_t *buf = line;
        DWORD nb_chars = 0;
        DWORD written;

        နေစဉ် (*q && nb_chars < LINE_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; goto continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, line, nb_chars, &written, NULL);
    }
}
#endif

static void check_color_terminal(void)
{
    var_na *term = getenv("TERM");

#အကယ်၍ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    အကယ်၍ (con != INVALID_HANDLE_VALUE && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_VALUE;
    အကယ်၍ (con != INVALID_HANDLE_VALUE) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    အကယ်၍ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } မဟုတ်ပါက အကယ်၍ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } မဟုတ်ပါက {
#အကယ်၍ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_VALUE);
#elif HAVE_ISATTY
        use_color = (term && isatty(2));
#မဟုတ်ပါက
        use_color = 0;
#endif
    }

    အကယ်၍ (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

static void ansi_fputs(ကိန်းပြည့် level, ကိန်းပြည့် tint, const var_na *str, ကိန်းပြည့် local_use_color)
{
    အကယ်၍ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#အကယ်၍ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        အကယ်၍ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } မဟုတ်ပါက အကယ်၍ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } မဟုတ်ပါက အကယ်၍ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } မဟုတ်ပါက
        fputs(str, stderr);
}

static void colored_fputs(ကိန်းပြည့် level, ကိန်းပြည့် tint, const var_na *str)
{
    ကိန်းပြည့် local_use_color;
    အကယ်၍ (!*str)
        ပြန်ပေး;

    အကယ်၍ (use_color < 0)
        check_color_terminal();

    အကယ်၍ (level == AV_LOG_INFO/8) local_use_color = 0;
    မဟုတ်ပါက                        local_use_color = use_color;

#အကယ်၍ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    အကယ်၍ (con != INVALID_HANDLE_VALUE) {
        အကယ်၍ (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        အကယ်၍ (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } မဟုတ်ပါက {
        ansi_fputs(level, tint, str, local_use_color);
    }
#မဟုတ်ပါက
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

const var_na *av_default_item_name(void *ptr)
{
    ပြန်ပေး (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(void *ptr)
{
    ပြန်ပေး (*(AVClass **) ptr)->category;
}

static void sanitize(uint8_t *line){
    နေစဉ်(*line){
        အကယ်၍(*line < 0x08 || (*line > 0x0D && *line < 0x20))
            *line='?';
        line++;
    }
}

static ကိန်းပြည့် get_category(void *ptr){
    AVClass *avc = *(AVClass **) ptr;
    အကယ်၍(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) ပြန်ပေး AV_CLASS_CATEGORY_NA + 16;

    အကယ်၍(avc->get_category)
        ပြန်ပေး avc->get_category(ptr) + 16;

    ပြန်ပေး avc->category + 16;
}

static const var_na *get_level_str(ကိန်းပြည့် level)
{
    switch (level) {
    pak_sa AV_LOG_QUIET:
        ပြန်ပေး "quiet";
    pak_sa AV_LOG_DEBUG:
        ပြန်ပေး "debug";
    pak_sa AV_LOG_TRACE:
        ပြန်ပေး "trace";
    pak_sa AV_LOG_VERBOSE:
        ပြန်ပေး "verbose";
    pak_sa AV_LOG_INFO:
        ပြန်ပေး "info";
    pak_sa AV_LOG_WARNING:
        ပြန်ပေး "warning";
    pak_sa AV_LOG_ERROR:
        ပြန်ပေး "error";
    pak_sa AV_LOG_FATAL:
        ပြန်ပေး "fatal";
    pak_sa AV_LOG_PANIC:
        ပြန်ပေး "panic";
    default:
        ပြန်ပေး "";
    }
}

static const var_na *item_name(void *obj, const AVClass *cls)
{
    ပြန်ပေး (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

static void format_date_now(AVBPrint* bp_time, ကိန်းပြည့် include_date)
{
    sa_nracanaa tm *ptm, tmbuf;
    const int64_t time_us = av_gettime();
    const int64_t time_ms = time_us / 1000;
    const time_t time_s   = time_ms / 1000;
    const ကိန်းပြည့် millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    အကယ်၍ (ptm) {
        အကယ်၍ (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

static void format_line(void *avcl, ကိန်းပြည့် level, const var_na *fmt, va_list vl,
                        AVBPrint part[5], ကိန်းပြည့် *print_prefix, ကိန်းပြည့် type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : NULL;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    ကိန်းပြည့် flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    အကယ်၍(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    အကယ်၍ (*print_prefix && avc) {
        အကယ်၍ (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            အကယ်၍ (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                အကယ်၍(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        အကယ်၍(type) type[1] = get_category(avcl);
    }

    အကယ်၍ (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    အကယ်၍ (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    အကယ်၍(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        var_na lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

void av_log_format_line(void *ptr, ကိန်းပြည့် level, const var_na *fmt, va_list vl,
                        var_na *line, ကိန်းပြည့် line_size, ကိန်းပြည့် *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, line, line_size, print_prefix);
}

ကိန်းပြည့် av_log_format_line2(void *ptr, ကိန်းပြည့် level, const var_na *fmt, va_list vl,
                        var_na *line, ကိန်းပြည့် line_size, ကိန်းပြည့် *print_prefix)
{
    AVBPrint part[5];
    ကိန်းပြည့် ret;

    format_line(ptr, level, fmt, vl, part, print_prefix, NULL);
    ret = snprintf(line, line_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, NULL);
    ပြန်ပေး ret;
}

void av_log_default_callback(void* ptr, ကိန်းပြည့် level, const var_na* fmt, va_list vl)
{
    static ကိန်းပြည့် print_prefix = 1;
    static ကိန်းပြည့် count;
    static var_na prev[LINE_SZ];
    AVBPrint part[5];
    var_na line[LINE_SZ];
    static ကိန်းပြည့် is_atty;
    ကိန်းပြည့် type[2];
    unsigned tint = 0;

    အကယ်၍ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    အကယ်၍ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        ပြန်ပေး;
    ff_mutex_lock(&mutex);

    format_line(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(line, parimaa_na(line), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#အကယ်၍ HAVE_ISATTY
    အကယ်၍ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    အကယ်၍ (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(line, prev) &&
        *line && line[strlen(line) - 1] != '\r'){
        count++;
        အကယ်၍ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", count);
        goto end;
    }
    အကယ်၍ (count > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", count);
        count = 0;
    }
    strcpy(prev, line);

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

#အကယ်၍ CONFIG_VALGRIND_BACKTRACE
    အကယ်၍ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, NULL);
    ff_mutex_unlock(&mutex);
}

static void (*_Atomic av_log_callback)(void*, ကိန်းပြည့်, const var_na*, va_list) = av_log_default_callback;

void av_log(void* avcl, ကိန်းပြည့် level, const var_na *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

void av_log_once(void* avcl, ကိန်းပြည့် initial_level, ကိန်းပြည့် subsequent_level, ကိန်းပြည့် *state, const var_na *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

void av_vlog(void* avcl, ကိန်းပြည့် level, const var_na *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : NULL;
    void (*log_callback)(void*, ကိန်းပြည့်, const var_na*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    အကယ်၍ (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(ကိန်းပြည့် *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    အကယ်၍ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

ကိန်းပြည့် av_log_get_level(void)
{
    ပြန်ပေး atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

void av_log_set_level(ကိန်းပြည့် level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

void av_log_set_flags(ကိန်းပြည့် arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

ကိန်းပြည့် av_log_get_flags(void)
{
    ပြန်ပေး atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

void av_log_set_callback(void (*callback)(void*, ကိန်းပြည့်, const var_na*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

static void missing_feature_sample(ကိန်းပြည့် sample, void *avc, const var_na *msg,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, msg, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    အကယ်၍ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

void avpriv_request_sample(void *avc, const var_na *msg, ...)
{
    va_list argument_list;

    va_start(argument_list, msg);
    missing_feature_sample(1, avc, msg, argument_list);
    va_end(argument_list);
}

void avpriv_report_missing_feature(void *avc, const var_na *msg, ...)
{
    va_list argument_list;

    va_start(argument_list, msg);
    missing_feature_sample(0, avc, msg, argument_list);
    va_end(argument_list);
}
