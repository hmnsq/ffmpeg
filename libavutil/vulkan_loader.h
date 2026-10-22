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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_VULKAN_LOADER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_VULKAN_LOADER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PFN_ਲੱਦੋ_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        offsetof(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t ff_vk_extensions_ਮੰਜ਼ਿਲ_ਨਕਾਬ(ਅਚਲ ਅੱਖਰ * ਅਚਲ *extensions,
                                                ਪੂਰਨ nb_extensions)
{
    ਸਥਿਰ ਅਚਲ ਬਣਤਰ ExtensionMap {
        ਅਚਲ ਅੱਖਰ *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#ਜੇ_ਅੰਤ
        { VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_DMA_BUF_EXTENSION_NAME,   FF_VK_EXT_EXTERNAL_DMABUF_ਸਮ੍ਰਿਤੀ },
        { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME, FF_VK_EXT_DRM_MODIFIER_FLAGS     },
        { VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_FD_EXTENSION_NAME,        FF_VK_EXT_EXTERNAL_FD_ਸਮ੍ਰਿਤੀ     },
        { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_FD_SEM        },
        { VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_HOST_EXTENSION_NAME,      FF_VK_EXT_EXTERNAL_HOST_ਸਮ੍ਰਿਤੀ   },
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,               FF_VK_EXT_DEBUG_UTILS            },
        { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,       FF_VK_EXT_DEVICE_DRM             },
        { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,       FF_VK_EXT_ATOMIC_FLOAT           },
        { VK_KHR_COOPERATIVE_ਮੈਟ੍ਰਿਕਸ_EXTENSION_NAME,        FF_VK_EXT_COOP_ਮੈਟ੍ਰਿਕਸ            },
        { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,               FF_VK_EXT_OPTICAL_FLOW           },
        { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,             FF_VK_EXT_SHADER_OBJECT          },
        { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,    FF_VK_EXT_SUBGROUP_ROTATE        },
        { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,           FF_VK_EXT_HOST_IMAGE_COPY        },
        { VK_KHR_WORKGROUP_ਸਮ੍ਰਿਤੀ_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
        { VK_EXT_SHADER_LONG_ਸਦਿਸ਼_EXTENSION_NAME,               FF_VK_EXT_LONG_ਸਦਿਸ਼         },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_zero_initialize_device_ਸਮ੍ਰਿਤੀ
        { VK_EXT_ZERO_INITIALIZE_DEVICE_ਸਮ੍ਰਿਤੀ_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#ਜੇ_ਅੰਤ
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        { VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_ਸਮ੍ਰਿਤੀ  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#ਜੇ_ਅੰਤ
        { VK_KHR_VIDEO_ਕਤਾਰ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ਕਤਾਰ            },
        { VK_KHR_VIDEO_ENCODE_ਕਤਾਰ_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_ਕਤਾਰ     },
        { VK_KHR_VIDEO_DECODE_ਕਤਾਰ_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_ਕਤਾਰ     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#ਜੇ_ਅੰਤ
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_ਧੱਕੋ_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_ਧੱਕੋ_DESCRIPTOR        },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC   },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#ਜੇ_ਅੰਤ
    };

    FFVulkanExtensions ਨਕਾਬ_2 = 0x0;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_extensions; i++) {
        ਲਈ (ਪੂਰਨ j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            ਜੇ (!strcmp(extensions[i], extension_map[j].name)) {
                ਨਕਾਬ_2 |= extension_map[j].flag;
                ਜਾਰੀ;
            }
        }
    }

    ਵਾਪਸ ਨਕਾਬ_2;
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
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_vk_ਲੱਦੋ_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_ਨਕਾਬ,
                                       ਪੂਰਨ has_inst, ਪੂਰਨ has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    ਸਥਿਰ ਅਚਲ ਬਣਤਰ Function_ਲੱਦੋ_Info {
        ਅੱਖਰ req_inst;
        ਅੱਖਰ req_dev;
        uint16_t struct_ਵਿੱਥ;
        FFVulkanExtensions ext_flag;
    } vk_ਲੱਦੋ_info[] = {
        FN_LIST(PFN_ਲੱਦੋ_INFO)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        FN_LIST_WIN32(PFN_ਲੱਦੋ_INFO)
#ਜੇ_ਅੰਤ
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    ਅਚਲ ਅੱਖਰ *name =
        FN_LIST(FUNC_NAME)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#ਜੇ_ਅੰਤ
    ;
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ FUNC_NAME

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(vk_ਲੱਦੋ_info); name += ਲੜੀ_ਲੰਬਾਈ(name) + 1, i++) {
        ਅਚਲ ਬਣਤਰ Function_ਲੱਦੋ_Info *ਲੱਦੋ = &vk_ਲੱਦੋ_info[i];
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        ਜੇ (ਲੱਦੋ->req_dev  && !has_dev)
            ਜਾਰੀ;
        ਜੇ (ਲੱਦੋ->req_inst && !has_inst)
            ਜਾਰੀ;

        ਲਈ (ਪੂਰਨ j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            ਅੱਖਰ ext_name[128];
            av_ਅਣਵਰਤਿਆ ਪੂਰਨ n;

            n = snprintf(ext_name, ਆਕਾਰ(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < ਆਕਾਰ(ext_name));

            ਜੇ (ਲੱਦੋ->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            ਨਹੀਂਤਾਂ ਜੇ (ਲੱਦੋ->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            ਨਹੀਂਤਾਂ
                fn = hwctx->get_proc_addr(ਨਿਰਾ, ext_name);

            ਜੇ (fn)
                ਰੋਕੋ;
        }

        ਜੇ (!fn && ((extensions_ਨਕਾਬ &~ FF_VK_EXT_NO_FLAG) & ਲੱਦੋ->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + ਲੱਦੋ->struct_ਵਿੱਥ) = fn;
    }
    av_assert1(*name == '\0');

    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ /* AVUTIL_VULKAN_LOADER_H */
