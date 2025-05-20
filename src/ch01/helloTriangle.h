#ifndef HELLO_TRIANGLE
#define HELLO_TRIANGLE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hello_triangle {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	int helloTriangle();
}
#endif // !HELLO_TRIANGLE
