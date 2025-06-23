#include "VulkanInstance.h"

Vulkan::Init::VulkanInstance::VulkanInstance() {

}

void Vulkan::Init::VulkanInstance::Initialize() noexcept {

}

void Vulkan::Init::VulkanInstance::createInstance() {
    Utils::K_constexpr_if<enableValidationLayers>([&](){
        checkValidationLayerSupport()
            .and_then([](bool) -> std::expected<void, std::vector<std::string>> {
                kDebug() << "Validation layers are available.";
                return std::expected<void, std::vector<std::string>>{};
            })
            .or_else([](std::vector<std::string> err)
                -> std::expected<void, std::vector<std::string>> {
                throw std::runtime_error("missing layers: [ " +
                     (err.empty() ? "" : std::accumulate(
                         std::next(err.begin()), err.end(), err[0],
                         [](std::string a, const std::string& b)
                            -> std::string {
                             return "\033[31m"
                                + std::move(a) + " \033[0m## \033[31m"
                                + b + "\033[0m";
                         })
                     )
                     + " ]"
                );}
            );
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
    Utils::K_constexpr_if<enableValidationLayers>([&](){
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
                throw std::runtime_error("CreateDebugMessenger failed with code: "
                + std::to_string(err));
            });

    });
}

std::expected<bool, std::vector<std::string>>
Vulkan::Init::VulkanInstance::checkValidationLayerSupport() noexcept {
    const auto availableLayers =
            Utils::K_vkEnumerateVector<VkLayerProperties>
                    (vkEnumerateInstanceLayerProperties);

    auto&& missingLayers = validationLayers
        | std::views::filter([&](const char* layerName)
            -> bool {
            return !std::ranges::any_of(
                availableLayers,
                [&](const VkLayerProperties& props) {
                    return std::strcmp(layerName, props.layerName) == 0;
                });
            })
        | std::views::transform([](const char* name)
            -> std::string {
                return std::string{name};
            })
        | std::ranges::to<std::vector>();

    return missingLayers.empty() ? std::expected<bool, std::vector<std::string>>{true}
                           : std::unexpected(std::move(missingLayers));
}

std::vector<const char*> Vulkan::Init::VulkanInstance::getRequiredExtensions() noexcept {
    auto base_extensions = {
            "VK_KHR_surface",
#if defined(_WIN32)
            "VK_KHR_win32_surface",
#elif defined(__linux__)
            "VK_KHR_xlib_surface",
#endif
    };

    std::vector<const char*> extensions{base_extensions};

    Utils::K_constexpr_if<enableValidationLayers>([&](){
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
    kDebug() << "validation layer: " << pCallbackData->pMessage;
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
    if (m_debugMessenger != VK_NULL_HANDLE && m_instance != VK_NULL_HANDLE) {
        auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func) {
            func(m_instance, m_debugMessenger, nullptr);
            m_debugMessenger = VK_NULL_HANDLE;
        }
    }
}

void Vulkan::Init::VulkanInstance::DestroyInstance() noexcept {
    DestroyDebugUtilsMessengerEXT();

    if (m_instance != VK_NULL_HANDLE) {
        vkDestroyInstance(m_instance, nullptr);
        m_instance = VK_NULL_HANDLE;
    }
}

VkInstance Vulkan::Init::VulkanInstance::GetInstance() noexcept {
    return m_instance;
}