/*
 * File:    VulkanInstance.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   封装 Vulkan 实例（VkInstance）与调试工具的初始化与管理。
 *
 * Description:
 *   This header defines the VulkanInstance class, which handles the
 *   creation and destruction of the Vulkan instance (VkInstance), as well
 *   as the setup of the debug messenger (VkDebugUtilsMessengerEXT) for
 *   validation and debugging during development.
 *
 *   本类是 Vulkan 初始化的第一步，负责创建 Vulkan 实例和调试消息回调，
 *   包括验证层支持检测、所需扩展获取、调试回调函数注册等关键步骤。
 *
 * License: MIT License
 */


#ifndef BLUEPRINT_VULKANINSTANCE_H
#define BLUEPRINT_VULKANINSTANCE_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <format>
#include <ranges>
#include <numeric>
#include <expected>
#include <algorithm>
#include <vulkan/vulkan.h>

#include "VulkanConfig.h"
#include "utils/VulkanEnumerateUtils.h"
#include "utils/VulkanBoolUtils.h"
#include "utils/VulkanConstexprUtils.h"
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

        VkInstance GetInstance() noexcept;

    private:
        static std::expected<bool, std::vector<std::string>>
        checkValidationLayerSupport() noexcept;
        static std::vector<const char*> getRequiredExtensions() noexcept;
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) noexcept;
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            void* pUserData);
        std::expected<VkDebugUtilsMessengerEXT, VkResult>
        CreateDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT* createInfo);
    private:
        VkInstance m_instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
    };
}

#endif //BLUEPRINT_VULKANINSTANCE_H
