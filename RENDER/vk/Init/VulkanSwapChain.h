#ifndef BLUEPRINT_VULKANSWAPCHAIN_H
#define BLUEPRINT_VULKANSWAPCHAIN_H

#include <numeric>
#include <algorithm>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "VulkanStruct.h"
#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanSwapChain {
    public:
        VulkanSwapChain();

        void Initialize() noexcept;

        void createSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surfaceKhr, int width, int height);
        void createImageViews(VkDevice device);

        std::vector<VkImageView>& GetSwapChainImageViews() noexcept;
        VkSwapchainKHR GetSwapChain() noexcept;
        VkFormat GetSwapChainImageFormat() noexcept;
        VkExtent2D GetExtent2D() noexcept;

    private:
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int width, int height);

    private:
        VkSwapchainKHR m_swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkImageView> swapChainImageViews;
    };
}

#endif //BLUEPRINT_VULKANSWAPCHAIN_H
