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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NO_PROTOTYPES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_ENABLE_BETA_EXTENSIONS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#ਅਨ੍ਤਰ੍ਭਾਵ <versionhelpers.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32dlfcn.h"
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uuid.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_loader.h"

#ਜੇ CONFIG_VAAPI
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vaapi.h"
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_LIBDRM
#ਜੇ CONFIG_VAAPI
#ਅਨ੍ਤਰ੍ਭਾਵ <va/va_drmcommon.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __linux__
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysmacros.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/stat.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xf86drm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <drm_fourcc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_drm.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_LINUX_DMA_BUF_H
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/ioctl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <linux/dma-buf.h>
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_CUDA
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_cuda_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cuda_check.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    Vk_Physical_Device_Workgroup_ਸਮ੍ਰਿਤੀ_Explicit_Layout_Features_KHR explicit_mem_layout;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    Vk_Physical_Device_Shader_Long_ਸਦਿਸ਼_Features_EXT long_ਸਦਿਸ਼;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_zero_initialize_device_ਸਮ੍ਰਿਤੀ
    Vk_Physical_Device_Zero_Initialize_Device_ਸਮ੍ਰਿਤੀ_Features_EXT zero_initialize;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#ਜੇ_ਅੰਤ

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#ਜੇ_ਅੰਤ

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    Vk_Physical_Device_Cooperative_ਮੈਟ੍ਰਿਕਸ_Features_KHR cooperative_ਮੈਟ੍ਰਿਕਸ;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync;
#ਜੇ_ਅੰਤ
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    ਖਾਲੀ *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkan_Device_ਕਤਾਰ_Family *compute_qf;
    AVVulkan_Device_ਕਤਾਰ_Family *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    Vk_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties mprops;
    Vk_Physical_Device_External_ਸਮ੍ਰਿਤੀ_Host_Properties_EXT hprops;
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
    ਪੂਰਨ use_ਰੇਖਿਕ_images;

    /* Option to allocate all image planes in a single allocation */
    ਪੂਰਨ contiguous_planes;

    /* Disable multiplane images */
    ਪੂਰਨ disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    ਪੂਰਨ avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    ਪੂਰਨ transfer_ਵਿੱਥ_align;

    /* Maximum queues */
    ਪੂਰਨ ਹੱਦਬੰਦੀ_queues;
} VulkanDevicePriv;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vulkan_ਚੌਖਟੇ_Priv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkan_ਚੌਖਟੇ_Context p;

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
    ਪੂਰਨ export_requires_dedicated;
} Vulkan_ਚੌਖਟੇ_Priv;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#ਜੇ CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternal_ਸਮ੍ਰਿਤੀ ext_mem[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    CUmipmappedArray cu_mma[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    CUarray cu_array[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    CUexternalSemaphore cu_sem[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    HANDLE ext_mem_handle[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    HANDLE ext_sem_handle[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
} AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ;

/* Initialize all structs in VulkanDeviceFeatures */
ਸਥਿਰ ਖਾਲੀ device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_ਸਦਿਸ਼, FF_VK_EXT_LONG_ਸਦਿਸ਼,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ਸਦਿਸ਼_FEATURES_EXT);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_zero_initialize_device_ਸਮ੍ਰਿਤੀ
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_ਸਮ੍ਰਿਤੀ_FEATURES_EXT);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#ਜੇ_ਅੰਤ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#ਜੇ_ਅੰਤ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_ਮੈਟ੍ਰਿਕਸ, FF_VK_EXT_COOP_ਮੈਟ੍ਰਿਕਸ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ਮੈਟ੍ਰਿਕਸ_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_ਸਮ੍ਰਿਤੀ_EXPLICIT_LAYOUT_FEATURES_KHR);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync, FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#ਜੇ_ਅੰਤ

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
ਸਥਿਰ ਖਾਲੀ device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COPY_VAL(VAL)        \
    ਕਰੋ {                     \
        dst->VAL = src->VAL; \
    } ਜਦੋਂ (0)              \

    COPY_VAL(device.features.shaderImageGatherExtended);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);
    COPY_VAL(device.features.fragmentStoresAndAtomics);
    COPY_VAL(device.features.ਸ਼ੀਰਸ਼_Pipeline_Stores_And_Atomics);
    COPY_VAL(device.features.shaderInt64);
    COPY_VAL(device.features.shaderInt16);
    COPY_VAL(device.features.shaderFloat64);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);

    COPY_VAL(vulkan_1_1.samplerYcbcrConversion);
    COPY_VAL(vulkan_1_1.storage_ਧੱਕੋ_Constant16);
    COPY_VAL(vulkan_1_1.storage_Buffer16_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);
    COPY_VAL(vulkan_1_1.ਇਕਸਾਰ_And_Storage_Buffer16_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalar_ਖੰਡ_Layout);
    COPY_VAL(vulkan_1_2.ਬਫਰ_Device_ਪਤਾ);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_ਧੱਕੋ_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storage_Buffer8_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);
    COPY_VAL(vulkan_1_2.ਇਕਸਾਰ_And_Storage_Buffer8_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_ਬਫਰ_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkan_ਸਮ੍ਰਿਤੀ_Model);
    COPY_VAL(vulkan_1_2.vulkan_ਸਮ੍ਰਿਤੀ_Model_Device_Scope);
    COPY_VAL(vulkan_1_2.vulkan_ਸਮ੍ਰਿਤੀ_Model_Availability_Visibility_Chains);
    COPY_VAL(vulkan_1_2.ਇਕਸਾਰ_ਬਫਰ_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_ਇਕਸਾਰ_ਬਫਰ_Array_Non_ਇਕਸਾਰ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Sampled_Image_Array_Non_ਇਕਸਾਰ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_ਬਫਰ_Array_Non_ਇਕਸਾਰ_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_Image_Array_Non_ਇਕਸਾਰ_Indexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.compute_ਭਰਿਆ_Subgroups);
    COPY_VAL(vulkan_1_3.subgroup_ਮਾਪ_Control);
    COPY_VAL(vulkan_1_3.shader_Zero_Initialize_Workgroup_ਸਮ੍ਰਿਤੀ);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    COPY_VAL(long_ਸਦਿਸ਼.long_ਸਦਿਸ਼_2);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_zero_initialize_device_ਸਮ੍ਰਿਤੀ
    COPY_VAL(zero_initialize.zero_Initialize_Device_ਸਮ੍ਰਿਤੀ);
#ਜੇ_ਅੰਤ

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#ਜੇ_ਅੰਤ

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_ਮੈਟ੍ਰਿਕਸ.cooperative_ਮੈਟ੍ਰਿਕਸ_2);

    COPY_VAL(atomic_float.shader_ਬਫਰ_Float32_Atomics);
    COPY_VAL(atomic_float.shader_ਬਫਰ_Float32_Atomic_ਜੋੜੋ);

    COPY_VAL(explicit_mem_layout.workgroup_ਸਮ੍ਰਿਤੀ_Explicit_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_ਸਮ੍ਰਿਤੀ_Explicit_Layout_Scalar_ਖੰਡ_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_ਸਮ੍ਰਿਤੀ_Explicit_Layout8_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);
    COPY_VAL(explicit_mem_layout.workgroup_ਸਮ੍ਰਿਤੀ_Explicit_Layout16_ਦੋਆਧਾਰੀ_ਅੰਕ_Access);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    COPY_VAL(ਅੰਦਰੂਨੀ_ਕਤਾਰ_sync.internallySynchronizedQueues);
#ਜੇ_ਅੰਤ

    COPY_VAL(optical_flow.opticalFlow);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ COPY_VAL
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_IMAGE_ASPECT_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_IMAGE_ASPECT_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_IMAGE_ASPECT_PLANE_2_ਦੋਆਧਾਰੀ_ਅੰਕ)

ਸਥਿਰ ਅਚਲ ਬਣਤਰ FFVk_Format_ਇੰਦਰਾਜ {
    VkFormat vkf;
    ਗਿਣਤੀ AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    ਪੂਰਨ vk_planes;
    ਪੂਰਨ nb_images;
    ਪੂਰਨ nb_images_fallback;
    ਅਚਲ VkFormat fallback[5];
} vk_formats_list[] = {
    /* Gray formats */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GRAY8,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY10,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY12,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY14,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GRAY32,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GRAYF32, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32_SFLOAT } },

    /* RGB formats */
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGRA,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGBA,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8_UNORM,             AV_PIX_FMT_RGB24,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8_UNORM             } },
    { VK_FORMAT_B8G8R8_UNORM,             AV_PIX_FMT_BGR24,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_B8G8R8_UNORM             } },
    { VK_FORMAT_R16G16B16_UNORM,          AV_PIX_FMT_RGB48,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16_UNORM          } },
    { VK_FORMAT_R16G16B16A16_UNORM,       AV_PIX_FMT_RGBA64,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM       } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGR0,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGB0,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, AV_PIX_FMT_X2RGB10, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_A2B10G10R10_UNORM_PACK32, AV_PIX_FMT_X2BGR10, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_A2B10G10R10_UNORM_PACK32 } },
    { VK_FORMAT_R32G32B32_SFLOAT,         AV_PIX_FMT_RGBF32,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32G32B32_SFLOAT         } },
    { VK_FORMAT_R16G16B16A16_SFLOAT,      AV_PIX_FMT_RGBAF16, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_SFLOAT      } },
    { VK_FORMAT_R32G32B32A32_SFLOAT,      AV_PIX_FMT_RGBAF32, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32G32B32A32_SFLOAT      } },
    { VK_FORMAT_R32G32B32_UINT,           AV_PIX_FMT_RGB96,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32G32B32_UINT           } },
    { VK_FORMAT_R32G32B32A32_UINT,        AV_PIX_FMT_RGBA128, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R32G32B32A32_UINT        } },

    /* Planar RGB */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRP,     VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP10,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP12,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP14,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP16,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRPF16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT  } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRPF32,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* XYZ */
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_XYZP12,   VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar RGB + Alpha */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRAP,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP10,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP12,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP14,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRAPF16, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GBRAP32,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRAPF32, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* Bayer */
    { VK_FORMAT_R16_UNORM, AV_PIX_FMT_BAYER_RGGB16, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16_UNORM } },

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
    { VK_FORMAT_G8B8G8R8_422_UNORM,                     AV_PIX_FMT_YUYV422, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_B8G8R8G8_422_UNORM,                     AV_PIX_FMT_UYVY422, VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, AV_PIX_FMT_Y210,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, AV_PIX_FMT_Y212,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G16B16G16R16_422_UNORM,                 AV_PIX_FMT_Y216,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },

    /* Planar YUVA 420 at 8, 10 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA420P,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P10,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA422P,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P10,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P12,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA444P,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P10,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P12,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P16,  VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Single plane 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32,               AV_PIX_FMT_XV30,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,     AV_PIX_FMT_XV36,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_R16G16B16A16_UNORM,                     AV_PIX_FMT_XV48,    VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
};
ਸਥਿਰ ਅਚਲ ਪੂਰਨ nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ਅਚਲ VkFormat *av_vkfmt_from_pixfmt(ਗਿਣਤੀ AVPixelFormat p)
{
    ਲਈ (ਪੂਰਨ i = 0; i < nb_vk_formats_list; i++)
        ਜੇ (vk_formats_list[i].pixfmt == p)
            ਵਾਪਸ vk_formats_list[i].fallback;
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ FFVk_Format_ਇੰਦਰਾਜ *vk_ਲੱਭੋ_format_ਇੰਦਰਾਜ(ਗਿਣਤੀ AVPixelFormat p)
{
    ਲਈ (ਪੂਰਨ i = 0; i < nb_vk_formats_list; i++)
        ਜੇ (vk_formats_list[i].pixfmt == p)
            ਵਾਪਸ &vk_formats_list[i];
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, ਗਿਣਤੀ AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ], /* Output format list */
                              ਪੂਰਨ *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              ਪੂਰਨ disable_multiplane, ਪੂਰਨ need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ਅਚਲ VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_vk_formats_list; i++) {
        ਜੇ (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ਅਗਲਾ = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            ਪੂਰਨ basics_primary = 0, basics_secondary = 0;
            ਪੂਰਨ storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_ਰੇਖਿਕ ?
                             fprops.ਰੇਖਿਕ_Tiling_Features : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ਦੋਆਧਾਰੀ_ਅੰਕ);

            ਜੇ (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_ਰੇਖਿਕ ?
                                  fprops.ਰੇਖਿਕ_Tiling_Features : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ਦੋਆਧਾਰੀ_ਅੰਕ);
            } ਨਹੀਂਤਾਂ {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            ਜੇ (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                ਜੇ (fmts) {
                    ਜੇ (vk_formats_list[i].nb_images > 1) {
                        ਲਈ (ਪੂਰਨ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } ਨਹੀਂਤਾਂ {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                ਜੇ (nb_images)
                    *nb_images = 1;
                ਜੇ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ਜੇ (supported_usage)
                    *supported_usage = ff_vk_map_feats_ਮੰਜ਼ਿਲ_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ : 0);
                ਵਾਪਸ 0;
            } ਨਹੀਂਤਾਂ ਜੇ (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                ਜੇ (fmts) {
                    ਲਈ (ਪੂਰਨ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                ਜੇ (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                ਜੇ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ਜੇ (supported_usage)
                    *supported_usage = ff_vk_map_feats_ਮੰਜ਼ਿਲ_usage(feats_secondary);
                ਵਾਪਸ 0;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ AVERROR(ENOTSUP);
            }
        }
    }

    ਵਾਪਸ AVERROR(EINVAL);
}

#ਜੇ CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ਅਚਲ ਅੱਖਰ *pName);
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ ਲੱਦੋ_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#ਜੇ CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#ਨਹੀਂਤਾਂ
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *lib_ਨਾਂ[] = {
#ਜੇ defined(_WIN32)
        "vulkan-1.dll",
#ਜਾਂਜੇ defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#ਨਹੀਂਤਾਂ
        "libvulkan.so.1",
        "libvulkan.so",
#ਜੇ_ਅੰਤ
    };

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(lib_ਨਾਂ); i++) {
        p->libvulkan = dlopen(lib_ਨਾਂ[i], RTLD_NOW | RTLD_LOCAL);
        ਜੇ (p->libvulkan)
            ਰੋਕੋ;
    }

    ਜੇ (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#ਜੇ_ਅੰਤ /* CONFIG_VULKAN_STATIC */

    ਵਾਪਸ 0;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VulkanOptExtension {
    ਅਚਲ ਅੱਖਰ *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

ਸਥਿਰ ਅਚਲ VulkanOptExtension optional_instance_exts[] = {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#ਜੇ_ਅੰਤ
    { 0 },
};

ਸਥਿਰ ਅਚਲ VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_ਧੱਕੋ_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_ਧੱਕੋ_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_ਮੈਟ੍ਰਿਕਸ_EXTENSION_NAME,               FF_VK_EXT_COOP_ਮੈਟ੍ਰਿਕਸ            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_ਸਮ੍ਰਿਤੀ_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    { VK_EXT_SHADER_LONG_ਸਦਿਸ਼_EXTENSION_NAME,               FF_VK_EXT_LONG_ਸਦਿਸ਼            },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_zero_initialize_device_ਸਮ੍ਰਿਤੀ
    { VK_EXT_ZERO_INITIALIZE_DEVICE_ਸਮ੍ਰਿਤੀ_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#ਜੇ_ਅੰਤ
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC    },
#ਜੇ_ਅੰਤ
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_ਸਮ੍ਰਿਤੀ     },
    { VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_ਸਮ੍ਰਿਤੀ },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_ਸਮ੍ਰਿਤੀ   },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    { VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_ਸਮ੍ਰਿਤੀ  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#ਜੇ_ਅੰਤ

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_ਕਤਾਰ_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_ਕਤਾਰ            },
    { VK_KHR_VIDEO_ENCODE_ਕਤਾਰ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_ਕਤਾਰ     },
    { VK_KHR_VIDEO_DECODE_ਕਤਾਰ_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_ਕਤਾਰ     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#ਜੇ_ਅੰਤ
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

ਅਚਲ ਅੱਖਰ **av_vk_get_optional_instance_extensions(ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਅਚਲ ਅੱਖਰ **exts = av_malloc_array(ਆਕਾਰ(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    ਜੇ (!exts)
        ਵਾਪਸ ਨਿਰਾ;

    ਲਈ (ਪੂਰਨ i = 0; i < (ਪੂਰਨ)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *ਗਿਣਤੀ_2 = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    ਵਾਪਸ exts;
}

ਅਚਲ ਅੱਖਰ **av_vk_get_optional_device_extensions(ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਅਚਲ ਅੱਖਰ **exts = av_malloc_array(ਆਕਾਰ(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    ਜੇ (!exts)
        ਵਾਪਸ ਨਿਰਾ;

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *ਗਿਣਤੀ_2 = FF_ARRAY_ELEMS(optional_device_exts);
    ਵਾਪਸ exts;
}

ਸਥਿਰ VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(Vk_Debug_Utils_ਸੁਨੇਹਾ_Severity_Flag_ਬਿੱਟ_EXT severity,
                                    Vk_Debug_Utils_ਸੁਨੇਹਾ_Type_Flags_EXT ਸੁਨੇਹਾ_Type,
                                    ਅਚਲ Vk_Debug_Utils_Messenger_Callback_ਅੰਕੜੇ_EXT *ਅੰਕੜੇ,
                                    ਖਾਲੀ *priv)
{
    ਪੂਰਨ l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    ਚੋਣ (ਅੰਕੜੇ->ਸੁਨੇਹਾ_Id_ਸੰਖਿਆ) {
    ਹਾਲਤ 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    ਹਾਲਤ 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        ਵਾਪਸ VK_FALSE;
    ਮੂਲ:
        ਰੋਕੋ;
    }

    ਚੋਣ (severity) {
    ਹਾਲਤ VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_VERBOSE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT: l = AV_LOG_VERBOSE; ਰੋਕੋ;
    ਹਾਲਤ VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_INFO_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT:    l = AV_LOG_INFO;    ਰੋਕੋ;
    ਹਾਲਤ VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_WARNING_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT: l = AV_LOG_WARNING; ਰੋਕੋ;
    ਹਾਲਤ VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_ERROR_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT:   l = AV_LOG_ERROR;   ਰੋਕੋ;
    ਮੂਲ:                                              l = AV_LOG_DEBUG;   ਰੋਕੋ;
    }

    av_log(ctx, l, "%s\n", ਅੰਕੜੇ->p_ਸੁਨੇਹਾ);
    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕੜੇ->cmd_Buf_Label_ਗਿਣਤੀ; i++)
        av_log(ctx, l, "\t%i: %s\n", i, ਅੰਕੜੇ->pCmdBufLabels[i].pLabelName);

    ਵਾਪਸ VK_FALSE;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(list, ਗਿਣਤੀ_2, val)                                      \
    ਕਰੋ {                                                                       \
        list = av_realloc_array(list, ++ਗਿਣਤੀ_2, ਆਕਾਰ(*list));                 \
        ਜੇ (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            ਜਾਓ fail;                                                         \
        }                                                                      \
        list[ਗਿਣਤੀ_2 - 1] = av_strdup(val);                                      \
        ਜੇ (!list[ਗਿਣਤੀ_2 - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            ਜਾਓ fail;                                                         \
        }                                                                      \
    } ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RELEASE_PROPS(props, ਗਿਣਤੀ_2)                                            \
    ਜੇ (props) {                                                               \
        ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; i++)                                        \
            av_free((ਖਾਲੀ *)((props)[i]));                                     \
        av_free((ਖਾਲੀ *)props);                                                \
    }

ਸਥਿਰ ਪੂਰਨ vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_ਮਾਪ max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ);
    ਲਈ (ਪੂਰਨ i = 0; i < p->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ; i++) {
        ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Type type = p->mprops.ਸਮ੍ਰਿਤੀ_Types[i];
        ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_ਢੇਰ ਢੇਰ = p->mprops.ਸਮ੍ਰਿਤੀ_Heaps[type.ਢੇਰ_ਸੂਚਕਾਂਕ_2];
        ਜੇ (!(type.propertyFlags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_DEVICE_LOCAL_ਦੋਆਧਾਰੀ_ਅੰਕ))
            ਜਾਰੀ;
        max_vram = FFMAX(max_vram, ਢੇਰ.ਮਾਪ);
        ਜੇ (type.propertyFlags & VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ)
            max_visible_vram = FFMAX(max_visible_vram, ਢੇਰ.ਮਾਪ);
    }

    ਵਾਪਸ max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

ਸਥਿਰ ਪੂਰਨ check_extensions(AVHWDeviceContext *ctx, ਪੂਰਨ dev, AVDictionary *opts,
                            ਅਚਲ ਅੱਖਰ * ਅਚਲ **dst, uint32_t *ਅੰਕ,
                            ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ debug_ਬਹੁਲਕ)
{
    ਅਚਲ ਅੱਖਰ *tstr;
    ਅਚਲ ਅੱਖਰ **extension_ਨਾਂ = ਨਿਰਾ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਪੂਰਨ err = 0, ਮਿਲਿਆ, extensions_ਮਿਲਿਆ = 0;

    ਅਚਲ ਅੱਖਰ *mod;
    ਪੂਰਨ optional_exts_ਅੰਕ;
    uint32_t sup_ext_ਗਿਣਤੀ;
    ਅੱਖਰ *user_exts_str = ਨਿਰਾ;
    AVDictionary_ਇੰਦਰਾਜ *user_exts;
    VkExtensionProperties *sup_ext;
    ਅਚਲ VulkanOptExtension *optional_exts;

    ਜੇ (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_ਅੰਕ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", ਨਿਰਾ, 0);
        ਜੇ (user_exts) {
            user_exts_str = av_strdup(user_exts->ਮੁੱਲ);
            ਜੇ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(ਨਿਰਾ, &sup_ext_ਗਿਣਤੀ, ਨਿਰਾ);
        sup_ext = av_malloc_array(sup_ext_ਗਿਣਤੀ, ਆਕਾਰ(VkExtensionProperties));
        ਜੇ (!sup_ext)
            ਵਾਪਸ AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(ਨਿਰਾ, &sup_ext_ਗਿਣਤੀ, sup_ext);
    } ਨਹੀਂਤਾਂ {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_ਅੰਕ = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", ਨਿਰਾ, 0);
        ਜੇ (user_exts) {
            user_exts_str = av_strdup(user_exts->ਮੁੱਲ);
            ਜੇ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ਨਿਰਾ,
                                               &sup_ext_ਗਿਣਤੀ, ਨਿਰਾ);
        sup_ext = av_malloc_array(sup_ext_ਗਿਣਤੀ, ਆਕਾਰ(VkExtensionProperties));
        ਜੇ (!sup_ext)
            ਵਾਪਸ AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ਨਿਰਾ,
                                               &sup_ext_ਗਿਣਤੀ, sup_ext);
    }

    ਲਈ (ਪੂਰਨ i = 0; i < optional_exts_ਅੰਕ; i++) {
        tstr = optional_exts[i].name;
        ਮਿਲਿਆ = 0;

        /* Check if the device has ReBAR for host image copies */
        ਜੇ (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            ਜਾਰੀ;

        ਜੇ (dev &&
            ((debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            ਜਾਰੀ;
        }

        ਲਈ (ਪੂਰਨ j = 0; j < sup_ext_ਗਿਣਤੀ; j++) {
            ਜੇ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ਮਿਲਿਆ = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (!ਮਿਲਿਆ)
            ਜਾਰੀ;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(extension_ਨਾਂ, extensions_ਮਿਲਿਆ, tstr);
    }

    ਜੇ (!dev &&
        ((debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        ਮਿਲਿਆ = 0;
        ਲਈ (ਪੂਰਨ j = 0; j < sup_ext_ਗਿਣਤੀ; j++) {
            ਜੇ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ਮਿਲਿਆ = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (ਮਿਲਿਆ) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(extension_ਨਾਂ, extensions_ਮਿਲਿਆ, tstr);
        } ਨਹੀਂਤਾਂ {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ਜਾਓ fail;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_shader_relaxed_extended_instruction
    ਜੇ ((debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        ਮਿਲਿਆ = 0;
        ਲਈ (ਪੂਰਨ j = 0; j < sup_ext_ਗਿਣਤੀ; j++) {
            ਜੇ (!strcmp(tstr, sup_ext[j].extensionName)) {
                ਮਿਲਿਆ = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (!ਮਿਲਿਆ) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ਜਾਓ fail;
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (user_exts_str) {
        ਅੱਖਰ *save, *token = av_strtok(user_exts_str, "+", &save);
        ਜਦੋਂ (token) {
            ਮਿਲਿਆ = 0;
            ਲਈ (ਪੂਰਨ j = 0; j < sup_ext_ਗਿਣਤੀ; j++) {
                ਜੇ (!strcmp(token, sup_ext[j].extensionName)) {
                    ਮਿਲਿਆ = 1;
                    ਰੋਕੋ;
                }
            }
            ਜੇ (ਮਿਲਿਆ) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(extension_ਨਾਂ, extensions_ਮਿਲਿਆ, token);
            } ਨਹੀਂਤਾਂ {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(ਨਿਰਾ, "+", &save);
        }
    }

    *dst = extension_ਨਾਂ;
    *ਅੰਕ = extensions_ਮਿਲਿਆ;

    av_free(user_exts_str);
    av_free(sup_ext);
    ਵਾਪਸ 0;

fail:
    RELEASE_PROPS(extension_ਨਾਂ, extensions_ਮਿਲਿਆ);
    av_free(user_exts_str);
    av_free(sup_ext);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ਅਚਲ ਅੱਖਰ * ਅਚਲ **dst, uint32_t *ਅੰਕ,
                        ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ *debug_ਬਹੁਲਕ)
{
    ਪੂਰਨ err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ਸਥਿਰ ਅਚਲ ਅੱਖਰ layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    ਪੂਰਨ layer_standard_validation_ਮਿਲਿਆ = 0;

    uint32_t sup_layer_ਗਿਣਤੀ;
    VkLayerProperties *sup_layers;

    AVDictionary_ਇੰਦਰਾਜ *user_layers = av_dict_get(opts, "layers", ਨਿਰਾ, 0);
    ਅੱਖਰ *user_layers_str = ਨਿਰਾ;
    ਅੱਖਰ *save, *token;

    ਅਚਲ ਅੱਖਰ **enabled_layers = ਨਿਰਾ;
    uint32_t enabled_layers_ਗਿਣਤੀ = 0;

    AVDictionary_ਇੰਦਰਾਜ *debug_opt = av_dict_get(opts, "debug", ਨਿਰਾ, 0);
    ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ ਬਹੁਲਕ;

    *debug_ਬਹੁਲਕ = ਬਹੁਲਕ = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_ਗਿਣਤੀ, ਨਿਰਾ);
    sup_layers = av_malloc_array(sup_layer_ਗਿਣਤੀ, ਆਕਾਰ(VkLayerProperties));
    ਜੇ (!sup_layers)
        ਵਾਪਸ AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_ਗਿਣਤੀ, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    ਲਈ (ਪੂਰਨ i = 0; i < sup_layer_ਗਿਣਤੀ; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    ਜੇ (!debug_opt && !user_layers)
        ਜਾਓ ਸਿਰਾ;

    /* Check for any properly supported validation layer */
    ਜੇ (debug_opt) {
        ਜੇ (!strcmp(debug_opt->ਮੁੱਲ, "printf")) {
            ਬਹੁਲਕ = FF_VULKAN_DEBUG_PRINTF;
        } ਨਹੀਂਤਾਂ ਜੇ (!strcmp(debug_opt->ਮੁੱਲ, "validate")) {
            ਬਹੁਲਕ = FF_VULKAN_DEBUG_VALIDATE;
        } ਨਹੀਂਤਾਂ ਜੇ (!strcmp(debug_opt->ਮੁੱਲ, "practices")) {
            ਬਹੁਲਕ = FF_VULKAN_DEBUG_PRACTICES;
        } ਨਹੀਂਤਾਂ {
            ਅੱਖਰ *ਸਿਰਾ_ptr = ਨਿਰਾ;
            ਪੂਰਨ idx = strtol(debug_opt->ਮੁੱਲ, &ਸਿਰਾ_ptr, 10);
            ਜੇ (ਸਿਰਾ_ptr == debug_opt->ਮੁੱਲ || ਸਿਰਾ_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->ਮੁੱਲ);
                err = AVERROR(EINVAL);
                ਜਾਓ ਸਿਰਾ;
            }
            ਬਹੁਲਕ = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    ਜੇ ((ਬਹੁਲਕ == FF_VULKAN_DEBUG_VALIDATE) ||
        (ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) ||
        (ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRACTICES)) {
        ਲਈ (ਪੂਰਨ i = 0; i < sup_layer_ਗਿਣਤੀ; i++) {
            ਜੇ (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(enabled_layers, enabled_layers_ਗਿਣਤੀ, layer_standard_validation);
                *debug_ਬਹੁਲਕ = ਬਹੁਲਕ;
                layer_standard_validation_ਮਿਲਿਆ = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (!layer_standard_validation_ਮਿਲਿਆ) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            ਜਾਓ ਸਿਰਾ;
        }
    }

    /* Process any custom layers enabled */
    ਜੇ (user_layers) {
        ਪੂਰਨ ਮਿਲਿਆ;

        user_layers_str = av_strdup(user_layers->ਮੁੱਲ);
        ਜੇ (!user_layers_str) {
            err = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        ਜਦੋਂ (token) {
            ਮਿਲਿਆ = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            ਜੇ (!strcmp(layer_standard_validation, token) && layer_standard_validation_ਮਿਲਿਆ) {
                token = av_strtok(ਨਿਰਾ, "+", &save);
                ਰੋਕੋ;
            }

            /* Try to find the layer in the list of supported layers */
            ਲਈ (ਪੂਰਨ j = 0; j < sup_layer_ਗਿਣਤੀ; j++) {
                ਜੇ (!strcmp(token, sup_layers[j].layerName)) {
                    ਮਿਲਿਆ = 1;
                    ਰੋਕੋ;
                }
            }

            ਜੇ (ਮਿਲਿਆ) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                ਜੋੜੋ_VAL_ਮੰਜ਼ਿਲ_LIST(enabled_layers, enabled_layers_ਗਿਣਤੀ, token);

                /* If debug was not set as an option, force it */
                ਜੇ (!strcmp(layer_standard_validation, token))
                    *debug_ਬਹੁਲਕ = FF_VULKAN_DEBUG_VALIDATE;
            } ਨਹੀਂਤਾਂ {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                ਜਾਓ ਸਿਰਾ;
            }

            token = av_strtok(ਨਿਰਾ, "+", &save);
        }
    }

fail:
ਸਿਰਾ:
    av_free(sup_layers);
    av_free(user_layers_str);

    ਜੇ (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_ਗਿਣਤੀ);
    } ਨਹੀਂਤਾਂ {
        *dst = enabled_layers;
        *ਅੰਕ = enabled_layers_ਗਿਣਤੀ;
    }

    ਵਾਪਸ err;
}

/* Creates a VkInstance */
ਸਥਿਰ ਪੂਰਨ create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ *debug_ਬਹੁਲਕ)
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .application_ਸੰਸਕਰਣ_2 = VK_MAKE_ਸੰਸਕਰਣ(LIBAVUTIL_ਸੰਸਕਰਣ_MAJOR,
                                              LIBAVUTIL_ਸੰਸਕਰਣ_MINOR,
                                              LIBAVUTIL_ਸੰਸਕਰਣ_MICRO),
        .pEngineName        = "libavutil",
        .api_ਸੰਸਕਰਣ         = VK_API_ਸੰਸਕਰਣ_1_3,
        .engine_ਸੰਸਕਰਣ      = VK_MAKE_ਸੰਸਕਰਣ(LIBAVUTIL_ਸੰਸਕਰਣ_MAJOR,
                                              LIBAVUTIL_ਸੰਸਕਰਣ_MINOR,
                                              LIBAVUTIL_ਸੰਸਕਰਣ_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    ਜੇ (!hwctx->get_proc_addr) {
        err = ਲੱਦੋ_libvulkan(ctx);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
    }

    err = ff_vk_ਲੱਦੋ_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    ਜੇ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        ਵਾਪਸ err;
    }

    err = check_layers(ctx, opts, &inst_props.pp_Enabled_Layer_ਨਾਂ,
                       &inst_props.enabled_Layer_ਗਿਣਤੀ, debug_ਬਹੁਲਕ);
    ਜੇ (err)
        ਜਾਓ fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.pp_Enabled_Extension_ਨਾਂ,
                           &inst_props.enabled_Extension_ਗਿਣਤੀ, *debug_ਬਹੁਲਕ);
    hwctx->enabled_inst_extensions = inst_props.pp_Enabled_Extension_ਨਾਂ;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_ਗਿਣਤੀ;
    ਜੇ (err < 0)
        ਜਾਓ fail;

    /* Enable debug features if needed */
    ਜੇ (*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_VALIDATE) {
        ਸਥਿਰ ਅਚਲ VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_ਥਾਂ_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_ਗਿਣਤੀ = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_ਅਗਲਾ = &validation_features;
    } ਨਹੀਂਤਾਂ ਜੇ (*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) {
        ਸਥਿਰ ਅਚਲ VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_ਥਾਂ_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_ਗਿਣਤੀ = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_ਅਗਲਾ = &validation_features;
    } ਨਹੀਂਤਾਂ ਜੇ (*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRACTICES) {
        ਸਥਿਰ ਅਚਲ VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_ਉੱਤਮ_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_ਗਿਣਤੀ = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_ਅਗਲਾ = &validation_features;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
    ਲਈ (ਪੂਰਨ i = 0; i < inst_props.enabled_Extension_ਗਿਣਤੀ; i++) {
        ਜੇ (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.pp_Enabled_Extension_ਨਾਂ[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
            ਰੋਕੋ;
        }
    }
#ਜੇ_ਅੰਤ

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ਜਾਓ fail;
    }

    err = ff_vk_ਲੱਦੋ_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    ਜੇ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        ਜਾਓ fail;
    }

    /* Setup debugging callback if needed */
    ਜੇ ((*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_ਬਹੁਲਕ == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .ਸੁਨੇਹਾ_Severity = VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_VERBOSE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT |
                               VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_INFO_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT    |
                               VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_WARNING_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT |
                               VK_DEBUG_UTILS_ਸੁਨੇਹਾ_SEVERITY_ERROR_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
            .ਸੁਨੇਹਾ_Type = VK_DEBUG_UTILS_ਸੁਨੇਹਾ_TYPE_GENERAL_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT    |
                           VK_DEBUG_UTILS_ਸੁਨੇਹਾ_TYPE_VALIDATION_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT |
                           VK_DEBUG_UTILS_ਸੁਨੇਹਾ_TYPE_PERFORMANCE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .p_User_ਅੰਕੜੇ = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.pp_Enabled_Layer_ਨਾਂ, inst_props.enabled_Layer_ਗਿਣਤੀ);
    ਵਾਪਸ err;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_ਮਾਪ]; /* Will use this first unless !has_uuid */
    ਪੂਰਨ has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ਅਚਲ ਅੱਖਰ *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    ਪੂਰਨ ਸੂਚਕਾਂਕ; /* Finally fall back to index */
} VulkanDeviceSelection;

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *vk_dev_type(ਗਿਣਤੀ VkPhysicalDeviceType type)
{
    ਚੋਣ (type) {
    ਹਾਲਤ VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: ਵਾਪਸ "integrated";
    ਹਾਲਤ VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   ਵਾਪਸ "discrete";
    ਹਾਲਤ VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    ਵਾਪਸ "virtual";
    ਹਾਲਤ VK_PHYSICAL_DEVICE_TYPE_CPU:            ਵਾਪਸ "software";
    ਮੂਲ:                                     ਵਾਪਸ "unknown";
    }
}

/* Finds a device */
ਸਥਿਰ ਪੂਰਨ ਲੱਭੋ_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    ਪੂਰਨ err = 0, choice = -1;
    uint32_t ਅੰਕ;
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = ਨਿਰਾ;
    VkPhysicalDeviceIDProperties *idp = ਨਿਰਾ;
    VkPhysicalDeviceProperties2 *prop = ਨਿਰਾ;
    VkPhysicalDeviceDriverProperties *driver_prop = ਨਿਰਾ;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = ਨਿਰਾ;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ਅੰਕ, ਨਿਰਾ);
    ਜੇ (ret != VK_SUCCESS || !ਅੰਕ) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR(ENODEV);
    }

    devices = av_malloc_array(ਅੰਕ, ਆਕਾਰ(VkPhysicalDevice));
    ਜੇ (!devices)
        ਵਾਪਸ AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ਅੰਕ, devices);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    }

    prop = av_calloc(ਅੰਕ, ਆਕਾਰ(*prop));
    ਜੇ (!prop) {
        err = AVERROR(ENOMEM);
        ਜਾਓ ਸਿਰਾ;
    }

    idp = av_calloc(ਅੰਕ, ਆਕਾਰ(*idp));
    ਜੇ (!idp) {
        err = AVERROR(ENOMEM);
        ਜਾਓ ਸਿਰਾ;
    }

    driver_prop = av_calloc(ਅੰਕ, ਆਕਾਰ(*driver_prop));
    ਜੇ (!driver_prop) {
        err = AVERROR(ENOMEM);
        ਜਾਓ ਸਿਰਾ;
    }

    ਜੇ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(ਅੰਕ, ਆਕਾਰ(*drm_prop));
        ਜੇ (!drm_prop) {
            err = AVERROR(ENOMEM);
            ਜਾਓ ਸਿਰਾ;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].p_ਅਗਲਾ = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].p_ਅਗਲਾ = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].p_ਅਗਲਾ = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    ਜੇ (select->has_uuid) {
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
            ਜੇ (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_ਮਾਪ)) {
                choice = i;
                ਜਾਓ ਸਿਰਾ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
            ਜੇ ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                ਜਾਓ ਸਿਰਾ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
            ਜੇ (ਲੜੀ_ਖੋਜ(prop[i].properties.deviceName, select->name)) {
                choice = i;
                ਜਾਓ ਸਿਰਾ;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
            ਜੇ (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                ਜਾਓ ਸਿਰਾ;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        ਜਾਓ ਸਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
            ਜੇ (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                ਜਾਓ ਸਿਰਾ;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (select->ਸੂਚਕਾਂਕ < ਅੰਕ) {
            choice = select->ਸੂਚਕਾਂਕ;
            ਜਾਓ ਸਿਰਾ;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->ਸੂਚਕਾਂਕ);
        err = AVERROR(ENODEV);
        ਜਾਓ ਸਿਰਾ;
    }

ਸਿਰਾ:
    ਜੇ (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_ਅਗਲਾ = ਨਿਰਾ;
        p->dprops = driver_prop[choice];
        p->dprops.p_ਅਗਲਾ = ਨਿਰਾ;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    ਵਾਪਸ err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ pick_ਕਤਾਰ_family(Vk_ਕਤਾਰ_Family_Properties2 *qf, uint32_t ਅੰਕ_qf,
                                    Vk_ਕਤਾਰ_Flag_ਬਿੱਟ flags)
{
    ਪੂਰਨ ਸੂਚਕਾਂਕ = -1;
    uint32_t min_score = UINT32_MAX;

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_qf; i++) {
        Vk_ਕਤਾਰ_Flag_ਬਿੱਟ qflags = qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        ਜੇ ((flags & VK_ਕਤਾਰ_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ) &&
            (qflags & (VK_ਕਤਾਰ_GRAPHICS_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ਕਤਾਰ_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ)))
            qflags |= VK_ਕਤਾਰ_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ;

        ਜੇ (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].ਕਤਾਰ_Family_Properties.timestamp_Valid_ਬਿੱਟ;
            ਜੇ (score < min_score) {
                ਸੂਚਕਾਂਕ = i;
                min_score = score;
            }
        }
    }

    ਜੇ (ਸੂਚਕਾਂਕ > -1)
        qf[ਸੂਚਕਾਂਕ].ਕਤਾਰ_Family_Properties.timestamp_Valid_ਬਿੱਟ++;

    ਵਾਪਸ ਸੂਚਕਾਂਕ;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ pick_video_ਕਤਾਰ_family(Vk_ਕਤਾਰ_Family_Properties2 *qf,
                                          Vk_ਕਤਾਰ_Family_Video_Properties_KHR *qf_vid, uint32_t ਅੰਕ_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    ਪੂਰਨ ਸੂਚਕਾਂਕ = -1;
    uint32_t min_score = UINT32_MAX;

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_qf; i++) {
        ਅਚਲ Vk_ਕਤਾਰ_Flags qflags = qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags;
        ਅਚਲ VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        ਜੇ (!(qflags & (VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR | VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)))
            ਜਾਰੀ;

        ਜੇ (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].ਕਤਾਰ_Family_Properties.timestamp_Valid_ਬਿੱਟ;
            ਜੇ (score < min_score) {
                ਸੂਚਕਾਂਕ = i;
                min_score = score;
            }
        }
    }

    ਜੇ (ਸੂਚਕਾਂਕ > -1)
        qf[ਸੂਚਕਾਂਕ].ਕਤਾਰ_Family_Properties.timestamp_Valid_ਬਿੱਟ++;

    ਵਾਪਸ ਸੂਚਕਾਂਕ;
}

ਸਥਿਰ ਪੂਰਨ ਤਿਆਰੀ_ਕਤਾਰ_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t ਅੰਕ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    Vk_ਕਤਾਰ_Family_Properties2 *qf = ਨਿਰਾ;
    Vk_ਕਤਾਰ_Family_Video_Properties_KHR *qf_vid = ਨਿਰਾ;

    /* First get the number of queue families */
    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties(hwctx->phys_dev, &ਅੰਕ, ਨਿਰਾ);
    ਜੇ (!ਅੰਕ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(ਅੰਕ, ਆਕਾਰ(Vk_ਕਤਾਰ_Family_Properties2));
    ਜੇ (!qf)
        ਵਾਪਸ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(ਅੰਕ, ਆਕਾਰ(Vk_ਕਤਾਰ_Family_Video_Properties_KHR));
    ਜੇ (!qf_vid)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (uint32_t i = 0; i < ਅੰਕ; i++) {
        qf_vid[i] = (Vk_ਕਤਾਰ_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_ਕਤਾਰ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_PROPERTIES_2,
            .p_ਅਗਲਾ = p->vkctx.extensions & FF_VK_EXT_VIDEO_ਕਤਾਰ ? &qf_vid[i] : ਨਿਰਾ,
        };
    }

    /* Finally retrieve the queue families */
    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties2(hwctx->phys_dev, &ਅੰਕ, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_GRAPHICS_ਦੋਆਧਾਰੀ_ਅੰਕ) ? " graphics" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ) ? " compute" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ) ? " transfer" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) ? " encode" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) ? " decode" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_SPARSE_BINDING_ਦੋਆਧਾਰੀ_ਅੰਕ) ? " sparse" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_OPTICAL_FLOW_ਦੋਆਧਾਰੀ_ਅੰਕ_NV) ? " optical_flow" : "",
               ((qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags) & VK_ਕਤਾਰ_PROTECTED_ਦੋਆਧਾਰੀ_ਅੰਕ) ? " protected" : "",
               qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_ਗਿਣਤੀ);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].ਕਤਾਰ_Family_Properties.timestamp_Valid_ਬਿੱਟ = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->ਕਤਾਰ_flags = 0;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_internally_synchronized_queues
    ਜੇ (p->vkctx.extensions & FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC)
        hwctx->ਕਤਾਰ_flags |= VK_DEVICE_ਕਤਾਰ_CREATE_INTERNALLY_SYNCHRONIZED_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
#ਜੇ_ਅੰਤ

    /* Pick each queue family to use. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PICK_QF(type, vid_op)                                            \
    ਕਰੋ {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        ਜੇ (vid_op)                                                      \
            idx = pick_video_ਕਤਾਰ_family(qf, qf_vid, ਅੰਕ, vid_op);      \
        ਨਹੀਂਤਾਂ                                                             \
            idx = pick_ਕਤਾਰ_family(qf, ਅੰਕ, type);                      \
                                                                         \
        ਜੇ (idx == -1)                                                   \
            ਜਾਰੀ;                                                    \
                                                                         \
        ਲਈ (i = 0; i < hwctx->nb_qf; i++) {                             \
            ਜੇ (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                ਰੋਕੋ;                                                   \
            }                                                            \
        }                                                                \
        ਜੇ (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].ਅੰਕ = qf[idx].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_ਗਿਣਤੀ; \
            ਜੇ (p->ਹੱਦਬੰਦੀ_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                ਪੂਰਨ max = p->ਹੱਦਬੰਦੀ_queues;                               \
                ਜੇ (type == VK_ਕਤਾਰ_GRAPHICS_ਦੋਆਧਾਰੀ_ਅੰਕ)                       \
                    hwctx->qf[i].ਅੰਕ = FFMIN(hwctx->qf[i].ਅੰਕ,           \
                                             max ? max : 1);             \
                ਨਹੀਂਤਾਂ ਜੇ (max)                                            \
                    hwctx->qf[i].ਅੰਕ = FFMIN(hwctx->qf[i].ਅੰਕ, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } ਜਦੋਂ (0)

    PICK_QF(VK_ਕਤਾਰ_GRAPHICS_ਦੋਆਧਾਰੀ_ਅੰਕ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_ਕਤਾਰ_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_ਕਤਾਰ_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);
    PICK_QF(VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);

    PICK_QF(VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);
    PICK_QF(VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_decode_vp9
    PICK_QF(VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_video_encode_av1
    PICK_QF(VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);
#ਜੇ_ਅੰਤ
    PICK_QF(VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR);

    ਜੇ (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_ਕਤਾਰ_OPTICAL_FLOW_ਦੋਆਧਾਰੀ_ਅੰਕ_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PICK_QF

    cd->p_ਕਤਾਰ_Create_Infos = av_malloc_array(hwctx->nb_qf,
                                            ਆਕਾਰ(Vk_Device_ਕਤਾਰ_Create_Info));
    ਜੇ (!cd->p_ਕਤਾਰ_Create_Infos)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        ਪੂਰਨ dup = 0;
        ਦਸ਼ਮਲਵ *weights = ਨਿਰਾ;
        Vk_Device_ਕਤਾਰ_Create_Info *pc;
        ਲਈ (uint32_t j = 0; j < cd->ਕਤਾਰ_Create_Info_ਗਿਣਤੀ; j++) {
            ਜੇ (hwctx->qf[i].idx == cd->p_ਕਤਾਰ_Create_Infos[j].ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ) {
                dup = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (dup)
            ਜਾਰੀ;

        weights = av_malloc_array(hwctx->qf[i].ਅੰਕ, ਆਕਾਰ(ਦਸ਼ਮਲਵ));
        ਜੇ (!weights) {
            ਲਈ (uint32_t j = 0; j < cd->ਕਤਾਰ_Create_Info_ਗਿਣਤੀ; j++)
                av_free((ਖਾਲੀ *)cd->p_ਕਤਾਰ_Create_Infos[i].p_ਕਤਾਰ_Priorities);
            av_free((ਖਾਲੀ *)cd->p_ਕਤਾਰ_Create_Infos);
            ਵਾਪਸ AVERROR(ENOMEM);
        }

        ਲਈ (uint32_t j = 0; j < hwctx->qf[i].ਅੰਕ; j++)
            weights[j] = 1.0;

        pc = (Vk_Device_ਕਤਾਰ_Create_Info *)cd->p_ਕਤਾਰ_Create_Infos;
        pc[cd->ਕਤਾਰ_Create_Info_ਗਿਣਤੀ++] = (Vk_Device_ਕਤਾਰ_Create_Info) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_ਕਤਾਰ_CREATE_INFO,
            .flags = hwctx->ਕਤਾਰ_flags,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = hwctx->qf[i].idx,
            .ਕਤਾਰ_ਗਿਣਤੀ = hwctx->qf[i].ਅੰਕ,
            .p_ਕਤਾਰ_Priorities = weights,
        };
    }

    ਵਾਪਸ 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
ਸਥਿਰ ਖਾਲੀ vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ਜੇ (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    ਜੇ (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    ਜੇ (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    ਜੇ (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

ਸਥਿਰ ਖਾਲੀ vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    ਜੇ (p->qf_mutex) {
        ਲਈ (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

ਸਥਿਰ ਪੂਰਨ vulkan_device_create_ਅੰਦਰੂਨੀ(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         ਪੂਰਨ disable_multiplane,
                                         AVDictionary *opts, ਪੂਰਨ flags)
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    AVDictionary_ਇੰਦਰਾਜ *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਗਿਣਤੀ FFVulkan_Debug_ਬਹੁਲਕ debug_ਬਹੁਲਕ = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    ਜੇ ((err = create_instance(ctx, opts, &debug_ਬਹੁਲਕ)))
        ਜਾਓ ਸਿਰਾ;

    /* Find a physical device (if not given one) */
    ਜੇ ((err = ਲੱਭੋ_device(ctx, dev_select)))
        ਜਾਓ ਸਿਰਾ;

    /* Get supported memory types */
    vk->Get_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    ਜੇ ((err = check_extensions(ctx, 1, opts, &dev_info.pp_Enabled_Extension_ਨਾਂ,
                                &dev_info.enabled_Extension_ਗਿਣਤੀ, debug_ਬਹੁਲਕ))) {
        ਲਈ (ਪੂਰਨ i = 0; i < dev_info.ਕਤਾਰ_Create_Info_ਗਿਣਤੀ; i++)
            av_free((ਖਾਲੀ *)dev_info.p_ਕਤਾਰ_Create_Infos[i].p_ਕਤਾਰ_Priorities);
        av_free((ਖਾਲੀ *)dev_info.p_ਕਤਾਰ_Create_Infos);
        ਜਾਓ ਸਿਰਾ;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.p_ਅਗਲਾ = p->feats.device.p_ਅਗਲਾ;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", ਨਿਰਾ, 0);
    ਜੇ (opt_d)
        p->ਹੱਦਬੰਦੀ_queues = strtol(opt_d->ਮੁੱਲ, ਨਿਰਾ, 10);

    /* Setup enabled queue families */
    ਜੇ ((err = ਤਿਆਰੀ_ਕਤਾਰ_families(ctx, &dev_info)))
        ਜਾਓ ਸਿਰਾ;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    ਲਈ (ਪੂਰਨ i = 0; i < dev_info.ਕਤਾਰ_Create_Info_ਗਿਣਤੀ; i++)
        av_free((ਖਾਲੀ *)dev_info.p_ਕਤਾਰ_Create_Infos[i].p_ਕਤਾਰ_Priorities);
    av_free((ਖਾਲੀ *)dev_info.p_ਕਤਾਰ_Create_Infos);

    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        ਲਈ (ਪੂਰਨ i = 0; i < dev_info.enabled_Extension_ਗਿਣਤੀ; i++)
            av_free((ਖਾਲੀ *)dev_info.pp_Enabled_Extension_ਨਾਂ[i]);
        av_free((ਖਾਲੀ *)dev_info.pp_Enabled_Extension_ਨਾਂ);
        err = AVERROR_EXTERNAL;
        ਜਾਓ ਸਿਰਾ;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", ਨਿਰਾ, 0);
    ਜੇ (opt_d)
        p->use_ਰੇਖਿਕ_images = strtol(opt_d->ਮੁੱਲ, ਨਿਰਾ, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    ਜੇ (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", ਨਿਰਾ, 0);
        ਜੇ (opt_d)
            p->disable_multiplane = strtol(opt_d->ਮੁੱਲ, ਨਿਰਾ, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", ਨਿਰਾ, 0);
    ਜੇ (opt_d)
        p->avoid_host_import = strtol(opt_d->ਮੁੱਲ, ਨਿਰਾ, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.pp_Enabled_Extension_ਨਾਂ;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_ਗਿਣਤੀ;

    /* The extension lists need to be freed */
    ctx->ਮੁਕਤ = vulkan_device_free;

ਸਿਰਾ:
    ਵਾਪਸ err;
}

ਸਥਿਰ ਖਾਲੀ ਤਾਲਾ_ਕਤਾਰ(AVHWDeviceContext *ctx, uint32_t ਕਤਾਰ_family, uint32_t ਸੂਚਕਾਂਕ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ਜੇ (p->qf_mutex)
        pthread_mutex_ਤਾਲਾ(&p->qf_mutex[ਕਤਾਰ_family][ਸੂਚਕਾਂਕ]);
}

ਸਥਿਰ ਖਾਲੀ unlock_ਕਤਾਰ(AVHWDeviceContext *ctx, uint32_t ਕਤਾਰ_family, uint32_t ਸੂਚਕਾਂਕ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ਜੇ (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[ਕਤਾਰ_family][ਸੂਚਕਾਂਕ]);
}

ਸਥਿਰ ਪੂਰਨ vulkan_device_init(AVHWDeviceContext *ctx)
{
    ਪੂਰਨ err = 0;
    uint32_t qf_ਅੰਕ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_ਕਤਾਰ_Family_Properties2 *qf;
    Vk_ਕਤਾਰ_Family_Video_Properties_KHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    ਲਈ (ਪੂਰਨ i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        ਲਈ (ਪੂਰਨ j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            ਜੇ (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                ਰੋਕੋ;
            }
        }
    }

    err = ff_vk_ਲੱਦੋ_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    ਜੇ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        ਵਾਪਸ err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_ਅਗਲਾ = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_ਸਮ੍ਰਿਤੀ_HOST_PROPERTIES_EXT;
    p->hprops.p_ਅਗਲਾ = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_ਬਫਰ_Copy_ਪੰਕਤੀ_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.min_ਸਮ੍ਰਿਤੀ_Map_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_ਮਾਪ);
    ਜੇ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_ਸਮ੍ਰਿਤੀ)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.min_Imported_Host_ਸੂਚਕ_Alignment);

    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties(hwctx->phys_dev, &qf_ਅੰਕ, ਨਿਰਾ);
    ਜੇ (!qf_ਅੰਕ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ਦੋਆਧਾਰੀ_ਅੰਕ
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ਦੋਆਧਾਰੀ_ਅੰਕ;
#ਨਹੀਂਤਾਂ
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ਦੋਆਧਾਰੀ_ਅੰਕ;
#ਜੇ_ਅੰਤ
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_ਅੰਕ, ਆਕਾਰ(Vk_ਕਤਾਰ_Family_Properties2));
    ਜੇ (!qf)
        ਵਾਪਸ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_ਅੰਕ, ਆਕਾਰ(Vk_ਕਤਾਰ_Family_Video_Properties_KHR));
    ਜੇ (!qf_vid) {
        av_free(qf);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਲਈ (uint32_t i = 0; i < qf_ਅੰਕ; i++) {
        qf_vid[i] = (Vk_ਕਤਾਰ_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_ਕਤਾਰ_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_ਕਤਾਰ_FAMILY_PROPERTIES_2,
            .p_ਅਗਲਾ = p->vkctx.extensions & FF_VK_EXT_VIDEO_ਕਤਾਰ ? &qf_vid[i] : ਨਿਰਾ,
        };
    }

    vk->Get_Physical_Device_ਕਤਾਰ_Family_Properties2(hwctx->phys_dev, &qf_ਅੰਕ, qf);

    p->nb_tot_qfs = qf_ਅੰਕ;

    ਜੇ (!(p->vkctx.extensions & FF_VK_EXT_ਅੰਦਰੂਨੀ_ਕਤਾਰ_SYNC)) {
        p->qf_mutex = av_calloc(qf_ਅੰਕ, ਆਕਾਰ(*p->qf_mutex));
        ਜੇ (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            ਜਾਓ ਸਿਰਾ;
        }

        ਲਈ (uint32_t i = 0; i < qf_ਅੰਕ; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_ਗਿਣਤੀ,
                                       ਆਕਾਰ(**p->qf_mutex));
            ਜੇ (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                ਜਾਓ ਸਿਰਾ;
            }
            ਲਈ (uint32_t j = 0; j < qf[i].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_ਗਿਣਤੀ; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], ਨਿਰਾ);
                ਜੇ (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    ਜਾਓ ਸਿਰਾ;
                }
            }
        }
    }

    ਲਈ (ਪੂਰਨ i = 0; i < hwctx->nb_qf; i++) {
        ਜੇ (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_ਕਤਾਰ_VIDEO_DECODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR |
                                  VK_ਕਤਾਰ_VIDEO_ENCODE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < hwctx->nb_qf; i++) {
        ਪੂਰਨ ਵੇਖਿਆ = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        ਲਈ (ਪੂਰਨ j = (i - 1); j >= 0; j--) {
            ਜੇ (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                ਵੇਖਿਆ = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (!ਵੇਖਿਆ)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#ਜੇ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    ਜੇ (!hwctx->ਤਾਲਾ_ਕਤਾਰ)
        hwctx->ਤਾਲਾ_ਕਤਾਰ = ਤਾਲਾ_ਕਤਾਰ;
    ਜੇ (!hwctx->unlock_ਕਤਾਰ)
        hwctx->unlock_ਕਤਾਰ = unlock_ਕਤਾਰ;
FF_ENABLE_DEPRECATION_WARNINGS
#ਜੇ_ਅੰਤ

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_ਲੱਦੋ_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_ਲੱਭੋ(&p->vkctx, VK_ਕਤਾਰ_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ, 0);
    p->transfer_qf = ff_vk_qf_ਲੱਭੋ(&p->vkctx, VK_ਕਤਾਰ_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_ਵਿੱਥ_align = 1;
    ਜੇ (p->transfer_qf) {
        Vk_ਕਤਾਰ_Flags flags = p->vkctx.qf_props[p->transfer_qf->idx].ਕਤਾਰ_Family_Properties.ਕਤਾਰ_Flags;
        ਜੇ (!(flags & (VK_ਕਤਾਰ_GRAPHICS_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ਕਤਾਰ_COMPUTE_ਦੋਆਧਾਰੀ_ਅੰਕ)))
            p->transfer_ਵਿੱਥ_align = 4;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    ਜੇ (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_ਵਿੱਥ_align = 1;
#ਜੇ_ਅੰਤ

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties(hwctx->phys_dev, &p->mprops);

ਸਿਰਾ:
    av_free(qf_vid);
    av_free(qf);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vulkan_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                                AVDictionary *opts, ਪੂਰਨ flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    ਜੇ (device && device[0]) {
        ਅੱਖਰ *ਸਿਰਾ = ਨਿਰਾ;

        ਜੇ (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } ਨਹੀਂਤਾਂ {
            dev_select.ਸੂਚਕਾਂਕ = strtol(device, &ਸਿਰਾ, 10);
            ਜੇ (ਸਿਰਾ == device || *ਸਿਰਾ) {
                dev_select.ਸੂਚਕਾਂਕ = 0;
                dev_select.name  = device;
            }
        }
    }

    ਵਾਪਸ vulkan_device_create_ਅੰਦਰੂਨੀ(ctx, &dev_select, 0, opts, flags);
}

ਸਥਿਰ ਪੂਰਨ vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, ਪੂਰਨ flags)
{
    av_ਅਣਵਰਤਿਆ VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    ਚੋਣ(src_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#ਜੇ VA_CHECK_ਸੰਸਕਰਣ(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#ਜੇ_ਅੰਤ
        ਅਚਲ ਅੱਖਰ *vendor;

#ਜੇ VA_CHECK_ਸੰਸਕਰਣ(1, 15, 0)
        vas = va_Get_Display_ਗੁਣ(dpy, &attr, 1);
        ਜੇ (vas == VA_ਸਥਿਤੀ_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.ਮੁੱਲ & 0xFFFF);
#ਜੇ_ਅੰਤ

        ਜੇ (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            ਜੇ (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                ਵਾਪਸ AVERROR_EXTERNAL;
            }

            ਜੇ (ਲੜੀ_ਖੋਜ(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        ਵਾਪਸ vulkan_device_create_ਅੰਦਰੂਨੀ(ctx, &dev_select, 0, opts, flags);
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_LIBDRM
    ਹਾਲਤ AV_HWDEVICE_TYPE_DRM: {
        ਪੂਰਨ err;
        ਬਣਤਰ stat drm_ਗੰਢ_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ਗੰਢ_info);
        ਜੇ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ਗੰਢ_info.st_dev);
        dev_select.drm_minor = minor(drm_ਗੰਢ_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        ਜੇ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        ਜੇ (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        ਵਾਪਸ vulkan_device_create_ਅੰਦਰੂਨੀ(ctx, &dev_select, 0, opts, flags);
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_CUDA
    ਹਾਲਤ AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADevice_Context_ਅੰਦਰੂਨੀ *cu_ਅੰਦਰੂਨੀ = src_hwctx->ਅੰਦਰੂਨੀ;
        CudaFunctions *cu = cu_ਅੰਦਰੂਨੀ->cuda_dl;

        ਪੂਰਨ ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_ਅੰਦਰੂਨੀ->cuda_device));
        ਜੇ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        ਵਾਪਸ vulkan_device_create_ਅੰਦਰੂਨੀ(ctx, &dev_select, 1, opts, flags);
    }
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }
}

ਸਥਿਰ ਪੂਰਨ vulkan_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                         ਅਚਲ ਖਾਲੀ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    ਲਈ (ਗਿਣਤੀ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ਗਿਣਤੀ_2 += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_ਰੇਖਿਕ_images ? VK_IMAGE_TILING_ਰੇਖਿਕ :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(ਗਿਣਤੀ_2 + 1 + CONFIG_CUDA,
                                                    ਆਕਾਰ(ਗਿਣਤੀ AVPixelFormat));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਗਿਣਤੀ_2 = 0;
    ਲਈ (ਗਿਣਤੀ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ਜੇ (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_ਰੇਖਿਕ_images ? VK_IMAGE_TILING_ਰੇਖਿਕ :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[ਗਿਣਤੀ_2++] = vk_formats_list[i].pixfmt;
        }
    }

#ਜੇ CONFIG_CUDA
    constraints->valid_sw_formats[ਗਿਣਤੀ_2++] = AV_PIX_FMT_CUDA;
#ਜੇ_ਅੰਤ

    constraints->valid_sw_formats[ਗਿਣਤੀ_2++] = AV_PIX_FMT_NONE;

    constraints->min_ਚੌੜਾਈ  = 1;
    constraints->min_ਉਚਾਈ = 1;
    constraints->max_ਚੌੜਾਈ  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_ਉਚਾਈ = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(ਗਿਣਤੀ AVPixelFormat));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ alloc_mem(AVHWDeviceContext *ctx, Vk_ਸਮ੍ਰਿਤੀ_Requirements *req,
                     Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ req_flags, ਅਚਲ ਖਾਲੀ *alloc_extension,
                     Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ *mem_flags, Vk_Device_ਸਮ੍ਰਿਤੀ *mem)
{
    Vk_ਨਤੀਜਾ ret;
    ਪੂਰਨ ਸੂਚਕਾਂਕ = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    Vk_ਸਮ੍ਰਿਤੀ_Allocate_Info alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_ALLOCATE_INFO,
        .p_ਅਗਲਾ          = alloc_extension,
        .ਵੰਡ_ਮਾਪ = req->ਮਾਪ,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ਲਈ (ਪੂਰਨ i = 0; i < p->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ; i++) {
        ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Type *type = &p->mprops.ਸਮ੍ਰਿਤੀ_Types[i];

        /* The memory type must be supported by the requirements (bitfield) */
        ਜੇ (!(req->ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ & (1 << i)))
            ਜਾਰੀ;

        /* The memory type flags must include our properties */
        ਜੇ ((type->propertyFlags & req_flags) != req_flags)
            ਜਾਰੀ;

        /* The memory type must be large enough */
        ਜੇ (req->ਮਾਪ > p->mprops.ਸਮ੍ਰਿਤੀ_Heaps[type->ਢੇਰ_ਸੂਚਕਾਂਕ_2].ਮਾਪ)
            ਜਾਰੀ;

        /* Found a suitable memory type */
        ਸੂਚਕਾਂਕ = i;
        ਰੋਕੋ;
    }

    ਜੇ (ਸੂਚਕਾਂਕ < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    alloc_info.ਸਮ੍ਰਿਤੀ_Type_ਸੂਚਕਾਂਕ = ਸੂਚਕਾਂਕ;

    ret = vk->Allocate_ਸਮ੍ਰਿਤੀ(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.ਸਮ੍ਰਿਤੀ_Types[ਸੂਚਕਾਂਕ].propertyFlags;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ vulkan_free_ਅੰਦਰੂਨੀ(VulkanDevicePriv *p, AVVk_ਚੌਖਟਾ *f)
{
    av_ਅਣਵਰਤਿਆ AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *ਅੰਦਰੂਨੀ = f->ਅੰਦਰੂਨੀ;

    // Make this function safe to call repeatedly
    ਜੇ (!ਅੰਦਰੂਨੀ)
        ਵਾਪਸ;

#ਜੇ CONFIG_CUDA
    ਜੇ (ਅੰਦਰੂਨੀ->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)ਅੰਦਰੂਨੀ->cuda_fc_ref->ਅੰਕੜੇ;
        ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADevice_Context_ਅੰਦਰੂਨੀ *cu_ਅੰਦਰੂਨੀ = cuda_dev->ਅੰਦਰੂਨੀ;
        CudaFunctions *cu = cu_ਅੰਦਰੂਨੀ->cuda_dl;

        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
            ਜੇ (ਅੰਦਰੂਨੀ->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(ਅੰਦਰੂਨੀ->cu_sem[i]));
            ਜੇ (ਅੰਦਰੂਨੀ->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(ਅੰਦਰੂਨੀ->cu_mma[i]));
            ਜੇ (ਅੰਦਰੂਨੀ->ext_mem[i])
                CHECK_CU(cu->cu_Destroy_External_ਸਮ੍ਰਿਤੀ(ਅੰਦਰੂਨੀ->ext_mem[i]));
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
            ਜੇ (ਅੰਦਰੂਨੀ->ext_sem_handle[i])
                CloseHandle(ਅੰਦਰੂਨੀ->ext_sem_handle[i]);
            ਜੇ (ਅੰਦਰੂਨੀ->ext_mem_handle[i])
                CloseHandle(ਅੰਦਰੂਨੀ->ext_mem_handle[i]);
#ਜੇ_ਅੰਤ
        }

        av_ਬਫਰ_unref(&ਅੰਦਰੂਨੀ->cuda_fc_ref);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਦਰੂਨੀ->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, ਅੰਦਰੂਨੀ->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&ਅੰਦਰੂਨੀ->update_mutex);
    av_freep(&f->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ ਖਾਲੀ vulkan_ਚੌਖਟਾ_free(AVHWFramesContext *hwfc, AVVk_ਚੌਖਟਾ *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(f);
    ਪੂਰਨ nb_sems = 0;

    ਜਦੋਂ (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    ਜੇ (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_ਮੁੱਲਾਂ        = f->sem_ਮੁੱਲ,
            .semaphore_ਗਿਣਤੀ = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_ਅੰਦਰੂਨੀ(p, f);

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->Free_ਸਮ੍ਰਿਤੀ(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

ਸਥਿਰ ਖਾਲੀ vulkan_ਚੌਖਟਾ_free_cb(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    vulkan_ਚੌਖਟਾ_free(opaque, (AVVk_ਚੌਖਟਾ*)ਅੰਕੜੇ);
}

ਸਥਿਰ ਪੂਰਨ alloc_bind_mem(AVHWFramesContext *hwfc, AVVk_ਚੌਖਟਾ *f,
                          ਖਾਲੀ *alloc_pnext, size_t alloc_pnext_stride)
{
    ਪੂਰਨ img_cnt = 0, err;
    Vk_ਨਤੀਜਾ ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Bind_Image_ਸਮ੍ਰਿਤੀ_Info bind_info[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { { 0 } };

    ਜਦੋਂ (f->img[img_cnt]) {
        ਪੂਰਨ use_ded_mem;
        Vk_Image_ਸਮ੍ਰਿਤੀ_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_ALLOCATE_INFO,
            .p_ਅਗਲਾ = (ਖਾਲੀ *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_REQUIREMENTS,
        };
        Vk_ਸਮ੍ਰਿਤੀ_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_2,
            .p_ਅਗਲਾ = &ded_req,
        };

        vk->Get_Image_ਸਮ੍ਰਿਤੀ_Requirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefers_Dedicated_ਵੰਡ, ded_req.requires_Dedicated_ਵੰਡ);

        ਜੇ (f->tiling == VK_IMAGE_TILING_ਰੇਖਿਕ)
            req.ਸਮ੍ਰਿਤੀ_Requirements.ਮਾਪ = FFALIGN(req.ਸਮ੍ਰਿਤੀ_Requirements.ਮਾਪ,
                                                  p->props.properties.limits.min_ਸਮ੍ਰਿਤੀ_Map_Alignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefers_Dedicated_ਵੰਡ |
                      ded_req.requires_Dedicated_ਵੰਡ;
        ਜੇ (((Vulkan_ਚੌਖਟੇ_Priv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        ਜੇ (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        ਜੇ ((err = alloc_mem(ctx, &req.ਸਮ੍ਰਿਤੀ_Requirements,
                             f->tiling == VK_IMAGE_TILING_ਰੇਖਿਕ ?
                             VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ :
                             VK_ਸਮ੍ਰਿਤੀ_PROPERTY_DEVICE_LOCAL_ਦੋਆਧਾਰੀ_ਅੰਕ,
                             use_ded_mem ? &ded_alloc : (ਖਾਲੀ *)ded_alloc.p_ਅਗਲਾ,
                             &f->flags, &f->mem[img_cnt])))
            ਵਾਪਸ err;

        f->ਮਾਪ[img_cnt] = req.ਸਮ੍ਰਿਤੀ_Requirements.ਮਾਪ;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_ਸਮ੍ਰਿਤੀ_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].ਸਮ੍ਰਿਤੀ = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਗਿਣਤੀ Prep_ਬਹੁਲਕ {
    PREP_ਬਹੁਲਕ_GENERAL,
    PREP_ਬਹੁਲਕ_WRITE,
    PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT,
    PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT,
    PREP_ਬਹੁਲਕ_DECODING_DST,
    PREP_ਬਹੁਲਕ_DECODING_DPB,
    PREP_ਬਹੁਲਕ_ENCODING_DPB,
};

ਸਥਿਰ ਖਾਲੀ switch_new_props(ਗਿਣਤੀ Prep_ਬਹੁਲਕ pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    ਚੋਣ (pmode) {
    ਹਾਲਤ PREP_ਬਹੁਲਕ_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_ਸਮ੍ਰਿਤੀ_READ_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ACCESS_ਸਮ੍ਰਿਤੀ_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_ਸਮ੍ਰਿਤੀ_READ_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ACCESS_ਸਮ੍ਰਿਤੀ_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ PREP_ਬਹੁਲਕ_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ਦੋਆਧਾਰੀ_ਅੰਕ | VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਪੂਰਨ switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_ਚੌਖਟਾ *ਚੌਖਟਾ, ਗਿਣਤੀ Prep_ਬਹੁਲਕ pmode)
{
    ਪੂਰਨ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 img_bar[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_ਕਤਾਰ_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    ਜੇ (pmode == PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT) {
        dst_qf     = VK_ਕਤਾਰ_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .ਅੰਕੜੇ = (uint8_t *)hwfc,
    };
    AVFrame tmp_ਚੌਖਟਾ = {
        .ਅੰਕੜੇ[0] = (uint8_t *)ਚੌਖਟਾ,
        .hw_ਚੌਖਟੇ_ctx = &tmp_ref,
    };

    Vk_Command_ਬਫਰ cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_ਸ਼ੁਰੂ(&p->vkctx, exec);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_ਜੋੜੋ_dep_ਚੌਖਟਾ(&p->vkctx, exec, &tmp_ਚੌਖਟਾ,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    ff_vk_ਚੌਖਟਾ_barrier(&p->vkctx, exec, &tmp_ਚੌਖਟਾ, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_ਸਮ੍ਰਿਤੀ_Barriers = img_bar,
            .image_ਸਮ੍ਰਿਤੀ_Barrier_ਗਿਣਤੀ = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVk_ਚੌਖਟਾ *ਚੌਖਟਾ, ਗਿਣਤੀ Prep_ਬਹੁਲਕ pmode)
{
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(ਚੌਖਟਾ);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    ਪੂਰਨ i;
    ਲਈ (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_ਗਿਣਤੀ; i++) {
        ਜੇ (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            ਰੋਕੋ;
    }
    ਜੇ (i == p->vkctx.host_image_props.copy_Dst_Layout_ਗਿਣਤੀ)
        ਵਾਪਸ AVERROR(ENOTSUP);

    ਲਈ (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = ਚੌਖਟਾ->img[i],
            .oldLayout = ਚੌਖਟਾ->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspect_ਨਕਾਬ = VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ,
            .subresourceRange.layer_ਗਿਣਤੀ = 1,
            .subresourceRange.level_ਗਿਣਤੀ = 1,
        };
        ਚੌਖਟਾ->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ prepare_ਚੌਖਟਾ(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_ਚੌਖਟਾ *ਚੌਖਟਾ, ਗਿਣਤੀ Prep_ਬਹੁਲਕ pmode)
{
    ਪੂਰਨ err = 0;
    AVVulkan_ਚੌਖਟੇ_Context *hwfc_vk = hwfc->hwctx;
    ਜੇ (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT &&
        (pmode != PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT) &&
        (pmode != PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, ਚੌਖਟਾ, pmode);
        ਜੇ (err != AVERROR(ENOTSUP))
            ਵਾਪਸ err;
    }

    ਵਾਪਸ switch_layout(hwfc, ectx, ਚੌਖਟਾ, pmode);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ get_plane_wh(uint32_t *w, uint32_t *h, ਗਿਣਤੀ AVPixelFormat format,
                                ਪੂਰਨ ਚੌਖਟਾ_w, ਪੂਰਨ ਚੌਖਟਾ_h, ਪੂਰਨ plane)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    ਜੇ (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = ਚੌਖਟਾ_w;
        *h = ਚੌਖਟਾ_h;
        ਵਾਪਸ;
    }

    *w = AV_CEIL_RSHIFT(ਚੌਖਟਾ_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(ਚੌਖਟਾ_h, desc->log2_chroma_h);
}

ਸਥਿਰ ਪੂਰਨ create_ਚੌਖਟਾ(AVHWFramesContext *hwfc, AVVk_ਚੌਖਟਾ **ਚੌਖਟਾ,
                        VkImageTiling tiling, Vk_Image_Usage_Flag_ਬਿੱਟ usage,
                        VkImageCreateFlags flags, ਪੂਰਨ nb_layers,
                        ਖਾਲੀ *create_pnext)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    AVVulkan_ਚੌਖਟੇ_Context *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVk_ਚੌਖਟਾ *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_ਮੁੱਲ  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_ਅਗਲਾ = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ਦੋਆਧਾਰੀ_ਅੰਕ
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ਦੋਆਧਾਰੀ_ਅੰਕ,
#ਨਹੀਂਤਾਂ
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ਦੋਆਧਾਰੀ_ਅੰਕ,
#ਜੇ_ਅੰਤ
    };

    /* Check if exporting is supported before chaining any structs */
    ਜੇ (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_ਦੋਆਧਾਰੀ_ਅੰਕ) {
        ਜੇ (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_ਚੌਖਟਾ_alloc();
    ਜੇ (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    ਲਈ (ਪੂਰਨ i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ਅਗਲਾ                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.ਡੂੰਘਾਈ          = 1,
            .mip_ਪੱਧਰ             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_ਗਿਣਤੀ_1_ਦੋਆਧਾਰੀ_ਅੰਕ,
            .p_ਕਤਾਰ_Family_Indices   = p->img_qfs,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = p->nb_img_qfs,
            .sharing_ਬਹੁਲਕ           = p->nb_img_qfs > 1 ? VK_SHARING_ਬਹੁਲਕ_CONCURRENT :
                                                         VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.ਚੌੜਾਈ, &create_info.extent.ਉਚਾਈ,
                     hwfc->sw_format, hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ਜਾਓ fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }

        f->ਕਤਾਰ_family[i] = p->nb_img_qfs > 1 ? VK_ਕਤਾਰ_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ਮੁੱਲ[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *ਚੌਖਟਾ = f;
    ਵਾਪਸ 0;

fail:
    vulkan_ਚੌਖਟਾ_free(hwfc, f);
    ਵਾਪਸ err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
ਸਥਿਰ ਖਾਲੀ try_export_flags(AVHWFramesContext *hwfc,
                             Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags *comp_handle_types,
                             Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags *iexp,
                             Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ ਘਾਤਾਂਕ)
{
    Vk_ਨਤੀਜਾ ret;
    AVVulkan_ਚੌਖਟੇ_Context *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ਅਚਲ VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ਪੂਰਨ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    ਪੂਰਨ nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_ਅਗਲਾ = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_ਅਗਲਾ = ਨਿਰਾ,
        .p_ਕਤਾਰ_Family_Indices   = p->img_qfs,
        .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = p->nb_img_qfs,
        .sharing_ਬਹੁਲਕ           = p->nb_img_qfs > 1 ? VK_SHARING_ਬਹੁਲਕ_CONCURRENT :
                                                     VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = ਘਾਤਾਂਕ,
        .p_ਅਗਲਾ = has_mods ? &phy_dev_mod_info : ਨਿਰਾ,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_ਅਗਲਾ  = !ਘਾਤਾਂਕ ? ਨਿਰਾ : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_ਦੋਆਧਾਰੀ_ਅੰਕ),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_ਗਿਣਤੀ : 1;
    ਲਈ (ਪੂਰਨ i = 0; i < nb_mods; i++) {
        ਜੇ (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        ਜੇ (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        ਜੇ (ret == VK_SUCCESS) {
            *iexp |= ਘਾਤਾਂਕ;
            *comp_handle_types |= eprops.external_ਸਮ੍ਰਿਤੀ_Properties.compatibleHandleTypes;
            ਜੇ (ਘਾਤਾਂਕ == VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT) {
                Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.external_ਸਮ੍ਰਿਤੀ_Properties.external_ਸਮ੍ਰਿਤੀ_Features &
                                                  VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_FEATURE_DEDICATED_ONLY_ਦੋਆਧਾਰੀ_ਅੰਕ);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
ਸਥਿਰ ਖਾਲੀ get_export_handle_types(AVHWFramesContext *hwfc,
                                    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags *comp_handle_types,
                                    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_ਅਣਵਰਤਿਆ AVVulkan_ਚੌਖਟੇ_Context *hwctx = &((Vulkan_ਚੌਖਟੇ_Priv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    ਜੇ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ਸਮ੍ਰਿਤੀ)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32_ਦੋਆਧਾਰੀ_ਅੰਕ
                             : VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32_KMT_ਦੋਆਧਾਰੀ_ਅੰਕ);
#ਨਹੀਂਤਾਂ
    ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ਸਮ੍ਰਿਤੀ) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_FD_ਦੋਆਧਾਰੀ_ਅੰਕ);

    ਜੇ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_ਸਮ੍ਰਿਤੀ &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ AVBufferRef *vulkan_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    ਪੂਰਨ err;
    AVVk_ਚੌਖਟਾ *f;
    AVBufferRef *avbuf = ਨਿਰਾ;
    AVHWFramesContext *hwfc = opaque;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkan_ਚੌਖਟੇ_Context *hwctx = &fp->p;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags e;
    Vk_Export_ਸਮ੍ਰਿਤੀ_Allocate_Info eminfo[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];

    Vk_External_ਸਮ੍ਰਿਤੀ_Image_Create_Info eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ਸਮ੍ਰਿਤੀ_IMAGE_CREATE_INFO,
        .p_ਅਗਲਾ       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    ਲਈ (ਪੂਰਨ i = 0; i < av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_ਸਮ੍ਰਿਤੀ_ALLOCATE_INFO;
        eminfo[i].p_ਅਗਲਾ       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_ਚੌਖਟਾ(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    ਜੇ (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        ਵਾਪਸ ਨਿਰਾ;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, ਆਕਾਰ(*eminfo));
    ਜੇ (err)
        ਜਾਓ fail;

    ਜੇ ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR))
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_DECODING_DPB);
    ਨਹੀਂਤਾਂ ਜੇ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_DECODING_DST);
    ਨਹੀਂਤਾਂ ਜੇ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_ENCODING_DPB);
    ਨਹੀਂਤਾਂ ਜੇ (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ)
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_WRITE);
    ਨਹੀਂਤਾਂ
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_GENERAL);
    ਜੇ (err)
        ਜਾਓ fail;

    avbuf = av_ਬਫਰ_create((uint8_t *)f, ਆਕਾਰ(AVVk_ਚੌਖਟਾ),
                             vulkan_ਚੌਖਟਾ_free_cb, hwfc, 0);
    ਜੇ (!avbuf)
        ਜਾਓ fail;

    ਵਾਪਸ avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_ਚੌਖਟਾ_free(hwfc, f);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ ਤਾਲਾ_ਚੌਖਟਾ(AVHWFramesContext *fc, AVVk_ਚੌਖਟਾ *vkf)
{
    pthread_mutex_ਤਾਲਾ(&vkf->ਅੰਦਰੂਨੀ->update_mutex);
}

ਸਥਿਰ ਖਾਲੀ unlock_ਚੌਖਟਾ(AVHWFramesContext *fc, AVVk_ਚੌਖਟਾ *vkf)
{
    pthread_mutex_unlock(&vkf->ਅੰਦਰੂਨੀ->update_mutex);
}

ਸਥਿਰ ਖਾਲੀ vulkan_ਚੌਖਟੇ_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;

    ਜੇ (fp->modifier_info) {
        ਜੇ (fp->modifier_info->pDrmFormatModifiers)
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
ਸਥਿਰ ਪੂਰਨ vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkan_ਚੌਖਟੇ_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_ਨਤੀਜਾ ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    ਅਚਲ ਬਣਤਰ FFVk_Format_ਇੰਦਰਾਜ *fmt = vk_ਲੱਭੋ_format_ਇੰਦਰਾਜ(hwfc->sw_format);
    ਜੇ (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        ਵਾਪਸ 0;
    }

    ਅਚਲ VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ਪੂਰਨ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_ਗਿਣਤੀ;
    ਪੂਰਨ nb_mods = has_mods ? mod_list->drm_Format_Modifier_ਗਿਣਤੀ : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    ਜੇ (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        ਵਾਪਸ 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_ਕਤਾਰ_Family_Indices   = p->img_qfs,
        .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = p->nb_img_qfs,
        .sharing_ਬਹੁਲਕ           = p->nb_img_qfs > 1 ? VK_SHARING_ਬਹੁਲਕ_CONCURRENT :
                                                     VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    ਜੇ (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ਅਚਲ VkVideoProfileListInfoKHR *pl =
        ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    ਜੇ (pl) {
        profile_list = *pl;
        profile_list.p_ਅਗਲਾ = ਨਿਰਾ;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ਅਚਲ VkImageFormatListCreateInfo *fl =
        ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    ਜੇ (fl) {
        format_list = *fl;
        format_list.p_ਅਗਲਾ = ਨਿਰਾ;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    ਲਈ (ਪੂਰਨ i = 0; i < AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        ਲਈ (ਪੂਰਨ j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_ਅਗਲਾ = &perf,
            };

            ਜੇ (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            ਜੇ (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                ਵਾਪਸ 0;
            }

            ਜੇ (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identical_ਸਮ੍ਰਿਤੀ_Layout);
                ਵਾਪਸ 0;
            }
        }
    }

    ਜੇ (!p->vkctx.host_image_props.identical_ਸਮ੍ਰਿਤੀ_Type_Requirements) {
        ਪੂਰਨ ਸੂਚਕਾਂਕ;
        Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags e;
        Vk_External_ਸਮ੍ਰਿਤੀ_Image_Create_Info eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ਸਮ੍ਰਿਤੀ_IMAGE_CREATE_INFO,
            .p_ਅਗਲਾ       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ਅਗਲਾ       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ, 1 },
            .mip_ਪੱਧਰ   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_ਗਿਣਤੀ_1_ਦੋਆਧਾਰੀ_ਅੰਕ,
            .p_ਕਤਾਰ_Family_Indices   = p->img_qfs,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = p->nb_img_qfs,
            .sharing_ਬਹੁਲਕ           = p->nb_img_qfs > 1 ? VK_SHARING_ਬਹੁਲਕ_CONCURRENT :
                                                         VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
        };
        Vk_Device_Image_ਸਮ੍ਰਿਤੀ_Requirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT : 0,
        };
        Vk_ਸਮ੍ਰਿਤੀ_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_2,
        };

        vk->Get_Device_Image_ਸਮ੍ਰਿਤੀ_Requirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        Vk_ਸਮ੍ਰਿਤੀ_Property_Flags req_flags = hwctx->tiling == VK_IMAGE_TILING_ਰੇਖਿਕ ?
                                          VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ :
                                          VK_ਸਮ੍ਰਿਤੀ_PROPERTY_DEVICE_LOCAL_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < p->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ; ਸੂਚਕਾਂਕ++) {
            ਜੇ (!(req.ਸਮ੍ਰਿਤੀ_Requirements.ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ & (1U << ਸੂਚਕਾਂਕ)))
                ਜਾਰੀ;
            ਜੇ ((p->mprops.ਸਮ੍ਰਿਤੀ_Types[ਸੂਚਕਾਂਕ].propertyFlags & req_flags) == req_flags)
                ਰੋਕੋ;
        }
        ਜੇ (ਸੂਚਕਾਂਕ == p->mprops.ਸਮ੍ਰਿਤੀ_Type_ਗਿਣਤੀ) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            ਵਾਪਸ 0;
        }
    }

    ਵਾਪਸ 1;
}

ਸਥਿਰ ਪੂਰਨ vulkan_ਚੌਖਟੇ_init(AVHWFramesContext *hwfc)
{
    ਪੂਰਨ err;
    AVVk_ਚੌਖਟਾ *f;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkan_ਚੌਖਟੇ_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਅਚਲ ਬਣਤਰ FFVk_Format_ਇੰਦਰਾਜ *fmt;
    ਅਚਲ AVPixFmtDescriptor *desc;
    ਪੂਰਨ disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_ਚੌਖਟਾ_FLAG_DISABLE_MULTIPLANE);
    ਪੂਰਨ is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR)));

    /* Defaults */
    ਜੇ (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    ਜੇ (p->use_ਰੇਖਿਕ_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_ਰੇਖਿਕ;


    fmt = vk_ਲੱਭੋ_format_ਇੰਦਰਾਜ(hwfc->sw_format);
    ਜੇ (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        ਵਾਪਸ AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ਜੇ ((hwfc->ਚੌੜਾਈ  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->ਉਚਾਈ & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    ਜੇ (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        ਜੇ (hwctx->format[0] != fmt->vkf) {
            ਲਈ (ਪੂਰਨ i = 0; i < fmt->nb_images_fallback; i++) {
                ਜੇ (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    ਵਾਪਸ AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, ਨਿਰਾ,
                                 ਨਿਰਾ, ਨਿਰਾ, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ));
        ਜੇ (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ਵਾਪਸ AVERROR(EINVAL);
        }
    } ਨਹੀਂਤਾਂ {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, ਨਿਰਾ,
                                 ਨਿਰਾ, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ));
        ਜੇ (err < 0)
            ਵਾਪਸ err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    ਪੂਰਨ drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    ਜੇ (!is_lone_dpb && !drm_mod_with_video) {
        /* Image usage flags */
        hwctx->usage |= supported_usage & (VK_IMAGE_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                           VK_IMAGE_USAGE_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                           VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ      |
                                           VK_IMAGE_USAGE_SAMPLED_ਦੋਆਧਾਰੀ_ਅੰਕ);

        /* Frames which may double as active references (coinciding decode
         * output) cannot support host transfers: decode submissions bake the
         * image layout into their barriers at record time, so a host-side
         * layout transition cannot be synchronized against them, not even
         * by the frame lock and timeline semaphore. */
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        ਜੇ ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_ਕਤਾਰ) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        ਜੇ (!hwctx->img_flags) {
            ਪੂਰਨ sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                             VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਜੇ (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_ਦੋਆਧਾਰੀ_ਅੰਕ;
                ਜੇ ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    ਜੇ ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_ਕਤਾਰ) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ਅਚਲ VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_ਲੱਭੋ_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        ਜੇ (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
        } ਨਹੀਂਤਾਂ {
            uint32_t i;
            ਲਈ (i = 0; i < pl->profile_ਗਿਣਤੀ; i++) {
                /* Video ops start at exactly 0x00010000 */
                ਜੇ (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    ਰੋਕੋ;
            }
            ਜੇ (i == pl->profile_ਗਿਣਤੀ)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    ਜੇ ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;

    ਜੇ (!hwctx->ਤਾਲਾ_ਚੌਖਟਾ)
        hwctx->ਤਾਲਾ_ਚੌਖਟਾ = ਤਾਲਾ_ਚੌਖਟਾ;

    ਜੇ (!hwctx->unlock_ਚੌਖਟਾ)
        hwctx->unlock_ਚੌਖਟਾ = unlock_ਚੌਖਟਾ;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, ਨਿਰਾ);
    ਜੇ (err)
        ਵਾਪਸ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, ਨਿਰਾ);
    ਜੇ (err)
        ਵਾਪਸ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, ਨਿਰਾ);
    ਜੇ (err)
        ਵਾਪਸ err;

    /* Test to see if allocation will fail */
    err = create_ਚੌਖਟਾ(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    ਜੇ (err)
        ਵਾਪਸ err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    ਜੇ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        ਜੇ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_ਚੌਖਟਾ_free(hwfc, f);
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
        ਲਈ (ਪੂਰਨ i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = ਨਿਰਾ;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ਅਗਲਾ = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_ਗਿਣਤੀ, ਆਕਾਰ(*modp.pDrmFormatModifierProperties));
            ਜੇ (!modp.pDrmFormatModifierProperties) {
                vulkan_ਚੌਖਟਾ_free(hwfc, f);
                ਵਾਪਸ AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            ਲਈ (uint32_t j = 0; j < modp.drm_Format_Modifier_ਗਿਣਤੀ; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                ਜੇ (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    ਰੋਕੋ;
                }
            }

            ਜੇ (mod_props == ਨਿਰਾ) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_ਚੌਖਟਾ_free(hwfc, f);
                ਵਾਪਸ AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_ਚੌਖਟਾ_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    ਜੇ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_ਅੰਦਰੂਨੀ = av_ਬਫਰ_pool_init2(ਆਕਾਰ(AVVk_ਚੌਖਟਾ),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(hwfc)->pool_ਅੰਦਰੂਨੀ)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vulkan_get_ਬਫਰ(AVHWFramesContext *hwfc, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(hwfc->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[0] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_VULKAN;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = hwfc->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = hwfc->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                       ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;
    ਪੂਰਨ n = 2;

#ਜੇ CONFIG_CUDA
    n++;
#ਜੇ_ਅੰਤ
    fmts = av_malloc_array(n, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#ਜੇ CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#ਜੇ_ਅੰਤ
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ਵਾਪਸ 0;
}

#ਜੇ CONFIG_LIBDRM
ਸਥਿਰ ਖਾਲੀ vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_ਚੌਖਟਾ_free(hwfc, hwmap->priv);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
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
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#ਜੇ_ਅੰਤ
};

ਸਥਿਰ ਸਤਰਅੰਦਰ VkFormat drm_ਮੰਜ਼ਿਲ_vulkan_fmt(uint32_t drm_fourcc)
{
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ਜੇ (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            ਵਾਪਸ vulkan_drm_format_map[i].vk_format;
    ਵਾਪਸ VK_FORMAT_UNDEFINED;
}

ਸਥਿਰ ਪੂਰਨ vulkan_map_from_drm_ਚੌਖਟਾ_desc(AVHWFramesContext *hwfc, AVVk_ਚੌਖਟਾ **ਚੌਖਟਾ,
                                          ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    AVVk_ਚੌਖਟਾ *f;
    ਪੂਰਨ bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਅਚਲ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->ਅੰਕੜੇ[0];
    Vk_Bind_Image_ਸਮ੍ਰਿਤੀ_Info bind_info[AV_DRM_MAX_PLANES];
    Vk_Bind_Image_Plane_ਸਮ੍ਰਿਤੀ_Info plane_info[AV_DRM_MAX_PLANES];

    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_layers; i++) {
        ਜੇ (drm_ਮੰਜ਼ਿਲ_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਜੇ (!(f = av_vk_ਚੌਖਟਾ_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_layers; i++) {
        ਅਚਲ ਪੂਰਨ planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_ਮੁੱਲ  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ਅਗਲਾ = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_ਗਿਣਤੀ = planes,
            .pPlaneLayouts = (ਅਚਲ VkSubresourceLayout *)&ext_img_layouts,
        };
        Vk_External_ਸਮ੍ਰਿਤੀ_Image_Create_Info ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_ਸਮ੍ਰਿਤੀ_IMAGE_CREATE_INFO,
            .p_ਅਗਲਾ       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ਅਗਲਾ                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_ਮੰਜ਼ਿਲ_vulkan_fmt(desc->layers[i].format),
            .extent.ਡੂੰਘਾਈ          = 1,
            .mip_ਪੱਧਰ             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_ਗਿਣਤੀ_1_ਦੋਆਧਾਰੀ_ਅੰਕ,
            .p_ਕਤਾਰ_Family_Indices   = p->img_qfs,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = p->nb_img_qfs,
            .sharing_ਬਹੁਲਕ           = p->nb_img_qfs > 1 ? VK_SHARING_ਬਹੁਲਕ_CONCURRENT :
                                                         VK_SHARING_ਬਹੁਲਕ_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        ਜੇ (planes == 1) {
            ਅਚਲ VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            ਜੇ (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .p_ਅਗਲਾ = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .p_ਕਤਾਰ_Family_Indices = create_info.p_ਕਤਾਰ_Family_Indices,
            .ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ = create_info.ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ_ਗਿਣਤੀ,
            .sharing_ਬਹੁਲਕ = create_info.sharing_ਬਹੁਲਕ,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_ਅਗਲਾ = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        ਜੇ (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ;
        ਜੇ (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                 VK_IMAGE_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .p_ਅਗਲਾ  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.ਚੌੜਾਈ, &create_info.extent.ਉਚਾਈ,
                     hwfc->sw_format, src->ਚੌੜਾਈ, src->ਉਚਾਈ, i);

        /* Set the subresource layout based on the layer properties */
        ਲਈ (ਪੂਰਨ j = 0; j < planes; j++) {
            ext_img_layouts[j].ਵਿੱਥ     = desc->layers[i].planes[j].ਵਿੱਥ;
            ext_img_layouts[j].ਪੰਕਤੀ_Pitch_2   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].ਮਾਪ       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].ਡੂੰਘਾਈ_Pitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ਜਾਓ fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ਜਾਓ fail;
        }

        f->ਕਤਾਰ_family[i] = VK_ਕਤਾਰ_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ਮੁੱਲ[i] = 0;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        Vk_Image_ਸਮ੍ਰਿਤੀ_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_REQUIREMENTS,
        };
        Vk_ਸਮ੍ਰਿਤੀ_Requirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_REQUIREMENTS_2,
            .p_ਅਗਲਾ = &ded_req,
        };

        /* Allocation/importing */
        Vk_ਸਮ੍ਰਿਤੀ_Fd_Properties_KHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        Vk_Import_ਸਮ੍ਰਿਤੀ_Fd_Info_KHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_ਸਮ੍ਰਿਤੀ_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_ਸੂਚਕਾਂਕ].fd),
            .handleType = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
        };
        Vk_ਸਮ੍ਰਿਤੀ_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_DEDICATED_ALLOCATE_INFO,
            .p_ਅਗਲਾ = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->Get_ਸਮ੍ਰਿਤੀ_Fd_Properties_KHR(hwctx->act_dev,
                                           VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
                                           idesc.fd, &fdmp);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            ਜਾਓ fail;
        }

        vk->Get_Image_ਸਮ੍ਰਿਤੀ_Requirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.ਸਮ੍ਰਿਤੀ_Requirements.ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ = fdmp.ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;

        err = alloc_mem(ctx, &req2.ਸਮ੍ਰਿਤੀ_Requirements,
                        VK_ਸਮ੍ਰਿਤੀ_PROPERTY_DEVICE_LOCAL_ਦੋਆਧਾਰੀ_ਅੰਕ,
                        (ded_req.prefers_Dedicated_ਵੰਡ ||
                         ded_req.requires_Dedicated_ਵੰਡ) ?
                            &ded_alloc : ded_alloc.p_ਅਗਲਾ,
                        &f->flags, &f->mem[i]);
        ਜੇ (err) {
            close(idesc.fd);
            ਜਾਓ fail;
        }

        f->ਮਾਪ[i] = req2.ਸਮ੍ਰਿਤੀ_Requirements.ਮਾਪ;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_layers; i++) {
        ਅਚਲ ਪੂਰਨ planes = desc->layers[i].nb_planes;
        ਲਈ (ਪੂਰਨ j = 0; j < planes; j++) {
            Vk_Image_Aspect_Flag_ਬਿੱਟ aspect = j == 0 ? VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT :
                                                    VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_2_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_ਸਮ੍ਰਿਤੀ_INFO;
            plane_info[bind_counts].p_ਅਗਲਾ = ਨਿਰਾ;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_ਸਮ੍ਰਿਤੀ_INFO;
            bind_info[bind_counts].p_ਅਗਲਾ  = planes > 1 ? &plane_info[bind_counts] : ਨਿਰਾ;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].ਸਮ੍ਰਿਤੀ = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].ਸਮ੍ਰਿਤੀ_ਵਿੱਥ = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ਜਾਓ fail;
    }

    *ਚੌਖਟਾ = f;

    ਵਾਪਸ 0;

fail:
    vulkan_ਚੌਖਟਾ_free(hwfc, f);

    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vulkan_map_from_drm_ਚੌਖਟਾ_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ਅਚਲ AVDRMFrameDescriptor *desc, ਪੂਰਨ flags)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ਜੇ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_ਬਫਰ cmd_buf;
        FFVkExecContext *exec;
        Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 img_bar[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        ਪੂਰਨ nb_img_bar = 0;

        ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ਦੁਆਧਾਰੀ,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_ਅਗਲਾ = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            ਬਣਤਰ dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            ਜੇ (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                ਲਈ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ਵਾਪਸ err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            ਜੇ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ਲਈ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ਵਾਪਸ err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ਦੋਆਧਾਰੀ_ਅੰਕ,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_ਦੋਆਧਾਰੀ_ਅੰਕ,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            ਜੇ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ਲਈ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ਵਾਪਸ err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_ਸ਼ੁਰੂ(&p->vkctx, exec);
        ਜੇ (err < 0) {
            ਲਈ (ਪੂਰਨ i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            ਵਾਪਸ err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_ਜੋੜੋ_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_ਜੋੜੋ_dep_ਚੌਖਟਾ(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ);
        ਜੇ (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            ਵਾਪਸ err;
        }

        ff_vk_ਚੌਖਟਾ_barrier(&p->vkctx, exec, dst, img_bar, &nb_img_bar,
                            VK_PIPELINE_STAGE_2_NONE,
                            VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                            ((flags & AV_HWFRAME_MAP_READ) ?
                             VK_ACCESS_2_SHADER_SAMPLED_READ_ਦੋਆਧਾਰੀ_ਅੰਕ : 0x0) |
                            ((flags & AV_HWFRAME_MAP_WRITE) ?
                             VK_ACCESS_2_SHADER_STORAGE_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ : 0x0),
                            VK_IMAGE_LAYOUT_GENERAL,
                            p->nb_img_qfs > 1 ? VK_ਕਤਾਰ_FAMILY_IGNORED : p->img_qfs[0]);

        vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
                .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                .p_Image_ਸਮ੍ਰਿਤੀ_Barriers = img_bar,
                .image_ਸਮ੍ਰਿਤੀ_Barrier_ਗਿਣਤੀ = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        AVVk_ਚੌਖਟਾ *f = (AVVk_ਚੌਖਟਾ *)dst->ਅੰਕੜੇ[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT);
        ਜੇ (err)
            ਵਾਪਸ err;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err = 0;
    AVVk_ਚੌਖਟਾ *f;
    ਅਚਲ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->ਅੰਕੜੇ[0];

    ਜੇ ((err = vulkan_map_from_drm_ਚੌਖਟਾ_desc(hwfc, &f, src, flags)))
        ਵਾਪਸ err;

    /* The unmapping function will free this */
    dst->ਅੰਕੜੇ[0] = (uint8_t *)f;
    dst->ਚੌੜਾਈ   = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ  = src->ਉਚਾਈ;

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = vulkan_map_from_drm_ਚੌਖਟਾ_sync(hwfc, dst, desc, flags);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    ਵਾਪਸ 0;

fail:
    vulkan_ਚੌਖਟਾ_free(hwfc->device_ctx->hwctx, f);
    dst->ਅੰਕੜੇ[0] = ਨਿਰਾ;
    ਵਾਪਸ err;
}

#ਜੇ CONFIG_VAAPI
ਸਥਿਰ ਪੂਰਨ vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ਅਚਲ AVFrame *src,
                                 ਪੂਰਨ flags)
{
    ਪੂਰਨ err;
    AVFrame *tmp = av_ਚੌਖਟਾ_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->ਅੰਕੜੇ[3];

    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_ਅਭਾਜ;

    err = av_hwframe_map(tmp, src, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ਚੌਖਟਾ_free(&tmp);
    ਵਾਪਸ err;
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_CUDA
ਸਥਿਰ ਪੂਰਨ export_mem_ਮੰਜ਼ਿਲ_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *dst_int, ਪੂਰਨ idx,
                              Vk_Device_ਸਮ੍ਰਿਤੀ mem, size_t ਮਾਪ)
{
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    CUDA_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .ਮਾਪ = ਮਾਪ,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Get_Win32_Handle_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_GET_WIN32_HANDLE_INFO_KHR,
        .ਸਮ੍ਰਿਤੀ     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32_ਦੋਆਧਾਰੀ_ਅੰਕ
            : VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_WIN32_KMT_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };

    ret = vk->Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_KHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#ਨਹੀਂਤਾਂ
    CUDA_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_FD,
        .ਮਾਪ = ਮਾਪ,
    };
    Vk_ਸਮ੍ਰਿਤੀ_Get_Fd_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_GET_FD_INFO_KHR,
        .ਸਮ੍ਰਿਤੀ     = mem,
        .handleType = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_OPAQUE_FD_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
    };

    ret = vk->Get_ਸਮ੍ਰਿਤੀ_Fd_KHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }
#ਜੇ_ਅੰਤ

    ret = CHECK_CU(cu->cu_Import_External_ਸਮ੍ਰਿਤੀ(&dst_int->ext_mem[idx], &ext_desc));
    ਜੇ (ret < 0) {
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _WIN32
        close(ext_desc.handle.fd);
#ਜੇ_ਅੰਤ
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ export_sem_ਮੰਜ਼ਿਲ_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *dst_int, ਪੂਰਨ idx,
                              VkSemaphore sem)
{
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    VkSemaphoreGetWin32HandleInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
        .semaphore = sem,
        .handleType = IsWindows8OrGreater()
                      ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ਦੋਆਧਾਰੀ_ਅੰਕ
                      : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 10 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32 */,
    };
#ਨਹੀਂਤਾਂ
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ਦੋਆਧਾਰੀ_ਅੰਕ,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#ਨਹੀਂਤਾਂ
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#ਜੇ_ਅੰਤ
    ਜੇ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        ਵਾਪਸ AVERROR_EXTERNAL;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#ਜੇ_ਅੰਤ

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    ਜੇ (ret < 0) {
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _WIN32
        close(ext_sem_desc.handle.fd);
#ਜੇ_ਅੰਤ
        ਵਾਪਸ AVERROR_EXTERNAL;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vulkan_export_ਮੰਜ਼ਿਲ_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ਅਚਲ AVFrame *ਚੌਖਟਾ)
{
    ਪੂਰਨ err;
    Vk_ਨਤੀਜਾ ret;
    AVVk_ਚੌਖਟਾ *dst_f;
    AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ਪੂਰਨ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->ਅੰਕੜੇ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ਅੰਦਰੂਨੀ *cu_ਅੰਦਰੂਨੀ = cuda_dev->ਅੰਦਰੂਨੀ;
    CudaFunctions *cu = cu_ਅੰਦਰੂਨੀ->cuda_dl;
    CUarray_format cufmt = desc->comp[0].ਡੂੰਘਾਈ > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ਅਚਲ ਪੂਰਨ elem_ਮਾਪ = 1 + (desc->comp[0].ਡੂੰਘਾਈ > 8);

    dst_f = (AVVk_ਚੌਖਟਾ *)ਚੌਖਟਾ->ਅੰਕੜੇ[0];
    dst_int = dst_f->ਅੰਦਰੂਨੀ;

    ਜੇ (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_ਬਫਰ_ref(cuda_hwfc);
        ਜੇ (!dst_int->cuda_fc_ref)
            ਵਾਪਸ AVERROR(ENOMEM);

        nb_images = ff_vk_ਗਿਣਤੀ_images(dst_f);
        ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
            err = export_mem_ਮੰਜ਼ਿਲ_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->ਮਾਪ[i]);
            ਜੇ (err < 0)
                ਜਾਓ fail;

            err = export_sem_ਮੰਜ਼ਿਲ_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            ਜੇ (err < 0)
                ਜਾਓ fail;
        }

        ਜੇ (nb_images != planes) {
            ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                ਜੇ (desc->comp[i].ਕਦਮ / elem_ਮਾਪ > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    ਜਾਓ fail;
                }

                VkImageSubresource subres = {
                    .aspect_ਨਕਾਬ = i == 2 ? VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_2_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT :
                                           VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.ਵਿੱਥ;
            }
        }

        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
            CUDA_EXTERNAL_ਸਮ੍ਰਿਤੀ_MIPMAPPED_ARRAY_DESC tex_desc = {
                .ਵਿੱਥ = offsets[i],
                .arrayDesc = {
                    .ਡੂੰਘਾਈ_2 = 0,
                    .Format = cufmt,
                    .ਅੰਕ_Channels = desc->comp[i].ਕਦਮ / elem_ਮਾਪ,
                    .Flags = 0,
                },
                .ਅੰਕ_ਪੱਧਰ = 1,
            };
            ਪੂਰਨ p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ, i);
            tex_desc.arrayDesc.ਚੌੜਾਈ_2 = p_w;
            tex_desc.arrayDesc.ਉਚਾਈ_2 = p_h;

            ret = CHECK_CU(cu->cu_External_ਸਮ੍ਰਿਤੀ_Get_Mapped_Mipmapped_Array(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            ਜੇ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ਜਾਓ fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            ਜੇ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ਜਾਓ fail;
            }

        }
    }

    ਵਾਪਸ 0;

fail:
    vulkan_free_ਅੰਦਰੂਨੀ(p, dst_f);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_ਅੰਕੜੇ_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ err;
    CUcontext dummy;
    AVVk_ਚੌਖਟਾ *dst_f;
    AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ਪੂਰਨ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ਅੰਦਰੂਨੀ *cu_ਅੰਦਰੂਨੀ = cuda_dev->ਅੰਦਰੂਨੀ;
    CudaFunctions *cu = cu_ਅੰਦਰੂਨੀ->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };

    dst_f = (AVVk_ਚੌਖਟਾ *)dst->ਅੰਕੜੇ[0];
    nb_images = ff_vk_ਗਿਣਤੀ_images(dst_f);

    err = prepare_ਚੌਖਟਾ(hwfc, &fp->upload_exec, dst_f, PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    err = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(cuda_dev->cuda_ctx));
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    err = vulkan_export_ਮੰਜ਼ਿਲ_cuda(hwfc, src->hw_ਚੌਖਟੇ_ctx, dst);
    ਜੇ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
        ਵਾਪਸ err;
    }

    dst_int = dst_f->ਅੰਦਰੂਨੀ;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ਮੁੱਲ = dst_f->sem_ਮੁੱਲ[i] + 0;
        s_s_par[i].params.fence.ਮੁੱਲ = dst_f->sem_ਮੁੱਲ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ਧਾਰਾ));
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .src_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->ਅੰਕੜੇ[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dst_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        ਪੂਰਨ p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ, i);

        cpy.ਚੌੜਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ = p_w * desc->comp[i].ਕਦਮ;
        cpy.ਉਚਾਈ_2 = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ਧਾਰਾ));
        ਜੇ (err < 0)
            ਜਾਓ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ਧਾਰਾ));
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++)
        dst_f->sem_ਮੁੱਲ[i]++;

    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    ਵਾਪਸ err = prepare_ਚੌਖਟਾ(hwfc, &fp->upload_exec, dst_f, PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    vulkan_free_ਅੰਦਰੂਨੀ(p, dst_f);
    av_ਬਫਰ_unref(&dst->buf[0]);
    ਵਾਪਸ err;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ vulkan_map_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc, AVFrame *dst,
                         ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    av_ਅਣਵਰਤਿਆ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ਚੋਣ (src->format) {
#ਜੇ CONFIG_LIBDRM
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ਵਾਪਸ vulkan_map_from_vaapi(hwfc, dst, src, flags);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
    ਹਾਲਤ AV_PIX_FMT_DRM_ਅਭਾਜ:
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ਵਾਪਸ vulkan_map_from_drm(hwfc, dst, src, flags);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }
}

#ਜੇ CONFIG_LIBDRM
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVk_ਚੌਖਟਾ *ਸਰੋਤ;
} VulkanDRMMapping;

ਸਥਿਰ ਖਾਲੀ vulkan_unmap_ਮੰਜ਼ਿਲ_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_ਚੌਖਟਾ_sync(hwfc, hwmap->ਸਰੋਤ, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    ਲਈ (ਪੂਰਨ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t vulkan_fmt_ਮੰਜ਼ਿਲ_drm(VkFormat vkfmt)
{
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ਜੇ (vulkan_drm_format_map[i].vk_format == vkfmt)
            ਵਾਪਸ vulkan_drm_format_map[i].drm_fourcc;
    ਵਾਪਸ DRM_FORMAT_INVALID;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਸਮ੍ਰਿਤੀ_PLANES 4
ਸਥਿਰ VkImageAspectFlags plane_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_aspect(ਪੂਰਨ plane) {
    ਜੇ (plane == 0) ਵਾਪਸ VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;
    ਜੇ (plane == 1) ਵਾਪਸ VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_1_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;
    ਜੇ (plane == 2) ਵਾਪਸ VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_2_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;
    ਜੇ (plane == 3) ਵਾਪਸ VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_3_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;

    av_assert2 (0 && "Invalid plane index");
    ਵਾਪਸ VK_IMAGE_ASPECT_ਸਮ੍ਰਿਤੀ_PLANE_0_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
ਸਥਿਰ ਪੂਰਨ vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVk_ਚੌਖਟਾ *f,
                                     Vulkan_ਚੌਖਟੇ_Priv *fp, ਪੂਰਨ nb_sems)
{
    ਪੂਰਨ sync_fd = -1;
    Vk_ਨਤੀਜਾ ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ਜੇ (f->ਅੰਦਰੂਨੀ->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ਦੋਆਧਾਰੀ_ਅੰਕ,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_ਅਗਲਾ         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ਦੁਆਧਾਰੀ,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ਅਗਲਾ = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->ਅੰਦਰੂਨੀ->drm_sync_sem);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    ਜੇ (ff_vk_exec_ਸ਼ੁਰੂ(&p->vkctx, exec) >= 0) {
        ਲਈ (ਪੂਰਨ i = 0; i < nb_sems; i++)
            ff_vk_exec_ਜੋੜੋ_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_ਮੁੱਲ[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ);
        ff_vk_exec_ਜੋੜੋ_dep_bool_sem(&p->vkctx, exec, &f->ਅੰਦਰੂਨੀ->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ, 0);
        ਜੇ (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->ਅੰਦਰੂਨੀ->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ਦੋਆਧਾਰੀ_ਅੰਕ,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            ਜੇ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    ਵਾਪਸ sync_fd;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ vulkan_map_ਮੰਜ਼ਿਲ_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err = 0;
    Vk_ਨਤੀਜਾ ret;
    AVVk_ਚੌਖਟਾ *f = (AVVk_ਚੌਖਟਾ *)src->ਅੰਕੜੇ[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ਅਚਲ ਪੂਰਨ nb_sems = nb_images;
    ਪੂਰਨ free_drm_desc_on_err = 1;
    ਪੂਰਨ sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(ਆਕਾਰ(*drm_desc));
    ਜੇ (!drm_desc)
        ਵਾਪਸ AVERROR(ENOMEM);

    err = prepare_ਚੌਖਟਾ(hwfc, &fp->compute_exec, f, PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        ਜੇ (err < 0)
            ਜਾਓ ਸਿਰਾ;
        sync_fd = err;
        err = 0;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_ਗਿਣਤੀ = nb_sems,
            .pSemaphores    = f->sem,
            .p_ਮੁੱਲਾਂ        = f->sem_ਮੁੱਲ,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src, &vulkan_unmap_ਮੰਜ਼ਿਲ_drm, drm_desc);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    ਜੇ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        ਜਾਓ ਸਿਰਾ;
    }

    ਲਈ (ਪੂਰਨ i = 0; (i < planes) && (f->mem[i]); i++) {
        Vk_ਸਮ੍ਰਿਤੀ_Get_Fd_Info_KHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_GET_FD_INFO_KHR,
            .ਸਮ੍ਰਿਤੀ     = f->mem[i],
            .handleType = VK_EXTERNAL_ਸਮ੍ਰਿਤੀ_HANDLE_TYPE_DMA_BUF_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT,
        };

        ret = vk->Get_ਸਮ੍ਰਿਤੀ_Fd_KHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        ਜੇ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            ਜਾਓ ਸਿਰਾ;
        }

#ਜੇ HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        ਜੇ (sync_fd >= 0) {
            ਪੂਰਨ dup_fd = dup(sync_fd);
            ਜੇ (dup_fd >= 0) {
                ਬਣਤਰ dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                ਜੇ (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } ਨਹੀਂਤਾਂ {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#ਜੇ_ਅੰਤ

        drm_desc->nb_objects++;
        drm_desc->objects[i].ਮਾਪ = f->ਮਾਪ[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    ਲਈ (ਪੂਰਨ i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_ਮੰਜ਼ਿਲ_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_ਗਿਣਤੀ;

        ਜੇ (drm_desc->layers[i].nb_planes > MAX_ਸਮ੍ਰਿਤੀ_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            ਜਾਓ ਸਿਰਾ;
        }

        ਲਈ (ਪੂਰਨ j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            ਪੂਰਨ aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspect_ਨਕਾਬ = plane_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_ਸੂਚਕਾਂਕ = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].ਵਿੱਥ = layout.ਵਿੱਥ;
            drm_desc->layers[i].planes[j].pitch  = layout.ਪੰਕਤੀ_Pitch_2;
        }

        ਜੇ (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            ਜਾਓ ਸਿਰਾ;
        }


        ਜੇ (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            ਜਾਰੀ;

    }

    dst->ਚੌੜਾਈ   = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ  = src->ਉਚਾਈ;
    dst->ਅੰਕੜੇ[0] = (uint8_t *)drm_desc;
    dst->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(src->hw_ਚੌਖਟੇ_ctx);

    ਜੇ (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    ਵਾਪਸ 0;

ਸਿਰਾ:
    ਲਈ (ਪੂਰਨ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    ਜੇ (free_drm_desc_on_err)
        av_free(drm_desc);
    ਜੇ (sync_fd >= 0)
        close(sync_fd);
    ਵਾਪਸ err;
}

#ਜੇ CONFIG_VAAPI
ਸਥਿਰ ਪੂਰਨ vulkan_map_ਮੰਜ਼ਿਲ_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err;
    AVFrame *tmp = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ਅਭਾਜ;

    err = vulkan_map_ਮੰਜ਼ਿਲ_drm(hwfc, tmp, src, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = av_hwframe_map(dst, tmp, flags);
    ਜੇ (err < 0)
        ਜਾਓ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_ਚੌਖਟਾ_free(&tmp);
    ਵਾਪਸ err;
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    av_ਅਣਵਰਤਿਆ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ਚੋਣ (dst->format) {
#ਜੇ CONFIG_LIBDRM
    ਹਾਲਤ AV_PIX_FMT_DRM_ਅਭਾਜ:
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ਵਾਪਸ vulkan_map_ਮੰਜ਼ਿਲ_drm(hwfc, dst, src, flags);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
        ਜੇ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ਵਾਪਸ vulkan_map_ਮੰਜ਼ਿਲ_vaapi(hwfc, dst, src, flags);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ AVERROR(ENOSYS);
}

ਸਥਿਰ ਪੂਰਨ copy_ਬਫਰ_ਅੰਕੜੇ(AVHWFramesContext *hwfc, FFVk_ਬਫਰ *vkbuf,
                            AVFrame *swf, Vk_ਬਫਰ_Image_Copy *region,
                            ਪੂਰਨ planes, ਪੂਰਨ upload)
{
    ਪੂਰਨ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ਪੂਰਨ bytewidth[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->ਚੌੜਾਈ, i);
        ਜੇ (bytewidth[i] < 0)
            ਵਾਪਸ bytewidth[i];
    }

    ਜੇ (upload) {
        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].ਬਫਰ_ਵਿੱਥ,
                                region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ,
                                swf->ਅੰਕੜੇ[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.ਉਚਾਈ);

        err = ff_vk_flush_ਬਫਰ(&p->vkctx, vkbuf, 0, VK_ਸਾਰਾ_ਮਾਪ, 1);
        ਜੇ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }
    } ਨਹੀਂਤਾਂ {
        err = ff_vk_flush_ਬਫਰ(&p->vkctx, vkbuf, 0, VK_ਸਾਰਾ_ਮਾਪ, 0);
        ਜੇ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            ਵਾਪਸ AVERROR_EXTERNAL;
        }

        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
            av_image_copy_plane(swf->ਅੰਕੜੇ[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].ਬਫਰ_ਵਿੱਥ,
                                region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ,
                                bytewidth[i],
                                region[i].imageExtent.ਉਚਾਈ);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ get_plane_buf(AVHWFramesContext *hwfc, FFVk_ਬਫਰ **dst,
                         AVFrame *swf, Vk_ਬਫਰ_Image_Copy *region, ਪੂਰਨ upload)
{
    ਪੂਰਨ err;
    uint32_t p_w, p_h;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(swf->format);
    Vk_ਬਫਰ_Usage_Flags buf_usage = upload ? VK_ਬਫਰ_USAGE_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ :
                                            VK_ਬਫਰ_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ;

    size_t buf_ਵਿੱਥ = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->ਚੌੜਾਈ, swf->ਉਚਾਈ, i);

        region[i] = (Vk_ਬਫਰ_Image_Copy) {
            .ਬਫਰ_ਵਿੱਥ = buf_ਵਿੱਥ,
            .ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_ਬਫਰ_Copy_ਪੰਕਤੀ_Pitch_Alignment),
            .ਬਫਰ_Image_ਉਚਾਈ = p_h,
            .imageSubresource.layer_ਗਿਣਤੀ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_ਵਿੱਥ += FFALIGN(p_h*region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ,
                              p->props.properties.limits.optimal_ਬਫਰ_Copy_ਵਿੱਥ_Alignment);
    }

    err = ff_vk_get_pooled_ਬਫਰ(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  ਨਿਰਾ, buf_ਵਿੱਥ,
                                  VK_ਸਮ੍ਰਿਤੀ_PROPERTY_HOST_VISIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ |
                                  p->vkctx.host_cached_flag);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ host_map_ਚੌਖਟਾ(AVHWFramesContext *hwfc, FFVk_ਬਫਰ **dst, ਪੂਰਨ *nb_bufs,
                          AVFrame *swf, Vk_ਬਫਰ_Image_Copy *region, ਪੂਰਨ upload)
{
    ਪੂਰਨ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ਪੂਰਨ nb_src_bufs;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(swf->format);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_ਬਫਰ_Usage_Flags buf_usage = upload ? VK_ਬਫਰ_USAGE_TRANSFER_SRC_ਦੋਆਧਾਰੀ_ਅੰਕ :
                                            VK_ਬਫਰ_USAGE_TRANSFER_DST_ਦੋਆਧਾਰੀ_ਅੰਕ;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    ਜਦੋਂ (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    ਜੇ (nb_src_bufs == 1) {
        err = ff_vk_host_map_ਬਫਰ(&p->vkctx, &dst[0],
                                    swf->ਅੰਕੜੇ[0], VK_ਸਾਰਾ_ਮਾਪ, swf->buf[0],
                                    buf_usage);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
        (*nb_bufs)++;

        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
            region[i].ਬਫਰ_ਵਿੱਥ = dst[0]->virtual_ਵਿੱਥ +
                                     swf->ਅੰਕੜੇ[i] - swf->ਅੰਕੜੇ[0];
    } ਨਹੀਂਤਾਂ ਜੇ (nb_src_bufs == planes) { /* One buffer per plane */
        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
            err = ff_vk_host_map_ਬਫਰ(&p->vkctx, &dst[i],
                                        swf->ਅੰਕੜੇ[i], VK_ਸਾਰਾ_ਮਾਪ,
                                        swf->buf[i], buf_usage);
            ਜੇ (err < 0)
                ਜਾਓ fail;
            (*nb_bufs)++;

            region[i].ਬਫਰ_ਵਿੱਥ = dst[i]->virtual_ਵਿੱਥ;
        }
    } ਨਹੀਂਤਾਂ {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        ਵਾਪਸ AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        ਪੂਰਨ align = FFMAX(desc->comp[i].ਕਦਮ, p->transfer_ਵਿੱਥ_align);
        ਜੇ ((align & (align - 1)) || (region[i].ਬਫਰ_ਵਿੱਥ & (align - 1))) {
            err = AVERROR(EINVAL);
            ਜਾਓ fail;
        }
    }

    ਵਾਪਸ 0;

fail:
    ਲਈ (ਪੂਰਨ i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, ਪੂਰਨ upload)
{
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkan_ਚੌਖਟੇ_Context *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVk_ਚੌਖਟਾ *hwf_vk = (AVVk_ਚੌਖਟਾ *)hwf->ਅੰਕੜੇ[0];
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(swf->format);
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ nb_layout_ch = 0;

    hwfc_vk->ਤਾਲਾ_ਚੌਖਟਾ(hwfc, hwf_vk);

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        ਪੂਰਨ compat = 0;
        ਲਈ (ਪੂਰਨ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ਗਿਣਤੀ; j++) {
            ਜੇ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                ਰੋਕੋ;
            }
        }
        ਜੇ (compat)
            ਜਾਰੀ;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspect_ਨਕਾਬ = VK_IMAGE_ASPECT_COLOR_ਦੋਆਧਾਰੀ_ਅੰਕ,
                .level_ਗਿਣਤੀ = 1,
                .layer_ਗਿਣਤੀ = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_ਮੁੱਲਾਂ = hwf_vk->sem_ਮੁੱਲ,
        .semaphore_ਗਿਣਤੀ = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    ਜੇ (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    ਜੇ (upload) {
        Vk_ਸਮ੍ਰਿਤੀ_ਮੰਜ਼ਿਲ_Image_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_ਸਮ੍ਰਿਤੀ_ਮੰਜ਼ਿਲ_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_ਗਿਣਤੀ = 1,
            },
        };
        Vk_Copy_ਸਮ੍ਰਿਤੀ_ਮੰਜ਼ਿਲ_Image_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_ਸਮ੍ਰਿਤੀ_ਮੰਜ਼ਿਲ_IMAGE_INFO_EXT,
            .region_ਗਿਣਤੀ = 1,
            .pRegions = &region_info,
        };
        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
            ਪੂਰਨ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ਚੌੜਾਈ, swf->ਉਚਾਈ, i);

            region_info.p_Host_ਸੂਚਕ = swf->ਅੰਕੜੇ[i];
            region_info.ਸਮ੍ਰਿਤੀ_ਪੰਕਤੀ_ਲੰਮਾਈ = swf->linesize[i] / desc->comp[i].ਕਦਮ;
            region_info.imageSubresource.aspect_ਨਕਾਬ = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_ਸਮ੍ਰਿਤੀ_ਮੰਜ਼ਿਲ_Image_EXT(hwctx->act_dev, &copy_info);
        }
    } ਨਹੀਂਤਾਂ {
        Vk_Image_ਮੰਜ਼ਿਲ_ਸਮ੍ਰਿਤੀ_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_ਮੰਜ਼ਿਲ_ਸਮ੍ਰਿਤੀ_COPY_EXT,
            .imageSubresource = {
                .layer_ਗਿਣਤੀ = 1,
            },
        };
        Vk_Copy_Image_ਮੰਜ਼ਿਲ_ਸਮ੍ਰਿਤੀ_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_ਮੰਜ਼ਿਲ_ਸਮ੍ਰਿਤੀ_INFO_EXT,
            .region_ਗਿਣਤੀ = 1,
            .pRegions = &region_info,
        };
        ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
            ਪੂਰਨ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ਚੌੜਾਈ, swf->ਉਚਾਈ, i);

            region_info.p_Host_ਸੂਚਕ = swf->ਅੰਕੜੇ[i];
            region_info.ਸਮ੍ਰਿਤੀ_ਪੰਕਤੀ_ਲੰਮਾਈ = swf->linesize[i] / desc->comp[i].ਕਦਮ;
            region_info.imageSubresource.aspect_ਨਕਾਬ = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_Image_ਮੰਜ਼ਿਲ_ਸਮ੍ਰਿਤੀ_EXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_ਚੌਖਟਾ(hwfc, hwf_vk);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_ਚੌਖਟਾ(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 ਪੂਰਨ upload)
{
    ਪੂਰਨ err;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    AVVulkan_ਚੌਖਟੇ_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ਪੂਰਨ host_mapped = 0;

    AVVk_ਚੌਖਟਾ *hwf_vk = (AVVk_ਚੌਖਟਾ *)hwf->ਅੰਕੜੇ[0];
    Vk_ਬਫਰ_Image_Copy region[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ]; // always one per plane

    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(swf->format);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ਅਚਲ ਪੂਰਨ nb_images = ff_vk_ਗਿਣਤੀ_images(hwf_vk);

    Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 img_bar[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ nb_img_bar = 0;

    FFVk_ਬਫਰ *bufs[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
    ਪੂਰਨ nb_bufs = 0;

    Vk_Command_ਬਫਰ cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    ਜੇ ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (swf->ਚੌੜਾਈ > hwfc->ਚੌੜਾਈ || swf->ਉਚਾਈ > hwfc->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਪੂਰਨ host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT;
    ਪੂਰਨ host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_ਸਮ੍ਰਿਤੀ &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
        ਜੇ (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    ਜੇ (!upload && host_copy) {
        ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
            ਪੂਰਨ compat = 0;
            ਲਈ (ਪੂਰਨ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ਗਿਣਤੀ; j++) {
                ਜੇ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    ਰੋਕੋ;
                }
            }
            ਜੇ (!compat) {
                host_copy = 0;
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (host_copy)
        ਵਾਪਸ vulkan_transfer_host(hwfc, hwf, swf, upload);

    ਲਈ (ਪੂਰਨ i = 0; i < av_pix_fmt_ਗਿਣਤੀ_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->ਚੌੜਾਈ, swf->ਉਚਾਈ, i);

        /* Buffer region for this plane */
        region[i] = (Vk_ਬਫਰ_Image_Copy) {
            .ਬਫਰ_ਵਿੱਥ = 0,
            .ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ = FFABS(swf->linesize[i]),
            .ਬਫਰ_Image_ਉਚਾਈ = p_h,
            .imageSubresource.layer_ਗਿਣਤੀ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    ਜੇ (host_map) {
        err = host_map_ਚੌਖਟਾ(hwfc, bufs, &nb_bufs, swf, region, upload);
        ਜੇ (err >= 0)
            host_mapped = 1;
    }

    ਜੇ (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        ਜੇ (err < 0)
            ਜਾਓ ਸਿਰਾ;
        nb_bufs = 1;

        ਜੇ (upload) {
            err = copy_ਬਫਰ_ਅੰਕੜੇ(hwfc, bufs[0], swf, region, planes, 1);
            ਜੇ (err < 0)
                ਜਾਓ ਸਿਰਾ;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_ਸ਼ੁਰੂ(&p->vkctx, exec);
    ਜੇ (err < 0)
        ਜਾਓ ਸਿਰਾ;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_ਜੋੜੋ_dep_ਚੌਖਟਾ(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                                   VK_PIPELINE_STAGE_2_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ);
    ਜੇ (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        ਜਾਓ ਸਿਰਾ;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    ਜੇ (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        ਜੇ (host_mapped) {
            err = ff_vk_exec_ਜੋੜੋ_dep_sw_ਚੌਖਟਾ(&p->vkctx, exec, swf);
            ਜੇ (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                ਜਾਓ ਸਿਰਾ;
            }
        }

        /* Add the buffers as a dependency */
        ਲਈ (ਪੂਰਨ i = 0; i < nb_bufs; i++)
            ff_vk_exec_ਜੋੜੋ_dep_refstruct(&p->vkctx, exec, bufs[i]);
    }

    ff_vk_ਚੌਖਟਾ_barrier(&p->vkctx, exec, hwf, img_bar, &nb_img_bar,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ,
                        VK_PIPELINE_STAGE_2_TRANSFER_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
                        upload ? VK_ACCESS_TRANSFER_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ :
                                 VK_ACCESS_TRANSFER_READ_ਦੋਆਧਾਰੀ_ਅੰਕ,
                        upload ? VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                        p->nb_img_qfs > 1 ? VK_ਕਤਾਰ_FAMILY_IGNORED : p->img_qfs[0]);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_ਸਮ੍ਰਿਤੀ_Barriers = img_bar,
            .image_ਸਮ੍ਰਿਤੀ_Barrier_ਗਿਣਤੀ = nb_img_bar,
    });

    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        ਪੂਰਨ buf_idx = FFMIN(i, (nb_bufs - 1));
        ਪੂਰਨ img_idx = FFMIN(i, (nb_images - 1));
        FFVk_ਬਫਰ *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ;
        region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ /= desc->comp[i].ਕਦਮ;
        region[i].imageSubresource.aspect_ਨਕਾਬ = ff_vk_aspect_flag(hwf, i);

        ਜੇ (upload)
            vk->Cmd_Copy_ਬਫਰ_ਮੰਜ਼ਿਲ_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        ਨਹੀਂਤਾਂ
            vk->Cmd_Copy_Image_ਮੰਜ਼ਿਲ_ਬਫਰ(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].ਬਫਰ_ਪੰਕਤੀ_ਲੰਮਾਈ = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ਜੇ (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        ਜੇ (!host_mapped)
            err = copy_ਬਫਰ_ਅੰਕੜੇ(hwfc, bufs[0], swf, region, planes, 0);
    }

ਸਿਰਾ:
    ਲਈ (ਪੂਰਨ i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ਅਚਲ AVFrame *src)
{
    av_ਅਣਵਰਤਿਆ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ਚੋਣ (src->format) {
#ਜੇ CONFIG_CUDA
    ਹਾਲਤ AV_PIX_FMT_CUDA:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ਸਮ੍ਰਿਤੀ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ਨਹੀਂਤਾਂ
        ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ਸਮ੍ਰਿਤੀ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#ਜੇ_ਅੰਤ
            ਵਾਪਸ vulkan_transfer_ਅੰਕੜੇ_from_cuda(hwfc, dst, src);
        av_fallthrough;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਜੇ (src->hw_ਚੌਖਟੇ_ctx)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ vulkan_transfer_ਚੌਖਟਾ(hwfc, (AVFrame *)src, dst, 1);
    }
}

#ਜੇ CONFIG_CUDA
ਸਥਿਰ ਪੂਰਨ vulkan_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ err;
    CUcontext dummy;
    AVVk_ਚੌਖਟਾ *dst_f;
    AVVk_ਚੌਖਟਾ_ਅੰਦਰੂਨੀ *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_ਚੌਖਟੇ_Priv *fp = hwfc->hwctx;
    ਅਚਲ ਪੂਰਨ planes = av_pix_fmt_ਗਿਣਤੀ_planes(hwfc->sw_format);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ਪੂਰਨ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_ਅੰਦਰੂਨੀ *cu_ਅੰਦਰੂਨੀ = cuda_dev->ਅੰਦਰੂਨੀ;
    CudaFunctions *cu = cu_ਅੰਦਰੂਨੀ->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] = { 0 };

    dst_f = (AVVk_ਚੌਖਟਾ *)src->ਅੰਕੜੇ[0];
    nb_images = ff_vk_ਗਿਣਤੀ_images(dst_f);

    err = prepare_ਚੌਖਟਾ(hwfc, &fp->upload_exec, dst_f, PREP_ਬਹੁਲਕ_EXTERNAL_EXPORT);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    err = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(cuda_dev->cuda_ctx));
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    err = vulkan_export_ਮੰਜ਼ਿਲ_cuda(hwfc, dst->hw_ਚੌਖਟੇ_ctx, src);
    ਜੇ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
        ਵਾਪਸ err;
    }

    dst_int = dst_f->ਅੰਦਰੂਨੀ;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ਮੁੱਲ = dst_f->sem_ਮੁੱਲ[i] + 0;
        s_s_par[i].params.fence.ਮੁੱਲ = dst_f->sem_ਮੁੱਲ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ਧਾਰਾ));
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dst_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->ਅੰਕੜੇ[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .src_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        ਪੂਰਨ w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->ਚੌੜਾਈ, hwfc->ਉਚਾਈ, i);

        cpy.ਚੌੜਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ = w * desc->comp[i].ਕਦਮ;
        cpy.ਉਚਾਈ_2 = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ਧਾਰਾ));
        ਜੇ (err < 0)
            ਜਾਓ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ਧਾਰਾ));
    ਜੇ (err < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_images; i++)
        dst_f->sem_ਮੁੱਲ[i]++;

    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    ਵਾਪਸ prepare_ਚੌਖਟਾ(hwfc, &fp->upload_exec, dst_f, PREP_ਬਹੁਲਕ_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    vulkan_free_ਅੰਦਰੂਨੀ(p, dst_f);
    av_ਬਫਰ_unref(&dst->buf[0]);
    ਵਾਪਸ err;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ vulkan_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ਅਚਲ AVFrame *src)
{
    av_ਅਣਵਰਤਿਆ VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ਚੋਣ (dst->format) {
#ਜੇ CONFIG_CUDA
    ਹਾਲਤ AV_PIX_FMT_CUDA:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
        ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_ਸਮ੍ਰਿਤੀ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ਨਹੀਂਤਾਂ
        ਜੇ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_ਸਮ੍ਰਿਤੀ) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#ਜੇ_ਅੰਤ
            ਵਾਪਸ vulkan_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ_cuda(hwfc, dst, src);
        av_fallthrough;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਜੇ (dst->hw_ਚੌਖਟੇ_ctx)
            ਵਾਪਸ AVERROR(ENOSYS);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ vulkan_transfer_ਚੌਖਟਾ(hwfc, dst, (AVFrame *)src, 0);
    }
}

ਸਥਿਰ ਪੂਰਨ vulkan_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ਪੂਰਨ flags)
{
    ਵਾਪਸ vulkan_ਚੌਖਟੇ_init(dst_fc);
}

AVVk_ਚੌਖਟਾ *av_vk_ਚੌਖਟਾ_alloc(ਖਾਲੀ)
{
    ਪੂਰਨ err;
    AVVk_ਚੌਖਟਾ *f = av_mallocz(ਆਕਾਰ(AVVk_ਚੌਖਟਾ));
    ਜੇ (!f)
        ਵਾਪਸ ਨਿਰਾ;

    f->ਅੰਦਰੂਨੀ = av_mallocz(ਆਕਾਰ(*f->ਅੰਦਰੂਨੀ));
    ਜੇ (!f->ਅੰਦਰੂਨੀ) {
        av_free(f);
        ਵਾਪਸ ਨਿਰਾ;
    }

    err = pthread_mutex_init(&f->ਅੰਦਰੂਨੀ->update_mutex, ਨਿਰਾ);
    ਜੇ (err != 0) {
        av_free(f->ਅੰਦਰੂਨੀ);
        av_free(f);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ f;
}

ਅਚਲ HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_ਮਾਪ      = ਆਕਾਰ(VulkanDevicePriv),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ      = ਆਕਾਰ(Vulkan_ਚੌਖਟੇ_Priv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .ਚੌਖਟੇ_get_constraints = &vulkan_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init            = vulkan_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_get_ਬਫਰ      = vulkan_get_ਬਫਰ,
    .ਚੌਖਟੇ_uninit          = vulkan_ਚੌਖਟੇ_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ       = vulkan_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from     = vulkan_transfer_ਅੰਕੜੇ_from,

    .map_ਮੰਜ਼ਿਲ                 = vulkan_map_ਮੰਜ਼ਿਲ,
    .map_from               = vulkan_map_from,
    .ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ       = &vulkan_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
