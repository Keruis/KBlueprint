#ifndef DEMO_VULKANSTRUCT_H
#define DEMO_VULKANSTRUCT_H

#include <vector>
#include <optional>

#include <vulkan/vulkan.h>

namespace Vulkan::Init {

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        [[nodiscard]] bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

}

#endif //DEMO_VULKANSTRUCT_H
