// This file contains functions that read, write and modify PPM image files
// Author: Noel Niles
// Email : noelniles@gmail.com
#include <cstdio>
#include "util.h"
// Gets the image data from filename and puts it into and array of pixels.
// Caller must delete array.
struct pixel {
    unsigned char red, green, blue;
};
pixel* get_ppm(const char* filename) {
    int height = get_height(filename);
    int width = get_width(filename);
    FILE* fp = fopen(filename, "rb");
    pixel* img = new pixel[height*width];

    eat_header(fp);
    // Reads the image into an array of structs
    for (int i = 0; i < height*width; i++) {
        pixel px;
        px.red = fgetc(fp);
        px.green = fgetc(fp);
        px.blue = fgetc(fp);
        img[i] = px;
    }
    
    fclose(fp);
    printf("Gots it.\n");
    return img; 
}
// Writes a PPM header and an array of pixel data to a new_filename);
void write_ppm(const char* orig_filename, const char* new_filename, 
        pixel* img_data) {
    int height = get_height(orig_filename);
    int width = get_width(orig_filename);
    int maxvalue = 255;
    FILE* fp = fopen(new_filename, "wb");
    fprint_header(fp, height, width, maxvalue);
    for (int i = 0; i < height*width; i++) {
        fputc(img_data[i].red, fp);
        fputc(img_data[i].green, fp);
        fputc(img_data[i].blue, fp);
    }
    printf("Data written.\n");
    fclose(fp);
}
// Reverses a pixel array, flipping the image.
void flip_ppm(const char* filename) {
    int height = get_height(filename);
    int width = get_width(filename);
    int vol = height*width; 
    pixel* orig = get_ppm(filename);
    pixel* flip = new pixel[vol];
    for(int i = 0, j = vol; i<vol; i++, j--) {
        flip[i].red = orig[j].red;
        flip[i].green = orig[j].green;
        flip[i].blue = orig[j].blue;
    }
    printf("Data flipped.\n");
    write_ppm(filename, "flip.ppm", flip);
    SAFE_ARRDEL(flip);
    SAFE_ARRDEL(orig);
}
// Blurs an image by taking the average color from a group of neighboring pixels
// and applying the average across the group. Not working yet. 
void blur_ppm(const char* filename) {
    const int height = get_height(filename);
    const int width = get_width(filename);
    int vol = height*width; 
    pixel* orig = get_ppm(filename);
    pixel* blur = new pixel[vol];
    for(int i = 0; i < width*height; i++) {
        // Just goofing around.
        blur[i].red = orig[i].red*2%199;
        blur[i].green = orig[i].green*2%199;
        blur[i].blue = orig[i].blue*2%199;
    }
    printf("image blurred");
    write_ppm(filename, "blur.ppm", blur);
    delete blur;
}
