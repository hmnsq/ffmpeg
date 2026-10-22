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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ called;

ಸ್ಥಿರ ಶೂನ್ಯ callback(ಶೂನ್ಯ)
{
    called++;
}

#ವ್ಯಾಖ್ಯಾನಿಸು TEST(A, T, name, V1, V2)                                             \
ಮಾಡು {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    ಬರೆ(name " exchange  %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    ಬರೆ(name " add       %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    ಬರೆ(name " sub       %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    ಬರೆ(name " or        %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    ಬರೆ(name " xor       %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    ಬರೆ(name " and       %lld\n", (ದೀರ್ಘ ದೀರ್ಘ)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    ಬರೆ(name " cas       %lld %lld\n",                                    \
           (ದೀರ್ಘ ದೀರ್ಘ)r, (ದೀರ್ಘ ದೀರ್ಘ)expected);                               \
    ಮಾಡು {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } ಆಗ (!r);                                                            \
    ಬರೆ(name " cas weak  %lld %lld %lld\n",                               \
           (ದೀರ್ಘ ದೀರ್ಘ)r, (ದೀರ್ಘ ದೀರ್ಘ)expected,                                \
           (ದೀರ್ಘ ದೀರ್ಘ)atomic_load(&object));                                 \
} ಆಗ (0)

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    ಪೂರ್ಣಾಂಕ x = 42;
    ಪೂರ್ಣಾಂಕ *_Atomic p = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ *pe;
    ಶೂನ್ಯ (*_Atomic fp)(ಶೂನ್ಯ) = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಸ್ಥಿರಾಂಕ arr[2] = { &x, ಖಾಲಿ };
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಸ್ಥಿರಾಂಕ *_Atomic lst = ಖಾಲಿ;
    atomic_flag f = ATOMIC_FLAG_INIT;
    ದೀರ್ಘ ದೀರ್ಘ old;
    ಪೂರ್ಣಾಂಕ r1, r2, r3;
    ಶೂನ್ಯ (*loaded_callback)(ಶೂನ್ಯ);

    TEST(atomic_char, ಅಕ್ಷರ,         "char",         97, 122);
    TEST(atomic_schar, ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ,        "schar",        -5, 42);
    TEST(atomic_uchar, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ,        "uchar",        200, 42);
    TEST(atomic_short, ಗಿಡ್ಡ,        "short",        -30000, 42);
    TEST(atomic_ushort, ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ,       "ushort",       60000, 42);
    TEST(atomic_int, ಪೂರ್ಣಾಂಕ,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ,         "uint",         4000000000u, 7u);
    TEST(atomic_long, ದೀರ್ಘ,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, ದೀರ್ಘ ದೀರ್ಘ,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ,       "ullong",       18446744073709551615ULL, 3ULL);
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
    ಬರೆ("uint wrap  %lld %lld\n",
           old, (ದೀರ್ಘ ದೀರ್ಘ)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (ದೀರ್ಘ ದೀರ್ಘ)atomic_fetch_add(&u64, 1);
    ಬರೆ("ullong add %lld %lld\n",
           old, (ದೀರ್ಘ ದೀರ್ಘ)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (ದೀರ್ಘ ದೀರ್ಘ)atomic_fetch_sub(&u64, 10);
    ಬರೆ("ullong sub %lld %lld\n",
           old, (ದೀರ್ಘ ದೀರ್ಘ)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    ಬರೆ("uchar add  %lld %lld\n",
           old, (ದೀರ್ಘ ದೀರ್ಘ)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    ಬರೆ("bool       %d %d %d %d %d\n", r1, r2, r3,
           (ಪೂರ್ಣಾಂಕ)be, (ಪೂರ್ಣಾಂಕ)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = ಖಾಲಿ;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, ಖಾಲಿ);
    ಬರೆ("ptr        %d %d %d\n", r1, r2, pe == &x);
    ಬರೆ("ptr exch   %d\n", atomic_exchange(&p, ಖಾಲಿ) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಸ್ಥಿರಾಂಕ *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    ಬರೆ("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    ಬರೆ("flag       %d %d %d\n", r1, r2, r3);
    ಬರೆ("called     %d\n", called);

    {
        ಪೂರ್ಣಾಂಕ _Atomic i = 0;
        atomic_init(&i, 43);
        ಬರೆ("init       %d\n", (ಪೂರ್ಣಾಂಕ)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    ಬರೆ("kill_dep   %d\n", (ಪೂರ್ಣಾಂಕ)kill_dependency(1));

    ಹಿಂತಿರುಗಿ 0;
}
