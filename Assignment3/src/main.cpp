//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
//#include "setup.h"
//#include "OpenGL_Program.h"

int main(int argc, char *argv[]) {
    //cout << argv[1]<<endl;
    if (argc < 1) {
        printf("Usage: <config file> or <model texture1 texture2 ...>\n");
        return -1;
    }
    //If successful store commandline args in a vector of strings
    vector<string> commandlineContents;
    //cout<<argv[1]<<endl;
    //cout<<argc<<endl;
    for (int i = 1; i < argc; ++i) {
        string element = argv[i];
        commandlineContents.push_back(element);
    }

    GLFWwindow *window; // Create "global" glfw window

    if(!setupOpenGL(&window)){
        return -1;
    }
    // Cull triangles which normal is not towards the camera.
    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
    glEnable(GL_CULL_FACE);
    //zbuffer enabled thanks to: https://stackoverflow.com/questions/1046029/depth-buffer-in-opengl
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(1.0f);
    //glDepthFunc(GL_LESS);

    //OpenGL_Program openGL_program(window);
    //give OpenGL_Program the things it needs to operate
    openGL_program.init_Program(window, &window_width, &window_height);
    openGL_program.commandLineArgs(commandlineContents);

    setupWindowCallbacks(&window);
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
    //glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
    glfwSetKeyCallback(*window, key_callback);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetScrollCallback(*window, scroll_callback);
    glfwSetMouseButtonCallback(*window, mouse_button_callback);
    glfwSetCursorPosCallback(*window, cursor_position_callback);
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    openGL_program.handleKeyCallback(key, action);
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //cout << xoffset << ":"<< yoffset<<endl;
    //float scalingSpeed=0.005f;
    openGL_program.handleScrollCallback(yoffset);
    //if(yoffset>0){
    //    openGL_program.changeCameraSpeed(scalingSpeed);
    //}
    //if(yoffset<0){
    //    openGL_program.changeCameraSpeed(-scalingSpeed);
    //}
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        openGL_program.handleMouseClick();
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