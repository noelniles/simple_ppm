// Utilities for working with PPM images
// Author: Noel Niles
// CSCI-3731
////////////////////////////////////////////////////////////////////////
// Discards the header of a P6 PPM image file. Doesn't handle comments.
void eat_header(void* fp);

// Prints a P6 PPM image header into the first few lines of a new file.
void fprint_header(void* fp, int height, int width, int maxvalue);

// Makes a 2D array ala Numerical Recipes.
unsigned char** tudra(int w, int h);

// Opens a PPM image and saves it to a 2D array of RGB values.
unsigned char** get_ppm(const char* filename, int h, int w);

// Writes a valid PPM image file (hopefully)
bool write_ppm(const char* new_filename, unsigned char** image, int h, int w);

// Flip 180
void flip_ppm(unsigned char** image, int h, int w);
