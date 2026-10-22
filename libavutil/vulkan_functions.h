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

#اگر_غیر_تعریف_شدہ AVUTIL_VULKAN_FUNCTIONS_H
#تعریف_کرو AVUTIL_VULKAN_FUNCTIONS_H

#تعریف_کرو VK_NO_PROTOTYPES
#تعریف_کرو VK_ENABLE_BETA_EXTENSIONS

#شامل "hwcontext.h"
#شامل "hwcontext_vulkan.h"

/* An enum of bitflags for every optional extension we need */
قسمتعریف uint64_t FFVulkanExtensions;

/* NOTE: when adding new entries, make sure to update ff_vk_extensions_to_mask */
#تعریف_کرو FF_VK_EXT_EXTERNAL_DMABUF_حافظہ (1ULL <<  0) /* VK_EXT_external_memory_dma_buf */
#تعریف_کرو FF_VK_EXT_DRM_MODIFIER_FLAGS     (1ULL <<  1) /* VK_EXT_image_drm_format_modifier */
#تعریف_کرو FF_VK_EXT_EXTERNAL_FD_حافظہ     (1ULL <<  2) /* VK_KHR_external_memory_fd */
#تعریف_کرو FF_VK_EXT_EXTERNAL_FD_SEM        (1ULL <<  3) /* VK_KHR_external_semaphore_fd */
#تعریف_کرو FF_VK_EXT_EXTERNAL_HOST_حافظہ   (1ULL <<  4) /* VK_EXT_external_memory_host */
#تعریف_کرو FF_VK_EXT_DEBUG_UTILS            (1ULL <<  5) /* VK_EXT_debug_utils */

#تعریف_کرو FF_VK_EXT_EXTERNAL_WIN32_حافظہ  (1ULL <<  6) /* VK_KHR_external_memory_win32 */
#تعریف_کرو FF_VK_EXT_EXTERNAL_WIN32_SEM     (1ULL <<  7) /* VK_KHR_external_semaphore_win32 */

#تعریف_کرو FF_VK_EXT_DEVICE_DRM             (1ULL <<  9) /* VK_EXT_physical_device_drm */
#تعریف_کرو FF_VK_EXT_ATOMIC_FLOAT           (1ULL << 10) /* VK_EXT_shader_atomic_float */
#تعریف_کرو FF_VK_EXT_COOP_میٹرکس            (1ULL << 11) /* VK_KHR_cooperative_matrix */
#تعریف_کرو FF_VK_EXT_OPTICAL_FLOW           (1ULL << 12) /* VK_NV_optical_flow */
#تعریف_کرو FF_VK_EXT_SHADER_OBJECT          (1ULL << 13) /* VK_EXT_shader_object */
#تعریف_کرو FF_VK_EXT_ڈالو_DESCRIPTOR        (1ULL << 14) /* VK_KHR_push_descriptor */
#تعریف_کرو FF_VK_EXT_RELAXED_EXTENDED_INSTR (1ULL << 15) /* VK_KHR_shader_relaxed_extended_instruction */
#تعریف_کرو FF_VK_EXT_EXPECT_ASSUME          (1ULL << 16) /* VK_KHR_shader_expect_assume */
#تعریف_کرو FF_VK_EXT_SUBGROUP_ROTATE        (1ULL << 17) /* VK_KHR_shader_subgroup_rotate */
#تعریف_کرو FF_VK_EXT_HOST_IMAGE_COPY        (1ULL << 18) /* VK_EXT_host_image_copy */
#تعریف_کرو FF_VK_EXT_ZERO_INITIALIZE        (1ULL << 19) /* VK_EXT_zero_initialize_device_memory */
#تعریف_کرو FF_VK_EXT_EXPLICIT_MEM_LAYOUT    (1ULL << 20) /* VK_KHR_workgroup_memory_explicit_layout */
#تعریف_کرو FF_VK_EXT_REPLICATED_COMPOSITES  (1ULL << 21) /* VK_EXT_shader_replicated_composites */
#تعریف_کرو FF_VK_EXT_LONG_سمتیہ            (1ULL << 22) /* VK_EXT_shader_long_vector */
#تعریف_کرو FF_VK_EXT_اندرونی_قطار_SYNC    (1ULL << 23) /* VK_KHR_internally_synchronized_queues */
#تعریف_کرو FF_VK_EXT_MAXIMAL_RECONVERGENCE  (1ULL << 24) /* VK_KHR_shader_maximal_reconvergence */
#تعریف_کرو FF_VK_EXT_MAINTENANCE_9          (1ULL << 25) /* VK_KHR_maintenance9 */
#تعریف_کرو FF_VK_EXT_UNIFIED_IMAGE_LAYOUTS  (1ULL << 26) /* VK_KHR_unified_image_layouts */
#تعریف_کرو FF_VK_EXT_MAINTENANCE_11         (1ULL << 27) /* VK_KHR_maintenance11 */

/* Video extensions */
#تعریف_کرو FF_VK_EXT_VIDEO_قطار            (1ULL << 36) /* VK_KHR_video_queue */
#تعریف_کرو FF_VK_EXT_VIDEO_MAINTENANCE_1    (1ULL << 37) /* VK_KHR_video_maintenance1 */
#تعریف_کرو FF_VK_EXT_VIDEO_MAINTENANCE_2    (1ULL << 38) /* VK_KHR_video_maintenance2 */

#تعریف_کرو FF_VK_EXT_VIDEO_DECODE_قطار     (1ULL << 40) /* VK_KHR_video_decode_queue */
#تعریف_کرو FF_VK_EXT_VIDEO_DECODE_H264      (1ULL << 41) /* VK_KHR_video_decode_h264 */
#تعریف_کرو FF_VK_EXT_VIDEO_DECODE_H265      (1ULL << 42) /* VK_KHR_video_decode_h265 */
#تعریف_کرو FF_VK_EXT_VIDEO_DECODE_VP9       (1ULL << 43) /* VK_KHR_video_decode_vp9 */
#تعریف_کرو FF_VK_EXT_VIDEO_DECODE_AV1       (1ULL << 44) /* VK_KHR_video_decode_av1 */

#تعریف_کرو FF_VK_EXT_VIDEO_ENCODE_قطار     (1ULL << 50) /* VK_KHR_video_encode_queue */
#تعریف_کرو FF_VK_EXT_VIDEO_ENCODE_H264      (1ULL << 51) /* VK_KHR_video_encode_h264 */
#تعریف_کرو FF_VK_EXT_VIDEO_ENCODE_H265      (1ULL << 52) /* VK_KHR_video_encode_h265 */
#تعریف_کرو FF_VK_EXT_VIDEO_ENCODE_AV1       (1ULL << 53) /* VK_KHR_video_encode_av1 */

#تعریف_کرو FF_VK_EXT_PORTABILITY_SUBSET     (1ULL << 62)
#تعریف_کرو FF_VK_EXT_NO_FLAG                (1ULL << 63)

/* Macro containing every function that we utilize in our codebase */
#تعریف_کرو FN_LIST(MACRO)                                                                   \
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
    MACRO(1, 0, FF_VK_EXT_VIDEO_قطار,          GetPhysicalDeviceVideoCapabilitiesKHR)     \
    MACRO(1, 0, FF_VK_EXT_VIDEO_قطار,          GetPhysicalDeviceVideoFormatPropertiesKHR) \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DeviceWaitIdle)                          \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              DestroyDevice)                           \
                                                                                         \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              EnumeratePhysicalDevices)                \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              EnumerateDeviceExtensionProperties)      \
                                                                                         \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceProperties2)            \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              Get_Physical_Device_حافظہ_Properties)       \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceFormatProperties2)      \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              GetPhysicalDeviceImageFormatProperties2) \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              Get_Physical_Device_قطار_Family_Properties)  \
    MACRO(1, 0, FF_VK_EXT_NO_FLAG,              Get_Physical_Device_قطار_Family_Properties2) \
    MACRO(1, 0, FF_VK_EXT_COOP_میٹرکس,          Get_Physical_Device_Cooperative_میٹرکس_Properties_KHR) \
                                                                                         \
    /* Command pool */                                                                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateCommandPool)                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyCommandPool)                      \
                                                                                         \
    /* Command buffer */                                                                 \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              AllocateCommandBuffers)                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Begin_Command_بفر)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              انتہا_Command_بفر)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Reset_Command_بفر)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              FreeCommandBuffers)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdDispatch)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Dispatch_بنیاد)                                       \
                                                                                         \
    /*قطار*/                                                                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              GetDeviceQueue2)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              قطار_Submit)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              قطار_Submit2)                              \
                                                                                         \
    /* Semaphores */                                                                     \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_SEM,      GetSemaphoreFdKHR)                       \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_SEM,      ImportSemaphoreFdKHR)                                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateSemaphore)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              WaitSemaphores)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              SignalSemaphore)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Semaphore_شمار_قدر)                \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroySemaphore)                        \
                                                                                         \
    /*حافظہ*/                                                                         \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_FD_حافظہ,   Get_حافظہ_Fd_KHR)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_حافظہ_Fd_Properties_KHR)                \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_HOST_حافظہ, Get_حافظہ_Host_اشارہ_گر_Properties_EXT)       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Allocate_حافظہ)                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Map_حافظہ)                               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Flush_Mapped_حافظہ_Ranges)                 \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Invalidate_Mapped_حافظہ_Ranges)            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Unmap_حافظہ)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Free_حافظہ)                              \
                                                                                         \
    /* Commands */                                                                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBindDescriptorSets)                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_ڈالو_Constants)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBindPipeline)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdPipelineBarrier)                      \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_بفر_مقصد_Image)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_Image_مقصد_بفر)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdCopyImage)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdClearColorImage)                                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Copy_بفر)                                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Update_بفر)                                       \
                                                                                         \
    /*بفر*/                                                                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_بفر_حافظہ_Requirements2)            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Create_بفر)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Bind_بفر_حافظہ)                        \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_بفر_Device_پتہ)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_Fill_بفر)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Destroy_بفر)                           \
                                                                                         \
    /* Image */                                                                          \
    MACRO(1, 1, FF_VK_EXT_DRM_MODIFIER_FLAGS,   GetImageDrmFormatModifierPropertiesEXT)  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Image_حافظہ_Requirements2)             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Get_Device_Image_حافظہ_Requirements)        \
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
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Create_Descriptor_سیٹ_Layout)               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              AllocateDescriptorSets)                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateDescriptorPool)                    \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyDescriptorPool)                   \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Destroy_Descriptor_سیٹ_Layout)              \
                                                                                         \
    /* DescriptorUpdateTemplate */                                                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Update_Descriptor_سیٹ_With_Template)         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateDescriptorUpdateTemplate)          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyDescriptorUpdateTemplate)         \
                                                                                                       \
    /* Descriptors */                                                                                  \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              UpdateDescriptorSets)                                  \
    MACRO(1, 1, FF_VK_EXT_ڈالو_DESCRIPTOR,      Cmd_ڈالو_Descriptor_سیٹ_KHR)                               \
                                                                                           \
    /* Queries */                                                                          \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CreateQueryPool)                           \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              GetQueryPoolResults)                       \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              ResetQueryPool)                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdBeginQuery)                             \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              Cmd_انتہا_Query)                               \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdResetQueryPool)                         \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              DestroyQueryPool)                          \
                                                                                           \
    /* sync2 */                                                                            \
    MACRO(1, 1, FF_VK_EXT_NO_FLAG,              CmdPipelineBarrier2)                       \
                                                                                           \
    /* Host image copy */                                                                              \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      TransitionImageLayoutEXT)                              \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      Copy_حافظہ_مقصد_Image_EXT)                                  \
    MACRO(1, 1, FF_VK_EXT_HOST_IMAGE_COPY,      Copy_Image_مقصد_حافظہ_EXT)                                  \
                                                                                                       \
    /* Video queue */                                                                      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          CreateVideoSessionKHR)                     \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          CreateVideoSessionParametersKHR)           \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          Get_Video_Session_حافظہ_Requirements_KHR)      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          Bind_Video_Session_حافظہ_KHR)                 \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          CmdBeginVideoCodingKHR)                    \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          CmdControlVideoCodingKHR)                  \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          Cmd_انتہا_Video_Coding_KHR)                      \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          DestroyVideoSessionParametersKHR)          \
    MACRO(1, 1, FF_VK_EXT_VIDEO_قطار,          DestroyVideoSessionKHR)                    \
                                                                                           \
    /* Video decoding */                                                                   \
    MACRO(1, 1, FF_VK_EXT_VIDEO_DECODE_قطار,   CmdDecodeVideoKHR)                         \
                                                                                           \
    /* Video encoding */                                                                   \
    MACRO(1, 1, FF_VK_EXT_VIDEO_ENCODE_قطار,   CmdEncodeVideoKHR)                         \
    MACRO(1, 1, FF_VK_EXT_VIDEO_ENCODE_قطار,   GetEncodedVideoSessionParametersKHR)       \
    MACRO(1, 0, FF_VK_EXT_VIDEO_ENCODE_قطار,   GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR) \
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
    MACRO(1, 1, FF_VK_EXT_SHADER_OBJECT,        Get_Shader_ثنائی_ڈیٹا_EXT)

/* Macro containing every win32 specific function that we utilize in our codebase */
#تعریف_کرو FN_LIST_WIN32(MACRO)                                                             \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_WIN32_SEM,    GetSemaphoreWin32HandleKHR)             \
    MACRO(1, 1, FF_VK_EXT_EXTERNAL_WIN32_حافظہ, Get_حافظہ_Win32_Handle_KHR)

/* Macro to turn a function name into a definition */
#تعریف_کرو PFN_DEF(req_inst, req_dev, ext_flag, name) \
    PFN_vk##name name;

/* Structure with the definition of all listed functions */
قسمتعریف ساخت FFVulkanFunctions {
    FN_LIST(PFN_DEF)
#اگر_تعریف_شدہ _WIN32
    FN_LIST_WIN32(PFN_DEF)
#اگر_ختم
} FFVulkanFunctions;

#اگر_ختم /* AVUTIL_VULKAN_FUNCTIONS_H */
