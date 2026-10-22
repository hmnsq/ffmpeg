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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>

ਸਥਿਰ ਪੂਰਨ called;

ਸਥਿਰ ਖਾਲੀ callback(ਖਾਲੀ)
{
    called++;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST(A, T, name, V1, V2)                                             \
ਕਰੋ {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    ਲਿਖੋ(name " exchange  %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    ਲਿਖੋ(name " add       %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    ਲਿਖੋ(name " sub       %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    ਲਿਖੋ(name " or        %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    ਲਿਖੋ(name " xor       %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    ਲਿਖੋ(name " and       %lld\n", (ਲੰਮਾ ਲੰਮਾ)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    ਲਿਖੋ(name " cas       %lld %lld\n",                                    \
           (ਲੰਮਾ ਲੰਮਾ)r, (ਲੰਮਾ ਲੰਮਾ)expected);                               \
    ਕਰੋ {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } ਜਦੋਂ (!r);                                                            \
    ਲਿਖੋ(name " cas weak  %lld %lld %lld\n",                               \
           (ਲੰਮਾ ਲੰਮਾ)r, (ਲੰਮਾ ਲੰਮਾ)expected,                                \
           (ਲੰਮਾ ਲੰਮਾ)atomic_load(&object));                                 \
} ਜਦੋਂ (0)

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    ਪੂਰਨ x = 42;
    ਪੂਰਨ *_Atomic p = ਨਿਰਾ;
    ਪੂਰਨ *pe;
    ਖਾਲੀ (*_Atomic fp)(ਖਾਲੀ) = ਨਿਰਾ;
    ਅਚਲ ਪੂਰਨ *ਅਚਲ arr[2] = { &x, ਨਿਰਾ };
    ਅਚਲ ਪੂਰਨ *ਅਚਲ *_Atomic lst = ਨਿਰਾ;
    atomic_flag f = ATOMIC_FLAG_INIT;
    ਲੰਮਾ ਲੰਮਾ old;
    ਪੂਰਨ r1, r2, r3;
    ਖਾਲੀ (*loaded_callback)(ਖਾਲੀ);

    TEST(atomic_char, ਅੱਖਰ,         "char",         97, 122);
    TEST(atomic_schar, ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ,        "schar",        -5, 42);
    TEST(atomic_uchar, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ,        "uchar",        200, 42);
    TEST(atomic_short, ਛੋਟਾ,        "short",        -30000, 42);
    TEST(atomic_ushort, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ,       "ushort",       60000, 42);
    TEST(atomic_int, ਪੂਰਨ,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ,         "uint",         4000000000u, 7u);
    TEST(atomic_long, ਲੰਮਾ,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, ਲੰਮਾ ਲੰਮਾ,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ,       "ullong",       18446744073709551615ULL, 3ULL);
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
    ਲਿਖੋ("uint wrap  %lld %lld\n",
           old, (ਲੰਮਾ ਲੰਮਾ)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (ਲੰਮਾ ਲੰਮਾ)atomic_fetch_add(&u64, 1);
    ਲਿਖੋ("ullong add %lld %lld\n",
           old, (ਲੰਮਾ ਲੰਮਾ)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (ਲੰਮਾ ਲੰਮਾ)atomic_fetch_sub(&u64, 10);
    ਲਿਖੋ("ullong sub %lld %lld\n",
           old, (ਲੰਮਾ ਲੰਮਾ)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    ਲਿਖੋ("uchar add  %lld %lld\n",
           old, (ਲੰਮਾ ਲੰਮਾ)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    ਲਿਖੋ("bool       %d %d %d %d %d\n", r1, r2, r3,
           (ਪੂਰਨ)be, (ਪੂਰਨ)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = ਨਿਰਾ;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, ਨਿਰਾ);
    ਲਿਖੋ("ptr        %d %d %d\n", r1, r2, pe == &x);
    ਲਿਖੋ("ptr exch   %d\n", atomic_exchange(&p, ਨਿਰਾ) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    ਅਚਲ ਪੂਰਨ *ਅਚਲ *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    ਲਿਖੋ("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    ਲਿਖੋ("flag       %d %d %d\n", r1, r2, r3);
    ਲਿਖੋ("called     %d\n", called);

    {
        ਪੂਰਨ _Atomic i = 0;
        atomic_init(&i, 43);
        ਲਿਖੋ("init       %d\n", (ਪੂਰਨ)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    ਲਿਖੋ("kill_dep   %d\n", (ਪੂਰਨ)kill_dependency(1));

    ਵਾਪਸ 0;
}
