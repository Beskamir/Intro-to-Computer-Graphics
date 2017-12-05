//
// This will export the render
//

#ifndef ASSIGNMENT4_IMAGE_H
#define ASSIGNMENT4_IMAGE_H


#include <glm/vec3.hpp>
#include "../Scene/Shading/Color.h"

using namespace glm;
class ImageData {
private:
    int width, height;
    //vector<vector<Color>> pixelData;
    //Color * pixelData;
    vector<vector<vec3>> framebuffer;

public:
    ImageData(int width, int height);
    ~ImageData() = default;

    void writeToPPM(string name);

    void storePixel(int x, int y, Color color);

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }
};


#endif //ASSIGNMENT4_IMAGE_H
