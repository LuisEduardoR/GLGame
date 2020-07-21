
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "shader.hpp"

/* Window parameters */
constexpr char kWindowTitle[] = "Window";
constexpr uint32_t kWindowDimensionsX = 1024;
constexpr uint32_t kWindowDimensionsY = 768;

/* OpenGL version */
constexpr uint32_t kGLMajor = 4, kGLMinor = 1;

int main(int argc, char **argv) {

    /* SDL initialization */
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Configures OpenGL context */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, kGLMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, kGLMinor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    /* Creates the window and the OpenGL context */
    SDL_Window *window = SDL_CreateWindow(kWindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowDimensionsX, kWindowDimensionsY, SDL_WINDOW_OPENGL);
    if(window == nullptr) {
        std::cout << "SDL window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(context == nullptr) {
        std::cout << "SDL GL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    /* GLEW initialization */
    if (glewInit() != GLEW_OK) {
        // TODO: Actually detect the correct
        std::cout << "GLEW could not initialize! GLEW Error: " << "Unknown" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    
    /* Geometry data */
    const glm::vec3 vertices[] =
    {
        { -0.5f,-0.5f, 0.0f },
        { 0.5f,-0.5f, 0.0f },
        { 0.5f,0.5f, 0.0f },
        { -0.5f,0.5f, 0.0f }
    };
    const uint32_t indexes[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    /* Creates the buffers */
    uint32_t buffers[2];
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

    /* Loads the buffers with data */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    /* Configures the attributes */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    /* Creates the shader */
    uint32_t shader1 = ParseShader("./res/shaders/basic.glsl");
    glUseProgram(shader1);

    /* Renders */        
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(uint32_t), GL_UNSIGNED_INT, nullptr);
    SDL_GL_SwapWindow(window);

    /* Loops until the window is closed */
    SDL_Event event;
    bool running = true;
    while(running) {

        /* Polls for events */
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

    }

    glDeleteProgram(shader1);

    /* Cleanup and exit */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    exit(EXIT_SUCCESS);

}
