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

#ಆದರೆ CONFIG_SHADER_COMPRESSION
#ಅನ್ತರ್ಭಾವ "libavutil/zlib_utils.h"
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರಾಂಕ VkComponentMapping ff_comp_ತಟಸ್ಥ_map = {
    .r = VK_COMPONENT_SWIZZLE_ತಟಸ್ಥ,
    .g = VK_COMPONENT_SWIZZLE_ತಟಸ್ಥ,
    .b = VK_COMPONENT_SWIZZLE_ತಟಸ್ಥ,
    .a = VK_COMPONENT_SWIZZLE_ತಟಸ್ಥ,
};

/* Converts return values to strings */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ff_vk_ret2str(Vk_ಫಲಿತಾಂಶ res)
{
#ವ್ಯಾಖ್ಯಾನಿಸು CASE(VAL) ಸ್ಥಿತಿ VAL: ಹಿಂತಿರುಗಿ #VAL
    ಆಯ್ಕೆ (res) {
    CASE(VK_SUCCESS);
    CASE(VK_NOT_READY);
    CASE(VK_TIMEOUT);
    CASE(VK_EVENT_ಗಣ);
    CASE(VK_EVENT_RESET);
    CASE(VK_INCOMPLETE);
    CASE(VK_ERROR_ಹೊರಹೋಗು_ದ_HOST_ಸ್ಮರಣೆ);
    CASE(VK_ERROR_ಹೊರಹೋಗು_ದ_DEVICE_ಸ್ಮರಣೆ);
    CASE(VK_ERROR_INITIALIZATION_FAILED);
    CASE(VK_ERROR_DEVICE_ಕಳೆದುಹೋದ);
    CASE(VK_ERROR_ಸ್ಮರಣೆ_MAP_FAILED);
    CASE(VK_ERROR_LAYER_NOT_PRESENT);
    CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
    CASE(VK_ERROR_FEATURE_NOT_PRESENT);
    CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
    CASE(VK_ERROR_TOO_MANY_OBJECTS);
    CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
    CASE(VK_ERROR_FRAGMENTED_POOL);
    CASE(VK_ERROR_UNKNOWN);
    CASE(VK_ERROR_ಹೊರಹೋಗು_ದ_POOL_ಸ್ಮರಣೆ);
    CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
    CASE(VK_ERROR_FRAGMENTATION);
    CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_ವಿಳಾಸ);
    CASE(VK_PIPELINE_COMPILE_REQUIRED);
    CASE(VK_ERROR_SURFACE_ಕಳೆದುಹೋದ_KHR);
    CASE(VK_ERROR_NATIVE_ಕಿಟಕಿ_ಒಳ_USE_KHR);
    CASE(VK_SUBOPTIMAL_KHR);
    CASE(VK_ERROR_ಹೊರಹೋಗು_ದ_DATE_KHR);
    CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
    CASE(VK_ERROR_VALIDATION_FAILED_EXT);
    CASE(VK_ERROR_INVALID_SHADER_NV);
    CASE(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_VIDEO_STD_ಆವೃತ್ತಿ_NOT_SUPPORTED_KHR);
    CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
    CASE(VK_ERROR_NOT_PERMITTED_KHR);
    CASE(VK_ERROR_ತುಂಬಿದ_SCREEN_EXCLUSIVE_ಬಹುಲಕ_ಕಳೆದುಹೋದ_EXT);
    CASE(VK_THREAD_IDLE_KHR);
    CASE(VK_THREAD_ಮುಗಿದ_KHR);
    CASE(VK_OPERATION_DEFERRED_KHR);
    CASE(VK_OPERATION_NOT_DEFERRED_KHR);
    ಪೂರ್ವನಿಯೋಜಿತ: ಹಿಂತಿರುಗಿ "Unknown error";
    }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CASE
}

/* Malitia pura, Khronos */
#ವ್ಯಾಖ್ಯಾನಿಸು FN_MAP_ಗಮ್ಯ(dst_t, dst_name, src_t, src_name)                                 \
    dst_t ff_vk_map_ ##src_name## ಗಮ್ಯ_2 ##dst_name(src_t src) \
    {                                                                   \
        dst_t dst = 0x0;                                                \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ಬಿಟ್,                   \
               VK_IMAGE_USAGE_SAMPLED_ಬಿಟ್);                             \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_TRANSFER_SRC_ಬಿಟ್,                    \
               VK_IMAGE_USAGE_TRANSFER_SRC_ಬಿಟ್);                        \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_TRANSFER_DST_ಬಿಟ್,                    \
               VK_IMAGE_USAGE_TRANSFER_DST_ಬಿಟ್);                        \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ಬಿಟ್,                   \
               VK_IMAGE_USAGE_STORAGE_ಬಿಟ್);                             \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_ಬಿಟ್,                \
               VK_IMAGE_USAGE_COLOR_ATTACHMENT_ಬಿಟ್);                    \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_VIDEO_DECODE_OUTPUT_ಬಿಟ್_KHR,         \
               VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR);                \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_VIDEO_DECODE_DPB_ಬಿಟ್_KHR,            \
               VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ಬಿಟ್_KHR);                \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_DPB_ಬಿಟ್_KHR,            \
               VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ಬಿಟ್_KHR);                \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_VIDEO_ENCODE_ಒಳಹರಿವು_ಬಿಟ್_KHR,          \
               VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR);                \
        MAP_ಗಮ್ಯ(VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_ಬಿಟ್_EXT,         \
               VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT);                   \
        ಹಿಂತಿರುಗಿ dst;                                                     \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು MAP_ಗಮ್ಯ(flag1, flag2) ಆದರೆ (src & flag2) dst |= flag1;
FN_MAP_ಗಮ್ಯ(VkFormatFeatureFlagBits2, feats, VkImageUsageFlags, usage)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAP_ಗಮ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು MAP_ಗಮ್ಯ(flag1, flag2) ಆದರೆ (src & flag1) dst |= flag2;
FN_MAP_ಗಮ್ಯ(VkImageUsageFlags, usage, VkFormatFeatureFlagBits2, feats)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MAP_ಗಮ್ಯ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು FN_MAP_ಗಮ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ ತುಂಬು_enabled_qfs(FFVulkanContext *s)
{
    s->nb_qfs = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->hwctx->nb_qf; i++) {
        /* Skip duplicates */
        ಪೂರ್ಣಾಂಕ skip = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < s->nb_qfs; j++) {
            ಆದರೆ (s->qfs[j] == s->hwctx->qf[i].idx) {
                skip = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (skip)
            ಮುಂದುವರಿ;

        s->qfs[s->nb_qfs++] = s->hwctx->qf[i].idx;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_imageviews(AVRefStructOpaque ಬಳಸದ, ಶೂನ್ಯ *obj);

ಪೂರ್ಣಾಂಕ ff_vk_ತುಂಬು_props(FFVulkanContext *s)
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
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_ಗಾತ್ರ_CONTROL_PROPERTIES);

    FF_VK_STRUCT_EXT(s, &s->props, &s->ತಳ್ಳು_desc_props, FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ತಳ್ಳು_DESCRIPTOR_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->hprops, FF_VK_EXT_EXTERNAL_HOST_ಸ್ಮರಣೆ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_ಸ್ಮರಣೆ_HOST_PROPERTIES_EXT);
    FF_VK_STRUCT_EXT(s, &s->props, &s->coop_ಮಾತೃಕೆ_props, FF_VK_EXT_COOP_ಮಾತೃಕೆ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ಮಾತೃಕೆ_PROPERTIES_KHR);
    FF_VK_STRUCT_EXT(s, &s->props, &s->optical_flow_props, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV);
    FF_VK_STRUCT_EXT(s, &s->props, &s->host_image_props, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES_EXT);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    FF_VK_STRUCT_EXT(s, &s->props, &s->long_ಸದಿಶ_props, FF_VK_EXT_LONG_ಸದಿಶ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ಸದಿಶ_PROPERTIES_EXT);
#ಆದರೆ_ಅಂತ್ಯ

    s->feats = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &s->feats, &s->feats_12, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &s->feats, &s->atomic_float_feats, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &s->feats, &s->unified_layout_feats, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &s->feats, &s->maintenance_11_feats, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!s->imageviews_pool) {
        s->imageviews_pool = av_refstruct_pool_alloc_ext(ಗಾತ್ರ(FFVkImageViews), 0,
                                                         ಖಾಲಿ, ಖಾಲಿ, reset_imageviews,
                                                         ಖಾಲಿ, ಖಾಲಿ);
        ಆದರೆ (!s->imageviews_pool)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    /* Try allocating 1024 layouts */
    s->host_image_copy_layouts = av_malloc(ಗಾತ್ರ(*s->host_image_copy_layouts)*1024);
    s->host_image_props.pCopySrcLayouts = s->host_image_copy_layouts;
    s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ = 512;
    s->host_image_props.pCopyDstLayouts = s->host_image_copy_layouts + 512;
    s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ = 512;

    vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

    /* Check if we had enough memory for all layouts */
    ಆದರೆ (s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ == 512 ||
        s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ == 512) {
        VkImageLayout *new_array;
        size_t new_ಗಾತ್ರ;
        s->host_image_props.pCopySrcLayouts =
        s->host_image_props.pCopyDstLayouts = ಖಾಲಿ;
        s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ =
        s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ = 0;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);

        new_ಗಾತ್ರ = s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ +
                   s->host_image_props.copy_Dst_Layout_ಎಣಿಕೆ;
        new_ಗಾತ್ರ *= ಗಾತ್ರ(*s->host_image_copy_layouts);
        new_array = av_realloc(s->host_image_copy_layouts, new_ಗಾತ್ರ);
        ಆದರೆ (!new_array)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        s->host_image_copy_layouts = new_array;
        s->host_image_props.pCopySrcLayouts = new_array;
        s->host_image_props.pCopyDstLayouts = new_array + s->host_image_props.copy_Src_Layout_ಎಣಿಕೆ;
        vk->GetPhysicalDeviceProperties2(s->hwctx->phys_dev, &s->props);
    }

    vk->Get_Physical_Device_ಸ್ಮರಣೆ_Properties(s->hwctx->phys_dev, &s->mprops);
    vk->GetPhysicalDeviceFeatures2(s->hwctx->phys_dev, &s->feats);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ; i++)
        s->host_cached_flag |= s->mprops.ಸ್ಮರಣೆ_Types[i].propertyFlags &
                               VK_ಸ್ಮರಣೆ_PROPERTY_HOST_CACHED_ಬಿಟ್;

    ತುಂಬು_enabled_qfs(s);

    ಆದರೆ (s->qf_props)
        ಹಿಂತಿರುಗಿ 0;

    vk->Get_Physical_Device_ಸರತಿ_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, ಖಾಲಿ);

    s->qf_props = av_calloc(s->tot_nb_qfs, ಗಾತ್ರ(*s->qf_props));
    ಆದರೆ (!s->qf_props)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    s->query_props = av_calloc(s->tot_nb_qfs, ಗಾತ್ರ(*s->query_props));
    ಆದರೆ (!s->qf_props) {
        av_freep(&s->qf_props);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    s->video_props = av_calloc(s->tot_nb_qfs, ಗಾತ್ರ(*s->video_props));
    ಆದರೆ (!s->video_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    s->ownership_props = av_calloc(s->tot_nb_qfs, ಗಾತ್ರ(*s->ownership_props));
    ಆದರೆ (!s->ownership_props) {
        av_freep(&s->qf_props);
        av_freep(&s->query_props);
        av_freep(&s->video_props);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಗಾಗಿ (uint32_t i = 0; i < s->tot_nb_qfs; i++) {
        s->qf_props[i] = (Vk_ಸರತಿ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_PROPERTIES_2,
        };

        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->query_props[i], FF_VK_EXT_VIDEO_ಸರತಿ,
                         VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_QUERY_ಫಲಿತಾಂಶ_ಸ್ಥಿತಿ_PROPERTIES_KHR);
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->video_props[i], FF_VK_EXT_VIDEO_ಸರತಿ,
                         VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_VIDEO_PROPERTIES_KHR);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
        FF_VK_STRUCT_EXT(s, &s->qf_props[i], &s->ownership_props[i], FF_VK_EXT_MAINTENANCE_9,
                         VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
    }

    vk->Get_Physical_Device_ಸರತಿ_Family_Properties2(s->hwctx->phys_dev, &s->tot_nb_qfs, s->qf_props);

    ಆದರೆ (s->extensions & FF_VK_EXT_COOP_ಮಾತೃಕೆ) {
        vk->Get_Physical_Device_Cooperative_ಮಾತೃಕೆ_Properties_KHR(s->hwctx->phys_dev,
                                                            &s->coop_mat_props_nb, ಖಾಲಿ);

        ಆದರೆ (s->coop_mat_props_nb) {
            s->coop_mat_props = av_malloc_array(s->coop_mat_props_nb,
                                                ಗಾತ್ರ(Vk_Cooperative_ಮಾತೃಕೆ_Properties_KHR));
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->coop_mat_props_nb; i++) {
                s->coop_mat_props[i] = (Vk_Cooperative_ಮಾತೃಕೆ_Properties_KHR) {
                    .sType = VK_STRUCTURE_TYPE_COOPERATIVE_ಮಾತೃಕೆ_PROPERTIES_KHR,
                };
            }

            vk->Get_Physical_Device_Cooperative_ಮಾತೃಕೆ_Properties_KHR(s->hwctx->phys_dev,
                                                                &s->coop_mat_props_nb,
                                                                s->coop_mat_props);
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

AVVulkan_Device_ಸರತಿ_Family *ff_vk_qf_ಕಂಡುಹಿಡಿ(FFVulkanContext *s,
                                         Vk_ಸರತಿ_Flag_ಬಿಟ್ಟುಗಳು dev_family,
                                         Vk_Video_Codec_Operation_Flag_ಬಿಟ್ಟುಗಳು_KHR vid_ops)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->hwctx->nb_qf; i++) {
        ಆದರೆ ((s->hwctx->qf[i].flags & dev_family) &&
            (s->hwctx->qf[i].video_caps & vid_ops) == vid_ops) {
            ಹಿಂತಿರುಗಿ &s->hwctx->qf[i];
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e);

ಶೂನ್ಯ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++) {
        FFVkExecContext *e = &pool->contexts[i];

        ಆದರೆ (e->sem) {
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
        pthread_mutex_destroy(&e->ಬೀಗ_2);
    }

    /* Free shader-specific data */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->nb_reg_shd; i++) {
        FFVulkan_Shader_ದತ್ತಾಂಶ *sd = &pool->reg_shd[i];

        ಆದರೆ (sd->desc_pool)
            vk->DestroyDescriptorPool(s->hwctx->act_dev, sd->desc_pool,
                                      s->hwctx->alloc);

        av_freep(&sd->desc_sets);
    }
    pool->nb_reg_shd = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++) {
        ಆದರೆ (pool->cmd_buf_pools[i])
            vk->FreeCommandBuffers(s->hwctx->act_dev, pool->cmd_buf_pools[i],
                                   1, &pool->cmd_bufs[i]);

        ಆದರೆ (pool->cmd_buf_pools[i])
            vk->DestroyCommandPool(s->hwctx->act_dev, pool->cmd_buf_pools[i], s->hwctx->alloc);
    }
    ಆದರೆ (pool->query_pool)
        vk->DestroyQueryPool(s->hwctx->act_dev, pool->query_pool, s->hwctx->alloc);

    av_free(pool->query_ದತ್ತಾಂಶ);
    av_free(pool->cmd_buf_pools);
    av_free(pool->cmd_bufs);
    av_free(pool->contexts);
    pool->pool_ಗಾತ್ರ = 0;
}

/* Per-family, per-library queue selection phases; each library links its own
 * copy, and pools which benefit from spreading are created by the same one */
ಸ್ಥಿರ atomic_uint exec_pool_phase[FF_ARRAY_ELEMS(((AVVulkanDeviceContext *)ಖಾಲಿ)->qf)];
ಸ್ಥಿರ AVOnce exec_pool_phase_seeded = AV_ONCE_INIT;

ಸ್ಥಿರ ಶೂನ್ಯ exec_pool_phase_ಬೀಜ(ಶೂನ್ಯ)
{
    uint32_t ಬೀಜ = av_get_random_ಬೀಜ();
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(exec_pool_phase); i++)
        atomic_store_explicit(&exec_pool_phase[i], ಬೀಜ, memory_order_relaxed);
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_ಸರತಿ_Family *qf,
                         FFVkExecPool *pool, ಪೂರ್ಣಾಂಕ nb_contexts,
                         ಪೂರ್ಣಾಂಕ nb_queries, VkQueryType query_type, ಪೂರ್ಣಾಂಕ query_64bit,
                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *query_create_pnext)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkCommandPoolCreateInfo cqueue_create;
    Vk_Command_ಬಫರ್_Allocate_Info cbuf_create;

    ಸ್ಥಿರಾಂಕ VkQueryPoolVideoEncodeFeedbackCreateInfoKHR *ef = ಖಾಲಿ;

    atomic_init(&pool->idx, 0);

    ಆದರೆ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
        ef = ff_vk_ಕಂಡುಹಿಡಿ_struct(query_create_pnext,
                               VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR);
        ಆದರೆ (!ef)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    /* Allocate space for command buffer pools */
    pool->cmd_buf_pools = av_malloc(nb_contexts*ಗಾತ್ರ(*pool->cmd_buf_pools));
    ಆದರೆ (!pool->cmd_buf_pools) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    /* Allocate space for command buffers */
    pool->cmd_bufs = av_malloc(nb_contexts*ಗಾತ್ರ(*pool->cmd_bufs));
    ಆದರೆ (!pool->cmd_bufs) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_contexts; i++) {
        /* Create command pool */
        cqueue_create = (VkCommandPoolCreateInfo) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags              = VK_COMMAND_POOL_CREATE_TRANSIENT_ಬಿಟ್ |
                                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_ಬಫರ್_ಬಿಟ್,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ   = qf->idx,
        };

        ret = vk->CreateCommandPool(s->hwctx->act_dev, &cqueue_create,
                                    s->hwctx->alloc, &pool->cmd_buf_pools[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command pool creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }

        /* Allocate command buffer */
        cbuf_create = (Vk_Command_ಬಫರ್_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_ಬಫರ್_ALLOCATE_INFO,
            .level              = VK_COMMAND_ಬಫರ್_LEVEL_PRIMARY,
            .commandPool        = pool->cmd_buf_pools[i],
            .command_ಬಫರ್_ಎಣಿಕೆ = 1,
        };
        ret = vk->AllocateCommandBuffers(s->hwctx->act_dev, &cbuf_create,
                                         &pool->cmd_bufs[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Command buffer alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }
    }

    /* Query pool */
    ಆದರೆ (nb_queries) {
        VkQueryPoolCreateInfo query_pool_info = {
            .sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            .p_ಮುಂದಿನ = query_create_pnext,
            .queryType = query_type,
            .query_ಎಣಿಕೆ = nb_queries*nb_contexts,
        };
        ret = vk->CreateQueryPool(s->hwctx->act_dev, &query_pool_info,
                                  s->hwctx->alloc, &pool->query_pool);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Query pool alloc failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }

        pool->nb_queries = nb_queries;
        pool->query_ಸ್ಥಿತಿ_stride = 1 + 1; /* One result, one status by default */
        pool->query_results = nb_queries;
        pool->query_statuses = nb_queries;

        /* Video encode queries produce two results per query */
        ಆದರೆ (query_type == VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR) {
            ಪೂರ್ಣಾಂಕ nb_results = av_popcount(ef->encodeFeedbackFlags);
            pool->query_ಸ್ಥಿತಿ_stride = nb_results + 1;
            pool->query_results *= nb_results;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (query_type == VK_QUERY_TYPE_ಫಲಿತಾಂಶ_ಸ್ಥಿತಿ_ONLY_KHR) {
            pool->query_ಸ್ಥಿತಿ_stride = 1;
            pool->query_results = 0;
        }

        pool->qd_ಗಾತ್ರ = (pool->query_results + pool->query_statuses)*(query_64bit ? 8 : 4);

        /* Allocate space for the query data */
        pool->query_ದತ್ತಾಂಶ = av_calloc(nb_contexts, pool->qd_ಗಾತ್ರ);
        ಆದರೆ (!pool->query_ದತ್ತಾಂಶ) {
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }

    /* Allocate space for the contexts */
    pool->contexts = av_calloc(nb_contexts, ಗಾತ್ರ(*pool->contexts));
    ಆದರೆ (!pool->contexts) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    pool->pool_ಗಾತ್ರ = nb_contexts;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++)
        pthread_mutex_init(&pool->contexts[i].ಬೀಗ_2, ಖಾಲಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    /* Check if the extension and its flag are actually enabled */
    ಪೂರ್ಣಾಂಕ ಆಂತರಿಕ_ಸರತಿ_sync = 0;
    ಆದರೆ (s->extensions & FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC) {
        ಸ್ಥಿರಾಂಕ VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR *iqs;
        iqs = ff_vk_ಕಂಡುಹಿಡಿ_struct(s->hwctx->device_features.p_ಮುಂದಿನ,
                                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
        ಆಂತರಿಕ_ಸರತಿ_sync = iqs && iqs->internallySynchronizedQueues;
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* Video pools are pinned to the phase-picked queue (sessions order their
     * execution anyway); all other pools rotate starting from it, so pools
     * advancing in lockstep do not collide. */
    av_assert1(qf->idx < FF_ARRAY_ELEMS(exec_pool_phase));
    ff_thread_once(&exec_pool_phase_seeded, exec_pool_phase_ಬೀಜ);
    uint32_t phase = atomic_fetch_add(&exec_pool_phase[qf->idx], 1);
    ಪೂರ್ಣಾಂಕ pin_ಸರತಿ = qf->flags & (VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR |
                                 VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR);

    /* Init contexts */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++) {
        FFVkExecContext *e = &pool->contexts[i];
        VkSemaphoreTypeCreateInfo sem_type = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ಮುಂದಿನ = &sem_type,
        };

        /* Timeline semaphore carrying the busy state */
        ret = vk->CreateSemaphore(s->hwctx->act_dev, &sem_create, s->hwctx->alloc,
                                  &e->sem);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create submission semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        e->idx = i;
        e->ಪೋಷಕ = pool;

        /* Query data */
        e->query_ದತ್ತಾಂಶ = ((uint8_t *)pool->query_ದತ್ತಾಂಶ) + pool->qd_ಗಾತ್ರ*i;
        e->query_idx = nb_queries*i;

        /* Command buffer */
        e->buf = pool->cmd_bufs[i];

        /* Queue index distribution */
        e->qi = pin_ಸರತಿ ? phase % qf->ಅಂಕೆ : (i + phase) % qf->ಅಂಕೆ;
        e->qf = qf->idx;
        Vk_Device_ಸರತಿ_Info2 qinfo = {
            .sType            = VK_STRUCTURE_TYPE_DEVICE_ಸರತಿ_INFO_2,
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
            .flags            = ಆಂತರಿಕ_ಸರತಿ_sync ?
                                VK_DEVICE_ಸರತಿ_CREATE_INTERNALLY_SYNCHRONIZED_ಬಿಟ್_KHR : 0,
#ಆದರೆ_ಅಂತ್ಯ
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = qf->idx,
            .ಸರತಿ_ಸೂಚ್ಯಂಕ       = e->qi,
        };
        vk->GetDeviceQueue2(s->hwctx->act_dev, &qinfo, &e->ಸರತಿ);
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ff_vk_exec_pool_free(s, pool);
    ಹಿಂತಿರುಗಿ err;
}

Vk_ಫಲಿತಾಂಶ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ಶೂನ್ಯ **ದತ್ತಾಂಶ, Vk_Query_ಫಲಿತಾಂಶ_Flag_ಬಿಟ್ಟುಗಳು flags)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ಸ್ಥಿರಾಂಕ FFVkExecPool *pool = e->ಪೋಷಕ;
    Vk_Query_ಫಲಿತಾಂಶ_Flags qf = flags & ~(VK_QUERY_ಫಲಿತಾಂಶ_64_ಬಿಟ್ |
                                      VK_QUERY_ಫಲಿತಾಂಶ_WITH_ಸ್ಥಿತಿ_ಬಿಟ್_KHR);

    ಆದರೆ (!e->query_ದತ್ತಾಂಶ) {
        av_log(s, AV_LOG_ERROR, "Requested a query with a NULL query_data pointer!\n");
        ಹಿಂತಿರುಗಿ VK_INCOMPLETE;
    }

    qf |= pool->query_64bit ?
          VK_QUERY_ಫಲಿತಾಂಶ_64_ಬಿಟ್ : 0x0;
    qf |= pool->query_statuses ?
          VK_QUERY_ಫಲಿತಾಂಶ_WITH_ಸ್ಥಿತಿ_ಬಿಟ್_KHR : 0x0;

    ಆದರೆ (ದತ್ತಾಂಶ)
        *ದತ್ತಾಂಶ = e->query_ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ vk->GetQueryPoolResults(s->hwctx->act_dev, pool->query_pool,
                                   e->query_idx,
                                   pool->nb_queries,
                                   pool->qd_ಗಾತ್ರ, e->query_ದತ್ತಾಂಶ,
                                   pool->qd_ಗಾತ್ರ, qf);
}

FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool)
{
    FFVulkanFunctions *vk = &s->vkfn;

    /* Release the dependencies of every completed context, rather than leaving them held until reuse */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++) {
        uint64_t sem_val;
        FFVkExecContext *e = &pool->contexts[i];
        ಆದರೆ (pthread_mutex_trylock(&e->ಬೀಗ_2))
            ಮುಂದುವರಿ; /* In use by a recording or submitting thread */
        /* Busy contexts (counter below sem_value) are claimed or executing:
         * their dependency lists are off-limits */
        ಆದರೆ (vk->Get_Semaphore_Counter_ಮೌಲ್ಯ(s->hwctx->act_dev, e->sem, &sem_val) == VK_SUCCESS &&
            sem_val >= e->sem_ಮೌಲ್ಯ &&
            (e->nb_buf_deps || e->nb_refstruct_deps || e->nb_obj_deps ||
             e->nb_ಚೌಕಟ್ಟು_deps || e->nb_sw_ಚೌಕಟ್ಟು_deps))
            exec_discard_deps(s, e);
        pthread_mutex_unlock(&e->ಬೀಗ_2);
    }

    ಹಿಂತಿರುಗಿ &pool->contexts[atomic_fetch_add(&pool->idx, 1) % pool->pool_ಗಾತ್ರ];
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
    pthread_mutex_ಬೀಗ(&e->ಬೀಗ_2);
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);
    exec_discard_deps(s, e);
    pthread_mutex_unlock(&e->ಬೀಗ_2);
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_ಆರಂಭ(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    ಸ್ಥಿರಾಂಕ FFVkExecPool *pool = e->ಪೋಷಕ;

    Vk_Command_ಬಫರ್_Begin_Info cmd_ಆರಂಭ = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_ಬಫರ್_BEGIN_INFO,
        .flags = VK_COMMAND_ಬಫರ್_USAGE_ONE_ಸಮಯ_SUBMIT_ಬಿಟ್,
    };
    VkSemaphoreWaitInfo sem_wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphore_ಎಣಿಕೆ = 1,
        .pSemaphores = &e->sem,
        .p_ಮೌಲ್ಯಗಳು = &e->sem_ಮೌಲ್ಯ,
    };

    pthread_mutex_ಬೀಗ(&e->ಬೀಗ_2);

    /* Wait out the context's previous execution */
    vk->WaitSemaphores(s->hwctx->act_dev, &sem_wait_info, UINT64_MAX);

    /* Discard queue dependencies */
    exec_discard_deps(s, e);

    ret = vk->Begin_Command_ಬಫರ್(e->buf, &cmd_ಆರಂಭ);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to start command recoding: %s\n",
               ff_vk_ret2str(ret));
        pthread_mutex_unlock(&e->ಬೀಗ_2);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಆದರೆ (pool->nb_queries)
        vk->CmdResetQueryPool(e->buf, pool->query_pool,
                              e->query_idx, pool->nb_queries);

    /* Claim: the semaphore stays below this value until submission completes
     * or the recording is discarded, keeping every other user away */
    e->sem_ಮೌಲ್ಯ++;
    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = e->sem,
        .ಮೌಲ್ಯ = e->sem_ಮೌಲ್ಯ,
        .stage_ಮುಖವಾಡ = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
    };

    pthread_mutex_unlock(&e->ಬೀಗ_2);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ exec_discard_deps(FFVulkanContext *s, FFVkExecContext *e)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_buf_deps; j++)
        av_ಬಫರ್_unref(&e->buf_deps[j]);
    e->nb_buf_deps = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_refstruct_deps; j++)
        av_refstruct_unref(&e->refstruct_deps[j]);
    e->nb_refstruct_deps = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_obj_deps; j++) {
        FFVkExecObjDep *od = &e->obj_deps[j];
        ಆಯ್ಕೆ (od->type) {
        ಸ್ಥಿತಿ VK_OBJECT_TYPE_IMAGE_VIEW:
            vk->DestroyImageView(s->hwctx->act_dev,
                                 (VkImageView)od->obj, s->hwctx->alloc);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ VK_OBJECT_TYPE_SEMAPHORE:
            vk->DestroySemaphore(s->hwctx->act_dev,
                                 (VkSemaphore)od->obj, s->hwctx->alloc);
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            av_assert1(0);
        }
    }
    e->nb_obj_deps = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_sw_ಚೌಕಟ್ಟು_deps; j++)
        av_ಚೌಕಟ್ಟು_free(&e->sw_ಚೌಕಟ್ಟು_deps[j]);
    e->nb_sw_ಚೌಕಟ್ಟು_deps = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_ಚೌಕಟ್ಟು_deps; j++) {
        AVFrame *f = e->ಚೌಕಟ್ಟು_deps[j];
        ಆದರೆ (e->ಚೌಕಟ್ಟು_locked[j]) {
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
            AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *vkfc = hwfc->hwctx;
            AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];
            vkfc->unlock_ಚೌಕಟ್ಟು(hwfc, vkf);
            e->ಚೌಕಟ್ಟು_locked[j] = 0;
        }
        e->ಚೌಕಟ್ಟು_update[j] = 0;
    }
    e->nb_ಚೌಕಟ್ಟು_deps = 0;

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
    vk->Reset_Command_ಬಫರ್(e->buf, 0);
    vk->SignalSemaphore(s->hwctx->act_dev, &sig_info);
}

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
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

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->nb_refstruct_deps; i++) {
        ಆದರೆ (e->refstruct_deps[i] == *ptr) {
            av_refstruct_unref(obj);
            ಹಿಂತಿರುಗಿ;
        }
    }

    e->refstruct_deps[e->nb_refstruct_deps++] = *ptr;
    *ptr = ಖಾಲಿ;
}

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj)
{
    av_assert1(e->nb_obj_deps < FF_VK_EXEC_MAX_BUF_DEPS);
    e->obj_deps[e->nb_obj_deps++] = (FFVkExecObjDep) { obj, type };
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_ಕೂಡಿಸು_dep_sw_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f)
{
    av_assert1(e->nb_sw_ಚೌಕಟ್ಟು_deps < FF_VK_EXEC_MAX_SW_ಚೌಕಟ್ಟು_DEPS);

    e->sw_ಚೌಕಟ್ಟು_deps[e->nb_sw_ಚೌಕಟ್ಟು_deps] = av_ಚೌಕಟ್ಟು_clone(f);
    ಆದರೆ (!e->sw_ಚೌಕಟ್ಟು_deps[e->nb_sw_ಚೌಕಟ್ಟು_deps])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    e->nb_sw_ಚೌಕಟ್ಟು_deps++;

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_wait_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ಮೌಲ್ಯ = val,
        .stage_ಮುಖವಾಡ = stage,
    };
}

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage)
{
    av_assert1(e->sem_sig_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sem,
        .ಮೌಲ್ಯ = val,
        .stage_ಮುಖವಾಡ = stage,
    };
}

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ಪೂರ್ಣಾಂಕ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ಪೂರ್ಣಾಂಕ wait)
{
    /* Do not transfer ownership if we're signalling a binary semaphore,
     * since we're probably exporting it. */
    ಆದರೆ (!wait) {
        av_assert1((e->sem_sig_cnt + nb) <= FF_VK_EXEC_MAX_SEM_OPS);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb; i++) {
            e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                .semaphore = sem[i],
                .stage_ಮುಖವಾಡ = stage,
            };
        }

        ಹಿಂತಿರುಗಿ;
    }

    /* Ownership of each semaphore passes to the execution */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb; i++) {
        ff_vk_exec_ಕೂಡಿಸು_dep_obj(s, e, VK_OBJECT_TYPE_SEMAPHORE,
                               (uint64_t)sem[i]);
        ff_vk_exec_ಕೂಡಿಸು_dep_wait_sem(s, e, sem[i], 0, stage);
    }
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_ಕೂಡಿಸು_dep_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *vkfc = hwfc->hwctx;
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];
    ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);

    /* Don't add duplicates */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->nb_ಚೌಕಟ್ಟು_deps; i++)
        ಆದರೆ (e->ಚೌಕಟ್ಟು_deps[i]->ದತ್ತಾಂಶ[0] == f->ದತ್ತಾಂಶ[0])
            ಹಿಂತಿರುಗಿ 1;

    av_assert1(e->nb_ಚೌಕಟ್ಟು_deps < FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS);
    av_assert1((e->sem_wait_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);
    av_assert1((e->sem_sig_cnt + nb_images) <= FF_VK_EXEC_MAX_SEM_OPS);

    /* prepare_frame in hwcontext_vulkan.c uses the regular frame management
     * code but has no frame yet, and it doesn't need to actually store a ref
     * to the frame. */
    ಆದರೆ (f->buf[0]) {
        av_assert1(e->nb_buf_deps < FF_VK_EXEC_MAX_BUF_DEPS);
        e->buf_deps[e->nb_buf_deps] = av_ಬಫರ್_ref(f->buf[0]);
        ಆದರೆ (!e->buf_deps[e->nb_buf_deps])
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        e->nb_buf_deps++;
    }

    e->ಚೌಕಟ್ಟು_deps[e->nb_ಚೌಕಟ್ಟು_deps] = f;

    vkfc->ಬೀಗ_ಚೌಕಟ್ಟು(hwfc, vkf);
    e->ಚೌಕಟ್ಟು_locked[e->nb_ಚೌಕಟ್ಟು_deps] = 1;
    e->ಚೌಕಟ್ಟು_update[e->nb_ಚೌಕಟ್ಟು_deps] = 0;
    e->nb_ಚೌಕಟ್ಟು_deps++;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        e->sem_wait[e->sem_wait_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ಮೌಲ್ಯ = vkf->sem_ಮೌಲ್ಯ[i],
            .stage_ಮುಖವಾಡ = wait_stage,
        };

        e->sem_sig[e->sem_sig_cnt++] = (VkSemaphoreSubmitInfo) {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
            .semaphore = vkf->sem[i],
            .ಮೌಲ್ಯ = vkf->sem_ಮೌಲ್ಯ[i] + 1,
            .stage_ಮುಖವಾಡ = signal_stage,
        };

        e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = &vkf->sem_ಮೌಲ್ಯ[i];
        e->sem_sig_val_dst_cnt++;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ ff_vk_exec_update_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_ಸ್ಮರಣೆ_Barrier2 *bar, uint32_t *nb_img_bar)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < e->nb_ಚೌಕಟ್ಟು_deps; i++)
        ಆದರೆ (e->ಚೌಕಟ್ಟು_deps[i]->ದತ್ತಾಂಶ[0] == f->ದತ್ತಾಂಶ[0])
            ನಿಲ್ಲಿಸು;
    av_assert0(i < e->nb_ಚೌಕಟ್ಟು_deps);

    /* Don't update duplicates */
    ಆದರೆ (nb_img_bar && !e->ಚೌಕಟ್ಟು_update[i])
        (*nb_img_bar)++;

    e->ಸರತಿ_family_dst[i] = bar->dst_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ;
    e->access_dst[i] = bar->dst_Access_ಮುಖವಾಡ;
    e->layout_dst[i] = bar->newLayout;
    e->ಚೌಕಟ್ಟು_update[i] = 1;
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_mirror_sem_ಮೌಲ್ಯ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f)
{
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];

    /* Reject unknown frames */
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < e->nb_ಚೌಕಟ್ಟು_deps; i++)
        ಆದರೆ (e->ಚೌಕಟ್ಟು_deps[i]->ದತ್ತಾಂಶ[0] == f->ದತ್ತಾಂಶ[0])
            ನಿಲ್ಲಿಸು;
    ಆದರೆ (i == e->nb_ಚೌಕಟ್ಟು_deps)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_assert1(e->sem_sig_val_dst_cnt < FF_VK_EXEC_MAX_SEM_OPS);

    *dst     = vkf->sem[0];
    *dst_val = vkf->sem_ಮೌಲ್ಯ[0];

    e->sem_sig_val_dst[e->sem_sig_val_dst_cnt] = dst_val;
    e->sem_sig_val_dst_cnt++;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Command_ಬಫರ್_Submit_Info cmd_buf_info = (Vk_Command_ಬಫರ್_Submit_Info) {
        .sType = VK_STRUCTURE_TYPE_COMMAND_ಬಫರ್_SUBMIT_INFO,
        .command_ಬಫರ್ = e->buf,
    };
    VkSubmitInfo2 submit_info = (VkSubmitInfo2) {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .p_Command_ಬಫರ್_Infos = &cmd_buf_info,
        .command_ಬಫರ್_Info_ಎಣಿಕೆ = 1,
        .pWaitSemaphoreInfos = e->sem_wait,
        .wait_Semaphore_Info_ಎಣಿಕೆ = e->sem_wait_cnt,
        .pSignalSemaphoreInfos = e->sem_sig,
        .signal_Semaphore_Info_ಎಣಿಕೆ = e->sem_sig_cnt,
    };

    ret = vk->ಕೊನೆ_Command_ಬಫರ್(e->buf);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to finish command buffer: %s\n",
               ff_vk_ret2str(ret));
        ff_vk_exec_discard(s, e);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

#ಆದರೆ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->ಬೀಗ_ಸರತಿ(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#ಆದರೆ_ಅಂತ್ಯ
    ret = vk->ಸರತಿ_Submit2(e->ಸರತಿ, 1, &submit_info, VK_NULL_HANDLE);
#ಆದರೆ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    s->hwctx->unlock_ಸರತಿ(s->device, e->qf, e->qi);
FF_ENABLE_DEPRECATION_WARNINGS
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to submit command buffer: %s\n",
               ff_vk_ret2str(ret));
        /* This also un-claims the context by signalling its semaphore */
        ff_vk_exec_discard(s, e);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->sem_sig_val_dst_cnt; i++)
        *e->sem_sig_val_dst[i] += 1;

    /* Unlock all frames */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < e->nb_ಚೌಕಟ್ಟು_deps; j++) {
        ಆದರೆ (e->ಚೌಕಟ್ಟು_locked[j]) {
            AVFrame *f = e->ಚೌಕಟ್ಟು_deps[j];
            AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
            AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *vkfc = hwfc->hwctx;
            AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];

            ಆದರೆ (e->ಚೌಕಟ್ಟು_update[j]) {
                ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
                    vkf->layout[i] = e->layout_dst[j];
                    vkf->access[i] = e->access_dst[j];
                    vkf->ಸರತಿ_family[i] = e->ಸರತಿ_family_dst[j];
                }
            }
            vkfc->unlock_ಚೌಕಟ್ಟು(hwfc, vkf);
            e->ಚೌಕಟ್ಟು_locked[j] = 0;
        }
    }

    e->had_submission = 1;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_alloc_mem(FFVulkanContext *s, Vk_ಸ್ಮರಣೆ_Requirements *req,
                    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು req_flags, ಶೂನ್ಯ *alloc_extension,
                    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು *mem_flags, Vk_Device_ಸ್ಮರಣೆ *mem)
{
    Vk_ಫಲಿತಾಂಶ ret;
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = -1;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ಸ್ಮರಣೆ_Allocate_Info alloc_info = {
        .sType           = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_ALLOCATE_INFO,
        .p_ಮುಂದಿನ           = alloc_extension,
    };

    alloc_info.ಹಂಚಿಕೆ_ಗಾತ್ರ = req->ಗಾತ್ರ_2;

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ; i++) {
        /* The memory type must be supported by the requirements (bitfield) */
        ಆದರೆ (!(req->ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು & (1 << i)))
            ಮುಂದುವರಿ;

        /* The memory type flags must include our properties */
        ಆದರೆ ((req_flags != UINT32_MAX) &&
            ((s->mprops.ಸ್ಮರಣೆ_Types[i].propertyFlags & req_flags) != req_flags))
            ಮುಂದುವರಿ;

        /* Found a suitable memory type */
        ಸೂಚ್ಯಂಕ = i;
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (ಸೂಚ್ಯಂಕ < 0) {
        av_log(s, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    alloc_info.ಸ್ಮರಣೆ_Type_ಸೂಚ್ಯಂಕ = ಸೂಚ್ಯಂಕ;

    ret = vk->Allocate_ಸ್ಮರಣೆ(s->hwctx->act_dev, &alloc_info,
                             s->hwctx->alloc, mem);
    ಆದರೆ (ret != VK_SUCCESS)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (mem_flags)
        *mem_flags |= s->mprops.ಸ್ಮರಣೆ_Types[ಸೂಚ್ಯಂಕ].propertyFlags;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_ಸ್ಮರಣೆ *mem,
                       ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, VkFormat format, ಪೂರ್ಣಾಂಕ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ಶೂನ್ಯ *create_pnext)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು mem_flags;

    VkImageCreateInfo create_info = {
        .sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .p_ಮುಂದಿನ         = create_pnext,
        .flags         = flags,
        .imageType     = VK_IMAGE_TYPE_2D,
        .format        = format,
        .extent        = { ಅಗಲ, ಎತ್ತರ, 1 },
        .mip_ಮಟ್ಟಗಳು     = 1,
        .arrayLayers   = nb_layers,
        .tiling        = tiling,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage         = usage,
        .samples       = VK_SAMPLE_ಎಣಿಕೆ_1_ಬಿಟ್,
        .sharing_ಬಹುಲಕ   = VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
    };
    Vk_ಸ್ಮರಣೆ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_ALLOCATE_INFO,
    };
    Vk_ಸ್ಮರಣೆ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_REQUIREMENTS_2,
    };
    Vk_Image_ಸ್ಮರಣೆ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_ಸ್ಮರಣೆ_REQUIREMENTS_INFO_2,
    };
    Vk_Bind_Image_ಸ್ಮರಣೆ_Info bind_info = {
        .sType = VK_STRUCTURE_TYPE_BIND_IMAGE_ಸ್ಮರಣೆ_INFO,
    };

    *img = VK_NULL_HANDLE;
    *mem = VK_NULL_HANDLE;

    ret = vk->CreateImage(s->hwctx->act_dev, &create_info,
                          s->hwctx->alloc, img);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Image creation failure: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    req_desc.image = *img;
    vk->Get_Image_ಸ್ಮರಣೆ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* Never shared with another image, so always dedicated */
    ded_alloc.image = *img;
    err = ff_vk_alloc_mem(s, &req.ಸ್ಮರಣೆ_Requirements,
                          VK_ಸ್ಮರಣೆ_PROPERTY_DEVICE_LOCAL_ಬಿಟ್,
                          &ded_alloc, &mem_flags, mem);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    bind_info.image  = *img;
    bind_info.ಸ್ಮರಣೆ = *mem;
    ret = vk->BindImageMemory2(s->hwctx->act_dev, 1, &bind_info);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind image memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ff_vk_image_free(s, img, mem);
    ಹಿಂತಿರುಗಿ err;
}

ಶೂನ್ಯ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_ಸ್ಮರಣೆ *mem)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಆದರೆ (*img) {
        vk->DestroyImage(s->hwctx->act_dev, *img, s->hwctx->alloc);
        *img = VK_NULL_HANDLE;
    }
    ಆದರೆ (*mem) {
        vk->Free_ಸ್ಮರಣೆ(s->hwctx->act_dev, *mem, s->hwctx->alloc);
        *mem = VK_NULL_HANDLE;
    }
}

ಪೂರ್ಣಾಂಕ ff_vk_create_buf(FFVulkanContext *s, FFVk_ಬಫರ್ *buf, size_t ಗಾತ್ರ_2,
                     ಶೂನ್ಯ *p_ಮುಂದಿನ, ಶೂನ್ಯ *alloc_p_ಮುಂದಿನ,
                     Vk_ಬಫರ್_Usage_Flags usage, Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು flags)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    ಪೂರ್ಣಾಂಕ use_ded_mem;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ಬಫರ್_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_ಬಫರ್_CREATE_INFO,
        .p_ಮುಂದಿನ       = p_ಮುಂದಿನ,
        .usage       = usage,
        .sharing_ಬಹುಲಕ = VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
        .ಗಾತ್ರ_2        = flags & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್ ?
                       FFALIGN(ಗಾತ್ರ_2, s->props.properties.limits.min_ಸ್ಮರಣೆ_Map_Alignment) :
                       ಗಾತ್ರ_2,
    };

    Vk_ಸ್ಮರಣೆ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_ALLOCATE_FLAGS_INFO,
        .flags = VK_ಸ್ಮರಣೆ_ALLOCATE_DEVICE_ವಿಳಾಸ_ಬಿಟ್,
    };
    Vk_ಬಫರ್_ಸ್ಮರಣೆ_Requirements_Info2 req_desc = {
        .sType = VK_STRUCTURE_TYPE_ಬಫರ್_ಸ್ಮರಣೆ_REQUIREMENTS_INFO_2,
    };
    Vk_ಸ್ಮರಣೆ_Dedicated_Allocate_Info ded_alloc = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_ALLOCATE_INFO,
        .p_ಮುಂದಿನ = alloc_p_ಮುಂದಿನ,
    };
    Vk_ಸ್ಮರಣೆ_Dedicated_Requirements ded_req = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_REQUIREMENTS,
    };
    Vk_ಸ್ಮರಣೆ_Requirements2 req = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_REQUIREMENTS_2,
        .p_ಮುಂದಿನ = &ded_req,
    };

    av_log(s, AV_LOG_DEBUG, "Creating a buffer of %zu bytes, "
                            "usage: 0x%x, flags: 0x%x\n",
           ಗಾತ್ರ_2, usage, flags);

    ret = vk->Create_ಬಫರ್(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &buf->buf);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create buffer: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    req_desc.ಬಫರ್ = buf->buf;

    vk->Get_ಬಫರ್_ಸ್ಮರಣೆ_Requirements2(s->hwctx->act_dev, &req_desc, &req);

    /* In case the implementation prefers/requires dedicated allocation */
    use_ded_mem = ded_req.prefers_Dedicated_ಹಂಚಿಕೆ |
                  ded_req.requires_Dedicated_ಹಂಚಿಕೆ;
    ಆದರೆ (use_ded_mem) {
        ded_alloc.ಬಫರ್ = buf->buf;
        ded_alloc.p_ಮುಂದಿನ = alloc_p_ಮುಂದಿನ;
        alloc_p_ಮುಂದಿನ = &ded_alloc;
    }

    ಆದರೆ (usage & VK_ಬಫರ್_USAGE_SHADER_DEVICE_ವಿಳಾಸ_ಬಿಟ್) {
        alloc_flags.p_ಮುಂದಿನ = alloc_p_ಮುಂದಿನ;
        alloc_p_ಮುಂದಿನ = &alloc_flags;
    }

    err = ff_vk_alloc_mem(s, &req.ಸ್ಮರಣೆ_Requirements, flags, alloc_p_ಮುಂದಿನ,
                          &buf->flags, &buf->mem);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    ret = vk->Bind_ಬಫರ್_ಸ್ಮರಣೆ(s->hwctx->act_dev, buf->buf, buf->mem, 0);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to bind memory to buffer: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಆದರೆ (usage & VK_ಬಫರ್_USAGE_SHADER_DEVICE_ವಿಳಾಸ_ಬಿಟ್) {
        Vk_ಬಫರ್_Device_ವಿಳಾಸ_Info ವಿಳಾಸ_info = {
            .sType = VK_STRUCTURE_TYPE_ಬಫರ್_DEVICE_ವಿಳಾಸ_INFO,
            .ಬಫರ್ = buf->buf,
        };
        buf->ವಿಳಾಸ = vk->Get_ಬಫರ್_Device_ವಿಳಾಸ(s->hwctx->act_dev, &ವಿಳಾಸ_info);
    }

    buf->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_map_buffers(FFVulkanContext *s, FFVk_ಬಫರ್ **buf, uint8_t *mem[],
                      ಪೂರ್ಣಾಂಕ nb_buffers, ಪೂರ್ಣಾಂಕ invalidate)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_ಸ್ಮರಣೆ_Range inval_list[64];
    ಪೂರ್ಣಾಂಕ inval_ಎಣಿಕೆ = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_buffers; i++) {
        ಶೂನ್ಯ *dst;
        ret = vk->Map_ಸ್ಮರಣೆ(s->hwctx->act_dev, buf[i]->mem, 0,
                            VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ, 0, &dst);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to map buffer memory: %s\n",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
        buf[i]->mapped_mem = dst;
        ಆದರೆ (mem)
            mem[i] = dst;
    }

    ಆದರೆ (!invalidate)
        ಹಿಂತಿರುಗಿ 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_buffers; i++) {
        ಸ್ಥಿರಾಂಕ Vk_Mapped_ಸ್ಮರಣೆ_Range ival_buf = {
            .sType  = VK_STRUCTURE_TYPE_MAPPED_ಸ್ಮರಣೆ_RANGE,
            .ಸ್ಮರಣೆ = buf[i]->mem,
            .ಗಾತ್ರ_2   = VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ,
        };
        ಆದರೆ (buf[i]->flags & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_COHERENT_ಬಿಟ್)
            ಮುಂದುವರಿ;
        inval_list[inval_ಎಣಿಕೆ++] = ival_buf;
    }

    ಆದರೆ (inval_ಎಣಿಕೆ) {
        ret = vk->Invalidate_Mapped_ಸ್ಮರಣೆ_Ranges(s->hwctx->act_dev, inval_ಎಣಿಕೆ,
                                               inval_list);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to invalidate memory: %s\n",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_flush_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ *buf,
                       Vk_Device_ಗಾತ್ರ ಸ್ಥಾನಾಂತರ, Vk_Device_ಗಾತ್ರ mem_ಗಾತ್ರ,
                       ಪೂರ್ಣಾಂಕ flush)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ಆದರೆ (buf->flags & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_COHERENT_ಬಿಟ್)
        ಹಿಂತಿರುಗಿ 0;

    ಸ್ಥಿರಾಂಕ Vk_Mapped_ಸ್ಮರಣೆ_Range flush_ದತ್ತಾಂಶ = {
        .sType  = VK_STRUCTURE_TYPE_MAPPED_ಸ್ಮರಣೆ_RANGE,
        .ಸ್ಮರಣೆ = buf->mem,
        .ಸ್ಥಾನಾಂತರ = ಸ್ಥಾನಾಂತರ,
        .ಗಾತ್ರ_2   = mem_ಗಾತ್ರ,
    };

    ಆದರೆ (flush)
        ret = vk->Flush_Mapped_ಸ್ಮರಣೆ_Ranges(s->hwctx->act_dev, 1, &flush_ದತ್ತಾಂಶ);
    ಇಲ್ಲದಿದ್ದರೆ
        ret = vk->Invalidate_Mapped_ಸ್ಮರಣೆ_Ranges(s->hwctx->act_dev, 1, &flush_ದತ್ತಾಂಶ);

    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_ಬಫರ್ **buf, ಪೂರ್ಣಾಂಕ nb_buffers,
                        ಪೂರ್ಣಾಂಕ flush)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Mapped_ಸ್ಮರಣೆ_Range flush_list[64];
    ಪೂರ್ಣಾಂಕ flush_ಎಣಿಕೆ = 0;

    ಆದರೆ (flush) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_buffers; i++) {
            ಸ್ಥಿರಾಂಕ Vk_Mapped_ಸ್ಮರಣೆ_Range flush_buf = {
                .sType  = VK_STRUCTURE_TYPE_MAPPED_ಸ್ಮರಣೆ_RANGE,
                .ಸ್ಮರಣೆ = buf[i]->mem,
                .ಗಾತ್ರ_2   = VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ,
            };

            av_assert0(!buf[i]->host_ref);
            ಆದರೆ (buf[i]->flags & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_COHERENT_ಬಿಟ್)
                ಮುಂದುವರಿ;
            flush_list[flush_ಎಣಿಕೆ++] = flush_buf;
        }
    }

    ಆದರೆ (flush_ಎಣಿಕೆ) {
        ret = vk->Flush_Mapped_ಸ್ಮರಣೆ_Ranges(s->hwctx->act_dev, flush_ಎಣಿಕೆ,
                                          flush_list);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to flush memory: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL; /* We still want to try to unmap them */
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_buffers; i++) {
        vk->Unmap_ಸ್ಮರಣೆ(s->hwctx->act_dev, buf[i]->mem);
        buf[i]->mapped_mem = ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ err;
}

ಶೂನ್ಯ ff_vk_free_buf(FFVulkanContext *s, FFVk_ಬಫರ್ *buf)
{
    FFVulkanFunctions *vk = &s->vkfn;

    ಆದರೆ (!buf || !s->hwctx)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (buf->mapped_mem && !buf->host_ref)
        ff_vk_unmap_ಬಫರ್(s, buf, 0);
    ಆದರೆ (buf->buf != VK_NULL_HANDLE)
        vk->Destroy_ಬಫರ್(s->hwctx->act_dev, buf->buf, s->hwctx->alloc);
    ಆದರೆ (buf->mem != VK_NULL_HANDLE)
        vk->Free_ಸ್ಮರಣೆ(s->hwctx->act_dev, buf->mem, s->hwctx->alloc);
    ಆದರೆ (buf->host_ref)
        av_ಬಫರ್_unref(&buf->host_ref);

    buf->buf = VK_NULL_HANDLE;
    buf->mem = VK_NULL_HANDLE;
    buf->mapped_mem = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ pooled_buf_free(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ಪೂರ್ಣಾಂಕ ff_vk_get_pooled_ಬಫರ್(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_ಬಫರ್ **buf, Vk_ಬಫರ್_Usage_Flags usage,
                            ಶೂನ್ಯ *create_p_ಮುಂದಿನ, size_t ಗಾತ್ರ_2,
                            Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು mem_props)
{
    ಪೂರ್ಣಾಂಕ err;
    FFVk_ಬಫರ್ *ದತ್ತಾಂಶ;

    ಆದರೆ (!(*buf_pool)) {
        *buf_pool = av_refstruct_pool_alloc_ext(ಗಾತ್ರ(FFVk_ಬಫರ್), 0, ctx,
                                                ಖಾಲಿ, ಖಾಲಿ, pooled_buf_free,
                                                ಖಾಲಿ);
        ಆದರೆ (!(*buf_pool))
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    *buf = ದತ್ತಾಂಶ = av_refstruct_pool_get(*buf_pool);
    ಆದರೆ (!ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (ದತ್ತಾಂಶ->ಗಾತ್ರ_2 >= ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ 0;

    ff_vk_free_buf(ctx, ದತ್ತಾಂಶ);
    memset(ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(*ದತ್ತಾಂಶ));

    err = ff_vk_create_buf(ctx, ದತ್ತಾಂಶ, ಗಾತ್ರ_2,
                           create_p_ಮುಂದಿನ, ಖಾಲಿ, usage,
                           mem_props);
    ಆದರೆ (err < 0) {
        av_refstruct_unref(buf);
        ಹಿಂತಿರುಗಿ err;
    }

    ಆದರೆ (mem_props & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್) {
        err = ff_vk_map_ಬಫರ್(ctx, ದತ್ತಾಂಶ, &ದತ್ತಾಂಶ->mapped_mem, 0);
        ಆದರೆ (err < 0) {
            av_refstruct_unref(buf);
            ಹಿಂತಿರುಗಿ err;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ create_mapped_ಬಫರ್(FFVulkanContext *s,
                                FFVk_ಬಫರ್ *vkb, Vk_ಬಫರ್_Usage_Flags usage,
                                size_t ಗಾತ್ರ_2,
                                Vk_External_ಸ್ಮರಣೆ_ಬಫರ್_Create_Info *create_desc,
                                Vk_Import_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Info_EXT *import_desc,
                                Vk_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Properties_EXT props)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_ಬಫರ್_Create_Info buf_spawn = {
        .sType       = VK_STRUCTURE_TYPE_ಬಫರ್_CREATE_INFO,
        .p_ಮುಂದಿನ       = create_desc,
        .usage       = usage,
        .sharing_ಬಹುಲಕ = VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
        .ಗಾತ್ರ_2        = ಗಾತ್ರ_2,
    };
    Vk_ಸ್ಮರಣೆ_Requirements req = {
        .ಗಾತ್ರ_2           = ಗಾತ್ರ_2,
        .alignment      = s->hprops.min_Imported_Host_ಸೂಚಕ_Alignment,
        .ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು = props.ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು,
    };

    err = ff_vk_alloc_mem(s, &req,
                          VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್,
                          import_desc, &vkb->flags, &vkb->mem);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    ret = vk->Create_ಬಫರ್(s->hwctx->act_dev, &buf_spawn, s->hwctx->alloc, &vkb->buf);
    ಆದರೆ (ret != VK_SUCCESS) {
        vk->Free_ಸ್ಮರಣೆ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ret = vk->Bind_ಬಫರ್_ಸ್ಮರಣೆ(s->hwctx->act_dev, vkb->buf, vkb->mem, 0);
    ಆದರೆ (ret != VK_SUCCESS) {
        vk->Free_ಸ್ಮರಣೆ(s->hwctx->act_dev, vkb->mem, s->hwctx->alloc);
        vk->Destroy_ಬಫರ್(s->hwctx->act_dev, vkb->buf, s->hwctx->alloc);
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ host_map_free(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj)
{
    ff_vk_free_buf(opaque.nc, obj);
}

ಪೂರ್ಣಾಂಕ ff_vk_host_map_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ **dst,
                          uint8_t *src_ದತ್ತಾಂಶ, Vk_Device_ಗಾತ್ರ ಗಾತ್ರ_2,
                          ಸ್ಥಿರಾಂಕ AVBufferRef *src_buf,
                          Vk_ಬಫರ್_Usage_Flags usage)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    Vk_External_ಸ್ಮರಣೆ_ಬಫರ್_Create_Info create_desc = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_ಸ್ಮರಣೆ_ಬಫರ್_CREATE_INFO,
        .handleTypes = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_HOST_ಹಂಚಿಕೆ_ಬಿಟ್_EXT,
    };
    Vk_ಸ್ಮರಣೆ_Allocate_Flags_Info alloc_flags = {
        .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_ALLOCATE_FLAGS_INFO,
        .flags = VK_ಸ್ಮರಣೆ_ALLOCATE_DEVICE_ವಿಳಾಸ_ಬಿಟ್,
    };
    Vk_Import_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Info_EXT import_desc = {
        .sType = VK_STRUCTURE_TYPE_IMPORT_ಸ್ಮರಣೆ_HOST_ಸೂಚಕ_INFO_EXT,
        .handleType = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_HOST_ಹಂಚಿಕೆ_ಬಿಟ್_EXT,
        .p_ಮುಂದಿನ = usage & VK_ಬಫರ್_USAGE_SHADER_DEVICE_ವಿಳಾಸ_ಬಿಟ್ ? &alloc_flags : ಖಾಲಿ,
    };
    Vk_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Properties_EXT props;

    AVBufferRef *ref;
    FFVk_ಬಫರ್ *vkb;
    size_t offs;
    size_t ಬಫರ್_ಗಾತ್ರ;

    *dst = ಖಾಲಿ;

    /* Get the previous point at which mapping was possible and use it */
    offs = (uintptr_t)src_ದತ್ತಾಂಶ % s->hprops.min_Imported_Host_ಸೂಚಕ_Alignment;
    import_desc.p_Host_ಸೂಚಕ = src_ದತ್ತಾಂಶ - offs;

    props = (Vk_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Properties_EXT) {
        VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_HOST_ಸೂಚಕ_PROPERTIES_EXT,
    };
    ret = vk->Get_ಸ್ಮರಣೆ_Host_ಸೂಚಕ_Properties_EXT(s->hwctx->act_dev,
                                                import_desc.handleType,
                                                import_desc.p_Host_ಸೂಚಕ,
                                                &props);
    ಆದರೆ (!(ret == VK_SUCCESS && props.ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    /* Ref the source buffer */
    ref = av_ಬಫರ್_ref(src_buf);
    ಆದರೆ (!ref)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* Add the offset at the start, which gets ignored. */
    ಸ್ಥಿರಾಂಕ Vk_Device_ಗಾತ್ರ src_avail = src_buf->ಗಾತ್ರ_2 - (src_ದತ್ತಾಂಶ - src_buf->ದತ್ತಾಂಶ);
    ಬಫರ್_ಗಾತ್ರ = offs + FFMIN(ಗಾತ್ರ_2, src_avail);
    ಬಫರ್_ಗಾತ್ರ = FFALIGN(ಬಫರ್_ಗಾತ್ರ, s->props.properties.limits.min_ಸ್ಮರಣೆ_Map_Alignment);
    ಬಫರ್_ಗಾತ್ರ = FFALIGN(ಬಫರ್_ಗಾತ್ರ, s->hprops.min_Imported_Host_ಸೂಚಕ_Alignment);

    /* Create a buffer struct */
    vkb = av_refstruct_alloc_ext(ಗಾತ್ರ(*vkb), 0, s, host_map_free);
    ಆದರೆ (!vkb) {
        av_ಬಫರ್_unref(&ref);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    err = create_mapped_ಬಫರ್(s, vkb, usage,
                               ಬಫರ್_ಗಾತ್ರ, &create_desc, &import_desc,
                               props);
    ಆದರೆ (err < 0) {
        av_ಬಫರ್_unref(&ref);
        av_refstruct_unref(&vkb);
        ಹಿಂತಿರುಗಿ err;
    }

    ಆದರೆ (usage & VK_ಬಫರ್_USAGE_SHADER_DEVICE_ವಿಳಾಸ_ಬಿಟ್) {
        Vk_ಬಫರ್_Device_ವಿಳಾಸ_Info ವಿಳಾಸ_info = {
            .sType = VK_STRUCTURE_TYPE_ಬಫರ್_DEVICE_ವಿಳಾಸ_INFO,
            .ಬಫರ್ = vkb->buf,
        };
        vkb->ವಿಳಾಸ = vk->Get_ಬಫರ್_Device_ವಿಳಾಸ(s->hwctx->act_dev, &ವಿಳಾಸ_info);
    }

    vkb->host_ref       = ref;
    vkb->virtual_ಸ್ಥಾನಾಂತರ = offs;
    vkb->ವಿಳಾಸ       += offs;
    vkb->mapped_mem     = src_ದತ್ತಾಂಶ;
    vkb->ಗಾತ್ರ_2           = ಬಫರ್_ಗಾತ್ರ - offs;

    *dst = vkb;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_ಕೂಡಿಸು_ತಳ್ಳು_const(FFVulkanShader *shd, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2,
                                Vk_Shader_Stage_Flag_ಬಿಟ್ಟುಗಳು stage)
{
    Vk_ತಳ್ಳು_Constant_Range *pc = &shd->ತಳ್ಳು_consts[shd->ತಳ್ಳು_consts_ಅಂಕೆ++];
    av_assert1(shd->ತಳ್ಳು_consts_ಅಂಕೆ < FF_VK_MAX_ತಳ್ಳು_CONSTS);
    pc->stageFlags = stage;
    pc->ಸ್ಥಾನಾಂತರ = ಸ್ಥಾನಾಂತರ;
    pc->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ಪೂರ್ಣಾಂಕ unnorm_coords, VkFilter filt)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkSamplerCreateInfo sampler_info = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = filt,
        .minFilter = sampler_info.magFilter,
        .mipmap_ಬಹುಲಕ = (unnorm_coords || filt == VK_FILTER_ಹತ್ತಿರದ) ?
                      VK_SAMPLER_MIPMAP_ಬಹುಲಕ_ಹತ್ತಿರದ :
                      VK_SAMPLER_MIPMAP_ಬಹುಲಕ_ರೇಖೀಯ,
        .ವಿಳಾಸ_ಬಹುಲಕ_U = VK_SAMPLER_ವಿಳಾಸ_ಬಹುಲಕ_CLAMP_ಗಮ್ಯ_ಅಂಚು,
        .ವಿಳಾಸ_ಬಹುಲಕ_V = sampler_info.ವಿಳಾಸ_ಬಹುಲಕ_U,
        .ವಿಳಾಸ_ಬಹುಲಕ_W = sampler_info.ವಿಳಾಸ_ಬಹುಲಕ_U,
        .anisotropyEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_NEVER,
        .borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        .unnormalizedCoordinates = unnorm_coords,
    };

    ret = vk->CreateSampler(s->hwctx->act_dev, &sampler_info,
                            s->hwctx->alloc, sampler);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init sampler: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ಪೂರ್ಣಾಂಕ p)
{
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VkImageAspectFlags plane_aspect[] = { VK_IMAGE_ASPECT_PLANE_0_ಬಿಟ್,
                                                       VK_IMAGE_ASPECT_PLANE_1_ಬಿಟ್,
                                                       VK_IMAGE_ASPECT_PLANE_2_ಬಿಟ್, };

    ಆದರೆ (ff_vk_mt_is_np_rgb(hwfc->sw_format) || (nb_planes == nb_images))
        ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_COLOR_ಬಿಟ್;

    ಹಿಂತಿರುಗಿ plane_aspect[p];
}

ಪೂರ್ಣಾಂಕ ff_vk_mt_is_np_rgb(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಆದರೆ (pix_fmt == AV_PIX_FMT_ABGR   || pix_fmt == AV_PIX_FMT_BGRA   ||
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
        ಹಿಂತಿರುಗಿ 1;
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ ff_vk_ಗಣ_perm(ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ lut[4], ಪೂರ್ಣಾಂಕ inv)
{
    ಆಯ್ಕೆ (pix_fmt) {
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP10:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP12:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP14:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAPF16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP10:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP12:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP14:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRPF16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRPF32:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP32:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAPF32:
        lut[0] = 1;
        lut[1] = 2;
        lut[2] = 0;
        lut[3] = 3;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_X2BGR10:
        lut[0] = 0;
        lut[1] = 2;
        lut[2] = 1;
        lut[3] = 3;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_BGRA:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR0:
        /* Stored in RGBA images, so reverse them */
        lut[0] = 2;
        lut[1] = 1;
        lut[2] = 0;
        lut[3] = 3;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        lut[0] = 0;
        lut[1] = 1;
        lut[2] = 2;
        lut[3] = 3;
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (inv) {
        ಪೂರ್ಣಾಂಕ lut_tmp[4] = { lut[0], lut[1], lut[2], lut[3] };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
            lut[lut_tmp[i]] = i;
    }

    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ff_vk_shader_rep_fmt(ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                 ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt)
{
    ಆಯ್ಕೆ (pix_fmt) {
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBA:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGRA:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB24:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR24:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR0:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB0:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB565:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR565:
    ಸ್ಥಿತಿ AV_PIX_FMT_UYVA:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUYV422:
    ಸ್ಥಿತಿ AV_PIX_FMT_UYVY422: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba8ui",
            [FF_VK_REP_FLOAT] = "rgba8",
            [FF_VK_REP_INT] = "rgba8i",
            [FF_VK_REP_UINT] = "rgba8ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_X2RGB10:
    ಸ್ಥಿತಿ AV_PIX_FMT_X2BGR10:
    ಸ್ಥಿತಿ AV_PIX_FMT_Y210:
    ಸ್ಥಿತಿ AV_PIX_FMT_XV30: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ಖಾಲಿ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB48:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBA64:
    ಸ್ಥಿತಿ AV_PIX_FMT_Y212:
    ಸ್ಥಿತಿ AV_PIX_FMT_Y216:
    ಸ್ಥಿತಿ AV_PIX_FMT_XV36:
    ಸ್ಥಿತಿ AV_PIX_FMT_XV48: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16ui",
            [FF_VK_REP_FLOAT] = "rgba16",
            [FF_VK_REP_INT] = "rgba16i",
            [FF_VK_REP_UINT] = "rgba16ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBAF16: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba16f",
            [FF_VK_REP_FLOAT] = "rgba16f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba16u",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBF32:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBAF32: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32f",
            [FF_VK_REP_FLOAT] = "rgba32f",
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB96:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGBA128: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgba32ui",
            [FF_VK_REP_FLOAT] = ಖಾಲಿ,
            [FF_VK_REP_INT] = "rgba32i",
            [FF_VK_REP_UINT] = "rgba32ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    }
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP:
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY8:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA420P:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA422P:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA444P: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r8ui",
            [FF_VK_REP_FLOAT] = "r8",
            [FF_VK_REP_INT] = "r8i",
            [FF_VK_REP_UINT] = "r8ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY10:
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY12:
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY14:
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP10:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP12:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP14:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAPF16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP10:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP12:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP14:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRP16:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRPF16:
    ಸ್ಥಿತಿ AV_PIX_FMT_XYZP12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA420P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA420P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA422P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA422P12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA422P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA444P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA444P12:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUVA444P16:
    ಸ್ಥಿತಿ AV_PIX_FMT_BAYER_RGGB16: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r16ui",
            [FF_VK_REP_FLOAT] = "r16f",
            [FF_VK_REP_INT] = "r16i",
            [FF_VK_REP_UINT] = "r16ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAY32:
    ಸ್ಥಿತಿ AV_PIX_FMT_GRAYF32:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRPF32:
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAPF32: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32f",
            [FF_VK_REP_FLOAT] = "r32f",
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_GBRAP32: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "r32ui",
            [FF_VK_REP_FLOAT] = ಖಾಲಿ,
            [FF_VK_REP_INT] = "r32i",
            [FF_VK_REP_UINT] = "r32ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_NV12:
    ಸ್ಥಿತಿ AV_PIX_FMT_NV16:
    ಸ್ಥಿತಿ AV_PIX_FMT_NV24: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg8ui",
            [FF_VK_REP_FLOAT] = "rg8",
            [FF_VK_REP_INT] = "rg8i",
            [FF_VK_REP_UINT] = "rg8ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_P010:
    ಸ್ಥಿತಿ AV_PIX_FMT_P210:
    ಸ್ಥಿತಿ AV_PIX_FMT_P410: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rgb10_a2ui",
            [FF_VK_REP_FLOAT] = "rgb10_a2",
            [FF_VK_REP_INT] = ಖಾಲಿ,
            [FF_VK_REP_UINT] = "rgb10_a2ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಸ್ಥಿತಿ AV_PIX_FMT_P012:
    ಸ್ಥಿತಿ AV_PIX_FMT_P016:
    ಸ್ಥಿತಿ AV_PIX_FMT_P212:
    ಸ್ಥಿತಿ AV_PIX_FMT_P216:
    ಸ್ಥಿತಿ AV_PIX_FMT_P412:
    ಸ್ಥಿತಿ AV_PIX_FMT_P416: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rep_tab[] = {
            [FF_VK_REP_NATIVE] = "rg16ui",
            [FF_VK_REP_FLOAT] = "rg16",
            [FF_VK_REP_INT] = "rg16i",
            [FF_VK_REP_UINT] = "rg16ui",
        };
        ಹಿಂತಿರುಗಿ rep_tab[rep_fmt];
    };
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ "rgba32f";
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ reset_imageviews(AVRefStructOpaque ಬಳಸದ, ಶೂನ್ಯ *obj)
{
    FFVkImageViews *iv = obj;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < iv->nb_views; i++) {
        ಆದರೆ (iv->views[i])
            iv->destroy_image_view(iv->dev, iv->views[i], iv->alloc);
    }

    memset(iv->views, 0, ಗಾತ್ರ(iv->views));
}

FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ಪೂರ್ಣಾಂಕ nb_views)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVkImageViews *iv;

    av_assert1(nb_views <= AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು);

    iv = av_refstruct_pool_get(s->imageviews_pool);
    ಆದರೆ (!iv)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    iv->nb_views           = nb_views;
    iv->dev                = s->hwctx->act_dev;
    iv->alloc              = s->hwctx->alloc;
    iv->destroy_image_view = vk->DestroyImageView;

    ಹಿಂತಿರುಗಿ iv;
}

VkFormat ff_vk_map_fmt_ಗಮ್ಯ_rep(VkFormat fmt, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt)
{
#ವ್ಯಾಖ್ಯಾನಿಸು REPS_FMT(fmt) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM, \
    [FF_VK_REP_INT]    = fmt ## _SINT, \
    [FF_VK_REP_UINT]   = fmt ## _UINT,

#ವ್ಯಾಖ್ಯಾನಿಸು REPS_FMT_PACK(fmt, ಅಂಕೆ) \
    [FF_VK_REP_NATIVE] = fmt ## _UINT_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_FLOAT]  = fmt ## _UNORM_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_INT]    = fmt ## _SINT_PACK ## ಅಂಕೆ, \
    [FF_VK_REP_UINT]   = fmt ## _UINT_PACK ## ಅಂಕೆ,

    ಸ್ಥಿರಾಂಕ VkFormat fmts_map[][4] = {
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
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು REPS_FMT_PACK
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು REPS_FMT

    ಆದರೆ (fmt == VK_FORMAT_UNDEFINED)
        ಹಿಂತಿರುಗಿ VK_FORMAT_UNDEFINED;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(fmts_map); i++) {
        ಆದರೆ (fmts_map[i][FF_VK_REP_NATIVE] == fmt ||
            fmts_map[i][FF_VK_REP_FLOAT] == fmt ||
            fmts_map[i][FF_VK_REP_INT] == fmt ||
            fmts_map[i][FF_VK_REP_UINT] == fmt)
            ಹಿಂತಿರುಗಿ fmts_map[i][rep_fmt];
    }

    ಹಿಂತಿರುಗಿ VK_FORMAT_UNDEFINED;
}

ಪೂರ್ಣಾಂಕ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ಪೂರ್ಣಾಂಕ plane, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *vkfc = hwfc->hwctx;
    ಸ್ಥಿರಾಂಕ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);

    VkImageViewUsageCreateInfo view_usage_info = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
        .usage = vkfc->usage &
                 (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR |
                    VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR)),
    };
    VkImageViewCreateInfo view_create_info = {
        .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .p_ಮುಂದಿನ      = &view_usage_info,
        .image      = vkf->img[FFMIN(plane, nb_images - 1)],
        .viewType   = VK_IMAGE_VIEW_TYPE_2D,
        .format     = ff_vk_map_fmt_ಗಮ್ಯ_rep(rep_fmts[plane], rep_fmt),
        .components = ff_comp_ತಟಸ್ಥ_map,
        .subresourceRange = {
            .aspect_ಮುಖವಾಡ = ff_vk_aspect_flag(f, plane),
            .level_ಎಣಿಕೆ = 1,
            .layer_ಎಣಿಕೆ = 1,
        },
    };
    ಆದರೆ (view_create_info.format == VK_FORMAT_UNDEFINED) {
        av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                "of format %i and mode %i\n",
               rep_fmts[plane], rep_fmt);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                              s->hwctx->alloc, img_view);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    *aspect = view_create_info.subresourceRange.aspect_ಮುಖವಾಡ;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು],
                                AVFrame *f,
                                ಸ್ಥಿರಾಂಕ VkFormat fmts[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು])
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *vkfc = hwfc->hwctx;
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)f->ದತ್ತಾಂಶ[0];
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    VkImageView tmp_views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_planes; i++) {
        VkImageViewUsageCreateInfo view_usage_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
            .usage = vkfc->usage &
                     (~(VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR |
                        VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR)),
        };
        VkImageViewCreateInfo view_create_info = {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .p_ಮುಂದಿನ      = &view_usage_info,
            .image      = vkf->img[FFMIN(i, nb_images - 1)],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = fmts[i],
            .components = ff_comp_ತಟಸ್ಥ_map,
            .subresourceRange = {
                .aspect_ಮುಖವಾಡ = ff_vk_aspect_flag(f, i),
                .level_ಎಣಿಕೆ = 1,
                .layer_ಎಣಿಕೆ = 1,
            },
        };

        ret = vk->CreateImageView(s->hwctx->act_dev, &view_create_info,
                                  s->hwctx->alloc, &tmp_views[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Failed to create imageview: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }
    }

    /* The execution context owns the views, destroying them on completion */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_planes; i++)
        ff_vk_exec_ಕೂಡಿಸು_dep_obj(s, e, VK_OBJECT_TYPE_IMAGE_VIEW,
                               (uint64_t)tmp_views[i]);

    ಸ್ಮರಣೆ_ನಕಲು(views, tmp_views, nb_planes*ಗಾತ್ರ(*views));

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_planes; i++)
        ಆದರೆ (tmp_views[i])
            vk->DestroyImageView(s->hwctx->act_dev, tmp_views[i], s->hwctx->alloc);
    ಹಿಂತಿರುಗಿ err;
}

ಪೂರ್ಣಾಂಕ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು],
                            AVFrame *f, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ VkFormat *rep_fmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    VkFormat fmts[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_planes; i++) {
        fmts[i] = ff_vk_map_fmt_ಗಮ್ಯ_rep(rep_fmts[i], rep_fmt);
        ಆದರೆ (fmts[i] == VK_FORMAT_UNDEFINED) {
            av_log(s, AV_LOG_ERROR, "Unable to find a compatible representation "
                                    "of format %i and mode %i\n",
                   rep_fmts[i], rep_fmt);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಹಿಂತಿರುಗಿ ff_vk_create_imageviews_fmt(s, e, views, f, fmts);
}

ಶೂನ್ಯ ff_vk_ಚೌಕಟ್ಟು_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_ಸ್ಮರಣೆ_Barrier2 *bar, ಪೂರ್ಣಾಂಕ *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t              new_qf)
{
    ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು = -1;
    AVVk_ಚೌಕಟ್ಟು *vkf = (AVVk_ಚೌಕಟ್ಟು *)pic->ದತ್ತಾಂಶ[0];
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(vkf);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->nb_ಚೌಕಟ್ಟು_deps; i++)
        ಆದರೆ (e->ಚೌಕಟ್ಟು_deps[i]->ದತ್ತಾಂಶ[0] == pic->ದತ್ತಾಂಶ[0]) {
            ಆದರೆ (e->ಚೌಕಟ್ಟು_update[i])
                ಸಿಕ್ಕಿತು = i;
            ನಿಲ್ಲಿಸು;
        }

    /* Earlier submissions are ordered by the frame's semaphore, which makes
     * their writes available and visible, so only accesses recorded in this
     * command buffer belong in the source scope. */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        bar[*nb_bar] = (Vk_Image_ಸ್ಮರಣೆ_Barrier2) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ಸ್ಮರಣೆ_BARRIER_2,
            .p_ಮುಂದಿನ = ಖಾಲಿ,
            .src_Stage_ಮುಖವಾಡ = src_stage,
            .dst_Stage_ಮುಖವಾಡ = dst_stage,
            .src_Access_ಮುಖವಾಡ = ಸಿಕ್ಕಿತು >= 0 ? e->access_dst[ಸಿಕ್ಕಿತು] : VK_ACCESS_2_NONE,
            .dst_Access_ಮುಖವಾಡ = new_access,
            .oldLayout = ಸಿಕ್ಕಿತು >= 0 ? e->layout_dst[ಸಿಕ್ಕಿತು] : vkf->layout[0],
            .newLayout = new_layout,
            .src_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = ಸಿಕ್ಕಿತು >= 0 ? e->ಸರತಿ_family_dst[ಸಿಕ್ಕಿತು] : vkf->ಸರತಿ_family[0],
            .dst_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = new_qf,
            .image = vkf->img[i],
            .subresourceRange = (VkImageSubresourceRange) {
                .aspect_ಮುಖವಾಡ = VK_IMAGE_ASPECT_COLOR_ಬಿಟ್,
                .layer_ಎಣಿಕೆ = 1,
                .level_ಎಣಿಕೆ = 1,
            },
        };
        *nb_bar += 1;
    }

    ff_vk_exec_update_ಚೌಕಟ್ಟು(s, e, pic, &bar[*nb_bar - nb_images], ಖಾಲಿ);
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_ತುಂಬು(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_ಗಾತ್ರ[3], uint32_t required_subgroup_ಗಾತ್ರ)
{
    shd->stage = stage;
    shd->precompiled = 1;
    shd->specialization_info = spec;
    ಸ್ಮರಣೆ_ನಕಲು(shd->lg_ಗಾತ್ರ, wg_ಗಾತ್ರ, 3*ಗಾತ್ರ(uint32_t));

    shd->subgroup_info = (Vk_Pipeline_Shader_Stage_Required_Subgroup_ಗಾತ್ರ_Create_Info) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_ಗಾತ್ರ_CREATE_INFO,
        .required_Subgroup_ಗಾತ್ರ = required_subgroup_ಗಾತ್ರ,
    };

    ಆಯ್ಕೆ (shd->stage) {
    ಸ್ಥಿತಿ VK_SHADER_STAGE_ANY_ದೊರಕಿತು_ಬಿಟ್_KHR:
    ಸ್ಥಿತಿ VK_SHADER_STAGE_CALLABLE_ಬಿಟ್_KHR:
    ಸ್ಥಿತಿ VK_SHADER_STAGE_CLOSEST_ದೊರಕಿತು_ಬಿಟ್_KHR:
    ಸ್ಥಿತಿ VK_SHADER_STAGE_INTERSECTION_ಬಿಟ್_KHR:
    ಸ್ಥಿತಿ VK_SHADER_STAGE_ತಪ್ಪಿದ_ಬಿಟ್_KHR:
    ಸ್ಥಿತಿ VK_SHADER_STAGE_RAYGEN_ಬಿಟ್_KHR:
        shd->bind_ಬಿಂದು = VK_PIPELINE_BIND_ಬಿಂದು_RAY_TRACING_KHR;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_SHADER_STAGE_COMPUTE_ಬಿಟ್:
        shd->bind_ಬಿಂದು = VK_PIPELINE_BIND_ಬಿಂದು_COMPUTE;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        shd->bind_ಬಿಂದು = VK_PIPELINE_BIND_ಬಿಂದು_GRAPHICS;
        ನಿಲ್ಲಿಸು;
    };

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ init_pipeline_layout(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;
    VkPipelineLayoutCreateInfo pipeline_layout_info;

    /* Finally create the pipeline layout */
    pipeline_layout_info = (VkPipelineLayoutCreateInfo) {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .p_ಗಣ_Layouts            = shd->desc_layout,
        .ಗಣ_Layout_ಎಣಿಕೆ         = shd->nb_descriptor_sets,
        .ತಳ್ಳು_Constant_Range_ಎಣಿಕೆ = shd->ತಳ್ಳು_consts_ಅಂಕೆ,
        .p_ತಳ್ಳು_Constant_Ranges    = shd->ತಳ್ಳು_consts,
    };

    ret = vk->CreatePipelineLayout(s->hwctx->act_dev, &pipeline_layout_info,
                                   s->hwctx->alloc, &shd->pipeline_layout);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init pipeline layout: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ create_shader_module(FFVulkanContext *s, FFVulkanShader *shd,
                                VkShaderModule *mod,
                                ಸ್ಥಿರಾಂಕ uint8_t *spirv, size_t spirv_len)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkShaderModuleCreateInfo shader_module_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .p_ಮುಂದಿನ    = ಖಾಲಿ,
        .flags    = 0x0,
        .p_ಸಂಕೇತ    = (ಶೂನ್ಯ *)spirv,
        .ಸಂಕೇತ_ಗಾತ್ರ = spirv_len,
    };

    ret = vk->CreateShaderModule(s->hwctx->act_dev, &shader_module_info,
                                 s->hwctx->alloc, mod);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Error creating shader module: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ init_compute_pipeline(FFVulkanContext *s, FFVulkanShader *shd,
                                 VkShaderModule mod, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *entrypoint)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    VkComputePipelineCreateInfo pipeline_create_info = {
        .sType  = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .flags = 0x0,
        .layout = shd->pipeline_layout,
        .stage = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .p_ಮುಂದಿನ = shd->subgroup_info.required_Subgroup_ಗಾತ್ರ ?
                     &shd->subgroup_info : ಖಾಲಿ,
            .pName = entrypoint,
            .flags = shd->subgroup_info.required_Subgroup_ಗಾತ್ರ ?
                     VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_ತುಂಬಿದ_SUBGROUPS_ಬಿಟ್ : 0x0,
            .stage = shd->stage,
            .module = mod,
            .pSpecializationInfo = shd->specialization_info,
        },
    };

    ret = vk->CreateComputePipelines(s->hwctx->act_dev, VK_NULL_HANDLE, 1,
                                     &pipeline_create_info,
                                     s->hwctx->alloc, &shd->pipeline);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(s, AV_LOG_ERROR, "Unable to init compute pipeline: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ init_descriptors(FFVulkanContext *s, FFVulkanShader *shd)
{
    Vk_ಫಲಿತಾಂಶ ret;
    FFVulkanFunctions *vk = &s->vkfn;

    ಪೂರ್ಣಾಂಕ has_singular = 0;
    ಪೂರ್ಣಾಂಕ max_descriptors = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < shd->nb_descriptor_sets; i++) {
        max_descriptors = FFMAX(max_descriptors, shd->desc_ಗಣ[i].nb_bindings);
        ಆದರೆ (shd->desc_ಗಣ[i].singular)
            has_singular = 1;
    }
    shd->use_ತಳ್ಳು = (s->extensions & FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR) &&
                    (max_descriptors <= s->ತಳ್ಳು_desc_props.max_ತಳ್ಳು_Descriptors) &&
                    (shd->nb_descriptor_sets == 1) &&
                    (has_singular == 0);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < shd->nb_descriptor_sets; i++) {
        FFVulkan_Descriptor_ಗಣ *ಗಣ = &shd->desc_ಗಣ[i];
        Vk_Descriptor_ಗಣ_Layout_Create_Info desc_layout_create = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_ಗಣ_LAYOUT_CREATE_INFO,
            .binding_ಎಣಿಕೆ = ಗಣ->nb_bindings,
            .pBindings = ಗಣ->binding,
            .flags = (shd->use_ತಳ್ಳು) ?
                     VK_DESCRIPTOR_ಗಣ_LAYOUT_CREATE_ತಳ್ಳು_DESCRIPTOR_ಬಿಟ್_KHR :
                     0x0,
        };

        ret = vk->Create_Descriptor_ಗಣ_Layout(s->hwctx->act_dev,
                                            &desc_layout_create,
                                            s->hwctx->alloc,
                                            &shd->desc_layout[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor set layout: %s",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *spirv, size_t spirv_len,
                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *entrypoint)
{
    ಪೂರ್ಣಾಂಕ err;
    FFVulkanFunctions *vk = &s->vkfn;
    Vk_Specialization_Map_ನಮೂದು spec_entries[3];
    VkSpecializationInfo spec_info;
    VkShaderModule mod;
    size_t ಒಳಹರಿವು_ಗಾತ್ರ = spirv_len;

    ಆದರೆ (shd->precompiled) {
        ಆದರೆ (!shd->specialization_info) {
            spec_info = (VkSpecializationInfo) {
                .pMapEntries = spec_entries,
                .map_ನಮೂದು_ಎಣಿಕೆ = 0,
                .p_ದತ್ತಾಂಶ = shd->lg_ಗಾತ್ರ,
                .ದತ್ತಾಂಶ_ಗಾತ್ರ_2 = 0,
            };
            shd->specialization_info = &spec_info;
        }

        Vk_Specialization_Map_ನಮೂದು *spe = (ಶೂನ್ಯ *)shd->specialization_info->pMapEntries;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            spe[shd->specialization_info->map_ನಮೂದು_ಎಣಿಕೆ++] = (Vk_Specialization_Map_ನಮೂದು) {
                .constantID = 253 + i,
                .ಸ್ಥಾನಾಂತರ = shd->specialization_info->ದತ್ತಾಂಶ_ಗಾತ್ರ_2 + i*ಗಾತ್ರ(uint32_t),
                .ಗಾತ್ರ_2 = ಗಾತ್ರ(uint32_t),
            };
        }

        uint8_t *spd = (uint8_t *)shd->specialization_info->p_ದತ್ತಾಂಶ;
        ಸ್ಮರಣೆ_ನಕಲು(&spd[shd->specialization_info->ದತ್ತಾಂಶ_ಗಾತ್ರ_2],
               shd->lg_ಗಾತ್ರ, 3*ಗಾತ್ರ(uint32_t));
        shd->specialization_info->ದತ್ತಾಂಶ_ಗಾತ್ರ_2 += 3*ಗಾತ್ರ(uint32_t);

#ಆದರೆ CONFIG_SHADER_COMPRESSION
        uint8_t *ಹೊರಹೋಗು;
        size_t ಹೊರಹೋಗು_len;
        ಪೂರ್ಣಾಂಕ ret = ff_zlib_expand(s, &ಹೊರಹೋಗು, &ಹೊರಹೋಗು_len, spirv, spirv_len);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        spirv = ಹೊರಹೋಗು;
        spirv_len = ಹೊರಹೋಗು_len;
#ಆದರೆ_ಅಂತ್ಯ
    }

    err = init_descriptors(s, shd);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    err = init_pipeline_layout(s, shd);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    err = create_shader_module(s, shd, &mod, spirv, spirv_len);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    ಆಯ್ಕೆ (shd->bind_ಬಿಂದು) {
    ಸ್ಥಿತಿ VK_PIPELINE_BIND_ಬಿಂದು_COMPUTE:
        err = init_compute_pipeline(s, shd, mod, entrypoint);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        av_log(s, AV_LOG_ERROR, "Unsupported shader type: %i\n",
               shd->bind_ಬಿಂದು);
        err = AVERROR(EINVAL);
        ಹೋಗು ಕೊನೆ;
        ನಿಲ್ಲಿಸು;
    };

    vk->DestroyShaderModule(s->hwctx->act_dev, mod, s->hwctx->alloc);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    ಆದರೆ (shd->name)
        av_log(s, AV_LOG_VERBOSE, "Shader %s linked, size:", shd->name);
    ಇಲ್ಲದಿದ್ದರೆ
        av_log(s, AV_LOG_VERBOSE, "Shader linked, size:");

    ಆದರೆ (ಒಳಹರಿವು_ಗಾತ್ರ != spirv_len)
        av_log(s, AV_LOG_VERBOSE, " %zu compressed,", ಒಳಹರಿವು_ಗಾತ್ರ);
    av_log(s, AV_LOG_VERBOSE, " %zu SPIR-V\n", spirv_len);

ಕೊನೆ:
    ಆದರೆ (shd->precompiled) {
        shd->specialization_info->map_ನಮೂದು_ಎಣಿಕೆ -= 3;
        shd->specialization_info->ದತ್ತಾಂಶ_ಗಾತ್ರ_2 -= 3*ಗಾತ್ರ(uint32_t);
    }
#ಆದರೆ CONFIG_SHADER_COMPRESSION
    ಆದರೆ (shd->precompiled)
        av_free((ಶೂನ್ಯ *)spirv);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ err;
}

ಶೂನ್ಯ ff_vk_shader_ಕೂಡಿಸು_descriptor_ಗಣ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ಸ್ಥಿರಾಂಕ FFVulkan_Descriptor_ಗಣ_Binding *desc, ಪೂರ್ಣಾಂಕ nb,
                                     ಪೂರ್ಣಾಂಕ singular)
{
    FFVulkan_Descriptor_ಗಣ *ಗಣ = &shd->desc_ಗಣ[shd->nb_descriptor_sets++];
    av_assert1(shd->nb_descriptor_sets < FF_VK_MAX_DESCRIPTOR_SETS);
    av_assert1(nb < FF_VK_MAX_DESCRIPTOR_BINDINGS);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb; i++) {
        ಗಣ->binding[i].binding            = i;
        ಗಣ->binding[i].descriptorType     = desc[i].type;
        ಗಣ->binding[i].descriptor_ಎಣಿಕೆ    = FFMAX(desc[i].elems, 1);
        ಗಣ->binding[i].stageFlags         = desc[i].stages;
        ಗಣ->binding[i].pImmutableSamplers = desc[i].samplers;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb; i++) {
        ಪೂರ್ಣಾಂಕ j;
        ಗಾಗಿ (j = 0; j < shd->nb_desc_pool_ಗಾತ್ರ; j++)
            ಆದರೆ (shd->desc_pool_ಗಾತ್ರ[j].type == desc[i].type)
                ನಿಲ್ಲಿಸು;
        ಆದರೆ (j >= shd->nb_desc_pool_ಗಾತ್ರ) {
            shd->nb_desc_pool_ಗಾತ್ರ++;
            av_assert1(shd->nb_desc_pool_ಗಾತ್ರ < FF_VK_MAX_DESCRIPTOR_TYPES);
        }

        shd->desc_pool_ಗಾತ್ರ[j].type             = desc[i].type;
        shd->desc_pool_ಗಾತ್ರ[j].descriptor_ಎಣಿಕೆ += FFMAX(desc[i].elems, 1);
    }

    ಗಣ->singular = singular;
    ಗಣ->nb_bindings = nb;
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_ರಿಜಿಸ್ಟರ್_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd)
{
    ಆದರೆ (!shd->nb_descriptor_sets)
        ಹಿಂತಿರುಗಿ 0;

    FFVulkan_Shader_ದತ್ತಾಂಶ *sd = &pool->reg_shd[pool->nb_reg_shd++];
    av_assert1(pool->nb_reg_shd < FF_VK_MAX_SHADERS);

    sd->shd = shd;
    sd->nb_descriptor_sets = shd->nb_descriptor_sets;

    ಆದರೆ (!shd->use_ತಳ್ಳು) {
        Vk_ಫಲಿತಾಂಶ ret;
        FFVulkanFunctions *vk = &s->vkfn;
        Vk_Descriptor_ಗಣ_Layout *tmp_layouts;
        Vk_Descriptor_ಗಣ_Allocate_Info ಗಣ_alloc_info;
        VkDescriptorPoolCreateInfo pool_create_info;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < shd->nb_desc_pool_ಗಾತ್ರ; i++)
            shd->desc_pool_ಗಾತ್ರ[i].descriptor_ಎಣಿಕೆ *= pool->pool_ಗಾತ್ರ;

        pool_create_info = (VkDescriptorPoolCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = 0,
            .pPoolSizes = shd->desc_pool_ಗಾತ್ರ,
            .pool_ಗಾತ್ರ_ಎಣಿಕೆ = shd->nb_desc_pool_ಗಾತ್ರ,
            .maxSets = sd->nb_descriptor_sets*pool->pool_ಗಾತ್ರ,
        };

        ret = vk->CreateDescriptorPool(s->hwctx->act_dev, &pool_create_info,
                                       s->hwctx->alloc, &sd->desc_pool);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to create descriptor pool: %s\n",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        tmp_layouts = av_malloc_array(pool_create_info.maxSets, ಗಾತ್ರ(*tmp_layouts));
        ಆದರೆ (!tmp_layouts)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        /* Colate each execution context's descriptor set layouts */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < pool->pool_ಗಾತ್ರ; i++)
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sd->nb_descriptor_sets; j++)
                tmp_layouts[i*sd->nb_descriptor_sets + j] = shd->desc_layout[j];

        ಗಣ_alloc_info = (Vk_Descriptor_ಗಣ_Allocate_Info) {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_ಗಣ_ALLOCATE_INFO,
            .descriptorPool     = sd->desc_pool,
            .p_ಗಣ_Layouts        = tmp_layouts,
            .descriptor_ಗಣ_ಎಣಿಕೆ = pool_create_info.maxSets,
        };

        sd->desc_sets = av_malloc_array(pool_create_info.maxSets,
                                        ಗಾತ್ರ(*tmp_layouts));
        ಆದರೆ (!sd->desc_sets) {
            av_free(tmp_layouts);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ret = vk->AllocateDescriptorSets(s->hwctx->act_dev, &ಗಣ_alloc_info,
                                         sd->desc_sets);
        av_free(tmp_layouts);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(s, AV_LOG_ERROR, "Unable to allocate descriptor set: %s\n",
                   ff_vk_ret2str(ret));
            av_freep(&sd->desc_sets);
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಸ್ಥಿರಾಂಕ FFVulkan_Shader_ದತ್ತಾಂಶ *get_shd_ದತ್ತಾಂಶ(FFVkExecContext *e,
                                                     ಸ್ಥಿರಾಂಕ FFVulkanShader *shd)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->ಪೋಷಕ->nb_reg_shd; i++)
        ಆದರೆ (e->ಪೋಷಕ->reg_shd[i].shd == shd)
            ಹಿಂತಿರುಗಿ &e->ಪೋಷಕ->reg_shd[i];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ update_ಗಣ_pool_write(FFVulkanContext *s, FFVkExecContext *e,
                                         FFVulkanShader *shd, ಪೂರ್ಣಾಂಕ ಗಣ,
                                         Vk_Write_Descriptor_ಗಣ *write_info)
{
    FFVulkanFunctions *vk = &s->vkfn;
    FFVulkan_Descriptor_ಗಣ *desc_ಗಣ = &shd->desc_ಗಣ[ಗಣ];
    ಸ್ಥಿರಾಂಕ FFVulkan_Shader_ದತ್ತಾಂಶ *sd = get_shd_ದತ್ತಾಂಶ(e, shd);

    ಆದರೆ (desc_ಗಣ->singular) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < e->ಪೋಷಕ->pool_ಗಾತ್ರ; i++) {
            write_info->dst_ಗಣ = sd->desc_sets[i*sd->nb_descriptor_sets + ಗಣ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ಖಾಲಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (shd->use_ತಳ್ಳು) {
            vk->Cmd_ತಳ್ಳು_Descriptor_ಗಣ_KHR(e->buf,
                                        shd->bind_ಬಿಂದು,
                                        shd->pipeline_layout,
                                        ಗಣ, 1,
                                        write_info);
        } ಇಲ್ಲದಿದ್ದರೆ {
            write_info->dst_ಗಣ = sd->desc_sets[e->idx*sd->nb_descriptor_sets + ಗಣ];
            vk->UpdateDescriptorSets(s->hwctx->act_dev, 1, write_info, 0, ಖಾಲಿ);
        }
    }
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ bind, ಪೂರ್ಣಾಂಕ offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler)
{
    FFVulkan_Descriptor_ಗಣ *desc_ಗಣ = &shd->desc_ಗಣ[ಗಣ];

    VkDescriptorImageInfo desc_pool_write_info_img = {
        .sampler = sampler,
        .imageView = view,
        .imageLayout = layout,
    };
    Vk_Write_Descriptor_ಗಣ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_ಗಣ,
        .dstBinding = bind,
        .descriptor_ಎಣಿಕೆ = 1,
        .dstArrayElement = offs,
        .descriptorType = desc_ಗಣ->binding[bind].descriptorType,
        .pImageInfo = &desc_pool_write_info_img,
    };
    update_ಗಣ_pool_write(s, e, shd, ಗಣ, &desc_pool_write_info);

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ binding,
                                   VkImageLayout layout, VkSampler sampler)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)f->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_planes; i++)
        ff_vk_shader_update_img(s, e, shd, ಗಣ, binding, i,
                                views[i], layout, sampler);
}

ಪೂರ್ಣಾಂಕ ff_vk_shader_update_desc_ಬಫರ್(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ bind, ಪೂರ್ಣಾಂಕ elem,
                                    FFVk_ಬಫರ್ *buf, Vk_Device_ಗಾತ್ರ ಸ್ಥಾನಾಂತರ, Vk_Device_ಗಾತ್ರ len,
                                    VkFormat fmt)
{
    FFVulkan_Descriptor_ಗಣ *desc_ಗಣ = &shd->desc_ಗಣ[ಗಣ];

    Vk_Descriptor_ಬಫರ್_Info desc_pool_write_info_buf = {
        .ಬಫರ್ = buf->buf,
        .ಸ್ಥಾನಾಂತರ = buf->virtual_ಸ್ಥಾನಾಂತರ + ಸ್ಥಾನಾಂತರ,
        .range = len,
    };
    Vk_Write_Descriptor_ಗಣ desc_pool_write_info = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_ಗಣ,
        .dstBinding = bind,
        .descriptor_ಎಣಿಕೆ = 1,
        .dstArrayElement = elem,
        .descriptorType = desc_ಗಣ->binding[bind].descriptorType,
        .p_ಬಫರ್_Info = &desc_pool_write_info_buf,
    };
    update_ಗಣ_pool_write(s, e, shd, ಗಣ, &desc_pool_write_info);

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ ff_vk_shader_update_ತಳ್ಳು_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_ಬಿಟ್ಟುಗಳು stage,
                                    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, size_t ಗಾತ್ರ_2, ಶೂನ್ಯ *src)
{
    FFVulkanFunctions *vk = &s->vkfn;
    vk->Cmd_ತಳ್ಳು_Constants(e->buf, shd->pipeline_layout,
                         stage, ಸ್ಥಾನಾಂತರ, ಗಾತ್ರ_2, src);
}

ಶೂನ್ಯ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ಸ್ಥಿರಾಂಕ FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;
    ಸ್ಥಿರಾಂಕ FFVulkan_Shader_ದತ್ತಾಂಶ *sd = get_shd_ದತ್ತಾಂಶ(e, shd);

    vk->CmdBindPipeline(e->buf, shd->bind_ಬಿಂದು, shd->pipeline);

    ಆದರೆ (sd && sd->nb_descriptor_sets) {
        ಆದರೆ (!shd->use_ತಳ್ಳು) {
            vk->CmdBindDescriptorSets(e->buf, shd->bind_ಬಿಂದು, shd->pipeline_layout,
                                      0, sd->nb_descriptor_sets,
                                      &sd->desc_sets[e->idx*sd->nb_descriptor_sets],
                                      0, ಖಾಲಿ);
        }
    }
}

ಶೂನ್ಯ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd)
{
    FFVulkanFunctions *vk = &s->vkfn;

#ಆದರೆ 0
    ಆದರೆ (shd->shader.module)
        vk->DestroyShaderModule(s->hwctx->act_dev, shd->shader.module,
                                s->hwctx->alloc);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (shd->pipeline)
        vk->DestroyPipeline(s->hwctx->act_dev, shd->pipeline, s->hwctx->alloc);
    ಆದರೆ (shd->pipeline_layout)
        vk->DestroyPipelineLayout(s->hwctx->act_dev, shd->pipeline_layout,
                                  s->hwctx->alloc);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < shd->nb_descriptor_sets; i++)
        ಆದರೆ (shd->desc_layout[i])
            vk->Destroy_Descriptor_ಗಣ_Layout(s->hwctx->act_dev, shd->desc_layout[i],
                                           s->hwctx->alloc);
}

ಶೂನ್ಯ ff_vk_uninit(FFVulkanContext *s)
{
    av_freep(&s->query_props);
    av_freep(&s->qf_props);
    av_freep(&s->video_props);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    av_freep(&s->ownership_props);
#ಆದರೆ_ಅಂತ್ಯ
    av_freep(&s->coop_mat_props);
    av_freep(&s->host_image_copy_layouts);
    av_refstruct_pool_uninit(&s->imageviews_pool);

    av_ಬಫರ್_unref(&s->device_ref);
    av_ಬಫರ್_unref(&s->ಚೌಕಟ್ಟುಗಳು_ref);
}

ಪೂರ್ಣಾಂಕ ff_vk_init(FFVulkanContext *s, ಶೂನ್ಯ *log_ಪೋಷಕ,
               AVBufferRef *device_ref, AVBufferRef *ಚೌಕಟ್ಟುಗಳು_ref)
{
    ಪೂರ್ಣಾಂಕ err;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass vulkan_context_class = {
        .class_name       = "vk",
        .ಆವೃತ್ತಿ          = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
        .ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ = offsetof(FFVulkanContext, log_ಪೋಷಕ),
    };

    memset(s, 0, ಗಾತ್ರ(*s));
    s->log_ಪೋಷಕ = log_ಪೋಷಕ;
    s->class      = &vulkan_context_class;

    ಆದರೆ (ಚೌಕಟ್ಟುಗಳು_ref) {
        s->ಚೌಕಟ್ಟುಗಳು_ref = av_ಬಫರ್_ref(ಚೌಕಟ್ಟುಗಳು_ref);
        ಆದರೆ (!s->ಚೌಕಟ್ಟುಗಳು_ref)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        s->ಚೌಕಟ್ಟುಗಳು = (AVHWFramesContext *)s->ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
        s->hwfc = s->ಚೌಕಟ್ಟುಗಳು->hwctx;

        device_ref = s->ಚೌಕಟ್ಟುಗಳು->device_ref;
    }

    s->device_ref = av_ಬಫರ್_ref(device_ref);
    ಆದರೆ (!s->device_ref) {
        ff_vk_uninit(s);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    s->device = (AVHWDeviceContext *)s->device_ref->ದತ್ತಾಂಶ;
    s->hwctx = s->device->hwctx;

    s->extensions = ff_vk_extensions_ಗಮ್ಯ_ಮುಖವಾಡ(s->hwctx->enabled_dev_extensions,
                                             s->hwctx->nb_enabled_dev_extensions);
    s->extensions |= ff_vk_extensions_ಗಮ್ಯ_ಮುಖವಾಡ(s->hwctx->enabled_inst_extensions,
                                              s->hwctx->nb_enabled_inst_extensions);

    err = ff_vk_ತುಂಬು_functions(s->device, &s->vkfn, s->extensions, 1, 1);
    ಆದರೆ (err < 0) {
        ff_vk_uninit(s);
        ಹಿಂತಿರುಗಿ err;
    }

    err = ff_vk_ತುಂಬು_props(s);
    ಆದರೆ (err < 0) {
        ff_vk_uninit(s);
        ಹಿಂತಿರುಗಿ err;
    }

    ಹಿಂತಿರುಗಿ 0;
}
