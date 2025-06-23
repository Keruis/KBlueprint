#include "VulkanDevice.h"
#include "VulkanStruct.h"

Vulkan::Init::VulkanDevice::VulkanDevice() {

}

void Vulkan::Init::VulkanDevice::Initialize() noexcept {

}
#include <iostream>
void Vulkan::Init::VulkanDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surfaceKhr) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::cout << "r1" <<std::endl;

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    std::cout << "r2" <<std::endl;
    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surfaceKhr)) {
            m_physicalDevice = device;
            break;
        }
    }
    std::cout << "r3" <<std::endl;
    if (m_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void Vulkan::Init::VulkanDevice::createLogicalDevice(VkSurfaceKHR surfaceKhr) {
    QueueFamilyIndices indices = Utils::findQueueFamilies(m_physicalDevice, surfaceKhr);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
    vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
}

VkDevice Vulkan::Init::VulkanDevice::GetDevice() noexcept {
    return m_device;
}

VkPhysicalDevice Vulkan::Init::VulkanDevice::GetPhysicalDevice() noexcept {
    return m_physicalDevice;
}

const VkQueue &Vulkan::Init::VulkanDevice::GetGraphicsQueue() const noexcept {
    return m_graphicsQueue;
}

const VkQueue &Vulkan::Init::VulkanDevice::GetPresentQueue() const noexcept {
    return m_presentQueue;
}

bool Vulkan::Init::VulkanDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surfaceKhr) noexcept {
    QueueFamilyIndices indices = Utils::findQueueFamilies(device, surfaceKhr);
    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = Init::Utils::querySwapChainSupport(device, surfaceKhr);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool Vulkan::Init::VulkanDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) noexcept {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

