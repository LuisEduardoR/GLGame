#include <utility>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "shader.hpp"
#include "renderer.hpp"
#include "gl_debug.hpp"

/* Window parameters */
constexpr char kWindowTitle[] = "Window";
constexpr uint32_t kWindowDimensionsX = 1024;
constexpr uint32_t kWindowDimensionsY = 768;

/* File paths */
constexpr char kShaderPath[] = ".\\res\\shaders";

/* OpenGL version */
constexpr uint32_t kGLMajor = 3, kGLMinor = 3;

int main(int argc, char **argv) {

    /* SDL initialization */
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    /* Configures OpenGL context */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, kGLMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, kGLMinor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    /* Creates the window and the OpenGL context */
    SDL_Window *window = SDL_CreateWindow(kWindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowDimensionsX, kWindowDimensionsY, SDL_WINDOW_OPENGL);
    if(window == nullptr) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(context == nullptr) {
        std::cout << "SDL Error: " << SDL_GetError();
        glLogError();
        exit(EXIT_FAILURE);
    }

    /* GLEW initialization */
    if (glewInit() != GLEW_OK) {
        // TODO: Actually detect the correct error
        std::cout << "GLEW could not initialize!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

    /* Creates the renderer */
    Renderer main_renderer(window, context);
    
    /* Loads shaders */
    std::pair<uint32_t, uint32_t> shader_result = main_renderer.LoadShaders(kShaderPath);
    std::cout << "Loaded shaders: " << shader_result.first << "/" << shader_result.second << "!";
    if(shader_result.first != shader_result.second) {
        std::cout << shader_result.second << " failed to load!";
    }
    std::cout << std::endl;

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
        
    /* Creates the vertex array */
    uint32_t vertex_array;
    glCall(glGenVertexArrays(1, &vertex_array));
    glCall(glBindVertexArray(vertex_array));

    /* Creates the buffers */
    uint32_t buffers[2];
    glCall(glGenBuffers(2, buffers));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, buffers[0]));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]));

    /* Loads the buffers with data */
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW));

    /* Configures the attributes */
    glCall(glEnableVertexAttribArray(0));
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0));

    /*  Sets the shader */
    uint32_t shader1 = main_renderer.RequestShader("basic");
    if(main_renderer.IsErrorShader(shader1)){
        std::cout << "The requested shader \"basic\" could not be found! Falling back..." << std::endl;
    }
    glCall(glUseProgram(shader1));

    /* Create a uniform and uses it with the shader */
    //uint32_t u1_loc;
    //glCallAssignment(u1_loc, glGetUniformLocation(shader1, "u_Color"));

    /* Used to animate the color */
    int32_t color_increment = 1;
    glm::vec3 add_color(0.0f, 0.0f, 0.0f);

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

        /* Updates the color */
        add_color.z += 0.01f * color_increment;

        if(add_color.z > 1.0f) {
            color_increment = -1;
            add_color.z = 1.0f;
        } else if(add_color.z < 0.0f) {
            color_increment = 1;
            add_color.z = 0.0f;
        }
        //glCall(glUniform4f(u1_loc, add_color.x, add_color.y, add_color.z, 0.0f));

        /* Renders */        
        glCall(glClear(GL_COLOR_BUFFER_BIT));
        glCall(glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(uint32_t), GL_UNSIGNED_INT, nullptr));

        /* Updates the window */
        SDL_GL_SwapWindow(window);

    }

    glCall(glDeleteProgram(shader1));

    /* Cleanup and exit */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    exit(EXIT_SUCCESS);

}
