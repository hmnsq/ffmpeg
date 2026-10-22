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

#समावेश "config.h"

#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर HAVE_IO_H
#समावेश <io.h>
#पूर्ण_अगर
#समावेश <inttypes.h>
#समावेश <stdarg.h>
#समावेश <stdatomic.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश "bprint.h"
#समावेश "common.h"
#समावेश "internal.h"
#समावेश "log.h"
#समावेश "thread.h"
#समावेश "time.h"
#समावेश "time_internal.h"

अटल AVMutex mutex = AV_MUTEX_INITIALIZER;

#घोषणा पंक्ति_SZ 1024

#अगर HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#समावेश <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#घोषणा BACKTRACE_LOGLEVEL AV_LOG_ERROR
#पूर्ण_अगर

अटल atomic_int av_log_level = AV_LOG_INFO;
अटल atomic_int av_log_flags = 0;

#घोषणा NB_LEVELS 8
#अगर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#समावेश <windows.h>
अटल स्थिर uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_निवेश           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_निवेश  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_निवेश  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_निवेश        ] = 5,
};

अटल int16_t background, attr_orig;
अटल HANDLE con;
#पूर्ण_अगर

अटल स्थिर uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_निवेश           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_निवेश  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_निवेश  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_निवेश        ] = 207 << 8 | 0x05,
};

अटल पूर्णांक use_color = -1;

#अगर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
अटल व्योम win_console_puts(स्थिर अक्षर *str)
{
    स्थिर uint8_t *q = str;
    uint16_t पंक्ति_2[पंक्ति_SZ];

    जबतक (*q) {
        uint16_t *buf = पंक्ति_2;
        DWORD nb_chars = 0;
        DWORD written;

        जबतक (*q && nb_chars < पंक्ति_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; जाओ continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, पंक्ति_2, nb_chars, &written, शून्य);
    }
}
#पूर्ण_अगर

अटल व्योम check_color_terminal(व्योम)
{
    अक्षर *term = दो_पर्या("TERM");

#अगर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_बफर_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    अगर (con != INVALID_HANDLE_मूल्य && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_मूल्य;
    अगर (con != INVALID_HANDLE_मूल्य) {
        Get_Console_Screen_बफर_Info(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#पूर्ण_अगर

    अगर (दो_पर्या("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } अन्यथा अगर (दो_पर्या("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } अन्यथा {
#अगर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_मूल्य);
#या_अगर HAVE_ISATTY
        use_color = (term && isatty(2));
#अन्यथा
        use_color = 0;
#पूर्ण_अगर
    }

    अगर (दो_पर्या("AV_LOG_FORCE_256COLOR") || term && म_माला(term, "256color"))
        use_color *= 256;
}

अटल व्योम ansi_fputs(पूर्णांक level, पूर्णांक tint, स्थिर अक्षर *str, पूर्णांक local_use_color)
{
    अगर (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#अगर defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        अगर (level == AV_LOG_WARNING / 8)
            intensity = 1;
#पूर्ण_अगर
        ख_लिखो(मानक_त्रुटि,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } अन्यथा अगर (tint && use_color == 256) {
        ख_लिखो(मानक_त्रुटि,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } अन्यथा अगर (local_use_color == 256) {
        ख_लिखो(मानक_त्रुटि,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } अन्यथा
        ख_माला_दो(str, मानक_त्रुटि);
}

अटल व्योम colored_fputs(पूर्णांक level, पूर्णांक tint, स्थिर अक्षर *str)
{
    पूर्णांक local_use_color;
    अगर (!*str)
        वापस;

    अगर (use_color < 0)
        check_color_terminal();

    अगर (level == AV_LOG_INFO/8) local_use_color = 0;
    अन्यथा                        local_use_color = use_color;

#अगर defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    अगर (con != INVALID_HANDLE_मूल्य) {
        अगर (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        अगर (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } अन्यथा {
        ansi_fputs(level, tint, str, local_use_color);
    }
#अन्यथा
    ansi_fputs(level, tint, str, local_use_color);
#पूर्ण_अगर

}

स्थिर अक्षर *av_default_item_name(व्योम *ptr)
{
    वापस (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(व्योम *ptr)
{
    वापस (*(AVClass **) ptr)->category;
}

अटल व्योम sanitize(uint8_t *पंक्ति_2){
    जबतक(*पंक्ति_2){
        अगर(*पंक्ति_2 < 0x08 || (*पंक्ति_2 > 0x0D && *पंक्ति_2 < 0x20))
            *पंक्ति_2='?';
        पंक्ति_2++;
    }
}

अटल पूर्णांक get_category(व्योम *ptr){
    AVClass *avc = *(AVClass **) ptr;
    अगर(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) वापस AV_CLASS_CATEGORY_NA + 16;

    अगर(avc->get_category)
        वापस avc->get_category(ptr) + 16;

    वापस avc->category + 16;
}

अटल स्थिर अक्षर *get_level_str(पूर्णांक level)
{
    चयन (level) {
    हाल AV_LOG_QUIET:
        वापस "quiet";
    हाल AV_LOG_DEBUG:
        वापस "debug";
    हाल AV_LOG_TRACE:
        वापस "trace";
    हाल AV_LOG_VERBOSE:
        वापस "verbose";
    हाल AV_LOG_INFO:
        वापस "info";
    हाल AV_LOG_WARNING:
        वापस "warning";
    हाल AV_LOG_ERROR:
        वापस "error";
    हाल AV_LOG_FATAL:
        वापस "fatal";
    हाल AV_LOG_PANIC:
        वापस "panic";
    शेष:
        वापस "";
    }
}

अटल स्थिर अक्षर *item_name(व्योम *obj, स्थिर AVClass *cls)
{
    वापस (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

अटल व्योम format_date_now(AVBPrint* bp_time, पूर्णांक include_date)
{
    काष्ठा पंचांग *ptm, tmbuf;
    स्थिर int64_t time_us = av_gettime();
    स्थिर int64_t time_ms = time_us / 1000;
    स्थिर समय_प्रकार time_s   = time_ms / 1000;
    स्थिर पूर्णांक millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    अगर (ptm) {
        अगर (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

अटल व्योम format_पंक्ति(व्योम *avcl, पूर्णांक level, स्थिर अक्षर *fmt, बहु_सूची vl,
                        AVBPrint part[5], पूर्णांक *print_prefix, पूर्णांक type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : शून्य;
    av_bprint_init(part+0, 0, AV_BPRINT_आकार_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_आकार_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_आकार_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_आकार_AUTOMATIC);
    पूर्णांक flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    अगर(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    अगर (*print_prefix && avc) {
        अगर (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            अगर (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                अगर(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        अगर(type) type[1] = get_category(avcl);
    }

    अगर (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    अगर (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    अगर(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        अक्षर lastc = part[3].len && part[3].len <= part[3].आकार ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

व्योम av_log_format_पंक्ति(व्योम *ptr, पूर्णांक level, स्थिर अक्षर *fmt, बहु_सूची vl,
                        अक्षर *पंक्ति_2, पूर्णांक पंक्ति_आकार, पूर्णांक *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, पंक्ति_2, पंक्ति_आकार, print_prefix);
}

पूर्णांक av_log_format_line2(व्योम *ptr, पूर्णांक level, स्थिर अक्षर *fmt, बहु_सूची vl,
                        अक्षर *पंक्ति_2, पूर्णांक पंक्ति_आकार, पूर्णांक *print_prefix)
{
    AVBPrint part[5];
    पूर्णांक ret;

    format_पंक्ति(ptr, level, fmt, vl, part, print_prefix, शून्य);
    ret = snprintf(पंक्ति_2, पंक्ति_आकार, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, शून्य);
    वापस ret;
}

व्योम av_log_default_callback(व्योम* ptr, पूर्णांक level, स्थिर अक्षर* fmt, बहु_सूची vl)
{
    अटल पूर्णांक print_prefix = 1;
    अटल पूर्णांक गिनती;
    अटल अक्षर पूर्व[पंक्ति_SZ];
    AVBPrint part[5];
    अक्षर पंक्ति_2[पंक्ति_SZ];
    अटल पूर्णांक is_atty;
    पूर्णांक type[2];
    अचिन्हित tint = 0;

    अगर (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    अगर (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        वापस;
    ff_mutex_lock(&mutex);

    format_पंक्ति(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(पंक्ति_2, माप(पंक्ति_2), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#अगर HAVE_ISATTY
    अगर (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#पूर्ण_अगर

    अगर (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !म_भेद(पंक्ति_2, पूर्व) &&
        *पंक्ति_2 && पंक्ति_2[म_माप(पंक्ति_2) - 1] != '\r'){
        गिनती++;
        अगर (is_atty == 1)
            ख_लिखो(मानक_त्रुटि, "    Last message repeated %d times\r", गिनती);
        जाओ end;
    }
    अगर (गिनती > 0) {
        ख_लिखो(मानक_त्रुटि, "    Last message repeated %d times\n", गिनती);
        गिनती = 0;
    }
    म_नकल(पूर्व, पंक्ति_2);

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

#अगर CONFIG_VALGRIND_BACKTRACE
    अगर (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#पूर्ण_अगर
end:
    av_bprint_finalize(part+3, शून्य);
    ff_mutex_unlock(&mutex);
}

अटल व्योम (*_Atomic av_log_callback)(व्योम*, पूर्णांक, स्थिर अक्षर*, बहु_सूची) = av_log_default_callback;

व्योम av_log(व्योम* avcl, पूर्णांक level, स्थिर अक्षर *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    बहु_पूर्ण(vl);
}

व्योम av_log_once(व्योम* avcl, पूर्णांक initial_level, पूर्णांक subsequent_level, पूर्णांक *state, स्थिर अक्षर *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    बहु_पूर्ण(vl);
    *state = 1;
}

व्योम av_vlog(व्योम* avcl, पूर्णांक level, स्थिर अक्षर *fmt, बहु_सूची vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : शून्य;
    व्योम (*log_callback)(व्योम*, पूर्णांक, स्थिर अक्षर*, बहु_सूची) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    अगर (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(पूर्णांक *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    अगर (log_callback)
        log_callback(avcl, level, fmt, vl);
}

पूर्णांक av_log_get_level(व्योम)
{
    वापस atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

व्योम av_log_set_level(पूर्णांक level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

व्योम av_log_set_flags(पूर्णांक arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

पूर्णांक av_log_get_flags(व्योम)
{
    वापस atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

व्योम av_log_set_callback(व्योम (*callback)(व्योम*, पूर्णांक, स्थिर अक्षर*, बहु_सूची))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

अटल व्योम missing_feature_sample(पूर्णांक sample, व्योम *avc, स्थिर अक्षर *संदेश,
                                   बहु_सूची argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, संदेश, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    अगर (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

व्योम avpriv_request_sample(व्योम *avc, स्थिर अक्षर *संदेश, ...)
{
    बहु_सूची argument_list;

    बहु_शुरू(argument_list, संदेश);
    missing_feature_sample(1, avc, संदेश, argument_list);
    बहु_पूर्ण(argument_list);
}

व्योम avpriv_report_missing_feature(व्योम *avc, स्थिर अक्षर *संदेश, ...)
{
    बहु_सूची argument_list;

    बहु_शुरू(argument_list, संदेश);
    missing_feature_sample(0, avc, संदेश, argument_list);
    बहु_पूर्ण(argument_list);
}
