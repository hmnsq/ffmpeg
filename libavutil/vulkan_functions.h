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

#यदि_अपरिभाषितम् AVUTIL_VULKAN_FUNCTIONS_H
#परिभाषय AVUTIL_VULKAN_FUNCTIONS_H

#परिभाषय VK_NO_PROTOTYPES
#परिभाषय VK_ENABLE_BETA_EXTENSIONS

#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_vulkan.h"

/* An enum of bitflags for every optional extension we need */
प्रकारनिर्देश uint64_t FFVulkanExtensions;

/* NOTE: when adding new entries, make sure to update ff_vk_extensions_to_mask */
#परिभाषय FF_VK_EXT_EXTERNAL_DMABUF_स्मृतिः (1ULL <<  0) /* VK_EXT_external_memory_dma_buf */
#परिभाषय FF_VK_EXT_DRM_MODIFIER_FLAGS     (1ULL <<  1) /* VK_EXT_image_drm_format_modifier */
#परिभाषय FF_VK_EXT_EXTERNAL_FD_स्मृतिः     (1ULL <<  2) /* VK_KHR_external_memory_fd */
#परिभाषय FF_VK_EXT_EXTERNAL_FD_SEM        (1ULL <<  3) /* VK_KHR_external_semaphore_fd */
#परिभाषय FF_VK_EXT_EXTERNAL_HOST_स्मृतिः   (1ULL <<  4) /* VK_EXT_external_memory_host */
#परिभाषय FF_VK_EXT_DEBUG_UTILS            (1ULL <<  5) /* VK_EXT_debug_utils */

#परिभाषय FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः  (1ULL <<  6) /* VK_KHR_external_memory_win32 */
#परिभाषय FF_VK_EXT_EXTERNAL_WIN32_SEM     (1ULL <<  7) /* VK_KHR_external_semaphore_win32 */

#परिभाषय FF_VK_EXT_DEVICE_DRM             (1ULL <<  9) /* VK_EXT_physical_device_drm */
#परिभाषय FF_VK_EXT_ATOMIC_FLOAT           (1ULL << 10) /* VK_EXT_shader_atomic_float */
#परिभाषय FF_VK_EXT_COOP_MATRIX            (1ULL << 11) /* VK_KHR_cooperative_matrix */
#परिभाषय FF_VK_EXT_OPTICAL_FLOW           (1ULL << 12) /* VK_NV_optical_flow */
#परिभाषय FF_VK_EXT_SHADER_OBJECT          (1ULL << 13) /* VK_EXT_shader_object */
#परिभाषय FF_VK_EXT_प्रक्षिप_DESCRIPTOR        (1ULL << 14) /* VK_KHR_push_descriptor */
#परिभाषय FF_VK_EXT_RELAXED_EXTENDED_INSTR (1ULL << 15) /* VK_KHR_shader_relaxed_extended_instruction */
#परिभाषय FF_VK_EXT_EXPECT_ASSUME          (1ULL << 16) /* VK_KHR_shader_expect_assume */
#परिभाषय FF_VK_EXT_SUBGROUP_ROTATE        (1ULL << 17) /* VK_KHR_shader_subgroup_rotate */
#परिभाषय FF_VK_EXT_HOST_IMAGE_COPY        (1ULL << 18) /* VK_EXT_host_image_copy */
#परिभाषय FF_VK_EXT_ZERO_INITIALIZE        (1ULL << 19) /* VK_EXT_zero_initialize_device_memory */
#परिभाषय FF_VK_EXT_EXPLICIT_MEM_LAYOUT    (1ULL << 20) /* VK_KHR_workgroup_memory_explicit_layout */
#परिभाषय FF_VK_EXT_REPLICATED_COMPOSITES  (1ULL << 21) /* VK_EXT_shader_replicated_composites */
#परिभाषय FF_VK_EXT_LONG_सदिशम्            (1ULL << 22) /* VK_EXT_shader_long_vector */
#परिभाषय FF_VK_EXT_आन्तरिकम्_QUEUE_SYNC    (1ULL << 23) /* VK_KHR_internally_synchronized_queues */
#परिभाषय FF_VK_EXT_MAXIMAL_RECONVERGENCE  (1ULL << 24) /* VK_KHR_shader_maximal_reconvergence */
#परिभाषय FF_VK_EXT_MAINTENANCE_9          (1ULL << 25) /* VK_KHR_maintenance9 */
#परिभाषय FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  (1ULL << 26) /* VK_KHR_unified_image_layouts */
#परिभाषय FF_VK_EXT_MAINTENANCE_11         (1ULL << 27) /* VK_KHR_maintenance11 */

/* Video extensions */
#परिभाषय FF_VK_EXT_VIDEO_QUEUE            (1ULL << 36) /* VK_KHR_video_queue */
#परिभाषय FF_VK_EXT_VIDEO_MAINTENANCE_1    (1ULL << 37) /* VK_KHR_video_maintenance1 */
#परिभाषय FF_VK_EXT_VIDEO_MAINTENANCE_2    (1ULL << 38) /* VK_KHR_video_maintenance2 */

#परिभाषय FF_VK_EXT_VIDEO_DECODE_QUEUE     (1ULL << 40) /* VK_KHR_video_decode_queue */
#परिभाषय FF_VK_EXT_VIDEO_DECODE_H264      (1ULL << 41) /* VK_KHR_video_decode_h264 */
#परिभाषय FF_VK_EXT_VIDEO_DECODE_H265      (1ULL << 42) /* VK_KHR_video_decode_h265 */
#परिभाषय FF_VK_EXT_VIDEO_DECODE_VP9       (1ULL << 43) /* VK_KHR_video_decode_vp9 */
#परिभाषय FF_VK_EXT_VIDEO_DECODE_AV1       (1ULL << 44) /* VK_KHR_video_decode_av1 */

#परिभाषय FF_VK_EXT_VIDEO_ENCODE_QUEUE     (1ULL << 50) /* VK_KHR_video_encode_queue */
#परिभाषय FF_VK_EXT_VIDEO_ENCODE_H264      (1ULL << 51) /* VK_KHR_video_encode_h264 */
#परिभाषय FF_VK_EXT_VIDEO_ENCODE_H265      (1ULL << 52) /* VK_KHR_video_encode_h265 */
#परिभाषय FF_VK_EXT_VIDEO_ENCODE_AV1       (1ULL << 53) /* VK_KHR_video_encode_av1 */

#परिभाषय FF_VK_EXT_PORTABILITY_SUBSET     (1ULL << 62)
#परिभाषय FF_VK_EXT_NO_FLAG                (1ULL << 63)

/* Macro containing every function that we utilize in our codebase */
#परिभाषय FN_LIST(MACRO)                                                                   \
    /* Instance */                                                                       \
    MACRO(0, 0, FF_VK_EXT_NO_FLAG,              EnumerateInstanceExtensionProperties)    \
    MACRO(0, 0, FF_VK_EXT_NO_FLAG,              EnumerateInstanceLayerProperties)        \
    MACRO(0, 0, FF_VK_EXT_NO_FLAG,              CreateInstance)                          \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DestroyInstance)                         \
                                                                                         \
    /* Debug */                                                                          \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              CreateDebugUtilsMessengerEXT)            \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DestroyDebugUtilsMessengerEXT)           \
                                                                                         \
    /* Device */                                                                         \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetDeviceProcAddr)                       \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              CreateDevice)                            \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceFeatures2)              \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceProperties)             \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceExternalSemaphoreProperties)          \
    MACRO(1, 0, FF_VK_EXT_VIDEO_QUEUE,          GetPhysicalDeviceVideoCapabilitiesKHR)     \
    MACRO(1, 0, FF_VK_EXT_VIDEO_QUEUE,          GetPhysicalDeviceVideoFormatPropertiesKHR) \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DeviceWaitIdle)                          \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DestroyDevice)                           \
                                                                                         \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              EnumeratePhysicalDevices)                \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              EnumerateDeviceExtensionProperties)      \
                                                                                         \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceProperties2)            \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              Get_Physical_Device_स्मृतिः_Properties)       \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceFormatProperties2)      \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceImageFormatProperties2) \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceQueueFamilyProperties)  \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceQueueFamilyProperties2) \
    MACRO(1, 0, FF_VK_EXT_COOP_MATRIX,          GetPhysicalDeviceCooperativeMatrixPropertiesKHR) \
                                                                                         \
    /* Command pool */                                                                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateCommandPool)                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyCommandPool)                      \
                                                                                         \
    /* Command buffer */                                                                 \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              AllocateCommandBuffers)                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Begin_Command_बफर)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              अन्तः_Command_बफर)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Reset_Command_बफर)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              FreeCommandBuffers)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdDispatch)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Dispatch_आधारः)                                       \
                                                                                         \
    /* Queue */                                                                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              GetDeviceQueue2)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              QueueSubmit)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              QueueSubmit2)                              \
                                                                                         \
    /* Semaphores */                                                                     \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_SEM,      GetSemaphoreFdKHR)                       \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_SEM,      ImportSemaphoreFdKHR)                                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateSemaphore)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              WaitSemaphores)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              SignalSemaphore)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Semaphore_गणक_मानम्)                \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroySemaphore)                        \
                                                                                         \
    /*स्मृतिः*/                                                                         \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_स्मृतिः,   Get_स्मृतिः_Fd_KHR)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_स्मृतिः_Fd_Properties_KHR)                \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_HOST_स्मृतिः, Get_स्मृतिः_Host_Pointer_Properties_EXT)       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Allocate_स्मृतिः)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Map_स्मृतिः)                               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Flush_Mapped_स्मृतिः_Ranges)                 \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Invalidate_Mapped_स्मृतिः_Ranges)            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Unmap_स्मृतिः)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Free_स्मृतिः)                              \
                                                                                         \
    /* Commands */                                                                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBindDescriptorSets)                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_प्रक्षिप_Constants)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBindPipeline)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdPipelineBarrier)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_बफर_गन्तव्यम्_Image)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_Image_गन्तव्यम्_बफर)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdCopyImage)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdClearColorImage)                                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_बफर)                                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Update_बफर)                                       \
                                                                                         \
    /*बफर*/                                                                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_बफर_स्मृतिः_Requirements2)            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Create_बफर)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Bind_बफर_स्मृतिः)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_बफर_Device_स्थानाङ्कः)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Fill_बफर)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Destroy_बफर)                           \
                                                                                         \
    /* Image */                                                                          \
    MACRO(1, 1, FF_VK_EXT_DRM_MODIFIER_FLAGS,   GetImageDrmFormatModifierPropertiesEXT)  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Image_स्मृतिः_Requirements2)             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Device_Image_स्मृतिः_Requirements)        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateImage)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              BindImageMemory2)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              GetImageSubresourceLayout)               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyImage)                            \
                                                                                         \
    /* ImageView */                                                                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateImageView)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyImageView)                        \
                                                                                         \
    /* DescriptorSet */                                                                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Create_Descriptor_समुच्चयः_Layout)               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              AllocateDescriptorSets)                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateDescriptorPool)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyDescriptorPool)                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Destroy_Descriptor_समुच्चयः_Layout)              \
                                                                                         \
    /* DescriptorUpdateTemplate */                                                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Update_Descriptor_समुच्चयः_With_Template)         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateDescriptorUpdateTemplate)          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyDescriptorUpdateTemplate)         \
                                                                                                       \
    /* Descriptors */                                                                                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              UpdateDescriptorSets)                                  \
    MACRO(1, 1, FF_VK_EXT_प्रक्षिप_DESCRIPTOR,      Cmd_प्रक्षिप_Descriptor_समुच्चयः_KHR)                               \
                                                                                           \
    /* Queries */                                                                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateQueryPool)                           \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              GetQueryPoolResults)                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              ResetQueryPool)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBeginQuery)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_अन्तः_Query)                               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdResetQueryPool)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyQueryPool)                          \
                                                                                           \
    /* sync2 */                                                                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdPipelineBarrier2)                       \
                                                                                           \
    /* Host image copy */                                                                              \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      TransitionImageLayoutEXT)                              \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      Copy_स्मृतिः_गन्तव्यम्_Image_EXT)                                  \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      Copy_Image_गन्तव्यम्_स्मृतिः_EXT)                                  \
                                                                                                       \
    /* Video queue */                                                                      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          CreateVideoSessionKHR)                     \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          CreateVideoSessionParametersKHR)           \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          Get_Video_Session_स्मृतिः_Requirements_KHR)      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          Bind_Video_Session_स्मृतिः_KHR)                 \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          CmdBeginVideoCodingKHR)                    \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          CmdControlVideoCodingKHR)                  \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          Cmd_अन्तः_Video_Coding_KHR)                      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          DestroyVideoSessionParametersKHR)          \
    MACRO(1, 1, FF_VK_EXT_VIDEO_QUEUE,          DestroyVideoSessionKHR)                    \
                                                                                           \
    /* Video decoding */                                                                   \
    MACRO(1, 1, FF_VK_EXT_VIDEO_DECODE_QUEUE,   CmdDecodeVideoKHR)                         \
                                                                                           \
    /* Video encoding */                                                                   \
    MACRO(1, 1, FF_VK_EXT_VIDEO_ENCODE_QUEUE,   CmdEncodeVideoKHR)                         \
    MACRO(1, 1, FF_VK_EXT_VIDEO_ENCODE_QUEUE,   GetEncodedVideoSessionParametersKHR)       \
    MACRO(1, 0, FF_VK_EXT_VIDEO_ENCODE_QUEUE,   GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR) \
                                                                                         \
    /* Pipeline */                                                                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreatePipelineLayout)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyPipelineLayout)                   \
                                                                                         \
    /* PipelineLayout */                                                                 \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateComputePipelines)                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyPipeline)                         \
                                                                                         \
    /* Sampler */                                                                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateSamplerYcbcrConversion)              \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroySamplerYcbcrConversion)             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateSampler)                           \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroySampler)                          \
                                                                                           \
    /* Optical flow */                                                                     \
    MACRO(1, 1, FF_VK_EXT_OPTICAL_FLOW,         BindOpticalFlowSessionImageNV)             \
    MACRO(1, 1, FF_VK_EXT_OPTICAL_FLOW,         CmdOpticalFlowExecuteNV)                   \
    MACRO(1, 1, FF_VK_EXT_OPTICAL_FLOW,         CreateOpticalFlowSessionNV)                \
    MACRO(1, 1, FF_VK_EXT_OPTICAL_FLOW,         DestroyOpticalFlowSessionNV)               \
    MACRO(1, 0, FF_VK_EXT_OPTICAL_FLOW,         GetPhysicalDeviceOpticalFlowImageFormatsNV)\
                                                                                         \
    /* Shaders */                                                                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateShaderModule)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyShaderModule)                       \
    MACRO(1, 1, FF_VK_EXT_SHADER_OBJECT,        CmdBindShadersEXT)                         \
    MACRO(1, 1, FF_VK_EXT_SHADER_OBJECT,        CreateShadersEXT)                          \
    MACRO(1, 1, FF_VK_EXT_SHADER_OBJECT,        DestroyShaderEXT)                          \
    MACRO(1, 1, FF_VK_EXT_SHADER_OBJECT,        Get_Shader_द्विमान_दत्त_EXT)

/* Macro containing every win32 specific function that we utilize in our codebase */
#परिभाषय FN_LIST_WIN32(MACRO)                                                             \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_WIN32_SEM,    GetSemaphoreWin32HandleKHR)             \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_WIN32_स्मृतिः, Get_स्मृतिः_Win32_Handle_KHR)

/* Macro to turn a function name into a definition */
#परिभाषय PFN_DEF(req_inst, req_dev, ext_flag, name) \
    PFN_vk##name name;

/* Structure with the definition of all listed functions */
प्रकारनिर्देश संरचना FFVulkanFunctions {
    FN_LIST(PFN_DEF)
#यदि_परिभाषितम् _WIN32
    FN_LIST_WIN32(PFN_DEF)
#यदि_अन्तः
} FFVulkanFunctions;

#यदि_अन्तः /* AVUTIL_VULKAN_FUNCTIONS_H */
