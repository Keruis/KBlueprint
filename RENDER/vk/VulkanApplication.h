#ifndef DEMO_VULKANAPPLICATION_H
#define DEMO_VULKANAPPLICATION_H

#include "System.h"
#include "Init/VulkanContext.h"

#include "../inputclass.h"
#include "../FrameRateCounter.h"
#include "../FrameLimiter.h"

class VulkanApplication {
public:
    VulkanApplication();
    ~VulkanApplication();

    void Initialize();
    void Run();
    void Cleanup();

private:
    void mainLoop();
    void drawFrame();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
    uint32_t currentFrame = 0;

    X11Window* window;
    Vulkan::VulkanContext m_context;
};


#endif //DEMO_VULKANAPPLICATION_H
