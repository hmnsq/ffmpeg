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

#ضمن "config.h"
#ضمن "avassert.h"
#ضمن "mem.h"
#ضمن "random_seed.h"
#ضمن "refstruct.h"

#ضمن "vulkan.h"
#ضمن "libavutil/vulkan_loader.h"

#إذا CONFIG_SHADER_COMPRESSION
#ضمن "libavutil/zlib_utils.h"
#جيڪڏهن_پورو

ثابت VkComponentMapping ff_comp_سڃاڻپ_عنصر_map = {
    .r = VK_COMPONENT_SWIZZLE_سڃاڻپ_عنصر,
    .g = VK_COMPONENT_SWIZZLE_سڃاڻپ_عنصر,
    .b = VK_COMPONENT_SWIZZLE_سڃاڻپ_عنصر,
    .a = VK_COMPONENT_SWIZZLE_سڃاڻپ_عنصر,
};

/* Converts return values to strings */
ثابت حرف *ff_vk_ret2str(Vk_نتيجو res)
{
#وصف_ڪريو CASE(VAL) حالة VAL: أرجع #VAL
    بدل (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_سيٽ);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_ٻاهريون_جو_HOST_يادگيري);
    CASE(VK_ERROR_ٻاهريون_جو_DEVICE_يادگيري);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_گم);
    CASE(VK_ERROR_يادگيري_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_ٻاهريون_جو_POOL_يادگيري);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_پتو);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_گم_KHR);
    CASE(VK_ERROR_NATIVE_دري_اندريون_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_ٻاهريون_جو_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_نسخو_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_ڀريل_SCREEN_EXCLUSIVE_گهڻائي_گم_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_پورو_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    افتراضي: أرجع "Unknown error";
    }
#وصف_رد CASE
}

/* Malitia pura, Khronos */
#وصف_ڪريو FN_MAP_منزل(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## منزل_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_منزل(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ٻٽو_انگ,                   \
               VK_IMAGE_USAGE_SAMPLED_ٻٽو_انگ);                             \
        MAP_منزل(VK_FORMAT_FEATURE_2_TRANSFER_SRC_ٻٽو_انگ,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_ٻٽو_انگ);                        \
        MAP_منزل(VK_FORMAT_FEATURE_2_TRANSFER_DST_ٻٽو_انگ,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_ٻٽو_انگ);                        \
        MAP_منزل(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ٻٽو_انگ,                   \
               VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ);                             \
        MAP_منزل(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_ٻٽو_انگ,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_ٻٽو_انگ);                    \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_ٻٽو_انگ_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_ٻٽو_انگ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ٻٽو_انگ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_ٻٽو_انگ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ٻٽو_انگ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_داخلا_ٻٽو_انگ_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_ٻٽو_انگ_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT);                   \
        أرجع dst;                                                     \
    }

#وصف_ڪريو MAP_منزل(flag1, flag2) إذا (src & flag2) dst |= flag1;
FN_MAP_منزل(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#وصف_رد MAP_منزل
#وصف_ڪريو MAP_منزل(flag1, flag2) إذا (src & flag1) dst |= flag2;
FN_MAP_منزل(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#وصف_رد MAP_منزل
#وصف_رد FN_MAP_منزل

ساكن فراغ ڀريو_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    لكل (صحيح i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        صحيح skip = 0;
        لكل (صحيح j = 0; j < s->nb_qfs; j++) {
            إذا (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                اكسر;
            }
        }
        إذا (skip)
            استمر;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ساكن فراغ reset_imageviews(AVRefStructOpaque اڻ_استعمال_ٿيل, فراغ *obj);

صحيح ff_vk_ڀريو_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_سائيز_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ڌڪو_desc_props, FF_VK_EXT_ڌڪو_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ڌڪو_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_يادگيري,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_يادگيري_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_ميٽرڪس_props, FF_VK_EXT_COOP_ميٽرڪس,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ميٽرڪس_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_ويڪٽر_props, FF_VK_EXT_LONG_ويڪٽر,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ويڪٽر_PROPERTIES_EXT);
#جيڪڏهن_پورو

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#جيڪڏهن_پورو

    إذا (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(حجم(FFVkImageViews), 0,
                                                         عدم, عدم, reset_imageviews,
                                                         عدم, عدم);
        إذا (!s->imageviews_pool)
            أرجع AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(حجم(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_ڳڻپ = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_ڳڻپ = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    إذا (s->host_image_props.copy_Src_Layout_ڳڻپ == 512 ||
        s->host_image_props.copy_Dst_Layout_ڳڻپ == 512) {
        VkImageLayout *new_array;
        size_t new_سائيز;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = عدم;
        s->host_image_props.copy_Src_Layout_ڳڻپ =
        s->host_image_props.copy_Dst_Layout_ڳڻپ = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_سائيز = s->host_image_props.copy_Src_Layout_ڳڻپ +
                   s->host_image_props.copy_Dst_Layout_ڳڻپ;
        new_سائيز *= حجم(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_سائيز);
        إذا (!new_array)
            أرجع AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_ڳڻپ;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_يادگيري_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    لكل (صحيح i = 0; i < s->mprops.يادگيري_Type_ڳڻپ; i++)
        s->host_cached_flag |= s->mprops.يادگيري_Types[i].propertyFlags &
                               VK_يادگيري_PROPERTY_HOST_CACHED_ٻٽو_انگ;

    ڀريو_enabled_qfs(s);

    إذا (s->qf_props)
        أرجع 0;

    vk->Get_Physical_Device_قطار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, عدم);

    s->qf_props = av_calloc(s->tot_nb_qfs, حجم(*s->qf_props));
    إذا (!s->qf_props)
        أرجع AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, حجم(*s->query_props));
    إذا (!s->qf_props) {
        av_freep(&s->qf_props);
        أرجع AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, حجم(*s->video_props));
    إذا (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        أرجع AVERROR(ENOMEM);
    }

#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, حجم(*s->ownership_props));
    إذا (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        أرجع AVERROR(ENOMEM);
    }
#جيڪڏهن_پورو

    لكل (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_قطار_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_قطار,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_QUERY_نتيجو_حالت_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_قطار,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_VIDEO_PROPERTIES_KHR);
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#جيڪڏهن_پورو
    }

    vk->Get_Physical_Device_قطار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    إذا (s->extensions & FF_VK_EXT_COOP_ميٽرڪس) {
        vk->Get_Physical_Device_Cooperative_ميٽرڪس_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, عدم);

        إذا (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                حجم(Vk_Cooperative_ميٽرڪس_Properties_KHR));
            لكل (صحيح i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_ميٽرڪس_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_ميٽرڪس_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_ميٽرڪس_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    أرجع 0;
}

AVVulkan_Device_قطار_Family *ff_vk_qf_ڳوليو(FFVulkanContext *s,
                                         Vk_قطار_Flag_بٽ dev_family,
                                         Vk_Video_Codec_Operation_Flag_بٽ_KHR vid_ops)
{
    لكل (صحيح i = 0; i < s->hwctx->nb_qf; i++) {
        إذا ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            أرجع &s->hwctx->qf[i];
        }
    }
    أرجع عدم;
}

ساكن فراغ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

فراغ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    لكل (صحيح i = 0; i < pool->pool_سائيز; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        إذا (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_ڳڻپ = 1,
                .pSemaphores = &e->sem,
                .p_قدرون = &e->sem_قدر,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->تالو);
    }

    /* Free shader-specific data */
    لكل (صحيح i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_معلومات *sd = &pool->reg_shd[i];

        إذا (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    لكل (صحيح i = 0; i < pool->pool_سائيز; i++) {
        إذا (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        إذا (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    إذا (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_معلومات);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_سائيز = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ساكن atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)عدم)->qf)];
ساكن AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ساكن فراغ exec_pool_phase_ٻج(فراغ)
{
    uint32_t ٻج = av_get_random_ٻج();
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], ٻج, memory_order_relaxed);
}

صحيح ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_قطار_Family *qf,
                         FFVkExecPool *pool, صحيح nb_contexts,
                         صحيح nb_queries, VkQueryType query_type, صحيح query_64bit,
                         ثابت فراغ *query_create_pnext)
{
    صحيح err;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_بفر_Allocate_Info cbuf_create;

    ثابت VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = عدم;

    atomic_init(&pool->idx, 0);

    إذا (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_ڳوليو_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        إذا (!ef)
            أرجع AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*حجم(*pool->cmd_buf_pools));
    إذا (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*حجم(*pool->cmd_bufs));
    إذا (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    لكل (صحيح i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_ٻٽو_انگ |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_بفر_ٻٽو_انگ,
            .قطار_Family_اشاريو   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_بفر_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_بفر_ALLOCATE_INFO,
            .level              = VK_COMMAND_بفر_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_بفر_ڳڻپ = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }
    }

    /* Query pool */
    إذا (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_ايندڙ = query_create_pnext,
            .queryType = query_type,
            .query_ڳڻپ = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_حالت_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        إذا (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            صحيح nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_حالت_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } وإلا إذا (query_type == VK_QUERY_TYPE_نتيجو_حالت_ONLY_KHR) {
            pool->query_حالت_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_سائيز = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_معلومات = av_calloc(nb_contexts, pool->qd_سائيز);
        إذا (!pool->query_معلومات) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, حجم(*pool->contexts));
    إذا (!pool->contexts) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    pool->pool_سائيز = nb_contexts;

    لكل (صحيح i = 0; i < pool->pool_سائيز; i++)
        pthread_mutex_init(&pool->contexts[i].تالو, عدم);

#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    صحيح اندروني_قطار_sync = 0;
    إذا (s->extensions & FF_VK_EXT_اندروني_قطار_SYNC) {
        ثابت VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_ڳوليو_struct(s->hwctx->device_features.p_ايندڙ,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        اندروني_قطار_sync = iqs && iqs->internallySynchronizedQueues;
    }
#جيڪڏهن_پورو

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_ٻج);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    صحيح pin_قطار = qf->flags & (VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR |
                                 VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR);

    /* Init contexts */
    لكل (صحيح i = 0; i < pool->pool_سائيز; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ايندڙ = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->والد = pool;

        /* Query data */
        e->query_معلومات = ((uint8_t *)pool->query_معلومات) + pool->qd_سائيز*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_قطار ? phase % qf->انگ : (i + phase) % qf->انگ;
        e->qf = qf->idx;
        Vk_Device_قطار_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_قطار_INFO_2,
#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
            .flags            = اندروني_قطار_sync ?
                                VK_DEVICE_قطار_CREATE_INTERNALLY_SYNCHRONIZED_ٻٽو_انگ_KHR : 0,
#جيڪڏهن_پورو
            .قطار_Family_اشاريو = qf->idx,
            .قطار_اشاريو       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->قطار);
    }

    أرجع 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    أرجع err;
}

Vk_نتيجو ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              فراغ **معلومات, Vk_Query_نتيجو_Flag_بٽ flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->والد;
    Vk_Query_نتيجو_Flags qf = flags & ~(VK_QUERY_نتيجو_64_ٻٽو_انگ |
                                      VK_QUERY_نتيجو_WITH_حالت_ٻٽو_انگ_KHR);

    إذا (!e->query_معلومات) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        أرجع VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_نتيجو_64_ٻٽو_انگ : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_نتيجو_WITH_حالت_ٻٽو_انگ_KHR : 0x0;

    إذا (معلومات)
        *معلومات = e->query_معلومات;

    أرجع vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_سائيز, e->query_معلومات,
                                   pool->qd_سائيز, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    لكل (صحيح i = 0; i < pool->pool_سائيز; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        إذا (pthread_mutex_trylock(&e->تالو))
            استمر; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        إذا (vk->Get_Semaphore_Counter_قدر(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_قدر &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_چوکٺو_deps || e->nb_sw_چوکٺو_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->تالو);
    }

    أرجع &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_سائيز];
}

فراغ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ڳڻپ = 1,
        .pSemaphores = &e->sem,
        .p_قدرون = &e->sem_قدر,
    };
    pthread_mutex_تالو(&e->تالو);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->تالو);
}

صحيح ff_vk_exec_شروعات(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->والد;

    Vk_Command_بفر_Begin_Info cmd_شروعات = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_BEGIN_INFO,
        .flags = VK_COMMAND_بفر_USAGE_ONE_وقت_SUBMIT_ٻٽو_انگ,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ڳڻپ = 1,
        .pSemaphores = &e->sem,
        .p_قدرون = &e->sem_قدر,
    };

    pthread_mutex_تالو(&e->تالو);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_بفر(e->buf, &cmd_شروعات);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->تالو);
        أرجع AVERROR_EXTERNAL;
    }

    إذا (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_قدر++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .قدر = e->sem_قدر,
        .stage_نقاب = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
    };

    pthread_mutex_unlock(&e->تالو);

    أرجع 0;
}

ساكن فراغ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    لكل (صحيح j = 0; j < e->nb_buf_deps; j++)
        av_بفر_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    لكل (صحيح j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    لكل (صحيح j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        بدل (od->type) {
        حالة VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            اكسر;
        حالة VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            اكسر;
        افتراضي:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    لكل (صحيح j = 0; j < e->nb_sw_چوکٺو_deps; j++)
        av_چوکٺو_free(&e->sw_چوکٺو_deps[j]);
    e->nb_sw_چوکٺو_deps = 0;

    لكل (صحيح j = 0; j < e->nb_چوکٺو_deps; j++) {
        AVFrame *f = e->چوکٺو_deps[j];
        إذا (e->چوکٺو_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
            AVVulkan_چوکٺا_Context *vkfc = hwfc->hwctx;
            AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];
            vkfc->unlock_چوکٺو(hwfc, vkf);
            e->چوکٺو_locked[j] = 0;
        }
        e->چوکٺو_update[j] = 0;
    }
    e->nb_چوکٺو_deps = 0;

    e->sem_wait_cnt = 0;
    e->sem_sig_cnt = 0;
    e->sem_sig_val_dst_cnt = 0;
}

فراغ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .قدر = e->sem_قدر,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_بفر(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

فراغ ff_vk_exec_جوڙيو_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  فراغ *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

فراغ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   فراغ *obj)
{
    فراغ **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    لكل (صحيح i = 0; i < e->nb_refstruct_deps; i++) {
        إذا (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            أرجع;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = عدم;
}

فراغ ff_vk_exec_جوڙيو_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

صحيح ff_vk_exec_جوڙيو_dep_sw_چوکٺو(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_چوکٺو_deps < FF_VK_EXEC_MAX_SW_چوکٺو_DEPS);

    e->sw_چوکٺو_deps[e->nb_sw_چوکٺو_deps] = av_چوکٺو_clone(f);
    إذا (!e->sw_چوکٺو_deps[e->nb_sw_چوکٺو_deps])
        أرجع AVERROR(ENOMEM);

    e->nb_sw_چوکٺو_deps++;

    أرجع 0;
}

فراغ ff_vk_exec_جوڙيو_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .قدر = val,
        .stage_نقاب = stage,
    };
}

فراغ ff_vk_exec_جوڙيو_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .قدر = val,
        .stage_نقاب = stage,
    };
}

فراغ ff_vk_exec_جوڙيو_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, صحيح nb,
                                 VkPipelineStageFlagBits2 stage,
                                 صحيح wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    إذا (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        لكل (صحيح i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_نقاب = stage,
            };
        }

        أرجع;
    }

    /* Ownership of each semaphore passes to the execution */
    لكل (صحيح i = 0; i < nb; i++) {
        ff_vk_exec_جوڙيو_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_جوڙيو_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

صحيح ff_vk_exec_جوڙيو_dep_چوکٺو(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    AVVulkan_چوکٺا_Context *vkfc = hwfc->hwctx;
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];
    صحيح nb_images = ff_vk_ڳڻپ_images(vkf);

    /* Don't add duplicates */
    لكل (صحيح i = 0; i < e->nb_چوکٺو_deps; i++)
        إذا (e->چوکٺو_deps[i]->معلومات[0] == f->معلومات[0])
            أرجع 1;

    av_assert1(e->nb_چوکٺو_deps < FF_VK_EXEC_MAX_چوکٺو_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    إذا (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_بفر_ref(f->buf[0]);
        إذا (!e->buf_deps[e->nb_buf_deps])
            أرجع AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->چوکٺو_deps[e->nb_چوکٺو_deps] = f;

    vkfc->تالو_چوکٺو(hwfc, vkf);
    e->چوکٺو_locked[e->nb_چوکٺو_deps] = 1;
    e->چوکٺو_update[e->nb_چوکٺو_deps] = 0;
    e->nb_چوکٺو_deps++;

    لكل (صحيح i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .قدر = vkf->sem_قدر[i],
            .stage_نقاب = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .قدر = vkf->sem_قدر[i] + 1,
            .stage_نقاب = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_قدر[i];
        e->sem_sig_val_dst_cnt++;
    }

    أرجع 0;
}

فراغ ff_vk_exec_update_چوکٺو(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_يادگيري_Barrier2 *bar, uint32_t *nb_img_bar)
{
    صحيح i;
    لكل (i = 0; i < e->nb_چوکٺو_deps; i++)
        إذا (e->چوکٺو_deps[i]->معلومات[0] == f->معلومات[0])
            اكسر;
    av_assert0(i < e->nb_چوکٺو_deps);

    /* Don't update duplicates */
    إذا (nb_img_bar && !e->چوکٺو_update[i])
        (*nb_img_bar)++;

    e->قطار_family_dst[i] = bar->dst_قطار_Family_اشاريو;
    e->access_dst[i] = bar->dst_Access_نقاب;
    e->layout_dst[i] = bar->newLayout;
    e->چوکٺو_update[i] = 1;
}

صحيح ff_vk_exec_mirror_sem_قدر(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];

    /* Reject unknown frames */
    صحيح i;
    لكل (i = 0; i < e->nb_چوکٺو_deps; i++)
        إذا (e->چوکٺو_deps[i]->معلومات[0] == f->معلومات[0])
            اكسر;
    إذا (i == e->nb_چوکٺو_deps)
        أرجع AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_قدر[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    أرجع 0;
}

صحيح ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_بفر_Submit_Info cmd_buf_info = (Vk_Command_بفر_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_SUBMIT_INFO,
        .command_بفر = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_بفر_Infos = &cmd_buf_info,
        .command_بفر_Info_ڳڻپ = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_ڳڻپ = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_ڳڻپ = e->sem_sig_cnt,
    };

    ret = vk->پڇاڙي_Command_بفر(e->buf);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        أرجع AVERROR_EXTERNAL;
    }

#إذا FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->تالو_قطار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#جيڪڏهن_پورو
    ret = vk->قطار_Submit2(e->قطار, 1, &submit_info, VK_NULL_HANDLE);
#إذا FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_قطار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#جيڪڏهن_پورو

    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        أرجع AVERROR_EXTERNAL;
    }

    لكل (صحيح i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    لكل (صحيح j = 0; j < e->nb_چوکٺو_deps; j++) {
        إذا (e->چوکٺو_locked[j]) {
            AVFrame *f = e->چوکٺو_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
            AVVulkan_چوکٺا_Context *vkfc = hwfc->hwctx;
            AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];

            إذا (e->چوکٺو_update[j]) {
                صحيح nb_images = ff_vk_ڳڻپ_images(vkf);
                لكل (صحيح i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->قطار_family[i] = e->قطار_family_dst[j];
                }
            }
            vkfc->unlock_چوکٺو(hwfc, vkf);
            e->چوکٺو_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    أرجع 0;
}

صحيح ff_vk_alloc_mem(FFVulkanContext *s, Vk_يادگيري_Requirements *req,
                    Vk_يادگيري_Property_Flag_بٽ req_flags, فراغ *alloc_extension,
                    Vk_يادگيري_Property_Flag_بٽ *mem_flags, Vk_Device_يادگيري *mem)
{
    Vk_نتيجو ret;
    صحيح اشاريو = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_يادگيري_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_يادگيري_ALLOCATE_INFO,
        .p_ايندڙ           = alloc_extension,
    };

    alloc_info.ورهاست_سائيز = req->سائيز;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    لكل (صحيح i = 0; i < s->mprops.يادگيري_Type_ڳڻپ; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        إذا (!(req->يادگيري_Type_بٽ & (1 << i)))
            استمر;

        /* The memory type flags must include our properties */
        إذا ((req_flags != UINT32_MAX) &&
            ((s->mprops.يادگيري_Types[i].propertyFlags & req_flags) != req_flags))
            استمر;

        /* Found a suitable memory type */
        اشاريو = i;
        اكسر;
    }

    إذا (اشاريو < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        أرجع AVERROR(EINVAL);
    }

    alloc_info.يادگيري_Type_اشاريو = اشاريو;

    ret = vk->Allocate_يادگيري(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    إذا (ret != VK_SUCCESS)
        أرجع AVERROR(ENOMEM);

    إذا (mem_flags)
        *mem_flags |= s->mprops.يادگيري_Types[اشاريو].propertyFlags;

    أرجع 0;
}

صحيح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_يادگيري *mem,
                       صحيح ويڪر, صحيح اوچائي, VkFormat format, صحيح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, فراغ *create_pnext)
{
    صحيح err;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_يادگيري_Property_Flag_بٽ mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_ايندڙ         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { ويڪر, اوچائي, 1 },
        .mip_سطحون     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_ڳڻپ_1_ٻٽو_انگ,
        .sharing_گهڻائي   = VK_SHARING_گهڻائي_EXCLUSIVE,
    };
    Vk_يادگيري_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_ALLOCATE_INFO,
    };
    Vk_يادگيري_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_REQUIREMENTS_2,
    };
    Vk_Image_يادگيري_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_يادگيري_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_يادگيري_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_يادگيري_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_يادگيري_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.يادگيري_Requirements,
                          VK_يادگيري_PROPERTY_DEVICE_LOCAL_ٻٽو_انگ,
                          &ded_alloc, &mem_flags, mem);
    إذا (err < 0)
        اذهب fail;

    bind_info.image  = *img;
    bind_info.يادگيري = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        اذهب fail;
    }

    أرجع 0;

fail:
    ff_vk_image_free(s, img, mem);
    أرجع err;
}

فراغ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_يادگيري *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    إذا (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    إذا (*mem) {
        vk->Free_يادگيري(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

صحيح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t سائيز,
                     فراغ *p_ايندڙ, فراغ *alloc_p_ايندڙ,
                     Vk_بفر_Usage_Flags usage, Vk_يادگيري_Property_Flag_بٽ flags)
{
    صحيح err;
    Vk_نتيجو ret;
    صحيح use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_ايندڙ       = p_ايندڙ,
        .usage       = usage,
        .sharing_گهڻائي = VK_SHARING_گهڻائي_EXCLUSIVE,
        .سائيز        = flags & VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ ?
                       FFALIGN(سائيز, s->props.properties.limits.min_يادگيري_Map_Alignment) :
                       سائيز,
    };

    Vk_يادگيري_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_ALLOCATE_FLAGS_INFO,
        .flags = VK_يادگيري_ALLOCATE_DEVICE_پتو_ٻٽو_انگ,
    };
    Vk_بفر_يادگيري_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_بفر_يادگيري_REQUIREMENTS_INFO_2,
    };
    Vk_يادگيري_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_ALLOCATE_INFO,
        .p_ايندڙ = alloc_p_ايندڙ,
    };
    Vk_يادگيري_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_REQUIREMENTS,
    };
    Vk_يادگيري_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_REQUIREMENTS_2,
        .p_ايندڙ = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           سائيز, usage, flags);

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    req_desc.بفر = buf->buf;

    vk->Get_بفر_يادگيري_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_ورهاست |
                  ded_req.requires_Dedicated_ورهاست;
    إذا (use_ded_mem) {
        ded_alloc.بفر = buf->buf;
        ded_alloc.p_ايندڙ = alloc_p_ايندڙ;
        alloc_p_ايندڙ = &ded_alloc;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پتو_ٻٽو_انگ) {
        alloc_flags.p_ايندڙ = alloc_p_ايندڙ;
        alloc_p_ايندڙ = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.يادگيري_Requirements, flags, alloc_p_ايندڙ,
                          &buf->flags, &buf->mem);
    إذا (err)
        أرجع err;

    ret = vk->Bind_بفر_يادگيري(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پتو_ٻٽو_انگ) {
        Vk_بفر_Device_پتو_Info پتو_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پتو_INFO,
            .بفر = buf->buf,
        };
        buf->پتو = vk->Get_بفر_Device_پتو(s->hwctx->act_dev, &پتو_info);
    }

    buf->سائيز = سائيز;

    أرجع 0;
}

صحيح ff_vk_map_buffers(FFVulkanContext *s, FFVk_بفر **buf, uint8_t *mem[],
                      صحيح nb_buffers, صحيح invalidate)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_يادگيري_Range inval_list[64];
    صحيح inval_ڳڻپ = 0;

    لكل (صحيح i = 0; i < nb_buffers; i++) {
        فراغ *dst;
        ret = vk->Map_يادگيري(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_سڄو_سائيز, 0, &dst);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        إذا (mem)
            mem[i] = dst;
    }

    إذا (!invalidate)
        أرجع 0;

    لكل (صحيح i = 0; i < nb_buffers; i++) {
        ثابت Vk_Mapped_يادگيري_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_يادگيري_RANGE,
            .يادگيري = buf[i]->mem,
            .سائيز   = VK_سڄو_سائيز,
        };
        إذا (buf[i]->flags & VK_يادگيري_PROPERTY_HOST_COHERENT_ٻٽو_انگ)
            استمر;
        inval_list[inval_ڳڻپ++] = ival_buf;
    }

    إذا (inval_ڳڻپ) {
        ret = vk->Invalidate_Mapped_يادگيري_Ranges(s->hwctx->act_dev, inval_ڳڻپ,
                                               inval_list);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }
    }

    أرجع 0;
}

صحيح ff_vk_flush_بفر(FFVulkanContext *s, FFVk_بفر *buf,
                       Vk_Device_سائيز وٿي, Vk_Device_سائيز mem_سائيز,
                       صحيح flush)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    إذا (buf->flags & VK_يادگيري_PROPERTY_HOST_COHERENT_ٻٽو_انگ)
        أرجع 0;

    ثابت Vk_Mapped_يادگيري_Range flush_معلومات = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_يادگيري_RANGE,
        .يادگيري = buf->mem,
        .وٿي = وٿي,
        .سائيز   = mem_سائيز,
    };

    إذا (flush)
        ret = vk->Flush_Mapped_يادگيري_Ranges(s->hwctx->act_dev, 1, &flush_معلومات);
    وإلا
        ret = vk->Invalidate_Mapped_يادگيري_Ranges(s->hwctx->act_dev, 1, &flush_معلومات);

    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

صحيح ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_بفر **buf, صحيح nb_buffers,
                        صحيح flush)
{
    صحيح err = 0;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_يادگيري_Range flush_list[64];
    صحيح flush_ڳڻپ = 0;

    إذا (flush) {
        لكل (صحيح i = 0; i < nb_buffers; i++) {
            ثابت Vk_Mapped_يادگيري_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_يادگيري_RANGE,
                .يادگيري = buf[i]->mem,
                .سائيز   = VK_سڄو_سائيز,
            };

            av_assert0(!buf[i]->host_ref);
            إذا (buf[i]->flags & VK_يادگيري_PROPERTY_HOST_COHERENT_ٻٽو_انگ)
                استمر;
            flush_list[flush_ڳڻپ++] = flush_buf;
        }
    }

    إذا (flush_ڳڻپ) {
        ret = vk->Flush_Mapped_يادگيري_Ranges(s->hwctx->act_dev, flush_ڳڻپ,
                                          flush_list);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    لكل (صحيح i = 0; i < nb_buffers; i++) {
        vk->Unmap_يادگيري(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = عدم;
    }

    أرجع err;
}

فراغ ff_vk_free_buf(FFVulkanContext *s, FFVk_بفر *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    إذا (!buf || !s->hwctx)
        أرجع;

    إذا (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_بفر(s, buf, 0);
    إذا (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_بفر(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    إذا (buf->mem != VK_NULL_HANDLE)
        vk->Free_يادگيري(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    إذا (buf->host_ref)
        av_بفر_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = عدم;
}

ساكن فراغ pooled_buf_free(AVRefStructOpaque opaque, فراغ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

صحيح ff_vk_get_pooled_بفر(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_بفر **buf, Vk_بفر_Usage_Flags usage,
                            فراغ *create_p_ايندڙ, size_t سائيز,
                            Vk_يادگيري_Property_Flag_بٽ mem_props)
{
    صحيح err;
    FFVk_بفر *معلومات;

    إذا (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(حجم(FFVk_بفر), 0, ctx,
                                                عدم, عدم, pooled_buf_free,
                                                عدم);
        إذا (!(*buf_pool))
            أرجع AVERROR(ENOMEM);
    }

    *buf = معلومات = av_refstruct_pool_get(*buf_pool);
    إذا (!معلومات)
        أرجع AVERROR(ENOMEM);

    إذا (معلومات->سائيز >= سائيز)
        أرجع 0;

    ff_vk_free_buf(ctx, معلومات);
    memset(معلومات, 0, حجم(*معلومات));

    err = ff_vk_create_buf(ctx, معلومات, سائيز,
                           create_p_ايندڙ, عدم, usage,
                           mem_props);
    إذا (err < 0) {
        av_refstruct_unref(buf);
        أرجع err;
    }

    إذا (mem_props & VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ) {
        err = ff_vk_map_بفر(ctx, معلومات, &معلومات->mapped_mem, 0);
        إذا (err < 0) {
            av_refstruct_unref(buf);
            أرجع err;
        }
    }

    أرجع 0;
}

ساكن صحيح create_mapped_بفر(FFVulkanContext *s,
                                FFVk_بفر *vkb, Vk_بفر_Usage_Flags usage,
                                size_t سائيز,
                                Vk_External_يادگيري_بفر_Create_Info *create_desc,
                                Vk_Import_يادگيري_Host_اشارو_Info_EXT *import_desc,
                                Vk_يادگيري_Host_اشارو_Properties_EXT props)
{
    صحيح err;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_ايندڙ       = create_desc,
        .usage       = usage,
        .sharing_گهڻائي = VK_SHARING_گهڻائي_EXCLUSIVE,
        .سائيز        = سائيز,
    };
    Vk_يادگيري_Requirements req = {
        .سائيز           = سائيز,
        .alignment      = s->hprops.min_Imported_Host_اشارو_Alignment,
        .يادگيري_Type_بٽ = props.يادگيري_Type_بٽ,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ,
                          import_desc, &vkb->flags, &vkb->mem);
    إذا (err < 0)
        أرجع err;

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    إذا (ret != VK_SUCCESS) {
        vk->Free_يادگيري(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        أرجع AVERROR_EXTERNAL;
    }

    ret = vk->Bind_بفر_يادگيري(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    إذا (ret != VK_SUCCESS) {
        vk->Free_يادگيري(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_بفر(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن فراغ host_map_free(AVRefStructOpaque opaque, فراغ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

صحيح ff_vk_host_map_بفر(FFVulkanContext *s, FFVk_بفر **dst,
                          uint8_t *src_معلومات, Vk_Device_سائيز سائيز,
                          ثابت AVBufferRef *src_buf,
                          Vk_بفر_Usage_Flags usage)
{
    صحيح err;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_يادگيري_بفر_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_يادگيري_بفر_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_يادگيري_HANDLE_TYPE_HOST_ورهاست_ٻٽو_انگ_EXT,
    };
    Vk_يادگيري_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_يادگيري_ALLOCATE_FLAGS_INFO,
        .flags = VK_يادگيري_ALLOCATE_DEVICE_پتو_ٻٽو_انگ,
    };
    Vk_Import_يادگيري_Host_اشارو_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_يادگيري_HOST_اشارو_INFO_EXT,
        .handleType = VK_EXTERNAL_يادگيري_HANDLE_TYPE_HOST_ورهاست_ٻٽو_انگ_EXT,
        .p_ايندڙ = usage & VK_بفر_USAGE_SHADER_DEVICE_پتو_ٻٽو_انگ ? &alloc_flags : عدم,
    };
    Vk_يادگيري_Host_اشارو_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_بفر *vkb;
    size_t offs;
    size_t بفر_سائيز;

    *dst = عدم;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_معلومات % s->hprops.min_Imported_Host_اشارو_Alignment;
    import_desc.p_Host_اشارو = src_معلومات - offs;

    props = (Vk_يادگيري_Host_اشارو_Properties_EXT) {
        VK_STRUCTURE_TYPE_يادگيري_HOST_اشارو_PROPERTIES_EXT,
    };
    ret = vk->Get_يادگيري_Host_اشارو_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_اشارو,
                                                &props);
    إذا (!(ret == VK_SUCCESS && props.يادگيري_Type_بٽ))
        أرجع AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_بفر_ref(src_buf);
    إذا (!ref)
        أرجع AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ثابت Vk_Device_سائيز src_avail = src_buf->سائيز - (src_معلومات - src_buf->معلومات);
    بفر_سائيز = offs + FFMIN(سائيز, src_avail);
    بفر_سائيز = FFALIGN(بفر_سائيز, s->props.properties.limits.min_يادگيري_Map_Alignment);
    بفر_سائيز = FFALIGN(بفر_سائيز, s->hprops.min_Imported_Host_اشارو_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(حجم(*vkb), 0, s, host_map_free);
    إذا (!vkb) {
        av_بفر_unref(&ref);
        أرجع AVERROR(ENOMEM);
    }

    err = create_mapped_بفر(s, vkb, usage,
                               بفر_سائيز, &create_desc, &import_desc,
                               props);
    إذا (err < 0) {
        av_بفر_unref(&ref);
        av_refstruct_unref(&vkb);
        أرجع err;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پتو_ٻٽو_انگ) {
        Vk_بفر_Device_پتو_Info پتو_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پتو_INFO,
            .بفر = vkb->buf,
        };
        vkb->پتو = vk->Get_بفر_Device_پتو(s->hwctx->act_dev, &پتو_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_وٿي = offs;
    vkb->پتو       += offs;
    vkb->mapped_mem     = src_معلومات;
    vkb->سائيز           = بفر_سائيز - offs;

    *dst = vkb;

    أرجع 0;
}

صحيح ff_vk_shader_جوڙيو_ڌڪو_const(FFVulkanShader *shd, صحيح وٿي, صحيح سائيز,
                                Vk_Shader_Stage_Flag_بٽ stage)
{
    Vk_ڌڪو_Constant_Range *pc = &shd->ڌڪو_consts[shd->ڌڪو_consts_انگ++];
    av_assert1(shd->ڌڪو_consts_انگ < FF_VK_MAX_ڌڪو_CONSTS);
    pc->stageFlags = stage;
    pc->وٿي = وٿي;
    pc->سائيز = سائيز;
    أرجع 0;
}

صحيح ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       صحيح unnorm_coords, VkFilter filt)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_گهڻائي = (unnorm_coords || filt == VK_FILTER_سڀ_کان_ويجهو) ?
                      VK_SAMPLER_MIPMAP_گهڻائي_سڀ_کان_ويجهو :
                      VK_SAMPLER_MIPMAP_گهڻائي_لڪيري,
        .پتو_گهڻائي_U = VK_SAMPLER_پتو_گهڻائي_CLAMP_منزل_ڪنارو,
        .پتو_گهڻائي_V = sampler_info.پتو_گهڻائي_U,
        .پتو_گهڻائي_W = sampler_info.پتو_گهڻائي_U,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, صحيح p)
{
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    صحيح nb_images = ff_vk_ڳڻپ_images(vkf);
    صحيح nb_planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);

    ساكن ثابت VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_ٻٽو_انگ,
                                                       VK_IMAGE_ASPECT_PLANE_1_ٻٽو_انگ,
                                                       VK_IMAGE_ASPECT_PLANE_2_ٻٽو_انگ, };

    إذا (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        أرجع VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ;

    أرجع plane_aspect[p];
}

صحيح ff_vk_mt_is_np_rgb(تعداد AVPixelFormat pix_fmt)
{
    إذا (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        أرجع 1;
    أرجع 0;
}

فراغ ff_vk_سيٽ_perm(تعداد AVPixelFormat pix_fmt, صحيح lut[4], صحيح inv)
{
    بدل (pix_fmt) {
    حالة AV_PIX_FMT_GBRP:
    حالة AV_PIX_FMT_GBRAP:
    حالة AV_PIX_FMT_GBRAP10:
    حالة AV_PIX_FMT_GBRAP12:
    حالة AV_PIX_FMT_GBRAP14:
    حالة AV_PIX_FMT_GBRAP16:
    حالة AV_PIX_FMT_GBRAPF16:
    حالة AV_PIX_FMT_GBRP10:
    حالة AV_PIX_FMT_GBRP12:
    حالة AV_PIX_FMT_GBRP14:
    حالة AV_PIX_FMT_GBRP16:
    حالة AV_PIX_FMT_GBRPF16:
    حالة AV_PIX_FMT_GBRPF32:
    حالة AV_PIX_FMT_GBRAP32:
    حالة AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        اكسر;
    حالة AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        اكسر;
    حالة AV_PIX_FMT_BGRA:
    حالة AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        اكسر;
    افتراضي:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        اكسر;
    }

    إذا (inv) {
        صحيح lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        لكل (صحيح i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    أرجع;
}

ثابت حرف *ff_vk_shader_rep_fmt(تعداد AVPixelFormat pix_fmt,
                                 تعداد FFVkShaderRepFormat rep_fmt)
{
    بدل (pix_fmt) {
    حالة AV_PIX_FMT_RGBA:
    حالة AV_PIX_FMT_BGRA:
    حالة AV_PIX_FMT_RGB24:
    حالة AV_PIX_FMT_BGR24:
    حالة AV_PIX_FMT_BGR0:
    حالة AV_PIX_FMT_RGB0:
    حالة AV_PIX_FMT_RGB565:
    حالة AV_PIX_FMT_BGR565:
    حالة AV_PIX_FMT_UYVA:
    حالة AV_PIX_FMT_YUYV422:
    حالة AV_PIX_FMT_UYVY422: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_X2RGB10:
    حالة AV_PIX_FMT_X2BGR10:
    حالة AV_PIX_FMT_Y210:
    حالة AV_PIX_FMT_XV30: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = عدم,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_RGB48:
    حالة AV_PIX_FMT_RGBA64:
    حالة AV_PIX_FMT_Y212:
    حالة AV_PIX_FMT_Y216:
    حالة AV_PIX_FMT_XV36:
    حالة AV_PIX_FMT_XV48: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_RGBAF16: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_RGBF32:
    حالة AV_PIX_FMT_RGBAF32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_RGB96:
    حالة AV_PIX_FMT_RGBA128: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = عدم,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        أرجع rep_tab[rep_fmt];
    }
    حالة AV_PIX_FMT_GBRP:
    حالة AV_PIX_FMT_GRAY8:
    حالة AV_PIX_FMT_GBRAP:
    حالة AV_PIX_FMT_YUV420P:
    حالة AV_PIX_FMT_YUV422P:
    حالة AV_PIX_FMT_YUV444P:
    حالة AV_PIX_FMT_YUVA420P:
    حالة AV_PIX_FMT_YUVA422P:
    حالة AV_PIX_FMT_YUVA444P: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_GRAY10:
    حالة AV_PIX_FMT_GRAY12:
    حالة AV_PIX_FMT_GRAY14:
    حالة AV_PIX_FMT_GRAY16:
    حالة AV_PIX_FMT_GBRAP10:
    حالة AV_PIX_FMT_GBRAP12:
    حالة AV_PIX_FMT_GBRAP14:
    حالة AV_PIX_FMT_GBRAP16:
    حالة AV_PIX_FMT_GBRAPF16:
    حالة AV_PIX_FMT_GBRP10:
    حالة AV_PIX_FMT_GBRP12:
    حالة AV_PIX_FMT_GBRP14:
    حالة AV_PIX_FMT_GBRP16:
    حالة AV_PIX_FMT_GBRPF16:
    حالة AV_PIX_FMT_XYZP12:
    حالة AV_PIX_FMT_YUV420P10:
    حالة AV_PIX_FMT_YUV420P12:
    حالة AV_PIX_FMT_YUV420P16:
    حالة AV_PIX_FMT_YUV422P10:
    حالة AV_PIX_FMT_YUV422P12:
    حالة AV_PIX_FMT_YUV422P16:
    حالة AV_PIX_FMT_YUV444P10:
    حالة AV_PIX_FMT_YUV444P12:
    حالة AV_PIX_FMT_YUV444P16:
    حالة AV_PIX_FMT_YUVA420P10:
    حالة AV_PIX_FMT_YUVA420P16:
    حالة AV_PIX_FMT_YUVA422P10:
    حالة AV_PIX_FMT_YUVA422P12:
    حالة AV_PIX_FMT_YUVA422P16:
    حالة AV_PIX_FMT_YUVA444P10:
    حالة AV_PIX_FMT_YUVA444P12:
    حالة AV_PIX_FMT_YUVA444P16:
    حالة AV_PIX_FMT_BAYER_RGGB16: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_GRAY32:
    حالة AV_PIX_FMT_GRAYF32:
    حالة AV_PIX_FMT_GBRPF32:
    حالة AV_PIX_FMT_GBRAPF32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_GBRAP32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = عدم,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_NV12:
    حالة AV_PIX_FMT_NV16:
    حالة AV_PIX_FMT_NV24: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P210:
    حالة AV_PIX_FMT_P410: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = عدم,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    حالة AV_PIX_FMT_P012:
    حالة AV_PIX_FMT_P016:
    حالة AV_PIX_FMT_P212:
    حالة AV_PIX_FMT_P216:
    حالة AV_PIX_FMT_P412:
    حالة AV_PIX_FMT_P416: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        أرجع rep_tab[rep_fmt];
    };
    افتراضي:
        أرجع "rgba32f";
    }
}

ساكن فراغ reset_imageviews(AVRefStructOpaque اڻ_استعمال_ٿيل, فراغ *obj)
{
    FFVkImageViews *iv = obj;

    لكل (صحيح i = 0; i < iv->nb_views; i++) {
        إذا (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, حجم(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, صحيح nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_انگ_معلومات_اشارا);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    إذا (!iv)
        أرجع عدم;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    أرجع iv;
}

VkFormat ff_vk_map_fmt_منزل_rep(VkFormat fmt, تعداد FFVkShaderRepFormat rep_fmt)
{
#وصف_ڪريو REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#وصف_ڪريو REPS_FMT_PACK(fmt, انگ) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## انگ, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## انگ, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## انگ, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## انگ,

    ثابت VkFormat fmts_map[][4] = {
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
#وصف_رد REPS_FMT_PACK
#وصف_رد REPS_FMT

    إذا (fmt == VK_FORMAT_UNDEFINED)
        أرجع VK_FORMAT_UNDEFINED;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        إذا (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            أرجع fmts_map[i][rep_fmt];
    }

    أرجع VK_FORMAT_UNDEFINED;
}

صحيح ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, صحيح plane, تعداد FFVkShaderRepFormat rep_fmt)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    AVVulkan_چوکٺا_Context *vkfc = hwfc->hwctx;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_ايندڙ      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_منزل_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_سڃاڻپ_عنصر_map,
        .subresourceRange = {
            .aspect_نقاب = ff_vk_aspect_flag(f, plane),
            .level_ڳڻپ = 1,
            .layer_ڳڻپ = 1,
        },
    };
    إذا (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        أرجع AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_نقاب;

    أرجع 0;
}

صحيح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_انگ_معلومات_اشارا],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_انگ_معلومات_اشارا])
{
    صحيح err = 0;
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    AVVulkan_چوکٺا_Context *vkfc = hwfc->hwctx;
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)f->معلومات[0];
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(vkf);
    ثابت صحيح nb_planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_انگ_معلومات_اشارا] = { 0 };

    لكل (صحيح i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_ايندڙ      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_سڃاڻپ_عنصر_map,
            .subresourceRange = {
                .aspect_نقاب = ff_vk_aspect_flag(f, i),
                .level_ڳڻپ = 1,
                .layer_ڳڻپ = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    لكل (صحيح i = 0; i < nb_planes; i++)
        ff_vk_exec_جوڙيو_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    يادگيري_نقل(views, tmp_views, nb_planes*حجم(*views));

    أرجع 0;

fail:
    لكل (صحيح i = 0; i < nb_planes; i++)
        إذا (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    أرجع err;
}

صحيح ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_انگ_معلومات_اشارا],
                            AVFrame *f, تعداد FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ثابت صحيح nb_planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    VkFormat fmts[AV_انگ_معلومات_اشارا] = { 0 };

    لكل (صحيح i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_منزل_rep(rep_fmts[i], rep_fmt);
        إذا (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            أرجع AVERROR(EINVAL);
        }
    }

    أرجع ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

فراغ ff_vk_چوکٺو_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_يادگيري_Barrier2 *bar, صحيح *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    صحيح مليو = -1;
    AVVk_چوکٺو *vkf = (AVVk_چوکٺو *)pic->معلومات[0];
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(vkf);
    لكل (صحيح i = 0; i < e->nb_چوکٺو_deps; i++)
        إذا (e->چوکٺو_deps[i]->معلومات[0] == pic->معلومات[0]) {
            إذا (e->چوکٺو_update[i])
                مليو = i;
            اكسر;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    لكل (صحيح i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_يادگيري_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_يادگيري_BARRIER_2,
            .p_ايندڙ = عدم,
            .src_Stage_نقاب = src_stage,
            .dst_Stage_نقاب = dst_stage,
            .src_Access_نقاب = مليو >= 0 ? e->access_dst[مليو] : VK_ACCESS_2_NONE,
            .dst_Access_نقاب = new_access,
            .oldLayout = مليو >= 0 ? e->layout_dst[مليو] : vkf->layout[0],
            .newLayout = new_layout,
            .src_قطار_Family_اشاريو = مليو >= 0 ? e->قطار_family_dst[مليو] : vkf->قطار_family[0],
            .dst_قطار_Family_اشاريو = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_نقاب = VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ,
                .layer_ڳڻپ = 1,
                .level_ڳڻپ = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_چوکٺو(s, e, pic, &bar[*nb_bar - nb_images], عدم);
}

صحيح ff_vk_shader_ڀريو(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_سائيز[3], uint32_t required_subgroup_سائيز)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    يادگيري_نقل(shd->lg_سائيز, wg_سائيز, 3*حجم(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_سائيز_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_سائيز_CREATE_INFO,
        .required_Subgroup_سائيز = required_subgroup_سائيز,
    };

    بدل (shd->stage) {
    حالة VK_SHADER_STAGE_ANY_ڪاميابي_ٻٽو_انگ_KHR:
    حالة VK_SHADER_STAGE_CALLABLE_ٻٽو_انگ_KHR:
    حالة VK_SHADER_STAGE_CLOSEST_ڪاميابي_ٻٽو_انگ_KHR:
    حالة VK_SHADER_STAGE_INTERSECTION_ٻٽو_انگ_KHR:
    حالة VK_SHADER_STAGE_ناڪامي_ٻٽو_انگ_KHR:
    حالة VK_SHADER_STAGE_RAYGEN_ٻٽو_انگ_KHR:
        shd->bind_نقطو = VK_PIPELINE_BIND_نقطو_RAY_TRACING_KHR;
        اكسر;
    حالة VK_SHADER_STAGE_COMPUTE_ٻٽو_انگ:
        shd->bind_نقطو = VK_PIPELINE_BIND_نقطو_COMPUTE;
        اكسر;
    افتراضي:
        shd->bind_نقطو = VK_PIPELINE_BIND_نقطو_GRAPHICS;
        اكسر;
    };

    أرجع 0;
}

ساكن صحيح init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_سيٽ_Layouts            = shd->desc_layout,
        .سيٽ_Layout_ڳڻپ         = shd->nb_descriptor_sets,
        .ڌڪو_Constant_Range_ڳڻپ = shd->ڌڪو_consts_انگ,
        .p_ڌڪو_Constant_Ranges    = shd->ڌڪو_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ثابت uint8_t *spirv, size_t spirv_len)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_ايندڙ    = عدم,
        .flags    = 0x0,
        .p_ڪوڊ    = (فراغ *)spirv,
        .ڪوڊ_سائيز = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ثابت حرف *entrypoint)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_ايندڙ = shd->subgroup_info.required_Subgroup_سائيز ?
                     &shd->subgroup_info : عدم,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_سائيز ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_ڀريل_SUBGROUPS_ٻٽو_انگ : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_نتيجو ret;
    FFVulkanFunctions *vk = &s->vkfn;

    صحيح has_singular = 0;
    صحيح max_descriptors = 0;
    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_سيٽ[i].nb_bindings);
        إذا (shd->desc_سيٽ[i].singular)
            has_singular = 1;
    }
    shd->use_ڌڪو = (s->extensions & FF_VK_EXT_ڌڪو_DESCRIPTOR) &&
                    (max_descriptors <= s->ڌڪو_desc_props.max_ڌڪو_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_سيٽ *سيٽ = &shd->desc_سيٽ[i];
        Vk_Descriptor_سيٽ_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_سيٽ_LAYOUT_CREATE_INFO,
            .binding_ڳڻپ = سيٽ->nb_bindings,
            .pBindings = سيٽ->binding,
            .flags = (shd->use_ڌڪو) ?
                     VK_DESCRIPTOR_سيٽ_LAYOUT_CREATE_ڌڪو_DESCRIPTOR_ٻٽو_انگ_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_سيٽ_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }
    }

    أرجع 0;
}

صحيح ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ثابت حرف *spirv, size_t spirv_len,
                      ثابت حرف *entrypoint)
{
    صحيح err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_داخلا spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t داخلا_سائيز_2 = spirv_len;

    إذا (shd->precompiled) {
        إذا (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_داخلا_ڳڻپ = 0,
                .p_معلومات = shd->lg_سائيز,
                .معلومات_سائيز_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_داخلا *spe = (فراغ *)shd->specialization_info->pMapEntries;
        لكل (صحيح i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_داخلا_ڳڻپ++] = (Vk_Specialization_Map_داخلا) {
                .constantID = 253 + i,
                .وٿي = shd->specialization_info->معلومات_سائيز_2 + i*حجم(uint32_t),
                .سائيز = حجم(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_معلومات;
        يادگيري_نقل(&spd[shd->specialization_info->معلومات_سائيز_2],
               shd->lg_سائيز, 3*حجم(uint32_t));
        shd->specialization_info->معلومات_سائيز_2 += 3*حجم(uint32_t);

#إذا CONFIG_SHADER_COMPRESSION
        uint8_t *ٻاهريون;
        size_t ٻاهريون_len;
        صحيح ret = ff_zlib_expand(s, &ٻاهريون, &ٻاهريون_len, spirv, spirv_len);
        إذا (ret < 0)
            أرجع ret;
        spirv = ٻاهريون;
        spirv_len = ٻاهريون_len;
#جيڪڏهن_پورو
    }

    err = init_descriptors(s, shd);
    إذا (err < 0)
        اذهب پڇاڙي;

    err = init_pipeline_layout(s, shd);
    إذا (err < 0)
        اذهب پڇاڙي;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    إذا (err < 0)
        اذهب پڇاڙي;

    بدل (shd->bind_نقطو) {
    حالة VK_PIPELINE_BIND_نقطو_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        اكسر;
    افتراضي:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_نقطو);
        err = AVERROR(EINVAL);
        اذهب پڇاڙي;
        اكسر;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    إذا (err < 0)
        اذهب پڇاڙي;

    إذا (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    وإلا
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    إذا (داخلا_سائيز_2 != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", داخلا_سائيز_2);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

پڇاڙي:
    إذا (shd->precompiled) {
        shd->specialization_info->map_داخلا_ڳڻپ -= 3;
        shd->specialization_info->معلومات_سائيز_2 -= 3*حجم(uint32_t);
    }
#إذا CONFIG_SHADER_COMPRESSION
    إذا (shd->precompiled)
        av_free((فراغ *)spirv);
#جيڪڏهن_پورو
    أرجع err;
}

فراغ ff_vk_shader_جوڙيو_descriptor_سيٽ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سيٽ_Binding *desc, صحيح nb,
                                     صحيح singular)
{
    FFVulkan_Descriptor_سيٽ *سيٽ = &shd->desc_سيٽ[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    لكل (صحيح i = 0; i < nb; i++) {
        سيٽ->binding[i].binding            = i;
        سيٽ->binding[i].descriptorType     = desc[i].type;
        سيٽ->binding[i].descriptor_ڳڻپ    = FFMAX(desc[i].elems, 1);
        سيٽ->binding[i].stageFlags         = desc[i].stages;
        سيٽ->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    لكل (صحيح i = 0; i < nb; i++) {
        صحيح j;
        لكل (j = 0; j < shd->nb_desc_pool_سائيز; j++)
            إذا (shd->desc_pool_سائيز[j].type == desc[i].type)
                اكسر;
        إذا (j >= shd->nb_desc_pool_سائيز) {
            shd->nb_desc_pool_سائيز++;
            av_assert1(shd->nb_desc_pool_سائيز < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_سائيز[j].type             = desc[i].type;
        shd->desc_pool_سائيز[j].descriptor_ڳڻپ += FFMAX(desc[i].elems, 1);
    }

    سيٽ->singular = singular;
    سيٽ->nb_bindings = nb;
}

صحيح ff_vk_shader_رجسٽر_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    إذا (!shd->nb_descriptor_sets)
        أرجع 0;

    FFVulkan_Shader_معلومات *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    إذا (!shd->use_ڌڪو) {
        Vk_نتيجو ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_سيٽ_Layout *tmp_layouts;
        Vk_Descriptor_سيٽ_Allocate_Info سيٽ_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        لكل (صحيح i = 0; i < shd->nb_desc_pool_سائيز; i++)
            shd->desc_pool_سائيز[i].descriptor_ڳڻپ *= pool->pool_سائيز;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_سائيز,
            .pool_سائيز_ڳڻپ = shd->nb_desc_pool_سائيز,
            .maxSets = sd->nb_descriptor_sets*pool->pool_سائيز,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, حجم(*tmp_layouts));
        إذا (!tmp_layouts)
            أرجع AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        لكل (صحيح i = 0; i < pool->pool_سائيز; i++)
            لكل (صحيح j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        سيٽ_alloc_info = (Vk_Descriptor_سيٽ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_سيٽ_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_سيٽ_Layouts        = tmp_layouts,
            .descriptor_سيٽ_ڳڻپ = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        حجم(*tmp_layouts));
        إذا (!sd->desc_sets) {
            av_free(tmp_layouts);
            أرجع AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &سيٽ_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            أرجع AVERROR_EXTERNAL;
        }
    }

    أرجع 0;
}

ساكن مضمن ثابت FFVulkan_Shader_معلومات *get_shd_معلومات(FFVkExecContext *e,
                                                     ثابت FFVulkanShader *shd)
{
    لكل (صحيح i = 0; i < e->والد->nb_reg_shd; i++)
        إذا (e->والد->reg_shd[i].shd == shd)
            أرجع &e->والد->reg_shd[i];
    أرجع عدم;
}

ساكن مضمن فراغ update_سيٽ_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, صحيح سيٽ,
                                         Vk_Write_Descriptor_سيٽ *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_سيٽ *desc_سيٽ = &shd->desc_سيٽ[سيٽ];
    ثابت FFVulkan_Shader_معلومات *sd = get_shd_معلومات(e, shd);

    إذا (desc_سيٽ->singular) {
        لكل (صحيح i = 0; i < e->والد->pool_سائيز; i++) {
            write_info->dst_سيٽ = sd->desc_sets[i*sd->nb_descriptor_sets + سيٽ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, عدم);
        }
    } وإلا {
        إذا (shd->use_ڌڪو) {
            vk->Cmd_ڌڪو_Descriptor_سيٽ_KHR(e->buf,
                                        shd->bind_نقطو,
                                        shd->pipeline_layout,
                                        سيٽ, 1,
                                        write_info);
        } وإلا {
            write_info->dst_سيٽ = sd->desc_sets[e->idx*sd->nb_descriptor_sets + سيٽ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, عدم);
        }
    }
}

صحيح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحيح سيٽ, صحيح bind, صحيح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_سيٽ *desc_سيٽ = &shd->desc_سيٽ[سيٽ];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_سيٽ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سيٽ,
        .dstBinding = bind,
        .descriptor_ڳڻپ = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_سيٽ->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_سيٽ_pool_write(s, e, shd, سيٽ, &desc_pool_write_info);

    أرجع 0;
}

فراغ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحيح سيٽ, صحيح binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکٺا_ctx->معلومات;
    ثابت صحيح nb_planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);

    لكل (صحيح i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, سيٽ, binding, i,
                                views[i], layout, sampler);
}

صحيح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحيح سيٽ, صحيح bind, صحيح elem,
                                    FFVk_بفر *buf, Vk_Device_سائيز وٿي, Vk_Device_سائيز len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_سيٽ *desc_سيٽ = &shd->desc_سيٽ[سيٽ];

    Vk_Descriptor_بفر_Info desc_pool_write_info_buf = {
        .بفر = buf->buf,
        .وٿي = buf->virtual_وٿي + وٿي,
        .range = len,
    };
    Vk_Write_Descriptor_سيٽ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سيٽ,
        .dstBinding = bind,
        .descriptor_ڳڻپ = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_سيٽ->binding[bind].descriptorType,
        .p_بفر_Info = &desc_pool_write_info_buf,
    };
    update_سيٽ_pool_write(s, e, shd, سيٽ, &desc_pool_write_info);

    أرجع 0;
}

فراغ ff_vk_shader_update_ڌڪو_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بٽ stage,
                                    صحيح وٿي, size_t سائيز, فراغ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ڌڪو_Constants(e->buf, shd->pipeline_layout,
                         stage, وٿي, سائيز, src);
}

فراغ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ثابت FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVulkan_Shader_معلومات *sd = get_shd_معلومات(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_نقطو, shd->pipeline);

    إذا (sd && sd->nb_descriptor_sets) {
        إذا (!shd->use_ڌڪو) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_نقطو, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, عدم);
        }
    }
}

فراغ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#إذا 0
    إذا (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#جيڪڏهن_پورو

    إذا (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    إذا (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++)
        إذا (shd->desc_layout[i])
            vk->Destroy_Descriptor_سيٽ_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

فراغ ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#جيڪڏهن_پورو
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_بفر_unref(&s->device_ref);
    av_بفر_unref(&s->چوکٺا_ref);
}

صحيح ff_vk_init(FFVulkanContext *s, فراغ *log_والد,
               AVBufferRef *device_ref, AVBufferRef *چوکٺا_ref)
{
    صحيح err;

    ساكن ثابت AVClass vulkan_context_class = {
        .class_name       = "vk",
        .نسخو          = LIBAVUTIL_نسخو_INT,
        .والد_log_context_وٿي = offsetof(FFVulkanContext, log_والد),
    };

    memset(s, 0, حجم(*s));
    s->log_والد = log_والد;
    s->class      = &vulkan_context_class;

    إذا (چوکٺا_ref) {
        s->چوکٺا_ref = av_بفر_ref(چوکٺا_ref);
        إذا (!s->چوکٺا_ref)
            أرجع AVERROR(ENOMEM);

        s->چوکٺا = (AVHWFramesContext *)s->چوکٺا_ref->معلومات;
        s->hwfc = s->چوکٺا->hwctx;

        device_ref = s->چوکٺا->device_ref;
    }

    s->device_ref = av_بفر_ref(device_ref);
    إذا (!s->device_ref) {
        ff_vk_uninit(s);
        أرجع AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->معلومات;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_منزل_نقاب(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_منزل_نقاب(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_ڀريو_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    إذا (err < 0) {
        ff_vk_uninit(s);
        أرجع err;
    }

    err = ff_vk_ڀريو_props(s);
    إذا (err < 0) {
        ff_vk_uninit(s);
        أرجع err;
    }

    أرجع 0;
}
