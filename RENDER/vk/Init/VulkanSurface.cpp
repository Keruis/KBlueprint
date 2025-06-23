#include "VulkanSurface.h"

Vulkan::Init::VulkanSurface::VulkanSurface() {

}

void Vulkan::Init::VulkanSurface::Initialize() noexcept {

}

void Vulkan::Init::VulkanSurface::createSurface(VkInstance instance, Display *vulkanDisplay, Window vulkanWindow) {
    VkXlibSurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.dpy = vulkanDisplay;
    surfaceInfo.window = vulkanWindow;

    VkResult result = vkCreateXlibSurfaceKHR(instance, &surfaceInfo, nullptr, &m_surface);
    if (result != VK_SUCCESS) {
        std::cerr << "[FATAL] Failed to create Xlib surface! VkResult = " << result << std::endl;
        throw std::runtime_error("vkCreateXlibSurfaceKHR failed");
        /// S_S
    }
}

void Vulkan::Init::VulkanSurface::DestroySurfaceKHR(VkInstance instance) noexcept {
    vkDestroySurfaceKHR(instance, m_surface, nullptr);
}

VkSurfaceKHR Vulkan::Init::VulkanSurface::GetSurfaceKHR() noexcept {
    return m_surface;
}