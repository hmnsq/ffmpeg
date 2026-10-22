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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_VULKAN_H
#وصف_ڪريو AVUTIL_VULKAN_H

#وصف_ڪريو VK_NO_PROTOTYPES

#ضمن <stdatomic.h>

#ضمن "refstruct.h"

#ضمن "thread.h"
#ضمن "pixdesc.h"
#ضمن "hwcontext.h"
#ضمن "vulkan_functions.h"
#ضمن "hwcontext_vulkan.h"
#ضمن "avassert.h"
#ضمن "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#وصف_ڪريو RET(x)                                                                 \
    افعل {                                                                       \
        إذا ((err = (x)) < 0)                                                   \
            اذهب fail;                                                         \
    } طالما (0)

/* Convenience macros for specialization lists */
#وصف_ڪريو SPEC_LIST_MAX 256
#وصف_ڪريو SPEC_LIST_CREATE(name, max_ڊيگهائي, max_سائيز)           \
    av_assert1((max_ڊيگهائي) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_سائيز) + 3*حجم(uint32_t)];      \
    Vk_Specialization_Map_داخلا name##_entries[(max_ڊيگهائي) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_معلومات = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#وصف_ڪريو SPEC_LIST_جوڙيو(name, idx, val_بٽ, val)                \
افعل {                                                           \
    بنانشان صحيح name##_cnt = name->map_داخلا_ڳڻپ;             \
    size_t name##_off = name->معلومات_سائيز_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_معلومات;               \
    فراغ *name##_ep = (فراغ *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_بٽ, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_داخلا name##_new_entry = {              \
        .constantID = (idx),                                   \
        .وٿي = name##_off,                                  \
        .سائيز = val_بٽ >> 3,                                 \
    };                                                         \
    يادگيري_نقل(name##_ep, &name##_new_entry,                       \
           حجم(Vk_Specialization_Map_داخلا));                  \
    name->معلومات_سائيز_2 = name##_off + (val_بٽ >> 3);             \
    name->map_داخلا_ڳڻپ = name##_cnt + 1;                      \
} طالما (0)

#وصف_ڪريو DUP_SAMPLER(x) { x, x, x, x }

#وصف_ڪريو FF_VK_MAX_DESCRIPTOR_SETS 4
#وصف_ڪريو FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#وصف_ڪريو FF_VK_MAX_DESCRIPTOR_TYPES 16
#وصف_ڪريو FF_VK_MAX_ڌڪو_CONSTS 4
#وصف_ڪريو FF_VK_MAX_SHADERS 16

تعريفنوع بنية FFVulkan_Descriptor_سيٽ_Binding {
    ثابت حرف         *name;
    VkDescriptorType    type;
    ثابت حرف         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ثابت حرف         *mem_quali;   /* readonly, writeonly, etc. */
    ثابت حرف         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkan_Descriptor_سيٽ_Binding;

تعريفنوع بنية FFVk_بفر {
    Vk_بفر buf;
    Vk_Device_يادگيري mem;
    Vk_يادگيري_Property_Flag_بٽ flags;
    size_t سائيز;
    Vk_Device_پتو پتو;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_وٿي;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_بفر;

/* Fixed dependency limits per exec context (with room to spare) */
#وصف_ڪريو FF_VK_EXEC_MAX_چوکٺو_DEPS 64
#وصف_ڪريو FF_VK_EXEC_MAX_BUF_DEPS 256
#وصف_ڪريو FF_VK_EXEC_MAX_SW_چوکٺو_DEPS 16
#وصف_ڪريو FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_چوکٺو_DEPS*AV_انگ_معلومات_اشارا)

/* Default number of in-flight execution contexts per pool */
#وصف_ڪريو FF_VK_DEFAULT_EXEC_CONTEXTS 4

تعريفنوع بنية FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

تعريفنوع بنية FFVkExecContext {
    uint32_t idx;
    ثابت بنية FFVkExecPool *والد;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    صحيح had_submission;

    /* Queue for the execution context */
    Vk_قطار قطار;
    صحيح qf;
    صحيح qi;

    /* Command buffer for the context */
    Vk_Command_بفر buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_قدر;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t تالو;

    /* Opaque data, untouched, free to use by users */
    فراغ *opaque;

    فراغ *query_معلومات;
    صحيح query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحيح nb_buf_deps;

    /* AVRefStruct object dependencies */
    فراغ *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحيح nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحيح nb_obj_deps;

    /* Frame dependencies */
    AVFrame *چوکٺو_deps[FF_VK_EXEC_MAX_چوکٺو_DEPS];
    صحيح nb_چوکٺو_deps;

    /* Software frame dependencies */
    AVFrame *sw_چوکٺو_deps[FF_VK_EXEC_MAX_SW_چوکٺو_DEPS];
    صحيح nb_sw_چوکٺو_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_sig_val_dst_cnt;

    uint8_t چوکٺو_locked[FF_VK_EXEC_MAX_چوکٺو_DEPS];
    Vk_Access_Flag_بٽ access_dst[FF_VK_EXEC_MAX_چوکٺو_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_چوکٺو_DEPS];
    uint32_t قطار_family_dst[FF_VK_EXEC_MAX_چوکٺو_DEPS];
    uint8_t چوکٺو_update[FF_VK_EXEC_MAX_چوکٺو_DEPS];
} FFVkExecContext;

تعريفنوع بنية FFVulkan_Descriptor_سيٽ {
    /* Descriptor buffer */
    Vk_Device_سائيز layout_سائيز;
    Vk_Device_سائيز aligned_سائيز; /* descriptorBufferOffsetAlignment */
    Vk_بفر_Usage_Flags usage;

    Vk_Descriptor_سيٽ_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_سائيز binding_وٿي[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    صحيح nb_bindings;

    /* Descriptor set is shared between all submissions */
    صحيح singular;
} FFVulkan_Descriptor_سيٽ;

تعريفنوع بنية FFVulkanShader {
    /* Name for id/debugging purposes */
    ثابت حرف *name;

    /* Whether shader is precompiled or not */
    صحيح precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_سائيز[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_نقطو bind_نقطو;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_سائيز_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ڌڪو_Constant_Range ڌڪو_consts[FF_VK_MAX_ڌڪو_CONSTS];
    صحيح ڌڪو_consts_انگ;

    /* Descriptor sets */
    FFVulkan_Descriptor_سيٽ desc_سيٽ[FF_VK_MAX_DESCRIPTOR_SETS];
    صحيح nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_سيٽ_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    صحيح use_ڌڪو;
    Vk_Descriptor_Pool_سائيز desc_pool_سائيز[FF_VK_MAX_DESCRIPTOR_TYPES];
    صحيح nb_desc_pool_سائيز;
} FFVulkanShader;

تعريفنوع بنية FFVulkan_Descriptor_سيٽ_معلومات {
    /* Descriptor buffer */
    FFVk_بفر buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_سيٽ_معلومات;

تعريفنوع بنية FFVulkan_Shader_معلومات {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    صحيح nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_سيٽ_معلومات desc_سيٽ_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_بفر_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_سيٽ *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_معلومات;

تعريفنوع بنية FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_بفر *cmd_bufs;
    صحيح pool_سائيز;

    VkQueryPool query_pool;
    فراغ *query_معلومات;
    صحيح query_results;
    صحيح query_statuses;
    صحيح query_64bit;
    صحيح query_حالت_stride;
    صحيح nb_queries;
    size_t qd_سائيز;

    /* Registered shaders' data */
    FFVulkan_Shader_معلومات reg_shd[FF_VK_MAX_SHADERS];
    صحيح nb_reg_shd;
} FFVkExecPool;

تعريفنوع بنية FFVulkanContext {
    ثابت AVClass *class;
    فراغ *log_والد;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_يادگيري_Properties mprops;
    Vk_Physical_Device_External_يادگيري_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_بفر_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_سائيز_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_ميٽرڪس_Properties_KHR coop_ميٽرڪس_props;
    Vk_Physical_Device_ڌڪو_Descriptor_Properties_KHR ڌڪو_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#جيڪڏهن_وصف_ٿيل VK_EXT_shader_long_ويڪٽر
    Vk_Physical_Device_Shader_Long_ويڪٽر_Properties_EXT long_ويڪٽر_props;
#جيڪڏهن_پورو
    Vk_قطار_Family_Query_نتيجو_حالت_Properties_KHR *query_props;
    Vk_قطار_Family_Video_Properties_KHR *video_props;
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance9
    Vk_قطار_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#جيڪڏهن_پورو
    Vk_قطار_Family_Properties2 *qf_props;
    صحيح tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_ميٽرڪس_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#جيڪڏهن_وصف_ٿيل VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#جيڪڏهن_پورو
    VkPhysicalDeviceFeatures2 feats;

    Vk_يادگيري_Property_Flag_بٽ host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *داخلا_چوکٺا_ref;
    AVBufferRef           *چوکٺا_ref;
    AVHWFramesContext     *چوکٺا;
    AVVulkan_چوکٺا_Context *hwfc;

    uint32_t               qfs[64];
    صحيح                    nb_qfs;

    /* Properties */
    صحيح                 output_ويڪر;
    صحيح                output_اوچائي;
    تعداد AVPixelFormat output_format;
    تعداد AVPixelFormat  داخلا_format;
} FFVulkanContext;

ساكن مضمن صحيح ff_vk_ڳڻپ_images(AVVk_چوکٺو *f)
{
    صحيح cnt = 0;
    طالما (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    أرجع cnt;
}

ساكن مضمن ثابت فراغ *ff_vk_ڳوليو_struct(ثابت فراغ *chain, VkStructureType stype)
{
    ثابت Vk_بنياد_اندريون_Structure *اندريون = chain;
    طالما (اندريون) {
        إذا (اندريون->sType == stype)
            أرجع اندريون;

        اندريون = اندريون->p_ايندڙ;
    }

    أرجع عدم;
}

ساكن مضمن فراغ ff_vk_link_struct(فراغ *chain, ثابت فراغ *اندريون)
{
    Vk_بنياد_ٻاهريون_Structure *ٻاهريون = chain;
    طالما (ٻاهريون->p_ايندڙ)
        ٻاهريون = ٻاهريون->p_ايندڙ;

    ٻاهريون->p_ايندڙ = (فراغ *)اندريون;
}

#وصف_ڪريو FF_VK_STRUCT_EXT(CTX, بنياد, STRUCT_P, EXT_FLAG, TYPE) \
    افعل {                                                      \
        إذا ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(بنياد, STRUCT_P);                \
        }                                                     \
    } طالما (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
خارجي ثابت VkComponentMapping ff_comp_سڃاڻپ_عنصر_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
صحيح ff_vk_init(FFVulkanContext *s, فراغ *log_والد,
               AVBufferRef *device_ref, AVBufferRef *چوکٺا_ref);

/**
 * Converts Vulkan return values to strings
 */
ثابت حرف *ff_vk_ret2str(Vk_نتيجو res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_منزل_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_منزل_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
صحيح ff_vk_mt_is_np_rgb(تعداد AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
فراغ ff_vk_سيٽ_perm(تعداد AVPixelFormat pix_fmt, صحيح lut[4], صحيح inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, صحيح p);

/**
 * Returns the format to use for images in shaders.
 */
تعداد FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ثابت حرف *ff_vk_shader_rep_fmt(تعداد AVPixelFormat pix_fmt,
                                 تعداد FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_منزل_rep(VkFormat fmt, تعداد FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
صحيح ff_vk_ڀريو_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_قطار_Family *ff_vk_qf_ڳوليو(FFVulkanContext *s,
                                         Vk_قطار_Flag_بٽ dev_family,
                                         Vk_Video_Codec_Operation_Flag_بٽ_KHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
صحيح ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_قطار_Family *qf,
                         FFVkExecPool *pool, صحيح nb_contexts,
                         صحيح nb_queries, VkQueryType query_type, صحيح query_64bit,
                         ثابت فراغ *query_create_pnext);
فراغ ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_نتيجو ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              فراغ **معلومات, Vk_Query_نتيجو_Flag_بٽ flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
صحيح ff_vk_exec_شروعات(FFVulkanContext *s, FFVkExecContext *e);
صحيح ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
فراغ ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
فراغ ff_vk_exec_جوڙيو_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  فراغ *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
فراغ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   فراغ *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
فراغ ff_vk_exec_جوڙيو_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

فراغ ff_vk_exec_جوڙيو_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
فراغ ff_vk_exec_جوڙيو_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
فراغ ff_vk_exec_جوڙيو_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, صحيح nb,
                                 VkPipelineStageFlagBits2 stage,
                                 صحيح wait); /* Ownership transferred if !wait */
صحيح ff_vk_exec_جوڙيو_dep_چوکٺو(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
صحيح ff_vk_exec_جوڙيو_dep_sw_چوکٺو(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
فراغ ff_vk_exec_update_چوکٺو(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_يادگيري_Barrier2 *bar, uint32_t *nb_img_bar);
صحيح ff_vk_exec_mirror_sem_قدر(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
فراغ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
صحيح ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, صحيح plane, تعداد FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
تعريفنوع بنية FFVkImageViews {
    صحيح nb_views;

    VkDevice dev;
    ثابت Vk_ورهاست_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_انگ_معلومات_اشارا];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, صحيح nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
صحيح ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_انگ_معلومات_اشارا],
                            AVFrame *f, تعداد FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
صحيح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_انگ_معلومات_اشارا],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_انگ_معلومات_اشارا]);

#وصف_ڪريو ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    افعل {                                                                       \
        dst = (Vk_بفر_يادگيري_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_بفر_يادگيري_BARRIER_2,                \
            .src_Stage_نقاب = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_نقاب = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_نقاب = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_نقاب = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_قطار_Family_اشاريو = VK_قطار_FAMILY_IGNORED,                    \
            .dst_قطار_Family_اشاريو = VK_قطار_FAMILY_IGNORED,                    \
            .بفر = vkb->buf,                                                \
            .وٿي = offs,                                                    \
            .سائيز = bsz                                                        \
        };                                                                     \
    } طالما(0)

فراغ ff_vk_چوکٺو_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_يادگيري_Barrier2 *bar, صحيح *nb_bar,
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
صحيح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_يادگيري *mem,
                       صحيح ويڪر, صحيح اوچائي, VkFormat format, صحيح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, فراغ *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
فراغ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_يادگيري *mem);

صحيح ff_vk_alloc_mem(FFVulkanContext *s, Vk_يادگيري_Requirements *req,
                    Vk_يادگيري_Property_Flag_بٽ req_flags, فراغ *alloc_extension,
                    Vk_يادگيري_Property_Flag_بٽ *mem_flags, Vk_Device_يادگيري *mem);
صحيح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t سائيز,
                     فراغ *p_ايندڙ, فراغ *alloc_p_ايندڙ,
                     Vk_بفر_Usage_Flags usage, Vk_يادگيري_Property_Flag_بٽ flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
صحيح ff_vk_flush_بفر(FFVulkanContext *s, FFVk_بفر *buf,
                       Vk_Device_سائيز وٿي, Vk_Device_سائيز mem_سائيز,
                       صحيح flush);

/**
 * Buffer management code.
 */
صحيح ff_vk_map_buffers(FFVulkanContext *s, FFVk_بفر **buf, uint8_t *mem[],
                      صحيح nb_buffers, صحيح invalidate);
صحيح ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_بفر **buf, صحيح nb_buffers,
                        صحيح flush);

ساكن مضمن صحيح ff_vk_map_بفر(FFVulkanContext *s, FFVk_بفر *buf, uint8_t **mem,
                                   صحيح invalidate)
{
    أرجع ff_vk_map_buffers(s, (FFVk_بفر *[]){ buf }, mem,
                             1, invalidate);
}

ساكن مضمن صحيح ff_vk_unmap_بفر(FFVulkanContext *s, FFVk_بفر *buf, صحيح flush)
{
    أرجع ff_vk_unmap_buffers(s, (FFVk_بفر *[]){ buf }, 1, flush);
}

فراغ ff_vk_free_buf(FFVulkanContext *s, FFVk_بفر *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
صحيح ff_vk_get_pooled_بفر(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_بفر **buf, Vk_بفر_Usage_Flags usage,
                            فراغ *create_p_ايندڙ, size_t سائيز,
                            Vk_يادگيري_Property_Flag_بٽ mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
صحيح ff_vk_host_map_بفر(FFVulkanContext *s, FFVk_بفر **dst,
                          uint8_t *src_معلومات, Vk_Device_سائيز سائيز,
                          ثابت AVBufferRef *src_buf,
                          Vk_بفر_Usage_Flags usage);

/**
 * Create a sampler.
 */
صحيح ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       صحيح unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
صحيح ff_vk_shader_ڀريو(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_سائيز[3], uint32_t required_subgroup_سائيز);

/**
 * Link a shader into an executable.
 */
صحيح ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ثابت حرف *spirv, size_t spirv_len,
                      ثابت حرف *entrypoint);

/**
 * Add/update push constants for execution.
 */
صحيح ff_vk_shader_جوڙيو_ڌڪو_const(FFVulkanShader *shd, صحيح وٿي, صحيح سائيز,
                                Vk_Shader_Stage_Flag_بٽ stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
فراغ ff_vk_shader_جوڙيو_descriptor_سيٽ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سيٽ_Binding *desc, صحيح nb,
                                     صحيح singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
صحيح ff_vk_shader_رجسٽر_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
فراغ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ثابت FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
فراغ ff_vk_shader_update_ڌڪو_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بٽ stage,
                                    صحيح وٿي, size_t سائيز, فراغ *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
صحيح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحيح سيٽ, صحيح bind, صحيح elem,
                                    FFVk_بفر *buf, Vk_Device_سائيز وٿي, Vk_Device_سائيز len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
صحيح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحيح سيٽ, صحيح bind, صحيح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
فراغ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحيح سيٽ, صحيح binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
فراغ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
فراغ ff_vk_uninit(FFVulkanContext *s);

#جيڪڏهن_پورو /* AVUTIL_VULKAN_H */
