/*
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

/*
 * Test the stdatomic.h interface as used by FFmpeg, against whichever
 * implementation configure selected, the native one or the compat fallback.
 *
 * The output is architecture independent: integer results are converted to
 * long long before printing, and no pointer values are printed.
 */

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdatomic.h>

స్థిర పూర్ణాంకం called;

స్థిర శూన్య callback(శూన్య)
{
    called++;
}

#నిర్వచించు TEST(A, T, name, V1, V2)                                             \
చేయి {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    రాయి(name " exchange  %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    రాయి(name " add       %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    రాయి(name " sub       %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    రాయి(name " or        %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    రాయి(name " xor       %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    రాయి(name " and       %lld\n", (దీర్ఘ దీర్ఘ)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    రాయి(name " cas       %lld %lld\n",                                    \
           (దీర్ఘ దీర్ఘ)r, (దీర్ఘ దీర్ఘ)expected);                               \
    చేయి {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } అయితే (!r);                                                            \
    రాయి(name " cas weak  %lld %lld %lld\n",                               \
           (దీర్ఘ దీర్ఘ)r, (దీర్ఘ దీర్ఘ)expected,                                \
           (దీర్ఘ దీర్ఘ)atomic_load(&object));                                 \
} అయితే (0)

పూర్ణాంకం ప్రధాన(శూన్య)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    పూర్ణాంకం x = 42;
    పూర్ణాంకం *_Atomic p = ఖాళీ;
    పూర్ణాంకం *pe;
    శూన్య (*_Atomic fp)(శూన్య) = ఖాళీ;
    స్థిరరాశి పూర్ణాంకం *స్థిరరాశి arr[2] = { &x, ఖాళీ };
    స్థిరరాశి పూర్ణాంకం *స్థిరరాశి *_Atomic lst = ఖాళీ;
    atomic_flag f = ATOMIC_FLAG_INIT;
    దీర్ఘ దీర్ఘ old;
    పూర్ణాంకం r1, r2, r3;
    శూన్య (*loaded_callback)(శూన్య);

    TEST(atomic_char, అక్షరం,         "char",         97, 122);
    TEST(atomic_schar, గుర్తుగల అక్షరం,        "schar",        -5, 42);
    TEST(atomic_uchar, గుర్తులేని అక్షరం,        "uchar",        200, 42);
    TEST(atomic_short, పొట్టి,        "short",        -30000, 42);
    TEST(atomic_ushort, గుర్తులేని పొట్టి,       "ushort",       60000, 42);
    TEST(atomic_int, పూర్ణాంకం,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, గుర్తులేని పూర్ణాంకం,         "uint",         4000000000u, 7u);
    TEST(atomic_long, దీర్ఘ,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, గుర్తులేని దీర్ఘ,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, దీర్ఘ దీర్ఘ,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, గుర్తులేని దీర్ఘ దీర్ఘ,       "ullong",       18446744073709551615ULL, 3ULL);
    TEST(atomic_int_least16_t, int_least16_t, "int_least16", -30000, 42);
    TEST(atomic_uint_least32_t, uint_least32_t, "uint_least32", 4000000000u, 7u);
    TEST(atomic_int_least64_t, int_least64_t, "int_least64", -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_uint_least64_t, uint_least64_t, "uint_least64", 18446744073709551615ULL, 3ULL);
    TEST(atomic_int_fast16_t, int_fast16_t,  "int_fast16",  -30000, 42);
    TEST(atomic_uint_fast32_t, uint_fast32_t, "uint_fast32", 4000000000u, 7u);
    TEST(atomic_intptr_t, intptr_t,     "intptr",       -123456, 42);
    TEST(atomic_size_t, size_t,       "size",         4000000000u, 7u);
    TEST(atomic_intmax_t, intmax_t,     "intmax",       -9007199254740993LL, 9007199254740993LL);

    /* unsigned wraparound */
    atomic_store(&u32, UINT_MAX);
    old = atomic_fetch_add(&u32, 1u);
    రాయి("uint wrap  %lld %lld\n",
           old, (దీర్ఘ దీర్ఘ)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (దీర్ఘ దీర్ఘ)atomic_fetch_add(&u64, 1);
    రాయి("ullong add %lld %lld\n",
           old, (దీర్ఘ దీర్ఘ)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (దీర్ఘ దీర్ఘ)atomic_fetch_sub(&u64, 10);
    రాయి("ullong sub %lld %lld\n",
           old, (దీర్ఘ దీర్ఘ)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    రాయి("uchar add  %lld %lld\n",
           old, (దీర్ఘ దీర్ఘ)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    రాయి("bool       %d %d %d %d %d\n", r1, r2, r3,
           (పూర్ణాంకం)be, (పూర్ణాంకం)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = ఖాళీ;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, ఖాళీ);
    రాయి("ptr        %d %d %d\n", r1, r2, pe == &x);
    రాయి("ptr exch   %d\n", atomic_exchange(&p, ఖాళీ) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    స్థిరరాశి పూర్ణాంకం *స్థిరరాశి *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    రాయి("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    రాయి("flag       %d %d %d\n", r1, r2, r3);
    రాయి("called     %d\n", called);

    {
        పూర్ణాంకం _Atomic i = 0;
        atomic_init(&i, 43);
        రాయి("init       %d\n", (పూర్ణాంకం)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    రాయి("kill_dep   %d\n", (పూర్ణాంకం)kill_dependency(1));

    తిరిగి 0;
}
