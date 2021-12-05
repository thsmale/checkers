//
//  Window.hpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/20/21.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
// Checks which functions are available at runtime dependent on graphics card
#include <GL/glew.h>

// Include GLFW
// This handles window and keyboard
#include <GLFW/glfw3.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

class Window {
public:
    Window();
    ~Window();
    GLFWwindow* get_window();
private:
    GLFWwindow* window;
};

#endif /* Window_hpp */
