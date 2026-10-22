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

#شامل "config.h"
#شامل "avassert.h"
#شامل "mem.h"
#شامل "random_seed.h"
#شامل "refstruct.h"

#شامل "vulkan.h"
#شامل "libavutil/vulkan_loader.h"

#اگر CONFIG_SHADER_COMPRESSION
#شامل "libavutil/zlib_utils.h"
#اگر_ختم

ثابت VkComponentMapping ff_comp_شناختی_عنصر_map = {
    .r = VK_COMPONENT_SWIZZLE_شناختی_عنصر,
    .g = VK_COMPONENT_SWIZZLE_شناختی_عنصر,
    .b = VK_COMPONENT_SWIZZLE_شناختی_عنصر,
    .a = VK_COMPONENT_SWIZZLE_شناختی_عنصر,
};

/* Converts return values to strings */
ثابت حرف *ff_vk_ret2str(Vk_نتیجہ res)
{
#تعریف_کرو CASE(VAL) حالت VAL: واپس #VAL
    انتخاب (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_سیٹ);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_برآمد_کا_HOST_حافظہ);
    CASE(VK_ERROR_برآمد_کا_DEVICE_حافظہ);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_گمشدہ);
    CASE(VK_ERROR_حافظہ_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_برآمد_کا_POOL_حافظہ);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_پتہ);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_گمشدہ_KHR);
    CASE(VK_ERROR_NATIVE_کھڑکی_اندر_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_برآمد_کا_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_نسخہ_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_بھرا_SCREEN_EXCLUSIVE_منوال_گمشدہ_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_مکمل_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    طےشدہ: واپس "Unknown error";
    }
#تعریف_منسوخ CASE
}

/* Malitia pura, Khronos */
#تعریف_کرو FN_MAP_مقصد(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## مقصد_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_مقصد(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ثنائی_ہندسہ,                   \
               VK_IMAGE_USAGE_SAMPLED_ثنائی_ہندسہ);                             \
        MAP_مقصد(VK_FORMAT_FEATURE_2_TRANSFER_SRC_ثنائی_ہندسہ,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_ثنائی_ہندسہ);                        \
        MAP_مقصد(VK_FORMAT_FEATURE_2_TRANSFER_DST_ثنائی_ہندسہ,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_ثنائی_ہندسہ);                        \
        MAP_مقصد(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ثنائی_ہندسہ,                   \
               VK_IMAGE_USAGE_STORAGE_ثنائی_ہندسہ);                             \
        MAP_مقصد(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_ثنائی_ہندسہ,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_ثنائی_ہندسہ);                    \
        MAP_مقصد(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_ثنائی_ہندسہ_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_ثنائی_ہندسہ_KHR);                \
        MAP_مقصد(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_ثنائی_ہندسہ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ثنائی_ہندسہ_KHR);                \
        MAP_مقصد(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_ثنائی_ہندسہ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ثنائی_ہندسہ_KHR);                \
        MAP_مقصد(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_داخلہ_ثنائی_ہندسہ_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ثنائی_ہندسہ_KHR);                \
        MAP_مقصد(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_ثنائی_ہندسہ_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_ثنائی_ہندسہ_EXT);                   \
        واپس dst;                                                     \
    }

#تعریف_کرو MAP_مقصد(flag1, flag2) اگر (src & flag2) dst |= flag1;
FN_MAP_مقصد(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#تعریف_منسوخ MAP_مقصد
#تعریف_کرو MAP_مقصد(flag1, flag2) اگر (src & flag1) dst |= flag2;
FN_MAP_مقصد(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#تعریف_منسوخ MAP_مقصد
#تعریف_منسوخ FN_MAP_مقصد

ساکن خالی بھرو_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    برائے (صحیح i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        صحیح skip = 0;
        برائے (صحیح j = 0; j < s->nb_qfs; j++) {
            اگر (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                توڑو;
            }
        }
        اگر (skip)
            جاری;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ساکن خالی reset_imageviews(AVRefStructOpaque غیر_مستعمل, خالی *obj);

صحیح ff_vk_بھرو_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_سائز_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ڈالو_desc_props, FF_VK_EXT_ڈالو_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ڈالو_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_حافظہ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_حافظہ_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_میٹرکس_props, FF_VK_EXT_COOP_میٹرکس,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_میٹرکس_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#اگر_تعریف_شدہ VK_EXT_shader_long_سمتیہ
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_سمتیہ_props, FF_VK_EXT_LONG_سمتیہ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_سمتیہ_PROPERTIES_EXT);
#اگر_ختم

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#اگر_تعریف_شدہ VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#اگر_ختم

    اگر (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(حجم(FFVkImageViews), 0,
                                                         تہی, تہی, reset_imageviews,
                                                         تہی, تہی);
        اگر (!s->imageviews_pool)
            واپس AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(حجم(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_گنتی = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_گنتی = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    اگر (s->host_image_props.copy_Src_Layout_گنتی == 512 ||
        s->host_image_props.copy_Dst_Layout_گنتی == 512) {
        VkImageLayout *new_array;
        size_t new_سائز;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = تہی;
        s->host_image_props.copy_Src_Layout_گنتی =
        s->host_image_props.copy_Dst_Layout_گنتی = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_سائز = s->host_image_props.copy_Src_Layout_گنتی +
                   s->host_image_props.copy_Dst_Layout_گنتی;
        new_سائز *= حجم(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_سائز);
        اگر (!new_array)
            واپس AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_گنتی;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_حافظہ_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    برائے (صحیح i = 0; i < s->mprops.حافظہ_Type_گنتی; i++)
        s->host_cached_flag |= s->mprops.حافظہ_Types[i].propertyFlags &
                               VK_حافظہ_PROPERTY_HOST_CACHED_ثنائی_ہندسہ;

    بھرو_enabled_qfs(s);

    اگر (s->qf_props)
        واپس 0;

    vk->Get_Physical_Device_قطار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, تہی);

    s->qf_props = av_calloc(s->tot_nb_qfs, حجم(*s->qf_props));
    اگر (!s->qf_props)
        واپس AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, حجم(*s->query_props));
    اگر (!s->qf_props) {
        av_freep(&s->qf_props);
        واپس AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, حجم(*s->video_props));
    اگر (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        واپس AVERROR(ENOMEM);
    }

#اگر_تعریف_شدہ VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, حجم(*s->ownership_props));
    اگر (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        واپس AVERROR(ENOMEM);
    }
#اگر_ختم

    برائے (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_قطار_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_قطار,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_QUERY_نتیجہ_حالت_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_قطار,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_VIDEO_PROPERTIES_KHR);
#اگر_تعریف_شدہ VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_قطار_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#اگر_ختم
    }

    vk->Get_Physical_Device_قطار_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    اگر (s->extensions & FF_VK_EXT_COOP_میٹرکس) {
        vk->Get_Physical_Device_Cooperative_میٹرکس_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, تہی);

        اگر (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                حجم(Vk_Cooperative_میٹرکس_Properties_KHR));
            برائے (صحیح i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_میٹرکس_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_میٹرکس_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_میٹرکس_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    واپس 0;
}

AVVulkan_Device_قطار_Family *ff_vk_qf_ڈھونڈو(FFVulkanContext *s,
                                         Vk_قطار_Flag_بٹ dev_family,
                                         Vk_Video_Codec_Operation_Flag_بٹ_KHR vid_ops)
{
    برائے (صحیح i = 0; i < s->hwctx->nb_qf; i++) {
        اگر ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            واپس &s->hwctx->qf[i];
        }
    }
    واپس تہی;
}

ساکن خالی exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

خالی ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    برائے (صحیح i = 0; i < pool->pool_سائز; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        اگر (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_گنتی = 1,
                .pSemaphores = &e->sem,
                .p_اقدار = &e->sem_قدر,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->تالا_2);
    }

    /* Free shader-specific data */
    برائے (صحیح i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_ڈیٹا *sd = &pool->reg_shd[i];

        اگر (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    برائے (صحیح i = 0; i < pool->pool_سائز; i++) {
        اگر (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        اگر (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    اگر (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_ڈیٹا);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_سائز = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ساکن atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)تہی)->qf)];
ساکن AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ساکن خالی exec_pool_phase_بیج(خالی)
{
    uint32_t بیج = av_get_random_بیج();
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], بیج, memory_order_relaxed);
}

صحیح ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_قطار_Family *qf,
                         FFVkExecPool *pool, صحیح nb_contexts,
                         صحیح nb_queries, VkQueryType query_type, صحیح query_64bit,
                         ثابت خالی *query_create_pnext)
{
    صحیح err;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_بفر_Allocate_Info cbuf_create;

    ثابت VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = تہی;

    atomic_init(&pool->idx, 0);

    اگر (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_ڈھونڈو_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        اگر (!ef)
            واپس AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*حجم(*pool->cmd_buf_pools));
    اگر (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*حجم(*pool->cmd_bufs));
    اگر (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    برائے (صحیح i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_ثنائی_ہندسہ |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_بفر_ثنائی_ہندسہ,
            .قطار_Family_اشاریہ   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            جاؤ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_بفر_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_بفر_ALLOCATE_INFO,
            .level              = VK_COMMAND_بفر_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_بفر_گنتی = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            جاؤ fail;
        }
    }

    /* Query pool */
    اگر (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_اگلا = query_create_pnext,
            .queryType = query_type,
            .query_گنتی = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            جاؤ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_حالت_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        اگر (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            صحیح nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_حالت_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } ورنہ اگر (query_type == VK_QUERY_TYPE_نتیجہ_حالت_ONLY_KHR) {
            pool->query_حالت_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_سائز = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_ڈیٹا = av_calloc(nb_contexts, pool->qd_سائز);
        اگر (!pool->query_ڈیٹا) {
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, حجم(*pool->contexts));
    اگر (!pool->contexts) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    pool->pool_سائز = nb_contexts;

    برائے (صحیح i = 0; i < pool->pool_سائز; i++)
        pthread_mutex_init(&pool->contexts[i].تالا_2, تہی);

#اگر_تعریف_شدہ VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    صحیح اندرونی_قطار_sync = 0;
    اگر (s->extensions & FF_VK_EXT_اندرونی_قطار_SYNC) {
        ثابت VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_ڈھونڈو_struct(s->hwctx->device_features.p_اگلا,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        اندرونی_قطار_sync = iqs && iqs->internallySynchronizedQueues;
    }
#اگر_ختم

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_بیج);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    صحیح pin_قطار = qf->flags & (VK_قطار_VIDEO_DECODE_ثنائی_ہندسہ_KHR |
                                 VK_قطار_VIDEO_ENCODE_ثنائی_ہندسہ_KHR);

    /* Init contexts */
    برائے (صحیح i = 0; i < pool->pool_سائز; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_اگلا = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            واپس AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->والد = pool;

        /* Query data */
        e->query_ڈیٹا = ((uint8_t *)pool->query_ڈیٹا) + pool->qd_سائز*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_قطار ? phase % qf->عدد : (i + phase) % qf->عدد;
        e->qf = qf->idx;
        Vk_Device_قطار_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_قطار_INFO_2,
#اگر_تعریف_شدہ VK_KHR_internally_synchronized_queues
            .flags            = اندرونی_قطار_sync ?
                                VK_DEVICE_قطار_CREATE_INTERNALLY_SYNCHRONIZED_ثنائی_ہندسہ_KHR : 0,
#اگر_ختم
            .قطار_Family_اشاریہ = qf->idx,
            .قطار_اشاریہ       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->قطار);
    }

    واپس 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    واپس err;
}

Vk_نتیجہ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              خالی **ڈیٹا, Vk_Query_نتیجہ_Flag_بٹ flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->والد;
    Vk_Query_نتیجہ_Flags qf = flags & ~(VK_QUERY_نتیجہ_64_ثنائی_ہندسہ |
                                      VK_QUERY_نتیجہ_WITH_حالت_ثنائی_ہندسہ_KHR);

    اگر (!e->query_ڈیٹا) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        واپس VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_نتیجہ_64_ثنائی_ہندسہ : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_نتیجہ_WITH_حالت_ثنائی_ہندسہ_KHR : 0x0;

    اگر (ڈیٹا)
        *ڈیٹا = e->query_ڈیٹا;

    واپس vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_سائز, e->query_ڈیٹا,
                                   pool->qd_سائز, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    برائے (صحیح i = 0; i < pool->pool_سائز; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        اگر (pthread_mutex_trylock(&e->تالا_2))
            جاری; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        اگر (vk->Get_Semaphore_شمار_قدر(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_قدر &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_چوکھٹا_deps || e->nb_sw_چوکھٹا_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->تالا_2);
    }

    واپس &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_سائز];
}

خالی ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_گنتی = 1,
        .pSemaphores = &e->sem,
        .p_اقدار = &e->sem_قدر,
    };
    pthread_mutex_تالا(&e->تالا_2);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->تالا_2);
}

صحیح ff_vk_exec_آغاز(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVkExecPool *pool = e->والد;

    Vk_Command_بفر_Begin_Info cmd_آغاز = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_BEGIN_INFO,
        .flags = VK_COMMAND_بفر_USAGE_ONE_وقت_SUBMIT_ثنائی_ہندسہ,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_گنتی = 1,
        .pSemaphores = &e->sem,
        .p_اقدار = &e->sem_قدر,
    };

    pthread_mutex_تالا(&e->تالا_2);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_بفر(e->buf, &cmd_آغاز);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->تالا_2);
        واپس AVERROR_EXTERNAL;
    }

    اگر (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_قدر++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .قدر = e->sem_قدر,
        .stage_نقاب = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ثنائی_ہندسہ,
    };

    pthread_mutex_unlock(&e->تالا_2);

    واپس 0;
}

ساکن خالی exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    برائے (صحیح j = 0; j < e->nb_buf_deps; j++)
        av_بفر_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    برائے (صحیح j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    برائے (صحیح j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        انتخاب (od->type) {
        حالت VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            توڑو;
        حالت VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            توڑو;
        طےشدہ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    برائے (صحیح j = 0; j < e->nb_sw_چوکھٹا_deps; j++)
        av_چوکھٹا_free(&e->sw_چوکھٹا_deps[j]);
    e->nb_sw_چوکھٹا_deps = 0;

    برائے (صحیح j = 0; j < e->nb_چوکھٹا_deps; j++) {
        AVFrame *f = e->چوکھٹا_deps[j];
        اگر (e->چوکھٹا_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
            AVVulkan_چوکھٹے_Context *vkfc = hwfc->hwctx;
            AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];
            vkfc->unlock_چوکھٹا(hwfc, vkf);
            e->چوکھٹا_locked[j] = 0;
        }
        e->چوکھٹا_update[j] = 0;
    }
    e->nb_چوکھٹا_deps = 0;

    e->sem_wait_cnt = 0;
    e->sem_sig_cnt = 0;
    e->sem_sig_val_dst_cnt = 0;
}

خالی ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
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

خالی ff_vk_exec_جوڑو_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  خالی *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

خالی ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   خالی *obj)
{
    خالی **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    برائے (صحیح i = 0; i < e->nb_refstruct_deps; i++) {
        اگر (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            واپس;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = تہی;
}

خالی ff_vk_exec_جوڑو_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

صحیح ff_vk_exec_جوڑو_dep_sw_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_چوکھٹا_deps < FF_VK_EXEC_MAX_SW_چوکھٹا_DEPS);

    e->sw_چوکھٹا_deps[e->nb_sw_چوکھٹا_deps] = av_چوکھٹا_clone(f);
    اگر (!e->sw_چوکھٹا_deps[e->nb_sw_چوکھٹا_deps])
        واپس AVERROR(ENOMEM);

    e->nb_sw_چوکھٹا_deps++;

    واپس 0;
}

خالی ff_vk_exec_جوڑو_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
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

خالی ff_vk_exec_جوڑو_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
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

خالی ff_vk_exec_جوڑو_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, صحیح nb,
                                 VkPipelineStageFlagBits2 stage,
                                 صحیح wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    اگر (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        برائے (صحیح i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_نقاب = stage,
            };
        }

        واپس;
    }

    /* Ownership of each semaphore passes to the execution */
    برائے (صحیح i = 0; i < nb; i++) {
        ff_vk_exec_جوڑو_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_جوڑو_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

صحیح ff_vk_exec_جوڑو_dep_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    AVVulkan_چوکھٹے_Context *vkfc = hwfc->hwctx;
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];
    صحیح nb_images = ff_vk_گنتی_images(vkf);

    /* Don't add duplicates */
    برائے (صحیح i = 0; i < e->nb_چوکھٹا_deps; i++)
        اگر (e->چوکھٹا_deps[i]->ڈیٹا[0] == f->ڈیٹا[0])
            واپس 1;

    av_assert1(e->nb_چوکھٹا_deps < FF_VK_EXEC_MAX_چوکھٹا_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    اگر (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_بفر_ref(f->buf[0]);
        اگر (!e->buf_deps[e->nb_buf_deps])
            واپس AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->چوکھٹا_deps[e->nb_چوکھٹا_deps] = f;

    vkfc->تالا_چوکھٹا(hwfc, vkf);
    e->چوکھٹا_locked[e->nb_چوکھٹا_deps] = 1;
    e->چوکھٹا_update[e->nb_چوکھٹا_deps] = 0;
    e->nb_چوکھٹا_deps++;

    برائے (صحیح i = 0; i < nb_images; i++) {
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

    واپس 0;
}

خالی ff_vk_exec_update_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_حافظہ_Barrier2 *bar, uint32_t *nb_img_bar)
{
    صحیح i;
    برائے (i = 0; i < e->nb_چوکھٹا_deps; i++)
        اگر (e->چوکھٹا_deps[i]->ڈیٹا[0] == f->ڈیٹا[0])
            توڑو;
    av_assert0(i < e->nb_چوکھٹا_deps);

    /* Don't update duplicates */
    اگر (nb_img_bar && !e->چوکھٹا_update[i])
        (*nb_img_bar)++;

    e->قطار_family_dst[i] = bar->dst_قطار_Family_اشاریہ;
    e->access_dst[i] = bar->dst_Access_نقاب;
    e->layout_dst[i] = bar->newLayout;
    e->چوکھٹا_update[i] = 1;
}

صحیح ff_vk_exec_mirror_sem_قدر(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];

    /* Reject unknown frames */
    صحیح i;
    برائے (i = 0; i < e->nb_چوکھٹا_deps; i++)
        اگر (e->چوکھٹا_deps[i]->ڈیٹا[0] == f->ڈیٹا[0])
            توڑو;
    اگر (i == e->nb_چوکھٹا_deps)
        واپس AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_قدر[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    واپس 0;
}

صحیح ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_بفر_Submit_Info cmd_buf_info = (Vk_Command_بفر_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_بفر_SUBMIT_INFO,
        .command_بفر = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_بفر_Infos = &cmd_buf_info,
        .command_بفر_Info_گنتی = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_گنتی = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_گنتی = e->sem_sig_cnt,
    };

    ret = vk->انتہا_Command_بفر(e->buf);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        واپس AVERROR_EXTERNAL;
    }

#اگر FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->تالا_قطار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#اگر_ختم
    ret = vk->قطار_Submit2(e->قطار, 1, &submit_info, VK_NULL_HANDLE);
#اگر FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_قطار(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#اگر_ختم

    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        واپس AVERROR_EXTERNAL;
    }

    برائے (صحیح i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    برائے (صحیح j = 0; j < e->nb_چوکھٹا_deps; j++) {
        اگر (e->چوکھٹا_locked[j]) {
            AVFrame *f = e->چوکھٹا_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
            AVVulkan_چوکھٹے_Context *vkfc = hwfc->hwctx;
            AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];

            اگر (e->چوکھٹا_update[j]) {
                صحیح nb_images = ff_vk_گنتی_images(vkf);
                برائے (صحیح i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->قطار_family[i] = e->قطار_family_dst[j];
                }
            }
            vkfc->unlock_چوکھٹا(hwfc, vkf);
            e->چوکھٹا_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    واپس 0;
}

صحیح ff_vk_alloc_mem(FFVulkanContext *s, Vk_حافظہ_Requirements *req,
                    Vk_حافظہ_Property_Flag_بٹ req_flags, خالی *alloc_extension,
                    Vk_حافظہ_Property_Flag_بٹ *mem_flags, Vk_Device_حافظہ *mem)
{
    Vk_نتیجہ ret;
    صحیح اشاریہ = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_حافظہ_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_حافظہ_ALLOCATE_INFO,
        .p_اگلا           = alloc_extension,
    };

    alloc_info.تخصیص_سائز = req->سائز;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    برائے (صحیح i = 0; i < s->mprops.حافظہ_Type_گنتی; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        اگر (!(req->حافظہ_Type_بٹ & (1 << i)))
            جاری;

        /* The memory type flags must include our properties */
        اگر ((req_flags != UINT32_MAX) &&
            ((s->mprops.حافظہ_Types[i].propertyFlags & req_flags) != req_flags))
            جاری;

        /* Found a suitable memory type */
        اشاریہ = i;
        توڑو;
    }

    اگر (اشاریہ < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        واپس AVERROR(EINVAL);
    }

    alloc_info.حافظہ_Type_اشاریہ = اشاریہ;

    ret = vk->Allocate_حافظہ(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    اگر (ret != VK_SUCCESS)
        واپس AVERROR(ENOMEM);

    اگر (mem_flags)
        *mem_flags |= s->mprops.حافظہ_Types[اشاریہ].propertyFlags;

    واپس 0;
}

صحیح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem,
                       صحیح چوڑائی, صحیح اونچائی, VkFormat format, صحیح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, خالی *create_pnext)
{
    صحیح err;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_حافظہ_Property_Flag_بٹ mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_اگلا         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { چوڑائی, اونچائی, 1 },
        .mip_سطحیں     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_گنتی_1_ثنائی_ہندسہ,
        .sharing_منوال   = VK_SHARING_منوال_EXCLUSIVE,
    };
    Vk_حافظہ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_DEDICATED_ALLOCATE_INFO,
    };
    Vk_حافظہ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_REQUIREMENTS_2,
    };
    Vk_Image_حافظہ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_حافظہ_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_حافظہ_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_حافظہ_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_حافظہ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.حافظہ_Requirements,
                          VK_حافظہ_PROPERTY_DEVICE_LOCAL_ثنائی_ہندسہ,
                          &ded_alloc, &mem_flags, mem);
    اگر (err < 0)
        جاؤ fail;

    bind_info.image  = *img;
    bind_info.حافظہ = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        جاؤ fail;
    }

    واپس 0;

fail:
    ff_vk_image_free(s, img, mem);
    واپس err;
}

خالی ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    اگر (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    اگر (*mem) {
        vk->Free_حافظہ(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

صحیح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t سائز,
                     خالی *p_اگلا, خالی *alloc_p_اگلا,
                     Vk_بفر_Usage_Flags usage, Vk_حافظہ_Property_Flag_بٹ flags)
{
    صحیح err;
    Vk_نتیجہ ret;
    صحیح use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_اگلا       = p_اگلا,
        .usage       = usage,
        .sharing_منوال = VK_SHARING_منوال_EXCLUSIVE,
        .سائز        = flags & VK_حافظہ_PROPERTY_HOST_VISIBLE_ثنائی_ہندسہ ?
                       FFALIGN(سائز, s->props.properties.limits.min_حافظہ_Map_Alignment) :
                       سائز,
    };

    Vk_حافظہ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_ALLOCATE_FLAGS_INFO,
        .flags = VK_حافظہ_ALLOCATE_DEVICE_پتہ_ثنائی_ہندسہ,
    };
    Vk_بفر_حافظہ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_بفر_حافظہ_REQUIREMENTS_INFO_2,
    };
    Vk_حافظہ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_DEDICATED_ALLOCATE_INFO,
        .p_اگلا = alloc_p_اگلا,
    };
    Vk_حافظہ_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_DEDICATED_REQUIREMENTS,
    };
    Vk_حافظہ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_REQUIREMENTS_2,
        .p_اگلا = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           سائز, usage, flags);

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    req_desc.بفر = buf->buf;

    vk->Get_بفر_حافظہ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_تخصیص |
                  ded_req.requires_Dedicated_تخصیص;
    اگر (use_ded_mem) {
        ded_alloc.بفر = buf->buf;
        ded_alloc.p_اگلا = alloc_p_اگلا;
        alloc_p_اگلا = &ded_alloc;
    }

    اگر (usage & VK_بفر_USAGE_SHADER_DEVICE_پتہ_ثنائی_ہندسہ) {
        alloc_flags.p_اگلا = alloc_p_اگلا;
        alloc_p_اگلا = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.حافظہ_Requirements, flags, alloc_p_اگلا,
                          &buf->flags, &buf->mem);
    اگر (err)
        واپس err;

    ret = vk->Bind_بفر_حافظہ(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    اگر (usage & VK_بفر_USAGE_SHADER_DEVICE_پتہ_ثنائی_ہندسہ) {
        Vk_بفر_Device_پتہ_Info پتہ_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پتہ_INFO,
            .بفر = buf->buf,
        };
        buf->پتہ = vk->Get_بفر_Device_پتہ(s->hwctx->act_dev, &پتہ_info);
    }

    buf->سائز = سائز;

    واپس 0;
}

صحیح ff_vk_map_buffers(FFVulkanContext *s, FFVk_بفر **buf, uint8_t *mem[],
                      صحیح nb_buffers, صحیح invalidate)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_حافظہ_Range inval_list[64];
    صحیح inval_گنتی = 0;

    برائے (صحیح i = 0; i < nb_buffers; i++) {
        خالی *dst;
        ret = vk->Map_حافظہ(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_پورا_سائز, 0, &dst);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            واپس AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        اگر (mem)
            mem[i] = dst;
    }

    اگر (!invalidate)
        واپس 0;

    برائے (صحیح i = 0; i < nb_buffers; i++) {
        ثابت Vk_Mapped_حافظہ_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظہ_RANGE,
            .حافظہ = buf[i]->mem,
            .سائز   = VK_پورا_سائز,
        };
        اگر (buf[i]->flags & VK_حافظہ_PROPERTY_HOST_COHERENT_ثنائی_ہندسہ)
            جاری;
        inval_list[inval_گنتی++] = ival_buf;
    }

    اگر (inval_گنتی) {
        ret = vk->Invalidate_Mapped_حافظہ_Ranges(s->hwctx->act_dev, inval_گنتی,
                                               inval_list);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            واپس AVERROR_EXTERNAL;
        }
    }

    واپس 0;
}

صحیح ff_vk_flush_بفر(FFVulkanContext *s, FFVk_بفر *buf,
                       Vk_Device_سائز انحراف, Vk_Device_سائز mem_سائز,
                       صحیح flush)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    اگر (buf->flags & VK_حافظہ_PROPERTY_HOST_COHERENT_ثنائی_ہندسہ)
        واپس 0;

    ثابت Vk_Mapped_حافظہ_Range flush_ڈیٹا = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظہ_RANGE,
        .حافظہ = buf->mem,
        .انحراف = انحراف,
        .سائز   = mem_سائز,
    };

    اگر (flush)
        ret = vk->Flush_Mapped_حافظہ_Ranges(s->hwctx->act_dev, 1, &flush_ڈیٹا);
    ورنہ
        ret = vk->Invalidate_Mapped_حافظہ_Ranges(s->hwctx->act_dev, 1, &flush_ڈیٹا);

    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

صحیح ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_بفر **buf, صحیح nb_buffers,
                        صحیح flush)
{
    صحیح err = 0;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_حافظہ_Range flush_list[64];
    صحیح flush_گنتی = 0;

    اگر (flush) {
        برائے (صحیح i = 0; i < nb_buffers; i++) {
            ثابت Vk_Mapped_حافظہ_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_حافظہ_RANGE,
                .حافظہ = buf[i]->mem,
                .سائز   = VK_پورا_سائز,
            };

            av_assert0(!buf[i]->host_ref);
            اگر (buf[i]->flags & VK_حافظہ_PROPERTY_HOST_COHERENT_ثنائی_ہندسہ)
                جاری;
            flush_list[flush_گنتی++] = flush_buf;
        }
    }

    اگر (flush_گنتی) {
        ret = vk->Flush_Mapped_حافظہ_Ranges(s->hwctx->act_dev, flush_گنتی,
                                          flush_list);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    برائے (صحیح i = 0; i < nb_buffers; i++) {
        vk->Unmap_حافظہ(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = تہی;
    }

    واپس err;
}

خالی ff_vk_free_buf(FFVulkanContext *s, FFVk_بفر *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    اگر (!buf || !s->hwctx)
        واپس;

    اگر (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_بفر(s, buf, 0);
    اگر (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_بفر(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    اگر (buf->mem != VK_NULL_HANDLE)
        vk->Free_حافظہ(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    اگر (buf->host_ref)
        av_بفر_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = تہی;
}

ساکن خالی pooled_buf_free(AVRefStructOpaque opaque, خالی *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

صحیح ff_vk_get_pooled_بفر(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_بفر **buf, Vk_بفر_Usage_Flags usage,
                            خالی *create_p_اگلا, size_t سائز,
                            Vk_حافظہ_Property_Flag_بٹ mem_props)
{
    صحیح err;
    FFVk_بفر *ڈیٹا;

    اگر (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(حجم(FFVk_بفر), 0, ctx,
                                                تہی, تہی, pooled_buf_free,
                                                تہی);
        اگر (!(*buf_pool))
            واپس AVERROR(ENOMEM);
    }

    *buf = ڈیٹا = av_refstruct_pool_get(*buf_pool);
    اگر (!ڈیٹا)
        واپس AVERROR(ENOMEM);

    اگر (ڈیٹا->سائز >= سائز)
        واپس 0;

    ff_vk_free_buf(ctx, ڈیٹا);
    memset(ڈیٹا, 0, حجم(*ڈیٹا));

    err = ff_vk_create_buf(ctx, ڈیٹا, سائز,
                           create_p_اگلا, تہی, usage,
                           mem_props);
    اگر (err < 0) {
        av_refstruct_unref(buf);
        واپس err;
    }

    اگر (mem_props & VK_حافظہ_PROPERTY_HOST_VISIBLE_ثنائی_ہندسہ) {
        err = ff_vk_map_بفر(ctx, ڈیٹا, &ڈیٹا->mapped_mem, 0);
        اگر (err < 0) {
            av_refstruct_unref(buf);
            واپس err;
        }
    }

    واپس 0;
}

ساکن صحیح create_mapped_بفر(FFVulkanContext *s,
                                FFVk_بفر *vkb, Vk_بفر_Usage_Flags usage,
                                size_t سائز,
                                Vk_External_حافظہ_بفر_Create_Info *create_desc,
                                Vk_Import_حافظہ_Host_اشارہ_گر_Info_EXT *import_desc,
                                Vk_حافظہ_Host_اشارہ_گر_Properties_EXT props)
{
    صحیح err;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_بفر_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_بفر_CREATE_INFO,
        .p_اگلا       = create_desc,
        .usage       = usage,
        .sharing_منوال = VK_SHARING_منوال_EXCLUSIVE,
        .سائز        = سائز,
    };
    Vk_حافظہ_Requirements req = {
        .سائز           = سائز,
        .alignment      = s->hprops.min_Imported_Host_اشارہ_گر_Alignment,
        .حافظہ_Type_بٹ = props.حافظہ_Type_بٹ,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_حافظہ_PROPERTY_HOST_VISIBLE_ثنائی_ہندسہ,
                          import_desc, &vkb->flags, &vkb->mem);
    اگر (err < 0)
        واپس err;

    ret = vk->Create_بفر(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    اگر (ret != VK_SUCCESS) {
        vk->Free_حافظہ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        واپس AVERROR_EXTERNAL;
    }

    ret = vk->Bind_بفر_حافظہ(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    اگر (ret != VK_SUCCESS) {
        vk->Free_حافظہ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_بفر(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

ساکن خالی host_map_free(AVRefStructOpaque opaque, خالی *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

صحیح ff_vk_host_map_بفر(FFVulkanContext *s, FFVk_بفر **dst,
                          uint8_t *src_ڈیٹا, Vk_Device_سائز سائز,
                          ثابت AVBufferRef *src_buf,
                          Vk_بفر_Usage_Flags usage)
{
    صحیح err;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_حافظہ_بفر_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_حافظہ_بفر_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_حافظہ_HANDLE_TYPE_HOST_تخصیص_ثنائی_ہندسہ_EXT,
    };
    Vk_حافظہ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_حافظہ_ALLOCATE_FLAGS_INFO,
        .flags = VK_حافظہ_ALLOCATE_DEVICE_پتہ_ثنائی_ہندسہ,
    };
    Vk_Import_حافظہ_Host_اشارہ_گر_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_حافظہ_HOST_اشارہ_گر_INFO_EXT,
        .handleType = VK_EXTERNAL_حافظہ_HANDLE_TYPE_HOST_تخصیص_ثنائی_ہندسہ_EXT,
        .p_اگلا = usage & VK_بفر_USAGE_SHADER_DEVICE_پتہ_ثنائی_ہندسہ ? &alloc_flags : تہی,
    };
    Vk_حافظہ_Host_اشارہ_گر_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_بفر *vkb;
    size_t offs;
    size_t بفر_سائز;

    *dst = تہی;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_ڈیٹا % s->hprops.min_Imported_Host_اشارہ_گر_Alignment;
    import_desc.p_Host_اشارہ_گر = src_ڈیٹا - offs;

    props = (Vk_حافظہ_Host_اشارہ_گر_Properties_EXT) {
        VK_STRUCTURE_TYPE_حافظہ_HOST_اشارہ_گر_PROPERTIES_EXT,
    };
    ret = vk->Get_حافظہ_Host_اشارہ_گر_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_اشارہ_گر,
                                                &props);
    اگر (!(ret == VK_SUCCESS && props.حافظہ_Type_بٹ))
        واپس AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_بفر_ref(src_buf);
    اگر (!ref)
        واپس AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ثابت Vk_Device_سائز src_avail = src_buf->سائز - (src_ڈیٹا - src_buf->ڈیٹا);
    بفر_سائز = offs + FFMIN(سائز, src_avail);
    بفر_سائز = FFALIGN(بفر_سائز, s->props.properties.limits.min_حافظہ_Map_Alignment);
    بفر_سائز = FFALIGN(بفر_سائز, s->hprops.min_Imported_Host_اشارہ_گر_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(حجم(*vkb), 0, s, host_map_free);
    اگر (!vkb) {
        av_بفر_unref(&ref);
        واپس AVERROR(ENOMEM);
    }

    err = create_mapped_بفر(s, vkb, usage,
                               بفر_سائز, &create_desc, &import_desc,
                               props);
    اگر (err < 0) {
        av_بفر_unref(&ref);
        av_refstruct_unref(&vkb);
        واپس err;
    }

    اگر (usage & VK_بفر_USAGE_SHADER_DEVICE_پتہ_ثنائی_ہندسہ) {
        Vk_بفر_Device_پتہ_Info پتہ_info = {
            .sType = VK_STRUCTURE_TYPE_بفر_DEVICE_پتہ_INFO,
            .بفر = vkb->buf,
        };
        vkb->پتہ = vk->Get_بفر_Device_پتہ(s->hwctx->act_dev, &پتہ_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_انحراف = offs;
    vkb->پتہ       += offs;
    vkb->mapped_mem     = src_ڈیٹا;
    vkb->سائز           = بفر_سائز - offs;

    *dst = vkb;

    واپس 0;
}

صحیح ff_vk_shader_جوڑو_ڈالو_const(FFVulkanShader *shd, صحیح انحراف, صحیح سائز,
                                Vk_Shader_Stage_Flag_بٹ stage)
{
    Vk_ڈالو_Constant_Range *pc = &shd->ڈالو_consts[shd->ڈالو_consts_عدد++];
    av_assert1(shd->ڈالو_consts_عدد < FF_VK_MAX_ڈالو_CONSTS);
    pc->stageFlags = stage;
    pc->انحراف = انحراف;
    pc->سائز = سائز;
    واپس 0;
}

صحیح ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       صحیح unnorm_coords, VkFilter filt)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_منوال = (unnorm_coords || filt == VK_FILTER_قریب_ترین) ?
                      VK_SAMPLER_MIPMAP_منوال_قریب_ترین :
                      VK_SAMPLER_MIPMAP_منوال_خطی,
        .پتہ_منوال_U = VK_SAMPLER_پتہ_منوال_CLAMP_مقصد_کنارہ,
        .پتہ_منوال_V = sampler_info.پتہ_منوال_U,
        .پتہ_منوال_W = sampler_info.پتہ_منوال_U,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, صحیح p)
{
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    صحیح nb_images = ff_vk_گنتی_images(vkf);
    صحیح nb_planes = av_pix_fmt_گنتی_planes(hwfc->sw_format);

    ساکن ثابت VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_ثنائی_ہندسہ,
                                                       VK_IMAGE_ASPECT_PLANE_1_ثنائی_ہندسہ,
                                                       VK_IMAGE_ASPECT_PLANE_2_ثنائی_ہندسہ, };

    اگر (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        واپس VK_IMAGE_ASPECT_COLOR_ثنائی_ہندسہ;

    واپس plane_aspect[p];
}

صحیح ff_vk_mt_is_np_rgb(شمار AVPixelFormat pix_fmt)
{
    اگر (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        واپس 1;
    واپس 0;
}

خالی ff_vk_سیٹ_perm(شمار AVPixelFormat pix_fmt, صحیح lut[4], صحیح inv)
{
    انتخاب (pix_fmt) {
    حالت AV_PIX_FMT_GBRP:
    حالت AV_PIX_FMT_GBRAP:
    حالت AV_PIX_FMT_GBRAP10:
    حالت AV_PIX_FMT_GBRAP12:
    حالت AV_PIX_FMT_GBRAP14:
    حالت AV_PIX_FMT_GBRAP16:
    حالت AV_PIX_FMT_GBRAPF16:
    حالت AV_PIX_FMT_GBRP10:
    حالت AV_PIX_FMT_GBRP12:
    حالت AV_PIX_FMT_GBRP14:
    حالت AV_PIX_FMT_GBRP16:
    حالت AV_PIX_FMT_GBRPF16:
    حالت AV_PIX_FMT_GBRPF32:
    حالت AV_PIX_FMT_GBRAP32:
    حالت AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        توڑو;
    حالت AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        توڑو;
    حالت AV_PIX_FMT_BGRA:
    حالت AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        توڑو;
    طےشدہ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        توڑو;
    }

    اگر (inv) {
        صحیح lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        برائے (صحیح i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    واپس;
}

ثابت حرف *ff_vk_shader_rep_fmt(شمار AVPixelFormat pix_fmt,
                                 شمار FFVkShaderRepFormat rep_fmt)
{
    انتخاب (pix_fmt) {
    حالت AV_PIX_FMT_RGBA:
    حالت AV_PIX_FMT_BGRA:
    حالت AV_PIX_FMT_RGB24:
    حالت AV_PIX_FMT_BGR24:
    حالت AV_PIX_FMT_BGR0:
    حالت AV_PIX_FMT_RGB0:
    حالت AV_PIX_FMT_RGB565:
    حالت AV_PIX_FMT_BGR565:
    حالت AV_PIX_FMT_UYVA:
    حالت AV_PIX_FMT_YUYV422:
    حالت AV_PIX_FMT_UYVY422: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_X2RGB10:
    حالت AV_PIX_FMT_X2BGR10:
    حالت AV_PIX_FMT_Y210:
    حالت AV_PIX_FMT_XV30: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = تہی,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_RGB48:
    حالت AV_PIX_FMT_RGBA64:
    حالت AV_PIX_FMT_Y212:
    حالت AV_PIX_FMT_Y216:
    حالت AV_PIX_FMT_XV36:
    حالت AV_PIX_FMT_XV48: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_RGBAF16: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_RGBF32:
    حالت AV_PIX_FMT_RGBAF32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_RGB96:
    حالت AV_PIX_FMT_RGBA128: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = تہی,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        واپس rep_tab[rep_fmt];
    }
    حالت AV_PIX_FMT_GBRP:
    حالت AV_PIX_FMT_GRAY8:
    حالت AV_PIX_FMT_GBRAP:
    حالت AV_PIX_FMT_YUV420P:
    حالت AV_PIX_FMT_YUV422P:
    حالت AV_PIX_FMT_YUV444P:
    حالت AV_PIX_FMT_YUVA420P:
    حالت AV_PIX_FMT_YUVA422P:
    حالت AV_PIX_FMT_YUVA444P: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_GRAY10:
    حالت AV_PIX_FMT_GRAY12:
    حالت AV_PIX_FMT_GRAY14:
    حالت AV_PIX_FMT_GRAY16:
    حالت AV_PIX_FMT_GBRAP10:
    حالت AV_PIX_FMT_GBRAP12:
    حالت AV_PIX_FMT_GBRAP14:
    حالت AV_PIX_FMT_GBRAP16:
    حالت AV_PIX_FMT_GBRAPF16:
    حالت AV_PIX_FMT_GBRP10:
    حالت AV_PIX_FMT_GBRP12:
    حالت AV_PIX_FMT_GBRP14:
    حالت AV_PIX_FMT_GBRP16:
    حالت AV_PIX_FMT_GBRPF16:
    حالت AV_PIX_FMT_XYZP12:
    حالت AV_PIX_FMT_YUV420P10:
    حالت AV_PIX_FMT_YUV420P12:
    حالت AV_PIX_FMT_YUV420P16:
    حالت AV_PIX_FMT_YUV422P10:
    حالت AV_PIX_FMT_YUV422P12:
    حالت AV_PIX_FMT_YUV422P16:
    حالت AV_PIX_FMT_YUV444P10:
    حالت AV_PIX_FMT_YUV444P12:
    حالت AV_PIX_FMT_YUV444P16:
    حالت AV_PIX_FMT_YUVA420P10:
    حالت AV_PIX_FMT_YUVA420P16:
    حالت AV_PIX_FMT_YUVA422P10:
    حالت AV_PIX_FMT_YUVA422P12:
    حالت AV_PIX_FMT_YUVA422P16:
    حالت AV_PIX_FMT_YUVA444P10:
    حالت AV_PIX_FMT_YUVA444P12:
    حالت AV_PIX_FMT_YUVA444P16:
    حالت AV_PIX_FMT_BAYER_RGGB16: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_GRAY32:
    حالت AV_PIX_FMT_GRAYF32:
    حالت AV_PIX_FMT_GBRPF32:
    حالت AV_PIX_FMT_GBRAPF32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_GBRAP32: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = تہی,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_NV12:
    حالت AV_PIX_FMT_NV16:
    حالت AV_PIX_FMT_NV24: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_P010:
    حالت AV_PIX_FMT_P210:
    حالت AV_PIX_FMT_P410: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = تہی,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        واپس rep_tab[rep_fmt];
    };
    حالت AV_PIX_FMT_P012:
    حالت AV_PIX_FMT_P016:
    حالت AV_PIX_FMT_P212:
    حالت AV_PIX_FMT_P216:
    حالت AV_PIX_FMT_P412:
    حالت AV_PIX_FMT_P416: {
        ثابت حرف *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        واپس rep_tab[rep_fmt];
    };
    طےشدہ:
        واپس "rgba32f";
    }
}

ساکن خالی reset_imageviews(AVRefStructOpaque غیر_مستعمل, خالی *obj)
{
    FFVkImageViews *iv = obj;

    برائے (صحیح i = 0; i < iv->nb_views; i++) {
        اگر (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, حجم(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, صحیح nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_عدد_ڈیٹا_اشارے);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    اگر (!iv)
        واپس تہی;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    واپس iv;
}

VkFormat ff_vk_map_fmt_مقصد_rep(VkFormat fmt, شمار FFVkShaderRepFormat rep_fmt)
{
#تعریف_کرو REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#تعریف_کرو REPS_FMT_PACK(fmt, عدد) \
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
#تعریف_منسوخ REPS_FMT_PACK
#تعریف_منسوخ REPS_FMT

    اگر (fmt == VK_FORMAT_UNDEFINED)
        واپس VK_FORMAT_UNDEFINED;

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        اگر (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            واپس fmts_map[i][rep_fmt];
    }

    واپس VK_FORMAT_UNDEFINED;
}

صحیح ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, صحیح plane, شمار FFVkShaderRepFormat rep_fmt)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    AVVulkan_چوکھٹے_Context *vkfc = hwfc->hwctx;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];
    ثابت صحیح nb_images = ff_vk_گنتی_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ثنائی_ہندسہ_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_ثنائی_ہندسہ_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_اگلا      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_مقصد_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_شناختی_عنصر_map,
        .subresourceRange = {
            .aspect_نقاب = ff_vk_aspect_flag(f, plane),
            .level_گنتی = 1,
            .layer_گنتی = 1,
        },
    };
    اگر (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        واپس AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_نقاب;

    واپس 0;
}

صحیح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_عدد_ڈیٹا_اشارے],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_عدد_ڈیٹا_اشارے])
{
    صحیح err = 0;
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    AVVulkan_چوکھٹے_Context *vkfc = hwfc->hwctx;
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)f->ڈیٹا[0];
    ثابت صحیح nb_images = ff_vk_گنتی_images(vkf);
    ثابت صحیح nb_planes = av_pix_fmt_گنتی_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_عدد_ڈیٹا_اشارے] = { 0 };

    برائے (صحیح i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ثنائی_ہندسہ_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_ثنائی_ہندسہ_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_اگلا      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_شناختی_عنصر_map,
            .subresourceRange = {
                .aspect_نقاب = ff_vk_aspect_flag(f, i),
                .level_گنتی = 1,
                .layer_گنتی = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            جاؤ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    برائے (صحیح i = 0; i < nb_planes; i++)
        ff_vk_exec_جوڑو_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    حافظہ_نقل(views, tmp_views, nb_planes*حجم(*views));

    واپس 0;

fail:
    برائے (صحیح i = 0; i < nb_planes; i++)
        اگر (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    واپس err;
}

صحیح ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_عدد_ڈیٹا_اشارے],
                            AVFrame *f, شمار FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    ثابت VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ثابت صحیح nb_planes = av_pix_fmt_گنتی_planes(hwfc->sw_format);
    VkFormat fmts[AV_عدد_ڈیٹا_اشارے] = { 0 };

    برائے (صحیح i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_مقصد_rep(rep_fmts[i], rep_fmt);
        اگر (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            واپس AVERROR(EINVAL);
        }
    }

    واپس ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

خالی ff_vk_چوکھٹا_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_حافظہ_Barrier2 *bar, صحیح *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    صحیح ملا = -1;
    AVVk_چوکھٹا *vkf = (AVVk_چوکھٹا *)pic->ڈیٹا[0];
    ثابت صحیح nb_images = ff_vk_گنتی_images(vkf);
    برائے (صحیح i = 0; i < e->nb_چوکھٹا_deps; i++)
        اگر (e->چوکھٹا_deps[i]->ڈیٹا[0] == pic->ڈیٹا[0]) {
            اگر (e->چوکھٹا_update[i])
                ملا = i;
            توڑو;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    برائے (صحیح i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_حافظہ_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_حافظہ_BARRIER_2,
            .p_اگلا = تہی,
            .src_Stage_نقاب = src_stage,
            .dst_Stage_نقاب = dst_stage,
            .src_Access_نقاب = ملا >= 0 ? e->access_dst[ملا] : VK_ACCESS_2_NONE,
            .dst_Access_نقاب = new_access,
            .oldLayout = ملا >= 0 ? e->layout_dst[ملا] : vkf->layout[0],
            .newLayout = new_layout,
            .src_قطار_Family_اشاریہ = ملا >= 0 ? e->قطار_family_dst[ملا] : vkf->قطار_family[0],
            .dst_قطار_Family_اشاریہ = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_نقاب = VK_IMAGE_ASPECT_COLOR_ثنائی_ہندسہ,
                .layer_گنتی = 1,
                .level_گنتی = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_چوکھٹا(s, e, pic, &bar[*nb_bar - nb_images], تہی);
}

صحیح ff_vk_shader_بھرو(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_سائز[3], uint32_t required_subgroup_سائز)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    حافظہ_نقل(shd->lg_سائز, wg_سائز, 3*حجم(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_سائز_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_سائز_CREATE_INFO,
        .required_Subgroup_سائز = required_subgroup_سائز,
    };

    انتخاب (shd->stage) {
    حالت VK_SHADER_STAGE_ANY_کامیابی_ثنائی_ہندسہ_KHR:
    حالت VK_SHADER_STAGE_CALLABLE_ثنائی_ہندسہ_KHR:
    حالت VK_SHADER_STAGE_CLOSEST_کامیابی_ثنائی_ہندسہ_KHR:
    حالت VK_SHADER_STAGE_INTERSECTION_ثنائی_ہندسہ_KHR:
    حالت VK_SHADER_STAGE_ناکامی_ثنائی_ہندسہ_KHR:
    حالت VK_SHADER_STAGE_RAYGEN_ثنائی_ہندسہ_KHR:
        shd->bind_نقطہ = VK_PIPELINE_BIND_نقطہ_RAY_TRACING_KHR;
        توڑو;
    حالت VK_SHADER_STAGE_COMPUTE_ثنائی_ہندسہ:
        shd->bind_نقطہ = VK_PIPELINE_BIND_نقطہ_COMPUTE;
        توڑو;
    طےشدہ:
        shd->bind_نقطہ = VK_PIPELINE_BIND_نقطہ_GRAPHICS;
        توڑو;
    };

    واپس 0;
}

ساکن صحیح init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_سیٹ_Layouts            = shd->desc_layout,
        .سیٹ_Layout_گنتی         = shd->nb_descriptor_sets,
        .ڈالو_Constant_Range_گنتی = shd->ڈالو_consts_عدد,
        .p_ڈالو_Constant_Ranges    = shd->ڈالو_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

ساکن صحیح create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ثابت uint8_t *spirv, size_t spirv_len)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_اگلا    = تہی,
        .flags    = 0x0,
        .p_رمز    = (خالی *)spirv,
        .رمز_سائز = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

ساکن صحیح init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ثابت حرف *entrypoint)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_اگلا = shd->subgroup_info.required_Subgroup_سائز ?
                     &shd->subgroup_info : تہی,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_سائز ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_بھرا_SUBGROUPS_ثنائی_ہندسہ : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    اگر (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        واپس AVERROR_EXTERNAL;
    }

    واپس 0;
}

ساکن صحیح init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_نتیجہ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    صحیح has_singular = 0;
    صحیح max_descriptors = 0;
    برائے (صحیح i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_سیٹ[i].nb_bindings);
        اگر (shd->desc_سیٹ[i].singular)
            has_singular = 1;
    }
    shd->use_ڈالو = (s->extensions & FF_VK_EXT_ڈالو_DESCRIPTOR) &&
                    (max_descriptors <= s->ڈالو_desc_props.max_ڈالو_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    برائے (صحیح i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_سیٹ *سیٹ = &shd->desc_سیٹ[i];
        Vk_Descriptor_سیٹ_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_سیٹ_LAYOUT_CREATE_INFO,
            .binding_گنتی = سیٹ->nb_bindings,
            .pBindings = سیٹ->binding,
            .flags = (shd->use_ڈالو) ?
                     VK_DESCRIPTOR_سیٹ_LAYOUT_CREATE_ڈالو_DESCRIPTOR_ثنائی_ہندسہ_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_سیٹ_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            واپس AVERROR_EXTERNAL;
        }
    }

    واپس 0;
}

صحیح ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ثابت حرف *spirv, size_t spirv_len,
                      ثابت حرف *entrypoint)
{
    صحیح err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_اندراج spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t داخلہ_سائز = spirv_len;

    اگر (shd->precompiled) {
        اگر (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_اندراج_گنتی = 0,
                .p_ڈیٹا = shd->lg_سائز,
                .ڈیٹا_سائز_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_اندراج *spe = (خالی *)shd->specialization_info->pMapEntries;
        برائے (صحیح i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_اندراج_گنتی++] = (Vk_Specialization_Map_اندراج) {
                .constantID = 253 + i,
                .انحراف = shd->specialization_info->ڈیٹا_سائز_2 + i*حجم(uint32_t),
                .سائز = حجم(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_ڈیٹا;
        حافظہ_نقل(&spd[shd->specialization_info->ڈیٹا_سائز_2],
               shd->lg_سائز, 3*حجم(uint32_t));
        shd->specialization_info->ڈیٹا_سائز_2 += 3*حجم(uint32_t);

#اگر CONFIG_SHADER_COMPRESSION
        uint8_t *برآمد;
        size_t برآمد_len;
        صحیح ret = ff_zlib_expand(s, &برآمد, &برآمد_len, spirv, spirv_len);
        اگر (ret < 0)
            واپس ret;
        spirv = برآمد;
        spirv_len = برآمد_len;
#اگر_ختم
    }

    err = init_descriptors(s, shd);
    اگر (err < 0)
        جاؤ انتہا;

    err = init_pipeline_layout(s, shd);
    اگر (err < 0)
        جاؤ انتہا;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    اگر (err < 0)
        جاؤ انتہا;

    انتخاب (shd->bind_نقطہ) {
    حالت VK_PIPELINE_BIND_نقطہ_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        توڑو;
    طےشدہ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_نقطہ);
        err = AVERROR(EINVAL);
        جاؤ انتہا;
        توڑو;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    اگر (err < 0)
        جاؤ انتہا;

    اگر (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    ورنہ
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    اگر (داخلہ_سائز != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", داخلہ_سائز);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

انتہا:
    اگر (shd->precompiled) {
        shd->specialization_info->map_اندراج_گنتی -= 3;
        shd->specialization_info->ڈیٹا_سائز_2 -= 3*حجم(uint32_t);
    }
#اگر CONFIG_SHADER_COMPRESSION
    اگر (shd->precompiled)
        av_free((خالی *)spirv);
#اگر_ختم
    واپس err;
}

خالی ff_vk_shader_جوڑو_descriptor_سیٹ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سیٹ_Binding *desc, صحیح nb,
                                     صحیح singular)
{
    FFVulkan_Descriptor_سیٹ *سیٹ = &shd->desc_سیٹ[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    برائے (صحیح i = 0; i < nb; i++) {
        سیٹ->binding[i].binding            = i;
        سیٹ->binding[i].descriptorType     = desc[i].type;
        سیٹ->binding[i].descriptor_گنتی    = FFMAX(desc[i].elems, 1);
        سیٹ->binding[i].stageFlags         = desc[i].stages;
        سیٹ->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    برائے (صحیح i = 0; i < nb; i++) {
        صحیح j;
        برائے (j = 0; j < shd->nb_desc_pool_سائز; j++)
            اگر (shd->desc_pool_سائز[j].type == desc[i].type)
                توڑو;
        اگر (j >= shd->nb_desc_pool_سائز) {
            shd->nb_desc_pool_سائز++;
            av_assert1(shd->nb_desc_pool_سائز < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_سائز[j].type             = desc[i].type;
        shd->desc_pool_سائز[j].descriptor_گنتی += FFMAX(desc[i].elems, 1);
    }

    سیٹ->singular = singular;
    سیٹ->nb_bindings = nb;
}

صحیح ff_vk_shader_رجسٹر_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    اگر (!shd->nb_descriptor_sets)
        واپس 0;

    FFVulkan_Shader_ڈیٹا *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    اگر (!shd->use_ڈالو) {
        Vk_نتیجہ ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_سیٹ_Layout *tmp_layouts;
        Vk_Descriptor_سیٹ_Allocate_Info سیٹ_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        برائے (صحیح i = 0; i < shd->nb_desc_pool_سائز; i++)
            shd->desc_pool_سائز[i].descriptor_گنتی *= pool->pool_سائز;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_سائز,
            .pool_سائز_گنتی = shd->nb_desc_pool_سائز,
            .maxSets = sd->nb_descriptor_sets*pool->pool_سائز,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            واپس AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, حجم(*tmp_layouts));
        اگر (!tmp_layouts)
            واپس AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        برائے (صحیح i = 0; i < pool->pool_سائز; i++)
            برائے (صحیح j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        سیٹ_alloc_info = (Vk_Descriptor_سیٹ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_سیٹ_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_سیٹ_Layouts        = tmp_layouts,
            .descriptor_سیٹ_گنتی = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        حجم(*tmp_layouts));
        اگر (!sd->desc_sets) {
            av_free(tmp_layouts);
            واپس AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &سیٹ_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        اگر (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            واپس AVERROR_EXTERNAL;
        }
    }

    واپس 0;
}

ساکن اندرونی ثابت FFVulkan_Shader_ڈیٹا *get_shd_ڈیٹا(FFVkExecContext *e,
                                                     ثابت FFVulkanShader *shd)
{
    برائے (صحیح i = 0; i < e->والد->nb_reg_shd; i++)
        اگر (e->والد->reg_shd[i].shd == shd)
            واپس &e->والد->reg_shd[i];
    واپس تہی;
}

ساکن اندرونی خالی update_سیٹ_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, صحیح سیٹ,
                                         Vk_Write_Descriptor_سیٹ *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_سیٹ *desc_سیٹ = &shd->desc_سیٹ[سیٹ];
    ثابت FFVulkan_Shader_ڈیٹا *sd = get_shd_ڈیٹا(e, shd);

    اگر (desc_سیٹ->singular) {
        برائے (صحیح i = 0; i < e->والد->pool_سائز; i++) {
            write_info->dst_سیٹ = sd->desc_sets[i*sd->nb_descriptor_sets + سیٹ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, تہی);
        }
    } ورنہ {
        اگر (shd->use_ڈالو) {
            vk->Cmd_ڈالو_Descriptor_سیٹ_KHR(e->buf,
                                        shd->bind_نقطہ,
                                        shd->pipeline_layout,
                                        سیٹ, 1,
                                        write_info);
        } ورنہ {
            write_info->dst_سیٹ = sd->desc_sets[e->idx*sd->nb_descriptor_sets + سیٹ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, تہی);
        }
    }
}

صحیح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحیح سیٹ, صحیح bind, صحیح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_سیٹ *desc_سیٹ = &shd->desc_سیٹ[سیٹ];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_سیٹ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سیٹ,
        .dstBinding = bind,
        .descriptor_گنتی = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_سیٹ->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_سیٹ_pool_write(s, e, shd, سیٹ, &desc_pool_write_info);

    واپس 0;
}

خالی ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحیح سیٹ, صحیح binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_چوکھٹے_ctx->ڈیٹا;
    ثابت صحیح nb_planes = av_pix_fmt_گنتی_planes(hwfc->sw_format);

    برائے (صحیح i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, سیٹ, binding, i,
                                views[i], layout, sampler);
}

صحیح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحیح سیٹ, صحیح bind, صحیح elem,
                                    FFVk_بفر *buf, Vk_Device_سائز انحراف, Vk_Device_سائز len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_سیٹ *desc_سیٹ = &shd->desc_سیٹ[سیٹ];

    Vk_Descriptor_بفر_Info desc_pool_write_info_buf = {
        .بفر = buf->buf,
        .انحراف = buf->virtual_انحراف + انحراف,
        .range = len,
    };
    Vk_Write_Descriptor_سیٹ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_سیٹ,
        .dstBinding = bind,
        .descriptor_گنتی = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_سیٹ->binding[bind].descriptorType,
        .p_بفر_Info = &desc_pool_write_info_buf,
    };
    update_سیٹ_pool_write(s, e, shd, سیٹ, &desc_pool_write_info);

    واپس 0;
}

خالی ff_vk_shader_update_ڈالو_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بٹ stage,
                                    صحیح انحراف, size_t سائز, خالی *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ڈالو_Constants(e->buf, shd->pipeline_layout,
                         stage, انحراف, سائز, src);
}

خالی ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ثابت FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ثابت FFVulkan_Shader_ڈیٹا *sd = get_shd_ڈیٹا(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_نقطہ, shd->pipeline);

    اگر (sd && sd->nb_descriptor_sets) {
        اگر (!shd->use_ڈالو) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_نقطہ, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, تہی);
        }
    }
}

خالی ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#اگر 0
    اگر (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#اگر_ختم

    اگر (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    اگر (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    برائے (صحیح i = 0; i < shd->nb_descriptor_sets; i++)
        اگر (shd->desc_layout[i])
            vk->Destroy_Descriptor_سیٹ_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

خالی ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#اگر_تعریف_شدہ VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#اگر_ختم
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_بفر_unref(&s->device_ref);
    av_بفر_unref(&s->چوکھٹے_ref);
}

صحیح ff_vk_init(FFVulkanContext *s, خالی *log_والد,
               AVBufferRef *device_ref, AVBufferRef *چوکھٹے_ref)
{
    صحیح err;

    ساکن ثابت AVClass vulkan_context_class = {
        .class_name       = "vk",
        .نسخہ          = LIBAVUTIL_نسخہ_INT,
        .والد_log_context_انحراف = offsetof(FFVulkanContext, log_والد),
    };

    memset(s, 0, حجم(*s));
    s->log_والد = log_والد;
    s->class      = &vulkan_context_class;

    اگر (چوکھٹے_ref) {
        s->چوکھٹے_ref = av_بفر_ref(چوکھٹے_ref);
        اگر (!s->چوکھٹے_ref)
            واپس AVERROR(ENOMEM);

        s->چوکھٹے = (AVHWFramesContext *)s->چوکھٹے_ref->ڈیٹا;
        s->hwfc = s->چوکھٹے->hwctx;

        device_ref = s->چوکھٹے->device_ref;
    }

    s->device_ref = av_بفر_ref(device_ref);
    اگر (!s->device_ref) {
        ff_vk_uninit(s);
        واپس AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->ڈیٹا;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_مقصد_نقاب(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_مقصد_نقاب(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_بھرو_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    اگر (err < 0) {
        ff_vk_uninit(s);
        واپس err;
    }

    err = ff_vk_بھرو_props(s);
    اگر (err < 0) {
        ff_vk_uninit(s);
        واپس err;
    }

    واپس 0;
}
