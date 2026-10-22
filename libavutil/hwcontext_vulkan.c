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

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿಸು VK_ENABLE_BETA_EXTENSIONS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
#ಅನ್ತರ್ಭಾವ <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#ಅನ್ತರ್ಭಾವ <versionhelpers.h>
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "thread.h"

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_vulkan.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "uuid.h"

#ಅನ್ತರ್ಭಾವ "vulkan.h"
#ಅನ್ತರ್ಭಾವ "vulkan_loader.h"

#ಆದರೆ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_LIBDRM
#ಆದರೆ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ <va/va_drmcommon.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __linux__
#ಅನ್ತರ್ಭಾವ <sys/sysmacros.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <sys/stat.h>
#ಅನ್ತರ್ಭಾವ <xf86drm.h>
#ಅನ್ತರ್ಭಾವ <drm_fourcc.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_LINUX_DMA_BUF_H
#ಅನ್ತರ್ಭಾವ <sys/ioctl.h>
#ಅನ್ತರ್ಭಾವ <linux/dma-buf.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_CUDA
#ಅನ್ತರ್ಭಾವ "hwcontext_cuda_internal.h"
#ಅನ್ತರ್ಭಾವ "cuda_check.h"
#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    Vk_Physical_Device_Workgroup_ಸ್ಮರಣೆ_Explicit_Layout_Features_KHR explicit_mem_layout;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    Vk_Physical_Device_Shader_Long_ಸದಿಶ_Features_EXT long_ಸದಿಶ;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_zero_initialize_device_ಸ್ಮರಣೆ
    Vk_Physical_Device_Zero_Initialize_Device_ಸ್ಮರಣೆ_Features_EXT zero_initialize;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#ಆದರೆ_ಅಂತ್ಯ

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#ಆದರೆ_ಅಂತ್ಯ

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    Vk_Physical_Device_Cooperative_ಮಾತೃಕೆ_Features_KHR cooperative_ಮಾತೃಕೆ;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR ಆಂತರಿಕ_ಸರತಿ_sync;
#ಆದರೆ_ಅಂತ್ಯ
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    ಶೂನ್ಯ *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkan_Device_ಸರತಿ_Family *compute_qf;
    AVVulkan_Device_ಸರತಿ_Family *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    Vk_Physical_Device_ಸ್ಮರಣೆ_Properties mprops;
    Vk_Physical_Device_External_ಸ್ಮರಣೆ_Host_Properties_EXT hprops;
    VkPhysicalDeviceDriverProperties dprops;

    /* Opaque FD external semaphore properties */
    VkExternalSemaphoreProperties ext_sem_props_opaque;

    /* Enabled features */
    VulkanDeviceFeatures feats;

    /* Queues */
    pthread_mutex_t **qf_mutex;
    uint32_t nb_tot_qfs;
    uint32_t img_qfs[64];
    uint32_t nb_img_qfs;

    /* Debug callback */
    VkDebugUtilsMessengerEXT debug_ctx;

    /* Settings */
    ಪೂರ್ಣಾಂಕ use_ರೇಖೀಯ_images;

    /* Option to allocate all image planes in a single allocation */
    ಪೂರ್ಣಾಂಕ contiguous_planes;

    /* Disable multiplane images */
    ಪೂರ್ಣಾಂಕ disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    ಪೂರ್ಣಾಂಕ avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    ಪೂರ್ಣಾಂಕ transfer_ಸ್ಥಾನಾಂತರ_align;

    /* Maximum queues */
    ಪೂರ್ಣಾಂಕ ಎಲ್ಲೆ_queues;
} VulkanDevicePriv;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context p;

    /* Image conversions */
    FFVkExecPool compute_exec;

    /* Image transfers */
    FFVkExecPool upload_exec;
    FFVkExecPool download_exec;

    /* Temporary buffer pools */
    AVRefStructPool *tmp;

    /* Modifier info list to free at uninit */
    VkImageDrmFormatModifierListCreateInfoEXT *modifier_info;

    /* Properties for DRM modifier for each plane in the image */
    VkDrmFormatModifierPropertiesEXT drm_format_modifier_properties[5];

    /* Set when physical device reports DEDICATED_ONLY for DMA-BUF export (try_export_flags) */
    ಪೂರ್ಣಾಂಕ export_requires_dedicated;
} Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#ಆದರೆ CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternal_ಸ್ಮರಣೆ ext_mem[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    CUmipmappedArray cu_mma[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    CUarray cu_array[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    CUexternalSemaphore cu_sem[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    HANDLE ext_mem_handle[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    HANDLE ext_sem_handle[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
} AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ;

/* Initialize all structs in VulkanDeviceFeatures */
ಸ್ಥಿರ ಶೂನ್ಯ device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
{
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanContext *s = &p->vkctx;

    feats->device = (VkPhysicalDeviceFeatures2) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    };

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vulkan_1_1, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vulkan_1_2, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vulkan_1_3, FF_VK_EXT_NO_FLAG,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES);

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->timeline_semaphore, FF_VK_EXT_PORTABILITY_SUBSET,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->subgroup_rotate, FF_VK_EXT_SUBGROUP_ROTATE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_ROTATE_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->host_image_copy, FF_VK_EXT_HOST_IMAGE_COPY,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_FEATURES_EXT);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_ಸದಿಶ, FF_VK_EXT_LONG_ಸದಿಶ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ಸದಿಶ_FEATURES_EXT);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_zero_initialize_device_ಸ್ಮರಣೆ
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_ಸ್ಮರಣೆ_FEATURES_EXT);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_ಮಾತೃಕೆ, FF_VK_EXT_COOP_ಮಾತೃಕೆ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ಮಾತೃಕೆ_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_ಸ್ಮರಣೆ_EXPLICIT_LAYOUT_FEATURES_KHR);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->ಆಂತರಿಕ_ಸರತಿ_sync, FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#ಆದರೆ_ಅಂತ್ಯ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
ಸ್ಥಿರ ಶೂನ್ಯ device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#ವ್ಯಾಖ್ಯಾನಿಸು COPY_VAL(VAL)        \
    ಮಾಡು {                     \
        dst->VAL = src->VAL; \
    } ಆಗ (0)              \

    COPY_VAL(device.features.shaderImageGatherExtended);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);
    COPY_VAL(device.features.fragmentStoresAndAtomics);
    COPY_VAL(device.features.ಶೃಂಗ_Pipeline_Stores_And_Atomics);
    COPY_VAL(device.features.shaderInt64);
    COPY_VAL(device.features.shaderInt16);
    COPY_VAL(device.features.shaderFloat64);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);

    COPY_VAL(vulkan_1_1.samplerYcbcrConversion);
    COPY_VAL(vulkan_1_1.storage_ತಳ್ಳು_Constant16);
    COPY_VAL(vulkan_1_1.storage_Buffer16_ಬಿಟ್_Access);
    COPY_VAL(vulkan_1_1.ಏಕರೂಪ_And_Storage_Buffer16_ಬಿಟ್_Access);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalar_ಖಂಡ_Layout);
    COPY_VAL(vulkan_1_2.ಬಫರ್_Device_ವಿಳಾಸ);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_ತಳ್ಳು_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storage_Buffer8_ಬಿಟ್_Access);
    COPY_VAL(vulkan_1_2.ಏಕರೂಪ_And_Storage_Buffer8_ಬಿಟ್_Access);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_ಬಫರ್_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkan_ಸ್ಮರಣೆ_Model);
    COPY_VAL(vulkan_1_2.vulkan_ಸ್ಮರಣೆ_Model_Device_Scope);
    COPY_VAL(vulkan_1_2.vulkan_ಸ್ಮರಣೆ_Model_Availability_Visibility_Chains);
    COPY_VAL(vulkan_1_2.ಏಕರೂಪ_ಬಫರ್_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_ಏಕರೂಪ_ಬಫರ್_Array_Non_ಏಕರೂಪ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Sampled_Image_Array_Non_ಏಕರೂಪ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_ಬಫರ್_Array_Non_ಏಕರೂಪ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_Image_Array_Non_ಏಕರೂಪ_Indexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.compute_ತುಂಬಿದ_Subgroups);
    COPY_VAL(vulkan_1_3.subgroup_ಗಾತ್ರ_Control);
    COPY_VAL(vulkan_1_3.shader_Zero_Initialize_Workgroup_ಸ್ಮರಣೆ);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    COPY_VAL(long_ಸದಿಶ.long_ಸದಿಶ_2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_zero_initialize_device_ಸ್ಮರಣೆ
    COPY_VAL(zero_initialize.zero_Initialize_Device_ಸ್ಮರಣೆ);
#ಆದರೆ_ಅಂತ್ಯ

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#ಆದರೆ_ಅಂತ್ಯ

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_ಮಾತೃಕೆ.cooperative_ಮಾತೃಕೆ_2);

    COPY_VAL(atomic_float.shader_ಬಫರ್_Float32_Atomics);
    COPY_VAL(atomic_float.shader_ಬಫರ್_Float32_Atomic_ಕೂಡಿಸು);

    COPY_VAL(explicit_mem_layout.workgroup_ಸ್ಮರಣೆ_Explicit_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_ಸ್ಮರಣೆ_Explicit_Layout_Scalar_ಖಂಡ_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_ಸ್ಮರಣೆ_Explicit_Layout8_ಬಿಟ್_Access);
    COPY_VAL(explicit_mem_layout.workgroup_ಸ್ಮರಣೆ_Explicit_Layout16_ಬಿಟ್_Access);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    COPY_VAL(ಆಂತರಿಕ_ಸರತಿ_sync.internallySynchronizedQueues);
#ಆದರೆ_ಅಂತ್ಯ

    COPY_VAL(optical_flow.opticalFlow);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು COPY_VAL
}

#ವ್ಯಾಖ್ಯಾನಿಸು ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_ಬಿಟ್ | VK_IMAGE_ASPECT_PLANE_1_ಬಿಟ್)
#ವ್ಯಾಖ್ಯಾನಿಸು ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_ಬಿಟ್ | VK_IMAGE_ASPECT_PLANE_1_ಬಿಟ್ | VK_IMAGE_ASPECT_PLANE_2_ಬಿಟ್)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ FFVk_Format_ನಮೂದು {
    VkFormat vkf;
    ಎಣಿಕೆ AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    ಪೂರ್ಣಾಂಕ vk_planes;
    ಪೂರ್ಣಾಂಕ nb_images;
    ಪೂರ್ಣಾಂಕ nb_images_fallback;
    ಸ್ಥಿರಾಂಕ VkFormat fallback[5];
} vk_formats_list[] = {
    /* Gray formats */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GRAY8,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY10,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY12,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY14,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GRAY32,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GRAYF32, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32_SFLOAT } },

    /* RGB formats */
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGRA,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGBA,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8_UNORM,             AV_PIX_FMT_RGB24,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8_UNORM             } },
    { VK_FORMAT_B8G8R8_UNORM,             AV_PIX_FMT_BGR24,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_B8G8R8_UNORM             } },
    { VK_FORMAT_R16G16B16_UNORM,          AV_PIX_FMT_RGB48,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16_UNORM          } },
    { VK_FORMAT_R16G16B16A16_UNORM,       AV_PIX_FMT_RGBA64,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM       } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGR0,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGB0,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, AV_PIX_FMT_X2RGB10, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_A2B10G10R10_UNORM_PACK32, AV_PIX_FMT_X2BGR10, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_A2B10G10R10_UNORM_PACK32 } },
    { VK_FORMAT_R32G32B32_SFLOAT,         AV_PIX_FMT_RGBF32,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32G32B32_SFLOAT         } },
    { VK_FORMAT_R16G16B16A16_SFLOAT,      AV_PIX_FMT_RGBAF16, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_SFLOAT      } },
    { VK_FORMAT_R32G32B32A32_SFLOAT,      AV_PIX_FMT_RGBAF32, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32G32B32A32_SFLOAT      } },
    { VK_FORMAT_R32G32B32_UINT,           AV_PIX_FMT_RGB96,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32G32B32_UINT           } },
    { VK_FORMAT_R32G32B32A32_UINT,        AV_PIX_FMT_RGBA128, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R32G32B32A32_UINT        } },

    /* Planar RGB */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRP,     VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP10,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP12,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP14,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP16,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRPF16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT  } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRPF32,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* XYZ */
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_XYZP12,   VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar RGB + Alpha */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRAP,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP10,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP12,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP14,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRAPF16, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GBRAP32,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRAPF32, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* Bayer */
    { VK_FORMAT_R16_UNORM, AV_PIX_FMT_BAYER_RGGB16, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16_UNORM } },

    /* Two-plane 420 YUV at 8, 10, 12 and 16 bits */
    { VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,                  AV_PIX_FMT_NV12, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8G8_UNORM   } },
    { VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16, AV_PIX_FMT_P010, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16, AV_PIX_FMT_P012, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,               AV_PIX_FMT_P016, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },

    /* Two-plane 422 YUV at 8, 10 and 16 bits */
    { VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,                  AV_PIX_FMT_NV16, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8G8_UNORM   } },
    { VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16, AV_PIX_FMT_P210, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16, AV_PIX_FMT_P212, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,               AV_PIX_FMT_P216, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },

    /* Two-plane 444 YUV at 8, 10 and 16 bits */
    { VK_FORMAT_G8_B8R8_2PLANE_444_UNORM,                  AV_PIX_FMT_NV24, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8G8_UNORM   } },
    { VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16, AV_PIX_FMT_P410, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16, AV_PIX_FMT_P412, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },
    { VK_FORMAT_G16_B16R16_2PLANE_444_UNORM,               AV_PIX_FMT_P416, ASPECT_2PLANE, 2, 1, 2, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16G16_UNORM } },

    /* Three-plane 420, 422, 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,    AV_PIX_FMT_YUV420P,   ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM  } },
    { VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM, AV_PIX_FMT_YUV420P10, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM, AV_PIX_FMT_YUV420P12, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM, AV_PIX_FMT_YUV420P16, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,    AV_PIX_FMT_YUV422P,   ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM  } },
    { VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM, AV_PIX_FMT_YUV422P10, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM, AV_PIX_FMT_YUV422P12, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM, AV_PIX_FMT_YUV422P16, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,    AV_PIX_FMT_YUV444P,   ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM,  VK_FORMAT_R8_UNORM  } },
    { VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM, AV_PIX_FMT_YUV444P10, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM, AV_PIX_FMT_YUV444P12, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },
    { VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM, AV_PIX_FMT_YUV444P16, ASPECT_3PLANE, 3, 1, 3, { VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM, VK_FORMAT_R16_UNORM } },

    /* Single plane 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_G8B8G8R8_422_UNORM,                     AV_PIX_FMT_YUYV422, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_B8G8R8G8_422_UNORM,                     AV_PIX_FMT_UYVY422, VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, AV_PIX_FMT_Y210,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, AV_PIX_FMT_Y212,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G16B16G16R16_422_UNORM,                 AV_PIX_FMT_Y216,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },

    /* Planar YUVA 420 at 8, 10 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA420P,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P10,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA422P,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P10,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P12,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA444P,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P10,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P12,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P16,  VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Single plane 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32,               AV_PIX_FMT_XV30,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,     AV_PIX_FMT_XV36,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_R16G16B16A16_UNORM,                     AV_PIX_FMT_XV48,    VK_IMAGE_ASPECT_COLOR_ಬಿಟ್, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ಸ್ಥಿರಾಂಕ VkFormat *av_vkfmt_from_pixfmt(ಎಣಿಕೆ AVPixelFormat p)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_vk_formats_list; i++)
        ಆದರೆ (vk_formats_list[i].pixfmt == p)
            ಹಿಂತಿರುಗಿ vk_formats_list[i].fallback;
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ FFVk_Format_ನಮೂದು *vk_ಕಂಡುಹಿಡಿ_format_ನಮೂದು(ಎಣಿಕೆ AVPixelFormat p)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_vk_formats_list; i++)
        ಆದರೆ (vk_formats_list[i].pixfmt == p)
            ಹಿಂತಿರುಗಿ &vk_formats_list[i];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, ಎಣಿಕೆ AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು], /* Output format list */
                              ಪೂರ್ಣಾಂಕ *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              ಪೂರ್ಣಾಂಕ disable_multiplane, ಪೂರ್ಣಾಂಕ need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ಸ್ಥಿರಾಂಕ VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ಬಿಟ್ |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_ಬಿಟ್  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_ಬಿಟ್;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_vk_formats_list; i++) {
        ಆದರೆ (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ಮುಂದಿನ = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            ಪೂರ್ಣಾಂಕ basics_primary = 0, basics_secondary = 0;
            ಪೂರ್ಣಾಂಕ storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_ರೇಖೀಯ ?
                             fprops.ರೇಖೀಯ_Tiling_Features : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ಬಿಟ್);

            ಆದರೆ (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_ರೇಖೀಯ ?
                                  fprops.ರೇಖೀಯ_Tiling_Features : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ಬಿಟ್);
            } ಇಲ್ಲದಿದ್ದರೆ {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            ಆದರೆ (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                ಆದರೆ (fmts) {
                    ಆದರೆ (vk_formats_list[i].nb_images > 1) {
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                ಆದರೆ (nb_images)
                    *nb_images = 1;
                ಆದರೆ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ಆದರೆ (supported_usage)
                    *supported_usage = ff_vk_map_feats_ಗಮ್ಯ_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_ಬಿಟ್ : 0);
                ಹಿಂತಿರುಗಿ 0;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                ಆದರೆ (fmts) {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                ಆದರೆ (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                ಆದರೆ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ಆದರೆ (supported_usage)
                    *supported_usage = ff_vk_map_feats_ಗಮ್ಯ_usage(feats_secondary);
                ಹಿಂತಿರುಗಿ 0;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ AVERROR(ENOTSUP);
            }
        }
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

#ಆದರೆ CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pName);
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ತುಂಬು_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#ಆದರೆ CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *lib_ಹೆಸರುಗಳು[] = {
#ಆದರೆ defined(_WIN32)
        "vulkan-1.dll",
#ಅಥವಾಆದರೆ defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#ಇಲ್ಲದಿದ್ದರೆ
        "libvulkan.so.1",
        "libvulkan.so",
#ಆದರೆ_ಅಂತ್ಯ
    };

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(lib_ಹೆಸರುಗಳು); i++) {
        p->libvulkan = dlopen(lib_ಹೆಸರುಗಳು[i], RTLD_NOW | RTLD_LOCAL);
        ಆದರೆ (p->libvulkan)
            ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#ಆದರೆ_ಅಂತ್ಯ /* CONFIG_VULKAN_STATIC */

    ಹಿಂತಿರುಗಿ 0;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VulkanOptExtension {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VulkanOptExtension optional_instance_exts[] = {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#ಆದರೆ_ಅಂತ್ಯ
    { 0 },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_ತಳ್ಳು_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_ಮಾತೃಕೆ_EXTENSION_NAME,               FF_VK_EXT_COOP_ಮಾತೃಕೆ            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_ಸ್ಮರಣೆ_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    { VK_EXT_SHADER_LONG_ಸದಿಶ_EXTENSION_NAME,               FF_VK_EXT_LONG_ಸದಿಶ            },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_zero_initialize_device_ಸ್ಮರಣೆ
    { VK_EXT_ZERO_INITIALIZE_DEVICE_ಸ್ಮರಣೆ_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#ಆದರೆ_ಅಂತ್ಯ
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC    },
#ಆದರೆ_ಅಂತ್ಯ
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_ಸ್ಮರಣೆ     },
    { VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_ಸ್ಮರಣೆ },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_ಸ್ಮರಣೆ   },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    { VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_ಸ್ಮರಣೆ  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#ಆದರೆ_ಅಂತ್ಯ

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_ಸರತಿ_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_ಸರತಿ            },
    { VK_KHR_VIDEO_ENCODE_ಸರತಿ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_ಸರತಿ     },
    { VK_KHR_VIDEO_DECODE_ಸರತಿ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_ಸರತಿ     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#ಆದರೆ_ಅಂತ್ಯ
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **av_vk_get_optional_instance_extensions(ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **exts = av_malloc_array(ಗಾತ್ರ(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    ಆದರೆ (!exts)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < (ಪೂರ್ಣಾಂಕ)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *ಎಣಿಕೆ_2 = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    ಹಿಂತಿರುಗಿ exts;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **av_vk_get_optional_device_extensions(ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **exts = av_malloc_array(ಗಾತ್ರ(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    ಆದರೆ (!exts)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *ಎಣಿಕೆ_2 = FF_ARRAY_ELEMS(optional_device_exts);
    ಹಿಂತಿರುಗಿ exts;
}

ಸ್ಥಿರ VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(Vk_Debug_Utils_ಸಂದೇಶ_Severity_Flag_ಬಿಟ್ಟುಗಳು_EXT severity,
                                    Vk_Debug_Utils_ಸಂದೇಶ_Type_Flags_EXT ಸಂದೇಶ_Type,
                                    ಸ್ಥಿರಾಂಕ Vk_Debug_Utils_Messenger_Callback_ದತ್ತಾಂಶ_EXT *ದತ್ತಾಂಶ,
                                    ಶೂನ್ಯ *priv)
{
    ಪೂರ್ಣಾಂಕ l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    ಆಯ್ಕೆ (ದತ್ತಾಂಶ->ಸಂದೇಶ_Id_ಸಂಖ್ಯೆ) {
    ಸ್ಥಿತಿ 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    ಸ್ಥಿತಿ 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        ಹಿಂತಿರುಗಿ VK_FALSE;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    ಆಯ್ಕೆ (severity) {
    ಸ್ಥಿತಿ VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_VERBOSE_ಬಿಟ್_EXT: l = AV_LOG_VERBOSE; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_INFO_ಬಿಟ್_EXT:    l = AV_LOG_INFO;    ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_WARNING_ಬಿಟ್_EXT: l = AV_LOG_WARNING; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_ERROR_ಬಿಟ್_EXT:   l = AV_LOG_ERROR;   ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:                                              l = AV_LOG_DEBUG;   ನಿಲ್ಲಿಸು;
    }

    av_log(ctx, l, "%s\n", ದತ್ತಾಂಶ->p_ಸಂದೇಶ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ದತ್ತಾಂಶ->cmd_Buf_Label_ಎಣಿಕೆ; i++)
        av_log(ctx, l, "\t%i: %s\n", i, ದತ್ತಾಂಶ->pCmdBufLabels[i].pLabelName);

    ಹಿಂತಿರುಗಿ VK_FALSE;
}

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(list, ಎಣಿಕೆ_2, val)                                      \
    ಮಾಡು {                                                                       \
        list = av_realloc_array(list, ++ಎಣಿಕೆ_2, ಗಾತ್ರ(*list));                 \
        ಆದರೆ (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            ಹೋಗು fail;                                                         \
        }                                                                      \
        list[ಎಣಿಕೆ_2 - 1] = av_strdup(val);                                      \
        ಆದರೆ (!list[ಎಣಿಕೆ_2 - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            ಹೋಗು fail;                                                         \
        }                                                                      \
    } ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು RELEASE_PROPS(props, ಎಣಿಕೆ_2)                                            \
    ಆದರೆ (props) {                                                               \
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; i++)                                        \
            av_free((ಶೂನ್ಯ *)((props)[i]));                                     \
        av_free((ಶೂನ್ಯ *)props);                                                \
    }

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_ಗಾತ್ರ max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < p->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ; i++) {
        ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Type type = p->mprops.ಸ್ಮರಣೆ_Types[i];
        ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_ರಾಶಿ ರಾಶಿ = p->mprops.ಸ್ಮರಣೆ_Heaps[type.ರಾಶಿ_ಸೂಚ್ಯಂಕ_2];
        ಆದರೆ (!(type.propertyFlags & VK_ಸ್ಮರಣೆ_PROPERTY_DEVICE_LOCAL_ಬಿಟ್))
            ಮುಂದುವರಿ;
        max_vram = FFMAX(max_vram, ರಾಶಿ.ಗಾತ್ರ_2);
        ಆದರೆ (type.propertyFlags & VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್)
            max_visible_vram = FFMAX(max_visible_vram, ರಾಶಿ.ಗಾತ್ರ_2);
    }

    ಹಿಂತಿರುಗಿ max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_extensions(AVHWDeviceContext *ctx, ಪೂರ್ಣಾಂಕ dev, AVDictionary *opts,
                            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ **dst, uint32_t *ಅಂಕೆ,
                            ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ debug_ಬಹುಲಕ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *tstr;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **extension_ಹೆಸರುಗಳು = ಖಾಲಿ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಂಕ err = 0, ಸಿಕ್ಕಿತು, extensions_ಸಿಕ್ಕಿತು = 0;

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mod;
    ಪೂರ್ಣಾಂಕ optional_exts_ಅಂಕೆ;
    uint32_t sup_ext_ಎಣಿಕೆ;
    ಅಕ್ಷರ *user_exts_str = ಖಾಲಿ;
    AVDictionary_ನಮೂದು *user_exts;
    VkExtensionProperties *sup_ext;
    ಸ್ಥಿರಾಂಕ VulkanOptExtension *optional_exts;

    ಆದರೆ (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_ಅಂಕೆ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", ಖಾಲಿ, 0);
        ಆದರೆ (user_exts) {
            user_exts_str = av_strdup(user_exts->ಮೌಲ್ಯ);
            ಆದರೆ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(ಖಾಲಿ, &sup_ext_ಎಣಿಕೆ, ಖಾಲಿ);
        sup_ext = av_malloc_array(sup_ext_ಎಣಿಕೆ, ಗಾತ್ರ(VkExtensionProperties));
        ಆದರೆ (!sup_ext)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(ಖಾಲಿ, &sup_ext_ಎಣಿಕೆ, sup_ext);
    } ಇಲ್ಲದಿದ್ದರೆ {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_ಅಂಕೆ = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", ಖಾಲಿ, 0);
        ಆದರೆ (user_exts) {
            user_exts_str = av_strdup(user_exts->ಮೌಲ್ಯ);
            ಆದರೆ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ಖಾಲಿ,
                                               &sup_ext_ಎಣಿಕೆ, ಖಾಲಿ);
        sup_ext = av_malloc_array(sup_ext_ಎಣಿಕೆ, ಗಾತ್ರ(VkExtensionProperties));
        ಆದರೆ (!sup_ext)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ಖಾಲಿ,
                                               &sup_ext_ಎಣಿಕೆ, sup_ext);
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < optional_exts_ಅಂಕೆ; i++) {
        tstr = optional_exts[i].name;
        ಸಿಕ್ಕಿತು = 0;

        /* Check if the device has ReBAR for host image copies */
        ಆದರೆ (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            ಮುಂದುವರಿ;

        ಆದರೆ (dev &&
            ((debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            ಮುಂದುವರಿ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಆದರೆ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ಸಿಕ್ಕಿತು = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!ಸಿಕ್ಕಿತು)
            ಮುಂದುವರಿ;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(extension_ಹೆಸರುಗಳು, extensions_ಸಿಕ್ಕಿತು, tstr);
    }

    ಆದರೆ (!dev &&
        ((debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        ಸಿಕ್ಕಿತು = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಆದರೆ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ಸಿಕ್ಕಿತು = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (ಸಿಕ್ಕಿತು) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(extension_ಹೆಸರುಗಳು, extensions_ಸಿಕ್ಕಿತು, tstr);
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ಹೋಗು fail;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_shader_relaxed_extended_instruction
    ಆದರೆ ((debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        ಸಿಕ್ಕಿತು = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಆದರೆ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ಸಿಕ್ಕಿತು = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!ಸಿಕ್ಕಿತು) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ಹೋಗು fail;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (user_exts_str) {
        ಅಕ್ಷರ *save, *token = av_strtok(user_exts_str, "+", &save);
        ಆಗ (token) {
            ಸಿಕ್ಕಿತು = 0;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
                ಆದರೆ (!strcmp(token, sup_ext[j].extensionName)) {
                    ಸಿಕ್ಕಿತು = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }
            ಆದರೆ (ಸಿಕ್ಕಿತು) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(extension_ಹೆಸರುಗಳು, extensions_ಸಿಕ್ಕಿತು, token);
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(ಖಾಲಿ, "+", &save);
        }
    }

    *dst = extension_ಹೆಸರುಗಳು;
    *ಅಂಕೆ = extensions_ಸಿಕ್ಕಿತು;

    av_free(user_exts_str);
    av_free(sup_ext);
    ಹಿಂತಿರುಗಿ 0;

fail:
    RELEASE_PROPS(extension_ಹೆಸರುಗಳು, extensions_ಸಿಕ್ಕಿತು);
    av_free(user_exts_str);
    av_free(sup_ext);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ **dst, uint32_t *ಅಂಕೆ,
                        ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ *debug_ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    ಪೂರ್ಣಾಂಕ layer_standard_validation_ಸಿಕ್ಕಿತು = 0;

    uint32_t sup_layer_ಎಣಿಕೆ;
    VkLayerProperties *sup_layers;

    AVDictionary_ನಮೂದು *user_layers = av_dict_get(opts, "layers", ಖಾಲಿ, 0);
    ಅಕ್ಷರ *user_layers_str = ಖಾಲಿ;
    ಅಕ್ಷರ *save, *token;

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **enabled_layers = ಖಾಲಿ;
    uint32_t enabled_layers_ಎಣಿಕೆ = 0;

    AVDictionary_ನಮೂದು *debug_opt = av_dict_get(opts, "debug", ಖಾಲಿ, 0);
    ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ ಬಹುಲಕ;

    *debug_ಬಹುಲಕ = ಬಹುಲಕ = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_ಎಣಿಕೆ, ಖಾಲಿ);
    sup_layers = av_malloc_array(sup_layer_ಎಣಿಕೆ, ಗಾತ್ರ(VkLayerProperties));
    ಆದರೆ (!sup_layers)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_ಎಣಿಕೆ, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < sup_layer_ಎಣಿಕೆ; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    ಆದರೆ (!debug_opt && !user_layers)
        ಹೋಗು ಕೊನೆ;

    /* Check for any properly supported validation layer */
    ಆದರೆ (debug_opt) {
        ಆದರೆ (!strcmp(debug_opt->ಮೌಲ್ಯ, "printf")) {
            ಬಹುಲಕ = FF_VULKAN_DEBUG_PRINTF;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(debug_opt->ಮೌಲ್ಯ, "validate")) {
            ಬಹುಲಕ = FF_VULKAN_DEBUG_VALIDATE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(debug_opt->ಮೌಲ್ಯ, "practices")) {
            ಬಹುಲಕ = FF_VULKAN_DEBUG_PRACTICES;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಅಕ್ಷರ *ಕೊನೆ_ptr = ಖಾಲಿ;
            ಪೂರ್ಣಾಂಕ idx = strtol(debug_opt->ಮೌಲ್ಯ, &ಕೊನೆ_ptr, 10);
            ಆದರೆ (ಕೊನೆ_ptr == debug_opt->ಮೌಲ್ಯ || ಕೊನೆ_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->ಮೌಲ್ಯ);
                err = AVERROR(EINVAL);
                ಹೋಗು ಕೊನೆ;
            }
            ಬಹುಲಕ = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    ಆದರೆ ((ಬಹುಲಕ == FF_VULKAN_DEBUG_VALIDATE) ||
        (ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) ||
        (ಬಹುಲಕ == FF_VULKAN_DEBUG_PRACTICES)) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < sup_layer_ಎಣಿಕೆ; i++) {
            ಆದರೆ (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(enabled_layers, enabled_layers_ಎಣಿಕೆ, layer_standard_validation);
                *debug_ಬಹುಲಕ = ಬಹುಲಕ;
                layer_standard_validation_ಸಿಕ್ಕಿತು = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!layer_standard_validation_ಸಿಕ್ಕಿತು) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            ಹೋಗು ಕೊನೆ;
        }
    }

    /* Process any custom layers enabled */
    ಆದರೆ (user_layers) {
        ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು;

        user_layers_str = av_strdup(user_layers->ಮೌಲ್ಯ);
        ಆದರೆ (!user_layers_str) {
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        ಆಗ (token) {
            ಸಿಕ್ಕಿತು = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            ಆದರೆ (!strcmp(layer_standard_validation, token) && layer_standard_validation_ಸಿಕ್ಕಿತು) {
                token = av_strtok(ಖಾಲಿ, "+", &save);
                ನಿಲ್ಲಿಸು;
            }

            /* Try to find the layer in the list of supported layers */
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sup_layer_ಎಣಿಕೆ; j++) {
                ಆದರೆ (!strcmp(token, sup_layers[j].layerName)) {
                    ಸಿಕ್ಕಿತು = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ (ಸಿಕ್ಕಿತು) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                ಕೂಡಿಸು_VAL_ಗಮ್ಯ_LIST(enabled_layers, enabled_layers_ಎಣಿಕೆ, token);

                /* If debug was not set as an option, force it */
                ಆದರೆ (!strcmp(layer_standard_validation, token))
                    *debug_ಬಹುಲಕ = FF_VULKAN_DEBUG_VALIDATE;
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                ಹೋಗು ಕೊನೆ;
            }

            token = av_strtok(ಖಾಲಿ, "+", &save);
        }
    }

fail:
ಕೊನೆ:
    av_free(sup_layers);
    av_free(user_layers_str);

    ಆದರೆ (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_ಎಣಿಕೆ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *dst = enabled_layers;
        *ಅಂಕೆ = enabled_layers_ಎಣಿಕೆ;
    }

    ಹಿಂತಿರುಗಿ err;
}

/* Creates a VkInstance */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ *debug_ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .application_ಆವೃತ್ತಿ_2 = VK_MAKE_ಆವೃತ್ತಿ(LIBAVUTIL_ಆವೃತ್ತಿ_MAJOR,
                                              LIBAVUTIL_ಆವೃತ್ತಿ_MINOR,
                                              LIBAVUTIL_ಆವೃತ್ತಿ_MICRO),
        .pEngineName        = "libavutil",
        .api_ಆವೃತ್ತಿ         = VK_API_ಆವೃತ್ತಿ_1_3,
        .engine_ಆವೃತ್ತಿ      = VK_MAKE_ಆವೃತ್ತಿ(LIBAVUTIL_ಆವೃತ್ತಿ_MAJOR,
                                              LIBAVUTIL_ಆವೃತ್ತಿ_MINOR,
                                              LIBAVUTIL_ಆವೃತ್ತಿ_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    ಆದರೆ (!hwctx->get_proc_addr) {
        err = ತುಂಬು_libvulkan(ctx);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
    }

    err = ff_vk_ತುಂಬು_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    ಆದರೆ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        ಹಿಂತಿರುಗಿ err;
    }

    err = check_layers(ctx, opts, &inst_props.pp_Enabled_Layer_ಹೆಸರುಗಳು,
                       &inst_props.enabled_Layer_ಎಣಿಕೆ, debug_ಬಹುಲಕ);
    ಆದರೆ (err)
        ಹೋಗು fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.pp_Enabled_Extension_ಹೆಸರುಗಳು,
                           &inst_props.enabled_Extension_ಎಣಿಕೆ, *debug_ಬಹುಲಕ);
    hwctx->enabled_inst_extensions = inst_props.pp_Enabled_Extension_ಹೆಸರುಗಳು;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_ಎಣಿಕೆ;
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    /* Enable debug features if needed */
    ಆದರೆ (*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_VALIDATE) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_ಸ್ಥಾನ_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_ಮುಂದಿನ = &validation_features;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_ಸ್ಥಾನ_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_ಮುಂದಿನ = &validation_features;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRACTICES) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_ಉತ್ತಮ_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_ಮುಂದಿನ = &validation_features;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < inst_props.enabled_Extension_ಎಣಿಕೆ; i++) {
        ಆದರೆ (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.pp_Enabled_Extension_ಹೆಸರುಗಳು[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_ಬಿಟ್_KHR;
            ನಿಲ್ಲಿಸು;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಹೋಗು fail;
    }

    err = ff_vk_ತುಂಬು_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    ಆದರೆ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        ಹೋಗು fail;
    }

    /* Setup debugging callback if needed */
    ಆದರೆ ((*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_ಬಹುಲಕ == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .ಸಂದೇಶ_Severity = VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_VERBOSE_ಬಿಟ್_EXT |
                               VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_INFO_ಬಿಟ್_EXT    |
                               VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_WARNING_ಬಿಟ್_EXT |
                               VK_DEBUG_UTILS_ಸಂದೇಶ_SEVERITY_ERROR_ಬಿಟ್_EXT,
            .ಸಂದೇಶ_Type = VK_DEBUG_UTILS_ಸಂದೇಶ_TYPE_GENERAL_ಬಿಟ್_EXT    |
                           VK_DEBUG_UTILS_ಸಂದೇಶ_TYPE_VALIDATION_ಬಿಟ್_EXT |
                           VK_DEBUG_UTILS_ಸಂದೇಶ_TYPE_PERFORMANCE_ಬಿಟ್_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .p_User_ದತ್ತಾಂಶ = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.pp_Enabled_Layer_ಹೆಸರುಗಳು, inst_props.enabled_Layer_ಎಣಿಕೆ);
    ಹಿಂತಿರುಗಿ err;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_ಗಾತ್ರ]; /* Will use this first unless !has_uuid */
    ಪೂರ್ಣಾಂಕ has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ; /* Finally fall back to index */
} VulkanDeviceSelection;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *vk_dev_type(ಎಣಿಕೆ VkPhysicalDeviceType type)
{
    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: ಹಿಂತಿರುಗಿ "integrated";
    ಸ್ಥಿತಿ VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   ಹಿಂತಿರುಗಿ "discrete";
    ಸ್ಥಿತಿ VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    ಹಿಂತಿರುಗಿ "virtual";
    ಸ್ಥಿತಿ VK_PHYSICAL_DEVICE_TYPE_CPU:            ಹಿಂತಿರುಗಿ "software";
    ಪೂರ್ವನಿಯೋಜಿತ:                                     ಹಿಂತಿರುಗಿ "unknown";
    }
}

/* Finds a device */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಕಂಡುಹಿಡಿ_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    ಪೂರ್ಣಾಂಕ err = 0, choice = -1;
    uint32_t ಅಂಕೆ;
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = ಖಾಲಿ;
    VkPhysicalDeviceIDProperties *idp = ಖಾಲಿ;
    VkPhysicalDeviceProperties2 *prop = ಖಾಲಿ;
    VkPhysicalDeviceDriverProperties *driver_prop = ಖಾಲಿ;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = ಖಾಲಿ;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ಅಂಕೆ, ಖಾಲಿ);
    ಆದರೆ (ret != VK_SUCCESS || !ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR(ENODEV);
    }

    devices = av_malloc_array(ಅಂಕೆ, ಗಾತ್ರ(VkPhysicalDevice));
    ಆದರೆ (!devices)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ಅಂಕೆ, devices);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    }

    prop = av_calloc(ಅಂಕೆ, ಗಾತ್ರ(*prop));
    ಆದರೆ (!prop) {
        err = AVERROR(ENOMEM);
        ಹೋಗು ಕೊನೆ;
    }

    idp = av_calloc(ಅಂಕೆ, ಗಾತ್ರ(*idp));
    ಆದರೆ (!idp) {
        err = AVERROR(ENOMEM);
        ಹೋಗು ಕೊನೆ;
    }

    driver_prop = av_calloc(ಅಂಕೆ, ಗಾತ್ರ(*driver_prop));
    ಆದರೆ (!driver_prop) {
        err = AVERROR(ENOMEM);
        ಹೋಗು ಕೊನೆ;
    }

    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(ಅಂಕೆ, ಗಾತ್ರ(*drm_prop));
        ಆದರೆ (!drm_prop) {
            err = AVERROR(ENOMEM);
            ಹೋಗು ಕೊನೆ;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].p_ಮುಂದಿನ = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].p_ಮುಂದಿನ = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].p_ಮುಂದಿನ = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    ಆದರೆ (select->has_uuid) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
            ಆದರೆ (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_ಗಾತ್ರ)) {
                choice = i;
                ಹೋಗು ಕೊನೆ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
            ಆದರೆ ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                ಹೋಗು ಕೊನೆ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(prop[i].properties.deviceName, select->name)) {
                choice = i;
                ಹೋಗು ಕೊನೆ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
            ಆದರೆ (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                ಹೋಗು ಕೊನೆ;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        ಹೋಗು ಕೊನೆ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
            ಆದರೆ (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                ಹೋಗು ಕೊನೆ;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (select->ಸೂಚ್ಯಂಕ < ಅಂಕೆ) {
            choice = select->ಸೂಚ್ಯಂಕ;
            ಹೋಗು ಕೊನೆ;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->ಸೂಚ್ಯಂಕ);
        err = AVERROR(ENODEV);
        ಹೋಗು ಕೊನೆ;
    }

ಕೊನೆ:
    ಆದರೆ (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_ಮುಂದಿನ = ಖಾಲಿ;
        p->dprops = driver_prop[choice];
        p->dprops.p_ಮುಂದಿನ = ಖಾಲಿ;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    ಹಿಂತಿರುಗಿ err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ pick_ಸರತಿ_family(Vk_ಸರತಿ_Family_Properties2 *qf, uint32_t ಅಂಕೆ_qf,
                                    Vk_ಸರತಿ_Flag_ಬಿಟ್ಟುಗಳು flags)
{
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = -1;
    uint32_t min_score = UINT32_MAX;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_qf; i++) {
        Vk_ಸರತಿ_Flag_ಬಿಟ್ಟುಗಳು qflags = qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        ಆದರೆ ((flags & VK_ಸರತಿ_TRANSFER_ಬಿಟ್) &&
            (qflags & (VK_ಸರತಿ_GRAPHICS_ಬಿಟ್ | VK_ಸರತಿ_COMPUTE_ಬಿಟ್)))
            qflags |= VK_ಸರತಿ_TRANSFER_ಬಿಟ್;

        ಆದರೆ (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].ಸರತಿ_Family_Properties.timestamp_Valid_ಬಿಟ್ಟುಗಳು;
            ಆದರೆ (score < min_score) {
                ಸೂಚ್ಯಂಕ = i;
                min_score = score;
            }
        }
    }

    ಆದರೆ (ಸೂಚ್ಯಂಕ > -1)
        qf[ಸೂಚ್ಯಂಕ].ಸರತಿ_Family_Properties.timestamp_Valid_ಬಿಟ್ಟುಗಳು++;

    ಹಿಂತಿರುಗಿ ಸೂಚ್ಯಂಕ;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ pick_video_ಸರತಿ_family(Vk_ಸರತಿ_Family_Properties2 *qf,
                                          Vk_ಸರತಿ_Family_Video_Properties_KHR *qf_vid, uint32_t ಅಂಕೆ_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = -1;
    uint32_t min_score = UINT32_MAX;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_qf; i++) {
        ಸ್ಥಿರಾಂಕ Vk_ಸರತಿ_Flags qflags = qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags;
        ಸ್ಥಿರಾಂಕ VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        ಆದರೆ (!(qflags & (VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR | VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR)))
            ಮುಂದುವರಿ;

        ಆದರೆ (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].ಸರತಿ_Family_Properties.timestamp_Valid_ಬಿಟ್ಟುಗಳು;
            ಆದರೆ (score < min_score) {
                ಸೂಚ್ಯಂಕ = i;
                min_score = score;
            }
        }
    }

    ಆದರೆ (ಸೂಚ್ಯಂಕ > -1)
        qf[ಸೂಚ್ಯಂಕ].ಸರತಿ_Family_Properties.timestamp_Valid_ಬಿಟ್ಟುಗಳು++;

    ಹಿಂತಿರುಗಿ ಸೂಚ್ಯಂಕ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಸಿದ್ಧತೆ_ಸರತಿ_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t ಅಂಕೆ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    Vk_ಸರತಿ_Family_Properties2 *qf = ಖಾಲಿ;
    Vk_ಸರತಿ_Family_Video_Properties_KHR *qf_vid = ಖಾಲಿ;

    /* First get the number of queue families */
    vk->Get_Physical_Device_ಸರತಿ_Family_Properties(hwctx->phys_dev, &ಅಂಕೆ, ಖಾಲಿ);
    ಆದರೆ (!ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(ಅಂಕೆ, ಗಾತ್ರ(Vk_ಸರತಿ_Family_Properties2));
    ಆದರೆ (!qf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(ಅಂಕೆ, ಗಾತ್ರ(Vk_ಸರತಿ_Family_Video_Properties_KHR));
    ಆದರೆ (!qf_vid)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (uint32_t i = 0; i < ಅಂಕೆ; i++) {
        qf_vid[i] = (Vk_ಸರತಿ_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_ಸರತಿ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_PROPERTIES_2,
            .p_ಮುಂದಿನ = p->vkctx.extensions & FF_VK_EXT_VIDEO_ಸರತಿ ? &qf_vid[i] : ಖಾಲಿ,
        };
    }

    /* Finally retrieve the queue families */
    vk->Get_Physical_Device_ಸರತಿ_Family_Properties2(hwctx->phys_dev, &ಅಂಕೆ, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_GRAPHICS_ಬಿಟ್) ? " graphics" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_COMPUTE_ಬಿಟ್) ? " compute" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_TRANSFER_ಬಿಟ್) ? " transfer" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR) ? " encode" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR) ? " decode" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_SPARSE_BINDING_ಬಿಟ್) ? " sparse" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_OPTICAL_FLOW_ಬಿಟ್_NV) ? " optical_flow" : "",
               ((qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_Flags) & VK_ಸರತಿ_PROTECTED_ಬಿಟ್) ? " protected" : "",
               qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_ಎಣಿಕೆ);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].ಸರತಿ_Family_Properties.timestamp_Valid_ಬಿಟ್ಟುಗಳು = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->ಸರತಿ_flags = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_internally_synchronized_queues
    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC)
        hwctx->ಸರತಿ_flags |= VK_DEVICE_ಸರತಿ_CREATE_INTERNALLY_SYNCHRONIZED_ಬಿಟ್_KHR;
#ಆದರೆ_ಅಂತ್ಯ

    /* Pick each queue family to use. */
#ವ್ಯಾಖ್ಯಾನಿಸು PICK_QF(type, vid_op)                                            \
    ಮಾಡು {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        ಆದರೆ (vid_op)                                                      \
            idx = pick_video_ಸರತಿ_family(qf, qf_vid, ಅಂಕೆ, vid_op);      \
        ಇಲ್ಲದಿದ್ದರೆ                                                             \
            idx = pick_ಸರತಿ_family(qf, ಅಂಕೆ, type);                      \
                                                                         \
        ಆದರೆ (idx == -1)                                                   \
            ಮುಂದುವರಿ;                                                    \
                                                                         \
        ಗಾಗಿ (i = 0; i < hwctx->nb_qf; i++) {                             \
            ಆದರೆ (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                ನಿಲ್ಲಿಸು;                                                   \
            }                                                            \
        }                                                                \
        ಆದರೆ (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].ಅಂಕೆ = qf[idx].ಸರತಿ_Family_Properties.ಸರತಿ_ಎಣಿಕೆ; \
            ಆದರೆ (p->ಎಲ್ಲೆ_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                ಪೂರ್ಣಾಂಕ max = p->ಎಲ್ಲೆ_queues;                               \
                ಆದರೆ (type == VK_ಸರತಿ_GRAPHICS_ಬಿಟ್)                       \
                    hwctx->qf[i].ಅಂಕೆ = FFMIN(hwctx->qf[i].ಅಂಕೆ,           \
                                             max ? max : 1);             \
                ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (max)                                            \
                    hwctx->qf[i].ಅಂಕೆ = FFMIN(hwctx->qf[i].ಅಂಕೆ, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } ಆಗ (0)

    PICK_QF(VK_ಸರತಿ_GRAPHICS_ಬಿಟ್, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_ಸರತಿ_COMPUTE_ಬಿಟ್, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_ಸರತಿ_TRANSFER_ಬಿಟ್, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_ಬಿಟ್_KHR);
    PICK_QF(VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_ಬಿಟ್_KHR);

    PICK_QF(VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_ಬಿಟ್_KHR);
    PICK_QF(VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_ಬಿಟ್_KHR);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_decode_vp9
    PICK_QF(VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_ಬಿಟ್_KHR);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_video_encode_av1
    PICK_QF(VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_ಬಿಟ್_KHR);
#ಆದರೆ_ಅಂತ್ಯ
    PICK_QF(VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_ಬಿಟ್_KHR);

    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_ಸರತಿ_OPTICAL_FLOW_ಬಿಟ್_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PICK_QF

    cd->p_ಸರತಿ_Create_Infos = av_malloc_array(hwctx->nb_qf,
                                            ಗಾತ್ರ(Vk_Device_ಸರತಿ_Create_Info));
    ಆದರೆ (!cd->p_ಸರತಿ_Create_Infos)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        ಪೂರ್ಣಾಂಕ dup = 0;
        ದಶಮಾಂಶ *weights = ಖಾಲಿ;
        Vk_Device_ಸರತಿ_Create_Info *pc;
        ಗಾಗಿ (uint32_t j = 0; j < cd->ಸರತಿ_Create_Info_ಎಣಿಕೆ; j++) {
            ಆದರೆ (hwctx->qf[i].idx == cd->p_ಸರತಿ_Create_Infos[j].ಸರತಿ_Family_ಸೂಚ್ಯಂಕ) {
                dup = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (dup)
            ಮುಂದುವರಿ;

        weights = av_malloc_array(hwctx->qf[i].ಅಂಕೆ, ಗಾತ್ರ(ದಶಮಾಂಶ));
        ಆದರೆ (!weights) {
            ಗಾಗಿ (uint32_t j = 0; j < cd->ಸರತಿ_Create_Info_ಎಣಿಕೆ; j++)
                av_free((ಶೂನ್ಯ *)cd->p_ಸರತಿ_Create_Infos[i].p_ಸರತಿ_Priorities);
            av_free((ಶೂನ್ಯ *)cd->p_ಸರತಿ_Create_Infos);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }

        ಗಾಗಿ (uint32_t j = 0; j < hwctx->qf[i].ಅಂಕೆ; j++)
            weights[j] = 1.0;

        pc = (Vk_Device_ಸರತಿ_Create_Info *)cd->p_ಸರತಿ_Create_Infos;
        pc[cd->ಸರತಿ_Create_Info_ಎಣಿಕೆ++] = (Vk_Device_ಸರತಿ_Create_Info) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_ಸರತಿ_CREATE_INFO,
            .flags = hwctx->ಸರತಿ_flags,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = hwctx->qf[i].idx,
            .ಸರತಿ_ಎಣಿಕೆ = hwctx->qf[i].ಅಂಕೆ,
            .p_ಸರತಿ_Priorities = weights,
        };
    }

    ಹಿಂತಿರುಗಿ 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
ಸ್ಥಿರ ಶೂನ್ಯ vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಆದರೆ (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    ಆದರೆ (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    ಆದರೆ (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    ಆದರೆ (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    ಆದರೆ (p->qf_mutex) {
        ಗಾಗಿ (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_device_create_ಆಂತರಿಕ(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         ಪೂರ್ಣಾಂಕ disable_multiplane,
                                         AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    AVDictionary_ನಮೂದು *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಎಣಿಕೆ FFVulkan_Debug_ಬಹುಲಕ debug_ಬಹುಲಕ = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    ಆದರೆ ((err = create_instance(ctx, opts, &debug_ಬಹುಲಕ)))
        ಹೋಗು ಕೊನೆ;

    /* Find a physical device (if not given one) */
    ಆದರೆ ((err = ಕಂಡುಹಿಡಿ_device(ctx, dev_select)))
        ಹೋಗು ಕೊನೆ;

    /* Get supported memory types */
    vk->Get_Physical_Device_ಸ್ಮರಣೆ_Properties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    ಆದರೆ ((err = check_extensions(ctx, 1, opts, &dev_info.pp_Enabled_Extension_ಹೆಸರುಗಳು,
                                &dev_info.enabled_Extension_ಎಣಿಕೆ, debug_ಬಹುಲಕ))) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dev_info.ಸರತಿ_Create_Info_ಎಣಿಕೆ; i++)
            av_free((ಶೂನ್ಯ *)dev_info.p_ಸರತಿ_Create_Infos[i].p_ಸರತಿ_Priorities);
        av_free((ಶೂನ್ಯ *)dev_info.p_ಸರತಿ_Create_Infos);
        ಹೋಗು ಕೊನೆ;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.p_ಮುಂದಿನ = p->feats.device.p_ಮುಂದಿನ;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", ಖಾಲಿ, 0);
    ಆದರೆ (opt_d)
        p->ಎಲ್ಲೆ_queues = strtol(opt_d->ಮೌಲ್ಯ, ಖಾಲಿ, 10);

    /* Setup enabled queue families */
    ಆದರೆ ((err = ಸಿದ್ಧತೆ_ಸರತಿ_families(ctx, &dev_info)))
        ಹೋಗು ಕೊನೆ;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dev_info.ಸರತಿ_Create_Info_ಎಣಿಕೆ; i++)
        av_free((ಶೂನ್ಯ *)dev_info.p_ಸರತಿ_Create_Infos[i].p_ಸರತಿ_Priorities);
    av_free((ಶೂನ್ಯ *)dev_info.p_ಸರತಿ_Create_Infos);

    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dev_info.enabled_Extension_ಎಣಿಕೆ; i++)
            av_free((ಶೂನ್ಯ *)dev_info.pp_Enabled_Extension_ಹೆಸರುಗಳು[i]);
        av_free((ಶೂನ್ಯ *)dev_info.pp_Enabled_Extension_ಹೆಸರುಗಳು);
        err = AVERROR_EXTERNAL;
        ಹೋಗು ಕೊನೆ;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", ಖಾಲಿ, 0);
    ಆದರೆ (opt_d)
        p->use_ರೇಖೀಯ_images = strtol(opt_d->ಮೌಲ್ಯ, ಖಾಲಿ, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    ಆದರೆ (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", ಖಾಲಿ, 0);
        ಆದರೆ (opt_d)
            p->disable_multiplane = strtol(opt_d->ಮೌಲ್ಯ, ಖಾಲಿ, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", ಖಾಲಿ, 0);
    ಆದರೆ (opt_d)
        p->avoid_host_import = strtol(opt_d->ಮೌಲ್ಯ, ಖಾಲಿ, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.pp_Enabled_Extension_ಹೆಸರುಗಳು;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_ಎಣಿಕೆ;

    /* The extension lists need to be freed */
    ctx->ಬಿಡುಗಡೆ = vulkan_device_free;

ಕೊನೆ:
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಬೀಗ_ಸರತಿ(AVHWDeviceContext *ctx, uint32_t ಸರತಿ_family, uint32_t ಸೂಚ್ಯಂಕ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ಆದರೆ (p->qf_mutex)
        pthread_mutex_ಬೀಗ(&p->qf_mutex[ಸರತಿ_family][ಸೂಚ್ಯಂಕ]);
}

ಸ್ಥಿರ ಶೂನ್ಯ unlock_ಸರತಿ(AVHWDeviceContext *ctx, uint32_t ಸರತಿ_family, uint32_t ಸೂಚ್ಯಂಕ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ಆದರೆ (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[ಸರತಿ_family][ಸೂಚ್ಯಂಕ]);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_device_init(AVHWDeviceContext *ctx)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    uint32_t qf_ಅಂಕೆ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_ಸರತಿ_Family_Properties2 *qf;
    Vk_ಸರತಿ_Family_Video_Properties_KHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            ಆದರೆ (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    err = ff_vk_ತುಂಬು_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    ಆದರೆ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        ಹಿಂತಿರುಗಿ err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_ಮುಂದಿನ = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_ಸ್ಮರಣೆ_HOST_PROPERTIES_EXT;
    p->hprops.p_ಮುಂದಿನ = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_ಬಫರ್_Copy_ಅಡ್ಡಸಾಲು_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.min_ಸ್ಮರಣೆ_Map_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_ಗಾತ್ರ);
    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_ಸ್ಮರಣೆ)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.min_Imported_Host_ಸೂಚಕ_Alignment);

    vk->Get_Physical_Device_ಸರತಿ_Family_Properties(hwctx->phys_dev, &qf_ಅಂಕೆ, ಖಾಲಿ);
    ಆದರೆ (!qf_ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ಬಿಟ್
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ಬಿಟ್;
#ಇಲ್ಲದಿದ್ದರೆ
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ಬಿಟ್;
#ಆದರೆ_ಅಂತ್ಯ
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_ಅಂಕೆ, ಗಾತ್ರ(Vk_ಸರತಿ_Family_Properties2));
    ಆದರೆ (!qf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_ಅಂಕೆ, ಗಾತ್ರ(Vk_ಸರತಿ_Family_Video_Properties_KHR));
    ಆದರೆ (!qf_vid) {
        av_free(qf);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಗಾಗಿ (uint32_t i = 0; i < qf_ಅಂಕೆ; i++) {
        qf_vid[i] = (Vk_ಸರತಿ_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_ಸರತಿ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ಸರತಿ_FAMILY_PROPERTIES_2,
            .p_ಮುಂದಿನ = p->vkctx.extensions & FF_VK_EXT_VIDEO_ಸರತಿ ? &qf_vid[i] : ಖಾಲಿ,
        };
    }

    vk->Get_Physical_Device_ಸರತಿ_Family_Properties2(hwctx->phys_dev, &qf_ಅಂಕೆ, qf);

    p->nb_tot_qfs = qf_ಅಂಕೆ;

    ಆದರೆ (!(p->vkctx.extensions & FF_VK_EXT_ಆಂತರಿಕ_ಸರತಿ_SYNC)) {
        p->qf_mutex = av_calloc(qf_ಅಂಕೆ, ಗಾತ್ರ(*p->qf_mutex));
        ಆದರೆ (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            ಹೋಗು ಕೊನೆ;
        }

        ಗಾಗಿ (uint32_t i = 0; i < qf_ಅಂಕೆ; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_ಎಣಿಕೆ,
                                       ಗಾತ್ರ(**p->qf_mutex));
            ಆದರೆ (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                ಹೋಗು ಕೊನೆ;
            }
            ಗಾಗಿ (uint32_t j = 0; j < qf[i].ಸರತಿ_Family_Properties.ಸರತಿ_ಎಣಿಕೆ; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], ಖಾಲಿ);
                ಆದರೆ (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    ಹೋಗು ಕೊನೆ;
                }
            }
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < hwctx->nb_qf; i++) {
        ಆದರೆ (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_ಸರತಿ_VIDEO_DECODE_ಬಿಟ್_KHR |
                                  VK_ಸರತಿ_VIDEO_ENCODE_ಬಿಟ್_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < hwctx->nb_qf; i++) {
        ಪೂರ್ಣಾಂಕ ನೋಡಿದ = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = (i - 1); j >= 0; j--) {
            ಆದರೆ (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                ನೋಡಿದ = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!ನೋಡಿದ)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#ಆದರೆ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    ಆದರೆ (!hwctx->ಬೀಗ_ಸರತಿ)
        hwctx->ಬೀಗ_ಸರತಿ = ಬೀಗ_ಸರತಿ;
    ಆದರೆ (!hwctx->unlock_ಸರತಿ)
        hwctx->unlock_ಸರತಿ = unlock_ಸರತಿ;
FF_ENABLE_DEPRECATION_WARNINGS
#ಆದರೆ_ಅಂತ್ಯ

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_ಸ್ಮರಣೆ_Properties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_ತುಂಬು_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_ಕಂಡುಹಿಡಿ(&p->vkctx, VK_ಸರತಿ_COMPUTE_ಬಿಟ್, 0);
    p->transfer_qf = ff_vk_qf_ಕಂಡುಹಿಡಿ(&p->vkctx, VK_ಸರತಿ_TRANSFER_ಬಿಟ್, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_ಸ್ಥಾನಾಂತರ_align = 1;
    ಆದರೆ (p->transfer_qf) {
        Vk_ಸರತಿ_Flags flags = p->vkctx.qf_props[p->transfer_qf->idx].ಸರತಿ_Family_Properties.ಸರತಿ_Flags;
        ಆದರೆ (!(flags & (VK_ಸರತಿ_GRAPHICS_ಬಿಟ್ | VK_ಸರತಿ_COMPUTE_ಬಿಟ್)))
            p->transfer_ಸ್ಥಾನಾಂತರ_align = 4;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    ಆದರೆ (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_ಸ್ಥಾನಾಂತರ_align = 1;
#ಆದರೆ_ಅಂತ್ಯ

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_ಸ್ಮರಣೆ_Properties(hwctx->phys_dev, &p->mprops);

ಕೊನೆ:
    av_free(qf_vid);
    av_free(qf);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                                AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    ಆದರೆ (device && device[0]) {
        ಅಕ್ಷರ *ಕೊನೆ = ಖಾಲಿ;

        ಆದರೆ (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dev_select.ಸೂಚ್ಯಂಕ = strtol(device, &ಕೊನೆ, 10);
            ಆದರೆ (ಕೊನೆ == device || *ಕೊನೆ) {
                dev_select.ಸೂಚ್ಯಂಕ = 0;
                dev_select.name  = device;
            }
        }
    }

    ಹಿಂತಿರುಗಿ vulkan_device_create_ಆಂತರಿಕ(ctx, &dev_select, 0, opts, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    av_ಬಳಸದ VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    ಆಯ್ಕೆ(src_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#ಆದರೆ_ಅಂತ್ಯ
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *vendor;

#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 15, 0)
        vas = va_Get_Display_ಗುಣಲಕ್ಷಣಗಳು(dpy, &attr, 1);
        ಆದರೆ (vas == VA_ಸ್ಥಿತಿ_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.ಮೌಲ್ಯ & 0xFFFF);
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            ಆದರೆ (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
            }

            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        ಹಿಂತಿರುಗಿ vulkan_device_create_ಆಂತರಿಕ(ctx, &dev_select, 0, opts, flags);
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_LIBDRM
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DRM: {
        ಪೂರ್ಣಾಂಕ err;
        ರಚನೆ stat drm_ಗಂಟು_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ಗಂಟು_info);
        ಆದರೆ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ಗಂಟು_info.st_dev);
        dev_select.drm_minor = minor(drm_ಗಂಟು_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        ಆದರೆ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        ಆದರೆ (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        ಹಿಂತಿರುಗಿ vulkan_device_create_ಆಂತರಿಕ(ctx, &dev_select, 0, opts, flags);
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_CUDA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADevice_Context_ಆಂತರಿಕ *cu_ಆಂತರಿಕ = src_hwctx->ಆಂತರಿಕ;
        CudaFunctions *cu = cu_ಆಂತರಿಕ->cuda_dl;

        ಪೂರ್ಣಾಂಕ ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_ಆಂತರಿಕ->cuda_device));
        ಆದರೆ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        ಹಿಂತಿರುಗಿ vulkan_device_create_ಆಂತರಿಕ(ctx, &dev_select, 1, opts, flags);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    ಗಾಗಿ (ಎಣಿಕೆ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ಎಣಿಕೆ_2 += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_ರೇಖೀಯ_images ? VK_IMAGE_TILING_ರೇಖೀಯ :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(ಎಣಿಕೆ_2 + 1 + CONFIG_CUDA,
                                                    ಗಾತ್ರ(ಎಣಿಕೆ AVPixelFormat));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಎಣಿಕೆ_2 = 0;
    ಗಾಗಿ (ಎಣಿಕೆ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ಆದರೆ (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_ರೇಖೀಯ_images ? VK_IMAGE_TILING_ರೇಖೀಯ :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[ಎಣಿಕೆ_2++] = vk_formats_list[i].pixfmt;
        }
    }

#ಆದರೆ CONFIG_CUDA
    constraints->valid_sw_formats[ಎಣಿಕೆ_2++] = AV_PIX_FMT_CUDA;
#ಆದರೆ_ಅಂತ್ಯ

    constraints->valid_sw_formats[ಎಣಿಕೆ_2++] = AV_PIX_FMT_NONE;

    constraints->min_ಅಗಲ  = 1;
    constraints->min_ಎತ್ತರ = 1;
    constraints->max_ಅಗಲ  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_ಎತ್ತರ = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(ಎಣಿಕೆ AVPixelFormat));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ alloc_mem(AVHWDeviceContext *ctx, Vk_ಸ್ಮರಣೆ_Requirements *req,
                     Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು req_flags, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *alloc_extension,
                     Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು *mem_flags, Vk_Device_ಸ್ಮರಣೆ *mem)
{
    Vk_ಫಲಿತಾಂಶ ret;
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    Vk_ಸ್ಮರಣೆ_Allocate_Info alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_ALLOCATE_INFO,
        .p_ಮುಂದಿನ          = alloc_extension,
        .ಹಂಚಿಕೆ_ಗಾತ್ರ = req->ಗಾತ್ರ_2,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < p->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ; i++) {
        ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Type *type = &p->mprops.ಸ್ಮರಣೆ_Types[i];

        /* The memory type must be supported by the requirements (bitfield) */
        ಆದರೆ (!(req->ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು & (1 << i)))
            ಮುಂದುವರಿ;

        /* The memory type flags must include our properties */
        ಆದರೆ ((type->propertyFlags & req_flags) != req_flags)
            ಮುಂದುವರಿ;

        /* The memory type must be large enough */
        ಆದರೆ (req->ಗಾತ್ರ_2 > p->mprops.ಸ್ಮರಣೆ_Heaps[type->ರಾಶಿ_ಸೂಚ್ಯಂಕ_2].ಗಾತ್ರ_2)
            ಮುಂದುವರಿ;

        /* Found a suitable memory type */
        ಸೂಚ್ಯಂಕ = i;
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (ಸೂಚ್ಯಂಕ < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    alloc_info.ಸ್ಮರಣೆ_Type_ಸೂಚ್ಯಂಕ = ಸೂಚ್ಯಂಕ;

    ret = vk->Allocate_ಸ್ಮರಣೆ(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.ಸ್ಮರಣೆ_Types[ಸೂಚ್ಯಂಕ].propertyFlags;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_free_ಆಂತರಿಕ(VulkanDevicePriv *p, AVVk_ಚೌಕಟ್ಟು *f)
{
    av_ಬಳಸದ AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *ಆಂತರಿಕ = f->ಆಂತರಿಕ;

    // Make this function safe to call repeatedly
    ಆದರೆ (!ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ;

#ಆದರೆ CONFIG_CUDA
    ಆದರೆ (ಆಂತರಿಕ->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)ಆಂತರಿಕ->cuda_fc_ref->ದತ್ತಾಂಶ;
        ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADevice_Context_ಆಂತರಿಕ *cu_ಆಂತರಿಕ = cuda_dev->ಆಂತರಿಕ;
        CudaFunctions *cu = cu_ಆಂತರಿಕ->cuda_dl;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
            ಆದರೆ (ಆಂತರಿಕ->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(ಆಂತರಿಕ->cu_sem[i]));
            ಆದರೆ (ಆಂತರಿಕ->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(ಆಂತರಿಕ->cu_mma[i]));
            ಆದರೆ (ಆಂತರಿಕ->ext_mem[i])
                CHECK_CU(cu->cu_Destroy_External_ಸ್ಮರಣೆ(ಆಂತರಿಕ->ext_mem[i]));
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
            ಆದರೆ (ಆಂತರಿಕ->ext_sem_handle[i])
                CloseHandle(ಆಂತರಿಕ->ext_sem_handle[i]);
            ಆದರೆ (ಆಂತರಿಕ->ext_mem_handle[i])
                CloseHandle(ಆಂತರಿಕ->ext_mem_handle[i]);
#ಆದರೆ_ಅಂತ್ಯ
        }

        av_ಬಫರ್_unref(&ಆಂತರಿಕ->cuda_fc_ref);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ಆಂತರಿಕ->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, ಆಂತರಿಕ->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&ಆಂತರಿಕ->update_mutex);
    av_freep(&f->ಆಂತರಿಕ);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_ಚೌಕಟ್ಟು_free(AVHWFramesContext *hwfc, AVVk_ಚೌಕಟ್ಟು *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(f);
    ಪೂರ್ಣಾಂಕ nb_sems = 0;

    ಆಗ (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    ಆದರೆ (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_ಮೌಲ್ಯಗಳು        = f->sem_ಮೌಲ್ಯ,
            .semaphore_ಎಣಿಕೆ = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_ಆಂತರಿಕ(p, f);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->Free_ಸ್ಮರಣೆ(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_ಚೌಕಟ್ಟು_free_cb(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    vulkan_ಚೌಕಟ್ಟು_free(opaque, (AVVk_ಚೌಕಟ್ಟು*)ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ alloc_bind_mem(AVHWFramesContext *hwfc, AVVk_ಚೌಕಟ್ಟು *f,
                          ಶೂನ್ಯ *alloc_pnext, size_t alloc_pnext_stride)
{
    ಪೂರ್ಣಾಂಕ img_cnt = 0, err;
    Vk_ಫಲಿತಾಂಶ ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Bind_Image_ಸ್ಮರಣೆ_Info bind_info[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { { 0 } };

    ಆಗ (f->img[img_cnt]) {
        ಪೂರ್ಣಾಂಕ use_ded_mem;
        Vk_Image_ಸ್ಮರಣೆ_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ಸ್ಮರಣೆ_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        Vk_ಸ್ಮರಣೆ_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_ALLOCATE_INFO,
            .p_ಮುಂದಿನ = (ಶೂನ್ಯ *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        Vk_ಸ್ಮರಣೆ_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_REQUIREMENTS,
        };
        Vk_ಸ್ಮರಣೆ_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_REQUIREMENTS_2,
            .p_ಮುಂದಿನ = &ded_req,
        };

        vk->Get_Image_ಸ್ಮರಣೆ_Requirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefers_Dedicated_ಹಂಚಿಕೆ, ded_req.requires_Dedicated_ಹಂಚಿಕೆ);

        ಆದರೆ (f->tiling == VK_IMAGE_TILING_ರೇಖೀಯ)
            req.ಸ್ಮರಣೆ_Requirements.ಗಾತ್ರ_2 = FFALIGN(req.ಸ್ಮರಣೆ_Requirements.ಗಾತ್ರ_2,
                                                  p->props.properties.limits.min_ಸ್ಮರಣೆ_Map_Alignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefers_Dedicated_ಹಂಚಿಕೆ |
                      ded_req.requires_Dedicated_ಹಂಚಿಕೆ;
        ಆದರೆ (((Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        ಆದರೆ (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        ಆದರೆ ((err = alloc_mem(ctx, &req.ಸ್ಮರಣೆ_Requirements,
                             f->tiling == VK_IMAGE_TILING_ರೇಖೀಯ ?
                             VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್ :
                             VK_ಸ್ಮರಣೆ_PROPERTY_DEVICE_LOCAL_ಬಿಟ್,
                             use_ded_mem ? &ded_alloc : (ಶೂನ್ಯ *)ded_alloc.p_ಮುಂದಿನ,
                             &f->flags, &f->mem[img_cnt])))
            ಹಿಂತಿರುಗಿ err;

        f->ಗಾತ್ರ_2[img_cnt] = req.ಸ್ಮರಣೆ_Requirements.ಗಾತ್ರ_2;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_ಸ್ಮರಣೆ_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].ಸ್ಮರಣೆ = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಎಣಿಕೆ Prep_ಬಹುಲಕ {
    PREP_ಬಹುಲಕ_GENERAL,
    PREP_ಬಹುಲಕ_WRITE,
    PREP_ಬಹುಲಕ_EXTERNAL_EXPORT,
    PREP_ಬಹುಲಕ_EXTERNAL_IMPORT,
    PREP_ಬಹುಲಕ_DECODING_DST,
    PREP_ಬಹುಲಕ_DECODING_DPB,
    PREP_ಬಹುಲಕ_ENCODING_DPB,
};

ಸ್ಥಿರ ಶೂನ್ಯ switch_new_props(ಎಣಿಕೆ Prep_ಬಹುಲಕ pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    ಆಯ್ಕೆ (pmode) {
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_ಸ್ಮರಣೆ_READ_ಬಿಟ್ | VK_ACCESS_ಸ್ಮರಣೆ_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_ಸ್ಮರಣೆ_READ_ಬಿಟ್ | VK_ACCESS_ಸ್ಮರಣೆ_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ಬಿಟ್ | VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ PREP_ಬಹುಲಕ_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ಬಿಟ್ | VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್;
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಎಣಿಕೆ Prep_ಬಹುಲಕ pmode)
{
    ಪೂರ್ಣಾಂಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Image_ಸ್ಮರಣೆ_Barrier2 img_bar[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_ಸರತಿ_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    ಆದರೆ (pmode == PREP_ಬಹುಲಕ_EXTERNAL_EXPORT) {
        dst_qf     = VK_ಸರತಿ_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .ದತ್ತಾಂಶ = (uint8_t *)hwfc,
    };
    AVFrame tmp_ಚೌಕಟ್ಟು = {
        .ದತ್ತಾಂಶ[0] = (uint8_t *)ಚೌಕಟ್ಟು,
        .hw_ಚೌಕಟ್ಟುಗಳು_ctx = &tmp_ref,
    };

    Vk_Command_ಬಫರ್ cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_ಆರಂಭ(&p->vkctx, exec);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_ಕೂಡಿಸು_dep_ಚೌಕಟ್ಟು(&p->vkctx, exec, &tmp_ಚೌಕಟ್ಟು,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    ff_vk_ಚೌಕಟ್ಟು_barrier(&p->vkctx, exec, &tmp_ಚೌಕಟ್ಟು, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_ಸ್ಮರಣೆ_Barriers = img_bar,
            .image_ಸ್ಮರಣೆ_Barrier_ಎಣಿಕೆ = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVk_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಎಣಿಕೆ Prep_ಬಹುಲಕ pmode)
{
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(ಚೌಕಟ್ಟು);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_ಎಣಿಕೆ; i++) {
        ಆದರೆ (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i == p->vkctx.host_image_props.copy_Dst_Layout_ಎಣಿಕೆ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOTSUP);

    ಗಾಗಿ (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = ಚೌಕಟ್ಟು->img[i],
            .oldLayout = ಚೌಕಟ್ಟು->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspect_ಮುಖವಾಡ = VK_IMAGE_ASPECT_COLOR_ಬಿಟ್,
            .subresourceRange.layer_ಎಣಿಕೆ = 1,
            .subresourceRange.level_ಎಣಿಕೆ = 1,
        };
        ಚೌಕಟ್ಟು->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ prepare_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಎಣಿಕೆ Prep_ಬಹುಲಕ pmode)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwfc_vk = hwfc->hwctx;
    ಆದರೆ (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT &&
        (pmode != PREP_ಬಹುಲಕ_EXTERNAL_EXPORT) &&
        (pmode != PREP_ಬಹುಲಕ_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, ಚೌಕಟ್ಟು, pmode);
        ಆದರೆ (err != AVERROR(ENOTSUP))
            ಹಿಂತಿರುಗಿ err;
    }

    ಹಿಂತಿರುಗಿ switch_layout(hwfc, ectx, ಚೌಕಟ್ಟು, pmode);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ get_plane_wh(uint32_t *w, uint32_t *h, ಎಣಿಕೆ AVPixelFormat format,
                                ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_w, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_h, ಪೂರ್ಣಾಂಕ plane)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    ಆದರೆ (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = ಚೌಕಟ್ಟು_w;
        *h = ಚೌಕಟ್ಟು_h;
        ಹಿಂತಿರುಗಿ;
    }

    *w = AV_CEIL_RSHIFT(ಚೌಕಟ್ಟು_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(ಚೌಕಟ್ಟು_h, desc->log2_chroma_h);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ create_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc, AVVk_ಚೌಕಟ್ಟು **ಚೌಕಟ್ಟು,
                        VkImageTiling tiling, Vk_Image_Usage_Flag_ಬಿಟ್ಟುಗಳು usage,
                        VkImageCreateFlags flags, ಪೂರ್ಣಾಂಕ nb_layers,
                        ಶೂನ್ಯ *create_pnext)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVk_ಚೌಕಟ್ಟು *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_ಮೌಲ್ಯ  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_ಮುಂದಿನ = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ಬಿಟ್
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ಬಿಟ್,
#ಇಲ್ಲದಿದ್ದರೆ
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ಬಿಟ್,
#ಆದರೆ_ಅಂತ್ಯ
    };

    /* Check if exporting is supported before chaining any structs */
    ಆದರೆ (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_ಬಿಟ್) {
        ಆದರೆ (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ಮುಂದಿನ                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.ಆಳ          = 1,
            .mip_ಮಟ್ಟಗಳು             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_ಎಣಿಕೆ_1_ಬಿಟ್,
            .p_ಸರತಿ_Family_Indices   = p->img_qfs,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharing_ಬಹುಲಕ           = p->nb_img_qfs > 1 ? VK_SHARING_ಬಹುಲಕ_CONCURRENT :
                                                         VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.ಅಗಲ, &create_info.extent.ಎತ್ತರ,
                     hwfc->sw_format, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ಹೋಗು fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }

        f->ಸರತಿ_family[i] = p->nb_img_qfs > 1 ? VK_ಸರತಿ_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ಮೌಲ್ಯ[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *ಚೌಕಟ್ಟು = f;
    ಹಿಂತಿರುಗಿ 0;

fail:
    vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);
    ಹಿಂತಿರುಗಿ err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
ಸ್ಥಿರ ಶೂನ್ಯ try_export_flags(AVHWFramesContext *hwfc,
                             Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags *comp_handle_types,
                             Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags *iexp,
                             Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು ಘಾತಾಂಕ)
{
    Vk_ಫಲಿತಾಂಶ ret;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಸ್ಥಿರಾಂಕ VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ಪೂರ್ಣಾಂಕ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    ಪೂರ್ಣಾಂಕ nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_ಮುಂದಿನ = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_ಮುಂದಿನ = ಖಾಲಿ,
        .p_ಸರತಿ_Family_Indices   = p->img_qfs,
        .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = p->nb_img_qfs,
        .sharing_ಬಹುಲಕ           = p->nb_img_qfs > 1 ? VK_SHARING_ಬಹುಲಕ_CONCURRENT :
                                                     VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = ಘಾತಾಂಕ,
        .p_ಮುಂದಿನ = has_mods ? &phy_dev_mod_info : ಖಾಲಿ,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_ಮುಂದಿನ  = !ಘಾತಾಂಕ ? ಖಾಲಿ : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_ಬಿಟ್),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_ಎಣಿಕೆ : 1;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_mods; i++) {
        ಆದರೆ (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        ಆದರೆ (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        ಆದರೆ (ret == VK_SUCCESS) {
            *iexp |= ಘಾತಾಂಕ;
            *comp_handle_types |= eprops.external_ಸ್ಮರಣೆ_Properties.compatibleHandleTypes;
            ಆದರೆ (ಘಾತಾಂಕ == VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT) {
                Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.external_ಸ್ಮರಣೆ_Properties.external_ಸ್ಮರಣೆ_Features &
                                                  VK_EXTERNAL_ಸ್ಮರಣೆ_FEATURE_DEDICATED_ONLY_ಬಿಟ್);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
ಸ್ಥಿರ ಶೂನ್ಯ get_export_handle_types(AVHWFramesContext *hwfc,
                                    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags *comp_handle_types,
                                    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_ಬಳಸದ AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &((Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ಸ್ಮರಣೆ)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32_ಬಿಟ್
                             : VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32_KMT_ಬಿಟ್);
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ಸ್ಮರಣೆ) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_FD_ಬಿಟ್);

    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_ಸ್ಮರಣೆ &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT);
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ AVBufferRef *vulkan_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    ಪೂರ್ಣಾಂಕ err;
    AVVk_ಚೌಕಟ್ಟು *f;
    AVBufferRef *avbuf = ಖಾಲಿ;
    AVHWFramesContext *hwfc = opaque;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &fp->p;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags e;
    Vk_Export_ಸ್ಮರಣೆ_Allocate_Info eminfo[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];

    Vk_External_ಸ್ಮರಣೆ_Image_Create_Info eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ಸ್ಮರಣೆ_IMAGE_CREATE_INFO,
        .p_ಮುಂದಿನ       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_ಸ್ಮರಣೆ_ALLOCATE_INFO;
        eminfo[i].p_ಮುಂದಿನ       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_ಚೌಕಟ್ಟು(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    ಆದರೆ (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, ಗಾತ್ರ(*eminfo));
    ಆದರೆ (err)
        ಹೋಗು fail;

    ಆದರೆ ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ಬಿಟ್_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR))
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_DECODING_DPB);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR)
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_DECODING_DST);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ಬಿಟ್_KHR)
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_ENCODING_DPB);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_ಬಿಟ್)
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_WRITE);
    ಇಲ್ಲದಿದ್ದರೆ
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_GENERAL);
    ಆದರೆ (err)
        ಹೋಗು fail;

    avbuf = av_ಬಫರ್_create((uint8_t *)f, ಗಾತ್ರ(AVVk_ಚೌಕಟ್ಟು),
                             vulkan_ಚೌಕಟ್ಟು_free_cb, hwfc, 0);
    ಆದರೆ (!avbuf)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಬೀಗ_ಚೌಕಟ್ಟು(AVHWFramesContext *fc, AVVk_ಚೌಕಟ್ಟು *vkf)
{
    pthread_mutex_ಬೀಗ(&vkf->ಆಂತರಿಕ->update_mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ unlock_ಚೌಕಟ್ಟು(AVHWFramesContext *fc, AVVk_ಚೌಕಟ್ಟು *vkf)
{
    pthread_mutex_unlock(&vkf->ಆಂತರಿಕ->update_mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;

    ಆದರೆ (fp->modifier_info) {
        ಆದರೆ (fp->modifier_info->pDrmFormatModifiers)
            av_freep(&fp->modifier_info->pDrmFormatModifiers);
        av_freep(&fp->modifier_info);
    }

    ff_vk_exec_pool_free(&p->vkctx, &fp->compute_exec);
    ff_vk_exec_pool_free(&p->vkctx, &fp->upload_exec);
    ff_vk_exec_pool_free(&p->vkctx, &fp->download_exec);

    av_refstruct_pool_uninit(&fp->tmp);
}

/* Probes whether the host transfer usage bit is actually usable in combination
 * with the rest of the image creation parameters. Drivers may expose the
 * format feature, yet reject the final image, or provide no memory type from
 * which such an image can be allocated. Notably video decode/encode images
 * are often not possible to allocate from the host visible memory type. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_ಫಲಿತಾಂಶ ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    ಸ್ಥಿರಾಂಕ ರಚನೆ FFVk_Format_ನಮೂದು *fmt = vk_ಕಂಡುಹಿಡಿ_format_ನಮೂದು(hwfc->sw_format);
    ಆದರೆ (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಸ್ಥಿರಾಂಕ VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ಪೂರ್ಣಾಂಕ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಂಕ nb_mods = has_mods ? mod_list->drm_Format_Modifier_ಎಣಿಕೆ : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    ಆದರೆ (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        ಹಿಂತಿರುಗಿ 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_ಸರತಿ_Family_Indices   = p->img_qfs,
        .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = p->nb_img_qfs,
        .sharing_ಬಹುಲಕ           = p->nb_img_qfs > 1 ? VK_SHARING_ಬಹುಲಕ_CONCURRENT :
                                                     VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    ಆದರೆ (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ಸ್ಥಿರಾಂಕ VkVideoProfileListInfoKHR *pl =
        ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    ಆದರೆ (pl) {
        profile_list = *pl;
        profile_list.p_ಮುಂದಿನ = ಖಾಲಿ;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ಸ್ಥಿರಾಂಕ VkImageFormatListCreateInfo *fl =
        ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    ಆದರೆ (fl) {
        format_list = *fl;
        format_list.p_ಮುಂದಿನ = ಖಾಲಿ;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_ಮುಂದಿನ = &perf,
            };

            ಆದರೆ (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            ಆದರೆ (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                ಹಿಂತಿರುಗಿ 0;
            }

            ಆದರೆ (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identical_ಸ್ಮರಣೆ_Layout);
                ಹಿಂತಿರುಗಿ 0;
            }
        }
    }

    ಆದರೆ (!p->vkctx.host_image_props.identical_ಸ್ಮರಣೆ_Type_Requirements) {
        ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
        Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags e;
        Vk_External_ಸ್ಮರಣೆ_Image_Create_Info eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ಸ್ಮರಣೆ_IMAGE_CREATE_INFO,
            .p_ಮುಂದಿನ       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ಮುಂದಿನ       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, 1 },
            .mip_ಮಟ್ಟಗಳು   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_ಎಣಿಕೆ_1_ಬಿಟ್,
            .p_ಸರತಿ_Family_Indices   = p->img_qfs,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharing_ಬಹುಲಕ           = p->nb_img_qfs > 1 ? VK_SHARING_ಬಹುಲಕ_CONCURRENT :
                                                         VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
        };
        Vk_Device_Image_ಸ್ಮರಣೆ_Requirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_ಸ್ಮರಣೆ_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_0_ಬಿಟ್_EXT : 0,
        };
        Vk_ಸ್ಮರಣೆ_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_REQUIREMENTS_2,
        };

        vk->Get_Device_Image_ಸ್ಮರಣೆ_Requirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        Vk_ಸ್ಮರಣೆ_Property_Flags req_flags = hwctx->tiling == VK_IMAGE_TILING_ರೇಖೀಯ ?
                                          VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್ :
                                          VK_ಸ್ಮರಣೆ_PROPERTY_DEVICE_LOCAL_ಬಿಟ್;
        ಗಾಗಿ (ಸೂಚ್ಯಂಕ = 0; ಸೂಚ್ಯಂಕ < p->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ; ಸೂಚ್ಯಂಕ++) {
            ಆದರೆ (!(req.ಸ್ಮರಣೆ_Requirements.ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು & (1U << ಸೂಚ್ಯಂಕ)))
                ಮುಂದುವರಿ;
            ಆದರೆ ((p->mprops.ಸ್ಮರಣೆ_Types[ಸೂಚ್ಯಂಕ].propertyFlags & req_flags) == req_flags)
                ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (ಸೂಚ್ಯಂಕ == p->mprops.ಸ್ಮರಣೆ_Type_ಎಣಿಕೆ) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            ಹಿಂತಿರುಗಿ 0;
        }
    }

    ಹಿಂತಿರುಗಿ 1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *hwfc)
{
    ಪೂರ್ಣಾಂಕ err;
    AVVk_ಚೌಕಟ್ಟು *f;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಸ್ಥಿರಾಂಕ ರಚನೆ FFVk_Format_ನಮೂದು *fmt;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    ಪೂರ್ಣಾಂಕ disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_ಚೌಕಟ್ಟು_FLAG_DISABLE_MULTIPLANE);
    ಪೂರ್ಣಾಂಕ is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ಬಿಟ್_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ಬಿಟ್_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ಬಿಟ್_KHR)));

    /* Defaults */
    ಆದರೆ (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    ಆದರೆ (p->use_ರೇಖೀಯ_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_ರೇಖೀಯ;


    fmt = vk_ಕಂಡುಹಿಡಿ_format_ನಮೂದು(hwfc->sw_format);
    ಆದರೆ (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಆದರೆ ((hwfc->ಅಗಲ  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->ಎತ್ತರ & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    ಆದರೆ (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        ಆದರೆ (hwctx->format[0] != fmt->vkf) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < fmt->nb_images_fallback; i++) {
                ಆದರೆ (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, ಖಾಲಿ,
                                 ಖಾಲಿ, ಖಾಲಿ, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ಬಿಟ್));
        ಆದರೆ (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, ಖಾಲಿ,
                                 ಖಾಲಿ, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ಬಿಟ್));
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    ಪೂರ್ಣಾಂಕ drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    ಆದರೆ (!is_lone_dpb && !drm_mod_with_video) {
        /* Image usage flags */
        hwctx->usage |= supported_usage & (VK_IMAGE_USAGE_TRANSFER_DST_ಬಿಟ್ |
                                           VK_IMAGE_USAGE_TRANSFER_SRC_ಬಿಟ್ |
                                           VK_IMAGE_USAGE_STORAGE_ಬಿಟ್      |
                                           VK_IMAGE_USAGE_SAMPLED_ಬಿಟ್);

        /* Frames which may double as active references (coinciding decode
         * output) cannot support host transfers: decode submissions bake the
         * image layout into their barriers at record time, so a host-side
         * layout transition cannot be synchronized against them, not even
         * by the frame lock and timeline semaphore. */
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ಬಿಟ್_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        ಆದರೆ ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_ಸರತಿ) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        ಆದರೆ (!hwctx->img_flags) {
            ಪೂರ್ಣಾಂಕ sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_ಬಿಟ್ |
                                             VK_IMAGE_USAGE_STORAGE_ಬಿಟ್);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_ಬಿಟ್;
            ಆದರೆ (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_ಬಿಟ್;
                ಆದರೆ ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_ಬಿಟ್;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    ಆದರೆ ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ಬಿಟ್_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_ಸರತಿ) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ಸ್ಥಿರಾಂಕ VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_ಕಂಡುಹಿಡಿ_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        ಆದರೆ (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ಬಿಟ್_KHR;
        } ಇಲ್ಲದಿದ್ದರೆ {
            uint32_t i;
            ಗಾಗಿ (i = 0; i < pl->profile_ಎಣಿಕೆ; i++) {
                /* Video ops start at exactly 0x00010000 */
                ಆದರೆ (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    ನಿಲ್ಲಿಸು;
            }
            ಆದರೆ (i == pl->profile_ಎಣಿಕೆ)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ಬಿಟ್_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    ಆದರೆ ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT;

    ಆದರೆ (!hwctx->ಬೀಗ_ಚೌಕಟ್ಟು)
        hwctx->ಬೀಗ_ಚೌಕಟ್ಟು = ಬೀಗ_ಚೌಕಟ್ಟು;

    ಆದರೆ (!hwctx->unlock_ಚೌಕಟ್ಟು)
        hwctx->unlock_ಚೌಕಟ್ಟು = unlock_ಚೌಕಟ್ಟು;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, ಖಾಲಿ);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, ಖಾಲಿ);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, ಖಾಲಿ);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    /* Test to see if allocation will fail */
    err = create_ಚೌಕಟ್ಟು(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        ಆದರೆ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = ಖಾಲಿ;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ಮುಂದಿನ = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_ಎಣಿಕೆ, ಗಾತ್ರ(*modp.pDrmFormatModifierProperties));
            ಆದರೆ (!modp.pDrmFormatModifierProperties) {
                vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            ಗಾಗಿ (uint32_t j = 0; j < modp.drm_Format_Modifier_ಎಣಿಕೆ; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                ಆದರೆ (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ (mod_props == ಖಾಲಿ) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);
                ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    ಆದರೆ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ = av_ಬಫರ್_pool_init2(ಗಾತ್ರ(AVVk_ಚೌಕಟ್ಟು),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(hwfc)->pool_ಆಂತರಿಕ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_get_ಬಫರ್(AVHWFramesContext *hwfc, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(hwfc->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_VULKAN;
    ಚೌಕಟ್ಟು->ಅಗಲ   = hwfc->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = hwfc->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                       ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;
    ಪೂರ್ಣಾಂಕ n = 2;

#ಆದರೆ CONFIG_CUDA
    n++;
#ಆದರೆ_ಅಂತ್ಯ
    fmts = av_malloc_array(n, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#ಆದರೆ CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#ಆದರೆ_ಅಂತ್ಯ
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ CONFIG_LIBDRM
ಸ್ಥಿರ ಶೂನ್ಯ vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_ಚೌಕಟ್ಟು_free(hwfc, hwmap->priv);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    uint32_t drm_fourcc;
    VkFormat vk_format;
} vulkan_drm_format_map[] = {
    { DRM_FORMAT_R8,       VK_FORMAT_R8_UNORM       },
    { DRM_FORMAT_R16,      VK_FORMAT_R16_UNORM      },
    { DRM_FORMAT_GR88,     VK_FORMAT_R8G8_UNORM     },
    { DRM_FORMAT_RG88,     VK_FORMAT_R8G8_UNORM     },
    { DRM_FORMAT_GR1616,   VK_FORMAT_R16G16_UNORM   },
    { DRM_FORMAT_RG1616,   VK_FORMAT_R16G16_UNORM   },
    { DRM_FORMAT_ARGB8888, VK_FORMAT_B8G8R8A8_UNORM },
    { DRM_FORMAT_XRGB8888, VK_FORMAT_B8G8R8A8_UNORM },
    { DRM_FORMAT_ABGR8888, VK_FORMAT_R8G8B8A8_UNORM },
    { DRM_FORMAT_XBGR8888, VK_FORMAT_R8G8B8A8_UNORM },
    { DRM_FORMAT_ARGB2101010, VK_FORMAT_A2B10G10R10_UNORM_PACK32 },
    { DRM_FORMAT_ABGR2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },
    { DRM_FORMAT_XRGB2101010, VK_FORMAT_A2B10G10R10_UNORM_PACK32 },
    { DRM_FORMAT_XBGR2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },

    // All these DRM_FORMATs were added in the same libdrm commit.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#ಆದರೆ_ಅಂತ್ಯ
};

ಸ್ಥಿರ ಸಾಲೊಳಗೆ VkFormat drm_ಗಮ್ಯ_vulkan_fmt(uint32_t drm_fourcc)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ಆದರೆ (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            ಹಿಂತಿರುಗಿ vulkan_drm_format_map[i].vk_format;
    ಹಿಂತಿರುಗಿ VK_FORMAT_UNDEFINED;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_from_drm_ಚೌಕಟ್ಟು_desc(AVHWFramesContext *hwfc, AVVk_ಚೌಕಟ್ಟು **ಚೌಕಟ್ಟು,
                                          ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    AVVk_ಚೌಕಟ್ಟು *f;
    ಪೂರ್ಣಾಂಕ bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->ದತ್ತಾಂಶ[0];
    Vk_Bind_Image_ಸ್ಮರಣೆ_Info bind_info[AV_DRM_MAX_PLANES];
    Vk_Bind_Image_Plane_ಸ್ಮರಣೆ_Info plane_info[AV_DRM_MAX_PLANES];

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_layers; i++) {
        ಆದರೆ (drm_ಗಮ್ಯ_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಆದರೆ (!(f = av_vk_ಚೌಕಟ್ಟು_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_layers; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_ಮೌಲ್ಯ  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ಮುಂದಿನ = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_ಎಣಿಕೆ = planes,
            .pPlaneLayouts = (ಸ್ಥಿರಾಂಕ VkSubresourceLayout *)&ext_img_layouts,
        };
        Vk_External_ಸ್ಮರಣೆ_Image_Create_Info ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ಸ್ಮರಣೆ_IMAGE_CREATE_INFO,
            .p_ಮುಂದಿನ       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ಮುಂದಿನ                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_ಗಮ್ಯ_vulkan_fmt(desc->layers[i].format),
            .extent.ಆಳ          = 1,
            .mip_ಮಟ್ಟಗಳು             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_ಎಣಿಕೆ_1_ಬಿಟ್,
            .p_ಸರತಿ_Family_Indices   = p->img_qfs,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharing_ಬಹುಲಕ           = p->nb_img_qfs > 1 ? VK_SHARING_ಬಹುಲಕ_CONCURRENT :
                                                         VK_SHARING_ಬಹುಲಕ_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        ಆದರೆ (planes == 1) {
            ಸ್ಥಿರಾಂಕ VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            ಆದರೆ (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .p_ಮುಂದಿನ = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .p_ಸರತಿ_Family_Indices = create_info.p_ಸರತಿ_Family_Indices,
            .ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ = create_info.ಸರತಿ_Family_ಸೂಚ್ಯಂಕ_ಎಣಿಕೆ,
            .sharing_ಬಹುಲಕ = create_info.sharing_ಬಹುಲಕ,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_ಮುಂದಿನ = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        ಆದರೆ (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_ಬಿಟ್ |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_ಬಿಟ್;
        ಆದರೆ (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_ಬಿಟ್ |
                                 VK_IMAGE_USAGE_TRANSFER_DST_ಬಿಟ್;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .p_ಮುಂದಿನ  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.ಅಗಲ, &create_info.extent.ಎತ್ತರ,
                     hwfc->sw_format, src->ಅಗಲ, src->ಎತ್ತರ, i);

        /* Set the subresource layout based on the layer properties */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < planes; j++) {
            ext_img_layouts[j].ಸ್ಥಾನಾಂತರ     = desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ;
            ext_img_layouts[j].ಅಡ್ಡಸಾಲು_Pitch_2   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].ಗಾತ್ರ_2       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].ಆಳ_Pitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ಹೋಗು fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಹೋಗು fail;
        }

        f->ಸರತಿ_family[i] = VK_ಸರತಿ_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ಮೌಲ್ಯ[i] = 0;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        Vk_Image_ಸ್ಮರಣೆ_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ಸ್ಮರಣೆ_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        Vk_ಸ್ಮರಣೆ_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_REQUIREMENTS,
        };
        Vk_ಸ್ಮರಣೆ_Requirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_REQUIREMENTS_2,
            .p_ಮುಂದಿನ = &ded_req,
        };

        /* Allocation/importing */
        Vk_ಸ್ಮರಣೆ_Fd_Properties_KHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        Vk_Import_ಸ್ಮರಣೆ_Fd_Info_KHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_ಸ್ಮರಣೆ_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_ಸೂಚ್ಯಂಕ].fd),
            .handleType = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT,
        };
        Vk_ಸ್ಮರಣೆ_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_DEDICATED_ALLOCATE_INFO,
            .p_ಮುಂದಿನ = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->Get_ಸ್ಮರಣೆ_Fd_Properties_KHR(hwctx->act_dev,
                                           VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT,
                                           idesc.fd, &fdmp);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            ಹೋಗು fail;
        }

        vk->Get_Image_ಸ್ಮರಣೆ_Requirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.ಸ್ಮರಣೆ_Requirements.ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು = fdmp.ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;

        err = alloc_mem(ctx, &req2.ಸ್ಮರಣೆ_Requirements,
                        VK_ಸ್ಮರಣೆ_PROPERTY_DEVICE_LOCAL_ಬಿಟ್,
                        (ded_req.prefers_Dedicated_ಹಂಚಿಕೆ ||
                         ded_req.requires_Dedicated_ಹಂಚಿಕೆ) ?
                            &ded_alloc : ded_alloc.p_ಮುಂದಿನ,
                        &f->flags, &f->mem[i]);
        ಆದರೆ (err) {
            close(idesc.fd);
            ಹೋಗು fail;
        }

        f->ಗಾತ್ರ_2[i] = req2.ಸ್ಮರಣೆ_Requirements.ಗಾತ್ರ_2;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_layers; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = desc->layers[i].nb_planes;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < planes; j++) {
            Vk_Image_Aspect_Flag_ಬಿಟ್ಟುಗಳು aspect = j == 0 ? VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_0_ಬಿಟ್_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_1_ಬಿಟ್_EXT :
                                                    VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_2_ಬಿಟ್_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_ಸ್ಮರಣೆ_INFO;
            plane_info[bind_counts].p_ಮುಂದಿನ = ಖಾಲಿ;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_ಸ್ಮರಣೆ_INFO;
            bind_info[bind_counts].p_ಮುಂದಿನ  = planes > 1 ? &plane_info[bind_counts] : ಖಾಲಿ;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].ಸ್ಮರಣೆ = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].ಸ್ಮರಣೆ_ಸ್ಥಾನಾಂತರ = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಹೋಗು fail;
    }

    *ಚೌಕಟ್ಟು = f;

    ಹಿಂತಿರುಗಿ 0;

fail:
    vulkan_ಚೌಕಟ್ಟು_free(hwfc, f);

    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_from_drm_ಚೌಕಟ್ಟು_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_ಬಫರ್ cmd_buf;
        FFVkExecContext *exec;
        Vk_Image_ಸ್ಮರಣೆ_Barrier2 img_bar[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        ಪೂರ್ಣಾಂಕ nb_img_bar = 0;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ದ್ವಿಮಾನ,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_ಮುಂದಿನ = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            ರಚನೆ dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            ಆದರೆ (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                ಗಾಗಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಹಿಂತಿರುಗಿ err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            ಆದರೆ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ಗಾಗಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಹಿಂತಿರುಗಿ err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ಬಿಟ್,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_ಬಿಟ್,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            ಆದರೆ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ಗಾಗಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಹಿಂತಿರುಗಿ err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_ಆರಂಭ(&p->vkctx, exec);
        ಆದರೆ (err < 0) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            ಹಿಂತಿರುಗಿ err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_ಕೂಡಿಸು_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_ಕೂಡಿಸು_dep_ಚೌಕಟ್ಟು(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್);
        ಆದರೆ (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            ಹಿಂತಿರುಗಿ err;
        }

        ff_vk_ಚೌಕಟ್ಟು_barrier(&p->vkctx, exec, dst, img_bar, &nb_img_bar,
                            VK_PIPELINE_STAGE_2_NONE,
                            VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                            ((flags & AV_HWFRAME_MAP_READ) ?
                             VK_ACCESS_2_SHADER_SAMPLED_READ_ಬಿಟ್ : 0x0) |
                            ((flags & AV_HWFRAME_MAP_WRITE) ?
                             VK_ACCESS_2_SHADER_STORAGE_WRITE_ಬಿಟ್ : 0x0),
                            VK_IMAGE_LAYOUT_GENERAL,
                            p->nb_img_qfs > 1 ? VK_ಸರತಿ_FAMILY_IGNORED : p->img_qfs[0]);

        vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
                .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                .p_Image_ಸ್ಮರಣೆ_Barriers = img_bar,
                .image_ಸ್ಮರಣೆ_Barrier_ಎಣಿಕೆ = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        AVVk_ಚೌಕಟ್ಟು *f = (AVVk_ಚೌಕಟ್ಟು *)dst->ದತ್ತಾಂಶ[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_EXTERNAL_IMPORT);
        ಆದರೆ (err)
            ಹಿಂತಿರುಗಿ err;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    AVVk_ಚೌಕಟ್ಟು *f;
    ಸ್ಥಿರಾಂಕ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->ದತ್ತಾಂಶ[0];

    ಆದರೆ ((err = vulkan_map_from_drm_ಚೌಕಟ್ಟು_desc(hwfc, &f, src, flags)))
        ಹಿಂತಿರುಗಿ err;

    /* The unmapping function will free this */
    dst->ದತ್ತಾಂಶ[0] = (uint8_t *)f;
    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = vulkan_map_from_drm_ಚೌಕಟ್ಟು_sync(hwfc, dst, desc, flags);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    ಹಿಂತಿರುಗಿ 0;

fail:
    vulkan_ಚೌಕಟ್ಟು_free(hwfc->device_ctx->hwctx, f);
    dst->ದತ್ತಾಂಶ[0] = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ CONFIG_VAAPI
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                                 ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;
    AVFrame *tmp = av_ಚೌಕಟ್ಟು_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];

    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = av_hwframe_map(tmp, src, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ಚೌಕಟ್ಟು_free(&tmp);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_CUDA
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ export_mem_ಗಮ್ಯ_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *dst_int, ಪೂರ್ಣಾಂಕ idx,
                              Vk_Device_ಸ್ಮರಣೆ mem, size_t ಗಾತ್ರ_2)
{
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    CUDA_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .ಗಾತ್ರ_2 = ಗಾತ್ರ_2,
    };
    Vk_ಸ್ಮರಣೆ_Get_Win32_Handle_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_GET_WIN32_HANDLE_INFO_KHR,
        .ಸ್ಮರಣೆ     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32_ಬಿಟ್
            : VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_WIN32_KMT_ಬಿಟ್,
    };

    ret = vk->Get_ಸ್ಮರಣೆ_Win32_Handle_KHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#ಇಲ್ಲದಿದ್ದರೆ
    CUDA_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_FD,
        .ಗಾತ್ರ_2 = ಗಾತ್ರ_2,
    };
    Vk_ಸ್ಮರಣೆ_Get_Fd_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_GET_FD_INFO_KHR,
        .ಸ್ಮರಣೆ     = mem,
        .handleType = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_OPAQUE_FD_ಬಿಟ್_KHR,
    };

    ret = vk->Get_ಸ್ಮರಣೆ_Fd_KHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ret = CHECK_CU(cu->cu_Import_External_ಸ್ಮರಣೆ(&dst_int->ext_mem[idx], &ext_desc));
    ಆದರೆ (ret < 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _WIN32
        close(ext_desc.handle.fd);
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ export_sem_ಗಮ್ಯ_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *dst_int, ಪೂರ್ಣಾಂಕ idx,
                              VkSemaphore sem)
{
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    VkSemaphoreGetWin32HandleInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
        .semaphore = sem,
        .handleType = IsWindows8OrGreater()
                      ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ಬಿಟ್
                      : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ಬಿಟ್,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 10 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32 */,
    };
#ಇಲ್ಲದಿದ್ದರೆ
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ಬಿಟ್,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#ಇಲ್ಲದಿದ್ದರೆ
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#ಆದರೆ_ಅಂತ್ಯ

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    ಆದರೆ (ret < 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _WIN32
        close(ext_sem_desc.handle.fd);
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_export_ಗಮ್ಯ_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು)
{
    ಪೂರ್ಣಾಂಕ err;
    Vk_ಫಲಿತಾಂಶ ret;
    AVVk_ಚೌಕಟ್ಟು *dst_f;
    AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಂಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->ದತ್ತಾಂಶ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ಆಂತರಿಕ *cu_ಆಂತರಿಕ = cuda_dev->ಆಂತರಿಕ;
    CudaFunctions *cu = cu_ಆಂತರಿಕ->cuda_dl;
    CUarray_format cufmt = desc->comp[0].ಆಳ > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ elem_ಗಾತ್ರ = 1 + (desc->comp[0].ಆಳ > 8);

    dst_f = (AVVk_ಚೌಕಟ್ಟು *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
    dst_int = dst_f->ಆಂತರಿಕ;

    ಆದರೆ (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_ಬಫರ್_ref(cuda_hwfc);
        ಆದರೆ (!dst_int->cuda_fc_ref)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
            err = export_mem_ಗಮ್ಯ_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->ಗಾತ್ರ_2[i]);
            ಆದರೆ (err < 0)
                ಹೋಗು fail;

            err = export_sem_ಗಮ್ಯ_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            ಆದರೆ (err < 0)
                ಹೋಗು fail;
        }

        ಆದರೆ (nb_images != planes) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                ಆದರೆ (desc->comp[i].ಹೆಜ್ಜೆ / elem_ಗಾತ್ರ > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    ಹೋಗು fail;
                }

                VkImageSubresource subres = {
                    .aspect_ಮುಖವಾಡ = i == 2 ? VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_2_ಬಿಟ್_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_1_ಬಿಟ್_EXT :
                                           VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_0_ಬಿಟ್_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.ಸ್ಥಾನಾಂತರ;
            }
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
            CUDA_EXTERNAL_ಸ್ಮರಣೆ_MIPMAPPED_ARRAY_DESC tex_desc = {
                .ಸ್ಥಾನಾಂತರ = offsets[i],
                .arrayDesc = {
                    .ಆಳ_2 = 0,
                    .Format = cufmt,
                    .ಅಂಕೆ_Channels = desc->comp[i].ಹೆಜ್ಜೆ / elem_ಗಾತ್ರ,
                    .Flags = 0,
                },
                .ಅಂಕೆ_ಮಟ್ಟಗಳು = 1,
            };
            ಪೂರ್ಣಾಂಕ p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, i);
            tex_desc.arrayDesc.ಅಗಲ_2 = p_w;
            tex_desc.arrayDesc.ಎತ್ತರ_2 = p_h;

            ret = CHECK_CU(cu->cu_External_ಸ್ಮರಣೆ_Get_Mapped_Mipmapped_Array(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            ಆದರೆ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ಹೋಗು fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            ಆದರೆ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ಹೋಗು fail;
            }

        }
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    vulkan_free_ಆಂತರಿಕ(p, dst_f);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_ದತ್ತಾಂಶ_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ err;
    CUcontext dummy;
    AVVk_ಚೌಕಟ್ಟು *dst_f;
    AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಪೂರ್ಣಾಂಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ಆಂತರಿಕ *cu_ಆಂತರಿಕ = cuda_dev->ಆಂತರಿಕ;
    CudaFunctions *cu = cu_ಆಂತರಿಕ->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };

    dst_f = (AVVk_ಚೌಕಟ್ಟು *)dst->ದತ್ತಾಂಶ[0];
    nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);

    err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->upload_exec, dst_f, PREP_ಬಹುಲಕ_EXTERNAL_EXPORT);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(cuda_dev->cuda_ctx));
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    err = vulkan_export_ಗಮ್ಯ_cuda(hwfc, src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst);
    ಆದರೆ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಹಿಂತಿರುಗಿ err;
    }

    dst_int = dst_f->ಆಂತರಿಕ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 0;
        s_s_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ಹರಿವು));
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .src_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->ದತ್ತಾಂಶ[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dst_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        ಪೂರ್ಣಾಂಕ p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, i);

        cpy.ಅಗಲ_ಒಳ_ಬೈಟುಗಳು = p_w * desc->comp[i].ಹೆಜ್ಜೆ;
        cpy.ಎತ್ತರ_2 = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ಹರಿವು));
        ಆದರೆ (err < 0)
            ಹೋಗು fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ಹರಿವು));
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++)
        dst_f->sem_ಮೌಲ್ಯ[i]++;

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    ಹಿಂತಿರುಗಿ err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->upload_exec, dst_f, PREP_ಬಹುಲಕ_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    vulkan_free_ಆಂತರಿಕ(p, dst_f);
    av_ಬಫರ್_unref(&dst->buf[0]);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_ಗಮ್ಯ(AVHWFramesContext *hwfc, AVFrame *dst,
                         ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    av_ಬಳಸದ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಆಯ್ಕೆ (src->format) {
#ಆದರೆ CONFIG_LIBDRM
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಹಿಂತಿರುಗಿ vulkan_map_from_vaapi(hwfc, dst, src, flags);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಹಿಂತಿರುಗಿ vulkan_map_from_drm(hwfc, dst, src, flags);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
}

#ಆದರೆ CONFIG_LIBDRM
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVk_ಚೌಕಟ್ಟು *ಮೂಲ;
} VulkanDRMMapping;

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_unmap_ಗಮ್ಯ_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_ಚೌಕಟ್ಟು_sync(hwfc, hwmap->ಮೂಲ, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t vulkan_fmt_ಗಮ್ಯ_drm(VkFormat vkfmt)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ಆದರೆ (vulkan_drm_format_map[i].vk_format == vkfmt)
            ಹಿಂತಿರುಗಿ vulkan_drm_format_map[i].drm_fourcc;
    ಹಿಂತಿರುಗಿ DRM_FORMAT_INVALID;
}

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಸ್ಮರಣೆ_PLANES 4
ಸ್ಥಿರ VkImageAspectFlags plane_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_aspect(ಪೂರ್ಣಾಂಕ plane) {
    ಆದರೆ (plane == 0) ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_0_ಬಿಟ್_EXT;
    ಆದರೆ (plane == 1) ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_1_ಬಿಟ್_EXT;
    ಆದರೆ (plane == 2) ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_2_ಬಿಟ್_EXT;
    ಆದರೆ (plane == 3) ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_3_ಬಿಟ್_EXT;

    av_assert2 (0 && "Invalid plane index");
    ಹಿಂತಿರುಗಿ VK_IMAGE_ASPECT_ಸ್ಮರಣೆ_PLANE_0_ಬಿಟ್_EXT;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVk_ಚೌಕಟ್ಟು *f,
                                     Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp, ಪೂರ್ಣಾಂಕ nb_sems)
{
    ಪೂರ್ಣಾಂಕ sync_fd = -1;
    Vk_ಫಲಿತಾಂಶ ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಆದರೆ (f->ಆಂತರಿಕ->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ಬಿಟ್,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_ಮುಂದಿನ         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ದ್ವಿಮಾನ,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ಮುಂದಿನ = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->ಆಂತರಿಕ->drm_sync_sem);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    ಆದರೆ (ff_vk_exec_ಆರಂಭ(&p->vkctx, exec) >= 0) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_sems; i++)
            ff_vk_exec_ಕೂಡಿಸು_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_ಮೌಲ್ಯ[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್);
        ff_vk_exec_ಕೂಡಿಸು_dep_bool_sem(&p->vkctx, exec, &f->ಆಂತರಿಕ->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್, 0);
        ಆದರೆ (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->ಆಂತರಿಕ->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ಬಿಟ್,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            ಆದರೆ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    ಹಿಂತಿರುಗಿ sync_fd;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_ಗಮ್ಯ_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err = 0;
    Vk_ಫಲಿತಾಂಶ ret;
    AVVk_ಚೌಕಟ್ಟು *f = (AVVk_ಚೌಕಟ್ಟು *)src->ದತ್ತಾಂಶ[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_sems = nb_images;
    ಪೂರ್ಣಾಂಕ free_drm_desc_on_err = 1;
    ಪೂರ್ಣಾಂಕ sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(ಗಾತ್ರ(*drm_desc));
    ಆದರೆ (!drm_desc)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->compute_exec, f, PREP_ಬಹುಲಕ_EXTERNAL_EXPORT);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        ಆದರೆ (err < 0)
            ಹೋಗು ಕೊನೆ;
        sync_fd = err;
        err = 0;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_ಎಣಿಕೆ = nb_sems,
            .pSemaphores    = f->sem,
            .p_ಮೌಲ್ಯಗಳು        = f->sem_ಮೌಲ್ಯ,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src, &vulkan_unmap_ಗಮ್ಯ_drm, drm_desc);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    ಆದರೆ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        ಹೋಗು ಕೊನೆ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; (i < planes) && (f->mem[i]); i++) {
        Vk_ಸ್ಮರಣೆ_Get_Fd_Info_KHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_GET_FD_INFO_KHR,
            .ಸ್ಮರಣೆ     = f->mem[i],
            .handleType = VK_EXTERNAL_ಸ್ಮರಣೆ_HANDLE_TYPE_DMA_BUF_ಬಿಟ್_EXT,
        };

        ret = vk->Get_ಸ್ಮರಣೆ_Fd_KHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        ಆದರೆ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            ಹೋಗು ಕೊನೆ;
        }

#ಆದರೆ HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        ಆದರೆ (sync_fd >= 0) {
            ಪೂರ್ಣಾಂಕ dup_fd = dup(sync_fd);
            ಆದರೆ (dup_fd >= 0) {
                ರಚನೆ dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                ಆದರೆ (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#ಆದರೆ_ಅಂತ್ಯ

        drm_desc->nb_objects++;
        drm_desc->objects[i].ಗಾತ್ರ_2 = f->ಗಾತ್ರ_2[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_ಗಮ್ಯ_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_ಎಣಿಕೆ;

        ಆದರೆ (drm_desc->layers[i].nb_planes > MAX_ಸ್ಮರಣೆ_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            ಹೋಗು ಕೊನೆ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            ಪೂರ್ಣಾಂಕ aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspect_ಮುಖವಾಡ = plane_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_ಸೂಚ್ಯಂಕ = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].ಸ್ಥಾನಾಂತರ = layout.ಸ್ಥಾನಾಂತರ;
            drm_desc->layers[i].planes[j].pitch  = layout.ಅಡ್ಡಸಾಲು_Pitch_2;
        }

        ಆದರೆ (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            ಹೋಗು ಕೊನೆ;
        }


        ಆದರೆ (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            ಮುಂದುವರಿ;

    }

    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;
    dst->ದತ್ತಾಂಶ[0] = (uint8_t *)drm_desc;
    dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx);

    ಆದರೆ (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    ಹಿಂತಿರುಗಿ 0;

ಕೊನೆ:
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    ಆದರೆ (free_drm_desc_on_err)
        av_free(drm_desc);
    ಆದರೆ (sync_fd >= 0)
        close(sync_fd);
    ಹಿಂತಿರುಗಿ err;
}

#ಆದರೆ CONFIG_VAAPI
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_ಗಮ್ಯ_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;
    AVFrame *tmp = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = vulkan_map_ಗಮ್ಯ_drm(hwfc, tmp, src, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = av_hwframe_map(dst, tmp, flags);
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ಚೌಕಟ್ಟು_free(&tmp);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    av_ಬಳಸದ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಆಯ್ಕೆ (dst->format) {
#ಆದರೆ CONFIG_LIBDRM
    ಸ್ಥಿತಿ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಹಿಂತಿರುಗಿ vulkan_map_ಗಮ್ಯ_drm(hwfc, dst, src, flags);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
        ಆದರೆ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಹಿಂತಿರುಗಿ vulkan_map_ಗಮ್ಯ_vaapi(hwfc, dst, src, flags);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ copy_ಬಫರ್_ದತ್ತಾಂಶ(AVHWFramesContext *hwfc, FFVk_ಬಫರ್ *vkbuf,
                            AVFrame *swf, Vk_ಬಫರ್_Image_Copy *region,
                            ಪೂರ್ಣಾಂಕ planes, ಪೂರ್ಣಾಂಕ upload)
{
    ಪೂರ್ಣಾಂಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ಪೂರ್ಣಾಂಕ bytewidth[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->ಅಗಲ, i);
        ಆದರೆ (bytewidth[i] < 0)
            ಹಿಂತಿರುಗಿ bytewidth[i];
    }

    ಆದರೆ (upload) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].ಬಫರ್_ಸ್ಥಾನಾಂತರ,
                                region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ,
                                swf->ದತ್ತಾಂಶ[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.ಎತ್ತರ);

        err = ff_vk_flush_ಬಫರ್(&p->vkctx, vkbuf, 0, VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ, 1);
        ಆದರೆ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        err = ff_vk_flush_ಬಫರ್(&p->vkctx, vkbuf, 0, VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ, 0);
        ಆದರೆ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
            av_image_copy_plane(swf->ದತ್ತಾಂಶ[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].ಬಫರ್_ಸ್ಥಾನಾಂತರ,
                                region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ,
                                bytewidth[i],
                                region[i].imageExtent.ಎತ್ತರ);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_plane_buf(AVHWFramesContext *hwfc, FFVk_ಬಫರ್ **dst,
                         AVFrame *swf, Vk_ಬಫರ್_Image_Copy *region, ಪೂರ್ಣಾಂಕ upload)
{
    ಪೂರ್ಣಾಂಕ err;
    uint32_t p_w, p_h;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    Vk_ಬಫರ್_Usage_Flags buf_usage = upload ? VK_ಬಫರ್_USAGE_TRANSFER_SRC_ಬಿಟ್ :
                                            VK_ಬಫರ್_USAGE_TRANSFER_DST_ಬಿಟ್;

    size_t buf_ಸ್ಥಾನಾಂತರ = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->ಅಗಲ, swf->ಎತ್ತರ, i);

        region[i] = (Vk_ಬಫರ್_Image_Copy) {
            .ಬಫರ್_ಸ್ಥಾನಾಂತರ = buf_ಸ್ಥಾನಾಂತರ,
            .ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_ಬಫರ್_Copy_ಅಡ್ಡಸಾಲು_Pitch_Alignment),
            .ಬಫರ್_Image_ಎತ್ತರ = p_h,
            .imageSubresource.layer_ಎಣಿಕೆ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_ಸ್ಥಾನಾಂತರ += FFALIGN(p_h*region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ,
                              p->props.properties.limits.optimal_ಬಫರ್_Copy_ಸ್ಥಾನಾಂತರ_Alignment);
    }

    err = ff_vk_get_pooled_ಬಫರ್(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  ಖಾಲಿ, buf_ಸ್ಥಾನಾಂತರ,
                                  VK_ಸ್ಮರಣೆ_PROPERTY_HOST_VISIBLE_ಬಿಟ್ |
                                  p->vkctx.host_cached_flag);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ host_map_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc, FFVk_ಬಫರ್ **dst, ಪೂರ್ಣಾಂಕ *nb_bufs,
                          AVFrame *swf, Vk_ಬಫರ್_Image_Copy *region, ಪೂರ್ಣಾಂಕ upload)
{
    ಪೂರ್ಣಾಂಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಪೂರ್ಣಾಂಕ nb_src_bufs;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_ಬಫರ್_Usage_Flags buf_usage = upload ? VK_ಬಫರ್_USAGE_TRANSFER_SRC_ಬಿಟ್ :
                                            VK_ಬಫರ್_USAGE_TRANSFER_DST_ಬಿಟ್;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    ಆಗ (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    ಆದರೆ (nb_src_bufs == 1) {
        err = ff_vk_host_map_ಬಫರ್(&p->vkctx, &dst[0],
                                    swf->ದತ್ತಾಂಶ[0], VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ, swf->buf[0],
                                    buf_usage);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
        (*nb_bufs)++;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
            region[i].ಬಫರ್_ಸ್ಥಾನಾಂತರ = dst[0]->virtual_ಸ್ಥಾನಾಂತರ +
                                     swf->ದತ್ತಾಂಶ[i] - swf->ದತ್ತಾಂಶ[0];
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (nb_src_bufs == planes) { /* One buffer per plane */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
            err = ff_vk_host_map_ಬಫರ್(&p->vkctx, &dst[i],
                                        swf->ದತ್ತಾಂಶ[i], VK_ಸಂಪೂರ್ಣ_ಗಾತ್ರ,
                                        swf->buf[i], buf_usage);
            ಆದರೆ (err < 0)
                ಹೋಗು fail;
            (*nb_bufs)++;

            region[i].ಬಫರ್_ಸ್ಥಾನಾಂತರ = dst[i]->virtual_ಸ್ಥಾನಾಂತರ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        ಹಿಂತಿರುಗಿ AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        ಪೂರ್ಣಾಂಕ align = FFMAX(desc->comp[i].ಹೆಜ್ಜೆ, p->transfer_ಸ್ಥಾನಾಂತರ_align);
        ಆದರೆ ((align & (align - 1)) || (region[i].ಬಫರ್_ಸ್ಥಾನಾಂತರ & (align - 1))) {
            err = AVERROR(EINVAL);
            ಹೋಗು fail;
        }
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, ಪೂರ್ಣಾಂಕ upload)
{
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVk_ಚೌಕಟ್ಟು *hwf_vk = (AVVk_ಚೌಕಟ್ಟು *)hwf->ದತ್ತಾಂಶ[0];
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ nb_layout_ch = 0;

    hwfc_vk->ಬೀಗ_ಚೌಕಟ್ಟು(hwfc, hwf_vk);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        ಪೂರ್ಣಾಂಕ compat = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ಎಣಿಕೆ; j++) {
            ಆದರೆ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (compat)
            ಮುಂದುವರಿ;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspect_ಮುಖವಾಡ = VK_IMAGE_ASPECT_COLOR_ಬಿಟ್,
                .level_ಎಣಿಕೆ = 1,
                .layer_ಎಣಿಕೆ = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_ಮೌಲ್ಯಗಳು = hwf_vk->sem_ಮೌಲ್ಯ,
        .semaphore_ಎಣಿಕೆ = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    ಆದರೆ (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    ಆದರೆ (upload) {
        Vk_ಸ್ಮರಣೆ_ಗಮ್ಯ_Image_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_ಸ್ಮರಣೆ_ಗಮ್ಯ_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_ಎಣಿಕೆ = 1,
            },
        };
        Vk_Copy_ಸ್ಮರಣೆ_ಗಮ್ಯ_Image_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_ಸ್ಮರಣೆ_ಗಮ್ಯ_IMAGE_INFO_EXT,
            .region_ಎಣಿಕೆ = 1,
            .pRegions = &region_info,
        };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
            ಪೂರ್ಣಾಂಕ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ಅಗಲ, swf->ಎತ್ತರ, i);

            region_info.p_Host_ಸೂಚಕ = swf->ದತ್ತಾಂಶ[i];
            region_info.ಸ್ಮರಣೆ_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ = swf->linesize[i] / desc->comp[i].ಹೆಜ್ಜೆ;
            region_info.imageSubresource.aspect_ಮುಖವಾಡ = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_ಸ್ಮರಣೆ_ಗಮ್ಯ_Image_EXT(hwctx->act_dev, &copy_info);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        Vk_Image_ಗಮ್ಯ_ಸ್ಮರಣೆ_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ಗಮ್ಯ_ಸ್ಮರಣೆ_COPY_EXT,
            .imageSubresource = {
                .layer_ಎಣಿಕೆ = 1,
            },
        };
        Vk_Copy_Image_ಗಮ್ಯ_ಸ್ಮರಣೆ_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_ಗಮ್ಯ_ಸ್ಮರಣೆ_INFO_EXT,
            .region_ಎಣಿಕೆ = 1,
            .pRegions = &region_info,
        };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
            ಪೂರ್ಣಾಂಕ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ಅಗಲ, swf->ಎತ್ತರ, i);

            region_info.p_Host_ಸೂಚಕ = swf->ದತ್ತಾಂಶ[i];
            region_info.ಸ್ಮರಣೆ_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ = swf->linesize[i] / desc->comp[i].ಹೆಜ್ಜೆ;
            region_info.imageSubresource.aspect_ಮುಖವಾಡ = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_Image_ಗಮ್ಯ_ಸ್ಮರಣೆ_EXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_ಚೌಕಟ್ಟು(hwfc, hwf_vk);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_ಚೌಕಟ್ಟು(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 ಪೂರ್ಣಾಂಕ upload)
{
    ಪೂರ್ಣಾಂಕ err;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಪೂರ್ಣಾಂಕ host_mapped = 0;

    AVVk_ಚೌಕಟ್ಟು *hwf_vk = (AVVk_ಚೌಕಟ್ಟು *)hwf->ದತ್ತಾಂಶ[0];
    Vk_ಬಫರ್_Image_Copy region[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು]; // always one per plane

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_images = ff_vk_ಎಣಿಕೆ_images(hwf_vk);

    Vk_Image_ಸ್ಮರಣೆ_Barrier2 img_bar[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ nb_img_bar = 0;

    FFVk_ಬಫರ್ *bufs[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
    ಪೂರ್ಣಾಂಕ nb_bufs = 0;

    Vk_Command_ಬಫರ್ cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    ಆದರೆ ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (swf->ಅಗಲ > hwfc->ಅಗಲ || swf->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಪೂರ್ಣಾಂಕ host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ಬಿಟ್_EXT;
    ಪೂರ್ಣಾಂಕ host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_ಸ್ಮರಣೆ &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
        ಆದರೆ (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    ಆದರೆ (!upload && host_copy) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
            ಪೂರ್ಣಾಂಕ compat = 0;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ಎಣಿಕೆ; j++) {
                ಆದರೆ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }
            ಆದರೆ (!compat) {
                host_copy = 0;
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (host_copy)
        ಹಿಂತಿರುಗಿ vulkan_transfer_host(hwfc, hwf, swf, upload);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < av_pix_fmt_ಎಣಿಕೆ_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->ಅಗಲ, swf->ಎತ್ತರ, i);

        /* Buffer region for this plane */
        region[i] = (Vk_ಬಫರ್_Image_Copy) {
            .ಬಫರ್_ಸ್ಥಾನಾಂತರ = 0,
            .ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ = FFABS(swf->linesize[i]),
            .ಬಫರ್_Image_ಎತ್ತರ = p_h,
            .imageSubresource.layer_ಎಣಿಕೆ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    ಆದರೆ (host_map) {
        err = host_map_ಚೌಕಟ್ಟು(hwfc, bufs, &nb_bufs, swf, region, upload);
        ಆದರೆ (err >= 0)
            host_mapped = 1;
    }

    ಆದರೆ (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        ಆದರೆ (err < 0)
            ಹೋಗು ಕೊನೆ;
        nb_bufs = 1;

        ಆದರೆ (upload) {
            err = copy_ಬಫರ್_ದತ್ತಾಂಶ(hwfc, bufs[0], swf, region, planes, 1);
            ಆದರೆ (err < 0)
                ಹೋಗು ಕೊನೆ;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_ಆರಂಭ(&p->vkctx, exec);
    ಆದರೆ (err < 0)
        ಹೋಗು ಕೊನೆ;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_ಕೂಡಿಸು_dep_ಚೌಕಟ್ಟು(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                                   VK_PIPELINE_STAGE_2_TRANSFER_ಬಿಟ್);
    ಆದರೆ (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        ಹೋಗು ಕೊನೆ;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    ಆದರೆ (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        ಆದರೆ (host_mapped) {
            err = ff_vk_exec_ಕೂಡಿಸು_dep_sw_ಚೌಕಟ್ಟು(&p->vkctx, exec, swf);
            ಆದರೆ (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                ಹೋಗು ಕೊನೆ;
            }
        }

        /* Add the buffers as a dependency */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_bufs; i++)
            ff_vk_exec_ಕೂಡಿಸು_dep_refstruct(&p->vkctx, exec, bufs[i]);
    }

    ff_vk_ಚೌಕಟ್ಟು_barrier(&p->vkctx, exec, hwf, img_bar, &nb_img_bar,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ಬಿಟ್,
                        VK_PIPELINE_STAGE_2_TRANSFER_ಬಿಟ್_KHR,
                        upload ? VK_ACCESS_TRANSFER_WRITE_ಬಿಟ್ :
                                 VK_ACCESS_TRANSFER_READ_ಬಿಟ್,
                        upload ? VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                        p->nb_img_qfs > 1 ? VK_ಸರತಿ_FAMILY_IGNORED : p->img_qfs[0]);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_ಸ್ಮರಣೆ_Barriers = img_bar,
            .image_ಸ್ಮರಣೆ_Barrier_ಎಣಿಕೆ = nb_img_bar,
    });

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        ಪೂರ್ಣಾಂಕ buf_idx = FFMIN(i, (nb_bufs - 1));
        ಪೂರ್ಣಾಂಕ img_idx = FFMIN(i, (nb_images - 1));
        FFVk_ಬಫರ್ *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ;
        region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ /= desc->comp[i].ಹೆಜ್ಜೆ;
        region[i].imageSubresource.aspect_ಮುಖವಾಡ = ff_vk_aspect_flag(hwf, i);

        ಆದರೆ (upload)
            vk->Cmd_Copy_ಬಫರ್_ಗಮ್ಯ_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        ಇಲ್ಲದಿದ್ದರೆ
            vk->Cmd_Copy_Image_ಗಮ್ಯ_ಬಫರ್(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].ಬಫರ್_ಅಡ್ಡಸಾಲು_ಉದ್ದಳತೆ = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ಆದರೆ (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        ಆದರೆ (!host_mapped)
            err = copy_ಬಫರ್_ದತ್ತಾಂಶ(hwfc, bufs[0], swf, region, planes, 0);
    }

ಕೊನೆ:
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    av_ಬಳಸದ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಆಯ್ಕೆ (src->format) {
#ಆದರೆ CONFIG_CUDA
    ಸ್ಥಿತಿ AV_PIX_FMT_CUDA:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ಸ್ಮರಣೆ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ಇಲ್ಲದಿದ್ದರೆ
        ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ಸ್ಮರಣೆ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ vulkan_transfer_ದತ್ತಾಂಶ_from_cuda(hwfc, dst, src);
        av_fallthrough;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ vulkan_transfer_ಚೌಕಟ್ಟು(hwfc, (AVFrame *)src, dst, 1);
    }
}

#ಆದರೆ CONFIG_CUDA
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ err;
    CUcontext dummy;
    AVVk_ಚೌಕಟ್ಟು *dst_f;
    AVVk_ಚೌಕಟ್ಟು_ಆಂತರಿಕ *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv *fp = hwfc->hwctx;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಪೂರ್ಣಾಂಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ಆಂತರಿಕ *cu_ಆಂತರಿಕ = cuda_dev->ಆಂತರಿಕ;
    CudaFunctions *cu = cu_ಆಂತರಿಕ->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] = { 0 };

    dst_f = (AVVk_ಚೌಕಟ್ಟು *)src->ದತ್ತಾಂಶ[0];
    nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);

    err = prepare_ಚೌಕಟ್ಟು(hwfc, &fp->upload_exec, dst_f, PREP_ಬಹುಲಕ_EXTERNAL_EXPORT);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(cuda_dev->cuda_ctx));
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    err = vulkan_export_ಗಮ್ಯ_cuda(hwfc, dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, src);
    ಆದರೆ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಹಿಂತಿರುಗಿ err;
    }

    dst_int = dst_f->ಆಂತರಿಕ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 0;
        s_s_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ಹರಿವು));
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dst_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->ದತ್ತಾಂಶ[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .src_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        ಪೂರ್ಣಾಂಕ w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->ಅಗಲ, hwfc->ಎತ್ತರ, i);

        cpy.ಅಗಲ_ಒಳ_ಬೈಟುಗಳು = w * desc->comp[i].ಹೆಜ್ಜೆ;
        cpy.ಎತ್ತರ_2 = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ಹರಿವು));
        ಆದರೆ (err < 0)
            ಹೋಗು fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ಹರಿವು));
    ಆದರೆ (err < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_images; i++)
        dst_f->sem_ಮೌಲ್ಯ[i]++;

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    ಹಿಂತಿರುಗಿ prepare_ಚೌಕಟ್ಟು(hwfc, &fp->upload_exec, dst_f, PREP_ಬಹುಲಕ_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    vulkan_free_ಆಂತರಿಕ(p, dst_f);
    av_ಬಫರ್_unref(&dst->buf[0]);
    ಹಿಂತಿರುಗಿ err;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    av_ಬಳಸದ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಆಯ್ಕೆ (dst->format) {
#ಆದರೆ CONFIG_CUDA
    ಸ್ಥಿತಿ AV_PIX_FMT_CUDA:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
        ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ಸ್ಮರಣೆ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ಇಲ್ಲದಿದ್ದರೆ
        ಆದರೆ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ಸ್ಮರಣೆ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ vulkan_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ_cuda(hwfc, dst, src);
        av_fallthrough;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಆದರೆ (dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ vulkan_transfer_ಚೌಕಟ್ಟು(hwfc, dst, (AVFrame *)src, 0);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vulkan_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ಪೂರ್ಣಾಂಕ flags)
{
    ಹಿಂತಿರುಗಿ vulkan_ಚೌಕಟ್ಟುಗಳು_init(dst_fc);
}

AVVk_ಚೌಕಟ್ಟು *av_vk_ಚೌಕಟ್ಟು_alloc(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ err;
    AVVk_ಚೌಕಟ್ಟು *f = av_mallocz(ಗಾತ್ರ(AVVk_ಚೌಕಟ್ಟು));
    ಆದರೆ (!f)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    f->ಆಂತರಿಕ = av_mallocz(ಗಾತ್ರ(*f->ಆಂತರಿಕ));
    ಆದರೆ (!f->ಆಂತರಿಕ) {
        av_free(f);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    err = pthread_mutex_init(&f->ಆಂತರಿಕ->update_mutex, ಖಾಲಿ);
    ಆದರೆ (err != 0) {
        av_free(f->ಆಂತರಿಕ);
        av_free(f);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ f;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(VulkanDevicePriv),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(Vulkan_ಚೌಕಟ್ಟುಗಳು_Priv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .ಚೌಕಟ್ಟುಗಳು_get_constraints = &vulkan_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init            = vulkan_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = vulkan_get_ಬಫರ್,
    .ಚೌಕಟ್ಟುಗಳು_uninit          = vulkan_ಚೌಕಟ್ಟುಗಳು_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = vulkan_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from     = vulkan_transfer_ದತ್ತಾಂಶ_from,

    .map_ಗಮ್ಯ                 = vulkan_map_ಗಮ್ಯ,
    .map_from               = vulkan_map_from,
    .ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ       = &vulkan_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
