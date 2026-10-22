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

#اگر_غیر_تعریف_شدہ AVUTIL_VULKAN_H
#تعریف_کرو AVUTIL_VULKAN_H

#تعریف_کرو VK_NO_PROTOTYPES

#شامل <stdatomic.h>

#شامل "refstruct.h"

#شامل "thread.h"
#شامل "pixdesc.h"
#شامل "hwcontext.h"
#شامل "vulkan_functions.h"
#شامل "hwcontext_vulkan.h"
#شامل "avassert.h"
#شامل "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#تعریف_کرو RET(x)                                                                 \
    کرو {                                                                       \
        اگر ((err = (x)) < 0)                                                   \
            جاؤ fail;                                                         \
    } جب (0)

/* Convenience macros for specialization lists */
#تعریف_کرو SPEC_LIST_MAX 256
#تعریف_کرو SPEC_LIST_CREATE(name, max_لمبائی, max_سائز)           \
    av_assert1((max_لمبائی) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_سائز) + 3*حجم(uint32_t)];      \
    Vk_Specialization_Map_اندراج name##_entries[(max_لمبائی) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_ڈیٹا = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#تعریف_کرو SPEC_LIST_جوڑو(name, idx, val_بٹ, val)                \
کرو {                                                           \
    غیرعلامتی صحیح name##_cnt = name->map_اندراج_گنتی;             \
    size_t name##_off = name->ڈیٹا_سائز_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_ڈیٹا;               \
    خالی *name##_ep = (خالی *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_بٹ, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_اندراج name##_new_entry = {              \
        .constantID = (idx),                                   \
        .انحراف = name##_off,                                  \
        .سائز = val_بٹ >> 3,                                 \
    };                                                         \
    حافظہ_نقل(name##_ep, &name##_new_entry,                       \
           حجم(Vk_Specialization_Map_اندراج));                  \
    name->ڈیٹا_سائز_2 = name##_off + (val_بٹ >> 3);             \
    name->map_اندراج_گنتی = name##_cnt + 1;                      \
} جب (0)

#تعریف_کرو DUP_SAMPLER(x) { x, x, x, x }

#تعریف_کرو FF_VK_MAX_DESCRIPTOR_SETS 4
#تعریف_کرو FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#تعریف_کرو FF_VK_MAX_DESCRIPTOR_TYPES 16
#تعریف_کرو FF_VK_MAX_ڈالو_CONSTS 4
#تعریف_کرو FF_VK_MAX_SHADERS 16

قسمتعریف ساخت FFVulkan_Descriptor_سیٹ_Binding {
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
} FFVulkan_Descriptor_سیٹ_Binding;

قسمتعریف ساخت FFVk_بفر {
    Vk_بفر buf;
    Vk_Device_حافظہ mem;
    Vk_حافظہ_Property_Flag_بٹ flags;
    size_t سائز;
    Vk_Device_پتہ پتہ;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_انحراف;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_بفر;

/* Fixed dependency limits per exec context (with room to spare) */
#تعریف_کرو FF_VK_EXEC_MAX_چوکھٹا_DEPS 64
#تعریف_کرو FF_VK_EXEC_MAX_BUF_DEPS 256
#تعریف_کرو FF_VK_EXEC_MAX_SW_چوکھٹا_DEPS 16
#تعریف_کرو FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_چوکھٹا_DEPS*AV_عدد_ڈیٹا_اشارے)

/* Default number of in-flight execution contexts per pool */
#تعریف_کرو FF_VK_DEFAULT_EXEC_CONTEXTS 4

قسمتعریف ساخت FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

قسمتعریف ساخت FFVkExecContext {
    uint32_t idx;
    ثابت ساخت FFVkExecPool *والد;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    صحیح had_submission;

    /* Queue for the execution context */
    Vk_قطار قطار;
    صحیح qf;
    صحیح qi;

    /* Command buffer for the context */
    Vk_Command_بفر buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_قدر;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t تالا_2;

    /* Opaque data, untouched, free to use by users */
    خالی *opaque;

    خالی *query_ڈیٹا;
    صحیح query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحیح nb_buf_deps;

    /* AVRefStruct object dependencies */
    خالی *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحیح nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    صحیح nb_obj_deps;

    /* Frame dependencies */
    AVFrame *چوکھٹا_deps[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    صحیح nb_چوکھٹا_deps;

    /* Software frame dependencies */
    AVFrame *sw_چوکھٹا_deps[FF_VK_EXEC_MAX_SW_چوکھٹا_DEPS];
    صحیح nb_sw_چوکھٹا_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    صحیح sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    صحیح sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    صحیح sem_sig_val_dst_cnt;

    uint8_t چوکھٹا_locked[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    Vk_Access_Flag_بٹ access_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    uint32_t قطار_family_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    uint8_t چوکھٹا_update[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
} FFVkExecContext;

قسمتعریف ساخت FFVulkan_Descriptor_سیٹ {
    /* Descriptor buffer */
    Vk_Device_سائز layout_سائز;
    Vk_Device_سائز aligned_سائز; /* descriptorBufferOffsetAlignment */
    Vk_بفر_Usage_Flags usage;

    Vk_Descriptor_سیٹ_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_سائز binding_انحراف[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    صحیح nb_bindings;

    /* Descriptor set is shared between all submissions */
    صحیح singular;
} FFVulkan_Descriptor_سیٹ;

قسمتعریف ساخت FFVulkanShader {
    /* Name for id/debugging purposes */
    ثابت حرف *name;

    /* Whether shader is precompiled or not */
    صحیح precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_سائز[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_نقطہ bind_نقطہ;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_سائز_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ڈالو_Constant_Range ڈالو_consts[FF_VK_MAX_ڈالو_CONSTS];
    صحیح ڈالو_consts_عدد;

    /* Descriptor sets */
    FFVulkan_Descriptor_سیٹ desc_سیٹ[FF_VK_MAX_DESCRIPTOR_SETS];
    صحیح nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_سیٹ_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    صحیح use_ڈالو;
    Vk_Descriptor_Pool_سائز desc_pool_سائز[FF_VK_MAX_DESCRIPTOR_TYPES];
    صحیح nb_desc_pool_سائز;
} FFVulkanShader;

قسمتعریف ساخت FFVulkan_Descriptor_سیٹ_ڈیٹا {
    /* Descriptor buffer */
    FFVk_بفر buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_سیٹ_ڈیٹا;

قسمتعریف ساخت FFVulkan_Shader_ڈیٹا {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    صحیح nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_سیٹ_ڈیٹا desc_سیٹ_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_بفر_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_سیٹ *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_ڈیٹا;

قسمتعریف ساخت FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_بفر *cmd_bufs;
    صحیح pool_سائز;

    VkQueryPool query_pool;
    خالی *query_ڈیٹا;
    صحیح query_results;
    صحیح query_statuses;
    صحیح query_64bit;
    صحیح query_حالت_stride;
    صحیح nb_queries;
    size_t qd_سائز;

    /* Registered shaders' data */
    FFVulkan_Shader_ڈیٹا reg_shd[FF_VK_MAX_SHADERS];
    صحیح nb_reg_shd;
} FFVkExecPool;

قسمتعریف ساخت FFVulkanContext {
    ثابت AVClass *class;
    خالی *log_والد;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_حافظہ_Properties mprops;
    Vk_Physical_Device_External_حافظہ_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_بفر_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_سائز_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_میٹرکس_Properties_KHR coop_میٹرکس_props;
    Vk_Physical_Device_ڈالو_Descriptor_Properties_KHR ڈالو_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#اگر_تعریف_شدہ VK_EXT_shader_long_سمتیہ
    Vk_Physical_Device_Shader_Long_سمتیہ_Properties_EXT long_سمتیہ_props;
#اگر_ختم
    Vk_قطار_Family_Query_نتیجہ_حالت_Properties_KHR *query_props;
    Vk_قطار_Family_Video_Properties_KHR *video_props;
#اگر_تعریف_شدہ VK_KHR_maintenance9
    Vk_قطار_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#اگر_ختم
    Vk_قطار_Family_Properties2 *qf_props;
    صحیح tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_میٹرکس_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#اگر_تعریف_شدہ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#اگر_ختم
#اگر_تعریف_شدہ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#اگر_ختم
    VkPhysicalDeviceFeatures2 feats;

    Vk_حافظہ_Property_Flag_بٹ host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *داخلہ_چوکھٹے_ref;
    AVBufferRef           *چوکھٹے_ref;
    AVHWFramesContext     *چوکھٹے;
    AVVulkan_چوکھٹے_Context *hwfc;

    uint32_t               qfs[64];
    صحیح                    nb_qfs;

    /* Properties */
    صحیح                 output_چوڑائی;
    صحیح                output_اونچائی;
    شمار AVPixelFormat output_format;
    شمار AVPixelFormat  داخلہ_format;
} FFVulkanContext;

ساکن اندرونی صحیح ff_vk_گنتی_images(AVVk_چوکھٹا *f)
{
    صحیح cnt = 0;
    جب (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    واپس cnt;
}

ساکن اندرونی ثابت خالی *ff_vk_ڈھونڈو_struct(ثابت خالی *chain, VkStructureType stype)
{
    ثابت Vk_بنیاد_اندر_Structure *اندر = chain;
    جب (اندر) {
        اگر (اندر->sType == stype)
            واپس اندر;

        اندر = اندر->p_اگلا;
    }

    واپس تہی;
}

ساکن اندرونی خالی ff_vk_link_struct(خالی *chain, ثابت خالی *اندر)
{
    Vk_بنیاد_برآمد_Structure *برآمد = chain;
    جب (برآمد->p_اگلا)
        برآمد = برآمد->p_اگلا;

    برآمد->p_اگلا = (خالی *)اندر;
}

#تعریف_کرو FF_VK_STRUCT_EXT(CTX, بنیاد, STRUCT_P, EXT_FLAG, TYPE) \
    کرو {                                                      \
        اگر ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(بنیاد, STRUCT_P);                \
        }                                                     \
    } جب (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
خارجی ثابت VkComponentMapping ff_comp_شناختی_عنصر_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
صحیح ff_vk_init(FFVulkanContext *s, خالی *log_والد,
               AVBufferRef *device_ref, AVBufferRef *چوکھٹے_ref);

/**
 * Converts Vulkan return values to strings
 */
ثابت حرف *ff_vk_ret2str(Vk_نتیجہ res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_مقصد_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_مقصد_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
صحیح ff_vk_mt_is_np_rgb(شمار AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
خالی ff_vk_سیٹ_perm(شمار AVPixelFormat pix_fmt, صحیح lut[4], صحیح inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, صحیح p);

/**
 * Returns the format to use for images in shaders.
 */
شمار FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ثابت حرف *ff_vk_shader_rep_fmt(شمار AVPixelFormat pix_fmt,
                                 شمار FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_مقصد_rep(VkFormat fmt, شمار FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
صحیح ff_vk_بھرو_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_قطار_Family *ff_vk_qf_ڈھونڈو(FFVulkanContext *s,
                                         Vk_قطار_Flag_بٹ dev_family,
                                         Vk_Video_Codec_Operation_Flag_بٹ_KHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
صحیح ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_قطار_Family *qf,
                         FFVkExecPool *pool, صحیح nb_contexts,
                         صحیح nb_queries, VkQueryType query_type, صحیح query_64bit,
                         ثابت خالی *query_create_pnext);
خالی ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_نتیجہ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              خالی **ڈیٹا, Vk_Query_نتیجہ_Flag_بٹ flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
صحیح ff_vk_exec_آغاز(FFVulkanContext *s, FFVkExecContext *e);
صحیح ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
خالی ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
خالی ff_vk_exec_جوڑو_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  خالی *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
خالی ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   خالی *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
خالی ff_vk_exec_جوڑو_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

خالی ff_vk_exec_جوڑو_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
خالی ff_vk_exec_جوڑو_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
خالی ff_vk_exec_جوڑو_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, صحیح nb,
                                 VkPipelineStageFlagBits2 stage,
                                 صحیح wait); /* Ownership transferred if !wait */
صحیح ff_vk_exec_جوڑو_dep_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
صحیح ff_vk_exec_جوڑو_dep_sw_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
خالی ff_vk_exec_update_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_حافظہ_Barrier2 *bar, uint32_t *nb_img_bar);
صحیح ff_vk_exec_mirror_sem_قدر(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
خالی ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
صحیح ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, صحیح plane, شمار FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
قسمتعریف ساخت FFVkImageViews {
    صحیح nb_views;

    VkDevice dev;
    ثابت Vk_تخصیص_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_عدد_ڈیٹا_اشارے];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, صحیح nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
صحیح ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_عدد_ڈیٹا_اشارے],
                            AVFrame *f, شمار FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
صحیح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_عدد_ڈیٹا_اشارے],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_عدد_ڈیٹا_اشارے]);

#تعریف_کرو ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    کرو {                                                                       \
        dst = (Vk_بفر_حافظہ_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_بفر_حافظہ_BARRIER_2,                \
            .src_Stage_نقاب = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_نقاب = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_نقاب = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_نقاب = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_قطار_Family_اشاریہ = VK_قطار_FAMILY_IGNORED,                    \
            .dst_قطار_Family_اشاریہ = VK_قطار_FAMILY_IGNORED,                    \
            .بفر = vkb->buf,                                                \
            .انحراف = offs,                                                    \
            .سائز = bsz                                                        \
        };                                                                     \
    } جب(0)

خالی ff_vk_چوکھٹا_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_حافظہ_Barrier2 *bar, صحیح *nb_bar,
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
صحیح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem,
                       صحیح چوڑائی, صحیح اونچائی, VkFormat format, صحیح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, خالی *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
خالی ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem);

صحیح ff_vk_alloc_mem(FFVulkanContext *s, Vk_حافظہ_Requirements *req,
                    Vk_حافظہ_Property_Flag_بٹ req_flags, خالی *alloc_extension,
                    Vk_حافظہ_Property_Flag_بٹ *mem_flags, Vk_Device_حافظہ *mem);
صحیح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t سائز,
                     خالی *p_اگلا, خالی *alloc_p_اگلا,
                     Vk_بفر_Usage_Flags usage, Vk_حافظہ_Property_Flag_بٹ flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
صحیح ff_vk_flush_بفر(FFVulkanContext *s, FFVk_بفر *buf,
                       Vk_Device_سائز انحراف, Vk_Device_سائز mem_سائز,
                       صحیح flush);

/**
 * Buffer management code.
 */
صحیح ff_vk_map_buffers(FFVulkanContext *s, FFVk_بفر **buf, uint8_t *mem[],
                      صحیح nb_buffers, صحیح invalidate);
صحیح ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_بفر **buf, صحیح nb_buffers,
                        صحیح flush);

ساکن اندرونی صحیح ff_vk_map_بفر(FFVulkanContext *s, FFVk_بفر *buf, uint8_t **mem,
                                   صحیح invalidate)
{
    واپس ff_vk_map_buffers(s, (FFVk_بفر *[]){ buf }, mem,
                             1, invalidate);
}

ساکن اندرونی صحیح ff_vk_unmap_بفر(FFVulkanContext *s, FFVk_بفر *buf, صحیح flush)
{
    واپس ff_vk_unmap_buffers(s, (FFVk_بفر *[]){ buf }, 1, flush);
}

خالی ff_vk_free_buf(FFVulkanContext *s, FFVk_بفر *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
صحیح ff_vk_get_pooled_بفر(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_بفر **buf, Vk_بفر_Usage_Flags usage,
                            خالی *create_p_اگلا, size_t سائز,
                            Vk_حافظہ_Property_Flag_بٹ mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
صحیح ff_vk_host_map_بفر(FFVulkanContext *s, FFVk_بفر **dst,
                          uint8_t *src_ڈیٹا, Vk_Device_سائز سائز,
                          ثابت AVBufferRef *src_buf,
                          Vk_بفر_Usage_Flags usage);

/**
 * Create a sampler.
 */
صحیح ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       صحیح unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
صحیح ff_vk_shader_بھرو(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_سائز[3], uint32_t required_subgroup_سائز);

/**
 * Link a shader into an executable.
 */
صحیح ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ثابت حرف *spirv, size_t spirv_len,
                      ثابت حرف *entrypoint);

/**
 * Add/update push constants for execution.
 */
صحیح ff_vk_shader_جوڑو_ڈالو_const(FFVulkanShader *shd, صحیح انحراف, صحیح سائز,
                                Vk_Shader_Stage_Flag_بٹ stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
خالی ff_vk_shader_جوڑو_descriptor_سیٹ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سیٹ_Binding *desc, صحیح nb,
                                     صحیح singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
صحیح ff_vk_shader_رجسٹر_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
خالی ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ثابت FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
خالی ff_vk_shader_update_ڈالو_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بٹ stage,
                                    صحیح انحراف, size_t سائز, خالی *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
صحیح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحیح سیٹ, صحیح bind, صحیح elem,
                                    FFVk_بفر *buf, Vk_Device_سائز انحراف, Vk_Device_سائز len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
صحیح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحیح سیٹ, صحیح bind, صحیح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
خالی ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحیح سیٹ, صحیح binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
خالی ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
خالی ff_vk_uninit(FFVulkanContext *s);

#اگر_ختم /* AVUTIL_VULKAN_H */
