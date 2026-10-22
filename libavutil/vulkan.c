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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "random_seed.h"
#ಅನ್ತರ್ಭಾವ "refstruct.h"

#ಅನ್ತರ್ಭಾವ "vulkan.h"
#ಅನ್ತರ್ಭಾವ "libavutil/vulkan_loader.h"

#ಯದಿ CONFIG_SHADER_COMPRESSION
#ಅನ್ತರ್ಭಾವ "libavutil/zlib_utils.h"
#endif

ಧ್ರುವ VkComponentMapping ff_comp_identity_map = {
    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
};

/* Converts return values to strings */
ಧ್ರುವ ವರ್ಣ *ff_vk_ret2str(VkResult res)
{
#define CASE(VAL) ಪಕ್ಷ VAL: ಪ್ರತ್ಯಾಗಮ #VAL
    ವಿಕಲ್ಪ (res) {
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
    ಸ್ವಭಾವ: ಪ್ರತ್ಯಾಗಮ "Unknown error";
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
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ಒಳಹರಿವು_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        ಪ್ರತ್ಯಾಗಮ dst;                                                     \
    }

#define MAP_TO(flag1, flag2) ಯದಿ (src & flag2) dst |= flag1;
FN_MAP_TO(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#undef MAP_TO
#define MAP_TO(flag1, flag2) ಯದಿ (src & flag1) dst |= flag2;
FN_MAP_TO(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#undef MAP_TO
#undef FN_MAP_TO

ಸ್ಥಿರ ಶೂನ್ಯ load_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        ಪೂರ್ಣಾಙ್ಕ skip = 0;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < s->nb_qfs; j++) {
            ಯದಿ (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (skip)
            ಅನುವರ್ತ;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_imageviews(AVRefStructOpaque unused, ಶೂನ್ಯ *obj);

ಪೂರ್ಣಾಙ್ಕ ff_vk_load_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ತಳ್ಳು_desc_props, FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ತಳ್ಳು_DESCRIPTOR_PROPERTIES_KHR);
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

    ಯದಿ (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(ಪರಿಮಾಣ(FFVkImageViews), 0,
                                                         ರಿಕ್ತ, ರಿಕ್ತ, reset_imageviews,
                                                         ರಿಕ್ತ, ರಿಕ್ತ);
        ಯದಿ (!s->imageviews_pool)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(ಪರಿಮಾಣ(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    ಯದಿ (s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ == 512 ||
        s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ == 512) {
        VkImageLayout *new_array;
        size_t new_size;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ರಿಕ್ತ;
        s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ =
        s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_size = s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ +
                   s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ;
        new_size *= ಪರಿಮಾಣ(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_size);
        ಯದಿ (!new_array)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->GetPhysicalDeviceMemoryProperties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->mprops.memory_Type_ಎಣಿಕೆ; i++)
        s->host_cached_flag |= s->mprops.memoryTypes[i].propertyFlags &
                               VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

    load_enabled_qfs(s);

    ಯದಿ (s->qf_props)
        ಪ್ರತ್ಯಾಗಮ 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ರಿಕ್ತ);

    s->qf_props = av_calloc(s->tot_nb_qfs, ಪರಿಮಾಣ(*s->qf_props));
    ಯದಿ (!s->qf_props)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, ಪರಿಮಾಣ(*s->query_props));
    ಯದಿ (!s->qf_props) {
        av_freep(&s->qf_props);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, ಪರಿಮಾಣ(*s->video_props));
    ಯದಿ (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

#ifdef VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, ಪರಿಮಾಣ(*s->ownership_props));
    ಯದಿ (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
#endif

    ಪ್ರತಿ (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR);
#ifdef VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#endif
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    ಯದಿ (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ರಿಕ್ತ);

        ಯದಿ (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                ಪರಿಮಾಣ(VkCooperativeMatrixPropertiesKHR));
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->hwctx->nb_qf; i++) {
        ಯದಿ ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            ಪ್ರತ್ಯಾಗಮ &s->hwctx->qf[i];
        }
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

ಶೂನ್ಯ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        ಯದಿ (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_ಎಣಿಕೆ = 1,
                .pSemaphores = &e->sem,
                .p_ಮೌಲ್ಯಗಳು = &e->sem_ಮೌಲ್ಯ,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->lock);
    }

    /* Free shader-specific data */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkanShaderData *sd = &pool->reg_shd[i];

        ಯದಿ (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++) {
        ಯದಿ (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        ಯದಿ (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    ಯದಿ (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_data);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_size = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ಸ್ಥಿರ atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ರಿಕ್ತ)->qf)];
ಸ್ಥಿರ AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ಸ್ಥಿರ ಶೂನ್ಯ exec_pool_phase_seed(ಶೂನ್ಯ)
{
    uint32_t seed = av_get_random_seed();
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], seed, memory_order_relaxed);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, ಪೂರ್ಣಾಙ್ಕ nb_contexts,
                         ಪೂರ್ಣಾಙ್ಕ nb_queries, VkQueryType query_type, ಪೂರ್ಣಾಙ್ಕ query_64bit,
                         ಧ್ರುವ ಶೂನ್ಯ *query_create_pnext)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    VkCommandBufferAllocateInfo cbuf_create;

    ಧ್ರುವ VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ರಿಕ್ತ;

    atomic_init(&pool->idx, 0);

    ಯದಿ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        ಯದಿ (!ef)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*ಪರಿಮಾಣ(*pool->cmd_buf_pools));
    ಯದಿ (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*ಪರಿಮಾಣ(*pool->cmd_bufs));
    ಯದಿ (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (VkCommandBufferAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_Buffer_ಎಣಿಕೆ = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }
    }

    /* Query pool */
    ಯದಿ (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .pNext = query_create_pnext,
            .queryType = query_type,
            .query_ಎಣಿಕೆ = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_status_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        ಯದಿ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            ಪೂರ್ಣಾಙ್ಕ nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_status_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } ಅನ್ಯಥಾ ಯದಿ (query_type == VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR) {
            pool->query_status_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_size = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_data = av_calloc(nb_contexts, pool->qd_size);
        ಯದಿ (!pool->query_data) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, ಪರಿಮಾಣ(*pool->contexts));
    ಯದಿ (!pool->contexts) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    pool->pool_size = nb_contexts;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++)
        pthread_mutex_init(&pool->contexts[i].lock, ರಿಕ್ತ);

#ifdef VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    ಪೂರ್ಣಾಙ್ಕ internal_queue_sync = 0;
    ಯದಿ (s->extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC) {
        ಧ್ರುವ VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_find_struct(s->hwctx->device_features.pNext,
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
    ಪೂರ್ಣಾಙ್ಕ pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_data = ((uint8_t *)pool->query_data) + pool->qd_size*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->ಅಂಕೆ : (i + phase) % qf->ಅಂಕೆ;
        e->qf = qf->idx;
        VkDeviceQueueInfo2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
#ifdef VK_KHR_internally_synchronized_queues
            .flags            = internal_queue_sync ?
                                VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR : 0,
#endif
            .queueFamilyIndex = qf->idx,
            .queueIndex       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->queue);
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    ಪ್ರತ್ಯಾಗಮ err;
}

VkResult ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ಶೂನ್ಯ **data, VkQueryResultFlagBits flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ಧ್ರುವ FFVkExecPool *pool = e->parent;
    VkQueryResultFlags qf = flags & ~(VK_QUERY_RESULT_64_BIT |
                                      VK_QUERY_RESULT_WITH_STATUS_BIT_KHR);

    ಯದಿ (!e->query_data) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        ಪ್ರತ್ಯಾಗಮ VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_RESULT_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_RESULT_WITH_STATUS_BIT_KHR : 0x0;

    ಯದಿ (data)
        *data = e->query_data;

    ಪ್ರತ್ಯಾಗಮ vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_size, e->query_data,
                                   pool->qd_size, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        ಯದಿ (pthread_mutex_trylock(&e->lock))
            ಅನುವರ್ತ; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        ಯದಿ (vk->Get_Semaphore_Counter_ಮೌಲ್ಯ(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_ಮೌಲ್ಯ &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->lock);
    }

    ಪ್ರತ್ಯಾಗಮ &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_size];
}

ಶೂನ್ಯ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ಎಣಿಕೆ = 1,
        .pSemaphores = &e->sem,
        .p_ಮೌಲ್ಯಗಳು = &e->sem_ಮೌಲ್ಯ,
    };
    pthread_mutex_lock(&e->lock);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->lock);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ಧ್ರುವ FFVkExecPool *pool = e->parent;

    VkCommandBufferBeginInfo cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ಎಣಿಕೆ = 1,
        .pSemaphores = &e->sem,
        .p_ಮೌಲ್ಯಗಳು = &e->sem_ಮೌಲ್ಯ,
    };

    pthread_mutex_lock(&e->lock);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->BeginCommandBuffer(e->buf, &cmd_start);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->lock);
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಯದಿ (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_ಮೌಲ್ಯ++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .ಮೌಲ್ಯ = e->sem_ಮೌಲ್ಯ,
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->lock);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_buf_deps; j++)
        av_buffer_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        ವಿಕಲ್ಪ (od->type) {
        ಪಕ್ಷ VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            ಭಙ್ಗ;
        ಪಕ್ಷ VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        ಯದಿ (e->frame_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->data[0];
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

ಶೂನ್ಯ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .ಮೌಲ್ಯ = e->sem_ಮೌಲ್ಯ,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->ResetCommandBuffer(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

ಶೂನ್ಯ ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ಶೂನ್ಯ *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

ಶೂನ್ಯ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ಶೂನ್ಯ *obj)
{
    ಶೂನ್ಯ **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->nb_refstruct_deps; i++) {
        ಯದಿ (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            ಪ್ರತ್ಯಾಗಮ;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ರಿಕ್ತ;
}

ಶೂನ್ಯ ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    ಯದಿ (!e->sw_frame_deps[e->nb_sw_frame_deps])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ಮೌಲ್ಯ = val,
        .stageMask = stage,
    };
}

ಶೂನ್ಯ ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ಮೌಲ್ಯ = val,
        .stageMask = stage,
    };
}

ಶೂನ್ಯ ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ಪೂರ್ಣಾಙ್ಕ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ಪೂರ್ಣಾಙ್ಕ wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    ಯದಿ (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stageMask = stage,
            };
        }

        ಪ್ರತ್ಯಾಗಮ;
    }

    /* Ownership of each semaphore passes to the execution */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb; i++) {
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_add_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);

    /* Don't add duplicates */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->nb_frame_deps; i++)
        ಯದಿ (e->frame_deps[i]->data[0] == f->data[0])
            ಪ್ರತ್ಯಾಗಮ 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    ಯದಿ (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_buffer_ref(f->buf[0]);
        ಯದಿ (!e->buf_deps[e->nb_buf_deps])
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->lock_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ಮೌಲ್ಯ = vkf->sem_ಮೌಲ್ಯ[i],
            .stageMask = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ಮೌಲ್ಯ = vkf->sem_ಮೌಲ್ಯ[i] + 1,
            .stageMask = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_ಮೌಲ್ಯ[i];
        e->sem_sig_val_dst_cnt++;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < e->nb_frame_deps; i++)
        ಯದಿ (e->frame_deps[i]->data[0] == f->data[0])
            ಭಙ್ಗ;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    ಯದಿ (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dstQueueFamilyIndex;
    e->access_dst[i] = bar->dstAccessMask;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_mirror_sem_ಮೌಲ್ಯ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];

    /* Reject unknown frames */
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < e->nb_frame_deps; i++)
        ಯದಿ (e->frame_deps[i]->data[0] == f->data[0])
            ಭಙ್ಗ;
    ಯದಿ (i == e->nb_frame_deps)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_ಮೌಲ್ಯ[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkCommandBufferSubmitInfo cmd_buf_info = (VkCommandBufferSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pCommandBufferInfos = &cmd_buf_info,
        .command_Buffer_Info_ಎಣಿಕೆ = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_ಎಣಿಕೆ = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_ಎಣಿಕೆ = e->sem_sig_cnt,
    };

    ret = vk->EndCommandBuffer(e->buf);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

#ಯದಿ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->lock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#ಯದಿ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < e->nb_frame_deps; j++) {
        ಯದಿ (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->data[0];

            ಯದಿ (e->frame_update[j]) {
                ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
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

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, ಶೂನ್ಯ *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    VkResult ret;
    ಪೂರ್ಣಾಙ್ಕ index = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    VkMemoryAllocateInfo alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext           = alloc_extension,
    };

    alloc_info.allocationSize = req->size;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < s->mprops.memory_Type_ಎಣಿಕೆ; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        ಯದಿ (!(req->memoryTypeBits & (1 << i)))
            ಅನುವರ್ತ;

        /* The memory type flags must include our properties */
        ಯದಿ ((req_flags != UINT32_MAX) &&
            ((s->mprops.memoryTypes[i].propertyFlags & req_flags) != req_flags))
            ಅನುವರ್ತ;

        /* Found a suitable memory type */
        index = i;
        ಭಙ್ಗ;
    }

    ಯದಿ (index < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    alloc_info.memoryTypeIndex = index;

    ret = vk->AllocateMemory(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    ಯದಿ (ret != VK_SUCCESS)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (mem_flags)
        *mem_flags |= s->mprops.memoryTypes[index].propertyFlags;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, VkFormat format, ಪೂರ್ಣಾಙ್ಕ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ಶೂನ್ಯ *create_pnext)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMemoryPropertyFlagBits mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pNext         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { width, height, 1 },
        .mipLevels     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_ಎಣಿಕೆ_1_BIT,
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
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->GetImageMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.memoryRequirements,
                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    bind_info.image  = *img;
    bind_info.memory = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಗಚ್ಛ fail;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ff_vk_image_free(s, img, mem);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಶೂನ್ಯ ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಯದಿ (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    ಯದಿ (*mem) {
        vk->FreeMemory(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, size_t size,
                     ಶೂನ್ಯ *pNext, ಶೂನ್ಯ *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    ಪೂರ್ಣಾಙ್ಕ use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    VkBufferCreateInfo buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext       = pNext,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .size        = flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ?
                       FFALIGN(size, s->props.properties.limits.minMemoryMapAlignment) :
                       size,
    };

    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    VkBufferMemoryRequirementsInfo2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2,
    };
    VkMemoryDedicatedAllocateInfo ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
        .pNext = alloc_pNext,
    };
    VkMemoryDedicatedRequirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
    };
    VkMemoryRequirements2 req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
        .pNext = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           size, usage, flags);

    ret = vk->CreateBuffer(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    req_desc.buffer = buf->buf;

    vk->GetBufferMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefersDedicatedAllocation |
                  ded_req.requiresDedicatedAllocation;
    ಯದಿ (use_ded_mem) {
        ded_alloc.buffer = buf->buf;
        ded_alloc.pNext = alloc_pNext;
        alloc_pNext = &ded_alloc;
    }

    ಯದಿ (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags.pNext = alloc_pNext;
        alloc_pNext = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.memoryRequirements, flags, alloc_pNext,
                          &buf->flags, &buf->mem);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    ret = vk->BindBufferMemory(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಯದಿ (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        VkBufferDeviceAddressInfo address_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
            .buffer = buf->buf,
        };
        buf->address = vk->GetBufferDeviceAddress(s->hwctx->act_dev, &address_info);
    }

    buf->size = size;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      ಪೂರ್ಣಾಙ್ಕ nb_buffers, ಪೂರ್ಣಾಙ್ಕ invalidate)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange inval_list[64];
    ಪೂರ್ಣಾಙ್ಕ inval_ಎಣಿಕೆ = 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_buffers; i++) {
        ಶೂನ್ಯ *dst;
        ret = vk->MapMemory(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_WHOLE_SIZE, 0, &dst);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        ಯದಿ (mem)
            mem[i] = dst;
    }

    ಯದಿ (!invalidate)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_buffers; i++) {
        ಧ್ರುವ VkMappedMemoryRange ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            .memory = buf[i]->mem,
            .size   = VK_WHOLE_SIZE,
        };
        ಯದಿ (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            ಅನುವರ್ತ;
        inval_list[inval_ಎಣಿಕೆ++] = ival_buf;
    }

    ಯದಿ (inval_ಎಣಿಕೆ) {
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, inval_ಎಣಿಕೆ,
                                               inval_list);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       ಪೂರ್ಣಾಙ್ಕ flush)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ಯದಿ (buf->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಧ್ರುವ VkMappedMemoryRange flush_data = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = buf->mem,
        .offset = offset,
        .size   = mem_size,
    };

    ಯದಿ (flush)
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);
    ಅನ್ಯಥಾ
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);

    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, ಪೂರ್ಣಾಙ್ಕ nb_buffers,
                        ಪೂರ್ಣಾಙ್ಕ flush)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange flush_list[64];
    ಪೂರ್ಣಾಙ್ಕ flush_ಎಣಿಕೆ = 0;

    ಯದಿ (flush) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_buffers; i++) {
            ಧ್ರುವ VkMappedMemoryRange flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .memory = buf[i]->mem,
                .size   = VK_WHOLE_SIZE,
            };

            av_assert0(!buf[i]->host_ref);
            ಯದಿ (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                ಅನುವರ್ತ;
            flush_list[flush_ಎಣಿಕೆ++] = flush_buf;
        }
    }

    ಯದಿ (flush_ಎಣಿಕೆ) {
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, flush_ಎಣಿಕೆ,
                                          flush_list);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_buffers; i++) {
        vk->UnmapMemory(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ err;
}

ಶೂನ್ಯ ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಯದಿ (!buf || !s->hwctx)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_buffer(s, buf, 0);
    ಯದಿ (buf->buf != VK_NULL_HANDLE)
        vk->DestroyBuffer(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    ಯದಿ (buf->mem != VK_NULL_HANDLE)
        vk->FreeMemory(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    ಯದಿ (buf->host_ref)
        av_buffer_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ pooled_buf_free(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            ಶೂನ್ಯ *create_pNext, size_t size,
                            VkMemoryPropertyFlagBits mem_props)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    FFVkBuffer *data;

    ಯದಿ (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(ಪರಿಮಾಣ(FFVkBuffer), 0, ctx,
                                                ರಿಕ್ತ, ರಿಕ್ತ, pooled_buf_free,
                                                ರಿಕ್ತ);
        ಯದಿ (!(*buf_pool))
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    *buf = data = av_refstruct_pool_get(*buf_pool);
    ಯದಿ (!data)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (data->size >= size)
        ಪ್ರತ್ಯಾಗಮ 0;

    ff_vk_free_buf(ctx, data);
    memset(data, 0, ಪರಿಮಾಣ(*data));

    err = ff_vk_create_buf(ctx, data, size,
                           create_pNext, ರಿಕ್ತ, usage,
                           mem_props);
    ಯದಿ (err < 0) {
        av_refstruct_unref(buf);
        ಪ್ರತ್ಯಾಗಮ err;
    }

    ಯದಿ (mem_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_buffer(ctx, data, &data->mapped_mem, 0);
        ಯದಿ (err < 0) {
            av_refstruct_unref(buf);
            ಪ್ರತ್ಯಾಗಮ err;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ create_mapped_buffer(FFVulkanContext *s,
                                FFVkBuffer *vkb, VkBufferUsageFlags usage,
                                size_t size,
                                VkExternalMemoryBufferCreateInfo *create_desc,
                                VkImportMemoryHostPointerInfoEXT *import_desc,
                                VkMemoryHostPointerPropertiesEXT props)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkBufferCreateInfo buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext       = create_desc,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .size        = size,
    };
    VkMemoryRequirements req = {
        .size           = size,
        .alignment      = s->hprops.minImportedHostPointerAlignment,
        .memoryTypeBits = props.memoryTypeBits,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                          import_desc, &vkb->flags, &vkb->mem);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    ret = vk->CreateBuffer(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    ಯದಿ (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ret = vk->BindBufferMemory(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    ಯದಿ (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->DestroyBuffer(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ host_map_free(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          ಧ್ರುವ AVBufferRef *src_buf,
                          VkBufferUsageFlags usage)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkExternalMemoryBufferCreateInfo create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
    };
    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    VkImportMemoryHostPointerInfoEXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT,
        .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
        .pNext = usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT ? &alloc_flags : ರಿಕ್ತ,
    };
    VkMemoryHostPointerPropertiesEXT props;

    AVBufferRef *ref;
    FFVkBuffer *vkb;
    size_t offs;
    size_t buffer_size;

    *dst = ರಿಕ್ತ;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_data % s->hprops.minImportedHostPointerAlignment;
    import_desc.pHostPointer = src_data - offs;

    props = (VkMemoryHostPointerPropertiesEXT) {
        VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT,
    };
    ret = vk->GetMemoryHostPointerPropertiesEXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.pHostPointer,
                                                &props);
    ಯದಿ (!(ret == VK_SUCCESS && props.memoryTypeBits))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_buffer_ref(src_buf);
    ಯದಿ (!ref)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ಧ್ರುವ VkDeviceSize src_avail = src_buf->size - (src_data - src_buf->data);
    buffer_size = offs + FFMIN(size, src_avail);
    buffer_size = FFALIGN(buffer_size, s->props.properties.limits.minMemoryMapAlignment);
    buffer_size = FFALIGN(buffer_size, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(ಪರಿಮಾಣ(*vkb), 0, s, host_map_free);
    ಯದಿ (!vkb) {
        av_buffer_unref(&ref);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    err = create_mapped_buffer(s, vkb, usage,
                               buffer_size, &create_desc, &import_desc,
                               props);
    ಯದಿ (err < 0) {
        av_buffer_unref(&ref);
        av_refstruct_unref(&vkb);
        ಪ್ರತ್ಯಾಗಮ err;
    }

    ಯದಿ (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        VkBufferDeviceAddressInfo address_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
            .buffer = vkb->buf,
        };
        vkb->address = vk->GetBufferDeviceAddress(s->hwctx->act_dev, &address_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_offset = offs;
    vkb->address       += offs;
    vkb->mapped_mem     = src_data;
    vkb->size           = buffer_size - offs;

    *dst = vkb;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_add_ತಳ್ಳು_const(FFVulkanShader *shd, ಪೂರ್ಣಾಙ್ಕ offset, ಪೂರ್ಣಾಙ್ಕ size,
                                VkShaderStageFlagBits stage)
{
    Vk_ತಳ್ಳು_Constant_Range *pc = &shd->ತಳ್ಳು_consts[shd->ತಳ್ಳು_consts_ಅಂಕೆ++];
    av_assert1(shd->ತಳ್ಳು_consts_ಅಂಕೆ < FF_VK_MAX_ತಳ್ಳು_CONSTS);
    pc->stageFlags = stage;
    pc->offset = offset;
    pc->size = size;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ಪೂರ್ಣಾಙ್ಕ unnorm_coords, VkFilter filt)
{
    VkResult ret;
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
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ಪೂರ್ಣಾಙ್ಕ p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);

    ಸ್ಥಿರ ಧ್ರುವ VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    ಯದಿ (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_COLOR_BIT;

    ಪ್ರತ್ಯಾಗಮ plane_aspect[p];
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_mt_is_np_rgb(ಗಣನಾ AVPixelFormat pix_fmt)
{
    ಯದಿ (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        ಪ್ರತ್ಯಾಗಮ 1;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ ff_vk_set_perm(ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ lut[4], ಪೂರ್ಣಾಙ್ಕ inv)
{
    ವಿಕಲ್ಪ (pix_fmt) {
    ಪಕ್ಷ AV_PIX_FMT_GBRP:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP10:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP12:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP14:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP16:
    ಪಕ್ಷ AV_PIX_FMT_GBRAPF16:
    ಪಕ್ಷ AV_PIX_FMT_GBRP10:
    ಪಕ್ಷ AV_PIX_FMT_GBRP12:
    ಪಕ್ಷ AV_PIX_FMT_GBRP14:
    ಪಕ್ಷ AV_PIX_FMT_GBRP16:
    ಪಕ್ಷ AV_PIX_FMT_GBRPF16:
    ಪಕ್ಷ AV_PIX_FMT_GBRPF32:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP32:
    ಪಕ್ಷ AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_BGRA:
    ಪಕ್ಷ AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        ಭಙ್ಗ;
    }

    ಯದಿ (inv) {
        ಪೂರ್ಣಾಙ್ಕ lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    ಪ್ರತ್ಯಾಗಮ;
}

ಧ್ರುವ ವರ್ಣ *ff_vk_shader_rep_fmt(ಗಣನಾ AVPixelFormat pix_fmt,
                                 ಗಣನಾ FFVkShaderRepFormat rep_fmt)
{
    ವಿಕಲ್ಪ (pix_fmt) {
    ಪಕ್ಷ AV_PIX_FMT_RGBA:
    ಪಕ್ಷ AV_PIX_FMT_BGRA:
    ಪಕ್ಷ AV_PIX_FMT_RGB24:
    ಪಕ್ಷ AV_PIX_FMT_BGR24:
    ಪಕ್ಷ AV_PIX_FMT_BGR0:
    ಪಕ್ಷ AV_PIX_FMT_RGB0:
    ಪಕ್ಷ AV_PIX_FMT_RGB565:
    ಪಕ್ಷ AV_PIX_FMT_BGR565:
    ಪಕ್ಷ AV_PIX_FMT_UYVA:
    ಪಕ್ಷ AV_PIX_FMT_YUYV422:
    ಪಕ್ಷ AV_PIX_FMT_UYVY422: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_X2RGB10:
    ಪಕ್ಷ AV_PIX_FMT_X2BGR10:
    ಪಕ್ಷ AV_PIX_FMT_Y210:
    ಪಕ್ಷ AV_PIX_FMT_XV30: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ರಿಕ್ತ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_RGB48:
    ಪಕ್ಷ AV_PIX_FMT_RGBA64:
    ಪಕ್ಷ AV_PIX_FMT_Y212:
    ಪಕ್ಷ AV_PIX_FMT_Y216:
    ಪಕ್ಷ AV_PIX_FMT_XV36:
    ಪಕ್ಷ AV_PIX_FMT_XV48: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_RGBAF16: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_RGBF32:
    ಪಕ್ಷ AV_PIX_FMT_RGBAF32: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_RGB96:
    ಪಕ್ಷ AV_PIX_FMT_RGBA128: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ರಿಕ್ತ,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    }
    ಪಕ್ಷ AV_PIX_FMT_GBRP:
    ಪಕ್ಷ AV_PIX_FMT_GRAY8:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP:
    ಪಕ್ಷ AV_PIX_FMT_YUV420P:
    ಪಕ್ಷ AV_PIX_FMT_YUV422P:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P:
    ಪಕ್ಷ AV_PIX_FMT_YUVA420P:
    ಪಕ್ಷ AV_PIX_FMT_YUVA422P:
    ಪಕ್ಷ AV_PIX_FMT_YUVA444P: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_GRAY10:
    ಪಕ್ಷ AV_PIX_FMT_GRAY12:
    ಪಕ್ಷ AV_PIX_FMT_GRAY14:
    ಪಕ್ಷ AV_PIX_FMT_GRAY16:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP10:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP12:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP14:
    ಪಕ್ಷ AV_PIX_FMT_GBRAP16:
    ಪಕ್ಷ AV_PIX_FMT_GBRAPF16:
    ಪಕ್ಷ AV_PIX_FMT_GBRP10:
    ಪಕ್ಷ AV_PIX_FMT_GBRP12:
    ಪಕ್ಷ AV_PIX_FMT_GBRP14:
    ಪಕ್ಷ AV_PIX_FMT_GBRP16:
    ಪಕ್ಷ AV_PIX_FMT_GBRPF16:
    ಪಕ್ಷ AV_PIX_FMT_XYZP12:
    ಪಕ್ಷ AV_PIX_FMT_YUV420P10:
    ಪಕ್ಷ AV_PIX_FMT_YUV420P12:
    ಪಕ್ಷ AV_PIX_FMT_YUV420P16:
    ಪಕ್ಷ AV_PIX_FMT_YUV422P10:
    ಪಕ್ಷ AV_PIX_FMT_YUV422P12:
    ಪಕ್ಷ AV_PIX_FMT_YUV422P16:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P10:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P12:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P16:
    ಪಕ್ಷ AV_PIX_FMT_YUVA420P10:
    ಪಕ್ಷ AV_PIX_FMT_YUVA420P16:
    ಪಕ್ಷ AV_PIX_FMT_YUVA422P10:
    ಪಕ್ಷ AV_PIX_FMT_YUVA422P12:
    ಪಕ್ಷ AV_PIX_FMT_YUVA422P16:
    ಪಕ್ಷ AV_PIX_FMT_YUVA444P10:
    ಪಕ್ಷ AV_PIX_FMT_YUVA444P12:
    ಪಕ್ಷ AV_PIX_FMT_YUVA444P16:
    ಪಕ್ಷ AV_PIX_FMT_BAYER_RGGB16: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_GRAY32:
    ಪಕ್ಷ AV_PIX_FMT_GRAYF32:
    ಪಕ್ಷ AV_PIX_FMT_GBRPF32:
    ಪಕ್ಷ AV_PIX_FMT_GBRAPF32: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_GBRAP32: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ರಿಕ್ತ,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_NV12:
    ಪಕ್ಷ AV_PIX_FMT_NV16:
    ಪಕ್ಷ AV_PIX_FMT_NV24: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_P010:
    ಪಕ್ಷ AV_PIX_FMT_P210:
    ಪಕ್ಷ AV_PIX_FMT_P410: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ರಿಕ್ತ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಪಕ್ಷ AV_PIX_FMT_P012:
    ಪಕ್ಷ AV_PIX_FMT_P016:
    ಪಕ್ಷ AV_PIX_FMT_P212:
    ಪಕ್ಷ AV_PIX_FMT_P216:
    ಪಕ್ಷ AV_PIX_FMT_P412:
    ಪಕ್ಷ AV_PIX_FMT_P416: {
        ಧ್ರುವ ವರ್ಣ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        ಪ್ರತ್ಯಾಗಮ rep_tab[rep_fmt];
    };
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ "rgba32f";
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_imageviews(AVRefStructOpaque unused, ಶೂನ್ಯ *obj)
{
    FFVkImageViews *iv = obj;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < iv->nb_views; i++) {
        ಯದಿ (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, ಪರಿಮಾಣ(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ಪೂರ್ಣಾಙ್ಕ nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_ಅಂಕೆ_DATA_POINTERS);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    ಯದಿ (!iv)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    ಪ್ರತ್ಯಾಗಮ iv;
}

VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, ಗಣನಾ FFVkShaderRepFormat rep_fmt)
{
#define REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#define REPS_FMT_PACK(fmt, ಅಂಕೆ) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## ಅಂಕೆ,

    ಧ್ರುವ VkFormat fmts_map[][4] = {
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

    ಯದಿ (fmt == VK_FORMAT_UNDEFINED)
        ಪ್ರತ್ಯಾಗಮ VK_FORMAT_UNDEFINED;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        ಯದಿ (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            ಪ್ರತ್ಯಾಗಮ fmts_map[i][rep_fmt];
    }

    ಪ್ರತ್ಯಾಗಮ VK_FORMAT_UNDEFINED;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ಪೂರ್ಣಾಙ್ಕ plane, ಗಣನಾ FFVkShaderRepFormat rep_fmt)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    ಧ್ರುವ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_to_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_identity_map,
        .subresourceRange = {
            .aspectMask = ff_vk_aspect_flag(f, plane),
            .level_ಎಣಿಕೆ = 1,
            .layer_ಎಣಿಕೆ = 1,
        },
    };
    ಯದಿ (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspectMask;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ಅಂಕೆ_DATA_POINTERS],
                                AVFrame *f,
                                ಧ್ರುವ VkFormat fmts[AV_ಅಂಕೆ_DATA_POINTERS])
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_identity_map,
            .subresourceRange = {
                .aspectMask = ff_vk_aspect_flag(f, i),
                .level_ಎಣಿಕೆ = 1,
                .layer_ಎಣಿಕೆ = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_planes; i++)
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    memcpy(views, tmp_views, nb_planes*ಪರಿಮಾಣ(*views));

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_planes; i++)
        ಯದಿ (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ಅಂಕೆ_DATA_POINTERS],
                            AVFrame *f, ಗಣನಾ FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ಧ್ರುವ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    VkFormat fmts[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_to_rep(rep_fmts[i], rep_fmt);
        ಯದಿ (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಪ್ರತ್ಯಾಗಮ ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

ಶೂನ್ಯ ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, ಪೂರ್ಣಾಙ್ಕ *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    ಪೂರ್ಣಾಙ್ಕ found = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->data[0];
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->nb_frame_deps; i++)
        ಯದಿ (e->frame_deps[i]->data[0] == pic->data[0]) {
            ಯದಿ (e->frame_update[i])
                found = i;
            ಭಙ್ಗ;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (VkImageMemoryBarrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .pNext = ರಿಕ್ತ,
            .srcStageMask = src_stage,
            .dstStageMask = dst_stage,
            .srcAccessMask = found >= 0 ? e->access_dst[found] : VK_ACCESS_2_NONE,
            .dstAccessMask = new_access,
            .oldLayout = found >= 0 ? e->layout_dst[found] : vkf->layout[0],
            .newLayout = new_layout,
            .srcQueueFamilyIndex = found >= 0 ? e->queue_family_dst[found] : vkf->queue_family[0],
            .dstQueueFamilyIndex = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .layer_ಎಣಿಕೆ = 1,
                .level_ಎಣಿಕೆ = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], ರಿಕ್ತ);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    memcpy(shd->lg_size, wg_size, 3*ಪರಿಮಾಣ(uint32_t));

    shd->subgroup_info = (VkPipelineShaderStageRequiredSubgroupSizeCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO,
        .requiredSubgroupSize = required_subgroup_size,
    };

    ವಿಕಲ್ಪ (shd->stage) {
    ಪಕ್ಷ VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
    ಪಕ್ಷ VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    ಪಕ್ಷ VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
    ಪಕ್ಷ VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    ಪಕ್ಷ VK_SHADER_STAGE_MISS_BIT_KHR:
    ಪಕ್ಷ VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        ಭಙ್ಗ;
    ಪಕ್ಷ VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        ಭಙ್ಗ;
    };

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pSetLayouts            = shd->desc_layout,
        .set_Layout_ಎಣಿಕೆ         = shd->nb_descriptor_sets,
        .ತಳ್ಳು_Constant_Range_ಎಣಿಕೆ = shd->ತಳ್ಳು_consts_ಅಂಕೆ,
        .p_ತಳ್ಳು_Constant_Ranges    = shd->ತಳ್ಳು_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ಧ್ರುವ uint8_t *spirv, size_t spirv_len)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext    = ರಿಕ್ತ,
        .flags    = 0x0,
        .pCode    = (ಶೂನ್ಯ *)spirv,
        .codeSize = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ಧ್ರುವ ವರ್ಣ *entrypoint)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = shd->subgroup_info.requiredSubgroupSize ?
                     &shd->subgroup_info : ರಿಕ್ತ,
            .pName = entrypoint,
            .flags = shd->subgroup_info.requiredSubgroupSize ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ಪೂರ್ಣಾಙ್ಕ has_singular = 0;
    ಪೂರ್ಣಾಙ್ಕ max_descriptors = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_set[i].nb_bindings);
        ಯದಿ (shd->desc_set[i].singular)
            has_singular = 1;
    }
    shd->use_ತಳ್ಳು = (s->extensions & FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR) &&
                    (max_descriptors <= s->ತಳ್ಳು_desc_props.max_ತಳ್ಳು_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkanDescriptorSet *set = &shd->desc_set[i];
        VkDescriptorSetLayoutCreateInfo desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .binding_ಎಣಿಕೆ = set->nb_bindings,
            .pBindings = set->binding,
            .flags = (shd->use_ತಳ್ಳು) ?
                     VK_DESCRIPTOR_SET_LAYOUT_CREATE_ತಳ್ಳು_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->CreateDescriptorSetLayout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ಧ್ರುವ ವರ್ಣ *spirv, size_t spirv_len,
                      ಧ್ರುವ ವರ್ಣ *entrypoint)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    FFVulkanFunctions *vk = &s->vkfn;
    VkSpecializationMapEntry spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ಒಳಹರಿವು_size = spirv_len;

    ಯದಿ (shd->precompiled) {
        ಯದಿ (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_Entry_ಎಣಿಕೆ = 0,
                .pData = shd->lg_size,
                .dataSize = 0,
            };
            shd->specialization_info = &spec_info;
        }

        VkSpecializationMapEntry *spe = (ಶೂನ್ಯ *)shd->specialization_info->pMapEntries;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_Entry_ಎಣಿಕೆ++] = (VkSpecializationMapEntry) {
                .constantID = 253 + i,
                .offset = shd->specialization_info->dataSize + i*ಪರಿಮಾಣ(uint32_t),
                .size = ಪರಿಮಾಣ(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->pData;
        memcpy(&spd[shd->specialization_info->dataSize],
               shd->lg_size, 3*ಪರಿಮಾಣ(uint32_t));
        shd->specialization_info->dataSize += 3*ಪರಿಮಾಣ(uint32_t);

#ಯದಿ CONFIG_SHADER_COMPRESSION
        uint8_t *out;
        size_t out_len;
        ಪೂರ್ಣಾಙ್ಕ ret = ff_zlib_expand(s, &out, &out_len, spirv, spirv_len);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        spirv = out;
        spirv_len = out_len;
#endif
    }

    err = init_descriptors(s, shd);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    err = init_pipeline_layout(s, shd);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    ವಿಕಲ್ಪ (shd->bind_point) {
    ಪಕ್ಷ VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        ಗಚ್ಛ end;
        ಭಙ್ಗ;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    ಯದಿ (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    ಅನ್ಯಥಾ
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    ಯದಿ (ಒಳಹರಿವು_size != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ಒಳಹರಿವು_size);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

end:
    ಯದಿ (shd->precompiled) {
        shd->specialization_info->map_Entry_ಎಣಿಕೆ -= 3;
        shd->specialization_info->dataSize -= 3*ಪರಿಮಾಣ(uint32_t);
    }
#ಯದಿ CONFIG_SHADER_COMPRESSION
    ಯದಿ (shd->precompiled)
        av_free((ಶೂನ್ಯ *)spirv);
#endif
    ಪ್ರತ್ಯಾಗಮ err;
}

ಶೂನ್ಯ ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ಧ್ರುವ FFVulkanDescriptorSetBinding *desc, ಪೂರ್ಣಾಙ್ಕ nb,
                                     ಪೂರ್ಣಾಙ್ಕ singular)
{
    FFVulkanDescriptorSet *set = &shd->desc_set[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb; i++) {
        set->binding[i].binding            = i;
        set->binding[i].descriptorType     = desc[i].type;
        set->binding[i].descriptor_ಎಣಿಕೆ    = FFMAX(desc[i].elems, 1);
        set->binding[i].stageFlags         = desc[i].stages;
        set->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb; i++) {
        ಪೂರ್ಣಾಙ್ಕ j;
        ಪ್ರತಿ (j = 0; j < shd->nb_desc_pool_size; j++)
            ಯದಿ (shd->desc_pool_size[j].type == desc[i].type)
                ಭಙ್ಗ;
        ಯದಿ (j >= shd->nb_desc_pool_size) {
            shd->nb_desc_pool_size++;
            av_assert1(shd->nb_desc_pool_size < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_size[j].type             = desc[i].type;
        shd->desc_pool_size[j].descriptor_ಎಣಿಕೆ += FFMAX(desc[i].elems, 1);
    }

    set->singular = singular;
    set->nb_bindings = nb;
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    ಯದಿ (!shd->nb_descriptor_sets)
        ಪ್ರತ್ಯಾಗಮ 0;

    FFVulkanShaderData *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    ಯದಿ (!shd->use_ತಳ್ಳು) {
        VkResult ret;
        FFVulkanFunctions *vk = &s->vkfn;
        VkDescriptorSetLayout *tmp_layouts;
        VkDescriptorSetAllocateInfo set_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < shd->nb_desc_pool_size; i++)
            shd->desc_pool_size[i].descriptor_ಎಣಿಕೆ *= pool->pool_size;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_size,
            .pool_Size_ಎಣಿಕೆ = shd->nb_desc_pool_size,
            .maxSets = sd->nb_descriptor_sets*pool->pool_size,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, ಪರಿಮಾಣ(*tmp_layouts));
        ಯದಿ (!tmp_layouts)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < pool->pool_size; i++)
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        set_alloc_info = (VkDescriptorSetAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .pSetLayouts        = tmp_layouts,
            .descriptor_Set_ಎಣಿಕೆ = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        ಪರಿಮಾಣ(*tmp_layouts));
        ಯದಿ (!sd->desc_sets) {
            av_free(tmp_layouts);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &set_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಧ್ರುವ FFVulkanShaderData *get_shd_data(FFVkExecContext *e,
                                                     ಧ್ರುವ FFVulkanShader *shd)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->parent->nb_reg_shd; i++)
        ಯದಿ (e->parent->reg_shd[i].shd == shd)
            ಪ್ರತ್ಯಾಗಮ &e->parent->reg_shd[i];
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ update_set_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, ಪೂರ್ಣಾಙ್ಕ set,
                                         VkWriteDescriptorSet *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];
    ಧ್ರುವ FFVulkanShaderData *sd = get_shd_data(e, shd);

    ಯದಿ (desc_set->singular) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < e->parent->pool_size; i++) {
            write_info->dstSet = sd->desc_sets[i*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ರಿಕ್ತ);
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (shd->use_ತಳ್ಳು) {
            vk->Cmd_ತಳ್ಳು_Descriptor_Set_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        set, 1,
                                        write_info);
        } ಅನ್ಯಥಾ {
            write_info->dstSet = sd->desc_sets[e->idx*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ರಿಕ್ತ);
        }
    }
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ bind, ಪೂರ್ಣಾಙ್ಕ offs,
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
        .descriptor_ಎಣಿಕೆ = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, set, binding, i,
                                views[i], layout, sampler);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ bind, ಪೂರ್ಣಾಙ್ಕ elem,
                                    FFVkBuffer *buf, VkDeviceSize offset, VkDeviceSize len,
                                    VkFormat fmt)
{
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];

    VkDescriptorBufferInfo desc_pool_write_info_buf = {
        .buffer = buf->buf,
        .offset = buf->virtual_offset + offset,
        .range = len,
    };
    VkWriteDescriptorSet desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstBinding = bind,
        .descriptor_ಎಣಿಕೆ = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pBufferInfo = &desc_pool_write_info_buf,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ ff_vk_shader_update_ತಳ್ಳು_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    ಪೂರ್ಣಾಙ್ಕ offset, size_t size, ಶೂನ್ಯ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ತಳ್ಳು_Constants(e->buf, shd->pipeline_layout,
                         stage, offset, size, src);
}

ಶೂನ್ಯ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ಧ್ರುವ FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ಧ್ರುವ FFVulkanShaderData *sd = get_shd_data(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    ಯದಿ (sd && sd->nb_descriptor_sets) {
        ಯದಿ (!shd->use_ತಳ್ಳು) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_point, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ರಿಕ್ತ);
        }
    }
}

ಶೂನ್ಯ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#ಯದಿ 0
    ಯದಿ (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#endif

    ಯದಿ (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    ಯದಿ (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < shd->nb_descriptor_sets; i++)
        ಯದಿ (shd->desc_layout[i])
            vk->DestroyDescriptorSetLayout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

ಶೂನ್ಯ ff_vk_uninit(FFVulkanContext *s)
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

    av_buffer_unref(&s->device_ref);
    av_buffer_unref(&s->frames_ref);
}

ಪೂರ್ಣಾಙ್ಕ ff_vk_init(FFVulkanContext *s, ಶೂನ್ಯ *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref)
{
    ಪೂರ್ಣಾಙ್ಕ err;

    ಸ್ಥಿರ ಧ್ರುವ AVClass vulkan_context_class = {
        .class_name       = "vk",
        .version          = LIBAVUTIL_VERSION_INT,
        .parent_log_context_offset = offsetof(FFVulkanContext, log_parent),
    };

    memset(s, 0, ಪರಿಮಾಣ(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    ಯದಿ (frames_ref) {
        s->frames_ref = av_buffer_ref(frames_ref);
        ಯದಿ (!s->frames_ref)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        s->frames = (AVHWFramesContext *)s->frames_ref->data;
        s->hwfc = s->frames->hwctx;

        device_ref = s->frames->device_ref;
    }

    s->device_ref = av_buffer_ref(device_ref);
    ಯದಿ (!s->device_ref) {
        ff_vk_uninit(s);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->data;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_to_mask(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_to_mask(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_load_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    ಯದಿ (err < 0) {
        ff_vk_uninit(s);
        ಪ್ರತ್ಯಾಗಮ err;
    }

    err = ff_vk_load_props(s);
    ಯದಿ (err < 0) {
        ff_vk_uninit(s);
        ಪ್ರತ್ಯಾಗಮ err;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
