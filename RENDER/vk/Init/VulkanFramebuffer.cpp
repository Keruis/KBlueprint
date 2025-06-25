#include "VulkanFramebuffer.h"

Vulkan::Init::VulkanFramebuffer::VulkanFramebuffer() {

}

void Vulkan::Init::VulkanFramebuffer::Initialize() noexcept {

}

void Vulkan::Init::VulkanFramebuffer::createFramebuffers(VkDevice device, std::vector<VkImageView>& swapChainImageView, VkRenderPass renderPass, int width, int height) {
    swapChainFramebuffers.resize(swapChainImageView.size());

    for (size_t i = 0; i < swapChainImageView.size(); i++) {
        VkImageView attachments[] = {
                swapChainImageView[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = width;
        framebufferInfo.height = height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

std::vector<VkFramebuffer> &Vulkan::Init::VulkanFramebuffer::GetSwapChainFrameBuffers() noexcept {
    return swapChainFramebuffers;
}