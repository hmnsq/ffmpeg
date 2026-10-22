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

#समावेश "config.h"
#समावेश "avassert.h"
#समावेश "mem.h"
#समावेश "random_seed.h"
#समावेश "refstruct.h"

#समावेश "vulkan.h"
#समावेश "libavutil/vulkan_loader.h"

#अगर CONFIG_SHADER_COMPRESSION
#समावेश "libavutil/zlib_utils.h"
#पूर्ण_अगर

स्थिर VkComponentMapping ff_comp_identity_map = {
    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
};

/* Converts return values to strings */
स्थिर अक्षर *ff_vk_ret2str(Vk_परिणाम res)
{
#घोषणा CASE(VAL) हाल VAL: वापस #VAL
    चयन (res) {
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
    शेष: वापस "Unknown error";
    }
#अघोषित CASE
}

/* Malitia pura, Khronos */
#घोषणा FN_MAP_TO(dst_t, dst_name, src_t, src_name)                                 \
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
        MAP_TO(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_निवेश_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_TO(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        वापस dst;                                                     \
    }

#घोषणा MAP_TO(flag1, flag2) अगर (src & flag2) dst |= flag1;
FN_MAP_TO(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#अघोषित MAP_TO
#घोषणा MAP_TO(flag1, flag2) अगर (src & flag1) dst |= flag2;
FN_MAP_TO(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#अघोषित MAP_TO
#अघोषित FN_MAP_TO

अटल व्योम load_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    क्रम (पूर्णांक i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        पूर्णांक skip = 0;
        क्रम (पूर्णांक j = 0; j < s->nb_qfs; j++) {
            अगर (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                अवरोध;
            }
        }
        अगर (skip)
            जारी;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

अटल व्योम reset_imageviews(AVRefStructOpaque unused, व्योम *obj);

पूर्णांक ff_vk_load_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_आकार_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->धकेलो_desc_props, FF_VK_EXT_धकेलो_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_धकेलो_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_MEMORY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_matrix_props, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#अगर_घोषित VK_EXT_shader_long_vector
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_vector_props, FF_VK_EXT_LONG_VECTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_PROPERTIES_EXT);
#पूर्ण_अगर

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#अगर_घोषित VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#पूर्ण_अगर

    अगर (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(माप(FFVkImageViews), 0,
                                                         शून्य, शून्य, reset_imageviews,
                                                         शून्य, शून्य);
        अगर (!s->imageviews_pool)
            वापस AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(माप(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_गिनती = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_गिनती = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    अगर (s->host_image_props.copy_Src_Layout_गिनती == 512 ||
        s->host_image_props.copy_Dst_Layout_गिनती == 512) {
        VkImageLayout *new_array;
        माप_प्रकार new_आकार;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = शून्य;
        s->host_image_props.copy_Src_Layout_गिनती =
        s->host_image_props.copy_Dst_Layout_गिनती = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_आकार = s->host_image_props.copy_Src_Layout_गिनती +
                   s->host_image_props.copy_Dst_Layout_गिनती;
        new_आकार *= माप(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_आकार);
        अगर (!new_array)
            वापस AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_गिनती;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->GetPhysicalDeviceMemoryProperties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    क्रम (पूर्णांक i = 0; i < s->mprops.memory_Type_गिनती; i++)
        s->host_cached_flag |= s->mprops.memoryTypes[i].propertyFlags &
                               VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

    load_enabled_qfs(s);

    अगर (s->qf_props)
        वापस 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, शून्य);

    s->qf_props = av_calloc(s->tot_nb_qfs, माप(*s->qf_props));
    अगर (!s->qf_props)
        वापस AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, माप(*s->query_props));
    अगर (!s->qf_props) {
        av_freep(&s->qf_props);
        वापस AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, माप(*s->video_props));
    अगर (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        वापस AVERROR(ENOMEM);
    }

#अगर_घोषित VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, माप(*s->ownership_props));
    अगर (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        वापस AVERROR(ENOMEM);
    }
#पूर्ण_अगर

    क्रम (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_परिणाम_STATUS_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR);
#अगर_घोषित VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#पूर्ण_अगर
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    अगर (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, शून्य);

        अगर (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                माप(VkCooperativeMatrixPropertiesKHR));
            क्रम (पूर्णांक i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    वापस 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops)
{
    क्रम (पूर्णांक i = 0; i < s->hwctx->nb_qf; i++) {
        अगर ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            वापस &s->hwctx->qf[i];
        }
    }
    वापस शून्य;
}

अटल व्योम exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

व्योम ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        अगर (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_गिनती = 1,
                .pSemaphores = &e->sem,
                .p_मूल्यावली = &e->sem_मूल्य,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->lock);
    }

    /* Free shader-specific data */
    क्रम (पूर्णांक i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_तथ्य *sd = &pool->reg_shd[i];

        अगर (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++) {
        अगर (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        अगर (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    अगर (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_तथ्य);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_आकार = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
अटल atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)शून्य)->qf)];
अटल AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

अटल व्योम exec_pool_phase_seed(व्योम)
{
    uint32_t seed = av_get_random_seed();
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], seed, memory_order_relaxed);
}

पूर्णांक ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, पूर्णांक nb_contexts,
                         पूर्णांक nb_queries, VkQueryType query_type, पूर्णांक query_64bit,
                         स्थिर व्योम *query_create_pnext)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_बफर_Allocate_Info cbuf_create;

    स्थिर VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = शून्य;

    atomic_init(&pool->idx, 0);

    अगर (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        अगर (!ef)
            वापस AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*माप(*pool->cmd_buf_pools));
    अगर (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*माप(*pool->cmd_bufs));
    अगर (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    क्रम (पूर्णांक i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_बफर_BIT,
            .queue_Family_सूचकांक   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_बफर_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_बफर_ALLOCATE_INFO,
            .level              = VK_COMMAND_बफर_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_बफर_गिनती = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }
    }

    /* Query pool */
    अगर (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_अग्र = query_create_pnext,
            .queryType = query_type,
            .query_गिनती = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_status_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        अगर (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            पूर्णांक nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_status_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } अन्यथा अगर (query_type == VK_QUERY_TYPE_परिणाम_STATUS_ONLY_KHR) {
            pool->query_status_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_आकार = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_तथ्य = av_calloc(nb_contexts, pool->qd_आकार);
        अगर (!pool->query_तथ्य) {
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, माप(*pool->contexts));
    अगर (!pool->contexts) {
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    pool->pool_आकार = nb_contexts;

    क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++)
        pthread_mutex_init(&pool->contexts[i].lock, शून्य);

#अगर_घोषित VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    पूर्णांक internal_queue_sync = 0;
    अगर (s->extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC) {
        स्थिर VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_find_struct(s->hwctx->device_features.p_अग्र,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        internal_queue_sync = iqs && iqs->internallySynchronizedQueues;
    }
#पूर्ण_अगर

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_seed);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    पूर्णांक pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_अग्र = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_तथ्य = ((uint8_t *)pool->query_तथ्य) + pool->qd_आकार*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->अंक : (i + phase) % qf->अंक;
        e->qf = qf->idx;
        VkDeviceQueueInfo2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
#अगर_घोषित VK_KHR_internally_synchronized_queues
            .flags            = internal_queue_sync ?
                                VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR : 0,
#पूर्ण_अगर
            .queue_Family_सूचकांक = qf->idx,
            .queue_सूचकांक       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->queue);
    }

    वापस 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    वापस err;
}

Vk_परिणाम ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              व्योम **तथ्य, Vk_Query_परिणाम_Flag_Bits flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    स्थिर FFVkExecPool *pool = e->parent;
    Vk_Query_परिणाम_Flags qf = flags & ~(VK_QUERY_परिणाम_64_BIT |
                                      VK_QUERY_परिणाम_WITH_STATUS_BIT_KHR);

    अगर (!e->query_तथ्य) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        वापस VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_परिणाम_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_परिणाम_WITH_STATUS_BIT_KHR : 0x0;

    अगर (तथ्य)
        *तथ्य = e->query_तथ्य;

    वापस vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_आकार, e->query_तथ्य,
                                   pool->qd_आकार, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        अगर (pthread_mutex_trylock(&e->lock))
            जारी; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        अगर (vk->Get_Semaphore_गणक_मूल्य(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_मूल्य &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->lock);
    }

    वापस &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_आकार];
}

व्योम ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गिनती = 1,
        .pSemaphores = &e->sem,
        .p_मूल्यावली = &e->sem_मूल्य,
    };
    pthread_mutex_lock(&e->lock);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->lock);
}

पूर्णांक ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    स्थिर FFVkExecPool *pool = e->parent;

    Vk_Command_बफर_Begin_Info cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_बफर_BEGIN_INFO,
        .flags = VK_COMMAND_बफर_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गिनती = 1,
        .pSemaphores = &e->sem,
        .p_मूल्यावली = &e->sem_मूल्य,
    };

    pthread_mutex_lock(&e->lock);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_बफर(e->buf, &cmd_start);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->lock);
        वापस AVERROR_EXTERNAL;
    }

    अगर (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_मूल्य++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .मूल्य = e->sem_मूल्य,
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->lock);

    वापस 0;
}

अटल व्योम exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    क्रम (पूर्णांक j = 0; j < e->nb_buf_deps; j++)
        av_बफर_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    क्रम (पूर्णांक j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    क्रम (पूर्णांक j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        चयन (od->type) {
        हाल VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            अवरोध;
        हाल VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            अवरोध;
        शेष:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    क्रम (पूर्णांक j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    क्रम (पूर्णांक j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        अगर (e->frame_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];
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

व्योम ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .मूल्य = e->sem_मूल्य,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_बफर(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

व्योम ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  व्योम *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

व्योम ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   व्योम *obj)
{
    व्योम **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    क्रम (पूर्णांक i = 0; i < e->nb_refstruct_deps; i++) {
        अगर (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            वापस;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = शून्य;
}

व्योम ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

पूर्णांक ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    अगर (!e->sw_frame_deps[e->nb_sw_frame_deps])
        वापस AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    वापस 0;
}

व्योम ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मूल्य = val,
        .stageMask = stage,
    };
}

व्योम ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मूल्य = val,
        .stageMask = stage,
    };
}

व्योम ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णांक nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णांक रुको)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    अगर (!रुको) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        क्रम (पूर्णांक i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stageMask = stage,
            };
        }

        वापस;
    }

    /* Ownership of each semaphore passes to the execution */
    क्रम (पूर्णांक i = 0; i < nb; i++) {
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_add_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

पूर्णांक ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];
    पूर्णांक nb_images = ff_vk_गिनती_images(vkf);

    /* Don't add duplicates */
    क्रम (पूर्णांक i = 0; i < e->nb_frame_deps; i++)
        अगर (e->frame_deps[i]->तथ्य[0] == f->तथ्य[0])
            वापस 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    अगर (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_बफर_ref(f->buf[0]);
        अगर (!e->buf_deps[e->nb_buf_deps])
            वापस AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->lock_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मूल्य = vkf->sem_मूल्य[i],
            .stageMask = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मूल्य = vkf->sem_मूल्य[i] + 1,
            .stageMask = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_मूल्य[i];
        e->sem_sig_val_dst_cnt++;
    }

    वापस 0;
}

व्योम ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar)
{
    पूर्णांक i;
    क्रम (i = 0; i < e->nb_frame_deps; i++)
        अगर (e->frame_deps[i]->तथ्य[0] == f->तथ्य[0])
            अवरोध;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    अगर (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dst_Queue_Family_सूचकांक;
    e->access_dst[i] = bar->dstAccessMask;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

पूर्णांक ff_vk_exec_mirror_sem_मूल्य(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];

    /* Reject unknown frames */
    पूर्णांक i;
    क्रम (i = 0; i < e->nb_frame_deps; i++)
        अगर (e->frame_deps[i]->तथ्य[0] == f->तथ्य[0])
            अवरोध;
    अगर (i == e->nb_frame_deps)
        वापस AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_मूल्य[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    वापस 0;
}

पूर्णांक ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_बफर_Submit_Info cmd_buf_info = (Vk_Command_बफर_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_बफर_SUBMIT_INFO,
        .command_बफर = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_बफर_Infos = &cmd_buf_info,
        .command_बफर_Info_गिनती = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_गिनती = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_गिनती = e->sem_sig_cnt,
    };

    ret = vk->End_Command_बफर(e->buf);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        वापस AVERROR_EXTERNAL;
    }

#अगर FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->lock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#पूर्ण_अगर
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#अगर FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#पूर्ण_अगर

    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        वापस AVERROR_EXTERNAL;
    }

    क्रम (पूर्णांक i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    क्रम (पूर्णांक j = 0; j < e->nb_frame_deps; j++) {
        अगर (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
            AVVulkanFramesContext *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];

            अगर (e->frame_update[j]) {
                पूर्णांक nb_images = ff_vk_गिनती_images(vkf);
                क्रम (पूर्णांक i = 0; i < nb_images; i++) {
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

    वापस 0;
}

पूर्णांक ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, व्योम *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    Vk_परिणाम ret;
    पूर्णांक सूचकांक = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    VkMemoryAllocateInfo alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .p_अग्र           = alloc_extension,
    };

    alloc_info.allocation_आकार = req->आकार;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    क्रम (पूर्णांक i = 0; i < s->mprops.memory_Type_गिनती; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        अगर (!(req->memoryTypeBits & (1 << i)))
            जारी;

        /* The memory type flags must include our properties */
        अगर ((req_flags != UINT32_MAX) &&
            ((s->mprops.memoryTypes[i].propertyFlags & req_flags) != req_flags))
            जारी;

        /* Found a suitable memory type */
        सूचकांक = i;
        अवरोध;
    }

    अगर (सूचकांक < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        वापस AVERROR(EINVAL);
    }

    alloc_info.memory_Type_सूचकांक = सूचकांक;

    ret = vk->AllocateMemory(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    अगर (ret != VK_SUCCESS)
        वापस AVERROR(ENOMEM);

    अगर (mem_flags)
        *mem_flags |= s->mprops.memoryTypes[सूचकांक].propertyFlags;

    वापस 0;
}

पूर्णांक ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       पूर्णांक width, पूर्णांक height, VkFormat format, पूर्णांक nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, व्योम *create_pnext)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMemoryPropertyFlagBits mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_अग्र         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { width, height, 1 },
        .mipLevels     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_गिनती_1_BIT,
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
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->GetImageMemoryRequirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.memoryRequirements,
                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    अगर (err < 0)
        जाओ fail;

    bind_info.image  = *img;
    bind_info.memory = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        जाओ fail;
    }

    वापस 0;

fail:
    ff_vk_image_free(s, img, mem);
    वापस err;
}

व्योम ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    अगर (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    अगर (*mem) {
        vk->FreeMemory(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

पूर्णांक ff_vk_create_buf(FFVulkanContext *s, FFVk_बफर *buf, माप_प्रकार आकार,
                     व्योम *p_अग्र, व्योम *alloc_p_अग्र,
                     Vk_बफर_Usage_Flags usage, VkMemoryPropertyFlagBits flags)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    पूर्णांक use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_बफर_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_बफर_CREATE_INFO,
        .p_अग्र       = p_अग्र,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .आकार        = flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ?
                       FFALIGN(आकार, s->props.properties.limits.minMemoryMapAlignment) :
                       आकार,
    };

    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    Vk_बफर_Memory_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_बफर_MEMORY_REQUIREMENTS_INFO_2,
    };
    VkMemoryDedicatedAllocateInfo ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
        .p_अग्र = alloc_p_अग्र,
    };
    VkMemoryDedicatedRequirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
    };
    VkMemoryRequirements2 req = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
        .p_अग्र = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           आकार, usage, flags);

    ret = vk->Create_बफर(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    req_desc.बफर = buf->buf;

    vk->Get_बफर_Memory_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefersDedicatedAllocation |
                  ded_req.requiresDedicatedAllocation;
    अगर (use_ded_mem) {
        ded_alloc.बफर = buf->buf;
        ded_alloc.p_अग्र = alloc_p_अग्र;
        alloc_p_अग्र = &ded_alloc;
    }

    अगर (usage & VK_बफर_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags.p_अग्र = alloc_p_अग्र;
        alloc_p_अग्र = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.memoryRequirements, flags, alloc_p_अग्र,
                          &buf->flags, &buf->mem);
    अगर (err)
        वापस err;

    ret = vk->Bind_बफर_Memory(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    अगर (usage & VK_बफर_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        Vk_बफर_Device_Address_Info address_info = {
            .sType = VK_STRUCTURE_TYPE_बफर_DEVICE_ADDRESS_INFO,
            .बफर = buf->buf,
        };
        buf->address = vk->Get_बफर_Device_Address(s->hwctx->act_dev, &address_info);
    }

    buf->आकार = आकार;

    वापस 0;
}

पूर्णांक ff_vk_map_buffers(FFVulkanContext *s, FFVk_बफर **buf, uint8_t *mem[],
                      पूर्णांक nb_buffers, पूर्णांक invalidate)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange inval_list[64];
    पूर्णांक inval_गिनती = 0;

    क्रम (पूर्णांक i = 0; i < nb_buffers; i++) {
        व्योम *dst;
        ret = vk->MapMemory(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_WHOLE_आकार, 0, &dst);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        अगर (mem)
            mem[i] = dst;
    }

    अगर (!invalidate)
        वापस 0;

    क्रम (पूर्णांक i = 0; i < nb_buffers; i++) {
        स्थिर VkMappedMemoryRange ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            .memory = buf[i]->mem,
            .आकार   = VK_WHOLE_आकार,
        };
        अगर (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            जारी;
        inval_list[inval_गिनती++] = ival_buf;
    }

    अगर (inval_गिनती) {
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, inval_गिनती,
                                               inval_list);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }
    }

    वापस 0;
}

पूर्णांक ff_vk_flush_बफर(FFVulkanContext *s, FFVk_बफर *buf,
                       Vk_Device_आकार offset, Vk_Device_आकार mem_आकार,
                       पूर्णांक flush)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    अगर (buf->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        वापस 0;

    स्थिर VkMappedMemoryRange flush_तथ्य = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .memory = buf->mem,
        .offset = offset,
        .आकार   = mem_आकार,
    };

    अगर (flush)
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_तथ्य);
    अन्यथा
        ret = vk->InvalidateMappedMemoryRanges(s->hwctx->act_dev, 1, &flush_तथ्य);

    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

पूर्णांक ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_बफर **buf, पूर्णांक nb_buffers,
                        पूर्णांक flush)
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkMappedMemoryRange flush_list[64];
    पूर्णांक flush_गिनती = 0;

    अगर (flush) {
        क्रम (पूर्णांक i = 0; i < nb_buffers; i++) {
            स्थिर VkMappedMemoryRange flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .memory = buf[i]->mem,
                .आकार   = VK_WHOLE_आकार,
            };

            av_assert0(!buf[i]->host_ref);
            अगर (buf[i]->flags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                जारी;
            flush_list[flush_गिनती++] = flush_buf;
        }
    }

    अगर (flush_गिनती) {
        ret = vk->FlushMappedMemoryRanges(s->hwctx->act_dev, flush_गिनती,
                                          flush_list);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    क्रम (पूर्णांक i = 0; i < nb_buffers; i++) {
        vk->UnmapMemory(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = शून्य;
    }

    वापस err;
}

व्योम ff_vk_free_buf(FFVulkanContext *s, FFVk_बफर *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    अगर (!buf || !s->hwctx)
        वापस;

    अगर (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_बफर(s, buf, 0);
    अगर (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_बफर(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    अगर (buf->mem != VK_NULL_HANDLE)
        vk->FreeMemory(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    अगर (buf->host_ref)
        av_बफर_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = शून्य;
}

अटल व्योम pooled_buf_free(AVRefStructOpaque opaque, व्योम *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णांक ff_vk_get_pooled_बफर(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_बफर **buf, Vk_बफर_Usage_Flags usage,
                            व्योम *create_p_अग्र, माप_प्रकार आकार,
                            VkMemoryPropertyFlagBits mem_props)
{
    पूर्णांक err;
    FFVk_बफर *तथ्य;

    अगर (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(माप(FFVk_बफर), 0, ctx,
                                                शून्य, शून्य, pooled_buf_free,
                                                शून्य);
        अगर (!(*buf_pool))
            वापस AVERROR(ENOMEM);
    }

    *buf = तथ्य = av_refstruct_pool_get(*buf_pool);
    अगर (!तथ्य)
        वापस AVERROR(ENOMEM);

    अगर (तथ्य->आकार >= आकार)
        वापस 0;

    ff_vk_free_buf(ctx, तथ्य);
    स_रखो(तथ्य, 0, माप(*तथ्य));

    err = ff_vk_create_buf(ctx, तथ्य, आकार,
                           create_p_अग्र, शून्य, usage,
                           mem_props);
    अगर (err < 0) {
        av_refstruct_unref(buf);
        वापस err;
    }

    अगर (mem_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_बफर(ctx, तथ्य, &तथ्य->mapped_mem, 0);
        अगर (err < 0) {
            av_refstruct_unref(buf);
            वापस err;
        }
    }

    वापस 0;
}

अटल पूर्णांक create_mapped_बफर(FFVulkanContext *s,
                                FFVk_बफर *vkb, Vk_बफर_Usage_Flags usage,
                                माप_प्रकार आकार,
                                Vk_External_Memory_बफर_Create_Info *create_desc,
                                VkImportMemoryHostPointerInfoEXT *import_desc,
                                VkMemoryHostPointerPropertiesEXT props)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_बफर_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_बफर_CREATE_INFO,
        .p_अग्र       = create_desc,
        .usage       = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .आकार        = आकार,
    };
    VkMemoryRequirements req = {
        .आकार           = आकार,
        .alignment      = s->hprops.minImportedHostPointerAlignment,
        .memoryTypeBits = props.memoryTypeBits,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                          import_desc, &vkb->flags, &vkb->mem);
    अगर (err < 0)
        वापस err;

    ret = vk->Create_बफर(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    अगर (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        वापस AVERROR_EXTERNAL;
    }

    ret = vk->Bind_बफर_Memory(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    अगर (ret != VK_SUCCESS) {
        vk->FreeMemory(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_बफर(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल व्योम host_map_free(AVRefStructOpaque opaque, व्योम *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णांक ff_vk_host_map_बफर(FFVulkanContext *s, FFVk_बफर **dst,
                          uint8_t *src_तथ्य, Vk_Device_आकार आकार,
                          स्थिर AVBufferRef *src_buf,
                          Vk_बफर_Usage_Flags usage)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_Memory_बफर_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_बफर_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
    };
    VkMemoryAllocateFlagsInfo alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    VkImportMemoryHostPointerInfoEXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT,
        .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT,
        .p_अग्र = usage & VK_बफर_USAGE_SHADER_DEVICE_ADDRESS_BIT ? &alloc_flags : शून्य,
    };
    VkMemoryHostPointerPropertiesEXT props;

    AVBufferRef *ref;
    FFVk_बफर *vkb;
    माप_प्रकार offs;
    माप_प्रकार बफर_आकार;

    *dst = शून्य;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_तथ्य % s->hprops.minImportedHostPointerAlignment;
    import_desc.pHostPointer = src_तथ्य - offs;

    props = (VkMemoryHostPointerPropertiesEXT) {
        VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT,
    };
    ret = vk->GetMemoryHostPointerPropertiesEXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.pHostPointer,
                                                &props);
    अगर (!(ret == VK_SUCCESS && props.memoryTypeBits))
        वापस AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_बफर_ref(src_buf);
    अगर (!ref)
        वापस AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    स्थिर Vk_Device_आकार src_avail = src_buf->आकार - (src_तथ्य - src_buf->तथ्य);
    बफर_आकार = offs + FFMIN(आकार, src_avail);
    बफर_आकार = FFALIGN(बफर_आकार, s->props.properties.limits.minMemoryMapAlignment);
    बफर_आकार = FFALIGN(बफर_आकार, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(माप(*vkb), 0, s, host_map_free);
    अगर (!vkb) {
        av_बफर_unref(&ref);
        वापस AVERROR(ENOMEM);
    }

    err = create_mapped_बफर(s, vkb, usage,
                               बफर_आकार, &create_desc, &import_desc,
                               props);
    अगर (err < 0) {
        av_बफर_unref(&ref);
        av_refstruct_unref(&vkb);
        वापस err;
    }

    अगर (usage & VK_बफर_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        Vk_बफर_Device_Address_Info address_info = {
            .sType = VK_STRUCTURE_TYPE_बफर_DEVICE_ADDRESS_INFO,
            .बफर = vkb->buf,
        };
        vkb->address = vk->Get_बफर_Device_Address(s->hwctx->act_dev, &address_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_offset = offs;
    vkb->address       += offs;
    vkb->mapped_mem     = src_तथ्य;
    vkb->आकार           = बफर_आकार - offs;

    *dst = vkb;

    वापस 0;
}

पूर्णांक ff_vk_shader_add_धकेलो_const(FFVulkanShader *shd, पूर्णांक offset, पूर्णांक आकार,
                                VkShaderStageFlagBits stage)
{
    Vk_धकेलो_Constant_Range *pc = &shd->धकेलो_consts[shd->धकेलो_consts_अंक++];
    av_assert1(shd->धकेलो_consts_अंक < FF_VK_MAX_धकेलो_CONSTS);
    pc->stageFlags = stage;
    pc->offset = offset;
    pc->आकार = आकार;
    वापस 0;
}

पूर्णांक ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       पूर्णांक unnorm_coords, VkFilter filt)
{
    Vk_परिणाम ret;
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
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, पूर्णांक p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    पूर्णांक nb_images = ff_vk_गिनती_images(vkf);
    पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);

    अटल स्थिर VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    अगर (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        वापस VK_IMAGE_ASPECT_COLOR_BIT;

    वापस plane_aspect[p];
}

पूर्णांक ff_vk_mt_is_np_rgb(क्रमागत AVPixelFormat pix_fmt)
{
    अगर (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        वापस 1;
    वापस 0;
}

व्योम ff_vk_set_perm(क्रमागत AVPixelFormat pix_fmt, पूर्णांक lut[4], पूर्णांक inv)
{
    चयन (pix_fmt) {
    हाल AV_PIX_FMT_GBRP:
    हाल AV_PIX_FMT_GBRAP:
    हाल AV_PIX_FMT_GBRAP10:
    हाल AV_PIX_FMT_GBRAP12:
    हाल AV_PIX_FMT_GBRAP14:
    हाल AV_PIX_FMT_GBRAP16:
    हाल AV_PIX_FMT_GBRAPF16:
    हाल AV_PIX_FMT_GBRP10:
    हाल AV_PIX_FMT_GBRP12:
    हाल AV_PIX_FMT_GBRP14:
    हाल AV_PIX_FMT_GBRP16:
    हाल AV_PIX_FMT_GBRPF16:
    हाल AV_PIX_FMT_GBRPF32:
    हाल AV_PIX_FMT_GBRAP32:
    हाल AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        अवरोध;
    हाल AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        अवरोध;
    हाल AV_PIX_FMT_BGRA:
    हाल AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        अवरोध;
    शेष:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        अवरोध;
    }

    अगर (inv) {
        पूर्णांक lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        क्रम (पूर्णांक i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    वापस;
}

स्थिर अक्षर *ff_vk_shader_rep_fmt(क्रमागत AVPixelFormat pix_fmt,
                                 क्रमागत FFVkShaderRepFormat rep_fmt)
{
    चयन (pix_fmt) {
    हाल AV_PIX_FMT_RGBA:
    हाल AV_PIX_FMT_BGRA:
    हाल AV_PIX_FMT_RGB24:
    हाल AV_PIX_FMT_BGR24:
    हाल AV_PIX_FMT_BGR0:
    हाल AV_PIX_FMT_RGB0:
    हाल AV_PIX_FMT_RGB565:
    हाल AV_PIX_FMT_BGR565:
    हाल AV_PIX_FMT_UYVA:
    हाल AV_PIX_FMT_YUYV422:
    हाल AV_PIX_FMT_UYVY422: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_X2RGB10:
    हाल AV_PIX_FMT_X2BGR10:
    हाल AV_PIX_FMT_Y210:
    हाल AV_PIX_FMT_XV30: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = शून्य,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_RGB48:
    हाल AV_PIX_FMT_RGBA64:
    हाल AV_PIX_FMT_Y212:
    हाल AV_PIX_FMT_Y216:
    हाल AV_PIX_FMT_XV36:
    हाल AV_PIX_FMT_XV48: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_RGBAF16: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_RGBF32:
    हाल AV_PIX_FMT_RGBAF32: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_RGB96:
    हाल AV_PIX_FMT_RGBA128: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = शून्य,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        वापस rep_tab[rep_fmt];
    }
    हाल AV_PIX_FMT_GBRP:
    हाल AV_PIX_FMT_GRAY8:
    हाल AV_PIX_FMT_GBRAP:
    हाल AV_PIX_FMT_YUV420P:
    हाल AV_PIX_FMT_YUV422P:
    हाल AV_PIX_FMT_YUV444P:
    हाल AV_PIX_FMT_YUVA420P:
    हाल AV_PIX_FMT_YUVA422P:
    हाल AV_PIX_FMT_YUVA444P: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_GRAY10:
    हाल AV_PIX_FMT_GRAY12:
    हाल AV_PIX_FMT_GRAY14:
    हाल AV_PIX_FMT_GRAY16:
    हाल AV_PIX_FMT_GBRAP10:
    हाल AV_PIX_FMT_GBRAP12:
    हाल AV_PIX_FMT_GBRAP14:
    हाल AV_PIX_FMT_GBRAP16:
    हाल AV_PIX_FMT_GBRAPF16:
    हाल AV_PIX_FMT_GBRP10:
    हाल AV_PIX_FMT_GBRP12:
    हाल AV_PIX_FMT_GBRP14:
    हाल AV_PIX_FMT_GBRP16:
    हाल AV_PIX_FMT_GBRPF16:
    हाल AV_PIX_FMT_XYZP12:
    हाल AV_PIX_FMT_YUV420P10:
    हाल AV_PIX_FMT_YUV420P12:
    हाल AV_PIX_FMT_YUV420P16:
    हाल AV_PIX_FMT_YUV422P10:
    हाल AV_PIX_FMT_YUV422P12:
    हाल AV_PIX_FMT_YUV422P16:
    हाल AV_PIX_FMT_YUV444P10:
    हाल AV_PIX_FMT_YUV444P12:
    हाल AV_PIX_FMT_YUV444P16:
    हाल AV_PIX_FMT_YUVA420P10:
    हाल AV_PIX_FMT_YUVA420P16:
    हाल AV_PIX_FMT_YUVA422P10:
    हाल AV_PIX_FMT_YUVA422P12:
    हाल AV_PIX_FMT_YUVA422P16:
    हाल AV_PIX_FMT_YUVA444P10:
    हाल AV_PIX_FMT_YUVA444P12:
    हाल AV_PIX_FMT_YUVA444P16:
    हाल AV_PIX_FMT_BAYER_RGGB16: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_GRAY32:
    हाल AV_PIX_FMT_GRAYF32:
    हाल AV_PIX_FMT_GBRPF32:
    हाल AV_PIX_FMT_GBRAPF32: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_GBRAP32: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = शून्य,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_NV12:
    हाल AV_PIX_FMT_NV16:
    हाल AV_PIX_FMT_NV24: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_P010:
    हाल AV_PIX_FMT_P210:
    हाल AV_PIX_FMT_P410: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = शून्य,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        वापस rep_tab[rep_fmt];
    };
    हाल AV_PIX_FMT_P012:
    हाल AV_PIX_FMT_P016:
    हाल AV_PIX_FMT_P212:
    हाल AV_PIX_FMT_P216:
    हाल AV_PIX_FMT_P412:
    हाल AV_PIX_FMT_P416: {
        स्थिर अक्षर *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        वापस rep_tab[rep_fmt];
    };
    शेष:
        वापस "rgba32f";
    }
}

अटल व्योम reset_imageviews(AVRefStructOpaque unused, व्योम *obj)
{
    FFVkImageViews *iv = obj;

    क्रम (पूर्णांक i = 0; i < iv->nb_views; i++) {
        अगर (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    स_रखो(iv->views, 0, माप(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, पूर्णांक nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_अंक_तथ्य_POINTERS);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    अगर (!iv)
        वापस शून्य;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    वापस iv;
}

VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, क्रमागत FFVkShaderRepFormat rep_fmt)
{
#घोषणा REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#घोषणा REPS_FMT_PACK(fmt, अंक) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## अंक, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## अंक, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## अंक, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## अंक,

    स्थिर VkFormat fmts_map[][4] = {
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
#अघोषित REPS_FMT_PACK
#अघोषित REPS_FMT

    अगर (fmt == VK_FORMAT_UNDEFINED)
        वापस VK_FORMAT_UNDEFINED;

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        अगर (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            वापस fmts_map[i][rep_fmt];
    }

    वापस VK_FORMAT_UNDEFINED;
}

पूर्णांक ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, पूर्णांक plane, क्रमागत FFVkShaderRepFormat rep_fmt)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    स्थिर VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_अग्र      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_to_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_identity_map,
        .subresourceRange = {
            .aspectMask = ff_vk_aspect_flag(f, plane),
            .level_गिनती = 1,
            .layer_गिनती = 1,
        },
    };
    अगर (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        वापस AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspectMask;

    वापस 0;
}

पूर्णांक ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अंक_तथ्य_POINTERS],
                                AVFrame *f,
                                स्थिर VkFormat fmts[AV_अंक_तथ्य_POINTERS])
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    AVVulkanFramesContext *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->तथ्य[0];
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(vkf);
    स्थिर पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_अंक_तथ्य_POINTERS] = { 0 };

    क्रम (पूर्णांक i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_अग्र      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_identity_map,
            .subresourceRange = {
                .aspectMask = ff_vk_aspect_flag(f, i),
                .level_गिनती = 1,
                .layer_गिनती = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    क्रम (पूर्णांक i = 0; i < nb_planes; i++)
        ff_vk_exec_add_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    स_नकल(views, tmp_views, nb_planes*माप(*views));

    वापस 0;

fail:
    क्रम (पूर्णांक i = 0; i < nb_planes; i++)
        अगर (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    वापस err;
}

पूर्णांक ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_अंक_तथ्य_POINTERS],
                            AVFrame *f, क्रमागत FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    स्थिर VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    स्थिर पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    VkFormat fmts[AV_अंक_तथ्य_POINTERS] = { 0 };

    क्रम (पूर्णांक i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_to_rep(rep_fmts[i], rep_fmt);
        अगर (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            वापस AVERROR(EINVAL);
        }
    }

    वापस ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

व्योम ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, पूर्णांक *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    पूर्णांक found = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->तथ्य[0];
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(vkf);
    क्रम (पूर्णांक i = 0; i < e->nb_frame_deps; i++)
        अगर (e->frame_deps[i]->तथ्य[0] == pic->तथ्य[0]) {
            अगर (e->frame_update[i])
                found = i;
            अवरोध;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (VkImageMemoryBarrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
            .p_अग्र = शून्य,
            .srcStageMask = src_stage,
            .dstStageMask = dst_stage,
            .srcAccessMask = found >= 0 ? e->access_dst[found] : VK_ACCESS_2_NONE,
            .dstAccessMask = new_access,
            .oldLayout = found >= 0 ? e->layout_dst[found] : vkf->layout[0],
            .newLayout = new_layout,
            .src_Queue_Family_सूचकांक = found >= 0 ? e->queue_family_dst[found] : vkf->queue_family[0],
            .dst_Queue_Family_सूचकांक = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .layer_गिनती = 1,
                .level_गिनती = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], शून्य);
}

पूर्णांक ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_आकार[3], uint32_t required_subgroup_आकार)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    स_नकल(shd->lg_आकार, wg_आकार, 3*माप(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_आकार_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_आकार_CREATE_INFO,
        .required_Subgroup_आकार = required_subgroup_आकार,
    };

    चयन (shd->stage) {
    हाल VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
    हाल VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    हाल VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
    हाल VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    हाल VK_SHADER_STAGE_MISS_BIT_KHR:
    हाल VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        अवरोध;
    हाल VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        अवरोध;
    शेष:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        अवरोध;
    };

    वापस 0;
}

अटल पूर्णांक init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pSetLayouts            = shd->desc_layout,
        .set_Layout_गिनती         = shd->nb_descriptor_sets,
        .धकेलो_Constant_Range_गिनती = shd->धकेलो_consts_अंक,
        .p_धकेलो_Constant_Ranges    = shd->धकेलो_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                स्थिर uint8_t *spirv, माप_प्रकार spirv_len)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_अग्र    = शून्य,
        .flags    = 0x0,
        .pCode    = (व्योम *)spirv,
        .code_आकार = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, स्थिर अक्षर *entrypoint)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_अग्र = shd->subgroup_info.required_Subgroup_आकार ?
                     &shd->subgroup_info : शून्य,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_आकार ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    अगर (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    पूर्णांक has_singular = 0;
    पूर्णांक max_descriptors = 0;
    क्रम (पूर्णांक i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_set[i].nb_bindings);
        अगर (shd->desc_set[i].singular)
            has_singular = 1;
    }
    shd->use_धकेलो = (s->extensions & FF_VK_EXT_धकेलो_DESCRIPTOR) &&
                    (max_descriptors <= s->धकेलो_desc_props.max_धकेलो_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    क्रम (पूर्णांक i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkanDescriptorSet *set = &shd->desc_set[i];
        VkDescriptorSetLayoutCreateInfo desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .binding_गिनती = set->nb_bindings,
            .pBindings = set->binding,
            .flags = (shd->use_धकेलो) ?
                     VK_DESCRIPTOR_SET_LAYOUT_CREATE_धकेलो_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->CreateDescriptorSetLayout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }
    }

    वापस 0;
}

पूर्णांक ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      स्थिर अक्षर *spirv, माप_प्रकार spirv_len,
                      स्थिर अक्षर *entrypoint)
{
    पूर्णांक err;
    FFVulkanFunctions *vk = &s->vkfn;
    VkSpecializationMapEntry spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    माप_प्रकार निवेश_आकार = spirv_len;

    अगर (shd->precompiled) {
        अगर (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_Entry_गिनती = 0,
                .p_तथ्य = shd->lg_आकार,
                .तथ्य_आकार_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        VkSpecializationMapEntry *spe = (व्योम *)shd->specialization_info->pMapEntries;
        क्रम (पूर्णांक i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_Entry_गिनती++] = (VkSpecializationMapEntry) {
                .constantID = 253 + i,
                .offset = shd->specialization_info->तथ्य_आकार_2 + i*माप(uint32_t),
                .आकार = माप(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_तथ्य;
        स_नकल(&spd[shd->specialization_info->तथ्य_आकार_2],
               shd->lg_आकार, 3*माप(uint32_t));
        shd->specialization_info->तथ्य_आकार_2 += 3*माप(uint32_t);

#अगर CONFIG_SHADER_COMPRESSION
        uint8_t *out;
        माप_प्रकार out_len;
        पूर्णांक ret = ff_zlib_expand(s, &out, &out_len, spirv, spirv_len);
        अगर (ret < 0)
            वापस ret;
        spirv = out;
        spirv_len = out_len;
#पूर्ण_अगर
    }

    err = init_descriptors(s, shd);
    अगर (err < 0)
        जाओ end;

    err = init_pipeline_layout(s, shd);
    अगर (err < 0)
        जाओ end;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    अगर (err < 0)
        जाओ end;

    चयन (shd->bind_point) {
    हाल VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        अवरोध;
    शेष:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        जाओ end;
        अवरोध;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    अगर (err < 0)
        जाओ end;

    अगर (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    अन्यथा
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    अगर (निवेश_आकार != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", निवेश_आकार);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

end:
    अगर (shd->precompiled) {
        shd->specialization_info->map_Entry_गिनती -= 3;
        shd->specialization_info->तथ्य_आकार_2 -= 3*माप(uint32_t);
    }
#अगर CONFIG_SHADER_COMPRESSION
    अगर (shd->precompiled)
        av_free((व्योम *)spirv);
#पूर्ण_अगर
    वापस err;
}

व्योम ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     स्थिर FFVulkanDescriptorSetBinding *desc, पूर्णांक nb,
                                     पूर्णांक singular)
{
    FFVulkanDescriptorSet *set = &shd->desc_set[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    क्रम (पूर्णांक i = 0; i < nb; i++) {
        set->binding[i].binding            = i;
        set->binding[i].descriptorType     = desc[i].type;
        set->binding[i].descriptor_गिनती    = FFMAX(desc[i].elems, 1);
        set->binding[i].stageFlags         = desc[i].stages;
        set->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    क्रम (पूर्णांक i = 0; i < nb; i++) {
        पूर्णांक j;
        क्रम (j = 0; j < shd->nb_desc_pool_आकार; j++)
            अगर (shd->desc_pool_आकार[j].type == desc[i].type)
                अवरोध;
        अगर (j >= shd->nb_desc_pool_आकार) {
            shd->nb_desc_pool_आकार++;
            av_assert1(shd->nb_desc_pool_आकार < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_आकार[j].type             = desc[i].type;
        shd->desc_pool_आकार[j].descriptor_गिनती += FFMAX(desc[i].elems, 1);
    }

    set->singular = singular;
    set->nb_bindings = nb;
}

पूर्णांक ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    अगर (!shd->nb_descriptor_sets)
        वापस 0;

    FFVulkan_Shader_तथ्य *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    अगर (!shd->use_धकेलो) {
        Vk_परिणाम ret;
        FFVulkanFunctions *vk = &s->vkfn;
        VkDescriptorSetLayout *tmp_layouts;
        VkDescriptorSetAllocateInfo set_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        क्रम (पूर्णांक i = 0; i < shd->nb_desc_pool_आकार; i++)
            shd->desc_pool_आकार[i].descriptor_गिनती *= pool->pool_आकार;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_आकार,
            .pool_आकार_गिनती = shd->nb_desc_pool_आकार,
            .maxSets = sd->nb_descriptor_sets*pool->pool_आकार,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, माप(*tmp_layouts));
        अगर (!tmp_layouts)
            वापस AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        क्रम (पूर्णांक i = 0; i < pool->pool_आकार; i++)
            क्रम (पूर्णांक j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        set_alloc_info = (VkDescriptorSetAllocateInfo) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .pSetLayouts        = tmp_layouts,
            .descriptor_Set_गिनती = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        माप(*tmp_layouts));
        अगर (!sd->desc_sets) {
            av_free(tmp_layouts);
            वापस AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &set_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        अगर (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            वापस AVERROR_EXTERNAL;
        }
    }

    वापस 0;
}

अटल अंतरभूत स्थिर FFVulkan_Shader_तथ्य *get_shd_तथ्य(FFVkExecContext *e,
                                                     स्थिर FFVulkanShader *shd)
{
    क्रम (पूर्णांक i = 0; i < e->parent->nb_reg_shd; i++)
        अगर (e->parent->reg_shd[i].shd == shd)
            वापस &e->parent->reg_shd[i];
    वापस शून्य;
}

अटल अंतरभूत व्योम update_set_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, पूर्णांक set,
                                         VkWriteDescriptorSet *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];
    स्थिर FFVulkan_Shader_तथ्य *sd = get_shd_तथ्य(e, shd);

    अगर (desc_set->singular) {
        क्रम (पूर्णांक i = 0; i < e->parent->pool_आकार; i++) {
            write_info->dstSet = sd->desc_sets[i*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, शून्य);
        }
    } अन्यथा {
        अगर (shd->use_धकेलो) {
            vk->Cmd_धकेलो_Descriptor_Set_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        set, 1,
                                        write_info);
        } अन्यथा {
            write_info->dstSet = sd->desc_sets[e->idx*sd->nb_descriptor_sets + set];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, शून्य);
        }
    }
}

पूर्णांक ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णांक set, पूर्णांक bind, पूर्णांक offs,
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
        .descriptor_गिनती = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    वापस 0;
}

व्योम ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णांक set, पूर्णांक binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_frames_ctx->तथ्य;
    स्थिर पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);

    क्रम (पूर्णांक i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, set, binding, i,
                                views[i], layout, sampler);
}

पूर्णांक ff_vk_shader_update_desc_बफर(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णांक set, पूर्णांक bind, पूर्णांक elem,
                                    FFVk_बफर *buf, Vk_Device_आकार offset, Vk_Device_आकार len,
                                    VkFormat fmt)
{
    FFVulkanDescriptorSet *desc_set = &shd->desc_set[set];

    Vk_Descriptor_बफर_Info desc_pool_write_info_buf = {
        .बफर = buf->buf,
        .offset = buf->virtual_offset + offset,
        .range = len,
    };
    VkWriteDescriptorSet desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstBinding = bind,
        .descriptor_गिनती = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_set->binding[bind].descriptorType,
        .p_बफर_Info = &desc_pool_write_info_buf,
    };
    update_set_pool_write(s, e, shd, set, &desc_pool_write_info);

    वापस 0;
}

व्योम ff_vk_shader_update_धकेलो_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    पूर्णांक offset, माप_प्रकार आकार, व्योम *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_धकेलो_Constants(e->buf, shd->pipeline_layout,
                         stage, offset, आकार, src);
}

व्योम ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            स्थिर FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    स्थिर FFVulkan_Shader_तथ्य *sd = get_shd_तथ्य(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    अगर (sd && sd->nb_descriptor_sets) {
        अगर (!shd->use_धकेलो) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_point, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, शून्य);
        }
    }
}

व्योम ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#अगर 0
    अगर (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#पूर्ण_अगर

    अगर (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    अगर (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    क्रम (पूर्णांक i = 0; i < shd->nb_descriptor_sets; i++)
        अगर (shd->desc_layout[i])
            vk->DestroyDescriptorSetLayout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

व्योम ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#अगर_घोषित VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#पूर्ण_अगर
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_बफर_unref(&s->device_ref);
    av_बफर_unref(&s->frames_ref);
}

पूर्णांक ff_vk_init(FFVulkanContext *s, व्योम *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref)
{
    पूर्णांक err;

    अटल स्थिर AVClass vulkan_context_class = {
        .class_name       = "vk",
        .version          = LIBAVUTIL_VERSION_INT,
        .parent_log_context_offset = दुरत्व(FFVulkanContext, log_parent),
    };

    स_रखो(s, 0, माप(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    अगर (frames_ref) {
        s->frames_ref = av_बफर_ref(frames_ref);
        अगर (!s->frames_ref)
            वापस AVERROR(ENOMEM);

        s->frames = (AVHWFramesContext *)s->frames_ref->तथ्य;
        s->hwfc = s->frames->hwctx;

        device_ref = s->frames->device_ref;
    }

    s->device_ref = av_बफर_ref(device_ref);
    अगर (!s->device_ref) {
        ff_vk_uninit(s);
        वापस AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->तथ्य;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_to_mask(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_to_mask(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_load_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    अगर (err < 0) {
        ff_vk_uninit(s);
        वापस err;
    }

    err = ff_vk_load_props(s);
    अगर (err < 0) {
        ff_vk_uninit(s);
        वापस err;
    }

    वापस 0;
}
