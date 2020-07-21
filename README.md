# GLGame (temporary title - will be changed along with this repository title later)
by Luís Eduardo Rozante <luis.eduardo.rozante@usp.br>

---

## Configuration

You will need some configuration before being able to compile the project, follow this instructions:

- Install [MSYS2](https://www.msys2.org/) and follow the instructions

- **For x86_64 target:**         
    
    - **(In the MSYS2 terminal)** Install dependencies:

        - MinGW-w64 tool-chain:

            > pacman -S mingw-w64-x86_64-toolchain

        - SDL2:

            > pacman -S mingw-w64-x86_64-SDL2

        - GLEW:

            > pacman -S mingw-w64-x86_64-glew

        - GLM:

            > pacman -S mingw-w64-x86_64-glm

  - Add `C:\msys64\mingw64\bin` to **PATH** (Assuming MSYS2 was installed on `C:\msys64`)

- **For x86 target:** 
  - Do the same as above but swap all occurrences of `mingw-w64-x86_64` for `mingw-w64-i686` and `C:\msys64\mingw64\bin` for `C:\msys64\mingw32\bin` in the **PATH**

**Note:** If MSYS2 was installed somewhere else other than `C:\msys64\`, you will need to not only correct the **PATH** accordingly but the `.vscode\c_cpp_properties.json` and `.vscode\launch.json` too.

---

## Useful links:

* Question about installing MinGW-w64 with MSYS2 (look for Steely Wing answer): https://stackoverflow.com/questions/30069830/how-to-install-mingw-w64-and-msys2
* How to setup SDL for OpenGL development with GLEW: https://www.turbonut.com/2019/03/18/opengl3-sdl2/
* Configuring dependencies for an OpenGL project (Uses GLFW instead of SDL): https://cis.gvsu.edu/~dulimarh/jkl/opengl/glew/glfw/glm/mingw/gllibs/
* OpenGL tutorial being followed (Uses GLFW instead of SDL, but the OpenGL bits after initialization should be the same): https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2