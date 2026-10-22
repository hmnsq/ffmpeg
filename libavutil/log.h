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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_LOG_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_LOG_H

#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "version.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ {
    AV_CLASS_CATEGORY_NA = 0,
    AV_CLASS_CATEGORY_ಒಳಹರಿವು,
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
    AV_CLASS_CATEGORY_DEVICE_VIDEO_ಒಳಹರಿವು,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_ಒಳಹರಿವು,
    AV_CLASS_CATEGORY_DEVICE_OUTPUT,
    AV_CLASS_CATEGORY_DEVICE_ಒಳಹರಿವು,
    AV_CLASS_CATEGORY_NB  ///< not part of ABI/API
}AVClassCategory;

ಎಣಿಕೆ AVClassStateFlags {
    /**
     * Object initialization has finished and it is now in the 'runtime' stage.
     * This affects e.g. what options can be set on the object (only
     * AV_OPT_FLAG_RUNTIME_PARAM options can be set on initialized objects).
     */
    AV_CLASS_STATE_INITIALIZED         = (1 << 0),
};

#ವ್ಯಾಖ್ಯಾನಿಸು AV_IS_ಒಳಹರಿವು_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_ಒಳಹರಿವು) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_ಒಳಹರಿವು) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_ಒಳಹರಿವು))

#ವ್ಯಾಖ್ಯಾನಿಸು AV_IS_OUTPUT_DEVICE(category) \
    (((category) == AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT) || \
     ((category) == AV_CLASS_CATEGORY_DEVICE_OUTPUT))

ರಚನೆ AVOptionRanges;

/**
 * Describe the class of an AVClass context structure. That is an
 * arbitrary struct of which the first field is a pointer to an
 * AVClass struct (e.g. AVCodecContext, AVFormatContext etc.).
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVClass {
    /**
     * The name of the class; usually it is the same name as the
     * context structure type to which the AVClass is associated.
     */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* class_name;

    /**
     * A pointer to a function which returns the name of a context
     * instance ctx associated with the class.
     */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* (*ಅಂಶ_name)(ಶೂನ್ಯ* ctx);

    /**
     * An array of options for the structure or NULL.
     * When non-NULL, the array must be terminated by an option with a NULL
     * name.
     *
     * @see av_set_default_options()
     */
    ಸ್ಥಿರಾಂಕ ರಚನೆ AVOption *option;

    /**
     * LIBAVUTIL_VERSION with which this structure was created.
     * This is used to allow fields to be added to AVClass without requiring
     * major version bumps everywhere.
     */

    ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ;

    /**
     * Offset in the structure where the log level offset is stored. The log
     * level offset is an int added to the log level for logging with this
     * object as the context.
     *
     * 0 means there is no such variable.
     */
    ಪೂರ್ಣಾಂಕ log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ;

    /**
     * Offset in the structure where a pointer to the parent context for
     * logging is stored. For example a decoder could pass its AVCodecContext
     * to eval as such a parent context, which an ::av_log() implementation
     * could then leverage to display the parent context.
     *
     * When the pointer is NULL, or this offset is zero, the object is assumed
     * to have no parent.
     */
    ಪೂರ್ಣಾಂಕ ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ;

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
    AVClassCategory (*get_category)(ಶೂನ್ಯ* ctx);

    /**
     * Callback to return the supported/allowed ranges.
     */
    ಪೂರ್ಣಾಂಕ (*query_ranges)(ರಚನೆ AVOptionRanges **, ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ flags);

    /**
     * Return next AVOptions-enabled child or NULL
     */
    ಶೂನ್ಯ* (*ಮಗು_ಮುಂದಿನ)(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev);

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
    ಸ್ಥಿರಾಂಕ ರಚನೆ AVClass* (*ಮಗು_class_iterate)(ಶೂನ್ಯ **iter);

    /**
     * When non-zero, offset in the object to an unsigned int holding object
     * state flags, a combination of AVClassStateFlags values. The flags are
     * updated by the object to signal its state to the generic code.
     *
     * Added in version 59.41.100.
     */
    ಪೂರ್ಣಾಂಕ state_flags_ಸ್ಥಾನಾಂತರ;
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
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_QUIET    -8

/**
 * Something went really wrong and we will crash now.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_PANIC     0

/**
 * Something went wrong and recovery is not possible.
 * For example, no header was found for a format which depends
 * on headers or an illegal combination of parameters is used.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_FATAL     8

/**
 * Something went wrong and cannot losslessly be recovered.
 * However, not all future data is affected.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_ERROR    16

/**
 * Something somehow does not look correct. This may or may not
 * lead to problems. An example would be the use of '-vstrict -2'.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_WARNING  24

/**
 * Standard information.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_INFO     32

/**
 * Detailed information.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_VERBOSE  40

/**
 * Stuff which is only useful for libav* developers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_DEBUG    48

/**
 * Extremely verbose debugging, useful for libav* development.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_TRACE    56

#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_MAX_ಸ್ಥಾನಾಂತರ (AV_LOG_TRACE - AV_LOG_QUIET)

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
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_C(x) ((x) << 8)

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
ಶೂನ್ಯ av_log(ಶೂನ್ಯ *avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...) av_printf_format(3, 4);

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
ಶೂನ್ಯ av_log_once(ಶೂನ್ಯ* avcl, ಪೂರ್ಣಾಂಕ initial_level, ಪೂರ್ಣಾಂಕ subsequent_level, ಪೂರ್ಣಾಂಕ *state, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...) av_printf_format(5, 6);


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
ಶೂನ್ಯ av_vlog(ಶೂನ್ಯ *avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl);

/**
 * Get the current log level
 *
 * @see lavu_log_constants
 *
 * @return Current log level
 */
ಪೂರ್ಣಾಂಕ av_log_get_level(ಶೂನ್ಯ);

/**
 * Set the log level
 *
 * @see lavu_log_constants
 *
 * @param level Logging level
 */
ಶೂನ್ಯ av_log_ಗಣ_level(ಪೂರ್ಣಾಂಕ level);

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
ಶೂನ್ಯ av_log_ಗಣ_callback(ಶೂನ್ಯ (*callback)(ಶೂನ್ಯ*, ಪೂರ್ಣಾಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*, va_list));

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
ಶೂನ್ಯ av_log_default_callback(ಶೂನ್ಯ *avcl, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt,
                             va_list vl);

/**
 * Return the context name
 *
 * @param  ctx The AVClass context
 *
 * @return The AVClass class_name
 */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* av_default_ಅಂಶ_name(ಶೂನ್ಯ* ctx);
AVClassCategory av_default_get_category(ಶೂನ್ಯ *ptr);

/**
 * Format a line of log the same way as the default callback.
 * @param line          buffer to receive the formatted line
 * @param line_size     size of the buffer
 * @param print_prefix  used to store whether the prefix must be printed;
 *                      must point to a persistent integer initially set to 1
 */
ಶೂನ್ಯ av_log_format_ಸಾಲು(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl,
                        ಅಕ್ಷರ *ಸಾಲು, ಪೂರ್ಣಾಂಕ ಸಾಲು_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ *print_ಪೂರ್ವಪ್ರತ್ಯಯ);

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
ಪೂರ್ಣಾಂಕ av_log_format_line2(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl,
                        ಅಕ್ಷರ *ಸಾಲು, ಪೂರ್ಣಾಂಕ ಸಾಲು_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ *print_ಪೂರ್ವಪ್ರತ್ಯಯ);

/**
 * Skip repeated messages, this requires the user app to use av_log() instead of
 * (f)printf as the 2 would otherwise interfere and lead to
 * "Last message repeated x times" messages below (f)printf messages with some
 * bad luck.
 * Also to receive the last, "last repeated" line if any, the user app must
 * call av_log(NULL, AV_LOG_QUIET, "%s", ""); at the end
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_SKIP_REPEATED 1

/**
 * Include the log severity in messages originating from codecs.
 *
 * Results in messages such as:
 * [rawvideo @ 0xDEADBEEF] [error] encode did not produce valid pts
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_PRINT_LEVEL 2

/**
 * Include system time in log output.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_PRINT_ಸಮಯ 4

/**
 * Include system date and time in log output.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LOG_PRINT_DATETIME 8

ಶೂನ್ಯ av_log_ಗಣ_flags(ಪೂರ್ಣಾಂಕ arg);
ಪೂರ್ಣಾಂಕ av_log_get_flags(ಶೂನ್ಯ);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_LOG_H */
