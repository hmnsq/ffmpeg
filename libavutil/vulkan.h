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
#define RET(x)                                                                 \
    ಕುರು {                                                                       \
        ಯದಿ ((err = (x)) < 0)                                                   \
            ಗಚ್ಛ fail;                                                         \
    } ಯಾವತ್ (0)

/* Convenience macros for specialization lists */
#define SPEC_LIST_MAX 256
#define SPEC_LIST_CREATE(name, max_length, max_size)           \
    av_assert1((max_length) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_size) + 3*ಪರಿಮಾಣ(uint32_t)];      \
    VkSpecializationMapEntry name##_entries[(max_length) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .pData = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#define SPEC_LIST_ADD(name, idx, val_bits, val)                \
ಕುರು {                                                           \
    unsigned ಪೂರ್ಣಾಙ್ಕ name##_cnt = name->map_Entry_ಎಣಿಕೆ;             \
    size_t name##_off = name->dataSize;                        \
    uint8_t *name##_dp = (uint8_t *)name->pData;               \
    ಶೂನ್ಯ *name##_ep = (ಶೂನ್ಯ *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_bits, name##_dp + name##_off, (val));            \
    VkSpecializationMapEntry name##_new_entry = {              \
        .constantID = (idx),                                   \
        .offset = name##_off,                                  \
        .size = val_bits >> 3,                                 \
    };                                                         \
    memcpy(name##_ep, &name##_new_entry,                       \
           ಪರಿಮಾಣ(VkSpecializationMapEntry));                  \
    name->dataSize = name##_off + (val_bits >> 3);             \
    name->map_Entry_ಎಣಿಕೆ = name##_cnt + 1;                      \
} ಯಾವತ್ (0)

#define DUP_SAMPLER(x) { x, x, x, x }

#define FF_VK_MAX_DESCRIPTOR_SETS 4
#define FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#define FF_VK_MAX_DESCRIPTOR_TYPES 16
#define FF_VK_MAX_ತಳ್ಳು_CONSTS 4
#define FF_VK_MAX_SHADERS 16

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanDescriptorSetBinding {
    ಧ್ರುವ ವರ್ಣ         *name;
    VkDescriptorType    type;
    ಧ್ರುವ ವರ್ಣ         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    ಧ್ರುವ ವರ್ಣ         *mem_quali;   /* readonly, writeonly, etc. */
    ಧ್ರುವ ವರ್ಣ         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkanDescriptorSetBinding;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVkBuffer {
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
#define FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_ಅಂಕೆ_DATA_POINTERS)

/* Default number of in-flight execution contexts per pool */
#define FF_VK_DEFAULT_EXEC_CONTEXTS 4

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVkExecContext {
    uint32_t idx;
    ಧ್ರುವ ಸಂರಚನಾ FFVkExecPool *parent;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    ಪೂರ್ಣಾಙ್ಕ had_submission;

    /* Queue for the execution context */
    VkQueue queue;
    ಪೂರ್ಣಾಙ್ಕ qf;
    ಪೂರ್ಣಾಙ್ಕ qi;

    /* Command buffer for the context */
    VkCommandBuffer buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_ಮೌಲ್ಯ;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t lock;

    /* Opaque data, untouched, free to use by users */
    ಶೂನ್ಯ *opaque;

    ಶೂನ್ಯ *query_data;
    ಪೂರ್ಣಾಙ್ಕ query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಙ್ಕ nb_buf_deps;

    /* AVRefStruct object dependencies */
    ಶೂನ್ಯ *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಙ್ಕ nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    ಪೂರ್ಣಾಙ್ಕ nb_obj_deps;

    /* Frame dependencies */
    AVFrame *frame_deps[FF_VK_EXEC_MAX_FRAME_DEPS];
    ಪೂರ್ಣಾಙ್ಕ nb_frame_deps;

    /* Software frame dependencies */
    AVFrame *sw_frame_deps[FF_VK_EXEC_MAX_SW_FRAME_DEPS];
    ಪೂರ್ಣಾಙ್ಕ nb_sw_frame_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಙ್ಕ sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಙ್ಕ sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    ಪೂರ್ಣಾಙ್ಕ sem_sig_val_dst_cnt;

    uint8_t frame_locked[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkAccessFlagBits access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanDescriptorSet {
    /* Descriptor buffer */
    VkDeviceSize layout_size;
    VkDeviceSize aligned_size; /* descriptorBufferOffsetAlignment */
    VkBufferUsageFlags usage;

    VkDescriptorSetLayoutBinding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    VkDeviceSize binding_offset[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    ಪೂರ್ಣಾಙ್ಕ nb_bindings;

    /* Descriptor set is shared between all submissions */
    ಪೂರ್ಣಾಙ್ಕ singular;
} FFVulkanDescriptorSet;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanShader {
    /* Name for id/debugging purposes */
    ಧ್ರುವ ವರ್ಣ *name;

    /* Whether shader is precompiled or not */
    ಪೂರ್ಣಾಙ್ಕ precompiled;
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
    Vk_ತಳ್ಳು_Constant_Range ತಳ್ಳು_consts[FF_VK_MAX_ತಳ್ಳು_CONSTS];
    ಪೂರ್ಣಾಙ್ಕ ತಳ್ಳು_consts_ಅಂಕೆ;

    /* Descriptor sets */
    FFVulkanDescriptorSet desc_set[FF_VK_MAX_DESCRIPTOR_SETS];
    ಪೂರ್ಣಾಙ್ಕ nb_descriptor_sets;

    /* Descriptors */
    VkDescriptorSetLayout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    ಪೂರ್ಣಾಙ್ಕ use_ತಳ್ಳು;
    VkDescriptorPoolSize desc_pool_size[FF_VK_MAX_DESCRIPTOR_TYPES];
    ಪೂರ್ಣಾಙ್ಕ nb_desc_pool_size;
} FFVulkanShader;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanDescriptorSetData {
    /* Descriptor buffer */
    FFVkBuffer buf;
    uint8_t *desc_mem;
} FFVulkanDescriptorSetData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanShaderData {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    ಪೂರ್ಣಾಙ್ಕ nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkanDescriptorSetData desc_set_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    VkDescriptorBufferBindingInfoEXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    VkDescriptorSet *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkanShaderData;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    VkCommandBuffer *cmd_bufs;
    ಪೂರ್ಣಾಙ್ಕ pool_size;

    VkQueryPool query_pool;
    ಶೂನ್ಯ *query_data;
    ಪೂರ್ಣಾಙ್ಕ query_results;
    ಪೂರ್ಣಾಙ್ಕ query_statuses;
    ಪೂರ್ಣಾಙ್ಕ query_64bit;
    ಪೂರ್ಣಾಙ್ಕ query_status_stride;
    ಪೂರ್ಣಾಙ್ಕ nb_queries;
    size_t qd_size;

    /* Registered shaders' data */
    FFVulkanShaderData reg_shd[FF_VK_MAX_SHADERS];
    ಪೂರ್ಣಾಙ್ಕ nb_reg_shd;
} FFVkExecPool;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVulkanContext {
    ಧ್ರುವ AVClass *class;
    ಶೂನ್ಯ *log_parent;

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
    Vk_Physical_Device_ತಳ್ಳು_Descriptor_Properties_KHR ತಳ್ಳು_desc_props;
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
    ಪೂರ್ಣಾಙ್ಕ tot_nb_qfs;
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

    AVBufferRef           *ಒಳಹರಿವು_frames_ref;
    AVBufferRef           *frames_ref;
    AVHWFramesContext     *frames;
    AVVulkanFramesContext *hwfc;

    uint32_t               qfs[64];
    ಪೂರ್ಣಾಙ್ಕ                    nb_qfs;

    /* Properties */
    ಪೂರ್ಣಾಙ್ಕ                 output_width;
    ಪೂರ್ಣಾಙ್ಕ                output_height;
    ಗಣನಾ AVPixelFormat output_format;
    ಗಣನಾ AVPixelFormat  ಒಳಹರಿವು_format;
} FFVulkanContext;

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_vk_ಎಣಿಕೆ_images(AVVkFrame *f)
{
    ಪೂರ್ಣಾಙ್ಕ cnt = 0;
    ಯಾವತ್ (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    ಪ್ರತ್ಯಾಗಮ cnt;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಧ್ರುವ ಶೂನ್ಯ *ff_vk_find_struct(ಧ್ರುವ ಶೂನ್ಯ *chain, VkStructureType stype)
{
    ಧ್ರುವ VkBaseInStructure *in = chain;
    ಯಾವತ್ (in) {
        ಯದಿ (in->sType == stype)
            ಪ್ರತ್ಯಾಗಮ in;

        in = in->pNext;
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ ff_vk_link_struct(ಶೂನ್ಯ *chain, ಧ್ರುವ ಶೂನ್ಯ *in)
{
    VkBaseOutStructure *out = chain;
    ಯಾವತ್ (out->pNext)
        out = out->pNext;

    out->pNext = (ಶೂನ್ಯ *)in;
}

#define FF_VK_STRUCT_EXT(CTX, BASE, STRUCT_P, EXT_FLAG, TYPE) \
    ಕುರು {                                                      \
        ಯದಿ ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(BASE, STRUCT_P);                \
        }                                                     \
    } ಯಾವತ್ (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
ಬಾಹ್ಯ ಧ್ರುವ VkComponentMapping ff_comp_identity_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_init(FFVulkanContext *s, ಶೂನ್ಯ *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref);

/**
 * Converts Vulkan return values to strings
 */
ಧ್ರುವ ವರ್ಣ *ff_vk_ret2str(VkResult res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_to_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_to_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_mt_is_np_rgb(ಗಣನಾ AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
ಶೂನ್ಯ ff_vk_set_perm(ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ lut[4], ಪೂರ್ಣಾಙ್ಕ inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, ಪೂರ್ಣಾಙ್ಕ p);

/**
 * Returns the format to use for images in shaders.
 */
ಗಣನಾ FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
ಧ್ರುವ ವರ್ಣ *ff_vk_shader_rep_fmt(ಗಣನಾ AVPixelFormat pix_fmt,
                                 ಗಣನಾ FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, ಗಣನಾ FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_load_props(FFVulkanContext *s);

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
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, ಪೂರ್ಣಾಙ್ಕ nb_contexts,
                         ಪೂರ್ಣಾಙ್ಕ nb_queries, VkQueryType query_type, ಪೂರ್ಣಾಙ್ಕ query_64bit,
                         ಧ್ರುವ ಶೂನ್ಯ *query_create_pnext);
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
VkResult ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              ಶೂನ್ಯ **data, VkQueryResultFlagBits flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e);
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
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
ಶೂನ್ಯ ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  ಶೂನ್ಯ *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
ಶೂನ್ಯ ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   ಶೂನ್ಯ *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
ಶೂನ್ಯ ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

ಶೂನ್ಯ ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
ಶೂನ್ಯ ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
ಶೂನ್ಯ ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, ಪೂರ್ಣಾಙ್ಕ nb,
                                 VkPipelineStageFlagBits2 stage,
                                 ಪೂರ್ಣಾಙ್ಕ wait); /* Ownership transferred if !wait */
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
ಶೂನ್ಯ ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar);
ಪೂರ್ಣಾಙ್ಕ ff_vk_exec_mirror_sem_ಮೌಲ್ಯ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
ಶೂನ್ಯ ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, ಪೂರ್ಣಾಙ್ಕ plane, ಗಣನಾ FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFVkImageViews {
    ಪೂರ್ಣಾಙ್ಕ nb_views;

    VkDevice dev;
    ಧ್ರುವ VkAllocationCallbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_ಅಂಕೆ_DATA_POINTERS];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, ಪೂರ್ಣಾಙ್ಕ nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_ಅಂಕೆ_DATA_POINTERS],
                            AVFrame *f, ಗಣನಾ FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_ಅಂಕೆ_DATA_POINTERS],
                                AVFrame *f,
                                ಧ್ರುವ VkFormat fmts[AV_ಅಂಕೆ_DATA_POINTERS]);

#define ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    ಕುರು {                                                                       \
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
    } ಯಾವತ್(0)

ಶೂನ್ಯ ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, ಪೂರ್ಣಾಙ್ಕ *nb_bar,
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
ಪೂರ್ಣಾಙ್ಕ ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, VkFormat format, ಪೂರ್ಣಾಙ್ಕ nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, ಶೂನ್ಯ *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
ಶೂನ್ಯ ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem);

ಪೂರ್ಣಾಙ್ಕ ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, ಶೂನ್ಯ *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem);
ಪೂರ್ಣಾಙ್ಕ ff_vk_create_buf(FFVulkanContext *s, FFVkBuffer *buf, size_t size,
                     ಶೂನ್ಯ *pNext, ಶೂನ್ಯ *alloc_pNext,
                     VkBufferUsageFlags usage, VkMemoryPropertyFlagBits flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_flush_buffer(FFVulkanContext *s, FFVkBuffer *buf,
                       VkDeviceSize offset, VkDeviceSize mem_size,
                       ಪೂರ್ಣಾಙ್ಕ flush);

/**
 * Buffer management code.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_map_buffers(FFVulkanContext *s, FFVkBuffer **buf, uint8_t *mem[],
                      ಪೂರ್ಣಾಙ್ಕ nb_buffers, ಪೂರ್ಣಾಙ್ಕ invalidate);
ಪೂರ್ಣಾಙ್ಕ ff_vk_unmap_buffers(FFVulkanContext *s, FFVkBuffer **buf, ಪೂರ್ಣಾಙ್ಕ nb_buffers,
                        ಪೂರ್ಣಾಙ್ಕ flush);

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_vk_map_buffer(FFVulkanContext *s, FFVkBuffer *buf, uint8_t **mem,
                                   ಪೂರ್ಣಾಙ್ಕ invalidate)
{
    ಪ್ರತ್ಯಾಗಮ ff_vk_map_buffers(s, (FFVkBuffer *[]){ buf }, mem,
                             1, invalidate);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ ff_vk_unmap_buffer(FFVulkanContext *s, FFVkBuffer *buf, ಪೂರ್ಣಾಙ್ಕ flush)
{
    ಪ್ರತ್ಯಾಗಮ ff_vk_unmap_buffers(s, (FFVkBuffer *[]){ buf }, 1, flush);
}

ಶೂನ್ಯ ff_vk_free_buf(FFVulkanContext *s, FFVkBuffer *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
ಪೂರ್ಣಾಙ್ಕ ff_vk_get_pooled_buffer(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVkBuffer **buf, VkBufferUsageFlags usage,
                            ಶೂನ್ಯ *create_pNext, size_t size,
                            VkMemoryPropertyFlagBits mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
ಪೂರ್ಣಾಙ್ಕ ff_vk_host_map_buffer(FFVulkanContext *s, FFVkBuffer **dst,
                          uint8_t *src_data, VkDeviceSize size,
                          ಧ್ರುವ AVBufferRef *src_buf,
                          VkBufferUsageFlags usage);

/**
 * Create a sampler.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       ಪೂರ್ಣಾಙ್ಕ unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_size[3], uint32_t required_subgroup_size);

/**
 * Link a shader into an executable.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ಧ್ರುವ ವರ್ಣ *spirv, size_t spirv_len,
                      ಧ್ರುವ ವರ್ಣ *entrypoint);

/**
 * Add/update push constants for execution.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_add_ತಳ್ಳು_const(FFVulkanShader *shd, ಪೂರ್ಣಾಙ್ಕ offset, ಪೂರ್ಣಾಙ್ಕ size,
                                VkShaderStageFlagBits stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
ಶೂನ್ಯ ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     ಧ್ರುವ FFVulkanDescriptorSetBinding *desc, ಪೂರ್ಣಾಙ್ಕ nb,
                                     ಪೂರ್ಣಾಙ್ಕ singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
ಶೂನ್ಯ ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            ಧ್ರುವ FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
ಶೂನ್ಯ ff_vk_shader_update_ತಳ್ಳು_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    ಪೂರ್ಣಾಙ್ಕ offset, size_t size, ಶೂನ್ಯ *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_update_desc_buffer(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ bind, ಪೂರ್ಣಾಙ್ಕ elem,
                                    FFVkBuffer *buf, VkDeviceSize offset, VkDeviceSize len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
ಪೂರ್ಣಾಙ್ಕ ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ bind, ಪೂರ್ಣಾಙ್ಕ offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
ಶೂನ್ಯ ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, ಪೂರ್ಣಾಙ್ಕ set, ಪೂರ್ಣಾಙ್ಕ binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
ಶೂನ್ಯ ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
ಶೂನ್ಯ ff_vk_uninit(FFVulkanContext *s);

#endif /* AVUTIL_VULKAN_H */
