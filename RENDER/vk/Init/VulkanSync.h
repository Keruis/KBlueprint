#ifndef BLUEPRINT_VULKANSYNC_H
#define BLUEPRINT_VULKANSYNC_H

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {
    class VulkanSync {
    public:
        VulkanSync();

        void Initialize() noexcept;

        void createSyncObjects(VkDevice device);

        VkSemaphore& GetImageAvailableSemaphore() noexcept;
        VkSemaphore& GetRenderFinishedSemaphore() noexcept;
        VkFence& GetFlightFence() noexcept;

    private:
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;
    };
}

#endif //BLUEPRINT_VULKANSYNC_H
