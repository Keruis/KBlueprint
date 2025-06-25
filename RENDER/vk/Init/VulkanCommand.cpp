#include "VulkanCommand.h"

Vulkan::Init::VulkanCommand::VulkanCommand() {

}

void Vulkan::Init::VulkanCommand::Initialize() noexcept {

}

void Vulkan::Init::VulkanCommand::createCommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr) {
    Vulkan::Init::QueueFamilyIndices queueFamilyIndices = Vulkan::Init::Utils::findQueueFamilies(physicalDevice, surfaceKhr);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void Vulkan::Init::VulkanCommand::createCommandBuffer(VkDevice device) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

VkCommandPool Vulkan::Init::VulkanCommand::GetCommandPool() noexcept {
    return commandPool;
}

VkCommandBuffer& Vulkan::Init::VulkanCommand::GetCommandBuffer() noexcept {
    return commandBuffer;
}