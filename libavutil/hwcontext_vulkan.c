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

#घोषणा VK_NO_PROTOTYPES
#घोषणा VK_ENABLE_BETA_EXTENSIONS

#अगर_घोषित _WIN32
#समावेश <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#समावेश <versionhelpers.h>
#समावेश "compat/w32dlfcn.h"
#अन्यथा
#समावेश <dlfcn.h>
#समावेश <unistd.h>
#पूर्ण_अगर

#समावेश "thread.h"

#समावेश "config.h"
#समावेश "pixdesc.h"
#समावेश "avstring.h"
#समावेश "imgutils.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_vulkan.h"
#समावेश "mem.h"
#समावेश "uuid.h"

#समावेश "vulkan.h"
#समावेश "vulkan_loader.h"

#अगर CONFIG_VAAPI
#समावेश "hwcontext_vaapi.h"
#पूर्ण_अगर

#अगर CONFIG_LIBDRM
#अगर CONFIG_VAAPI
#समावेश <va/va_drmcommon.h>
#पूर्ण_अगर
#अगर_घोषित __linux__
#समावेश <sys/sysmacros.h>
#पूर्ण_अगर
#समावेश <sys/stat.h>
#समावेश <xf86drm.h>
#समावेश <drm_fourcc.h>
#समावेश "hwcontext_drm.h"
#पूर्ण_अगर

#अगर HAVE_LINUX_DMA_BUF_H
#समावेश <sys/ioctl.h>
#समावेश <linux/dma-buf.h>
#पूर्ण_अगर

#अगर CONFIG_CUDA
#समावेश "hwcontext_cuda_internal.h"
#समावेश "cuda_check.h"
#घोषणा CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#पूर्ण_अगर

प्रकार काष्ठा VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR explicit_mem_layout;

#अगर_घोषित VK_EXT_shader_long_vector
    VkPhysicalDeviceShaderLongVectorFeaturesEXT long_vector;
#पूर्ण_अगर

#अगर_घोषित VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#पूर्ण_अगर

#अगर_घोषित VK_EXT_zero_initialize_device_memory
    VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT zero_initialize;
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#पूर्ण_अगर

#अगर_घोषित VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#पूर्ण_अगर
#अगर_घोषित VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#पूर्ण_अगर

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#अगर_घोषित VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#पूर्ण_अगर

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR cooperative_matrix;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#पूर्ण_अगर

#अगर_घोषित VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR internal_queue_sync;
#पूर्ण_अगर
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

प्रकार काष्ठा VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    व्योम *libvulkan;

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
    पूर्णांक use_linear_images;

    /* Option to allocate all image planes in a single allocation */
    पूर्णांक contiguous_planes;

    /* Disable multiplane images */
    पूर्णांक disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    पूर्णांक avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    पूर्णांक transfer_offset_align;

    /* Maximum queues */
    पूर्णांक limit_queues;
} VulkanDevicePriv;

प्रकार काष्ठा VulkanFramesPriv {
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
    पूर्णांक export_requires_dedicated;
} VulkanFramesPriv;

प्रकार काष्ठा AVVkFrameInternal {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#अगर CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternalMemory ext_mem[AV_अंक_तथ्य_POINTERS];
    CUmipmappedArray cu_mma[AV_अंक_तथ्य_POINTERS];
    CUarray cu_array[AV_अंक_तथ्य_POINTERS];
    CUexternalSemaphore cu_sem[AV_अंक_तथ्य_POINTERS];
#अगर_घोषित _WIN32
    HANDLE ext_mem_handle[AV_अंक_तथ्य_POINTERS];
    HANDLE ext_sem_handle[AV_अंक_तथ्य_POINTERS];
#पूर्ण_अगर
#पूर्ण_अगर
} AVVkFrameInternal;

/* Initialize all structs in VulkanDeviceFeatures */
अटल व्योम device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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

#अगर_घोषित VK_EXT_shader_long_vector
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_vector, FF_VK_EXT_LONG_VECTOR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_FEATURES_EXT);
#पूर्ण_अगर

#अगर_घोषित VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#पूर्ण_अगर

#अगर_घोषित VK_EXT_zero_initialize_device_memory
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_MEMORY_FEATURES_EXT);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#पूर्ण_अगर

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#अगर_घोषित VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#पूर्ण_अगर

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_matrix, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR);

#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->internal_queue_sync, FF_VK_EXT_INTERNAL_QUEUE_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#पूर्ण_अगर

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
अटल व्योम device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#घोषणा COPY_VAL(VAL)        \
    करो {                     \
        dst->VAL = src->VAL; \
    } जबतक (0)              \

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
    COPY_VAL(vulkan_1_1.storage_धकेलो_Constant16);
    COPY_VAL(vulkan_1_1.storageBuffer16BitAccess);
    COPY_VAL(vulkan_1_1.uniformAndStorageBuffer16BitAccess);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalarBlockLayout);
    COPY_VAL(vulkan_1_2.बफर_Device_Address);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_धकेलो_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storageBuffer8BitAccess);
    COPY_VAL(vulkan_1_2.uniformAndStorageBuffer8BitAccess);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_बफर_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkanMemoryModel);
    COPY_VAL(vulkan_1_2.vulkanMemoryModelDeviceScope);
    COPY_VAL(vulkan_1_2.vulkanMemoryModelAvailabilityVisibilityChains);
    COPY_VAL(vulkan_1_2.uniform_बफर_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_Uniform_बफर_Array_Non_Uniform_Indexing);
    COPY_VAL(vulkan_1_2.shaderSampledImageArrayNonUniformIndexing);
    COPY_VAL(vulkan_1_2.shader_Storage_बफर_Array_Non_Uniform_Indexing);
    COPY_VAL(vulkan_1_2.shaderStorageImageArrayNonUniformIndexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.computeFullSubgroups);
    COPY_VAL(vulkan_1_3.subgroup_आकार_Control);
    COPY_VAL(vulkan_1_3.shaderZeroInitializeWorkgroupMemory);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#अगर_घोषित VK_EXT_shader_long_vector
    COPY_VAL(long_vector.longVector);
#पूर्ण_अगर

#अगर_घोषित VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#पूर्ण_अगर

#अगर_घोषित VK_EXT_zero_initialize_device_memory
    COPY_VAL(zero_initialize.zeroInitializeDeviceMemory);
#पूर्ण_अगर

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#अगर_घोषित VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#पूर्ण_अगर

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_matrix.cooperativeMatrix);

    COPY_VAL(atomic_float.shader_बफर_Float32_Atomics);
    COPY_VAL(atomic_float.shader_बफर_Float32_Atomic_Add);

    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayoutScalarBlockLayout);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout8BitAccess);
    COPY_VAL(explicit_mem_layout.workgroupMemoryExplicitLayout16BitAccess);

#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#पूर्ण_अगर
#अगर_घोषित VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_internally_synchronized_queues
    COPY_VAL(internal_queue_sync.internallySynchronizedQueues);
#पूर्ण_अगर

    COPY_VAL(optical_flow.opticalFlow);

#अघोषित COPY_VAL
}

#घोषणा ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT)
#घोषणा ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT | VK_IMAGE_ASPECT_PLANE_2_BIT)

अटल स्थिर काष्ठा FFVkFormatEntry {
    VkFormat vkf;
    क्रमागत AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    पूर्णांक vk_planes;
    पूर्णांक nb_images;
    पूर्णांक nb_images_fallback;
    स्थिर VkFormat fallback[5];
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
अटल स्थिर पूर्णांक nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

स्थिर VkFormat *av_vkfmt_from_pixfmt(क्रमागत AVPixelFormat p)
{
    क्रम (पूर्णांक i = 0; i < nb_vk_formats_list; i++)
        अगर (vk_formats_list[i].pixfmt == p)
            वापस vk_formats_list[i].fallback;
    वापस शून्य;
}

अटल स्थिर काष्ठा FFVkFormatEntry *vk_find_format_entry(क्रमागत AVPixelFormat p)
{
    क्रम (पूर्णांक i = 0; i < nb_vk_formats_list; i++)
        अगर (vk_formats_list[i].pixfmt == p)
            वापस &vk_formats_list[i];
    वापस शून्य;
}

अटल पूर्णांक vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, क्रमागत AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_अंक_तथ्य_POINTERS], /* Output format list */
                              पूर्णांक *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              पूर्णांक disable_multiplane, पूर्णांक need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    स्थिर VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT;

    क्रम (पूर्णांक i = 0; i < nb_vk_formats_list; i++) {
        अगर (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_अग्र = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            पूर्णांक basics_primary = 0, basics_secondary = 0;
            पूर्णांक storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_LINEAR ?
                             fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);

            अगर (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_LINEAR ?
                                  fprops.linearTilingFeatures : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);
            } अन्यथा {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            अगर (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                अगर (fmts) {
                    अगर (vk_formats_list[i].nb_images > 1) {
                        क्रम (पूर्णांक j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } अन्यथा {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                अगर (nb_images)
                    *nb_images = 1;
                अगर (aspect)
                    *aspect = vk_formats_list[i].aspect;
                अगर (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_BIT : 0);
                वापस 0;
            } अन्यथा अगर (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                अगर (fmts) {
                    क्रम (पूर्णांक j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                अगर (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                अगर (aspect)
                    *aspect = vk_formats_list[i].aspect;
                अगर (supported_usage)
                    *supported_usage = ff_vk_map_feats_to_usage(feats_secondary);
                वापस 0;
            } अन्यथा {
                वापस AVERROR(ENOTSUP);
            }
        }
    }

    वापस AVERROR(EINVAL);
}

#अगर CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               स्थिर अक्षर *pName);
#पूर्ण_अगर

अटल पूर्णांक load_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#अगर CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#अन्यथा
    अटल स्थिर अक्षर *lib_names[] = {
#अगर defined(_WIN32)
        "vulkan-1.dll",
#या_अगर defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#अन्यथा
        "libvulkan.so.1",
        "libvulkan.so",
#पूर्ण_अगर
    };

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(lib_names); i++) {
        p->libvulkan = dlopen(lib_names[i], RTLD_NOW | RTLD_LOCAL);
        अगर (p->libvulkan)
            अवरोध;
    }

    अगर (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        वापस AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#पूर्ण_अगर /* CONFIG_VULKAN_STATIC */

    वापस 0;
}

प्रकार काष्ठा VulkanOptExtension {
    स्थिर अक्षर *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

अटल स्थिर VulkanOptExtension optional_instance_exts[] = {
#अगर_घोषित __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#पूर्ण_अगर
    { 0 },
};

अटल स्थिर VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_धकेलो_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_धकेलो_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME,               FF_VK_EXT_COOP_MATRIX            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#पूर्ण_अगर
#अगर_घोषित VK_EXT_shader_long_vector
    { VK_EXT_SHADER_LONG_VECTOR_EXTENSION_NAME,               FF_VK_EXT_LONG_VECTOR            },
#पूर्ण_अगर
#अगर_घोषित VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#पूर्ण_अगर
#अगर_घोषित VK_EXT_zero_initialize_device_memory
    { VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#पूर्ण_अगर
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#अगर_घोषित VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_INTERNAL_QUEUE_SYNC    },
#पूर्ण_अगर
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_MEMORY     },
    { VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_MEMORY },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_MEMORY   },
#अगर_घोषित _WIN32
    { VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_MEMORY  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#पूर्ण_अगर

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_QUEUE            },
    { VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_QUEUE     },
    { VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_QUEUE     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#अगर_घोषित VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#पूर्ण_अगर
#अगर_घोषित VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#पूर्ण_अगर
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

स्थिर अक्षर **av_vk_get_optional_instance_extensions(पूर्णांक *गिनती)
{
    स्थिर अक्षर **exts = av_malloc_array(माप(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    अगर (!exts)
        वापस शून्य;

    क्रम (पूर्णांक i = 0; i < (पूर्णांक)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *गिनती = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    वापस exts;
}

स्थिर अक्षर **av_vk_get_optional_device_extensions(पूर्णांक *गिनती)
{
    स्थिर अक्षर **exts = av_malloc_array(माप(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    अगर (!exts)
        वापस शून्य;

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *गिनती = FF_ARRAY_ELEMS(optional_device_exts);
    वापस exts;
}

अटल VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                    स्थिर Vk_Debug_Utils_Messenger_Callback_तथ्य_EXT *तथ्य,
                                    व्योम *priv)
{
    पूर्णांक l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    चयन (तथ्य->message_Id_संख्या) {
    हाल 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    हाल 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        वापस VK_FALSE;
    शेष:
        अवरोध;
    }

    चयन (severity) {
    हाल VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: l = AV_LOG_VERBOSE; अवरोध;
    हाल VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:    l = AV_LOG_INFO;    अवरोध;
    हाल VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: l = AV_LOG_WARNING; अवरोध;
    हाल VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:   l = AV_LOG_ERROR;   अवरोध;
    शेष:                                              l = AV_LOG_DEBUG;   अवरोध;
    }

    av_log(ctx, l, "%s\n", तथ्य->pMessage);
    क्रम (पूर्णांक i = 0; i < तथ्य->cmd_Buf_Label_गिनती; i++)
        av_log(ctx, l, "\t%i: %s\n", i, तथ्य->pCmdBufLabels[i].pLabelName);

    वापस VK_FALSE;
}

#घोषणा ADD_VAL_TO_LIST(list, गिनती, val)                                      \
    करो {                                                                       \
        list = av_realloc_array(list, ++गिनती, माप(*list));                 \
        अगर (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            जाओ fail;                                                         \
        }                                                                      \
        list[गिनती - 1] = av_strdup(val);                                      \
        अगर (!list[गिनती - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            जाओ fail;                                                         \
        }                                                                      \
    } जबतक(0)

#घोषणा RELEASE_PROPS(props, गिनती)                                            \
    अगर (props) {                                                               \
        क्रम (पूर्णांक i = 0; i < गिनती; i++)                                        \
            av_free((व्योम *)((props)[i]));                                     \
        av_free((व्योम *)props);                                                \
    }

अटल पूर्णांक vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_आकार max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.memory_Type_गिनती);
    क्रम (पूर्णांक i = 0; i < p->mprops.memory_Type_गिनती; i++) {
        स्थिर VkMemoryType type = p->mprops.memoryTypes[i];
        स्थिर VkMemoryHeap heap = p->mprops.memoryHeaps[type.heap_सूचकांक];
        अगर (!(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            जारी;
        max_vram = FFMAX(max_vram, heap.आकार);
        अगर (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            max_visible_vram = FFMAX(max_visible_vram, heap.आकार);
    }

    वापस max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

क्रमागत FFVulkanDebugMode {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

अटल पूर्णांक check_extensions(AVHWDeviceContext *ctx, पूर्णांक dev, AVDictionary *opts,
                            स्थिर अक्षर * स्थिर **dst, uint32_t *अंक,
                            क्रमागत FFVulkanDebugMode debug_mode)
{
    स्थिर अक्षर *tstr;
    स्थिर अक्षर **extension_names = शून्य;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णांक err = 0, found, extensions_found = 0;

    स्थिर अक्षर *mod;
    पूर्णांक optional_exts_अंक;
    uint32_t sup_ext_गिनती;
    अक्षर *user_exts_str = शून्य;
    AVDictionaryEntry *user_exts;
    VkExtensionProperties *sup_ext;
    स्थिर VulkanOptExtension *optional_exts;

    अगर (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_अंक = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", शून्य, 0);
        अगर (user_exts) {
            user_exts_str = av_strdup(user_exts->मूल्य);
            अगर (!user_exts_str) {
                err = AVERROR(ENOMEM);
                जाओ fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(शून्य, &sup_ext_गिनती, शून्य);
        sup_ext = av_malloc_array(sup_ext_गिनती, माप(VkExtensionProperties));
        अगर (!sup_ext)
            वापस AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(शून्य, &sup_ext_गिनती, sup_ext);
    } अन्यथा {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_अंक = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", शून्य, 0);
        अगर (user_exts) {
            user_exts_str = av_strdup(user_exts->मूल्य);
            अगर (!user_exts_str) {
                err = AVERROR(ENOMEM);
                जाओ fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, शून्य,
                                               &sup_ext_गिनती, शून्य);
        sup_ext = av_malloc_array(sup_ext_गिनती, माप(VkExtensionProperties));
        अगर (!sup_ext)
            वापस AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, शून्य,
                                               &sup_ext_गिनती, sup_ext);
    }

    क्रम (पूर्णांक i = 0; i < optional_exts_अंक; i++) {
        tstr = optional_exts[i].name;
        found = 0;

        /* Check if the device has ReBAR for host image copies */
        अगर (!म_भेद(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            जारी;

        अगर (dev &&
            ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_mode == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!म_भेद(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            जारी;
        }

        क्रम (पूर्णांक j = 0; j < sup_ext_गिनती; j++) {
            अगर (!म_भेद(tstr, sup_ext[j].extensionName)) {
                found = 1;
                अवरोध;
            }
        }
        अगर (!found)
            जारी;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
    }

    अगर (!dev &&
        ((debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_mode == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_mode == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        found = 0;
        क्रम (पूर्णांक j = 0; j < sup_ext_गिनती; j++) {
            अगर (!म_भेद(tstr, sup_ext[j].extensionName)) {
                found = 1;
                अवरोध;
            }
        }
        अगर (found) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            ADD_VAL_TO_LIST(extension_names, extensions_found, tstr);
        } अन्यथा {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            जाओ fail;
        }
    }

#अगर_घोषित VK_KHR_shader_relaxed_extended_instruction
    अगर ((debug_mode == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        found = 0;
        क्रम (पूर्णांक j = 0; j < sup_ext_गिनती; j++) {
            अगर (!म_भेद(tstr, sup_ext[j].extensionName)) {
                found = 1;
                अवरोध;
            }
        }
        अगर (!found) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            जाओ fail;
        }
    }
#पूर्ण_अगर

    अगर (user_exts_str) {
        अक्षर *save, *token = av_strtok(user_exts_str, "+", &save);
        जबतक (token) {
            found = 0;
            क्रम (पूर्णांक j = 0; j < sup_ext_गिनती; j++) {
                अगर (!म_भेद(token, sup_ext[j].extensionName)) {
                    found = 1;
                    अवरोध;
                }
            }
            अगर (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                ADD_VAL_TO_LIST(extension_names, extensions_found, token);
            } अन्यथा {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(शून्य, "+", &save);
        }
    }

    *dst = extension_names;
    *अंक = extensions_found;

    av_free(user_exts_str);
    av_free(sup_ext);
    वापस 0;

fail:
    RELEASE_PROPS(extension_names, extensions_found);
    av_free(user_exts_str);
    av_free(sup_ext);
    वापस err;
}

अटल पूर्णांक check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        स्थिर अक्षर * स्थिर **dst, uint32_t *अंक,
                        क्रमागत FFVulkanDebugMode *debug_mode)
{
    पूर्णांक err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    अटल स्थिर अक्षर layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    पूर्णांक layer_standard_validation_found = 0;

    uint32_t sup_layer_गिनती;
    VkLayerProperties *sup_layers;

    AVDictionaryEntry *user_layers = av_dict_get(opts, "layers", शून्य, 0);
    अक्षर *user_layers_str = शून्य;
    अक्षर *save, *token;

    स्थिर अक्षर **enabled_layers = शून्य;
    uint32_t enabled_layers_गिनती = 0;

    AVDictionaryEntry *debug_opt = av_dict_get(opts, "debug", शून्य, 0);
    क्रमागत FFVulkanDebugMode mode;

    *debug_mode = mode = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_गिनती, शून्य);
    sup_layers = av_malloc_array(sup_layer_गिनती, माप(VkLayerProperties));
    अगर (!sup_layers)
        वापस AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_गिनती, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    क्रम (पूर्णांक i = 0; i < sup_layer_गिनती; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    अगर (!debug_opt && !user_layers)
        जाओ end;

    /* Check for any properly supported validation layer */
    अगर (debug_opt) {
        अगर (!म_भेद(debug_opt->मूल्य, "printf")) {
            mode = FF_VULKAN_DEBUG_PRINTF;
        } अन्यथा अगर (!म_भेद(debug_opt->मूल्य, "validate")) {
            mode = FF_VULKAN_DEBUG_VALIDATE;
        } अन्यथा अगर (!म_भेद(debug_opt->मूल्य, "practices")) {
            mode = FF_VULKAN_DEBUG_PRACTICES;
        } अन्यथा {
            अक्षर *end_ptr = शून्य;
            पूर्णांक idx = म_से_दीर्घ(debug_opt->मूल्य, &end_ptr, 10);
            अगर (end_ptr == debug_opt->मूल्य || end_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->मूल्य);
                err = AVERROR(EINVAL);
                जाओ end;
            }
            mode = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    अगर ((mode == FF_VULKAN_DEBUG_VALIDATE) ||
        (mode == FF_VULKAN_DEBUG_PRINTF) ||
        (mode == FF_VULKAN_DEBUG_PRACTICES)) {
        क्रम (पूर्णांक i = 0; i < sup_layer_गिनती; i++) {
            अगर (!म_भेद(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_गिनती, layer_standard_validation);
                *debug_mode = mode;
                layer_standard_validation_found = 1;
                अवरोध;
            }
        }
        अगर (!layer_standard_validation_found) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            जाओ end;
        }
    }

    /* Process any custom layers enabled */
    अगर (user_layers) {
        पूर्णांक found;

        user_layers_str = av_strdup(user_layers->मूल्य);
        अगर (!user_layers_str) {
            err = AVERROR(ENOMEM);
            जाओ fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        जबतक (token) {
            found = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            अगर (!म_भेद(layer_standard_validation, token) && layer_standard_validation_found) {
                token = av_strtok(शून्य, "+", &save);
                अवरोध;
            }

            /* Try to find the layer in the list of supported layers */
            क्रम (पूर्णांक j = 0; j < sup_layer_गिनती; j++) {
                अगर (!म_भेद(token, sup_layers[j].layerName)) {
                    found = 1;
                    अवरोध;
                }
            }

            अगर (found) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                ADD_VAL_TO_LIST(enabled_layers, enabled_layers_गिनती, token);

                /* If debug was not set as an option, force it */
                अगर (!म_भेद(layer_standard_validation, token))
                    *debug_mode = FF_VULKAN_DEBUG_VALIDATE;
            } अन्यथा {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                जाओ end;
            }

            token = av_strtok(शून्य, "+", &save);
        }
    }

fail:
end:
    av_free(sup_layers);
    av_free(user_layers_str);

    अगर (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_गिनती);
    } अन्यथा {
        *dst = enabled_layers;
        *अंक = enabled_layers_गिनती;
    }

    वापस err;
}

/* Creates a VkInstance */
अटल पूर्णांक create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           क्रमागत FFVulkanDebugMode *debug_mode)
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
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

    अगर (!hwctx->get_proc_addr) {
        err = load_libvulkan(ctx);
        अगर (err < 0)
            वापस err;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    अगर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        वापस err;
    }

    err = check_layers(ctx, opts, &inst_props.ppEnabledLayerNames,
                       &inst_props.enabled_Layer_गिनती, debug_mode);
    अगर (err)
        जाओ fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.ppEnabledExtensionNames,
                           &inst_props.enabled_Extension_गिनती, *debug_mode);
    hwctx->enabled_inst_extensions = inst_props.ppEnabledExtensionNames;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_गिनती;
    अगर (err < 0)
        जाओ fail;

    /* Enable debug features if needed */
    अगर (*debug_mode == FF_VULKAN_DEBUG_VALIDATE) {
        अटल स्थिर VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_गिनती = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_अग्र = &validation_features;
    } अन्यथा अगर (*debug_mode == FF_VULKAN_DEBUG_PRINTF) {
        अटल स्थिर VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_गिनती = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_अग्र = &validation_features;
    } अन्यथा अगर (*debug_mode == FF_VULKAN_DEBUG_PRACTICES) {
        अटल स्थिर VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_गिनती = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_अग्र = &validation_features;
    }

#अगर_घोषित __APPLE__
    क्रम (पूर्णांक i = 0; i < inst_props.enabled_Extension_गिनती; i++) {
        अगर (!म_भेद(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.ppEnabledExtensionNames[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            अवरोध;
        }
    }
#पूर्ण_अगर

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        जाओ fail;
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    अगर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        जाओ fail;
    }

    /* Setup debugging callback if needed */
    अगर ((*debug_mode == FF_VULKAN_DEBUG_VALIDATE) ||
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
            .p_User_तथ्य = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.ppEnabledLayerNames, inst_props.enabled_Layer_गिनती);
    वापस err;
}

प्रकार काष्ठा VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_आकार]; /* Will use this first unless !has_uuid */
    पूर्णांक has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    स्थिर अक्षर *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    पूर्णांक सूचकांक; /* Finally fall back to index */
} VulkanDeviceSelection;

अटल स्थिर अक्षर *vk_dev_type(क्रमागत VkPhysicalDeviceType type)
{
    चयन (type) {
    हाल VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: वापस "integrated";
    हाल VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   वापस "discrete";
    हाल VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    वापस "virtual";
    हाल VK_PHYSICAL_DEVICE_TYPE_CPU:            वापस "software";
    शेष:                                     वापस "unknown";
    }
}

/* Finds a device */
अटल पूर्णांक find_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    पूर्णांक err = 0, choice = -1;
    uint32_t अंक;
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = शून्य;
    VkPhysicalDeviceIDProperties *idp = शून्य;
    VkPhysicalDeviceProperties2 *prop = शून्य;
    VkPhysicalDeviceDriverProperties *driver_prop = शून्य;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = शून्य;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &अंक, शून्य);
    अगर (ret != VK_SUCCESS || !अंक) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        वापस AVERROR(ENODEV);
    }

    devices = av_malloc_array(अंक, माप(VkPhysicalDevice));
    अगर (!devices)
        वापस AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &अंक, devices);
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        जाओ end;
    }

    prop = av_calloc(अंक, माप(*prop));
    अगर (!prop) {
        err = AVERROR(ENOMEM);
        जाओ end;
    }

    idp = av_calloc(अंक, माप(*idp));
    अगर (!idp) {
        err = AVERROR(ENOMEM);
        जाओ end;
    }

    driver_prop = av_calloc(अंक, माप(*driver_prop));
    अगर (!driver_prop) {
        err = AVERROR(ENOMEM);
        जाओ end;
    }

    अगर (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(अंक, माप(*drm_prop));
        अगर (!drm_prop) {
            err = AVERROR(ENOMEM);
            जाओ end;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    क्रम (पूर्णांक i = 0; i < अंक; i++) {
        अगर (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].p_अग्र = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].p_अग्र = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].p_अग्र = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    अगर (select->has_uuid) {
        क्रम (पूर्णांक i = 0; i < अंक; i++) {
            अगर (!स_भेद(idp[i].deviceUUID, select->uuid, VK_UUID_आकार)) {
                choice = i;
                जाओ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        जाओ end;
    } अन्यथा अगर ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        क्रम (पूर्णांक i = 0; i < अंक; i++) {
            अगर ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                जाओ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        जाओ end;
    } अन्यथा अगर (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        क्रम (पूर्णांक i = 0; i < अंक; i++) {
            अगर (म_माला(prop[i].properties.deviceName, select->name)) {
                choice = i;
                जाओ end;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        जाओ end;
    } अन्यथा अगर (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        क्रम (पूर्णांक i = 0; i < अंक; i++) {
            अगर (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                जाओ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        जाओ end;
    } अन्यथा अगर (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        क्रम (पूर्णांक i = 0; i < अंक; i++) {
            अगर (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                जाओ end;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        जाओ end;
    } अन्यथा {
        अगर (select->सूचकांक < अंक) {
            choice = select->सूचकांक;
            जाओ end;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->सूचकांक);
        err = AVERROR(ENODEV);
        जाओ end;
    }

end:
    अगर (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_अग्र = शून्य;
        p->dprops = driver_prop[choice];
        p->dprops.p_अग्र = शून्य;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    वापस err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
अटल अंतरभूत पूर्णांक pick_queue_family(VkQueueFamilyProperties2 *qf, uint32_t अंक_qf,
                                    VkQueueFlagBits flags)
{
    पूर्णांक सूचकांक = -1;
    uint32_t min_score = UINT32_MAX;

    क्रम (पूर्णांक i = 0; i < अंक_qf; i++) {
        VkQueueFlagBits qflags = qf[i].queueFamilyProperties.queueFlags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        अगर ((flags & VK_QUEUE_TRANSFER_BIT) &&
            (qflags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            qflags |= VK_QUEUE_TRANSFER_BIT;

        अगर (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].queueFamilyProperties.timestampValidBits;
            अगर (score < min_score) {
                सूचकांक = i;
                min_score = score;
            }
        }
    }

    अगर (सूचकांक > -1)
        qf[सूचकांक].queueFamilyProperties.timestampValidBits++;

    वापस सूचकांक;
}

अटल अंतरभूत पूर्णांक pick_video_queue_family(VkQueueFamilyProperties2 *qf,
                                          VkQueueFamilyVideoPropertiesKHR *qf_vid, uint32_t अंक_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    पूर्णांक सूचकांक = -1;
    uint32_t min_score = UINT32_MAX;

    क्रम (पूर्णांक i = 0; i < अंक_qf; i++) {
        स्थिर VkQueueFlags qflags = qf[i].queueFamilyProperties.queueFlags;
        स्थिर VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        अगर (!(qflags & (VK_QUEUE_VIDEO_ENCODE_BIT_KHR | VK_QUEUE_VIDEO_DECODE_BIT_KHR)))
            जारी;

        अगर (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].queueFamilyProperties.timestampValidBits;
            अगर (score < min_score) {
                सूचकांक = i;
                min_score = score;
            }
        }
    }

    अगर (सूचकांक > -1)
        qf[सूचकांक].queueFamilyProperties.timestampValidBits++;

    वापस सूचकांक;
}

अटल पूर्णांक setup_queue_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t अंक;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    VkQueueFamilyProperties2 *qf = शून्य;
    VkQueueFamilyVideoPropertiesKHR *qf_vid = शून्य;

    /* First get the number of queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &अंक, शून्य);
    अगर (!अंक) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        वापस AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(अंक, माप(VkQueueFamilyProperties2));
    अगर (!qf)
        वापस AVERROR(ENOMEM);

    qf_vid = av_malloc_array(अंक, माप(VkQueueFamilyVideoPropertiesKHR));
    अगर (!qf_vid)
        वापस AVERROR(ENOMEM);

    क्रम (uint32_t i = 0; i < अंक; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .p_अग्र = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : शून्य,
        };
    }

    /* Finally retrieve the queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &अंक, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    क्रम (पूर्णांक i = 0; i < अंक; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_GRAPHICS_BIT) ? " graphics" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_COMPUTE_BIT) ? " compute" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_TRANSFER_BIT) ? " transfer" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) ? " encode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_DECODE_BIT_KHR) ? " decode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_SPARSE_BINDING_BIT) ? " sparse" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_OPTICAL_FLOW_BIT_NV) ? " optical_flow" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_PROTECTED_BIT) ? " protected" : "",
               qf[i].queueFamilyProperties.queue_गिनती);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].queueFamilyProperties.timestampValidBits = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->queue_flags = 0;
#अगर_घोषित VK_KHR_internally_synchronized_queues
    अगर (p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)
        hwctx->queue_flags |= VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR;
#पूर्ण_अगर

    /* Pick each queue family to use. */
#घोषणा PICK_QF(type, vid_op)                                            \
    करो {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        अगर (vid_op)                                                      \
            idx = pick_video_queue_family(qf, qf_vid, अंक, vid_op);      \
        अन्यथा                                                             \
            idx = pick_queue_family(qf, अंक, type);                      \
                                                                         \
        अगर (idx == -1)                                                   \
            जारी;                                                    \
                                                                         \
        क्रम (i = 0; i < hwctx->nb_qf; i++) {                             \
            अगर (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                अवरोध;                                                   \
            }                                                            \
        }                                                                \
        अगर (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].अंक = qf[idx].queueFamilyProperties.queue_गिनती; \
            अगर (p->limit_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                पूर्णांक max = p->limit_queues;                               \
                अगर (type == VK_QUEUE_GRAPHICS_BIT)                       \
                    hwctx->qf[i].अंक = FFMIN(hwctx->qf[i].अंक,           \
                                             max ? max : 1);             \
                अन्यथा अगर (max)                                            \
                    hwctx->qf[i].अंक = FFMIN(hwctx->qf[i].अंक, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } जबतक (0)

    PICK_QF(VK_QUEUE_GRAPHICS_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_COMPUTE_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_TRANSFER_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR);

#अगर_घोषित VK_KHR_video_decode_vp9
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR);
#पूर्ण_अगर

#अगर_घोषित VK_KHR_video_encode_av1
    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR);
#पूर्ण_अगर
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR);

    अगर (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_QUEUE_OPTICAL_FLOW_BIT_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#अघोषित PICK_QF

    cd->pQueueCreateInfos = av_malloc_array(hwctx->nb_qf,
                                            माप(VkDeviceQueueCreateInfo));
    अगर (!cd->pQueueCreateInfos)
        वापस AVERROR(ENOMEM);

    क्रम (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        पूर्णांक dup = 0;
        भग्न *weights = शून्य;
        VkDeviceQueueCreateInfo *pc;
        क्रम (uint32_t j = 0; j < cd->queue_Create_Info_गिनती; j++) {
            अगर (hwctx->qf[i].idx == cd->pQueueCreateInfos[j].queue_Family_सूचकांक) {
                dup = 1;
                अवरोध;
            }
        }
        अगर (dup)
            जारी;

        weights = av_malloc_array(hwctx->qf[i].अंक, माप(भग्न));
        अगर (!weights) {
            क्रम (uint32_t j = 0; j < cd->queue_Create_Info_गिनती; j++)
                av_free((व्योम *)cd->pQueueCreateInfos[i].pQueuePriorities);
            av_free((व्योम *)cd->pQueueCreateInfos);
            वापस AVERROR(ENOMEM);
        }

        क्रम (uint32_t j = 0; j < hwctx->qf[i].अंक; j++)
            weights[j] = 1.0;

        pc = (VkDeviceQueueCreateInfo *)cd->pQueueCreateInfos;
        pc[cd->queue_Create_Info_गिनती++] = (VkDeviceQueueCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .flags = hwctx->queue_flags,
            .queue_Family_सूचकांक = hwctx->qf[i].idx,
            .queue_गिनती = hwctx->qf[i].अंक,
            .pQueuePriorities = weights,
        };
    }

    वापस 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
अटल व्योम vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    अगर (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    अगर (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    अगर (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    अगर (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

अटल व्योम vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    अगर (p->qf_mutex) {
        क्रम (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

अटल पूर्णांक vulkan_device_create_internal(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         पूर्णांक disable_multiplane,
                                         AVDictionary *opts, पूर्णांक flags)
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
    AVDictionaryEntry *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    क्रमागत FFVulkanDebugMode debug_mode = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    अगर ((err = create_instance(ctx, opts, &debug_mode)))
        जाओ end;

    /* Find a physical device (if not given one) */
    अगर ((err = find_device(ctx, dev_select)))
        जाओ end;

    /* Get supported memory types */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    अगर ((err = check_extensions(ctx, 1, opts, &dev_info.ppEnabledExtensionNames,
                                &dev_info.enabled_Extension_गिनती, debug_mode))) {
        क्रम (पूर्णांक i = 0; i < dev_info.queue_Create_Info_गिनती; i++)
            av_free((व्योम *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
        av_free((व्योम *)dev_info.pQueueCreateInfos);
        जाओ end;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.p_अग्र = p->feats.device.p_अग्र;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", शून्य, 0);
    अगर (opt_d)
        p->limit_queues = म_से_दीर्घ(opt_d->मूल्य, शून्य, 10);

    /* Setup enabled queue families */
    अगर ((err = setup_queue_families(ctx, &dev_info)))
        जाओ end;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    क्रम (पूर्णांक i = 0; i < dev_info.queue_Create_Info_गिनती; i++)
        av_free((व्योम *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
    av_free((व्योम *)dev_info.pQueueCreateInfos);

    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        क्रम (पूर्णांक i = 0; i < dev_info.enabled_Extension_गिनती; i++)
            av_free((व्योम *)dev_info.ppEnabledExtensionNames[i]);
        av_free((व्योम *)dev_info.ppEnabledExtensionNames);
        err = AVERROR_EXTERNAL;
        जाओ end;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", शून्य, 0);
    अगर (opt_d)
        p->use_linear_images = म_से_दीर्घ(opt_d->मूल्य, शून्य, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    अगर (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", शून्य, 0);
        अगर (opt_d)
            p->disable_multiplane = म_से_दीर्घ(opt_d->मूल्य, शून्य, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", शून्य, 0);
    अगर (opt_d)
        p->avoid_host_import = म_से_दीर्घ(opt_d->मूल्य, शून्य, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.ppEnabledExtensionNames;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_गिनती;

    /* The extension lists need to be freed */
    ctx->मुक्त = vulkan_device_free;

end:
    वापस err;
}

अटल व्योम lock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t सूचकांक)
{
    VulkanDevicePriv *p = ctx->hwctx;
    अगर (p->qf_mutex)
        pthread_mutex_lock(&p->qf_mutex[queue_family][सूचकांक]);
}

अटल व्योम unlock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t सूचकांक)
{
    VulkanDevicePriv *p = ctx->hwctx;
    अगर (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[queue_family][सूचकांक]);
}

अटल पूर्णांक vulkan_device_init(AVHWDeviceContext *ctx)
{
    पूर्णांक err = 0;
    uint32_t qf_अंक;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkQueueFamilyProperties2 *qf;
    VkQueueFamilyVideoPropertiesKHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    क्रम (पूर्णांक i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        क्रम (पूर्णांक j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            अगर (!म_भेद(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                अवरोध;
            }
        }
    }

    err = ff_vk_load_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    अगर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        वापस err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_अग्र = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    p->hprops.p_अग्र = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_बफर_Copy_Row_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.minMemoryMapAlignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_आकार);
    अगर (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.minImportedHostPointerAlignment);

    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &qf_अंक, शून्य);
    अगर (!qf_अंक) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        वापस AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#अगर_घोषित _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT;
#अन्यथा
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;
#पूर्ण_अगर
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_अंक, माप(VkQueueFamilyProperties2));
    अगर (!qf)
        वापस AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_अंक, माप(VkQueueFamilyVideoPropertiesKHR));
    अगर (!qf_vid) {
        av_free(qf);
        वापस AVERROR(ENOMEM);
    }

    क्रम (uint32_t i = 0; i < qf_अंक; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .p_अग्र = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : शून्य,
        };
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &qf_अंक, qf);

    p->nb_tot_qfs = qf_अंक;

    अगर (!(p->vkctx.extensions & FF_VK_EXT_INTERNAL_QUEUE_SYNC)) {
        p->qf_mutex = av_calloc(qf_अंक, माप(*p->qf_mutex));
        अगर (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            जाओ end;
        }

        क्रम (uint32_t i = 0; i < qf_अंक; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].queueFamilyProperties.queue_गिनती,
                                       माप(**p->qf_mutex));
            अगर (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                जाओ end;
            }
            क्रम (uint32_t j = 0; j < qf[i].queueFamilyProperties.queue_गिनती; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], शून्य);
                अगर (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    जाओ end;
                }
            }
        }
    }

    क्रम (पूर्णांक i = 0; i < hwctx->nb_qf; i++) {
        अगर (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                  VK_QUEUE_VIDEO_ENCODE_BIT_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    क्रम (पूर्णांक i = 0; i < hwctx->nb_qf; i++) {
        पूर्णांक seen = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        क्रम (पूर्णांक j = (i - 1); j >= 0; j--) {
            अगर (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                seen = 1;
                अवरोध;
            }
        }
        अगर (!seen)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#अगर FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    अगर (!hwctx->lock_queue)
        hwctx->lock_queue = lock_queue;
    अगर (!hwctx->unlock_queue)
        hwctx->unlock_queue = unlock_queue;
FF_ENABLE_DEPRECATION_WARNINGS
#पूर्ण_अगर

    /* Re-query device capabilities, in case the device was created externally */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_load_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_COMPUTE_BIT, 0);
    p->transfer_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_TRANSFER_BIT, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_offset_align = 1;
    अगर (p->transfer_qf) {
        VkQueueFlags flags = p->vkctx.qf_props[p->transfer_qf->idx].queueFamilyProperties.queueFlags;
        अगर (!(flags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            p->transfer_offset_align = 4;
    }
#अगर_घोषित VK_KHR_maintenance11
    अगर (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_offset_align = 1;
#पूर्ण_अगर

    /* Re-query device capabilities, in case the device was created externally */
    vk->GetPhysicalDeviceMemoryProperties(hwctx->phys_dev, &p->mprops);

end:
    av_free(qf_vid);
    av_free(qf);
    वापस err;
}

अटल पूर्णांक vulkan_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                                AVDictionary *opts, पूर्णांक flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    अगर (device && device[0]) {
        अक्षर *end = शून्य;

        अगर (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } अन्यथा {
            dev_select.सूचकांक = म_से_दीर्घ(device, &end, 10);
            अगर (end == device || *end) {
                dev_select.सूचकांक = 0;
                dev_select.name  = device;
            }
        }
    }

    वापस vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
}

अटल पूर्णांक vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, पूर्णांक flags)
{
    av_unused VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    चयन(src_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#अगर VA_CHECK_VERSION(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#पूर्ण_अगर
        स्थिर अक्षर *vendor;

#अगर VA_CHECK_VERSION(1, 15, 0)
        vas = vaGetDisplayAttributes(dpy, &attr, 1);
        अगर (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.मूल्य & 0xFFFF);
#पूर्ण_अगर

        अगर (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            अगर (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                वापस AVERROR_EXTERNAL;
            }

            अगर (म_माला(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        वापस vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#पूर्ण_अगर
#अगर CONFIG_LIBDRM
    हाल AV_HWDEVICE_TYPE_DRM: {
        पूर्णांक err;
        काष्ठा stat drm_गाँठ_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = ख_स्थिति(src_hwctx->fd, &drm_गाँठ_info);
        अगर (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(त्रुटि_सं)));
            वापस AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_गाँठ_info.st_dev);
        dev_select.drm_minor = minor(drm_गाँठ_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        अगर (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(त्रुटि_सं)));
            वापस AVERROR_EXTERNAL;
        }

        अगर (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        वापस vulkan_device_create_internal(ctx, &dev_select, 0, opts, flags);
    }
#पूर्ण_अगर
#अगर CONFIG_CUDA
    हाल AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADeviceContextInternal *cu_internal = src_hwctx->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        पूर्णांक ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_internal->cuda_device));
        अगर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            वापस AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        वापस vulkan_device_create_internal(ctx, &dev_select, 1, opts, flags);
    }
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }
}

अटल पूर्णांक vulkan_frames_get_constraints(AVHWDeviceContext *ctx,
                                         स्थिर व्योम *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    पूर्णांक गिनती = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    क्रम (क्रमागत AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        गिनती += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    शून्य, शून्य, शून्य, शून्य, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(गिनती + 1 + CONFIG_CUDA,
                                                    माप(क्रमागत AVPixelFormat));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    गिनती = 0;
    क्रम (क्रमागत AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        अगर (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_linear_images ? VK_IMAGE_TILING_LINEAR :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               शून्य, शून्य, शून्य, शून्य, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[गिनती++] = vk_formats_list[i].pixfmt;
        }
    }

#अगर CONFIG_CUDA
    constraints->valid_sw_formats[गिनती++] = AV_PIX_FMT_CUDA;
#पूर्ण_अगर

    constraints->valid_sw_formats[गिनती++] = AV_PIX_FMT_NONE;

    constraints->min_width  = 1;
    constraints->min_height = 1;
    constraints->max_width  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_height = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, माप(क्रमागत AVPixelFormat));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल पूर्णांक alloc_mem(AVHWDeviceContext *ctx, VkMemoryRequirements *req,
                     VkMemoryPropertyFlagBits req_flags, स्थिर व्योम *alloc_extension,
                     VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem)
{
    Vk_परिणाम ret;
    पूर्णांक सूचकांक = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkMemoryAllocateInfo alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .p_अग्र          = alloc_extension,
        .allocation_आकार = req->आकार,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    क्रम (पूर्णांक i = 0; i < p->mprops.memory_Type_गिनती; i++) {
        स्थिर VkMemoryType *type = &p->mprops.memoryTypes[i];

        /* The memory type must be supported by the requirements (bitfield) */
        अगर (!(req->memoryTypeBits & (1 << i)))
            जारी;

        /* The memory type flags must include our properties */
        अगर ((type->propertyFlags & req_flags) != req_flags)
            जारी;

        /* The memory type must be large enough */
        अगर (req->आकार > p->mprops.memoryHeaps[type->heap_सूचकांक].आकार)
            जारी;

        /* Found a suitable memory type */
        सूचकांक = i;
        अवरोध;
    }

    अगर (सूचकांक < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        वापस AVERROR(EINVAL);
    }

    alloc_info.memory_Type_सूचकांक = सूचकांक;

    ret = vk->AllocateMemory(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.memoryTypes[सूचकांक].propertyFlags;

    वापस 0;
}

अटल व्योम vulkan_free_internal(VulkanDevicePriv *p, AVVkFrame *f)
{
    av_unused AVVkFrameInternal *internal = f->internal;

    // Make this function safe to call repeatedly
    अगर (!internal)
        वापस;

#अगर CONFIG_CUDA
    अगर (internal->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)internal->cuda_fc_ref->तथ्य;
        पूर्णांक planes = av_pix_fmt_गिनती_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
        CudaFunctions *cu = cu_internal->cuda_dl;

        क्रम (पूर्णांक i = 0; i < planes; i++) {
            अगर (internal->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(internal->cu_sem[i]));
            अगर (internal->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(internal->cu_mma[i]));
            अगर (internal->ext_mem[i])
                CHECK_CU(cu->cuDestroyExternalMemory(internal->ext_mem[i]));
#अगर_घोषित _WIN32
            अगर (internal->ext_sem_handle[i])
                CloseHandle(internal->ext_sem_handle[i]);
            अगर (internal->ext_mem_handle[i])
                CloseHandle(internal->ext_mem_handle[i]);
#पूर्ण_अगर
        }

        av_बफर_unref(&internal->cuda_fc_ref);
    }
#पूर्ण_अगर

    अगर (internal->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, internal->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&internal->update_mutex);
    av_freep(&f->internal);
}

अटल व्योम vulkan_frame_free(AVHWFramesContext *hwfc, AVVkFrame *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णांक nb_images = ff_vk_गिनती_images(f);
    पूर्णांक nb_sems = 0;

    जबतक (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    अगर (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_मूल्यावली        = f->sem_मूल्य,
            .semaphore_गिनती = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_internal(p, f);

    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->FreeMemory(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

अटल व्योम vulkan_frame_free_cb(व्योम *opaque, uint8_t *तथ्य)
{
    vulkan_frame_free(opaque, (AVVkFrame*)तथ्य);
}

अटल पूर्णांक alloc_bind_mem(AVHWFramesContext *hwfc, AVVkFrame *f,
                          व्योम *alloc_pnext, माप_प्रकार alloc_pnext_stride)
{
    पूर्णांक img_cnt = 0, err;
    Vk_परिणाम ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkBindImageMemoryInfo bind_info[AV_अंक_तथ्य_POINTERS] = { { 0 } };

    जबतक (f->img[img_cnt]) {
        पूर्णांक use_ded_mem;
        VkImageMemoryRequirementsInfo2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        VkMemoryDedicatedAllocateInfo ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .p_अग्र = (व्योम *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        VkMemoryDedicatedRequirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
        };
        VkMemoryRequirements2 req = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2,
            .p_अग्र = &ded_req,
        };

        vk->GetImageMemoryRequirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefersDedicatedAllocation, ded_req.requiresDedicatedAllocation);

        अगर (f->tiling == VK_IMAGE_TILING_LINEAR)
            req.memoryRequirements.आकार = FFALIGN(req.memoryRequirements.आकार,
                                                  p->props.properties.limits.minMemoryMapAlignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefersDedicatedAllocation |
                      ded_req.requiresDedicatedAllocation;
        अगर (((VulkanFramesPriv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        अगर (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        अगर ((err = alloc_mem(ctx, &req.memoryRequirements,
                             f->tiling == VK_IMAGE_TILING_LINEAR ?
                             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT :
                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                             use_ded_mem ? &ded_alloc : (व्योम *)ded_alloc.p_अग्र,
                             &f->flags, &f->mem[img_cnt])))
            वापस err;

        f->आकार[img_cnt] = req.memoryRequirements.आकार;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].memory = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

क्रमागत PrepMode {
    PREP_MODE_GENERAL,
    PREP_MODE_WRITE,
    PREP_MODE_EXTERNAL_EXPORT,
    PREP_MODE_EXTERNAL_IMPORT,
    PREP_MODE_DECODING_DST,
    PREP_MODE_DECODING_DPB,
    PREP_MODE_ENCODING_DPB,
};

अटल व्योम switch_new_props(क्रमागत PrepMode pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    चयन (pmode) {
    हाल PREP_MODE_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        अवरोध;
    हाल PREP_MODE_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        अवरोध;
    }
}

अटल पूर्णांक switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, क्रमागत PrepMode pmode)
{
    पूर्णांक err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkImageMemoryBarrier2 img_bar[AV_अंक_तथ्य_POINTERS];
    पूर्णांक nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    अगर (pmode == PREP_MODE_EXTERNAL_EXPORT) {
        dst_qf     = VK_QUEUE_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .तथ्य = (uint8_t *)hwfc,
    };
    AVFrame tmp_frame = {
        .तथ्य[0] = (uint8_t *)frame,
        .hw_frames_ctx = &tmp_ref,
    };

    Vk_Command_बफर cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_start(&p->vkctx, exec);
    अगर (err < 0)
        वापस err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, &tmp_frame,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
    अगर (err < 0)
        वापस err;

    ff_vk_frame_barrier(&p->vkctx, exec, &tmp_frame, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .pImageMemoryBarriers = img_bar,
            .image_Memory_Barrier_गिनती = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    अगर (err < 0)
        वापस err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    वापस 0;
}

अटल पूर्णांक switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVkFrame *frame, क्रमागत PrepMode pmode)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_अंक_तथ्य_POINTERS];
    पूर्णांक nb_images = ff_vk_गिनती_images(frame);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    पूर्णांक i;
    क्रम (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_गिनती; i++) {
        अगर (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            अवरोध;
    }
    अगर (i == p->vkctx.host_image_props.copy_Dst_Layout_गिनती)
        वापस AVERROR(ENOTSUP);

    क्रम (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = frame->img[i],
            .oldLayout = frame->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.layer_गिनती = 1,
            .subresourceRange.level_गिनती = 1,
        };
        frame->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    अगर (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक prepare_frame(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, क्रमागत PrepMode pmode)
{
    पूर्णांक err = 0;
    AVVulkanFramesContext *hwfc_vk = hwfc->hwctx;
    अगर (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT &&
        (pmode != PREP_MODE_EXTERNAL_EXPORT) &&
        (pmode != PREP_MODE_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, frame, pmode);
        अगर (err != AVERROR(ENOTSUP))
            वापस err;
    }

    वापस switch_layout(hwfc, ectx, frame, pmode);
}

अटल अंतरभूत व्योम get_plane_wh(uint32_t *w, uint32_t *h, क्रमागत AVPixelFormat format,
                                पूर्णांक frame_w, पूर्णांक frame_h, पूर्णांक plane)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    अगर (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = frame_w;
        *h = frame_h;
        वापस;
    }

    *w = AV_CEIL_RSHIFT(frame_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(frame_h, desc->log2_chroma_h);
}

अटल पूर्णांक create_frame(AVHWFramesContext *hwfc, AVVkFrame **frame,
                        VkImageTiling tiling, VkImageUsageFlagBits usage,
                        VkImageCreateFlags flags, पूर्णांक nb_layers,
                        व्योम *create_pnext)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    AVVulkanFramesContext *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVkFrame *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_मूल्य  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_अग्र = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#अगर_घोषित _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
#अन्यथा
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
#पूर्ण_अगर
    };

    /* Check if exporting is supported before chaining any structs */
    अगर (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT) {
        अगर (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_frame_alloc();
    अगर (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        वापस AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    क्रम (पूर्णांक i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.depth          = 1,
            .mipLevels             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_गिनती_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गिनती = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, hwfc->width, hwfc->height, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            जाओ fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }

        f->queue_family[i] = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_मूल्य[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *frame = f;
    वापस 0;

fail:
    vulkan_frame_free(hwfc, f);
    वापस err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
अटल व्योम try_export_flags(AVHWFramesContext *hwfc,
                             VkExternalMemoryHandleTypeFlags *comp_handle_types,
                             VkExternalMemoryHandleTypeFlags *iexp,
                             VkExternalMemoryHandleTypeFlagBits exp)
{
    Vk_परिणाम ret;
    AVVulkanFramesContext *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    स्थिर VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    पूर्णांक has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    पूर्णांक nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_अग्र = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_अग्र = शून्य,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_सूचकांक_गिनती = p->nb_img_qfs,
        .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                     VK_SHARING_MODE_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = exp,
        .p_अग्र = has_mods ? &phy_dev_mod_info : शून्य,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_अग्र  = !exp ? शून्य : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_BIT),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_गिनती : 1;
    क्रम (पूर्णांक i = 0; i < nb_mods; i++) {
        अगर (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        अगर (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (अचिन्हित दीर्घ दीर्घ)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        अगर (ret == VK_SUCCESS) {
            *iexp |= exp;
            *comp_handle_types |= eprops.externalMemoryProperties.compatibleHandleTypes;
            अगर (exp == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT) {
                VulkanFramesPriv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.externalMemoryProperties.externalMemoryFeatures &
                                                  VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
अटल व्योम get_export_handle_types(AVHWFramesContext *hwfc,
                                    VkExternalMemoryHandleTypeFlags *comp_handle_types,
                                    VkExternalMemoryHandleTypeFlags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_unused AVVulkanFramesContext *hwctx = &((VulkanFramesPriv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#अगर_घोषित _WIN32
    अगर (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT
                             : VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT);
#अन्यथा
    अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);

    अगर (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_MEMORY &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT);
#पूर्ण_अगर
}

अटल AVBufferRef *vulkan_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    पूर्णांक err;
    AVVkFrame *f;
    AVBufferRef *avbuf = शून्य;
    AVHWFramesContext *hwfc = opaque;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VkExternalMemoryHandleTypeFlags e;
    VkExportMemoryAllocateInfo eminfo[AV_अंक_तथ्य_POINTERS];

    VkExternalMemoryImageCreateInfo eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
        .p_अग्र       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    क्रम (पूर्णांक i = 0; i < av_pix_fmt_गिनती_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
        eminfo[i].p_अग्र       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    अगर (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        वापस शून्य;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, माप(*eminfo));
    अगर (err)
        जाओ fail;

    अगर ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR))
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DPB);
    अन्यथा अगर (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_DECODING_DST);
    अन्यथा अगर (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_ENCODING_DPB);
    अन्यथा अगर (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_WRITE);
    अन्यथा
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_GENERAL);
    अगर (err)
        जाओ fail;

    avbuf = av_बफर_create((uint8_t *)f, माप(AVVkFrame),
                             vulkan_frame_free_cb, hwfc, 0);
    अगर (!avbuf)
        जाओ fail;

    वापस avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_frame_free(hwfc, f);
    वापस शून्य;
}

अटल व्योम lock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_lock(&vkf->internal->update_mutex);
}

अटल व्योम unlock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_unlock(&vkf->internal->update_mutex);
}

अटल व्योम vulkan_frames_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;

    अगर (fp->modifier_info) {
        अगर (fp->modifier_info->pDrmFormatModifiers)
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
अटल पूर्णांक vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_परिणाम ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    स्थिर काष्ठा FFVkFormatEntry *fmt = vk_find_format_entry(hwfc->sw_format);
    अगर (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        वापस 0;
    }

    स्थिर VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    पूर्णांक has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_गिनती;
    पूर्णांक nb_mods = has_mods ? mod_list->drm_Format_Modifier_गिनती : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    अगर (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        वापस 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_सूचकांक_गिनती = p->nb_img_qfs,
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

    अगर (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    स्थिर VkVideoProfileListInfoKHR *pl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    अगर (pl) {
        profile_list = *pl;
        profile_list.p_अग्र = शून्य;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    स्थिर VkImageFormatListCreateInfo *fl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    अगर (fl) {
        format_list = *fl;
        format_list.p_अग्र = शून्य;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    क्रम (पूर्णांक i = 0; i < AV_अंक_तथ्य_POINTERS &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        क्रम (पूर्णांक j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_अग्र = &perf,
            };

            अगर (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            अगर (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                वापस 0;
            }

            अगर (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identicalMemoryLayout);
                वापस 0;
            }
        }
    }

    अगर (!p->vkctx.host_image_props.identicalMemoryTypeRequirements) {
        पूर्णांक सूचकांक;
        VkExternalMemoryHandleTypeFlags e;
        VkExternalMemoryImageCreateInfo eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
            .p_अग्र       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->width, hwfc->height, 1 },
            .mipLevels   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_गिनती_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गिनती = p->nb_img_qfs,
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
        क्रम (सूचकांक = 0; सूचकांक < p->mprops.memory_Type_गिनती; सूचकांक++) {
            अगर (!(req.memoryRequirements.memoryTypeBits & (1U << सूचकांक)))
                जारी;
            अगर ((p->mprops.memoryTypes[सूचकांक].propertyFlags & req_flags) == req_flags)
                अवरोध;
        }
        अगर (सूचकांक == p->mprops.memory_Type_गिनती) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            वापस 0;
        }
    }

    वापस 1;
}

अटल पूर्णांक vulkan_frames_init(AVHWFramesContext *hwfc)
{
    पूर्णांक err;
    AVVkFrame *f;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    स्थिर काष्ठा FFVkFormatEntry *fmt;
    स्थिर AVPixFmtDescriptor *desc;
    पूर्णांक disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_FRAME_FLAG_DISABLE_MULTIPLANE);
    पूर्णांक is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)));

    /* Defaults */
    अगर (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    अगर (p->use_linear_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_LINEAR;


    fmt = vk_find_format_entry(hwfc->sw_format);
    अगर (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        वापस AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    अगर ((hwfc->width  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->height & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    अगर (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        अगर (hwctx->format[0] != fmt->vkf) {
            क्रम (पूर्णांक i = 0; i < fmt->nb_images_fallback; i++) {
                अगर (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    वापस AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, शून्य,
                                 शून्य, शून्य, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        अगर (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            वापस AVERROR(EINVAL);
        }
    } अन्यथा {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, शून्य,
                                 शून्य, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        अगर (err < 0)
            वापस err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    पूर्णांक drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_find_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    अगर (!is_lone_dpb && !drm_mod_with_video) {
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
        अगर (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        अगर ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        अगर (!hwctx->img_flags) {
            पूर्णांक sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_BIT |
                                             VK_IMAGE_USAGE_STORAGE_BIT);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
            अगर (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_BIT;
                अगर ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_BIT;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    अगर ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        स्थिर VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_find_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        अगर (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        } अन्यथा {
            uint32_t i;
            क्रम (i = 0; i < pl->profile_गिनती; i++) {
                /* Video ops start at exactly 0x00010000 */
                अगर (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    अवरोध;
            }
            अगर (i == pl->profile_गिनती)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    अगर ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

    अगर (!hwctx->lock_frame)
        hwctx->lock_frame = lock_frame;

    अगर (!hwctx->unlock_frame)
        hwctx->unlock_frame = unlock_frame;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, शून्य);
    अगर (err)
        वापस err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, शून्य);
    अगर (err)
        वापस err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, शून्य);
    अगर (err)
        वापस err;

    /* Test to see if allocation will fail */
    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    अगर (err)
        वापस err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    अगर (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        अगर (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_frame_free(hwfc, f);
            वापस AVERROR_EXTERNAL;
        }
        क्रम (पूर्णांक i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = शून्य;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_अग्र = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_गिनती, माप(*modp.pDrmFormatModifierProperties));
            अगर (!modp.pDrmFormatModifierProperties) {
                vulkan_frame_free(hwfc, f);
                वापस AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            क्रम (uint32_t j = 0; j < modp.drm_Format_Modifier_गिनती; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                अगर (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    अवरोध;
                }
            }

            अगर (mod_props == शून्य) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_frame_free(hwfc, f);
                वापस AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_frame_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    अगर (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_internal = av_बफर_pool_init2(माप(AVVkFrame),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  शून्य);
        अगर (!ffhwframesctx(hwfc)->pool_internal)
            वापस AVERROR(ENOMEM);
    }

    वापस 0;
}

अटल पूर्णांक vulkan_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[0] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_VULKAN;
    frame->width   = hwfc->width;
    frame->height  = hwfc->height;

    वापस 0;
}

अटल पूर्णांक vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       क्रमागत AVHWFrameTransferDirection dir,
                                       क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;
    पूर्णांक n = 2;

#अगर CONFIG_CUDA
    n++;
#पूर्ण_अगर
    fmts = av_malloc_array(n, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#अगर CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#पूर्ण_अगर
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    वापस 0;
}

#अगर CONFIG_LIBDRM
अटल व्योम vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_frame_free(hwfc, hwmap->priv);
}

अटल स्थिर काष्ठा {
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
#अगर_घोषित DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#पूर्ण_अगर
};

अटल अंतरभूत VkFormat drm_to_vulkan_fmt(uint32_t drm_fourcc)
{
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        अगर (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            वापस vulkan_drm_format_map[i].vk_format;
    वापस VK_FORMAT_UNDEFINED;
}

अटल पूर्णांक vulkan_map_from_drm_frame_desc(AVHWFramesContext *hwfc, AVVkFrame **frame,
                                          स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
    AVVkFrame *f;
    पूर्णांक bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    स्थिर AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->तथ्य[0];
    VkBindImageMemoryInfo bind_info[AV_DRM_MAX_PLANES];
    VkBindImagePlaneMemoryInfo plane_info[AV_DRM_MAX_PLANES];

    क्रम (पूर्णांक i = 0; i < desc->nb_layers; i++) {
        अगर (drm_to_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            वापस AVERROR(EINVAL);
        }
    }

    अगर (!(f = av_vk_frame_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        जाओ fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    क्रम (पूर्णांक i = 0; i < desc->nb_layers; i++) {
        स्थिर पूर्णांक planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_मूल्य  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_अग्र = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_गिनती = planes,
            .pPlaneLayouts = (स्थिर VkSubresourceLayout *)&ext_img_layouts,
        };
        VkExternalMemoryImageCreateInfo ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
            .p_अग्र       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_to_vulkan_fmt(desc->layers[i].format),
            .extent.depth          = 1,
            .mipLevels             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_गिनती_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गिनती = p->nb_img_qfs,
            .sharingMode           = p->nb_img_qfs > 1 ? VK_SHARING_MODE_CONCURRENT :
                                                         VK_SHARING_MODE_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        अगर (planes == 1) {
            स्थिर VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            अगर (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .p_अग्र = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .pQueueFamilyIndices = create_info.pQueueFamilyIndices,
            .queue_Family_सूचकांक_गिनती = create_info.queue_Family_सूचकांक_गिनती,
            .sharingMode = create_info.sharingMode,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_अग्र = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        अगर (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        अगर (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .p_अग्र  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        अगर (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.width, &create_info.extent.height,
                     hwfc->sw_format, src->width, src->height, i);

        /* Set the subresource layout based on the layer properties */
        क्रम (पूर्णांक j = 0; j < planes; j++) {
            ext_img_layouts[j].offset     = desc->layers[i].planes[j].offset;
            ext_img_layouts[j].rowPitch   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].आकार       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].depthPitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            जाओ fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        अगर (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            जाओ fail;
        }

        f->queue_family[i] = VK_QUEUE_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_मूल्य[i] = 0;
    }

    क्रम (पूर्णांक i = 0; i < desc->nb_layers; i++) {
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
            .p_अग्र = &ded_req,
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
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_सूचकांक].fd),
            .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        VkMemoryDedicatedAllocateInfo ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .p_अग्र = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->GetMemoryFdPropertiesKHR(hwctx->act_dev,
                                           VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
                                           idesc.fd, &fdmp);
        अगर (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            बंद(idesc.fd);
            जाओ fail;
        }

        vk->GetImageMemoryRequirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.memoryRequirements.memoryTypeBits = fdmp.memoryTypeBits;

        err = alloc_mem(ctx, &req2.memoryRequirements,
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                        (ded_req.prefersDedicatedAllocation ||
                         ded_req.requiresDedicatedAllocation) ?
                            &ded_alloc : ded_alloc.p_अग्र,
                        &f->flags, &f->mem[i]);
        अगर (err) {
            बंद(idesc.fd);
            जाओ fail;
        }

        f->आकार[i] = req2.memoryRequirements.आकार;
    }

    क्रम (पूर्णांक i = 0; i < desc->nb_layers; i++) {
        स्थिर पूर्णांक planes = desc->layers[i].nb_planes;
        क्रम (पूर्णांक j = 0; j < planes; j++) {
            VkImageAspectFlagBits aspect = j == 0 ? VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT :
                                                    VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
            plane_info[bind_counts].p_अग्र = शून्य;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
            bind_info[bind_counts].p_अग्र  = planes > 1 ? &plane_info[bind_counts] : शून्य;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].memory = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].memoryOffset = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        जाओ fail;
    }

    *frame = f;

    वापस 0;

fail:
    vulkan_frame_free(hwfc, f);

    वापस err;
}

अटल पूर्णांक vulkan_map_from_drm_frame_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          स्थिर AVDRMFrameDescriptor *desc, पूर्णांक flags)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#अगर_घोषित DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    अगर (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_बफर cmd_buf;
        FFVkExecContext *exec;
        VkImageMemoryBarrier2 img_bar[AV_अंक_तथ्य_POINTERS];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        पूर्णांक nb_img_bar = 0;

        क्रम (पूर्णांक i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_द्विआधारी,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_अग्र = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            काष्ठा dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            अगर (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(त्रुटि_सं);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                क्रम (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                वापस err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            अगर (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                क्रम (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                वापस err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_BIT,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            अगर (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                क्रम (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                वापस err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_start(&p->vkctx, exec);
        अगर (err < 0) {
            क्रम (पूर्णांक i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            वापस err;
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
        अगर (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            वापस err;
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
                .image_Memory_Barrier_गिनती = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        अगर (err < 0)
            वापस err;
    } अन्यथा
#पूर्ण_अगर
    {
        AVVkFrame *f = (AVVkFrame *)dst->तथ्य[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_IMPORT);
        अगर (err)
            वापस err;
    }

    वापस 0;
}

अटल पूर्णांक vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err = 0;
    AVVkFrame *f;
    स्थिर AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->तथ्य[0];

    अगर ((err = vulkan_map_from_drm_frame_desc(hwfc, &f, src, flags)))
        वापस err;

    /* The unmapping function will free this */
    dst->तथ्य[0] = (uint8_t *)f;
    dst->width   = src->width;
    dst->height  = src->height;

    err = ff_hwframe_map_create(dst->hw_frames_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    अगर (err < 0)
        जाओ fail;

    err = vulkan_map_from_drm_frame_sync(hwfc, dst, desc, flags);
    अगर (err < 0)
        वापस err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    वापस 0;

fail:
    vulkan_frame_free(hwfc->device_ctx->hwctx, f);
    dst->तथ्य[0] = शून्य;
    वापस err;
}

#अगर CONFIG_VAAPI
अटल पूर्णांक vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, स्थिर AVFrame *src,
                                 पूर्णांक flags)
{
    पूर्णांक err;
    AVFrame *tmp = av_frame_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->तथ्य[3];

    अगर (!tmp)
        वापस AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_अभाज्य;

    err = av_hwframe_map(tmp, src, flags);
    अगर (err < 0)
        जाओ fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    अगर (err < 0)
        जाओ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    वापस err;
}
#पूर्ण_अगर
#पूर्ण_अगर

#अगर CONFIG_CUDA
अटल पूर्णांक export_mem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, पूर्णांक idx,
                              VkDeviceMemory mem, माप_प्रकार आकार)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#अगर_घोषित _WIN32
    CUDA_EXTERNAL_MEMORY_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .आकार = आकार,
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
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#अन्यथा
    CUDA_EXTERNAL_MEMORY_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD,
        .आकार = आकार,
    };
    VkMemoryGetFdInfoKHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
        .memory     = mem,
        .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR,
    };

    ret = vk->GetMemoryFdKHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }
#पूर्ण_अगर

    ret = CHECK_CU(cu->cuImportExternalMemory(&dst_int->ext_mem[idx], &ext_desc));
    अगर (ret < 0) {
#अगर_अघोषित _WIN32
        बंद(ext_desc.handle.fd);
#पूर्ण_अगर
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक export_sem_to_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVkFrameInternal *dst_int, पूर्णांक idx,
                              VkSemaphore sem)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#अगर_घोषित _WIN32
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
#अन्यथा
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#पूर्ण_अगर

#अगर_घोषित _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#अन्यथा
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#पूर्ण_अगर
    अगर (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        वापस AVERROR_EXTERNAL;
    }
#अगर_घोषित _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#पूर्ण_अगर

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    अगर (ret < 0) {
#अगर_अघोषित _WIN32
        बंद(ext_sem_desc.handle.fd);
#पूर्ण_अगर
        वापस AVERROR_EXTERNAL;
    }

    वापस 0;
}

अटल पूर्णांक vulkan_export_to_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 स्थिर AVFrame *frame)
{
    पूर्णांक err;
    Vk_परिणाम ret;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णांक nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->तथ्य;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUarray_format cufmt = desc->comp[0].depth > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    स्थिर पूर्णांक elem_आकार = 1 + (desc->comp[0].depth > 8);

    dst_f = (AVVkFrame *)frame->तथ्य[0];
    dst_int = dst_f->internal;

    अगर (!dst_int->cuda_fc_ref) {
        माप_प्रकार offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_बफर_ref(cuda_hwfc);
        अगर (!dst_int->cuda_fc_ref)
            वापस AVERROR(ENOMEM);

        nb_images = ff_vk_गिनती_images(dst_f);
        क्रम (पूर्णांक i = 0; i < nb_images; i++) {
            err = export_mem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->आकार[i]);
            अगर (err < 0)
                जाओ fail;

            err = export_sem_to_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            अगर (err < 0)
                जाओ fail;
        }

        अगर (nb_images != planes) {
            क्रम (पूर्णांक i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                अगर (desc->comp[i].step / elem_आकार > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    जाओ fail;
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

        क्रम (पूर्णांक i = 0; i < planes; i++) {
            CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC tex_desc = {
                .offset = offsets[i],
                .arrayDesc = {
                    .Depth = 0,
                    .Format = cufmt,
                    .अंक_Channels = desc->comp[i].step / elem_आकार,
                    .Flags = 0,
                },
                .अंक_Levels = 1,
            };
            पूर्णांक p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);
            tex_desc.arrayDesc.Width = p_w;
            tex_desc.arrayDesc.Height = p_h;

            ret = CHECK_CU(cu->cuExternalMemoryGetMappedMipmappedArray(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            अगर (ret < 0) {
                err = AVERROR_EXTERNAL;
                जाओ fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            अगर (ret < 0) {
                err = AVERROR_EXTERNAL;
                जाओ fail;
            }

        }
    }

    वापस 0;

fail:
    vulkan_free_internal(p, dst_f);
    वापस err;
}

अटल पूर्णांक vulkan_transfer_तथ्य_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, स्थिर AVFrame *src)
{
    पूर्णांक err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    पूर्णांक nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_अंक_तथ्य_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_अंक_तथ्य_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)dst->तथ्य[0];
    nb_images = ff_vk_गिनती_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    अगर (err < 0)
        वापस err;

    err = CHECK_CU(cu->cu_Ctx_धकेलो_Current(cuda_dev->cuda_ctx));
    अगर (err < 0)
        वापस err;

    err = vulkan_export_to_cuda(hwfc, src->hw_frames_ctx, dst);
    अगर (err < 0) {
        CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
        वापस err;
    }

    dst_int = dst_f->internal;

    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.मूल्य = dst_f->sem_मूल्य[i] + 0;
        s_s_par[i].params.fence.मूल्य = dst_f->sem_मूल्य[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    अगर (err < 0)
        जाओ fail;

    क्रम (पूर्णांक i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .srcMemoryType = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->तथ्य[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dstMemoryType = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        पूर्णांक p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = p_w * desc->comp[i].step;
        cpy.Height = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        अगर (err < 0)
            जाओ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    अगर (err < 0)
        जाओ fail;

    क्रम (पूर्णांक i = 0; i < nb_images; i++)
        dst_f->sem_मूल्य[i]++;

    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    वापस err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_बफर_unref(&dst->buf[0]);
    वापस err;
}
#पूर्ण_अगर

अटल पूर्णांक vulkan_map_to(AVHWFramesContext *hwfc, AVFrame *dst,
                         स्थिर AVFrame *src, पूर्णांक flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    चयन (src->format) {
#अगर CONFIG_LIBDRM
#अगर CONFIG_VAAPI
    हाल AV_PIX_FMT_VAAPI:
        अगर (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            वापस vulkan_map_from_vaapi(hwfc, dst, src, flags);
        अन्यथा
            वापस AVERROR(ENOSYS);
#पूर्ण_अगर
    हाल AV_PIX_FMT_DRM_अभाज्य:
        अगर (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            वापस vulkan_map_from_drm(hwfc, dst, src, flags);
        अन्यथा
            वापस AVERROR(ENOSYS);
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }
}

#अगर CONFIG_LIBDRM
प्रकार काष्ठा VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVkFrame *source;
} VulkanDRMMapping;

अटल व्योम vulkan_unmap_to_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_frame_sync(hwfc, hwmap->source, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    क्रम (पूर्णांक i = 0; i < drm_desc->nb_objects; i++)
        बंद(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

अटल अंतरभूत uint32_t vulkan_fmt_to_drm(VkFormat vkfmt)
{
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        अगर (vulkan_drm_format_map[i].vk_format == vkfmt)
            वापस vulkan_drm_format_map[i].drm_fourcc;
    वापस DRM_FORMAT_INVALID;
}

#घोषणा MAX_MEMORY_PLANES 4
अटल VkImageAspectFlags plane_सूचकांक_to_aspect(पूर्णांक plane) {
    अगर (plane == 0) वापस VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
    अगर (plane == 1) वापस VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT;
    अगर (plane == 2) वापस VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;
    अगर (plane == 3) वापस VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT;

    av_assert2 (0 && "Invalid plane index");
    वापस VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
}

#अगर_घोषित DMA_BUF_IOCTL_EXPORT_SYNC_FILE
अटल पूर्णांक vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVkFrame *f,
                                     VulkanFramesPriv *fp, पूर्णांक nb_sems)
{
    पूर्णांक sync_fd = -1;
    Vk_परिणाम ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    अगर (f->internal->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_अग्र         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_द्विआधारी,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_अग्र = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->internal->drm_sync_sem);
        अगर (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            वापस AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    अगर (ff_vk_exec_start(&p->vkctx, exec) >= 0) {
        क्रम (पूर्णांक i = 0; i < nb_sems; i++)
            ff_vk_exec_add_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_मूल्य[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        ff_vk_exec_add_dep_bool_sem(&p->vkctx, exec, &f->internal->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 0);
        अगर (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->internal->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            अगर (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    वापस sync_fd;
}
#पूर्ण_अगर

अटल पूर्णांक vulkan_map_to_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err = 0;
    Vk_परिणाम ret;
    AVVkFrame *f = (AVVkFrame *)src->तथ्य[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VulkanFramesPriv *fp = hwfc->hwctx;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    स्थिर पूर्णांक nb_sems = nb_images;
    पूर्णांक free_drm_desc_on_err = 1;
    पूर्णांक sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(माप(*drm_desc));
    अगर (!drm_desc)
        वापस AVERROR(ENOMEM);

    err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_MODE_EXTERNAL_EXPORT);
    अगर (err < 0)
        जाओ end;

#अगर_घोषित DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        अगर (err < 0)
            जाओ end;
        sync_fd = err;
        err = 0;
    }
#पूर्ण_अगर

    अगर (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_गिनती = nb_sems,
            .pSemaphores    = f->sem,
            .p_मूल्यावली        = f->sem_मूल्य,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &vulkan_unmap_to_drm, drm_desc);
    अगर (err < 0)
        जाओ end;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    अगर (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        जाओ end;
    }

    क्रम (पूर्णांक i = 0; (i < planes) && (f->mem[i]); i++) {
        VkMemoryGetFdInfoKHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
            .memory     = f->mem[i],
            .handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };

        ret = vk->GetMemoryFdKHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        अगर (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            जाओ end;
        }

#अगर HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        अगर (sync_fd >= 0) {
            पूर्णांक dup_fd = dup(sync_fd);
            अगर (dup_fd >= 0) {
                काष्ठा dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                अगर (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(त्रुटि_सं)));
                बंद(dup_fd);
            } अन्यथा {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(त्रुटि_सं)));
            }
        }
#पूर्ण_अगर

        drm_desc->nb_objects++;
        drm_desc->objects[i].आकार = f->आकार[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    क्रम (पूर्णांक i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_to_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_गिनती;

        अगर (drm_desc->layers[i].nb_planes > MAX_MEMORY_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            जाओ end;
        }

        क्रम (पूर्णांक j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            पूर्णांक aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspectMask = plane_सूचकांक_to_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_सूचकांक = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].offset = layout.offset;
            drm_desc->layers[i].planes[j].pitch  = layout.rowPitch;
        }

        अगर (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            जाओ end;
        }


        अगर (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            जारी;

    }

    dst->width   = src->width;
    dst->height  = src->height;
    dst->तथ्य[0] = (uint8_t *)drm_desc;
    dst->hw_frames_ctx = av_बफर_ref(src->hw_frames_ctx);

    अगर (sync_fd >= 0)
        बंद(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    वापस 0;

end:
    क्रम (पूर्णांक i = 0; i < drm_desc->nb_objects; i++)
        बंद(drm_desc->objects[i].fd);
    अगर (free_drm_desc_on_err)
        av_free(drm_desc);
    अगर (sync_fd >= 0)
        बंद(sync_fd);
    वापस err;
}

#अगर CONFIG_VAAPI
अटल पूर्णांक vulkan_map_to_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;
    AVFrame *tmp = av_frame_alloc();
    अगर (!tmp)
        वापस AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_अभाज्य;

    err = vulkan_map_to_drm(hwfc, tmp, src, flags);
    अगर (err < 0)
        जाओ fail;

    err = av_hwframe_map(dst, tmp, flags);
    अगर (err < 0)
        जाओ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    वापस err;
}
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           स्थिर AVFrame *src, पूर्णांक flags)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    चयन (dst->format) {
#अगर CONFIG_LIBDRM
    हाल AV_PIX_FMT_DRM_अभाज्य:
        अगर (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            वापस vulkan_map_to_drm(hwfc, dst, src, flags);
        अन्यथा
            वापस AVERROR(ENOSYS);
#अगर CONFIG_VAAPI
    हाल AV_PIX_FMT_VAAPI:
        अगर (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            वापस vulkan_map_to_vaapi(hwfc, dst, src, flags);
        अन्यथा
            वापस AVERROR(ENOSYS);
#पूर्ण_अगर
#पूर्ण_अगर
    शेष:
        अवरोध;
    }
    वापस AVERROR(ENOSYS);
}

अटल पूर्णांक copy_बफर_तथ्य(AVHWFramesContext *hwfc, FFVk_बफर *vkbuf,
                            AVFrame *swf, Vk_बफर_Image_Copy *region,
                            पूर्णांक planes, पूर्णांक upload)
{
    पूर्णांक err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    पूर्णांक bytewidth[AV_अंक_तथ्य_POINTERS];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    क्रम (पूर्णांक i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->width, i);
        अगर (bytewidth[i] < 0)
            वापस bytewidth[i];
    }

    अगर (upload) {
        क्रम (पूर्णांक i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].बफर_Offset,
                                region[i].बफर_Row_लंबाई,
                                swf->तथ्य[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.height);

        err = ff_vk_flush_बफर(&p->vkctx, vkbuf, 0, VK_WHOLE_आकार, 1);
        अगर (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            वापस AVERROR_EXTERNAL;
        }
    } अन्यथा {
        err = ff_vk_flush_बफर(&p->vkctx, vkbuf, 0, VK_WHOLE_आकार, 0);
        अगर (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            वापस AVERROR_EXTERNAL;
        }

        क्रम (पूर्णांक i = 0; i < planes; i++)
            av_image_copy_plane(swf->तथ्य[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].बफर_Offset,
                                region[i].बफर_Row_लंबाई,
                                bytewidth[i],
                                region[i].imageExtent.height);
    }

    वापस 0;
}

अटल पूर्णांक get_plane_buf(AVHWFramesContext *hwfc, FFVk_बफर **dst,
                         AVFrame *swf, Vk_बफर_Image_Copy *region, पूर्णांक upload)
{
    पूर्णांक err;
    uint32_t p_w, p_h;
    VulkanFramesPriv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(swf->format);
    Vk_बफर_Usage_Flags buf_usage = upload ? VK_बफर_USAGE_TRANSFER_SRC_BIT :
                                            VK_बफर_USAGE_TRANSFER_DST_BIT;

    माप_प्रकार buf_offset = 0;
    क्रम (पूर्णांक i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        region[i] = (Vk_बफर_Image_Copy) {
            .बफर_Offset = buf_offset,
            .बफर_Row_लंबाई = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_बफर_Copy_Row_Pitch_Alignment),
            .बफर_Image_Height = p_h,
            .imageSubresource.layer_गिनती = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_offset += FFALIGN(p_h*region[i].बफर_Row_लंबाई,
                              p->props.properties.limits.optimal_बफर_Copy_Offset_Alignment);
    }

    err = ff_vk_get_pooled_बफर(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  शून्य, buf_offset,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                  p->vkctx.host_cached_flag);
    अगर (err < 0)
        वापस err;

    वापस 0;
}

अटल पूर्णांक host_map_frame(AVHWFramesContext *hwfc, FFVk_बफर **dst, पूर्णांक *nb_bufs,
                          AVFrame *swf, Vk_बफर_Image_Copy *region, पूर्णांक upload)
{
    पूर्णांक err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    पूर्णांक nb_src_bufs;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(swf->format);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_बफर_Usage_Flags buf_usage = upload ? VK_बफर_USAGE_TRANSFER_SRC_BIT :
                                            VK_बफर_USAGE_TRANSFER_DST_BIT;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    जबतक (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    अगर (nb_src_bufs == 1) {
        err = ff_vk_host_map_बफर(&p->vkctx, &dst[0],
                                    swf->तथ्य[0], VK_WHOLE_आकार, swf->buf[0],
                                    buf_usage);
        अगर (err < 0)
            वापस err;
        (*nb_bufs)++;

        क्रम (पूर्णांक i = 0; i < planes; i++)
            region[i].बफर_Offset = dst[0]->virtual_offset +
                                     swf->तथ्य[i] - swf->तथ्य[0];
    } अन्यथा अगर (nb_src_bufs == planes) { /* One buffer per plane */
        क्रम (पूर्णांक i = 0; i < planes; i++) {
            err = ff_vk_host_map_बफर(&p->vkctx, &dst[i],
                                        swf->तथ्य[i], VK_WHOLE_आकार,
                                        swf->buf[i], buf_usage);
            अगर (err < 0)
                जाओ fail;
            (*nb_bufs)++;

            region[i].बफर_Offset = dst[i]->virtual_offset;
        }
    } अन्यथा {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        वापस AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    क्रम (पूर्णांक i = 0; i < planes; i++) {
        पूर्णांक align = FFMAX(desc->comp[i].step, p->transfer_offset_align);
        अगर ((align & (align - 1)) || (region[i].बफर_Offset & (align - 1))) {
            err = AVERROR(EINVAL);
            जाओ fail;
        }
    }

    वापस 0;

fail:
    क्रम (पूर्णांक i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    वापस err;
}

अटल पूर्णांक vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, पूर्णांक upload)
{
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->तथ्य[0];
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(swf->format);
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_अंक_तथ्य_POINTERS];
    पूर्णांक nb_layout_ch = 0;

    hwfc_vk->lock_frame(hwfc, hwf_vk);

    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        पूर्णांक compat = 0;
        क्रम (पूर्णांक j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_गिनती; j++) {
            अगर (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                अवरोध;
            }
        }
        अगर (compat)
            जारी;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .level_गिनती = 1,
                .layer_गिनती = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_मूल्यावली = hwf_vk->sem_मूल्य,
        .semaphore_गिनती = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    अगर (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    अगर (upload) {
        VkMemoryToImageCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_गिनती = 1,
            },
        };
        VkCopyMemoryToImageInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT,
            .region_गिनती = 1,
            .pRegions = &region_info,
        };
        क्रम (पूर्णांक i = 0; i < planes; i++) {
            पूर्णांक img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

            region_info.pHostPointer = swf->तथ्य[i];
            region_info.memory_Row_लंबाई = swf->linesize[i] / desc->comp[i].step;
            region_info.imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->CopyMemoryToImageEXT(hwctx->act_dev, &copy_info);
        }
    } अन्यथा {
        VkImageToMemoryCopyEXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT,
            .imageSubresource = {
                .layer_गिनती = 1,
            },
        };
        VkCopyImageToMemoryInfoEXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT,
            .region_गिनती = 1,
            .pRegions = &region_info,
        };
        क्रम (पूर्णांक i = 0; i < planes; i++) {
            पूर्णांक img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

            region_info.pHostPointer = swf->तथ्य[i];
            region_info.memory_Row_लंबाई = swf->linesize[i] / desc->comp[i].step;
            region_info.imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->CopyImageToMemoryEXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_frame(hwfc, hwf_vk);

    वापस 0;
}

अटल पूर्णांक vulkan_transfer_frame(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 पूर्णांक upload)
{
    पूर्णांक err;
    VulkanFramesPriv *fp = hwfc->hwctx;
    AVVulkanFramesContext *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    पूर्णांक host_mapped = 0;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->तथ्य[0];
    Vk_बफर_Image_Copy region[AV_अंक_तथ्य_POINTERS]; // always one per plane

    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(swf->format);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    स्थिर पूर्णांक nb_images = ff_vk_गिनती_images(hwf_vk);

    VkImageMemoryBarrier2 img_bar[AV_अंक_तथ्य_POINTERS];
    पूर्णांक nb_img_bar = 0;

    FFVk_बफर *bufs[AV_अंक_तथ्य_POINTERS];
    पूर्णांक nb_bufs = 0;

    Vk_Command_बफर cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    अगर ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        वापस AVERROR(EINVAL);
    }

    अगर (swf->width > hwfc->width || swf->height > hwfc->height)
        वापस AVERROR(EINVAL);

    पूर्णांक host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;
    पूर्णांक host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_MEMORY &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    क्रम (पूर्णांक i = 0; i < planes; i++)
        अगर (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    अगर (!upload && host_copy) {
        क्रम (पूर्णांक i = 0; i < nb_images; i++) {
            पूर्णांक compat = 0;
            क्रम (पूर्णांक j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_गिनती; j++) {
                अगर (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    अवरोध;
                }
            }
            अगर (!compat) {
                host_copy = 0;
                अवरोध;
            }
        }
    }

    अगर (host_copy)
        वापस vulkan_transfer_host(hwfc, hwf, swf, upload);

    क्रम (पूर्णांक i = 0; i < av_pix_fmt_गिनती_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->width, swf->height, i);

        /* Buffer region for this plane */
        region[i] = (Vk_बफर_Image_Copy) {
            .बफर_Offset = 0,
            .बफर_Row_लंबाई = FFABS(swf->linesize[i]),
            .बफर_Image_Height = p_h,
            .imageSubresource.layer_गिनती = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    अगर (host_map) {
        err = host_map_frame(hwfc, bufs, &nb_bufs, swf, region, upload);
        अगर (err >= 0)
            host_mapped = 1;
    }

    अगर (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        अगर (err < 0)
            जाओ end;
        nb_bufs = 1;

        अगर (upload) {
            err = copy_बफर_तथ्य(hwfc, bufs[0], swf, region, planes, 1);
            अगर (err < 0)
                जाओ end;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_start(&p->vkctx, exec);
    अगर (err < 0)
        जाओ end;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_add_dep_frame(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_TRANSFER_BIT);
    अगर (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        जाओ end;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    अगर (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        अगर (host_mapped) {
            err = ff_vk_exec_add_dep_sw_frame(&p->vkctx, exec, swf);
            अगर (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                जाओ end;
            }
        }

        /* Add the buffers as a dependency */
        क्रम (पूर्णांक i = 0; i < nb_bufs; i++)
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
            .image_Memory_Barrier_गिनती = nb_img_bar,
    });

    क्रम (पूर्णांक i = 0; i < planes; i++) {
        पूर्णांक buf_idx = FFMIN(i, (nb_bufs - 1));
        पूर्णांक img_idx = FFMIN(i, (nb_images - 1));
        FFVk_बफर *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].बफर_Row_लंबाई;
        region[i].बफर_Row_लंबाई /= desc->comp[i].step;
        region[i].imageSubresource.aspectMask = ff_vk_aspect_flag(hwf, i);

        अगर (upload)
            vk->Cmd_Copy_बफर_To_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        अन्यथा
            vk->Cmd_Copy_Image_To_बफर(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].बफर_Row_लंबाई = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    अगर (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        अगर (!host_mapped)
            err = copy_बफर_तथ्य(hwfc, bufs[0], swf, region, planes, 0);
    }

end:
    क्रम (पूर्णांक i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    वापस err;
}

अटल पूर्णांक vulkan_transfer_तथ्य_to(AVHWFramesContext *hwfc, AVFrame *dst,
                                   स्थिर AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    चयन (src->format) {
#अगर CONFIG_CUDA
    हाल AV_PIX_FMT_CUDA:
#अगर_घोषित _WIN32
        अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#अन्यथा
        अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#पूर्ण_अगर
            वापस vulkan_transfer_तथ्य_from_cuda(hwfc, dst, src);
        av_fallthrough;
#पूर्ण_अगर
    शेष:
        अगर (src->hw_frames_ctx)
            वापस AVERROR(ENOSYS);
        अन्यथा
            वापस vulkan_transfer_frame(hwfc, (AVFrame *)src, dst, 1);
    }
}

#अगर CONFIG_CUDA
अटल पूर्णांक vulkan_transfer_तथ्य_to_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        स्थिर AVFrame *src)
{
    पूर्णांक err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVkFrameInternal *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    VulkanFramesPriv *fp = hwfc->hwctx;
    स्थिर पूर्णांक planes = av_pix_fmt_गिनती_planes(hwfc->sw_format);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    पूर्णांक nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_frames_ctx->तथ्य;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADeviceContextInternal *cu_internal = cuda_dev->internal;
    CudaFunctions *cu = cu_internal->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_अंक_तथ्य_POINTERS] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_अंक_तथ्य_POINTERS] = { 0 };

    dst_f = (AVVkFrame *)src->तथ्य[0];
    nb_images = ff_vk_गिनती_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_EXPORT);
    अगर (err < 0)
        वापस err;

    err = CHECK_CU(cu->cu_Ctx_धकेलो_Current(cuda_dev->cuda_ctx));
    अगर (err < 0)
        वापस err;

    err = vulkan_export_to_cuda(hwfc, dst->hw_frames_ctx, src);
    अगर (err < 0) {
        CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
        वापस err;
    }

    dst_int = dst_f->internal;

    क्रम (पूर्णांक i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.मूल्य = dst_f->sem_मूल्य[i] + 0;
        s_s_par[i].params.fence.मूल्य = dst_f->sem_मूल्य[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->stream));
    अगर (err < 0)
        जाओ fail;

    क्रम (पूर्णांक i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dstMemoryType = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->तथ्य[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .srcMemoryType = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        पूर्णांक w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->width, hwfc->height, i);

        cpy.WidthInBytes = w * desc->comp[i].step;
        cpy.Height = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->stream));
        अगर (err < 0)
            जाओ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->stream));
    अगर (err < 0)
        जाओ fail;

    क्रम (पूर्णांक i = 0; i < nb_images; i++)
        dst_f->sem_मूल्य[i]++;

    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    वापस prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_MODE_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    vulkan_free_internal(p, dst_f);
    av_बफर_unref(&dst->buf[0]);
    वापस err;
}
#पूर्ण_अगर

अटल पूर्णांक vulkan_transfer_तथ्य_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     स्थिर AVFrame *src)
{
    av_unused VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    चयन (dst->format) {
#अगर CONFIG_CUDA
    हाल AV_PIX_FMT_CUDA:
#अगर_घोषित _WIN32
        अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#अन्यथा
        अगर ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_MEMORY) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#पूर्ण_अगर
            वापस vulkan_transfer_तथ्य_to_cuda(hwfc, dst, src);
        av_fallthrough;
#पूर्ण_अगर
    शेष:
        अगर (dst->hw_frames_ctx)
            वापस AVERROR(ENOSYS);
        अन्यथा
            वापस vulkan_transfer_frame(hwfc, dst, (AVFrame *)src, 0);
    }
}

अटल पूर्णांक vulkan_frames_derive_to(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, पूर्णांक flags)
{
    वापस vulkan_frames_init(dst_fc);
}

AVVkFrame *av_vk_frame_alloc(व्योम)
{
    पूर्णांक err;
    AVVkFrame *f = av_mallocz(माप(AVVkFrame));
    अगर (!f)
        वापस शून्य;

    f->internal = av_mallocz(माप(*f->internal));
    अगर (!f->internal) {
        av_free(f);
        वापस शून्य;
    }

    err = pthread_mutex_init(&f->internal->update_mutex, शून्य);
    अगर (err != 0) {
        av_free(f->internal);
        av_free(f);
        वापस शून्य;
    }

    वापस f;
}

स्थिर HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_आकार      = माप(VulkanDevicePriv),
    .frames_hwctx_आकार      = माप(VulkanFramesPriv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .frames_get_constraints = &vulkan_frames_get_constraints,
    .frames_init            = vulkan_frames_init,
    .frames_get_बफर      = vulkan_get_बफर,
    .frames_uninit          = vulkan_frames_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_तथ्य_to       = vulkan_transfer_तथ्य_to,
    .transfer_तथ्य_from     = vulkan_transfer_तथ्य_from,

    .map_to                 = vulkan_map_to,
    .map_from               = vulkan_map_from,
    .frames_derive_to       = &vulkan_frames_derive_to,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
