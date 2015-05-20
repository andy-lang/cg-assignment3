#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include <iostream>

int main(int argc, char const* argv[]) {
    int x, y, n;
    unsigned char* img = SOIL_load_image("geom/cube-tex/auvBG.png", &x, &y, &n, SOIL_LOAD_RGBA);
    std::cout << x << ", " << y << " (" << n << ")" << std::endl;
    /*
    for (int i = 0; i < x*y; i+=3) {
        std::cout << (int)img[i] << ", " << (int)img[i+1] << ", " << (int)img[i+2] << ", " << (int)img[i+3] << std::endl;
    }
    */
    return 0;
}
