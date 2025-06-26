#ifndef HELLO_TRANSFORM
#define HELLO_TRANSFORM
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hello_transform {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	int helloTransform();

	void createTexture(unsigned int& texture, const char*, GLenum format);
}
#endif 
