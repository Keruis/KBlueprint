#ifndef BLUEPRINT_VULKANCONFIG_H
#define BLUEPRINT_VULKANCONFIG_H

#include <vector>

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#endif //BLUEPRINT_VULKANCONFIG_H
