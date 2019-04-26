#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "Logger.h"

using namespace std;

#define gWINDOW_NAME "Covert_GL"
#define gViewport_Width 800
#define gViewport_Height 600

GLFWwindow* InitOpenGL();
void ProcessInput(GLFWwindow *window);

int loadShader(char* filename, GLchar* ShaderSource, unsigned long len);
unsigned long getFileLength(ifstream& file);
int unloadshader(GLubyte** ShaderSource);

//OpenGL Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//ShaderLoading
GLuint LoadShader(const char* VERTEX_PATH, const char* FRAGMENT_PATH);
string ReadFile(const char *filePath);