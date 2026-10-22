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

#وصف_ڪريو VK_NO_PROTOTYPES
#وصف_ڪريو VK_ENABLE_BETA_EXTENSIONS

#جيڪڏهن_وصف_ٿيل _WIN32
#ضمن <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#ضمن <versionhelpers.h>
#ضمن "compat/w32dlfcn.h"
#وإلا
#ضمن <dlfcn.h>
#ضمن <unistd.h>
#جيڪڏهن_پورو

#ضمن "thread.h"

#ضمن "config.h"
#ضمن "pixdesc.h"
#ضمن "avstring.h"
#ضمن "imgutils.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_vulkan.h"
#ضمن "mem.h"
#ضمن "uuid.h"

#ضمن "vulkan.h"
#ضمن "vulkan_loader.h"

#إذا CONFIG_VAAPI
#ضمن "hwcontext_vaapi.h"
#جيڪڏهن_پورو

#إذا CONFIG_LIBDRM
#إذا CONFIG_VAAPI
#ضمن <va/va_drmcommon.h>
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __linux__
#ضمن <sys/sysmacros.h>
#جيڪڏهن_پورو
#ضمن <sys/stat.h>
#ضمن <xf86drm.h>
#ضمن <drm_fourcc.h>
#ضمن "hwcontext_drm.h"
#جيڪڏهن_پورو

#إذا HAVE_LINUX_DMA_BUF_H
#ضمن <sys/ioctl.h>
#ضمن <linux/dma-buf.h>
#جيڪڏهن_پورو

#إذا CONFIG_CUDA
#ضمن "hwcontext_cuda_internal.h"
#ضمن "cuda_check.h"
#وصف_ڪريو CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#جيڪڏهن_پورو

تعريفنوع بنية VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    Vk_Physical_Device_Workgroup_يادگيري_Explicit_Layout_Features_KHR explicit_mem_layout;

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    Vk_Physical_Device_Shader_Long_ويڪٽر_Features_EXT long_ويڪٽر;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_zero_initialize_device_يادگيري
    Vk_Physical_Device_Zero_Initialize_Device_يادگيري_Features_EXT zero_initialize;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#جيڪڏهن_پورو

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#جيڪڏهن_وصف_ٿيل VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#جيڪڏهن_پورو

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    Vk_Physical_Device_Cooperative_ميٽرڪس_Features_KHR cooperative_ميٽرڪس;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR اندروني_قطار_sync;
#جيڪڏهن_پورو
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

تعريفنوع بنية VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    فراغ *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkan_Device_قطار_Family *compute_qf;
    AVVulkan_Device_قطار_Family *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    Vk_Physical_Device_يادگيري_Properties mprops;
    Vk_Physical_Device_External_يادگيري_Host_Properties_EXT hprops;
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
    صحيح use_لڪيري_images;

    /* Option to allocate all image planes in a single allocation */
    صحيح contiguous_planes;

    /* Disable multiplane images */
    صحيح disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    صحيح avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    صحيح transfer_وٿي_align;

    /* Maximum queues */
    صحيح حد_بندي_queues;
} VulkanDevicePriv;

تعريفنوع بنية Vulkan_چوکٺا_Priv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkan_چوکٺا_Context p;

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
    صحيح export_requires_dedicated;
} Vulkan_چوکٺا_Priv;

تعريفنوع بنية AVVk_چوکٺو_اندروني {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#إذا CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternal_يادگيري ext_mem[AV_انگ_معلومات_اشارا];
    CUmipmappedArray cu_mma[AV_انگ_معلومات_اشارا];
    CUarray cu_array[AV_انگ_معلومات_اشارا];
    CUexternalSemaphore cu_sem[AV_انگ_معلومات_اشارا];
#جيڪڏهن_وصف_ٿيل _WIN32
    HANDLE ext_mem_handle[AV_انگ_معلومات_اشارا];
    HANDLE ext_sem_handle[AV_انگ_معلومات_اشارا];
#جيڪڏهن_پورو
#جيڪڏهن_پورو
} AVVk_چوکٺو_اندروني;

/* Initialize all structs in VulkanDeviceFeatures */
ساكن فراغ device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_ويڪٽر, FF_VK_EXT_LONG_ويڪٽر,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_ويڪٽر_FEATURES_EXT);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_zero_initialize_device_يادگيري
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_يادگيري_FEATURES_EXT);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#جيڪڏهن_پورو

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#جيڪڏهن_وصف_ٿيل VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#جيڪڏهن_پورو

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_ميٽرڪس, FF_VK_EXT_COOP_ميٽرڪس,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_ميٽرڪس_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_يادگيري_EXPLICIT_LAYOUT_FEATURES_KHR);

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->اندروني_قطار_sync, FF_VK_EXT_اندروني_قطار_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#جيڪڏهن_پورو

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
ساكن فراغ device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#وصف_ڪريو COPY_VAL(VAL)        \
    افعل {                     \
        dst->VAL = src->VAL; \
    } طالما (0)              \

    COPY_VAL(device.features.shaderImageGatherExtended);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);
    COPY_VAL(device.features.fragmentStoresAndAtomics);
    COPY_VAL(device.features.راس_Pipeline_Stores_And_Atomics);
    COPY_VAL(device.features.shaderInt64);
    COPY_VAL(device.features.shaderInt16);
    COPY_VAL(device.features.shaderFloat64);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);

    COPY_VAL(vulkan_1_1.samplerYcbcrConversion);
    COPY_VAL(vulkan_1_1.storage_ڌڪو_Constant16);
    COPY_VAL(vulkan_1_1.storage_Buffer16_ٻٽو_انگ_Access);
    COPY_VAL(vulkan_1_1.هڪجهڙو_And_Storage_Buffer16_ٻٽو_انگ_Access);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalar_بلاڪ_Layout);
    COPY_VAL(vulkan_1_2.بفر_Device_پتو);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_ڌڪو_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storage_Buffer8_ٻٽو_انگ_Access);
    COPY_VAL(vulkan_1_2.هڪجهڙو_And_Storage_Buffer8_ٻٽو_انگ_Access);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_بفر_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkan_يادگيري_Model);
    COPY_VAL(vulkan_1_2.vulkan_يادگيري_Model_Device_Scope);
    COPY_VAL(vulkan_1_2.vulkan_يادگيري_Model_Availability_Visibility_Chains);
    COPY_VAL(vulkan_1_2.هڪجهڙو_بفر_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_هڪجهڙو_بفر_Array_Non_هڪجهڙو_Indexing);
    COPY_VAL(vulkan_1_2.shader_Sampled_Image_Array_Non_هڪجهڙو_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_بفر_Array_Non_هڪجهڙو_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_Image_Array_Non_هڪجهڙو_Indexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.compute_ڀريل_Subgroups);
    COPY_VAL(vulkan_1_3.subgroup_سائيز_Control);
    COPY_VAL(vulkan_1_3.shader_Zero_Initialize_Workgroup_يادگيري);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    COPY_VAL(long_ويڪٽر.long_ويڪٽر_2);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_EXT_zero_initialize_device_يادگيري
    COPY_VAL(zero_initialize.zero_Initialize_Device_يادگيري);
#جيڪڏهن_پورو

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#جيڪڏهن_وصف_ٿيل VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#جيڪڏهن_پورو

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_ميٽرڪس.cooperative_ميٽرڪس_2);

    COPY_VAL(atomic_float.shader_بفر_Float32_Atomics);
    COPY_VAL(atomic_float.shader_بفر_Float32_Atomic_جوڙيو);

    COPY_VAL(explicit_mem_layout.workgroup_يادگيري_Explicit_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_يادگيري_Explicit_Layout_Scalar_بلاڪ_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_يادگيري_Explicit_Layout8_ٻٽو_انگ_Access);
    COPY_VAL(explicit_mem_layout.workgroup_يادگيري_Explicit_Layout16_ٻٽو_انگ_Access);

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    COPY_VAL(اندروني_قطار_sync.internallySynchronizedQueues);
#جيڪڏهن_پورو

    COPY_VAL(optical_flow.opticalFlow);

#وصف_رد COPY_VAL
}

#وصف_ڪريو ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_ٻٽو_انگ | VK_IMAGE_ASPECT_PLANE_1_ٻٽو_انگ)
#وصف_ڪريو ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_ٻٽو_انگ | VK_IMAGE_ASPECT_PLANE_1_ٻٽو_انگ | VK_IMAGE_ASPECT_PLANE_2_ٻٽو_انگ)

ساكن ثابت بنية FFVk_Format_داخلا {
    VkFormat vkf;
    تعداد AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    صحيح vk_planes;
    صحيح nb_images;
    صحيح nb_images_fallback;
    ثابت VkFormat fallback[5];
} vk_formats_list[] = {
    /* Gray formats */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GRAY8,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY10,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY12,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY14,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GRAY32,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GRAYF32, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32_SFLOAT } },

    /* RGB formats */
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGRA,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGBA,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8_UNORM,             AV_PIX_FMT_RGB24,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8_UNORM             } },
    { VK_FORMAT_B8G8R8_UNORM,             AV_PIX_FMT_BGR24,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_B8G8R8_UNORM             } },
    { VK_FORMAT_R16G16B16_UNORM,          AV_PIX_FMT_RGB48,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16_UNORM          } },
    { VK_FORMAT_R16G16B16A16_UNORM,       AV_PIX_FMT_RGBA64,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM       } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGR0,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGB0,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, AV_PIX_FMT_X2RGB10, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_A2B10G10R10_UNORM_PACK32, AV_PIX_FMT_X2BGR10, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_A2B10G10R10_UNORM_PACK32 } },
    { VK_FORMAT_R32G32B32_SFLOAT,         AV_PIX_FMT_RGBF32,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32G32B32_SFLOAT         } },
    { VK_FORMAT_R16G16B16A16_SFLOAT,      AV_PIX_FMT_RGBAF16, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_SFLOAT      } },
    { VK_FORMAT_R32G32B32A32_SFLOAT,      AV_PIX_FMT_RGBAF32, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32G32B32A32_SFLOAT      } },
    { VK_FORMAT_R32G32B32_UINT,           AV_PIX_FMT_RGB96,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32G32B32_UINT           } },
    { VK_FORMAT_R32G32B32A32_UINT,        AV_PIX_FMT_RGBA128, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R32G32B32A32_UINT        } },

    /* Planar RGB */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRP,     VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP10,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP12,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP14,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP16,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRPF16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT  } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRPF32,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* XYZ */
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_XYZP12,   VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar RGB + Alpha */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRAP,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP10,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP12,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP14,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRAPF16, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GBRAP32,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRAPF32, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* Bayer */
    { VK_FORMAT_R16_UNORM, AV_PIX_FMT_BAYER_RGGB16, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16_UNORM } },

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
    { VK_FORMAT_G8B8G8R8_422_UNORM,                     AV_PIX_FMT_YUYV422, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_B8G8R8G8_422_UNORM,                     AV_PIX_FMT_UYVY422, VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, AV_PIX_FMT_Y210,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, AV_PIX_FMT_Y212,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G16B16G16R16_422_UNORM,                 AV_PIX_FMT_Y216,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },

    /* Planar YUVA 420 at 8, 10 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA420P,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P10,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA422P,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P10,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P12,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA444P,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P10,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P12,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P16,  VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Single plane 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32,               AV_PIX_FMT_XV30,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,     AV_PIX_FMT_XV36,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_R16G16B16A16_UNORM,                     AV_PIX_FMT_XV48,    VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
};
ساكن ثابت صحيح nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ثابت VkFormat *av_vkfmt_from_pixfmt(تعداد AVPixelFormat p)
{
    لكل (صحيح i = 0; i < nb_vk_formats_list; i++)
        إذا (vk_formats_list[i].pixfmt == p)
            أرجع vk_formats_list[i].fallback;
    أرجع عدم;
}

ساكن ثابت بنية FFVk_Format_داخلا *vk_ڳوليو_format_داخلا(تعداد AVPixelFormat p)
{
    لكل (صحيح i = 0; i < nb_vk_formats_list; i++)
        إذا (vk_formats_list[i].pixfmt == p)
            أرجع &vk_formats_list[i];
    أرجع عدم;
}

ساكن صحيح vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, تعداد AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_انگ_معلومات_اشارا], /* Output format list */
                              صحيح *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              صحيح disable_multiplane, صحيح need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ثابت VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_ٻٽو_انگ |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_ٻٽو_انگ  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_ٻٽو_انگ;

    لكل (صحيح i = 0; i < nb_vk_formats_list; i++) {
        إذا (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ايندڙ = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            صحيح basics_primary = 0, basics_secondary = 0;
            صحيح storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_لڪيري ?
                             fprops.لڪيري_Tiling_Features : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ٻٽو_انگ);

            إذا (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_لڪيري ?
                                  fprops.لڪيري_Tiling_Features : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_ٻٽو_انگ);
            } وإلا {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            إذا (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                إذا (fmts) {
                    إذا (vk_formats_list[i].nb_images > 1) {
                        لكل (صحيح j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } وإلا {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                إذا (nb_images)
                    *nb_images = 1;
                إذا (aspect)
                    *aspect = vk_formats_list[i].aspect;
                إذا (supported_usage)
                    *supported_usage = ff_vk_map_feats_منزل_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ : 0);
                أرجع 0;
            } وإلا إذا (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                إذا (fmts) {
                    لكل (صحيح j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                إذا (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                إذا (aspect)
                    *aspect = vk_formats_list[i].aspect;
                إذا (supported_usage)
                    *supported_usage = ff_vk_map_feats_منزل_usage(feats_secondary);
                أرجع 0;
            } وإلا {
                أرجع AVERROR(ENOTSUP);
            }
        }
    }

    أرجع AVERROR(EINVAL);
}

#إذا CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ثابت حرف *pName);
#جيڪڏهن_پورو

ساكن صحيح ڀريو_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#إذا CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#وإلا
    ساكن ثابت حرف *lib_نالا[] = {
#إذا defined(_WIN32)
        "vulkan-1.dll",
#وإلاإذا defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#وإلا
        "libvulkan.so.1",
        "libvulkan.so",
#جيڪڏهن_پورو
    };

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(lib_نالا); i++) {
        p->libvulkan = dlopen(lib_نالا[i], RTLD_NOW | RTLD_LOCAL);
        إذا (p->libvulkan)
            اكسر;
    }

    إذا (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        أرجع AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#جيڪڏهن_پورو /* CONFIG_VULKAN_STATIC */

    أرجع 0;
}

تعريفنوع بنية VulkanOptExtension {
    ثابت حرف *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

ساكن ثابت VulkanOptExtension optional_instance_exts[] = {
#جيڪڏهن_وصف_ٿيل __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#جيڪڏهن_پورو
    { 0 },
};

ساكن ثابت VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_ڌڪو_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_ڌڪو_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_ميٽرڪس_EXTENSION_NAME,               FF_VK_EXT_COOP_ميٽرڪس            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_يادگيري_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#جيڪڏهن_وصف_ٿيل VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    { VK_EXT_SHADER_LONG_ويڪٽر_EXTENSION_NAME,               FF_VK_EXT_LONG_ويڪٽر            },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_EXT_zero_initialize_device_يادگيري
    { VK_EXT_ZERO_INITIALIZE_DEVICE_يادگيري_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#جيڪڏهن_پورو
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#جيڪڏهن_وصف_ٿيل VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_اندروني_قطار_SYNC    },
#جيڪڏهن_پورو
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_يادگيري_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_يادگيري     },
    { VK_EXT_EXTERNAL_يادگيري_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_يادگيري },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_يادگيري_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_يادگيري   },
#جيڪڏهن_وصف_ٿيل _WIN32
    { VK_KHR_EXTERNAL_يادگيري_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_يادگيري  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#جيڪڏهن_پورو

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_قطار_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_قطار            },
    { VK_KHR_VIDEO_ENCODE_قطار_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_قطار     },
    { VK_KHR_VIDEO_DECODE_قطار_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_قطار     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#جيڪڏهن_وصف_ٿيل VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#جيڪڏهن_پورو
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

ثابت حرف **av_vk_get_optional_instance_extensions(صحيح *ڳڻپ)
{
    ثابت حرف **exts = av_malloc_array(حجم(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    إذا (!exts)
        أرجع عدم;

    لكل (صحيح i = 0; i < (صحيح)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *ڳڻپ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    أرجع exts;
}

ثابت حرف **av_vk_get_optional_device_extensions(صحيح *ڳڻپ)
{
    ثابت حرف **exts = av_malloc_array(حجم(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    إذا (!exts)
        أرجع عدم;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *ڳڻپ = FF_ARRAY_ELEMS(optional_device_exts);
    أرجع exts;
}

ساكن VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(Vk_Debug_Utils_پيغام_Severity_Flag_بٽ_EXT severity,
                                    Vk_Debug_Utils_پيغام_Type_Flags_EXT پيغام_Type,
                                    ثابت Vk_Debug_Utils_Messenger_Callback_معلومات_EXT *معلومات,
                                    فراغ *priv)
{
    صحيح l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    بدل (معلومات->پيغام_Id_عدد) {
    حالة 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    حالة 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        أرجع VK_FALSE;
    افتراضي:
        اكسر;
    }

    بدل (severity) {
    حالة VK_DEBUG_UTILS_پيغام_SEVERITY_VERBOSE_ٻٽو_انگ_EXT: l = AV_LOG_VERBOSE; اكسر;
    حالة VK_DEBUG_UTILS_پيغام_SEVERITY_INFO_ٻٽو_انگ_EXT:    l = AV_LOG_INFO;    اكسر;
    حالة VK_DEBUG_UTILS_پيغام_SEVERITY_WARNING_ٻٽو_انگ_EXT: l = AV_LOG_WARNING; اكسر;
    حالة VK_DEBUG_UTILS_پيغام_SEVERITY_ERROR_ٻٽو_انگ_EXT:   l = AV_LOG_ERROR;   اكسر;
    افتراضي:                                              l = AV_LOG_DEBUG;   اكسر;
    }

    av_log(ctx, l, "%s\n", معلومات->p_پيغام);
    لكل (صحيح i = 0; i < معلومات->cmd_Buf_Label_ڳڻپ; i++)
        av_log(ctx, l, "\t%i: %s\n", i, معلومات->pCmdBufLabels[i].pLabelName);

    أرجع VK_FALSE;
}

#وصف_ڪريو جوڙيو_VAL_منزل_LIST(list, ڳڻپ, val)                                      \
    افعل {                                                                       \
        list = av_realloc_array(list, ++ڳڻپ, حجم(*list));                 \
        إذا (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            اذهب fail;                                                         \
        }                                                                      \
        list[ڳڻپ - 1] = av_strdup(val);                                      \
        إذا (!list[ڳڻپ - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            اذهب fail;                                                         \
        }                                                                      \
    } طالما(0)

#وصف_ڪريو RELEASE_PROPS(props, ڳڻپ)                                            \
    إذا (props) {                                                               \
        لكل (صحيح i = 0; i < ڳڻپ; i++)                                        \
            av_free((فراغ *)((props)[i]));                                     \
        av_free((فراغ *)props);                                                \
    }

ساكن صحيح vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_سائيز max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.يادگيري_Type_ڳڻپ);
    لكل (صحيح i = 0; i < p->mprops.يادگيري_Type_ڳڻپ; i++) {
        ثابت Vk_يادگيري_Type type = p->mprops.يادگيري_Types[i];
        ثابت Vk_يادگيري_ڍير ڍير = p->mprops.يادگيري_Heaps[type.ڍير_اشاريو_2];
        إذا (!(type.propertyFlags & VK_يادگيري_PROPERTY_DEVICE_LOCAL_ٻٽو_انگ))
            استمر;
        max_vram = FFMAX(max_vram, ڍير.سائيز);
        إذا (type.propertyFlags & VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ)
            max_visible_vram = FFMAX(max_visible_vram, ڍير.سائيز);
    }

    أرجع max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

تعداد FFVulkan_Debug_گهڻائي {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

ساكن صحيح check_extensions(AVHWDeviceContext *ctx, صحيح dev, AVDictionary *opts,
                            ثابت حرف * ثابت **dst, uint32_t *انگ,
                            تعداد FFVulkan_Debug_گهڻائي debug_گهڻائي)
{
    ثابت حرف *tstr;
    ثابت حرف **extension_نالا = عدم;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    صحيح err = 0, مليو, extensions_مليو = 0;

    ثابت حرف *mod;
    صحيح optional_exts_انگ;
    uint32_t sup_ext_ڳڻپ;
    حرف *user_exts_str = عدم;
    AVDictionary_داخلا *user_exts;
    VkExtensionProperties *sup_ext;
    ثابت VulkanOptExtension *optional_exts;

    إذا (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_انگ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", عدم, 0);
        إذا (user_exts) {
            user_exts_str = av_strdup(user_exts->قدر);
            إذا (!user_exts_str) {
                err = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(عدم, &sup_ext_ڳڻپ, عدم);
        sup_ext = av_malloc_array(sup_ext_ڳڻپ, حجم(VkExtensionProperties));
        إذا (!sup_ext)
            أرجع AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(عدم, &sup_ext_ڳڻپ, sup_ext);
    } وإلا {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_انگ = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", عدم, 0);
        إذا (user_exts) {
            user_exts_str = av_strdup(user_exts->قدر);
            إذا (!user_exts_str) {
                err = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, عدم,
                                               &sup_ext_ڳڻپ, عدم);
        sup_ext = av_malloc_array(sup_ext_ڳڻپ, حجم(VkExtensionProperties));
        إذا (!sup_ext)
            أرجع AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, عدم,
                                               &sup_ext_ڳڻپ, sup_ext);
    }

    لكل (صحيح i = 0; i < optional_exts_انگ; i++) {
        tstr = optional_exts[i].name;
        مليو = 0;

        /* Check if the device has ReBAR for host image copies */
        إذا (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            استمر;

        إذا (dev &&
            ((debug_گهڻائي == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_گهڻائي == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_گهڻائي == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            استمر;
        }

        لكل (صحيح j = 0; j < sup_ext_ڳڻپ; j++) {
            إذا (!strcmp(tstr, sup_ext[j].extensionName)) {
                مليو = 1;
                اكسر;
            }
        }
        إذا (!مليو)
            استمر;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        جوڙيو_VAL_منزل_LIST(extension_نالا, extensions_مليو, tstr);
    }

    إذا (!dev &&
        ((debug_گهڻائي == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_گهڻائي == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_گهڻائي == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        مليو = 0;
        لكل (صحيح j = 0; j < sup_ext_ڳڻپ; j++) {
            إذا (!strcmp(tstr, sup_ext[j].extensionName)) {
                مليو = 1;
                اكسر;
            }
        }
        إذا (مليو) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            جوڙيو_VAL_منزل_LIST(extension_نالا, extensions_مليو, tstr);
        } وإلا {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            اذهب fail;
        }
    }

#جيڪڏهن_وصف_ٿيل VK_KHR_shader_relaxed_extended_instruction
    إذا ((debug_گهڻائي == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        مليو = 0;
        لكل (صحيح j = 0; j < sup_ext_ڳڻپ; j++) {
            إذا (!strcmp(tstr, sup_ext[j].extensionName)) {
                مليو = 1;
                اكسر;
            }
        }
        إذا (!مليو) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            اذهب fail;
        }
    }
#جيڪڏهن_پورو

    إذا (user_exts_str) {
        حرف *save, *token = av_strtok(user_exts_str, "+", &save);
        طالما (token) {
            مليو = 0;
            لكل (صحيح j = 0; j < sup_ext_ڳڻپ; j++) {
                إذا (!strcmp(token, sup_ext[j].extensionName)) {
                    مليو = 1;
                    اكسر;
                }
            }
            إذا (مليو) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                جوڙيو_VAL_منزل_LIST(extension_نالا, extensions_مليو, token);
            } وإلا {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(عدم, "+", &save);
        }
    }

    *dst = extension_نالا;
    *انگ = extensions_مليو;

    av_free(user_exts_str);
    av_free(sup_ext);
    أرجع 0;

fail:
    RELEASE_PROPS(extension_نالا, extensions_مليو);
    av_free(user_exts_str);
    av_free(sup_ext);
    أرجع err;
}

ساكن صحيح check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ثابت حرف * ثابت **dst, uint32_t *انگ,
                        تعداد FFVulkan_Debug_گهڻائي *debug_گهڻائي)
{
    صحيح err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ساكن ثابت حرف layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    صحيح layer_standard_validation_مليو = 0;

    uint32_t sup_layer_ڳڻپ;
    VkLayerProperties *sup_layers;

    AVDictionary_داخلا *user_layers = av_dict_get(opts, "layers", عدم, 0);
    حرف *user_layers_str = عدم;
    حرف *save, *token;

    ثابت حرف **enabled_layers = عدم;
    uint32_t enabled_layers_ڳڻپ = 0;

    AVDictionary_داخلا *debug_opt = av_dict_get(opts, "debug", عدم, 0);
    تعداد FFVulkan_Debug_گهڻائي گهڻائي;

    *debug_گهڻائي = گهڻائي = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_ڳڻپ, عدم);
    sup_layers = av_malloc_array(sup_layer_ڳڻپ, حجم(VkLayerProperties));
    إذا (!sup_layers)
        أرجع AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_ڳڻپ, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    لكل (صحيح i = 0; i < sup_layer_ڳڻپ; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    إذا (!debug_opt && !user_layers)
        اذهب پڇاڙي;

    /* Check for any properly supported validation layer */
    إذا (debug_opt) {
        إذا (!strcmp(debug_opt->قدر, "printf")) {
            گهڻائي = FF_VULKAN_DEBUG_PRINTF;
        } وإلا إذا (!strcmp(debug_opt->قدر, "validate")) {
            گهڻائي = FF_VULKAN_DEBUG_VALIDATE;
        } وإلا إذا (!strcmp(debug_opt->قدر, "practices")) {
            گهڻائي = FF_VULKAN_DEBUG_PRACTICES;
        } وإلا {
            حرف *پڇاڙي_ptr = عدم;
            صحيح idx = strtol(debug_opt->قدر, &پڇاڙي_ptr, 10);
            إذا (پڇاڙي_ptr == debug_opt->قدر || پڇاڙي_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->قدر);
                err = AVERROR(EINVAL);
                اذهب پڇاڙي;
            }
            گهڻائي = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    إذا ((گهڻائي == FF_VULKAN_DEBUG_VALIDATE) ||
        (گهڻائي == FF_VULKAN_DEBUG_PRINTF) ||
        (گهڻائي == FF_VULKAN_DEBUG_PRACTICES)) {
        لكل (صحيح i = 0; i < sup_layer_ڳڻپ; i++) {
            إذا (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                جوڙيو_VAL_منزل_LIST(enabled_layers, enabled_layers_ڳڻپ, layer_standard_validation);
                *debug_گهڻائي = گهڻائي;
                layer_standard_validation_مليو = 1;
                اكسر;
            }
        }
        إذا (!layer_standard_validation_مليو) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            اذهب پڇاڙي;
        }
    }

    /* Process any custom layers enabled */
    إذا (user_layers) {
        صحيح مليو;

        user_layers_str = av_strdup(user_layers->قدر);
        إذا (!user_layers_str) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        طالما (token) {
            مليو = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            إذا (!strcmp(layer_standard_validation, token) && layer_standard_validation_مليو) {
                token = av_strtok(عدم, "+", &save);
                اكسر;
            }

            /* Try to find the layer in the list of supported layers */
            لكل (صحيح j = 0; j < sup_layer_ڳڻپ; j++) {
                إذا (!strcmp(token, sup_layers[j].layerName)) {
                    مليو = 1;
                    اكسر;
                }
            }

            إذا (مليو) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                جوڙيو_VAL_منزل_LIST(enabled_layers, enabled_layers_ڳڻپ, token);

                /* If debug was not set as an option, force it */
                إذا (!strcmp(layer_standard_validation, token))
                    *debug_گهڻائي = FF_VULKAN_DEBUG_VALIDATE;
            } وإلا {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                اذهب پڇاڙي;
            }

            token = av_strtok(عدم, "+", &save);
        }
    }

fail:
پڇاڙي:
    av_free(sup_layers);
    av_free(user_layers_str);

    إذا (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_ڳڻپ);
    } وإلا {
        *dst = enabled_layers;
        *انگ = enabled_layers_ڳڻپ;
    }

    أرجع err;
}

/* Creates a VkInstance */
ساكن صحيح create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           تعداد FFVulkan_Debug_گهڻائي *debug_گهڻائي)
{
    صحيح err = 0;
    Vk_نتيجو ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .application_نسخو_2 = VK_MAKE_نسخو(LIBAVUTIL_نسخو_MAJOR,
                                              LIBAVUTIL_نسخو_MINOR,
                                              LIBAVUTIL_نسخو_MICRO),
        .pEngineName        = "libavutil",
        .api_نسخو         = VK_API_نسخو_1_3,
        .engine_نسخو      = VK_MAKE_نسخو(LIBAVUTIL_نسخو_MAJOR,
                                              LIBAVUTIL_نسخو_MINOR,
                                              LIBAVUTIL_نسخو_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    إذا (!hwctx->get_proc_addr) {
        err = ڀريو_libvulkan(ctx);
        إذا (err < 0)
            أرجع err;
    }

    err = ff_vk_ڀريو_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        أرجع err;
    }

    err = check_layers(ctx, opts, &inst_props.pp_Enabled_Layer_نالا,
                       &inst_props.enabled_Layer_ڳڻپ, debug_گهڻائي);
    إذا (err)
        اذهب fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.pp_Enabled_Extension_نالا,
                           &inst_props.enabled_Extension_ڳڻپ, *debug_گهڻائي);
    hwctx->enabled_inst_extensions = inst_props.pp_Enabled_Extension_نالا;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_ڳڻپ;
    إذا (err < 0)
        اذهب fail;

    /* Enable debug features if needed */
    إذا (*debug_گهڻائي == FF_VULKAN_DEBUG_VALIDATE) {
        ساكن ثابت VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_جڳهه_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_ڳڻپ = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_ايندڙ = &validation_features;
    } وإلا إذا (*debug_گهڻائي == FF_VULKAN_DEBUG_PRINTF) {
        ساكن ثابت VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_جڳهه_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_ڳڻپ = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_ايندڙ = &validation_features;
    } وإلا إذا (*debug_گهڻائي == FF_VULKAN_DEBUG_PRACTICES) {
        ساكن ثابت VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_بهترين_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_ڳڻپ = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_ايندڙ = &validation_features;
    }

#جيڪڏهن_وصف_ٿيل __APPLE__
    لكل (صحيح i = 0; i < inst_props.enabled_Extension_ڳڻپ; i++) {
        إذا (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.pp_Enabled_Extension_نالا[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_ٻٽو_انگ_KHR;
            اكسر;
        }
    }
#جيڪڏهن_پورو

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        اذهب fail;
    }

    err = ff_vk_ڀريو_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        اذهب fail;
    }

    /* Setup debugging callback if needed */
    إذا ((*debug_گهڻائي == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_گهڻائي == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_گهڻائي == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .پيغام_Severity = VK_DEBUG_UTILS_پيغام_SEVERITY_VERBOSE_ٻٽو_انگ_EXT |
                               VK_DEBUG_UTILS_پيغام_SEVERITY_INFO_ٻٽو_انگ_EXT    |
                               VK_DEBUG_UTILS_پيغام_SEVERITY_WARNING_ٻٽو_انگ_EXT |
                               VK_DEBUG_UTILS_پيغام_SEVERITY_ERROR_ٻٽو_انگ_EXT,
            .پيغام_Type = VK_DEBUG_UTILS_پيغام_TYPE_GENERAL_ٻٽو_انگ_EXT    |
                           VK_DEBUG_UTILS_پيغام_TYPE_VALIDATION_ٻٽو_انگ_EXT |
                           VK_DEBUG_UTILS_پيغام_TYPE_PERFORMANCE_ٻٽو_انگ_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .p_User_معلومات = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.pp_Enabled_Layer_نالا, inst_props.enabled_Layer_ڳڻپ);
    أرجع err;
}

تعريفنوع بنية VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_سائيز]; /* Will use this first unless !has_uuid */
    صحيح has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ثابت حرف *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    صحيح اشاريو; /* Finally fall back to index */
} VulkanDeviceSelection;

ساكن ثابت حرف *vk_dev_type(تعداد VkPhysicalDeviceType type)
{
    بدل (type) {
    حالة VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: أرجع "integrated";
    حالة VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   أرجع "discrete";
    حالة VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    أرجع "virtual";
    حالة VK_PHYSICAL_DEVICE_TYPE_CPU:            أرجع "software";
    افتراضي:                                     أرجع "unknown";
    }
}

/* Finds a device */
ساكن صحيح ڳوليو_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    صحيح err = 0, choice = -1;
    uint32_t انگ;
    Vk_نتيجو ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = عدم;
    VkPhysicalDeviceIDProperties *idp = عدم;
    VkPhysicalDeviceProperties2 *prop = عدم;
    VkPhysicalDeviceDriverProperties *driver_prop = عدم;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = عدم;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &انگ, عدم);
    إذا (ret != VK_SUCCESS || !انگ) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        أرجع AVERROR(ENODEV);
    }

    devices = av_malloc_array(انگ, حجم(VkPhysicalDevice));
    إذا (!devices)
        أرجع AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &انگ, devices);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    }

    prop = av_calloc(انگ, حجم(*prop));
    إذا (!prop) {
        err = AVERROR(ENOMEM);
        اذهب پڇاڙي;
    }

    idp = av_calloc(انگ, حجم(*idp));
    إذا (!idp) {
        err = AVERROR(ENOMEM);
        اذهب پڇاڙي;
    }

    driver_prop = av_calloc(انگ, حجم(*driver_prop));
    إذا (!driver_prop) {
        err = AVERROR(ENOMEM);
        اذهب پڇاڙي;
    }

    إذا (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(انگ, حجم(*drm_prop));
        إذا (!drm_prop) {
            err = AVERROR(ENOMEM);
            اذهب پڇاڙي;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    لكل (صحيح i = 0; i < انگ; i++) {
        إذا (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].p_ايندڙ = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].p_ايندڙ = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].p_ايندڙ = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    إذا (select->has_uuid) {
        لكل (صحيح i = 0; i < انگ; i++) {
            إذا (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_سائيز)) {
                choice = i;
                اذهب پڇاڙي;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    } وإلا إذا ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        لكل (صحيح i = 0; i < انگ; i++) {
            إذا ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                اذهب پڇاڙي;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    } وإلا إذا (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        لكل (صحيح i = 0; i < انگ; i++) {
            إذا (لڙي_ڳولا(prop[i].properties.deviceName, select->name)) {
                choice = i;
                اذهب پڇاڙي;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    } وإلا إذا (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        لكل (صحيح i = 0; i < انگ; i++) {
            إذا (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                اذهب پڇاڙي;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        اذهب پڇاڙي;
    } وإلا إذا (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        لكل (صحيح i = 0; i < انگ; i++) {
            إذا (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                اذهب پڇاڙي;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    } وإلا {
        إذا (select->اشاريو < انگ) {
            choice = select->اشاريو;
            اذهب پڇاڙي;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->اشاريو);
        err = AVERROR(ENODEV);
        اذهب پڇاڙي;
    }

پڇاڙي:
    إذا (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_ايندڙ = عدم;
        p->dprops = driver_prop[choice];
        p->dprops.p_ايندڙ = عدم;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    أرجع err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
ساكن مضمن صحيح pick_قطار_family(Vk_قطار_Family_Properties2 *qf, uint32_t انگ_qf,
                                    Vk_قطار_Flag_بٽ flags)
{
    صحيح اشاريو = -1;
    uint32_t min_score = UINT32_MAX;

    لكل (صحيح i = 0; i < انگ_qf; i++) {
        Vk_قطار_Flag_بٽ qflags = qf[i].قطار_Family_Properties.قطار_Flags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        إذا ((flags & VK_قطار_TRANSFER_ٻٽو_انگ) &&
            (qflags & (VK_قطار_GRAPHICS_ٻٽو_انگ | VK_قطار_COMPUTE_ٻٽو_انگ)))
            qflags |= VK_قطار_TRANSFER_ٻٽو_انگ;

        إذا (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].قطار_Family_Properties.timestamp_Valid_بٽ;
            إذا (score < min_score) {
                اشاريو = i;
                min_score = score;
            }
        }
    }

    إذا (اشاريو > -1)
        qf[اشاريو].قطار_Family_Properties.timestamp_Valid_بٽ++;

    أرجع اشاريو;
}

ساكن مضمن صحيح pick_video_قطار_family(Vk_قطار_Family_Properties2 *qf,
                                          Vk_قطار_Family_Video_Properties_KHR *qf_vid, uint32_t انگ_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    صحيح اشاريو = -1;
    uint32_t min_score = UINT32_MAX;

    لكل (صحيح i = 0; i < انگ_qf; i++) {
        ثابت Vk_قطار_Flags qflags = qf[i].قطار_Family_Properties.قطار_Flags;
        ثابت VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        إذا (!(qflags & (VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR | VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR)))
            استمر;

        إذا (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].قطار_Family_Properties.timestamp_Valid_بٽ;
            إذا (score < min_score) {
                اشاريو = i;
                min_score = score;
            }
        }
    }

    إذا (اشاريو > -1)
        qf[اشاريو].قطار_Family_Properties.timestamp_Valid_بٽ++;

    أرجع اشاريو;
}

ساكن صحيح تياري_قطار_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t انگ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    Vk_قطار_Family_Properties2 *qf = عدم;
    Vk_قطار_Family_Video_Properties_KHR *qf_vid = عدم;

    /* First get the number of queue families */
    vk->Get_Physical_Device_قطار_Family_Properties(hwctx->phys_dev, &انگ, عدم);
    إذا (!انگ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        أرجع AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(انگ, حجم(Vk_قطار_Family_Properties2));
    إذا (!qf)
        أرجع AVERROR(ENOMEM);

    qf_vid = av_malloc_array(انگ, حجم(Vk_قطار_Family_Video_Properties_KHR));
    إذا (!qf_vid)
        أرجع AVERROR(ENOMEM);

    لكل (uint32_t i = 0; i < انگ; i++) {
        qf_vid[i] = (Vk_قطار_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_قطار_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_PROPERTIES_2,
            .p_ايندڙ = p->vkctx.extensions & FF_VK_EXT_VIDEO_قطار ? &qf_vid[i] : عدم,
        };
    }

    /* Finally retrieve the queue families */
    vk->Get_Physical_Device_قطار_Family_Properties2(hwctx->phys_dev, &انگ, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    لكل (صحيح i = 0; i < انگ; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_GRAPHICS_ٻٽو_انگ) ? " graphics" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_COMPUTE_ٻٽو_انگ) ? " compute" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_TRANSFER_ٻٽو_انگ) ? " transfer" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR) ? " encode" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR) ? " decode" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_SPARSE_BINDING_ٻٽو_انگ) ? " sparse" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_OPTICAL_FLOW_ٻٽو_انگ_NV) ? " optical_flow" : "",
               ((qf[i].قطار_Family_Properties.قطار_Flags) & VK_قطار_PROTECTED_ٻٽو_انگ) ? " protected" : "",
               qf[i].قطار_Family_Properties.قطار_ڳڻپ);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].قطار_Family_Properties.timestamp_Valid_بٽ = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->قطار_flags = 0;
#جيڪڏهن_وصف_ٿيل VK_KHR_internally_synchronized_queues
    إذا (p->vkctx.extensions & FF_VK_EXT_اندروني_قطار_SYNC)
        hwctx->قطار_flags |= VK_DEVICE_قطار_CREATE_INTERNALLY_SYNCHRONIZED_ٻٽو_انگ_KHR;
#جيڪڏهن_پورو

    /* Pick each queue family to use. */
#وصف_ڪريو PICK_QF(type, vid_op)                                            \
    افعل {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        إذا (vid_op)                                                      \
            idx = pick_video_قطار_family(qf, qf_vid, انگ, vid_op);      \
        وإلا                                                             \
            idx = pick_قطار_family(qf, انگ, type);                      \
                                                                         \
        إذا (idx == -1)                                                   \
            استمر;                                                    \
                                                                         \
        لكل (i = 0; i < hwctx->nb_qf; i++) {                             \
            إذا (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                اكسر;                                                   \
            }                                                            \
        }                                                                \
        إذا (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].انگ = qf[idx].قطار_Family_Properties.قطار_ڳڻپ; \
            إذا (p->حد_بندي_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                صحيح max = p->حد_بندي_queues;                               \
                إذا (type == VK_قطار_GRAPHICS_ٻٽو_انگ)                       \
                    hwctx->qf[i].انگ = FFMIN(hwctx->qf[i].انگ,           \
                                             max ? max : 1);             \
                وإلا إذا (max)                                            \
                    hwctx->qf[i].انگ = FFMIN(hwctx->qf[i].انگ, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } طالما (0)

    PICK_QF(VK_قطار_GRAPHICS_ٻٽو_انگ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_قطار_COMPUTE_ٻٽو_انگ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_قطار_TRANSFER_ٻٽو_انگ, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_ٻٽو_انگ_KHR);
    PICK_QF(VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_ٻٽو_انگ_KHR);

    PICK_QF(VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_ٻٽو_انگ_KHR);
    PICK_QF(VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_ٻٽو_انگ_KHR);

#جيڪڏهن_وصف_ٿيل VK_KHR_video_decode_vp9
    PICK_QF(VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_ٻٽو_انگ_KHR);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل VK_KHR_video_encode_av1
    PICK_QF(VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_ٻٽو_انگ_KHR);
#جيڪڏهن_پورو
    PICK_QF(VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_ٻٽو_انگ_KHR);

    إذا (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_قطار_OPTICAL_FLOW_ٻٽو_انگ_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#وصف_رد PICK_QF

    cd->p_قطار_Create_Infos = av_malloc_array(hwctx->nb_qf,
                                            حجم(Vk_Device_قطار_Create_Info));
    إذا (!cd->p_قطار_Create_Infos)
        أرجع AVERROR(ENOMEM);

    لكل (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        صحيح dup = 0;
        عائم *weights = عدم;
        Vk_Device_قطار_Create_Info *pc;
        لكل (uint32_t j = 0; j < cd->قطار_Create_Info_ڳڻپ; j++) {
            إذا (hwctx->qf[i].idx == cd->p_قطار_Create_Infos[j].قطار_Family_اشاريو) {
                dup = 1;
                اكسر;
            }
        }
        إذا (dup)
            استمر;

        weights = av_malloc_array(hwctx->qf[i].انگ, حجم(عائم));
        إذا (!weights) {
            لكل (uint32_t j = 0; j < cd->قطار_Create_Info_ڳڻپ; j++)
                av_free((فراغ *)cd->p_قطار_Create_Infos[i].p_قطار_Priorities);
            av_free((فراغ *)cd->p_قطار_Create_Infos);
            أرجع AVERROR(ENOMEM);
        }

        لكل (uint32_t j = 0; j < hwctx->qf[i].انگ; j++)
            weights[j] = 1.0;

        pc = (Vk_Device_قطار_Create_Info *)cd->p_قطار_Create_Infos;
        pc[cd->قطار_Create_Info_ڳڻپ++] = (Vk_Device_قطار_Create_Info) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_قطار_CREATE_INFO,
            .flags = hwctx->قطار_flags,
            .قطار_Family_اشاريو = hwctx->qf[i].idx,
            .قطار_ڳڻپ = hwctx->qf[i].انگ,
            .p_قطار_Priorities = weights,
        };
    }

    أرجع 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
ساكن فراغ vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    إذا (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    إذا (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    إذا (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    إذا (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

ساكن فراغ vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    إذا (p->qf_mutex) {
        لكل (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

ساكن صحيح vulkan_device_create_اندروني(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         صحيح disable_multiplane,
                                         AVDictionary *opts, صحيح flags)
{
    صحيح err = 0;
    Vk_نتيجو ret;
    AVDictionary_داخلا *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    تعداد FFVulkan_Debug_گهڻائي debug_گهڻائي = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    إذا ((err = create_instance(ctx, opts, &debug_گهڻائي)))
        اذهب پڇاڙي;

    /* Find a physical device (if not given one) */
    إذا ((err = ڳوليو_device(ctx, dev_select)))
        اذهب پڇاڙي;

    /* Get supported memory types */
    vk->Get_Physical_Device_يادگيري_Properties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    إذا ((err = check_extensions(ctx, 1, opts, &dev_info.pp_Enabled_Extension_نالا,
                                &dev_info.enabled_Extension_ڳڻپ, debug_گهڻائي))) {
        لكل (صحيح i = 0; i < dev_info.قطار_Create_Info_ڳڻپ; i++)
            av_free((فراغ *)dev_info.p_قطار_Create_Infos[i].p_قطار_Priorities);
        av_free((فراغ *)dev_info.p_قطار_Create_Infos);
        اذهب پڇاڙي;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.p_ايندڙ = p->feats.device.p_ايندڙ;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", عدم, 0);
    إذا (opt_d)
        p->حد_بندي_queues = strtol(opt_d->قدر, عدم, 10);

    /* Setup enabled queue families */
    إذا ((err = تياري_قطار_families(ctx, &dev_info)))
        اذهب پڇاڙي;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    لكل (صحيح i = 0; i < dev_info.قطار_Create_Info_ڳڻپ; i++)
        av_free((فراغ *)dev_info.p_قطار_Create_Infos[i].p_قطار_Priorities);
    av_free((فراغ *)dev_info.p_قطار_Create_Infos);

    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        لكل (صحيح i = 0; i < dev_info.enabled_Extension_ڳڻپ; i++)
            av_free((فراغ *)dev_info.pp_Enabled_Extension_نالا[i]);
        av_free((فراغ *)dev_info.pp_Enabled_Extension_نالا);
        err = AVERROR_EXTERNAL;
        اذهب پڇاڙي;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", عدم, 0);
    إذا (opt_d)
        p->use_لڪيري_images = strtol(opt_d->قدر, عدم, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    إذا (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", عدم, 0);
        إذا (opt_d)
            p->disable_multiplane = strtol(opt_d->قدر, عدم, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", عدم, 0);
    إذا (opt_d)
        p->avoid_host_import = strtol(opt_d->قدر, عدم, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.pp_Enabled_Extension_نالا;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_ڳڻپ;

    /* The extension lists need to be freed */
    ctx->حرر = vulkan_device_free;

پڇاڙي:
    أرجع err;
}

ساكن فراغ تالو_قطار(AVHWDeviceContext *ctx, uint32_t قطار_family, uint32_t اشاريو)
{
    VulkanDevicePriv *p = ctx->hwctx;
    إذا (p->qf_mutex)
        pthread_mutex_تالو(&p->qf_mutex[قطار_family][اشاريو]);
}

ساكن فراغ unlock_قطار(AVHWDeviceContext *ctx, uint32_t قطار_family, uint32_t اشاريو)
{
    VulkanDevicePriv *p = ctx->hwctx;
    إذا (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[قطار_family][اشاريو]);
}

ساكن صحيح vulkan_device_init(AVHWDeviceContext *ctx)
{
    صحيح err = 0;
    uint32_t qf_انگ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_قطار_Family_Properties2 *qf;
    Vk_قطار_Family_Video_Properties_KHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    لكل (صحيح i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        لكل (صحيح j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            إذا (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                اكسر;
            }
        }
    }

    err = ff_vk_ڀريو_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        أرجع err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_ايندڙ = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_يادگيري_HOST_PROPERTIES_EXT;
    p->hprops.p_ايندڙ = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_بفر_Copy_صف_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.min_يادگيري_Map_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_سائيز);
    إذا (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_يادگيري)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.min_Imported_Host_اشارو_Alignment);

    vk->Get_Physical_Device_قطار_Family_Properties(hwctx->phys_dev, &qf_انگ, عدم);
    إذا (!qf_انگ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        أرجع AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#جيڪڏهن_وصف_ٿيل _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ٻٽو_انگ
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ٻٽو_انگ;
#وإلا
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ٻٽو_انگ;
#جيڪڏهن_پورو
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_انگ, حجم(Vk_قطار_Family_Properties2));
    إذا (!qf)
        أرجع AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_انگ, حجم(Vk_قطار_Family_Video_Properties_KHR));
    إذا (!qf_vid) {
        av_free(qf);
        أرجع AVERROR(ENOMEM);
    }

    لكل (uint32_t i = 0; i < qf_انگ; i++) {
        qf_vid[i] = (Vk_قطار_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_قطار_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_قطار_FAMILY_PROPERTIES_2,
            .p_ايندڙ = p->vkctx.extensions & FF_VK_EXT_VIDEO_قطار ? &qf_vid[i] : عدم,
        };
    }

    vk->Get_Physical_Device_قطار_Family_Properties2(hwctx->phys_dev, &qf_انگ, qf);

    p->nb_tot_qfs = qf_انگ;

    إذا (!(p->vkctx.extensions & FF_VK_EXT_اندروني_قطار_SYNC)) {
        p->qf_mutex = av_calloc(qf_انگ, حجم(*p->qf_mutex));
        إذا (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            اذهب پڇاڙي;
        }

        لكل (uint32_t i = 0; i < qf_انگ; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].قطار_Family_Properties.قطار_ڳڻپ,
                                       حجم(**p->qf_mutex));
            إذا (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                اذهب پڇاڙي;
            }
            لكل (uint32_t j = 0; j < qf[i].قطار_Family_Properties.قطار_ڳڻپ; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], عدم);
                إذا (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    اذهب پڇاڙي;
                }
            }
        }
    }

    لكل (صحيح i = 0; i < hwctx->nb_qf; i++) {
        إذا (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_قطار_VIDEO_DECODE_ٻٽو_انگ_KHR |
                                  VK_قطار_VIDEO_ENCODE_ٻٽو_انگ_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    لكل (صحيح i = 0; i < hwctx->nb_qf; i++) {
        صحيح ڏٺل = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        لكل (صحيح j = (i - 1); j >= 0; j--) {
            إذا (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                ڏٺل = 1;
                اكسر;
            }
        }
        إذا (!ڏٺل)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#إذا FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    إذا (!hwctx->تالو_قطار)
        hwctx->تالو_قطار = تالو_قطار;
    إذا (!hwctx->unlock_قطار)
        hwctx->unlock_قطار = unlock_قطار;
FF_ENABLE_DEPRECATION_WARNINGS
#جيڪڏهن_پورو

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_يادگيري_Properties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_ڀريو_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_ڳوليو(&p->vkctx, VK_قطار_COMPUTE_ٻٽو_انگ, 0);
    p->transfer_qf = ff_vk_qf_ڳوليو(&p->vkctx, VK_قطار_TRANSFER_ٻٽو_انگ, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_وٿي_align = 1;
    إذا (p->transfer_qf) {
        Vk_قطار_Flags flags = p->vkctx.qf_props[p->transfer_qf->idx].قطار_Family_Properties.قطار_Flags;
        إذا (!(flags & (VK_قطار_GRAPHICS_ٻٽو_انگ | VK_قطار_COMPUTE_ٻٽو_انگ)))
            p->transfer_وٿي_align = 4;
    }
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    إذا (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_وٿي_align = 1;
#جيڪڏهن_پورو

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_يادگيري_Properties(hwctx->phys_dev, &p->mprops);

پڇاڙي:
    av_free(qf_vid);
    av_free(qf);
    أرجع err;
}

ساكن صحيح vulkan_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                                AVDictionary *opts, صحيح flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    إذا (device && device[0]) {
        حرف *پڇاڙي = عدم;

        إذا (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } وإلا {
            dev_select.اشاريو = strtol(device, &پڇاڙي, 10);
            إذا (پڇاڙي == device || *پڇاڙي) {
                dev_select.اشاريو = 0;
                dev_select.name  = device;
            }
        }
    }

    أرجع vulkan_device_create_اندروني(ctx, &dev_select, 0, opts, flags);
}

ساكن صحيح vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, صحيح flags)
{
    av_اڻ_استعمال_ٿيل VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    بدل(src_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#إذا VA_CHECK_نسخو(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#جيڪڏهن_پورو
        ثابت حرف *vendor;

#إذا VA_CHECK_نسخو(1, 15, 0)
        vas = va_Get_Display_خاصيتون(dpy, &attr, 1);
        إذا (vas == VA_حالت_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.قدر & 0xFFFF);
#جيڪڏهن_پورو

        إذا (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            إذا (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                أرجع AVERROR_EXTERNAL;
            }

            إذا (لڙي_ڳولا(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        أرجع vulkan_device_create_اندروني(ctx, &dev_select, 0, opts, flags);
    }
#جيڪڏهن_پورو
#إذا CONFIG_LIBDRM
    حالة AV_HWDEVICE_TYPE_DRM: {
        صحيح err;
        بنية stat drm_ڳنڍ_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ڳنڍ_info);
        إذا (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            أرجع AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ڳنڍ_info.st_dev);
        dev_select.drm_minor = minor(drm_ڳنڍ_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        إذا (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            أرجع AVERROR_EXTERNAL;
        }

        إذا (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        أرجع vulkan_device_create_اندروني(ctx, &dev_select, 0, opts, flags);
    }
#جيڪڏهن_پورو
#إذا CONFIG_CUDA
    حالة AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADevice_Context_اندروني *cu_اندروني = src_hwctx->اندروني;
        CudaFunctions *cu = cu_اندروني->cuda_dl;

        صحيح ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_اندروني->cuda_device));
        إذا (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            أرجع AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        أرجع vulkan_device_create_اندروني(ctx, &dev_select, 1, opts, flags);
    }
#جيڪڏهن_پورو
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }
}

ساكن صحيح vulkan_چوکٺا_get_constraints(AVHWDeviceContext *ctx,
                                         ثابت فراغ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    صحيح ڳڻپ = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    لكل (تعداد AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ڳڻپ += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_لڪيري_images ? VK_IMAGE_TILING_لڪيري :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    عدم, عدم, عدم, عدم, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(ڳڻپ + 1 + CONFIG_CUDA,
                                                    حجم(تعداد AVPixelFormat));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    ڳڻپ = 0;
    لكل (تعداد AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        إذا (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_لڪيري_images ? VK_IMAGE_TILING_لڪيري :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               عدم, عدم, عدم, عدم, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[ڳڻپ++] = vk_formats_list[i].pixfmt;
        }
    }

#إذا CONFIG_CUDA
    constraints->valid_sw_formats[ڳڻپ++] = AV_PIX_FMT_CUDA;
#جيڪڏهن_پورو

    constraints->valid_sw_formats[ڳڻپ++] = AV_PIX_FMT_NONE;

    constraints->min_ويڪر  = 1;
    constraints->min_اوچائي = 1;
    constraints->max_ويڪر  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_اوچائي = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(تعداد AVPixelFormat));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن صحيح alloc_mem(AVHWDeviceContext *ctx, Vk_يادگيري_Requirements *req,
                     Vk_يادگيري_Property_Flag_بٽ req_flags, ثابت فراغ *alloc_extension,
                     Vk_يادگيري_Property_Flag_بٽ *mem_flags, Vk_Device_يادگيري *mem)
{
    Vk_نتيجو ret;
    صحيح اشاريو = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    Vk_يادگيري_Allocate_Info alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_يادگيري_ALLOCATE_INFO,
        .p_ايندڙ          = alloc_extension,
        .ورهاست_سائيز = req->سائيز,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    لكل (صحيح i = 0; i < p->mprops.يادگيري_Type_ڳڻپ; i++) {
        ثابت Vk_يادگيري_Type *type = &p->mprops.يادگيري_Types[i];

        /* The memory type must be supported by the requirements (bitfield) */
        إذا (!(req->يادگيري_Type_بٽ & (1 << i)))
            استمر;

        /* The memory type flags must include our properties */
        إذا ((type->propertyFlags & req_flags) != req_flags)
            استمر;

        /* The memory type must be large enough */
        إذا (req->سائيز > p->mprops.يادگيري_Heaps[type->ڍير_اشاريو_2].سائيز)
            استمر;

        /* Found a suitable memory type */
        اشاريو = i;
        اكسر;
    }

    إذا (اشاريو < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        أرجع AVERROR(EINVAL);
    }

    alloc_info.يادگيري_Type_اشاريو = اشاريو;

    ret = vk->Allocate_يادگيري(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.يادگيري_Types[اشاريو].propertyFlags;

    أرجع 0;
}

ساكن فراغ vulkan_free_اندروني(VulkanDevicePriv *p, AVVk_چوکٺو *f)
{
    av_اڻ_استعمال_ٿيل AVVk_چوکٺو_اندروني *اندروني = f->اندروني;

    // Make this function safe to call repeatedly
    إذا (!اندروني)
        أرجع;

#إذا CONFIG_CUDA
    إذا (اندروني->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)اندروني->cuda_fc_ref->معلومات;
        صحيح planes = av_pix_fmt_ڳڻپ_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADevice_Context_اندروني *cu_اندروني = cuda_dev->اندروني;
        CudaFunctions *cu = cu_اندروني->cuda_dl;

        لكل (صحيح i = 0; i < planes; i++) {
            إذا (اندروني->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(اندروني->cu_sem[i]));
            إذا (اندروني->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(اندروني->cu_mma[i]));
            إذا (اندروني->ext_mem[i])
                CHECK_CU(cu->cu_Destroy_External_يادگيري(اندروني->ext_mem[i]));
#جيڪڏهن_وصف_ٿيل _WIN32
            إذا (اندروني->ext_sem_handle[i])
                CloseHandle(اندروني->ext_sem_handle[i]);
            إذا (اندروني->ext_mem_handle[i])
                CloseHandle(اندروني->ext_mem_handle[i]);
#جيڪڏهن_پورو
        }

        av_بفر_unref(&اندروني->cuda_fc_ref);
    }
#جيڪڏهن_پورو

    إذا (اندروني->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, اندروني->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&اندروني->update_mutex);
    av_freep(&f->اندروني);
}

ساكن فراغ vulkan_چوکٺو_free(AVHWFramesContext *hwfc, AVVk_چوکٺو *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    صحيح nb_images = ff_vk_ڳڻپ_images(f);
    صحيح nb_sems = 0;

    طالما (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    إذا (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_قدرون        = f->sem_قدر,
            .semaphore_ڳڻپ = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_اندروني(p, f);

    لكل (صحيح i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->Free_يادگيري(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

ساكن فراغ vulkan_چوکٺو_free_cb(فراغ *opaque, uint8_t *معلومات)
{
    vulkan_چوکٺو_free(opaque, (AVVk_چوکٺو*)معلومات);
}

ساكن صحيح alloc_bind_mem(AVHWFramesContext *hwfc, AVVk_چوکٺو *f,
                          فراغ *alloc_pnext, size_t alloc_pnext_stride)
{
    صحيح img_cnt = 0, err;
    Vk_نتيجو ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Bind_Image_يادگيري_Info bind_info[AV_انگ_معلومات_اشارا] = { { 0 } };

    طالما (f->img[img_cnt]) {
        صحيح use_ded_mem;
        Vk_Image_يادگيري_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_يادگيري_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        Vk_يادگيري_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_ALLOCATE_INFO,
            .p_ايندڙ = (فراغ *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        Vk_يادگيري_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_REQUIREMENTS,
        };
        Vk_يادگيري_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_REQUIREMENTS_2,
            .p_ايندڙ = &ded_req,
        };

        vk->Get_Image_يادگيري_Requirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefers_Dedicated_ورهاست, ded_req.requires_Dedicated_ورهاست);

        إذا (f->tiling == VK_IMAGE_TILING_لڪيري)
            req.يادگيري_Requirements.سائيز = FFALIGN(req.يادگيري_Requirements.سائيز,
                                                  p->props.properties.limits.min_يادگيري_Map_Alignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefers_Dedicated_ورهاست |
                      ded_req.requires_Dedicated_ورهاست;
        إذا (((Vulkan_چوکٺا_Priv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        إذا (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        إذا ((err = alloc_mem(ctx, &req.يادگيري_Requirements,
                             f->tiling == VK_IMAGE_TILING_لڪيري ?
                             VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ :
                             VK_يادگيري_PROPERTY_DEVICE_LOCAL_ٻٽو_انگ,
                             use_ded_mem ? &ded_alloc : (فراغ *)ded_alloc.p_ايندڙ,
                             &f->flags, &f->mem[img_cnt])))
            أرجع err;

        f->سائيز[img_cnt] = req.يادگيري_Requirements.سائيز;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_يادگيري_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].يادگيري = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

تعداد Prep_گهڻائي {
    PREP_گهڻائي_GENERAL,
    PREP_گهڻائي_WRITE,
    PREP_گهڻائي_EXTERNAL_EXPORT,
    PREP_گهڻائي_EXTERNAL_IMPORT,
    PREP_گهڻائي_DECODING_DST,
    PREP_گهڻائي_DECODING_DPB,
    PREP_گهڻائي_ENCODING_DPB,
};

ساكن فراغ switch_new_props(تعداد Prep_گهڻائي pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    بدل (pmode) {
    حالة PREP_گهڻائي_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_يادگيري_READ_ٻٽو_انگ | VK_ACCESS_يادگيري_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_يادگيري_READ_ٻٽو_انگ | VK_ACCESS_يادگيري_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ٻٽو_انگ | VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ;
        اكسر;
    حالة PREP_گهڻائي_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_ٻٽو_انگ | VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ;
        اكسر;
    }
}

ساكن صحيح switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_چوکٺو *چوکٺو, تعداد Prep_گهڻائي pmode)
{
    صحيح err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Image_يادگيري_Barrier2 img_bar[AV_انگ_معلومات_اشارا];
    صحيح nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_قطار_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    إذا (pmode == PREP_گهڻائي_EXTERNAL_EXPORT) {
        dst_qf     = VK_قطار_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .معلومات = (uint8_t *)hwfc,
    };
    AVFrame tmp_چوکٺو = {
        .معلومات[0] = (uint8_t *)چوکٺو,
        .hw_چوکٺا_ctx = &tmp_ref,
    };

    Vk_Command_بفر cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_شروعات(&p->vkctx, exec);
    إذا (err < 0)
        أرجع err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_جوڙيو_dep_چوکٺو(&p->vkctx, exec, &tmp_چوکٺو,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ);
    إذا (err < 0)
        أرجع err;

    ff_vk_چوکٺو_barrier(&p->vkctx, exec, &tmp_چوکٺو, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_يادگيري_Barriers = img_bar,
            .image_يادگيري_Barrier_ڳڻپ = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    إذا (err < 0)
        أرجع err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    أرجع 0;
}

ساكن صحيح switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVk_چوکٺو *چوکٺو, تعداد Prep_گهڻائي pmode)
{
    Vk_نتيجو ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_انگ_معلومات_اشارا];
    صحيح nb_images = ff_vk_ڳڻپ_images(چوکٺو);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    صحيح i;
    لكل (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_ڳڻپ; i++) {
        إذا (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            اكسر;
    }
    إذا (i == p->vkctx.host_image_props.copy_Dst_Layout_ڳڻپ)
        أرجع AVERROR(ENOTSUP);

    لكل (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = چوکٺو->img[i],
            .oldLayout = چوکٺو->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspect_نقاب = VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ,
            .subresourceRange.layer_ڳڻپ = 1,
            .subresourceRange.level_ڳڻپ = 1,
        };
        چوکٺو->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    إذا (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح prepare_چوکٺو(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_چوکٺو *چوکٺو, تعداد Prep_گهڻائي pmode)
{
    صحيح err = 0;
    AVVulkan_چوکٺا_Context *hwfc_vk = hwfc->hwctx;
    إذا (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT &&
        (pmode != PREP_گهڻائي_EXTERNAL_EXPORT) &&
        (pmode != PREP_گهڻائي_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, چوکٺو, pmode);
        إذا (err != AVERROR(ENOTSUP))
            أرجع err;
    }

    أرجع switch_layout(hwfc, ectx, چوکٺو, pmode);
}

ساكن مضمن فراغ get_plane_wh(uint32_t *w, uint32_t *h, تعداد AVPixelFormat format,
                                صحيح چوکٺو_w, صحيح چوکٺو_h, صحيح plane)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    إذا (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = چوکٺو_w;
        *h = چوکٺو_h;
        أرجع;
    }

    *w = AV_CEIL_RSHIFT(چوکٺو_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(چوکٺو_h, desc->log2_chroma_h);
}

ساكن صحيح create_چوکٺو(AVHWFramesContext *hwfc, AVVk_چوکٺو **چوکٺو,
                        VkImageTiling tiling, Vk_Image_Usage_Flag_بٽ usage,
                        VkImageCreateFlags flags, صحيح nb_layers,
                        فراغ *create_pnext)
{
    صحيح err;
    Vk_نتيجو ret;
    AVVulkan_چوکٺا_Context *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVk_چوکٺو *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_قدر  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_ايندڙ = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#جيڪڏهن_وصف_ٿيل _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ٻٽو_انگ
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ٻٽو_انگ,
#وإلا
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ٻٽو_انگ,
#جيڪڏهن_پورو
    };

    /* Check if exporting is supported before chaining any structs */
    إذا (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_ٻٽو_انگ) {
        إذا (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_چوکٺو_alloc();
    إذا (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        أرجع AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    لكل (صحيح i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ايندڙ                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.اونهائي          = 1,
            .mip_سطحون             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_ڳڻپ_1_ٻٽو_انگ,
            .p_قطار_Family_Indices   = p->img_qfs,
            .قطار_Family_اشاريو_ڳڻپ = p->nb_img_qfs,
            .sharing_گهڻائي           = p->nb_img_qfs > 1 ? VK_SHARING_گهڻائي_CONCURRENT :
                                                         VK_SHARING_گهڻائي_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.ويڪر, &create_info.extent.اوچائي,
                     hwfc->sw_format, hwfc->ويڪر, hwfc->اوچائي, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            اذهب fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }

        f->قطار_family[i] = p->nb_img_qfs > 1 ? VK_قطار_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_قدر[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *چوکٺو = f;
    أرجع 0;

fail:
    vulkan_چوکٺو_free(hwfc, f);
    أرجع err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
ساكن فراغ try_export_flags(AVHWFramesContext *hwfc,
                             Vk_External_يادگيري_Handle_Type_Flags *comp_handle_types,
                             Vk_External_يادگيري_Handle_Type_Flags *iexp,
                             Vk_External_يادگيري_Handle_Type_Flag_بٽ قوت_نما)
{
    Vk_نتيجو ret;
    AVVulkan_چوکٺا_Context *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ثابت VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_ڳوليو_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    صحيح has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    صحيح nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_ايندڙ = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_ايندڙ = عدم,
        .p_قطار_Family_Indices   = p->img_qfs,
        .قطار_Family_اشاريو_ڳڻپ = p->nb_img_qfs,
        .sharing_گهڻائي           = p->nb_img_qfs > 1 ? VK_SHARING_گهڻائي_CONCURRENT :
                                                     VK_SHARING_گهڻائي_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = قوت_نما,
        .p_ايندڙ = has_mods ? &phy_dev_mod_info : عدم,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_ايندڙ  = !قوت_نما ? عدم : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_ٻٽو_انگ),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_ڳڻپ : 1;
    لكل (صحيح i = 0; i < nb_mods; i++) {
        إذا (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        إذا (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (بنانشان ڊگهو ڊگهو)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        إذا (ret == VK_SUCCESS) {
            *iexp |= قوت_نما;
            *comp_handle_types |= eprops.external_يادگيري_Properties.compatibleHandleTypes;
            إذا (قوت_نما == VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT) {
                Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.external_يادگيري_Properties.external_يادگيري_Features &
                                                  VK_EXTERNAL_يادگيري_FEATURE_DEDICATED_ONLY_ٻٽو_انگ);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
ساكن فراغ get_export_handle_types(AVHWFramesContext *hwfc,
                                    Vk_External_يادگيري_Handle_Type_Flags *comp_handle_types,
                                    Vk_External_يادگيري_Handle_Type_Flags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_اڻ_استعمال_ٿيل AVVulkan_چوکٺا_Context *hwctx = &((Vulkan_چوکٺا_Priv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#جيڪڏهن_وصف_ٿيل _WIN32
    إذا (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_يادگيري)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32_ٻٽو_انگ
                             : VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32_KMT_ٻٽو_انگ);
#وإلا
    إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_يادگيري) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_FD_ٻٽو_انگ);

    إذا (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_يادگيري &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT);
#جيڪڏهن_پورو
}

ساكن AVBufferRef *vulkan_pool_alloc(فراغ *opaque, size_t سائيز)
{
    صحيح err;
    AVVk_چوکٺو *f;
    AVBufferRef *avbuf = عدم;
    AVHWFramesContext *hwfc = opaque;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkan_چوکٺا_Context *hwctx = &fp->p;
    Vk_External_يادگيري_Handle_Type_Flags e;
    Vk_Export_يادگيري_Allocate_Info eminfo[AV_انگ_معلومات_اشارا];

    Vk_External_يادگيري_Image_Create_Info eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_يادگيري_IMAGE_CREATE_INFO,
        .p_ايندڙ       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    لكل (صحيح i = 0; i < av_pix_fmt_ڳڻپ_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_يادگيري_ALLOCATE_INFO;
        eminfo[i].p_ايندڙ       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_چوکٺو(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    إذا (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        أرجع عدم;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, حجم(*eminfo));
    إذا (err)
        اذهب fail;

    إذا ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ٻٽو_انگ_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR))
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_DECODING_DPB);
    وإلا إذا (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR)
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_DECODING_DST);
    وإلا إذا (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ٻٽو_انگ_KHR)
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_ENCODING_DPB);
    وإلا إذا (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_ٻٽو_انگ)
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_WRITE);
    وإلا
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_GENERAL);
    إذا (err)
        اذهب fail;

    avbuf = av_بفر_create((uint8_t *)f, حجم(AVVk_چوکٺو),
                             vulkan_چوکٺو_free_cb, hwfc, 0);
    إذا (!avbuf)
        اذهب fail;

    أرجع avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_چوکٺو_free(hwfc, f);
    أرجع عدم;
}

ساكن فراغ تالو_چوکٺو(AVHWFramesContext *fc, AVVk_چوکٺو *vkf)
{
    pthread_mutex_تالو(&vkf->اندروني->update_mutex);
}

ساكن فراغ unlock_چوکٺو(AVHWFramesContext *fc, AVVk_چوکٺو *vkf)
{
    pthread_mutex_unlock(&vkf->اندروني->update_mutex);
}

ساكن فراغ vulkan_چوکٺا_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;

    إذا (fp->modifier_info) {
        إذا (fp->modifier_info->pDrmFormatModifiers)
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
ساكن صحيح vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkan_چوکٺا_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_نتيجو ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    ثابت بنية FFVk_Format_داخلا *fmt = vk_ڳوليو_format_داخلا(hwfc->sw_format);
    إذا (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        أرجع 0;
    }

    ثابت VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_ڳوليو_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    صحيح has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_ڳڻپ;
    صحيح nb_mods = has_mods ? mod_list->drm_Format_Modifier_ڳڻپ : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    إذا (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        أرجع 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_قطار_Family_Indices   = p->img_qfs,
        .قطار_Family_اشاريو_ڳڻپ = p->nb_img_qfs,
        .sharing_گهڻائي           = p->nb_img_qfs > 1 ? VK_SHARING_گهڻائي_CONCURRENT :
                                                     VK_SHARING_گهڻائي_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    إذا (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ثابت VkVideoProfileListInfoKHR *pl =
        ff_vk_ڳوليو_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    إذا (pl) {
        profile_list = *pl;
        profile_list.p_ايندڙ = عدم;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ثابت VkImageFormatListCreateInfo *fl =
        ff_vk_ڳوليو_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    إذا (fl) {
        format_list = *fl;
        format_list.p_ايندڙ = عدم;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    لكل (صحيح i = 0; i < AV_انگ_معلومات_اشارا &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        لكل (صحيح j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_ايندڙ = &perf,
            };

            إذا (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            إذا (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                أرجع 0;
            }

            إذا (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identical_يادگيري_Layout);
                أرجع 0;
            }
        }
    }

    إذا (!p->vkctx.host_image_props.identical_يادگيري_Type_Requirements) {
        صحيح اشاريو;
        Vk_External_يادگيري_Handle_Type_Flags e;
        Vk_External_يادگيري_Image_Create_Info eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_يادگيري_IMAGE_CREATE_INFO,
            .p_ايندڙ       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ايندڙ       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->ويڪر, hwfc->اوچائي, 1 },
            .mip_سطحون   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_ڳڻپ_1_ٻٽو_انگ,
            .p_قطار_Family_Indices   = p->img_qfs,
            .قطار_Family_اشاريو_ڳڻپ = p->nb_img_qfs,
            .sharing_گهڻائي           = p->nb_img_qfs > 1 ? VK_SHARING_گهڻائي_CONCURRENT :
                                                         VK_SHARING_گهڻائي_EXCLUSIVE,
        };
        Vk_Device_Image_يادگيري_Requirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_يادگيري_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_يادگيري_PLANE_0_ٻٽو_انگ_EXT : 0,
        };
        Vk_يادگيري_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_REQUIREMENTS_2,
        };

        vk->Get_Device_Image_يادگيري_Requirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        Vk_يادگيري_Property_Flags req_flags = hwctx->tiling == VK_IMAGE_TILING_لڪيري ?
                                          VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ :
                                          VK_يادگيري_PROPERTY_DEVICE_LOCAL_ٻٽو_انگ;
        لكل (اشاريو = 0; اشاريو < p->mprops.يادگيري_Type_ڳڻپ; اشاريو++) {
            إذا (!(req.يادگيري_Requirements.يادگيري_Type_بٽ & (1U << اشاريو)))
                استمر;
            إذا ((p->mprops.يادگيري_Types[اشاريو].propertyFlags & req_flags) == req_flags)
                اكسر;
        }
        إذا (اشاريو == p->mprops.يادگيري_Type_ڳڻپ) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            أرجع 0;
        }
    }

    أرجع 1;
}

ساكن صحيح vulkan_چوکٺا_init(AVHWFramesContext *hwfc)
{
    صحيح err;
    AVVk_چوکٺو *f;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkan_چوکٺا_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ثابت بنية FFVk_Format_داخلا *fmt;
    ثابت AVPixFmtDescriptor *desc;
    صحيح disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_چوکٺو_FLAG_DISABLE_MULTIPLANE);
    صحيح is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_ٻٽو_انگ_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ٻٽو_انگ_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_ٻٽو_انگ_KHR)));

    /* Defaults */
    إذا (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    إذا (p->use_لڪيري_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_لڪيري;


    fmt = vk_ڳوليو_format_داخلا(hwfc->sw_format);
    إذا (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        أرجع AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    إذا ((hwfc->ويڪر  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->اوچائي & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    إذا (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        إذا (hwctx->format[0] != fmt->vkf) {
            لكل (صحيح i = 0; i < fmt->nb_images_fallback; i++) {
                إذا (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    أرجع AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, عدم,
                                 عدم, عدم, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ));
        إذا (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            أرجع AVERROR(EINVAL);
        }
    } وإلا {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, عدم,
                                 عدم, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ));
        إذا (err < 0)
            أرجع err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    صحيح drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_ڳوليو_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    إذا (!is_lone_dpb && !drm_mod_with_video) {
        /* Image usage flags */
        hwctx->usage |= supported_usage & (VK_IMAGE_USAGE_TRANSFER_DST_ٻٽو_انگ |
                                           VK_IMAGE_USAGE_TRANSFER_SRC_ٻٽو_انگ |
                                           VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ      |
                                           VK_IMAGE_USAGE_SAMPLED_ٻٽو_انگ);

        /* Frames which may double as active references (coinciding decode
         * output) cannot support host transfers: decode submissions bake the
         * image layout into their barriers at record time, so a host-side
         * layout transition cannot be synchronized against them, not even
         * by the frame lock and timeline semaphore. */
        إذا (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_ٻٽو_انگ_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        إذا ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_قطار) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        إذا (!hwctx->img_flags) {
            صحيح sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_ٻٽو_انگ |
                                             VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_ٻٽو_انگ;
            إذا (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_ٻٽو_انگ;
                إذا ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_ٻٽو_انگ;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    إذا ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_ٻٽو_انگ_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_قطار) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ثابت VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_ڳوليو_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        إذا (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ٻٽو_انگ_KHR;
        } وإلا {
            uint32_t i;
            لكل (i = 0; i < pl->profile_ڳڻپ; i++) {
                /* Video ops start at exactly 0x00010000 */
                إذا (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    اكسر;
            }
            إذا (i == pl->profile_ڳڻپ)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_ٻٽو_انگ_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    إذا ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT;

    إذا (!hwctx->تالو_چوکٺو)
        hwctx->تالو_چوکٺو = تالو_چوکٺو;

    إذا (!hwctx->unlock_چوکٺو)
        hwctx->unlock_چوکٺو = unlock_چوکٺو;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, عدم);
    إذا (err)
        أرجع err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, عدم);
    إذا (err)
        أرجع err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, عدم);
    إذا (err)
        أرجع err;

    /* Test to see if allocation will fail */
    err = create_چوکٺو(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    إذا (err)
        أرجع err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    إذا (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        إذا (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_چوکٺو_free(hwfc, f);
            أرجع AVERROR_EXTERNAL;
        }
        لكل (صحيح i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = عدم;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_ايندڙ = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_ڳڻپ, حجم(*modp.pDrmFormatModifierProperties));
            إذا (!modp.pDrmFormatModifierProperties) {
                vulkan_چوکٺو_free(hwfc, f);
                أرجع AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            لكل (uint32_t j = 0; j < modp.drm_Format_Modifier_ڳڻپ; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                إذا (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    اكسر;
                }
            }

            إذا (mod_props == عدم) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_چوکٺو_free(hwfc, f);
                أرجع AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_چوکٺو_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    إذا (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_اندروني = av_بفر_pool_init2(حجم(AVVk_چوکٺو),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  عدم);
        إذا (!ffhwframesctx(hwfc)->pool_اندروني)
            أرجع AVERROR(ENOMEM);
    }

    أرجع 0;
}

ساكن صحيح vulkan_get_بفر(AVHWFramesContext *hwfc, AVFrame *چوکٺو)
{
    چوکٺو->buf[0] = av_بفر_pool_get(hwfc->pool);
    إذا (!چوکٺو->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکٺو->معلومات[0] = چوکٺو->buf[0]->معلومات;
    چوکٺو->format  = AV_PIX_FMT_VULKAN;
    چوکٺو->ويڪر   = hwfc->ويڪر;
    چوکٺو->اوچائي  = hwfc->اوچائي;

    أرجع 0;
}

ساكن صحيح vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       تعداد AVHWFrameTransferDirection dir,
                                       تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;
    صحيح n = 2;

#إذا CONFIG_CUDA
    n++;
#جيڪڏهن_پورو
    fmts = av_malloc_array(n, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#إذا CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#جيڪڏهن_پورو
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    أرجع 0;
}

#إذا CONFIG_LIBDRM
ساكن فراغ vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_چوکٺو_free(hwfc, hwmap->priv);
}

ساكن ثابت بنية {
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
#جيڪڏهن_وصف_ٿيل DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#جيڪڏهن_پورو
};

ساكن مضمن VkFormat drm_منزل_vulkan_fmt(uint32_t drm_fourcc)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        إذا (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            أرجع vulkan_drm_format_map[i].vk_format;
    أرجع VK_FORMAT_UNDEFINED;
}

ساكن صحيح vulkan_map_from_drm_چوکٺو_desc(AVHWFramesContext *hwfc, AVVk_چوکٺو **چوکٺو,
                                          ثابت AVFrame *src, صحيح flags)
{
    صحيح err = 0;
    Vk_نتيجو ret;
    AVVk_چوکٺو *f;
    صحيح bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->معلومات[0];
    Vk_Bind_Image_يادگيري_Info bind_info[AV_DRM_MAX_PLANES];
    Vk_Bind_Image_Plane_يادگيري_Info plane_info[AV_DRM_MAX_PLANES];

    لكل (صحيح i = 0; i < desc->nb_layers; i++) {
        إذا (drm_منزل_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            أرجع AVERROR(EINVAL);
        }
    }

    إذا (!(f = av_vk_چوکٺو_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    لكل (صحيح i = 0; i < desc->nb_layers; i++) {
        ثابت صحيح planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_قدر  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ايندڙ = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_ڳڻپ = planes,
            .pPlaneLayouts = (ثابت VkSubresourceLayout *)&ext_img_layouts,
        };
        Vk_External_يادگيري_Image_Create_Info ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_يادگيري_IMAGE_CREATE_INFO,
            .p_ايندڙ       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_ايندڙ                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_منزل_vulkan_fmt(desc->layers[i].format),
            .extent.اونهائي          = 1,
            .mip_سطحون             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_ڳڻپ_1_ٻٽو_انگ,
            .p_قطار_Family_Indices   = p->img_qfs,
            .قطار_Family_اشاريو_ڳڻپ = p->nb_img_qfs,
            .sharing_گهڻائي           = p->nb_img_qfs > 1 ? VK_SHARING_گهڻائي_CONCURRENT :
                                                         VK_SHARING_گهڻائي_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        إذا (planes == 1) {
            ثابت VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            إذا (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .p_ايندڙ = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .p_قطار_Family_Indices = create_info.p_قطار_Family_Indices,
            .قطار_Family_اشاريو_ڳڻپ = create_info.قطار_Family_اشاريو_ڳڻپ,
            .sharing_گهڻائي = create_info.sharing_گهڻائي,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_ايندڙ = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        إذا (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_ٻٽو_انگ |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_ٻٽو_انگ;
        إذا (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_ٻٽو_انگ |
                                 VK_IMAGE_USAGE_TRANSFER_DST_ٻٽو_انگ;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .p_ايندڙ  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        إذا (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.ويڪر, &create_info.extent.اوچائي,
                     hwfc->sw_format, src->ويڪر, src->اوچائي, i);

        /* Set the subresource layout based on the layer properties */
        لكل (صحيح j = 0; j < planes; j++) {
            ext_img_layouts[j].وٿي     = desc->layers[i].planes[j].وٿي;
            ext_img_layouts[j].صف_Pitch_2   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].سائيز       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].اونهائي_Pitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            اذهب fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        إذا (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            اذهب fail;
        }

        f->قطار_family[i] = VK_قطار_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_قدر[i] = 0;
    }

    لكل (صحيح i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        Vk_Image_يادگيري_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_يادگيري_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        Vk_يادگيري_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_REQUIREMENTS,
        };
        Vk_يادگيري_Requirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_REQUIREMENTS_2,
            .p_ايندڙ = &ded_req,
        };

        /* Allocation/importing */
        Vk_يادگيري_Fd_Properties_KHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        Vk_Import_يادگيري_Fd_Info_KHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_يادگيري_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_اشاريو].fd),
            .handleType = VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT,
        };
        Vk_يادگيري_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_DEDICATED_ALLOCATE_INFO,
            .p_ايندڙ = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->Get_يادگيري_Fd_Properties_KHR(hwctx->act_dev,
                                           VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT,
                                           idesc.fd, &fdmp);
        إذا (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            اذهب fail;
        }

        vk->Get_Image_يادگيري_Requirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.يادگيري_Requirements.يادگيري_Type_بٽ = fdmp.يادگيري_Type_بٽ;

        err = alloc_mem(ctx, &req2.يادگيري_Requirements,
                        VK_يادگيري_PROPERTY_DEVICE_LOCAL_ٻٽو_انگ,
                        (ded_req.prefers_Dedicated_ورهاست ||
                         ded_req.requires_Dedicated_ورهاست) ?
                            &ded_alloc : ded_alloc.p_ايندڙ,
                        &f->flags, &f->mem[i]);
        إذا (err) {
            close(idesc.fd);
            اذهب fail;
        }

        f->سائيز[i] = req2.يادگيري_Requirements.سائيز;
    }

    لكل (صحيح i = 0; i < desc->nb_layers; i++) {
        ثابت صحيح planes = desc->layers[i].nb_planes;
        لكل (صحيح j = 0; j < planes; j++) {
            Vk_Image_Aspect_Flag_بٽ aspect = j == 0 ? VK_IMAGE_ASPECT_يادگيري_PLANE_0_ٻٽو_انگ_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_يادگيري_PLANE_1_ٻٽو_انگ_EXT :
                                                    VK_IMAGE_ASPECT_يادگيري_PLANE_2_ٻٽو_انگ_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_يادگيري_INFO;
            plane_info[bind_counts].p_ايندڙ = عدم;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_يادگيري_INFO;
            bind_info[bind_counts].p_ايندڙ  = planes > 1 ? &plane_info[bind_counts] : عدم;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].يادگيري = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].يادگيري_وٿي = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        اذهب fail;
    }

    *چوکٺو = f;

    أرجع 0;

fail:
    vulkan_چوکٺو_free(hwfc, f);

    أرجع err;
}

ساكن صحيح vulkan_map_from_drm_چوکٺو_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ثابت AVDRMFrameDescriptor *desc, صحيح flags)
{
    صحيح err;
    Vk_نتيجو ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#جيڪڏهن_وصف_ٿيل DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    إذا (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_بفر cmd_buf;
        FFVkExecContext *exec;
        Vk_Image_يادگيري_Barrier2 img_bar[AV_انگ_معلومات_اشارا];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        صحيح nb_img_bar = 0;

        لكل (صحيح i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ٻٽو,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_ايندڙ = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            بنية dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            إذا (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                لكل (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                أرجع err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            إذا (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                لكل (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                أرجع err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ٻٽو_انگ,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_ٻٽو_انگ,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            إذا (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                لكل (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                أرجع err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_شروعات(&p->vkctx, exec);
        إذا (err < 0) {
            لكل (صحيح i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            أرجع err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_جوڙيو_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_جوڙيو_dep_چوکٺو(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ);
        إذا (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            أرجع err;
        }

        ff_vk_چوکٺو_barrier(&p->vkctx, exec, dst, img_bar, &nb_img_bar,
                            VK_PIPELINE_STAGE_2_NONE,
                            VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                            ((flags & AV_HWFRAME_MAP_READ) ?
                             VK_ACCESS_2_SHADER_SAMPLED_READ_ٻٽو_انگ : 0x0) |
                            ((flags & AV_HWFRAME_MAP_WRITE) ?
                             VK_ACCESS_2_SHADER_STORAGE_WRITE_ٻٽو_انگ : 0x0),
                            VK_IMAGE_LAYOUT_GENERAL,
                            p->nb_img_qfs > 1 ? VK_قطار_FAMILY_IGNORED : p->img_qfs[0]);

        vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
                .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                .p_Image_يادگيري_Barriers = img_bar,
                .image_يادگيري_Barrier_ڳڻپ = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        إذا (err < 0)
            أرجع err;
    } وإلا
#جيڪڏهن_پورو
    {
        AVVk_چوکٺو *f = (AVVk_چوکٺو *)dst->معلومات[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_EXTERNAL_IMPORT);
        إذا (err)
            أرجع err;
    }

    أرجع 0;
}

ساكن صحيح vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags)
{
    صحيح err = 0;
    AVVk_چوکٺو *f;
    ثابت AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->معلومات[0];

    إذا ((err = vulkan_map_from_drm_چوکٺو_desc(hwfc, &f, src, flags)))
        أرجع err;

    /* The unmapping function will free this */
    dst->معلومات[0] = (uint8_t *)f;
    dst->ويڪر   = src->ويڪر;
    dst->اوچائي  = src->اوچائي;

    err = ff_hwframe_map_create(dst->hw_چوکٺا_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    إذا (err < 0)
        اذهب fail;

    err = vulkan_map_from_drm_چوکٺو_sync(hwfc, dst, desc, flags);
    إذا (err < 0)
        أرجع err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    أرجع 0;

fail:
    vulkan_چوکٺو_free(hwfc->device_ctx->hwctx, f);
    dst->معلومات[0] = عدم;
    أرجع err;
}

#إذا CONFIG_VAAPI
ساكن صحيح vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ثابت AVFrame *src,
                                 صحيح flags)
{
    صحيح err;
    AVFrame *tmp = av_چوکٺو_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_چوکٺا_ctx->معلومات;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->معلومات[3];

    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_مفرد;

    err = av_hwframe_map(tmp, src, flags);
    إذا (err < 0)
        اذهب fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_چوکٺو_free(&tmp);
    أرجع err;
}
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا CONFIG_CUDA
ساكن صحيح export_mem_منزل_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_چوکٺو_اندروني *dst_int, صحيح idx,
                              Vk_Device_يادگيري mem, size_t سائيز)
{
    Vk_نتيجو ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#جيڪڏهن_وصف_ٿيل _WIN32
    CUDA_EXTERNAL_يادگيري_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .سائيز = سائيز,
    };
    Vk_يادگيري_Get_Win32_Handle_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_يادگيري_GET_WIN32_HANDLE_INFO_KHR,
        .يادگيري     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32_ٻٽو_انگ
            : VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_WIN32_KMT_ٻٽو_انگ,
    };

    ret = vk->Get_يادگيري_Win32_Handle_KHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#وإلا
    CUDA_EXTERNAL_يادگيري_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_FD,
        .سائيز = سائيز,
    };
    Vk_يادگيري_Get_Fd_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_يادگيري_GET_FD_INFO_KHR,
        .يادگيري     = mem,
        .handleType = VK_EXTERNAL_يادگيري_HANDLE_TYPE_OPAQUE_FD_ٻٽو_انگ_KHR,
    };

    ret = vk->Get_يادگيري_Fd_KHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }
#جيڪڏهن_پورو

    ret = CHECK_CU(cu->cu_Import_External_يادگيري(&dst_int->ext_mem[idx], &ext_desc));
    إذا (ret < 0) {
#جيڪڏهن_وصف_نه_ٿيل _WIN32
        close(ext_desc.handle.fd);
#جيڪڏهن_پورو
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح export_sem_منزل_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_چوکٺو_اندروني *dst_int, صحيح idx,
                              VkSemaphore sem)
{
    Vk_نتيجو ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#جيڪڏهن_وصف_ٿيل _WIN32
    VkSemaphoreGetWin32HandleInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
        .semaphore = sem,
        .handleType = IsWindows8OrGreater()
                      ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_ٻٽو_انگ
                      : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_ٻٽو_انگ,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 10 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32 */,
    };
#وإلا
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_ٻٽو_انگ,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#وإلا
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#جيڪڏهن_پورو
    إذا (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        أرجع AVERROR_EXTERNAL;
    }
#جيڪڏهن_وصف_ٿيل _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#جيڪڏهن_پورو

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    إذا (ret < 0) {
#جيڪڏهن_وصف_نه_ٿيل _WIN32
        close(ext_sem_desc.handle.fd);
#جيڪڏهن_پورو
        أرجع AVERROR_EXTERNAL;
    }

    أرجع 0;
}

ساكن صحيح vulkan_export_منزل_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ثابت AVFrame *چوکٺو)
{
    صحيح err;
    Vk_نتيجو ret;
    AVVk_چوکٺو *dst_f;
    AVVk_چوکٺو_اندروني *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    صحيح nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->معلومات;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_اندروني *cu_اندروني = cuda_dev->اندروني;
    CudaFunctions *cu = cu_اندروني->cuda_dl;
    CUarray_format cufmt = desc->comp[0].اونهائي > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ثابت صحيح elem_سائيز = 1 + (desc->comp[0].اونهائي > 8);

    dst_f = (AVVk_چوکٺو *)چوکٺو->معلومات[0];
    dst_int = dst_f->اندروني;

    إذا (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_بفر_ref(cuda_hwfc);
        إذا (!dst_int->cuda_fc_ref)
            أرجع AVERROR(ENOMEM);

        nb_images = ff_vk_ڳڻپ_images(dst_f);
        لكل (صحيح i = 0; i < nb_images; i++) {
            err = export_mem_منزل_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->سائيز[i]);
            إذا (err < 0)
                اذهب fail;

            err = export_sem_منزل_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            إذا (err < 0)
                اذهب fail;
        }

        إذا (nb_images != planes) {
            لكل (صحيح i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                إذا (desc->comp[i].قدم / elem_سائيز > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    اذهب fail;
                }

                VkImageSubresource subres = {
                    .aspect_نقاب = i == 2 ? VK_IMAGE_ASPECT_يادگيري_PLANE_2_ٻٽو_انگ_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_يادگيري_PLANE_1_ٻٽو_انگ_EXT :
                                           VK_IMAGE_ASPECT_يادگيري_PLANE_0_ٻٽو_انگ_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.وٿي;
            }
        }

        لكل (صحيح i = 0; i < planes; i++) {
            CUDA_EXTERNAL_يادگيري_MIPMAPPED_ARRAY_DESC tex_desc = {
                .وٿي = offsets[i],
                .arrayDesc = {
                    .اونهائي_2 = 0,
                    .Format = cufmt,
                    .انگ_Channels = desc->comp[i].قدم / elem_سائيز,
                    .Flags = 0,
                },
                .انگ_سطحون = 1,
            };
            صحيح p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ويڪر, hwfc->اوچائي, i);
            tex_desc.arrayDesc.ويڪر_2 = p_w;
            tex_desc.arrayDesc.اوچائي_2 = p_h;

            ret = CHECK_CU(cu->cu_External_يادگيري_Get_Mapped_Mipmapped_Array(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            إذا (ret < 0) {
                err = AVERROR_EXTERNAL;
                اذهب fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            إذا (ret < 0) {
                err = AVERROR_EXTERNAL;
                اذهب fail;
            }

        }
    }

    أرجع 0;

fail:
    vulkan_free_اندروني(p, dst_f);
    أرجع err;
}

ساكن صحيح vulkan_transfer_معلومات_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ثابت AVFrame *src)
{
    صحيح err;
    CUcontext dummy;
    AVVk_چوکٺو *dst_f;
    AVVk_چوکٺو_اندروني *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    صحيح nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_چوکٺا_ctx->معلومات;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_اندروني *cu_اندروني = cuda_dev->اندروني;
    CudaFunctions *cu = cu_اندروني->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_انگ_معلومات_اشارا] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_انگ_معلومات_اشارا] = { 0 };

    dst_f = (AVVk_چوکٺو *)dst->معلومات[0];
    nb_images = ff_vk_ڳڻپ_images(dst_f);

    err = prepare_چوکٺو(hwfc, &fp->upload_exec, dst_f, PREP_گهڻائي_EXTERNAL_EXPORT);
    إذا (err < 0)
        أرجع err;

    err = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(cuda_dev->cuda_ctx));
    إذا (err < 0)
        أرجع err;

    err = vulkan_export_منزل_cuda(hwfc, src->hw_چوکٺا_ctx, dst);
    إذا (err < 0) {
        CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
        أرجع err;
    }

    dst_int = dst_f->اندروني;

    لكل (صحيح i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.قدر = dst_f->sem_قدر[i] + 0;
        s_s_par[i].params.fence.قدر = dst_f->sem_قدر[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->وهڪرو));
    إذا (err < 0)
        اذهب fail;

    لكل (صحيح i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .src_يادگيري_Type = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->معلومات[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dst_يادگيري_Type = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        صحيح p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->ويڪر, hwfc->اوچائي, i);

        cpy.ويڪر_اندريون_بائيٽون = p_w * desc->comp[i].قدم;
        cpy.اوچائي_2 = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->وهڪرو));
        إذا (err < 0)
            اذهب fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->وهڪرو));
    إذا (err < 0)
        اذهب fail;

    لكل (صحيح i = 0; i < nb_images; i++)
        dst_f->sem_قدر[i]++;

    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    أرجع err = prepare_چوکٺو(hwfc, &fp->upload_exec, dst_f, PREP_گهڻائي_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    vulkan_free_اندروني(p, dst_f);
    av_بفر_unref(&dst->buf[0]);
    أرجع err;
}
#جيڪڏهن_پورو

ساكن صحيح vulkan_map_منزل(AVHWFramesContext *hwfc, AVFrame *dst,
                         ثابت AVFrame *src, صحيح flags)
{
    av_اڻ_استعمال_ٿيل VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    بدل (src->format) {
#إذا CONFIG_LIBDRM
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
        إذا (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            أرجع vulkan_map_from_vaapi(hwfc, dst, src, flags);
        وإلا
            أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
    حالة AV_PIX_FMT_DRM_مفرد:
        إذا (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            أرجع vulkan_map_from_drm(hwfc, dst, src, flags);
        وإلا
            أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }
}

#إذا CONFIG_LIBDRM
تعريفنوع بنية VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVk_چوکٺو *ذريعو;
} VulkanDRMMapping;

ساكن فراغ vulkan_unmap_منزل_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_چوکٺو_sync(hwfc, hwmap->ذريعو, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    لكل (صحيح i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

ساكن مضمن uint32_t vulkan_fmt_منزل_drm(VkFormat vkfmt)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        إذا (vulkan_drm_format_map[i].vk_format == vkfmt)
            أرجع vulkan_drm_format_map[i].drm_fourcc;
    أرجع DRM_FORMAT_INVALID;
}

#وصف_ڪريو MAX_يادگيري_PLANES 4
ساكن VkImageAspectFlags plane_اشاريو_منزل_aspect(صحيح plane) {
    إذا (plane == 0) أرجع VK_IMAGE_ASPECT_يادگيري_PLANE_0_ٻٽو_انگ_EXT;
    إذا (plane == 1) أرجع VK_IMAGE_ASPECT_يادگيري_PLANE_1_ٻٽو_انگ_EXT;
    إذا (plane == 2) أرجع VK_IMAGE_ASPECT_يادگيري_PLANE_2_ٻٽو_انگ_EXT;
    إذا (plane == 3) أرجع VK_IMAGE_ASPECT_يادگيري_PLANE_3_ٻٽو_انگ_EXT;

    av_assert2 (0 && "Invalid plane index");
    أرجع VK_IMAGE_ASPECT_يادگيري_PLANE_0_ٻٽو_انگ_EXT;
}

#جيڪڏهن_وصف_ٿيل DMA_BUF_IOCTL_EXPORT_SYNC_FILE
ساكن صحيح vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVk_چوکٺو *f,
                                     Vulkan_چوکٺا_Priv *fp, صحيح nb_sems)
{
    صحيح sync_fd = -1;
    Vk_نتيجو ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    إذا (f->اندروني->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ٻٽو_انگ,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_ايندڙ         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ٻٽو,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_ايندڙ = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->اندروني->drm_sync_sem);
        إذا (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            أرجع AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    إذا (ff_vk_exec_شروعات(&p->vkctx, exec) >= 0) {
        لكل (صحيح i = 0; i < nb_sems; i++)
            ff_vk_exec_جوڙيو_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_قدر[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ);
        ff_vk_exec_جوڙيو_dep_bool_sem(&p->vkctx, exec, &f->اندروني->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ, 0);
        إذا (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->اندروني->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_ٻٽو_انگ,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            إذا (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    أرجع sync_fd;
}
#جيڪڏهن_پورو

ساكن صحيح vulkan_map_منزل_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ثابت AVFrame *src, صحيح flags)
{
    صحيح err = 0;
    Vk_نتيجو ret;
    AVVk_چوکٺو *f = (AVVk_چوکٺو *)src->معلومات[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ثابت صحيح nb_sems = nb_images;
    صحيح free_drm_desc_on_err = 1;
    صحيح sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(حجم(*drm_desc));
    إذا (!drm_desc)
        أرجع AVERROR(ENOMEM);

    err = prepare_چوکٺو(hwfc, &fp->compute_exec, f, PREP_گهڻائي_EXTERNAL_EXPORT);
    إذا (err < 0)
        اذهب پڇاڙي;

#جيڪڏهن_وصف_ٿيل DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        إذا (err < 0)
            اذهب پڇاڙي;
        sync_fd = err;
        err = 0;
    }
#جيڪڏهن_پورو

    إذا (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_ڳڻپ = nb_sems,
            .pSemaphores    = f->sem,
            .p_قدرون        = f->sem_قدر,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_چوکٺا_ctx, dst, src, &vulkan_unmap_منزل_drm, drm_desc);
    إذا (err < 0)
        اذهب پڇاڙي;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    إذا (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        اذهب پڇاڙي;
    }

    لكل (صحيح i = 0; (i < planes) && (f->mem[i]); i++) {
        Vk_يادگيري_Get_Fd_Info_KHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_يادگيري_GET_FD_INFO_KHR,
            .يادگيري     = f->mem[i],
            .handleType = VK_EXTERNAL_يادگيري_HANDLE_TYPE_DMA_BUF_ٻٽو_انگ_EXT,
        };

        ret = vk->Get_يادگيري_Fd_KHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        إذا (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            اذهب پڇاڙي;
        }

#إذا HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        إذا (sync_fd >= 0) {
            صحيح dup_fd = dup(sync_fd);
            إذا (dup_fd >= 0) {
                بنية dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                إذا (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } وإلا {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#جيڪڏهن_پورو

        drm_desc->nb_objects++;
        drm_desc->objects[i].سائيز = f->سائيز[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    لكل (صحيح i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_منزل_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_ڳڻپ;

        إذا (drm_desc->layers[i].nb_planes > MAX_يادگيري_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            اذهب پڇاڙي;
        }

        لكل (صحيح j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            صحيح aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspect_نقاب = plane_اشاريو_منزل_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_اشاريو = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].وٿي = layout.وٿي;
            drm_desc->layers[i].planes[j].pitch  = layout.صف_Pitch_2;
        }

        إذا (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            اذهب پڇاڙي;
        }


        إذا (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            استمر;

    }

    dst->ويڪر   = src->ويڪر;
    dst->اوچائي  = src->اوچائي;
    dst->معلومات[0] = (uint8_t *)drm_desc;
    dst->hw_چوکٺا_ctx = av_بفر_ref(src->hw_چوکٺا_ctx);

    إذا (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    أرجع 0;

پڇاڙي:
    لكل (صحيح i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    إذا (free_drm_desc_on_err)
        av_free(drm_desc);
    إذا (sync_fd >= 0)
        close(sync_fd);
    أرجع err;
}

#إذا CONFIG_VAAPI
ساكن صحيح vulkan_map_منزل_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ثابت AVFrame *src, صحيح flags)
{
    صحيح err;
    AVFrame *tmp = av_چوکٺو_alloc();
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_مفرد;

    err = vulkan_map_منزل_drm(hwfc, tmp, src, flags);
    إذا (err < 0)
        اذهب fail;

    err = av_hwframe_map(dst, tmp, flags);
    إذا (err < 0)
        اذهب fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_چوکٺو_free(&tmp);
    أرجع err;
}
#جيڪڏهن_پورو
#جيڪڏهن_پورو

ساكن صحيح vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ثابت AVFrame *src, صحيح flags)
{
    av_اڻ_استعمال_ٿيل VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    بدل (dst->format) {
#إذا CONFIG_LIBDRM
    حالة AV_PIX_FMT_DRM_مفرد:
        إذا (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            أرجع vulkan_map_منزل_drm(hwfc, dst, src, flags);
        وإلا
            أرجع AVERROR(ENOSYS);
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
        إذا (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            أرجع vulkan_map_منزل_vaapi(hwfc, dst, src, flags);
        وإلا
            أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
#جيڪڏهن_پورو
    افتراضي:
        اكسر;
    }
    أرجع AVERROR(ENOSYS);
}

ساكن صحيح copy_بفر_معلومات(AVHWFramesContext *hwfc, FFVk_بفر *vkbuf,
                            AVFrame *swf, Vk_بفر_Image_Copy *region,
                            صحيح planes, صحيح upload)
{
    صحيح err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    صحيح bytewidth[AV_انگ_معلومات_اشارا];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    لكل (صحيح i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->ويڪر, i);
        إذا (bytewidth[i] < 0)
            أرجع bytewidth[i];
    }

    إذا (upload) {
        لكل (صحيح i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].بفر_وٿي,
                                region[i].بفر_صف_ڊيگهائي,
                                swf->معلومات[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.اوچائي);

        err = ff_vk_flush_بفر(&p->vkctx, vkbuf, 0, VK_سڄو_سائيز, 1);
        إذا (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            أرجع AVERROR_EXTERNAL;
        }
    } وإلا {
        err = ff_vk_flush_بفر(&p->vkctx, vkbuf, 0, VK_سڄو_سائيز, 0);
        إذا (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            أرجع AVERROR_EXTERNAL;
        }

        لكل (صحيح i = 0; i < planes; i++)
            av_image_copy_plane(swf->معلومات[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].بفر_وٿي,
                                region[i].بفر_صف_ڊيگهائي,
                                bytewidth[i],
                                region[i].imageExtent.اوچائي);
    }

    أرجع 0;
}

ساكن صحيح get_plane_buf(AVHWFramesContext *hwfc, FFVk_بفر **dst,
                         AVFrame *swf, Vk_بفر_Image_Copy *region, صحيح upload)
{
    صحيح err;
    uint32_t p_w, p_h;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(swf->format);
    Vk_بفر_Usage_Flags buf_usage = upload ? VK_بفر_USAGE_TRANSFER_SRC_ٻٽو_انگ :
                                            VK_بفر_USAGE_TRANSFER_DST_ٻٽو_انگ;

    size_t buf_وٿي = 0;
    لكل (صحيح i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->ويڪر, swf->اوچائي, i);

        region[i] = (Vk_بفر_Image_Copy) {
            .بفر_وٿي = buf_وٿي,
            .بفر_صف_ڊيگهائي = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_بفر_Copy_صف_Pitch_Alignment),
            .بفر_Image_اوچائي = p_h,
            .imageSubresource.layer_ڳڻپ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_وٿي += FFALIGN(p_h*region[i].بفر_صف_ڊيگهائي,
                              p->props.properties.limits.optimal_بفر_Copy_وٿي_Alignment);
    }

    err = ff_vk_get_pooled_بفر(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  عدم, buf_وٿي,
                                  VK_يادگيري_PROPERTY_HOST_VISIBLE_ٻٽو_انگ |
                                  p->vkctx.host_cached_flag);
    إذا (err < 0)
        أرجع err;

    أرجع 0;
}

ساكن صحيح host_map_چوکٺو(AVHWFramesContext *hwfc, FFVk_بفر **dst, صحيح *nb_bufs,
                          AVFrame *swf, Vk_بفر_Image_Copy *region, صحيح upload)
{
    صحيح err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    صحيح nb_src_bufs;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(swf->format);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_بفر_Usage_Flags buf_usage = upload ? VK_بفر_USAGE_TRANSFER_SRC_ٻٽو_انگ :
                                            VK_بفر_USAGE_TRANSFER_DST_ٻٽو_انگ;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    طالما (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    إذا (nb_src_bufs == 1) {
        err = ff_vk_host_map_بفر(&p->vkctx, &dst[0],
                                    swf->معلومات[0], VK_سڄو_سائيز, swf->buf[0],
                                    buf_usage);
        إذا (err < 0)
            أرجع err;
        (*nb_bufs)++;

        لكل (صحيح i = 0; i < planes; i++)
            region[i].بفر_وٿي = dst[0]->virtual_وٿي +
                                     swf->معلومات[i] - swf->معلومات[0];
    } وإلا إذا (nb_src_bufs == planes) { /* One buffer per plane */
        لكل (صحيح i = 0; i < planes; i++) {
            err = ff_vk_host_map_بفر(&p->vkctx, &dst[i],
                                        swf->معلومات[i], VK_سڄو_سائيز,
                                        swf->buf[i], buf_usage);
            إذا (err < 0)
                اذهب fail;
            (*nb_bufs)++;

            region[i].بفر_وٿي = dst[i]->virtual_وٿي;
        }
    } وإلا {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        أرجع AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    لكل (صحيح i = 0; i < planes; i++) {
        صحيح align = FFMAX(desc->comp[i].قدم, p->transfer_وٿي_align);
        إذا ((align & (align - 1)) || (region[i].بفر_وٿي & (align - 1))) {
            err = AVERROR(EINVAL);
            اذهب fail;
        }
    }

    أرجع 0;

fail:
    لكل (صحيح i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    أرجع err;
}

ساكن صحيح vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, صحيح upload)
{
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkan_چوکٺا_Context *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVk_چوکٺو *hwf_vk = (AVVk_چوکٺو *)hwf->معلومات[0];
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(swf->format);
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_انگ_معلومات_اشارا];
    صحيح nb_layout_ch = 0;

    hwfc_vk->تالو_چوکٺو(hwfc, hwf_vk);

    لكل (صحيح i = 0; i < nb_images; i++) {
        صحيح compat = 0;
        لكل (صحيح j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ڳڻپ; j++) {
            إذا (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                اكسر;
            }
        }
        إذا (compat)
            استمر;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspect_نقاب = VK_IMAGE_ASPECT_COLOR_ٻٽو_انگ,
                .level_ڳڻپ = 1,
                .layer_ڳڻپ = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_قدرون = hwf_vk->sem_قدر,
        .semaphore_ڳڻپ = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    إذا (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    إذا (upload) {
        Vk_يادگيري_منزل_Image_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_يادگيري_منزل_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_ڳڻپ = 1,
            },
        };
        Vk_Copy_يادگيري_منزل_Image_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_يادگيري_منزل_IMAGE_INFO_EXT,
            .region_ڳڻپ = 1,
            .pRegions = &region_info,
        };
        لكل (صحيح i = 0; i < planes; i++) {
            صحيح img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ويڪر, swf->اوچائي, i);

            region_info.p_Host_اشارو = swf->معلومات[i];
            region_info.يادگيري_صف_ڊيگهائي = swf->linesize[i] / desc->comp[i].قدم;
            region_info.imageSubresource.aspect_نقاب = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_يادگيري_منزل_Image_EXT(hwctx->act_dev, &copy_info);
        }
    } وإلا {
        Vk_Image_منزل_يادگيري_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_منزل_يادگيري_COPY_EXT,
            .imageSubresource = {
                .layer_ڳڻپ = 1,
            },
        };
        Vk_Copy_Image_منزل_يادگيري_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_منزل_يادگيري_INFO_EXT,
            .region_ڳڻپ = 1,
            .pRegions = &region_info,
        };
        لكل (صحيح i = 0; i < planes; i++) {
            صحيح img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->ويڪر, swf->اوچائي, i);

            region_info.p_Host_اشارو = swf->معلومات[i];
            region_info.يادگيري_صف_ڊيگهائي = swf->linesize[i] / desc->comp[i].قدم;
            region_info.imageSubresource.aspect_نقاب = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_Image_منزل_يادگيري_EXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_چوکٺو(hwfc, hwf_vk);

    أرجع 0;
}

ساكن صحيح vulkan_transfer_چوکٺو(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 صحيح upload)
{
    صحيح err;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    AVVulkan_چوکٺا_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    صحيح host_mapped = 0;

    AVVk_چوکٺو *hwf_vk = (AVVk_چوکٺو *)hwf->معلومات[0];
    Vk_بفر_Image_Copy region[AV_انگ_معلومات_اشارا]; // always one per plane

    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(swf->format);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ثابت صحيح nb_images = ff_vk_ڳڻپ_images(hwf_vk);

    Vk_Image_يادگيري_Barrier2 img_bar[AV_انگ_معلومات_اشارا];
    صحيح nb_img_bar = 0;

    FFVk_بفر *bufs[AV_انگ_معلومات_اشارا];
    صحيح nb_bufs = 0;

    Vk_Command_بفر cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    إذا ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        أرجع AVERROR(EINVAL);
    }

    إذا (swf->ويڪر > hwfc->ويڪر || swf->اوچائي > hwfc->اوچائي)
        أرجع AVERROR(EINVAL);

    صحيح host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_ٻٽو_انگ_EXT;
    صحيح host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_يادگيري &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    لكل (صحيح i = 0; i < planes; i++)
        إذا (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    إذا (!upload && host_copy) {
        لكل (صحيح i = 0; i < nb_images; i++) {
            صحيح compat = 0;
            لكل (صحيح j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ڳڻپ; j++) {
                إذا (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    اكسر;
                }
            }
            إذا (!compat) {
                host_copy = 0;
                اكسر;
            }
        }
    }

    إذا (host_copy)
        أرجع vulkan_transfer_host(hwfc, hwf, swf, upload);

    لكل (صحيح i = 0; i < av_pix_fmt_ڳڻپ_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->ويڪر, swf->اوچائي, i);

        /* Buffer region for this plane */
        region[i] = (Vk_بفر_Image_Copy) {
            .بفر_وٿي = 0,
            .بفر_صف_ڊيگهائي = FFABS(swf->linesize[i]),
            .بفر_Image_اوچائي = p_h,
            .imageSubresource.layer_ڳڻپ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    إذا (host_map) {
        err = host_map_چوکٺو(hwfc, bufs, &nb_bufs, swf, region, upload);
        إذا (err >= 0)
            host_mapped = 1;
    }

    إذا (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        إذا (err < 0)
            اذهب پڇاڙي;
        nb_bufs = 1;

        إذا (upload) {
            err = copy_بفر_معلومات(hwfc, bufs[0], swf, region, planes, 1);
            إذا (err < 0)
                اذهب پڇاڙي;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_شروعات(&p->vkctx, exec);
    إذا (err < 0)
        اذهب پڇاڙي;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_جوڙيو_dep_چوکٺو(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                                   VK_PIPELINE_STAGE_2_TRANSFER_ٻٽو_انگ);
    إذا (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        اذهب پڇاڙي;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    إذا (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        إذا (host_mapped) {
            err = ff_vk_exec_جوڙيو_dep_sw_چوکٺو(&p->vkctx, exec, swf);
            إذا (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                اذهب پڇاڙي;
            }
        }

        /* Add the buffers as a dependency */
        لكل (صحيح i = 0; i < nb_bufs; i++)
            ff_vk_exec_جوڙيو_dep_refstruct(&p->vkctx, exec, bufs[i]);
    }

    ff_vk_چوکٺو_barrier(&p->vkctx, exec, hwf, img_bar, &nb_img_bar,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_ٻٽو_انگ,
                        VK_PIPELINE_STAGE_2_TRANSFER_ٻٽو_انگ_KHR,
                        upload ? VK_ACCESS_TRANSFER_WRITE_ٻٽو_انگ :
                                 VK_ACCESS_TRANSFER_READ_ٻٽو_انگ,
                        upload ? VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                        p->nb_img_qfs > 1 ? VK_قطار_FAMILY_IGNORED : p->img_qfs[0]);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_يادگيري_Barriers = img_bar,
            .image_يادگيري_Barrier_ڳڻپ = nb_img_bar,
    });

    لكل (صحيح i = 0; i < planes; i++) {
        صحيح buf_idx = FFMIN(i, (nb_bufs - 1));
        صحيح img_idx = FFMIN(i, (nb_images - 1));
        FFVk_بفر *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].بفر_صف_ڊيگهائي;
        region[i].بفر_صف_ڊيگهائي /= desc->comp[i].قدم;
        region[i].imageSubresource.aspect_نقاب = ff_vk_aspect_flag(hwf, i);

        إذا (upload)
            vk->Cmd_Copy_بفر_منزل_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        وإلا
            vk->Cmd_Copy_Image_منزل_بفر(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].بفر_صف_ڊيگهائي = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    إذا (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        إذا (!host_mapped)
            err = copy_بفر_معلومات(hwfc, bufs[0], swf, region, planes, 0);
    }

پڇاڙي:
    لكل (صحيح i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    أرجع err;
}

ساكن صحيح vulkan_transfer_معلومات_منزل(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    av_اڻ_استعمال_ٿيل VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    بدل (src->format) {
#إذا CONFIG_CUDA
    حالة AV_PIX_FMT_CUDA:
#جيڪڏهن_وصف_ٿيل _WIN32
        إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_يادگيري) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#وإلا
        إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_يادگيري) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#جيڪڏهن_پورو
            أرجع vulkan_transfer_معلومات_from_cuda(hwfc, dst, src);
        av_fallthrough;
#جيڪڏهن_پورو
    افتراضي:
        إذا (src->hw_چوکٺا_ctx)
            أرجع AVERROR(ENOSYS);
        وإلا
            أرجع vulkan_transfer_چوکٺو(hwfc, (AVFrame *)src, dst, 1);
    }
}

#إذا CONFIG_CUDA
ساكن صحيح vulkan_transfer_معلومات_منزل_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ثابت AVFrame *src)
{
    صحيح err;
    CUcontext dummy;
    AVVk_چوکٺو *dst_f;
    AVVk_چوکٺو_اندروني *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_چوکٺا_Priv *fp = hwfc->hwctx;
    ثابت صحيح planes = av_pix_fmt_ڳڻپ_planes(hwfc->sw_format);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    صحيح nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_چوکٺا_ctx->معلومات;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_اندروني *cu_اندروني = cuda_dev->اندروني;
    CudaFunctions *cu = cu_اندروني->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_انگ_معلومات_اشارا] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_انگ_معلومات_اشارا] = { 0 };

    dst_f = (AVVk_چوکٺو *)src->معلومات[0];
    nb_images = ff_vk_ڳڻپ_images(dst_f);

    err = prepare_چوکٺو(hwfc, &fp->upload_exec, dst_f, PREP_گهڻائي_EXTERNAL_EXPORT);
    إذا (err < 0)
        أرجع err;

    err = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(cuda_dev->cuda_ctx));
    إذا (err < 0)
        أرجع err;

    err = vulkan_export_منزل_cuda(hwfc, dst->hw_چوکٺا_ctx, src);
    إذا (err < 0) {
        CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
        أرجع err;
    }

    dst_int = dst_f->اندروني;

    لكل (صحيح i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.قدر = dst_f->sem_قدر[i] + 0;
        s_s_par[i].params.fence.قدر = dst_f->sem_قدر[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->وهڪرو));
    إذا (err < 0)
        اذهب fail;

    لكل (صحيح i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dst_يادگيري_Type = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->معلومات[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .src_يادگيري_Type = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        صحيح w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->ويڪر, hwfc->اوچائي, i);

        cpy.ويڪر_اندريون_بائيٽون = w * desc->comp[i].قدم;
        cpy.اوچائي_2 = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->وهڪرو));
        إذا (err < 0)
            اذهب fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->وهڪرو));
    إذا (err < 0)
        اذهب fail;

    لكل (صحيح i = 0; i < nb_images; i++)
        dst_f->sem_قدر[i]++;

    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    أرجع prepare_چوکٺو(hwfc, &fp->upload_exec, dst_f, PREP_گهڻائي_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    vulkan_free_اندروني(p, dst_f);
    av_بفر_unref(&dst->buf[0]);
    أرجع err;
}
#جيڪڏهن_پورو

ساكن صحيح vulkan_transfer_معلومات_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ثابت AVFrame *src)
{
    av_اڻ_استعمال_ٿيل VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    بدل (dst->format) {
#إذا CONFIG_CUDA
    حالة AV_PIX_FMT_CUDA:
#جيڪڏهن_وصف_ٿيل _WIN32
        إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_يادگيري) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#وإلا
        إذا ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_يادگيري) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#جيڪڏهن_پورو
            أرجع vulkan_transfer_معلومات_منزل_cuda(hwfc, dst, src);
        av_fallthrough;
#جيڪڏهن_پورو
    افتراضي:
        إذا (dst->hw_چوکٺا_ctx)
            أرجع AVERROR(ENOSYS);
        وإلا
            أرجع vulkan_transfer_چوکٺو(hwfc, dst, (AVFrame *)src, 0);
    }
}

ساكن صحيح vulkan_چوکٺا_derive_منزل(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, صحيح flags)
{
    أرجع vulkan_چوکٺا_init(dst_fc);
}

AVVk_چوکٺو *av_vk_چوکٺو_alloc(فراغ)
{
    صحيح err;
    AVVk_چوکٺو *f = av_mallocz(حجم(AVVk_چوکٺو));
    إذا (!f)
        أرجع عدم;

    f->اندروني = av_mallocz(حجم(*f->اندروني));
    إذا (!f->اندروني) {
        av_free(f);
        أرجع عدم;
    }

    err = pthread_mutex_init(&f->اندروني->update_mutex, عدم);
    إذا (err != 0) {
        av_free(f->اندروني);
        av_free(f);
        أرجع عدم;
    }

    أرجع f;
}

ثابت HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_سائيز      = حجم(VulkanDevicePriv),
    .چوکٺا_hwctx_سائيز      = حجم(Vulkan_چوکٺا_Priv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .چوکٺا_get_constraints = &vulkan_چوکٺا_get_constraints,
    .چوکٺا_init            = vulkan_چوکٺا_init,
    .چوکٺا_get_بفر      = vulkan_get_بفر,
    .چوکٺا_uninit          = vulkan_چوکٺا_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_معلومات_منزل       = vulkan_transfer_معلومات_منزل,
    .transfer_معلومات_from     = vulkan_transfer_معلومات_from,

    .map_منزل                 = vulkan_map_منزل,
    .map_from               = vulkan_map_from,
    .چوکٺا_derive_منزل       = &vulkan_چوکٺا_derive_منزل,

    .pix_fmts = (ثابت تعداد AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
