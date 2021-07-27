**IMPORTANT:** This project is currently a *work-in-progress*, and certain files will not be of final quality in terms of content and structure. Please keep this in mind when examining the source code.

---

# Introduction
An easy-to-understand 3D game engine, for *learning and experimenting*. Forking and hacking the code for your own project is also encouraged :)

<img src="docs/screenshot.png" width="50%">

**Note:** The engine is currently only buildable on Windows systems.

# Getting Started

1. Install [Visual Studio Community Edition](https://visualstudio.microsoft.com)
    - Remember to toggle the `Desktop development with C++` feature.
2. Install the [SDL runtime](https://www.libsdl.org/download-2.0.php):
    - Under `Runtime Binaries : Windows`, click the `32-bit Windows` link.
    - Extract the `SDL2.DLL` file to `C:\Windows`.
3. Install the [SDL SDK](https://www.libsdl.org/download-2.0.php):
    - Under `Development Libraries : Windows`, click the `Visual C++ 32/64-bit` link.
    - Extract the file to `C:\SDK`.
4. Install [GLEW](http://glew.sourceforge.net/):
    - Click the `Windows 32-bit and 64-bit` link.
    - Extract the file to `C:\SDK`
5. Ensure you have downloaded or cloned this repository, by clicking the green button at the top of this page.
6. Open the `easy-3d-engine.sln` file from your local repository.
6. From Visual Studio, click on the `Debug` menu, then `Start Without Debugging`.
7. Move around in the engine with the arrow keys, and press `ESC` to quit.

# Technical notes
* For simplicity we standardise on 32-bit for the build, and third-party libraries.
* As a starting point, we use the (now deprecated) Fixed Function Pipeline approach for OpenGL. We will move to the modern shader-driven approach as time permits.
