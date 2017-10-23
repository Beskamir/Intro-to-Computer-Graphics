//
// Setup functions to help the main function set things up.
// Ideally will make things cleaner in the main function
//

#ifndef ASSIGNMENT2_SETUP_H
#define ASSIGNMENT2_SETUP_H

//Setup glew
bool initGLEW() {
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        cout << "glew init failed" << endl;
        return false;
    }
    return true;
}

// Create a GLFWwindow object that we can use for GLFW's functions
bool setupWindow() {
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPSC 453 Assignment 2", nullptr, nullptr);

    //Check that window was properly setup
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

// Set options for GLFW such as telling it to use OpenGL 4.1
void setWindowHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

// Set the required callback functions
void setWindowCallbacks() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
#endif //ASSIGNMENT2_SETUP_H
