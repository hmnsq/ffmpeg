/*
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_VULKAN_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_VULKAN_H

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NO_PROTOTYPES

#ಅನ್ತರ್ಭಾವ <stdatomic.h>

#ಅನ್ತರ್ಭಾವ "refstruct.h"

#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "vulkan_functions.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_vulkan.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#ವ್ಯಾಖ್ಯಾನಿಸು RET(x)                                                                 \
    ಮಾಡು {                                                                       \
        ಆದರೆ ((err = (x)) < 0)                                                   \
            ಹೋಗು fail;                                                         \
    } ಆಗ (0)

/* Convenience macros for specialization lists */
#ವ್ಯಾಖ್ಯಾನಿಸು SPEC_LIST_MAX 256
#ವ್ಯಾಖ್ಯಾನಿಸು SPEC_LIST_CREATE(name, max_ಉದ್ದಳತೆ, max_ಗಾತ್ರ)           \
    av_assert1((max_ಉದ್ದಳತೆ) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_ಗಾತ್ರ) + 3*ಗಾತ್ರ(uint32_t)];      \
    Vk_Specialization_Map_ನಮೂದು name##_entries[(max_ಉದ್ದಳತೆ) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_ದತ್ತಾಂಶ = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#ವ್ಯಾಖ್ಯಾನಿಸು SPEC_LIST_ಕೂಡಿಸು(name, idx, val_ಬಿಟ್ಟುಗಳು, val)                \
ಮಾಡು {                                                           \
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ name##_cnt = name->map_ನಮೂದು_ಎಣಿಕೆ;             \
    size_t name##_off = name->ದತ್ತಾಂಶ_ಗಾತ್ರ_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_ದತ್ತಾಂಶ;               \
    ಶೂನ್ಯ *name##_ep = (ಶೂನ್ಯ *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_ಬಿಟ್ಟುಗಳು, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_ನಮೂದು name##_new_entry = {              \
        .constantID = (idx),                                   \
        .ಸ್ಥಾನಾಂತರ = name##_off,                                  \
        .ಗಾತ್ರ_2 = val_ಬಿಟ್ಟುಗಳು >> 3,                                 \
    };                                                         \
    ಸ್ಮರಣೆ_ನಕಲು(name##_ep, &name##_new_entry,                       \
           ಗಾತ್ರ(Vk_Specialization_Map_ನಮೂದು));                  \
    name->ದತ್ತಾಂಶ_ಗಾತ್ರ_2 = name##_off + (val_ಬಿಟ್ಟುಗಳು >> 3);             \
    name->map_ನಮೂದು_ಎಣಿಕೆ = name##_cnt + 1;                      \
} ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು DUP_SAMPLER(x) { x, x, x, x }

#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_MAX_DESCRIPTOR_SETS 4
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_MAX_DESCRIPTOR_TYPES 16
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_MAX_ತಳ್ಳು_CONSTS 4
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_MAX_SHADERS 16

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkan_Descriptor_ಗಣ_Binding {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ         *name;
    VkDescriptorType    type;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ         *mem_quali;   /* readonly, writeonly, etc. */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkan_Descriptor_ಗಣ_Binding;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVk_ಬಫರ್ {
    Vk_ಬಫರ್ buf;
    Vk_Device_ಸ್ಮರಣೆ mem;
    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು flags;
    size_t ಗಾತ್ರ_2;
    Vk_Device_ವಿಳಾಸ ವಿಳಾಸ;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_ಸ್ಥಾನಾಂತರ;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_ಬಫರ್;

/* Fixed dependency limits per exec context (with room to spare) */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS 64
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_EXEC_MAX_BUF_DEPS 256
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_EXEC_MAX_SW_ಚೌಕಟ್ಟು_DEPS 16
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS*AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು)

/* Default number of in-flight execution contexts per pool */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_DEFAULT_EXEC_CONTEXTS 4

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVkExecContext {
    uint32_t idx;
    ಸ್ಥಿರಾಂಕ ರಚನೆ FFVkExecPool *ಪೋಷಕ;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    ಪೂರ್ಣಾಂಕ had_submission;

    /* Queue for the execution context */
    Vk_ಸರತಿ ಸರತಿ;
    ಪೂರ್ಣಾಂಕ qf;
    ಪೂರ್ಣಾಂಕ qi;

    /* Command buffer for the context */
    Vk_Command_ಬಫರ್ buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_ಮೌಲ್ಯ;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t ಬೀಗ_2;

    /* Opaque data, untouched, free to use by users */
    ಶೂನ್ಯ *opaque;

    ಶೂನ್ಯ *query_ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಂಕ nb_buf_deps;

    /* AVRefStruct object dependencies */
    ಶೂನ್ಯ *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಂಕ nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಂಕ nb_obj_deps;

    /* Frame dependencies */
    AVFrame *ಚೌಕಟ್ಟು_deps[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
    ಪೂರ್ಣಾಂಕ nb_ಚೌಕಟ್ಟು_deps;

    /* Software frame dependencies */
    AVFrame *sw_ಚೌಕಟ್ಟು_deps[FF_VK_EXEC_MAX_SW_ಚೌಕಟ್ಟು_DEPS];
    ಪೂರ್ಣಾಂಕ nb_sw_ಚೌಕಟ್ಟು_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಂಕ sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಂಕ sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಂಕ sem_sig_val_dst_cnt;

    uint8_t ಚೌಕಟ್ಟು_locked[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
    Vk_Access_Flag_ಬಿಟ್ಟುಗಳು access_dst[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
    uint32_t ಸರತಿ_family_dst[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
    uint8_t ಚೌಕಟ್ಟು_update[FF_VK_EXEC_MAX_ಚೌಕಟ್ಟು_DEPS];
} FFVkExecContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkan_Descriptor_ಗಣ {
    /* Descriptor buffer */
    Vk_Device_ಗಾತ್ರ layout_ಗಾತ್ರ;
    Vk_Device_ಗಾತ್ರ aligned_ಗಾತ್ರ; /* descriptorBufferOffsetAlignment */
    Vk_ಬಫರ್_Usage_Flags usage;

    Vk_Descriptor_ಗಣ_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_ಗಾತ್ರ binding_ಸ್ಥಾನಾಂತರ[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    ಪೂರ್ಣಾಂಕ nb_bindings;

    /* Descriptor set is shared between all submissions */
    ಪೂರ್ಣಾಂಕ singular;
} FFVulkan_Descriptor_ಗಣ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkanShader {
    /* Name for id/debugging purposes */
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;

    /* Whether shader is precompiled or not */
    ಪೂರ್ಣಾಂಕ precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_ಗಾತ್ರ[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_ಬಿಂದು bind_ಬಿಂದು;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_ಗಾತ್ರ_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ತಳ್ಳು_Constant_Range ತಳ್ಳು_consts[FF_VK_MAX_ತಳ್ಳು_CONSTS];
    ಪೂರ್ಣಾಂಕ ತಳ್ಳು_consts_ಅಂಕೆ;

    /* Descriptor sets */
    FFVulkan_Descriptor_ಗಣ desc_ಗಣ[FF_VK_MAX_DESCRIPTOR_SETS];
    ಪೂರ್ಣಾಂಕ nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_ಗಣ_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    ಪೂರ್ಣಾಂಕ use_ತಳ್ಳು;
    Vk_Descriptor_Pool_ಗಾತ್ರ desc_pool_ಗಾತ್ರ[FF_VK_MAX_DESCRIPTOR_TYPES];
    ಪೂರ್ಣಾಂಕ nb_desc_pool_ಗಾತ್ರ;
} FFVulkanShader;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkan_Descriptor_ಗಣ_ದತ್ತಾಂಶ {
    /* Descriptor buffer */
    FFVk_ಬಫರ್ buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_ಗಣ_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkan_Shader_ದತ್ತಾಂಶ {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    ಪೂರ್ಣಾಂಕ nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_ಗಣ_ದತ್ತಾಂಶ desc_ಗಣ_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_ಬಫರ್_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_ಗಣ *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_ದತ್ತಾಂಶ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_ಬಫರ್ *cmd_bufs;
    ಪೂರ್ಣಾಂಕ pool_ಗಾತ್ರ;

    VkQueryPool query_pool;
    ಶೂನ್ಯ *query_ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ query_results;
    ಪೂರ್ಣಾಂಕ query_statuses;
    ಪೂರ್ಣಾಂಕ query_64bit;
    ಪೂರ್ಣಾಂಕ query_ಸ್ಥಿತಿ_stride;
    ಪೂರ್ಣಾಂಕ nb_queries;
    size_t qd_ಗಾತ್ರ;

    /* Registered shaders' data */
    FFVulkan_Shader_ದತ್ತಾಂಶ reg_shd[FF_VK_MAX_SHADERS];
    ಪೂರ್ಣಾಂಕ nb_reg_shd;
} FFVkExecPool;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVulkanContext {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಶೂನ್ಯ *log_ಪೋಷಕ;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_ಸ್ಮರಣೆ_Properties mprops;
    Vk_Physical_Device_External_ಸ್ಮರಣೆ_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_ಬಫರ್_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_ಗಾತ್ರ_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_ಮಾತೃಕೆ_Properties_KHR coop_ಮಾತೃಕೆ_props;
    Vk_Physical_Device_ತಳ್ಳು_Descriptor_Properties_KHR ತಳ್ಳು_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_EXT_shader_long_ಸದಿಶ
    Vk_Physical_Device_Shader_Long_ಸದಿಶ_Properties_EXT long_ಸದಿಶ_props;
#ಆದರೆ_ಅಂತ್ಯ
    Vk_ಸರತಿ_Family_Query_ಫಲಿತಾಂಶ_ಸ್ಥಿತಿ_Properties_KHR *query_props;
    Vk_ಸರತಿ_Family_Video_Properties_KHR *video_props;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance9
    Vk_ಸರತಿ_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#ಆದರೆ_ಅಂತ್ಯ
    Vk_ಸರತಿ_Family_Properties2 *qf_props;
    ಪೂರ್ಣಾಂಕ tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_ಮಾತೃಕೆ_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#ಆದರೆ_ಅಂತ್ಯ
    VkPhysicalDeviceFeatures2 feats;

    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *ಒಳಹರಿವು_ಚೌಕಟ್ಟುಗಳು_ref;
    AVBufferRef           *ಚೌಕಟ್ಟುಗಳು_ref;
    AVHWFramesContext     *ಚೌಕಟ್ಟುಗಳು;
    AVVulkan_ಚೌಕಟ್ಟುಗಳು_Context *hwfc;

    uint32_t               qfs[64];
    ಪೂರ್ಣಾಂಕ                    nb_qfs;

    /* Properties */
    ಪೂರ್ಣಾಂಕ                 output_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ                output_ಎತ್ತರ;
    ಎಣಿಕೆ AVPixelFormat output_format;
    ಎಣಿಕೆ AVPixelFormat  ಒಳಹರಿವು_format;
} FFVulkanContext;

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_vk_ಎಣಿಕೆ_images(AVVk_ಚೌಕಟ್ಟು *f)
{
    ಪೂರ್ಣಾಂಕ cnt = 0;
    ಆಗ (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    ಹಿಂತಿರುಗಿ cnt;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ff_vk_ಕಂಡುಹಿಡಿ_struct(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *chain, VkStructureType stype)
{
    ಸ್ಥಿರಾಂಕ Vk_ತಳ_ಒಳ_Structure *ಒಳ = chain;
    ಆಗ (ಒಳ) {
        ಆದರೆ (ಒಳ->sType == stype)
            ಹಿಂತಿರುಗಿ ಒಳ;

        ಒಳ = ಒಳ->p_ಮುಂದಿನ;
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ff_vk_link_struct(ಶೂನ್ಯ *chain, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಒಳ)
{
    Vk_ತಳ_ಹೊರಹೋಗು_Structure *ಹೊರಹೋಗು = chain;
    ಆಗ (ಹೊರಹೋಗು->p_ಮುಂದಿನ)
        ಹೊರಹೋಗು = ಹೊರಹೋಗು->p_ಮುಂದಿನ;

    ಹೊರಹೋಗು->p_ಮುಂದಿನ = (ಶೂನ್ಯ *)ಒಳ;
}

#ವ್ಯಾಖ್ಯಾನಿಸು FF_VK_STRUCT_EXT(CTX, ತಳ, STRUCT_P, EXT_FLAG, TYPE) \
    ಮಾಡು {                                                      \
        ಆದರೆ ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(ತಳ, STRUCT_P);                \
        }                                                     \
    } ಆಗ (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ VkComponentMapping ff_comp_ತಟಸ್ಥ_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
ಪೂರ್ಣಾಂಕ ff_vk_init(FFVulkanContext *s, ಶೂನ್ಯ *log_ಪೋಷಕ,
               AVBufferRef *device_ref, AVBufferRef *ಚೌಕಟ್ಟುಗಳು_ref);

/**
 * Converts Vulkan return values to strings
 */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ff_vk_ret2str(Vk_ಫಲಿತಾಂಶ res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_ಗಮ್ಯ_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_ಗಮ್ಯ_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
ಪೂರ್ಣಾಂಕ ff_vk_mt_is_np_rgb(ಎಣಿಕೆ AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
ಶೂನ್ಯ ff_vk_ಗಣ_perm(ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ lut[4], ಪೂರ್ಣಾಂಕ inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ಪೂರ್ಣಾಂಕ p);

/**
 * Returns the format to use for images in shaders.
 */
ಎಣಿಕೆ FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ff_vk_shader_rep_fmt(ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                 ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_ಗಮ್ಯ_rep(VkFormat fmt, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
ಪೂರ್ಣಾಂಕ ff_vk_ತುಂಬು_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_ಸರತಿ_Family *ff_vk_qf_ಕಂಡುಹಿಡಿ(FFVulkanContext *s,
                                         Vk_ಸರತಿ_Flag_ಬಿಟ್ಟುಗಳು dev_family,
                                         Vk_Video_Codec_Operation_Flag_ಬಿಟ್ಟುಗಳು_KHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
ಪೂರ್ಣಾಂಕ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_ಸರತಿ_Family *qf,
                         FFVkExecPool *pool, ಪೂರ್ಣಾಂಕ nb_contexts,
                         ಪೂರ್ಣಾಂಕ nb_queries, VkQueryType query_type, ಪೂರ್ಣಾಂಕ query_64bit,
                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *query_create_pnext);
ಶೂನ್ಯ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_ಫಲಿತಾಂಶ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ಶೂನ್ಯ **ದತ್ತಾಂಶ, Vk_Query_ಫಲಿತಾಂಶ_Flag_ಬಿಟ್ಟುಗಳು flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
ಪೂರ್ಣಾಂಕ ff_vk_exec_ಆರಂಭ(FFVulkanContext *s, FFVkExecContext *e);
ಪೂರ್ಣಾಂಕ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
ಶೂನ್ಯ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Execution dependency management.
 * Can attach buffers to executions that will only be unref'd once the
 * buffer has finished executing.
 * Adding a frame dep will *lock the frame*, until either the dependencies
 * are discarded, the execution is submitted, or a failure happens.
 * update_frame will update the frame's properties before it is unlocked,
 * only if submission was successful.
 * ff_vk_exec_discard() abandons a started, unsubmitted recording: call it
 * exactly once, from the claiming thread. ff_vk_exec_submit() cleans up
 * after its own failures.
 */

/* Takes a new reference to an AVRefStruct-managed object, held until the
 * execution's dependencies are released. */
ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ಶೂನ್ಯ *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
ಶೂನ್ಯ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ಶೂನ್ಯ *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
ಶೂನ್ಯ ff_vk_exec_ಕೂಡಿಸು_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ಪೂರ್ಣಾಂಕ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ಪೂರ್ಣಾಂಕ wait); /* Ownership transferred if !wait */
ಪೂರ್ಣಾಂಕ ff_vk_exec_ಕೂಡಿಸು_dep_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
ಪೂರ್ಣಾಂಕ ff_vk_exec_ಕೂಡಿಸು_dep_sw_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
ಶೂನ್ಯ ff_vk_exec_update_ಚೌಕಟ್ಟು(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_ಸ್ಮರಣೆ_Barrier2 *bar, uint32_t *nb_img_bar);
ಪೂರ್ಣಾಂಕ ff_vk_exec_mirror_sem_ಮೌಲ್ಯ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
ಶೂನ್ಯ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
ಪೂರ್ಣಾಂಕ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ಪೂರ್ಣಾಂಕ plane, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFVkImageViews {
    ಪೂರ್ಣಾಂಕ nb_views;

    VkDevice dev;
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ಪೂರ್ಣಾಂಕ nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
ಪೂರ್ಣಾಂಕ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು],
                            AVFrame *f, ಎಣಿಕೆ FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
ಪೂರ್ಣಾಂಕ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು],
                                AVFrame *f,
                                ಸ್ಥಿರಾಂಕ VkFormat fmts[AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು]);

#ವ್ಯಾಖ್ಯಾನಿಸು ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    ಮಾಡು {                                                                       \
        dst = (Vk_ಬಫರ್_ಸ್ಮರಣೆ_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_ಬಫರ್_ಸ್ಮರಣೆ_BARRIER_2,                \
            .src_Stage_ಮುಖವಾಡ = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_ಮುಖವಾಡ = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_ಮುಖವಾಡ = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_ಮುಖವಾಡ = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = VK_ಸರತಿ_FAMILY_IGNORED,                    \
            .dst_ಸರತಿ_Family_ಸೂಚ್ಯಂಕ = VK_ಸರತಿ_FAMILY_IGNORED,                    \
            .ಬಫರ್ = vkb->buf,                                                \
            .ಸ್ಥಾನಾಂತರ = offs,                                                    \
            .ಗಾತ್ರ_2 = bsz                                                        \
        };                                                                     \
    } ಆಗ(0)

ಶೂನ್ಯ ff_vk_ಚೌಕಟ್ಟು_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_ಸ್ಮರಣೆ_Barrier2 *bar, ಪೂರ್ಣಾಂಕ *nb_bar,
                         VkPipelineStageFlags2 src_stage,
                         VkPipelineStageFlags2 dst_stage,
                         VkAccessFlagBits2     new_access,
                         VkImageLayout         new_layout,
                         uint32_t             new_qf);

/**
 * Memory/buffer/image allocation helpers.
 */
/**
 * Create a standalone internal-use image: exclusive sharing, dedicated
 * memory. Not for interop or mapping.
 */
ಪೂರ್ಣಾಂಕ ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_ಸ್ಮರಣೆ *mem,
                       ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, VkFormat format, ಪೂರ್ಣಾಂಕ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ಶೂನ್ಯ *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
ಶೂನ್ಯ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_ಸ್ಮರಣೆ *mem);

ಪೂರ್ಣಾಂಕ ff_vk_alloc_mem(FFVulkanContext *s, Vk_ಸ್ಮರಣೆ_Requirements *req,
                    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು req_flags, ಶೂನ್ಯ *alloc_extension,
                    Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು *mem_flags, Vk_Device_ಸ್ಮರಣೆ *mem);
ಪೂರ್ಣಾಂಕ ff_vk_create_buf(FFVulkanContext *s, FFVk_ಬಫರ್ *buf, size_t ಗಾತ್ರ_2,
                     ಶೂನ್ಯ *p_ಮುಂದಿನ, ಶೂನ್ಯ *alloc_p_ಮುಂದಿನ,
                     Vk_ಬಫರ್_Usage_Flags usage, Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
ಪೂರ್ಣಾಂಕ ff_vk_flush_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ *buf,
                       Vk_Device_ಗಾತ್ರ ಸ್ಥಾನಾಂತರ, Vk_Device_ಗಾತ್ರ mem_ಗಾತ್ರ,
                       ಪೂರ್ಣಾಂಕ flush);

/**
 * Buffer management code.
 */
ಪೂರ್ಣಾಂಕ ff_vk_map_buffers(FFVulkanContext *s, FFVk_ಬಫರ್ **buf, uint8_t *mem[],
                      ಪೂರ್ಣಾಂಕ nb_buffers, ಪೂರ್ಣಾಂಕ invalidate);
ಪೂರ್ಣಾಂಕ ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_ಬಫರ್ **buf, ಪೂರ್ಣಾಂಕ nb_buffers,
                        ಪೂರ್ಣಾಂಕ flush);

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_vk_map_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ *buf, uint8_t **mem,
                                   ಪೂರ್ಣಾಂಕ invalidate)
{
    ಹಿಂತಿರುಗಿ ff_vk_map_buffers(s, (FFVk_ಬಫರ್ *[]){ buf }, mem,
                             1, invalidate);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_vk_unmap_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ *buf, ಪೂರ್ಣಾಂಕ flush)
{
    ಹಿಂತಿರುಗಿ ff_vk_unmap_buffers(s, (FFVk_ಬಫರ್ *[]){ buf }, 1, flush);
}

ಶೂನ್ಯ ff_vk_free_buf(FFVulkanContext *s, FFVk_ಬಫರ್ *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
ಪೂರ್ಣಾಂಕ ff_vk_get_pooled_ಬಫರ್(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_ಬಫರ್ **buf, Vk_ಬಫರ್_Usage_Flags usage,
                            ಶೂನ್ಯ *create_p_ಮುಂದಿನ, size_t ಗಾತ್ರ_2,
                            Vk_ಸ್ಮರಣೆ_Property_Flag_ಬಿಟ್ಟುಗಳು mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
ಪೂರ್ಣಾಂಕ ff_vk_host_map_ಬಫರ್(FFVulkanContext *s, FFVk_ಬಫರ್ **dst,
                          uint8_t *src_ದತ್ತಾಂಶ, Vk_Device_ಗಾತ್ರ ಗಾತ್ರ_2,
                          ಸ್ಥಿರಾಂಕ AVBufferRef *src_buf,
                          Vk_ಬಫರ್_Usage_Flags usage);

/**
 * Create a sampler.
 */
ಪೂರ್ಣಾಂಕ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ಪೂರ್ಣಾಂಕ unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_ತುಂಬು(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_ಗಾತ್ರ[3], uint32_t required_subgroup_ಗಾತ್ರ);

/**
 * Link a shader into an executable.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *spirv, size_t spirv_len,
                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *entrypoint);

/**
 * Add/update push constants for execution.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_ಕೂಡಿಸು_ತಳ್ಳು_const(FFVulkanShader *shd, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2,
                                Vk_Shader_Stage_Flag_ಬಿಟ್ಟುಗಳು stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
ಶೂನ್ಯ ff_vk_shader_ಕೂಡಿಸು_descriptor_ಗಣ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ಸ್ಥಿರಾಂಕ FFVulkan_Descriptor_ಗಣ_Binding *desc, ಪೂರ್ಣಾಂಕ nb,
                                     ಪೂರ್ಣಾಂಕ singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_ರಿಜಿಸ್ಟರ್_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
ಶೂನ್ಯ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ಸ್ಥಿರಾಂಕ FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
ಶೂನ್ಯ ff_vk_shader_update_ತಳ್ಳು_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_ಬಿಟ್ಟುಗಳು stage,
                                    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, size_t ಗಾತ್ರ_2, ಶೂನ್ಯ *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_update_desc_ಬಫರ್(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ bind, ಪೂರ್ಣಾಂಕ elem,
                                    FFVk_ಬಫರ್ *buf, Vk_Device_ಗಾತ್ರ ಸ್ಥಾನಾಂತರ, Vk_Device_ಗಾತ್ರ len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
ಪೂರ್ಣಾಂಕ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ bind, ಪೂರ್ಣಾಂಕ offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
ಶೂನ್ಯ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ಪೂರ್ಣಾಂಕ ಗಣ, ಪೂರ್ಣಾಂಕ binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
ಶೂನ್ಯ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
ಶೂನ್ಯ ff_vk_uninit(FFVulkanContext *s);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_VULKAN_H */
