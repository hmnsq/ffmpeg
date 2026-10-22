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

#నిర్వచితం_కాకపోతే AVUTIL_VULKAN_LOADER_H
#నిర్వచించు AVUTIL_VULKAN_LOADER_H

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "vulkan_functions.h"

/* Macro to turn a function name into a loader struct */
#నిర్వచించు PFN_ఎక్కించు_INFO(req_inst, req_dev, ext_flag, name) \
    {                                                    \
        req_inst,                                        \
        req_dev,                                         \
        offsetof(FFVulkanFunctions, name),               \
        ext_flag,                                        \
    },

స్థిర అంతఃవరుస uint64_t ff_vk_extensions_గమ్యం_ముసుగు(స్థిరరాశి అక్షరం * స్థిరరాశి *extensions,
                                                పూర్ణాంకం nb_extensions)
{
    స్థిర స్థిరరాశి నిర్మాణం ExtensionMap {
        స్థిరరాశి అక్షరం *name;
        FFVulkanExtensions flag;
    } extension_map[] = {
        /* Instance extensions */
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,                         FF_VK_EXT_DEBUG_UTILS            },

        /* Device extensions */
#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
        { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#అయితే_ముగింపు
        { VK_EXT_EXTERNAL_జ్ఞాపకం_DMA_BUF_EXTENSION_NAME,   FF_VK_EXT_EXTERNAL_DMABUF_జ్ఞాపకం },
        { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME, FF_VK_EXT_DRM_MODIFIER_FLAGS     },
        { VK_KHR_EXTERNAL_జ్ఞాపకం_FD_EXTENSION_NAME,        FF_VK_EXT_EXTERNAL_FD_జ్ఞాపకం     },
        { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_FD_SEM        },
        { VK_EXT_EXTERNAL_జ్ఞాపకం_HOST_EXTENSION_NAME,      FF_VK_EXT_EXTERNAL_HOST_జ్ఞాపకం   },
        { VK_EXT_DEBUG_UTILS_EXTENSION_NAME,               FF_VK_EXT_DEBUG_UTILS            },
        { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,       FF_VK_EXT_DEVICE_DRM             },
        { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,       FF_VK_EXT_ATOMIC_FLOAT           },
        { VK_KHR_COOPERATIVE_మాతృక_EXTENSION_NAME,        FF_VK_EXT_COOP_మాతృక            },
        { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,               FF_VK_EXT_OPTICAL_FLOW           },
        { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,             FF_VK_EXT_SHADER_OBJECT          },
        { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,    FF_VK_EXT_SUBGROUP_ROTATE        },
        { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,           FF_VK_EXT_HOST_IMAGE_COPY        },
        { VK_KHR_WORKGROUP_జ్ఞాపకం_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT },
#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
        { VK_EXT_SHADER_LONG_సదిశ_EXTENSION_NAME,               FF_VK_EXT_LONG_సదిశ         },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_EXT_shader_replicated_composites
        { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME, FF_VK_EXT_REPLICATED_COMPOSITES   },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_EXT_zero_initialize_device_జ్ఞాపకం
        { VK_EXT_ZERO_INITIALIZE_DEVICE_జ్ఞాపకం_EXTENSION_NAME, FF_VK_EXT_ZERO_INITIALIZE    },
#అయితే_ముగింపు
        { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#నిర్వచితమైతే VK_KHR_video_maintenance2
        { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,       FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#అయితే_ముగింపు
#నిర్వచితమైతే _WIN32
        { VK_KHR_EXTERNAL_జ్ఞాపకం_WIN32_EXTENSION_NAME,     FF_VK_EXT_EXTERNAL_WIN32_జ్ఞాపకం  },
        { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,  FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#అయితే_ముగింపు
        { VK_KHR_VIDEO_వరుస_EXTENSION_NAME,               FF_VK_EXT_VIDEO_వరుస            },
        { VK_KHR_VIDEO_ENCODE_వరుస_EXTENSION_NAME,        FF_VK_EXT_VIDEO_ENCODE_వరుస     },
        { VK_KHR_VIDEO_DECODE_వరుస_EXTENSION_NAME,        FF_VK_EXT_VIDEO_DECODE_వరుస     },
        { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H264      },
        { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H264      },
        { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_ENCODE_H265      },
        { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,         FF_VK_EXT_VIDEO_DECODE_H265      },
#నిర్వచితమైతే VK_KHR_video_decode_vp9
        { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_VP9       },
#అయితే_ముగింపు
        { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_DECODE_AV1       },
        { VK_KHR_నెట్టు_DESCRIPTOR_EXTENSION_NAME,           FF_VK_EXT_నెట్టు_DESCRIPTOR        },
#నిర్వచితమైతే VK_KHR_shader_expect_assume
        { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,      FF_VK_EXT_EXPECT_ASSUME          },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_shader_maximal_reconvergence
        { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME, FF_VK_EXT_MAXIMAL_RECONVERGENCE },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance9
        { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,             FF_VK_EXT_MAINTENANCE_9          },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_unified_image_layouts
        { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,     FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_encode_av1
        { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,          FF_VK_EXT_VIDEO_ENCODE_AV1       },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
        { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME, FF_VK_EXT_అంతర్గత_వరుస_SYNC   },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
        { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,            FF_VK_EXT_MAINTENANCE_11         },
#అయితే_ముగింపు
    };

    FFVulkanExtensions ముసుగు_2 = 0x0;

    కొరకు (పూర్ణాంకం i = 0; i < nb_extensions; i++) {
        కొరకు (పూర్ణాంకం j = 0; j < FF_ARRAY_ELEMS(extension_map); j++) {
            ఒకవేళ (!strcmp(extensions[i], extension_map[j].name)) {
                ముసుగు_2 |= extension_map[j].flag;
                కొనసాగు;
            }
        }
    }

    తిరిగి ముసుగు_2;
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
స్థిర అంతఃవరుస పూర్ణాంకం ff_vk_ఎక్కించు_functions(AVHWDeviceContext *ctx,
                                       FFVulkanFunctions *vk,
                                       uint64_t extensions_ముసుగు,
                                       పూర్ణాంకం has_inst, పూర్ణాంకం has_dev)
{
    AVVulkanDeviceContext *hwctx = ctx->hwctx;

    స్థిర స్థిరరాశి నిర్మాణం Function_ఎక్కించు_Info {
        అక్షరం req_inst;
        అక్షరం req_dev;
        uint16_t struct_స్థానభ్రంశం;
        FFVulkanExtensions ext_flag;
    } vk_ఎక్కించు_info[] = {
        FN_LIST(PFN_ఎక్కించు_INFO)
#నిర్వచితమైతే _WIN32
        FN_LIST_WIN32(PFN_ఎక్కించు_INFO)
#అయితే_ముగింపు
    };
    // Concatenate the names to avoid relocations. The resulting string
    // will end with \0\0
#నిర్వచించు FUNC_NAME(req_inst, req_dev, ext_flag, name) "vk"#name"\0"
    స్థిరరాశి అక్షరం *name =
        FN_LIST(FUNC_NAME)
#నిర్వచితమైతే _WIN32
        FN_LIST_WIN32(FUNC_NAME)
#అయితే_ముగింపు
    ;
#నిర్వచనం_రద్దు FUNC_NAME

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(vk_ఎక్కించు_info); name += అక్షరశ్రేణి_పొడవు(name) + 1, i++) {
        స్థిరరాశి నిర్మాణం Function_ఎక్కించు_Info *ఎక్కించు = &vk_ఎక్కించు_info[i];
        స్థిర స్థిరరాశి అక్షరం extensions[][4] = { "", "EXT", "KHR" };
        PFN_vkVoidFunction fn;

        ఒకవేళ (ఎక్కించు->req_dev  && !has_dev)
            కొనసాగు;
        ఒకవేళ (ఎక్కించు->req_inst && !has_inst)
            కొనసాగు;

        కొరకు (పూర్ణాంకం j = 0; j < FF_ARRAY_ELEMS(extensions); j++) {
            అక్షరం ext_name[128];
            av_వాడని పూర్ణాంకం n;

            n = snprintf(ext_name, పరిమాణం(ext_name), "%s%s", name, extensions[j]);
            av_assert1(n < పరిమాణం(ext_name));

            ఒకవేళ (ఎక్కించు->req_dev)
                fn = vk->GetDeviceProcAddr(hwctx->act_dev, ext_name);
            లేకపోతే ఒకవేళ (ఎక్కించు->req_inst)
                fn = hwctx->get_proc_addr(hwctx->inst, ext_name);
            లేకపోతే
                fn = hwctx->get_proc_addr(ఖాళీ, ext_name);

            ఒకవేళ (fn)
                ఆపు;
        }

        ఒకవేళ (!fn && ((extensions_ముసుగు &~ FF_VK_EXT_NO_FLAG) & ఎక్కించు->ext_flag)) {
            av_log(ctx, AV_LOG_ERROR, "Loader error, function \"%s\" indicated "
                   "as supported, but got NULL function pointer!\n", name);
            తిరిగి AVERROR_EXTERNAL;
        }

        *(PFN_vkVoidFunction *)((uint8_t *)vk + ఎక్కించు->struct_స్థానభ్రంశం) = fn;
    }
    av_assert1(*name == '\0');

    తిరిగి 0;
}

#అయితే_ముగింపు /* AVUTIL_VULKAN_LOADER_H */
