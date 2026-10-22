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

#ifndef AVUTIL_VULKAN_LOADER_H
#define AVUTIL_VULKAN_LOADER_H

#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#define PFN_LOAD_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        offsetof(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

நிலையான உள்வரி uint64_t ff_vk_extensions_to_mask(மாறிலி எழுத்து * மாறிலி *extensions,
                                                முழு nb_extensions)
{
    நிலையான மாறிலி கட்டமைப்பு ExtensionMap {
        மாறிலி எழுத்து *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#ifdef VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#endif
        { VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME,   FF_VK_EXT_EXTERNAL_DMABUF_MEMORY },
        { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME, FF_VK_EXT_DRM_MODIFIER_FLAGS     },
        { VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,        FF_VK_EXT_EXTERNAL_FD_MEMORY     },
        { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_FD_SEM        },
        { VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME,      FF_VK_EXT_EXTERNAL_HOST_MEMORY   },
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,               FF_VK_EXT_DEBUG_UTILS            },
        { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,       FF_VK_EXT_DEVICE_DRM             },
        { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,       FF_VK_EXT_ATOMIC_FLOAT           },
        { VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME,        FF_VK_EXT_COOP_MATRIX            },
        { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,               FF_VK_EXT_OPTICAL_FLOW           },
        { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,             FF_VK_EXT_SHADER_OBJECT          },
        { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,    FF_VK_EXT_SUBGROUP_ROTATE        },
        { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,           FF_VK_EXT_HOST_IMAGE_COPY        },
        { VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT },
#ifdef VK_EXT_shader_long_vector
        { VK_EXT_SHADER_LONG_VECTOR_EXTENSION_NAME,               FF_VK_EXT_LONG_VECTOR         },
#endif
#ifdef VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#endif
#ifdef VK_EXT_zero_initialize_device_memory
        { VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#endif
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ifdef VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#endif
#ifdef _WIN32
        { VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_MEMORY  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#endif
        { VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_QUEUE            },
        { VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_QUEUE     },
        { VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_QUEUE     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#ifdef VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#endif
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_தள்ளு_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_தள்ளு_DESCRIPTOR        },
#ifdef VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#endif
#ifdef VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#endif
#ifdef VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#endif
#ifdef VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#endif
#ifdef VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#endif
#ifdef VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_INTERNAL_QUEUE_SYNC   },
#endif
#ifdef VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#endif
    };

    FFVulkanExtensions mask = 0x0;

    க்கு (முழு i = 0; i < nb_extensions; i++) {
        க்கு (முழு j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            எனில் (!strcmp(extensions[i], extension_map[j].name)) {
                mask |= extension_map[j].flag;
                தொடர்;
            }
        }
    }

    திரும்பு mask;
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
நிலையான உள்வரி முழு ff_vk_load_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_mask,
                                       முழு has_inst, முழு has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    நிலையான மாறிலி கட்டமைப்பு FunctionLoadInfo {
        எழுத்து req_inst;
        எழுத்து req_dev;
        uint16_t struct_offset;
        FFVulkanExtensions ext_flag;
    } vk_load_info[] = {
        FN_LIST(PFN_LOAD_INFO)
#ifdef _WIN32
        FN_LIST_WIN32(PFN_LOAD_INFO)
#endif
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#define FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    மாறிலி எழுத்து *name =
        FN_LIST(FUNC_NAME)
#ifdef _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#endif
    ;
#undef FUNC_NAME

    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(vk_load_info); name += strlen(name) + 1, i++) {
        மாறிலி கட்டமைப்பு FunctionLoadInfo *load = &vk_load_info[i];
        நிலையான மாறிலி எழுத்து extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        எனில் (load->req_dev  && !has_dev)
            தொடர்;
        எனில் (load->req_inst && !has_inst)
            தொடர்;

        க்கு (முழு j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            எழுத்து ext_name[128];
            av_unused முழு n;

            n = snprintf(ext_name, அளவு(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < அளவு(ext_name));

            எனில் (load->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            இல்லையெனில் எனில் (load->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            இல்லையெனில்
                fn = hwctx->get_proc_addr(வெற்று, ext_name);

            எனில் (fn)
                நிறுத்து;
        }

        எனில் (!fn && ((extensions_mask &~ FF_VK_EXT_NO_FLAG) & load->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            திரும்பு AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + load->struct_offset) = fn;
    }
    av_assert1(*name == '\0');

    திரும்பு 0;
}

#endif /* AVUTIL_VULKAN_LOADER_H */
