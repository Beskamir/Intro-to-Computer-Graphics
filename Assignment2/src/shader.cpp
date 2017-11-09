//
// Shader class heavily based on: https://learnopengl.com/code_viewer.php?type=header&code=shader
//

#include "shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *tessCtrlPath, const GLchar *tessEvalPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    string vertexCode;
    string fragmentCode;
    string tessCtrlCode;
    string tessEvalCode;

    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream tcShaderFile;
    ifstream teShaderFile;
    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions (ifstream::badbit);
    fShaderFile.exceptions (ifstream::badbit);
    tcShaderFile.exceptions (ifstream::badbit);
    teShaderFile.exceptions (ifstream::badbit);
    try{
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        tcShaderFile.open(tessCtrlPath);
        teShaderFile.open(tessEvalPath);

        stringstream vShaderStream, fShaderStream, tcShaderStream, teShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        tcShaderStream << tcShaderFile.rdbuf();
        teShaderStream << teShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        tcShaderFile.close();
        teShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        tessCtrlCode = tcShaderStream.str();
        tessEvalCode = teShaderStream.str();
    }
    catch (ifstream::failure e){
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar * fShaderCode = fragmentCode.c_str();
    const GLchar * tcShaderCode = tessCtrlCode.c_str();
    const GLchar * teShaderCode = tessEvalCode.c_str();
    // 2. Compile shaders
    GLuint vertex, fragment, tessCtrl, tessEval;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    //// Tessellation Control Shader
    tessCtrl = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tessCtrl, 1, &tcShaderCode, NULL);
    glCompileShader(tessCtrl);
    // Print compile errors if any
    glGetShaderiv(tessCtrl, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(tessCtrl, 512, NULL, infoLog);
        cout << "ERROR::SHADER::TESSELLATION::COMPILATION_FAILED\n" << infoLog << endl;
    }
    //// Tessellation Evaluation Shader
    tessEval = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tessEval, 1, &teShaderCode, NULL);
    glCompileShader(tessEval);
    // Print compile errors if any
    glGetShaderiv(tessEval, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(tessCtrl, 512, NULL, infoLog);
        cout << "ERROR::SHADER::TESSELLATION::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    //glAttachShader(this->Program, tessellation);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(tessCtrl);
    glDeleteShader(tessEval);
}
