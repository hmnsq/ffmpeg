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

#جے_بنا_تعریف AVUTIL_VULKAN_H
#تعریف_کرو AVUTIL_VULKAN_H

#تعریف_کرو VK_NO_PROTOTYPES

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
#تعریف_کرو RET(x)                                                                 \
    افعل {                                                                       \
        إذا ((err = (x)) < 0)                                                   \
            اذهب fail;                                                         \
    } طالما (0)

/* Convenience macros for specialization lists */
#تعریف_کرو SPEC_LIST_MAX 256
#تعریف_کرو SPEC_LIST_CREATE(name, max_لمائی, max_ناپ)           \
    av_assert1((max_لمائی) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_ناپ) + 3*حجم(uint32_t)];      \
    Vk_Specialization_Map_اندراج name##_entries[(max_لمائی) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_انکڑے = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#تعریف_کرو SPEC_LIST_جوڑو(name, idx, val_بٹ, val)                \
افعل {                                                           \
    بنانشانی صحيح name##_cnt = name->map_اندراج_گنتی;             \
    size_t name##_off = name->انکڑے_ناپ_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_انکڑے;               \
    فراغ *name##_ep = (فراغ *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_بٹ, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_اندراج name##_new_entry = {              \
        .constantID = (idx),                                   \
        .وتھ = name##_off,                                  \
        .ناپ = val_بٹ >> 3,                                 \
    };                                                         \
    حافظہ_نقل(name##_ep, &name##_new_entry,                       \
           حجم(Vk_Specialization_Map_اندراج));                  \
    name->انکڑے_ناپ_2 = name##_off + (val_بٹ >> 3);             \
    name->map_اندراج_گنتی = name##_cnt + 1;                      \
} طالما (0)

#تعریف_کرو DUP_SAMPLER(x) { x, x, x, x }

#تعریف_کرو FF_VK_MAX_DESCRIPTOR_SETS 4
#تعریف_کرو FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#تعریف_کرو FF_VK_MAX_DESCRIPTOR_TYPES 16
#تعریف_کرو FF_VK_MAX_ڈالو_CONSTS 4
#تعریف_کرو FF_VK_MAX_SHADERS 16

تعريفنوع بنية FFVulkan_Descriptor_سیٹ_Binding {
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

تعريفنوع بنية FFVk_بفر {
    Vk_بفر buf;
    Vk_Device_حافظہ mem;
    Vk_حافظہ_Property_Flag_بٹ flags;
    size_t ناپ;
    Vk_Device_پتہ پتہ;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_وتھ;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_بفر;

/* Fixed dependency limits per exec context (with room to spare) */
#تعریف_کرو FF_VK_EXEC_MAX_چوکھٹا_DEPS 64
#تعریف_کرو FF_VK_EXEC_MAX_BUF_DEPS 256
#تعریف_کرو FF_VK_EXEC_MAX_SW_چوکھٹا_DEPS 16
#تعریف_کرو FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_چوکھٹا_DEPS*AV_عدد_انکڑے_سوچکاں)

/* Default number of in-flight execution contexts per pool */
#تعریف_کرو FF_VK_DEFAULT_EXEC_CONTEXTS 4

تعريفنوع بنية FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

تعريفنوع بنية FFVkExecContext {
    uint32_t idx;
    ثابت بنية FFVkExecPool *ماپا;

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
    pthread_mutex_t جندرا;

    /* Opaque data, untouched, free to use by users */
    فراغ *opaque;

    فراغ *query_انکڑے;
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
    AVFrame *چوکھٹا_deps[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    صحيح nb_چوکھٹا_deps;

    /* Software frame dependencies */
    AVFrame *sw_چوکھٹا_deps[FF_VK_EXEC_MAX_SW_چوکھٹا_DEPS];
    صحيح nb_sw_چوکھٹا_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    صحيح sem_sig_val_dst_cnt;

    uint8_t چوکھٹا_locked[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    Vk_Access_Flag_بٹ access_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    uint32_t قطار_family_dst[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
    uint8_t چوکھٹا_update[FF_VK_EXEC_MAX_چوکھٹا_DEPS];
} FFVkExecContext;

تعريفنوع بنية FFVulkan_Descriptor_سیٹ {
    /* Descriptor buffer */
    Vk_Device_ناپ layout_ناپ;
    Vk_Device_ناپ aligned_ناپ; /* descriptorBufferOffsetAlignment */
    Vk_بفر_Usage_Flags usage;

    Vk_Descriptor_سیٹ_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_ناپ binding_وتھ[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    صحيح nb_bindings;

    /* Descriptor set is shared between all submissions */
    صحيح singular;
} FFVulkan_Descriptor_سیٹ;

تعريفنوع بنية FFVulkanShader {
    /* Name for id/debugging purposes */
    ثابت حرف *name;

    /* Whether shader is precompiled or not */
    صحيح precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_ناپ[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_نقطہ bind_نقطہ;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_ناپ_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ڈالو_Constant_Range ڈالو_consts[FF_VK_MAX_ڈالو_CONSTS];
    صحيح ڈالو_consts_عدد;

    /* Descriptor sets */
    FFVulkan_Descriptor_سیٹ desc_سیٹ[FF_VK_MAX_DESCRIPTOR_SETS];
    صحيح nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_سیٹ_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    صحيح use_ڈالو;
    Vk_Descriptor_Pool_ناپ desc_pool_ناپ[FF_VK_MAX_DESCRIPTOR_TYPES];
    صحيح nb_desc_pool_ناپ;
} FFVulkanShader;

تعريفنوع بنية FFVulkan_Descriptor_سیٹ_انکڑے {
    /* Descriptor buffer */
    FFVk_بفر buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_سیٹ_انکڑے;

تعريفنوع بنية FFVulkan_Shader_انکڑے {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    صحيح nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_سیٹ_انکڑے desc_سیٹ_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_بفر_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_سیٹ *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_انکڑے;

تعريفنوع بنية FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_بفر *cmd_bufs;
    صحيح pool_ناپ;

    VkQueryPool query_pool;
    فراغ *query_انکڑے;
    صحيح query_results;
    صحيح query_statuses;
    صحيح query_64bit;
    صحيح query_حالت_stride;
    صحيح nb_queries;
    size_t qd_ناپ;

    /* Registered shaders' data */
    FFVulkan_Shader_انکڑے reg_shd[FF_VK_MAX_SHADERS];
    صحيح nb_reg_shd;
} FFVkExecPool;

تعريفنوع بنية FFVulkanContext {
    ثابت AVClass *class;
    فراغ *log_ماپا;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_حافظہ_Properties mprops;
    Vk_Physical_Device_External_حافظہ_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_بفر_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_ناپ_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_میٹرکس_Properties_KHR coop_میٹرکس_props;
    Vk_Physical_Device_ڈالو_Descriptor_Properties_KHR ڈالو_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#جے_تعریف_شدہ VK_EXT_shader_long_سمتیہ
    Vk_Physical_Device_Shader_Long_سمتیہ_Properties_EXT long_سمتیہ_props;
#جے_انت
    Vk_قطار_Family_Query_نتیجہ_حالت_Properties_KHR *query_props;
    Vk_قطار_Family_Video_Properties_KHR *video_props;
#جے_تعریف_شدہ VK_KHR_maintenance9
    Vk_قطار_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#جے_انت
    Vk_قطار_Family_Properties2 *qf_props;
    صحيح tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_میٹرکس_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#جے_تعریف_شدہ VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#جے_انت
#جے_تعریف_شدہ VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#جے_انت
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
    صحيح                    nb_qfs;

    /* Properties */
    صحيح                 output_چوڑائی;
    صحيح                output_اچائی;
    تعداد AVPixelFormat output_format;
    تعداد AVPixelFormat  داخلہ_format;
} FFVulkanContext;

ساكن مضمن صحيح ff_vk_گنتی_images(AVVk_چوکھٹا *f)
{
    صحيح cnt = 0;
    طالما (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    أرجع cnt;
}

ساكن مضمن ثابت فراغ *ff_vk_لبھو_struct(ثابت فراغ *chain, VkStructureType stype)
{
    ثابت Vk_ادھار_وچ_Structure *وچ = chain;
    طالما (وچ) {
        إذا (وچ->sType == stype)
            أرجع وچ;

        وچ = وچ->p_اگلا;
    }

    أرجع عدم;
}

ساكن مضمن فراغ ff_vk_link_struct(فراغ *chain, ثابت فراغ *وچ)
{
    Vk_ادھار_باہرلا_Structure *باہرلا = chain;
    طالما (باہرلا->p_اگلا)
        باہرلا = باہرلا->p_اگلا;

    باہرلا->p_اگلا = (فراغ *)وچ;
}

#تعریف_کرو FF_VK_STRUCT_EXT(CTX, ادھار, STRUCT_P, EXT_FLAG, TYPE) \
    افعل {                                                      \
        إذا ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(ادھار, STRUCT_P);                \
        }                                                     \
    } طالما (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
خارجي ثابت VkComponentMapping ff_comp_پچھان_تت_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
صحيح ff_vk_init(FFVulkanContext *s, فراغ *log_ماپا,
               AVBufferRef *device_ref, AVBufferRef *چوکھٹے_ref);

/**
 * Converts Vulkan return values to strings
 */
ثابت حرف *ff_vk_ret2str(Vk_نتیجہ res);

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
فراغ ff_vk_سیٹ_perm(تعداد AVPixelFormat pix_fmt, صحيح lut[4], صحيح inv);

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
صحيح ff_vk_لدو_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_قطار_Family *ff_vk_qf_لبھو(FFVulkanContext *s,
                                         Vk_قطار_Flag_بٹ dev_family,
                                         Vk_Video_Codec_Operation_Flag_بٹ_KHR vid_ops);

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
Vk_نتیجہ ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              فراغ **انکڑے, Vk_Query_نتیجہ_Flag_بٹ flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
صحيح ff_vk_exec_شروع(FFVulkanContext *s, FFVkExecContext *e);
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
فراغ ff_vk_exec_جوڑو_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  فراغ *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
فراغ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   فراغ *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
فراغ ff_vk_exec_جوڑو_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

فراغ ff_vk_exec_جوڑو_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
فراغ ff_vk_exec_جوڑو_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
فراغ ff_vk_exec_جوڑو_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, صحيح nb,
                                 VkPipelineStageFlagBits2 stage,
                                 صحيح wait); /* Ownership transferred if !wait */
صحيح ff_vk_exec_جوڑو_dep_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
صحيح ff_vk_exec_جوڑو_dep_sw_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
فراغ ff_vk_exec_update_چوکھٹا(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_حافظہ_Barrier2 *bar, uint32_t *nb_img_bar);
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
    ثابت Vk_ونڈ_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_عدد_انکڑے_سوچکاں];
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
                            VkImageView views[AV_عدد_انکڑے_سوچکاں],
                            AVFrame *f, تعداد FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
صحيح ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_عدد_انکڑے_سوچکاں],
                                AVFrame *f,
                                ثابت VkFormat fmts[AV_عدد_انکڑے_سوچکاں]);

#تعریف_کرو ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    افعل {                                                                       \
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
            .وتھ = offs,                                                    \
            .ناپ = bsz                                                        \
        };                                                                     \
    } طالما(0)

فراغ ff_vk_چوکھٹا_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_حافظہ_Barrier2 *bar, صحيح *nb_bar,
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
صحيح ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem,
                       صحيح چوڑائی, صحيح اچائی, VkFormat format, صحيح nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, فراغ *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
فراغ ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_حافظہ *mem);

صحيح ff_vk_alloc_mem(FFVulkanContext *s, Vk_حافظہ_Requirements *req,
                    Vk_حافظہ_Property_Flag_بٹ req_flags, فراغ *alloc_extension,
                    Vk_حافظہ_Property_Flag_بٹ *mem_flags, Vk_Device_حافظہ *mem);
صحيح ff_vk_create_buf(FFVulkanContext *s, FFVk_بفر *buf, size_t ناپ,
                     فراغ *p_اگلا, فراغ *alloc_p_اگلا,
                     Vk_بفر_Usage_Flags usage, Vk_حافظہ_Property_Flag_بٹ flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
صحيح ff_vk_flush_بفر(FFVulkanContext *s, FFVk_بفر *buf,
                       Vk_Device_ناپ وتھ, Vk_Device_ناپ mem_ناپ,
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
                            فراغ *create_p_اگلا, size_t ناپ,
                            Vk_حافظہ_Property_Flag_بٹ mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
صحيح ff_vk_host_map_بفر(FFVulkanContext *s, FFVk_بفر **dst,
                          uint8_t *src_انکڑے, Vk_Device_ناپ ناپ,
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
صحيح ff_vk_shader_لدو(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_ناپ[3], uint32_t required_subgroup_ناپ);

/**
 * Link a shader into an executable.
 */
صحيح ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ثابت حرف *spirv, size_t spirv_len,
                      ثابت حرف *entrypoint);

/**
 * Add/update push constants for execution.
 */
صحيح ff_vk_shader_جوڑو_ڈالو_const(FFVulkanShader *shd, صحيح وتھ, صحيح ناپ,
                                Vk_Shader_Stage_Flag_بٹ stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
فراغ ff_vk_shader_جوڑو_descriptor_سیٹ(FFVulkanContext *s, FFVulkanShader *shd,
                                     ثابت FFVulkan_Descriptor_سیٹ_Binding *desc, صحيح nb,
                                     صحيح singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
صحيح ff_vk_shader_رجسٹر_exec(FFVulkanContext *s, FFVkExecPool *pool,
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
فراغ ff_vk_shader_update_ڈالو_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_بٹ stage,
                                    صحيح وتھ, size_t ناپ, فراغ *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
صحيح ff_vk_shader_update_desc_بفر(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    صحيح سیٹ, صحيح bind, صحيح elem,
                                    FFVk_بفر *buf, Vk_Device_ناپ وتھ, Vk_Device_ناپ len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
صحيح ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, صحيح سیٹ, صحيح bind, صحيح offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
فراغ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, صحيح سیٹ, صحيح binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
فراغ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
فراغ ff_vk_uninit(FFVulkanContext *s);

#جے_انت /* AVUTIL_VULKAN_H */
