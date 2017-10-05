//
// Main and render functions based on boilerplate
// Primary resources used:
// https://learnopengl.com
// http://www.glfw.org/docs/latest/input_guide.html
// http://www.glfw.org/docs/latest/window_guide.html
//
// As mentioned in the boilerplate the #ifdef _WIN32 bit was provided by Scott/Blake
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

vector<float> getVertsOnly(vector<vector<float>> matrixData){
    vector<float> vertData{};
    for (int i = 0; i < matrixData.size(); ++i) {
        vertData.push_back(matrixData[i][0]);
        vertData.push_back(matrixData[i][1]);
    }
    return vertData;
}
vector<float> getColorsOnly(vector<vector<float>> matrixData){
    vector<float> colorData{};
    for (int i = 0; i < matrixData.size(); ++i) {
        colorData.push_back(matrixData[i][2]);
        colorData.push_back(matrixData[i][3]);
        colorData.push_back(matrixData[i][4]);
    }
    return colorData;
}

void loopRender(GLFWwindow *window){

    Program mainProgram("data/vertex.glsl", "data/fragment.glsl");

    Matrix vertData;

    vertData.genCurveData(targetDetail);

    vector<vector<float>> vertexColorMatrix;
    vector<float> vertexMatrix;
    vector<float> colorMatrix;

    vertexColorMatrix = vertData.getTris(lineSize);
    vertexMatrix = getVertsOnly(vertexColorMatrix);
    colorMatrix = getColorsOnly(vertexColorMatrix);

    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window)) {
        if(recalculate){
            vertData.genCurveData(targetDetail);
            recalculate = false;
            cout << "Hilbert curve with detail "<< targetDetail<<" generated."<<endl;
        }

        if(drawTriangles){
            vertexColorMatrix = vertData.getTris(lineSize);
            vertexMatrix = getVertsOnly(vertexColorMatrix);
            colorMatrix = getColorsOnly(vertexColorMatrix);
        }

        else{
            vertexColorMatrix = vertData.getCurve();
            vertexMatrix = getVertsOnly(vertexColorMatrix);
            colorMatrix = getColorsOnly(vertexColorMatrix);
        }

        VertexArray verts((int)vertexMatrix.size()/2);

        verts.addBuffer("v", 0, vertexMatrix);
        verts.addBuffer("c", 1, colorMatrix);

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
    if(key==GLFW_KEY_O&&action==GLFW_PRESS&&!drawTriangles){
        drawingMode=GL_TRIANGLES;
        drawTriangles=true;
        cout << "Drawing using triangles" << endl;
    }
    if(key==GLFW_KEY_L&&action==GLFW_PRESS&&drawTriangles){
        drawingMode=GL_LINES;
        drawTriangles=false;
        cout << "Drawing using lines" << endl;
    }
    if((key==GLFW_KEY_I&&action==GLFW_PRESS)&&(targetDetail<maxDetail)){
        targetDetail++;
        recalculate = true;
        cout << "Increasing detail to: " << targetDetail << endl;
    }
    if((key==GLFW_KEY_K&&action==GLFW_PRESS)&&(targetDetail>1)){
        targetDetail--;
        recalculate = true;
        cout << "Decreasing detail to: " << targetDetail << endl;
    }
}
void window_size_callback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
}