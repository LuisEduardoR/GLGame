#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <map>
#include <string>
#include <iostream>
#include <filesystem>

#include <SDL2/SDL.h>

#include "shader.hpp"

/* Extension to be checked for shader files */
constexpr char kShaderExtension[] = ".glsl";

/* Vertex shader that will be used in case a ShaderResquest can't find a shader */
constexpr char kErrorVertexShader[] =   "#version 410 core"
                                        "\n"
                                        "layout(location = 0) in vec4 position;"
                                        "\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = position;\n"
                                        "}\n";
/* Fragment shader that will be used in case a ShaderResquest can't find a shader */
constexpr char kErrorFragmentShader[] = "#version 410 core\n"
                                        "\n"
                                        "layout(location = 0) out vec4 color;\n"
                                        "\n"
                                        "void main()\n"
                                        "{\n"
                                        "   color = vec4(1.0, 0.0, 1.0, 1.0);\n"
                                        "}\n";

class Renderer {

    public:

        Renderer(SDL_Window* window, SDL_GLContext context);

        /* Loads game shaders from a files in a certain path (returns a pair with the number of shaders loaded successfully and the total number of shaders found) */
        std::pair<uint32_t,uint32_t> LoadShaders(const std::string& path);

        /* Requests a shader  to the renderer by name (returns the default_error_shader if no shader is found this shader is created by the renderer class constructor using kErrorVertexShader and )kErrorFragmentShader */
        uint32_t RequestShader(const std::string& name);

        /* Checks if a shader is the default_error_shader */
        bool IsErrorShader(uint32_t shader);

    private:

        SDL_Window* window;
        SDL_GLContext context;

        uint32_t default_error_shader;
        std::map<std::string, uint32_t> shaders;

};

#endif