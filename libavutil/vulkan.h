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

#నిర్వచితం_కాకపోతే AVUTIL_VULKAN_H
#నిర్వచించు AVUTIL_VULKAN_H

#నిర్వచించు VK_NO_PROTOTYPES

#అన్తర్భావ <stdatomic.h>

#అన్తర్భావ "refstruct.h"

#అన్తర్భావ "thread.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "vulkan_functions.h"
#అన్తర్భావ "hwcontext_vulkan.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "intreadwrite.h"

/* Helper, pretty much every Vulkan return value needs to be checked */
#నిర్వచించు RET(x)                                                                 \
    చేయి {                                                                       \
        ఒకవేళ ((err = (x)) < 0)                                                   \
            వెళ్ళు fail;                                                         \
    } అయితే (0)

/* Convenience macros for specialization lists */
#నిర్వచించు SPEC_LIST_MAX 256
#నిర్వచించు SPEC_LIST_CREATE(name, max_నిడివి, max_కొలత)           \
    av_assert1((max_నిడివి) < (SPEC_LIST_MAX - 3));            \
    uint8_t name##_data[(max_కొలత) + 3*పరిమాణం(uint32_t)];      \
    Vk_Specialization_Map_నమోదు name##_entries[(max_నిడివి) + 3]; \
    VkSpecializationInfo name##_info = {                       \
        .pMapEntries = name##_entries,                         \
        .p_దత్తాంశం = name##_data,                                  \
    };                                                         \
    VkSpecializationInfo *name = &name##_info;

#నిర్వచించు SPEC_LIST_కూడు(name, idx, val_బిట్లు, val)                \
చేయి {                                                           \
    గుర్తులేని పూర్ణాంకం name##_cnt = name->map_నమోదు_లెక్క;             \
    size_t name##_off = name->దత్తాంశం_కొలత_2;                        \
    uint8_t *name##_dp = (uint8_t *)name->p_దత్తాంశం;               \
    శూన్య *name##_ep = (శూన్య *)&name->pMapEntries[name##_cnt];  \
    AV_WN(val_బిట్లు, name##_dp + name##_off, (val));            \
    Vk_Specialization_Map_నమోదు name##_new_entry = {              \
        .constantID = (idx),                                   \
        .స్థానభ్రంశం = name##_off,                                  \
        .కొలత = val_బిట్లు >> 3,                                 \
    };                                                         \
    జ్ఞాపకం_నకలు(name##_ep, &name##_new_entry,                       \
           పరిమాణం(Vk_Specialization_Map_నమోదు));                  \
    name->దత్తాంశం_కొలత_2 = name##_off + (val_బిట్లు >> 3);             \
    name->map_నమోదు_లెక్క = name##_cnt + 1;                      \
} అయితే (0)

#నిర్వచించు DUP_SAMPLER(x) { x, x, x, x }

#నిర్వచించు FF_VK_MAX_DESCRIPTOR_SETS 4
#నిర్వచించు FF_VK_MAX_DESCRIPTOR_BINDINGS 16
#నిర్వచించు FF_VK_MAX_DESCRIPTOR_TYPES 16
#నిర్వచించు FF_VK_MAX_నెట్టు_CONSTS 4
#నిర్వచించు FF_VK_MAX_SHADERS 16

రకనిర్వచనం నిర్మాణం FFVulkan_Descriptor_సమితి_Binding {
    స్థిరరాశి అక్షరం         *name;
    VkDescriptorType    type;
    స్థిరరాశి అక్షరం         *mem_layout;  /* Storage images (rgba8, etc.) and buffers (std430, etc.) */
    స్థిరరాశి అక్షరం         *mem_quali;   /* readonly, writeonly, etc. */
    స్థిరరాశి అక్షరం         *buf_content; /* For buffers */
    uint32_t            dimensions;  /* Needed for e.g. sampler%iD */
    uint32_t            elems;       /* 0 - scalar, 1 or more - vector */
    VkShaderStageFlags  stages;
    uint32_t            buf_elems;   /* Appends [buf_elems] to the contents. Avoids manually printing to a string. */
    VkSampler           samplers[4]; /* Sampler to use for all elems */
} FFVulkan_Descriptor_సమితి_Binding;

రకనిర్వచనం నిర్మాణం FFVk_బఫరు {
    Vk_బఫరు buf;
    Vk_Device_జ్ఞాపకం mem;
    Vk_జ్ఞాపకం_Property_Flag_బిట్లు flags;
    size_t కొలత;
    Vk_Device_చిరునామా చిరునామా;

    /* Only valid when allocated via ff_vk_get_pooled_buffer with HOST_VISIBLE or
     * via ff_vk_host_map_buffer */
    uint8_t *mapped_mem;

    /* Set by ff_vk_host_map_buffer. This is the offset at which the buffer data
     * actually begins at.
     * The address and mapped_mem fields will be offset by this amount. */
    size_t virtual_స్థానభ్రంశం;

    /* If host mapping, reference to the backing host memory buffer */
    AVBufferRef *host_ref;
} FFVk_బఫరు;

/* Fixed dependency limits per exec context (with room to spare) */
#నిర్వచించు FF_VK_EXEC_MAX_చట్రం_DEPS 64
#నిర్వచించు FF_VK_EXEC_MAX_BUF_DEPS 256
#నిర్వచించు FF_VK_EXEC_MAX_SW_చట్రం_DEPS 16
#నిర్వచించు FF_VK_EXEC_MAX_SEM_OPS (FF_VK_EXEC_MAX_చట్రం_DEPS*AV_అంకె_దత్తాంశం_సూచికలు)

/* Default number of in-flight execution contexts per pool */
#నిర్వచించు FF_VK_DEFAULT_EXEC_CONTEXTS 4

రకనిర్వచనం నిర్మాణం FFVkExecObjDep {
    uint64_t obj;
    VkObjectType type;
} FFVkExecObjDep;

రకనిర్వచనం నిర్మాణం FFVkExecContext {
    uint32_t idx;
    స్థిరరాశి నిర్మాణం FFVkExecPool *మాతృ;

    /* Set on submission; pool-rolling users check and clear it to tell
     * contexts with uncollected results apart from fresh ones */
    పూర్ణాంకం had_submission;

    /* Queue for the execution context */
    Vk_వరుస వరుస;
    పూర్ణాంకం qf;
    పూర్ణాంకం qi;

    /* Command buffer for the context */
    Vk_Command_బఫరు buf;

    /* Busy (claimed or executing) while the counter is below sem_value;
     * signalled by the submission, or by ff_vk_exec_discard() */
    VkSemaphore sem;
    uint64_t sem_విలువ;

    /* Briefly guards the dependency lists; the busy state is carried by the
     * semaphore above */
    pthread_mutex_t తాళం_2;

    /* Opaque data, untouched, free to use by users */
    శూన్య *opaque;

    శూన్య *query_దత్తాంశం;
    పూర్ణాంకం query_idx;

    /* Buffer dependencies */
    AVBufferRef *buf_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    పూర్ణాంకం nb_buf_deps;

    /* AVRefStruct object dependencies */
    శూన్య *refstruct_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    పూర్ణాంకం nb_refstruct_deps;

    /* Raw Vulkan object dependencies, destroyed on release */
    FFVkExecObjDep obj_deps[FF_VK_EXEC_MAX_BUF_DEPS];
    పూర్ణాంకం nb_obj_deps;

    /* Frame dependencies */
    AVFrame *చట్రం_deps[FF_VK_EXEC_MAX_చట్రం_DEPS];
    పూర్ణాంకం nb_చట్రం_deps;

    /* Software frame dependencies */
    AVFrame *sw_చట్రం_deps[FF_VK_EXEC_MAX_SW_చట్రం_DEPS];
    పూర్ణాంకం nb_sw_చట్రం_deps;

    VkSemaphoreSubmitInfo sem_wait[FF_VK_EXEC_MAX_SEM_OPS];
    పూర్ణాంకం sem_wait_cnt;

    VkSemaphoreSubmitInfo sem_sig[FF_VK_EXEC_MAX_SEM_OPS];
    పూర్ణాంకం sem_sig_cnt;

    uint64_t *sem_sig_val_dst[FF_VK_EXEC_MAX_SEM_OPS];
    పూర్ణాంకం sem_sig_val_dst_cnt;

    uint8_t చట్రం_locked[FF_VK_EXEC_MAX_చట్రం_DEPS];
    Vk_Access_Flag_బిట్లు access_dst[FF_VK_EXEC_MAX_చట్రం_DEPS];
    VkImageLayout layout_dst[FF_VK_EXEC_MAX_చట్రం_DEPS];
    uint32_t వరుస_family_dst[FF_VK_EXEC_MAX_చట్రం_DEPS];
    uint8_t చట్రం_update[FF_VK_EXEC_MAX_చట్రం_DEPS];
} FFVkExecContext;

రకనిర్వచనం నిర్మాణం FFVulkan_Descriptor_సమితి {
    /* Descriptor buffer */
    Vk_Device_కొలత layout_కొలత;
    Vk_Device_కొలత aligned_కొలత; /* descriptorBufferOffsetAlignment */
    Vk_బఫరు_Usage_Flags usage;

    Vk_Descriptor_సమితి_Layout_Binding binding[FF_VK_MAX_DESCRIPTOR_BINDINGS];
    Vk_Device_కొలత binding_స్థానభ్రంశం[FF_VK_MAX_DESCRIPTOR_BINDINGS];

    పూర్ణాంకం nb_bindings;

    /* Descriptor set is shared between all submissions */
    పూర్ణాంకం singular;
} FFVulkan_Descriptor_సమితి;

రకనిర్వచనం నిర్మాణం FFVulkanShader {
    /* Name for id/debugging purposes */
    స్థిరరాశి అక్షరం *name;

    /* Whether shader is precompiled or not */
    పూర్ణాంకం precompiled;
    VkSpecializationInfo *specialization_info;

    /* Compute shader local group sizes */
    uint32_t lg_కొలత[3];

    /* Shader bind point/type */
    VkPipelineStageFlags stage;
    Vk_Pipeline_Bind_బిందువు bind_బిందువు;

    /* Creation info */
    Vk_Pipeline_Shader_Stage_Required_Subgroup_కొలత_Create_Info subgroup_info;

    VkPipeline pipeline;

    /* Pipeline layout */
    VkPipelineLayout pipeline_layout;

    /* Push consts */
    Vk_నెట్టు_Constant_Range నెట్టు_consts[FF_VK_MAX_నెట్టు_CONSTS];
    పూర్ణాంకం నెట్టు_consts_అంకె;

    /* Descriptor sets */
    FFVulkan_Descriptor_సమితి desc_సమితి[FF_VK_MAX_DESCRIPTOR_SETS];
    పూర్ణాంకం nb_descriptor_sets;

    /* Descriptors */
    Vk_Descriptor_సమితి_Layout desc_layout[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pool */
    పూర్ణాంకం use_నెట్టు;
    Vk_Descriptor_Pool_కొలత desc_pool_కొలత[FF_VK_MAX_DESCRIPTOR_TYPES];
    పూర్ణాంకం nb_desc_pool_కొలత;
} FFVulkanShader;

రకనిర్వచనం నిర్మాణం FFVulkan_Descriptor_సమితి_దత్తాంశం {
    /* Descriptor buffer */
    FFVk_బఫరు buf;
    uint8_t *desc_mem;
} FFVulkan_Descriptor_సమితి_దత్తాంశం;

రకనిర్వచనం నిర్మాణం FFVulkan_Shader_దత్తాంశం {
    /* Shader to which this data belongs to */
    FFVulkanShader *shd;
    పూర్ణాంకం nb_descriptor_sets;

    /* Descriptor buffer */
    FFVulkan_Descriptor_సమితి_దత్తాంశం desc_సమితి_buf[FF_VK_MAX_DESCRIPTOR_SETS];
    Vk_Descriptor_బఫరు_Binding_Info_EXT desc_bind[FF_VK_MAX_DESCRIPTOR_SETS];

    /* Descriptor pools */
    Vk_Descriptor_సమితి *desc_sets;
    VkDescriptorPool desc_pool;
} FFVulkan_Shader_దత్తాంశం;

రకనిర్వచనం నిర్మాణం FFVkExecPool {
    FFVkExecContext *contexts;
    atomic_uint_least64_t idx;

    VkCommandPool *cmd_buf_pools;
    Vk_Command_బఫరు *cmd_bufs;
    పూర్ణాంకం pool_కొలత;

    VkQueryPool query_pool;
    శూన్య *query_దత్తాంశం;
    పూర్ణాంకం query_results;
    పూర్ణాంకం query_statuses;
    పూర్ణాంకం query_64bit;
    పూర్ణాంకం query_స్థితి_stride;
    పూర్ణాంకం nb_queries;
    size_t qd_కొలత;

    /* Registered shaders' data */
    FFVulkan_Shader_దత్తాంశం reg_shd[FF_VK_MAX_SHADERS];
    పూర్ణాంకం nb_reg_shd;
} FFVkExecPool;

రకనిర్వచనం నిర్మాణం FFVulkanContext {
    స్థిరరాశి AVClass *class;
    శూన్య *log_మాతృ;

    FFVulkanFunctions     vkfn;
    FFVulkanExtensions    extensions;
    VkPhysicalDeviceProperties2 props;
    VkPhysicalDeviceVulkan11Properties props_11;
    VkPhysicalDeviceDriverProperties driver_props;
    Vk_Physical_Device_జ్ఞాపకం_Properties mprops;
    Vk_Physical_Device_External_జ్ఞాపకం_Host_Properties_EXT hprops;
    Vk_Physical_Device_Descriptor_బఫరు_Properties_EXT desc_buf_props;
    Vk_Physical_Device_Subgroup_కొలత_Control_Properties subgroup_props;
    Vk_Physical_Device_Cooperative_మాతృక_Properties_KHR coop_మాతృక_props;
    Vk_Physical_Device_నెట్టు_Descriptor_Properties_KHR నెట్టు_desc_props;
    VkPhysicalDeviceOpticalFlowPropertiesNV optical_flow_props;
#నిర్వచితమైతే VK_EXT_shader_long_సదిశ
    Vk_Physical_Device_Shader_Long_సదిశ_Properties_EXT long_సదిశ_props;
#అయితే_ముగింపు
    Vk_వరుస_Family_Query_ఫలితం_స్థితి_Properties_KHR *query_props;
    Vk_వరుస_Family_Video_Properties_KHR *video_props;
#నిర్వచితమైతే VK_KHR_maintenance9
    Vk_వరుస_Family_Ownership_Transfer_Properties_KHR *ownership_props;
#అయితే_ముగింపు
    Vk_వరుస_Family_Properties2 *qf_props;
    పూర్ణాంకం tot_nb_qfs;
    VkPhysicalDeviceHostImageCopyPropertiesEXT host_image_props;
    VkImageLayout *host_image_copy_layouts;

    Vk_Cooperative_మాతృక_Properties_KHR *coop_mat_props;
    uint32_t coop_mat_props_nb;

    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT atomic_float_feats;
    AVRefStructPool *imageviews_pool;

    VkPhysicalDeviceVulkan12Features feats_12;
#నిర్వచితమైతే VK_KHR_unified_image_layouts
    VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR unified_layout_feats;
#అయితే_ముగింపు
#నిర్వచితమైతే VK_KHR_maintenance11
    VkPhysicalDeviceMaintenance11FeaturesKHR maintenance_11_feats;
#అయితే_ముగింపు
    VkPhysicalDeviceFeatures2 feats;

    Vk_జ్ఞాపకం_Property_Flag_బిట్లు host_cached_flag;

    AVBufferRef           *device_ref;
    AVHWDeviceContext     *device;
    AVVulkanDeviceContext *hwctx;

    AVBufferRef           *ఆదానం_చట్రాలు_ref;
    AVBufferRef           *చట్రాలు_ref;
    AVHWFramesContext     *చట్రాలు;
    AVVulkan_చట్రాలు_Context *hwfc;

    uint32_t               qfs[64];
    పూర్ణాంకం                    nb_qfs;

    /* Properties */
    పూర్ణాంకం                 output_వెడల్పు;
    పూర్ణాంకం                output_ఎత్తు;
    గణన AVPixelFormat output_format;
    గణన AVPixelFormat  ఆదానం_format;
} FFVulkanContext;

స్థిర అంతఃవరుస పూర్ణాంకం ff_vk_లెక్క_images(AVVk_చట్రం *f)
{
    పూర్ణాంకం cnt = 0;
    అయితే (cnt < FF_ARRAY_ELEMS(f->img) && f->img[cnt])
        cnt++;

    తిరిగి cnt;
}

స్థిర అంతఃవరుస స్థిరరాశి శూన్య *ff_vk_కనుగొను_struct(స్థిరరాశి శూన్య *chain, VkStructureType stype)
{
    స్థిరరాశి Vk_పునాది_లోపల_Structure *లోపల = chain;
    అయితే (లోపల) {
        ఒకవేళ (లోపల->sType == stype)
            తిరిగి లోపల;

        లోపల = లోపల->p_తదుపరి;
    }

    తిరిగి ఖాళీ;
}

స్థిర అంతఃవరుస శూన్య ff_vk_link_struct(శూన్య *chain, స్థిరరాశి శూన్య *లోపల)
{
    Vk_పునాది_బహిర్గతం_Structure *బహిర్గతం = chain;
    అయితే (బహిర్గతం->p_తదుపరి)
        బహిర్గతం = బహిర్గతం->p_తదుపరి;

    బహిర్గతం->p_తదుపరి = (శూన్య *)లోపల;
}

#నిర్వచించు FF_VK_STRUCT_EXT(CTX, పునాది, STRUCT_P, EXT_FLAG, TYPE) \
    చేయి {                                                      \
        ఒకవేళ ((EXT_FLAG == FF_VK_EXT_NO_FLAG) ||                \
            ((CTX)->extensions & EXT_FLAG)) {                 \
            (STRUCT_P)->sType = TYPE;                         \
            ff_vk_link_struct(పునాది, STRUCT_P);                \
        }                                                     \
    } అయితే (0)

/* Identity mapping - r = r, b = b, g = g, a = a */
బాహ్య స్థిరరాశి VkComponentMapping ff_comp_తటస్థం_map;

/**
 * Initializes the AVClass, in case this context is not used
 * as the main user's context.
 * May use either a frames context reference, or a device context reference.
 */
పూర్ణాంకం ff_vk_init(FFVulkanContext *s, శూన్య *log_మాతృ,
               AVBufferRef *device_ref, AVBufferRef *చట్రాలు_ref);

/**
 * Converts Vulkan return values to strings
 */
స్థిరరాశి అక్షరం *ff_vk_ret2str(Vk_ఫలితం res);

/**
 * Map between usage and features.
 */
VkImageUsageFlags ff_vk_map_feats_గమ్యం_usage(VkFormatFeatureFlagBits2 feats);
VkFormatFeatureFlagBits2 ff_vk_map_usage_గమ్యం_feats(VkImageUsageFlags usage);

/**
 * Returns 1 if pixfmt is a usable RGB format.
 */
పూర్ణాంకం ff_vk_mt_is_np_rgb(గణన AVPixelFormat pix_fmt);

/**
 * Since storage images may not be swizzled, we have to do this in the
 * shader itself. This fills in a lookup table to do it.
 */
శూన్య ff_vk_సమితి_perm(గణన AVPixelFormat pix_fmt, పూర్ణాంకం lut[4], పూర్ణాంకం inv);

/**
 * Get the aspect flag for a plane from an image.
 */
VkImageAspectFlags ff_vk_aspect_flag(AVFrame *f, పూర్ణాంకం p);

/**
 * Returns the format to use for images in shaders.
 */
గణన FFVkShaderRepFormat {
    /* Native format with no conversion. May require casting. */
    FF_VK_REP_NATIVE = 0,
    /* Float conversion of the native format. */
    FF_VK_REP_FLOAT,
    /* Signed integer version of the native format */
    FF_VK_REP_INT,
    /* Unsigned integer version of the native format */
    FF_VK_REP_UINT,
};
స్థిరరాశి అక్షరం *ff_vk_shader_rep_fmt(గణన AVPixelFormat pix_fmt,
                                 గణన FFVkShaderRepFormat rep_fmt);

/**
 * Returns the view format for the given representation of fmt, or
 * VK_FORMAT_UNDEFINED if there is none.
 */
VkFormat ff_vk_map_fmt_గమ్యం_rep(VkFormat fmt, గణన FFVkShaderRepFormat rep_fmt);

/**
 * Loads props/mprops/driver_props
 */
పూర్ణాంకం ff_vk_ఎక్కించు_props(FFVulkanContext *s);

/**
 * Chooses an appropriate QF.
 */
AVVulkan_Device_వరుస_Family *ff_vk_qf_కనుగొను(FFVulkanContext *s,
                                         Vk_వరుస_Flag_బిట్లు dev_family,
                                         Vk_Video_Codec_Operation_Flag_బిట్లు_KHR vid_ops);

/**
 * Allocates/frees an execution pool.
 * If used in a multi-threaded context, there must be at least as many contexts
 * as there are threads.
 * ff_vk_exec_pool_init_desc() MUST be called if ff_vk_exec_descriptor_set_add()
 * has been called.
 */
పూర్ణాంకం ff_vk_exec_pool_init(FFVulkanContext *s, AVVulkan_Device_వరుస_Family *qf,
                         FFVkExecPool *pool, పూర్ణాంకం nb_contexts,
                         పూర్ణాంకం nb_queries, VkQueryType query_type, పూర్ణాంకం query_64bit,
                         స్థిరరాశి శూన్య *query_create_pnext);
శూన్య ff_vk_exec_pool_free(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Retrieve an execution pool. Threadsafe.
 */
FFVkExecContext *ff_vk_exec_get(FFVulkanContext *s, FFVkExecPool *pool);

/**
 * Performs nb_queries queries and returns their results and statuses.
 * 64_BIT and WITH_STATUS flags are ignored as 64_BIT must be specified via
 * query_64bit in ff_vk_exec_pool_init() and WITH_STATUS is always enabled.
 */
Vk_ఫలితం ff_vk_exec_get_query(FFVulkanContext *s, FFVkExecContext *e,
                              శూన్య **దత్తాంశం, Vk_Query_ఫలితం_Flag_బిట్లు flags);

/**
 * Start/submit/wait an execution.
 * ff_vk_exec_start() always waits on a submission, so using ff_vk_exec_wait()
 * is not necessary (unless using it is just better).
 */
పూర్ణాంకం ff_vk_exec_ప్రారంభం(FFVulkanContext *s, FFVkExecContext *e);
పూర్ణాంకం ff_vk_exec_submit(FFVulkanContext *s, FFVkExecContext *e);
శూన్య ff_vk_exec_wait(FFVulkanContext *s, FFVkExecContext *e);

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
శూన్య ff_vk_exec_కూడు_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                  శూన్య *obj);

/* Moves the caller's reference into the execution's dependencies, given a
 * pointer to it; a duplicate of an already-tracked object is released. */
శూన్య ff_vk_exec_move_dep_refstruct(FFVulkanContext *s, FFVkExecContext *e,
                                   శూన్య *obj);

/* Takes ownership of a raw Vulkan object, destroyed when the execution's
 * dependencies are released. */
శూన్య ff_vk_exec_కూడు_dep_obj(FFVulkanContext *s, FFVkExecContext *e,
                            VkObjectType type, uint64_t obj);

శూన్య ff_vk_exec_కూడు_dep_wait_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore sem, uint64_t val,
                                 VkPipelineStageFlagBits2 stage);
శూన్య ff_vk_exec_కూడు_dep_signal_sem(FFVulkanContext *s, FFVkExecContext *e,
                                   VkSemaphore sem, uint64_t val,
                                   VkPipelineStageFlagBits2 stage);
శూన్య ff_vk_exec_కూడు_dep_bool_sem(FFVulkanContext *s, FFVkExecContext *e,
                                 VkSemaphore *sem, పూర్ణాంకం nb,
                                 VkPipelineStageFlagBits2 stage,
                                 పూర్ణాంకం wait); /* Ownership transferred if !wait */
పూర్ణాంకం ff_vk_exec_కూడు_dep_చట్రం(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             VkPipelineStageFlagBits2 wait_stage,
                             VkPipelineStageFlagBits2 signal_stage);
పూర్ణాంకం ff_vk_exec_కూడు_dep_sw_చట్రం(FFVulkanContext *s, FFVkExecContext *e,
                                AVFrame *f);
శూన్య ff_vk_exec_update_చట్రం(FFVulkanContext *s, FFVkExecContext *e, AVFrame *f,
                             Vk_Image_జ్ఞాపకం_Barrier2 *bar, uint32_t *nb_img_bar);
పూర్ణాంకం ff_vk_exec_mirror_sem_విలువ(FFVulkanContext *s, FFVkExecContext *e,
                                VkSemaphore *dst, uint64_t *dst_val,
                                AVFrame *f);
శూన్య ff_vk_exec_discard(FFVulkanContext *s, FFVkExecContext *e);

/**
 * Create a single imageview for a given plane.
 */
పూర్ణాంకం ff_vk_create_imageview(FFVulkanContext *s,
                           VkImageView *img_view, VkImageAspectFlags *aspect,
                           AVFrame *f, పూర్ణాంకం plane, గణన FFVkShaderRepFormat rep_fmt);

/* Refcounted set of image views; stashes destruction handles to be context-free */
రకనిర్వచనం నిర్మాణం FFVkImageViews {
    పూర్ణాంకం nb_views;

    VkDevice dev;
    స్థిరరాశి Vk_కేటాయింపు_Callbacks *alloc;
    PFN_vkDestroyImageView destroy_image_view;

    VkImageView views[AV_అంకె_దత్తాంశం_సూచికలు];
} FFVkImageViews;

/**
 * Allocate a reference-counted set of image views, zero-initialized for the
 * caller to create.
 */
FFVkImageViews *ff_vk_imageviews_alloc(FFVulkanContext *s, పూర్ణాంకం nb_views);

/**
 * Create an imageview and add it as a dependency to an execution.
 */
పూర్ణాంకం ff_vk_create_imageviews(FFVulkanContext *s, FFVkExecContext *e,
                            VkImageView views[AV_అంకె_దత్తాంశం_సూచికలు],
                            AVFrame *f, గణన FFVkShaderRepFormat rep_fmt);

/**
 * Same as ff_vk_create_imageviews(), but with an explicit view format for
 * each plane, which must be compatible with the format of the image.
 */
పూర్ణాంకం ff_vk_create_imageviews_fmt(FFVulkanContext *s, FFVkExecContext *e,
                                VkImageView views[AV_అంకె_దత్తాంశం_సూచికలు],
                                AVFrame *f,
                                స్థిరరాశి VkFormat fmts[AV_అంకె_దత్తాంశం_సూచికలు]);

#నిర్వచించు ff_vk_buf_barrier(dst, vkb, s_stage, s_access, s_access2,              \
                          d_stage, d_access, d_access2, offs, bsz)             \
    చేయి {                                                                       \
        dst = (Vk_బఫరు_జ్ఞాపకం_Barrier2) {                                       \
            .sType = VK_STRUCTURE_TYPE_బఫరు_జ్ఞాపకం_BARRIER_2,                \
            .src_Stage_ముసుగు = VK_PIPELINE_STAGE_2_ ##s_stage,                    \
            .src_Access_ముసుగు = VK_ACCESS_2_ ##s_access |                         \
                             VK_ACCESS_2_ ##s_access2,                         \
            .dst_Stage_ముసుగు = VK_PIPELINE_STAGE_2_ ##d_stage,                    \
            .dst_Access_ముసుగు = VK_ACCESS_2_ ##d_access |                         \
                             VK_ACCESS_2_ ##d_access2,                         \
            .src_వరుస_Family_సూచీ = VK_వరుస_FAMILY_IGNORED,                    \
            .dst_వరుస_Family_సూచీ = VK_వరుస_FAMILY_IGNORED,                    \
            .బఫరు = vkb->buf,                                                \
            .స్థానభ్రంశం = offs,                                                    \
            .కొలత = bsz                                                        \
        };                                                                     \
    } అయితే(0)

శూన్య ff_vk_చట్రం_barrier(FFVulkanContext *s, FFVkExecContext *e,
                         AVFrame *pic, Vk_Image_జ్ఞాపకం_Barrier2 *bar, పూర్ణాంకం *nb_bar,
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
పూర్ణాంకం ff_vk_image_create(FFVulkanContext *s, VkImage *img, Vk_Device_జ్ఞాపకం *mem,
                       పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, VkFormat format, పూర్ణాంకం nb_layers,
                       VkImageTiling tiling, VkImageUsageFlags usage,
                       VkImageCreateFlags flags, శూన్య *create_pnext);

/**
 * Free an image created by ff_vk_image_create(); all GPU use must have
 * completed.
 */
శూన్య ff_vk_image_free(FFVulkanContext *s, VkImage *img, Vk_Device_జ్ఞాపకం *mem);

పూర్ణాంకం ff_vk_alloc_mem(FFVulkanContext *s, Vk_జ్ఞాపకం_Requirements *req,
                    Vk_జ్ఞాపకం_Property_Flag_బిట్లు req_flags, శూన్య *alloc_extension,
                    Vk_జ్ఞాపకం_Property_Flag_బిట్లు *mem_flags, Vk_Device_జ్ఞాపకం *mem);
పూర్ణాంకం ff_vk_create_buf(FFVulkanContext *s, FFVk_బఫరు *buf, size_t కొలత,
                     శూన్య *p_తదుపరి, శూన్య *alloc_p_తదుపరి,
                     Vk_బఫరు_Usage_Flags usage, Vk_జ్ఞాపకం_Property_Flag_బిట్లు flags);

/**
 * Flush or invalidate a single buffer, with a given size and offset.
 */
పూర్ణాంకం ff_vk_flush_బఫరు(FFVulkanContext *s, FFVk_బఫరు *buf,
                       Vk_Device_కొలత స్థానభ్రంశం, Vk_Device_కొలత mem_కొలత,
                       పూర్ణాంకం flush);

/**
 * Buffer management code.
 */
పూర్ణాంకం ff_vk_map_buffers(FFVulkanContext *s, FFVk_బఫరు **buf, uint8_t *mem[],
                      పూర్ణాంకం nb_buffers, పూర్ణాంకం invalidate);
పూర్ణాంకం ff_vk_unmap_buffers(FFVulkanContext *s, FFVk_బఫరు **buf, పూర్ణాంకం nb_buffers,
                        పూర్ణాంకం flush);

స్థిర అంతఃవరుస పూర్ణాంకం ff_vk_map_బఫరు(FFVulkanContext *s, FFVk_బఫరు *buf, uint8_t **mem,
                                   పూర్ణాంకం invalidate)
{
    తిరిగి ff_vk_map_buffers(s, (FFVk_బఫరు *[]){ buf }, mem,
                             1, invalidate);
}

స్థిర అంతఃవరుస పూర్ణాంకం ff_vk_unmap_బఫరు(FFVulkanContext *s, FFVk_బఫరు *buf, పూర్ణాంకం flush)
{
    తిరిగి ff_vk_unmap_buffers(s, (FFVk_బఫరు *[]){ buf }, 1, flush);
}

శూన్య ff_vk_free_buf(FFVulkanContext *s, FFVk_బఫరు *buf);

/** Initialize a pool and create AVBufferRefs containing FFVkBuffer.
 * Threadsafe to use. Buffers are automatically mapped on creation if
 * VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is set in mem_props. Users should
 * synchronize access themselvesd. Mainly meant for device-local buffers. */
పూర్ణాంకం ff_vk_get_pooled_బఫరు(FFVulkanContext *ctx, AVRefStructPool **buf_pool,
                            FFVk_బఫరు **buf, Vk_బఫరు_Usage_Flags usage,
                            శూన్య *create_p_తదుపరి, size_t కొలత,
                            Vk_జ్ఞాపకం_Property_Flag_బిట్లు mem_props);

/** Maps a system RAM buffer into a Vulkan buffer.
 * References the source buffer. Imports size bytes starting at src_data,
 * rounded up to the host-pointer import alignment and clamped to the end
 * of src_buf. */
పూర్ణాంకం ff_vk_host_map_బఫరు(FFVulkanContext *s, FFVk_బఫరు **dst,
                          uint8_t *src_దత్తాంశం, Vk_Device_కొలత కొలత,
                          స్థిరరాశి AVBufferRef *src_buf,
                          Vk_బఫరు_Usage_Flags usage);

/**
 * Create a sampler.
 */
పూర్ణాంకం ff_vk_init_sampler(FFVulkanContext *s, VkSampler *sampler,
                       పూర్ణాంకం unnorm_coords, VkFilter filt);

/**
 * Initialize a shader object.
 * If spec is non-null, it must have been created with SPEC_LIST_CREATE().
 * The IDs for the workgroup size must be 253, 254, 255.
 */
పూర్ణాంకం ff_vk_shader_ఎక్కించు(FFVulkanShader *shd,
                      VkPipelineStageFlags stage, VkSpecializationInfo *spec,
                      uint32_t wg_కొలత[3], uint32_t required_subgroup_కొలత);

/**
 * Link a shader into an executable.
 */
పూర్ణాంకం ff_vk_shader_link(FFVulkanContext *s, FFVulkanShader *shd,
                      స్థిరరాశి అక్షరం *spirv, size_t spirv_len,
                      స్థిరరాశి అక్షరం *entrypoint);

/**
 * Add/update push constants for execution.
 */
పూర్ణాంకం ff_vk_shader_కూడు_నెట్టు_const(FFVulkanShader *shd, పూర్ణాంకం స్థానభ్రంశం, పూర్ణాంకం కొలత,
                                Vk_Shader_Stage_Flag_బిట్లు stage);

/**
 * Add descriptor to a shader. Must be called before shader init.
 */
శూన్య ff_vk_shader_కూడు_descriptor_సమితి(FFVulkanContext *s, FFVulkanShader *shd,
                                     స్థిరరాశి FFVulkan_Descriptor_సమితి_Binding *desc, పూర్ణాంకం nb,
                                     పూర్ణాంకం singular);

/**
 * Register a shader with an exec pool.
 * Pool may be NULL if all descriptor sets are read-only.
 */
పూర్ణాంకం ff_vk_shader_రిజిస్టరు_exec(FFVulkanContext *s, FFVkExecPool *pool,
                               FFVulkanShader *shd);

/**
 * Bind a shader.
 */
శూన్య ff_vk_exec_bind_shader(FFVulkanContext *s, FFVkExecContext *e,
                            స్థిరరాశి FFVulkanShader *shd);

/**
 * Update push constant in a shader.
 * Must be called before binding the shader.
 */
శూన్య ff_vk_shader_update_నెట్టు_const(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    Vk_Shader_Stage_Flag_బిట్లు stage,
                                    పూర్ణాంకం స్థానభ్రంశం, size_t కొలత, శూన్య *src);

/**
 * Update a descriptor in a buffer with a buffer.
 * Must be called before binding the shader.
 */
పూర్ణాంకం ff_vk_shader_update_desc_బఫరు(FFVulkanContext *s, FFVkExecContext *e,
                                    FFVulkanShader *shd,
                                    పూర్ణాంకం సమితి, పూర్ణాంకం bind, పూర్ణాంకం elem,
                                    FFVk_బఫరు *buf, Vk_Device_కొలత స్థానభ్రంశం, Vk_Device_కొలత len,
                                    VkFormat fmt);

/**
 * Sets an image descriptor for specified shader and binding.
 */
పూర్ణాంకం ff_vk_shader_update_img(FFVulkanContext *s, FFVkExecContext *e,
                            FFVulkanShader *shd, పూర్ణాంకం సమితి, పూర్ణాంకం bind, పూర్ణాంకం offs,
                            VkImageView view, VkImageLayout layout,
                            VkSampler sampler);

/**
 * Update a descriptor in a buffer with an image array..
 * Must be called before binding the shader.
 */
శూన్య ff_vk_shader_update_img_array(FFVulkanContext *s, FFVkExecContext *e,
                                   FFVulkanShader *shd, AVFrame *f,
                                   VkImageView *views, పూర్ణాంకం సమితి, పూర్ణాంకం binding,
                                   VkImageLayout layout, VkSampler sampler);

/**
 * Free a shader.
 */
శూన్య ff_vk_shader_free(FFVulkanContext *s, FFVulkanShader *shd);

/**
 * Frees main context.
 */
శూన్య ff_vk_uninit(FFVulkanContext *s);

#అయితే_ముగింపు /* AVUTIL_VULKAN_H */
