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

#सचे HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#सचे HAVE_IO_H
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

#define पङ्क्तिः_SZ 1024

#सचे HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#अन्तर्भाव <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

स्थिर atomic_int av_log_level = AV_LOG_INFO;
स्थिर atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#सचे defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
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
    [16+AV_CLASS_CATEGORY_निवेशः           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_निवेशः  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_निवेशः  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_निवेशः        ] = 5,
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
    [16+AV_CLASS_CATEGORY_निवेशः           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_निवेशः  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_निवेशः  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_निवेशः        ] = 207 << 8 | 0x05,
};

स्थिर पूर्णाङ्क use_color = -1;

#सचे defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
स्थिर शून्य win_console_puts(ध्रुव वर्ण *str)
{
    ध्रुव uint8_t *q = str;
    uint16_t पङ्क्तिः[पङ्क्तिः_SZ];

    याव (*q) {
        uint16_t *buf = पङ्क्तिः;
        DWORD nb_chars = 0;
        DWORD written;

        याव (*q && nb_chars < पङ्क्तिः_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; गच्छ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, पङ्क्तिः, nb_chars, &written, रिक्त);
    }
}
#endif

स्थिर शून्य check_color_terminal(शून्य)
{
    वर्ण *term = getenv("TERM");

#सचे defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    सचे (con != INVALID_HANDLE_मानम् && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_मानम्;
    सचे (con != INVALID_HANDLE_मानम्) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    सचे (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } अञ्ञथा सचे (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } अञ्ञथा {
#सचे defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_मानम्);
#नोचेद्यदि HAVE_ISATTY
        use_color = (term && isatty(2));
#अञ्ञथा
        use_color = 0;
#endif
    }

    सचे (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

स्थिर शून्य ansi_fputs(पूर्णाङ्क level, पूर्णाङ्क tint, ध्रुव वर्ण *str, पूर्णाङ्क local_use_color)
{
    सचे (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#सचे defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        सचे (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } अञ्ञथा सचे (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } अञ्ञथा सचे (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } अञ्ञथा
        fputs(str, stderr);
}

स्थिर शून्य colored_fputs(पूर्णाङ्क level, पूर्णाङ्क tint, ध्रुव वर्ण *str)
{
    पूर्णाङ्क local_use_color;
    सचे (!*str)
        पटिनिवत्त;

    सचे (use_color < 0)
        check_color_terminal();

    सचे (level == AV_LOG_INFO/8) local_use_color = 0;
    अञ्ञथा                        local_use_color = use_color;

#सचे defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    सचे (con != INVALID_HANDLE_मानम्) {
        सचे (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        सचे (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } अञ्ञथा {
        ansi_fputs(level, tint, str, local_use_color);
    }
#अञ्ञथा
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

ध्रुव वर्ण *av_default_item_name(शून्य *ptr)
{
    पटिनिवत्त (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(शून्य *ptr)
{
    पटिनिवत्त (*(AVClass **) ptr)->category;
}

स्थिर शून्य sanitize(uint8_t *पङ्क्तिः){
    याव(*पङ्क्तिः){
        सचे(*पङ्क्तिः < 0x08 || (*पङ्क्तिः > 0x0D && *पङ्क्तिः < 0x20))
            *पङ्क्तिः='?';
        पङ्क्तिः++;
    }
}

स्थिर पूर्णाङ्क get_category(शून्य *ptr){
    AVClass *avc = *(AVClass **) ptr;
    सचे(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) पटिनिवत्त AV_CLASS_CATEGORY_NA + 16;

    सचे(avc->get_category)
        पटिनिवत्त avc->get_category(ptr) + 16;

    पटिनिवत्त avc->category + 16;
}

स्थिर ध्रुव वर्ण *get_level_str(पूर्णाङ्क level)
{
    विकल्प (level) {
    पक्ष AV_LOG_QUIET:
        पटिनिवत्त "quiet";
    पक्ष AV_LOG_DEBUG:
        पटिनिवत्त "debug";
    पक्ष AV_LOG_TRACE:
        पटिनिवत्त "trace";
    पक्ष AV_LOG_VERBOSE:
        पटिनिवत्त "verbose";
    पक्ष AV_LOG_INFO:
        पटिनिवत्त "info";
    पक्ष AV_LOG_WARNING:
        पटिनिवत्त "warning";
    पक्ष AV_LOG_ERROR:
        पटिनिवत्त "error";
    पक्ष AV_LOG_FATAL:
        पटिनिवत्त "fatal";
    पक्ष AV_LOG_PANIC:
        पटिनिवत्त "panic";
    स्वभाव:
        पटिनिवत्त "";
    }
}

स्थिर ध्रुव वर्ण *item_name(शून्य *obj, ध्रुव AVClass *cls)
{
    पटिनिवत्त (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

स्थिर शून्य format_date_now(AVBPrint* bp_time, पूर्णाङ्क include_date)
{
    संरचना tm *ptm, tmbuf;
    ध्रुव int64_t time_us = av_gettime();
    ध्रुव int64_t time_ms = time_us / 1000;
    ध्रुव time_t time_s   = time_ms / 1000;
    ध्रुव पूर्णाङ्क millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    सचे (ptm) {
        सचे (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

स्थिर शून्य format_पङ्क्तिः(शून्य *avcl, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        AVBPrint part[5], पूर्णाङ्क *print_prefix, पूर्णाङ्क type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : रिक्त;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    पूर्णाङ्क flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    सचे(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    सचे (*print_prefix && avc) {
        सचे (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            सचे (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                सचे(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        सचे(type) type[1] = get_category(avcl);
    }

    सचे (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    सचे (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    सचे(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        वर्ण lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

शून्य av_log_format_पङ्क्तिः(शून्य *ptr, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        वर्ण *पङ्क्तिः, पूर्णाङ्क पङ्क्तिः_size, पूर्णाङ्क *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, पङ्क्तिः, पङ्क्तिः_size, print_prefix);
}

पूर्णाङ्क av_log_format_line2(शून्य *ptr, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list vl,
                        वर्ण *पङ्क्तिः, पूर्णाङ्क पङ्क्तिः_size, पूर्णाङ्क *print_prefix)
{
    AVBPrint part[5];
    पूर्णाङ्क ret;

    format_पङ्क्तिः(ptr, level, fmt, vl, part, print_prefix, रिक्त);
    ret = snprintf(पङ्क्तिः, पङ्क्तिः_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, रिक्त);
    पटिनिवत्त ret;
}

शून्य av_log_default_callback(शून्य* ptr, पूर्णाङ्क level, ध्रुव वर्ण* fmt, va_list vl)
{
    स्थिर पूर्णाङ्क print_prefix = 1;
    स्थिर पूर्णाङ्क गणनम्;
    स्थिर वर्ण prev[पङ्क्तिः_SZ];
    AVBPrint part[5];
    वर्ण पङ्क्तिः[पङ्क्तिः_SZ];
    स्थिर पूर्णाङ्क is_atty;
    पूर्णाङ्क type[2];
    unsigned tint = 0;

    सचे (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    सचे (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        पटिनिवत्त;
    ff_mutex_lock(&mutex);

    format_पङ्क्तिः(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(पङ्क्तिः, परिमाण(पङ्क्तिः), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#सचे HAVE_ISATTY
    सचे (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    सचे (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(पङ्क्तिः, prev) &&
        *पङ्क्तिः && पङ्क्तिः[strlen(पङ्क्तिः) - 1] != '\r'){
        गणनम्++;
        सचे (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", गणनम्);
        गच्छ end;
    }
    सचे (गणनम् > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", गणनम्);
        गणनम् = 0;
    }
    strcpy(prev, पङ्क्तिः);

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

#सचे CONFIG_VALGRIND_BACKTRACE
    सचे (level <= BACKTRACE_LOGLEVEL)
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
    सचे (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(पूर्णाङ्क *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    सचे (log_callback)
        log_callback(avcl, level, fmt, vl);
}

पूर्णाङ्क av_log_get_level(शून्य)
{
    पटिनिवत्त atomic_load_explicit(&av_log_level, memory_order_relaxed);
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
    पटिनिवत्त atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

शून्य av_log_set_callback(शून्य (*callback)(शून्य*, पूर्णाङ्क, ध्रुव वर्ण*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

स्थिर शून्य missing_feature_sample(पूर्णाङ्क sample, शून्य *avc, ध्रुव वर्ण *सन्देशः,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, सन्देशः, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    सचे (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

शून्य avpriv_request_sample(शून्य *avc, ध्रुव वर्ण *सन्देशः, ...)
{
    va_list argument_list;

    va_start(argument_list, सन्देशः);
    missing_feature_sample(1, avc, सन्देशः, argument_list);
    va_end(argument_list);
}

शून्य avpriv_report_missing_feature(शून्य *avc, ध्रुव वर्ण *सन्देशः, ...)
{
    va_list argument_list;

    va_start(argument_list, सन्देशः);
    missing_feature_sample(0, avc, सन्देशः, argument_list);
    va_end(argument_list);
}
