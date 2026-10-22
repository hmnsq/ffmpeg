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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdatomic.h>

स्थिर पूर्णाङ्क called;

स्थिर शून्य callback(शून्य)
{
    called++;
}

#define TEST(A, T, name, V1, V2)                                             \
करेहि {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    printf(name " exchange  %lld\n", (long long)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    printf(name " add       %lld\n", (long long)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    printf(name " sub       %lld\n", (long long)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    printf(name " or        %lld\n", (long long)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    printf(name " xor       %lld\n", (long long)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    printf(name " and       %lld\n", (long long)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    printf(name " cas       %lld %lld\n",                                    \
           (long long)r, (long long)expected);                               \
    करेहि {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } जाव (!r);                                                            \
    printf(name " cas weak  %lld %lld %lld\n",                               \
           (long long)r, (long long)expected,                                \
           (long long)atomic_load(&object));                                 \
} जाव (0)

पूर्णाङ्क main(शून्य)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    पूर्णाङ्क x = 42;
    पूर्णाङ्क *_Atomic p = रिक्त;
    पूर्णाङ्क *pe;
    शून्य (*_Atomic fp)(शून्य) = रिक्त;
    ध्रुव पूर्णाङ्क *ध्रुव arr[2] = { &x, रिक्त };
    ध्रुव पूर्णाङ्क *ध्रुव *_Atomic lst = रिक्त;
    atomic_flag f = ATOMIC_FLAG_INIT;
    long long old;
    पूर्णाङ्क r1, r2, r3;
    शून्य (*loaded_callback)(शून्य);

    TEST(atomic_char, वर्ण,         "char",         97, 122);
    TEST(atomic_schar, signed वर्ण,        "schar",        -5, 42);
    TEST(atomic_uchar, unsigned वर्ण,        "uchar",        200, 42);
    TEST(atomic_short, short,        "short",        -30000, 42);
    TEST(atomic_ushort, unsigned short,       "ushort",       60000, 42);
    TEST(atomic_int, पूर्णाङ्क,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, unsigned पूर्णाङ्क,         "uint",         4000000000u, 7u);
    TEST(atomic_long, long,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, unsigned long,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, long long,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, unsigned long long,       "ullong",       18446744073709551615ULL, 3ULL);
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
    printf("uint wrap  %lld %lld\n",
           old, (long long)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (long long)atomic_fetch_add(&u64, 1);
    printf("ullong add %lld %lld\n",
           old, (long long)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (long long)atomic_fetch_sub(&u64, 10);
    printf("ullong sub %lld %lld\n",
           old, (long long)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    printf("uchar add  %lld %lld\n",
           old, (long long)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    printf("bool       %d %d %d %d %d\n", r1, r2, r3,
           (पूर्णाङ्क)be, (पूर्णाङ्क)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = रिक्त;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, रिक्त);
    printf("ptr        %d %d %d\n", r1, r2, pe == &x);
    printf("ptr exch   %d\n", atomic_exchange(&p, रिक्त) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    ध्रुव पूर्णाङ्क *ध्रुव *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    printf("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    printf("flag       %d %d %d\n", r1, r2, r3);
    printf("called     %d\n", called);

    {
        पूर्णाङ्क _Atomic i = 0;
        atomic_init(&i, 43);
        printf("init       %d\n", (पूर्णाङ्क)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    printf("kill_dep   %d\n", (पूर्णाङ्क)kill_dependency(1));

    प्रत्यागम 0;
}
