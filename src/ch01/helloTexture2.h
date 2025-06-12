#ifndef HELLO_TEXTURE2
#define HELLO_TEXTURE2
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hello_texture2 {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput(GLFWwindow* window);

	int helloTexture2();

	int createTexture(const char*, GLenum format);
}
#endif 
