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

#অন্তর্ভাৱ <stdatomic.h>

#অন্তর্ভাৱ "refstruct.h"

#অন্তর্ভাৱ "thread.h"
#অন্তর্ভাৱ "pixdesc.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ "vulkan_functions.h"
#অন্তর্ভাৱ "hwcontext_vulkan.h"
#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#define RET(x)                                                                 \
    কৰা {                                                                       \
        যদি ((err = (x)) < 0)                                                   \
            গচ্ছ fail;                                                         \
    } যেতিয়ালৈ (0)

/* Convenience macros for specialization lists */
#define SPEC_LIST_MAX 256
#define SPEC_LIST_CREATE(name, max_length, max_size)           \
    av_assert1((max_length) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_size) + 3*পরিমাণ(uint32_t)];      \
    VkSpecializationMapEntry name##_entries[(max_length) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .pData = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#define SPEC_LIST_ADD(name, idx, val_bits, val)                \
কৰা {                                                           \
    unsigned পূর্ণাঙ্ক name##_cnt = name->map_Entry_গুনতি;             \
    size_t name##_off = name->dataSize;                        \
    uint8_t *name##_dp = (uint8_t *)name->pData;               \
    শূন্য *name##_ep = (শূন্য *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_bits, name##_dp + name##_off, (val));            \
    VkSpecializationMapEntry name##_new_entry = {              \
        .constantID = (idx),                                   \
        .offset = name##_off,                                  \
        .size = val_bits >> 3,                                 \
    };                                                         \
    memcpy(name##_ep, &name##_new_entry,                       \
           পরিমাণ(VkSpecializationMapEntry));                  \
    name->dataSize = name##_off + (val_bits >> 3);             \
    name->map_Entry_গুনতি = name##_cnt + 1;                      \
} যেতিয়ালৈ (0)

#define DUP_SAMPLER(x) { x, x, x, x }

#define FF_VK_MAX_DESCRIPTOR_SETS 4
#define FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#define FF_VK_MAX_DESCRIPTOR_TYPES 16
#define FF_VK_MAX_ঠেলো_CONSTS 4
#define FF_VK_MAX_SHADERS 16

প্রকারনির্দেশ সংরচনা FFVulkanDescriptorSetBinding {
    ধ্রুৱ ৱর্ণ         *name;
    VkDescriptorType    type;
    ধ্রুৱ ৱর্ণ         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ধ্রুৱ ৱর্ণ         *mem_quali;   /* readonly, writeonly, etc. */
    ধ্রুৱ ৱর্ণ         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkanDescriptorSetBinding;

প্রকারনির্দেশ সংরচনা FFVkBuffer {
    VkBuffer buf;
    VkDeviceMemory mem;
    VkMemoryPropertyFlagBits flags;
    size_t size;
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
} FFVkBuffer;

/* Fixed dependency limits per exec context (with room to spare) */
#define FF_VK_EXEC_MAX_FRAME_DEPS 64
#define FF_VK_EXEC_MAX_BUF_DEPS 256
#define FF_VK_EXEC_MAX_SW_FRAME_DEPS 16
#define FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_অঙ্ক_DATA_POINTERS)

/* Default number of in-flight execution contexts per pool */
#define FF_VK_DEFAULT_EXEC_CONTEXTS 4

প্রকারনির্দেশ সংরচনা FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

প্রকারনির্দেশ সংরচনা FFVkExecContext {
    uint32_t idx;
    ধ্রুৱ সংরচনা FFVkExecPool *parent;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    পূর্ণাঙ্ক had_submission;

    /* Queue for the execution context */
    VkQueue queue;
    পূর্ণাঙ্ক qf;
    পূর্ণাঙ্ক qi;

    /* Command buffer for the context */
    VkCommandBuffer buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_মান;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t lock;

    /* Opaque data, untouched, free to use by users */
    শূন্য *opaque;

    শূন্য *query_data;
    পূর্ণাঙ্ক query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণাঙ্ক nb_buf_deps;

    /* AVRefStruct object dependencies */
    শূন্য *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণাঙ্ক nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    পূর্ণাঙ্ক nb_obj_deps;

    /* Frame dependencies */
    AVFrame *frame_deps[FF_VK_EXEC_MAX_FRAME_DEPS];
    পূর্ণাঙ্ক nb_frame_deps;

    /* Software frame dependencies */
    AVFrame *sw_frame_deps[FF_VK_EXEC_MAX_SW_FRAME_DEPS];
    পূর্ণাঙ্ক nb_sw_frame_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণাঙ্ক sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণাঙ্ক sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    পূর্ণাঙ্ক sem_sig_val_dst_cnt;

    uint8_t frame_locked[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkAccessFlagBits access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

প্রকারনির্দেশ সংরচনা FFVulkanDescriptorSet {
    /* Descriptor buffer */
    VkDeviceSize layout_size;
    VkDeviceSize aligned_size; /* descriptorBufferOffsetAlignment */
    VkBufferUsageFlags usage;

    VkDescriptorSetLayoutBinding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    VkDeviceSize binding_offset[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    পূর্ণাঙ্ক nb_bindings;

    /* Descriptor set is shared between all submissions */
    পূর্ণাঙ্ক singular;
} FFVulkanDescriptorSet;

প্রকারনির্দেশ সংরচনা FFVulkanShader {
    /* Name for id/debugging purposes */
    ধ্রুৱ ৱর্ণ *name;

    /* Whether shader is precompiled or not */
    পূর্ণাঙ্ক precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_size[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    VkPipelineBindPoint bind_point;

    /* Creation info */
    VkPipelineShaderStageRequiredSubgroupSizeCreateInfo subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_ঠেলো_Constant_Range ঠেলো_consts[FF_VK_MAX_ঠেলো_CONSTS];
    পূর্ণাঙ্ক ঠেলো_consts_অঙ্ক;

    /* Descriptor sets */
    FFVulkanDescriptorSet desc_set[FF_VK_MAX_DESCRIPTOR_SETS];
    পূর্ণাঙ্ক nb_descriptor_sets;

    /* Descriptors */
    VkDescriptorSetLayout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    পূর্ণাঙ্ক use_ঠেলো;
    VkDescriptorPoolSize desc_pool_size[FF_VK_MAX_DESCRIPTOR_TYPES];
    পূর্ণাঙ্ক nb_desc_pool_size;
} FFVulkanShader;

প্রকারনির্দেশ সংরচনা FFVulkanDescriptorSetData {
    /* Descriptor buffer */
    FFVkBuffer buf;
    uint8_t *desc_mem;
} FFVulkanDescriptorSetData;

প্রকারনির্দেশ সংরচনা FFVulkanShaderData {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    পূর্ণাঙ্ক nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkanDescriptorSetData desc_set_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    VkDescriptorBufferBindingInfoEXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    VkDescriptorSet *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkanShaderData;

প্রকারনির্দেশ সংরচনা FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    VkCommandBuffer *cmd_bufs;
    পূর্ণাঙ্ক pool_size;

    VkQueryPool query_pool;
    শূন্য *query_data;
    পূর্ণাঙ্ক query_results;
    পূর্ণাঙ্ক query_statuses;
    পূর্ণাঙ্ক query_64bit;
    পূর্ণাঙ্ক query_status_stride;
    পূর্ণাঙ্ক nb_queries;
    size_t qd_size;

    /* Registered shaders' data */
    FFVulkanShaderData reg_shd[FF_VK_MAX_SHADERS];
    পূর্ণাঙ্ক nb_reg_shd;
} FFVkExecPool;

প্রকারনির্দেশ সংরচনা FFVulkanContext {
    ধ্রুৱ AVClass *class;
    শূন্য *log_parent;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    VkPhysicalDeviceMemoryProperties mprops;
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT hprops;
    VkPhysicalDeviceDescriptorBufferPropertiesEXT desc_buf_props;
    VkPhysicalDeviceSubgroupSizeControlProperties subgroup_props;
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR coop_matrix_props;
    Vk_Physical_Device_ঠেলো_Descriptor_Properties_KHR ঠেলো_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#ifdef VK_EXT_shader_long_vector
    VkPhysicalDeviceShaderLongVectorPropertiesEXT long_vector_props;
#endif
    VkQueueFamilyQueryResultStatusPropertiesKHR *query_props;
    VkQueueFamilyVideoPropertiesKHR *video_props;
#ifdef VK_KHR_maintenance9
    VkQueueFamilyOwnershipTransferPropertiesKHR *ownership_props;
#endif
    VkQueueFamilyProperties2 *qf_props;
    পূর্ণাঙ্ক tot_nb_qfs;
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

    AVBufferRef           *প্ৰবেশ_frames_ref;
    AVBufferRef           *frames_ref;
    AVHWFramesContext     *frames;
    AVVulkanFramesContext *hwfc;

    uint32_t               qfs[64];
    পূর্ণাঙ্ক                    nb_qfs;

    /* Properties */
    পূর্ণাঙ্ক                 output_width;
    পূর্ণাঙ্ক                output_height;
    গণনা AVPixelFormat output_format;
    গণনা AVPixelFormat  প্ৰবেশ_format;
} FFVulkanContext;

স্থির অন্তঃস্থ পূর্ণাঙ্ক ff_vk_গুনতি_images(AVVkFrame *f)
{
    পূর্ণাঙ্ক cnt = 0;
    যেতিয়ালৈ (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    ঘূৰাই cnt;
}

স্থির অন্তঃস্থ ধ্রুৱ শূন্য *ff_vk_find_struct(ধ্রুৱ শূন্য *chain, VkStructureType stype)
{
    ধ্রুৱ VkBaseInStructure *in = chain;
    যেতিয়ালৈ (in) {
        যদি (in->sType == stype)
            ঘূৰাই in;

        in = in->pNext;
    }

    ঘূৰাই রিক্ত;
}

স্থির অন্তঃস্থ শূন্য ff_vk_link_struct(শূন্য *chain, ধ্রুৱ শূন্য *in)
{
    VkBaseOutStructure *out = chain;
    যেতিয়ালৈ (out->pNext)
        out = out->pNext;

    out->pNext = (শূন্য *)in;
}

#define FF_VK_STRUCT_EXT(CTX, BASE, STRUCT_P, EXT_FLAG, TYPE) \
    কৰা {                                                      \
        যদি ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(BASE, STRUCT_P);                \
        }                                                     \
    } যেতিয়ালৈ (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
বাহ্য ধ্রুৱ VkComponentMapping ff_comp_identity_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
পূর্ণাঙ্ক ff_vk_init(FFVulkanContext *s, শূন্য *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref);

/**
 * Converts Vulkan return values to strings
 */
ধ্রুৱ ৱর্ণ *ff_vk_ret2str(VkResult res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_to_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_to_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
পূর্ণাঙ্ক ff_vk_mt_is_np_rgb(গণনা AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
শূন্য ff_vk_set_perm(গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক lut[4], পূর্ণাঙ্ক inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, পূর্ণাঙ্ক p);

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
ধ্রুৱ ৱর্ণ *ff_vk_shader_rep_fmt(গণনা AVPixelFormat pix_fmt,
                                 গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
পূর্ণাঙ্ক ff_vk_load_props(FFVulkanContext *s);

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
পূর্ণাঙ্ক ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, পূর্ণাঙ্ক nb_contexts,
                         পূর্ণাঙ্ক nb_queries, VkQueryType query_type, পূর্ণাঙ্ক query_64bit,
                         ধ্রুৱ শূন্য *query_create_pnext);
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
VkResult ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              শূন্য **data, VkQueryResultFlagBits flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
পূর্ণাঙ্ক ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e);
পূর্ণাঙ্ক ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
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
                                 VkSemaphore *sem, পূর্ণাঙ্ক nb,
                                 VkPipelineStageFlagBits2 stage,
                                 পূর্ণাঙ্ক wait); /* Ownership transferred if !wait */
পূর্ণাঙ্ক ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
পূর্ণাঙ্ক ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
শূন্য ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar);
পূর্ণাঙ্ক ff_vk_exec_mirror_sem_মান(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
শূন্য ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
পূর্ণাঙ্ক ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, পূর্ণাঙ্ক plane, গণনা FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
প্রকারনির্দেশ সংরচনা FFVkImageViews {
    পূর্ণাঙ্ক nb_views;

    VkDevice dev;
    ধ্রুৱ VkAllocationCallbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_অঙ্ক_DATA_POINTERS];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, পূর্ণাঙ্ক nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
পূর্ণাঙ্ক ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_অঙ্ক_DATA_POINTERS],
                            AVFrame *f, গণনা FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
পূর্ণাঙ্ক ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_অঙ্ক_DATA_POINTERS],
                                AVFrame *f,
                                ধ্রুৱ VkFormat fmts[AV_অঙ্ক_DATA_POINTERS]);

#define ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    কৰা {                                                                       \
        dst = (VkBufferMemoryBarrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2,                \
            .srcStageMask = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .srcAccessMask = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dstStageMask = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dstAccessMask = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,                    \
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,                    \
            .buffer = vkb->buf,                                                \
            .offset = offs,                                                    \
            .size = bsz                                                        \
        };                                                                     \
    } যেতিয়ালৈ(0)

শূন্য ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, পূর্ণাঙ্ক *nb_bar,
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
পূর্ণাঙ্ক ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, VkFormat format, পূর্ণাঙ্ক nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, শূন্য *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
শূন্য ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem);

পূর্ণাঙ্ক ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, শূন্য *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem);
পূর্ণাঙ্ক ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, size_t size,
                     শূন্য *pNext, শূন্য *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
পূর্ণাঙ্ক ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       পূর্ণাঙ্ক flush);

/**
 * Buffer management code.
 */
পূর্ণাঙ্ক ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      পূর্ণাঙ্ক nb_buffers, পূর্ণাঙ্ক invalidate);
পূর্ণাঙ্ক ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, পূর্ণাঙ্ক nb_buffers,
                        পূর্ণাঙ্ক flush);

স্থির অন্তঃস্থ পূর্ণাঙ্ক ff_vk_map_buffer(FFVulkanContext *s, FFVkBuffer *buf, uint8_t **mem,
                                   পূর্ণাঙ্ক invalidate)
{
    ঘূৰাই ff_vk_map_buffers(s, (FFVkBuffer *[]){ buf }, mem,
                             1, invalidate);
}

স্থির অন্তঃস্থ পূর্ণাঙ্ক ff_vk_unmap_buffer(FFVulkanContext *s, FFVkBuffer *buf, পূর্ণাঙ্ক flush)
{
    ঘূৰাই ff_vk_unmap_buffers(s, (FFVkBuffer *[]){ buf }, 1, flush);
}

শূন্য ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
পূর্ণাঙ্ক ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            শূন্য *create_pNext, size_t size,
                            VkMemoryPropertyFlagBits mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
পূর্ণাঙ্ক ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          ধ্রুৱ AVBufferRef *src_buf,
                          VkBufferUsageFlags usage);

/**
 * Create a sampler.
 */
পূর্ণাঙ্ক ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       পূর্ণাঙ্ক unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
পূর্ণাঙ্ক ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size);

/**
 * Link a shader into an executable.
 */
পূর্ণাঙ্ক ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ধ্রুৱ ৱর্ণ *spirv, size_t spirv_len,
                      ধ্রুৱ ৱর্ণ *entrypoint);

/**
 * Add/update push constants for execution.
 */
পূর্ণাঙ্ক ff_vk_shader_add_ঠেলো_const(FFVulkanShader *shd, পূর্ণাঙ্ক offset, পূর্ণাঙ্ক size,
                                VkShaderStageFlagBits stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
শূন্য ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ধ্রুৱ FFVulkanDescriptorSetBinding *desc, পূর্ণাঙ্ক nb,
                                     পূর্ণাঙ্ক singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
পূর্ণাঙ্ক ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
শূন্য ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ধ্রুৱ FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
শূন্য ff_vk_shader_update_ঠেলো_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    পূর্ণাঙ্ক offset, size_t size, শূন্য *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
পূর্ণাঙ্ক ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    পূর্ণাঙ্ক set, পূর্ণাঙ্ক bind, পূর্ণাঙ্ক elem,
                                    FFVkBuffer *buf, VkDeviceSize offset, VkDeviceSize len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
পূর্ণাঙ্ক ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, পূর্ণাঙ্ক set, পূর্ণাঙ্ক bind, পূর্ণাঙ্ক offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
শূন্য ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, পূর্ণাঙ্ক set, পূর্ণাঙ্ক binding,
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
