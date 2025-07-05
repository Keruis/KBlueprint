/*
 * File:    VulkanContext.cpp
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   VulkanContext 类的具体实现。
 *
 * Description:
 *   Implements the VulkanContext class, which manages the entire
 *   Vulkan rendering setup and lifecycle, including initialization,
 *   cleanup, and swapchain recreation.
 *
 *   本文件实现了 VulkanContext 类的各个函数，用于管理 Vulkan 的初始化、
 *   渲染流程、资源释放与交换链重建等逻辑，是渲染核心上下文的关键组件。
 *
 * License: MIT License
 */


#include "VulkanContext.h"

void Vulkan::VulkanContext::init
        (Display* display, Window windowHandel, int width, int height)
noexcept
{
    m_width  = width;
    m_height = height;

    m_instance      .createInstance             ();
    m_instance      .setupDebugMessenger        ();

    m_surface       .createSurface              (m_instance.GetInstance(), display, windowHandel);

    m_device        .pickPhysicalDevice         (m_instance.GetInstance(), m_surface.GetSurfaceKHR());
    m_device        .createLogicalDevice        (m_surface.GetSurfaceKHR());

    m_swapChain     .createSwapChain            (m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR(), width, height);
    m_swapChain     .createImageViews           (m_device.GetDevice());

    m_randerPass    .createRenderPass           (m_device.GetDevice(), m_swapChain.GetSwapChainImageFormat());

    m_pipeline      .createDescriptorSetLayout  (m_device.GetDevice());
    m_pipeline      .createGraphicsPipeline     (m_device.GetDevice(), m_randerPass.GetRenderPass());

    m_franeBuffer   .createFramebuffers         (m_device.GetDevice(), m_swapChain.GetSwapChainImageViews(), m_randerPass.GetRenderPass(), m_swapChain.GetExtent2D().width, m_swapChain.GetExtent2D().height);

    m_command       .createCommandPool          (m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR());

    m_mesh          .resize                     (2);
    m_mesh[0].vertices = {
            {{-0.2f, -0.2f}, {1.0f, 0.0f, 0.0f}},
            {{0.2f, -0.2f}, {0.0f, 1.0f, 0.0f}},
            {{0.2f, 0.2f}, {0.0f, 0.0f, 1.0f}},
            {{-0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}}
    };
    m_mesh[1].vertices = {
            {{-0.2f - 0.5f, -0.2f}, {1.0f, 0.0f, 0.0f}},
            {{0.2f - 0.5f, -0.2f}, {0.0f, 1.0f, 0.0f}},
            {{0.2f - 0.5f, 0.2f}, {0.0f, 0.0f, 1.0f}},
            {{-0.2f - 0.5f, 0.2f}, {1.0f, 1.0f, 1.0f}}
    };
    std::vector<std::vector<VkBuffer>> tmp(2);
    for (uint32_t i = 0; i < 2; i++) {
        m_mesh[i]   .createVertexBuffer         (m_device.GetDevice(), m_device.GetPhysicalDevice(), m_device.GetGraphicsQueue(), m_command.GetCommandPool());
        m_mesh[i]   .createIndexBuffer          (m_device.GetDevice(), m_device.GetPhysicalDevice(), m_device.GetGraphicsQueue(), m_command.GetCommandPool());
        m_mesh[i]   .createUniformBuffers       (m_device.GetDevice(), m_device.GetPhysicalDevice());
        tmp[i] = m_mesh[i]
                .GetUniformBuffers              ();
    }
    m_pipeline      .createDescriptorPool       (m_device.GetDevice());
    m_pipeline      .createDescriptorSets       (m_device.GetDevice(), tmp);
    m_command       .createCommandBuffer        (m_device.GetDevice());
    m_sync          .createSyncObjects          (m_device.GetDevice());
}

void Vulkan::VulkanContext::cleanup
        ()
noexcept
{
    cleanupSwapChain                            ();

    vkDestroyDescriptorPool                     (m_device.GetDevice(), m_pipeline.GetDescriptorPool(), nullptr);
    vkDestroyDescriptorSetLayout                (m_device.GetDevice(), m_pipeline.GetVkDescriptorSetLayout(), nullptr);

    for (uint32_t i = 0; i < 2; i++) {
        m_mesh[i]   .cleanup                    (m_device.GetDevice());
    }

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore                      (m_device.GetDevice(), m_sync.GetRenderFinishedSemaphore()[i], nullptr);
        vkDestroySemaphore                      (m_device.GetDevice(), m_sync.GetImageAvailableSemaphore()[i], nullptr);
        vkDestroyFence                          (m_device.GetDevice(), m_sync.GetFlightFence()[i], nullptr);
    }

    vkDestroyCommandPool                        (m_device.GetDevice(), m_command.GetCommandPool(), nullptr);

    vkDestroyPipeline                           (m_device.GetDevice(), m_pipeline.GetGraphicsPipeline(), nullptr);
    vkDestroyPipelineLayout                     (m_device.GetDevice(), m_pipeline.GetPipelineLayout(), nullptr);
    vkDestroyRenderPass                         (m_device.GetDevice(), m_randerPass.GetRenderPass(), nullptr);

    vkDestroyDevice                             (m_device.GetDevice(), nullptr);

    m_surface       .DestroySurfaceKHR          (m_instance.GetInstance());
    m_instance      .DestroyInstance            ();
}

void Vulkan::VulkanContext::recreateSwapChain
        ()
noexcept
{
    vkDeviceWaitIdle                            (m_device.GetDevice());
    m_swapChain     .createSwapChain            (m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR(), m_width, m_height);
    m_swapChain     .createImageViews           (m_device.GetDevice());
    m_franeBuffer   .createFramebuffers         (m_device.GetDevice(), m_swapChain.GetSwapChainImageViews(), m_randerPass.GetRenderPass(), m_swapChain.GetExtent2D().width, m_swapChain.GetExtent2D().height);
}

void Vulkan::VulkanContext::cleanupSwapChain
        ()
noexcept
{
    for (auto framebuffer : m_franeBuffer.GetSwapChainFrameBuffers()) {
        vkDestroyFramebuffer                    (m_device.GetDevice(), framebuffer, nullptr);
    }
    for (auto imageView : m_swapChain.GetSwapChainImageViews()) {
        vkDestroyImageView                      (m_device.GetDevice(), imageView, nullptr);
    }

    vkDestroySwapchainKHR                       (m_device.GetDevice(), m_swapChain.GetSwapChain(), nullptr);
}
