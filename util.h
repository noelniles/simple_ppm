#include <cstdio>
#define SAFE_DEL(p) if(NULL != p) {delete p; p = NULL;}
#define SAFE_ARRDEL(p) if(NULL != p) {delete [] p; p = NULL;}

int get_height(const char* filename) {
    char ignore[10];
    int height = 0;
    FILE* fp = fopen(filename, "rb");
    // Gets the type of file
    fscanf(fp, "%s\n%d", ignore, &height);
    fclose(fp);
    return height;
}
int get_width(const char* filename) {
    char ignore[10];
    int width = 0;
    FILE* fp = fopen(filename, "rb");
    // Gets width from PPM
    fscanf(fp, "%s\n%s\n%d", ignore, ignore, &width);
    fclose(fp);
    return width;
}
// Eat the first 4 lines of PPM file
void eat_header(FILE* fp) {
    char ignore[30];
    int int_ignore[30];
    fscanf(fp, "%s\n%i %i\n%i", ignore, int_ignore, int_ignore, 
            int_ignore);
    fgetc(fp); 
}
// Makes a PPM header
void fprint_header(FILE* fp, int height, int width, int maxvalue) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", height, width);
    fprintf(fp, "%d\n", maxvalue);
}
// Get the volume of the image
int get_vol(const char* filename) {
    int height = get_height(filename);
    int width = get_width(filename);
    int img_vol = width*height*3;
    return img_vol;
}
