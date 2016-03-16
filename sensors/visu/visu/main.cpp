#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>

const char * readFile(const char *filename);

int main() {
  
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;

  sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  // Create and compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char * vertShaderSource = readFile("basic.vert");
  glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
  glCompileShader(vertexShader);

  // Create and compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char * fragShaderSource = readFile("basic.frag");
  glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Link the vertex and fragment shader into a shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);

  GLfloat vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Color
  GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
  glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  
  while (window.isOpen()) {
    sf::Event windowEvent;
    while (window.pollEvent(windowEvent)) {
      switch (windowEvent.type) {
      case sf::Event::Closed:
	window.close();
	break;
      }
    }

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap buffers
    window.display();
  }

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);
}


const char * readFile(const char *filename) {

  std::ifstream t(filename);
  std::string str;

  t.seekg(0, std::ios::end);   
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);
  
  str.assign((std::istreambuf_iterator<char>(t)),
	     std::istreambuf_iterator<char>());

  return str.c_str();

}
