#include "ppm.h"

int main(int argc, char* argv[]) {
    const char* filename = "einstein_stamp.ppm";
    const char* cp_filename = "einstein_stamp_cpy.ppm";
    flip_ppm(filename);
    blur_ppm(filename);
}
