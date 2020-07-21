#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include "gl_debug.hpp"

/* Compiles a shader from a string containing source code and returns it's ID */
uint32_t CompileShader(uint32_t type, const std::string& source);

/* Creates a shader from a string containing source code and returns it's ID */
uint32_t CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);

/* Creates a shader from a file and returns it's ID */
uint32_t CreateShader(std::ifstream& shader);

/* Opens a file, creates a shader from it and returns it's ID */
uint32_t ParseShader(const std::string& filepath);

#endif