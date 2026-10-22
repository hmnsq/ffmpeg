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

#అన్తర్భావ "error.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "tree.h"

రకనిర్వచనం నిర్మాణం AVTree_కణుపు {
    నిర్మాణం AVTree_కణుపు *బిడ్డ[2];
    శూన్య *elem;
    పూర్ణాంకం state;
} AVTree_కణుపు;

స్థిరరాశి పూర్ణాంకం av_వృక్షం_కణుపు_కొలత = పరిమాణం(AVTree_కణుపు);

నిర్మాణం AVTree_కణుపు *av_వృక్షం_కణుపు_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVTree_కణుపు));
}

శూన్య *av_వృక్షం_కనుగొను(స్థిరరాశి AVTree_కణుపు *t, శూన్య *కీలకం,
                   పూర్ణాంకం (*cmp)(స్థిరరాశి శూన్య *కీలకం, స్థిరరాశి శూన్య *b), శూన్య *తదుపరి[2])
{
    ఒకవేళ (t) {
        గుర్తులేని పూర్ణాంకం v = cmp(కీలకం, t->elem);
        ఒకవేళ (v) {
            ఒకవేళ (తదుపరి)
                తదుపరి[v >> 31] = t->elem;
            తిరిగి av_వృక్షం_కనుగొను(t->బిడ్డ[(v >> 31) ^ 1], కీలకం, cmp, తదుపరి);
        } లేకపోతే {
            ఒకవేళ (తదుపరి) {
                av_వృక్షం_కనుగొను(t->బిడ్డ[0], కీలకం, cmp, తదుపరి);
                av_వృక్షం_కనుగొను(t->బిడ్డ[1], కీలకం, cmp, తదుపరి);
            }
            తిరిగి t->elem;
        }
    }
    తిరిగి ఖాళీ;
}

శూన్య *av_వృక్షం_చొప్పించు(AVTree_కణుపు **tp, శూన్య *కీలకం,
                     పూర్ణాంకం (*cmp)(స్థిరరాశి శూన్య *కీలకం, స్థిరరాశి శూన్య *b), AVTree_కణుపు **తదుపరి)
{
    AVTree_కణుపు *t = *tp;
    ఒకవేళ (t) {
        గుర్తులేని పూర్ణాంకం v = cmp(t->elem, కీలకం);
        శూన్య *ret;
        ఒకవేళ (!v) {
            ఒకవేళ (*తదుపరి)
                తిరిగి t->elem;
            లేకపోతే ఒకవేళ (t->బిడ్డ[0] || t->బిడ్డ[1]) {
                పూర్ణాంకం i = !t->బిడ్డ[0];
                శూన్య *తదుపరి_elem[2];
                av_వృక్షం_కనుగొను(t->బిడ్డ[i], కీలకం, cmp, తదుపరి_elem);
                కీలకం = t->elem = తదుపరి_elem[i];
                v   = -i;
            } లేకపోతే {
                *తదుపరి = t;
                *tp   = ఖాళీ;
                తిరిగి ఖాళీ;
            }
        }
        ret = av_వృక్షం_చొప్పించు(&t->బిడ్డ[v >> 31], కీలకం, cmp, తదుపరి);
        ఒకవేళ (!ret) {
            పూర్ణాంకం i              = (v >> 31) ^ !!*తదుపరి;
            AVTree_కణుపు **బిడ్డ = &t->బిడ్డ[i];
            t->state += 2 * i - 1;

            ఒకవేళ (!(t->state & 1)) {
                ఒకవేళ (t->state) {
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
                    ఒకవేళ ((*బిడ్డ)->state * 2 == -t->state) {
                        *tp                    = (*బిడ్డ)->బిడ్డ[i ^ 1];
                        (*బిడ్డ)->బిడ్డ[i ^ 1] = (*tp)->బిడ్డ[i];
                        (*tp)->బిడ్డ[i]        = *బిడ్డ;
                        *బిడ్డ                 = (*tp)->బిడ్డ[i ^ 1];
                        (*tp)->బిడ్డ[i ^ 1]    = t;

                        (*tp)->బిడ్డ[0]->state = -((*tp)->state > 0);
                        (*tp)->బిడ్డ[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } లేకపోతే {
                        *tp                 = *బిడ్డ;
                        *బిడ్డ              = (*బిడ్డ)->బిడ్డ[i ^ 1];
                        (*tp)->బిడ్డ[i ^ 1] = t;
                        ఒకవేళ ((*tp)->state)
                            t->state = 0;
                        లేకపోతే
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ఒకవేళ (!(*tp)->state ^ !!*తదుపరి)
                తిరిగి కీలకం;
        }
        తిరిగి ret;
    } లేకపోతే {
        *tp   = *తదుపరి;
        *తదుపరి = ఖాళీ;
        ఒకవేళ (*tp) {
            (*tp)->elem = కీలకం;
            తిరిగి ఖాళీ;
        } లేకపోతే
            తిరిగి కీలకం;
    }
}

శూన్య av_వృక్షం_destroy(AVTree_కణుపు *t)
{
    ఒకవేళ (t) {
        av_వృక్షం_destroy(t->బిడ్డ[0]);
        av_వృక్షం_destroy(t->బిడ్డ[1]);
        av_free(t);
    }
}

శూన్య av_వృక్షం_enumerate(AVTree_కణుపు *t, శూన్య *opaque,
                       పూర్ణాంకం (*cmp)(శూన్య *opaque, శూన్య *elem),
                       పూర్ణాంకం (*enu)(శూన్య *opaque, శూన్య *elem))
{
    ఒకవేళ (t) {
        పూర్ణాంకం v = cmp ? cmp(opaque, t->elem) : 0;
        ఒకవేళ (v >= 0)
            av_వృక్షం_enumerate(t->బిడ్డ[0], opaque, cmp, enu);
        ఒకవేళ (v == 0)
            enu(opaque, t->elem);
        ఒకవేళ (v <= 0)
            av_వృక్షం_enumerate(t->బిడ్డ[1], opaque, cmp, enu);
    }
}
