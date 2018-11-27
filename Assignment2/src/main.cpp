//
// main function heavily based on: https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
//

#include "main.h"
#include "setup.h"

void drawCurves();
Mesh getCurve(Mesh newSpline);
glm::mat2x4 getCtrlVerts(int p0, int p1, int p2, int p3, int lastCtrlPoints);
glm::mat3x4 getCtrlColors(int p0, int p1, int p2, int p3, int lastCtrlPoints);

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
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Closing program" << endl;
    return 0;
}

void mainRender(){
    // Define the viewport dimensions
    glViewport(0, 0, window_width, window_height);

    // Build and compile the shader programs
    Shader mShaders("shaderData/vertex.glsl", "shaderData/fragment.glsl", "shaderData/tessControl.glsl", "shaderData/tessEvaluation.glsl","shaderData/geometry.glsl");

    GLuint mTexture=0;
    int imageWidth=0, imageHeight=0;
    loadImage(&mTexture,&imageWidth,&imageHeight);
    // Set up vertex shaderData (and buffer(s)) and attribute pointers
    Mesh imagePlane=genImagePlane(imageWidth,imageHeight);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    vertexArray verts(imagePlane.vertices.size()*imagePlane.vertices[0].size()/3);
    verts.addBuffer("v", 0, imagePlane.vertices);
    verts.addBuffer("c", 1, imagePlane.colors);
    verts.addBuffer("t", 2, imagePlane.texture);

    // main render loop, keeps running until window is closed
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        //Render to screen loop
        renderToScreen(mShaders, verts);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
}


void renderToScreen(Shader mShaders, vertexArray &verts) {
    // clear screen to a dark grey colour
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    mShaders.Use();
    //Setup the transformations that will be used to move the image, curves, points, etc.
    setupTransformations(mShaders);

    //Set image style and whether using a texture or vertex colors
    setImageStyle(mShaders);
    setTextureUsage(mShaders,1);
    drawImage(verts); //Draw the image

    if(showControlPoints){
        setTextureUsage(mShaders,0);
        drawPoints();
    }

    setTextureUsage(mShaders,2);
    drawCurves();

    glUseProgram(0);
}

void drawCurves() {
    if(!splines.empty()){
        for (int i = 0; i < splines.size(); ++i) {
            vertexArray sLines(splines[i].vertices.size()*splines[i].vertices[0].size()/3);
            sLines.addBuffer("v", 0, splines[i].vertices);
            sLines.addBuffer("c", 1, splines[i].colors);
            sLines.addBuffer("t", 2, splines[i].texture);
            glBindVertexArray(sLines.id);
            //glLineWidth(50.0f);
            glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, sLines.count);
            //glEnable(GL_PROGRAM_POINT_SIZE);
            glBindVertexArray(0);
        }
    }
}

void drawPoints() {
    Mesh tempControlPoints;
    tempControlPoints.vertices={};
    tempControlPoints.colors={};
    tempControlPoints.texture={};
    for (int i = 0; i < controlPoints.size(); ++i) {
        for (int j = 0; j < controlPoints[i].size(); ++j) {
            tempControlPoints.vertices.push_back(controlPoints[i][j].vertices);
            tempControlPoints.colors.push_back(controlPoints[i][j].colors);
            tempControlPoints.texture.push_back(controlPoints[i][j].texture);
            //cout<<tempControlPoints.vertices[i][0]<<":"<<tempControlPoints.vertices[i][1]<<endl;
        }
    }
    if(!tempControlPoints.vertices.empty()){
        vertexArray cPoints(tempControlPoints.vertices.size()*tempControlPoints.vertices[0].size()/3);
        cPoints.addBuffer("v", 0, tempControlPoints.vertices);
        cPoints.addBuffer("c", 1, tempControlPoints.colors);
        cPoints.addBuffer("t", 2, tempControlPoints.texture);
        glBindVertexArray(cPoints.id);
        glDrawArrays(GL_POINTS, 0, cPoints.count);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glBindVertexArray(0);
        //cout <<"should be drawing a point"<<endl;
    }
    //for (int i = 0; i < controlPoints.size(); ++i) {
    //
    //}
}


void drawImage(vertexArray &verts) {
    glBindVertexArray(verts.id);
    glDrawArrays(GL_TRIANGLES, 0, verts.count);
    glBindVertexArray(0);
}

void setTextureUsage(Shader mShaders, int textureUsage) {
    GLint imageStyleLocation = glGetUniformLocation(mShaders.Program, "useTexture");
    glUniform1i(imageStyleLocation,textureUsage);
}


void setImageStyle(Shader mShaders) {
    GLint imageStyleLocation = glGetUniformLocation(mShaders.Program, "imageStyle");
    glUniform1i(imageStyleLocation,imageStyle);
}

void setupTransformations(Shader mShaders) {
    //Create transformations
    glm::mat4 transformFunction;
    transformFunction = glm::scale(transformFunction, glm::vec3(scaleFactor, scaleFactor, 1.0f));
    transformFunction = glm::translate(transformFunction, glm::vec3(translate.x, translate.y, 0.0f));
    // Get matrix's uniform location and set matrix
    GLint transformationLocation = glGetUniformLocation(mShaders.Program, "transformation");
    glUniformMatrix4fv(transformationLocation, 1, GL_FALSE, glm::value_ptr(transformFunction));
}

void addControlPoint() {
    Position mouseLocation=getMouseLocation();
    //Fix the location where points should be drawn if the image has been moved or scaled
    glm::mat4 correctiveTransform;
    correctiveTransform = glm::translate(correctiveTransform, glm::vec3(-translate.x, -translate.y, 0.0f));
    correctiveTransform = glm::scale(correctiveTransform, glm::vec3(1/scaleFactor, 1/scaleFactor, 1.0f));

    glm::vec4 fixedLocation={mouseLocation.x,mouseLocation.y,1,1};
    fixedLocation = correctiveTransform * fixedLocation;

    //add control point to the control point data structure
    //vector<float> pointVerts={fixedLocation.x,fixedLocation.y,fixedLocation.z};
    ControlPoint cPoint;

    int lastControlPoints = controlPoints.size()-1;
    if(lastControlPoints<0){
        cPoint.vertices={fixedLocation.x,
                         fixedLocation.y,
                         fixedLocation.z};
        cPoint.colors={0,0,0};
        cPoint.texture={0,0,0};
        vector<ControlPoint> cPoints;
        cPoints.push_back(cPoint);
        controlPoints.push_back(cPoints);
    }
    else{
        cPoint.vertices={fixedLocation.x,
                         fixedLocation.y,
                         fixedLocation.z};
        cPoint.colors={0,0,0};
        cPoint.texture={0,0,0};
        controlPoints[lastControlPoints].push_back(cPoint);
    }
}

void controlPoints2Spline(float loopMax, bool drawLoop) {
    Mesh newSpline;
    newSpline.vertices={};
    glm::mat4 allocations = {{-1,2,-1,0},
                             {3,-5,0,2},
                             {-3,4,1,0},
                             {1,-1,0,0}};
    glm::vec2 curvePoints;
    glm::vec2 curveDerivatives;
    glm::vec3 curveColors;

    int lastCtrlPoints = controlPoints.size()-1;
    float t=0;
    int p0,p1,p2,p3;

    for (float i = 0.0f; i < loopMax; i+=0.005f) {
        if(drawLoop){
            p1=(int)(i);
            p2=(p1+1) % controlPoints[lastCtrlPoints].size();
            p3=(p2+1) % controlPoints[lastCtrlPoints].size();
            p0=p1 >= 1 ? p1 - 1: controlPoints[lastCtrlPoints].size()-1;
        }else{
            p1 = (int)i + 1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        }
        t=i-int(i);
        glm::vec4 tValues = {t*t*t,t*t,t,1};
        //glm::vec4 tDerivatives = {3*t*t,2*t,1,0};

        glm::mat2x4 controlVerts = getCtrlVerts(p0,p1,p2,p3,lastCtrlPoints);
        glm::mat3x4 controlColors = getCtrlColors(p0,p1,p2,p3,lastCtrlPoints);

        curvePoints=0.5f*tValues*allocations*controlVerts;
        curveColors=0.5f*tValues*allocations*controlColors;

        newSpline.vertices.push_back({curvePoints.x,curvePoints.y,1});
        newSpline.colors.push_back({curveColors.r,curveColors.g,curveColors.b});
        newSpline.texture.push_back({0,0,0});
    }
    ControlPoint cPoint;
    cPoint.vertices={};
    cPoint.colors={};
    cPoint.texture={};
    vector<ControlPoint> cPoints;
    controlPoints.push_back(cPoints);

    //newSpline=getCurve(newSpline);

    splines.push_back(newSpline);
}

//Mesh getCurve(Mesh newSpline){
//    Mesh curveData;
//    curveData.vertices={};
//    curveData.colors={};
//    curveData.texture={};
//    for (int i = 0; i < newSpline.vertices.size(); ++i) {
//        curveData.vertices.push_back({newSpline.vertices[i]});
//        curveData.colors.push_back({newSpline.colors[i]});
//        curveData.texture.push_back({newSpline.texture[i]});
//        //cout << pointData2D[i][0] << ","<< pointData2D[i][1]<<endl;
//        if (i>0 && i < (newSpline.vertices.size()-1)){
//            curveData.vertices.push_back({newSpline.vertices[i]});
//            curveData.colors.push_back({newSpline.colors[i]});
//            curveData.texture.push_back({newSpline.texture[i]});
//        }
//    }
//    return curveData;
//}



glm::mat3x4 getCtrlColors(int p0, int p1, int p2, int p3, int lastCtrlPoints) {
    return {
            {controlPoints[lastCtrlPoints][p0].colors[0],controlPoints[lastCtrlPoints][p1].colors[0],controlPoints[lastCtrlPoints][p2].colors[0],controlPoints[lastCtrlPoints][p3].colors[0]},
            {controlPoints[lastCtrlPoints][p0].colors[1],controlPoints[lastCtrlPoints][p1].colors[1],controlPoints[lastCtrlPoints][p2].colors[1],controlPoints[lastCtrlPoints][p3].colors[1]},
            {controlPoints[lastCtrlPoints][p0].colors[2],controlPoints[lastCtrlPoints][p1].colors[2],controlPoints[lastCtrlPoints][p2].colors[2],controlPoints[lastCtrlPoints][p3].colors[2]},
    };
}

glm::mat2x4 getCtrlVerts(int p0, int p1, int p2, int p3, int lastCtrlPoints) {
    glm::mat4x2 controlValues = {
            {controlPoints[lastCtrlPoints][p0].vertices[0],controlPoints[lastCtrlPoints][p0].vertices[1]},
            {controlPoints[lastCtrlPoints][p1].vertices[0],controlPoints[lastCtrlPoints][p1].vertices[1]},
            {controlPoints[lastCtrlPoints][p2].vertices[0],controlPoints[lastCtrlPoints][p2].vertices[1]},
            {controlPoints[lastCtrlPoints][p3].vertices[0],controlPoints[lastCtrlPoints][p3].vertices[1]},
    };
    return glm::transpose(controlValues);
}

void convertControlPoints2Loop() {
    float loopMax=(float)controlPoints[controlPoints.size()-1].size();
    controlPoints2Spline(loopMax,true);
}

void convertControlPoints2Spline() {
    controlPoints[controlPoints.size()-1].insert(controlPoints[controlPoints.size()-1].begin(),controlPoints[controlPoints.size()-1][0]);
    controlPoints[controlPoints.size()-1].insert(controlPoints[controlPoints.size()-1].end(),controlPoints[controlPoints.size()-1][controlPoints[controlPoints.size()-1].size()-1]);

    //float loopMax=(float)controlPoints[controlPoints.size()-1].vertices.size()-3.0f;
    float loopMax=(float)controlPoints[controlPoints.size()-1].size()-3.0f;
    controlPoints2Spline(loopMax,false);
}
