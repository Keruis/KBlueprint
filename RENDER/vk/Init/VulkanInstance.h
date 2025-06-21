#ifndef BLUEPRINT_VULKANINSTANCE_H
#define BLUEPRINT_VULKANINSTANCE_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <ranges>
#include <expected>
#include <algorithm>
#include <vulkan/vulkan.h>

#include "VulkanConfig.h"
#include "utils/VulkanEnumerateUtils.h"
#include "utils/VulkanBoolUtils.h"
#include "utils/KDebug.h"

namespace Vulkan::Init {
    class VulkanInstance {
    public:
        VulkanInstance();

        void Initialize() noexcept;
        void createInstance();
        void setupDebugMessenger();

        void DestroyDebugUtilsMessengerEXT() noexcept;
        void DestroyInstance() noexcept;

        VkInstance& GetInstance() noexcept;

    private:
        bool checkValidationLayerSupport() noexcept;
        std::vector<const char*> getRequiredExtensions() noexcept;
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) noexcept;
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            void* pUserData);
        std::expected<VkDebugUtilsMessengerEXT, VkResult>
        CreateDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT* createInfo);
    private:
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugMessenger;
    };
}

#endif //BLUEPRINT_VULKANINSTANCE_H
