#include "Engine.h"


GLFWwindow* InitOpenGL()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow* tempWindow = glfwCreateWindow(gViewport_Width, gViewport_Height, gWINDOW_NAME, NULL, NULL);

  if (tempWindow == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(tempWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, gViewport_Width, gViewport_Height);

  glfwSetFramebufferSizeCallback(tempWindow, framebuffer_size_callback);

  return tempWindow;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

std::string ReadFile(const char *filePath)
{
  std::string fileContent;
  std::ifstream fileStream(filePath, std::ios::in);

  if (!fileStream.is_open())
  {
    std::cerr << "Could not read file" << filePath << ": File Does not exist." << std::endl;
    return "";
  }
  
  std::string line = "";
  while (!fileStream.eof())
  {
    std::getline(fileStream, line);
    fileContent.append(line + "\n");
  }

  fileStream.close();
  return fileContent;
}

GLuint LoadShader(const char* VERTEX_PATH, const char* FRAGMENT_PATH)
{
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = ReadFile(VERTEX_PATH);
  std::string fragShaderStr = ReadFile(FRAGMENT_PATH);
  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader
  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  std::cout << &vertShaderError[0] << std::endl;

  // Compile fragment shader
  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  std::cout << &fragShaderError[0] << std::endl;

  std::cout << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> programError((logLength > 1) ? logLength : 1);
  glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
  std::cout << &programError[0] << std::endl;

  //Delete all shader objects
  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  return program;
}