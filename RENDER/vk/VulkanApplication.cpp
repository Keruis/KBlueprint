#include "VulkanApplication.h"

VulkanApplication::VulkanApplication() {

}

VulkanApplication::~VulkanApplication() {

}

void VulkanApplication::Initialize() {
    window = new X11Window(1024, 768, "Vulkan Ready X11 Window (Enhanced Callbacks)");
    m_context.init(window->getDisplay(), window->getWindowHandle(), window->getWidth(), window->getHeight());
}

void VulkanApplication::Run() {
    try {
        mainLoop();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error] Exception: " << e.what() << std::endl;
    }
}

void VulkanApplication::Cleanup() {
    m_context.cleanup();
}

void VulkanApplication::mainLoop() {
    Render::utils::FrameLimiter limiter(7000.0);
    Render::utils::AsyncFrameRateCounter fps;
    Input input;
    input.Initialize(static_cast<void*>(&window->getWindowHandle()), window->getWidth(), window->getHeight());

    window->show();
    window->addKeyPressCallback([](const XKeyEvent& keyEvent) {
        char buffer[32];
        KeySym keysym;
        XComposeStatus composeStatus;
        int len = XLookupString(const_cast<XKeyEvent*>(&keyEvent), buffer, sizeof(buffer), &keysym, &composeStatus);
        if (len > 0) {
            std::cout << "Callback: Key pressed: " << buffer[0] << " (Keysym: " << XKeysymToString(keysym) << ")" << std::endl;
        }
        if (keysym == XK_Escape) {
            std::cout << "Callback: Escape key detected!" << std::endl;
        }
    });
    window->startEventThread();

    bool appRunning = true;

    try {
        while (appRunning) {
            limiter.beginFrame();

            if (window->hasQuitRequested()) {
                appRunning = false;
                std::cout << "Main loop: Quit requested. Stopping application." << std::endl;
            }

            input.Frame();
            fps.notify_frame();
            drawFrame();

            if (input.IsMousePressed()) {
                int x, y;
                input.GetMouseLocation(x, y);
                std::cout << "[Input] Mouse Click at (" << x << ", " << y << ")" << std::endl;
            }

            auto stats = fps.GetStats();
            std::cout << "FPS: " << stats.fps
                      << " | Min: " << stats.min_fps
                      << " | Max: " << stats.max_fps
                      << " | Avg: " << stats.avg_fps << '\n';

            limiter.endFrame();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[Fatal Error] Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[Fatal Error] Unknown exception occurred in main loop." << std::endl;
    }

    vkDeviceWaitIdle(m_context.getDevice());
}

void VulkanApplication::drawFrame() {
    vkWaitForFences(m_context.getDevice(), 1, &m_context.getFlightFence()[currentFrame], VK_TRUE, UINT64_MAX);
    vkResetFences(m_context.getDevice(), 1, &m_context.getFlightFence()[currentFrame]);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(m_context.getDevice(), m_context.getSwapChain(), UINT64_MAX, m_context.getImageAvailableSemaphore()[currentFrame], VK_NULL_HANDLE,
                          &imageIndex);

    vkResetCommandBuffer(m_context.getCommandBuffer()[currentFrame], 0);
    recordCommandBuffer(m_context.getCommandBuffer()[currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {m_context.getImageAvailableSemaphore()[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_context.getCommandBuffer()[currentFrame];

    VkSemaphore signalSemaphores[] = {m_context.getRenderFinishedSemaphore()[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(m_context.getGraphicsQueue(), 1, &submitInfo, m_context.getFlightFence()[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {m_context.getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(m_context.getPresentQueue(), &presentInfo);

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanApplication::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_context.getRenderPass();
    renderPassInfo.framebuffer = m_context.getSwapChainFrameBuffers()[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = m_context.getExtent2D();

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_context.getGraphicsPipeline());

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) m_context.getExtent2D().width;
    viewport.height = (float) m_context.getExtent2D().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = m_context.getExtent2D();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}