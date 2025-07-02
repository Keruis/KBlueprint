#include "VulkanSync.h"

Vulkan::Init::VulkanSync::VulkanSync() {

}

void Vulkan::Init::VulkanSync::Initialize() noexcept {

}

void Vulkan::Init::VulkanSync::createSyncObjects(VkDevice device) {
    imageAvailableSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFence.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetImageAvailableSemaphore() noexcept {
    return imageAvailableSemaphore;
}

std::vector<VkSemaphore>& Vulkan::Init::VulkanSync::GetRenderFinishedSemaphore() noexcept {
    return renderFinishedSemaphore;
}

std::vector<VkFence>& Vulkan::Init::VulkanSync::GetFlightFence() noexcept {
    return inFlightFence;
}
