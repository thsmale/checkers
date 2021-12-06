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
#include "player.hpp"
#include "moves.hpp"
#include <SOIL2/SOIL2.h>
using namespace std;

static int selected_square = -1; 

//Human is object is extern so we can access it via this call back function
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        human.select_square(xpos, ypos);
    }
}

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
    board.set_board_vertices();
    GLfloat *vertex_buffer_data = board.get_board_vertices();
    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, board.get_board_vertices_size() * sizeof(*vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    
    board.color_squares();
    GLfloat* color_buffer_data = board.get_colors();
    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
    
    Player computer(0);
    computer.set_checkers();
    GLuint computer_vbo;
    vector<GLfloat> computer_buffer_data = computer.get_checker_vertices();
    glGenBuffers(1, &computer_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
    glBufferData(GL_ARRAY_BUFFER, computer_buffer_data.size() * sizeof(GLfloat), &computer_buffer_data[0], GL_STATIC_DRAW);
    
    human.set_checkers();
    GLuint player_vbo;
    vector<GLfloat> player_buffer_data = human.get_checker_vertices();
    glGenBuffers(1, &player_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, player_vbo);
    glBufferData(GL_ARRAY_BUFFER, player_buffer_data.size() * sizeof(player_buffer_data[0]), &player_buffer_data[0], GL_STATIC_DRAW);
    
    GLuint player_color_vbo;
    vector<GLfloat> player_color_buffer = human.get_checker_colors();
    glGenBuffers(1, &player_color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, player_color_vbo);
    glBufferData(GL_ARRAY_BUFFER, player_color_buffer.size() * sizeof(player_color_buffer[0]), &player_color_buffer[0], GL_STATIC_DRAW);
    
    board.set_board();
    board.print_board(); 
    pair<int, int> coordinates;
    vector<vector<char> > board_layout = board.get_board();
    vector<pair<int, int> > possible_moves;
    int cur_x = -1, cur_y = -1;
     

     
    // Create and compile our GLSL program from the shaders
    GLuint shader = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    GLuint computer_shader = LoadShaders( "computer.vertexshader", "computer.fragmentshader" );
    GLuint human_shader = LoadShaders( "player.vertexshader", "player.fragmentshader" );
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    
    // Check if the ESC key was pressed or the window was closed
    // Closed event loops, only handle events when you need to
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 ) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        //Highlight selected checker if there is one
        player_color_buffer = human.get_checker_colors();
        glBufferData(GL_ARRAY_BUFFER, player_color_buffer.size() * sizeof(player_color_buffer[0]), &player_color_buffer[0], GL_STATIC_DRAW);

        // 1st attribute buffer : board_vertices
        glUseProgram(shader);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //Layout in shader, dimensions, type, normalized?, stride, offset
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // 2nd attribute buffer : board_colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        coordinates = board.get_coordinates(human.get_selected_checker_square());
        if((coordinates.first != -1 && coordinates.second != -1) &&
           (coordinates.first != cur_x || coordinates.second != cur_y)) {
            /*
            computer.update_checkers();
            human.update_checkers();
            cout << "Computer" << endl;
            computer.print_checker_squares();
            cout << "Human" << endl; 
            human.print_checker_squares();
             */
            cur_x = coordinates.first;
            cur_y = coordinates.second;
            //Update selected checker buffer and possible movements
            board_layout = board.get_board();
            possible_moves = whereCanPieceMove(board.get_board(),
                                               coordinates.second,
                                               coordinates.first,
                                               false, false);
            printMoves(possible_moves); 
            board.color_squares(); 
            if(possible_moves.size() > 0) {
                board.color_possible_moves(possible_moves);
            }
            color_buffer_data = board.get_colors();
            glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

        }
         
        //glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

        //1st parameter must match the layout in the shader
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, board.get_board_vertices_size());
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
         
        // 3rd attribute buffer : computer
        glUseProgram(computer_shader);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
        //1st parameter must match the layout in the shader
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, computer_buffer_data.size());
        glDisableVertexAttribArray(2);
        
        // 4th attribute buffer : player
        glUseProgram(human_shader);
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, player_vbo);
        player_buffer_data = human.get_checker_vertices();
        glBufferData(GL_ARRAY_BUFFER, player_buffer_data.size() * sizeof(player_buffer_data[0]), &player_buffer_data[0], GL_STATIC_DRAW);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        //5th attribute buffer : player colors
        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, player_color_vbo);

        //1st parameter must match the layout in the shader
        //Colors
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, player_buffer_data.size());
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
         
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    /*
    // save a screenshot of your awesome OpenGL game engine, running at 1024x768
    int save_result = SOIL_save_screenshot
        (
            "/Users/tommysmale/classroom/csci580/projects/ogl/checkers/checker.bmp",
            SOIL_SAVE_TYPE_BMP,
            0, 0, 2048, 1536
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
    glDeleteBuffers(1, &computer_vbo);
    glDeleteBuffers(1, &player_vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
    glDeleteProgram(computer_shader);
    glDeleteProgram(human_shader);
    
    return 0;

}

