#ifndef BLUEPRINT_VULKANSURFACE_H
#define BLUEPRINT_VULKANSURFACE_H

namespace Vulkan::Init {
    class VulkanSurface {
    public:
        VulkanSurface();

        void Initialize() noexcept;

        void createSurface() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANSURFACE_H
