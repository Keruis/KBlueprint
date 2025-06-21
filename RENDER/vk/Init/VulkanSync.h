#ifndef BLUEPRINT_VULKANSYNC_H
#define BLUEPRINT_VULKANSYNC_H

namespace Vulkan::Init {
    class VulkanSync {
    public:
        VulkanSync();

        void Initialize() noexcept;

        void createSyncObjects() noexcept;

    private:

    };
}

#endif //BLUEPRINT_VULKANSYNC_H
