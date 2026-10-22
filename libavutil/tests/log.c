/*
 * log functions
 * Copyright (c) 2003 Michel Bardiaux
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

#ಅನ್ತರ್ಭಾವ "libavutil/log.c"

#ಅನ್ತರ್ಭಾವ <string.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ call_log_format_line2(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಅಕ್ಷರ *ಬಫರ್, ಪೂರ್ಣಾಂಕ ಬಫರ್_ಗಾತ್ರ, ...)
{
    va_list ವಾದಗಳು;
    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ print_ಪೂರ್ವಪ್ರತ್ಯಯ=1;
    va_start(ವಾದಗಳು, ಬಫರ್_ಗಾತ್ರ);
    ret = av_log_format_line2(ಖಾಲಿ, AV_LOG_INFO, fmt, ವಾದಗಳು, ಬಫರ್, ಬಫರ್_ಗಾತ್ರ, &print_ಪೂರ್ವಪ್ರತ್ಯಯ);
    va_end(ವಾದಗಳು);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಪೂರ್ಣಾಂಕ i;
    av_log_ಗಣ_level(AV_LOG_DEBUG);
    check_color_terminal();
    ಗಾಗಿ (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ಖಾಲಿ, AV_LOG_FATAL, "use_color: %d\n", use_color);
        ಗಾಗಿ (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ಖಾಲಿ, i, " %d", i);
            av_log(ಖಾಲಿ, AV_LOG_INFO, "e ");
            av_log(ಖಾಲಿ, i + 256*123, "C%d", i);
            av_log(ಖಾಲಿ, AV_LOG_INFO, "e");
        }
        av_log(ಖಾಲಿ, AV_LOG_PANIC, "\n");
    }
    {
        ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;
        ಅಕ್ಷರ ಬಫರ್[4];
        ಫಲಿತಾಂಶ = call_log_format_line2("foo", ಖಾಲಿ, 0);
        ಆದರೆ(ಫಲಿತಾಂಶ != 3) {
            ಬರೆ("Test NULL buffer failed.\n");
            ಹಿಂತಿರುಗಿ 1;
        }
        ಫಲಿತಾಂಶ = call_log_format_line2("foo", ಬಫರ್, 2);
        ಆದರೆ(ಫಲಿತಾಂಶ != 3 || ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(ಬಫರ್, "f", 2)) {
            ಬರೆ("Test buffer too small failed.\n");
            ಹಿಂತಿರುಗಿ 1;
        }
        ಫಲಿತಾಂಶ = call_log_format_line2("foo", ಬಫರ್, 4);
        ಆದರೆ(ಫಲಿತಾಂಶ != 3 || ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(ಬಫರ್, "foo", 4)) {
            ಬರೆ("Test buffer sufficiently big failed.\n");
            ಹಿಂತಿರುಗಿ 1;
        }
    }
    ಹಿಂತಿರುಗಿ 0;
}
