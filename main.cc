// Author: Noel Niles
// CSCI-3731
//
// Main function to test PPM image manipulations.Not much here.
// The flip function was working when I was using flat arrays and 
// struct for the RGB values. The current version doesn't work.
///////////////////////////////////////////////////////////////////////
#include <cstdio>
#include "ppm.h"

int main(void) {
    const char* filename = "thundar.ppm";
    const char* cp_filename = "thundar_cpy.ppm";
    unsigned char** image = get_ppm(filename, 652, 650);
    printf("%u %u %u", **image, **image+1, **image+2);
    write_ppm(cp_filename, image, 652, 650);
    // The flip_ppm function is broken.
    flip_ppm(image, 652, 650);
    delete *image;
    delete image;
}
