#include "window.hpp"

#include <stdexcept>

namespace engine {

    Window::Window(int w, int h, std::string n): width(w), height(h), name(n) {
        initWindow();
    }

    void Window::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void Window::frameBufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto veWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        veWindow->frameBufferResized = true;
        veWindow->width = width;
        veWindow->height = height;
    }
}