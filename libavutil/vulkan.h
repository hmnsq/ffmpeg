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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_VULKAN_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_VULKAN_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NO_PROTOTYPES

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "refstruct.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_functions.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RET(x)                                                                 \
    ਕਰੋ {                                                                       \
        ਜੇ ((err = (x)) < 0)                                                   \
            ਜਾਓ fail;                                                         \
    } ਜਦੋਂ (0)

/* Convenience macros for specialization lists */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPEC_LIST_MAX 256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPEC_LIST_CREATE(name, max_ਲੰਮਾਈ, max_ਮਾਪ)           \
    av_assert1((max_ਲੰਮਾਈ) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_ਮਾਪ) + 3*ਆਕਾਰ(uint32_t)];      \
    Vk_Specialization_Map_ਇੰਦਰਾਜ name##_entries[(max_ਲੰਮਾਈ) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_ਅੰਕੜੇ = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPEC_LIST_ਜੋੜੋ(name, idx, val_ਬਿੱਟ, val)                \
ਕਰੋ {                                                           \
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ name##_cnt = name->map_ਇੰਦਰਾਜ_ਗਿਣਤੀ;             \
    size_t name##_off = name->ਅੰਕੜੇ_ਮਾਪ_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_ਅੰਕੜੇ;               \
    ਖਾਲੀ *name##_ep = (ਖਾਲੀ *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_ਬਿੱਟ, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_ਇੰਦਰਾਜ name##_new_entry = {              \
        .constantID = (idx),                                   \
        .ਵਿੱਥ = name##_off,                                  \
        .ਮਾਪ = val_ਬਿੱਟ >> 3,                                 \
    };                                                         \
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(name##_ep, &name##_new_entry,                       \
           ਆਕਾਰ(Vk_Specialization_Map_ਇੰਦਰਾਜ));                  \
    name->ਅੰਕੜੇ_ਮਾਪ_2 = name##_off + (val_ਬਿੱਟ >> 3);             \
    name->map_ਇੰਦਰਾਜ_ਗਿਣਤੀ = name##_cnt + 1;                      \
} ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUP_SAMPLER(x) { x, x, x, x }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_MAX_DESCRIPTOR_SETS 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_MAX_DESCRIPTOR_TYPES 16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_MAX_ਧੱਕੋ_CONSTS 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_MAX_SHADERS 16

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkan_Descriptor_ਸੈੱਟ_Binding {
    ਅਚਲ ਅੱਖਰ         *name;
    VkDescriptorType    type;
    ਅਚਲ ਅੱਖਰ         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ਅਚਲ ਅੱਖਰ         *mem_quali;   /* readonly, writeonly, etc. */
    ਅਚਲ ਅੱਖਰ         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkan_Descriptor_ਸੈੱਟ_Binding;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVk_ਬਫਰ {
    Vk_ਬਫਰ buf;
    Vk_Device_ਸਮ੍ਰਿਤੀ mem;
    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ flags;
    size_t ਮਾਪ;
    Vk_Device_ਪਤਾ ਪਤਾ;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_ਵਿੱਥ;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_ਬਫਰ;

/* Fixed dependency limits per exec context (with room to spare) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS 64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_EXEC_MAX_BUF_DEPS 256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_EXEC_MAX_SW_ਚੌਖਟਾ_DEPS 16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS*AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ)

/* Default number of in-flight execution contexts per pool */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_DEFAULT_EXEC_CONTEXTS 4

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVkExecContext {
    uint32_t idx;
    ਅਚਲ ਬਣਤਰ FFVkExecPool *ਮਾਪਾ;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    ਪੂਰਨ had_submission;

    /* Queue for the execution context */
    Vk_ਕਤਾਰ ਕਤਾਰ;
    ਪੂਰਨ qf;
    ਪੂਰਨ qi;

    /* Command buffer for the context */
    Vk_Command_ਬਫਰ buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_ਮੁੱਲ;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t ਤਾਲਾ;

    /* Opaque data, untouched, free to use by users */
    ਖਾਲੀ *opaque;

    ਖਾਲੀ *query_ਅੰਕੜੇ;
    ਪੂਰਨ query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ਪੂਰਨ nb_buf_deps;

    /* AVRefStruct object dependencies */
    ਖਾਲੀ *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ਪੂਰਨ nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ਪੂਰਨ nb_obj_deps;

    /* Frame dependencies */
    AVFrame *ਚੌਖਟਾ_deps[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
    ਪੂਰਨ nb_ਚੌਖਟਾ_deps;

    /* Software frame dependencies */
    AVFrame *sw_ਚੌਖਟਾ_deps[FF_VK_EXEC_MAX_SW_ਚੌਖਟਾ_DEPS];
    ਪੂਰਨ nb_sw_ਚੌਖਟਾ_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    ਪੂਰਨ sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    ਪੂਰਨ sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    ਪੂਰਨ sem_sig_val_dst_cnt;

    uint8_t ਚੌਖਟਾ_locked[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
    Vk_Access_Flag_ਬਿੱਟ access_dst[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
    uint32_t ਕਤਾਰ_family_dst[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
    uint8_t ਚੌਖਟਾ_update[FF_VK_EXEC_MAX_ਚੌਖਟਾ_DEPS];
} FFVkExecContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkan_Descriptor_ਸੈੱਟ {
    /* Descriptor buffer */
    Vk_Device_ਮਾਪ layout_ਮਾਪ;
    Vk_Device_ਮਾਪ aligned_ਮਾਪ; /* descriptorBufferOffsetAlignment */
    Vk_ਬਫਰ_Usage_Flags usage;

    Vk_Descriptor_ਸੈੱਟ_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_ਮਾਪ binding_ਵਿੱਥ[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    ਪੂਰਨ nb_bindings;

    /* Descriptor set is shared between all submissions */
    ਪੂਰਨ singular;
} FFVulkan_Descriptor_ਸੈੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkanShader {
    /* Name for id/debugging purposes */
    ਅਚਲ ਅੱਖਰ *name;

    /* Whether shader is precompiled or not */
    ਪੂਰਨ precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_ਮਾਪ[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_ਬਿੰਦੂ bind_ਬਿੰਦੂ;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_ਮਾਪ_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ਧੱਕੋ_Constant_Range ਧੱਕੋ_consts[FF_VK_MAX_ਧੱਕੋ_CONSTS];
    ਪੂਰਨ ਧੱਕੋ_consts_ਅੰਕ;

    /* Descriptor sets */
    FFVulkan_Descriptor_ਸੈੱਟ desc_ਸੈੱਟ[FF_VK_MAX_DESCRIPTOR_SETS];
    ਪੂਰਨ nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_ਸੈੱਟ_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    ਪੂਰਨ use_ਧੱਕੋ;
    Vk_Descriptor_Pool_ਮਾਪ desc_pool_ਮਾਪ[FF_VK_MAX_DESCRIPTOR_TYPES];
    ਪੂਰਨ nb_desc_pool_ਮਾਪ;
} FFVulkanShader;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkan_Descriptor_ਸੈੱਟ_ਅੰਕੜੇ {
    /* Descriptor buffer */
    FFVk_ਬਫਰ buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_ਸੈੱਟ_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkan_Shader_ਅੰਕੜੇ {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    ਪੂਰਨ nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_ਸੈੱਟ_ਅੰਕੜੇ desc_ਸੈੱਟ_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_ਬਫਰ_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_ਸੈੱਟ *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_ਅੰਕੜੇ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_ਬਫਰ *cmd_bufs;
    ਪੂਰਨ pool_ਮਾਪ;

    VkQueryPool query_pool;
    ਖਾਲੀ *query_ਅੰਕੜੇ;
    ਪੂਰਨ query_results;
    ਪੂਰਨ query_statuses;
    ਪੂਰਨ query_64bit;
    ਪੂਰਨ query_ਸਥਿਤੀ_stride;
    ਪੂਰਨ nb_queries;
    size_t qd_ਮਾਪ;

    /* Registered shaders' data */
    FFVulkan_Shader_ਅੰਕੜੇ reg_shd[FF_VK_MAX_SHADERS];
    ਪੂਰਨ nb_reg_shd;
} FFVkExecPool;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVulkanContext {
    ਅਚਲ AVClass *class;
    ਖਾਲੀ *log_ਮਾਪਾ;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_ਸਮ੍ਰਿਤੀ_Properties mprops;
    Vk_Physical_Device_External_ਸਮ੍ਰਿਤੀ_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_ਬਫਰ_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_ਮਾਪ_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR coop_ਮੈਟ੍ਰਿਕਸ_props;
    Vk_Physical_Device_ਧੱਕੋ_Descriptor_Properties_KHR ਧੱਕੋ_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_EXT_shader_long_ਸਦਿਸ਼
    Vk_Physical_Device_Shader_Long_ਸਦਿਸ਼_Properties_EXT long_ਸਦਿਸ਼_props;
#ਜੇ_ਅੰਤ
    Vk_ਕਤਾਰ_Family_Query_ਨਤੀਜਾ_ਸਥਿਤੀ_Properties_KHR *query_props;
    Vk_ਕਤਾਰ_Family_Video_Properties_KHR *video_props;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance9
    Vk_ਕਤਾਰ_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#ਜੇ_ਅੰਤ
    Vk_ਕਤਾਰ_Family_Properties2 *qf_props;
    ਪੂਰਨ tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_ਮੈਟ੍ਰਿਕਸ_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#ਜੇ_ਅੰਤ
    VkPhysicalDeviceFeatures2 feats;

    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *ਨਿਵੇਸ਼_ਚੌਖਟੇ_ref;
    AVBufferRef           *ਚੌਖਟੇ_ref;
    AVHWFramesContext     *ਚੌਖਟੇ;
    AVVulkan_ਚੌਖਟੇ_Context *hwfc;

    uint32_t               qfs[64];
    ਪੂਰਨ                    nb_qfs;

    /* Properties */
    ਪੂਰਨ                 output_ਚੌੜਾਈ;
    ਪੂਰਨ                output_ਉਚਾਈ;
    ਗਿਣਤੀ AVPixelFormat output_format;
    ਗਿਣਤੀ AVPixelFormat  ਨਿਵੇਸ਼_format;
} FFVulkanContext;

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_vk_ਗਿਣਤੀ_images(AVVk_ਚੌਖਟਾ *f)
{
    ਪੂਰਨ cnt = 0;
    ਜਦੋਂ (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    ਵਾਪਸ cnt;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਚਲ ਖਾਲੀ *ff_vk_ਲੱਭੋ_struct(ਅਚਲ ਖਾਲੀ *chain, VkStructureType stype)
{
    ਅਚਲ Vk_ਅਧਾਰ_ਵਿੱਚ_Structure *ਵਿੱਚ_2 = chain;
    ਜਦੋਂ (ਵਿੱਚ_2) {
        ਜੇ (ਵਿੱਚ_2->sType == stype)
            ਵਾਪਸ ਵਿੱਚ_2;

        ਵਿੱਚ_2 = ਵਿੱਚ_2->p_ਅਗਲਾ;
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ff_vk_link_struct(ਖਾਲੀ *chain, ਅਚਲ ਖਾਲੀ *ਵਿੱਚ_2)
{
    Vk_ਅਧਾਰ_ਬਾਹਰਲਾ_Structure *ਬਾਹਰਲਾ = chain;
    ਜਦੋਂ (ਬਾਹਰਲਾ->p_ਅਗਲਾ)
        ਬਾਹਰਲਾ = ਬਾਹਰਲਾ->p_ਅਗਲਾ;

    ਬਾਹਰਲਾ->p_ਅਗਲਾ = (ਖਾਲੀ *)ਵਿੱਚ_2;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_VK_STRUCT_EXT(CTX, ਅਧਾਰ, STRUCT_P, EXT_FLAG, TYPE) \
    ਕਰੋ {                                                      \
        ਜੇ ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(ਅਧਾਰ, STRUCT_P);                \
        }                                                     \
    } ਜਦੋਂ (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
ਬਾਹਰੀ ਅਚਲ VkComponentMapping ff_comp_ਪਛਾਣ_ਤੱਤ_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
ਪੂਰਨ ff_vk_init(FFVulkanContext *s, ਖਾਲੀ *log_ਮਾਪਾ,
               AVBufferRef *device_ref, AVBufferRef *ਚੌਖਟੇ_ref);

/**
 * Converts Vulkan return values to strings
 */
ਅਚਲ ਅੱਖਰ *ff_vk_ret2str(Vk_ਨਤੀਜਾ res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_ਮੰਜ਼ਿਲ_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_ਮੰਜ਼ਿਲ_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
ਪੂਰਨ ff_vk_mt_is_np_rgb(ਗਿਣਤੀ AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
ਖਾਲੀ ff_vk_ਸੈੱਟ_perm(ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ lut[4], ਪੂਰਨ inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ਪੂਰਨ p);

/**
 * Returns the format to use for images in shaders.
 */
ਗਿਣਤੀ FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ਅਚਲ ਅੱਖਰ *ff_vk_shader_rep_fmt(ਗਿਣਤੀ AVPixelFormat pix_fmt,
                                 ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_ਮੰਜ਼ਿਲ_rep(VkFormat fmt, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
ਪੂਰਨ ff_vk_ਲੱਦੋ_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_ਕਤਾਰ_Family *ff_vk_qf_ਲੱਭੋ(FFVulkanContext *s,
                                         Vk_ਕਤਾਰ_Flag_ਬਿੱਟ dev_family,
                                         Vk_Video_Codec_Operation_Flag_ਬਿੱਟ_KHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
ਪੂਰਨ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_ਕਤਾਰ_Family *qf,
                         FFVkExecPool *pool, ਪੂਰਨ nb_contexts,
                         ਪੂਰਨ nb_queries, VkQueryType query_type, ਪੂਰਨ query_64bit,
                         ਅਚਲ ਖਾਲੀ *query_create_pnext);
ਖਾਲੀ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_ਨਤੀਜਾ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ਖਾਲੀ **ਅੰਕੜੇ, Vk_Query_ਨਤੀਜਾ_Flag_ਬਿੱਟ flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
ਪੂਰਨ ff_vk_exec_ਸ਼ੁਰੂ(FFVulkanContext *s, FFVkExecContext *e);
ਪੂਰਨ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
ਖਾਲੀ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ਖਾਲੀ *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
ਖਾਲੀ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ਖਾਲੀ *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
ਖਾਲੀ ff_vk_exec_ਜੋੜੋ_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ਪੂਰਨ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ਪੂਰਨ wait); /* Ownership transferred if !wait */
ਪੂਰਨ ff_vk_exec_ਜੋੜੋ_dep_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
ਪੂਰਨ ff_vk_exec_ਜੋੜੋ_dep_sw_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
ਖਾਲੀ ff_vk_exec_update_ਚੌਖਟਾ(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 *bar, uint32_t *nb_img_bar);
ਪੂਰਨ ff_vk_exec_mirror_sem_ਮੁੱਲ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
ਖਾਲੀ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
ਪੂਰਨ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ਪੂਰਨ plane, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFVkImageViews {
    ਪੂਰਨ nb_views;

    VkDevice dev;
    ਅਚਲ Vk_ਵੰਡ_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ਪੂਰਨ nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
ਪੂਰਨ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ],
                            AVFrame *f, ਗਿਣਤੀ FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
ਪੂਰਨ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ],
                                AVFrame *f,
                                ਅਚਲ VkFormat fmts[AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ]);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    ਕਰੋ {                                                                       \
        dst = (Vk_ਬਫਰ_ਸਮ੍ਰਿਤੀ_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_ਬਫਰ_ਸਮ੍ਰਿਤੀ_BARRIER_2,                \
            .src_Stage_ਨਕਾਬ = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_ਨਕਾਬ = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_ਨਕਾਬ = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_ਨਕਾਬ = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = VK_ਕਤਾਰ_FAMILY_IGNORED,                    \
            .dst_ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ = VK_ਕਤਾਰ_FAMILY_IGNORED,                    \
            .ਬਫਰ = vkb->buf,                                                \
            .ਵਿੱਥ = offs,                                                    \
            .ਮਾਪ = bsz                                                        \
        };                                                                     \
    } ਜਦੋਂ(0)

ਖਾਲੀ ff_vk_ਚੌਖਟਾ_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_ਸਮ੍ਰਿਤੀ_Barrier2 *bar, ਪੂਰਨ *nb_bar,
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
ਪੂਰਨ ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_ਸਮ੍ਰਿਤੀ *mem,
                       ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, VkFormat format, ਪੂਰਨ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ਖਾਲੀ *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
ਖਾਲੀ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_ਸਮ੍ਰਿਤੀ *mem);

ਪੂਰਨ ff_vk_alloc_mem(FFVulkanContext *s, Vk_ਸਮ੍ਰਿਤੀ_Requirements *req,
                    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ req_flags, ਖਾਲੀ *alloc_extension,
                    Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ *mem_flags, Vk_Device_ਸਮ੍ਰਿਤੀ *mem);
ਪੂਰਨ ff_vk_create_buf(FFVulkanContext *s, FFVk_ਬਫਰ *buf, size_t ਮਾਪ,
                     ਖਾਲੀ *p_ਅਗਲਾ, ਖਾਲੀ *alloc_p_ਅਗਲਾ,
                     Vk_ਬਫਰ_Usage_Flags usage, Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
ਪੂਰਨ ff_vk_flush_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ *buf,
                       Vk_Device_ਮਾਪ ਵਿੱਥ, Vk_Device_ਮਾਪ mem_ਮਾਪ,
                       ਪੂਰਨ flush);

/**
 * Buffer management code.
 */
ਪੂਰਨ ff_vk_map_buffers(FFVulkanContext *s, FFVk_ਬਫਰ **buf, uint8_t *mem[],
                      ਪੂਰਨ nb_buffers, ਪੂਰਨ invalidate);
ਪੂਰਨ ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_ਬਫਰ **buf, ਪੂਰਨ nb_buffers,
                        ਪੂਰਨ flush);

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_vk_map_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ *buf, uint8_t **mem,
                                   ਪੂਰਨ invalidate)
{
    ਵਾਪਸ ff_vk_map_buffers(s, (FFVk_ਬਫਰ *[]){ buf }, mem,
                             1, invalidate);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_vk_unmap_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ *buf, ਪੂਰਨ flush)
{
    ਵਾਪਸ ff_vk_unmap_buffers(s, (FFVk_ਬਫਰ *[]){ buf }, 1, flush);
}

ਖਾਲੀ ff_vk_free_buf(FFVulkanContext *s, FFVk_ਬਫਰ *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
ਪੂਰਨ ff_vk_get_pooled_ਬਫਰ(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_ਬਫਰ **buf, Vk_ਬਫਰ_Usage_Flags usage,
                            ਖਾਲੀ *create_p_ਅਗਲਾ, size_t ਮਾਪ,
                            Vk_ਸਮ੍ਰਿਤੀ_Property_Flag_ਬਿੱਟ mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
ਪੂਰਨ ff_vk_host_map_ਬਫਰ(FFVulkanContext *s, FFVk_ਬਫਰ **dst,
                          uint8_t *src_ਅੰਕੜੇ, Vk_Device_ਮਾਪ ਮਾਪ,
                          ਅਚਲ AVBufferRef *src_buf,
                          Vk_ਬਫਰ_Usage_Flags usage);

/**
 * Create a sampler.
 */
ਪੂਰਨ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ਪੂਰਨ unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
ਪੂਰਨ ff_vk_shader_ਲੱਦੋ(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_ਮਾਪ[3], uint32_t required_subgroup_ਮਾਪ);

/**
 * Link a shader into an executable.
 */
ਪੂਰਨ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ਅਚਲ ਅੱਖਰ *spirv, size_t spirv_len,
                      ਅਚਲ ਅੱਖਰ *entrypoint);

/**
 * Add/update push constants for execution.
 */
ਪੂਰਨ ff_vk_shader_ਜੋੜੋ_ਧੱਕੋ_const(FFVulkanShader *shd, ਪੂਰਨ ਵਿੱਥ, ਪੂਰਨ ਮਾਪ,
                                Vk_Shader_Stage_Flag_ਬਿੱਟ stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
ਖਾਲੀ ff_vk_shader_ਜੋੜੋ_descriptor_ਸੈੱਟ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ਅਚਲ FFVulkan_Descriptor_ਸੈੱਟ_Binding *desc, ਪੂਰਨ nb,
                                     ਪੂਰਨ singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
ਪੂਰਨ ff_vk_shader_ਰਜਿਸਟਰ_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
ਖਾਲੀ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ਅਚਲ FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
ਖਾਲੀ ff_vk_shader_update_ਧੱਕੋ_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_ਬਿੱਟ stage,
                                    ਪੂਰਨ ਵਿੱਥ, size_t ਮਾਪ, ਖਾਲੀ *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
ਪੂਰਨ ff_vk_shader_update_desc_ਬਫਰ(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ bind, ਪੂਰਨ elem,
                                    FFVk_ਬਫਰ *buf, Vk_Device_ਮਾਪ ਵਿੱਥ, Vk_Device_ਮਾਪ len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
ਪੂਰਨ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ bind, ਪੂਰਨ offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
ਖਾਲੀ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ਪੂਰਨ ਸੈੱਟ, ਪੂਰਨ binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
ਖਾਲੀ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
ਖਾਲੀ ff_vk_uninit(FFVulkanContext *s);

#ਜੇ_ਅੰਤ /* AVUTIL_VULKAN_H */
