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
#د_که_پای

ثابت VkComponentMapping ff_comp_بې_اغېزه_عنصر_map = {
    .r = VK_COMPONENT_SWIZZLE_بې_اغېزه_عنصر,
    .g = VK_COMPONENT_SWIZZLE_بې_اغېزه_عنصر,
    .b = VK_COMPONENT_SWIZZLE_بې_اغېزه_عنصر,
    .a = VK_COMPONENT_SWIZZLE_بې_اغېزه_عنصر,
};

/* Converts return values to strings */
ثابت حرف *ff_vk_ret2str(Vk_پایله res)
{
#تعریف_کړه CASE(VAL) حالة VAL: أرجع #VAL
    بدل (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_سېټ);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_بهر_د_HOST_حافظه);
    CASE(VK_ERROR_بهر_د_DEVICE_حافظه);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_ورک);
    CASE(VK_ERROR_حافظه_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_بهر_د_POOL_حافظه);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_پته);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_ورک_KHR);
    CASE(VK_ERROR_NATIVE_کړکۍ_دننه_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_بهر_د_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_نسخه_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_ډک_SCREEN_EXCLUSIVE_ډېرپېښ_ورک_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_بشپړ_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    افتراضي: أرجع "Unknown error";
    }
#تعریف_لغوه CASE
}

/* Malitia pura, Khronos */
#تعریف_کړه FN_MAP_منزل(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## منزل_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_منزل(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_بټ,                   \
               VK_IMAGE_USAGE_SAMPLED_بټ);                             \
        MAP_منزل(VK_FORMAT_FEATURE_2_TRANSFER_SRC_بټ,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_بټ);                        \
        MAP_منزل(VK_FORMAT_FEATURE_2_TRANSFER_DST_بټ,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_بټ);                        \
        MAP_منزل(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_بټ,                   \
               VK_IMAGE_USAGE_STORAGE_بټ);                             \
        MAP_منزل(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_بټ,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_بټ);                    \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_بټ_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_بټ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_بټ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_بټ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_بټ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_بټ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ننوت_بټ_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_بټ_KHR);                \
        MAP_منزل(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_بټ_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_بټ_EXT);                   \
        أرجع dst;                                                     \
    }

#تعریف_کړه MAP_منزل(flag1, flag2) إذا (src & flag2) dst |= flag1;
FN_MAP_منزل(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#تعریف_لغوه MAP_منزل
#تعریف_کړه MAP_منزل(flag1, flag2) إذا (src & flag1) dst |= flag2;
FN_MAP_منزل(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#تعریف_لغوه MAP_منزل
#تعریف_لغوه FN_MAP_منزل

ساكن فراغ بارول_enabled_qfs(FFVulkanContext *s)
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

ساكن فراغ reset_imageviews(AVRefStructOpaque ناکارول_شوی, فراغ *obj);

صحيح ff_vk_بارول_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_اندازه_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ټېل_desc_props, FF_VK_EXT_ټېل_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ټېل_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_حافظه,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_حافظه_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_ماتریکس_props, FF_VK_EXT_COOP_ماتریکس,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ماتریکس_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#که_تعریف_شوی VK_EXT_shader_long_ویکټور
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_ویکټور_props, FF_VK_EXT_LONG_ویکټور,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ویکټور_PROPERTIES_EXT);
#د_که_پای

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#که_تعریف_شوی VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#د_که_پای
#که_تعریف_شوی VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#د_که_پای

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
    s->host_image_props.copy_Src_Layout_شمېر = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_شمېر = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    إذا (s->host_image_props.copy_Src_Layout_شمېر == 512 ||
        s->host_image_props.copy_Dst_Layout_شمېر == 512) {
        VkImageLayout *new_array;
        size_t new_اندازه;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = عدم;
        s->host_image_props.copy_Src_Layout_شمېر =
        s->host_image_props.copy_Dst_Layout_شمېر = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_اندازه = s->host_image_props.copy_Src_Layout_شمېر +
                   s->host_image_props.copy_Dst_Layout_شمېر;
        new_اندازه *= حجم(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_اندازه);
        إذا (!new_array)
            أرجع AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_شمېر;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_حافظه_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    لكل (صحيح i = 0; i < s->mprops.حافظه_Type_شمېر; i++)
        s->host_cached_flag |= s->mprops.حافظه_Types[i].propertyFlags &
                               VK_حافظه_PROPERTY_HOST_CACHED_بټ;

    بارول_enabled_qfs(s);

    إذا (s->qf_props)
        أرجع 0;

    vk->Get_Physical_Device_کتار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, عدم);

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

#که_تعریف_شوی VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, حجم(*s->ownership_props));
    إذا (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        أرجع AVERROR(ENOMEM);
    }
#د_که_پای

    لكل (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_کتار_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_کتار_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_کتار,
                         VK_STRUCTURE_TYPE_کتار_FAMILY_QUERY_پایله_حالت_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_کتار,
                         VK_STRUCTURE_TYPE_کتار_FAMILY_VIDEO_PROPERTIES_KHR);
#که_تعریف_شوی VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_کتار_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#د_که_پای
    }

    vk->Get_Physical_Device_کتار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    إذا (s->extensions & FF_VK_EXT_COOP_ماتریکس) {
        vk->Get_Physical_Device_Cooperative_ماتریکس_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, عدم);

        إذا (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                حجم(Vk_Cooperative_ماتریکس_Properties_KHR));
            لكل (صحيح i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_ماتریکس_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_ماتریکس_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_ماتریکس_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    أرجع 0;
}

AVVulkan_Device_کتار_Family *ff_vk_qf_پیدا_کړه(FFVulkanContext *s,
                                         Vk_کتار_Flag_بټونه dev_family,
                                         Vk_Video_Codec_Operation_Flag_بټونه_KHR vid_ops)
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

    لكل (صحيح i = 0; i < pool->pool_اندازه; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        إذا (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_شمېر = 1,
                .pSemaphores = &e->sem,
                .p_ارزښتونه = &e->sem_ارزښت,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->قلف);
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

    لكل (صحيح i = 0; i < pool->pool_اندازه; i++) {
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
    pool->pool_اندازه = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ساكن atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)عدم)->qf)];
ساكن AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ساكن فراغ exec_pool_phase_تخم(فراغ)
{
    uint32_t تخم = av_get_random_تخم();
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], تخم, memory_order_relaxed);
}

صحيح ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_کتار_Family *qf,
                         FFVkExecPool *pool, صحيح nb_contexts,
                         صحيح nb_queries, VkQueryType query_type, صحيح query_64bit,
                         ثابت فراغ *query_create_pnext)
{
    صحيح err;
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_بفر_Allocate_Info cbuf_create;

    ثابت VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = عدم;

    atomic_init(&pool->idx, 0);

    إذا (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_پیدا_کړه_struct(query_create_pnext,
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
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_بټ |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_بفر_بټ,
            .کتار_Family_شاخص   = qf->idx,
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
            .command_بفر_شمېر = 1,
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
            .p_بل = query_create_pnext,
            .queryType = query_type,
            .query_شمېر = nb_queries*nb_contexts,
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
        } وإلا إذا (query_type == VK_QUERY_TYPE_پایله_حالت_ONLY_KHR) {
            pool->query_حالت_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_اندازه = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_معلومات = av_calloc(nb_contexts, pool->qd_اندازه);
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

    pool->pool_اندازه = nb_contexts;

    لكل (صحيح i = 0; i < pool->pool_اندازه; i++)
        pthread_mutex_init(&pool->contexts[i].قلف, عدم);

#که_تعریف_شوی VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    صحيح دننی_کتار_sync = 0;
    إذا (s->extensions & FF_VK_EXT_دننی_کتار_SYNC) {
        ثابت VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_پیدا_کړه_struct(s->hwctx->device_features.p_بل,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        دننی_کتار_sync = iqs && iqs->internallySynchronizedQueues;
    }
#د_که_پای

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_تخم);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    صحيح pin_کتار = qf->flags & (VK_کتار_VIDEO_DECODE_بټ_KHR |
                                 VK_کتار_VIDEO_ENCODE_بټ_KHR);

    /* Init contexts */
    لكل (صحيح i = 0; i < pool->pool_اندازه; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_بل = &sem_type,
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
        e->پلار = pool;

        /* Query data */
        e->query_معلومات = ((uint8_t *)pool->query_معلومات) + pool->qd_اندازه*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_کتار ? phase % qf->عدد : (i + phase) % qf->عدد;
        e->qf = qf->idx;
        Vk_Device_کتار_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_کتار_INFO_2,
#که_تعریف_شوی VK_KHR_internally_synchronized_queues
            .flags            = دننی_کتار_sync ?
                                VK_DEVICE_کتار_CREATE_INTERNALLY_SYNCHRONIZED_بټ_KHR : 0,
#د_که_پای
            .کتار_Family_شاخص = qf->idx,
            .کتار_شاخص       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->کتار);
    }

    أرجع 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    أرجع err;
}

Vk_پایله ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              فراغ **معلومات, Vk_Query_پایله_Flag_بټونه flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->پلار;
    Vk_Query_پایله_Flags qf = flags & ~(VK_QUERY_پایله_64_بټ |
                                      VK_QUERY_پایله_WITH_حالت_بټ_KHR);

    إذا (!e->query_معلومات) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        أرجع VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_پایله_64_بټ : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_پایله_WITH_حالت_بټ_KHR : 0x0;

    إذا (معلومات)
        *معلومات = e->query_معلومات;

    أرجع vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_اندازه, e->query_معلومات,
                                   pool->qd_اندازه, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    لكل (صحيح i = 0; i < pool->pool_اندازه; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        إذا (pthread_mutex_trylock(&e->قلف))
            استمر; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        إذا (vk->Get_Semaphore_Counter_ارزښت(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_ارزښت &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_چوکاټ_deps || e->nb_sw_چوکاټ_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->قلف);
    }

    أرجع &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_اندازه];
}

فراغ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_شمېر = 1,
        .pSemaphores = &e->sem,
        .p_ارزښتونه = &e->sem_ارزښت,
    };
    pthread_mutex_قلف(&e->قلف);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->قلف);
}

صحيح ff_vk_exec_پیل(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->پلار;

    Vk_Command_بفر_Begin_Info cmd_پیل = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_BEGIN_INFO,
        .flags = VK_COMMAND_بفر_USAGE_ONE_وخت_SUBMIT_بټ,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_شمېر = 1,
        .pSemaphores = &e->sem,
        .p_ارزښتونه = &e->sem_ارزښت,
    };

    pthread_mutex_قلف(&e->قلف);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_بفر(e->buf, &cmd_پیل);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->قلف);
        أرجع AVERROR_EXTERNAL;
    }

    إذا (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_ارزښت++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .ارزښت = e->sem_ارزښت,
        .stage_ماسک = VK_PIPELINE_STAGE_2_ALL_COMMANDS_بټ,
    };

    pthread_mutex_unlock(&e->قلف);

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

    لكل (صحيح j = 0; j < e->nb_sw_چوکاټ_deps; j++)
        av_چوکاټ_free(&e->sw_چوکاټ_deps[j]);
    e->nb_sw_چوکاټ_deps = 0;

    لكل (صحيح j = 0; j < e->nb_چوکاټ_deps; j++) {
        AVFrame *f = e->چوکاټ_deps[j];
        إذا (e->چوکاټ_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
            AVVulkan_چوکاټونه_Context *vkfc = hwfc->hwctx;
            AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];
            vkfc->unlock_چوکاټ(hwfc, vkf);
            e->چوکاټ_locked[j] = 0;
        }
        e->چوکاټ_update[j] = 0;
    }
    e->nb_چوکاټ_deps = 0;

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
        .ارزښت = e->sem_ارزښت,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_بفر(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

فراغ ff_vk_exec_جمع_کړه_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
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

فراغ ff_vk_exec_جمع_کړه_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

صحيح ff_vk_exec_جمع_کړه_dep_sw_چوکاټ(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_چوکاټ_deps < FF_VK_EXEC_MAX_SW_چوکاټ_DEPS);

    e->sw_چوکاټ_deps[e->nb_sw_چوکاټ_deps] = av_چوکاټ_clone(f);
    إذا (!e->sw_چوکاټ_deps[e->nb_sw_چوکاټ_deps])
        أرجع AVERROR(ENOMEM);

    e->nb_sw_چوکاټ_deps++;

    أرجع 0;
}

فراغ ff_vk_exec_جمع_کړه_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ارزښت = val,
        .stage_ماسک = stage,
    };
}

فراغ ff_vk_exec_جمع_کړه_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ارزښت = val,
        .stage_ماسک = stage,
    };
}

فراغ ff_vk_exec_جمع_کړه_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
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
                .stage_ماسک = stage,
            };
        }

        أرجع;
    }

    /* Ownership of each semaphore passes to the execution */
    لكل (صحيح i = 0; i < nb; i++) {
        ff_vk_exec_جمع_کړه_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_جمع_کړه_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

صحيح ff_vk_exec_جمع_کړه_dep_چوکاټ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    AVVulkan_چوکاټونه_Context *vkfc = hwfc->hwctx;
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];
    صحيح nb_images = ff_vk_شمېر_images(vkf);

    /* Don't add duplicates */
    لكل (صحيح i = 0; i < e->nb_چوکاټ_deps; i++)
        إذا (e->چوکاټ_deps[i]->معلومات[0] == f->معلومات[0])
            أرجع 1;

    av_assert1(e->nb_چوکاټ_deps < FF_VK_EXEC_MAX_چوکاټ_DEPS);
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

    e->چوکاټ_deps[e->nb_چوکاټ_deps] = f;

    vkfc->قلف_چوکاټ(hwfc, vkf);
    e->چوکاټ_locked[e->nb_چوکاټ_deps] = 1;
    e->چوکاټ_update[e->nb_چوکاټ_deps] = 0;
    e->nb_چوکاټ_deps++;

    لكل (صحيح i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ارزښت = vkf->sem_ارزښت[i],
            .stage_ماسک = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ارزښت = vkf->sem_ارزښت[i] + 1,
            .stage_ماسک = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_ارزښت[i];
        e->sem_sig_val_dst_cnt++;
    }

    أرجع 0;
}

فراغ ff_vk_exec_update_چوکاټ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_حافظه_Barrier2 *bar, uint32_t *nb_img_bar)
{
    صحيح i;
    لكل (i = 0; i < e->nb_چوکاټ_deps; i++)
        إذا (e->چوکاټ_deps[i]->معلومات[0] == f->معلومات[0])
            اكسر;
    av_assert0(i < e->nb_چوکاټ_deps);

    /* Don't update duplicates */
    إذا (nb_img_bar && !e->چوکاټ_update[i])
        (*nb_img_bar)++;

    e->کتار_family_dst[i] = bar->dst_کتار_Family_شاخص;
    e->access_dst[i] = bar->dst_Access_ماسک;
    e->layout_dst[i] = bar->newLayout;
    e->چوکاټ_update[i] = 1;
}

صحيح ff_vk_exec_mirror_sem_ارزښت(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];

    /* Reject unknown frames */
    صحيح i;
    لكل (i = 0; i < e->nb_چوکاټ_deps; i++)
        إذا (e->چوکاټ_deps[i]->معلومات[0] == f->معلومات[0])
            اكسر;
    إذا (i == e->nb_چوکاټ_deps)
        أرجع AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_ارزښت[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    أرجع 0;
}

صحيح ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_بفر_Submit_Info cmd_buf_info = (Vk_Command_بفر_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_SUBMIT_INFO,
        .command_بفر = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_بفر_Infos = &cmd_buf_info,
        .command_بفر_Info_شمېر = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_شمېر = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_شمېر = e->sem_sig_cnt,
    };

    ret = vk->پای_ټکی_Command_بفر(e->buf);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        أرجع AVERROR_EXTERNAL;
    }

#إذا FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->قلف_کتار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#د_که_پای
    ret = vk->کتار_Submit2(e->کتار, 1, &submit_info, VK_NULL_HANDLE);
#إذا FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_کتار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#د_که_پای

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
    لكل (صحيح j = 0; j < e->nb_چوکاټ_deps; j++) {
        إذا (e->چوکاټ_locked[j]) {
            AVFrame *f = e->چوکاټ_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
            AVVulkan_چوکاټونه_Context *vkfc = hwfc->hwctx;
            AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];

            إذا (e->چوکاټ_update[j]) {
                صحيح nb_images = ff_vk_شمېر_images(vkf);
                لكل (صحيح i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->کتار_family[i] = e->کتار_family_dst[j];
                }
            }
            vkfc->unlock_چوکاټ(hwfc, vkf);
            e->چوکاټ_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    أرجع 0;
}

صحيح ff_vk_alloc_mem(FFVulkanContext *s, Vk_حافظه_Requirements *req,
                    Vk_حافظه_Property_Flag_بټونه req_flags, فراغ *alloc_extension,
                    Vk_حافظه_Property_Flag_بټونه *mem_flags, Vk_Device_حافظه *mem)
{
    Vk_پایله ret;
    صحيح شاخص = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_حافظه_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_حافظه_ALLOCATE_INFO,
        .p_بل           = alloc_extension,
    };

    alloc_info.ویش_اندازه = req->اندازه;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    لكل (صحيح i = 0; i < s->mprops.حافظه_Type_شمېر; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        إذا (!(req->حافظه_Type_بټونه & (1 << i)))
            استمر;

        /* The memory type flags must include our properties */
        إذا ((req_flags != UINT32_MAX) &&
            ((s->mprops.حافظه_Types[i].propertyFlags & req_flags) != req_flags))
            استمر;

        /* Found a suitable memory type */
        شاخص = i;
        اكسر;
    }

    إذا (شاخص < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        أرجع AVERROR(EINVAL);
    }

    alloc_info.حافظه_Type_شاخص = شاخص;

    ret = vk->Allocate_حافظه(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    إذا (ret != VK_SUCCESS)
        أرجع AVERROR(ENOMEM);

    إذا (mem_flags)
        *mem_flags |= s->mprops.حافظه_Types[شاخص].propertyFlags;

    أرجع 0;
}

صحيح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_حافظه *mem,
                       صحيح پلنوالی, صحيح لوړوالی, VkFormat format, صحيح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, فراغ *create_pnext)
{
    صحيح err;
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_حافظه_Property_Flag_بټونه mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_بل         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { پلنوالی, لوړوالی, 1 },
        .mip_پوړونه     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_شمېر_1_بټ,
        .sharing_ډېرپېښ   = VK_SHARING_ډېرپېښ_EXCLUSIVE,
    };
    Vk_حافظه_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_حافظه_DEDICATED_ALLOCATE_INFO,
    };
    Vk_حافظه_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_حافظه_REQUIREMENTS_2,
    };
    Vk_Image_حافظه_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_حافظه_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_حافظه_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_حافظه_INFO,
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
    vk->Get_Image_حافظه_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.حافظه_Requirements,
                          VK_حافظه_PROPERTY_DEVICE_LOCAL_بټ,
                          &ded_alloc, &mem_flags, mem);
    إذا (err < 0)
        اذهب fail;

    bind_info.image  = *img;
    bind_info.حافظه = *mem;
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

فراغ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_حافظه *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    إذا (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    إذا (*mem) {
        vk->Free_حافظه(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

صحيح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t اندازه,
                     فراغ *p_بل, فراغ *alloc_p_بل,
                     Vk_بفر_Usage_Flags usage, Vk_حافظه_Property_Flag_بټونه flags)
{
    صحيح err;
    Vk_پایله ret;
    صحيح use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_بل       = p_بل,
        .usage       = usage,
        .sharing_ډېرپېښ = VK_SHARING_ډېرپېښ_EXCLUSIVE,
        .اندازه        = flags & VK_حافظه_PROPERTY_HOST_VISIBLE_بټ ?
                       FFALIGN(اندازه, s->props.properties.limits.min_حافظه_Map_Alignment) :
                       اندازه,
    };

    Vk_حافظه_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_حافظه_ALLOCATE_FLAGS_INFO,
        .flags = VK_حافظه_ALLOCATE_DEVICE_پته_بټ,
    };
    Vk_بفر_حافظه_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_بفر_حافظه_REQUIREMENTS_INFO_2,
    };
    Vk_حافظه_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_حافظه_DEDICATED_ALLOCATE_INFO,
        .p_بل = alloc_p_بل,
    };
    Vk_حافظه_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_حافظه_DEDICATED_REQUIREMENTS,
    };
    Vk_حافظه_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_حافظه_REQUIREMENTS_2,
        .p_بل = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           اندازه, usage, flags);

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    req_desc.بفر = buf->buf;

    vk->Get_بفر_حافظه_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_ویش |
                  ded_req.requires_Dedicated_ویش;
    إذا (use_ded_mem) {
        ded_alloc.بفر = buf->buf;
        ded_alloc.p_بل = alloc_p_بل;
        alloc_p_بل = &ded_alloc;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پته_بټ) {
        alloc_flags.p_بل = alloc_p_بل;
        alloc_p_بل = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.حافظه_Requirements, flags, alloc_p_بل,
                          &buf->flags, &buf->mem);
    إذا (err)
        أرجع err;

    ret = vk->Bind_بفر_حافظه(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    إذا (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پته_بټ) {
        Vk_بفر_Device_پته_Info پته_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پته_INFO,
            .بفر = buf->buf,
        };
        buf->پته = vk->Get_بفر_Device_پته(s->hwctx->act_dev, &پته_info);
    }

    buf->اندازه = اندازه;

    أرجع 0;
}

صحيح ff_vk_map_buffers(FFVulkanContext *s, FFVk_بفر **buf, uint8_t *mem[],
                      صحيح nb_buffers, صحيح invalidate)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_حافظه_Range inval_list[64];
    صحيح inval_شمېر = 0;

    لكل (صحيح i = 0; i < nb_buffers; i++) {
        فراغ *dst;
        ret = vk->Map_حافظه(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_ټولیز_اندازه, 0, &dst);
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
        ثابت Vk_Mapped_حافظه_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظه_RANGE,
            .حافظه = buf[i]->mem,
            .اندازه   = VK_ټولیز_اندازه,
        };
        إذا (buf[i]->flags & VK_حافظه_PROPERTY_HOST_COHERENT_بټ)
            استمر;
        inval_list[inval_شمېر++] = ival_buf;
    }

    إذا (inval_شمېر) {
        ret = vk->Invalidate_Mapped_حافظه_Ranges(s->hwctx->act_dev, inval_شمېر,
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
                       Vk_Device_اندازه دننه_واټن, Vk_Device_اندازه mem_اندازه,
                       صحيح flush)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    إذا (buf->flags & VK_حافظه_PROPERTY_HOST_COHERENT_بټ)
        أرجع 0;

    ثابت Vk_Mapped_حافظه_Range flush_معلومات = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظه_RANGE,
        .حافظه = buf->mem,
        .دننه_واټن = دننه_واټن,
        .اندازه   = mem_اندازه,
    };

    إذا (flush)
        ret = vk->Flush_Mapped_حافظه_Ranges(s->hwctx->act_dev, 1, &flush_معلومات);
    وإلا
        ret = vk->Invalidate_Mapped_حافظه_Ranges(s->hwctx->act_dev, 1, &flush_معلومات);

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
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_حافظه_Range flush_list[64];
    صحيح flush_شمېر = 0;

    إذا (flush) {
        لكل (صحيح i = 0; i < nb_buffers; i++) {
            ثابت Vk_Mapped_حافظه_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظه_RANGE,
                .حافظه = buf[i]->mem,
                .اندازه   = VK_ټولیز_اندازه,
            };

            av_assert0(!buf[i]->host_ref);
            إذا (buf[i]->flags & VK_حافظه_PROPERTY_HOST_COHERENT_بټ)
                استمر;
            flush_list[flush_شمېر++] = flush_buf;
        }
    }

    إذا (flush_شمېر) {
        ret = vk->Flush_Mapped_حافظه_Ranges(s->hwctx->act_dev, flush_شمېر,
                                          flush_list);
        إذا (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    لكل (صحيح i = 0; i < nb_buffers; i++) {
        vk->Unmap_حافظه(s->hwctx->act_dev, buf[i]->mem);
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
        vk->Free_حافظه(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
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
                            فراغ *create_p_بل, size_t اندازه,
                            Vk_حافظه_Property_Flag_بټونه mem_props)
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

    إذا (معلومات->اندازه >= اندازه)
        أرجع 0;

    ff_vk_free_buf(ctx, معلومات);
    memset(معلومات, 0, حجم(*معلومات));

    err = ff_vk_create_buf(ctx, معلومات, اندازه,
                           create_p_بل, عدم, usage,
                           mem_props);
    إذا (err < 0) {
        av_refstruct_unref(buf);
        أرجع err;
    }

    إذا (mem_props & VK_حافظه_PROPERTY_HOST_VISIBLE_بټ) {
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
                                size_t اندازه,
                                Vk_External_حافظه_بفر_Create_Info *create_desc,
                                Vk_Import_حافظه_Host_اشاره_ګر_Info_EXT *import_desc,
                                Vk_حافظه_Host_اشاره_ګر_Properties_EXT props)
{
    صحيح err;
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_بل       = create_desc,
        .usage       = usage,
        .sharing_ډېرپېښ = VK_SHARING_ډېرپېښ_EXCLUSIVE,
        .اندازه        = اندازه,
    };
    Vk_حافظه_Requirements req = {
        .اندازه           = اندازه,
        .alignment      = s->hprops.min_Imported_Host_اشاره_ګر_Alignment,
        .حافظه_Type_بټونه = props.حافظه_Type_بټونه,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_حافظه_PROPERTY_HOST_VISIBLE_بټ,
                          import_desc, &vkb->flags, &vkb->mem);
    إذا (err < 0)
        أرجع err;

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    إذا (ret != VK_SUCCESS) {
        vk->Free_حافظه(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        أرجع AVERROR_EXTERNAL;
    }

    ret = vk->Bind_بفر_حافظه(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    إذا (ret != VK_SUCCESS) {
        vk->Free_حافظه(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
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
                          uint8_t *src_معلومات, Vk_Device_اندازه اندازه,
                          ثابت AVBufferRef *src_buf,
                          Vk_بفر_Usage_Flags usage)
{
    صحيح err;
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_حافظه_بفر_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_حافظه_بفر_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_حافظه_HANDLE_TYPE_HOST_ویش_بټ_EXT,
    };
    Vk_حافظه_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_حافظه_ALLOCATE_FLAGS_INFO,
        .flags = VK_حافظه_ALLOCATE_DEVICE_پته_بټ,
    };
    Vk_Import_حافظه_Host_اشاره_ګر_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_حافظه_HOST_اشاره_ګر_INFO_EXT,
        .handleType = VK_EXTERNAL_حافظه_HANDLE_TYPE_HOST_ویش_بټ_EXT,
        .p_بل = usage & VK_بفر_USAGE_SHADER_DEVICE_پته_بټ ? &alloc_flags : عدم,
    };
    Vk_حافظه_Host_اشاره_ګر_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_بفر *vkb;
    size_t offs;
    size_t بفر_اندازه;

    *dst = عدم;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_معلومات % s->hprops.min_Imported_Host_اشاره_ګر_Alignment;
    import_desc.p_Host_اشاره_ګر = src_معلومات - offs;

    props = (Vk_حافظه_Host_اشاره_ګر_Properties_EXT) {
        VK_STRUCTURE_TYPE_حافظه_HOST_اشاره_ګر_PROPERTIES_EXT,
    };
    ret = vk->Get_حافظه_Host_اشاره_ګر_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_اشاره_ګر,
                                                &props);
    إذا (!(ret == VK_SUCCESS && props.حافظه_Type_بټونه))
        أرجع AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_بفر_ref(src_buf);
    إذا (!ref)
        أرجع AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ثابت Vk_Device_اندازه src_avail = src_buf->اندازه - (src_معلومات - src_buf->معلومات);
    بفر_اندازه = offs + FFMIN(اندازه, src_avail);
    بفر_اندازه = FFALIGN(بفر_اندازه, s->props.properties.limits.min_حافظه_Map_Alignment);
    بفر_اندازه = FFALIGN(بفر_اندازه, s->hprops.min_Imported_Host_اشاره_ګر_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(حجم(*vkb), 0, s, host_map_free);
    إذا (!vkb) {
        av_بفر_unref(&ref);
        أرجع AVERROR(ENOMEM);
    }

    err = create_mapped_بفر(s, vkb, usage,
                               بفر_اندازه, &create_desc, &import_desc,
                               props);
    إذا (err < 0) {
        av_بفر_unref(&ref);
        av_refstruct_unref(&vkb);
        أرجع err;
    }

    إذا (usage & VK_بفر_USAGE_SHADER_DEVICE_پته_بټ) {
        Vk_بفر_Device_پته_Info پته_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پته_INFO,
            .بفر = vkb->buf,
        };
        vkb->پته = vk->Get_بفر_Device_پته(s->hwctx->act_dev, &پته_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_دننه_واټن = offs;
    vkb->پته       += offs;
    vkb->mapped_mem     = src_معلومات;
    vkb->اندازه           = بفر_اندازه - offs;

    *dst = vkb;

    أرجع 0;
}

صحيح ff_vk_shader_جمع_کړه_ټېل_const(FFVulkanShader *shd, صحيح دننه_واټن, صحيح اندازه,
                                Vk_Shader_Stage_Flag_بټونه stage)
{
    Vk_ټېل_Constant_Range *pc = &shd->ټېل_consts[shd->ټېل_consts_عدد++];
    av_assert1(shd->ټېل_consts_عدد < FF_VK_MAX_ټېل_CONSTS);
    pc->stageFlags = stage;
    pc->دننه_واټن = دننه_واټن;
    pc->اندازه = اندازه;
    أرجع 0;
}

صحيح ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       صحيح unnorm_coords, VkFilter filt)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_ډېرپېښ = (unnorm_coords || filt == VK_FILTER_تر_ټولو_نږدې) ?
                      VK_SAMPLER_MIPMAP_ډېرپېښ_تر_ټولو_نږدې :
                      VK_SAMPLER_MIPMAP_ډېرپېښ_خطي,
        .پته_ډېرپېښ_U = VK_SAMPLER_پته_ډېرپېښ_CLAMP_منزل_څنډه,
        .پته_ډېرپېښ_V = sampler_info.پته_ډېرپېښ_U,
        .پته_ډېرپېښ_W = sampler_info.پته_ډېرپېښ_U,
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
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    صحيح nb_images = ff_vk_شمېر_images(vkf);
    صحيح nb_planes = av_pix_fmt_شمېر_planes(hwfc->sw_format);

    ساكن ثابت VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_بټ,
                                                       VK_IMAGE_ASPECT_PLANE_1_بټ,
                                                       VK_IMAGE_ASPECT_PLANE_2_بټ, };

    إذا (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        أرجع VK_IMAGE_ASPECT_COLOR_بټ;

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

فراغ ff_vk_سېټ_perm(تعداد AVPixelFormat pix_fmt, صحيح lut[4], صحيح inv)
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

ساكن فراغ reset_imageviews(AVRefStructOpaque ناکارول_شوی, فراغ *obj)
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

    av_assert1(nb_views <= AV_عدد_معلومات_اشارې);

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
#تعریف_کړه REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#تعریف_کړه REPS_FMT_PACK(fmt, عدد) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## عدد, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## عدد, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## عدد, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## عدد,

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
#تعریف_لغوه REPS_FMT_PACK
#تعریف_لغوه REPS_FMT

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
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    AVVulkan_چوکاټونه_Context *vkfc = hwfc->hwctx;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];
    ثابت صحيح nb_images = ff_vk_شمېر_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_بټ_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_بټ_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_بل      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_منزل_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_بې_اغېزه_عنصر_map,
        .subresourceRange = {
            .aspect_ماسک = ff_vk_aspect_flag(f, plane),
            .level_شمېر = 1,
            .layer_شمېر = 1,
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

    *aspect = view_create_info.subresourceRange.aspect_ماسک;

    أرجع 0;
}

صحيح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_عدد_معلومات_اشارې],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_عدد_معلومات_اشارې])
{
    صحيح err = 0;
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    AVVulkan_چوکاټونه_Context *vkfc = hwfc->hwctx;
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)f->معلومات[0];
    ثابت صحيح nb_images = ff_vk_شمېر_images(vkf);
    ثابت صحيح nb_planes = av_pix_fmt_شمېر_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_عدد_معلومات_اشارې] = { 0 };

    لكل (صحيح i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_بټ_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_بټ_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_بل      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_بې_اغېزه_عنصر_map,
            .subresourceRange = {
                .aspect_ماسک = ff_vk_aspect_flag(f, i),
                .level_شمېر = 1,
                .layer_شمېر = 1,
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
        ff_vk_exec_جمع_کړه_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    حافظه_نقل(views, tmp_views, nb_planes*حجم(*views));

    أرجع 0;

fail:
    لكل (صحيح i = 0; i < nb_planes; i++)
        إذا (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    أرجع err;
}

صحيح ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_عدد_معلومات_اشارې],
                            AVFrame *f, تعداد FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ثابت صحيح nb_planes = av_pix_fmt_شمېر_planes(hwfc->sw_format);
    VkFormat fmts[AV_عدد_معلومات_اشارې] = { 0 };

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

فراغ ff_vk_چوکاټ_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_حافظه_Barrier2 *bar, صحيح *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    صحيح وموندل = -1;
    AVVk_چوکاټ *vkf = (AVVk_چوکاټ *)pic->معلومات[0];
    ثابت صحيح nb_images = ff_vk_شمېر_images(vkf);
    لكل (صحيح i = 0; i < e->nb_چوکاټ_deps; i++)
        إذا (e->چوکاټ_deps[i]->معلومات[0] == pic->معلومات[0]) {
            إذا (e->چوکاټ_update[i])
                وموندل = i;
            اكسر;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    لكل (صحيح i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_حافظه_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_حافظه_BARRIER_2,
            .p_بل = عدم,
            .src_Stage_ماسک = src_stage,
            .dst_Stage_ماسک = dst_stage,
            .src_Access_ماسک = وموندل >= 0 ? e->access_dst[وموندل] : VK_ACCESS_2_NONE,
            .dst_Access_ماسک = new_access,
            .oldLayout = وموندل >= 0 ? e->layout_dst[وموندل] : vkf->layout[0],
            .newLayout = new_layout,
            .src_کتار_Family_شاخص = وموندل >= 0 ? e->کتار_family_dst[وموندل] : vkf->کتار_family[0],
            .dst_کتار_Family_شاخص = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_ماسک = VK_IMAGE_ASPECT_COLOR_بټ,
                .layer_شمېر = 1,
                .level_شمېر = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_چوکاټ(s, e, pic, &bar[*nb_bar - nb_images], عدم);
}

صحيح ff_vk_shader_بارول(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_اندازه[3], uint32_t required_subgroup_اندازه)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    حافظه_نقل(shd->lg_اندازه, wg_اندازه, 3*حجم(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_اندازه_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_اندازه_CREATE_INFO,
        .required_Subgroup_اندازه = required_subgroup_اندازه,
    };

    بدل (shd->stage) {
    حالة VK_SHADER_STAGE_ANY_موندنه_بټ_KHR:
    حالة VK_SHADER_STAGE_CALLABLE_بټ_KHR:
    حالة VK_SHADER_STAGE_CLOSEST_موندنه_بټ_KHR:
    حالة VK_SHADER_STAGE_INTERSECTION_بټ_KHR:
    حالة VK_SHADER_STAGE_نه_موندنه_بټ_KHR:
    حالة VK_SHADER_STAGE_RAYGEN_بټ_KHR:
        shd->bind_ټکی = VK_PIPELINE_BIND_ټکی_RAY_TRACING_KHR;
        اكسر;
    حالة VK_SHADER_STAGE_COMPUTE_بټ:
        shd->bind_ټکی = VK_PIPELINE_BIND_ټکی_COMPUTE;
        اكسر;
    افتراضي:
        shd->bind_ټکی = VK_PIPELINE_BIND_ټکی_GRAPHICS;
        اكسر;
    };

    أرجع 0;
}

ساكن صحيح init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_سېټ_Layouts            = shd->desc_layout,
        .سېټ_Layout_شمېر         = shd->nb_descriptor_sets,
        .ټېل_Constant_Range_شمېر = shd->ټېل_consts_عدد,
        .p_ټېل_Constant_Ranges    = shd->ټېل_consts,
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
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_بل    = عدم,
        .flags    = 0x0,
        .p_کوډ    = (فراغ *)spirv,
        .کوډ_اندازه = spirv_len,
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
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_بل = shd->subgroup_info.required_Subgroup_اندازه ?
                     &shd->subgroup_info : عدم,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_اندازه ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_ډک_SUBGROUPS_بټ : 0x0,
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
    Vk_پایله ret;
    FFVulkanFunctions *vk = &s->vkfn;

    صحيح has_singular = 0;
    صحيح max_descriptors = 0;
    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_سېټ[i].nb_bindings);
        إذا (shd->desc_سېټ[i].singular)
            has_singular = 1;
    }
    shd->use_ټېل = (s->extensions & FF_VK_EXT_ټېل_DESCRIPTOR) &&
                    (max_descriptors <= s->ټېل_desc_props.max_ټېل_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_سېټ *سېټ = &shd->desc_سېټ[i];
        Vk_Descriptor_سېټ_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_سېټ_LAYOUT_CREATE_INFO,
            .binding_شمېر = سېټ->nb_bindings,
            .pBindings = سېټ->binding,
            .flags = (shd->use_ټېل) ?
                     VK_DESCRIPTOR_سېټ_LAYOUT_CREATE_ټېل_DESCRIPTOR_بټ_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_سېټ_Layout(s->hwctx->act_dev,
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
    Vk_Specialization_Map_ثبت spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ننوت_اندازه = spirv_len;

    إذا (shd->precompiled) {
        إذا (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_ثبت_شمېر = 0,
                .p_معلومات = shd->lg_اندازه,
                .معلومات_اندازه_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_ثبت *spe = (فراغ *)shd->specialization_info->pMapEntries;
        لكل (صحيح i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_ثبت_شمېر++] = (Vk_Specialization_Map_ثبت) {
                .constantID = 253 + i,
                .دننه_واټن = shd->specialization_info->معلومات_اندازه_2 + i*حجم(uint32_t),
                .اندازه = حجم(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_معلومات;
        حافظه_نقل(&spd[shd->specialization_info->معلومات_اندازه_2],
               shd->lg_اندازه, 3*حجم(uint32_t));
        shd->specialization_info->معلومات_اندازه_2 += 3*حجم(uint32_t);

#إذا CONFIG_SHADER_COMPRESSION
        uint8_t *بهر;
        size_t بهر_len;
        صحيح ret = ff_zlib_expand(s, &بهر, &بهر_len, spirv, spirv_len);
        إذا (ret < 0)
            أرجع ret;
        spirv = بهر;
        spirv_len = بهر_len;
#د_که_پای
    }

    err = init_descriptors(s, shd);
    إذا (err < 0)
        اذهب پای_ټکی;

    err = init_pipeline_layout(s, shd);
    إذا (err < 0)
        اذهب پای_ټکی;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    إذا (err < 0)
        اذهب پای_ټکی;

    بدل (shd->bind_ټکی) {
    حالة VK_PIPELINE_BIND_ټکی_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        اكسر;
    افتراضي:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_ټکی);
        err = AVERROR(EINVAL);
        اذهب پای_ټکی;
        اكسر;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    إذا (err < 0)
        اذهب پای_ټکی;

    إذا (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    وإلا
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    إذا (ننوت_اندازه != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ننوت_اندازه);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

پای_ټکی:
    إذا (shd->precompiled) {
        shd->specialization_info->map_ثبت_شمېر -= 3;
        shd->specialization_info->معلومات_اندازه_2 -= 3*حجم(uint32_t);
    }
#إذا CONFIG_SHADER_COMPRESSION
    إذا (shd->precompiled)
        av_free((فراغ *)spirv);
#د_که_پای
    أرجع err;
}

فراغ ff_vk_shader_جمع_کړه_descriptor_سېټ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سېټ_Binding *desc, صحيح nb,
                                     صحيح singular)
{
    FFVulkan_Descriptor_سېټ *سېټ = &shd->desc_سېټ[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    لكل (صحيح i = 0; i < nb; i++) {
        سېټ->binding[i].binding            = i;
        سېټ->binding[i].descriptorType     = desc[i].type;
        سېټ->binding[i].descriptor_شمېر    = FFMAX(desc[i].elems, 1);
        سېټ->binding[i].stageFlags         = desc[i].stages;
        سېټ->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    لكل (صحيح i = 0; i < nb; i++) {
        صحيح j;
        لكل (j = 0; j < shd->nb_desc_pool_اندازه; j++)
            إذا (shd->desc_pool_اندازه[j].type == desc[i].type)
                اكسر;
        إذا (j >= shd->nb_desc_pool_اندازه) {
            shd->nb_desc_pool_اندازه++;
            av_assert1(shd->nb_desc_pool_اندازه < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_اندازه[j].type             = desc[i].type;
        shd->desc_pool_اندازه[j].descriptor_شمېر += FFMAX(desc[i].elems, 1);
    }

    سېټ->singular = singular;
    سېټ->nb_bindings = nb;
}

صحيح ff_vk_shader_ثبتوونکی_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    إذا (!shd->nb_descriptor_sets)
        أرجع 0;

    FFVulkan_Shader_معلومات *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    إذا (!shd->use_ټېل) {
        Vk_پایله ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_سېټ_Layout *tmp_layouts;
        Vk_Descriptor_سېټ_Allocate_Info سېټ_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        لكل (صحيح i = 0; i < shd->nb_desc_pool_اندازه; i++)
            shd->desc_pool_اندازه[i].descriptor_شمېر *= pool->pool_اندازه;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_اندازه,
            .pool_اندازه_شمېر = shd->nb_desc_pool_اندازه,
            .maxSets = sd->nb_descriptor_sets*pool->pool_اندازه,
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
        لكل (صحيح i = 0; i < pool->pool_اندازه; i++)
            لكل (صحيح j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        سېټ_alloc_info = (Vk_Descriptor_سېټ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_سېټ_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_سېټ_Layouts        = tmp_layouts,
            .descriptor_سېټ_شمېر = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        حجم(*tmp_layouts));
        إذا (!sd->desc_sets) {
            av_free(tmp_layouts);
            أرجع AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &سېټ_alloc_info,
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
    لكل (صحيح i = 0; i < e->پلار->nb_reg_shd; i++)
        إذا (e->پلار->reg_shd[i].shd == shd)
            أرجع &e->پلار->reg_shd[i];
    أرجع عدم;
}

ساكن مضمن فراغ update_سېټ_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, صحيح سېټ,
                                         Vk_Write_Descriptor_سېټ *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_سېټ *desc_سېټ = &shd->desc_سېټ[سېټ];
    ثابت FFVulkan_Shader_معلومات *sd = get_shd_معلومات(e, shd);

    إذا (desc_سېټ->singular) {
        لكل (صحيح i = 0; i < e->پلار->pool_اندازه; i++) {
            write_info->dst_سېټ = sd->desc_sets[i*sd->nb_descriptor_sets + سېټ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, عدم);
        }
    } وإلا {
        إذا (shd->use_ټېل) {
            vk->Cmd_ټېل_Descriptor_سېټ_KHR(e->buf,
                                        shd->bind_ټکی,
                                        shd->pipeline_layout,
                                        سېټ, 1,
                                        write_info);
        } وإلا {
            write_info->dst_سېټ = sd->desc_sets[e->idx*sd->nb_descriptor_sets + سېټ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, عدم);
        }
    }
}

صحيح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحيح سېټ, صحيح bind, صحيح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_سېټ *desc_سېټ = &shd->desc_سېټ[سېټ];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_سېټ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سېټ,
        .dstBinding = bind,
        .descriptor_شمېر = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_سېټ->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_سېټ_pool_write(s, e, shd, سېټ, &desc_pool_write_info);

    أرجع 0;
}

فراغ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحيح سېټ, صحيح binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکاټونه_ctx->معلومات;
    ثابت صحيح nb_planes = av_pix_fmt_شمېر_planes(hwfc->sw_format);

    لكل (صحيح i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, سېټ, binding, i,
                                views[i], layout, sampler);
}

صحيح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحيح سېټ, صحيح bind, صحيح elem,
                                    FFVk_بفر *buf, Vk_Device_اندازه دننه_واټن, Vk_Device_اندازه len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_سېټ *desc_سېټ = &shd->desc_سېټ[سېټ];

    Vk_Descriptor_بفر_Info desc_pool_write_info_buf = {
        .بفر = buf->buf,
        .دننه_واټن = buf->virtual_دننه_واټن + دننه_واټن,
        .range = len,
    };
    Vk_Write_Descriptor_سېټ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سېټ,
        .dstBinding = bind,
        .descriptor_شمېر = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_سېټ->binding[bind].descriptorType,
        .p_بفر_Info = &desc_pool_write_info_buf,
    };
    update_سېټ_pool_write(s, e, shd, سېټ, &desc_pool_write_info);

    أرجع 0;
}

فراغ ff_vk_shader_update_ټېل_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بټونه stage,
                                    صحيح دننه_واټن, size_t اندازه, فراغ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ټېل_Constants(e->buf, shd->pipeline_layout,
                         stage, دننه_واټن, اندازه, src);
}

فراغ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ثابت FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVulkan_Shader_معلومات *sd = get_shd_معلومات(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_ټکی, shd->pipeline);

    إذا (sd && sd->nb_descriptor_sets) {
        إذا (!shd->use_ټېل) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_ټکی, shd->pipeline_layout,
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
#د_که_پای

    إذا (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    إذا (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    لكل (صحيح i = 0; i < shd->nb_descriptor_sets; i++)
        إذا (shd->desc_layout[i])
            vk->Destroy_Descriptor_سېټ_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

فراغ ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#که_تعریف_شوی VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#د_که_پای
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_بفر_unref(&s->device_ref);
    av_بفر_unref(&s->چوکاټونه_ref);
}

صحيح ff_vk_init(FFVulkanContext *s, فراغ *log_پلار,
               AVBufferRef *device_ref, AVBufferRef *چوکاټونه_ref)
{
    صحيح err;

    ساكن ثابت AVClass vulkan_context_class = {
        .class_name       = "vk",
        .نسخه          = LIBAVUTIL_نسخه_INT,
        .پلار_log_context_دننه_واټن = offsetof(FFVulkanContext, log_پلار),
    };

    memset(s, 0, حجم(*s));
    s->log_پلار = log_پلار;
    s->class      = &vulkan_context_class;

    إذا (چوکاټونه_ref) {
        s->چوکاټونه_ref = av_بفر_ref(چوکاټونه_ref);
        إذا (!s->چوکاټونه_ref)
            أرجع AVERROR(ENOMEM);

        s->چوکاټونه = (AVHWFramesContext *)s->چوکاټونه_ref->معلومات;
        s->hwfc = s->چوکاټونه->hwctx;

        device_ref = s->چوکاټونه->device_ref;
    }

    s->device_ref = av_بفر_ref(device_ref);
    إذا (!s->device_ref) {
        ff_vk_uninit(s);
        أرجع AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->معلومات;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_منزل_ماسک(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_منزل_ماسک(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_بارول_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    إذا (err < 0) {
        ff_vk_uninit(s);
        أرجع err;
    }

    err = ff_vk_بارول_props(s);
    إذا (err < 0) {
        ff_vk_uninit(s);
        أرجع err;
    }

    أرجع 0;
}
