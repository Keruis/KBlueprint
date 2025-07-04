#ifndef DEMO_MESH_H
#define DEMO_MESH_H

#include <cstring>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "../Vertex.h"
#include "../Init/utils/Memory.h"
#include "../../../Math/MMat.h"
#include "../Init/config.h"
#include "../UniformBufferObject.h"

class Mesh {
public:
    void createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool);
    void createIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool);
    void createUniformBuffers(VkDevice device, VkPhysicalDevice physicalDevice);

    [[nodiscard]] VkBuffer GetVertexBuffer() const noexcept;
    [[nodiscard]] VkBuffer GetIndexBuffer() const noexcept;
    [[nodiscard]] uint32_t GetVertexSize() const noexcept;
    [[nodiscard]] uint32_t GetIndexSize() const noexcept;
    [[nodiscard]] std::vector<VkBuffer>& GetUniformBuffers() noexcept;
    [[nodiscard]] std::vector<VkDeviceMemory>& GetUniformBuffersMemory() noexcept;
    [[nodiscard]] std::vector<void*>& GetUniformBuffersMapped() noexcept;

    void cleanup(VkDevice device) noexcept;

private:
    void copyBuffer(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

public:
    std::vector<Vertex> vertices;
    const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
    };

    UniformBufferObject ubo;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
};


#endif //DEMO_MESH_H
