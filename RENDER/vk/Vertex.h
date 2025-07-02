#ifndef DEMO_VERTEX_H
#define DEMO_VERTEX_H

#include <vulkan/vulkan.h>

#include "../../Math/Vec/include/Vec2.hpp"
#include "../../Math/Vec/include/Vec3Float.hpp"

struct Vertex {
    Math::Vec::vec<2, float> pos;
    Math::Vec::vec<3, float> color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);
        return attributeDescriptions;
    }
};

#endif //DEMO_VERTEX_H
