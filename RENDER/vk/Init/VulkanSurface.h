#ifndef BLUEPRINT_VULKANSURFACE_H
#define BLUEPRINT_VULKANSURFACE_H

#include <iostream>
#include <stdexcept>

#include <X11/Xlib.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

#include "utils/KDebug.h"

namespace Vulkan::Init {
    class VulkanSurface {
    public:
        VulkanSurface();

        void Initialize() noexcept;

        void createSurface(VkInstance instance, Display* vulkanDisplay, Window vulkanWindow);
        void DestroySurfaceKHR(VkInstance instance) noexcept;

        VkSurfaceKHR GetSurfaceKHR() noexcept;
    private:
        VkSurfaceKHR m_surface;
    };
}

#endif //BLUEPRINT_VULKANSURFACE_H
