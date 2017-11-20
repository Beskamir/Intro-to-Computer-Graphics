//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
//#include "setup.h"
//#include "OpenGL_Program.h"

int window_width = 1024, window_height = 1024; // Window dimensions
OpenGL_Program openGL_program;

int main(int argc, char *argv[]) {
    GLFWwindow *window; // Create "global" glfw window

    if(!setupOpenGL(&window)){
        return -1;
    }
    setupWindowCallbacks(&window);

    //OpenGL_Program openGL_program(window);
    openGL_program.init_Program(window, &window_width, &window_height);
    openGL_program.mainRender();

    //Call the mainRender method which actually sets up the verts to be drawn
    //mainRender();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

bool setupOpenGL(GLFWwindow **window) {
// initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(window_width, window_height, "CPSC 453 Assignment 2", nullptr, nullptr);
    //Check that window was properly setup
    if (!*window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);

// Initialize GLEW if on windows
#ifdef _WIN32
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return false;
    }
#endif
    return true;
}

void setupWindowCallbacks(GLFWwindow **window) {
    glfwSetKeyCallback(*window, key_callback);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetScrollCallback(*window, scroll_callback);
    glfwSetMouseButtonCallback(*window, mouse_button_callback);
    glfwSetCursorPosCallback(*window, cursor_position_callback);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS){
        openGL_program.handleKeyPress(key);
    }

    openGL_program.moveCamera();

    if(action==GLFW_RELEASE){
        openGL_program.handleKeyRelease(key);
    }
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    float scalingSpeed=0.005f;
    if(yoffset>0){
        openGL_program.changeCameraSpeed(scalingSpeed);
    }
    if(yoffset<0){
        openGL_program.changeCameraSpeed(-scalingSpeed);
    }
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        openGL_program.finalizeTransformation();
        cout << "mouse down" <<endl;
    }
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    openGL_program.handleMouseMovement(xpos,ypos);

}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //float scaleX = float(window_width)/float(width);
    //float scaleY = float(window_height)/float(height);
    //openGL_program.scaleWithWindow(scaleX,scaleY);
    window_width=width;
    window_height=height;
}