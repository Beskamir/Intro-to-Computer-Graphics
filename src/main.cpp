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
        if(key==GLFW_KEY_F){
            mouseLocLast = getMouseLocation();
            fpsMode = !fpsMode;
            movement= {false,false,false,false};
        }
        if(!fpsMode){
            if(key==GLFW_KEY_S){
                mouseLocLast = getMouseLocation();
                initalMouseDistance = getMouseDistance(mouseLocLast);
                scaleMode = !scaleMode;
            }
            if(key==GLFW_KEY_R){
                mouseLocLast = getMouseLocation();
                rotateMode = !rotateMode;
                useAxis={true,true,true};
            }
            if(rotateMode){
                //Lock to one of the following axis
                if(key==GLFW_KEY_X){
                    useAxis={true,false,false};
                }
                if(key==GLFW_KEY_Y){
                    useAxis={false,true,false};
                }
                if(key==GLFW_KEY_Z){
                    useAxis={false,false,true};
                }
            }
            if(key==GLFW_KEY_C){
                //Center view on object
                int scaleX = 1;
                int scaleY = 1;
                openGL_program.centerView(scaleX,scaleY);
            }
        }
        if(key==GLFW_KEY_W){
            movement.forward = true;
            movement.backward = false;
        }
        if(key==GLFW_KEY_S){
            movement.backward = true;
            movement.forward = false;
        }
        if(key==GLFW_KEY_A){
            movement.left = true;
            movement.right = false;
        }
        if(key==GLFW_KEY_D){
            movement.right = true;
            movement.left = false;
        }
    }
    if(fpsMode){
        openGL_program.moveCamera(movement.forward, movement.backward, movement.right, movement.left);
    }
    if(action==GLFW_RELEASE){
        cout<<key<<endl;
        if(key==GLFW_KEY_W){
            movement.forward = false;
        }
        if(key==GLFW_KEY_S){
            movement.backward = false;
        }
        if(key==GLFW_KEY_A){
            movement.left = false;
        }
        if(key==GLFW_KEY_D){
            movement.right = false;
        }
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



ScreenPosition getMouseLocation() {
    double xpos,ypos;
    glfwGetCursorPos(window, &xpos,&ypos);
    ScreenPosition mouseLocation={(2.0f*((float)(xpos)/(window_width)))-1.0f,
                                  1.0f-(2.0f*((float)(ypos)/(window_height)))};
    return mouseLocation;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if(fpsMode){
        //mouseLocCurrent=getMouseLocation();
        //teleportMouse(xpos,ypos);
        mouseLocCurrent = getMouseLocation();
        openGL_program.rotateView(mouseLocCurrent.x-mouseLocLast.x,
                                  mouseLocCurrent.y-mouseLocLast.y);
        glfwSetCursorPos(window,window_width/2,window_height/2);
        //mouseLocCurrent = getMouseLocation();
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = getMouseLocation();
    }
    if(scaleMode){
        teleportMouse(xpos,ypos);
        mouseLocCurrent = getMouseLocation();
        double scaleFactor = getMouseDistance(mouseLocCurrent)/initalMouseDistance;
        cout<<scaleFactor<<endl;
        vec3 scaleVec(scaleFactor,scaleFactor,scaleFactor);
        openGL_program.scaleModel(scaleVec);
        //glfwSetCursorPos(window,window_width/2,window_height/2);
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = mouseLocCurrent;
    }
    if(rotateMode){
        mouseLocCurrent = getMouseLocation();
        //openGL_program.rotateModel(mouseLocCurrent.x-mouseLocLast.x,
        //                          mouseLocCurrent.y-mouseLocLast.y);
        //cout<<mouseLocCurrent.x<<":"<<mouseLocCurrent.y<<endl;
        //cout<<mouseLocLast.x<<":"<<mouseLocLast.y<<endl;
        mouseLocLast = mouseLocCurrent;
    }
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

double getMouseDistance(ScreenPosition mousePosition) {
    return sqrt(pow(mousePosition.x,2)+pow(mousePosition.y,2));
}

void teleportMouse(double xpos, double ypos) {
    mouseLocCurrent=getMouseLocation();
    if (mouseLocCurrent.x < -0.75) {
        glfwSetCursorPos(window, ((0.7 + 1.0) / 2) * window_width, ypos);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.x > 0.75) {
        glfwSetCursorPos(window, ((-0.7 + 1.0) / 2) * window_width, ypos);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.y < -0.75) {
        glfwSetCursorPos(window, xpos, ((0.7 - 1.0) / 2) * -window_height);
        mouseLocLast = getMouseLocation();
    }
    if (mouseLocCurrent.y > 0.75) {
        glfwSetCursorPos(window, xpos, ((-0.7 - 1.0) / 2) * -window_height);
        mouseLocLast = getMouseLocation();
    }
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //float scaleX = float(window_width)/float(width);
    //float scaleY = float(window_height)/float(height);
    //openGL_program.scaleWithWindow(scaleX,scaleY);
    window_width=width;
    window_height=height;
}