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

#شامل "libavutil/pixdesc.c"

ساکن ثابت شمار AVPixelFormat pixfmt_list[] = {
    AV_PIX_FMT_MONOWHITE,
    AV_PIX_FMT_GRAY8,
    AV_PIX_FMT_GRAY10,
    AV_PIX_FMT_GRAY16,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_YUV420P10,
    AV_PIX_FMT_YUV420P16,
    AV_PIX_FMT_YUV422P,
    AV_PIX_FMT_YUV422P10,
    AV_PIX_FMT_YUV422P16,
    AV_PIX_FMT_YUV444P,
    AV_PIX_FMT_YUV444P10,
    AV_PIX_FMT_YUV444P16,
    AV_PIX_FMT_RGB565,
    AV_PIX_FMT_RGB24,
    AV_PIX_FMT_RGB48,
    AV_PIX_FMT_VDPAU,
    AV_PIX_FMT_VAAPI,
};

ساکن ثابت شمار AVPixelFormat semiplanar_list[] = {
    AV_PIX_FMT_P016,
    AV_PIX_FMT_P012,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_P216,
    AV_PIX_FMT_P210,
    AV_PIX_FMT_NV16,
    AV_PIX_FMT_P416,
    AV_PIX_FMT_P410,
    AV_PIX_FMT_NV24,
    AV_PIX_FMT_NV12,
};

ساکن ثابت شمار AVPixelFormat packed_list[] = {
    AV_PIX_FMT_XV48,
    AV_PIX_FMT_XV36,
    AV_PIX_FMT_XV30,
    AV_PIX_FMT_VUYX,
    AV_PIX_FMT_Y216,
    AV_PIX_FMT_Y212,
    AV_PIX_FMT_Y210,
    AV_PIX_FMT_YUYV422,
};

ساکن ثابت شمار AVPixelFormat subsampled_list[] = {
    AV_PIX_FMT_YUV411P,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_YUV422P,
    AV_PIX_FMT_YUV444P,
};

ساکن ثابت شمار AVPixelFormat depthchroma_list[] = {
    AV_PIX_FMT_YUV420P14,
    AV_PIX_FMT_YUV422P14,
    AV_PIX_FMT_YUV444P16,
};

قسمتعریف شمار AVPixelFormat (*ڈھونڈو_بہترین_t)(شمار AVPixelFormat pixfmt);

#تعریف_کرو ڈھونڈو_بہترین_wrapper(name, list) \
ساکن شمار AVPixelFormat ڈھونڈو_بہترین ## name (شمار AVPixelFormat pixfmt)    \
{                                                                           \
    شمار AVPixelFormat بہترین = AV_PIX_FMT_NONE;                              \
    صحیح i;                                                                  \
    برائے (i = 0; i < FF_ARRAY_ELEMS(list); i++)                              \
        بہترین = av_ڈھونڈو_بہترین_pix_fmt_کا_2(بہترین, list[i],                     \
                                         pixfmt, 0, تہی);                  \
    واپس بہترین;                                                            \
}

ڈھونڈو_بہترین_wrapper(بنیاد_2, pixfmt_list)
ڈھونڈو_بہترین_wrapper(seminplanar, semiplanar_list)
ڈھونڈو_بہترین_wrapper(packed, packed_list)
ڈھونڈو_بہترین_wrapper(subsampled, subsampled_list)
ڈھونڈو_بہترین_wrapper(depthchroma, depthchroma_list)

ساکن خالی test(شمار AVPixelFormat داخلہ, شمار AVPixelFormat expected,
                 صحیح *pass, صحیح *fail, ڈھونڈو_بہترین_t ڈھونڈو_بہترین_fn)
{
        شمار AVPixelFormat output = ڈھونڈو_بہترین_fn(داخلہ);
        اگر (output != expected) {
            لکھو("Matching %s: got %s, expected %s\n",
                   av_get_pix_fmt_name(داخلہ),
                   av_get_pix_fmt_name(output),
                   av_get_pix_fmt_name(expected));
            ++(*fail);
        } ورنہ
            ++(*pass);
}

صحیح مین(خالی)
{
    صحیح i, pass = 0, fail = 0;

#تعریف_کرو TEST(داخلہ, expected) \
    test(داخلہ, expected, &pass, &fail, ڈھونڈو_بہترین_بنیاد)

    // Same formats.
    برائے (i = 0; i < FF_ARRAY_ELEMS(pixfmt_list); i++)
        TEST(pixfmt_list[i], pixfmt_list[i]);

    // Formats containing the same data in different layouts.
    TEST(AV_PIX_FMT_MONOBLACK, AV_PIX_FMT_MONOWHITE);
    TEST(AV_PIX_FMT_NV12,      AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_P010,      AV_PIX_FMT_YUV420P10);
    TEST(AV_PIX_FMT_P012,      AV_PIX_FMT_YUV420P16);
    TEST(AV_PIX_FMT_P016,      AV_PIX_FMT_YUV420P16);
    TEST(AV_PIX_FMT_P210,      AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_P212,      AV_PIX_FMT_YUV422P16);
    TEST(AV_PIX_FMT_P216,      AV_PIX_FMT_YUV422P16);
    TEST(AV_PIX_FMT_P410,      AV_PIX_FMT_YUV444P10);
    TEST(AV_PIX_FMT_P412,      AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_P416,      AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_NV16,      AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_NV20,      AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_NV24,      AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_YUYV422,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_UYVY422,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_VYU444,    AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_BGR565,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_BGR24,     AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRP,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_0RGB,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRP16,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_VUYX,      AV_PIX_FMT_YUV444P);

    // Formats additionally containing alpha (here ignored).
    TEST(AV_PIX_FMT_YA8,       AV_PIX_FMT_GRAY8);
    TEST(AV_PIX_FMT_YA16,      AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUVA420P,  AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_YUVA422P,  AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_YUVA444P,  AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_VUYA,      AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_AYUV,      AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_UYVA,      AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_AYUV64,    AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_RGBA,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_ABGR,      AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_GBRAP,     AV_PIX_FMT_RGB24);
    TEST(AV_PIX_FMT_RGBA64,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_BGRA64,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP16,   AV_PIX_FMT_RGB48);

    // Formats requiring upsampling to represent exactly.
    TEST(AV_PIX_FMT_GRAY12,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUV410P,   AV_PIX_FMT_YUV420P);
    TEST(AV_PIX_FMT_YUV411P,   AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_UYYVYY411, AV_PIX_FMT_YUV422P);
    TEST(AV_PIX_FMT_YUV440P,   AV_PIX_FMT_YUV444P);
    TEST(AV_PIX_FMT_YUV440P10, AV_PIX_FMT_YUV444P10);
    TEST(AV_PIX_FMT_YUV440P12, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_YUV420P9,  AV_PIX_FMT_YUV420P10);
    TEST(AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV420P16);
    TEST(AV_PIX_FMT_YUV444P9,  AV_PIX_FMT_YUV444P10);
    TEST(AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_BGR4,      AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB444,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB555,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_GBRP10,    AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP10,   AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_GBRAP12,   AV_PIX_FMT_RGB48);

    // Formats containing the same data in different endianness.
    TEST(AV_PIX_FMT_GRAY10BE,    AV_PIX_FMT_GRAY10);
    TEST(AV_PIX_FMT_GRAY10LE,    AV_PIX_FMT_GRAY10);
    TEST(AV_PIX_FMT_GRAY16BE,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_GRAY16LE,    AV_PIX_FMT_GRAY16);
    TEST(AV_PIX_FMT_YUV422P10BE, AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_YUV422P10LE, AV_PIX_FMT_YUV422P10);
    TEST(AV_PIX_FMT_YUV444P16BE, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_YUV444P16LE, AV_PIX_FMT_YUV444P16);
    TEST(AV_PIX_FMT_RGB565BE,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB565LE,    AV_PIX_FMT_RGB565);
    TEST(AV_PIX_FMT_RGB48BE,     AV_PIX_FMT_RGB48);
    TEST(AV_PIX_FMT_RGB48LE,     AV_PIX_FMT_RGB48);

    // Opaque formats are least unlike each other.
    TEST(AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_VDPAU);

#تعریف_کرو TEST_SEMIPLANAR(داخلہ, expected) \
    test(داخلہ, expected, &pass, &fail, ڈھونڈو_بہترین_seminplanar)

    // Same formats.
    برائے (i = 0; i < FF_ARRAY_ELEMS(semiplanar_list); i++)
        TEST_SEMIPLANAR(semiplanar_list[i], semiplanar_list[i]);

    // Formats containing the same data in different layouts.
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV420P, AV_PIX_FMT_NV12);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV420P10, AV_PIX_FMT_P010);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV420P12, AV_PIX_FMT_P012);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV420P16, AV_PIX_FMT_P016);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV420P9, AV_PIX_FMT_P010);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV422P, AV_PIX_FMT_NV16);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV422P10, AV_PIX_FMT_P210);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV422P12, AV_PIX_FMT_P216);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV422P16, AV_PIX_FMT_P216);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV444P, AV_PIX_FMT_NV24);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV444P10, AV_PIX_FMT_P410);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV444P12, AV_PIX_FMT_P416);
    TEST_SEMIPLANAR(AV_PIX_FMT_YUV444P16, AV_PIX_FMT_P416);

#تعریف_کرو TEST_PACKED(داخلہ, expected) \
    test(داخلہ, expected, &pass, &fail, ڈھونڈو_بہترین_packed)

    // Same formats.
    برائے (i = 0; i < FF_ARRAY_ELEMS(packed_list); i++)
        TEST_PACKED(packed_list[i], packed_list[i]);

    // Formats containing the same data in different layouts.
    TEST_PACKED(AV_PIX_FMT_YUV444P, AV_PIX_FMT_VUYX);
    TEST_PACKED(AV_PIX_FMT_YUV444P10, AV_PIX_FMT_XV30);
    TEST_PACKED(AV_PIX_FMT_YUV444P12, AV_PIX_FMT_XV36);
    TEST_PACKED(AV_PIX_FMT_YUV444P16, AV_PIX_FMT_XV48);
    TEST_PACKED(AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUYV422);
    TEST_PACKED(AV_PIX_FMT_YUV422P10, AV_PIX_FMT_Y210);
    TEST_PACKED(AV_PIX_FMT_YUV422P12, AV_PIX_FMT_Y212);
    TEST_PACKED(AV_PIX_FMT_YUV422P16, AV_PIX_FMT_Y216);

#تعریف_کرو TEST_SUBSAMPLED(داخلہ, expected) \
    test(داخلہ, expected, &pass, &fail, ڈھونڈو_بہترین_subsampled)

    // Same formats.
    برائے (i = 0; i < FF_ARRAY_ELEMS(subsampled_list); i++)
        TEST_SUBSAMPLED(subsampled_list[i], subsampled_list[i]);

    TEST_SUBSAMPLED(AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV420P);

#تعریف_کرو TEST_گہرائی_CHROMA(داخلہ, expected) \
    test(داخلہ, expected, &pass, &fail, ڈھونڈو_بہترین_depthchroma)

    // Same formats.
    برائے (i = 0; i < FF_ARRAY_ELEMS(depthchroma_list); i++)
        TEST_گہرائی_CHROMA(depthchroma_list[i], depthchroma_list[i]);

    TEST_گہرائی_CHROMA(AV_PIX_FMT_YUV420P16, AV_PIX_FMT_YUV444P16);
    TEST_گہرائی_CHROMA(AV_PIX_FMT_YUV422P16, AV_PIX_FMT_YUV444P16);


    لکھو("%d tests passed, %d tests failed.\n", pass, fail);
    واپس !!fail;
}
