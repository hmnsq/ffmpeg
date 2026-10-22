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

#समावेश "error.h"
#समावेश "log.h"
#समावेश "mem.h"
#समावेश "tree.h"

प्रकार काष्ठा AVTree_गाँठ {
    काष्ठा AVTree_गाँठ *child[2];
    व्योम *elem;
    पूर्णांक state;
} AVTree_गाँठ;

स्थिर पूर्णांक av_वृक्ष_गाँठ_आकार = माप(AVTree_गाँठ);

काष्ठा AVTree_गाँठ *av_वृक्ष_गाँठ_alloc(व्योम)
{
    वापस av_mallocz(माप(काष्ठा AVTree_गाँठ));
}

व्योम *av_वृक्ष_find(स्थिर AVTree_गाँठ *t, व्योम *कुंजी,
                   पूर्णांक (*cmp)(स्थिर व्योम *कुंजी, स्थिर व्योम *b), व्योम *अग्र[2])
{
    अगर (t) {
        अचिन्हित पूर्णांक v = cmp(कुंजी, t->elem);
        अगर (v) {
            अगर (अग्र)
                अग्र[v >> 31] = t->elem;
            वापस av_वृक्ष_find(t->child[(v >> 31) ^ 1], कुंजी, cmp, अग्र);
        } अन्यथा {
            अगर (अग्र) {
                av_वृक्ष_find(t->child[0], कुंजी, cmp, अग्र);
                av_वृक्ष_find(t->child[1], कुंजी, cmp, अग्र);
            }
            वापस t->elem;
        }
    }
    वापस शून्य;
}

व्योम *av_वृक्ष_जोड़ो(AVTree_गाँठ **tp, व्योम *कुंजी,
                     पूर्णांक (*cmp)(स्थिर व्योम *कुंजी, स्थिर व्योम *b), AVTree_गाँठ **अग्र)
{
    AVTree_गाँठ *t = *tp;
    अगर (t) {
        अचिन्हित पूर्णांक v = cmp(t->elem, कुंजी);
        व्योम *ret;
        अगर (!v) {
            अगर (*अग्र)
                वापस t->elem;
            अन्यथा अगर (t->child[0] || t->child[1]) {
                पूर्णांक i = !t->child[0];
                व्योम *अग्र_elem[2];
                av_वृक्ष_find(t->child[i], कुंजी, cmp, अग्र_elem);
                कुंजी = t->elem = अग्र_elem[i];
                v   = -i;
            } अन्यथा {
                *अग्र = t;
                *tp   = शून्य;
                वापस शून्य;
            }
        }
        ret = av_वृक्ष_जोड़ो(&t->child[v >> 31], कुंजी, cmp, अग्र);
        अगर (!ret) {
            पूर्णांक i              = (v >> 31) ^ !!*अग्र;
            AVTree_गाँठ **child = &t->child[i];
            t->state += 2 * i - 1;

            अगर (!(t->state & 1)) {
                अगर (t->state) {
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
                    अगर ((*child)->state * 2 == -t->state) {
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
                        अगर ((*tp)->state)
                            t->state = 0;
                        अन्यथा
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            अगर (!(*tp)->state ^ !!*अग्र)
                वापस कुंजी;
        }
        वापस ret;
    } अन्यथा {
        *tp   = *अग्र;
        *अग्र = शून्य;
        अगर (*tp) {
            (*tp)->elem = कुंजी;
            वापस शून्य;
        } अन्यथा
            वापस कुंजी;
    }
}

व्योम av_वृक्ष_destroy(AVTree_गाँठ *t)
{
    अगर (t) {
        av_वृक्ष_destroy(t->child[0]);
        av_वृक्ष_destroy(t->child[1]);
        av_free(t);
    }
}

व्योम av_वृक्ष_enumerate(AVTree_गाँठ *t, व्योम *opaque,
                       पूर्णांक (*cmp)(व्योम *opaque, व्योम *elem),
                       पूर्णांक (*enu)(व्योम *opaque, व्योम *elem))
{
    अगर (t) {
        पूर्णांक v = cmp ? cmp(opaque, t->elem) : 0;
        अगर (v >= 0)
            av_वृक्ष_enumerate(t->child[0], opaque, cmp, enu);
        अगर (v == 0)
            enu(opaque, t->elem);
        अगर (v <= 0)
            av_वृक्ष_enumerate(t->child[1], opaque, cmp, enu);
    }
}
