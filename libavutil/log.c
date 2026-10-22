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

#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_IO_H
#అన్తర్భావ <io.h>
#అయితే_ముగింపు
#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "bprint.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "internal.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "thread.h"
#అన్తర్భావ "time.h"
#అన్తర్భావ "time_internal.h"

స్థిర AVMutex mutex = AV_MUTEX_INITIALIZER;

#నిర్వచించు పంక్తి_SZ 1024

#ఒకవేళ HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#అన్తర్భావ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#నిర్వచించు BACKTRACE_LOGLEVEL AV_LOG_ERROR
#అయితే_ముగింపు

స్థిర atomic_int av_log_level = AV_LOG_INFO;
స్థిర atomic_int av_log_flags = 0;

#నిర్వచించు NB_స్థాయిలు 8
#ఒకవేళ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#అన్తర్భావ <windows.h>
స్థిర స్థిరరాశి uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_ఆదానం           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ఆదానం  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ఆదానం  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_ఆదానం        ] = 5,
};

స్థిర int16_t background, attr_orig;
స్థిర HANDLE con;
#అయితే_ముగింపు

స్థిర స్థిరరాశి uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_ఆదానం           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_ఆదానం  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_ఆదానం  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_ఆదానం        ] = 207 << 8 | 0x05,
};

స్థిర పూర్ణాంకం use_color = -1;

#ఒకవేళ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
స్థిర శూన్య win_console_puts(స్థిరరాశి అక్షరం *str)
{
    స్థిరరాశి uint8_t *q = str;
    uint16_t పంక్తి[పంక్తి_SZ];

    అయితే (*q) {
        uint16_t *buf = పంక్తి;
        DWORD nb_chars = 0;
        DWORD written;

        అయితే (*q && nb_chars < పంక్తి_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; వెళ్ళు continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, పంక్తి, nb_chars, &written, ఖాళీ);
    }
}
#అయితే_ముగింపు

స్థిర శూన్య check_color_terminal(శూన్య)
{
    అక్షరం *పదం = getenv("TERM");

#ఒకవేళ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_బఫరు_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    ఒకవేళ (con != INVALID_HANDLE_విలువ && !Get_Console_బహుళకం(con, &dummy))
        con = INVALID_HANDLE_విలువ;
    ఒకవేళ (con != INVALID_HANDLE_విలువ) {
        Get_Console_Screen_బఫరు_Info(con, &con_info);
        attr_orig  = con_info.w_లక్షణాలు;
        background = attr_orig & 0xF0;
    }
#అయితే_ముగింపు

    ఒకవేళ (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } లేకపోతే ఒకవేళ (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } లేకపోతే {
#ఒకవేళ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_విలువ);
#లేదావేళ HAVE_ISATTY
        use_color = (పదం && isatty(2));
#లేకపోతే
        use_color = 0;
#అయితే_ముగింపు
    }

    ఒకవేళ (getenv("AV_LOG_FORCE_256COLOR") || పదం && అక్షరశ్రేణి_శోధన(పదం, "256color"))
        use_color *= 256;
}

స్థిర శూన్య ansi_fputs(పూర్ణాంకం level, పూర్ణాంకం tint, స్థిరరాశి అక్షరం *str, పూర్ణాంకం local_use_color)
{
    ఒకవేళ (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#ఒకవేళ defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        ఒకవేళ (level == AV_LOG_WARNING / 8)
            intensity = 1;
#అయితే_ముగింపు
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } లేకపోతే ఒకవేళ (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } లేకపోతే ఒకవేళ (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } లేకపోతే
        fputs(str, stderr);
}

స్థిర శూన్య colored_fputs(పూర్ణాంకం level, పూర్ణాంకం tint, స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం local_use_color;
    ఒకవేళ (!*str)
        తిరిగి;

    ఒకవేళ (use_color < 0)
        check_color_terminal();

    ఒకవేళ (level == AV_LOG_INFO/8) local_use_color = 0;
    లేకపోతే                        local_use_color = use_color;

#ఒకవేళ defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    ఒకవేళ (con != INVALID_HANDLE_విలువ) {
        ఒకవేళ (local_use_color)
            సమితి_Console_పాఠ్యం_Attribute(con, background | win_color[level]);
        win_console_puts(str);
        ఒకవేళ (local_use_color)
            సమితి_Console_పాఠ్యం_Attribute(con, attr_orig);
    } లేకపోతే {
        ansi_fputs(level, tint, str, local_use_color);
    }
#లేకపోతే
    ansi_fputs(level, tint, str, local_use_color);
#అయితే_ముగింపు

}

స్థిరరాశి అక్షరం *av_default_అంశం_name(శూన్య *ptr)
{
    తిరిగి (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(శూన్య *ptr)
{
    తిరిగి (*(AVClass **) ptr)->category;
}

స్థిర శూన్య sanitize(uint8_t *పంక్తి){
    అయితే(*పంక్తి){
        ఒకవేళ(*పంక్తి < 0x08 || (*పంక్తి > 0x0D && *పంక్తి < 0x20))
            *పంక్తి='?';
        పంక్తి++;
    }
}

స్థిర పూర్ణాంకం get_category(శూన్య *ptr){
    AVClass *avc = *(AVClass **) ptr;
    ఒకవేళ(    !avc
        || (avc->సంస్కరణ&0xFF)<100
        ||  avc->సంస్కరణ < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) తిరిగి AV_CLASS_CATEGORY_NA + 16;

    ఒకవేళ(avc->get_category)
        తిరిగి avc->get_category(ptr) + 16;

    తిరిగి avc->category + 16;
}

స్థిర స్థిరరాశి అక్షరం *get_level_str(పూర్ణాంకం level)
{
    ఎంపిక (level) {
    స్థితి AV_LOG_QUIET:
        తిరిగి "quiet";
    స్థితి AV_LOG_DEBUG:
        తిరిగి "debug";
    స్థితి AV_LOG_TRACE:
        తిరిగి "trace";
    స్థితి AV_LOG_VERBOSE:
        తిరిగి "verbose";
    స్థితి AV_LOG_INFO:
        తిరిగి "info";
    స్థితి AV_LOG_WARNING:
        తిరిగి "warning";
    స్థితి AV_LOG_ERROR:
        తిరిగి "error";
    స్థితి AV_LOG_FATAL:
        తిరిగి "fatal";
    స్థితి AV_LOG_PANIC:
        తిరిగి "panic";
    అప్రమేయ:
        తిరిగి "";
    }
}

స్థిర స్థిరరాశి అక్షరం *అంశం_name(శూన్య *obj, స్థిరరాశి AVClass *cls)
{
    తిరిగి (cls->అంశం_name ? cls->అంశం_name : av_default_అంశం_name)(obj);
}

స్థిర శూన్య format_date_now(AVBPrint* bp_సమయం, పూర్ణాంకం include_date)
{
    నిర్మాణం tm *ptm, tmbuf;
    స్థిరరాశి int64_t సమయం_us = av_gettime();
    స్థిరరాశి int64_t సమయం_ms = సమయం_us / 1000;
    స్థిరరాశి time_t సమయం_s   = సమయం_ms / 1000;
    స్థిరరాశి పూర్ణాంకం millisec    = సమయం_ms - (సమయం_s * 1000);
    ptm                   = localtime_r(&సమయం_s, &tmbuf);
    ఒకవేళ (ptm) {
        ఒకవేళ (include_date)
            av_bprint_strftime(bp_సమయం, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_సమయం, "%H:%M:%S", ptm);
        av_bprintf(bp_సమయం, ".%03d ", millisec);
    }
}

స్థిర శూన్య format_పంక్తి(శూన్య *avcl, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list vl,
                        AVBPrint part[5], పూర్ణాంకం *print_ఉపసర్గ, పూర్ణాంకం type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ఖాళీ;
    av_bprint_init(part+0, 0, AV_BPRINT_కొలత_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_కొలత_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_కొలత_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_కొలత_AUTOMATIC);
    పూర్ణాంకం flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    ఒకవేళ(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    ఒకవేళ (*print_ఉపసర్గ && avc) {
        ఒకవేళ (avc->మాతృ_log_context_స్థానభ్రంశం) {
            AVClass** మాతృ = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->మాతృ_log_context_స్థానభ్రంశం);
            ఒకవేళ (మాతృ && *మాతృ) {
                av_bprintf(part+0, "[%s @ %p] ",
                           అంశం_name(మాతృ, *మాతృ), మాతృ);
                ఒకవేళ(type) type[0] = get_category(మాతృ);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   అంశం_name(avcl, avc), avcl);
        ఒకవేళ(type) type[1] = get_category(avcl);
    }

    ఒకవేళ (*print_ఉపసర్గ && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_సమయం | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    ఒకవేళ (*print_ఉపసర్గ && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    ఒకవేళ(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        అక్షరం lastc = part[3].len && part[3].len <= part[3].కొలత ? part[3].str[part[3].len - 1] : 0;
        *print_ఉపసర్గ = lastc == '\n' || lastc == '\r';
    }
}

శూన్య av_log_format_పంక్తి(శూన్య *ptr, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list vl,
                        అక్షరం *పంక్తి, పూర్ణాంకం పంక్తి_కొలత, పూర్ణాంకం *print_ఉపసర్గ)
{
    av_log_format_line2(ptr, level, fmt, vl, పంక్తి, పంక్తి_కొలత, print_ఉపసర్గ);
}

పూర్ణాంకం av_log_format_line2(శూన్య *ptr, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list vl,
                        అక్షరం *పంక్తి, పూర్ణాంకం పంక్తి_కొలత, పూర్ణాంకం *print_ఉపసర్గ)
{
    AVBPrint part[5];
    పూర్ణాంకం ret;

    format_పంక్తి(ptr, level, fmt, vl, part, print_ఉపసర్గ, ఖాళీ);
    ret = snprintf(పంక్తి, పంక్తి_కొలత, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, ఖాళీ);
    తిరిగి ret;
}

శూన్య av_log_default_callback(శూన్య* ptr, పూర్ణాంకం level, స్థిరరాశి అక్షరం* fmt, va_list vl)
{
    స్థిర పూర్ణాంకం print_ఉపసర్గ = 1;
    స్థిర పూర్ణాంకం లెక్క;
    స్థిర అక్షరం prev[పంక్తి_SZ];
    AVBPrint part[5];
    అక్షరం పంక్తి[పంక్తి_SZ];
    స్థిర పూర్ణాంకం is_atty;
    పూర్ణాంకం type[2];
    గుర్తులేని tint = 0;

    ఒకవేళ (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    ఒకవేళ (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        తిరిగి;
    ff_mutex_తాళం(&mutex);

    format_పంక్తి(ptr, level, fmt, vl, part, &print_ఉపసర్గ, type);
    snprintf(పంక్తి, పరిమాణం(పంక్తి), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#ఒకవేళ HAVE_ISATTY
    ఒకవేళ (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#అయితే_ముగింపు

    ఒకవేళ (print_ఉపసర్గ && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(పంక్తి, prev) &&
        *పంక్తి && పంక్తి[అక్షరశ్రేణి_పొడవు(పంక్తి) - 1] != '\r'){
        లెక్క++;
        ఒకవేళ (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", లెక్క);
        వెళ్ళు చివర;
    }
    ఒకవేళ (లెక్క > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", లెక్క);
        లెక్క = 0;
    }
    strcpy(prev, పంక్తి);

    sanitize(part[4].str);
    colored_fputs(7, 0, part[4].str);
    sanitize(part[0].str);
    colored_fputs(type[0], 0, part[0].str);
    sanitize(part[1].str);
    colored_fputs(type[1], 0, part[1].str);
    sanitize(part[2].str);
    colored_fputs(av_clip(level >> 3, 0, NB_స్థాయిలు - 1), tint >> 8, part[2].str);
    sanitize(part[3].str);
    colored_fputs(av_clip(level >> 3, 0, NB_స్థాయిలు - 1), tint >> 8, part[3].str);

#ఒకవేళ CONFIG_VALGRIND_BACKTRACE
    ఒకవేళ (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#అయితే_ముగింపు
చివర:
    av_bprint_finalize(part+3, ఖాళీ);
    ff_mutex_unlock(&mutex);
}

స్థిర శూన్య (*_Atomic av_log_callback)(శూన్య*, పూర్ణాంకం, స్థిరరాశి అక్షరం*, va_list) = av_log_default_callback;

శూన్య av_log(శూన్య* avcl, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

శూన్య av_log_once(శూన్య* avcl, పూర్ణాంకం initial_level, పూర్ణాంకం subsequent_level, పూర్ణాంకం *state, స్థిరరాశి అక్షరం *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

శూన్య av_vlog(శూన్య* avcl, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : ఖాళీ;
    శూన్య (*log_callback)(శూన్య*, పూర్ణాంకం, స్థిరరాశి అక్షరం*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    ఒకవేళ (avc && avc->సంస్కరణ >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_స్థానభ్రంశం_స్థానభ్రంశం && level >= AV_LOG_FATAL)
        level += *(పూర్ణాంకం *) (((uint8_t *) avcl) + avc->log_level_స్థానభ్రంశం_స్థానభ్రంశం);
    ఒకవేళ (log_callback)
        log_callback(avcl, level, fmt, vl);
}

పూర్ణాంకం av_log_get_level(శూన్య)
{
    తిరిగి atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

శూన్య av_log_సమితి_level(పూర్ణాంకం level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

శూన్య av_log_సమితి_flags(పూర్ణాంకం arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

పూర్ణాంకం av_log_get_flags(శూన్య)
{
    తిరిగి atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

శూన్య av_log_సమితి_callback(శూన్య (*callback)(శూన్య*, పూర్ణాంకం, స్థిరరాశి అక్షరం*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

స్థిర శూన్య missing_feature_sample(పూర్ణాంకం sample, శూన్య *avc, స్థిరరాశి అక్షరం *సందేశం,
                                   va_list వాదం_list)
{
    av_vlog(avc, AV_LOG_WARNING, సందేశం, వాదం_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    ఒకవేళ (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

శూన్య avpriv_request_sample(శూన్య *avc, స్థిరరాశి అక్షరం *సందేశం, ...)
{
    va_list వాదం_list;

    va_start(వాదం_list, సందేశం);
    missing_feature_sample(1, avc, సందేశం, వాదం_list);
    va_end(వాదం_list);
}

శూన్య avpriv_report_missing_feature(శూన్య *avc, స్థిరరాశి అక్షరం *సందేశం, ...)
{
    va_list వాదం_list;

    va_start(వాదం_list, సందేశం);
    missing_feature_sample(0, avc, సందేశం, వాదం_list);
    va_end(వాదం_list);
}
