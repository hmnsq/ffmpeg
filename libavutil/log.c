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

#அந்தர்பாவ "config.h"

#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#எனில் HAVE_IO_H
#அந்தர்பாவ <io.h>
#endif
#அந்தர்பாவ <inttypes.h>
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ "bprint.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "internal.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "thread.h"
#அந்தர்பாவ "time.h"
#அந்தர்பாவ "time_internal.h"

நிலையான AVMutex mutex = AV_MUTEX_INITIALIZER;

#define வரி_SZ 1024

#எனில் HAVE_VALGRIND_VALGRIND_H && CONFIG_VALGRIND_BACKTRACE
#அந்தர்பாவ <valgrind/valgrind.h>
/* this is the log level at which valgrind will output a full backtrace */
#define BACKTRACE_LOGLEVEL AV_LOG_ERROR
#endif

நிலையான atomic_int av_log_level = AV_LOG_INFO;
நிலையான atomic_int av_log_flags = 0;

#define NB_LEVELS 8
#எனில் defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
#அந்தர்பாவ <windows.h>
நிலையான மாறிலி uint8_t win_color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] = 12,
    [AV_LOG_FATAL  /8] = 12,
    [AV_LOG_ERROR  /8] = 12,
    [AV_LOG_WARNING/8] = 14,
    [AV_LOG_INFO   /8] =  7,
    [AV_LOG_VERBOSE/8] = 10,
    [AV_LOG_DEBUG  /8] = 10,
    [AV_LOG_TRACE  /8] = 8,
    [16+AV_CLASS_CATEGORY_NA              ] =  7,
    [16+AV_CLASS_CATEGORY_உள்ளீடு           ] = 13,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_உள்ளீடு  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_உள்ளீடு  ] = 5,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 13,
    [16+AV_CLASS_CATEGORY_DEVICE_உள்ளீடு        ] = 5,
};

நிலையான int16_t background, attr_orig;
நிலையான HANDLE con;
#endif

நிலையான மாறிலி uint32_t color[16 + AV_CLASS_CATEGORY_NB] = {
    [AV_LOG_PANIC  /8] =  52 << 16 | 196 << 8 | 0x41,
    [AV_LOG_FATAL  /8] = 208 <<  8 | 0x41,
    [AV_LOG_ERROR  /8] = 196 <<  8 | 0x11,
    [AV_LOG_WARNING/8] = 226 <<  8 | 0x03,
    [AV_LOG_INFO   /8] = 253 <<  8 | 0x09,
    [AV_LOG_VERBOSE/8] =  40 <<  8 | 0x02,
    [AV_LOG_DEBUG  /8] =  34 <<  8 | 0x02,
    [AV_LOG_TRACE  /8] =  34 <<  8 | 0x07,
    [16+AV_CLASS_CATEGORY_NA              ] = 250 << 8 | 0x09,
    [16+AV_CLASS_CATEGORY_உள்ளீடு           ] = 219 << 8 | 0x15,
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
    [16+AV_CLASS_CATEGORY_DEVICE_VIDEO_உள்ளீடு  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_AUDIO_உள்ளீடு  ] = 207 << 8 | 0x05,
    [16+AV_CLASS_CATEGORY_DEVICE_OUTPUT       ] = 213 << 8 | 0x15,
    [16+AV_CLASS_CATEGORY_DEVICE_உள்ளீடு        ] = 207 << 8 | 0x05,
};

நிலையான முழு use_color = -1;

#எனில் defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
நிலையான வெறுமை win_console_puts(மாறிலி எழுத்து *str)
{
    மாறிலி uint8_t *q = str;
    uint16_t வரி[வரி_SZ];

    போது (*q) {
        uint16_t *buf = வரி;
        DWORD nb_chars = 0;
        DWORD written;

        போது (*q && nb_chars < வரி_SZ - 1) {
            uint32_t ch;
            uint16_t tmp;

            GET_UTF8(ch, *q ? *q++ : 0, ch = 0xfffd; செல் continue_on_invalid;)
continue_on_invalid:
            PUT_UTF16(ch, tmp, *buf++ = tmp; nb_chars++;)
        }

        WriteConsoleW(con, வரி, nb_chars, &written, வெற்று);
    }
}
#endif

நிலையான வெறுமை check_color_terminal(வெறுமை)
{
    எழுத்து *term = getenv("TERM");

#எனில் defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    DWORD dummy;
    con = GetStdHandle(STD_ERROR_HANDLE);
    எனில் (con != INVALID_HANDLE_மதிப்பு && !GetConsoleMode(con, &dummy))
        con = INVALID_HANDLE_மதிப்பு;
    எனில் (con != INVALID_HANDLE_மதிப்பு) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#endif

    எனில் (getenv("AV_LOG_FORCE_NOCOLOR")) {
        use_color = 0;
    } இல்லையெனில் எனில் (getenv("AV_LOG_FORCE_COLOR")) {
        use_color = 1;
    } இல்லையெனில் {
#எனில் defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
        use_color = (con != INVALID_HANDLE_மதிப்பு);
#அல்லதெனில் HAVE_ISATTY
        use_color = (term && isatty(2));
#இல்லையெனில்
        use_color = 0;
#endif
    }

    எனில் (getenv("AV_LOG_FORCE_256COLOR") || term && strstr(term, "256color"))
        use_color *= 256;
}

நிலையான வெறுமை ansi_fputs(முழு level, முழு tint, மாறிலி எழுத்து *str, முழு local_use_color)
{
    எனில் (local_use_color == 1) {
        uint32_t intensity = (color[level] >> 4) & 15;
        uint32_t fg       = color[level] & 15;
#எனில் defined(_WIN32)
        /* Piped stderr is 8-color ANSI. Linux keeps 0;33m; Windows console
         * already uses win_color 14 (bright yellow), so match that here. */
        எனில் (level == AV_LOG_WARNING / 8)
            intensity = 1;
#endif
        fprintf(stderr,
                "\033[%"PRIu32";3%"PRIu32"m%s\033[0m",
                intensity, fg, str);
    } இல்லையெனில் எனில் (tint && use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%dm%s\033[0m",
                (color[level] >> 16) & 0xff,
                tint,
                str);
    } இல்லையெனில் எனில் (local_use_color == 256) {
        fprintf(stderr,
                "\033[48;5;%"PRIu32"m\033[38;5;%"PRIu32"m%s\033[0m",
                (color[level] >> 16) & 0xff,
                (color[level] >> 8) & 0xff,
                str);
    } இல்லையெனில்
        fputs(str, stderr);
}

நிலையான வெறுமை colored_fputs(முழு level, முழு tint, மாறிலி எழுத்து *str)
{
    முழு local_use_color;
    எனில் (!*str)
        திரும்பு;

    எனில் (use_color < 0)
        check_color_terminal();

    எனில் (level == AV_LOG_INFO/8) local_use_color = 0;
    இல்லையெனில்                        local_use_color = use_color;

#எனில் defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE && HAVE_GETSTDHANDLE
    எனில் (con != INVALID_HANDLE_மதிப்பு) {
        எனில் (local_use_color)
            SetConsoleTextAttribute(con, background | win_color[level]);
        win_console_puts(str);
        எனில் (local_use_color)
            SetConsoleTextAttribute(con, attr_orig);
    } இல்லையெனில் {
        ansi_fputs(level, tint, str, local_use_color);
    }
#இல்லையெனில்
    ansi_fputs(level, tint, str, local_use_color);
#endif

}

மாறிலி எழுத்து *av_default_item_name(வெறுமை *ptr)
{
    திரும்பு (*(AVClass **) ptr)->class_name;
}

AVClassCategory av_default_get_category(வெறுமை *ptr)
{
    திரும்பு (*(AVClass **) ptr)->category;
}

நிலையான வெறுமை sanitize(uint8_t *வரி){
    போது(*வரி){
        எனில்(*வரி < 0x08 || (*வரி > 0x0D && *வரி < 0x20))
            *வரி='?';
        வரி++;
    }
}

நிலையான முழு get_category(வெறுமை *ptr){
    AVClass *avc = *(AVClass **) ptr;
    எனில்(    !avc
        || (avc->version&0xFF)<100
        ||  avc->version < (51 << 16 | 59 << 8)
        ||  avc->category >= AV_CLASS_CATEGORY_NB) திரும்பு AV_CLASS_CATEGORY_NA + 16;

    எனில்(avc->get_category)
        திரும்பு avc->get_category(ptr) + 16;

    திரும்பு avc->category + 16;
}

நிலையான மாறிலி எழுத்து *get_level_str(முழு level)
{
    தேர்வு (level) {
    நிலை AV_LOG_QUIET:
        திரும்பு "quiet";
    நிலை AV_LOG_DEBUG:
        திரும்பு "debug";
    நிலை AV_LOG_TRACE:
        திரும்பு "trace";
    நிலை AV_LOG_VERBOSE:
        திரும்பு "verbose";
    நிலை AV_LOG_INFO:
        திரும்பு "info";
    நிலை AV_LOG_WARNING:
        திரும்பு "warning";
    நிலை AV_LOG_ERROR:
        திரும்பு "error";
    நிலை AV_LOG_FATAL:
        திரும்பு "fatal";
    நிலை AV_LOG_PANIC:
        திரும்பு "panic";
    இயல்பு:
        திரும்பு "";
    }
}

நிலையான மாறிலி எழுத்து *item_name(வெறுமை *obj, மாறிலி AVClass *cls)
{
    திரும்பு (cls->item_name ? cls->item_name : av_default_item_name)(obj);
}

நிலையான வெறுமை format_date_now(AVBPrint* bp_time, முழு include_date)
{
    கட்டமைப்பு tm *ptm, tmbuf;
    மாறிலி int64_t time_us = av_gettime();
    மாறிலி int64_t time_ms = time_us / 1000;
    மாறிலி time_t time_s   = time_ms / 1000;
    மாறிலி முழு millisec    = time_ms - (time_s * 1000);
    ptm                   = localtime_r(&time_s, &tmbuf);
    எனில் (ptm) {
        எனில் (include_date)
            av_bprint_strftime(bp_time, "%Y-%m-%d ", ptm);

        av_bprint_strftime(bp_time, "%H:%M:%S", ptm);
        av_bprintf(bp_time, ".%03d ", millisec);
    }
}

நிலையான வெறுமை format_வரி(வெறுமை *avcl, முழு level, மாறிலி எழுத்து *fmt, va_list vl,
                        AVBPrint part[5], முழு *print_prefix, முழு type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : வெற்று;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);
    av_bprint_init(part+4, 0, AV_BPRINT_SIZE_AUTOMATIC);
    முழு flags = atomic_load_explicit(&av_log_flags, memory_order_relaxed);

    எனில்(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    எனில் (*print_prefix && avc) {
        எனில் (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            எனில் (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                           item_name(parent, *parent), parent);
                எனில்(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                   item_name(avcl, avc), avcl);
        எனில்(type) type[1] = get_category(avcl);
    }

    எனில் (*print_prefix && (level > AV_LOG_QUIET) && (flags & (AV_LOG_PRINT_TIME | AV_LOG_PRINT_DATETIME)))
        format_date_now(&part[4], flags & AV_LOG_PRINT_DATETIME);

    எனில் (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    எனில்(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        எழுத்து lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}

வெறுமை av_log_format_வரி(வெறுமை *ptr, முழு level, மாறிலி எழுத்து *fmt, va_list vl,
                        எழுத்து *வரி, முழு வரி_size, முழு *print_prefix)
{
    av_log_format_line2(ptr, level, fmt, vl, வரி, வரி_size, print_prefix);
}

முழு av_log_format_line2(வெறுமை *ptr, முழு level, மாறிலி எழுத்து *fmt, va_list vl,
                        எழுத்து *வரி, முழு வரி_size, முழு *print_prefix)
{
    AVBPrint part[5];
    முழு ret;

    format_வரி(ptr, level, fmt, vl, part, print_prefix, வெற்று);
    ret = snprintf(வரி, வரி_size, "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);
    av_bprint_finalize(part+3, வெற்று);
    திரும்பு ret;
}

வெறுமை av_log_default_callback(வெறுமை* ptr, முழு level, மாறிலி எழுத்து* fmt, va_list vl)
{
    நிலையான முழு print_prefix = 1;
    நிலையான முழு மொத்தம்;
    நிலையான எழுத்து prev[வரி_SZ];
    AVBPrint part[5];
    எழுத்து வரி[வரி_SZ];
    நிலையான முழு is_atty;
    முழு type[2];
    unsigned tint = 0;

    எனில் (level >= 0) {
        tint = level & 0xff00;
        level &= 0xff;
    }

    எனில் (level > atomic_load_explicit(&av_log_level, memory_order_relaxed))
        திரும்பு;
    ff_mutex_lock(&mutex);

    format_வரி(ptr, level, fmt, vl, part, &print_prefix, type);
    snprintf(வரி, அளவு(வரி), "%s%s%s%s", part[0].str, part[1].str, part[2].str, part[3].str);

#எனில் HAVE_ISATTY
    எனில் (!is_atty)
        is_atty = isatty(2) ? 1 : -1;
#endif

    எனில் (print_prefix && (atomic_load_explicit(&av_log_flags, memory_order_relaxed) & AV_LOG_SKIP_REPEATED) && !strcmp(வரி, prev) &&
        *வரி && வரி[strlen(வரி) - 1] != '\r'){
        மொத்தம்++;
        எனில் (is_atty == 1)
            fprintf(stderr, "    Last message repeated %d times\r", மொத்தம்);
        செல் end;
    }
    எனில் (மொத்தம் > 0) {
        fprintf(stderr, "    Last message repeated %d times\n", மொத்தம்);
        மொத்தம் = 0;
    }
    strcpy(prev, வரி);

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

#எனில் CONFIG_VALGRIND_BACKTRACE
    எனில் (level <= BACKTRACE_LOGLEVEL)
        VALGRIND_PRINTF_BACKTRACE("%s", "");
#endif
end:
    av_bprint_finalize(part+3, வெற்று);
    ff_mutex_unlock(&mutex);
}

நிலையான வெறுமை (*_Atomic av_log_callback)(வெறுமை*, முழு, மாறிலி எழுத்து*, va_list) = av_log_default_callback;

வெறுமை av_log(வெறுமை* avcl, முழு level, மாறிலி எழுத்து *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, level, fmt, vl);
    va_end(vl);
}

வெறுமை av_log_once(வெறுமை* avcl, முழு initial_level, முழு subsequent_level, முழு *state, மாறிலி எழுத்து *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vlog(avcl, *state ? subsequent_level : initial_level, fmt, vl);
    va_end(vl);
    *state = 1;
}

வெறுமை av_vlog(வெறுமை* avcl, முழு level, மாறிலி எழுத்து *fmt, va_list vl)
{
    AVClass* avc = avcl ? *(AVClass **) avcl : வெற்று;
    வெறுமை (*log_callback)(வெறுமை*, முழு, மாறிலி எழுத்து*, va_list) =
        atomic_load_explicit(&av_log_callback, memory_order_relaxed);
    எனில் (avc && avc->version >= (50 << 16 | 15 << 8 | 2) &&
        avc->log_level_offset_offset && level >= AV_LOG_FATAL)
        level += *(முழு *) (((uint8_t *) avcl) + avc->log_level_offset_offset);
    எனில் (log_callback)
        log_callback(avcl, level, fmt, vl);
}

முழு av_log_get_level(வெறுமை)
{
    திரும்பு atomic_load_explicit(&av_log_level, memory_order_relaxed);
}

வெறுமை av_log_set_level(முழு level)
{
    atomic_store_explicit(&av_log_level, level, memory_order_relaxed);
}

வெறுமை av_log_set_flags(முழு arg)
{
    atomic_store_explicit(&av_log_flags, arg, memory_order_relaxed);
}

முழு av_log_get_flags(வெறுமை)
{
    திரும்பு atomic_load_explicit(&av_log_flags, memory_order_relaxed);
}

வெறுமை av_log_set_callback(வெறுமை (*callback)(வெறுமை*, முழு, மாறிலி எழுத்து*, va_list))
{
    atomic_store_explicit(&av_log_callback, callback, memory_order_relaxed);
}

நிலையான வெறுமை missing_feature_sample(முழு sample, வெறுமை *avc, மாறிலி எழுத்து *செய்தி,
                                   va_list argument_list)
{
    av_vlog(avc, AV_LOG_WARNING, செய்தி, argument_list);
    av_log(avc, AV_LOG_WARNING, " is not implemented. Update your FFmpeg "
           "version to the newest one from Git. If the problem still "
           "occurs, it means that your file has a feature which has not "
           "been implemented.\n");
    எனில் (sample)
        av_log(avc, AV_LOG_WARNING, "If you want to help, upload a sample "
               "of this file to https://streams.videolan.org/upload/ "
               "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)\n");
}

வெறுமை avpriv_request_sample(வெறுமை *avc, மாறிலி எழுத்து *செய்தி, ...)
{
    va_list argument_list;

    va_start(argument_list, செய்தி);
    missing_feature_sample(1, avc, செய்தி, argument_list);
    va_end(argument_list);
}

வெறுமை avpriv_report_missing_feature(வெறுமை *avc, மாறிலி எழுத்து *செய்தி, ...)
{
    va_list argument_list;

    va_start(argument_list, செய்தி);
    missing_feature_sample(0, avc, செய்தி, argument_list);
    va_end(argument_list);
}
