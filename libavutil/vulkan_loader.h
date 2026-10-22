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

#اگر_غیر_تعریف_شدہ AVUTIL_VULKAN_LOADER_H
#تعریف_کرو AVUTIL_VULKAN_LOADER_H

#شامل <stdio.h>

#شامل "avassert.h"
#شامل "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#تعریف_کرو PFN_بھرو_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        offsetof(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

ساکن اندرونی uint64_t ff_vk_extensions_مقصد_نقاب(ثابت حرف * ثابت *extensions,
                                                صحیح nb_extensions)
{
    ساکن ثابت ساخت ExtensionMap {
        ثابت حرف *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#اگر_تعریف_شدہ VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#اگر_ختم
        { VK_EXT_EXTERNAL_حافظہ_DMA_BUF_EXTENSION_NAME,   FF_VK_EXT_EXTERNAL_DMABUF_حافظہ },
        { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME, FF_VK_EXT_DRM_MODIFIER_FLAGS     },
        { VK_KHR_EXTERNAL_حافظہ_FD_EXTENSION_NAME,        FF_VK_EXT_EXTERNAL_FD_حافظہ     },
        { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_FD_SEM        },
        { VK_EXT_EXTERNAL_حافظہ_HOST_EXTENSION_NAME,      FF_VK_EXT_EXTERNAL_HOST_حافظہ   },
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,               FF_VK_EXT_DEBUG_UTILS            },
        { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,       FF_VK_EXT_DEVICE_DRM             },
        { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,       FF_VK_EXT_ATOMIC_FLOAT           },
        { VK_KHR_COOPERATIVE_میٹرکس_EXTENSION_NAME,        FF_VK_EXT_COOP_میٹرکس            },
        { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,               FF_VK_EXT_OPTICAL_FLOW           },
        { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,             FF_VK_EXT_SHADER_OBJECT          },
        { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,    FF_VK_EXT_SUBGROUP_ROTATE        },
        { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,           FF_VK_EXT_HOST_IMAGE_COPY        },
        { VK_KHR_WORKGROUP_حافظہ_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT },
#اگر_تعریف_شدہ VK_EXT_shader_long_سمتیہ
        { VK_EXT_SHADER_LONG_سمتیہ_EXTENSION_NAME,               FF_VK_EXT_LONG_سمتیہ         },
#اگر_ختم
#اگر_تعریف_شدہ VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#اگر_ختم
#اگر_تعریف_شدہ VK_EXT_zero_initialize_device_حافظہ
        { VK_EXT_ZERO_INITIALIZE_DEVICE_حافظہ_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#اگر_ختم
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#اگر_تعریف_شدہ VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#اگر_ختم
#اگر_تعریف_شدہ _WIN32
        { VK_KHR_EXTERNAL_حافظہ_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_حافظہ  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#اگر_ختم
        { VK_KHR_VIDEO_قطار_EXTENSION_NAME,               FF_VK_EXT_VIDEO_قطار            },
        { VK_KHR_VIDEO_ENCODE_قطار_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_قطار     },
        { VK_KHR_VIDEO_DECODE_قطار_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_قطار     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#اگر_تعریف_شدہ VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#اگر_ختم
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_ڈالو_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_ڈالو_DESCRIPTOR        },
#اگر_تعریف_شدہ VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_اندرونی_قطار_SYNC   },
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#اگر_ختم
    };

    FFVulkanExtensions نقاب_2 = 0x0;

    برائے (صحیح i = 0; i < nb_extensions; i++) {
        برائے (صحیح j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            اگر (!strcmp(extensions[i], extension_map[j].name)) {
                نقاب_2 |= extension_map[j].flag;
                جاری;
            }
        }
    }

    واپس نقاب_2;
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
ساکن اندرونی صحیح ff_vk_بھرو_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_نقاب,
                                       صحیح has_inst, صحیح has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    ساکن ثابت ساخت Function_بھرو_Info {
        حرف req_inst;
        حرف req_dev;
        uint16_t struct_انحراف;
        FFVulkanExtensions ext_flag;
    } vk_بھرو_info[] = {
        FN_LIST(PFN_بھرو_INFO)
#اگر_تعریف_شدہ _WIN32
        FN_LIST_WIN32(PFN_بھرو_INFO)
#اگر_ختم
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#تعریف_کرو FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    ثابت حرف *name =
        FN_LIST(FUNC_NAME)
#اگر_تعریف_شدہ _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#اگر_ختم
    ;
#تعریف_منسوخ FUNC_NAME

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(vk_بھرو_info); name += لڑی_لمبائی(name) + 1, i++) {
        ثابت ساخت Function_بھرو_Info *بھرو = &vk_بھرو_info[i];
        ساکن ثابت حرف extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        اگر (بھرو->req_dev  && !has_dev)
            جاری;
        اگر (بھرو->req_inst && !has_inst)
            جاری;

        برائے (صحیح j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            حرف ext_name[128];
            av_غیر_مستعمل صحیح n;

            n = snprintf(ext_name, حجم(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < حجم(ext_name));

            اگر (بھرو->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            ورنہ اگر (بھرو->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            ورنہ
                fn = hwctx->get_proc_addr(تہی, ext_name);

            اگر (fn)
                توڑو;
        }

        اگر (!fn && ((extensions_نقاب &~ FF_VK_EXT_NO_FLAG) & بھرو->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            واپس AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + بھرو->struct_انحراف) = fn;
    }
    av_assert1(*name == '\0');

    واپس 0;
}

#اگر_ختم /* AVUTIL_VULKAN_LOADER_H */
