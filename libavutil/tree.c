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

प्रकारव्याख्या संरचना AVTree_गाठ {
    संरचना AVTree_गाठ *child[2];
    शून्य *elem;
    पूर्णांक state;
} AVTree_गाठ;

स्थिरांक पूर्णांक av_वृक्ष_गाठ_size = आकार(AVTree_गाठ);

संरचना AVTree_गाठ *av_वृक्ष_गाठ_alloc(शून्य)
{
    परत av_mallocz(आकार(संरचना AVTree_गाठ));
}

शून्य *av_वृक्ष_find(स्थिरांक AVTree_गाठ *t, शून्य *किल्ली,
                   पूर्णांक (*cmp)(स्थिरांक शून्य *किल्ली, स्थिरांक शून्य *b), शून्य *next[2])
{
    जर (t) {
        अचिन्हित पूर्णांक v = cmp(किल्ली, t->elem);
        जर (v) {
            जर (next)
                next[v >> 31] = t->elem;
            परत av_वृक्ष_find(t->child[(v >> 31) ^ 1], किल्ली, cmp, next);
        } अन्यथा {
            जर (next) {
                av_वृक्ष_find(t->child[0], किल्ली, cmp, next);
                av_वृक्ष_find(t->child[1], किल्ली, cmp, next);
            }
            परत t->elem;
        }
    }
    परत रिक्त;
}

शून्य *av_वृक्ष_घाला(AVTree_गाठ **tp, शून्य *किल्ली,
                     पूर्णांक (*cmp)(स्थिरांक शून्य *किल्ली, स्थिरांक शून्य *b), AVTree_गाठ **next)
{
    AVTree_गाठ *t = *tp;
    जर (t) {
        अचिन्हित पूर्णांक v = cmp(t->elem, किल्ली);
        शून्य *ret;
        जर (!v) {
            जर (*next)
                परत t->elem;
            अन्यथा जर (t->child[0] || t->child[1]) {
                पूर्णांक i = !t->child[0];
                शून्य *next_elem[2];
                av_वृक्ष_find(t->child[i], किल्ली, cmp, next_elem);
                किल्ली = t->elem = next_elem[i];
                v   = -i;
            } अन्यथा {
                *next = t;
                *tp   = रिक्त;
                परत रिक्त;
            }
        }
        ret = av_वृक्ष_घाला(&t->child[v >> 31], किल्ली, cmp, next);
        जर (!ret) {
            पूर्णांक i              = (v >> 31) ^ !!*next;
            AVTree_गाठ **child = &t->child[i];
            t->state += 2 * i - 1;

            जर (!(t->state & 1)) {
                जर (t->state) {
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
                    जर ((*child)->state * 2 == -t->state) {
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
                        जर ((*tp)->state)
                            t->state = 0;
                        अन्यथा
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            जर (!(*tp)->state ^ !!*next)
                परत किल्ली;
        }
        परत ret;
    } अन्यथा {
        *tp   = *next;
        *next = रिक्त;
        जर (*tp) {
            (*tp)->elem = किल्ली;
            परत रिक्त;
        } अन्यथा
            परत किल्ली;
    }
}

शून्य av_वृक्ष_destroy(AVTree_गाठ *t)
{
    जर (t) {
        av_वृक्ष_destroy(t->child[0]);
        av_वृक्ष_destroy(t->child[1]);
        av_free(t);
    }
}

शून्य av_वृक्ष_enumerate(AVTree_गाठ *t, शून्य *opaque,
                       पूर्णांक (*cmp)(शून्य *opaque, शून्य *elem),
                       पूर्णांक (*enu)(शून्य *opaque, शून्य *elem))
{
    जर (t) {
        पूर्णांक v = cmp ? cmp(opaque, t->elem) : 0;
        जर (v >= 0)
            av_वृक्ष_enumerate(t->child[0], opaque, cmp, enu);
        जर (v == 0)
            enu(opaque, t->elem);
        जर (v <= 0)
            av_वृक्ष_enumerate(t->child[1], opaque, cmp, enu);
    }
}
