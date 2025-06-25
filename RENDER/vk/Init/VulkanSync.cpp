#include "VulkanSync.h"

Vulkan::Init::VulkanSync::VulkanSync() {

}

void Vulkan::Init::VulkanSync::Initialize() noexcept {

}

void Vulkan::Init::VulkanSync::createSyncObjects(VkDevice device) {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}

VkSemaphore& Vulkan::Init::VulkanSync::GetImageAvailableSemaphore() noexcept {
    return imageAvailableSemaphore;
}

VkSemaphore& Vulkan::Init::VulkanSync::GetRenderFinishedSemaphore() noexcept {
    return renderFinishedSemaphore;
}

VkFence& Vulkan::Init::VulkanSync::GetFlightFence() noexcept {
    return inFlightFence;
}
