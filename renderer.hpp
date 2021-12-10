#pragma once

#include "window.hpp"
#include "device.hpp"
#include "swap_chain.hpp"

#include <memory>
#include <vector>
#include <cassert>

namespace engine {

class Renderer {

    public:
        Renderer(Window &window_in, Device &device_in);
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        VkRenderPass getSwapchainRenderPass() const { return swapchain->getRenderPass(); }
        bool isFrameInProgress() const { return isFrameStarted; }
        VkCommandBuffer getCurrentCommandBuffer() const  {
            assert(isFrameStarted && "Cannot get command buffer when frame is not in progress!");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame is not in progress!");
            return currentFrameIndex;
        }

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapchain();

        Window &window;
        Device &device;
        std::unique_ptr<SwapChain> swapchain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
};
}   // namespace engine