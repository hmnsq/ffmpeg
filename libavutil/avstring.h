/*
 * Copyright (c) 2007 Mans Rullgard
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

#ifndef AVUTIL_AVSTRING_H
#define AVUTIL_AVSTRING_H

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن "attributes.h"

/**
 * @addtogroup lavu_string
 * @{
 */

/**
 * Return non-zero if pfx is a prefix of str. If it is, *ptr is set to
 * the address of the first character in str after the prefix.
 *
 * @param str input string
 * @param pfx prefix to test
 * @param ptr updated if the prefix is matched inside str
 * @return non-zero if the prefix matches, zero otherwise
 */
صحيح av_strstart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr);

/**
 * Return non-zero if pfx is a prefix of str independent of case. If
 * it is, *ptr is set to the address of the first character in str
 * after the prefix.
 *
 * @param str input string
 * @param pfx prefix to test
 * @param ptr updated if the prefix is matched inside str
 * @return non-zero if the prefix matches, zero otherwise
 */
صحيح av_stristart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr);

/**
 * Locate the first case-independent occurrence in the string haystack
 * of the string needle.  A zero-length string needle is considered to
 * match at the start of haystack.
 *
 * This function is a case-insensitive version of the standard strstr().
 *
 * @param haystack string to search in
 * @param needle   string to search for
 * @return         pointer to the located match within haystack
 *                 or a null pointer if no match
 */
حرف *av_stristr(ثابت حرف *haystack, ثابت حرف *needle);

/**
 * Locate the first occurrence of the string needle in the string haystack
 * where not more than hay_length characters are searched. A zero-length
 * string needle is considered to match at the start of haystack.
 *
 * This function is a length-limited version of the standard strstr().
 *
 * @param haystack   string to search in
 * @param needle     string to search for
 * @param hay_length length of string to search in
 * @return           pointer to the located match within haystack
 *                   or a null pointer if no match
 */
حرف *av_strnstr(ثابت حرف *haystack, ثابت حرف *needle, size_t hay_length);

/**
 * Copy the string src to dst, but no more than size - 1 bytes, and
 * null-terminate dst.
 *
 * This function is the same as BSD strlcpy().
 *
 * @param dst destination buffer
 * @param src source string
 * @param size size of destination buffer
 * @return the length of src
 *
 * @warning since the return value is the length of src, src absolutely
 * _must_ be a properly 0-terminated string, otherwise this will read beyond
 * the end of the buffer and possibly crash.
 */
size_t av_strlcpy(حرف *dst, ثابت حرف *src, size_t size);

/**
 * Append the string src to the string dst, but to a total length of
 * no more than size - 1 bytes, and null-terminate dst.
 *
 * This function is similar to BSD strlcat(), but differs when
 * size <= strlen(dst).
 *
 * @param dst destination buffer
 * @param src source string
 * @param size size of destination buffer
 * @return the total length of src and dst
 *
 * @warning since the return value use the length of src and dst, these
 * absolutely _must_ be a properly 0-terminated strings, otherwise this
 * will read beyond the end of the buffer and possibly crash.
 */
size_t av_strlcat(حرف *dst, ثابت حرف *src, size_t size);

/**
 * Append output to a string, according to a format. Never write out of
 * the destination buffer, and always put a terminating 0 within
 * the buffer.
 * @param dst destination buffer (string to which the output is
 *  appended)
 * @param size total size of the destination buffer
 * @param fmt printf-compatible format string, specifying how the
 *  following parameters are used
 * @return the length of the string that would have been generated
 *  if enough space had been available
 */
size_t av_strlcatf(حرف *dst, size_t size, ثابت حرف *fmt, ...) av_printf_format(3, 4);

/**
 * Get the count of continuous non zero chars starting from the beginning.
 *
 * @param s   the string whose length to count
 * @param len maximum number of characters to check in the string, that
 *            is the maximum value which is returned by the function
 */
ساكن مضمن size_t av_strnlen(ثابت حرف *s, size_t len)
{
    size_t i;
    لكل (i = 0; i < len && s[i]; i++)
        ;
    أرجع i;
}

/**
 * Print arguments following specified format into a large enough auto
 * allocated buffer. It is similar to GNU asprintf().
 * @param fmt printf-compatible format string, specifying how the
 *            following parameters are used.
 * @return the allocated string
 * @note You have to free the string yourself with av_free().
 */
حرف *av_asprintf(ثابت حرف *fmt, ...) av_printf_format(1, 2);

/**
 * Unescape the given string until a non escaped terminating char,
 * and return the token corresponding to the unescaped string.
 *
 * The normal \ and ' escaping is supported. Leading and trailing
 * whitespaces are removed, unless they are escaped with '\' or are
 * enclosed between ''.
 *
 * @param buf the buffer to parse, buf will be updated to point to the
 * terminating char
 * @param term a 0-terminated list of terminating chars
 * @return the malloced unescaped string, which must be av_freed by
 * the user, NULL in case of allocation failure
 */
حرف *av_get_token(ثابت حرف **buf, ثابت حرف *term);

/**
 * Split the string into several tokens which can be accessed by
 * successive calls to av_strtok().
 *
 * A token is defined as a sequence of characters not belonging to the
 * set specified in delim.
 *
 * On the first call to av_strtok(), s should point to the string to
 * parse, and the value of saveptr is ignored. In subsequent calls, s
 * should be NULL, and saveptr should be unchanged since the previous
 * call.
 *
 * This function is similar to strtok_r() defined in POSIX.1.
 *
 * @param s the string to parse, may be NULL
 * @param delim 0-terminated list of token delimiters, must be non-NULL
 * @param saveptr user-provided pointer which points to stored
 * information necessary for av_strtok() to continue scanning the same
 * string. saveptr is updated to point to the next character after the
 * first delimiter found, or to NULL if the string was terminated
 * @return the found token, or NULL when no token is found
 */
حرف *av_strtok(حرف *s, ثابت حرف *delim, حرف **saveptr);

/**
 * Locale-independent conversion of ASCII isdigit.
 */
ساكن مضمن av_const صحيح av_isdigit(صحيح c)
{
    أرجع c >= '0' && c <= '9';
}

/**
 * Locale-independent conversion of ASCII isgraph.
 */
ساكن مضمن av_const صحيح av_isgraph(صحيح c)
{
    أرجع c > 32 && c < 127;
}

/**
 * Locale-independent conversion of ASCII isspace.
 */
ساكن مضمن av_const صحيح av_isspace(صحيح c)
{
    أرجع c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
           c == '\v';
}

/**
 * Locale-independent conversion of ASCII characters to uppercase.
 */
ساكن مضمن av_const صحيح av_toupper(صحيح c)
{
    𐤀𐤌 (c >= 'a' && c <= 'z')
        c ^= 0x20;
    أرجع c;
}

/**
 * Locale-independent conversion of ASCII characters to lowercase.
 */
ساكن مضمن av_const صحيح av_tolower(صحيح c)
{
    𐤀𐤌 (c >= 'A' && c <= 'Z')
        c ^= 0x20;
    أرجع c;
}

/**
 * Locale-independent conversion of ASCII isxdigit.
 */
ساكن مضمن av_const صحيح av_isxdigit(صحيح c)
{
    c = av_tolower(c);
    أرجع av_isdigit(c) || (c >= 'a' && c <= 'f');
}

/**
 * Locale-independent case-insensitive compare.
 * @note This means only ASCII-range characters are case-insensitive
 */
صحيح av_strcasecmp(ثابت حرف *a, ثابت حرف *b);

/**
 * Locale-independent case-insensitive compare.
 * @note This means only ASCII-range characters are case-insensitive
 */
صحيح av_strncasecmp(ثابت حرف *a, ثابت حرف *b, size_t n);

/**
 * Locale-independent strings replace.
 * @note This means only ASCII-range characters are replaced.
 */
حرف *av_strireplace(ثابت حرف *str, ثابت حرف *from, ثابت حرف *to);

/**
 * Thread safe basename.
 * @param path the string to parse, on DOS both \ and / are considered separators.
 * @return pointer to the basename substring.
 * If path does not contain a slash, the function returns a copy of path.
 * If path is a NULL pointer or points to an empty string, a pointer
 * to a string "." is returned.
 */
ثابت حرف *av_basename(ثابت حرف *path);

/**
 * Thread safe dirname.
 * @param path the string to parse, on DOS both \ and / are considered separators.
 * @return A pointer to a string that's the parent directory of path.
 * If path is a NULL pointer or points to an empty string, a pointer
 * to a string "." is returned.
 * @note the function may modify the contents of the path, so copies should be passed.
 */
ثابت حرف *av_dirname(حرف *path);

/**
 * Match instances of a name in a comma-separated list of names.
 * List entries are checked from the start to the end of the names list,
 * the first match ends further processing. If an entry prefixed with '-'
 * matches, then 0 is returned. The "ALL" list entry is considered to
 * match all names.
 *
 * @param name  Name to look for.
 * @param names List of names.
 * @return 1 on match, 0 otherwise.
 */
صحيح av_match_name(ثابت حرف *name, ثابت حرف *names);

/**
 * Append path component to the existing path.
 * Path separator '/' is placed between when needed.
 * Resulting string have to be freed with av_free().
 * @param path      base path
 * @param component component to be appended
 * @return new path or NULL on error.
 */
حرف *av_append_path_component(ثابت حرف *path, ثابت حرف *component);

تعداد AVEscapeMode {
    AV_ESCAPE_MODE_AUTO,      ///< Use auto-selected escaping mode.
    AV_ESCAPE_MODE_BACKSLASH, ///< Use backslash escaping.
    AV_ESCAPE_MODE_QUOTE,     ///< Use single-quote escaping.
    AV_ESCAPE_MODE_XML,       ///< Use XML non-markup character data escaping.
};

/**
 * Consider spaces special and escape them even in the middle of the
 * string.
 *
 * This is equivalent to adding the whitespace characters to the special
 * characters lists, except it is guaranteed to use the exact same list
 * of whitespace characters as the rest of libavutil.
 */
#define AV_ESCAPE_FLAG_WHITESPACE (1 << 0)

/**
 * Escape only specified special characters.
 * Without this flag, escape also any characters that may be considered
 * special by av_get_token(), such as the single quote.
 */
#define AV_ESCAPE_FLAG_STRICT (1 << 1)

/**
 * Within AV_ESCAPE_MODE_XML, additionally escape single quotes for single
 * quoted attributes.
 */
#define AV_ESCAPE_FLAG_XML_SINGLE_QUOTES (1 << 2)

/**
 * Within AV_ESCAPE_MODE_XML, additionally escape double quotes for double
 * quoted attributes.
 */
#define AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES (1 << 3)


/**
 * Escape string in src, and put the escaped string in an allocated
 * string in *dst, which must be freed with av_free().
 *
 * @param dst           pointer where an allocated string is put
 * @param src           string to escape, must be non-NULL
 * @param special_chars string containing the special characters which
 *                      need to be escaped, can be NULL
 * @param mode          escape mode to employ, see AV_ESCAPE_MODE_* macros.
 *                      Any unknown value for mode will be considered equivalent to
 *                      AV_ESCAPE_MODE_BACKSLASH, but this behaviour can change without
 *                      notice.
 * @param flags         flags which control how to escape, see AV_ESCAPE_FLAG_ macros
 * @return the length of the allocated string, or a negative error code in case of error
 * @see av_bprint_escape()
 */
av_warn_unused_result
صحيح av_escape(حرف **dst, ثابت حرف *src, ثابت حرف *special_chars,
              تعداد AVEscapeMode mode, صحيح flags);

#define AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES          1 ///< accept codepoints over 0x10FFFF
#define AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS             2 ///< accept non-characters - 0xFFFE and 0xFFFF
#define AV_UTF8_FLAG_ACCEPT_SURROGATES                 4 ///< accept UTF-16 surrogates codes
#define AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES 8 ///< exclude control codes not accepted by XML

#define AV_UTF8_FLAG_ACCEPT_ALL \
    AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES|AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS|AV_UTF8_FLAG_ACCEPT_SURROGATES

/**
 * Read and decode a single UTF-8 code point (character) from the
 * buffer in *buf, and update *buf to point to the next byte to
 * decode.
 *
 * In case of an invalid byte sequence, the pointer will be updated to
 * the next byte after the invalid sequence and the function will
 * return an error code.
 *
 * Depending on the specified flags, the function will also fail in
 * case the decoded code point does not belong to a valid range.
 *
 * @note For speed-relevant code a carefully implemented use of
 * GET_UTF8() may be preferred.
 *
 * @param codep   pointer used to return the parsed code in case of success.
 *                The value in *codep is set even in case the range check fails.
 * @param bufp    pointer to the address the first byte of the sequence
 *                to decode, updated by the function to point to the
 *                byte next after the decoded sequence
 * @param buf_end pointer to the end of the buffer, points to the next
 *                byte past the last in the buffer. This is used to
 *                avoid buffer overreads (in case of an unfinished
 *                UTF-8 sequence towards the end of the buffer).
 * @param flags   a collection of AV_UTF8_FLAG_* flags
 * @return >= 0 in case a sequence was successfully read, a negative
 * value in case of invalid sequence
 */
av_warn_unused_result
صحيح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_end,
                   unsigned صحيح flags);

/**
 * Check if a name is in a list.
 * @returns 0 if not found, or the 1 based index where it has been found in the
 *            list.
 */
صحيح av_match_list(ثابت حرف *name, ثابت حرف *list, حرف separator);

/**
 * See libc sscanf manual for more information.
 * Locale-independent sscanf implementation.
 */
صحيح av_sscanf(ثابت حرف *string, ثابت حرف *format, ...) av_scanf_format(2, 3);

/**
 * @}
 */

#endif /* AVUTIL_AVSTRING_H */
