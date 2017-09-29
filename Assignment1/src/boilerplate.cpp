// ==========================================================================
// An Object-Oriented Boilerplate Code for GLFW
//
// Author:  Kamyar Allahverdi, University of Calgary. Minor tweaks by Haysn Hornbeck.
// Date:    January 2017
// ==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

//Modified to do it for both Windows and non-windows.
#ifdef _WIN32
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#endif

#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

class Program {
    GLuint vertex_shader;
    GLuint fragment_shader;
public:
    GLuint id;
    Program() {
        vertex_shader = 0;
        fragment_shader = 0;
        id = 0;
    }
    Program(string vertex_path, string fragment_path) {
        init(vertex_path, fragment_path);
    }
    void init(string vertex_path, string fragment_path) {
        id = glCreateProgram();
        vertex_shader = addShader(vertex_path, GL_VERTEX_SHADER);
        fragment_shader = addShader(fragment_path, GL_FRAGMENT_SHADER);
        if (vertex_shader)
            glAttachShader(id, vertex_shader);
        if (fragment_shader)
            glAttachShader(id, fragment_shader);

        glLinkProgram(id);
    }
    GLuint addShader(string path, GLuint type) {
        std::ifstream in(path);
        string buffer = [&in] {
            std::ostringstream ss {};
            ss << in.rdbuf();
            return ss.str();
        }();
        const char *buffer_array[] = { buffer.c_str() };

        GLuint shader = glCreateShader(type);

        glShaderSource(shader, 1, buffer_array, 0);
        glCompileShader(shader);

        // Compile results
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            string info(length, ' ');
            glGetShaderInfoLog(shader, info.length(), &length, &info[0]);
            cerr << "ERROR compiling shader:" << endl << endl;
            cerr << info << endl;
        }
        return shader;
    }
    ~Program() {
        glUseProgram(0);
        glDeleteProgram(id);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
};

class VertexArray {
    std::map<string, GLuint> buffers;
    std::map<string, int> indices;
public:
    GLuint id;
    unsigned int count;
    VertexArray(int c) {
        glGenVertexArrays(1, &id);
        count = c;
    }

    VertexArray(const VertexArray &v) {
        glGenVertexArrays(1, &id);

        // Copy data from the old object
        this->indices = std::map<string, int>(v.indices);
        count = v.count;

        vector<GLuint> temp_buffers(v.buffers.size());

        // Allocate some temporary buffer object handles
        glGenBuffers(v.buffers.size(), &temp_buffers[0]);

        // Copy each old VBO into a new VBO
        int i = 0;
        for (auto &ent : v.buffers) {
            int size = 0;
            glBindBuffer(GL_ARRAY_BUFFER, ent.second);
            glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

            glBindBuffer(GL_COPY_READ_BUFFER, temp_buffers[i]);
            glBufferData(GL_COPY_READ_BUFFER, size, NULL, GL_STATIC_COPY);

            glCopyBufferSubData(GL_ARRAY_BUFFER, GL_COPY_READ_BUFFER, 0, 0, size);
            i++;
        }

        // Copy those temporary buffer objects into our VBOs

        i = 0;
        for (auto &ent : v.buffers) {
            GLuint buffer_id;
            int size = 0;
            int index = indices[ent.first];

            glGenBuffers(1, &buffer_id);

            glBindVertexArray(this->id);
            glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
            glBindBuffer(GL_COPY_READ_BUFFER, temp_buffers[i]);
            glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

            // Allocate VBO memory and copy
            glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, size);
            string indexs = ent.first;

            buffers[ent.first] = buffer_id;
            indices[ent.first] = index;

            // Setup the attributes
            size = size / (sizeof(float) * this->count);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(index);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            i++;
        }

        // Delete temporary buffers
        glDeleteBuffers(v.buffers.size(), &temp_buffers[0]);
    }

    void addBuffer(string name, int index, vector<float> buffer) {
        GLuint buffer_id;
        glBindVertexArray(id);

        glGenBuffers(1, &buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
        buffers[name] = buffer_id;
        indices[name] = index;

        int components = buffer.size() / count;
        glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(index);

        // unset states
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void updateBuffer(string name, vector<float> buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[name]);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    ~VertexArray() {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        for (auto &ent : buffers)
            glDeleteBuffers(1, &ent.second);
    }
};

void render(Program &program, VertexArray &va) {
    // clear screen to a dark grey colour
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Using lines first to get the generator to work

    glUseProgram(program.id);
    glBindVertexArray(va.id);
    glDrawArrays(GL_LINES, 0, va.count);

    glBindVertexArray(0);
    glUseProgram(0);

}

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
