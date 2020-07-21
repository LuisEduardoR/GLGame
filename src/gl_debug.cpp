#include <iostream>

#include <GL/glew.h>

/* Clears all OpenGL errors */
void glClearError() {
    while(glGetError());
}

/* Logs the first OpenGL errors */
void glLogError() {
    if(GLenum error = glGetError()) {
            std::cout << "[OpenGL ERROR] (0x" << std::hex << error << ")" << std::endl;
    }
}

/* Logs all OpenGL errors */
void glLogErrors() {
    while(GLenum error = glGetError()) {
            std::cout << "[OpenGL ERROR] (0x" << std::hex << error << ")" << std::endl;
    }
}

#ifdef _DEBUG


    /* Print all OpenGL errors */
    bool glLogCall(const char* function, const char* file, uint32_t line) {

        while(GLenum error = glGetError()) {
            std::cout << "[OpenGL ERROR] (0x" << std::hex << error << "): " << file << ":" << std::dec << line << " " << function << std::endl;
            return false;
        }

        return true;

    }


#endif