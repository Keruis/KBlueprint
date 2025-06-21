#ifndef BLUEPRINT_VULKANUTILS_H
#define BLUEPRINT_VULKANUTILS_H

#include <vector>
#include <cstdint>

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace Vulkan::Utils {
    template <typename Ty_, typename Fn_>
    [[nodiscard]] std::vector<Ty_> K_vkEnumerateVector(Fn_ enumerateFn) {
        uint32_t count = 0;
        if (enumerateFn(&count, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to enumerate Vulkan items (count)");
        }
        std::vector<Ty_> result(count);
        if (count > 0 && enumerateFn(&count, result.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to enumerate Vulkan items (data).");
        }
        return result;
    }
}

#endif //BLUEPRINT_VULKANUTILS_H
