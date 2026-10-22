/*
 * Copyright (c) Lynne
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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "random_seed.h"
#অন্তর্ভাব "refstruct.h"

#অন্তর্ভাব "vulkan.h"
#অন্তর্ভাব "libavutil/vulkan_loader.h"

#যদি CONFIG_SHADER_COMPRESSION
#অন্তর্ভাব "libavutil/zlib_utils.h"
#endif

ধ্রুবক VkComponentMapping ff_comp_identity_map = {
    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
};

/* Converts return values to strings */
ধ্রুবক অক্ষর *ff_vk_ret2str(Vk_ফলাফল res)
{
#define CASE(VAL) ক্ষেত্র VAL: ফেরত #VAL
    নির্বাচন (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_SET);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_OUT_OF_HOST_MEMORY);
    CASE(VK_ERROR_OUT_OF_DEVICE_MEMORY);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_LOST);
    CASE(VK_ERROR_MEMORY_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_OUT_OF_POOL_MEMORY);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_LOST_KHR);
    CASE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_OUT_OF_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_DONE_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    পূর্বনির্ধারিত: ফেরত "Unknown error";
    }
#undef CASE
}

/* Malitia pura, Khronos */
#define FN_MAP_TO(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## _to_ ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_TO(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT,                   \
               VK_IMAGE_USAGE_SAMPLED_BIT);                             \
        MAP_TO(VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT);                        \
        MAP_TO(VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_BIT);                        \
        MAP_TO(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT,                   \
               VK_IMAGE_USAGE_STORAGE_BIT);                             \
        MAP_TO(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_BIT,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);                    \
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_BIT_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_BIT_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_BIT_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_প্রবেশ_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        ফেরত dst;                                                     \
    }

#define MAP_TO(flag1, flag2) যদি (src & flag2) dst |= flag1;
FN_MAP_TO(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#undef MAP_TO
#define MAP_TO(flag1, flag2) যদি (src & flag1) dst |= flag2;
FN_MAP_TO(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#undef MAP_TO
#undef FN_MAP_TO

স্থির শূন্য load_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    জন্য (পূর্ণসংখ্যা i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        পূর্ণসংখ্যা skip = 0;
        জন্য (পূর্ণসংখ্যা j = 0; j < s->nb_qfs; j++) {
            যদি (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                বিরতি;
            }
        }
        যদি (skip)
            চালু;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

স্থির শূন্য reset_imageviews(AVRefStructOpaque unused, শূন্য *obj);

পূর্ণসংখ্যা ff_vk_load_props(FFVulkanContext *s)
{
    FFVulkanFunctions *vk = &s->vkfn;

    s->props = (VkPhysicalDeviceProperties2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->props, &s->props_11, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES);
    FF_VK_STRUCT_EXT(s, &s->props, &s->driver_props, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES);
    FF_VK_STRUCT_EXT(s, &s->props, &s->subgroup_props, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_আকার_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ঠেলো_desc_props, FF_VK_EXT_ঠেলো_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ঠেলো_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_MEMORY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_matrix_props, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#ifdef VK_EXT_shader_long_vector
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_vector_props, FF_VK_EXT_LONG_VECTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_PROPERTIES_EXT);
#endif

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#ifdef VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#endif
#ifdef VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#endif

    যদি (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(আকার(FFVkImageViews), 0,
                                                         ফাঁকা, ফাঁকা, reset_imageviews,
                                                         ফাঁকা, ফাঁকা);
        যদি (!s->imageviews_pool)
            ফেরত AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(আকার(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_গুনতি = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_গুনতি = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    যদি (s->host_image_props.copy_Src_Layout_গুনতি == 512 ||
        s->host_image_props.copy_Dst_Layout_গুনতি == 512) {
        VkImageLayout *new_array;
        size_t new_আকার;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ফাঁকা;
        s->host_image_props.copy_Src_Layout_গুনতি =
        s->host_image_props.copy_Dst_Layout_গুনতি = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_আকার = s->host_image_props.copy_Src_Layout_গুনতি +
                   s->host_image_props.copy_Dst_Layout_গুনতি;
        new_আকার *= আকার(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_আকার);
        যদি (!new_array)
            ফেরত AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_গুনতি;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->GetPhysicalDeviceMemoryProperties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    জন্য (পূর্ণসংখ্যা i = 0; i < s->mprops.memory_Type_গুনতি; i++)
        s->host_cached_flag |= s->mprops.memoryTypes[i].propertyFlags &
                               VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

    load_enabled_qfs(s);

    যদি (s->qf_props)
        ফেরত 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ফাঁকা);

    s->qf_props = av_calloc(s->tot_nb_qfs, আকার(*s->qf_props));
    যদি (!s->qf_props)
        ফেরত AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, আকার(*s->query_props));
    যদি (!s->qf_props) {
        av_freep(&s->qf_props);
        ফেরত AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, আকার(*s->video_props));
    যদি (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        ফেরত AVERROR(ENOMEM);
    }

#ifdef VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, আকার(*s->ownership_props));
    যদি (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        ফেরত AVERROR(ENOMEM);
    }
#endif

    জন্য (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_ফলাফল_STATUS_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR);
#ifdef VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#endif
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    যদি (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ফাঁকা);

        যদি (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                আকার(VkCooperativeMatrixPropertiesKHR));
            জন্য (পূর্ণসংখ্যা i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    ফেরত 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < s->hwctx->nb_qf; i++) {
        যদি ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            ফেরত &s->hwctx->qf[i];
        }
    }
    ফেরত ফাঁকা;
}

স্থির শূন্য exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

শূন্য ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        যদি (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_গুনতি = 1,
                .pSemaphores = &e->sem,
                .p_মানসমূহ = &e->sem_মান,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->lock);
    }

    /* Free shader-specific data */
    জন্য (পূর্ণসংখ্যা i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_তথ্য *sd = &pool->reg_shd[i];

        যদি (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++) {
        যদি (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        যদি (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    যদি (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_তথ্য);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_আকার = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
স্থির atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ফাঁকা)->qf)];
স্থির AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

স্থির শূন্য exec_pool_phase_seed(শূন্য)
{
    uint32_t seed = av_get_random_seed();
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], seed, memory_order_relaxed);
}

পূর্ণসংখ্যা ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, পূর্ণসংখ্যা nb_contexts,
                         পূর্ণসংখ্যা nb_queries, VkQueryType query_type, পূর্ণসংখ্যা query_64bit,
                         ধ্রুবক শূন্য *query_create_pnext)
{
    পূর্ণসংখ্যা err;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_বাফার_Allocate_Info cbuf_create;

    ধ্রুবক VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ফাঁকা;

    atomic_init(&pool->idx, 0);

    যদি (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        যদি (!ef)
            ফেরত AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*আকার(*pool->cmd_buf_pools));
    যদি (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*আকার(*pool->cmd_bufs));
    যদি (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_বাফার_BIT,
            .queue_Family_সূচক   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            যাও fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_বাফার_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_বাফার_ALLOCATE_INFO,
            .level              = VK_COMMAND_বাফার_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_বাফার_গুনতি = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            যাও fail;
        }
    }

    /* Query pool */
    যদি (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_পরবর্তী = query_create_pnext,
            .queryType = query_type,
            .query_গুনতি = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            যাও fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_status_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        যদি (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            পূর্ণসংখ্যা nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_status_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } অন্যথা যদি (query_type == VK_QUERY_TYPE_ফলাফল_STATUS_ONLY_KHR) {
            pool->query_status_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_আকার = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_তথ্য = av_calloc(nb_contexts, pool->qd_আকার);
        যদি (!pool->query_তথ্য) {
            err = AVERROR(ENOMEM);
            যাও fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, আকার(*pool->contexts));
    যদি (!pool->contexts) {
        err = AVERROR(ENOMEM);
        যাও fail;
    }

    pool->pool_আকার = nb_contexts;

    জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++)
        pthread_mutex_init(&pool->contexts[i].lock, ফাঁকা);

#ifdef VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    পূর্ণসংখ্যা internal_queue_sync = 0;
    যদি (s->extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC) {
        ধ্রুবক VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_find_struct(s->hwctx->device_features.p_পরবর্তী,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        internal_queue_sync = iqs && iqs->internallySynchronizedQueues;
    }
#endif

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_seed);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    পূর্ণসংখ্যা pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_পরবর্তী = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ফেরত AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_তথ্য = ((uint8_t *)pool->query_তথ্য) + pool->qd_আকার*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->অঙ্ক : (i + phase) % qf->অঙ্ক;
        e->qf = qf->idx;
        VkDeviceQueueInfo2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
#ifdef VK_KHR_internally_synchronized_queues
            .flags            = internal_queue_sync ?
                                VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR : 0,
#endif
            .queue_Family_সূচক = qf->idx,
            .queue_সূচক       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->queue);
    }

    ফেরত 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    ফেরত err;
}

Vk_ফলাফল ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              শূন্য **তথ্য, Vk_Query_ফলাফল_Flag_Bits flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ধ্রুবক FFVkExecPool *pool = e->parent;
    Vk_Query_ফলাফল_Flags qf = flags & ~(VK_QUERY_ফলাফল_64_BIT |
                                      VK_QUERY_ফলাফল_WITH_STATUS_BIT_KHR);

    যদি (!e->query_তথ্য) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        ফেরত VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_ফলাফল_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_ফলাফল_WITH_STATUS_BIT_KHR : 0x0;

    যদি (তথ্য)
        *তথ্য = e->query_তথ্য;

    ফেরত vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_আকার, e->query_তথ্য,
                                   pool->qd_আকার, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        যদি (pthread_mutex_trylock(&e->lock))
            চালু; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        যদি (vk->Get_Semaphore_গণক_মান(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_মান &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->lock);
    }

    ফেরত &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_আকার];
}

শূন্য ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_গুনতি = 1,
        .pSemaphores = &e->sem,
        .p_মানসমূহ = &e->sem_মান,
    };
    pthread_mutex_lock(&e->lock);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->lock);
}

পূর্ণসংখ্যা ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ধ্রুবক FFVkExecPool *pool = e->parent;

    Vk_Command_বাফার_Begin_Info cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_বাফার_BEGIN_INFO,
        .flags = VK_COMMAND_বাফার_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_গুনতি = 1,
        .pSemaphores = &e->sem,
        .p_মানসমূহ = &e->sem_মান,
    };

    pthread_mutex_lock(&e->lock);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_বাফার(e->buf, &cmd_start);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->lock);
        ফেরত AVERROR_EXTERNAL;
    }

    যদি (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_মান++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .মান = e->sem_মান,
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->lock);

    ফেরত 0;
}

স্থির শূন্য exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_buf_deps; j++)
        av_বাফার_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        নির্বাচন (od->type) {
        ক্ষেত্র VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            বিরতি;
        ক্ষেত্র VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            বিরতি;
        পূর্বনির্ধারিত:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        যদি (e->frame_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];
            vkfc->unlock_frame(hwfc, vkf);
            e->frame_locked[j] = 0;
        }
        e->frame_update[j] = 0;
    }
    e->nb_frame_deps = 0;

    e->sem_wait_cnt = 0;
    e->sem_sig_cnt = 0;
    e->sem_sig_val_dst_cnt = 0;
}

শূন্য ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .মান = e->sem_মান,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_বাফার(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

শূন্য ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  শূন্য *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

শূন্য ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   শূন্য *obj)
{
    শূন্য **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    জন্য (পূর্ণসংখ্যা i = 0; i < e->nb_refstruct_deps; i++) {
        যদি (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            ফেরত;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ফাঁকা;
}

শূন্য ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

পূর্ণসংখ্যা ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    যদি (!e->sw_frame_deps[e->nb_sw_frame_deps])
        ফেরত AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    ফেরত 0;
}

শূন্য ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .মান = val,
        .stageMask = stage,
    };
}

শূন্য ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .মান = val,
        .stageMask = stage,
    };
}

শূন্য ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, পূর্ণসংখ্যা nb,
                                 VkPipelineStageFlagBits2 stage,
                                 পূর্ণসংখ্যা wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    যদি (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        জন্য (পূর্ণসংখ্যা i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stageMask = stage,
            };
        }

        ফেরত;
    }

    /* Ownership of each semaphore passes to the execution */
    জন্য (পূর্ণসংখ্যা i = 0; i < nb; i++) {
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_add_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

পূর্ণসংখ্যা ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];
    পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);

    /* Don't add duplicates */
    জন্য (পূর্ণসংখ্যা i = 0; i < e->nb_frame_deps; i++)
        যদি (e->frame_deps[i]->তথ্য[0] == f->তথ্য[0])
            ফেরত 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    যদি (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_বাফার_ref(f->buf[0]);
        যদি (!e->buf_deps[e->nb_buf_deps])
            ফেরত AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->lock_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .মান = vkf->sem_মান[i],
            .stageMask = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .মান = vkf->sem_মান[i] + 1,
            .stageMask = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_মান[i];
        e->sem_sig_val_dst_cnt++;
    }

    ফেরত 0;
}

শূন্য ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < e->nb_frame_deps; i++)
        যদি (e->frame_deps[i]->তথ্য[0] == f->তথ্য[0])
            বিরতি;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    যদি (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dst_Queue_Family_সূচক;
    e->access_dst[i] = bar->dstAccessMask;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

পূর্ণসংখ্যা ff_vk_exec_mirror_sem_মান(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];

    /* Reject unknown frames */
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < e->nb_frame_deps; i++)
        যদি (e->frame_deps[i]->তথ্য[0] == f->তথ্য[0])
            বিরতি;
    যদি (i == e->nb_frame_deps)
        ফেরত AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_মান[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_বাফার_Submit_Info cmd_buf_info = (Vk_Command_বাফার_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_বাফার_SUBMIT_INFO,
        .command_বাফার = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_বাফার_Infos = &cmd_buf_info,
        .command_বাফার_Info_গুনতি = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_গুনতি = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_গুনতি = e->sem_sig_cnt,
    };

    ret = vk->End_Command_বাফার(e->buf);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        ফেরত AVERROR_EXTERNAL;
    }

#যদি FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->lock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#যদি FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        ফেরত AVERROR_EXTERNAL;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    জন্য (পূর্ণসংখ্যা j = 0; j < e->nb_frame_deps; j++) {
        যদি (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];

            যদি (e->frame_update[j]) {
                পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);
                জন্য (পূর্ণসংখ্যা i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->queue_family[i] = e->queue_family_dst[j];
                }
            }
            vkfc->unlock_frame(hwfc, vkf);
            e->frame_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, শূন্য *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    Vk_ফলাফল ret;
    পূর্ণসংখ্যা সূচক = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    VkMemoryAllocateInfo alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .p_পরবর্তী           = alloc_extension,
    };

    alloc_info.allocation_আকার = req->আকার_2;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    জন্য (পূর্ণসংখ্যা i = 0; i < s->mprops.memory_Type_গুনতি; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        যদি (!(req->memoryTypeBits & (1 << i)))
            চালু;

        /* The memory type flags must include our properties */
        যদি ((req_flags != UINT32_MAX) &&
            ((s->mprops.memoryTypes[i].propertyFlags & req_flags) != req_flags))
            চালু;

        /* Found a suitable memory type */
        সূচক = i;
        বিরতি;
    }

    যদি (সূচক < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ফেরত AVERROR(EINVAL);
    }

    alloc_info.memory_Type_সূচক = সূচক;

    ret = vk->AllocateMemory(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    যদি (ret != VK_SUCCESS)
        ফেরত AVERROR(ENOMEM);

    যদি (mem_flags)
        *mem_flags |= s->mprops.memoryTypes[সূচক].propertyFlags;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, VkFormat format, পূর্ণসংখ্যা nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, শূন্য *create_pnext)
{
    পূর্ণসংখ্যা err;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMemoryPropertyFlagBits mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_পরবর্তী         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { width, height, 1 },
        .mipLevels     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_গুনতি_1_BIT,
        .sharingMode   = VK_SHARING_MODE_EXCLUSIVE,
    };
    VkMemoryDedicatedAllocateInfo ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
    };
    VkMemoryRequirements2 req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
    };
    VkImageMemoryRequirementsInfo2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
    };
    VkBindImageMemoryInfo bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->GetImageMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.memoryRequirements,
                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    যদি (err < 0)
        যাও fail;

    bind_info.image  = *img;
    bind_info.memory = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        যাও fail;
    }

    ফেরত 0;

fail:
    ff_vk_image_free(s, img, mem);
    ফেরত err;
}

শূন্য ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    যদি (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    যদি (*mem) {
        vk->FreeMemory(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

পূর্ণসংখ্যা ff_vk_create_buf(FFVulkanContext *s, FFVk_বাফার *buf, size_t আকার_2,
                     শূন্য *p_পরবর্তী, শূন্য *alloc_p_পরবর্তী,
                     Vk_বাফার_Usage_Flags usage, VkMemoryPropertyFlagBits flags)
{
    পূর্ণসংখ্যা err;
    Vk_ফলাফল ret;
    পূর্ণসংখ্যা use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_বাফার_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_বাফার_CREATE_INFO,
        .p_পরবর্তী       = p_পরবর্তী,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .আকার_2        = flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ?
                       FFALIGN(আকার_2, s->props.properties.limits.minMemoryMapAlignment) :
                       আকার_2,
    };

    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    Vk_বাফার_Memory_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_বাফার_MEMORY_REQUIREMENTS_INFO_2,
    };
    VkMemoryDedicatedAllocateInfo ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
        .p_পরবর্তী = alloc_p_পরবর্তী,
    };
    VkMemoryDedicatedRequirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
    };
    VkMemoryRequirements2 req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
        .p_পরবর্তী = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           আকার_2, usage, flags);

    ret = vk->Create_বাফার(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    req_desc.বাফার = buf->buf;

    vk->Get_বাফার_Memory_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefersDedicatedAllocation |
                  ded_req.requiresDedicatedAllocation;
    যদি (use_ded_mem) {
        ded_alloc.বাফার = buf->buf;
        ded_alloc.p_পরবর্তী = alloc_p_পরবর্তী;
        alloc_p_পরবর্তী = &ded_alloc;
    }

    যদি (usage & VK_বাফার_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags.p_পরবর্তী = alloc_p_পরবর্তী;
        alloc_p_পরবর্তী = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.memoryRequirements, flags, alloc_p_পরবর্তী,
                          &buf->flags, &buf->mem);
    যদি (err)
        ফেরত err;

    ret = vk->Bind_বাফার_Memory(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    যদি (usage & VK_বাফার_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        Vk_বাফার_Device_Address_Info address_info = {
            .sType = VK_STRUCTURE_TYPE_বাফার_DEVICE_ADDRESS_INFO,
            .বাফার = buf->buf,
        };
        buf->address = vk->Get_বাফার_Device_Address(s->hwctx->act_dev, &address_info);
    }

    buf->আকার_2 = আকার_2;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_map_buffers(FFVulkanContext *s, FFVk_বাফার **buf, uint8_t *mem[],
                      পূর্ণসংখ্যা nb_buffers, পূর্ণসংখ্যা invalidate)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange inval_list[64];
    পূর্ণসংখ্যা inval_গুনতি = 0;

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_buffers; i++) {
        শূন্য *dst;
        ret = vk->MapMemory(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_WHOLE_আকার, 0, &dst);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            ফেরত AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        যদি (mem)
            mem[i] = dst;
    }

    যদি (!invalidate)
        ফেরত 0;

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_buffers; i++) {
        ধ্রুবক VkMappedMemoryRange ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            .memory = buf[i]->mem,
            .আকার_2   = VK_WHOLE_আকার,
        };
        যদি (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            চালু;
        inval_list[inval_গুনতি++] = ival_buf;
    }

    যদি (inval_গুনতি) {
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, inval_গুনতি,
                                               inval_list);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            ফেরত AVERROR_EXTERNAL;
        }
    }

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_flush_বাফার(FFVulkanContext *s, FFVk_বাফার *buf,
                       Vk_Device_আকার offset, Vk_Device_আকার mem_আকার,
                       পূর্ণসংখ্যা flush)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    যদি (buf->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        ফেরত 0;

    ধ্রুবক VkMappedMemoryRange flush_তথ্য = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = buf->mem,
        .offset = offset,
        .আকার_2   = mem_আকার,
    };

    যদি (flush)
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_তথ্য);
    অন্যথা
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_তথ্য);

    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_বাফার **buf, পূর্ণসংখ্যা nb_buffers,
                        পূর্ণসংখ্যা flush)
{
    পূর্ণসংখ্যা err = 0;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange flush_list[64];
    পূর্ণসংখ্যা flush_গুনতি = 0;

    যদি (flush) {
        জন্য (পূর্ণসংখ্যা i = 0; i < nb_buffers; i++) {
            ধ্রুবক VkMappedMemoryRange flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .memory = buf[i]->mem,
                .আকার_2   = VK_WHOLE_আকার,
            };

            av_assert0(!buf[i]->host_ref);
            যদি (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                চালু;
            flush_list[flush_গুনতি++] = flush_buf;
        }
    }

    যদি (flush_গুনতি) {
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, flush_গুনতি,
                                          flush_list);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_buffers; i++) {
        vk->UnmapMemory(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ফাঁকা;
    }

    ফেরত err;
}

শূন্য ff_vk_free_buf(FFVulkanContext *s, FFVk_বাফার *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    যদি (!buf || !s->hwctx)
        ফেরত;

    যদি (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_বাফার(s, buf, 0);
    যদি (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_বাফার(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    যদি (buf->mem != VK_NULL_HANDLE)
        vk->FreeMemory(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    যদি (buf->host_ref)
        av_বাফার_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ফাঁকা;
}

স্থির শূন্য pooled_buf_free(AVRefStructOpaque opaque, শূন্য *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

পূর্ণসংখ্যা ff_vk_get_pooled_বাফার(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_বাফার **buf, Vk_বাফার_Usage_Flags usage,
                            শূন্য *create_p_পরবর্তী, size_t আকার_2,
                            VkMemoryPropertyFlagBits mem_props)
{
    পূর্ণসংখ্যা err;
    FFVk_বাফার *তথ্য;

    যদি (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(আকার(FFVk_বাফার), 0, ctx,
                                                ফাঁকা, ফাঁকা, pooled_buf_free,
                                                ফাঁকা);
        যদি (!(*buf_pool))
            ফেরত AVERROR(ENOMEM);
    }

    *buf = তথ্য = av_refstruct_pool_get(*buf_pool);
    যদি (!তথ্য)
        ফেরত AVERROR(ENOMEM);

    যদি (তথ্য->আকার_2 >= আকার_2)
        ফেরত 0;

    ff_vk_free_buf(ctx, তথ্য);
    memset(তথ্য, 0, আকার(*তথ্য));

    err = ff_vk_create_buf(ctx, তথ্য, আকার_2,
                           create_p_পরবর্তী, ফাঁকা, usage,
                           mem_props);
    যদি (err < 0) {
        av_refstruct_unref(buf);
        ফেরত err;
    }

    যদি (mem_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_বাফার(ctx, তথ্য, &তথ্য->mapped_mem, 0);
        যদি (err < 0) {
            av_refstruct_unref(buf);
            ফেরত err;
        }
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা create_mapped_বাফার(FFVulkanContext *s,
                                FFVk_বাফার *vkb, Vk_বাফার_Usage_Flags usage,
                                size_t আকার_2,
                                Vk_External_Memory_বাফার_Create_Info *create_desc,
                                VkImportMemoryHostPointerInfoEXT *import_desc,
                                VkMemoryHostPointerPropertiesEXT props)
{
    পূর্ণসংখ্যা err;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_বাফার_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_বাফার_CREATE_INFO,
        .p_পরবর্তী       = create_desc,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .আকার_2        = আকার_2,
    };
    VkMemoryRequirements req = {
        .আকার_2           = আকার_2,
        .alignment      = s->hprops.minImportedHostPointerAlignment,
        .memoryTypeBits = props.memoryTypeBits,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                          import_desc, &vkb->flags, &vkb->mem);
    যদি (err < 0)
        ফেরত err;

    ret = vk->Create_বাফার(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    যদি (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        ফেরত AVERROR_EXTERNAL;
    }

    ret = vk->Bind_বাফার_Memory(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    যদি (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_বাফার(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

স্থির শূন্য host_map_free(AVRefStructOpaque opaque, শূন্য *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

পূর্ণসংখ্যা ff_vk_host_map_বাফার(FFVulkanContext *s, FFVk_বাফার **dst,
                          uint8_t *src_তথ্য, Vk_Device_আকার আকার_2,
                          ধ্রুবক AVBufferRef *src_buf,
                          Vk_বাফার_Usage_Flags usage)
{
    পূর্ণসংখ্যা err;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_Memory_বাফার_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_বাফার_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
    };
    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    VkImportMemoryHostPointerInfoEXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT,
        .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
        .p_পরবর্তী = usage & VK_বাফার_USAGE_SHADER_DEVICE_ADDRESS_BIT ? &alloc_flags : ফাঁকা,
    };
    VkMemoryHostPointerPropertiesEXT props;

    AVBufferRef *ref;
    FFVk_বাফার *vkb;
    size_t offs;
    size_t বাফার_আকার;

    *dst = ফাঁকা;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_তথ্য % s->hprops.minImportedHostPointerAlignment;
    import_desc.pHostPointer = src_তথ্য - offs;

    props = (VkMemoryHostPointerPropertiesEXT) {
        VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT,
    };
    ret = vk->GetMemoryHostPointerPropertiesEXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.pHostPointer,
                                                &props);
    যদি (!(ret == VK_SUCCESS && props.memoryTypeBits))
        ফেরত AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_বাফার_ref(src_buf);
    যদি (!ref)
        ফেরত AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ধ্রুবক Vk_Device_আকার src_avail = src_buf->আকার_2 - (src_তথ্য - src_buf->তথ্য);
    বাফার_আকার = offs + FFMIN(আকার_2, src_avail);
    বাফার_আকার = FFALIGN(বাফার_আকার, s->props.properties.limits.minMemoryMapAlignment);
    বাফার_আকার = FFALIGN(বাফার_আকার, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(আকার(*vkb), 0, s, host_map_free);
    যদি (!vkb) {
        av_বাফার_unref(&ref);
        ফেরত AVERROR(ENOMEM);
    }

    err = create_mapped_বাফার(s, vkb, usage,
                               বাফার_আকার, &create_desc, &import_desc,
                               props);
    যদি (err < 0) {
        av_বাফার_unref(&ref);
        av_refstruct_unref(&vkb);
        ফেরত err;
    }

    যদি (usage & VK_বাফার_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        Vk_বাফার_Device_Address_Info address_info = {
            .sType = VK_STRUCTURE_TYPE_বাফার_DEVICE_ADDRESS_INFO,
            .বাফার = vkb->buf,
        };
        vkb->address = vk->Get_বাফার_Device_Address(s->hwctx->act_dev, &address_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_offset = offs;
    vkb->address       += offs;
    vkb->mapped_mem     = src_তথ্য;
    vkb->আকার_2           = বাফার_আকার - offs;

    *dst = vkb;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_shader_add_ঠেলো_const(FFVulkanShader *shd, পূর্ণসংখ্যা offset, পূর্ণসংখ্যা আকার_2,
                                VkShaderStageFlagBits stage)
{
    Vk_ঠেলো_Constant_Range *pc = &shd->ঠেলো_consts[shd->ঠেলো_consts_অঙ্ক++];
    av_assert1(shd->ঠেলো_consts_অঙ্ক < FF_VK_MAX_ঠেলো_CONSTS);
    pc->stageFlags = stage;
    pc->offset = offset;
    pc->আকার_2 = আকার_2;
    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       পূর্ণসংখ্যা unnorm_coords, VkFilter filt)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmapMode = (unnorm_coords || filt == VK_FILTER_NEAREST) ?
                      VK_SAMPLER_MIPMAP_MODE_NEAREST :
                      VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        .addressModeV = sampler_info.addressModeU,
        .addressModeW = sampler_info.addressModeU,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, পূর্ণসংখ্যা p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);
    পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(hwfc->sw_format);

    স্থির ধ্রুবক VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    যদি (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        ফেরত VK_IMAGE_ASPECT_COLOR_BIT;

    ফেরত plane_aspect[p];
}

পূর্ণসংখ্যা ff_vk_mt_is_np_rgb(গণনা AVPixelFormat pix_fmt)
{
    যদি (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
        pix_fmt == AV_PIX_FMT_RGBA   || pix_fmt == AV_PIX_FMT_RGB24  ||
        pix_fmt == AV_PIX_FMT_BGR24  || pix_fmt == AV_PIX_FMT_RGB48  ||
        pix_fmt == AV_PIX_FMT_RGBA64 || pix_fmt == AV_PIX_FMT_RGB565 ||
        pix_fmt == AV_PIX_FMT_BGR565 || pix_fmt == AV_PIX_FMT_BGR0   ||
        pix_fmt == AV_PIX_FMT_0BGR   || pix_fmt == AV_PIX_FMT_RGB0   ||
        pix_fmt == AV_PIX_FMT_GBRP10  || pix_fmt == AV_PIX_FMT_GBRP12 ||
        pix_fmt == AV_PIX_FMT_GBRP14  || pix_fmt == AV_PIX_FMT_GBRP16 ||
        pix_fmt == AV_PIX_FMT_GBRAP   || pix_fmt == AV_PIX_FMT_GBRAP10 ||
        pix_fmt == AV_PIX_FMT_GBRAP12 || pix_fmt == AV_PIX_FMT_GBRAP14 ||
        pix_fmt == AV_PIX_FMT_GBRAP16 || pix_fmt == AV_PIX_FMT_GBRAP32 ||
        pix_fmt == AV_PIX_FMT_GBRPF16 || pix_fmt == AV_PIX_FMT_GBRAPF16 ||
        pix_fmt == AV_PIX_FMT_GBRPF32 || pix_fmt == AV_PIX_FMT_GBRAPF32 ||
        pix_fmt == AV_PIX_FMT_X2RGB10 || pix_fmt == AV_PIX_FMT_X2BGR10 ||
        pix_fmt == AV_PIX_FMT_RGBAF32 || pix_fmt == AV_PIX_FMT_RGBF32 ||
        pix_fmt == AV_PIX_FMT_RGBA128 || pix_fmt == AV_PIX_FMT_RGB96 ||
        pix_fmt == AV_PIX_FMT_XYZP12 ||
        pix_fmt == AV_PIX_FMT_GBRP || pix_fmt == AV_PIX_FMT_BAYER_RGGB16)
        ফেরত 1;
    ফেরত 0;
}

শূন্য ff_vk_set_perm(গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা lut[4], পূর্ণসংখ্যা inv)
{
    নির্বাচন (pix_fmt) {
    ক্ষেত্র AV_PIX_FMT_GBRP:
    ক্ষেত্র AV_PIX_FMT_GBRAP:
    ক্ষেত্র AV_PIX_FMT_GBRAP10:
    ক্ষেত্র AV_PIX_FMT_GBRAP12:
    ক্ষেত্র AV_PIX_FMT_GBRAP14:
    ক্ষেত্র AV_PIX_FMT_GBRAP16:
    ক্ষেত্র AV_PIX_FMT_GBRAPF16:
    ক্ষেত্র AV_PIX_FMT_GBRP10:
    ক্ষেত্র AV_PIX_FMT_GBRP12:
    ক্ষেত্র AV_PIX_FMT_GBRP14:
    ক্ষেত্র AV_PIX_FMT_GBRP16:
    ক্ষেত্র AV_PIX_FMT_GBRPF16:
    ক্ষেত্র AV_PIX_FMT_GBRPF32:
    ক্ষেত্র AV_PIX_FMT_GBRAP32:
    ক্ষেত্র AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_BGRA:
    ক্ষেত্র AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        বিরতি;
    পূর্বনির্ধারিত:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        বিরতি;
    }

    যদি (inv) {
        পূর্ণসংখ্যা lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        জন্য (পূর্ণসংখ্যা i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    ফেরত;
}

ধ্রুবক অক্ষর *ff_vk_shader_rep_fmt(গণনা AVPixelFormat pix_fmt,
                                 গণনা FFVkShaderRepFormat rep_fmt)
{
    নির্বাচন (pix_fmt) {
    ক্ষেত্র AV_PIX_FMT_RGBA:
    ক্ষেত্র AV_PIX_FMT_BGRA:
    ক্ষেত্র AV_PIX_FMT_RGB24:
    ক্ষেত্র AV_PIX_FMT_BGR24:
    ক্ষেত্র AV_PIX_FMT_BGR0:
    ক্ষেত্র AV_PIX_FMT_RGB0:
    ক্ষেত্র AV_PIX_FMT_RGB565:
    ক্ষেত্র AV_PIX_FMT_BGR565:
    ক্ষেত্র AV_PIX_FMT_UYVA:
    ক্ষেত্র AV_PIX_FMT_YUYV422:
    ক্ষেত্র AV_PIX_FMT_UYVY422: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_X2RGB10:
    ক্ষেত্র AV_PIX_FMT_X2BGR10:
    ক্ষেত্র AV_PIX_FMT_Y210:
    ক্ষেত্র AV_PIX_FMT_XV30: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ফাঁকা,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_RGB48:
    ক্ষেত্র AV_PIX_FMT_RGBA64:
    ক্ষেত্র AV_PIX_FMT_Y212:
    ক্ষেত্র AV_PIX_FMT_Y216:
    ক্ষেত্র AV_PIX_FMT_XV36:
    ক্ষেত্র AV_PIX_FMT_XV48: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_RGBAF16: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_RGBF32:
    ক্ষেত্র AV_PIX_FMT_RGBAF32: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_RGB96:
    ক্ষেত্র AV_PIX_FMT_RGBA128: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ফাঁকা,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ফেরত rep_tab[rep_fmt];
    }
    ক্ষেত্র AV_PIX_FMT_GBRP:
    ক্ষেত্র AV_PIX_FMT_GRAY8:
    ক্ষেত্র AV_PIX_FMT_GBRAP:
    ক্ষেত্র AV_PIX_FMT_YUV420P:
    ক্ষেত্র AV_PIX_FMT_YUV422P:
    ক্ষেত্র AV_PIX_FMT_YUV444P:
    ক্ষেত্র AV_PIX_FMT_YUVA420P:
    ক্ষেত্র AV_PIX_FMT_YUVA422P:
    ক্ষেত্র AV_PIX_FMT_YUVA444P: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_GRAY10:
    ক্ষেত্র AV_PIX_FMT_GRAY12:
    ক্ষেত্র AV_PIX_FMT_GRAY14:
    ক্ষেত্র AV_PIX_FMT_GRAY16:
    ক্ষেত্র AV_PIX_FMT_GBRAP10:
    ক্ষেত্র AV_PIX_FMT_GBRAP12:
    ক্ষেত্র AV_PIX_FMT_GBRAP14:
    ক্ষেত্র AV_PIX_FMT_GBRAP16:
    ক্ষেত্র AV_PIX_FMT_GBRAPF16:
    ক্ষেত্র AV_PIX_FMT_GBRP10:
    ক্ষেত্র AV_PIX_FMT_GBRP12:
    ক্ষেত্র AV_PIX_FMT_GBRP14:
    ক্ষেত্র AV_PIX_FMT_GBRP16:
    ক্ষেত্র AV_PIX_FMT_GBRPF16:
    ক্ষেত্র AV_PIX_FMT_XYZP12:
    ক্ষেত্র AV_PIX_FMT_YUV420P10:
    ক্ষেত্র AV_PIX_FMT_YUV420P12:
    ক্ষেত্র AV_PIX_FMT_YUV420P16:
    ক্ষেত্র AV_PIX_FMT_YUV422P10:
    ক্ষেত্র AV_PIX_FMT_YUV422P12:
    ক্ষেত্র AV_PIX_FMT_YUV422P16:
    ক্ষেত্র AV_PIX_FMT_YUV444P10:
    ক্ষেত্র AV_PIX_FMT_YUV444P12:
    ক্ষেত্র AV_PIX_FMT_YUV444P16:
    ক্ষেত্র AV_PIX_FMT_YUVA420P10:
    ক্ষেত্র AV_PIX_FMT_YUVA420P16:
    ক্ষেত্র AV_PIX_FMT_YUVA422P10:
    ক্ষেত্র AV_PIX_FMT_YUVA422P12:
    ক্ষেত্র AV_PIX_FMT_YUVA422P16:
    ক্ষেত্র AV_PIX_FMT_YUVA444P10:
    ক্ষেত্র AV_PIX_FMT_YUVA444P12:
    ক্ষেত্র AV_PIX_FMT_YUVA444P16:
    ক্ষেত্র AV_PIX_FMT_BAYER_RGGB16: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_GRAY32:
    ক্ষেত্র AV_PIX_FMT_GRAYF32:
    ক্ষেত্র AV_PIX_FMT_GBRPF32:
    ক্ষেত্র AV_PIX_FMT_GBRAPF32: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_GBRAP32: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ফাঁকা,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_NV12:
    ক্ষেত্র AV_PIX_FMT_NV16:
    ক্ষেত্র AV_PIX_FMT_NV24: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_P010:
    ক্ষেত্র AV_PIX_FMT_P210:
    ক্ষেত্র AV_PIX_FMT_P410: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ফাঁকা,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    ক্ষেত্র AV_PIX_FMT_P012:
    ক্ষেত্র AV_PIX_FMT_P016:
    ক্ষেত্র AV_PIX_FMT_P212:
    ক্ষেত্র AV_PIX_FMT_P216:
    ক্ষেত্র AV_PIX_FMT_P412:
    ক্ষেত্র AV_PIX_FMT_P416: {
        ধ্রুবক অক্ষর *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        ফেরত rep_tab[rep_fmt];
    };
    পূর্বনির্ধারিত:
        ফেরত "rgba32f";
    }
}

স্থির শূন্য reset_imageviews(AVRefStructOpaque unused, শূন্য *obj)
{
    FFVkImageViews *iv = obj;

    জন্য (পূর্ণসংখ্যা i = 0; i < iv->nb_views; i++) {
        যদি (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, আকার(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, পূর্ণসংখ্যা nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_অঙ্ক_তথ্য_POINTERS);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    যদি (!iv)
        ফেরত ফাঁকা;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    ফেরত iv;
}

VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, গণনা FFVkShaderRepFormat rep_fmt)
{
#define REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#define REPS_FMT_PACK(fmt, অঙ্ক) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## অঙ্ক, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## অঙ্ক, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## অঙ্ক, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## অঙ্ক,

    ধ্রুবক VkFormat fmts_map[][4] = {
        { REPS_FMT_PACK(VK_FORMAT_A2B10G10R10, 32) },
        { REPS_FMT_PACK(VK_FORMAT_A2R10G10B10, 32) },
        {
            VK_FORMAT_B5G6R5_UNORM_PACK16,
            VK_FORMAT_B5G6R5_UNORM_PACK16,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_UNDEFINED,
        },
        {
            VK_FORMAT_R5G6B5_UNORM_PACK16,
            VK_FORMAT_R5G6B5_UNORM_PACK16,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_UNDEFINED,
        },
        { REPS_FMT(VK_FORMAT_B8G8R8) },
        { REPS_FMT(VK_FORMAT_B8G8R8A8) },
        { REPS_FMT(VK_FORMAT_R8) },
        { REPS_FMT(VK_FORMAT_R8G8) },
        { REPS_FMT(VK_FORMAT_R8G8B8) },
        { REPS_FMT(VK_FORMAT_R8G8B8A8) },
        { REPS_FMT(VK_FORMAT_R16) },
        { REPS_FMT(VK_FORMAT_R16G16) },
        { REPS_FMT(VK_FORMAT_R16G16B16) },
        { REPS_FMT(VK_FORMAT_R16G16B16A16) },
        {
            VK_FORMAT_R32_UINT,
            VK_FORMAT_R32_SFLOAT,
            VK_FORMAT_R32_SINT,
            VK_FORMAT_R32_UINT,
        },
        {
            VK_FORMAT_R32G32B32_SFLOAT,
            VK_FORMAT_R32G32B32_SFLOAT,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_UNDEFINED,
        },
        {
            VK_FORMAT_R16G16B16A16_SFLOAT,
            VK_FORMAT_R16G16B16A16_SFLOAT,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_UNDEFINED,
        },
        {
            VK_FORMAT_R32G32B32A32_SFLOAT,
            VK_FORMAT_R32G32B32A32_SFLOAT,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_UNDEFINED,
        },
        {
            VK_FORMAT_R32G32B32_UINT,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_R32G32B32_SINT,
            VK_FORMAT_R32G32B32_UINT,
        },
        {
            VK_FORMAT_R32G32B32A32_UINT,
            VK_FORMAT_UNDEFINED,
            VK_FORMAT_R32G32B32A32_SINT,
            VK_FORMAT_R32G32B32A32_UINT,
        },
        {
            VK_FORMAT_R16_SFLOAT,
            VK_FORMAT_R16_SFLOAT,
            VK_FORMAT_R16_SINT,
            VK_FORMAT_R16_UINT,
        },
    };
#undef REPS_FMT_PACK
#undef REPS_FMT

    যদি (fmt == VK_FORMAT_UNDEFINED)
        ফেরত VK_FORMAT_UNDEFINED;

    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        যদি (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            ফেরত fmts_map[i][rep_fmt];
    }

    ফেরত VK_FORMAT_UNDEFINED;
}

পূর্ণসংখ্যা ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, পূর্ণসংখ্যা plane, গণনা FFVkShaderRepFormat rep_fmt)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    ধ্রুবক VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];
    ধ্রুবক পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_পরবর্তী      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_to_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_identity_map,
        .subresourceRange = {
            .aspectMask = ff_vk_aspect_flag(f, plane),
            .level_গুনতি = 1,
            .layer_গুনতি = 1,
        },
    };
    যদি (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        ফেরত AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspectMask;

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_অঙ্ক_তথ্য_POINTERS],
                                AVFrame *f,
                                ধ্রুবক VkFormat fmts[AV_অঙ্ক_তথ্য_POINTERS])
{
    পূর্ণসংখ্যা err = 0;
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->তথ্য[0];
    ধ্রুবক পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);
    ধ্রুবক পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_অঙ্ক_তথ্য_POINTERS] = { 0 };

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_পরবর্তী      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_identity_map,
            .subresourceRange = {
                .aspectMask = ff_vk_aspect_flag(f, i),
                .level_গুনতি = 1,
                .layer_গুনতি = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            যাও fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    জন্য (পূর্ণসংখ্যা i = 0; i < nb_planes; i++)
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    memcpy(views, tmp_views, nb_planes*আকার(*views));

    ফেরত 0;

fail:
    জন্য (পূর্ণসংখ্যা i = 0; i < nb_planes; i++)
        যদি (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    ফেরত err;
}

পূর্ণসংখ্যা ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_অঙ্ক_তথ্য_POINTERS],
                            AVFrame *f, গণনা FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    ধ্রুবক VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ধ্রুবক পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(hwfc->sw_format);
    VkFormat fmts[AV_অঙ্ক_তথ্য_POINTERS] = { 0 };

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_to_rep(rep_fmts[i], rep_fmt);
        যদি (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            ফেরত AVERROR(EINVAL);
        }
    }

    ফেরত ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

শূন্য ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, পূর্ণসংখ্যা *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    পূর্ণসংখ্যা found = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->তথ্য[0];
    ধ্রুবক পূর্ণসংখ্যা nb_images = ff_vk_গুনতি_images(vkf);
    জন্য (পূর্ণসংখ্যা i = 0; i < e->nb_frame_deps; i++)
        যদি (e->frame_deps[i]->তথ্য[0] == pic->তথ্য[0]) {
            যদি (e->frame_update[i])
                found = i;
            বিরতি;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    জন্য (পূর্ণসংখ্যা i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (VkImageMemoryBarrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .p_পরবর্তী = ফাঁকা,
            .srcStageMask = src_stage,
            .dstStageMask = dst_stage,
            .srcAccessMask = found >= 0 ? e->access_dst[found] : VK_ACCESS_2_NONE,
            .dstAccessMask = new_access,
            .oldLayout = found >= 0 ? e->layout_dst[found] : vkf->layout[0],
            .newLayout = new_layout,
            .src_Queue_Family_সূচক = found >= 0 ? e->queue_family_dst[found] : vkf->queue_family[0],
            .dst_Queue_Family_সূচক = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .layer_গুনতি = 1,
                .level_গুনতি = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], ফাঁকা);
}

পূর্ণসংখ্যা ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_আকার[3], uint32_t required_subgroup_আকার)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    memcpy(shd->lg_আকার, wg_আকার, 3*আকার(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_আকার_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_আকার_CREATE_INFO,
        .required_Subgroup_আকার = required_subgroup_আকার,
    };

    নির্বাচন (shd->stage) {
    ক্ষেত্র VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
    ক্ষেত্র VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    ক্ষেত্র VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
    ক্ষেত্র VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    ক্ষেত্র VK_SHADER_STAGE_MISS_BIT_KHR:
    ক্ষেত্র VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        বিরতি;
    ক্ষেত্র VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        বিরতি;
    পূর্বনির্ধারিত:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        বিরতি;
    };

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pSetLayouts            = shd->desc_layout,
        .set_Layout_গুনতি         = shd->nb_descriptor_sets,
        .ঠেলো_Constant_Range_গুনতি = shd->ঠেলো_consts_অঙ্ক,
        .p_ঠেলো_Constant_Ranges    = shd->ঠেলো_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ধ্রুবক uint8_t *spirv, size_t spirv_len)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_পরবর্তী    = ফাঁকা,
        .flags    = 0x0,
        .pCode    = (শূন্য *)spirv,
        .code_আকার = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ধ্রুবক অক্ষর *entrypoint)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_পরবর্তী = shd->subgroup_info.required_Subgroup_আকার ?
                     &shd->subgroup_info : ফাঁকা,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_আকার ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    যদি (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        ফেরত AVERROR_EXTERNAL;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ফলাফল ret;
    FFVulkanFunctions *vk = &s->vkfn;

    পূর্ণসংখ্যা has_singular = 0;
    পূর্ণসংখ্যা max_descriptors = 0;
    জন্য (পূর্ণসংখ্যা i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_set[i].nb_bindings);
        যদি (shd->desc_set[i].singular)
            has_singular = 1;
    }
    shd->use_ঠেলো = (s->extensions & FF_VK_EXT_ঠেলো_DESCRIPTOR) &&
                    (max_descriptors <= s->ঠেলো_desc_props.max_ঠেলো_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    জন্য (পূর্ণসংখ্যা i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkanDescriptorSet *set = &shd->desc_set[i];
        VkDescriptorSetLayoutCreateInfo desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .binding_গুনতি = set->nb_bindings,
            .pBindings = set->binding,
            .flags = (shd->use_ঠেলো) ?
                     VK_DESCRIPTOR_SET_LAYOUT_CREATE_ঠেলো_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->CreateDescriptorSetLayout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            ফেরত AVERROR_EXTERNAL;
        }
    }

    ফেরত 0;
}

পূর্ণসংখ্যা ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ধ্রুবক অক্ষর *spirv, size_t spirv_len,
                      ধ্রুবক অক্ষর *entrypoint)
{
    পূর্ণসংখ্যা err;
    FFVulkanFunctions *vk = &s->vkfn;
    VkSpecializationMapEntry spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t প্রবেশ_আকার = spirv_len;

    যদি (shd->precompiled) {
        যদি (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_Entry_গুনতি = 0,
                .p_তথ্য = shd->lg_আকার,
                .তথ্য_আকার_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        VkSpecializationMapEntry *spe = (শূন্য *)shd->specialization_info->pMapEntries;
        জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_Entry_গুনতি++] = (VkSpecializationMapEntry) {
                .constantID = 253 + i,
                .offset = shd->specialization_info->তথ্য_আকার_2 + i*আকার(uint32_t),
                .আকার_2 = আকার(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_তথ্য;
        memcpy(&spd[shd->specialization_info->তথ্য_আকার_2],
               shd->lg_আকার, 3*আকার(uint32_t));
        shd->specialization_info->তথ্য_আকার_2 += 3*আকার(uint32_t);

#যদি CONFIG_SHADER_COMPRESSION
        uint8_t *out;
        size_t out_len;
        পূর্ণসংখ্যা ret = ff_zlib_expand(s, &out, &out_len, spirv, spirv_len);
        যদি (ret < 0)
            ফেরত ret;
        spirv = out;
        spirv_len = out_len;
#endif
    }

    err = init_descriptors(s, shd);
    যদি (err < 0)
        যাও end;

    err = init_pipeline_layout(s, shd);
    যদি (err < 0)
        যাও end;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    যদি (err < 0)
        যাও end;

    নির্বাচন (shd->bind_point) {
    ক্ষেত্র VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        বিরতি;
    পূর্বনির্ধারিত:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        যাও end;
        বিরতি;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    যদি (err < 0)
        যাও end;

    যদি (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    অন্যথা
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    যদি (প্রবেশ_আকার != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", প্রবেশ_আকার);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

end:
    যদি (shd->precompiled) {
        shd->specialization_info->map_Entry_গুনতি -= 3;
        shd->specialization_info->তথ্য_আকার_2 -= 3*আকার(uint32_t);
    }
#যদি CONFIG_SHADER_COMPRESSION
    যদি (shd->precompiled)
        av_free((শূন্য *)spirv);
#endif
    ফেরত err;
}

শূন্য ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ধ্রুবক FFVulkanDescriptorSetBinding *desc, পূর্ণসংখ্যা nb,
                                     পূর্ণসংখ্যা singular)
{
    FFVulkanDescriptorSet *set = &shd->desc_set[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    জন্য (পূর্ণসংখ্যা i = 0; i < nb; i++) {
        set->binding[i].binding            = i;
        set->binding[i].descriptorType     = desc[i].type;
        set->binding[i].descriptor_গুনতি    = FFMAX(desc[i].elems, 1);
        set->binding[i].stageFlags         = desc[i].stages;
        set->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < nb; i++) {
        পূর্ণসংখ্যা j;
        জন্য (j = 0; j < shd->nb_desc_pool_আকার; j++)
            যদি (shd->desc_pool_আকার[j].type == desc[i].type)
                বিরতি;
        যদি (j >= shd->nb_desc_pool_আকার) {
            shd->nb_desc_pool_আকার++;
            av_assert1(shd->nb_desc_pool_আকার < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_আকার[j].type             = desc[i].type;
        shd->desc_pool_আকার[j].descriptor_গুনতি += FFMAX(desc[i].elems, 1);
    }

    set->singular = singular;
    set->nb_bindings = nb;
}

পূর্ণসংখ্যা ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    যদি (!shd->nb_descriptor_sets)
        ফেরত 0;

    FFVulkan_Shader_তথ্য *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    যদি (!shd->use_ঠেলো) {
        Vk_ফলাফল ret;
        FFVulkanFunctions *vk = &s->vkfn;
        VkDescriptorSetLayout *tmp_layouts;
        VkDescriptorSetAllocateInfo set_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        জন্য (পূর্ণসংখ্যা i = 0; i < shd->nb_desc_pool_আকার; i++)
            shd->desc_pool_আকার[i].descriptor_গুনতি *= pool->pool_আকার;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_আকার,
            .pool_আকার_গুনতি = shd->nb_desc_pool_আকার,
            .maxSets = sd->nb_descriptor_sets*pool->pool_আকার,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            ফেরত AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, আকার(*tmp_layouts));
        যদি (!tmp_layouts)
            ফেরত AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        জন্য (পূর্ণসংখ্যা i = 0; i < pool->pool_আকার; i++)
            জন্য (পূর্ণসংখ্যা j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        set_alloc_info = (VkDescriptorSetAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .pSetLayouts        = tmp_layouts,
            .descriptor_Set_গুনতি = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        আকার(*tmp_layouts));
        যদি (!sd->desc_sets) {
            av_free(tmp_layouts);
            ফেরত AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &set_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        যদি (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            ফেরত AVERROR_EXTERNAL;
        }
    }

    ফেরত 0;
}

স্থির অন্তঃরেখ ধ্রুবক FFVulkan_Shader_তথ্য *get_shd_তথ্য(FFVkExecContext *e,
                                                     ধ্রুবক FFVulkanShader *shd)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < e->parent->nb_reg_shd; i++)
        যদি (e->parent->reg_shd[i].shd == shd)
            ফেরত &e->parent->reg_shd[i];
    ফেরত ফাঁকা;
}

স্থির অন্তঃরেখ শূন্য update_set_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, পূর্ণসংখ্যা set,
                                         VkWriteDescriptorSet *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];
    ধ্রুবক FFVulkan_Shader_তথ্য *sd = get_shd_তথ্য(e, shd);

    যদি (desc_set->singular) {
        জন্য (পূর্ণসংখ্যা i = 0; i < e->parent->pool_আকার; i++) {
            write_info->dstSet = sd->desc_sets[i*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ফাঁকা);
        }
    } অন্যথা {
        যদি (shd->use_ঠেলো) {
            vk->Cmd_ঠেলো_Descriptor_Set_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        set, 1,
                                        write_info);
        } অন্যথা {
            write_info->dstSet = sd->desc_sets[e->idx*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ফাঁকা);
        }
    }
}

পূর্ণসংখ্যা ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, পূর্ণসংখ্যা set, পূর্ণসংখ্যা bind, পূর্ণসংখ্যা offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    VkWriteDescriptorSet desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstBinding = bind,
        .descriptor_গুনতি = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ফেরত 0;
}

শূন্য ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, পূর্ণসংখ্যা set, পূর্ণসংখ্যা binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->তথ্য;
    ধ্রুবক পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(hwfc->sw_format);

    জন্য (পূর্ণসংখ্যা i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, set, binding, i,
                                views[i], layout, sampler);
}

পূর্ণসংখ্যা ff_vk_shader_update_desc_বাফার(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    পূর্ণসংখ্যা set, পূর্ণসংখ্যা bind, পূর্ণসংখ্যা elem,
                                    FFVk_বাফার *buf, Vk_Device_আকার offset, Vk_Device_আকার len,
                                    VkFormat fmt)
{
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];

    Vk_Descriptor_বাফার_Info desc_pool_write_info_buf = {
        .বাফার = buf->buf,
        .offset = buf->virtual_offset + offset,
        .range = len,
    };
    VkWriteDescriptorSet desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstBinding = bind,
        .descriptor_গুনতি = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .p_বাফার_Info = &desc_pool_write_info_buf,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ফেরত 0;
}

শূন্য ff_vk_shader_update_ঠেলো_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    পূর্ণসংখ্যা offset, size_t আকার_2, শূন্য *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ঠেলো_Constants(e->buf, shd->pipeline_layout,
                         stage, offset, আকার_2, src);
}

শূন্য ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ধ্রুবক FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ধ্রুবক FFVulkan_Shader_তথ্য *sd = get_shd_তথ্য(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    যদি (sd && sd->nb_descriptor_sets) {
        যদি (!shd->use_ঠেলো) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_point, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ফাঁকা);
        }
    }
}

শূন্য ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#যদি 0
    যদি (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#endif

    যদি (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    যদি (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    জন্য (পূর্ণসংখ্যা i = 0; i < shd->nb_descriptor_sets; i++)
        যদি (shd->desc_layout[i])
            vk->DestroyDescriptorSetLayout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

শূন্য ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#ifdef VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#endif
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_বাফার_unref(&s->device_ref);
    av_বাফার_unref(&s->frames_ref);
}

পূর্ণসংখ্যা ff_vk_init(FFVulkanContext *s, শূন্য *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref)
{
    পূর্ণসংখ্যা err;

    স্থির ধ্রুবক AVClass vulkan_context_class = {
        .class_name       = "vk",
        .version          = LIBAVUTIL_VERSION_INT,
        .parent_log_context_offset = offsetof(FFVulkanContext, log_parent),
    };

    memset(s, 0, আকার(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    যদি (frames_ref) {
        s->frames_ref = av_বাফার_ref(frames_ref);
        যদি (!s->frames_ref)
            ফেরত AVERROR(ENOMEM);

        s->frames = (AVHWFramesContext *)s->frames_ref->তথ্য;
        s->hwfc = s->frames->hwctx;

        device_ref = s->frames->device_ref;
    }

    s->device_ref = av_বাফার_ref(device_ref);
    যদি (!s->device_ref) {
        ff_vk_uninit(s);
        ফেরত AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->তথ্য;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_to_mask(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_to_mask(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_load_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    যদি (err < 0) {
        ff_vk_uninit(s);
        ফেরত err;
    }

    err = ff_vk_load_props(s);
    যদি (err < 0) {
        ff_vk_uninit(s);
        ফেরত err;
    }

    ফেরত 0;
}
