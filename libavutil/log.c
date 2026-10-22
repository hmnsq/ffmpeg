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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ଯଦି HAVE_IO_H
#ଅନ୍ତର୍ଭାଵ <io.h>
#endif
#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ "bprint.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "internal.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"
#ଅନ୍ତର୍ଭାଵ "time.h"
#ଅନ୍ତର୍ଭାଵ "time_internal.h"

ସ୍ଥିର AVMutex mutex = AV_MUTEX_INITIALIZER;

#define ଧାଡ଼ି_SZ 1024

#ଯଦି HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#ଅନ୍ତର୍ଭାଵ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

ସ୍ଥିର atomic_int av_log_level = AV_LOG_INFO;
ସ୍ଥିର atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#ଯଦି defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#ଅନ୍ତର୍ଭାଵ <windows.h>
ସ୍ଥିର ଅଚଳ uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_ନିବେଶ           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ନିବେଶ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ନିବେଶ  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_ନିବେଶ        ] = 5,
};

ସ୍ଥିର int16_t background, attr_orig;
ସ୍ଥିର HANDLE con;
#endif

ସ୍ଥିର ଅଚଳ uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_ନିବେଶ           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ନିବେଶ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ନିବେଶ  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_ନିବେଶ        ] = 207 << 8 | 0x05,
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_color = -1;

#ଯଦି defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
ସ୍ଥିର ଶୂନ୍ୟ win_console_puts(ଅଚଳ ଅକ୍ଷର *str)
{
    ଅଚଳ uint8_t *q = str;
    uint16_t ଧାଡ଼ି[ଧାଡ଼ି_SZ];

    ଯେତେବେଳେ (*q) {
        uint16_t *buf = ଧାଡ଼ି;
        DWORD nb_chars = 0;
        DWORD written;

        ଯେତେବେଳେ (*q && nb_chars < ଧାଡ଼ି_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; ଯାଅ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ଧାଡ଼ି, nb_chars, &written, ଖାଲି);
    }
}
#endif

ସ୍ଥିର ଶୂନ୍ୟ check_color_terminal(ଶୂନ୍ୟ)
{
    ଅକ୍ଷର *term = getenv("TERM");

#ଯଦି defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    ଯଦି (con != INVALID_HANDLE_ମୂଲ୍ୟ && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_ମୂଲ୍ୟ;
    ଯଦି (con != INVALID_HANDLE_ମୂଲ୍ୟ) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    ଯଦି (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } ଅନ୍ୟଥା ଯଦି (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } ଅନ୍ୟଥା {
#ଯଦି defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_ମୂଲ୍ୟ);
#ନଚେତଯଦି HAVE_ISATTY
        use_color = (term && isatty(2));
#ଅନ୍ୟଥା
        use_color = 0;
#endif
    }

    ଯଦି (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

ସ୍ଥିର ଶୂନ୍ୟ ansi_fputs(ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ପୂର୍ଣ୍ଣସଂଖ୍ୟା tint, ଅଚଳ ଅକ୍ଷର *str, ପୂର୍ଣ୍ଣସଂଖ୍ୟା local_use_color)
{
    ଯଦି (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#ଯଦି defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        ଯଦି (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } ଅନ୍ୟଥା ଯଦି (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } ଅନ୍ୟଥା ଯଦି (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } ଅନ୍ୟଥା
        fputs(str, stderr);
}

ସ୍ଥିର ଶୂନ୍ୟ colored_fputs(ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ପୂର୍ଣ୍ଣସଂଖ୍ୟା tint, ଅଚଳ ଅକ୍ଷର *str)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା local_use_color;
    ଯଦି (!*str)
        ଫେରନ୍ତୁ;

    ଯଦି (use_color < 0)
        check_color_terminal();

    ଯଦି (level == AV_LOG_INFO/8) local_use_color = 0;
    ଅନ୍ୟଥା                        local_use_color = use_color;

#ଯଦି defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    ଯଦି (con != INVALID_HANDLE_ମୂଲ୍ୟ) {
        ଯଦି (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        ଯଦି (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } ଅନ୍ୟଥା {
        ansi_fputs(level, tint, str, local_use_color);
    }
#ଅନ୍ୟଥା
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ଅଚଳ ଅକ୍ଷର *av_default_item_name(ଶୂନ୍ୟ *ptr)
{
    ଫେରନ୍ତୁ (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(ଶୂନ୍ୟ *ptr)
{
    ଫେରନ୍ତୁ (*(AVClass **) ptr)->category;
}

ସ୍ଥିର ଶୂନ୍ୟ sanitize(uint8_t *ଧାଡ଼ି){
    ଯେତେବେଳେ(*ଧାଡ଼ି){
        ଯଦି(*ଧାଡ଼ି < 0x08 || (*ଧାଡ଼ି > 0x0D && *ଧାଡ଼ି < 0x20))
            *ଧାଡ଼ି='?';
        ଧାଡ଼ି++;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_category(ଶୂନ୍ୟ *ptr){
    AVClass *avc = *(AVClass **) ptr;
    ଯଦି(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) ଫେରନ୍ତୁ AV_CLASS_CATEGORY_NA + 16;

    ଯଦି(avc->get_category)
        ଫେରନ୍ତୁ avc->get_category(ptr) + 16;

    ଫେରନ୍ତୁ avc->category + 16;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *get_level_str(ପୂର୍ଣ୍ଣସଂଖ୍ୟା level)
{
    ବାଛ (level) {
    ସ୍ଥିତି AV_LOG_QUIET:
        ଫେରନ୍ତୁ "quiet";
    ସ୍ଥିତି AV_LOG_DEBUG:
        ଫେରନ୍ତୁ "debug";
    ସ୍ଥିତି AV_LOG_TRACE:
        ଫେରନ୍ତୁ "trace";
    ସ୍ଥିତି AV_LOG_VERBOSE:
        ଫେରନ୍ତୁ "verbose";
    ସ୍ଥିତି AV_LOG_INFO:
        ଫେରନ୍ତୁ "info";
    ସ୍ଥିତି AV_LOG_WARNING:
        ଫେରନ୍ତୁ "warning";
    ସ୍ଥିତି AV_LOG_ERROR:
        ଫେରନ୍ତୁ "error";
    ସ୍ଥିତି AV_LOG_FATAL:
        ଫେରନ୍ତୁ "fatal";
    ସ୍ଥିତି AV_LOG_PANIC:
        ଫେରନ୍ତୁ "panic";
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ "";
    }
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *item_name(ଶୂନ୍ୟ *obj, ଅଚଳ AVClass *cls)
{
    ଫେରନ୍ତୁ (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

ସ୍ଥିର ଶୂନ୍ୟ format_date_now(AVBPrint* bp_time, ପୂର୍ଣ୍ଣସଂଖ୍ୟା include_date)
{
    ସଂରଚନା tm *ptm, tmbuf;
    ଅଚଳ int64_t time_us = av_gettime();
    ଅଚଳ int64_t time_ms = time_us / 1000;
    ଅଚଳ time_t time_s   = time_ms / 1000;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    ଯଦି (ptm) {
        ଯଦି (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ format_ଧାଡ଼ି(ଶୂନ୍ୟ *avcl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, va_list vl,
                        AVBPrint part[5], ପୂର୍ଣ୍ଣସଂଖ୍ୟା *print_prefix, ପୂର୍ଣ୍ଣସଂଖ୍ୟା type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ଖାଲି;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    ଯଦି(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    ଯଦି (*print_prefix && avc) {
        ଯଦି (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            ଯଦି (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                ଯଦି(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        ଯଦି(type) type[1] = get_category(avcl);
    }

    ଯଦି (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    ଯଦି (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    ଯଦି(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        ଅକ୍ଷର lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

ଶୂନ୍ୟ av_log_format_ଧାଡ଼ି(ଶୂନ୍ୟ *ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, va_list vl,
                        ଅକ୍ଷର *ଧାଡ଼ି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଧାଡ଼ି_size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, ଧାଡ଼ି, ଧାଡ଼ି_size, print_prefix);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_log_format_line2(ଶୂନ୍ୟ *ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, va_list vl,
                        ଅକ୍ଷର *ଧାଡ଼ି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଧାଡ଼ି_size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *print_prefix)
{
    AVBPrint part[5];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    format_ଧାଡ଼ି(ptr, level, fmt, vl, part, print_prefix, ଖାଲି);
    ret = snprintf(ଧାଡ଼ି, ଧାଡ଼ି_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ଖାଲି);
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ av_log_default_callback(ଶୂନ୍ୟ* ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର* fmt, va_list vl)
{
    ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା print_prefix = 1;
    ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;
    ସ୍ଥିର ଅକ୍ଷର prev[ଧାଡ଼ି_SZ];
    AVBPrint part[5];
    ଅକ୍ଷର ଧାଡ଼ି[ଧାଡ଼ି_SZ];
    ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_atty;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା type[2];
    unsigned tint = 0;

    ଯଦି (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    ଯଦି (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        ଫେରନ୍ତୁ;
    ff_mutex_lock(&mutex);

    format_ଧାଡ଼ି(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(ଧାଡ଼ି, ଆକାର(ଧାଡ଼ି), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#ଯଦି HAVE_ISATTY
    ଯଦି (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    ଯଦି (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(ଧାଡ଼ି, prev) &&
        *ଧାଡ଼ି && ଧାଡ଼ି[strlen(ଧାଡ଼ି) - 1] != '\r'){
        ଗଣନା_2++;
        ଯଦି (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", ଗଣନା_2);
        ଯାଅ end;
    }
    ଯଦି (ଗଣନା_2 > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", ଗଣନା_2);
        ଗଣନା_2 = 0;
    }
    strcpy(prev, ଧାଡ଼ି);

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

#ଯଦି CONFIG_VALGRIND_BACKTRACE
    ଯଦି (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, ଖାଲି);
    ff_mutex_unlock(&mutex);
}

ସ୍ଥିର ଶୂନ୍ୟ (*_Atomic av_log_callback)(ଶୂନ୍ୟ*, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅଚଳ ଅକ୍ଷର*, va_list) = av_log_default_callback;

ଶୂନ୍ୟ av_log(ଶୂନ୍ୟ* avcl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

ଶୂନ୍ୟ av_log_once(ଶୂନ୍ୟ* avcl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା initial_level, ପୂର୍ଣ୍ଣସଂଖ୍ୟା subsequent_level, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *state, ଅଚଳ ଅକ୍ଷର *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

ଶୂନ୍ୟ av_vlog(ଶୂନ୍ୟ* avcl, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ଖାଲି;
    ଶୂନ୍ୟ (*log_callback)(ଶୂନ୍ୟ*, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅଚଳ ଅକ୍ଷର*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    ଯଦି (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    ଯଦି (log_callback)
        log_callback(avcl, level, fmt, vl);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_log_get_level(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

ଶୂନ୍ୟ av_log_set_level(ପୂର୍ଣ୍ଣସଂଖ୍ୟା level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

ଶୂନ୍ୟ av_log_set_flags(ପୂର୍ଣ୍ଣସଂଖ୍ୟା arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_log_get_flags(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

ଶୂନ୍ୟ av_log_set_callback(ଶୂନ୍ୟ (*callback)(ଶୂନ୍ୟ*, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅଚଳ ଅକ୍ଷର*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

ସ୍ଥିର ଶୂନ୍ୟ missing_feature_sample(ପୂର୍ଣ୍ଣସଂଖ୍ୟା sample, ଶୂନ୍ୟ *avc, ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, ସନ୍ଦେଶ, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    ଯଦି (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

ଶୂନ୍ୟ avpriv_request_sample(ଶୂନ୍ୟ *avc, ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ, ...)
{
    va_list argument_list;

    va_start(argument_list, ସନ୍ଦେଶ);
    missing_feature_sample(1, avc, ସନ୍ଦେଶ, argument_list);
    va_end(argument_list);
}

ଶୂନ୍ୟ avpriv_report_missing_feature(ଶୂନ୍ୟ *avc, ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ, ...)
{
    va_list argument_list;

    va_start(argument_list, ସନ୍ଦେଶ);
    missing_feature_sample(0, avc, ସନ୍ଦେଶ, argument_list);
    va_end(argument_list);
}
