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

#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVTree_ਗੰਢ {
    ਬਣਤਰ AVTree_ਗੰਢ *ਬੱਚਾ[2];
    ਖਾਲੀ *elem;
    ਪੂਰਨ state;
} AVTree_ਗੰਢ;

ਅਚਲ ਪੂਰਨ av_ਰੁੱਖ_ਗੰਢ_ਮਾਪ = ਆਕਾਰ(AVTree_ਗੰਢ);

ਬਣਤਰ AVTree_ਗੰਢ *av_ਰੁੱਖ_ਗੰਢ_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVTree_ਗੰਢ));
}

ਖਾਲੀ *av_ਰੁੱਖ_ਲੱਭੋ(ਅਚਲ AVTree_ਗੰਢ *t, ਖਾਲੀ *ਕੁੰਜੀ,
                   ਪੂਰਨ (*cmp)(ਅਚਲ ਖਾਲੀ *ਕੁੰਜੀ, ਅਚਲ ਖਾਲੀ *b), ਖਾਲੀ *ਅਗਲਾ[2])
{
    ਜੇ (t) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v = cmp(ਕੁੰਜੀ, t->elem);
        ਜੇ (v) {
            ਜੇ (ਅਗਲਾ)
                ਅਗਲਾ[v >> 31] = t->elem;
            ਵਾਪਸ av_ਰੁੱਖ_ਲੱਭੋ(t->ਬੱਚਾ[(v >> 31) ^ 1], ਕੁੰਜੀ, cmp, ਅਗਲਾ);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (ਅਗਲਾ) {
                av_ਰੁੱਖ_ਲੱਭੋ(t->ਬੱਚਾ[0], ਕੁੰਜੀ, cmp, ਅਗਲਾ);
                av_ਰੁੱਖ_ਲੱਭੋ(t->ਬੱਚਾ[1], ਕੁੰਜੀ, cmp, ਅਗਲਾ);
            }
            ਵਾਪਸ t->elem;
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ *av_ਰੁੱਖ_ਪਾਓ(AVTree_ਗੰਢ **tp, ਖਾਲੀ *ਕੁੰਜੀ,
                     ਪੂਰਨ (*cmp)(ਅਚਲ ਖਾਲੀ *ਕੁੰਜੀ, ਅਚਲ ਖਾਲੀ *b), AVTree_ਗੰਢ **ਅਗਲਾ)
{
    AVTree_ਗੰਢ *t = *tp;
    ਜੇ (t) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v = cmp(t->elem, ਕੁੰਜੀ);
        ਖਾਲੀ *ret;
        ਜੇ (!v) {
            ਜੇ (*ਅਗਲਾ)
                ਵਾਪਸ t->elem;
            ਨਹੀਂਤਾਂ ਜੇ (t->ਬੱਚਾ[0] || t->ਬੱਚਾ[1]) {
                ਪੂਰਨ i = !t->ਬੱਚਾ[0];
                ਖਾਲੀ *ਅਗਲਾ_elem[2];
                av_ਰੁੱਖ_ਲੱਭੋ(t->ਬੱਚਾ[i], ਕੁੰਜੀ, cmp, ਅਗਲਾ_elem);
                ਕੁੰਜੀ = t->elem = ਅਗਲਾ_elem[i];
                v   = -i;
            } ਨਹੀਂਤਾਂ {
                *ਅਗਲਾ = t;
                *tp   = ਨਿਰਾ;
                ਵਾਪਸ ਨਿਰਾ;
            }
        }
        ret = av_ਰੁੱਖ_ਪਾਓ(&t->ਬੱਚਾ[v >> 31], ਕੁੰਜੀ, cmp, ਅਗਲਾ);
        ਜੇ (!ret) {
            ਪੂਰਨ i              = (v >> 31) ^ !!*ਅਗਲਾ;
            AVTree_ਗੰਢ **ਬੱਚਾ = &t->ਬੱਚਾ[i];
            t->state += 2 * i - 1;

            ਜੇ (!(t->state & 1)) {
                ਜੇ (t->state) {
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
                    ਜੇ ((*ਬੱਚਾ)->state * 2 == -t->state) {
                        *tp                    = (*ਬੱਚਾ)->ਬੱਚਾ[i ^ 1];
                        (*ਬੱਚਾ)->ਬੱਚਾ[i ^ 1] = (*tp)->ਬੱਚਾ[i];
                        (*tp)->ਬੱਚਾ[i]        = *ਬੱਚਾ;
                        *ਬੱਚਾ                 = (*tp)->ਬੱਚਾ[i ^ 1];
                        (*tp)->ਬੱਚਾ[i ^ 1]    = t;

                        (*tp)->ਬੱਚਾ[0]->state = -((*tp)->state > 0);
                        (*tp)->ਬੱਚਾ[1]->state = (*tp)->state < 0;
                        (*tp)->state           = 0;
                    } ਨਹੀਂਤਾਂ {
                        *tp                 = *ਬੱਚਾ;
                        *ਬੱਚਾ              = (*ਬੱਚਾ)->ਬੱਚਾ[i ^ 1];
                        (*tp)->ਬੱਚਾ[i ^ 1] = t;
                        ਜੇ ((*tp)->state)
                            t->state = 0;
                        ਨਹੀਂਤਾਂ
                            t->state >>= 1;
                        (*tp)->state = -t->state;
                    }
                }
            }
            ਜੇ (!(*tp)->state ^ !!*ਅਗਲਾ)
                ਵਾਪਸ ਕੁੰਜੀ;
        }
        ਵਾਪਸ ret;
    } ਨਹੀਂਤਾਂ {
        *tp   = *ਅਗਲਾ;
        *ਅਗਲਾ = ਨਿਰਾ;
        ਜੇ (*tp) {
            (*tp)->elem = ਕੁੰਜੀ;
            ਵਾਪਸ ਨਿਰਾ;
        } ਨਹੀਂਤਾਂ
            ਵਾਪਸ ਕੁੰਜੀ;
    }
}

ਖਾਲੀ av_ਰੁੱਖ_destroy(AVTree_ਗੰਢ *t)
{
    ਜੇ (t) {
        av_ਰੁੱਖ_destroy(t->ਬੱਚਾ[0]);
        av_ਰੁੱਖ_destroy(t->ਬੱਚਾ[1]);
        av_free(t);
    }
}

ਖਾਲੀ av_ਰੁੱਖ_enumerate(AVTree_ਗੰਢ *t, ਖਾਲੀ *opaque,
                       ਪੂਰਨ (*cmp)(ਖਾਲੀ *opaque, ਖਾਲੀ *elem),
                       ਪੂਰਨ (*enu)(ਖਾਲੀ *opaque, ਖਾਲੀ *elem))
{
    ਜੇ (t) {
        ਪੂਰਨ v = cmp ? cmp(opaque, t->elem) : 0;
        ਜੇ (v >= 0)
            av_ਰੁੱਖ_enumerate(t->ਬੱਚਾ[0], opaque, cmp, enu);
        ਜੇ (v == 0)
            enu(opaque, t->elem);
        ਜੇ (v <= 0)
            av_ਰੁੱਖ_enumerate(t->ਬੱਚਾ[1], opaque, cmp, enu);
    }
}
