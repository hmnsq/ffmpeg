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

#అన్తర్భావ "config.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "random_seed.h"
#అన్తర్భావ "refstruct.h"

#అన్తర్భావ "vulkan.h"
#అన్తర్భావ "libavutil/vulkan_loader.h"

#ఒకవేళ CONFIG_SHADER_COMPRESSION
#అన్తర్భావ "libavutil/zlib_utils.h"
#అయితే_ముగింపు

స్థిరరాశి VkComponentMapping ff_comp_తటస్థం_map = {
    .r = VK_COMPONENT_SWIZZLE_తటస్థం,
    .g = VK_COMPONENT_SWIZZLE_తటస్థం,
    .b = VK_COMPONENT_SWIZZLE_తటస్థం,
    .a = VK_COMPONENT_SWIZZLE_తటస్థం,
};

/* Converts return values to strings */
స్థిరరాశి అక్షరం *ff_vk_ret2str(Vk_ఫలితం res)
{
#నిర్వచించు CASE(VAL) స్థితి VAL: తిరిగి #VAL
    ఎంపిక (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_సమితి);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_బహిర్గతం_యొక్క_HOST_జ్ఞాపకం);
    CASE(VK_ERROR_బహిర్గతం_యొక్క_DEVICE_జ్ఞాపకం);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_కోల్పోయిన);
    CASE(VK_ERROR_జ్ఞాపకం_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_బహిర్గతం_యొక్క_POOL_జ్ఞాపకం);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_చిరునామా);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_కోల్పోయిన_KHR);
    CASE(VK_ERROR_NATIVE_కిటికీ_లోపల_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_బహిర్గతం_యొక్క_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_సంస్కరణ_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_నిండిన_SCREEN_EXCLUSIVE_బహుళకం_కోల్పోయిన_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_పూర్తి_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    అప్రమేయ: తిరిగి "Unknown error";
    }
#నిర్వచనం_రద్దు CASE
}

/* Malitia pura, Khronos */
#నిర్వచించు FN_MAP_గమ్యం(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## గమ్యం_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_బిట్టు,                   \
               VK_IMAGE_USAGE_SAMPLED_బిట్టు);                             \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_TRANSFER_SRC_బిట్టు,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_బిట్టు);                        \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_TRANSFER_DST_బిట్టు,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_బిట్టు);                        \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_బిట్టు,                   \
               VK_IMAGE_USAGE_STORAGE_బిట్టు);                             \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_బిట్టు,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_బిట్టు);                    \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_బిట్టు_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR);                \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_బిట్టు_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_బిట్టు_KHR);                \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_బిట్టు_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_బిట్టు_KHR);                \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ఆదానం_బిట్టు_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR);                \
        MAP_గమ్యం(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_బిట్టు_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT);                   \
        తిరిగి dst;                                                     \
    }

#నిర్వచించు MAP_గమ్యం(flag1, flag2) ఒకవేళ (src & flag2) dst |= flag1;
FN_MAP_గమ్యం(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#నిర్వచనం_రద్దు MAP_గమ్యం
#నిర్వచించు MAP_గమ్యం(flag1, flag2) ఒకవేళ (src & flag1) dst |= flag2;
FN_MAP_గమ్యం(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#నిర్వచనం_రద్దు MAP_గమ్యం
#నిర్వచనం_రద్దు FN_MAP_గమ్యం

స్థిర శూన్య ఎక్కించు_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    కొరకు (పూర్ణాంకం i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        పూర్ణాంకం skip = 0;
        కొరకు (పూర్ణాంకం j = 0; j < s->nb_qfs; j++) {
            ఒకవేళ (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                ఆపు;
            }
        }
        ఒకవేళ (skip)
            కొనసాగు;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

స్థిర శూన్య reset_imageviews(AVRefStructOpaque వాడని, శూన్య *obj);

పూర్ణాంకం ff_vk_ఎక్కించు_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_కొలత_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->నెట్టు_desc_props, FF_VK_EXT_నెట్టు_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_నెట్టు_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_జ్ఞాపకం,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_జ్ఞాపకం_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_మాతృక_props, FF_VK_EXT_COOP_మాతృక,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_మాతృక_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_సదిశ_props, FF_VK_EXT_LONG_సదిశ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_సదిశ_PROPERTIES_EXT);
#అయితే_ముగింపు

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#అయితే_ముగింపు

    ఒకవేళ (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(పరిమాణం(FFVkImageViews), 0,
                                                         ఖాళీ, ఖాళీ, reset_imageviews,
                                                         ఖాళీ, ఖాళీ);
        ఒకవేళ (!s->imageviews_pool)
            తిరిగి AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(పరిమాణం(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_లెక్క = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_లెక్క = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    ఒకవేళ (s->host_image_props.copy_Src_Layout_లెక్క == 512 ||
        s->host_image_props.copy_Dst_Layout_లెక్క == 512) {
        VkImageLayout *new_array;
        size_t new_కొలత;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ఖాళీ;
        s->host_image_props.copy_Src_Layout_లెక్క =
        s->host_image_props.copy_Dst_Layout_లెక్క = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_కొలత = s->host_image_props.copy_Src_Layout_లెక్క +
                   s->host_image_props.copy_Dst_Layout_లెక్క;
        new_కొలత *= పరిమాణం(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_కొలత);
        ఒకవేళ (!new_array)
            తిరిగి AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_లెక్క;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_జ్ఞాపకం_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    కొరకు (పూర్ణాంకం i = 0; i < s->mprops.జ్ఞాపకం_Type_లెక్క; i++)
        s->host_cached_flag |= s->mprops.జ్ఞాపకం_Types[i].propertyFlags &
                               VK_జ్ఞాపకం_PROPERTY_HOST_CACHED_బిట్టు;

    ఎక్కించు_enabled_qfs(s);

    ఒకవేళ (s->qf_props)
        తిరిగి 0;

    vk->Get_Physical_Device_వరుస_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ఖాళీ);

    s->qf_props = av_calloc(s->tot_nb_qfs, పరిమాణం(*s->qf_props));
    ఒకవేళ (!s->qf_props)
        తిరిగి AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, పరిమాణం(*s->query_props));
    ఒకవేళ (!s->qf_props) {
        av_freep(&s->qf_props);
        తిరిగి AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, పరిమాణం(*s->video_props));
    ఒకవేళ (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        తిరిగి AVERROR(ENOMEM);
    }

#నిర్వచితమైతే VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, పరిమాణం(*s->ownership_props));
    ఒకవేళ (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        తిరిగి AVERROR(ENOMEM);
    }
#అయితే_ముగింపు

    కొరకు (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_వరుస_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_వరుస_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_వరుస,
                         VK_STRUCTURE_TYPE_వరుస_FAMILY_QUERY_ఫలితం_స్థితి_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_వరుస,
                         VK_STRUCTURE_TYPE_వరుస_FAMILY_VIDEO_PROPERTIES_KHR);
#నిర్వచితమైతే VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_వరుస_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#అయితే_ముగింపు
    }

    vk->Get_Physical_Device_వరుస_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    ఒకవేళ (s->extensions & FF_VK_EXT_COOP_మాతృక) {
        vk->Get_Physical_Device_Cooperative_మాతృక_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ఖాళీ);

        ఒకవేళ (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                పరిమాణం(Vk_Cooperative_మాతృక_Properties_KHR));
            కొరకు (పూర్ణాంకం i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_మాతృక_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_మాతృక_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_మాతృక_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    తిరిగి 0;
}

AVVulkan_Device_వరుస_Family *ff_vk_qf_కనుగొను(FFVulkanContext *s,
                                         Vk_వరుస_Flag_బిట్లు dev_family,
                                         Vk_Video_Codec_Operation_Flag_బిట్లు_KHR vid_ops)
{
    కొరకు (పూర్ణాంకం i = 0; i < s->hwctx->nb_qf; i++) {
        ఒకవేళ ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            తిరిగి &s->hwctx->qf[i];
        }
    }
    తిరిగి ఖాళీ;
}

స్థిర శూన్య exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

శూన్య ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        ఒకవేళ (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_లెక్క = 1,
                .pSemaphores = &e->sem,
                .p_విలువలు = &e->sem_విలువ,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->తాళం_2);
    }

    /* Free shader-specific data */
    కొరకు (పూర్ణాంకం i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_దత్తాంశం *sd = &pool->reg_shd[i];

        ఒకవేళ (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++) {
        ఒకవేళ (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        ఒకవేళ (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    ఒకవేళ (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_దత్తాంశం);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_కొలత = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
స్థిర atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ఖాళీ)->qf)];
స్థిర AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

స్థిర శూన్య exec_pool_phase_విత్తనం(శూన్య)
{
    uint32_t విత్తనం = av_get_random_విత్తనం();
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], విత్తనం, memory_order_relaxed);
}

పూర్ణాంకం ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_వరుస_Family *qf,
                         FFVkExecPool *pool, పూర్ణాంకం nb_contexts,
                         పూర్ణాంకం nb_queries, VkQueryType query_type, పూర్ణాంకం query_64bit,
                         స్థిరరాశి శూన్య *query_create_pnext)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_బఫరు_Allocate_Info cbuf_create;

    స్థిరరాశి VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ఖాళీ;

    atomic_init(&pool->idx, 0);

    ఒకవేళ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_కనుగొను_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        ఒకవేళ (!ef)
            తిరిగి AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*పరిమాణం(*pool->cmd_buf_pools));
    ఒకవేళ (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*పరిమాణం(*pool->cmd_bufs));
    ఒకవేళ (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    కొరకు (పూర్ణాంకం i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_బిట్టు |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_బఫరు_బిట్టు,
            .వరుస_Family_సూచీ   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_బఫరు_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_బఫరు_ALLOCATE_INFO,
            .level              = VK_COMMAND_బఫరు_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_బఫరు_లెక్క = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }
    }

    /* Query pool */
    ఒకవేళ (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_తదుపరి = query_create_pnext,
            .queryType = query_type,
            .query_లెక్క = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_స్థితి_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        ఒకవేళ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            పూర్ణాంకం nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_స్థితి_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } లేకపోతే ఒకవేళ (query_type == VK_QUERY_TYPE_ఫలితం_స్థితి_ONLY_KHR) {
            pool->query_స్థితి_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_కొలత = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_దత్తాంశం = av_calloc(nb_contexts, pool->qd_కొలత);
        ఒకవేళ (!pool->query_దత్తాంశం) {
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, పరిమాణం(*pool->contexts));
    ఒకవేళ (!pool->contexts) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    pool->pool_కొలత = nb_contexts;

    కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++)
        pthread_mutex_init(&pool->contexts[i].తాళం_2, ఖాళీ);

#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    పూర్ణాంకం అంతర్గత_వరుస_sync = 0;
    ఒకవేళ (s->extensions & FF_VK_EXT_అంతర్గత_వరుస_SYNC) {
        స్థిరరాశి VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_కనుగొను_struct(s->hwctx->device_features.p_తదుపరి,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        అంతర్గత_వరుస_sync = iqs && iqs->internallySynchronizedQueues;
    }
#అయితే_ముగింపు

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_విత్తనం);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    పూర్ణాంకం pin_వరుస = qf->flags & (VK_వరుస_VIDEO_DECODE_బిట్టు_KHR |
                                 VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR);

    /* Init contexts */
    కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_తదుపరి = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->మాతృ = pool;

        /* Query data */
        e->query_దత్తాంశం = ((uint8_t *)pool->query_దత్తాంశం) + pool->qd_కొలత*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_వరుస ? phase % qf->అంకె : (i + phase) % qf->అంకె;
        e->qf = qf->idx;
        Vk_Device_వరుస_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_వరుస_INFO_2,
#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
            .flags            = అంతర్గత_వరుస_sync ?
                                VK_DEVICE_వరుస_CREATE_INTERNALLY_SYNCHRONIZED_బిట్టు_KHR : 0,
#అయితే_ముగింపు
            .వరుస_Family_సూచీ = qf->idx,
            .వరుస_సూచీ       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->వరుస);
    }

    తిరిగి 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    తిరిగి err;
}

Vk_ఫలితం ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              శూన్య **దత్తాంశం, Vk_Query_ఫలితం_Flag_బిట్లు flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    స్థిరరాశి FFVkExecPool *pool = e->మాతృ;
    Vk_Query_ఫలితం_Flags qf = flags & ~(VK_QUERY_ఫలితం_64_బిట్టు |
                                      VK_QUERY_ఫలితం_WITH_స్థితి_బిట్టు_KHR);

    ఒకవేళ (!e->query_దత్తాంశం) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        తిరిగి VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_ఫలితం_64_బిట్టు : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_ఫలితం_WITH_స్థితి_బిట్టు_KHR : 0x0;

    ఒకవేళ (దత్తాంశం)
        *దత్తాంశం = e->query_దత్తాంశం;

    తిరిగి vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_కొలత, e->query_దత్తాంశం,
                                   pool->qd_కొలత, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        ఒకవేళ (pthread_mutex_trylock(&e->తాళం_2))
            కొనసాగు; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        ఒకవేళ (vk->Get_Semaphore_Counter_విలువ(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_విలువ &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_చట్రం_deps || e->nb_sw_చట్రం_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->తాళం_2);
    }

    తిరిగి &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_కొలత];
}

శూన్య ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_లెక్క = 1,
        .pSemaphores = &e->sem,
        .p_విలువలు = &e->sem_విలువ,
    };
    pthread_mutex_తాళం(&e->తాళం_2);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->తాళం_2);
}

పూర్ణాంకం ff_vk_exec_ప్రారంభం(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    స్థిరరాశి FFVkExecPool *pool = e->మాతృ;

    Vk_Command_బఫరు_Begin_Info cmd_ప్రారంభం = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_బఫరు_BEGIN_INFO,
        .flags = VK_COMMAND_బఫరు_USAGE_ONE_సమయం_SUBMIT_బిట్టు,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_లెక్క = 1,
        .pSemaphores = &e->sem,
        .p_విలువలు = &e->sem_విలువ,
    };

    pthread_mutex_తాళం(&e->తాళం_2);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_బఫరు(e->buf, &cmd_ప్రారంభం);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->తాళం_2);
        తిరిగి AVERROR_EXTERNAL;
    }

    ఒకవేళ (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_విలువ++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .విలువ = e->sem_విలువ,
        .stage_ముసుగు = VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
    };

    pthread_mutex_unlock(&e->తాళం_2);

    తిరిగి 0;
}

స్థిర శూన్య exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    కొరకు (పూర్ణాంకం j = 0; j < e->nb_buf_deps; j++)
        av_బఫరు_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    కొరకు (పూర్ణాంకం j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    కొరకు (పూర్ణాంకం j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        ఎంపిక (od->type) {
        స్థితి VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            ఆపు;
        స్థితి VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            ఆపు;
        అప్రమేయ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    కొరకు (పూర్ణాంకం j = 0; j < e->nb_sw_చట్రం_deps; j++)
        av_చట్రం_free(&e->sw_చట్రం_deps[j]);
    e->nb_sw_చట్రం_deps = 0;

    కొరకు (పూర్ణాంకం j = 0; j < e->nb_చట్రం_deps; j++) {
        AVFrame *f = e->చట్రం_deps[j];
        ఒకవేళ (e->చట్రం_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
            AVVulkan_చట్రాలు_Context *vkfc = hwfc->hwctx;
            AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];
            vkfc->unlock_చట్రం(hwfc, vkf);
            e->చట్రం_locked[j] = 0;
        }
        e->చట్రం_update[j] = 0;
    }
    e->nb_చట్రం_deps = 0;

    e->sem_wait_cnt = 0;
    e->sem_sig_cnt = 0;
    e->sem_sig_val_dst_cnt = 0;
}

శూన్య ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .విలువ = e->sem_విలువ,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_బఫరు(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

శూన్య ff_vk_exec_కూడు_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  శూన్య *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

శూన్య ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   శూన్య *obj)
{
    శూన్య **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    కొరకు (పూర్ణాంకం i = 0; i < e->nb_refstruct_deps; i++) {
        ఒకవేళ (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            తిరిగి;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ఖాళీ;
}

శూన్య ff_vk_exec_కూడు_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

పూర్ణాంకం ff_vk_exec_కూడు_dep_sw_చట్రం(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_చట్రం_deps < FF_VK_EXEC_MAX_SW_చట్రం_DEPS);

    e->sw_చట్రం_deps[e->nb_sw_చట్రం_deps] = av_చట్రం_clone(f);
    ఒకవేళ (!e->sw_చట్రం_deps[e->nb_sw_చట్రం_deps])
        తిరిగి AVERROR(ENOMEM);

    e->nb_sw_చట్రం_deps++;

    తిరిగి 0;
}

శూన్య ff_vk_exec_కూడు_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .విలువ = val,
        .stage_ముసుగు = stage,
    };
}

శూన్య ff_vk_exec_కూడు_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .విలువ = val,
        .stage_ముసుగు = stage,
    };
}

శూన్య ff_vk_exec_కూడు_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, పూర్ణాంకం nb,
                                 VkPipelineStageFlagBits2 stage,
                                 పూర్ణాంకం wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    ఒకవేళ (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        కొరకు (పూర్ణాంకం i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_ముసుగు = stage,
            };
        }

        తిరిగి;
    }

    /* Ownership of each semaphore passes to the execution */
    కొరకు (పూర్ణాంకం i = 0; i < nb; i++) {
        ff_vk_exec_కూడు_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_కూడు_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

పూర్ణాంకం ff_vk_exec_కూడు_dep_చట్రం(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    AVVulkan_చట్రాలు_Context *vkfc = hwfc->hwctx;
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];
    పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);

    /* Don't add duplicates */
    కొరకు (పూర్ణాంకం i = 0; i < e->nb_చట్రం_deps; i++)
        ఒకవేళ (e->చట్రం_deps[i]->దత్తాంశం[0] == f->దత్తాంశం[0])
            తిరిగి 1;

    av_assert1(e->nb_చట్రం_deps < FF_VK_EXEC_MAX_చట్రం_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    ఒకవేళ (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_బఫరు_ref(f->buf[0]);
        ఒకవేళ (!e->buf_deps[e->nb_buf_deps])
            తిరిగి AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->చట్రం_deps[e->nb_చట్రం_deps] = f;

    vkfc->తాళం_చట్రం(hwfc, vkf);
    e->చట్రం_locked[e->nb_చట్రం_deps] = 1;
    e->చట్రం_update[e->nb_చట్రం_deps] = 0;
    e->nb_చట్రం_deps++;

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .విలువ = vkf->sem_విలువ[i],
            .stage_ముసుగు = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .విలువ = vkf->sem_విలువ[i] + 1,
            .stage_ముసుగు = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_విలువ[i];
        e->sem_sig_val_dst_cnt++;
    }

    తిరిగి 0;
}

శూన్య ff_vk_exec_update_చట్రం(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_జ్ఞాపకం_Barrier2 *bar, uint32_t *nb_img_bar)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < e->nb_చట్రం_deps; i++)
        ఒకవేళ (e->చట్రం_deps[i]->దత్తాంశం[0] == f->దత్తాంశం[0])
            ఆపు;
    av_assert0(i < e->nb_చట్రం_deps);

    /* Don't update duplicates */
    ఒకవేళ (nb_img_bar && !e->చట్రం_update[i])
        (*nb_img_bar)++;

    e->వరుస_family_dst[i] = bar->dst_వరుస_Family_సూచీ;
    e->access_dst[i] = bar->dst_Access_ముసుగు;
    e->layout_dst[i] = bar->newLayout;
    e->చట్రం_update[i] = 1;
}

పూర్ణాంకం ff_vk_exec_mirror_sem_విలువ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];

    /* Reject unknown frames */
    పూర్ణాంకం i;
    కొరకు (i = 0; i < e->nb_చట్రం_deps; i++)
        ఒకవేళ (e->చట్రం_deps[i]->దత్తాంశం[0] == f->దత్తాంశం[0])
            ఆపు;
    ఒకవేళ (i == e->nb_చట్రం_deps)
        తిరిగి AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_విలువ[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_బఫరు_Submit_Info cmd_buf_info = (Vk_Command_బఫరు_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_బఫరు_SUBMIT_INFO,
        .command_బఫరు = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_బఫరు_Infos = &cmd_buf_info,
        .command_బఫరు_Info_లెక్క = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_లెక్క = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_లెక్క = e->sem_sig_cnt,
    };

    ret = vk->చివర_Command_బఫరు(e->buf);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        తిరిగి AVERROR_EXTERNAL;
    }

#ఒకవేళ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->తాళం_వరుస(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#అయితే_ముగింపు
    ret = vk->వరుస_Submit2(e->వరుస, 1, &submit_info, VK_NULL_HANDLE);
#ఒకవేళ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_వరుస(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#అయితే_ముగింపు

    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        తిరిగి AVERROR_EXTERNAL;
    }

    కొరకు (పూర్ణాంకం i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    కొరకు (పూర్ణాంకం j = 0; j < e->nb_చట్రం_deps; j++) {
        ఒకవేళ (e->చట్రం_locked[j]) {
            AVFrame *f = e->చట్రం_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
            AVVulkan_చట్రాలు_Context *vkfc = hwfc->hwctx;
            AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];

            ఒకవేళ (e->చట్రం_update[j]) {
                పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);
                కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->వరుస_family[i] = e->వరుస_family_dst[j];
                }
            }
            vkfc->unlock_చట్రం(hwfc, vkf);
            e->చట్రం_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_alloc_mem(FFVulkanContext *s, Vk_జ్ఞాపకం_Requirements *req,
                    Vk_జ్ఞాపకం_Property_Flag_బిట్లు req_flags, శూన్య *alloc_extension,
                    Vk_జ్ఞాపకం_Property_Flag_బిట్లు *mem_flags, Vk_Device_జ్ఞాపకం *mem)
{
    Vk_ఫలితం ret;
    పూర్ణాంకం సూచీ = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_జ్ఞాపకం_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_జ్ఞాపకం_ALLOCATE_INFO,
        .p_తదుపరి           = alloc_extension,
    };

    alloc_info.కేటాయింపు_కొలత = req->కొలత;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    కొరకు (పూర్ణాంకం i = 0; i < s->mprops.జ్ఞాపకం_Type_లెక్క; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        ఒకవేళ (!(req->జ్ఞాపకం_Type_బిట్లు & (1 << i)))
            కొనసాగు;

        /* The memory type flags must include our properties */
        ఒకవేళ ((req_flags != UINT32_MAX) &&
            ((s->mprops.జ్ఞాపకం_Types[i].propertyFlags & req_flags) != req_flags))
            కొనసాగు;

        /* Found a suitable memory type */
        సూచీ = i;
        ఆపు;
    }

    ఒకవేళ (సూచీ < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        తిరిగి AVERROR(EINVAL);
    }

    alloc_info.జ్ఞాపకం_Type_సూచీ = సూచీ;

    ret = vk->Allocate_జ్ఞాపకం(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    ఒకవేళ (ret != VK_SUCCESS)
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (mem_flags)
        *mem_flags |= s->mprops.జ్ఞాపకం_Types[సూచీ].propertyFlags;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_జ్ఞాపకం *mem,
                       పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, VkFormat format, పూర్ణాంకం nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, శూన్య *create_pnext)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_జ్ఞాపకం_Property_Flag_బిట్లు mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_తదుపరి         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { వెడల్పు, ఎత్తు, 1 },
        .mip_స్థాయిలు     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_లెక్క_1_బిట్టు,
        .sharing_బహుళకం   = VK_SHARING_బహుళకం_EXCLUSIVE,
    };
    Vk_జ్ఞాపకం_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_ALLOCATE_INFO,
    };
    Vk_జ్ఞాపకం_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_REQUIREMENTS_2,
    };
    Vk_Image_జ్ఞాపకం_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_జ్ఞాపకం_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_జ్ఞాపకం_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_జ్ఞాపకం_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_జ్ఞాపకం_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.జ్ఞాపకం_Requirements,
                          VK_జ్ఞాపకం_PROPERTY_DEVICE_LOCAL_బిట్టు,
                          &ded_alloc, &mem_flags, mem);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    bind_info.image  = *img;
    bind_info.జ్ఞాపకం = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        వెళ్ళు fail;
    }

    తిరిగి 0;

fail:
    ff_vk_image_free(s, img, mem);
    తిరిగి err;
}

శూన్య ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_జ్ఞాపకం *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ఒకవేళ (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    ఒకవేళ (*mem) {
        vk->Free_జ్ఞాపకం(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

పూర్ణాంకం ff_vk_create_buf(FFVulkanContext *s, FFVk_బఫరు *buf, size_t కొలత,
                     శూన్య *p_తదుపరి, శూన్య *alloc_p_తదుపరి,
                     Vk_బఫరు_Usage_Flags usage, Vk_జ్ఞాపకం_Property_Flag_బిట్లు flags)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    పూర్ణాంకం use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_బఫరు_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_బఫరు_CREATE_INFO,
        .p_తదుపరి       = p_తదుపరి,
        .usage       = usage,
        .sharing_బహుళకం = VK_SHARING_బహుళకం_EXCLUSIVE,
        .కొలత        = flags & VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు ?
                       FFALIGN(కొలత, s->props.properties.limits.min_జ్ఞాపకం_Map_Alignment) :
                       కొలత,
    };

    Vk_జ్ఞాపకం_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_ALLOCATE_FLAGS_INFO,
        .flags = VK_జ్ఞాపకం_ALLOCATE_DEVICE_చిరునామా_బిట్టు,
    };
    Vk_బఫరు_జ్ఞాపకం_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_బఫరు_జ్ఞాపకం_REQUIREMENTS_INFO_2,
    };
    Vk_జ్ఞాపకం_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_ALLOCATE_INFO,
        .p_తదుపరి = alloc_p_తదుపరి,
    };
    Vk_జ్ఞాపకం_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_REQUIREMENTS,
    };
    Vk_జ్ఞాపకం_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_REQUIREMENTS_2,
        .p_తదుపరి = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           కొలత, usage, flags);

    ret = vk->Create_బఫరు(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    req_desc.బఫరు = buf->buf;

    vk->Get_బఫరు_జ్ఞాపకం_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_కేటాయింపు |
                  ded_req.requires_Dedicated_కేటాయింపు;
    ఒకవేళ (use_ded_mem) {
        ded_alloc.బఫరు = buf->buf;
        ded_alloc.p_తదుపరి = alloc_p_తదుపరి;
        alloc_p_తదుపరి = &ded_alloc;
    }

    ఒకవేళ (usage & VK_బఫరు_USAGE_SHADER_DEVICE_చిరునామా_బిట్టు) {
        alloc_flags.p_తదుపరి = alloc_p_తదుపరి;
        alloc_p_తదుపరి = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.జ్ఞాపకం_Requirements, flags, alloc_p_తదుపరి,
                          &buf->flags, &buf->mem);
    ఒకవేళ (err)
        తిరిగి err;

    ret = vk->Bind_బఫరు_జ్ఞాపకం(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    ఒకవేళ (usage & VK_బఫరు_USAGE_SHADER_DEVICE_చిరునామా_బిట్టు) {
        Vk_బఫరు_Device_చిరునామా_Info చిరునామా_info = {
            .sType = VK_STRUCTURE_TYPE_బఫరు_DEVICE_చిరునామా_INFO,
            .బఫరు = buf->buf,
        };
        buf->చిరునామా = vk->Get_బఫరు_Device_చిరునామా(s->hwctx->act_dev, &చిరునామా_info);
    }

    buf->కొలత = కొలత;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_map_buffers(FFVulkanContext *s, FFVk_బఫరు **buf, uint8_t *mem[],
                      పూర్ణాంకం nb_buffers, పూర్ణాంకం invalidate)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_జ్ఞాపకం_Range inval_list[64];
    పూర్ణాంకం inval_లెక్క = 0;

    కొరకు (పూర్ణాంకం i = 0; i < nb_buffers; i++) {
        శూన్య *dst;
        ret = vk->Map_జ్ఞాపకం(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_సంపూర్ణ_కొలత, 0, &dst);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        ఒకవేళ (mem)
            mem[i] = dst;
    }

    ఒకవేళ (!invalidate)
        తిరిగి 0;

    కొరకు (పూర్ణాంకం i = 0; i < nb_buffers; i++) {
        స్థిరరాశి Vk_Mapped_జ్ఞాపకం_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_జ్ఞాపకం_RANGE,
            .జ్ఞాపకం = buf[i]->mem,
            .కొలత   = VK_సంపూర్ణ_కొలత,
        };
        ఒకవేళ (buf[i]->flags & VK_జ్ఞాపకం_PROPERTY_HOST_COHERENT_బిట్టు)
            కొనసాగు;
        inval_list[inval_లెక్క++] = ival_buf;
    }

    ఒకవేళ (inval_లెక్క) {
        ret = vk->Invalidate_Mapped_జ్ఞాపకం_Ranges(s->hwctx->act_dev, inval_లెక్క,
                                               inval_list);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_flush_బఫరు(FFVulkanContext *s, FFVk_బఫరు *buf,
                       Vk_Device_కొలత స్థానభ్రంశం, Vk_Device_కొలత mem_కొలత,
                       పూర్ణాంకం flush)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ఒకవేళ (buf->flags & VK_జ్ఞాపకం_PROPERTY_HOST_COHERENT_బిట్టు)
        తిరిగి 0;

    స్థిరరాశి Vk_Mapped_జ్ఞాపకం_Range flush_దత్తాంశం = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_జ్ఞాపకం_RANGE,
        .జ్ఞాపకం = buf->mem,
        .స్థానభ్రంశం = స్థానభ్రంశం,
        .కొలత   = mem_కొలత,
    };

    ఒకవేళ (flush)
        ret = vk->Flush_Mapped_జ్ఞాపకం_Ranges(s->hwctx->act_dev, 1, &flush_దత్తాంశం);
    లేకపోతే
        ret = vk->Invalidate_Mapped_జ్ఞాపకం_Ranges(s->hwctx->act_dev, 1, &flush_దత్తాంశం);

    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_బఫరు **buf, పూర్ణాంకం nb_buffers,
                        పూర్ణాంకం flush)
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_జ్ఞాపకం_Range flush_list[64];
    పూర్ణాంకం flush_లెక్క = 0;

    ఒకవేళ (flush) {
        కొరకు (పూర్ణాంకం i = 0; i < nb_buffers; i++) {
            స్థిరరాశి Vk_Mapped_జ్ఞాపకం_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_జ్ఞాపకం_RANGE,
                .జ్ఞాపకం = buf[i]->mem,
                .కొలత   = VK_సంపూర్ణ_కొలత,
            };

            av_assert0(!buf[i]->host_ref);
            ఒకవేళ (buf[i]->flags & VK_జ్ఞాపకం_PROPERTY_HOST_COHERENT_బిట్టు)
                కొనసాగు;
            flush_list[flush_లెక్క++] = flush_buf;
        }
    }

    ఒకవేళ (flush_లెక్క) {
        ret = vk->Flush_Mapped_జ్ఞాపకం_Ranges(s->hwctx->act_dev, flush_లెక్క,
                                          flush_list);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    కొరకు (పూర్ణాంకం i = 0; i < nb_buffers; i++) {
        vk->Unmap_జ్ఞాపకం(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ఖాళీ;
    }

    తిరిగి err;
}

శూన్య ff_vk_free_buf(FFVulkanContext *s, FFVk_బఫరు *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ఒకవేళ (!buf || !s->hwctx)
        తిరిగి;

    ఒకవేళ (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_బఫరు(s, buf, 0);
    ఒకవేళ (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_బఫరు(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    ఒకవేళ (buf->mem != VK_NULL_HANDLE)
        vk->Free_జ్ఞాపకం(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    ఒకవేళ (buf->host_ref)
        av_బఫరు_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ఖాళీ;
}

స్థిర శూన్య pooled_buf_free(AVRefStructOpaque opaque, శూన్య *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

పూర్ణాంకం ff_vk_get_pooled_బఫరు(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_బఫరు **buf, Vk_బఫరు_Usage_Flags usage,
                            శూన్య *create_p_తదుపరి, size_t కొలత,
                            Vk_జ్ఞాపకం_Property_Flag_బిట్లు mem_props)
{
    పూర్ణాంకం err;
    FFVk_బఫరు *దత్తాంశం;

    ఒకవేళ (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(పరిమాణం(FFVk_బఫరు), 0, ctx,
                                                ఖాళీ, ఖాళీ, pooled_buf_free,
                                                ఖాళీ);
        ఒకవేళ (!(*buf_pool))
            తిరిగి AVERROR(ENOMEM);
    }

    *buf = దత్తాంశం = av_refstruct_pool_get(*buf_pool);
    ఒకవేళ (!దత్తాంశం)
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (దత్తాంశం->కొలత >= కొలత)
        తిరిగి 0;

    ff_vk_free_buf(ctx, దత్తాంశం);
    memset(దత్తాంశం, 0, పరిమాణం(*దత్తాంశం));

    err = ff_vk_create_buf(ctx, దత్తాంశం, కొలత,
                           create_p_తదుపరి, ఖాళీ, usage,
                           mem_props);
    ఒకవేళ (err < 0) {
        av_refstruct_unref(buf);
        తిరిగి err;
    }

    ఒకవేళ (mem_props & VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు) {
        err = ff_vk_map_బఫరు(ctx, దత్తాంశం, &దత్తాంశం->mapped_mem, 0);
        ఒకవేళ (err < 0) {
            av_refstruct_unref(buf);
            తిరిగి err;
        }
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం create_mapped_బఫరు(FFVulkanContext *s,
                                FFVk_బఫరు *vkb, Vk_బఫరు_Usage_Flags usage,
                                size_t కొలత,
                                Vk_External_జ్ఞాపకం_బఫరు_Create_Info *create_desc,
                                Vk_Import_జ్ఞాపకం_Host_సూచిక_Info_EXT *import_desc,
                                Vk_జ్ఞాపకం_Host_సూచిక_Properties_EXT props)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_బఫరు_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_బఫరు_CREATE_INFO,
        .p_తదుపరి       = create_desc,
        .usage       = usage,
        .sharing_బహుళకం = VK_SHARING_బహుళకం_EXCLUSIVE,
        .కొలత        = కొలత,
    };
    Vk_జ్ఞాపకం_Requirements req = {
        .కొలత           = కొలత,
        .alignment      = s->hprops.min_Imported_Host_సూచిక_Alignment,
        .జ్ఞాపకం_Type_బిట్లు = props.జ్ఞాపకం_Type_బిట్లు,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు,
                          import_desc, &vkb->flags, &vkb->mem);
    ఒకవేళ (err < 0)
        తిరిగి err;

    ret = vk->Create_బఫరు(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    ఒకవేళ (ret != VK_SUCCESS) {
        vk->Free_జ్ఞాపకం(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        తిరిగి AVERROR_EXTERNAL;
    }

    ret = vk->Bind_బఫరు_జ్ఞాపకం(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    ఒకవేళ (ret != VK_SUCCESS) {
        vk->Free_జ్ఞాపకం(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_బఫరు(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర శూన్య host_map_free(AVRefStructOpaque opaque, శూన్య *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

పూర్ణాంకం ff_vk_host_map_బఫరు(FFVulkanContext *s, FFVk_బఫరు **dst,
                          uint8_t *src_దత్తాంశం, Vk_Device_కొలత కొలత,
                          స్థిరరాశి AVBufferRef *src_buf,
                          Vk_బఫరు_Usage_Flags usage)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_జ్ఞాపకం_బఫరు_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_జ్ఞాపకం_బఫరు_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_HOST_కేటాయింపు_బిట్టు_EXT,
    };
    Vk_జ్ఞాపకం_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_ALLOCATE_FLAGS_INFO,
        .flags = VK_జ్ఞాపకం_ALLOCATE_DEVICE_చిరునామా_బిట్టు,
    };
    Vk_Import_జ్ఞాపకం_Host_సూచిక_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_జ్ఞాపకం_HOST_సూచిక_INFO_EXT,
        .handleType = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_HOST_కేటాయింపు_బిట్టు_EXT,
        .p_తదుపరి = usage & VK_బఫరు_USAGE_SHADER_DEVICE_చిరునామా_బిట్టు ? &alloc_flags : ఖాళీ,
    };
    Vk_జ్ఞాపకం_Host_సూచిక_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_బఫరు *vkb;
    size_t offs;
    size_t బఫరు_కొలత;

    *dst = ఖాళీ;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_దత్తాంశం % s->hprops.min_Imported_Host_సూచిక_Alignment;
    import_desc.p_Host_సూచిక = src_దత్తాంశం - offs;

    props = (Vk_జ్ఞాపకం_Host_సూచిక_Properties_EXT) {
        VK_STRUCTURE_TYPE_జ్ఞాపకం_HOST_సూచిక_PROPERTIES_EXT,
    };
    ret = vk->Get_జ్ఞాపకం_Host_సూచిక_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_సూచిక,
                                                &props);
    ఒకవేళ (!(ret == VK_SUCCESS && props.జ్ఞాపకం_Type_బిట్లు))
        తిరిగి AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_బఫరు_ref(src_buf);
    ఒకవేళ (!ref)
        తిరిగి AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    స్థిరరాశి Vk_Device_కొలత src_avail = src_buf->కొలత - (src_దత్తాంశం - src_buf->దత్తాంశం);
    బఫరు_కొలత = offs + FFMIN(కొలత, src_avail);
    బఫరు_కొలత = FFALIGN(బఫరు_కొలత, s->props.properties.limits.min_జ్ఞాపకం_Map_Alignment);
    బఫరు_కొలత = FFALIGN(బఫరు_కొలత, s->hprops.min_Imported_Host_సూచిక_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(పరిమాణం(*vkb), 0, s, host_map_free);
    ఒకవేళ (!vkb) {
        av_బఫరు_unref(&ref);
        తిరిగి AVERROR(ENOMEM);
    }

    err = create_mapped_బఫరు(s, vkb, usage,
                               బఫరు_కొలత, &create_desc, &import_desc,
                               props);
    ఒకవేళ (err < 0) {
        av_బఫరు_unref(&ref);
        av_refstruct_unref(&vkb);
        తిరిగి err;
    }

    ఒకవేళ (usage & VK_బఫరు_USAGE_SHADER_DEVICE_చిరునామా_బిట్టు) {
        Vk_బఫరు_Device_చిరునామా_Info చిరునామా_info = {
            .sType = VK_STRUCTURE_TYPE_బఫరు_DEVICE_చిరునామా_INFO,
            .బఫరు = vkb->buf,
        };
        vkb->చిరునామా = vk->Get_బఫరు_Device_చిరునామా(s->hwctx->act_dev, &చిరునామా_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_స్థానభ్రంశం = offs;
    vkb->చిరునామా       += offs;
    vkb->mapped_mem     = src_దత్తాంశం;
    vkb->కొలత           = బఫరు_కొలత - offs;

    *dst = vkb;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_shader_కూడు_నెట్టు_const(FFVulkanShader *shd, పూర్ణాంకం స్థానభ్రంశం, పూర్ణాంకం కొలత,
                                Vk_Shader_Stage_Flag_బిట్లు stage)
{
    Vk_నెట్టు_Constant_Range *pc = &shd->నెట్టు_consts[shd->నెట్టు_consts_అంకె++];
    av_assert1(shd->నెట్టు_consts_అంకె < FF_VK_MAX_నెట్టు_CONSTS);
    pc->stageFlags = stage;
    pc->స్థానభ్రంశం = స్థానభ్రంశం;
    pc->కొలత = కొలత;
    తిరిగి 0;
}

పూర్ణాంకం ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       పూర్ణాంకం unnorm_coords, VkFilter filt)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_బహుళకం = (unnorm_coords || filt == VK_FILTER_సమీప) ?
                      VK_SAMPLER_MIPMAP_బహుళకం_సమీప :
                      VK_SAMPLER_MIPMAP_బహుళకం_రేఖీయ,
        .చిరునామా_బహుళకం_U = VK_SAMPLER_చిరునామా_బహుళకం_CLAMP_గమ్యం_అంచు,
        .చిరునామా_బహుళకం_V = sampler_info.చిరునామా_బహుళకం_U,
        .చిరునామా_బహుళకం_W = sampler_info.చిరునామా_బహుళకం_U,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, పూర్ణాంకం p)
{
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);
    పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);

    స్థిర స్థిరరాశి VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_బిట్టు,
                                                       VK_IMAGE_ASPECT_PLANE_1_బిట్టు,
                                                       VK_IMAGE_ASPECT_PLANE_2_బిట్టు, };

    ఒకవేళ (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        తిరిగి VK_IMAGE_ASPECT_COLOR_బిట్టు;

    తిరిగి plane_aspect[p];
}

పూర్ణాంకం ff_vk_mt_is_np_rgb(గణన AVPixelFormat pix_fmt)
{
    ఒకవేళ (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        తిరిగి 1;
    తిరిగి 0;
}

శూన్య ff_vk_సమితి_perm(గణన AVPixelFormat pix_fmt, పూర్ణాంకం lut[4], పూర్ణాంకం inv)
{
    ఎంపిక (pix_fmt) {
    స్థితి AV_PIX_FMT_GBRP:
    స్థితి AV_PIX_FMT_GBRAP:
    స్థితి AV_PIX_FMT_GBRAP10:
    స్థితి AV_PIX_FMT_GBRAP12:
    స్థితి AV_PIX_FMT_GBRAP14:
    స్థితి AV_PIX_FMT_GBRAP16:
    స్థితి AV_PIX_FMT_GBRAPF16:
    స్థితి AV_PIX_FMT_GBRP10:
    స్థితి AV_PIX_FMT_GBRP12:
    స్థితి AV_PIX_FMT_GBRP14:
    స్థితి AV_PIX_FMT_GBRP16:
    స్థితి AV_PIX_FMT_GBRPF16:
    స్థితి AV_PIX_FMT_GBRPF32:
    స్థితి AV_PIX_FMT_GBRAP32:
    స్థితి AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        ఆపు;
    స్థితి AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        ఆపు;
    స్థితి AV_PIX_FMT_BGRA:
    స్థితి AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        ఆపు;
    అప్రమేయ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        ఆపు;
    }

    ఒకవేళ (inv) {
        పూర్ణాంకం lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        కొరకు (పూర్ణాంకం i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    తిరిగి;
}

స్థిరరాశి అక్షరం *ff_vk_shader_rep_fmt(గణన AVPixelFormat pix_fmt,
                                 గణన FFVkShaderRepFormat rep_fmt)
{
    ఎంపిక (pix_fmt) {
    స్థితి AV_PIX_FMT_RGBA:
    స్థితి AV_PIX_FMT_BGRA:
    స్థితి AV_PIX_FMT_RGB24:
    స్థితి AV_PIX_FMT_BGR24:
    స్థితి AV_PIX_FMT_BGR0:
    స్థితి AV_PIX_FMT_RGB0:
    స్థితి AV_PIX_FMT_RGB565:
    స్థితి AV_PIX_FMT_BGR565:
    స్థితి AV_PIX_FMT_UYVA:
    స్థితి AV_PIX_FMT_YUYV422:
    స్థితి AV_PIX_FMT_UYVY422: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_X2RGB10:
    స్థితి AV_PIX_FMT_X2BGR10:
    స్థితి AV_PIX_FMT_Y210:
    స్థితి AV_PIX_FMT_XV30: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ఖాళీ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_RGB48:
    స్థితి AV_PIX_FMT_RGBA64:
    స్థితి AV_PIX_FMT_Y212:
    స్థితి AV_PIX_FMT_Y216:
    స్థితి AV_PIX_FMT_XV36:
    స్థితి AV_PIX_FMT_XV48: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_RGBAF16: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_RGBF32:
    స్థితి AV_PIX_FMT_RGBAF32: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_RGB96:
    స్థితి AV_PIX_FMT_RGBA128: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ఖాళీ,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        తిరిగి rep_tab[rep_fmt];
    }
    స్థితి AV_PIX_FMT_GBRP:
    స్థితి AV_PIX_FMT_GRAY8:
    స్థితి AV_PIX_FMT_GBRAP:
    స్థితి AV_PIX_FMT_YUV420P:
    స్థితి AV_PIX_FMT_YUV422P:
    స్థితి AV_PIX_FMT_YUV444P:
    స్థితి AV_PIX_FMT_YUVA420P:
    స్థితి AV_PIX_FMT_YUVA422P:
    స్థితి AV_PIX_FMT_YUVA444P: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_GRAY10:
    స్థితి AV_PIX_FMT_GRAY12:
    స్థితి AV_PIX_FMT_GRAY14:
    స్థితి AV_PIX_FMT_GRAY16:
    స్థితి AV_PIX_FMT_GBRAP10:
    స్థితి AV_PIX_FMT_GBRAP12:
    స్థితి AV_PIX_FMT_GBRAP14:
    స్థితి AV_PIX_FMT_GBRAP16:
    స్థితి AV_PIX_FMT_GBRAPF16:
    స్థితి AV_PIX_FMT_GBRP10:
    స్థితి AV_PIX_FMT_GBRP12:
    స్థితి AV_PIX_FMT_GBRP14:
    స్థితి AV_PIX_FMT_GBRP16:
    స్థితి AV_PIX_FMT_GBRPF16:
    స్థితి AV_PIX_FMT_XYZP12:
    స్థితి AV_PIX_FMT_YUV420P10:
    స్థితి AV_PIX_FMT_YUV420P12:
    స్థితి AV_PIX_FMT_YUV420P16:
    స్థితి AV_PIX_FMT_YUV422P10:
    స్థితి AV_PIX_FMT_YUV422P12:
    స్థితి AV_PIX_FMT_YUV422P16:
    స్థితి AV_PIX_FMT_YUV444P10:
    స్థితి AV_PIX_FMT_YUV444P12:
    స్థితి AV_PIX_FMT_YUV444P16:
    స్థితి AV_PIX_FMT_YUVA420P10:
    స్థితి AV_PIX_FMT_YUVA420P16:
    స్థితి AV_PIX_FMT_YUVA422P10:
    స్థితి AV_PIX_FMT_YUVA422P12:
    స్థితి AV_PIX_FMT_YUVA422P16:
    స్థితి AV_PIX_FMT_YUVA444P10:
    స్థితి AV_PIX_FMT_YUVA444P12:
    స్థితి AV_PIX_FMT_YUVA444P16:
    స్థితి AV_PIX_FMT_BAYER_RGGB16: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_GRAY32:
    స్థితి AV_PIX_FMT_GRAYF32:
    స్థితి AV_PIX_FMT_GBRPF32:
    స్థితి AV_PIX_FMT_GBRAPF32: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_GBRAP32: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ఖాళీ,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_NV12:
    స్థితి AV_PIX_FMT_NV16:
    స్థితి AV_PIX_FMT_NV24: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_P010:
    స్థితి AV_PIX_FMT_P210:
    స్థితి AV_PIX_FMT_P410: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ఖాళీ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    స్థితి AV_PIX_FMT_P012:
    స్థితి AV_PIX_FMT_P016:
    స్థితి AV_PIX_FMT_P212:
    స్థితి AV_PIX_FMT_P216:
    స్థితి AV_PIX_FMT_P412:
    స్థితి AV_PIX_FMT_P416: {
        స్థిరరాశి అక్షరం *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        తిరిగి rep_tab[rep_fmt];
    };
    అప్రమేయ:
        తిరిగి "rgba32f";
    }
}

స్థిర శూన్య reset_imageviews(AVRefStructOpaque వాడని, శూన్య *obj)
{
    FFVkImageViews *iv = obj;

    కొరకు (పూర్ణాంకం i = 0; i < iv->nb_views; i++) {
        ఒకవేళ (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, పరిమాణం(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, పూర్ణాంకం nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_అంకె_దత్తాంశం_సూచికలు);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    ఒకవేళ (!iv)
        తిరిగి ఖాళీ;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    తిరిగి iv;
}

VkFormat ff_vk_map_fmt_గమ్యం_rep(VkFormat fmt, గణన FFVkShaderRepFormat rep_fmt)
{
#నిర్వచించు REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#నిర్వచించు REPS_FMT_PACK(fmt, అంకె) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## అంకె, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## అంకె, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## అంకె, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## అంకె,

    స్థిరరాశి VkFormat fmts_map[][4] = {
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
#నిర్వచనం_రద్దు REPS_FMT_PACK
#నిర్వచనం_రద్దు REPS_FMT

    ఒకవేళ (fmt == VK_FORMAT_UNDEFINED)
        తిరిగి VK_FORMAT_UNDEFINED;

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        ఒకవేళ (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            తిరిగి fmts_map[i][rep_fmt];
    }

    తిరిగి VK_FORMAT_UNDEFINED;
}

పూర్ణాంకం ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, పూర్ణాంకం plane, గణన FFVkShaderRepFormat rep_fmt)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    AVVulkan_చట్రాలు_Context *vkfc = hwfc->hwctx;
    స్థిరరాశి VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_తదుపరి      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_గమ్యం_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_తటస్థం_map,
        .subresourceRange = {
            .aspect_ముసుగు = ff_vk_aspect_flag(f, plane),
            .level_లెక్క = 1,
            .layer_లెక్క = 1,
        },
    };
    ఒకవేళ (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        తిరిగి AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_ముసుగు;

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_అంకె_దత్తాంశం_సూచికలు],
                                AVFrame *f,
                                స్థిరరాశి VkFormat fmts[AV_అంకె_దత్తాంశం_సూచికలు])
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    AVVulkan_చట్రాలు_Context *vkfc = hwfc->hwctx;
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)f->దత్తాంశం[0];
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);
    స్థిరరాశి పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };

    కొరకు (పూర్ణాంకం i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_తదుపరి      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_తటస్థం_map,
            .subresourceRange = {
                .aspect_ముసుగు = ff_vk_aspect_flag(f, i),
                .level_లెక్క = 1,
                .layer_లెక్క = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    కొరకు (పూర్ణాంకం i = 0; i < nb_planes; i++)
        ff_vk_exec_కూడు_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    జ్ఞాపకం_నకలు(views, tmp_views, nb_planes*పరిమాణం(*views));

    తిరిగి 0;

fail:
    కొరకు (పూర్ణాంకం i = 0; i < nb_planes; i++)
        ఒకవేళ (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    తిరిగి err;
}

పూర్ణాంకం ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_అంకె_దత్తాంశం_సూచికలు],
                            AVFrame *f, గణన FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    స్థిరరాశి VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    స్థిరరాశి పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    VkFormat fmts[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };

    కొరకు (పూర్ణాంకం i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_గమ్యం_rep(rep_fmts[i], rep_fmt);
        ఒకవేళ (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            తిరిగి AVERROR(EINVAL);
        }
    }

    తిరిగి ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

శూన్య ff_vk_చట్రం_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_జ్ఞాపకం_Barrier2 *bar, పూర్ణాంకం *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    పూర్ణాంకం దొరికింది = -1;
    AVVk_చట్రం *vkf = (AVVk_చట్రం *)pic->దత్తాంశం[0];
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(vkf);
    కొరకు (పూర్ణాంకం i = 0; i < e->nb_చట్రం_deps; i++)
        ఒకవేళ (e->చట్రం_deps[i]->దత్తాంశం[0] == pic->దత్తాంశం[0]) {
            ఒకవేళ (e->చట్రం_update[i])
                దొరికింది = i;
            ఆపు;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_జ్ఞాపకం_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_జ్ఞాపకం_BARRIER_2,
            .p_తదుపరి = ఖాళీ,
            .src_Stage_ముసుగు = src_stage,
            .dst_Stage_ముసుగు = dst_stage,
            .src_Access_ముసుగు = దొరికింది >= 0 ? e->access_dst[దొరికింది] : VK_ACCESS_2_NONE,
            .dst_Access_ముసుగు = new_access,
            .oldLayout = దొరికింది >= 0 ? e->layout_dst[దొరికింది] : vkf->layout[0],
            .newLayout = new_layout,
            .src_వరుస_Family_సూచీ = దొరికింది >= 0 ? e->వరుస_family_dst[దొరికింది] : vkf->వరుస_family[0],
            .dst_వరుస_Family_సూచీ = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_ముసుగు = VK_IMAGE_ASPECT_COLOR_బిట్టు,
                .layer_లెక్క = 1,
                .level_లెక్క = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_చట్రం(s, e, pic, &bar[*nb_bar - nb_images], ఖాళీ);
}

పూర్ణాంకం ff_vk_shader_ఎక్కించు(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_కొలత[3], uint32_t required_subgroup_కొలత)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    జ్ఞాపకం_నకలు(shd->lg_కొలత, wg_కొలత, 3*పరిమాణం(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_కొలత_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_కొలత_CREATE_INFO,
        .required_Subgroup_కొలత = required_subgroup_కొలత,
    };

    ఎంపిక (shd->stage) {
    స్థితి VK_SHADER_STAGE_ANY_తగిలింది_బిట్టు_KHR:
    స్థితి VK_SHADER_STAGE_CALLABLE_బిట్టు_KHR:
    స్థితి VK_SHADER_STAGE_CLOSEST_తగిలింది_బిట్టు_KHR:
    స్థితి VK_SHADER_STAGE_INTERSECTION_బిట్టు_KHR:
    స్థితి VK_SHADER_STAGE_తప్పిపోవు_బిట్టు_KHR:
    స్థితి VK_SHADER_STAGE_RAYGEN_బిట్టు_KHR:
        shd->bind_బిందువు = VK_PIPELINE_BIND_బిందువు_RAY_TRACING_KHR;
        ఆపు;
    స్థితి VK_SHADER_STAGE_COMPUTE_బిట్టు:
        shd->bind_బిందువు = VK_PIPELINE_BIND_బిందువు_COMPUTE;
        ఆపు;
    అప్రమేయ:
        shd->bind_బిందువు = VK_PIPELINE_BIND_బిందువు_GRAPHICS;
        ఆపు;
    };

    తిరిగి 0;
}

స్థిర పూర్ణాంకం init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_సమితి_Layouts            = shd->desc_layout,
        .సమితి_Layout_లెక్క         = shd->nb_descriptor_sets,
        .నెట్టు_Constant_Range_లెక్క = shd->నెట్టు_consts_అంకె,
        .p_నెట్టు_Constant_Ranges    = shd->నెట్టు_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                స్థిరరాశి uint8_t *spirv, size_t spirv_len)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_తదుపరి    = ఖాళీ,
        .flags    = 0x0,
        .p_సంకేతం    = (శూన్య *)spirv,
        .సంకేతం_కొలత = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, స్థిరరాశి అక్షరం *entrypoint)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_తదుపరి = shd->subgroup_info.required_Subgroup_కొలత ?
                     &shd->subgroup_info : ఖాళీ,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_కొలత ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_నిండిన_SUBGROUPS_బిట్టు : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ఫలితం ret;
    FFVulkanFunctions *vk = &s->vkfn;

    పూర్ణాంకం has_singular = 0;
    పూర్ణాంకం max_descriptors = 0;
    కొరకు (పూర్ణాంకం i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_సమితి[i].nb_bindings);
        ఒకవేళ (shd->desc_సమితి[i].singular)
            has_singular = 1;
    }
    shd->use_నెట్టు = (s->extensions & FF_VK_EXT_నెట్టు_DESCRIPTOR) &&
                    (max_descriptors <= s->నెట్టు_desc_props.max_నెట్టు_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    కొరకు (పూర్ణాంకం i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_సమితి *సమితి = &shd->desc_సమితి[i];
        Vk_Descriptor_సమితి_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_సమితి_LAYOUT_CREATE_INFO,
            .binding_లెక్క = సమితి->nb_bindings,
            .pBindings = సమితి->binding,
            .flags = (shd->use_నెట్టు) ?
                     VK_DESCRIPTOR_సమితి_LAYOUT_CREATE_నెట్టు_DESCRIPTOR_బిట్టు_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_సమితి_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      స్థిరరాశి అక్షరం *spirv, size_t spirv_len,
                      స్థిరరాశి అక్షరం *entrypoint)
{
    పూర్ణాంకం err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_నమోదు spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ఆదానం_కొలత = spirv_len;

    ఒకవేళ (shd->precompiled) {
        ఒకవేళ (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_నమోదు_లెక్క = 0,
                .p_దత్తాంశం = shd->lg_కొలత,
                .దత్తాంశం_కొలత_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_నమోదు *spe = (శూన్య *)shd->specialization_info->pMapEntries;
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_నమోదు_లెక్క++] = (Vk_Specialization_Map_నమోదు) {
                .constantID = 253 + i,
                .స్థానభ్రంశం = shd->specialization_info->దత్తాంశం_కొలత_2 + i*పరిమాణం(uint32_t),
                .కొలత = పరిమాణం(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_దత్తాంశం;
        జ్ఞాపకం_నకలు(&spd[shd->specialization_info->దత్తాంశం_కొలత_2],
               shd->lg_కొలత, 3*పరిమాణం(uint32_t));
        shd->specialization_info->దత్తాంశం_కొలత_2 += 3*పరిమాణం(uint32_t);

#ఒకవేళ CONFIG_SHADER_COMPRESSION
        uint8_t *బహిర్గతం;
        size_t బహిర్గతం_len;
        పూర్ణాంకం ret = ff_zlib_expand(s, &బహిర్గతం, &బహిర్గతం_len, spirv, spirv_len);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        spirv = బహిర్గతం;
        spirv_len = బహిర్గతం_len;
#అయితే_ముగింపు
    }

    err = init_descriptors(s, shd);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    err = init_pipeline_layout(s, shd);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    ఎంపిక (shd->bind_బిందువు) {
    స్థితి VK_PIPELINE_BIND_బిందువు_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        ఆపు;
    అప్రమేయ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_బిందువు);
        err = AVERROR(EINVAL);
        వెళ్ళు చివర;
        ఆపు;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    ఒకవేళ (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    లేకపోతే
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    ఒకవేళ (ఆదానం_కొలత != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ఆదానం_కొలత);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

చివర:
    ఒకవేళ (shd->precompiled) {
        shd->specialization_info->map_నమోదు_లెక్క -= 3;
        shd->specialization_info->దత్తాంశం_కొలత_2 -= 3*పరిమాణం(uint32_t);
    }
#ఒకవేళ CONFIG_SHADER_COMPRESSION
    ఒకవేళ (shd->precompiled)
        av_free((శూన్య *)spirv);
#అయితే_ముగింపు
    తిరిగి err;
}

శూన్య ff_vk_shader_కూడు_descriptor_సమితి(FFVulkanContext *s, FFVulkanShader *shd,
                                     స్థిరరాశి FFVulkan_Descriptor_సమితి_Binding *desc, పూర్ణాంకం nb,
                                     పూర్ణాంకం singular)
{
    FFVulkan_Descriptor_సమితి *సమితి = &shd->desc_సమితి[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    కొరకు (పూర్ణాంకం i = 0; i < nb; i++) {
        సమితి->binding[i].binding            = i;
        సమితి->binding[i].descriptorType     = desc[i].type;
        సమితి->binding[i].descriptor_లెక్క    = FFMAX(desc[i].elems, 1);
        సమితి->binding[i].stageFlags         = desc[i].stages;
        సమితి->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    కొరకు (పూర్ణాంకం i = 0; i < nb; i++) {
        పూర్ణాంకం j;
        కొరకు (j = 0; j < shd->nb_desc_pool_కొలత; j++)
            ఒకవేళ (shd->desc_pool_కొలత[j].type == desc[i].type)
                ఆపు;
        ఒకవేళ (j >= shd->nb_desc_pool_కొలత) {
            shd->nb_desc_pool_కొలత++;
            av_assert1(shd->nb_desc_pool_కొలత < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_కొలత[j].type             = desc[i].type;
        shd->desc_pool_కొలత[j].descriptor_లెక్క += FFMAX(desc[i].elems, 1);
    }

    సమితి->singular = singular;
    సమితి->nb_bindings = nb;
}

పూర్ణాంకం ff_vk_shader_రిజిస్టరు_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    ఒకవేళ (!shd->nb_descriptor_sets)
        తిరిగి 0;

    FFVulkan_Shader_దత్తాంశం *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    ఒకవేళ (!shd->use_నెట్టు) {
        Vk_ఫలితం ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_సమితి_Layout *tmp_layouts;
        Vk_Descriptor_సమితి_Allocate_Info సమితి_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        కొరకు (పూర్ణాంకం i = 0; i < shd->nb_desc_pool_కొలత; i++)
            shd->desc_pool_కొలత[i].descriptor_లెక్క *= pool->pool_కొలత;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_కొలత,
            .pool_కొలత_లెక్క = shd->nb_desc_pool_కొలత,
            .maxSets = sd->nb_descriptor_sets*pool->pool_కొలత,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, పరిమాణం(*tmp_layouts));
        ఒకవేళ (!tmp_layouts)
            తిరిగి AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        కొరకు (పూర్ణాంకం i = 0; i < pool->pool_కొలత; i++)
            కొరకు (పూర్ణాంకం j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        సమితి_alloc_info = (Vk_Descriptor_సమితి_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_సమితి_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_సమితి_Layouts        = tmp_layouts,
            .descriptor_సమితి_లెక్క = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        పరిమాణం(*tmp_layouts));
        ఒకవేళ (!sd->desc_sets) {
            av_free(tmp_layouts);
            తిరిగి AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &సమితి_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            తిరిగి AVERROR_EXTERNAL;
        }
    }

    తిరిగి 0;
}

స్థిర అంతఃవరుస స్థిరరాశి FFVulkan_Shader_దత్తాంశం *get_shd_దత్తాంశం(FFVkExecContext *e,
                                                     స్థిరరాశి FFVulkanShader *shd)
{
    కొరకు (పూర్ణాంకం i = 0; i < e->మాతృ->nb_reg_shd; i++)
        ఒకవేళ (e->మాతృ->reg_shd[i].shd == shd)
            తిరిగి &e->మాతృ->reg_shd[i];
    తిరిగి ఖాళీ;
}

స్థిర అంతఃవరుస శూన్య update_సమితి_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, పూర్ణాంకం సమితి,
                                         Vk_Write_Descriptor_సమితి *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_సమితి *desc_సమితి = &shd->desc_సమితి[సమితి];
    స్థిరరాశి FFVulkan_Shader_దత్తాంశం *sd = get_shd_దత్తాంశం(e, shd);

    ఒకవేళ (desc_సమితి->singular) {
        కొరకు (పూర్ణాంకం i = 0; i < e->మాతృ->pool_కొలత; i++) {
            write_info->dst_సమితి = sd->desc_sets[i*sd->nb_descriptor_sets + సమితి];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ఖాళీ);
        }
    } లేకపోతే {
        ఒకవేళ (shd->use_నెట్టు) {
            vk->Cmd_నెట్టు_Descriptor_సమితి_KHR(e->buf,
                                        shd->bind_బిందువు,
                                        shd->pipeline_layout,
                                        సమితి, 1,
                                        write_info);
        } లేకపోతే {
            write_info->dst_సమితి = sd->desc_sets[e->idx*sd->nb_descriptor_sets + సమితి];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ఖాళీ);
        }
    }
}

పూర్ణాంకం ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, పూర్ణాంకం సమితి, పూర్ణాంకం bind, పూర్ణాంకం offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_సమితి *desc_సమితి = &shd->desc_సమితి[సమితి];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_సమితి desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_సమితి,
        .dstBinding = bind,
        .descriptor_లెక్క = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_సమితి->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_సమితి_pool_write(s, e, shd, సమితి, &desc_pool_write_info);

    తిరిగి 0;
}

శూన్య ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, పూర్ణాంకం సమితి, పూర్ణాంకం binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_చట్రాలు_ctx->దత్తాంశం;
    స్థిరరాశి పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);

    కొరకు (పూర్ణాంకం i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, సమితి, binding, i,
                                views[i], layout, sampler);
}

పూర్ణాంకం ff_vk_shader_update_desc_బఫరు(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    పూర్ణాంకం సమితి, పూర్ణాంకం bind, పూర్ణాంకం elem,
                                    FFVk_బఫరు *buf, Vk_Device_కొలత స్థానభ్రంశం, Vk_Device_కొలత len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_సమితి *desc_సమితి = &shd->desc_సమితి[సమితి];

    Vk_Descriptor_బఫరు_Info desc_pool_write_info_buf = {
        .బఫరు = buf->buf,
        .స్థానభ్రంశం = buf->virtual_స్థానభ్రంశం + స్థానభ్రంశం,
        .range = len,
    };
    Vk_Write_Descriptor_సమితి desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_సమితి,
        .dstBinding = bind,
        .descriptor_లెక్క = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_సమితి->binding[bind].descriptorType,
        .p_బఫరు_Info = &desc_pool_write_info_buf,
    };
    update_సమితి_pool_write(s, e, shd, సమితి, &desc_pool_write_info);

    తిరిగి 0;
}

శూన్య ff_vk_shader_update_నెట్టు_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_బిట్లు stage,
                                    పూర్ణాంకం స్థానభ్రంశం, size_t కొలత, శూన్య *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_నెట్టు_Constants(e->buf, shd->pipeline_layout,
                         stage, స్థానభ్రంశం, కొలత, src);
}

శూన్య ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            స్థిరరాశి FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    స్థిరరాశి FFVulkan_Shader_దత్తాంశం *sd = get_shd_దత్తాంశం(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_బిందువు, shd->pipeline);

    ఒకవేళ (sd && sd->nb_descriptor_sets) {
        ఒకవేళ (!shd->use_నెట్టు) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_బిందువు, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ఖాళీ);
        }
    }
}

శూన్య ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#ఒకవేళ 0
    ఒకవేళ (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#అయితే_ముగింపు

    ఒకవేళ (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    ఒకవేళ (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    కొరకు (పూర్ణాంకం i = 0; i < shd->nb_descriptor_sets; i++)
        ఒకవేళ (shd->desc_layout[i])
            vk->Destroy_Descriptor_సమితి_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

శూన్య ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#నిర్వచితమైతే VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#అయితే_ముగింపు
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_బఫరు_unref(&s->device_ref);
    av_బఫరు_unref(&s->చట్రాలు_ref);
}

పూర్ణాంకం ff_vk_init(FFVulkanContext *s, శూన్య *log_మాతృ,
               AVBufferRef *device_ref, AVBufferRef *చట్రాలు_ref)
{
    పూర్ణాంకం err;

    స్థిర స్థిరరాశి AVClass vulkan_context_class = {
        .class_name       = "vk",
        .సంస్కరణ          = LIBAVUTIL_సంస్కరణ_INT,
        .మాతృ_log_context_స్థానభ్రంశం = offsetof(FFVulkanContext, log_మాతృ),
    };

    memset(s, 0, పరిమాణం(*s));
    s->log_మాతృ = log_మాతృ;
    s->class      = &vulkan_context_class;

    ఒకవేళ (చట్రాలు_ref) {
        s->చట్రాలు_ref = av_బఫరు_ref(చట్రాలు_ref);
        ఒకవేళ (!s->చట్రాలు_ref)
            తిరిగి AVERROR(ENOMEM);

        s->చట్రాలు = (AVHWFramesContext *)s->చట్రాలు_ref->దత్తాంశం;
        s->hwfc = s->చట్రాలు->hwctx;

        device_ref = s->చట్రాలు->device_ref;
    }

    s->device_ref = av_బఫరు_ref(device_ref);
    ఒకవేళ (!s->device_ref) {
        ff_vk_uninit(s);
        తిరిగి AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->దత్తాంశం;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_గమ్యం_ముసుగు(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_గమ్యం_ముసుగు(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_ఎక్కించు_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    ఒకవేళ (err < 0) {
        ff_vk_uninit(s);
        తిరిగి err;
    }

    err = ff_vk_ఎక్కించు_props(s);
    ఒకవేళ (err < 0) {
        ff_vk_uninit(s);
        తిరిగి err;
    }

    తిరిగి 0;
}
