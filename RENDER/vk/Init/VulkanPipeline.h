#ifndef BLUEPRINT_VULKANPIPELINE_H
#define BLUEPRINT_VULKANPIPELINE_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include "../Vertex.h"
#include "config.h"
#include "../UniformBufferObject.h"

namespace Vulkan::Init {
    class VulkanPipeline {
    public:
        VulkanPipeline();

        void Initialize() noexcept;

        void createDescriptorSetLayout(VkDevice device);
        void createGraphicsPipeline(VkDevice device, VkRenderPass renderPass);
        void createDescriptorPool(VkDevice device);
        void createDescriptorSets(VkDevice device, std::vector<std::vector<VkBuffer>>& uniformBuffers);

        VkPipelineLayout GetPipelineLayout() noexcept;
        VkPipeline GetGraphicsPipeline() noexcept;
        VkDescriptorPool GetDescriptorPool() noexcept;
        VkDescriptorSetLayout GetVkDescriptorSetLayout() noexcept;
        std::vector<std::vector<VkDescriptorSet>>& GetDescriptorSets() noexcept;

    private:
        static std::vector<char> readFile(const std::string& filename) {
            std::ifstream file(filename, std::ios::ate | std::ios::binary);

            if (!file.is_open()) {
                throw std::runtime_error("failed to open file!");
            }

            size_t fileSize = (size_t) file.tellg();
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);

            file.close();

            return buffer;
        }

        VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code) {
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();
            createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

            VkShaderModule shaderModule;
            if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
                throw std::runtime_error("failed to create shader module!");
            }

            return shaderModule;
        }

    private:
        VkDescriptorPool descriptorPool;
        std::vector<std::vector<VkDescriptorSet>> descriptorSets;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
    };
}

#endif //BLUEPRINT_VULKANPIPELINE_H
