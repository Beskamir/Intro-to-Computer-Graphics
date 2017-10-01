//
// Created by Sebastian on 9/28/2017.
//

#include "main.h"

int main(int argc, char *argv[]) {
    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return -1;
    }
    glfwSetErrorCallback([](int error, const char* description) {
        cout << "GLFW ERROR " << error << ":" << endl;
        cout << description << endl;
    });

    // Use OpenGL 4.1
    GLFWwindow *window = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1024, 1024, "CPSC 453 OpenGL Boilerplate", 0, 0);
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

#ifdef _WIN32
    // Intialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return -1;
    }
#endif

    Program mainProgram("data/vertex.glsl", "data/fragment.glsl");

    vector<float> vertexMatrix= { -0.9, -0.9,
                                  -0.9, 0.9,

                                  -0.9, 0.9,
                                  0.9, 0.9,

                                  0.9, 0.9,
                                  0.9, -0.9};



    VertexArray verts(6);
    verts.addBuffer("v", 0, vertexMatrix);

    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window)) {
        // render
        render(mainProgram, verts);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    cout << "The End" << endl;
    return 0;
}

void render(Program &program, VertexArray &va) {
    // clear screen to a dark grey colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Using lines first to get the generator to work

    glUseProgram(program.id);
    glBindVertexArray(va.id);
    glDrawArrays(GL_LINES, 0, va.count);

    glBindVertexArray(0);
    glUseProgram(0);
}