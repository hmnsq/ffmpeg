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

#अन्तर्भाव "config.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "random_seed.h"
#अन्तर्भाव "refstruct.h"

#अन्तर्भाव "vulkan.h"
#अन्तर्भाव "libavutil/vulkan_loader.h"

#यदि CONFIG_SHADER_COMPRESSION
#अन्तर्भाव "libavutil/zlib_utils.h"
#endif

अचर VkComponentMapping ff_comp_identity_map = {
    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
};

/* Converts return values to strings */
अचर वर्ण *ff_vk_ret2str(VkResult res)
{
#define CASE(VAL) पक्ष VAL: फर्काऊ #VAL
    विकल्प (res) {
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
    स्वभाव: फर्काऊ "Unknown error";
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
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_आगत_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        फर्काऊ dst;                                                     \
    }

#define MAP_TO(flag1, flag2) यदि (src & flag2) dst |= flag1;
FN_MAP_TO(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#undef MAP_TO
#define MAP_TO(flag1, flag2) यदि (src & flag1) dst |= flag2;
FN_MAP_TO(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#undef MAP_TO
#undef FN_MAP_TO

स्थिर शून्य load_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    लागि (पूर्णाङ्क i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        पूर्णाङ्क skip = 0;
        लागि (पूर्णाङ्क j = 0; j < s->nb_qfs; j++) {
            यदि (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                रोक;
            }
        }
        यदि (skip)
            जारी;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

स्थिर शून्य reset_imageviews(AVRefStructOpaque unused, शून्य *obj);

पूर्णाङ्क ff_vk_load_props(FFVulkanContext *s)
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

    FF_VK_STRUCT_EXT(s, &s->props, &s->थप_desc_props, FF_VK_EXT_थप_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_थप_DESCRIPTOR_PROPERTIES_KHR);
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

    यदि (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(परिमाण(FFVkImageViews), 0,
                                                         रिक्त, रिक्त, reset_imageviews,
                                                         रिक्त, रिक्त);
        यदि (!s->imageviews_pool)
            फर्काऊ AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(परिमाण(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_गन्ती = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_गन्ती = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    यदि (s->host_image_props.copy_Src_Layout_गन्ती == 512 ||
        s->host_image_props.copy_Dst_Layout_गन्ती == 512) {
        VkImageLayout *new_array;
        माप_प्रकार new_size;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = रिक्त;
        s->host_image_props.copy_Src_Layout_गन्ती =
        s->host_image_props.copy_Dst_Layout_गन्ती = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_size = s->host_image_props.copy_Src_Layout_गन्ती +
                   s->host_image_props.copy_Dst_Layout_गन्ती;
        new_size *= परिमाण(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_size);
        यदि (!new_array)
            फर्काऊ AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_गन्ती;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->GetPhysicalDeviceMemoryProperties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    लागि (पूर्णाङ्क i = 0; i < s->mprops.memory_Type_गन्ती; i++)
        s->host_cached_flag |= s->mprops.memoryTypes[i].propertyFlags &
                               VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

    load_enabled_qfs(s);

    यदि (s->qf_props)
        फर्काऊ 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, रिक्त);

    s->qf_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->qf_props));
    यदि (!s->qf_props)
        फर्काऊ AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->query_props));
    यदि (!s->qf_props) {
        av_freep(&s->qf_props);
        फर्काऊ AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->video_props));
    यदि (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        फर्काऊ AVERROR(ENOMEM);
    }

#ifdef VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->ownership_props));
    यदि (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        फर्काऊ AVERROR(ENOMEM);
    }
#endif

    लागि (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
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

    यदि (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, रिक्त);

        यदि (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                परिमाण(VkCooperativeMatrixPropertiesKHR));
            लागि (पूर्णाङ्क i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    फर्काऊ 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops)
{
    लागि (पूर्णाङ्क i = 0; i < s->hwctx->nb_qf; i++) {
        यदि ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            फर्काऊ &s->hwctx->qf[i];
        }
    }
    फर्काऊ रिक्त;
}

स्थिर शून्य exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

शून्य ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        यदि (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_गन्ती = 1,
                .pSemaphores = &e->sem,
                .p_मानहरू = &e->sem_मान,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->lock);
    }

    /* Free shader-specific data */
    लागि (पूर्णाङ्क i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkanShaderData *sd = &pool->reg_shd[i];

        यदि (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++) {
        यदि (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        यदि (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    यदि (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_data);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_size = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
स्थिर atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)रिक्त)->qf)];
स्थिर AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

स्थिर शून्य exec_pool_phase_seed(शून्य)
{
    uint32_t seed = av_get_random_seed();
    लागि (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], seed, memory_order_relaxed);
}

पूर्णाङ्क ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, पूर्णाङ्क nb_contexts,
                         पूर्णाङ्क nb_queries, VkQueryType query_type, पूर्णाङ्क query_64bit,
                         अचर शून्य *query_create_pnext)
{
    पूर्णाङ्क err;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    VkCommandBufferAllocateInfo cbuf_create;

    अचर VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = रिक्त;

    atomic_init(&pool->idx, 0);

    यदि (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        यदि (!ef)
            फर्काऊ AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*परिमाण(*pool->cmd_buf_pools));
    यदि (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*परिमाण(*pool->cmd_bufs));
    यदि (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    लागि (पूर्णाङ्क i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (VkCommandBufferAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_Buffer_गन्ती = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }
    }

    /* Query pool */
    यदि (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .pNext = query_create_pnext,
            .queryType = query_type,
            .query_गन्ती = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_status_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        यदि (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            पूर्णाङ्क nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_status_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } अन्यथा यदि (query_type == VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR) {
            pool->query_status_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_size = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_data = av_calloc(nb_contexts, pool->qd_size);
        यदि (!pool->query_data) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, परिमाण(*pool->contexts));
    यदि (!pool->contexts) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    pool->pool_size = nb_contexts;

    लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++)
        pthread_mutex_init(&pool->contexts[i].lock, रिक्त);

#ifdef VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    पूर्णाङ्क internal_queue_sync = 0;
    यदि (s->extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC) {
        अचर VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
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
    पूर्णाङ्क pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++) {
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
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            फर्काऊ AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_data = ((uint8_t *)pool->query_data) + pool->qd_size*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->अङ्क : (i + phase) % qf->अङ्क;
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

    फर्काऊ 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    फर्काऊ err;
}

VkResult ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              शून्य **data, VkQueryResultFlagBits flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    अचर FFVkExecPool *pool = e->parent;
    VkQueryResultFlags qf = flags & ~(VK_QUERY_RESULT_64_BIT |
                                      VK_QUERY_RESULT_WITH_STATUS_BIT_KHR);

    यदि (!e->query_data) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        फर्काऊ VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_RESULT_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_RESULT_WITH_STATUS_BIT_KHR : 0x0;

    यदि (data)
        *data = e->query_data;

    फर्काऊ vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_size, e->query_data,
                                   pool->qd_size, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        यदि (pthread_mutex_trylock(&e->lock))
            जारी; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        यदि (vk->Get_Semaphore_Counter_मान(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_मान &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->lock);
    }

    फर्काऊ &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_size];
}

शून्य ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गन्ती = 1,
        .pSemaphores = &e->sem,
        .p_मानहरू = &e->sem_मान,
    };
    pthread_mutex_lock(&e->lock);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->lock);
}

पूर्णाङ्क ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    अचर FFVkExecPool *pool = e->parent;

    VkCommandBufferBeginInfo cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गन्ती = 1,
        .pSemaphores = &e->sem,
        .p_मानहरू = &e->sem_मान,
    };

    pthread_mutex_lock(&e->lock);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->BeginCommandBuffer(e->buf, &cmd_start);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->lock);
        फर्काऊ AVERROR_EXTERNAL;
    }

    यदि (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_मान++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .मान = e->sem_मान,
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->lock);

    फर्काऊ 0;
}

स्थिर शून्य exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    लागि (पूर्णाङ्क j = 0; j < e->nb_buf_deps; j++)
        av_buffer_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    लागि (पूर्णाङ्क j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    लागि (पूर्णाङ्क j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        विकल्प (od->type) {
        पक्ष VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            रोक;
        पक्ष VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            रोक;
        स्वभाव:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    लागि (पूर्णाङ्क j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    लागि (पूर्णाङ्क j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        यदि (e->frame_locked[j]) {
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

शून्य ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .मान = e->sem_मान,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->ResetCommandBuffer(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

शून्य ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  शून्य *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

शून्य ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   शून्य *obj)
{
    शून्य **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    लागि (पूर्णाङ्क i = 0; i < e->nb_refstruct_deps; i++) {
        यदि (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            फर्काऊ;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = रिक्त;
}

शून्य ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

पूर्णाङ्क ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    यदि (!e->sw_frame_deps[e->nb_sw_frame_deps])
        फर्काऊ AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    फर्काऊ 0;
}

शून्य ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मान = val,
        .stageMask = stage,
    };
}

शून्य ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मान = val,
        .stageMask = stage,
    };
}

शून्य ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णाङ्क nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णाङ्क रुको)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    यदि (!रुको) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        लागि (पूर्णाङ्क i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stageMask = stage,
            };
        }

        फर्काऊ;
    }

    /* Ownership of each semaphore passes to the execution */
    लागि (पूर्णाङ्क i = 0; i < nb; i++) {
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_add_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

पूर्णाङ्क ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);

    /* Don't add duplicates */
    लागि (पूर्णाङ्क i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->data[0] == f->data[0])
            फर्काऊ 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    यदि (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_buffer_ref(f->buf[0]);
        यदि (!e->buf_deps[e->nb_buf_deps])
            फर्काऊ AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->lock_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    लागि (पूर्णाङ्क i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मान = vkf->sem_मान[i],
            .stageMask = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मान = vkf->sem_मान[i] + 1,
            .stageMask = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_मान[i];
        e->sem_sig_val_dst_cnt++;
    }

    फर्काऊ 0;
}

शून्य ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar)
{
    पूर्णाङ्क i;
    लागि (i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->data[0] == f->data[0])
            रोक;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    यदि (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dstQueueFamilyIndex;
    e->access_dst[i] = bar->dstAccessMask;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

पूर्णाङ्क ff_vk_exec_mirror_sem_मान(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];

    /* Reject unknown frames */
    पूर्णाङ्क i;
    लागि (i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->data[0] == f->data[0])
            रोक;
    यदि (i == e->nb_frame_deps)
        फर्काऊ AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_मान[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
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
        .command_Buffer_Info_गन्ती = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_गन्ती = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_गन्ती = e->sem_sig_cnt,
    };

    ret = vk->EndCommandBuffer(e->buf);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        फर्काऊ AVERROR_EXTERNAL;
    }

#यदि FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->lock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#यदि FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        फर्काऊ AVERROR_EXTERNAL;
    }

    लागि (पूर्णाङ्क i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    लागि (पूर्णाङ्क j = 0; j < e->nb_frame_deps; j++) {
        यदि (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->data[0];

            यदि (e->frame_update[j]) {
                पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);
                लागि (पूर्णाङ्क i = 0; i < nb_images; i++) {
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

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, शून्य *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    VkResult ret;
    पूर्णाङ्क index = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    VkMemoryAllocateInfo alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext           = alloc_extension,
    };

    alloc_info.allocationSize = req->size;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    लागि (पूर्णाङ्क i = 0; i < s->mprops.memory_Type_गन्ती; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        यदि (!(req->memoryTypeBits & (1 << i)))
            जारी;

        /* The memory type flags must include our properties */
        यदि ((req_flags != UINT32_MAX) &&
            ((s->mprops.memoryTypes[i].propertyFlags & req_flags) != req_flags))
            जारी;

        /* Found a suitable memory type */
        index = i;
        रोक;
    }

    यदि (index < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        फर्काऊ AVERROR(EINVAL);
    }

    alloc_info.memoryTypeIndex = index;

    ret = vk->AllocateMemory(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    यदि (ret != VK_SUCCESS)
        फर्काऊ AVERROR(ENOMEM);

    यदि (mem_flags)
        *mem_flags |= s->mprops.memoryTypes[index].propertyFlags;

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       पूर्णाङ्क width, पूर्णाङ्क height, VkFormat format, पूर्णाङ्क nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, शून्य *create_pnext)
{
    पूर्णाङ्क err;
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
        .samples       = VK_SAMPLE_गन्ती_1_BIT,
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
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->GetImageMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.memoryRequirements,
                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    यदि (err < 0)
        गच्छ fail;

    bind_info.image  = *img;
    bind_info.memory = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        गच्छ fail;
    }

    फर्काऊ 0;

fail:
    ff_vk_image_free(s, img, mem);
    फर्काऊ err;
}

शून्य ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    यदि (*mem) {
        vk->FreeMemory(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

पूर्णाङ्क ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, माप_प्रकार size,
                     शून्य *pNext, शून्य *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags)
{
    पूर्णाङ्क err;
    VkResult ret;
    पूर्णाङ्क use_ded_mem;
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
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    req_desc.buffer = buf->buf;

    vk->GetBufferMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefersDedicatedAllocation |
                  ded_req.requiresDedicatedAllocation;
    यदि (use_ded_mem) {
        ded_alloc.buffer = buf->buf;
        ded_alloc.pNext = alloc_pNext;
        alloc_pNext = &ded_alloc;
    }

    यदि (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags.pNext = alloc_pNext;
        alloc_pNext = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.memoryRequirements, flags, alloc_pNext,
                          &buf->flags, &buf->mem);
    यदि (err)
        फर्काऊ err;

    ret = vk->BindBufferMemory(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    यदि (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        VkBufferDeviceAddressInfo address_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
            .buffer = buf->buf,
        };
        buf->address = vk->GetBufferDeviceAddress(s->hwctx->act_dev, &address_info);
    }

    buf->size = size;

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      पूर्णाङ्क nb_buffers, पूर्णाङ्क invalidate)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange inval_list[64];
    पूर्णाङ्क inval_गन्ती = 0;

    लागि (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        शून्य *dst;
        ret = vk->MapMemory(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_WHOLE_SIZE, 0, &dst);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            फर्काऊ AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        यदि (mem)
            mem[i] = dst;
    }

    यदि (!invalidate)
        फर्काऊ 0;

    लागि (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        अचर VkMappedMemoryRange ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            .memory = buf[i]->mem,
            .size   = VK_WHOLE_SIZE,
        };
        यदि (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            जारी;
        inval_list[inval_गन्ती++] = ival_buf;
    }

    यदि (inval_गन्ती) {
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, inval_गन्ती,
                                               inval_list);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            फर्काऊ AVERROR_EXTERNAL;
        }
    }

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       पूर्णाङ्क flush)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (buf->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        फर्काऊ 0;

    अचर VkMappedMemoryRange flush_data = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = buf->mem,
        .offset = offset,
        .size   = mem_size,
    };

    यदि (flush)
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);
    अन्यथा
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_data);

    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, पूर्णाङ्क nb_buffers,
                        पूर्णाङ्क flush)
{
    पूर्णाङ्क err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange flush_list[64];
    पूर्णाङ्क flush_गन्ती = 0;

    यदि (flush) {
        लागि (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
            अचर VkMappedMemoryRange flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .memory = buf[i]->mem,
                .size   = VK_WHOLE_SIZE,
            };

            av_assert0(!buf[i]->host_ref);
            यदि (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                जारी;
            flush_list[flush_गन्ती++] = flush_buf;
        }
    }

    यदि (flush_गन्ती) {
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, flush_गन्ती,
                                          flush_list);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    लागि (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        vk->UnmapMemory(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = रिक्त;
    }

    फर्काऊ err;
}

शून्य ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (!buf || !s->hwctx)
        फर्काऊ;

    यदि (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_buffer(s, buf, 0);
    यदि (buf->buf != VK_NULL_HANDLE)
        vk->DestroyBuffer(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    यदि (buf->mem != VK_NULL_HANDLE)
        vk->FreeMemory(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    यदि (buf->host_ref)
        av_buffer_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = रिक्त;
}

स्थिर शून्य pooled_buf_free(AVRefStructOpaque opaque, शून्य *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णाङ्क ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            शून्य *create_pNext, माप_प्रकार size,
                            VkMemoryPropertyFlagBits mem_props)
{
    पूर्णाङ्क err;
    FFVkBuffer *data;

    यदि (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(परिमाण(FFVkBuffer), 0, ctx,
                                                रिक्त, रिक्त, pooled_buf_free,
                                                रिक्त);
        यदि (!(*buf_pool))
            फर्काऊ AVERROR(ENOMEM);
    }

    *buf = data = av_refstruct_pool_get(*buf_pool);
    यदि (!data)
        फर्काऊ AVERROR(ENOMEM);

    यदि (data->size >= size)
        फर्काऊ 0;

    ff_vk_free_buf(ctx, data);
    स_रखो(data, 0, परिमाण(*data));

    err = ff_vk_create_buf(ctx, data, size,
                           create_pNext, रिक्त, usage,
                           mem_props);
    यदि (err < 0) {
        av_refstruct_unref(buf);
        फर्काऊ err;
    }

    यदि (mem_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_buffer(ctx, data, &data->mapped_mem, 0);
        यदि (err < 0) {
            av_refstruct_unref(buf);
            फर्काऊ err;
        }
    }

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क create_mapped_buffer(FFVulkanContext *s,
                                FFVkBuffer *vkb, VkBufferUsageFlags usage,
                                माप_प्रकार size,
                                VkExternalMemoryBufferCreateInfo *create_desc,
                                VkImportMemoryHostPointerInfoEXT *import_desc,
                                VkMemoryHostPointerPropertiesEXT props)
{
    पूर्णाङ्क err;
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
    यदि (err < 0)
        फर्काऊ err;

    ret = vk->CreateBuffer(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    यदि (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        फर्काऊ AVERROR_EXTERNAL;
    }

    ret = vk->BindBufferMemory(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    यदि (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->DestroyBuffer(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

स्थिर शून्य host_map_free(AVRefStructOpaque opaque, शून्य *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णाङ्क ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          अचर AVBufferRef *src_buf,
                          VkBufferUsageFlags usage)
{
    पूर्णाङ्क err;
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
        .pNext = usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT ? &alloc_flags : रिक्त,
    };
    VkMemoryHostPointerPropertiesEXT props;

    AVBufferRef *ref;
    FFVkBuffer *vkb;
    माप_प्रकार offs;
    माप_प्रकार buffer_size;

    *dst = रिक्त;

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
    यदि (!(ret == VK_SUCCESS && props.memoryTypeBits))
        फर्काऊ AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_buffer_ref(src_buf);
    यदि (!ref)
        फर्काऊ AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    अचर VkDeviceSize src_avail = src_buf->size - (src_data - src_buf->data);
    buffer_size = offs + FFMIN(size, src_avail);
    buffer_size = FFALIGN(buffer_size, s->props.properties.limits.minMemoryMapAlignment);
    buffer_size = FFALIGN(buffer_size, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(परिमाण(*vkb), 0, s, host_map_free);
    यदि (!vkb) {
        av_buffer_unref(&ref);
        फर्काऊ AVERROR(ENOMEM);
    }

    err = create_mapped_buffer(s, vkb, usage,
                               buffer_size, &create_desc, &import_desc,
                               props);
    यदि (err < 0) {
        av_buffer_unref(&ref);
        av_refstruct_unref(&vkb);
        फर्काऊ err;
    }

    यदि (usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
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

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_shader_add_थप_const(FFVulkanShader *shd, पूर्णाङ्क offset, पूर्णाङ्क size,
                                VkShaderStageFlagBits stage)
{
    Vk_थप_Constant_Range *pc = &shd->थप_consts[shd->थप_consts_अङ्क++];
    av_assert1(shd->थप_consts_अङ्क < FF_VK_MAX_थप_CONSTS);
    pc->stageFlags = stage;
    pc->offset = offset;
    pc->size = size;
    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       पूर्णाङ्क unnorm_coords, VkFilter filt)
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
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, पूर्णाङ्क p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);
    पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(hwfc->sw_format);

    स्थिर अचर VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    यदि (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        फर्काऊ VK_IMAGE_ASPECT_COLOR_BIT;

    फर्काऊ plane_aspect[p];
}

पूर्णाङ्क ff_vk_mt_is_np_rgb(गणना AVPixelFormat pix_fmt)
{
    यदि (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        फर्काऊ 1;
    फर्काऊ 0;
}

शून्य ff_vk_set_perm(गणना AVPixelFormat pix_fmt, पूर्णाङ्क lut[4], पूर्णाङ्क inv)
{
    विकल्प (pix_fmt) {
    पक्ष AV_PIX_FMT_GBRP:
    पक्ष AV_PIX_FMT_GBRAP:
    पक्ष AV_PIX_FMT_GBRAP10:
    पक्ष AV_PIX_FMT_GBRAP12:
    पक्ष AV_PIX_FMT_GBRAP14:
    पक्ष AV_PIX_FMT_GBRAP16:
    पक्ष AV_PIX_FMT_GBRAPF16:
    पक्ष AV_PIX_FMT_GBRP10:
    पक्ष AV_PIX_FMT_GBRP12:
    पक्ष AV_PIX_FMT_GBRP14:
    पक्ष AV_PIX_FMT_GBRP16:
    पक्ष AV_PIX_FMT_GBRPF16:
    पक्ष AV_PIX_FMT_GBRPF32:
    पक्ष AV_PIX_FMT_GBRAP32:
    पक्ष AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        रोक;
    पक्ष AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        रोक;
    पक्ष AV_PIX_FMT_BGRA:
    पक्ष AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        रोक;
    स्वभाव:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        रोक;
    }

    यदि (inv) {
        पूर्णाङ्क lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        लागि (पूर्णाङ्क i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    फर्काऊ;
}

अचर वर्ण *ff_vk_shader_rep_fmt(गणना AVPixelFormat pix_fmt,
                                 गणना FFVkShaderRepFormat rep_fmt)
{
    विकल्प (pix_fmt) {
    पक्ष AV_PIX_FMT_RGBA:
    पक्ष AV_PIX_FMT_BGRA:
    पक्ष AV_PIX_FMT_RGB24:
    पक्ष AV_PIX_FMT_BGR24:
    पक्ष AV_PIX_FMT_BGR0:
    पक्ष AV_PIX_FMT_RGB0:
    पक्ष AV_PIX_FMT_RGB565:
    पक्ष AV_PIX_FMT_BGR565:
    पक्ष AV_PIX_FMT_UYVA:
    पक्ष AV_PIX_FMT_YUYV422:
    पक्ष AV_PIX_FMT_UYVY422: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_X2RGB10:
    पक्ष AV_PIX_FMT_X2BGR10:
    पक्ष AV_PIX_FMT_Y210:
    पक्ष AV_PIX_FMT_XV30: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = रिक्त,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGB48:
    पक्ष AV_PIX_FMT_RGBA64:
    पक्ष AV_PIX_FMT_Y212:
    पक्ष AV_PIX_FMT_Y216:
    पक्ष AV_PIX_FMT_XV36:
    पक्ष AV_PIX_FMT_XV48: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGBAF16: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGBF32:
    पक्ष AV_PIX_FMT_RGBAF32: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGB96:
    पक्ष AV_PIX_FMT_RGBA128: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = रिक्त,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_GBRP:
    पक्ष AV_PIX_FMT_GRAY8:
    पक्ष AV_PIX_FMT_GBRAP:
    पक्ष AV_PIX_FMT_YUV420P:
    पक्ष AV_PIX_FMT_YUV422P:
    पक्ष AV_PIX_FMT_YUV444P:
    पक्ष AV_PIX_FMT_YUVA420P:
    पक्ष AV_PIX_FMT_YUVA422P:
    पक्ष AV_PIX_FMT_YUVA444P: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_GRAY10:
    पक्ष AV_PIX_FMT_GRAY12:
    पक्ष AV_PIX_FMT_GRAY14:
    पक्ष AV_PIX_FMT_GRAY16:
    पक्ष AV_PIX_FMT_GBRAP10:
    पक्ष AV_PIX_FMT_GBRAP12:
    पक्ष AV_PIX_FMT_GBRAP14:
    पक्ष AV_PIX_FMT_GBRAP16:
    पक्ष AV_PIX_FMT_GBRAPF16:
    पक्ष AV_PIX_FMT_GBRP10:
    पक्ष AV_PIX_FMT_GBRP12:
    पक्ष AV_PIX_FMT_GBRP14:
    पक्ष AV_PIX_FMT_GBRP16:
    पक्ष AV_PIX_FMT_GBRPF16:
    पक्ष AV_PIX_FMT_XYZP12:
    पक्ष AV_PIX_FMT_YUV420P10:
    पक्ष AV_PIX_FMT_YUV420P12:
    पक्ष AV_PIX_FMT_YUV420P16:
    पक्ष AV_PIX_FMT_YUV422P10:
    पक्ष AV_PIX_FMT_YUV422P12:
    पक्ष AV_PIX_FMT_YUV422P16:
    पक्ष AV_PIX_FMT_YUV444P10:
    पक्ष AV_PIX_FMT_YUV444P12:
    पक्ष AV_PIX_FMT_YUV444P16:
    पक्ष AV_PIX_FMT_YUVA420P10:
    पक्ष AV_PIX_FMT_YUVA420P16:
    पक्ष AV_PIX_FMT_YUVA422P10:
    पक्ष AV_PIX_FMT_YUVA422P12:
    पक्ष AV_PIX_FMT_YUVA422P16:
    पक्ष AV_PIX_FMT_YUVA444P10:
    पक्ष AV_PIX_FMT_YUVA444P12:
    पक्ष AV_PIX_FMT_YUVA444P16:
    पक्ष AV_PIX_FMT_BAYER_RGGB16: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_GRAY32:
    पक्ष AV_PIX_FMT_GRAYF32:
    पक्ष AV_PIX_FMT_GBRPF32:
    पक्ष AV_PIX_FMT_GBRAPF32: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_GBRAP32: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = रिक्त,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_NV12:
    पक्ष AV_PIX_FMT_NV16:
    पक्ष AV_PIX_FMT_NV24: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_P010:
    पक्ष AV_PIX_FMT_P210:
    पक्ष AV_PIX_FMT_P410: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = रिक्त,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_P012:
    पक्ष AV_PIX_FMT_P016:
    पक्ष AV_PIX_FMT_P212:
    पक्ष AV_PIX_FMT_P216:
    पक्ष AV_PIX_FMT_P412:
    पक्ष AV_PIX_FMT_P416: {
        अचर वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        फर्काऊ rep_tab[rep_fmt];
    };
    स्वभाव:
        फर्काऊ "rgba32f";
    }
}

स्थिर शून्य reset_imageviews(AVRefStructOpaque unused, शून्य *obj)
{
    FFVkImageViews *iv = obj;

    लागि (पूर्णाङ्क i = 0; i < iv->nb_views; i++) {
        यदि (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    स_रखो(iv->views, 0, परिमाण(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, पूर्णाङ्क nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_अङ्क_DATA_POINTERS);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    यदि (!iv)
        फर्काऊ रिक्त;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    फर्काऊ iv;
}

VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, गणना FFVkShaderRepFormat rep_fmt)
{
#define REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#define REPS_FMT_PACK(fmt, अङ्क) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## अङ्क, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## अङ्क, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## अङ्क, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## अङ्क,

    अचर VkFormat fmts_map[][4] = {
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

    यदि (fmt == VK_FORMAT_UNDEFINED)
        फर्काऊ VK_FORMAT_UNDEFINED;

    लागि (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        यदि (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            फर्काऊ fmts_map[i][rep_fmt];
    }

    फर्काऊ VK_FORMAT_UNDEFINED;
}

पूर्णाङ्क ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, पूर्णाङ्क plane, गणना FFVkShaderRepFormat rep_fmt)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    अचर VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    अचर पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);

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
            .level_गन्ती = 1,
            .layer_गन्ती = 1,
        },
    };
    यदि (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        फर्काऊ AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspectMask;

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अङ्क_DATA_POINTERS],
                                AVFrame *f,
                                अचर VkFormat fmts[AV_अङ्क_DATA_POINTERS])
{
    पूर्णाङ्क err = 0;
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->data[0];
    अचर पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);
    अचर पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_अङ्क_DATA_POINTERS] = { 0 };

    लागि (पूर्णाङ्क i = 0; i < nb_planes; i++) {
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
                .level_गन्ती = 1,
                .layer_गन्ती = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    लागि (पूर्णाङ्क i = 0; i < nb_planes; i++)
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    स_नकल(views, tmp_views, nb_planes*परिमाण(*views));

    फर्काऊ 0;

fail:
    लागि (पूर्णाङ्क i = 0; i < nb_planes; i++)
        यदि (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    फर्काऊ err;
}

पूर्णाङ्क ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_अङ्क_DATA_POINTERS],
                            AVFrame *f, गणना FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    अचर VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    अचर पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(hwfc->sw_format);
    VkFormat fmts[AV_अङ्क_DATA_POINTERS] = { 0 };

    लागि (पूर्णाङ्क i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_to_rep(rep_fmts[i], rep_fmt);
        यदि (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            फर्काऊ AVERROR(EINVAL);
        }
    }

    फर्काऊ ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

शून्य ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, पूर्णाङ्क *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    पूर्णाङ्क found = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->data[0];
    अचर पूर्णाङ्क nb_images = ff_vk_गन्ती_images(vkf);
    लागि (पूर्णाङ्क i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->data[0] == pic->data[0]) {
            यदि (e->frame_update[i])
                found = i;
            रोक;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    लागि (पूर्णाङ्क i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (VkImageMemoryBarrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .pNext = रिक्त,
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
                .layer_गन्ती = 1,
                .level_गन्ती = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], रिक्त);
}

पूर्णाङ्क ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    स_नकल(shd->lg_size, wg_size, 3*परिमाण(uint32_t));

    shd->subgroup_info = (VkPipelineShaderStageRequiredSubgroupSizeCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO,
        .requiredSubgroupSize = required_subgroup_size,
    };

    विकल्प (shd->stage) {
    पक्ष VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
    पक्ष VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    पक्ष VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
    पक्ष VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    पक्ष VK_SHADER_STAGE_MISS_BIT_KHR:
    पक्ष VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        रोक;
    पक्ष VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        रोक;
    स्वभाव:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        रोक;
    };

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pSetLayouts            = shd->desc_layout,
        .set_Layout_गन्ती         = shd->nb_descriptor_sets,
        .थप_Constant_Range_गन्ती = shd->थप_consts_अङ्क,
        .p_थप_Constant_Ranges    = shd->थप_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                अचर uint8_t *spirv, माप_प्रकार spirv_len)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext    = रिक्त,
        .flags    = 0x0,
        .pCode    = (शून्य *)spirv,
        .codeSize = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, अचर वर्ण *entrypoint)
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
                     &shd->subgroup_info : रिक्त,
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
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        फर्काऊ AVERROR_EXTERNAL;
    }

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    VkResult ret;
    FFVulkanFunctions *vk = &s->vkfn;

    पूर्णाङ्क has_singular = 0;
    पूर्णाङ्क max_descriptors = 0;
    लागि (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_set[i].nb_bindings);
        यदि (shd->desc_set[i].singular)
            has_singular = 1;
    }
    shd->use_थप = (s->extensions & FF_VK_EXT_थप_DESCRIPTOR) &&
                    (max_descriptors <= s->थप_desc_props.max_थप_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    लागि (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkanDescriptorSet *set = &shd->desc_set[i];
        VkDescriptorSetLayoutCreateInfo desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .binding_गन्ती = set->nb_bindings,
            .pBindings = set->binding,
            .flags = (shd->use_थप) ?
                     VK_DESCRIPTOR_SET_LAYOUT_CREATE_थप_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->CreateDescriptorSetLayout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            फर्काऊ AVERROR_EXTERNAL;
        }
    }

    फर्काऊ 0;
}

पूर्णाङ्क ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      अचर वर्ण *spirv, माप_प्रकार spirv_len,
                      अचर वर्ण *entrypoint)
{
    पूर्णाङ्क err;
    FFVulkanFunctions *vk = &s->vkfn;
    VkSpecializationMapEntry spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    माप_प्रकार आगत_size = spirv_len;

    यदि (shd->precompiled) {
        यदि (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_Entry_गन्ती = 0,
                .pData = shd->lg_size,
                .dataSize = 0,
            };
            shd->specialization_info = &spec_info;
        }

        VkSpecializationMapEntry *spe = (शून्य *)shd->specialization_info->pMapEntries;
        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_Entry_गन्ती++] = (VkSpecializationMapEntry) {
                .constantID = 253 + i,
                .offset = shd->specialization_info->dataSize + i*परिमाण(uint32_t),
                .size = परिमाण(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->pData;
        स_नकल(&spd[shd->specialization_info->dataSize],
               shd->lg_size, 3*परिमाण(uint32_t));
        shd->specialization_info->dataSize += 3*परिमाण(uint32_t);

#यदि CONFIG_SHADER_COMPRESSION
        uint8_t *out;
        माप_प्रकार out_len;
        पूर्णाङ्क ret = ff_zlib_expand(s, &out, &out_len, spirv, spirv_len);
        यदि (ret < 0)
            फर्काऊ ret;
        spirv = out;
        spirv_len = out_len;
#endif
    }

    err = init_descriptors(s, shd);
    यदि (err < 0)
        गच्छ end;

    err = init_pipeline_layout(s, shd);
    यदि (err < 0)
        गच्छ end;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    यदि (err < 0)
        गच्छ end;

    विकल्प (shd->bind_point) {
    पक्ष VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        रोक;
    स्वभाव:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        गच्छ end;
        रोक;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    यदि (err < 0)
        गच्छ end;

    यदि (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    अन्यथा
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    यदि (आगत_size != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", आगत_size);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

end:
    यदि (shd->precompiled) {
        shd->specialization_info->map_Entry_गन्ती -= 3;
        shd->specialization_info->dataSize -= 3*परिमाण(uint32_t);
    }
#यदि CONFIG_SHADER_COMPRESSION
    यदि (shd->precompiled)
        av_free((शून्य *)spirv);
#endif
    फर्काऊ err;
}

शून्य ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     अचर FFVulkanDescriptorSetBinding *desc, पूर्णाङ्क nb,
                                     पूर्णाङ्क singular)
{
    FFVulkanDescriptorSet *set = &shd->desc_set[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    लागि (पूर्णाङ्क i = 0; i < nb; i++) {
        set->binding[i].binding            = i;
        set->binding[i].descriptorType     = desc[i].type;
        set->binding[i].descriptor_गन्ती    = FFMAX(desc[i].elems, 1);
        set->binding[i].stageFlags         = desc[i].stages;
        set->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    लागि (पूर्णाङ्क i = 0; i < nb; i++) {
        पूर्णाङ्क j;
        लागि (j = 0; j < shd->nb_desc_pool_size; j++)
            यदि (shd->desc_pool_size[j].type == desc[i].type)
                रोक;
        यदि (j >= shd->nb_desc_pool_size) {
            shd->nb_desc_pool_size++;
            av_assert1(shd->nb_desc_pool_size < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_size[j].type             = desc[i].type;
        shd->desc_pool_size[j].descriptor_गन्ती += FFMAX(desc[i].elems, 1);
    }

    set->singular = singular;
    set->nb_bindings = nb;
}

पूर्णाङ्क ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    यदि (!shd->nb_descriptor_sets)
        फर्काऊ 0;

    FFVulkanShaderData *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    यदि (!shd->use_थप) {
        VkResult ret;
        FFVulkanFunctions *vk = &s->vkfn;
        VkDescriptorSetLayout *tmp_layouts;
        VkDescriptorSetAllocateInfo set_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        लागि (पूर्णाङ्क i = 0; i < shd->nb_desc_pool_size; i++)
            shd->desc_pool_size[i].descriptor_गन्ती *= pool->pool_size;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_size,
            .pool_Size_गन्ती = shd->nb_desc_pool_size,
            .maxSets = sd->nb_descriptor_sets*pool->pool_size,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            फर्काऊ AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, परिमाण(*tmp_layouts));
        यदि (!tmp_layouts)
            फर्काऊ AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        लागि (पूर्णाङ्क i = 0; i < pool->pool_size; i++)
            लागि (पूर्णाङ्क j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        set_alloc_info = (VkDescriptorSetAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .pSetLayouts        = tmp_layouts,
            .descriptor_Set_गन्ती = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        परिमाण(*tmp_layouts));
        यदि (!sd->desc_sets) {
            av_free(tmp_layouts);
            फर्काऊ AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &set_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            फर्काऊ AVERROR_EXTERNAL;
        }
    }

    फर्काऊ 0;
}

स्थिर अन्तःस्थ अचर FFVulkanShaderData *get_shd_data(FFVkExecContext *e,
                                                     अचर FFVulkanShader *shd)
{
    लागि (पूर्णाङ्क i = 0; i < e->parent->nb_reg_shd; i++)
        यदि (e->parent->reg_shd[i].shd == shd)
            फर्काऊ &e->parent->reg_shd[i];
    फर्काऊ रिक्त;
}

स्थिर अन्तःस्थ शून्य update_set_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, पूर्णाङ्क set,
                                         VkWriteDescriptorSet *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];
    अचर FFVulkanShaderData *sd = get_shd_data(e, shd);

    यदि (desc_set->singular) {
        लागि (पूर्णाङ्क i = 0; i < e->parent->pool_size; i++) {
            write_info->dstSet = sd->desc_sets[i*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, रिक्त);
        }
    } अन्यथा {
        यदि (shd->use_थप) {
            vk->Cmd_थप_Descriptor_Set_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        set, 1,
                                        write_info);
        } अन्यथा {
            write_info->dstSet = sd->desc_sets[e->idx*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, रिक्त);
        }
    }
}

पूर्णाङ्क ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णाङ्क set, पूर्णाङ्क bind, पूर्णाङ्क offs,
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
        .descriptor_गन्ती = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    फर्काऊ 0;
}

शून्य ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णाङ्क set, पूर्णाङ्क binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->data;
    अचर पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(hwfc->sw_format);

    लागि (पूर्णाङ्क i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, set, binding, i,
                                views[i], layout, sampler);
}

पूर्णाङ्क ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णाङ्क set, पूर्णाङ्क bind, पूर्णाङ्क elem,
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
        .descriptor_गन्ती = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pBufferInfo = &desc_pool_write_info_buf,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    फर्काऊ 0;
}

शून्य ff_vk_shader_update_थप_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    पूर्णाङ्क offset, माप_प्रकार size, शून्य *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_थप_Constants(e->buf, shd->pipeline_layout,
                         stage, offset, size, src);
}

शून्य ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            अचर FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    अचर FFVulkanShaderData *sd = get_shd_data(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    यदि (sd && sd->nb_descriptor_sets) {
        यदि (!shd->use_थप) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_point, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, रिक्त);
        }
    }
}

शून्य ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#यदि 0
    यदि (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#endif

    यदि (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    यदि (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    लागि (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++)
        यदि (shd->desc_layout[i])
            vk->DestroyDescriptorSetLayout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

शून्य ff_vk_uninit(FFVulkanContext *s)
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

पूर्णाङ्क ff_vk_init(FFVulkanContext *s, शून्य *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref)
{
    पूर्णाङ्क err;

    स्थिर अचर AVClass vulkan_context_class = {
        .class_name       = "vk",
        .version          = LIBAVUTIL_VERSION_INT,
        .parent_log_context_offset = दुरत्व(FFVulkanContext, log_parent),
    };

    स_रखो(s, 0, परिमाण(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    यदि (frames_ref) {
        s->frames_ref = av_buffer_ref(frames_ref);
        यदि (!s->frames_ref)
            फर्काऊ AVERROR(ENOMEM);

        s->frames = (AVHWFramesContext *)s->frames_ref->data;
        s->hwfc = s->frames->hwctx;

        device_ref = s->frames->device_ref;
    }

    s->device_ref = av_buffer_ref(device_ref);
    यदि (!s->device_ref) {
        ff_vk_uninit(s);
        फर्काऊ AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->data;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_to_mask(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_to_mask(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_load_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    यदि (err < 0) {
        ff_vk_uninit(s);
        फर्काऊ err;
    }

    err = ff_vk_load_props(s);
    यदि (err < 0) {
        ff_vk_uninit(s);
        फर्काऊ err;
    }

    फर्काऊ 0;
}
