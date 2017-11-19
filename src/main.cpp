//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
//#include "setup.h"
//#include "OpenGL_Program.h"

int main(int argc, char *argv[]) {
    if(!setupOpenGL()){
        return -1;
    }

    setupWindowCallbacks();

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

bool setupOpenGL() {
// initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "CPSC 453 Assignment 2", nullptr, nullptr);
    //Check that window was properly setup
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

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

void setupWindowCallbacks() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS){
        if (key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    //if(yoffset>0){
    //    scaleFactor+=scalingSpeed;
    //}
    //if(yoffset<0){
    //    scaleFactor-=scalingSpeed;
    //}
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
    //    mousePressed=true;
    //    Position currentMouse;
    //    double xpos, ypos;
    //    glfwGetCursorPos(window, &xpos, &ypos);
    //    currentMouse.x=(float)xpos;
    //    currentMouse.y=(float)ypos;
    //    lastMousePos=currentMouse;
    //    //cout << "mouse down" <<endl;
    //}
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
    //    mousePressed=false;
    //    //cout << "mouse up" <<endl;
    //}
    //if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && showControlPoints){
    //}
}


//Position getMouseLocation() {
//    double xpos,ypos;
//    glfwGetCursorPos(window, &xpos,&ypos);
//    Position mouseLocation;
//    mouseLocation.x=(2.0f*((float)(xpos)/(window_width)))-1.0f;
//    mouseLocation.y=1.0f-(2.0f*((float)(ypos)/(window_height)));
//    return mouseLocation;
//}


void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    //if(mousePressed){
    //    Position currentMouse;
    //    currentMouse.x=(float)xpos;
    //    currentMouse.y=(float)ypos;
    //
    //    Position pastMousePos = lastMousePos;
    //
    //    translate.x+=2/scaleFactor*(-pastMousePos.x+currentMouse.x)/window_width;
    //    translate.y+=2/scaleFactor*(pastMousePos.y-currentMouse.y)/window_height;
    //
    //    //Update mouse last positioning
    //    lastMousePos=currentMouse;
    //}
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    window_width=width;
    window_height=height;
}