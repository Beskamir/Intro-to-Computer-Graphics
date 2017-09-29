// ==========================================================================
// An Object-Oriented Boilerplate Code for GLFW
//
// Author:  Kamyar Allahverdi, University of Calgary. Minor tweaks by Haysn Hornbeck.
// Date:    January 2017
// ==========================================================================
//
// Separated into separate files by Sebastian for his sanity.
//

#ifndef ASSIGNMENT1_BOILERPLATE_H
#define ASSIGNMENT1_BOILERPLATE_H

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

using namespace std;


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


#endif //ASSIGNMENT1_BOILERPLATE_H
