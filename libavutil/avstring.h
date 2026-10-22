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

#यदि_अपरिभाषितम् AVUTIL_AVSTRING_H
#परिभाषय AVUTIL_AVSTRING_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव "attributes.h"

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
पूर्णाङ्क av_strstart(ध्रुव वर्ण *str, ध्रुव वर्ण *pfx, ध्रुव वर्ण **ptr);

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
पूर्णाङ्क av_stristart(ध्रुव वर्ण *str, ध्रुव वर्ण *pfx, ध्रुव वर्ण **ptr);

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
वर्ण *av_stristr(ध्रुव वर्ण *haystack, ध्रुव वर्ण *needle);

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
वर्ण *av_strnstr(ध्रुव वर्ण *haystack, ध्रुव वर्ण *needle, size_t hay_दीर्घता);

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
size_t av_strlcpy(वर्ण *dst, ध्रुव वर्ण *src, size_t आकार);

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
size_t av_strlcat(वर्ण *dst, ध्रुव वर्ण *src, size_t आकार);

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
size_t av_strlcatf(वर्ण *dst, size_t आकार, ध्रुव वर्ण *fmt, ...) av_printf_format(3, 4);

/**
 * Get the count of continuous non zero chars starting from the beginning.
 *
 * @param s   the string whose length to count
 * @param len maximum number of characters to check in the string, that
 *            is the maximum value which is returned by the function
 */
स्थिर अन्तःस्थ size_t av_strnlen(ध्रुव वर्ण *s, size_t len)
{
    size_t i;
    प्रति (i = 0; i < len && s[i]; i++)
        ;
    प्रत्यागम i;
}

/**
 * Print arguments following specified format into a large enough auto
 * allocated buffer. It is similar to GNU asprintf().
 * @param fmt printf-compatible format string, specifying how the
 *            following parameters are used.
 * @return the allocated string
 * @note You have to free the string yourself with av_free().
 */
वर्ण *av_asprintf(ध्रुव वर्ण *fmt, ...) av_printf_format(1, 2);

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
वर्ण *av_get_token(ध्रुव वर्ण **buf, ध्रुव वर्ण *पदांशः);

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
वर्ण *av_strtok(वर्ण *s, ध्रुव वर्ण *delim, वर्ण **saveptr);

/**
 * Locale-independent conversion of ASCII isdigit.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_isdigit(पूर्णाङ्क c)
{
    प्रत्यागम c >= '0' && c <= '9';
}

/**
 * Locale-independent conversion of ASCII isgraph.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_isgraph(पूर्णाङ्क c)
{
    प्रत्यागम c > 32 && c < 127;
}

/**
 * Locale-independent conversion of ASCII isspace.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_isspace(पूर्णाङ्क c)
{
    प्रत्यागम c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
           c == '\v';
}

/**
 * Locale-independent conversion of ASCII characters to uppercase.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_toupper(पूर्णाङ्क c)
{
    यदि (c >= 'a' && c <= 'z')
        c ^= 0x20;
    प्रत्यागम c;
}

/**
 * Locale-independent conversion of ASCII characters to lowercase.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_tolower(पूर्णाङ्क c)
{
    यदि (c >= 'A' && c <= 'Z')
        c ^= 0x20;
    प्रत्यागम c;
}

/**
 * Locale-independent conversion of ASCII isxdigit.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_isxdigit(पूर्णाङ्क c)
{
    c = av_tolower(c);
    प्रत्यागम av_isdigit(c) || (c >= 'a' && c <= 'f');
}

/**
 * Locale-independent case-insensitive compare.
 * @note This means only ASCII-range characters are case-insensitive
 */
पूर्णाङ्क av_strcasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b);

/**
 * Locale-independent case-insensitive compare.
 * @note This means only ASCII-range characters are case-insensitive
 */
पूर्णाङ्क av_strncasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b, size_t n);

/**
 * Locale-independent strings replace.
 * @note This means only ASCII-range characters are replaced.
 */
वर्ण *av_strireplace(ध्रुव वर्ण *str, ध्रुव वर्ण *from, ध्रुव वर्ण *गन्तव्यम्);

/**
 * Thread safe basename.
 * @param path the string to parse, on DOS both \ and / are considered separators.
 * @return pointer to the basename substring.
 * If path does not contain a slash, the function returns a copy of path.
 * If path is a NULL pointer or points to an empty string, a pointer
 * to a string "." is returned.
 */
ध्रुव वर्ण *av_basename(ध्रुव वर्ण *मार्गः);

/**
 * Thread safe dirname.
 * @param path the string to parse, on DOS both \ and / are considered separators.
 * @return A pointer to a string that's the parent directory of path.
 * If path is a NULL pointer or points to an empty string, a pointer
 * to a string "." is returned.
 * @note the function may modify the contents of the path, so copies should be passed.
 */
ध्रुव वर्ण *av_dirname(वर्ण *मार्गः);

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
पूर्णाङ्क av_मेलनम्_name(ध्रुव वर्ण *name, ध्रुव वर्ण *नामानि);

/**
 * Append path component to the existing path.
 * Path separator '/' is placed between when needed.
 * Resulting string have to be freed with av_free().
 * @param path      base path
 * @param component component to be appended
 * @return new path or NULL on error.
 */
वर्ण *av_append_मार्गः_component(ध्रुव वर्ण *मार्गः, ध्रुव वर्ण *component);

गणना AVEscape_बहुलकम् {
    AV_ESCAPE_बहुलकम्_AUTO,      ///< Use auto-selected escaping mode.
    AV_ESCAPE_बहुलकम्_BACKSLASH, ///< Use backslash escaping.
    AV_ESCAPE_बहुलकम्_QUOTE,     ///< Use single-quote escaping.
    AV_ESCAPE_बहुलकम्_XML,       ///< Use XML non-markup character data escaping.
};

/**
 * Consider spaces special and escape them even in the middle of the
 * string.
 *
 * This is equivalent to adding the whitespace characters to the special
 * characters lists, except it is guaranteed to use the exact same list
 * of whitespace characters as the rest of libavutil.
 */
#परिभाषय AV_ESCAPE_FLAG_WHITESPACE (1 << 0)

/**
 * Escape only specified special characters.
 * Without this flag, escape also any characters that may be considered
 * special by av_get_token(), such as the single quote.
 */
#परिभाषय AV_ESCAPE_FLAG_STRICT (1 << 1)

/**
 * Within AV_ESCAPE_MODE_XML, additionally escape single quotes for single
 * quoted attributes.
 */
#परिभाषय AV_ESCAPE_FLAG_XML_SINGLE_QUOTES (1 << 2)

/**
 * Within AV_ESCAPE_MODE_XML, additionally escape double quotes for double
 * quoted attributes.
 */
#परिभाषय AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES (1 << 3)


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
av_warn_अप्रयुक्तम्_परिणाम
पूर्णाङ्क av_escape(वर्ण **dst, ध्रुव वर्ण *src, ध्रुव वर्ण *special_chars,
              गणना AVEscape_बहुलकम् बहुलकम्, पूर्णाङ्क flags);

#परिभाषय AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES          1 ///< accept codepoints over 0x10FFFF
#परिभाषय AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS             2 ///< accept non-characters - 0xFFFE and 0xFFFF
#परिभाषय AV_UTF8_FLAG_ACCEPT_SURROGATES                 4 ///< accept UTF-16 surrogates codes
#परिभाषय AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES 8 ///< exclude control codes not accepted by XML

#परिभाषय AV_UTF8_FLAG_ACCEPT_ALL \
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
av_warn_अप्रयुक्तम्_परिणाम
पूर्णाङ्क av_utf8_decode(int32_t *codep, ध्रुव uint8_t **bufp, ध्रुव uint8_t *buf_अन्तः,
                   अचिह्नित पूर्णाङ्क flags);

/**
 * Check if a name is in a list.
 * @returns 0 if not found, or the 1 based index where it has been found in the
 *            list.
 */
पूर्णाङ्क av_मेलनम्_list(ध्रुव वर्ण *name, ध्रुव वर्ण *list, वर्ण separator);

/**
 * See libc sscanf manual for more information.
 * Locale-independent sscanf implementation.
 */
पूर्णाङ्क av_sscanf(ध्रुव वर्ण *string, ध्रुव वर्ण *format, ...) av_scanf_format(2, 3);

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_AVSTRING_H */
