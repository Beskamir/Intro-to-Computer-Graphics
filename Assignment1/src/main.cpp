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
    window = glfwCreateWindow(window_width, window_height, "CPSC 453 OpenGL Boilerplate", 0,0);
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);

#ifdef _WIN32
    // Intialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return -1;
    }
#endif

    // Main loop for once all the stuff is setup
    loopRender(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    cout << "The End" << endl;
    return 0;
}

void loopRender(GLFWwindow *window){

    Program mainProgram("data/vertex.glsl", "data/fragment.glsl");



    vector<float> vertexMatrix= { -0.9, -0.9,
                                  -0.9, 0.9,

                                  -0.9, 0.9,
                                  0.9, 0.9,

                                  0.9, 0.9,
                                  0.9, -0.9};

    //vector<float> vertexMatrix = {1.0,0.0,-1.0,0,0,1.0};


    VertexArray verts(6);
    verts.addBuffer("v", 0, vertexMatrix);

    //glUseProgram(mainProgram.id);
    //GLint vertexColorLocation = glGetUniformLocation(mainProgram.id,"vertexColor");
    //glUniform3f(vertexColorLocation,1.0f,0.5f,1.0f);


    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window)) {
        // render
        render(mainProgram, verts);

        glfwSwapBuffers(window);

        glfwWaitEvents();
    }
}


void render(Program &program, VertexArray &va) {
    // clear screen to a dark grey colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.id);
    glBindVertexArray(va.id);
    glDrawArrays(drawingMode, 0, va.count);

    glBindVertexArray(0);
    glUseProgram(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9){
    //    printf("%d ",key);
    //}
    switch(key){
        case GLFW_KEY_O:
            drawingMode=GL_TRIANGLE_STRIP;
            break;
        case GLFW_KEY_P:
            drawingMode=GL_POINTS;
            break;
        case GLFW_KEY_L:
            drawingMode=GL_LINES;
            break;
        default:
            break;
    }
}
//void window_focus_callback(GLFWwindow* window, int focused)
//{
//    if (focused)
//    {
//        // The window gained input focus
//    }
//    else
//    {
//        // The window lost input focus
//    }
//}
