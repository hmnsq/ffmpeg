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

#अगर_अघोषित AVUTIL_VULKAN_LOADER_H
#घोषणा AVUTIL_VULKAN_LOADER_H

#समावेश <stdio.h>

#समावेश "avassert.h"
#समावेश "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#घोषणा PFN_LOAD_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        दुरत्व(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

अटल अंतरभूत uint64_t ff_vk_extensions_to_mask(स्थिर अक्षर * स्थिर *extensions,
                                                पूर्णांक nb_extensions)
{
    अटल स्थिर काष्ठा ExtensionMap {
        स्थिर अक्षर *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#पूर्ण_अगर
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
#अगर_घोषित VK_EXT_shader_long_vector
        { VK_EXT_SHADER_LONG_VECTOR_EXTENSION_NAME,               FF_VK_EXT_LONG_VECTOR         },
#पूर्ण_अगर
#अगर_घोषित VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#पूर्ण_अगर
#अगर_घोषित VK_EXT_zero_initialize_device_memory
        { VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#पूर्ण_अगर
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#अगर_घोषित VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#पूर्ण_अगर
#अगर_घोषित _WIN32
        { VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_MEMORY  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#पूर्ण_अगर
        { VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_QUEUE            },
        { VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_QUEUE     },
        { VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_QUEUE     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#अगर_घोषित VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#पूर्ण_अगर
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_धकेलो_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_धकेलो_DESCRIPTOR        },
#अगर_घोषित VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_INTERNAL_QUEUE_SYNC   },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#पूर्ण_अगर
    };

    FFVulkanExtensions mask = 0x0;

    क्रम (पूर्णांक i = 0; i < nb_extensions; i++) {
        क्रम (पूर्णांक j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            अगर (!म_भेद(extensions[i], extension_map[j].name)) {
                mask |= extension_map[j].flag;
                जारी;
            }
        }
    }

    वापस mask;
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
अटल अंतरभूत पूर्णांक ff_vk_load_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_mask,
                                       पूर्णांक has_inst, पूर्णांक has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    अटल स्थिर काष्ठा FunctionLoadInfo {
        अक्षर req_inst;
        अक्षर req_dev;
        uint16_t struct_offset;
        FFVulkanExtensions ext_flag;
    } vk_load_info[] = {
        FN_LIST(PFN_LOAD_INFO)
#अगर_घोषित _WIN32
        FN_LIST_WIN32(PFN_LOAD_INFO)
#पूर्ण_अगर
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#घोषणा FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    स्थिर अक्षर *name =
        FN_LIST(FUNC_NAME)
#अगर_घोषित _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#पूर्ण_अगर
    ;
#अघोषित FUNC_NAME

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(vk_load_info); name += म_माप(name) + 1, i++) {
        स्थिर काष्ठा FunctionLoadInfo *load = &vk_load_info[i];
        अटल स्थिर अक्षर extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        अगर (load->req_dev  && !has_dev)
            जारी;
        अगर (load->req_inst && !has_inst)
            जारी;

        क्रम (पूर्णांक j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            अक्षर ext_name[128];
            av_unused पूर्णांक n;

            n = snprintf(ext_name, माप(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < माप(ext_name));

            अगर (load->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            अन्यथा अगर (load->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            अन्यथा
                fn = hwctx->get_proc_addr(शून्य, ext_name);

            अगर (fn)
                अवरोध;
        }

        अगर (!fn && ((extensions_mask &~ FF_VK_EXT_NO_FLAG) & load->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            वापस AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + load->struct_offset) = fn;
    }
    av_assert1(*name == '\0');

    वापस 0;
}

#पूर्ण_अगर /* AVUTIL_VULKAN_LOADER_H */
