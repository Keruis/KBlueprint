#ifndef BLUEPRINT_VULKANDEVICE_H
#define BLUEPRINT_VULKANDEVICE_H

#include <set>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <ranges>

#include <vulkan/vulkan.h>

#include "VulkanConfig.h"
#include "VulkanStruct.h"
#include "VulkanFuncUtils.h"

namespace Vulkan::Init {
    class VulkanDevice {
    public:
        VulkanDevice();

        void Initialize() noexcept;

        void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surfaceKhr);
        void createLogicalDevice(VkSurfaceKHR surfaceKhr);

        VkDevice GetDevice() noexcept;
        VkPhysicalDevice GetPhysicalDevice() noexcept;
        [[nodiscard]] const VkQueue& GetGraphicsQueue() const noexcept;
        [[nodiscard]] const VkQueue& GetPresentQueue() const noexcept;

    private:
        static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surfaceKhr) noexcept;
        static bool checkDeviceExtensionSupport(VkPhysicalDevice device) noexcept;

    private:
        VkDevice m_device = VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkQueue m_graphicsQueue;
        VkQueue m_presentQueue;
    };
}

#endif //BLUEPRINT_VULKANDEVICE_H
