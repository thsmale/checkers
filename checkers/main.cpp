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
#include "additionalMoves.hpp"
#include <SOIL2/SOIL2.h>
#include "abp.hpp"
using namespace std;

//Human is object is extern so we can access it via this call back function
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        if(human.get_turn())
            human.select_square(xpos, ypos);
    }
}

int main() {
    

    
    Window w;
    GLFWwindow *window = w.get_window();
    
    // Create and compile our GLSL program from the shaders
    GLuint board_shader = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    GLuint computer_shader = LoadShaders( "computer.vertexshader", "computer.fragmentshader" );
    GLuint human_shader = LoadShaders( "player.vertexshader", "player.fragmentshader" );

    //Vertex array object
    //Stores links between the vbo and its attributes
    //Does not store vertex data but reference to VBO and how to retrieve the attributes
    //Any vertex buffers or element buffers declared before this will be ignored
    
    /*
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
     */
    
    GLuint vao = w.get_vao();

    Board board;
    board.set_board_vertices();
    GLfloat *vertex_buffer_data = board.get_board_vertices();
    w.set_board_vbo(vertex_buffer_data, board.get_board_vertices_size());
    GLuint board_vbo = w.get_board_vbo();
    // Create a Vertex Buffer Object and copy the vertex data to it
    

    /*
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, board.get_board_vertices_size() * sizeof(*vertex_buffer_data), vertex_buffer_data, GL_DYNAMIC_DRAW);
     */
     
    board.color_squares();
    GLfloat* color_buffer_data = board.get_colors();
    w.set_board_colors_vbo(color_buffer_data, board.get_colors_size());
    GLuint board_colors_vbo = w.get_board_colors_vbo();
    
    /*
    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_DYNAMIC_DRAW);
     */
    
    Player computer(0);
    computer.set_checkers();
    GLuint computer_vbo;
    w.set_computer_vbo(computer.get_checker_vertices());
    /*
    glGenBuffers(1, &computer_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
    glBufferData(GL_ARRAY_BUFFER, computer_buffer_data.size() * sizeof(GLfloat), &computer_buffer_data[0], GL_DYNAMIC_DRAW);
     */
    
    human.set_checkers();
    GLuint player_vbo;
    vector<GLfloat> player_buffer_data = human.get_checker_vertices();
    w.set_human_vbo(player_buffer_data);
    /*
    glGenBuffers(1, &player_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, player_vbo);
    glBufferData(GL_ARRAY_BUFFER, player_buffer_data.size() * sizeof(player_buffer_data[0]), &player_buffer_data[0], GL_DYNAMIC_DRAW);
     */
    
    GLuint player_color_vbo;
    vector<GLfloat> player_color_buffer = human.get_checker_colors();
    w.set_human_colors_vbo(player_buffer_data);
    /*
    glGenBuffers(1, &player_color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, player_color_vbo);
    glBufferData(GL_ARRAY_BUFFER, player_color_buffer.size() * sizeof(player_color_buffer[0]), &player_color_buffer[0], GL_STATIC_DRAW);
     */
    
    board.set_board();
    pair<int, int> coordinates;
    vector<vector<char> > board_layout = board.get_board();
    vector<pair<int, int> > possible_moves;
    int cur_x = -1, cur_y = -1;
    ABP Algo;
     
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    



    
    // Check if the ESC key was pressed or the window was closed
    // Closed event loops, only handle events when you need to
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 ) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Highlight selected checker if there is one
        /*
        player_color_buffer = human.get_checker_colors();
        glBufferData(GL_ARRAY_BUFFER, player_color_buffer.size() * sizeof(player_color_buffer[0]), &player_color_buffer[0], GL_DYNAMIC_DRAW);
         */
        
        glUseProgram(board_shader);
        w.draw_board(board);
        
        glUseProgram(human_shader);
        w.draw_human_checkers(human.get_checker_vertices(), human.get_checker_colors());
    
        glUseProgram(computer_shader);
        w.draw_computer_checkers(computer.get_checker_vertices());


        /*
        glUseProgram(shader);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //Layout in shader, dimensions, type, normalized?, stride, offset
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        // 2nd attribute buffer : board_colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        //Board color buffer is called if we select a new checker or move checker piece
        glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(GLfloat), board.get_board_vertices(), GL_DYNAMIC_DRAW);
        //1st parameter must match the layout in the shader
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, board.get_board_vertices_size());
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        */

        /*
        // 1st attribute buffer : board_vertices
        glUseProgram(board_shader);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, board_vbo);
        //Layout in shader, dimensions, type, normalized?, stride, offset
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        // 2nd attribute buffer : board_colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, board_colors_vbo);
        //Board color buffer is called if we select a new checker or move checker piece
        coordinates = board.get_coordinates(human.get_selected_checker_square());
        //Need to separate clicking square to see moves and actually moving a piece
        if(coordinates.first != cur_x || coordinates.second != cur_y) {
            cur_x = coordinates.first;
            cur_y = coordinates.second;
            //If cur_x && cur_y == -1 then we just moved a square
            //else we are selecting a square
            //Update selected checker buffer and possible movements
            board_layout = board.get_board();
            possible_moves = whereCanPieceMove(board.get_board(),
                                               coordinates.second,
                                               coordinates.first,
                                               false, false);
            board.color_squares();
            if(possible_moves.size() > 0) {
                board.color_possible_moves(possible_moves);
            }
            color_buffer_data = board.get_colors();
            glBufferData(GL_ARRAY_BUFFER, board.get_colors_size() * sizeof(*color_buffer_data), color_buffer_data, GL_DYNAMIC_DRAW);
        }
        //1st parameter must match the layout in the shader
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, board.get_board_vertices_size());
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
         */
        /*
         
        // 4th attribute buffer : player
        human.update_checkers();
        glUseProgram(human_shader);
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, player_vbo);
        player_buffer_data = human.get_checker_vertices();
        glBufferData(GL_ARRAY_BUFFER, player_buffer_data.size() * sizeof(player_buffer_data[0]), &player_buffer_data[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        //5th attribute buffer : player colors
        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, player_color_vbo);
        player_color_buffer = human.get_checker_colors();
        glBufferData(GL_ARRAY_BUFFER, player_color_buffer.size() * sizeof(player_color_buffer[0]), &player_color_buffer[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, player_buffer_data.size());
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        
        // 3rd attribute buffer : computer
        computer.update_checkers();
        glUseProgram(computer_shader);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
        computer_buffer_data = computer.get_checker_vertices();
        glBufferData(GL_ARRAY_BUFFER, computer_buffer_data.size() * sizeof(GLfloat), &computer_buffer_data[0], GL_DYNAMIC_DRAW);
        //1st parameter must match the layout in the shader
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, computer_buffer_data.size());
        glDisableVertexAttribArray(2);
         
        if(!human.get_turn()) {
            // Alpha-Beta Pruning min max implementation
            Checker* chosen_checker;
            vector<std::pair<std::pair<int, int>, int> > chosen_moves;
            int maxEval = 0;

            vector<Checker*> checkers_ref = computer.get_checkers();

            for (Checker* checker : checkers_ref) {
                pair<int, int> coords = board.get_coordinates(checker->square);
                vector<std::pair<std::pair<int, int>, int> > moves = possible_moves_weights(board.get_board(), coords.second, coords.first, checker->white, checker->king);

                if (moves.size() > 0) {
                    int eval = Algo.minmax(board, checker->square, Algo.getHighestScore(moves), INT_MIN, INT_MAX, true, checker->king);

                    if (eval > maxEval) {
                        maxEval = eval;
                        chosen_checker = checker;
                        chosen_moves = moves;
                    }
                }
            }
            
            if (chosen_checker != nullptr) { // just in case (for now?)
                //cout << "AI chooses to move checker from square " << chosen_checker->square << endl;
                std::pair<int, int> optimal_move;
                int highest = 0;

                for (std::pair<std::pair<int, int>, int> move : chosen_moves) {
                    if (move.second > highest) {
                        highest = move.second;
                        optimal_move = move.first;
                    }
                }
                int old_new_square = board.get_square(make_pair(optimal_move.second, optimal_move.first));
                computer.move_checker(chosen_checker->square, old_new_square);
                
            }
            human.set_turn();
        }
         */
         
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
    /*
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &color_buffer);
    glDeleteBuffers(1, &computer_vbo);
    glDeleteBuffers(1, &player_vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
    glDeleteProgram(computer_shader);
    glDeleteProgram(human_shader);
     */
    
    return 0;

}

