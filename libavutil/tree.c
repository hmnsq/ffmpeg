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

#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "tree.h"

തരനിർവചനം ഘടന AVTree_കണ്ണി {
    ഘടന AVTree_കണ്ണി *child[2];
    ശൂന്യം *elem;
    പൂർണ്ണസംഖ്യ state;
} AVTree_കണ്ണി;

സ്ഥിരം പൂർണ്ണസംഖ്യ av_വൃക്ഷം_കണ്ണി_size = വലുപ്പം(AVTree_കണ്ണി);

ഘടന AVTree_കണ്ണി *av_വൃക്ഷം_കണ്ണി_alloc(ശൂന്യം)
{
    തിരികെ av_mallocz(വലുപ്പം(ഘടന AVTree_കണ്ണി));
}

ശൂന്യം *av_വൃക്ഷം_find(സ്ഥിരം AVTree_കണ്ണി *t, ശൂന്യം *താക്കോൽ,
                   പൂർണ്ണസംഖ്യ (*cmp)(സ്ഥിരം ശൂന്യം *താക്കോൽ, സ്ഥിരം ശൂന്യം *b), ശൂന്യം *next[2])
{
    എങ്കിൽ (t) {
        unsigned പൂർണ്ണസംഖ്യ v = cmp(താക്കോൽ, t->elem);
        എങ്കിൽ (v) {
            എങ്കിൽ (next)
                next[v >> 31] = t->elem;
            തിരികെ av_വൃക്ഷം_find(t->child[(v >> 31) ^ 1], താക്കോൽ, cmp, next);
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (next) {
                av_വൃക്ഷം_find(t->child[0], താക്കോൽ, cmp, next);
                av_വൃക്ഷം_find(t->child[1], താക്കോൽ, cmp, next);
            }
            തിരികെ t->elem;
        }
    }
    തിരികെ ശൂന്യ;
}

ശൂന്യം *av_വൃക്ഷം_തിരുകുക(AVTree_കണ്ണി **tp, ശൂന്യം *താക്കോൽ,
                     പൂർണ്ണസംഖ്യ (*cmp)(സ്ഥിരം ശൂന്യം *താക്കോൽ, സ്ഥിരം ശൂന്യം *b), AVTree_കണ്ണി **next)
{
    AVTree_കണ്ണി *t = *tp;
    എങ്കിൽ (t) {
        unsigned പൂർണ്ണസംഖ്യ v = cmp(t->elem, താക്കോൽ);
        ശൂന്യം *ret;
        എങ്കിൽ (!v) {
            എങ്കിൽ (*next)
                തിരികെ t->elem;
            അല്ലെങ്കിൽ എങ്കിൽ (t->child[0] || t->child[1]) {
                പൂർണ്ണസംഖ്യ i = !t->child[0];
                ശൂന്യം *next_elem[2];
                av_വൃക്ഷം_find(t->child[i], താക്കോൽ, cmp, next_elem);
                താക്കോൽ = t->elem = next_elem[i];
                v   = -i;
            } അല്ലെങ്കിൽ {
                *next = t;
                *tp   = ശൂന്യ;
                തിരികെ ശൂന്യ;
            }
        }
        ret = av_വൃക്ഷം_തിരുകുക(&t->child[v >> 31], താക്കോൽ, cmp, next);
        എങ്കിൽ (!ret) {
            പൂർണ്ണസംഖ്യ i              = (v >> 31) ^ !!*next;
            AVTree_കണ്ണി **child = &t->child[i];
            t->state += 2 * i - 1;

            എങ്കിൽ (!(t->state & 1)) {
                എങ്കിൽ (t->state) {
                    /* The following code is equivalent to
                     * if ((*child)->state * 2 == -t->state)
                     *     rotate(child, i ^ 1);
                     * rotate(tp, i);
                     *
                     * with rotate():
                     * static void rotate(AVTreeNode **tp, int i)
                     * {
                     *     AVTreeNode *t= *tp;
                     *
                     *     *tp = t->child[i];
                     *     t->child[i] = t->child[i]->child[i ^ 1];
                     *     (*tp)->child[i ^ 1] = t;
                     *     i = 4 * t->state + 2 * (*tp)->state + 12;
                     *     t->state     = ((0x614586 >> i) & 3) - 1;
                     *     (*tp)->state = ((0x400EEA >> i) & 3) - 1 +
                     *                    ((*tp)->state >> 1);
                     * }
                     * but such a rotate function is both bigger and slower
                     */
                    എങ്കിൽ ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } അല്ലെങ്കിൽ {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        എങ്കിൽ ((*tp)->state)
                            t->state = 0;
                        അല്ലെങ്കിൽ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            എങ്കിൽ (!(*tp)->state ^ !!*next)
                തിരികെ താക്കോൽ;
        }
        തിരികെ ret;
    } അല്ലെങ്കിൽ {
        *tp   = *next;
        *next = ശൂന്യ;
        എങ്കിൽ (*tp) {
            (*tp)->elem = താക്കോൽ;
            തിരികെ ശൂന്യ;
        } അല്ലെങ്കിൽ
            തിരികെ താക്കോൽ;
    }
}

ശൂന്യം av_വൃക്ഷം_destroy(AVTree_കണ്ണി *t)
{
    എങ്കിൽ (t) {
        av_വൃക്ഷം_destroy(t->child[0]);
        av_വൃക്ഷം_destroy(t->child[1]);
        av_free(t);
    }
}

ശൂന്യം av_വൃക്ഷം_enumerate(AVTree_കണ്ണി *t, ശൂന്യം *opaque,
                       പൂർണ്ണസംഖ്യ (*cmp)(ശൂന്യം *opaque, ശൂന്യം *elem),
                       പൂർണ്ണസംഖ്യ (*enu)(ശൂന്യം *opaque, ശൂന്യം *elem))
{
    എങ്കിൽ (t) {
        പൂർണ്ണസംഖ്യ v = cmp ? cmp(opaque, t->elem) : 0;
        എങ്കിൽ (v >= 0)
            av_വൃക്ഷം_enumerate(t->child[0], opaque, cmp, enu);
        എങ്കിൽ (v == 0)
            enu(opaque, t->elem);
        എങ്കിൽ (v <= 0)
            av_വൃക്ഷം_enumerate(t->child[1], opaque, cmp, enu);
    }
}
