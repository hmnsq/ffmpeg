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
#ଅନ୍ତର୍ଭାଵ <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#ଅନ୍ତର୍ଭାଵ <versionhelpers.h>
#ଅନ୍ତର୍ଭାଵ "compat/w32dlfcn.h"
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ <dlfcn.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif

#ଅନ୍ତର୍ଭାଵ "thread.h"

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_vulkan.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "uuid.h"

#ଅନ୍ତର୍ଭାଵ "vulkan.h"
#ଅନ୍ତର୍ଭାଵ "vulkan_loader.h"

#ଯଦି CONFIG_VAAPI
#ଅନ୍ତର୍ଭାଵ "hwcontext_vaapi.h"
#endif

#ଯଦି CONFIG_LIBDRM
#ଯଦି CONFIG_VAAPI
#ଅନ୍ତର୍ଭାଵ <va/va_drmcommon.h>
#endif
#ifdef __linux__
#ଅନ୍ତର୍ଭାଵ <sys/sysmacros.h>
#endif
#ଅନ୍ତର୍ଭାଵ <sys/stat.h>
#ଅନ୍ତର୍ଭାଵ <xf86drm.h>
#ଅନ୍ତର୍ଭାଵ <drm_fourcc.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_drm.h"
#endif

#ଯଦି HAVE_LINUX_DMA_BUF_H
#ଅନ୍ତର୍ଭାଵ <sys/ioctl.h>
#ଅନ୍ତର୍ଭାଵ <linux/dma-buf.h>
#endif

#ଯଦି CONFIG_CUDA
#ଅନ୍ତର୍ଭାଵ "hwcontext_cuda_internal.h"
#ଅନ୍ତର୍ଭାଵ "cuda_check.h"
#define CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanDeviceFeatures {
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    ଶୂନ୍ୟ *libvulkan;

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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_linear_images;

    /* Option to allocate all image planes in a single allocation */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା contiguous_planes;

    /* Disable multiplane images */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା transfer_offset_align;

    /* Maximum queues */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା limit_queues;
} VulkanDevicePriv;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanFramesPriv {
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା export_requires_dedicated;
} VulkanFramesPriv;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVVkFrameInternal {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#ଯଦି CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternalMemory ext_mem[AV_ଅଙ୍କ_DATA_POINTERS];
    CUmipmappedArray cu_mma[AV_ଅଙ୍କ_DATA_POINTERS];
    CUarray cu_array[AV_ଅଙ୍କ_DATA_POINTERS];
    CUexternalSemaphore cu_sem[AV_ଅଙ୍କ_DATA_POINTERS];
#ifdef _WIN32
    HANDLE ext_mem_handle[AV_ଅଙ୍କ_DATA_POINTERS];
    HANDLE ext_sem_handle[AV_ଅଙ୍କ_DATA_POINTERS];
#endif
#endif
} AVVkFrameInternal;

/* Initialize all structs in VulkanDeviceFeatures */
ସ୍ଥିର ଶୂନ୍ୟ device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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
ସ୍ଥିର ଶୂନ୍ୟ device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#define COPY_VAL(VAL)        \
    କର {                     \
        dst->VAL = src->VAL; \
    } ଯେତେବେଳେ (0)              \

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
    COPY_VAL(vulkan_1_1.storage_ଠେଲ_Constant16);
    COPY_VAL(vulkan_1_1.storageBuffer16BitAccess);
    COPY_VAL(vulkan_1_1.uniformAndStorageBuffer16BitAccess);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalarBlockLayout);
    COPY_VAL(vulkan_1_2.bufferDeviceAddress);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_ଠେଲ_Constant8);
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

ସ୍ଥିର ଅଚଳ ସଂରଚନା FFVkFormatEntry {
    VkFormat vkf;
    ଗଣନା AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା vk_planes;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images_fallback;
    ଅଚଳ VkFormat fallback[5];
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
ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ଅଚଳ VkFormat *av_vkfmt_from_pixfmt(ଗଣନା AVPixelFormat p)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_vk_formats_list; i++)
        ଯଦି (vk_formats_list[i].pixfmt == p)
            ଫେରନ୍ତୁ vk_formats_list[i].fallback;
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା FFVkFormatEntry *vk_find_format_entry(ଗଣନା AVPixelFormat p)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_vk_formats_list; i++)
        ଯଦି (vk_formats_list[i].pixfmt == p)
            ଫେରନ୍ତୁ &vk_formats_list[i];
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, ଗଣନା AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_ଅଙ୍କ_DATA_POINTERS], /* Output format list */
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା disable_multiplane, ପୂର୍ଣ୍ଣସଂଖ୍ୟା need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ଅଚଳ VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_vk_formats_list; i++) {
        ଯଦି (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .pNext = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା basics_primary = 0, basics_secondary = 0;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_LINEAR ?
                             fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);

            ଯଦି (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_LINEAR ?
                                  fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);
            } ଅନ୍ୟଥା {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            ଯଦି (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                ଯଦି (fmts) {
                    ଯଦି (vk_formats_list[i].nb_images > 1) {
                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } ଅନ୍ୟଥା {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                ଯଦି (nb_images)
                    *nb_images = 1;
                ଯଦି (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ଯଦି (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_BIT : 0);
                ଫେରନ୍ତୁ 0;
            } ଅନ୍ୟଥା ଯଦି (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                ଯଦି (fmts) {
                    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                ଯଦି (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                ଯଦି (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ଯଦି (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_secondary);
                ଫେରନ୍ତୁ 0;
            } ଅନ୍ୟଥା {
                ଫେରନ୍ତୁ AVERROR(ENOTSUP);
            }
        }
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

#ଯଦି CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ଅଚଳ ଅକ୍ଷର *pName);
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା load_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#ଯଦି CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#ଅନ୍ୟଥା
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *lib_names[] = {
#ଯଦି defined(_WIN32)
        "vulkan-1.dll",
#ନଚେତଯଦି defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#ଅନ୍ୟଥା
        "libvulkan.so.1",
        "libvulkan.so",
#endif
    };

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(lib_names); i++) {
        p->libvulkan = dlopen(lib_names[i], RTLD_NOW | RTLD_LOCAL);
        ଯଦି (p->libvulkan)
            ଭାଙ୍ଗ;
    }

    ଯଦି (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#endif /* CONFIG_VULKAN_STATIC */

    ଫେରନ୍ତୁ 0;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanOptExtension {
    ଅଚଳ ଅକ୍ଷର *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

ସ୍ଥିର ଅଚଳ VulkanOptExtension optional_instance_exts[] = {
#ifdef __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#endif
    { 0 },
};

ସ୍ଥିର ଅଚଳ VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_ଠେଲ_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_ଠେଲ_DESCRIPTOR        },
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

ଅଚଳ ଅକ୍ଷର **av_vk_get_optional_instance_extensions(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ଅଚଳ ଅକ୍ଷର **exts = av_malloc_array(ଆକାର(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    ଯଦି (!exts)
        ଫେରନ୍ତୁ ଖାଲି;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *ଗଣନା_2 = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    ଫେରନ୍ତୁ exts;
}

ଅଚଳ ଅକ୍ଷର **av_vk_get_optional_device_extensions(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ଅଚଳ ଅକ୍ଷର **exts = av_malloc_array(ଆକାର(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    ଯଦି (!exts)
        ଫେରନ୍ତୁ ଖାଲି;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *ଗଣନା_2 = FF_ARRAY_ELEMS(optional_device_exts);
    ଫେରନ୍ତୁ exts;
}

ସ୍ଥିର VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                    ଅଚଳ VkDebugUtilsMessengerCallbackDataEXT *data,
                                    ଶୂନ୍ୟ *priv)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    ବାଛ (data->message_Id_ସଂଖ୍ୟା) {
    ସ୍ଥିତି 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    ସ୍ଥିତି 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        ଫେରନ୍ତୁ VK_FALSE;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }

    ବାଛ (severity) {
    ସ୍ଥିତି VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: l = AV_LOG_VERBOSE; ଭାଙ୍ଗ;
    ସ୍ଥିତି VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:    l = AV_LOG_INFO;    ଭାଙ୍ଗ;
    ସ୍ଥିତି VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: l = AV_LOG_WARNING; ଭାଙ୍ଗ;
    ସ୍ଥିତି VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:   l = AV_LOG_ERROR;   ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                                              l = AV_LOG_DEBUG;   ଭାଙ୍ଗ;
    }

    av_log(ctx, l, "%s\n", data->pMessage);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < data->cmd_Buf_Label_ଗଣନା; i++)
        av_log(ctx, l, "\t%i: %s\n", i, data->pCmdBufLabels[i].pLabelName);

    ଫେରନ୍ତୁ VK_FALSE;
}

#define ADD_VAL_TO_LIST(list, ଗଣନା_2, val)                                      \
    କର {                                                                       \
        list = av_realloc_array(list, ++ଗଣନା_2, ଆକାର(*list));                 \
        ଯଦି (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            ଯାଅ fail;                                                         \
        }                                                                      \
        list[ଗଣନା_2 - 1] = av_strdup(val);                                      \
        ଯଦି (!list[ଗଣନା_2 - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            ଯାଅ fail;                                                         \
        }                                                                      \
    } ଯେତେବେଳେ(0)

#define RELEASE_PROPS(props, ଗଣନା_2)                                            \
    ଯଦି (props) {                                                               \
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଗଣନା_2; i++)                                        \
            av_free((ଶୂନ୍ୟ *)((props)[i]));                                     \
        av_free((ଶୂନ୍ୟ *)props);                                                \
    }

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    VkDeviceSize max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.memory_Type_ଗଣନା);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < p->mprops.memory_Type_ଗଣନା; i++) {
        ଅଚଳ VkMemoryType type = p->mprops.memoryTypes[i];
        ଅଚଳ VkMemoryHeap heap = p->mprops.memoryHeaps[type.heapIndex];
        ଯଦି (!(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            ଜାରି;
        max_vram = FFMAX(max_vram, heap.size);
        ଯଦି (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            max_visible_vram = FFMAX(max_visible_vram, heap.size);
    }

    ଫେରନ୍ତୁ max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

ଗଣନା FFVulkanDebugMode {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_extensions(AVHWDeviceContext *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dev, AVDictionary *opts,
                            ଅଚଳ ଅକ୍ଷର * ଅଚଳ **dst, uint32_t *ଅଙ୍କ,
                            ଗଣନା FFVulkanDebugMode debug_mode)
{
    ଅଚଳ ଅକ୍ଷର *tstr;
    ଅଚଳ ଅକ୍ଷର **extension_names = ଖାଲି;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0, found, extensions_found = 0;

    ଅଚଳ ଅକ୍ଷର *mod;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା optional_exts_ଅଙ୍କ;
    uint32_t sup_ext_ଗଣନା;
    ଅକ୍ଷର *user_exts_str = ଖାଲି;
    AVDictionaryEntry *user_exts;
    VkExtensionProperties *sup_ext;
    ଅଚଳ VulkanOptExtension *optional_exts;

    ଯଦି (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_ଅଙ୍କ = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", ଖାଲି, 0);
        ଯଦି (user_exts) {
            user_exts_str = av_strdup(user_exts->ମୂଲ୍ୟ);
            ଯଦି (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(ଖାଲି, &sup_ext_ଗଣନା, ଖାଲି);
        sup_ext = av_malloc_array(sup_ext_ଗଣନା, ଆକାର(VkExtensionProperties));
        ଯଦି (!sup_ext)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(ଖାଲି, &sup_ext_ଗଣନା, sup_ext);
    } ଅନ୍ୟଥା {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_ଅଙ୍କ = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", ଖାଲି, 0);
        ଯଦି (user_exts) {
            user_exts_str = av_strdup(user_exts->ମୂଲ୍ୟ);
            ଯଦି (!user_exts_str) {
                err = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ଖାଲି,
                                               &sup_ext_ଗଣନା, ଖାଲି);
        sup_ext = av_malloc_array(sup_ext_ଗଣନା, ଆକାର(VkExtensionProperties));
        ଯଦି (!sup_ext)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ଖାଲି,
                                               &sup_ext_ଗଣନା, sup_ext);
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < optional_exts_ଅଙ୍କ; i++) {
        tstr = optional_exts[i].name;
        found = 0;

        /* Check if the device has ReBAR for host image copies */
        ଯଦି (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            ଜାରି;

        ଯଦି (dev &&
            ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_mode == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            ଜାରି;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sup_ext_ଗଣନା; j++) {
            ଯଦି (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!found)
            ଜାରି;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
    }

    ଯଦି (!dev &&
        ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_mode == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        found = 0;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sup_ext_ଗଣନା; j++) {
            ଯଦି (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (found) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
        } ଅନ୍ୟଥା {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ଯାଅ fail;
        }
    }

#ifdef VK_KHR_shader_relaxed_extended_instruction
    ଯଦି ((debug_mode == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        found = 0;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sup_ext_ଗଣନା; j++) {
            ଯଦି (!strcmp(tstr, sup_ext[j].extensionName)) {
                found = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!found) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            ଯାଅ fail;
        }
    }
#endif

    ଯଦି (user_exts_str) {
        ଅକ୍ଷର *save, *token = av_strtok(user_exts_str, "+", &save);
        ଯେତେବେଳେ (token) {
            found = 0;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sup_ext_ଗଣନା; j++) {
                ଯଦି (!strcmp(token, sup_ext[j].extensionName)) {
                    found = 1;
                    ଭାଙ୍ଗ;
                }
            }
            ଯଦି (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                ADD_VAL_TO_LIST(extension_names, extensions_found, token);
            } ଅନ୍ୟଥା {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(ଖାଲି, "+", &save);
        }
    }

    *dst = extension_names;
    *ଅଙ୍କ = extensions_found;

    av_free(user_exts_str);
    av_free(sup_ext);
    ଫେରନ୍ତୁ 0;

fail:
    RELEASE_PROPS(extension_names, extensions_found);
    av_free(user_exts_str);
    av_free(sup_ext);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ଅଚଳ ଅକ୍ଷର * ଅଚଳ **dst, uint32_t *ଅଙ୍କ,
                        ଗଣନା FFVulkanDebugMode *debug_mode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା layer_standard_validation_found = 0;

    uint32_t sup_layer_ଗଣନା;
    VkLayerProperties *sup_layers;

    AVDictionaryEntry *user_layers = av_dict_get(opts, "layers", ଖାଲି, 0);
    ଅକ୍ଷର *user_layers_str = ଖାଲି;
    ଅକ୍ଷର *save, *token;

    ଅଚଳ ଅକ୍ଷର **enabled_layers = ଖାଲି;
    uint32_t enabled_layers_ଗଣନା = 0;

    AVDictionaryEntry *debug_opt = av_dict_get(opts, "debug", ଖାଲି, 0);
    ଗଣନା FFVulkanDebugMode mode;

    *debug_mode = mode = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_ଗଣନା, ଖାଲି);
    sup_layers = av_malloc_array(sup_layer_ଗଣନା, ଆକାର(VkLayerProperties));
    ଯଦି (!sup_layers)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_ଗଣନା, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < sup_layer_ଗଣନା; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    ଯଦି (!debug_opt && !user_layers)
        ଯାଅ end;

    /* Check for any properly supported validation layer */
    ଯଦି (debug_opt) {
        ଯଦି (!strcmp(debug_opt->ମୂଲ୍ୟ, "printf")) {
            mode = FF_VULKAN_DEBUG_PRINTF;
        } ଅନ୍ୟଥା ଯଦି (!strcmp(debug_opt->ମୂଲ୍ୟ, "validate")) {
            mode = FF_VULKAN_DEBUG_VALIDATE;
        } ଅନ୍ୟଥା ଯଦି (!strcmp(debug_opt->ମୂଲ୍ୟ, "practices")) {
            mode = FF_VULKAN_DEBUG_PRACTICES;
        } ଅନ୍ୟଥା {
            ଅକ୍ଷର *end_ptr = ଖାଲି;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = strtol(debug_opt->ମୂଲ୍ୟ, &end_ptr, 10);
            ଯଦି (end_ptr == debug_opt->ମୂଲ୍ୟ || end_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->ମୂଲ୍ୟ);
                err = AVERROR(EINVAL);
                ଯାଅ end;
            }
            mode = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    ଯଦି ((mode == FF_VULKAN_DEBUG_VALIDATE) ||
        (mode == FF_VULKAN_DEBUG_PRINTF) ||
        (mode == FF_VULKAN_DEBUG_PRACTICES)) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < sup_layer_ଗଣନା; i++) {
            ଯଦି (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_ଗଣନା, layer_standard_validation);
                *debug_mode = mode;
                layer_standard_validation_found = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!layer_standard_validation_found) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            ଯାଅ end;
        }
    }

    /* Process any custom layers enabled */
    ଯଦି (user_layers) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା found;

        user_layers_str = av_strdup(user_layers->ମୂଲ୍ୟ);
        ଯଦି (!user_layers_str) {
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        ଯେତେବେଳେ (token) {
            found = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            ଯଦି (!strcmp(layer_standard_validation, token) && layer_standard_validation_found) {
                token = av_strtok(ଖାଲି, "+", &save);
                ଭାଙ୍ଗ;
            }

            /* Try to find the layer in the list of supported layers */
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < sup_layer_ଗଣନା; j++) {
                ଯଦି (!strcmp(token, sup_layers[j].layerName)) {
                    found = 1;
                    ଭାଙ୍ଗ;
                }
            }

            ଯଦି (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_ଗଣନା, token);

                /* If debug was not set as an option, force it */
                ଯଦି (!strcmp(layer_standard_validation, token))
                    *debug_mode = FF_VULKAN_DEBUG_VALIDATE;
            } ଅନ୍ୟଥା {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                ଯାଅ end;
            }

            token = av_strtok(ଖାଲି, "+", &save);
        }
    }

fail:
end:
    av_free(sup_layers);
    av_free(user_layers_str);

    ଯଦି (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_ଗଣନା);
    } ଅନ୍ୟଥା {
        *dst = enabled_layers;
        *ଅଙ୍କ = enabled_layers_ଗଣନା;
    }

    ଫେରନ୍ତୁ err;
}

/* Creates a VkInstance */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           ଗଣନା FFVulkanDebugMode *debug_mode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
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

    ଯଦି (!hwctx->get_proc_addr) {
        err = load_libvulkan(ctx);
        ଯଦି (err < 0)
            ଫେରନ୍ତୁ err;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    ଯଦି (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        ଫେରନ୍ତୁ err;
    }

    err = check_layers(ctx, opts, &inst_props.ppEnabledLayerNames,
                       &inst_props.enabled_Layer_ଗଣନା, debug_mode);
    ଯଦି (err)
        ଯାଅ fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.ppEnabledExtensionNames,
                           &inst_props.enabled_Extension_ଗଣନା, *debug_mode);
    hwctx->enabled_inst_extensions = inst_props.ppEnabledExtensionNames;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_ଗଣନା;
    ଯଦି (err < 0)
        ଯାଅ fail;

    /* Enable debug features if needed */
    ଯଦି (*debug_mode == FF_VULKAN_DEBUG_VALIDATE) {
        ସ୍ଥିର ଅଚଳ VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_ଗଣନା = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.pNext = &validation_features;
    } ଅନ୍ୟଥା ଯଦି (*debug_mode == FF_VULKAN_DEBUG_PRINTF) {
        ସ୍ଥିର ଅଚଳ VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_ଗଣନା = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.pNext = &validation_features;
    } ଅନ୍ୟଥା ଯଦି (*debug_mode == FF_VULKAN_DEBUG_PRACTICES) {
        ସ୍ଥିର ଅଚଳ VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_ଗଣନା = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.pNext = &validation_features;
    }

#ifdef __APPLE__
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < inst_props.enabled_Extension_ଗଣନା; i++) {
        ଯଦି (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.ppEnabledExtensionNames[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            ଭାଙ୍ଗ;
        }
    }
#endif

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ଯାଅ fail;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    ଯଦି (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        ଯାଅ fail;
    }

    /* Setup debugging callback if needed */
    ଯଦି ((*debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
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
    RELEASE_PROPS(inst_props.ppEnabledLayerNames, inst_props.enabled_Layer_ଗଣନା);
    ଫେରନ୍ତୁ err;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_SIZE]; /* Will use this first unless !has_uuid */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ଅଚଳ ଅକ୍ଷର *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index; /* Finally fall back to index */
} VulkanDeviceSelection;

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *vk_dev_type(ଗଣନା VkPhysicalDeviceType type)
{
    ବାଛ (type) {
    ସ୍ଥିତି VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: ଫେରନ୍ତୁ "integrated";
    ସ୍ଥିତି VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   ଫେରନ୍ତୁ "discrete";
    ସ୍ଥିତି VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    ଫେରନ୍ତୁ "virtual";
    ସ୍ଥିତି VK_PHYSICAL_DEVICE_TYPE_CPU:            ଫେରନ୍ତୁ "software";
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                                     ଫେରନ୍ତୁ "unknown";
    }
}

/* Finds a device */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା find_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0, choice = -1;
    uint32_t ଅଙ୍କ;
    VkResult ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = ଖାଲି;
    VkPhysicalDeviceIDProperties *idp = ଖାଲି;
    VkPhysicalDeviceProperties2 *prop = ଖାଲି;
    VkPhysicalDeviceDriverProperties *driver_prop = ଖାଲି;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = ଖାଲି;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ଅଙ୍କ, ଖାଲି);
    ଯଦି (ret != VK_SUCCESS || !ଅଙ୍କ) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR(ENODEV);
    }

    devices = av_malloc_array(ଅଙ୍କ, ଆକାର(VkPhysicalDevice));
    ଯଦି (!devices)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &ଅଙ୍କ, devices);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        ଯାଅ end;
    }

    prop = av_calloc(ଅଙ୍କ, ଆକାର(*prop));
    ଯଦି (!prop) {
        err = AVERROR(ENOMEM);
        ଯାଅ end;
    }

    idp = av_calloc(ଅଙ୍କ, ଆକାର(*idp));
    ଯଦି (!idp) {
        err = AVERROR(ENOMEM);
        ଯାଅ end;
    }

    driver_prop = av_calloc(ଅଙ୍କ, ଆକାର(*driver_prop));
    ଯଦି (!driver_prop) {
        err = AVERROR(ENOMEM);
        ଯାଅ end;
    }

    ଯଦି (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(ଅଙ୍କ, ଆକାର(*drm_prop));
        ଯଦି (!drm_prop) {
            err = AVERROR(ENOMEM);
            ଯାଅ end;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
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

    ଯଦି (select->has_uuid) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
            ଯଦି (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_SIZE)) {
                choice = i;
                ଯାଅ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        ଯାଅ end;
    } ଅନ୍ୟଥା ଯଦି ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
            ଯଦି ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                ଯାଅ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        ଯାଅ end;
    } ଅନ୍ୟଥା ଯଦି (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
            ଯଦି (strstr(prop[i].properties.deviceName, select->name)) {
                choice = i;
                ଯାଅ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        ଯାଅ end;
    } ଅନ୍ୟଥା ଯଦି (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
            ଯଦି (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                ଯାଅ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        ଯାଅ end;
    } ଅନ୍ୟଥା ଯଦି (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
            ଯଦି (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                ଯାଅ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        ଯାଅ end;
    } ଅନ୍ୟଥା {
        ଯଦି (select->index < ଅଙ୍କ) {
            choice = select->index;
            ଯାଅ end;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->index);
        err = AVERROR(ENODEV);
        ଯାଅ end;
    }

end:
    ଯଦି (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.pNext = ଖାଲି;
        p->dprops = driver_prop[choice];
        p->dprops.pNext = ଖାଲି;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    ଫେରନ୍ତୁ err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pick_queue_family(VkQueueFamilyProperties2 *qf, uint32_t ଅଙ୍କ_qf,
                                    VkQueueFlagBits flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = -1;
    uint32_t min_score = UINT32_MAX;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_qf; i++) {
        VkQueueFlagBits qflags = qf[i].queueFamilyProperties.queueFlags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        ଯଦି ((flags & VK_QUEUE_TRANSFER_BIT) &&
            (qflags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            qflags |= VK_QUEUE_TRANSFER_BIT;

        ଯଦି (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].queueFamilyProperties.timestampValidBits;
            ଯଦି (score < min_score) {
                index = i;
                min_score = score;
            }
        }
    }

    ଯଦି (index > -1)
        qf[index].queueFamilyProperties.timestampValidBits++;

    ଫେରନ୍ତୁ index;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pick_video_queue_family(VkQueueFamilyProperties2 *qf,
                                          VkQueueFamilyVideoPropertiesKHR *qf_vid, uint32_t ଅଙ୍କ_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = -1;
    uint32_t min_score = UINT32_MAX;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_qf; i++) {
        ଅଚଳ VkQueueFlags qflags = qf[i].queueFamilyProperties.queueFlags;
        ଅଚଳ VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        ଯଦି (!(qflags & (VK_QUEUE_VIDEO_ENCODE_BIT_KHR | VK_QUEUE_VIDEO_DECODE_BIT_KHR)))
            ଜାରି;

        ଯଦି (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].queueFamilyProperties.timestampValidBits;
            ଯଦି (score < min_score) {
                index = i;
                min_score = score;
            }
        }
    }

    ଯଦି (index > -1)
        qf[index].queueFamilyProperties.timestampValidBits++;

    ଫେରନ୍ତୁ index;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା setup_queue_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t ଅଙ୍କ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    VkQueueFamilyProperties2 *qf = ଖାଲି;
    VkQueueFamilyVideoPropertiesKHR *qf_vid = ଖାଲି;

    /* First get the number of queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &ଅଙ୍କ, ଖାଲି);
    ଯଦି (!ଅଙ୍କ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(ଅଙ୍କ, ଆକାର(VkQueueFamilyProperties2));
    ଯଦି (!qf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(ଅଙ୍କ, ଆକାର(VkQueueFamilyVideoPropertiesKHR));
    ଯଦି (!qf_vid)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (uint32_t i = 0; i < ଅଙ୍କ; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .pNext = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : ଖାଲି,
        };
    }

    /* Finally retrieve the queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &ଅଙ୍କ, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_GRAPHICS_BIT) ? " graphics" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_COMPUTE_BIT) ? " compute" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_TRANSFER_BIT) ? " transfer" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) ? " encode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_DECODE_BIT_KHR) ? " decode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_SPARSE_BINDING_BIT) ? " sparse" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_OPTICAL_FLOW_BIT_NV) ? " optical_flow" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_PROTECTED_BIT) ? " protected" : "",
               qf[i].queueFamilyProperties.queue_ଗଣନା);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].queueFamilyProperties.timestampValidBits = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->queue_flags = 0;
#ifdef VK_KHR_internally_synchronized_queues
    ଯଦି (p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)
        hwctx->queue_flags |= VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR;
#endif

    /* Pick each queue family to use. */
#define PICK_QF(type, vid_op)                                            \
    କର {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        ଯଦି (vid_op)                                                      \
            idx = pick_video_queue_family(qf, qf_vid, ଅଙ୍କ, vid_op);      \
        ଅନ୍ୟଥା                                                             \
            idx = pick_queue_family(qf, ଅଙ୍କ, type);                      \
                                                                         \
        ଯଦି (idx == -1)                                                   \
            ଜାରି;                                                    \
                                                                         \
        ପାଇଁ (i = 0; i < hwctx->nb_qf; i++) {                             \
            ଯଦି (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                ଭାଙ୍ଗ;                                                   \
            }                                                            \
        }                                                                \
        ଯଦି (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].ଅଙ୍କ = qf[idx].queueFamilyProperties.queue_ଗଣନା; \
            ଯଦି (p->limit_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା max = p->limit_queues;                               \
                ଯଦି (type == VK_QUEUE_GRAPHICS_BIT)                       \
                    hwctx->qf[i].ଅଙ୍କ = FFMIN(hwctx->qf[i].ଅଙ୍କ,           \
                                             max ? max : 1);             \
                ଅନ୍ୟଥା ଯଦି (max)                                            \
                    hwctx->qf[i].ଅଙ୍କ = FFMIN(hwctx->qf[i].ଅଙ୍କ, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } ଯେତେବେଳେ (0)

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

    ଯଦି (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_QUEUE_OPTICAL_FLOW_BIT_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#undef PICK_QF

    cd->pQueueCreateInfos = av_malloc_array(hwctx->nb_qf,
                                            ଆକାର(VkDeviceQueueCreateInfo));
    ଯଦି (!cd->pQueueCreateInfos)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା dup = 0;
        ଦଶମିକ *weights = ଖାଲି;
        VkDeviceQueueCreateInfo *pc;
        ପାଇଁ (uint32_t j = 0; j < cd->queue_Create_Info_ଗଣନା; j++) {
            ଯଦି (hwctx->qf[i].idx == cd->pQueueCreateInfos[j].queueFamilyIndex) {
                dup = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (dup)
            ଜାରି;

        weights = av_malloc_array(hwctx->qf[i].ଅଙ୍କ, ଆକାର(ଦଶମିକ));
        ଯଦି (!weights) {
            ପାଇଁ (uint32_t j = 0; j < cd->queue_Create_Info_ଗଣନା; j++)
                av_free((ଶୂନ୍ୟ *)cd->pQueueCreateInfos[i].pQueuePriorities);
            av_free((ଶୂନ୍ୟ *)cd->pQueueCreateInfos);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }

        ପାଇଁ (uint32_t j = 0; j < hwctx->qf[i].ଅଙ୍କ; j++)
            weights[j] = 1.0;

        pc = (VkDeviceQueueCreateInfo *)cd->pQueueCreateInfos;
        pc[cd->queue_Create_Info_ଗଣନା++] = (VkDeviceQueueCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .flags = hwctx->queue_flags,
            .queueFamilyIndex = hwctx->qf[i].idx,
            .queue_ଗଣନା = hwctx->qf[i].ଅଙ୍କ,
            .pQueuePriorities = weights,
        };
    }

    ଫେରନ୍ତୁ 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
ସ୍ଥିର ଶୂନ୍ୟ vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ଯଦି (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    ଯଦି (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    ଯଦି (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    ଯଦି (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

ସ୍ଥିର ଶୂନ୍ୟ vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    ଯଦି (p->qf_mutex) {
        ପାଇଁ (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_device_create_internal(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା disable_multiplane,
                                         AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VkResult ret;
    AVDictionaryEntry *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ଗଣନା FFVulkanDebugMode debug_mode = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    ଯଦି ((err = create_instance(ctx, opts, &debug_mode)))
        ଯାଅ end;

    /* Find a physical device (if not given one) */
    ଯଦି ((err = find_device(ctx, dev_select)))
        ଯାଅ end;

    /* Get supported memory types */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    ଯଦି ((err = check_extensions(ctx, 1, opts, &dev_info.ppEnabledExtensionNames,
                                &dev_info.enabled_Extension_ଗଣନା, debug_mode))) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dev_info.queue_Create_Info_ଗଣନା; i++)
            av_free((ଶୂନ୍ୟ *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
        av_free((ଶୂନ୍ୟ *)dev_info.pQueueCreateInfos);
        ଯାଅ end;
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
    opt_d = av_dict_get(opts, "limit_queues", ଖାଲି, 0);
    ଯଦି (opt_d)
        p->limit_queues = strtol(opt_d->ମୂଲ୍ୟ, ଖାଲି, 10);

    /* Setup enabled queue families */
    ଯଦି ((err = setup_queue_families(ctx, &dev_info)))
        ଯାଅ end;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dev_info.queue_Create_Info_ଗଣନା; i++)
        av_free((ଶୂନ୍ୟ *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
    av_free((ଶୂନ୍ୟ *)dev_info.pQueueCreateInfos);

    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dev_info.enabled_Extension_ଗଣନା; i++)
            av_free((ଶୂନ୍ୟ *)dev_info.ppEnabledExtensionNames[i]);
        av_free((ଶୂନ୍ୟ *)dev_info.ppEnabledExtensionNames);
        err = AVERROR_EXTERNAL;
        ଯାଅ end;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", ଖାଲି, 0);
    ଯଦି (opt_d)
        p->use_linear_images = strtol(opt_d->ମୂଲ୍ୟ, ଖାଲି, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    ଯଦି (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", ଖାଲି, 0);
        ଯଦି (opt_d)
            p->disable_multiplane = strtol(opt_d->ମୂଲ୍ୟ, ଖାଲି, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", ଖାଲି, 0);
    ଯଦି (opt_d)
        p->avoid_host_import = strtol(opt_d->ମୂଲ୍ୟ, ଖାଲି, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.ppEnabledExtensionNames;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_ଗଣନା;

    /* The extension lists need to be freed */
    ctx->ମୁକ୍ତ = vulkan_device_free;

end:
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ଶୂନ୍ୟ lock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t index)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ଯଦି (p->qf_mutex)
        pthread_mutex_lock(&p->qf_mutex[queue_family][index]);
}

ସ୍ଥିର ଶୂନ୍ୟ unlock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t index)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ଯଦି (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[queue_family][index]);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_device_init(AVHWDeviceContext *ctx)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    uint32_t qf_ଅଙ୍କ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkQueueFamilyProperties2 *qf;
    VkQueueFamilyVideoPropertiesKHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            ଯଦି (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                ଭାଙ୍ଗ;
            }
        }
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    ଯଦି (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        ଫେରନ୍ତୁ err;
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
    ଯଦି (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.minImportedHostPointerAlignment);

    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &qf_ଅଙ୍କ, ଖାଲି);
    ଯଦି (!qf_ଅଙ୍କ) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
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
#ଅନ୍ୟଥା
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;
#endif
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_ଅଙ୍କ, ଆକାର(VkQueueFamilyProperties2));
    ଯଦି (!qf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_ଅଙ୍କ, ଆକାର(VkQueueFamilyVideoPropertiesKHR));
    ଯଦି (!qf_vid) {
        av_free(qf);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ପାଇଁ (uint32_t i = 0; i < qf_ଅଙ୍କ; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .pNext = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : ଖାଲି,
        };
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &qf_ଅଙ୍କ, qf);

    p->nb_tot_qfs = qf_ଅଙ୍କ;

    ଯଦି (!(p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)) {
        p->qf_mutex = av_calloc(qf_ଅଙ୍କ, ଆକାର(*p->qf_mutex));
        ଯଦି (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            ଯାଅ end;
        }

        ପାଇଁ (uint32_t i = 0; i < qf_ଅଙ୍କ; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].queueFamilyProperties.queue_ଗଣନା,
                                       ଆକାର(**p->qf_mutex));
            ଯଦି (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                ଯାଅ end;
            }
            ପାଇଁ (uint32_t j = 0; j < qf[i].queueFamilyProperties.queue_ଗଣନା; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], ଖାଲି);
                ଯଦି (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    ଯାଅ end;
                }
            }
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < hwctx->nb_qf; i++) {
        ଯଦି (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                  VK_QUEUE_VIDEO_ENCODE_BIT_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < hwctx->nb_qf; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା seen = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = (i - 1); j >= 0; j--) {
            ଯଦି (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                seen = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!seen)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#ଯଦି FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    ଯଦି (!hwctx->lock_queue)
        hwctx->lock_queue = lock_queue;
    ଯଦି (!hwctx->unlock_queue)
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
    ଯଦି (p->transfer_qf) {
        VkQueueFlags flags = p->vkctx.qf_props[p->transfer_qf->idx].queueFamilyProperties.queueFlags;
        ଯଦି (!(flags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            p->transfer_offset_align = 4;
    }
#ifdef VK_KHR_maintenance11
    ଯଦି (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_offset_align = 1;
#endif

    /* Re-query device capabilities, in case the device was created externally */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

end:
    av_free(qf_vid);
    av_free(qf);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                                AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    ଯଦି (device && device[0]) {
        ଅକ୍ଷର *end = ଖାଲି;

        ଯଦି (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } ଅନ୍ୟଥା {
            dev_select.index = strtol(device, &end, 10);
            ଯଦି (end == device || *end) {
                dev_select.index = 0;
                dev_select.name  = device;
            }
        }
    }

    ଫେରନ୍ତୁ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_unused VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    ବାଛ(src_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#ଯଦି VA_CHECK_VERSION(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#endif
        ଅଚଳ ଅକ୍ଷର *vendor;

#ଯଦି VA_CHECK_VERSION(1, 15, 0)
        vas = vaGetDisplayAttributes(dpy, &attr, 1);
        ଯଦି (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.ମୂଲ୍ୟ & 0xFFFF);
#endif

        ଯଦି (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            ଯଦି (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                ଫେରନ୍ତୁ AVERROR_EXTERNAL;
            }

            ଯଦି (strstr(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        ଫେରନ୍ତୁ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#endif
#ଯଦି CONFIG_LIBDRM
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DRM: {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
        ସଂରଚନା stat drm_ଗଣ୍ଠି_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ଗଣ୍ଠି_info);
        ଯଦି (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ଗଣ୍ଠି_info.st_dev);
        dev_select.drm_minor = minor(drm_ଗଣ୍ଠି_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        ଯଦି (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        ଯଦି (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        ଫେରନ୍ତୁ vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#endif
#ଯଦି CONFIG_CUDA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADeviceContextInternal *cu_internal = src_hwctx->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_internal->cuda_device));
        ଯଦି (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        ଫେରନ୍ତୁ vulkan_device_create_internal(ctx, &dev_select, 1, opts, flags);
    }
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_frames_get_constraints(AVHWDeviceContext *ctx,
                                         ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2 = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    ପାଇଁ (ଗଣନା AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ଗଣନା_2 += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(ଗଣନା_2 + 1 + CONFIG_CUDA,
                                                    ଆକାର(ଗଣନା AVPixelFormat));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଗଣନା_2 = 0;
    ପାଇଁ (ଗଣନା AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ଯଦି (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[ଗଣନା_2++] = vk_formats_list[i].pixfmt;
        }
    }

#ଯଦି CONFIG_CUDA
    constraints->valid_sw_formats[ଗଣନା_2++] = AV_PIX_FMT_CUDA;
#endif

    constraints->valid_sw_formats[ଗଣନା_2++] = AV_PIX_FMT_NONE;

    constraints->min_width  = 1;
    constraints->min_height = 1;
    constraints->max_width  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_height = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(ଗଣନା AVPixelFormat));
    ଯଦି (!constraints->valid_hw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା alloc_mem(AVHWDeviceContext *ctx, VkMemoryRequirements *req,
                     VkMemoryPropertyFlagBits req_flags, ଅଚଳ ଶୂନ୍ୟ *alloc_extension,
                     VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    VkResult ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = -1;
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
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < p->mprops.memory_Type_ଗଣନା; i++) {
        ଅଚଳ VkMemoryType *type = &p->mprops.memoryTypes[i];

        /* The memory type must be supported by the requirements (bitfield) */
        ଯଦି (!(req->memoryTypeBits & (1 << i)))
            ଜାରି;

        /* The memory type flags must include our properties */
        ଯଦି ((type->propertyFlags & req_flags) != req_flags)
            ଜାରି;

        /* The memory type must be large enough */
        ଯଦି (req->size > p->mprops.memoryHeaps[type->heapIndex].size)
            ଜାରି;

        /* Found a suitable memory type */
        index = i;
        ଭାଙ୍ଗ;
    }

    ଯଦି (index < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    alloc_info.memoryTypeIndex = index;

    ret = vk->AllocateMemory(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.memoryTypes[index].propertyFlags;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ vulkan_free_internal(VulkanDevicePriv *p, AVVkFrame *f)
{
    av_unused AVVkFrameInternal *internal = f->internal;

    // Make this function safe to call repeatedly
    ଯଦି (!internal)
        ଫେରନ୍ତୁ;

#ଯଦି CONFIG_CUDA
    ଯଦି (internal->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)internal->cuda_fc_ref->data;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
            ଯଦି (internal->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(internal->cu_sem[i]));
            ଯଦି (internal->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(internal->cu_mma[i]));
            ଯଦି (internal->ext_mem[i])
                CHECK_CU(cu->cuDestroyExternalMemory(internal->ext_mem[i]));
#ifdef _WIN32
            ଯଦି (internal->ext_sem_handle[i])
                CloseHandle(internal->ext_sem_handle[i]);
            ଯଦି (internal->ext_mem_handle[i])
                CloseHandle(internal->ext_mem_handle[i]);
#endif
        }

        av_buffer_unref(&internal->cuda_fc_ref);
    }
#endif

    ଯଦି (internal->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, internal->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&internal->update_mutex);
    av_freep(&f->internal);
}

ସ୍ଥିର ଶୂନ୍ୟ vulkan_frame_free(AVHWFramesContext *hwfc, AVVkFrame *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(f);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sems = 0;

    ଯେତେବେଳେ (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    ଯଦି (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_ମୂଲ୍ୟଗୁଡ଼ିକ        = f->sem_ମୂଲ୍ୟ,
            .semaphore_ଗଣନା = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_internal(p, f);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->FreeMemory(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

ସ୍ଥିର ଶୂନ୍ୟ vulkan_frame_free_cb(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    vulkan_frame_free(opaque, (AVVkFrame*)data);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା alloc_bind_mem(AVHWFramesContext *hwfc, AVVkFrame *f,
                          ଶୂନ୍ୟ *alloc_pnext, size_t alloc_pnext_stride)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା img_cnt = 0, err;
    VkResult ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkBindImageMemoryInfo bind_info[AV_ଅଙ୍କ_DATA_POINTERS] = { { 0 } };

    ଯେତେବେଳେ (f->img[img_cnt]) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_ded_mem;
        VkImageMemoryRequirementsInfo2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        VkMemoryDedicatedAllocateInfo ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .pNext = (ଶୂନ୍ୟ *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
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

        ଯଦି (f->tiling == VK_IMAGE_TILING_LINEAR)
            req.memoryRequirements.size = FFALIGN(req.memoryRequirements.size,
                                                  p->props.properties.limits.minMemoryMapAlignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefersDedicatedAllocation |
                      ded_req.requiresDedicatedAllocation;
        ଯଦି (((VulkanFramesPriv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        ଯଦି (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        ଯଦି ((err = alloc_mem(ctx, &req.memoryRequirements,
                             f->tiling == VK_IMAGE_TILING_LINEAR ?
                             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT :
                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                             use_ded_mem ? &ded_alloc : (ଶୂନ୍ୟ *)ded_alloc.pNext,
                             &f->flags, &f->mem[img_cnt])))
            ଫେରନ୍ତୁ err;

        f->size[img_cnt] = req.memoryRequirements.size;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].memory = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ଗଣନା PrepMode {
    PREP_MODE_GENERAL,
    PREP_MODE_WRITE,
    PREP_MODE_EXTERNAL_EXPORT,
    PREP_MODE_EXTERNAL_IMPORT,
    PREP_MODE_DECODING_DST,
    PREP_MODE_DECODING_DPB,
    PREP_MODE_ENCODING_DPB,
};

ସ୍ଥିର ଶୂନ୍ୟ switch_new_props(ଗଣନା PrepMode pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    ବାଛ (pmode) {
    ସ୍ଥିତି PREP_MODE_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି PREP_MODE_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, ଗଣନା PrepMode pmode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkImageMemoryBarrier2 img_bar[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    ଯଦି (pmode == PREP_MODE_EXTERNAL_EXPORT) {
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
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, &tmp_frame,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    ff_vk_frame_barrier(&p->vkctx, exec, &tmp_frame, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .pImageMemoryBarriers = img_bar,
            .image_Memory_Barrier_ଗଣନା = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVkFrame *frame, ଗଣନା PrepMode pmode)
{
    VkResult ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(frame);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_ଗଣନା; i++) {
        ଯଦି (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            ଭାଙ୍ଗ;
    }
    ଯଦି (i == p->vkctx.host_image_props.copy_Dst_Layout_ଗଣନା)
        ଫେରନ୍ତୁ AVERROR(ENOTSUP);

    ପାଇଁ (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = frame->img[i],
            .oldLayout = frame->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.layer_ଗଣନା = 1,
            .subresourceRange.level_ଗଣନା = 1,
        };
        frame->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା prepare_frame(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, ଗଣନା PrepMode pmode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    AVVulkanFramesContext *hwfc_vk = hwfc->hwctx;
    ଯଦି (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT &&
        (pmode != PREP_MODE_EXTERNAL_EXPORT) &&
        (pmode != PREP_MODE_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, frame, pmode);
        ଯଦି (err != AVERROR(ENOTSUP))
            ଫେରନ୍ତୁ err;
    }

    ଫେରନ୍ତୁ switch_layout(hwfc, ectx, frame, pmode);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ get_plane_wh(uint32_t *w, uint32_t *h, ଗଣନା AVPixelFormat format,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    ଯଦି (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = frame_w;
        *h = frame_h;
        ଫେରନ୍ତୁ;
    }

    *w = AV_CEIL_RSHIFT(frame_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(frame_h, desc->log2_chroma_h);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା create_frame(AVHWFramesContext *hwfc, AVVkFrame **frame,
                        VkImageTiling tiling, VkImageUsageFlagBits usage,
                        VkImageCreateFlags flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_layers,
                        ଶୂନ୍ୟ *create_pnext)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
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
        .initial_ମୂଲ୍ୟ  = 0,
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
#ଅନ୍ୟଥା
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
#endif
    };

    /* Check if exporting is supported before chaining any structs */
    ଯଦି (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT) {
        ଯଦି (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_frame_alloc();
    ଯଦି (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
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
            .samples               = VK_SAMPLE_ଗଣନା_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ଗଣନା = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, hwfc->width, hwfc->height, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ଯାଅ fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }

        f->queue_family[i] = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ମୂଲ୍ୟ[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *frame = f;
    ଫେରନ୍ତୁ 0;

fail:
    vulkan_frame_free(hwfc, f);
    ଫେରନ୍ତୁ err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
ସ୍ଥିର ଶୂନ୍ୟ try_export_flags(AVHWFramesContext *hwfc,
                             VkExternalMemoryHandleTypeFlags *comp_handle_types,
                             VkExternalMemoryHandleTypeFlags *iexp,
                             VkExternalMemoryHandleTypeFlagBits exp)
{
    VkResult ret;
    AVVulkanFramesContext *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ଅଚଳ VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .pNext = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pNext = ଖାଲି,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_Index_ଗଣନା = p->nb_img_qfs,
        .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                     VK_SHARING_MODE_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = exp,
        .pNext = has_mods ? &phy_dev_mod_info : ଖାଲି,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .pNext  = !exp ? ଖାଲି : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_BIT),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_ଗଣନା : 1;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_mods; i++) {
        ଯଦି (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        ଯଦି (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (unsigned long long)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        ଯଦି (ret == VK_SUCCESS) {
            *iexp |= exp;
            *comp_handle_types |= eprops.externalMemoryProperties.compatibleHandleTypes;
            ଯଦି (exp == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT) {
                VulkanFramesPriv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.externalMemoryProperties.externalMemoryFeatures &
                                                  VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
ସ୍ଥିର ଶୂନ୍ୟ get_export_handle_types(AVHWFramesContext *hwfc,
                                    VkExternalMemoryHandleTypeFlags *comp_handle_types,
                                    VkExternalMemoryHandleTypeFlags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_unused AVVulkanFramesContext *hwctx = &((VulkanFramesPriv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#ifdef _WIN32
    ଯଦି (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT
                             : VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT);
#ଅନ୍ୟଥା
    ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);

    ଯଦି (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_MEMORY &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT);
#endif
}

ସ୍ଥିର AVBufferRef *vulkan_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    AVVkFrame *f;
    AVBufferRef *avbuf = ଖାଲି;
    AVHWFramesContext *hwfc = opaque;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VkExternalMemoryHandleTypeFlags e;
    VkExportMemoryAllocateInfo eminfo[AV_ଅଙ୍କ_DATA_POINTERS];

    VkExternalMemoryImageCreateInfo eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
        .pNext       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < av_pix_fmt_ଗଣନା_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
        eminfo[i].pNext       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    ଯଦି (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, ଆକାର(*eminfo));
    ଯଦି (err)
        ଯାଅ fail;

    ଯଦି ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR))
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DPB);
    ଅନ୍ୟଥା ଯଦି (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DST);
    ଅନ୍ୟଥା ଯଦି (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_ENCODING_DPB);
    ଅନ୍ୟଥା ଯଦି (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_WRITE);
    ଅନ୍ୟଥା
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_GENERAL);
    ଯଦି (err)
        ଯାଅ fail;

    avbuf = av_buffer_create((uint8_t *)f, ଆକାର(AVVkFrame),
                             vulkan_frame_free_cb, hwfc, 0);
    ଯଦି (!avbuf)
        ଯାଅ fail;

    ଫେରନ୍ତୁ avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_frame_free(hwfc, f);
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ lock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_lock(&vkf->internal->update_mutex);
}

ସ୍ଥିର ଶୂନ୍ୟ unlock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_unlock(&vkf->internal->update_mutex);
}

ସ୍ଥିର ଶୂନ୍ୟ vulkan_frames_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;

    ଯଦି (fp->modifier_info) {
        ଯଦି (fp->modifier_info->pDrmFormatModifiers)
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
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
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
    ଅଚଳ ସଂରଚନା FFVkFormatEntry *fmt = vk_find_format_entry(hwfc->sw_format);
    ଯଦି (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        ଫେରନ୍ତୁ 0;
    }

    ଅଚଳ VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_ଗଣନା;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_mods = has_mods ? mod_list->drm_Format_Modifier_ଗଣନା : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    ଯଦି (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        ଫେରନ୍ତୁ 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_Index_ଗଣନା = p->nb_img_qfs,
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

    ଯଦି (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ଅଚଳ VkVideoProfileListInfoKHR *pl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    ଯଦି (pl) {
        profile_list = *pl;
        profile_list.pNext = ଖାଲି;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ଅଚଳ VkImageFormatListCreateInfo *fl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    ଯଦି (fl) {
        format_list = *fl;
        format_list.pNext = ଖାଲି;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < AV_ଅଙ୍କ_DATA_POINTERS &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .pNext = &perf,
            };

            ଯଦି (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            ଯଦି (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                ଫେରନ୍ତୁ 0;
            }

            ଯଦି (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identicalMemoryLayout);
                ଫେରନ୍ତୁ 0;
            }
        }
    }

    ଯଦି (!p->vkctx.host_image_props.identicalMemoryTypeRequirements) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା index;
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
            .samples     = VK_SAMPLE_ଗଣନା_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ଗଣନା = p->nb_img_qfs,
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
        ପାଇଁ (index = 0; index < p->mprops.memory_Type_ଗଣନା; index++) {
            ଯଦି (!(req.memoryRequirements.memoryTypeBits & (1U << index)))
                ଜାରି;
            ଯଦି ((p->mprops.memoryTypes[index].propertyFlags & req_flags) == req_flags)
                ଭାଙ୍ଗ;
        }
        ଯଦି (index == p->mprops.memory_Type_ଗଣନା) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            ଫେରନ୍ତୁ 0;
        }
    }

    ଫେରନ୍ତୁ 1;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_frames_init(AVHWFramesContext *hwfc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    AVVkFrame *f;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ଅଚଳ ସଂରଚନା FFVkFormatEntry *fmt;
    ଅଚଳ AVPixFmtDescriptor *desc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_FRAME_FLAG_DISABLE_MULTIPLANE);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)));

    /* Defaults */
    ଯଦି (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    ଯଦି (p->use_linear_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_LINEAR;


    fmt = vk_find_format_entry(hwfc->sw_format);
    ଯଦି (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        ଫେରନ୍ତୁ AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ଯଦି ((hwfc->width  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->height & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    ଯଦି (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        ଯଦି (hwctx->format[0] != fmt->vkf) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < fmt->nb_images_fallback; i++) {
                ଯଦି (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    ଫେରନ୍ତୁ AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, ଖାଲି,
                                 ଖାଲି, ଖାଲି, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        ଯଦି (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    } ଅନ୍ୟଥା {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, ଖାଲି,
                                 ଖାଲି, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        ଯଦି (err < 0)
            ଫେରନ୍ତୁ err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_find_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    ଯଦି (!is_lone_dpb && !drm_mod_with_video) {
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
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        ଯଦି ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        ଯଦି (!hwctx->img_flags) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_BIT |
                                             VK_IMAGE_USAGE_STORAGE_BIT);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
            ଯଦି (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_BIT;
                ଯଦି ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_BIT;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    ଯଦି ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ଅଚଳ VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_find_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        ଯଦି (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        } ଅନ୍ୟଥା {
            uint32_t i;
            ପାଇଁ (i = 0; i < pl->profile_ଗଣନା; i++) {
                /* Video ops start at exactly 0x00010000 */
                ଯଦି (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    ଭାଙ୍ଗ;
            }
            ଯଦି (i == pl->profile_ଗଣନା)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    ଯଦି ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

    ଯଦି (!hwctx->lock_frame)
        hwctx->lock_frame = lock_frame;

    ଯଦି (!hwctx->unlock_frame)
        hwctx->unlock_frame = unlock_frame;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, ଖାଲି);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, ଖାଲି);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, ଖାଲି);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    /* Test to see if allocation will fail */
    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    ଯଦି (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        ଯଦି (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_frame_free(hwfc, f);
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = ଖାଲି;

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
                av_calloc(modp.drm_Format_Modifier_ଗଣନା, ଆକାର(*modp.pDrmFormatModifierProperties));
            ଯଦି (!modp.pDrmFormatModifierProperties) {
                vulkan_frame_free(hwfc, f);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            ପାଇଁ (uint32_t j = 0; j < modp.drm_Format_Modifier_ଗଣନା; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                ଯଦି (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    ଭାଙ୍ଗ;
                }
            }

            ଯଦି (mod_props == ଖାଲି) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_frame_free(hwfc, f);
                ଫେରନ୍ତୁ AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_frame_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    ଯଦି (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal = av_buffer_pool_init2(ଆକାର(AVVkFrame),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  ଖାଲି);
        ଯଦି (!ffhwframesctx(hwfc)->pool_internal)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_get_buffer(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(hwfc->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VULKAN;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       ଗଣନା AVHWFrameTransferDirection dir,
                                       ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *fmts;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 2;

#ଯଦି CONFIG_CUDA
    n++;
#endif
    fmts = av_malloc_array(n, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#ଯଦି CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#endif
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ଫେରନ୍ତୁ 0;
}

#ଯଦି CONFIG_LIBDRM
ସ୍ଥିର ଶୂନ୍ୟ vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_frame_free(hwfc, hwmap->priv);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
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

ସ୍ଥିର ଧାଡ଼ିଭିତରେ VkFormat drm_to_vulkan_fmt(uint32_t drm_fourcc)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ଯଦି (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            ଫେରନ୍ତୁ vulkan_drm_format_map[i].vk_format;
    ଫେରନ୍ତୁ VK_FORMAT_UNDEFINED;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_from_drm_frame_desc(AVHWFramesContext *hwfc, AVVkFrame **frame,
                                          ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VkResult ret;
    AVVkFrame *f;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ଅଚଳ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->data[0];
    VkBindImageMemoryInfo bind_info[AV_DRM_MAX_PLANES];
    VkBindImagePlaneMemoryInfo plane_info[AV_DRM_MAX_PLANES];

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_layers; i++) {
        ଯଦି (drm_to_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଯଦି (!(f = av_vk_frame_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_layers; i++) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_ମୂଲ୍ୟ  = 0,
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
            .drm_Format_Modifier_Plane_ଗଣନା = planes,
            .pPlaneLayouts = (ଅଚଳ VkSubresourceLayout *)&ext_img_layouts,
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
            .samples               = VK_SAMPLE_ଗଣନା_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_Index_ଗଣନା = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        ଯଦି (planes == 1) {
            ଅଚଳ VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            ଯଦି (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
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
            .queue_Family_Index_ଗଣନା = create_info.queue_Family_Index_ଗଣନା,
            .sharingMode = create_info.sharingMode,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .pNext = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        ଯଦି (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        ଯଦି (flags & AV_HWFRAME_MAP_WRITE)
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
        ଯଦି (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, src->width, src->height, i);

        /* Set the subresource layout based on the layer properties */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < planes; j++) {
            ext_img_layouts[j].offset     = desc->layers[i].planes[j].offset;
            ext_img_layouts[j].rowPitch   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].size       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].depthPitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            ଯାଅ fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            ଯାଅ fail;
        }

        f->queue_family[i] = VK_QUEUE_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_ମୂଲ୍ୟ[i] = 0;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_layers; i++) {
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
        ଯଦି (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            ଯାଅ fail;
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
        ଯଦି (err) {
            close(idesc.fd);
            ଯାଅ fail;
        }

        f->size[i] = req2.memoryRequirements.size;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_layers; i++) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = desc->layers[i].nb_planes;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < planes; j++) {
            VkImageAspectFlagBits aspect = j == 0 ? VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT :
                                                    VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
            plane_info[bind_counts].pNext = ଖାଲି;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
            bind_info[bind_counts].pNext  = planes > 1 ? &plane_info[bind_counts] : ଖାଲି;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].memory = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].memoryOffset = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        ଯାଅ fail;
    }

    *frame = f;

    ଫେରନ୍ତୁ 0;

fail:
    vulkan_frame_free(hwfc, f);

    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_from_drm_frame_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ଅଚଳ AVDRMFrameDescriptor *desc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VkResult ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ଯଦି (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        VkCommandBuffer cmd_buf;
        FFVkExecContext *exec;
        VkImageMemoryBarrier2 img_bar[AV_ଅଙ୍କ_DATA_POINTERS];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_img_bar = 0;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ଦ୍ୱିମିକ,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            ସଂରଚନା dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            ଯଦି (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                ପାଇଁ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ଫେରନ୍ତୁ err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            ଯଦି (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ପାଇଁ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ଫେରନ୍ତୁ err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_BIT,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            ଯଦି (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                ପାଇଁ (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                ଫେରନ୍ତୁ err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_start(&p->vkctx, exec);
        ଯଦି (err < 0) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            ଫେରନ୍ତୁ err;
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
        ଯଦି (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            ଫେରନ୍ତୁ err;
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
                .image_Memory_Barrier_ଗଣନା = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        ଯଦି (err < 0)
            ଫେରନ୍ତୁ err;
    } ଅନ୍ୟଥା
#endif
    {
        AVVkFrame *f = (AVVkFrame *)dst->data[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_IMPORT);
        ଯଦି (err)
            ଫେରନ୍ତୁ err;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    AVVkFrame *f;
    ଅଚଳ AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->data[0];

    ଯଦି ((err = vulkan_map_from_drm_frame_desc(hwfc, &f, src, flags)))
        ଫେରନ୍ତୁ err;

    /* The unmapping function will free this */
    dst->data[0] = (uint8_t *)f;
    dst->width   = src->width;
    dst->height  = src->height;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = vulkan_map_from_drm_frame_sync(hwfc, dst, desc, flags);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    ଫେରନ୍ତୁ 0;

fail:
    vulkan_frame_free(hwfc->device_ctx->hwctx, f);
    dst->data[0] = ଖାଲି;
    ଫେରନ୍ତୁ err;
}

#ଯଦି CONFIG_VAAPI
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ଅଚଳ AVFrame *src,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    AVFrame *tmp = av_frame_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->data[3];

    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_ମୌଳିକ;

    err = av_hwframe_map(tmp, src, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ଫେରନ୍ତୁ err;
}
#endif
#endif

#ଯଦି CONFIG_CUDA
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା export_mem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx,
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#ଅନ୍ୟଥା
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
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }
#endif

    ret = CHECK_CU(cu->cuImportExternalMemory(&dst_int->ext_mem[idx], &ext_desc));
    ଯଦି (ret < 0) {
#ifndef _WIN32
        close(ext_desc.handle.fd);
#endif
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା export_sem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx,
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
#ଅନ୍ୟଥା
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
#ଅନ୍ୟଥା
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#endif
    ଯଦି (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }
#ifdef _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#endif

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    ଯଦି (ret < 0) {
#ifndef _WIN32
        close(ext_sem_desc.handle.fd);
#endif
        ଫେରନ୍ତୁ AVERROR_EXTERNAL;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_export_to_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ଅଚଳ AVFrame *frame)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VkResult ret;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUarray_format cufmt = desc->comp[0].depth > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା elem_size = 1 + (desc->comp[0].depth > 8);

    dst_f = (AVVkFrame *)frame->data[0];
    dst_int = dst_f->internal;

    ଯଦି (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_buffer_ref(cuda_hwfc);
        ଯଦି (!dst_int->cuda_fc_ref)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        nb_images = ff_vk_ଗଣନା_images(dst_f);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
            err = export_mem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->size[i]);
            ଯଦି (err < 0)
                ଯାଅ fail;

            err = export_sem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            ଯଦି (err < 0)
                ଯାଅ fail;
        }

        ଯଦି (nb_images != planes) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                ଯଦି (desc->comp[i].step / elem_size > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    ଯାଅ fail;
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

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
            CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC tex_desc = {
                .offset = offsets[i],
                .arrayDesc = {
                    .Depth = 0,
                    .Format = cufmt,
                    .ଅଙ୍କ_Channels = desc->comp[i].step / elem_size,
                    .Flags = 0,
                },
                .ଅଙ୍କ_Levels = 1,
            };
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);
            tex_desc.arrayDesc.Width = p_w;
            tex_desc.arrayDesc.Height = p_h;

            ret = CHECK_CU(cu->cuExternalMemoryGetMappedMipmappedArray(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            ଯଦି (ret < 0) {
                err = AVERROR_EXTERNAL;
                ଯାଅ fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            ଯଦି (ret < 0) {
                err = AVERROR_EXTERNAL;
                ଯାଅ fail;
            }

        }
    }

    ଫେରନ୍ତୁ 0;

fail:
    vulkan_free_internal(p, dst_f);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_data_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_frames_ctx->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)dst->data[0];
    nb_images = ff_vk_ଗଣନା_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    err = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(cuda_dev->cuda_ctx));
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    err = vulkan_export_to_cuda(hwfc, src->hw_frames_ctx, dst);
    ଯଦି (err < 0) {
        CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
        ଫେରନ୍ତୁ err;
    }

    dst_int = dst_f->internal;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ମୂଲ୍ୟ = dst_f->sem_ମୂଲ୍ୟ[i] + 0;
        s_s_par[i].params.fence.ମୂଲ୍ୟ = dst_f->sem_ମୂଲ୍ୟ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .srcMemoryType = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->data[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dstMemoryType = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = p_w * desc->comp[i].step;
        cpy.Height = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        ଯଦି (err < 0)
            ଯାଅ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++)
        dst_f->sem_ମୂଲ୍ୟ[i]++;

    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    ଫେରନ୍ତୁ err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_buffer_unref(&dst->buf[0]);
    ଫେରନ୍ତୁ err;
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ବାଛ (src->format) {
#ଯଦି CONFIG_LIBDRM
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ଫେରନ୍ତୁ vulkan_map_from_vaapi(hwfc, dst, src, flags);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ଫେରନ୍ତୁ vulkan_map_from_drm(hwfc, dst, src, flags);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
}

#ଯଦି CONFIG_LIBDRM
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVkFrame *source;
} VulkanDRMMapping;

ସ୍ଥିର ଶୂନ୍ୟ vulkan_unmap_to_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_frame_sync(hwfc, hwmap->source, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ uint32_t vulkan_fmt_to_drm(VkFormat vkfmt)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ଯଦି (vulkan_drm_format_map[i].vk_format == vkfmt)
            ଫେରନ୍ତୁ vulkan_drm_format_map[i].drm_fourcc;
    ଫେରନ୍ତୁ DRM_FORMAT_INVALID;
}

#define MAX_MEMORY_PLANES 4
ସ୍ଥିର VkImageAspectFlags plane_index_to_aspect(ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane) {
    ଯଦି (plane == 0) ଫେରନ୍ତୁ VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
    ଯଦି (plane == 1) ଫେରନ୍ତୁ VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT;
    ଯଦି (plane == 2) ଫେରନ୍ତୁ VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;
    ଯଦି (plane == 3) ଫେରନ୍ତୁ VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT;

    av_assert2 (0 && "Invalid plane index");
    ଫେରନ୍ତୁ VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
}

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVkFrame *f,
                                     VulkanFramesPriv *fp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sems)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sync_fd = -1;
    VkResult ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ଯଦି (f->internal->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .pNext         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ଦ୍ୱିମିକ,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->internal->drm_sync_sem);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    ଯଦି (ff_vk_exec_start(&p->vkctx, exec) >= 0) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_sems; i++)
            ff_vk_exec_add_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_ମୂଲ୍ୟ[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        ff_vk_exec_add_dep_bool_sem(&p->vkctx, exec, &f->internal->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 0);
        ଯଦି (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->internal->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            ଯଦି (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    ଫେରନ୍ତୁ sync_fd;
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
    VkResult ret;
    AVVkFrame *f = (AVVkFrame *)src->data[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sems = nb_images;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା free_drm_desc_on_err = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(ଆକାର(*drm_desc));
    ଯଦି (!drm_desc)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_EXPORT);
    ଯଦି (err < 0)
        ଯାଅ end;

#ifdef DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        ଯଦି (err < 0)
            ଯାଅ end;
        sync_fd = err;
        err = 0;
    }
#endif

    ଯଦି (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_ଗଣନା = nb_sems,
            .pSemaphores    = f->sem,
            .p_ମୂଲ୍ୟଗୁଡ଼ିକ        = f->sem_ମୂଲ୍ୟ,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &vulkan_unmap_to_drm, drm_desc);
    ଯଦି (err < 0)
        ଯାଅ end;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    ଯଦି (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        ଯାଅ end;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; (i < planes) && (f->mem[i]); i++) {
        VkMemoryGetFdInfoKHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
            .memory     = f->mem[i],
            .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };

        ret = vk->GetMemoryFdKHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        ଯଦି (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            ଯାଅ end;
        }

#ଯଦି HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        ଯଦି (sync_fd >= 0) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା dup_fd = dup(sync_fd);
            ଯଦି (dup_fd >= 0) {
                ସଂରଚନା dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                ଯଦି (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } ଅନ୍ୟଥା {
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
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_to_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_ଗଣନା;

        ଯଦି (drm_desc->layers[i].nb_planes > MAX_MEMORY_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            ଯାଅ end;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspectMask = plane_index_to_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_index = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].offset = layout.offset;
            drm_desc->layers[i].planes[j].pitch  = layout.rowPitch;
        }

        ଯଦି (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            ଯାଅ end;
        }


        ଯଦି (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            ଜାରି;

    }

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[0] = (uint8_t *)drm_desc;
    dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);

    ଯଦି (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    ଫେରନ୍ତୁ 0;

end:
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    ଯଦି (free_drm_desc_on_err)
        av_free(drm_desc);
    ଯଦି (sync_fd >= 0)
        close(sync_fd);
    ଫେରନ୍ତୁ err;
}

#ଯଦି CONFIG_VAAPI
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_to_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    AVFrame *tmp = av_frame_alloc();
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ମୌଳିକ;

    err = vulkan_map_to_drm(hwfc, tmp, src, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = av_hwframe_map(dst, tmp, flags);
    ଯଦି (err < 0)
        ଯାଅ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    ଫେରନ୍ତୁ err;
}
#endif
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ବାଛ (dst->format) {
#ଯଦି CONFIG_LIBDRM
    ସ୍ଥିତି AV_PIX_FMT_DRM_ମୌଳିକ:
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ଫେରନ୍ତୁ vulkan_map_to_drm(hwfc, dst, src, flags);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
        ଯଦି (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            ଫେରନ୍ତୁ vulkan_map_to_vaapi(hwfc, dst, src, flags);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା copy_buffer_data(AVHWFramesContext *hwfc, FFVkBuffer *vkbuf,
                            AVFrame *swf, VkBufferImageCopy *region,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bytewidth[AV_ଅଙ୍କ_DATA_POINTERS];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->width, i);
        ଯଦି (bytewidth[i] < 0)
            ଫେରନ୍ତୁ bytewidth[i];
    }

    ଯଦି (upload) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].bufferOffset,
                                region[i].bufferRowLength,
                                swf->data[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.height);

        err = ff_vk_flush_buffer(&p->vkctx, vkbuf, 0, VK_WHOLE_SIZE, 1);
        ଯଦି (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }
    } ଅନ୍ୟଥା {
        err = ff_vk_flush_buffer(&p->vkctx, vkbuf, 0, VK_WHOLE_SIZE, 0);
        ଯଦି (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            ଫେରନ୍ତୁ AVERROR_EXTERNAL;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
            av_image_copy_plane(swf->data[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].bufferOffset,
                                region[i].bufferRowLength,
                                bytewidth[i],
                                region[i].imageExtent.height);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_plane_buf(AVHWFramesContext *hwfc, FFVkBuffer **dst,
                         AVFrame *swf, VkBufferImageCopy *region, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    uint32_t p_w, p_h;
    VulkanFramesPriv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(swf->format);
    VkBufferUsageFlags buf_usage = upload ? VK_BUFFER_USAGE_TRANSFER_SRC_BIT :
                                            VK_BUFFER_USAGE_TRANSFER_DST_BIT;

    size_t buf_offset = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        region[i] = (VkBufferImageCopy) {
            .bufferOffset = buf_offset,
            .bufferRowLength = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimalBufferCopyRowPitchAlignment),
            .bufferImageHeight = p_h,
            .imageSubresource.layer_ଗଣନା = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_offset += FFALIGN(p_h*region[i].bufferRowLength,
                              p->props.properties.limits.optimalBufferCopyOffsetAlignment);
    }

    err = ff_vk_get_pooled_buffer(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  ଖାଲି, buf_offset,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                  p->vkctx.host_cached_flag);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା host_map_frame(AVHWFramesContext *hwfc, FFVkBuffer **dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_bufs,
                          AVFrame *swf, VkBufferImageCopy *region, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_src_bufs;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(swf->format);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    VkBufferUsageFlags buf_usage = upload ? VK_BUFFER_USAGE_TRANSFER_SRC_BIT :
                                            VK_BUFFER_USAGE_TRANSFER_DST_BIT;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    ଯେତେବେଳେ (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    ଯଦି (nb_src_bufs == 1) {
        err = ff_vk_host_map_buffer(&p->vkctx, &dst[0],
                                    swf->data[0], VK_WHOLE_SIZE, swf->buf[0],
                                    buf_usage);
        ଯଦି (err < 0)
            ଫେରନ୍ତୁ err;
        (*nb_bufs)++;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
            region[i].bufferOffset = dst[0]->virtual_offset +
                                     swf->data[i] - swf->data[0];
    } ଅନ୍ୟଥା ଯଦି (nb_src_bufs == planes) { /* One buffer per plane */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
            err = ff_vk_host_map_buffer(&p->vkctx, &dst[i],
                                        swf->data[i], VK_WHOLE_SIZE,
                                        swf->buf[i], buf_usage);
            ଯଦି (err < 0)
                ଯାଅ fail;
            (*nb_bufs)++;

            region[i].bufferOffset = dst[i]->virtual_offset;
        }
    } ଅନ୍ୟଥା {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        ଫେରନ୍ତୁ AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା align = FFMAX(desc->comp[i].step, p->transfer_offset_align);
        ଯଦି ((align & (align - 1)) || (region[i].bufferOffset & (align - 1))) {
            err = AVERROR(EINVAL);
            ଯାଅ fail;
        }
    }

    ଫେରନ୍ତୁ 0;

fail:
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->data[0];
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(swf->format);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_layout_ch = 0;

    hwfc_vk->lock_frame(hwfc, hwf_vk);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା compat = 0;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ଗଣନା; j++) {
            ଯଦି (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (compat)
            ଜାରି;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .level_ଗଣନା = 1,
                .layer_ଗଣନା = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_ମୂଲ୍ୟଗୁଡ଼ିକ = hwf_vk->sem_ମୂଲ୍ୟ,
        .semaphore_ଗଣନା = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    ଯଦି (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    ଯଦି (upload) {
        VkMemoryToImageCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_ଗଣନା = 1,
            },
        };
        VkCopyMemoryToImageInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT,
            .region_ଗଣନା = 1,
            .pRegions = &region_info,
        };
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା img_idx = FFMIN(i, (nb_images - 1));
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
    } ଅନ୍ୟଥା {
        VkImageToMemoryCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT,
            .imageSubresource = {
                .layer_ଗଣନା = 1,
            },
        };
        VkCopyImageToMemoryInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT,
            .region_ଗଣନା = 1,
            .pRegions = &region_info,
        };
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା img_idx = FFMIN(i, (nb_images - 1));
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

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_frame(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା host_mapped = 0;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->data[0];
    VkBufferImageCopy region[AV_ଅଙ୍କ_DATA_POINTERS]; // always one per plane

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(swf->format);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images = ff_vk_ଗଣନା_images(hwf_vk);

    VkImageMemoryBarrier2 img_bar[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_img_bar = 0;

    FFVkBuffer *bufs[AV_ଅଙ୍କ_DATA_POINTERS];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_bufs = 0;

    VkCommandBuffer cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    ଯଦି ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (swf->width > hwfc->width || swf->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
        ଯଦି (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    ଯଦି (!upload && host_copy) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା compat = 0;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_ଗଣନା; j++) {
                ଯଦି (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    ଭାଙ୍ଗ;
                }
            }
            ଯଦି (!compat) {
                host_copy = 0;
                ଭାଙ୍ଗ;
            }
        }
    }

    ଯଦି (host_copy)
        ଫେରନ୍ତୁ vulkan_transfer_host(hwfc, hwf, swf, upload);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < av_pix_fmt_ଗଣନା_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        /* Buffer region for this plane */
        region[i] = (VkBufferImageCopy) {
            .bufferOffset = 0,
            .bufferRowLength = FFABS(swf->linesize[i]),
            .bufferImageHeight = p_h,
            .imageSubresource.layer_ଗଣନା = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    ଯଦି (host_map) {
        err = host_map_frame(hwfc, bufs, &nb_bufs, swf, region, upload);
        ଯଦି (err >= 0)
            host_mapped = 1;
    }

    ଯଦି (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        ଯଦି (err < 0)
            ଯାଅ end;
        nb_bufs = 1;

        ଯଦି (upload) {
            err = copy_buffer_data(hwfc, bufs[0], swf, region, planes, 1);
            ଯଦି (err < 0)
                ଯାଅ end;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_start(&p->vkctx, exec);
    ଯଦି (err < 0)
        ଯାଅ end;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_TRANSFER_BIT);
    ଯଦି (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        ଯାଅ end;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    ଯଦି (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        ଯଦି (host_mapped) {
            err = ff_vk_exec_add_dep_sw_frame(&p->vkctx, exec, swf);
            ଯଦି (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                ଯାଅ end;
            }
        }

        /* Add the buffers as a dependency */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_bufs; i++)
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
            .image_Memory_Barrier_ଗଣନା = nb_img_bar,
    });

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା buf_idx = FFMIN(i, (nb_bufs - 1));
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା img_idx = FFMIN(i, (nb_images - 1));
        FFVkBuffer *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].bufferRowLength;
        region[i].bufferRowLength /= desc->comp[i].step;
        region[i].imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);

        ଯଦି (upload)
            vk->CmdCopyBufferToImage(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        ଅନ୍ୟଥା
            vk->CmdCopyImageToBuffer(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].bufferRowLength = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ଯଦି (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        ଯଦି (!host_mapped)
            err = copy_buffer_data(hwfc, bufs[0], swf, region, planes, 0);
    }

end:
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_data_to(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ଅଚଳ AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ବାଛ (src->format) {
#ଯଦି CONFIG_CUDA
    ସ୍ଥିତି AV_PIX_FMT_CUDA:
#ifdef _WIN32
        ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ଅନ୍ୟଥା
        ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#endif
            ଫେରନ୍ତୁ vulkan_transfer_data_from_cuda(hwfc, dst, src);
        av_fallthrough;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଯଦି (src->hw_frames_ctx)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ vulkan_transfer_frame(hwfc, (AVFrame *)src, dst, 1);
    }
}

#ଯଦି CONFIG_CUDA
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_data_to_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = av_pix_fmt_ଗଣନା_planes(hwfc->sw_format);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_frames_ctx->data;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_ଅଙ୍କ_DATA_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)src->data[0];
    nb_images = ff_vk_ଗଣନା_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    err = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(cuda_dev->cuda_ctx));
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    err = vulkan_export_to_cuda(hwfc, dst->hw_frames_ctx, src);
    ଯଦି (err < 0) {
        CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
        ଫେରନ୍ତୁ err;
    }

    dst_int = dst_f->internal;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.ମୂଲ୍ୟ = dst_f->sem_ମୂଲ୍ୟ[i] + 0;
        s_s_par[i].params.fence.ମୂଲ୍ୟ = dst_f->sem_ମୂଲ୍ୟ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dstMemoryType = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->data[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .srcMemoryType = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = w * desc->comp[i].step;
        cpy.Height = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        ଯଦି (err < 0)
            ଯାଅ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    ଯଦି (err < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_images; i++)
        dst_f->sem_ମୂଲ୍ୟ[i]++;

    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    ଫେରନ୍ତୁ prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_buffer_unref(&dst->buf[0]);
    ଫେରନ୍ତୁ err;
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_transfer_data_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ଅଚଳ AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ବାଛ (dst->format) {
#ଯଦି CONFIG_CUDA
    ସ୍ଥିତି AV_PIX_FMT_CUDA:
#ifdef _WIN32
        ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#ଅନ୍ୟଥା
        ଯଦି ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#endif
            ଫେରନ୍ତୁ vulkan_transfer_data_to_cuda(hwfc, dst, src);
        av_fallthrough;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଯଦି (dst->hw_frames_ctx)
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ vulkan_transfer_frame(hwfc, dst, (AVFrame *)src, 0);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vulkan_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଫେରନ୍ତୁ vulkan_frames_init(dst_fc);
}

AVVkFrame *av_vk_frame_alloc(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;
    AVVkFrame *f = av_mallocz(ଆକାର(AVVkFrame));
    ଯଦି (!f)
        ଫେରନ୍ତୁ ଖାଲି;

    f->internal = av_mallocz(ଆକାର(*f->internal));
    ଯଦି (!f->internal) {
        av_free(f);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    err = pthread_mutex_init(&f->internal->update_mutex, ଖାଲି);
    ଯଦି (err != 0) {
        av_free(f->internal);
        av_free(f);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ f;
}

ଅଚଳ HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_size      = ଆକାର(VulkanDevicePriv),
    .frames_hwctx_size      = ଆକାର(VulkanFramesPriv),

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

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
