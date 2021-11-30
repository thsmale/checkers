//
//  main.cpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/12/21.
//

#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
// Checks which functions are available at runtime dependent on graphics card
#include <GL/glew.h>

// Include GLFW
// This handles window and keyboard
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <chrono>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include "board.hpp"
#include <stdlib.h>
#include <string.h>
#include "window.hpp"
#include <SOIL2/SOIL2.h>
using namespace std;

int main() {
    
    Window w;
    GLFWwindow *window = w.get_window();
        
    //Vertex array object
    //Stores links between the vbo and its attributes
    //Does not store vertex data but reference to VBO and how to retrieve the attributes
    //Any vertex buffers or element buffers declared before this will be ignored
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    Board board;
    board.set_board();

    GLfloat *vertex_buffer_data = board.get_board();
    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, board.get_board_size() * sizeof(*vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    
    board.set_color();
    for(int d = 0; d <= board.num_diagonals(); d++) {
        board.set_color(); 
        if(!board.color_diagonal(d))
            return -1;
    }
    GLfloat* color_buffer_data = board.get_colors();
    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
     
    // Create and compile our GLSL program from the shaders
    GLuint shader = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Layout in shader, dimensions, type, normalized?, stride, offset
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    //1st parameter must match the layout in the shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Check if the ESC key was pressed or the window was closed
    // Closed event loops, only handle events when you need to
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 ) {
        
        glUseProgram(shader);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, board.num_vertices());
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    /*
    // save a screenshot of your awesome OpenGL game engine, running at 1024x768
    int save_result = SOIL_save_screenshot
        (
            "random_color_drawings/random_color_rows.jpg",
            SOIL_SAVE_TYPE_JPG,
            0, 0, 1024, 768
        );
    if(save_result == 1) {
        cout << "Successful" << endl;
    }else {
        cerr << "Save file unsuccessful" << endl;
    }
    */
    
    // Cleanup VBO
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &color_buffer);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
    
    return 0;

}

