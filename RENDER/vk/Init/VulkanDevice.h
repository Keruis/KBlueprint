#ifndef BLUEPRINT_VULKANDEVICE_H
#define BLUEPRINT_VULKANDEVICE_H

namespace Vulkan::Init {
    class VulkanDevice {
    public:
        VulkanDevice();

        void Initialize() noexcept;

        void pickPhysicalDevice() noexcept;

        void createLogicalDevice() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANDEVICE_H
