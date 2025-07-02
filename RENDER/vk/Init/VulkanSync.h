#ifndef BLUEPRINT_VULKANSYNC_H
#define BLUEPRINT_VULKANSYNC_H

#include <vector>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "config.h"

namespace Vulkan::Init {
    class VulkanSync {
    public:
        VulkanSync();

        void Initialize() noexcept;

        void createSyncObjects(VkDevice device);

        std::vector<VkSemaphore>& GetImageAvailableSemaphore() noexcept;
        std::vector<VkSemaphore>& GetRenderFinishedSemaphore() noexcept;
        std::vector<VkFence>& GetFlightFence() noexcept;

    private:
        std::vector<VkSemaphore> imageAvailableSemaphore;
        std::vector<VkSemaphore> renderFinishedSemaphore;
        std::vector<VkFence> inFlightFence;
    };
}

#endif //BLUEPRINT_VULKANSYNC_H
