#ifndef BLUEPRINT_VULKANCONTEXT_H
#define BLUEPRINT_VULKANCONTEXT_H

#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanRenderPass.h"
#include "VulkanPipeline.h"
#include "VulkanFramebuffer.h"
#include "VulkanCommand.h"
#include "VulkanSync.h"

class VulkanContext {
public:
    void init() noexcept;
    void cleanup() noexcept;

private:
    VulkanInstance instance;
    VulkanSurface surface;
    VulkanDevice device;
    VulkanSwapchain swapchain;
    VulkanRenderPass renderPass;
    VulkanPipeline pipeline;
    VulkanFramebuffer framebuffer;
    VulkanCommand command;
    VulkanSync sync;
};


#endif //BLUEPRINT_VULKANCONTEXT_H
