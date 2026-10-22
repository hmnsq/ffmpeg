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

#अन्तर्भाव "error.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "tree.h"

प्रकारनिर्देश संरचना AVTree_गाँठो {
    संरचना AVTree_गाँठो *child[2];
    शून्य *elem;
    पूर्णाङ्क state;
} AVTree_गाँठो;

अचर पूर्णाङ्क av_रूख_गाँठो_size = परिमाण(AVTree_गाँठो);

संरचना AVTree_गाँठो *av_रूख_गाँठो_alloc(शून्य)
{
    फर्काऊ av_mallocz(परिमाण(संरचना AVTree_गाँठो));
}

शून्य *av_रूख_find(अचर AVTree_गाँठो *t, शून्य *साँचो,
                   पूर्णाङ्क (*cmp)(अचर शून्य *साँचो, अचर शून्य *b), शून्य *next[2])
{
    यदि (t) {
        अचिन्हित पूर्णाङ्क v = cmp(साँचो, t->elem);
        यदि (v) {
            यदि (next)
                next[v >> 31] = t->elem;
            फर्काऊ av_रूख_find(t->child[(v >> 31) ^ 1], साँचो, cmp, next);
        } अन्यथा {
            यदि (next) {
                av_रूख_find(t->child[0], साँचो, cmp, next);
                av_रूख_find(t->child[1], साँचो, cmp, next);
            }
            फर्काऊ t->elem;
        }
    }
    फर्काऊ रिक्त;
}

शून्य *av_रूख_घुसाउ(AVTree_गाँठो **tp, शून्य *साँचो,
                     पूर्णाङ्क (*cmp)(अचर शून्य *साँचो, अचर शून्य *b), AVTree_गाँठो **next)
{
    AVTree_गाँठो *t = *tp;
    यदि (t) {
        अचिन्हित पूर्णाङ्क v = cmp(t->elem, साँचो);
        शून्य *ret;
        यदि (!v) {
            यदि (*next)
                फर्काऊ t->elem;
            अन्यथा यदि (t->child[0] || t->child[1]) {
                पूर्णाङ्क i = !t->child[0];
                शून्य *next_elem[2];
                av_रूख_find(t->child[i], साँचो, cmp, next_elem);
                साँचो = t->elem = next_elem[i];
                v   = -i;
            } अन्यथा {
                *next = t;
                *tp   = रिक्त;
                फर्काऊ रिक्त;
            }
        }
        ret = av_रूख_घुसाउ(&t->child[v >> 31], साँचो, cmp, next);
        यदि (!ret) {
            पूर्णाङ्क i              = (v >> 31) ^ !!*next;
            AVTree_गाँठो **child = &t->child[i];
            t->state += 2 * i - 1;

            यदि (!(t->state & 1)) {
                यदि (t->state) {
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
                    यदि ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } अन्यथा {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        यदि ((*tp)->state)
                            t->state = 0;
                        अन्यथा
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            यदि (!(*tp)->state ^ !!*next)
                फर्काऊ साँचो;
        }
        फर्काऊ ret;
    } अन्यथा {
        *tp   = *next;
        *next = रिक्त;
        यदि (*tp) {
            (*tp)->elem = साँचो;
            फर्काऊ रिक्त;
        } अन्यथा
            फर्काऊ साँचो;
    }
}

शून्य av_रूख_destroy(AVTree_गाँठो *t)
{
    यदि (t) {
        av_रूख_destroy(t->child[0]);
        av_रूख_destroy(t->child[1]);
        av_free(t);
    }
}

शून्य av_रूख_enumerate(AVTree_गाँठो *t, शून्य *opaque,
                       पूर्णाङ्क (*cmp)(शून्य *opaque, शून्य *elem),
                       पूर्णाङ्क (*enu)(शून्य *opaque, शून्य *elem))
{
    यदि (t) {
        पूर्णाङ्क v = cmp ? cmp(opaque, t->elem) : 0;
        यदि (v >= 0)
            av_रूख_enumerate(t->child[0], opaque, cmp, enu);
        यदि (v == 0)
            enu(opaque, t->elem);
        यदि (v <= 0)
            av_रूख_enumerate(t->child[1], opaque, cmp, enu);
    }
}
