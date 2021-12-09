//
//  Window.cpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/20/21.
//

#include "window.hpp"

Window::Window() {
    
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    //Create and Configure Window
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    
    window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, "Checkers", nullptr, nullptr);
    
    if( window == nullptr ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

}

Window::~Window() {
    glDeleteBuffers(1, &board_vbo);
    glDeleteBuffers(1, &board_colors_vbo);
    glDeleteBuffers(1, &checkers_vertices_buffer);
    glDeleteBuffers(1, &checkers_colors_buffer);
    glDeleteBuffers(1, &computer_colors_vbo);
    glDeleteBuffers(1, &computer_vbo);
    glDeleteBuffers(1, &human_vbo);
    glDeleteBuffers(1, &human_colors_vbo); 
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
}

GLFWwindow* Window::get_window() {
    return window;
}

GLuint& Window::get_vao() {
    return vao;
}

GLuint& Window::get_board_vbo() {
    return board_vbo;
}

GLuint& Window::get_board_colors_vbo() {
    return board_colors_vbo; 
}

void Window::set_board_vbo(GLfloat *vertices, int size) {
    glGenBuffers(1, &board_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, board_vbo);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(*vertices), vertices, GL_STREAM_DRAW);
}

void Window::set_board_colors_vbo(GLfloat* vertices, int size) {
    glGenBuffers(1, &board_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, board_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(*vertices), vertices, GL_STREAM_DRAW);
}

void Window::set_checkers_buffers(vector<GLfloat> vertices, vector<GLfloat> colors) {
    glGenBuffers(1, &checkers_vertices_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, checkers_vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    
    glGenBuffers(1, &checkers_colors_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, checkers_colors_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STREAM_DRAW);
}

void Window::set_human_vbo(vector<GLfloat> vertices) {
    glGenBuffers(1, &human_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, human_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);

}

void Window::set_human_colors_vbo(vector<GLfloat> vertices) {
    glGenBuffers(1, &human_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, human_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
}

void Window::set_computer_vbo(vector<GLfloat> vertices) {
    glGenBuffers(1, &computer_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
}

void Window::set_computer_colors_vbo(vector<GLfloat> vertices) {
    glGenBuffers(1, &computer_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, computer_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
}

void Window::draw_board(int board_size, GLfloat *colors, int colors_size) {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, board_vbo);
    //Layout in shader, dimensions, type, normalized?, stride, offset
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // 2nd attribute buffer : board_colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, board_colors_vbo);
    //Board color buffer is called if we select a new checker or move checker piece
    glBufferData(GL_ARRAY_BUFFER, colors_size * sizeof(*colors), colors, GL_STREAM_DRAW);
    //1st parameter must match the layout in the shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, board_size);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Window::draw_checkers(vector<GLfloat> vertices, vector<GLfloat> colors) {
    //glGenBuffers(1, &checkers_vertices_buffer);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, checkers_vertices_buffer);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // 2nd attribute buffer : checker colors
    //glGenBuffers(1, &checkers_colors_buffer);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, checkers_colors_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STREAM_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

void Window::draw_human_checkers(vector<GLfloat> vertices) {
    glGenBuffers(1, &human_vbo);
    glEnableVertexAttribArray(5);
    glBindBuffer(GL_ARRAY_BUFFER, human_vbo);
    //Layout in shader, dimensions, type, normalized?, stride, offset
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(5);
    //glDeleteBuffers(1, &human_vbo);

}

void Window::draw_human_checkers(vector<GLfloat> vertices, vector<GLfloat> colors) {
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, human_vbo);
    //Layout in shader, dimensions, type, normalized?, stride, offset
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, human_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STREAM_DRAW);
    //1st parameter must match the layout in the shader
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
}

void Window::draw_computer_checkers(vector<GLfloat> vertices) {
    glGenBuffers(1, &computer_vbo);
    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, computer_vbo);
    //Layout in shader, dimensions, type, normalized?, stride, offset
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(4);
    //glDeleteBuffers(1, &computer_vbo);

}
