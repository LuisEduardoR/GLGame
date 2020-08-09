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
constexpr char kErrorVertexShader[] =   "#version 330 core"
                                        "\n"
                                        "layout(location = 0) in vec4 position;"
                                        "\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = position;\n"
                                        "}\n";
/* Fragment shader that will be used in case a ShaderResquest can't find a shader */
constexpr char kErrorFragmentShader[] = "#version 330 core\n"
                                        "\n"
                                        "layout(location = 0) out vec4 color;\n"
                                        "\n"
                                        "void main()\n"
                                        "{\n"
                                        "   color = vec4(1.0, 0.0, 1.0, 1.0);\n"
                                        "}\n";

/* Used to store the results of calling the Renderer::LoadShaders() function */
struct ShaderLoadResult {
    
    /* Error messages or an empty string if there's no errors */
    const std::string errors;

    /* Total number of files in the provided directory */
    const int32_t total_files;
    /* Total number of files with a shader extension */
    const int32_t total_shaders;
    /* Number of shaders successfully loaded */
    const int32_t shaders_loaded;
    /* Number of shaders that failed to loaded */
    const int32_t shaders_failed;

};

class Renderer {

    public:

        Renderer(SDL_Window* window, SDL_GLContext context);

        /* Loads shaders from files in a certain path to the renderer, returns a struct with the results (if something really bad happens "ShaderLoadResult.errors" will contain a string explaining that, otherwise it will be an empty string, if it's just shader files failing to load "errors" will be empty, but the number of failures will be reported in "ShaderLoadResult.shaders_failed", the failed shaders will be added to the renderer but will use Renderer.default_error_shader) */
        ShaderLoadResult LoadShaders(const std::string& path);

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