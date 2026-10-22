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

#यदि_अपरिभाषितम् AVUTIL_VULKAN_H
#परिभाषय AVUTIL_VULKAN_H

#परिभाषय VK_NO_PROTOTYPES

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
#परिभाषय RET(x)                                                                 \
    कुरु {                                                                       \
        यदि ((err = (x)) < 0)                                                   \
            गच्छ fail;                                                         \
    } यावत् (0)

/* Convenience macros for specialization lists */
#परिभाषय SPEC_LIST_MAX 256
#परिभाषय SPEC_LIST_CREATE(name, max_दीर्घता, max_आकार)           \
    av_assert1((max_दीर्घता) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_आकार) + 3*परिमाण(uint32_t)];      \
    Vk_Specialization_Map_प्रविष्टिः name##_entries[(max_दीर्घता) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_दत्त = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#परिभाषय SPEC_LIST_सङ्कलय(name, idx, val_द्वयङ्काः, val)                \
कुरु {                                                           \
    अचिह्नित पूर्णाङ्क name##_cnt = name->map_प्रविष्टिः_गणनम्;             \
    size_t name##_off = name->दत्त_आकार_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_दत्त;               \
    शून्य *name##_ep = (शून्य *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_द्वयङ्काः, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_प्रविष्टिः name##_new_entry = {              \
        .constantID = (idx),                                   \
        .विस्थापनम् = name##_off,                                  \
        .आकार = val_द्वयङ्काः >> 3,                                 \
    };                                                         \
    स्मृतिं_प्रतिलिख(name##_ep, &name##_new_entry,                       \
           परिमाण(Vk_Specialization_Map_प्रविष्टिः));                  \
    name->दत्त_आकार_2 = name##_off + (val_द्वयङ्काः >> 3);             \
    name->map_प्रविष्टिः_गणनम् = name##_cnt + 1;                      \
} यावत् (0)

#परिभाषय DUP_SAMPLER(x) { x, x, x, x }

#परिभाषय FF_VK_MAX_DESCRIPTOR_SETS 4
#परिभाषय FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#परिभाषय FF_VK_MAX_DESCRIPTOR_TYPES 16
#परिभाषय FF_VK_MAX_प्रक्षिप_CONSTS 4
#परिभाषय FF_VK_MAX_SHADERS 16

प्रकारनिर्देश संरचना FFVulkan_Descriptor_समुच्चयः_Binding {
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
} FFVulkan_Descriptor_समुच्चयः_Binding;

प्रकारनिर्देश संरचना FFVk_बफर {
    Vk_बफर buf;
    Vk_Device_स्मृतिः mem;
    Vk_स्मृतिः_Property_Flag_द्वयङ्काः flags;
    size_t आकार;
    Vk_Device_स्थानाङ्कः स्थानाङ्कः;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_विस्थापनम्;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_बफर;

/* Fixed dependency limits per exec context (with room to spare) */
#परिभाषय FF_VK_EXEC_MAX_FRAME_DEPS 64
#परिभाषय FF_VK_EXEC_MAX_BUF_DEPS 256
#परिभाषय FF_VK_EXEC_MAX_SW_FRAME_DEPS 16
#परिभाषय FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_FRAME_DEPS*AV_अङ्कः_दत्त_सूचकाः)

/* Default number of in-flight execution contexts per pool */
#परिभाषय FF_VK_DEFAULT_EXEC_CONTEXTS 4

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
    Vk_Command_बफर buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_मानम्;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t तालकम्;

    /* Opaque data, untouched, free to use by users */
    शून्य *opaque;

    शून्य *query_दत्त;
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
    Vk_Access_Flag_द्वयङ्काः access_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint32_t queue_family_dst[FF_VK_EXEC_MAX_FRAME_DEPS];
    uint8_t frame_update[FF_VK_EXEC_MAX_FRAME_DEPS];
} FFVkExecContext;

प्रकारनिर्देश संरचना FFVulkan_Descriptor_समुच्चयः {
    /* Descriptor buffer */
    Vk_Device_आकार layout_आकार;
    Vk_Device_आकार aligned_आकार; /* descriptorBufferOffsetAlignment */
    Vk_बफर_Usage_Flags usage;

    Vk_Descriptor_समुच्चयः_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_आकार binding_विस्थापनम्[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    पूर्णाङ्क nb_bindings;

    /* Descriptor set is shared between all submissions */
    पूर्णाङ्क singular;
} FFVulkan_Descriptor_समुच्चयः;

प्रकारनिर्देश संरचना FFVulkanShader {
    /* Name for id/debugging purposes */
    ध्रुव वर्ण *name;

    /* Whether shader is precompiled or not */
    पूर्णाङ्क precompiled;
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
    Vk_प्रक्षिप_Constant_Range प्रक्षिप_consts[FF_VK_MAX_प्रक्षिप_CONSTS];
    पूर्णाङ्क प्रक्षिप_consts_अङ्कः;

    /* Descriptor sets */
    FFVulkan_Descriptor_समुच्चयः desc_समुच्चयः[FF_VK_MAX_DESCRIPTOR_SETS];
    पूर्णाङ्क nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_समुच्चयः_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    पूर्णाङ्क use_प्रक्षिप;
    Vk_Descriptor_Pool_आकार desc_pool_आकार[FF_VK_MAX_DESCRIPTOR_TYPES];
    पूर्णाङ्क nb_desc_pool_आकार;
} FFVulkanShader;

प्रकारनिर्देश संरचना FFVulkan_Descriptor_समुच्चयः_दत्त {
    /* Descriptor buffer */
    FFVk_बफर buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_समुच्चयः_दत्त;

प्रकारनिर्देश संरचना FFVulkan_Shader_दत्त {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    पूर्णाङ्क nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_समुच्चयः_दत्त desc_समुच्चयः_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_बफर_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_समुच्चयः *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_दत्त;

प्रकारनिर्देश संरचना FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_बफर *cmd_bufs;
    पूर्णाङ्क pool_आकार;

    VkQueryPool query_pool;
    शून्य *query_दत्त;
    पूर्णाङ्क query_results;
    पूर्णाङ्क query_statuses;
    पूर्णाङ्क query_64bit;
    पूर्णाङ्क query_स्थितिः_stride;
    पूर्णाङ्क nb_queries;
    size_t qd_आकार;

    /* Registered shaders' data */
    FFVulkan_Shader_दत्त reg_shd[FF_VK_MAX_SHADERS];
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
    Vk_Physical_Device_स्मृतिः_Properties mprops;
    Vk_Physical_Device_External_स्मृतिः_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_बफर_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_आकार_Control_Properties subgroup_props;
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR coop_matrix_props;
    Vk_Physical_Device_प्रक्षिप_Descriptor_Properties_KHR प्रक्षिप_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#यदि_परिभाषितम् VK_EXT_shader_long_सदिशम्
    Vk_Physical_Device_Shader_Long_सदिशम्_Properties_EXT long_सदिशम्_props;
#यदि_अन्तः
    Vk_Queue_Family_Query_परिणाम_स्थितिः_Properties_KHR *query_props;
    VkQueueFamilyVideoPropertiesKHR *video_props;
#यदि_परिभाषितम् VK_KHR_maintenance9
    VkQueueFamilyOwnershipTransferPropertiesKHR *ownership_props;
#यदि_अन्तः
    VkQueueFamilyProperties2 *qf_props;
    पूर्णाङ्क tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    VkCooperativeMatrixPropertiesKHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#यदि_परिभाषितम् VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#यदि_अन्तः
#यदि_परिभाषितम् VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#यदि_अन्तः
    VkPhysicalDeviceFeatures2 feats;

    Vk_स्मृतिः_Property_Flag_द्वयङ्काः host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *निवेशः_चौकटाः_ref;
    AVBufferRef           *चौकटाः_ref;
    AVHWFramesContext     *चौकटाः;
    AVVulkan_चौकटाः_Context *hwfc;

    uint32_t               qfs[64];
    पूर्णाङ्क                    nb_qfs;

    /* Properties */
    पूर्णाङ्क                 output_विस्तारः;
    पूर्णाङ्क                output_height;
    गणना AVPixelFormat output_format;
    गणना AVPixelFormat  निवेशः_format;
} FFVulkanContext;

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_गणनम्_images(AVVkFrame *f)
{
    पूर्णाङ्क cnt = 0;
    यावत् (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    प्रत्यागम cnt;
}

स्थिर अन्तःस्थ ध्रुव शून्य *ff_vk_find_struct(ध्रुव शून्य *chain, VkStructureType stype)
{
    ध्रुव Vk_आधारः_अन्तर्_Structure *अन्तर् = chain;
    यावत् (अन्तर्) {
        यदि (अन्तर्->sType == stype)
            प्रत्यागम अन्तर्;

        अन्तर् = अन्तर्->p_अग्र;
    }

    प्रत्यागम रिक्त;
}

स्थिर अन्तःस्थ शून्य ff_vk_link_struct(शून्य *chain, ध्रुव शून्य *अन्तर्)
{
    Vk_आधारः_बहिर्गमनम्_Structure *बहिर्गमनम् = chain;
    यावत् (बहिर्गमनम्->p_अग्र)
        बहिर्गमनम् = बहिर्गमनम्->p_अग्र;

    बहिर्गमनम्->p_अग्र = (शून्य *)अन्तर्;
}

#परिभाषय FF_VK_STRUCT_EXT(CTX, आधारः, STRUCT_P, EXT_FLAG, TYPE) \
    कुरु {                                                      \
        यदि ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(आधारः, STRUCT_P);                \
        }                                                     \
    } यावत् (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
बाह्य ध्रुव VkComponentMapping ff_comp_तटस्थः_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
पूर्णाङ्क ff_vk_init(FFVulkanContext *s, शून्य *log_parent,
               AVBufferRef *device_ref, AVBufferRef *चौकटाः_ref);

/**
 * Converts Vulkan return values to strings
 */
ध्रुव वर्ण *ff_vk_ret2str(Vk_परिणाम res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_गन्तव्यम्_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_गन्तव्यम्_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
पूर्णाङ्क ff_vk_mt_is_np_rgb(गणना AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
शून्य ff_vk_समुच्चयः_perm(गणना AVPixelFormat pix_fmt, पूर्णाङ्क lut[4], पूर्णाङ्क inv);

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
VkFormat ff_vk_map_fmt_गन्तव्यम्_rep(VkFormat fmt, गणना FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
पूर्णाङ्क ff_vk_आरोपय_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkanDeviceQueueFamily *ff_vk_qf_find(FFVulkanContext *s,
                                         Vk_Queue_Flag_द्वयङ्काः dev_family,
                                         Vk_Video_Codec_Operation_Flag_द्वयङ्काः_KHR vid_ops);

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
Vk_परिणाम ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              शून्य **दत्त, Vk_Query_परिणाम_Flag_द्वयङ्काः flags);

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
शून्य ff_vk_exec_सङ्कलय_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  शून्य *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
शून्य ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   शून्य *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
शून्य ff_vk_exec_सङ्कलय_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

शून्य ff_vk_exec_सङ्कलय_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
शून्य ff_vk_exec_सङ्कलय_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
शून्य ff_vk_exec_सङ्कलय_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, पूर्णाङ्क nb,
                                 VkPipelineStageFlagBits2 stage,
                                 पूर्णाङ्क प्रतीक्षस्व); /* Ownership transferred if !wait */
पूर्णाङ्क ff_vk_exec_सङ्कलय_dep_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
पूर्णाङ्क ff_vk_exec_सङ्कलय_dep_sw_frame(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
शून्य ff_vk_exec_update_frame(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_स्मृतिः_Barrier2 *bar, uint32_t *nb_img_bar);
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
    ध्रुव Vk_आवण्टनम्_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_अङ्कः_दत्त_सूचकाः];
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
                            VkImageView views[AV_अङ्कः_दत्त_सूचकाः],
                            AVFrame *f, गणना FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
पूर्णाङ्क ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_अङ्कः_दत्त_सूचकाः],
                                AVFrame *f,
                                ध्रुव VkFormat fmts[AV_अङ्कः_दत्त_सूचकाः]);

#परिभाषय ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    कुरु {                                                                       \
        dst = (Vk_बफर_स्मृतिः_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_बफर_स्मृतिः_BARRIER_2,                \
            .src_Stage_आवरणम् = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_आवरणम् = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_आवरणम् = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_आवरणम् = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_Queue_Family_सूचकांक = VK_QUEUE_FAMILY_IGNORED,                    \
            .dst_Queue_Family_सूचकांक = VK_QUEUE_FAMILY_IGNORED,                    \
            .बफर = vkb->buf,                                                \
            .विस्थापनम् = offs,                                                    \
            .आकार = bsz                                                        \
        };                                                                     \
    } यावत्(0)

शून्य ff_vk_frame_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_स्मृतिः_Barrier2 *bar, पूर्णाङ्क *nb_bar,
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
पूर्णाङ्क ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_स्मृतिः *mem,
                       पूर्णाङ्क विस्तारः, पूर्णाङ्क height, VkFormat format, पूर्णाङ्क nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, शून्य *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
शून्य ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_स्मृतिः *mem);

पूर्णाङ्क ff_vk_alloc_mem(FFVulkanContext *s, Vk_स्मृतिः_Requirements *req,
                    Vk_स्मृतिः_Property_Flag_द्वयङ्काः req_flags, शून्य *alloc_extension,
                    Vk_स्मृतिः_Property_Flag_द्वयङ्काः *mem_flags, Vk_Device_स्मृतिः *mem);
पूर्णाङ्क ff_vk_create_buf(FFVulkanContext *s, FFVk_बफर *buf, size_t आकार,
                     शून्य *p_अग्र, शून्य *alloc_p_अग्र,
                     Vk_बफर_Usage_Flags usage, Vk_स्मृतिः_Property_Flag_द्वयङ्काः flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
पूर्णाङ्क ff_vk_flush_बफर(FFVulkanContext *s, FFVk_बफर *buf,
                       Vk_Device_आकार विस्थापनम्, Vk_Device_आकार mem_आकार,
                       पूर्णाङ्क flush);

/**
 * Buffer management code.
 */
पूर्णाङ्क ff_vk_map_buffers(FFVulkanContext *s, FFVk_बफर **buf, uint8_t *mem[],
                      पूर्णाङ्क nb_buffers, पूर्णाङ्क invalidate);
पूर्णाङ्क ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_बफर **buf, पूर्णाङ्क nb_buffers,
                        पूर्णाङ्क flush);

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_map_बफर(FFVulkanContext *s, FFVk_बफर *buf, uint8_t **mem,
                                   पूर्णाङ्क invalidate)
{
    प्रत्यागम ff_vk_map_buffers(s, (FFVk_बफर *[]){ buf }, mem,
                             1, invalidate);
}

स्थिर अन्तःस्थ पूर्णाङ्क ff_vk_unmap_बफर(FFVulkanContext *s, FFVk_बफर *buf, पूर्णाङ्क flush)
{
    प्रत्यागम ff_vk_unmap_buffers(s, (FFVk_बफर *[]){ buf }, 1, flush);
}

शून्य ff_vk_free_buf(FFVulkanContext *s, FFVk_बफर *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
पूर्णाङ्क ff_vk_get_pooled_बफर(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_बफर **buf, Vk_बफर_Usage_Flags usage,
                            शून्य *create_p_अग्र, size_t आकार,
                            Vk_स्मृतिः_Property_Flag_द्वयङ्काः mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
पूर्णाङ्क ff_vk_host_map_बफर(FFVulkanContext *s, FFVk_बफर **dst,
                          uint8_t *src_दत्त, Vk_Device_आकार आकार,
                          ध्रुव AVBufferRef *src_buf,
                          Vk_बफर_Usage_Flags usage);

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
पूर्णाङ्क ff_vk_shader_आरोपय(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_आकार[3], uint32_t required_subgroup_आकार);

/**
 * Link a shader into an executable.
 */
पूर्णाङ्क ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      ध्रुव वर्ण *spirv, size_t spirv_len,
                      ध्रुव वर्ण *entrypoint);

/**
 * Add/update push constants for execution.
 */
पूर्णाङ्क ff_vk_shader_सङ्कलय_प्रक्षिप_const(FFVulkanShader *shd, पूर्णाङ्क विस्थापनम्, पूर्णाङ्क आकार,
                                Vk_Shader_Stage_Flag_द्वयङ्काः stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
शून्य ff_vk_shader_सङ्कलय_descriptor_समुच्चयः(FFVulkanContext *s, FFVulkanShader *shd,
                                     ध्रुव FFVulkan_Descriptor_समुच्चयः_Binding *desc, पूर्णाङ्क nb,
                                     पूर्णाङ्क singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
पूर्णाङ्क ff_vk_shader_पञ्जिकाकोशः_exec(FFVulkanContext *s, FFVkExecPool *pool,
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
                                    Vk_Shader_Stage_Flag_द्वयङ्काः stage,
                                    पूर्णाङ्क विस्थापनम्, size_t आकार, शून्य *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
पूर्णाङ्क ff_vk_shader_update_desc_बफर(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    पूर्णाङ्क समुच्चयः, पूर्णाङ्क bind, पूर्णाङ्क elem,
                                    FFVk_बफर *buf, Vk_Device_आकार विस्थापनम्, Vk_Device_आकार len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
पूर्णाङ्क ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, पूर्णाङ्क समुच्चयः, पूर्णाङ्क bind, पूर्णाङ्क offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
शून्य ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, पूर्णाङ्क समुच्चयः, पूर्णाङ्क binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
शून्य ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
शून्य ff_vk_uninit(FFVulkanContext *s);

#यदि_अन्तः /* AVUTIL_VULKAN_H */
