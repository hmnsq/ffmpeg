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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "random_seed.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "refstruct.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/vulkan_loader.h"

#ਜੇ CONFIG_SHADER_COMPRESSION
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/zlib_utils.h"
#ਜੇ_ਅੰਤ

ਅਚਲ VkComponentMapping ff_comp_ਪਛਾਣ_ਤੱਤ_map = {
    .r = VK_COMPONENT_SWIZZLE_ਪਛਾਣ_ਤੱਤ,
    .g = VK_COMPONENT_SWIZZLE_ਪਛਾਣ_ਤੱਤ,
    .b = VK_COMPONENT_SWIZZLE_ਪਛਾਣ_ਤੱਤ,
    .a = VK_COMPONENT_SWIZZLE_ਪਛਾਣ_ਤੱਤ,
};

/* Converts return values to strings */
ਅਚਲ ਅੱਖਰ *ff_vk_ret2str(Vk_ਨਤੀਜਾ res)
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CASE(VAL) ਹਾਲਤ VAL: ਵਾਪਸ #VAL
    ਚੋਣ (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_ਸੈੱਟ);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_HOST_ਸਮ੍ਰਿਤੀ);
    CASE(VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_DEVICE_ਸਮ੍ਰਿਤੀ);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_ਗੁਆਚਾ);
    CASE(VK_ERROR_ਸਮ੍ਰਿਤੀ_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_POOL_ਸਮ੍ਰਿਤੀ);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_ਪਤਾ);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_ਗੁਆਚਾ_KHR);
    CASE(VK_ERROR_NATIVE_ਖਿੜਕੀ_ਵਿੱਚ_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_ਸੰਸਕਰਣ_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_ਭਰਿਆ_SCREEN_EXCLUSIVE_ਬਹੁਲਕ_ਗੁਆਚਾ_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_ਪੂਰਾ_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    ਮੂਲ: ਵਾਪਸ "Unknown error";
    }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CASE
}

/* Malitia pura, Khronos */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FN_MAP_ਮੰਜ਼ਿਲ(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## ਮੰਜ਼ਿਲ_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ਦੋਆਧਾਰੀ_ਅੰਕ,                   \
               VK_IMAGE_USAGE_SAMPLED_ਦੋਆਧਾਰੀ_ਅੰਕ);                             \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ);                        \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ);                        \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ਦੋਆਧਾਰੀ_ਅੰਕ,                   \
               VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ);                             \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_ਦੋਆਧਾਰੀ_ਅੰਕ,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_ਦੋਆਧਾਰੀ_ਅੰਕ);                    \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);                \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);                \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);                \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ਨਿਵੇਸ਼_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);                \
        MAP_ਮੰਜ਼ਿਲ(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT);                   \
        ਵਾਪਸ dst;                                                     \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAP_ਮੰਜ਼ਿਲ(flag1, flag2) ਜੇ (src & flag2) dst |= flag1;
FN_MAP_ਮੰਜ਼ਿਲ(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAP_ਮੰਜ਼ਿਲ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAP_ਮੰਜ਼ਿਲ(flag1, flag2) ਜੇ (src & flag1) dst |= flag2;
FN_MAP_ਮੰਜ਼ਿਲ(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MAP_ਮੰਜ਼ਿਲ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ FN_MAP_ਮੰਜ਼ਿਲ

ਸਥਿਰ ਖਾਲੀ ਲੱਦੋ_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        ਪੂਰਨ skip = 0;
        ਲਈ (ਪੂਰਨ j = 0; j < s->nb_qfs; j++) {
            ਜੇ (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (skip)
            ਜਾਰੀ;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ਸਥਿਰ ਖਾਲੀ reset_imageviews(AVRefStructOpaque ਅਣਵਰਤਿਆ, ਖਾਲੀ *obj);

ਪੂਰਨ ff_vk_ਲੱਦੋ_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_ਮਾਪ_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ਧੱਕੋ_desc_props, FF_VK_EXT_ਧੱਕੋ_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ਧੱਕੋ_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_ਸਮ੍ਰਿਤੀ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_ਸਮ੍ਰਿਤੀ_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_ਮੈਟ੍ਰਿਕਸ_props, FF_VK_EXT_COOP_ਮੈਟ੍ਰਿਕਸ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ਮੈਟ੍ਰਿਕਸ_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_ਸਦਿਸ਼_props, FF_VK_EXT_LONG_ਸਦਿਸ਼,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ਸਦਿਸ਼_PROPERTIES_EXT);
#ਜੇ_ਅੰਤ

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#ਜੇ_ਅੰਤ

    ਜੇ (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(ਆਕਾਰ(FFVkImageViews), 0,
                                                         ਨਿਰਾ, ਨਿਰਾ, reset_imageviews,
                                                         ਨਿਰਾ, ਨਿਰਾ);
        ਜੇ (!s->imageviews_pool)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(ਆਕਾਰ(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_ਗਿਣਤੀ = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_ਗਿਣਤੀ = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    ਜੇ (s->host_image_props.copy_Src_Layout_ਗਿਣਤੀ == 512 ||
        s->host_image_props.copy_Dst_Layout_ਗਿਣਤੀ == 512) {
        VkImageLayout *new_array;
        size_t new_ਮਾਪ;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ਨਿਰਾ;
        s->host_image_props.copy_Src_Layout_ਗਿਣਤੀ =
        s->host_image_props.copy_Dst_Layout_ਗਿਣਤੀ = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_ਮਾਪ = s->host_image_props.copy_Src_Layout_ਗਿਣਤੀ +
                   s->host_image_props.copy_Dst_Layout_ਗਿਣਤੀ;
        new_ਮਾਪ *= ਆਕਾਰ(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_ਮਾਪ);
        ਜੇ (!new_array)
            ਵਾਪਸ AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_ਗਿਣਤੀ;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    ਲਈ (ਪੂਰਨ i = 0; i < s->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ; i++)
        s->host_cached_flag |= s->mprops.ਸਮ੍ਰਿਤੀ_Types[i].propertyFlags &
                               VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_CACHED_ਦੋਆਧਾਰੀ_ਅੰਕ;

    ਲੱਦੋ_enabled_qfs(s);

    ਜੇ (s->qf_props)
        ਵਾਪਸ 0;

    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ਨਿਰਾ);

    s->qf_props = av_calloc(s->tot_nb_qfs, ਆਕਾਰ(*s->qf_props));
    ਜੇ (!s->qf_props)
        ਵਾਪਸ AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, ਆਕਾਰ(*s->query_props));
    ਜੇ (!s->qf_props) {
        av_freep(&s->qf_props);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, ਆਕਾਰ(*s->video_props));
    ਜੇ (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, ਆਕਾਰ(*s->ownership_props));
    ਜੇ (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        ਵਾਪਸ AVERROR(ENOMEM);
    }
#ਜੇ_ਅੰਤ

    ਲਈ (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_ਕਤਾਰ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_ਕਤਾਰ,
                         VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_QUERY_ਨਤੀਜਾ_ਸਥਿਤੀ_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_ਕਤਾਰ,
                         VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_VIDEO_PROPERTIES_KHR);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#ਜੇ_ਅੰਤ
    }

    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    ਜੇ (s->extensions & FF_VK_EXT_COOP_ਮੈਟ੍ਰਿਕਸ) {
        vk->Get_Physical_Device_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ਨਿਰਾ);

        ਜੇ (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                ਆਕਾਰ(Vk_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR));
            ਲਈ (ਪੂਰਨ i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_ਮੈਟ੍ਰਿਕਸ_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    ਵਾਪਸ 0;
}

AVVulkan_Device_ਕਤਾਰ_Family *ff_vk_qf_ਲੱਭੋ(FFVulkanContext *s,
                                         Vk_ਕਤਾਰ_Flag_ਬਿੱਟ dev_family,
                                         Vk_Video_Codec_Operation_Flag_ਬਿੱਟ_KHR vid_ops)
{
    ਲਈ (ਪੂਰਨ i = 0; i < s->hwctx->nb_qf; i++) {
        ਜੇ ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            ਵਾਪਸ &s->hwctx->qf[i];
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

ਖਾਲੀ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        ਜੇ (e->sem) {
            VkSemaphoreWaitInfo sem_wait_info = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                .semaphore_ਗਿਣਤੀ = 1,
                .pSemaphores = &e->sem,
                .p_ਮੁੱਲਾਂ = &e->sem_ਮੁੱਲ,
            };
            vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
            vk->DestroySemaphore(s->hwctx->act_dev, e->sem, s->hwctx->alloc);
        }

        exec_discard_deps(s, e);
        pthread_mutex_destroy(&e->ਤਾਲਾ);
    }

    /* Free shader-specific data */
    ਲਈ (ਪੂਰਨ i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_ਅੰਕੜੇ *sd = &pool->reg_shd[i];

        ਜੇ (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++) {
        ਜੇ (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        ਜੇ (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    ਜੇ (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_ਅੰਕੜੇ);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_ਮਾਪ = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ਸਥਿਰ atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ਨਿਰਾ)->qf)];
ਸਥਿਰ AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ਸਥਿਰ ਖਾਲੀ exec_pool_phase_ਬੀਜ(ਖਾਲੀ)
{
    uint32_t ਬੀਜ = av_get_random_ਬੀਜ();
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], ਬੀਜ, memory_order_relaxed);
}

ਪੂਰਨ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_ਕਤਾਰ_Family *qf,
                         FFVkExecPool *pool, ਪੂਰਨ nb_contexts,
                         ਪੂਰਨ nb_queries, VkQueryType query_type, ਪੂਰਨ query_64bit,
                         ਅਚਲ ਖਾਲੀ *query_create_pnext)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_ਬਫਰ_Allocate_Info cbuf_create;

    ਅਚਲ VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ਨਿਰਾ;

    atomic_init(&pool->idx, 0);

    ਜੇ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_ਲੱਭੋ_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        ਜੇ (!ef)
            ਵਾਪਸ AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*ਆਕਾਰ(*pool->cmd_buf_pools));
    ਜੇ (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*ਆਕਾਰ(*pool->cmd_bufs));
    ਜੇ (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_ਬਫਰ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_ਬਫਰ_ALLOCATE_INFO,
            .level              = VK_COMMAND_ਬਫਰ_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_ਬਫਰ_ਗਿਣਤੀ = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }
    }

    /* Query pool */
    ਜੇ (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_ਅਗਲਾ = query_create_pnext,
            .queryType = query_type,
            .query_ਗਿਣਤੀ = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_ਸਥਿਤੀ_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        ਜੇ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            ਪੂਰਨ nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_ਸਥਿਤੀ_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } ਨਹੀਂਤਾਂ ਜੇ (query_type == VK_QUERY_TYPE_ਨਤੀਜਾ_ਸਥਿਤੀ_ONLY_KHR) {
            pool->query_ਸਥਿਤੀ_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_ਮਾਪ = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_ਅੰਕੜੇ = av_calloc(nb_contexts, pool->qd_ਮਾਪ);
        ਜੇ (!pool->query_ਅੰਕੜੇ) {
            err = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, ਆਕਾਰ(*pool->contexts));
    ਜੇ (!pool->contexts) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    pool->pool_ਮਾਪ = nb_contexts;

    ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++)
        pthread_mutex_init(&pool->contexts[i].ਤਾਲਾ, ਨਿਰਾ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    ਪੂਰਨ ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync = 0;
    ਜੇ (s->extensions & FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC) {
        ਅਚਲ VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_ਲੱਭੋ_struct(s->hwctx->device_features.p_ਅਗਲਾ,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync = iqs && iqs->internallySynchronizedQueues;
    }
#ਜੇ_ਅੰਤ

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_ਬੀਜ);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    ਪੂਰਨ pin_ਕਤਾਰ = qf->flags & (VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR |
                                 VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);

    /* Init contexts */
    ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ਅਗਲਾ = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->ਮਾਪਾ = pool;

        /* Query data */
        e->query_ਅੰਕੜੇ = ((uint8_t *)pool->query_ਅੰਕੜੇ) + pool->qd_ਮਾਪ*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_ਕਤਾਰ ? phase % qf->ਅੰਕ : (i + phase) % qf->ਅੰਕ;
        e->qf = qf->idx;
        Vk_Device_ਕਤਾਰ_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_ਕਤਾਰ_INFO_2,
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
            .flags            = ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync ?
                                VK_DEVICE_ਕਤਾਰ_CREATE_INTERNALLY_SYNCHRONIZED_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR : 0,
#ਜੇ_ਅੰਤ
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = qf->idx,
            .ਕਤਾਰ_ਸੂਚਕਾਂਕ       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->ਕਤਾਰ);
    }

    ਵਾਪਸ 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    ਵਾਪਸ err;
}

Vk_ਨਤੀਜਾ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ਖਾਲੀ **ਅੰਕੜੇ, Vk_Query_ਨਤੀਜਾ_Flag_ਬਿੱਟ flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ਅਚਲ FFVkExecPool *pool = e->ਮਾਪਾ;
    Vk_Query_ਨਤੀਜਾ_Flags qf = flags & ~(VK_QUERY_ਨਤੀਜਾ_64_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                      VK_QUERY_ਨਤੀਜਾ_WITH_ਸਥਿਤੀ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);

    ਜੇ (!e->query_ਅੰਕੜੇ) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        ਵਾਪਸ VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_ਨਤੀਜਾ_64_ਦੋਆਧਾਰੀ_ਅੰਕ : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_ਨਤੀਜਾ_WITH_ਸਥਿਤੀ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR : 0x0;

    ਜੇ (ਅੰਕੜੇ)
        *ਅੰਕੜੇ = e->query_ਅੰਕੜੇ;

    ਵਾਪਸ vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_ਮਾਪ, e->query_ਅੰਕੜੇ,
                                   pool->qd_ਮਾਪ, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        ਜੇ (pthread_mutex_trylock(&e->ਤਾਲਾ))
            ਜਾਰੀ; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        ਜੇ (vk->Get_Semaphore_Counter_ਮੁੱਲ(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_ਮੁੱਲ &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_ਚੌਖਟਾ_deps || e->nb_sw_ਚੌਖਟਾ_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->ਤਾਲਾ);
    }

    ਵਾਪਸ &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_ਮਾਪ];
}

ਖਾਲੀ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ਗਿਣਤੀ = 1,
        .pSemaphores = &e->sem,
        .p_ਮੁੱਲਾਂ = &e->sem_ਮੁੱਲ,
    };
    pthread_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->ਤਾਲਾ);
}

ਪੂਰਨ ff_vk_exec_ਸ਼ੁਰੂ(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ਅਚਲ FFVkExecPool *pool = e->ਮਾਪਾ;

    Vk_Command_ਬਫਰ_Begin_Info cmd_ਸ਼ੁਰੂ = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_ਬਫਰ_BEGIN_INFO,
        .flags = VK_COMMAND_ਬਫਰ_USAGE_ONE_ਸਮਾਂ_SUBMIT_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ਗਿਣਤੀ = 1,
        .pSemaphores = &e->sem,
        .p_ਮੁੱਲਾਂ = &e->sem_ਮੁੱਲ,
    };

    pthread_mutex_ਤਾਲਾ(&e->ਤਾਲਾ);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_ਬਫਰ(e->buf, &cmd_ਸ਼ੁਰੂ);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->ਤਾਲਾ);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਜੇ (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_ਮੁੱਲ++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .ਮੁੱਲ = e->sem_ਮੁੱਲ,
        .stage_ਨਕਾਬ = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };

    pthread_mutex_unlock(&e->ਤਾਲਾ);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_buf_deps; j++)
        av_ਬਫਰ_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        ਚੋਣ (od->type) {
        ਹਾਲਤ VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            ਰੋਕੋ;
        ਹਾਲਤ VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            ਰੋਕੋ;
        ਮੂਲ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_sw_ਚੌਖਟਾ_deps; j++)
        av_ਚੌਖਟਾ_free(&e->sw_ਚੌਖਟਾ_deps[j]);
    e->nb_sw_ਚੌਖਟਾ_deps = 0;

    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_ਚੌਖਟਾ_deps; j++) {
        AVFrame *f = e->ਚੌਖਟਾ_deps[j];
        ਜੇ (e->ਚੌਖਟਾ_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
            AVVulkan_ਚੌਖਟੇ_Context *vkfc = hwfc->hwctx;
            AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];
            vkfc->unlock_ਚੌਖਟਾ(hwfc, vkf);
            e->ਚੌਖਟਾ_locked[j] = 0;
        }
        e->ਚੌਖਟਾ_update[j] = 0;
    }
    e->nb_ਚੌਖਟਾ_deps = 0;

    e->sem_wait_cnt = 0;
    e->sem_sig_cnt = 0;
    e->sem_sig_val_dst_cnt = 0;
}

ਖਾਲੀ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;
    VkSemaphoreSignalInfo sig_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO,
        .semaphore = e->sem,
        .ਮੁੱਲ = e->sem_ਮੁੱਲ,
    };

    /* An abandoned recording is exclusively the claimer's: free everything
     * without the mutex, and un-claim last by signalling the burnt generation */
    exec_discard_deps(s, e);
    vk->Reset_Command_ਬਫਰ(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ਖਾਲੀ *obj)
{
    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->refstruct_deps[e->nb_refstruct_deps++] = av_refstruct_ref(obj);
}

ਖਾਲੀ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ਖਾਲੀ *obj)
{
    ਖਾਲੀ **ptr = obj;

    av_assert1(e->nb_refstruct_deps < FF_VK_EXEC_MAX_BUF_DEPS);

    ਲਈ (ਪੂਰਨ i = 0; i < e->nb_refstruct_deps; i++) {
        ਜੇ (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            ਵਾਪਸ;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ਨਿਰਾ;
}

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

ਪੂਰਨ ff_vk_exec_ਜੋੜੋ_dep_sw_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_ਚੌਖਟਾ_deps < FF_VK_EXEC_MAX_SW_ਚੌਖਟਾ_DEPS);

    e->sw_ਚੌਖਟਾ_deps[e->nb_sw_ਚੌਖਟਾ_deps] = av_ਚੌਖਟਾ_clone(f);
    ਜੇ (!e->sw_ਚੌਖਟਾ_deps[e->nb_sw_ਚੌਖਟਾ_deps])
        ਵਾਪਸ AVERROR(ENOMEM);

    e->nb_sw_ਚੌਖਟਾ_deps++;

    ਵਾਪਸ 0;
}

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ਮੁੱਲ = val,
        .stage_ਨਕਾਬ = stage,
    };
}

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ਮੁੱਲ = val,
        .stage_ਨਕਾਬ = stage,
    };
}

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ਪੂਰਨ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ਪੂਰਨ wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    ਜੇ (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        ਲਈ (ਪੂਰਨ i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_ਨਕਾਬ = stage,
            };
        }

        ਵਾਪਸ;
    }

    /* Ownership of each semaphore passes to the execution */
    ਲਈ (ਪੂਰਨ i = 0; i < nb; i++) {
        ff_vk_exec_ਜੋੜੋ_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_ਜੋੜੋ_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

ਪੂਰਨ ff_vk_exec_ਜੋੜੋ_dep_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVVulkan_ਚੌਖਟੇ_Context *vkfc = hwfc->hwctx;
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];
    ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);

    /* Don't add duplicates */
    ਲਈ (ਪੂਰਨ i = 0; i < e->nb_ਚੌਖਟਾ_deps; i++)
        ਜੇ (e->ਚੌਖਟਾ_deps[i]->ਅੰਕੜੇ[0] == f->ਅੰਕੜੇ[0])
            ਵਾਪਸ 1;

    av_assert1(e->nb_ਚੌਖਟਾ_deps < FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    ਜੇ (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_ਬਫਰ_ref(f->buf[0]);
        ਜੇ (!e->buf_deps[e->nb_buf_deps])
            ਵਾਪਸ AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->ਚੌਖਟਾ_deps[e->nb_ਚੌਖਟਾ_deps] = f;

    vkfc->ਤਾਲਾ_ਚੌਖਟਾ(hwfc, vkf);
    e->ਚੌਖਟਾ_locked[e->nb_ਚੌਖਟਾ_deps] = 1;
    e->ਚੌਖਟਾ_update[e->nb_ਚੌਖਟਾ_deps] = 0;
    e->nb_ਚੌਖਟਾ_deps++;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ਮੁੱਲ = vkf->sem_ਮੁੱਲ[i],
            .stage_ਨਕਾਬ = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ਮੁੱਲ = vkf->sem_ਮੁੱਲ[i] + 1,
            .stage_ਨਕਾਬ = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_ਮੁੱਲ[i];
        e->sem_sig_val_dst_cnt++;
    }

    ਵਾਪਸ 0;
}

ਖਾਲੀ ff_vk_exec_update_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 *bar, uint32_t *nb_img_bar)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < e->nb_ਚੌਖਟਾ_deps; i++)
        ਜੇ (e->ਚੌਖਟਾ_deps[i]->ਅੰਕੜੇ[0] == f->ਅੰਕੜੇ[0])
            ਰੋਕੋ;
    av_assert0(i < e->nb_ਚੌਖਟਾ_deps);

    /* Don't update duplicates */
    ਜੇ (nb_img_bar && !e->ਚੌਖਟਾ_update[i])
        (*nb_img_bar)++;

    e->ਕਤਾਰ_family_dst[i] = bar->dst_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ;
    e->access_dst[i] = bar->dst_Access_ਨਕਾਬ;
    e->layout_dst[i] = bar->newLayout;
    e->ਚੌਖਟਾ_update[i] = 1;
}

ਪੂਰਨ ff_vk_exec_mirror_sem_ਮੁੱਲ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];

    /* Reject unknown frames */
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < e->nb_ਚੌਖਟਾ_deps; i++)
        ਜੇ (e->ਚੌਖਟਾ_deps[i]->ਅੰਕੜੇ[0] == f->ਅੰਕੜੇ[0])
            ਰੋਕੋ;
    ਜੇ (i == e->nb_ਚੌਖਟਾ_deps)
        ਵਾਪਸ AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_ਮੁੱਲ[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_ਬਫਰ_Submit_Info cmd_buf_info = (Vk_Command_ਬਫਰ_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_ਬਫਰ_SUBMIT_INFO,
        .command_ਬਫਰ = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_ਬਫਰ_Infos = &cmd_buf_info,
        .command_ਬਫਰ_Info_ਗਿਣਤੀ = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_ਗਿਣਤੀ = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_ਗਿਣਤੀ = e->sem_sig_cnt,
    };

    ret = vk->ਸਿਰਾ_Command_ਬਫਰ(e->buf);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

#ਜੇ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->ਤਾਲਾ_ਕਤਾਰ(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#ਜੇ_ਅੰਤ
    ret = vk->ਕਤਾਰ_Submit2(e->ਕਤਾਰ, 1, &submit_info, VK_NULL_HANDLE);
#ਜੇ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_ਕਤਾਰ(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#ਜੇ_ਅੰਤ

    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    ਲਈ (ਪੂਰਨ j = 0; j < e->nb_ਚੌਖਟਾ_deps; j++) {
        ਜੇ (e->ਚੌਖਟਾ_locked[j]) {
            AVFrame *f = e->ਚੌਖਟਾ_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
            AVVulkan_ਚੌਖਟੇ_Context *vkfc = hwfc->hwctx;
            AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];

            ਜੇ (e->ਚੌਖਟਾ_update[j]) {
                ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);
                ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->ਕਤਾਰ_family[i] = e->ਕਤਾਰ_family_dst[j];
                }
            }
            vkfc->unlock_ਚੌਖਟਾ(hwfc, vkf);
            e->ਚੌਖਟਾ_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_alloc_mem(FFVulkanContext *s, Vk_ਸਮ੍ਰਿਤੀ_Requirements *req,
                    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ req_flags, ਖਾਲੀ *alloc_extension,
                    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ *mem_flags, Vk_Device_ਸਮ੍ਰਿਤੀ *mem)
{
    Vk_ਨਤੀਜਾ ret;
    ਪੂਰਨ ਸੂਚਕਾਂਕ = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ਸਮ੍ਰਿਤੀ_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_ALLOCATE_INFO,
        .p_ਅਗਲਾ           = alloc_extension,
    };

    alloc_info.ਵੰਡ_ਮਾਪ = req->ਮਾਪ;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ਲਈ (ਪੂਰਨ i = 0; i < s->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        ਜੇ (!(req->ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ & (1 << i)))
            ਜਾਰੀ;

        /* The memory type flags must include our properties */
        ਜੇ ((req_flags != UINT32_MAX) &&
            ((s->mprops.ਸਮ੍ਰਿਤੀ_Types[i].propertyFlags & req_flags) != req_flags))
            ਜਾਰੀ;

        /* Found a suitable memory type */
        ਸੂਚਕਾਂਕ = i;
        ਰੋਕੋ;
    }

    ਜੇ (ਸੂਚਕਾਂਕ < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    alloc_info.ਸਮ੍ਰਿਤੀ_Type_ਸੂਚਕਾਂਕ = ਸੂਚਕਾਂਕ;

    ret = vk->Allocate_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    ਜੇ (ret != VK_SUCCESS)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (mem_flags)
        *mem_flags |= s->mprops.ਸਮ੍ਰਿਤੀ_Types[ਸੂਚਕਾਂਕ].propertyFlags;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_ਸਮ੍ਰਿਤੀ *mem,
                       ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, VkFormat format, ਪੂਰਨ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ਖਾਲੀ *create_pnext)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_ਅਗਲਾ         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { ਚੌੜਾਈ, ਉਚਾਈ, 1 },
        .mip_ਪੱਧਰ     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_ਗਿਣਤੀ_1_ਦੋਆਧਾਰੀ_ਅੰਕ,
        .sharing_ਬਹੁਲਕ   = VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_ALLOCATE_INFO,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_2,
    };
    Vk_Image_ਸਮ੍ਰਿਤੀ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_ਸਮ੍ਰਿਤੀ_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_ਸਮ੍ਰਿਤੀ_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_ਸਮ੍ਰਿਤੀ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.ਸਮ੍ਰਿਤੀ_Requirements,
                          VK_ਸਮ੍ਰਿਤੀ_PROPERTY_DEVICE_LOCAL_ਦੋਆਧਾਰੀ_ਅੰਕ,
                          &ded_alloc, &mem_flags, mem);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    bind_info.image  = *img;
    bind_info.ਸਮ੍ਰਿਤੀ = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ਜਾਓ fail;
    }

    ਵਾਪਸ 0;

fail:
    ff_vk_image_free(s, img, mem);
    ਵਾਪਸ err;
}

ਖਾਲੀ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_ਸਮ੍ਰਿਤੀ *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ਜੇ (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    ਜੇ (*mem) {
        vk->Free_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

ਪੂਰਨ ff_vk_create_buf(FFVulkanContext *s, FFVk_ਬਫਰ *buf, size_t ਮਾਪ,
                     ਖਾਲੀ *p_ਅਗਲਾ, ਖਾਲੀ *alloc_p_ਅਗਲਾ,
                     Vk_ਬਫਰ_Usage_Flags usage, Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ flags)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    ਪੂਰਨ use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ਬਫਰ_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_ਬਫਰ_CREATE_INFO,
        .p_ਅਗਲਾ       = p_ਅਗਲਾ,
        .usage       = usage,
        .sharing_ਬਹੁਲਕ = VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
        .ਮਾਪ        = flags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ ?
                       FFALIGN(ਮਾਪ, s->props.properties.limits.min_ਸਮ੍ਰਿਤੀ_Map_Alignment) :
                       ਮਾਪ,
    };

    Vk_ਸਮ੍ਰਿਤੀ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_ALLOCATE_FLAGS_INFO,
        .flags = VK_ਸਮ੍ਰਿਤੀ_ALLOCATE_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };
    Vk_ਬਫਰ_ਸਮ੍ਰਿਤੀ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_ਬਫਰ_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_INFO_2,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_ALLOCATE_INFO,
        .p_ਅਗਲਾ = alloc_p_ਅਗਲਾ,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_REQUIREMENTS,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_2,
        .p_ਅਗਲਾ = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           ਮਾਪ, usage, flags);

    ret = vk->Create_ਬਫਰ(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    req_desc.ਬਫਰ = buf->buf;

    vk->Get_ਬਫਰ_ਸਮ੍ਰਿਤੀ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_ਵੰਡ |
                  ded_req.requires_Dedicated_ਵੰਡ;
    ਜੇ (use_ded_mem) {
        ded_alloc.ਬਫਰ = buf->buf;
        ded_alloc.p_ਅਗਲਾ = alloc_p_ਅਗਲਾ;
        alloc_p_ਅਗਲਾ = &ded_alloc;
    }

    ਜੇ (usage & VK_ਬਫਰ_USAGE_SHADER_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ) {
        alloc_flags.p_ਅਗਲਾ = alloc_p_ਅਗਲਾ;
        alloc_p_ਅਗਲਾ = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.ਸਮ੍ਰਿਤੀ_Requirements, flags, alloc_p_ਅਗਲਾ,
                          &buf->flags, &buf->mem);
    ਜੇ (err)
        ਵਾਪਸ err;

    ret = vk->Bind_ਬਫਰ_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਜੇ (usage & VK_ਬਫਰ_USAGE_SHADER_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ) {
        Vk_ਬਫਰ_Device_ਪਤਾ_Info ਪਤਾ_info = {
            .sType = VK_STRUCTURE_TYPE_ਬਫਰ_DEVICE_ਪਤਾ_INFO,
            .ਬਫਰ = buf->buf,
        };
        buf->ਪਤਾ = vk->Get_ਬਫਰ_Device_ਪਤਾ(s->hwctx->act_dev, &ਪਤਾ_info);
    }

    buf->ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_map_buffers(FFVulkanContext *s, FFVk_ਬਫਰ **buf, uint8_t *mem[],
                      ਪੂਰਨ nb_buffers, ਪੂਰਨ invalidate)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_ਸਮ੍ਰਿਤੀ_Range inval_list[64];
    ਪੂਰਨ inval_ਗਿਣਤੀ = 0;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_buffers; i++) {
        ਖਾਲੀ *dst;
        ret = vk->Map_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_ਸਾਰਾ_ਮਾਪ, 0, &dst);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        ਜੇ (mem)
            mem[i] = dst;
    }

    ਜੇ (!invalidate)
        ਵਾਪਸ 0;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_buffers; i++) {
        ਅਚਲ Vk_Mapped_ਸਮ੍ਰਿਤੀ_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_ਸਮ੍ਰਿਤੀ_RANGE,
            .ਸਮ੍ਰਿਤੀ = buf[i]->mem,
            .ਮਾਪ   = VK_ਸਾਰਾ_ਮਾਪ,
        };
        ਜੇ (buf[i]->flags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_COHERENT_ਦੋਆਧਾਰੀ_ਅੰਕ)
            ਜਾਰੀ;
        inval_list[inval_ਗਿਣਤੀ++] = ival_buf;
    }

    ਜੇ (inval_ਗਿਣਤੀ) {
        ret = vk->Invalidate_Mapped_ਸਮ੍ਰਿਤੀ_Ranges(s->hwctx->act_dev, inval_ਗਿਣਤੀ,
                                               inval_list);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_flush_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ *buf,
                       Vk_Device_ਮਾਪ ਵਿੱਥ, Vk_Device_ਮਾਪ mem_ਮਾਪ,
                       ਪੂਰਨ flush)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ਜੇ (buf->flags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_COHERENT_ਦੋਆਧਾਰੀ_ਅੰਕ)
        ਵਾਪਸ 0;

    ਅਚਲ Vk_Mapped_ਸਮ੍ਰਿਤੀ_Range flush_ਅੰਕੜੇ = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_ਸਮ੍ਰਿਤੀ_RANGE,
        .ਸਮ੍ਰਿਤੀ = buf->mem,
        .ਵਿੱਥ = ਵਿੱਥ,
        .ਮਾਪ   = mem_ਮਾਪ,
    };

    ਜੇ (flush)
        ret = vk->Flush_Mapped_ਸਮ੍ਰਿਤੀ_Ranges(s->hwctx->act_dev, 1, &flush_ਅੰਕੜੇ);
    ਨਹੀਂਤਾਂ
        ret = vk->Invalidate_Mapped_ਸਮ੍ਰਿਤੀ_Ranges(s->hwctx->act_dev, 1, &flush_ਅੰਕੜੇ);

    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_ਬਫਰ **buf, ਪੂਰਨ nb_buffers,
                        ਪੂਰਨ flush)
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_ਸਮ੍ਰਿਤੀ_Range flush_list[64];
    ਪੂਰਨ flush_ਗਿਣਤੀ = 0;

    ਜੇ (flush) {
        ਲਈ (ਪੂਰਨ i = 0; i < nb_buffers; i++) {
            ਅਚਲ Vk_Mapped_ਸਮ੍ਰਿਤੀ_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_ਸਮ੍ਰਿਤੀ_RANGE,
                .ਸਮ੍ਰਿਤੀ = buf[i]->mem,
                .ਮਾਪ   = VK_ਸਾਰਾ_ਮਾਪ,
            };

            av_assert0(!buf[i]->host_ref);
            ਜੇ (buf[i]->flags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_COHERENT_ਦੋਆਧਾਰੀ_ਅੰਕ)
                ਜਾਰੀ;
            flush_list[flush_ਗਿਣਤੀ++] = flush_buf;
        }
    }

    ਜੇ (flush_ਗਿਣਤੀ) {
        ret = vk->Flush_Mapped_ਸਮ੍ਰਿਤੀ_Ranges(s->hwctx->act_dev, flush_ਗਿਣਤੀ,
                                          flush_list);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    ਲਈ (ਪੂਰਨ i = 0; i < nb_buffers; i++) {
        vk->Unmap_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ਨਿਰਾ;
    }

    ਵਾਪਸ err;
}

ਖਾਲੀ ff_vk_free_buf(FFVulkanContext *s, FFVk_ਬਫਰ *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ਜੇ (!buf || !s->hwctx)
        ਵਾਪਸ;

    ਜੇ (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_ਬਫਰ(s, buf, 0);
    ਜੇ (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_ਬਫਰ(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    ਜੇ (buf->mem != VK_NULL_HANDLE)
        vk->Free_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    ਜੇ (buf->host_ref)
        av_ਬਫਰ_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ pooled_buf_free(AVRefStructOpaque opaque, ਖਾਲੀ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ਪੂਰਨ ff_vk_get_pooled_ਬਫਰ(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_ਬਫਰ **buf, Vk_ਬਫਰ_Usage_Flags usage,
                            ਖਾਲੀ *create_p_ਅਗਲਾ, size_t ਮਾਪ,
                            Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ mem_props)
{
    ਪੂਰਨ err;
    FFVk_ਬਫਰ *ਅੰਕੜੇ;

    ਜੇ (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(ਆਕਾਰ(FFVk_ਬਫਰ), 0, ctx,
                                                ਨਿਰਾ, ਨਿਰਾ, pooled_buf_free,
                                                ਨਿਰਾ);
        ਜੇ (!(*buf_pool))
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    *buf = ਅੰਕੜੇ = av_refstruct_pool_get(*buf_pool);
    ਜੇ (!ਅੰਕੜੇ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (ਅੰਕੜੇ->ਮਾਪ >= ਮਾਪ)
        ਵਾਪਸ 0;

    ff_vk_free_buf(ctx, ਅੰਕੜੇ);
    memset(ਅੰਕੜੇ, 0, ਆਕਾਰ(*ਅੰਕੜੇ));

    err = ff_vk_create_buf(ctx, ਅੰਕੜੇ, ਮਾਪ,
                           create_p_ਅਗਲਾ, ਨਿਰਾ, usage,
                           mem_props);
    ਜੇ (err < 0) {
        av_refstruct_unref(buf);
        ਵਾਪਸ err;
    }

    ਜੇ (mem_props & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ) {
        err = ff_vk_map_ਬਫਰ(ctx, ਅੰਕੜੇ, &ਅੰਕੜੇ->mapped_mem, 0);
        ਜੇ (err < 0) {
            av_refstruct_unref(buf);
            ਵਾਪਸ err;
        }
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ create_mapped_ਬਫਰ(FFVulkanContext *s,
                                FFVk_ਬਫਰ *vkb, Vk_ਬਫਰ_Usage_Flags usage,
                                size_t ਮਾਪ,
                                Vk_External_ਸਮ੍ਰਿਤੀ_ਬਫਰ_Create_Info *create_desc,
                                Vk_Import_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Info_EXT *import_desc,
                                Vk_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Properties_EXT props)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ਬਫਰ_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_ਬਫਰ_CREATE_INFO,
        .p_ਅਗਲਾ       = create_desc,
        .usage       = usage,
        .sharing_ਬਹੁਲਕ = VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
        .ਮਾਪ        = ਮਾਪ,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Requirements req = {
        .ਮਾਪ           = ਮਾਪ,
        .alignment      = s->hprops.min_Imported_Host_ਸੂਚਕ_Alignment,
        .ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ = props.ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ,
                          import_desc, &vkb->flags, &vkb->mem);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    ret = vk->Create_ਬਫਰ(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    ਜੇ (ret != VK_SUCCESS) {
        vk->Free_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ret = vk->Bind_ਬਫਰ_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    ਜੇ (ret != VK_SUCCESS) {
        vk->Free_ਸਮ੍ਰਿਤੀ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_ਬਫਰ(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ host_map_free(AVRefStructOpaque opaque, ਖਾਲੀ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ਪੂਰਨ ff_vk_host_map_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ **dst,
                          uint8_t *src_ਅੰਕੜੇ, Vk_Device_ਮਾਪ ਮਾਪ,
                          ਅਚਲ AVBufferRef *src_buf,
                          Vk_ਬਫਰ_Usage_Flags usage)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_ਸਮ੍ਰਿਤੀ_ਬਫਰ_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_ਸਮ੍ਰਿਤੀ_ਬਫਰ_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_HOST_ਵੰਡ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_ALLOCATE_FLAGS_INFO,
        .flags = VK_ਸਮ੍ਰਿਤੀ_ALLOCATE_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };
    Vk_Import_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_ਸਮ੍ਰਿਤੀ_HOST_ਸੂਚਕ_INFO_EXT,
        .handleType = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_HOST_ਵੰਡ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
        .p_ਅਗਲਾ = usage & VK_ਬਫਰ_USAGE_SHADER_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ ? &alloc_flags : ਨਿਰਾ,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_ਬਫਰ *vkb;
    size_t offs;
    size_t ਬਫਰ_ਮਾਪ;

    *dst = ਨਿਰਾ;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_ਅੰਕੜੇ % s->hprops.min_Imported_Host_ਸੂਚਕ_Alignment;
    import_desc.p_Host_ਸੂਚਕ = src_ਅੰਕੜੇ - offs;

    props = (Vk_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Properties_EXT) {
        VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_HOST_ਸੂਚਕ_PROPERTIES_EXT,
    };
    ret = vk->Get_ਸਮ੍ਰਿਤੀ_Host_ਸੂਚਕ_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_ਸੂਚਕ,
                                                &props);
    ਜੇ (!(ret == VK_SUCCESS && props.ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ))
        ਵਾਪਸ AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_ਬਫਰ_ref(src_buf);
    ਜੇ (!ref)
        ਵਾਪਸ AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ਅਚਲ Vk_Device_ਮਾਪ src_avail = src_buf->ਮਾਪ - (src_ਅੰਕੜੇ - src_buf->ਅੰਕੜੇ);
    ਬਫਰ_ਮਾਪ = offs + FFMIN(ਮਾਪ, src_avail);
    ਬਫਰ_ਮਾਪ = FFALIGN(ਬਫਰ_ਮਾਪ, s->props.properties.limits.min_ਸਮ੍ਰਿਤੀ_Map_Alignment);
    ਬਫਰ_ਮਾਪ = FFALIGN(ਬਫਰ_ਮਾਪ, s->hprops.min_Imported_Host_ਸੂਚਕ_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(ਆਕਾਰ(*vkb), 0, s, host_map_free);
    ਜੇ (!vkb) {
        av_ਬਫਰ_unref(&ref);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    err = create_mapped_ਬਫਰ(s, vkb, usage,
                               ਬਫਰ_ਮਾਪ, &create_desc, &import_desc,
                               props);
    ਜੇ (err < 0) {
        av_ਬਫਰ_unref(&ref);
        av_refstruct_unref(&vkb);
        ਵਾਪਸ err;
    }

    ਜੇ (usage & VK_ਬਫਰ_USAGE_SHADER_DEVICE_ਪਤਾ_ਦੋਆਧਾਰੀ_ਅੰਕ) {
        Vk_ਬਫਰ_Device_ਪਤਾ_Info ਪਤਾ_info = {
            .sType = VK_STRUCTURE_TYPE_ਬਫਰ_DEVICE_ਪਤਾ_INFO,
            .ਬਫਰ = vkb->buf,
        };
        vkb->ਪਤਾ = vk->Get_ਬਫਰ_Device_ਪਤਾ(s->hwctx->act_dev, &ਪਤਾ_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_ਵਿੱਥ = offs;
    vkb->ਪਤਾ       += offs;
    vkb->mapped_mem     = src_ਅੰਕੜੇ;
    vkb->ਮਾਪ           = ਬਫਰ_ਮਾਪ - offs;

    *dst = vkb;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_shader_ਜੋੜੋ_ਧੱਕੋ_const(FFVulkanShader *shd, ਪੂਰਨ ਵਿੱਥ, ਪੂਰਨ ਮਾਪ,
                                Vk_Shader_Stage_Flag_ਬਿੱਟ stage)
{
    Vk_ਧੱਕੋ_Constant_Range *pc = &shd->ਧੱਕੋ_consts[shd->ਧੱਕੋ_consts_ਅੰਕ++];
    av_assert1(shd->ਧੱਕੋ_consts_ਅੰਕ < FF_VK_MAX_ਧੱਕੋ_CONSTS);
    pc->stageFlags = stage;
    pc->ਵਿੱਥ = ਵਿੱਥ;
    pc->ਮਾਪ = ਮਾਪ;
    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ਪੂਰਨ unnorm_coords, VkFilter filt)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_ਬਹੁਲਕ = (unnorm_coords || filt == VK_FILTER_ਸਭ_ਤੋਂ_ਨੇੜੇ) ?
                      VK_SAMPLER_MIPMAP_ਬਹੁਲਕ_ਸਭ_ਤੋਂ_ਨੇੜੇ :
                      VK_SAMPLER_MIPMAP_ਬਹੁਲਕ_ਰੇਖਿਕ,
        .ਪਤਾ_ਬਹੁਲਕ_U = VK_SAMPLER_ਪਤਾ_ਬਹੁਲਕ_CLAMP_ਮੰਜ਼ਿਲ_ਕਿਨਾਰਾ,
        .ਪਤਾ_ਬਹੁਲਕ_V = sampler_info.ਪਤਾ_ਬਹੁਲਕ_U,
        .ਪਤਾ_ਬਹੁਲਕ_W = sampler_info.ਪਤਾ_ਬਹੁਲਕ_U,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ਪੂਰਨ p)
{
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);
    ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);

    ਸਥਿਰ ਅਚਲ VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ,
                                                       VK_IMAGE_ASPECT_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ,
                                                       VK_IMAGE_ASPECT_PLANE_2_ਦੋਆਧਾਰੀ_ਅੰਕ, };

    ਜੇ (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        ਵਾਪਸ VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ;

    ਵਾਪਸ plane_aspect[p];
}

ਪੂਰਨ ff_vk_mt_is_np_rgb(ਗਿਣਤੀ AVPixelFormat pix_fmt)
{
    ਜੇ (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        ਵਾਪਸ 1;
    ਵਾਪਸ 0;
}

ਖਾਲੀ ff_vk_ਸੈੱਟ_perm(ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ lut[4], ਪੂਰਨ inv)
{
    ਚੋਣ (pix_fmt) {
    ਹਾਲਤ AV_PIX_FMT_GBRP:
    ਹਾਲਤ AV_PIX_FMT_GBRAP:
    ਹਾਲਤ AV_PIX_FMT_GBRAP10:
    ਹਾਲਤ AV_PIX_FMT_GBRAP12:
    ਹਾਲਤ AV_PIX_FMT_GBRAP14:
    ਹਾਲਤ AV_PIX_FMT_GBRAP16:
    ਹਾਲਤ AV_PIX_FMT_GBRAPF16:
    ਹਾਲਤ AV_PIX_FMT_GBRP10:
    ਹਾਲਤ AV_PIX_FMT_GBRP12:
    ਹਾਲਤ AV_PIX_FMT_GBRP14:
    ਹਾਲਤ AV_PIX_FMT_GBRP16:
    ਹਾਲਤ AV_PIX_FMT_GBRPF16:
    ਹਾਲਤ AV_PIX_FMT_GBRPF32:
    ਹਾਲਤ AV_PIX_FMT_GBRAP32:
    ਹਾਲਤ AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_BGRA:
    ਹਾਲਤ AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        ਰੋਕੋ;
    ਮੂਲ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        ਰੋਕੋ;
    }

    ਜੇ (inv) {
        ਪੂਰਨ lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    ਵਾਪਸ;
}

ਅਚਲ ਅੱਖਰ *ff_vk_shader_rep_fmt(ਗਿਣਤੀ AVPixelFormat pix_fmt,
                                 ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt)
{
    ਚੋਣ (pix_fmt) {
    ਹਾਲਤ AV_PIX_FMT_RGBA:
    ਹਾਲਤ AV_PIX_FMT_BGRA:
    ਹਾਲਤ AV_PIX_FMT_RGB24:
    ਹਾਲਤ AV_PIX_FMT_BGR24:
    ਹਾਲਤ AV_PIX_FMT_BGR0:
    ਹਾਲਤ AV_PIX_FMT_RGB0:
    ਹਾਲਤ AV_PIX_FMT_RGB565:
    ਹਾਲਤ AV_PIX_FMT_BGR565:
    ਹਾਲਤ AV_PIX_FMT_UYVA:
    ਹਾਲਤ AV_PIX_FMT_YUYV422:
    ਹਾਲਤ AV_PIX_FMT_UYVY422: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_X2RGB10:
    ਹਾਲਤ AV_PIX_FMT_X2BGR10:
    ਹਾਲਤ AV_PIX_FMT_Y210:
    ਹਾਲਤ AV_PIX_FMT_XV30: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ਨਿਰਾ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_RGB48:
    ਹਾਲਤ AV_PIX_FMT_RGBA64:
    ਹਾਲਤ AV_PIX_FMT_Y212:
    ਹਾਲਤ AV_PIX_FMT_Y216:
    ਹਾਲਤ AV_PIX_FMT_XV36:
    ਹਾਲਤ AV_PIX_FMT_XV48: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_RGBAF16: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_RGBF32:
    ਹਾਲਤ AV_PIX_FMT_RGBAF32: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_RGB96:
    ਹਾਲਤ AV_PIX_FMT_RGBA128: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ਨਿਰਾ,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    }
    ਹਾਲਤ AV_PIX_FMT_GBRP:
    ਹਾਲਤ AV_PIX_FMT_GRAY8:
    ਹਾਲਤ AV_PIX_FMT_GBRAP:
    ਹਾਲਤ AV_PIX_FMT_YUV420P:
    ਹਾਲਤ AV_PIX_FMT_YUV422P:
    ਹਾਲਤ AV_PIX_FMT_YUV444P:
    ਹਾਲਤ AV_PIX_FMT_YUVA420P:
    ਹਾਲਤ AV_PIX_FMT_YUVA422P:
    ਹਾਲਤ AV_PIX_FMT_YUVA444P: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_GRAY10:
    ਹਾਲਤ AV_PIX_FMT_GRAY12:
    ਹਾਲਤ AV_PIX_FMT_GRAY14:
    ਹਾਲਤ AV_PIX_FMT_GRAY16:
    ਹਾਲਤ AV_PIX_FMT_GBRAP10:
    ਹਾਲਤ AV_PIX_FMT_GBRAP12:
    ਹਾਲਤ AV_PIX_FMT_GBRAP14:
    ਹਾਲਤ AV_PIX_FMT_GBRAP16:
    ਹਾਲਤ AV_PIX_FMT_GBRAPF16:
    ਹਾਲਤ AV_PIX_FMT_GBRP10:
    ਹਾਲਤ AV_PIX_FMT_GBRP12:
    ਹਾਲਤ AV_PIX_FMT_GBRP14:
    ਹਾਲਤ AV_PIX_FMT_GBRP16:
    ਹਾਲਤ AV_PIX_FMT_GBRPF16:
    ਹਾਲਤ AV_PIX_FMT_XYZP12:
    ਹਾਲਤ AV_PIX_FMT_YUV420P10:
    ਹਾਲਤ AV_PIX_FMT_YUV420P12:
    ਹਾਲਤ AV_PIX_FMT_YUV420P16:
    ਹਾਲਤ AV_PIX_FMT_YUV422P10:
    ਹਾਲਤ AV_PIX_FMT_YUV422P12:
    ਹਾਲਤ AV_PIX_FMT_YUV422P16:
    ਹਾਲਤ AV_PIX_FMT_YUV444P10:
    ਹਾਲਤ AV_PIX_FMT_YUV444P12:
    ਹਾਲਤ AV_PIX_FMT_YUV444P16:
    ਹਾਲਤ AV_PIX_FMT_YUVA420P10:
    ਹਾਲਤ AV_PIX_FMT_YUVA420P16:
    ਹਾਲਤ AV_PIX_FMT_YUVA422P10:
    ਹਾਲਤ AV_PIX_FMT_YUVA422P12:
    ਹਾਲਤ AV_PIX_FMT_YUVA422P16:
    ਹਾਲਤ AV_PIX_FMT_YUVA444P10:
    ਹਾਲਤ AV_PIX_FMT_YUVA444P12:
    ਹਾਲਤ AV_PIX_FMT_YUVA444P16:
    ਹਾਲਤ AV_PIX_FMT_BAYER_RGGB16: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_GRAY32:
    ਹਾਲਤ AV_PIX_FMT_GRAYF32:
    ਹਾਲਤ AV_PIX_FMT_GBRPF32:
    ਹਾਲਤ AV_PIX_FMT_GBRAPF32: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_GBRAP32: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ਨਿਰਾ,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_NV12:
    ਹਾਲਤ AV_PIX_FMT_NV16:
    ਹਾਲਤ AV_PIX_FMT_NV24: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_P010:
    ਹਾਲਤ AV_PIX_FMT_P210:
    ਹਾਲਤ AV_PIX_FMT_P410: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ਨਿਰਾ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਹਾਲਤ AV_PIX_FMT_P012:
    ਹਾਲਤ AV_PIX_FMT_P016:
    ਹਾਲਤ AV_PIX_FMT_P212:
    ਹਾਲਤ AV_PIX_FMT_P216:
    ਹਾਲਤ AV_PIX_FMT_P412:
    ਹਾਲਤ AV_PIX_FMT_P416: {
        ਅਚਲ ਅੱਖਰ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        ਵਾਪਸ rep_tab[rep_fmt];
    };
    ਮੂਲ:
        ਵਾਪਸ "rgba32f";
    }
}

ਸਥਿਰ ਖਾਲੀ reset_imageviews(AVRefStructOpaque ਅਣਵਰਤਿਆ, ਖਾਲੀ *obj)
{
    FFVkImageViews *iv = obj;

    ਲਈ (ਪੂਰਨ i = 0; i < iv->nb_views; i++) {
        ਜੇ (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, ਆਕਾਰ(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ਪੂਰਨ nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    ਜੇ (!iv)
        ਵਾਪਸ ਨਿਰਾ;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    ਵਾਪਸ iv;
}

VkFormat ff_vk_map_fmt_ਮੰਜ਼ਿਲ_rep(VkFormat fmt, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt)
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REPS_FMT_PACK(fmt, ਅੰਕ) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## ਅੰਕ, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## ਅੰਕ, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## ਅੰਕ, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## ਅੰਕ,

    ਅਚਲ VkFormat fmts_map[][4] = {
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
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ REPS_FMT_PACK
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ REPS_FMT

    ਜੇ (fmt == VK_FORMAT_UNDEFINED)
        ਵਾਪਸ VK_FORMAT_UNDEFINED;

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        ਜੇ (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            ਵਾਪਸ fmts_map[i][rep_fmt];
    }

    ਵਾਪਸ VK_FORMAT_UNDEFINED;
}

ਪੂਰਨ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ਪੂਰਨ plane, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVVulkan_ਚੌਖਟੇ_Context *vkfc = hwfc->hwctx;
    ਅਚਲ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_ਅਗਲਾ      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_ਮੰਜ਼ਿਲ_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_ਪਛਾਣ_ਤੱਤ_map,
        .subresourceRange = {
            .aspect_ਨਕਾਬ = ff_vk_aspect_flag(f, plane),
            .level_ਗਿਣਤੀ = 1,
            .layer_ਗਿਣਤੀ = 1,
        },
    };
    ਜੇ (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_ਨਕਾਬ;

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ],
                                AVFrame *f,
                                ਅਚਲ VkFormat fmts[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ])
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVVulkan_ਚੌਖਟੇ_Context *vkfc = hwfc->hwctx;
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)f->ਅੰਕੜੇ[0];
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);
    ਅਚਲ ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };

    ਲਈ (ਪੂਰਨ i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_ਅਗਲਾ      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_ਪਛਾਣ_ਤੱਤ_map,
            .subresourceRange = {
                .aspect_ਨਕਾਬ = ff_vk_aspect_flag(f, i),
                .level_ਗਿਣਤੀ = 1,
                .layer_ਗਿਣਤੀ = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    ਲਈ (ਪੂਰਨ i = 0; i < nb_planes; i++)
        ff_vk_exec_ਜੋੜੋ_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(views, tmp_views, nb_planes*ਆਕਾਰ(*views));

    ਵਾਪਸ 0;

fail:
    ਲਈ (ਪੂਰਨ i = 0; i < nb_planes; i++)
        ਜੇ (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    ਵਾਪਸ err;
}

ਪੂਰਨ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ],
                            AVFrame *f, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    ਅਚਲ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ਅਚਲ ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    VkFormat fmts[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };

    ਲਈ (ਪੂਰਨ i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_ਮੰਜ਼ਿਲ_rep(rep_fmts[i], rep_fmt);
        ਜੇ (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਵਾਪਸ ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

ਖਾਲੀ ff_vk_ਚੌਖਟਾ_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 *bar, ਪੂਰਨ *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    ਪੂਰਨ ਮਿਲਿਆ = -1;
    AVVk_ਚੌਖਟਾ *vkf = (AVVk_ਚੌਖਟਾ *)pic->ਅੰਕੜੇ[0];
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(vkf);
    ਲਈ (ਪੂਰਨ i = 0; i < e->nb_ਚੌਖਟਾ_deps; i++)
        ਜੇ (e->ਚੌਖਟਾ_deps[i]->ਅੰਕੜੇ[0] == pic->ਅੰਕੜੇ[0]) {
            ਜੇ (e->ਚੌਖਟਾ_update[i])
                ਮਿਲਿਆ = i;
            ਰੋਕੋ;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ਸਮ੍ਰਿਤੀ_BARRIER_2,
            .p_ਅਗਲਾ = ਨਿਰਾ,
            .src_Stage_ਨਕਾਬ = src_stage,
            .dst_Stage_ਨਕਾਬ = dst_stage,
            .src_Access_ਨਕਾਬ = ਮਿਲਿਆ >= 0 ? e->access_dst[ਮਿਲਿਆ] : VK_ACCESS_2_NONE,
            .dst_Access_ਨਕਾਬ = new_access,
            .oldLayout = ਮਿਲਿਆ >= 0 ? e->layout_dst[ਮਿਲਿਆ] : vkf->layout[0],
            .newLayout = new_layout,
            .src_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = ਮਿਲਿਆ >= 0 ? e->ਕਤਾਰ_family_dst[ਮਿਲਿਆ] : vkf->ਕਤਾਰ_family[0],
            .dst_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_ਨਕਾਬ = VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ,
                .layer_ਗਿਣਤੀ = 1,
                .level_ਗਿਣਤੀ = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_ਚੌਖਟਾ(s, e, pic, &bar[*nb_bar - nb_images], ਨਿਰਾ);
}

ਪੂਰਨ ff_vk_shader_ਲੱਦੋ(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_ਮਾਪ[3], uint32_t required_subgroup_ਮਾਪ)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(shd->lg_ਮਾਪ, wg_ਮਾਪ, 3*ਆਕਾਰ(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_ਮਾਪ_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_ਮਾਪ_CREATE_INFO,
        .required_Subgroup_ਮਾਪ = required_subgroup_ਮਾਪ,
    };

    ਚੋਣ (shd->stage) {
    ਹਾਲਤ VK_SHADER_STAGE_ANY_ਪ੍ਰਾਪਤੀ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
    ਹਾਲਤ VK_SHADER_STAGE_CALLABLE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
    ਹਾਲਤ VK_SHADER_STAGE_CLOSEST_ਪ੍ਰਾਪਤੀ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
    ਹਾਲਤ VK_SHADER_STAGE_INTERSECTION_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
    ਹਾਲਤ VK_SHADER_STAGE_ਖੁੰਝ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
    ਹਾਲਤ VK_SHADER_STAGE_RAYGEN_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR:
        shd->bind_ਬਿੰਦੂ = VK_PIPELINE_BIND_ਬਿੰਦੂ_RAY_TRACING_KHR;
        ਰੋਕੋ;
    ਹਾਲਤ VK_SHADER_STAGE_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ:
        shd->bind_ਬਿੰਦੂ = VK_PIPELINE_BIND_ਬਿੰਦੂ_COMPUTE;
        ਰੋਕੋ;
    ਮੂਲ:
        shd->bind_ਬਿੰਦੂ = VK_PIPELINE_BIND_ਬਿੰਦੂ_GRAPHICS;
        ਰੋਕੋ;
    };

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_ਸੈੱਟ_Layouts            = shd->desc_layout,
        .ਸੈੱਟ_Layout_ਗਿਣਤੀ         = shd->nb_descriptor_sets,
        .ਧੱਕੋ_Constant_Range_ਗਿਣਤੀ = shd->ਧੱਕੋ_consts_ਅੰਕ,
        .p_ਧੱਕੋ_Constant_Ranges    = shd->ਧੱਕੋ_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ਅਚਲ uint8_t *spirv, size_t spirv_len)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_ਅਗਲਾ    = ਨਿਰਾ,
        .flags    = 0x0,
        .p_ਕੋਡ    = (ਖਾਲੀ *)spirv,
        .ਕੋਡ_ਮਾਪ = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ਅਚਲ ਅੱਖਰ *entrypoint)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_ਅਗਲਾ = shd->subgroup_info.required_Subgroup_ਮਾਪ ?
                     &shd->subgroup_info : ਨਿਰਾ,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_ਮਾਪ ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_ਭਰਿਆ_SUBGROUPS_ਦੋਆਧਾਰੀ_ਅੰਕ : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ਨਤੀਜਾ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ਪੂਰਨ has_singular = 0;
    ਪੂਰਨ max_descriptors = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_ਸੈੱਟ[i].nb_bindings);
        ਜੇ (shd->desc_ਸੈੱਟ[i].singular)
            has_singular = 1;
    }
    shd->use_ਧੱਕੋ = (s->extensions & FF_VK_EXT_ਧੱਕੋ_DESCRIPTOR) &&
                    (max_descriptors <= s->ਧੱਕੋ_desc_props.max_ਧੱਕੋ_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    ਲਈ (ਪੂਰਨ i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_ਸੈੱਟ *ਸੈੱਟ = &shd->desc_ਸੈੱਟ[i];
        Vk_Descriptor_ਸੈੱਟ_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_ਸੈੱਟ_LAYOUT_CREATE_INFO,
            .binding_ਗਿਣਤੀ = ਸੈੱਟ->nb_bindings,
            .pBindings = ਸੈੱਟ->binding,
            .flags = (shd->use_ਧੱਕੋ) ?
                     VK_DESCRIPTOR_ਸੈੱਟ_LAYOUT_CREATE_ਧੱਕੋ_DESCRIPTOR_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_ਸੈੱਟ_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ਅਚਲ ਅੱਖਰ *spirv, size_t spirv_len,
                      ਅਚਲ ਅੱਖਰ *entrypoint)
{
    ਪੂਰਨ err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_ਇੰਦਰਾਜ spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ਨਿਵੇਸ਼_ਮਾਪ = spirv_len;

    ਜੇ (shd->precompiled) {
        ਜੇ (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_ਇੰਦਰਾਜ_ਗਿਣਤੀ = 0,
                .p_ਅੰਕੜੇ = shd->lg_ਮਾਪ,
                .ਅੰਕੜੇ_ਮਾਪ_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_ਇੰਦਰਾਜ *spe = (ਖਾਲੀ *)shd->specialization_info->pMapEntries;
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_ਇੰਦਰਾਜ_ਗਿਣਤੀ++] = (Vk_Specialization_Map_ਇੰਦਰਾਜ) {
                .constantID = 253 + i,
                .ਵਿੱਥ = shd->specialization_info->ਅੰਕੜੇ_ਮਾਪ_2 + i*ਆਕਾਰ(uint32_t),
                .ਮਾਪ = ਆਕਾਰ(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_ਅੰਕੜੇ;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(&spd[shd->specialization_info->ਅੰਕੜੇ_ਮਾਪ_2],
               shd->lg_ਮਾਪ, 3*ਆਕਾਰ(uint32_t));
        shd->specialization_info->ਅੰਕੜੇ_ਮਾਪ_2 += 3*ਆਕਾਰ(uint32_t);

#ਜੇ CONFIG_SHADER_COMPRESSION
        uint8_t *ਬਾਹਰਲਾ;
        size_t ਬਾਹਰਲਾ_len;
        ਪੂਰਨ ret = ff_zlib_expand(s, &ਬਾਹਰਲਾ, &ਬਾਹਰਲਾ_len, spirv, spirv_len);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        spirv = ਬਾਹਰਲਾ;
        spirv_len = ਬਾਹਰਲਾ_len;
#ਜੇ_ਅੰਤ
    }

    err = init_descriptors(s, shd);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    err = init_pipeline_layout(s, shd);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    ਚੋਣ (shd->bind_ਬਿੰਦੂ) {
    ਹਾਲਤ VK_PIPELINE_BIND_ਬਿੰਦੂ_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        ਰੋਕੋ;
    ਮੂਲ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_ਬਿੰਦੂ);
        err = AVERROR(EINVAL);
        ਜਾਓ ਸਿਰਾ;
        ਰੋਕੋ;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    ਜੇ (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    ਨਹੀਂਤਾਂ
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    ਜੇ (ਨਿਵੇਸ਼_ਮਾਪ != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ਨਿਵੇਸ਼_ਮਾਪ);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

ਸਿਰਾ:
    ਜੇ (shd->precompiled) {
        shd->specialization_info->map_ਇੰਦਰਾਜ_ਗਿਣਤੀ -= 3;
        shd->specialization_info->ਅੰਕੜੇ_ਮਾਪ_2 -= 3*ਆਕਾਰ(uint32_t);
    }
#ਜੇ CONFIG_SHADER_COMPRESSION
    ਜੇ (shd->precompiled)
        av_free((ਖਾਲੀ *)spirv);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ err;
}

ਖਾਲੀ ff_vk_shader_ਜੋੜੋ_descriptor_ਸੈੱਟ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ਅਚਲ FFVulkan_Descriptor_ਸੈੱਟ_Binding *desc, ਪੂਰਨ nb,
                                     ਪੂਰਨ singular)
{
    FFVulkan_Descriptor_ਸੈੱਟ *ਸੈੱਟ = &shd->desc_ਸੈੱਟ[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    ਲਈ (ਪੂਰਨ i = 0; i < nb; i++) {
        ਸੈੱਟ->binding[i].binding            = i;
        ਸੈੱਟ->binding[i].descriptorType     = desc[i].type;
        ਸੈੱਟ->binding[i].descriptor_ਗਿਣਤੀ    = FFMAX(desc[i].elems, 1);
        ਸੈੱਟ->binding[i].stageFlags         = desc[i].stages;
        ਸੈੱਟ->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < nb; i++) {
        ਪੂਰਨ j;
        ਲਈ (j = 0; j < shd->nb_desc_pool_ਮਾਪ; j++)
            ਜੇ (shd->desc_pool_ਮਾਪ[j].type == desc[i].type)
                ਰੋਕੋ;
        ਜੇ (j >= shd->nb_desc_pool_ਮਾਪ) {
            shd->nb_desc_pool_ਮਾਪ++;
            av_assert1(shd->nb_desc_pool_ਮਾਪ < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_ਮਾਪ[j].type             = desc[i].type;
        shd->desc_pool_ਮਾਪ[j].descriptor_ਗਿਣਤੀ += FFMAX(desc[i].elems, 1);
    }

    ਸੈੱਟ->singular = singular;
    ਸੈੱਟ->nb_bindings = nb;
}

ਪੂਰਨ ff_vk_shader_ਰਜਿਸਟਰ_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    ਜੇ (!shd->nb_descriptor_sets)
        ਵਾਪਸ 0;

    FFVulkan_Shader_ਅੰਕੜੇ *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    ਜੇ (!shd->use_ਧੱਕੋ) {
        Vk_ਨਤੀਜਾ ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_ਸੈੱਟ_Layout *tmp_layouts;
        Vk_Descriptor_ਸੈੱਟ_Allocate_Info ਸੈੱਟ_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        ਲਈ (ਪੂਰਨ i = 0; i < shd->nb_desc_pool_ਮਾਪ; i++)
            shd->desc_pool_ਮਾਪ[i].descriptor_ਗਿਣਤੀ *= pool->pool_ਮਾਪ;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_ਮਾਪ,
            .pool_ਮਾਪ_ਗਿਣਤੀ = shd->nb_desc_pool_ਮਾਪ,
            .maxSets = sd->nb_descriptor_sets*pool->pool_ਮਾਪ,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, ਆਕਾਰ(*tmp_layouts));
        ਜੇ (!tmp_layouts)
            ਵਾਪਸ AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        ਲਈ (ਪੂਰਨ i = 0; i < pool->pool_ਮਾਪ; i++)
            ਲਈ (ਪੂਰਨ j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        ਸੈੱਟ_alloc_info = (Vk_Descriptor_ਸੈੱਟ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_ਸੈੱਟ_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_ਸੈੱਟ_Layouts        = tmp_layouts,
            .descriptor_ਸੈੱਟ_ਗਿਣਤੀ = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        ਆਕਾਰ(*tmp_layouts));
        ਜੇ (!sd->desc_sets) {
            av_free(tmp_layouts);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &ਸੈੱਟ_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਚਲ FFVulkan_Shader_ਅੰਕੜੇ *get_shd_ਅੰਕੜੇ(FFVkExecContext *e,
                                                     ਅਚਲ FFVulkanShader *shd)
{
    ਲਈ (ਪੂਰਨ i = 0; i < e->ਮਾਪਾ->nb_reg_shd; i++)
        ਜੇ (e->ਮਾਪਾ->reg_shd[i].shd == shd)
            ਵਾਪਸ &e->ਮਾਪਾ->reg_shd[i];
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ update_ਸੈੱਟ_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, ਪੂਰਨ ਸੈੱਟ,
                                         Vk_Write_Descriptor_ਸੈੱਟ *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_ਸੈੱਟ *desc_ਸੈੱਟ = &shd->desc_ਸੈੱਟ[ਸੈੱਟ];
    ਅਚਲ FFVulkan_Shader_ਅੰਕੜੇ *sd = get_shd_ਅੰਕੜੇ(e, shd);

    ਜੇ (desc_ਸੈੱਟ->singular) {
        ਲਈ (ਪੂਰਨ i = 0; i < e->ਮਾਪਾ->pool_ਮਾਪ; i++) {
            write_info->dst_ਸੈੱਟ = sd->desc_sets[i*sd->nb_descriptor_sets + ਸੈੱਟ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ਨਿਰਾ);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (shd->use_ਧੱਕੋ) {
            vk->Cmd_ਧੱਕੋ_Descriptor_ਸੈੱਟ_KHR(e->buf,
                                        shd->bind_ਬਿੰਦੂ,
                                        shd->pipeline_layout,
                                        ਸੈੱਟ, 1,
                                        write_info);
        } ਨਹੀਂਤਾਂ {
            write_info->dst_ਸੈੱਟ = sd->desc_sets[e->idx*sd->nb_descriptor_sets + ਸੈੱਟ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ਨਿਰਾ);
        }
    }
}

ਪੂਰਨ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ bind, ਪੂਰਨ offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_ਸੈੱਟ *desc_ਸੈੱਟ = &shd->desc_ਸੈੱਟ[ਸੈੱਟ];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_ਸੈੱਟ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_ਸੈੱਟ,
        .dstBinding = bind,
        .descriptor_ਗਿਣਤੀ = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_ਸੈੱਟ->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_ਸੈੱਟ_pool_write(s, e, shd, ਸੈੱਟ, &desc_pool_write_info);

    ਵਾਪਸ 0;
}

ਖਾਲੀ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    ਅਚਲ ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);

    ਲਈ (ਪੂਰਨ i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, ਸੈੱਟ, binding, i,
                                views[i], layout, sampler);
}

ਪੂਰਨ ff_vk_shader_update_desc_ਬਫਰ(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ bind, ਪੂਰਨ elem,
                                    FFVk_ਬਫਰ *buf, Vk_Device_ਮਾਪ ਵਿੱਥ, Vk_Device_ਮਾਪ len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_ਸੈੱਟ *desc_ਸੈੱਟ = &shd->desc_ਸੈੱਟ[ਸੈੱਟ];

    Vk_Descriptor_ਬਫਰ_Info desc_pool_write_info_buf = {
        .ਬਫਰ = buf->buf,
        .ਵਿੱਥ = buf->virtual_ਵਿੱਥ + ਵਿੱਥ,
        .range = len,
    };
    Vk_Write_Descriptor_ਸੈੱਟ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_ਸੈੱਟ,
        .dstBinding = bind,
        .descriptor_ਗਿਣਤੀ = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_ਸੈੱਟ->binding[bind].descriptorType,
        .p_ਬਫਰ_Info = &desc_pool_write_info_buf,
    };
    update_ਸੈੱਟ_pool_write(s, e, shd, ਸੈੱਟ, &desc_pool_write_info);

    ਵਾਪਸ 0;
}

ਖਾਲੀ ff_vk_shader_update_ਧੱਕੋ_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_ਬਿੱਟ stage,
                                    ਪੂਰਨ ਵਿੱਥ, size_t ਮਾਪ, ਖਾਲੀ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ਧੱਕੋ_Constants(e->buf, shd->pipeline_layout,
                         stage, ਵਿੱਥ, ਮਾਪ, src);
}

ਖਾਲੀ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ਅਚਲ FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ਅਚਲ FFVulkan_Shader_ਅੰਕੜੇ *sd = get_shd_ਅੰਕੜੇ(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_ਬਿੰਦੂ, shd->pipeline);

    ਜੇ (sd && sd->nb_descriptor_sets) {
        ਜੇ (!shd->use_ਧੱਕੋ) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_ਬਿੰਦੂ, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ਨਿਰਾ);
        }
    }
}

ਖਾਲੀ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#ਜੇ 0
    ਜੇ (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#ਜੇ_ਅੰਤ

    ਜੇ (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    ਜੇ (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    ਲਈ (ਪੂਰਨ i = 0; i < shd->nb_descriptor_sets; i++)
        ਜੇ (shd->desc_layout[i])
            vk->Destroy_Descriptor_ਸੈੱਟ_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

ਖਾਲੀ ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#ਜੇ_ਅੰਤ
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_ਬਫਰ_unref(&s->device_ref);
    av_ਬਫਰ_unref(&s->ਚੌਖਟੇ_ref);
}

ਪੂਰਨ ff_vk_init(FFVulkanContext *s, ਖਾਲੀ *log_ਮਾਪਾ,
               AVBufferRef *device_ref, AVBufferRef *ਚੌਖਟੇ_ref)
{
    ਪੂਰਨ err;

    ਸਥਿਰ ਅਚਲ AVClass vulkan_context_class = {
        .class_name       = "vk",
        .ਸੰਸਕਰਣ          = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
        .ਮਾਪਾ_log_context_ਵਿੱਥ = offsetof(FFVulkanContext, log_ਮਾਪਾ),
    };

    memset(s, 0, ਆਕਾਰ(*s));
    s->log_ਮਾਪਾ = log_ਮਾਪਾ;
    s->class      = &vulkan_context_class;

    ਜੇ (ਚੌਖਟੇ_ref) {
        s->ਚੌਖਟੇ_ref = av_ਬਫਰ_ref(ਚੌਖਟੇ_ref);
        ਜੇ (!s->ਚੌਖਟੇ_ref)
            ਵਾਪਸ AVERROR(ENOMEM);

        s->ਚੌਖਟੇ = (AVHWFramesContext *)s->ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
        s->hwfc = s->ਚੌਖਟੇ->hwctx;

        device_ref = s->ਚੌਖਟੇ->device_ref;
    }

    s->device_ref = av_ਬਫਰ_ref(device_ref);
    ਜੇ (!s->device_ref) {
        ff_vk_uninit(s);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->ਅੰਕੜੇ;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_ਮੰਜ਼ਿਲ_ਨਕਾਬ(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_ਮੰਜ਼ਿਲ_ਨਕਾਬ(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_ਲੱਦੋ_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    ਜੇ (err < 0) {
        ff_vk_uninit(s);
        ਵਾਪਸ err;
    }

    err = ff_vk_ਲੱਦੋ_props(s);
    ਜੇ (err < 0) {
        ff_vk_uninit(s);
        ਵਾਪਸ err;
    }

    ਵਾਪਸ 0;
}
