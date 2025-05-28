#ifndef HELLO_SHADER2
#define HELLO_SHADER2
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hello_shader2 {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	int helloShader2();
}
#endif // !HELLO_SHADER2
