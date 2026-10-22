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

#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "tree.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVTree_ଗଣ୍ଠି {
    ସଂରଚନା AVTree_ଗଣ୍ଠି *child[2];
    ଶୂନ୍ୟ *elem;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା state;
} AVTree_ଗଣ୍ଠି;

ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_ବୃକ୍ଷ_ଗଣ୍ଠି_size = ଆକାର(AVTree_ଗଣ୍ଠି);

ସଂରଚନା AVTree_ଗଣ୍ଠି *av_ବୃକ୍ଷ_ଗଣ୍ଠି_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mallocz(ଆକାର(ସଂରଚନା AVTree_ଗଣ୍ଠି));
}

ଶୂନ୍ୟ *av_ବୃକ୍ଷ_find(ଅଚଳ AVTree_ଗଣ୍ଠି *t, ଶୂନ୍ୟ *ଚାବି,
                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*cmp)(ଅଚଳ ଶୂନ୍ୟ *ଚାବି, ଅଚଳ ଶୂନ୍ୟ *b), ଶୂନ୍ୟ *next[2])
{
    ଯଦି (t) {
        unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା v = cmp(ଚାବି, t->elem);
        ଯଦି (v) {
            ଯଦି (next)
                next[v >> 31] = t->elem;
            ଫେରନ୍ତୁ av_ବୃକ୍ଷ_find(t->child[(v >> 31) ^ 1], ଚାବି, cmp, next);
        } ଅନ୍ୟଥା {
            ଯଦି (next) {
                av_ବୃକ୍ଷ_find(t->child[0], ଚାବି, cmp, next);
                av_ବୃକ୍ଷ_find(t->child[1], ଚାବି, cmp, next);
            }
            ଫେରନ୍ତୁ t->elem;
        }
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ *av_ବୃକ୍ଷ_ଭର୍ତ୍ତି(AVTree_ଗଣ୍ଠି **tp, ଶୂନ୍ୟ *ଚାବି,
                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*cmp)(ଅଚଳ ଶୂନ୍ୟ *ଚାବି, ଅଚଳ ଶୂନ୍ୟ *b), AVTree_ଗଣ୍ଠି **next)
{
    AVTree_ଗଣ୍ଠି *t = *tp;
    ଯଦି (t) {
        unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା v = cmp(t->elem, ଚାବି);
        ଶୂନ୍ୟ *ret;
        ଯଦି (!v) {
            ଯଦି (*next)
                ଫେରନ୍ତୁ t->elem;
            ଅନ୍ୟଥା ଯଦି (t->child[0] || t->child[1]) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = !t->child[0];
                ଶୂନ୍ୟ *next_elem[2];
                av_ବୃକ୍ଷ_find(t->child[i], ଚାବି, cmp, next_elem);
                ଚାବି = t->elem = next_elem[i];
                v   = -i;
            } ଅନ୍ୟଥା {
                *next = t;
                *tp   = ଖାଲି;
                ଫେରନ୍ତୁ ଖାଲି;
            }
        }
        ret = av_ବୃକ୍ଷ_ଭର୍ତ୍ତି(&t->child[v >> 31], ଚାବି, cmp, next);
        ଯଦି (!ret) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i              = (v >> 31) ^ !!*next;
            AVTree_ଗଣ୍ଠି **child = &t->child[i];
            t->state += 2 * i - 1;

            ଯଦି (!(t->state & 1)) {
                ଯଦି (t->state) {
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
                    ଯଦି ((*child)->state * 2 == -t->state) {
                        *tp                    = (*child)->child[i ^ 1];
                        (*child)->child[i ^ 1] = (*tp)->child[i];
                        (*tp)->child[i]        = *child;
                        *child                 = (*tp)->child[i ^ 1];
                        (*tp)->child[i ^ 1]    = t;

                        (*tp)->child[0]->state = -((*tp)->state > 0);
                        (*tp)->child[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ଅନ୍ୟଥା {
                        *tp                 = *child;
                        *child              = (*child)->child[i ^ 1];
                        (*tp)->child[i ^ 1] = t;
                        ଯଦି ((*tp)->state)
                            t->state = 0;
                        ଅନ୍ୟଥା
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ଯଦି (!(*tp)->state ^ !!*next)
                ଫେରନ୍ତୁ ଚାବି;
        }
        ଫେରନ୍ତୁ ret;
    } ଅନ୍ୟଥା {
        *tp   = *next;
        *next = ଖାଲି;
        ଯଦି (*tp) {
            (*tp)->elem = ଚାବି;
            ଫେରନ୍ତୁ ଖାଲି;
        } ଅନ୍ୟଥା
            ଫେରନ୍ତୁ ଚାବି;
    }
}

ଶୂନ୍ୟ av_ବୃକ୍ଷ_destroy(AVTree_ଗଣ୍ଠି *t)
{
    ଯଦି (t) {
        av_ବୃକ୍ଷ_destroy(t->child[0]);
        av_ବୃକ୍ଷ_destroy(t->child[1]);
        av_free(t);
    }
}

ଶୂନ୍ୟ av_ବୃକ୍ଷ_enumerate(AVTree_ଗଣ୍ଠି *t, ଶୂନ୍ୟ *opaque,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*cmp)(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *elem),
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*enu)(ଶୂନ୍ୟ *opaque, ଶୂନ୍ୟ *elem))
{
    ଯଦି (t) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା v = cmp ? cmp(opaque, t->elem) : 0;
        ଯଦି (v >= 0)
            av_ବୃକ୍ଷ_enumerate(t->child[0], opaque, cmp, enu);
        ଯଦି (v == 0)
            enu(opaque, t->elem);
        ଯଦି (v <= 0)
            av_ବୃକ୍ଷ_enumerate(t->child[1], opaque, cmp, enu);
    }
}
