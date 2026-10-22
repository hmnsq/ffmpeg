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
#यदि_अन्तः

ध्रुव VkComponentMapping ff_comp_तटस्थः_map = {
    .r = VK_COMPONENT_SWIZZLE_तटस्थः,
    .g = VK_COMPONENT_SWIZZLE_तटस्थः,
    .b = VK_COMPONENT_SWIZZLE_तटस्थः,
    .a = VK_COMPONENT_SWIZZLE_तटस्थः,
};

/* Converts return values to strings */
ध्रुव वर्ण *ff_vk_ret2str(Vk_परिणाम res)
{
#परिभाषय CASE(VAL) पक्ष VAL: प्रत्यागम #VAL
    विकल्प (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_समुच्चयः);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_बहिर्गमनम्_सम्बन्धि_HOST_स्मृतिः);
    CASE(VK_ERROR_बहिर्गमनम्_सम्बन्धि_DEVICE_स्मृतिः);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_नष्टम्);
    CASE(VK_ERROR_स्मृतिः_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_बहिर्गमनम्_सम्बन्धि_POOL_स्मृतिः);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_स्थानाङ्कः);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_नष्टम्_KHR);
    CASE(VK_ERROR_NATIVE_गवाक्षः_अन्तर्_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_बहिर्गमनम्_सम्बन्धि_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_संस्करणम्_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_पूर्णम्_SCREEN_EXCLUSIVE_बहुलकम्_नष्टम्_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_समाप्तम्_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    स्वभाव: प्रत्यागम "Unknown error";
    }
#अपरिभाषय CASE
}

/* Malitia pura, Khronos */
#परिभाषय FN_MAP_गन्तव्यम्(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## गन्तव्यम्_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT,                   \
               VK_IMAGE_USAGE_SAMPLED_BIT);                             \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_BIT);                        \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_BIT);                        \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT,                   \
               VK_IMAGE_USAGE_STORAGE_BIT);                             \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_BIT,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);                    \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_BIT_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR);                \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_BIT_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR);                \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_BIT_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR);                \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_निवेशः_BIT_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR);                \
        MAP_गन्तव्यम्(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT);                   \
        प्रत्यागम dst;                                                     \
    }

#परिभाषय MAP_गन्तव्यम्(flag1, flag2) यदि (src & flag2) dst |= flag1;
FN_MAP_गन्तव्यम्(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#अपरिभाषय MAP_गन्तव्यम्
#परिभाषय MAP_गन्तव्यम्(flag1, flag2) यदि (src & flag1) dst |= flag2;
FN_MAP_गन्तव्यम्(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#अपरिभाषय MAP_गन्तव्यम्
#अपरिभाषय FN_MAP_गन्तव्यम्

स्थिर शून्य आरोपय_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    प्रति (पूर्णाङ्क i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        पूर्णाङ्क skip = 0;
        प्रति (पूर्णाङ्क j = 0; j < s->nb_qfs; j++) {
            यदि (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                भङ्ग;
            }
        }
        यदि (skip)
            अनुवर्त;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

स्थिर शून्य reset_imageviews(AVRefStructOpaque अप्रयुक्तम्, शून्य *obj);

पूर्णाङ्क ff_vk_आरोपय_props(FFVulkanContext *s)
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

    FF_VK_STRUCT_EXT(s, &s->props, &s->प्रक्षिप_desc_props, FF_VK_EXT_प्रक्षिप_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_प्रक्षिप_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_स्मृतिः,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_स्मृतिः_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_matrix_props, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_सदिशम्_props, FF_VK_EXT_LONG_सदिशम्,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_सदिशम्_PROPERTIES_EXT);
#यदि_अन्तः

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#यदि_अन्तः

    यदि (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(परिमाण(FFVkImageViews), 0,
                                                         रिक्त, रिक्त, reset_imageviews,
                                                         रिक्त, रिक्त);
        यदि (!s->imageviews_pool)
            प्रत्यागम AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(परिमाण(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_गणनम् = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_गणनम् = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    यदि (s->host_image_props.copy_Src_Layout_गणनम् == 512 ||
        s->host_image_props.copy_Dst_Layout_गणनम् == 512) {
        VkImageLayout *new_array;
        size_t new_आकार;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = रिक्त;
        s->host_image_props.copy_Src_Layout_गणनम् =
        s->host_image_props.copy_Dst_Layout_गणनम् = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_आकार = s->host_image_props.copy_Src_Layout_गणनम् +
                   s->host_image_props.copy_Dst_Layout_गणनम्;
        new_आकार *= परिमाण(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_आकार);
        यदि (!new_array)
            प्रत्यागम AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_गणनम्;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_स्मृतिः_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    प्रति (पूर्णाङ्क i = 0; i < s->mprops.स्मृतिः_Type_गणनम्; i++)
        s->host_cached_flag |= s->mprops.स्मृतिः_Types[i].propertyFlags &
                               VK_स्मृतिः_PROPERTY_HOST_CACHED_BIT;

    आरोपय_enabled_qfs(s);

    यदि (s->qf_props)
        प्रत्यागम 0;

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, रिक्त);

    s->qf_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->qf_props));
    यदि (!s->qf_props)
        प्रत्यागम AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->query_props));
    यदि (!s->qf_props) {
        av_freep(&s->qf_props);
        प्रत्यागम AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->video_props));
    यदि (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        प्रत्यागम AVERROR(ENOMEM);
    }

#यदि_परिभाषितम् VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, परिमाण(*s->ownership_props));
    यदि (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        प्रत्यागम AVERROR(ENOMEM);
    }
#यदि_अन्तः

    प्रति (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_परिणाम_स्थितिः_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_QUEUE,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR);
#यदि_परिभाषितम् VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_QUEUE_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#यदि_अन्तः
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    यदि (s->extensions & FF_VK_EXT_COOP_MATRIX) {
        vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, रिक्त);

        यदि (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                परिमाण(VkCooperativeMatrixPropertiesKHR));
            प्रति (पूर्णाङ्क i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (VkCooperativeMatrixPropertiesKHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR,
                };
            }

            vk->GetPhysicalDeviceCooperativeMatrixPropertiesKHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    प्रत्यागम 0;
}

AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         Vk_Queue_Flag_द्वयङ्काः dev_family,
                                         Vk_Video_Codec_Operation_Flag_द्वयङ्काः_KHR vid_ops)
{
    प्रति (पूर्णाङ्क i = 0; i < s->hwctx->nb_qf; i++) {
        यदि ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            प्रत्यागम &s->hwctx->qf[i];
        }
    }
    प्रत्यागम रिक्त;
}

स्थिर शून्य exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

शून्य ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        यदि (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_गणनम् = 1,
                .pSemaphores = &e->sem,
                .p_मानानि = &e->sem_मानम्,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->तालकम्);
    }

    /* Free shader-specific data */
    प्रति (पूर्णाङ्क i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_दत्त *sd = &pool->reg_shd[i];

        यदि (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++) {
        यदि (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        यदि (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    यदि (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_दत्त);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_आकार = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
स्थिर atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)रिक्त)->qf)];
स्थिर AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

स्थिर शून्य exec_pool_phase_बीजम्(शून्य)
{
    uint32_t बीजम् = av_get_random_बीजम्();
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], बीजम्, memory_order_relaxed);
}

पूर्णाङ्क ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, पूर्णाङ्क nb_contexts,
                         पूर्णाङ्क nb_queries, VkQueryType query_type, पूर्णाङ्क query_64bit,
                         ध्रुव शून्य *query_create_pnext)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_बफर_Allocate_Info cbuf_create;

    ध्रुव VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = रिक्त;

    atomic_init(&pool->idx, 0);

    यदि (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_find_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        यदि (!ef)
            प्रत्यागम AVERROR(EINVAL);
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

    प्रति (पूर्णाङ्क i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_बफर_BIT,
            .queue_Family_सूचकांक   = qf->idx,
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
        cbuf_create = (Vk_Command_बफर_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_बफर_ALLOCATE_INFO,
            .level              = VK_COMMAND_बफर_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_बफर_गणनम् = 1,
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
            .p_अग्र = query_create_pnext,
            .queryType = query_type,
            .query_गणनम् = nb_queries*nb_contexts,
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
        pool->query_स्थितिः_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        यदि (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            पूर्णाङ्क nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_स्थितिः_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } अन्यथा यदि (query_type == VK_QUERY_TYPE_परिणाम_स्थितिः_ONLY_KHR) {
            pool->query_स्थितिः_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_आकार = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_दत्त = av_calloc(nb_contexts, pool->qd_आकार);
        यदि (!pool->query_दत्त) {
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

    pool->pool_आकार = nb_contexts;

    प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++)
        pthread_mutex_init(&pool->contexts[i].तालकम्, रिक्त);

#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    पूर्णाङ्क आन्तरिकम्_queue_sync = 0;
    यदि (s->extensions & FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC) {
        ध्रुव VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_find_struct(s->hwctx->device_features.p_अग्र,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        आन्तरिकम्_queue_sync = iqs && iqs->internallySynchronizedQueues;
    }
#यदि_अन्तः

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_बीजम्);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    पूर्णाङ्क pin_queue = qf->flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                 VK_QUEUE_VIDEO_ENCODE_BIT_KHR);

    /* Init contexts */
    प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++) {
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
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->parent = pool;

        /* Query data */
        e->query_दत्त = ((uint8_t *)pool->query_दत्त) + pool->qd_आकार*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_queue ? phase % qf->अङ्कः : (i + phase) % qf->अङ्कः;
        e->qf = qf->idx;
        VkDeviceQueueInfo2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
            .flags            = आन्तरिकम्_queue_sync ?
                                VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR : 0,
#यदि_अन्तः
            .queue_Family_सूचकांक = qf->idx,
            .queue_सूचकांक       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->queue);
    }

    प्रत्यागम 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    प्रत्यागम err;
}

Vk_परिणाम ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              शून्य **दत्त, Vk_Query_परिणाम_Flag_द्वयङ्काः flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ध्रुव FFVkExecPool *pool = e->parent;
    Vk_Query_परिणाम_Flags qf = flags & ~(VK_QUERY_परिणाम_64_BIT |
                                      VK_QUERY_परिणाम_WITH_स्थितिः_BIT_KHR);

    यदि (!e->query_दत्त) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        प्रत्यागम VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_परिणाम_64_BIT : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_परिणाम_WITH_स्थितिः_BIT_KHR : 0x0;

    यदि (दत्त)
        *दत्त = e->query_दत्त;

    प्रत्यागम vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_आकार, e->query_दत्त,
                                   pool->qd_आकार, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        यदि (pthread_mutex_trylock(&e->तालकम्))
            अनुवर्त; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        यदि (vk->Get_Semaphore_गणक_मानम्(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_मानम् &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_frame_deps || e->nb_sw_frame_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->तालकम्);
    }

    प्रत्यागम &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_आकार];
}

शून्य ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गणनम् = 1,
        .pSemaphores = &e->sem,
        .p_मानानि = &e->sem_मानम्,
    };
    pthread_mutex_तालकम्(&e->तालकम्);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->तालकम्);
}

पूर्णाङ्क ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ध्रुव FFVkExecPool *pool = e->parent;

    Vk_Command_बफर_Begin_Info cmd_start = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_बफर_BEGIN_INFO,
        .flags = VK_COMMAND_बफर_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_गणनम् = 1,
        .pSemaphores = &e->sem,
        .p_मानानि = &e->sem_मानम्,
    };

    pthread_mutex_तालकम्(&e->तालकम्);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_बफर(e->buf, &cmd_start);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->तालकम्);
        प्रत्यागम AVERROR_EXTERNAL;
    }

    यदि (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_मानम्++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .मानम् = e->sem_मानम्,
        .stage_आवरणम् = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    pthread_mutex_unlock(&e->तालकम्);

    प्रत्यागम 0;
}

स्थिर शून्य exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    प्रति (पूर्णाङ्क j = 0; j < e->nb_buf_deps; j++)
        av_बफर_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    प्रति (पूर्णाङ्क j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    प्रति (पूर्णाङ्क j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        विकल्प (od->type) {
        पक्ष VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            भङ्ग;
        पक्ष VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            भङ्ग;
        स्वभाव:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    प्रति (पूर्णाङ्क j = 0; j < e->nb_sw_frame_deps; j++)
        av_frame_free(&e->sw_frame_deps[j]);
    e->nb_sw_frame_deps = 0;

    प्रति (पूर्णाङ्क j = 0; j < e->nb_frame_deps; j++) {
        AVFrame *f = e->frame_deps[j];
        यदि (e->frame_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
            AVVulkan_चौकटाः_Context *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];
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
        .मानम् = e->sem_मानम्,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_बफर(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

शून्य ff_vk_exec_सङ्कलय_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
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

    प्रति (पूर्णाङ्क i = 0; i < e->nb_refstruct_deps; i++) {
        यदि (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            प्रत्यागम;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = रिक्त;
}

शून्य ff_vk_exec_सङ्कलय_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

पूर्णाङ्क ff_vk_exec_सङ्कलय_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_frame_deps < FF_VK_EXEC_MAX_SW_FRAME_DEPS);

    e->sw_frame_deps[e->nb_sw_frame_deps] = av_frame_clone(f);
    यदि (!e->sw_frame_deps[e->nb_sw_frame_deps])
        प्रत्यागम AVERROR(ENOMEM);

    e->nb_sw_frame_deps++;

    प्रत्यागम 0;
}

शून्य ff_vk_exec_सङ्कलय_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मानम् = val,
        .stage_आवरणम् = stage,
    };
}

शून्य ff_vk_exec_सङ्कलय_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .मानम् = val,
        .stage_आवरणम् = stage,
    };
}

शून्य ff_vk_exec_सङ्कलय_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णाङ्क nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णाङ्क प्रतीक्षस्व)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    यदि (!प्रतीक्षस्व) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        प्रति (पूर्णाङ्क i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_आवरणम् = stage,
            };
        }

        प्रत्यागम;
    }

    /* Ownership of each semaphore passes to the execution */
    प्रति (पूर्णाङ्क i = 0; i < nb; i++) {
        ff_vk_exec_सङ्कलय_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_सङ्कलय_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

पूर्णाङ्क ff_vk_exec_सङ्कलय_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    AVVulkan_चौकटाः_Context *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];
    पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);

    /* Don't add duplicates */
    प्रति (पूर्णाङ्क i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->दत्त[0] == f->दत्त[0])
            प्रत्यागम 1;

    av_assert1(e->nb_frame_deps < FF_VK_EXEC_MAX_FRAME_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    यदि (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_बफर_ref(f->buf[0]);
        यदि (!e->buf_deps[e->nb_buf_deps])
            प्रत्यागम AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->frame_deps[e->nb_frame_deps] = f;

    vkfc->तालकम्_frame(hwfc, vkf);
    e->frame_locked[e->nb_frame_deps] = 1;
    e->frame_update[e->nb_frame_deps] = 0;
    e->nb_frame_deps++;

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मानम् = vkf->sem_मानम्[i],
            .stage_आवरणम् = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .मानम् = vkf->sem_मानम्[i] + 1,
            .stage_आवरणम् = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_मानम्[i];
        e->sem_sig_val_dst_cnt++;
    }

    प्रत्यागम 0;
}

शून्य ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_स्मृतिः_Barrier2 *bar, uint32_t *nb_img_bar)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->दत्त[0] == f->दत्त[0])
            भङ्ग;
    av_assert0(i < e->nb_frame_deps);

    /* Don't update duplicates */
    यदि (nb_img_bar && !e->frame_update[i])
        (*nb_img_bar)++;

    e->queue_family_dst[i] = bar->dst_Queue_Family_सूचकांक;
    e->access_dst[i] = bar->dst_Access_आवरणम्;
    e->layout_dst[i] = bar->newLayout;
    e->frame_update[i] = 1;
}

पूर्णाङ्क ff_vk_exec_mirror_sem_मानम्(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];

    /* Reject unknown frames */
    पूर्णाङ्क i;
    प्रति (i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->दत्त[0] == f->दत्त[0])
            भङ्ग;
    यदि (i == e->nb_frame_deps)
        प्रत्यागम AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_मानम्[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
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
        .command_बफर_Info_गणनम् = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_गणनम् = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_गणनम् = e->sem_sig_cnt,
    };

    ret = vk->अन्तः_Command_बफर(e->buf);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        प्रत्यागम AVERROR_EXTERNAL;
    }

#यदि FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->तालकम्_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#यदि_अन्तः
    ret = vk->QueueSubmit2(e->queue, 1, &submit_info, VK_NULL_HANDLE);
#यदि FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_queue(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#यदि_अन्तः

    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रति (पूर्णाङ्क i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    प्रति (पूर्णाङ्क j = 0; j < e->nb_frame_deps; j++) {
        यदि (e->frame_locked[j]) {
            AVFrame *f = e->frame_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
            AVVulkan_चौकटाः_Context *vkfc = hwfc->hwctx;
            AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];

            यदि (e->frame_update[j]) {
                पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);
                प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
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

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_alloc_mem(FFVulkanContext *s, Vk_स्मृतिः_Requirements *req,
                    Vk_स्मृतिः_Property_Flag_द्वयङ्काः req_flags, शून्य *alloc_extension,
                    Vk_स्मृतिः_Property_Flag_द्वयङ्काः *mem_flags, Vk_Device_स्मृतिः *mem)
{
    Vk_परिणाम ret;
    पूर्णाङ्क सूचकांक = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_स्मृतिः_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_स्मृतिः_ALLOCATE_INFO,
        .p_अग्र           = alloc_extension,
    };

    alloc_info.आवण्टनम्_आकार = req->आकार;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    प्रति (पूर्णाङ्क i = 0; i < s->mprops.स्मृतिः_Type_गणनम्; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        यदि (!(req->स्मृतिः_Type_द्वयङ्काः & (1 << i)))
            अनुवर्त;

        /* The memory type flags must include our properties */
        यदि ((req_flags != UINT32_MAX) &&
            ((s->mprops.स्मृतिः_Types[i].propertyFlags & req_flags) != req_flags))
            अनुवर्त;

        /* Found a suitable memory type */
        सूचकांक = i;
        भङ्ग;
    }

    यदि (सूचकांक < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        प्रत्यागम AVERROR(EINVAL);
    }

    alloc_info.स्मृतिः_Type_सूचकांक = सूचकांक;

    ret = vk->Allocate_स्मृतिः(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    यदि (ret != VK_SUCCESS)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (mem_flags)
        *mem_flags |= s->mprops.स्मृतिः_Types[सूचकांक].propertyFlags;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_स्मृतिः *mem,
                       पूर्णाङ्क विस्तारः, पूर्णाङ्क height, VkFormat format, पूर्णाङ्क nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, शून्य *create_pnext)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_स्मृतिः_Property_Flag_द्वयङ्काः mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_अग्र         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { विस्तारः, height, 1 },
        .mip_स्तराः     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_गणनम्_1_BIT,
        .sharing_बहुलकम्   = VK_SHARING_बहुलकम्_EXCLUSIVE,
    };
    Vk_स्मृतिः_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_ALLOCATE_INFO,
    };
    Vk_स्मृतिः_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_REQUIREMENTS_2,
    };
    Vk_Image_स्मृतिः_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_स्मृतिः_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_स्मृतिः_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_स्मृतिः_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_स्मृतिः_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.स्मृतिः_Requirements,
                          VK_स्मृतिः_PROPERTY_DEVICE_LOCAL_BIT,
                          &ded_alloc, &mem_flags, mem);
    यदि (err < 0)
        गच्छ fail;

    bind_info.image  = *img;
    bind_info.स्मृतिः = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        गच्छ fail;
    }

    प्रत्यागम 0;

fail:
    ff_vk_image_free(s, img, mem);
    प्रत्यागम err;
}

शून्य ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_स्मृतिः *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    यदि (*mem) {
        vk->Free_स्मृतिः(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

पूर्णाङ्क ff_vk_create_buf(FFVulkanContext *s, FFVk_बफर *buf, size_t आकार,
                     शून्य *p_अग्र, शून्य *alloc_p_अग्र,
                     Vk_बफर_Usage_Flags usage, Vk_स्मृतिः_Property_Flag_द्वयङ्काः flags)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    पूर्णाङ्क use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_बफर_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_बफर_CREATE_INFO,
        .p_अग्र       = p_अग्र,
        .usage       = usage,
        .sharing_बहुलकम् = VK_SHARING_बहुलकम्_EXCLUSIVE,
        .आकार        = flags & VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT ?
                       FFALIGN(आकार, s->props.properties.limits.min_स्मृतिः_Map_Alignment) :
                       आकार,
    };

    Vk_स्मृतिः_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_ALLOCATE_FLAGS_INFO,
        .flags = VK_स्मृतिः_ALLOCATE_DEVICE_स्थानाङ्कः_BIT,
    };
    Vk_बफर_स्मृतिः_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_बफर_स्मृतिः_REQUIREMENTS_INFO_2,
    };
    Vk_स्मृतिः_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_ALLOCATE_INFO,
        .p_अग्र = alloc_p_अग्र,
    };
    Vk_स्मृतिः_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_REQUIREMENTS,
    };
    Vk_स्मृतिः_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_REQUIREMENTS_2,
        .p_अग्र = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           आकार, usage, flags);

    ret = vk->Create_बफर(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    req_desc.बफर = buf->buf;

    vk->Get_बफर_स्मृतिः_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_आवण्टनम् |
                  ded_req.requires_Dedicated_आवण्टनम्;
    यदि (use_ded_mem) {
        ded_alloc.बफर = buf->buf;
        ded_alloc.p_अग्र = alloc_p_अग्र;
        alloc_p_अग्र = &ded_alloc;
    }

    यदि (usage & VK_बफर_USAGE_SHADER_DEVICE_स्थानाङ्कः_BIT) {
        alloc_flags.p_अग्र = alloc_p_अग्र;
        alloc_p_अग्र = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.स्मृतिः_Requirements, flags, alloc_p_अग्र,
                          &buf->flags, &buf->mem);
    यदि (err)
        प्रत्यागम err;

    ret = vk->Bind_बफर_स्मृतिः(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    यदि (usage & VK_बफर_USAGE_SHADER_DEVICE_स्थानाङ्कः_BIT) {
        Vk_बफर_Device_स्थानाङ्कः_Info स्थानाङ्कः_info = {
            .sType = VK_STRUCTURE_TYPE_बफर_DEVICE_स्थानाङ्कः_INFO,
            .बफर = buf->buf,
        };
        buf->स्थानाङ्कः = vk->Get_बफर_Device_स्थानाङ्कः(s->hwctx->act_dev, &स्थानाङ्कः_info);
    }

    buf->आकार = आकार;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_map_buffers(FFVulkanContext *s, FFVk_बफर **buf, uint8_t *mem[],
                      पूर्णाङ्क nb_buffers, पूर्णाङ्क invalidate)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_स्मृतिः_Range inval_list[64];
    पूर्णाङ्क inval_गणनम् = 0;

    प्रति (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        शून्य *dst;
        ret = vk->Map_स्मृतिः(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_सम्पूर्णम्_आकार, 0, &dst);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        यदि (mem)
            mem[i] = dst;
    }

    यदि (!invalidate)
        प्रत्यागम 0;

    प्रति (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        ध्रुव Vk_Mapped_स्मृतिः_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_स्मृतिः_RANGE,
            .स्मृतिः = buf[i]->mem,
            .आकार   = VK_सम्पूर्णम्_आकार,
        };
        यदि (buf[i]->flags & VK_स्मृतिः_PROPERTY_HOST_COHERENT_BIT)
            अनुवर्त;
        inval_list[inval_गणनम्++] = ival_buf;
    }

    यदि (inval_गणनम्) {
        ret = vk->Invalidate_Mapped_स्मृतिः_Ranges(s->hwctx->act_dev, inval_गणनम्,
                                               inval_list);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }
    }

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_flush_बफर(FFVulkanContext *s, FFVk_बफर *buf,
                       Vk_Device_आकार विस्थापनम्, Vk_Device_आकार mem_आकार,
                       पूर्णाङ्क flush)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (buf->flags & VK_स्मृतिः_PROPERTY_HOST_COHERENT_BIT)
        प्रत्यागम 0;

    ध्रुव Vk_Mapped_स्मृतिः_Range flush_दत्त = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_स्मृतिः_RANGE,
        .स्मृतिः = buf->mem,
        .विस्थापनम् = विस्थापनम्,
        .आकार   = mem_आकार,
    };

    यदि (flush)
        ret = vk->Flush_Mapped_स्मृतिः_Ranges(s->hwctx->act_dev, 1, &flush_दत्त);
    अन्यथा
        ret = vk->Invalidate_Mapped_स्मृतिः_Ranges(s->hwctx->act_dev, 1, &flush_दत्त);

    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_बफर **buf, पूर्णाङ्क nb_buffers,
                        पूर्णाङ्क flush)
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_स्मृतिः_Range flush_list[64];
    पूर्णाङ्क flush_गणनम् = 0;

    यदि (flush) {
        प्रति (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
            ध्रुव Vk_Mapped_स्मृतिः_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_स्मृतिः_RANGE,
                .स्मृतिः = buf[i]->mem,
                .आकार   = VK_सम्पूर्णम्_आकार,
            };

            av_assert0(!buf[i]->host_ref);
            यदि (buf[i]->flags & VK_स्मृतिः_PROPERTY_HOST_COHERENT_BIT)
                अनुवर्त;
            flush_list[flush_गणनम्++] = flush_buf;
        }
    }

    यदि (flush_गणनम्) {
        ret = vk->Flush_Mapped_स्मृतिः_Ranges(s->hwctx->act_dev, flush_गणनम्,
                                          flush_list);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    प्रति (पूर्णाङ्क i = 0; i < nb_buffers; i++) {
        vk->Unmap_स्मृतिः(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = रिक्त;
    }

    प्रत्यागम err;
}

शून्य ff_vk_free_buf(FFVulkanContext *s, FFVk_बफर *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    यदि (!buf || !s->hwctx)
        प्रत्यागम;

    यदि (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_बफर(s, buf, 0);
    यदि (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_बफर(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    यदि (buf->mem != VK_NULL_HANDLE)
        vk->Free_स्मृतिः(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    यदि (buf->host_ref)
        av_बफर_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = रिक्त;
}

स्थिर शून्य pooled_buf_free(AVRefStructOpaque opaque, शून्य *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णाङ्क ff_vk_get_pooled_बफर(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_बफर **buf, Vk_बफर_Usage_Flags usage,
                            शून्य *create_p_अग्र, size_t आकार,
                            Vk_स्मृतिः_Property_Flag_द्वयङ्काः mem_props)
{
    पूर्णाङ्क err;
    FFVk_बफर *दत्त;

    यदि (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(परिमाण(FFVk_बफर), 0, ctx,
                                                रिक्त, रिक्त, pooled_buf_free,
                                                रिक्त);
        यदि (!(*buf_pool))
            प्रत्यागम AVERROR(ENOMEM);
    }

    *buf = दत्त = av_refstruct_pool_get(*buf_pool);
    यदि (!दत्त)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (दत्त->आकार >= आकार)
        प्रत्यागम 0;

    ff_vk_free_buf(ctx, दत्त);
    स्मृतिं_पूरय(दत्त, 0, परिमाण(*दत्त));

    err = ff_vk_create_buf(ctx, दत्त, आकार,
                           create_p_अग्र, रिक्त, usage,
                           mem_props);
    यदि (err < 0) {
        av_refstruct_unref(buf);
        प्रत्यागम err;
    }

    यदि (mem_props & VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT) {
        err = ff_vk_map_बफर(ctx, दत्त, &दत्त->mapped_mem, 0);
        यदि (err < 0) {
            av_refstruct_unref(buf);
            प्रत्यागम err;
        }
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क create_mapped_बफर(FFVulkanContext *s,
                                FFVk_बफर *vkb, Vk_बफर_Usage_Flags usage,
                                size_t आकार,
                                Vk_External_स्मृतिः_बफर_Create_Info *create_desc,
                                Vk_Import_स्मृतिः_Host_Pointer_Info_EXT *import_desc,
                                Vk_स्मृतिः_Host_Pointer_Properties_EXT props)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_बफर_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_बफर_CREATE_INFO,
        .p_अग्र       = create_desc,
        .usage       = usage,
        .sharing_बहुलकम् = VK_SHARING_बहुलकम्_EXCLUSIVE,
        .आकार        = आकार,
    };
    Vk_स्मृतिः_Requirements req = {
        .आकार           = आकार,
        .alignment      = s->hprops.minImportedHostPointerAlignment,
        .स्मृतिः_Type_द्वयङ्काः = props.स्मृतिः_Type_द्वयङ्काः,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT,
                          import_desc, &vkb->flags, &vkb->mem);
    यदि (err < 0)
        प्रत्यागम err;

    ret = vk->Create_बफर(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    यदि (ret != VK_SUCCESS) {
        vk->Free_स्मृतिः(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        प्रत्यागम AVERROR_EXTERNAL;
    }

    ret = vk->Bind_बफर_स्मृतिः(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    यदि (ret != VK_SUCCESS) {
        vk->Free_स्मृतिः(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_बफर(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर शून्य host_map_free(AVRefStructOpaque opaque, शून्य *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

पूर्णाङ्क ff_vk_host_map_बफर(FFVulkanContext *s, FFVk_बफर **dst,
                          uint8_t *src_दत्त, Vk_Device_आकार आकार,
                          ध्रुव AVBufferRef *src_buf,
                          Vk_बफर_Usage_Flags usage)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_स्मृतिः_बफर_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_स्मृतिः_बफर_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_HOST_आवण्टनम्_BIT_EXT,
    };
    Vk_स्मृतिः_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_स्मृतिः_ALLOCATE_FLAGS_INFO,
        .flags = VK_स्मृतिः_ALLOCATE_DEVICE_स्थानाङ्कः_BIT,
    };
    Vk_Import_स्मृतिः_Host_Pointer_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_स्मृतिः_HOST_POINTER_INFO_EXT,
        .handleType = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_HOST_आवण्टनम्_BIT_EXT,
        .p_अग्र = usage & VK_बफर_USAGE_SHADER_DEVICE_स्थानाङ्कः_BIT ? &alloc_flags : रिक्त,
    };
    Vk_स्मृतिः_Host_Pointer_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_बफर *vkb;
    size_t offs;
    size_t बफर_आकार;

    *dst = रिक्त;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_दत्त % s->hprops.minImportedHostPointerAlignment;
    import_desc.pHostPointer = src_दत्त - offs;

    props = (Vk_स्मृतिः_Host_Pointer_Properties_EXT) {
        VK_STRUCTURE_TYPE_स्मृतिः_HOST_POINTER_PROPERTIES_EXT,
    };
    ret = vk->Get_स्मृतिः_Host_Pointer_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.pHostPointer,
                                                &props);
    यदि (!(ret == VK_SUCCESS && props.स्मृतिः_Type_द्वयङ्काः))
        प्रत्यागम AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_बफर_ref(src_buf);
    यदि (!ref)
        प्रत्यागम AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ध्रुव Vk_Device_आकार src_avail = src_buf->आकार - (src_दत्त - src_buf->दत्त);
    बफर_आकार = offs + FFMIN(आकार, src_avail);
    बफर_आकार = FFALIGN(बफर_आकार, s->props.properties.limits.min_स्मृतिः_Map_Alignment);
    बफर_आकार = FFALIGN(बफर_आकार, s->hprops.minImportedHostPointerAlignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(परिमाण(*vkb), 0, s, host_map_free);
    यदि (!vkb) {
        av_बफर_unref(&ref);
        प्रत्यागम AVERROR(ENOMEM);
    }

    err = create_mapped_बफर(s, vkb, usage,
                               बफर_आकार, &create_desc, &import_desc,
                               props);
    यदि (err < 0) {
        av_बफर_unref(&ref);
        av_refstruct_unref(&vkb);
        प्रत्यागम err;
    }

    यदि (usage & VK_बफर_USAGE_SHADER_DEVICE_स्थानाङ्कः_BIT) {
        Vk_बफर_Device_स्थानाङ्कः_Info स्थानाङ्कः_info = {
            .sType = VK_STRUCTURE_TYPE_बफर_DEVICE_स्थानाङ्कः_INFO,
            .बफर = vkb->buf,
        };
        vkb->स्थानाङ्कः = vk->Get_बफर_Device_स्थानाङ्कः(s->hwctx->act_dev, &स्थानाङ्कः_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_विस्थापनम् = offs;
    vkb->स्थानाङ्कः       += offs;
    vkb->mapped_mem     = src_दत्त;
    vkb->आकार           = बफर_आकार - offs;

    *dst = vkb;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_shader_सङ्कलय_प्रक्षिप_const(FFVulkanShader *shd, पूर्णाङ्क विस्थापनम्, पूर्णाङ्क आकार,
                                Vk_Shader_Stage_Flag_द्वयङ्काः stage)
{
    Vk_प्रक्षिप_Constant_Range *pc = &shd->प्रक्षिप_consts[shd->प्रक्षिप_consts_अङ्कः++];
    av_assert1(shd->प्रक्षिप_consts_अङ्कः < FF_VK_MAX_प्रक्षिप_CONSTS);
    pc->stageFlags = stage;
    pc->विस्थापनम् = विस्थापनम्;
    pc->आकार = आकार;
    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       पूर्णाङ्क unnorm_coords, VkFilter filt)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_बहुलकम् = (unnorm_coords || filt == VK_FILTER_निकटतमः) ?
                      VK_SAMPLER_MIPMAP_बहुलकम्_निकटतमः :
                      VK_SAMPLER_MIPMAP_बहुलकम्_रैखिकम्,
        .स्थानाङ्कः_बहुलकम्_U = VK_SAMPLER_स्थानाङ्कः_बहुलकम्_CLAMP_गन्तव्यम्_EDGE,
        .स्थानाङ्कः_बहुलकम्_V = sampler_info.स्थानाङ्कः_बहुलकम्_U,
        .स्थानाङ्कः_बहुलकम्_W = sampler_info.स्थानाङ्कः_बहुलकम्_U,
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
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, पूर्णाङ्क p)
{
    AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);
    पूर्णाङ्क nb_planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);

    स्थिर ध्रुव VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_1_BIT,
                                                       VK_IMAGE_ASPECT_PLANE_2_BIT, };

    यदि (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        प्रत्यागम VK_IMAGE_ASPECT_COLOR_BIT;

    प्रत्यागम plane_aspect[p];
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
        प्रत्यागम 1;
    प्रत्यागम 0;
}

शून्य ff_vk_समुच्चयः_perm(गणना AVPixelFormat pix_fmt, पूर्णाङ्क lut[4], पूर्णाङ्क inv)
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
        भङ्ग;
    पक्ष AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_BGRA:
    पक्ष AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        भङ्ग;
    स्वभाव:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        भङ्ग;
    }

    यदि (inv) {
        पूर्णाङ्क lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        प्रति (पूर्णाङ्क i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    प्रत्यागम;
}

ध्रुव वर्ण *ff_vk_shader_rep_fmt(गणना AVPixelFormat pix_fmt,
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
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_X2RGB10:
    पक्ष AV_PIX_FMT_X2BGR10:
    पक्ष AV_PIX_FMT_Y210:
    पक्ष AV_PIX_FMT_XV30: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = रिक्त,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGB48:
    पक्ष AV_PIX_FMT_RGBA64:
    पक्ष AV_PIX_FMT_Y212:
    पक्ष AV_PIX_FMT_Y216:
    पक्ष AV_PIX_FMT_XV36:
    पक्ष AV_PIX_FMT_XV48: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGBAF16: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        प्रत्यागम rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGBF32:
    पक्ष AV_PIX_FMT_RGBAF32: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    }
    पक्ष AV_PIX_FMT_RGB96:
    पक्ष AV_PIX_FMT_RGBA128: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = रिक्त,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
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
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
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
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_GRAY32:
    पक्ष AV_PIX_FMT_GRAYF32:
    पक्ष AV_PIX_FMT_GBRPF32:
    पक्ष AV_PIX_FMT_GBRAPF32: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_GBRAP32: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = रिक्त,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_NV12:
    पक्ष AV_PIX_FMT_NV16:
    पक्ष AV_PIX_FMT_NV24: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_P010:
    पक्ष AV_PIX_FMT_P210:
    पक्ष AV_PIX_FMT_P410: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = रिक्त,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    पक्ष AV_PIX_FMT_P012:
    पक्ष AV_PIX_FMT_P016:
    पक्ष AV_PIX_FMT_P212:
    पक्ष AV_PIX_FMT_P216:
    पक्ष AV_PIX_FMT_P412:
    पक्ष AV_PIX_FMT_P416: {
        ध्रुव वर्ण *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        प्रत्यागम rep_tab[rep_fmt];
    };
    स्वभाव:
        प्रत्यागम "rgba32f";
    }
}

स्थिर शून्य reset_imageviews(AVRefStructOpaque अप्रयुक्तम्, शून्य *obj)
{
    FFVkImageViews *iv = obj;

    प्रति (पूर्णाङ्क i = 0; i < iv->nb_views; i++) {
        यदि (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    स्मृतिं_पूरय(iv->views, 0, परिमाण(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, पूर्णाङ्क nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_अङ्कः_दत्त_सूचकाः);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    यदि (!iv)
        प्रत्यागम रिक्त;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    प्रत्यागम iv;
}

VkFormat ff_vk_map_fmt_गन्तव्यम्_rep(VkFormat fmt, गणना FFVkShaderRepFormat rep_fmt)
{
#परिभाषय REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#परिभाषय REPS_FMT_PACK(fmt, अङ्कः) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## अङ्कः, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## अङ्कः, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## अङ्कः, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## अङ्कः,

    ध्रुव VkFormat fmts_map[][4] = {
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
#अपरिभाषय REPS_FMT_PACK
#अपरिभाषय REPS_FMT

    यदि (fmt == VK_FORMAT_UNDEFINED)
        प्रत्यागम VK_FORMAT_UNDEFINED;

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        यदि (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            प्रत्यागम fmts_map[i][rep_fmt];
    }

    प्रत्यागम VK_FORMAT_UNDEFINED;
}

पूर्णाङ्क ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, पूर्णाङ्क plane, गणना FFVkShaderRepFormat rep_fmt)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    AVVulkan_चौकटाः_Context *vkfc = hwfc->hwctx;
    ध्रुव VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);

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
        .format     = ff_vk_map_fmt_गन्तव्यम्_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_तटस्थः_map,
        .subresourceRange = {
            .aspect_आवरणम् = ff_vk_aspect_flag(f, plane),
            .level_गणनम् = 1,
            .layer_गणनम् = 1,
        },
    };
    यदि (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        प्रत्यागम AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_आवरणम्;

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अङ्कः_दत्त_सूचकाः],
                                AVFrame *f,
                                ध्रुव VkFormat fmts[AV_अङ्कः_दत्त_सूचकाः])
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    AVVulkan_चौकटाः_Context *vkfc = hwfc->hwctx;
    AVVkFrame *vkf = (AVVkFrame *)f->दत्त[0];
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);
    ध्रुव पूर्णाङ्क nb_planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_अङ्कः_दत्त_सूचकाः] = { 0 };

    प्रति (पूर्णाङ्क i = 0; i < nb_planes; i++) {
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
            .components = ff_comp_तटस्थः_map,
            .subresourceRange = {
                .aspect_आवरणम् = ff_vk_aspect_flag(f, i),
                .level_गणनम् = 1,
                .layer_गणनम् = 1,
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
    प्रति (पूर्णाङ्क i = 0; i < nb_planes; i++)
        ff_vk_exec_सङ्कलय_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    स्मृतिं_प्रतिलिख(views, tmp_views, nb_planes*परिमाण(*views));

    प्रत्यागम 0;

fail:
    प्रति (पूर्णाङ्क i = 0; i < nb_planes; i++)
        यदि (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    प्रत्यागम err;
}

पूर्णाङ्क ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_अङ्कः_दत्त_सूचकाः],
                            AVFrame *f, गणना FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    ध्रुव VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ध्रुव पूर्णाङ्क nb_planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    VkFormat fmts[AV_अङ्कः_दत्त_सूचकाः] = { 0 };

    प्रति (पूर्णाङ्क i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_गन्तव्यम्_rep(rep_fmts[i], rep_fmt);
        यदि (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            प्रत्यागम AVERROR(EINVAL);
        }
    }

    प्रत्यागम ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

शून्य ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_स्मृतिः_Barrier2 *bar, पूर्णाङ्क *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    पूर्णाङ्क प्राप्तम् = -1;
    AVVkFrame *vkf = (AVVkFrame *)pic->दत्त[0];
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(vkf);
    प्रति (पूर्णाङ्क i = 0; i < e->nb_frame_deps; i++)
        यदि (e->frame_deps[i]->दत्त[0] == pic->दत्त[0]) {
            यदि (e->frame_update[i])
                प्राप्तम् = i;
            भङ्ग;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_स्मृतिः_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_स्मृतिः_BARRIER_2,
            .p_अग्र = रिक्त,
            .src_Stage_आवरणम् = src_stage,
            .dst_Stage_आवरणम् = dst_stage,
            .src_Access_आवरणम् = प्राप्तम् >= 0 ? e->access_dst[प्राप्तम्] : VK_ACCESS_2_NONE,
            .dst_Access_आवरणम् = new_access,
            .oldLayout = प्राप्तम् >= 0 ? e->layout_dst[प्राप्तम्] : vkf->layout[0],
            .newLayout = new_layout,
            .src_Queue_Family_सूचकांक = प्राप्तम् >= 0 ? e->queue_family_dst[प्राप्तम्] : vkf->queue_family[0],
            .dst_Queue_Family_सूचकांक = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_आवरणम् = VK_IMAGE_ASPECT_COLOR_BIT,
                .layer_गणनम् = 1,
                .level_गणनम् = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_frame(s, e, pic, &bar[*nb_bar - nb_images], रिक्त);
}

पूर्णाङ्क ff_vk_shader_आरोपय(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_आकार[3], uint32_t required_subgroup_आकार)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    स्मृतिं_प्रतिलिख(shd->lg_आकार, wg_आकार, 3*परिमाण(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_आकार_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_आकार_CREATE_INFO,
        .required_Subgroup_आकार = required_subgroup_आकार,
    };

    विकल्प (shd->stage) {
    पक्ष VK_SHADER_STAGE_ANY_लब्धम्_BIT_KHR:
    पक्ष VK_SHADER_STAGE_CALLABLE_BIT_KHR:
    पक्ष VK_SHADER_STAGE_CLOSEST_लब्धम्_BIT_KHR:
    पक्ष VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
    पक्ष VK_SHADER_STAGE_अलब्धिः_BIT_KHR:
    पक्ष VK_SHADER_STAGE_RAYGEN_BIT_KHR:
        shd->bind_point = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
        भङ्ग;
    पक्ष VK_SHADER_STAGE_COMPUTE_BIT:
        shd->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        भङ्ग;
    स्वभाव:
        shd->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        भङ्ग;
    };

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_समुच्चयः_Layouts            = shd->desc_layout,
        .समुच्चयः_Layout_गणनम्         = shd->nb_descriptor_sets,
        .प्रक्षिप_Constant_Range_गणनम् = shd->प्रक्षिप_consts_अङ्कः,
        .p_प्रक्षिप_Constant_Ranges    = shd->प्रक्षिप_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ध्रुव uint8_t *spirv, size_t spirv_len)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_अग्र    = रिक्त,
        .flags    = 0x0,
        .p_संहिता    = (शून्य *)spirv,
        .संहिता_आकार = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    यदि (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ध्रुव वर्ण *entrypoint)
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
                     &shd->subgroup_info : रिक्त,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_आकार ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_पूर्णम्_SUBGROUPS_BIT : 0x0,
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
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_परिणाम ret;
    FFVulkanFunctions *vk = &s->vkfn;

    पूर्णाङ्क has_singular = 0;
    पूर्णाङ्क max_descriptors = 0;
    प्रति (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_समुच्चयः[i].nb_bindings);
        यदि (shd->desc_समुच्चयः[i].singular)
            has_singular = 1;
    }
    shd->use_प्रक्षिप = (s->extensions & FF_VK_EXT_प्रक्षिप_DESCRIPTOR) &&
                    (max_descriptors <= s->प्रक्षिप_desc_props.max_प्रक्षिप_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    प्रति (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_समुच्चयः *समुच्चयः = &shd->desc_समुच्चयः[i];
        Vk_Descriptor_समुच्चयः_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_समुच्चयः_LAYOUT_CREATE_INFO,
            .binding_गणनम् = समुच्चयः->nb_bindings,
            .pBindings = समुच्चयः->binding,
            .flags = (shd->use_प्रक्षिप) ?
                     VK_DESCRIPTOR_समुच्चयः_LAYOUT_CREATE_प्रक्षिप_DESCRIPTOR_BIT_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_समुच्चयः_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }
    }

    प्रत्यागम 0;
}

पूर्णाङ्क ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ध्रुव वर्ण *spirv, size_t spirv_len,
                      ध्रुव वर्ण *entrypoint)
{
    पूर्णाङ्क err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_प्रविष्टिः spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t निवेशः_आकार = spirv_len;

    यदि (shd->precompiled) {
        यदि (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_प्रविष्टिः_गणनम् = 0,
                .p_दत्त = shd->lg_आकार,
                .दत्त_आकार_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_प्रविष्टिः *spe = (शून्य *)shd->specialization_info->pMapEntries;
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_प्रविष्टिः_गणनम्++] = (Vk_Specialization_Map_प्रविष्टिः) {
                .constantID = 253 + i,
                .विस्थापनम् = shd->specialization_info->दत्त_आकार_2 + i*परिमाण(uint32_t),
                .आकार = परिमाण(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_दत्त;
        स्मृतिं_प्रतिलिख(&spd[shd->specialization_info->दत्त_आकार_2],
               shd->lg_आकार, 3*परिमाण(uint32_t));
        shd->specialization_info->दत्त_आकार_2 += 3*परिमाण(uint32_t);

#यदि CONFIG_SHADER_COMPRESSION
        uint8_t *बहिर्गमनम्;
        size_t बहिर्गमनम्_len;
        पूर्णाङ्क ret = ff_zlib_expand(s, &बहिर्गमनम्, &बहिर्गमनम्_len, spirv, spirv_len);
        यदि (ret < 0)
            प्रत्यागम ret;
        spirv = बहिर्गमनम्;
        spirv_len = बहिर्गमनम्_len;
#यदि_अन्तः
    }

    err = init_descriptors(s, shd);
    यदि (err < 0)
        गच्छ अन्तः_2;

    err = init_pipeline_layout(s, shd);
    यदि (err < 0)
        गच्छ अन्तः_2;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    यदि (err < 0)
        गच्छ अन्तः_2;

    विकल्प (shd->bind_point) {
    पक्ष VK_PIPELINE_BIND_POINT_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        भङ्ग;
    स्वभाव:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_point);
        err = AVERROR(EINVAL);
        गच्छ अन्तः_2;
        भङ्ग;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    यदि (err < 0)
        गच्छ अन्तः_2;

    यदि (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    अन्यथा
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    यदि (निवेशः_आकार != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", निवेशः_आकार);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

अन्तः_2:
    यदि (shd->precompiled) {
        shd->specialization_info->map_प्रविष्टिः_गणनम् -= 3;
        shd->specialization_info->दत्त_आकार_2 -= 3*परिमाण(uint32_t);
    }
#यदि CONFIG_SHADER_COMPRESSION
    यदि (shd->precompiled)
        av_free((शून्य *)spirv);
#यदि_अन्तः
    प्रत्यागम err;
}

शून्य ff_vk_shader_सङ्कलय_descriptor_समुच्चयः(FFVulkanContext *s, FFVulkanShader *shd,
                                     ध्रुव FFVulkan_Descriptor_समुच्चयः_Binding *desc, पूर्णाङ्क nb,
                                     पूर्णाङ्क singular)
{
    FFVulkan_Descriptor_समुच्चयः *समुच्चयः = &shd->desc_समुच्चयः[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    प्रति (पूर्णाङ्क i = 0; i < nb; i++) {
        समुच्चयः->binding[i].binding            = i;
        समुच्चयः->binding[i].descriptorType     = desc[i].type;
        समुच्चयः->binding[i].descriptor_गणनम्    = FFMAX(desc[i].elems, 1);
        समुच्चयः->binding[i].stageFlags         = desc[i].stages;
        समुच्चयः->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    प्रति (पूर्णाङ्क i = 0; i < nb; i++) {
        पूर्णाङ्क j;
        प्रति (j = 0; j < shd->nb_desc_pool_आकार; j++)
            यदि (shd->desc_pool_आकार[j].type == desc[i].type)
                भङ्ग;
        यदि (j >= shd->nb_desc_pool_आकार) {
            shd->nb_desc_pool_आकार++;
            av_assert1(shd->nb_desc_pool_आकार < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_आकार[j].type             = desc[i].type;
        shd->desc_pool_आकार[j].descriptor_गणनम् += FFMAX(desc[i].elems, 1);
    }

    समुच्चयः->singular = singular;
    समुच्चयः->nb_bindings = nb;
}

पूर्णाङ्क ff_vk_shader_पञ्जिकाकोशः_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    यदि (!shd->nb_descriptor_sets)
        प्रत्यागम 0;

    FFVulkan_Shader_दत्त *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    यदि (!shd->use_प्रक्षिप) {
        Vk_परिणाम ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_समुच्चयः_Layout *tmp_layouts;
        Vk_Descriptor_समुच्चयः_Allocate_Info समुच्चयः_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        प्रति (पूर्णाङ्क i = 0; i < shd->nb_desc_pool_आकार; i++)
            shd->desc_pool_आकार[i].descriptor_गणनम् *= pool->pool_आकार;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_आकार,
            .pool_आकार_गणनम् = shd->nb_desc_pool_आकार,
            .maxSets = sd->nb_descriptor_sets*pool->pool_आकार,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, परिमाण(*tmp_layouts));
        यदि (!tmp_layouts)
            प्रत्यागम AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        प्रति (पूर्णाङ्क i = 0; i < pool->pool_आकार; i++)
            प्रति (पूर्णाङ्क j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        समुच्चयः_alloc_info = (Vk_Descriptor_समुच्चयः_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_समुच्चयः_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_समुच्चयः_Layouts        = tmp_layouts,
            .descriptor_समुच्चयः_गणनम् = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        परिमाण(*tmp_layouts));
        यदि (!sd->desc_sets) {
            av_free(tmp_layouts);
            प्रत्यागम AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &समुच्चयः_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        यदि (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            प्रत्यागम AVERROR_EXTERNAL;
        }
    }

    प्रत्यागम 0;
}

स्थिर अन्तःस्थ ध्रुव FFVulkan_Shader_दत्त *get_shd_दत्त(FFVkExecContext *e,
                                                     ध्रुव FFVulkanShader *shd)
{
    प्रति (पूर्णाङ्क i = 0; i < e->parent->nb_reg_shd; i++)
        यदि (e->parent->reg_shd[i].shd == shd)
            प्रत्यागम &e->parent->reg_shd[i];
    प्रत्यागम रिक्त;
}

स्थिर अन्तःस्थ शून्य update_समुच्चयः_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, पूर्णाङ्क समुच्चयः,
                                         Vk_Write_Descriptor_समुच्चयः *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_समुच्चयः *desc_समुच्चयः = &shd->desc_समुच्चयः[समुच्चयः];
    ध्रुव FFVulkan_Shader_दत्त *sd = get_shd_दत्त(e, shd);

    यदि (desc_समुच्चयः->singular) {
        प्रति (पूर्णाङ्क i = 0; i < e->parent->pool_आकार; i++) {
            write_info->dst_समुच्चयः = sd->desc_sets[i*sd->nb_descriptor_sets + समुच्चयः];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, रिक्त);
        }
    } अन्यथा {
        यदि (shd->use_प्रक्षिप) {
            vk->Cmd_प्रक्षिप_Descriptor_समुच्चयः_KHR(e->buf,
                                        shd->bind_point,
                                        shd->pipeline_layout,
                                        समुच्चयः, 1,
                                        write_info);
        } अन्यथा {
            write_info->dst_समुच्चयः = sd->desc_sets[e->idx*sd->nb_descriptor_sets + समुच्चयः];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, रिक्त);
        }
    }
}

पूर्णाङ्क ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णाङ्क समुच्चयः, पूर्णाङ्क bind, पूर्णाङ्क offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_समुच्चयः *desc_समुच्चयः = &shd->desc_समुच्चयः[समुच्चयः];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_समुच्चयः desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_समुच्चयः,
        .dstBinding = bind,
        .descriptor_गणनम् = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_समुच्चयः->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_समुच्चयः_pool_write(s, e, shd, समुच्चयः, &desc_pool_write_info);

    प्रत्यागम 0;
}

शून्य ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णाङ्क समुच्चयः, पूर्णाङ्क binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_चौकटाः_ctx->दत्त;
    ध्रुव पूर्णाङ्क nb_planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);

    प्रति (पूर्णाङ्क i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, समुच्चयः, binding, i,
                                views[i], layout, sampler);
}

पूर्णाङ्क ff_vk_shader_update_desc_बफर(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णाङ्क समुच्चयः, पूर्णाङ्क bind, पूर्णाङ्क elem,
                                    FFVk_बफर *buf, Vk_Device_आकार विस्थापनम्, Vk_Device_आकार len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_समुच्चयः *desc_समुच्चयः = &shd->desc_समुच्चयः[समुच्चयः];

    Vk_Descriptor_बफर_Info desc_pool_write_info_buf = {
        .बफर = buf->buf,
        .विस्थापनम् = buf->virtual_विस्थापनम् + विस्थापनम्,
        .range = len,
    };
    Vk_Write_Descriptor_समुच्चयः desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_समुच्चयः,
        .dstBinding = bind,
        .descriptor_गणनम् = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_समुच्चयः->binding[bind].descriptorType,
        .p_बफर_Info = &desc_pool_write_info_buf,
    };
    update_समुच्चयः_pool_write(s, e, shd, समुच्चयः, &desc_pool_write_info);

    प्रत्यागम 0;
}

शून्य ff_vk_shader_update_प्रक्षिप_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_द्वयङ्काः stage,
                                    पूर्णाङ्क विस्थापनम्, size_t आकार, शून्य *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_प्रक्षिप_Constants(e->buf, shd->pipeline_layout,
                         stage, विस्थापनम्, आकार, src);
}

शून्य ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ध्रुव FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ध्रुव FFVulkan_Shader_दत्त *sd = get_shd_दत्त(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_point, shd->pipeline);

    यदि (sd && sd->nb_descriptor_sets) {
        यदि (!shd->use_प्रक्षिप) {
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
#यदि_अन्तः

    यदि (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    यदि (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    प्रति (पूर्णाङ्क i = 0; i < shd->nb_descriptor_sets; i++)
        यदि (shd->desc_layout[i])
            vk->Destroy_Descriptor_समुच्चयः_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

शून्य ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#यदि_परिभाषितम् VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#यदि_अन्तः
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_बफर_unref(&s->device_ref);
    av_बफर_unref(&s->चौकटाः_ref);
}

पूर्णाङ्क ff_vk_init(FFVulkanContext *s, शून्य *log_parent,
               AVBufferRef *device_ref, AVBufferRef *चौकटाः_ref)
{
    पूर्णाङ्क err;

    स्थिर ध्रुव AVClass vulkan_context_class = {
        .class_name       = "vk",
        .संस्करणम्          = LIBAVUTIL_संस्करणम्_INT,
        .parent_log_context_विस्थापनम् = offsetof(FFVulkanContext, log_parent),
    };

    स्मृतिं_पूरय(s, 0, परिमाण(*s));
    s->log_parent = log_parent;
    s->class      = &vulkan_context_class;

    यदि (चौकटाः_ref) {
        s->चौकटाः_ref = av_बफर_ref(चौकटाः_ref);
        यदि (!s->चौकटाः_ref)
            प्रत्यागम AVERROR(ENOMEM);

        s->चौकटाः = (AVHWFramesContext *)s->चौकटाः_ref->दत्त;
        s->hwfc = s->चौकटाः->hwctx;

        device_ref = s->चौकटाः->device_ref;
    }

    s->device_ref = av_बफर_ref(device_ref);
    यदि (!s->device_ref) {
        ff_vk_uninit(s);
        प्रत्यागम AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->दत्त;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_गन्तव्यम्_आवरणम्(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_गन्तव्यम्_आवरणम्(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_आरोपय_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    यदि (err < 0) {
        ff_vk_uninit(s);
        प्रत्यागम err;
    }

    err = ff_vk_आरोपय_props(s);
    यदि (err < 0) {
        ff_vk_uninit(s);
        प्रत्यागम err;
    }

    प्रत्यागम 0;
}
