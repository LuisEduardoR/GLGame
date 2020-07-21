#include "renderer.hpp"

#include <map>
#include <string>
#include <iostream>
#include <filesystem>

#include <SDL2/SDL.h>

#include "shader.hpp"

Renderer::Renderer(SDL_Window* window, SDL_GLContext context) {

    this->window = window;
    this->context = context;

    this->default_error_shader = CreateShader(kErrorVertexShader, kErrorFragmentShader);

}

/* Loads game shaders from a files in a certain path (returns a pair with the number of shaders loaded successfully and the total number of shaders found) */
std::pair<uint32_t,uint32_t> Renderer::LoadShaders(const std::string& path) {

    uint32_t successfull_shaders = 0;
    uint32_t total_shaders = 0;

    /* Checks for files in the path provided */
    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        std::string fullpath = entry.path().string();
        std::string filename = entry.path().filename().string();
        std::string extension = entry.path().extension().string();

        /* Ignores non .glsl files */
        if(extension.compare(kShaderExtension) != 0)
            continue;

        total_shaders++;

        /* Loads the shader for this entry */
        uint32_t shader = ParseShader(fullpath);
        
        /* If the shader could not be created uses the default error shader */
        if(!shader) {
            this->shaders.insert(std::make_pair(filename.substr(0, filename.length() - extension.length()), default_error_shader));
            continue;
        }

        /* Adds the shader to the map with the key equals to the filename without extension */
        this->shaders.insert(std::make_pair(filename.substr(0, filename.length() - extension.length()), shader));
        successfull_shaders++;

    }

    return std::make_pair(successfull_shaders, total_shaders);

}

/* Requests a shader  to the renderer by name (returns the default_error_shader if no shader is found this shader is created by the renderer class constructor using kErrorVertexShader and )kErrorFragmentShader */
uint32_t Renderer::RequestShader(const std::string& name) {

    auto iter = this->shaders.find(name);
    if(iter != this->shaders.end())
        return (*iter).second;

    return this->default_error_shader;

}

/* Checks if a shader is the default_error_shader */
bool Renderer::IsErrorShader(uint32_t shader) {
    return (shader == this->default_error_shader);
}