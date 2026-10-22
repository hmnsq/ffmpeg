/*
 * Copyright (c) 2002 Michael Niedermayer <michaelni@gmx.at>
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
 * simple arithmetic expression evaluator
 */

#ifndef AVUTIL_EVAL_H
#define AVUTIL_EVAL_H

प्रकारनिर्देश संरचना AVExpr AVExpr;

/**
 * Parse and evaluate an expression.
 * Note, this is significantly slower than av_expr_eval().
 *
 * @param res a pointer to a double where is put the result value of
 * the expression, or NAN in case of error
 * @param s expression as a zero terminated string, for example "1+2^3+5*5+sin(2/3)"
 * @param const_names NULL terminated array of zero terminated strings of constant identifiers, for example {"PI", "E", 0}
 * @param const_values a zero terminated array of values for the identifiers from const_names
 * @param func1_names NULL terminated array of zero terminated strings of funcs1 identifiers
 * @param funcs1 NULL terminated array of function pointers for functions which take 1 argument
 * @param func2_names NULL terminated array of zero terminated strings of funcs2 identifiers
 * @param funcs2 NULL terminated array of function pointers for functions which take 2 arguments
 * @param opaque a pointer which will be passed to all functions from funcs1 and funcs2
 * @param log_offset log level offset, can be used to silence error messages
 * @param log_ctx parent logging context
 * @return >= 0 in case of success, a negative value corresponding to an
 * AVERROR code otherwise
 */
पूर्णाङ्क av_अभिव्यक्ति_parse_and_eval(द्विगुण *res, अचर वर्ण *s,
                           अचर वर्ण * अचर *const_names, अचर द्विगुण *const_मानहरू,
                           अचर वर्ण * अचर *func1_names, द्विगुण (* अचर *funcs1)(शून्य *, द्विगुण),
                           अचर वर्ण * अचर *func2_names, द्विगुण (* अचर *funcs2)(शून्य *, द्विगुण, द्विगुण),
                           शून्य *opaque, पूर्णाङ्क log_offset, शून्य *log_ctx);

/**
 * Parse an expression.
 *
 * @param expr a pointer where is put an AVExpr containing the parsed
 * value in case of successful parsing, or NULL otherwise.
 * The pointed to AVExpr must be freed with av_expr_free() by the user
 * when it is not needed anymore.
 * @param s expression as a zero terminated string, for example "1+2^3+5*5+sin(2/3)"
 * @param const_names NULL terminated array of zero terminated strings of constant identifiers, for example {"PI", "E", 0}
 * @param func1_names NULL terminated array of zero terminated strings of funcs1 identifiers
 * @param funcs1 NULL terminated array of function pointers for functions which take 1 argument
 * @param func2_names NULL terminated array of zero terminated strings of funcs2 identifiers
 * @param funcs2 NULL terminated array of function pointers for functions which take 2 arguments
 * @param log_offset log level offset, can be used to silence error messages
 * @param log_ctx parent logging context
 * @return >= 0 in case of success, a negative value corresponding to an
 * AVERROR code otherwise
 */
पूर्णाङ्क av_अभिव्यक्ति_parse(AVExpr **अभिव्यक्ति, अचर वर्ण *s,
                  अचर वर्ण * अचर *const_names,
                  अचर वर्ण * अचर *func1_names, द्विगुण (* अचर *funcs1)(शून्य *, द्विगुण),
                  अचर वर्ण * अचर *func2_names, द्विगुण (* अचर *funcs2)(शून्य *, द्विगुण, द्विगुण),
                  पूर्णाङ्क log_offset, शून्य *log_ctx);

/**
 * Evaluate a previously parsed expression.
 *
 * @param e the AVExpr to evaluate
 * @param const_values a zero terminated array of values for the identifiers from av_expr_parse() const_names
 * @param opaque a pointer which will be passed to all functions from funcs1 and funcs2
 * @return the value of the expression
 */
द्विगुण av_अभिव्यक्ति_eval(AVExpr *e, अचर द्विगुण *const_मानहरू, शून्य *opaque);

/**
 * Track the presence of variables and their number of occurrences in a parsed expression
 *
 * @param e the AVExpr to track variables in
 * @param counter a zero-initialized array where the count of each variable will be stored
 * @param size size of array
 * @return 0 on success, a negative value indicates that no expression or array was passed
 * or size was zero
 */
पूर्णाङ्क av_अभिव्यक्ति_गन्ती_vars(AVExpr *e, अचिन्हित *counter, पूर्णाङ्क size);

/**
 * Track the presence of user provided functions and their number of occurrences
 * in a parsed expression.
 *
 * @param e the AVExpr to track user provided functions in
 * @param counter a zero-initialized array where the count of each function will be stored
 *                if you passed 5 functions with 2 arguments to av_expr_parse()
 *                then for arg=2 this will use up to 5 entries.
 * @param size size of array
 * @param arg number of arguments the counted functions have
 * @return 0 on success, a negative value indicates that no expression or array was passed
 * or size was zero
 */
पूर्णाङ्क av_अभिव्यक्ति_गन्ती_func(AVExpr *e, अचिन्हित *counter, पूर्णाङ्क size, पूर्णाङ्क arg);

/**
 * Free a parsed expression previously created with av_expr_parse().
 */
शून्य av_अभिव्यक्ति_free(AVExpr *e);

/**
 * Parse the string in numstr and return its value as a double. If
 * the string is empty, contains only whitespaces, or does not contain
 * an initial substring that has the expected syntax for a
 * floating-point number, no conversion is performed. In this case,
 * returns a value of zero and the value returned in tail is the value
 * of numstr.
 *
 * @param numstr a string representing a number, may contain one of
 * the International System number postfixes, for example 'K', 'M',
 * 'G'. If 'i' is appended after the postfix, powers of 2 are used
 * instead of powers of 10. The 'B' postfix multiplies the value by
 * 8, and can be appended after another postfix or used alone. This
 * allows using for example 'KB', 'MiB', 'G' and 'B' as postfix.
 * @param tail if non-NULL puts here the pointer to the char next
 * after the last parsed character
 */
द्विगुण av_strtod(अचर वर्ण *numstr, वर्ण **tail);

#endif /* AVUTIL_EVAL_H */
