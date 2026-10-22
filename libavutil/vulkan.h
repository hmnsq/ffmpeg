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

#ifndef AVUTIL_VULKAN_H
#define AVUTIL_VULKAN_H

#define VK_NO_PROTOTYPES

#অন্তর্ভাব <stdatomic.h>

#অন্তর্ভাব "refstruct.h"

#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "vulkan_functions.h"
#অন্তর্ভাব "hwcontext_vulkan.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#define RET(x)                                                                 \
    করো {                                                                       \
        যদি ((err = (x)) < 0)                                                   \
            যাও fail;                                                         \
    } যখন (0)

/* Convenience macros for specialization lists */
#define SPEC_LIST_MAX 256
#define SPEC_LIST_CREATE(name, max_দৈর্ঘ্য, max_আকার)           \
    av_assert1((max_দৈর্ঘ্য) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_আকার) + 3*আকার(uint32_t)];      \
    VkSpecializationMapEntry name##_entries[(max_দৈর্ঘ্য) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_তথ্য = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#define SPEC_LIST_ADD(name, idx, val_bits, val)                \
করো {                                                           \
    unsigned পূর্ণসংখ্যা name##_cnt = name->map_Entry_গুনতি;             \
    size_t name##_off = name->তথ্য_আকার_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_তথ্য;               \
    শূন্য *name##_ep = (শূন্য *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_bits, name##_dp + name##_off, (val));            \
    VkSpecializationMapEntry name##_new_entry = {              \
        .constantID = (idx),                                   \
        .offset = name##_off,                                  \
        .আকার_2 = val_bits >> 3,                                 \
    };                                                         \
    memcpy(name##_ep, &name##_new_entry,                       \
           আকার(VkSpecializationMapEntry));                  \
    name->তথ্য_আকার_2 = name##_off + (val_bits >> 3);             \
    name->map_Entry_গুনতি = name##_cnt + 1;                      \
} যখন (0)

#define DUP_SAMPLER(x) { x, x, x, x }

#define FF_VK_MAX_DESCRIPTOR_SETS 4
#define FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#define FF_VK_MAX_DESCRIPTOR_TYPES 16
#define FF_VK_MAX_ঠেলো_CONSTS 4
#define FF_VK_MAX_SHADERS 16

প্রকারলেখ কাঠামো FFVulkanDescriptorSetBinding {
    ধ্রুবক অক্ষর         *name;
    VkDescriptorType    type;
    ধ্রুবক অক্ষর         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ধ্রুবক অক্ষর         *mem_quali;   /* readonly, writeonly, etc. */
    ধ্রুবক অক্ষর         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkanDescriptorSetBinding;

প্রকারলেখ কাঠামো FFVk_বাফার {
    Vk_বাফার buf;
    VkDeviceMemory mem;
    VkMemoryPropertyFlagBits flags;
    size_t আকার_2;
    VkDeviceAddress address;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_offset;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_বাফার;

/* Fixed dependency limits per exec context (with room to spare) */
#define FF_VK_EXEC_MAX_FRAME_DEPS 64
#define FF_VK_EXEC_MAX_BUF_DEPS 256
#define FF_VK_EXEC_MAX_SW_FRAME_DEPS 16
#define FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_অঙ্ক_তথ্য_POINTERS)

/* Default number of in-flight execution contexts per pool */
#define FF_VK_DEFAULT_EXEC_CONTEXTS 4

প্রকারলেখ কাঠামো FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

প্রকারলেখ কাঠামো FFVkExecContext {
    uint32_t idx;
    ধ্রুবক কাঠামো FFVkExecPool *parent;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    পূর্ণসংখ্যা had_submission;

    /* Queue for the execution context */
    VkQueue queue;
    পূর্ণসংখ্যা qf;
    পূর্ণসংখ্যা qi;

    /* Command buffer for the context */
    Vk_Command_বাফার buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_মান;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t lock;

    /* Opaque data, untouched, free to use by users */
    শূন্য *opaque;

    শূন্য *query_তথ্য;
    পূর্ণসংখ্যা query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণসংখ্যা nb_buf_deps;

    /* AVRefStruct object dependencies */
    শূন্য *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণসংখ্যা nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণসংখ্যা nb_obj_deps;

    /* Frame dependencies */
    AVFrame *frame_deps[FF_VK_EXEC_MAX_FRAME_DEPS];
    পূর্ণসংখ্যা nb_frame_deps;

    /* Software frame dependencies */
    AVFrame *sw_frame_deps[FF_VK_EXEC_MAX_SW_FRAME_DEPS];
    পূর্ণসংখ্যা nb_sw_frame_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণসংখ্যা sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণসংখ্যা sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণসংখ্যা sem_sig_val_dst_cnt;

    uint8_t frame_locked[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkAccessFlagBits access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

প্রকারলেখ কাঠামো FFVulkanDescriptorSet {
    /* Descriptor buffer */
    Vk_Device_আকার layout_আকার;
    Vk_Device_আকার aligned_আকার; /* descriptorBufferOffsetAlignment */
    Vk_বাফার_Usage_Flags usage;

    VkDescriptorSetLayoutBinding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_আকার binding_offset[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    পূর্ণসংখ্যা nb_bindings;

    /* Descriptor set is shared between all submissions */
    পূর্ণসংখ্যা singular;
} FFVulkanDescriptorSet;

প্রকারলেখ কাঠামো FFVulkanShader {
    /* Name for id/debugging purposes */
    ধ্রুবক অক্ষর *name;

    /* Whether shader is precompiled or not */
    পূর্ণসংখ্যা precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_আকার[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    VkPipelineBindPoint bind_point;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_আকার_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ঠেলো_Constant_Range ঠেলো_consts[FF_VK_MAX_ঠেলো_CONSTS];
    পূর্ণসংখ্যা ঠেলো_consts_অঙ্ক;

    /* Descriptor sets */
    FFVulkanDescriptorSet desc_set[FF_VK_MAX_DESCRIPTOR_SETS];
    পূর্ণসংখ্যা nb_descriptor_sets;

    /* Descriptors */
    VkDescriptorSetLayout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    পূর্ণসংখ্যা use_ঠেলো;
    Vk_Descriptor_Pool_আকার desc_pool_আকার[FF_VK_MAX_DESCRIPTOR_TYPES];
    পূর্ণসংখ্যা nb_desc_pool_আকার;
} FFVulkanShader;

প্রকারলেখ কাঠামো FFVulkan_Descriptor_Set_তথ্য {
    /* Descriptor buffer */
    FFVk_বাফার buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_Set_তথ্য;

প্রকারলেখ কাঠামো FFVulkan_Shader_তথ্য {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    পূর্ণসংখ্যা nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_Set_তথ্য desc_set_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_বাফার_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    VkDescriptorSet *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_তথ্য;

প্রকারলেখ কাঠামো FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_বাফার *cmd_bufs;
    পূর্ণসংখ্যা pool_আকার;

    VkQueryPool query_pool;
    শূন্য *query_তথ্য;
    পূর্ণসংখ্যা query_results;
    পূর্ণসংখ্যা query_statuses;
    পূর্ণসংখ্যা query_64bit;
    পূর্ণসংখ্যা query_status_stride;
    পূর্ণসংখ্যা nb_queries;
    size_t qd_আকার;

    /* Registered shaders' data */
    FFVulkan_Shader_তথ্য reg_shd[FF_VK_MAX_SHADERS];
    পূর্ণসংখ্যা nb_reg_shd;
} FFVkExecPool;

প্রকারলেখ কাঠামো FFVulkanContext {
    ধ্রুবক AVClass *class;
    শূন্য *log_parent;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    VkPhysicalDeviceMemoryProperties mprops;
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT hprops;
    Vk_Physical_Device_Descriptor_বাফার_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_আকার_Control_Properties subgroup_props;
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR coop_matrix_props;
    Vk_Physical_Device_ঠেলো_Descriptor_Properties_KHR ঠেলো_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#ifdef VK_EXT_shader_long_vector
    VkPhysicalDeviceShaderLongVectorPropertiesEXT long_vector_props;
#endif
    Vk_Queue_Family_Query_ফলাফল_Status_Properties_KHR *query_props;
    VkQueueFamilyVideoPropertiesKHR *video_props;
#ifdef VK_KHR_maintenance9
    VkQueueFamilyOwnershipTransferPropertiesKHR *ownership_props;
#endif
    VkQueueFamilyProperties2 *qf_props;
    পূর্ণসংখ্যা tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    VkCooperativeMatrixPropertiesKHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#ifdef VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#endif
#ifdef VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#endif
    VkPhysicalDeviceFeatures2 feats;

    VkMemoryPropertyFlagBits host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *প্রবেশ_frames_ref;
    AVBufferRef           *frames_ref;
    AVHWFramesContext     *frames;
    AVVulkanFramesContext *hwfc;

    uint32_t               qfs[64];
    পূর্ণসংখ্যা                    nb_qfs;

    /* Properties */
    পূর্ণসংখ্যা                 output_width;
    পূর্ণসংখ্যা                output_height;
    গণনা AVPixelFormat output_format;
    গণনা AVPixelFormat  প্রবেশ_format;
} FFVulkanContext;

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_vk_গুনতি_images(AVVkFrame *f)
{
    পূর্ণসংখ্যা cnt = 0;
    যখন (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    ফেরত cnt;
}

স্থির অন্তঃরেখ ধ্রুবক শূন্য *ff_vk_find_struct(ধ্রুবক শূন্য *chain, VkStructureType stype)
{
    ধ্রুবক VkBaseInStructure *in = chain;
    যখন (in) {
        যদি (in->sType == stype)
            ফেরত in;

        in = in->p_পরবর্তী;
    }

    ফেরত ফাঁকা;
}

স্থির অন্তঃরেখ শূন্য ff_vk_link_struct(শূন্য *chain, ধ্রুবক শূন্য *in)
{
    VkBaseOutStructure *out = chain;
    যখন (out->p_পরবর্তী)
        out = out->p_পরবর্তী;

    out->p_পরবর্তী = (শূন্য *)in;
}

#define FF_VK_STRUCT_EXT(CTX, BASE, STRUCT_P, EXT_FLAG, TYPE) \
    করো {                                                      \
        যদি ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(BASE, STRUCT_P);                \
        }                                                     \
    } যখন (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
বাহ্যিক ধ্রুবক VkComponentMapping ff_comp_identity_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
পূর্ণসংখ্যা ff_vk_init(FFVulkanContext *s, শূন্য *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref);

/**
 * Converts Vulkan return values to strings
 */
ধ্রুবক অক্ষর *ff_vk_ret2str(Vk_ফলাফল res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_to_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_to_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
পূর্ণসংখ্যা ff_vk_mt_is_np_rgb(গণনা AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
শূন্য ff_vk_set_perm(গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা lut[4], পূর্ণসংখ্যা inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, পূর্ণসংখ্যা p);

/**
 * Returns the format to use for images in shaders.
 */
গণনা FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ধ্রুবক অক্ষর *ff_vk_shader_rep_fmt(গণনা AVPixelFormat pix_fmt,
                                 গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
পূর্ণসংখ্যা ff_vk_load_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         VkQueueFlagBits dev_family,
                                         VkVideoCodecOperationFlagBitsKHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
পূর্ণসংখ্যা ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, পূর্ণসংখ্যা nb_contexts,
                         পূর্ণসংখ্যা nb_queries, VkQueryType query_type, পূর্ণসংখ্যা query_64bit,
                         ধ্রুবক শূন্য *query_create_pnext);
শূন্য ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_ফলাফল ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              শূন্য **তথ্য, Vk_Query_ফলাফল_Flag_Bits flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
পূর্ণসংখ্যা ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e);
পূর্ণসংখ্যা ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
শূন্য ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
শূন্য ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  শূন্য *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
শূন্য ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   শূন্য *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
শূন্য ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

শূন্য ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
শূন্য ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
শূন্য ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, পূর্ণসংখ্যা nb,
                                 VkPipelineStageFlagBits2 stage,
                                 পূর্ণসংখ্যা wait); /* Ownership transferred if !wait */
পূর্ণসংখ্যা ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
পূর্ণসংখ্যা ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
শূন্য ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar);
পূর্ণসংখ্যা ff_vk_exec_mirror_sem_মান(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
শূন্য ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
পূর্ণসংখ্যা ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, পূর্ণসংখ্যা plane, গণনা FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
প্রকারলেখ কাঠামো FFVkImageViews {
    পূর্ণসংখ্যা nb_views;

    VkDevice dev;
    ধ্রুবক VkAllocationCallbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_অঙ্ক_তথ্য_POINTERS];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, পূর্ণসংখ্যা nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
পূর্ণসংখ্যা ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_অঙ্ক_তথ্য_POINTERS],
                            AVFrame *f, গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
পূর্ণসংখ্যা ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_অঙ্ক_তথ্য_POINTERS],
                                AVFrame *f,
                                ধ্রুবক VkFormat fmts[AV_অঙ্ক_তথ্য_POINTERS]);

#define ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    করো {                                                                       \
        dst = (Vk_বাফার_Memory_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_বাফার_MEMORY_BARRIER_2,                \
            .srcStageMask = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .srcAccessMask = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dstStageMask = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dstAccessMask = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_Queue_Family_সূচক = VK_QUEUE_FAMILY_IGNORED,                    \
            .dst_Queue_Family_সূচক = VK_QUEUE_FAMILY_IGNORED,                    \
            .বাফার = vkb->buf,                                                \
            .offset = offs,                                                    \
            .আকার_2 = bsz                                                        \
        };                                                                     \
    } যখন(0)

শূন্য ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, পূর্ণসংখ্যা *nb_bar,
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
পূর্ণসংখ্যা ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, VkFormat format, পূর্ণসংখ্যা nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, শূন্য *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
শূন্য ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem);

পূর্ণসংখ্যা ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, শূন্য *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem);
পূর্ণসংখ্যা ff_vk_create_buf(FFVulkanContext *s, FFVk_বাফার *buf, size_t আকার_2,
                     শূন্য *p_পরবর্তী, শূন্য *alloc_p_পরবর্তী,
                     Vk_বাফার_Usage_Flags usage, VkMemoryPropertyFlagBits flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
পূর্ণসংখ্যা ff_vk_flush_বাফার(FFVulkanContext *s, FFVk_বাফার *buf,
                       Vk_Device_আকার offset, Vk_Device_আকার mem_আকার,
                       পূর্ণসংখ্যা flush);

/**
 * Buffer management code.
 */
পূর্ণসংখ্যা ff_vk_map_buffers(FFVulkanContext *s, FFVk_বাফার **buf, uint8_t *mem[],
                      পূর্ণসংখ্যা nb_buffers, পূর্ণসংখ্যা invalidate);
পূর্ণসংখ্যা ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_বাফার **buf, পূর্ণসংখ্যা nb_buffers,
                        পূর্ণসংখ্যা flush);

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_vk_map_বাফার(FFVulkanContext *s, FFVk_বাফার *buf, uint8_t **mem,
                                   পূর্ণসংখ্যা invalidate)
{
    ফেরত ff_vk_map_buffers(s, (FFVk_বাফার *[]){ buf }, mem,
                             1, invalidate);
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_vk_unmap_বাফার(FFVulkanContext *s, FFVk_বাফার *buf, পূর্ণসংখ্যা flush)
{
    ফেরত ff_vk_unmap_buffers(s, (FFVk_বাফার *[]){ buf }, 1, flush);
}

শূন্য ff_vk_free_buf(FFVulkanContext *s, FFVk_বাফার *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
পূর্ণসংখ্যা ff_vk_get_pooled_বাফার(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_বাফার **buf, Vk_বাফার_Usage_Flags usage,
                            শূন্য *create_p_পরবর্তী, size_t আকার_2,
                            VkMemoryPropertyFlagBits mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
পূর্ণসংখ্যা ff_vk_host_map_বাফার(FFVulkanContext *s, FFVk_বাফার **dst,
                          uint8_t *src_তথ্য, Vk_Device_আকার আকার_2,
                          ধ্রুবক AVBufferRef *src_buf,
                          Vk_বাফার_Usage_Flags usage);

/**
 * Create a sampler.
 */
পূর্ণসংখ্যা ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       পূর্ণসংখ্যা unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
পূর্ণসংখ্যা ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_আকার[3], uint32_t required_subgroup_আকার);

/**
 * Link a shader into an executable.
 */
পূর্ণসংখ্যা ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ধ্রুবক অক্ষর *spirv, size_t spirv_len,
                      ধ্রুবক অক্ষর *entrypoint);

/**
 * Add/update push constants for execution.
 */
পূর্ণসংখ্যা ff_vk_shader_add_ঠেলো_const(FFVulkanShader *shd, পূর্ণসংখ্যা offset, পূর্ণসংখ্যা আকার_2,
                                VkShaderStageFlagBits stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
শূন্য ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ধ্রুবক FFVulkanDescriptorSetBinding *desc, পূর্ণসংখ্যা nb,
                                     পূর্ণসংখ্যা singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
পূর্ণসংখ্যা ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
শূন্য ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ধ্রুবক FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
শূন্য ff_vk_shader_update_ঠেলো_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    পূর্ণসংখ্যা offset, size_t আকার_2, শূন্য *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
পূর্ণসংখ্যা ff_vk_shader_update_desc_বাফার(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    পূর্ণসংখ্যা set, পূর্ণসংখ্যা bind, পূর্ণসংখ্যা elem,
                                    FFVk_বাফার *buf, Vk_Device_আকার offset, Vk_Device_আকার len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
পূর্ণসংখ্যা ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, পূর্ণসংখ্যা set, পূর্ণসংখ্যা bind, পূর্ণসংখ্যা offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
শূন্য ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, পূর্ণসংখ্যা set, পূর্ণসংখ্যা binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
শূন্য ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
শূন্য ff_vk_uninit(FFVulkanContext *s);

#endif /* AVUTIL_VULKAN_H */
