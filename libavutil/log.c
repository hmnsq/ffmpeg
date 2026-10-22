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

#अन्तर्भाव "config.h"

#यदि HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#यदि HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "bprint.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "thread.h"
#अन्तर्भाव "time.h"
#अन्तर्भाव "time_internal.h"

स्थिर AVMutex mutex = AV_MUTEX_INITIALIZER;

#define ओळ_SZ 1024

#यदि HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#अन्तर्भाव <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

स्थिर atomic_int av_log_level = AV_LOG_INFO;
स्थिर atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#यदि defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#अन्तर्भाव <windows.h>
स्थिर ध्रुव uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_आदान           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_आदान  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_आदान  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_आदान        ] = 5,
};

स्थिर int16_t background, attr_orig;
स्थिर HANDLE con;
#endif

स्थिर ध्रुव uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_आदान           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_आदान  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_आदान  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_आदान        ] = 207 << 8 | 0x05,
};

स्थिर पूर्णाङ्क use_color = -1;

#यदि defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
स्थिर शून्य win_console_puts(ध्रुव वर्ण *str)
{
    ध्रुव uint8_t *q = str;
    uint16_t ओळ[ओळ_SZ];

    यावत् (*q) {
        uint16_t *buf = ओळ;
        DWORD nb_chars = 0;
        DWORD written;

        यावत् (*q && nb_chars < ओळ_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; गच्छ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ओळ, nb_chars, &written, रिक्त);
    }
}
#endif

स्थिर शून्य check_color_terminal(शून्य)
{
    वर्ण *term = getenv("TERM");

#यदि defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    यदि (con != INVALID_HANDLE_मूल्य && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_मूल्य;
    यदि (con != INVALID_HANDLE_मूल्य) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    यदि (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } अन्यथा यदि (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } अन्यथा {
#यदि defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_मूल्य);
#नोचेद्यदि HAVE_ISATTY
        use_color = (term && isatty(2));
#अन्यथा
        use_color = 0;
#endif
    }

    यदि (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

स्थिर शून्य ansi_fputs(पूर्णाङ्क level, पूर्णाङ्क tint, ध्रुव वर्ण *str, पूर्णाङ्क local_use_color)
{
    यदि (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#यदि defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        यदि (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } अन्यथा यदि (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } अन्यथा यदि (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } अन्यथा
        fputs(str, stderr);
}

स्थिर शून्य colored_fputs(पूर्णाङ्क level, पूर्णाङ्क tint, ध्रुव वर्ण *str)
{
    पूर्णाङ्क local_use_color;
    यदि (!*str)
        प्रत्यागम;

    यदि (use_color < 0)
        check_color_terminal();

    यदि (level == AV_LOG_INFO/8) local_use_color = 0;
    अन्यथा                        local_use_color = use_color;

#यदि defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    यदि (con != INVALID_HANDLE_मूल्य) {
        यदि (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        यदि (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } अन्यथा {
        ansi_fputs(level, tint, str, local_use_color);
    }
#अन्यथा
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ध्रुव वर्ण *av_default_item_name(शून्य *ptr)
{
    प्रत्यागम (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(शून्य *ptr)
{
    प्रत्यागम (*(AVClass **) ptr)->category;
}

स्थिर शून्य sanitize(uint8_t *ओळ){
    यावत्(*ओळ){
        यदि(*ओळ < 0x08 || (*ओळ > 0x0D && *ओळ < 0x20))
            *ओळ='?';
        ओळ++;
    }
}

स्थिर पूर्णाङ्क get_category(शून्य *ptr){
    AVClass *avc = *(AVClass **) ptr;
    यदि(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) प्रत्यागम AV_CLASS_CATEGORY_NA + 16;

    यदि(avc->get_category)
        प्रत्यागम avc->get_category(ptr) + 16;

    प्रत्यागम avc->category + 16;
}

स्थिर ध्रुव वर्ण *get_level_str(पूर्णाङ्क level)
{
    विकल्प (level) {
    पक्ष AV_LOG_QUIET:
        प्रत्यागम "quiet";
    पक्ष AV_LOG_DEBUG:
        प्रत्यागम "debug";
    पक्ष AV_LOG_TRACE:
        प्रत्यागम "trace";
    पक्ष AV_LOG_VERBOSE:
        प्रत्यागम "verbose";
    पक्ष AV_LOG_INFO:
        प्रत्यागम "info";
    पक्ष AV_LOG_WARNING:
        प्रत्यागम "warning";
    पक्ष AV_LOG_ERROR:
        प्रत्यागम "error";
    पक्ष AV_LOG_FATAL:
        प्रत्यागम "fatal";
    पक्ष AV_LOG_PANIC:
        प्रत्यागम "panic";
    स्वभाव:
        प्रत्यागम "";
    }
}

स्थिर ध्रुव वर्ण *item_name(शून्य *obj, ध्रुव AVClass *cls)
{
    प्रत्यागम (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

स्थिर शून्य format_date_now(AVBPrint* bp_time, पूर्णाङ्क include_date)
{
    संरचना tm *ptm, tmbuf;
    ध्रुव int64_t time_us = av_gettime();
    ध्रुव int64_t time_ms = time_us / 1000;
    ध्रुव time_t time_s   = time_ms / 1000;
    ध्रुव पूर्णाङ्क millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    यदि (ptm) {
        यदि (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

स्थिर शून्य format_ओळ(शून्य *avcl, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        AVBPrint part[5], पूर्णाङ्क *print_prefix, पूर्णाङ्क type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : रिक्त;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    पूर्णाङ्क flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    यदि(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    यदि (*print_prefix && avc) {
        यदि (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            यदि (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                यदि(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        यदि(type) type[1] = get_category(avcl);
    }

    यदि (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    यदि (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    यदि(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        वर्ण lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

शून्य av_log_format_ओळ(शून्य *ptr, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        वर्ण *ओळ, पूर्णाङ्क ओळ_size, पूर्णाङ्क *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, ओळ, ओळ_size, print_prefix);
}

पूर्णाङ्क av_log_format_line2(शून्य *ptr, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        वर्ण *ओळ, पूर्णाङ्क ओळ_size, पूर्णाङ्क *print_prefix)
{
    AVBPrint part[5];
    पूर्णाङ्क ret;

    format_ओळ(ptr, level, fmt, vl, part, print_prefix, रिक्त);
    ret = snprintf(ओळ, ओळ_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, रिक्त);
    प्रत्यागम ret;
}

शून्य av_log_default_callback(शून्य* ptr, पूर्णाङ्क level, ध्रुव वर्ण* fmt, va_list vl)
{
    स्थिर पूर्णाङ्क print_prefix = 1;
    स्थिर पूर्णाङ्क मोजणी;
    स्थिर वर्ण prev[ओळ_SZ];
    AVBPrint part[5];
    वर्ण ओळ[ओळ_SZ];
    स्थिर पूर्णाङ्क is_atty;
    पूर्णाङ्क type[2];
    unsigned tint = 0;

    यदि (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    यदि (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        प्रत्यागम;
    ff_mutex_lock(&mutex);

    format_ओळ(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(ओळ, परिमाण(ओळ), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#यदि HAVE_ISATTY
    यदि (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    यदि (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(ओळ, prev) &&
        *ओळ && ओळ[strlen(ओळ) - 1] != '\r'){
        मोजणी++;
        यदि (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", मोजणी);
        गच्छ end;
    }
    यदि (मोजणी > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", मोजणी);
        मोजणी = 0;
    }
    strcpy(prev, ओळ);

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

#यदि CONFIG_VALGRIND_BACKTRACE
    यदि (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, रिक्त);
    ff_mutex_unlock(&mutex);
}

स्थिर शून्य (*_Atomic av_log_callback)(शून्य*, पूर्णाङ्क, ध्रुव वर्ण*, va_list) = av_log_default_callback;

शून्य av_log(शून्य* avcl, पूर्णाङ्क level, ध्रुव वर्ण *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

शून्य av_log_once(शून्य* avcl, पूर्णाङ्क initial_level, पूर्णाङ्क subsequent_level, पूर्णाङ्क *state, ध्रुव वर्ण *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

शून्य av_vlog(शून्य* avcl, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : रिक्त;
    शून्य (*log_callback)(शून्य*, पूर्णाङ्क, ध्रुव वर्ण*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    यदि (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(पूर्णाङ्क *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    यदि (log_callback)
        log_callback(avcl, level, fmt, vl);
}

पूर्णाङ्क av_log_get_level(शून्य)
{
    प्रत्यागम atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

शून्य av_log_set_level(पूर्णाङ्क level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

शून्य av_log_set_flags(पूर्णाङ्क arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

पूर्णाङ्क av_log_get_flags(शून्य)
{
    प्रत्यागम atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

शून्य av_log_set_callback(शून्य (*callback)(शून्य*, पूर्णाङ्क, ध्रुव वर्ण*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

स्थिर शून्य missing_feature_sample(पूर्णाङ्क sample, शून्य *avc, ध्रुव वर्ण *संदेश,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, संदेश, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    यदि (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

शून्य avpriv_request_sample(शून्य *avc, ध्रुव वर्ण *संदेश, ...)
{
    va_list argument_list;

    va_start(argument_list, संदेश);
    missing_feature_sample(1, avc, संदेश, argument_list);
    va_end(argument_list);
}

शून्य avpriv_report_missing_feature(शून्य *avc, ध्रुव वर्ण *संदेश, ...)
{
    va_list argument_list;

    va_start(argument_list, संदेश);
    missing_feature_sample(0, avc, संदेश, argument_list);
    va_end(argument_list);
}
