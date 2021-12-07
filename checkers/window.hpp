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
#include "board.hpp"
#include <vector>
using namespace std;

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

class Window {
public:
    Window();
    ~Window();
    GLFWwindow* get_window();
    GLuint& get_vao();
    GLuint& get_board_vbo();
    GLuint& get_board_colors_vbo(); 
    void set_board_vbo(GLfloat*, int);
    void set_board_colors_vbo(GLfloat*, int);
    void set_human_vbo(vector<GLfloat>);
    void set_human_colors_vbo(vector<GLfloat>);
    void set_computer_vbo(vector<GLfloat>);
    void set_computer_colors_vbo(vector<GLfloat>);
    void draw_board(Board &board);
    void draw_human_checkers(vector<GLfloat>, vector<GLfloat>);
    void draw_computer_checkers(vector<GLfloat>); 
private:
    GLFWwindow* window;
    GLuint vao; 
    GLuint board_vbo;
    GLuint board_colors_vbo;
    GLuint human_vbo;
    GLuint human_colors_vbo;
    GLuint computer_vbo;
    GLuint computer_colors_vbo;
};

#endif /* Window_hpp */
