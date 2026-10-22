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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "random_seed.h"
#ଅନ୍ତର୍ଭାଵ "refstruct.h"

#ଅନ୍ତର୍ଭାଵ "vulkan.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/vulkan_loader.h"

#ଯଦି CONFIG_SHADER_COMPRESSION
#ଅନ୍ତର୍ଭାଵ "libavutil/zlib_utils.h"
#endif

ଅଚଳ VkComponentMapping ff_comp_identity_map = {
    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
};

/* Converts return values to strings */
ଅଚଳ ଅକ୍ଷର *ff_vk_ret2str(VkResult res)
{
#define CASE(VAL) ସ୍ଥିତି VAL: ଫେରନ୍ତୁ #VAL
    ବାଛ (res) {
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
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଫେରନ୍ତୁ "Unknown error";
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
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ନିବେଶ_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        ଫେରନ୍ତୁ dst;                                                     \
    }

#define MAP_TO(flag1, flag2) ଯଦି (src & flag2) dst |= flag1;
FN_MAP_TO(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#undef MAP_TO
#define MAP_TO(flag1, flag2) ଯଦି (src & flag1) dst |= flag2;
FN_MAP_TO(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#undef MAP_TO
#undef FN_MAP_TO

ସ୍ଥିର ଶୂନ୍ୟ load_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା skip = 0;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < s->nb_qfs; j++) {
            ଯଦି (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (skip)
            ଜାରି;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ reset_imageviews(AVRefStructOpaque unused, ଶୂନ୍ୟ *obj);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_load_props(FFVulkanContext *s)
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

    FF_VK_STRUCT_EXT(s, &s->props, &s->ଠେଲ_desc_props, FF_VK_EXT_ଠେଲ_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ଠେଲ_DESCRIPTOR_PROPERTIES_KHR);
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

    ଯଦି (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(ଆକାର(FFVkImageViews), 0,
                                                         ଖାଲି, ଖାଲି, reset_imageviews,
                                                         ଖାଲି, ଖାଲି);
        ଯଦି (!s->imageviews_pool)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(ଆକାର(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_ଗଣନା = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_ଗଣନା = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    ଯଦି (s->host_image_props.copy_Src_Layout_ଗଣନା == 512 ||
        s->host_image_props.copy_Dst_Layout_ଗଣନା == 512) {
        VkImageLayout *new_array;
        size_t new_size;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ଖାଲି;
        s->host_image_props.copy_Src_Layout_ଗଣନା =
        s->host_image_props.copy_Dst_Layout_ଗଣନା = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_size = s->host_image_props.copy_Src_Layout_ଗଣନା +
                   s->host_image_props.copy_Dst_Layout_ଗଣନା;
        new_size *= ଆକାର(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_size);
        ଯଦି (!new_array)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_ଗଣନା;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->GetPhysicalDeviceMemoryProperties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->mprops.memory_Type_ଗଣନା; i++)
        s->host_cached_flag |= s->mprops.memoryTypes[i].propertyFlags &
                               VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

    load_enabled_qfs(s);

    ଯଦି (s->qf_props)
        ଫେରନ୍ତୁ 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ଖାଲି);

    s->qf_props = av_calloc(s->tot_nb_qfs, ଆକାର(*s->qf_props));
    ଯଦି (!s->qf_props)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, ଆକାର(*s->query_props));
    ଯଦି (!s->qf_props) {
        av_freep(&s->qf_props);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, ଆକାର(*s->video_props));
    ଯଦି (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

#ifdef VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, ଆକାର(*s->ownership_props));
    ଯଦି (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
#endif

    ପାଇଁ (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
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

    ଯଦି (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ଖାଲି);

        ଯଦି (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                ଆକାର(VkCooperativeMatrixPropertiesKHR));
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    ଫେରନ୍ତୁ 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->hwctx->nb_qf; i++) {
        ଯଦି ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            ଫେରନ୍ତୁ &s->hwctx->qf[i];
        }
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

ଶୂନ୍ୟ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        ଯଦି (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_ଗଣନା = 1,
                .pSemaphores = &e->sem,
                .p_ମୂଲ୍ୟଗୁଡ଼ିକ = &e->sem_ମୂଲ୍ୟ,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->lock);
    }

    /* Free shader-specific data */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkanShaderData *sd = &pool->reg_shd[i];

        ଯଦି (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++) {
        ଯଦି (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        ଯଦି (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    ଯଦି (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_data);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_size = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ସ୍ଥିର atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ଖାଲି)->qf)];
ସ୍ଥିର AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ସ୍ଥିର ଶୂନ୍ୟ exec_pool_phase_seed(ଶୂନ୍ୟ)
{
    uint32_t seed = av_get_random_seed();
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], seed, memory_order_relaxed);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_contexts,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_queries, VkQueryType query_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା query_64bit,
                         ଅଚଳ ଶୂନ୍ୟ *query_create_pnext)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    VkCommandBufferAllocateInfo cbuf_create;

    ଅଚଳ VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ଖାଲି;

    atomic_init(&pool->idx, 0);

    ଯଦି (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        ଯଦି (!ef)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*ଆକାର(*pool->cmd_buf_pools));
    ଯଦି (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*ଆକାର(*pool->cmd_bufs));
    ଯଦି (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (VkCommandBufferAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_Buffer_ଗଣନା = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }
    }

    /* Query pool */
    ଯଦି (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .pNext = query_create_pnext,
            .queryType = query_type,
            .query_ଗଣନା = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_status_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        ଯଦି (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_status_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } ଅନ୍ୟଥା ଯଦି (query_type == VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR) {
            pool->query_status_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_size = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_data = av_calloc(nb_contexts, pool->qd_size);
        ଯଦି (!pool->query_data) {
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, ଆକାର(*pool->contexts));
    ଯଦି (!pool->contexts) {
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    pool->pool_size = nb_contexts;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++)
        pthread_mutex_init(&pool->contexts[i].lock, ଖାଲି);

#ifdef VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା internal_queue_sync = 0;
    ଯଦି (s->extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC) {
        ଅଚଳ VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++) {
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
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_data = ((uint8_t *)pool->query_data) + pool->qd_size*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->ଅଙ୍କ : (i + phase) % qf->ଅଙ୍କ;
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

    ଫେରନ୍ତୁ 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    ଫେରନ୍ତୁ err;
}

VkResult ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ଶୂନ୍ୟ **data, VkQueryResultFlagBits flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ଅଚଳ FFVkExecPool *pool = e->parent;
    VkQueryResultFlags qf = flags & ~(VK_QUERY_RESULT_64_BIT |
                                      VK_QUERY_RESULT_WITH_STATUS_BIT_KHR);

    ଯଦି (!e->query_data) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        ଫେରନ୍ତୁ VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_RESULT_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_RESULT_WITH_STATUS_BIT_KHR : 0x0;

    ଯଦି (data)
        *data = e->query_data;

    ଫେରନ୍ତୁ vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_size, e->query_data,
                                   pool->qd_size, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        ଯଦି (pthread_mutex_trylock(&e->lock))
            ଜାରି; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        ଯଦି (vk->Get_Semaphore_Counter_ମୂଲ୍ୟ(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_ମୂଲ୍ୟ &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->lock);
    }

    ଫେରନ୍ତୁ &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_size];
}

ଶୂନ୍ୟ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ଗଣନା = 1,
        .pSemaphores = &e->sem,
        .p_ମୂଲ୍ୟଗୁଡ଼ିକ = &e->sem_ମୂଲ୍ୟ,
    };
    pthread_mutex_lock(&e->lock);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->lock);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ଅଚଳ FFVkExecPool *pool = e->parent;

    VkCommandBufferBeginInfo cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ଗଣନା = 1,
        .pSemaphores = &e->sem,
        .p_ମୂଲ୍ୟଗୁଡ଼ିକ = &e->sem_ମୂଲ୍ୟ,
    };

    pthread_mutex_lock(&e->lock);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->BeginCommandBuffer(e->buf, &cmd_start);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->lock);
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଯଦି (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_ମୂଲ୍ୟ++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .ମୂଲ୍ୟ = e->sem_ମୂଲ୍ୟ,
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->lock);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_buf_deps; j++)
        av_buffer_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        ବାଛ (od->type) {
        ସ୍ଥିତି VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        ଯଦି (e->frame_locked[j]) {
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

ଶୂନ୍ୟ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .ମୂଲ୍ୟ = e->sem_ମୂଲ୍ୟ,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->ResetCommandBuffer(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

ଶୂନ୍ୟ ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ଶୂନ୍ୟ *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

ଶୂନ୍ୟ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ଶୂନ୍ୟ *obj)
{
    ଶୂନ୍ୟ **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->nb_refstruct_deps; i++) {
        ଯଦି (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            ଫେରନ୍ତୁ;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ଖାଲି;
}

ଶୂନ୍ୟ ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    ଯଦି (!e->sw_frame_deps[e->nb_sw_frame_deps])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ମୂଲ୍ୟ = val,
        .stageMask = stage,
    };
}

ଶୂନ୍ୟ ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ମୂଲ୍ୟ = val,
        .stageMask = stage,
    };
}

ଶୂନ୍ୟ ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    ଯଦି (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stageMask = stage,
            };
        }

        ଫେରନ୍ତୁ;
    }

    /* Ownership of each semaphore passes to the execution */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb; i++) {
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_add_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);

    /* Don't add duplicates */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->nb_frame_deps; i++)
        ଯଦି (e->frame_deps[i]->data[0] == f->data[0])
            ଫେରନ୍ତୁ 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    ଯଦି (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_buffer_ref(f->buf[0]);
        ଯଦି (!e->buf_deps[e->nb_buf_deps])
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->lock_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ମୂଲ୍ୟ = vkf->sem_ମୂଲ୍ୟ[i],
            .stageMask = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ମୂଲ୍ୟ = vkf->sem_ମୂଲ୍ୟ[i] + 1,
            .stageMask = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_ମୂଲ୍ୟ[i];
        e->sem_sig_val_dst_cnt++;
    }

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < e->nb_frame_deps; i++)
        ଯଦି (e->frame_deps[i]->data[0] == f->data[0])
            ଭାଙ୍ଗ;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    ଯଦି (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dstQueueFamilyIndex;
    e->access_dst[i] = bar->dstAccessMask;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_mirror_sem_ମୂଲ୍ୟ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];

    /* Reject unknown frames */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < e->nb_frame_deps; i++)
        ଯଦି (e->frame_deps[i]->data[0] == f->data[0])
            ଭାଙ୍ଗ;
    ଯଦି (i == e->nb_frame_deps)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_ମୂଲ୍ୟ[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
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
        .command_Buffer_Info_ଗଣନା = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_ଗଣନା = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_ଗଣନା = e->sem_sig_cnt,
    };

    ret = vk->EndCommandBuffer(e->buf);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

#ଯଦି FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->lock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#ଯଦି FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < e->nb_frame_deps; j++) {
        ଯଦି (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->data[0];

            ଯଦି (e->frame_update[j]) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
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

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, ଶୂନ୍ୟ *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    VkResult ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    VkMemoryAllocateInfo alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext           = alloc_extension,
    };

    alloc_info.allocationSize = req->size;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->mprops.memory_Type_ଗଣନା; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        ଯଦି (!(req->memoryTypeBits & (1 << i)))
            ଜାରି;

        /* The memory type flags must include our properties */
        ଯଦି ((req_flags != UINT32_MAX) &&
            ((s->mprops.memoryTypes[i].propertyFlags & req_flags) != req_flags))
            ଜାରି;

        /* Found a suitable memory type */
        index = i;
        ଭାଙ୍ଗ;
    }

    ଯଦି (index < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    alloc_info.memoryTypeIndex = index;

    ret = vk->AllocateMemory(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    ଯଦି (ret != VK_SUCCESS)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (mem_flags)
        *mem_flags |= s->mprops.memoryTypes[index].propertyFlags;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, VkFormat format, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ଶୂନ୍ୟ *create_pnext)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
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
        .samples       = VK_SAMPLE_ଗଣନା_1_BIT,
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->GetImageMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.memoryRequirements,
                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    ଯଦି (err < 0)
        ଯାଅ fail;

    bind_info.image  = *img;
    bind_info.memory = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ 0;

fail:
    ff_vk_image_free(s, img, mem);
    ଫେରନ୍ତୁ err;
}

ଶୂନ୍ୟ ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ଯଦି (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    ଯଦି (*mem) {
        vk->FreeMemory(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, size_t size,
                     ଶୂନ୍ୟ *pNext, ଶୂନ୍ୟ *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VkResult ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_ded_mem;
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    req_desc.buffer = buf->buf;

    vk->GetBufferMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefersDedicatedAllocation |
                  ded_req.requiresDedicatedAllocation;
    ଯଦି (use_ded_mem) {
        ded_alloc.buffer = buf->buf;
        ded_alloc.pNext = alloc_pNext;
        alloc_pNext = &ded_alloc;
    }

    ଯଦି (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags.pNext = alloc_pNext;
        alloc_pNext = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.memoryRequirements, flags, alloc_pNext,
                          &buf->flags, &buf->mem);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    ret = vk->BindBufferMemory(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଯଦି (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        VkBufferDeviceAddressInfo address_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
            .buffer = buf->buf,
        };
        buf->address = vk->GetBufferDeviceAddress(s->hwctx->act_dev, &address_info);
    }

    buf->size = size;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_buffers, ପୂର୍ଣ୍ଣସଂଖ୍ୟା invalidate)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange inval_list[64];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା inval_ଗଣନା = 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_buffers; i++) {
        ଶୂନ୍ୟ *dst;
        ret = vk->MapMemory(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_WHOLE_SIZE, 0, &dst);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        ଯଦି (mem)
            mem[i] = dst;
    }

    ଯଦି (!invalidate)
        ଫେରନ୍ତୁ 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_buffers; i++) {
        ଅଚଳ VkMappedMemoryRange ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            .memory = buf[i]->mem,
            .size   = VK_WHOLE_SIZE,
        };
        ଯଦି (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            ଜାରି;
        inval_list[inval_ଗଣନା++] = ival_buf;
    }

    ଯଦି (inval_ଗଣନା) {
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, inval_ଗଣନା,
                                               inval_list);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା flush)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ଯଦି (buf->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        ଫେରନ୍ତୁ 0;

    ଅଚଳ VkMappedMemoryRange flush_data = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = buf->mem,
        .offset = offset,
        .size   = mem_size,
    };

    ଯଦି (flush)
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);
    ଅନ୍ୟଥା
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);

    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_buffers,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା flush)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange flush_list[64];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flush_ଗଣନା = 0;

    ଯଦି (flush) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_buffers; i++) {
            ଅଚଳ VkMappedMemoryRange flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .memory = buf[i]->mem,
                .size   = VK_WHOLE_SIZE,
            };

            av_assert0(!buf[i]->host_ref);
            ଯଦି (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                ଜାରି;
            flush_list[flush_ଗଣନା++] = flush_buf;
        }
    }

    ଯଦି (flush_ଗଣନା) {
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, flush_ଗଣନା,
                                          flush_list);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_buffers; i++) {
        vk->UnmapMemory(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ଖାଲି;
    }

    ଫେରନ୍ତୁ err;
}

ଶୂନ୍ୟ ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ଯଦି (!buf || !s->hwctx)
        ଫେରନ୍ତୁ;

    ଯଦି (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_buffer(s, buf, 0);
    ଯଦି (buf->buf != VK_NULL_HANDLE)
        vk->DestroyBuffer(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    ଯଦି (buf->mem != VK_NULL_HANDLE)
        vk->FreeMemory(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    ଯଦି (buf->host_ref)
        av_buffer_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ pooled_buf_free(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            ଶୂନ୍ୟ *create_pNext, size_t size,
                            VkMemoryPropertyFlagBits mem_props)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    FFVkBuffer *data;

    ଯଦି (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(ଆକାର(FFVkBuffer), 0, ctx,
                                                ଖାଲି, ଖାଲି, pooled_buf_free,
                                                ଖାଲି);
        ଯଦି (!(*buf_pool))
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    *buf = data = av_refstruct_pool_get(*buf_pool);
    ଯଦି (!data)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (data->size >= size)
        ଫେରନ୍ତୁ 0;

    ff_vk_free_buf(ctx, data);
    memset(data, 0, ଆକାର(*data));

    err = ff_vk_create_buf(ctx, data, size,
                           create_pNext, ଖାଲି, usage,
                           mem_props);
    ଯଦି (err < 0) {
        av_refstruct_unref(buf);
        ଫେରନ୍ତୁ err;
    }

    ଯଦି (mem_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_buffer(ctx, data, &data->mapped_mem, 0);
        ଯଦି (err < 0) {
            av_refstruct_unref(buf);
            ଫେରନ୍ତୁ err;
        }
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା create_mapped_buffer(FFVulkanContext *s,
                                FFVkBuffer *vkb, VkBufferUsageFlags usage,
                                size_t size,
                                VkExternalMemoryBufferCreateInfo *create_desc,
                                VkImportMemoryHostPointerInfoEXT *import_desc,
                                VkMemoryHostPointerPropertiesEXT props)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
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
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    ret = vk->CreateBuffer(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    ଯଦି (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ret = vk->BindBufferMemory(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    ଯଦି (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->DestroyBuffer(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ host_map_free(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          ଅଚଳ AVBufferRef *src_buf,
                          VkBufferUsageFlags usage)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
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
        .pNext = usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT ? &alloc_flags : ଖାଲି,
    };
    VkMemoryHostPointerPropertiesEXT props;

    AVBufferRef *ref;
    FFVkBuffer *vkb;
    size_t offs;
    size_t buffer_size;

    *dst = ଖାଲି;

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
    ଯଦି (!(ret == VK_SUCCESS && props.memoryTypeBits))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_buffer_ref(src_buf);
    ଯଦି (!ref)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ଅଚଳ VkDeviceSize src_avail = src_buf->size - (src_data - src_buf->data);
    buffer_size = offs + FFMIN(size, src_avail);
    buffer_size = FFALIGN(buffer_size, s->props.properties.limits.minMemoryMapAlignment);
    buffer_size = FFALIGN(buffer_size, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(ଆକାର(*vkb), 0, s, host_map_free);
    ଯଦି (!vkb) {
        av_buffer_unref(&ref);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    err = create_mapped_buffer(s, vkb, usage,
                               buffer_size, &create_desc, &import_desc,
                               props);
    ଯଦି (err < 0) {
        av_buffer_unref(&ref);
        av_refstruct_unref(&vkb);
        ଫେରନ୍ତୁ err;
    }

    ଯଦି (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
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

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_add_ଠେଲ_const(FFVulkanShader *shd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size,
                                VkShaderStageFlagBits stage)
{
    Vk_ଠେଲ_Constant_Range *pc = &shd->ଠେଲ_consts[shd->ଠେଲ_consts_ଅଙ୍କ++];
    av_assert1(shd->ଠେଲ_consts_ଅଙ୍କ < FF_VK_MAX_ଠେଲ_CONSTS);
    pc->stageFlags = stage;
    pc->offset = offset;
    pc->size = size;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା unnorm_coords, VkFilter filt)
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);

    ସ୍ଥିର ଅଚଳ VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    ଯଦି (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        ଫେରନ୍ତୁ VK_IMAGE_ASPECT_COLOR_BIT;

    ଫେରନ୍ତୁ plane_aspect[p];
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_mt_is_np_rgb(ଗଣନା AVPixelFormat pix_fmt)
{
    ଯଦି (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        ଫେରନ୍ତୁ 1;
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ ff_vk_set_perm(ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା lut[4], ପୂର୍ଣ୍ଣସଂଖ୍ୟା inv)
{
    ବାଛ (pix_fmt) {
    ସ୍ଥିତି AV_PIX_FMT_GBRP:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP10:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP12:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP14:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP16:
    ସ୍ଥିତି AV_PIX_FMT_GBRAPF16:
    ସ୍ଥିତି AV_PIX_FMT_GBRP10:
    ସ୍ଥିତି AV_PIX_FMT_GBRP12:
    ସ୍ଥିତି AV_PIX_FMT_GBRP14:
    ସ୍ଥିତି AV_PIX_FMT_GBRP16:
    ସ୍ଥିତି AV_PIX_FMT_GBRPF16:
    ସ୍ଥିତି AV_PIX_FMT_GBRPF32:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP32:
    ସ୍ଥିତି AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_BGRA:
    ସ୍ଥିତି AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        ଭାଙ୍ଗ;
    }

    ଯଦି (inv) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    ଫେରନ୍ତୁ;
}

ଅଚଳ ଅକ୍ଷର *ff_vk_shader_rep_fmt(ଗଣନା AVPixelFormat pix_fmt,
                                 ଗଣନା FFVkShaderRepFormat rep_fmt)
{
    ବାଛ (pix_fmt) {
    ସ୍ଥିତି AV_PIX_FMT_RGBA:
    ସ୍ଥିତି AV_PIX_FMT_BGRA:
    ସ୍ଥିତି AV_PIX_FMT_RGB24:
    ସ୍ଥିତି AV_PIX_FMT_BGR24:
    ସ୍ଥିତି AV_PIX_FMT_BGR0:
    ସ୍ଥିତି AV_PIX_FMT_RGB0:
    ସ୍ଥିତି AV_PIX_FMT_RGB565:
    ସ୍ଥିତି AV_PIX_FMT_BGR565:
    ସ୍ଥିତି AV_PIX_FMT_UYVA:
    ସ୍ଥିତି AV_PIX_FMT_YUYV422:
    ସ୍ଥିତି AV_PIX_FMT_UYVY422: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_X2RGB10:
    ସ୍ଥିତି AV_PIX_FMT_X2BGR10:
    ସ୍ଥିତି AV_PIX_FMT_Y210:
    ସ୍ଥିତି AV_PIX_FMT_XV30: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ଖାଲି,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_RGB48:
    ସ୍ଥିତି AV_PIX_FMT_RGBA64:
    ସ୍ଥିତି AV_PIX_FMT_Y212:
    ସ୍ଥିତି AV_PIX_FMT_Y216:
    ସ୍ଥିତି AV_PIX_FMT_XV36:
    ସ୍ଥିତି AV_PIX_FMT_XV48: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_RGBAF16: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_RGBF32:
    ସ୍ଥିତି AV_PIX_FMT_RGBAF32: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_RGB96:
    ସ୍ଥିତି AV_PIX_FMT_RGBA128: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ଖାଲି,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    }
    ସ୍ଥିତି AV_PIX_FMT_GBRP:
    ସ୍ଥିତି AV_PIX_FMT_GRAY8:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP:
    ସ୍ଥିତି AV_PIX_FMT_YUV420P:
    ସ୍ଥିତି AV_PIX_FMT_YUV422P:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P:
    ସ୍ଥିତି AV_PIX_FMT_YUVA420P:
    ସ୍ଥିତି AV_PIX_FMT_YUVA422P:
    ସ୍ଥିତି AV_PIX_FMT_YUVA444P: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_GRAY10:
    ସ୍ଥିତି AV_PIX_FMT_GRAY12:
    ସ୍ଥିତି AV_PIX_FMT_GRAY14:
    ସ୍ଥିତି AV_PIX_FMT_GRAY16:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP10:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP12:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP14:
    ସ୍ଥିତି AV_PIX_FMT_GBRAP16:
    ସ୍ଥିତି AV_PIX_FMT_GBRAPF16:
    ସ୍ଥିତି AV_PIX_FMT_GBRP10:
    ସ୍ଥିତି AV_PIX_FMT_GBRP12:
    ସ୍ଥିତି AV_PIX_FMT_GBRP14:
    ସ୍ଥିତି AV_PIX_FMT_GBRP16:
    ସ୍ଥିତି AV_PIX_FMT_GBRPF16:
    ସ୍ଥିତି AV_PIX_FMT_XYZP12:
    ସ୍ଥିତି AV_PIX_FMT_YUV420P10:
    ସ୍ଥିତି AV_PIX_FMT_YUV420P12:
    ସ୍ଥିତି AV_PIX_FMT_YUV420P16:
    ସ୍ଥିତି AV_PIX_FMT_YUV422P10:
    ସ୍ଥିତି AV_PIX_FMT_YUV422P12:
    ସ୍ଥିତି AV_PIX_FMT_YUV422P16:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P10:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P12:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P16:
    ସ୍ଥିତି AV_PIX_FMT_YUVA420P10:
    ସ୍ଥିତି AV_PIX_FMT_YUVA420P16:
    ସ୍ଥିତି AV_PIX_FMT_YUVA422P10:
    ସ୍ଥିତି AV_PIX_FMT_YUVA422P12:
    ସ୍ଥିତି AV_PIX_FMT_YUVA422P16:
    ସ୍ଥିତି AV_PIX_FMT_YUVA444P10:
    ସ୍ଥିତି AV_PIX_FMT_YUVA444P12:
    ସ୍ଥିତି AV_PIX_FMT_YUVA444P16:
    ସ୍ଥିତି AV_PIX_FMT_BAYER_RGGB16: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_GRAY32:
    ସ୍ଥିତି AV_PIX_FMT_GRAYF32:
    ସ୍ଥିତି AV_PIX_FMT_GBRPF32:
    ସ୍ଥିତି AV_PIX_FMT_GBRAPF32: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_GBRAP32: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ଖାଲି,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_NV12:
    ସ୍ଥିତି AV_PIX_FMT_NV16:
    ସ୍ଥିତି AV_PIX_FMT_NV24: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_P010:
    ସ୍ଥିତି AV_PIX_FMT_P210:
    ସ୍ଥିତି AV_PIX_FMT_P410: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ଖାଲି,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ସ୍ଥିତି AV_PIX_FMT_P012:
    ସ୍ଥିତି AV_PIX_FMT_P016:
    ସ୍ଥିତି AV_PIX_FMT_P212:
    ସ୍ଥିତି AV_PIX_FMT_P216:
    ସ୍ଥିତି AV_PIX_FMT_P412:
    ସ୍ଥିତି AV_PIX_FMT_P416: {
        ଅଚଳ ଅକ୍ଷର *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        ଫେରନ୍ତୁ rep_tab[rep_fmt];
    };
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ "rgba32f";
    }
}

ସ୍ଥିର ଶୂନ୍ୟ reset_imageviews(AVRefStructOpaque unused, ଶୂନ୍ୟ *obj)
{
    FFVkImageViews *iv = obj;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < iv->nb_views; i++) {
        ଯଦି (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, ଆକାର(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_ଅଙ୍କ_DATA_POINTERS);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    ଯଦି (!iv)
        ଫେରନ୍ତୁ ଖାଲି;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    ଫେରନ୍ତୁ iv;
}

VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, ଗଣନା FFVkShaderRepFormat rep_fmt)
{
#define REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#define REPS_FMT_PACK(fmt, ଅଙ୍କ) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## ଅଙ୍କ, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## ଅଙ୍କ, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## ଅଙ୍କ, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## ଅଙ୍କ,

    ଅଚଳ VkFormat fmts_map[][4] = {
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

    ଯଦି (fmt == VK_FORMAT_UNDEFINED)
        ଫେରନ୍ତୁ VK_FORMAT_UNDEFINED;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        ଯଦି (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            ଫେରନ୍ତୁ fmts_map[i][rep_fmt];
    }

    ଫେରନ୍ତୁ VK_FORMAT_UNDEFINED;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane, ଗଣନା FFVkShaderRepFormat rep_fmt)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    ଅଚଳ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);

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
            .level_ଗଣନା = 1,
            .layer_ଗଣନା = 1,
        },
    };
    ଯଦି (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspectMask;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ଅଙ୍କ_DATA_POINTERS],
                                AVFrame *f,
                                ଅଚଳ VkFormat fmts[AV_ଅଙ୍କ_DATA_POINTERS])
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_planes; i++) {
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
                .level_ଗଣନା = 1,
                .layer_ଗଣନା = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_planes; i++)
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    memcpy(views, tmp_views, nb_planes*ଆକାର(*views));

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_planes; i++)
        ଯଦି (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    ଫେରନ୍ତୁ err;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ଅଙ୍କ_DATA_POINTERS],
                            AVFrame *f, ଗଣନା FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ଅଚଳ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    VkFormat fmts[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_to_rep(rep_fmts[i], rep_fmt);
        ଯଦି (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଫେରନ୍ତୁ ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

ଶୂନ୍ୟ ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା found = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->data[0];
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(vkf);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->nb_frame_deps; i++)
        ଯଦି (e->frame_deps[i]->data[0] == pic->data[0]) {
            ଯଦି (e->frame_update[i])
                found = i;
            ଭାଙ୍ଗ;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (VkImageMemoryBarrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .pNext = ଖାଲି,
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
                .layer_ଗଣନା = 1,
                .level_ଗଣନା = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], ଖାଲି);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    memcpy(shd->lg_size, wg_size, 3*ଆକାର(uint32_t));

    shd->subgroup_info = (VkPipelineShaderStageRequiredSubgroupSizeCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO,
        .requiredSubgroupSize = required_subgroup_size,
    };

    ବାଛ (shd->stage) {
    ସ୍ଥିତି VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
    ସ୍ଥିତି VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    ସ୍ଥିତି VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
    ସ୍ଥିତି VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    ସ୍ଥିତି VK_SHADER_STAGE_MISS_BIT_KHR:
    ସ୍ଥିତି VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        ଭାଙ୍ଗ;
    };

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pSetLayouts            = shd->desc_layout,
        .set_Layout_ଗଣନା         = shd->nb_descriptor_sets,
        .ଠେଲ_Constant_Range_ଗଣନା = shd->ଠେଲ_consts_ଅଙ୍କ,
        .p_ଠେଲ_Constant_Ranges    = shd->ଠେଲ_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ଅଚଳ uint8_t *spirv, size_t spirv_len)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext    = ଖାଲି,
        .flags    = 0x0,
        .pCode    = (ଶୂନ୍ୟ *)spirv,
        .codeSize = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ଅଚଳ ଅକ୍ଷର *entrypoint)
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
                     &shd->subgroup_info : ଖାଲି,
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_singular = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_descriptors = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_set[i].nb_bindings);
        ଯଦି (shd->desc_set[i].singular)
            has_singular = 1;
    }
    shd->use_ଠେଲ = (s->extensions & FF_VK_EXT_ଠେଲ_DESCRIPTOR) &&
                    (max_descriptors <= s->ଠେଲ_desc_props.max_ଠେଲ_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkanDescriptorSet *set = &shd->desc_set[i];
        VkDescriptorSetLayoutCreateInfo desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .binding_ଗଣନା = set->nb_bindings,
            .pBindings = set->binding,
            .flags = (shd->use_ଠେଲ) ?
                     VK_DESCRIPTOR_SET_LAYOUT_CREATE_ଠେଲ_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->CreateDescriptorSetLayout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ଅଚଳ ଅକ୍ଷର *spirv, size_t spirv_len,
                      ଅଚଳ ଅକ୍ଷର *entrypoint)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    FFVulkanFunctions *vk = &s->vkfn;
    VkSpecializationMapEntry spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ନିବେଶ_size = spirv_len;

    ଯଦି (shd->precompiled) {
        ଯଦି (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_Entry_ଗଣନା = 0,
                .pData = shd->lg_size,
                .dataSize = 0,
            };
            shd->specialization_info = &spec_info;
        }

        VkSpecializationMapEntry *spe = (ଶୂନ୍ୟ *)shd->specialization_info->pMapEntries;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_Entry_ଗଣନା++] = (VkSpecializationMapEntry) {
                .constantID = 253 + i,
                .offset = shd->specialization_info->dataSize + i*ଆକାର(uint32_t),
                .size = ଆକାର(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->pData;
        memcpy(&spd[shd->specialization_info->dataSize],
               shd->lg_size, 3*ଆକାର(uint32_t));
        shd->specialization_info->dataSize += 3*ଆକାର(uint32_t);

#ଯଦି CONFIG_SHADER_COMPRESSION
        uint8_t *out;
        size_t out_len;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = ff_zlib_expand(s, &out, &out_len, spirv, spirv_len);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
        spirv = out;
        spirv_len = out_len;
#endif
    }

    err = init_descriptors(s, shd);
    ଯଦି (err < 0)
        ଯାଅ end;

    err = init_pipeline_layout(s, shd);
    ଯଦି (err < 0)
        ଯାଅ end;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    ଯଦି (err < 0)
        ଯାଅ end;

    ବାଛ (shd->bind_point) {
    ସ୍ଥିତି VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        ଯାଅ end;
        ଭାଙ୍ଗ;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    ଯଦି (err < 0)
        ଯାଅ end;

    ଯଦି (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    ଅନ୍ୟଥା
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    ଯଦି (ନିବେଶ_size != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ନିବେଶ_size);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

end:
    ଯଦି (shd->precompiled) {
        shd->specialization_info->map_Entry_ଗଣନା -= 3;
        shd->specialization_info->dataSize -= 3*ଆକାର(uint32_t);
    }
#ଯଦି CONFIG_SHADER_COMPRESSION
    ଯଦି (shd->precompiled)
        av_free((ଶୂନ୍ୟ *)spirv);
#endif
    ଫେରନ୍ତୁ err;
}

ଶୂନ୍ୟ ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ଅଚଳ FFVulkanDescriptorSetBinding *desc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb,
                                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା singular)
{
    FFVulkanDescriptorSet *set = &shd->desc_set[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb; i++) {
        set->binding[i].binding            = i;
        set->binding[i].descriptorType     = desc[i].type;
        set->binding[i].descriptor_ଗଣନା    = FFMAX(desc[i].elems, 1);
        set->binding[i].stageFlags         = desc[i].stages;
        set->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା j;
        ପାଇଁ (j = 0; j < shd->nb_desc_pool_size; j++)
            ଯଦି (shd->desc_pool_size[j].type == desc[i].type)
                ଭାଙ୍ଗ;
        ଯଦି (j >= shd->nb_desc_pool_size) {
            shd->nb_desc_pool_size++;
            av_assert1(shd->nb_desc_pool_size < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_size[j].type             = desc[i].type;
        shd->desc_pool_size[j].descriptor_ଗଣନା += FFMAX(desc[i].elems, 1);
    }

    set->singular = singular;
    set->nb_bindings = nb;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    ଯଦି (!shd->nb_descriptor_sets)
        ଫେରନ୍ତୁ 0;

    FFVulkanShaderData *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    ଯଦି (!shd->use_ଠେଲ) {
        VkResult ret;
        FFVulkanFunctions *vk = &s->vkfn;
        VkDescriptorSetLayout *tmp_layouts;
        VkDescriptorSetAllocateInfo set_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < shd->nb_desc_pool_size; i++)
            shd->desc_pool_size[i].descriptor_ଗଣନା *= pool->pool_size;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_size,
            .pool_Size_ଗଣନା = shd->nb_desc_pool_size,
            .maxSets = sd->nb_descriptor_sets*pool->pool_size,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, ଆକାର(*tmp_layouts));
        ଯଦି (!tmp_layouts)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < pool->pool_size; i++)
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        set_alloc_info = (VkDescriptorSetAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .pSetLayouts        = tmp_layouts,
            .descriptor_Set_ଗଣନା = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        ଆକାର(*tmp_layouts));
        ଯଦି (!sd->desc_sets) {
            av_free(tmp_layouts);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &set_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅଚଳ FFVulkanShaderData *get_shd_data(FFVkExecContext *e,
                                                     ଅଚଳ FFVulkanShader *shd)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->parent->nb_reg_shd; i++)
        ଯଦି (e->parent->reg_shd[i].shd == shd)
            ଫେରନ୍ତୁ &e->parent->reg_shd[i];
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ update_set_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା set,
                                         VkWriteDescriptorSet *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];
    ଅଚଳ FFVulkanShaderData *sd = get_shd_data(e, shd);

    ଯଦି (desc_set->singular) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < e->parent->pool_size; i++) {
            write_info->dstSet = sd->desc_sets[i*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ଖାଲି);
        }
    } ଅନ୍ୟଥା {
        ଯଦି (shd->use_ଠେଲ) {
            vk->Cmd_ଠେଲ_Descriptor_Set_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        set, 1,
                                        write_info);
        } ଅନ୍ୟଥା {
            write_info->dstSet = sd->desc_sets[e->idx*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ଖାଲି);
        }
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା set, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bind, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offs,
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
        .descriptor_ଗଣନା = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ପୂର୍ଣ୍ଣସଂଖ୍ୟା set, ପୂର୍ଣ୍ଣସଂଖ୍ୟା binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, set, binding, i,
                                views[i], layout, sampler);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା set, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bind, ପୂର୍ଣ୍ଣସଂଖ୍ୟା elem,
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
        .descriptor_ଗଣନା = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pBufferInfo = &desc_pool_write_info_buf,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ ff_vk_shader_update_ଠେଲ_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset, size_t size, ଶୂନ୍ୟ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ଠେଲ_Constants(e->buf, shd->pipeline_layout,
                         stage, offset, size, src);
}

ଶୂନ୍ୟ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ଅଚଳ FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ଅଚଳ FFVulkanShaderData *sd = get_shd_data(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    ଯଦି (sd && sd->nb_descriptor_sets) {
        ଯଦି (!shd->use_ଠେଲ) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_point, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ଖାଲି);
        }
    }
}

ଶୂନ୍ୟ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#ଯଦି 0
    ଯଦି (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#endif

    ଯଦି (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    ଯଦି (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < shd->nb_descriptor_sets; i++)
        ଯଦି (shd->desc_layout[i])
            vk->DestroyDescriptorSetLayout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

ଶୂନ୍ୟ ff_vk_uninit(FFVulkanContext *s)
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

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_vk_init(FFVulkanContext *s, ଶୂନ୍ୟ *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ସ୍ଥିର ଅଚଳ AVClass vulkan_context_class = {
        .class_name       = "vk",
        .version          = LIBAVUTIL_VERSION_INT,
        .parent_log_context_offset = offsetof(FFVulkanContext, log_parent),
    };

    memset(s, 0, ଆକାର(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    ଯଦି (frames_ref) {
        s->frames_ref = av_buffer_ref(frames_ref);
        ଯଦି (!s->frames_ref)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        s->frames = (AVHWFramesContext *)s->frames_ref->data;
        s->hwfc = s->frames->hwctx;

        device_ref = s->frames->device_ref;
    }

    s->device_ref = av_buffer_ref(device_ref);
    ଯଦି (!s->device_ref) {
        ff_vk_uninit(s);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->data;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_to_mask(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_to_mask(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_load_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    ଯଦି (err < 0) {
        ff_vk_uninit(s);
        ଫେରନ୍ତୁ err;
    }

    err = ff_vk_load_props(s);
    ଯଦି (err < 0) {
        ff_vk_uninit(s);
        ଫେରନ୍ତୁ err;
    }

    ଫେରନ୍ତୁ 0;
}
