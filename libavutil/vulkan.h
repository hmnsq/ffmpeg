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

#अगर_अघोषित AVUTIL_VULKAN_H
#घोषणा AVUTIL_VULKAN_H

#घोषणा VK_NO_PROTOTYPES

#समावेश <stdatomic.h>

#समावेश "refstruct.h"

#समावेश "thread.h"
#समावेश "pixdesc.h"
#समावेश "hwcontext.h"
#समावेश "vulkan_functions.h"
#समावेश "hwcontext_vulkan.h"
#समावेश "avassert.h"
#समावेश "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#घोषणा RET(x)                                                                 \
    करो {                                                                       \
        अगर ((err = (x)) < 0)                                                   \
            जाओ fail;                                                         \
    } जबतक (0)

/* Convenience macros for specialization lists */
#घोषणा SPEC_LIST_MAX 256
#घोषणा SPEC_LIST_CREATE(name, max_लंबाई, max_आकार)           \
    av_assert1((max_लंबाई) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_आकार) + 3*माप(uint32_t)];      \
    VkSpecializationMapEntry name##_entries[(max_लंबाई) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_तथ्य = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#घोषणा SPEC_LIST_ADD(name, idx, val_bits, val)                \
करो {                                                           \
    अचिन्हित पूर्णांक name##_cnt = name->map_Entry_गिनती;             \
    माप_प्रकार name##_off = name->तथ्य_आकार_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_तथ्य;               \
    व्योम *name##_ep = (व्योम *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_bits, name##_dp + name##_off, (val));            \
    VkSpecializationMapEntry name##_new_entry = {              \
        .constantID = (idx),                                   \
        .offset = name##_off,                                  \
        .आकार = val_bits >> 3,                                 \
    };                                                         \
    स_नकल(name##_ep, &name##_new_entry,                       \
           माप(VkSpecializationMapEntry));                  \
    name->तथ्य_आकार_2 = name##_off + (val_bits >> 3);             \
    name->map_Entry_गिनती = name##_cnt + 1;                      \
} जबतक (0)

#घोषणा DUP_SAMPLER(x) { x, x, x, x }

#घोषणा FF_VK_MAX_DESCRIPTOR_SETS 4
#घोषणा FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#घोषणा FF_VK_MAX_DESCRIPTOR_TYPES 16
#घोषणा FF_VK_MAX_धकेलो_CONSTS 4
#घोषणा FF_VK_MAX_SHADERS 16

प्रकार काष्ठा FFVulkanDescriptorSetBinding {
    स्थिर अक्षर         *name;
    VkDescriptorType    type;
    स्थिर अक्षर         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    स्थिर अक्षर         *mem_quali;   /* readonly, writeonly, etc. */
    स्थिर अक्षर         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkanDescriptorSetBinding;

प्रकार काष्ठा FFVk_बफर {
    Vk_बफर buf;
    VkDeviceMemory mem;
    VkMemoryPropertyFlagBits flags;
    माप_प्रकार आकार;
    VkDeviceAddress address;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    माप_प्रकार virtual_offset;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_बफर;

/* Fixed dependency limits per exec context (with room to spare) */
#घोषणा FF_VK_EXEC_MAX_FRAME_DEPS 64
#घोषणा FF_VK_EXEC_MAX_BUF_DEPS 256
#घोषणा FF_VK_EXEC_MAX_SW_FRAME_DEPS 16
#घोषणा FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_अंक_तथ्य_POINTERS)

/* Default number of in-flight execution contexts per pool */
#घोषणा FF_VK_DEFAULT_EXEC_CONTEXTS 4

प्रकार काष्ठा FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

प्रकार काष्ठा FFVkExecContext {
    uint32_t idx;
    स्थिर काष्ठा FFVkExecPool *parent;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    पूर्णांक had_submission;

    /* Queue for the execution context */
    VkQueue queue;
    पूर्णांक qf;
    पूर्णांक qi;

    /* Command buffer for the context */
    Vk_Command_बफर buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_मूल्य;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t lock;

    /* Opaque data, untouched, free to use by users */
    व्योम *opaque;

    व्योम *query_तथ्य;
    पूर्णांक query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णांक nb_buf_deps;

    /* AVRefStruct object dependencies */
    व्योम *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णांक nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    पूर्णांक nb_obj_deps;

    /* Frame dependencies */
    AVFrame *frame_deps[FF_VK_EXEC_MAX_FRAME_DEPS];
    पूर्णांक nb_frame_deps;

    /* Software frame dependencies */
    AVFrame *sw_frame_deps[FF_VK_EXEC_MAX_SW_FRAME_DEPS];
    पूर्णांक nb_sw_frame_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णांक sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णांक sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    पूर्णांक sem_sig_val_dst_cnt;

    uint8_t frame_locked[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkAccessFlagBits access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

प्रकार काष्ठा FFVulkanDescriptorSet {
    /* Descriptor buffer */
    Vk_Device_आकार layout_आकार;
    Vk_Device_आकार aligned_आकार; /* descriptorBufferOffsetAlignment */
    Vk_बफर_Usage_Flags usage;

    VkDescriptorSetLayoutBinding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_आकार binding_offset[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    पूर्णांक nb_bindings;

    /* Descriptor set is shared between all submissions */
    पूर्णांक singular;
} FFVulkanDescriptorSet;

प्रकार काष्ठा FFVulkanShader {
    /* Name for id/debugging purposes */
    स्थिर अक्षर *name;

    /* Whether shader is precompiled or not */
    पूर्णांक precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_आकार[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    VkPipelineBindPoint bind_point;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_आकार_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_धकेलो_Constant_Range धकेलो_consts[FF_VK_MAX_धकेलो_CONSTS];
    पूर्णांक धकेलो_consts_अंक;

    /* Descriptor sets */
    FFVulkanDescriptorSet desc_set[FF_VK_MAX_DESCRIPTOR_SETS];
    पूर्णांक nb_descriptor_sets;

    /* Descriptors */
    VkDescriptorSetLayout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    पूर्णांक use_धकेलो;
    Vk_Descriptor_Pool_आकार desc_pool_आकार[FF_VK_MAX_DESCRIPTOR_TYPES];
    पूर्णांक nb_desc_pool_आकार;
} FFVulkanShader;

प्रकार काष्ठा FFVulkan_Descriptor_Set_तथ्य {
    /* Descriptor buffer */
    FFVk_बफर buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_Set_तथ्य;

प्रकार काष्ठा FFVulkan_Shader_तथ्य {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    पूर्णांक nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_Set_तथ्य desc_set_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_बफर_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    VkDescriptorSet *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_तथ्य;

प्रकार काष्ठा FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_बफर *cmd_bufs;
    पूर्णांक pool_आकार;

    VkQueryPool query_pool;
    व्योम *query_तथ्य;
    पूर्णांक query_results;
    पूर्णांक query_statuses;
    पूर्णांक query_64bit;
    पूर्णांक query_status_stride;
    पूर्णांक nb_queries;
    माप_प्रकार qd_आकार;

    /* Registered shaders' data */
    FFVulkan_Shader_तथ्य reg_shd[FF_VK_MAX_SHADERS];
    पूर्णांक nb_reg_shd;
} FFVkExecPool;

प्रकार काष्ठा FFVulkanContext {
    स्थिर AVClass *class;
    व्योम *log_parent;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    VkPhysicalDeviceMemoryProperties mprops;
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT hprops;
    Vk_Physical_Device_Descriptor_बफर_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_आकार_Control_Properties subgroup_props;
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR coop_matrix_props;
    Vk_Physical_Device_धकेलो_Descriptor_Properties_KHR धकेलो_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#अगर_घोषित VK_EXT_shader_long_vector
    VkPhysicalDeviceShaderLongVectorPropertiesEXT long_vector_props;
#पूर्ण_अगर
    Vk_Queue_Family_Query_परिणाम_Status_Properties_KHR *query_props;
    VkQueueFamilyVideoPropertiesKHR *video_props;
#अगर_घोषित VK_KHR_maintenance9
    VkQueueFamilyOwnershipTransferPropertiesKHR *ownership_props;
#पूर्ण_अगर
    VkQueueFamilyProperties2 *qf_props;
    पूर्णांक tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    VkCooperativeMatrixPropertiesKHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#अगर_घोषित VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#पूर्ण_अगर
#अगर_घोषित VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#पूर्ण_अगर
    VkPhysicalDeviceFeatures2 feats;

    VkMemoryPropertyFlagBits host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *निवेश_frames_ref;
    AVBufferRef           *frames_ref;
    AVHWFramesContext     *frames;
    AVVulkanFramesContext *hwfc;

    uint32_t               qfs[64];
    पूर्णांक                    nb_qfs;

    /* Properties */
    पूर्णांक                 output_width;
    पूर्णांक                output_height;
    क्रमागत AVPixelFormat output_format;
    क्रमागत AVPixelFormat  निवेश_format;
} FFVulkanContext;

अटल अंतरभूत पूर्णांक ff_vk_गिनती_images(AVVkFrame *f)
{
    पूर्णांक cnt = 0;
    जबतक (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    वापस cnt;
}

अटल अंतरभूत स्थिर व्योम *ff_vk_find_struct(स्थिर व्योम *chain, VkStructureType stype)
{
    स्थिर VkBaseInStructure *in = chain;
    जबतक (in) {
        अगर (in->sType == stype)
            वापस in;

        in = in->p_अग्र;
    }

    वापस शून्य;
}

अटल अंतरभूत व्योम ff_vk_link_struct(व्योम *chain, स्थिर व्योम *in)
{
    VkBaseOutStructure *out = chain;
    जबतक (out->p_अग्र)
        out = out->p_अग्र;

    out->p_अग्र = (व्योम *)in;
}

#घोषणा FF_VK_STRUCT_EXT(CTX, BASE, STRUCT_P, EXT_FLAG, TYPE) \
    करो {                                                      \
        अगर ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(BASE, STRUCT_P);                \
        }                                                     \
    } जबतक (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
बाह्य स्थिर VkComponentMapping ff_comp_identity_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
पूर्णांक ff_vk_init(FFVulkanContext *s, व्योम *log_parent,
               AVBufferRef *device_ref, AVBufferRef *frames_ref);

/**
 * Converts Vulkan return values to strings
 */
स्थिर अक्षर *ff_vk_ret2str(Vk_परिणाम res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_to_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_to_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
पूर्णांक ff_vk_mt_is_np_rgb(क्रमागत AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
व्योम ff_vk_set_perm(क्रमागत AVPixelFormat pix_fmt, पूर्णांक lut[4], पूर्णांक inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, पूर्णांक p);

/**
 * Returns the format to use for images in shaders.
 */
क्रमागत FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
स्थिर अक्षर *ff_vk_shader_rep_fmt(क्रमागत AVPixelFormat pix_fmt,
                                 क्रमागत FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_to_rep(VkFormat fmt, क्रमागत FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
पूर्णांक ff_vk_load_props(FFVulkanContext *s);

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
पूर्णांक ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkanDeviceQueueFamily *qf,
                         FFVkExecPool *pool, पूर्णांक nb_contexts,
                         पूर्णांक nb_queries, VkQueryType query_type, पूर्णांक query_64bit,
                         स्थिर व्योम *query_create_pnext);
व्योम ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_परिणाम ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              व्योम **तथ्य, Vk_Query_परिणाम_Flag_Bits flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
पूर्णांक ff_vk_exec_start(FFVulkanContext *s, FFVkExecContext *e);
पूर्णांक ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
व्योम ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
व्योम ff_vk_exec_add_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  व्योम *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
व्योम ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   व्योम *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
व्योम ff_vk_exec_add_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

व्योम ff_vk_exec_add_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
व्योम ff_vk_exec_add_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
व्योम ff_vk_exec_add_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णांक nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णांक रुको); /* Ownership transferred if !wait */
पूर्णांक ff_vk_exec_add_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
पूर्णांक ff_vk_exec_add_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
व्योम ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkImageMemoryBarrier2 *bar, uint32_t *nb_img_bar);
पूर्णांक ff_vk_exec_mirror_sem_मूल्य(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
व्योम ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
पूर्णांक ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, पूर्णांक plane, क्रमागत FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
प्रकार काष्ठा FFVkImageViews {
    पूर्णांक nb_views;

    VkDevice dev;
    स्थिर VkAllocationCallbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_अंक_तथ्य_POINTERS];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, पूर्णांक nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
पूर्णांक ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_अंक_तथ्य_POINTERS],
                            AVFrame *f, क्रमागत FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
पूर्णांक ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अंक_तथ्य_POINTERS],
                                AVFrame *f,
                                स्थिर VkFormat fmts[AV_अंक_तथ्य_POINTERS]);

#घोषणा ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    करो {                                                                       \
        dst = (Vk_बफर_Memory_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_बफर_MEMORY_BARRIER_2,                \
            .srcStageMask = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .srcAccessMask = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dstStageMask = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dstAccessMask = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_Queue_Family_सूचकांक = VK_QUEUE_FAMILY_IGNORED,                    \
            .dst_Queue_Family_सूचकांक = VK_QUEUE_FAMILY_IGNORED,                    \
            .बफर = vkb->buf,                                                \
            .offset = offs,                                                    \
            .आकार = bsz                                                        \
        };                                                                     \
    } जबतक(0)

व्योम ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, VkImageMemoryBarrier2 *bar, पूर्णांक *nb_bar,
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
पूर्णांक ff_vk_image_create(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem,
                       पूर्णांक width, पूर्णांक height, VkFormat format, पूर्णांक nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, व्योम *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
व्योम ff_vk_image_free(FFVulkanContext *s, VkImage *img, VkDeviceMemory *mem);

पूर्णांक ff_vk_alloc_mem(FFVulkanContext *s, VkMemoryRequirements *req,
                    VkMemoryPropertyFlagBits req_flags, व्योम *alloc_extension,
                    VkMemoryPropertyFlagBits *mem_flags, VkDeviceMemory *mem);
पूर्णांक ff_vk_create_buf(FFVulkanContext *s, FFVk_बफर *buf, माप_प्रकार आकार,
                     व्योम *p_अग्र, व्योम *alloc_p_अग्र,
                     Vk_बफर_Usage_Flags usage, VkMemoryPropertyFlagBits flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
पूर्णांक ff_vk_flush_बफर(FFVulkanContext *s, FFVk_बफर *buf,
                       Vk_Device_आकार offset, Vk_Device_आकार mem_आकार,
                       पूर्णांक flush);

/**
 * Buffer management code.
 */
पूर्णांक ff_vk_map_buffers(FFVulkanContext *s, FFVk_बफर **buf, uint8_t *mem[],
                      पूर्णांक nb_buffers, पूर्णांक invalidate);
पूर्णांक ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_बफर **buf, पूर्णांक nb_buffers,
                        पूर्णांक flush);

अटल अंतरभूत पूर्णांक ff_vk_map_बफर(FFVulkanContext *s, FFVk_बफर *buf, uint8_t **mem,
                                   पूर्णांक invalidate)
{
    वापस ff_vk_map_buffers(s, (FFVk_बफर *[]){ buf }, mem,
                             1, invalidate);
}

अटल अंतरभूत पूर्णांक ff_vk_unmap_बफर(FFVulkanContext *s, FFVk_बफर *buf, पूर्णांक flush)
{
    वापस ff_vk_unmap_buffers(s, (FFVk_बफर *[]){ buf }, 1, flush);
}

व्योम ff_vk_free_buf(FFVulkanContext *s, FFVk_बफर *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
पूर्णांक ff_vk_get_pooled_बफर(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_बफर **buf, Vk_बफर_Usage_Flags usage,
                            व्योम *create_p_अग्र, माप_प्रकार आकार,
                            VkMemoryPropertyFlagBits mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
पूर्णांक ff_vk_host_map_बफर(FFVulkanContext *s, FFVk_बफर **dst,
                          uint8_t *src_तथ्य, Vk_Device_आकार आकार,
                          स्थिर AVBufferRef *src_buf,
                          Vk_बफर_Usage_Flags usage);

/**
 * Create a sampler.
 */
पूर्णांक ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       पूर्णांक unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
पूर्णांक ff_vk_shader_load(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_आकार[3], uint32_t required_subgroup_आकार);

/**
 * Link a shader into an executable.
 */
पूर्णांक ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      स्थिर अक्षर *spirv, माप_प्रकार spirv_len,
                      स्थिर अक्षर *entrypoint);

/**
 * Add/update push constants for execution.
 */
पूर्णांक ff_vk_shader_add_धकेलो_const(FFVulkanShader *shd, पूर्णांक offset, पूर्णांक आकार,
                                VkShaderStageFlagBits stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
व्योम ff_vk_shader_add_descriptor_set(FFVulkanContext *s, FFVulkanShader *shd,
                                     स्थिर FFVulkanDescriptorSetBinding *desc, पूर्णांक nb,
                                     पूर्णांक singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
पूर्णांक ff_vk_shader_register_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
व्योम ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            स्थिर FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
व्योम ff_vk_shader_update_धकेलो_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    VkShaderStageFlagBits stage,
                                    पूर्णांक offset, माप_प्रकार आकार, व्योम *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
पूर्णांक ff_vk_shader_update_desc_बफर(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णांक set, पूर्णांक bind, पूर्णांक elem,
                                    FFVk_बफर *buf, Vk_Device_आकार offset, Vk_Device_आकार len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
पूर्णांक ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णांक set, पूर्णांक bind, पूर्णांक offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
व्योम ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णांक set, पूर्णांक binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
व्योम ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
व्योम ff_vk_uninit(FFVulkanContext *s);

#पूर्ण_अगर /* AVUTIL_VULKAN_H */
