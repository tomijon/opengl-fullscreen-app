#include <GLFW/glfw3.h>

#include "window.hpp"

using namespace Windows;

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (monitor != nullptr) {
		const GLFWvidmode* monitorSettings = glfwGetVideoMode(monitor);
		width = monitorSettings->width;
		height = monitorSettings->height;
	}

	window = glfwCreateWindow(width, height, title, monitor, share);

	mode = monitor == nullptr ? WindowMode::WINDOWED : WindowMode::FULLSCREEN;
	mode = window == nullptr ? WindowMode::ERROR : mode;

	// Default to primary monitor if none provided.
	this->monitor = monitor == nullptr ? glfwGetPrimaryMonitor() : monitor;
}


Window::~Window() {
	glfwDestroyWindow(window);
}


void Window::SetWindowMode(WindowMode targetMode) {
	if (targetMode == mode) return;

	switch (targetMode) {
	case WindowMode::FULLSCREEN:
		SetFullscreen();
		return;

	case WindowMode::BORDERLESS:
		SetBorderless();
		return;

	case WindowMode::WINDOWED:
		SetWindowed();
		return;

	default:
		;
	}

	mode = targetMode;
}


void Window::SetFullscreenMonitor(int monitorIndex) {
	int numMonitors;
	GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);
	monitor = monitors[monitorIndex];
}


void Window::MakeThisContext() {
    glfwMakeContextCurrent(window);
}


void Window::Update() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		mode = WindowMode::CLOSED;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}


bool Window::IsOpen() {
	return mode != WindowMode::ERROR && mode != WindowMode::CLOSED;
}


void Window::SetFullscreen() {
	const GLFWvidmode* monitorSettings = glfwGetVideoMode(monitor);
	const char* title = glfwGetWindowTitle(window);

	GLFWwindow* newWindow = glfwCreateWindow(monitorSettings->width, monitorSettings->height,
		title, monitor, shared);
	glfwDestroyWindow(window);
	window = newWindow;
}


void Window::SetBorderless() {

}


void Window::SetWindowed() {

}



