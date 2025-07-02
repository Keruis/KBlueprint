#ifndef DEMO_MESH_H
#define DEMO_MESH_H

#include <stdexcept>

#include <vulkan/vulkan.h>

#include "../Vertex.h"

class Mesh {
public:
    void createVertexBuffer(VkDevice device);

    VkBuffer& GetVertexBuffer() noexcept;

private:
    const std::vector<Vertex> vertices = {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };
    VkBuffer vertexBuffer;
};


#endif //DEMO_MESH_H
