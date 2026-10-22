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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_VULKAN_LOADER_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_VULKAN_LOADER_H

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#ವ್ಯಾಖ್ಯಾನಿಸು PFN_ತುಂಬು_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        offsetof(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t ff_vk_extensions_ಗಮ್ಯ_ಮುಖವಾಡ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *extensions,
                                                ಪೂರ್ಣಾಂಕ nb_extensions)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ ExtensionMap {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#ಆದರೆ_ಅಂತ್ಯ
        { VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_DMA_BUF_EXTENSION_NAME,   FF_VK_EXT_EXTERNAL_DMABUF_ಸ್ಮರಣೆ },
        { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME, FF_VK_EXT_DRM_MODIFIER_FLAGS     },
        { VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_FD_EXTENSION_NAME,        FF_VK_EXT_EXTERNAL_FD_ಸ್ಮರಣೆ     },
        { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_FD_SEM        },
        { VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_HOST_EXTENSION_NAME,      FF_VK_EXT_EXTERNAL_HOST_ಸ್ಮರಣೆ   },
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,               FF_VK_EXT_DEBUG_UTILS            },
        { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,       FF_VK_EXT_DEVICE_DRM             },
        { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,       FF_VK_EXT_ATOMIC_FLOAT           },
        { VK_KHR_COOPERATIVE_ಮಾತೃಕೆ_EXTENSION_NAME,        FF_VK_EXT_COOP_ಮಾತೃಕೆ            },
        { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,               FF_VK_EXT_OPTICAL_FLOW           },
        { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,             FF_VK_EXT_SHADER_OBJECT          },
        { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,    FF_VK_EXT_SUBGROUP_ROTATE        },
        { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,           FF_VK_EXT_HOST_IMAGE_COPY        },
        { VK_KHR_WORKGROUP_ಸ್ಮರಣೆ_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
        { VK_EXT_SHADER_LONG_ಸದಿಶ_EXTENSION_NAME,               FF_VK_EXT_LONG_ಸದಿಶ         },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_zero_initialize_device_ಸ್ಮರಣೆ
        { VK_EXT_ZERO_INITIALIZE_DEVICE_ಸ್ಮರಣೆ_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#ಆದರೆ_ಅಂತ್ಯ
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        { VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_ಸ್ಮರಣೆ  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#ಆದರೆ_ಅಂತ್ಯ
        { VK_KHR_VIDEO_ಸರತಿ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ಸರತಿ            },
        { VK_KHR_VIDEO_ENCODE_ಸರತಿ_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_ಸರತಿ     },
        { VK_KHR_VIDEO_DECODE_ಸರತಿ_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_ಸರತಿ     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#ಆದರೆ_ಅಂತ್ಯ
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_ತಳ್ಳು_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR        },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC   },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#ಆದರೆ_ಅಂತ್ಯ
    };

    FFVulkanExtensions ಮುಖವಾಡ_2 = 0x0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_extensions; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            ಆದರೆ (!strcmp(extensions[i], extension_map[j].name)) {
                ಮುಖವಾಡ_2 |= extension_map[j].flag;
                ಮುಂದುವರಿ;
            }
        }
    }

    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ_2;
}

/**
 * Function loader.
 * Vulkan function from scratch loading happens in 3 stages - the first one
 * is before any initialization has happened, and you have neither an instance
 * structure nor a device structure. At this stage, you can only get the bare
 * minimals to initialize an instance.
 * The second stage is when you have an instance. At this stage, you can
 * initialize a VkDevice, and have an idea of what extensions each device
 * supports.
 * Finally, in the third stage, you can proceed and load all core functions,
 * plus you can be sure that any extensions you've enabled during device
 * initialization will be available.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_vk_ತುಂಬು_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_ಮುಖವಾಡ,
                                       ಪೂರ್ಣಾಂಕ has_inst, ಪೂರ್ಣಾಂಕ has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ Function_ತುಂಬು_Info {
        ಅಕ್ಷರ req_inst;
        ಅಕ್ಷರ req_dev;
        uint16_t struct_ಸ್ಥಾನಾಂತರ;
        FFVulkanExtensions ext_flag;
    } vk_ತುಂಬು_info[] = {
        FN_LIST(PFN_ತುಂಬು_INFO)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        FN_LIST_WIN32(PFN_ತುಂಬು_INFO)
#ಆದರೆ_ಅಂತ್ಯ
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#ವ್ಯಾಖ್ಯಾನಿಸು FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name =
        FN_LIST(FUNC_NAME)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#ಆದರೆ_ಅಂತ್ಯ
    ;
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು FUNC_NAME

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(vk_ತುಂಬು_info); name += ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(name) + 1, i++) {
        ಸ್ಥಿರಾಂಕ ರಚನೆ Function_ತುಂಬು_Info *ತುಂಬು = &vk_ತುಂಬು_info[i];
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        ಆದರೆ (ತುಂಬು->req_dev  && !has_dev)
            ಮುಂದುವರಿ;
        ಆದರೆ (ತುಂಬು->req_inst && !has_inst)
            ಮುಂದುವರಿ;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            ಅಕ್ಷರ ext_name[128];
            av_ಬಳಸದ ಪೂರ್ಣಾಂಕ n;

            n = snprintf(ext_name, ಗಾತ್ರ(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < ಗಾತ್ರ(ext_name));

            ಆದರೆ (ತುಂಬು->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ತುಂಬು->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            ಇಲ್ಲದಿದ್ದರೆ
                fn = hwctx->get_proc_addr(ಖಾಲಿ, ext_name);

            ಆದರೆ (fn)
                ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!fn && ((extensions_ಮುಖವಾಡ &~ FF_VK_EXT_NO_FLAG) & ತುಂಬು->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + ತುಂಬು->struct_ಸ್ಥಾನಾಂತರ) = fn;
    }
    av_assert1(*name == '\0');

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_VULKAN_LOADER_H */
