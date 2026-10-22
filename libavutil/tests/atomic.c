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

#شامل <limits.h>
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <stdatomic.h>

ساکن صحیح called;

ساکن خالی callback(خالی)
{
    called++;
}

#تعریف_کرو TEST(A, T, name, V1, V2)                                             \
کرو {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    لکھو(name " exchange  %lld\n", (طویل طویل)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    لکھو(name " add       %lld\n", (طویل طویل)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    لکھو(name " sub       %lld\n", (طویل طویل)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    لکھو(name " or        %lld\n", (طویل طویل)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    لکھو(name " xor       %lld\n", (طویل طویل)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    لکھو(name " and       %lld\n", (طویل طویل)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    لکھو(name " cas       %lld %lld\n",                                    \
           (طویل طویل)r, (طویل طویل)expected);                               \
    کرو {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } جب (!r);                                                            \
    لکھو(name " cas weak  %lld %lld %lld\n",                               \
           (طویل طویل)r, (طویل طویل)expected,                                \
           (طویل طویل)atomic_load(&object));                                 \
} جب (0)

صحیح مین(خالی)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    صحیح x = 42;
    صحیح *_Atomic p = تہی;
    صحیح *pe;
    خالی (*_Atomic fp)(خالی) = تہی;
    ثابت صحیح *ثابت arr[2] = { &x, تہی };
    ثابت صحیح *ثابت *_Atomic lst = تہی;
    atomic_flag f = ATOMIC_FLAG_INIT;
    طویل طویل old;
    صحیح r1, r2, r3;
    خالی (*loaded_callback)(خالی);

    TEST(atomic_char, حرف,         "char",         97, 122);
    TEST(atomic_schar, علامتی حرف,        "schar",        -5, 42);
    TEST(atomic_uchar, غیرعلامتی حرف,        "uchar",        200, 42);
    TEST(atomic_short, مختصر,        "short",        -30000, 42);
    TEST(atomic_ushort, غیرعلامتی مختصر,       "ushort",       60000, 42);
    TEST(atomic_int, صحیح,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, غیرعلامتی صحیح,         "uint",         4000000000u, 7u);
    TEST(atomic_long, طویل,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, غیرعلامتی طویل,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, طویل طویل,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, غیرعلامتی طویل طویل,       "ullong",       18446744073709551615ULL, 3ULL);
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
    لکھو("uint wrap  %lld %lld\n",
           old, (طویل طویل)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (طویل طویل)atomic_fetch_add(&u64, 1);
    لکھو("ullong add %lld %lld\n",
           old, (طویل طویل)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (طویل طویل)atomic_fetch_sub(&u64, 10);
    لکھو("ullong sub %lld %lld\n",
           old, (طویل طویل)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    لکھو("uchar add  %lld %lld\n",
           old, (طویل طویل)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    لکھو("bool       %d %d %d %d %d\n", r1, r2, r3,
           (صحیح)be, (صحیح)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = تہی;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, تہی);
    لکھو("ptr        %d %d %d\n", r1, r2, pe == &x);
    لکھو("ptr exch   %d\n", atomic_exchange(&p, تہی) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    ثابت صحیح *ثابت *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    لکھو("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    لکھو("flag       %d %d %d\n", r1, r2, r3);
    لکھو("called     %d\n", called);

    {
        صحیح _Atomic i = 0;
        atomic_init(&i, 43);
        لکھو("init       %d\n", (صحیح)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    لکھو("kill_dep   %d\n", (صحیح)kill_dependency(1));

    واپس 0;
}
