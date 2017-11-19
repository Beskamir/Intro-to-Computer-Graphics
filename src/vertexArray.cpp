//
// Based on Assignment 1 boilerplate
//

#include "vertexArray.h"

vertexArray::vertexArray(int c) {
    glGenVertexArrays(1, &id);
    count = c;
}


void vertexArray::addBuffer(string name, int index, vector<vector<float>> primativeBuffer){
    GLuint buffer_id;
    glBindVertexArray(id);

    vector<float> buffer;
    for (int i = 0; i < primativeBuffer.size(); ++i) {
        for (int j = 0; j < primativeBuffer[i].size(); ++j) {
            buffer.push_back(primativeBuffer[i][j]);
        }
    }

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

void vertexArray::updateBuffer(string name, vector<vector<float>> primativeBuffer)  {
    vector<float> buffer;
    for (int i = 0; i < primativeBuffer.size(); ++i) {
        for (int j = 0; j < primativeBuffer[i].size(); ++j) {
            buffer.push_back(primativeBuffer[i][j]);
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, buffers[name]);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

vertexArray::~vertexArray() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (auto &ent : buffers)
        glDeleteBuffers(1, &ent.second);
}