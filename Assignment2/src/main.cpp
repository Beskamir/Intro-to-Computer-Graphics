//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
#include "setup.h"

int main(int argc, char *argv[]) {
    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return -1;
    }
    setWindowHints();
    if (!setupWindow()){
        return -1;
    }
    setWindowCallbacks();
// Initialize GLEW if on windows only
#ifdef _WIN32
    if (!initGLEW()){
        return -1;
    }
#endif
    //Call the mainRender method which actually sets up the verts to be drawn
    mainRender();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

void mainRender(){
    // Define the viewport dimensions
    //glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Build and compile the shader programs
    Shader mShaders("data/vertex.glsl", "data/fragment.glsl");


    // Set up vertex data (and buffer(s)) and attribute pointers
    vector<float> vertices = {0.5f,  0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
                              0.5f, -0.5f, 0.0f,

                              -0.5f,  0.5f, 0.0f,
                              0.5f,  0.5f, 0.0f,
                              -0.5f, -0.5f, 0.0f,
    };
    vector<float> colors={1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 1.0f,

                          1.0f, 1.0f, 0.0f,
                          1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f,
    };

    vector<float> texture={1.0f, 1.0f,
                           1.0f, 0.0f,
                           0.0f, 0.0f,

                           0.0f, 1.0f,
                           1.0f, 1.0f,
                           1.0f, 0.0f,
    };

    VertexArray verts((int)vertices.size()/3);
    verts.addBuffer("v", 0, vertices);
    verts.addBuffer("c", 1, colors);
    verts.addBuffer("t", 2, texture);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        renderToScreen(mShaders, verts);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
}

void renderToScreen(Shader mShaders, VertexArray &verts) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    mShaders.Use();
    glBindVertexArray(verts.id);
    glDrawArrays(GL_TRIANGLES, 0, verts.count);
    glBindVertexArray(0);

    //glUseProgram(program.id);
    //glBindVertexArray(va.id);
    //glDrawArrays(drawingMode, 0, va.count);

    glBindVertexArray(0);
    glUseProgram(0);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}