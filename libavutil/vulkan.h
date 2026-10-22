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

#अन्तर्भाव <stdatomic.h>

#अन्तर्भाव "refstruct.h"

#अन्तर्भाव "thread.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "vulkan_functions.h"
#अन्तर्भाव "hwcontext_vulkan.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#define RET(x)                                                                 \
    करेहि {                                                                       \
        जइ ((err = (x)) < 0)                                                   \
            गच्छ fail;                                                         \
    } जाव (0)

/* Convenience macros for specialization lists */
#define SPEC_LIST_MAX 256
#define SPEC_LIST_CREATE(name, max_length, max_size)           \
    av_assert1((max_length) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_size) + 3*परिमाण(uint32_t)];      \
    VkSpecializationMapEntry name##_entries[(max_length) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .pData = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#define SPEC_LIST_ADD(name, idx, val_bits, val)                \
करेहि {                                                           \
    unsigned पूर्णाङ्क name##_cnt = name->map_Entry_गणनम्;             \
    size_t name##_off = name->dataSize;                        \
    uint8_t *name##_dp = (uint8_t *)name->pData;               \
    शून्य *name##_ep = (शून्य *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_bits, name##_dp + name##_off, (val));            \
    VkSpecializationMapEntry name##_new_entry = {              \
        .constantID = (idx),                                   \
        .offset = name##_off,                                  \
        .size = val_bits >> 3,                                 \
    };                                                         \
    memcpy(name##_ep, &name##_new_entry,                       \
           परिमाण(VkSpecializationMapEntry));                  \
    name->dataSize = name##_off + (val_bits >> 3);             \
    name->map_Entry_गणनम् = name##_cnt + 1;                      \
} जाव (0)

#define DUP_SAMPLER(x) { x, x, x, x }

#define FF_VK_MAX_DESCRIPTOR_SETS 4
#define FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#define FF_VK_MAX_DESCRIPTOR_TYPES 16
#define FF_VK_MAX_प्रक्षिप_CONSTS 4
#define FF_VK_MAX_SHADERS 16

प्रकारनिर्देश संरचना FFVulkanDescriptorSetBinding {
    ध्रुव वर्ण         *name;
    VkDescriptorType    type;
    ध्रुव वर्ण         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ध्रुव वर्ण         *mem_quali;   /* readonly, writeonly, etc. */
    ध्रुव वर्ण         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkanDescriptorSetBinding;

प्रकारनिर्देश संरचना FFVkBuffer {
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
#define FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_अङ्कः_DATA_POINTERS)

/* Default number of in-flight execution contexts per pool */
#define FF_VK_DEFAULT_EXEC_CONTEXTS 4

प्रकारनिर्देश संरचना FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

प्रकारनिर्देश संरचना FFVkExecContext {
    uint32_t idx;
    ध्रुव संरचना FFVkExecPool *parent;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    पूर्णाङ्क had_submission;

    /* Queue for the execution context */
    VkQueue queue;
    पूर्णाङ्क qf;
    पूर्णाङ्क qi;

    /* Command buffer for the context */
    VkCommandBuffer buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_मानम्;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t lock;

    /* Opaque data, untouched, free to use by users */
    शून्य *opaque;

    शून्य *query_data;
    पूर्णाङ्क query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णाङ्क nb_buf_deps;

    /* AVRefStruct object dependencies */
    शून्य *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णाङ्क nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णाङ्क nb_obj_deps;

    /* Frame dependencies */
    AVFrame *frame_deps[FF_VK_EXEC_MAX_FRAME_DEPS];
    पूर्णाङ्क nb_frame_deps;

    /* Software frame dependencies */
    AVFrame *sw_frame_deps[FF_VK_EXEC_MAX_SW_FRAME_DEPS];
    पूर्णाङ्क nb_sw_frame_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णाङ्क sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णाङ्क sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णाङ्क sem_sig_val_dst_cnt;

    uint8_t frame_locked[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkAccessFlagBits access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

प्रकारनिर्देश संरचना FFVulkanDescriptorSet {
    /* Descriptor buffer */
    VkDeviceSize layout_size;
    VkDeviceSize aligned_size; /* descriptorBufferOffsetAlignment */
    VkBufferUsageFlags usage;

    VkDescriptorSetLayoutBinding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    VkDeviceSize binding_offset[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    पूर्णाङ्क nb_bindings;

    /* Descriptor set is shared between all submissions */
    पूर्णाङ्क singular;
} FFVulkanDescriptorSet;

प्रकारनिर्देश संरचना FFVulkanShader {
    /* Name for id/debugging purposes */
    ध्रुव वर्ण *name;

    /* Whether shader is precompiled or not */
    पूर्णाङ्क precompiled;
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
    Vk_प्रक्षिप_Constant_Range प्रक्षिप_consts[FF_VK_MAX_प्रक्षिप_CONSTS];
    पूर्णाङ्क प्रक्षिप_consts_अङ्कः;

    /* Descriptor sets */
    FFVulkanDescriptorSet desc_set[FF_VK_MAX_DESCRIPTOR_SETS];
    पूर्णाङ्क nb_descriptor_sets;

    /* Descriptors */
    VkDescriptorSetLayout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    पूर्णाङ्क use_प्रक्षिप;
    VkDescriptorPoolSize desc_pool_size[FF_VK_MAX_DESCRIPTOR_TYPES];
    पूर्णाङ्क nb_desc_pool_size;
} FFVulkanShader;

प्रकारनिर्देश संरचना FFVulkanDescriptorSetData {
    /* Descriptor buffer */
    FFVkBuffer buf;
    uint8_t *desc_mem;
} FFVulkanDescriptorSetData;

प्रकारनिर्देश संरचना FFVulkanShaderData {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    पूर्णाङ्क nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkanDescriptorSetData desc_set_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    VkDescriptorBufferBindingInfoEXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    VkDescriptorSet *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkanShaderData;

प्रकारनिर्देश संरचना FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    VkCommandBuffer *cmd_bufs;
    पूर्णाङ्क pool_size;

    VkQueryPool query_pool;
    शून्य *query_data;
    पूर्णाङ्क query_results;
    पूर्णाङ्क query_statuses;
    पूर्णाङ्क query_64bit;
    पूर्णाङ्क query_status_stride;
    पूर्णाङ्क nb_queries;
    size_t qd_size;

    /* Registered shaders' data */
    FFVulkanShaderData reg_shd[FF_VK_MAX_SHADERS];
    पूर्णाङ्क nb_reg_shd;
} FFVkExecPool;

प्रकारनिर्देश संरचना FFVulkanContext {
    ध्रुव AVClass *class;
    शून्य *log_parent;

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
    Vk_Physical_Device_प्रक्षिप_Descriptor_Properties_KHR प्रक्षिप_desc_props;
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
    पूर्णाङ्क tot_nb_qfs;
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

    AVBufferRef           *निवेशः_frames_ref;
    AVBufferRef           *frames_ref;
    AVHWFramesContext     *frames;
    AVVulkanFramesContext *hwfc;

    uint32_t               qfs[64];
    पूर्णाङ्क                    nb_qfs;

    /* Properties */
    पूर्णाङ्क                 output_width;
    पूर्णाङ्क                output_height;
    गणना AVPixelFormat output_format;
    गणना AVPixelFormat  निवेशः_format;
} FFVulkanContext;

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_गणनम्_images(AVVkFrame *f)
{
    पूर्णाङ्क cnt = 0;
    जाव (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    प्रत्यागम cnt;
}

स्थिर अन्तःस्थ ध्रुव शून्य *ff_vk_find_struct(ध्रुव शून्य *chain, VkStructureType stype)
{
    ध्रुव VkBaseInStructure *in = chain;
    जाव (in) {
        जइ (in->sType == stype)
            प्रत्यागम in;

        in = in->pNext;
    }

    प्रत्यागम रिक्त;
}

स्थिर अन्तःस्थ शून्य ff_vk_link_struct(शून्य *chain, ध्रुव शून्य *in)
{
    VkBaseOutStructure *out = chain;
    जाव (out->pNext)
        out = out->pNext;

    out->pNext = (शून्य *)in;
}

#define FF_VK_STRUCT_EXT(CTX, BASE, STRUCT_P, EXT_FLAG, TYPE) \
    करेहि {                                                      \
        जइ ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(BASE, STRUCT_P);                \
        }                                                     \
    } जाव (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
बाह्य ध्रुव VkComponentMapping ff_comp_identity_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
पूर्णाङ्क ff_vk_init(FFVulkanContext *s, शून्य *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref);

/**
 * Converts Vulkan return values to strings
 */
ध्रुव वर्ण *ff_vk_ret2str(VkResult res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_to_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_to_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
पूर्णाङ्क ff_vk_mt_is_np_rgb(गणना AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
शून्य ff_vk_set_perm(गणना AVPixelFormat pix_fmt, पूर्णाङ्क lut[4], पूर्णाङ्क inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, पूर्णाङ्क p);

/**
 * Returns the format to use for images in shaders.
 */
गणना FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ध्रुव वर्ण *ff_vk_shader_rep_fmt(गणना AVPixelFormat pix_fmt,
                                 गणना FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, गणना FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
पूर्णाङ्क ff_vk_load_props(FFVulkanContext *s);

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
पूर्णाङ्क ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, पूर्णाङ्क nb_contexts,
                         पूर्णाङ्क nb_queries, VkQueryType query_type, पूर्णाङ्क query_64bit,
                         ध्रुव शून्य *query_create_pnext);
शून्य ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

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
                              शून्य **data, VkQueryResultFlagBits flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
पूर्णाङ्क ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e);
पूर्णाङ्क ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
शून्य ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
शून्य ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  शून्य *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
शून्य ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   शून्य *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
शून्य ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

शून्य ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
शून्य ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
शून्य ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णाङ्क nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णाङ्क wait); /* Ownership transferred if !wait */
पूर्णाङ्क ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
पूर्णाङ्क ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
शून्य ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar);
पूर्णाङ्क ff_vk_exec_mirror_sem_मानम्(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
शून्य ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
पूर्णाङ्क ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, पूर्णाङ्क plane, गणना FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
प्रकारनिर्देश संरचना FFVkImageViews {
    पूर्णाङ्क nb_views;

    VkDevice dev;
    ध्रुव VkAllocationCallbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_अङ्कः_DATA_POINTERS];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, पूर्णाङ्क nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
पूर्णाङ्क ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_अङ्कः_DATA_POINTERS],
                            AVFrame *f, गणना FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
पूर्णाङ्क ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अङ्कः_DATA_POINTERS],
                                AVFrame *f,
                                ध्रुव VkFormat fmts[AV_अङ्कः_DATA_POINTERS]);

#define ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    करेहि {                                                                       \
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
    } जाव(0)

शून्य ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, पूर्णाङ्क *nb_bar,
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
पूर्णाङ्क ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       पूर्णाङ्क width, पूर्णाङ्क height, VkFormat format, पूर्णाङ्क nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, शून्य *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
शून्य ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem);

पूर्णाङ्क ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, शून्य *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem);
पूर्णाङ्क ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, size_t size,
                     शून्य *pNext, शून्य *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
पूर्णाङ्क ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       पूर्णाङ्क flush);

/**
 * Buffer management code.
 */
पूर्णाङ्क ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      पूर्णाङ्क nb_buffers, पूर्णाङ्क invalidate);
पूर्णाङ्क ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, पूर्णाङ्क nb_buffers,
                        पूर्णाङ्क flush);

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_map_buffer(FFVulkanContext *s, FFVkBuffer *buf, uint8_t **mem,
                                   पूर्णाङ्क invalidate)
{
    प्रत्यागम ff_vk_map_buffers(s, (FFVkBuffer *[]){ buf }, mem,
                             1, invalidate);
}

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_unmap_buffer(FFVulkanContext *s, FFVkBuffer *buf, पूर्णाङ्क flush)
{
    प्रत्यागम ff_vk_unmap_buffers(s, (FFVkBuffer *[]){ buf }, 1, flush);
}

शून्य ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
पूर्णाङ्क ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            शून्य *create_pNext, size_t size,
                            VkMemoryPropertyFlagBits mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
पूर्णाङ्क ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          ध्रुव AVBufferRef *src_buf,
                          VkBufferUsageFlags usage);

/**
 * Create a sampler.
 */
पूर्णाङ्क ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       पूर्णाङ्क unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
पूर्णाङ्क ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size);

/**
 * Link a shader into an executable.
 */
पूर्णाङ्क ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ध्रुव वर्ण *spirv, size_t spirv_len,
                      ध्रुव वर्ण *entrypoint);

/**
 * Add/update push constants for execution.
 */
पूर्णाङ्क ff_vk_shader_add_प्रक्षिप_const(FFVulkanShader *shd, पूर्णाङ्क offset, पूर्णाङ्क size,
                                VkShaderStageFlagBits stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
शून्य ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ध्रुव FFVulkanDescriptorSetBinding *desc, पूर्णाङ्क nb,
                                     पूर्णाङ्क singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
पूर्णाङ्क ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
शून्य ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ध्रुव FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
शून्य ff_vk_shader_update_प्रक्षिप_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    पूर्णाङ्क offset, size_t size, शून्य *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
पूर्णाङ्क ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णाङ्क set, पूर्णाङ्क bind, पूर्णाङ्क elem,
                                    FFVkBuffer *buf, VkDeviceSize offset, VkDeviceSize len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
पूर्णाङ्क ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णाङ्क set, पूर्णाङ्क bind, पूर्णाङ्क offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
शून्य ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णाङ्क set, पूर्णाङ्क binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
शून्य ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
शून्य ff_vk_uninit(FFVulkanContext *s);

#endif /* AVUTIL_VULKAN_H */
