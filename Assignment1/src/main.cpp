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
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

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

    //glUseProgram(mainProgram.id);
    //GLint vertexColorLocation = glGetUniformLocation(mainProgram.id,"vertexColor");
    //glUniform3f(vertexColorLocation,1.0f,0.5f,1.0f);

    vertData.genCurveData(targetDetail);
    vector<float> vertexMatrix;
    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window)) {

        if(drawTriangles){
            //vertexMatrix = vertData.getTris();
            vertexMatrix={0.5, 0.2, 0.2, 0.6, 0.8, 0.6, 0,0,-0,-1,-0.5,-0.5};
        }
        else{
            vertexMatrix = vertData.getCurve();
            vertData.getTris(lineSize);
        }

        VertexArray verts((int)vertexMatrix.size()/2);


        verts.addBuffer("v", 0, vertexMatrix);

        // render
        render(mainProgram, verts);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}


void render(Program &program, VertexArray &va) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.id);
    glBindVertexArray(va.id);
    glDrawArrays(drawingMode, 0, va.count);

    glBindVertexArray(0);
    glUseProgram(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key==GLFW_KEY_O&&action==GLFW_PRESS){
        drawingMode=GL_TRIANGLES;
        drawTriangles=true;
    }
    if(key==GLFW_KEY_L&&action==GLFW_PRESS){
        drawingMode=GL_LINES;
        drawTriangles=false;
    }
    if((key==GLFW_KEY_I&&action==GLFW_PRESS)&&(targetDetail<maxDetail)){
        targetDetail++;
        vertData.genCurveData(targetDetail);
    }
    if((key==GLFW_KEY_K&&action==GLFW_PRESS)&&(targetDetail>1)){
        targetDetail--;
        vertData.genCurveData(targetDetail);
    }
}
void window_size_callback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
}