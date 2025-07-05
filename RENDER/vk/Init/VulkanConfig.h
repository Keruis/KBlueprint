/*
 * File:    VulkanConfig.h
 * Author:  Keruis
 * Date:    2025-07-05
 * Project: Blueprint Vulkan Renderer
 * Brief:   Vulkan 渲染配置项定义头文件。
 *
 * Description:
 *   This header defines global Vulkan-related configuration constants
 *   such as validation layer toggling and required device extensions.
 *
 *   本文件用于定义 Vulkan 的全局配置，包括是否启用验证层（基于编译模式），
 *   以及设备所需的扩展列表（如 VK_KHR_swapchain）。
 *
 * License: MIT License
 */

#ifndef BLUEPRINT_VULKANCONFIG_H
#define BLUEPRINT_VULKANCONFIG_H

#include <vector>
#include <vulkan/vulkan.h>

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#endif //BLUEPRINT_VULKANCONFIG_H
