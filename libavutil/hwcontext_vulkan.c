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

#परिभाषय VK_NO_PROTOTYPES
#परिभाषय VK_ENABLE_BETA_EXTENSIONS

#यदि_परिभाषितम् _WIN32
#अन्तर्भाव <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#अन्तर्भाव <versionhelpers.h>
#अन्तर्भाव "compat/w32dlfcn.h"
#अन्यथा
#अन्तर्भाव <dlfcn.h>
#अन्तर्भाव <unistd.h>
#यदि_अन्तः

#अन्तर्भाव "thread.h"

#अन्तर्भाव "config.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_vulkan.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "uuid.h"

#अन्तर्भाव "vulkan.h"
#अन्तर्भाव "vulkan_loader.h"

#यदि CONFIG_VAAPI
#अन्तर्भाव "hwcontext_vaapi.h"
#यदि_अन्तः

#यदि CONFIG_LIBDRM
#यदि CONFIG_VAAPI
#अन्तर्भाव <va/va_drmcommon.h>
#यदि_अन्तः
#यदि_परिभाषितम् __linux__
#अन्तर्भाव <sys/sysmacros.h>
#यदि_अन्तः
#अन्तर्भाव <sys/stat.h>
#अन्तर्भाव <xf86drm.h>
#अन्तर्भाव <drm_fourcc.h>
#अन्तर्भाव "hwcontext_drm.h"
#यदि_अन्तः

#यदि HAVE_LINUX_DMA_BUF_H
#अन्तर्भाव <sys/ioctl.h>
#अन्तर्भाव <linux/dma-buf.h>
#यदि_अन्तः

#यदि CONFIG_CUDA
#अन्तर्भाव "hwcontext_cuda_internal.h"
#अन्तर्भाव "cuda_check.h"
#परिभाषय CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#यदि_अन्तः

प्रकारनिर्देश संरचना VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    Vk_Physical_Device_Workgroup_स्मृतिः_Explicit_Layout_Features_KHR explicit_mem_layout;

#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    Vk_Physical_Device_Shader_Long_सदिशम्_Features_EXT long_सदिशम्;
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_zero_initialize_device_स्मृतिः
    Vk_Physical_Device_Zero_Initialize_Device_स्मृतिः_Features_EXT zero_initialize;
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#यदि_अन्तः

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#यदि_परिभाषितम् VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#यदि_अन्तः

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR cooperative_matrix;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#यदि_परिभाषितम् VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR आन्तरिकम्_queue_sync;
#यदि_अन्तः
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

प्रकारनिर्देश संरचना VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    शून्य *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkanDeviceQueueFamily *compute_qf;
    AVVulkanDeviceQueueFamily *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    Vk_Physical_Device_स्मृतिः_Properties mprops;
    Vk_Physical_Device_External_स्मृतिः_Host_Properties_EXT hprops;
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
    पूर्णाङ्क use_रैखिकम्_images;

    /* Option to allocate all image planes in a single allocation */
    पूर्णाङ्क contiguous_planes;

    /* Disable multiplane images */
    पूर्णाङ्क disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    पूर्णाङ्क avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    पूर्णाङ्क transfer_विस्थापनम्_align;

    /* Maximum queues */
    पूर्णाङ्क सीमा_queues;
} VulkanDevicePriv;

प्रकारनिर्देश संरचना Vulkan_चौकटाः_Priv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkan_चौकटाः_Context p;

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
    पूर्णाङ्क export_requires_dedicated;
} Vulkan_चौकटाः_Priv;

प्रकारनिर्देश संरचना AVVk_Frame_आन्तरिकम् {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#यदि CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternal_स्मृतिः ext_mem[AV_अङ्कः_दत्त_सूचकाः];
    CUmipmappedArray cu_mma[AV_अङ्कः_दत्त_सूचकाः];
    CUarray cu_array[AV_अङ्कः_दत्त_सूचकाः];
    CUexternalSemaphore cu_sem[AV_अङ्कः_दत्त_सूचकाः];
#यदि_परिभाषितम् _WIN32
    HANDLE ext_mem_handle[AV_अङ्कः_दत्त_सूचकाः];
    HANDLE ext_sem_handle[AV_अङ्कः_दत्त_सूचकाः];
#यदि_अन्तः
#यदि_अन्तः
} AVVk_Frame_आन्तरिकम्;

/* Initialize all structs in VulkanDeviceFeatures */
स्थिर शून्य device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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

#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_सदिशम्, FF_VK_EXT_LONG_सदिशम्,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_सदिशम्_FEATURES_EXT);
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_zero_initialize_device_स्मृतिः
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_स्मृतिः_FEATURES_EXT);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#यदि_अन्तः

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#यदि_परिभाषितम् VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#यदि_अन्तः

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_matrix, FF_VK_EXT_COOP_MATRIX,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_स्मृतिः_EXPLICIT_LAYOUT_FEATURES_KHR);

#यदि_परिभाषितम् VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->आन्तरिकम्_queue_sync, FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#यदि_अन्तः

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
स्थिर शून्य device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#परिभाषय COPY_VAL(VAL)        \
    कुरु {                     \
        dst->VAL = src->VAL; \
    } यावत् (0)              \

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
    COPY_VAL(vulkan_1_1.storage_प्रक्षिप_Constant16);
    COPY_VAL(vulkan_1_1.storageBuffer16BitAccess);
    COPY_VAL(vulkan_1_1.एकरूपम्_And_Storage_Buffer16_Bit_Access);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalar_खण्डम्_Layout);
    COPY_VAL(vulkan_1_2.बफर_Device_स्थानाङ्कः);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_प्रक्षिप_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storageBuffer8BitAccess);
    COPY_VAL(vulkan_1_2.एकरूपम्_And_Storage_Buffer8_Bit_Access);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_बफर_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkan_स्मृतिः_Model);
    COPY_VAL(vulkan_1_2.vulkan_स्मृतिः_Model_Device_Scope);
    COPY_VAL(vulkan_1_2.vulkan_स्मृतिः_Model_Availability_Visibility_Chains);
    COPY_VAL(vulkan_1_2.एकरूपम्_बफर_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_एकरूपम्_बफर_Array_Non_एकरूपम्_Indexing);
    COPY_VAL(vulkan_1_2.shader_Sampled_Image_Array_Non_एकरूपम्_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_बफर_Array_Non_एकरूपम्_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_Image_Array_Non_एकरूपम्_Indexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.compute_पूर्णम्_Subgroups);
    COPY_VAL(vulkan_1_3.subgroup_आकार_Control);
    COPY_VAL(vulkan_1_3.shader_Zero_Initialize_Workgroup_स्मृतिः);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    COPY_VAL(long_सदिशम्.long_सदिशम्_2);
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#यदि_अन्तः

#यदि_परिभाषितम् VK_EXT_zero_initialize_device_स्मृतिः
    COPY_VAL(zero_initialize.zero_Initialize_Device_स्मृतिः);
#यदि_अन्तः

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#यदि_परिभाषितम् VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#यदि_अन्तः

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_matrix.cooperativeMatrix);

    COPY_VAL(atomic_float.shader_बफर_Float32_Atomics);
    COPY_VAL(atomic_float.shader_बफर_Float32_Atomic_सङ्कलय);

    COPY_VAL(explicit_mem_layout.workgroup_स्मृतिः_Explicit_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_स्मृतिः_Explicit_Layout_Scalar_खण्डम्_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_स्मृतिः_Explicit_Layout8_Bit_Access);
    COPY_VAL(explicit_mem_layout.workgroup_स्मृतिः_Explicit_Layout16_Bit_Access);

#यदि_परिभाषितम् VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    COPY_VAL(आन्तरिकम्_queue_sync.internallySynchronizedQueues);
#यदि_अन्तः

    COPY_VAL(optical_flow.opticalFlow);

#अपरिभाषय COPY_VAL
}

#परिभाषय ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT)
#परिभाषय ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_BIT | VK_IMAGE_ASPECT_PLANE_1_BIT | VK_IMAGE_ASPECT_PLANE_2_BIT)

स्थिर ध्रुव संरचना FFVk_Format_प्रविष्टिः {
    VkFormat vkf;
    गणना AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    पूर्णाङ्क vk_planes;
    पूर्णाङ्क nb_images;
    पूर्णाङ्क nb_images_fallback;
    ध्रुव VkFormat fallback[5];
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
स्थिर ध्रुव पूर्णाङ्क nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

ध्रुव VkFormat *av_vkfmt_from_pixfmt(गणना AVPixelFormat p)
{
    प्रति (पूर्णाङ्क i = 0; i < nb_vk_formats_list; i++)
        यदि (vk_formats_list[i].pixfmt == p)
            प्रत्यागम vk_formats_list[i].fallback;
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव संरचना FFVk_Format_प्रविष्टिः *vk_find_format_प्रविष्टिः(गणना AVPixelFormat p)
{
    प्रति (पूर्णाङ्क i = 0; i < nb_vk_formats_list; i++)
        यदि (vk_formats_list[i].pixfmt == p)
            प्रत्यागम &vk_formats_list[i];
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, गणना AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_अङ्कः_दत्त_सूचकाः], /* Output format list */
                              पूर्णाङ्क *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              पूर्णाङ्क disable_multiplane, पूर्णाङ्क need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    ध्रुव VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_BIT |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_BIT  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_BIT;

    प्रति (पूर्णाङ्क i = 0; i < nb_vk_formats_list; i++) {
        यदि (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_अग्र = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            पूर्णाङ्क basics_primary = 0, basics_secondary = 0;
            पूर्णाङ्क storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_रैखिकम् ?
                             fprops.रैखिकम्_Tiling_Features : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);

            यदि (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_रैखिकम् ?
                                  fprops.रैखिकम्_Tiling_Features : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT);
            } अन्यथा {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            यदि (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                यदि (fmts) {
                    यदि (vk_formats_list[i].nb_images > 1) {
                        प्रति (पूर्णाङ्क j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } अन्यथा {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                यदि (nb_images)
                    *nb_images = 1;
                यदि (aspect)
                    *aspect = vk_formats_list[i].aspect;
                यदि (supported_usage)
                    *supported_usage = ff_vk_map_feats_गन्तव्यम्_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_BIT : 0);
                प्रत्यागम 0;
            } अन्यथा यदि (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                यदि (fmts) {
                    प्रति (पूर्णाङ्क j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                यदि (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                यदि (aspect)
                    *aspect = vk_formats_list[i].aspect;
                यदि (supported_usage)
                    *supported_usage = ff_vk_map_feats_गन्तव्यम्_usage(feats_secondary);
                प्रत्यागम 0;
            } अन्यथा {
                प्रत्यागम AVERROR(ENOTSUP);
            }
        }
    }

    प्रत्यागम AVERROR(EINVAL);
}

#यदि CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               ध्रुव वर्ण *pName);
#यदि_अन्तः

स्थिर पूर्णाङ्क आरोपय_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#यदि CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#अन्यथा
    स्थिर ध्रुव वर्ण *lib_नामानि[] = {
#यदि defined(_WIN32)
        "vulkan-1.dll",
#नोचेद्यदि defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#अन्यथा
        "libvulkan.so.1",
        "libvulkan.so",
#यदि_अन्तः
    };

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(lib_नामानि); i++) {
        p->libvulkan = dlopen(lib_नामानि[i], RTLD_NOW | RTLD_LOCAL);
        यदि (p->libvulkan)
            भङ्ग;
    }

    यदि (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#यदि_अन्तः /* CONFIG_VULKAN_STATIC */

    प्रत्यागम 0;
}

प्रकारनिर्देश संरचना VulkanOptExtension {
    ध्रुव वर्ण *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

स्थिर ध्रुव VulkanOptExtension optional_instance_exts[] = {
#यदि_परिभाषितम् __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#यदि_अन्तः
    { 0 },
};

स्थिर ध्रुव VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_प्रक्षिप_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_प्रक्षिप_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME,               FF_VK_EXT_COOP_MATRIX            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_स्मृतिः_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#यदि_परिभाषितम् VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#यदि_अन्तः
#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    { VK_EXT_SHADER_LONG_सदिशम्_EXTENSION_NAME,               FF_VK_EXT_LONG_सदिशम्            },
#यदि_अन्तः
#यदि_परिभाषितम् VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#यदि_अन्तः
#यदि_परिभाषितम् VK_EXT_zero_initialize_device_स्मृतिः
    { VK_EXT_ZERO_INITIALIZE_DEVICE_स्मृतिः_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#यदि_अन्तः
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#यदि_परिभाषितम् VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC    },
#यदि_अन्तः
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_स्मृतिः_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_स्मृतिः     },
    { VK_EXT_EXTERNAL_स्मृतिः_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_स्मृतिः },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_स्मृतिः_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_स्मृतिः   },
#यदि_परिभाषितम् _WIN32
    { VK_KHR_EXTERNAL_स्मृतिः_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#यदि_अन्तः

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_QUEUE            },
    { VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_QUEUE     },
    { VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_QUEUE     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#यदि_परिभाषितम् VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#यदि_अन्तः
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

ध्रुव वर्ण **av_vk_get_optional_instance_extensions(पूर्णाङ्क *गणनम्)
{
    ध्रुव वर्ण **exts = av_malloc_array(परिमाण(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    यदि (!exts)
        प्रत्यागम रिक्त;

    प्रति (पूर्णाङ्क i = 0; i < (पूर्णाङ्क)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *गणनम् = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    प्रत्यागम exts;
}

ध्रुव वर्ण **av_vk_get_optional_device_extensions(पूर्णाङ्क *गणनम्)
{
    ध्रुव वर्ण **exts = av_malloc_array(परिमाण(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    यदि (!exts)
        प्रत्यागम रिक्त;

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *गणनम् = FF_ARRAY_ELEMS(optional_device_exts);
    प्रत्यागम exts;
}

स्थिर VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(Vk_Debug_Utils_सन्देशः_Severity_Flag_द्वयङ्काः_EXT severity,
                                    Vk_Debug_Utils_सन्देशः_Type_Flags_EXT सन्देशः_Type,
                                    ध्रुव Vk_Debug_Utils_Messenger_Callback_दत्त_EXT *दत्त,
                                    शून्य *priv)
{
    पूर्णाङ्क l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    विकल्प (दत्त->सन्देशः_Id_सङ्ख्या) {
    पक्ष 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    पक्ष 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        प्रत्यागम VK_FALSE;
    स्वभाव:
        भङ्ग;
    }

    विकल्प (severity) {
    पक्ष VK_DEBUG_UTILS_सन्देशः_SEVERITY_VERBOSE_BIT_EXT: l = AV_LOG_VERBOSE; भङ्ग;
    पक्ष VK_DEBUG_UTILS_सन्देशः_SEVERITY_INFO_BIT_EXT:    l = AV_LOG_INFO;    भङ्ग;
    पक्ष VK_DEBUG_UTILS_सन्देशः_SEVERITY_WARNING_BIT_EXT: l = AV_LOG_WARNING; भङ्ग;
    पक्ष VK_DEBUG_UTILS_सन्देशः_SEVERITY_ERROR_BIT_EXT:   l = AV_LOG_ERROR;   भङ्ग;
    स्वभाव:                                              l = AV_LOG_DEBUG;   भङ्ग;
    }

    av_log(ctx, l, "%s\n", दत्त->p_सन्देशः);
    प्रति (पूर्णाङ्क i = 0; i < दत्त->cmd_Buf_Label_गणनम्; i++)
        av_log(ctx, l, "\t%i: %s\n", i, दत्त->pCmdBufLabels[i].pLabelName);

    प्रत्यागम VK_FALSE;
}

#परिभाषय सङ्कलय_VAL_गन्तव्यम्_LIST(list, गणनम्, val)                                      \
    कुरु {                                                                       \
        list = av_realloc_array(list, ++गणनम्, परिमाण(*list));                 \
        यदि (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            गच्छ fail;                                                         \
        }                                                                      \
        list[गणनम् - 1] = av_strdup(val);                                      \
        यदि (!list[गणनम् - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            गच्छ fail;                                                         \
        }                                                                      \
    } यावत्(0)

#परिभाषय RELEASE_PROPS(props, गणनम्)                                            \
    यदि (props) {                                                               \
        प्रति (पूर्णाङ्क i = 0; i < गणनम्; i++)                                        \
            av_free((शून्य *)((props)[i]));                                     \
        av_free((शून्य *)props);                                                \
    }

स्थिर पूर्णाङ्क vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_आकार max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.स्मृतिः_Type_गणनम्);
    प्रति (पूर्णाङ्क i = 0; i < p->mprops.स्मृतिः_Type_गणनम्; i++) {
        ध्रुव Vk_स्मृतिः_Type type = p->mprops.स्मृतिः_Types[i];
        ध्रुव Vk_स्मृतिः_Heap heap = p->mprops.स्मृतिः_Heaps[type.heap_सूचकांक];
        यदि (!(type.propertyFlags & VK_स्मृतिः_PROPERTY_DEVICE_LOCAL_BIT))
            अनुवर्त;
        max_vram = FFMAX(max_vram, heap.आकार);
        यदि (type.propertyFlags & VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT)
            max_visible_vram = FFMAX(max_visible_vram, heap.आकार);
    }

    प्रत्यागम max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

गणना FFVulkan_Debug_बहुलकम् {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

स्थिर पूर्णाङ्क check_extensions(AVHWDeviceContext *ctx, पूर्णाङ्क dev, AVDictionary *opts,
                            ध्रुव वर्ण * ध्रुव **dst, uint32_t *अङ्कः,
                            गणना FFVulkan_Debug_बहुलकम् debug_बहुलकम्)
{
    ध्रुव वर्ण *tstr;
    ध्रुव वर्ण **extension_नामानि = रिक्त;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णाङ्क err = 0, प्राप्तम्, extensions_प्राप्तम् = 0;

    ध्रुव वर्ण *mod;
    पूर्णाङ्क optional_exts_अङ्कः;
    uint32_t sup_ext_गणनम्;
    वर्ण *user_exts_str = रिक्त;
    AVDictionary_प्रविष्टिः *user_exts;
    VkExtensionProperties *sup_ext;
    ध्रुव VulkanOptExtension *optional_exts;

    यदि (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_अङ्कः = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", रिक्त, 0);
        यदि (user_exts) {
            user_exts_str = av_strdup(user_exts->मानम्);
            यदि (!user_exts_str) {
                err = AVERROR(ENOMEM);
                गच्छ fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(रिक्त, &sup_ext_गणनम्, रिक्त);
        sup_ext = av_malloc_array(sup_ext_गणनम्, परिमाण(VkExtensionProperties));
        यदि (!sup_ext)
            प्रत्यागम AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(रिक्त, &sup_ext_गणनम्, sup_ext);
    } अन्यथा {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_अङ्कः = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", रिक्त, 0);
        यदि (user_exts) {
            user_exts_str = av_strdup(user_exts->मानम्);
            यदि (!user_exts_str) {
                err = AVERROR(ENOMEM);
                गच्छ fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, रिक्त,
                                               &sup_ext_गणनम्, रिक्त);
        sup_ext = av_malloc_array(sup_ext_गणनम्, परिमाण(VkExtensionProperties));
        यदि (!sup_ext)
            प्रत्यागम AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, रिक्त,
                                               &sup_ext_गणनम्, sup_ext);
    }

    प्रति (पूर्णाङ्क i = 0; i < optional_exts_अङ्कः; i++) {
        tstr = optional_exts[i].name;
        प्राप्तम् = 0;

        /* Check if the device has ReBAR for host image copies */
        यदि (!वाक्यं_तुलय(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            अनुवर्त;

        यदि (dev &&
            ((debug_बहुलकम् == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_बहुलकम् == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_बहुलकम् == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!वाक्यं_तुलय(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            अनुवर्त;
        }

        प्रति (पूर्णाङ्क j = 0; j < sup_ext_गणनम्; j++) {
            यदि (!वाक्यं_तुलय(tstr, sup_ext[j].extensionName)) {
                प्राप्तम् = 1;
                भङ्ग;
            }
        }
        यदि (!प्राप्तम्)
            अनुवर्त;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        सङ्कलय_VAL_गन्तव्यम्_LIST(extension_नामानि, extensions_प्राप्तम्, tstr);
    }

    यदि (!dev &&
        ((debug_बहुलकम् == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_बहुलकम् == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_बहुलकम् == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        प्राप्तम् = 0;
        प्रति (पूर्णाङ्क j = 0; j < sup_ext_गणनम्; j++) {
            यदि (!वाक्यं_तुलय(tstr, sup_ext[j].extensionName)) {
                प्राप्तम् = 1;
                भङ्ग;
            }
        }
        यदि (प्राप्तम्) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            सङ्कलय_VAL_गन्तव्यम्_LIST(extension_नामानि, extensions_प्राप्तम्, tstr);
        } अन्यथा {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            गच्छ fail;
        }
    }

#यदि_परिभाषितम् VK_KHR_shader_relaxed_extended_instruction
    यदि ((debug_बहुलकम् == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        प्राप्तम् = 0;
        प्रति (पूर्णाङ्क j = 0; j < sup_ext_गणनम्; j++) {
            यदि (!वाक्यं_तुलय(tstr, sup_ext[j].extensionName)) {
                प्राप्तम् = 1;
                भङ्ग;
            }
        }
        यदि (!प्राप्तम्) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            गच्छ fail;
        }
    }
#यदि_अन्तः

    यदि (user_exts_str) {
        वर्ण *save, *token = av_strtok(user_exts_str, "+", &save);
        यावत् (token) {
            प्राप्तम् = 0;
            प्रति (पूर्णाङ्क j = 0; j < sup_ext_गणनम्; j++) {
                यदि (!वाक्यं_तुलय(token, sup_ext[j].extensionName)) {
                    प्राप्तम् = 1;
                    भङ्ग;
                }
            }
            यदि (प्राप्तम्) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                सङ्कलय_VAL_गन्तव्यम्_LIST(extension_नामानि, extensions_प्राप्तम्, token);
            } अन्यथा {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(रिक्त, "+", &save);
        }
    }

    *dst = extension_नामानि;
    *अङ्कः = extensions_प्राप्तम्;

    av_free(user_exts_str);
    av_free(sup_ext);
    प्रत्यागम 0;

fail:
    RELEASE_PROPS(extension_नामानि, extensions_प्राप्तम्);
    av_free(user_exts_str);
    av_free(sup_ext);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        ध्रुव वर्ण * ध्रुव **dst, uint32_t *अङ्कः,
                        गणना FFVulkan_Debug_बहुलकम् *debug_बहुलकम्)
{
    पूर्णाङ्क err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    स्थिर ध्रुव वर्ण layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    पूर्णाङ्क layer_standard_validation_प्राप्तम् = 0;

    uint32_t sup_layer_गणनम्;
    VkLayerProperties *sup_layers;

    AVDictionary_प्रविष्टिः *user_layers = av_dict_get(opts, "layers", रिक्त, 0);
    वर्ण *user_layers_str = रिक्त;
    वर्ण *save, *token;

    ध्रुव वर्ण **enabled_layers = रिक्त;
    uint32_t enabled_layers_गणनम् = 0;

    AVDictionary_प्रविष्टिः *debug_opt = av_dict_get(opts, "debug", रिक्त, 0);
    गणना FFVulkan_Debug_बहुलकम् बहुलकम्;

    *debug_बहुलकम् = बहुलकम् = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_गणनम्, रिक्त);
    sup_layers = av_malloc_array(sup_layer_गणनम्, परिमाण(VkLayerProperties));
    यदि (!sup_layers)
        प्रत्यागम AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_गणनम्, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    प्रति (पूर्णाङ्क i = 0; i < sup_layer_गणनम्; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    यदि (!debug_opt && !user_layers)
        गच्छ अन्तः_2;

    /* Check for any properly supported validation layer */
    यदि (debug_opt) {
        यदि (!वाक्यं_तुलय(debug_opt->मानम्, "printf")) {
            बहुलकम् = FF_VULKAN_DEBUG_PRINTF;
        } अन्यथा यदि (!वाक्यं_तुलय(debug_opt->मानम्, "validate")) {
            बहुलकम् = FF_VULKAN_DEBUG_VALIDATE;
        } अन्यथा यदि (!वाक्यं_तुलय(debug_opt->मानम्, "practices")) {
            बहुलकम् = FF_VULKAN_DEBUG_PRACTICES;
        } अन्यथा {
            वर्ण *अन्तः_ptr = रिक्त;
            पूर्णाङ्क idx = strtol(debug_opt->मानम्, &अन्तः_ptr, 10);
            यदि (अन्तः_ptr == debug_opt->मानम् || अन्तः_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->मानम्);
                err = AVERROR(EINVAL);
                गच्छ अन्तः_2;
            }
            बहुलकम् = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    यदि ((बहुलकम् == FF_VULKAN_DEBUG_VALIDATE) ||
        (बहुलकम् == FF_VULKAN_DEBUG_PRINTF) ||
        (बहुलकम् == FF_VULKAN_DEBUG_PRACTICES)) {
        प्रति (पूर्णाङ्क i = 0; i < sup_layer_गणनम्; i++) {
            यदि (!वाक्यं_तुलय(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                सङ्कलय_VAL_गन्तव्यम्_LIST(enabled_layers, enabled_layers_गणनम्, layer_standard_validation);
                *debug_बहुलकम् = बहुलकम्;
                layer_standard_validation_प्राप्तम् = 1;
                भङ्ग;
            }
        }
        यदि (!layer_standard_validation_प्राप्तम्) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            गच्छ अन्तः_2;
        }
    }

    /* Process any custom layers enabled */
    यदि (user_layers) {
        पूर्णाङ्क प्राप्तम्;

        user_layers_str = av_strdup(user_layers->मानम्);
        यदि (!user_layers_str) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        यावत् (token) {
            प्राप्तम् = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            यदि (!वाक्यं_तुलय(layer_standard_validation, token) && layer_standard_validation_प्राप्तम्) {
                token = av_strtok(रिक्त, "+", &save);
                भङ्ग;
            }

            /* Try to find the layer in the list of supported layers */
            प्रति (पूर्णाङ्क j = 0; j < sup_layer_गणनम्; j++) {
                यदि (!वाक्यं_तुलय(token, sup_layers[j].layerName)) {
                    प्राप्तम् = 1;
                    भङ्ग;
                }
            }

            यदि (प्राप्तम्) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                सङ्कलय_VAL_गन्तव्यम्_LIST(enabled_layers, enabled_layers_गणनम्, token);

                /* If debug was not set as an option, force it */
                यदि (!वाक्यं_तुलय(layer_standard_validation, token))
                    *debug_बहुलकम् = FF_VULKAN_DEBUG_VALIDATE;
            } अन्यथा {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                गच्छ अन्तः_2;
            }

            token = av_strtok(रिक्त, "+", &save);
        }
    }

fail:
अन्तः_2:
    av_free(sup_layers);
    av_free(user_layers_str);

    यदि (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_गणनम्);
    } अन्यथा {
        *dst = enabled_layers;
        *अङ्कः = enabled_layers_गणनम्;
    }

    प्रत्यागम err;
}

/* Creates a VkInstance */
स्थिर पूर्णाङ्क create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           गणना FFVulkan_Debug_बहुलकम् *debug_बहुलकम्)
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .application_संस्करणम्_2 = VK_MAKE_संस्करणम्(LIBAVUTIL_संस्करणम्_MAJOR,
                                              LIBAVUTIL_संस्करणम्_MINOR,
                                              LIBAVUTIL_संस्करणम्_MICRO),
        .pEngineName        = "libavutil",
        .api_संस्करणम्         = VK_API_संस्करणम्_1_3,
        .engine_संस्करणम्      = VK_MAKE_संस्करणम्(LIBAVUTIL_संस्करणम्_MAJOR,
                                              LIBAVUTIL_संस्करणम्_MINOR,
                                              LIBAVUTIL_संस्करणम्_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    यदि (!hwctx->get_proc_addr) {
        err = आरोपय_libvulkan(ctx);
        यदि (err < 0)
            प्रत्यागम err;
    }

    err = ff_vk_आरोपय_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    यदि (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        प्रत्यागम err;
    }

    err = check_layers(ctx, opts, &inst_props.pp_Enabled_Layer_नामानि,
                       &inst_props.enabled_Layer_गणनम्, debug_बहुलकम्);
    यदि (err)
        गच्छ fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.pp_Enabled_Extension_नामानि,
                           &inst_props.enabled_Extension_गणनम्, *debug_बहुलकम्);
    hwctx->enabled_inst_extensions = inst_props.pp_Enabled_Extension_नामानि;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_गणनम्;
    यदि (err < 0)
        गच्छ fail;

    /* Enable debug features if needed */
    यदि (*debug_बहुलकम् == FF_VULKAN_DEBUG_VALIDATE) {
        स्थिर ध्रुव VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_गणनम् = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_अग्र = &validation_features;
    } अन्यथा यदि (*debug_बहुलकम् == FF_VULKAN_DEBUG_PRINTF) {
        स्थिर ध्रुव VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_गणनम् = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_अग्र = &validation_features;
    } अन्यथा यदि (*debug_बहुलकम् == FF_VULKAN_DEBUG_PRACTICES) {
        स्थिर ध्रुव VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_गणनम् = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_अग्र = &validation_features;
    }

#यदि_परिभाषितम् __APPLE__
    प्रति (पूर्णाङ्क i = 0; i < inst_props.enabled_Extension_गणनम्; i++) {
        यदि (!वाक्यं_तुलय(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.pp_Enabled_Extension_नामानि[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            भङ्ग;
        }
    }
#यदि_अन्तः

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        गच्छ fail;
    }

    err = ff_vk_आरोपय_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    यदि (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        गच्छ fail;
    }

    /* Setup debugging callback if needed */
    यदि ((*debug_बहुलकम् == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_बहुलकम् == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_बहुलकम् == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .सन्देशः_Severity = VK_DEBUG_UTILS_सन्देशः_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_सन्देशः_SEVERITY_INFO_BIT_EXT    |
                               VK_DEBUG_UTILS_सन्देशः_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_सन्देशः_SEVERITY_ERROR_BIT_EXT,
            .सन्देशः_Type = VK_DEBUG_UTILS_सन्देशः_TYPE_GENERAL_BIT_EXT    |
                           VK_DEBUG_UTILS_सन्देशः_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_सन्देशः_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .p_User_दत्त = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.pp_Enabled_Layer_नामानि, inst_props.enabled_Layer_गणनम्);
    प्रत्यागम err;
}

प्रकारनिर्देश संरचना VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_आकार]; /* Will use this first unless !has_uuid */
    पूर्णाङ्क has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    ध्रुव वर्ण *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    पूर्णाङ्क सूचकांक; /* Finally fall back to index */
} VulkanDeviceSelection;

स्थिर ध्रुव वर्ण *vk_dev_type(गणना VkPhysicalDeviceType type)
{
    विकल्प (type) {
    पक्ष VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: प्रत्यागम "integrated";
    पक्ष VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   प्रत्यागम "discrete";
    पक्ष VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    प्रत्यागम "virtual";
    पक्ष VK_PHYSICAL_DEVICE_TYPE_CPU:            प्रत्यागम "software";
    स्वभाव:                                     प्रत्यागम "unknown";
    }
}

/* Finds a device */
स्थिर पूर्णाङ्क find_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    पूर्णाङ्क err = 0, choice = -1;
    uint32_t अङ्कः;
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = रिक्त;
    VkPhysicalDeviceIDProperties *idp = रिक्त;
    VkPhysicalDeviceProperties2 *prop = रिक्त;
    VkPhysicalDeviceDriverProperties *driver_prop = रिक्त;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = रिक्त;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &अङ्कः, रिक्त);
    यदि (ret != VK_SUCCESS || !अङ्कः) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        प्रत्यागम AVERROR(ENODEV);
    }

    devices = av_malloc_array(अङ्कः, परिमाण(VkPhysicalDevice));
    यदि (!devices)
        प्रत्यागम AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &अङ्कः, devices);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    }

    prop = av_calloc(अङ्कः, परिमाण(*prop));
    यदि (!prop) {
        err = AVERROR(ENOMEM);
        गच्छ अन्तः_2;
    }

    idp = av_calloc(अङ्कः, परिमाण(*idp));
    यदि (!idp) {
        err = AVERROR(ENOMEM);
        गच्छ अन्तः_2;
    }

    driver_prop = av_calloc(अङ्कः, परिमाण(*driver_prop));
    यदि (!driver_prop) {
        err = AVERROR(ENOMEM);
        गच्छ अन्तः_2;
    }

    यदि (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(अङ्कः, परिमाण(*drm_prop));
        यदि (!drm_prop) {
            err = AVERROR(ENOMEM);
            गच्छ अन्तः_2;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
        यदि (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
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

    यदि (select->has_uuid) {
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
            यदि (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_आकार)) {
                choice = i;
                गच्छ अन्तः_2;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    } अन्यथा यदि ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
            यदि ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                गच्छ अन्तः_2;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    } अन्यथा यदि (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
            यदि (वाक्ये_अन्विष(prop[i].properties.deviceName, select->name)) {
                choice = i;
                गच्छ अन्तः_2;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    } अन्यथा यदि (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
            यदि (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                गच्छ अन्तः_2;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        गच्छ अन्तः_2;
    } अन्यथा यदि (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
            यदि (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                गच्छ अन्तः_2;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    } अन्यथा {
        यदि (select->सूचकांक < अङ्कः) {
            choice = select->सूचकांक;
            गच्छ अन्तः_2;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->सूचकांक);
        err = AVERROR(ENODEV);
        गच्छ अन्तः_2;
    }

अन्तः_2:
    यदि (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_अग्र = रिक्त;
        p->dprops = driver_prop[choice];
        p->dprops.p_अग्र = रिक्त;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    प्रत्यागम err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
स्थिर अन्तःस्थ पूर्णाङ्क pick_queue_family(VkQueueFamilyProperties2 *qf, uint32_t अङ्कः_qf,
                                    Vk_Queue_Flag_द्वयङ्काः flags)
{
    पूर्णाङ्क सूचकांक = -1;
    uint32_t min_score = UINT32_MAX;

    प्रति (पूर्णाङ्क i = 0; i < अङ्कः_qf; i++) {
        Vk_Queue_Flag_द्वयङ्काः qflags = qf[i].queueFamilyProperties.queueFlags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        यदि ((flags & VK_QUEUE_TRANSFER_BIT) &&
            (qflags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            qflags |= VK_QUEUE_TRANSFER_BIT;

        यदि (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].queueFamilyProperties.timestamp_Valid_द्वयङ्काः;
            यदि (score < min_score) {
                सूचकांक = i;
                min_score = score;
            }
        }
    }

    यदि (सूचकांक > -1)
        qf[सूचकांक].queueFamilyProperties.timestamp_Valid_द्वयङ्काः++;

    प्रत्यागम सूचकांक;
}

स्थिर अन्तःस्थ पूर्णाङ्क pick_video_queue_family(VkQueueFamilyProperties2 *qf,
                                          VkQueueFamilyVideoPropertiesKHR *qf_vid, uint32_t अङ्कः_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    पूर्णाङ्क सूचकांक = -1;
    uint32_t min_score = UINT32_MAX;

    प्रति (पूर्णाङ्क i = 0; i < अङ्कः_qf; i++) {
        ध्रुव VkQueueFlags qflags = qf[i].queueFamilyProperties.queueFlags;
        ध्रुव VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        यदि (!(qflags & (VK_QUEUE_VIDEO_ENCODE_BIT_KHR | VK_QUEUE_VIDEO_DECODE_BIT_KHR)))
            अनुवर्त;

        यदि (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].queueFamilyProperties.timestamp_Valid_द्वयङ्काः;
            यदि (score < min_score) {
                सूचकांक = i;
                min_score = score;
            }
        }
    }

    यदि (सूचकांक > -1)
        qf[सूचकांक].queueFamilyProperties.timestamp_Valid_द्वयङ्काः++;

    प्रत्यागम सूचकांक;
}

स्थिर पूर्णाङ्क सज्जता_queue_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t अङ्कः;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    VkQueueFamilyProperties2 *qf = रिक्त;
    VkQueueFamilyVideoPropertiesKHR *qf_vid = रिक्त;

    /* First get the number of queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &अङ्कः, रिक्त);
    यदि (!अङ्कः) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        प्रत्यागम AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(अङ्कः, परिमाण(VkQueueFamilyProperties2));
    यदि (!qf)
        प्रत्यागम AVERROR(ENOMEM);

    qf_vid = av_malloc_array(अङ्कः, परिमाण(VkQueueFamilyVideoPropertiesKHR));
    यदि (!qf_vid)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (uint32_t i = 0; i < अङ्कः; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .p_अग्र = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : रिक्त,
        };
    }

    /* Finally retrieve the queue families */
    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &अङ्कः, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    प्रति (पूर्णाङ्क i = 0; i < अङ्कः; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_GRAPHICS_BIT) ? " graphics" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_COMPUTE_BIT) ? " compute" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_TRANSFER_BIT) ? " transfer" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) ? " encode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_VIDEO_DECODE_BIT_KHR) ? " decode" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_SPARSE_BINDING_BIT) ? " sparse" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_OPTICAL_FLOW_BIT_NV) ? " optical_flow" : "",
               ((qf[i].queueFamilyProperties.queueFlags) & VK_QUEUE_PROTECTED_BIT) ? " protected" : "",
               qf[i].queueFamilyProperties.queue_गणनम्);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].queueFamilyProperties.timestamp_Valid_द्वयङ्काः = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->queue_flags = 0;
#यदि_परिभाषितम् VK_KHR_internally_synchronized_queues
    यदि (p->vkctx.extensions & FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC)
        hwctx->queue_flags |= VK_DEVICE_QUEUE_CREATE_INTERNALLY_SYNCHRONIZED_BIT_KHR;
#यदि_अन्तः

    /* Pick each queue family to use. */
#परिभाषय PICK_QF(type, vid_op)                                            \
    कुरु {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        यदि (vid_op)                                                      \
            idx = pick_video_queue_family(qf, qf_vid, अङ्कः, vid_op);      \
        अन्यथा                                                             \
            idx = pick_queue_family(qf, अङ्कः, type);                      \
                                                                         \
        यदि (idx == -1)                                                   \
            अनुवर्त;                                                    \
                                                                         \
        प्रति (i = 0; i < hwctx->nb_qf; i++) {                             \
            यदि (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                भङ्ग;                                                   \
            }                                                            \
        }                                                                \
        यदि (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].अङ्कः = qf[idx].queueFamilyProperties.queue_गणनम्; \
            यदि (p->सीमा_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                पूर्णाङ्क max = p->सीमा_queues;                               \
                यदि (type == VK_QUEUE_GRAPHICS_BIT)                       \
                    hwctx->qf[i].अङ्कः = FFMIN(hwctx->qf[i].अङ्कः,           \
                                             max ? max : 1);             \
                अन्यथा यदि (max)                                            \
                    hwctx->qf[i].अङ्कः = FFMIN(hwctx->qf[i].अङ्कः, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } यावत् (0)

    PICK_QF(VK_QUEUE_GRAPHICS_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_COMPUTE_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_QUEUE_TRANSFER_BIT, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR);

    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR);
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR);

#यदि_परिभाषितम् VK_KHR_video_decode_vp9
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR);
#यदि_अन्तः

#यदि_परिभाषितम् VK_KHR_video_encode_av1
    PICK_QF(VK_QUEUE_VIDEO_ENCODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR);
#यदि_अन्तः
    PICK_QF(VK_QUEUE_VIDEO_DECODE_BIT_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR);

    यदि (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_QUEUE_OPTICAL_FLOW_BIT_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#अपरिभाषय PICK_QF

    cd->pQueueCreateInfos = av_malloc_array(hwctx->nb_qf,
                                            परिमाण(VkDeviceQueueCreateInfo));
    यदि (!cd->pQueueCreateInfos)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        पूर्णाङ्क dup = 0;
        भिन्न *weights = रिक्त;
        VkDeviceQueueCreateInfo *pc;
        प्रति (uint32_t j = 0; j < cd->queue_Create_Info_गणनम्; j++) {
            यदि (hwctx->qf[i].idx == cd->pQueueCreateInfos[j].queue_Family_सूचकांक) {
                dup = 1;
                भङ्ग;
            }
        }
        यदि (dup)
            अनुवर्त;

        weights = av_malloc_array(hwctx->qf[i].अङ्कः, परिमाण(भिन्न));
        यदि (!weights) {
            प्रति (uint32_t j = 0; j < cd->queue_Create_Info_गणनम्; j++)
                av_free((शून्य *)cd->pQueueCreateInfos[i].pQueuePriorities);
            av_free((शून्य *)cd->pQueueCreateInfos);
            प्रत्यागम AVERROR(ENOMEM);
        }

        प्रति (uint32_t j = 0; j < hwctx->qf[i].अङ्कः; j++)
            weights[j] = 1.0;

        pc = (VkDeviceQueueCreateInfo *)cd->pQueueCreateInfos;
        pc[cd->queue_Create_Info_गणनम्++] = (VkDeviceQueueCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .flags = hwctx->queue_flags,
            .queue_Family_सूचकांक = hwctx->qf[i].idx,
            .queue_गणनम् = hwctx->qf[i].अङ्कः,
            .pQueuePriorities = weights,
        };
    }

    प्रत्यागम 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
स्थिर शून्य vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    यदि (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    यदि (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    यदि (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    यदि (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

स्थिर शून्य vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    यदि (p->qf_mutex) {
        प्रति (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

स्थिर पूर्णाङ्क vulkan_device_create_आन्तरिकम्(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         पूर्णाङ्क disable_multiplane,
                                         AVDictionary *opts, पूर्णाङ्क flags)
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    AVDictionary_प्रविष्टिः *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    गणना FFVulkan_Debug_बहुलकम् debug_बहुलकम् = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    यदि ((err = create_instance(ctx, opts, &debug_बहुलकम्)))
        गच्छ अन्तः_2;

    /* Find a physical device (if not given one) */
    यदि ((err = find_device(ctx, dev_select)))
        गच्छ अन्तः_2;

    /* Get supported memory types */
    vk->Get_Physical_Device_स्मृतिः_Properties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    यदि ((err = check_extensions(ctx, 1, opts, &dev_info.pp_Enabled_Extension_नामानि,
                                &dev_info.enabled_Extension_गणनम्, debug_बहुलकम्))) {
        प्रति (पूर्णाङ्क i = 0; i < dev_info.queue_Create_Info_गणनम्; i++)
            av_free((शून्य *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
        av_free((शून्य *)dev_info.pQueueCreateInfos);
        गच्छ अन्तः_2;
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
    opt_d = av_dict_get(opts, "limit_queues", रिक्त, 0);
    यदि (opt_d)
        p->सीमा_queues = strtol(opt_d->मानम्, रिक्त, 10);

    /* Setup enabled queue families */
    यदि ((err = सज्जता_queue_families(ctx, &dev_info)))
        गच्छ अन्तः_2;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    प्रति (पूर्णाङ्क i = 0; i < dev_info.queue_Create_Info_गणनम्; i++)
        av_free((शून्य *)dev_info.pQueueCreateInfos[i].pQueuePriorities);
    av_free((शून्य *)dev_info.pQueueCreateInfos);

    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        प्रति (पूर्णाङ्क i = 0; i < dev_info.enabled_Extension_गणनम्; i++)
            av_free((शून्य *)dev_info.pp_Enabled_Extension_नामानि[i]);
        av_free((शून्य *)dev_info.pp_Enabled_Extension_नामानि);
        err = AVERROR_EXTERNAL;
        गच्छ अन्तः_2;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", रिक्त, 0);
    यदि (opt_d)
        p->use_रैखिकम्_images = strtol(opt_d->मानम्, रिक्त, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    यदि (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", रिक्त, 0);
        यदि (opt_d)
            p->disable_multiplane = strtol(opt_d->मानम्, रिक्त, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", रिक्त, 0);
    यदि (opt_d)
        p->avoid_host_import = strtol(opt_d->मानम्, रिक्त, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.pp_Enabled_Extension_नामानि;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_गणनम्;

    /* The extension lists need to be freed */
    ctx->मुक्त = vulkan_device_free;

अन्तः_2:
    प्रत्यागम err;
}

स्थिर शून्य तालकम्_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t सूचकांक)
{
    VulkanDevicePriv *p = ctx->hwctx;
    यदि (p->qf_mutex)
        pthread_mutex_तालकम्(&p->qf_mutex[queue_family][सूचकांक]);
}

स्थिर शून्य unlock_queue(AVHWDeviceContext *ctx, uint32_t queue_family, uint32_t सूचकांक)
{
    VulkanDevicePriv *p = ctx->hwctx;
    यदि (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[queue_family][सूचकांक]);
}

स्थिर पूर्णाङ्क vulkan_device_init(AVHWDeviceContext *ctx)
{
    पूर्णाङ्क err = 0;
    uint32_t qf_अङ्कः;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkQueueFamilyProperties2 *qf;
    VkQueueFamilyVideoPropertiesKHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    प्रति (पूर्णाङ्क i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        प्रति (पूर्णाङ्क j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            यदि (!वाक्यं_तुलय(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                भङ्ग;
            }
        }
    }

    err = ff_vk_आरोपय_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    यदि (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        प्रत्यागम err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_अग्र = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_स्मृतिः_HOST_PROPERTIES_EXT;
    p->hprops.p_अग्र = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_बफर_Copy_Row_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.min_स्मृतिः_Map_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_आकार);
    यदि (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_स्मृतिः)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.minImportedHostPointerAlignment);

    vk->GetPhysicalDeviceQueueFamilyProperties(hwctx->phys_dev, &qf_अङ्कः, रिक्त);
    यदि (!qf_अङ्कः) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        प्रत्यागम AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#यदि_परिभाषितम् _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT;
#अन्यथा
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;
#यदि_अन्तः
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_अङ्कः, परिमाण(VkQueueFamilyProperties2));
    यदि (!qf)
        प्रत्यागम AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_अङ्कः, परिमाण(VkQueueFamilyVideoPropertiesKHR));
    यदि (!qf_vid) {
        av_free(qf);
        प्रत्यागम AVERROR(ENOMEM);
    }

    प्रति (uint32_t i = 0; i < qf_अङ्कः; i++) {
        qf_vid[i] = (VkQueueFamilyVideoPropertiesKHR) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (VkQueueFamilyProperties2) {
            .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2,
            .p_अग्र = p->vkctx.extensions & FF_VK_EXT_VIDEO_QUEUE ? &qf_vid[i] : रिक्त,
        };
    }

    vk->GetPhysicalDeviceQueueFamilyProperties2(hwctx->phys_dev, &qf_अङ्कः, qf);

    p->nb_tot_qfs = qf_अङ्कः;

    यदि (!(p->vkctx.extensions & FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC)) {
        p->qf_mutex = av_calloc(qf_अङ्कः, परिमाण(*p->qf_mutex));
        यदि (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            गच्छ अन्तः_2;
        }

        प्रति (uint32_t i = 0; i < qf_अङ्कः; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].queueFamilyProperties.queue_गणनम्,
                                       परिमाण(**p->qf_mutex));
            यदि (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                गच्छ अन्तः_2;
            }
            प्रति (uint32_t j = 0; j < qf[i].queueFamilyProperties.queue_गणनम्; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], रिक्त);
                यदि (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    गच्छ अन्तः_2;
                }
            }
        }
    }

    प्रति (पूर्णाङ्क i = 0; i < hwctx->nb_qf; i++) {
        यदि (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                  VK_QUEUE_VIDEO_ENCODE_BIT_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    प्रति (पूर्णाङ्क i = 0; i < hwctx->nb_qf; i++) {
        पूर्णाङ्क आलोकितम् = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        प्रति (पूर्णाङ्क j = (i - 1); j >= 0; j--) {
            यदि (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                आलोकितम् = 1;
                भङ्ग;
            }
        }
        यदि (!आलोकितम्)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#यदि FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    यदि (!hwctx->तालकम्_queue)
        hwctx->तालकम्_queue = तालकम्_queue;
    यदि (!hwctx->unlock_queue)
        hwctx->unlock_queue = unlock_queue;
FF_ENABLE_DEPRECATION_WARNINGS
#यदि_अन्तः

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_स्मृतिः_Properties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_आरोपय_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_COMPUTE_BIT, 0);
    p->transfer_qf = ff_vk_qf_find(&p->vkctx, VK_QUEUE_TRANSFER_BIT, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_विस्थापनम्_align = 1;
    यदि (p->transfer_qf) {
        VkQueueFlags flags = p->vkctx.qf_props[p->transfer_qf->idx].queueFamilyProperties.queueFlags;
        यदि (!(flags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)))
            p->transfer_विस्थापनम्_align = 4;
    }
#यदि_परिभाषितम् VK_KHR_maintenance11
    यदि (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_विस्थापनम्_align = 1;
#यदि_अन्तः

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_स्मृतिः_Properties(hwctx->phys_dev, &p->mprops);

अन्तः_2:
    av_free(qf_vid);
    av_free(qf);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vulkan_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                                AVDictionary *opts, पूर्णाङ्क flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    यदि (device && device[0]) {
        वर्ण *अन्तः_2 = रिक्त;

        यदि (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } अन्यथा {
            dev_select.सूचकांक = strtol(device, &अन्तः_2, 10);
            यदि (अन्तः_2 == device || *अन्तः_2) {
                dev_select.सूचकांक = 0;
                dev_select.name  = device;
            }
        }
    }

    प्रत्यागम vulkan_device_create_आन्तरिकम्(ctx, &dev_select, 0, opts, flags);
}

स्थिर पूर्णाङ्क vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, पूर्णाङ्क flags)
{
    av_अप्रयुक्तम् VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    विकल्प(src_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#यदि VA_CHECK_संस्करणम्(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#यदि_अन्तः
        ध्रुव वर्ण *vendor;

#यदि VA_CHECK_संस्करणम्(1, 15, 0)
        vas = va_Get_Display_गुणाः(dpy, &attr, 1);
        यदि (vas == VA_स्थितिः_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.मानम् & 0xFFFF);
#यदि_अन्तः

        यदि (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            यदि (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                प्रत्यागम AVERROR_EXTERNAL;
            }

            यदि (वाक्ये_अन्विष(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        प्रत्यागम vulkan_device_create_आन्तरिकम्(ctx, &dev_select, 0, opts, flags);
    }
#यदि_अन्तः
#यदि CONFIG_LIBDRM
    पक्ष AV_HWDEVICE_TYPE_DRM: {
        पूर्णाङ्क err;
        संरचना stat drm_ग्रन्थिः_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_ग्रन्थिः_info);
        यदि (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            प्रत्यागम AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_ग्रन्थिः_info.st_dev);
        dev_select.drm_minor = minor(drm_ग्रन्थिः_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        यदि (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            प्रत्यागम AVERROR_EXTERNAL;
        }

        यदि (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        प्रत्यागम vulkan_device_create_आन्तरिकम्(ctx, &dev_select, 0, opts, flags);
    }
#यदि_अन्तः
#यदि CONFIG_CUDA
    पक्ष AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADevice_Context_आन्तरिकम् *cu_आन्तरिकम् = src_hwctx->आन्तरिकम्;
        CudaFunctions *cu = cu_आन्तरिकम्->cuda_dl;

        पूर्णाङ्क ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_आन्तरिकम्->cuda_device));
        यदि (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            प्रत्यागम AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        प्रत्यागम vulkan_device_create_आन्तरिकम्(ctx, &dev_select, 1, opts, flags);
    }
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }
}

स्थिर पूर्णाङ्क vulkan_चौकटाः_get_constraints(AVHWDeviceContext *ctx,
                                         ध्रुव शून्य *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क गणनम् = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    प्रति (गणना AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        गणनम् += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_रैखिकम्_images ? VK_IMAGE_TILING_रैखिकम् :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    रिक्त, रिक्त, रिक्त, रिक्त, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(गणनम् + 1 + CONFIG_CUDA,
                                                    परिमाण(गणना AVPixelFormat));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    गणनम् = 0;
    प्रति (गणना AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        यदि (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_रैखिकम्_images ? VK_IMAGE_TILING_रैखिकम् :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               रिक्त, रिक्त, रिक्त, रिक्त, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[गणनम्++] = vk_formats_list[i].pixfmt;
        }
    }

#यदि CONFIG_CUDA
    constraints->valid_sw_formats[गणनम्++] = AV_PIX_FMT_CUDA;
#यदि_अन्तः

    constraints->valid_sw_formats[गणनम्++] = AV_PIX_FMT_NONE;

    constraints->min_विस्तारः  = 1;
    constraints->min_height = 1;
    constraints->max_विस्तारः  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_height = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(गणना AVPixelFormat));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क alloc_mem(AVHWDeviceContext *ctx, Vk_स्मृतिः_Requirements *req,
                     Vk_स्मृतिः_Property_Flag_द्वयङ्काः req_flags, ध्रुव शून्य *alloc_extension,
                     Vk_स्मृतिः_Property_Flag_द्वयङ्काः *mem_flags, Vk_Device_स्मृतिः *mem)
{
    Vk_परिणाम ret;
    पूर्णाङ्क सूचकांक = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    Vk_स्मृतिः_Allocate_Info alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_स्मृतिः_ALLOCATE_INFO,
        .p_अग्र          = alloc_extension,
        .आवण्टनम्_आकार = req->आकार,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    प्रति (पूर्णाङ्क i = 0; i < p->mprops.स्मृतिः_Type_गणनम्; i++) {
        ध्रुव Vk_स्मृतिः_Type *type = &p->mprops.स्मृतिः_Types[i];

        /* The memory type must be supported by the requirements (bitfield) */
        यदि (!(req->स्मृतिः_Type_द्वयङ्काः & (1 << i)))
            अनुवर्त;

        /* The memory type flags must include our properties */
        यदि ((type->propertyFlags & req_flags) != req_flags)
            अनुवर्त;

        /* The memory type must be large enough */
        यदि (req->आकार > p->mprops.स्मृतिः_Heaps[type->heap_सूचकांक].आकार)
            अनुवर्त;

        /* Found a suitable memory type */
        सूचकांक = i;
        भङ्ग;
    }

    यदि (सूचकांक < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        प्रत्यागम AVERROR(EINVAL);
    }

    alloc_info.स्मृतिः_Type_सूचकांक = सूचकांक;

    ret = vk->Allocate_स्मृतिः(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.स्मृतिः_Types[सूचकांक].propertyFlags;

    प्रत्यागम 0;
}

स्थिर शून्य vulkan_free_आन्तरिकम्(VulkanDevicePriv *p, AVVkFrame *f)
{
    av_अप्रयुक्तम् AVVk_Frame_आन्तरिकम् *आन्तरिकम् = f->आन्तरिकम्;

    // Make this function safe to call repeatedly
    यदि (!आन्तरिकम्)
        प्रत्यागम;

#यदि CONFIG_CUDA
    यदि (आन्तरिकम्->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)आन्तरिकम्->cuda_fc_ref->दत्त;
        पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADevice_Context_आन्तरिकम् *cu_आन्तरिकम् = cuda_dev->आन्तरिकम्;
        CudaFunctions *cu = cu_आन्तरिकम्->cuda_dl;

        प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
            यदि (आन्तरिकम्->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(आन्तरिकम्->cu_sem[i]));
            यदि (आन्तरिकम्->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(आन्तरिकम्->cu_mma[i]));
            यदि (आन्तरिकम्->ext_mem[i])
                CHECK_CU(cu->cu_Destroy_External_स्मृतिः(आन्तरिकम्->ext_mem[i]));
#यदि_परिभाषितम् _WIN32
            यदि (आन्तरिकम्->ext_sem_handle[i])
                CloseHandle(आन्तरिकम्->ext_sem_handle[i]);
            यदि (आन्तरिकम्->ext_mem_handle[i])
                CloseHandle(आन्तरिकम्->ext_mem_handle[i]);
#यदि_अन्तः
        }

        av_बफर_unref(&आन्तरिकम्->cuda_fc_ref);
    }
#यदि_अन्तः

    यदि (आन्तरिकम्->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, आन्तरिकम्->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&आन्तरिकम्->update_mutex);
    av_freep(&f->आन्तरिकम्);
}

स्थिर शून्य vulkan_frame_free(AVHWFramesContext *hwfc, AVVkFrame *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णाङ्क nb_images = ff_vk_गणनम्_images(f);
    पूर्णाङ्क nb_sems = 0;

    यावत् (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    यदि (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_मानानि        = f->sem_मानम्,
            .semaphore_गणनम् = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_आन्तरिकम्(p, f);

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->Free_स्मृतिः(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

स्थिर शून्य vulkan_frame_free_cb(शून्य *opaque, uint8_t *दत्त)
{
    vulkan_frame_free(opaque, (AVVkFrame*)दत्त);
}

स्थिर पूर्णाङ्क alloc_bind_mem(AVHWFramesContext *hwfc, AVVkFrame *f,
                          शून्य *alloc_pnext, size_t alloc_pnext_stride)
{
    पूर्णाङ्क img_cnt = 0, err;
    Vk_परिणाम ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Bind_Image_स्मृतिः_Info bind_info[AV_अङ्कः_दत्त_सूचकाः] = { { 0 } };

    यावत् (f->img[img_cnt]) {
        पूर्णाङ्क use_ded_mem;
        Vk_Image_स्मृतिः_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_स्मृतिः_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        Vk_स्मृतिः_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_ALLOCATE_INFO,
            .p_अग्र = (शून्य *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        Vk_स्मृतिः_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_REQUIREMENTS,
        };
        Vk_स्मृतिः_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_REQUIREMENTS_2,
            .p_अग्र = &ded_req,
        };

        vk->Get_Image_स्मृतिः_Requirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefers_Dedicated_आवण्टनम्, ded_req.requires_Dedicated_आवण्टनम्);

        यदि (f->tiling == VK_IMAGE_TILING_रैखिकम्)
            req.स्मृतिः_Requirements.आकार = FFALIGN(req.स्मृतिः_Requirements.आकार,
                                                  p->props.properties.limits.min_स्मृतिः_Map_Alignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefers_Dedicated_आवण्टनम् |
                      ded_req.requires_Dedicated_आवण्टनम्;
        यदि (((Vulkan_चौकटाः_Priv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        यदि (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        यदि ((err = alloc_mem(ctx, &req.स्मृतिः_Requirements,
                             f->tiling == VK_IMAGE_TILING_रैखिकम् ?
                             VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT :
                             VK_स्मृतिः_PROPERTY_DEVICE_LOCAL_BIT,
                             use_ded_mem ? &ded_alloc : (शून्य *)ded_alloc.p_अग्र,
                             &f->flags, &f->mem[img_cnt])))
            प्रत्यागम err;

        f->आकार[img_cnt] = req.स्मृतिः_Requirements.आकार;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_स्मृतिः_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].स्मृतिः = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

गणना Prep_बहुलकम् {
    PREP_बहुलकम्_GENERAL,
    PREP_बहुलकम्_WRITE,
    PREP_बहुलकम्_EXTERNAL_EXPORT,
    PREP_बहुलकम्_EXTERNAL_IMPORT,
    PREP_बहुलकम्_DECODING_DST,
    PREP_बहुलकम्_DECODING_DPB,
    PREP_बहुलकम्_ENCODING_DPB,
};

स्थिर शून्य switch_new_props(गणना Prep_बहुलकम् pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    विकल्प (pmode) {
    पक्ष PREP_बहुलकम्_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_स्मृतिः_READ_BIT | VK_ACCESS_स्मृतिः_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_स्मृतिः_READ_BIT | VK_ACCESS_स्मृतिः_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        भङ्ग;
    पक्ष PREP_बहुलकम्_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        भङ्ग;
    }
}

स्थिर पूर्णाङ्क switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, गणना Prep_बहुलकम् pmode)
{
    पूर्णाङ्क err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Image_स्मृतिः_Barrier2 img_bar[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    यदि (pmode == PREP_बहुलकम्_EXTERNAL_EXPORT) {
        dst_qf     = VK_QUEUE_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .दत्त = (uint8_t *)hwfc,
    };
    AVFrame tmp_frame = {
        .दत्त[0] = (uint8_t *)frame,
        .hw_चौकटाः_ctx = &tmp_ref,
    };

    Vk_Command_बफर cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_start(&p->vkctx, exec);
    यदि (err < 0)
        प्रत्यागम err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_सङ्कलय_dep_frame(&p->vkctx, exec, &tmp_frame,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
    यदि (err < 0)
        प्रत्यागम err;

    ff_vk_frame_barrier(&p->vkctx, exec, &tmp_frame, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_स्मृतिः_Barriers = img_bar,
            .image_स्मृतिः_Barrier_गणनम् = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    यदि (err < 0)
        प्रत्यागम err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVkFrame *frame, गणना Prep_बहुलकम् pmode)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क nb_images = ff_vk_गणनम्_images(frame);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    पूर्णाङ्क i;
    प्रति (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_गणनम्; i++) {
        यदि (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            भङ्ग;
    }
    यदि (i == p->vkctx.host_image_props.copy_Dst_Layout_गणनम्)
        प्रत्यागम AVERROR(ENOTSUP);

    प्रति (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = frame->img[i],
            .oldLayout = frame->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspect_आवरणम् = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.layer_गणनम् = 1,
            .subresourceRange.level_गणनम् = 1,
        };
        frame->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    यदि (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क prepare_frame(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVkFrame *frame, गणना Prep_बहुलकम् pmode)
{
    पूर्णाङ्क err = 0;
    AVVulkan_चौकटाः_Context *hwfc_vk = hwfc->hwctx;
    यदि (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT &&
        (pmode != PREP_बहुलकम्_EXTERNAL_EXPORT) &&
        (pmode != PREP_बहुलकम्_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, frame, pmode);
        यदि (err != AVERROR(ENOTSUP))
            प्रत्यागम err;
    }

    प्रत्यागम switch_layout(hwfc, ectx, frame, pmode);
}

स्थिर अन्तःस्थ शून्य get_plane_wh(uint32_t *w, uint32_t *h, गणना AVPixelFormat format,
                                पूर्णाङ्क frame_w, पूर्णाङ्क frame_h, पूर्णाङ्क plane)
{
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    यदि (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = frame_w;
        *h = frame_h;
        प्रत्यागम;
    }

    *w = AV_CEIL_RSHIFT(frame_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(frame_h, desc->log2_chroma_h);
}

स्थिर पूर्णाङ्क create_frame(AVHWFramesContext *hwfc, AVVkFrame **frame,
                        VkImageTiling tiling, Vk_Image_Usage_Flag_द्वयङ्काः usage,
                        VkImageCreateFlags flags, पूर्णाङ्क nb_layers,
                        शून्य *create_pnext)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    AVVulkan_चौकटाः_Context *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVkFrame *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_मानम्  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_अग्र = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#यदि_परिभाषितम् _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
#अन्यथा
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT,
#यदि_अन्तः
    };

    /* Check if exporting is supported before chaining any structs */
    यदि (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT) {
        यदि (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_frame_alloc();
    यदि (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        प्रत्यागम AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    प्रति (पूर्णाङ्क i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.गभीरता          = 1,
            .mip_स्तराः             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_गणनम्_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गणनम् = p->nb_img_qfs,
            .sharing_बहुलकम्           = p->nb_img_qfs > 1 ? VK_SHARING_बहुलकम्_CONCURRENT :
                                                         VK_SHARING_बहुलकम्_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.विस्तारः, &create_info.extent.height,
                     hwfc->sw_format, hwfc->विस्तारः, hwfc->height, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            गच्छ fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }

        f->queue_family[i] = p->nb_img_qfs > 1 ? VK_QUEUE_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_मानम्[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *frame = f;
    प्रत्यागम 0;

fail:
    vulkan_frame_free(hwfc, f);
    प्रत्यागम err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
स्थिर शून्य try_export_flags(AVHWFramesContext *hwfc,
                             Vk_External_स्मृतिः_Handle_Type_Flags *comp_handle_types,
                             Vk_External_स्मृतिः_Handle_Type_Flags *iexp,
                             Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः घातांकः)
{
    Vk_परिणाम ret;
    AVVulkan_चौकटाः_Context *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ध्रुव VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    पूर्णाङ्क has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    पूर्णाङ्क nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_अग्र = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_अग्र = रिक्त,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_सूचकांक_गणनम् = p->nb_img_qfs,
        .sharing_बहुलकम्           = p->nb_img_qfs > 1 ? VK_SHARING_बहुलकम्_CONCURRENT :
                                                     VK_SHARING_बहुलकम्_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = घातांकः,
        .p_अग्र = has_mods ? &phy_dev_mod_info : रिक्त,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_अग्र  = !घातांकः ? रिक्त : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_BIT),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_गणनम् : 1;
    प्रति (पूर्णाङ्क i = 0; i < nb_mods; i++) {
        यदि (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        यदि (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (अचिह्नित दीर्घ दीर्घ)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        यदि (ret == VK_SUCCESS) {
            *iexp |= घातांकः;
            *comp_handle_types |= eprops.external_स्मृतिः_Properties.compatibleHandleTypes;
            यदि (घातांकः == VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT) {
                Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.external_स्मृतिः_Properties.external_स्मृतिः_Features &
                                                  VK_EXTERNAL_स्मृतिः_FEATURE_DEDICATED_ONLY_BIT);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
स्थिर शून्य get_export_handle_types(AVHWFramesContext *hwfc,
                                    Vk_External_स्मृतिः_Handle_Type_Flags *comp_handle_types,
                                    Vk_External_स्मृतिः_Handle_Type_Flags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_अप्रयुक्तम् AVVulkan_चौकटाः_Context *hwctx = &((Vulkan_चौकटाः_Priv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#यदि_परिभाषितम् _WIN32
    यदि (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32_BIT
                             : VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT);
#अन्यथा
    यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_स्मृतिः) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_FD_BIT);

    यदि (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_स्मृतिः &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT);
#यदि_अन्तः
}

स्थिर AVBufferRef *vulkan_pool_alloc(शून्य *opaque, size_t आकार)
{
    पूर्णाङ्क err;
    AVVkFrame *f;
    AVBufferRef *avbuf = रिक्त;
    AVHWFramesContext *hwfc = opaque;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkan_चौकटाः_Context *hwctx = &fp->p;
    Vk_External_स्मृतिः_Handle_Type_Flags e;
    Vk_Export_स्मृतिः_Allocate_Info eminfo[AV_अङ्कः_दत्त_सूचकाः];

    Vk_External_स्मृतिः_Image_Create_Info eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_स्मृतिः_IMAGE_CREATE_INFO,
        .p_अग्र       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    प्रति (पूर्णाङ्क i = 0; i < av_pix_fmt_गणनम्_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_स्मृतिः_ALLOCATE_INFO;
        eminfo[i].p_अग्र       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    यदि (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        प्रत्यागम रिक्त;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, परिमाण(*eminfo));
    यदि (err)
        गच्छ fail;

    यदि ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR))
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_DECODING_DPB);
    अन्यथा यदि (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_DECODING_DST);
    अन्यथा यदि (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_ENCODING_DPB);
    अन्यथा यदि (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_WRITE);
    अन्यथा
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_GENERAL);
    यदि (err)
        गच्छ fail;

    avbuf = av_बफर_create((uint8_t *)f, परिमाण(AVVkFrame),
                             vulkan_frame_free_cb, hwfc, 0);
    यदि (!avbuf)
        गच्छ fail;

    प्रत्यागम avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_frame_free(hwfc, f);
    प्रत्यागम रिक्त;
}

स्थिर शून्य तालकम्_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_तालकम्(&vkf->आन्तरिकम्->update_mutex);
}

स्थिर शून्य unlock_frame(AVHWFramesContext *fc, AVVkFrame *vkf)
{
    pthread_mutex_unlock(&vkf->आन्तरिकम्->update_mutex);
}

स्थिर शून्य vulkan_चौकटाः_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;

    यदि (fp->modifier_info) {
        यदि (fp->modifier_info->pDrmFormatModifiers)
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
स्थिर पूर्णाङ्क vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkan_चौकटाः_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_परिणाम ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    ध्रुव संरचना FFVk_Format_प्रविष्टिः *fmt = vk_find_format_प्रविष्टिः(hwfc->sw_format);
    यदि (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        प्रत्यागम 0;
    }

    ध्रुव VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    पूर्णाङ्क has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_गणनम्;
    पूर्णाङ्क nb_mods = has_mods ? mod_list->drm_Format_Modifier_गणनम् : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    यदि (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        प्रत्यागम 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .pQueueFamilyIndices   = p->img_qfs,
        .queue_Family_सूचकांक_गणनम् = p->nb_img_qfs,
        .sharing_बहुलकम्           = p->nb_img_qfs > 1 ? VK_SHARING_बहुलकम्_CONCURRENT :
                                                     VK_SHARING_बहुलकम्_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    यदि (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    ध्रुव VkVideoProfileListInfoKHR *pl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    यदि (pl) {
        profile_list = *pl;
        profile_list.p_अग्र = रिक्त;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    ध्रुव VkImageFormatListCreateInfo *fl =
        ff_vk_find_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    यदि (fl) {
        format_list = *fl;
        format_list.p_अग्र = रिक्त;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    प्रति (पूर्णाङ्क i = 0; i < AV_अङ्कः_दत्त_सूचकाः &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        प्रति (पूर्णाङ्क j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_अग्र = &perf,
            };

            यदि (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            यदि (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                प्रत्यागम 0;
            }

            यदि (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identical_स्मृतिः_Layout);
                प्रत्यागम 0;
            }
        }
    }

    यदि (!p->vkctx.host_image_props.identical_स्मृतिः_Type_Requirements) {
        पूर्णाङ्क सूचकांक;
        Vk_External_स्मृतिः_Handle_Type_Flags e;
        Vk_External_स्मृतिः_Image_Create_Info eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_स्मृतिः_IMAGE_CREATE_INFO,
            .p_अग्र       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->विस्तारः, hwfc->height, 1 },
            .mip_स्तराः   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_गणनम्_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गणनम् = p->nb_img_qfs,
            .sharing_बहुलकम्           = p->nb_img_qfs > 1 ? VK_SHARING_बहुलकम्_CONCURRENT :
                                                         VK_SHARING_बहुलकम्_EXCLUSIVE,
        };
        Vk_Device_Image_स्मृतिः_Requirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_स्मृतिः_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_स्मृतिः_PLANE_0_BIT_EXT : 0,
        };
        Vk_स्मृतिः_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_REQUIREMENTS_2,
        };

        vk->Get_Device_Image_स्मृतिः_Requirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        Vk_स्मृतिः_Property_Flags req_flags = hwctx->tiling == VK_IMAGE_TILING_रैखिकम् ?
                                          VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT :
                                          VK_स्मृतिः_PROPERTY_DEVICE_LOCAL_BIT;
        प्रति (सूचकांक = 0; सूचकांक < p->mprops.स्मृतिः_Type_गणनम्; सूचकांक++) {
            यदि (!(req.स्मृतिः_Requirements.स्मृतिः_Type_द्वयङ्काः & (1U << सूचकांक)))
                अनुवर्त;
            यदि ((p->mprops.स्मृतिः_Types[सूचकांक].propertyFlags & req_flags) == req_flags)
                भङ्ग;
        }
        यदि (सूचकांक == p->mprops.स्मृतिः_Type_गणनम्) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            प्रत्यागम 0;
        }
    }

    प्रत्यागम 1;
}

स्थिर पूर्णाङ्क vulkan_चौकटाः_init(AVHWFramesContext *hwfc)
{
    पूर्णाङ्क err;
    AVVkFrame *f;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkan_चौकटाः_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ध्रुव संरचना FFVk_Format_प्रविष्टिः *fmt;
    ध्रुव AVPixFmtDescriptor *desc;
    पूर्णाङ्क disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_FRAME_FLAG_DISABLE_MULTIPLANE);
    पूर्णाङ्क is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)));

    /* Defaults */
    यदि (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    यदि (p->use_रैखिकम्_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_रैखिकम्;


    fmt = vk_find_format_प्रविष्टिः(hwfc->sw_format);
    यदि (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        प्रत्यागम AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    यदि ((hwfc->विस्तारः  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->height & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    यदि (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        यदि (hwctx->format[0] != fmt->vkf) {
            प्रति (पूर्णाङ्क i = 0; i < fmt->nb_images_fallback; i++) {
                यदि (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    प्रत्यागम AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, रिक्त,
                                 रिक्त, रिक्त, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        यदि (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            प्रत्यागम AVERROR(EINVAL);
        }
    } अन्यथा {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, रिक्त,
                                 रिक्त, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_BIT));
        यदि (err < 0)
            प्रत्यागम err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    पूर्णाङ्क drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_find_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    यदि (!is_lone_dpb && !drm_mod_with_video) {
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
        यदि (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        यदि ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        यदि (!hwctx->img_flags) {
            पूर्णाङ्क sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_BIT |
                                             VK_IMAGE_USAGE_STORAGE_BIT);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
            यदि (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_BIT;
                यदि ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_BIT;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    यदि ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_QUEUE) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        ध्रुव VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_find_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        यदि (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        } अन्यथा {
            uint32_t i;
            प्रति (i = 0; i < pl->profile_गणनम्; i++) {
                /* Video ops start at exactly 0x00010000 */
                यदि (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    भङ्ग;
            }
            यदि (i == pl->profile_गणनम्)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    यदि ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;

    यदि (!hwctx->तालकम्_frame)
        hwctx->तालकम्_frame = तालकम्_frame;

    यदि (!hwctx->unlock_frame)
        hwctx->unlock_frame = unlock_frame;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, रिक्त);
    यदि (err)
        प्रत्यागम err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, रिक्त);
    यदि (err)
        प्रत्यागम err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, रिक्त);
    यदि (err)
        प्रत्यागम err;

    /* Test to see if allocation will fail */
    err = create_frame(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    यदि (err)
        प्रत्यागम err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    यदि (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        यदि (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_frame_free(hwfc, f);
            प्रत्यागम AVERROR_EXTERNAL;
        }
        प्रति (पूर्णाङ्क i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = रिक्त;

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
                av_calloc(modp.drm_Format_Modifier_गणनम्, परिमाण(*modp.pDrmFormatModifierProperties));
            यदि (!modp.pDrmFormatModifierProperties) {
                vulkan_frame_free(hwfc, f);
                प्रत्यागम AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            प्रति (uint32_t j = 0; j < modp.drm_Format_Modifier_गणनम्; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                यदि (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    भङ्ग;
                }
            }

            यदि (mod_props == रिक्त) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_frame_free(hwfc, f);
                प्रत्यागम AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_frame_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    यदि (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_आन्तरिकम् = av_बफर_pool_init2(परिमाण(AVVkFrame),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  रिक्त);
        यदि (!ffhwframesctx(hwfc)->pool_आन्तरिकम्)
            प्रत्यागम AVERROR(ENOMEM);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vulkan_get_बफर(AVHWFramesContext *hwfc, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(hwfc->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->दत्त[0] = frame->buf[0]->दत्त;
    frame->format  = AV_PIX_FMT_VULKAN;
    frame->विस्तारः   = hwfc->विस्तारः;
    frame->height  = hwfc->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       गणना AVHWFrameTransferDirection dir,
                                       गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;
    पूर्णाङ्क n = 2;

#यदि CONFIG_CUDA
    n++;
#यदि_अन्तः
    fmts = av_malloc_array(n, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#यदि CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#यदि_अन्तः
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    प्रत्यागम 0;
}

#यदि CONFIG_LIBDRM
स्थिर शून्य vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_frame_free(hwfc, hwmap->priv);
}

स्थिर ध्रुव संरचना {
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
#यदि_परिभाषितम् DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#यदि_अन्तः
};

स्थिर अन्तःस्थ VkFormat drm_गन्तव्यम्_vulkan_fmt(uint32_t drm_fourcc)
{
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        यदि (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            प्रत्यागम vulkan_drm_format_map[i].vk_format;
    प्रत्यागम VK_FORMAT_UNDEFINED;
}

स्थिर पूर्णाङ्क vulkan_map_from_drm_frame_desc(AVHWFramesContext *hwfc, AVVkFrame **frame,
                                          ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    AVVkFrame *f;
    पूर्णाङ्क bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    ध्रुव AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->दत्त[0];
    Vk_Bind_Image_स्मृतिः_Info bind_info[AV_DRM_MAX_PLANES];
    Vk_Bind_Image_Plane_स्मृतिः_Info plane_info[AV_DRM_MAX_PLANES];

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_layers; i++) {
        यदि (drm_गन्तव्यम्_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            प्रत्यागम AVERROR(EINVAL);
        }
    }

    यदि (!(f = av_vk_frame_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_layers; i++) {
        ध्रुव पूर्णाङ्क planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_मानम्  = 0,
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
            .drm_Format_Modifier_Plane_गणनम् = planes,
            .pPlaneLayouts = (ध्रुव VkSubresourceLayout *)&ext_img_layouts,
        };
        Vk_External_स्मृतिः_Image_Create_Info ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_स्मृतिः_IMAGE_CREATE_INFO,
            .p_अग्र       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_अग्र                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_गन्तव्यम्_vulkan_fmt(desc->layers[i].format),
            .extent.गभीरता          = 1,
            .mip_स्तराः             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_गणनम्_1_BIT,
            .pQueueFamilyIndices   = p->img_qfs,
            .queue_Family_सूचकांक_गणनम् = p->nb_img_qfs,
            .sharing_बहुलकम्           = p->nb_img_qfs > 1 ? VK_SHARING_बहुलकम्_CONCURRENT :
                                                         VK_SHARING_बहुलकम्_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        यदि (planes == 1) {
            ध्रुव VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            यदि (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
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
            .queue_Family_सूचकांक_गणनम् = create_info.queue_Family_सूचकांक_गणनम्,
            .sharing_बहुलकम् = create_info.sharing_बहुलकम्,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_अग्र = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        यदि (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_BIT |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        यदि (flags & AV_HWFRAME_MAP_WRITE)
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
        यदि (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.विस्तारः, &create_info.extent.height,
                     hwfc->sw_format, src->विस्तारः, src->height, i);

        /* Set the subresource layout based on the layer properties */
        प्रति (पूर्णाङ्क j = 0; j < planes; j++) {
            ext_img_layouts[j].विस्थापनम्     = desc->layers[i].planes[j].विस्थापनम्;
            ext_img_layouts[j].rowPitch   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].आकार       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].गभीरता_Pitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            गच्छ fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        यदि (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            गच्छ fail;
        }

        f->queue_family[i] = VK_QUEUE_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_मानम्[i] = 0;
    }

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        Vk_Image_स्मृतिः_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_स्मृतिः_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        Vk_स्मृतिः_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_REQUIREMENTS,
        };
        Vk_स्मृतिः_Requirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_REQUIREMENTS_2,
            .p_अग्र = &ded_req,
        };

        /* Allocation/importing */
        Vk_स्मृतिः_Fd_Properties_KHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        Vk_Import_स्मृतिः_Fd_Info_KHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_स्मृतिः_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_सूचकांक].fd),
            .handleType = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };
        Vk_स्मृतिः_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_DEDICATED_ALLOCATE_INFO,
            .p_अग्र = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->Get_स्मृतिः_Fd_Properties_KHR(hwctx->act_dev,
                                           VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT,
                                           idesc.fd, &fdmp);
        यदि (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            गच्छ fail;
        }

        vk->Get_Image_स्मृतिः_Requirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.स्मृतिः_Requirements.स्मृतिः_Type_द्वयङ्काः = fdmp.स्मृतिः_Type_द्वयङ्काः;

        err = alloc_mem(ctx, &req2.स्मृतिः_Requirements,
                        VK_स्मृतिः_PROPERTY_DEVICE_LOCAL_BIT,
                        (ded_req.prefers_Dedicated_आवण्टनम् ||
                         ded_req.requires_Dedicated_आवण्टनम्) ?
                            &ded_alloc : ded_alloc.p_अग्र,
                        &f->flags, &f->mem[i]);
        यदि (err) {
            close(idesc.fd);
            गच्छ fail;
        }

        f->आकार[i] = req2.स्मृतिः_Requirements.आकार;
    }

    प्रति (पूर्णाङ्क i = 0; i < desc->nb_layers; i++) {
        ध्रुव पूर्णाङ्क planes = desc->layers[i].nb_planes;
        प्रति (पूर्णाङ्क j = 0; j < planes; j++) {
            Vk_Image_Aspect_Flag_द्वयङ्काः aspect = j == 0 ? VK_IMAGE_ASPECT_स्मृतिः_PLANE_0_BIT_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_स्मृतिः_PLANE_1_BIT_EXT :
                                                    VK_IMAGE_ASPECT_स्मृतिः_PLANE_2_BIT_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_स्मृतिः_INFO;
            plane_info[bind_counts].p_अग्र = रिक्त;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_स्मृतिः_INFO;
            bind_info[bind_counts].p_अग्र  = planes > 1 ? &plane_info[bind_counts] : रिक्त;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].स्मृतिः = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].स्मृतिः_विस्थापनम् = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        गच्छ fail;
    }

    *frame = f;

    प्रत्यागम 0;

fail:
    vulkan_frame_free(hwfc, f);

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vulkan_map_from_drm_frame_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          ध्रुव AVDRMFrameDescriptor *desc, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#यदि_परिभाषितम् DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    यदि (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_बफर cmd_buf;
        FFVkExecContext *exec;
        Vk_Image_स्मृतिः_Barrier2 img_bar[AV_अङ्कः_दत्त_सूचकाः];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        पूर्णाङ्क nb_img_bar = 0;

        प्रति (पूर्णाङ्क i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_द्विमान,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_अग्र = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            संरचना dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            यदि (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                प्रति (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                प्रत्यागम err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            यदि (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                प्रति (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                प्रत्यागम err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_BIT,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            यदि (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                प्रति (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                प्रत्यागम err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_start(&p->vkctx, exec);
        यदि (err < 0) {
            प्रति (पूर्णाङ्क i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            प्रत्यागम err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_सङ्कलय_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_सङ्कलय_dep_frame(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        यदि (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            प्रत्यागम err;
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
                .p_Image_स्मृतिः_Barriers = img_bar,
                .image_स्मृतिः_Barrier_गणनम् = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        यदि (err < 0)
            प्रत्यागम err;
    } अन्यथा
#यदि_अन्तः
    {
        AVVkFrame *f = (AVVkFrame *)dst->दत्त[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_EXTERNAL_IMPORT);
        यदि (err)
            प्रत्यागम err;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err = 0;
    AVVkFrame *f;
    ध्रुव AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->दत्त[0];

    यदि ((err = vulkan_map_from_drm_frame_desc(hwfc, &f, src, flags)))
        प्रत्यागम err;

    /* The unmapping function will free this */
    dst->दत्त[0] = (uint8_t *)f;
    dst->विस्तारः   = src->विस्तारः;
    dst->height  = src->height;

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    यदि (err < 0)
        गच्छ fail;

    err = vulkan_map_from_drm_frame_sync(hwfc, dst, desc, flags);
    यदि (err < 0)
        प्रत्यागम err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    प्रत्यागम 0;

fail:
    vulkan_frame_free(hwfc->device_ctx->hwctx, f);
    dst->दत्त[0] = रिक्त;
    प्रत्यागम err;
}

#यदि CONFIG_VAAPI
स्थिर पूर्णाङ्क vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, ध्रुव AVFrame *src,
                                 पूर्णाङ्क flags)
{
    पूर्णाङ्क err;
    AVFrame *tmp = av_frame_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->दत्त[3];

    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_अविभाज्यः;

    err = av_hwframe_map(tmp, src, flags);
    यदि (err < 0)
        गच्छ fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    यदि (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    प्रत्यागम err;
}
#यदि_अन्तः
#यदि_अन्तः

#यदि CONFIG_CUDA
स्थिर पूर्णाङ्क export_mem_गन्तव्यम्_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_Frame_आन्तरिकम् *dst_int, पूर्णाङ्क idx,
                              Vk_Device_स्मृतिः mem, size_t आकार)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#यदि_परिभाषितम् _WIN32
    CUDA_EXTERNAL_स्मृतिः_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .आकार = आकार,
    };
    Vk_स्मृतिः_Get_Win32_Handle_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_स्मृतिः_GET_WIN32_HANDLE_INFO_KHR,
        .स्मृतिः     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32_BIT
            : VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT,
    };

    ret = vk->Get_स्मृतिः_Win32_Handle_KHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#अन्यथा
    CUDA_EXTERNAL_स्मृतिः_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_FD,
        .आकार = आकार,
    };
    Vk_स्मृतिः_Get_Fd_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_स्मृतिः_GET_FD_INFO_KHR,
        .स्मृतिः     = mem,
        .handleType = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_OPAQUE_FD_BIT_KHR,
    };

    ret = vk->Get_स्मृतिः_Fd_KHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }
#यदि_अन्तः

    ret = CHECK_CU(cu->cu_Import_External_स्मृतिः(&dst_int->ext_mem[idx], &ext_desc));
    यदि (ret < 0) {
#यदि_अपरिभाषितम् _WIN32
        close(ext_desc.handle.fd);
#यदि_अन्तः
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क export_sem_गन्तव्यम्_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_Frame_आन्तरिकम् *dst_int, पूर्णाङ्क idx,
                              VkSemaphore sem)
{
    Vk_परिणाम ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#यदि_परिभाषितम् _WIN32
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
#यदि_अन्तः

#यदि_परिभाषितम् _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#अन्यथा
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#यदि_अन्तः
    यदि (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        प्रत्यागम AVERROR_EXTERNAL;
    }
#यदि_परिभाषितम् _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#यदि_अन्तः

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    यदि (ret < 0) {
#यदि_अपरिभाषितम् _WIN32
        close(ext_sem_desc.handle.fd);
#यदि_अन्तः
        प्रत्यागम AVERROR_EXTERNAL;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vulkan_export_गन्तव्यम्_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 ध्रुव AVFrame *frame)
{
    पूर्णाङ्क err;
    Vk_परिणाम ret;
    AVVkFrame *dst_f;
    AVVk_Frame_आन्तरिकम् *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    पूर्णाङ्क nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->दत्त;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_आन्तरिकम् *cu_आन्तरिकम् = cuda_dev->आन्तरिकम्;
    CudaFunctions *cu = cu_आन्तरिकम्->cuda_dl;
    CUarray_format cufmt = desc->comp[0].गभीरता > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    ध्रुव पूर्णाङ्क elem_आकार = 1 + (desc->comp[0].गभीरता > 8);

    dst_f = (AVVkFrame *)frame->दत्त[0];
    dst_int = dst_f->आन्तरिकम्;

    यदि (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_बफर_ref(cuda_hwfc);
        यदि (!dst_int->cuda_fc_ref)
            प्रत्यागम AVERROR(ENOMEM);

        nb_images = ff_vk_गणनम्_images(dst_f);
        प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
            err = export_mem_गन्तव्यम्_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->आकार[i]);
            यदि (err < 0)
                गच्छ fail;

            err = export_sem_गन्तव्यम्_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            यदि (err < 0)
                गच्छ fail;
        }

        यदि (nb_images != planes) {
            प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                यदि (desc->comp[i].चरणः / elem_आकार > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    गच्छ fail;
                }

                VkImageSubresource subres = {
                    .aspect_आवरणम् = i == 2 ? VK_IMAGE_ASPECT_स्मृतिः_PLANE_2_BIT_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_स्मृतिः_PLANE_1_BIT_EXT :
                                           VK_IMAGE_ASPECT_स्मृतिः_PLANE_0_BIT_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.विस्थापनम्;
            }
        }

        प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
            CUDA_EXTERNAL_स्मृतिः_MIPMAPPED_ARRAY_DESC tex_desc = {
                .विस्थापनम् = offsets[i],
                .arrayDesc = {
                    .गभीरता_2 = 0,
                    .Format = cufmt,
                    .अङ्कः_Channels = desc->comp[i].चरणः / elem_आकार,
                    .Flags = 0,
                },
                .अङ्कः_स्तराः = 1,
            };
            पूर्णाङ्क p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->विस्तारः, hwfc->height, i);
            tex_desc.arrayDesc.विस्तारः_2 = p_w;
            tex_desc.arrayDesc.Height = p_h;

            ret = CHECK_CU(cu->cu_External_स्मृतिः_Get_Mapped_Mipmapped_Array(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            यदि (ret < 0) {
                err = AVERROR_EXTERNAL;
                गच्छ fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            यदि (ret < 0) {
                err = AVERROR_EXTERNAL;
                गच्छ fail;
            }

        }
    }

    प्रत्यागम 0;

fail:
    vulkan_free_आन्तरिकम्(p, dst_f);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vulkan_transfer_दत्त_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVk_Frame_आन्तरिकम् *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    पूर्णाङ्क nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_आन्तरिकम् *cu_आन्तरिकम् = cuda_dev->आन्तरिकम्;
    CudaFunctions *cu = cu_आन्तरिकम्->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_अङ्कः_दत्त_सूचकाः] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_अङ्कः_दत्त_सूचकाः] = { 0 };

    dst_f = (AVVkFrame *)dst->दत्त[0];
    nb_images = ff_vk_गणनम्_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_बहुलकम्_EXTERNAL_EXPORT);
    यदि (err < 0)
        प्रत्यागम err;

    err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(cuda_dev->cuda_ctx));
    यदि (err < 0)
        प्रत्यागम err;

    err = vulkan_export_गन्तव्यम्_cuda(hwfc, src->hw_चौकटाः_ctx, dst);
    यदि (err < 0) {
        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        प्रत्यागम err;
    }

    dst_int = dst_f->आन्तरिकम्;

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.मानम् = dst_f->sem_मानम्[i] + 0;
        s_s_par[i].params.fence.मानम् = dst_f->sem_मानम्[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->प्रवाहः));
    यदि (err < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .src_स्मृतिः_Type = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->दत्त[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dst_स्मृतिः_Type = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        पूर्णाङ्क p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->विस्तारः, hwfc->height, i);

        cpy.विस्तारः_अन्तर्_अष्टकानि = p_w * desc->comp[i].चरणः;
        cpy.Height = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->प्रवाहः));
        यदि (err < 0)
            गच्छ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->प्रवाहः));
    यदि (err < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++)
        dst_f->sem_मानम्[i]++;

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    प्रत्यागम err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_बहुलकम्_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    vulkan_free_आन्तरिकम्(p, dst_f);
    av_बफर_unref(&dst->buf[0]);
    प्रत्यागम err;
}
#यदि_अन्तः

स्थिर पूर्णाङ्क vulkan_map_गन्तव्यम्(AVHWFramesContext *hwfc, AVFrame *dst,
                         ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_अप्रयुक्तम् VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    विकल्प (src->format) {
#यदि CONFIG_LIBDRM
#यदि CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
        यदि (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            प्रत्यागम vulkan_map_from_vaapi(hwfc, dst, src, flags);
        अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        यदि (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            प्रत्यागम vulkan_map_from_drm(hwfc, dst, src, flags);
        अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }
}

#यदि CONFIG_LIBDRM
प्रकारनिर्देश संरचना VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVkFrame *source;
} VulkanDRMMapping;

स्थिर शून्य vulkan_unmap_गन्तव्यम्_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_frame_sync(hwfc, hwmap->source, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    प्रति (पूर्णाङ्क i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

स्थिर अन्तःस्थ uint32_t vulkan_fmt_गन्तव्यम्_drm(VkFormat vkfmt)
{
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        यदि (vulkan_drm_format_map[i].vk_format == vkfmt)
            प्रत्यागम vulkan_drm_format_map[i].drm_fourcc;
    प्रत्यागम DRM_FORMAT_INVALID;
}

#परिभाषय MAX_स्मृतिः_PLANES 4
स्थिर VkImageAspectFlags plane_सूचकांक_गन्तव्यम्_aspect(पूर्णाङ्क plane) {
    यदि (plane == 0) प्रत्यागम VK_IMAGE_ASPECT_स्मृतिः_PLANE_0_BIT_EXT;
    यदि (plane == 1) प्रत्यागम VK_IMAGE_ASPECT_स्मृतिः_PLANE_1_BIT_EXT;
    यदि (plane == 2) प्रत्यागम VK_IMAGE_ASPECT_स्मृतिः_PLANE_2_BIT_EXT;
    यदि (plane == 3) प्रत्यागम VK_IMAGE_ASPECT_स्मृतिः_PLANE_3_BIT_EXT;

    av_assert2 (0 && "Invalid plane index");
    प्रत्यागम VK_IMAGE_ASPECT_स्मृतिः_PLANE_0_BIT_EXT;
}

#यदि_परिभाषितम् DMA_BUF_IOCTL_EXPORT_SYNC_FILE
स्थिर पूर्णाङ्क vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVkFrame *f,
                                     Vulkan_चौकटाः_Priv *fp, पूर्णाङ्क nb_sems)
{
    पूर्णाङ्क sync_fd = -1;
    Vk_परिणाम ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    यदि (f->आन्तरिकम्->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_अग्र         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_द्विमान,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_अग्र = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->आन्तरिकम्->drm_sync_sem);
        यदि (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            प्रत्यागम AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    यदि (ff_vk_exec_start(&p->vkctx, exec) >= 0) {
        प्रति (पूर्णाङ्क i = 0; i < nb_sems; i++)
            ff_vk_exec_सङ्कलय_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_मानम्[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT);
        ff_vk_exec_सङ्कलय_dep_bool_sem(&p->vkctx, exec, &f->आन्तरिकम्->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT, 0);
        यदि (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->आन्तरिकम्->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            यदि (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    प्रत्यागम sync_fd;
}
#यदि_अन्तः

स्थिर पूर्णाङ्क vulkan_map_गन्तव्यम्_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err = 0;
    Vk_परिणाम ret;
    AVVkFrame *f = (AVVkFrame *)src->दत्त[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    ध्रुव पूर्णाङ्क nb_sems = nb_images;
    पूर्णाङ्क free_drm_desc_on_err = 1;
    पूर्णाङ्क sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(परिमाण(*drm_desc));
    यदि (!drm_desc)
        प्रत्यागम AVERROR(ENOMEM);

    err = prepare_frame(hwfc, &fp->compute_exec, f, PREP_बहुलकम्_EXTERNAL_EXPORT);
    यदि (err < 0)
        गच्छ अन्तः_2;

#यदि_परिभाषितम् DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        यदि (err < 0)
            गच्छ अन्तः_2;
        sync_fd = err;
        err = 0;
    }
#यदि_अन्तः

    यदि (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_गणनम् = nb_sems,
            .pSemaphores    = f->sem,
            .p_मानानि        = f->sem_मानम्,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_चौकटाः_ctx, dst, src, &vulkan_unmap_गन्तव्यम्_drm, drm_desc);
    यदि (err < 0)
        गच्छ अन्तः_2;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    यदि (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        गच्छ अन्तः_2;
    }

    प्रति (पूर्णाङ्क i = 0; (i < planes) && (f->mem[i]); i++) {
        Vk_स्मृतिः_Get_Fd_Info_KHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_स्मृतिः_GET_FD_INFO_KHR,
            .स्मृतिः     = f->mem[i],
            .handleType = VK_EXTERNAL_स्मृतिः_HANDLE_TYPE_DMA_BUF_BIT_EXT,
        };

        ret = vk->Get_स्मृतिः_Fd_KHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        यदि (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            गच्छ अन्तः_2;
        }

#यदि HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        यदि (sync_fd >= 0) {
            पूर्णाङ्क dup_fd = dup(sync_fd);
            यदि (dup_fd >= 0) {
                संरचना dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                यदि (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } अन्यथा {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#यदि_अन्तः

        drm_desc->nb_objects++;
        drm_desc->objects[i].आकार = f->आकार[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    प्रति (पूर्णाङ्क i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_गन्तव्यम्_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_गणनम्;

        यदि (drm_desc->layers[i].nb_planes > MAX_स्मृतिः_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            गच्छ अन्तः_2;
        }

        प्रति (पूर्णाङ्क j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            पूर्णाङ्क aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspect_आवरणम् = plane_सूचकांक_गन्तव्यम्_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_सूचकांक = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].विस्थापनम् = layout.विस्थापनम्;
            drm_desc->layers[i].planes[j].pitch  = layout.rowPitch;
        }

        यदि (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            गच्छ अन्तः_2;
        }


        यदि (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            अनुवर्त;

    }

    dst->विस्तारः   = src->विस्तारः;
    dst->height  = src->height;
    dst->दत्त[0] = (uint8_t *)drm_desc;
    dst->hw_चौकटाः_ctx = av_बफर_ref(src->hw_चौकटाः_ctx);

    यदि (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    प्रत्यागम 0;

अन्तः_2:
    प्रति (पूर्णाङ्क i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    यदि (free_drm_desc_on_err)
        av_free(drm_desc);
    यदि (sync_fd >= 0)
        close(sync_fd);
    प्रत्यागम err;
}

#यदि CONFIG_VAAPI
स्थिर पूर्णाङ्क vulkan_map_गन्तव्यम्_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;
    AVFrame *tmp = av_frame_alloc();
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_अविभाज्यः;

    err = vulkan_map_गन्तव्यम्_drm(hwfc, tmp, src, flags);
    यदि (err < 0)
        गच्छ fail;

    err = av_hwframe_map(dst, tmp, flags);
    यदि (err < 0)
        गच्छ fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_frame_free(&tmp);
    प्रत्यागम err;
}
#यदि_अन्तः
#यदि_अन्तः

स्थिर पूर्णाङ्क vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    av_अप्रयुक्तम् VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    विकल्प (dst->format) {
#यदि CONFIG_LIBDRM
    पक्ष AV_PIX_FMT_DRM_अविभाज्यः:
        यदि (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            प्रत्यागम vulkan_map_गन्तव्यम्_drm(hwfc, dst, src, flags);
        अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
#यदि CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
        यदि (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            प्रत्यागम vulkan_map_गन्तव्यम्_vaapi(hwfc, dst, src, flags);
        अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
#यदि_अन्तः
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम AVERROR(ENOSYS);
}

स्थिर पूर्णाङ्क copy_बफर_दत्त(AVHWFramesContext *hwfc, FFVk_बफर *vkbuf,
                            AVFrame *swf, Vk_बफर_Image_Copy *region,
                            पूर्णाङ्क planes, पूर्णाङ्क upload)
{
    पूर्णाङ्क err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    पूर्णाङ्क bytewidth[AV_अङ्कः_दत्त_सूचकाः];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->विस्तारः, i);
        यदि (bytewidth[i] < 0)
            प्रत्यागम bytewidth[i];
    }

    यदि (upload) {
        प्रति (पूर्णाङ्क i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].बफर_विस्थापनम्,
                                region[i].बफर_Row_दीर्घता,
                                swf->दत्त[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.height);

        err = ff_vk_flush_बफर(&p->vkctx, vkbuf, 0, VK_सम्पूर्णम्_आकार, 1);
        यदि (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            प्रत्यागम AVERROR_EXTERNAL;
        }
    } अन्यथा {
        err = ff_vk_flush_बफर(&p->vkctx, vkbuf, 0, VK_सम्पूर्णम्_आकार, 0);
        यदि (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            प्रत्यागम AVERROR_EXTERNAL;
        }

        प्रति (पूर्णाङ्क i = 0; i < planes; i++)
            av_image_copy_plane(swf->दत्त[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].बफर_विस्थापनम्,
                                region[i].बफर_Row_दीर्घता,
                                bytewidth[i],
                                region[i].imageExtent.height);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क get_plane_buf(AVHWFramesContext *hwfc, FFVk_बफर **dst,
                         AVFrame *swf, Vk_बफर_Image_Copy *region, पूर्णाङ्क upload)
{
    पूर्णाङ्क err;
    uint32_t p_w, p_h;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(swf->format);
    Vk_बफर_Usage_Flags buf_usage = upload ? VK_बफर_USAGE_TRANSFER_SRC_BIT :
                                            VK_बफर_USAGE_TRANSFER_DST_BIT;

    size_t buf_विस्थापनम् = 0;
    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->विस्तारः, swf->height, i);

        region[i] = (Vk_बफर_Image_Copy) {
            .बफर_विस्थापनम् = buf_विस्थापनम्,
            .बफर_Row_दीर्घता = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_बफर_Copy_Row_Pitch_Alignment),
            .बफर_Image_Height = p_h,
            .imageSubresource.layer_गणनम् = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_विस्थापनम् += FFALIGN(p_h*region[i].बफर_Row_दीर्घता,
                              p->props.properties.limits.optimal_बफर_Copy_विस्थापनम्_Alignment);
    }

    err = ff_vk_get_pooled_बफर(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  रिक्त, buf_विस्थापनम्,
                                  VK_स्मृतिः_PROPERTY_HOST_VISIBLE_BIT |
                                  p->vkctx.host_cached_flag);
    यदि (err < 0)
        प्रत्यागम err;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क host_map_frame(AVHWFramesContext *hwfc, FFVk_बफर **dst, पूर्णाङ्क *nb_bufs,
                          AVFrame *swf, Vk_बफर_Image_Copy *region, पूर्णाङ्क upload)
{
    पूर्णाङ्क err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    पूर्णाङ्क nb_src_bufs;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(swf->format);
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_बफर_Usage_Flags buf_usage = upload ? VK_बफर_USAGE_TRANSFER_SRC_BIT :
                                            VK_बफर_USAGE_TRANSFER_DST_BIT;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    यावत् (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    यदि (nb_src_bufs == 1) {
        err = ff_vk_host_map_बफर(&p->vkctx, &dst[0],
                                    swf->दत्त[0], VK_सम्पूर्णम्_आकार, swf->buf[0],
                                    buf_usage);
        यदि (err < 0)
            प्रत्यागम err;
        (*nb_bufs)++;

        प्रति (पूर्णाङ्क i = 0; i < planes; i++)
            region[i].बफर_विस्थापनम् = dst[0]->virtual_विस्थापनम् +
                                     swf->दत्त[i] - swf->दत्त[0];
    } अन्यथा यदि (nb_src_bufs == planes) { /* One buffer per plane */
        प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
            err = ff_vk_host_map_बफर(&p->vkctx, &dst[i],
                                        swf->दत्त[i], VK_सम्पूर्णम्_आकार,
                                        swf->buf[i], buf_usage);
            यदि (err < 0)
                गच्छ fail;
            (*nb_bufs)++;

            region[i].बफर_विस्थापनम् = dst[i]->virtual_विस्थापनम्;
        }
    } अन्यथा {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        प्रत्यागम AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        पूर्णाङ्क align = FFMAX(desc->comp[i].चरणः, p->transfer_विस्थापनम्_align);
        यदि ((align & (align - 1)) || (region[i].बफर_विस्थापनम् & (align - 1))) {
            err = AVERROR(EINVAL);
            गच्छ fail;
        }
    }

    प्रत्यागम 0;

fail:
    प्रति (पूर्णाङ्क i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, पूर्णाङ्क upload)
{
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkan_चौकटाः_Context *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->दत्त[0];
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(swf->format);
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क nb_layout_ch = 0;

    hwfc_vk->तालकम्_frame(hwfc, hwf_vk);

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        पूर्णाङ्क compat = 0;
        प्रति (पूर्णाङ्क j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_गणनम्; j++) {
            यदि (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                भङ्ग;
            }
        }
        यदि (compat)
            अनुवर्त;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspect_आवरणम् = VK_IMAGE_ASPECT_COLOR_BIT,
                .level_गणनम् = 1,
                .layer_गणनम् = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_मानानि = hwf_vk->sem_मानम्,
        .semaphore_गणनम् = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    यदि (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    यदि (upload) {
        Vk_स्मृतिः_गन्तव्यम्_Image_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_स्मृतिः_गन्तव्यम्_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_गणनम् = 1,
            },
        };
        Vk_Copy_स्मृतिः_गन्तव्यम्_Image_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_स्मृतिः_गन्तव्यम्_IMAGE_INFO_EXT,
            .region_गणनम् = 1,
            .pRegions = &region_info,
        };
        प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
            पूर्णाङ्क img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->विस्तारः, swf->height, i);

            region_info.pHostPointer = swf->दत्त[i];
            region_info.स्मृतिः_Row_दीर्घता = swf->linesize[i] / desc->comp[i].चरणः;
            region_info.imageSubresource.aspect_आवरणम् = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_स्मृतिः_गन्तव्यम्_Image_EXT(hwctx->act_dev, &copy_info);
        }
    } अन्यथा {
        Vk_Image_गन्तव्यम्_स्मृतिः_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_गन्तव्यम्_स्मृतिः_COPY_EXT,
            .imageSubresource = {
                .layer_गणनम् = 1,
            },
        };
        Vk_Copy_Image_गन्तव्यम्_स्मृतिः_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_गन्तव्यम्_स्मृतिः_INFO_EXT,
            .region_गणनम् = 1,
            .pRegions = &region_info,
        };
        प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
            पूर्णाङ्क img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->विस्तारः, swf->height, i);

            region_info.pHostPointer = swf->दत्त[i];
            region_info.स्मृतिः_Row_दीर्घता = swf->linesize[i] / desc->comp[i].चरणः;
            region_info.imageSubresource.aspect_आवरणम् = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_Image_गन्तव्यम्_स्मृतिः_EXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_frame(hwfc, hwf_vk);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vulkan_transfer_frame(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 पूर्णाङ्क upload)
{
    पूर्णाङ्क err;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    AVVulkan_चौकटाः_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    पूर्णाङ्क host_mapped = 0;

    AVVkFrame *hwf_vk = (AVVkFrame *)hwf->दत्त[0];
    Vk_बफर_Image_Copy region[AV_अङ्कः_दत्त_सूचकाः]; // always one per plane

    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(swf->format);
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    ध्रुव पूर्णाङ्क nb_images = ff_vk_गणनम्_images(hwf_vk);

    Vk_Image_स्मृतिः_Barrier2 img_bar[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क nb_img_bar = 0;

    FFVk_बफर *bufs[AV_अङ्कः_दत्त_सूचकाः];
    पूर्णाङ्क nb_bufs = 0;

    Vk_Command_बफर cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    यदि ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (swf->विस्तारः > hwfc->विस्तारः || swf->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    पूर्णाङ्क host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;
    पूर्णाङ्क host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_स्मृतिः &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    प्रति (पूर्णाङ्क i = 0; i < planes; i++)
        यदि (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    यदि (!upload && host_copy) {
        प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
            पूर्णाङ्क compat = 0;
            प्रति (पूर्णाङ्क j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_गणनम्; j++) {
                यदि (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    भङ्ग;
                }
            }
            यदि (!compat) {
                host_copy = 0;
                भङ्ग;
            }
        }
    }

    यदि (host_copy)
        प्रत्यागम vulkan_transfer_host(hwfc, hwf, swf, upload);

    प्रति (पूर्णाङ्क i = 0; i < av_pix_fmt_गणनम्_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->विस्तारः, swf->height, i);

        /* Buffer region for this plane */
        region[i] = (Vk_बफर_Image_Copy) {
            .बफर_विस्थापनम् = 0,
            .बफर_Row_दीर्घता = FFABS(swf->linesize[i]),
            .बफर_Image_Height = p_h,
            .imageSubresource.layer_गणनम् = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    यदि (host_map) {
        err = host_map_frame(hwfc, bufs, &nb_bufs, swf, region, upload);
        यदि (err >= 0)
            host_mapped = 1;
    }

    यदि (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        यदि (err < 0)
            गच्छ अन्तः_2;
        nb_bufs = 1;

        यदि (upload) {
            err = copy_बफर_दत्त(hwfc, bufs[0], swf, region, planes, 1);
            यदि (err < 0)
                गच्छ अन्तः_2;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_start(&p->vkctx, exec);
    यदि (err < 0)
        गच्छ अन्तः_2;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_सङ्कलय_dep_frame(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
                                   VK_PIPELINE_STAGE_2_TRANSFER_BIT);
    यदि (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        गच्छ अन्तः_2;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    यदि (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        यदि (host_mapped) {
            err = ff_vk_exec_सङ्कलय_dep_sw_frame(&p->vkctx, exec, swf);
            यदि (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                गच्छ अन्तः_2;
            }
        }

        /* Add the buffers as a dependency */
        प्रति (पूर्णाङ्क i = 0; i < nb_bufs; i++)
            ff_vk_exec_सङ्कलय_dep_refstruct(&p->vkctx, exec, bufs[i]);
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
            .p_Image_स्मृतिः_Barriers = img_bar,
            .image_स्मृतिः_Barrier_गणनम् = nb_img_bar,
    });

    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        पूर्णाङ्क buf_idx = FFMIN(i, (nb_bufs - 1));
        पूर्णाङ्क img_idx = FFMIN(i, (nb_images - 1));
        FFVk_बफर *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].बफर_Row_दीर्घता;
        region[i].बफर_Row_दीर्घता /= desc->comp[i].चरणः;
        region[i].imageSubresource.aspect_आवरणम् = ff_vk_aspect_flag(hwf, i);

        यदि (upload)
            vk->Cmd_Copy_बफर_गन्तव्यम्_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        अन्यथा
            vk->Cmd_Copy_Image_गन्तव्यम्_बफर(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].बफर_Row_दीर्घता = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    यदि (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        यदि (!host_mapped)
            err = copy_बफर_दत्त(hwfc, bufs[0], swf, region, planes, 0);
    }

अन्तः_2:
    प्रति (पूर्णाङ्क i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vulkan_transfer_दत्त_गन्तव्यम्(AVHWFramesContext *hwfc, AVFrame *dst,
                                   ध्रुव AVFrame *src)
{
    av_अप्रयुक्तम् VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    विकल्प (src->format) {
#यदि CONFIG_CUDA
    पक्ष AV_PIX_FMT_CUDA:
#यदि_परिभाषितम् _WIN32
        यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#अन्यथा
        यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_स्मृतिः) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#यदि_अन्तः
            प्रत्यागम vulkan_transfer_दत्त_from_cuda(hwfc, dst, src);
        av_fallthrough;
#यदि_अन्तः
    स्वभाव:
        यदि (src->hw_चौकटाः_ctx)
            प्रत्यागम AVERROR(ENOSYS);
        अन्यथा
            प्रत्यागम vulkan_transfer_frame(hwfc, (AVFrame *)src, dst, 1);
    }
}

#यदि CONFIG_CUDA
स्थिर पूर्णाङ्क vulkan_transfer_दत्त_गन्तव्यम्_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        ध्रुव AVFrame *src)
{
    पूर्णाङ्क err;
    CUcontext dummy;
    AVVkFrame *dst_f;
    AVVk_Frame_आन्तरिकम् *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_चौकटाः_Priv *fp = hwfc->hwctx;
    ध्रुव पूर्णाङ्क planes = av_pix_fmt_गणनम्_planes(hwfc->sw_format);
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    पूर्णाङ्क nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_चौकटाः_ctx->दत्त;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_आन्तरिकम् *cu_आन्तरिकम् = cuda_dev->आन्तरिकम्;
    CudaFunctions *cu = cu_आन्तरिकम्->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_अङ्कः_दत्त_सूचकाः] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_अङ्कः_दत्त_सूचकाः] = { 0 };

    dst_f = (AVVkFrame *)src->दत्त[0];
    nb_images = ff_vk_गणनम्_images(dst_f);

    err = prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_बहुलकम्_EXTERNAL_EXPORT);
    यदि (err < 0)
        प्रत्यागम err;

    err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(cuda_dev->cuda_ctx));
    यदि (err < 0)
        प्रत्यागम err;

    err = vulkan_export_गन्तव्यम्_cuda(hwfc, dst->hw_चौकटाः_ctx, src);
    यदि (err < 0) {
        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        प्रत्यागम err;
    }

    dst_int = dst_f->आन्तरिकम्;

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.मानम् = dst_f->sem_मानम्[i] + 0;
        s_s_par[i].params.fence.मानम् = dst_f->sem_मानम्[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->प्रवाहः));
    यदि (err < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dst_स्मृतिः_Type = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->दत्त[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .src_स्मृतिः_Type = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        पूर्णाङ्क w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->विस्तारः, hwfc->height, i);

        cpy.विस्तारः_अन्तर्_अष्टकानि = w * desc->comp[i].चरणः;
        cpy.Height = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->प्रवाहः));
        यदि (err < 0)
            गच्छ fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->प्रवाहः));
    यदि (err < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क i = 0; i < nb_images; i++)
        dst_f->sem_मानम्[i]++;

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    प्रत्यागम prepare_frame(hwfc, &fp->upload_exec, dst_f, PREP_बहुलकम्_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    vulkan_free_आन्तरिकम्(p, dst_f);
    av_बफर_unref(&dst->buf[0]);
    प्रत्यागम err;
}
#यदि_अन्तः

स्थिर पूर्णाङ्क vulkan_transfer_दत्त_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     ध्रुव AVFrame *src)
{
    av_अप्रयुक्तम् VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    विकल्प (dst->format) {
#यदि CONFIG_CUDA
    पक्ष AV_PIX_FMT_CUDA:
#यदि_परिभाषितम् _WIN32
        यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#अन्यथा
        यदि ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_स्मृतिः) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#यदि_अन्तः
            प्रत्यागम vulkan_transfer_दत्त_गन्तव्यम्_cuda(hwfc, dst, src);
        av_fallthrough;
#यदि_अन्तः
    स्वभाव:
        यदि (dst->hw_चौकटाः_ctx)
            प्रत्यागम AVERROR(ENOSYS);
        अन्यथा
            प्रत्यागम vulkan_transfer_frame(hwfc, dst, (AVFrame *)src, 0);
    }
}

स्थिर पूर्णाङ्क vulkan_चौकटाः_derive_गन्तव्यम्(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, पूर्णाङ्क flags)
{
    प्रत्यागम vulkan_चौकटाः_init(dst_fc);
}

AVVkFrame *av_vk_frame_alloc(शून्य)
{
    पूर्णाङ्क err;
    AVVkFrame *f = av_mallocz(परिमाण(AVVkFrame));
    यदि (!f)
        प्रत्यागम रिक्त;

    f->आन्तरिकम् = av_mallocz(परिमाण(*f->आन्तरिकम्));
    यदि (!f->आन्तरिकम्) {
        av_free(f);
        प्रत्यागम रिक्त;
    }

    err = pthread_mutex_init(&f->आन्तरिकम्->update_mutex, रिक्त);
    यदि (err != 0) {
        av_free(f->आन्तरिकम्);
        av_free(f);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम f;
}

ध्रुव HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_आकार      = परिमाण(VulkanDevicePriv),
    .चौकटाः_hwctx_आकार      = परिमाण(Vulkan_चौकटाः_Priv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .चौकटाः_get_constraints = &vulkan_चौकटाः_get_constraints,
    .चौकटाः_init            = vulkan_चौकटाः_init,
    .चौकटाः_get_बफर      = vulkan_get_बफर,
    .चौकटाः_uninit          = vulkan_चौकटाः_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्       = vulkan_transfer_दत्त_गन्तव्यम्,
    .transfer_दत्त_from     = vulkan_transfer_दत्त_from,

    .map_गन्तव्यम्                 = vulkan_map_गन्तव्यम्,
    .map_from               = vulkan_map_from,
    .चौकटाः_derive_गन्तव्यम्       = &vulkan_चौकटाः_derive_गन्तव्यम्,

    .pix_fmts = (ध्रुव गणना AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
