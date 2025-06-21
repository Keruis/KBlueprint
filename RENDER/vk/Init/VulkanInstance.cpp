#include "VulkanInstance.h"

Vulkan::Init::VulkanInstance::VulkanInstance() {

}

void Vulkan::Init::VulkanInstance::Initialize() noexcept {

}

void Vulkan::Init::VulkanInstance::createInstance() {
    Utils::K_MixedAll(enableValidationLayers, !checkValidationLayerSupport())
        .then([](){
            throw std::runtime_error("validation layers requested, but not available!");
        })
        .otherwise([](){
            kDebug() << "Validation layers are available.";
        });

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Keruis";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    Utils::K_MixedAll(enableValidationLayers)
        .then([&](){
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        })
        .otherwise([&](){
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        });

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS) {
        std::cerr << "vkCreateInstance failed with code: " << result << std::endl;
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

void Vulkan::Init::VulkanInstance::setupDebugMessenger() {
    if constexpr (enableValidationLayers) {
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        CreateDebugMessenger(&createInfo)
            .and_then([this](VkDebugUtilsMessengerEXT messenger)
                -> std::expected<void, VkResult> {
                    m_debugMessenger = messenger;
                    return std::expected<void, VkResult>{};
                })
                .or_else([](VkResult err)
                -> std::expected<void, VkResult> {
                    std::cerr << "Create failed with: " << err << "\n";
                    return std::unexpected(err);
                }
            );

    }
}

bool Vulkan::Init::VulkanInstance::checkValidationLayerSupport() noexcept {
    std::vector<VkLayerProperties> availableLayers =
            Utils::K_vkEnumerateVector<VkLayerProperties>
                    (vkEnumerateInstanceLayerProperties);

    auto isLayerAvailable = [&](const char* layerName) -> bool {
        return std::ranges::any_of(
            availableLayers,
            [&](const VkLayerProperties& props) {
                return std::strcmp(layerName, props.layerName) == 0;
            });
    };

    return std::ranges::all_of(validationLayers, isLayerAvailable);
}

std::vector<const char *> Vulkan::Init::VulkanInstance::getRequiredExtensions() noexcept {
    std::vector<const char*> extensions;

    extensions.push_back("VK_KHR_surface");

#ifdef _WIN32
    extensions.push_back("VK_KHR_win32_surface");
#elif defined(__linux__)
    extensions.push_back("VK_KHR_xlib_surface");
#endif

    Utils::K_MixedAll(enableValidationLayers)
        .then([&](){
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        });

    return extensions;
}

void Vulkan::Init::VulkanInstance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) noexcept {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT         |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT      |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan::Init::VulkanInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                    void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

std::expected<VkDebugUtilsMessengerEXT, VkResult>
Vulkan::Init::VulkanInstance::CreateDebugMessenger(const VkDebugUtilsMessengerCreateInfoEXT* createInfo) {
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT"));

    if (!func) {
        return std::unexpected(VK_ERROR_EXTENSION_NOT_PRESENT);
    }

    VkDebugUtilsMessengerEXT messenger{};
    VkResult result = func(m_instance, createInfo, nullptr, &messenger);
    if (result != VK_SUCCESS)
        return std::unexpected(result);

    return messenger;
}

void Vulkan::Init::VulkanInstance::DestroyDebugUtilsMessengerEXT() noexcept {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(m_instance, m_debugMessenger, nullptr);
    }
}

void Vulkan::Init::VulkanInstance::DestroyInstance() noexcept {
    vkDestroyInstance(m_instance, nullptr);
}

VkInstance &Vulkan::Init::VulkanInstance::GetInstance() noexcept {
    return m_instance;
}