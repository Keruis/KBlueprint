#include "VulkanApplication.h"

VulkanApplication::VulkanApplication()
    : cameraController(&camera)
{

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
    Render::utils::FrameLimiter limiter(60.0);
    Render::utils::AsyncFrameRateCounter fps;
    Input input;
    input.Initialize(static_cast<void*>(&window->getWindowHandle()), window->getWidth(), window->getHeight());

    window->show();
    window->addKeyPressCallback([&](const XKeyEvent& keyEvent) {
        char buffer[32];
        KeySym keysym;
        XComposeStatus status;

        int len = XLookupString(const_cast<XKeyEvent*>(&keyEvent), buffer, sizeof(buffer), &keysym, &status);
        std::cout << "Key pressed: " << XKeysymToString(keysym) << "\n";

//        auto tmp = camera.GetPosition();
//
//        if (keysym == XK_w || keysym == XK_W) {
//            std::cout << "Moving camera up\n";
//            camera.SetPosition(tmp.x, tmp.y - 0.05f, tmp.z);
//        }
//        if (keysym == XK_s || keysym == XK_S) {
//            std::cout << "Moving camera down\n";
//            camera.SetPosition(tmp.x, tmp.y + 0.05f, tmp.z);
//        }
//        if (keysym == XK_a || keysym == XK_A) {
//            std::cout << "Moving camera left\n";
//            camera.SetPosition(tmp.x - 0.05f, tmp.y, tmp.z);
//        }
//        if (keysym == XK_d || keysym == XK_D) {
//            std::cout << "Moving camera right\n";
//            camera.SetPosition(tmp.x + 0.05f, tmp.y, tmp.z);
//        }

        if (keysym == XK_Escape) {
            std::cout << "Escape pressed\n";
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
            cameraController.Update(input, limiter.GetDeltaTime());
            camera.Render();
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

    updateUniformBuffer(currentFrame);

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

    for (uint32_t i = 0; i < 2; i++) {
        VkBuffer vertexBuffers[] = {m_context.getVertexBuffer(i)};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, m_context.getIndexBuffer(i), 0, VK_INDEX_TYPE_UINT16);
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_context.getPipelineLayout(), 0, 1, &m_context.getDescriptorSets()[i][currentFrame], 0, nullptr);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(m_context.getIndexSize(i)), 1, 0, 0, 0);
    }

    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

#include <glm/gtc/matrix_transform.hpp>

void VulkanApplication::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    for (uint32_t i = 0; i < 2; i++) {
        UniformBufferObject ubo{};

        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0, 0, 1));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(i == 0 ? -0.5f : 0.5f, 0.0f, 0.0f));

        ubo.model = rotate * translate;
        Math::Mat::MatF44 tmp;
        camera.GetViewMatrix(tmp);
        ubo.view = glm::mat4(tmp[0][0], tmp[0][1], tmp[0][2], tmp[0][3],
                             tmp[1][0], tmp[1][1], tmp[1][2], tmp[1][3],
                             tmp[2][0], tmp[2][1], tmp[2][2], tmp[2][3],
                             tmp[3][0], tmp[3][1], tmp[3][2], tmp[3][3]);
        ubo.proj = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

        memcpy(m_context.getUniformBuffersMapped(i)[currentImage], &ubo, sizeof(ubo));
    }

}
