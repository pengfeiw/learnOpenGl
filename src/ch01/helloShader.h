#ifndef HELLO_SHADER
#define HELLO_SHADER
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hello_shader {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	int helloShader();
}
#endif // !HELLO_SHADER
