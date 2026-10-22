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

#define VK_NO_PROTOTYPES
#define VK_ENABLE_BETA_EXTENSIONS

#ifdef _WIN32
#ಅನ್ತರ್ಭಾವ <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#ಅನ್ತರ್ಭಾವ <versionhelpers.h>
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"
#ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif

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

#ಯದಿ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#endif

#ಯದಿ CONFIG_LIBDRM
#ಯದಿ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ <va/va_drmcommon.h>
#endif
#ifdef __linux__
#ಅನ್ತರ್ಭಾವ <sys/sysmacros.h>
#endif
#ಅನ್ತರ್ಭಾವ <sys/stat.h>
#ಅನ್ತರ್ಭಾವ <xf86drm.h>
#ಅನ್ತರ್ಭಾವ <drm_fourcc.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_drm.h"
#endif

#ಯದಿ HAVE_LINUX_DMA_BUF_H
#ಅನ್ತರ್ಭಾವ <sys/ioctl.h>
#ಅನ್ತರ್ಭಾವ <linux/dma-buf.h>
#endif

#ಯದಿ CONFIG_CUDA
#ಅನ್ತರ್ಭಾವ "hwcontext_cuda_internal.h"
#ಅನ್ತರ್ಭಾವ "cuda_check.h"
#define CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR explicit_mem_layout;

#ifdef VK_EXT_shader_long_vector
    VkPhysicalDeviceShaderLongVectorFeaturesEXT long_vector;
#endif

#ifdef VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#endif

#ifdef VK_EXT_zero_initialize_device_memory
    VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT zero_initialize;
#endif

#ifdef VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#endif

#ifdef VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#endif

#ifdef VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#endif
#ifdef VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#endif
#ifdef VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#endif

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#ifdef VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#endif
#ifdef VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#endif
#ifdef VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#endif

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR cooperative_matrix;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#ifdef VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#endif

#ifdef VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR internal_queue_sync;
#endif
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    ಶೂನ್ಯ *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkanDeviceQueueFamily *compute_qf;
    AVVulkanDeviceQueueFamily *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceMemoryProperties mprops;
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT hprops;
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
    ಪೂರ್ಣಾಙ್ಕ use_linear_images;

    /* Option to allocate all image planes in a single allocation */
    ಪೂರ್ಣಾಙ್ಕ contiguous_planes;

    /* Disable multiplane images */
    ಪೂರ್ಣಾಙ್ಕ disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    ಪೂರ್ಣಾಙ್ಕ avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    ಪೂರ್ಣಾಙ್ಕ transfer_offset_align;

    /* Maximum queues */
    ಪೂರ್ಣಾಙ್ಕ limit_queues;
} VulkanDevicePriv;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanFramesPriv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanFramesContext p;

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
    ಪೂರ್ಣಾಙ್ಕ export_requires_dedicated;
} VulkanFramesPriv;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVVkFrameInternal {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#ಯದಿ CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternalMemory ext_mem[AV_ಅಂಕೆ_DATA_POINTERS];
    CUmipmappedArray cu_mma[AV_ಅಂಕೆ_DATA_POINTERS];
    CUarray cu_array[AV_ಅಂಕೆ_DATA_POINTERS];
    CUexternalSemaphore cu_sem[AV_ಅಂಕೆ_DATA_POINTERS];
#ifdef _WIN32
    HANDLE ext_mem_handle[AV_ಅಂಕೆ_DATA_POINTERS];
    HANDLE ext_sem_handle[AV_ಅಂಕೆ_DATA_POINTERS];
#endif
#endif
} AVVkFrameInternal;

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

#ifdef VK_EXT_shader_long_vector
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_vector, FF_VK_EXT_LONG_VECTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_FEATURES_EXT);
#endif

#ifdef VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#endif

#ifdef VK_EXT_zero_initialize_device_memory
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_MEMORY_FEATURES_EXT);
#endif

#ifdef VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#endif

#ifdef VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#endif

#ifdef VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#endif
#ifdef VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#endif
#ifdef VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#endif

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#ifdef VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#endif
#ifdef VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#endif
#ifdef VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#endif

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_matrix, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR);

#ifdef VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#endif

#ifdef VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->internal_queue_sync, FF_VK_EXT_INTERNAL_QUEUE_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#endif

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
ಸ್ಥಿರ ಶೂನ್ಯ device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#define COPY_VAL(VAL)        \
    ಕುರು {                     \
        dst->VAL = src->VAL; \
    } ಯಾವತ್ (0)              \

    COPY_VAL(device.features.shaderImageGatherExtended);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);
    COPY_VAL(device.features.fragmentStoresAndAtomics);
    COPY_VAL(device.features.vertexPipelineStoresAndAtomics);
    COPY_VAL(device.features.shaderInt64);
    COPY_VAL(device.features.shaderInt16);
    COPY_VAL(device.features.shaderFloat64);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);

    COPY_VAL(vulkan_1_1.samplerYcbcrConversion);
    COPY_VAL(vulkan_1_1.storage_ತಳ್ಳು_Constant16);
    COPY_VAL(vulkan_1_1.storageBuffer16BitAccess);
    COPY_VAL(vulkan_1_1.uniformAndStorageBuffer16BitAccess);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalarBlockLayout);
    COPY_VAL(vulkan_1_2.bufferDeviceAddress);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_ತಳ್ಳು_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storageBuffer8BitAccess);
    COPY_VAL(vulkan_1_2.uniformAndStorageBuffer8BitAccess);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shaderBufferInt64Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkanMemoryModel);
    COPY_VAL(vulkan_1_2.vulkanMemoryModelDeviceScope);
    COPY_VAL(vulkan_1_2.vulkanMemoryModelAvailabilityVisibilityChains);
    COPY_VAL(vulkan_1_2.uniformBufferStandardLayout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shaderUniformBufferArrayNonUniformIndexing);
    COPY_VAL(vulkan_1_2.shaderSampledImageArrayNonUniformIndexing);
    COPY_VAL(vulkan_1_2.shaderStorageBufferArrayNonUniformIndexing);
    COPY_VAL(vulkan_1_2.shaderStorageImageArrayNonUniformIndexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.computeFullSubgroups);
    COPY_VAL(vulkan_1_3.subgroupSizeControl);
    COPY_VAL(vulkan_1_3.shaderZeroInitializeWorkgroupMemory);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#ifdef VK_EXT_shader_long_vector
    COPY_VAL(long_vector.longVector);
#endif

#ifdef VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#endif

#ifdef VK_EXT_zero_initialize_device_memory
    COPY_VAL(zero_initialize.zeroInitializeDeviceMemory);
#endif

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#ifdef VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#endif

#ifdef VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#endif

#ifdef VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#endif

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_matrix.cooperativeMatrix);

    COPY_VAL(atomic_float.shaderBufferFloat32Atomics);
    COPY_VAL(atomic_float.shaderBufferFloat32AtomicAdd);

    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayoutScalarBlockLayout);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout8BitAccess);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout16BitAccess);

#ifdef VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#endif

#ifdef VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#endif

#ifdef VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#endif

#ifdef VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#endif
#ifdef VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#endif
#ifdef VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#endif

#ifdef VK_KHR_internally_synchronized_queues
    COPY_VAL(internal_queue_sync.internallySynchronizedQueues);
#endif

    COPY_VAL(optical_flow.opticalFlow);

#undef COPY_VAL
}

#define ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT)
#define ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT | VK_IMAGE_ASPECT_PLANE_2_BIT)

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ FFVkFormatEntry {
    VkFormat vkf;
    ಗಣನಾ AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    ಪೂರ್ಣಾಙ್ಕ vk_planes;
    ಪೂರ್ಣಾಙ್ಕ nb_images;
    ಪೂರ್ಣಾಙ್ಕ nb_images_fallback;
    ಧ್ರುವ VkFormat fallback[5];
} vk_formats_list[] = {
    /* Gray formats */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GRAY8,   VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY10,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY12,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY14,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY16,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GRAY32,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GRAYF32, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32_SFLOAT } },

    /* RGB formats */
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGRA,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGBA,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8_UNORM,             AV_PIX_FMT_RGB24,   VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8_UNORM             } },
    { VK_FORMAT_B8G8R8_UNORM,             AV_PIX_FMT_BGR24,   VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_B8G8R8_UNORM             } },
    { VK_FORMAT_R16G16B16_UNORM,          AV_PIX_FMT_RGB48,   VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16_UNORM          } },
    { VK_FORMAT_R16G16B16A16_UNORM,       AV_PIX_FMT_RGBA64,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM       } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGR0,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGB0,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, AV_PIX_FMT_X2RGB10, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_A2B10G10R10_UNORM_PACK32, AV_PIX_FMT_X2BGR10, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_A2B10G10R10_UNORM_PACK32 } },
    { VK_FORMAT_R32G32B32_SFLOAT,         AV_PIX_FMT_RGBF32,  VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32G32B32_SFLOAT         } },
    { VK_FORMAT_R16G16B16A16_SFLOAT,      AV_PIX_FMT_RGBAF16, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_SFLOAT      } },
    { VK_FORMAT_R32G32B32A32_SFLOAT,      AV_PIX_FMT_RGBAF32, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32G32B32A32_SFLOAT      } },
    { VK_FORMAT_R32G32B32_UINT,           AV_PIX_FMT_RGB96,   VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32G32B32_UINT           } },
    { VK_FORMAT_R32G32B32A32_UINT,        AV_PIX_FMT_RGBA128, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R32G32B32A32_UINT        } },

    /* Planar RGB */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRP,     VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP10,   VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP12,   VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP14,   VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP16,   VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRPF16,  VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT  } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRPF32,  VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* XYZ */
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_XYZP12,   VK_IMAGE_ASPECT_COLOR_BIT, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar RGB + Alpha */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRAP,    VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP10,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP12,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP14,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP16,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRAPF16, VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GBRAP32,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRAPF32, VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* Bayer */
    { VK_FORMAT_R16_UNORM, AV_PIX_FMT_BAYER_RGGB16, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16_UNORM } },

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
    { VK_FORMAT_G8B8G8R8_422_UNORM,                     AV_PIX_FMT_YUYV422, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_B8G8R8G8_422_UNORM,                     AV_PIX_FMT_UYVY422, VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, AV_PIX_FMT_Y210,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, AV_PIX_FMT_Y212,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G16B16G16R16_422_UNORM,                 AV_PIX_FMT_Y216,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },

    /* Planar YUVA 420 at 8, 10 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA420P,    VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P10,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P16,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA422P,    VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P10,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P12,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P16,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA444P,    VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P10,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P12,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P16,  VK_IMAGE_ASPECT_COLOR_BIT, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Single plane 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32,               AV_PIX_FMT_XV30,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,     AV_PIX_FMT_XV36,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_R16G16B16A16_UNORM,                     AV_PIX_FMT_XV48,    VK_IMAGE_ASPECT_COLOR_BIT, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
};
ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ಧ್ರುವ VkFormat *av_vkfmt_from_pixfmt(ಗಣನಾ AVPixelFormat p)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_vk_formats_list; i++)
        ಯದಿ (vk_formats_list[i].pixfmt == p)
            ಪ್ರತ್ಯಾಗಮ vk_formats_list[i].fallback;
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ FFVkFormatEntry *vk_find_format_entry(ಗಣನಾ AVPixelFormat p)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_vk_formats_list; i++)
        ಯದಿ (vk_formats_list[i].pixfmt == p)
            ಪ್ರತ್ಯಾಗಮ &vk_formats_list[i];
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, ಗಣನಾ AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_ಅಂಕೆ_DATA_POINTERS], /* Output format list */
                              ಪೂರ್ಣಾಙ್ಕ *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              ಪೂರ್ಣಾಙ್ಕ disable_multiplane, ಪೂರ್ಣಾಙ್ಕ need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ಧ್ರುವ VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_vk_formats_list; i++) {
        ಯದಿ (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .pNext = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            ಪೂರ್ಣಾಙ್ಕ basics_primary = 0, basics_secondary = 0;
            ಪೂರ್ಣಾಙ್ಕ storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_LINEAR ?
                             fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);

            ಯದಿ (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_LINEAR ?
                                  fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);
            } ಅನ್ಯಥಾ {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            ಯದಿ (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                ಯದಿ (fmts) {
                    ಯದಿ (vk_formats_list[i].nb_images > 1) {
                        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } ಅನ್ಯಥಾ {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                ಯದಿ (nb_images)
                    *nb_images = 1;
                ಯದಿ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ಯದಿ (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_BIT : 0);
                ಪ್ರತ್ಯಾಗಮ 0;
            } ಅನ್ಯಥಾ ಯದಿ (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                ಯದಿ (fmts) {
                    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                ಯದಿ (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                ಯದಿ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ಯದಿ (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_secondary);
                ಪ್ರತ್ಯಾಗಮ 0;
            } ಅನ್ಯಥಾ {
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOTSUP);
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

#ಯದಿ CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ಧ್ರುವ ವರ್ಣ *pName);
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ load_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#ಯದಿ CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#ಅನ್ಯಥಾ
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *lib_names[] = {
#ಯದಿ defined(_WIN32)
        "vulkan-1.dll",
#ನೋಚೇದ್ಯದಿ defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#ಅನ್ಯಥಾ
        "libvulkan.so.1",
        "libvulkan.so",
#endif
    };

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(lib_names); i++) {
        p->libvulkan = dlopen(lib_names[i], RTLD_NOW | RTLD_LOCAL);
        ಯದಿ (p->libvulkan)
            ಭಙ್ಗ;
    }

    ಯದಿ (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#endif /* CONFIG_VULKAN_STATIC */

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanOptExtension {
    ಧ್ರುವ ವರ್ಣ *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

ಸ್ಥಿರ ಧ್ರುವ VulkanOptExtension optional_instance_exts[] = {
#ifdef __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#endif
    { 0 },
};

ಸ್ಥಿರ ಧ್ರುವ VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_ತಳ್ಳು_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_ತಳ್ಳು_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME,               FF_VK_EXT_COOP_MATRIX            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#ifdef VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#endif
#ifdef VK_EXT_shader_long_vector
    { VK_EXT_SHADER_LONG_VECTOR_EXTENSION_NAME,               FF_VK_EXT_LONG_VECTOR            },
#endif
#ifdef VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#endif
#ifdef VK_EXT_zero_initialize_device_memory
    { VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#endif
#ifdef VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#endif
#ifdef VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#endif
#ifdef VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#endif
#ifdef VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#endif
#ifdef VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#endif
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#ifdef VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#endif
#ifdef VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_INTERNAL_QUEUE_SYNC    },
#endif
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_MEMORY     },
    { VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_MEMORY },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_MEMORY   },
#ifdef _WIN32
    { VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_MEMORY  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#endif

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_QUEUE            },
    { VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_QUEUE     },
    { VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_QUEUE     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#ifdef VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#endif
#ifdef VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#endif
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

ಧ್ರುವ ವರ್ಣ **av_vk_get_optional_instance_extensions(ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಧ್ರುವ ವರ್ಣ **exts = av_malloc_array(ಪರಿಮಾಣ(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    ಯದಿ (!exts)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < (ಪೂರ್ಣಾಙ್ಕ)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *ಎಣಿಕೆ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    ಪ್ರತ್ಯಾಗಮ exts;
}

ಧ್ರುವ ವರ್ಣ **av_vk_get_optional_device_extensions(ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಧ್ರುವ ವರ್ಣ **exts = av_malloc_array(ಪರಿಮಾಣ(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    ಯದಿ (!exts)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *ಎಣಿಕೆ = FF_ARRAY_ELEMS(optional_device_exts);
    ಪ್ರತ್ಯಾಗಮ exts;
}

ಸ್ಥಿರ VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                    ಧ್ರುವ VkDebugUtilsMessengerCallbackDataEXT *data,
                                    ಶೂನ್ಯ *priv)
{
    ಪೂರ್ಣಾಙ್ಕ l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    ವಿಕಲ್ಪ (data->message_Id_ಸಂಖ್ಯೆ) {
    ಪಕ್ಷ 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    ಪಕ್ಷ 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        ಪ್ರತ್ಯಾಗಮ VK_FALSE;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }

    ವಿಕಲ್ಪ (severity) {
    ಪಕ್ಷ VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: l = AV_LOG_VERBOSE; ಭಙ್ಗ;
    ಪಕ್ಷ VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:    l = AV_LOG_INFO;    ಭಙ್ಗ;
    ಪಕ್ಷ VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: l = AV_LOG_WARNING; ಭಙ್ಗ;
    ಪಕ್ಷ VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:   l = AV_LOG_ERROR;   ಭಙ್ಗ;
    ಸ್ವಭಾವ:                                              l = AV_LOG_DEBUG;   ಭಙ್ಗ;
    }

    av_log(ctx, l, "%s\n", data->pMessage);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < data->cmd_Buf_Label_ಎಣಿಕೆ; i++)
        av_log(ctx, l, "\t%i: %s\n", i, data->pCmdBufLabels[i].pLabelName);

    ಪ್ರತ್ಯಾಗಮ VK_FALSE;
}

#define ADD_VAL_TO_LIST(list, ಎಣಿಕೆ, val)                                      \
    ಕುರು {                                                                       \
        list = av_realloc_array(list, ++ಎಣಿಕೆ, ಪರಿಮಾಣ(*list));                 \
        ಯದಿ (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            ಗಚ್ಛ fail;                                                         \
        }                                                                      \
        list[ಎಣಿಕೆ - 1] = av_strdup(val);                                      \
        ಯದಿ (!list[ಎಣಿಕೆ - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            ಗಚ್ಛ fail;                                                         \
        }                                                                      \
    } ಯಾವತ್(0)

#define RELEASE_PROPS(props, ಎಣಿಕೆ)                                            \
    ಯದಿ (props) {                                                               \
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಎಣಿಕೆ; i++)                                        \
            av_free((ಶೂನ್ಯ *)((props)[i]));                                     \
        av_free((ಶೂನ್ಯ *)props);                                                \
    }

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    VkDeviceSize max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.memory_Type_ಎಣಿಕೆ);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < p->mprops.memory_Type_ಎಣಿಕೆ; i++) {
        ಧ್ರುವ VkMemoryType type = p->mprops.memoryTypes[i];
        ಧ್ರುವ VkMemoryHeap heap = p->mprops.memoryHeaps[type.heapIndex];
        ಯದಿ (!(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            ಅನುವರ್ತ;
        max_vram = FFMAX(max_vram, heap.size);
        ಯದಿ (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            max_visible_vram = FFMAX(max_visible_vram, heap.size);
    }

    ಪ್ರತ್ಯಾಗಮ max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

ಗಣನಾ FFVulkanDebugMode {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_extensions(AVHWDeviceContext *ctx, ಪೂರ್ಣಾಙ್ಕ dev, AVDictionary *opts,
                            ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ **dst, uint32_t *ಅಂಕೆ,
                            ಗಣನಾ FFVulkanDebugMode debug_mode)
{
    ಧ್ರುವ ವರ್ಣ *tstr;
    ಧ್ರುವ ವರ್ಣ **extension_names = ರಿಕ್ತ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಙ್ಕ err = 0, found, extensions_found = 0;

    ಧ್ರುವ ವರ್ಣ *mod;
    ಪೂರ್ಣಾಙ್ಕ optional_exts_ಅಂಕೆ;
    uint32_t sup_ext_ಎಣಿಕೆ;
    ವರ್ಣ *user_exts_str = ರಿಕ್ತ;
    AVDictionaryEntry *user_exts;
    VkExtensionProperties *sup_ext;
    ಧ್ರುವ VulkanOptExtension *optional_exts;

    ಯದಿ (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_ಅಂಕೆ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", ರಿಕ್ತ, 0);
        ಯದಿ (user_exts) {
            user_exts_str = av_strdup(user_exts->ಮೌಲ್ಯ);
            ಯದಿ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(ರಿಕ್ತ, &sup_ext_ಎಣಿಕೆ, ರಿಕ್ತ);
        sup_ext = av_malloc_array(sup_ext_ಎಣಿಕೆ, ಪರಿಮಾಣ(VkExtensionProperties));
        ಯದಿ (!sup_ext)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(ರಿಕ್ತ, &sup_ext_ಎಣಿಕೆ, sup_ext);
    } ಅನ್ಯಥಾ {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_ಅಂಕೆ = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", ರಿಕ್ತ, 0);
        ಯದಿ (user_exts) {
            user_exts_str = av_strdup(user_exts->ಮೌಲ್ಯ);
            ಯದಿ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ರಿಕ್ತ,
                                               &sup_ext_ಎಣಿಕೆ, ರಿಕ್ತ);
        sup_ext = av_malloc_array(sup_ext_ಎಣಿಕೆ, ಪರಿಮಾಣ(VkExtensionProperties));
        ಯದಿ (!sup_ext)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ರಿಕ್ತ,
                                               &sup_ext_ಎಣಿಕೆ, sup_ext);
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < optional_exts_ಅಂಕೆ; i++) {
        tstr = optional_exts[i].name;
        found = 0;

        /* Check if the device has ReBAR for host image copies */
        ಯದಿ (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            ಅನುವರ್ತ;

        ಯದಿ (dev &&
            ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_mode == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            ಅನುವರ್ತ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಯದಿ (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!found)
            ಅನುವರ್ತ;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
    }

    ಯದಿ (!dev &&
        ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_mode == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        found = 0;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಯದಿ (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (found) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
        } ಅನ್ಯಥಾ {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }
    }

#ifdef VK_KHR_shader_relaxed_extended_instruction
    ಯದಿ ((debug_mode == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        found = 0;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
            ಯದಿ (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!found) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }
    }
#endif

    ಯದಿ (user_exts_str) {
        ವರ್ಣ *save, *token = av_strtok(user_exts_str, "+", &save);
        ಯಾವತ್ (token) {
            found = 0;
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sup_ext_ಎಣಿಕೆ; j++) {
                ಯದಿ (!strcmp(token, sup_ext[j].extensionName)) {
                    found = 1;
                    ಭಙ್ಗ;
                }
            }
            ಯದಿ (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                ADD_VAL_TO_LIST(extension_names, extensions_found, token);
            } ಅನ್ಯಥಾ {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(ರಿಕ್ತ, "+", &save);
        }
    }

    *dst = extension_names;
    *ಅಂಕೆ = extensions_found;

    av_free(user_exts_str);
    av_free(sup_ext);
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    RELEASE_PROPS(extension_names, extensions_found);
    av_free(user_exts_str);
    av_free(sup_ext);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ **dst, uint32_t *ಅಂಕೆ,
                        ಗಣನಾ FFVulkanDebugMode *debug_mode)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    ಪೂರ್ಣಾಙ್ಕ layer_standard_validation_found = 0;

    uint32_t sup_layer_ಎಣಿಕೆ;
    VkLayerProperties *sup_layers;

    AVDictionaryEntry *user_layers = av_dict_get(opts, "layers", ರಿಕ್ತ, 0);
    ವರ್ಣ *user_layers_str = ರಿಕ್ತ;
    ವರ್ಣ *save, *token;

    ಧ್ರುವ ವರ್ಣ **enabled_layers = ರಿಕ್ತ;
    uint32_t enabled_layers_ಎಣಿಕೆ = 0;

    AVDictionaryEntry *debug_opt = av_dict_get(opts, "debug", ರಿಕ್ತ, 0);
    ಗಣನಾ FFVulkanDebugMode mode;

    *debug_mode = mode = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_ಎಣಿಕೆ, ರಿಕ್ತ);
    sup_layers = av_malloc_array(sup_layer_ಎಣಿಕೆ, ಪರಿಮಾಣ(VkLayerProperties));
    ಯದಿ (!sup_layers)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_ಎಣಿಕೆ, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < sup_layer_ಎಣಿಕೆ; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    ಯದಿ (!debug_opt && !user_layers)
        ಗಚ್ಛ end;

    /* Check for any properly supported validation layer */
    ಯದಿ (debug_opt) {
        ಯದಿ (!strcmp(debug_opt->ಮೌಲ್ಯ, "printf")) {
            mode = FF_VULKAN_DEBUG_PRINTF;
        } ಅನ್ಯಥಾ ಯದಿ (!strcmp(debug_opt->ಮೌಲ್ಯ, "validate")) {
            mode = FF_VULKAN_DEBUG_VALIDATE;
        } ಅನ್ಯಥಾ ಯದಿ (!strcmp(debug_opt->ಮೌಲ್ಯ, "practices")) {
            mode = FF_VULKAN_DEBUG_PRACTICES;
        } ಅನ್ಯಥಾ {
            ವರ್ಣ *end_ptr = ರಿಕ್ತ;
            ಪೂರ್ಣಾಙ್ಕ idx = strtol(debug_opt->ಮೌಲ್ಯ, &end_ptr, 10);
            ಯದಿ (end_ptr == debug_opt->ಮೌಲ್ಯ || end_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->ಮೌಲ್ಯ);
                err = AVERROR(EINVAL);
                ಗಚ್ಛ end;
            }
            mode = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    ಯದಿ ((mode == FF_VULKAN_DEBUG_VALIDATE) ||
        (mode == FF_VULKAN_DEBUG_PRINTF) ||
        (mode == FF_VULKAN_DEBUG_PRACTICES)) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < sup_layer_ಎಣಿಕೆ; i++) {
            ಯದಿ (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_ಎಣಿಕೆ, layer_standard_validation);
                *debug_mode = mode;
                layer_standard_validation_found = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!layer_standard_validation_found) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            ಗಚ್ಛ end;
        }
    }

    /* Process any custom layers enabled */
    ಯದಿ (user_layers) {
        ಪೂರ್ಣಾಙ್ಕ found;

        user_layers_str = av_strdup(user_layers->ಮೌಲ್ಯ);
        ಯದಿ (!user_layers_str) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        ಯಾವತ್ (token) {
            found = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            ಯದಿ (!strcmp(layer_standard_validation, token) && layer_standard_validation_found) {
                token = av_strtok(ರಿಕ್ತ, "+", &save);
                ಭಙ್ಗ;
            }

            /* Try to find the layer in the list of supported layers */
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < sup_layer_ಎಣಿಕೆ; j++) {
                ಯದಿ (!strcmp(token, sup_layers[j].layerName)) {
                    found = 1;
                    ಭಙ್ಗ;
                }
            }

            ಯದಿ (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_ಎಣಿಕೆ, token);

                /* If debug was not set as an option, force it */
                ಯದಿ (!strcmp(layer_standard_validation, token))
                    *debug_mode = FF_VULKAN_DEBUG_VALIDATE;
            } ಅನ್ಯಥಾ {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                ಗಚ್ಛ end;
            }

            token = av_strtok(ರಿಕ್ತ, "+", &save);
        }
    }

fail:
end:
    av_free(sup_layers);
    av_free(user_layers_str);

    ಯದಿ (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_ಎಣಿಕೆ);
    } ಅನ್ಯಥಾ {
        *dst = enabled_layers;
        *ಅಂಕೆ = enabled_layers_ಎಣಿಕೆ;
    }

    ಪ್ರತ್ಯಾಗಮ err;
}

/* Creates a VkInstance */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           ಗಣನಾ FFVulkanDebugMode *debug_mode)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .applicationVersion = VK_MAKE_VERSION(LIBAVUTIL_VERSION_MAJOR,
                                              LIBAVUTIL_VERSION_MINOR,
                                              LIBAVUTIL_VERSION_MICRO),
        .pEngineName        = "libavutil",
        .apiVersion         = VK_API_VERSION_1_3,
        .engineVersion      = VK_MAKE_VERSION(LIBAVUTIL_VERSION_MAJOR,
                                              LIBAVUTIL_VERSION_MINOR,
                                              LIBAVUTIL_VERSION_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    ಯದಿ (!hwctx->get_proc_addr) {
        err = load_libvulkan(ctx);
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    ಯದಿ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        ಪ್ರತ್ಯಾಗಮ err;
    }

    err = check_layers(ctx, opts, &inst_props.ppEnabledLayerNames,
                       &inst_props.enabled_Layer_ಎಣಿಕೆ, debug_mode);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.ppEnabledExtensionNames,
                           &inst_props.enabled_Extension_ಎಣಿಕೆ, *debug_mode);
    hwctx->enabled_inst_extensions = inst_props.ppEnabledExtensionNames;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_ಎಣಿಕೆ;
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    /* Enable debug features if needed */
    ಯದಿ (*debug_mode == FF_VULKAN_DEBUG_VALIDATE) {
        ಸ್ಥಿರ ಧ್ರುವ VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.pNext = &validation_features;
    } ಅನ್ಯಥಾ ಯದಿ (*debug_mode == FF_VULKAN_DEBUG_PRINTF) {
        ಸ್ಥಿರ ಧ್ರುವ VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.pNext = &validation_features;
    } ಅನ್ಯಥಾ ಯದಿ (*debug_mode == FF_VULKAN_DEBUG_PRACTICES) {
        ಸ್ಥಿರ ಧ್ರುವ VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_ಎಣಿಕೆ = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.pNext = &validation_features;
    }

#ifdef __APPLE__
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < inst_props.enabled_Extension_ಎಣಿಕೆ; i++) {
        ಯದಿ (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.ppEnabledExtensionNames[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            ಭಙ್ಗ;
        }
    }
#endif

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಗಚ್ಛ fail;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    ಯದಿ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        ಗಚ್ಛ fail;
    }

    /* Setup debugging callback if needed */
    ಯದಿ ((*debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_mode == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT    |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .pUserData = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.ppEnabledLayerNames, inst_props.enabled_Layer_ಎಣಿಕೆ);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_SIZE]; /* Will use this first unless !has_uuid */
    ಪೂರ್ಣಾಙ್ಕ has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ಧ್ರುವ ವರ್ಣ *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    ಪೂರ್ಣಾಙ್ಕ index; /* Finally fall back to index */
} VulkanDeviceSelection;

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *vk_dev_type(ಗಣನಾ VkPhysicalDeviceType type)
{
    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: ಪ್ರತ್ಯಾಗಮ "integrated";
    ಪಕ್ಷ VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   ಪ್ರತ್ಯಾಗಮ "discrete";
    ಪಕ್ಷ VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    ಪ್ರತ್ಯಾಗಮ "virtual";
    ಪಕ್ಷ VK_PHYSICAL_DEVICE_TYPE_CPU:            ಪ್ರತ್ಯಾಗಮ "software";
    ಸ್ವಭಾವ:                                     ಪ್ರತ್ಯಾಗಮ "unknown";
    }
}

/* Finds a device */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ find_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0, choice = -1;
    uint32_t ಅಂಕೆ;
    VkResult ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = ರಿಕ್ತ;
    VkPhysicalDeviceIDProperties *idp = ರಿಕ್ತ;
    VkPhysicalDeviceProperties2 *prop = ರಿಕ್ತ;
    VkPhysicalDeviceDriverProperties *driver_prop = ರಿಕ್ತ;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = ರಿಕ್ತ;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ಅಂಕೆ, ರಿಕ್ತ);
    ಯದಿ (ret != VK_SUCCESS || !ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENODEV);
    }

    devices = av_malloc_array(ಅಂಕೆ, ಪರಿಮಾಣ(VkPhysicalDevice));
    ಯದಿ (!devices)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ಅಂಕೆ, devices);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    }

    prop = av_calloc(ಅಂಕೆ, ಪರಿಮಾಣ(*prop));
    ಯದಿ (!prop) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ end;
    }

    idp = av_calloc(ಅಂಕೆ, ಪರಿಮಾಣ(*idp));
    ಯದಿ (!idp) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ end;
    }

    driver_prop = av_calloc(ಅಂಕೆ, ಪರಿಮಾಣ(*driver_prop));
    ಯದಿ (!driver_prop) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ end;
    }

    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(ಅಂಕೆ, ಪರಿಮಾಣ(*drm_prop));
        ಯದಿ (!drm_prop) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ end;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].pNext = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].pNext = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].pNext = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    ಯದಿ (select->has_uuid) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
            ಯದಿ (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_SIZE)) {
                choice = i;
                ಗಚ್ಛ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    } ಅನ್ಯಥಾ ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
            ಯದಿ ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                ಗಚ್ಛ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    } ಅನ್ಯಥಾ ಯದಿ (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
            ಯದಿ (strstr(prop[i].properties.deviceName, select->name)) {
                choice = i;
                ಗಚ್ಛ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    } ಅನ್ಯಥಾ ಯದಿ (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
            ಯದಿ (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                ಗಚ್ಛ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        ಗಚ್ಛ end;
    } ಅನ್ಯಥಾ ಯದಿ (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
            ಯದಿ (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                ಗಚ್ಛ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    } ಅನ್ಯಥಾ {
        ಯದಿ (select->index < ಅಂಕೆ) {
            choice = select->index;
            ಗಚ್ಛ end;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->index);
        err = AVERROR(ENODEV);
        ಗಚ್ಛ end;
    }

end:
    ಯದಿ (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.pNext = ರಿಕ್ತ;
        p->dprops = driver_prop[choice];
        p->dprops.pNext = ರಿಕ್ತ;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    ಪ್ರತ್ಯಾಗಮ err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ pick_queue_family(VkQueueFamilyProperties2 *qf, uint32_t ಅಂಕೆ_qf,
                                    VkQueueFlagBits flags)
{
    ಪೂರ್ಣಾಙ್ಕ index = -1;
    uint32_t min_score = UINT32_MAX;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_qf; i++) {
        VkQueueFlagBits qflags = qf[i].queueFamilyProperties.queueFlags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        ಯದಿ ((flags & VK_QUEUE_TRANSFER_BIT) &&
            (qflags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            qflags |= VK_QUEUE_TRANSFER_BIT;

        ಯದಿ (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].queueFamilyProperties.timestampValidBits;
            ಯದಿ (score < min_score) {
                index = i;
                min_score = score;
            }
        }
    }

    ಯದಿ (index > -1)
        qf[index].queueFamilyProperties.timestampValidBits++;

    ಪ್ರತ್ಯಾಗಮ index;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ pick_video_queue_family(VkQueueFamilyProperties2 *qf,
                                          VkQueueFamilyVideoPropertiesKHR *qf_vid, uint32_t ಅಂಕೆ_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    ಪೂರ್ಣಾಙ್ಕ index = -1;
    uint32_t min_score = UINT32_MAX;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_qf; i++) {
        ಧ್ರುವ VkQueueFlags qflags = qf[i].queueFamilyProperties.queueFlags;
        ಧ್ರುವ VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        ಯದಿ (!(qflags & (VK_QUEUE_VIDEO_ENCODE_BIT_KHR | VK_QUEUE_VIDEO_DECODE_BIT_KHR)))
            ಅನುವರ್ತ;

        ಯದಿ (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].queueFamilyProperties.timestampValidBits;
            ಯದಿ (score < min_score) {
                index = i;
                min_score = score;
            }
        }
    }

    ಯದಿ (index > -1)
        qf[index].queueFamilyProperties.timestampValidBits++;

    ಪ್ರತ್ಯಾಗಮ index;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ setup_queue_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t ಅಂಕೆ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    VkQueueFamilyProperties2 *qf = ರಿಕ್ತ;
    VkQueueFamilyVideoPropertiesKHR *qf_vid = ರಿಕ್ತ;

    /* First get the number of queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &ಅಂಕೆ, ರಿಕ್ತ);
    ಯದಿ (!ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(ಅಂಕೆ, ಪರಿಮಾಣ(VkQueueFamilyProperties2));
    ಯದಿ (!qf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(ಅಂಕೆ, ಪರಿಮಾಣ(VkQueueFamilyVideoPropertiesKHR));
    ಯದಿ (!qf_vid)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (uint32_t i = 0; i < ಅಂಕೆ; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .pNext = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : ರಿಕ್ತ,
        };
    }

    /* Finally retrieve the queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &ಅಂಕೆ, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_GRAPHICS_BIT) ? " graphics" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_COMPUTE_BIT) ? " compute" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_TRANSFER_BIT) ? " transfer" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) ? " encode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_DECODE_BIT_KHR) ? " decode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_SPARSE_BINDING_BIT) ? " sparse" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_OPTICAL_FLOW_BIT_NV) ? " optical_flow" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_PROTECTED_BIT) ? " protected" : "",
               qf[i].queueFamilyProperties.queue_ಎಣಿಕೆ);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].queueFamilyProperties.timestampValidBits = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->queue_flags = 0;
#ifdef VK_KHR_internally_synchronized_queues
    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)
        hwctx->queue_flags |= VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR;
#endif

    /* Pick each queue family to use. */
#define PICK_QF(type, vid_op)                                            \
    ಕುರು {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        ಯದಿ (vid_op)                                                      \
            idx = pick_video_queue_family(qf, qf_vid, ಅಂಕೆ, vid_op);      \
        ಅನ್ಯಥಾ                                                             \
            idx = pick_queue_family(qf, ಅಂಕೆ, type);                      \
                                                                         \
        ಯದಿ (idx == -1)                                                   \
            ಅನುವರ್ತ;                                                    \
                                                                         \
        ಪ್ರತಿ (i = 0; i < hwctx->nb_qf; i++) {                             \
            ಯದಿ (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                ಭಙ್ಗ;                                                   \
            }                                                            \
        }                                                                \
        ಯದಿ (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].ಅಂಕೆ = qf[idx].queueFamilyProperties.queue_ಎಣಿಕೆ; \
            ಯದಿ (p->limit_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                ಪೂರ್ಣಾಙ್ಕ max = p->limit_queues;                               \
                ಯದಿ (type == VK_QUEUE_GRAPHICS_BIT)                       \
                    hwctx->qf[i].ಅಂಕೆ = FFMIN(hwctx->qf[i].ಅಂಕೆ,           \
                                             max ? max : 1);             \
                ಅನ್ಯಥಾ ಯದಿ (max)                                            \
                    hwctx->qf[i].ಅಂಕೆ = FFMIN(hwctx->qf[i].ಅಂಕೆ, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } ಯಾವತ್ (0)

    PICK_QF(VK_QUEUE_GRAPHICS_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_COMPUTE_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_TRANSFER_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR);

#ifdef VK_KHR_video_decode_vp9
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR);
#endif

#ifdef VK_KHR_video_encode_av1
    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR);
#endif
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR);

    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_QUEUE_OPTICAL_FLOW_BIT_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#undef PICK_QF

    cd->pQueueCreateInfos = av_malloc_array(hwctx->nb_qf,
                                            ಪರಿಮಾಣ(VkDeviceQueueCreateInfo));
    ಯದಿ (!cd->pQueueCreateInfos)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        ಪೂರ್ಣಾಙ್ಕ dup = 0;
        ಭಿನ್ನ *weights = ರಿಕ್ತ;
        VkDeviceQueueCreateInfo *pc;
        ಪ್ರತಿ (uint32_t j = 0; j < cd->queue_Create_Info_ಎಣಿಕೆ; j++) {
            ಯದಿ (hwctx->qf[i].idx == cd->pQueueCreateInfos[j].queueFamilyIndex) {
                dup = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (dup)
            ಅನುವರ್ತ;

        weights = av_malloc_array(hwctx->qf[i].ಅಂಕೆ, ಪರಿಮಾಣ(ಭಿನ್ನ));
        ಯದಿ (!weights) {
            ಪ್ರತಿ (uint32_t j = 0; j < cd->queue_Create_Info_ಎಣಿಕೆ; j++)
                av_free((ಶೂನ್ಯ *)cd->pQueueCreateInfos[i].pQueuePriorities);
            av_free((ಶೂನ್ಯ *)cd->pQueueCreateInfos);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }

        ಪ್ರತಿ (uint32_t j = 0; j < hwctx->qf[i].ಅಂಕೆ; j++)
            weights[j] = 1.0;

        pc = (VkDeviceQueueCreateInfo *)cd->pQueueCreateInfos;
        pc[cd->queue_Create_Info_ಎಣಿಕೆ++] = (VkDeviceQueueCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .flags = hwctx->queue_flags,
            .queueFamilyIndex = hwctx->qf[i].idx,
            .queue_ಎಣಿಕೆ = hwctx->qf[i].ಅಂಕೆ,
            .pQueuePriorities = weights,
        };
    }

    ಪ್ರತ್ಯಾಗಮ 0;
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

    ಯದಿ (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    ಯದಿ (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    ಯದಿ (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    ಯದಿ (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    ಯದಿ (p->qf_mutex) {
        ಪ್ರತಿ (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_device_create_internal(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         ಪೂರ್ಣಾಙ್ಕ disable_multiplane,
                                         AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    AVDictionaryEntry *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಗಣನಾ FFVulkanDebugMode debug_mode = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    ಯದಿ ((err = create_instance(ctx, opts, &debug_mode)))
        ಗಚ್ಛ end;

    /* Find a physical device (if not given one) */
    ಯದಿ ((err = find_device(ctx, dev_select)))
        ಗಚ್ಛ end;

    /* Get supported memory types */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    ಯದಿ ((err = check_extensions(ctx, 1, opts, &dev_info.ppEnabledExtensionNames,
                                &dev_info.enabled_Extension_ಎಣಿಕೆ, debug_mode))) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dev_info.queue_Create_Info_ಎಣಿಕೆ; i++)
            av_free((ಶೂನ್ಯ *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
        av_free((ಶೂನ್ಯ *)dev_info.pQueueCreateInfos);
        ಗಚ್ಛ end;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.pNext = p->feats.device.pNext;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", ರಿಕ್ತ, 0);
    ಯದಿ (opt_d)
        p->limit_queues = strtol(opt_d->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);

    /* Setup enabled queue families */
    ಯದಿ ((err = setup_queue_families(ctx, &dev_info)))
        ಗಚ್ಛ end;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dev_info.queue_Create_Info_ಎಣಿಕೆ; i++)
        av_free((ಶೂನ್ಯ *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
    av_free((ಶೂನ್ಯ *)dev_info.pQueueCreateInfos);

    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dev_info.enabled_Extension_ಎಣಿಕೆ; i++)
            av_free((ಶೂನ್ಯ *)dev_info.ppEnabledExtensionNames[i]);
        av_free((ಶೂನ್ಯ *)dev_info.ppEnabledExtensionNames);
        err = AVERROR_EXTERNAL;
        ಗಚ್ಛ end;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", ರಿಕ್ತ, 0);
    ಯದಿ (opt_d)
        p->use_linear_images = strtol(opt_d->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    ಯದಿ (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", ರಿಕ್ತ, 0);
        ಯದಿ (opt_d)
            p->disable_multiplane = strtol(opt_d->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", ರಿಕ್ತ, 0);
    ಯದಿ (opt_d)
        p->avoid_host_import = strtol(opt_d->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.ppEnabledExtensionNames;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_ಎಣಿಕೆ;

    /* The extension lists need to be freed */
    ctx->ಮುಕ್ತ = vulkan_device_free;

end:
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಶೂನ್ಯ lock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t index)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ಯದಿ (p->qf_mutex)
        pthread_mutex_lock(&p->qf_mutex[queue_family][index]);
}

ಸ್ಥಿರ ಶೂನ್ಯ unlock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t index)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ಯದಿ (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[queue_family][index]);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_device_init(AVHWDeviceContext *ctx)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    uint32_t qf_ಅಂಕೆ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkQueueFamilyProperties2 *qf;
    VkQueueFamilyVideoPropertiesKHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            ಯದಿ (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                ಭಙ್ಗ;
            }
        }
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    ಯದಿ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        ಪ್ರತ್ಯಾಗಮ err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.pNext = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    p->hprops.pNext = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimalBufferCopyRowPitchAlignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.minMemoryMapAlignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.nonCoherentAtomSize);
    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.minImportedHostPointerAlignment);

    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &qf_ಅಂಕೆ, ರಿಕ್ತ);
    ಯದಿ (!qf_ಅಂಕೆ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#ifdef _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT;
#ಅನ್ಯಥಾ
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;
#endif
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_ಅಂಕೆ, ಪರಿಮಾಣ(VkQueueFamilyProperties2));
    ಯದಿ (!qf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_ಅಂಕೆ, ಪರಿಮಾಣ(VkQueueFamilyVideoPropertiesKHR));
    ಯದಿ (!qf_vid) {
        av_free(qf);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ಪ್ರತಿ (uint32_t i = 0; i < qf_ಅಂಕೆ; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .pNext = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : ರಿಕ್ತ,
        };
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &qf_ಅಂಕೆ, qf);

    p->nb_tot_qfs = qf_ಅಂಕೆ;

    ಯದಿ (!(p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)) {
        p->qf_mutex = av_calloc(qf_ಅಂಕೆ, ಪರಿಮಾಣ(*p->qf_mutex));
        ಯದಿ (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ end;
        }

        ಪ್ರತಿ (uint32_t i = 0; i < qf_ಅಂಕೆ; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].queueFamilyProperties.queue_ಎಣಿಕೆ,
                                       ಪರಿಮಾಣ(**p->qf_mutex));
            ಯದಿ (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                ಗಚ್ಛ end;
            }
            ಪ್ರತಿ (uint32_t j = 0; j < qf[i].queueFamilyProperties.queue_ಎಣಿಕೆ; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], ರಿಕ್ತ);
                ಯದಿ (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    ಗಚ್ಛ end;
                }
            }
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < hwctx->nb_qf; i++) {
        ಯದಿ (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                  VK_QUEUE_VIDEO_ENCODE_BIT_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < hwctx->nb_qf; i++) {
        ಪೂರ್ಣಾಙ್ಕ seen = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = (i - 1); j >= 0; j--) {
            ಯದಿ (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                seen = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!seen)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#ಯದಿ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    ಯದಿ (!hwctx->lock_queue)
        hwctx->lock_queue = lock_queue;
    ಯದಿ (!hwctx->unlock_queue)
        hwctx->unlock_queue = unlock_queue;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    /* Re-query device capabilities, in case the device was created externally */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_load_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_COMPUTE_BIT, 0);
    p->transfer_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_TRANSFER_BIT, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_offset_align = 1;
    ಯದಿ (p->transfer_qf) {
        VkQueueFlags flags = p->vkctx.qf_props[p->transfer_qf->idx].queueFamilyProperties.queueFlags;
        ಯದಿ (!(flags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            p->transfer_offset_align = 4;
    }
#ifdef VK_KHR_maintenance11
    ಯದಿ (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_offset_align = 1;
#endif

    /* Re-query device capabilities, in case the device was created externally */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

end:
    av_free(qf_vid);
    av_free(qf);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                                AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    ಯದಿ (device && device[0]) {
        ವರ್ಣ *end = ರಿಕ್ತ;

        ಯದಿ (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } ಅನ್ಯಥಾ {
            dev_select.index = strtol(device, &end, 10);
            ಯದಿ (end == device || *end) {
                dev_select.index = 0;
                dev_select.name  = device;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_unused VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    ವಿಕಲ್ಪ(src_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#ಯದಿ VA_CHECK_VERSION(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#endif
        ಧ್ರುವ ವರ್ಣ *vendor;

#ಯದಿ VA_CHECK_VERSION(1, 15, 0)
        vas = vaGetDisplayAttributes(dpy, &attr, 1);
        ಯದಿ (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.ಮೌಲ್ಯ & 0xFFFF);
#endif

        ಯದಿ (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            ಯದಿ (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
            }

            ಯದಿ (strstr(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        ಪ್ರತ್ಯಾಗಮ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#endif
#ಯದಿ CONFIG_LIBDRM
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DRM: {
        ಪೂರ್ಣಾಙ್ಕ err;
        ಸಂರಚನಾ stat drm_ಗಂಟು_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ಗಂಟು_info);
        ಯದಿ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ಗಂಟು_info.st_dev);
        dev_select.drm_minor = minor(drm_ಗಂಟು_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        ಯದಿ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        ಯದಿ (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        ಪ್ರತ್ಯಾಗಮ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#endif
#ಯದಿ CONFIG_CUDA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADeviceContextInternal *cu_internal = src_hwctx->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        ಪೂರ್ಣಾಙ್ಕ ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_internal->cuda_device));
        ಯದಿ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        ಪ್ರತ್ಯಾಗಮ vulkan_device_create_internal(ctx, &dev_select, 1, opts, flags);
    }
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_frames_get_constraints(AVHWDeviceContext *ctx,
                                         ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    ಪ್ರತಿ (ಗಣನಾ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ಎಣಿಕೆ += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(ಎಣಿಕೆ + 1 + CONFIG_CUDA,
                                                    ಪರಿಮಾಣ(ಗಣನಾ AVPixelFormat));
    ಯದಿ (!constraints->valid_sw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಎಣಿಕೆ = 0;
    ಪ್ರತಿ (ಗಣನಾ AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ಯದಿ (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[ಎಣಿಕೆ++] = vk_formats_list[i].pixfmt;
        }
    }

#ಯದಿ CONFIG_CUDA
    constraints->valid_sw_formats[ಎಣಿಕೆ++] = AV_PIX_FMT_CUDA;
#endif

    constraints->valid_sw_formats[ಎಣಿಕೆ++] = AV_PIX_FMT_NONE;

    constraints->min_width  = 1;
    constraints->min_height = 1;
    constraints->max_width  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_height = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(ಗಣನಾ AVPixelFormat));
    ಯದಿ (!constraints->valid_hw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ alloc_mem(AVHWDeviceContext *ctx, VkMemoryRequirements *req,
                     VkMemoryPropertyFlagBits req_flags, ಧ್ರುವ ಶೂನ್ಯ *alloc_extension,
                     VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    VkResult ret;
    ಪೂರ್ಣಾಙ್ಕ index = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkMemoryAllocateInfo alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext          = alloc_extension,
        .allocationSize = req->size,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < p->mprops.memory_Type_ಎಣಿಕೆ; i++) {
        ಧ್ರುವ VkMemoryType *type = &p->mprops.memoryTypes[i];

        /* The memory type must be supported by the requirements (bitfield) */
        ಯದಿ (!(req->memoryTypeBits & (1 << i)))
            ಅನುವರ್ತ;

        /* The memory type flags must include our properties */
        ಯದಿ ((type->propertyFlags & req_flags) != req_flags)
            ಅನುವರ್ತ;

        /* The memory type must be large enough */
        ಯದಿ (req->size > p->mprops.memoryHeaps[type->heapIndex].size)
            ಅನುವರ್ತ;

        /* Found a suitable memory type */
        index = i;
        ಭಙ್ಗ;
    }

    ಯದಿ (index < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    alloc_info.memoryTypeIndex = index;

    ret = vk->AllocateMemory(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.memoryTypes[index].propertyFlags;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_free_internal(VulkanDevicePriv *p, AVVkFrame *f)
{
    av_unused AVVkFrameInternal *internal = f->internal;

    // Make this function safe to call repeatedly
    ಯದಿ (!internal)
        ಪ್ರತ್ಯಾಗಮ;

#ಯದಿ CONFIG_CUDA
    ಯದಿ (internal->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)internal->cuda_fc_ref->data;
        ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
            ಯದಿ (internal->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(internal->cu_sem[i]));
            ಯದಿ (internal->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(internal->cu_mma[i]));
            ಯದಿ (internal->ext_mem[i])
                CHECK_CU(cu->cuDestroyExternalMemory(internal->ext_mem[i]));
#ifdef _WIN32
            ಯದಿ (internal->ext_sem_handle[i])
                CloseHandle(internal->ext_sem_handle[i]);
            ಯದಿ (internal->ext_mem_handle[i])
                CloseHandle(internal->ext_mem_handle[i]);
#endif
        }

        av_buffer_unref(&internal->cuda_fc_ref);
    }
#endif

    ಯದಿ (internal->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, internal->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&internal->update_mutex);
    av_freep(&f->internal);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_frame_free(AVHWFramesContext *hwfc, AVVkFrame *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(f);
    ಪೂರ್ಣಾಙ್ಕ nb_sems = 0;

    ಯಾವತ್ (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    ಯದಿ (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_ಮೌಲ್ಯಗಳು        = f->sem_ಮೌಲ್ಯ,
            .semaphore_ಎಣಿಕೆ = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_internal(p, f);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->FreeMemory(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_frame_free_cb(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    vulkan_frame_free(opaque, (AVVkFrame*)data);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ alloc_bind_mem(AVHWFramesContext *hwfc, AVVkFrame *f,
                          ಶೂನ್ಯ *alloc_pnext, size_t alloc_pnext_stride)
{
    ಪೂರ್ಣಾಙ್ಕ img_cnt = 0, err;
    VkResult ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkBindImageMemoryInfo bind_info[AV_ಅಂಕೆ_DATA_POINTERS] = { { 0 } };

    ಯಾವತ್ (f->img[img_cnt]) {
        ಪೂರ್ಣಾಙ್ಕ use_ded_mem;
        VkImageMemoryRequirementsInfo2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        VkMemoryDedicatedAllocateInfo ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .pNext = (ಶೂನ್ಯ *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        VkMemoryDedicatedRequirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
        };
        VkMemoryRequirements2 req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
            .pNext = &ded_req,
        };

        vk->GetImageMemoryRequirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefersDedicatedAllocation, ded_req.requiresDedicatedAllocation);

        ಯದಿ (f->tiling == VK_IMAGE_TILING_LINEAR)
            req.memoryRequirements.size = FFALIGN(req.memoryRequirements.size,
                                                  p->props.properties.limits.minMemoryMapAlignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefersDedicatedAllocation |
                      ded_req.requiresDedicatedAllocation;
        ಯದಿ (((VulkanFramesPriv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        ಯದಿ (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        ಯದಿ ((err = alloc_mem(ctx, &req.memoryRequirements,
                             f->tiling == VK_IMAGE_TILING_LINEAR ?
                             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT :
                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                             use_ded_mem ? &ded_alloc : (ಶೂನ್ಯ *)ded_alloc.pNext,
                             &f->flags, &f->mem[img_cnt])))
            ಪ್ರತ್ಯಾಗಮ err;

        f->size[img_cnt] = req.memoryRequirements.size;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].memory = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಗಣನಾ PrepMode {
    PREP_MODE_GENERAL,
    PREP_MODE_WRITE,
    PREP_MODE_EXTERNAL_EXPORT,
    PREP_MODE_EXTERNAL_IMPORT,
    PREP_MODE_DECODING_DST,
    PREP_MODE_DECODING_DPB,
    PREP_MODE_ENCODING_DPB,
};

ಸ್ಥಿರ ಶೂನ್ಯ switch_new_props(ಗಣನಾ PrepMode pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    ವಿಕಲ್ಪ (pmode) {
    ಪಕ್ಷ PREP_MODE_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ PREP_MODE_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, ಗಣನಾ PrepMode pmode)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkImageMemoryBarrier2 img_bar[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    ಯದಿ (pmode == PREP_MODE_EXTERNAL_EXPORT) {
        dst_qf     = VK_QUEUE_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .data = (uint8_t *)hwfc,
    };
    AVFrame tmp_frame = {
        .data[0] = (uint8_t *)frame,
        .hw_frames_ctx = &tmp_ref,
    };

    VkCommandBuffer cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_start(&p->vkctx, exec);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, &tmp_frame,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    ff_vk_frame_barrier(&p->vkctx, exec, &tmp_frame, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .pImageMemoryBarriers = img_bar,
            .image_Memory_Barrier_ಎಣಿಕೆ = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVkFrame *frame, ಗಣನಾ PrepMode pmode)
{
    VkResult ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(frame);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_ಎಣಿಕೆ; i++) {
        ಯದಿ (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            ಭಙ್ಗ;
    }
    ಯದಿ (i == p->vkctx.host_image_props.copy_Dst_Layout_ಎಣಿಕೆ)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOTSUP);

    ಪ್ರತಿ (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = frame->img[i],
            .oldLayout = frame->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.layer_ಎಣಿಕೆ = 1,
            .subresourceRange.level_ಎಣಿಕೆ = 1,
        };
        frame->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ prepare_frame(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, ಗಣನಾ PrepMode pmode)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    AVVulkanFramesContext *hwfc_vk = hwfc->hwctx;
    ಯದಿ (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT &&
        (pmode != PREP_MODE_EXTERNAL_EXPORT) &&
        (pmode != PREP_MODE_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, frame, pmode);
        ಯದಿ (err != AVERROR(ENOTSUP))
            ಪ್ರತ್ಯಾಗಮ err;
    }

    ಪ್ರತ್ಯಾಗಮ switch_layout(hwfc, ectx, frame, pmode);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ get_plane_wh(uint32_t *w, uint32_t *h, ಗಣನಾ AVPixelFormat format,
                                ಪೂರ್ಣಾಙ್ಕ frame_w, ಪೂರ್ಣಾಙ್ಕ frame_h, ಪೂರ್ಣಾಙ್ಕ plane)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    ಯದಿ (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = frame_w;
        *h = frame_h;
        ಪ್ರತ್ಯಾಗಮ;
    }

    *w = AV_CEIL_RSHIFT(frame_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(frame_h, desc->log2_chroma_h);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ create_frame(AVHWFramesContext *hwfc, AVVkFrame **frame,
                        VkImageTiling tiling, VkImageUsageFlagBits usage,
                        VkImageCreateFlags flags, ಪೂರ್ಣಾಙ್ಕ nb_layers,
                        ಶೂನ್ಯ *create_pnext)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    AVVulkanFramesContext *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVkFrame *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_ಮೌಲ್ಯ  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#ifdef _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
#ಅನ್ಯಥಾ
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
#endif
    };

    /* Check if exporting is supported before chaining any structs */
    ಯದಿ (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT) {
        ಯದಿ (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_frame_alloc();
    ಯದಿ (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.depth          = 1,
            .mipLevels             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_ಎಣಿಕೆ_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, hwfc->width, hwfc->height, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }

        f->queue_family[i] = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ಮೌಲ್ಯ[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *frame = f;
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    vulkan_frame_free(hwfc, f);
    ಪ್ರತ್ಯಾಗಮ err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
ಸ್ಥಿರ ಶೂನ್ಯ try_export_flags(AVHWFramesContext *hwfc,
                             VkExternalMemoryHandleTypeFlags *comp_handle_types,
                             VkExternalMemoryHandleTypeFlags *iexp,
                             VkExternalMemoryHandleTypeFlagBits exp)
{
    VkResult ret;
    AVVulkanFramesContext *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಧ್ರುವ VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ಪೂರ್ಣಾಙ್ಕ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    ಪೂರ್ಣಾಙ್ಕ nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .pNext = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pNext = ರಿಕ್ತ,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_Index_ಎಣಿಕೆ = p->nb_img_qfs,
        .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                     VK_SHARING_MODE_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = exp,
        .pNext = has_mods ? &phy_dev_mod_info : ರಿಕ್ತ,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .pNext  = !exp ? ರಿಕ್ತ : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_BIT),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_ಎಣಿಕೆ : 1;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_mods; i++) {
        ಯದಿ (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        ಯದಿ (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (unsigned long long)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        ಯದಿ (ret == VK_SUCCESS) {
            *iexp |= exp;
            *comp_handle_types |= eprops.externalMemoryProperties.compatibleHandleTypes;
            ಯದಿ (exp == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT) {
                VulkanFramesPriv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.externalMemoryProperties.externalMemoryFeatures &
                                                  VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
ಸ್ಥಿರ ಶೂನ್ಯ get_export_handle_types(AVHWFramesContext *hwfc,
                                    VkExternalMemoryHandleTypeFlags *comp_handle_types,
                                    VkExternalMemoryHandleTypeFlags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_unused AVVulkanFramesContext *hwctx = &((VulkanFramesPriv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#ifdef _WIN32
    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT
                             : VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT);
#ಅನ್ಯಥಾ
    ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);

    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_MEMORY &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT);
#endif
}

ಸ್ಥಿರ AVBufferRef *vulkan_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    AVVkFrame *f;
    AVBufferRef *avbuf = ರಿಕ್ತ;
    AVHWFramesContext *hwfc = opaque;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VkExternalMemoryHandleTypeFlags e;
    VkExportMemoryAllocateInfo eminfo[AV_ಅಂಕೆ_DATA_POINTERS];

    VkExternalMemoryImageCreateInfo eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
        .pNext       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
        eminfo[i].pNext       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    ಯದಿ (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, ಪರಿಮಾಣ(*eminfo));
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    ಯದಿ ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR))
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DPB);
    ಅನ್ಯಥಾ ಯದಿ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DST);
    ಅನ್ಯಥಾ ಯದಿ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_ENCODING_DPB);
    ಅನ್ಯಥಾ ಯದಿ (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_WRITE);
    ಅನ್ಯಥಾ
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_GENERAL);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    avbuf = av_buffer_create((uint8_t *)f, ಪರಿಮಾಣ(AVVkFrame),
                             vulkan_frame_free_cb, hwfc, 0);
    ಯದಿ (!avbuf)
        ಗಚ್ಛ fail;

    ಪ್ರತ್ಯಾಗಮ avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_frame_free(hwfc, f);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ lock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_lock(&vkf->internal->update_mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ unlock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_unlock(&vkf->internal->update_mutex);
}

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_frames_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;

    ಯದಿ (fp->modifier_info) {
        ಯದಿ (fp->modifier_info->pDrmFormatModifiers)
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
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkResult ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    ಧ್ರುವ ಸಂರಚನಾ FFVkFormatEntry *fmt = vk_find_format_entry(hwfc->sw_format);
    ಯದಿ (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಧ್ರುವ VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ಪೂರ್ಣಾಙ್ಕ has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ nb_mods = has_mods ? mod_list->drm_Format_Modifier_ಎಣಿಕೆ : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    ಯದಿ (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        ಪ್ರತ್ಯಾಗಮ 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_Index_ಎಣಿಕೆ = p->nb_img_qfs,
        .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                     VK_SHARING_MODE_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    ಯದಿ (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ಧ್ರುವ VkVideoProfileListInfoKHR *pl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    ಯದಿ (pl) {
        profile_list = *pl;
        profile_list.pNext = ರಿಕ್ತ;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ಧ್ರುವ VkImageFormatListCreateInfo *fl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    ಯದಿ (fl) {
        format_list = *fl;
        format_list.pNext = ರಿಕ್ತ;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AV_ಅಂಕೆ_DATA_POINTERS &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .pNext = &perf,
            };

            ಯದಿ (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            ಯದಿ (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                ಪ್ರತ್ಯಾಗಮ 0;
            }

            ಯದಿ (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identicalMemoryLayout);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        }
    }

    ಯದಿ (!p->vkctx.host_image_props.identicalMemoryTypeRequirements) {
        ಪೂರ್ಣಾಙ್ಕ index;
        VkExternalMemoryHandleTypeFlags e;
        VkExternalMemoryImageCreateInfo eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
            .pNext       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->width, hwfc->height, 1 },
            .mipLevels   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_ಎಣಿಕೆ_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };
        VkDeviceImageMemoryRequirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT : 0,
        };
        VkMemoryRequirements2 req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
        };

        vk->GetDeviceImageMemoryRequirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        VkMemoryPropertyFlags req_flags = hwctx->tiling == VK_IMAGE_TILING_LINEAR ?
                                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT :
                                          VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        ಪ್ರತಿ (index = 0; index < p->mprops.memory_Type_ಎಣಿಕೆ; index++) {
            ಯದಿ (!(req.memoryRequirements.memoryTypeBits & (1U << index)))
                ಅನುವರ್ತ;
            ಯದಿ ((p->mprops.memoryTypes[index].propertyFlags & req_flags) == req_flags)
                ಭಙ್ಗ;
        }
        ಯದಿ (index == p->mprops.memory_Type_ಎಣಿಕೆ) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_frames_init(AVHWFramesContext *hwfc)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    AVVkFrame *f;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಧ್ರುವ ಸಂರಚನಾ FFVkFormatEntry *fmt;
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    ಪೂರ್ಣಾಙ್ಕ disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_FRAME_FLAG_DISABLE_MULTIPLANE);
    ಪೂರ್ಣಾಙ್ಕ is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)));

    /* Defaults */
    ಯದಿ (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    ಯದಿ (p->use_linear_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_LINEAR;


    fmt = vk_find_format_entry(hwfc->sw_format);
    ಯದಿ (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಯದಿ ((hwfc->width  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->height & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    ಯದಿ (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        ಯದಿ (hwctx->format[0] != fmt->vkf) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < fmt->nb_images_fallback; i++) {
                ಯದಿ (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, ರಿಕ್ತ,
                                 ರಿಕ್ತ, ರಿಕ್ತ, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        ಯದಿ (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    } ಅನ್ಯಥಾ {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, ರಿಕ್ತ,
                                 ರಿಕ್ತ, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    ಪೂರ್ಣಾಙ್ಕ drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_find_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    ಯದಿ (!is_lone_dpb && !drm_mod_with_video) {
        /* Image usage flags */
        hwctx->usage |= supported_usage & (VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                                           VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                           VK_IMAGE_USAGE_STORAGE_BIT      |
                                           VK_IMAGE_USAGE_SAMPLED_BIT);

        /* Frames which may double as active references (coinciding decode
         * output) cannot support host transfers: decode submissions bake the
         * image layout into their barriers at record time, so a host-side
         * layout transition cannot be synchronized against them, not even
         * by the frame lock and timeline semaphore. */
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        ಯದಿ ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        ಯದಿ (!hwctx->img_flags) {
            ಪೂರ್ಣಾಙ್ಕ sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_BIT |
                                             VK_IMAGE_USAGE_STORAGE_BIT);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
            ಯದಿ (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_BIT;
                ಯದಿ ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_BIT;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    ಯದಿ ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ಧ್ರುವ VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_find_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        ಯದಿ (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        } ಅನ್ಯಥಾ {
            uint32_t i;
            ಪ್ರತಿ (i = 0; i < pl->profile_ಎಣಿಕೆ; i++) {
                /* Video ops start at exactly 0x00010000 */
                ಯದಿ (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    ಭಙ್ಗ;
            }
            ಯದಿ (i == pl->profile_ಎಣಿಕೆ)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    ಯದಿ ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

    ಯದಿ (!hwctx->lock_frame)
        hwctx->lock_frame = lock_frame;

    ಯದಿ (!hwctx->unlock_frame)
        hwctx->unlock_frame = unlock_frame;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, ರಿಕ್ತ);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, ರಿಕ್ತ);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, ರಿಕ್ತ);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    /* Test to see if allocation will fail */
    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        ಯದಿ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_frame_free(hwfc, f);
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = ರಿಕ್ತ;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .pNext = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_ಎಣಿಕೆ, ಪರಿಮಾಣ(*modp.pDrmFormatModifierProperties));
            ಯದಿ (!modp.pDrmFormatModifierProperties) {
                vulkan_frame_free(hwfc, f);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            ಪ್ರತಿ (uint32_t j = 0; j < modp.drm_Format_Modifier_ಎಣಿಕೆ; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                ಯದಿ (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    ಭಙ್ಗ;
                }
            }

            ಯದಿ (mod_props == ರಿಕ್ತ) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_frame_free(hwfc, f);
                ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_frame_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    ಯದಿ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal = av_buffer_pool_init2(ಪರಿಮಾಣ(AVVkFrame),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(hwfc)->pool_internal)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VULKAN;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ಗಣನಾ AVHWFrameTransferDirection dir,
                                       ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts;
    ಪೂರ್ಣಾಙ್ಕ n = 2;

#ಯದಿ CONFIG_CUDA
    n++;
#endif
    fmts = av_malloc_array(n, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#ಯದಿ CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#endif
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ CONFIG_LIBDRM
ಸ್ಥಿರ ಶೂನ್ಯ vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_frame_free(hwfc, hwmap->priv);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
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
#ifdef DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#endif
};

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ VkFormat drm_to_vulkan_fmt(uint32_t drm_fourcc)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ಯದಿ (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            ಪ್ರತ್ಯಾಗಮ vulkan_drm_format_map[i].vk_format;
    ಪ್ರತ್ಯಾಗಮ VK_FORMAT_UNDEFINED;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_from_drm_frame_desc(AVHWFramesContext *hwfc, AVVkFrame **frame,
                                          ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    AVVkFrame *f;
    ಪೂರ್ಣಾಙ್ಕ bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಧ್ರುವ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->data[0];
    VkBindImageMemoryInfo bind_info[AV_DRM_MAX_PLANES];
    VkBindImagePlaneMemoryInfo plane_info[AV_DRM_MAX_PLANES];

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_layers; i++) {
        ಯದಿ (drm_to_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಯದಿ (!(f = av_vk_frame_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_layers; i++) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_ಮೌಲ್ಯ  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_ಎಣಿಕೆ = planes,
            .pPlaneLayouts = (ಧ್ರುವ VkSubresourceLayout *)&ext_img_layouts,
        };
        VkExternalMemoryImageCreateInfo ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
            .pNext       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_to_vulkan_fmt(desc->layers[i].format),
            .extent.depth          = 1,
            .mipLevels             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_ಎಣಿಕೆ_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ಎಣಿಕೆ = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        ಯದಿ (planes == 1) {
            ಧ್ರುವ VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            ಯದಿ (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .pNext = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .pQueueFamilyIndices = create_info.pQueueFamilyIndices,
            .queue_Family_Index_ಎಣಿಕೆ = create_info.queue_Family_Index_ಎಣಿಕೆ,
            .sharingMode = create_info.sharingMode,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .pNext = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        ಯದಿ (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        ಯದಿ (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .pNext  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, src->width, src->height, i);

        /* Set the subresource layout based on the layer properties */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < planes; j++) {
            ext_img_layouts[j].offset     = desc->layers[i].planes[j].offset;
            ext_img_layouts[j].rowPitch   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].size       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].depthPitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ fail;
        }

        f->queue_family[i] = VK_QUEUE_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ಮೌಲ್ಯ[i] = 0;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        VkImageMemoryRequirementsInfo2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        VkMemoryDedicatedRequirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
        };
        VkMemoryRequirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
            .pNext = &ded_req,
        };

        /* Allocation/importing */
        VkMemoryFdPropertiesKHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        VkImportMemoryFdInfoKHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_index].fd),
            .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        VkMemoryDedicatedAllocateInfo ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .pNext = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->GetMemoryFdPropertiesKHR(hwctx->act_dev,
                                           VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
                                           idesc.fd, &fdmp);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            ಗಚ್ಛ fail;
        }

        vk->GetImageMemoryRequirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.memoryRequirements.memoryTypeBits = fdmp.memoryTypeBits;

        err = alloc_mem(ctx, &req2.memoryRequirements,
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                        (ded_req.prefersDedicatedAllocation ||
                         ded_req.requiresDedicatedAllocation) ?
                            &ded_alloc : ded_alloc.pNext,
                        &f->flags, &f->mem[i]);
        ಯದಿ (err) {
            close(idesc.fd);
            ಗಚ್ಛ fail;
        }

        f->size[i] = req2.memoryRequirements.size;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_layers; i++) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = desc->layers[i].nb_planes;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < planes; j++) {
            VkImageAspectFlagBits aspect = j == 0 ? VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT :
                                                    VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
            plane_info[bind_counts].pNext = ರಿಕ್ತ;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
            bind_info[bind_counts].pNext  = planes > 1 ? &plane_info[bind_counts] : ರಿಕ್ತ;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].memory = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].memoryOffset = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ಗಚ್ಛ fail;
    }

    *frame = f;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    vulkan_frame_free(hwfc, f);

    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_from_drm_frame_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ಧ್ರುವ AVDRMFrameDescriptor *desc, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ಯದಿ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        VkCommandBuffer cmd_buf;
        FFVkExecContext *exec;
        VkImageMemoryBarrier2 img_bar[AV_ಅಂಕೆ_DATA_POINTERS];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        ಪೂರ್ಣಾಙ್ಕ nb_img_bar = 0;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ದ್ವಿಮಾನ,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            ಸಂರಚನಾ dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            ಯದಿ (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                ಪ್ರತಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಪ್ರತ್ಯಾಗಮ err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            ಯದಿ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ಪ್ರತಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಪ್ರತ್ಯಾಗಮ err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_BIT,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            ಯದಿ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ಪ್ರತಿ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ಪ್ರತ್ಯಾಗಮ err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_start(&p->vkctx, exec);
        ಯದಿ (err < 0) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            ಪ್ರತ್ಯಾಗಮ err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_add_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        ಯದಿ (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            ಪ್ರತ್ಯಾಗಮ err;
        }

        ff_vk_frame_barrier(&p->vkctx, exec, dst, img_bar, &nb_img_bar,
                            VK_PIPELINE_STAGE_2_NONE,
                            VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                            ((flags & AV_HWFRAME_MAP_READ) ?
                             VK_ACCESS_2_SHADER_SAMPLED_READ_BIT : 0x0) |
                            ((flags & AV_HWFRAME_MAP_WRITE) ?
                             VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT : 0x0),
                            VK_IMAGE_LAYOUT_GENERAL,
                            p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0]);

        vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
                .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                .pImageMemoryBarriers = img_bar,
                .image_Memory_Barrier_ಎಣಿಕೆ = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
    } ಅನ್ಯಥಾ
#endif
    {
        AVVkFrame *f = (AVVkFrame *)dst->data[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_IMPORT);
        ಯದಿ (err)
            ಪ್ರತ್ಯಾಗಮ err;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    AVVkFrame *f;
    ಧ್ರುವ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->data[0];

    ಯದಿ ((err = vulkan_map_from_drm_frame_desc(hwfc, &f, src, flags)))
        ಪ್ರತ್ಯಾಗಮ err;

    /* The unmapping function will free this */
    dst->data[0] = (uint8_t *)f;
    dst->width   = src->width;
    dst->height  = src->height;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = vulkan_map_from_drm_frame_sync(hwfc, dst, desc, flags);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    vulkan_frame_free(hwfc->device_ctx->hwctx, f);
    dst->data[0] = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ err;
}

#ಯದಿ CONFIG_VAAPI
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ಧ್ರುವ AVFrame *src,
                                 ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    AVFrame *tmp = av_frame_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = av_hwframe_map(tmp, src, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif
#endif

#ಯದಿ CONFIG_CUDA
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ export_mem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, ಪೂರ್ಣಾಙ್ಕ idx,
                              VkDeviceMemory mem, size_t size)
{
    VkResult ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ifdef _WIN32
    CUDA_EXTERNAL_MEMORY_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .size = size,
    };
    VkMemoryGetWin32HandleInfoKHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR,
        .memory     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
    };

    ret = vk->GetMemoryWin32HandleKHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#ಅನ್ಯಥಾ
    CUDA_EXTERNAL_MEMORY_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD,
        .size = size,
    };
    VkMemoryGetFdInfoKHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
        .memory     = mem,
        .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR,
    };

    ret = vk->GetMemoryFdKHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }
#endif

    ret = CHECK_CU(cu->cuImportExternalMemory(&dst_int->ext_mem[idx], &ext_desc));
    ಯದಿ (ret < 0) {
#ifndef _WIN32
        close(ext_desc.handle.fd);
#endif
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ export_sem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, ಪೂರ್ಣಾಙ್ಕ idx,
                              VkSemaphore sem)
{
    VkResult ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ifdef _WIN32
    VkSemaphoreGetWin32HandleInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
        .semaphore = sem,
        .handleType = IsWindows8OrGreater()
                      ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
                      : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 10 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32 */,
    };
#ಅನ್ಯಥಾ
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#endif

#ifdef _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#ಅನ್ಯಥಾ
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#endif
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }
#ifdef _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#endif

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    ಯದಿ (ret < 0) {
#ifndef _WIN32
        close(ext_sem_desc.handle.fd);
#endif
        ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_export_to_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ಧ್ರುವ AVFrame *frame)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VkResult ret;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ಪೂರ್ಣಾಙ್ಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUarray_format cufmt = desc->comp[0].depth > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ elem_size = 1 + (desc->comp[0].depth > 8);

    dst_f = (AVVkFrame *)frame->data[0];
    dst_int = dst_f->internal;

    ಯದಿ (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_buffer_ref(cuda_hwfc);
        ಯದಿ (!dst_int->cuda_fc_ref)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
            err = export_mem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->size[i]);
            ಯದಿ (err < 0)
                ಗಚ್ಛ fail;

            err = export_sem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            ಯದಿ (err < 0)
                ಗಚ್ಛ fail;
        }

        ಯದಿ (nb_images != planes) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                ಯದಿ (desc->comp[i].step / elem_size > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    ಗಚ್ಛ fail;
                }

                VkImageSubresource subres = {
                    .aspectMask = i == 2 ? VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT :
                                           VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.offset;
            }
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
            CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC tex_desc = {
                .offset = offsets[i],
                .arrayDesc = {
                    .Depth = 0,
                    .Format = cufmt,
                    .ಅಂಕೆ_Channels = desc->comp[i].step / elem_size,
                    .Flags = 0,
                },
                .ಅಂಕೆ_Levels = 1,
            };
            ಪೂರ್ಣಾಙ್ಕ p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);
            tex_desc.arrayDesc.Width = p_w;
            tex_desc.arrayDesc.Height = p_h;

            ret = CHECK_CU(cu->cuExternalMemoryGetMappedMipmappedArray(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            ಯದಿ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ಗಚ್ಛ fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            ಯದಿ (ret < 0) {
                err = AVERROR_EXTERNAL;
                ಗಚ್ಛ fail;
            }

        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    vulkan_free_internal(p, dst_f);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_data_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಪೂರ್ಣಾಙ್ಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)dst->data[0];
    nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(cuda_dev->cuda_ctx));
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    err = vulkan_export_to_cuda(hwfc, src->hw_frames_ctx, dst);
    ಯದಿ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಪ್ರತ್ಯಾಗಮ err;
    }

    dst_int = dst_f->internal;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 0;
        s_s_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .srcMemoryType = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->data[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dstMemoryType = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        ಪೂರ್ಣಾಙ್ಕ p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = p_w * desc->comp[i].step;
        cpy.Height = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++)
        dst_f->sem_ಮೌಲ್ಯ[i]++;

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    ಪ್ರತ್ಯಾಗಮ err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_buffer_unref(&dst->buf[0]);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ವಿಕಲ್ಪ (src->format) {
#ಯದಿ CONFIG_LIBDRM
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಪ್ರತ್ಯಾಗಮ vulkan_map_from_vaapi(hwfc, dst, src, flags);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಪ್ರತ್ಯಾಗಮ vulkan_map_from_drm(hwfc, dst, src, flags);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
}

#ಯದಿ CONFIG_LIBDRM
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVkFrame *source;
} VulkanDRMMapping;

ಸ್ಥಿರ ಶೂನ್ಯ vulkan_unmap_to_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_frame_sync(hwfc, hwmap->source, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ uint32_t vulkan_fmt_to_drm(VkFormat vkfmt)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ಯದಿ (vulkan_drm_format_map[i].vk_format == vkfmt)
            ಪ್ರತ್ಯಾಗಮ vulkan_drm_format_map[i].drm_fourcc;
    ಪ್ರತ್ಯಾಗಮ DRM_FORMAT_INVALID;
}

#define MAX_MEMORY_PLANES 4
ಸ್ಥಿರ VkImageAspectFlags plane_index_to_aspect(ಪೂರ್ಣಾಙ್ಕ plane) {
    ಯದಿ (plane == 0) ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
    ಯದಿ (plane == 1) ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT;
    ಯದಿ (plane == 2) ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;
    ಯದಿ (plane == 3) ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT;

    av_assert2 (0 && "Invalid plane index");
    ಪ್ರತ್ಯಾಗಮ VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
}

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVkFrame *f,
                                     VulkanFramesPriv *fp, ಪೂರ್ಣಾಙ್ಕ nb_sems)
{
    ಪೂರ್ಣಾಙ್ಕ sync_fd = -1;
    VkResult ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಯದಿ (f->internal->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .pNext         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ದ್ವಿಮಾನ,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->internal->drm_sync_sem);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    ಯದಿ (ff_vk_exec_start(&p->vkctx, exec) >= 0) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_sems; i++)
            ff_vk_exec_add_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_ಮೌಲ್ಯ[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        ff_vk_exec_add_dep_bool_sem(&p->vkctx, exec, &f->internal->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 0);
        ಯದಿ (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->internal->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            ಯದಿ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ sync_fd;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err = 0;
    VkResult ret;
    AVVkFrame *f = (AVVkFrame *)src->data[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_sems = nb_images;
    ಪೂರ್ಣಾಙ್ಕ free_drm_desc_on_err = 1;
    ಪೂರ್ಣಾಙ್ಕ sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(ಪರಿಮಾಣ(*drm_desc));
    ಯದಿ (!drm_desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_EXPORT);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        ಯದಿ (err < 0)
            ಗಚ್ಛ end;
        sync_fd = err;
        err = 0;
    }
#endif

    ಯದಿ (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_ಎಣಿಕೆ = nb_sems,
            .pSemaphores    = f->sem,
            .p_ಮೌಲ್ಯಗಳು        = f->sem_ಮೌಲ್ಯ,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &vulkan_unmap_to_drm, drm_desc);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    ಯದಿ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        ಗಚ್ಛ end;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; (i < planes) && (f->mem[i]); i++) {
        VkMemoryGetFdInfoKHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
            .memory     = f->mem[i],
            .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };

        ret = vk->GetMemoryFdKHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        ಯದಿ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ end;
        }

#ಯದಿ HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        ಯದಿ (sync_fd >= 0) {
            ಪೂರ್ಣಾಙ್ಕ dup_fd = dup(sync_fd);
            ಯದಿ (dup_fd >= 0) {
                ಸಂರಚನಾ dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                ಯದಿ (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } ಅನ್ಯಥಾ {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#endif

        drm_desc->nb_objects++;
        drm_desc->objects[i].size = f->size[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_to_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_ಎಣಿಕೆ;

        ಯದಿ (drm_desc->layers[i].nb_planes > MAX_MEMORY_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            ಗಚ್ಛ end;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            ಪೂರ್ಣಾಙ್ಕ aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspectMask = plane_index_to_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_index = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].offset = layout.offset;
            drm_desc->layers[i].planes[j].pitch  = layout.rowPitch;
        }

        ಯದಿ (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            ಗಚ್ಛ end;
        }


        ಯದಿ (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            ಅನುವರ್ತ;

    }

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t *)drm_desc;
    dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);

    ಯದಿ (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    ಪ್ರತ್ಯಾಗಮ 0;

end:
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    ಯದಿ (free_drm_desc_on_err)
        av_free(drm_desc);
    ಯದಿ (sync_fd >= 0)
        close(sync_fd);
    ಪ್ರತ್ಯಾಗಮ err;
}

#ಯದಿ CONFIG_VAAPI
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_to_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    AVFrame *tmp = av_frame_alloc();
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ;

    err = vulkan_map_to_drm(hwfc, tmp, src, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = av_hwframe_map(dst, tmp, flags);
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ವಿಕಲ್ಪ (dst->format) {
#ಯದಿ CONFIG_LIBDRM
    ಪಕ್ಷ AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ:
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಪ್ರತ್ಯಾಗಮ vulkan_map_to_drm(hwfc, dst, src, flags);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
        ಯದಿ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ಪ್ರತ್ಯಾಗಮ vulkan_map_to_vaapi(hwfc, dst, src, flags);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
#endif
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ copy_buffer_data(AVHWFramesContext *hwfc, FFVkBuffer *vkbuf,
                            AVFrame *swf, VkBufferImageCopy *region,
                            ಪೂರ್ಣಾಙ್ಕ planes, ಪೂರ್ಣಾಙ್ಕ upload)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ bytewidth[AV_ಅಂಕೆ_DATA_POINTERS];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->width, i);
        ಯದಿ (bytewidth[i] < 0)
            ಪ್ರತ್ಯಾಗಮ bytewidth[i];
    }

    ಯದಿ (upload) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].bufferOffset,
                                region[i].bufferRowLength,
                                swf->data[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.height);

        err = ff_vk_flush_buffer(&p->vkctx, vkbuf, 0, VK_WHOLE_SIZE, 1);
        ಯದಿ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }
    } ಅನ್ಯಥಾ {
        err = ff_vk_flush_buffer(&p->vkctx, vkbuf, 0, VK_WHOLE_SIZE, 0);
        ಯದಿ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
            av_image_copy_plane(swf->data[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].bufferOffset,
                                region[i].bufferRowLength,
                                bytewidth[i],
                                region[i].imageExtent.height);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_plane_buf(AVHWFramesContext *hwfc, FFVkBuffer **dst,
                         AVFrame *swf, VkBufferImageCopy *region, ಪೂರ್ಣಾಙ್ಕ upload)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    uint32_t p_w, p_h;
    VulkanFramesPriv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    VkBufferUsageFlags buf_usage = upload ? VK_BUFFER_USAGE_TRANSFER_SRC_BIT :
                                            VK_BUFFER_USAGE_TRANSFER_DST_BIT;

    size_t buf_offset = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        region[i] = (VkBufferImageCopy) {
            .bufferOffset = buf_offset,
            .bufferRowLength = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimalBufferCopyRowPitchAlignment),
            .bufferImageHeight = p_h,
            .imageSubresource.layer_ಎಣಿಕೆ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_offset += FFALIGN(p_h*region[i].bufferRowLength,
                              p->props.properties.limits.optimalBufferCopyOffsetAlignment);
    }

    err = ff_vk_get_pooled_buffer(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  ರಿಕ್ತ, buf_offset,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                  p->vkctx.host_cached_flag);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ host_map_frame(AVHWFramesContext *hwfc, FFVkBuffer **dst, ಪೂರ್ಣಾಙ್ಕ *nb_bufs,
                          AVFrame *swf, VkBufferImageCopy *region, ಪೂರ್ಣಾಙ್ಕ upload)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ಪೂರ್ಣಾಙ್ಕ nb_src_bufs;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    VkBufferUsageFlags buf_usage = upload ? VK_BUFFER_USAGE_TRANSFER_SRC_BIT :
                                            VK_BUFFER_USAGE_TRANSFER_DST_BIT;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    ಯಾವತ್ (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    ಯದಿ (nb_src_bufs == 1) {
        err = ff_vk_host_map_buffer(&p->vkctx, &dst[0],
                                    swf->data[0], VK_WHOLE_SIZE, swf->buf[0],
                                    buf_usage);
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
        (*nb_bufs)++;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
            region[i].bufferOffset = dst[0]->virtual_offset +
                                     swf->data[i] - swf->data[0];
    } ಅನ್ಯಥಾ ಯದಿ (nb_src_bufs == planes) { /* One buffer per plane */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
            err = ff_vk_host_map_buffer(&p->vkctx, &dst[i],
                                        swf->data[i], VK_WHOLE_SIZE,
                                        swf->buf[i], buf_usage);
            ಯದಿ (err < 0)
                ಗಚ್ಛ fail;
            (*nb_bufs)++;

            region[i].bufferOffset = dst[i]->virtual_offset;
        }
    } ಅನ್ಯಥಾ {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        ಪ್ರತ್ಯಾಗಮ AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        ಪೂರ್ಣಾಙ್ಕ align = FFMAX(desc->comp[i].step, p->transfer_offset_align);
        ಯದಿ ((align & (align - 1)) || (region[i].bufferOffset & (align - 1))) {
            err = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, ಪೂರ್ಣಾಙ್ಕ upload)
{
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->data[0];
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ nb_layout_ch = 0;

    hwfc_vk->lock_frame(hwfc, hwf_vk);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        ಪೂರ್ಣಾಙ್ಕ compat = 0;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ಎಣಿಕೆ; j++) {
            ಯದಿ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (compat)
            ಅನುವರ್ತ;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
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

    ಯದಿ (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    ಯದಿ (upload) {
        VkMemoryToImageCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_ಎಣಿಕೆ = 1,
            },
        };
        VkCopyMemoryToImageInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT,
            .region_ಎಣಿಕೆ = 1,
            .pRegions = &region_info,
        };
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
            ಪೂರ್ಣಾಙ್ಕ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

            region_info.pHostPointer = swf->data[i];
            region_info.memoryRowLength = swf->linesize[i] / desc->comp[i].step;
            region_info.imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->CopyMemoryToImageEXT(hwctx->act_dev, &copy_info);
        }
    } ಅನ್ಯಥಾ {
        VkImageToMemoryCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT,
            .imageSubresource = {
                .layer_ಎಣಿಕೆ = 1,
            },
        };
        VkCopyImageToMemoryInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT,
            .region_ಎಣಿಕೆ = 1,
            .pRegions = &region_info,
        };
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
            ಪೂರ್ಣಾಙ್ಕ img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

            region_info.pHostPointer = swf->data[i];
            region_info.memoryRowLength = swf->linesize[i] / desc->comp[i].step;
            region_info.imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->CopyImageToMemoryEXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_frame(hwfc, hwf_vk);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_frame(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 ಪೂರ್ಣಾಙ್ಕ upload)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ಪೂರ್ಣಾಙ್ಕ host_mapped = 0;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->data[0];
    VkBufferImageCopy region[AV_ಅಂಕೆ_DATA_POINTERS]; // always one per plane

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(swf->format);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_images = ff_vk_ಎಣಿಕೆ_images(hwf_vk);

    VkImageMemoryBarrier2 img_bar[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ nb_img_bar = 0;

    FFVkBuffer *bufs[AV_ಅಂಕೆ_DATA_POINTERS];
    ಪೂರ್ಣಾಙ್ಕ nb_bufs = 0;

    VkCommandBuffer cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    ಯದಿ ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (swf->width > hwfc->width || swf->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪೂರ್ಣಾಙ್ಕ host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;
    ಪೂರ್ಣಾಙ್ಕ host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
        ಯದಿ (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    ಯದಿ (!upload && host_copy) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
            ಪೂರ್ಣಾಙ್ಕ compat = 0;
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ಎಣಿಕೆ; j++) {
                ಯದಿ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    ಭಙ್ಗ;
                }
            }
            ಯದಿ (!compat) {
                host_copy = 0;
                ಭಙ್ಗ;
            }
        }
    }

    ಯದಿ (host_copy)
        ಪ್ರತ್ಯಾಗಮ vulkan_transfer_host(hwfc, hwf, swf, upload);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < av_pix_fmt_ಎಣಿಕೆ_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        /* Buffer region for this plane */
        region[i] = (VkBufferImageCopy) {
            .bufferOffset = 0,
            .bufferRowLength = FFABS(swf->linesize[i]),
            .bufferImageHeight = p_h,
            .imageSubresource.layer_ಎಣಿಕೆ = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    ಯದಿ (host_map) {
        err = host_map_frame(hwfc, bufs, &nb_bufs, swf, region, upload);
        ಯದಿ (err >= 0)
            host_mapped = 1;
    }

    ಯದಿ (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        ಯದಿ (err < 0)
            ಗಚ್ಛ end;
        nb_bufs = 1;

        ಯದಿ (upload) {
            err = copy_buffer_data(hwfc, bufs[0], swf, region, planes, 1);
            ಯದಿ (err < 0)
                ಗಚ್ಛ end;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_start(&p->vkctx, exec);
    ಯದಿ (err < 0)
        ಗಚ್ಛ end;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_TRANSFER_BIT);
    ಯದಿ (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        ಗಚ್ಛ end;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    ಯದಿ (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        ಯದಿ (host_mapped) {
            err = ff_vk_exec_add_dep_sw_frame(&p->vkctx, exec, swf);
            ಯದಿ (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                ಗಚ್ಛ end;
            }
        }

        /* Add the buffers as a dependency */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_bufs; i++)
            ff_vk_exec_add_dep_refstruct(&p->vkctx, exec, bufs[i]);
    }

    ff_vk_frame_barrier(&p->vkctx, exec, hwf, img_bar, &nb_img_bar,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                        VK_PIPELINE_STAGE_2_TRANSFER_BIT_KHR,
                        upload ? VK_ACCESS_TRANSFER_WRITE_BIT :
                                 VK_ACCESS_TRANSFER_READ_BIT,
                        upload ? VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                        p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0]);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .pImageMemoryBarriers = img_bar,
            .image_Memory_Barrier_ಎಣಿಕೆ = nb_img_bar,
    });

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        ಪೂರ್ಣಾಙ್ಕ buf_idx = FFMIN(i, (nb_bufs - 1));
        ಪೂರ್ಣಾಙ್ಕ img_idx = FFMIN(i, (nb_images - 1));
        FFVkBuffer *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].bufferRowLength;
        region[i].bufferRowLength /= desc->comp[i].step;
        region[i].imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);

        ಯದಿ (upload)
            vk->CmdCopyBufferToImage(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        ಅನ್ಯಥಾ
            vk->CmdCopyImageToBuffer(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].bufferRowLength = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ಯದಿ (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        ಯದಿ (!host_mapped)
            err = copy_buffer_data(hwfc, bufs[0], swf, region, planes, 0);
    }

end:
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_data_to(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ಧ್ರುವ AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ವಿಕಲ್ಪ (src->format) {
#ಯದಿ CONFIG_CUDA
    ಪಕ್ಷ AV_PIX_FMT_CUDA:
#ifdef _WIN32
        ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ಅನ್ಯಥಾ
        ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#endif
            ಪ್ರತ್ಯಾಗಮ vulkan_transfer_data_from_cuda(hwfc, dst, src);
        av_fallthrough;
#endif
    ಸ್ವಭಾವ:
        ಯದಿ (src->hw_frames_ctx)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ vulkan_transfer_frame(hwfc, (AVFrame *)src, dst, 1);
    }
}

#ಯದಿ CONFIG_CUDA
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_data_to_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ planes = av_pix_fmt_ಎಣಿಕೆ_planes(hwfc->sw_format);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ಪೂರ್ಣಾಙ್ಕ nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ಅಂಕೆ_DATA_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)src->data[0];
    nb_images = ff_vk_ಎಣಿಕೆ_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(cuda_dev->cuda_ctx));
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    err = vulkan_export_to_cuda(hwfc, dst->hw_frames_ctx, src);
    ಯದಿ (err < 0) {
        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಪ್ರತ್ಯಾಗಮ err;
    }

    dst_int = dst_f->internal;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 0;
        s_s_par[i].params.fence.ಮೌಲ್ಯ = dst_f->sem_ಮೌಲ್ಯ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dstMemoryType = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->data[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .srcMemoryType = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        ಪೂರ್ಣಾಙ್ಕ w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = w * desc->comp[i].step;
        cpy.Height = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    ಯದಿ (err < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_images; i++)
        dst_f->sem_ಮೌಲ್ಯ[i]++;

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    ಪ್ರತ್ಯಾಗಮ prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_buffer_unref(&dst->buf[0]);
    ಪ್ರತ್ಯಾಗಮ err;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_transfer_data_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ಧ್ರುವ AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ವಿಕಲ್ಪ (dst->format) {
#ಯದಿ CONFIG_CUDA
    ಪಕ್ಷ AV_PIX_FMT_CUDA:
#ifdef _WIN32
        ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ಅನ್ಯಥಾ
        ಯದಿ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#endif
            ಪ್ರತ್ಯಾಗಮ vulkan_transfer_data_to_cuda(hwfc, dst, src);
        av_fallthrough;
#endif
    ಸ್ವಭಾವ:
        ಯದಿ (dst->hw_frames_ctx)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ vulkan_transfer_frame(hwfc, dst, (AVFrame *)src, 0);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vulkan_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪ್ರತ್ಯಾಗಮ vulkan_frames_init(dst_fc);
}

AVVkFrame *av_vk_frame_alloc(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ err;
    AVVkFrame *f = av_mallocz(ಪರಿಮಾಣ(AVVkFrame));
    ಯದಿ (!f)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    f->internal = av_mallocz(ಪರಿಮಾಣ(*f->internal));
    ಯದಿ (!f->internal) {
        av_free(f);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    err = pthread_mutex_init(&f->internal->update_mutex, ರಿಕ್ತ);
    ಯದಿ (err != 0) {
        av_free(f->internal);
        av_free(f);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ f;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_size      = ಪರಿಮಾಣ(VulkanDevicePriv),
    .frames_hwctx_size      = ಪರಿಮಾಣ(VulkanFramesPriv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .frames_get_constraints = &vulkan_frames_get_constraints,
    .frames_init            = vulkan_frames_init,
    .frames_get_buffer      = vulkan_get_buffer,
    .frames_uninit          = vulkan_frames_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_data_to       = vulkan_transfer_data_to,
    .transfer_data_from     = vulkan_transfer_data_from,

    .map_to                 = vulkan_map_to,
    .map_from               = vulkan_map_from,
    .frames_derive_to       = &vulkan_frames_derive_to,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
