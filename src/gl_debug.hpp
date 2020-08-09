#ifndef GL_DEBUG_HPP
#define GL_DEBUG_HPP

#include <iostream>

#include <GL/glew.h>

/* Clears all OpenGL errors */
void glClearError();

/* Logs the first OpenGL errors */
void glLogError();

/* Logs all OpenGL errors */
void glLogErrors();

#ifdef _DEBUG

    #define GL_ASSERT(x) if(!(x)) { __builtin_trap(); }
    #define glCall(x) glClearError(); x; GL_ASSERT(glLogCall(#x, __FILE__, __LINE__));
    #define glCallAssignment(x, y) glClearError(); x = y; GL_ASSERT(glLogCall(#x, __FILE__, __LINE__));

    /* Print all OpenGL errors */
    bool glLogCall(const char* function, const char* file, uint32_t line);

# else
    #define glCall(x) x
    #define glCallAssignment(x, y) x = y
# endif


#endif