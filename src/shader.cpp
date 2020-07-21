#include "shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include "gl_debug.hpp"

enum class ShaderType { kNone = -1, kVertex = 0, kFragment = 1 };

/* Compiles a shader from a string containing source code and returns it's ID */
uint32_t CompileShader(uint32_t type, const std::string& source) {

    uint32_t id;
    glCallAssignment(id, glCreateShader(type));

    /* Gets the shader source code from the string provided */
    const char *src = source.c_str();

    glCall(glShaderSource(id, 1, &src, nullptr));
    glCall(glCompileShader(id));

    /* Checks and logs errors. */
    int32_t success;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if(!success) {

        /* Gets the error message */
        int32_t length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        glCall(glGetShaderInfoLog(id, length, &length, message));

        std::cerr << "Failed to compile shader!" << std::endl;
        std::cerr << message << std::endl;

        glCall(glDeleteShader(id));

        return 0;

    }

    return id;

}

/* Creates a shader from a string containing source code and returns it's ID */
uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

    uint32_t program;
    glCallAssignment(program, glCreateProgram());
    
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glCall(glAttachShader(program, vs));
    glCall(glAttachShader(program, fs));

    glCall(glLinkProgram(program));
    glCall(glValidateProgram(program));

    // TODO: handles errors.

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));

    return program;

}

/* Creates a shader from a file and returns it's ID */
uint32_t CreateShader(std::ifstream& shader) {

    ShaderType cur_type = ShaderType::kNone;

    /* Stores any shaders being read (2 is used, because we currently only support vertex and fragment shaders) */
    std::stringstream streams[2];

    /* Reads the shader from the file */
    std::string line;
    while(getline(shader, line)) {
        /* Detects which type of shader is currently being read */
        if(line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos)
                cur_type = ShaderType::kVertex;
            else if(line.find("fragment") != std::string::npos)
                cur_type = ShaderType::kFragment;
        /* Reads the shader normally */
        } else {
            streams[(uint32_t)cur_type] << line << std::endl;
        }
    }
    
    return CreateShader(streams[0].str(), streams[1].str());

}

/* Opens a file, creates a shader from it and returns it's ID */
uint32_t ParseShader(const std::string& filepath) {

    /* Opens the file */
    std::ifstream shader(filepath);
    if(!shader.is_open() || !shader.good()) {
        std::cerr << "Failed to open shader file (\"" << filepath << "\")!" << std::endl;
        return 0;
    }

    return CreateShader(shader);

}