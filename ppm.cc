// This file contains functions that read, write and modify PPM image files
// Author: Noel Niles
// CSCI-3731
//
///////////////////////////////////////////////////////////////////////////
#include <cstdio>

// Eat the first 4 lines of PPM file
void eat_header(void* fptr) {
    FILE* fp;
    fp = (FILE*)fptr;
    char ignore[30];
    int int_ignore[30];
    fscanf(fp, "%s\n%i %i\n%i", ignore, int_ignore, int_ignore, 
            int_ignore);
    fgetc(fp); 
}
// Makes a PPM header
void fprint_header(void* fptr, int height, int width, int maxvalue) {
    FILE* fp;
    fp = (FILE*)fptr;
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "%d\n", maxvalue);
}

// Creates a 2D array ala Numerical Recipes. Caller must delete the 
// returned array.
unsigned char** tudra(int w, int h) {
    unsigned char** image = new unsigned char*[h];
    *image = new unsigned char[w*h];
    for(int i = 1; i < h; ++i) {
        image[i] = image[i-1] + w;
    }
    return image;        
}
// Gets the image data from filename and puts into 2D array.
unsigned char** get_ppm(const char* filename, int h, int w) {
    FILE* fp = fopen(filename, "rb");
    eat_header(fp);
    unsigned char** image = tudra(w * 3, h);
    int nbytes = h * w * 3;
    int nread = fread(*image, sizeof(**image), nbytes, fp);
    if(nread != nbytes) {
        fprintf(stderr, "Only read %d of %d bytes\n", nread, nbytes);
        return NULL;
    }
    fclose(fp);
    return image; 
}
// Writes a PPM header and an array of pixel data to a new_filename);
bool write_ppm(const char* new_filename, unsigned char** image, 
        int h, int w) {
    FILE* fp = fopen(new_filename, "wb");
    int nbytes = w * 3 * h;
    fprint_header(fp, h, w, 255); 
    int nwritten = fwrite(*image, sizeof(**image), nbytes, fp);
    if(nwritten != nbytes) {
        fprintf(stderr, "Only wrote %d of %d bytes\n", nwritten, nbytes);
        return false;
    }
    fclose(fp);
    return true;
}
// Flip image. Doesn't work yet.
void flip_ppm(unsigned char** image, int h, int w) {
    unsigned char** flip = tudra (w*3, h);
    for(int i = h; i<0; i--) { 
        for(int j = w*3; j>0; j--){
            flip[i][j] = image[i][j];
        }
    }
    write_ppm("flipped_thundar.ppm", flip, h, w);
}
