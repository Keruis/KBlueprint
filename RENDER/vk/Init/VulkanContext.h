#ifndef BLUEPRINT_VULKANCONTEXT_H
#define BLUEPRINT_VULKANCONTEXT_H

#include <X11/Xlib.h>

#include "config.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanRenderPass.h"
#include "VulkanPipeline.h"
#include "VulkanFramebuffer.h"
#include "VulkanCommand.h"
#include "VulkanSync.h"

#include "../Model/Mesh.h"

namespace Vulkan {
    class VulkanContext {
    public:
        void init(Display* display, Window windowHandel, int width, int height) noexcept;
        void cleanup() noexcept;

        [[nodiscard]] VkDevice getDevice() noexcept {return m_device.GetDevice();};
        [[nodiscard]] const VkQueue& getGraphicsQueue() const noexcept {return m_device.GetGraphicsQueue();};
        [[nodiscard]] const VkQueue& getPresentQueue() const noexcept {return m_device.GetPresentQueue();};
        [[nodiscard]] std::vector<VkFence>& getFlightFence() noexcept {return m_sync.GetFlightFence();};
        [[nodiscard]] std::vector<VkSemaphore>& getImageAvailableSemaphore() noexcept {return m_sync.GetImageAvailableSemaphore();};
        [[nodiscard]] std::vector<VkSemaphore>& getRenderFinishedSemaphore() noexcept {return m_sync.GetRenderFinishedSemaphore();};
        [[nodiscard]] VkSwapchainKHR getSwapChain() noexcept {return m_swapChain.GetSwapChain();};
        [[nodiscard]] VkExtent2D getExtent2D() noexcept {return m_swapChain.GetExtent2D();};
        [[nodiscard]] std::vector<VkCommandBuffer>& getCommandBuffer() noexcept {return m_command.GetCommandBuffer();};
        [[nodiscard]] VkRenderPass getRenderPass() noexcept {return m_randerPass.GetRenderPass();};
        [[nodiscard]] std::vector<VkFramebuffer>& getSwapChainFrameBuffers() noexcept {return m_franeBuffer.GetSwapChainFrameBuffers();};
        [[nodiscard]] VkPipeline getGraphicsPipeline() noexcept {return m_pipeline.GetGraphicsPipeline();};

        void recreateSwapChain() noexcept;
        void cleanupSwapChain() noexcept;

    private:
        uint32_t m_width = 0;
        uint32_t m_height = 0;

        Vulkan::Init::VulkanInstance m_instance;
        Vulkan::Init::VulkanSurface m_surface;
        Vulkan::Init::VulkanDevice m_device;
        Vulkan::Init::VulkanSwapChain m_swapChain;
        Vulkan::Init::VulkanRenderPass m_randerPass;
        Vulkan::Init::VulkanPipeline m_pipeline;
        Vulkan::Init::VulkanFramebuffer m_franeBuffer;
        Vulkan::Init::VulkanCommand m_command;
        Vulkan::Init::VulkanSync m_sync;

        Mesh m_mesh;
    };
}

#endif //BLUEPRINT_VULKANCONTEXT_H
