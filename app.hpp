#pragma once

#include "camera.hpp"
#include "window.hpp"
#include "device.hpp"
#include "swap_chain.hpp"
#include "game_object.hpp"
#include "renderer.hpp"

#include <memory>
#include <vector>

namespace engine {

class App {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete;

        void run(); 

    private:
        void loadGameObjects();

        Window window{WIDTH, HEIGHT, "Hello Vulkan!"};
        Device device{window};
        Renderer renderer{window, device};
        std::vector<GameObject> gameObjects;
};
}   // namespace engine