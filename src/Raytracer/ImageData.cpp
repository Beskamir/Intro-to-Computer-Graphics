//
// This will export the render
//

#include <iostream>
#include <fstream>
#include "ImageData.h"

void ImageData::storePixel(int x, int y, Color color) {
    //pixelData[x+(y*width)] = color;
    framebuffer[x][y] = vec3(color.r,color.g,color.b);

}

//write to ppm based on: https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
void ImageData::writeToPPM(string name) {
        FILE *fp = fopen((name+".ppm").c_str(), "wb"); /* b - binary mode */
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            static unsigned char color[3];
            color[0] = (unsigned char) (framebuffer[x][y].r * 255);
            color[1] = (unsigned char) (framebuffer[x][y].g * 255);
            color[2] = (unsigned char) (framebuffer[x][y].b * 255);
            //color[1] = (unsigned char) (pixelData[x+(y*width)].g * 255);
            //color[2] = (unsigned char) (pixelData[x+(y*width)].b * 255);

            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}

ImageData::ImageData(int width, int height) {
    this->width=width;
    this->height=height;
    //pixelData = new Color[width*height];
    for (int i = 0; i < width; ++i) {
        vector<vec3> tempframebuffer;
        for (int j = 0; j < height; ++j) {
            tempframebuffer.emplace_back(0);
        }
        framebuffer.push_back(tempframebuffer);
    }
}
