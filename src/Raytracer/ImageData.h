//
// This will export the render
//

#ifndef ASSIGNMENT4_IMAGE_H
#define ASSIGNMENT4_IMAGE_H


#include "Color.h"

class ImageData {
private:
    int width, height;
    //vector<vector<Color>> pixelData;
    Color * pixelData;

public:
    ImageData(int width, int height){
        this->width=width;
        this->height=height;
        pixelData = new Color[width*height];
    };
    ~ImageData(){
        delete[] pixelData;
    };

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
