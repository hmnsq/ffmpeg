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

#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जर HAVE_IO_H
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

#जर HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#अन्तर्भाव <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

स्थिर atomic_int av_log_level = AV_LOG_INFO;
स्थिर atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#जर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#अन्तर्भाव <windows.h>
स्थिर स्थिरांक uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
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

स्थिर स्थिरांक uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
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

स्थिर पूर्णांक use_color = -1;

#जर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
स्थिर शून्य win_console_puts(स्थिरांक अक्षर *str)
{
    स्थिरांक uint8_t *q = str;
    uint16_t ओळ[ओळ_SZ];

    पर्यंत (*q) {
        uint16_t *buf = ओळ;
        DWORD nb_chars = 0;
        DWORD written;

        पर्यंत (*q && nb_chars < ओळ_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; जा continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, ओळ, nb_chars, &written, रिक्त);
    }
}
#endif

स्थिर शून्य check_color_terminal(शून्य)
{
    अक्षर *term = दो_पर्या("TERM");

#जर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    जर (con != INVALID_HANDLE_मूल्य && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_मूल्य;
    जर (con != INVALID_HANDLE_मूल्य) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    जर (दो_पर्या("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } अन्यथा जर (दो_पर्या("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } अन्यथा {
#जर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_मूल्य);
#किंवाजर HAVE_ISATTY
        use_color = (term && isatty(2));
#अन्यथा
        use_color = 0;
#endif
    }

    जर (दो_पर्या("AV_LOG_FORCE_256COLOR") || term && म_माला(term, "256color"))
        use_color *= 256;
}

स्थिर शून्य ansi_fputs(पूर्णांक level, पूर्णांक tint, स्थिरांक अक्षर *str, पूर्णांक local_use_color)
{
    जर (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#जर defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        जर (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        ख_लिखो(मानक_त्रुटि,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } अन्यथा जर (tint && use_color == 256) {
        ख_लिखो(मानक_त्रुटि,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } अन्यथा जर (local_use_color == 256) {
        ख_लिखो(मानक_त्रुटि,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } अन्यथा
        ख_माला_दो(str, मानक_त्रुटि);
}

स्थिर शून्य colored_fputs(पूर्णांक level, पूर्णांक tint, स्थिरांक अक्षर *str)
{
    पूर्णांक local_use_color;
    जर (!*str)
        परत;

    जर (use_color < 0)
        check_color_terminal();

    जर (level == AV_LOG_INFO/8) local_use_color = 0;
    अन्यथा                        local_use_color = use_color;

#जर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    जर (con != INVALID_HANDLE_मूल्य) {
        जर (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        जर (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } अन्यथा {
        ansi_fputs(level, tint, str, local_use_color);
    }
#अन्यथा
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

स्थिरांक अक्षर *av_default_item_name(शून्य *ptr)
{
    परत (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(शून्य *ptr)
{
    परत (*(AVClass **) ptr)->category;
}

स्थिर शून्य sanitize(uint8_t *ओळ){
    पर्यंत(*ओळ){
        जर(*ओळ < 0x08 || (*ओळ > 0x0D && *ओळ < 0x20))
            *ओळ='?';
        ओळ++;
    }
}

स्थिर पूर्णांक get_category(शून्य *ptr){
    AVClass *avc = *(AVClass **) ptr;
    जर(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) परत AV_CLASS_CATEGORY_NA + 16;

    जर(avc->get_category)
        परत avc->get_category(ptr) + 16;

    परत avc->category + 16;
}

स्थिर स्थिरांक अक्षर *get_level_str(पूर्णांक level)
{
    निवड (level) {
    स्थिती AV_LOG_QUIET:
        परत "quiet";
    स्थिती AV_LOG_DEBUG:
        परत "debug";
    स्थिती AV_LOG_TRACE:
        परत "trace";
    स्थिती AV_LOG_VERBOSE:
        परत "verbose";
    स्थिती AV_LOG_INFO:
        परत "info";
    स्थिती AV_LOG_WARNING:
        परत "warning";
    स्थिती AV_LOG_ERROR:
        परत "error";
    स्थिती AV_LOG_FATAL:
        परत "fatal";
    स्थिती AV_LOG_PANIC:
        परत "panic";
    पूर्वनिर्धारित:
        परत "";
    }
}

स्थिर स्थिरांक अक्षर *item_name(शून्य *obj, स्थिरांक AVClass *cls)
{
    परत (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

स्थिर शून्य format_date_now(AVBPrint* bp_time, पूर्णांक include_date)
{
    संरचना पंचांग *ptm, tmbuf;
    स्थिरांक int64_t time_us = av_gettime();
    स्थिरांक int64_t time_ms = time_us / 1000;
    स्थिरांक समय_प्रकार time_s   = time_ms / 1000;
    स्थिरांक पूर्णांक millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    जर (ptm) {
        जर (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

स्थिर शून्य format_ओळ(शून्य *avcl, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची vl,
                        AVBPrint part[5], पूर्णांक *print_prefix, पूर्णांक type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : रिक्त;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    पूर्णांक flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    जर(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    जर (*print_prefix && avc) {
        जर (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            जर (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                जर(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        जर(type) type[1] = get_category(avcl);
    }

    जर (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    जर (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    जर(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        अक्षर lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

शून्य av_log_format_ओळ(शून्य *ptr, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची vl,
                        अक्षर *ओळ, पूर्णांक ओळ_size, पूर्णांक *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, ओळ, ओळ_size, print_prefix);
}

पूर्णांक av_log_format_line2(शून्य *ptr, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची vl,
                        अक्षर *ओळ, पूर्णांक ओळ_size, पूर्णांक *print_prefix)
{
    AVBPrint part[5];
    पूर्णांक ret;

    format_ओळ(ptr, level, fmt, vl, part, print_prefix, रिक्त);
    ret = snprintf(ओळ, ओळ_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, रिक्त);
    परत ret;
}

शून्य av_log_default_callback(शून्य* ptr, पूर्णांक level, स्थिरांक अक्षर* fmt, बहु_सूची vl)
{
    स्थिर पूर्णांक print_prefix = 1;
    स्थिर पूर्णांक मोजणी;
    स्थिर अक्षर prev[ओळ_SZ];
    AVBPrint part[5];
    अक्षर ओळ[ओळ_SZ];
    स्थिर पूर्णांक is_atty;
    पूर्णांक type[2];
    अचिन्हित tint = 0;

    जर (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    जर (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        परत;
    ff_mutex_lock(&mutex);

    format_ओळ(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(ओळ, आकार(ओळ), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#जर HAVE_ISATTY
    जर (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    जर (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !म_भेद(ओळ, prev) &&
        *ओळ && ओळ[म_माप(ओळ) - 1] != '\r'){
        मोजणी++;
        जर (is_atty == 1)
            ख_लिखो(मानक_त्रुटि, "    Last message repeated %d times\r", मोजणी);
        जा end;
    }
    जर (मोजणी > 0) {
        ख_लिखो(मानक_त्रुटि, "    Last message repeated %d times\n", मोजणी);
        मोजणी = 0;
    }
    म_नकल(prev, ओळ);

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

#जर CONFIG_VALGRIND_BACKTRACE
    जर (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, रिक्त);
    ff_mutex_unlock(&mutex);
}

स्थिर शून्य (*_Atomic av_log_callback)(शून्य*, पूर्णांक, स्थिरांक अक्षर*, बहु_सूची) = av_log_default_callback;

शून्य av_log(शून्य* avcl, पूर्णांक level, स्थिरांक अक्षर *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    बहु_पूर्ण(vl);
}

शून्य av_log_once(शून्य* avcl, पूर्णांक initial_level, पूर्णांक subsequent_level, पूर्णांक *state, स्थिरांक अक्षर *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    बहु_पूर्ण(vl);
    *state = 1;
}

शून्य av_vlog(शून्य* avcl, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : रिक्त;
    शून्य (*log_callback)(शून्य*, पूर्णांक, स्थिरांक अक्षर*, बहु_सूची) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    जर (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(पूर्णांक *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    जर (log_callback)
        log_callback(avcl, level, fmt, vl);
}

पूर्णांक av_log_get_level(शून्य)
{
    परत atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

शून्य av_log_set_level(पूर्णांक level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

शून्य av_log_set_flags(पूर्णांक arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

पूर्णांक av_log_get_flags(शून्य)
{
    परत atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

शून्य av_log_set_callback(शून्य (*callback)(शून्य*, पूर्णांक, स्थिरांक अक्षर*, बहु_सूची))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

स्थिर शून्य missing_feature_sample(पूर्णांक sample, शून्य *avc, स्थिरांक अक्षर *संदेश,
                                   बहु_सूची argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, संदेश, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    जर (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

शून्य avpriv_request_sample(शून्य *avc, स्थिरांक अक्षर *संदेश, ...)
{
    बहु_सूची argument_list;

    बहु_शुरू(argument_list, संदेश);
    missing_feature_sample(1, avc, संदेश, argument_list);
    बहु_पूर्ण(argument_list);
}

शून्य avpriv_report_missing_feature(शून्य *avc, स्थिरांक अक्षर *संदेश, ...)
{
    बहु_सूची argument_list;

    बहु_शुरू(argument_list, संदेश);
    missing_feature_sample(0, avc, संदेश, argument_list);
    बहु_पूर्ण(argument_list);
}
