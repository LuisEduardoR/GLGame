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

/* Loads shaders from files in a certain path to the renderer, returns a struct with the results (if something really bad happen "ShaderLoadResult.errors" will contain a string explaining what happened, otherwise it will be an empty string, if it's just shader files failing to load "errors" will be empty, but the number of failures will be reported in "ShaderLoadResult.shaders_failed") */
ShaderLoadResult Renderer::LoadShaders(const std::string& path) {

    int32_t total_files = 0;
    int32_t total_shaders = 0;
    int32_t successfull_shaders = 0;

    // TODO: check for exceptions when handling the directory and files

    /* Checks for files in the path provided */
    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        total_files++;

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

    return ShaderLoadResult { "", total_files, total_shaders, successfull_shaders, total_shaders - successfull_shaders };

}

/* Requests a shader to the renderer by name (returns the Renderer.default_error_shader if no shader is found, this shader is created by the renderer class constructor using kErrorVertexShader and kErrorFragmentShader) */
uint32_t Renderer::RequestShader(const std::string& name) {

    auto iter = this->shaders.find(name);
    if(iter != this->shaders.end())
        return (*iter).second;

    return this->default_error_shader;

}

/* Checks if a shader is the Renderer.default_error_shader */
bool Renderer::IsErrorShader(uint32_t shader) {
    return (shader == this->default_error_shader);
}