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

#నిర్వచించు VK_NO_PROTOTYPES
#నిర్వచించు VK_ENABLE_BETA_EXTENSIONS

#నిర్వచితమైతే _WIN32
#అన్తర్భావ <windows.h> /* Included to prevent conflicts with CreateSemaphore */
#అన్తర్భావ <versionhelpers.h>
#అన్తర్భావ "compat/w32dlfcn.h"
#లేకపోతే
#అన్తర్భావ <dlfcn.h>
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు

#అన్తర్భావ "thread.h"

#అన్తర్భావ "config.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_vulkan.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "uuid.h"

#అన్తర్భావ "vulkan.h"
#అన్తర్భావ "vulkan_loader.h"

#ఒకవేళ CONFIG_VAAPI
#అన్తర్భావ "hwcontext_vaapi.h"
#అయితే_ముగింపు

#ఒకవేళ CONFIG_LIBDRM
#ఒకవేళ CONFIG_VAAPI
#అన్తర్భావ <va/va_drmcommon.h>
#అయితే_ముగింపు
#నిర్వచితమైతే __linux__
#అన్తర్భావ <sys/sysmacros.h>
#అయితే_ముగింపు
#అన్తర్భావ <sys/stat.h>
#అన్తర్భావ <xf86drm.h>
#అన్తర్భావ <drm_fourcc.h>
#అన్తర్భావ "hwcontext_drm.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_LINUX_DMA_BUF_H
#అన్తర్భావ <sys/ioctl.h>
#అన్తర్భావ <linux/dma-buf.h>
#అయితే_ముగింపు

#ఒకవేళ CONFIG_CUDA
#అన్తర్భావ "hwcontext_cuda_internal.h"
#అన్తర్భావ "cuda_check.h"
#నిర్వచించు CHECK_CU(x) FF_CUDA_CHECK_DL(cuda_cu, cu, x)
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం VulkanDeviceFeatures {
    VkPhysicalDeviceFeatures2 device;

    VkPhysicalDeviceVulkan11Features vulkan_1_1;
    VkPhysicalDeviceVulkan12Features vulkan_1_2;
    VkPhysicalDeviceVulkan13Features vulkan_1_3;
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore;
    VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR subgroup_rotate;
    VkPhysicalDeviceHostImageCopyFeaturesEXT host_image_copy;
    Vk_Physical_Device_Workgroup_జ్ఞాపకం_Explicit_Layout_Features_KHR explicit_mem_layout;

#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    Vk_Physical_Device_Shader_Long_సదిశ_Features_EXT long_సదిశ;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_shader_replicated_composites
    VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT replicated_composites;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_zero_initialize_device_జ్ఞాపకం
    Vk_Physical_Device_Zero_Initialize_Device_జ్ఞాపకం_Features_EXT zero_initialize;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_expect_assume
    VkPhysicalDeviceShaderExpectAssumeFeaturesKHR expect_assume;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_maximal_reconvergence
    VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR maximal_reconvergence;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_maintenance9
    VkPhysicalDeviceMaintenance9FeaturesKHR maintenance_9;
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11;
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layouts;
#అయితే_ముగింపు

    VkPhysicalDeviceVideoMaintenance1FeaturesKHR video_maintenance_1;
#నిర్వచితమైతే VK_KHR_video_maintenance2
    VkPhysicalDeviceVideoMaintenance2FeaturesKHR video_maintenance_2;
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_decode_vp9
    VkPhysicalDeviceVideoDecodeVP9FeaturesKHR vp9_decode;
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_encode_av1
    VkPhysicalDeviceVideoEncodeAV1FeaturesKHR av1_encode;
#అయితే_ముగింపు

    VkPhysicalDeviceShaderObjectFeaturesEXT shader_object;
    Vk_Physical_Device_Cooperative_మాతృక_Features_KHR cooperative_మాతృక;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float;

#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
    VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR relaxed_extended_instruction;
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR అంతర్గత_వరుస_sync;
#అయితే_ముగింపు
    VkPhysicalDeviceOpticalFlowFeaturesNV optical_flow;
} VulkanDeviceFeatures;

రకనిర్వచనం నిర్మాణం VulkanDevicePriv {
    /**
     * The public AVVulkanDeviceContext. See hwcontext_vulkan.h for it.
     */
    AVVulkanDeviceContext p;

    /* Vulkan library and loader functions */
    శూన్య *libvulkan;

    FFVulkanContext    vkctx;
    AVVulkan_Device_వరుస_Family *compute_qf;
    AVVulkan_Device_వరుస_Family *transfer_qf;

    /* Properties */
    VkPhysicalDeviceProperties2 props;
    Vk_Physical_Device_జ్ఞాపకం_Properties mprops;
    Vk_Physical_Device_External_జ్ఞాపకం_Host_Properties_EXT hprops;
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
    పూర్ణాంకం use_రేఖీయ_images;

    /* Option to allocate all image planes in a single allocation */
    పూర్ణాంకం contiguous_planes;

    /* Disable multiplane images */
    పూర్ణాంకం disable_multiplane;

    /* Prefer memcpy over dynamic host pointer imports */
    పూర్ణాంకం avoid_host_import;

    /* Alignment the transfer queue needs for buffer offsets in image copies */
    పూర్ణాంకం transfer_స్థానభ్రంశం_align;

    /* Maximum queues */
    పూర్ణాంకం హద్దు_queues;
} VulkanDevicePriv;

రకనిర్వచనం నిర్మాణం Vulkan_చట్రాలు_Priv {
    /**
     * The public AVVulkanFramesContext. See hwcontext_vulkan.h for it.
     */
    AVVulkan_చట్రాలు_Context p;

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
    పూర్ణాంకం export_requires_dedicated;
} Vulkan_చట్రాలు_Priv;

రకనిర్వచనం నిర్మాణం AVVk_చట్రం_అంతర్గత {
    pthread_mutex_t update_mutex;

    /* Binary semaphore for SYNC_FD export at DRM map time. Created once lazily,
     * re-signaled each time via a submit in vulkan_map_to_drm. */
    VkSemaphore drm_sync_sem;

#ఒకవేళ CONFIG_CUDA
    /* Importing external memory into cuda is really expensive so we keep the
     * memory imported all the time */
    AVBufferRef *cuda_fc_ref; /* Need to keep it around for uninit */
    CUexternal_జ్ఞాపకం ext_mem[AV_అంకె_దత్తాంశం_సూచికలు];
    CUmipmappedArray cu_mma[AV_అంకె_దత్తాంశం_సూచికలు];
    CUarray cu_array[AV_అంకె_దత్తాంశం_సూచికలు];
    CUexternalSemaphore cu_sem[AV_అంకె_దత్తాంశం_సూచికలు];
#నిర్వచితమైతే _WIN32
    HANDLE ext_mem_handle[AV_అంకె_దత్తాంశం_సూచికలు];
    HANDLE ext_sem_handle[AV_అంకె_దత్తాంశం_సూచికలు];
#అయితే_ముగింపు
#అయితే_ముగింపు
} AVVk_చట్రం_అంతర్గత;

/* Initialize all structs in VulkanDeviceFeatures */
స్థిర శూన్య device_features_init(AVHWDeviceContext *ctx, VulkanDeviceFeatures *feats)
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

#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->long_సదిశ, FF_VK_EXT_LONG_సదిశ,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_సదిశ_FEATURES_EXT);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_shader_replicated_composites
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->replicated_composites, FF_VK_EXT_REPLICATED_COMPOSITES,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_zero_initialize_device_జ్ఞాపకం
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->zero_initialize, FF_VK_EXT_ZERO_INITIALIZE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_జ్ఞాపకం_FEATURES_EXT);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_expect_assume
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->expect_assume, FF_VK_EXT_EXPECT_ASSUME,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES_KHR);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_maximal_reconvergence
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maximal_reconvergence, FF_VK_EXT_MAXIMAL_RECONVERGENCE,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_maintenance9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_9, FF_VK_EXT_MAINTENANCE_9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->maintenance_11, FF_VK_EXT_MAINTENANCE_11,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->unified_layouts, FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR);
#అయితే_ముగింపు

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_1, FF_VK_EXT_VIDEO_MAINTENANCE_1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR);
#నిర్వచితమైతే VK_KHR_video_maintenance2
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->video_maintenance_2, FF_VK_EXT_VIDEO_MAINTENANCE_2,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_2_FEATURES_KHR);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_decode_vp9
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->vp9_decode, FF_VK_EXT_VIDEO_DECODE_VP9,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_encode_av1
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->av1_encode, FF_VK_EXT_VIDEO_ENCODE_AV1,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR);
#అయితే_ముగింపు

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->shader_object, FF_VK_EXT_SHADER_OBJECT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->cooperative_మాతృక, FF_VK_EXT_COOP_మాతృక,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_మాతృక_FEATURES_KHR);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->atomic_float, FF_VK_EXT_ATOMIC_FLOAT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->explicit_mem_layout, FF_VK_EXT_EXPLICIT_MEM_LAYOUT,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_జ్ఞాపకం_EXPLICIT_LAYOUT_FEATURES_KHR);

#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->relaxed_extended_instruction, FF_VK_EXT_RELAXED_EXTENDED_INSTR,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    FF_VK_STRUCT_EXT(s, &feats->device, &feats->అంతర్గత_వరుస_sync, FF_VK_EXT_అంతర్గత_వరుస_SYNC,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR);
#అయితే_ముగింపు

    FF_VK_STRUCT_EXT(s, &feats->device, &feats->optical_flow, FF_VK_EXT_OPTICAL_FLOW,
                     VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV);
}

/* Copy all needed device features */
స్థిర శూన్య device_features_copy_needed(VulkanDeviceFeatures *dst, VulkanDeviceFeatures *src)
{
#నిర్వచించు COPY_VAL(VAL)        \
    చేయి {                     \
        dst->VAL = src->VAL; \
    } అయితే (0)              \

    COPY_VAL(device.features.shaderImageGatherExtended);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);
    COPY_VAL(device.features.fragmentStoresAndAtomics);
    COPY_VAL(device.features.శీర్షం_Pipeline_Stores_And_Atomics);
    COPY_VAL(device.features.shaderInt64);
    COPY_VAL(device.features.shaderInt16);
    COPY_VAL(device.features.shaderFloat64);
    COPY_VAL(device.features.shaderStorageImageReadWithoutFormat);
    COPY_VAL(device.features.shaderStorageImageWriteWithoutFormat);

    COPY_VAL(vulkan_1_1.samplerYcbcrConversion);
    COPY_VAL(vulkan_1_1.storage_నెట్టు_Constant16);
    COPY_VAL(vulkan_1_1.storage_Buffer16_బిట్టు_Access);
    COPY_VAL(vulkan_1_1.ఏకరీతి_And_Storage_Buffer16_బిట్టు_Access);

    COPY_VAL(vulkan_1_2.timelineSemaphore);
    COPY_VAL(vulkan_1_2.scalar_ఖండం_Layout);
    COPY_VAL(vulkan_1_2.బఫరు_Device_చిరునామా);
    COPY_VAL(vulkan_1_2.hostQueryReset);
    COPY_VAL(vulkan_1_2.storage_నెట్టు_Constant8);
    COPY_VAL(vulkan_1_2.shaderInt8);
    COPY_VAL(vulkan_1_2.storage_Buffer8_బిట్టు_Access);
    COPY_VAL(vulkan_1_2.ఏకరీతి_And_Storage_Buffer8_బిట్టు_Access);
    COPY_VAL(vulkan_1_2.shaderFloat16);
    COPY_VAL(vulkan_1_2.shader_బఫరు_Int64_Atomics);
    COPY_VAL(vulkan_1_2.shaderSharedInt64Atomics);
    COPY_VAL(vulkan_1_2.vulkan_జ్ఞాపకం_Model);
    COPY_VAL(vulkan_1_2.vulkan_జ్ఞాపకం_Model_Device_Scope);
    COPY_VAL(vulkan_1_2.vulkan_జ్ఞాపకం_Model_Availability_Visibility_Chains);
    COPY_VAL(vulkan_1_2.ఏకరీతి_బఫరు_Standard_Layout);
    COPY_VAL(vulkan_1_2.runtimeDescriptorArray);
    COPY_VAL(vulkan_1_2.shaderSubgroupExtendedTypes);
    COPY_VAL(vulkan_1_2.shader_ఏకరీతి_బఫరు_Array_Non_ఏకరీతి_Indexing);
    COPY_VAL(vulkan_1_2.shader_Sampled_Image_Array_Non_ఏకరీతి_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_బఫరు_Array_Non_ఏకరీతి_Indexing);
    COPY_VAL(vulkan_1_2.shader_Storage_Image_Array_Non_ఏకరీతి_Indexing);

    COPY_VAL(vulkan_1_3.dynamicRendering);
    COPY_VAL(vulkan_1_3.maintenance4);
    COPY_VAL(vulkan_1_3.synchronization2);
    COPY_VAL(vulkan_1_3.compute_నిండిన_Subgroups);
    COPY_VAL(vulkan_1_3.subgroup_కొలత_Control);
    COPY_VAL(vulkan_1_3.shader_Zero_Initialize_Workgroup_జ్ఞాపకం);
    COPY_VAL(vulkan_1_3.dynamicRendering);

    COPY_VAL(timeline_semaphore.timelineSemaphore);
    COPY_VAL(subgroup_rotate.shaderSubgroupRotate);
    COPY_VAL(host_image_copy.hostImageCopy);

#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    COPY_VAL(long_సదిశ.long_సదిశ_2);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_shader_replicated_composites
    COPY_VAL(replicated_composites.shaderReplicatedComposites);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_EXT_zero_initialize_device_జ్ఞాపకం
    COPY_VAL(zero_initialize.zero_Initialize_Device_జ్ఞాపకం);
#అయితే_ముగింపు

    COPY_VAL(video_maintenance_1.videoMaintenance1);
#నిర్వచితమైతే VK_KHR_video_maintenance2
    COPY_VAL(video_maintenance_2.videoMaintenance2);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_video_decode_vp9
    COPY_VAL(vp9_decode.videoDecodeVP9);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_video_encode_av1
    COPY_VAL(av1_encode.videoEncodeAV1);
#అయితే_ముగింపు

    COPY_VAL(shader_object.shaderObject);

    COPY_VAL(cooperative_మాతృక.cooperative_మాతృక_2);

    COPY_VAL(atomic_float.shader_బఫరు_Float32_Atomics);
    COPY_VAL(atomic_float.shader_బఫరు_Float32_Atomic_కూడు);

    COPY_VAL(explicit_mem_layout.workgroup_జ్ఞాపకం_Explicit_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_జ్ఞాపకం_Explicit_Layout_Scalar_ఖండం_Layout);
    COPY_VAL(explicit_mem_layout.workgroup_జ్ఞాపకం_Explicit_Layout8_బిట్టు_Access);
    COPY_VAL(explicit_mem_layout.workgroup_జ్ఞాపకం_Explicit_Layout16_బిట్టు_Access);

#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
    COPY_VAL(relaxed_extended_instruction.shaderRelaxedExtendedInstruction);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_expect_assume
    COPY_VAL(expect_assume.shaderExpectAssume);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_shader_maximal_reconvergence
    COPY_VAL(maximal_reconvergence.shaderMaximalReconvergence);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_maintenance9
    COPY_VAL(maintenance_9.maintenance9);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    COPY_VAL(maintenance_11.maintenance11);
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    COPY_VAL(unified_layouts.unifiedImageLayouts);
    COPY_VAL(unified_layouts.unifiedImageLayoutsVideo);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    COPY_VAL(అంతర్గత_వరుస_sync.internallySynchronizedQueues);
#అయితే_ముగింపు

    COPY_VAL(optical_flow.opticalFlow);

#నిర్వచనం_రద్దు COPY_VAL
}

#నిర్వచించు ASPECT_2PLANE (VK_IMAGE_ASPECT_PLANE_0_బిట్టు | VK_IMAGE_ASPECT_PLANE_1_బిట్టు)
#నిర్వచించు ASPECT_3PLANE (VK_IMAGE_ASPECT_PLANE_0_బిట్టు | VK_IMAGE_ASPECT_PLANE_1_బిట్టు | VK_IMAGE_ASPECT_PLANE_2_బిట్టు)

స్థిర స్థిరరాశి నిర్మాణం FFVk_Format_నమోదు {
    VkFormat vkf;
    గణన AVPixelFormat pixfmt;
    VkImageAspectFlags aspect;
    పూర్ణాంకం vk_planes;
    పూర్ణాంకం nb_images;
    పూర్ణాంకం nb_images_fallback;
    స్థిరరాశి VkFormat fallback[5];
} vk_formats_list[] = {
    /* Gray formats */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GRAY8,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY10,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY12,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY14,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GRAY16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GRAY32,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GRAYF32, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32_SFLOAT } },

    /* RGB formats */
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGRA,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGBA,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8_UNORM,             AV_PIX_FMT_RGB24,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8_UNORM             } },
    { VK_FORMAT_B8G8R8_UNORM,             AV_PIX_FMT_BGR24,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_B8G8R8_UNORM             } },
    { VK_FORMAT_R16G16B16_UNORM,          AV_PIX_FMT_RGB48,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16_UNORM          } },
    { VK_FORMAT_R16G16B16A16_UNORM,       AV_PIX_FMT_RGBA64,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM       } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_BGR0,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_R8G8B8A8_UNORM,           AV_PIX_FMT_RGB0,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM           } },
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32, AV_PIX_FMT_X2RGB10, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_A2B10G10R10_UNORM_PACK32, AV_PIX_FMT_X2BGR10, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_A2B10G10R10_UNORM_PACK32 } },
    { VK_FORMAT_R32G32B32_SFLOAT,         AV_PIX_FMT_RGBF32,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32G32B32_SFLOAT         } },
    { VK_FORMAT_R16G16B16A16_SFLOAT,      AV_PIX_FMT_RGBAF16, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_SFLOAT      } },
    { VK_FORMAT_R32G32B32A32_SFLOAT,      AV_PIX_FMT_RGBAF32, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32G32B32A32_SFLOAT      } },
    { VK_FORMAT_R32G32B32_UINT,           AV_PIX_FMT_RGB96,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32G32B32_UINT           } },
    { VK_FORMAT_R32G32B32A32_UINT,        AV_PIX_FMT_RGBA128, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R32G32B32A32_UINT        } },

    /* Planar RGB */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRP,     VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP10,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP12,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP14,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRP16,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRPF16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT,  VK_FORMAT_R16_SFLOAT  } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRPF32,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* XYZ */
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_XYZP12,   VK_IMAGE_ASPECT_COLOR_బిట్టు, 3, 3, 3, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar RGB + Alpha */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_GBRAP,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP10,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP12,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP14,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_GBRAP16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_SFLOAT, AV_PIX_FMT_GBRAPF16, VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT, VK_FORMAT_R16_SFLOAT } },
    { VK_FORMAT_R32_UINT,   AV_PIX_FMT_GBRAP32,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT,   VK_FORMAT_R32_UINT   } },
    { VK_FORMAT_R32_SFLOAT, AV_PIX_FMT_GBRAPF32, VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32_SFLOAT } },

    /* Bayer */
    { VK_FORMAT_R16_UNORM, AV_PIX_FMT_BAYER_RGGB16, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16_UNORM } },

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
    { VK_FORMAT_G8B8G8R8_422_UNORM,                     AV_PIX_FMT_YUYV422, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_B8G8R8G8_422_UNORM,                     AV_PIX_FMT_UYVY422, VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R8G8B8A8_UNORM     } },
    { VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16, AV_PIX_FMT_Y210,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16, AV_PIX_FMT_Y212,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_G16B16G16R16_422_UNORM,                 AV_PIX_FMT_Y216,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },

    /* Planar YUVA 420 at 8, 10 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA420P,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P10,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA420P16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 422 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA422P,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P10,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P12,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA422P16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Planar YUVA 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_R8_UNORM,   AV_PIX_FMT_YUVA444P,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM,   VK_FORMAT_R8_UNORM   } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P10,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P12,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },
    { VK_FORMAT_R16_UNORM,  AV_PIX_FMT_YUVA444P16,  VK_IMAGE_ASPECT_COLOR_బిట్టు, 4, 4, 4, { VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM,  VK_FORMAT_R16_UNORM  } },

    /* Single plane 444 at 8, 10, 12 and 16 bits */
    { VK_FORMAT_A2R10G10B10_UNORM_PACK32,               AV_PIX_FMT_XV30,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_A2R10G10B10_UNORM_PACK32 } },
    { VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,     AV_PIX_FMT_XV36,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
    { VK_FORMAT_R16G16B16A16_UNORM,                     AV_PIX_FMT_XV48,    VK_IMAGE_ASPECT_COLOR_బిట్టు, 1, 1, 1, { VK_FORMAT_R16G16B16A16_UNORM } },
};
స్థిర స్థిరరాశి పూర్ణాంకం nb_vk_formats_list = FF_ARRAY_ELEMS(vk_formats_list);

స్థిరరాశి VkFormat *av_vkfmt_from_pixfmt(గణన AVPixelFormat p)
{
    కొరకు (పూర్ణాంకం i = 0; i < nb_vk_formats_list; i++)
        ఒకవేళ (vk_formats_list[i].pixfmt == p)
            తిరిగి vk_formats_list[i].fallback;
    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి నిర్మాణం FFVk_Format_నమోదు *vk_కనుగొను_format_నమోదు(గణన AVPixelFormat p)
{
    కొరకు (పూర్ణాంకం i = 0; i < nb_vk_formats_list; i++)
        ఒకవేళ (vk_formats_list[i].pixfmt == p)
            తిరిగి &vk_formats_list[i];
    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం vkfmt_from_pixfmt2(AVHWDeviceContext *dev_ctx, గణన AVPixelFormat p,
                              VkImageTiling tiling,
                              VkFormat fmts[AV_అంకె_దత్తాంశం_సూచికలు], /* Output format list */
                              పూర్ణాంకం *nb_images,                      /* Output number of images */
                              VkImageAspectFlags *aspect,          /* Output aspect */
                              VkImageUsageFlags *supported_usage,  /* Output supported usage */
                              పూర్ణాంకం disable_multiplane, పూర్ణాంకం need_storage)
{
    VulkanDevicePriv *priv = dev_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &priv->p;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    స్థిరరాశి VkFormatFeatureFlagBits2 basic_flags = VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_బిట్టు |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_SRC_బిట్టు  |
                                                 VK_FORMAT_FEATURE_2_TRANSFER_DST_బిట్టు;

    కొరకు (పూర్ణాంకం i = 0; i < nb_vk_formats_list; i++) {
        ఒకవేళ (vk_formats_list[i].pixfmt == p) {
            VkFormatProperties3 fprops = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3,
            };
            VkFormatProperties2 prop = {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_తదుపరి = &fprops,
            };
            VkFormatFeatureFlagBits2 feats_primary, feats_secondary;
            పూర్ణాంకం basics_primary = 0, basics_secondary = 0;
            పూర్ణాంకం storage_primary = 0, storage_secondary = 0;

            vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                   vk_formats_list[i].vkf,
                                                   &prop);

            feats_primary = tiling == VK_IMAGE_TILING_రేఖీయ ?
                             fprops.రేఖీయ_Tiling_Features : fprops.optimalTilingFeatures;
            basics_primary = (feats_primary & basic_flags) == basic_flags;
            storage_primary = !!(feats_primary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_బిట్టు);

            ఒకవేళ (vk_formats_list[i].vkf != vk_formats_list[i].fallback[0]) {
                vk->GetPhysicalDeviceFormatProperties2(hwctx->phys_dev,
                                                       vk_formats_list[i].fallback[0],
                                                       &prop);
                feats_secondary = tiling == VK_IMAGE_TILING_రేఖీయ ?
                                  fprops.రేఖీయ_Tiling_Features : fprops.optimalTilingFeatures;
                basics_secondary = (feats_secondary & basic_flags) == basic_flags;
                storage_secondary = !!(feats_secondary & VK_FORMAT_FEATURE_2_STORAGE_IMAGE_బిట్టు);
            } లేకపోతే {
                feats_secondary = feats_primary;
                basics_secondary = basics_primary;
                storage_secondary = storage_primary;
            }

            ఒకవేళ (basics_primary &&
                !(disable_multiplane && vk_formats_list[i].vk_planes > 1) &&
                (!need_storage || (need_storage && (storage_primary | storage_secondary)))) {
                ఒకవేళ (fmts) {
                    ఒకవేళ (vk_formats_list[i].nb_images > 1) {
                        కొరకు (పూర్ణాంకం j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                            fmts[j] = vk_formats_list[i].fallback[j];
                    } లేకపోతే {
                        fmts[0] = vk_formats_list[i].vkf;
                    }
                }
                ఒకవేళ (nb_images)
                    *nb_images = 1;
                ఒకవేళ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ఒకవేళ (supported_usage)
                    *supported_usage = ff_vk_map_feats_గమ్యం_usage(feats_primary) |
                                       ((need_storage && (storage_primary | storage_secondary)) ?
                                        VK_IMAGE_USAGE_STORAGE_బిట్టు : 0);
                తిరిగి 0;
            } లేకపోతే ఒకవేళ (basics_secondary &&
                       (!need_storage || (need_storage && storage_secondary))) {
                ఒకవేళ (fmts) {
                    కొరకు (పూర్ణాంకం j = 0; j < vk_formats_list[i].nb_images_fallback; j++)
                        fmts[j] = vk_formats_list[i].fallback[j];
                }
                ఒకవేళ (nb_images)
                    *nb_images = vk_formats_list[i].nb_images_fallback;
                ఒకవేళ (aspect)
                    *aspect = vk_formats_list[i].aspect;
                ఒకవేళ (supported_usage)
                    *supported_usage = ff_vk_map_feats_గమ్యం_usage(feats_secondary);
                తిరిగి 0;
            } లేకపోతే {
                తిరిగి AVERROR(ENOTSUP);
            }
        }
    }

    తిరిగి AVERROR(EINVAL);
}

#ఒకవేళ CONFIG_VULKAN_STATIC
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                               స్థిరరాశి అక్షరం *pName);
#అయితే_ముగింపు

స్థిర పూర్ణాంకం ఎక్కించు_libvulkan(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;

#ఒకవేళ CONFIG_VULKAN_STATIC
    hwctx->get_proc_addr = vkGetInstanceProcAddr;
#లేకపోతే
    స్థిర స్థిరరాశి అక్షరం *lib_పేర్లు[] = {
#ఒకవేళ defined(_WIN32)
        "vulkan-1.dll",
#లేదావేళ defined(__APPLE__)
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#లేకపోతే
        "libvulkan.so.1",
        "libvulkan.so",
#అయితే_ముగింపు
    };

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(lib_పేర్లు); i++) {
        p->libvulkan = dlopen(lib_పేర్లు[i], RTLD_NOW | RTLD_LOCAL);
        ఒకవేళ (p->libvulkan)
            ఆపు;
    }

    ఒకవేళ (!p->libvulkan) {
        av_log(ctx, AV_LOG_ERROR, "Unable to open the libvulkan library!\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    hwctx->get_proc_addr = (PFN_vkGetInstanceProcAddr)dlsym(p->libvulkan, "vkGetInstanceProcAddr");
#అయితే_ముగింపు /* CONFIG_VULKAN_STATIC */

    తిరిగి 0;
}

రకనిర్వచనం నిర్మాణం VulkanOptExtension {
    స్థిరరాశి అక్షరం *name;
    FFVulkanExtensions flag;
} VulkanOptExtension;

స్థిర స్థిరరాశి VulkanOptExtension optional_instance_exts[] = {
#నిర్వచితమైతే __APPLE__
    { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,          FF_VK_EXT_NO_FLAG                },
#అయితే_ముగింపు
    { 0 },
};

స్థిర స్థిరరాశి VulkanOptExtension optional_device_exts[] = {
    /* Misc or required by other extensions */
    { VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,               FF_VK_EXT_PORTABILITY_SUBSET     },
    { VK_KHR_నెట్టు_DESCRIPTOR_EXTENSION_NAME,                  FF_VK_EXT_నెట్టు_DESCRIPTOR        },
    { VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME,              FF_VK_EXT_DEVICE_DRM             },
    { VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME,              FF_VK_EXT_ATOMIC_FLOAT           },
    { VK_KHR_COOPERATIVE_మాతృక_EXTENSION_NAME,               FF_VK_EXT_COOP_మాతృక            },
    { VK_EXT_SHADER_OBJECT_EXTENSION_NAME,                    FF_VK_EXT_SHADER_OBJECT          },
    { VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME,           FF_VK_EXT_SUBGROUP_ROTATE        },
    { VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME,                  FF_VK_EXT_HOST_IMAGE_COPY        },
    { VK_KHR_WORKGROUP_జ్ఞాపకం_EXPLICIT_LAYOUT_EXTENSION_NAME, FF_VK_EXT_EXPLICIT_MEM_LAYOUT    },
#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
    { VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME, FF_VK_EXT_RELAXED_EXTENDED_INSTR },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    { VK_EXT_SHADER_LONG_సదిశ_EXTENSION_NAME,               FF_VK_EXT_LONG_సదిశ            },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_EXT_shader_replicated_composites
    { VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME,     FF_VK_EXT_REPLICATED_COMPOSITES  },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_EXT_zero_initialize_device_జ్ఞాపకం
    { VK_EXT_ZERO_INITIALIZE_DEVICE_జ్ఞాపకం_EXTENSION_NAME,    FF_VK_EXT_ZERO_INITIALIZE        },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_shader_expect_assume
    { VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME,             FF_VK_EXT_EXPECT_ASSUME          },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_shader_maximal_reconvergence
    { VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME,     FF_VK_EXT_MAXIMAL_RECONVERGENCE  },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance9
    { VK_KHR_MAINTENANCE_9_EXTENSION_NAME,                    FF_VK_EXT_MAINTENANCE_9          },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    { VK_KHR_MAINTENANCE_11_EXTENSION_NAME,                   FF_VK_EXT_MAINTENANCE_11         },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    { VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME,            FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  },
#అయితే_ముగింపు
    { VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_1    },
#నిర్వచితమైతే VK_KHR_video_maintenance2
    { VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME,              FF_VK_EXT_VIDEO_MAINTENANCE_2    },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    { VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME,   FF_VK_EXT_అంతర్గత_వరుస_SYNC    },
#అయితే_ముగింపు
    { VK_NV_OPTICAL_FLOW_EXTENSION_NAME,                      FF_VK_EXT_OPTICAL_FLOW           },

    /* Imports/exports */
    { VK_KHR_EXTERNAL_జ్ఞాపకం_FD_EXTENSION_NAME,               FF_VK_EXT_EXTERNAL_FD_జ్ఞాపకం     },
    { VK_EXT_EXTERNAL_జ్ఞాపకం_DMA_BUF_EXTENSION_NAME,          FF_VK_EXT_EXTERNAL_DMABUF_జ్ఞాపకం },
    { VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME,        FF_VK_EXT_DRM_MODIFIER_FLAGS     },
    { VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_FD_SEM        },
    { VK_EXT_EXTERNAL_జ్ఞాపకం_HOST_EXTENSION_NAME,             FF_VK_EXT_EXTERNAL_HOST_జ్ఞాపకం   },
#నిర్వచితమైతే _WIN32
    { VK_KHR_EXTERNAL_జ్ఞాపకం_WIN32_EXTENSION_NAME,            FF_VK_EXT_EXTERNAL_WIN32_జ్ఞాపకం  },
    { VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME,         FF_VK_EXT_EXTERNAL_WIN32_SEM     },
#అయితే_ముగింపు

    /* Video encoding/decoding */
    { VK_KHR_VIDEO_వరుస_EXTENSION_NAME,                      FF_VK_EXT_VIDEO_వరుస            },
    { VK_KHR_VIDEO_ENCODE_వరుస_EXTENSION_NAME,               FF_VK_EXT_VIDEO_ENCODE_వరుస     },
    { VK_KHR_VIDEO_DECODE_వరుస_EXTENSION_NAME,               FF_VK_EXT_VIDEO_DECODE_వరుస     },
    { VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H264      },
    { VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H264      },
    { VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_ENCODE_H265      },
    { VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME,                FF_VK_EXT_VIDEO_DECODE_H265      },
#నిర్వచితమైతే VK_KHR_video_decode_vp9
    { VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_VP9       },
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_video_encode_av1
    { VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_ENCODE_AV1       },
#అయితే_ముగింపు
    { VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME,                 FF_VK_EXT_VIDEO_DECODE_AV1       },
};

స్థిరరాశి అక్షరం **av_vk_get_optional_instance_extensions(పూర్ణాంకం *లెక్క)
{
    స్థిరరాశి అక్షరం **exts = av_malloc_array(పరిమాణం(*exts),
                                        FF_ARRAY_ELEMS(optional_instance_exts) - 1);
    ఒకవేళ (!exts)
        తిరిగి ఖాళీ;

    కొరకు (పూర్ణాంకం i = 0; i < (పూర్ణాంకం)FF_ARRAY_ELEMS(optional_instance_exts) - 1; i++)
        exts[i] = optional_instance_exts[i].name;

    *లెక్క = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
    తిరిగి exts;
}

స్థిరరాశి అక్షరం **av_vk_get_optional_device_extensions(పూర్ణాంకం *లెక్క)
{
    స్థిరరాశి అక్షరం **exts = av_malloc_array(పరిమాణం(*exts),
                                        FF_ARRAY_ELEMS(optional_device_exts));
    ఒకవేళ (!exts)
        తిరిగి ఖాళీ;

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(optional_device_exts); i++)
        exts[i] = optional_device_exts[i].name;

    *లెక్క = FF_ARRAY_ELEMS(optional_device_exts);
    తిరిగి exts;
}

స్థిర VKAPI_ATTR
VkBool32 VKAPI_CALL vk_dbg_callback(Vk_Debug_Utils_సందేశం_Severity_Flag_బిట్లు_EXT severity,
                                    Vk_Debug_Utils_సందేశం_Type_Flags_EXT సందేశం_Type,
                                    స్థిరరాశి Vk_Debug_Utils_Messenger_Callback_దత్తాంశం_EXT *దత్తాంశం,
                                    శూన్య *priv)
{
    పూర్ణాంకం l;
    AVHWDeviceContext *ctx = priv;

    /* Ignore false positives */
    ఎంపిక (దత్తాంశం->సందేశం_Id_సంఖ్య) {
    స్థితి 0x086974c1: /* BestPractices-vkCreateCommandPool-command-buffer-reset */
    స్థితి 0xfd92477a: /* BestPractices-vkAllocateMemory-small-allocation */
        తిరిగి VK_FALSE;
    అప్రమేయ:
        ఆపు;
    }

    ఎంపిక (severity) {
    స్థితి VK_DEBUG_UTILS_సందేశం_SEVERITY_VERBOSE_బిట్టు_EXT: l = AV_LOG_VERBOSE; ఆపు;
    స్థితి VK_DEBUG_UTILS_సందేశం_SEVERITY_INFO_బిట్టు_EXT:    l = AV_LOG_INFO;    ఆపు;
    స్థితి VK_DEBUG_UTILS_సందేశం_SEVERITY_WARNING_బిట్టు_EXT: l = AV_LOG_WARNING; ఆపు;
    స్థితి VK_DEBUG_UTILS_సందేశం_SEVERITY_ERROR_బిట్టు_EXT:   l = AV_LOG_ERROR;   ఆపు;
    అప్రమేయ:                                              l = AV_LOG_DEBUG;   ఆపు;
    }

    av_log(ctx, l, "%s\n", దత్తాంశం->p_సందేశం);
    కొరకు (పూర్ణాంకం i = 0; i < దత్తాంశం->cmd_Buf_Label_లెక్క; i++)
        av_log(ctx, l, "\t%i: %s\n", i, దత్తాంశం->pCmdBufLabels[i].pLabelName);

    తిరిగి VK_FALSE;
}

#నిర్వచించు కూడు_VAL_గమ్యం_LIST(list, లెక్క, val)                                      \
    చేయి {                                                                       \
        list = av_realloc_array(list, ++లెక్క, పరిమాణం(*list));                 \
        ఒకవేళ (!list) {                                                           \
            err = AVERROR(ENOMEM);                                             \
            వెళ్ళు fail;                                                         \
        }                                                                      \
        list[లెక్క - 1] = av_strdup(val);                                      \
        ఒకవేళ (!list[లెక్క - 1]) {                                                \
            err = AVERROR(ENOMEM);                                             \
            వెళ్ళు fail;                                                         \
        }                                                                      \
    } అయితే(0)

#నిర్వచించు RELEASE_PROPS(props, లెక్క)                                            \
    ఒకవేళ (props) {                                                               \
        కొరకు (పూర్ణాంకం i = 0; i < లెక్క; i++)                                        \
            av_free((శూన్య *)((props)[i]));                                     \
        av_free((శూన్య *)props);                                                \
    }

స్థిర పూర్ణాంకం vulkan_device_has_rebar(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    Vk_Device_కొలత max_vram = 0, max_visible_vram = 0;

    /* Get device memory properties */
    av_assert0(p->mprops.జ్ఞాపకం_Type_లెక్క);
    కొరకు (పూర్ణాంకం i = 0; i < p->mprops.జ్ఞాపకం_Type_లెక్క; i++) {
        స్థిరరాశి Vk_జ్ఞాపకం_Type type = p->mprops.జ్ఞాపకం_Types[i];
        స్థిరరాశి Vk_జ్ఞాపకం_కుప్ప కుప్ప = p->mprops.జ్ఞాపకం_Heaps[type.కుప్ప_సూచీ];
        ఒకవేళ (!(type.propertyFlags & VK_జ్ఞాపకం_PROPERTY_DEVICE_LOCAL_బిట్టు))
            కొనసాగు;
        max_vram = FFMAX(max_vram, కుప్ప.కొలత);
        ఒకవేళ (type.propertyFlags & VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు)
            max_visible_vram = FFMAX(max_visible_vram, కుప్ప.కొలత);
    }

    తిరిగి max_vram - max_visible_vram < 1024; /* 1 kB tolerance */
}

గణన FFVulkan_Debug_బహుళకం {
    FF_VULKAN_DEBUG_NONE = 0,
    /* Standard GPU-assisted validation */
    FF_VULKAN_DEBUG_VALIDATE = 1,
    /* Passes printfs in shaders to the debug callback */
    FF_VULKAN_DEBUG_PRINTF = 2,
    /* Enables extra printouts */
    FF_VULKAN_DEBUG_PRACTICES = 3,

    FF_VULKAN_DEBUG_NB,
};

స్థిర పూర్ణాంకం check_extensions(AVHWDeviceContext *ctx, పూర్ణాంకం dev, AVDictionary *opts,
                            స్థిరరాశి అక్షరం * స్థిరరాశి **dst, uint32_t *అంకె,
                            గణన FFVulkan_Debug_బహుళకం debug_బహుళకం)
{
    స్థిరరాశి అక్షరం *tstr;
    స్థిరరాశి అక్షరం **extension_పేర్లు = ఖాళీ;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    పూర్ణాంకం err = 0, దొరికింది, extensions_దొరికింది = 0;

    స్థిరరాశి అక్షరం *mod;
    పూర్ణాంకం optional_exts_అంకె;
    uint32_t sup_ext_లెక్క;
    అక్షరం *user_exts_str = ఖాళీ;
    AVDictionary_నమోదు *user_exts;
    VkExtensionProperties *sup_ext;
    స్థిరరాశి VulkanOptExtension *optional_exts;

    ఒకవేళ (!dev) {
        mod = "instance";
        optional_exts = optional_instance_exts;
        optional_exts_అంకె = FF_ARRAY_ELEMS(optional_instance_exts) - 1;
        user_exts = av_dict_get(opts, "instance_extensions", ఖాళీ, 0);
        ఒకవేళ (user_exts) {
            user_exts_str = av_strdup(user_exts->విలువ);
            ఒకవేళ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
        }
        vk->EnumerateInstanceExtensionProperties(ఖాళీ, &sup_ext_లెక్క, ఖాళీ);
        sup_ext = av_malloc_array(sup_ext_లెక్క, పరిమాణం(VkExtensionProperties));
        ఒకవేళ (!sup_ext)
            తిరిగి AVERROR(ENOMEM);
        vk->EnumerateInstanceExtensionProperties(ఖాళీ, &sup_ext_లెక్క, sup_ext);
    } లేకపోతే {
        mod = "device";
        optional_exts = optional_device_exts;
        optional_exts_అంకె = FF_ARRAY_ELEMS(optional_device_exts);
        user_exts = av_dict_get(opts, "device_extensions", ఖాళీ, 0);
        ఒకవేళ (user_exts) {
            user_exts_str = av_strdup(user_exts->విలువ);
            ఒకవేళ (!user_exts_str) {
                err = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
        }
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ఖాళీ,
                                               &sup_ext_లెక్క, ఖాళీ);
        sup_ext = av_malloc_array(sup_ext_లెక్క, పరిమాణం(VkExtensionProperties));
        ఒకవేళ (!sup_ext)
            తిరిగి AVERROR(ENOMEM);
        vk->EnumerateDeviceExtensionProperties(hwctx->phys_dev, ఖాళీ,
                                               &sup_ext_లెక్క, sup_ext);
    }

    కొరకు (పూర్ణాంకం i = 0; i < optional_exts_అంకె; i++) {
        tstr = optional_exts[i].name;
        దొరికింది = 0;

        /* Check if the device has ReBAR for host image copies */
        ఒకవేళ (!strcmp(tstr, VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME) &&
            !vulkan_device_has_rebar(ctx))
            కొనసాగు;

        ఒకవేళ (dev &&
            ((debug_బహుళకం == FF_VULKAN_DEBUG_VALIDATE) ||
             (debug_బహుళకం == FF_VULKAN_DEBUG_PRINTF) ||
             (debug_బహుళకం == FF_VULKAN_DEBUG_PRACTICES)) &&
            (!strcmp(tstr, VK_EXT_SHADER_OBJECT_EXTENSION_NAME))) {
            కొనసాగు;
        }

        కొరకు (పూర్ణాంకం j = 0; j < sup_ext_లెక్క; j++) {
            ఒకవేళ (!strcmp(tstr, sup_ext[j].extensionName)) {
                దొరికింది = 1;
                ఆపు;
            }
        }
        ఒకవేళ (!దొరికింది)
            కొనసాగు;

        av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
        p->vkctx.extensions |= optional_exts[i].flag;
        కూడు_VAL_గమ్యం_LIST(extension_పేర్లు, extensions_దొరికింది, tstr);
    }

    ఒకవేళ (!dev &&
        ((debug_బహుళకం == FF_VULKAN_DEBUG_VALIDATE) ||
         (debug_బహుళకం == FF_VULKAN_DEBUG_PRINTF) ||
         (debug_బహుళకం == FF_VULKAN_DEBUG_PRACTICES))) {
        tstr = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
        దొరికింది = 0;
        కొరకు (పూర్ణాంకం j = 0; j < sup_ext_లెక్క; j++) {
            ఒకవేళ (!strcmp(tstr, sup_ext[j].extensionName)) {
                దొరికింది = 1;
                ఆపు;
            }
        }
        ఒకవేళ (దొరికింది) {
            av_log(ctx, AV_LOG_VERBOSE, "Using %s extension %s\n", mod, tstr);
            కూడు_VAL_గమ్యం_LIST(extension_పేర్లు, extensions_దొరికింది, tstr);
        } లేకపోతే {
            av_log(ctx, AV_LOG_ERROR, "Debug extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            వెళ్ళు fail;
        }
    }

#నిర్వచితమైతే VK_KHR_shader_relaxed_extended_instruction
    ఒకవేళ ((debug_బహుళకం == FF_VULKAN_DEBUG_PRINTF) && dev) {
        tstr = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;
        దొరికింది = 0;
        కొరకు (పూర్ణాంకం j = 0; j < sup_ext_లెక్క; j++) {
            ఒకవేళ (!strcmp(tstr, sup_ext[j].extensionName)) {
                దొరికింది = 1;
                ఆపు;
            }
        }
        ఒకవేళ (!దొరికింది) {
            av_log(ctx, AV_LOG_ERROR, "Debug_printf/profile enabled, but extension \"%s\" not found!\n",
                   tstr);
            err = AVERROR(EINVAL);
            వెళ్ళు fail;
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (user_exts_str) {
        అక్షరం *save, *token = av_strtok(user_exts_str, "+", &save);
        అయితే (token) {
            దొరికింది = 0;
            కొరకు (పూర్ణాంకం j = 0; j < sup_ext_లెక్క; j++) {
                ఒకవేళ (!strcmp(token, sup_ext[j].extensionName)) {
                    దొరికింది = 1;
                    ఆపు;
                }
            }
            ఒకవేళ (దొరికింది) {
                av_log(ctx, AV_LOG_VERBOSE, "Using %s extension \"%s\"\n", mod, token);
                కూడు_VAL_గమ్యం_LIST(extension_పేర్లు, extensions_దొరికింది, token);
            } లేకపోతే {
                av_log(ctx, AV_LOG_WARNING, "%s extension \"%s\" not found, excluding.\n",
                       mod, token);
            }
            token = av_strtok(ఖాళీ, "+", &save);
        }
    }

    *dst = extension_పేర్లు;
    *అంకె = extensions_దొరికింది;

    av_free(user_exts_str);
    av_free(sup_ext);
    తిరిగి 0;

fail:
    RELEASE_PROPS(extension_పేర్లు, extensions_దొరికింది);
    av_free(user_exts_str);
    av_free(sup_ext);
    తిరిగి err;
}

స్థిర పూర్ణాంకం check_layers(AVHWDeviceContext *ctx, AVDictionary *opts,
                        స్థిరరాశి అక్షరం * స్థిరరాశి **dst, uint32_t *అంకె,
                        గణన FFVulkan_Debug_బహుళకం *debug_బహుళకం)
{
    పూర్ణాంకం err = 0;
    VulkanDevicePriv *priv = ctx->hwctx;
    FFVulkanFunctions *vk = &priv->vkctx.vkfn;

    స్థిర స్థిరరాశి అక్షరం layer_standard_validation[] = { "VK_LAYER_KHRONOS_validation" };
    పూర్ణాంకం layer_standard_validation_దొరికింది = 0;

    uint32_t sup_layer_లెక్క;
    VkLayerProperties *sup_layers;

    AVDictionary_నమోదు *user_layers = av_dict_get(opts, "layers", ఖాళీ, 0);
    అక్షరం *user_layers_str = ఖాళీ;
    అక్షరం *save, *token;

    స్థిరరాశి అక్షరం **enabled_layers = ఖాళీ;
    uint32_t enabled_layers_లెక్క = 0;

    AVDictionary_నమోదు *debug_opt = av_dict_get(opts, "debug", ఖాళీ, 0);
    గణన FFVulkan_Debug_బహుళకం బహుళకం;

    *debug_బహుళకం = బహుళకం = FF_VULKAN_DEBUG_NONE;

    /* Get a list of all layers */
    vk->EnumerateInstanceLayerProperties(&sup_layer_లెక్క, ఖాళీ);
    sup_layers = av_malloc_array(sup_layer_లెక్క, పరిమాణం(VkLayerProperties));
    ఒకవేళ (!sup_layers)
        తిరిగి AVERROR(ENOMEM);
    vk->EnumerateInstanceLayerProperties(&sup_layer_లెక్క, sup_layers);

    av_log(ctx, AV_LOG_VERBOSE, "Supported layers:\n");
    కొరకు (పూర్ణాంకం i = 0; i < sup_layer_లెక్క; i++)
        av_log(ctx, AV_LOG_VERBOSE, "\t%s\n", sup_layers[i].layerName);

    /* If no user layers or debug layers are given, return */
    ఒకవేళ (!debug_opt && !user_layers)
        వెళ్ళు చివర;

    /* Check for any properly supported validation layer */
    ఒకవేళ (debug_opt) {
        ఒకవేళ (!strcmp(debug_opt->విలువ, "printf")) {
            బహుళకం = FF_VULKAN_DEBUG_PRINTF;
        } లేకపోతే ఒకవేళ (!strcmp(debug_opt->విలువ, "validate")) {
            బహుళకం = FF_VULKAN_DEBUG_VALIDATE;
        } లేకపోతే ఒకవేళ (!strcmp(debug_opt->విలువ, "practices")) {
            బహుళకం = FF_VULKAN_DEBUG_PRACTICES;
        } లేకపోతే {
            అక్షరం *చివర_ptr = ఖాళీ;
            పూర్ణాంకం idx = strtol(debug_opt->విలువ, &చివర_ptr, 10);
            ఒకవేళ (చివర_ptr == debug_opt->విలువ || చివర_ptr[0] != '\0' ||
                idx < 0 || idx >= FF_VULKAN_DEBUG_NB) {
                av_log(ctx, AV_LOG_ERROR, "Invalid debugging mode \"%s\"\n",
                       debug_opt->విలువ);
                err = AVERROR(EINVAL);
                వెళ్ళు చివర;
            }
            బహుళకం = idx;
        }
    }

    /* If mode is VALIDATE or PRINTF, try to find the standard validation layer extension */
    ఒకవేళ ((బహుళకం == FF_VULKAN_DEBUG_VALIDATE) ||
        (బహుళకం == FF_VULKAN_DEBUG_PRINTF) ||
        (బహుళకం == FF_VULKAN_DEBUG_PRACTICES)) {
        కొరకు (పూర్ణాంకం i = 0; i < sup_layer_లెక్క; i++) {
            ఒకవేళ (!strcmp(layer_standard_validation, sup_layers[i].layerName)) {
                av_log(ctx, AV_LOG_VERBOSE, "Standard validation layer %s is enabled\n",
                       layer_standard_validation);
                కూడు_VAL_గమ్యం_LIST(enabled_layers, enabled_layers_లెక్క, layer_standard_validation);
                *debug_బహుళకం = బహుళకం;
                layer_standard_validation_దొరికింది = 1;
                ఆపు;
            }
        }
        ఒకవేళ (!layer_standard_validation_దొరికింది) {
            av_log(ctx, AV_LOG_ERROR,
                   "Validation Layer \"%s\" not supported\n", layer_standard_validation);
            err = AVERROR(ENOTSUP);
            వెళ్ళు చివర;
        }
    }

    /* Process any custom layers enabled */
    ఒకవేళ (user_layers) {
        పూర్ణాంకం దొరికింది;

        user_layers_str = av_strdup(user_layers->విలువ);
        ఒకవేళ (!user_layers_str) {
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }

        token = av_strtok(user_layers_str, "+", &save);
        అయితే (token) {
            దొరికింది = 0;

            /* If debug=1/2 was specified as an option, skip this layer */
            ఒకవేళ (!strcmp(layer_standard_validation, token) && layer_standard_validation_దొరికింది) {
                token = av_strtok(ఖాళీ, "+", &save);
                ఆపు;
            }

            /* Try to find the layer in the list of supported layers */
            కొరకు (పూర్ణాంకం j = 0; j < sup_layer_లెక్క; j++) {
                ఒకవేళ (!strcmp(token, sup_layers[j].layerName)) {
                    దొరికింది = 1;
                    ఆపు;
                }
            }

            ఒకవేళ (దొరికింది) {
                av_log(ctx, AV_LOG_VERBOSE, "Using layer: %s\n", token);
                కూడు_VAL_గమ్యం_LIST(enabled_layers, enabled_layers_లెక్క, token);

                /* If debug was not set as an option, force it */
                ఒకవేళ (!strcmp(layer_standard_validation, token))
                    *debug_బహుళకం = FF_VULKAN_DEBUG_VALIDATE;
            } లేకపోతే {
                av_log(ctx, AV_LOG_ERROR,
                       "Layer \"%s\" not supported\n", token);
                err = AVERROR(EINVAL);
                వెళ్ళు చివర;
            }

            token = av_strtok(ఖాళీ, "+", &save);
        }
    }

fail:
చివర:
    av_free(sup_layers);
    av_free(user_layers_str);

    ఒకవేళ (err < 0) {
        RELEASE_PROPS(enabled_layers, enabled_layers_లెక్క);
    } లేకపోతే {
        *dst = enabled_layers;
        *అంకె = enabled_layers_లెక్క;
    }

    తిరిగి err;
}

/* Creates a VkInstance */
స్థిర పూర్ణాంకం create_instance(AVHWDeviceContext *ctx, AVDictionary *opts,
                           గణన FFVulkan_Debug_బహుళకం *debug_బహుళకం)
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkApplicationInfo application_info = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "ffmpeg",
        .application_సంస్కరణ_2 = VK_MAKE_సంస్కరణ(LIBAVUTIL_సంస్కరణ_MAJOR,
                                              LIBAVUTIL_సంస్కరణ_MINOR,
                                              LIBAVUTIL_సంస్కరణ_MICRO),
        .pEngineName        = "libavutil",
        .api_సంస్కరణ         = VK_API_సంస్కరణ_1_3,
        .engine_సంస్కరణ      = VK_MAKE_సంస్కరణ(LIBAVUTIL_సంస్కరణ_MAJOR,
                                              LIBAVUTIL_సంస్కరణ_MINOR,
                                              LIBAVUTIL_సంస్కరణ_MICRO),
    };
    VkValidationFeaturesEXT validation_features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
    };
    VkInstanceCreateInfo inst_props = {
        .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &application_info,
    };

    ఒకవేళ (!hwctx->get_proc_addr) {
        err = ఎక్కించు_libvulkan(ctx);
        ఒకవేళ (err < 0)
            తిరిగి err;
    }

    err = ff_vk_ఎక్కించు_functions(ctx, vk, p->vkctx.extensions, 0, 0);
    ఒకవేళ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance enumeration functions!\n");
        తిరిగి err;
    }

    err = check_layers(ctx, opts, &inst_props.pp_Enabled_Layer_పేర్లు,
                       &inst_props.enabled_Layer_లెక్క, debug_బహుళకం);
    ఒకవేళ (err)
        వెళ్ళు fail;

    /* Check for present/missing extensions */
    err = check_extensions(ctx, 0, opts, &inst_props.pp_Enabled_Extension_పేర్లు,
                           &inst_props.enabled_Extension_లెక్క, *debug_బహుళకం);
    hwctx->enabled_inst_extensions = inst_props.pp_Enabled_Extension_పేర్లు;
    hwctx->nb_enabled_inst_extensions = inst_props.enabled_Extension_లెక్క;
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    /* Enable debug features if needed */
    ఒకవేళ (*debug_బహుళకం == FF_VULKAN_DEBUG_VALIDATE) {
        స్థిర స్థిరరాశి VkValidationFeatureEnableEXT feat_list_validate[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_స్థానం_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_validate;
        validation_features.enabled_Validation_Feature_లెక్క = FF_ARRAY_ELEMS(feat_list_validate);
        inst_props.p_తదుపరి = &validation_features;
    } లేకపోతే ఒకవేళ (*debug_బహుళకం == FF_VULKAN_DEBUG_PRINTF) {
        స్థిర స్థిరరాశి VkValidationFeatureEnableEXT feat_list_debug[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_స్థానం_EXT,
            VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_debug;
        validation_features.enabled_Validation_Feature_లెక్క = FF_ARRAY_ELEMS(feat_list_debug);
        inst_props.p_తదుపరి = &validation_features;
    } లేకపోతే ఒకవేళ (*debug_బహుళకం == FF_VULKAN_DEBUG_PRACTICES) {
        స్థిర స్థిరరాశి VkValidationFeatureEnableEXT feat_list_practices[] = {
            VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
            VK_VALIDATION_FEATURE_ENABLE_ఉత్తమ_PRACTICES_EXT,
        };
        validation_features.pEnabledValidationFeatures = feat_list_practices;
        validation_features.enabled_Validation_Feature_లెక్క = FF_ARRAY_ELEMS(feat_list_practices);
        inst_props.p_తదుపరి = &validation_features;
    }

#నిర్వచితమైతే __APPLE__
    కొరకు (పూర్ణాంకం i = 0; i < inst_props.enabled_Extension_లెక్క; i++) {
        ఒకవేళ (!strcmp(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
                    inst_props.pp_Enabled_Extension_పేర్లు[i])) {
            inst_props.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_బిట్టు_KHR;
            ఆపు;
        }
    }
#అయితే_ముగింపు

    /* Try to create the instance */
    ret = vk->CreateInstance(&inst_props, hwctx->alloc, &hwctx->inst);

    /* Check for errors */
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Instance creation failure: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        వెళ్ళు fail;
    }

    err = ff_vk_ఎక్కించు_functions(ctx, vk, p->vkctx.extensions, 1, 0);
    ఒకవేళ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load instance functions!\n");
        వెళ్ళు fail;
    }

    /* Setup debugging callback if needed */
    ఒకవేళ ((*debug_బహుళకం == FF_VULKAN_DEBUG_VALIDATE) ||
        (*debug_బహుళకం == FF_VULKAN_DEBUG_PRINTF) ||
        (*debug_బహుళకం == FF_VULKAN_DEBUG_PRACTICES)) {
        VkDebugUtilsMessengerCreateInfoEXT dbg = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .సందేశం_Severity = VK_DEBUG_UTILS_సందేశం_SEVERITY_VERBOSE_బిట్టు_EXT |
                               VK_DEBUG_UTILS_సందేశం_SEVERITY_INFO_బిట్టు_EXT    |
                               VK_DEBUG_UTILS_సందేశం_SEVERITY_WARNING_బిట్టు_EXT |
                               VK_DEBUG_UTILS_సందేశం_SEVERITY_ERROR_బిట్టు_EXT,
            .సందేశం_Type = VK_DEBUG_UTILS_సందేశం_TYPE_GENERAL_బిట్టు_EXT    |
                           VK_DEBUG_UTILS_సందేశం_TYPE_VALIDATION_బిట్టు_EXT |
                           VK_DEBUG_UTILS_సందేశం_TYPE_PERFORMANCE_బిట్టు_EXT,
            .pfnUserCallback = vk_dbg_callback,
            .p_User_దత్తాంశం = ctx,
        };

        vk->CreateDebugUtilsMessengerEXT(hwctx->inst, &dbg,
                                         hwctx->alloc, &p->debug_ctx);
    }

    err = 0;

fail:
    RELEASE_PROPS(inst_props.pp_Enabled_Layer_పేర్లు, inst_props.enabled_Layer_లెక్క);
    తిరిగి err;
}

రకనిర్వచనం నిర్మాణం VulkanDeviceSelection {
    uint8_t uuid[VK_UUID_కొలత]; /* Will use this first unless !has_uuid */
    పూర్ణాంకం has_uuid;
    uint32_t drm_major; /* Will use this second unless !has_drm */
    uint32_t drm_minor; /* Will use this second unless !has_drm */
    uint32_t has_drm; /* has drm node info */
    స్థిరరాశి అక్షరం *name; /* Will use this third unless NULL */
    uint32_t pci_device; /* Will use this fourth unless 0x0 */
    uint32_t vendor_id; /* Last resort to find something deterministic */
    పూర్ణాంకం సూచీ; /* Finally fall back to index */
} VulkanDeviceSelection;

స్థిర స్థిరరాశి అక్షరం *vk_dev_type(గణన VkPhysicalDeviceType type)
{
    ఎంపిక (type) {
    స్థితి VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: తిరిగి "integrated";
    స్థితి VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   తిరిగి "discrete";
    స్థితి VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    తిరిగి "virtual";
    స్థితి VK_PHYSICAL_DEVICE_TYPE_CPU:            తిరిగి "software";
    అప్రమేయ:                                     తిరిగి "unknown";
    }
}

/* Finds a device */
స్థిర పూర్ణాంకం కనుగొను_device(AVHWDeviceContext *ctx, VulkanDeviceSelection *select)
{
    పూర్ణాంకం err = 0, choice = -1;
    uint32_t అంకె;
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkPhysicalDevice *devices = ఖాళీ;
    VkPhysicalDeviceIDProperties *idp = ఖాళీ;
    VkPhysicalDeviceProperties2 *prop = ఖాళీ;
    VkPhysicalDeviceDriverProperties *driver_prop = ఖాళీ;
    VkPhysicalDeviceDrmPropertiesEXT *drm_prop = ఖాళీ;

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &అంకె, ఖాళీ);
    ఒకవేళ (ret != VK_SUCCESS || !అంకె) {
        av_log(ctx, AV_LOG_ERROR, "No devices found: %s!\n", ff_vk_ret2str(ret));
        తిరిగి AVERROR(ENODEV);
    }

    devices = av_malloc_array(అంకె, పరిమాణం(VkPhysicalDevice));
    ఒకవేళ (!devices)
        తిరిగి AVERROR(ENOMEM);

    ret = vk->EnumeratePhysicalDevices(hwctx->inst, &అంకె, devices);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed enumerating devices: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    }

    prop = av_calloc(అంకె, పరిమాణం(*prop));
    ఒకవేళ (!prop) {
        err = AVERROR(ENOMEM);
        వెళ్ళు చివర;
    }

    idp = av_calloc(అంకె, పరిమాణం(*idp));
    ఒకవేళ (!idp) {
        err = AVERROR(ENOMEM);
        వెళ్ళు చివర;
    }

    driver_prop = av_calloc(అంకె, పరిమాణం(*driver_prop));
    ఒకవేళ (!driver_prop) {
        err = AVERROR(ENOMEM);
        వెళ్ళు చివర;
    }

    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
        drm_prop = av_calloc(అంకె, పరిమాణం(*drm_prop));
        ఒకవేళ (!drm_prop) {
            err = AVERROR(ENOMEM);
            వెళ్ళు చివర;
        }
    }

    av_log(ctx, AV_LOG_VERBOSE, "GPU listing:\n");
    కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) {
            drm_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT;
            driver_prop[i].p_తదుపరి = &drm_prop[i];
        }
        driver_prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        idp[i].p_తదుపరి = &driver_prop[i];
        idp[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
        prop[i].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        prop[i].p_తదుపరి = &idp[i];

        vk->GetPhysicalDeviceProperties2(devices[i], &prop[i]);
        av_log(ctx, AV_LOG_VERBOSE, "    %d: %s (%s) (0x%x)\n", i,
               prop[i].properties.deviceName,
               vk_dev_type(prop[i].properties.deviceType),
               prop[i].properties.deviceID);
    }

    ఒకవేళ (select->has_uuid) {
        కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
            ఒకవేళ (!memcmp(idp[i].deviceUUID, select->uuid, VK_UUID_కొలత)) {
                choice = i;
                వెళ్ళు చివర;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given UUID!\n");
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    } లేకపోతే ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_DEVICE_DRM) && select->has_drm) {
        కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
            ఒకవేళ ((select->drm_major == drm_prop[i].primaryMajor &&
                 select->drm_minor == drm_prop[i].primaryMinor) ||
                (select->drm_major == drm_prop[i].renderMajor &&
                 select->drm_minor == drm_prop[i].renderMinor)) {
                choice = i;
                వెళ్ళు చివర;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device by given DRM node numbers %i:%i!\n",
               select->drm_major, select->drm_minor);
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    } లేకపోతే ఒకవేళ (select->name) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: %s\n", select->name);
        కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
            ఒకవేళ (అక్షరశ్రేణి_శోధన(prop[i].properties.deviceName, select->name)) {
                choice = i;
                వెళ్ళు చివర;
             }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device \"%s\"!\n",
               select->name);
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    } లేకపోతే ఒకవేళ (select->pci_device) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested device: 0x%x\n", select->pci_device);
        కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
            ఒకవేళ (select->pci_device == prop[i].properties.deviceID) {
                choice = i;
                వెళ్ళు చివర;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with PCI ID 0x%x!\n",
               select->pci_device);
        err = AVERROR(EINVAL);
        వెళ్ళు చివర;
    } లేకపోతే ఒకవేళ (select->vendor_id) {
        av_log(ctx, AV_LOG_VERBOSE, "Requested vendor: 0x%x\n", select->vendor_id);
        కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
            ఒకవేళ (select->vendor_id == prop[i].properties.vendorID) {
                choice = i;
                వెళ్ళు చివర;
            }
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with Vendor ID 0x%x!\n",
               select->vendor_id);
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    } లేకపోతే {
        ఒకవేళ (select->సూచీ < అంకె) {
            choice = select->సూచీ;
            వెళ్ళు చివర;
        }
        av_log(ctx, AV_LOG_ERROR, "Unable to find device with index %i!\n",
               select->సూచీ);
        err = AVERROR(ENODEV);
        వెళ్ళు చివర;
    }

చివర:
    ఒకవేళ (choice > -1) {
        av_log(ctx, AV_LOG_VERBOSE, "Device %d selected: %s (%s) (0x%x)\n",
               choice, prop[choice].properties.deviceName,
               vk_dev_type(prop[choice].properties.deviceType),
               prop[choice].properties.deviceID);
        hwctx->phys_dev = devices[choice];
        p->props = prop[choice];
        p->props.p_తదుపరి = ఖాళీ;
        p->dprops = driver_prop[choice];
        p->dprops.p_తదుపరి = ఖాళీ;
    }

    av_free(devices);
    av_free(prop);
    av_free(idp);
    av_free(drm_prop);
    av_free(driver_prop);

    తిరిగి err;
}

/* Picks the least used qf with the fewest unneeded flags, or -1 if none found */
స్థిర అంతఃవరుస పూర్ణాంకం pick_వరుస_family(Vk_వరుస_Family_Properties2 *qf, uint32_t అంకె_qf,
                                    Vk_వరుస_Flag_బిట్లు flags)
{
    పూర్ణాంకం సూచీ = -1;
    uint32_t min_score = UINT32_MAX;

    కొరకు (పూర్ణాంకం i = 0; i < అంకె_qf; i++) {
        Vk_వరుస_Flag_బిట్లు qflags = qf[i].వరుస_Family_Properties.వరుస_Flags;

        /* Per the spec, reporting transfer caps is optional for these 2 types */
        ఒకవేళ ((flags & VK_వరుస_TRANSFER_బిట్టు) &&
            (qflags & (VK_వరుస_GRAPHICS_బిట్టు | VK_వరుస_COMPUTE_బిట్టు)))
            qflags |= VK_వరుస_TRANSFER_బిట్టు;

        ఒకవేళ (qflags & flags) {
            uint32_t score = av_popcount(qflags) + qf[i].వరుస_Family_Properties.timestamp_Valid_బిట్లు;
            ఒకవేళ (score < min_score) {
                సూచీ = i;
                min_score = score;
            }
        }
    }

    ఒకవేళ (సూచీ > -1)
        qf[సూచీ].వరుస_Family_Properties.timestamp_Valid_బిట్లు++;

    తిరిగి సూచీ;
}

స్థిర అంతఃవరుస పూర్ణాంకం pick_video_వరుస_family(Vk_వరుస_Family_Properties2 *qf,
                                          Vk_వరుస_Family_Video_Properties_KHR *qf_vid, uint32_t అంకె_qf,
                                          VkVideoCodecOperationFlagsKHR flags)
{
    పూర్ణాంకం సూచీ = -1;
    uint32_t min_score = UINT32_MAX;

    కొరకు (పూర్ణాంకం i = 0; i < అంకె_qf; i++) {
        స్థిరరాశి Vk_వరుస_Flags qflags = qf[i].వరుస_Family_Properties.వరుస_Flags;
        స్థిరరాశి VkVideoCodecOperationFlagsKHR vflags = qf_vid[i].videoCodecOperations;

        ఒకవేళ (!(qflags & (VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR | VK_వరుస_VIDEO_DECODE_బిట్టు_KHR)))
            కొనసాగు;

        ఒకవేళ (vflags & flags) {
            uint32_t score = av_popcount(vflags) + qf[i].వరుస_Family_Properties.timestamp_Valid_బిట్లు;
            ఒకవేళ (score < min_score) {
                సూచీ = i;
                min_score = score;
            }
        }
    }

    ఒకవేళ (సూచీ > -1)
        qf[సూచీ].వరుస_Family_Properties.timestamp_Valid_బిట్లు++;

    తిరిగి సూచీ;
}

స్థిర పూర్ణాంకం అమరిక_వరుస_families(AVHWDeviceContext *ctx, VkDeviceCreateInfo *cd)
{
    uint32_t అంకె;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    Vk_వరుస_Family_Properties2 *qf = ఖాళీ;
    Vk_వరుస_Family_Video_Properties_KHR *qf_vid = ఖాళీ;

    /* First get the number of queue families */
    vk->Get_Physical_Device_వరుస_Family_Properties(hwctx->phys_dev, &అంకె, ఖాళీ);
    ఒకవేళ (!అంకె) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        తిరిగి AVERROR_EXTERNAL;
    }

    /* Then allocate memory */
    qf = av_malloc_array(అంకె, పరిమాణం(Vk_వరుస_Family_Properties2));
    ఒకవేళ (!qf)
        తిరిగి AVERROR(ENOMEM);

    qf_vid = av_malloc_array(అంకె, పరిమాణం(Vk_వరుస_Family_Video_Properties_KHR));
    ఒకవేళ (!qf_vid)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (uint32_t i = 0; i < అంకె; i++) {
        qf_vid[i] = (Vk_వరుస_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_వరుస_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_వరుస_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_వరుస_FAMILY_PROPERTIES_2,
            .p_తదుపరి = p->vkctx.extensions & FF_VK_EXT_VIDEO_వరుస ? &qf_vid[i] : ఖాళీ,
        };
    }

    /* Finally retrieve the queue families */
    vk->Get_Physical_Device_వరుస_Family_Properties2(hwctx->phys_dev, &అంకె, qf);

    av_log(ctx, AV_LOG_VERBOSE, "Queue families:\n");
    కొరకు (పూర్ణాంకం i = 0; i < అంకె; i++) {
        av_log(ctx, AV_LOG_VERBOSE, "    %i:%s%s%s%s%s%s%s%s (queues: %i)\n", i,
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_GRAPHICS_బిట్టు) ? " graphics" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_COMPUTE_బిట్టు) ? " compute" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_TRANSFER_బిట్టు) ? " transfer" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR) ? " encode" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_VIDEO_DECODE_బిట్టు_KHR) ? " decode" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_SPARSE_BINDING_బిట్టు) ? " sparse" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_OPTICAL_FLOW_బిట్టు_NV) ? " optical_flow" : "",
               ((qf[i].వరుస_Family_Properties.వరుస_Flags) & VK_వరుస_PROTECTED_బిట్టు) ? " protected" : "",
               qf[i].వరుస_Family_Properties.వరుస_లెక్క);

        /* We use this field to keep a score of how many times we've used that
         * queue family in order to make better choices. */
        qf[i].వరుస_Family_Properties.timestamp_Valid_బిట్లు = 0;
    }

    hwctx->nb_qf = 0;
    hwctx->వరుస_flags = 0;
#నిర్వచితమైతే VK_KHR_internally_synchronized_queues
    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_అంతర్గత_వరుస_SYNC)
        hwctx->వరుస_flags |= VK_DEVICE_వరుస_CREATE_INTERNALLY_SYNCHRONIZED_బిట్టు_KHR;
#అయితే_ముగింపు

    /* Pick each queue family to use. */
#నిర్వచించు PICK_QF(type, vid_op)                                            \
    చేయి {                                                                 \
        uint32_t i;                                                      \
        uint32_t idx;                                                    \
                                                                         \
        ఒకవేళ (vid_op)                                                      \
            idx = pick_video_వరుస_family(qf, qf_vid, అంకె, vid_op);      \
        లేకపోతే                                                             \
            idx = pick_వరుస_family(qf, అంకె, type);                      \
                                                                         \
        ఒకవేళ (idx == -1)                                                   \
            కొనసాగు;                                                    \
                                                                         \
        కొరకు (i = 0; i < hwctx->nb_qf; i++) {                             \
            ఒకవేళ (hwctx->qf[i].idx == idx) {                               \
                hwctx->qf[i].flags |= type;                              \
                hwctx->qf[i].video_caps |= vid_op;                       \
                ఆపు;                                                   \
            }                                                            \
        }                                                                \
        ఒకవేళ (i == hwctx->nb_qf) {                                         \
            hwctx->qf[i].idx = idx;                                      \
            hwctx->qf[i].అంకె = qf[idx].వరుస_Family_Properties.వరుస_లెక్క; \
            ఒకవేళ (p->హద్దు_queues ||                                       \
                p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY) { \
                పూర్ణాంకం max = p->హద్దు_queues;                               \
                ఒకవేళ (type == VK_వరుస_GRAPHICS_బిట్టు)                       \
                    hwctx->qf[i].అంకె = FFMIN(hwctx->qf[i].అంకె,           \
                                             max ? max : 1);             \
                లేకపోతే ఒకవేళ (max)                                            \
                    hwctx->qf[i].అంకె = FFMIN(hwctx->qf[i].అంకె, max);     \
            }                                                            \
            hwctx->qf[i].flags = type;                                   \
            hwctx->qf[i].video_caps = vid_op;                            \
            hwctx->nb_qf++;                                              \
        }                                                                \
    } అయితే (0)

    PICK_QF(VK_వరుస_GRAPHICS_బిట్టు, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_వరుస_COMPUTE_బిట్టు, VK_VIDEO_CODEC_OPERATION_NONE_KHR);
    PICK_QF(VK_వరుస_TRANSFER_బిట్టు, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    PICK_QF(VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H264_బిట్టు_KHR);
    PICK_QF(VK_వరుస_VIDEO_DECODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H264_బిట్టు_KHR);

    PICK_QF(VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_H265_బిట్టు_KHR);
    PICK_QF(VK_వరుస_VIDEO_DECODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_H265_బిట్టు_KHR);

#నిర్వచితమైతే VK_KHR_video_decode_vp9
    PICK_QF(VK_వరుస_VIDEO_DECODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_VP9_బిట్టు_KHR);
#అయితే_ముగింపు

#నిర్వచితమైతే VK_KHR_video_encode_av1
    PICK_QF(VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_బిట్టు_KHR);
#అయితే_ముగింపు
    PICK_QF(VK_వరుస_VIDEO_DECODE_బిట్టు_KHR, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_బిట్టు_KHR);

    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_OPTICAL_FLOW)
        PICK_QF(VK_వరుస_OPTICAL_FLOW_బిట్టు_NV, VK_VIDEO_CODEC_OPERATION_NONE_KHR);

    av_free(qf);
    av_free(qf_vid);

#నిర్వచనం_రద్దు PICK_QF

    cd->p_వరుస_Create_Infos = av_malloc_array(hwctx->nb_qf,
                                            పరిమాణం(Vk_Device_వరుస_Create_Info));
    ఒకవేళ (!cd->p_వరుస_Create_Infos)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (uint32_t i = 0; i < hwctx->nb_qf; i++) {
        పూర్ణాంకం dup = 0;
        దశాంశం *weights = ఖాళీ;
        Vk_Device_వరుస_Create_Info *pc;
        కొరకు (uint32_t j = 0; j < cd->వరుస_Create_Info_లెక్క; j++) {
            ఒకవేళ (hwctx->qf[i].idx == cd->p_వరుస_Create_Infos[j].వరుస_Family_సూచీ) {
                dup = 1;
                ఆపు;
            }
        }
        ఒకవేళ (dup)
            కొనసాగు;

        weights = av_malloc_array(hwctx->qf[i].అంకె, పరిమాణం(దశాంశం));
        ఒకవేళ (!weights) {
            కొరకు (uint32_t j = 0; j < cd->వరుస_Create_Info_లెక్క; j++)
                av_free((శూన్య *)cd->p_వరుస_Create_Infos[i].p_వరుస_Priorities);
            av_free((శూన్య *)cd->p_వరుస_Create_Infos);
            తిరిగి AVERROR(ENOMEM);
        }

        కొరకు (uint32_t j = 0; j < hwctx->qf[i].అంకె; j++)
            weights[j] = 1.0;

        pc = (Vk_Device_వరుస_Create_Info *)cd->p_వరుస_Create_Infos;
        pc[cd->వరుస_Create_Info_లెక్క++] = (Vk_Device_వరుస_Create_Info) {
            .sType = VK_STRUCTURE_TYPE_DEVICE_వరుస_CREATE_INFO,
            .flags = hwctx->వరుస_flags,
            .వరుస_Family_సూచీ = hwctx->qf[i].idx,
            .వరుస_లెక్క = hwctx->qf[i].అంకె,
            .p_వరుస_Priorities = weights,
        };
    }

    తిరిగి 0;
}

/* Only resources created by vulkan_device_create should be released here,
 * resources created by vulkan_device_init should be released by
 * vulkan_device_uninit, to make sure we don't free user provided resources,
 * and there is no leak.
 */
స్థిర శూన్య vulkan_device_free(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ఒకవేళ (hwctx->act_dev)
        vk->DestroyDevice(hwctx->act_dev, hwctx->alloc);

    ఒకవేళ (p->debug_ctx)
        vk->DestroyDebugUtilsMessengerEXT(hwctx->inst, p->debug_ctx,
                                          hwctx->alloc);

    ఒకవేళ (hwctx->inst)
        vk->DestroyInstance(hwctx->inst, hwctx->alloc);

    ఒకవేళ (p->libvulkan)
        dlclose(p->libvulkan);

    RELEASE_PROPS(hwctx->enabled_inst_extensions, hwctx->nb_enabled_inst_extensions);
    RELEASE_PROPS(hwctx->enabled_dev_extensions, hwctx->nb_enabled_dev_extensions);
}

స్థిర శూన్య vulkan_device_uninit(AVHWDeviceContext *ctx)
{
    VulkanDevicePriv *p = ctx->hwctx;

    ఒకవేళ (p->qf_mutex) {
        కొరకు (uint32_t i = 0; i < p->nb_tot_qfs; i++) {
            pthread_mutex_destroy(p->qf_mutex[i]);
            av_freep(&p->qf_mutex[i]);
        }
        av_freep(&p->qf_mutex);
    }

    ff_vk_uninit(&p->vkctx);
}

స్థిర పూర్ణాంకం vulkan_device_create_అంతర్గత(AVHWDeviceContext *ctx,
                                         VulkanDeviceSelection *dev_select,
                                         పూర్ణాంకం disable_multiplane,
                                         AVDictionary *opts, పూర్ణాంకం flags)
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    AVDictionary_నమోదు *opt_d;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    గణన FFVulkan_Debug_బహుళకం debug_బహుళకం = FF_VULKAN_DEBUG_NONE;
    VulkanDeviceFeatures supported_feats = { 0 };
    VkDeviceCreateInfo dev_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    };

    /* Create an instance if not given one */
    ఒకవేళ ((err = create_instance(ctx, opts, &debug_బహుళకం)))
        వెళ్ళు చివర;

    /* Find a physical device (if not given one) */
    ఒకవేళ ((err = కనుగొను_device(ctx, dev_select)))
        వెళ్ళు చివర;

    /* Get supported memory types */
    vk->Get_Physical_Device_జ్ఞాపకం_Properties(hwctx->phys_dev, &p->mprops);

    /* Find and enable extensions for the physical device */
    ఒకవేళ ((err = check_extensions(ctx, 1, opts, &dev_info.pp_Enabled_Extension_పేర్లు,
                                &dev_info.enabled_Extension_లెక్క, debug_బహుళకం))) {
        కొరకు (పూర్ణాంకం i = 0; i < dev_info.వరుస_Create_Info_లెక్క; i++)
            av_free((శూన్య *)dev_info.p_వరుస_Create_Infos[i].p_వరుస_Priorities);
        av_free((శూన్య *)dev_info.p_వరుస_Create_Infos);
        వెళ్ళు చివర;
    }

    /* Get all supported features for the physical device */
    device_features_init(ctx, &supported_feats);
    vk->GetPhysicalDeviceFeatures2(hwctx->phys_dev, &supported_feats.device);

    /* Copy all needed features from those supported and activate them */
    device_features_init(ctx, &p->feats);
    device_features_copy_needed(&p->feats, &supported_feats);
    dev_info.p_తదుపరి = p->feats.device.p_తదుపరి;
    dev_info.pEnabledFeatures = &p->feats.device.features;

    /* Limit queues to a given number if needed */
    opt_d = av_dict_get(opts, "limit_queues", ఖాళీ, 0);
    ఒకవేళ (opt_d)
        p->హద్దు_queues = strtol(opt_d->విలువ, ఖాళీ, 10);

    /* Setup enabled queue families */
    ఒకవేళ ((err = అమరిక_వరుస_families(ctx, &dev_info)))
        వెళ్ళు చివర;

    /* Finally create the device */
    ret = vk->CreateDevice(hwctx->phys_dev, &dev_info, hwctx->alloc,
                           &hwctx->act_dev);

    కొరకు (పూర్ణాంకం i = 0; i < dev_info.వరుస_Create_Info_లెక్క; i++)
        av_free((శూన్య *)dev_info.p_వరుస_Create_Infos[i].p_వరుస_Priorities);
    av_free((శూన్య *)dev_info.p_వరుస_Create_Infos);

    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Device creation failure: %s\n",
               ff_vk_ret2str(ret));
        కొరకు (పూర్ణాంకం i = 0; i < dev_info.enabled_Extension_లెక్క; i++)
            av_free((శూన్య *)dev_info.pp_Enabled_Extension_పేర్లు[i]);
        av_free((శూన్య *)dev_info.pp_Enabled_Extension_పేర్లు);
        err = AVERROR_EXTERNAL;
        వెళ్ళు చివర;
    }

    /* Tiled images setting, use them by default */
    opt_d = av_dict_get(opts, "linear_images", ఖాళీ, 0);
    ఒకవేళ (opt_d)
        p->use_రేఖీయ_images = strtol(opt_d->విలువ, ఖాళీ, 10);

    /* The disable_multiplane argument takes precedent over the option */
    p->disable_multiplane = disable_multiplane;
    ఒకవేళ (!p->disable_multiplane) {
        opt_d = av_dict_get(opts, "disable_multiplane", ఖాళీ, 0);
        ఒకవేళ (opt_d)
            p->disable_multiplane = strtol(opt_d->విలువ, ఖాళీ, 10);
    }

    /* Disable host pointer imports (by default on nvidia) */
    p->avoid_host_import = p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY;
    opt_d = av_dict_get(opts, "avoid_host_import", ఖాళీ, 0);
    ఒకవేళ (opt_d)
        p->avoid_host_import = strtol(opt_d->విలువ, ఖాళీ, 10);

    /* Set the public device feature struct and its pNext chain */
    hwctx->device_features = p->feats.device;

    /* Set the list of all active extensions */
    hwctx->enabled_dev_extensions = dev_info.pp_Enabled_Extension_పేర్లు;
    hwctx->nb_enabled_dev_extensions = dev_info.enabled_Extension_లెక్క;

    /* The extension lists need to be freed */
    ctx->విడుదల = vulkan_device_free;

చివర:
    తిరిగి err;
}

స్థిర శూన్య తాళం_వరుస(AVHWDeviceContext *ctx, uint32_t వరుస_family, uint32_t సూచీ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ఒకవేళ (p->qf_mutex)
        pthread_mutex_తాళం(&p->qf_mutex[వరుస_family][సూచీ]);
}

స్థిర శూన్య unlock_వరుస(AVHWDeviceContext *ctx, uint32_t వరుస_family, uint32_t సూచీ)
{
    VulkanDevicePriv *p = ctx->hwctx;
    ఒకవేళ (p->qf_mutex)
        pthread_mutex_unlock(&p->qf_mutex[వరుస_family][సూచీ]);
}

స్థిర పూర్ణాంకం vulkan_device_init(AVHWDeviceContext *ctx)
{
    పూర్ణాంకం err = 0;
    uint32_t qf_అంకె;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_వరుస_Family_Properties2 *qf;
    Vk_వరుస_Family_Video_Properties_KHR *qf_vid;
    VkPhysicalDeviceExternalSemaphoreInfo ext_sem_props_info;

    /* Set device extension flags */
    కొరకు (పూర్ణాంకం i = 0; i < hwctx->nb_enabled_dev_extensions; i++) {
        కొరకు (పూర్ణాంకం j = 0; j < FF_ARRAY_ELEMS(optional_device_exts); j++) {
            ఒకవేళ (!strcmp(hwctx->enabled_dev_extensions[i],
                        optional_device_exts[j].name)) {
                p->vkctx.extensions |= optional_device_exts[j].flag;
                ఆపు;
            }
        }
    }

    err = ff_vk_ఎక్కించు_functions(ctx, vk, p->vkctx.extensions, 1, 1);
    ఒకవేళ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to load functions!\n");
        తిరిగి err;
    }

    p->props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    p->props.p_తదుపరి = &p->hprops;
    p->hprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_జ్ఞాపకం_HOST_PROPERTIES_EXT;
    p->hprops.p_తదుపరి = &p->dprops;
    p->dprops.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;

    vk->GetPhysicalDeviceProperties2(hwctx->phys_dev, &p->props);
    av_log(ctx, AV_LOG_VERBOSE, "Using device: %s\n",
           p->props.properties.deviceName);
    av_log(ctx, AV_LOG_VERBOSE, "Alignments:\n");
    av_log(ctx, AV_LOG_VERBOSE, "    optimalBufferCopyRowPitchAlignment: %"PRIu64"\n",
           p->props.properties.limits.optimal_బఫరు_Copy_అడ్డువరుస_Pitch_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    minMemoryMapAlignment:              %zu\n",
           p->props.properties.limits.min_జ్ఞాపకం_Map_Alignment);
    av_log(ctx, AV_LOG_VERBOSE, "    nonCoherentAtomSize:                %"PRIu64"\n",
           p->props.properties.limits.non_Coherent_Atom_కొలత);
    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_జ్ఞాపకం)
        av_log(ctx, AV_LOG_VERBOSE, "    minImportedHostPointerAlignment:    %"PRIu64"\n",
               p->hprops.min_Imported_Host_సూచిక_Alignment);

    vk->Get_Physical_Device_వరుస_Family_Properties(hwctx->phys_dev, &qf_అంకె, ఖాళీ);
    ఒకవేళ (!qf_అంకె) {
        av_log(ctx, AV_LOG_ERROR, "Failed to get queues!\n");
        తిరిగి AVERROR_EXTERNAL;
    }

    ext_sem_props_info = (VkPhysicalDeviceExternalSemaphoreInfo) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO,
    };

    /* Opaque FD semaphore properties */
    ext_sem_props_info.handleType =
#నిర్వచితమైతే _WIN32
        IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_బిట్టు
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_బిట్టు;
#లేకపోతే
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_బిట్టు;
#అయితే_ముగింపు
    p->ext_sem_props_opaque.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
    vk->GetPhysicalDeviceExternalSemaphoreProperties(hwctx->phys_dev,
                                                     &ext_sem_props_info,
                                                     &p->ext_sem_props_opaque);

    qf = av_malloc_array(qf_అంకె, పరిమాణం(Vk_వరుస_Family_Properties2));
    ఒకవేళ (!qf)
        తిరిగి AVERROR(ENOMEM);

    qf_vid = av_malloc_array(qf_అంకె, పరిమాణం(Vk_వరుస_Family_Video_Properties_KHR));
    ఒకవేళ (!qf_vid) {
        av_free(qf);
        తిరిగి AVERROR(ENOMEM);
    }

    కొరకు (uint32_t i = 0; i < qf_అంకె; i++) {
        qf_vid[i] = (Vk_వరుస_Family_Video_Properties_KHR) {
            .sType = VK_STRUCTURE_TYPE_వరుస_FAMILY_VIDEO_PROPERTIES_KHR,
        };
        qf[i] = (Vk_వరుస_Family_Properties2) {
            .sType = VK_STRUCTURE_TYPE_వరుస_FAMILY_PROPERTIES_2,
            .p_తదుపరి = p->vkctx.extensions & FF_VK_EXT_VIDEO_వరుస ? &qf_vid[i] : ఖాళీ,
        };
    }

    vk->Get_Physical_Device_వరుస_Family_Properties2(hwctx->phys_dev, &qf_అంకె, qf);

    p->nb_tot_qfs = qf_అంకె;

    ఒకవేళ (!(p->vkctx.extensions & FF_VK_EXT_అంతర్గత_వరుస_SYNC)) {
        p->qf_mutex = av_calloc(qf_అంకె, పరిమాణం(*p->qf_mutex));
        ఒకవేళ (!p->qf_mutex) {
            err = AVERROR(ENOMEM);
            వెళ్ళు చివర;
        }

        కొరకు (uint32_t i = 0; i < qf_అంకె; i++) {
            p->qf_mutex[i] = av_calloc(qf[i].వరుస_Family_Properties.వరుస_లెక్క,
                                       పరిమాణం(**p->qf_mutex));
            ఒకవేళ (!p->qf_mutex[i]) {
                err = AVERROR(ENOMEM);
                వెళ్ళు చివర;
            }
            కొరకు (uint32_t j = 0; j < qf[i].వరుస_Family_Properties.వరుస_లెక్క; j++) {
                err = pthread_mutex_init(&p->qf_mutex[i][j], ఖాళీ);
                ఒకవేళ (err != 0) {
                    av_log(ctx, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n",
                           av_err2str(err));
                    err = AVERROR(err);
                    వెళ్ళు చివర;
                }
            }
        }
    }

    కొరకు (పూర్ణాంకం i = 0; i < hwctx->nb_qf; i++) {
        ఒకవేళ (!hwctx->qf[i].video_caps &&
            hwctx->qf[i].flags & (VK_వరుస_VIDEO_DECODE_బిట్టు_KHR |
                                  VK_వరుస_VIDEO_ENCODE_బిట్టు_KHR)) {
            hwctx->qf[i].video_caps = qf_vid[hwctx->qf[i].idx].videoCodecOperations;
        }
    }

    /* Setup array for pQueueFamilyIndices with used queue families */
    p->nb_img_qfs = 0;
    కొరకు (పూర్ణాంకం i = 0; i < hwctx->nb_qf; i++) {
        పూర్ణాంకం చూసిన = 0;
        /* Make sure each entry is unique
         * (VUID-VkBufferCreateInfo-sharingMode-01419) */
        కొరకు (పూర్ణాంకం j = (i - 1); j >= 0; j--) {
            ఒకవేళ (hwctx->qf[i].idx == hwctx->qf[j].idx) {
                చూసిన = 1;
                ఆపు;
            }
        }
        ఒకవేళ (!చూసిన)
            p->img_qfs[p->nb_img_qfs++] = hwctx->qf[i].idx;
    }

#ఒకవేళ FF_API_VULKAN_SYNC_QUEUES
FF_DISABLE_DEPRECATION_WARNINGS
    ఒకవేళ (!hwctx->తాళం_వరుస)
        hwctx->తాళం_వరుస = తాళం_వరుస;
    ఒకవేళ (!hwctx->unlock_వరుస)
        hwctx->unlock_వరుస = unlock_వరుస;
FF_ENABLE_DEPRECATION_WARNINGS
#అయితే_ముగింపు

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_జ్ఞాపకం_Properties(hwctx->phys_dev, &p->mprops);

    p->vkctx.device = ctx;
    p->vkctx.hwctx = hwctx;

    ff_vk_ఎక్కించు_props(&p->vkctx);
    p->compute_qf = ff_vk_qf_కనుగొను(&p->vkctx, VK_వరుస_COMPUTE_బిట్టు, 0);
    p->transfer_qf = ff_vk_qf_కనుగొను(&p->vkctx, VK_వరుస_TRANSFER_బిట్టు, 0);

    /* Transfer-only queues need 4-byte aligned buffer offsets in image copies */
    p->transfer_స్థానభ్రంశం_align = 1;
    ఒకవేళ (p->transfer_qf) {
        Vk_వరుస_Flags flags = p->vkctx.qf_props[p->transfer_qf->idx].వరుస_Family_Properties.వరుస_Flags;
        ఒకవేళ (!(flags & (VK_వరుస_GRAPHICS_బిట్టు | VK_వరుస_COMPUTE_బిట్టు)))
            p->transfer_స్థానభ్రంశం_align = 4;
    }
#నిర్వచితమైతే VK_KHR_maintenance11
    ఒకవేళ (p->vkctx.maintenance_11_feats.maintenance11)
        p->transfer_స్థానభ్రంశం_align = 1;
#అయితే_ముగింపు

    /* Re-query device capabilities, in case the device was created externally */
    vk->Get_Physical_Device_జ్ఞాపకం_Properties(hwctx->phys_dev, &p->mprops);

చివర:
    av_free(qf_vid);
    av_free(qf);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vulkan_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                                AVDictionary *opts, పూర్ణాంకం flags)
{
    VulkanDeviceSelection dev_select = { 0 };
    ఒకవేళ (device && device[0]) {
        అక్షరం *చివర = ఖాళీ;

        ఒకవేళ (!av_uuid_parse(device, dev_select.uuid)) {
            dev_select.has_uuid = 1;
        } లేకపోతే {
            dev_select.సూచీ = strtol(device, &చివర, 10);
            ఒకవేళ (చివర == device || *చివర) {
                dev_select.సూచీ = 0;
                dev_select.name  = device;
            }
        }
    }

    తిరిగి vulkan_device_create_అంతర్గత(ctx, &dev_select, 0, opts, flags);
}

స్థిర పూర్ణాంకం vulkan_device_derive(AVHWDeviceContext *ctx,
                                AVHWDeviceContext *src_ctx,
                                AVDictionary *opts, పూర్ణాంకం flags)
{
    av_వాడని VulkanDeviceSelection dev_select = { 0 };

    /* If there's only one device on the system, then even if its not covered
     * by the following checks (e.g. non-PCIe ARM GPU), having an empty
     * dev_select will mean it'll get picked. */
    ఎంపిక(src_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI: {
        AVVAAPIDeviceContext *src_hwctx = src_ctx->hwctx;
        VADisplay dpy = src_hwctx->display;
#ఒకవేళ VA_CHECK_సంస్కరణ(1, 15, 0)
        VAStatus vas;
        VADisplayAttribute attr = {
            .type = VADisplayPCIID,
        };
#అయితే_ముగింపు
        స్థిరరాశి అక్షరం *vendor;

#ఒకవేళ VA_CHECK_సంస్కరణ(1, 15, 0)
        vas = va_Get_Display_లక్షణాలు(dpy, &attr, 1);
        ఒకవేళ (vas == VA_స్థితి_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED)
            dev_select.pci_device = (attr.విలువ & 0xFFFF);
#అయితే_ముగింపు

        ఒకవేళ (!dev_select.pci_device) {
            vendor = vaQueryVendorString(dpy);
            ఒకవేళ (!vendor) {
                av_log(ctx, AV_LOG_ERROR, "Unable to get device info from VAAPI!\n");
                తిరిగి AVERROR_EXTERNAL;
            }

            ఒకవేళ (అక్షరశ్రేణి_శోధన(vendor, "AMD"))
                dev_select.vendor_id = 0x1002;
        }

        తిరిగి vulkan_device_create_అంతర్గత(ctx, &dev_select, 0, opts, flags);
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_LIBDRM
    స్థితి AV_HWDEVICE_TYPE_DRM: {
        పూర్ణాంకం err;
        నిర్మాణం stat drm_కణుపు_info;
        drmDevice *drm_dev_info;
        AVDRMDeviceContext *src_hwctx = src_ctx->hwctx;

        err = fstat(src_hwctx->fd, &drm_కణుపు_info);
        ఒకవేళ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get node info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            తిరిగి AVERROR_EXTERNAL;
        }

        dev_select.drm_major = major(drm_కణుపు_info.st_dev);
        dev_select.drm_minor = minor(drm_కణుపు_info.st_dev);
        dev_select.has_drm   = 1;

        err = drmGetDevice(src_hwctx->fd, &drm_dev_info);
        ఒకవేళ (err) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get device info from DRM fd: %s!\n",
                   av_err2str(AVERROR(errno)));
            తిరిగి AVERROR_EXTERNAL;
        }

        ఒకవేళ (drm_dev_info->bustype == DRM_BUS_PCI)
            dev_select.pci_device = drm_dev_info->deviceinfo.pci->device_id;

        drmFreeDevice(&drm_dev_info);

        తిరిగి vulkan_device_create_అంతర్గత(ctx, &dev_select, 0, opts, flags);
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_CUDA
    స్థితి AV_HWDEVICE_TYPE_CUDA: {
        AVHWDeviceContext *cuda_cu = src_ctx;
        AVCUDADeviceContext *src_hwctx = src_ctx->hwctx;
        AVCUDADevice_Context_అంతర్గత *cu_అంతర్గత = src_hwctx->అంతర్గత;
        CudaFunctions *cu = cu_అంతర్గత->cuda_dl;

        పూర్ణాంకం ret = CHECK_CU(cu->cuDeviceGetUuid((CUuuid *)&dev_select.uuid,
                                               cu_అంతర్గత->cuda_device));
        ఒకవేళ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Unable to get UUID from CUDA!\n");
            తిరిగి AVERROR_EXTERNAL;
        }

        dev_select.has_uuid = 1;

        /*
         * CUDA is not able to import multiplane images, so always derive a
         * Vulkan device with multiplane disabled.
         */
        తిరిగి vulkan_device_create_అంతర్గత(ctx, &dev_select, 1, opts, flags);
    }
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }
}

స్థిర పూర్ణాంకం vulkan_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                         స్థిరరాశి శూన్య *hwconfig,
                                         AVHWFramesConstraints *constraints)
{
    పూర్ణాంకం లెక్క = 0;
    VulkanDevicePriv *p = ctx->hwctx;

    కొరకు (గణన AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        లెక్క += vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                                    p->use_రేఖీయ_images ? VK_IMAGE_TILING_రేఖీయ :
                                                           VK_IMAGE_TILING_OPTIMAL,
                                    ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, p->disable_multiplane, 1) >= 0;
    }

    constraints->valid_sw_formats = av_malloc_array(లెక్క + 1 + CONFIG_CUDA,
                                                    పరిమాణం(గణన AVPixelFormat));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    లెక్క = 0;
    కొరకు (గణన AVPixelFormat i = 0; i < nb_vk_formats_list; i++) {
        ఒకవేళ (vkfmt_from_pixfmt2(ctx, vk_formats_list[i].pixfmt,
                               p->use_రేఖీయ_images ? VK_IMAGE_TILING_రేఖీయ :
                                                      VK_IMAGE_TILING_OPTIMAL,
                               ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, p->disable_multiplane, 1) >= 0) {
            constraints->valid_sw_formats[లెక్క++] = vk_formats_list[i].pixfmt;
        }
    }

#ఒకవేళ CONFIG_CUDA
    constraints->valid_sw_formats[లెక్క++] = AV_PIX_FMT_CUDA;
#అయితే_ముగింపు

    constraints->valid_sw_formats[లెక్క++] = AV_PIX_FMT_NONE;

    constraints->min_వెడల్పు  = 1;
    constraints->min_ఎత్తు = 1;
    constraints->max_వెడల్పు  = p->props.properties.limits.maxImageDimension2D;
    constraints->max_ఎత్తు = p->props.properties.limits.maxImageDimension2D;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(గణన AVPixelFormat));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VULKAN;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం alloc_mem(AVHWDeviceContext *ctx, Vk_జ్ఞాపకం_Requirements *req,
                     Vk_జ్ఞాపకం_Property_Flag_బిట్లు req_flags, స్థిరరాశి శూన్య *alloc_extension,
                     Vk_జ్ఞాపకం_Property_Flag_బిట్లు *mem_flags, Vk_Device_జ్ఞాపకం *mem)
{
    Vk_ఫలితం ret;
    పూర్ణాంకం సూచీ = -1;
    VulkanDevicePriv *p = ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    Vk_జ్ఞాపకం_Allocate_Info alloc_info = {
        .sType          = VK_STRUCTURE_TYPE_జ్ఞాపకం_ALLOCATE_INFO,
        .p_తదుపరి          = alloc_extension,
        .కేటాయింపు_కొలత = req->కొలత,
    };

    /* The vulkan spec requires memory types to be sorted in the "optimal"
     * order, so the first matching type we find will be the best/fastest one */
    కొరకు (పూర్ణాంకం i = 0; i < p->mprops.జ్ఞాపకం_Type_లెక్క; i++) {
        స్థిరరాశి Vk_జ్ఞాపకం_Type *type = &p->mprops.జ్ఞాపకం_Types[i];

        /* The memory type must be supported by the requirements (bitfield) */
        ఒకవేళ (!(req->జ్ఞాపకం_Type_బిట్లు & (1 << i)))
            కొనసాగు;

        /* The memory type flags must include our properties */
        ఒకవేళ ((type->propertyFlags & req_flags) != req_flags)
            కొనసాగు;

        /* The memory type must be large enough */
        ఒకవేళ (req->కొలత > p->mprops.జ్ఞాపకం_Heaps[type->కుప్ప_సూచీ].కొలత)
            కొనసాగు;

        /* Found a suitable memory type */
        సూచీ = i;
        ఆపు;
    }

    ఒకవేళ (సూచీ < 0) {
        av_log(ctx, AV_LOG_ERROR, "No memory type found for flags 0x%x\n",
               req_flags);
        తిరిగి AVERROR(EINVAL);
    }

    alloc_info.జ్ఞాపకం_Type_సూచీ = సూచీ;

    ret = vk->Allocate_జ్ఞాపకం(dev_hwctx->act_dev, &alloc_info,
                             dev_hwctx->alloc, mem);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate memory: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR(ENOMEM);
    }

    *mem_flags |= p->mprops.జ్ఞాపకం_Types[సూచీ].propertyFlags;

    తిరిగి 0;
}

స్థిర శూన్య vulkan_free_అంతర్గత(VulkanDevicePriv *p, AVVk_చట్రం *f)
{
    av_వాడని AVVk_చట్రం_అంతర్గత *అంతర్గత = f->అంతర్గత;

    // Make this function safe to call repeatedly
    ఒకవేళ (!అంతర్గత)
        తిరిగి;

#ఒకవేళ CONFIG_CUDA
    ఒకవేళ (అంతర్గత->cuda_fc_ref) {
        AVHWFramesContext *cuda_fc = (AVHWFramesContext *)అంతర్గత->cuda_fc_ref->దత్తాంశం;
        పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(cuda_fc->sw_format);
        AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
        AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
        AVCUDADevice_Context_అంతర్గత *cu_అంతర్గత = cuda_dev->అంతర్గత;
        CudaFunctions *cu = cu_అంతర్గత->cuda_dl;

        కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
            ఒకవేళ (అంతర్గత->cu_sem[i])
                CHECK_CU(cu->cuDestroyExternalSemaphore(అంతర్గత->cu_sem[i]));
            ఒకవేళ (అంతర్గత->cu_mma[i])
                CHECK_CU(cu->cuMipmappedArrayDestroy(అంతర్గత->cu_mma[i]));
            ఒకవేళ (అంతర్గత->ext_mem[i])
                CHECK_CU(cu->cu_Destroy_External_జ్ఞాపకం(అంతర్గత->ext_mem[i]));
#నిర్వచితమైతే _WIN32
            ఒకవేళ (అంతర్గత->ext_sem_handle[i])
                CloseHandle(అంతర్గత->ext_sem_handle[i]);
            ఒకవేళ (అంతర్గత->ext_mem_handle[i])
                CloseHandle(అంతర్గత->ext_mem_handle[i]);
#అయితే_ముగింపు
        }

        av_బఫరు_unref(&అంతర్గత->cuda_fc_ref);
    }
#అయితే_ముగింపు

    ఒకవేళ (అంతర్గత->drm_sync_sem != VK_NULL_HANDLE)
        p->vkctx.vkfn.DestroySemaphore(p->p.act_dev, అంతర్గత->drm_sync_sem,
                                        p->p.alloc);

    pthread_mutex_destroy(&అంతర్గత->update_mutex);
    av_freep(&f->అంతర్గత);
}

స్థిర శూన్య vulkan_చట్రం_free(AVHWFramesContext *hwfc, AVVk_చట్రం *f)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    పూర్ణాంకం nb_images = ff_vk_లెక్క_images(f);
    పూర్ణాంకం nb_sems = 0;

    అయితే (nb_sems < FF_ARRAY_ELEMS(f->sem) && f->sem[nb_sems])
        nb_sems++;

    ఒకవేళ (nb_sems) {
        VkSemaphoreWaitInfo sem_wait = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .pSemaphores    = f->sem,
            .p_విలువలు        = f->sem_విలువ,
            .semaphore_లెక్క = nb_sems,
        };

        vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);
    }

    vulkan_free_అంతర్గత(p, f);

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        vk->DestroyImage(hwctx->act_dev,     f->img[i], hwctx->alloc);
        vk->Free_జ్ఞాపకం(hwctx->act_dev,       f->mem[i], hwctx->alloc);
        vk->DestroySemaphore(hwctx->act_dev, f->sem[i], hwctx->alloc);
    }

    av_free(f);
}

స్థిర శూన్య vulkan_చట్రం_free_cb(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    vulkan_చట్రం_free(opaque, (AVVk_చట్రం*)దత్తాంశం);
}

స్థిర పూర్ణాంకం alloc_bind_mem(AVHWFramesContext *hwfc, AVVk_చట్రం *f,
                          శూన్య *alloc_pnext, size_t alloc_pnext_stride)
{
    పూర్ణాంకం img_cnt = 0, err;
    Vk_ఫలితం ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Bind_Image_జ్ఞాపకం_Info bind_info[AV_అంకె_దత్తాంశం_సూచికలు] = { { 0 } };

    అయితే (f->img[img_cnt]) {
        పూర్ణాంకం use_ded_mem;
        Vk_Image_జ్ఞాపకం_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_జ్ఞాపకం_REQUIREMENTS_INFO_2,
            .image = f->img[img_cnt],
        };
        Vk_జ్ఞాపకం_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_ALLOCATE_INFO,
            .p_తదుపరి = (శూన్య *)(((uint8_t *)alloc_pnext) + img_cnt*alloc_pnext_stride),
        };
        Vk_జ్ఞాపకం_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_REQUIREMENTS,
        };
        Vk_జ్ఞాపకం_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_REQUIREMENTS_2,
            .p_తదుపరి = &ded_req,
        };

        vk->Get_Image_జ్ఞాపకం_Requirements2(hwctx->act_dev, &req_desc, &req);

        av_log(hwfc, AV_LOG_TRACE,
               "plane %d: driver reports prefersDedicatedAllocation=%i requiresDedicatedAllocation=%i\n",
               img_cnt, ded_req.prefers_Dedicated_కేటాయింపు, ded_req.requires_Dedicated_కేటాయింపు);

        ఒకవేళ (f->tiling == VK_IMAGE_TILING_రేఖీయ)
            req.జ్ఞాపకం_Requirements.కొలత = FFALIGN(req.జ్ఞాపకం_Requirements.కొలత,
                                                  p->props.properties.limits.min_జ్ఞాపకం_Map_Alignment);

        /* In case the implementation prefers/requires dedicated allocation */
        use_ded_mem = ded_req.prefers_Dedicated_కేటాయింపు |
                      ded_req.requires_Dedicated_కేటాయింపు;
        ఒకవేళ (((Vulkan_చట్రాలు_Priv *)hwfc->hwctx)->export_requires_dedicated)
            use_ded_mem = 1;
        ఒకవేళ (use_ded_mem)
            ded_alloc.image = f->img[img_cnt];

        /* Allocate memory */
        ఒకవేళ ((err = alloc_mem(ctx, &req.జ్ఞాపకం_Requirements,
                             f->tiling == VK_IMAGE_TILING_రేఖీయ ?
                             VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు :
                             VK_జ్ఞాపకం_PROPERTY_DEVICE_LOCAL_బిట్టు,
                             use_ded_mem ? &ded_alloc : (శూన్య *)ded_alloc.p_తదుపరి,
                             &f->flags, &f->mem[img_cnt])))
            తిరిగి err;

        f->కొలత[img_cnt] = req.జ్ఞాపకం_Requirements.కొలత;
        bind_info[img_cnt].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_జ్ఞాపకం_INFO;
        bind_info[img_cnt].image  = f->img[img_cnt];
        bind_info[img_cnt].జ్ఞాపకం = f->mem[img_cnt];

        img_cnt++;
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, img_cnt, bind_info);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

గణన Prep_బహుళకం {
    PREP_బహుళకం_GENERAL,
    PREP_బహుళకం_WRITE,
    PREP_బహుళకం_EXTERNAL_EXPORT,
    PREP_బహుళకం_EXTERNAL_IMPORT,
    PREP_బహుళకం_DECODING_DST,
    PREP_బహుళకం_DECODING_DPB,
    PREP_బహుళకం_ENCODING_DPB,
};

స్థిర శూన్య switch_new_props(గణన Prep_బహుళకం pmode, VkImageLayout *new_layout,
                             VkAccessFlags2 *new_access)
{
    ఎంపిక (pmode) {
    స్థితి PREP_బహుళకం_GENERAL:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_WRITE:
        *new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        *new_access = VK_ACCESS_TRANSFER_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_EXTERNAL_IMPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_జ్ఞాపకం_READ_బిట్టు | VK_ACCESS_జ్ఞాపకం_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_EXTERNAL_EXPORT:
        *new_layout = VK_IMAGE_LAYOUT_GENERAL;
        *new_access = VK_ACCESS_జ్ఞాపకం_READ_బిట్టు | VK_ACCESS_జ్ఞాపకం_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_DECODING_DST:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
        *new_access = VK_ACCESS_TRANSFER_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_DECODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_బిట్టు | VK_ACCESS_TRANSFER_WRITE_బిట్టు;
        ఆపు;
    స్థితి PREP_బహుళకం_ENCODING_DPB:
        *new_layout = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR;
        *new_access = VK_ACCESS_TRANSFER_READ_బిట్టు | VK_ACCESS_TRANSFER_WRITE_బిట్టు;
        ఆపు;
    }
}

స్థిర పూర్ణాంకం switch_layout(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_చట్రం *చట్రం, గణన Prep_బహుళకం pmode)
{
    పూర్ణాంకం err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_Image_జ్ఞాపకం_Barrier2 img_bar[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం nb_img_bar = 0;

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    uint32_t dst_qf = p->nb_img_qfs > 1 ? VK_వరుస_FAMILY_IGNORED : p->img_qfs[0];
    VkPipelineStageFlagBits2 src_stage = VK_PIPELINE_STAGE_2_NONE;
    ఒకవేళ (pmode == PREP_బహుళకం_EXTERNAL_EXPORT) {
        dst_qf     = VK_వరుస_FAMILY_EXTERNAL_KHR;
        src_stage  = VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు;
    }

    /* This is dirty - but it works. The vulkan.c dependency system doesn't
     * free non-refcounted frames, and non-refcounted hardware frames cannot
     * happen anywhere outside of here. */
    AVBufferRef tmp_ref = {
        .దత్తాంశం = (uint8_t *)hwfc,
    };
    AVFrame tmp_చట్రం = {
        .దత్తాంశం[0] = (uint8_t *)చట్రం,
        .hw_చట్రాలు_ctx = &tmp_ref,
    };

    Vk_Command_బఫరు cmd_buf;
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, ectx);
    cmd_buf = exec->buf;
    err = ff_vk_exec_ప్రారంభం(&p->vkctx, exec);
    ఒకవేళ (err < 0)
        తిరిగి err;

    /* NONE does not block any stage, so this queue's layout transition
     * races a decode write submitted on the video queue. */
    err = ff_vk_exec_కూడు_dep_చట్రం(&p->vkctx, exec, &tmp_చట్రం,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు);
    ఒకవేళ (err < 0)
        తిరిగి err;

    ff_vk_చట్రం_barrier(&p->vkctx, exec, &tmp_చట్రం, img_bar, &nb_img_bar,
                        src_stage,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                        new_access, new_layout, dst_qf);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_జ్ఞాపకం_Barriers = img_bar,
            .image_జ్ఞాపకం_Barrier_లెక్క = nb_img_bar,
        });

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ఒకవేళ (err < 0)
        తిరిగి err;

    /* Drops the stack-based frame above from the dependency list */
    ff_vk_exec_wait(&p->vkctx, exec);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం switch_layout_host(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                              AVVk_చట్రం *చట్రం, గణన Prep_బహుళకం pmode)
{
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    VkHostImageLayoutTransitionInfoEXT layout_change[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం nb_images = ff_vk_లెక్క_images(చట్రం);

    VkImageLayout new_layout;
    VkAccessFlags2 new_access;
    switch_new_props(pmode, &new_layout, &new_access);

    పూర్ణాంకం i;
    కొరకు (i = 0; i < p->vkctx.host_image_props.copy_Dst_Layout_లెక్క; i++) {
        ఒకవేళ (p->vkctx.host_image_props.pCopyDstLayouts[i] == new_layout)
            ఆపు;
    }
    ఒకవేళ (i == p->vkctx.host_image_props.copy_Dst_Layout_లెక్క)
        తిరిగి AVERROR(ENOTSUP);

    కొరకు (i = 0; i < nb_images; i++) {
        layout_change[i] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = చట్రం->img[i],
            .oldLayout = చట్రం->layout[i],
            .newLayout = new_layout,
            .subresourceRange.aspect_ముసుగు = VK_IMAGE_ASPECT_COLOR_బిట్టు,
            .subresourceRange.layer_లెక్క = 1,
            .subresourceRange.level_లెక్క = 1,
        };
        చట్రం->layout[i] = new_layout;
    }

    ret = vk->TransitionImageLayoutEXT(p->vkctx.hwctx->act_dev,
                                       nb_images, layout_change);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Unable to prepare frame: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం prepare_చట్రం(AVHWFramesContext *hwfc, FFVkExecPool *ectx,
                         AVVk_చట్రం *చట్రం, గణన Prep_బహుళకం pmode)
{
    పూర్ణాంకం err = 0;
    AVVulkan_చట్రాలు_Context *hwfc_vk = hwfc->hwctx;
    ఒకవేళ (hwfc_vk->usage & VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT &&
        (pmode != PREP_బహుళకం_EXTERNAL_EXPORT) &&
        (pmode != PREP_బహుళకం_EXTERNAL_IMPORT)) {
        err = switch_layout_host(hwfc, ectx, చట్రం, pmode);
        ఒకవేళ (err != AVERROR(ENOTSUP))
            తిరిగి err;
    }

    తిరిగి switch_layout(hwfc, ectx, చట్రం, pmode);
}

స్థిర అంతఃవరుస శూన్య get_plane_wh(uint32_t *w, uint32_t *h, గణన AVPixelFormat format,
                                పూర్ణాంకం చట్రం_w, పూర్ణాంకం చట్రం_h, పూర్ణాంకం plane)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(format);

    /* Currently always true unless gray + alpha support is added */
    ఒకవేళ (!plane || (plane == 3) || desc->flags & AV_PIX_FMT_FLAG_RGB ||
        !(desc->flags & AV_PIX_FMT_FLAG_PLANAR)) {
        *w = చట్రం_w;
        *h = చట్రం_h;
        తిరిగి;
    }

    *w = AV_CEIL_RSHIFT(చట్రం_w, desc->log2_chroma_w);
    *h = AV_CEIL_RSHIFT(చట్రం_h, desc->log2_chroma_h);
}

స్థిర పూర్ణాంకం create_చట్రం(AVHWFramesContext *hwfc, AVVk_చట్రం **చట్రం,
                        VkImageTiling tiling, Vk_Image_Usage_Flag_బిట్లు usage,
                        VkImageCreateFlags flags, పూర్ణాంకం nb_layers,
                        శూన్య *create_pnext)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    AVVulkan_చట్రాలు_Context *hwfc_vk = hwfc->hwctx;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    AVVk_చట్రం *f;

    VkSemaphoreTypeCreateInfo sem_type_info = {
        .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initial_విలువ  = 0,
    };
    VkSemaphoreCreateInfo sem_spawn = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .p_తదుపరి = &sem_type_info,
    };

    VkExportSemaphoreCreateInfo ext_sem_info_opaque = {
        .sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
#నిర్వచితమైతే _WIN32
        .handleTypes = IsWindows8OrGreater()
            ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_బిట్టు
            : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_బిట్టు,
#లేకపోతే
        .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_బిట్టు,
#అయితే_ముగింపు
    };

    /* Check if exporting is supported before chaining any structs */
    ఒకవేళ (p->ext_sem_props_opaque.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_బిట్టు) {
        ఒకవేళ (p->vkctx.extensions & (FF_VK_EXT_EXTERNAL_WIN32_SEM | FF_VK_EXT_EXTERNAL_FD_SEM))
            ff_vk_link_struct(&sem_type_info, &ext_sem_info_opaque);
    }

    f = av_vk_చట్రం_alloc();
    ఒకవేళ (!f) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        తిరిగి AVERROR(ENOMEM);
    }

    // TODO: check width and height for alignment in case of multiplanar (must be mod-2 if subsampled)

    /* Create the images */
    కొరకు (పూర్ణాంకం i = 0; (hwfc_vk->format[i] != VK_FORMAT_UNDEFINED); i++) {
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_తదుపరి                 = create_pnext,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = hwfc_vk->format[i],
            .extent.లోతు          = 1,
            .mip_స్థాయిలు             = 1,
            .arrayLayers           = nb_layers,
            .flags                 = flags,
            .tiling                = tiling,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage                 = usage,
            .samples               = VK_SAMPLE_లెక్క_1_బిట్టు,
            .p_వరుస_Family_Indices   = p->img_qfs,
            .వరుస_Family_సూచీ_లెక్క = p->nb_img_qfs,
            .sharing_బహుళకం           = p->nb_img_qfs > 1 ? VK_SHARING_బహుళకం_CONCURRENT :
                                                         VK_SHARING_బహుళకం_EXCLUSIVE,
        };

        get_plane_wh(&create_info.extent.వెడల్పు, &create_info.extent.ఎత్తు,
                     hwfc->sw_format, hwfc->వెడల్పు, hwfc->ఎత్తు, i);

        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            వెళ్ళు fail;
        }

        /* Create semaphore */
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }

        f->వరుస_family[i] = p->nb_img_qfs > 1 ? VK_వరుస_FAMILY_IGNORED : p->img_qfs[0];
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_విలువ[i] = 0;
    }

    f->flags     = 0x0;
    f->tiling    = tiling;

    *చట్రం = f;
    తిరిగి 0;

fail:
    vulkan_చట్రం_free(hwfc, f);
    తిరిగి err;
}

/* Checks if an export flag is enabled, and if it is ORs it with *iexp */
స్థిర శూన్య try_export_flags(AVHWFramesContext *hwfc,
                             Vk_External_జ్ఞాపకం_Handle_Type_Flags *comp_handle_types,
                             Vk_External_జ్ఞాపకం_Handle_Type_Flags *iexp,
                             Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు ఘాతాంకం)
{
    Vk_ఫలితం ret;
    AVVulkan_చట్రాలు_Context *hwctx = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    స్థిరరాశి VkImageDrmFormatModifierListCreateInfoEXT *drm_mod_info =
        ff_vk_కనుగొను_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    పూర్ణాంకం has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && drm_mod_info;
    పూర్ణాంకం nb_mods;

    VkExternalImageFormatProperties eprops = {
        .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
    };
    VkImageFormatProperties2 props = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .p_తదుపరి = &eprops,
    };
    VkPhysicalDeviceImageDrmFormatModifierInfoEXT phy_dev_mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_తదుపరి = ఖాళీ,
        .p_వరుస_Family_Indices   = p->img_qfs,
        .వరుస_Family_సూచీ_లెక్క = p->nb_img_qfs,
        .sharing_బహుళకం           = p->nb_img_qfs > 1 ? VK_SHARING_బహుళకం_CONCURRENT :
                                                     VK_SHARING_బహుళకం_EXCLUSIVE,
    };
    VkPhysicalDeviceExternalImageFormatInfo enext = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
        .handleType = ఘాతాంకం,
        .p_తదుపరి = has_mods ? &phy_dev_mod_info : ఖాళీ,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .p_తదుపరి  = !ఘాతాంకం ? ఖాళీ : &enext,
        .format = hwctx->format[0],
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && has_mods) ?
                  (hwctx->img_flags) : hwctx->img_flags ? hwctx->img_flags : (VkImageCreateFlags)(VK_IMAGE_CREATE_ALIAS_బిట్టు),
    };

    nb_mods = has_mods ? drm_mod_info->drm_Format_Modifier_లెక్క : 1;
    కొరకు (పూర్ణాంకం i = 0; i < nb_mods; i++) {
        ఒకవేళ (has_mods)
            phy_dev_mod_info.drmFormatModifier = drm_mod_info->pDrmFormatModifiers[i];

        ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                        &pinfo, &props);

        ఒకవేళ (has_mods)
            av_log(hwfc, AV_LOG_VERBOSE, "GetPhysicalDeviceImageFormatProperties2: mod[%d]=0x%llx -> %s\n",
                   i, (గుర్తులేని దీర్ఘ దీర్ఘ)phy_dev_mod_info.drmFormatModifier,
                   ret == VK_SUCCESS ? "OK" : "FAIL");
        ఒకవేళ (ret == VK_SUCCESS) {
            *iexp |= ఘాతాంకం;
            *comp_handle_types |= eprops.external_జ్ఞాపకం_Properties.compatibleHandleTypes;
            ఒకవేళ (ఘాతాంకం == VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT) {
                Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
                fp->export_requires_dedicated = !!(eprops.external_జ్ఞాపకం_Properties.external_జ్ఞాపకం_Features &
                                                  VK_EXTERNAL_జ్ఞాపకం_FEATURE_DEDICATED_ONLY_బిట్టు);
            }
        }
    }
}

/* Computes the external memory handle types for the frame context. */
స్థిర శూన్య get_export_handle_types(AVHWFramesContext *hwfc,
                                    Vk_External_జ్ఞాపకం_Handle_Type_Flags *comp_handle_types,
                                    Vk_External_జ్ఞాపకం_Handle_Type_Flags *export_types)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    av_వాడని AVVulkan_చట్రాలు_Context *hwctx = &((Vulkan_చట్రాలు_Priv *)hwfc->hwctx)->p;

    *comp_handle_types = 0x0;
    *export_types = 0x0;

#నిర్వచితమైతే _WIN32
    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_జ్ఞాపకం)
        try_export_flags(hwfc, comp_handle_types, export_types, IsWindows8OrGreater()
                             ? VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32_బిట్టు
                             : VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32_KMT_బిట్టు);
#లేకపోతే
    ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_జ్ఞాపకం) &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_FD_బిట్టు);

    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_DMABUF_జ్ఞాపకం &&
        hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT)
        try_export_flags(hwfc, comp_handle_types, export_types,
                         VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT);
#అయితే_ముగింపు
}

స్థిర AVBufferRef *vulkan_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    పూర్ణాంకం err;
    AVVk_చట్రం *f;
    AVBufferRef *avbuf = ఖాళీ;
    AVHWFramesContext *hwfc = opaque;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkan_చట్రాలు_Context *hwctx = &fp->p;
    Vk_External_జ్ఞాపకం_Handle_Type_Flags e;
    Vk_Export_జ్ఞాపకం_Allocate_Info eminfo[AV_అంకె_దత్తాంశం_సూచికలు];

    Vk_External_జ్ఞాపకం_Image_Create_Info eiinfo = {
        .sType       = VK_STRUCTURE_TYPE_EXTERNAL_జ్ఞాపకం_IMAGE_CREATE_INFO,
        .p_తదుపరి       = hwctx->create_pnext,
    };

    get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);

    కొరకు (పూర్ణాంకం i = 0; i < av_pix_fmt_లెక్క_planes(hwfc->sw_format); i++) {
        eminfo[i].sType       = VK_STRUCTURE_TYPE_EXPORT_జ్ఞాపకం_ALLOCATE_INFO;
        eminfo[i].p_తదుపరి       = hwctx->alloc_pnext[i];
        eminfo[i].handleTypes = e;
    }

    err = create_చట్రం(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers,
                       eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext);
    ఒకవేళ (err) {
        av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed: create_frame failed: %d\n", err);
        తిరిగి ఖాళీ;
    }

    err = alloc_bind_mem(hwfc, f, eminfo, పరిమాణం(*eminfo));
    ఒకవేళ (err)
        వెళ్ళు fail;

    ఒకవేళ ( (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_బిట్టు_KHR) &&
        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR))
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_DECODING_DPB);
    లేకపోతే ఒకవేళ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR)
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_DECODING_DST);
    లేకపోతే ఒకవేళ (hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_బిట్టు_KHR)
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_ENCODING_DPB);
    లేకపోతే ఒకవేళ (hwctx->usage & VK_IMAGE_USAGE_TRANSFER_DST_బిట్టు)
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_WRITE);
    లేకపోతే
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_GENERAL);
    ఒకవేళ (err)
        వెళ్ళు fail;

    avbuf = av_బఫరు_create((uint8_t *)f, పరిమాణం(AVVk_చట్రం),
                             vulkan_చట్రం_free_cb, hwfc, 0);
    ఒకవేళ (!avbuf)
        వెళ్ళు fail;

    తిరిగి avbuf;

fail:
    av_log(hwfc, AV_LOG_ERROR, "vulkan_pool_alloc failed with error %d\n", err);
    vulkan_చట్రం_free(hwfc, f);
    తిరిగి ఖాళీ;
}

స్థిర శూన్య తాళం_చట్రం(AVHWFramesContext *fc, AVVk_చట్రం *vkf)
{
    pthread_mutex_తాళం(&vkf->అంతర్గత->update_mutex);
}

స్థిర శూన్య unlock_చట్రం(AVHWFramesContext *fc, AVVk_చట్రం *vkf)
{
    pthread_mutex_unlock(&vkf->అంతర్గత->update_mutex);
}

స్థిర శూన్య vulkan_చట్రాలు_uninit(AVHWFramesContext *hwfc)
{
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;

    ఒకవేళ (fp->modifier_info) {
        ఒకవేళ (fp->modifier_info->pDrmFormatModifiers)
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
స్థిర పూర్ణాంకం vulkan_host_transfer_usable(AVHWFramesContext *hwfc)
{
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkan_చట్రాలు_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vk_ఫలితం ret;

    /* NVIDIA's host image copy resolves every plane's parameters as if it were
     * plane 0, so every plane but the first is corrupted on both upload and
     * download. Frames with one image per plane are unaffected.
     */
    స్థిరరాశి నిర్మాణం FFVk_Format_నమోదు *fmt = vk_కనుగొను_format_నమోదు(hwfc->sw_format);
    ఒకవేళ (p->dprops.driverID == VK_DRIVER_ID_NVIDIA_PROPRIETARY &&
        fmt && fmt->vk_planes > 1 && hwctx->format[0] == fmt->vkf) {
        av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
               "NVIDIA drivers mishandle multi-plane images\n");
        తిరిగి 0;
    }

    స్థిరరాశి VkImageDrmFormatModifierListCreateInfoEXT *mod_list =
        ff_vk_కనుగొను_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT);
    పూర్ణాంకం has_mods = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                   mod_list && mod_list->drm_Format_Modifier_లెక్క;
    పూర్ణాంకం nb_mods = has_mods ? mod_list->drm_Format_Modifier_లెక్క : 1;

    /* Without a modifier list the final modifier is not knowable here. */
    ఒకవేళ (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT && !has_mods)
        తిరిగి 0;

    VkPhysicalDeviceImageDrmFormatModifierInfoEXT mod_info = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
        .p_వరుస_Family_Indices   = p->img_qfs,
        .వరుస_Family_సూచీ_లెక్క = p->nb_img_qfs,
        .sharing_బహుళకం           = p->nb_img_qfs > 1 ? VK_SHARING_బహుళకం_CONCURRENT :
                                                     VK_SHARING_బహుళకం_EXCLUSIVE,
    };
    VkPhysicalDeviceImageFormatInfo2 pinfo = {
        .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .type   = VK_IMAGE_TYPE_2D,
        .tiling = hwctx->tiling,
        .usage  = hwctx->usage,
        .flags  = hwctx->img_flags,
    };

    ఒకవేళ (has_mods)
        ff_vk_link_struct(&pinfo, &mod_info);

    VkVideoProfileListInfoKHR profile_list;
    స్థిరరాశి VkVideoProfileListInfoKHR *pl =
        ff_vk_కనుగొను_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
    ఒకవేళ (pl) {
        profile_list = *pl;
        profile_list.p_తదుపరి = ఖాళీ;
        ff_vk_link_struct(&pinfo, &profile_list);
    }

    VkImageFormatListCreateInfo format_list;
    స్థిరరాశి VkImageFormatListCreateInfo *fl =
        ff_vk_కనుగొను_struct(hwctx->create_pnext,
                          VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO);
    ఒకవేళ (fl) {
        format_list = *fl;
        format_list.p_తదుపరి = ఖాళీ;
        ff_vk_link_struct(&pinfo, &format_list);
    }

    /* The same usage is applied to the images of every plane, so each plane
     * format has to support host transfers for the usage to be usable. */
    కొరకు (పూర్ణాంకం i = 0; i < AV_అంకె_దత్తాంశం_సూచికలు &&
                    hwctx->format[i] != VK_FORMAT_UNDEFINED; i++) {
        pinfo.format = hwctx->format[i];

        /* The driver is free to pick any modifier from the list, so all of
         * them have to be compatible. */
        కొరకు (పూర్ణాంకం j = 0; j < nb_mods; j++) {
            VkHostImageCopyDevicePerformanceQueryEXT perf = {
                .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT,
            };
            VkImageFormatProperties2 props = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
                .p_తదుపరి = &perf,
            };

            ఒకవేళ (has_mods)
                mod_info.drmFormatModifier = mod_list->pDrmFormatModifiers[j];

            ret = vk->GetPhysicalDeviceImageFormatProperties2(dev_hwctx->phys_dev,
                                                              &pinfo, &props);
            ఒకవేళ (ret != VK_SUCCESS) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i is not supported: %s\n",
                       pinfo.format, ff_vk_ret2str(ret));
                తిరిగి 0;
            }

            ఒకవేళ (!perf.optimalDeviceAccess) {
                av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                       "format %i has no optimal device access (identical "
                       "memory layout: %i)\n",
                       pinfo.format, perf.identical_జ్ఞాపకం_Layout);
                తిరిగి 0;
            }
        }
    }

    ఒకవేళ (!p->vkctx.host_image_props.identical_జ్ఞాపకం_Type_Requirements) {
        పూర్ణాంకం సూచీ;
        Vk_External_జ్ఞాపకం_Handle_Type_Flags e;
        Vk_External_జ్ఞాపకం_Image_Create_Info eiinfo = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_జ్ఞాపకం_IMAGE_CREATE_INFO,
            .p_తదుపరి       = hwctx->create_pnext,
        };
        get_export_handle_types(hwfc, &eiinfo.handleTypes, &e);
        VkImageCreateInfo create_info = {
            .sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_తదుపరి       = eiinfo.handleTypes ? &eiinfo : hwctx->create_pnext,
            .imageType   = VK_IMAGE_TYPE_2D,
            .format      = hwctx->format[0],
            .extent      = { hwfc->వెడల్పు, hwfc->ఎత్తు, 1 },
            .mip_స్థాయిలు   = 1,
            .arrayLayers = hwctx->nb_layers,
            .flags       = hwctx->img_flags,
            .tiling      = hwctx->tiling,
            .usage       = hwctx->usage,
            .samples     = VK_SAMPLE_లెక్క_1_బిట్టు,
            .p_వరుస_Family_Indices   = p->img_qfs,
            .వరుస_Family_సూచీ_లెక్క = p->nb_img_qfs,
            .sharing_బహుళకం           = p->nb_img_qfs > 1 ? VK_SHARING_బహుళకం_CONCURRENT :
                                                         VK_SHARING_బహుళకం_EXCLUSIVE,
        };
        Vk_Device_Image_జ్ఞాపకం_Requirements req_info = {
            .sType       = VK_STRUCTURE_TYPE_DEVICE_IMAGE_జ్ఞాపకం_REQUIREMENTS,
            .pCreateInfo = &create_info,
            .planeAspect = hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT ?
                           VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_0_బిట్టు_EXT : 0,
        };
        Vk_జ్ఞాపకం_Requirements2 req = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_REQUIREMENTS_2,
        };

        vk->Get_Device_Image_జ్ఞాపకం_Requirements(dev_hwctx->act_dev, &req_info, &req);
        /* Check that alloc_bind_mem() will find a compatible memory type. */
        Vk_జ్ఞాపకం_Property_Flags req_flags = hwctx->tiling == VK_IMAGE_TILING_రేఖీయ ?
                                          VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు :
                                          VK_జ్ఞాపకం_PROPERTY_DEVICE_LOCAL_బిట్టు;
        కొరకు (సూచీ = 0; సూచీ < p->mprops.జ్ఞాపకం_Type_లెక్క; సూచీ++) {
            ఒకవేళ (!(req.జ్ఞాపకం_Requirements.జ్ఞాపకం_Type_బిట్లు & (1U << సూచీ)))
                కొనసాగు;
            ఒకవేళ ((p->mprops.జ్ఞాపకం_Types[సూచీ].propertyFlags & req_flags) == req_flags)
                ఆపు;
        }
        ఒకవేళ (సూచీ == p->mprops.జ్ఞాపకం_Type_లెక్క) {
            av_log(hwfc, AV_LOG_VERBOSE, "Disabling host image transfers: "
                   "no compatible memory type\n");
            తిరిగి 0;
        }
    }

    తిరిగి 1;
}

స్థిర పూర్ణాంకం vulkan_చట్రాలు_init(AVHWFramesContext *hwfc)
{
    పూర్ణాంకం err;
    AVVk_చట్రం *f;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkan_చట్రాలు_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *dev_hwctx = &p->p;
    VkImageUsageFlags supported_usage;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    స్థిరరాశి నిర్మాణం FFVk_Format_నమోదు *fmt;
    స్థిరరాశి AVPixFmtDescriptor *desc;
    పూర్ణాంకం disable_multiplane = p->disable_multiplane ||
                             (hwctx->flags & AV_VK_చట్రం_FLAG_DISABLE_MULTIPLANE);
    పూర్ణాంకం is_lone_dpb = ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_బిట్టు_KHR) ||
                       ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_బిట్టు_KHR) &&
                        !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DST_బిట్టు_KHR)));

    /* Defaults */
    ఒకవేళ (!hwctx->nb_layers)
        hwctx->nb_layers = 1;

    /* VK_IMAGE_TILING_OPTIMAL == 0, can't check for it really */
    ఒకవేళ (p->use_రేఖీయ_images &&
        (hwctx->tiling != VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT))
        hwctx->tiling = VK_IMAGE_TILING_రేఖీయ;


    fmt = vk_కనుగొను_format_నమోదు(hwfc->sw_format);
    ఒకవేళ (!fmt) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported pixel format: %s!\n",
               av_get_pix_fmt_name(hwfc->sw_format));
        తిరిగి AVERROR(ENOTSUP);
    }

    /* _420 and _422 formats need even dimensions, use one image per plane */
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    ఒకవేళ ((hwfc->వెడల్పు  & ((1 << desc->log2_chroma_w) - 1)) ||
        (hwfc->ఎత్తు & ((1 << desc->log2_chroma_h) - 1)))
        disable_multiplane = 1;

    ఒకవేళ (hwctx->format[0] != VK_FORMAT_UNDEFINED) {
        ఒకవేళ (hwctx->format[0] != fmt->vkf) {
            కొరకు (పూర్ణాంకం i = 0; i < fmt->nb_images_fallback; i++) {
                ఒకవేళ (hwctx->format[i] != fmt->fallback[i]) {
                    av_log(hwfc, AV_LOG_ERROR, "Incompatible Vulkan format given "
                           "for the current sw_format %s!\n",
                           av_get_pix_fmt_name(hwfc->sw_format));
                    తిరిగి AVERROR(EINVAL);
                }
            }
        }

        /* Check if the sw_format itself is supported */
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, ఖాళీ,
                                 ఖాళీ, ఖాళీ, &supported_usage, 0,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_బిట్టు));
        ఒకవేళ (err < 0) {
            av_log(hwfc, AV_LOG_ERROR, "Unsupported sw format: %s!\n",
                   av_get_pix_fmt_name(hwfc->sw_format));
            తిరిగి AVERROR(EINVAL);
        }
    } లేకపోతే {
        err = vkfmt_from_pixfmt2(hwfc->device_ctx, hwfc->sw_format,
                                 hwctx->tiling, hwctx->format, ఖాళీ,
                                 ఖాళీ, &supported_usage,
                                 disable_multiplane,
                                 !hwctx->usage ||
                                 (hwctx->usage & VK_IMAGE_USAGE_STORAGE_బిట్టు));
        ఒకవేళ (err < 0)
            తిరిగి err;
    }

    /* Lone DPB images do not need additional flags. */
    /* With DRM modifier + video profile the caller has already chosen a valid
     * usage/img_flags/chain; do not add usage or img_flags (supported_usage does
     * not consider the actual modifier or video profile). */
    పూర్ణాంకం drm_mod_with_video = (hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
                              ff_vk_కనుగొను_struct(hwctx->create_pnext,
                                                VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR));

    ఒకవేళ (!is_lone_dpb && !drm_mod_with_video) {
        /* Image usage flags */
        hwctx->usage |= supported_usage & (VK_IMAGE_USAGE_TRANSFER_DST_బిట్టు |
                                           VK_IMAGE_USAGE_TRANSFER_SRC_బిట్టు |
                                           VK_IMAGE_USAGE_STORAGE_బిట్టు      |
                                           VK_IMAGE_USAGE_SAMPLED_బిట్టు);

        /* Frames which may double as active references (coinciding decode
         * output) cannot support host transfers: decode submissions bake the
         * image layout into their barriers at record time, so a host-side
         * layout transition cannot be synchronized against them, not even
         * by the frame lock and timeline semaphore. */
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_HOST_IMAGE_COPY &&
            !(hwctx->usage & VK_IMAGE_USAGE_VIDEO_DECODE_DPB_బిట్టు_KHR))
            hwctx->usage |= supported_usage & VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT;

        /* Enables encoding of images, if supported by format and extensions */
        ఒకవేళ ((supported_usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_వరుస) &&
            (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1))
            hwctx->usage |= VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR;

        /* Image creation flags.
         * Only fill them in automatically if the image is not going to be used as
         * a DPB-only image, and we have SAMPLED/STORAGE bits set. */
        ఒకవేళ (!hwctx->img_flags) {
            పూర్ణాంకం sampleable = hwctx->usage & (VK_IMAGE_USAGE_SAMPLED_బిట్టు |
                                             VK_IMAGE_USAGE_STORAGE_బిట్టు);
            hwctx->img_flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_బిట్టు;
            ఒకవేళ (sampleable) {
                hwctx->img_flags |= VK_IMAGE_CREATE_ALIAS_బిట్టు;
                ఒకవేళ ((fmt->vk_planes > 1) && (hwctx->format[0] == fmt->vkf))
                    hwctx->img_flags |= VK_IMAGE_CREATE_EXTENDED_USAGE_బిట్టు;
            }
        }
    }

    /* If the image has an ENCODE_SRC usage, and the maintenance1
     * extension is supported, check if it has a profile list.
     * If there's no profile list, or it has no encode operations,
     * then allow creating the image with no specific profile. */
    ఒకవేళ ((hwctx->usage & VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_బిట్టు_KHR) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_ENCODE_వరుస) &&
        (p->vkctx.extensions & FF_VK_EXT_VIDEO_MAINTENANCE_1)) {
        స్థిరరాశి VkVideoProfileListInfoKHR *pl;
        pl = ff_vk_కనుగొను_struct(hwctx->create_pnext, VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR);
        ఒకవేళ (!pl) {
            hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_బిట్టు_KHR;
        } లేకపోతే {
            uint32_t i;
            కొరకు (i = 0; i < pl->profile_లెక్క; i++) {
                /* Video ops start at exactly 0x00010000 */
                ఒకవేళ (pl->pProfiles[i].videoCodecOperation & 0xFFFF0000)
                    ఆపు;
            }
            ఒకవేళ (i == pl->profile_లెక్క)
                hwctx->img_flags |= VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_బిట్టు_KHR;
        }
    }

    /* Drop the host transfer if it isn't usable for this image configuration. */
    ఒకవేళ ((hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT) &&
        !vulkan_host_transfer_usable(hwfc))
        hwctx->usage &= ~VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT;

    ఒకవేళ (!hwctx->తాళం_చట్రం)
        hwctx->తాళం_చట్రం = తాళం_చట్రం;

    ఒకవేళ (!hwctx->unlock_చట్రం)
        hwctx->unlock_చట్రం = unlock_చట్రం;

    err = ff_vk_exec_pool_init(&p->vkctx, p->compute_qf, &fp->compute_exec,
                               2, 0, 0, 0, ఖాళీ);
    ఒకవేళ (err)
        తిరిగి err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->upload_exec,
                               FF_VK_DEFAULT_EXEC_CONTEXTS, 0, 0, 0, ఖాళీ);
    ఒకవేళ (err)
        తిరిగి err;

    err = ff_vk_exec_pool_init(&p->vkctx, p->transfer_qf, &fp->download_exec,
                               2, 0, 0, 0, ఖాళీ);
    ఒకవేళ (err)
        తిరిగి err;

    /* Test to see if allocation will fail */
    err = create_చట్రం(hwfc, &f, hwctx->tiling, hwctx->usage, hwctx->img_flags,
                       hwctx->nb_layers, hwctx->create_pnext);
    ఒకవేళ (err)
        తిరిగి err;

    /* Collect `VkDrmFormatModifierPropertiesEXT` for each plane. Required for DRM export. */
    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS && hwctx->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        VkImageDrmFormatModifierPropertiesEXT drm_mod = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
        };
        err = vk->GetImageDrmFormatModifierPropertiesEXT(dev_hwctx->act_dev, f->img[0],
                                                        &drm_mod);
        ఒకవేళ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get image DRM format modifier properties");
            vulkan_చట్రం_free(hwfc, f);
            తిరిగి AVERROR_EXTERNAL;
        }
        కొరకు (పూర్ణాంకం i = 0; i < fmt->vk_planes; ++i) {
            VkDrmFormatModifierPropertiesListEXT modp;
            VkFormatProperties2 fmtp;
            VkDrmFormatModifierPropertiesEXT *mod_props = ఖాళీ;

            modp = (VkDrmFormatModifierPropertiesListEXT) {
                .sType = VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT,
            };
            fmtp = (VkFormatProperties2) {
                .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
                .p_తదుపరి = &modp,
            };

            /* query drmFormatModifierCount by keeping pDrmFormatModifierProperties NULL */
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            modp.pDrmFormatModifierProperties =
                av_calloc(modp.drm_Format_Modifier_లెక్క, పరిమాణం(*modp.pDrmFormatModifierProperties));
            ఒకవేళ (!modp.pDrmFormatModifierProperties) {
                vulkan_చట్రం_free(hwfc, f);
                తిరిగి AVERROR(ENOMEM);
            }
            vk->GetPhysicalDeviceFormatProperties2(dev_hwctx->phys_dev, fmt->fallback[i], &fmtp);

            కొరకు (uint32_t j = 0; j < modp.drm_Format_Modifier_లెక్క; ++j) {
                VkDrmFormatModifierPropertiesEXT *m = &modp.pDrmFormatModifierProperties[j];
                ఒకవేళ (m->drmFormatModifier == drm_mod.drmFormatModifier) {
                    mod_props = m;
                    ఆపు;
                }
            }

            ఒకవేళ (mod_props == ఖాళీ) {
                av_log(hwfc, AV_LOG_ERROR, "No DRM format modifier properties found for modifier 0x%016"PRIx64"\n",
                          drm_mod.drmFormatModifier);
                av_free(modp.pDrmFormatModifierProperties);
                vulkan_చట్రం_free(hwfc, f);
                తిరిగి AVERROR_EXTERNAL;
            }

            fp->drm_format_modifier_properties[i] = *mod_props;
            av_free(modp.pDrmFormatModifierProperties);
        }
    }

    vulkan_చట్రం_free(hwfc, f);

    /* If user did not specify a pool, hwfc->pool will be set to the internal one
     * in hwcontext.c just after this gets called */
    ఒకవేళ (!hwfc->pool) {
        ffhwframesctx(hwfc)->pool_అంతర్గత = av_బఫరు_pool_init2(పరిమాణం(AVVk_చట్రం),
                                                                  hwfc, vulkan_pool_alloc,
                                                                  ఖాళీ);
        ఒకవేళ (!ffhwframesctx(hwfc)->pool_అంతర్గత)
            తిరిగి AVERROR(ENOMEM);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vulkan_get_బఫరు(AVHWFramesContext *hwfc, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(hwfc->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[0] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_VULKAN;
    చట్రం->వెడల్పు   = hwfc->వెడల్పు;
    చట్రం->ఎత్తు  = hwfc->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vulkan_transfer_get_formats(AVHWFramesContext *hwfc,
                                       గణన AVHWFrameTransferDirection dir,
                                       గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts;
    పూర్ణాంకం n = 2;

#ఒకవేళ CONFIG_CUDA
    n++;
#అయితే_ముగింపు
    fmts = av_malloc_array(n, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    n = 0;
    fmts[n++] = hwfc->sw_format;
#ఒకవేళ CONFIG_CUDA
    fmts[n++] = AV_PIX_FMT_CUDA;
#అయితే_ముగింపు
    fmts[n++] = AV_PIX_FMT_NONE;

    *formats = fmts;
    తిరిగి 0;
}

#ఒకవేళ CONFIG_LIBDRM
స్థిర శూన్య vulkan_unmap_from_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    vulkan_చట్రం_free(hwfc, hwmap->priv);
}

స్థిర స్థిరరాశి నిర్మాణం {
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
#నిర్వచితమైతే DRM_FORMAT_XYUV8888
    { DRM_FORMAT_XYUV8888, VK_FORMAT_R8G8B8A8_UNORM     },
    { DRM_FORMAT_XVYU2101010, VK_FORMAT_A2R10G10B10_UNORM_PACK32 } ,
    { DRM_FORMAT_XVYU12_16161616, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 } ,
    { DRM_FORMAT_XVYU16161616, VK_FORMAT_R16G16B16A16_UNORM } ,
#అయితే_ముగింపు
};

స్థిర అంతఃవరుస VkFormat drm_గమ్యం_vulkan_fmt(uint32_t drm_fourcc)
{
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ఒకవేళ (vulkan_drm_format_map[i].drm_fourcc == drm_fourcc)
            తిరిగి vulkan_drm_format_map[i].vk_format;
    తిరిగి VK_FORMAT_UNDEFINED;
}

స్థిర పూర్ణాంకం vulkan_map_from_drm_చట్రం_desc(AVHWFramesContext *hwfc, AVVk_చట్రం **చట్రం,
                                          స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    AVVk_చట్రం *f;
    పూర్ణాంకం bind_counts = 0;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    స్థిరరాశి AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->దత్తాంశం[0];
    Vk_Bind_Image_జ్ఞాపకం_Info bind_info[AV_DRM_MAX_PLANES];
    Vk_Bind_Image_Plane_జ్ఞాపకం_Info plane_info[AV_DRM_MAX_PLANES];

    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_layers; i++) {
        ఒకవేళ (drm_గమ్యం_vulkan_fmt(desc->layers[i].format) == VK_FORMAT_UNDEFINED) {
            av_log(ctx, AV_LOG_ERROR, "Unsupported DMABUF layer format %#08x!\n",
                   desc->layers[i].format);
            తిరిగి AVERROR(EINVAL);
        }
    }

    ఒకవేళ (!(f = av_vk_చట్రం_alloc())) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate memory for AVVkFrame!\n");
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    f->tiling = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT;

    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_layers; i++) {
        స్థిరరాశి పూర్ణాంకం planes = desc->layers[i].nb_planes;

        /* Semaphore */
        VkSemaphoreTypeCreateInfo sem_type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
            .initial_విలువ  = 0,
        };
        VkSemaphoreCreateInfo sem_spawn = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_తదుపరి = &sem_type_info,
        };

        /* Image creation */
        VkSubresourceLayout ext_img_layouts[AV_DRM_MAX_PLANES];
        VkImageDrmFormatModifierExplicitCreateInfoEXT ext_img_mod_spec = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
            .drmFormatModifier = desc->objects[0].format_modifier,
            .drm_Format_Modifier_Plane_లెక్క = planes,
            .pPlaneLayouts = (స్థిరరాశి VkSubresourceLayout *)&ext_img_layouts,
        };
        Vk_External_జ్ఞాపకం_Image_Create_Info ext_img_spec = {
            .sType       = VK_STRUCTURE_TYPE_EXTERNAL_జ్ఞాపకం_IMAGE_CREATE_INFO,
            .p_తదుపరి       = &ext_img_mod_spec,
            .handleTypes = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT,
        };
        VkImageCreateInfo create_info = {
            .sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .p_తదుపరి                 = &ext_img_spec,
            .imageType             = VK_IMAGE_TYPE_2D,
            .format                = drm_గమ్యం_vulkan_fmt(desc->layers[i].format),
            .extent.లోతు          = 1,
            .mip_స్థాయిలు             = 1,
            .arrayLayers           = 1,
            .flags                 = 0x0,
            .tiling                = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT,
            .initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED, /* specs say so */
            .usage                 = 0x0, /* filled in below */
            .samples               = VK_SAMPLE_లెక్క_1_బిట్టు,
            .p_వరుస_Family_Indices   = p->img_qfs,
            .వరుస_Family_సూచీ_లెక్క = p->nb_img_qfs,
            .sharing_బహుళకం           = p->nb_img_qfs > 1 ? VK_SHARING_బహుళకం_CONCURRENT :
                                                         VK_SHARING_బహుళకం_EXCLUSIVE,
        };

        /* The DRM fourcc fixes a specific channel order (f.ex ARGB8888 maps to
         * B8G8R8A8), but image views are always created from the destination
         * frames context sw_format (like how bgra maps to R8G8B8A8). For a
         * single plane layer, create the image with the sw_format's compatible
         * VkFormat so the image and its views agree without a mutable format
         * list, the format query below validates this */
        ఒకవేళ (planes == 1) {
            స్థిరరాశి VkFormat *sw_vkfmts = av_vkfmt_from_pixfmt(hwfc->sw_format);
            ఒకవేళ (sw_vkfmts && sw_vkfmts[i] != VK_FORMAT_UNDEFINED)
                create_info.format = sw_vkfmts[i];
        }

        /* Image format verification */
        VkExternalImageFormatProperties ext_props = {
            .sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHR,
        };
        VkImageFormatProperties2 props_ret = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
            .p_తదుపరి = &ext_props,
        };
        VkPhysicalDeviceImageDrmFormatModifierInfoEXT props_drm_mod = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT,
            .drmFormatModifier = ext_img_mod_spec.drmFormatModifier,
            .p_వరుస_Family_Indices = create_info.p_వరుస_Family_Indices,
            .వరుస_Family_సూచీ_లెక్క = create_info.వరుస_Family_సూచీ_లెక్క,
            .sharing_బహుళకం = create_info.sharing_బహుళకం,
        };
        VkPhysicalDeviceExternalImageFormatInfo props_ext = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO,
            .p_తదుపరి = &props_drm_mod,
            .handleType = ext_img_spec.handleTypes,
        };
        VkPhysicalDeviceImageFormatInfo2 fmt_props;

        ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
            create_info.usage |= VK_IMAGE_USAGE_SAMPLED_బిట్టు |
                                 VK_IMAGE_USAGE_TRANSFER_SRC_బిట్టు;
        ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
            create_info.usage |= VK_IMAGE_USAGE_STORAGE_బిట్టు |
                                 VK_IMAGE_USAGE_TRANSFER_DST_బిట్టు;

        fmt_props = (VkPhysicalDeviceImageFormatInfo2) {
            .sType  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
            .p_తదుపరి  = &props_ext,
            .format = create_info.format,
            .type   = create_info.imageType,
            .tiling = create_info.tiling,
            .usage  = create_info.usage,
            .flags  = create_info.flags,
        };

        /* Check if importing is possible for this combination of parameters */
        ret = vk->GetPhysicalDeviceImageFormatProperties2(hwctx->phys_dev,
                                                          &fmt_props, &props_ret);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Cannot map DRM frame to Vulkan: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }

        /* Set the image width/height */
        get_plane_wh(&create_info.extent.వెడల్పు, &create_info.extent.ఎత్తు,
                     hwfc->sw_format, src->వెడల్పు, src->ఎత్తు, i);

        /* Set the subresource layout based on the layer properties */
        కొరకు (పూర్ణాంకం j = 0; j < planes; j++) {
            ext_img_layouts[j].స్థానభ్రంశం     = desc->layers[i].planes[j].స్థానభ్రంశం;
            ext_img_layouts[j].అడ్డువరుస_Pitch_2   = desc->layers[i].planes[j].pitch;
            ext_img_layouts[j].కొలత       = 0; /* The specs say so for all 3 */
            ext_img_layouts[j].arrayPitch = 0;
            ext_img_layouts[j].లోతు_Pitch = 0;
        }

        /* Create image */
        ret = vk->CreateImage(hwctx->act_dev, &create_info,
                              hwctx->alloc, &f->img[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(ctx, AV_LOG_ERROR, "Image creation failure: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR(EINVAL);
            వెళ్ళు fail;
        }

        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                  hwctx->alloc, &f->sem[i]);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            వెళ్ళు fail;
        }

        f->వరుస_family[i] = VK_వరుస_FAMILY_EXTERNAL;
        f->layout[i] = create_info.initialLayout;
        f->access[i] = 0x0;
        f->sem_విలువ[i] = 0;
    }

    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_layers; i++) {
        /* Memory requirements */
        Vk_Image_జ్ఞాపకం_Requirements_Info2 req_desc = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_జ్ఞాపకం_REQUIREMENTS_INFO_2,
            .image = f->img[i],
        };
        Vk_జ్ఞాపకం_Dedicated_Requirements ded_req = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_REQUIREMENTS,
        };
        Vk_జ్ఞాపకం_Requirements2 req2 = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_REQUIREMENTS_2,
            .p_తదుపరి = &ded_req,
        };

        /* Allocation/importing */
        Vk_జ్ఞాపకం_Fd_Properties_KHR fdmp = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_FD_PROPERTIES_KHR,
        };
        /* This assumes that a layer will never be constructed from multiple
         * objects. If that was to happen in the real world, this code would
         * need to import each plane separately.
         */
        Vk_Import_జ్ఞాపకం_Fd_Info_KHR idesc = {
            .sType      = VK_STRUCTURE_TYPE_IMPORT_జ్ఞాపకం_FD_INFO_KHR,
            .fd         = dup(desc->objects[desc->layers[i].planes[0].object_సూచీ].fd),
            .handleType = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT,
        };
        Vk_జ్ఞాపకం_Dedicated_Allocate_Info ded_alloc = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_DEDICATED_ALLOCATE_INFO,
            .p_తదుపరి = &idesc,
            .image = req_desc.image,
        };

        /* Get object properties */
        ret = vk->Get_జ్ఞాపకం_Fd_Properties_KHR(hwctx->act_dev,
                                           VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT,
                                           idesc.fd, &fdmp);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to get FD properties: %s\n",
                   ff_vk_ret2str(ret));
            err = AVERROR_EXTERNAL;
            close(idesc.fd);
            వెళ్ళు fail;
        }

        vk->Get_Image_జ్ఞాపకం_Requirements2(hwctx->act_dev, &req_desc, &req2);

        /* Only a single bit must be set, not a range, and it must match */
        req2.జ్ఞాపకం_Requirements.జ్ఞాపకం_Type_బిట్లు = fdmp.జ్ఞాపకం_Type_బిట్లు;

        err = alloc_mem(ctx, &req2.జ్ఞాపకం_Requirements,
                        VK_జ్ఞాపకం_PROPERTY_DEVICE_LOCAL_బిట్టు,
                        (ded_req.prefers_Dedicated_కేటాయింపు ||
                         ded_req.requires_Dedicated_కేటాయింపు) ?
                            &ded_alloc : ded_alloc.p_తదుపరి,
                        &f->flags, &f->mem[i]);
        ఒకవేళ (err) {
            close(idesc.fd);
            వెళ్ళు fail;
        }

        f->కొలత[i] = req2.జ్ఞాపకం_Requirements.కొలత;
    }

    కొరకు (పూర్ణాంకం i = 0; i < desc->nb_layers; i++) {
        స్థిరరాశి పూర్ణాంకం planes = desc->layers[i].nb_planes;
        కొరకు (పూర్ణాంకం j = 0; j < planes; j++) {
            Vk_Image_Aspect_Flag_బిట్లు aspect = j == 0 ? VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_0_బిట్టు_EXT :
                                           j == 1 ? VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_1_బిట్టు_EXT :
                                                    VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_2_బిట్టు_EXT;

            plane_info[bind_counts].sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_జ్ఞాపకం_INFO;
            plane_info[bind_counts].p_తదుపరి = ఖాళీ;
            plane_info[bind_counts].planeAspect = aspect;

            bind_info[bind_counts].sType  = VK_STRUCTURE_TYPE_BIND_IMAGE_జ్ఞాపకం_INFO;
            bind_info[bind_counts].p_తదుపరి  = planes > 1 ? &plane_info[bind_counts] : ఖాళీ;
            bind_info[bind_counts].image  = f->img[i];
            bind_info[bind_counts].జ్ఞాపకం = f->mem[i];

            /* Offset is already signalled via pPlaneLayouts above */
            bind_info[bind_counts].జ్ఞాపకం_స్థానభ్రంశం = 0;

            bind_counts++;
        }
    }

    /* Bind the allocated memory to the images */
    ret = vk->BindImageMemory2(hwctx->act_dev, bind_counts, bind_info);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind memory: %s\n",
               ff_vk_ret2str(ret));
        err = AVERROR_EXTERNAL;
        వెళ్ళు fail;
    }

    *చట్రం = f;

    తిరిగి 0;

fail:
    vulkan_చట్రం_free(hwfc, f);

    తిరిగి err;
}

స్థిర పూర్ణాంకం vulkan_map_from_drm_చట్రం_sync(AVHWFramesContext *hwfc, AVFrame *dst,
                                          స్థిరరాశి AVDRMFrameDescriptor *desc, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    VulkanDevicePriv *p = ctx->hwctx;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#నిర్వచితమైతే DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) {
        Vk_Command_బఫరు cmd_buf;
        FFVkExecContext *exec;
        Vk_Image_జ్ఞాపకం_Barrier2 img_bar[AV_అంకె_దత్తాంశం_సూచికలు];
        VkSemaphore drm_sync_sem[AV_DRM_MAX_PLANES] = { 0 };
        పూర్ణాంకం nb_img_bar = 0;

        కొరకు (పూర్ణాంకం i = 0; i < desc->nb_objects; i++) {
            VkSemaphoreTypeCreateInfo sem_type_info = {
                .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                .semaphoreType = VK_SEMAPHORE_TYPE_ద్విమాన,
            };
            VkSemaphoreCreateInfo sem_spawn = {
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .p_తదుపరి = &sem_type_info,
            };
            VkImportSemaphoreFdInfoKHR import_info;
            నిర్మాణం dma_buf_export_sync_file implicit_fd_info = {
                .flags = DMA_BUF_SYNC_READ,
                .fd = -1,
            };

            ఒకవేళ (ioctl(desc->objects[i].fd, DMA_BUF_IOCTL_EXPORT_SYNC_FILE,
                      &implicit_fd_info)) {
                err = AVERROR(errno);
                av_log(hwctx, AV_LOG_ERROR, "Failed to retrieve implicit DRM sync file: %s\n",
                       av_err2str(err));
                కొరకు (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                తిరిగి err;
            }

            ret = vk->CreateSemaphore(hwctx->act_dev, &sem_spawn,
                                      hwctx->alloc, &drm_sync_sem[i]);
            ఒకవేళ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to create semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                కొరకు (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                తిరిగి err;
            }

            import_info = (VkImportSemaphoreFdInfoKHR) {
                .sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_బిట్టు,
                .flags = VK_SEMAPHORE_IMPORT_TEMPORARY_బిట్టు,
                .semaphore = drm_sync_sem[i],
                .fd = implicit_fd_info.fd,
            };

            ret = vk->ImportSemaphoreFdKHR(hwctx->act_dev, &import_info);
            ఒకవేళ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_ERROR, "Failed to import semaphore: %s\n",
                       ff_vk_ret2str(ret));
                err = AVERROR_EXTERNAL;
                కొరకు (; i >= 0; i--)
                    vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
                తిరిగి err;
            }
        }

        exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
        cmd_buf = exec->buf;

        err = ff_vk_exec_ప్రారంభం(&p->vkctx, exec);
        ఒకవేళ (err < 0) {
            కొరకు (పూర్ణాంకం i = 0; i < desc->nb_objects; i++)
                vk->DestroySemaphore(hwctx->act_dev, drm_sync_sem[i], hwctx->alloc);
            తిరిగి err;
        }

        /* Ownership of semaphores is passed */
        ff_vk_exec_కూడు_dep_bool_sem(&p->vkctx, exec,
                                    drm_sync_sem, desc->nb_objects,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు, 1);

        /* The imported DRM sync file only orders the external data, not this
         * frame's earlier use by FFmpeg. The frame may be recycled from the
         * pool while it is still in flight (and last used on another queue),
         * so the map waits on its last signal, at ALL_COMMANDS, to be ordered
         * after that previous use. */
        err = ff_vk_exec_కూడు_dep_చట్రం(&p->vkctx, exec, dst,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                                       VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు);
        ఒకవేళ (err < 0) {
            ff_vk_exec_discard(&p->vkctx, exec);
            తిరిగి err;
        }

        ff_vk_చట్రం_barrier(&p->vkctx, exec, dst, img_bar, &nb_img_bar,
                            VK_PIPELINE_STAGE_2_NONE,
                            VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                            ((flags & AV_HWFRAME_MAP_READ) ?
                             VK_ACCESS_2_SHADER_SAMPLED_READ_బిట్టు : 0x0) |
                            ((flags & AV_HWFRAME_MAP_WRITE) ?
                             VK_ACCESS_2_SHADER_STORAGE_WRITE_బిట్టు : 0x0),
                            VK_IMAGE_LAYOUT_GENERAL,
                            p->nb_img_qfs > 1 ? VK_వరుస_FAMILY_IGNORED : p->img_qfs[0]);

        vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
                .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                .p_Image_జ్ఞాపకం_Barriers = img_bar,
                .image_జ్ఞాపకం_Barrier_లెక్క = nb_img_bar,
            });

        err = ff_vk_exec_submit(&p->vkctx, exec);
        ఒకవేళ (err < 0)
            తిరిగి err;
    } లేకపోతే
#అయితే_ముగింపు
    {
        AVVk_చట్రం *f = (AVVk_చట్రం *)dst->దత్తాంశం[0];
        av_log(hwctx, AV_LOG_WARNING, "No support for synchronization when importing DMA-BUFs, "
                                      "image may be corrupted.\n");
        err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_EXTERNAL_IMPORT);
        ఒకవేళ (err)
            తిరిగి err;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vulkan_map_from_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                               స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err = 0;
    AVVk_చట్రం *f;
    స్థిరరాశి AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor *)src->దత్తాంశం[0];

    ఒకవేళ ((err = vulkan_map_from_drm_చట్రం_desc(hwfc, &f, src, flags)))
        తిరిగి err;

    /* The unmapping function will free this */
    dst->దత్తాంశం[0] = (uint8_t *)f;
    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx, dst, src,
                                &vulkan_unmap_from_drm, f);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = vulkan_map_from_drm_చట్రం_sync(hwfc, dst, desc, flags);
    ఒకవేళ (err < 0)
        తిరిగి err;

    av_log(hwfc, AV_LOG_DEBUG, "Mapped DRM object to Vulkan!\n");

    తిరిగి 0;

fail:
    vulkan_చట్రం_free(hwfc->device_ctx->hwctx, f);
    dst->దత్తాంశం[0] = ఖాళీ;
    తిరిగి err;
}

#ఒకవేళ CONFIG_VAAPI
స్థిర పూర్ణాంకం vulkan_map_from_vaapi(AVHWFramesContext *dst_fc,
                                 AVFrame *dst, స్థిరరాశి AVFrame *src,
                                 పూర్ణాంకం flags)
{
    పూర్ణాంకం err;
    AVFrame *tmp = av_చట్రం_alloc();
    AVHWFramesContext *vaapi_fc = (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
    AVVAAPIDeviceContext *vaapi_ctx = vaapi_fc->device_ctx->hwctx;
    VASurfaceID surface_id = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];

    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);

    /* We have to sync since like the previous comment said, no semaphores */
    vaSyncSurface(vaapi_ctx->display, surface_id);

    tmp->format = AV_PIX_FMT_DRM_ప్రధానసంఖ్య;

    err = av_hwframe_map(tmp, src, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = vulkan_map_from_drm(dst_fc, dst, tmp, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_చట్రం_free(&tmp);
    తిరిగి err;
}
#అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ CONFIG_CUDA
స్థిర పూర్ణాంకం export_mem_గమ్యం_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_చట్రం_అంతర్గత *dst_int, పూర్ణాంకం idx,
                              Vk_Device_జ్ఞాపకం mem, size_t కొలత)
{
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#నిర్వచితమైతే _WIN32
    CUDA_EXTERNAL_జ్ఞాపకం_HANDLE_DESC ext_desc = {
        .type = IsWindows8OrGreater()
                ? CU_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32
                : CU_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32_KMT,
            .కొలత = కొలత,
    };
    Vk_జ్ఞాపకం_Get_Win32_Handle_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_జ్ఞాపకం_GET_WIN32_HANDLE_INFO_KHR,
        .జ్ఞాపకం     = mem,
        .handleType = IsWindows8OrGreater()
            ? VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32_బిట్టు
            : VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_WIN32_KMT_బిట్టు,
    };

    ret = vk->Get_జ్ఞాపకం_Win32_Handle_KHR(hwctx->act_dev, &export_info,
                                      &ext_desc.handle.win32.handle);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a Win32 Handle: %s!\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }
    dst_int->ext_mem_handle[idx] = ext_desc.handle.win32.handle;
#లేకపోతే
    CUDA_EXTERNAL_జ్ఞాపకం_HANDLE_DESC ext_desc = {
        .type = CU_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_FD,
        .కొలత = కొలత,
    };
    Vk_జ్ఞాపకం_Get_Fd_Info_KHR export_info = {
        .sType      = VK_STRUCTURE_TYPE_జ్ఞాపకం_GET_FD_INFO_KHR,
        .జ్ఞాపకం     = mem,
        .handleType = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_OPAQUE_FD_బిట్టు_KHR,
    };

    ret = vk->Get_జ్ఞాపకం_Fd_KHR(hwctx->act_dev, &export_info,
                             &ext_desc.handle.fd);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Unable to export the image as a FD: %s!\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }
#అయితే_ముగింపు

    ret = CHECK_CU(cu->cu_Import_External_జ్ఞాపకం(&dst_int->ext_mem[idx], &ext_desc));
    ఒకవేళ (ret < 0) {
#నిర్వచితం_కాకపోతే _WIN32
        close(ext_desc.handle.fd);
#అయితే_ముగింపు
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం export_sem_గమ్యం_cuda(AVHWDeviceContext *ctx,
                              AVHWDeviceContext *cuda_cu, CudaFunctions *cu,
                              AVVk_చట్రం_అంతర్గత *dst_int, పూర్ణాంకం idx,
                              VkSemaphore sem)
{
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

#నిర్వచితమైతే _WIN32
    VkSemaphoreGetWin32HandleInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR,
        .semaphore = sem,
        .handleType = IsWindows8OrGreater()
                      ? VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_బిట్టు
                      : VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_బిట్టు,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 10 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_WIN32 */,
    };
#లేకపోతే
    VkSemaphoreGetFdInfoKHR sem_export = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
        .semaphore = sem,
        .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_బిట్టు,
    };
    CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC ext_sem_desc = {
        .type = 9 /* TODO: CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_TIMELINE_SEMAPHORE_FD */,
    };
#అయితే_ముగింపు

#నిర్వచితమైతే _WIN32
    ret = vk->GetSemaphoreWin32HandleKHR(hwctx->act_dev, &sem_export,
                                         &ext_sem_desc.handle.win32.handle);
#లేకపోతే
    ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &sem_export,
                                &ext_sem_desc.handle.fd);
#అయితే_ముగింపు
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(ctx, AV_LOG_ERROR, "Failed to export semaphore: %s\n",
               ff_vk_ret2str(ret));
        తిరిగి AVERROR_EXTERNAL;
    }
#నిర్వచితమైతే _WIN32
    dst_int->ext_sem_handle[idx] = ext_sem_desc.handle.win32.handle;
#అయితే_ముగింపు

    ret = CHECK_CU(cu->cuImportExternalSemaphore(&dst_int->cu_sem[idx],
                                                 &ext_sem_desc));
    ఒకవేళ (ret < 0) {
#నిర్వచితం_కాకపోతే _WIN32
        close(ext_sem_desc.handle.fd);
#అయితే_ముగింపు
        తిరిగి AVERROR_EXTERNAL;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vulkan_export_గమ్యం_cuda(AVHWFramesContext *hwfc,
                                 AVBufferRef *cuda_hwfc,
                                 స్థిరరాశి AVFrame *చట్రం)
{
    పూర్ణాంకం err;
    Vk_ఫలితం ret;
    AVVk_చట్రం *dst_f;
    AVVk_చట్రం_అంతర్గత *dst_int;
    AVHWDeviceContext *ctx = hwfc->device_ctx;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    VulkanDevicePriv *p = ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    పూర్ణాంకం nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)cuda_hwfc->దత్తాంశం;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_అంతర్గత *cu_అంతర్గత = cuda_dev->అంతర్గత;
    CudaFunctions *cu = cu_అంతర్గత->cuda_dl;
    CUarray_format cufmt = desc->comp[0].లోతు > 8 ? CU_AD_FORMAT_UNSIGNED_INT16 :
                                                     CU_AD_FORMAT_UNSIGNED_INT8;
    స్థిరరాశి పూర్ణాంకం elem_కొలత = 1 + (desc->comp[0].లోతు > 8);

    dst_f = (AVVk_చట్రం *)చట్రం->దత్తాంశం[0];
    dst_int = dst_f->అంతర్గత;

    ఒకవేళ (!dst_int->cuda_fc_ref) {
        size_t offsets[3] = { 0 };

        dst_int->cuda_fc_ref = av_బఫరు_ref(cuda_hwfc);
        ఒకవేళ (!dst_int->cuda_fc_ref)
            తిరిగి AVERROR(ENOMEM);

        nb_images = ff_vk_లెక్క_images(dst_f);
        కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
            err = export_mem_గమ్యం_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->mem[i], dst_f->కొలత[i]);
            ఒకవేళ (err < 0)
                వెళ్ళు fail;

            err = export_sem_గమ్యం_cuda(ctx, cuda_cu, cu, dst_int, i,
                                     dst_f->sem[i]);
            ఒకవేళ (err < 0)
                వెళ్ళు fail;
        }

        ఒకవేళ (nb_images != planes) {
            కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
                /* Cuda now defines array formats for semi-planar, but these are
                 * not currently supported for imported Vulkan images. */
                ఒకవేళ (desc->comp[i].అడుగు / elem_కొలత > 1) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Cannot map a multiplane Vulkan image (%d image(s) "
                           "for %d plane(s)) to CUDA; create the Vulkan device "
                           "with the disable_multiplane=1 option (one image per "
                           "plane) for CUDA interop.\n", nb_images, planes);
                    err = AVERROR(ENOSYS);
                    వెళ్ళు fail;
                }

                VkImageSubresource subres = {
                    .aspect_ముసుగు = i == 2 ? VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_2_బిట్టు_EXT :
                                  i == 1 ? VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_1_బిట్టు_EXT :
                                           VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_0_బిట్టు_EXT
                };
                VkSubresourceLayout layout = { 0 };
                vk->GetImageSubresourceLayout(hwctx->act_dev, dst_f->img[FFMIN(i, nb_images - 1)],
                                              &subres, &layout);
                offsets[i] = layout.స్థానభ్రంశం;
            }
        }

        కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
            CUDA_EXTERNAL_జ్ఞాపకం_MIPMAPPED_ARRAY_DESC tex_desc = {
                .స్థానభ్రంశం = offsets[i],
                .arrayDesc = {
                    .లోతు_2 = 0,
                    .Format = cufmt,
                    .అంకె_Channels = desc->comp[i].అడుగు / elem_కొలత,
                    .Flags = 0,
                },
                .అంకె_స్థాయిలు = 1,
            };
            పూర్ణాంకం p_w, p_h;

            get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->వెడల్పు, hwfc->ఎత్తు, i);
            tex_desc.arrayDesc.వెడల్పు_2 = p_w;
            tex_desc.arrayDesc.ఎత్తు_2 = p_h;

            ret = CHECK_CU(cu->cu_External_జ్ఞాపకం_Get_Mapped_Mipmapped_Array(&dst_int->cu_mma[i],
                                                                       dst_int->ext_mem[FFMIN(i, nb_images - 1)],
                                                                       &tex_desc));
            ఒకవేళ (ret < 0) {
                err = AVERROR_EXTERNAL;
                వెళ్ళు fail;
            }

            ret = CHECK_CU(cu->cuMipmappedArrayGetLevel(&dst_int->cu_array[i],
                                                        dst_int->cu_mma[i], 0));
            ఒకవేళ (ret < 0) {
                err = AVERROR_EXTERNAL;
                వెళ్ళు fail;
            }

        }
    }

    తిరిగి 0;

fail:
    vulkan_free_అంతర్గత(p, dst_f);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vulkan_transfer_దత్తాంశం_from_cuda(AVHWFramesContext *hwfc,
                                          AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం err;
    CUcontext dummy;
    AVVk_చట్రం *dst_f;
    AVVk_చట్రం_అంతర్గత *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    పూర్ణాంకం nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_అంతర్గత *cu_అంతర్గత = cuda_dev->అంతర్గత;
    CudaFunctions *cu = cu_అంతర్గత->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };

    dst_f = (AVVk_చట్రం *)dst->దత్తాంశం[0];
    nb_images = ff_vk_లెక్క_images(dst_f);

    err = prepare_చట్రం(hwfc, &fp->upload_exec, dst_f, PREP_బహుళకం_EXTERNAL_EXPORT);
    ఒకవేళ (err < 0)
        తిరిగి err;

    err = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(cuda_dev->cuda_ctx));
    ఒకవేళ (err < 0)
        తిరిగి err;

    err = vulkan_export_గమ్యం_cuda(hwfc, src->hw_చట్రాలు_ctx, dst);
    ఒకవేళ (err < 0) {
        CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
        తిరిగి err;
    }

    dst_int = dst_f->అంతర్గత;

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.విలువ = dst_f->sem_విలువ[i] + 0;
        s_s_par[i].params.fence.విలువ = dst_f->sem_విలువ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ప్రవాహం));
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .src_జ్ఞాపకం_Type = CU_MEMORYTYPE_DEVICE,
            .srcDevice     = (CUdeviceptr)src->దత్తాంశం[i],
            .srcPitch      = src->linesize[i],
            .srcY          = 0,

            .dst_జ్ఞాపకం_Type = CU_MEMORYTYPE_ARRAY,
            .dstArray      = dst_int->cu_array[i],
        };

        పూర్ణాంకం p_w, p_h;
        get_plane_wh(&p_w, &p_h, hwfc->sw_format, hwfc->వెడల్పు, hwfc->ఎత్తు, i);

        cpy.వెడల్పు_లోపల_బైట్లు = p_w * desc->comp[i].అడుగు;
        cpy.ఎత్తు_2 = p_h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ప్రవాహం));
        ఒకవేళ (err < 0)
            వెళ్ళు fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ప్రవాహం));
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++)
        dst_f->sem_విలువ[i]++;

    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred CUDA image to Vulkan!\n");

    తిరిగి err = prepare_చట్రం(hwfc, &fp->upload_exec, dst_f, PREP_బహుళకం_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    vulkan_free_అంతర్గత(p, dst_f);
    av_బఫరు_unref(&dst->buf[0]);
    తిరిగి err;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vulkan_map_గమ్యం(AVHWFramesContext *hwfc, AVFrame *dst,
                         స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    av_వాడని VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ఎంపిక (src->format) {
#ఒకవేళ CONFIG_LIBDRM
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_PIX_FMT_VAAPI:
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            తిరిగి vulkan_map_from_vaapi(hwfc, dst, src, flags);
        లేకపోతే
            తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            తిరిగి vulkan_map_from_drm(hwfc, dst, src, flags);
        లేకపోతే
            తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }
}

#ఒకవేళ CONFIG_LIBDRM
రకనిర్వచనం నిర్మాణం VulkanDRMMapping {
    AVDRMFrameDescriptor drm_desc;
    AVVk_చట్రం *ఆధారం;
} VulkanDRMMapping;

స్థిర శూన్య vulkan_unmap_గమ్యం_drm(AVHWFramesContext *hwfc, HWMapDescriptor *hwmap)
{
    AVDRMFrameDescriptor *drm_desc = hwmap->priv;

    /* on unmap from DRM, make sure to import sync objects so that we are sync'd with any work that was
     * done on the buffer while exported. We don't know if who used the dmabuf did reads or writes, so protect against both */
    vulkan_map_from_drm_చట్రం_sync(hwfc, hwmap->ఆధారం, drm_desc, AV_HWFRAME_MAP_READ | AV_HWFRAME_MAP_WRITE);

    కొరకు (పూర్ణాంకం i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);

    av_free(drm_desc);
}

స్థిర అంతఃవరుస uint32_t vulkan_fmt_గమ్యం_drm(VkFormat vkfmt)
{
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(vulkan_drm_format_map); i++)
        ఒకవేళ (vulkan_drm_format_map[i].vk_format == vkfmt)
            తిరిగి vulkan_drm_format_map[i].drm_fourcc;
    తిరిగి DRM_FORMAT_INVALID;
}

#నిర్వచించు MAX_జ్ఞాపకం_PLANES 4
స్థిర VkImageAspectFlags plane_సూచీ_గమ్యం_aspect(పూర్ణాంకం plane) {
    ఒకవేళ (plane == 0) తిరిగి VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_0_బిట్టు_EXT;
    ఒకవేళ (plane == 1) తిరిగి VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_1_బిట్టు_EXT;
    ఒకవేళ (plane == 2) తిరిగి VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_2_బిట్టు_EXT;
    ఒకవేళ (plane == 3) తిరిగి VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_3_బిట్టు_EXT;

    av_assert2 (0 && "Invalid plane index");
    తిరిగి VK_IMAGE_ASPECT_జ్ఞాపకం_PLANE_0_బిట్టు_EXT;
}

#నిర్వచితమైతే DMA_BUF_IOCTL_EXPORT_SYNC_FILE
స్థిర పూర్ణాంకం vulkan_drm_export_sync_fd(AVHWFramesContext *hwfc, AVVk_చట్రం *f,
                                     Vulkan_చట్రాలు_Priv *fp, పూర్ణాంకం nb_sems)
{
    పూర్ణాంకం sync_fd = -1;
    Vk_ఫలితం ret;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    ఒకవేళ (f->అంతర్గత->drm_sync_sem == VK_NULL_HANDLE) {
        VkExportSemaphoreCreateInfo exp_info = {
            .sType       = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO,
            .handleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_బిట్టు,
        };
        VkSemaphoreTypeCreateInfo type_info = {
            .sType         = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
            .p_తదుపరి         = &exp_info,
            .semaphoreType = VK_SEMAPHORE_TYPE_ద్విమాన,
        };
        VkSemaphoreCreateInfo sem_create = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .p_తదుపరి = &type_info,
        };
        ret = vk->CreateSemaphore(hwctx->act_dev, &sem_create, hwctx->alloc,
                                  &f->అంతర్గత->drm_sync_sem);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(hwctx, AV_LOG_ERROR, "Failed to create DRM export semaphore: %s\n",
                   ff_vk_ret2str(ret));
            తిరిగి AVERROR_EXTERNAL;
        }
    }

    /* Submit a lightweight exec that waits on the timeline semaphore
     * (true last operation on the frame) and signals the binary semaphore,
     * so any Vulkan frame can get a SYNC_FD regardless of origin. */
    FFVkExecContext *exec = ff_vk_exec_get(&p->vkctx, &fp->compute_exec);
    ఒకవేళ (ff_vk_exec_ప్రారంభం(&p->vkctx, exec) >= 0) {
        కొరకు (పూర్ణాంకం i = 0; i < nb_sems; i++)
            ff_vk_exec_కూడు_dep_wait_sem(&p->vkctx, exec, f->sem[i],
                                        f->sem_విలువ[i],
                                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు);
        ff_vk_exec_కూడు_dep_bool_sem(&p->vkctx, exec, &f->అంతర్గత->drm_sync_sem, 1,
                                    VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు, 0);
        ఒకవేళ (ff_vk_exec_submit(&p->vkctx, exec) >= 0) {
            VkSemaphoreGetFdInfoKHR get_fd_info = {
                .sType      = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR,
                .semaphore  = f->అంతర్గత->drm_sync_sem,
                .handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_బిట్టు,
            };
            ret = vk->GetSemaphoreFdKHR(hwctx->act_dev, &get_fd_info, &sync_fd);
            ఒకవేళ (ret != VK_SUCCESS) {
                av_log(hwctx, AV_LOG_WARNING,
                       "Failed to get sync fd from DRM map export semaphore: %s\n",
                       ff_vk_ret2str(ret));
                sync_fd = -1;
            }
        }
    }

    తిరిగి sync_fd;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vulkan_map_గమ్యం_drm(AVHWFramesContext *hwfc, AVFrame *dst,
                             స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err = 0;
    Vk_ఫలితం ret;
    AVVk_చట్రం *f = (AVVk_చట్రం *)src->దత్తాంశం[0];
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(f);
    VkImageDrmFormatModifierPropertiesEXT drm_mod = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT,
    };
    స్థిరరాశి పూర్ణాంకం nb_sems = nb_images;
    పూర్ణాంకం free_drm_desc_on_err = 1;
    పూర్ణాంకం sync_fd = -1;

    AVDRMFrameDescriptor *drm_desc = av_mallocz(పరిమాణం(*drm_desc));
    ఒకవేళ (!drm_desc)
        తిరిగి AVERROR(ENOMEM);

    err = prepare_చట్రం(hwfc, &fp->compute_exec, f, PREP_బహుళకం_EXTERNAL_EXPORT);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

#నిర్వచితమైతే DMA_BUF_IOCTL_EXPORT_SYNC_FILE
    ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM) &&
        f->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT &&
        vk->GetSemaphoreFdKHR && vk->CreateSemaphore) {
        err = vulkan_drm_export_sync_fd(hwfc, f, fp, nb_sems);
        ఒకవేళ (err < 0)
            వెళ్ళు చివర;
        sync_fd = err;
        err = 0;
    }
#అయితే_ముగింపు

    ఒకవేళ (sync_fd < 0) {
        VkSemaphoreWaitInfo wait_info = {
            .sType          = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
            .flags          = 0x0,
            .semaphore_లెక్క = nb_sems,
            .pSemaphores    = f->sem,
            .p_విలువలు        = f->sem_విలువ,
        };
        vk->WaitSemaphores(hwctx->act_dev, &wait_info, UINT64_MAX);
    }

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src, &vulkan_unmap_గమ్యం_drm, drm_desc);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    /* It will be freed in ff_hwframe_map_create callback */
    free_drm_desc_on_err = 0;

    ret = vk->GetImageDrmFormatModifierPropertiesEXT(hwctx->act_dev, f->img[0],
                                                     &drm_mod);
    ఒకవేళ (ret != VK_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to retrieve DRM format modifier!\n");
        err = AVERROR_EXTERNAL;
        వెళ్ళు చివర;
    }

    కొరకు (పూర్ణాంకం i = 0; (i < planes) && (f->mem[i]); i++) {
        Vk_జ్ఞాపకం_Get_Fd_Info_KHR export_info = {
            .sType      = VK_STRUCTURE_TYPE_జ్ఞాపకం_GET_FD_INFO_KHR,
            .జ్ఞాపకం     = f->mem[i],
            .handleType = VK_EXTERNAL_జ్ఞాపకం_HANDLE_TYPE_DMA_BUF_బిట్టు_EXT,
        };

        ret = vk->Get_జ్ఞాపకం_Fd_KHR(hwctx->act_dev, &export_info,
                                 &drm_desc->objects[i].fd);
        ఒకవేళ (ret != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Unable to export the image as a FD!\n");
            err = AVERROR_EXTERNAL;
            వెళ్ళు చివర;
        }

#ఒకవేళ HAVE_LINUX_DMA_BUF_H && defined(DMA_BUF_IOCTL_IMPORT_SYNC_FILE)
        ఒకవేళ (sync_fd >= 0) {
            పూర్ణాంకం dup_fd = dup(sync_fd);
            ఒకవేళ (dup_fd >= 0) {
                నిర్మాణం dma_buf_import_sync_file import_info = {
                    .flags = DMA_BUF_SYNC_WRITE,
                    .fd = dup_fd,
                };
                ఒకవేళ (ioctl(drm_desc->objects[i].fd, DMA_BUF_IOCTL_IMPORT_SYNC_FILE, &import_info) < 0)
                    av_log(hwfc, AV_LOG_WARNING, "DMA_BUF_IOCTL_IMPORT_SYNC_FILE failed: %s\n", av_err2str(AVERROR(errno)));
                close(dup_fd);
            } లేకపోతే {
                av_log(hwfc, AV_LOG_WARNING, "dup(sync_fd) failed: %s\n", av_err2str(AVERROR(errno)));
            }
        }
#అయితే_ముగింపు

        drm_desc->nb_objects++;
        drm_desc->objects[i].కొలత = f->కొలత[i];
        drm_desc->objects[i].format_modifier = drm_mod.drmFormatModifier;
    }

    /* NV12 has 2 planes but 1 image/semaphore */
    drm_desc->nb_layers = FFMAX(planes, nb_images);
    కొరకు (పూర్ణాంకం i = 0; i < drm_desc->nb_layers; i++) {
        VkFormat plane_vkfmt = av_vkfmt_from_pixfmt(hwfc->sw_format)[i];

        drm_desc->layers[i].format = vulkan_fmt_గమ్యం_drm(plane_vkfmt);
        drm_desc->layers[i].nb_planes = fp->drm_format_modifier_properties[i].drm_Format_Modifier_Plane_లెక్క;

        ఒకవేళ (drm_desc->layers[i].nb_planes > MAX_జ్ఞాపకం_PLANES) {
            av_log(hwfc, AV_LOG_ERROR, "Too many memory planes for DRM format!\n");
            err = AVERROR_EXTERNAL;
            వెళ్ళు చివర;
        }

        కొరకు (పూర్ణాంకం j = 0; j < drm_desc->layers[i].nb_planes; j++) {
            VkSubresourceLayout layout;
            పూర్ణాంకం aspect_plane = (nb_images == 1) ? i : j;
            VkImageSubresource sub = {
                .aspect_ముసుగు = plane_సూచీ_గమ్యం_aspect(aspect_plane),
            };

            drm_desc->layers[i].planes[j].object_సూచీ = FFMIN(i, drm_desc->nb_objects - 1);

            vk->GetImageSubresourceLayout(hwctx->act_dev, f->img[FFMIN(i, nb_images - 1)], &sub, &layout);
            drm_desc->layers[i].planes[j].స్థానభ్రంశం = layout.స్థానభ్రంశం;
            drm_desc->layers[i].planes[j].pitch  = layout.అడ్డువరుస_Pitch_2;
        }

        ఒకవేళ (drm_desc->layers[i].format == DRM_FORMAT_INVALID) {
            av_log(hwfc, AV_LOG_ERROR, "Cannot map to DRM layer, unsupported!\n");
            err = AVERROR_PATCHWELCOME;
            వెళ్ళు చివర;
        }


        ఒకవేళ (f->tiling == VK_IMAGE_TILING_OPTIMAL)
            కొనసాగు;

    }

    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;
    dst->దత్తాంశం[0] = (uint8_t *)drm_desc;
    dst->hw_చట్రాలు_ctx = av_బఫరు_ref(src->hw_చట్రాలు_ctx);

    ఒకవేళ (sync_fd >= 0)
        close(sync_fd);

    av_log(hwfc, AV_LOG_VERBOSE, "Mapped AVVkFrame to a DRM object!\n");

    తిరిగి 0;

చివర:
    కొరకు (పూర్ణాంకం i = 0; i < drm_desc->nb_objects; i++)
        close(drm_desc->objects[i].fd);
    ఒకవేళ (free_drm_desc_on_err)
        av_free(drm_desc);
    ఒకవేళ (sync_fd >= 0)
        close(sync_fd);
    తిరిగి err;
}

#ఒకవేళ CONFIG_VAAPI
స్థిర పూర్ణాంకం vulkan_map_గమ్యం_vaapi(AVHWFramesContext *hwfc, AVFrame *dst,
                               స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;
    AVFrame *tmp = av_చట్రం_alloc();
    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);

    tmp->format = AV_PIX_FMT_DRM_ప్రధానసంఖ్య;

    err = vulkan_map_గమ్యం_drm(hwfc, tmp, src, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = av_hwframe_map(dst, tmp, flags);
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    err = ff_hwframe_map_replace(dst, src);

fail:
    av_చట్రం_free(&tmp);
    తిరిగి err;
}
#అయితే_ముగింపు
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vulkan_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                           స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    av_వాడని VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ఎంపిక (dst->format) {
#ఒకవేళ CONFIG_LIBDRM
    స్థితి AV_PIX_FMT_DRM_ప్రధానసంఖ్య:
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            తిరిగి vulkan_map_గమ్యం_drm(hwfc, dst, src, flags);
        లేకపోతే
            తిరిగి AVERROR(ENOSYS);
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_PIX_FMT_VAAPI:
        ఒకవేళ (p->vkctx.extensions & FF_VK_EXT_DRM_MODIFIER_FLAGS)
            తిరిగి vulkan_map_గమ్యం_vaapi(hwfc, dst, src, flags);
        లేకపోతే
            తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
#అయితే_ముగింపు
    అప్రమేయ:
        ఆపు;
    }
    తిరిగి AVERROR(ENOSYS);
}

స్థిర పూర్ణాంకం copy_బఫరు_దత్తాంశం(AVHWFramesContext *hwfc, FFVk_బఫరు *vkbuf,
                            AVFrame *swf, Vk_బఫరు_Image_Copy *region,
                            పూర్ణాంకం planes, పూర్ణాంకం upload)
{
    పూర్ణాంకం err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    పూర్ణాంకం bytewidth[AV_అంకె_దత్తాంశం_సూచికలు];

    /* Copy only the visible bytes of each row, the last row of a plane
     * does not have to extend to the full linesize. */
    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        bytewidth[i] = av_image_get_linesize(swf->format, swf->వెడల్పు, i);
        ఒకవేళ (bytewidth[i] < 0)
            తిరిగి bytewidth[i];
    }

    ఒకవేళ (upload) {
        కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
            av_image_copy_plane(vkbuf->mapped_mem + region[i].బఫరు_స్థానభ్రంశం,
                                region[i].బఫరు_అడ్డువరుస_నిడివి,
                                swf->దత్తాంశం[i],
                                swf->linesize[i],
                                bytewidth[i],
                                region[i].imageExtent.ఎత్తు);

        err = ff_vk_flush_బఫరు(&p->vkctx, vkbuf, 0, VK_సంపూర్ణ_కొలత, 1);
        ఒకవేళ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to flush buffer data: %s\n",
                   av_err2str(err));
            తిరిగి AVERROR_EXTERNAL;
        }
    } లేకపోతే {
        err = ff_vk_flush_బఫరు(&p->vkctx, vkbuf, 0, VK_సంపూర్ణ_కొలత, 0);
        ఒకవేళ (err != VK_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to invalidate buffer data: %s\n",
                   av_err2str(err));
            తిరిగి AVERROR_EXTERNAL;
        }

        కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
            av_image_copy_plane(swf->దత్తాంశం[i],
                                swf->linesize[i],
                                vkbuf->mapped_mem + region[i].బఫరు_స్థానభ్రంశం,
                                region[i].బఫరు_అడ్డువరుస_నిడివి,
                                bytewidth[i],
                                region[i].imageExtent.ఎత్తు);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం get_plane_buf(AVHWFramesContext *hwfc, FFVk_బఫరు **dst,
                         AVFrame *swf, Vk_బఫరు_Image_Copy *region, పూర్ణాంకం upload)
{
    పూర్ణాంకం err;
    uint32_t p_w, p_h;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(swf->format);
    Vk_బఫరు_Usage_Flags buf_usage = upload ? VK_బఫరు_USAGE_TRANSFER_SRC_బిట్టు :
                                            VK_బఫరు_USAGE_TRANSFER_DST_బిట్టు;

    size_t buf_స్థానభ్రంశం = 0;
    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        get_plane_wh(&p_w, &p_h, swf->format, swf->వెడల్పు, swf->ఎత్తు, i);

        region[i] = (Vk_బఫరు_Image_Copy) {
            .బఫరు_స్థానభ్రంశం = buf_స్థానభ్రంశం,
            .బఫరు_అడ్డువరుస_నిడివి = FFALIGN(FFABS(swf->linesize[i]),
                                       p->props.properties.limits.optimal_బఫరు_Copy_అడ్డువరుస_Pitch_Alignment),
            .బఫరు_Image_ఎత్తు = p_h,
            .imageSubresource.layer_లెక్క = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };

        buf_స్థానభ్రంశం += FFALIGN(p_h*region[i].బఫరు_అడ్డువరుస_నిడివి,
                              p->props.properties.limits.optimal_బఫరు_Copy_స్థానభ్రంశం_Alignment);
    }

    err = ff_vk_get_pooled_బఫరు(&p->vkctx, &fp->tmp, dst, buf_usage,
                                  ఖాళీ, buf_స్థానభ్రంశం,
                                  VK_జ్ఞాపకం_PROPERTY_HOST_VISIBLE_బిట్టు |
                                  p->vkctx.host_cached_flag);
    ఒకవేళ (err < 0)
        తిరిగి err;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం host_map_చట్రం(AVHWFramesContext *hwfc, FFVk_బఫరు **dst, పూర్ణాంకం *nb_bufs,
                          AVFrame *swf, Vk_బఫరు_Image_Copy *region, పూర్ణాంకం upload)
{
    పూర్ణాంకం err;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    పూర్ణాంకం nb_src_bufs;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(swf->format);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    Vk_బఫరు_Usage_Flags buf_usage = upload ? VK_బఫరు_USAGE_TRANSFER_SRC_బిట్టు :
                                            VK_బఫరు_USAGE_TRANSFER_DST_బిట్టు;

    /* Count the number of buffers in the software frame */
    nb_src_bufs = 0;
    అయితే (swf->buf[nb_src_bufs])
        nb_src_bufs++;

    /* Single buffer contains all planes */
    ఒకవేళ (nb_src_bufs == 1) {
        err = ff_vk_host_map_బఫరు(&p->vkctx, &dst[0],
                                    swf->దత్తాంశం[0], VK_సంపూర్ణ_కొలత, swf->buf[0],
                                    buf_usage);
        ఒకవేళ (err < 0)
            తిరిగి err;
        (*nb_bufs)++;

        కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
            region[i].బఫరు_స్థానభ్రంశం = dst[0]->virtual_స్థానభ్రంశం +
                                     swf->దత్తాంశం[i] - swf->దత్తాంశం[0];
    } లేకపోతే ఒకవేళ (nb_src_bufs == planes) { /* One buffer per plane */
        కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
            err = ff_vk_host_map_బఫరు(&p->vkctx, &dst[i],
                                        swf->దత్తాంశం[i], VK_సంపూర్ణ_కొలత,
                                        swf->buf[i], buf_usage);
            ఒకవేళ (err < 0)
                వెళ్ళు fail;
            (*nb_bufs)++;

            region[i].బఫరు_స్థానభ్రంశం = dst[i]->virtual_స్థానభ్రంశం;
        }
    } లేకపోతే {
        /* Weird layout (3 planes, 2 buffers), patch welcome, fallback to copy */
        తిరిగి AVERROR_PATCHWELCOME;
    }

    /* Buffer-image copies need offsets aligned to the texel block, and
     * transfer-only queues to 4 bytes; stage anything else, including
     * texel blocks that are not a power of two */
    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        పూర్ణాంకం align = FFMAX(desc->comp[i].అడుగు, p->transfer_స్థానభ్రంశం_align);
        ఒకవేళ ((align & (align - 1)) || (region[i].బఫరు_స్థానభ్రంశం & (align - 1))) {
            err = AVERROR(EINVAL);
            వెళ్ళు fail;
        }
    }

    తిరిగి 0;

fail:
    కొరకు (పూర్ణాంకం i = 0; i < (*nb_bufs); i++)
        av_refstruct_unref(&dst[i]);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vulkan_transfer_host(AVHWFramesContext *hwfc, AVFrame *hwf,
                                AVFrame *swf, పూర్ణాంకం upload)
{
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkan_చట్రాలు_Context *hwfc_vk = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    AVVulkanDeviceContext *hwctx = &p->p;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    AVVk_చట్రం *hwf_vk = (AVVk_చట్రం *)hwf->దత్తాంశం[0];
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(swf->format);
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(hwf_vk);

    VkSemaphoreWaitInfo sem_wait;
    VkHostImageLayoutTransitionInfoEXT layout_ch_info[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం nb_layout_ch = 0;

    hwfc_vk->తాళం_చట్రం(hwfc, hwf_vk);

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        పూర్ణాంకం compat = 0;
        కొరకు (పూర్ణాంకం j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_లెక్క; j++) {
            ఒకవేళ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                compat = 1;
                ఆపు;
            }
        }
        ఒకవేళ (compat)
            కొనసాగు;

        /* This should only ever happen on uploads, so using UNDEFINED is safe */
        av_assert1(upload);
        layout_ch_info[nb_layout_ch] = (VkHostImageLayoutTransitionInfoEXT) {
            .sType = VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO_EXT,
            .image = hwf_vk->img[i],
            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
            .subresourceRange = {
                .aspect_ముసుగు = VK_IMAGE_ASPECT_COLOR_బిట్టు,
                .level_లెక్క = 1,
                .layer_లెక్క = 1,
            },
        };

        hwf_vk->layout[i] = layout_ch_info[nb_layout_ch].newLayout;
        nb_layout_ch++;
    }

    sem_wait = (VkSemaphoreWaitInfo) {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pSemaphores = hwf_vk->sem,
        .p_విలువలు = hwf_vk->sem_విలువ,
        .semaphore_లెక్క = nb_images,
    };

    vk->WaitSemaphores(hwctx->act_dev, &sem_wait, UINT64_MAX);

    ఒకవేళ (nb_layout_ch)
        vk->TransitionImageLayoutEXT(hwctx->act_dev,
                                     nb_layout_ch, layout_ch_info);

    ఒకవేళ (upload) {
        Vk_జ్ఞాపకం_గమ్యం_Image_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_జ్ఞాపకం_గమ్యం_IMAGE_COPY_EXT,
            .imageSubresource = {
                .layer_లెక్క = 1,
            },
        };
        Vk_Copy_జ్ఞాపకం_గమ్యం_Image_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_జ్ఞాపకం_గమ్యం_IMAGE_INFO_EXT,
            .region_లెక్క = 1,
            .pRegions = &region_info,
        };
        కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
            పూర్ణాంకం img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->వెడల్పు, swf->ఎత్తు, i);

            region_info.p_Host_సూచిక = swf->దత్తాంశం[i];
            region_info.జ్ఞాపకం_అడ్డువరుస_నిడివి = swf->linesize[i] / desc->comp[i].అడుగు;
            region_info.imageSubresource.aspect_ముసుగు = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.dstImage = hwf_vk->img[img_idx];
            copy_info.dstImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_జ్ఞాపకం_గమ్యం_Image_EXT(hwctx->act_dev, &copy_info);
        }
    } లేకపోతే {
        Vk_Image_గమ్యం_జ్ఞాపకం_Copy_EXT region_info = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_గమ్యం_జ్ఞాపకం_COPY_EXT,
            .imageSubresource = {
                .layer_లెక్క = 1,
            },
        };
        Vk_Copy_Image_గమ్యం_జ్ఞాపకం_Info_EXT copy_info = {
            .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_గమ్యం_జ్ఞాపకం_INFO_EXT,
            .region_లెక్క = 1,
            .pRegions = &region_info,
        };
        కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
            పూర్ణాంకం img_idx = FFMIN(i, (nb_images - 1));
            uint32_t p_w, p_h;
            get_plane_wh(&p_w, &p_h, swf->format, swf->వెడల్పు, swf->ఎత్తు, i);

            region_info.p_Host_సూచిక = swf->దత్తాంశం[i];
            region_info.జ్ఞాపకం_అడ్డువరుస_నిడివి = swf->linesize[i] / desc->comp[i].అడుగు;
            region_info.imageSubresource.aspect_ముసుగు = ff_vk_aspect_flag(hwf, i);
            region_info.imageExtent = (VkExtent3D){ p_w, p_h, 1 };
            copy_info.srcImage = hwf_vk->img[img_idx];
            copy_info.srcImageLayout = hwf_vk->layout[img_idx];

            vk->Copy_Image_గమ్యం_జ్ఞాపకం_EXT(hwctx->act_dev, &copy_info);
        }
    }

    hwfc_vk->unlock_చట్రం(hwfc, hwf_vk);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vulkan_transfer_చట్రం(AVHWFramesContext *hwfc,
                                 AVFrame *swf, AVFrame *hwf,
                                 పూర్ణాంకం upload)
{
    పూర్ణాంకం err;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    AVVulkan_చట్రాలు_Context *hwctx = &fp->p;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    FFVulkanFunctions *vk = &p->vkctx.vkfn;

    పూర్ణాంకం host_mapped = 0;

    AVVk_చట్రం *hwf_vk = (AVVk_చట్రం *)hwf->దత్తాంశం[0];
    Vk_బఫరు_Image_Copy region[AV_అంకె_దత్తాంశం_సూచికలు]; // always one per plane

    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(swf->format);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(swf->format);
    స్థిరరాశి పూర్ణాంకం nb_images = ff_vk_లెక్క_images(hwf_vk);

    Vk_Image_జ్ఞాపకం_Barrier2 img_bar[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం nb_img_bar = 0;

    FFVk_బఫరు *bufs[AV_అంకె_దత్తాంశం_సూచికలు];
    పూర్ణాంకం nb_bufs = 0;

    Vk_Command_బఫరు cmd_buf;
    FFVkExecContext *exec;

    /* Sanity checking */
    ఒకవేళ ((swf->format != AV_PIX_FMT_NONE && !av_vkfmt_from_pixfmt(swf->format))) {
        av_log(hwfc, AV_LOG_ERROR, "Unsupported software frame pixel format!\n");
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (swf->వెడల్పు > hwfc->వెడల్పు || swf->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    పూర్ణాంకం host_copy = hwctx->usage & VK_IMAGE_USAGE_HOST_TRANSFER_బిట్టు_EXT;
    పూర్ణాంకం host_map = p->vkctx.extensions & FF_VK_EXT_EXTERNAL_HOST_జ్ఞాపకం &&
                   !p->avoid_host_import;

    /* Host image copies and host mapping address rows upwards from the plane
     * pointer, so a bottom-up frame goes through the staging buffer */
    కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
        ఒకవేళ (swf->linesize[i] < 0)
            host_copy = host_map = 0;

    /* Host layout transitions may only originate from a host-copyable layout */
    ఒకవేళ (!upload && host_copy) {
        కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
            పూర్ణాంకం compat = 0;
            కొరకు (పూర్ణాంకం j = 0; j < p->vkctx.host_image_props.copy_Src_Layout_లెక్క; j++) {
                ఒకవేళ (hwf_vk->layout[i] == p->vkctx.host_image_props.pCopySrcLayouts[j]) {
                    compat = 1;
                    ఆపు;
                }
            }
            ఒకవేళ (!compat) {
                host_copy = 0;
                ఆపు;
            }
        }
    }

    ఒకవేళ (host_copy)
        తిరిగి vulkan_transfer_host(hwfc, hwf, swf, upload);

    కొరకు (పూర్ణాంకం i = 0; i < av_pix_fmt_లెక్క_planes(swf->format); i++) {
        uint32_t p_w, p_h;
        get_plane_wh(&p_w, &p_h, swf->format, swf->వెడల్పు, swf->ఎత్తు, i);

        /* Buffer region for this plane */
        region[i] = (Vk_బఫరు_Image_Copy) {
            .బఫరు_స్థానభ్రంశం = 0,
            .బఫరు_అడ్డువరుస_నిడివి = FFABS(swf->linesize[i]),
            .బఫరు_Image_ఎత్తు = p_h,
            .imageSubresource.layer_లెక్క = 1,
            .imageExtent = (VkExtent3D){ p_w, p_h, 1 },
            /* Rest of the fields adjusted/filled in later */
        };
    }

    /* Setup buffers first */
    ఒకవేళ (host_map) {
        err = host_map_చట్రం(hwfc, bufs, &nb_bufs, swf, region, upload);
        ఒకవేళ (err >= 0)
            host_mapped = 1;
    }

    ఒకవేళ (!host_mapped) {
        err = get_plane_buf(hwfc, &bufs[0], swf, region, upload);
        ఒకవేళ (err < 0)
            వెళ్ళు చివర;
        nb_bufs = 1;

        ఒకవేళ (upload) {
            err = copy_బఫరు_దత్తాంశం(hwfc, bufs[0], swf, region, planes, 1);
            ఒకవేళ (err < 0)
                వెళ్ళు చివర;
        }
    }

    exec = ff_vk_exec_get(&p->vkctx, &fp->upload_exec);
    cmd_buf = exec->buf;

    err = ff_vk_exec_ప్రారంభం(&p->vkctx, exec);
    ఒకవేళ (err < 0)
        వెళ్ళు చివర;

    /* Prep destination Vulkan frame */
    err = ff_vk_exec_కూడు_dep_చట్రం(&p->vkctx, exec, hwf,
                                   VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                                   VK_PIPELINE_STAGE_2_TRANSFER_బిట్టు);
    ఒకవేళ (err < 0) {
        ff_vk_exec_discard(&p->vkctx, exec);
        వెళ్ళు చివర;
    }

    /* No need to declare buf deps for synchronous transfers (downloads) */
    ఒకవేళ (upload) {
        /* Add the software frame backing the buffers if we're host mapping */
        ఒకవేళ (host_mapped) {
            err = ff_vk_exec_కూడు_dep_sw_చట్రం(&p->vkctx, exec, swf);
            ఒకవేళ (err < 0) {
                ff_vk_exec_discard(&p->vkctx, exec);
                వెళ్ళు చివర;
            }
        }

        /* Add the buffers as a dependency */
        కొరకు (పూర్ణాంకం i = 0; i < nb_bufs; i++)
            ff_vk_exec_కూడు_dep_refstruct(&p->vkctx, exec, bufs[i]);
    }

    ff_vk_చట్రం_barrier(&p->vkctx, exec, hwf, img_bar, &nb_img_bar,
                        VK_PIPELINE_STAGE_2_ALL_COMMANDS_బిట్టు,
                        VK_PIPELINE_STAGE_2_TRANSFER_బిట్టు_KHR,
                        upload ? VK_ACCESS_TRANSFER_WRITE_బిట్టు :
                                 VK_ACCESS_TRANSFER_READ_బిట్టు,
                        upload ? VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                        p->nb_img_qfs > 1 ? VK_వరుస_FAMILY_IGNORED : p->img_qfs[0]);

    vk->CmdPipelineBarrier2(cmd_buf, &(VkDependencyInfo) {
            .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
            .p_Image_జ్ఞాపకం_Barriers = img_bar,
            .image_జ్ఞాపకం_Barrier_లెక్క = nb_img_bar,
    });

    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        పూర్ణాంకం buf_idx = FFMIN(i, (nb_bufs - 1));
        పూర్ణాంకం img_idx = FFMIN(i, (nb_images - 1));
        FFVk_బఫరు *vkbuf = bufs[buf_idx];

        uint32_t orig_stride = region[i].బఫరు_అడ్డువరుస_నిడివి;
        region[i].బఫరు_అడ్డువరుస_నిడివి /= desc->comp[i].అడుగు;
        region[i].imageSubresource.aspect_ముసుగు = ff_vk_aspect_flag(hwf, i);

        ఒకవేళ (upload)
            vk->Cmd_Copy_బఫరు_గమ్యం_Image(cmd_buf, vkbuf->buf,
                                     hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     1, &region[i]);
        లేకపోతే
            vk->Cmd_Copy_Image_గమ్యం_బఫరు(cmd_buf, hwf_vk->img[img_idx],
                                     img_bar[img_idx].newLayout,
                                     vkbuf->buf,
                                     1, &region[i]);

        region[i].బఫరు_అడ్డువరుస_నిడివి = orig_stride;
    }

    err = ff_vk_exec_submit(&p->vkctx, exec);
    ఒకవేళ (err >= 0 && !upload) {
        ff_vk_exec_wait(&p->vkctx, exec);
        ఒకవేళ (!host_mapped)
            err = copy_బఫరు_దత్తాంశం(hwfc, bufs[0], swf, region, planes, 0);
    }

చివర:
    కొరకు (పూర్ణాంకం i = 0; i < nb_bufs; i++)
        av_refstruct_unref(&bufs[i]);

    తిరిగి err;
}

స్థిర పూర్ణాంకం vulkan_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *hwfc, AVFrame *dst,
                                   స్థిరరాశి AVFrame *src)
{
    av_వాడని VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ఎంపిక (src->format) {
#ఒకవేళ CONFIG_CUDA
    స్థితి AV_PIX_FMT_CUDA:
#నిర్వచితమైతే _WIN32
        ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_జ్ఞాపకం) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#లేకపోతే
        ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_జ్ఞాపకం) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#అయితే_ముగింపు
            తిరిగి vulkan_transfer_దత్తాంశం_from_cuda(hwfc, dst, src);
        av_fallthrough;
#అయితే_ముగింపు
    అప్రమేయ:
        ఒకవేళ (src->hw_చట్రాలు_ctx)
            తిరిగి AVERROR(ENOSYS);
        లేకపోతే
            తిరిగి vulkan_transfer_చట్రం(hwfc, (AVFrame *)src, dst, 1);
    }
}

#ఒకవేళ CONFIG_CUDA
స్థిర పూర్ణాంకం vulkan_transfer_దత్తాంశం_గమ్యం_cuda(AVHWFramesContext *hwfc, AVFrame *dst,
                                        స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం err;
    CUcontext dummy;
    AVVk_చట్రం *dst_f;
    AVVk_చట్రం_అంతర్గత *dst_int;
    VulkanDevicePriv *p = hwfc->device_ctx->hwctx;
    Vulkan_చట్రాలు_Priv *fp = hwfc->hwctx;
    స్థిరరాశి పూర్ణాంకం planes = av_pix_fmt_లెక్క_planes(hwfc->sw_format);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(hwfc->sw_format);
    పూర్ణాంకం nb_images;

    AVHWFramesContext *cuda_fc = (AVHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;
    AVHWDeviceContext *cuda_cu = cuda_fc->device_ctx;
    AVCUDADeviceContext *cuda_dev = cuda_cu->hwctx;
    AVCUDADevice_Context_అంతర్గత *cu_అంతర్గత = cuda_dev->అంతర్గత;
    CudaFunctions *cu = cu_అంతర్గత->cuda_dl;
    CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS s_w_par[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };
    CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS s_s_par[AV_అంకె_దత్తాంశం_సూచికలు] = { 0 };

    dst_f = (AVVk_చట్రం *)src->దత్తాంశం[0];
    nb_images = ff_vk_లెక్క_images(dst_f);

    err = prepare_చట్రం(hwfc, &fp->upload_exec, dst_f, PREP_బహుళకం_EXTERNAL_EXPORT);
    ఒకవేళ (err < 0)
        తిరిగి err;

    err = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(cuda_dev->cuda_ctx));
    ఒకవేళ (err < 0)
        తిరిగి err;

    err = vulkan_export_గమ్యం_cuda(hwfc, dst->hw_చట్రాలు_ctx, src);
    ఒకవేళ (err < 0) {
        CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
        తిరిగి err;
    }

    dst_int = dst_f->అంతర్గత;

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++) {
        s_w_par[i].params.fence.విలువ = dst_f->sem_విలువ[i] + 0;
        s_s_par[i].params.fence.విలువ = dst_f->sem_విలువ[i] + 1;
    }

    err = CHECK_CU(cu->cuWaitExternalSemaphoresAsync(dst_int->cu_sem, s_w_par,
                                                     nb_images, cuda_dev->ప్రవాహం));
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం i = 0; i < planes; i++) {
        CUDA_MEMCPY2D cpy = {
            .dst_జ్ఞాపకం_Type = CU_MEMORYTYPE_DEVICE,
            .dstDevice     = (CUdeviceptr)dst->దత్తాంశం[i],
            .dstPitch      = dst->linesize[i],
            .dstY          = 0,

            .src_జ్ఞాపకం_Type = CU_MEMORYTYPE_ARRAY,
            .srcArray      = dst_int->cu_array[i],
        };

        పూర్ణాంకం w, h;
        get_plane_wh(&w, &h, hwfc->sw_format, hwfc->వెడల్పు, hwfc->ఎత్తు, i);

        cpy.వెడల్పు_లోపల_బైట్లు = w * desc->comp[i].అడుగు;
        cpy.ఎత్తు_2 = h;

        err = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, cuda_dev->ప్రవాహం));
        ఒకవేళ (err < 0)
            వెళ్ళు fail;
    }

    err = CHECK_CU(cu->cuSignalExternalSemaphoresAsync(dst_int->cu_sem, s_s_par,
                                                       nb_images, cuda_dev->ప్రవాహం));
    ఒకవేళ (err < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం i = 0; i < nb_images; i++)
        dst_f->sem_విలువ[i]++;

    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));

    av_log(hwfc, AV_LOG_VERBOSE, "Transferred Vulkan image to CUDA!\n");

    తిరిగి prepare_చట్రం(hwfc, &fp->upload_exec, dst_f, PREP_బహుళకం_EXTERNAL_IMPORT);

fail:
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    vulkan_free_అంతర్గత(p, dst_f);
    av_బఫరు_unref(&dst->buf[0]);
    తిరిగి err;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం vulkan_transfer_దత్తాంశం_from(AVHWFramesContext *hwfc, AVFrame *dst,
                                     స్థిరరాశి AVFrame *src)
{
    av_వాడని VulkanDevicePriv *p = hwfc->device_ctx->hwctx;

    ఎంపిక (dst->format) {
#ఒకవేళ CONFIG_CUDA
    స్థితి AV_PIX_FMT_CUDA:
#నిర్వచితమైతే _WIN32
        ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_జ్ఞాపకం) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_WIN32_SEM))
#లేకపోతే
        ఒకవేళ ((p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_జ్ఞాపకం) &&
            (p->vkctx.extensions & FF_VK_EXT_EXTERNAL_FD_SEM))
#అయితే_ముగింపు
            తిరిగి vulkan_transfer_దత్తాంశం_గమ్యం_cuda(hwfc, dst, src);
        av_fallthrough;
#అయితే_ముగింపు
    అప్రమేయ:
        ఒకవేళ (dst->hw_చట్రాలు_ctx)
            తిరిగి AVERROR(ENOSYS);
        లేకపోతే
            తిరిగి vulkan_transfer_చట్రం(hwfc, dst, (AVFrame *)src, 0);
    }
}

స్థిర పూర్ణాంకం vulkan_చట్రాలు_derive_గమ్యం(AVHWFramesContext *dst_fc,
                                   AVHWFramesContext *src_fc, పూర్ణాంకం flags)
{
    తిరిగి vulkan_చట్రాలు_init(dst_fc);
}

AVVk_చట్రం *av_vk_చట్రం_alloc(శూన్య)
{
    పూర్ణాంకం err;
    AVVk_చట్రం *f = av_mallocz(పరిమాణం(AVVk_చట్రం));
    ఒకవేళ (!f)
        తిరిగి ఖాళీ;

    f->అంతర్గత = av_mallocz(పరిమాణం(*f->అంతర్గత));
    ఒకవేళ (!f->అంతర్గత) {
        av_free(f);
        తిరిగి ఖాళీ;
    }

    err = pthread_mutex_init(&f->అంతర్గత->update_mutex, ఖాళీ);
    ఒకవేళ (err != 0) {
        av_free(f->అంతర్గత);
        av_free(f);
        తిరిగి ఖాళీ;
    }

    తిరిగి f;
}

స్థిరరాశి HWContextType ff_hwcontext_type_vulkan = {
    .type                   = AV_HWDEVICE_TYPE_VULKAN,
    .name                   = "Vulkan",

    .device_hwctx_కొలత      = పరిమాణం(VulkanDevicePriv),
    .చట్రాలు_hwctx_కొలత      = పరిమాణం(Vulkan_చట్రాలు_Priv),

    .device_init            = &vulkan_device_init,
    .device_uninit          = &vulkan_device_uninit,
    .device_create          = &vulkan_device_create,
    .device_derive          = &vulkan_device_derive,

    .చట్రాలు_get_constraints = &vulkan_చట్రాలు_get_constraints,
    .చట్రాలు_init            = vulkan_చట్రాలు_init,
    .చట్రాలు_get_బఫరు      = vulkan_get_బఫరు,
    .చట్రాలు_uninit          = vulkan_చట్రాలు_uninit,

    .transfer_get_formats   = vulkan_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = vulkan_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from     = vulkan_transfer_దత్తాంశం_from,

    .map_గమ్యం                 = vulkan_map_గమ్యం,
    .map_from               = vulkan_map_from,
    .చట్రాలు_derive_గమ్యం       = &vulkan_చట్రాలు_derive_గమ్యం,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat []) {
        AV_PIX_FMT_VULKAN,
        AV_PIX_FMT_NONE
    },
};
