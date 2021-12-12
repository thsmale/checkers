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

#define COMPUTER 0
#define HUMAN 1

static bool human_turn = false;
static bool go = false;


//Human is object is extern so we can access it via this call back function
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        go = true;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(human_turn)
            human_turn = human.select_square(xpos, ypos);
    }
}

int main() {
    
    Window w;
    GLFWwindow *window = w.get_window();
    
    // Create and compile our GLSL program from the shaders
    GLuint board_shader = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    GLuint computer_shader = LoadShaders( "computer.vertexshader", "computer.fragmentshader" );
    GLuint human_shader = LoadShaders( "player.vertexshader", "player.fragmentshader" );
    //GLuint checkers_shader = LoadShaders( "checkers.vertexshader", "checkers.fragmentshader" );

    //Vertex array object
    //Stores links between the vbo and its attributes
    //Does not store vertex data but reference to VBO and how to retrieve the attributes
    //Any vertex buffers or element buffers declared before this will be ignored
    GLuint vao = w.get_vao();

    //Set up the game
    Board board;
    board.set_board_vertices();
    w.set_board_vbo(board.get_board_vertices(), board.get_board_vertices_size());
    board.set_colors();
    board.color_squares();
    w.set_board_colors_vbo(board.get_colors(), board.get_colors_size());
    
    Player computer(COMPUTER);
    computer.set_checkers();
    w.set_computer_vbo(computer.get_checker_vertices());
    
    human.set_checkers();
    w.set_human_vbo(human.get_checker_vertices());
    
    board.set_board();
    ABP abp;
    int turn = HUMAN;
    Player *temp;
     
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    // Check if the ESC key was pressed or the window was closed
    // Closed event loops, only handle events when you need to
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 ) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(board_shader);
        w.draw_board(board.get_board_vertices_size(), board.get_colors(), board.get_colors_size());

        glUseProgram(computer_shader);
        w.draw_computer_checkers(computer.get_checker_vertices());
        //computer.get_checker_colors());
        
        glUseProgram(human_shader);
        w.draw_human_checkers(human.get_checker_vertices());
        //Highlight selected checker if there is one
        if(go) {
            string player;
            if(turn == HUMAN) {
                cout << "Human turn " << endl;
                temp = &human;
                player = "human";
            }else {
                cout << "Computer turn" << endl;
                temp = &computer;
                player = "computer";
            }
            // Alpha-Beta Pruning min max implementation
            vector<Checker*> checkers = temp->get_checkers();
            pair<int,int> move = abp.optimal_move(board, checkers);
            cout << "Moving " << player << " checker at square " << move.first << " to " << move.second << endl;
            temp->move_checker(move.first, move.second);
                
            computer.update_checkers();
            human.update_checkers();
            board.print_board();
            cout << "Human checkers" << endl;
            human.print_checker_squares();
            cout << "Computer checkers"<<endl;
            computer.print_checker_squares(); 
            if(turn == HUMAN) {
                turn = COMPUTER;
            }else {
                turn = HUMAN;
            }
            go = false;
            
            //w.set_checkers_buffers(human.get_checker_vertices(), human.get_checker_colors());

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glUseProgram(board_shader);
            w.draw_board(board.get_board_vertices_size(), board.get_colors(), board.get_colors_size());

            glUseProgram(computer_shader);
            w.draw_computer_checkers(computer.get_checker_vertices());
            //computer.get_checker_colors());
            
            glUseProgram(human_shader);
            w.draw_human_checkers(human.get_checker_vertices());
            
            glfwSwapBuffers(window);
        

        }
        glfwPollEvents();
    }
    
    // save a screenshot of your awesome OpenGL game engine, running at 1024x768
    
    int save_result = SOIL_save_screenshot
        (
            "/Users/tommysmale/classroom/csci580/projects/ogl/checkers/board_state.bmp",
            SOIL_SAVE_TYPE_BMP,
            0, 0, 2048, 1536
        );
    if(save_result == 1) {
        cout << "Successful" << endl;
    }else {
        cerr << "Save file unsuccessful" << endl;
    }
     
     
    
    // Cleanup VBO
    glDeleteProgram(board_shader);
    glDeleteProgram(computer_shader);
    glDeleteProgram(human_shader);
    
    return 0;

}

