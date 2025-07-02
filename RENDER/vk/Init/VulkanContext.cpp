#include "VulkanContext.h"

void Vulkan::VulkanContext::init(Display* display, Window windowHandel, int width, int height) noexcept {
    m_width = width;
    m_height = height;
    m_instance.createInstance();
    m_instance.setupDebugMessenger();
    m_surface.createSurface(m_instance.GetInstance(), display, windowHandel);
    m_device.pickPhysicalDevice(m_instance.GetInstance(), m_surface.GetSurfaceKHR());
    m_device.createLogicalDevice(m_surface.GetSurfaceKHR());
    m_swapChain.createSwapChain(m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR(), width, height);
    m_swapChain.createImageViews(m_device.GetDevice());
    m_randerPass.createRenderPass(m_device.GetDevice(), m_swapChain.GetSwapChainImageFormat());
    m_pipeline.createGraphicsPipeline(m_device.GetDevice(), m_randerPass.GetRenderPass());
    m_franeBuffer.createFramebuffers(m_device.GetDevice(), m_swapChain.GetSwapChainImageViews(), m_randerPass.GetRenderPass(), m_swapChain.GetExtent2D().width, m_swapChain.GetExtent2D().height);
    m_command.createCommandPool(m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR());
    m_mesh.createVertexBuffer(m_device.GetDevice());
    m_command.createCommandBuffer(m_device.GetDevice());
    m_sync.createSyncObjects(m_device.GetDevice());
}

void Vulkan::VulkanContext::cleanup() noexcept {
    cleanupSwapChain();

    vkDestroyBuffer(m_device.GetDevice(), m_mesh.GetVertexBuffer(), nullptr);

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(m_device.GetDevice(), m_sync.GetRenderFinishedSemaphore()[i], nullptr);
        vkDestroySemaphore(m_device.GetDevice(), m_sync.GetImageAvailableSemaphore()[i], nullptr);
        vkDestroyFence(m_device.GetDevice(), m_sync.GetFlightFence()[i], nullptr);
    }

    vkDestroyCommandPool(m_device.GetDevice(), m_command.GetCommandPool(), nullptr);

    vkDestroyPipeline(m_device.GetDevice(), m_pipeline.GetGraphicsPipeline(), nullptr);
    vkDestroyPipelineLayout(m_device.GetDevice(), m_pipeline.GetPipelineLayout(), nullptr);
    vkDestroyRenderPass(m_device.GetDevice(), m_randerPass.GetRenderPass(), nullptr);

    vkDestroyDevice(m_device.GetDevice(), nullptr);

    m_surface.DestroySurfaceKHR(m_instance.GetInstance());
    m_instance.DestroyInstance();
}

void Vulkan::VulkanContext::recreateSwapChain() noexcept {
    vkDeviceWaitIdle(m_device.GetDevice());
    m_swapChain.createSwapChain(m_device.GetDevice(), m_device.GetPhysicalDevice(), m_surface.GetSurfaceKHR(), m_width, m_height);
    m_swapChain.createImageViews(m_device.GetDevice());
    m_franeBuffer.createFramebuffers(m_device.GetDevice(), m_swapChain.GetSwapChainImageViews(), m_randerPass.GetRenderPass(), m_swapChain.GetExtent2D().width, m_swapChain.GetExtent2D().height);
}

void Vulkan::VulkanContext::cleanupSwapChain() noexcept {
    for (auto framebuffer : m_franeBuffer.GetSwapChainFrameBuffers()) {
        vkDestroyFramebuffer(m_device.GetDevice(), framebuffer, nullptr);
    }
    for (auto imageView : m_swapChain.GetSwapChainImageViews()) {
        vkDestroyImageView(m_device.GetDevice(), imageView, nullptr);
    }

    vkDestroySwapchainKHR(m_device.GetDevice(), m_swapChain.GetSwapChain(), nullptr);
}
