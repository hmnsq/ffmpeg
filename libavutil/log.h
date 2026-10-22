/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_LOG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_LOG_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ {
    AV_CLASS_CATEGORY_NA = 0,
    AV_CLASS_CATEGORY_ਨਿਵੇਸ਼,
    AV_CLASS_CATEGORY_OUTPUT,
    AV_CLASS_CATEGORY_MUXER,
    AV_CLASS_CATEGORY_DEMUXER,
    AV_CLASS_CATEGORY_ENCODER,
    AV_CLASS_CATEGORY_DECODER,
    AV_CLASS_CATEGORY_FILTER,
    AV_CLASS_CATEGORY_BITSTREAM_FILTER,
    AV_CLASS_CATEGORY_SWSCALER,
    AV_CLASS_CATEGORY_SWRESAMPLER,
    AV_CLASS_CATEGORY_HWDEVICE,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT = 40,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_ਨਿਵੇਸ਼,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_ਨਿਵੇਸ਼,
    AV_CLASS_CATEGORY_DEVICE_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_ਨਿਵੇਸ਼,
    AV_CLASS_CATEGORY_NB  ///< not part of ABI/API
}AVClassCategory;

ਗਿਣਤੀ AVClassStateFlags {
    /**
     * Object initialization has finished and it is now in the 'runtime' stage.
     * This affects e.g. what options can be set on the object (only
     * AV_OPT_FLAG_RUNTIME_PARAM options can be set on initialized objects).
     */
    AV_CLASS_STATE_INITIALIZED         = (1 << 0),
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_IS_ਨਿਵੇਸ਼_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_ਨਿਵੇਸ਼) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_ਨਿਵੇਸ਼) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_ਨਿਵੇਸ਼))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_IS_OUTPUT_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_OUTPUT))

ਬਣਤਰ AVOptionRanges;

/**
 * Describe the class of an AVClass context structure. That is an
 * arbitrary struct of which the first field is a pointer to an
 * AVClass struct (e.g. AVCodecContext, AVFormatContext etc.).
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVClass {
    /**
     * The name of the class; usually it is the same name as the
     * context structure type to which the AVClass is associated.
     */
    ਅਚਲ ਅੱਖਰ* class_name;

    /**
     * A pointer to a function which returns the name of a context
     * instance ctx associated with the class.
     */
    ਅਚਲ ਅੱਖਰ* (*ਵਸਤੂ_name)(ਖਾਲੀ* ctx);

    /**
     * An array of options for the structure or NULL.
     * When non-NULL, the array must be terminated by an option with a NULL
     * name.
     *
     * @see av_set_default_options()
     */
    ਅਚਲ ਬਣਤਰ AVOption *option;

    /**
     * LIBAVUTIL_VERSION with which this structure was created.
     * This is used to allow fields to be added to AVClass without requiring
     * major version bumps everywhere.
     */

    ਪੂਰਨ ਸੰਸਕਰਣ;

    /**
     * Offset in the structure where the log level offset is stored. The log
     * level offset is an int added to the log level for logging with this
     * object as the context.
     *
     * 0 means there is no such variable.
     */
    ਪੂਰਨ log_level_ਵਿੱਥ_ਵਿੱਥ;

    /**
     * Offset in the structure where a pointer to the parent context for
     * logging is stored. For example a decoder could pass its AVCodecContext
     * to eval as such a parent context, which an ::av_log() implementation
     * could then leverage to display the parent context.
     *
     * When the pointer is NULL, or this offset is zero, the object is assumed
     * to have no parent.
     */
    ਪੂਰਨ ਮਾਪਾ_log_context_ਵਿੱਥ;

    /**
     * Category used for visualization (like color).
     *
     * Only used when ::get_category() is NULL. Use this field when all
     * instances of this class have the same category, use ::get_category()
     * otherwise.
     */
    AVClassCategory category;

    /**
     * Callback to return the instance category. Use this callback when
     * different instances of this class may have different categories,
     * ::category otherwise.
     */
    AVClassCategory (*get_category)(ਖਾਲੀ* ctx);

    /**
     * Callback to return the supported/allowed ranges.
     */
    ਪੂਰਨ (*query_ranges)(ਬਣਤਰ AVOptionRanges **, ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ flags);

    /**
     * Return next AVOptions-enabled child or NULL
     */
    ਖਾਲੀ* (*ਬੱਚਾ_ਅਗਲਾ)(ਖਾਲੀ *obj, ਖਾਲੀ *prev);

    /**
     * Iterate over the AVClasses corresponding to potential AVOptions-enabled
     * children.
     *
     * @param iter pointer to opaque iteration state. The caller must initialize
     *             *iter to NULL before the first call.
     * @return AVClass for the next AVOptions-enabled child or NULL if there are
     *         no more such children.
     *
     * @note The difference between ::child_next() and ::child_class_iterate()
     *       is that ::child_next() iterates over _actual_ children of an
     *       _existing_ object instance, while ::child_class_iterate() iterates
     *       over the classes of all _potential_ children of any possible
     *       instance of this class.
     */
    ਅਚਲ ਬਣਤਰ AVClass* (*ਬੱਚਾ_class_iterate)(ਖਾਲੀ **iter);

    /**
     * When non-zero, offset in the object to an unsigned int holding object
     * state flags, a combination of AVClassStateFlags values. The flags are
     * updated by the object to signal its state to the generic code.
     *
     * Added in version 59.41.100.
     */
    ਪੂਰਨ state_flags_ਵਿੱਥ;
} AVClass;

/**
 * @addtogroup lavu_log
 *
 * @{
 *
 * @defgroup lavu_log_constants Logging Constants
 *
 * @{
 */

/**
 * Print no output.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_QUIET    -8

/**
 * Something went really wrong and we will crash now.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_PANIC     0

/**
 * Something went wrong and recovery is not possible.
 * For example, no header was found for a format which depends
 * on headers or an illegal combination of parameters is used.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_FATAL     8

/**
 * Something went wrong and cannot losslessly be recovered.
 * However, not all future data is affected.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_ERROR    16

/**
 * Something somehow does not look correct. This may or may not
 * lead to problems. An example would be the use of '-vstrict -2'.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_WARNING  24

/**
 * Standard information.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_INFO     32

/**
 * Detailed information.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_VERBOSE  40

/**
 * Stuff which is only useful for libav* developers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_DEBUG    48

/**
 * Extremely verbose debugging, useful for libav* development.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_TRACE    56

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_MAX_ਵਿੱਥ (AV_LOG_TRACE - AV_LOG_QUIET)

/**
 * @}
 */

/**
 * Sets additional colors for extended debugging sessions.
 * @code
   av_log(ctx, AV_LOG_DEBUG|AV_LOG_C(134), "Message in purple\n");
   @endcode
 * Requires 256color terminal support. Uses outside debugging is not
 * recommended.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_C(x) ((x) << 8)

/**
 * Send the specified message to the log if the level is less than or equal
 * to the current av_log_level. By default, all logging messages are sent to
 * stderr. This behavior can be altered by setting a different logging callback
 * function.
 * @see av_log_set_callback
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct or NULL if general log.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 */
ਖਾਲੀ av_log(ਖਾਲੀ *avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, ...) av_printf_format(3, 4);

/**
 * Send the specified message to the log once with the initial_level and then with
 * the subsequent_level. By default, all logging messages are sent to
 * stderr. This behavior can be altered by setting a different logging callback
 * function.
 * @see av_log
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct or NULL if general log.
 * @param initial_level importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant" for the first occurrence.
 * @param subsequent_level importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant" after the first occurrence.
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 * @param state a variable to keep trak of if a message has already been printed
 *        this must be initialized to 0 before the first use. The same state
 *        must not be accessed by 2 Threads simultaneously.
 */
ਖਾਲੀ av_log_once(ਖਾਲੀ* avcl, ਪੂਰਨ initial_level, ਪੂਰਨ subsequent_level, ਪੂਰਨ *state, ਅਚਲ ਅੱਖਰ *fmt, ...) av_printf_format(5, 6);


/**
 * Send the specified message to the log if the level is less than or equal
 * to the current av_log_level. By default, all logging messages are sent to
 * stderr. This behavior can be altered by setting a different logging callback
 * function.
 * @see av_log_set_callback
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 * @param vl The arguments referenced by the format string.
 */
ਖਾਲੀ av_vlog(ਖਾਲੀ *avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl);

/**
 * Get the current log level
 *
 * @see lavu_log_constants
 *
 * @return Current log level
 */
ਪੂਰਨ av_log_get_level(ਖਾਲੀ);

/**
 * Set the log level
 *
 * @see lavu_log_constants
 *
 * @param level Logging level
 */
ਖਾਲੀ av_log_ਸੈੱਟ_level(ਪੂਰਨ level);

/**
 * Set the logging callback
 *
 * @note The callback must be thread safe, even if the application does not use
 *       threads itself as some codecs are multithreaded.
 *
 * @see av_log_default_callback
 *
 * @param callback A logging function with a compatible signature.
 */
ਖਾਲੀ av_log_ਸੈੱਟ_callback(ਖਾਲੀ (*callback)(ਖਾਲੀ*, ਪੂਰਨ, ਅਚਲ ਅੱਖਰ*, va_list));

/**
 * Default logging callback
 *
 * It prints the message to stderr, optionally colorizing it.
 *
 * @param avcl A pointer to an arbitrary struct of which the first field is a
 *        pointer to an AVClass struct.
 * @param level The importance level of the message expressed using a @ref
 *        lavu_log_constants "Logging Constant".
 * @param fmt The format string (printf-compatible) that specifies how
 *        subsequent arguments are converted to output.
 * @param vl The arguments referenced by the format string.
 */
ਖਾਲੀ av_log_default_callback(ਖਾਲੀ *avcl, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt,
                             va_list vl);

/**
 * Return the context name
 *
 * @param  ctx The AVClass context
 *
 * @return The AVClass class_name
 */
ਅਚਲ ਅੱਖਰ* av_default_ਵਸਤੂ_name(ਖਾਲੀ* ctx);
AVClassCategory av_default_get_category(ਖਾਲੀ *ptr);

/**
 * Format a line of log the same way as the default callback.
 * @param line          buffer to receive the formatted line
 * @param line_size     size of the buffer
 * @param print_prefix  used to store whether the prefix must be printed;
 *                      must point to a persistent integer initially set to 1
 */
ਖਾਲੀ av_log_format_ਸਤਰ(ਖਾਲੀ *ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl,
                        ਅੱਖਰ *ਸਤਰ, ਪੂਰਨ ਸਤਰ_ਮਾਪ, ਪੂਰਨ *print_ਅਗੇਤਰ);

/**
 * Format a line of log the same way as the default callback.
 * @param line          buffer to receive the formatted line;
 *                      may be NULL if line_size is 0
 * @param line_size     size of the buffer; at most line_size-1 characters will
 *                      be written to the buffer, plus one null terminator
 * @param print_prefix  used to store whether the prefix must be printed;
 *                      must point to a persistent integer initially set to 1
 * @return Returns a negative value if an error occurred, otherwise returns
 *         the number of characters that would have been written for a
 *         sufficiently large buffer, not including the terminating null
 *         character. If the return value is not less than line_size, it means
 *         that the log message was truncated to fit the buffer.
 */
ਪੂਰਨ av_log_format_line2(ਖਾਲੀ *ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl,
                        ਅੱਖਰ *ਸਤਰ, ਪੂਰਨ ਸਤਰ_ਮਾਪ, ਪੂਰਨ *print_ਅਗੇਤਰ);

/**
 * Skip repeated messages, this requires the user app to use av_log() instead of
 * (f)printf as the 2 would otherwise interfere and lead to
 * "Last message repeated x times" messages below (f)printf messages with some
 * bad luck.
 * Also to receive the last, "last repeated" line if any, the user app must
 * call av_log(NULL, AV_LOG_QUIET, "%s", ""); at the end
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_SKIP_REPEATED 1

/**
 * Include the log severity in messages originating from codecs.
 *
 * Results in messages such as:
 * [rawvideo @ 0xDEADBEEF] [error] encode did not produce valid pts
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_PRINT_LEVEL 2

/**
 * Include system time in log output.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_PRINT_ਸਮਾਂ 4

/**
 * Include system date and time in log output.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LOG_PRINT_DATETIME 8

ਖਾਲੀ av_log_ਸੈੱਟ_flags(ਪੂਰਨ arg);
ਪੂਰਨ av_log_get_flags(ਖਾਲੀ);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_LOG_H */
